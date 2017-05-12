{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 4;
    const char *nameSample[NSAMPLE] = {"SIG", "CRI", "CRII","CRIII"};//by definition in baseTree:CutSamplebyID
    const char *nameSample_long[NSAMPLE]={"SIG", "CRI", "CRII","CRIII"};
    
    const char *colorcode[NSAMPLE] = {"#000000",
        "#0072B2",
        "#D55E00",
	"#CC79A7"};
    const int markerStyle[NSAMPLE] = {20, 21, 22,23};
    
    const Int_t NBINCCQE = 5;
    TFile *pFile = new TFile("../inputs/detresponse_FVTime.root");
	    const char *colorbybin[NBINCCQE] = {
    "#000000",
"#E69F00",
"#009E73",
"#0072B2",
"#D55E00"
    };

const int markerStyleBin[NBINCCQE] = {20, 21, 22, 24, 25/*, 26,27,28,29*/};   
 
    //this is consistent with XsecParameters
    //follow kikawa-scheme
    const Int_t NCUTTIMING = 3;
    const Int_t NCUTFV = 7;//4
    const Int_t NCUTVETO = 3;
    //histogram to fill
    TH1F* hdt_timing[NSAMPLE][NCUTTIMING];
    
    TH1F* hmc_fv[NSAMPLE][NCUTFV];
    TH1F* hdt_fv[NSAMPLE][NCUTFV];
    TGraph *pgrccqemc_fv[NSAMPLE][NBINCCQE];//change from 20
    TGraph *pgrccqedt_fv[NSAMPLE][NBINCCQE];
    TGraph *pgrccqesub_fv[NSAMPLE][NBINCCQE];
 
    TH1F* hmc_veto[NSAMPLE][NCUTVETO];
    TH1F* hdt_veto[NSAMPLE][NCUTVETO];
    TGraph *pgrccqemc_veto[NSAMPLE][NBINCCQE];//change from 20
    TGraph *pgrccqedt_veto[NSAMPLE][NBINCCQE];
    TGraph *pgrccqesub_veto[NSAMPLE][NBINCCQE];

    
    TGraph *pUncertaintyTiming[NSAMPLE];
    TGraph *pUncertaintyFV[NSAMPLE];
    TGraph *pUncertaintyVeto[NSAMPLE];
    TGraph *pUncertaintyComb[NSAMPLE];
    
    //get histogram
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        //get graph
        icolor = TColor::GetColor(colorcode[isam]);
        imarker = markerStyle[isam];
        pUncertaintyTiming[isam] = (TGraph*)pFile->Get(Form("detresponse_timing_uncertainty_sam%d",isam));
        pUncertaintyFV[isam] = (TGraph*)pFile->Get(Form("detresponse_fv_uncertainty_sam%d",isam));
        pUncertaintyVeto[isam] = (TGraph*)pFile->Get(Form("detresponse_veto_uncertainty_sam%d",isam));
        pUncertaintyComb[isam] = (TGraph*)pFile->Get(Form("detresponse_fvtimeall_uncertainty_sam%d",isam));
        
        pUncertaintyTiming[isam]->SetLineColor(icolor);
        pUncertaintyTiming[isam]->SetMarkerColor(icolor);
        pUncertaintyTiming[isam]->SetMarkerStyle(imarker);
        pUncertaintyTiming[isam]->SetLineWidth(3);
        
        pUncertaintyFV[isam]->SetLineColor(icolor);
        pUncertaintyFV[isam]->SetMarkerColor(icolor);
        pUncertaintyFV[isam]->SetMarkerStyle(imarker);
        pUncertaintyFV[isam]->SetLineWidth(3);
        
        pUncertaintyVeto[isam]->SetLineColor(icolor);
        pUncertaintyVeto[isam]->SetMarkerColor(icolor);
        pUncertaintyVeto[isam]->SetMarkerStyle(imarker);
        pUncertaintyVeto[isam]->SetLineWidth(3);
        
        pUncertaintyComb[isam]->SetLineColor(icolor);
        pUncertaintyComb[isam]->SetMarkerColor(icolor);
        pUncertaintyComb[isam]->SetMarkerStyle(imarker);
        pUncertaintyComb[isam]->SetLineWidth(3);
        
        
        //get histogram--> to check
        for (Int_t iindex=0; iindex<NCUTTIMING; ++iindex) {
            hdt_timing[isam][iindex] = (TH1F*)pFile->Get(Form("hdt_timing_sam%d_index%d",isam,iindex));
            icolor = TColor::GetColor(colorcode[iindex]);
            hdt_timing[isam][iindex]->SetLineColor(icolor);
            hdt_timing[isam][iindex]->SetLineWidth(3);
            
        }
        new TCanvas;
        hdt_timing[isam][0]->SetMinimum(0);
        hdt_timing[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTTIMING; ++iindex) {
            hdt_timing[isam][iindex]->Draw("same");
        }
	TLatex* tlx=new TLatex(0.42, 0.95,Form("%s ",nameSample_long[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Print(Form("plots/detresponse_fvtimenosig_dt_5bptheta_timing_sam%d.eps",isam));
        
        for (Int_t iindex=0; iindex<NCUTFV; ++iindex) {
            hmc_fv[isam][iindex] = (TH1F*)pFile->Get(Form("hmc_fv_sam%d_index%d",isam,iindex));
            hdt_fv[isam][iindex] = (TH1F*)pFile->Get(Form("hdt_fv_sam%d_index%d",isam,iindex));
            
		if(iindex<NSAMPLE) icolor = TColor::GetColor(colorcode[iindex]);
            else icolor = iindex;
            hmc_fv[isam][iindex]->SetLineColor(icolor);
            hdt_fv[isam][iindex]->SetLineColor(icolor);
            hmc_fv[isam][iindex]->SetLineWidth(3);
            hdt_fv[isam][iindex]->SetLineWidth(3);
            
        }
        new TCanvas;
        hdt_fv[isam][0]->SetMinimum(0);
        hdt_fv[isam][0]->GetXaxis()->SetTitle("p-#theta bins");
        hdt_fv[isam][0]->GetYaxis()->SetTitle("Number of events");
        titleStyle(hdt_fv[isam][0]);
	hdt_fv[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTFV; ++iindex) {
            hdt_fv[isam][iindex]->Draw("same");
        }
	tlx->Draw();
        gPad->Print(Form("plots/detresponse_fvtimenosig_dt_5bptheta_fv_sam%d.eps",isam));
        
        new TCanvas;
        hmc_fv[isam][0]->SetMinimum(0);
	hmc_fv[isam][0]->GetXaxis()->SetTitle("p-#theta bins");
        hmc_fv[isam][0]->GetYaxis()->SetTitle("Number of events");
        titleStyle(hmc_fv[isam][0]);
	tlx->Draw();
	hmc_fv[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTFV; ++iindex) {
            hmc_fv[isam][iindex]->Draw("same");
        }
        gPad->Print(Form("plots/detresponse_fvtimenosig_mc_5bptheta_fv_sam%d.eps",isam));
      	//by bin
/*	for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
	pgrccqemc_fv[isam][ibin] ->(TGraph*)pFile->Get(Form("detresponse_mcfv_sam%d_bin%d",isam,ibin));
            pgrccqedt_fv[isam][ibin] ->(TGraph*)pFile->Get(Form("detresponse_dtfv_sam%d_bin%d",isam,ibin));
            pgrccqesub_fv[isam][ibin] ->(TGraph*)pFile->Get(Form("detresponse_subfv_sam%d_bin%d",isam,ibin));
	pgrccqemc_veto[isam][ibin] ->(TGraph*)pFile->Get(Form("detresponse_mcveto_sam%d_bin%d",isam,ibin));
            pgrccqedt_veto[isam][ibin] ->(TGraph*)pFile->Get(Form("detresponse_dtveto_sam%d_bin%d",isam,ibin));
            pgrccqesub_veto[isam][ibin] ->(TGraph*)pFile->Get(Form("detresponse_subveto_sam%d_bin%d",isam,ibin));
	}
*/
	//VETO        
        for (Int_t iindex=0; iindex<NCUTVETO; ++iindex) {
            hmc_veto[isam][iindex] = (TH1F*)pFile->Get(Form("hmc_veto_sam%d_index%d",isam,iindex));
            hdt_veto[isam][iindex] = (TH1F*)pFile->Get(Form("hdt_veto_sam%d_index%d",isam,iindex));
            icolor = TColor::GetColor(colorcode[iindex]);
            hmc_veto[isam][iindex]->SetLineColor(icolor);
            hdt_veto[isam][iindex]->SetLineColor(icolor);
            hmc_veto[isam][iindex]->SetLineWidth(3);
            hdt_veto[isam][iindex]->SetLineWidth(3);
        }
        new TCanvas;
        hdt_veto[isam][0]->SetMinimum(0);
	hdt_veto[isam][0]->GetXaxis()->SetTitle("p-#theta bins");
        hdt_veto[isam][0]->GetYaxis()->SetTitle("Number of events");
        titleStyle(hdt_veto[isam][0]);
	hdt_veto[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTVETO; ++iindex) {
            hdt_veto[isam][iindex]->Draw("same");
        }
	tlx->Draw();
        gPad->Print(Form("plots/detresponse_fvtimenosig_dt_5bptheta_veto_sam%d.eps",isam));
        
        new TCanvas;
        hmc_veto[isam][0]->SetMinimum(0);
	hmc_veto[isam][0]->GetXaxis()->SetTitle("p-#theta bins");
        hmc_veto[isam][0]->GetYaxis()->SetTitle("Number of events");
        titleStyle(hmc_veto[isam][0]);
	hmc_veto[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTVETO; ++iindex) {
            hmc_veto[isam][iindex]->Draw("same");
        }
	tlx->Draw();
        gPad->Print(Form("plots/detresponse_fvtimenosig_mc_5bptheta_veto_sam%d.eps",isam));
        
    }
    //making TGraph
    
   //by bin
        for (int isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
        pgrccqemc_fv[isam][ibin] =(TGraph*)pFile->Get(Form("detresponse_mcfv_sam%d_bin%d",isam,ibin));
            pgrccqedt_fv[isam][ibin] =(TGraph*)pFile->Get(Form("detresponse_dtfv_sam%d_bin%d",isam,ibin));
            pgrccqesub_fv[isam][ibin] =(TGraph*)pFile->Get(Form("detresponse_subfv_sam%d_bin%d",isam,ibin));
        pgrccqemc_veto[isam][ibin] =(TGraph*)pFile->Get(Form("detresponse_mcveto_sam%d_bin%d",isam,ibin));
            pgrccqedt_veto[isam][ibin] =(TGraph*)pFile->Get(Form("detresponse_dtveto_sam%d_bin%d",isam,ibin));
            pgrccqesub_veto[isam][ibin] =(TGraph*)pFile->Get(Form("detresponse_subveto_sam%d_bin%d",isam,ibin));
	icolor = TColor::GetColor(colorbybin[ibin]);
                pgrccqesub_fv[isam][ibin]->SetLineColor(icolor);
                pgrccqesub_fv[isam][ibin]->SetMarkerColor(icolor);
                imarker = markerStyleBin[ibin];
                pgrccqesub_fv[isam][ibin]->SetMarkerStyle(imarker);
               pgrccqesub_veto[isam][ibin]->SetLineColor(icolor);
                pgrccqesub_veto[isam][ibin]->SetMarkerColor(icolor);
               pgrccqesub_veto[isam][ibin]->SetMarkerStyle(imarker);
        }
 }
TLegend* leg0bin = new TLegend(.75, .21, 0.95, .55);
    leg0bin->SetFillStyle(0);
    leg0bin->SetBorderSize(0);
    leg0bin->SetTextSize(0.037);
    for (int ibin=0;ibin<NBINCCQE;ibin++){
        leg0bin->AddEntry(pgrccqesub_fv[0][ibin], Form("Bin %d",ibin),"pl");
    }
  TH1F *h1 = new TH1F("h1","TLegend Example",200,-10,10);
//h1->SetLineColor("kBlack");
 TH1F *h2 = new TH1F("h2","TLegend Example",200,-10,10);
//h2->SetLineColor("kBlack");
h2->SetLineStyle(7);
//leg0bin->AddEntry(h1,"Signal","l");
leg0bin->AddEntry(h2,"Sideband","l");
    leg0bin->SetFillStyle(0);
 new TCanvas;
        //pgrccqesub[0][0]->Draw("APL");
	pgrccqesub_fv[1][0]->GetYaxis()->SetTitle("Data-MC difference");
            pgrccqesub_fv[1][0]->GetXaxis()->SetTitle("Variations");

            titleStyle(pgrccqesub_fv[1][0]);
            pgrccqesub_fv[1][0]->GetYaxis()->SetRangeUser(-0.2,0.2);

        pgrccqesub_fv[1][0]->Draw("APL");
        for (Int_t ibin=1; ibin<NBINCCQE; ++ibin) {
                //pgrccqesub_fv[0][ibin]->Draw("PL same");
                pgrccqesub_fv[1][ibin]->Draw("PL same");
        }
        leg0bin->Draw("same");
        TLatex* tlx=new TLatex(0.42, 0.95,Form("Syst: %s","FV"));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/detresponse_fvtimenosig_5bptheta_sigvssb_%s_compAllBin.eps", "fv"));

new TCanvas;
    //pgrccqesub[0][0]->Draw("APL");
    pgrccqesub_veto[1][0]->GetYaxis()->SetTitle("Data-MC difference");
    pgrccqesub_veto[1][0]->GetXaxis()->SetTitle("Variations");
    
    titleStyle(pgrccqesub_veto[1][0]);
    pgrccqesub_veto[1][0]->GetYaxis()->SetRangeUser(-0.2,0.2);
    
    pgrccqesub_veto[1][0]->Draw("APL");
    for (Int_t ibin=1; ibin<NBINCCQE; ++ibin) {
        //pgrccqesub_veto[0][ibin]->Draw("PL same");
        pgrccqesub_veto[1][ibin]->Draw("PL same");
    }
    leg0bin->Draw("same");
    TLatex* tlx=new TLatex(0.42, 0.95,Form("Syst: %s","Veto"));
    tlx->SetNDC(kTRUE); // <- use NDC coordinate
    tlx->SetTextSize(0.05);
    tlx->Draw();
    gPad->Modified();
    gPad->Print(Form("plots/detresponse_fvtimenosig_5bptheta_sigvssb_%s_compAllBin.eps", "veto"));

/////////////////////////////
    //dummy TLegend
    TLegend* leg0 = new TLegend(.25, .62, 0.5, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.035);
    for (int isam=0;isam<2;isam++){
        leg0->AddEntry(pUncertaintyComb[isam], nameSample_long[isam],"pl");
    }
    leg0->SetFillStyle(0);
    
    //fv
    new TCanvas;
    pUncertaintyFV[0]->GetXaxis()->SetTitle("p-cos(#theta) bins");
    pUncertaintyFV[0]->GetYaxis()->SetTitle("Uncertainty");
    
    titleStyle(pUncertaintyFV[0]);
    pUncertaintyFV[0]->GetYaxis()->SetRangeUser(0,0.2);
    pUncertaintyFV[0]->Draw("APL");
    for (Int_t isam=1; isam<2; ++isam){
        pUncertaintyFV[isam]->Draw("PL same");
    }
    TLatex* tlx=new TLatex(0.42, 0.95,"Fiducial vol.");
    tlx->SetNDC(kTRUE); // <- use NDC coordinate
    tlx->SetTextSize(0.05);
    tlx->Draw();
    leg0->Draw("same");
    gPad->Modified();
    gPad->Print("plots/detresponse_fvtimenosig_alldet_5bptheta_fv_compSample.eps");
    
    //veto
    new TCanvas;
    pUncertaintyVeto[0]->GetXaxis()->SetTitle("p-cos(#theta) bins");
    pUncertaintyVeto[0]->GetYaxis()->SetTitle("Uncertainty");
    
    titleStyle(pUncertaintyVeto[0]);
    pUncertaintyVeto[0]->GetYaxis()->SetRangeUser(0,0.2);
    pUncertaintyVeto[0]->Draw("APL");
    for (Int_t isam=1; isam<2; ++isam){
        pUncertaintyVeto[isam]->Draw("PL same");
    }
    TLatex* tlx=new TLatex(0.42, 0.95,"Veto");
    tlx->SetNDC(kTRUE); // <- use NDC coordinate
    tlx->SetTextSize(0.05);
    tlx->Draw();
    leg0->Draw("same");
    gPad->Modified();
    gPad->Print("plots/detresponse_fvtimenosig_alldet_5bptheta_veto_compSample.eps");
    
    //comb
    new TCanvas;
    pUncertaintyComb[0]->GetXaxis()->SetTitle("p-cos(#theta) bins");
    pUncertaintyComb[0]->GetYaxis()->SetTitle("Uncertainty");
    
    titleStyle(pUncertaintyComb[0]);
    pUncertaintyComb[0]->GetYaxis()->SetRangeUser(0,0.2);
    pUncertaintyComb[0]->Draw("APL");
    for (Int_t isam=1; isam<2; ++isam){
        pUncertaintyComb[isam]->Draw("PL same");
    }
    TLatex* tlx=new TLatex(0.42, 0.95,"FV + Veto");
    tlx->SetNDC(kTRUE); // <- use NDC coordinate
    tlx->SetTextSize(0.05);
    tlx->Draw();
    leg0->Draw("same");
    gPad->Modified();
    gPad->Print("plots/detresponse_fvtimenosig_alldet_5bptheta_fvveto_compSample.eps");
    
    
    
}
