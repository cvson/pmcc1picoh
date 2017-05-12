{
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    /*TString subname = "basicdatamc_official_pidvalidate_noveract_";
     TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_4pidvalidate.root");
     TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_4validate.root");
     */
    TString subname = "basicdatamc_official_pidvalidate_finalsel_";
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff.root");
    TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff.root");
    //TFile *pfile = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_4validate.root");
    //TFile *pfile = new TFile("../outputs/basicHisto_datamc_genie.root");
    const int NVARIABLES = 42;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    const int NTOPOLOGY = 27;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    const int thvariable = 39;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="pidcoh";
    char *xtitle = "Discriminant parameter (COH)";
    double rangemax = 0.5;
    int nrebin = 2;
    
   /*const int thvariable = 42;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="pid1pres";
    char *xtitle = "Discriminant parameter (RES)";
    double rangemax = 0.5;
    int nrebin = 2;
    */
    /*const int thvariable = 43;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="pidccqe";
    char *xtitle = "Discriminant parameter (CCQE)";
    double rangemax = 0.5;
    int nrebin = 2;*/
    double effmax = 0.1;
    TH1F* hmcen[NTOPOLOGY][NINTERACTION];
    TH1F* hdata[NTOPOLOGY];
    
    TH1F* hmcengenie[NTOPOLOGY][NINTERACTION];
    
    
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        //energy plots
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcen[itopo][iint] = (TH1F*)pfile->Get(Form("hmc_topo%d_var%d_int%d",itopo,thvariable,iint));
            hmcengenie[itopo][iint] = (TH1F*)pfilegenie->Get(Form("hmc_topo%d_var%d_int%d",itopo,thvariable,iint));
            hmcen[itopo][iint]->Rebin(nrebin);
            hmcengenie[itopo][iint]->Rebin(nrebin);
            hmcen[itopo][iint]->SetLineWidth(3);
            
        }
        hdata[itopo] = (TH1F*)pfile->Get(Form("hdata_topo%d_var%d",itopo,0));
        
    }//end itopo
    //all 2 track & forward-2nd track
    
    
    new TCanvas;
    Int_t ci;
    ci = TColor::GetColor("#0072B2");
    hmcen[1][1]->SetLineColor(ci);
    hmcen[1][1]->GetXaxis()->SetTitle(xtitle);
    hmcen[1][1]->GetYaxis()->SetTitle("Normalization");
    hmcen[1][1]->GetXaxis()->SetRangeUser(-1.0,rangemax);
    //hmcen[1][1]->GetYaxis()->SetRangeUser(0,effmax);
    
    ci = TColor::GetColor("#D55E00");
    hmcen[1][2]->SetLineColor(ci);
    ci = TColor::GetColor("#CC79A7");
    hmcen[1][3]->SetLineColor(ci);
    ci = TColor::GetColor("#009E73");
    hmcen[1][4]->SetLineColor(ci);
    ci = TColor::GetColor("#000000");
    hmcen[1][5]->SetLineColor(ci);
    for (Int_t irec=6; irec<10; irec++) {
        hmcen[1][5]->Add(hmcen[1][irec]);
    }
    
    //normalize
    for (Int_t ihist=1; ihist<6; ihist++) {
        hmcen[1][ihist]->Scale(1./(hmcen[1][ihist]->Integral(0,hmcen[1][ihist]->GetNbinsX())));
    }
    titleStyle(hmcen[1][1]);
    hmcen[1][1]->GetYaxis()->SetRangeUser(0,effmax);
    hmcen[1][1]->Draw("hist");
    
    for (Int_t ihist=2; ihist<6; ihist++) {
        hmcen[1][ihist]->Draw("hist same");
    }
    TLegend *pleg = new TLegend(0.2,0.5,0.55,0.87);
    pleg->SetFillStyle(0);
    pleg->SetBorderSize(0);
    pleg->SetTextFont(43);
    pleg->SetTextSize(23);
    //pleg->SetTextSize(0.04);
    pleg->AddEntry(hmcen[1][1],"#nu_{#mu} CC coh. #pi","l");
    pleg->AddEntry(hmcen[1][2],"#nu_{#mu} CC 0#pi","l");
    pleg->AddEntry(hmcen[1][3],"#nu_{#mu} CC 1#pi","l");
    pleg->AddEntry(hmcen[1][4],"#nu_{#mu} CC (N>1)#pi","l");
    pleg->AddEntry(hmcen[1][5],"Others","l");
    pleg->Draw();
    
    gPad->Print("plots/"+varname+"_presel.eps");
    
    
    
    
    
    
}
