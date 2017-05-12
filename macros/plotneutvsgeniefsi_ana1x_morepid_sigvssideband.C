{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    

    TString subname = "neutvsgenie_ana1x_nonveractpid";
    
    
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_35samv1.root");
    TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_35samv1.root");
    
    
    
    const int NVARIABLES = 47;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    //const int NTOPOLOGY = 7;//21;//for finalcomb
    //const int NTOPOLOGY = 17;//for sam4test muon cl>0.6, pion cl>0.6, proton<0.2
    const int NTOPOLOGY = 27;//for sam4testv3, muon cl>0.6, pion cl>0.25, proton <0.05
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    
    char* atitle[NVARIABLES];
    
    atitle[0] = "Number of tracks";
    atitle[1] = "Number of INGRID-penetrated track";
    atitle[2] = "#mu-like track angle";
    atitle[3] = "#pi-like track angle";
    atitle[4] = "Mean of #pi-like track light yield";
    atitle[5] = "Mean of #mu-like track light yield";
    atitle[6] = "Opening angle btw 2 tracks";
    atitle[7] = "Coplanarity btw 2 tracks";
    atitle[8] = "Norm";
    atitle[9] = "totcrsne";
    
    atitle[10] = "inttype";
    atitle[11] = "True neutrino energy (GeV)";
    atitle[12] = "#mu-like track contained";
    atitle[13] = "#pi-like track contained";
    atitle[14] = "#mu-like track PDG";
    atitle[15] = "#pi-like track PDG";
    atitle[16] = "Vertex activity";
    atitle[17] = "#mu-like track confidence level";
    atitle[18] = "#pi-like track confidence level";
    atitle[19] = "#mu-like track angle";
    atitle[20] = "#pi-like track angle";
    //5/6
    //atitle[19] = "First track angle";
    //atitle[20] = "Second track angle";
    atitle[21] = "xnu";
    atitle[22] = "ynu";
    atitle[23] = "znu";
    atitle[24] = "exptime";
    atitle[25] = "startxch";
    atitle[26] = "startych";
    atitle[27] = "startxpln";
    atitle[28] = "startypln";
    atitle[29] = "#mu-like track range";
    
    atitle[30] = "pene";
    atitle[31] = "#pi-like track range";
    atitle[32] = "ppene";
    atitle[33] = "Discriminant parameter (COH)";
    atitle[34] = "Discriminant parameter (RES)";
    atitle[35] = "Discriminant parameter (CCQE)";
    atitle[36] = "Energy deposit at vertex (MeV)";
    atitle[37] = "Reconstructed Q^{2} (GeV^{2})";
    atitle[38] = "Reconstructed momentum (GeV))";
    
    atitle[39] = "Discriminant parameter (COH)";
    atitle[40] = "Discriminant parameter (RES)";
    atitle[41] = "Discriminant parameter (CCQE)";
    atitle[42] = "Discriminant parameter (RES)";
    atitle[43] = "Discriminant parameter (CCQE)";
    atitle[44] = "Discriminant parameter (COH, no #mu-range)";
    atitle[45] = "Discriminant parameter (CCQE, no #mu-range)";
    atitle[46] = "Discriminant parameter (RES, no #mu-range)";

    
    //if cut is not specific
    /*atitle[0] = "Number of tracks";
    atitle[1] = "Number of INGRID-penetrated track";
    atitle[2] = "1st track angle";
    atitle[3] = "2nd track angle";
    atitle[4] = "Mean of 2nd track light yield";
    atitle[5] = "Mean of 1st track light yield";
    atitle[6] = "Opening angle btw 2 tracks";
    atitle[7] = "Coplanarity btw 2 tracks";
    atitle[8] = "Norm";
    atitle[9] = "totcrsne";
    
    atitle[10] = "inttype";
    atitle[11] = "True neutrino energy (GeV)";
    atitle[12] = "1st track contained";
    atitle[13] = "2nd track contained";
    atitle[14] = "1st track PDG";
    atitle[15] = "2nd track PDG";
    atitle[16] = "Vertex activity";
    atitle[17] = "1st track confidence level";
    atitle[18] = "2nd track confidence level";
    atitle[19] = "1st track angle";
    atitle[20] = "2nd track angle";
    //5/6
    //atitle[19] = "First track angle";
    //atitle[20] = "Second track angle";
    atitle[21] = "xnu";
    atitle[22] = "ynu";
    atitle[23] = "znu";
    atitle[24] = "exptime";
    atitle[25] = "startxch";
    atitle[26] = "startych";
    atitle[27] = "startxpln";
    atitle[28] = "startypln";
    atitle[29] = "1st range";
    
    atitle[30] = "pene";
    atitle[31] = "2nd range";
    atitle[32] = "ppene";
    atitle[33] = "Discriminant parameter (COH)";
    atitle[34] = "Discriminant parameter (RES)";
    atitle[35] = "Discriminant parameter (CCQE)";
    atitle[36] = "Energy deposit at vertex (MeV)";
    atitle[37] = "Reconstructed Q^{2} (GeV^{2})";
    atitle[38] = "Reconstructed momentum (GeV))";
    
    atitle[39] = "Discriminant parameter (COH)";
    atitle[40] = "Discriminant parameter (RES)";
    atitle[41] = "Discriminant parameter (CCQE)";
    atitle[42] = "Discriminant parameter (RES)";
    atitle[43] = "Discriminant parameter (CCQE)";
    atitle[44] = "Discriminant parameter (COH, no #mu-range)";
    atitle[45] = "Discriminant parameter (CCQE, no #mu-range)";
    atitle[46] = "Discriminant parameter (RES, no #mu-range)";
    */
    
    Double_t MINVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1,-1,-1,0,0,0
        ,-1,-1,-1
        ,-1,-1,-1,-1,-1
    };
    Double_t MAXVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,1,1,1,400,1,5
        ,1,1,1
        ,1,1,1,1,1
    };
    
    //more 2 track
    Double_t NBINVAR[NVARIABLES] =   {10,10,90,180,200,200
        ,180,180,200,50,60,100
        ,2,2,500,500,500,100
        ,100,90,90,120,120,100
        ,120,120,120,16,16,100
        ,11,100,11,200,200,200,200,100,100
        ,200,200,200
        ,200,200,200,200,200
    };
    /*Double_t NREBINVAR[NVARIABLES] =   {1,1,2,4,4,4
        ,4,4,2,2,2,4
        ,1,1,5,5,5,2
        ,2,2,2,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,4,2,2
        ,2,2,2
        ,2,2,2,2,2
    };*/
    Double_t NREBINVAR[NVARIABLES] =   {1,1,2,4,4,4
        ,4,4,2,2,2,4
        ,1,1,5,5,5,2
        ,2,9,9,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,4,2,2
        ,2,2,2
        ,2,2,2,2,2
    };
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-0.8,-0.8,-0.8,0,0,0
        ,-0.8,-0.8,-0.8
        ,-0.8,-0.8,-0.8,-0.8,-0.8
    };
    
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,45,180,200,150
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,45,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.2,0.2,300,0.3,5
        ,0.3,0.4,0.4
        ,0.4,0.4,0.4,0.4,0.4
    };
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.05,0.0,0.07,0.0,0.0,0.0
        ,0.05,-0.3,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.1
        ,0.0,0.07,-0.1,0.0,0.0,0.0
        ,0.0,0.0,0.0,-0.32,-0.32,-0.3
        ,-0.3,0.0,0.0,-0.3,-0.3,-0.3, 0.05,0.0,0.0
        ,-0.3,-0.3,-0.3
        ,-0.3,-0.3,-0.3,-0.3,-0.3
    };
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.05,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,-0.25,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.03,0.03,0.0,
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0,0.0,0.0
        ,0,0,0
        ,0,0,0,0,0
    };
    
    TH1F* hdata[NTOPOLOGY][NVARIABLES];
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    TH1F* hmcgenie[NTOPOLOGY][NVARIABLES][NINTERACTION];
    TH1F* hmcen[NTOPOLOGY][NINTERACTION];
    double pidcut = 0.08;
    double pidcutlong = 0.3;
    double veractcut = 36;//475*7.6634e-2;
    double veractcutlong = 5;
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            TString subsubname = Form("topo%d_var%d",itopo,ivar);
            hdata[itopo][ivar] = (TH1F*)pfile->Get(Form("hdata_topo%d_var%d",itopo,ivar));
            hdata[itopo][ivar]->Rebin(NREBINVAR[ivar]);
            //hdata[itopo][ivar]->GetXaxis()->SetRangeUser(MINCUTVAR[ivar],MAXCUTVAR[ivar]);
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmc[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
                hmc[itopo][ivar][iint]->GetXaxis()->SetTitle(atitle[ivar]);
                //newadd
                hmcgenie[itopo][ivar][iint] = (TH1F*)pfilegenie->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmcgenie[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
            }
            //addnue to nubar for plot
            hmc[itopo][ivar][6]->Add(hmc[itopo][ivar][7]);//newadd
            hmcgenie[itopo][ivar][6]->Add(hmcgenie[itopo][ivar][7]);//newadd
        }
        
            
    }//end itopo
        //plot 4 hist for background NEUT vs GENIE in signal and sideband
    //this is area normalization
    //signal
    /*hmc[3][36][1]->GetXaxis()->SetRangeUser(0,100);
        plot4hist(true,hmc[3][36][1],"Selected sample (NEUT)",hmcgenie[3][36][1],"Selected sample (GENIE)", hmc[21][36][1],"Sideband (NEUT)",hmcgenie[21][36][1],"Sideband (GENIE)",subname+"sig_signalvssideband_veract",0.5,0.55);
    
    hmc[3][37][1]->GetXaxis()->SetRangeUser(0,0.3);
    plot4hist(true,hmc[3][37][1],"Selected sample (NEUT)",hmcgenie[3][37][1],"Selected sample (GENIE)", hmc[21][37][1],"Sideband (NEUT)",hmcgenie[21][37][1],"Sideband (GENIE)",subname+"sig_signalvssideband_Qsq",0.5,0.55);
    
    hmc[3][19][1]->GetXaxis()->SetRangeUser(0,50);
    plot4hist(true,hmc[3][19][1],"Selected sample (NEUT)",hmcgenie[3][19][1],"Selected sample (GENIE)", hmc[21][19][1],"Sideband (NEUT)",hmcgenie[21][19][1],"Sideband (GENIE)",subname+"sig_signalvssideband_muang",0.5,0.55);
    hmc[3][20][1]->GetXaxis()->SetRangeUser(0,90);
    plot4hist(true,hmc[3][20][1],"Selected sample (NEUT)",hmcgenie[3][20][1],"Selected sample (GENIE)", hmc[21][20][1],"Sideband (NEUT)",hmcgenie[21][20][1],"Sideband (GENIE)",subname+"sig_signalvssideband_pang",0.5,0.55);
    
    
    //ccres
    hmc[3][36][3]->GetXaxis()->SetRangeUser(0,100);
    plot4hist(true,hmc[3][36][3],"Selected sample (NEUT)",hmcgenie[3][36][3],"Selected sample (GENIE)", hmc[21][36][3],"Sideband (NEUT)",hmcgenie[21][36][3],"Sideband (GENIE)",subname+"res_signalvssideband_veract",0.5,0.55);
    
    hmc[3][37][3]->GetXaxis()->SetRangeUser(0,0.3);
    plot4hist(true,hmc[3][37][3],"Selected sample (NEUT)",hmcgenie[3][37][3],"Selected sample (GENIE)", hmc[21][37][3],"Sideband (NEUT)",hmcgenie[21][37][3],"Sideband (GENIE)",subname+"res_signalvssideband_Qsq",0.5,0.55);
    
    hmc[3][19][3]->GetXaxis()->SetRangeUser(0,50);
    plot4hist(true,hmc[3][19][3],"Selected sample (NEUT)",hmcgenie[3][19][3],"Selected sample (GENIE)", hmc[21][19][3],"Sideband (NEUT)",hmcgenie[21][19][3],"Sideband (GENIE)",subname+"res_signalvssideband_muang",0.5,0.55);
    hmc[3][20][3]->GetXaxis()->SetRangeUser(0,90);
    plot4hist(true,hmc[3][20][3],"Selected sample (NEUT)",hmcgenie[3][20][3],"Selected sample (GENIE)", hmc[21][20][3],"Sideband (NEUT)",hmcgenie[21][20][3],"Sideband (GENIE)",subname+"res_signalvssideband_pang",0.5,0.55);
    
    
    //ccother
    hmc[3][36][4]->GetXaxis()->SetRangeUser(0,100);
    plot4hist(true,hmc[3][36][4],"Selected sample (NEUT)",hmcgenie[3][36][4],"Selected sample (GENIE)", hmc[21][36][4],"Sideband (NEUT)",hmcgenie[21][36][4],"Sideband (GENIE)",subname+"other_signalvssideband_veract",0.5,0.55);
    
    hmc[3][37][4]->GetXaxis()->SetRangeUser(0,0.3);
    plot4hist(true,hmc[3][37][4],"Selected sample (NEUT)",hmcgenie[3][37][4],"Selected sample (GENIE)", hmc[21][37][4],"Sideband (NEUT)",hmcgenie[21][37][4],"Sideband (GENIE)",subname+"other_signalvssideband_Qsq",0.5,0.55);
    
    hmc[3][19][4]->GetXaxis()->SetRangeUser(0,50);
    plot4hist(true,hmc[3][19][4],"Selected sample (NEUT)",hmcgenie[3][19][4],"Selected sample (GENIE)", hmc[21][19][4],"Sideband (NEUT)",hmcgenie[21][19][4],"Sideband (GENIE)",subname+"other_signalvssideband_muang",0.5,0.55);
    hmc[3][20][4]->GetXaxis()->SetRangeUser(0,90);
    plot4hist(true,hmc[3][20][4],"Selected sample (NEUT)",hmcgenie[3][20][4],"Selected sample (GENIE)", hmc[21][20][4],"Sideband (NEUT)",hmcgenie[21][20][4],"Sideband (GENIE)",subname+"other_signalvssideband_pang",0.5,0.55);*/
    
    //POT normalization
    
    hmc[3][36][1]->GetXaxis()->SetRangeUser(0,100);
    plot4hist(false,hmc[3][36][1],"Selected sample (NEUT)",hmcgenie[3][36][1],"Selected sample (GENIE)", hmc[21][36][1],"Sideband (NEUT)",hmcgenie[21][36][1],"Sideband (GENIE)",subname+"sig_signalvssideband_veract",0.5,0.55);
    
    hmc[3][37][1]->GetXaxis()->SetRangeUser(0,0.3);
    plot4hist(false,hmc[3][37][1],"Selected sample (NEUT)",hmcgenie[3][37][1],"Selected sample (GENIE)", hmc[21][37][1],"Sideband (NEUT)",hmcgenie[21][37][1],"Sideband (GENIE)",subname+"sig_signalvssideband_Qsq",0.5,0.55);
    
    hmc[3][19][1]->GetXaxis()->SetRangeUser(0,50);
    plot4hist(false,hmc[3][19][1],"Selected sample (NEUT)",hmcgenie[3][19][1],"Selected sample (GENIE)", hmc[21][19][1],"Sideband (NEUT)",hmcgenie[21][19][1],"Sideband (GENIE)",subname+"sig_signalvssideband_muang",0.5,0.55);
    hmc[3][20][1]->GetXaxis()->SetRangeUser(0,90);
    plot4hist(false,hmc[3][20][1],"Selected sample (NEUT)",hmcgenie[3][20][1],"Selected sample (GENIE)", hmc[21][20][1],"Sideband (NEUT)",hmcgenie[21][20][1],"Sideband (GENIE)",subname+"sig_signalvssideband_pang",0.5,0.55);
    
    
    //ccres
    hmc[3][36][3]->GetXaxis()->SetRangeUser(0,100);
    plot4hist(false,hmc[3][36][3],"Selected sample (NEUT)",hmcgenie[3][36][3],"Selected sample (GENIE)", hmc[21][36][3],"Sideband (NEUT)",hmcgenie[21][36][3],"Sideband (GENIE)",subname+"res_signalvssideband_veract",0.5,0.55);
    
    hmc[3][37][3]->GetXaxis()->SetRangeUser(0,0.3);
    plot4hist(false,hmc[3][37][3],"Selected sample (NEUT)",hmcgenie[3][37][3],"Selected sample (GENIE)", hmc[21][37][3],"Sideband (NEUT)",hmcgenie[21][37][3],"Sideband (GENIE)",subname+"res_signalvssideband_Qsq",0.5,0.55);
    
    hmc[3][19][3]->GetXaxis()->SetRangeUser(0,50);
    plot4hist(false,hmc[3][19][3],"Selected sample (NEUT)",hmcgenie[3][19][3],"Selected sample (GENIE)", hmc[21][19][3],"Sideband (NEUT)",hmcgenie[21][19][3],"Sideband (GENIE)",subname+"res_signalvssideband_muang",0.5,0.55);
    hmc[3][20][3]->GetXaxis()->SetRangeUser(0,90);
    plot4hist(false,hmc[3][20][3],"Selected sample (NEUT)",hmcgenie[3][20][3],"Selected sample (GENIE)", hmc[21][20][3],"Sideband (NEUT)",hmcgenie[21][20][3],"Sideband (GENIE)",subname+"res_signalvssideband_pang",0.5,0.55);
    
    
    //ccother
    hmc[3][36][4]->GetXaxis()->SetRangeUser(0,100);
    plot4hist(false,hmc[3][36][4],"Selected sample (NEUT)",hmcgenie[3][36][4],"Selected sample (GENIE)", hmc[21][36][4],"Sideband (NEUT)",hmcgenie[21][36][4],"Sideband (GENIE)",subname+"other_signalvssideband_veract",0.5,0.55);
    
    hmc[3][37][4]->GetXaxis()->SetRangeUser(0,0.3);
    plot4hist(false,hmc[3][37][4],"Selected sample (NEUT)",hmcgenie[3][37][4],"Selected sample (GENIE)", hmc[21][37][4],"Sideband (NEUT)",hmcgenie[21][37][4],"Sideband (GENIE)",subname+"other_signalvssideband_Qsq",0.5,0.55);
    
    hmc[3][19][4]->GetXaxis()->SetRangeUser(0,50);
    plot4hist(false,hmc[3][19][4],"Selected sample (NEUT)",hmcgenie[3][19][4],"Selected sample (GENIE)", hmc[21][19][4],"Sideband (NEUT)",hmcgenie[21][19][4],"Sideband (GENIE)",subname+"other_signalvssideband_muang",0.5,0.55);
    hmc[3][20][4]->GetXaxis()->SetRangeUser(0,90);
    plot4hist(false,hmc[3][20][4],"Selected sample (NEUT)",hmcgenie[3][20][4],"Selected sample (GENIE)", hmc[21][20][4],"Sideband (NEUT)",hmcgenie[21][20][4],"Sideband (GENIE)",subname+"other_signalvssideband_pang",0.5,0.55);
    
    
    
        
        
      
}
