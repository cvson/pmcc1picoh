#define baseTree_cxx
#include "baseTree.hh"
#include "Setting.hh"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TGraph.h>

using namespace std;
//THIS FUNCTION is NOT Work
void baseTree::GenerateDetSyst(TString ipFile, char* treeName, TString opFile, std::vector<std::pair <double,double> > v_pedges, std::vector<std::pair <double,double> > v_cthedges){
    ////////////////////////////////////////////////////////////////////
    //Get Binning
    for(int i=0;i<v_pedges.size(); i++){
        cout<<v_cthedges[i].first<<"  "<<v_cthedges[i].second<<"  "<<v_pedges[i].first<<"  "<<v_pedges[i].second<<endl;
    }
    static const int nccqebins = v_pedges.size();
    double *bins_ccqe;
    //nccqebins=v_pedges.size();
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
    //follow kikawa-scheme
    const Int_t NCUTTIMING = 3;
    const Int_t NCUTFV = 7;//4
    const Int_t NCUTVETO = 3;
    //histogram to fill
    TH1F* hdt_timing[NSAMPLE][NCUTTIMING];
    
    TH1F* hmc_fv[NSAMPLE][NCUTFV];
    TH1F* hdt_fv[NSAMPLE][NCUTFV];
    
    TH1F* hmc_veto[NSAMPLE][NCUTVETO];
    TH1F* hdt_veto[NSAMPLE][NCUTVETO];
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t iindex=0; iindex<NCUTTIMING; ++iindex) {
            hdt_timing[isam][iindex] = new TH1F(Form("hdt_timing_sam%d_index%d",isam,iindex),"",nccqebins,bins_ccqe);
        }
        for (Int_t iindex=0; iindex<NCUTFV; ++iindex) {
            hmc_fv[isam][iindex] = new TH1F(Form("hmc_fv_sam%d_index%d",isam,iindex),"",nccqebins,bins_ccqe);
            hdt_fv[isam][iindex] = new TH1F(Form("hdt_fv_sam%d_index%d",isam,iindex),"",nccqebins,bins_ccqe);
        }
        for (Int_t iindex=0; iindex<NCUTVETO; ++iindex) {
            hmc_veto[isam][iindex] = new TH1F(Form("hmc_veto_sam%d_index%d",isam,iindex),"",nccqebins,bins_ccqe);
            hdt_veto[isam][iindex] = new TH1F(Form("hdt_veto_sam%d_index%d",isam,iindex),"",nccqebins,bins_ccqe);
        }
    }
    //Fill histogram
    
    Int_t paraIndex;
    Float_t totReweight;
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
        if (fileIndex==3) totweight = (norm*totcrsne<0.2e18)*1.106*norm*totcrsne*mcWeight*6.9e-12/1.3;
        //TODO reweight for genie
        if (fileIndex==10) totweight = 3.41e-2;
        //for Data
        if (fileIndex==0) totweight = 1.0;
        
        
        //fill histogram
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            if (CutSamplebyID(ientry,isam)<0) continue;
            
            pmu_rec = range*0.0114127 + 0.230608;
            cth_rec = TMath::Cos(TMath::Pi()/180.*muang_t);
            for(int j=0; j<nccqebins; j++){
                if((pmu_rec > v_pedges[j].first) && (pmu_rec < v_pedges[j].second)  &&
                   (cth_rec > v_cthedges[j].first) && (cth_rec < v_cthedges[j].second)){
                    
                    //data
                    if (fileIndex==0) {
                        //timing
                        for (Int_t iindex=0; iindex<NCUTTIMING; ++iindex) {
                            if (CutTimingbyIndex(ientry,iindex)>0) {
                                hdt_timing[isam][iindex]->Fill(j+0.5,totweight);
                            }
                        }
                        //fv
                        for (Int_t iindex=0; iindex<NCUTFV; ++iindex) {
                            if (CutFVbyIndex(ientry,iindex)>0) {
                                hdt_fv[isam][iindex]->Fill(j+0.5,totweight);
                            }
                        }
                        
                        //veto
                        for (Int_t iindex=0; iindex<NCUTVETO; ++iindex) {
                            if (CutVetobyIndex(ientry,iindex)>0) {
                                hdt_veto[isam][iindex]->Fill(j+0.5,totweight);
                            }
                        }
                        
                    }
                    //mc
                    else {
                        //fv
                        for (Int_t iindex=0; iindex<NCUTFV; ++iindex) {
                            if (CutFVbyIndex(ientry,iindex)>0) {
                                hmc_fv[isam][iindex]->Fill(j+0.5,totweight);
                            }
                        }
                        
                        //veto
                        for (Int_t iindex=0; iindex<NCUTVETO; ++iindex) {
                            if (CutVetobyIndex(ientry,iindex)>0) {
                                hmc_veto[isam][iindex]->Fill(j+0.5,totweight);
                            }
                        }
                    }
                    
                }
            }
            
            
        }//end isam
        
    }//end jentry
    //Fill TGraph
    //timing
    TGraph *pgrccqe_timing[NSAMPLE][nccqebins];//change from 20
    double nevtbyBin_timing[3];
    double xsigma_timing[3]={0.5,1.5,2.5};
    
    //FV
    TGraph *pgrccqemc_fv[NSAMPLE][nccqebins];//change from 20
    TGraph *pgrccqedt_fv[NSAMPLE][nccqebins];
    TGraph *pgrccqesub_fv[NSAMPLE][nccqebins];
    /*double nevtbyBinmc_fv[4];
    double nevtbyBindt_fv[4];
    double nevtbyBinsub_fv[4];
    double xsigma_fv[4]={0.5,1.5,2.5,3.5};
    */
    double nevtbyBinmc_fv[7];
    double nevtbyBindt_fv[7];
    double nevtbyBinsub_fv[7];
    double xsigma_fv[7]={0.5,1.5,2.5,3.5,4.5,5.5,6.5};
    //veto
    TGraph *pgrccqemc_veto[NSAMPLE][nccqebins];//change from 20
    TGraph *pgrccqedt_veto[NSAMPLE][nccqebins];
    TGraph *pgrccqesub_veto[NSAMPLE][nccqebins];
    double nevtbyBinmc_veto[3];
    double nevtbyBindt_veto[3];
    double nevtbyBinsub_veto[3];
    double xsigma_veto[3]={0.5,1.5,2.5};
    
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<nccqebins; ibin++) {
            //timing
            for (Int_t iindex=0; iindex<NCUTTIMING; ++iindex) {
                nevtbyBin_timing[iindex] = hdt_timing[isam][iindex]->GetBinContent(ibin+1);
                if (hdt_timing[isam][iindex]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin_timing[iindex] /= hdt_timing[isam][0]->GetBinContent(ibin+1);
                }
                else nevtbyBin_timing[iindex] = 1;
            }
            pgrccqe_timing[isam][ibin] = new TGraph(NCUTTIMING,xsigma_timing,nevtbyBin_timing);
            pgrccqe_timing[isam][ibin] ->Write(Form("detresponse_timing_sam%d_bin%d",isam,ibin));
            //fv
            for (Int_t iindex=0; iindex<NCUTFV; ++iindex) {
                nevtbyBinmc_fv[iindex] = hmc_fv[isam][iindex]->GetBinContent(ibin+1);
                if (hmc_fv[isam][iindex]->GetBinContent(ibin+1)!=0) {
                    nevtbyBinmc_fv[iindex] /= hmc_fv[isam][0]->GetBinContent(ibin+1);
                }
                else nevtbyBinmc_fv[iindex] = 1;
                
                nevtbyBindt_fv[iindex] = hdt_fv[isam][iindex]->GetBinContent(ibin+1);
                if (hdt_fv[isam][iindex]->GetBinContent(ibin+1)!=0) {
                    nevtbyBindt_fv[iindex] /= hdt_fv[isam][0]->GetBinContent(ibin+1);
                }
                else nevtbyBindt_fv[iindex] = 1;
                
                nevtbyBinsub_fv[iindex] = nevtbyBindt_fv[iindex] - nevtbyBinmc_fv[iindex];
            }
            pgrccqemc_fv[isam][ibin] = new TGraph(NCUTFV,xsigma_fv,nevtbyBinmc_fv);
            pgrccqedt_fv[isam][ibin] = new TGraph(NCUTFV,xsigma_fv,nevtbyBindt_fv);
            pgrccqesub_fv[isam][ibin] = new TGraph(NCUTFV,xsigma_fv,nevtbyBinsub_fv);
            
            pgrccqemc_fv[isam][ibin] ->Write(Form("detresponse_mcfv_sam%d_bin%d",isam,ibin));
            pgrccqedt_fv[isam][ibin] ->Write(Form("detresponse_dtfv_sam%d_bin%d",isam,ibin));
            pgrccqesub_fv[isam][ibin] ->Write(Form("detresponse_subfv_sam%d_bin%d",isam,ibin));
            //veto
            for (Int_t iindex=0; iindex<NCUTVETO; ++iindex) {
                nevtbyBinmc_veto[iindex] = hmc_veto[isam][iindex]->GetBinContent(ibin+1);
                if (hmc_veto[isam][iindex]->GetBinContent(ibin+1)!=0) {
                    nevtbyBinmc_veto[iindex] /= hmc_veto[isam][0]->GetBinContent(ibin+1);
                }
                else nevtbyBinmc_veto[iindex] = 1;
                
                nevtbyBindt_veto[iindex] = hdt_veto[isam][iindex]->GetBinContent(ibin+1);
                if (hdt_veto[isam][iindex]->GetBinContent(ibin+1)!=0) {
                    nevtbyBindt_veto[iindex] /= hdt_veto[isam][0]->GetBinContent(ibin+1);
                }
                else nevtbyBindt_veto[iindex] = 1;
                
                nevtbyBinsub_veto[iindex] = nevtbyBindt_veto[iindex] - nevtbyBinmc_veto[iindex];
            }
            pgrccqemc_veto[isam][ibin] = new TGraph(NCUTVETO,xsigma_veto,nevtbyBinmc_veto);
            pgrccqedt_veto[isam][ibin] = new TGraph(NCUTVETO,xsigma_veto,nevtbyBindt_veto);
            pgrccqesub_veto[isam][ibin] = new TGraph(NCUTVETO,xsigma_veto,nevtbyBinsub_veto);
            
            pgrccqemc_veto[isam][ibin] ->Write(Form("detresponse_mcveto_sam%d_bin%d",isam,ibin));
            pgrccqedt_veto[isam][ibin] ->Write(Form("detresponse_dtveto_sam%d_bin%d",isam,ibin));
            pgrccqesub_veto[isam][ibin] ->Write(Form("detresponse_subveto_sam%d_bin%d",isam,ibin));
        }//end ibin
    }//end isam
    //Fill uncertainty
    TGraph *pUncertaintyTiming[NSAMPLE];
    TGraph *pUncertaintyFV[NSAMPLE];
    TGraph *pUncertaintyVeto[NSAMPLE];
    TGraph *pUncertaintyComb[NSAMPLE];
    double aVariationTiming[nccqebins];//change from 10
    double aVariationFV[nccqebins];
    double aVariationVeto[nccqebins];
    double aVariationAll[nccqebins];
    
    double tempMaxGraph;
    double tempMinGraph;
    double xBinValue[nccqebins];//change from 10
    for (Int_t ibin=0; ibin<nccqebins; ibin++) {
        xBinValue[ibin] = ibin+0.5;
    }
    for (int isam=0; isam<NSAMPLE; ++isam) {
        //reset
        for (Int_t ibin=0; ibin<nccqebins; ibin++) {
            aVariationAll[ibin] = 0;
        }
        
        for (Int_t ibin=0; ibin<nccqebins; ibin++) {
            //timing
            tempMaxGraph = TMath::Abs(TMath::MaxElement(NCUTTIMING,pgrccqe_timing[isam][ibin]->GetY()) - 1.0);
            tempMinGraph = TMath::Abs(TMath::MinElement(NCUTTIMING,pgrccqe_timing[isam][ibin]->GetY()) - 1.0);
            aVariationTiming[ibin] = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;
            cout<<"Timing "<<" SAM "<<isam<<" BIN "<<ibin<<" abs(MAX) "<<tempMaxGraph<<" abs(MIN) "<<tempMinGraph<<" val "<<aVariationTiming[ibin]<<endl;
            
            aVariationAll[ibin] += pow(aVariationTiming[ibin],2);
            
            //fv
            tempMaxGraph = TMath::Abs(TMath::MaxElement(NCUTFV,pgrccqesub_fv[isam][ibin]->GetY()));
            tempMinGraph = TMath::Abs(TMath::MinElement(NCUTFV,pgrccqesub_fv[isam][ibin]->GetY()));
            aVariationFV[ibin] = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;
            cout<<"FV "<<" SAM "<<isam<<" BIN "<<ibin<<" abs(MAX) "<<tempMaxGraph<<" abs(MIN) "<<tempMinGraph<<" val "<<aVariationFV[ibin]<<endl;
            aVariationAll[ibin] += pow(aVariationFV[ibin],2);
            
            //veto
            tempMaxGraph = TMath::Abs(TMath::MaxElement(NCUTVETO,pgrccqesub_veto[isam][ibin]->GetY()));
            tempMinGraph = TMath::Abs(TMath::MinElement(NCUTVETO,pgrccqesub_veto[isam][ibin]->GetY()));
            aVariationVeto[ibin] = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;
            cout<<"VETO "<<" SAM "<<isam<<" BIN "<<ibin<<" abs(MAX) "<<tempMaxGraph<<" abs(MIN) "<<tempMinGraph<<" val "<<aVariationVeto[ibin]<<endl;
            aVariationAll[ibin] += pow(aVariationVeto[ibin],2);
        }
        //change from 10
        pUncertaintyTiming[isam] = new TGraph(nccqebins,xBinValue,aVariationTiming);
        pUncertaintyTiming[isam]->Write(Form("detresponse_timing_uncertainty_sam%d",isam));
        
        pUncertaintyFV[isam] = new TGraph(nccqebins,xBinValue,aVariationFV);
        pUncertaintyFV[isam]->Write(Form("detresponse_fv_uncertainty_sam%d",isam));
        
        pUncertaintyVeto[isam] = new TGraph(nccqebins,xBinValue,aVariationVeto);
        pUncertaintyVeto[isam]->Write(Form("detresponse_veto_uncertainty_sam%d",isam));
        
        //make square root
        for (Int_t ibin=0; ibin<nccqebins; ibin++) {
            if (aVariationAll[ibin]>1.0) aVariationAll[ibin] =1;
            else aVariationAll[ibin] = TMath::Sqrt(aVariationAll[ibin]);
            cout<<" SAM "<<isam<<" bin "<<ibin<<" COMBERROR "<<aVariationAll[ibin]<<endl;
        }
        
        pUncertaintyComb[isam] = new TGraph(nccqebins,xBinValue,aVariationAll);
        pUncertaintyComb[isam]->Write(Form("detresponse_fvtimeall_uncertainty_sam%d",isam));
        
    }
    
    
    //Write output
    popfile->Write();
    popfile->Close();
    
}
void baseTree::MakeBasicHisto(TString ipFile, TString opFile)
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
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TFile *popfile = new TFile(opFile,"RECREATE");
    //const int NVARIABLES = 42;//all variables -->for datafsiana1v0
    const int NVARIABLES = 47;//correct pid and add pid without range
    //const int NVARIABLES = 48;//different btw two angle
    //0 all, 1 sig, 2 cr1, 3 cr2a, 4 cr2b, 5 cr2c
    // 6 more than 2trk; 7 ccq with one track
    const int NTOPOLOGY = 7;//for short
    //const int NTOPOLOGY = 35;//this is latest
    //const int NTOPOLOGY = 8;//21;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    TH1F* hdata[NTOPOLOGY][NVARIABLES];
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    //newadd 2-dim
    TH2F* hdtveractvsmuang[NTOPOLOGY];
    TH2F* hdtveractvspang[NTOPOLOGY];
    TH2F* hdtveractvsstartxpln[NTOPOLOGY];
     TH2F* hdtveractvsstartypln[NTOPOLOGY];

    TH2F* hmcveractvsmuang[NTOPOLOGY][NINTERACTION];
    TH2F* hmcveractvspang[NTOPOLOGY][NINTERACTION];
    TH2F* hmcveractvsstartxpln[NTOPOLOGY][NINTERACTION];
    TH2F* hmcveractvsstartypln[NTOPOLOGY][NINTERACTION];

    //check PID correlation Newadd
    TH2F* hdtpidvsQsq[NTOPOLOGY];
    TH2F* hdtpidvsVeract[NTOPOLOGY];
    TH2F* hdtpidvspidres[NTOPOLOGY];
    TH2F* hdtpidvspidccqe[NTOPOLOGY];
    
    TH2F* hmcpidvsQsq[NTOPOLOGY][NINTERACTION];
    TH2F* hmcpidvsVeract[NTOPOLOGY][NINTERACTION];
    TH2F* hmcpidvspidres[NTOPOLOGY][NINTERACTION];
    TH2F* hmcpidvspidccqe[NTOPOLOGY][NINTERACTION];


    //binining and limit
    //ntrk, ning, muang, pang,
    Int_t NBINHIST[NVARIABLES]={10,10,90,180,200
        ,200,180,180,200,50
        ,60,100,2,2,500
        ,500,500,100,100,90
        ,90,120,120,100,120
        ,120,120,16,16,100
        ,11,100,11,200,200
        ,200,200,100,100,200,200,200
        ,200,200,200,200,200/*,180*/};
    Double_t XMIN[NVARIABLES]={0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,-60,-60,-160,-540
        ,0,0,0,0,0
        ,0,0,11,-1,-1
        ,-1,0,0,0,-1,-1,-1
        ,-1,-1,-1,-1,-1/*,-90*/};
    Double_t XMAX[NVARIABLES]={10,10,90,180,500
        ,500,180,180,500,20
        ,60,10,2,2,2500
        ,2500,5000,1,1,90
        ,90,60,60,-60,-480
        ,1200,1200,16,16,100
        ,11,100,11,1,1,
        1,400,1,5,1,1,1
        ,1,1,1,1,1/*,90*/};
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        //newadd 2-dim
        hdtveractvsmuang[itopo] = new TH2F(Form("hdtveractvsmuang_topo%d",itopo),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
        hdtveractvspang[itopo] = new TH2F(Form("hdtveractvspang_topo%d",itopo),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
        hdtveractvsstartxpln[itopo] = new TH2F(Form("hdtveractvsstartxpln_topo%d",itopo),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
        hdtveractvsstartypln[itopo] = new TH2F(Form("hdtveractvsstartypln_topo%d",itopo),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
        
        //newadd
        hdtpidvsQsq[itopo] = new TH2F(Form("hdtpidvsQsq_topo%d",itopo),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
        hdtpidvsVeract[itopo] = new TH2F(Form("hdtpidvsVeract_topo%d",itopo),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
        hdtpidvspidres[itopo] = new TH2F(Form("hdtpidvspidres_topo%d",itopo),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
        hdtpidvspidccqe[itopo] = new TH2F(Form("hdtpidvspidccqe_topo%d",itopo),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
        

        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            //for data
            hdata[itopo][ivar] = new TH1F(Form("hdata_topo%d_var%d",itopo,ivar),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
            //for mc
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = new TH1F(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
            }
        }
        //newadd 2-dim
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcveractvsmuang[itopo][iint] = new TH2F(Form("hmcveractvsmuang_topo%d_int%d",itopo,iint),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
            hmcveractvspang[itopo][iint] = new TH2F(Form("hmcveractvspang_topo%d_int%d",itopo,iint),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
            hmcveractvsstartxpln[itopo][iint] = new TH2F(Form("hmcveractvsstartxpln_topo%d_int%d",itopo,iint),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
            hmcveractvsstartypln[itopo][iint] = new TH2F(Form("hmcveractvsstartypln_topo%d_int%d",itopo,iint),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
            
            //newadd
            hmcpidvsQsq[itopo][iint] = new TH2F(Form("hmcpidvsQsq_topo%d_int%d",itopo,iint),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
            hmcpidvsVeract[itopo][iint] = new TH2F(Form("hmcpidvsVeract_topo%d_int%d",itopo,iint),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
            hmcpidvspidres[itopo][iint] = new TH2F(Form("hmcpidvspidres_topo%d_int%d",itopo,iint),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
            hmcpidvspidccqe[itopo][iint] = new TH2F(Form("hmcpidvspidccqe_topo%d_int%d",itopo,iint),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
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
        //Float_t mcWeight = (fileIndex==1)*1 +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        //for birk study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/986. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        //for me birk process study
	Float_t mcWeight = (fileIndex==1)*NMCFILE/994. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;

        //for PE variation study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/1974. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
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
        if (fileIndex==0) {
            for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
                for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                    if (CutTopologybyID(ientry,itopo)>0) {
                        hdata[itopo][ivar]->Fill(value2fill[ivar]);
                    }
                }
                //newadd 2-dim
                if (CutTopologybyID(ientry,itopo)>0) {
                    hdtveractvsmuang[itopo]->Fill(value2fill[19],value2fill[36]);
                    hdtveractvspang[itopo]->Fill(value2fill[20],value2fill[36]);
                    hdtveractvsstartxpln[itopo]->Fill(value2fill[27],value2fill[36]);
                    hdtveractvsstartypln[itopo]->Fill(value2fill[28],value2fill[36]);
                    
                    hdtpidvsQsq[itopo]->Fill(value2fill[37],value2fill[39]);
                    hdtpidvsVeract[itopo]->Fill(value2fill[36],value2fill[39]);
                    hdtpidvspidres[itopo]->Fill(value2fill[40],value2fill[39]);
                    hdtpidvspidccqe[itopo]->Fill(value2fill[41],value2fill[39]);
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
                //newadd two dimension
                for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                    if (CutTopologybyID(ientry,itopo)>0 && CutInteractionbyID(ientry,iint)>0) {
                        hmcveractvsmuang[itopo][iint]->Fill(value2fill[19],value2fill[36],totweight);
                        hmcveractvspang[itopo][iint]->Fill(value2fill[20],value2fill[36],totweight);
                        hmcveractvsstartxpln[itopo][iint]->Fill(value2fill[27],value2fill[36],totweight);
                        hmcveractvsstartypln[itopo][iint]->Fill(value2fill[28],value2fill[36],totweight);
                        
                        hmcpidvsQsq[itopo][iint]->Fill(value2fill[37],value2fill[39],totweight);
                        hmcpidvsVeract[itopo][iint]->Fill(value2fill[36],value2fill[39],totweight);
                        hmcpidvspidres[itopo][iint]->Fill(value2fill[40],value2fill[39],totweight);
                        hmcpidvspidccqe[itopo][iint]->Fill(value2fill[41],value2fill[39],totweight);
                    }
                }
                
            }
        }
    }//end for jentry
    popfile->Write();
    popfile->Close();
    
}
void baseTree::MakeBasicHistoBySample(TString ipFile, TString opFile, Int_t ithtopo)
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
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TString opFilename = opFile+Form("_sam%d",ithtopo)+".root";
	TFile *popfile = new TFile(opFilename,"RECREATE");
    //const int NVARIABLES = 42;//all variables -->for datafsiana1v0
    const int NVARIABLES = 47;//correct pid and add pid without range
    //const int NVARIABLES = 48;//different btw two angle
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    TH1F* hdata[NVARIABLES];
    TH1F* hmc[NVARIABLES][NINTERACTION];
    
    //newadd 2-dim
    TH2F* hdtveractvsmuang;
    TH2F* hdtveractvspang;
    TH2F* hdtveractvsstartxpln;
    TH2F* hdtveractvsstartypln;
    
    TH2F* hmcveractvsmuang[NINTERACTION];
    TH2F* hmcveractvspang[NINTERACTION];
    TH2F* hmcveractvsstartxpln[NINTERACTION];
    TH2F* hmcveractvsstartypln[NINTERACTION];
    
    //check PID correlation Newadd
    TH2F* hdtpidvsQsq;
    TH2F* hdtpidvsVeract;
    TH2F* hdtpidvspidres;
    TH2F* hdtpidvspidccqe;
    
    TH2F* hmcpidvsQsq[NINTERACTION];
    TH2F* hmcpidvsVeract[NINTERACTION];
    TH2F* hmcpidvspidres[NINTERACTION];
    TH2F* hmcpidvspidccqe[NINTERACTION];
    
    
    //binining and limit
    //ntrk, ning, muang, pang,
    Int_t NBINHIST[NVARIABLES]={10,10,90,180,200
        ,200,180,180,200,50
        ,60,100,2,2,500
        ,500,500,100,100,90
        ,90,120,120,100,120
        ,120,120,16,16,100
        ,11,100,11,200,200
        ,200,200,100,100,200,200,200
        ,200,200,200,200,200/*,180*/};
    Double_t XMIN[NVARIABLES]={0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,-60,-60,-160,-540
        ,0,0,0,0,0
        ,0,0,11,-1,-1
        ,-1,0,0,0,-1,-1,-1
        ,-1,-1,-1,-1,-1/*,-90*/};
    Double_t XMAX[NVARIABLES]={10,10,90,180,500
        ,500,180,180,500,20
        ,60,10,2,2,2500
        ,2500,5000,1,1,90
        ,90,60,60,-60,-480
        ,1200,1200,16,16,100
        ,11,100,11,1,1,
        1,400,1,5,1,1,1
        ,1,1,1,1,1/*,90*/};

    //newadd 2-dim
        hdtveractvsmuang = new TH2F(Form("hdtveractvsmuang_topo%d",ithtopo),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
        hdtveractvspang = new TH2F(Form("hdtveractvspang_topo%d",ithtopo),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
        hdtveractvsstartxpln = new TH2F(Form("hdtveractvsstartxpln_topo%d",ithtopo),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
        hdtveractvsstartypln = new TH2F(Form("hdtveractvsstartypln_topo%d",ithtopo),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
        
        //newadd
        hdtpidvsQsq = new TH2F(Form("hdtpidvsQsq_topo%d",ithtopo),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
        hdtpidvsVeract = new TH2F(Form("hdtpidvsVeract_topo%d",ithtopo),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
        hdtpidvspidres = new TH2F(Form("hdtpidvspidres_topo%d",ithtopo),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
        hdtpidvspidccqe = new TH2F(Form("hdtpidvspidccqe_topo%d",ithtopo),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
        
        
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            //for data
            hdata[ivar] = new TH1F(Form("hdata_topo%d_var%d",ithtopo,ivar),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
            //for mc
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[ivar][iint] = new TH1F(Form("hmc_topo%d_var%d_int%d",ithtopo,ivar,iint),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
            }
        }
        //newadd 2-dim
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcveractvsmuang[iint] = new TH2F(Form("hmcveractvsmuang_topo%d_int%d",ithtopo,iint),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
            hmcveractvspang[iint] = new TH2F(Form("hmcveractvspang_topo%d_int%d",ithtopo,iint),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
            hmcveractvsstartxpln[iint] = new TH2F(Form("hmcveractvsstartxpln_topo%d_int%d",ithtopo,iint),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
            hmcveractvsstartypln[iint] = new TH2F(Form("hmcveractvsstartypln_topo%d_int%d",ithtopo,iint),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
            
            //newadd
            hmcpidvsQsq[iint] = new TH2F(Form("hmcpidvsQsq_topo%d_int%d",ithtopo,iint),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
            hmcpidvsVeract[iint] = new TH2F(Form("hmcpidvsVeract_topo%d_int%d",ithtopo,iint),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
            hmcpidvspidres[iint] = new TH2F(Form("hmcpidvspidres_topo%d_int%d",ithtopo,iint),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
            hmcpidvspidccqe[iint] = new TH2F(Form("hmcpidvspidccqe_topo%d_int%d",ithtopo,iint),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
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
        //for birk study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/986. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        //for me birk process study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/994. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        
        //for PE variation study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/1974. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
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
        if (fileIndex==0) {
            
                if (CutTopologybyID(ientry,ithtopo)>0) {
                    for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                            hdata[ivar]->Fill(value2fill[ivar]);
                    }
                    
                    hdtveractvsmuang->Fill(value2fill[19],value2fill[36]);
                    hdtveractvspang->Fill(value2fill[20],value2fill[36]);
                    hdtveractvsstartxpln->Fill(value2fill[27],value2fill[36]);
                    hdtveractvsstartypln->Fill(value2fill[28],value2fill[36]);
                    
                    hdtpidvsQsq->Fill(value2fill[37],value2fill[39]);
                    hdtpidvsVeract->Fill(value2fill[36],value2fill[39]);
                    hdtpidvspidres->Fill(value2fill[40],value2fill[39]);
                    hdtpidvspidccqe->Fill(value2fill[41],value2fill[39]);
                }
                
                
        }
        else {

                for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                    for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                        if (CutTopologybyID(ientry,ithtopo)>0 && CutInteractionbyID(ientry,iint)>0) {
                            hmc[ivar][iint]->Fill(value2fill[ivar],totweight);
                        }
                    }
                }
                //newadd two dimension
                for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                    if (CutTopologybyID(ientry,ithtopo)>0 && CutInteractionbyID(ientry,iint)>0) {
                        hmcveractvsmuang[iint]->Fill(value2fill[19],value2fill[36],totweight);
                        hmcveractvspang[iint]->Fill(value2fill[20],value2fill[36],totweight);
                        hmcveractvsstartxpln[iint]->Fill(value2fill[27],value2fill[36],totweight);
                        hmcveractvsstartypln[iint]->Fill(value2fill[28],value2fill[36],totweight);
                        
                        hmcpidvsQsq[iint]->Fill(value2fill[37],value2fill[39],totweight);
                        hmcpidvsVeract[iint]->Fill(value2fill[36],value2fill[39],totweight);
                        hmcpidvspidres[iint]->Fill(value2fill[40],value2fill[39],totweight);
                        hmcpidvspidccqe[iint]->Fill(value2fill[41],value2fill[39],totweight);
                    }
                }
                
        }
    }//end for jentry
    popfile->Write();
    popfile->Close();
    
}

void baseTree::MakeBasicHistoBySampleGENIE(TString ipFile, TString opFile, Int_t ithtopo)
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
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TString opFilename = opFile+Form("_sam%d",ithtopo)+".root";
    TFile *popfile = new TFile(opFilename,"RECREATE");
    //const int NVARIABLES = 42;//all variables -->for datafsiana1v0
    const int NVARIABLES = 47;//correct pid and add pid without range
    //const int NVARIABLES = 48;//different btw two angle
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    TH1F* hdata[NVARIABLES];
    TH1F* hmc[NVARIABLES][NINTERACTION];
    
    //newadd 2-dim
    TH2F* hdtveractvsmuang;
    TH2F* hdtveractvspang;
    TH2F* hdtveractvsstartxpln;
    TH2F* hdtveractvsstartypln;
    
    TH2F* hmcveractvsmuang[NINTERACTION];
    TH2F* hmcveractvspang[NINTERACTION];
    TH2F* hmcveractvsstartxpln[NINTERACTION];
    TH2F* hmcveractvsstartypln[NINTERACTION];
    
    //check PID correlation Newadd
    TH2F* hdtpidvsQsq;
    TH2F* hdtpidvsVeract;
    TH2F* hdtpidvspidres;
    TH2F* hdtpidvspidccqe;
    
    TH2F* hmcpidvsQsq[NINTERACTION];
    TH2F* hmcpidvsVeract[NINTERACTION];
    TH2F* hmcpidvspidres[NINTERACTION];
    TH2F* hmcpidvspidccqe[NINTERACTION];
    
    
    //binining and limit
    //ntrk, ning, muang, pang,
    Int_t NBINHIST[NVARIABLES]={10,10,90,180,200
        ,200,180,180,200,50
        ,60,100,2,2,500
        ,500,500,100,100,90
        ,90,120,120,100,120
        ,120,120,16,16,100
        ,11,100,11,200,200
        ,200,200,100,100,200,200,200
        ,200,200,200,200,200/*,180*/};
    Double_t XMIN[NVARIABLES]={0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,-60,-60,-160,-540
        ,0,0,0,0,0
        ,0,0,11,-1,-1
        ,-1,0,0,0,-1,-1,-1
        ,-1,-1,-1,-1,-1/*,-90*/};
    Double_t XMAX[NVARIABLES]={10,10,90,180,500
        ,500,180,180,500,20
        ,60,10,2,2,2500
        ,2500,5000,1,1,90
        ,90,60,60,-60,-480
        ,1200,1200,16,16,100
        ,11,100,11,1,1,
        1,400,1,5,1,1,1
        ,1,1,1,1,1/*,90*/};
    
    //newadd 2-dim
    hdtveractvsmuang = new TH2F(Form("hdtveractvsmuang_topo%d",ithtopo),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
    hdtveractvspang = new TH2F(Form("hdtveractvspang_topo%d",ithtopo),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
    hdtveractvsstartxpln = new TH2F(Form("hdtveractvsstartxpln_topo%d",ithtopo),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
    hdtveractvsstartypln = new TH2F(Form("hdtveractvsstartypln_topo%d",ithtopo),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
    
    //newadd
    hdtpidvsQsq = new TH2F(Form("hdtpidvsQsq_topo%d",ithtopo),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
    hdtpidvsVeract = new TH2F(Form("hdtpidvsVeract_topo%d",ithtopo),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
    hdtpidvspidres = new TH2F(Form("hdtpidvspidres_topo%d",ithtopo),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
    hdtpidvspidccqe = new TH2F(Form("hdtpidvspidccqe_topo%d",ithtopo),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
    
    
    for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
        //for data
        hdata[ivar] = new TH1F(Form("hdata_topo%d_var%d",ithtopo,ivar),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
        //for mc
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmc[ivar][iint] = new TH1F(Form("hmc_topo%d_var%d_int%d",ithtopo,ivar,iint),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
        }
    }
    //newadd 2-dim
    for (Int_t iint=0; iint<NINTERACTION; ++iint) {
        hmcveractvsmuang[iint] = new TH2F(Form("hmcveractvsmuang_topo%d_int%d",ithtopo,iint),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvspang[iint] = new TH2F(Form("hmcveractvspang_topo%d_int%d",ithtopo,iint),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvsstartxpln[iint] = new TH2F(Form("hmcveractvsstartxpln_topo%d_int%d",ithtopo,iint),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvsstartypln[iint] = new TH2F(Form("hmcveractvsstartypln_topo%d_int%d",ithtopo,iint),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
        
        //newadd
        hmcpidvsQsq[iint] = new TH2F(Form("hmcpidvsQsq_topo%d_int%d",ithtopo,iint),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvsVeract[iint] = new TH2F(Form("hmcpidvsVeract_topo%d_int%d",ithtopo,iint),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvspidres[iint] = new TH2F(Form("hmcpidvspidres_topo%d_int%d",ithtopo,iint),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvspidccqe[iint] = new TH2F(Form("hmcpidvspidccqe_topo%d_int%d",ithtopo,iint),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
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
        //for birk study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/986. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        //for me birk process study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/994. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        
        //for PE variation study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/1974. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
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
        if (fileIndex==0) {
            
            if (CutTopologybyID(ientry,ithtopo)>0) {
                for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                    hdata[ivar]->Fill(value2fill[ivar]);
                }
                
                hdtveractvsmuang->Fill(value2fill[19],value2fill[36]);
                hdtveractvspang->Fill(value2fill[20],value2fill[36]);
                hdtveractvsstartxpln->Fill(value2fill[27],value2fill[36]);
                hdtveractvsstartypln->Fill(value2fill[28],value2fill[36]);
                
                hdtpidvsQsq->Fill(value2fill[37],value2fill[39]);
                hdtpidvsVeract->Fill(value2fill[36],value2fill[39]);
                hdtpidvspidres->Fill(value2fill[40],value2fill[39]);
                hdtpidvspidccqe->Fill(value2fill[41],value2fill[39]);
            }
            
            
        }
        else {
            
            for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                    if (CutTopologybyID(ientry,ithtopo)>0 && CutInteractionbyIDGENIE(ientry,iint)>0) {
                        hmc[ivar][iint]->Fill(value2fill[ivar],totweight);
                    }
                }
            }
            //newadd two dimension
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                if (CutTopologybyID(ientry,ithtopo)>0 && CutInteractionbyIDGENIE(ientry,iint)>0) {
                    hmcveractvsmuang[iint]->Fill(value2fill[19],value2fill[36],totweight);
                    hmcveractvspang[iint]->Fill(value2fill[20],value2fill[36],totweight);
                    hmcveractvsstartxpln[iint]->Fill(value2fill[27],value2fill[36],totweight);
                    hmcveractvsstartypln[iint]->Fill(value2fill[28],value2fill[36],totweight);
                    
                    hmcpidvsQsq[iint]->Fill(value2fill[37],value2fill[39],totweight);
                    hmcpidvsVeract[iint]->Fill(value2fill[36],value2fill[39],totweight);
                    hmcpidvspidres[iint]->Fill(value2fill[40],value2fill[39],totweight);
                    hmcpidvspidccqe[iint]->Fill(value2fill[41],value2fill[39],totweight);
                }
            }
            
        }
    }//end for jentry
    popfile->Write();
    popfile->Close();
    
}

void baseTree::MakeBasicHistoBySamplev532(TString ipFile, TString opFile, Int_t ithtopo)
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
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TString opFilename = opFile+Form("_sam%d",ithtopo)+".root";
    TFile *popfile = new TFile(opFilename,"RECREATE");
    //const int NVARIABLES = 42;//all variables -->for datafsiana1v0
    const int NVARIABLES = 47;//correct pid and add pid without range
    //const int NVARIABLES = 48;//different btw two angle
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    TH1F* hdata[NVARIABLES];
    TH1F* hmc[NVARIABLES][NINTERACTION];
    
    //newadd 2-dim
    TH2F* hdtveractvsmuang;
    TH2F* hdtveractvspang;
    TH2F* hdtveractvsstartxpln;
    TH2F* hdtveractvsstartypln;
    
    TH2F* hmcveractvsmuang[NINTERACTION];
    TH2F* hmcveractvspang[NINTERACTION];
    TH2F* hmcveractvsstartxpln[NINTERACTION];
    TH2F* hmcveractvsstartypln[NINTERACTION];
    
    //check PID correlation Newadd
    TH2F* hdtpidvsQsq;
    TH2F* hdtpidvsVeract;
    TH2F* hdtpidvspidres;
    TH2F* hdtpidvspidccqe;
    
    TH2F* hmcpidvsQsq[NINTERACTION];
    TH2F* hmcpidvsVeract[NINTERACTION];
    TH2F* hmcpidvspidres[NINTERACTION];
    TH2F* hmcpidvspidccqe[NINTERACTION];
    
    
    //binining and limit
    //ntrk, ning, muang, pang,
    Int_t NBINHIST[NVARIABLES]={10,10,90,180,200
        ,200,180,180,200,50
        ,60,100,2,2,500
        ,500,500,100,100,90
        ,90,120,120,100,120
        ,120,120,16,16,100
        ,11,100,11,200,200
        ,200,200,100,100,200,200,200
        ,200,200,200,200,200/*,180*/};
    Double_t XMIN[NVARIABLES]={0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,-60,-60,-160,-540
        ,0,0,0,0,0
        ,0,0,11,-1,-1
        ,-1,0,0,0,-1,-1,-1
        ,-1,-1,-1,-1,-1/*,-90*/};
    Double_t XMAX[NVARIABLES]={10,10,90,180,500
        ,500,180,180,500,20
        ,60,10,2,2,2500
        ,2500,5000,1,1,90
        ,90,60,60,-60,-480
        ,1200,1200,16,16,100
        ,11,100,11,1,1,
        1,400,1,5,1,1,1
        ,1,1,1,1,1/*,90*/};
    
    //newadd 2-dim
    hdtveractvsmuang = new TH2F(Form("hdtveractvsmuang_topo%d",ithtopo),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
    hdtveractvspang = new TH2F(Form("hdtveractvspang_topo%d",ithtopo),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
    hdtveractvsstartxpln = new TH2F(Form("hdtveractvsstartxpln_topo%d",ithtopo),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
    hdtveractvsstartypln = new TH2F(Form("hdtveractvsstartypln_topo%d",ithtopo),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
    
    //newadd
    hdtpidvsQsq = new TH2F(Form("hdtpidvsQsq_topo%d",ithtopo),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
    hdtpidvsVeract = new TH2F(Form("hdtpidvsVeract_topo%d",ithtopo),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
    hdtpidvspidres = new TH2F(Form("hdtpidvspidres_topo%d",ithtopo),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
    hdtpidvspidccqe = new TH2F(Form("hdtpidvspidccqe_topo%d",ithtopo),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
    
    
    for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
        //for data
        hdata[ivar] = new TH1F(Form("hdata_topo%d_var%d",ithtopo,ivar),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
        //for mc
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmc[ivar][iint] = new TH1F(Form("hmc_topo%d_var%d_int%d",ithtopo,ivar,iint),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
        }
    }
    //newadd 2-dim
    for (Int_t iint=0; iint<NINTERACTION; ++iint) {
        hmcveractvsmuang[iint] = new TH2F(Form("hmcveractvsmuang_topo%d_int%d",ithtopo,iint),"",NBINHIST[19],XMIN[19],XMAX[19],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvspang[iint] = new TH2F(Form("hmcveractvspang_topo%d_int%d",ithtopo,iint),"",NBINHIST[20],XMIN[20],XMAX[20],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvsstartxpln[iint] = new TH2F(Form("hmcveractvsstartxpln_topo%d_int%d",ithtopo,iint),"",NBINHIST[27],XMIN[27],XMAX[27],NBINHIST[36],XMIN[36],XMAX[36]);
        hmcveractvsstartypln[iint] = new TH2F(Form("hmcveractvsstartypln_topo%d_int%d",ithtopo,iint),"",NBINHIST[28],XMIN[28],XMAX[28],NBINHIST[36],XMIN[36],XMAX[36]);
        
        //newadd
        hmcpidvsQsq[iint] = new TH2F(Form("hmcpidvsQsq_topo%d_int%d",ithtopo,iint),"",NBINHIST[37],XMIN[37],XMAX[37],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvsVeract[iint] = new TH2F(Form("hmcpidvsVeract_topo%d_int%d",ithtopo,iint),"",NBINHIST[36],XMIN[36],XMAX[36],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvspidres[iint] = new TH2F(Form("hmcpidvspidres_topo%d_int%d",ithtopo,iint),"",NBINHIST[40],XMIN[40],XMAX[40],NBINHIST[39],XMIN[39],XMAX[39]);
        hmcpidvspidccqe[iint] = new TH2F(Form("hmcpidvspidccqe_topo%d_int%d",ithtopo,iint),"",NBINHIST[41],XMIN[41],XMAX[41],NBINHIST[39],XMIN[39],XMAX[39]);
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
        //Float_t mcWeight = (fileIndex==1)*1 +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        //for birk study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/986. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        //for me birk process study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/994. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        
        //for PE variation study
        //Float_t mcWeight = (fileIndex==1)*NMCFILE/1974. +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        //NEUT 5.3.2
        Float_t mcWeight = (fileIndex==1)*NMCFILE/(3974.) +(fileIndex==2)*SCALEBAR + (fileIndex==3)*SCALEWALL + (fileIndex==4)*SCALEINGRID + (fileIndex==5)*SCALENUE;
        
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
        if (fileIndex==0) {
            
            if (CutTopologybyID(ientry,ithtopo)>0) {
                for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                    hdata[ivar]->Fill(value2fill[ivar]);
                }
                
                hdtveractvsmuang->Fill(value2fill[19],value2fill[36]);
                hdtveractvspang->Fill(value2fill[20],value2fill[36]);
                hdtveractvsstartxpln->Fill(value2fill[27],value2fill[36]);
                hdtveractvsstartypln->Fill(value2fill[28],value2fill[36]);
                
                hdtpidvsQsq->Fill(value2fill[37],value2fill[39]);
                hdtpidvsVeract->Fill(value2fill[36],value2fill[39]);
                hdtpidvspidres->Fill(value2fill[40],value2fill[39]);
                hdtpidvspidccqe->Fill(value2fill[41],value2fill[39]);
            }
            
            
        }
        else {
            
            for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                    if (CutTopologybyID(ientry,ithtopo)>0 && CutInteractionbyID(ientry,iint)>0) {
                        hmc[ivar][iint]->Fill(value2fill[ivar],totweight);
                    }
                }
            }
            //newadd two dimension
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                if (CutTopologybyID(ientry,ithtopo)>0 && CutInteractionbyID(ientry,iint)>0) {
                    hmcveractvsmuang[iint]->Fill(value2fill[19],value2fill[36],totweight);
                    hmcveractvspang[iint]->Fill(value2fill[20],value2fill[36],totweight);
                    hmcveractvsstartxpln[iint]->Fill(value2fill[27],value2fill[36],totweight);
                    hmcveractvsstartypln[iint]->Fill(value2fill[28],value2fill[36],totweight);
                    
                    hmcpidvsQsq[iint]->Fill(value2fill[37],value2fill[39],totweight);
                    hmcpidvsVeract[iint]->Fill(value2fill[36],value2fill[39],totweight);
                    hmcpidvspidres[iint]->Fill(value2fill[40],value2fill[39],totweight);
                    hmcpidvspidccqe[iint]->Fill(value2fill[41],value2fill[39],totweight);
                }
            }
            
        }
    }//end for jentry
    popfile->Write();
    popfile->Close();
    
}

void baseTree::CheckVeract(TString ipFile, TString opFile)
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
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TFile *popfile = new TFile(opFile,"RECREATE");
    TH1F *hveract_1trk_ccqe = new TH1F("hveract_1trk_ccqe","",200,0,200);
    TH1F *hveract_1trk_ccqe_trkid = new TH1F("hveract_1trk_ccqe_trkid","",200,0,200);
    TH2F *hveractvsmuang_1trk_ccqe = new TH2F("hveractvsmuang_1trk_ccqe","",90,0,90,200,0,200);
    TH2F *hveractvsmuang_1trk_ccqe_trkid = new TH2F("hveractvsmuang_1trk_ccqe_trkid","",90,0,90,200,0,200);
    
    TH1F *hveract_2trk_ccqe = new TH1F("hveract_2trk_ccqe","",200,0,200);
    TH1F *hveract_2trk_ccqe_trkid = new TH1F("hveract_2trk_ccqe_trkid","",200,0,200);
    TH2F *hveractvsmuang_2trk_ccqe = new TH2F("hveractvsmuang_2trk_ccqe","",90,0,90,200,0,200);
    TH2F *hveractvsmuang_2trk_ccqe_trkid = new TH2F("hveractvsmuang_2trk_ccqe_trkid","",90,0,90,200,0,200);
    TH2F *hveractvspang_2trk_ccqe = new TH2F("hveractvspang_2trk_ccqe","",90,0,90,200,0,200);
    TH2F *hveractvspang_2trk_ccqe_trkid= new TH2F("hveractvspang_2trk_ccqe_trkid","",90,0,90,200,0,200);
    
    TH1F *hveract_1trk_ncqe = new TH1F("hveract_1trk_ncqe","",200,0,200);
    TH1F *hveract_1trk_ncqe_trkid = new TH1F("hveract_1trk_ncqe_trkid","",200,0,200);
    TH2F *hveractvsmuang_2trk_ncqe = new TH2F("hveractvsmuang_2trk_ncqe","",90,0,90,200,0,200);
    TH2F *hveractvsmuang_2trk_ncqe_trkid = new TH2F("hveractvsmuang_2trk_ncqe_trkid","",90,0,90,200,0,200);
    
    if (fChain == 0) return;
    
    Long64_t nentries = fChain->GetEntriesFast();
    Long64_t iprintProcess = Long64_t(nentries/100.);
    cout<<"total "<<nentries<<" iprint "<<iprintProcess<<endl;
    Long64_t nbytes = 0, nb = 0;
    
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
        if (fileIndex==3) totweight = (norm*totcrsne<0.2e18)*1.106*norm*totcrsne*mcWeight*6.9e-12/1.3;
        //TODO reweight for genie
        if (fileIndex==10) {
            totweight = 3.41e-2*NMCFILE*1e21/NPOT;//to mimic NEUT
            if (isEnergyReweightInclude) {
                totweight *=rwratio[3][intnue];
            }
        }
        
        if (fileIndex!=1) continue;
        
        if (Ntrack==1) {
            //ccqe
            if (inttype==1) {
                hveract_1trk_ccqe->Fill(veract*7.6634e-2);
                hveractvsmuang_1trk_ccqe->Fill(muang_t,veract*7.6634e-2);
                if (mupdg==13) {
                    hveract_1trk_ccqe_trkid->Fill(veract*7.6634e-2);
                    hveractvsmuang_1trk_ccqe_trkid->Fill(muang_t,veract*7.6634e-2);
                }
            }
            //NCQE
            if (inttype==51) {
                hveract_1trk_ncqe->Fill(veract*7.6634e-2);
                hveractvsmuang_2trk_ncqe->Fill(muang_t,veract*7.6634e-2);
                if (mupdg==2212) {
                    hveract_1trk_ncqe_trkid->Fill(veract*7.6634e-2);
                    hveractvsmuang_2trk_ncqe_trkid->Fill(muang_t,veract*7.6634e-2);
                }
            }
            
        }
        
        
        //two track CCQE
        if (Ntrack==2) {
            if (inttype==1) {
                hveract_2trk_ccqe->Fill(veract*7.6634e-2);
                hveractvsmuang_2trk_ccqe->Fill(muang_t,veract*7.6634e-2);
                hveractvspang_2trk_ccqe->Fill(pang_t,veract*7.6634e-2);
                if (mupdg==13 && ppdg==2212) {
                    hveract_2trk_ccqe_trkid->Fill(veract*7.6634e-2);
                    hveractvsmuang_2trk_ccqe_trkid->Fill(muang_t,veract*7.6634e-2);
                    hveractvspang_2trk_ccqe_trkid->Fill(pang_t,veract*7.6634e-2);
                }
            }
        }
        
        //fill histogram
        
    }//end for jentry
    popfile->Write();
    popfile->Close();

    
    
}
void baseTree::CheckFSI(TString ipFile, TString opFile)
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
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TFile *popfile = new TFile(opFile,"RECREATE");
    //muangle, piangle, mumucl, pmucl, mumomentum,
    //pid, pidres, pidccqe
    //pidfsi, pidfsires, pidfsiccqe
    //veract, energy deposition convert
    const int NVARIABLES = 13;
    //0 after presel, 1, presel + pid, 2 sig, 3 cr1, 4 cr2, 5 cr3, 6 truesig
    const int NTOPOLOGY = 7;
    //this is true information of track
    const int NINTERACTION = 14;
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    TH2F* hveractvsmuang[NTOPOLOGY][NINTERACTION];
    TH2F* hveractvspang[NTOPOLOGY][NINTERACTION];
    //binining and limit
    //ntrk, ning, muang, pang,
    Int_t NBINHIST[NVARIABLES]={90,90,100,100,150,200,200,200,200,200,200,200,200};
    Double_t XMIN[NVARIABLES]={0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0};
    Double_t XMAX[NVARIABLES]={90,90,1,1,1.5,1,1,1,1,1,1,500,200};
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            //for mc
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = new TH1F(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint),"",NBINHIST[ivar],XMIN[ivar],XMAX[ivar]);
            }
        }
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hveractvsmuang[itopo][iint] = new TH2F(Form("hveractvsmuang_topo%d_int%d",itopo,iint),"",NBINHIST[0],XMIN[0],XMAX[0],NBINHIST[12],XMIN[12],XMAX[12]);
            hveractvspang[itopo][iint] = new TH2F(Form("hveractvspang_topo%d_int%d",itopo,iint),"",NBINHIST[1],XMIN[1],XMAX[1],NBINHIST[12],XMIN[12],XMAX[12]);
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
        if (fileIndex==3) totweight = (norm*totcrsne<0.2e18)*1.106*norm*totcrsne*mcWeight*6.9e-12/1.3;
        //TODO reweight for genie
        if (fileIndex==10) {
            totweight = 3.41e-2*NMCFILE*1e21/NPOT;//to mimic NEUT
            if (isEnergyReweightInclude) {
                totweight *=rwratio[3][intnue];
            }
        }
        
        //Fill variable
        value2fill[0] =          muang_t;
        value2fill[1] =          pang_t;
        value2fill[2] =          mumucl;
        value2fill[3] =          pmucl;
        value2fill[4] =          GetPrec(range);
        value2fill[5] =          pid;
        value2fill[6] =          pid1pres;
        value2fill[7] =          pidccqe;
        value2fill[8] =          pidfsi;
        value2fill[9] =          pidfsi1pres;
        value2fill[10] =         pidfsiccqe;
        value2fill[11] =         veract;
        value2fill[12] =         veract*7.6634e-2;
        
        //fill histogram
        if (fileIndex!=0) {
            for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
                for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
                    for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                            if (CutTopologyFSIbyID(ientry,itopo)>0 && CutTrueTrackbyID(ientry,iint)>0) {
                            hmc[itopo][ivar][iint]->Fill(value2fill[ivar],totweight);
                            
                        }
                    }
                }
                for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                    if (CutTopologyFSIbyID(ientry,itopo)>0 && CutTrueTrackbyID(ientry,iint)>0) {
                        hveractvsmuang[itopo][iint]->Fill(value2fill[0],value2fill[12]);
                        hveractvspang[itopo][iint]->Fill(value2fill[1],value2fill[12]);
                    }
                }
            }
        }
    }//end for jentry
    popfile->Write();
    popfile->Close();
    
}
void baseTree::OptimizeFSICut(TString ipFile, TString opFile)
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
    TTree *piptree = (TTree*)pipfile->Get("tree");
    Init(piptree);
    
    /////////////////////////////////////////////////////////////////////
    TFile *popfile = new TFile(opFile,"RECREATE");
    //muangle, piangle, mumucl, pmucl, mumomentum,
    //pidfsi, vertexactivity, energydeposit, pidfsiccqe, pidfsires
    const int NVARIABLES = 5;
    
    //0 after presel, 1, after pidfsi, vertex activity cut
    const int NTOPOLOGY = 2;
    
    //signal & background
    const int NINTERACTION = 2;
    TH2F* hmcve[NTOPOLOGY][NINTERACTION];//vertex activity
    TH2F* hmcen[NTOPOLOGY][NINTERACTION];//energy deposition
    TH2F* hmcpidresqe[NTOPOLOGY][NINTERACTION];//energy deposition
    //binining and limit
    //ntrk, ning, muang, pang,
    Int_t NBINHIST[NVARIABLES]={200,500,200,200,200};
    Double_t XMIN[NVARIABLES]={-1,0,0,-1,-1};
    Double_t XMAX[NVARIABLES]={1,5000,400,1,1};
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmcve[itopo][iint] = new TH2F(Form("hmcve_topo%d_int%d",itopo,iint),"",NBINHIST[1],XMIN[1],XMAX[1],NBINHIST[0],XMIN[0],XMAX[0]);
                hmcen[itopo][iint] = new TH2F(Form("hmcen_topo%d_int%d",itopo,iint),"",NBINHIST[2],XMIN[2],XMAX[2],NBINHIST[0],XMIN[0],XMAX[0]);
                hmcpidresqe[itopo][iint] = new TH2F(Form("hmcpidresqe_topo%d_int%d",itopo,iint),"",NBINHIST[3],XMIN[3],XMAX[3],NBINHIST[4],XMIN[4],XMAX[4]);
                
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
        if (fileIndex==3) totweight = (norm*totcrsne<0.2e18)*1.106*norm*totcrsne*mcWeight*6.9e-12/1.3;
        //TODO reweight for genie
        if (fileIndex==10) {
            totweight = 3.41e-2*NMCFILE*1e21/NPOT;//to mimic NEUT
            if (isEnergyReweightInclude) {
                totweight *=rwratio[3][intnue];
            }
        }
        
        //Fill variable
        value2fill[0] =          pidfsi;
        value2fill[1] =          veract;
        value2fill[2] =          veract*7.6634e-2;
        value2fill[3] =          pidfsiccqe;
        value2fill[4] =          pidfsi1pres;
        
        //fill histogram
        if (fileIndex!=0) {
            for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
                    for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                        if (CutTopology2OptimizeFSIbyID(ientry,itopo)>0 && CutInteractionSBbyID(ientry,iint)>0) {
                            hmcve[itopo][iint]->Fill(value2fill[1],value2fill[0],totweight);
                            hmcen[itopo][iint]->Fill(value2fill[2],value2fill[0],totweight);
                            hmcpidresqe[itopo][iint]->Fill(value2fill[3],value2fill[4],totweight);
                            
                        }
                    }
            }
        }
    }//end for jentry
    popfile->Write();
    popfile->Close();
    
}

void baseTree::GetEvents(std::vector<AnaSample*> ana_samples)
    {
        //Flux correction --> used for event weight
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

        if (fChain == 0) return;
        if (ana_samples.empty()) return;
        
        Long64_t nentries = fChain->GetEntries();
        Long64_t iprintProcess = Long64_t(nentries/100.);
        cout<<"total "<<nentries<<" iprint "<<iprintProcess<<endl;
        
        Long64_t nbytes = 0, nb = 0;
        //nentries = 500;
        for (Long64_t jentry=0; jentry<nentries;jentry++)
        {
            
            Long64_t ientry = LoadTree(jentry);
            if (ientry < 0) break;
            nb = fChain->GetEntry(jentry);   nbytes += nb;
            if (jentry%iprintProcess == 0) std::cout<<"Processing "<<int(jentry*100./nentries)<<"% of events"<<std::endl;
            if(GetSampleType(ientry)<0) continue;
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
            if (fileIndex==3) totweight = (norm*totcrsne<0.2e18)*1.106*norm*totcrsne*mcWeight*6.9e-12/1.3;
            //TODO reweight for genie
            if (fileIndex==10) {
                totweight = 3.41e-2*NMCFILE*1e21/NPOT;//to mimic NEUT
                if (isEnergyReweightInclude) {
                    totweight *=rwratio[3][intnue];
                }
            }
            
            //for Data
            if (fileIndex==0) totweight = 1.0;
            
            //create and fill event structure
            AnaEvent ev(jentry);
            ev.SetEvType(GetEventType(ientry));//newadd
            ev.SetSampleType(GetSampleType(ientry));//changelater
            ev.SetReaction(GetInteractionType(ientry));
            ev.SetTrueEnu(nuE);
            double prec = GetPrec(range);//GeV
            double erec = GetErec(prec*1000., muang_t);//MeV
            double costh=TMath::Cos(TMath::Pi()/180.*muang_t);
            ev.SetRecEnu(erec/1000.);
            ev.SetTruePtrk(0);
            ev.SetRecPtrk(prec);
            ev.SetTrueCThtrk(0);
            ev.SetRecCThtrk(costh);
            ev.SetEvWght(totweight);
            ev.SetEvWghtMC(totweight);
            ev.SetVeract(veract*7.6634e-2);//newadd
		
		//add20170511
        ev.SetRecAng1trk(muang_t);
        ev.SetRecAng2trk(pang_t);
        ev.SetRecAngOpenging(opening);
        ev.SetRecAngCoplanarity(coplanarity);
        double recqsq = GetQsq(GetPrec(range)*1.e3,muang_t)/1.e6;
        ev.SetRecQsq(recqsq);	
  	//ev.Print();
            
            //Loop over AnaSample objs and fill appropriate ones
            for(size_t i=0;i<ana_samples.size();i++)
            {
                if(ana_samples[i]->GetSampleType() == GetSampleType(ientry))
                {
                    ana_samples[i]->AddEvent(ev);
                    break;
                }
            }//end for i
        } // jentry loop
        
        //Print some stats
        for(size_t i=0;i<ana_samples.size();i++)
            ana_samples[i]->PrintStats();
    }


