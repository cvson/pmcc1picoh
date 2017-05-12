{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    
    
    //TFile *pfile = new TFile("../outputs/checkFSI_fsisel_finalcomb.root");
    //TString subname="fsisel_finalcomb";
    
    TFile *pfile = new TFile("../outputs/checkFSI_fsisel_finalcomb_addnue.root");
    TString subname="fsisel_finalcomb_addnue";
    
    //TFile *pfile = new TFile("../outputs/checkFSI_fsisel_final.root");
    //TString subname="fsisel_final";
    
    
    
    //all variables//update to convert vertex activity
    //pid, pidres, pidccqe
    //pidfsi, pidfsires, pidfsiccqe
    const int NVARIABLES = 13;
    //0 prel, 1 pid, 2 sig, 3 cr1, 4 cr2, 5 cr3, 6 cccoh only
    const int NTOPOLOGY = 7;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 14;
    
    char* atitle[NVARIABLES];
    atitle[0] = "#mu-like track angle";
    atitle[1] = "#pi-like track angle";
    atitle[2] = "#mu-like track confidence level";
    atitle[3] = "#pi-like track confidence level";
    atitle[4] = "Reconstructed momentum (GeV))";
    atitle[5] = "Discriminant paras. (COH)";
    atitle[6] = "Discriminant paras. (RES)";
    atitle[7] = "Discriminant paras. (CCQE)";
    atitle[8] = "Discriminant paras. (COH)";
    atitle[9] = "Discriminant paras. (RES)";
    atitle[10] = "Discriminant paras. (CCQE)";
    atitle[11] = "Vertex activity";
    atitle[12] = "Energy deposit at vertex (MeV)";
    
    
    
    Double_t MINVAR[NVARIABLES] =    {0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0};
    Double_t MAXVAR[NVARIABLES] =   {90,90,1,1,1.5,1,1,1,1,1,1,500,200};
    
    Double_t NBINVAR[NVARIABLES] =   {90,90,100,100,150,200,200,200,200,200,200,200,200};
    
    Double_t NREBINVAR[NVARIABLES] =   {1,1,1,1,1,1,1,1,1,1,1,1,1};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,-1,-1,-1,-1,-1,-1,0,0};
    Double_t MAXCUTVAR[NVARIABLES] =   {90,90,1,1,1.5,1,1,1,1,1,1,500,200};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0,0,0,0,0,0,0,0};
    
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    TH2F* hveractvsmuang[NTOPOLOGY][NINTERACTION];
    TH2F* hveractvspang[NTOPOLOGY][NINTERACTION];
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmc[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
            }
            if(ivar==0 || ivar == 2 || ivar==5 || ivar==6 || ivar==7 || ivar==8 || ivar==9 || ivar==10 || ivar==12) plotfsimuon(hmc[itopo][ivar][0],hmc[itopo][ivar][2],hmc[itopo][ivar][1],hmc[itopo][ivar][3],hmc[itopo][ivar][4],Form("%s",atitle[ivar]),subname+Form("checkfsi_muid_topo%d_var%d",itopo,ivar),MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar]);
            
            if(ivar==1 || ivar == 3 || ivar==5 || ivar==6 || ivar==7 || ivar==8 || ivar==9 || ivar==10 || ivar==12) plotfsimuon(hmc[itopo][ivar][5],hmc[itopo][ivar][7],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],Form("%s",atitle[ivar]),subname+Form("checkfsi_piid_topo%d_var%d",itopo,ivar),MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar]);
        }//end ivar
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hveractvsmuang[itopo][iint] = (TH2F*)pfile->Get(Form("hveractvsmuang_topo%d_int%d",itopo,iint));
            hveractvspang[itopo][iint] = (TH2F*)pfile->Get(Form("hveractvspang_topo%d_int%d",itopo,iint));
        }
        
    }//end itopo
    
    //new TCanvas;
    hveractvsmuang[6][10]->GetXaxis()->SetTitle("#mu-like track angle");
    hveractvsmuang[6][10]->GetXaxis()->SetRangeUser(0,60);
    hveractvsmuang[6][10]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    hveractvsmuang[6][10]->GetYaxis()->SetRangeUser(0,100);
    plot2dhist(hveractvsmuang[6][10],"veractvsmuang_cccoh");
    
    hveractvspang[6][10]->GetXaxis()->SetTitle("#pi-like track angle");
    hveractvspang[6][10]->GetXaxis()->SetRangeUser(0,90);
    hveractvspang[6][10]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
    hveractvspang[6][10]->GetYaxis()->SetRangeUser(0,100);
    plot2dhist(hveractvspang[6][10],"veractvspang_cccoh");
    
    
    
}