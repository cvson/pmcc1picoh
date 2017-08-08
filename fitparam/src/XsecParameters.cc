#include <fstream>
#include <sstream>
#include <iomanip>
#include <assert.h>

#include "XsecParameters.hh"

using namespace std;

//ctor
XsecParameters::XsecParameters(const char *name)
{
    m_name = name;
    
    //parameter number, names & prior values
    //(Npar, values and ordering should be in agreement with input TFiles)
    //TODO: Group other remained to one?
    Npar=6;//NEUt 5.3.2 MECNorm
    //Npar=9;
    //MAQE
    pars_name.push_back(Form("%s%d%s", m_name.c_str(), 0,"MECNorm"));
    /*pars_prior.push_back(1.21);
    pars_step.push_back(0.45/5);
    pars_limlow.push_back(0.5);
    pars_limhigh.push_back(2.5);*/
    pars_prior.push_back(0.0);
    pars_step.push_back(0.4/5);
    pars_limlow.push_back(-5.0);//
    pars_limhigh.push_back(5.0);
    
    //MARES
    pars_name.push_back(Form("%s%d%s", m_name.c_str(), 1,"MACCQE"));
    /*pars_prior.push_back(1.41);
    pars_step.push_back(0.11);
    pars_limlow.push_back(0.5);
    pars_limhigh.push_back(2.5);*/
    pars_prior.push_back(0.0);
    pars_step.push_back(0.4/5);
    pars_limlow.push_back(-5.0);
    pars_limhigh.push_back(5.0);
    
    //CC1piE0
    pars_name.push_back(Form("%s%d%s", m_name.c_str(), 2,"CA5RES"));
    /*pars_prior.push_back(1.15);
    pars_step.push_back(0.43/5.);
    pars_limlow.push_back(-1.40);//why negative?
    pars_limhigh.push_back(2.44);*/
    pars_prior.push_back(0.0);
    pars_step.push_back(0.4/5.);
    pars_limlow.push_back(-5.0);//why negative?
    pars_limhigh.push_back(5.0);
    
    //CC1piE1
    pars_name.push_back(Form("%s%d%s", m_name.c_str(), 3,"MaNFFRES"));
    /*pars_prior.push_back(1.0);
    pars_step.push_back(0.40/5.);
    pars_limlow.push_back(-0.2);
    pars_limhigh.push_back(2.2);*/
    pars_prior.push_back(0.0);
    pars_step.push_back(0.40/5.);
    pars_limlow.push_back(-5.0);
    pars_limhigh.push_back(5.0);
    
    //CCother
    pars_name.push_back(Form("%s%d%s", m_name.c_str(), 4,"BgSclRES"));
    /*pars_prior.push_back(0.0);
    pars_step.push_back(0.4/5);
    pars_limlow.push_back(-1.2);
    pars_limhigh.push_back(1.2);*/
    pars_prior.push_back(0.0);
    pars_step.push_back(0.4/5);
    pars_limlow.push_back(-5.0);
    pars_limhigh.push_back(5.0);
    
    //Pi-less delta decay
    pars_name.push_back(Form("%s%d%s", m_name.c_str(), 5,"dismpishp"));
    pars_prior.push_back(0.0);
    pars_step.push_back(0.4/5);
    pars_limlow.push_back(-5.0);//
    pars_limhigh.push_back(5.0);//
    
   //1pi Enu shape
    /*pars_name.push_back(Form("%s%d%s", m_name.c_str(), 6,"1piEnuShape"));
    pars_prior.push_back(0.0);
    pars_step.push_back(0.4/5);
    pars_limlow.push_back(-5.0);
    pars_limhigh.push_back(5.0);
   */
    //all else
   /* pars_name.push_back(Form("%s%d%s", m_name.c_str(), 6,"AllElse"));
    pars_prior.push_back(0.0);
    pars_step.push_back(0.4/5);
    pars_limlow.push_back(-5.0);
    pars_limhigh.push_back(5.0);
   */


}

//dtor
XsecParameters::~XsecParameters()
{;}

// store response functions in vector of Xsec "bins" (Ereco, Etrue, reac, topo)
void XsecParameters::StoreResponseFunctions(vector<TFile*> respfuncs, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges)
{
    for ( int stInt = s_SIG; stInt != s_CRIII+1; stInt++ ){
     // for ( int stInt = s_SIG; stInt != s_CRII+1; stInt++ ){
         SampleTypes sampletype = static_cast <SampleTypes> (stInt);
        //for ( int rtInt = ReCC1picoh; rtInt != OutFGD+1; rtInt++){
        for ( int rtInt = ReCCQE; rtInt != OutFGD+1; rtInt++){
            ReactionTypes reactype = static_cast<ReactionTypes>(rtInt);
            cout<<"reading response functions for topology "<<stInt<<"  reaction "<<rtInt<<endl;
            int nccqebins=v_pedges.size();
            for(int br=0;br<nccqebins;br++){//reco kinematics bin
                //cout<<"reading rewighting function for reco bin "<<br<<endl;
                //for(int bt=0;bt<nccqebins;bt++){//true kinematics bin
                    //cout<<"reading rewighting function for true bin "<<bt<<endl;
                    XsecBin bin;
                    bin.recoPlow = v_pedges[br].first;
                    bin.recoPhigh = v_pedges[br].second;
                    //bin.truePlow = v_pedges[bt].first; //same binning for reco and true
                    //bin.truePhigh = v_pedges[bt].second;
                    bin.recoCTHlow = v_cthedges[br].first;
                    bin.recoCTHhigh = v_cthedges[br].second;
                    //bin.trueCTHlow = v_cthedges[bt].first; //same binning for reco and true
                    //bin.trueCTHhigh = v_cthedges[bt].second;
                    bin.topology = sampletype;
                    bin.reaction = reactype;
                    //if(fabs(br-bt)<21) {  //save memory if reco bin and true bin very far away
                        for(uint i=0; i<Npar; i++){
                            char name[200];
                            //sprintf(name,"topology_%d/RecBin_%d_trueBin_%d_topology_%d_reac_%d",stInt,br,bt,stInt,rtInt);
                            //sprintf(name,"sample_%d/RecBin_%d_sample_%d_reac_%d",stInt,br,stInt,rtInt);
                            //in the response function file, signal included
                            sprintf(name,"response_sample%d_reaction%d_bin%d",stInt,rtInt+1,br);
                            //cout<<respfuncs[i]->GetName()<<" "<<name<<endl;
                            TGraph* g=(TGraph*)respfuncs[i]->Get(name);
                            //cout<<g<<endl;
                            g->SetName(name);
                            bin.respfuncs.push_back(g);
                        }
                    //}
                    m_bins.push_back(bin);
               // }
            }//end for br
        }//end for rtInt
    }//end for stInt
    
    /*for(size_t j=0; j<m_bins.size();j++){
     cout<<j<<" topology: "<<m_bins[j].topology<<"  reaction: "<<m_bins[j].reaction
     <<"  recoP: "<<m_bins[j].recoPlow<<"-"<<m_bins[j].recoPhigh
        <<"  recoCTH: "<<m_bins[j].recoCTHlow<<"-"<<m_bins[j].recoCTHhigh<<endl;
     if(m_bins[j].respfuncs.size()>0)
     cout<<" response function name "<<m_bins[j].respfuncs[0]->GetName()<<endl;
     else
     cout<<" no response function"<<endl;
     }*/
    
}

// --
/*int XsecParameters::GetBinIndex(SampleTypes sampletype, ReactionTypes reactype,
                                double Pmureco, double Pmutrue, double CTHmureco, double CTHmutrue)
{
    int binn = BADBIN;
    for(size_t i=0;i<m_bins.size();i++)
    {
        if(m_bins[i].topology == sampletype && m_bins[i].reaction == reactype &&
           (Pmureco > m_bins[i].recoPlow) && (Pmureco  < m_bins[i].recoPhigh)  &&
           (CTHmureco  > m_bins[i].recoCTHlow) && (CTHmureco  < m_bins[i].recoCTHhigh) &&
           (Pmutrue > m_bins[i].truePlow) && (Pmutrue  < m_bins[i].truePhigh)  &&
           (CTHmutrue  > m_bins[i].trueCTHlow) && (CTHmutrue  < m_bins[i].trueCTHhigh)){
            binn = (int)i;
            break;
        }
    }
    //cout<<"topology "<<sampletype<<"  reaction "<<reactype<<endl;
     //cout<<"recoP "<<Pmureco<<"  trueP "<<Pmutrue<<"    recoCTH "<<CTHmureco<<"  trueCTH "<<CTHmutrue<<endl;
     //cout<<"BIN "<<binn<<endl<<endl;
    return binn;
}*/
int XsecParameters::GetBinIndex(SampleTypes sampletype, ReactionTypes reactype,
                                double Pmureco, double CTHmureco)
{
    int binn = BADBIN;
    for(size_t i=0;i<m_bins.size();i++)
    {
        if(m_bins[i].topology == sampletype && m_bins[i].reaction == reactype &&
           (Pmureco > m_bins[i].recoPlow) && (Pmureco  < m_bins[i].recoPhigh)  &&
           (CTHmureco  > m_bins[i].recoCTHlow) && (CTHmureco  < m_bins[i].recoCTHhigh)){
            binn = (int)i;
            break;
        }
    }
    //cout<<"topology "<<sampletype<<"  reaction "<<reactype<<endl;
    //cout<<"recoP "<<Pmureco<<"    recoCTH "<<CTHmureco<<endl;
    //cout<<"recoP "<<Pmureco<<"  trueP "<<Pmutrue<<"    recoCTH "<<CTHmureco<<"  trueCTH "<<CTHmutrue<<endl;
    //cout<<"BIN "<<binn<<endl<<endl;
    return binn;
}


// initEventMap
void XsecParameters::InitEventMap(std::vector<AnaSample*> &sample)
{
    if(m_bins.empty())
    {
        cout<<"Need to build map of response functions for "<<m_name<<" ... exiting ..."<<endl;
        exit(-1);
    }
    m_evmap.clear();
    
    //loop over events to build index map
    for(size_t s=0;s<sample.size();s++)
    {
        vector<int> row;
        for(int i=0;i<sample[s]->GetN();i++)
        {
            AnaEvent *ev = sample[s]->GetEvent(i);
            //skip reactions not prepared in response function
            //HACK HERE
            int code = PASSEVENT;
            //if(ev->GetReaction() < 9){
            if(ev->GetReaction() == 0 || ev->GetReaction()>4){
            //if(ev->GetReaction() != 2){
                row.push_back(code);
                continue;
            }
            //get event info
            /*int binn = GetBinIndex(static_cast<SampleTypes>(ev->GetSampleType()),
                                   static_cast<ReactionTypes>(ev->GetReaction()),
                                   ev->GetRecPtrk(),ev->GetTruePtrk(),ev->GetRecCThtrk(),ev->GetTrueCThtrk());*/
            //insert hear to HACK reaction index
            //in baseTree.hh, reaction is from 0 -to 8
            //here is combined nc,numubar, nue into 4 and ingrid-wall into 5
            int fakeIDforResponseFunction =0;
            if (ev->GetReaction()<5) {
                fakeIDforResponseFunction = ev->GetReaction()-1;
            }
            //else if (ev->GetReaction()==4 || ev->GetReaction()==5 || ev->GetReaction()==6)fakeIDforResponseFunction = 3;
            //else if (ev->GetReaction()==7 || ev->GetReaction()==8) fakeIDforResponseFunction = 4;
            int binn = GetBinIndex(static_cast<SampleTypes>(ev->GetSampleType()),
                                   //static_cast<ReactionTypes>(ev->GetReaction()),
                                   static_cast<ReactionTypes>(fakeIDforResponseFunction),
                                   ev->GetRecPtrk(),ev->GetRecCThtrk());
            if(binn == BADBIN)
            {
                cout<<"WARNING: "<<m_name<<" event "
                <<" fall outside bin ranges"<<endl;
                cout<<"        This event will be ignored in analysis."
                <<endl;
                ev->Print();
            }
            row.push_back(binn);
        }//event loop
        m_evmap.push_back(row);
    }//sample loop
}


// EventWeghts
void XsecParameters::EventWeights(std::vector<AnaSample*> &sample,
                                  std::vector<double> &params)
{
    
    for(size_t s=0;s<sample.size();s++)
    {
        for(int i=0;i<sample[s]->GetN();i++)
        {
            AnaEvent *ev = sample[s]->GetEvent(i);
            //HACK HERE, reweight if background event only
            ReWeight(ev, s, i, params);
            //if (ev->GetReaction()>0) ReWeight(ev, s, i, params);
        }
    }
}

// ReWeight
void XsecParameters::ReWeight(AnaEvent *event, int nsample, int nevent,
                              std::vector<double> &params)
{
    if(m_evmap.empty()) //need to build an event map first
    {
        cout<<"Need to build event map index for "<<m_name<<endl;
        return;
    }
    
    int binn = m_evmap[nsample][nevent];
    
    if(binn == PASSEVENT) return;
    if(binn == BADBIN)
    event->AddEvWght(0.0); //skip!!!!
    else
    {
        vector <TGraph*> respfuncs = m_bins[binn].respfuncs;
        double weight=1;
        if(respfuncs.size()>0){ //needed because there are missing reponse functions when reco very different from true (to save memory)
            for(uint i=0; i<Npar; i++){
                //TODO: changing option to include TSpline3
                weight = weight*(respfuncs[i]->Eval(params[i],0,"S"));
                /*if(weight!=1)
                cout<<"reweighting using weight "<<weight<<"  from bin "<<binn<<endl;*/
            }
        }
        event->AddEvWght(weight);
    }
}


