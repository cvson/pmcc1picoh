{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    TString subname="optimizeTrueIDCCQE_";
    ////////////////////////////////////////////////////////////////////
    ////True track
    TFile *pfile = new TFile("../outputs/checkFSI_fsiselopt12.root");
    
    const int NVARIABLES = 11;
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
            
        }//end ivar
    }//end itopo
    ////////////////////////////////////////////////////////////////////
    ////True interaction
    TFile *pfileint = new TFile("../outputs/basicHisto_datamcfsi_opt12.root");
    
    const Int_t ithvarccqe = 41;//ccqe+FSI
    const Int_t ithvarres = 40;//ccres+FSI
    
    const Int_t NVARIABLES = 2;
    char* atitle[NVARIABLES];
    atitle[0] = "Discriminant parameter (CCQE FSI)";
    
    const Int_t ithtopo = 4;
    const Int_t NTOPOLOGY = 1;
    const int NINTERACTION = 10;
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                if(ivar==0) hmc[itopo][ivar][iint] = (TH1F*)pfileint->Get(Form("hmc_topo%d_var%d_int%d",ithtopo,ithvarccqe,iint));
                if(ivar==1) hmc[itopo][ivar][iint] = (TH1F*)pfileint->Get(Form("hmc_topo%d_var%d_int%d",ithtopo,ithvarres,iint));
                //cout<<hmc[itopo][ivar][iint] ->Integral()<<endl;
            }
        }
    }
    //sum of background
    TH1F* hsigcoh_ccqe = (TH1F*)hmc[0][0][1]->Clone("hsigcoh_ccqe");
    TH1F* hsigccqe_ccqe = (TH1F*)hmc[0][0][2]->Clone("hsigccqe_ccqe");
    TH1F* htot_ccqe = (TH1F*)hmc[0][0][1]->Clone("htot_ccqe");
    
    TH1F* hsigcoh_res = (TH1F*)hmc[0][1][1]->Clone("hsigcoh_res");
    TH1F* hsigccqe_res = (TH1F*)hmc[0][1][2]->Clone("hsigccqe_res");
    TH1F* htot_res = (TH1F*)hmc[0][1][1]->Clone("htot_res");
    
    for (Int_t iint=2; iint<NINTERACTION; ++iint) {
        htot_ccqe->Add(hmc[0][0][iint]);
        htot_res->Add(hmc[0][1][iint]);
    }
    
    
    //optimize for cr1
    //0 for muon, 7 for pion
    Int_t sampleth = ithtopo-1;
    Int_t varthccqe = 10;
    Int_t varthres = 9;
    //sum of background
    TH1F* h1stccqemuon = (TH1F*)hmc[sampleth][varthccqe][0]->Clone("h1stccqemuon");
    TH1F* h1stccqenonmuon = (TH1F*)hmc[sampleth][varthccqe][1]->Clone("h1stccqenonmuon");
    
    TH1F* h1stresmuon = (TH1F*)hmc[sampleth][varthres][0]->Clone("h1stresmuon");
    TH1F* h1stresnonmuon = (TH1F*)hmc[sampleth][varthres][1]->Clone("h1stresnonmuon");
    
    
    
    for (Int_t iint=2; iint<5; ++iint) {
        h1stccqenonmuon->Add(hmc[sampleth][varthccqe][iint]);
        h1stresnonmuon->Add(hmc[sampleth][varthres][iint]);
    }
    
    TH1F* h2ndccqepion = (TH1F*)hmc[sampleth][varthccqe][7]->Clone("h2ndccqepion");
    TH1F* h2ndccqenonpion = (TH1F*)hmc[sampleth][varthccqe][5]->Clone("h2ndccqenonpion");
    
    TH1F* h2ndrespion = (TH1F*)hmc[sampleth][varthres][7]->Clone("h2ndrespion");
    TH1F* h2ndresnonpion = (TH1F*)hmc[sampleth][varthres][5]->Clone("h2ndresnonpion");
    
    for (Int_t iint=6; iint<10; ++iint) {
        if (iint!=7) h2ndccqenonpion->Add(hmc[sampleth][varthccqe][iint]);
        if (iint!=7) h2ndresnonpion->Add(hmc[sampleth][varthres][iint]);
    }
    
    
    //optimization
    TH1* hccqepuritymu = (TH1F*)h1stccqemuon->Clone("hccqepuritymu");
    TH1* hccqepuritypi = (TH1F*)h2ndccqepion->Clone("hccqepuritypi");
    TH1* hccqeefficiency = (TH1F*)h2ndccqepion->Clone("hccqeefficiency");
    
    
    //True information
    
    
    Double_t ncohTot = hsigcoh_ccqe->Integral(0,hsigcoh_ccqe->GetNbinsX()+1);
    Double_t nccqeTot = hsigccqe_ccqe->Integral(0,hsigccqe_ccqe->GetNbinsX()+1);
    Double_t ntotTot = htot_ccqe->Integral(0,htot_ccqe->GetNbinsX()+1);
    cout<<"COH "<<ncohTot*100./ntotTot<<endl;
    cout<<"CCQE "<<nccqeTot*100./ntotTot<<endl;
    

    
    
    Int_t nx = hccqepuritymu -> GetNbinsX()+1;
    
    Double_t xcutatMax;
    Double_t n1stmuonTot = h1stccqemuon->Integral(0,nx+1);
    Double_t n1stnonmuonTot = h1stccqenonmuon->Integral(0,nx+1);
    cout<<"1st track muon "<<n1stmuonTot<<" nonmuon "<<n1stnonmuonTot<<" purity "<<n1stmuonTot/(n1stmuonTot+n1stnonmuonTot)<<endl;
    
    Double_t n2ndpionTot = h2ndccqepion->Integral(0,nx+1);
    Double_t n2ndnonpionTot = h2ndccqenonpion->Integral(0,nx+1);
    cout<<"2nd track pion "<<n2ndpionTot<<" nonpion "<<n2ndnonpionTot<<" purity "<<n2ndpionTot/(n2ndpionTot+n2ndnonpionTot)<<endl;
    
    //expectation
    Double_t    uppercentcoh = 0.03;
    Double_t    uppercentccqe = 0.05;
    Double_t    uppercent1stmu = 0.8;
    Double_t    uppercent2ndpi = 0.5;
    
    Double_t    percentcoh;
    Double_t    percentccqe;
    Double_t    percent1stmu;
    Double_t    percent2ndpi;
    
    
    //for purity
    Double_t ncoh;
    Double_t nccqe;
    Double_t ntot;
    
    //for true
    Double_t n1stmuon;
    Double_t n1stnonmuon;
    Double_t n2ndpion;
    Double_t n2ndnonpion;
    
    
    //200 bins
    
    for (int ixqe = 1; ixqe < nx; ixqe++){//ccqecut
        n1stmuon = n1stmuonTot;
        n1stnonmuon = n1stnonmuonTot;
        n2ndpion = n2ndpionTot;
        n2ndnonpion = n2ndnonpionTot;
        ncoh = ncohTot;
        nccqe = nccqeTot;
        ntot = ntotTot;
        for (int jxqe = ixqe; jxqe < nx; jxqe++){//reduce
            n1stmuon -=  h1stccqemuon->GetBinContent(jxqe);
            n1stnonmuon -=  h1stccqenonmuon->GetBinContent(jxqe);
            n2ndpion -=  h2ndccqepion->GetBinContent(jxqe);
            n2ndnonpion -=  h2ndccqenonpion->GetBinContent(jxqe);
            ncoh -=  hsigcoh_ccqe->GetBinContent(jxqe);
            nccqe -=  hsigccqe_ccqe->GetBinContent(jxqe);
            ntot -=  htot_ccqe->GetBinContent(jxqe);
            
        }
        
        /*for (int ixres = 1; ixres < nx; ixres++){//rescut
            
            for (int jxres = 1; jxres < ixres; jxres++){//reduce
                n1stmuon -=  h1stresmuon->GetBinContent(jxres);
                n1stnonmuon -=  h1stresnonmuon->GetBinContent(jxres);
                n2ndpion -=  h2ndrespion->GetBinContent(jxres);
                n2ndnonpion -=  h2ndresnonpion->GetBinContent(jxres);
                ncoh -=  hsigcoh_res->GetBinContent(jxres);
                nccqe -=  hsigccqe_res->GetBinContent(jxres);
                ntot -=  htot_res->GetBinContent(jxres);
                
            }
         
        }*/
        
        percentcoh = ncoh*1.0/ntot;
        percentccqe = nccqe*1.0/ntot;
        percent1stmu = n1stmuon*1.0/(n1stmuon + n1stnonmuon);
        percent2ndpi = n2ndpion*1.0/(n2ndpion +  n2ndnonpion);
        //if(percentccqe<uppercentccqe && percent1stmu> uppercent1stmu)
            cout<<"ixqe "<<ixqe<< " ccqe "<<percentccqe<<" truemu "<<percent1stmu<<endl;
       
    }
    
    
   /* Double_t valsig;
    Double_t valbkg;
    Double_t purity;
    Double_t efficiency;
    
    Double_t valsigpi;
    Double_t valbkgpi;
    Double_t puritypi;
    //1st track
    
        valsig = n1stmuonTot;
        valbkg = n1stnonmuonTot;
        hccqepuritymu->SetBinContent(ix,0);
        hccqeefficiency->SetBinContent(ix,0);
        
        
        for (int icutx = 1; icutx<=ix; icutx++) {
            valsig -= h1stccqemuon->GetBinContent(icutx);//remaining
            valbkg -= h1stccqenonmuon->GetBinContent(icutx);//remmaining
            
        }
        if (valsig==0) continue;
        purity = valsig/(valsig + valbkg);
        efficiency = (valsig + valbkg)/(n1stmuonTot+n1stnonmuonTot);
        if (purity<1.1) hccqepuritymu->SetBinContent(ix,purity);
        if (efficiency<1.1) hccqeefficiency->SetBinContent(ix,efficiency);
        cout<<"binx "<<ix<<" at "<<hccqepuritymu->GetXaxis()->GetBinUpEdge(ix)<<" purity "<<purity<<endl;
    }
    
    //2nd track
    for (int ix = 1; ix < nx; ix++){
        valsig2 = n2ndpionTot;
        valbkg2 = n2ndnonpionTot;
        hccqepuritypi->SetBinContent(ix,0);
        
        for (int icutx = 1; icutx<=ix; icutx++) {
            valsig2 -= h2ndccqepion->GetBinContent(icutx);//remaining
            valbkg2 -= h2ndccqenonpion->GetBinContent(icutx);//remmaining
        }
        if (valsig2==0) continue;
        purity2 = valsig2/(valsig2 + valbkg2);
        if (purity2<1.1) hccqepuritypi->SetBinContent(ix,purity2);
        cout<<"binx "<<ix<<" at "<<hccqepuritypi->GetXaxis()->GetBinUpEdge(ix)<<" purity "<<purity2<<endl;
    }
    
    new TCanvas;
    hccqepuritymu->Draw("hist");
    hccqepuritypi->SetLineColor(2);
    hccqepuritypi->Draw("hist same");
    hccqeefficiency->SetLineColor(3);
    hccqeefficiency->Draw("hist same");
    
    
    */
    
    
}