{
    gROOT->ProcessLine(".x /Users/soncao/rootlogon.C");
    gROOT->ProcessLine(".L /Users/soncao/basicPlotUtil.C");
    const Int_t NFIT2COMP = 6;
    
    TFile *pFile[NFIT2COMP];
    /*pFile[0] = new TFile("../outputs/testFit_onesample_halfcc1pi.root");
    pFile[1] = new TFile("../outputs/testFit_twosample_halfcc1pi.root");
    pFile[2] = new TFile("../outputs/testFit_threesample_halfcc1pi.root");
    pFile[3] = new TFile("../outputs/testFit_foursample_halfcc1pi.root");*/
    
    TString subbin = "newbin2_wxsecpara_fixcov";
    pFile[0] = new TFile("../outputs/testFit_onesample_halfcc1pi_"+subbin+".root");
    pFile[1] = new TFile("../outputs/testFit_twosample_halfcc1pi_"+subbin+".root");
    pFile[2] = new TFile("../outputs/testFit_threesample_halfcc1pi_"+subbin+".root");
    pFile[3] = new TFile("../outputs/testFit_foursample_halfcc1pi_"+subbin+".root");
    pFile[4] = new TFile("../outputs/testFit_fivesample_halfcc1pi_"+subbin+".root");
    pFile[5] = new TFile("../outputs/testFit_sixsample_halfcc1pi_"+subbin+".root");
    
    const char *pcolor[NFIT2COMP]={"#4F4342", "#85C85B", "#A563B7", "#C14F4C", "#94B8B8", "#B99647"};
    const char *pname[NFIT2COMP]={"Signal", "Signal & 1*CR","Signal & 2*CR", "Signal & 3*CR", "Signal & 4*CR", "Signal & 5*CR"};
    
    TH1D *hscalepara_bfit[NFIT2COMP];
    TH1D *hscalepara[NFIT2COMP];
    TH1D *hscalepara_err[NFIT2COMP];
    
    TH1D *hfluxpara_bfit[NFIT2COMP];
    TH1D *hfluxpara[NFIT2COMP];
    TH1D *hfluxpara_err[NFIT2COMP];
    
    TH1D *hxsecpara_bfit[NFIT2COMP];
    TH1D *hxsecpara[NFIT2COMP];
    TH1D *hxsecpara_err[NFIT2COMP];
    
    Int_t icolor;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        icolor = TColor::GetColor(pcolor[isam]);
        hscalepara_bfit[isam] = (TH1D*)pFile[isam]->Get("paramhist_parpar_scale_result");
        hscalepara[isam] = (TH1D*)hscalepara_bfit[isam]->Clone(Form("clone_scale%d",isam));
        hscalepara_err[isam] = (TH1D*)pFile[isam]->Get("paramerrhist_parpar_scale_result");
        
        hfluxpara_bfit[isam] = (TH1D*)pFile[isam]->Get("paramhist_parpar_flux_result");
        hfluxpara[isam] = (TH1D*)hfluxpara_bfit[isam]->Clone(Form("clone_flux%d",isam));
        hfluxpara_err[isam] = (TH1D*)pFile[isam]->Get("paramerrhist_parpar_flux_result");
        
        hxsecpara_bfit[isam] = (TH1D*)pFile[isam]->Get("paramhist_parpar_xsec_result");
        hxsecpara[isam] = (TH1D*)hxsecpara_bfit[isam]->Clone(Form("clone_xsec%d",isam));
        hxsecpara_err[isam] = (TH1D*)pFile[isam]->Get("paramerrhist_parpar_xsec_result");
        
        hscalepara_bfit[isam]->SetLineColor(icolor);
        hscalepara[isam]->SetLineColor(icolor);
        hscalepara_err[isam]->SetLineColor(icolor);
        
        hfluxpara_bfit[isam]->SetLineColor(icolor);
        hfluxpara_err[isam]->SetLineColor(icolor);
        hfluxpara[isam]->SetLineColor(icolor);

        
        hscalepara_bfit[isam]->SetLineWidth(3);
        hscalepara_err[isam]->SetLineWidth(3);
        hscalepara[isam]->SetLineWidth(3);
        
        hfluxpara_bfit[isam]->SetLineWidth(3);
        hfluxpara_err[isam]->SetLineWidth(3);
        hfluxpara[isam]->SetLineWidth(3);
        
        hxsecpara_bfit[isam]->SetLineColor(icolor);
        hxsecpara_err[isam]->SetLineColor(icolor);
        hxsecpara[isam]->SetLineColor(icolor);
        hxsecpara_bfit[isam]->SetLineWidth(3);
        hxsecpara_err[isam]->SetLineWidth(3);
        hxsecpara[isam]->SetLineWidth(3);
    }
    //set error for histogram
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        for (Int_t ibin = 0; ibin<hscalepara[isam]->GetNbinsX(); ++ibin){
            double ibscaleerr = hscalepara_err[isam]->GetBinContent(ibin+1);
            hscalepara[isam]->SetBinError(ibin+1, ibscaleerr);
            
            double ibfluxerr = hfluxpara_err[isam]->GetBinContent(ibin+1);
            hfluxpara[isam]->SetBinError(ibin+1, ibfluxerr);
            
            double ibxsecerr = hxsecpara_err[isam]->GetBinContent(ibin+1);
            hxsecpara[isam]->SetBinError(ibin+1, ibxsecerr);
        }
    }
    //TLEGEND
    new TCanvas;
    TLegend* leg0 = new TLegend(.2, .6, 0.45, .85);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.037);
    
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
    gPad->Print("plots/allcompfittoyresult_scalepara_"+subbin+".eps");
    
    // with error flux parameter
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hfluxpara[isam]->SetTitle("");
            hfluxpara[isam]->GetYaxis()->SetRangeUser(0.,2.0);
            hfluxpara[isam]->GetYaxis()->SetTitle("Parameter best-fit ");
            titleStyle(hfluxpara[isam]);
            hfluxpara[isam]->Draw();
        }
        else hfluxpara[isam]->Draw("same");
    }
    leg0->Draw();
    gPad->Print("plots/allcompfittoyresult_fluxpara_"+subbin+".eps");
    
    // with error xsec parameter
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hxsecpara[isam]->SetTitle("");
            hxsecpara[isam]->GetYaxis()->SetRangeUser(-2.0,2.0);
            hxsecpara[isam]->GetYaxis()->SetTitle("Parameter best-fit (#sigma shifted)");
            titleStyle(hxsecpara[isam]);
            hxsecpara[isam]->Draw();
        }
        else hxsecpara[isam]->Draw("same");
    }
    leg0->Draw();
    gPad->Print("plots/allcompfittoyresult_xsecpara_"+subbin+".eps");
    
    //plotmultiTH1(NFIT2COMP,hscalepara_bfit,"hscalepara_bfit");
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hscalepara_bfit[isam]->SetTitle("");
            hscalepara_bfit[isam]->GetYaxis()->SetRangeUser(0,1.2);
            hscalepara_bfit[isam]->GetYaxis()->SetTitle("Parameter best-fit");
            titleStyle(hscalepara_bfit[isam]);
            hscalepara_bfit[isam]->Draw();
        }
        else hscalepara_bfit[isam]->Draw("same");
    }
    leg0->SetX1(0.40);
    leg0->SetX2(0.60);
    leg0->SetY1(0.25);
    leg0->SetY2(0.60);
    leg0->Draw();
    gPad->Print("plots/allcompfittoyresult_calepara_bfit_"+subbin+".eps");
    
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
    leg0->SetX1(0.65);
    leg0->SetX2(0.85);
    leg0->SetY1(0.53);
    leg0->SetY2(0.88);
    leg0->Draw();
    gPad->Print("plots/allcompfittoyresult_scalepara_err_"+subbin+".eps");
    //
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hfluxpara_bfit[isam]->SetTitle("");
            hfluxpara_bfit[isam]->GetYaxis()->SetRangeUser(0.5,1.2);
            hfluxpara_bfit[isam]->GetYaxis()->SetTitle("Parameter best-fit ");
            titleStyle(hfluxpara_bfit[isam]);
            hfluxpara_bfit[isam]->Draw();
        }
        else hfluxpara_bfit[isam]->Draw("same");
    }
    leg0->SetX1(0.2);
    leg0->SetX2(0.45);
    leg0->SetY1(0.25);
    leg0->SetY2(0.60);
    leg0->Draw();
    gPad->Print("plots/allcompfittoyresult_fluxpara_bfit_"+subbin+".eps");
    //
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hfluxpara_err[isam]->SetTitle("");
            hfluxpara_err[isam]->GetYaxis()->SetRangeUser(0.0,0.7);
            hfluxpara_err[isam]->GetYaxis()->SetTitle("Parameter uncertainty ");
            titleStyle(hfluxpara_err[isam]);
            hfluxpara_err[isam]->Draw();
        }
        else hfluxpara_err[isam]->Draw("same");
    }
    leg0->SetY1(0.53);
    leg0->SetY2(0.88);
    
    leg0->Draw();
    gPad->Print("plots/allcompfittoyresult_fluxpara_err_"+subbin+".eps");
    
    
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hxsecpara_bfit[isam]->SetTitle("");
            hxsecpara_bfit[isam]->GetYaxis()->SetRangeUser(-0.5,0.7);
            hxsecpara_bfit[isam]->GetYaxis()->SetTitle("Parameter best-fit (#sigma shifted)");
            titleStyle(hxsecpara_bfit[isam]);
            hxsecpara_bfit[isam]->Draw();
        }
        else hxsecpara_bfit[isam]->Draw("same");
    }
    leg0->SetX1(0.2);
    leg0->SetX2(0.45);
    leg0->Draw();
    gPad->Print("plots/allcompfittoyresult_xsecpara_bfit_"+subbin+".eps");
    //
    new TCanvas;
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        if (isam==0){
            hxsecpara_err[isam]->SetTitle("");
            hxsecpara_err[isam]->GetYaxis()->SetRangeUser(0.0,2.0);
            hxsecpara_err[isam]->GetYaxis()->SetTitle("Parameter uncertainty (#sigma)");
            titleStyle(hxsecpara_err[isam]);
            hxsecpara_err[isam]->Draw();
        }
        else hxsecpara_err[isam]->Draw("same");
    }
    
    leg0->Draw();
    gPad->Print("plots/allcompfittoyresult_xsecpara_err_"+subbin+".eps");
    
    //plot covariance matrix
    TMatrixDSym *pMatrix;
    float cov_mat_all[58][58];
    float cov_mat_scale[10][10];
    float cov_mat_flux[43][43];
    float cov_mat_xsec[5][5];
    TH2F *hall[NFIT2COMP];//
    TH2F *hscale[NFIT2COMP];//
    TH2F *hflux[NFIT2COMP];//
    TH2F *hxec[NFIT2COMP];//
    TString savename;
    TLatex* tlx;
    const char *parnames[5] = {"MACCQE","MAres","CC1piE0","CC1piE1","CCother"};
    for (Int_t isam = 0; isam<NFIT2COMP; ++isam){
        hall[isam]=new TH2F(Form("hall%d",isam),"",58,0,58,58,0,58);
        hscale[isam]=new TH2F(Form("hscale%d",isam),"",10,0,10,10,0,10);
        hflux[isam]=new TH2F(Form("hflux%d",isam),"",43,0,43,43,0,43);
        hxec[isam]=new TH2F(Form("hxec%d",isam),"",5,0,5,5,0,5);
        
        pMatrix = (TMatrixDSym*)pFile[isam]->Get("res_cov_matrix");
        cout<<"Get DIM "<<pMatrix->GetNrows()<<endl;
        
        for(int i=0; i<58; i++){
            for(int j=0; j<58; j++){
                cov_mat_all[i][j] = (*pMatrix)(i, j);
                hall[isam]->Fill(i+0.0001,j+0.0001,cov_mat_all[i][j]);
            }
        }
        
        for(int i=0; i<10; i++){
            for(int j=0; j<10; j++){
                cov_mat_scale[i][j] = (*pMatrix)(i, j);
                hscale[isam]->Fill(i+0.0001,j+0.0001,cov_mat_scale[i][j]);
            }
        }
        for(int i=0; i<43; i++){
            for(int j=0; j<43; j++){
                cov_mat_flux[i][j] = (*pMatrix)(i+10, j+10);
                hflux[isam]->Fill(i+0.0001,j+0.0001,cov_mat_flux[i][j]);
            }
        }
        for(int i=0; i<5; i++){
            for(int j=0; j<5; j++){
                cov_mat_xsec[i][j] = (*pMatrix)(i+53, j+53);
                hxec[isam]->Fill(i+0.0001,j+0.0001,cov_mat_xsec[i][j]);
                hxec[isam]->GetXaxis()->SetBinLabel(i+1,TString(parnames[i]));
                hxec[isam]->GetYaxis()->SetBinLabel(j+1,TString(parnames[j]));
            }
        }
        
        
        gStyle->SetPadRightMargin(0.15);
        gStyle->SetOptStat(0);
        gStyle->SetLineWidth(2);
        TGaxis::SetMaxDigits(3);
        
        new TCanvas;
        titleStyle2D(hall[isam]);
        hall[isam]->Draw("colz");
        savename = Form("toydata_cov_matrix_all_%dsample",isam+1);
        tlx=new TLatex(0.42, 0.95,Form("%s",pname[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Print("plots/"+savename+".eps");
        
        new TCanvas;
        titleStyle2D(hscale[isam]);
        hscale[isam]->Draw("colz");
        savename = Form("toydata_cov_matrix_scale_%dsample",isam+1);
        tlx=new TLatex(0.42, 0.95,Form("%s",pname[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Print("plots/"+savename+".eps");
        
        new TCanvas;
        titleStyle2D(hflux[isam]);
        hflux[isam]->Draw("colz");
        savename = Form("toydata_cov_matrix_flux_%dsample",isam+1);
        tlx=new TLatex(0.42, 0.95,Form("%s",pname[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Print("plots/"+savename+".eps");
        
        new TCanvas;
        titleStyle2D(hxec[isam]);
        hxec[isam]->Draw("colz");
        savename = Form("toydata_cov_matrix_xsec_%dsample",isam+1);
        tlx=new TLatex(0.42, 0.95,Form("%s",pname[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Print("plots/"+savename+".eps");
        
        
    }

    
}