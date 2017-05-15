{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    
   TString subname = "basicdataneutvsgenie_allv532_antipid";
   TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_all.root");
   TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_all.root");
   TFile *pfilev532 = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_neut5d3d2_all.root");   
 
    
    
    const int NVARIABLES = 47;//48;//all variables//update to convert vertex activity
    const int NTOPOLOGY = 35;//for sam4testv3, muon cl>0.6, pion cl>0.25, proton <0.05
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
    
    TH1F* hdata[NTOPOLOGY][NVARIABLES];
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    TH1F* hmcv532[NTOPOLOGY][NVARIABLES][NINTERACTION];
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
		//neut v5.3.2
		hmcv532[itopo][ivar][iint] = (TH1F*)pfilev532->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmcv532[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);	
                //genie 2.8.0
                hmcgenie[itopo][ivar][iint] = (TH1F*)pfilegenie->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmcgenie[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
            }
            //addnue to nubar for plot
            hmc[itopo][ivar][6]->Add(hmc[itopo][ivar][7]);
	    hmcv532[itopo][ivar][6]->Add(hmcv532[itopo][ivar][7]);
            hmcgenie[itopo][ivar][6]->Add(hmcgenie[itopo][ivar][7]);
           
		if(itopo==22 && !((ivar>7 && ivar<16)||(ivar>20 && ivar<24) )){
                if (ivar==17 || ivar==18){
                    plotbasicdataneutvsgenievsv532zoom(hdata[itopo][ivar],hmcv532[itopo][ivar][0],hmcgenie[itopo][ivar][0],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                }
                else if (ivar==39) plotbasicdataneutvsgenievsv532(hdata[itopo][ivar],hmcv532[itopo][ivar][0],hmcgenie[itopo][ivar][0],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                else if (ivar==36) plotbasicdataneutvsgenievsv532(hdata[itopo][ivar],hmcv532[itopo][ivar][0],hmcgenie[itopo][ivar][0],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
                else plotbasicdataneutvsgenievsv532(hdata[itopo][ivar],hmcv532[itopo][ivar][0],hmcgenie[itopo][ivar][0],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
            }
        }//end ivar
        //energy plots
        /*for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcen[itopo][iint] = (TH1F*)pfile->Get(Form("hmcen_topo%d_int%d",itopo,iint));
        }*/
    }//end itopo
	/*const char *m_color[]={"#000000","#D55E00","#0072B2","#CC79A7","#009E73"};
	const char *m_namequant[]={"All","Q^{2}<0.13 GeV","Q^{2}>0.13 GeV","Quantile III","Quantile IV"};
	//const char *m_namequant[]={"All","Q^{2}<0.08 GeV","Q^{2}>0.08 GeV","Quantile III","Quantile IV"};
	Int_t ci;
	float npot = 6.04193507503274721e20;
    int   nmc  = 3950;
    //int   nmc  = 3974;//for newneut
    float mcpotreweight = npot/(nmc*1e21);
	const Int_t NQUANTCCQE =3;
	//Int_t ATOPOCCQE[NQUANTCCQE]={8,14,15,16,17};
	Int_t ATOPOCCQE[NQUANTCCQE]={8,20,21};
	//Int_t ATOPOCCQE[NQUANTCCQE]={9,18,19};
	//subname +="_cc1p";
	TH1F* hgenierat[NQUANTCCQE];
	TH1F* hneutrat[NQUANTCCQE];
	TH1F* hdatarat[NQUANTCCQE];
	Int_t ithtopo;
	for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
		TString subsubname = Form("var%d",ivar);
		if(ivar==36){
		new TCanvas;
		// TLegend* leg0 = new TLegend(.52, .58, 0.8, .82);
    		TLegend* leg0 = new TLegend(.25, .70, 0.5, .85);
		leg0->SetFillStyle(0);
    		leg0->SetBorderSize(0);
    		leg0->SetTextSize(18);
    		leg0->SetTextFont(43);

		TLegend* leg1 = new TLegend(.3, .25, 0.5, .45);
                leg1->SetFillStyle(0);
                leg1->SetBorderSize(0);
                leg1->SetTextSize(18);
                leg1->SetTextFont(43);
		for (Int_t iquan=0; iquan<NQUANTCCQE; ++iquan) {
		ci = TColor::GetColor(m_color[iquan]);
                ithtopo =ATOPOCCQE[iquan];

		hdata[ithtopo][ivar]->SetMarkerColor(ci);
                hdata[ithtopo][ivar]->SetLineColor(ci);
                hmc[ithtopo][ivar][0]->SetLineColor(ci);
                hmcgenie[ithtopo][ivar][0]->SetLineColor(ci);
                hmcgenie[ithtopo][ivar][0]->SetLineStyle(3);
                hdata[ithtopo][ivar]->GetXaxis()->SetTitle(atitle[ivar]);
                //hdata[ithtopo][ivar]->GetYaxis()->SetTitle("Number of Events");
                hdata[ithtopo][ivar]->GetYaxis()->SetTitle("Area Normalization");
		titleStyle(hdata[ithtopo][ivar]);
                hdata[ithtopo][ivar]->Sumw2();
                hdata[ithtopo][ivar]->Scale(1./hdata[ithtopo][ivar]->GetSumOfWeights());
                if(iquan==0)hdata[ithtopo][ivar]->Draw("ep");
		else hdata[ithtopo][ivar]->Draw("ep same");
                hdata[ithtopo][ivar]->GetYaxis()->SetRangeUser(0,hdata[ithtopo][ivar]->GetMaximum()*2.5);
                hdata[ithtopo][ivar]->GetXaxis()->SetRangeUser(MINCUTVAR[ivar],MAXCUTVAR[ivar]-50);
                hmc[ithtopo][ivar][0]->Scale(mcpotreweight);
                hmcgenie[ithtopo][ivar][0]->Scale(mcpotreweight);
               hmc[ithtopo][ivar][0]->Scale(1./hmc[ithtopo][ivar][0]->GetSumOfWeights());
                hmcgenie[ithtopo][ivar][0]->Scale(1./hmcgenie[ithtopo][ivar][0]->GetSumOfWeights());
                 hmc[ithtopo][ivar][0]->Draw("hist same");
                hmcgenie[ithtopo][ivar][0]->Draw("hist same");
		leg0->AddEntry(hdata[ithtopo][ivar],m_namequant[iquan],"pl");
		}//end iquan
		leg0->SetFillStyle(0);
    		leg0->Draw();
		gPad->Print("plots/"+subname+subsubname+"_quantiles_comp.eps");
		*/
		//ratio plots
		//hgenierat[0]->Draw("hist");
		/*for (Int_t iquan=0; iquan<NQUANTCCQE; ++iquan) {
			ithtopo =ATOPOCCQE[iquan];
                hdatarat[iquan] = (TH1F*)hdata[ithtopo][ivar]->Clone(Form("hdatarat%d",iquan));
                hdatarat[iquan]->Sumw2();
                hdatarat[iquan]->Divide(hdata[ATOPOCCQE[0]][ivar][0]);

                hneutrat[iquan] = (TH1F*)hmc[ithtopo][ivar][0]->Clone(Form("hmcrat%d",iquan));
                hneutrat[iquan]->Sumw2();
                hneutrat[iquan]->Divide(hmc[ATOPOCCQE[0]][ivar][0]);

                hgenierat[iquan] = (TH1F*)hmcgenie[ithtopo][ivar][0]->Clone(Form("hgenierat%d",iquan));
                hgenierat[iquan]->Sumw2();
                hgenierat[iquan]->Divide(hmcgenie[ATOPOCCQE[0]][ivar][0]);

			ci = TColor::GetColor(m_color[iquan]);
			hdatarat[iquan]->SetMarkerColor(ci);
			hdatarat[iquan]->SetLineColor(ci);
			hgenierat[iquan]->SetLineColor(ci);
			hneutrat[iquan]->SetLineColor(ci);
			hgenierat[iquan]->SetLineStyle(3);
			hdatarat[iquan]->GetYaxis()->SetRangeUser(0,1);
			hdatarat[iquan]->GetXaxis()->SetRangeUser(0,250);
			hdatarat[iquan]->GetYaxis()->SetTitle("Quantiles/All");
			hdatarat[iquan]->GetXaxis()->SetTitle(atitle[ivar]);
			titleStyle(hdatarat[iquan]);
			if(iquan==0){
                        leg1->AddEntry(hdatarat[iquan],"Data","pl");
                        leg1->AddEntry(hneutrat[iquan],"MC NEUT","l");
                        leg1->AddEntry(hgenierat[iquan],"MC GENIE","l");
                        }
			if(iquan!=0){
			leg0->AddEntry(hdatarat[iquan],m_namequant[iquan],"lf");
			if(iquan==1)hdatarat[iquan]->Draw("ep");
                        else hdatarat[iquan]->Draw("ep same");
                        hgenierat[iquan]->Draw("hist same");
                        hneutrat[iquan]->Draw("hist same");
			}
		} //end iquan
		leg0->Draw();
		leg1->Draw();
                gPad->Print("plots/"+subname+subsubname+"_quantiles_comp_rat.eps");
		*/
		}//end if ivar
	}//end for ivar
    //compare 4 ccqe-enhanced quantiles

    //plot ccqe distribution
    //plot3hist(true,hmc[4][41][2],"CR1",hmc[5][41][2],"CR2",hmc[6][41][2],"CR3","opt12_ccqepid",0.5,0.5);
    //plot3hist(true,hmc[4][40][2],"CR1",hmc[5][40][2],"CR2",hmc[6][40][2],"CR3","opt12_ccrespid",0.5,0.5);
    //plot distribution for truth information w/ preselection only
    /*hmc[1][36][1]->GetXaxis()->SetTitle("Energy deposite around vertex (MeV)");
    hmc[1][36][1]->GetYaxis()->SetTitle("Number of events (true CC1#picoh)");
    hmc[1][36][1]->SetName("Vertex Act.");
    plot1hist_stat(hmc[1][36][1],"presel_endeposit",true);
    
    hmc[1][39][1]->GetXaxis()->SetTitle("Discriminant para. (CCcoh FSI)");
    hmc[1][39][1]->GetYaxis()->SetTitle("Number of events (true CC1#picoh)");
    hmc[1][39][1]->SetName("Dis. para. coh");
    plot1hist_stat(hmc[1][39][1],"presel_pidfsi",true);
    
    hmc[1][40][1]->GetXaxis()->SetTitle("Discriminant para. (CCres FSI)");
    hmc[1][40][1]->GetYaxis()->SetTitle("Number of events (true CC1#picoh)");
    hmc[1][40][1]->SetName("Dis. para. res");
    plot1hist_stat(hmc[1][40][1],"presel_pidfsires",true);
    
    hmc[1][41][1]->GetXaxis()->SetTitle("Discriminant para. (CCqe FSI)");
    hmc[1][41][1]->GetYaxis()->SetTitle("Number of events (true CC1#picoh)");
    hmc[1][41][1]->SetName("Dis. para. qe");
    plot1hist_stat(hmc[1][41][1],"presel_pidfsiccqe",true);*/
    
    //energy composition
   //plotCompositionwpion(hmcen[3][1],hmcen[3][2],hmcen[3][3],hmcen[3][4],hmcen[3][5],hmcen[3][6],hmcen[3][8],hmcen[3][9],subname+"nuE_comp_2trk_cutmva");
    //plotCompositionwpion(hmc[3][11][1],hmc[3][11][2],hmc[3][11][3],hmc[3][11][4],hmc[3][11][5],hmc[3][11][6],hmc[3][11][8],hmc[3][11][9],subname+"nuE_comp_2trk_cutmva");
    
    //plotCompositionwpion(hmc[25][11][1],hmc[25][11][2],hmc[25][11][3],hmc[25][11][4],hmc[25][11][5],hmc[25][11][6],hmc[25][11][8],hmc[25][11][9],subname+"nuE_comp_2trk_nom");
    
    
    
    //efficiency & purity. THIS IS FOR NEUT
    //purity
    /*cout<<"TMVA purity "<<hmc[3][11][1]->Integral(0,hmc[3][11][1]->GetNbinsX()+1)*100./(hmc[3][11][0]->Integral(0,hmc[3][11][0]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmc[25][11][1]->Integral(0,hmc[25][11][1]->GetNbinsX()+1)*100./hmc[25][11][0]->Integral(0,hmc[25][11][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmc[3][11][1]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmc[3][11][0]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmc[25][11][1]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmc[25][11][0]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,6);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_purity",0.5,0.65);
    
    //efficiency
    cout<<"TMVA efficiency "<<hmc[3][11][1]->Integral(0,hmc[3][11][1]->GetNbinsX()+1)*100./hmc[1][11][1]->Integral(0,hmc[1][11][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmc[25][11][1]->Integral(0,hmc[25][11][1]->GetNbinsX()+1)*100./hmc[1][11][1]->Integral(0,hmc[1][11][1]->GetNbinsX()+1)<<endl;
    
    TH1F* hefficiency_cutmva = hmc[3][11][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmc[1][11][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmc[25][11][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmc[1][11][1]);
    hefficiency_cutnom->Scale(100.);
    
    hefficiency_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,6);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"comp_efficiency",0.2,0.65);*/
    
    
    /*cout<<"TMVA purity "<<hmc[3][19][1]->Integral(0,hmc[3][19][1]->GetNbinsX()+1)*100./(hmc[3][19][0]->Integral(0,hmc[3][19][0]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmc[25][19][1]->Integral(0,hmc[25][19][1]->GetNbinsX()+1)*100./hmc[25][19][0]->Integral(0,hmc[25][19][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmc[3][19][1]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmc[3][19][0]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmc[25][19][1]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmc[25][19][0]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle("#mu-like track angle");
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,50);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_muang_purity",0.2,0.65);
    
    //efficiency
    cout<<"TMVA efficiency "<<hmc[3][19][1]->Integral(0,hmc[3][19][1]->GetNbinsX()+1)*100./hmc[1][19][1]->Integral(0,hmc[1][19][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmc[25][19][1]->Integral(0,hmc[25][19][1]->GetNbinsX()+1)*100./hmc[1][19][1]->Integral(0,hmc[1][19][1]->GetNbinsX()+1)<<endl;
    
    TH1F* hefficiency_cutmva = hmc[3][19][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmc[1][19][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmc[25][19][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmc[1][19][1]);
    hefficiency_cutnom->Scale(100.);
    
    hefficiency_cutmva->GetXaxis()->SetTitle("#mu-like track angle");
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,50);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"comp_muang_efficiency",0.2,0.65);*/
    
    /*cout<<"TMVA purity "<<hmc[3][20][1]->Integral(0,hmc[3][20][1]->GetNbinsX()+1)*100./(hmc[3][20][0]->Integral(0,hmc[3][20][0]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmc[25][20][1]->Integral(0,hmc[25][20][1]->GetNbinsX()+1)*100./hmc[25][20][0]->Integral(0,hmc[25][20][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmc[3][20][1]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmc[3][20][0]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmc[25][20][1]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmc[25][20][0]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle("#pi-like track angle");
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,90);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_pang_purity",0.5,0.65);
    
    //efficiency
    cout<<"TMVA efficiency "<<hmc[3][20][1]->Integral(0,hmc[3][20][1]->GetNbinsX()+1)*100./hmc[1][20][1]->Integral(0,hmc[1][20][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmc[25][20][1]->Integral(0,hmc[25][20][1]->GetNbinsX()+1)*100./hmc[1][20][1]->Integral(0,hmc[1][20][1]->GetNbinsX()+1)<<endl;
    
    TH1F* hefficiency_cutmva = hmc[3][20][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmc[1][20][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmc[25][20][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmc[1][20][1]);
    hefficiency_cutnom->Scale(100.);
    
    hefficiency_cutmva->GetXaxis()->SetTitle("#pi-like track angle");
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,90);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"comp_pang_efficiency",0.2,0.65);*/
    
    //this is for GENIE
    //purity
    /*cout<<"TMVA purity "<<hmcgenie[3][11][1]->Integral(0,hmcgenie[3][11][1]->GetNbinsX()+1)*100./(hmcgenie[3][11][0]->Integral(0,hmcgenie[3][11][0]->GetNbinsX()+1))<<endl;
     cout<<"NOM purity "<<hmcgenie[25][11][1]->Integral(0,hmcgenie[25][11][1]->GetNbinsX()+1)*100./hmcgenie[25][11][0]->Integral(0,hmcgenie[25][11][0]->GetNbinsX()+1)<<endl;
     
     TH1F* hpurity_cutmva = hmcgenie[3][11][1]->Clone("hpurity_cutmva");
     hpurity_cutmva->Divide(hmcgenie[3][11][0]);
     hpurity_cutmva->Scale(100.);
     
     TH1F* hpurity_cutnom = hmcgenie[25][11][1]->Clone("hpurity_cutnom");
     hpurity_cutnom->Divide(hmcgenie[25][11][0]);
     hpurity_cutnom->Scale(100.);
     
     hpurity_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
     hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
     hpurity_cutmva->GetXaxis()->SetRangeUser(0,6);
     hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
     plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"genie_comp_purity",0.5,0.65);
     
     //efficiency
     cout<<"TMVA efficiency "<<hmcgenie[3][11][1]->Integral(0,hmcgenie[3][11][1]->GetNbinsX()+1)*100./hmcgenie[1][11][1]->Integral(0,hmcgenie[1][11][1]->GetNbinsX()+1)<<endl;
     cout<<"NOM efficiency "<<hmcgenie[25][11][1]->Integral(0,hmcgenie[25][11][1]->GetNbinsX()+1)*100./hmcgenie[1][11][1]->Integral(0,hmcgenie[1][11][1]->GetNbinsX()+1)<<endl;
     
     TH1F* hefficiency_cutmva = hmcgenie[3][11][1]->Clone("hefficiency_cutmva");
     hefficiency_cutmva->Divide(hmcgenie[1][11][1]);
     hefficiency_cutmva->Scale(100.);
     
     TH1F* hefficiency_cutnom = hmcgenie[25][11][1]->Clone("hefficiency_cutnom");
     hefficiency_cutnom->Divide(hmcgenie[1][11][1]);
     hefficiency_cutnom->Scale(100.);
     
     hefficiency_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
     hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
     hefficiency_cutmva->GetXaxis()->SetRangeUser(0,6);
     hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
     plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"genie_comp_efficiency",0.2,0.65);*/
    
    
    /*cout<<"TMVA purity "<<hmcgenie[3][19][1]->Integral(0,hmcgenie[3][19][1]->GetNbinsX()+1)*100./(hmcgenie[3][19][0]->Integral(0,hmcgenie[3][19][0]->GetNbinsX()+1))<<endl;
     cout<<"NOM purity "<<hmcgenie[25][19][1]->Integral(0,hmcgenie[25][19][1]->GetNbinsX()+1)*100./hmcgenie[25][19][0]->Integral(0,hmcgenie[25][19][0]->GetNbinsX()+1)<<endl;
     
     TH1F* hpurity_cutmva = hmcgenie[3][19][1]->Clone("hpurity_cutmva");
     hpurity_cutmva->Divide(hmcgenie[3][19][0]);
     hpurity_cutmva->Scale(100.);
     
     TH1F* hpurity_cutnom = hmcgenie[25][19][1]->Clone("hpurity_cutnom");
     hpurity_cutnom->Divide(hmcgenie[25][19][0]);
     hpurity_cutnom->Scale(100.);
     
     hpurity_cutmva->GetXaxis()->SetTitle("#mu-like track angle");
     hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
     hpurity_cutmva->GetXaxis()->SetRangeUser(0,50);
     hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
     plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"genie_comp_muang_purity",0.2,0.65);
     
     //efficiency
     cout<<"TMVA efficiency "<<hmcgenie[3][19][1]->Integral(0,hmcgenie[3][19][1]->GetNbinsX()+1)*100./hmcgenie[1][19][1]->Integral(0,hmcgenie[1][19][1]->GetNbinsX()+1)<<endl;
     cout<<"NOM efficiency "<<hmcgenie[25][19][1]->Integral(0,hmcgenie[25][19][1]->GetNbinsX()+1)*100./hmcgenie[1][19][1]->Integral(0,hmcgenie[1][19][1]->GetNbinsX()+1)<<endl;
     
     TH1F* hefficiency_cutmva = hmcgenie[3][19][1]->Clone("hefficiency_cutmva");
     hefficiency_cutmva->Divide(hmcgenie[1][19][1]);
     hefficiency_cutmva->Scale(100.);
     
     TH1F* hefficiency_cutnom = hmcgenie[25][19][1]->Clone("hefficiency_cutnom");
     hefficiency_cutnom->Divide(hmcgenie[1][19][1]);
     hefficiency_cutnom->Scale(100.);
     
     hefficiency_cutmva->GetXaxis()->SetTitle("#mu-like track angle");
     hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
     hefficiency_cutmva->GetXaxis()->SetRangeUser(0,50);
     hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
     plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"genie_comp_muang_efficiency",0.2,0.65);*/
    
   /* cout<<"TMVA purity "<<hmcgenie[3][20][1]->Integral(0,hmcgenie[3][20][1]->GetNbinsX()+1)*100./(hmcgenie[3][20][0]->Integral(0,hmcgenie[3][20][0]->GetNbinsX()+1))<<endl;
     cout<<"NOM purity "<<hmcgenie[25][20][1]->Integral(0,hmcgenie[25][20][1]->GetNbinsX()+1)*100./hmcgenie[25][20][0]->Integral(0,hmcgenie[25][20][0]->GetNbinsX()+1)<<endl;
     
     TH1F* hpurity_cutmva = hmcgenie[3][20][1]->Clone("hpurity_cutmva");
     hpurity_cutmva->Divide(hmcgenie[3][20][0]);
     hpurity_cutmva->Scale(100.);
     
     TH1F* hpurity_cutnom = hmcgenie[25][20][1]->Clone("hpurity_cutnom");
     hpurity_cutnom->Divide(hmcgenie[25][20][0]);
     hpurity_cutnom->Scale(100.);
     
     hpurity_cutmva->GetXaxis()->SetTitle("#pi-like track angle");
     hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
     hpurity_cutmva->GetXaxis()->SetRangeUser(0,90);
     hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
     plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"genie_comp_pang_purity",0.5,0.65);
     
     //efficiency
     cout<<"TMVA efficiency "<<hmcgenie[3][20][1]->Integral(0,hmcgenie[3][20][1]->GetNbinsX()+1)*100./hmcgenie[1][20][1]->Integral(0,hmcgenie[1][20][1]->GetNbinsX()+1)<<endl;
     cout<<"NOM efficiency "<<hmcgenie[25][20][1]->Integral(0,hmcgenie[25][20][1]->GetNbinsX()+1)*100./hmcgenie[1][20][1]->Integral(0,hmcgenie[1][20][1]->GetNbinsX()+1)<<endl;
     
     TH1F* hefficiency_cutmva = hmcgenie[3][20][1]->Clone("hefficiency_cutmva");
     hefficiency_cutmva->Divide(hmcgenie[1][20][1]);
     hefficiency_cutmva->Scale(100.);
     
     TH1F* hefficiency_cutnom = hmcgenie[25][20][1]->Clone("hefficiency_cutnom");
     hefficiency_cutnom->Divide(hmcgenie[1][20][1]);
     hefficiency_cutnom->Scale(100.);
     
     hefficiency_cutmva->GetXaxis()->SetTitle("#pi-like track angle");
     hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
     hefficiency_cutmva->GetXaxis()->SetRangeUser(0,90);
     hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
     plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"genie_comp_pang_efficiency",0.2,0.65);
    */
    
}
