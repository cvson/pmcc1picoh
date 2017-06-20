{
    
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    Int_t isample = 0;
  
   TString opFilename = Form("../outputs/trueinfo_neut5d1d4d2_sam%d.root",isample);
   TFile *popfile = new TFile(opFilename);
   TFile *popfilegenie = new TFile(Form("../outputs/trueinfo_genie_sam%d.root",isample));
   TFile *popfilev532 = new TFile(Form("../outputs/trueinfo_neut5d3d2_sam%d.root",isample));    
TString subname = Form("basicTrueInfo_comp_genie_sam%d",isample);
   



    const Int_t NINTERACTION = 6;

    const Int_t NVARIABLES = 60;
    Int_t NBINHIST[NVARIABLES]={10,10,90,180,200
        ,200,180,180,200,50
        ,60,100,2,2,500
        ,500,500,100,100,90
        ,90,120,120,100,120
        ,120,120,16,16,100
        ,11,100,11,200,200
        ,200,200,100,100,200,200,200
        ,200,200,200,200,200
	,200,200,200,200,200
        ,200,200,200,200,180
        ,200,180,200
};
    Double_t XMIN[NVARIABLES]={0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0,0,0
        ,0,-60,-60,-160,-540
        ,0,0,0,0,0
        ,0,0,11,-1,-1
        ,-1,0,0,0,-1,-1,-1
        ,-1,-1,-1,-1,-1
	,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0
};
    Double_t XMAX[NVARIABLES]={10,10,90,180,500
        ,500,180,180,500,20
        ,60,10,2,2,2500
        ,2500,5000,1,1,90
        ,90,60,60,-60,-480
        ,1200,1200,16,16,100
        ,11,100,11,1,1,
        1,400,1,5,1,1,1
        ,1,1,1,1,1
	,10,10,5,5,5
        ,3,20,10,10,90
        ,20,90,20
};
    
  char* atitle[NVARIABLES];
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

    atitle[47] = "#mu true energy (GeV)";
    atitle[48] = "#mu momentum (GeV)";
    atitle[49] = "#pi true energy (GeV)";
    atitle[50] = "#pi true momentum (GeV)";
    atitle[51] = "True Q^{2} (GeV^{2})";
    atitle[52] = "True x bjorken";
    atitle[53] = "True |t|^{2} (GeV^{2})";
    atitle[54] = "True recoil energy (GeV)";
    atitle[55] = "True invariant hadronic mass (GeV)";

    atitle[56] = "True #mu angle";
    atitle[57] = "(True-reco) #mu angle";
    atitle[58] = "True #pi angle";
    atitle[59] = "(True-reco) #pi angle";
   


    Double_t NREBINVAR[NVARIABLES] =   {1,1,2,4,4,4
        ,4,4,2,2,2,4
        ,1,1,5,5,5,2
        ,2,2,3,2,2,2
        ,2,5,5,1,1,2
        ,1,2,1,2,2,2,4,2,2
        ,4,4,4
        ,4,4,4,4,4
	,2,2,2,2,2
        ,2,1,2,2,2
        ,2,2,2
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
	,0,0,0,0,0
        ,0,0,0,0,0
        ,0,0,0
    };

   Double_t MAXCUTVAR[NVARIABLES] =   {0,10,45,180,200,150
        ,180,180,500,20,60,10
        ,2,2,2500,2500,3000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.2,0.2,200,0.5,5
        ,0.3,0.4,0.4
        ,0.4,0.4,0.4,0.4,0.4
	,5,5,3,3,2
        ,1,2,4,6,90
        ,20,90,20
    };

    Double_t XLEGSHIFT[NVARIABLES] =    {0.05,0.0,0.07,0.0,0.0,0.0
        ,0.05,-0.3,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.2
        ,-0.15,0.13,-0.3,0.0,0.0,0.0
        ,0.0,0.0,0.0,-0.32,-0.32,-0.3
        ,-0.3,0.0,0.0,-0.3,-0.3,-0.3, 0.05,0.0,0.0
        ,-0.3,-0.3,-0.3
        ,-0.3,-0.3,-0.3,-0.3,-0.3
	,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0
    };
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.05,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.04
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.03,0.03,0.0,
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0,0.0,0.0
        ,0,0,0
        ,0,0,0,0,0
	,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0
    };

TH1F* hmc[NVARIABLES][NINTERACTION];
TH1F* hmcgenie[NVARIABLES][NINTERACTION];
TH1F* hmcv532[NVARIABLES][NINTERACTION];
  for (Int_t ivar=47; ivar<NVARIABLES; ++ivar) {
        //for mc
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmc[ivar][iint] = (TH1F*)popfile->Get(Form("hmc_var%d_int%d",ivar,iint));
       	     hmc[ivar][iint]->Rebin(NREBINVAR[ivar]);
		hmcgenie[ivar][iint] = (TH1F*)popfilegenie->Get(Form("hmc_var%d_int%d",ivar,iint));
		//hmcgenie[ivar][iint]->Scale(3950.0/3974.0);
	        hmcgenie[ivar][iint]->Rebin(NREBINVAR[ivar]);
		  hmcv532[ivar][iint] = (TH1F*)popfilev532->Get(Form("hmc_var%d_int%d",ivar,iint));
                hmcv532[ivar][iint]->Scale(3950.0/3974.0);
                hmcv532[ivar][iint]->Rebin(NREBINVAR[ivar]);

             hmc[ivar][iint]->GetXaxis()->SetTitle(atitle[ivar]);
		hmc[ivar][iint]->GetYaxis()->SetTitle("Event number (POT normalization)");
             hmc[ivar][iint]->GetXaxis()->SetRangeUser(MINCUTVAR[ivar],MAXCUTVAR[ivar]);

		hmcgenie[ivar][iint]->GetXaxis()->SetTitle(atitle[ivar]);
             hmcgenie[ivar][iint]->GetXaxis()->SetRangeUser(MINCUTVAR[ivar],MAXCUTVAR[ivar]);
	 
	}
	TString subsubname = Form("_var%d",ivar);
	//plot2hist(hmcgenie[ivar][3],"GENIE 2.8.0",hmc[ivar][3],"NEUT 5.1.4.2",subname+subsubname,0.65,0.65);
	plot3histStyle1(false, hmc[ivar][1],"NEUT 5.1.4.2",hmcv532[ivar][1],"NEUT 5.3.2",hmcgenie[ivar][1],"GENIE 2.8.0",subname+subsubname+"cccoh",0.65,0.65);
	plot3histStyle1(false, hmc[ivar][3],"NEUT 5.1.4.2",hmcv532[ivar][3],"NEUT 5.3.2",hmcgenie[ivar][3],"GENIE 2.8.0",subname+subsubname+"cc1pi",0.65,0.65);
    	plot3histStyle1(false, hmc[ivar][2],"NEUT 5.1.4.2",hmcv532[ivar][2],"NEUT 5.3.2",hmcgenie[ivar][2],"GENIE 2.8.0",subname+subsubname+"cc0pi",0.65,0.65);
	plot3histStyle1(false, hmc[ivar][4],"NEUT 5.1.4.2",hmcv532[ivar][4],"NEUT 5.3.2",hmcgenie[ivar][4],"GENIE 2.8.0",subname+subsubname+"ccnpi",0.65,0.65);
	}

//plot 2d
        popfile->Close();
	popfilegenie->Close();
 
 
}
