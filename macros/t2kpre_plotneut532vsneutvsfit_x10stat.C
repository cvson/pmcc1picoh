{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    TFile *pfileFIT = new TFile("../outputs/two/fittoy_result_1xseconly_x10stat.root");
    TFile *pfileNEUT532 = new TFile("../outputs/neut532vsneut_sample_ana1x50mepionFS_5binsptheta_x10stat.root");
    //stat uncertainty
    //syst uncertainty
    //TString subname = "ana1x_genievsneutvsfit_nodet_"; 
    TString subname = "ana1x_neut532vsneutvsfit_xsec_"; 
    TH1D *hmcneut_sig;
    TH1D *hmcneut532_sig;
    TH1D *hfit_sig;
    
    TH1D *hmcneut_bkg;
    TH1D *hmcneut532_bkg;
    TH1D *hfit_bkg;
    
    string samplestr = "SIG";
    string tagnom = "nominal";
    string tagfit = "fit";
    const int nreac = 9;//10;
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall"};
    TH1D *hmcneutnom[nreac];
    TH1D *hmcneut532nom[nreac];
    TH1D *hgeniefit[nreac];
    for(int ireac=0;ireac<nreac;ireac++){
        hmcneutnom[ireac] = (TH1D*)pfileFIT->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagnom.c_str()));
        hgeniefit[ireac] = (TH1D*)pfileFIT->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagfit.c_str()));
        hmcneut532nom[ireac] = (TH1D*)pfileNEUT532->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagnom.c_str()));
    }
    hmcneut_sig = (TH1D*)hmcneutnom[0]->Clone("hmcneut_sig");
    hmcneut532_sig = (TH1D*)hmcneut532nom[0]->Clone("hmcneut532_sig");
    hfit_sig = (TH1D*)hgeniefit[0]->Clone("hfit_sig");
    
    //need to setup the systematic + uncertainty
    hfit_sig->GetYaxis()->SetTitle("Number of event (Signal)");
    hfit_sig->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
   //check the ratio between NEUT and GENIE
    Int_t NBIN = hmcneut_sig->GetNbinsX();
    for(int ibin=0;ibin<NBIN;ibin++){
      double valneut = hmcneut_sig->GetBinContent(ibin+1);
      double valgenie = hmcneut532_sig->GetBinContent(ibin+1);
      cout<<"Bin "<<ibin<<" NEUT "<<valneut<<" GENIE "<<valgenie<<" ratio "<<valgenie/valneut<<endl;
    }
    plot3histdata(hfit_sig,"Fit result",hmcneut_sig,"NEUT MC",hmcneut532_sig," NEUT5.3.2 MC",subname+"sig",0.4,0.65);
    
    hmcneut_bkg = (TH1D*)hmcneutnom[1]->Clone("hmcneut_bkg");
    hmcneut532_bkg = (TH1D*)hmcneut532nom[1]->Clone("hmcneut532_bkg");
    hfit_bkg = (TH1D*)hgeniefit[1]->Clone("hfit_bkg");
    
    for(int ireac=2;ireac<nreac;ireac++){
        hmcneut_bkg->Add(hmcneutnom[ireac]);
        hmcneut532_bkg->Add(hmcneut532nom[ireac]);
        hfit_bkg->Add(hgeniefit[ireac]);
    }
    
    hfit_bkg->GetYaxis()->SetTitle("Number of event (Background)");
    hfit_bkg->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    plot3histdata(hfit_bkg,"Fit result",hmcneut_bkg,"NEUT MC",hmcneut532_bkg," NEUT5.3.2 MC",subname+"bkg",0.65,0.2);
}
