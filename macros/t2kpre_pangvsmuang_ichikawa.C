{
    /*
     to plot pang vs muang for signal, sideband and without vertex activity cut
     */
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil_v532.C");
    const Int_t NSAMPLE2CHECK = 3;
    //235 is CCQE 2trk, 244-246 is 235 devided in Q2, 224 is antipid, 223 is antipid CC1pi, 192 is more than 2trk
    Int_t indexNSAM[] = {221,222,249};
    const char *colorcode[] = {
"#000000",
"#0072B2",
"#D55E00",
"#CC79A7",
"#E69F00",
"#009E73",
"#56B4E9",
"#F0E442",
"#000000"
    };
    Int_t ci;
    
    Bool_t isNewVersion=true;//lazy to reproduce all sample with pang vs. muang
    Bool_t isPion=true;
    
    TString subname = "pangvsmuang_";
    TFile *pfile[NSAMPLE2CHECK];
    TFile *pfilegenie[NSAMPLE2CHECK];
    TFile *pfilev532[NSAMPLE2CHECK];
    
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        pfile[isample] = new TFile(Form("../outputs/basicHisto_neut5d3d2_20170529_sam%d.root",indexNSAM[isample]));//neut532.
        pfilegenie[isample] = new TFile(Form("../outputs/basicHisto_genie_20170529_sam%d.root",indexNSAM[isample]));//genie.
        pfilev532[isample] = new TFile(Form("../outputs/basicHisto_neut5d1d4d2_20170529_sam%d.root",indexNSAM[isample]));//neut5.14.2.
    }
   
    const Int_t NINTERACTION = 10;
    
    //TH1 to scale event;
    TH1F* hdt[NSAMPLE2CHECK];
    TH1F* hmc[NSAMPLE2CHECK];
    TH1F* hmc[NSAMPLE2CHECK];
    TH1F* hmcntype[NSAMPLE2CHECK];//0 to 60 bins
    
    //MC vs daat TH2D
    TH2F* hdtveractvsmuang[NSAMPLE2CHECK];
    TH2F* hmcveractvsmuang[NSAMPLE2CHECK][NINTERACTION];
    TH2F* hdtveractvspang[NSAMPLE2CHECK];
    TH2F* hmcveractvspang[NSAMPLE2CHECK][NINTERACTION];
    TH2F* hdtpangvsmuang[NSAMPLE2CHECK];
    TH2F* hmcpangvsmuang[NSAMPLE2CHECK][NINTERACTION];
    
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        hdt[isample] = (TH1F*)pfile[isample]->Get(Form("hdata_topo%d_var%d",indexNSAM[isample],2));
        hmc[isample] = (TH1F*)pfile[isample]->Get(Form("hmc_topo%d_var%d_int%d",indexNSAM[isample],2,0));
        hmcntype[isample] = (TH1F*)pfile[isample]->Get(Form("hmc_topo%d_var%d_int%d",indexNSAM[isample],10,0));
        
        if(isNewVersion){hdtpangvsmuang[isample] = (TH2F*)pfile[isample]->Get(Form("hdtpangvsmuang_topo%d",indexNSAM[isample]));}
        hdtveractvsmuang[isample] = (TH2F*)pfile[isample]->Get(Form("hdtveractvsmuang_topo%d",indexNSAM[isample]));
        hdtveractvspang[isample] = (TH2F*)pfile[isample]->Get(Form("hdtveractvspang_topo%d",indexNSAM[isample]));
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            if(isNewVersion)hmcpangvsmuang[isample][iint] = (TH2F*)pfile[isample]->Get(Form("hmcpangvsmuang_topo%d_int%d",indexNSAM[isample],iint));
            hmcveractvsmuang[isample][iint] = (TH2F*)pfile[isample]->Get(Form("hmcveractvsmuang_topo%d_int%d",indexNSAM[isample],iint));
            hmcveractvspang[isample][iint] = (TH2F*)pfile[isample]->Get(Form("hmcveractvspang_topo%d_int%d",indexNSAM[isample],iint));
        }
    }
    

    
    for (int isample=0; isample<NSAMPLE2CHECK; ++isample) {
        for (Int_t iint=0; iint<4; ++iint) {
            hmcpangvsmuang[isample][iint]->Rebin2D(3,3);
            hmcpangvsmuang[isample][iint]->GetXaxis()->SetRangeUser(0,30);
            hmcpangvsmuang[isample][iint]->GetXaxis()->SetTitle("Reconstructed #mu angle");
            hmcpangvsmuang[isample][iint]->GetYaxis()->SetTitle("Reconstructed #pi angle");
            plot2dcolz(hmcpangvsmuang[isample][iint],subname+Form("sam%d_topo%d",indexNSAM[isample],iint));
        }
    }
    //compare signal vs sideband
    for (Int_t iint=0; iint<4; ++iint) {
        
        new TCanvas;
        hmcpangvsmuang[0][0]->GetXaxis()->SetRangeUser(0,30);
        hmcpangvsmuang[0][0]->Draw("COLZ");
        hmcpangvsmuang[1][0]->SetMarkerSize(0.1);
        hmcpangvsmuang[1][0]->Draw("BOX same");
        gPad->Print("plots/"+subname+"sigvssb"+Form("_topo%d.eps",iint));
    }
   //compare signal vs. cc1pi in signal and CC1pi in sideband
    new TCanvas;
    hmcpangvsmuang[0][1]->Draw("COLZ");
    hmcpangvsmuang[0][3]->Draw("BOX same");
    hmcpangvsmuang[1][3]->SetLineColor(2);
    hmcpangvsmuang[1][3]->Draw("BOX same");
     gPad->Print("plots/"+subname+"sigvssb_cohvs1pi.eps");
}
