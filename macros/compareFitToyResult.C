{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    const Int_t NFIT2COMP = 4;
    
    TFile *pFile[NFIT2COMP];
    /*pFile[0] = new TFile("../outputs/testFit_onesample_halfcc1pi.root");
    pFile[1] = new TFile("../outputs/testFit_twosample_halfcc1pi.root");
    pFile[2] = new TFile("../outputs/testFit_threesample_halfcc1pi.root");
    pFile[3] = new TFile("../outputs/testFit_foursample_halfcc1pi.root");*/
    
    TString subbin = "newbin2";
    pFile[0] = new TFile("../outputs/testFit_onesample_halfcc1pi_"+subbin+".root");
    pFile[1] = new TFile("../outputs/testFit_twosample_halfcc1pi_"+subbin+".root");
    pFile[2] = new TFile("../outputs/testFit_threesample_halfcc1pi_"+subbin+".root");
    pFile[3] = new TFile("../outputs/testFit_foursample_halfcc1pi_"+subbin+".root");
    
    
    const char *pcolor[NFIT2COMP]={"#9E5DAB", "#95BD56","#A35540","#7E9B99"};
    const char *pname[NFIT2COMP]={"Signal", "Signal & 1*CR","Signal & 2*CR", "Signal & 3*CR"};
    
    TH1D *hscalepara_bfit[NFIT2COMP];
    TH1D *hscalepara[NFIT2COMP];
    TH1D *hscalepara_err[NFIT2COMP];
    
    TH1D *hfluxpara_bfit[NFIT2COMP];
    TH1D *hfluxpara[NFIT2COMP];
    TH1D *hfluxpara_err[NFIT2COMP];
    Int_t icolor;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        icolor = TColor::GetColor(pcolor[isam]);
        hscalepara_bfit[isam] = (TH1D*)pFile[isam]->Get("paramhist_parpar_scale_result");
        hscalepara[isam] = (TH1D*)hscalepara_bfit[isam]->Clone(Form("clone_scale%d",isam));
        hscalepara_err[isam] = (TH1D*)pFile[isam]->Get("paramerrhist_parpar_scale_result");
        
        hfluxpara_bfit[isam] = (TH1D*)pFile[isam]->Get("paramhist_parpar_flux_result");
        hfluxpara[isam] = (TH1D*)hfluxpara_bfit[isam]->Clone(Form("clone_flux%d",isam));
        hfluxpara_err[isam] = (TH1D*)pFile[isam]->Get("paramerrhist_parpar_flux_result");
        
        hscalepara_bfit[isam]->SetLineColor(icolor);
        hscalepara[isam]->SetLineColor(icolor);
        hfluxpara[isam]->SetLineColor(icolor);
        hscalepara_err[isam]->SetLineColor(icolor);
        hfluxpara_bfit[isam]->SetLineColor(icolor);
        hfluxpara_err[isam]->SetLineColor(icolor);
        
        hscalepara_bfit[isam]->SetLineWidth(3);
        hscalepara_err[isam]->SetLineWidth(3);
        hfluxpara_bfit[isam]->SetLineWidth(3);
        hfluxpara_err[isam]->SetLineWidth(3);
        hscalepara[isam]->SetLineWidth(3);
        hfluxpara[isam]->SetLineWidth(3);
    }
    //set error for histogram
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        for (Int_t ibin = 0; ibin<hscalepara[isam]->GetNbinsX(); ++ibin){
            double ibscaleerr = hscalepara_err[isam]->GetBinContent(ibin+1);
            hscalepara[isam]->SetBinError(ibin+1, ibscaleerr);
            
            double ibfluxerr = hfluxpara_err[isam]->GetBinContent(ibin+1);
            hfluxpara[isam]->SetBinError(ibin+1, ibfluxerr);
        }
    }
    //TLEGEND
    new TCanvas;
    TLegend* leg0 = new TLegend(.2, .6, 0.45, .85);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.045);
    
    for (Int_t isam=0;isam<NFIT2COMP;isam++){
        leg0->AddEntry(hscalepara_bfit[isam], pname[isam],"l");
        
    }
    leg0->SetFillStyle(0);
    
    //with error scale parameter
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hscalepara[isam]->SetTitle("");
            hscalepara[isam]->GetYaxis()->SetRangeUser(0.,2.0);
            hscalepara[isam]->GetYaxis()->SetTitle("Parameter best-fit");
            titleStyle(hscalepara[isam]);
            hscalepara[isam]->Draw();
        }
        else hscalepara[isam]->Draw("same");
    }
    leg0->Draw();
    gPad->Print("plots/compfittoyresult_scalepara_"+subbin+".eps");
    
    // with error flux parameter
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hfluxpara[isam]->SetTitle("");
            hfluxpara[isam]->GetYaxis()->SetRangeUser(0.,2.0);
            hfluxpara[isam]->GetYaxis()->SetTitle("Parameter best-fit");
            titleStyle(hfluxpara[isam]);
            hfluxpara[isam]->Draw();
        }
        else hfluxpara[isam]->Draw("same");
    }
    leg0->Draw();
    gPad->Print("plots/compfittoyresult_fluxpara_"+subbin+".eps");
    
    //plotmultiTH1(NFIT2COMP,hscalepara_bfit,"hscalepara_bfit");
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hscalepara_bfit[isam]->SetTitle("");
            hscalepara_bfit[isam]->GetYaxis()->SetRangeUser(0.5999,0.6001);
            hscalepara_bfit[isam]->GetYaxis()->SetTitle("Parameter best-fit");
            titleStyle(hscalepara_bfit[isam]);
            hscalepara_bfit[isam]->Draw();
        }
        else hscalepara_bfit[isam]->Draw("same");
    }
    leg0->Draw();
    gPad->Print("plots/compfittoyresult_calepara_bfit_"+subbin+".eps");
    
    //
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hscalepara_err[isam]->SetTitle("");
            hscalepara_err[isam]->GetYaxis()->SetRangeUser(0.0,0.7);
            hscalepara_err[isam]->GetYaxis()->SetTitle("Parameter uncertainty");
            titleStyle(hscalepara_err[isam]);
            hscalepara_err[isam]->Draw();
        }
        else hscalepara_err[isam]->Draw("same");
    }
    leg0->SetX1(0.25);
    leg0->SetX2(0.50);
    leg0->Draw();
    gPad->Print("plots/compfittoyresult_scalepara_err_"+subbin+".eps");
    //
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hfluxpara_bfit[isam]->SetTitle("");
            hfluxpara_bfit[isam]->GetYaxis()->SetRangeUser(0.9999,1.0001);
            hfluxpara_bfit[isam]->GetYaxis()->SetTitle("Parameter best-fit");
            titleStyle(hfluxpara_bfit[isam]);
            hfluxpara_bfit[isam]->Draw();
        }
        else hfluxpara_bfit[isam]->Draw("same");
    }
    leg0->SetX1(0.2);
    leg0->SetX2(0.45);
    leg0->Draw();
    gPad->Print("plots/compfittoyresult_fluxpara_bfit_"+subbin+".eps");
    //
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hfluxpara_err[isam]->SetTitle("");
            hfluxpara_err[isam]->GetYaxis()->SetRangeUser(0.0,0.7);
            hfluxpara_err[isam]->GetYaxis()->SetTitle("Parameter uncertainty");
            titleStyle(hfluxpara_err[isam]);
            hfluxpara_err[isam]->Draw();
        }
        else hfluxpara_err[isam]->Draw("same");
    }
    
    leg0->Draw();
    gPad->Print("plots/compfittoyresult_fluxpara_err_"+subbin+".eps");
    
}