{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    TFile *file = new TFile("../../data/nd34_tuned_11bv3.1_250ka.root");
    TH1F *hfluxnom = (TH1F*)file->Get("ing3_nom_numu");
    TH1F *hfluxtune = (TH1F*)file->Get("ing3_tune_numu");
    hfluxnom->GetXaxis()->SetTitle("True neutrino energy (GeV)");
    plot2hist_stat(hfluxnom,"Nominal",hfluxtune,"Tuned","ing3_numu_nomvstune",false);
    
}