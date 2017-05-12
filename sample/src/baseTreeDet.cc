#define baseTreeDet_cxx
#include "baseTreeDet.hh"
#include "Setting.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <string>
#include <iostream>
#include <TMath.h>
#include <TGraph.h>
using namespace std;
void baseTreeDet::MakeHitEfficiencySyst(TObjArray* paFile, TObjArray* paHitEffFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges){
    cout<<"Generate MPPC noise systematics"<<endl;
    static const Int_t NFILE = paFile->GetEntriesFast();
    cout<<"NUmber of FILE "<<NFILE<<endl;
    if (NFILE!=paHitEffFile ->GetEntriesFast()) {
        cout<<"MISMATCHING FILE NUMBER "<<endl;
    }
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
    ////output
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NSAMPLE = 4;
    //init histogram
    TH1F *hbinccqe[NSAMPLE][NFILE];
    TH1F *hbinccqe_sig[NSAMPLE][NFILE];
    TH1F *hbinccqe_bkg[NSAMPLE][NFILE];
    TH1F *hhiteff[NFILE];
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (int ifile=0; ifile < NFILE; ++ifile) {
            hbinccqe[isam][ifile] = new TH1F(Form("hbinccqe_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
            hbinccqe_sig[isam][ifile] = new TH1F(Form("hbinccqe_sig_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
            hbinccqe_bkg[isam][ifile] = new TH1F(Form("hbinccqe_bkg_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
        }
    }
    for (int ifile=0; ifile < NFILE; ++ifile) {
        hhiteff[ifile] = new TH1F(Form("hhiteff_file%d",ifile),"",2,0,2);
    }
    
    //fill histogram
    TFile *pithFile;
    TTree *pithTree;
    double pmu_rec;
    double cth_rec;
    Long64_t nentries;
    Long64_t iprintProcess;
    Long64_t nbytes = 0, nb = 0;
    Float_t totweight = 1;
    Float_t totReweight;
    for (int ifile=0; ifile<NFILE; ifile++) {
        cout<<"Processing file "<<(ifile+1)<<"/"<<NFILE<<endl;
        pithFile = (TFile*)(*paFile)[ifile];
        pithTree = (TTree*) pithFile->Get(treeName);
        Init(pithTree);
        
        nentries = fChain->GetEntriesFast();
        iprintProcess = Long64_t(nentries/100.);
        cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
        for (Long64_t jentry=0; jentry<nentries;jentry++) {
            if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            
            for (int isam=0; isam<NSAMPLE; ++isam) {
                if (CutSamplebyID(ientry,isam)<0) continue;
                pmu_rec = range*0.0114127 + 0.230608;
                cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
                totReweight = totweight*norm*totcrsne*2.8647e-13;
                for(int j=0; j<nccqebins; j++){
                    if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                       (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                        hbinccqe[isam][ifile]->Fill(j+0.5,totReweight);
                        if(inttype==16) hbinccqe_sig[isam][ifile]->Fill(j+0.5,totReweight);
                        if(inttype!=16) hbinccqe_bkg[isam][ifile]->Fill(j+0.5,totReweight);
                        break;
                    }
                }
                
            }//end isam
        }//end jentry
        
        //projecting the hit efficiency
        pithFile = (TFile*)(*paHitEffFile)[ifile];
        pithTree = (TTree*) pithFile->Get(treeName);
        pithTree -> Project( Form("hhiteff_file%d",ifile), "hit_miss" , "norm*totcrsne" );
        
    }//end ifile
    
    TGraph *pgrccqe[NSAMPLE][20];
    TGraph *pgrccqe_sig[NSAMPLE][20];
    TGraph *pgrccqe_bkg[NSAMPLE][20]; 
    double nevtbyBin[5];
    double nevtbyBin_sig[5];
    double nevtbyBin_bkg[5];
    double xsigma[5];//={0,..15};
    for (int ifile=0; ifile<NFILE; ++ifile) {
        //xsigma[ifile] = ifile+2;//pe 2,..6
        xsigma[ifile] = hhiteff[ifile]->GetMean();
    }
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<nccqebins; ibin++) {
            for (Int_t ivari=0; ivari<NFILE; ++ivari) {
                nevtbyBin[ivari] = hbinccqe[isam][ivari]->GetBinContent(ibin+1);
                if (hbinccqe[isam][0]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin[ivari] /= hbinccqe[isam][0]->GetBinContent(ibin+1);
                }
                //else nevtbyBin[ivari] = 0;
                //HACK HERE
                else{
                    cout<<"WARNING ZERO BIN"<<endl;
                    nevtbyBin[ivari] = 1.0;
                }

               //SIGNAL
               nevtbyBin_sig[ivari] = hbinccqe_sig[isam][ivari]->GetBinContent(ibin+1);
                if (hbinccqe_sig[isam][0]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin_sig[ivari] /= hbinccqe_sig[isam][0]->GetBinContent(ibin+1);
                }
                //else nevtbyBin[ivari] = 0;
                //HACK HERE
                else{
                    cout<<"WARNING ZERO BIN"<<endl;
                    nevtbyBin_sig[ivari] = 1.0;
                }
                
                //BACKGROUND
    		nevtbyBin_bkg[ivari] = hbinccqe_bkg[isam][ivari]->GetBinContent(ibin+1);
    		if (hbinccqe_bkg[isam][0]->GetBinContent(ibin+1)!=0) {
        		nevtbyBin_bkg[ivari] /= hbinccqe_bkg[isam][0]->GetBinContent(ibin+1);
    		}
    		//else nevtbyBin[ivari] = 0;
    		//HACK HERE
    		else{
        		cout<<"WARNING ZERO BIN"<<endl;
        		nevtbyBin_bkg[ivari] = 1.0;
   		 }
                
            }
            pgrccqe[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin);
            pgrccqe[isam][ibin] ->Write(Form("response_hiteff_sample%d_bin%d",isam,ibin));
            
     	    pgrccqe_sig[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin_sig);
            pgrccqe_sig[isam][ibin] ->Write(Form("response_hiteff_sig_sample%d_bin%d",isam,ibin));
          
            pgrccqe_bkg[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin_bkg);
            pgrccqe_bkg[isam][ibin] ->Write(Form("response_hiteff_bkg_sample%d_bin%d",isam,ibin));
        }
    }
    
    popfile->Write();
    popfile->Close();
}
void baseTreeDet::MakeMPPCNoiseSyt(TObjArray* paFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges){
    cout<<"Generate MPPC noise systematics"<<endl;
    static const Int_t NFILE = paFile->GetEntriesFast();
    cout<<"NUmber of FILE "<<NFILE<<endl;
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
    ////output
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NSAMPLE = 4;
    //init histogram
    TH1F *hbinccqe[NSAMPLE][NFILE];
    TH1F *hbinccqe_sig[NSAMPLE][NFILE];
    TH1F *hbinccqe_bkg[NSAMPLE][NFILE];
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (int ifile=0; ifile < NFILE; ++ifile) {
            hbinccqe[isam][ifile] = new TH1F(Form("hbinccqe_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
            hbinccqe_sig[isam][ifile] = new TH1F(Form("hbinccqe_sig_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
            hbinccqe_bkg[isam][ifile] = new TH1F(Form("hbinccqe_bkg_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
        }
    }
    //fill histogram
    TFile *pithFile;
    TTree *pithTree;
    double pmu_rec;
    double cth_rec;
    Long64_t nentries;
    Long64_t iprintProcess;
    Long64_t nbytes = 0, nb = 0;
    Float_t totweight = 1;
    Float_t totReweight;
    for (int ifile=0; ifile<NFILE; ifile++) {
        cout<<"Processing file "<<(ifile+1)<<"/"<<NFILE<<endl;
        pithFile = (TFile*)(*paFile)[ifile];
        pithTree = (TTree*) pithFile->Get(treeName);
        Init(pithTree);
        
        nentries = fChain->GetEntriesFast();
        iprintProcess = Long64_t(nentries/100.);
        cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
        for (Long64_t jentry=0; jentry<nentries;jentry++) {
            if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            
            for (int isam=0; isam<NSAMPLE; ++isam) {
                if (CutSamplebyID(ientry,isam)<0) continue;
                pmu_rec = range*0.0114127 + 0.230608;
                cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
                totReweight = totweight*norm*totcrsne*2.8647e-13;
                for(int j=0; j<nccqebins; j++){
                    if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                       (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                        hbinccqe[isam][ifile]->Fill(j+0.5,totReweight);
			if(inttype==16)hbinccqe_sig[isam][ifile]->Fill(j+0.5,totReweight);
			if(inttype!=16)hbinccqe_bkg[isam][ifile]->Fill(j+0.5,totReweight);
                        break;
                    }
                }
                
            }//end isam
        }//end jentry
    }//end ifile
    
    TGraph *pgrccqe[NSAMPLE][20];
   TGraph *pgrccqe_sig[NSAMPLE][20];
    TGraph *pgrccqe_bkg[NSAMPLE][20]; 
    double nevtbyBin[16];
    double nevtbyBin_sig[16];
    double nevtbyBin_bkg[16];
    double xsigma[16];//={0,..15};
    for (int ifile=0; ifile<NFILE; ++ifile) {
        xsigma[ifile] = ifile;
    }
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<nccqebins; ibin++) {
            for (Int_t ivari=0; ivari<NFILE; ++ivari) {
                nevtbyBin[ivari] = hbinccqe[isam][ivari]->GetBinContent(ibin+1);
                if (hbinccqe[isam][11]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin[ivari] /= hbinccqe[isam][11]->GetBinContent(ibin+1);
                }
                //else nevtbyBin[ivari] = 0;
                //HACK HERE
                else{
                    cout<<"WARNING ZERO BIN"<<endl;
                    nevtbyBin[ivari] = 1.0;
                }

		//signal
		nevtbyBin_sig[ivari] = hbinccqe_sig[isam][ivari]->GetBinContent(ibin+1);
                if (hbinccqe_sig[isam][11]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin_sig[ivari] /= hbinccqe_sig[isam][11]->GetBinContent(ibin+1);
                }
                //else nevtbyBin[ivari] = 0;
                //HACK HERE
                else{
                    cout<<"WARNING ZERO BIN"<<endl;
                    nevtbyBin_sig[ivari] = 1.0;
                }
               //background
		nevtbyBin_bkg[ivari] = hbinccqe_bkg[isam][ivari]->GetBinContent(ibin+1);
                if (hbinccqe_bkg[isam][11]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin_bkg[ivari] /= hbinccqe_bkg[isam][11]->GetBinContent(ibin+1);
                }
                //else nevtbyBin[ivari] = 0;
                //HACK HERE
                else{
                    cout<<"WARNING ZERO BIN"<<endl;
                    nevtbyBin_bkg[ivari] = 1.0;
                }
 
            }
            pgrccqe[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin);
            pgrccqe[isam][ibin] ->Write(Form("response_noise_sample%d_bin%d",isam,ibin));
           
	    pgrccqe_sig[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin_sig);
            pgrccqe_sig[isam][ibin] ->Write(Form("response_noise_sig_sample%d_bin%d",isam,ibin));

	    pgrccqe_bkg[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin_bkg);
            pgrccqe_bkg[isam][ibin] ->Write(Form("response_noise_bkg_sample%d_bin%d",isam,ibin)); 
        }
    }
    
    popfile->Write();
    popfile->Close();
    
    
}
void baseTreeDet::MakeResponseFunctionReco(TObjArray* paFile, TObjArray* paFiledata, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges)
{
    cout<<"Making response function"<<endl;
    static const Int_t NFILE = paFile->GetEntriesFast();
    cout<<"NUmber of FILE "<<NFILE<<endl;
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
    ////output
    TFile *popfile = new TFile(opFile,"RECREATE");
    const Int_t NSAMPLE = 4;
    //init histogram
    TH1F *hbinccqe[NSAMPLE][NFILE];
    TH1F *hdatabinccqe[NSAMPLE][NFILE];
    
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (int ifile=0; ifile < NFILE; ++ifile) {
            hbinccqe[isam][ifile] = new TH1F(Form("hbinccqe_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
            hdatabinccqe[isam][ifile] = new TH1F(Form("hdatabinccqe_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
        }
    }
    //fill histogram
    TFile *pithFile;
    TTree *pithTree;
    double pmu_rec;
    double cth_rec;
    Long64_t nentries;
    Long64_t iprintProcess;
    Long64_t nbytes = 0, nb = 0;
    Float_t totweight = 1;
    Float_t totReweight;
    for (int ifile=0; ifile<NFILE; ifile++) {
        cout<<"Processing file "<<(ifile+1)<<"/"<<NFILE<<endl;
        pithFile = (TFile*)(*paFile)[ifile];
        pithTree = (TTree*) pithFile->Get(treeName);
        Init(pithTree);
        
        nentries = fChain->GetEntriesFast();
        iprintProcess = Long64_t(nentries/100.);
        cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
        for (Long64_t jentry=0; jentry<nentries;jentry++) {
            if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            
            for (int isam=0; isam<NSAMPLE; ++isam) {
                if (CutSamplebyID(ientry,isam)<0) continue;
                pmu_rec = range*0.0114127 + 0.230608;
                cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
                totReweight = totweight*norm*totcrsne* 2.8647e-13;
                for(int j=0; j<nccqebins; j++){
                    if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                       (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                        hbinccqe[isam][ifile]->Fill(j+0.5,totReweight);
                        break;
                    }
                }
                
            }//end isam
        }//end jentry
        
        //fill for corresponding data
        cout<<"Processing data file "<<(ifile+1)<<"/"<<NFILE<<endl;
        pithFile = (TFile*)(*paFiledata)[ifile];
        pithTree = (TTree*) pithFile->Get(treeName);
        Init(pithTree);
        
        nentries = fChain->GetEntriesFast();
        iprintProcess = Long64_t(nentries/100.);
        cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
        for (Long64_t jentry=0; jentry<nentries;jentry++) {
            if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            
            for (int isam=0; isam<NSAMPLE; ++isam) {
                if (CutSamplebyID(ientry,isam)<0) continue;
                pmu_rec = range*0.0114127 + 0.230608;
                cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
                totReweight = totweight;
                for(int j=0; j<nccqebins; j++){
                    if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                       (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                        hdatabinccqe[isam][ifile]->Fill(j+0.5,totReweight);
                        break;
                    }
                }
                
            }//end isam
        }//end jentry
    }//end ifile
    //vertex xy
    TGraph *pgrccqe_vertxy[NSAMPLE][20];
    double nevtbyBin_vertxy[3];
    double xsigma_vertxy[3]={150,175,200};
    
    //vertex z
    TGraph *pgrccqe_vertz[NSAMPLE][20];
    double nevtbyBin_vertz[3];
    double xsigma_vertz[3]={2,3,4};
    
    //3D matching
    TGraph *pgrccqe_3dmatch[NSAMPLE][20];
    double nevtbyBin_3dmatch[3];
    double xsigma_3dmatch[3]={3,4,5};
    
    //INGRID matching position
    TGraph *pgrccqe_INmatchpos[NSAMPLE][20];
    double nevtbyBin_INmatchpos[3];
    double xsigma_INmatchpos[3]={75,85,95};
    
    //INGRID matching angle
    TGraph *pgrccqe_INmatchang[NSAMPLE][20];
    double nevtbyBin_INmatchang[3];
    double xsigma_INmatchang[3]={30,35,40};
    ///////////////////For data
    //vertex xy
    TGraph *pgrccqedata_vertxy[NSAMPLE][20];
    double nevtbyBindata_vertxy[3];
    
    //vertex z
    TGraph *pgrccqedata_vertz[NSAMPLE][20];
    double nevtbyBindata_vertz[3];
    
    //3D matching
    TGraph *pgrccqedata_3dmatch[NSAMPLE][20];
    double nevtbyBindata_3dmatch[3];
    
    //INGRID matching position
    TGraph *pgrccqedata_INmatchpos[NSAMPLE][20];
    double nevtbyBindata_INmatchpos[3];
    
    //INGRID matching angle
    TGraph *pgrccqedata_INmatchang[NSAMPLE][20];
    double nevtbyBindata_INmatchang[3];
    
    ///////////////////For sub data-MC
    //vertex xy
    TGraph *pgrccqesub_vertxy[NSAMPLE][20];
    double nevtbyBinsub_vertxy[3];
    
    //vertex z
    TGraph *pgrccqesub_vertz[NSAMPLE][20];
    double nevtbyBinsub_vertz[3];
    
    //3D matching
    TGraph *pgrccqesub_3dmatch[NSAMPLE][20];
    double nevtbyBinsub_3dmatch[3];
    
    //INGRID matching position
    TGraph *pgrccqesub_INmatchpos[NSAMPLE][20];
    double nevtbyBinsub_INmatchpos[3];
    
    //INGRID matching angle
    TGraph *pgrccqesub_INmatchang[NSAMPLE][20];
    double nevtbyBinsub_INmatchang[3];
    
   
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<nccqebins; ibin++) {
            //vertex xy
            nevtbyBin_vertxy[0] = hbinccqe[isam][4]->GetBinContent(ibin+1);
            nevtbyBin_vertxy[1] = hbinccqe[isam][5]->GetBinContent(ibin+1);
            nevtbyBin_vertxy[2] = hbinccqe[isam][6]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_vertxy[0]!=0) {
                    nevtbyBin_vertxy[isub] /= hbinccqe[isam][4]->GetBinContent(ibin+1);
                }
                else nevtbyBin_vertxy[isub] = 1;
            }
            
            
            
            //vertex z
            nevtbyBin_vertz[0] = hbinccqe[isam][2]->GetBinContent(ibin+1);
            nevtbyBin_vertz[1] = hbinccqe[isam][3]->GetBinContent(ibin+1);
            nevtbyBin_vertz[2] = hbinccqe[isam][4]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_vertz[0]!=0) {
                    nevtbyBin_vertz[isub] /= hbinccqe[isam][2]->GetBinContent(ibin+1);;
                }
                else nevtbyBin_vertz[isub] = 1;
            }
            
            
            //3dmatching
            nevtbyBin_3dmatch[0] = hbinccqe[isam][3]->GetBinContent(ibin+1);
            nevtbyBin_3dmatch[1] = hbinccqe[isam][4]->GetBinContent(ibin+1);
            nevtbyBin_3dmatch[2] = hbinccqe[isam][9]->GetBinContent(ibin+1);
            cout <<"TESTING "<< nevtbyBin_3dmatch[0]<<" vs "<<nevtbyBin_3dmatch[1]<<" vs "<<nevtbyBin_3dmatch[2]<<endl;
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_3dmatch[0]!=0) {
                    nevtbyBin_3dmatch[isub] /= hbinccqe[isam][3]->GetBinContent(ibin+1);
                }
                else nevtbyBin_3dmatch[isub] = 1;
            }
            
            
            //INGRID match position
            nevtbyBin_INmatchpos[0] = hbinccqe[isam][1]->GetBinContent(ibin+1);
            nevtbyBin_INmatchpos[1] = hbinccqe[isam][4]->GetBinContent(ibin+1);
            nevtbyBin_INmatchpos[2] = hbinccqe[isam][10]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_INmatchpos[0]!=0) {
                    nevtbyBin_INmatchpos[isub] /= hbinccqe[isam][1]->GetBinContent(ibin+1);
                }
                else nevtbyBin_INmatchpos[isub] = 1;
            }
            
            
            //INGRID match angle
            nevtbyBin_INmatchang[0] = hbinccqe[isam][0]->GetBinContent(ibin+1);
            nevtbyBin_INmatchang[1] = hbinccqe[isam][4]->GetBinContent(ibin+1);
            nevtbyBin_INmatchang[2] = hbinccqe[isam][11]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_INmatchang[0]!=0) {
                    nevtbyBin_INmatchang[isub] /= hbinccqe[isam][0]->GetBinContent(ibin+1);
                }
                else nevtbyBin_INmatchang[isub] = 1;
            }
            
            ////////////////////For data
            //vertex xy
            nevtbyBindata_vertxy[0] = hdatabinccqe[isam][4]->GetBinContent(ibin+1);
            nevtbyBindata_vertxy[1] = hdatabinccqe[isam][5]->GetBinContent(ibin+1);
            nevtbyBindata_vertxy[2] = hdatabinccqe[isam][6]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBindata_vertxy[0]!=0) {
                    nevtbyBindata_vertxy[isub] /= hdatabinccqe[isam][4]->GetBinContent(ibin+1);
                }
                else nevtbyBindata_vertxy[isub] = 1;
            }
            
            
            
            //vertex z
            nevtbyBindata_vertz[0] = hdatabinccqe[isam][2]->GetBinContent(ibin+1);
            nevtbyBindata_vertz[1] = hdatabinccqe[isam][3]->GetBinContent(ibin+1);
            nevtbyBindata_vertz[2] = hdatabinccqe[isam][4]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBindata_vertz[0]!=0) {
                    nevtbyBindata_vertz[isub] /= hdatabinccqe[isam][2]->GetBinContent(ibin+1);
                }
                else nevtbyBindata_vertz[isub] = 1;
            }
            
            
            //3dmatching
            nevtbyBindata_3dmatch[0] = hdatabinccqe[isam][3]->GetBinContent(ibin+1);
            nevtbyBindata_3dmatch[1] = hdatabinccqe[isam][4]->GetBinContent(ibin+1);
            nevtbyBindata_3dmatch[2] = hdatabinccqe[isam][9]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBindata_3dmatch[0]!=0) {
                    nevtbyBindata_3dmatch[isub] /= hdatabinccqe[isam][3]->GetBinContent(ibin+1);
                }
                else nevtbyBindata_3dmatch[isub] = 1;
            }
            
            
            //INGRID match position
            nevtbyBindata_INmatchpos[0] = hdatabinccqe[isam][1]->GetBinContent(ibin+1);
            nevtbyBindata_INmatchpos[1] = hdatabinccqe[isam][4]->GetBinContent(ibin+1);
            nevtbyBindata_INmatchpos[2] = hdatabinccqe[isam][10]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBindata_INmatchpos[0]!=0) {
                    nevtbyBindata_INmatchpos[isub] /= hdatabinccqe[isam][1]->GetBinContent(ibin+1);
                }
                else nevtbyBindata_INmatchpos[isub] = 1;
            }
            
            
            //INGRID match angle
            nevtbyBindata_INmatchang[0] = hdatabinccqe[isam][0]->GetBinContent(ibin+1);
            nevtbyBindata_INmatchang[1] = hdatabinccqe[isam][4]->GetBinContent(ibin+1);
            nevtbyBindata_INmatchang[2] = hdatabinccqe[isam][11]->GetBinContent(ibin+1);
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBindata_INmatchang[0]!=0) {
                    nevtbyBindata_INmatchang[isub] /= hdatabinccqe[isam][0]->GetBinContent(ibin+1);
                }
                else nevtbyBindata_INmatchang[isub] = 1;
            }
            ///////////////////For subtraction
            
            for (int isub=0; isub<3; isub++) {
                nevtbyBinsub_vertxy[isub] = nevtbyBindata_vertxy[isub] - nevtbyBin_vertxy[isub];
                nevtbyBinsub_vertz[isub] = nevtbyBindata_vertz[isub] - nevtbyBin_vertz[isub];
                nevtbyBinsub_3dmatch[isub] = nevtbyBindata_3dmatch[isub] - nevtbyBin_3dmatch[isub];
                nevtbyBinsub_INmatchpos[isub] = nevtbyBindata_INmatchpos[isub] - nevtbyBin_INmatchpos[isub];
                nevtbyBinsub_INmatchang[isub] = nevtbyBindata_INmatchang[isub] - nevtbyBin_INmatchang[isub];
            }
           
            //Fill graph
            
            pgrccqe_vertxy[isam][ibin] = new TGraph(3,xsigma_vertxy,nevtbyBin_vertxy);
            pgrccqe_vertxy[isam][ibin] ->Write(Form("response_mc_vertxy_sample%d_bin%d",isam,ibin));
            pgrccqedata_vertxy[isam][ibin] = new TGraph(3,xsigma_vertxy,nevtbyBindata_vertxy);
            pgrccqedata_vertxy[isam][ibin] ->Write(Form("response_data_vertxy_sample%d_bin%d",isam,ibin));
            pgrccqesub_vertxy[isam][ibin] = new TGraph(3,xsigma_vertxy,nevtbyBinsub_vertxy);
            pgrccqesub_vertxy[isam][ibin] ->Write(Form("response_sub_vertxy_sample%d_bin%d",isam,ibin));
            
            //vertex z
            pgrccqe_vertz[isam][ibin] = new TGraph(3,xsigma_vertz,nevtbyBin_vertz);
            pgrccqe_vertz[isam][ibin] ->Write(Form("response_mc_vertz_sample%d_bin%d",isam,ibin));
            pgrccqedata_vertz[isam][ibin] = new TGraph(3,xsigma_vertz,nevtbyBindata_vertz);
            pgrccqedata_vertz[isam][ibin] ->Write(Form("response_data_vertz_sample%d_bin%d",isam,ibin));
            pgrccqesub_vertz[isam][ibin] = new TGraph(3,xsigma_vertz,nevtbyBinsub_vertz);
            pgrccqesub_vertz[isam][ibin] ->Write(Form("response_sub_vertz_sample%d_bin%d",isam,ibin));
            
            //3dtrack
            pgrccqe_3dmatch[isam][ibin] = new TGraph(3,xsigma_3dmatch,nevtbyBin_3dmatch);
            pgrccqe_3dmatch[isam][ibin] ->Write(Form("response_mc_3dmatch_sample%d_bin%d",isam,ibin));
            pgrccqedata_3dmatch[isam][ibin] = new TGraph(3,xsigma_3dmatch,nevtbyBindata_3dmatch);
            pgrccqedata_3dmatch[isam][ibin] ->Write(Form("response_data_3dmatch_sample%d_bin%d",isam,ibin));
            pgrccqesub_3dmatch[isam][ibin] = new TGraph(3,xsigma_3dmatch,nevtbyBinsub_3dmatch);
            pgrccqesub_3dmatch[isam][ibin] ->Write(Form("response_sub_3dmatch_sample%d_bin%d",isam,ibin));
            
            //INGRID match position
            pgrccqe_INmatchpos[isam][ibin] = new TGraph(3,xsigma_INmatchpos,nevtbyBin_INmatchpos);
            pgrccqe_INmatchpos[isam][ibin] ->Write(Form("response_mc_INmatchpos_sample%d_bin%d",isam,ibin));
            pgrccqedata_INmatchpos[isam][ibin] = new TGraph(3,xsigma_INmatchpos,nevtbyBindata_INmatchpos);
            pgrccqedata_INmatchpos[isam][ibin] ->Write(Form("response_data_INmatchpos_sample%d_bin%d",isam,ibin));
            pgrccqesub_INmatchpos[isam][ibin] = new TGraph(3,xsigma_INmatchpos,nevtbyBinsub_INmatchpos);
            pgrccqesub_INmatchpos[isam][ibin] ->Write(Form("response_sub_INmatchpos_sample%d_bin%d",isam,ibin));
            
            //INGRID match angle
            pgrccqe_INmatchang[isam][ibin] = new TGraph(3,xsigma_INmatchang,nevtbyBin_INmatchang);
            pgrccqe_INmatchang[isam][ibin] ->Write(Form("response_mc_INmatchang_sample%d_bin%d",isam,ibin));
            pgrccqedata_INmatchang[isam][ibin] = new TGraph(3,xsigma_INmatchang,nevtbyBindata_INmatchang);
            pgrccqedata_INmatchang[isam][ibin] ->Write(Form("response_data_INmatchang_sample%d_bin%d",isam,ibin));
            pgrccqesub_INmatchang[isam][ibin] = new TGraph(3,xsigma_INmatchang,nevtbyBinsub_INmatchang);
            pgrccqesub_INmatchang[isam][ibin] ->Write(Form("response_sub_INmatchang_sample%d_bin%d",isam,ibin));
            
        }
    }
    
    popfile->Write();
    popfile->Close();
    
    
}
void baseTreeDet::MakeResponseFunction(TObjArray* paFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges)
{
    cout<<"Making response function"<<endl;
    static const Int_t NFILE = paFile->GetEntriesFast();
    cout<<"NUmber of FILE "<<NFILE<<endl;
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
    ////output
    TFile *popfile = new TFile(opFile,"RECREATE");
     const Int_t NSAMPLE = 4;
    //init histogram
    TH1F *hbinccqe[NSAMPLE][NFILE];
    TH1F *hbinccqe_bkg[NSAMPLE][NFILE];
    TH1F *hbinccqe_sig[NSAMPLE][NFILE];
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (int ifile=0; ifile < NFILE; ++ifile) {
            hbinccqe[isam][ifile] = new TH1F(Form("hbinccqe_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
            hbinccqe_bkg[isam][ifile] = new TH1F(Form("hbinccqe_bkg_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
            hbinccqe_sig[isam][ifile] = new TH1F(Form("hbinccqe_sig_sam%d_id%d",isam,ifile),"",nccqebins,bins_ccqe);
           }
    }
    //fill histogram
    TFile *pithFile;
    TTree *pithTree;
    double pmu_rec;
    double cth_rec;
    Long64_t nentries;
    Long64_t iprintProcess;
    Long64_t nbytes = 0, nb = 0;
    Float_t totweight = 1;
    Float_t totReweight;
    for (int ifile=0; ifile<NFILE; ifile++) {
        cout<<"Processing file "<<(ifile+1)<<"/"<<NFILE<<endl;
        pithFile = (TFile*)(*paFile)[ifile];
        pithTree = (TTree*) pithFile->Get(treeName);
        Init(pithTree);
        
        nentries = fChain->GetEntriesFast();
        iprintProcess = Long64_t(nentries/100.);
        cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
        for (Long64_t jentry=0; jentry<nentries;jentry++) {
            if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            
            for (int isam=0; isam<NSAMPLE; ++isam) {
                if (CutSamplebyID(ientry,isam)<0) continue;
                pmu_rec = range*0.0114127 + 0.230608;
                cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
                totReweight = totweight*norm*totcrsne* 2.8647e-13;
                for(int j=0; j<nccqebins; j++){
                    if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                       (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                        hbinccqe[isam][ifile]->Fill(j+0.5,totReweight);
                        if(inttype==16)hbinccqe_sig[isam][ifile]->Fill(j+0.5,totReweight);
                        if(inttype!=16)hbinccqe_bkg[isam][ifile]->Fill(j+0.5,totReweight);
                        break;
                    }
                }

            }//end isam
        }//end jentry
    }//end ifile
    
    TGraph *pgrccqe[NSAMPLE][20];
    TGraph *pgrccqe_bkg[NSAMPLE][20];
    TGraph *pgrccqe_sig[NSAMPLE][20];
    
    double nevtbyBin[9];
    double nevtbyBin_bkg[9];
    double nevtbyBin_sig[9];
    double xsigma[9];//={0,1,2,3,4,5,6,7,8};
    for (int ifile=0; ifile<NFILE; ++ifile) {
        xsigma[ifile] = 2.5*(ifile-4);
    }
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<nccqebins; ibin++) {
            for (Int_t ivari=0; ivari<NFILE; ++ivari) {
                nevtbyBin[ivari] = hbinccqe[isam][ivari]->GetBinContent(ibin+1);
                if (hbinccqe[isam][4]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin[ivari] /= hbinccqe[isam][4]->GetBinContent(ibin+1);
                }
                //else nevtbyBin[ivari] = 0;
                //HACK HERE
                else nevtbyBin[ivari] = 1.0;
                //BACKGROUND
                nevtbyBin_bkg[ivari] = hbinccqe_bkg[isam][ivari]->GetBinContent(ibin+1);
                if (hbinccqe_bkg[isam][4]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin_bkg[ivari] /= hbinccqe_bkg[isam][4]->GetBinContent(ibin+1);
                }
                //else nevtbyBin[ivari] = 0;
                //HACK HERE
                else nevtbyBin_bkg[ivari] = 1.0;
                //SIGNAL
                nevtbyBin_sig[ivari] = hbinccqe_sig[isam][ivari]->GetBinContent(ibin+1);
    		if (hbinccqe_sig[isam][4]->GetBinContent(ibin+1)!=0) {
        		nevtbyBin_sig[ivari] /= hbinccqe_sig[isam][4]->GetBinContent(ibin+1);
   		 }
    		//else nevtbyBin[ivari] = 0;
    		//HACK HERE
    		else nevtbyBin_sig[ivari] = 1.0;
            }
            pgrccqe[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin);
            pgrccqe[isam][ibin] ->Write(Form("response_sample%d_bin%d",isam,ibin));
            
            pgrccqe_bkg[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin_bkg);
            pgrccqe_bkg[isam][ibin] ->Write(Form("response_bkg_sample%d_bin%d",isam,ibin));
          
            pgrccqe_sig[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin_sig);
	    pgrccqe_sig[isam][ibin] ->Write(Form("response_sig_sample%d_bin%d",isam,ibin));
        }
    }
    
    popfile->Write();
    popfile->Close();
    
    
}
//this function is to use for both birk and PE variation systematics

void baseTreeDet::MakeSingleHisto(TString ipFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges, Int_t veractShift)
    {
        cout<<"Making response function"<<endl;
        
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
        ////output
        TFile *popfile = new TFile(opFile,"RECREATE");
        const Int_t NSAMPLE = 4;
        //init histogram
        TH1F *hbinccqe[NSAMPLE];
        TH1F *hbinccqe_bkg[NSAMPLE];
        TH1F *hbinccqe_sig[NSAMPLE];
        for (int isam=0; isam<NSAMPLE; ++isam) {
            hbinccqe[isam] = new TH1F(Form("hbinccqe_sam%d",isam),"",nccqebins,bins_ccqe);
            hbinccqe_bkg[isam] = new TH1F(Form("hbinccqe_bkg_sam%d",isam),"",nccqebins,bins_ccqe);
            hbinccqe_sig[isam] = new TH1F(Form("hbinccqe_sig_sam%d",isam),"",nccqebins,bins_ccqe);
        }
        //fill histogram
        TFile *pithFile = new TFile(ipFile);
        TTree *pithTree = (TTree*) pithFile->Get(treeName);
        Init(pithTree);
        
        double pmu_rec;
        double cth_rec;
        Long64_t nentries;
        Long64_t iprintProcess;
        Long64_t nbytes = 0, nb = 0;
        Float_t totweight = 1;
        Float_t totReweight;
        
        
        
        nentries = fChain->GetEntriesFast();
        iprintProcess = Long64_t(nentries/100.);
        cout<<"Number of entries "<<nentries<<" nprint "<<iprintProcess<<endl;
        for (Long64_t jentry=0; jentry<nentries;jentry++) {
            if (jentry%iprintProcess == 0) cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<endl;
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            if(fileIndex!=1) continue;//using numu sample only
            if(veractShift==1 && fileIndex==1) veract *= 1.027;//vertex activity shift 
            if(veractShift==-1 && fileIndex==1) veract *= 0.973; 
            for (int isam=0; isam<NSAMPLE; ++isam) {
                if (CutSamplebyID(ientry,isam)<0) continue;
                pmu_rec = range*0.0114127 + 0.230608;
                cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
                totReweight = totweight*norm*totcrsne* 2.8647e-13;
                for(int j=0; j<nccqebins; j++){
                    if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                       (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                        hbinccqe[isam]->Fill(j+0.5,totReweight);
                        if(inttype==16)hbinccqe_sig[isam]->Fill(j+0.5,totReweight);
                        if(inttype!=16)hbinccqe_bkg[isam]->Fill(j+0.5,totReweight);
                        break;
                    }
                }
                
            }//end isam
        }//end jentry
        
        
        popfile->Write();
        popfile->Close();
        
        
    }

void baseTreeDet::Loop()
{
   if (fChain == 0) return;

   Long64_t nentries = fChain->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      // if (Cut(ientry) < 0) continue;
   }
}
