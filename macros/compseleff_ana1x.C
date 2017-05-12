{
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    /*TString subname = "basicdatamc_official_pidvalidate_noveract_";    
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_4pidvalidate.root");
    TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_4validate.root");
    */
    TString subname = "compseleff_m2trk_";
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_ana1.root");
    TFile *pfilegenie = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_ana1.root");
    //TFile *pfile = new TFile("../outputs/basicHisto_genie_datamcfsi_finalcomb_sam4testv2_addnue_4validate.root");
    //TFile *pfile = new TFile("../outputs/basicHisto_datamc_genie.root");
    const int NVARIABLES = 42;//all variables//update to convert vertex activity
    //0 all, 1, preselection, 2, with PID cut, 3 sig, 4 cr1, 5 cr2a, 6 cr2b, 7 cr2c
    // 8 more than 2trk; 9 ccq with one track;
    const int NTOPOLOGY = 27;
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    /*const int thvariable = 20;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="pangt";
    char *xtitle = "#pi-like track angle (#circ)";
    double effmax = 15;
    double rangemax = 90;
    int nrebin = 1;*/
    
    /*const int thvariable = 19;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="muangt";
    char *xtitle = "#mu-like track angle (#circ)";
    double effmax = 25;
    double rangemax = 30;
    int nrebin = 1;*/

    const int thvariable = 36;// 2 muang, 3pang, 19 muang_t, 20 pang_t to beam, 11 nuE,
    TString varname ="veract";
    char *xtitle = "Energy deposit at vertex (MeV)";
    double effmax = 15;
    double rangemax = 300;
    int nrebin = 2;

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
    
 
    
    //efficiency of event selected
    cout<<"FOR NEUT=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcen[17][0]->Integral(0,hmcen[17][0]->GetNbinsX()+1)*100./hmcen[23][0]->Integral(0,hmcen[23][0]->GetNbinsX()+1)<<endl;
    
    //cout<<"NOM efficiency "<<hmcen[21][0]->Integral(0,hmcen[21][0]->GetNbinsX()+1)*100./hmcen[23][0]->Integral(0,hmcen[23][0]->GetNbinsX()+1)<<endl;
    
    
    
    cout<<"FOR GENIE=================>"<<endl;
    cout<<"TMVA efficiency "<<hmcengenie[17][0]->Integral(0,hmcengenie[17][0]->GetNbinsX()+1)*100./hmcengenie[23][0]->Integral(0,hmcengenie[23][0]->GetNbinsX()+1)<<endl;
    
    //cout<<"NOM efficiency "<<hmcengenie[21][0]->Integral(0,hmcengenie[21][0]->GetNbinsX()+1)*100./hmcengenie[23][0]->Integral(0,hmcengenie[23][0]->GetNbinsX()+1)<<endl;
    
    TH1F* hefficiency_cutmva = hmcen[17][0]->Clone("hefficiency_cutmva");
    hefficiency_cutmva->Divide(hmcen[23][0]);
    hefficiency_cutmva->Scale(100.);
    
    /*TH1F* hefficiency_cutnom = hmcen[21][0]->Clone("hefficiency_cutnom");
    hefficiency_cutnom->Divide(hmcen[23][0]);
    hefficiency_cutnom->Scale(100.);*/
    
    hefficiency_cutmva->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutmva->GetYaxis()->SetTitle("Selection efficiency (%)");
    hefficiency_cutmva->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutmva->GetYaxis()->SetRangeUser(0,effmax);
    
    TH1F* hefficiency_genie_cutmva = hmcengenie[17][0]->Clone("hefficiency_genie_cutmva");
    hefficiency_genie_cutmva->Divide(hmcengenie[23][0]);
    hefficiency_genie_cutmva->Scale(100.);
    
    /*TH1F* hefficiency_genie_cutnom = hmcengenie[21][0]->Clone("hefficiency_genie_cutnom");
    hefficiency_genie_cutnom->Divide(hmcengenie[23][0]);
    hefficiency_genie_cutnom->Scale(100.);
    
    hefficiency_cutnom->GetXaxis()->SetTitle(xtitle);
    hefficiency_cutnom->GetYaxis()->SetTitle("Selection efficiency (%)");
    hefficiency_cutnom->GetXaxis()->SetRangeUser(0,rangemax);
    hefficiency_cutnom->GetYaxis()->SetRangeUser(0,effmax);*/
    
        
    plot2hist(hefficiency_cutmva,"NEUT",hefficiency_genie_cutmva,"GENIE",subname+varname+"mva",0.6,0.6);
    //plot2hist(hefficiency_cutnom,"NEUT",hefficiency_genie_cutnom,"GENIE",subname+varname+"seleff_nom",0.6,0.6);

    
    
   }
