{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    
    
    TString subname = "mcen";
    
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_35samv1.root");
    TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_35samv1.root");
    
    
    
    
    const int NVARIABLES = 47;//all variables//update to convert vertex activity
    
    const int NTOPOLOGY = 1;//for sam4testv3, muon cl>0.6, pion cl>0.25, proton <0.05
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    
    char* atitle[NVARIABLES];
    
    
    
    atitle[0] = "Number of tracks";
    atitle[1] = "Number of INGRID-penetrated track";
    atitle[2] = "p-like track angle";
    atitle[3] = "#mu-like track angle";
    atitle[4] = "Mean of #mu-like track light yield";
    atitle[5] = "Mean of p-like track light yield";
    atitle[6] = "Opening angle btw 2 tracks";
    atitle[7] = "Coplanarity btw 2 tracks";
    atitle[8] = "Norm";
    atitle[9] = "totcrsne";
    
    atitle[10] = "inttype";
    atitle[11] = "True neutrino energy (GeV)";
    atitle[12] = "p-like track contained";
    atitle[13] = "#mu-like track contained";
    atitle[14] = "p-like track PDG";
    atitle[15] = "#mu-like track PDG";
    atitle[16] = "Vertex activity";
    atitle[17] = "p-like track confidence level";
    atitle[18] = "#mu-like track confidence level";
    atitle[19] = "p-like track angle";
    atitle[20] = "#mu-like track angle";
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
    atitle[29] = "p-like range";
    
    atitle[30] = "pene";
    atitle[31] = "#mu-like range";
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
        ,4,4,2,2,2,2
        ,1,1,5,5,5,2
        ,2,2,3,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,4,2,2
        ,2,2,2
        ,2,2,2,2,2
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
    
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,200,150
        ,180,180,500,20,60,10
        ,2,2,2500,2500,3000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.2,0.2,300,0.3,5
        ,0.4,0.4,0.4
        ,0.4,0.4,0.4,0.4,0.4
    };
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.05,0.0,0.07,0.0,0.0,0.0
        ,0.05,-0.3,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.2
        ,-0.15,0.07,0.07,0.0,0.0,0.0
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
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmc[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
                //newadd
                hmcgenie[itopo][ivar][iint] = (TH1F*)pfilegenie->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmcgenie[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
            }
            //addnue to nubar for plot
            hmc[itopo][ivar][6]->Add(hmc[itopo][ivar][7]);//newadd
            hmcgenie[itopo][ivar][6]->Add(hmcgenie[itopo][ivar][7]);//newadd
        }//end ivar
    }//end itopo
    hmc[0][11][1]->GetXaxis()->SetTitle("True neutrino energy (GeV)");
    plot2hist_stat(hmc[0][11][1],"NEUT",hmcgenie[0][11][1],"GENIE",subname+"comp_neutgenie_all",false);
    
    
    
    
}
