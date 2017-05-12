double getxsecuncertainty(double ratio, double datarate, double bkgratio){
return ((datarate*(1+TMath::Abs(ratio))-bkgratio)/(datarate-bkgratio)-1)*100;
}

void t2kpre_plotDetResponse_FVTime_nosb(){
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 3;
    const char *nameSample[NSAMPLE] = {"SIG", "CRI", "CRII"};//by definition in baseTree:CutSamplebyID
    const char *nameSample_long[NSAMPLE]={"SIG", "CRI", "CRII"};
    
    const char *colorcode[NSAMPLE] = {"#000000",
        "#0072B2",
        "#D55E00"};
    const int markerStyle[NSAMPLE] = {20, 21, 22};
    
    const Int_t NBINCCQE = 5;
    TFile *pFile = new TFile("../inputs/detresponse_FVTime_5bptheta.root");
    
    //this is consistent with XsecParameters
    //follow kikawa-scheme
    const Int_t NCUTTIMING = 3;
    const Int_t NCUTFV = 4;//4;
 
    const Int_t NCUTVETO = 3;
    //histogram to fill
    TH1F* hdt_timing[NSAMPLE][NCUTTIMING];
    
    TH1F* hmc_fv[NSAMPLE][NCUTFV];
    TH1F* hdt_fv[NSAMPLE][NCUTFV];
    
    TH1F* hmc_veto[NSAMPLE][NCUTVETO];
    TH1F* hdt_veto[NSAMPLE][NCUTVETO];
    
    
    //get histogram
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        
        //get histogram--> to check
        for (Int_t iindex=0; iindex<NCUTTIMING; ++iindex) {
            hdt_timing[isam][iindex] = (TH1F*)pFile->Get(Form("hdt_timing_sam%d_index%d",isam,iindex));
            
        }
        
        for (Int_t iindex=0; iindex<NCUTFV; ++iindex) {
            hmc_fv[isam][iindex] = (TH1F*)pFile->Get(Form("hmc_fv_sam%d_index%d",isam,iindex));
            hdt_fv[isam][iindex] = (TH1F*)pFile->Get(Form("hdt_fv_sam%d_index%d",isam,iindex));
            
        }
        
        for (Int_t iindex=0; iindex<NCUTVETO; ++iindex) {
            hmc_veto[isam][iindex] = (TH1F*)pFile->Get(Form("hmc_veto_sam%d_index%d",isam,iindex));
            hdt_veto[isam][iindex] = (TH1F*)pFile->Get(Form("hdt_veto_sam%d_index%d",isam,iindex));
        }
        
    }
    //timing
	double nevtbyBin_timing[3];
    double xsigma_timing[3]={0.5,1.5,2.5}; 
    //fv
	double nevtbyBinmc_fv[NCUTFV];
    double nevtbyBindt_fv[NCUTFV];
    double nevtbyBinsub_fv[NCUTFV];
    double xsigma_fv[NCUTFV]={0.5,1.5,2.5,3.5};
     //double xsigma_fv[NCUTFV]={0.5,1.5,2.5,3.5,4.5,5.5,6.5};
    //veto
	double nevtbyBinmc_veto[3];
    double nevtbyBindt_veto[3];
    double nevtbyBinsub_veto[3];
    double xsigma_veto[3]={0.5,1.5,2.5};
TGraph *pgrall[NSAMPLE][3];
	for (int isam=0; isam<NSAMPLE; ++isam) {
	cout<<"Processing...sam..."<<isam<<endl;
	 for (Int_t iindex=0; iindex<NCUTTIMING; ++iindex) {
                nevtbyBin_timing[iindex] = hdt_timing[isam][iindex]->GetSumOfWeights();
               cout<<" timing "<<iindex<<" nevt "<<nevtbyBin_timing[iindex]<<endl;
                if (hdt_timing[isam][iindex]->GetSumOfWeights()!=0) {
                    nevtbyBin_timing[iindex] /= hdt_timing[isam][0]->GetSumOfWeights();
                }
                else nevtbyBin_timing[iindex] = 1;
		cout<<" timing ratio "<<iindex<<" nevt "<<nevtbyBin_timing[iindex]<<endl;
   		nevtbyBin_timing[iindex] = nevtbyBin_timing[iindex] -1;
            }

	//fv
            for (Int_t iindex=0; iindex<NCUTFV; ++iindex) {
                nevtbyBinmc_fv[iindex] = hmc_fv[isam][iindex]->GetSumOfWeights();
		cout<<"fv "<<iindex<<" mc "<<nevtbyBinmc_fv[iindex]<<endl;
                if (hmc_fv[isam][iindex]->GetSumOfWeights()!=0) {
                    nevtbyBinmc_fv[iindex] /= hmc_fv[isam][0]->GetSumOfWeights();
                }
                else nevtbyBinmc_fv[iindex] = 1;

                nevtbyBindt_fv[iindex] = hdt_fv[isam][iindex]->GetSumOfWeights();
                cout<<"fv "<<iindex<<" dt "<<nevtbyBindt_fv[iindex]<<endl;
		if (hdt_fv[isam][iindex]->GetSumOfWeights()!=0) {
                    nevtbyBindt_fv[iindex] /= hdt_fv[isam][0]->GetSumOfWeights();
                }
                else nevtbyBindt_fv[iindex] = 1;

                nevtbyBinsub_fv[iindex] = nevtbyBindt_fv[iindex] - nevtbyBinmc_fv[iindex];
		cout<<"fv ratio "<<iindex<<" dt "<<nevtbyBindt_fv[iindex]<<" mc "<<nevtbyBinmc_fv[iindex]<<" sub "<<nevtbyBinsub_fv[iindex]<<endl;
            }

	//veto
	 for (Int_t iindex=0; iindex<NCUTVETO; ++iindex) {
                nevtbyBinmc_veto[iindex] = hmc_veto[isam][iindex]->GetSumOfWeights();
		cout<<"veto "<<iindex<<" mc "<<nevtbyBinmc_veto[iindex] <<endl;
                if (hmc_veto[isam][iindex]->GetSumOfWeights()!=0) {
                    nevtbyBinmc_veto[iindex] /= hmc_veto[isam][0]->GetSumOfWeights();
                }
                else nevtbyBinmc_veto[iindex] = 1;

                nevtbyBindt_veto[iindex] = hdt_veto[isam][iindex]->GetSumOfWeights();
		cout<<"veto "<<iindex<<" dt "<<nevtbyBindt_veto[iindex]<<endl;
                if (hdt_veto[isam][iindex]->GetSumOfWeights()!=0) {
                    nevtbyBindt_veto[iindex] /= hdt_veto[isam][0]->GetSumOfWeights();
                }
                else nevtbyBindt_veto[iindex] = 1;

                nevtbyBinsub_veto[iindex] = nevtbyBindt_veto[iindex] - nevtbyBinmc_veto[iindex];
                cout<<"veto ratio "<<iindex<<" dt "<<nevtbyBinsub_veto[iindex]<<" mc "<<nevtbyBindt_veto[iindex]<<" sub "<<nevtbyBinsub_veto[iindex]<<endl;
            }
	pgrall[isam][0] = new TGraph(3,xsigma_timing,nevtbyBin_timing);
        pgrall[isam][1] = new TGraph(NCUTFV,xsigma_fv,nevtbyBinsub_fv);
        pgrall[isam][2] = new TGraph(NCUTVETO,xsigma_veto,nevtbyBinsub_veto);	
	}
    
    //comb
       double aVariation;
    double aVariationAll;
    double tempMaxGraph;
    double tempMinGraph;
   for (int isam=0; isam<NSAMPLE; ++isam) {
   cout<<"Processing sample "<<isam<<endl;
	aVariationAll = 0;
    for (Int_t isys=0; isys<3; ++isys) {
          	
 		tempMaxGraph = TMath::Abs(TMath::MaxElement(pgrall[isam][isys]->GetN(),pgrall[isam][isys]->GetY()));
                tempMinGraph = TMath::Abs(TMath::MinElement(pgrall[isam][isys]->GetN(),pgrall[isam][isys]->GetY()));
                aVariation = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;
                cout<<"syst "<<isys<<" val "<<aVariation<<"xsec % "<<getxsecuncertainty(aVariation,0.616,0.4512)<<" rat04 "<<getxsecuncertainty(aVariation,0.671,0.4512)<<endl;
          	//cout<<"testing "<<aVariation<<endl;
                aVariationAll += pow(aVariation,2);
    }
    cout<<"final variation "<<TMath::Sqrt(aVariationAll)<<"xsec %"<<getxsecuncertainty(TMath::Sqrt(aVariationAll), 0.616,0.4512)<<" rat04 "<<getxsecuncertainty(TMath::Sqrt(aVariationAll), 0.671,0.4512)<<endl;
    } 
    
    
}
