{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    //TFile *pfile = new TFile("../outputs/optimizeCutFSI.root");
    //TString subname = "optimizeCutFSI";
    TFile *pfile = new TFile("../outputs/optimizeCutFSI_FSI_addnue.root");
    TString subname = "optimizeCutFSI_addnue_narrow";
    
    //0 after presel
    const int NTOPOLOGY = 2;
    //signal & background
    const int NINTERACTION = 2;
    TH2F* hmcve[NTOPOLOGY][NINTERACTION];//vertex activity
    TH2F* hmcen[NTOPOLOGY][NINTERACTION];//energy deposition
    TH2F* hmcpidresqe[NTOPOLOGY][NINTERACTION];//energy deposition
    
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcve[itopo][iint] = (TH2F*)pfile->Get(Form("hmcve_topo%d_int%d",itopo,iint));
            hmcen[itopo][iint] = (TH2F*)pfile->Get(Form("hmcen_topo%d_int%d",itopo,iint));
            hmcpidresqe[itopo][iint] = (TH2F*)pfile->Get(Form("hmcpidresqe_topo%d_int%d",itopo,iint));
            
        }
    }
    //firstcut
    hmcen[0][0]->GetXaxis()->SetTitle("Energy deposition at vertex (MeV)");
    hmcen[0][0]->GetYaxis()->SetTitle("Discriminant parameter (COH)");
    hmcen[0][0]->GetYaxis()->SetRangeUser(-1.0,0.5);
    hmcen[0][1]->GetYaxis()->SetRangeUser(-1.0,0.5);
    optimize2dcut(hmcen[0][0],hmcen[0][1],subname,true);
    
    //secondcut
    //hmcpidresqe[1][0]->GetXaxis()->SetTitle("Discriminant para. (CCQE + FSI)");
    //hmcpidresqe[1][0]->GetYaxis()->SetTitle("Discriminant para. (RES + FSI)");
    //optimize2dcut(hmcpidresqe[1][0],hmcpidresqe[1][1],"optimizeCutFSI_addpid",true);
    
}