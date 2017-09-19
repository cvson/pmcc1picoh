{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    float npot = 6.04193507503274721e20;
    //int   nmc  = 3950;
    int   nmc  = 3974;//for newneut
    float mcpotreweight = npot/(nmc*1e21);
    
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 6;
    const char *nameSample[NSAMPLE] = {"SIG", "CRI", "CRII","CRIII","CRIV","CRV"};
    const char *nameSample_long[NSAMPLE]={"SIG", "CRI", "CRII","CRIII","CRIV","CRV"};
    
    const char *colorcode[NSAMPLE] = {"#000000",
        "#0072B2",
        "#D55E00",
	"#CC79A7",
	"#E69F00",
	"#009E73"};
    const int markerStyle[NSAMPLE] = {20, 21, 22,23,24,25};
    
    const Int_t NBINCCQE = 3;
    const char *colorbin[] = {
        "#000000",
        "#E69F00",
        "#009E73",
        "#0072B2",
        "#D55E00"
    };
    const int markerStyleBin[] = {20, 21, 22, 24, 25};
    const Int_t NFILE = 4;
    TFile *pFile[NFILE];
    pFile[0] = new TFile("../inputs/detresponsefunction_nominal.root");
    pFile[1] = new TFile("../inputs/detresponsefunction_pevar_nom.root");
    pFile[2] = new TFile("../inputs/detresponsefunction_pevar_shiftplus.root");
    pFile[3] = new TFile("../inputs/detresponsefunction_pevar_shiftminus.root");
    
    TH1F *hbinccqe[NFILE][NSAMPLE];
    TH1F *hbinccqe_bkg[NFILE][NSAMPLE];
    TH1F *hbinccqe_sig[NFILE][NSAMPLE];
    
    for (int ifile=0; ifile<NFILE; ++ifile) {
        for (int isam=0; isam<NSAMPLE; ++isam) {
            hbinccqe[ifile][isam] = (TH1F*)pFile[ifile]->Get(Form("hbinccqe_sam%d",isam));
            hbinccqe[ifile][isam]->Scale(mcpotreweight);
            hbinccqe_bkg[ifile][isam] = (TH1F*)pFile[ifile]->Get(Form("hbinccqe_bkg_sam%d",isam));
            hbinccqe_bkg[ifile][isam]->Scale(mcpotreweight);
            hbinccqe_sig[ifile][isam] = (TH1F*)pFile[ifile]->Get(Form("hbinccqe_sig_sam%d",isam));
            hbinccqe_sig[ifile][isam]->Scale(mcpotreweight);
        }
    }
    
    //what is nominal, the general or subset
    const Int_t ithnominal = 0;
    for (int isam=0; isam<NSAMPLE; ++isam) {
    	TString savename = Form("detsyst_pevar_comp_sam%d",isam);
        hbinccqe[ithnominal][isam]->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
        hbinccqe[ithnominal][isam]->GetYaxis()->SetTitle("Number of Events");
        plot3histdata(hbinccqe[ithnominal][isam],"Nominal", hbinccqe[2][isam],"+1#sigma shift",hbinccqe[3][isam],"-1#sigma shift", savename+"_allevt", 0.55,0.25);
        hbinccqe_sig[ithnominal][isam]->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
        hbinccqe_sig[ithnominal][isam]->GetYaxis()->SetTitle("Number of Signals");
        plot3histdata(hbinccqe_sig[ithnominal][isam],"Nominal", hbinccqe_sig[2][isam],"+1#sigma shift",hbinccqe_sig[3][isam],"-1#sigma shift", savename+"_sigevt", 0.55,0.25);
        hbinccqe_bkg[ithnominal][isam]->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
        hbinccqe_bkg[ithnominal][isam]->GetYaxis()->SetTitle("Number of Backgrounds");
        plot3histdata(hbinccqe_bkg[ithnominal][isam],"Nominal", hbinccqe_bkg[2][isam],"+1#sigma shift",hbinccqe_bkg[3][isam],"-1#sigma shift", savename+"_bkgevt", 0.55,0.25);   
    }
 //make ratio and uncertainty
    //make graph, dont' need
    TGraph *pgrccqe[NSAMPLE][NBINCCQE];
    TGraph *pgrccqe_bkg[NSAMPLE][NBINCCQE];
    TGraph *pgrccqe_sig[NSAMPLE][NBINCCQE];
    double nevtbyBin[NFILE];
    double nevtbyBin_bkg[NFILE];
    double nevtbyBin_sig[NFILE];
    double xsigma[NFILE];//nominal, plus, minus//={0,1,2,3,4,5,6,7,8};
    for (int ifile=0; ifile<NFILE; ++ifile) {
        xsigma[ifile] = ifile+1;
    }
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
            for (int ifile=0; ifile<NFILE; ++ifile) {
                //for all event
                nevtbyBin[ifile] = hbinccqe[ifile][isam]->GetBinContent(ibin+1);
                if (hbinccqe[ithnominal][isam]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin[ifile] /= hbinccqe[ithnominal][isam]->GetBinContent(ibin+1);
                }
                else nevtbyBin[ifile] = 1.0;
                nevtbyBin[ithnominal] = 1.0;
                cout<<"Sample "<<isam<<" bin "<<ibin<<" value "<<nevtbyBin[ifile]<<endl;                
                //for background
                nevtbyBin_bkg[ifile] = hbinccqe_bkg[ifile][isam]->GetBinContent(ibin+1);
                if (hbinccqe_bkg[ithnominal][isam]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin_bkg[ifile] /= hbinccqe_bkg[ithnominal][isam]->GetBinContent(ibin+1);
                }
                else nevtbyBin_bkg[ifile] = 1.0;
                nevtbyBin_bkg[ithnominal] = 1.0;
                
                //for signal
                nevtbyBin_sig[ifile] = hbinccqe_sig[ifile][isam]->GetBinContent(ibin+1);
                if (hbinccqe_sig[ithnominal][isam]->GetBinContent(ibin+1)!=0) {
                    nevtbyBin_sig[ifile] /= hbinccqe_sig[ithnominal][isam]->GetBinContent(ibin+1);
                }
                else nevtbyBin_sig[ifile] = 1.0;
                nevtbyBin_sig[ithnominal] = 1.0;
                
            }//end ifile
            pgrccqe[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin);
            pgrccqe_bkg[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin_bkg);
            pgrccqe_sig[isam][ibin] = new TGraph(NFILE,xsigma,nevtbyBin_sig);
        }//end ibin
    }//end isam
   
      double aVariation[NBINCCQE];
    double aVariation_sig[NBINCCQE];
    double aVariation_bkg[NBINCCQE];
    double xBinValue[NBINCCQE];
    double tempMaxGraph;
    double tempMinGraph;
    for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
        xBinValue[ibin] = ibin+0.5;
    }
    TFile *popfile = new TFile("../inputs/detresponse_pevar_3bptheta_uncertainty.root","RECREATE");
    TGraph *pUncertainty[NSAMPLE];
    TGraph *pUncertainty_sig[NSAMPLE];
    TGraph *pUncertainty_bkg[NSAMPLE];
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
           
            tempMaxGraph = TMath::Abs(TMath::MaxElement(NFILE,pgrccqe[isam][ibin]->GetY())-1);
            tempMinGraph = TMath::Abs(TMath::MinElement(NFILE,pgrccqe[isam][ibin]->GetY())-1);
            aVariation[ibin] = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;
            
            cout<<"For ALL SAM "<<isam<<" BIN "<<ibin<<" Val "<<aVariation[ibin]<<endl;
            
        }
        pUncertainty[isam] = new TGraph(NBINCCQE,xBinValue,aVariation);
        pUncertainty[isam]->Write(Form("detresponse_pevar_3bptheta_uncertainty_sam%d",isam));
      //for signal
	for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {

            tempMaxGraph = TMath::Abs(TMath::MaxElement(NFILE,pgrccqe_sig[isam][ibin]->GetY())-1);
            tempMinGraph = TMath::Abs(TMath::MinElement(NFILE,pgrccqe_sig[isam][ibin]->GetY())-1);
            aVariation_sig[ibin] = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;

            cout<<"For SIGNAL SAM "<<isam<<" BIN "<<ibin<<" Val "<<aVariation_sig[ibin]<<endl;

        }
        pUncertainty_sig[isam] = new TGraph(NBINCCQE,xBinValue,aVariation_sig);
	pUncertainty_sig[isam]->Write(Form("detresponse_pevar_sig_3bptheta_uncertainty_sam%d",isam));
	//for background

      for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {

            tempMaxGraph = TMath::Abs(TMath::MaxElement(NFILE,pgrccqe_bkg[isam][ibin]->GetY())-1);
            tempMinGraph = TMath::Abs(TMath::MinElement(NFILE,pgrccqe_bkg[isam][ibin]->GetY())-1);
            aVariation_bkg[ibin] = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;

            cout<<"For BACKGROUND SAM "<<isam<<" BIN "<<ibin<<" Val "<<aVariation_bkg[ibin]<<endl;

        }
        pUncertainty_bkg[isam] = new TGraph(NBINCCQE,xBinValue,aVariation_bkg);
        pUncertainty_bkg[isam]->Write(Form("detresponse_pevar_bkg_3bptheta_uncertainty_sam%d",isam));
      }

   //plot
    popfile->Write();
    popfile->Close();
   
}
