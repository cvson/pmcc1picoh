{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 3;
    const char *nameSample[NSAMPLE] = {"SIG",  "CRI", "CRII"};
    const char *nameSample_long[NSAMPLE]={"SIG", "CRI", "CRII"};
    
    const char *colorcode[NSAMPLE] = {"#000000",
        "#0072B2",
        "#D55E00"};
    const int markerStyle[NSAMPLE] = {20, 21, 22};
    
    /*const Int_t NBINCCQE = 9;//need to be consistent w/ inputs/cc1picohbins.txt
        const char *colorbin[NBINCCQE] = {
        "#9a963f",
"#7f66cc",
"#64ac48",
"#c556b6",
"#4aac8d",
"#cb4f42",
"#6c8dcd",
"#c98443",
"#c45e86"
        };
    const int markerStyleBin[NBINCCQE] = {20, 21, 22, 24, 25, 26,27,28,29};
    */
const Int_t NBINCCQE = 5;//need to be consistent w/ inputs/cc1picohbins.txt
        const char *colorbin[NBINCCQE] = {
"#000000",
"#E69F00",
"#009E73",
"#0072B2",
"#D55E00"        
};
    const int markerStyleBin[NBINCCQE] = {20, 21, 22, 24, 25};

    TFile *pFile = new TFile("../inputs/detresponsefunction_pe.root");
    
    TGraph *pgrccqe[NSAMPLE][NBINCCQE];
    TGraph *pgrccqe_bkg[NSAMPLE][NBINCCQE];
    
    for (int isam=0; isam<NSAMPLE; ++isam) {
        icolor = TColor::GetColor(colorcode[isam]);
        imarker = markerStyle[isam];
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
            pgrccqe[isam][ibin]  = (TGraph*)pFile->Get(Form("response_sample%d_bin%d",isam,ibin));
            pgrccqe[isam][ibin]->SetLineColor(icolor);
            pgrccqe[isam][ibin]->SetMarkerColor(icolor);
            pgrccqe[isam][ibin]->SetMarkerStyle(imarker);
            
            pgrccqe_bkg[isam][ibin] = (TGraph*)pFile->Get(Form("response_bkg_sample%d_bin%d",isam,ibin));
            pgrccqe_bkg[isam][ibin]->SetLineColor(icolor);
            pgrccqe_bkg[isam][ibin]->SetMarkerColor(icolor);
            pgrccqe_bkg[isam][ibin]->SetMarkerStyle(imarker);
        }
    }
    
    //dummy TLegend
    TLegend* leg0 = new TLegend(.4, .62, 0.65, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.02);
    for (int isam=0;isam<2;isam++){
        leg0->AddEntry(pgrccqe[isam][0], nameSample_long[isam],"pl");
    }
    leg0->SetFillStyle(0);
    
    //draw
    for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
        new TCanvas;
        pgrccqe[0][ibin]->GetXaxis()->SetTitle("Parameter variation");
        pgrccqe[0][ibin]->GetYaxis()->SetTitle("Event variation (by bin)");
        
        titleStyle(pgrccqe[0][ibin]);
        pgrccqe[0][ibin]->GetYaxis()->SetRangeUser(0,2);
        pgrccqe[0][ibin]->Draw("APL");
        for (Int_t isam=1; isam<2; ++isam){
            pgrccqe[isam][ibin]->Draw("PL same");
        }
        TLatex* tlx=new TLatex(0.42, 0.95,Form("bin%d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        leg0->Draw("same");
        gPad->Modified();
        gPad->Print(Form("plots/detresponse_pe_5bptheta_bin%d_compSyst.eps",ibin));
        
        new TCanvas;
        pgrccqe_bkg[0][ibin]->GetXaxis()->SetTitle("Parameter variation");
        pgrccqe_bkg[0][ibin]->GetYaxis()->SetTitle("Event variation (by bin)");
        
        titleStyle(pgrccqe_bkg[0][ibin]);
        pgrccqe_bkg[0][ibin]->GetYaxis()->SetRangeUser(0,2);
        pgrccqe_bkg[0][ibin]->Draw("APL");
        for (Int_t isam=1; isam<2; ++isam){
            pgrccqe_bkg[isam][ibin]->Draw("PL same");
        }
        
        tlx->Draw();
        leg0->Draw("same");
        gPad->Modified();
        gPad->Print(Form("plots/detresponse_pe_5bptheta_bkg_bin%d_compSyst.eps",ibin));
        
    }
   //draw all
   TLegend* leg0bin = new TLegend(.75, .6, 0.95, .92);
    leg0bin->SetFillStyle(0);
    leg0bin->SetBorderSize(0);
    leg0bin->SetTextSize(0.037);
   new TCanvas;
   for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
   icolor = TColor::GetColor(colorbin[ibin]);
           imarker = markerStyleBin[ibin];
   pgrccqe[0][ibin]->SetLineColor(icolor);
   pgrccqe[0][ibin]->SetMarkerColor(icolor);
   pgrccqe[0][ibin]->SetMarkerStyle(imarker);

   pgrccqe[1][ibin]->SetLineColor(icolor);
   pgrccqe[1][ibin]->SetMarkerColor(icolor);
   pgrccqe[1][ibin]->SetMarkerStyle(imarker);
   pgrccqe[1][ibin]->SetLineStyle(7);
   
   pgrccqe_bkg[0][ibin]->SetLineColor(icolor);
    pgrccqe_bkg[0][ibin]->SetMarkerColor(icolor);
    pgrccqe_bkg[0][ibin]->SetMarkerStyle(imarker);
    
    pgrccqe_bkg[1][ibin]->SetLineColor(icolor);
    pgrccqe_bkg[1][ibin]->SetMarkerColor(icolor);
    pgrccqe_bkg[1][ibin]->SetMarkerStyle(imarker);
    pgrccqe_bkg[1][ibin]->SetLineStyle(7);
   leg0bin->AddEntry(pgrccqe[0][ibin], Form("bin %d",ibin),"PL");

   } 
  TH1F *h1 = new TH1F("h1","TLegend Example",200,-10,10);
//h1->SetLineColor("kBlack");
 TH1F *h2 = new TH1F("h2","TLegend Example",200,-10,10);
//h2->SetLineColor("kBlack");
h2->SetLineStyle(7);
leg0bin->AddEntry(h1,"Signal","l");
leg0bin->AddEntry(h2,"Sideband","l");
    leg0bin->SetFillStyle(0);
for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
if(ibin==0) pgrccqe[0][ibin]->Draw("APL");
else pgrccqe[0][ibin]->Draw("PL same");

pgrccqe[1][ibin]->Draw("PL same");
}
leg0bin->Draw("same");
      gPad->Modified();
gPad->Print("plots/detresponse_pe_5bptheta_sig_all_sigvssb.eps");


for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
if(ibin==0) pgrccqe_bkg[0][ibin]->Draw("APL");
else pgrccqe_bkg[0][ibin]->Draw("PL same");

pgrccqe_bkg[1][ibin]->Draw("PL same");
}
leg0bin->Draw("same");
      gPad->Modified();
gPad->Print("plots/detresponse_pe_5bptheta_bkg_all_sigvssb.eps");

    //fitting
    TF1 *f1= new TF1("f1","[0]+[1]*x");
    f1->SetParName(0,"#alpha");
    f1->SetParName(1,"#beta");
    f1->SetLineWidth(2);
    f1->SetLineStyle(7);
    f1->SetLineColor(2);
    double aSlope[NBINCCQE];
    double aVariation[NBINCCQE];
    double xBinValue[NBINCCQE];
    for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
        xBinValue[ibin] = ibin+0.5;
    }
    TGraph *pUncertainty[NSAMPLE];
    TFile *popfile = new TFile("../inputs/detresponse_pe_5bptheta_uncertainty.root","RECREATE");
    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
            pgrccqe[isam][ibin]->Fit("f1");
            TF1 *func=pgrccqe[isam][ibin]->GetFunction("f1");
            aSlope[ibin] = func->GetParameter(1);
            aVariation[ibin] = TMath::Abs(aSlope[ibin])*2.7;//TN data vs MC discrepancy
            cout<<"Sample "<<isam<<" Bin "<<ibin<<" variation "<<aVariation[ibin]<<endl;

        }
        pUncertainty[isam] = new TGraph(NBINCCQE,xBinValue,aVariation);
        pUncertainty[isam]->Write(Form("detresponse_pe_5bptheta_uncertainty_sam%d",isam));
    }
    popfile->Write();
    popfile->Close();
    
}
