void t2kpre_plotPullSyst()
{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    //TString subSaveName = "checkpull_statonly_2sam";
    //TString subSaveName = "checkpull_fluxonlystatfluc_1sam";
    //TString subSaveName = "checkpull_fluxonlynostat_2sam";
    //TString subSaveName = "checkpull_xseconlynostat_2sam";
   // TString subSaveName = "checkpull_detonlynostat_1sam";
   // TString subSaveName = "checkpull_allsystnostat_2sam";
  // TString subSaveName = "checkpull_allsyststatfluc_1sam";
   //TString subSaveName = "checkpullpiless02cor_xseconlynostat_2sam";
   // TString subSaveName = "checkpullpiless02cor_allsystnostat_2sam";
  // TString subSaveName = "checkpullpiless02cor_allsyststatfluc_1sam";
     TString subSaveName = "checkpullpiless02cor_xsecfluxnostat_2sam";
    const Bool_t isXsecInclude = true;
    const Bool_t isDetInclude = false;
    const Bool_t isFluxInclude = true;

    const Int_t NPTHETABIN = 5;
    const Int_t NXSECPARA = 7;//8;
    const Int_t NDETPARA = 10;//10;//5x2 samples
    const Int_t NFLUXPARA = 43;
    
    const Int_t NTOYFIT = 500;
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
        pFile[itoy] = new TFile(Form("../outputs/XsecFlux/twopiless02cor/fittoy_result_%d.root",itoy+1));
	//pFile[itoy] = new TFile(Form("../outputs/AllSystStatFluc/onepiless02cor/fittoy_result_%d.root",itoy+1));
        //pFile[itoy] = new TFile(Form("../outputs/AllSystStatFluc/one/fittoy_result_%d.root",itoy+1));
        //pFile[itoy] = new TFile(Form("../outputs/AllSyst/twopiless02cor/fittoy_result_%d.root",itoy+1));
        //pFile[itoy] = new TFile(Form("../outputs/AllSyst/two/fittoy_result_%d.root",itoy+1));
        //pFile[itoy] = new TFile(Form("../outputs/DetOnly/one/fittoy_result_%d.root",itoy+1));
        //pFile[itoy] = new TFile(Form("../outputs/XsecOnly/two/fittoy_result_%d.root",itoy+1));
	//pFile[itoy] = new TFile(Form("../outputs/FluxOnlyStatFluc/one/fittoy_result_%d.root",itoy+1));
   	 // pFile[itoy] = new TFile(Form("../outputs/FluxOnly/two/fittoy_result_%d.root",itoy+1));
         //pFile[itoy] = new TFile(Form("../outputs/XsecOnly/twopiless02cor/fittoy_result_%d.root",itoy+1));
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
    
    //flux
    TH1D *hfluxpara_thro[NTOYFIT];
    TH1D *hfluxpara_bfit[NTOYFIT];
    TH1D *hfluxpara[NTOYFIT];
    TH1D *hfluxpara_err[NTOYFIT];
    
    //histo
    TH1D *hccqebin_rec_nom[NTOYFIT][NSAMPLE][NREACTION];//mc
    TH1D *hccqebin_rec_thro[NTOYFIT][NSAMPLE][NREACTION];//mc
    TH1D *hccqebin_rec_fit[NTOYFIT][NSAMPLE][NREACTION];//fit
   
    //background
    TH1D *hccqebin_rec_nom_bkg[NTOYFIT][NSAMPLE];//mc
    TH1D *hccqebin_rec_thro_bkg[NTOYFIT][NSAMPLE];//thro
    TH1D *hccqebin_rec_fit_bkg[NTOYFIT][NSAMPLE]];//fit
     
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
        if(isXsecInclude==true){
        hxsecpara_thro[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_xsec_iter0");
        hxsecpara_bfit[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_xsec_result");
        hxsecpara[itoy] = (TH1D*)hxsecpara_bfit[itoy]->Clone(Form("clone_xsec%d",itoy));
        hxsecpara_err[itoy] = (TH1D*)pFile[itoy]->Get("paramerrhist_parpar_xsec_result");
        }

        //det
        if(isDetInclude==true){
        hdetpara_thro[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_det_iter0");
        hdetpara_bfit[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_det_result");
        hdetpara[itoy] = (TH1D*)hdetpara_bfit[itoy]->Clone(Form("clone_det%d",itoy));
        hdetpara_err[itoy] = (TH1D*)pFile[itoy]->Get("paramerrhist_parpar_det_result");
        }

        //flux
        if(isFluxInclude==true){
        hfluxpara_thro[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_flux_iter0");
        hfluxpara_bfit[itoy] = (TH1D*)pFile[itoy]->Get("paramhist_parpar_flux_result");
        hfluxpara[itoy] = (TH1D*)hfluxpara_bfit[itoy]->Clone(Form("clone_flux%d",itoy));
        hfluxpara_err[itoy] = (TH1D*)pFile[itoy]->Get("paramerrhist_parpar_flux_result");
        }

        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            for (Int_t ireac=0; ireac<NREACTION; ++ireac) {
                hccqebin_rec_nom[itoy][isam][ireac] = (TH1D*)pFile[itoy]->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tagnom.c_str()));
                hccqebin_rec_thro[itoy][isam][ireac] = (TH1D*)pFile[itoy]->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tagthro.c_str()));
                hccqebin_rec_fit[itoy][isam][ireac] = (TH1D*)pFile[itoy]->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tagfit.c_str()));
                //background
                
            }//end ireac
        }//end isam
        //difference between toy and fit
        /*nsigthro = hccqebin_rec_thro[itoy][0][0]->GetBinContent(10);
        nsigtoyfit = hccqebin_rec_fit[itoy][0][0]->GetBinContent(10);
        toyerror = nsigtoyfit - nsigthro;
        cout<<"TOY"<<itoy<<" THROW "<<nsigthro<<" FIT "<<nsigtoyfit<<" DIFF "<<toyerror<<endl;*/
    }//end itoy
    //background
    for (Int_t itoy=0; itoy<NTOYFIT; ++itoy){
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            hccqebin_rec_nom_bkg[itoy][isam] = (TH1D*)hccqebin_rec_nom[itoy][isam][1]->Clone(Form("hccqebin_rec_nom_bkg_toy%d_sam%d",itoy,isam));
            hccqebin_rec_thro_bkg[itoy][isam] = (TH1D*)hccqebin_rec_thro[itoy][isam][1]->Clone(Form("hccqebin_rec_thro_bkg_toy%d_sam%d",itoy,isam));
            hccqebin_rec_fit_bkg[itoy][isam] = (TH1D*)hccqebin_rec_fit[itoy][isam][1]->Clone(Form("hccqebin_rec_fit_bkg_toy%d_sam%d",itoy,isam));
            for (Int_t ireac=2; ireac<NREACTION; ++ireac) {
                hccqebin_rec_nom_bkg[itoy][isam] ->Add(hccqebin_rec_nom[itoy][isam][ireac]);
                hccqebin_rec_thro_bkg[itoy][isam] ->Add(hccqebin_rec_thro[itoy][isam][ireac]);
                hccqebin_rec_fit_bkg[itoy][isam] ->Add(hccqebin_rec_fit[itoy][isam][ireac]);
            }
        }//end isam
       // cout<<"Toy "<<itoy<<" Nom "<<hccqebin_rec_nom_bkg[itoy][0]->Integral()<<" Throw "<<hccqebin_rec_thro_bkg[itoy][0]->Integral()<<" FIT "<<hccqebin_rec_fit_bkg[itoy][0]->Integral()<<endl;

    }//end itoy

    //check pull statistical error
    TFile *popfile = new TFile("../outputs/"+subSaveName+".root","RECREATE");
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
    //make average throw

    //make average toyfit
    TH1F *haverage_ccqebins_toyfit = (TH1F*)hccqebin_rec_fit[0][0][0]->Clone("haverage_ccqebins_toyfit");
    TH1F *haverage_ccqebins_thro = (TH1F*)hccqebin_rec_thro[0][0][0]->Clone("haverage_ccqebins_thro");
    for (Int_t itoy=1; itoy<NTOYFIT; ++itoy) {
        haverage_ccqebins_toyfit->Add(hccqebin_rec_fit[itoy][0][0]);
	haverage_ccqebins_thro->Add(hccqebin_rec_thro[itoy][0][0]);
    }
    haverage_ccqebins_toyfit->Scale(1/float(NTOYFIT));
    cout<<"INTERGRAL before scale "<<haverage_ccqebins_thro->Integral()<<endl; 
    haverage_ccqebins_thro->Scale(1/float(NTOYFIT));
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        //haverage_ccqebins_toyfit->SetBinError(ibin+1,hpullScalePara[ibin]->GetRMS());
        haverage_ccqebins_toyfit->SetBinError(ibin+1,hUncertaintyPercentage[ibin]->GetRMS()*haverage_ccqebins_toyfit->GetBinContent(ibin+1)/100.);
	//haverage_ccqebins_thro->SetBinError(ibin+1,hpullScalePara[ibin]->GetRMS());
        cout<<"CHECK CHECK CHECK bin "<<ibin<<haverage_ccqebins_thro->GetBinContent(ibin+1)<<endl;
    }
    cout<<"INTERGRAL after scale "<<haverage_ccqebins_thro->Integral()<<endl;
    //plot pull each bin
    Int_t ci;
    
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        new TCanvas;
        //navy blue
        ci = TColor::GetColor("#0B3861");
        hpullScalePara[ibin]->GetXaxis()->SetTitle("N^{FIT}-N^{TOY} (CC coh. #pi)");
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
        hUncertaintyPercentage[ibin]->GetXaxis()->SetTitle("(N^{FIT}-N^{TOY})/N^{TOY} (CC coh. #pi)");
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
    TH1D* hUncertaintyPercentageAllClone = (TH1D*)hUncertaintyPercentageAll->Clone("hUncertaintyPercentageAllClone");
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
    //hccqebin_rec_nom[0][0][0]->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    //hccqebin_rec_nom[0][0][0]->GetYaxis()->SetTitle("Number of CC coh. #pi events");
    haverage_ccqebins_toyfit->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    haverage_ccqebins_toyfit->GetYaxis()->SetTitle("Number of CC coh. #pi events");
    //plot2histdata(hccqebin_rec_nom[0][0][0],"Nominal MC",haverage_ccqebins_toyfit,"Average of toy fits",""+subSaveName+"_averageToySpec",0.25,0.71);
    cout<<"INTERGRAL before plot "<<haverage_ccqebins_thro->Integral()<<endl;
    plot3histdata(haverage_ccqebins_toyfit,"Average of toy fits",haverage_ccqebins_thro,"Average of throws",hccqebin_rec_nom[0][0][0],"MC nominal",""+subSaveName+"_averageToySpec",0.35,0.21);

    plot3histdata(haverage_ccqebins_toyfit,"Average of toy fits",hccqebin_rec_nom[0][0][0],"MC nominal",haverage_ccqebins_thro,"Average of throws",""+subSaveName+"_averageToySpec_test",0.35,0.21);

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
    
    //flux
    TH1F *hpullDist_flux[NFLUXPARA];
    double gfmean_flux[NFLUXPARA];
    double gfmeanerr_flux[NFLUXPARA];
    double gfrms_flux[NFLUXPARA];
    double gfrmserr_flux[NFLUXPARA];
    double xflux[NFLUXPARA];
    double xfluxerr[NFLUXPARA];
    
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
    if(isXsecInclude){
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
    }
    
    //det
    if(isDetInclude){
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
    }
    //flux
    if(isFluxInclude){
    for (Int_t ibin=0; ibin<NFLUXPARA; ++ibin) {
        xflux[ibin] = ibin+0.5;
        xfluxerr[ibin] = 0;
        hpullDist_flux[ibin] = new TH1F(Form("hpullDist_flux_bin%d",ibin),"",100,-5,5);
        for (Int_t itoy=0; itoy<NTOYFIT; ++itoy) {
            double bfitVal = hfluxpara_bfit[itoy]->GetBinContent(ibin+1);
            double bthroVal = hfluxpara_thro[itoy]->GetBinContent(ibin+1);
            double efitVal = hfluxpara_err[itoy]->GetBinContent(ibin+1);
            pullVal = (bfitVal-bthroVal)/efitVal;
            hpullDist_flux[ibin]->Fill(pullVal);
        }
        new TCanvas;
        hpullDist_flux[ibin]->Rebin(2);
        hpullDist_flux[ibin]->Fit("gaus");
        TF1 *g2 = hpullDist_flux[ibin]->GetFunction("gaus");
        ci = TColor::GetColor("#B45F04");
        g2->SetLineColor(ci);
        TLatex* tlx=new TLatex(0.42, 0.95,Form("flux Para: %d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print("plots/"+subSaveName+Form("_fluxpara%d.eps",ibin));
        gfmean_flux[ibin] = g2->GetParameter(1);
        gfmeanerr_flux[ibin] = g2->GetParError(1);
        gfrms_flux[ibin] = g2->GetParameter(2);
        gfrmserr_flux[ibin] = g2->GetParError(2);
        //cout<<"BIN "<<ibin<<" MEan "<<hpullDist_flux[ibin]->GetMean()<<" RMS "<<hpullDist_flux[ibin]->GetRMS()<<endl;
        cout<<"BIN "<<ibin<<" MEan "<<gfmean_flux[ibin]<<" RMS "<<gfrms_flux[ibin]<<endl;
    }
    TGraphErrors *gmean_flux = new TGraphErrors(NFLUXPARA,xflux,gfmean_flux,xfluxerr,gfmeanerr_flux);
    TGraphErrors *grms_flux = new TGraphErrors(NFLUXPARA,xflux,gfrms_flux,xfluxerr,gfrmserr_flux);
    }
    
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
    if(isXsecInclude){
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
    }

    //det
    if(isDetInclude){
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
    }
    //flux
    if(isFluxInclude){
    new TCanvas;
    ci = TColor::GetColor("#0B3861");
    gmean_flux->SetLineColor(ci);
    gmean_flux->SetMarkerColor(ci);
    gmean_flux->SetMarkerStyle(8);
    gmean_flux->SetMarkerSize(1.2);
    gmean_flux->SetLineWidth(3);
    ci = TColor::GetColor("#B45F04");
    grms_flux->SetLineColor(ci);
    grms_flux->SetMarkerColor(ci);
    grms_flux->SetMarkerStyle(8);
    grms_flux->SetMarkerSize(1.2);
    grms_flux->SetLineWidth(3);
    titleStyle(grms_flux);
    grms_flux->GetYaxis()->SetTitle("Mean and Standard deviation");
    grms_flux->GetXaxis()->SetTitle("Flux parameters");
    grms_flux->Draw("AP");
    grms_flux->GetYaxis()->SetRangeUser(-1,2);
    gmean_flux->Draw("P sames");
    leg0->Draw();
    gPad->Modified();
    gPad->Print("plots/"+subSaveName+"_flux_fitdist.eps");
    }
//for background uncertainty 
    TH1F *hpullScalePara_bkg[NPTHETABIN];
    TH1F *hUncertaintyPercentage_bkg[NPTHETABIN];
    double percentUncertainty;
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        hpullScalePara_bkg[ibin] = new TH1F(Form("hpullScalePara_bkg_bin%d",ibin),"",50,-50,50);
        hUncertaintyPercentage_bkg[ibin] = new TH1F(Form("hUncertaintyPercentage_bkg_bin%d",ibin),"",100,-100,100);
        for (Int_t itoy=0; itoy<NTOYFIT; ++itoy){
            nsigthro = hccqebin_rec_thro_bkg[itoy][0]->GetBinContent(ibin+1);
            nsigtoyfit = hccqebin_rec_fit_bkg[itoy][0]->GetBinContent(ibin+1);
            toyerror = nsigtoyfit - nsigthro;
            hpullScalePara_bkg[ibin]->Fill(toyerror);
            percentUncertainty = toyerror*100./float(nsigthro);
            hUncertaintyPercentage_bkg[ibin]->Fill(percentUncertainty);
        }
    }
    TH1F *hOveralllUncertainty_bkg = new TH1F("hOveralllUncertainty_bkg","",100,-100,100);
    Double_t ntotSigThro;
    Double_t ntotSigFit;
    Double_t overallSigUncertainty;
    for (Int_t itoy=0; itoy<NTOYFIT; ++itoy){
        ntotSigThro = hccqebin_rec_thro_bkg[itoy][0]->GetSumOfWeights();
        ntotSigFit = hccqebin_rec_fit_bkg[itoy][0]->GetSumOfWeights();
        if(ntotSigThro!=0) {
            overallSigUncertainty = (ntotSigFit-ntotSigThro)*100./float(ntotSigThro);
            cout<<"Throw "<<ntotSigThro<<" Fit "<<ntotSigFit<<" Uncertainty "<<overallSigUncertainty<<endl;
            hOveralllUncertainty_bkg->Fill(overallSigUncertainty);
        }
    }
    hOveralllUncertainty_bkg->GetXaxis()->SetTitle("(N^{FIT}-N^{TOY})/N^{TOY}(%) (Background)");
    hOveralllUncertainty_bkg->GetYaxis()->SetTitle("Number of toy");
    hOveralllUncertainty_bkg->GetXaxis()->SetRangeUser(-50,50);
    //plot1hist_stat(hOveralllUncertainty_bkg,"average_uncertainty_signal",true);
    new TCanvas;
    //navy blue
    Int_t ci = TColor::GetColor("#4F81BD");
    hOveralllUncertainty_bkg->SetLineColor(ci);
    hOveralllUncertainty_bkg->SetLineColor(ci);
    titleStyle(hOveralllUncertainty_bkg);
    hOveralllUncertainty_bkg->Fit("gaus");
    TF1 *g = hOveralllUncertainty_bkg->GetFunction("gaus");
    ci = TColor::GetColor("#C0504D");
    g->SetLineColor(ci);
    gPad->Modified();
    gPad->Print("plots/"+subSaveName+"overallUncertainty_background.eps");
    
    //make average
    TH1F *haverage_ccqebins_toyfit_bkg = (TH1F*)hccqebin_rec_fit_bkg[0][0]->Clone("haverage_ccqebins_toyfit_bkg");
    TH1F *haverage_ccqebins_thro_bkg = (TH1F*)hccqebin_rec_thro_bkg[0][0]->Clone("haverage_ccqebins_thro_bkg");
    for (Int_t itoy=1; itoy<NTOYFIT; ++itoy) {
        haverage_ccqebins_toyfit_bkg->Add(hccqebin_rec_fit_bkg[itoy][0]);
        haverage_ccqebins_thro_bkg->Add(hccqebin_rec_thro_bkg[itoy][0]);
    }
    haverage_ccqebins_toyfit_bkg->Scale(1/float(NTOYFIT));
    haverage_ccqebins_thro_bkg->Scale(1/float(NTOYFIT));
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        haverage_ccqebins_toyfit_bkg->SetBinError(ibin+1,hUncertaintyPercentage_bkg[ibin]->GetRMS()*haverage_ccqebins_toyfit_bkg->GetBinContent(ibin+1)/100.);
    }
    //plot pull each bin
    Int_t ci;
    
    
    //plot percentage uncertainty each bin
    TH1F *hUncertaintyPercentage_bkgAll = (TH1F*)hccqebin_rec_nom[0][0][0]->Clone("hUncertaintyPercentage_bkgAll");
    for (Int_t ibin=0; ibin<NPTHETABIN; ++ibin) {
        hUncertaintyPercentage_bkgAll->SetBinContent(ibin+1, hUncertaintyPercentage_bkg[ibin]->GetRMS());
        new TCanvas;
        //navy blue
        ci = TColor::GetColor("#0B3861");
        hUncertaintyPercentage_bkg[ibin]->GetXaxis()->SetTitle("(N^{FIT}-N^{TOY})/N^{TOY} (Background)");
        hUncertaintyPercentage_bkg[ibin]->GetYaxis()->SetTitle("Number of toys");
        hUncertaintyPercentage_bkg[ibin]->SetLineColor(ci);
        titleStyle(hUncertaintyPercentage_bkg[ibin]);
        hUncertaintyPercentage_bkg[ibin]->Fit("gaus");
        TF1 *g = hUncertaintyPercentage_bkg[ibin]->GetFunction("gaus");
        ci = TColor::GetColor("#B45F04");
        g->SetLineColor(ci);
        TLatex* tlx=new TLatex(0.42, 0.95,Form("Bin: %d",ibin));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print("plots/"+subSaveName+Form("_percentUncertainty_bkg_bin%i.eps",ibin));
    }
    TH1D* hUncertaintyPercentage_bkgAllClone = (TH1D*)hUncertaintyPercentage_bkgAll->Clone("hUncertaintyPercentage_bkgAllClone");
    //plot percentage uncertainty
    hUncertaintyPercentage_bkgAll->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    hUncertaintyPercentage_bkgAll->GetYaxis()->SetTitle("Uncertainty (%)");
    new TCanvas;
    hUncertaintyPercentage_bkgAll->SetTitle("");
    titleStyle(hUncertaintyPercentage_bkgAll);
    ci = TColor::GetColor("#0B3861");
    hUncertaintyPercentage_bkgAll->SetLineColor(ci);
    hUncertaintyPercentage_bkgAll->SetLineWidth(3);
    hUncertaintyPercentage_bkgAll->GetYaxis()->SetRangeUser(0,100);
    
    hUncertaintyPercentage_bkgAll->Draw();
    gPad->Print("plots/"+subSaveName+"_UncertaintyPercentage_bkg.eps");
    //
    //hccqebin_rec_nom_bkg[0][0]->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    //hccqebin_rec_nom_bkg[0][0]->GetYaxis()->SetTitle("Number of CC1#picoh events");
    //plot2histdata(hccqebin_rec_nom_bkg[0][0],"Nominal MC",haverage_ccqebins_toyfit_bkg,"Average of toy fits",""+subSaveName+"_averageToySpec",0.25,0.71);
    
    haverage_ccqebins_toyfit_bkg->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    haverage_ccqebins_toyfit_bkg->GetYaxis()->SetTitle("Number of background events");
    //plot2histdata(haverage_ccqebins_thro_bkg,"Average of throws",haverage_ccqebins_toyfit_bkg,"Average of toy fits",""+subSaveName+"_averageToySpec",0.25,0.71);
    plot3histdata(haverage_ccqebins_toyfit_bkg,"Average of toy fits",haverage_ccqebins_thro_bkg,"Average of throws",hccqebin_rec_nom_bkg[0][0],"MC nominal",""+subSaveName+"_averageToySpec_bkg",0.35,0.21);
///
    popfile->Write();
    popfile->Close();
    
}
