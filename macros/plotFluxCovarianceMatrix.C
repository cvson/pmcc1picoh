{
    gROOT->ProcessLine(".x /home/t2k/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/t2k/cvson/basicPlotUtil.C");
    
    TFile *pfile = new TFile("../outputs/testFluxCovariance.root");
    
    TH2F *h1 = (TH2F*)pfile->Get("hfluxcovmatrix");
    gStyle->SetPadRightMargin(0.15);
    plot2dcolz(h1,"neuflux_fraccovmatrix");
    TH2F *h2 = (TH2F*)pfile->Get("hfluxcovmatrix_chol");
    h2->GetZaxis()->SetRangeUser(-0.045,0.045);
    plot2dcolz(h2,"neuflux_fraccovmatrix_chol");
}