{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    Bool_t isNEUTfake = false;
    TFile *pfileFIT = new TFile(isNEUTfake?"../outputs/two/fittoy_result_1xseconlyhi_neut.root":"../outputs/two/fittoy_result_1xseconlyhi.root");
    TFile *pfileGENIE = new TFile(isNEUTfake?"../outputs/neutvsgenie_sample_ana1x50mepionFS_3binsptheta.root":"../outputs/genievsneut_sample_ana1x50mepionFS_3binsptheta.root");
    TFile *pfileGENIEMIG = new TFile(isNEUTfake?"../outputs/neutvsgenieMIG_sample_ana1x50mepionFS_3binsptheta.root":"../outputs/genievsneutMIG_sample_ana1x50mepionFS_3binsptheta.root");
    TString subname = isNEUTfake?"xseconly_twohi_neut_":"xseconly_twohi_genie_"; 
    
    /*TFile *pfileFIT = new TFile(isNEUTfake?"../outputs/three/fittoy_result_1xseconlylo_neut.root":"../outputs/three/fittoy_result_1xseconlylo.root");
    TFile *pfileGENIE = new TFile(isNEUTfake?"../outputs/neutvsgenie_sample_ana1x50mepionFS_3binsptheta.root":"../outputs/genievsneut_sample_ana1x50mepionFS_3binsptheta.root");
    TFile *pfileGENIEMIG = new TFile(isNEUTfake?"../outputs/neutvsgenieMIG_sample_ana1x50mepionFS_3binsptheta.root":"../outputs/genievsneutMIG_sample_ana1x50mepionFS_3binsptheta.root");
    TString subname = isNEUTfake?"xseconly_threelo_neut_":"xseconly_threelo_genie_";
 */
    TH1D *hmcneut_sig;
    TH1D *hmcgenie_sig;
    TH1D *hmcgenieMIG_sig;
    TH1D *hfit_sig;
    
    TH1D *hmcneut_bkg;
    TH1D *hmcgenie_bkg;
    TH1D *hmcgenieMIG_bkg;
    TH1D *hfit_bkg;
    
    string samplestr = "SIG";
    string tagnom = "nominal";
    string tagfit = "fit";
    const int nreac = 9;//10;
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall"};
    TH1D *hmcneutnom[nreac];
    TH1D *hmcgenienom[nreac];
    TH1D *hmcgenienomMIG[nreac];
    TH1D *hgeniefit[nreac];
    for(int ireac=0;ireac<nreac;ireac++){
        hmcneutnom[ireac] = (TH1D*)pfileFIT->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagnom.c_str()));
        hgeniefit[ireac] = (TH1D*)pfileFIT->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagfit.c_str()));
        hmcgenienom[ireac] = (TH1D*)pfileGENIE->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagnom.c_str()));
	hmcgenienomMIG[ireac] = (TH1D*)pfileGENIEMIG->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagnom.c_str()));
    }
    hmcneut_sig = (TH1D*)hmcneutnom[0]->Clone("hmcneut_sig");
    hmcgenie_sig = (TH1D*)hmcgenienom[0]->Clone("hmcgenie_sig");
    hmcgenieMIG_sig = (TH1D*)hmcgenienomMIG[0]->Clone("hmcgenieMIG_sig");
    hfit_sig = (TH1D*)hgeniefit[0]->Clone("hfit_sig");
    
    //need to setup the systematic + uncertainty
    hfit_sig->GetYaxis()->SetTitle("Number of event (Signal)");
    hfit_sig->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
   //check the ratio between NEUT and GENIE
    Int_t NBIN = hmcneut_sig->GetNbinsX();
    for(int ibin=0;ibin<NBIN;ibin++){
      double valneut = hmcneut_sig->GetBinContent(ibin+1);
      double valgenie = hmcgenie_sig->GetBinContent(ibin+1);
      cout<<"Bin "<<ibin<<" NEUT "<<valneut<<" fake "<<valgenie<<" ratio "<<valgenie/valneut<<endl;
    }
    /*if(isNEUTfake) plot3histdata(hfit_sig,"Fit result",hmcneut_sig,"NEUT MC",hmcgenie_sig,"NEUT MC",subname+"sig",0.4,0.65);
    else plot3histdata(hfit_sig,"Fit result",hmcneut_sig,"NEUT MC",hmcgenie_sig,"GENIE MC",subname+"sig",0.4,0.65);*/
    if(isNEUTfake) plot3histdata(hfit_sig,"Fit result",hmcneut_sig,"NEUT MC",hmcgenieMIG_sig,"NEUT MC (shifted)",subname+"sig",0.52,0.25);
    else plot4histdata(hfit_sig,"Fit result",hmcneut_sig,"NEUT MC",hmcgenie_sig,"GENIE MC", hmcgenieMIG_sig,"GENIE MC (shifted)",subname+"sig",0.52,0.25);

    hmcneut_bkg = (TH1D*)hmcneutnom[1]->Clone("hmcneut_bkg");
    hmcgenie_bkg = (TH1D*)hmcgenienom[1]->Clone("hmcgenie_bkg");
    hmcgenieMIG_bkg = (TH1D*)hmcgenienomMIG[1]->Clone("hmcgenieMIG_bkg");
    hfit_bkg = (TH1D*)hgeniefit[1]->Clone("hfit_bkg");
    hmcneut_bkg->Sumw2();
	hmcgenie_bkg->Sumw2();
	hmcgenieMIG_bkg->Sumw2();
	hfit_bkg->Sumw2();
    
    for(int ireac=2;ireac<nreac;ireac++){
        hmcneut_bkg->Add(hmcneutnom[ireac]);
        hmcgenie_bkg->Add(hmcgenienom[ireac]);
        hmcgenieMIG_bkg->Add(hmcgenienomMIG[ireac]);
        hfit_bkg->Add(hgeniefit[ireac]);
    }
	//new TCanvas;
	//hmcgenieMIG_bkg->Draw("hist");
    cout<<"Compare NEUT-bkg"<<hmcneut_bkg->Integral(0,hmcneut_bkg->GetNbinsX()+1)<<" nominal "<< hmcgenie_bkg->Integral(0,hmcgenie_bkg->GetNbinsX()+1)<<" tuned "<<hmcgenieMIG_bkg->Integral(0,hmcgenieMIG_bkg->GetNbinsX()+1)<<endl;
     for(int ibin=0;ibin<NBIN;ibin++){
      double valneut = hmcgenie_bkg->GetBinContent(ibin+1);
      double valgenie = hmcgenieMIG_bkg->GetBinContent(ibin+1);
	hmcgenieMIG_bkg->SetBinContent(ibin+1,valgenie);
      cout<<"Bin "<<ibin<<" GENIE "<<valneut<<" GENIE (tuned) "<<valgenie<<" ratio "<<valgenie/valneut<<endl;
    }
 
    hfit_bkg->GetYaxis()->SetTitle("Number of event (Background)");
    hfit_bkg->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    
/*	new TCanvas;
hfit_bkg->Draw("ep");
hmcgenieMIG_bkg->Draw("hist same");*/
    /*if(isNEUTfake) plot4histdata(hfit_bkg,"Fit result",hmcneut_bkg,"NEUT MC",hmcgenie_bkg,"NEUT MC",hmcgenieMIG_sig,"NEUT MC (shifted)",subname+"bkg",0.52,0.25);
    else plot4histdata(hfit_bkg,"Fit result",hmcneut_bkg,"NEUT MC",hmcgenie_bkg,"GENIE MC",hmcgenieMIG_sig,"GENIE MC (shifted)",subname+"bkg",0.52,0.25);*/
    //plot3histdata(hfit_bkg,"Fit result",hmcneut_bkg,"NEUT MC",hmcgenieMIG_sig,"GENIE MC (shifted)",subname+"bkg",0.52,0.25);
new TCanvas;
	titleStyle(hfit_bkg);
hfit_bkg->GetYaxis()->SetRangeUser(0, 200);
    hfit_bkg->DrawCopy("ep");

    Int_t ci;
    ci = TColor::GetColor("#006633");
    hmcneut_bkg->SetLineColor(ci);
    hmcneut_bkg->SetFillStyle(0);
    hmcneut_bkg->SetLineWidth(3);
    hmcneut_bkg->DrawCopy("histsame");

    ci = TColor::GetColor("#B45F04");
    hmcgenie_bkg->SetLineColor(ci);
    hmcgenie_bkg->SetFillStyle(0);
    hmcgenie_bkg->SetLineWidth(3);
    hmcgenie_bkg->SetLineStyle(7);
    if(!isNEUTfake)hmcgenie_bkg->DrawCopy("histsame");

     hmcgenieMIG_bkg->SetLineColor(ci);
    hmcgenieMIG_bkg->SetFillStyle(0);
    hmcgenieMIG_bkg->SetLineWidth(3);
    hmcgenieMIG_bkg->SetLineStyle(1);
    hmcgenieMIG_bkg->DrawCopy("histsame");

    //gPad->RedrawAxis();
    TLegend* leg = new TLegend(0.52,0.25,0.52+0.3,0.25+0.25);
    leg->SetFillStyle(0);
    leg->SetBorderSize(0);
    leg->SetTextSize(0.045);
    leg->AddEntry(hfit_bkg, "Fit result","lep");
    leg->AddEntry(hmcneut_bkg, "NEUT MC","l");
    if (!isNEUTfake){leg->AddEntry(hmcgenie_bkg, "GENIE MC","l");
    leg->AddEntry(hmcgenieMIG_bkg, "GENIE MC (shift)","l");
     }
    else leg->AddEntry(hmcgenieMIG_bkg, "NEUT MC (shift)","l");
    leg->Draw();

    gPad->Print("plots/"+subname+"bkg.eps");

}
