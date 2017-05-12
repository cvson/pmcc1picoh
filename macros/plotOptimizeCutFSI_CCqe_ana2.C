{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana2.root");
    
    const int NVARIABLES = 47;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    const int NTOPOLOGY = 27;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    const int thvariable = 43;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="pidccqe";
    char *xtitle = "Discriminant parameter (CCQE)";
    double rangemax = 0.5;
    int nrebin = 1;
    
    TH1F* hmcen[NTOPOLOGY][NINTERACTION];
    TH1F* hdata[NTOPOLOGY];
    
    
    
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        //energy plots
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcen[itopo][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",itopo,thvariable,iint));
            hmcen[itopo][iint]->Rebin(nrebin);
            hmcen[itopo][iint]->SetLineWidth(3);
            
        }
        hdata[itopo] = (TH1F*)pfile->Get(Form("hdata_topo%d_var%d",itopo,0));
        
    }//end itopo
    //all 2 track & forward-2nd track
    
    
    
    //sum of background
    //7 is after cccoh-like pid cut and vertex activity cut
    TH1F* hsig = (TH1F*)hmcen[7][1]->Clone("hsignal");
    TH1F* hbkg = (TH1F*)hmcen[7][2]->Clone("hbackground");
    for (Int_t iint=3; iint<NINTERACTION; ++iint) {
        hbkg->Add(hmcen[7][iint]);
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
        cout<<"raw "<<significantRaw<<" sig "<<significant<<" at "<<hoptimize->GetXaxis()->GetBinUpEdge(ix)<<endl;
    }
    cout<<"raw "<<significantRaw<<"max "<<significantMax<<" at "<<hoptimize->GetXaxis()->GetBinUpEdge(binxwMax)<<endl;
    new TCanvas;
    hoptimize->GetXaxis()->SetTitle("Cut values on discriminant parameter (CCQE)");
    hoptimize->GetYaxis()->SetTitle("Signal significane S/#sqrt{B}");
    titleStyle(hoptimize);
    Int_t ci;
    ci = TColor::GetColor("#D55E00");
    hoptimize->SetLineColor(ci);
    hoptimize->Draw("hist");
    gPad->Print("plots/ana2_"+varname+"_opt.eps");
    //hbkg->SetLineColor(2);
    //hbkg->Draw("hist same");
    
    
}
