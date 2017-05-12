{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    //TString subSaveName = "checkpullScale";
    //TString subSaveName = "checkpull_statonly";
    //TString subSaveName = "checkpull_fluxonlystatfluc";
    //TString subSaveName = "checkpull_fluxonlynostat";
    //TString subSaveName = "checkpull_xseconlynostat";
   // TString subSaveName = "checkpull_detonlynostat";
    //TString subSaveName = "checkpull_allsystnostat";
    //TString subSaveName = "checkpull_allsyststatfluc";
    //TString subSaveName = "checkpullpiless02cor_xseconlynostat";
    //TString subSaveName = "checkpullpiless02cor_allsyststatfluc";
    //TString subSaveName = "checkpullpiless02cor_allsystnostat";
    TString subSaveName = "checkpullpiless02cor_xsecfluxnostat";
    TFile *pfour = new TFile("../outputs/"+subSaveName+"_2sam.root");
    TFile *pone = new TFile("../outputs/"+subSaveName+"_1sam.root");
    TH1D *hfour = (TH1D*)pfour->Get("hUncertaintyPercentageAllClone");
    TH1D *hone = (TH1D*)pone->Get("hUncertaintyPercentageAllClone");
    hone->SetMinimum(0);
    hone->SetMaximum(50);
    hone->GetYaxis()->SetTitle("Uncertainty on Signal (%)");
    hone->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    plot2hist(hone,"Signal sample",hfour,"Signal + Sidebands",subSaveName+"_sig_comp",0.5,0.65);

    TH1D *hfourbkg = (TH1D*)pfour->Get("hUncertaintyPercentage_bkgAllClone");
    TH1D *honebkg = (TH1D*)pone->Get("hUncertaintyPercentage_bkgAllClone");
    honebkg->SetMinimum(0);
    honebkg->SetMaximum(50);
    honebkg->GetYaxis()->SetTitle("Uncertainty on Background (%)");
    honebkg->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
    plot2hist(honebkg,"Signal sample",hfourbkg,"Signal + Sidebands",subSaveName+"_bkg_comp",0.5,0.65);
}
