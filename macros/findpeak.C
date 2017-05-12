{ 
    //TFile *pfile = new TFile("../outputs/checkFSI_fsisel_finalcomb_addnue.root");
    //TH1F *hh = (TH1F*)pfile->Get("hmc_topo6_var12_int10");//one muon, one pion
    
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue.root");
    //TH1F *hh = (TH1F*)pfile->Get("hdata_topo10_var36");//one muon
    //TH1F *hh = (TH1F*)pfile->Get("hdata_topo17_var36");//one proton
    TH1F *hh = (TH1F*)pfile->Get("hdata_topo23_var36");//one muon and one proton
    hh->Rebin(4);
    Int_t nbin = hh->GetNbinsX();
    double maxVal = 0;
    Int_t maxBin = 0;
    for (Int_t ibin=1; ibin<nbin; ibin++) {
        double valbin = hh->GetBinContent(ibin);
        if (valbin>maxVal) {
            maxVal = valbin;
            maxBin = ibin;
        }
    }
    cout<<"Max Val "<<maxVal<<" Bin "<<maxBin<<" at "<<hh->GetBinCenter(maxBin)<<endl;
}
