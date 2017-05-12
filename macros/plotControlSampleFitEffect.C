{
    gROOT->ProcessLine(".x /home/t2k/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/t2k/cvson/basicPlotUtil.C");
    TString subSaveName = "checkpullSyst";
    TFile *pfour = new TFile("../outputs/checkpull_"+subSaveName+".root");
    TFile *pone = new TFile("../outputs/checkpull_"+subSaveName+"SigOnly.root");
    TH1D *hfour = (TH1D*)pfour->Get("hUncertaintyPercentageAllClone");
    TH1D *hone = (TH1D*)pone->Get("hUncertaintyPercentageAllClone");
    hone->GetYaxis()->SetTitle("Uncertainty (%)");
    hone->GetXaxis()->SetTitle("Scaling parameter");
    plot2hist(hone,"Signal Only",hfour,"Signal + Sidebands",subSaveName+"_comp",0.5,0.65);
}
