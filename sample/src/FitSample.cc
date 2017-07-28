//////////////////////////////////////////////////////////
//
//  A class for Fit samples for CC1picoh analysis
//
//
//
//  Created: Thu Jun  6 12:01:10 CEST 2013
//  Modified:
//
//////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <assert.h>

#include "FitSample.hh"
#include "baseTree.hh"
#include "Setting.hh"
using namespace std;
//let check
  /*      TH1D *henu_true_data;
    TH1D *henu_rec_data;
    TH1D *hpmu_rec_data;
    TH1D *hcth_rec_data;
    TH2D *hpmucth_rec_data;
    TH1D *hpmu_true_data;
    TH1D *hcth_true_data;
    TH1D *hccqebin_true_data;
    TH1D *hccqebin_rec_data;*/
// ctor
FitSample::FitSample(int sample_id, string name,
                       std::vector<std::pair <double,double> > v_pedges,
                       std::vector<std::pair <double,double> > v_cthedges,
                       TTree* data)
{
    m_sampleid = sample_id; //unique id
    m_name     = name;      //some comprehensible name
    //cout<<"NEW SAMPLE with name "<<name<<" sample id "<<sample_id<<endl;
    m_data_tree = data;
    m_pedges = v_pedges;
    m_cthedges = v_cthedges;
    
    for(int i=0;i<v_pedges.size(); i++){
        cout<<v_cthedges[i].first<<"  "<<v_cthedges[i].second<<"  "<<v_pedges[i].first<<"  "<<v_pedges[i].second<<endl;
    }
    
    //Default binning choices
    nbins_enu = 28;
    bins_enu = new double[nbins_enu + 1];
    for(int i=0;i<=nbins_enu;i++)
    {
        if(i<10) bins_enu[i] = i*0.1;
        else if(i>=10 && i<18) bins_enu[i] = 1.0 + (i-10)*0.2;
        else if(i==18) bins_enu[i] = 2.7;
        else if(i>=19 && i<23) bins_enu[i] = 3.0 + (i-19)*0.5;
        else if(i>=23) bins_enu[i] = 5.0 + (i-23)*1.0;
    }
    
    /*nbins_pmu = 15;
    bins_pmu = new double[nbins_pmu + 1];
    for(int i=0;i<=nbins_pmu;i++)
    {
        if(i==0) bins_pmu[i] = 0.0;
        else if(i>=1 && i<=9) bins_pmu[i] = 0.2 + (i-1)*0.1;
        else if(i==10) bins_pmu[i] = 1.25;
        else if(i==11) bins_pmu[i] = 1.5;
        else if(i==12) bins_pmu[i] = 2.0;
        else if(i==13) bins_pmu[i] = 3.0;
        else if(i==14) bins_pmu[i] = 5.0;
        else if(i==15) bins_pmu[i] = 30.0;
    }
    
    nbins_cthmu = 11;
    bins_cthmu = new double[nbins_cthmu + 1];
    bins_cthmu[0]  = -1.0;
    bins_cthmu[1]  =  0.6;
    bins_cthmu[2]  =  0.7;
    bins_cthmu[3]  =  0.8;
    bins_cthmu[4]  =  0.85;
    bins_cthmu[5]  =  0.9;
    bins_cthmu[6]  =  0.92;
    bins_cthmu[7]  =  0.94;
    bins_cthmu[8]  =  0.96;
    bins_cthmu[9]  =  0.98;
    bins_cthmu[10] =  0.99;
    bins_cthmu[11] =  1.00;*/
    
    nbins_pmu = 4;
    bins_pmu = new double[nbins_pmu + 1];
    bins_pmu[0] = 0.0;
    bins_pmu[1] = 0.65;
    bins_pmu[2] = 0.95;
    bins_pmu[3] = 1.05;
    bins_pmu[4] = 5.0;
    
    nbins_cthmu = 5;
    bins_cthmu = new double[nbins_cthmu + 1];
    bins_cthmu[0]  = 0.0;
    bins_cthmu[1]  =  0.7;
    bins_cthmu[2]  =  0.9;
    bins_cthmu[3]  =  0.94;
    bins_cthmu[4]  =  0.98;
    bins_cthmu[5] =  1.00;
    
    
    nccqebins=m_pedges.size();
    bins_ccqe = new double[nccqebins+1];
    for (int i=0; i<=nccqebins; i++){
        bins_ccqe[i]=i;
    }
    cout<<"ccqe bins defined"<<endl;
    //event distribution histo
    m_hpred = NULL;
    m_hmc   = NULL;
    //m_hmcfake = NULL;//newadd
    MakeHistos(); //with default binning
    
    cout<<"MakeHistos called"<<endl;
    //data (or toy) histo
    m_hdata = NULL;
    
    m_norm  = 1.0;
}

// dtor
FitSample::~FitSample()
{
    m_hpred->Delete();
    m_hmc->Delete();
   // m_hmcfake->Delete();//newadd
    if(m_hdata != NULL) m_hdata->Delete();
    delete [] bins_pmu;
    delete [] bins_cthmu;
    delete [] bins_enu;
}

// MakeEventHisto
void FitSample::MakeHistos()
{
    if(m_hpred != NULL) m_hpred->Delete();
    m_hpred = new TH1D(Form("%s_pred_recpmucthmu", m_name.c_str()),
                       Form("%s_pred_recpmucthmu", m_name.c_str()),
                       nccqebins, bins_ccqe);
    m_hpred->SetDirectory(0);
    
    if(m_hmc != NULL) m_hmc->Delete();
    m_hmc = new TH1D(Form("%s_mc_recpmucthmu", m_name.c_str()),
                     Form("%s_mc_recpmucthmu", m_name.c_str()),
                     nccqebins, bins_ccqe);
    m_hmc->SetDirectory(0);
    
    //newadd
    /*if(m_hmcfake != NULL) m_hmcfake->Delete();
    m_hmcfake = new TH1D(Form("%s_mcfake_recpmucthmu", m_name.c_str()),
                     Form("%s_mcfake_recpmucthmu", m_name.c_str()),
                     nccqebins, bins_ccqe);
    m_hmcfake->SetDirectory(0);*/
    
    cout<<nccqebins<<" bins inside MakeHistos"<<endl;
}

void FitSample::SetData(TObject *hdata)
{
    //clone the data histogram internally
    if(m_hdata != NULL) m_hdata->Delete();
    m_hdata = (TH1D*)hdata->Clone(Form("%s_data", m_name.c_str()));
    m_hdata->SetDirectory(0);
}

// SetPmuBinning
void FitSample::SetPmuBinning(int nbins, double *bins)
{
    nbins_pmu = nbins;
    delete [] bins_pmu;
    bins_pmu = new double[nbins_pmu + 1];
    for(int i=0;i<=nbins_pmu;i++)
        bins_pmu[i] = bins[i];
}

// SetCThmuBinning
void FitSample::SetCThmuBinning(int nbins, double *bins)
{
    nbins_cthmu = nbins;
    delete [] bins_cthmu;
    bins_cthmu = new double[nbins_cthmu + 1];
    for(int i=0;i<=nbins_cthmu;i++)
        bins_cthmu[i] = bins[i];
}

// SetEnuBinning
void FitSample::SetEnuBinning(int nbins, double *bins)
{
    nbins_enu = nbins;
    delete [] bins_enu;
    bins_enu = new double[nbins_enu + 1];
    for(int i=0;i<=nbins_enu;i++)
        bins_enu[i] = bins[i];
}

// FillEventHist
void FitSample::FillEventHisto(int datatype)
{
    if(m_hpred) m_hpred->Reset();
    if(m_hmc) m_hmc->Reset();
    //if(m_hmcfake) m_hmcfake->Reset();//newadd
    for(size_t i=0;i<m_events.size();i++)
    {
        double pmu_rec   = m_events[i].GetRecPtrk();
        double cthmu_rec = m_events[i].GetRecCThtrk();
        double wght      = m_events[i].GetEvWght();
        double wghtscale = wght;
        //this is for quick fake data check, with option 1
        //change the weight for Signal
        /*if (m_events[i].GetReaction()==0) {
            wghtscale = wght * 0.6;//
        }*/
        for(int j=0; j<nccqebins; j++){
            if((pmu_rec > m_pedges[j].first) && (pmu_rec  < m_pedges[j].second)  &&
               (cthmu_rec  > m_cthedges[j].first) && (cthmu_rec  < m_cthedges[j].second)){
                m_hpred->Fill(j+0.5,wght);
                m_hmc->Fill(j+0.5,wght);
                //m_hpred->Fill(j+0.5,wghtscale);
                //m_hmc->Fill(j+0.5,wghtscale);
                //m_hmcfake->Fill(j+0.5,wghtscale);//newadd
                break;
            }
        }
    }
    m_hpred->Scale(m_norm);
    m_hmc->Scale(m_norm);
    //m_hmcfake->Scale(m_norm);//newadd
    //cout<<"TEST MCFAKE "<<m_hmcfake->Integral(0,m_hmcfake->GetNbinsX()+1)<<endl;
    
    //data without stat variation: useful when nuisance parameters
    //varied in the toys
    if(datatype==1)
    {
        SetData(m_hpred);
        m_hdata->Reset();
        for(int j=1;j<=m_hpred->GetNbinsX();j++)
        {
            double val = m_hpred->GetBinContent(j);
            //cout<<"bin "<<j<<" entry "<<val<<endl;
            if(val == 0.0) {
                cout<<"FitSample:"<<m_sampleid<<" bin "<<j<<" with 0 entries may cause proble on chi2 computations"<<endl;
                continue;
            }
            int binc = gRandom->Poisson(val);
            //m_hdata->SetBinContent(j,binc); //with statistical fluctuations
            m_hdata->SetBinContent(j,val);  //without statistical fluctuations
        }
        cout<<"FitSample:"<<m_sampleid<<" fake data "<<m_hdata->Integral()<<endl;
    }
    
    //data from external (fake) dataset
    else if(datatype==2) {
        //THIS iS FOR REAL DATA
        /*SetData(m_hpred);
        m_hdata->Reset();
        double pmu_rec_tree,cthmu_rec_tree,wght;
        int topology;
        baseTree *pbaseTree = new baseTree;
        pbaseTree->Init(m_data_tree);
        
        for(size_t i=0;i<m_data_tree->GetEntries();i++){
            m_data_tree->GetEntry(i);
            topology = pbaseTree->GetSampleType(i);
            pmu_rec_tree = pbaseTree->GetPrec(pbaseTree->range);
            cthmu_rec_tree = TMath::Cos(TMath::Pi()/180.*(pbaseTree->muang_t));
            wght = 1.;
            //change weight for CC1picoh
            //if (abs(pbaseTree->inttype) ==16) {
              //  wght = 0.6;
            //}
            /////////////////////////
            if(topology != m_sampleid) continue;
            for(int j=0; j<nccqebins; j++){
                if((pmu_rec_tree > m_pedges[j].first) && (pmu_rec_tree  < m_pedges[j].second)  &&
                   (cthmu_rec_tree  > m_cthedges[j].first) && (cthmu_rec_tree  < m_cthedges[j].second)){
                    m_hdata->Fill(j+0.5,wght);
                    //cout<<"filling "<<pmu_rec_tree/1000<<" "<<wght_syst<<endl;
                    break;
                }
            }
        }*/
        //THIS is FOR FAKE GENIE data
        SetData(m_hpred);
        m_hdata->Reset();
        ////////////////////////////////////////////////////////////////////
        ////GET the weight
        //Bool_t isEnergyReweightInclude = true;
        string fratio="../../data//nd34_tuned_11bv3.1_250ka.root";
        TH1D*  tratio[NMOD];
        TH1D*  tratio2[NMOD];
        double rwratio[NMOD][NBIN];
        TFile *fTFRatio   = new TFile(fratio.c_str());
        for(int i=0;i<NMOD;i++){
            char histname[300];
            char histname2[300];
            sprintf(histname,"ing%d_tune_numu",i);
            sprintf(histname2,"ing%d_nom_numu",i);
            tratio[i]= (TH1D*)fTFRatio  ->Get(histname);
            tratio2[i]= (TH1D*)fTFRatio  ->Get(histname2);
            for(int j=0;j<NBIN;j++){
                if(tratio2[i]->GetBinContent(j+1)!=0)
                    rwratio[i][j]=(tratio[i]->GetBinContent(j+1))/(tratio2[i]->GetBinContent(j+1));
                else
                    rwratio[i][j]=1;
            }
        }
        
        double pmu_rec_tree,cthmu_rec_tree,wght;
        int topology;
        baseTree *pbaseTree = new baseTree;
        pbaseTree->Init(m_data_tree);
        //newadd 20170205 new histo
	///////////////////////////////////////////////////////////////////////

	/*TH1D *henu_true_data;
    TH1D *henu_rec_data;
    TH1D *hpmu_rec_data;
    TH1D *hcth_rec_data;
    TH2D *hpmucth_rec_data;
    TH1D *hpmu_true_data;
    TH1D *hcth_true_data;
    TH1D *hccqebin_true_data;
    TH1D *hccqebin_rec_data;


	henu_true_data = new TH1D(Form("sam%d_TrueEnu_data", m_sampleid),Form("sam%d_TrueEnu_data", m_sampleid), nbins_enu, bins_enu);
    
    henu_rec_data = new TH1D(Form("sam%d_RecEnu_data", m_sampleid), Form("sam%d_RecEnu_data", m_sampleid), nbins_enu, bins_enu);
    henu_rec_data->SetDirectory(0);
    henu_rec_data->GetXaxis()->SetTitle("Recon E_{#nu} (GeV)");
    
    hpmu_rec_data = new TH1D(Form("sam%d_RecPmu_data",m_sampleid),Form("sam%d_RecPmu_data", m_sampleid), nbins_pmu, bins_pmu);
    hpmu_rec_data->SetDirectory(0);
    hpmu_rec_data->GetXaxis()->SetTitle("Recon p_{#mu} (GeV/c)");
    
    hcth_rec_data = new TH1D(Form("sam%d_RecCTh_data",m_sampleid),Form("sam%d_RecCTh_data",m_sampleid), nbins_cthmu, bins_cthmu);
    hcth_rec_data->SetDirectory(0);
    hcth_rec_data->GetXaxis()->SetTitle("Recon cos#theta_{#mu}");
    
    hpmucth_rec_data = new TH2D(Form("sam%d_RecPmuCTh_data",m_sampleid), Form("sam%d_RecPmuCTh_data", m_sampleid), nbins_pmu, bins_pmu,nbins_cthmu, bins_cthmu);
    hpmucth_rec_data->SetDirectory(0);
    hpmucth_rec_data->GetXaxis()->SetTitle("Recon p_{#mu} (GeV/c)");
    hpmucth_rec_data->GetXaxis()->SetTitle("Recon cos#theta_{#mu}");
    
    hpmu_true_data = new TH1D(Form("sam%d_TruePmu_data",m_sampleid),Form("sam%d_TruePmu_data",m_sampleid),nbins_pmu, bins_pmu);
    hpmu_true_data->SetDirectory(0);
    hpmu_true_data->GetXaxis()->SetTitle("True p_{#mu} (GeV/c)");
    
    hcth_true_data = new TH1D(Form("sam%d_TrueCTh_data",m_sampleid),Form("sam%d_TrueCTh_data",m_sampleid),nbins_cthmu, bins_cthmu);
    hcth_true_data->SetDirectory(0);
    hcth_true_data->GetXaxis()->SetTitle("True cos#theta_{#mu}");
    
    hccqebin_true_data = new TH1D(Form("sam%d_ccqebins_true_data",m_sampleid),Form("sam%d_ccqebins_true_data",m_sampleid),nccqebins, bins_ccqe);
    hccqebin_true_data->SetDirectory(0);
    hccqebin_true_data->GetXaxis()->SetTitle("CCQE bins");
    
    hccqebin_rec_data = new TH1D(Form("sam%d_ccqebins_rec_data", m_sampleid),Form("sam%d_ccqebins_rec_data",m_sampleid),nccqebins, bins_ccqe);
    hccqebin_rec_data->SetDirectory(0);
    hccqebin_rec_data->GetXaxis()->SetTitle("CCQE bins");
*/
	/////////////////////////////////////////////////////////////////////// 
        for(size_t i=0;i<m_data_tree->GetEntries();i++){
            m_data_tree->GetEntry(i);
            topology = pbaseTree->GetSampleType(i);
            pmu_rec_tree = pbaseTree->GetPrec(pbaseTree->range);
            cthmu_rec_tree = TMath::Cos(TMath::Pi()/180.*(pbaseTree->muang_t));
            //get weight
            Float_t mcWeight = (pbaseTree->fileIndex==1)*3974.0/3950.0 +(pbaseTree->fileIndex==2)*SCALEBAR + (pbaseTree->fileIndex==3)*SCALEWALL + (pbaseTree->fileIndex==4)*SCALEINGRID + (pbaseTree->fileIndex==5)*SCALENUE;
            
            Float_t totweight = (pbaseTree->norm)*(pbaseTree->totcrsne)*mcWeight*2.8647e-13;
            
            int intnue=(pbaseTree->nuE)/NMAX*NBIN;
            if(intnue>=NBIN)intnue=NBIN-1;
            
            if (isEnergyReweightInclude) {
                totweight *=rwratio[3][intnue];
            }
            //if INGRID background
            if (pbaseTree->fileIndex==4) totweight *= 29.16/2.8647;
            //if wall background
            if (pbaseTree->fileIndex==3) totweight = ((pbaseTree->norm)*(pbaseTree->totcrsne)<0.2e18)*1.106*(pbaseTree->norm)*(pbaseTree->totcrsne)*mcWeight*6.9e-12/1.3;
            //TODO reweight for genie
            if (pbaseTree->fileIndex==10) {
                totweight = 3.41e-2*NMCFILE*1e21/NPOT;//to mimic NEUT
                if (isEnergyReweightInclude) {
                    totweight *=rwratio[3][intnue];
                }
            }
            //for Data
            if (pbaseTree->fileIndex==0) totweight = 1.0;
            
            wght = totweight;//this is for data
            
            /////////////////////////
            if(topology != m_sampleid) continue;
		//fill some basic plots
	/////////////////////////////////////////////////////////////////////////////////////
	//get values
    /*double enu_true;
    double enu_rec, pmu_rec, cth_rec, pmu_true, cth_true;
    enu_true = pbaseTree->nuE;//newadd
    pmu_rec = pbaseTree->GetPrec(pbaseTree->range);
    enu_rec = pbaseTree->GetErec(pmu_rec*1000., pbaseTree->muang_t);
    cth_rec = TMath::Cos(TMath::Pi()/180.*pbaseTree->muang_t);
    pmu_true = pbaseTree->GetPrec(pbaseTree->range);//placeholder
    cth_true = TMath::Cos(TMath::Pi()/180.*pbaseTree->muang_t);//placeholder
    
    //fill histogram
    henu_true_data->Fill(enu_true, wght);//newadd
    henu_rec_data->Fill(enu_rec, wght);
    hpmu_rec_data->Fill(pmu_rec, wght);
    hcth_rec_data->Fill(cth_rec, wght);
    hpmu_true_data->Fill(pmu_true, wght);
    hcth_true_data->Fill(cth_true, wght);
    cout<<"sample "<<m_sampleid<<" Fake GENIE data crosscheck"<<hcth_rec_data->Integral()<<endl;
	hpmucth_rec_data->Fill(pmu_rec, cth_rec, wght);
  
	    henu_true_data->Scale(m_norm);
    henu_rec_data->Scale(m_norm);
    hpmu_rec_data->Scale(m_norm);
    hcth_rec_data->Scale(m_norm);
    hpmu_true_data->Scale(m_norm);
    hcth_true_data->Scale(m_norm);

    henu_true_data->Write();
    henu_rec_data->Write();
    hpmu_rec_data->Write();
    hcth_rec_data->Write();
    hpmu_true_data->Write();
    hcth_true_data->Write();*/
     ////////////////////////////////////////////////////////////////////////////////////
            for(int j=0; j<nccqebins; j++){
                if((pmu_rec_tree > m_pedges[j].first) && (pmu_rec_tree  < m_pedges[j].second)  &&
                   (cthmu_rec_tree  > m_cthedges[j].first) && (cthmu_rec_tree  < m_cthedges[j].second)){
                    if(pbaseTree->fileIndex>0) m_hdata->Fill(j+0.5,wght);
                    //cout<<"filling "<<pmu_rec_tree/1000<<" "<<wght_syst<<endl;
                    break;
                }
            }//end j
            
        }//end for
        m_hdata->Scale(m_norm);
         
        cout<<"sample "<<m_sampleid<<" Fake GENIE data"<<m_hdata->Integral()<<endl;

    }
    //data with statistical variation
    //(used when no nuisance sampling but nuisances are fitted)
    else if(datatype==3)
    {
        SetData(m_hpred);
        m_hdata->Reset();
        for(size_t i=0;i<m_events.size();i++)
        {
            double pmu_rec   = m_events[i].GetRecPtrk();
            double cthmu_rec = m_events[i].GetRecCThtrk();
            double wght      = m_events[i].GetEvWght();
            double wghtscale = wght;
            //change the weight for Signal
           /* if (m_events[i].GetReaction()==0) {
                wghtscale = wght * 0.6;//
            }*/
            for(int j=0; j<nccqebins; j++){
                if((pmu_rec > m_pedges[j].first) && (pmu_rec  < m_pedges[j].second)  &&
                   (cthmu_rec  > m_cthedges[j].first) && (cthmu_rec  < m_cthedges[j].second)){
                    m_hdata->Fill(j+0.5,wghtscale);
                    break;
                }
            }
        }
        m_hdata->Scale(m_norm);
        //Poisson fluctuation
        for(int j=1;j<=m_hdata->GetNbinsX();j++)
        {
            double val = m_hdata->GetBinContent(j);
            if(val == 0.0) {
                cout<<"FitSample:"<<m_sampleid<<" bin "<<j<<" with 0 entries may cause proble on chi2 computations"<<endl;
                continue;
            }
            int binc = gRandom->Poisson(val);
            m_hdata->SetBinContent(j,binc); //with statistical fluctuations
            //m_hdata->SetBinContent(j,val);  //without statistical fluctuations
        }//end for j
        
        
        
        /*
         SetData(m_hpred);
         m_hdata->Reset();
         for(int j=1;j<=m_hpred->GetNbinsX();j++)
        {
            double val = m_hpred->GetBinContent(j);
            //cout<<"bin "<<j<<" entry "<<val<<endl;
            if(val == 0.0) {
                cout<<"FitSample:"<<m_sampleid<<" bin "<<j<<" with 0 entries may cause proble on chi2 computations"<<endl;
                continue;
            }
            int binc = gRandom->Poisson(val);
            //m_hdata->SetBinContent(j,binc); //with statistical fluctuations
            m_hdata->SetBinContent(j,val);  //without statistical fluctuations
        }//end for j
        */
        /*SetData(m_hmcfake);
        m_hdata->Reset();
        for(int j=1;j<=m_hmcfake->GetNbinsX();j++)
        {
            double val = m_hmcfake->GetBinContent(j);
            if(val == 0.0) {
                cout<<"FitSample:"<<m_sampleid<<" bin "<<j<<" with 0 entries may cause proble on chi2 computations"<<endl;
                continue;
            }
            int binc = gRandom->Poisson(val);
            //m_hdata->SetBinContent(j,binc); //with statistical fluctuations
            m_hdata->SetBinContent(j,val);  //without statistical fluctuations
        }//end for j*/
        cout<<"FitSample:"<<m_sampleid<<" fake data "<<m_hdata->Integral(0, m_hdata->GetNbinsX()+1)<<endl;
    }
    //this is for genievsneutPlot
    else if(datatype==4)
    {
        SetData(m_hpred);
    }
   
    
}

double FitSample::CalcChi2()
{
    if(m_hdata == NULL)
    {
        cerr<<"ERROR: need to define data histogram"<<endl;
        return 0.0;
    }
    
    int nx = m_hpred->GetNbinsX();
    //int ny = m_hpred->GetNbinsY();
    
    if(nx != m_hdata->GetNbinsX())// || ny != m_hdata->GetNbinsY())
    {
        cerr<<"ERROR: binning mismatch between data and mc"<<endl;
        return 0.0;
    }
    
    double chi2 = 0.0;
    for(int j=1;j<=nx;j++)
    {
        double obs = m_hdata->GetBinContent(j);
        double exp = m_hpred->GetBinContent(j);
        if(exp>0.0){  //added when external fake datasets (you cannot reweight when simply 0)
            // this didn't happen when all from same MC since if exp=0 then obs =0
            chi2 += 2*(exp - obs);
            if(obs>0.0)
                chi2 += 2*obs*TMath::Log(obs/exp);
            //else
            //cout<<"bin "<<j<<" has observation "<<obs<<" PROBLEM???"<<endl;
        }
    }
    
    if(chi2 != chi2)
    {
        cerr<<"ERROR: stat chi2 is nan"<<endl;
        chi2 = 0.0;
    }
    
    return chi2;
}

// GetSampleBreakdown
void FitSample::GetSampleBreakdown(TDirectory *dirout, string tag)
{
    /*int nreac = 5;
    const char *names[] = {"cc0pi", "cc1pi", "ccother",
        "backg", "OOFV"};*/
    const int nreac = 9;//10;--> ignore genie
    //const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall","genie"};
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall"};
    TH1D *henu_true[nreac];//newadd
    TH1D *henu_rec[nreac];
    TH1D *hpmu_rec[nreac];
    TH1D *hcth_rec[nreac];
    TH2D *hpmucth_rec[nreac];
    TH1D *hpmu_true[nreac];
    TH1D *hcth_true[nreac];
    TH1D *hccqebin_true[nreac];
    TH1D *hccqebin_rec[nreac];
    TH1D *hveract[nreac];
	//add20170511
    TH1D *hrecang1trk[nreac];
    TH1D *hrecang2trk[nreac];
    TH1D *hrecangopening[nreac];
    TH1D *hrecangcoplanarity[nreac];
    TH1D *hrecqsq[nreac];
    int compos[nreac];
    double sumofweight[nreac];//ignore GENIE
    double totsumofweight=0;
    for(int i=0;i<nreac;i++)
    {
        compos[i] = 0;
        //newadd
        henu_true[i] = new TH1D(Form("%s_TrueEnu_%s_%s",
                                    m_name.c_str(),names[i],tag.c_str()),
                               Form("%s_TrueEnu_%s_%s",
                                    m_name.c_str(),names[i],tag.c_str()),
                               nbins_enu, bins_enu);
        
        henu_rec[i] = new TH1D(Form("%s_RecEnu_%s_%s",
                                    m_name.c_str(),names[i],tag.c_str()),
                               Form("%s_RecEnu_%s_%s",
                                    m_name.c_str(),names[i],tag.c_str()),
                               nbins_enu, bins_enu);
        henu_rec[i]->SetDirectory(0);
        henu_rec[i]->GetXaxis()->SetTitle("Recon E_{#nu} (GeV)");
        
        hpmu_rec[i] = new TH1D(Form("%s_RecPmu_%s_%s",
                                    m_name.c_str(),names[i],tag.c_str()),
                               Form("%s_RecPmu_%s_%s",
                                    m_name.c_str(),names[i],tag.c_str()),
                               nbins_pmu, bins_pmu);
        hpmu_rec[i]->SetDirectory(0);
        hpmu_rec[i]->GetXaxis()->SetTitle("Recon p_{#mu} (GeV/c)");
        
        hcth_rec[i] = new TH1D(Form("%s_RecCTh_%s_%s",
                                    m_name.c_str(),names[i],tag.c_str()),
                               Form("%s_RecCTh_%s_%s",
                                    m_name.c_str(),names[i],tag.c_str()),
                               nbins_cthmu, bins_cthmu);
        hcth_rec[i]->SetDirectory(0);
        hcth_rec[i]->GetXaxis()->SetTitle("Recon cos#theta_{#mu}");
        
        hpmucth_rec[i] = new TH2D(Form("%s_RecPmuCTh_%s_%s",
                                       m_name.c_str(),names[i],tag.c_str()),
                                  Form("%s_RecPmuCTh_%s_%s",
                                       m_name.c_str(),names[i],tag.c_str()),
                                  nbins_pmu, bins_pmu,
                                  nbins_cthmu, bins_cthmu);
        hpmucth_rec[i]->SetDirectory(0);
        hpmucth_rec[i]->GetXaxis()->SetTitle("Recon p_{#mu} (GeV/c)");
        hpmucth_rec[i]->GetXaxis()->SetTitle("Recon cos#theta_{#mu}");
        
        hpmu_true[i] = new TH1D(Form("%s_TruePmu_%s_%s",
                                     m_name.c_str(),names[i],tag.c_str()),
                                Form("%s_TruePmu_%s_%s",
                                     m_name.c_str(),names[i],tag.c_str()),
                                nbins_pmu, bins_pmu);
        hpmu_true[i]->SetDirectory(0);
        hpmu_true[i]->GetXaxis()->SetTitle("True p_{#mu} (GeV/c)");
        
        hcth_true[i] = new TH1D(Form("%s_TrueCTh_%s_%s",
                                     m_name.c_str(),names[i],tag.c_str()),
                                Form("%s_TrueCTh_%s_%s",
                                     m_name.c_str(),names[i],tag.c_str()),
                                nbins_cthmu, bins_cthmu);
        hcth_true[i]->SetDirectory(0);
        hcth_true[i]->GetXaxis()->SetTitle("True cos#theta_{#mu}");
        
        hccqebin_true[i] = new TH1D(Form("%s_ccqebins_true_%s_%s",
                                         m_name.c_str(),names[i],tag.c_str()),
                                    Form("%s_ccqebins_true_%s_%s",
                                         m_name.c_str(),names[i],tag.c_str()),
                                    nccqebins, bins_ccqe);
        hccqebin_true[i]->SetDirectory(0);
        hccqebin_true[i]->GetXaxis()->SetTitle("CCQE bins");
        
        hccqebin_rec[i] = new TH1D(Form("%s_ccqebins_rec_%s_%s",
                                        m_name.c_str(),names[i],tag.c_str()),
                                   Form("%s_ccqebins_rec_%s_%s",
                                        m_name.c_str(),names[i],tag.c_str()),
                                   nccqebins, bins_ccqe);
        hccqebin_rec[i]->SetDirectory(0);
        hccqebin_rec[i]->GetXaxis()->SetTitle("CCQE bins");

	hveract[i] = new TH1D(Form("%s_Veract_%s_%s",
                                     m_name.c_str(),names[i],tag.c_str()),
                                Form("%s_Veract_%s_%s",
                                     m_name.c_str(),names[i],tag.c_str()),
                                200,0,400);
	hveract[i]->SetDirectory(0);
	hveract[i]->GetXaxis()->SetTitle("Energy deposit at vertex [MeV]");
	//add20170511
        hrecang1trk[i] = new TH1D(Form("%s_recang1trk_%s_%s",
                                   m_name.c_str(),names[i],tag.c_str()),
                              Form("%s_recang1trk_%s_%s",
                                   m_name.c_str(),names[i],tag.c_str()),
                              90,0,90);
	hrecang1trk[i]->SetDirectory(0);
	hrecang1trk[i]->GetXaxis()->SetTitle("#mu-like track angle");
        hrecang2trk[i] = new TH1D(Form("%s_recang2trk_%s_%s",
                                       m_name.c_str(),names[i],tag.c_str()),
                                  Form("%s_recang2trk_%s_%s",
                                       m_name.c_str(),names[i],tag.c_str()),
                                  90,0,90);
	hrecang2trk[i]->SetDirectory(0);
	hrecang2trk[i]->GetXaxis()->SetTitle("#pi-like track angle");
        hrecangopening[i] = new TH1D(Form("%s_recangopening_%s_%s",
                                       m_name.c_str(),names[i],tag.c_str()),
                                  Form("%s_recangopening_%s_%s",
                                       m_name.c_str(),names[i],tag.c_str()),
                                  180,0,180);
	hrecangopening[i]->SetDirectory(0);
	hrecangopening[i]->GetXaxis()->SetTitle("Track opening angle");
        hrecangcoplanarity[i] = new TH1D(Form("%s_angcoplanarity_%s_%s",
                                          m_name.c_str(),names[i],tag.c_str()),
                                     Form("%s_angcoplanarity_%s_%s",
                                          m_name.c_str(),names[i],tag.c_str()),
                                     180,0,180);
	hrecangcoplanarity[i]->SetDirectory(0);
	hrecangcoplanarity[i]->GetXaxis()->SetTitle("Track coplanarity angle");
        hrecqsq[i] = new TH1D(Form("%s_recqsq_%s_%s",
                                   m_name.c_str(),names[i],tag.c_str()),
                              Form("%s_recqsq_%s_%s",
                                   m_name.c_str(),names[i],tag.c_str()),
                              100,0,1);
	hrecqsq[i]->SetDirectory(0);
	hrecqsq[i]->GetXaxis()->SetTitle("Reconstructed Q^{2}");
    }
    
    //loop over the events & fill histogram
    // ////////////////////////////////////////
    
    int Ntot = GetN();
    cout<<"Sample size "<<Ntot<<" vs "<< m_events.size()<<endl;
    for(size_t i=0;i<m_events.size();i++)
    {
        //get values
        double enu_true;
        double enu_rec, pmu_rec, cth_rec, pmu_true, cth_true, wght;
        enu_true = m_events[i].GetTrueEnu();//newadd
        enu_rec = m_events[i].GetRecEnu();
        pmu_rec = m_events[i].GetRecPtrk();
        cth_rec = m_events[i].GetRecCThtrk();
        pmu_true = m_events[i].GetTruePtrk();
        cth_true = m_events[i].GetTrueCThtrk();
        wght    = m_events[i].GetEvWght();
        int rtype = m_events[i].GetReaction();
       //20170205
	double veract_rec;
	veract_rec = m_events[i].GetVeract(); 
	//add20170511
        double recang1trk, recang2trk, recangopening, recangcoplanarity, recqsq;
        recang1trk = m_events[i].GetRecAng1trk();
        recang2trk = m_events[i].GetRecAng2trk();
        recangopening = m_events[i].GetRecAngOpening();
        recangcoplanarity = m_events[i].GetRecAngCoplanarity();
        recqsq = m_events[i].GetRecQsq();
        //fill histogram
        compos[rtype]++;
        henu_true[rtype]->Fill(enu_true, wght);//newadd
        henu_rec[rtype]->Fill(enu_rec, wght);
        hpmu_rec[rtype]->Fill(pmu_rec, wght);
        hcth_rec[rtype]->Fill(cth_rec, wght);
        hpmu_true[rtype]->Fill(pmu_true, wght);
        hcth_true[rtype]->Fill(cth_true, wght);
        hpmucth_rec[rtype]->Fill(pmu_rec, cth_rec, wght); 
	hveract[rtype]->Fill(veract_rec,wght);//20170205
	//add20170511
        hrecang1trk[rtype]->Fill(recang1trk,wght);
        hrecang2trk[rtype]->Fill(recang2trk,wght);
        hrecangopening[rtype]->Fill(recangopening,wght);
        hrecangcoplanarity[rtype]->Fill(recangcoplanarity,wght);
        hrecqsq[rtype]->Fill(recqsq,wght);
        for(int j=0; j<nccqebins; j++){
            if((pmu_true > m_pedges[j].first) && (pmu_true < m_pedges[j].second)  &&
               (cth_true > m_cthedges[j].first) && (cth_true < m_cthedges[j].second)){
                hccqebin_true[rtype]->Fill(j+0.5,wght);
                break;
            }
        }
        for(int j=0; j<nccqebins; j++){
            if((pmu_rec > m_pedges[j].first) && (pmu_rec < m_pedges[j].second)  &&
               (cth_rec > m_cthedges[j].first) && (cth_rec < m_cthedges[j].second)){
                hccqebin_rec[rtype]->Fill(j+0.5,wght);
                break;
            }
        }
    }
    
    dirout->cd();
    //tree->Write();
    for(int i=0;i<nreac;i++)
    {
        henu_true[i]->Scale(m_norm);//newadd
        henu_rec[i]->Scale(m_norm);
        hpmu_rec[i]->Scale(m_norm);
        hcth_rec[i]->Scale(m_norm);
        hpmu_true[i]->Scale(m_norm);
        hcth_true[i]->Scale(m_norm);
        hpmucth_rec[i]->Scale(m_norm);
        hccqebin_true[i]->Scale(m_norm);
        hccqebin_rec[i]->Scale(m_norm);
	hveract[i]->Scale(m_norm); //20170205
	//add0170511
	hveract[i]->Scale(m_norm);
        hrecang1trk[i]->Scale(m_norm);
        hrecang2trk[i]->Scale(m_norm);
        hrecangopening[i]->Scale(m_norm);
        hrecangcoplanarity[i]->Scale(m_norm);
        hrecqsq[i]->Scale(m_norm);
        //sumofweight[i] = henu_true[i]->GetSumOfWeights();//newadd
        sumofweight[i] = henu_true[i]->Integral(0,henu_true[i]->GetNbinsX()+1);//newadd
        if (i<9) totsumofweight += sumofweight[i];//newadd
        henu_true[i]->Write();
        henu_rec[i]->Write();
        hpmu_rec[i]->Write();
        hcth_rec[i]->Write();
        hpmu_true[i]->Write();
        hcth_true[i]->Write();
        hpmucth_rec[i]->Write();
        hccqebin_true[i]->Write();
        hccqebin_rec[i]->Write();
	hveract[i]->Write(); //20170205
	//newadd20170511
        hrecang1trk[i]->Write();
        hrecang2trk[i]->Write();
        hrecangopening[i]->Write();
        hrecangcoplanarity[i]->Write();
        hrecqsq[i]->Write();        

        henu_true[i]->Delete();//newadd
        henu_rec[i]->Delete();
        hpmu_true[i]->Delete();
        hcth_true[i]->Delete();
        hpmu_rec[i]->Delete();
        hcth_rec[i]->Delete();
        hpmucth_rec[i]->Delete();
        hccqebin_true[i]->Delete();
        hccqebin_rec[i]->Delete();
	hveract[i]->Delete();//20170205
	//newadd20170511
        hrecang1trk[i]->Delete();
        hrecang2trk[i]->Delete();
        hrecangopening[i]->Delete();
        hrecangcoplanarity[i]->Delete();
        hrecqsq[i]->Delete();
    }
    cout<<"============> Sample "<<m_name<<" <============"<<endl;
    //GENIE is used for test,ignore the last one
    /*for(int j=0;j<nreac;j++)
        cout<<setw(10)<<names[j]<<setw(5)<<j<<setw(10)<<compos[j]
        <<setw(10)<<(float)(compos[j])/(Ntot-compos[9])*100.0<<"%"<<endl;*/
        for(int j=0;j<nreac;j++)
        cout<<setw(10)<<names[j]<<setw(5)<<j<<setw(10)<<sumofweight[j]
        <<setw(10)<<(float)(sumofweight[j])/(totsumofweight)*100.0<<"%"<<endl;
}

// Write
void FitSample::Write(TDirectory *dirout, const char *bsname, int fititer)
{
    dirout->cd();
    m_hpred->Write(Form("%s_pred", bsname));
    if(fititer==0){
        m_hmc->Write(Form("%s_mc", bsname));
       // m_hmcfake->Write(Form("%s_mcfake", bsname));//newadd
        if(m_hdata != NULL) m_hdata->Write(Form("%s_data", bsname));
    }

    /*henu_true_data->Write();
    henu_rec_data->Write();
    hpmu_rec_data->Write();
    hcth_rec_data->Write();
    hpmu_true_data->Write();
    hcth_true_data->Write();*/

}
