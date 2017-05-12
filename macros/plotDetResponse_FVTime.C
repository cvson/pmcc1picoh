{
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
    TFile *pFile = new TFile("../inputs/detresponse_FVTime.root");
    
    //this is consistent with XsecParameters
    //follow kikawa-scheme
    const Int_t NCUTTIMING = 3;
    const Int_t NCUTFV = 4;
    const Int_t NCUTVETO = 3;
    //histogram to fill
    TH1F* hdt_timing[NSAMPLE][NCUTTIMING];
    
    TH1F* hmc_fv[NSAMPLE][NCUTFV];
    TH1F* hdt_fv[NSAMPLE][NCUTFV];
    
    TH1F* hmc_veto[NSAMPLE][NCUTVETO];
    TH1F* hdt_veto[NSAMPLE][NCUTVETO];
    
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
        gPad->Print(Form("plots/detresponse_fvtime_dt_5bptheta_timing_sam%d.eps",isam));
        
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
        hdt_fv[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTFV; ++iindex) {
            hdt_fv[isam][iindex]->Draw("same");
        }
        gPad->Print(Form("plots/detresponse_fvtime_dt_5bptheta_fv_sam%d.eps",isam));
        
        new TCanvas;
        hmc_fv[isam][0]->SetMinimum(0);
        hmc_fv[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTFV; ++iindex) {
            hmc_fv[isam][iindex]->Draw("same");
        }
        gPad->Print(Form("plots/detresponse_fvtime_mc_5bptheta_fv_sam%d.eps",isam));
        
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
        hdt_veto[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTVETO; ++iindex) {
            hdt_veto[isam][iindex]->Draw("same");
        }
        gPad->Print(Form("plots/detresponse_fvtime_dt_5bptheta_veto_sam%d.eps",isam));
        
        new TCanvas;
        hmc_veto[isam][0]->SetMinimum(0);
        hmc_veto[isam][0]->Draw();
        for (Int_t iindex=1; iindex<NCUTVETO; ++iindex) {
            hmc_veto[isam][iindex]->Draw("same");
        }
        gPad->Print(Form("plots/detresponse_fvtime_mc_5bptheta_veto_sam%d.eps",isam));
        
    }
    //making TGraph
    
    
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
    gPad->Print("plots/detresponse_fvtime_alldet_5bptheta_fv_compSample.eps");
    
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
    gPad->Print("plots/detresponse_fvtime_alldet_5bptheta_veto_compSample.eps");
    
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
    gPad->Print("plots/detresponse_fvtime_alldet_5bptheta_fvveto_compSample.eps");
    
    
    
}
