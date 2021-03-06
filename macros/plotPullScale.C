void plotPullScale()
{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    TString subSaveName = "checkpullScale_2sam";
    const Int_t NPTHETABIN = 5;
    const Int_t NTOYFIT = 200;
    const Int_t NSAMPLE = 2;
    const char *m_name[] = {"SIG", "CRI"};
    const char *m_namelong[] = {"Signal", "Sideband"};
    TFile *pFile[NTOYFIT];
    string tagnom = "nominal";
    string tagthro = "thrown";
    string tagfit = "fit";

    const int NREACTION = 9;//10;
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall"};
    //
    for (Int_t itoy=0; itoy<NTOYFIT; ++itoy) {
        pFile[itoy] = new TFile(Form("../outputs/StatUn/two/fittoy_result_%d.root",itoy+1));
    }
    //fit result
    TH1D *hscalepara_thro[NTOYFIT];
    TH1D *hscalepara_bfit[NTOYFIT];
    TH1D *hscalepara[NTOYFIT];
    TH1D *hscalepara_err[NTOYFIT];
    //histo
    TH1D *hccqebin_rec_nom[NTOYFIT][NSAMPLE][NREACTION];//mc
    TH1D *hccqebin_rec_thro[NTOYFIT][NSAMPLE][NREACTION];//mc
    TH1D *hccqebin_rec_fit[NTOYFIT][NSAMPLE][NREACTION];//fit
    
    double nsigthro;
    double nsigtoyfit;
    double toyerror;
    
    for (Int_t itoy=0; itoy<NTOYFIT; ++itoy){
        hscalepara_thro[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_scale_iter0");
        hscalepara_bfit[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_scale_result");
        hscalepara[itoy] = (TH1D*)hscalepara_bfit[itoy]->Clone(Form("clone_scale%d",itoy));
        hscalepara_err[itoy] = (TH1D*)pFile[itoy]->Get("paramerrhist_parpar_scale_result");
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
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        hpullScalePara[ibin] = new TH1F(Form("hpullScalePara_bin%d",ibin),"",50,-50,50);
        for (Int_t itoy=0; itoy<NTOYFIT; ++itoy){
            nsigthro = hccqebin_rec_thro[itoy][0][0]->GetBinContent(ibin+1);
            nsigtoyfit = hccqebin_rec_fit[itoy][0][0]->GetBinContent(ibin+1);
            toyerror = nsigtoyfit - nsigthro;
            hpullScalePara[ibin]->Fill(toyerror);
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
    hccqebin_rec_nom[0][0][0]->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
    hccqebin_rec_nom[0][0][0]->GetYaxis()->SetTitle("Number of CC1#picoh events");
    plot2histdata(hccqebin_rec_nom[0][0][0],"Nominal MC",haverage_ccqebins_toyfit,"Average of toy fits",""+subSaveName+"_averageToySpec",0.25,0.71);
    
    //pull parameter distribution
    TH1F *hpullDist[NPTHETABIN];
    double pullVal;
    double gfmean[NPTHETABIN];
    double gfmeanerr[NPTHETABIN];
    double gfrms[NPTHETABIN];
    double gfrmserr[NPTHETABIN];
    double xpthetabin[NPTHETABIN];
    double xpthetabinerr[NPTHETABIN];
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
        if (ibin==0) {
            hpullDist[ibin]->Rebin(4);
        }
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
    
    popfile->Write();
    popfile->Close();
    
}
