{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_opt8.root");
    
    const Int_t ithvar = 41;//ccqe+FSI
    const Int_t NVARIABLES = 1;
    char* atitle[NVARIABLES];
    atitle[0] = "Discriminant parameter (CCQE FSI)";
    
    const Int_t ithtopo = 3;
    const Int_t NTOPOLOGY = 1;
    const int NINTERACTION = 10;
    TH1F* hmc[NTOPOLOGY][NVARIABLES][NINTERACTION];
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t ivar=0; ivar<NVARIABLES; ++ivar) {
            for (Int_t iint=0; iint<NINTERACTION; ++iint) {
                hmc[itopo][ivar][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",ithtopo,ithvar,iint));
                cout<<hmc[itopo][ivar][iint] ->Integral()<<endl;
            }
        }
    }
    //sum of background
    TH1F* hsig = (TH1F*)hmc[0][0][1]->Clone("hsignal");
    TH1F* hbkg = (TH1F*)hmc[0][0][2]->Clone("hbackground");
    for (Int_t iint=3; iint<NINTERACTION; ++iint) {
        hbkg->Add(hmc[0][0][iint]);
    }
    
    //optimization
    TH1* hoptimize = (TH1F*)hsig->Clone("hoptimize");
    Int_t nx = hoptimize -> GetNbinsX()+1;
    Double_t xcutatMax;
    Double_t valsigTot = hsig->Integral(0,nx+1);
    Double_t valbkgTot = hbkg->Integral(0,nx+1);
    cout<<"SigTot "<<valsigTot<<" BkgTot "<<valbkgTot<<" purity "<<valsigTot/(valsigTot+valbkgTot)<<endl;
    Double_t valsig;
    Double_t valbkg;
    Double_t significantRaw = valsigTot/sqrt(valbkgTot);
    Double_t significant;
    Double_t significantMax = significantRaw;
    Int_t binxwMax=0;
    
    for (int ix = nx; ix >= 1; ix--){
        valsig = valsigTot;
        valbkg = valbkgTot;
        for (int icutx = ix; icutx<=nx; icutx++) {
            valsig -= hsig->GetBinContent(icutx);//remaining
            valbkg -= hbkg->GetBinContent(icutx);//remmaining
        }
        if (valbkg==0) continue;
        significant = valsig/sqrt(valbkg);
        if (significant>significantMax) {
            significantMax = significant;
            binxwMax = ix;
            
        }
        hoptimize->SetBinContent(ix,significant);
        cout<<"raw "<<significantRaw<<" sig "<<significant<<" at "<<hoptimize->GetXaxis()->GetBinLowEdge(ix)<<endl;
    }
    cout<<"raw "<<significantRaw<<"max "<<significantMax<<" at "<<hoptimize->GetXaxis()->GetBinLowEdge(binxwMax)<<endl;
    new TCanvas;
    hoptimize->Draw("hist");
    //hbkg->SetLineColor(2);
    //hbkg->Draw("hist same");
    
    
}