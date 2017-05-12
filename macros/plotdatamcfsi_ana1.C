{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    //TString subname = "basicdatamc_fsisel_finalcomb_genie";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_genie.root");
    
    //TString subname = "basicdatamc_fsisel_finalcomb";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb.root");
    
   // TString subname = "basicdatamc_fsisel_sam4test";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4test.root");
    
    //TString subname = "basicdatamc_fsisel_sam4testv2";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2.root");

    //TString subname = "basicdatamc_fsisel_sam4testv2_addnue";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue.root");

    //TString subname = "basicdatamc_genie_fsisel_sam4testv2_addnue";
    //TFile *pfile = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue.root");
    
    TString subname = "basicdatamc_ana1_sam4testv2_addnue";
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_ana1.root");
    
    //TString subname = "basicdatamc_fsiselop9_";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_opt9.root");
    
    
    
    const int NVARIABLES = 42;//all variables//update to convert vertex activity
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
    
    
    
    
    Double_t MINVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1,-1,-1,0,0,0
        ,-1,-1,-1};
    Double_t MAXVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,1,1,1,400,1,5
        ,1,1,1};
    
    //more 2 track
    Double_t NBINVAR[NVARIABLES] =   {10,10,90,180,200,200
        ,180,180,200,50,60,100
        ,2,2,500,500,500,100
        ,100,90,90,120,120,100
        ,120,120,120,16,16,100
        ,11,100,11,200,200,200,200,100,100
        , 200,200,200};
    Double_t NREBINVAR[NVARIABLES] =   {2,2,2,4,4,4
        ,2,2,2,2,2,4
        ,1,1,5,5,5,2
        ,2,2,2,2,2,2
        ,2,2,2,1,1,2
        ,1,2,1,2,2,2,4,2,2
        ,2,2,2};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,0,0,0
        ,0,0,0,-60,-60,-160
        ,-540,0,0,0,0,0
        ,0,0,11,-1.0,-0.5,-0.7,0,0,0
        ,-1,-1,-1};
    Double_t MAXCUTVAR[NVARIABLES] =   {0,10,90,180,500,250
        ,180,180,500,20,60,10
        ,2,2,2500,2500,5000,1
        ,1,90,90,60,60,-60
        ,-480,1200,1200,16,16,100
        ,11,100,11,0.2,0.5,0.2,400,1,5
        ,0.5,0.5,0.5};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.05,-0.2,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.1
        ,0.0,0.0,-0.35,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,-0.3
        ,0.0,0.0,0.0,-0.3,0.07,-0.3, 0.0,0.0,0.0,-0.3,-0.3,-0.3};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.05,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0
        ,0.0,0.0,0.0,0.0,0.0,0.0, 0.0,0.0,0.0,0,0,0};
    
    TH1F* hdata[NTOPOLOGY][NVARIABLES];
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
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
            }
            //addnue to nubar for plot
            hmc[itopo][ivar][6]->Add(hmc[itopo][ivar][7]);//newadd
            //sig 3, cr1 4, cr2 11, cr3 14 --> with 21 topo
            //all 0, pre 1, pre + pid 2, sig 3, cr1 4, cr2 5, cr3 6
            //7 for anti-pid, 8 1mu + all, 9+no side-escape, 10 + stopped
            //11 mu+pi all, 12 +side-escape, 13 +mu+pi stopped
            //14 mu+p all, 15 +side-escape, 16 +mu+pi stopped
           //17 p all, 18 19
           //23,24,25 CCQE 2 track
            if(itopo==18 && !((ivar>7 && ivar<16)||(ivar>20 && ivar<24) )){
                if (ivar==17 || ivar==18){
                    plotcc1pedatavsmcwpionwzoom(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                }
                //else if (ivar==39) plotcc1pedatavsmcwpionwcut(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],pidcut, pidcutlong,XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                //else if (ivar==36) plotcc1pedatavsmcwpionwcut(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],veractcut,veractcutlong,XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                else if (ivar==39) plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                else if (ivar==36) plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
                else plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
            }
        }//end ivar
        //energy plots
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcen[itopo][iint] = (TH1F*)pfile->Get(Form("hmcen_topo%d_int%d",itopo,iint));
        }
    }//end itopo
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
    
    //plotCompositionwpion(hmc[26][11][1],hmc[26][11][2],hmc[26][11][3],hmc[26][11][4],hmc[26][11][5],hmc[26][11][6],hmc[26][11][8],hmc[26][11][9],subname+"nuE_comp_2trk_nom");
    
    
    
    //efficiency & purity
    //purity
    /*cout<<"TMVA purity "<<hmc[3][11][1]->Integral(0,hmc[3][11][1]->GetNbinsX()+1)*100./(hmc[3][11][0]->Integral(0,hmc[3][11][0]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmc[26][11][1]->Integral(0,hmc[26][11][1]->GetNbinsX()+1)*100./hmc[26][11][0]->Integral(0,hmc[26][11][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmc[3][11][1]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmc[3][11][0]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmc[26][11][1]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmc[26][11][0]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,6);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_purity",0.5,0.65);
    
    //efficiency
    cout<<"TMVA efficiency "<<hmc[3][11][1]->Integral(0,hmc[3][11][1]->GetNbinsX()+1)*100./hmc[1][11][1]->Integral(0,hmc[1][11][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmc[26][11][1]->Integral(0,hmc[26][11][1]->GetNbinsX()+1)*100./hmc[1][11][1]->Integral(0,hmc[1][11][1]->GetNbinsX()+1)<<endl;
    
    TH1F* hefficiency_cutmva = hmc[3][11][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmc[1][11][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmc[26][11][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmc[1][11][1]);
    hefficiency_cutnom->Scale(100.);
    
    hefficiency_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,6);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"comp_efficiency",0.2,0.65);*/
    
    
    /*cout<<"TMVA purity "<<hmc[3][19][1]->Integral(0,hmc[3][19][1]->GetNbinsX()+1)*100./(hmc[3][19][0]->Integral(0,hmc[3][19][0]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmc[26][19][1]->Integral(0,hmc[26][19][1]->GetNbinsX()+1)*100./hmc[26][19][0]->Integral(0,hmc[26][19][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmc[3][19][1]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmc[3][19][0]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmc[26][19][1]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmc[26][19][0]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle("#mu-like track angle");
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,50);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_muang_purity",0.2,0.65);
    
    //efficiency
    cout<<"TMVA efficiency "<<hmc[3][19][1]->Integral(0,hmc[3][19][1]->GetNbinsX()+1)*100./hmc[1][19][1]->Integral(0,hmc[1][19][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmc[26][19][1]->Integral(0,hmc[26][19][1]->GetNbinsX()+1)*100./hmc[1][19][1]->Integral(0,hmc[1][19][1]->GetNbinsX()+1)<<endl;
    
    TH1F* hefficiency_cutmva = hmc[3][19][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmc[1][19][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmc[26][19][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmc[1][19][1]);
    hefficiency_cutnom->Scale(100.);
    
    hefficiency_cutmva->GetXaxis()->SetTitle("#mu-like track angle");
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,50);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"comp_muang_efficiency",0.2,0.65);*/
    
    /*cout<<"TMVA purity "<<hmc[3][20][1]->Integral(0,hmc[3][20][1]->GetNbinsX()+1)*100./(hmc[3][20][0]->Integral(0,hmc[3][20][0]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmc[26][20][1]->Integral(0,hmc[26][20][1]->GetNbinsX()+1)*100./hmc[26][20][0]->Integral(0,hmc[26][20][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmc[3][20][1]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmc[3][20][0]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmc[26][20][1]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmc[26][20][0]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle("#pi-like track angle");
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,90);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_pang_purity",0.5,0.65);
    
    //efficiency
    cout<<"TMVA efficiency "<<hmc[3][20][1]->Integral(0,hmc[3][20][1]->GetNbinsX()+1)*100./hmc[1][20][1]->Integral(0,hmc[1][20][1]->GetNbinsX()+1)<<endl;
    cout<<"NOM efficiency "<<hmc[26][20][1]->Integral(0,hmc[26][20][1]->GetNbinsX()+1)*100./hmc[1][20][1]->Integral(0,hmc[1][20][1]->GetNbinsX()+1)<<endl;
    
    TH1F* hefficiency_cutmva = hmc[3][20][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmc[1][20][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmc[26][20][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmc[1][20][1]);
    hefficiency_cutnom->Scale(100.);
    
    hefficiency_cutmva->GetXaxis()->SetTitle("#pi-like track angle");
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,90);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+"comp_pang_efficiency",0.2,0.65);*/
    
}
