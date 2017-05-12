#define baseTreeWeight_cxx
#include "baseTreeWeight.hh"
#include "Setting.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string>
#include <iostream>
#include <TMath.h>
#include <TGraph.h>
//#include <TSpline.h>
using namespace std;
void baseTreeWeight::MakeResponseFunctionAllElse(TString ipFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges){
    ////////////////////////////////////////////////////////////////////
    //Get Binning
    for(int i=0;i<v_pedges.size(); i++){
        cout<<v_cthedges[i].first<<"  "<<v_cthedges[i].second<<"  "<<v_pedges[i].first<<"  "<<v_pedges[i].second<<endl;
    }
    int nccqebins;
    double *bins_ccqe;
    nccqebins=v_pedges.size();
    bins_ccqe = new double[nccqebins+1];
    for (int i=0; i<=nccqebins; i++){
        bins_ccqe[i]=i;
    }
    
    ////////////////////////////////////////////////////////////////////
    ////GET the weight
    //Bool_t isEnergyReweightInclude = true;
    string fratio="../../data/nd34_tuned_11bv3.1_250ka.root";
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
    
    
    ////////////////////////////////////////////////////////////////////
    TFile *pipfile = new TFile(ipFile);
    TTree *piptree = (TTree*)pipfile->Get(treeName);
    Init(piptree);
    ////////////////////////////////////////////////////////////////////
    ////output
    TFile *popfile = new TFile(opFile,"RECREATE");
    
    if (fChain == 0) return;
    
    //this is consistent with XsecParameters
    const Int_t NSAMPLE = 4;
    
    //T2K reweight parameter
    const Int_t NPARAMETER = 25;
    
    //-3,-2,-1,0,1,2,3 sigma
    const Int_t NVARIATION = 7;
    //0: cc1pi, 1 for CCQE, 2 for CC1pion, 3 for CCother, 4 for NC & antinu, 5, wall & ingrid
    
    //TODO: include antineutrino, wall, ingrid
    //Manual INSERT at this moment
    const Int_t NINTERACTION = 6;
    
    //init histogram
    TH1F *hbinccqe[NSAMPLE][NVARIATION][NINTERACTION];
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ivari=0; ivari<NVARIATION; ++ivari) {
            for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
                hbinccqe[isam][ivari][iinttype] = new TH1F(Form("hbinccqe_sam%d_vari%d_inttype%d",isam,ivari,iinttype),"",nccqebins,bins_ccqe);
            }
        }
    }
    
    Int_t paraIndex;
    Int_t totReweight;
    double pmu_rec;
    double cth_rec;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t iprintProcess = Long64_t(nentries/100.);
    cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        //get weight
        Float_t mcWeight = 1;
        Float_t totweight = 1;
        int intnue=nuE/NMAX*NBIN;
        if (isEnergyReweightInclude) {
            totweight = norm*totcrsne*mcWeight*2.8647e-13;
            totweight *=rwratio[3][intnue];
        }
        //fill histogram
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            if (CutSamplebyID(ientry,isam)<0) continue;
            for (Int_t ivari=0; ivari<NVARIATION; ++ivari) {
                for (Int_t ipara=0; ipara<NPARAMETER; ++ipara) {
                    //ignore used parameter
                    if (ipara==0 || ipara==1 || ipara==13 || ipara==14 || ipara==16 || ipara==22 || ipara==23 || ipara==15) continue;
                    paraIndex = ipara*7+ivari;
                    if (!((reweight[paraIndex]>0&&reweight[paraIndex]<100))) {
                        continue;
                    }
                    totReweight = totweight*reweight[paraIndex];
                    for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
                        if (iinttype==5) {
                            for(int j=0; j<nccqebins; j++){
                                hbinccqe[isam][ivari][iinttype]->Fill(j+0.5,1000);//NEED TO CHANGE HERE
                            }
                        }
                        else {
                            if (CutInteractionbyIDnew(ientry,iinttype)>0) {
                                pmu_rec = range*0.0114127 + 0.230608;
                                cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
                                for(int j=0; j<nccqebins; j++){
                                    if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                                       (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                                        hbinccqe[isam][ivari][iinttype]->Fill(j+0.5,totReweight);
                                        break;
                                    }
                                }
                            }
                        }//end else
                        
                    }//end iintype
                }//end ipara
            }//en ivari
        }//end isam
        
    }//end jentry
    //INIT TGRAPH
    TGraph *pgrccqe[NSAMPLE][NINTERACTION][20];//
    //TSpline3 *pspccqe[NSAMPLE][NINTERACTION][20];
    double nevtbyBin[NVARIATION];
    double xsigma[NVARIATION]={-3,-2,-1,0,1,2,3};
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
            for (Int_t ibin=0; ibin<nccqebins; ibin++) {
                for (Int_t ivari=0; ivari<NVARIATION; ++ivari) {
                    nevtbyBin[ivari] = hbinccqe[isam][ivari][iinttype]->GetBinContent(ibin+1);
                    if (hbinccqe[isam][3][iinttype]->GetBinContent(ibin+1)!=0) {
                        nevtbyBin[ivari] /= hbinccqe[isam][3][iinttype]->GetBinContent(ibin+1);
                    }
                    //else nevtbyBin[ivari] = 0;
                    //There is no event of CCQE in CRIIA sample
                    //HACK HERE
                    else nevtbyBin[ivari] = 1.0;
                }
                pgrccqe[isam][iinttype][ibin] = new TGraph(NVARIATION,xsigma,nevtbyBin);
                pgrccqe[isam][iinttype][ibin] ->Write(Form("response_sample%d_reaction%d_bin%d",isam,iinttype,ibin));
            }
        }
    }
    
    popfile->Write();
    popfile->Close();
}

void baseTreeWeight::MakeResponseFunction(TString ipFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges, int ithParameter){
    ////////////////////////////////////////////////////////////////////
    //Get Binning
    for(int i=0;i<v_pedges.size(); i++){
        cout<<v_cthedges[i].first<<"  "<<v_cthedges[i].second<<"  "<<v_pedges[i].first<<"  "<<v_pedges[i].second<<endl;
    }
    int nccqebins;
    double *bins_ccqe;
    nccqebins=v_pedges.size();
    bins_ccqe = new double[nccqebins+1];
    for (int i=0; i<=nccqebins; i++){
        bins_ccqe[i]=i;
    }
    
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
    
    
    ////////////////////////////////////////////////////////////////////
    TFile *pipfile = new TFile(ipFile);
    TTree *piptree = (TTree*)pipfile->Get(treeName);
    Init(piptree);
    ////////////////////////////////////////////////////////////////////
    ////output
    //TString opFilename = opFile+Form("_sam%d",ithParameter)+".root";
    //TFile *popfile = new TFile(opFilename,"RECREATE");
    TFile *popfile = new TFile(opFile,"RECREATE");
    
    if (fChain == 0) return;
    
    //this is consistent with XsecParameters
    const Int_t NSAMPLE = 4;
    
    //T2K reweight parameter
    const Int_t NPARAMETER = 25;
    
    //-3,-2,-1,0,1,2,3 sigma
    const Int_t NVARIATION = 7;
    //0: cc1pi, 1 for CCQE, 2 for CC1pion, 3 for CCother, 4 for NC & antinu, 5, wall & ingrid
    
    //TODO: include antineutrino, wall, ingrid
    //Manual INSERT at this moment
    const Int_t NINTERACTION = 6;
    
    //init histogram
    TH1F *hbinccqe[NSAMPLE][NVARIATION][NINTERACTION];
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ivari=0; ivari<NVARIATION; ++ivari) {
            for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
                hbinccqe[isam][ivari][iinttype] = new TH1F(Form("hbinccqe_sam%d_vari%d_inttype%d",isam,ivari,iinttype),"",nccqebins,bins_ccqe);
            }
        }
    }
    
    Int_t paraIndex;
    Int_t totReweight;
    double pmu_rec;
    double cth_rec;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t iprintProcess = Long64_t(nentries/100.);
    cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        //get weight
        Float_t mcWeight = 1;
        Float_t totweight = 1;
        int intnue=nuE/NMAX*NBIN;
        if (isEnergyReweightInclude) {
            totweight = norm*totcrsne*mcWeight*2.8647e-13;
            totweight *=rwratio[3][intnue];
        }
        //fill histogram
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            if (CutSamplebyID(ientry,isam)<0) continue;
            for (Int_t ivari=0; ivari<NVARIATION; ++ivari) {
                paraIndex = ithParameter*7+ivari;
                if (!(reweight[paraIndex]>0&&reweight[paraIndex]<100)) {
                    continue;
                }
                totReweight = totweight*reweight[paraIndex];
                for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
                    if (iinttype==5) {
                        for(int j=0; j<nccqebins; j++){
                            hbinccqe[isam][ivari][iinttype]->Fill(j+0.5,1000);//NEED TO CHANGE HERE
                        }
                    }
                    else {
                        if (CutInteractionbyIDnew(ientry,iinttype)>0) {
                            pmu_rec = range*0.0114127 + 0.230608;
                            cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
                            for(int j=0; j<nccqebins; j++){
                                if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                                   (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                                    hbinccqe[isam][ivari][iinttype]->Fill(j+0.5,totReweight);
                                    break;
                                }
                            }
                        }
                    }//end else
                    
                }//end iintype
            }//en ivari
        }//end isam
        
    }//end jentry
    //INIT TGRAPH
    TGraph *pgrccqe[NSAMPLE][NINTERACTION][20];//
    //TSpline3 *pspccqe[NSAMPLE][NINTERACTION][20];
    double nevtbyBin[NVARIATION];
    double xsigma[NVARIATION]={-3,-2,-1,0,1,2,3};
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
            for (Int_t ibin=0; ibin<nccqebins; ibin++) {
                for (Int_t ivari=0; ivari<NVARIATION; ++ivari) {
                    nevtbyBin[ivari] = hbinccqe[isam][ivari][iinttype]->GetBinContent(ibin+1);
                    if (hbinccqe[isam][3][iinttype]->GetBinContent(ibin+1)!=0) {
                        nevtbyBin[ivari] /= hbinccqe[isam][3][iinttype]->GetBinContent(ibin+1);
                    }
                    //else nevtbyBin[ivari] = 0;
                    //There is no event of CCQE in CRIIA sample
                    //HACK HERE
                    else nevtbyBin[ivari] = 1.0;
                }
                pgrccqe[isam][iinttype][ibin] = new TGraph(NVARIATION,xsigma,nevtbyBin);
                pgrccqe[isam][iinttype][ibin] ->Write(Form("response_sample%d_reaction%d_bin%d",isam,iinttype,ibin));
            }
        }
    }
    
    popfile->Write();
    popfile->Close();
}
void baseTreeWeight::Loop(TString ipFile, char* treeName, TString opFile, Int_t iSample)
{
    
    ////////////////////////////////////////////////////////////////////
    ////GET the weight
    Bool_t isEnergyReweightInclude = true;
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
    
    
    ////////////////////////////////////////////////////////////////////
    TFile *pipfile = new TFile(ipFile);
    TTree *piptree = (TTree*)pipfile->Get(treeName);
    Init(piptree);
    ////////////////////////////////////////////////////////////////////
    ////output
    TString opFilename = opFile+Form("_sam%d",iSample)+".root";
    TFile *popfile = new TFile(opFilename,"RECREATE");
    
    if (fChain == 0) return;
    //histogram
    //13 sample: 0/all; 1/signal; 2/CR1; 3/cr23; 4/cr23isolate; 5/cr23free; 6/cr23freelow; 7/cr23freehi; 8/onetrack;9/more than 2; 10;kikawa signal region; 11/ccqe kikawa; 12/ccqe me
    const Int_t NPARAMETER = 25;
    //-3,-2,-1,0,1,2,3 sigma
    const Int_t NVARIATION = 7;
    //0: all, 1 for cc1picoh, 2 for CCQE, 3 for CC1pion, 4 for CCOther, 5, NC
    const Int_t NINTERACTION = 6;
    
    TH1F *hmuangle[NPARAMETER][NVARIATION][NINTERACTION];
    TH1F *hmurange[NPARAMETER][NVARIATION][NINTERACTION];
    TH1F *hmumomentum[NPARAMETER][NVARIATION][NINTERACTION];
    TH1F *hmuqsq[NPARAMETER][NVARIATION][NINTERACTION];
    //TODO: Binning scheme need to be optimized
    for (Int_t ipara=0; ipara<NPARAMETER; ipara++) {
        for (Int_t ivari=0; ivari<NVARIATION; ivari++) {
            for (Int_t iinttype=0; iinttype<NINTERACTION; iinttype++) {
            hmuangle[ipara][ivari][iinttype] = new TH1F(Form("hmuangle_sam%d_para%d_sigma%d_inttype%d",iSample,ipara,ivari,iinttype),"",10,0,90);
            hmurange[ipara][ivari][iinttype] = new TH1F(Form("hmurange_sam%d_para%d_sigma%d_inttype%d",iSample,ipara,ivari,iinttype),"",10,0,100);
            hmumomentum[ipara][ivari][iinttype] = new TH1F(Form("hmumomentum_sam%d_para%d_sigma%d_inttype%d",iSample,ipara,ivari,iinttype),"",10,0,2);
            hmuqsq[ipara][ivari][iinttype] = new TH1F(Form("hmuqsq_sam%d_para%d_sigma%d_inttype%d",iSample,ipara,ivari,iinttype),"",10,0,1);
       
            }
        }
    }
    
    const Double_t massProton = 0.938272046 ;
    const Double_t massMuon = 0.1056583715;
    const Double_t massNeutron = 0.939565378;
    const Double_t nuclearPotential = 0.027;
    const Double_t lighyieldConvert = 0.076634;
    
    Double_t splineMonmureco;
    Double_t splineEmureco;
    Double_t splineEreco;
    Double_t splineQsqreco;
    Int_t paraIndex;
    Int_t totReweight;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t iprintProcess = Long64_t(nentries/100.);
    cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        Float_t mcWeight = 1;
        Float_t totweight = 1;
        int intnue=nuE/NMAX*NBIN;
        if (isEnergyReweightInclude) {
            totweight = norm*totcrsne*mcWeight*2.8647e-13;
            totweight *=rwratio[3][intnue];
        }
        
        //for simple spline
        splineMonmureco = range*0.0114127 + 0.230608;
        splineEmureco = sqrt(pow(splineMonmureco,2)+pow(massMuon,2));
        splineEreco =0.5*(pow(massProton,2)-pow(massMuon,2)-pow(massNeutron-nuclearPotential,2)+2*splineEmureco*(massNeutron-nuclearPotential))/(massNeutron-nuclearPotential-splineEmureco+splineMonmureco*cos(muang_t*TMath::Pi()/180.));
        splineQsqreco = 2*splineEreco*(splineEmureco-splineMonmureco*cos(muang_t*TMath::Pi()/180.)) - pow(massMuon,2);
        if (CutbyID(ientry,iSample)>0) {
            for (Int_t ipara=0; ipara<NPARAMETER; ipara++) {
                for (Int_t ivari=0; ivari<NVARIATION; ivari++) {
                    paraIndex = ipara*7+ivari;
                    totReweight = totweight*reweight[paraIndex]*(reweight[paraIndex]>0&&reweight[paraIndex]<100);
                    for (Int_t iinttype=0; iinttype<NINTERACTION; iinttype++) {
                        if (CutInteractionbyID(ientry,iinttype)>0) {
                            hmuangle[ipara][ivari][iinttype]->Fill(muang_t,totReweight);
                            hmurange[ipara][ivari][iinttype]->Fill(range,totReweight);
                            hmumomentum[ipara][ivari][iinttype]->Fill(splineMonmureco,totReweight);
                            hmuqsq[ipara][ivari][iinttype]->Fill(splineQsqreco,totReweight);
                        }
                    }
                }//end ivari
            }//end for ipara
        }//end if CutbyID
        
        
    }//end for jentry
    popfile->Write();
    popfile->Close();
}


void baseTreeWeight::Loop(TString ipFile, char* treeName, TString opFile)
{
    
    ////////////////////////////////////////////////////////////////////
    ////GET the weight
    Bool_t isEnergyReweightInclude = true;
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
    
    
    ////////////////////////////////////////////////////////////////////
    TFile *pipfile = new TFile(ipFile);
    TTree *piptree = (TTree*)pipfile->Get(treeName);
    Init(piptree);
    ////////////////////////////////////////////////////////////////////
    ////output
    TString opFilename = opFile;
    TFile *popfile = new TFile(opFilename,"RECREATE");
    
    if (fChain == 0) return;
    //histogram
    //13 sample: 0/all; 1/signal; 2/CR1; 3/cr23; 4/cr23isolate; 5/cr23free; 6/cr23freelow; 7/cr23freehi; 8/onetrack;9/more than 2; 10;kikawa signal region; 11/ccqe kikawa; 12/ccqe me
    const Int_t NSAMPLE = 13;
    const Int_t NPARAMETER = 25;
    const Int_t NVARIATION = 7;
    
    TH1F *hmuangle[NSAMPLE][NPARAMETER][NVARIATION];
    TH1F *hmurange[NSAMPLE][NPARAMETER][NVARIATION];
    TH1F *hmumomentum[NSAMPLE][NPARAMETER][NVARIATION];
    TH1F *hmuqsq[NSAMPLE][NPARAMETER][NVARIATION];
    //TODO: Binning scheme need to be optimized
    for (Int_t isam=0; isam<NSAMPLE; isam++) {
        for (Int_t ipara=0; ipara<NPARAMETER; ipara++) {
            for (Int_t ivari=0; ivari<NVARIATION; ivari++) {
                hmuangle[isam][ipara][ivari] = new TH1F(Form("hmuangle_sam%d_para%d_sigma%d",isam,ipara,ivari),"",10,0,90);
                hmurange[isam][ipara][ivari] = new TH1F(Form("hmurange_sam%d_para%d_sigma%d",isam,ipara,ivari),"",10,0,100);
                hmumomentum[isam][ipara][ivari] = new TH1F(Form("hmumomentum_sam%d_para%d_sigma%d",isam,ipara,ivari),"",10,0,2);
                hmuqsq[isam][ipara][ivari] = new TH1F(Form("hmuqsq_sam%d_para%d_sigma%d",isam,ipara,ivari),"",10,0,1);
            }
        }
    }
    
    const Double_t massProton = 0.938272046 ;
    const Double_t massMuon = 0.1056583715;
    const Double_t massNeutron = 0.939565378;
    const Double_t nuclearPotential = 0.027;
    const Double_t lighyieldConvert = 0.076634;
    
    Double_t splineMonmureco;
    Double_t splineEmureco;
    Double_t splineEreco;
    Double_t splineQsqreco;
    Int_t paraIndex;
    Int_t totReweight;
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t iprintProcess = Long64_t(nentries/100.);
    cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        
        Float_t mcWeight = 1;
        Float_t totweight = 1;
        int intnue=nuE/NMAX*NBIN;
        if (isEnergyReweightInclude) {
            totweight = norm*totcrsne*mcWeight*2.8647e-13;
            totweight *=rwratio[3][intnue];
        }
        
        //for simple spline
        splineMonmureco = range*0.0114127 + 0.230608;
        splineEmureco = sqrt(pow(splineMonmureco,2)+pow(massMuon,2));
        splineEreco =0.5*(pow(massProton,2)-pow(massMuon,2)-pow(massNeutron-nuclearPotential,2)+2*splineEmureco*(massNeutron-nuclearPotential))/(massNeutron-nuclearPotential-splineEmureco+splineMonmureco*cos(muang_t*TMath::Pi()/180.));
        splineQsqreco = 2*splineEreco*(splineEmureco-splineMonmureco*cos(muang_t*TMath::Pi()/180.)) - pow(massMuon,2);
        for (Int_t isam=0; isam<NSAMPLE; isam++) {
            if (CutbyID(ientry,isam)>0) {
                for (Int_t ipara=0; ipara<NPARAMETER; ipara++) {
                    for (Int_t ivari=0; ivari<NVARIATION; ivari++) {
                        paraIndex = ipara*7+ivari;
                        totReweight = totweight*reweight[paraIndex]*(reweight[paraIndex]>0&&reweight[paraIndex]<100);
                        hmuangle[isam][ipara][ivari]->Fill(muang_t,totReweight);
                        hmurange[isam][ipara][ivari]->Fill(range,totReweight);
                        hmumomentum[isam][ipara][ivari]->Fill(splineMonmureco,totReweight);
                        hmuqsq[isam][ipara][ivari]->Fill(splineQsqreco,totReweight);
                    }//end ivari
                }//end for ipara
            }//end if CutbyID
            
        }//end for isam
        
    }//end for jentry
    popfile->Write();
    popfile->Close();
}
