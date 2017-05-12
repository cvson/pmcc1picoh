{
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
    
    TString strtopo = "noside";
    //TString subname = "basicdatamc_official_";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamc.root");//21 topology
    //const int NTOPOLOGY = 21;
    
    //TString subname = "basicdatamc_official_correctm2trk_";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_oldsel_correctm2trk.root");//shot for 7 topology
    TString subname = "basicdatamc_official_correctm2trk_optimizem2trk";
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_oldsel_correctm2trk_optimized.root");//shot for 7 topology
    const int NTOPOLOGY = 7;//0 all; 1 prel; 2 prel + pid; 3 sig ; 4 cr1; 5 cr2; 6 cr3
    const int NVARIABLES = 39;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    
    
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    
    char* atitle[NVARIABLES];
    atitle[0] = "Number of tracks";
    atitle[1] = "Number of INGRID-penetrated track";
    atitle[2] = "#mu-like track angle";
    atitle[3] = "#pi-like track angle";
    atitle[4] = "Mean of #pi-like light yield";
    atitle[5] = "Mean of #mu-like light yield";
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
    //atitle[19] = "#mu-like track angle";
    //atitle[20] = "#pi-like track angle";
    //5/6
    atitle[19] = "First track angle";
    atitle[20] = "Second track angle";
    atitle[21] = "xnu";
    atitle[22] = "ynu";
    atitle[23] = "znu";
    atitle[24] = "exptime";
    atitle[25] = "startxch";
    atitle[26] = "startych";
    atitle[27] = "startxpln";
    atitle[28] = "startypln";
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
    
    
    
    
    Double_t MINVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1,-1,-1,0,0,0};
    Double_t MAXVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,1,1,1,400,1,5};
    
    //all
    /*Double_t NREBINVAR[NVARIABLES] =   {2,2,2,4,4,4
        ,2,2,2,2,2,2
        ,1,1,5,5,5,2
        ,2,2,2,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,2};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1.0,-0.5,-0.5,0};
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.5,0.6,400};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.05,-0.2,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.1
        ,0.0,0.0,-0.35,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.3
        ,0.0,0.0,0.0,-0.3,0.07,0.07, 0.0};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.05,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0};
     */
    //cr1
    /*Double_t NREBINVAR[NVARIABLES] =   {2,2,2,4,8,8
        ,10,10,2,2,2,2
        ,1,1,5,5,10,4
        ,4,2,5,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,4};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-0.4,-0.5,-0.5,0};
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,40,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.5,0.6,400};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.05,-0.2,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.1
        ,0.0,0.0,0.1,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.3
        ,0.0,0.0,0.0,-0.3,0.07,0.07, 0.0};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0};*/
    
    //cr2a
    /*
    Double_t NREBINVAR[NVARIABLES] =   {2,2,2,4,4,4
        ,2,2,2,2,2,2
        ,1,1,5,5,5,2
        ,2,2,2,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,2};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1.0,-0.5,-0.4,0};
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.0,0.5,0.2,400};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.05,-0.2,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.1
        ,0.0,0.0,-0.35,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.3
        ,0.0,0.0,0.0,-0.3,0.07,-0.33, 0.0};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.05,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0};*/
    //cr2b
    /*Double_t NREBINVAR[NVARIABLES] =   {2,2,2,4,8,8
        ,10,10,2,2,2,2
        ,1,1,5,5,10,4
        ,4,2,5,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,4};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1.0,-0.5,-0.5,0};
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.0,0.5,0.1,80};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.05,-0.2,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.1
        ,0.0,0.0,0.1,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.3
        ,0.0,0.0,0.0,-0.3,0.07,-0.3, 0.05};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0};*/
    
    //cr2c
    
    /*Double_t NREBINVAR[NVARIABLES] =   {2,2,2,4,4,4
        ,2,2,2,2,2,2
        ,1,1,5,5,5,2
        ,2,2,2,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,4};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1.0,-0.5,-0.5,0};
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.0,0.5,0.1,400};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.05,-0.2,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.1
        ,0.0,0.0,0.05,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.3
        ,0.0,0.0,0.0,-0.3,0.07,-0.3, 0.0};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0};*/
    //more 2 track
    Double_t NBINVAR[NVARIABLES] =   {10,10,90,180,200,200
        ,180,180,200,50,60,100
        ,2,2,500,500,500,100
        ,100,90,90,120,120,100
        ,120,120,120,16,16,100
        ,11,100,11,200,200,200,200,100,100};
    Double_t NREBINVAR[NVARIABLES] =   {2,2,2,4,4,4
        ,2,2,2,2,2,2
        ,1,1,5,5,5,2
        ,2,2,2,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,4,2,2};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1.0,-0.5,-0.7,0,0,0};
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.5,0.2,400,1,5};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.05,-0.2,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.1
        ,0.0,0.0,-0.35,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.3
        ,0.0,0.0,0.0,-0.3,0.07,-0.3, 0.0,0.0,0.0};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.05,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0,0.0,0.0};
    
    TH1F* hdata[NTOPOLOGY][NVARIABLES];
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    TH1F* hmcen[NTOPOLOGY][NINTERACTION];
    double pidcut = -0.125;
    double pidcutlong = 0.1;
    double veractcut = 475*7.6634e-2;
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
            }
            //sig 3, cr1 4, cr2 11, cr3 14
            if(itopo==6 && !((ivar>7 && ivar<16)||(ivar>20 && ivar<24) || (ivar>29 && ivar<33))){
                if (ivar==17 || ivar==18){
                    plotcc1pedatavsmcwpionwzoom(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                }
                //else if (ivar==33) plotcc1pedatavsmcwpionwcut(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],pidcut, pidcutlong,XLEGSHIFT[ivar],YLEGSHIFT[ivar],false);
                //else if (ivar==36) plotcc1pedatavsmcwpionwcut(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],veractcut,veractcutlong,XLEGSHIFT[ivar],YLEGSHIFT[ivar],false);
                else if (ivar==33) plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                else if (ivar==36) plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
                else plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
            }
        }//end ivar
        //energy plots
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcen[itopo][iint] = (TH1F*)pfile->Get(Form("hmcen_topo%d_int%d",itopo,iint));
        }
    }//end itopo
    
    //energy composition
   /*plotCompositionwpion(hmcen[3][1],hmcen[3][2],hmcen[3][3],hmcen[3][4],hmcen[3][5],hmcen[3][6],hmcen[3][8],hmcen[3][9],subname+"nuE_comp_2trk_cutmva");
    plotCompositionwpion(hmcen[10][1],hmcen[10][2],hmcen[10][3],hmcen[10][4],hmcen[10][5],hmcen[10][6],hmcen[10][8],hmcen[10][9],subname+"nuE_comp_2trk_cutnom");
    
    plotCompositionwpion(hmcen[1][1],hmcen[1][2],hmcen[1][3],hmcen[1][4],hmcen[1][5],hmcen[1][6],hmcen[1][8],hmcen[1][9],subname+"nuE_comp_2trk");
    
    //efficiency & purity
    //purity
    cout<<"TMVA purity "<<hmcen[3][1]->Integral(0,hmcen[3][1]->GetNbinsX()+1)*100./(hmcen[3][0]->Integral(0,hmcen[3][0]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmcen[10][1]->Integral(0,hmcen[10][1]->GetNbinsX()+1)*100./hmcen[10][0]->Integral(0,hmcen[10][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmcen[3][1]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmcen[3][0]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmcen[10][1]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmcen[10][0]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,10);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_purity",0.5,0.65);
    
    //efficiency
    cout<<"TMVA efficiency "<<hmcen[3][1]->Integral(0,hmcen[3][1]->GetNbinsX()+1)*100./hmcen[1][1]->Integral(0,hmcen[1][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmcen[10][1]->Integral(0,hmcen[10][1]->GetNbinsX()+1)*100./hmcen[1][1]->Integral(0,hmcen[1][1]->GetNbinsX()+1)<<endl;
    
    TH1F* hefficiency_cutmva = hmcen[3][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmcen[1][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmcen[10][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmcen[1][1]);
    hefficiency_cutnom->Scale(100.);
    
    hefficiency_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,10);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"comp_efficiency",0.2,0.75);*/
    
    
}