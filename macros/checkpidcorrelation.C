{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    


    TString subname = "pidcorrelation";
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_35samv0.root");

    //TString subname = "basicdatamc_fsiselop9_";

    
    
    
    const int NVARIABLES = 47;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    //const int NTOPOLOGY = 7;//21;//for finalcomb
    //const int NTOPOLOGY = 17;//for sam4test muon cl>0.6, pion cl>0.6, proton<0.2
    const int NTOPOLOGY = 35;//for sam4testv3, muon cl>0.6, pion cl>0.25, proton <0.05
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
    atitle[27] = "pidres";
    atitle[28] = "pidccqe";
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
    
    
    
    
    
    //newadd 2-dim
    TH2F* hdtpidvsQsq[NTOPOLOGY];
    TH2F* hdtpidvsVeract[NTOPOLOGY];
    
    TH2F* hmcpidvsQsq[NTOPOLOGY][NINTERACTION];
    TH2F* hmcpidvsVeract[NTOPOLOGY][NINTERACTION];
    
    TH2F* hsubpidvsQsq[NTOPOLOGY];
    TH2F* hsubpidvsVeract[NTOPOLOGY];
     
    TH2F* hdtpidvspidres[NTOPOLOGY];
    TH2F* hdtpidvspidccqe[NTOPOLOGY];
    
    TH2F* hmcpidvspidres[NTOPOLOGY][NINTERACTION];
    TH2F* hmcpidvspidccqe[NTOPOLOGY][NINTERACTION];
    
    TH2F* hsubpidvspidres[NTOPOLOGY];
    TH2F* hsubpidvspidccqe[NTOPOLOGY];
    
    double pidcut = -0.125;
    double pidcutlong = 0.1;
    double veractcut = 475*7.6634e-2;
    double veractcutlong = 5;
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
    
        hdtpidvsQsq[itopo] = (TH2F*)pfile->Get(Form("hdtpidvsQsq_topo%d",itopo));
        hdtpidvsVeract[itopo] = (TH2F*)pfile->Get(Form("hdtpidvsVeract_topo%d",itopo));
        hdtpidvspidres[itopo] = (TH2F*)pfile->Get(Form("hdtpidvspidres_topo%d",itopo));
        hdtpidvspidccqe[itopo] = (TH2F*)pfile->Get(Form("hdtpidvspidccqe_topo%d",itopo));
        
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcpidvsQsq[itopo][iint] = (TH2F*)pfile->Get(Form("hmcpidvsQsq_topo%d_int%d",itopo,iint));
            hmcpidvsVeract[itopo][iint] = (TH2F*)pfile->Get(Form("hmcpidvsVeract_topo%d_int%d",itopo,iint));
            hmcpidvspidres[itopo][iint] = (TH2F*)pfile->Get(Form("hmcpidvspidres_topo%d_int%d",itopo,iint));
            hmcpidvspidccqe[itopo][iint] = (TH2F*)pfile->Get(Form("hmcpidvspidccqe_topo%d_int%d",itopo,iint));
        }
        
        new TCanvas;
        
    
    }//end itopo
    Int_t ci = TColor::GetColor("#000000");
    Int_t cimc = TColor::GetColor("#D55E00");
    //plot
    for (Int_t itopo=19; itopo<22; ++itopo) {
        
        hmcpidvsQsq[itopo][0]->Rebin2D(2,2);
        hmcpidvsVeract[itopo][0]->Rebin2D(2,2);
        
        //mc veract vs Qsq
        new TCanvas;
        hmcpidvsQsq[itopo][0]->GetXaxis()->SetTitle("Reconstructed Q^{2}");
        hmcpidvsQsq[itopo][0]->GetXaxis()->SetRangeUser(0,0.15);
        hmcpidvsQsq[itopo][0]->GetYaxis()->SetTitle("Discriminant parameter (COH)");
        hmcpidvsQsq[itopo][0]->GetYaxis()->SetRangeUser(-0.7,0.5);
        plot2dhist(hmcpidvsQsq[itopo][0],subname+Form("_mc_vsQsq_sam%d",itopo));
        
        //mc veract vs Veract
        new TCanvas;
        hmcpidvsVeract[itopo][0]->GetXaxis()->SetTitle("Energy deposit at vertex (MeV)");
        hmcpidvsVeract[itopo][0]->GetXaxis()->SetRangeUser(0,50);
        hmcpidvsVeract[itopo][0]->GetYaxis()->SetTitle("Discriminant parameter (COH)");
        hmcpidvsVeract[itopo][0]->GetYaxis()->SetRangeUser(-0.7,0.5);
        plot2dhist(hmcpidvsVeract[itopo][0],subname+Form("_mc_vsVeract_sam%d",itopo));
        
        
        
 
    }
    
    
}
