{
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil_v532.C");
    
    TString subname = "ana1x_effpur_v532_";
    const int NTOPOLOGY = 3;
    TFile *pfile[NTOPOLOGY];
    TFile *pfilegenie[NTOPOLOGY];
    TFile *pfilev5142[NTOPOLOGY];
    //id 14: is presel + >50
    //id 173: pidfsi>0.05 + >50
    //id 174: muang<15, mucl>0.6, pmucl>0.25
    Int_t topoindex[NTOPOLOGY] = {1,3,29};
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
     double effmax = 100;
     double rangemax = 90;
     int nrebin = 6;
     
    
    /*const int thvariable = 19;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="muangt";
    char *xtitle = "#mu-like track angle (#circ)";
    double effmax = 100;
    double rangemax = 50;
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
    
    
    
    //data
    
    //efficiency & purity
    //purity
    cout<<"TMVA purity "<<hmcen[1][1]->Integral(0,hmcen[1][1]->GetNbinsX()+1)*100./(hmcen[1][0]->Integral(0,hmcen[1][0]->GetNbinsX()+1))<<endl;
    cout<<"NOM purity "<<hmcen[2][1]->Integral(0,hmcen[2][1]->GetNbinsX()+1)*100./hmcen[2][0]->Integral(0,hmcen[2][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hpurity_cutmva = hmcen[1][1]->Clone("hpurity_cutmva");
    hpurity_cutmva->Divide(hmcen[1][0]);
    hpurity_cutmva->Scale(100.);
    
    TH1F* hpurity_cutnom = hmcen[2][1]->Clone("hpurity_cutnom");
    hpurity_cutnom->Divide(hmcen[2][0]);
    hpurity_cutnom->Scale(100.);
    
    hpurity_cutmva->GetXaxis()->SetTitle(xtitle);
    hpurity_cutmva->GetYaxis()->SetTitle("Signal Purity (%)");
    hpurity_cutmva->GetXaxis()->SetRangeUser(0,rangemax);
    hpurity_cutmva->GetYaxis()->SetRangeUser(0,effmax);
    plot2hist(hpurity_cutmva,"MVA method",hpurity_cutnom,"Nominal method",subname+varname+"comp_purity",0.5,0.45);
    
    //efficiency of event selected
    cout<<"FOR NEUT=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcen[1][1]->Integral(0,hmcen[1][1]->GetNbinsX()+1)*100./hmcen[0][1]->Integral(0,hmcen[0][1]->GetNbinsX()+1)<<endl;
    
    cout<<"NOM efficiency "<<hmcen[2][1]->Integral(0,hmcen[2][1]->GetNbinsX()+1)*100./hmcen[0][1]->Integral(0,hmcen[0][1]->GetNbinsX()+1)<<endl;
    
    cout<<"FOR GENIE=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcengenie[1][1]->Integral(0,hmcengenie[1][1]->GetNbinsX()+1)*100./hmcengenie[0][1]->Integral(0,hmcengenie[0][1]->GetNbinsX()+1)<<endl;
    
    cout<<"NOM efficiency "<<hmcengenie[2][1]->Integral(0,hmcengenie[2][1]->GetNbinsX()+1)*100./hmcengenie[0][1]->Integral(0,hmcengenie[0][1]->GetNbinsX()+1)<<endl;
    
    cout<<"FOR NEUT 5.1.4.2=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcenv5142[1][1]->Integral(0,hmcenv5142[1][1]->GetNbinsX()+1)*100./hmcenv5142[0][1]->Integral(0,hmcenv5142[0][1]->GetNbinsX()+1)<<endl;
    
    cout<<"NOM efficiency "<<hmcenv5142[2][1]->Integral(0,hmcenv5142[2][1]->GetNbinsX()+1)*100./hmcenv5142[0][1]->Integral(0,hmcenv5142[0][1]->GetNbinsX()+1)<<endl;
    
    //neut 5.3.2
    TH1F* hefficiency_cutmva = hmcen[1][1]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmcen[0][1]);
    hefficiency_cutmva->Scale(100.);
    
    TH1F* hefficiency_cutnom = hmcen[2][1]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmcen[0][1]);
    hefficiency_cutnom->Scale(100.);
    
    
    hefficiency_cutmva->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutmva->GetYaxis()->SetTitle("Signal efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,effmax);
    
    //plot2hist(hefficiency_cutmva,"MVA method",hefficiency_cutnom,"Nominal method",subname+varname+"comp_efficiency",0.55,0.6);
    
    
    //genie
    TH1F* hefficiency_genie_cutmva = hmcengenie[1][1]->Clone("hefficiency_genie_cutmva");
     hefficiency_genie_cutmva->Divide(hmcengenie[0][1]);
     hefficiency_genie_cutmva->Scale(100.);
     
     TH1F* hefficiency_genie_cutnom = hmcengenie[2][1]->Clone("hefficiency_genie_cutnom");
     hefficiency_genie_cutnom->Divide(hmcengenie[0][1]);
     hefficiency_genie_cutnom->Scale(100.);
     
     //neut 5.1.4.2
     TH1F* hefficiency_v5142_cutmva = hmcenv5142[1][1]->Clone("hefficiency_v5142_cutmva");
     hefficiency_v5142_cutmva->Divide(hmcenv5142[0][1]);
     hefficiency_v5142_cutmva->Scale(100.);
     
     TH1F* hefficiency_v5142_cutnom = hmcenv5142[2][1]->Clone("hefficiency_v5142_cutnom");
     hefficiency_v5142_cutnom->Divide(hmcenv5142[0][1]);
     hefficiency_v5142_cutnom->Scale(100.);
     
     
     hefficiency_cutnom->GetXaxis()->SetTitle(xtitle);
     hefficiency_cutnom->GetYaxis()->SetTitle("Signal efficiency (%)");
     hefficiency_cutnom->GetXaxis()->SetRangeUser(0,rangemax);
     hefficiency_cutnom->GetYaxis()->SetRangeUser(0,effmax);
     
    plot3histStyle1(false,hefficiency_cutmva,"NEUT 5.3.2",hefficiency_v5142_cutmva,"NEUT 5.1.4.2",hefficiency_genie_cutmva,"GENIE",subname+varname+"comp3mva_efficiency",0.55,0.6);
    
    plot3histStyle1(false,hefficiency_cutnom,"NEUT 5.3.2",hefficiency_v5142_cutnom,"NEUT 5.1.4.2",hefficiency_genie_cutnom,"GENIE",subname+varname+"comp3nom_efficiency",0.55,0.6);
    
    
}
