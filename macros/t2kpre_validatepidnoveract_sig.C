{
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    /*TString subname = "basicdatamc_official_pidvalidate_noveract_";    
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_4pidvalidate.root");
    TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_4validate.root");
    */
    TString subname = "ana1x_pidnoveractvalidate_";    
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_kikawa.root");
    TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_kikawa.root");
    //TFile *pfile = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_4validate.root");
    //TFile *pfile = new TFile("../outputs/basicHisto_datamc_genie.root");
    const int NVARIABLES = 42;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    const int NTOPOLOGY = 35;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    const int thvariable = 20;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="pangt";
    char *xtitle = "#pi-like track angle (#circ)";
    double effmax = 100;
    double rangemax = 90;
    int nrebin = 2;
    
   /* const int thvariable = 19;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="muangt";
    char *xtitle = "#mu-like track angle (#circ)";
    double effmax = 100;
    double rangemax = 30;
    int nrebin = 2;
    */
 
   /* const int thvariable = 36;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,  
    TString varname ="veract";
    char *xtitle = "Energy deposit at vertex (MeV)";
    double effmax = 100;
    double rangemax = 50;
    int nrebin = 2;
    */

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
        }
        hdata[itopo] = (TH1F*)pfile->Get(Form("hdata_topo%d_var%d",itopo,0));
        
    }//end itopo
    //all 2 track & forward-2nd track
    
   /* double nevnt_all = hmcen[1][1] ->Integral(0, hmcen[1][1]->GetNbinsX()+1);
    cout<<"Total "<<nevnt_all<<endl;
    //CC1picoh
    //me
     cout<<"===================== COH======================="<<endl;
    double nevnt_coh_me = hmcen[2][1] ->Integral(0, hmcen[2][1]->GetNbinsX()+1);
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_all<<endl;
    //kikawa
    double nevnt_coh_kikawa = hmcen[27][1] ->Integral(0, hmcen[27][1]->GetNbinsX()+1);
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_all<<endl;
    
    //allpass
    double nevnt_coh_allpass = hmcen[17][1] ->Integral(0, hmcen[17][1]->GetNbinsX()+1);
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_all<<endl;
    
    //me-not-kikawa
    double nevnt_coh_me_not_kikawa = hmcen[15][1] ->Integral(0, hmcen[15][1]->GetNbinsX()+1);
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_all<<endl;
    
    //not-me-kikawa
    double nevnt_coh_not_me_kikawa = hmcen[16][1] ->Integral(0, hmcen[16][1]->GetNbinsX()+1);
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_all<<endl;
    
    //me-not-kikawa
    double nevnt_coh_notall= hmcen[19][1] ->Integral(0, hmcen[19][1]->GetNbinsX()+1);
    cout<<"Not-all "<<nevnt_coh_notall<<" percent "<<nevnt_coh_notall*100./nevnt_all<<endl;
    */
    
    double nevnt_all = hmcengenie[1][1] ->Integral(0, hmcengenie[1][1]->GetNbinsX()+1);
    cout<<"Total "<<nevnt_all<<endl;
    //CC1picoh
    //me
    cout<<"===================== COH======================="<<endl;
    double nevnt_coh_me = hmcengenie[2][1] ->Integral(0, hmcengenie[2][1]->GetNbinsX()+1);
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_all<<endl;
    //kikawa
    double nevnt_coh_kikawa = hmcengenie[27][1] ->Integral(0, hmcengenie[27][1]->GetNbinsX()+1);
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_all<<endl;
    
    //allpass
    double nevnt_coh_allpass = hmcengenie[17][1] ->Integral(0, hmcengenie[17][1]->GetNbinsX()+1);
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_all<<endl;
    
    //me-not-kikawa
    double nevnt_coh_me_not_kikawa = hmcengenie[15][1] ->Integral(0, hmcengenie[15][1]->GetNbinsX()+1);
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_all<<endl;
    
    //not-me-kikawa
    double nevnt_coh_not_me_kikawa = hmcengenie[16][1] ->Integral(0, hmcengenie[16][1]->GetNbinsX()+1);
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_all<<endl;
    
    //me-not-kikawa
    double nevnt_coh_notall= hmcengenie[19][1] ->Integral(0, hmcengenie[19][1]->GetNbinsX()+1);
    cout<<"Not-all "<<nevnt_coh_notall<<" percent "<<nevnt_coh_notall*100./nevnt_all<<endl;
    

    //redefine
     cout<<"=====================REDEFINE COH======================="<<endl;
    double nevnt_coh_meorkikawa = nevnt_coh_me + nevnt_coh_kikawa - nevnt_coh_allpass;
    cout<<"Selected by either "<<nevnt_coh_meorkikawa<<" percent "<<nevnt_coh_meorkikawa*100/nevnt_all<<endl;
    
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_coh_meorkikawa<<endl;
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_coh_meorkikawa<<endl;
    

    /*cout<<"=====================CCQE======================="<<endl;
    double nevnt_ccqe_me = hmcen[12][1] ->Integral(0, hmcen[12][1]->GetNbinsX()+1);
    cout<<"Me pass "<<nevnt_ccqe_me<<" percent "<<nevnt_ccqe_me*100./nevnt_all<<endl;
    //kikawa
    double nevnt_ccqe_kikawa = hmcen[11][1] ->Integral(0, hmcen[11][1]->GetNbinsX()+1);
    cout<<"Kikawa pass "<<nevnt_ccqe_kikawa<<" percent "<<nevnt_ccqe_kikawa*100./nevnt_all<<endl;
    
    //allpass
    double nevnt_ccqe_allpass = hmcen[17][1] ->Integral(0, hmcen[17][1]->GetNbinsX()+1);
    cout<<"All pass "<<nevnt_ccqe_allpass<<" percent "<<nevnt_ccqe_allpass*100./nevnt_all<<endl;
    
    //me-not-kikawa
    double nevnt_ccqe_me_not_kikawa = hmcen[18][1] ->Integral(0, hmcen[18][1]->GetNbinsX()+1);
    cout<<"Me-not-kiawa "<<nevnt_ccqe_me_not_kikawa<<" percent "<<nevnt_ccqe_me_not_kikawa*100./nevnt_all<<endl;
    
    //not-me-kikawa
    double nevnt_ccqe_not_me_kikawa = hmcen[19][1] ->Integral(0, hmcen[19][1]->GetNbinsX()+1);
    cout<<"Not-me-kikawa "<<nevnt_ccqe_not_me_kikawa<<" percent "<<nevnt_ccqe_not_me_kikawa*100./nevnt_all<<endl;
    
    //me-not-kikawa
    double nevnt_ccqe_notall= hmcen[20][1] ->Integral(0, hmcen[20][1]->GetNbinsX()+1);
    cout<<"Not-all "<<nevnt_ccqe_notall<<" percent "<<nevnt_ccqe_notall*100./nevnt_all<<endl;
    
    cout<<"=====================REDEFINE CCQE======================="<<endl;
    double nevnt_ccqe_meorkikawa = nevnt_ccqe_me + nevnt_ccqe_kikawa - nevnt_ccqe_allpass;
    cout<<"Selected by either "<<nevnt_ccqe_meorkikawa<<" percent "<<nevnt_ccqe_meorkikawa*100/nevnt_all<<endl;
    
    cout<<"Me pass "<<nevnt_ccqe_me<<" percent "<<nevnt_ccqe_me*100./nevnt_ccqe_meorkikawa<<endl;
    cout<<"Kikawa pass "<<nevnt_ccqe_kikawa<<" percent "<<nevnt_ccqe_kikawa*100./nevnt_ccqe_meorkikawa<<endl;
    cout<<"All pass "<<nevnt_ccqe_allpass<<" percent "<<nevnt_ccqe_allpass*100./nevnt_ccqe_meorkikawa<<endl;
    cout<<"Me-not-kiawa "<<nevnt_ccqe_me_not_kikawa<<" percent "<<nevnt_ccqe_me_not_kikawa*100./nevnt_ccqe_meorkikawa<<endl;
    cout<<"Not-me-kikawa "<<nevnt_ccqe_not_me_kikawa<<" percent "<<nevnt_ccqe_not_me_kikawa*100./nevnt_ccqe_meorkikawa<<endl;
    
    //data
    
    //efficiency & purity
    //purity
    cout<<"TMVA purity "<<hmcen[12][2]->Integral(0,hmcen[12][2]->GetNbinsX()+1)*100./(hmcen[12][1]->Integral(0,hmcen[12][1]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmcen[11][2]->Integral(0,hmcen[11][2]->GetNbinsX()+1)*100./hmcen[11][1]->Integral(0,hmcen[11][1]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmcen[12][2]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmcen[12][1]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmcen[11][2]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmcen[11][1]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,10);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_purity",0.5,0.45);
    */
    //efficiency of event selected
    cout<<"FOR NEUT=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcen[2][1]->Integral(0,hmcen[2][1]->GetNbinsX()+1)*100./hmcen[1][1]->Integral(0,hmcen[1][1]->GetNbinsX()+1)<<endl;
    
    cout<<"NOM efficiency "<<hmcen[27][1]->Integral(0,hmcen[27][1]->GetNbinsX()+1)*100./hmcen[1][1]->Integral(0,hmcen[1][1]->GetNbinsX()+1)<<endl;
   cout<<"FOR GENIE=================>"<<endl; 
    cout<<"TMVA efficiency "<<hmcengenie[2][1]->Integral(0,hmcengenie[2][1]->GetNbinsX()+1)*100./hmcengenie[1][1]->Integral(0,hmcengenie[1][1]->GetNbinsX()+1)<<endl;
    
    cout<<"NOM efficiency "<<hmcengenie[27][1]->Integral(0,hmcengenie[27][1]->GetNbinsX()+1)*100./hmcengenie[1][1]->Integral(0,hmcengenie[1][1]->GetNbinsX()+1)<<endl;
    
    
    TH1F* hefficiency_cutmva = hmcen[2][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmcen[1][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmcen[27][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmcen[1][1]);
    hefficiency_cutnom->Scale(100.);
    
    hefficiency_cutmva->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,effmax);
    
    TH1F* hefficiency_genie_cutmva = hmcengenie[2][1]->Clone("hefficiency_genie_cutmva");
    hefficiency_genie_cutmva->Divide(hmcengenie[1][1]);
    hefficiency_genie_cutmva->Scale(100.);
    
    TH1F* hefficiency_genie_cutnom = hmcengenie[27][1]->Clone("hefficiency_genie_cutnom");
    hefficiency_genie_cutnom->Divide(hmcengenie[1][1]);
    hefficiency_genie_cutnom->Scale(100.);
    
    hefficiency_cutnom->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutnom->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutnom->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutnom->GetYaxis()->SetRangeUser(0,effmax);
    
        
    plot2hist(hefficiency_cutmva,"NEUT",hefficiency_genie_cutmva,"GENIE",subname+varname+"sigeff_mva",0.6,0.6);
    plot2hist(hefficiency_cutnom,"NEUT",hefficiency_genie_cutnom,"GENIE",subname+varname+"sigeff_nom",0.6,0.6); 

    
    
   }
