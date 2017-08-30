{
   //swithc between genie, neut5d3d2, genie 
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil_v532.C");
    const Int_t NSAMPLE = 3;
	//3 is Ana1, 147 is Ana2
    Int_t samIndex[NSAMPLE]={0,147,29};// 28 is Kikawa's original sel., 29 is without side-escaping
    
    //Int_t isample = 0;
    
    //TString opFilename = Form("../outputs/trueinfo_genie_sam%d.root",isample);
    TFile *popfile[NSAMPLE];//
    TFile *popfilev1542[NSAMPLE];
    TFile *popfilegenie[NSAMPLE];
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        if(isam==0) {
            popfile[isam] = new TFile(Form("../outputs/trueinfo_neut5d3d2_nominal_sam%d.root",samIndex[isam]));
            popfilev1542[isam] = new TFile(Form("../outputs/trueinfo_neut5d1d4d2_nominal_sam%d.root",samIndex[isam]));
            popfilegenie[isam] = new TFile(Form("../outputs/trueinfo_genie_nominal_sam%d.root",samIndex[isam]));
        }
        else {
            popfile[isam] = new TFile(Form("../outputs/trueinfo_neut5d3d2_sam%d.root",samIndex[isam]));
            popfilev1542[isam] = new TFile(Form("../outputs/trueinfo_neut5d1d4d2_sam%d.root",samIndex[isam]));
            popfilegenie[isam] = new TFile(Form("../outputs/trueinfo_genie_sam%d.root",samIndex[isam]));
        }
        
        
    }

    TString subname = "finaleff_ana2x_comp3_";
    
    const int thvariable = 58;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="truepang";
    double effmax = 50;
    double rangemax = 90;
    
    /*const int thvariable = 56;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
     TString varname ="truemuang";
     double effmax = 50;
     double rangemax = 90;
    */
    
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
        ,2,1,2,2,6
        ,2,6,2
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
    TH1F* hmc[NSAMPLE][NINTERACTION];
    TH1F* hmcv5142[NSAMPLE][NINTERACTION];
    TH1F* hmcgenie[NSAMPLE][NINTERACTION];
    
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        //for mc
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmc[isam][iint] = (TH1F*)popfile[isam]->Get(Form("hmc_var%d_int%d",thvariable,iint));
            hmc[isam][iint]->Rebin(NREBINVAR[thvariable]);
            hmc[isam][iint]->GetXaxis()->SetTitle(atitle[thvariable]);
            hmc[isam][iint]->GetXaxis()->SetRangeUser(MINCUTVAR[thvariable],MAXCUTVAR[thvariable]);
            //neut 5.1.4.2
            hmcv5142[isam][iint] = (TH1F*)popfilev1542[isam]->Get(Form("hmc_var%d_int%d",thvariable,iint));
            hmcv5142[isam][iint]->Rebin(NREBINVAR[thvariable]);
            hmcv5142[isam][iint]->GetXaxis()->SetTitle(atitle[thvariable]);
            hmcv5142[isam][iint]->GetXaxis()->SetRangeUser(MINCUTVAR[thvariable],MAXCUTVAR[thvariable]);
            //genie
            hmcgenie[isam][iint] = (TH1F*)popfilegenie[isam]->Get(Form("hmc_var%d_int%d",thvariable,iint));
            hmcgenie[isam][iint]->Rebin(NREBINVAR[thvariable]);
            hmcgenie[isam][iint]->GetXaxis()->SetTitle(atitle[thvariable]);
            hmcgenie[isam][iint]->GetXaxis()->SetRangeUser(MINCUTVAR[thvariable],MAXCUTVAR[thvariable]);
            
        }
        //TString subsubname = Form("var%d",ivar);
        //plotbasicTrueInfo(hmc[ivar][1],hmc[ivar][2],hmc[ivar][3],hmc[ivar][4],hmc[ivar][5],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar]);
    }
    //efficiency of event selected
    cout<<"FOR NEUT=================>"<<endl;
    cout<<"TMVA efficiency "<<hmc[1][1]->Integral(0,hmc[1][1]->GetNbinsX()+1)*100./hmc[0][1]->Integral(0,hmc[0][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmc[2][1]->Integral(0,hmc[2][1]->GetNbinsX()+1)*100./hmc[0][1]->Integral(0,hmc[0][1]->GetNbinsX()+1)<<endl;
    
    cout<<"FOR NEUT 5.1.4.2=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcv5142[1][1]->Integral(0,hmcv5142[1][1]->GetNbinsX()+1)*100./hmcv5142[0][1]->Integral(0,hmcv5142[0][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmcv5142[2][1]->Integral(0,hmcv5142[2][1]->GetNbinsX()+1)*100./hmcv5142[0][1]->Integral(0,hmcv5142[0][1]->GetNbinsX()+1)<<endl;
    
    cout<<"FOR GENIE=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcgenie[1][1]->Integral(0,hmcgenie[1][1]->GetNbinsX()+1)*100./hmcgenie[0][1]->Integral(0,hmcgenie[0][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmcgenie[2][1]->Integral(0,hmcgenie[2][1]->GetNbinsX()+1)*100./hmcgenie[0][1]->Integral(0,hmcgenie[0][1]->GetNbinsX()+1)<<endl;
    
    //neut 5.3.2
    TH1F* hefficiency_cutmva = hmc[1][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmc[0][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmc[2][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmc[0][1]);
    hefficiency_cutnom->Scale(100.);
    
    //neut 5.1.4.2
    TH1F* hefficiencyv5142_cutmva = hmcv5142[1][1]->Clone("hefficiencyv5142_cutmva");
    hefficiencyv5142_cutmva->Divide(hmcv5142[0][1]);
    hefficiencyv5142_cutmva->Scale(100.);
    
    TH1F* hefficiencyv5142_cutnom = hmcv5142[2][1]->Clone("hefficiencyv5142_cutnom");
    hefficiencyv5142_cutnom->Divide(hmcv5142[0][1]);
    hefficiencyv5142_cutnom->Scale(100.);
    
    //genie
    TH1F* hefficiencygenie_cutmva = hmcgenie[1][1]->Clone("hefficiencygenie_cutmva");
    hefficiencygenie_cutmva->Divide(hmcgenie[0][1]);
    hefficiencygenie_cutmva->Scale(100.);
    
    TH1F* hefficiencygenie_cutnom = hmcgenie[2][1]->Clone("hefficiencygenie_cutnom");
    hefficiencygenie_cutnom->Divide(hmcgenie[0][1]);
    hefficiencygenie_cutnom->Scale(100.);
    
    
    //hefficiency_cutmva->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,effmax);
    
    hefficiency_cutnom->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutnom->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutnom->GetYaxis()->SetRangeUser(0,effmax);
    //for compare norm and mva
    //plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+varname+"comp",0.55,0.6);
    
    //for compare different generator
    plot3histStyle1(false,hefficiency_cutmva,"NEUT 5.3.2",hefficiencyv5142_cutmva,"NEUT 5.1.4.2",hefficiencygenie_cutmva,"GENIE",subname+varname+"ana1",0.55,0.6);
    
    plot3histStyle1(false,hefficiency_cutnom,"NEUT 5.3.2",hefficiencyv5142_cutnom,"NEUT 5.1.4.2",hefficiencygenie_cutnom,"GENIE",subname+varname+"nom",0.55,0.6);
    
    //plot 2d
    /*TH2F* hmcpthetatrue[NINTERACTION];
    TH2F* hmcqsqpiangletrue[NINTERACTION];
    for (Int_t iint=0; iint<NINTERACTION; ++iint) {
        hmcpthetatrue[iint] = (TH2F*)popfile->Get(Form("hmcpthetatrue_int%d", iint));
        new TCanvas;
        TString sub2d = Form("hmcpthetatrue_int%d", iint);
        hmcpthetatrue[iint]->GetXaxis()->SetTitle("#mu Momentum [GeV]");
        hmcpthetatrue[iint]->GetYaxis()->SetTitle("#mu Angle");
        hmcpthetatrue[iint]->Rebin2D(4,3);
        plot2dcolz(hmcpthetatrue[iint],subname+sub2d);
        
        hmcqsqpiangletrue[iint] = (TH2F*)popfile->Get(Form("hmcqsqpiangletrue_int%d", iint));
        new TCanvas;
        sub2d = Form("hmcqsqpiangletrue_int%d", iint);
        hmcqsqpiangletrue[iint]->GetXaxis()->SetTitle("Q^{2} [GeV^{2}]");
        hmcqsqpiangletrue[iint]->GetYaxis()->SetTitle("#pi Angle");
        hmcqsqpiangletrue[iint]->Rebin2D(4,3);
        plot2dcolz(hmcqsqpiangletrue[iint],subname+sub2d);
        
    }*/
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        popfile[isam]->Close();
        popfilev1542[isam]->Close();
        popfilegenie[isam]->Close();
    }
    
    
    
}
