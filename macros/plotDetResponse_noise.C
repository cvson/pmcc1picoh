{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 3;
    const char *nameSample[NSAMPLE] = {"SIG", "CRI", "CRII"};
    const char *nameSample_long[NSAMPLE]={"SIG", "CRI", "CRII"};
    
    const char *colorcode[NSAMPLE] = {"#000000",
        "#0072B2",
        "#D55E00"};
    const int markerStyle[NSAMPLE] = {20, 21, 22};
    
    const Int_t NBINCCQE = 5;
   const char *colorbin[NBINCCQE] = {
"#000000",
"#E69F00",
"#009E73",
"#0072B2",
"#D55E00"
};
    const int markerStyleBin[NBINCCQE] = {20, 21, 22, 24, 25};

    TFile *pFile = new TFile("../inputs/detresponsefunction_noise.root");
    
    TGraph *pgrccqe[NSAMPLE][NBINCCQE];
    
    for (int isam=0; isam<NSAMPLE; ++isam) {
        icolor = TColor::GetColor(colorcode[isam]);
        imarker = markerStyle[isam];
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
            pgrccqe[isam][ibin]  = (TGraph*)pFile->Get(Form("response_noise_sample%d_bin%d",isam,ibin));
            pgrccqe[isam][ibin]->SetLineColor(icolor);
            pgrccqe[isam][ibin]->SetMarkerColor(icolor);
            pgrccqe[isam][ibin]->SetMarkerStyle(imarker);
            
           
        }
    }
    //check all bins
    TMultiGraph *pgrccqeAll[NSAMPLE];
    
    for (int isam=0; isam<NSAMPLE; ++isam) {
        pgrccqeAll[isam] = new TMultiGraph();
        
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
            icolor = TColor::GetColor(colorbin[ibin]);
           imarker = markerStyleBin[ibin];
   	pgrccqe[isam][ibin]->SetLineColor(icolor);
   	pgrccqe[isam][ibin]->SetMarkerColor(icolor);
   	pgrccqe[isam][ibin]->SetMarkerStyle(imarker);
            pgrccqeAll[isam]->Add(pgrccqe[isam][ibin]);
            
        }
        
        new TCanvas;
        pgrccqeAll[isam]->Draw("APL");
        pgrccqeAll[isam]->GetXaxis()->SetTitle("Parameter variation");
        pgrccqeAll[isam]->GetYaxis()->SetTitle("Event variation (by bin)");
        titleStyle(pgrccqeAll[isam]);
        pgrccqeAll[isam]->SetMinimum(0.95);
        pgrccqeAll[isam]->SetMaximum(1.05);
        gPad->Print(Form("plots/detresponse_noise_5bptheta_all_sam%d_compSyst.eps",isam));
        
        
    }
    

    
    //dummy TLegend
    TLegend* leg0 = new TLegend(.25, .62, 0.5, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.035);
    for (int isam=0;isam<NSAMPLE;isam++){
        leg0->AddEntry(pgrccqe[isam][0], nameSample_long[isam],"pl");
    }
    leg0->SetFillStyle(0);
    
    //draw
    for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
        new TCanvas;
        pgrccqe[0][ibin]->GetXaxis()->SetTitle("Parameter variation");
        pgrccqe[0][ibin]->GetYaxis()->SetTitle("Event variation (by bin)");
        
        titleStyle(pgrccqe[0][ibin]);
        pgrccqe[0][ibin]->GetYaxis()->SetRangeUser(0.8,1.2);
        pgrccqe[0][ibin]->Draw("APL");
        for (Int_t isam=1; isam<NSAMPLE; ++isam){
            pgrccqe[isam][ibin]->Draw("PL same");
        }
        TLatex* tlx=new TLatex(0.42, 0.95,Form("bin%d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        leg0->Draw("same");
        gPad->Modified();
        gPad->Print(Form("plots/detresponse_noise_5bptheta_bin%d_compSyst.eps",ibin));
        

        
    }
    
    //fitting
    
    double aVariation[NBINCCQE];
    double xBinValue[NBINCCQE];
    double tempMaxGraph;
    double tempMinGraph;
    for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
        xBinValue[ibin] = ibin+0.5;
    }
    TGraph *pUncertainty[NSAMPLE];
    TFile *popfile = new TFile("../inputs/detresponse_noise_5bptheta_uncertainty.root","RECREATE");
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
            Double_t* tmpYArray = new Double_t[7];
            for (int itmp=0; itmp<7; itmp++){
                tmpYArray[itmp] = pgrccqe[isam][ibin]->GetY()[itmp+8]-1.0;
                
            }
            tempMaxGraph = TMath::Abs(TMath::MaxElement(7,tmpYArray));
            tempMinGraph = TMath::Abs(TMath::MinElement(7,tmpYArray));
            aVariation[ibin] = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;
            
            cout<<"SAM "<<isam<<" BIN "<<ibin<<" Val "<<aVariation[ibin]<<endl;

        }
        pUncertainty[isam] = new TGraph(NBINCCQE,xBinValue,aVariation);
        pUncertainty[isam]->Write(Form("detresponse_noise_5bptheta_uncertainty_sam%d",isam));
    }
    popfile->Write();
    popfile->Close();
    
}
