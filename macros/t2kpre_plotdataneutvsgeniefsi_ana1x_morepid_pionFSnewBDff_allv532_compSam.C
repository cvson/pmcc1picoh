{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    Int_t itopo_1 = 22;
    TString subname = "comp";
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_all.root");
    
    Int_t itopo_2 = 103;
    TFile *pfile_2 = new TFile(Form("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_all_sam%d.root",itopo_2));
    
    
    const int NVARIABLES = 47;//48;//all variables//update to convert vertex activity
    const int NTOPOLOGY = 35;//for sam4testv3, muon cl>0.6, pion cl>0.25, proton <0.05
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall
    const int NINTERACTION = 10;
    
    char* atitle[NVARIABLES];
    
    
    //if cut is sepecified
    atitle[0] = "Number of tracks";
    atitle[1] = "Number of INGRID-penetrated track";
    atitle[2] = "#mu-like track angle";
    atitle[3] = "#pi-like track angle";
    
    atitle[4] = "Mean of 2nd track light yield";
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
    atitle[21] = "xnu";
    atitle[22] = "ynu";
    atitle[23] = "znu";
    atitle[24] = "exptime";
    atitle[25] = "Vertex x [mm]";
    atitle[26] = "Vertex y [mm]";
    atitle[27] = "Most upstream plane in reco. X track";
    atitle[28] = "Most upstream plane in reco. Y track";
    atitle[29] = "#mu-like range";
    
    atitle[30] = "pene";
    atitle[31] = "#pi-like range";
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
    Double_t NREBINVAR[NVARIABLES] =   {1,1,2,4,4,4
        ,4,4,2,2,2,4
        ,1,1,5,5,5,2
        ,2,2,3,2,2,2
        ,2,5,5,1,1,2
        ,1,2,1,2,2,2,4,2,2
        ,4,4,4
        ,4,4,4,4,4
    };
    //if signal, sideband
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-0.8,-0.8,-0.8,0,0,0
        ,-0.6,-0.8,-0.8
        ,-0.6,-0.8,-0.8,-0.8,-0.8
    };
    
    
    //anti-pid CC1pi-enhanced
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,45,180,200,150
        ,180,180,500,20,60,10
        ,2,2,2500,2500,3000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.2,0.2,300,0.5,5
        ,0.3,0.4,0.4
        ,0.4,0.4,0.4,0.4,0.4
    };
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.05,0.0,0.07,0.0,0.0,0.0
        ,0.05,-0.3,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.2
        ,-0.15,0.13,-0.3,0.0,0.0,0.0
        ,0.0,0.0,0.0,-0.32,-0.32,-0.3
        ,-0.3,0.0,0.0,-0.3,-0.3,-0.3, 0.05,0.0,0.0
        ,-0.3,-0.3,-0.3
        ,-0.3,-0.3,-0.3,-0.3,-0.3
    };
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.05,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.04
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.03,0.03,0.0,
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0,0.0,0.0
        ,0,0,0
        ,0,0,0,0,0
    };
    
    
    
    
    
    //for file 1
    TH1F* hdata[NTOPOLOGY][NVARIABLES];
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    TH2F* hdtveractvsmuang[NTOPOLOGY];
    TH2F* hmcveractvsmuang[NTOPOLOGY][NINTERACTION];
    TH2F* hdtveractvspang[NTOPOLOGY];
    TH2F* hmcveractvspang[NTOPOLOGY][NINTERACTION];
    
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            TString subsubname = Form("topo%d_var%d",itopo,ivar);
            hdata[itopo][ivar] = (TH1F*)pfile->Get(Form("hdata_topo%d_var%d",itopo,ivar));
            hdata[itopo][ivar]->Rebin(NREBINVAR[ivar]);
            hdtveractvsmuang[itopo] = (TH2F*)pfile->Get(Form("hdtveractvsmuang_topo%d",itopo));
            hdtveractvspang[itopo] = (TH2F*)pfile->Get(Form("hdtveractvspang_topo%d",itopo));
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmc[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
                hmcveractvsmuang[itopo][iint] = (TH2F*)pfile->Get(Form("hmcveractvsmuang_topo%d_int%d",itopo,iint));
                hmcveractvspang[itopo][iint] = (TH2F*)pfile->Get(Form("hmcveractvspang_topo%d_int%d",itopo,iint));
            }
        }//end ivar
    }//end itopo
    
    //for file 2
    TH1F* hdata_2[NVARIABLES];
    TH1F* hmc_2[NVARIABLES][NINTERACTION];
    TH2F* hdtveractvsmuang_2;
    TH2F* hmcveractvsmuang_2[NINTERACTION];
    TH2F* hdtveractvspang_2;
    TH2F* hmcveractvspang_2[NINTERACTION];
    for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
        hdata_2[ivar] = (TH1F*)pfile_2->Get(Form("hdata_topo%d_var%d",itopo_2,ivar));
        hdata_2[ivar]->Rebin(NREBINVAR[ivar]);
        hdtveractvsmuang_2 = (TH2F*)pfile_2->Get(Form("hdtveractvsmuang_topo%d",itopo_2));
        hdtveractvspang_2 = (TH2F*)pfile_2->Get(Form("hdtveractvspang_topo%d",itopo_2));
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmc_2[ivar][iint] = (TH1F*)pfile_2->Get(Form("hmc_topo%d_var%d_int%d",itopo_2,ivar,iint));
            hmc_2[ivar][iint]->Rebin(NREBINVAR[ivar]);
            hmcveractvsmuang_2[iint] = (TH2F*)pfile_2->Get(Form("hmcveractvsmuang_topo%d_int%d",itopo_2,iint));
            hmcveractvspang_2[iint] = (TH2F*)pfile_2->Get(Form("hmcveractvspang_topo%d_int%d",itopo_2,iint));
        }
        
        
    }
    
    /*subname +=Form("_topo%d_vs_topo%d_",itopo_1, itopo_2);
     plot4hist_style3(true,hdata[itopo_1][36],"Data 1-trk CCQE",hmc[itopo_1][36][0],"MC 1-trk CCQE",hdata_2[36],"Data 2-trk CCQE",hmc_2[36][0],"MC 2-trk CCQE",subname+"var36",0.5,0.5);
     plot4hist_style3(true,hdata[itopo_1][19],"Data 1-trk CCQE",hmc[itopo_1][19][0],"MC 1-trk CCQE",hdata_2[19],"Data 2-trk CCQE",hmc_2[19][0],"MC 2-trk CCQE",subname+"var19",0.5,0.5);
     hmcveractvsmuang[itopo_1][0]->GetXaxis()->SetTitle("#mu-like angle");
     hmcveractvsmuang[itopo_1][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
     hmcveractvsmuang[itopo_1][0]->GetYaxis()->SetTitleOffset(1.0);
     plot2dhist_comp(hmcveractvsmuang[itopo_1][0],"MC 1trk CCQE",hmcveractvsmuang_2[0],"MC 2trk CCQE",hdtveractvsmuang[itopo_1],"Data 1trk CCQE",hdtveractvsmuang_2,"Data 2trk CCQE",subname+"veractvsmuang",4,4);
     
     */
    itopo_1 = 20;
    itopo_2 = 21;
    subname +=Form("_topo%d_vs_topo%d_",itopo_1, itopo_2);
    hdata[itopo_1][36]->GetXaxis()->SetTitle("Energy deposit at vertex (MeV)");
    plot4hist_style3(true,hdata[itopo_1][36],"Data Q^{2}<0.13 GeV^{2}",hmc[itopo_1][36][0],"MC  Q^{2}<0.13 GeV^{2}",hdata[itopo_2][36],"Data  Q^{2}>0.13 GeV^{2}",hmc[itopo_2][36][0],"MC  Q^{2}>0.13 GeV^{2}",subname+"var36",0.5,0.5);
    
    hdata[itopo_1][19]->GetXaxis()->SetTitle("#mu-like track angle");
    plot4hist_style3(true,hdata[itopo_1][19],"Data Q^{2}<0.13 GeV^{2}",hmc[itopo_1][19][0],"MC  Q^{2}<0.13 GeV^{2}",hdata[itopo_2][19],"Data  Q^{2}>0.13 GeV^{2}",hmc[itopo_2][19][0],"MC  Q^{2}>0.13 GeV^{2}",subname+"var19",0.5,0.5);
    
    hdata[itopo_1][20]->GetXaxis()->SetTitle("#pi-like track angle");
    plot4hist_style3(true,hdata[itopo_1][20],"Data Q^{2}<0.13 GeV^{2}",hmc[itopo_1][20][0],"MC  Q^{2}<0.13 GeV^{2}",hdata[itopo_2][20],"Data  Q^{2}>0.13 GeV^{2}",hmc[itopo_2][20][0],"MC  Q^{2}>0.13 GeV^{2}",subname+"var20",0.2,0.5);
    
    itopo_1 = 4;
    hmcveractvsmuang[itopo_1][0]->GetXaxis()->SetTitle("#mu-like track angle");
    hmcveractvsmuang[itopo_1][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    plot2dhist_comp0(hmcveractvsmuang[itopo_1][0],"MC",hdtveractvsmuang[itopo_1],"Data",Form("comp_datamc_veractvsmuang_topo%d",itopo_1));
    
    itopo_1 = 8;
    hmcveractvsmuang[itopo_1][0]->GetXaxis()->SetTitle("#mu-like track angle");
    hmcveractvsmuang[itopo_1][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    plot2dhist_comp0(hmcveractvsmuang[itopo_1][0],"MC",hdtveractvsmuang[itopo_1],"Data",Form("comp_datamc_veractvsmuang_topo%d",itopo_1));
    
    itopo_1 = 9;
    hmcveractvsmuang[itopo_1][0]->GetXaxis()->SetTitle("#mu-like track angle");
    hmcveractvsmuang[itopo_1][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    plot2dhist_comp0(hmcveractvsmuang[itopo_1][0],"MC",hdtveractvsmuang[itopo_1],"Data",Form("comp_datamc_veractvsmuang_topo%d",itopo_1));
    
    itopo_1 = 23;
    hmcveractvsmuang[itopo_1][0]->SetMinimum(20);
    hdtveractvsmuang[itopo_1]->SetMinimum(20);
    hmcveractvsmuang[itopo_1][0]->GetXaxis()->SetTitle("#mu-like track angle");
    hmcveractvsmuang[itopo_1][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    plot2dhist_comp0(hmcveractvsmuang[itopo_1][0],"MC",hdtveractvsmuang[itopo_1],"Data",Form("comp_datamc_veractvsmuang_topo%d",itopo_1));
    
    
    itopo_1 = 4;
    hmcveractvspang[itopo_1][0]->GetXaxis()->SetTitle("#pi-like track angle");
    hmcveractvspang[itopo_1][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    plot2dhist_comp0(hmcveractvspang[itopo_1][0],"MC",hdtveractvspang[itopo_1],"Data",Form("comp_datamc_veractvspang_topo%d",itopo_1));
    
    itopo_1 = 8;
    hmcveractvspang[itopo_1][0]->GetXaxis()->SetTitle("p-like track angle");
    hmcveractvspang[itopo_1][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    //plot2dhist(hdtveractvspang[itopo_1],"test");
    //plot2dhist(hmcveractvspang[itopo_1][0],"testmc");
    plot2dhist_comp0(hmcveractvspang[itopo_1][0],"MC",hdtveractvspang[itopo_1],"Data",Form("comp_datamc_veractvspang_topo%d",itopo_1));
    
    itopo_1 = 9;
    hmcveractvspang[itopo_1][0]->GetXaxis()->SetTitle("#pi-like track angle");
    hmcveractvspang[itopo_1][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    plot2dhist_comp0(hmcveractvspang[itopo_1][0],"MC",hdtveractvspang[itopo_1],"Data",Form("comp_datamc_veractvspang_topo%d",itopo_1));
    //plot2dhist_comp(hmcveractvsmuang[itopo_1][0],"MC  Q^{2}<0.13 GeV^{2}",hmcveractvsmuang[itopo_2][0],"MC  Q^{2}>0.13 GeV^{2}",hdtveractvsmuang[itopo_1],"Data Q^{2}<0.13 GeV^{2}",hdtveractvsmuang[itopo_2],"Data Q^{2}>0.13 GeV^{2}",subname+"veractvsmuang",4,4);
}
