{
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil_v532.C");
    
    //TString subname = "sidebandvssignal_v532_";
    TString subname = "sidebandvssignal_v532_ana2x_";
    const int NTOPOLOGY = 3;
    TFile *pfile[NTOPOLOGY];
    TFile *pfilegenie[NTOPOLOGY];
    TFile *pfilev5142[NTOPOLOGY];
    //id 14: is presel + >50
    //id 173: pidfsi>0.05 + >50
    //id 174: muang<15, mucl>0.6, pmucl>0.25
    //Int_t topoindex[NTOPOLOGY] = {4,3,170};
    Int_t topoindex[NTOPOLOGY] = {4,170,3};
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        pfile[itopo] = new TFile(Form("../outputs/basicHisto_neut5d3d2_20170529_sam%d.root",topoindex[itopo]));//neut532.
        pfilegenie[itopo] = new TFile(Form("../outputs/basicHisto_genie_20170529_sam%d.root",topoindex[itopo]));//genie.
        pfilev5142[itopo] = new TFile(Form("../outputs/basicHisto_neut5d1d4d2_20170529_sam%d.root",topoindex[itopo]));//neut5.14.2.
    }
    
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    
    //select variable to plots
     /*const int thvariable = 20;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
     TString varname ="pangt";
     char *xtitle = "#pi-like track angle (#circ)";
     double rangemax = 90;
     int nrebin = 9;
     */
     const int thvariable = 37;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
     TString varname ="qsq";
     char *xtitle = "Reconstructed Q^{2} (GeV^{2})";
     double rangemax = 0.3;
     int nrebin = 2;
    

    /*const int thvariable = 19;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="muangt";
    char *xtitle = "#mu-like track angle (#circ)";
    double effmax = 100;
    double rangemax = 50;
    int nrebin = 3;
    */
    
    /*const int thvariable = 36;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
     TString varname ="veract";
     char *xtitle = "Energy deposit at vertex (MeV)";
     double effmax = 30;
     double rangemax = 200;
     int nrebin = 4;
     */
    
    TH1F* hmcen[NTOPOLOGY][NINTERACTION];
    TH1F* hdata[NTOPOLOGY];
    TH1F* hmcengenie[NTOPOLOGY][NINTERACTION];
    TH1F* hmcenv5142[NTOPOLOGY][NINTERACTION];
    
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        //energy plots
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcen[itopo][iint] = (TH1F*)pfile[itopo]->Get(Form("hmc_topo%d_var%d_int%d",topoindex[itopo],thvariable,iint));
            hmcengenie[itopo][iint] = (TH1F*)pfilegenie[itopo]->Get(Form("hmc_topo%d_var%d_int%d",topoindex[itopo],thvariable,iint));
            hmcenv5142[itopo][iint] = (TH1F*)pfilev5142[itopo]->Get(Form("hmc_topo%d_var%d_int%d",topoindex[itopo],thvariable,iint));
            
            hmcen[itopo][iint]->Rebin(nrebin);
            hmcengenie[itopo][iint]->Rebin(nrebin);
            hmcenv5142[itopo][iint]->Rebin(nrebin);
	hmcen[itopo][iint]->GetXaxis()->SetTitle(xtitle);
        }
        hdata[itopo] = (TH1F*)pfile[itopo]->Get(Form("hdata_topo%d_var%d",topoindex[itopo],thvariable));
        hdata[itopo]->Rebin(nrebin);
    }//end itopo
    //all 2 track & forward-2nd track
    
   //compare signal and sideband
   /*hmcen[1][1]->GetXaxis()->SetRangeUser(0,rangemax);
   plot4hist(true,hmcen[1][1],"Selected sample (NEUT 5.3.2)",hmcengenie[1][1],"Selected sample (GENIE)", hmcen[0][1],"Sideband (NEUT 5.3.2)",hmcengenie[0][1],"Sideband (GENIE)",subname+varname+"sig",0.5,0.62);
    //ccres
    hmcen[1][3]->GetXaxis()->SetRangeUser(0,rangemax);
    plot4hist(true,hmcen[1][3],"Selected sample (NEUT 5.3.2)",hmcengenie[1][3],"Selected sample (GENIE)", hmcen[0][3],"Sideband (NEUT 5.3.2)",hmcengenie[0][3],"Sideband (GENIE)",subname+varname+"res",0.5,0.62);
    //ccother
    hmcen[1][4]->GetXaxis()->SetRangeUser(0,rangemax);
    plot4hist(true,hmcen[1][4],"Selected sample (NEUT 5.3.2)",hmcengenie[1][4],"Selected sample (GENIE)", hmcen[0][4],"Sideband (NEUT 5.3.2)",hmcengenie[0][4],"Sideband (GENIE)",subname+varname+"other",0.5,0.62);
*/

	//absolute scale
 hmcen[1][1]->GetXaxis()->SetRangeUser(0,rangemax);
   plot4hist(false,hmcen[1][1],"Selected sample (NEUT 5.3.2)",hmcengenie[1][1],"Selected sample (GENIE)", hmcen[0][1],"Sideband (NEUT 5.3.2)",hmcengenie[0][1],"Sideband (GENIE)",subname+varname+"sig",0.5,0.62);
    //ccres
    hmcen[1][3]->GetXaxis()->SetRangeUser(0,rangemax);
    plot4hist(false,hmcen[1][3],"Selected sample (NEUT 5.3.2)",hmcengenie[1][3],"Selected sample (GENIE)", hmcen[0][3],"Sideband (NEUT 5.3.2)",hmcengenie[0][3],"Sideband (GENIE)",subname+varname+"res",0.5,0.62);
    //ccother
    hmcen[1][4]->GetXaxis()->SetRangeUser(0,rangemax);
    plot4hist(false,hmcen[1][4],"Selected sample (NEUT 5.3.2)",hmcengenie[1][4],"Selected sample (GENIE)", hmcen[0][4],"Sideband (NEUT 5.3.2)",hmcengenie[0][4],"Sideband (GENIE)",subname+varname+"other",0.5,0.62);	

}
