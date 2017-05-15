{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
   Int_t isample = 145;
   //TString subname = Form("basicdataneutvsgenie_allv532_sam%d",isample);
   //for sample smaller than 100
   /*TFile *pfile = new TFile(Form("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_all_sam%d.root",isample));
   TFile *pfilegenie = new TFile(Form("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_all_sam%d.root",isample));
   TFile *pfilev532 = new TFile(Form("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_neut5d3d2_all_sam%d.root",isample));   
   */

   //for sample larger than 100
   /*TString subname = Form("basicdataneutvsgenie_allv532_20170307_sam%d",isample);
   TFile *pfile = new TFile(Form("../outputs/basicHisto_20170307_sam%d.root",isample));
   TFile *pfilegenie = new TFile(Form("../outputs/basicHisto_genie_20170307_sam%d.root",isample));
   TFile *pfilev532 = new TFile(Form("../outputs/basicHisto_neut5d3d2_20170307_sam%d.root",isample));
    */
	//to check genie composition
    TString subname = Form("basicdataneutvsgenie_allv532_20170307_tmpgenie_sam%d",isample);
   TFile *pfilegenie = new TFile(Form("../outputs/basicHisto_20170307_sam%d.root",isample));
   TFile *pfile = new TFile(Form("../outputs/basicHisto_genie_20170307_sam%d.root",isample));
   TFile *pfilev532 = new TFile(Form("../outputs/basicHisto_neut5d3d2_20170307_sam%d.root",isample));
    
    const int NVARIABLES = 47;//48;//all variables//update to convert vertex activity
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall
    const int NINTERACTION = 10;
    
    char* atitle[NVARIABLES];
    
    
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
    
    /*Double_t MAXCUTVAR[NVARIABLES] =   {0,10,45,180,200,150
        ,180,180,500,20,60,10
        ,2,2,2500,2500,3000,1
        ,1,45,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.2,0.2,300,0.3,5
        ,0.3,0.4,0.4
        ,0.4,0.2,0.4,0.4,0.4
    };*/
    /*Double_t MAXCUTVAR[NVARIABLES] =   {0,10,45,180,200,150
        ,180,180,500,20,60,10
        ,2,2,2500,2500,3000,1
        ,1,45,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.2,0.2,300,0.3,5
        ,0.3,0.4,0.4
        ,0.4,0.4,0.4,0.4,0.4
    };

       Double_t XLEGSHIFT[NVARIABLES] =    {0.05,0.0,0.07,0.0,0.0,0.0
        ,0.05,-0.3,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.2
        ,-0.15,0.07,0.13,0.0,0.0,0.0
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
    */
//anti-pid CCQE-enhanced
/*Double_t MAXCUTVAR[NVARIABLES] =   {0,10,45,180,200,150
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
        ,0.13,-0.3,-0.3
        ,0.13,-0.3,-0.3,-0.3,-0.3
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
    
*/

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
    

    
    //if preselection
    /*Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-0.8,-0.8,-0.8,0,0,0
        ,-0.8,-0.8,-0.8
        ,-0.8,-0.8,-0.8,-0.8,-0.8
    };
    
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,200,150
        ,180,180,500,20,60,10
        ,2,2,2500,2500,1000,1
        ,1,60,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.2,0.2,100,0.5,5
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
    };*/
    
    TH1F* hdata[NVARIABLES];
    TH1F* hmc[NVARIABLES][NINTERACTION];
    TH1F* hmcv532[NVARIABLES][NINTERACTION];
    TH1F* hmcgenie[NVARIABLES][NINTERACTION];
    TH1F* hmcen[NINTERACTION];
    double pidcut = 0.08;
    double pidcutlong = 0.3;
    double veractcut = 36;//475*7.6634e-2;
    double veractcutlong = 5;
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            TString subsubname = Form("_var%d",ivar);
            hdata[ivar] = (TH1F*)pfile->Get(Form("hdata_topo%d_var%d",isample,ivar));
            hdata[ivar]->Rebin(NREBINVAR[ivar]);
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[ivar][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",isample,ivar,iint));
                hmc[ivar][iint]->Rebin(NREBINVAR[ivar]);
		//neut v5.3.2
		hmcv532[ivar][iint] = (TH1F*)pfilev532->Get(Form("hmc_topo%d_var%d_int%d",isample,ivar,iint));
                hmcv532[ivar][iint]->Rebin(NREBINVAR[ivar]);	
                //genie 2.8.0
                hmcgenie[ivar][iint] = (TH1F*)pfilegenie->Get(Form("hmc_topo%d_var%d_int%d",isample,ivar,iint));
                hmcgenie[ivar][iint]->Rebin(NREBINVAR[ivar]);
            }
            //addnue to nubar for plot
            hmc[ivar][6]->Add(hmc[ivar][7]);
	    hmcv532[ivar][6]->Add(hmcv532[ivar][7]);
            hmcgenie[ivar][6]->Add(hmcgenie[ivar][7]);
           
		if(!((ivar>7 && ivar<16)||(ivar>20 && ivar<25) )){
                if (ivar==17 || ivar==18){
                    plotbasicdataneutvsgenievsv532zoom(hdata[ivar],hmcv532[ivar][0],hmcgenie[ivar][0],hmc[ivar][1],hmc[ivar][2],hmc[ivar][3],hmc[ivar][4],hmc[ivar][5],hmc[ivar][6],hmc[ivar][8],hmc[ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                }
                else if (ivar==39) plotbasicdataneutvsgenievsv532(hdata[ivar],hmcv532[ivar][0],hmcgenie[ivar][0],hmc[ivar][1],hmc[ivar][2],hmc[ivar][3],hmc[ivar][4],hmc[ivar][5],hmc[ivar][6],hmc[ivar][8],hmc[ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                else if (ivar==36) plotbasicdataneutvsgenievsv532(hdata[ivar],hmcv532[ivar][0],hmcgenie[ivar][0],hmc[ivar][1],hmc[ivar][2],hmc[ivar][3],hmc[ivar][4],hmc[ivar][5],hmc[ivar][6],hmc[ivar][8],hmc[ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
                else plotbasicdataneutvsgenievsv532(hdata[ivar],hmcv532[ivar][0],hmcgenie[ivar][0],hmc[ivar][1],hmc[ivar][2],hmc[ivar][3],hmc[ivar][4],hmc[ivar][5],hmc[ivar][6],hmc[ivar][8],hmc[ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
            }
        }//end ivar
        //energy plots
    
}
