{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    TFile *pfileneut = new TFile("../outputs/neutvsgenie_sample_ana1x50mepionFS_5binsptheta.root");
    TFile *pfilegenie = new TFile("../outputs/genievsneut_sample_ana1x50mepionFS_5binsptheta.root");
    TString subname = "ana1x_5binstheta_";
    string tag = "nominal";
    string samplestr = "SIG";
    
    TH1D *hgenie;
    TH1D *hneut;
    
    const char *bsnameTag[2] = {"SIG", "CRI"};
   string reactionstr = "sig";
    for (Int_t isample=0; isample<2; isample++) {
        hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut->GetYaxis()->SetTitle("Number of CC coh.#pi Events");
        hneut->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
        plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",subname + Form("genievsneut_sig_%s",bsnameTag[isample]),0.3,0.7);
    }//end isample

    string reactionstr = "cc1pi"; 
    for (Int_t isample=0; isample<2; isample++) {
        hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut->GetYaxis()->SetTitle("Number of CC 1#pi Events");
        hneut->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
        plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",subname + Form("genievsneut_cc1pi_%s",bsnameTag[isample]),0.3,0.7);
    }//end isample
    
    reactionstr = "ccother";
    for (Int_t isample=0; isample<2; isample++) {
        hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut->GetYaxis()->SetTitle("Number of CC (N>1)#pi Events");
        hneut->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
        plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",subname + Form("genievsneut_ccNpi_%s",bsnameTag[isample]),0.3,0.7);
    }//end isample
    
    reactionstr = "ccqe";
    for (Int_t isample=0; isample<2; isample++) {
        hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut->GetYaxis()->SetTitle("Number of CC 0#pi Events");
        hneut->GetXaxis()->SetTitle("Reconstructed p_{#mu}-cos(#theta_{#mu}) bins");
        plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",subname + Form("genievsneut_cc0pi_%s",bsnameTag[isample]),0.3,0.7);
    }//end isample
 
}
