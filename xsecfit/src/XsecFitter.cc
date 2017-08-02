#include "XsecFitter.hh"
#include <TGraph.h>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>

using namespace std;

//ClassImp(XsecFitter)

TVirtualFitter *fitter = 0;

//dummy function for SetFCN
void dummy_fcn( Int_t &npar, Double_t *gin, Double_t &f,
               Double_t *par, Int_t iflag )
{
    XsecFitter *myObj;
    myObj = dynamic_cast<XsecFitter*>(fitter->GetObjectFit());
    //Call the actual chi2 function inside our class
    myObj->fcn( npar, gin, f, par, iflag );
}

// ctor
XsecFitter::XsecFitter(int seed)
{
    rand = new TRandom3(seed);
    //set gRandom to our rand
    gRandom = rand;
    m_dir   = NULL;
    m_freq  = -1;
}

// dtor
XsecFitter::~XsecFitter()
{
    if(rand) rand->Delete();
    m_dir = NULL;
}

// SetSeed
void XsecFitter::SetSeed(int seed)
{
    if(!rand)
    {
        rand = new TRandom3(seed);
        gRandom = rand; //Global pointer
    }
    else
        rand->SetSeed(seed);
}

void XsecFitter::FixParameter(string par_name, double value){
    for(int i=0;i<m_npar;i++)
    {
        size_t pos=par_names[i].find(par_name);
        if(pos != std::string::npos){
            fitter->SetParameter(i, par_names[i].c_str(), value,
                                 0, value, value);
            fitter->FixParameter(i);
            cout<<"XsecFitter: fixing parameter "<<par_names[i].c_str()<<" to value "<<value<<endl;
        }
    }
}

// PrepareFitter
void XsecFitter::InitFitter(std::vector<AnaFitParameters*> &fitpara)
{
    m_fitpara = fitpara;
    vector<double> par_step, par_low, par_high;
    //vector<int> par_fix;
    
    m_npar = 0;
    m_nparclass.clear();
    //get the parameter info
    for(size_t i=0;i<m_fitpara.size();i++)
    {
        m_npar += (int)m_fitpara[i]->Npar;
        m_nparclass.push_back((int)m_fitpara[i]->Npar);
        
        vector<string> vec0;
        m_fitpara[i]->GetParNames(vec0);
        par_names.insert(par_names.end(), vec0.begin(), vec0.end());
        
        vector<double> vec1, vec2;
        m_fitpara[i]->GetParPriors(vec1);
        par_prefit.insert(par_prefit.end(), vec1.begin(), vec1.end());
        
        m_fitpara[i]->GetParSteps(vec1);
        par_step.insert(par_step.end(), vec1.begin(), vec1.end());
        
        m_fitpara[i]->GetParLimits(vec1, vec2);
        par_low.insert(par_low.end(), vec1.begin(), vec1.end());
        par_high.insert(par_high.end(), vec2.begin(), vec2.end());
        
        //vector<int> vec3
        //m_fitpara[i]->GetFixStatus(vec3);
        //par_fix.insert(par_fix.end(), vec3.begin(), vec3.end());
    }
    
    if(m_npar == 0)
    {
        cerr<<"ERROR: no fit parameters were defined"<<endl;
        fitter = 0;
        return;
    }
    cout<<"==========================================="<<endl;
    cout<<"           Initilizing fitter              "<<endl;
    cout<<"    Number of parameters = " <<m_npar<<endl;
    cout<<"==========================================="<<endl;
    
    
    TVirtualFitter::SetDefaultFitter("Minuit");
    fitter = TVirtualFitter::Fitter(0, m_npar);
    //pass our object to the fitter
    fitter->SetObjectFit(this);
    //set the dummy fcn
    fitter->SetFCN(dummy_fcn);
    
    double arglist[5];
    // use this to have low printout
    // arglist[0] = -1.;
    arglist[0] = 1;
    fitter->ExecuteCommand("SET PRINT", arglist, 1);
    
    //init fitter stuff
    for(int i=0;i<m_npar;i++)
    {
        fitter->SetParameter(i, par_names[i].c_str(), par_prefit[i],
                             par_step[i], par_low[i], par_high[i]);
    }
}

// Fit
//datatype = 1 if toy from nuisances
//           2 if external fake dataset
void XsecFitter::Fit(std::vector<AnaSample*> &samples, int datatype)
{
    cout<<"Starting to fit"<<endl;
    m_calls = 0;
    m_samples = samples;
    if(!fitter)
    {
        cerr<<"ERROR: fitter has not been initialized"<<endl;
        return;
    }
    
    //generate toy data to fit
    if(datatype==1){
        GenerateToyData(0);
        cout<<"toy data generated"<<endl;
        //save hists if requested
        for(size_t s=0;s<m_samples.size();s++)
        {
            ((FitSample*)m_samples[s])->GetSampleBreakdown(m_dir,"thrown");
        }
    }
    else if(datatype==2 || datatype==3){
        for(size_t s=0;s<m_samples.size();s++)
        {
            m_samples[s]->FillEventHisto(datatype);
            //can be done to test but it is not the real thrown toy
            //((FitSample*)m_samples[s])->GetSampleBreakdown(m_dir,"thrown");
        }
    }
    if(m_freq>=0  && m_dir) DoSaveEvents(m_calls);
    
    //Do fit
    double arglist[5];
    arglist[0] = 1000000; //number of calls (was 10k)
    arglist[1] = 1.0E-5; //tolerance
    fitter->ExecuteCommand("MIGRAD", arglist, 2);
    //fitter->ExecuteCommand("MINOS", arglist, 2);
    
    //print the results
    Double_t amin;
    Double_t edm, errdef;
    Int_t nvpar, nparx;
    fitter->GetStats(amin, edm, errdef, nvpar, nparx);
    
    //fill chi2 info
    if(m_dir) DoSaveChi2();
    
    //save fit results
    TVectorD fitVec(nparx);
    vector< vector<double> > res_pars;
    vector< vector<double> > err_pars;
    int k=0;
    for(size_t i=0;i<m_fitpara.size();i++)
    {
        vector<double> vec_res;
        vector<double> vec_err;
        for(int j=0;j<m_nparclass[i];j++){
            vec_err.push_back(fitter->GetParError(k));
            double parvalue=fitter->GetParameter(k);
            vec_res.push_back(parvalue);
            fitVec(k) = parvalue;
            k++;
        }
        res_pars.push_back(vec_res);
        err_pars.push_back(vec_err);
    }
    
    if(k != nparx){
        cout<<"XsecFitter ERROR in number of parameters"<<endl;
        abort();
    }
    m_dir->cd();
    TMatrixDSym matrix(nvpar,fitter->GetCovarianceMatrix());
    matrix.Write("res_cov_matrix");
    fitVec.Write("res_vector");
    
    DoSaveResults(res_pars,err_pars,amin);
    if(m_freq>=0  && m_dir) DoSaveEvents(m_calls);
}

// GenerateToyData
void XsecFitter::GenerateToyData(int toyindx)
{
    //do parameter throws
    vector< vector<double> > par_throws;
    double chi2_sys = 0.0;
    for(size_t i=0;i<m_fitpara.size();i++)
    {
        if(toyindx == 0) m_fitpara[i]->InitThrows();
        vector<double> pars;
        m_fitpara[i]->DoThrow(pars);
        cout<<"Parameters "<<m_fitpara[i]->GetName()<<endl;
        for(size_t j=0;j<pars.size();j++)
            cout<<j<<" "<<pars[j]<<endl;
        //m_fitpara[i]->GetParPriors(pars);
        par_throws.push_back(pars);
        chi2_sys =+ m_fitpara[i]->GetChi2(pars);
    }
    vec_chi2_sys.push_back(chi2_sys);
    
    //Generate toy data histograms
    double chi2_stat=FillSamples(par_throws, 1);
    vec_chi2_stat.push_back(chi2_stat);
    
    if(m_freq>=0  && m_dir) DoSaveParams(par_throws);
}


// FillSample with new parameters
//datatype = 0 if fit iteration
//           1 if toy dataset from nuisances
double XsecFitter::FillSamples(vector< vector<double> > new_pars,
                               int datatype)
{
    double chi2 = 0.0;
    //loop over samples
    for(size_t s=0;s<m_samples.size();s++)
    {
        //loop over events
        for(int i=0;i<m_samples[s]->GetN();i++)
        {
            AnaEvent* ev = m_samples[s]->GetEvent(i);
            ev->SetEvWght(ev->GetEvWghtMC());//why using EvWghtMC?
            //do weights for each AnaFitParameters obj
            for(size_t j=0;j<m_fitpara.size();j++)
            {
                if((datatype==1) && (((TString)(m_fitpara[j]->GetName())).Contains("par_detAve")))
                    continue;
                if((datatype==0) && (((TString)(m_fitpara[j]->GetName())).Contains("par_detFine")))
                    continue;
                m_fitpara[j]->ReWeight(ev, s, i, new_pars[j]);
            }
        }
        m_samples[s]->FillEventHisto(datatype);
        
        //calculate chi2 for each sample
        chi2 += m_samples[s]->CalcChi2();
        //if (s!=0) chi2 += m_samples[s]->CalcChi2();//hack here to remove the chisq from signal sample
	}
    return chi2;
}

// fcn <-- this is the actual FCN
void XsecFitter::fcn(Int_t &npar, Double_t *gin, Double_t &f,
                     Double_t *par, Int_t iflag)
{
    m_calls++;
    
    vector< vector<double> > new_pars;
    int k=0;
    double chi2_sys = 0.0;
    for(size_t i=0;i<m_fitpara.size();i++)
    {
        vector<double> vec;
        for(int j=0;j<m_nparclass[i];j++)
            vec.push_back(par[k++]);
        chi2_sys += m_fitpara[i]->GetChi2(vec);
        new_pars.push_back(vec);
    }
    vec_chi2_sys.push_back(chi2_sys);
    
    double chi2_stat = FillSamples(new_pars, 0);
    vec_chi2_stat.push_back(chi2_stat);
    
    //save hists if requested
    if(m_calls % (m_freq*10000) == 0  && m_dir) {
        DoSaveParams(new_pars);
        if(m_calls % (m_freq*10000) == 0) {
            DoSaveEvents(m_calls);
        }
    }
    // total chi2
    f = chi2_stat + chi2_sys;
}

// Write hists for reweighted events
void XsecFitter::DoSaveEvents(int fititer)
{
    for(size_t s=0;s<m_samples.size();s++){
        m_samples[s]->Write(m_dir, Form("evhist_sam%d_iter%d",(int)s,m_calls), fititer);
    }
}


// Write hists for parameter values
void XsecFitter::DoSaveParams(vector< vector<double> > new_pars)
{
    //loop on number of parameter classes
    for(size_t i=0;i<m_fitpara.size();i++)
    {
        TH1D* histopar = new TH1D(Form("paramhist_par%s_iter%d",m_fitpara[i]->GetName().c_str(),m_calls),
                                  Form("paramhist_par%s_iter%d",m_fitpara[i]->GetName().c_str(),m_calls),
                                  m_nparclass[i], 0, m_nparclass[i]);
        //loop on number of parameters in each class
        vector <string> parnames;
        m_fitpara[i]->GetParNames(parnames);
        for(int j=0;j<m_nparclass[i];j++)
        {
            histopar->GetXaxis()->SetBinLabel(j+1,TString(parnames[j]));
            histopar->SetBinContent(j+1,(new_pars[i])[j]);
        }
        m_dir->cd();
        histopar->Write();
        delete histopar;
    }
}

void XsecFitter::DoSaveChi2()
{
    TH1D* histochi2stat = new TH1D("chi2_stat_periter","chi2_stat_periter",
                                   m_calls+1, 0, m_calls+1);
    TH1D* histochi2sys = new TH1D("chi2_sys_periter","chi2_sys_periter",
                                  m_calls+1, 0, m_calls+1);
    TH1D* histochi2tot = new TH1D("chi2_tot_periter","chi2_tot_periter",
                                  m_calls+1, 0, m_calls+1);
    if(vec_chi2_stat.size() != vec_chi2_sys.size()){
        cout<<"Number of saved iterations for chi2 stat and chi2 syst different -  EXITING"<<endl;
        exit(-1);
    }
    //loop on number of parameter classes
    for(size_t i=0;i<vec_chi2_stat.size();i++)
    {
        histochi2stat->SetBinContent(i+1,vec_chi2_stat[i]);
        histochi2sys->SetBinContent(i+1,vec_chi2_sys[i]);
        histochi2tot->SetBinContent(i+1,vec_chi2_sys[i] + vec_chi2_stat[i]);
    }
    m_dir->cd();
    histochi2stat->Write();
    histochi2sys->Write();
    histochi2tot->Write();
    
    delete histochi2stat;
    delete histochi2sys;
    delete histochi2tot;
}

void XsecFitter::DoSaveResults(vector< vector<double> > parresults, vector< vector<double> > parerrors, double chi2){
    //loop on number of parameter classes
    for(size_t i=0;i<m_fitpara.size();i++)
    {
        TH1D* histopar = new TH1D(Form("paramhist_par%s_result",m_fitpara[i]->GetName().c_str()),
                                  Form("paramhist_par%s_result",m_fitpara[i]->GetName().c_str()),
                                  m_nparclass[i], 0, m_nparclass[i]);
        TH1D* histoparerr = new TH1D(Form("paramerrhist_par%s_result",m_fitpara[i]->GetName().c_str()),
                                     Form("paramerrhist_par%s_result",m_fitpara[i]->GetName().c_str()), 
                                     m_nparclass[i], 0, m_nparclass[i]);
        //loop on number of parameters in each class
        vector <string> parnames;
        m_fitpara[i]->GetParNames(parnames);
        for(int j=0;j<m_nparclass[i];j++) 
        {
            histopar->GetXaxis()->SetBinLabel(j+1,TString(parnames[j]));
            histopar->SetBinContent(j+1,(parresults[i])[j]);
            histoparerr->GetXaxis()->SetBinLabel(j+1,TString(parnames[j]));
            histoparerr->SetBinContent(j+1,(parerrors[i])[j]);
        }
        m_dir->cd();
        histopar->Write();
        histoparerr->Write();
        delete histopar;
        delete histoparerr;
    }
    double x[1]={0};
    double y[1]={chi2};
    TGraph* grapchi2 = new TGraph(1,x,y);
    grapchi2->SetName("final_chi2_fromMinuit");
    m_dir->cd();
    grapchi2->Write();
    
    //ADDED save actual final results
    for(size_t s=0;s<m_samples.size();s++)
    {
        ((FitSample*)m_samples[s])->GetSampleBreakdown(m_dir,"fit");
    }
}
