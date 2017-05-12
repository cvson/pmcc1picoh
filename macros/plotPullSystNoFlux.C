void plotPullSystNoFlux()
{
    gROOT->ProcessLine(".x /home/t2k/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/t2k/cvson/basicPlotUtil.C");
    TString subSaveName = "checkpullSystNoFlux";
    const Int_t NPTHETABIN = 10;
    const Int_t NXSECPARA = 5;
    const Int_t NDETPARA = 40;//10x4 samples
    
    const Int_t NTOYFIT = 200;
    const Int_t NSAMPLE = 4;
    const char *m_name[] = {"SIG", "CRI"/*, "CRIIA", "CRIIB"*/, "CRIIC", "More2trk"};
    const char *m_namelong[] = {"Signal", "Control I"/*, "Control IIA", "Control IIB"*/, "Control IIC", "> two tracks"};
    TFile *pFile[NTOYFIT];
    string tagnom = "nominal";
    string tagthro = "thrown";
    string tagfit = "fit";

    const int NREACTION = 9;//10;
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall"};
    //
    for (Int_t itoy=0; itoy<NTOYFIT; ++itoy) {
        pFile[itoy] = new TFile(Form("../outputs/four/fittoy_result_%d.root",itoy+1));
    }
    //fit result
    TH1D *hscalepara_thro[NTOYFIT];
    TH1D *hscalepara_bfit[NTOYFIT];
    TH1D *hscalepara[NTOYFIT];
    TH1D *hscalepara_err[NTOYFIT];
    //x-sec
    TH1D *hxsecpara_thro[NTOYFIT];
    TH1D *hxsecpara_bfit[NTOYFIT];
    TH1D *hxsecpara[NTOYFIT];
    TH1D *hxsecpara_err[NTOYFIT];
    //det
    TH1D *hdetpara_thro[NTOYFIT];
    TH1D *hdetpara_bfit[NTOYFIT];
    TH1D *hdetpara[NTOYFIT];
    TH1D *hdetpara_err[NTOYFIT];
    
    //histo
    TH1D *hccqebin_rec_nom[NTOYFIT][NSAMPLE][NREACTION];//mc
    TH1D *hccqebin_rec_thro[NTOYFIT][NSAMPLE][NREACTION];//mc
    TH1D *hccqebin_rec_fit[NTOYFIT][NSAMPLE][NREACTION];//fit
    
    double nsigthro;
    double nsigtoyfit;
    double toyerror;
    
    for (Int_t itoy=0; itoy<NTOYFIT; ++itoy){
        //scale
        hscalepara_thro[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_scale_iter0");
        hscalepara_bfit[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_scale_result");
        hscalepara[itoy] = (TH1D*)hscalepara_bfit[itoy]->Clone(Form("clone_scale%d",itoy));
        hscalepara_err[itoy] = (TH1D*)pFile[itoy]->Get("paramerrhist_parpar_scale_result");
        //xsec
        hxsecpara_thro[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_xsec_iter0");
        hxsecpara_bfit[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_xsec_result");
        hxsecpara[itoy] = (TH1D*)hxsecpara_bfit[itoy]->Clone(Form("clone_xsec%d",itoy));
        hxsecpara_err[itoy] = (TH1D*)pFile[itoy]->Get("paramerrhist_parpar_xsec_result");
        
        //det
        hdetpara_thro[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_det_iter0");
        hdetpara_bfit[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_det_result");
        hdetpara[itoy] = (TH1D*)hdetpara_bfit[itoy]->Clone(Form("clone_det%d",itoy));
        hdetpara_err[itoy] = (TH1D*)pFile[itoy]->Get("paramerrhist_parpar_det_result");
        
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            for (Int_t ireac=0; ireac<NREACTION; ++ireac) {
                hccqebin_rec_nom[itoy][isam][ireac] = (TH1D*)pFile[itoy]->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tagnom.c_str()));
                hccqebin_rec_thro[itoy][isam][ireac] = (TH1D*)pFile[itoy]->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tagthro.c_str()));
                hccqebin_rec_fit[itoy][isam][ireac] = (TH1D*)pFile[itoy]->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tagfit.c_str()));
            }//end ireac
        }//end isam
        //difference between toy and fit
        /*nsigthro = hccqebin_rec_thro[itoy][0][0]->GetBinContent(10);
        nsigtoyfit = hccqebin_rec_fit[itoy][0][0]->GetBinContent(10);
        toyerror = nsigtoyfit - nsigthro;
        cout<<"TOY"<<itoy<<" THROW "<<nsigthro<<" FIT "<<nsigtoyfit<<" DIFF "<<toyerror<<endl;*/
    }//end itoy
    
    //check pull statistical error
    TFile *popfile = new TFile("../outputs/pullScalePara.root","RECREATE");
    TH1F *hpullScalePara[NPTHETABIN];
    TH1F *hUncertaintyPercentage[NPTHETABIN];
    double percentUncertainty;
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        hpullScalePara[ibin] = new TH1F(Form("hpullScalePara_bin%d",ibin),"",50,-50,50);
        hUncertaintyPercentage[ibin] = new TH1F(Form("hUncertaintyPercentage_bin%d",ibin),"",100,-100,100);
        for (Int_t itoy=0; itoy<NTOYFIT; ++itoy){
            nsigthro = hccqebin_rec_thro[itoy][0][0]->GetBinContent(ibin+1);
            nsigtoyfit = hccqebin_rec_fit[itoy][0][0]->GetBinContent(ibin+1);
            toyerror = nsigtoyfit - nsigthro;
            percentUncertainty = toyerror*100./float(nsigthro);
            hpullScalePara[ibin]->Fill(toyerror);
            hUncertaintyPercentage[ibin]->Fill(percentUncertainty);
        }
    }
    //make average
    TH1F *haverage_ccqebins_toyfit = (TH1F*)hccqebin_rec_fit[0][0][0]->Clone("haverage_ccqebins_toyfit");
    for (Int_t itoy=1; itoy<NTOYFIT; ++itoy) {
        haverage_ccqebins_toyfit->Add(hccqebin_rec_fit[itoy][0][0]);
    }
    haverage_ccqebins_toyfit->Scale(1/float(NTOYFIT));
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        haverage_ccqebins_toyfit->SetBinError(ibin+1,hpullScalePara[ibin]->GetRMS());
    }
    
    //plot pull each bin
    Int_t ci;
    
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        new TCanvas;
        //navy blue
        ci = TColor::GetColor("#0B3861");
        hpullScalePara[ibin]->GetXaxis()->SetTitle("N^{FIT}-N^{TOY} (CC1#picoh)");
        hpullScalePara[ibin]->GetYaxis()->SetTitle("Number of toys");
        hpullScalePara[ibin]->SetLineColor(ci);
        titleStyle(hpullScalePara[ibin]);
        hpullScalePara[ibin]->Fit("gaus");
        TF1 *g = hpullScalePara[ibin]->GetFunction("gaus");
        ci = TColor::GetColor("#B45F04");
        g->SetLineColor(ci);
        TLatex* tlx=new TLatex(0.42, 0.95,Form("Bin: %d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print("plots/"+subSaveName+Form("_bin%i.eps",ibin));
    }
    //plot percentage uncertainty each bin
    TH1F *hUncertaintyPercentageAll = (TH1F*)hccqebin_rec_nom[0][0][0]->Clone("hUncertaintyPercentageAll");
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        hUncertaintyPercentageAll->SetBinContent(ibin+1, hUncertaintyPercentage[ibin]->GetRMS());
        new TCanvas;
        //navy blue
        ci = TColor::GetColor("#0B3861");
        hUncertaintyPercentage[ibin]->GetXaxis()->SetTitle("(N^{FIT}-N^{TOY})/N^{TOY} (CC1#picoh)");
        hUncertaintyPercentage[ibin]->GetYaxis()->SetTitle("Number of toys");
        hUncertaintyPercentage[ibin]->SetLineColor(ci);
        titleStyle(hUncertaintyPercentage[ibin]);
        hUncertaintyPercentage[ibin]->Fit("gaus");
        TF1 *g = hUncertaintyPercentage[ibin]->GetFunction("gaus");
        ci = TColor::GetColor("#B45F04");
        g->SetLineColor(ci);
        TLatex* tlx=new TLatex(0.42, 0.95,Form("Bin: %d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print("plots/"+subSaveName+Form("_percentUncertainty_bin%i.eps",ibin));
    }
    //plot percentage uncertainty
    hUncertaintyPercentageAll->GetXaxis()->SetTitle("Scaling parameter");
    hUncertaintyPercentageAll->GetYaxis()->SetTitle("Uncertainty (%)");
    new TCanvas;
    hUncertaintyPercentageAll->SetTitle("");
    titleStyle(hUncertaintyPercentageAll);
    ci = TColor::GetColor("#0B3861");
    hUncertaintyPercentageAll->SetLineColor(ci);
    hUncertaintyPercentageAll->SetLineWidth(3);
    hUncertaintyPercentageAll->GetYaxis()->SetRangeUser(0,100);
    
    hUncertaintyPercentageAll->Draw();
    gPad->Print("plots/"+subSaveName+"_UncertaintyPercentage.eps");
    //
    hccqebin_rec_nom[0][0][0]->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
    hccqebin_rec_nom[0][0][0]->GetYaxis()->SetTitle("Number of CC1#picoh events");
    plot2histdata(hccqebin_rec_nom[0][0][0],"Nominal MC",haverage_ccqebins_toyfit,"Average of toy fits",""+subSaveName+"_averageToySpec",0.25,0.71);
    
    //pull parameter distribution
    //scale
    TH1F *hpullDist[NPTHETABIN];
    double pullVal;
    double gfmean[NPTHETABIN];
    double gfmeanerr[NPTHETABIN];
    double gfrms[NPTHETABIN];
    double gfrmserr[NPTHETABIN];
    double xpthetabin[NPTHETABIN];
    double xpthetabinerr[NPTHETABIN];
    //xsec
    TH1F *hpullDist_xsec[NXSECPARA];
    double gfmean_xsec[NXSECPARA];
    double gfmeanerr_xsec[NXSECPARA];
    double gfrms_xsec[NXSECPARA];
    double gfrmserr_xsec[NXSECPARA];
    double xxsec[NXSECPARA];
    double xxsecerr[NXSECPARA];
    //det
    TH1F *hpullDist_det[NDETPARA];
    double gfmean_det[NDETPARA];
    double gfmeanerr_det[NDETPARA];
    double gfrms_det[NDETPARA];
    double gfrmserr_det[NDETPARA];
    double xdet[NDETPARA];
    double xdeterr[NDETPARA];
    
    //scaling
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        xpthetabin[ibin] = ibin+0.5;
        xpthetabinerr[ibin] = 0;
        hpullDist[ibin] = new TH1F(Form("hpullDist_bin%d",ibin),"",100,-5,5);
        for (Int_t itoy=0; itoy<NTOYFIT; ++itoy) {
            double bfitVal = hscalepara_bfit[itoy]->GetBinContent(ibin+1);
            double bthroVal = hscalepara_thro[itoy]->GetBinContent(ibin+1);
            double efitVal = hscalepara_err[itoy]->GetBinContent(ibin+1);
            pullVal = (bfitVal-bthroVal)/efitVal;
            hpullDist[ibin]->Fill(pullVal);
        }
        new TCanvas;
        hpullDist[ibin]->Rebin(2);
        hpullDist[ibin]->Fit("gaus");
        TF1 *g2 = hpullDist[ibin]->GetFunction("gaus");
        ci = TColor::GetColor("#B45F04");
        g2->SetLineColor(ci);
        TLatex* tlx=new TLatex(0.42, 0.95,Form("ScalePara: %d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print("plots/"+subSaveName+Form("_scalepara%d.eps",ibin));
        gfmean[ibin] = g2->GetParameter(1);
        gfmeanerr[ibin] = g2->GetParError(1);
        gfrms[ibin] = g2->GetParameter(2);
        gfrmserr[ibin] = g2->GetParError(2);
        //cout<<"BIN "<<ibin<<" MEan "<<hpullDist[ibin]->GetMean()<<" RMS "<<hpullDist[ibin]->GetRMS()<<endl;
        cout<<"BIN "<<ibin<<" MEan "<<gfmean[ibin]<<" RMS "<<gfrms[ibin]<<endl;
    }
    TGraphErrors *gmean = new TGraphErrors(NPTHETABIN,xpthetabin,gfmean,xpthetabinerr,gfmeanerr);
    TGraphErrors *grms = new TGraphErrors(NPTHETABIN,xpthetabin,gfrms,xpthetabinerr,gfrmserr);
    
    //xsec
    for (Int_t ibin=0; ibin<NXSECPARA; ++ibin) {
        xxsec[ibin] = ibin+0.5;
        xxsecerr[ibin] = 0;
        hpullDist_xsec[ibin] = new TH1F(Form("hpullDist_xsec_bin%d",ibin),"",100,-5,5);
        for (Int_t itoy=0; itoy<NTOYFIT; ++itoy) {
            double bfitVal = hxsecpara_bfit[itoy]->GetBinContent(ibin+1);
            double bthroVal = hxsecpara_thro[itoy]->GetBinContent(ibin+1);
            double efitVal = hxsecpara_err[itoy]->GetBinContent(ibin+1);
            pullVal = (bfitVal-bthroVal)/efitVal;
            hpullDist_xsec[ibin]->Fill(pullVal);
        }
        new TCanvas;
        hpullDist_xsec[ibin]->Rebin(2);
        hpullDist_xsec[ibin]->Fit("gaus");
        TF1 *g2 = hpullDist_xsec[ibin]->GetFunction("gaus");
        ci = TColor::GetColor("#B45F04");
        g2->SetLineColor(ci);
        TLatex* tlx=new TLatex(0.42, 0.95,Form("X-sec Para: %d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print("plots/"+subSaveName+Form("_xsecpara%d.eps",ibin));
        gfmean_xsec[ibin] = g2->GetParameter(1);
        gfmeanerr_xsec[ibin] = g2->GetParError(1);
        gfrms_xsec[ibin] = g2->GetParameter(2);
        gfrmserr_xsec[ibin] = g2->GetParError(2);
        //cout<<"BIN "<<ibin<<" MEan "<<hpullDist_xsec[ibin]->GetMean()<<" RMS "<<hpullDist_xsec[ibin]->GetRMS()<<endl;
        cout<<"BIN "<<ibin<<" MEan "<<gfmean_xsec[ibin]<<" RMS "<<gfrms_xsec[ibin]<<endl;
    }
    TGraphErrors *gmean_xsec = new TGraphErrors(NXSECPARA,xxsec,gfmean_xsec,xxsecerr,gfmeanerr_xsec);
    TGraphErrors *grms_xsec = new TGraphErrors(NXSECPARA,xxsec,gfrms_xsec,xxsecerr,gfrmserr_xsec);
    
    //det
    for (Int_t ibin=0; ibin<NDETPARA; ++ibin) {
        xdet[ibin] = ibin+0.5;
        xdeterr[ibin] = 0;
        hpullDist_det[ibin] = new TH1F(Form("hpullDist_det_bin%d",ibin),"",100,-5,5);
        for (Int_t itoy=0; itoy<NTOYFIT; ++itoy) {
            double bfitVal = hdetpara_bfit[itoy]->GetBinContent(ibin+1);
            double bthroVal = hdetpara_thro[itoy]->GetBinContent(ibin+1);
            double efitVal = hdetpara_err[itoy]->GetBinContent(ibin+1);
            pullVal = (bfitVal-bthroVal)/efitVal;
            hpullDist_det[ibin]->Fill(pullVal);
        }
        new TCanvas;
        hpullDist_det[ibin]->Rebin(2);
        hpullDist_det[ibin]->Fit("gaus");
        TF1 *g2 = hpullDist_det[ibin]->GetFunction("gaus");
        ci = TColor::GetColor("#B45F04");
        g2->SetLineColor(ci);
        TLatex* tlx=new TLatex(0.42, 0.95,Form("Det Para: %d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print("plots/"+subSaveName+Form("_detpara%d.eps",ibin));
        gfmean_det[ibin] = g2->GetParameter(1);
        gfmeanerr_det[ibin] = g2->GetParError(1);
        gfrms_det[ibin] = g2->GetParameter(2);
        gfrmserr_det[ibin] = g2->GetParError(2);
        //cout<<"BIN "<<ibin<<" MEan "<<hpullDist_det[ibin]->GetMean()<<" RMS "<<hpullDist_det[ibin]->GetRMS()<<endl;
        cout<<"BIN "<<ibin<<" MEan "<<gfmean_det[ibin]<<" RMS "<<gfrms_det[ibin]<<endl;
    }
    TGraphErrors *gmean_det = new TGraphErrors(NDETPARA,xdet,gfmean_det,xdeterr,gfmeanerr_det);
    TGraphErrors *grms_det = new TGraphErrors(NDETPARA,xdet,gfrms_det,xdeterr,gfrmserr_det);
    
    //scale
    new TCanvas;
    ci = TColor::GetColor("#0B3861");
    gmean->SetLineColor(ci);
    gmean->SetMarkerColor(ci);
    gmean->SetMarkerStyle(8);
    gmean->SetMarkerSize(1.2);
    gmean->SetLineWidth(3);
    ci = TColor::GetColor("#B45F04");
    grms->SetLineColor(ci);
    grms->SetMarkerColor(ci);
    grms->SetMarkerStyle(8);
    grms->SetMarkerSize(1.2);
    grms->SetLineWidth(3);
    titleStyle(grms);
    grms->GetYaxis()->SetTitle("Mean and Standard deviation");
    grms->GetXaxis()->SetTitle("Scaling parameters");
    grms->Draw("AP");
    grms->GetYaxis()->SetRangeUser(-1,2);
    gmean->Draw("P sames");
    TLegend* leg0 = new TLegend(.22, .74, 0.44, .89);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.04);
    leg0->AddEntry(gmean, "Mean", "ep");
    leg0->AddEntry(grms, "Standard deviation", "ep");
    leg0->SetFillStyle(0);
    leg0->Draw();
    gPad->Modified();
    gPad->Print("plots/"+subSaveName+"_fitdist.eps");
    
    //x-sec
    new TCanvas;
    ci = TColor::GetColor("#0B3861");
    gmean_xsec->SetLineColor(ci);
    gmean_xsec->SetMarkerColor(ci);
    gmean_xsec->SetMarkerStyle(8);
    gmean_xsec->SetMarkerSize(1.2);
    gmean_xsec->SetLineWidth(3);
    ci = TColor::GetColor("#B45F04");
    grms_xsec->SetLineColor(ci);
    grms_xsec->SetMarkerColor(ci);
    grms_xsec->SetMarkerStyle(8);
    grms_xsec->SetMarkerSize(1.2);
    grms_xsec->SetLineWidth(3);
    titleStyle(grms_xsec);
    grms_xsec->GetYaxis()->SetTitle("Mean and Standard deviation");
    grms_xsec->GetXaxis()->SetTitle("X-Sec parameters");
    grms_xsec->Draw("AP");
    grms_xsec->GetYaxis()->SetRangeUser(-1,2);
    gmean_xsec->Draw("P sames");
    leg0->Draw();
    gPad->Modified();
    gPad->Print("plots/"+subSaveName+"_xsec_fitdist.eps");
    //det
    new TCanvas;
    ci = TColor::GetColor("#0B3861");
    gmean_det->SetLineColor(ci);
    gmean_det->SetMarkerColor(ci);
    gmean_det->SetMarkerStyle(8);
    gmean_det->SetMarkerSize(1.2);
    gmean_det->SetLineWidth(3);
    ci = TColor::GetColor("#B45F04");
    grms_det->SetLineColor(ci);
    grms_det->SetMarkerColor(ci);
    grms_det->SetMarkerStyle(8);
    grms_det->SetMarkerSize(1.2);
    grms_det->SetLineWidth(3);
    titleStyle(grms_det);
    grms_det->GetYaxis()->SetTitle("Mean and Standard deviation");
    grms_det->GetXaxis()->SetTitle("Detector parameters");
    grms_det->Draw("AP");
    grms_det->GetYaxis()->SetRangeUser(-1,2);
    gmean_det->Draw("P sames");
    leg0->Draw();
    gPad->Modified();
    gPad->Print("plots/"+subSaveName+"_det_fitdist.eps");
    
    popfile->Write();
    popfile->Close();
    
}
