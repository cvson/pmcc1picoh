#define baseTreeTrueInfo_cxx
#include "baseTreeTrueInfo.hh"
#include "Setting.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>
#include <iostream>

using namespace std;

void baseTreeTrueInfo::MakeBasicHistoBySample(TString ipFile, char* treeName, TString opFile, Int_t iSample, Bool_t isGENIE)
{
    //Flux correction
    /////////////////////////////////////////////////////////////////////
    string fratio="../../data//nd34_tuned_11bv3.1_250ka.root";
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
    TTree *piptree = (TTree*)pipfile->Get(treeName);
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TString opFilename = opFile+Form("_sam%d",iSample)+".root";
    TFile *popfile = new TFile(opFilename,"RECREATE");
	const int NVARIABLES = 60;//correct pid and add pid without range
    
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall
    const int NINTERACTION = 6;
    
    TH1F* hmc[NVARIABLES][NINTERACTION];
    
    //correlation
    TH2F* hmcveractvsmuang[NINTERACTION];
    TH2F* hmcveractvspang[NINTERACTION];
    TH2F* hmcveractvsstartxpln[NINTERACTION];
    TH2F* hmcveractvsstartypln[NINTERACTION];
    
    //check PID correlation Newadd
    TH2F* hmcpidvsQsq[NINTERACTION];
    TH2F* hmcpidvsVeract[NINTERACTION];
    TH2F* hmcpidvspidres[NINTERACTION];
    TH2F* hmcpidvspidccqe[NINTERACTION];
    
   //phase space
	TH2F* hmcpthetatrue[NINTERACTION];
	TH2F* hmcqsqpiangletrue[NINTERACTION]; 
    //binining and limit
    //NEED to rebin for the last 
    Int_t NBINHIST[NVARIABLES]={10,10,90,180,200
        ,200,180,180,200,50
        ,60,100,2,2,500
        ,500,500,100,100,90
        ,90,120,120,100,120
        ,120,120,16,16,100
        ,11,100,11,200,200
        ,200,200,100,100,200,200,200
        ,200,200,200,200,200
	,200,200,200,200,200
	,200,200,200,200,180
	,200,180,200	
};
    //NED to rebin for last 13 variable
    Double_t XMIN[NVARIABLES]={0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,-60,-60,-160,-540
        ,0,0,0,0,0
        ,0,0,11,-1,-1
        ,-1,0,0,0,-1,-1,-1
        ,-1,-1,-1,-1,-1
	,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0
};
    //NED to rebin for last 13 variable
    Double_t XMAX[NVARIABLES]={10,10,90,180,500
        ,500,180,180,500,20
        ,60,10,2,2,2500
        ,2500,5000,1,1,90
        ,90,60,60,-60,-480
        ,1200,1200,16,16,100
        ,11,100,11,1,1,
        1,400,1,5,1,1,1
        ,1,1,1,1,1
	,10,10,5,5,5
        ,3,20,10,10,90
        ,20,90,20
};
    
    
    
    
    
    for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
        //for mc
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmc[ivar][iint] = new TH1F(Form("hmc_var%d_int%d",ivar,iint),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
        }
    }
    //newadd 2-dim
    for (Int_t iint=0; iint<NINTERACTION; ++iint) {
        hmcveractvsmuang[iint] = new TH2F(Form("hmcveractvsmuang_int%d",iint),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvspang[iint] = new TH2F(Form("hmcveractvspang_int%d",iint),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvsstartxpln[iint] = new TH2F(Form("hmcveractvsstartxpln_int%d",iint),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvsstartypln[iint] = new TH2F(Form("hmcveractvsstartypln_int%d",iint),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
        
        //newadd
        hmcpidvsQsq[iint] = new TH2F(Form("hmcpidvsQsq_int%d",iint),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvsVeract[iint] = new TH2F(Form("hmcpidvsVeract_int%d",iint),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvspidres[iint] = new TH2F(Form("hmcpidvspidres_int%d",iint),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvspidccqe[iint] = new TH2F(Form("hmcpidvspidccqe_int%d",iint),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
	
	hmcpthetatrue[iint] = new TH2F(Form("hmcpthetatrue_int%d", iint),"",200,0,5,90,0,90);
	hmcqsqpiangletrue[iint] = new TH2F(Form("hmcqsqpiangletrue_int%d", iint),"",100,0,1,90,0,90);
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
        
        Float_t mcWeight = (fileIndex==1)*1.0 +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/3950. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;

        Float_t totweight = norm*totcrsne*mcWeight*2.8647e-13;
        
        int intnue=nuE/NMAX*NBIN;
        if(intnue>=NBIN)intnue=NBIN-1;
        
        if (isEnergyReweightInclude) {
            totweight *=rwratio[3][intnue];
        }
        //if INGRID background
        if (fileIndex==4) totweight *= 29.16/2.8647;
        //if wall background
        if (fileIndex==3) totweight = (norm*totcrsne<0.2e18)*1.106*norm*totcrsne*mcWeight*6.9e-12/1.3;
        //TODO reweight for genie
        if (fileIndex==10) {
            totweight = 3.41e-2*NMCFILE*1e21/NPOT;//to mimic NEUT
            if (isEnergyReweightInclude) {
                totweight *=rwratio[3][intnue];
            }
        }
        //if(fileIndex==1) veract *= 1.027;//vertex activity shift
        //if(fileIndex==1) veract *= 0.973;
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
        value2fill[36] =          veract*7.6634e-2;
        value2fill[37] =          GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6;
        value2fill[38] =          GetPrec(range);
        value2fill[39] =          pidfsi;
        value2fill[40] =          pidfsi1pres;
        value2fill[41] =          pidfsiccqe;
        //newadd
        value2fill[42] =          pidfsi1prescor;
        value2fill[43] =          pidfsiccqecor;
        value2fill[44] =          pidfsinorange;
        value2fill[45] =          pidfsi1prescornorange;
        value2fill[46] =          pidfsiccqecornorange;
        
	//add true info
	value2fill[47] =          muenergy_true;
        value2fill[48] =          mumomentum_true;
        value2fill[49] =          penergy_true;
        value2fill[50] =          pmomentum_true;
        value2fill[51] =          Qsq_true;
	value2fill[52] =          xbjorken_true;
        value2fill[53] =          tmomtrans_true;
        value2fill[54] =          Erecoil_true;
        value2fill[55] =          HadInvWsq;
        value2fill[56] =          muang_true;
        value2fill[57] =          muang_diff;
        value2fill[58] =          pang_true;
        value2fill[59] =          pang_diff;
	//value2fill[47] =	  pang_t-muang_t;//newadd
        //add randomly 0,225 MeV for 25% of CCQE
        /*if (fileIndex==1) {
         if (inttype==1) {
         double randProb = 4.0*gRandom->Uniform(0,1.0);
         if(randProb>3.0) value2fill[36] += gRandom->Uniform(0,225);
         }
         }*/
        ///Add more proton energy
        ///////////////////////////////////////
        //fill histogram
        if (CutTopologybyID(ientry,iSample)>0) {//cut sample
            for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                    if ((isGENIE==false && CutInteractionbyID(ientry,iint)>0) || (isGENIE==true && CutInteractionbyIDGENIE(ientry,iint)>0)) {
                        hmc[ivar][iint]->Fill(value2fill[ivar],totweight);
                    }
                }
            }
            //newadd two dimension
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                if ( (isGENIE==false && CutInteractionbyID(ientry,iint)>0) || (isGENIE==true && CutInteractionbyIDGENIE(ientry,iint)>0)) {
                    hmcveractvsmuang[iint]->Fill(value2fill[19],value2fill[36],totweight);
                    hmcveractvspang[iint]->Fill(value2fill[20],value2fill[36],totweight);
                    hmcveractvsstartxpln[iint]->Fill(value2fill[27],value2fill[36],totweight);
                    hmcveractvsstartypln[iint]->Fill(value2fill[28],value2fill[36],totweight);
                    
                    hmcpidvsQsq[iint]->Fill(value2fill[37],value2fill[39],totweight);
                    hmcpidvsVeract[iint]->Fill(value2fill[36],value2fill[39],totweight);
                    hmcpidvspidres[iint]->Fill(value2fill[40],value2fill[39],totweight);
                    hmcpidvspidccqe[iint]->Fill(value2fill[41],value2fill[39],totweight);

			hmcpthetatrue[iint]->Fill(value2fill[48],value2fill[56],totweight);
			hmcqsqpiangletrue[iint]->Fill(value2fill[51],value2fill[58],totweight);
                }//end if
            }//end for iint
            
        }//end CutTopologybyID
        
    }//end for jentry
    popfile->Write();
    popfile->Close();
    
}




