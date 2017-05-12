float Draw(TGraph *g, TString fname){

    g->GetXaxis()->SetTitle("Hit inefficiency  (%)");
    g->GetYaxis()->SetTitle(Form("Variation of %s",fname.Data()));
    g->GetYaxis()->SetTitleOffset(1.1);
    g->SetMarkerStyle(8);
    g->SetMarkerSize(1);
    g->Draw("AP");
    //TF1 *f1= new TF1("f1","[0]*(1-[1]*x)");
    TF1 *f1= new TF1("f1","[0]+[1]*x");
    f1->SetParName(0,"#alpha");
    f1->SetParName(1,"#beta");
    f1->SetLineWidth(2);
    f1->SetLineStyle(7);
    f1->SetLineColor(2);
    g->Fit("f1");
    TF1 *func=g->GetFunction("f1");


    TLegend* leg    = new TLegend(0.2, 0.25, 0.4, 0.4);
    leg  -> SetFillColor  (0);
    leg  -> SetShadowColor(0);
    leg  -> SetLineWidth  (0);
    leg  -> SetLineColor  (0);
    leg  -> SetTextSize   (0.04);
    leg  -> AddEntry(g,"MC results", "lep");
    leg  -> AddEntry(f1,"Fitting by y = #alpha +#beta x", "l");
    leg  -> Draw();
    float res = func->GetParameter(1);
    return res;
};

void t2kpre_plotDetResponse_hiteff_nosb(){
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 4;
    const char *nameSample[NSAMPLE] = {"SIG",  "CRI", "CRII","CRIII"};
    const char *nameSample_long[NSAMPLE]={"SIG", "CRI", "CRII","CRIII"};
    
    const char *colorcode[NSAMPLE] = {"#000000",
        "#0072B2",
        "#D55E00",
	"#CC79A7"};
    const int markerStyle[NSAMPLE] = {20, 21, 22,23};
    const int NFILE = 5;

    TFile *pFile = new TFile("../inputs/detresponsefunction_hiteff.root");
    TH1F *hbinccqe[NSAMPLE][NFILE];
    TH1F *hbinccqe_bkg[NSAMPLE][NFILE];
    TH1F *hhiteff[NSAMPLE][NFILE];
    double nsignal;
    double nbackground;
    TGraph *pgrccqe[NSAMPLE];
    TGraph *pgrccqe_bkg[NSAMPLE];
    double nevtbyBin[NFILE];
    double nevtbyBin_bkg[NFILE];
    double xsigma[NFILE];//={0,1,2,3,4,5,6,7,8};

    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (int ifile=0; ifile < NFILE; ++ifile) {
            hbinccqe[isam][ifile] = (TH1F*)pFile->Get(Form("hbinccqe_sig_sam%d_id%d",isam,ifile));
            hbinccqe_bkg[isam][ifile] = (TH1F*)pFile->Get(Form("hbinccqe_bkg_sam%d_id%d",isam,ifile));
            hhiteff[isam][ifile]= (TH1F*)pFile->Get(Form("hhiteff_file%d",ifile));
      }
  }
   for (int ifile=0; ifile<NFILE; ++ifile) {
        xsigma[ifile] = hhiteff[0][ifile]->GetMean()*100;
    }

    for (int isam=0; isam<NSAMPLE; ++isam) {
        for (int ifile=0; ifile < NFILE; ++ifile) {
            nevtbyBin[ifile] = hbinccqe[isam][ifile]->GetSumOfWeights()/hbinccqe[isam][0]->GetSumOfWeights();
            nevtbyBin_bkg[ifile] = hbinccqe_bkg[isam][ifile]->GetSumOfWeights()/hbinccqe_bkg[isam][0]->GetSumOfWeights();
            cout<<"sam "<<isam <<" file "<<ifile<<" signal "<<nevtbyBin[ifile]<<" bkg "<<nevtbyBin_bkg[ifile]<<endl;
        }
   pgrccqe[isam] = new TGraph(NFILE,xsigma,nevtbyBin);
   pgrccqe_bkg[isam] = new TGraph(NFILE,xsigma,nevtbyBin_bkg);
    new TCanvas;
    titleStyle(pgrccqe[isam]);
    float res1 = Draw(pgrccqe[isam],"Signal");
    gPad->Print(Form("plots/detsyst_hiteff_nosb_sig_sam%d.eps",isam));
    cout<<"sam "<<isam<<"sig frac "<<res1<<endl;
    titleStyle(pgrccqe_bkg[isam]);
    new TCanvas;
    float res2 = Draw(pgrccqe_bkg[isam], "Background");
    gPad->Print(Form("plots/detsyst_hiteff_nosb_bkg_sam%d.eps",isam));
    cout<<"sam "<<isam<<"bkg frac "<<res2<<endl;  
    
     }

    


}
