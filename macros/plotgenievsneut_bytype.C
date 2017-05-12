{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    //TFile *pfilegenie = new TFile("../outputs/neutvsgenie_sample_newbin2.root");
    //TFile *pfileneut = new TFile("../outputs/genievsneut_sample_newbin2.root");
    TFile *pfilegenie = new TFile("../outputs/neutvsgenie_sample_newbin2_pidccqev2.root");
    TFile *pfileneut = new TFile("../outputs/genievsneut_sample_newbin2_pidccqev2.root");
    TString subname = "pidccqev2";
    string tag = "nominal";
    string samplestr = "SIG";
    string reactionstr = "cc1pi";
    
    TH1D *hgenie;
    TH1D *hneut;
    
    const char *bsnameTag[11] = {"SIG", "CRI", "CRIIALoQsq", "CRIIAHiQsq","CRIIB", "CRIICHiResPID", "CRIICLoResPID", "M2TRKHiResPID","M2TRKLoResPID", "ONETRKLoQsq","ONETRKHiQsq"};
    
    for (Int_t isample=0; isample<11; isample++) {
        hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut->GetYaxis()->SetTitle("Number of CC1#pi resonant Events");
        hneut->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
        plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",subname + Form("genievsneut_cc1pi_%s",bsnameTag[isample]),0.3,0.7);
    }//end isample
    
    reactionstr = "ccother";
    for (Int_t isample=0; isample<11; isample++) {
        hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",subname + Form("genievsneut_ccother_%s",bsnameTag[isample]),0.3,0.7);
    }//end isample
    
    reactionstr = "ccqe";
    for (Int_t isample=0; isample<11; isample++) {
        hgenie = (TH1D*)pfilegenie->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        hneut = (TH1D*)pfileneut->Get(Form("%s_ccqebins_rec_%s_%s",bsnameTag[isample],reactionstr.c_str(),tag.c_str()));
        plot2histdata(hneut,"NEUT MC",hgenie,"GENIE MC",subname + Form("genievsneut_ccqe_%s",bsnameTag[isample]),0.3,0.7);
    }//end isample
 
}