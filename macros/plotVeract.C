{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    
    
    //TFile *pfile = new TFile("../outputs/checkFSI_fsisel_finalcomb.root");
    //TString subname="fsisel_finalcomb";
    
    TFile *pfile = new TFile("../outputs/CheckVeract_fsisel_finalcomb_addnue.root");
    TString subname="checkVeract";
    TH1F *hveract_1trk_ccqe = (TH1F*)pfile->Get("hveract_1trk_ccqe");
    TH1F *hveract_1trk_ccqe_trkid = (TH1F*)pfile->Get("hveract_1trk_ccqe_trkid");
    TH2F *hveractvsmuang_1trk_ccqe = (TH2F*)pfile->Get("hveractvsmuang_1trk_ccqe");
    TH2F *hveractvsmuang_1trk_ccqe_trkid = (TH2F*)pfile->Get("hveractvsmuang_1trk_ccqe_trkid");
    
    TH1F *hveract_2trk_ccqe = (TH1F*)pfile->Get("hveract_2trk_ccqe");
    TH1F *hveract_2trk_ccqe_trkid = (TH1F*)pfile->Get("hveract_2trk_ccqe_trkid");
    TH2F *hveractvsmuang_2trk_ccqe = (TH2F*)pfile->Get("hveractvsmuang_2trk_ccqe");
    TH2F *hveractvsmuang_2trk_ccqe_trkid = (TH2F*)pfile->Get("hveractvsmuang_2trk_ccqe_trkid");
    TH2F *hveractvspang_2trk_ccqe = (TH2F*)pfile->Get("hveractvspang_2trk_ccqe");
    TH2F *hveractvspang_2trk_ccqe_trkid= (TH2F*)pfile->Get("hveractvspang_2trk_ccqe_trkid");
    
    TH1F *hveract_1trk_ncqe = (TH1F*)pfile->Get("hveract_1trk_ncqe");
    TH1F *hveract_1trk_ncqe_trkid = (TH1F*)pfile->Get("hveract_1trk_ncqe_trkid");
    TH2F *hveractvsmuang_2trk_ncqe = (TH2F*)pfile->Get("hveractvsmuang_2trk_ncqe");
    TH2F *hveractvsmuang_2trk_ncqe_trkid = (TH2F*)pfile->Get("hveractvsmuang_2trk_ncqe_trkid");

    
    
    //new TCanvas;
    hveractvsmuang_1trk_ccqe_trkid->GetXaxis()->SetTitle("#mu-like track angle");
    hveractvsmuang_1trk_ccqe_trkid->GetXaxis()->SetRangeUser(0,60);
    hveractvsmuang_1trk_ccqe_trkid->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    hveractvsmuang_1trk_ccqe_trkid->GetYaxis()->SetRangeUser(0,100);
    plot2dhist(hveractvsmuang_1trk_ccqe_trkid,"hveractvsmuang_1trk_ccqe_trkid");
    
    hveractvsmuang_2trk_ccqe_trkid->GetXaxis()->SetTitle("#mu-like track angle");
    hveractvsmuang_2trk_ccqe_trkid->GetXaxis()->SetRangeUser(0,90);
    hveractvsmuang_2trk_ccqe_trkid->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    hveractvsmuang_2trk_ccqe_trkid->GetYaxis()->SetRangeUser(0,100);
    plot2dhist(hveractvsmuang_2trk_ccqe_trkid,"hveractvsmuang_2trk_ccqe_trkid");
    
    hveractvspang_2trk_ccqe_trkid->GetXaxis()->SetTitle("p-like track angle");
    hveractvspang_2trk_ccqe_trkid->GetXaxis()->SetRangeUser(0,90);
    hveractvspang_2trk_ccqe_trkid->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    hveractvspang_2trk_ccqe_trkid->GetYaxis()->SetRangeUser(0,100);
    plot2dhist(hveractvspang_2trk_ccqe_trkid,"hveractvspang_2trk_ccqe_trkid");
    
    hveractvsmuang_2trk_ncqe_trkid->GetXaxis()->SetTitle("p-like track angle");
    hveractvsmuang_2trk_ncqe_trkid->GetXaxis()->SetRangeUser(0,90);
    hveractvsmuang_2trk_ncqe_trkid->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    hveractvsmuang_2trk_ncqe_trkid->GetYaxis()->SetRangeUser(0,100);
    plot2dhist(hveractvsmuang_2trk_ncqe_trkid,"hveractvsmuang_1trk_ncqe_trkid");
    
    plot3hist(true, hveract_1trk_ncqe_trkid, "1trk-NCQE",hveract_1trk_ccqe_trkid,"1trk-CCQE",hveract_2trk_ccqe_trkid,"2trk-CCQE",subname+"_comp_ccqevsncqe_trkid");
    
    plot3hist(true, hveract_1trk_ncqe, "1trk-NCQE",hveract_1trk_ccqe,"1trk-CCQE",hveract_2trk_ccqe,"2trk-CCQE",subname+"_comp_ccqevsncqe");
    
    
}