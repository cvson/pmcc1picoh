{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    TFile *pfile = new TFile("../outputs/checkFSI_fsiselopt8.root");
    TString subname="optimizeTrueID_";
    
    const int NVARIABLES = 11;
    //0 prel, 1 pid, 2 sig, 3 cr1, 4 cr2, 5 cr3, 6 cccoh only
    const int NTOPOLOGY = 8;
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
    atitle[8] = "Discriminant paras. (COH + FSI)";
    atitle[9] = "Discriminant paras. (RES + FSI)";
    atitle[10] = "Discriminant paras. (CCQE + FSI)";
    
    
    
    
    Double_t MINVAR[NVARIABLES] =    {0,0,0,0,0,-1,-1,-1,-1,-1,-1};
    Double_t MAXVAR[NVARIABLES] =   {90,90,1,1,1.5,1,1,1,1,1,1};
    
    Double_t NBINVAR[NVARIABLES] =   {90,90,100,100,150,200,200,200,200,200,200};
    
    Double_t NREBINVAR[NVARIABLES] =   {1,1,1,1,1,1,1,1,1,1,1};
    
    Double_t MINCUTVAR[NVARIABLES] =    {0,0,0,0,0,-1,-1,-1,-1,-1,-1};
    Double_t MAXCUTVAR[NVARIABLES] =   {90,90,1,1,1.5,1,1,1,1,1,1};
    
    Double_t XLEGSHIFT[NVARIABLES] =    {0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2,0.2};
    Double_t YLEGSHIFT[NVARIABLES] =    {0.0,0.0,0.0,0.0,0.0,0,0,0,0,0,0};
    
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    
    
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",itopo,ivar,iint));
                hmc[itopo][ivar][iint]->Rebin(NREBINVAR[ivar]);
            }
            //if(ivar==0 || ivar == 2 || ivar==5 || ivar==6 || ivar==7 || ivar==8 || ivar==9 || ivar==10) plotfsimuon(hmc[itopo][ivar][0],hmc[itopo][ivar][2],hmc[itopo][ivar][1],hmc[itopo][ivar][3],hmc[itopo][ivar][4],Form("%s",atitle[ivar]),subname+Form("checkfsi_muid_topo%d_var%d",itopo,ivar),MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar]);
            
            //if(ivar==1 || ivar == 3 || ivar==5 || ivar==6 || ivar==7 || ivar==8 || ivar==9 || ivar==10 ) plotfsimuon(hmc[itopo][ivar][5],hmc[itopo][ivar][7],hmc[itopo][ivar][6],hmc[itopo][ivar][8],hmc[itopo][ivar][9],Form("%s",atitle[ivar]),subname+Form("checkfsi_piid_topo%d_var%d",itopo,ivar),MINCUTVAR[ivar],MAXCUTVAR[ivar],XLEGSHIFT[ivar],YLEGSHIFT[ivar]);
        }//end ivar
    }//end itopo
    
    //optimize for cr1
    //0 for muon, 7 for pion
    Int_t sampleth = 6;
    Int_t varth = 9;
    //sum of background
    TH1F* h1strmuon = (TH1F*)hmc[sampleth][varth][0]->Clone("h1strmuon");
    TH1F* h1strnonmuon = (TH1F*)hmc[sampleth][varth][1]->Clone("h1strnonmuon");
    for (Int_t iint=2; iint<5; ++iint) {
        h1strnonmuon->Add(hmc[sampleth][varth][iint]);
    }
    
    TH1F* h2ndpion = (TH1F*)hmc[sampleth][varth][7]->Clone("h2ndpion");
    TH1F* h2ndnonpion = (TH1F*)hmc[sampleth][varth][5]->Clone("h2ndnonpion");
    for (Int_t iint=6; iint<10; ++iint) {
        if (iint!=7) h2ndnonpion->Add(hmc[sampleth][varth][iint]);
    }
    
    
    //optimization
    TH1* hoptimize = (TH1F*)h1strmuon->Clone("hoptimize");
    TH1* hoptimize2 = (TH1F*)h2ndpion->Clone("hoptimize2");
    TH1* hefficiency = (TH1F*)h2ndpion->Clone("hefficiency");
    
    Int_t nx = hoptimize -> GetNbinsX()+1;
    Double_t xcutatMax;
    Double_t n1stmuonTot = h1strmuon->Integral(0,nx+1);
    Double_t n1stnonmuonTot = h1strnonmuon->Integral(0,nx+1);
    cout<<"1st track muon "<<n1stmuonTot<<" nonmuon "<<n1stnonmuonTot<<" purity "<<n1stmuonTot/(n1stmuonTot+n1stnonmuonTot)<<endl;
    
    Double_t n2ndpionTot = h2ndpion->Integral(0,nx+1);
    Double_t n2ndnonpionTot = h2ndnonpion->Integral(0,nx+1);
    cout<<"2nd track pion "<<n2ndpionTot<<" nonpion "<<n2ndnonpionTot<<" purity "<<n2ndpionTot/(n2ndpionTot+n2ndnonpionTot)<<endl;
    
    
    
    Double_t valsig;
    Double_t valbkg;
    Double_t purity;
    Double_t efficiency;
    
    Double_t valsigpi;
    Double_t valbkgpi;
    Double_t puritypi;
    //1st track
    for (int ix = 1; ix < nx; ix++){
        valsig = n1stmuonTot;
        valbkg = n1stnonmuonTot;
        hoptimize->SetBinContent(ix,0);
        hefficiency->SetBinContent(ix,0);
        
        
        for (int icutx = 1; icutx<=ix; icutx++) {
            valsig -= h1strmuon->GetBinContent(icutx);//remaining
            valbkg -= h1strnonmuon->GetBinContent(icutx);//remmaining
            
        }
        if (valsig==0) continue;
        purity = valsig/(valsig + valbkg);
        efficiency = (valsig + valbkg)/(n1stmuonTot+n1stnonmuonTot);
        if (purity<1.1) hoptimize->SetBinContent(ix,purity);
        if (efficiency<1.1) hefficiency->SetBinContent(ix,efficiency);
        cout<<"binx "<<ix<<" at "<<hoptimize->GetXaxis()->GetBinUpEdge(ix)<<" purity "<<purity<<endl;
    }
    
    //2nd track
    for (int ix = 1; ix < nx; ix++){
        valsig2 = n2ndpionTot;
        valbkg2 = n2ndnonpionTot;
        hoptimize2->SetBinContent(ix,0);
        
        for (int icutx = 1; icutx<=ix; icutx++) {
            valsig2 -= h2ndpion->GetBinContent(icutx);//remaining
            valbkg2 -= h2ndnonpion->GetBinContent(icutx);//remmaining
        }
        if (valsig2==0) continue;
        purity2 = valsig2/(valsig2 + valbkg2);
        if (purity2<1.1) hoptimize2->SetBinContent(ix,purity2);
        cout<<"binx "<<ix<<" at "<<hoptimize2->GetXaxis()->GetBinUpEdge(ix)<<" purity "<<purity2<<endl;
    }
    
    new TCanvas;
    hoptimize->Draw("hist");
    hoptimize2->SetLineColor(2);
    hoptimize2->Draw("hist same");
    hefficiency->SetLineColor(3);
    hefficiency->Draw("hist same");
    
    
    //optimize for cr2
    /*sampleth = 3;
    
    //optimize for cr3
    sampleth = 3;*/
    
    
}