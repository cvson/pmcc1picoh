#define baseTree_cxx
#include "baseTree.hh"
#include "Setting.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>

using namespace std;

void baseTree::MakeDataPlot(TString ipFile, TString opFile){
    //Re initialization ipFile
    /////////////////////////////////////////////////////////////////////
    TFile *pipfile = new TFile(ipFile);
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TFile *popfile = new TFile(opFile,"RECREATE");
    //binning
    string fccqebin = "../inputs/ccqebins_Dec2014.txt";
    std::vector<std::pair<double, double> > v_pedges;
    std::vector<std::pair<double, double> > v_cthedges;
    ifstream fin(fccqebin.c_str());
    assert(fin.is_open());
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        double p1, p2, cth1, cth2;
        if(!(ss>>cth1>>cth2>>p1>>p2))
        {
            cerr<<"Bad line format: "<<endl
            <<"     "<<line<<endl;
            continue;
        }
        v_pedges.push_back(make_pair(p1,p2));
        v_cthedges.push_back(make_pair(cth1,cth2));
    }
    fin.close();
    
}
void baseTree::MakeBasicHisto(TString ipFile, TString opFile)
{
    /*const float NPOT = 6.04193507503274721e20;
    const int   NMCFILE  = 3950;
    const int   NBARFILE  = 986;
    const int   NWALLFILE  = 55546;//(31085+24461);
    const int   NINGRIDFILE  = 7882;//(3941+3941);
    const int   NNUEFILE = 985;
    
    float SCALEBAR = NMCFILE/float(NBARFILE);
    float SCALEWALL = NMCFILE/float(NWALLFILE);
    float SCALEINGRID = NMCFILE/float(NINGRIDFILE);
    float SCALENUE = NMCFILE/float(NNUEFILE);
    
    bool isEnergyReweightInclude = true;*/
    //Flux correction
    /////////////////////////////////////////////////////////////////////
    string fratio="/home/t2k/cvson/gpfs/ingrid/backup/nd34_tuned_11bv3.1_250ka.root";
    TFile* fTFRatio   = new TFile(fratio.c_str());
    TH1D*  tratio[NMOD];
    TH1D*  tratio2[NMOD];
    double rwratio[NMOD][NBIN];
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
    
    //Re initialization ipFile
    /////////////////////////////////////////////////////////////////////
    TFile *pipfile = new TFile(ipFile);
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TFile *popfile = new TFile(opFile,"RECREATE");
    const int NVARIABLES = 36;//all variables
    //0 all, 1 sig, 2 cr1, 3 cr2a, 4 cr2b, 5 cr2c
    // 6 more than 2trk; 7 ccq with one track
    const int NTOPOLOGY = 8;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 11;
    TH1F* hdata[NTOPOLOGY][NVARIABLES];
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];

    //binining and limit
    //ntrk, ning, muang, pang,
    Int_t NBINHIST[NVARIABLES]={10,10,90,180,200,200,180,180,200,50,60,100,2,2,500,500,500,100,100,90,90,120,120,100,120,120,120,16,16,100,11,100,11,200,200,200};
    Double_t XMIN[NVARIABLES]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-60,-60,-160,-540,0,0,0,0,0,0,0,11,-1,-1,-1};
    Double_t XMAX[NVARIABLES]={10,10,90,180,500,500,180,180,500,20,60,10,2,2,2500,2500,5000,1,1,90,90,60,60,-60,-480,1200,1200,16,16,100,11,100,11,1,1,1};
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            //for data
            hdata[itopo][ivar] = new TH1F(Form("hdata_topo%d_var%d",itopo,ivar),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
            //for mc
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = new TH1F(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
            }
        }
    }

    
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t iprintProcess = Long64_t(nentries/100.);
    cout<<"total "<<nentries<<" iprint "<<iprintProcess<<endl;
    Long64_t nbytes = 0, nb = 0;
    
    double value2fill[NVARIABLES];
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;
        if (jentry%iprintProcess == 0) std::cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<std::endl;
        Float_t mcWeight = (fileIndex==1)*1 +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        
        Float_t totweight = norm*totcrsne*mcWeight*2.8647e-13;
        
        int intnue=nuE/NMAX*NBIN;
        if(intnue>=NBIN)intnue=NBIN-1;
        
        if (isEnergyReweightInclude) {
            totweight *=rwratio[3][intnue];
        }
        //if INGRID background
        if (fileIndex==4) totweight *= 29.16/2.8647;
        //if wall background
        if (fileIndex==3) totweight = (norm*totcrsne<0.2e18)*1.106*norm*totcrsne*6.9e-12/1.3;
        //TODO reweight for genie
        if (fileIndex==10) totweight = 3.41e-2;
        
        //Fill variable
        value2fill[0] =          Ntrack;
        value2fill[1] =          Ningtrack;
        value2fill[2] =          muang;
        value2fill[3] =          pang;
        value2fill[4] =          ppe;
        value2fill[5] =          mupe;
        value2fill[6] =          opening;
        value2fill[7] =          coplanarity;
        value2fill[8] =          norm;
        value2fill[9] =          totcrsne;
        value2fill[10] =          inttype;
        value2fill[11] =          nuE;
        value2fill[12] =          mufc;
        value2fill[13] =          pfc;
        value2fill[14] =          mupdg;
        value2fill[15] =          ppdg;
        value2fill[16] =          veract;
        value2fill[17] =          mumucl;
        value2fill[18] =          pmucl;
        value2fill[19] =          muang_t;
        value2fill[20] =          pang_t;
        value2fill[21] =          xnu;
        value2fill[22] =          ynu;
        value2fill[23] =          znu;
        value2fill[24] =          exptime;
        value2fill[25] =          startxch;
        value2fill[26] =          startych;
        value2fill[27] =          startxpln;
        value2fill[28] =          startypln;
        value2fill[29] =          range;
        value2fill[30] =          pene;
        value2fill[31] =          prange;
        value2fill[32] =          ppene;
        value2fill[33] =          pid;
        value2fill[34] =          pid1pres;
        value2fill[35] =          pidccqe;
        
        //fill histogram
        if (fileIndex==0) {
            for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
                for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                    if (CutTopologybyID(ientry,itopo)>0) {
                        hdata[itopo][ivar]->Fill(value2fill[ivar]);
                    }
                }
            }
        }
        else {
            for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
                for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                    for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                        if (CutTopologybyID(ientry,itopo)>0 && CutInteractionbyID(ientry,iint)>0) {
                            hmc[itopo][ivar][iint]->Fill(value2fill[ivar],totweight);
                        }
                    }
                }
            }
        }
    }//end for jentry
    popfile->Write();
    popfile->Close();
    
}


