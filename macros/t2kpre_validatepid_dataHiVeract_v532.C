{
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil_v532.C");
    
    TString subname = "ana1x_pidvalidate_v532_";
    const int NTOPOLOGY = 8;
    TFile *pfile[NTOPOLOGY];
    TFile *pfilegenie[NTOPOLOGY];
    TFile *pfilev5142[NTOPOLOGY];
    //id 14: is presel + >50
    //id 173: pidfsi>0.05 + >50
    //id 174: muang<15, mucl>0.6, pmucl>0.25
    Int_t topoindex[NTOPOLOGY] = {14,173,174,21,22,23,24,25};
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        pfile[itopo] = new TFile(Form("../outputs/basicHisto_neut5d3d2_20170529_sam%d.root",topoindex[itopo]));//neut532.
        pfilegenie[itopo] = new TFile(Form("../outputs/basicHisto_genie_20170529_sam%d.root",topoindex[itopo]));//genie.
        pfilev5142[itopo] = new TFile(Form("../outputs/basicHisto_neut5d1d4d2_20170529_sam%d.root",topoindex[itopo]));//neut5.14.2.
    }
   
    const int NVARIABLES = 42;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    
    //select variable to plots
    const int thvariable = 20;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
     TString varname ="pangt";
     char *xtitle = "#pi-like track angle (#circ)";
     double effmax = 20;
     double rangemax = 90;
     int nrebin = 6;
     
    
    /*const int thvariable = 19;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
     TString varname ="muangt";
     char *xtitle = "#mu-like track angle (#circ)";
     double effmax = 20;
     double rangemax = 30;
     int nrebin = 3;
    */
    
    /*const int thvariable = 36;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="veract";
    char *xtitle = "Energy deposit at vertex (MeV)";
    double effmax = 30;
    double rangemax = 200;
    int nrebin = 4;
    */
    
    TH1F* hmcen[NTOPOLOGY][NINTERACTION];
    TH1F* hdata[NTOPOLOGY];
    TH1F* hmcengenie[NTOPOLOGY][NINTERACTION];
    TH1F* hmcenv5142[NTOPOLOGY][NINTERACTION];
    
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        //energy plots
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcen[itopo][iint] = (TH1F*)pfile[itopo]->Get(Form("hmc_topo%d_var%d_int%d",topoindex[itopo],thvariable,iint));
            hmcengenie[itopo][iint] = (TH1F*)pfilegenie[itopo]->Get(Form("hmc_topo%d_var%d_int%d",topoindex[itopo],thvariable,iint));
            hmcenv5142[itopo][iint] = (TH1F*)pfilev5142[itopo]->Get(Form("hmc_topo%d_var%d_int%d",topoindex[itopo],thvariable,iint));
            
            hmcen[itopo][iint]->Rebin(nrebin);
            hmcengenie[itopo][iint]->Rebin(nrebin);
            hmcenv5142[itopo][iint]->Rebin(nrebin);
        }
        hdata[itopo] = (TH1F*)pfile[itopo]->Get(Form("hdata_topo%d_var%d",topoindex[itopo],thvariable));
        hdata[itopo]->Rebin(nrebin);
    }//end itopo
    //all 2 track & forward-2nd track
    
    double nevnt_all = hmcen[0][0] ->Integral(0, hmcen[0][0]->GetNbinsX()+1);
    double nevnt_all_data = hdata[0] ->Integral(0, hdata[0]->GetNbinsX()+1);
    double nevnt_all_genie = hmcengenie[0][0] ->Integral(0, hmcengenie[0][0]->GetNbinsX()+1);
    double nevnt_all_v5142 = hmcenv5142[0][0] ->Integral(0, hmcenv5142[0][0]->GetNbinsX()+1);
    cout<<"Total DATA "<<nevnt_all_data<<" mc "<<nevnt_all<<" GENIE "<<nevnt_all_genie<<" v5142 "<<nevnt_all_v5142<<endl;
    
    
    //check pass failed between two selection
    //selecting one set belows
    /*cout<<"===================== COH data======================="<<endl;
    double nevnt_coh_me = hdata[1] ->Integral(0, hdata[1]->GetNbinsX()+1);
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_all_data<<endl;
    
    //kikawa
    double nevnt_coh_kikawa = hdata[2] ->Integral(0, hdata[2]->GetNbinsX()+1);
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_all_data<<endl;
    
    //allpass
    double nevnt_coh_allpass = hdata[6] ->Integral(0, hdata[6]->GetNbinsX()+1);
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_all_data<<endl;
    
    //me-not-kikawa
    double nevnt_coh_me_not_kikawa = hdata[4] ->Integral(0, hdata[4]->GetNbinsX()+1);
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_all_data<<endl;
    
    //not-me-kikawa
    double nevnt_coh_not_me_kikawa = hdata[5] ->Integral(0, hdata[5]->GetNbinsX()+1);
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_all_data<<endl;
    
    //me-not-kikawa
    double nevnt_coh_notall= hdata[7] ->Integral(0, hdata[7]->GetNbinsX()+1);
    cout<<"Not-all "<<nevnt_coh_notall<<" percent "<<nevnt_coh_notall*100./nevnt_all_data<<endl;
    
    
    //redefine
    cout<<"=====================REDEFINE COH======================="<<endl;
    double nevnt_coh_meorkikawa = nevnt_coh_me + nevnt_coh_kikawa - nevnt_coh_allpass;
    cout<<"Selected by either "<<nevnt_coh_meorkikawa<<" percent "<<nevnt_coh_meorkikawa*100/nevnt_all_data<<endl;
    
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_coh_meorkikawa<<endl;
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_coh_meorkikawa<<endl;
	*/
    /*cout<<"===================== COH NEUT 5.3.2======================="<<endl;
    double nevnt_coh_me = hmcen[1][0] ->Integral(0, hmcen[1][0]->GetNbinsX()+1);
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_all<<endl;
    
    //kikawa
    double nevnt_coh_kikawa = hmcen[2][0] ->Integral(0, hmcen[2][0]->GetNbinsX()+1);
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_all<<endl;
    
    //allpass
    double nevnt_coh_allpass = hmcen[6][0] ->Integral(0, hmcen[6][0]->GetNbinsX()+1);
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_all<<endl;
    
    //me-not-kikawa
    double nevnt_coh_me_not_kikawa = hmcen[4][0] ->Integral(0, hmcen[4][0]->GetNbinsX()+1);
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_all<<endl;
    
    //not-me-kikawa
    double nevnt_coh_not_me_kikawa = hmcen[5][0] ->Integral(0, hmcen[5][0]->GetNbinsX()+1);
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_all<<endl;
    
    //me-not-kikawa
    double nevnt_coh_notall= hmcen[7][0] ->Integral(0, hmcen[7][0]->GetNbinsX()+1);
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
	*/
	//me
    /*cout<<"===================== COH GENIE======================="<<endl;
    double nevnt_coh_me = hmcengenie[1][0] ->Integral(0, hmcengenie[1][0]->GetNbinsX()+1);
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_all_genie<<endl;
    
    //kikawa
    double nevnt_coh_kikawa = hmcengenie[2][0] ->Integral(0, hmcengenie[2][0]->GetNbinsX()+1);
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_all_genie<<endl;
    
    //allpass
    double nevnt_coh_allpass = hmcengenie[6][0] ->Integral(0, hmcengenie[6][0]->GetNbinsX()+1);
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_all_genie<<endl;
    
    //me-not-kikawa
    double nevnt_coh_me_not_kikawa = hmcengenie[4][0] ->Integral(0, hmcengenie[4][0]->GetNbinsX()+1);
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_all_genie<<endl;
    
    //not-me-kikawa
    double nevnt_coh_not_me_kikawa = hmcengenie[5][0] ->Integral(0, hmcengenie[5][0]->GetNbinsX()+1);
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_all_genie<<endl;
    
    //me-not-kikawa
    double nevnt_coh_notall= hmcengenie[7][0] ->Integral(0, hmcengenie[7][0]->GetNbinsX()+1);
    cout<<"Not-all "<<nevnt_coh_notall<<" percent "<<nevnt_coh_notall*100./nevnt_all_genie<<endl;
    
    
    //redefine
    cout<<"=====================REDEFINE COH======================="<<endl;
    double nevnt_coh_meorkikawa = nevnt_coh_me + nevnt_coh_kikawa - nevnt_coh_allpass;
    cout<<"Selected by either "<<nevnt_coh_meorkikawa<<" percent "<<nevnt_coh_meorkikawa*100/nevnt_all_genie<<endl;
    
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_coh_meorkikawa<<endl;
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_coh_meorkikawa<<endl;
    */

    cout<<"===================== COH v5142======================="<<endl;
    double nevnt_coh_me = hmcenv5142[1][0] ->Integral(0, hmcenv5142[1][0]->GetNbinsX()+1);
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_all_v5142<<endl;
    
    //kikawa
    double nevnt_coh_kikawa = hmcenv5142[2][0] ->Integral(0, hmcenv5142[2][0]->GetNbinsX()+1);
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_all_v5142<<endl;
    
    //allpass
    double nevnt_coh_allpass = hmcenv5142[6][0] ->Integral(0, hmcenv5142[6][0]->GetNbinsX()+1);
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_all_v5142<<endl;
    
    //me-not-kikawa
    double nevnt_coh_me_not_kikawa = hmcenv5142[4][0] ->Integral(0, hmcenv5142[4][0]->GetNbinsX()+1);
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_all_v5142<<endl;
    
    //not-me-kikawa
    double nevnt_coh_not_me_kikawa = hmcenv5142[5][0] ->Integral(0, hmcenv5142[5][0]->GetNbinsX()+1);
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_all_v5142<<endl;
    
    //me-not-kikawa
    double nevnt_coh_notall= hmcenv5142[7][0] ->Integral(0, hmcenv5142[7][0]->GetNbinsX()+1);
    cout<<"Not-all "<<nevnt_coh_notall<<" percent "<<nevnt_coh_notall*100./nevnt_all_v5142<<endl;
    
    
    //redefine
    cout<<"=====================REDEFINE COH======================="<<endl;
    double nevnt_coh_meorkikawa = nevnt_coh_me + nevnt_coh_kikawa - nevnt_coh_allpass;
    cout<<"Selected by either "<<nevnt_coh_meorkikawa<<" percent "<<nevnt_coh_meorkikawa*100/nevnt_all_v5142<<endl;
    
    cout<<"Me pass "<<nevnt_coh_me<<" percent "<<nevnt_coh_me*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Kikawa pass "<<nevnt_coh_kikawa<<" percent "<<nevnt_coh_kikawa*100./nevnt_coh_meorkikawa<<endl;
    cout<<"All pass "<<nevnt_coh_allpass<<" percent "<<nevnt_coh_allpass*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Me-not-kiawa "<<nevnt_coh_me_not_kikawa<<" percent "<<nevnt_coh_me_not_kikawa*100./nevnt_coh_meorkikawa<<endl;
    cout<<"Not-me-kikawa "<<nevnt_coh_not_me_kikawa<<" percent "<<nevnt_coh_not_me_kikawa*100./nevnt_coh_meorkikawa<<endl;

//////////////////////////////////////end of pass/fail test///////////////////////////////
    /*double nevnt_coh_meorkikawa_data = nevnt_coh_me_data + nevnt_coh_kikawa_data - nevnt_coh_allpass_data;
     cout<<"Selected by either DATA "<<nevnt_coh_meorkikawa_data<<" percent "<<nevnt_coh_meorkikawa_data*100/nevnt_all_data <<endl;
     
     cout<<"Me pass DATA "<<nevnt_coh_me_data <<" percent "<<nevnt_coh_me_data*100./nevnt_coh_meorkikawa_data <<endl;
     cout<<"kikawa pass DATA "<<nevnt_coh_kikawa_data <<" percent "<<nevnt_coh_kikawa_data*100./nevnt_coh_meorkikawa_data <<endl;
     cout<<"All pass DATA "<<nevnt_coh_allpass_data <<" percent "<<nevnt_coh_allpass_data*100./nevnt_coh_meorkikawa_data <<endl;
     cout<<"Me-not-kiawa DATA "<<nevnt_coh_me_not_kikawa_data <<" percent "<<nevnt_coh_me_not_kikawa_data*100./nevnt_coh_meorkikawa_data <<endl;
     cout<<"Not-me-kikawa DATA "<<nevnt_coh_not_me_kikawa_data <<" percent "<<nevnt_coh_not_me_kikawa_data*100./nevnt_coh_meorkikawa_data<<endl;
     */
    
    /*cout<<"=====================CCQE======================="<<endl;
     double nevnt_ccqe_me = hmcen[12][0] ->Integral(0, hmcen[12][0]->GetNbinsX()+1);
     cout<<"Me pass "<<nevnt_ccqe_me<<" percent "<<nevnt_ccqe_me*100./nevnt_all<<endl;
     //kikawa
     double nevnt_ccqe_kikawa = hmcen[11][0] ->Integral(0, hmcen[11][0]->GetNbinsX()+1);
     cout<<"Kikawa pass "<<nevnt_ccqe_kikawa<<" percent "<<nevnt_ccqe_kikawa*100./nevnt_all<<endl;
     
     //allpass
     double nevnt_ccqe_allpass = hmcen[17][0] ->Integral(0, hmcen[17][0]->GetNbinsX()+1);
     cout<<"All pass "<<nevnt_ccqe_allpass<<" percent "<<nevnt_ccqe_allpass*100./nevnt_all<<endl;
     
     //me-not-kikawa
     double nevnt_ccqe_me_not_kikawa = hmcen[18][0] ->Integral(0, hmcen[18][0]->GetNbinsX()+1);
     cout<<"Me-not-kiawa "<<nevnt_ccqe_me_not_kikawa<<" percent "<<nevnt_ccqe_me_not_kikawa*100./nevnt_all<<endl;
     
     //not-me-kikawa
     double nevnt_ccqe_not_me_kikawa = hmcen[19][0] ->Integral(0, hmcen[19][0]->GetNbinsX()+1);
     cout<<"Not-me-kikawa "<<nevnt_ccqe_not_me_kikawa<<" percent "<<nevnt_ccqe_not_me_kikawa*100./nevnt_all<<endl;
     
     //me-not-kikawa
     double nevnt_ccqe_notall= hmcen[1][0] ->Integral(0, hmcen[1][0]->GetNbinsX()+1);
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
     cout<<"TMVA purity "<<hmcen[12][2]->Integral(0,hmcen[12][2]->GetNbinsX()+1)*100./(hmcen[12][0]->Integral(0,hmcen[12][0]->GetNbinsX()+1))<<endl;
     cout<<"NOM purity "<<hmcen[11][2]->Integral(0,hmcen[11][2]->GetNbinsX()+1)*100./hmcen[11][0]->Integral(0,hmcen[11][0]->GetNbinsX()+1)<<endl;
     
     TH1F* hpurity_cutmva = hmcen[12][2]->Clone("hpurity_cutmva");
     hpurity_cutmva->Divide(hmcen[12][0]);
     hpurity_cutmva->Scale(100.);
     
     TH1F* hpurity_cutnom = hmcen[11][2]->Clone("hpurity_cutnom");
     hpurity_cutnom->Divide(hmcen[11][0]);
     hpurity_cutnom->Scale(100.);
     
     hpurity_cutmva->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
     hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
     hpurity_cutmva->GetXaxis()->SetRangeUser(0,10);
     hpurity_cutmva->GetYaxis()->SetRangeUser(0,100);
     plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+"comp_purity",0.5,0.45);
     */
    //efficiency of event selected
    cout<<"FOR NEUT=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcen[1][0]->Integral(0,hmcen[1][0]->GetNbinsX()+1)*100./hmcen[0][0]->Integral(0,hmcen[0][0]->GetNbinsX()+1)<<endl;
    
    cout<<"NOM efficiency "<<hmcen[2][0]->Integral(0,hmcen[2][0]->GetNbinsX()+1)*100./hmcen[0][0]->Integral(0,hmcen[0][0]->GetNbinsX()+1)<<endl;
    
    cout<<"FOR GENIE=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcengenie[1][0]->Integral(0,hmcengenie[1][0]->GetNbinsX()+1)*100./hmcengenie[0][0]->Integral(0,hmcengenie[0][0]->GetNbinsX()+1)<<endl;
    
    cout<<"NOM efficiency "<<hmcengenie[2][0]->Integral(0,hmcengenie[2][0]->GetNbinsX()+1)*100./hmcengenie[0][0]->Integral(0,hmcengenie[0][0]->GetNbinsX()+1)<<endl;
    
    cout<<"FOR NEUT 5.1.4.2=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcenv5142[1][0]->Integral(0,hmcenv5142[1][0]->GetNbinsX()+1)*100./hmcenv5142[0][0]->Integral(0,hmcenv5142[0][0]->GetNbinsX()+1)<<endl;
    
    cout<<"NOM efficiency "<<hmcenv5142[2][0]->Integral(0,hmcenv5142[2][0]->GetNbinsX()+1)*100./hmcenv5142[0][0]->Integral(0,hmcenv5142[0][0]->GetNbinsX()+1)<<endl;
    
    //neut 5.3.2
    TH1F* hefficiency_cutmva = hmcen[1][0]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmcen[0][0]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmcen[2][0]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmcen[0][0]);
    hefficiency_cutnom->Scale(100.);
    
    //data
    TH1F* hefficiency_cutmva_data = hdata[1]->Clone("hefficiency_cutmva_data");
    hefficiency_cutmva_data->Divide(hdata[0]);
    hefficiency_cutmva_data->Scale(100.);
    
    TH1F* hefficiency_cutnom_data = hdata[2]->Clone("hefficiency_cutnom_data");
    hefficiency_cutnom_data->Divide(hdata[0]);
    hefficiency_cutnom_data->Scale(100.);
    
    /*hefficiency_cutmva->GetXaxis()->SetTitle(xtitle);
     hefficiency_cutmva->GetYaxis()->SetTitle("Detection efficiency (%)");
     hefficiency_cutmva->GetXaxis()->SetRangeUser(0,rangemax);
     hefficiency_cutmva->GetYaxis()->SetRangeUser(0,effmax);
     */
    hefficiency_cutmva_data->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutmva_data->GetYaxis()->SetTitle("Detection efficiency (%)");
    hefficiency_cutmva_data->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutmva_data->GetYaxis()->SetRangeUser(0,effmax);
    
    hefficiency_cutnom_data->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutnom_data->GetYaxis()->SetTitle("Detection efficiency (%)");
    hefficiency_cutnom_data->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutnom_data->GetYaxis()->SetRangeUser(0,effmax);
    
    //genie
    TH1F* hefficiency_genie_cutmva = hmcengenie[1][0]->Clone("hefficiency_genie_cutmva");
    hefficiency_genie_cutmva->Divide(hmcengenie[0][0]);
    hefficiency_genie_cutmva->Scale(100.);
    
    TH1F* hefficiency_genie_cutnom = hmcengenie[2][0]->Clone("hefficiency_genie_cutnom");
    hefficiency_genie_cutnom->Divide(hmcengenie[0][0]);
    hefficiency_genie_cutnom->Scale(100.);
    
    //neut 5.1.4.2
    TH1F* hefficiency_v5142_cutmva = hmcenv5142[1][0]->Clone("hefficiency_v5142_cutmva");
    hefficiency_v5142_cutmva->Divide(hmcenv5142[0][0]);
    hefficiency_v5142_cutmva->Scale(100.);
    
    TH1F* hefficiency_v5142_cutnom = hmcenv5142[2][0]->Clone("hefficiency_v5142_cutnom");
    hefficiency_v5142_cutnom->Divide(hmcenv5142[0][0]);
    hefficiency_v5142_cutnom->Scale(100.);
    
    
    hefficiency_cutnom->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutnom->GetYaxis()->SetTitle("Detection efficiency (%)");
    hefficiency_cutnom->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutnom->GetYaxis()->SetRangeUser(0,effmax);
    
    //plot3histdata(hefficiency_cutmva_data,"Data",hefficiency_cutmva,"NEUT",hefficiency_genie_cutmva,"GENIE",subname+varname+"deteffdata_mva",0.6,0.6);
    //plot3histdata(hefficiency_cutnom_data,"Data",hefficiency_cutnom,"NEUT",hefficiency_genie_cutnom,"GENIE",subname+varname+"deteffdata_nom",0.6,0.6);
     TString savename1 =subname+varname+"deteffdata_mva";
     plot4hist_style4(false, hefficiency_cutmva_data,"Data", hefficiency_cutmva,"NEUT 5.3.2", hefficiency_v5142_cutmva,"NEUT 5.1.4.2", hefficiency_genie_cutmva,"GENIE", savename1, 0.6,0.6);
    TString savename2 =subname+varname+"deteffdata_nom";
     plot4hist_style4(false, hefficiency_cutnom_data,"Data",hefficiency_cutnom,"NEUT 5.3.2", hefficiency_v5142_cutnom,"NEUT 5.1.4.2",hefficiency_genie_cutnom,"GENIE",savename2,0.6,0.6);
     
    //plot2hist(hefficiency_cutmva,"NEUT",hefficiency_genie_cutmva,"GENIE",subname+varname+"deteffdata_mva",0.6,0.6);
    //plot2hist(hefficiency_cutnom,"NEUT",hefficiency_genie_cutnom,"GENIE",subname+varname+"deteffdata_nom",0.6,0.6); 
    
    
    
}
