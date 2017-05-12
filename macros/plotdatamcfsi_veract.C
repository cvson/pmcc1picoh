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

    TString subname = "basicdatamc_fsisel_sam4testv2_addnue";
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue.root");
    
    //modify vertex activity
    TString subname2 = "basicdatamc_fsisel_sam4testv2_addnue";
    TFile *pfile2 = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_veractMINERvA.root");
    

    //TString subname = "basicdatamc_fsiselop9_";
    //TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_opt9.root");
    
    
    
    const int NVARIABLES = 42;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    //const int NTOPOLOGY = 7;//21;//for finalcomb
    //const int NTOPOLOGY = 17;//for sam4test muon cl>0.6, pion cl>0.6, proton<0.2
    const int NTOPOLOGY = 20;//for sam4testv3, muon cl>0.6, pion cl>0.25, proton <0.05
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
    
    atitle[39] = "Discriminant parameter (COH FSI)";
    atitle[40] = "Discriminant parameter (RES FSI)";
    atitle[41] = "Discriminant parameter (CCQE FSI)";
    
    
    
    
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
        ,2,2,2,2,2,2
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
    TH1F* hmcall[NTOPOLOGY][NVARIABLES];
    TH1F* hmcen[NTOPOLOGY][NINTERACTION];
    
    TH1F* hdata2[NTOPOLOGY][NVARIABLES];
    TH1F* hmc2[NTOPOLOGY][NVARIABLES][NINTERACTION];
    TH1F* hmcall2[NTOPOLOGY][NVARIABLES];
    TH1F* hmcen2[NTOPOLOGY][NINTERACTION];
    
    double pidcut = -0.125;
    double pidcutlong = 0.1;
    double veractcut = 475*7.6634e-2;
    double veractcutlong = 5;
    float npot = 6.04193507503274721e20;
    int   nmc  = 3950;
    //int   nmc  = 3974;//for newneut
    float mcpotreweight = npot/(nmc*1e21);
    
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            TString subsubname = Form("topo%d_var%d",itopo,ivar);
            hdata[itopo][ivar] = (TH1F*)pfile->Get(Form("hdata_topo%d_var%d",itopo,ivar));
            hdata[itopo][ivar]->Rebin(NREBINVAR[ivar]);
            //hdata[itopo][ivar]->GetXaxis()->SetRangeUser(MINCUTVAR[ivar],MAXCUTVAR[ivar]);
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmc[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
                
                hmc2[itopo][ivar][iint] = (TH1F*)pfile2->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmc2[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
            }
            
            //addnue to nubar for plot
            hmc[itopo][ivar][6]->Add(hmc[itopo][ivar][7]);//newadd
            hmc2[itopo][ivar][6]->Add(hmc2[itopo][ivar][7]);//newadd
            
            hmcall[itopo][ivar] = (TH1F*)hmc[itopo][ivar][1]->Clone(Form("hmc_topo%d_var%d_all",itopo,ivar));
            hmcall2[itopo][ivar] = (TH1F*)hmc2[itopo][ivar][1]->Clone(Form("hmc2_topo%d_var%d_all",itopo,ivar));
            for (Int_t iint=2; iint<NINTERACTION; ++iint) {
                if(iint!=7) {
                    hmcall[itopo][ivar]->Add(hmc[itopo][ivar][iint]);
                    hmcall2[itopo][ivar]->Add(hmc2[itopo][ivar][iint]);
                }
            }
            hmcall[itopo][ivar]->Scale(mcpotreweight);
            hmcall2[itopo][ivar]->Scale(mcpotreweight);
            
            hdata[itopo][ivar]->SetLineWidth(3);
            hmcall[itopo][ivar]->SetLineWidth(3);
            hmcall2[itopo][ivar]->SetLineWidth(3);
            //sig 3, cr1 4, cr2 11, cr3 14 --> with 21 topo
            //all 0, pre 1, pre + pid 2, sig 3, cr1 4, cr2 5, cr3 6
            //7 for anti-pid, 8 1mu + all, 9+no side-escape, 10 + stopped
            //11 mu+pi all, 12 +side-escape, 13 +mu+pi stopped
            //14 mu+p all, 15 +side-escape, 16 +mu+pi stopped
           //17 p all, 18 19
            /*if(itopo==10 && !((ivar>7 && ivar<16)||(ivar>20 && ivar<24))){
                if (ivar==17 || ivar==18){
                    plotcc1pedatavsmcwpionwzoom(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                }
                //else if (ivar==33) plotcc1pedatavsmcwpionwcut(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],pidcut, pidcutlong,XLEGSHIFT[ivar],YLEGSHIFT[ivar],false);
                //else if (ivar==36) plotcc1pedatavsmcwpionwcut(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],veractcut,veractcutlong,XLEGSHIFT[ivar],YLEGSHIFT[ivar],false);
                else if (ivar==33) plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                else if (ivar==36) plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname+"_nocut",MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
                else plotcc1pedatavsmcwpion(hdata[itopo][ivar],hmc[itopo][ivar][1],hmc[itopo][ivar][2],hmc[itopo][ivar][3],hmc[itopo][ivar][4],hmc[itopo][ivar][5],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],TString(atitle[ivar]),subname+subsubname,MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar],true);
                
            }*/
            
        }//end ivar
        //energy plots
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcen[itopo][iint] = (TH1F*)pfile->Get(Form("hmcen_topo%d_int%d",itopo,iint));
        }
    }//end itopo
    
    Int_t ci;
    ci = TColor::GetColor("#D55E00");
    
    Int_t cidata;
    cidata = TColor::GetColor("#000000");
    
    Int_t cimod;
    cimod = TColor::GetColor("#0072B2");
    
    new TCanvas;
    hdata[9][36]->SetMarkerColor(cidata);
    hdata[9][36]->SetLineColor(cidata);
    hdata[9][36]->GetXaxis()->SetTitle(atitle[36]);
    hdata[9][36]->GetYaxis()->SetTitle("Number of events");
    double maxy = 1.2*TMath::Max(hdata[9][36]->GetMaximum(),TMath::Max(hmcall[9][36]->GetMaximum(), hmcall2[9][36]->GetMaximum()));
    hdata[9][36]->GetYaxis()->SetRangeUser(0, maxy);
    titleStyle(hdata[9][36]);
    hdata[9][36]->Draw("ep");
    
    hmcall[9][36]->SetLineColor(ci);
    hmcall[9][36]->Draw("histsame");
    
    hmcall2[9][36]->SetLineColor(cimod);
    //hmcall2[9][36]->SetLineStyle(7);
    hmcall2[9][36]->Draw("histsame");
    gPad->Print("plots/veract_comp_datmc_MINERvAeffect_1mu.eps");
    
    new TCanvas;
    hdata[12][36]->SetMarkerColor(cidata);
    hdata[12][36]->SetLineColor(cidata);
    hdata[12][36]->GetXaxis()->SetTitle(atitle[36]);
    hdata[12][36]->GetYaxis()->SetTitle("Number of events");
    titleStyle(hdata[12][36]);
    maxy = 1.2*TMath::Max(hdata[12][36]->GetMaximum(),TMath::Max(hmcall[12][36]->GetMaximum(), hmcall2[12][36]->GetMaximum()));
    hdata[12][36]->GetYaxis()->SetRangeUser(0, maxy);
    
    hdata[12][36]->Draw("ep");
    
    hmcall[12][36]->SetLineColor(ci);
    hmcall[12][36]->Draw("histsame");
    
    hmcall2[12][36]->SetLineColor(cimod);
    //hmcall2[12][36]->SetLineStyle(7);
    hmcall2[12][36]->Draw("histsame");
    gPad->Print("plots/veract_comp_datmc_MINERvAeffect_1mu1pi.eps");
    
    
    new TCanvas;
    hdata[15][36]->SetMarkerColor(cidata);
    hdata[15][36]->SetLineColor(cidata);
    hdata[15][36]->GetXaxis()->SetTitle(atitle[36]);
    hdata[15][36]->GetYaxis()->SetTitle("Number of events");
    titleStyle(hdata[15][36]);
    maxy = 1.2*TMath::Max(hdata[15][36]->GetMaximum(),TMath::Max(hmcall[15][36]->GetMaximum(), hmcall2[15][36]->GetMaximum()));
    hdata[15][36]->GetYaxis()->SetRangeUser(0, maxy);
    
    hdata[15][36]->Draw("ep");
    
    hmcall[15][36]->SetLineColor(ci);
    hmcall[15][36]->Draw("histsame");
    
    hmcall2[15][36]->SetLineColor(cimod);
    //hmcall2[15][36]->SetLineStyle(7);
    hmcall2[15][36]->Draw("histsame");
    gPad->Print("plots/veract_comp_datmc_MINERvAeffect_1mu1pro.eps");
    
    /*new TCanvas;
    hdata[9][36]->SetMarkerColor(ci);
    hdata[9][36]->SetLineColor(ci);
    hdata[9][36]->GetXaxis()->SetTitle(atitle[36]);
    hdata[9][36]->GetYaxis()->SetTitle("Number of events");
    titleStyle(hdata[9][36]);
    hdata[9][36]->Draw("ep");
    
    hmcall[9][36]->SetLineColor(ci);
    hmcall[9][36]->Draw("histsame");
    
    ci = TColor::GetColor("#0072B2");
    hdata[12][36]->SetMarkerColor(ci);
    hdata[12][36]->SetLineColor(ci);
    hdata[12][36]->Draw("ep same");
    hmcall[12][36]->SetLineColor(ci);
    hmcall[12][36]->Draw("histsame");
    
    ci = TColor::GetColor("#000000");
    hdata[15][36]->SetMarkerColor(ci);
    hdata[15][36]->SetLineColor(ci);
    hdata[15][36]->Draw("ep same");
    hmcall[15][36]->SetLineColor(ci);
    hmcall[15][36]->Draw("histsame");
    
    TLegend* leg0 = new TLegend(.42, .58, 0.8, .82);
    //leg0->SetMargin(0.1);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(18);
    leg0->SetTextFont(43);
    leg0->AddEntry(hmcall[9][36], "1#mu sample", "l");
    leg0->AddEntry(hmcall[12][36], "1#mu + 1#pi sample", "l");
    leg0->AddEntry(hmcall[15][36], "1#mu + 1p sample", "l");
    leg0->SetFillStyle(0);
    leg0->Draw();
    
    
    gPad->Print("plots/veract_comp_datmc_shape.eps");*/
    
    
    
    
   
    
    
}
