{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    TFile *pfileFIT = new TFile("../outputs/four/fittoy_result_1allpara.root");
    TFile *pfileGENIE = new TFile("../outputs/neutvsgenie_sample_newbin2.root");
    //stat uncertainty
    //syst uncertainty
    
    TH1D *hmcneut_sig;
    TH1D *hmcgenie_sig;
    TH1D *hfit_sig;
    
    TH1D *hmcneut_bkg;
    TH1D *hmcgenie_bkg;
    TH1D *hfit_bkg;
    
    string samplestr = "SIG";
    string tagnom = "nominal";
    string tagfit = "fit";
    const int nreac = 9;//10;
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall"};
    TH1D *hmcneutnom[nreac];
    TH1D *hmcgenienom[nreac];
    TH1D *hgeniefit[nreac];
    for(int ireac=0;ireac<nreac;ireac++){
        hmcneutnom[ireac] = (TH1D*)pfileFIT->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagnom.c_str()));
        hgeniefit[ireac] = (TH1D*)pfileFIT->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagfit.c_str()));
        hmcgenienom[ireac] = (TH1D*)pfileGENIE->Get(Form("%s_ccqebins_rec_%s_%s",samplestr.c_str(),names[ireac],tagnom.c_str()));
    }
    hmcneut_sig = (TH1D*)hmcneutnom[0]->Clone("hmcneut_sig");
    hmcgenie_sig = (TH1D*)hmcgenienom[0]->Clone("hmcgenie_sig");
    hfit_sig = (TH1D*)hgeniefit[0]->Clone("hfit_sig");
    
    //need to setup the systematic + uncertainty
    hfit_sig->GetYaxis()->SetTitle("Number of event (Signal)");
    hfit_sig->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
    plot3histdata(hfit_sig,"Fit result",hmcneut_sig,"NEUT MC",hmcgenie_sig,"GENIE MC","comp_genievsneutvsfit_sig",0.4,0.65);
    
    hmcneut_bkg = (TH1D*)hmcneutnom[1]->Clone("hmcneut_bkg");
    hmcgenie_bkg = (TH1D*)hmcgenienom[1]->Clone("hmcgenie_bkg");
    hfit_bkg = (TH1D*)hgeniefit[1]->Clone("hfit_bkg");
    
    for(int ireac=2;ireac<nreac;ireac++){
        hmcneut_bkg->Add(hmcneutnom[ireac]);
        hmcgenie_bkg->Add(hmcgenienom[ireac]);
        hfit_bkg->Add(hgeniefit[ireac]);
    }
    
    hfit_bkg->GetYaxis()->SetTitle("Number of event (Background)");
    hfit_bkg->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
    plot3histdata(hfit_bkg,"Fit result",hmcneut_bkg,"NEUT MC",hmcgenie_bkg,"GENIE MC","comp_genievsneutvsfit_bkg",0.65,0.2);
}