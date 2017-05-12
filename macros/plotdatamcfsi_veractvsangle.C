{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    
    

    TString subname = "veractvsangle";
    TFile *pfile = new TFile("../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x.root");

    
    
    
    const int NVARIABLES = 42;//all variables//update to convert vertex activity
    const int NTOPOLOGY = 35;//for sam4testv3, muon cl>0.6, pion cl>0.25, proton <0.05
    //0 all, 1: cc1picoh, 2 ccqe, 3: cc 1pi, 4: cc other , 5nc
    //6 numubar, 7 nue, 8 ingrid , 9, wall, 10 genie
    const int NINTERACTION = 10;
    
    char* atitle[NVARIABLES];
    atitle[0] = "Number of tracks";
    atitle[1] = "Number of INGRID-penetrated track";
    atitle[2] = "1st track angle";
    atitle[3] = "#pi-like track angle";
    atitle[4] = "Mean of #pi-like light yield";
    atitle[5] = "Mean of 1st light yield";
    atitle[6] = "Opening angle btw 2 tracks";
    atitle[7] = "Coplanarity btw 2 tracks";
    atitle[8] = "Norm";
    atitle[9] = "totcrsne";
    
    atitle[10] = "inttype";
    atitle[11] = "True neutrino energy (GeV)";
    atitle[12] = "1st track contained";
    atitle[13] = "#pi-like track contained";
    atitle[14] = "1st track PDG";
    atitle[15] = "#pi-like track PDG";
    atitle[16] = "Vertex activity";
    atitle[17] = "1st track confidence level";
    atitle[18] = "#pi-like track confidence level";
    atitle[19] = "1st track angle";
    atitle[20] = "#pi-like track angle";
    //5/6
    //atitle[19] = "First track angle";
    //atitle[20] = "Second track angle";
    atitle[21] = "xnu";
    atitle[22] = "ynu";
    atitle[23] = "znu";
    atitle[24] = "exptime";
    atitle[25] = "startxch";
    atitle[26] = "startych";
    atitle[27] = "startxpln";
    atitle[28] = "startypln";
    atitle[29] = "1st range";
    
    atitle[30] = "pene";
    atitle[31] = "#pi-like range";
    atitle[32] = "ppene";
    atitle[33] = "Discriminant parameter (COH)";
    atitle[34] = "Discriminant parameter (RES)";
    atitle[35] = "Discriminant parameter (CCQE)";
    atitle[36] = "Energy deposit at vertex (MeV)";
    atitle[37] = "Reconstructed Q^{2} (GeV^{2})";
    atitle[38] = "Reconstructed momentum (GeV))";
    
    atitle[39] = "Discriminant parameter (COH FSI)";
    atitle[40] = "Discriminant parameter (RES FSI)";
    atitle[41] = "Discriminant parameter (CCQE FSI)";
    
    
    
    
    
    //newadd 2-dim
    TH2F* hdtveractvsmuang[NTOPOLOGY];
    TH2F* hdtveractvspang[NTOPOLOGY];
    
    TH2F* hmcveractvsmuang[NTOPOLOGY][NINTERACTION];
    TH2F* hmcveractvspang[NTOPOLOGY][NINTERACTION];
    
    TH2F* hsubveractvsmuang[NTOPOLOGY];
    TH2F* hsubveractvspang[NTOPOLOGY];
     
    TH2F* hdtveractvsstartxpln[NTOPOLOGY];
    TH2F* hdtveractvsstartypln[NTOPOLOGY];
    
    TH2F* hmcveractvsstartxpln[NTOPOLOGY][NINTERACTION];
    TH2F* hmcveractvsstartypln[NTOPOLOGY][NINTERACTION];
    
    TH2F* hsubveractvsstartxpln[NTOPOLOGY];
    TH2F* hsubveractvsstartypln[NTOPOLOGY];
    
    double pidcut = -0.125;
    double pidcutlong = 0.1;
    double veractcut = 475*7.6634e-2;
    double veractcutlong = 5;
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
    
        hdtveractvsmuang[itopo] = (TH2F*)pfile->Get(Form("hdtveractvsmuang_topo%d",itopo));
        hdtveractvspang[itopo] = (TH2F*)pfile->Get(Form("hdtveractvspang_topo%d",itopo));
        
        hdtveractvsstartxpln[itopo] = (TH2F*)pfile->Get(Form("hdtveractvsstartxpln_topo%d",itopo));
    hdtveractvsstartypln[itopo] = (TH2F*)pfile->Get(Form("hdtveractvsstartypln_topo%d",itopo));
        for (Int_t iint=0; iint<NINTERACTION; ++iint) {
            hmcveractvsmuang[itopo][iint] = (TH2F*)pfile->Get(Form("hmcveractvsmuang_topo%d_int%d",itopo,iint));
            hmcveractvspang[itopo][iint] = (TH2F*)pfile->Get(Form("hmcveractvspang_topo%d_int%d",itopo,iint));
            hmcveractvsstartxpln[itopo][iint] = (TH2F*)pfile->Get(Form("hmcveractvsstartxpln_topo%d_int%d",itopo,iint));
        hmcveractvsstartypln[itopo][iint] = (TH2F*)pfile->Get(Form("hmcveractvsstartypln_topo%d_int%d",itopo,iint));
        }
        
        new TCanvas;
        
    
    }//end itopo
    Int_t ci = TColor::GetColor("#000000");
    Int_t cimc = TColor::GetColor("#D55E00");
    //plot
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        hdtveractvsmuang[itopo]->Rebin2D(3,4);
        hmcveractvsmuang[itopo][0]->Rebin2D(3,4);
        
        hdtveractvspang[itopo]->Rebin2D(3,4);
        hmcveractvspang[itopo][0]->Rebin2D(3,4);
        //dt veract vs muangle
        new TCanvas;
        hdtveractvsmuang[itopo]->GetXaxis()->SetTitle("1st track angle");
        hdtveractvsmuang[itopo]->GetXaxis()->SetRangeUser(0,90);
        hdtveractvsmuang[itopo]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
        hdtveractvsmuang[itopo]->GetYaxis()->SetRangeUser(0,200);
        plot2dhist(hdtveractvsmuang[itopo],subname+Form("_dt_mu_sam%d",itopo));
        
        //dt veract vs piangle
        new TCanvas;
        hdtveractvspang[itopo]->GetXaxis()->SetTitle("2nd track angle");
        hdtveractvspang[itopo]->GetXaxis()->SetRangeUser(0,90);
        hdtveractvspang[itopo]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
        hdtveractvspang[itopo]->GetYaxis()->SetRangeUser(0,200);
        plot2dhist(hdtveractvspang[itopo],subname+Form("_dt_2ntrk_sam%d",itopo));
        
        //mc veract vs muang
        new TCanvas;
        hmcveractvsmuang[itopo][0]->GetXaxis()->SetTitle("1st track angle");
        hmcveractvsmuang[itopo][0]->GetXaxis()->SetRangeUser(0,90);
        hmcveractvsmuang[itopo][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
        hmcveractvsmuang[itopo][0]->GetYaxis()->SetRangeUser(0,200);
        plot2dhist(hmcveractvsmuang[itopo][0],subname+Form("_mc_mu_sam%d",itopo));
        
        //mc veract vs pang
        new TCanvas;
        hmcveractvspang[itopo][0]->GetXaxis()->SetTitle("2nd track angle");
        hmcveractvspang[itopo][0]->GetXaxis()->SetRangeUser(0,90);
        hmcveractvspang[itopo][0]->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
        hmcveractvspang[itopo][0]->GetYaxis()->SetRangeUser(0,200);
        plot2dhist(hmcveractvspang[itopo][0],subname+Form("_mc_2ntrk_sam%d",itopo));
        
        
        
        
        TProfile *hprofile = (TProfile*)hdtveractvsmuang[itopo]->ProfileX();
        hprofile->SetLineWidth(3);
        hprofile->SetLineColor(ci);
        hprofile->SetMarkerColor(ci);
        
        TProfile *hprofilemc = (TProfile*)hmcveractvsmuang[itopo][0]->ProfileX();
        hprofilemc->SetLineWidth(3);
        hprofilemc->SetLineColor(cimc);
        hprofilemc->SetMarkerColor(cimc);
        
        hprofile->GetXaxis()->SetTitle("1st track angle");
        hprofile->GetXaxis()->SetRangeUser(0,90);
        hprofile->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
        hprofile->GetYaxis()->SetRangeUser(0,200);
        
        new TCanvas;
        titleStyle(hprofile);
        hprofile->Draw();
        hprofilemc->Draw("same");
        
        TLegend* leg0 = new TLegend(.4, .7, 0.6, .86);
        //leg0->SetMargin(0.1);
        leg0->SetFillStyle(0);
        leg0->SetBorderSize(0);
        leg0->SetTextSize(18);
        leg0->SetTextFont(43);
        leg0->AddEntry(hprofile, "Data", "epl");
        leg0->AddEntry(hprofilemc, "MC", "epl");
        leg0->SetFillStyle(0);
        leg0->Draw();
        
        gPad->Print("plots/"+subname+Form("_mu_dtvsmc_sam%d.eps",itopo));
        
        TProfile *hprofile2trk = (TProfile*)hdtveractvspang[itopo]->ProfileX();
        hprofile2trk->SetLineWidth(3);
        hprofile2trk->SetLineColor(ci);
        hprofile2trk->SetMarkerColor(ci);
        
        TProfile *hprofile2trkmc = (TProfile*)hmcveractvspang[itopo][0]->ProfileX();
        hprofile2trkmc->SetLineWidth(3);
        hprofile2trkmc->SetLineColor(cimc);
        hprofile2trkmc->SetMarkerColor(cimc);
        
        hprofile2trk->GetXaxis()->SetTitle("2nd track angle");
        hprofile2trk->GetXaxis()->SetRangeUser(0,90);
        hprofile2trk->GetYaxis()->SetTitle("Energy deposit at vertex (MeV)");
        hprofile2trk->GetYaxis()->SetRangeUser(0,200);
        
        new TCanvas;
        titleStyle(hprofile2trk);
        hprofile2trk->Draw();
        hprofile2trkmc->Draw("same");
        leg0->Draw();
        
        gPad->Print("plots/"+subname+Form("_2ndtrk_dtvsmc_sam%d.eps",itopo));
    }
    
    //subraction two dimension
    float npot = 6.04193507503274721e20;
    int   nmc  = 3950;
    float mcpotreweight = npot/(nmc*1e21);
    for (Int_t itopo=0; itopo<NTOPOLOGY; ++itopo) {
        hsubveractvsmuang[itopo] = (TH2F*)hmcveractvsmuang[itopo][0]->Clone(Form("hsubveractvsmuang_sam%d",itopo));
        hsubveractvspang[itopo] = (TH2F*)hmcveractvspang[itopo][0]->Clone(Form("hmcveractvspang_sam%d",itopo));
        hsubveractvsstartxpln[itopo] = (TH2F*)hmcveractvsstartxpln[itopo][0]->Clone(Form("hsubveractvsstartxpln_sam%d",itopo));
    hsubveractvsstartypln[itopo] = (TH2F*)hmcveractvsstartypln[itopo][0]->Clone(Form("hmcveractvsstartypln_sam%d",itopo));
        //hsubveractvsmuang[itopo]->Scale(mcpotreweight);
        //hsubveractvspang[itopo]->Scale(mcpotreweight);
        
        Int_t nx = hsubveractvsmuang[itopo] -> GetNbinsX()+1;
        Int_t ny = hsubveractvsmuang[itopo] -> GetNbinsY()+1;
        for (int ix = 1; ix <= nx; ix++){
            for (int iy = 1; iy <= ny; iy++){
                double fracmu=0;
                if(hsubveractvsmuang[itopo]->GetBinContent(ix,iy)>0) fracmu= -1*(hsubveractvsmuang[itopo]->GetBinContent(ix,iy)*mcpotreweight-hdtveractvsmuang[itopo]->GetBinContent(ix,iy))*100/(hsubveractvsmuang[itopo]->GetBinContent(ix,iy)*mcpotreweight);
                double fracpi=0;
                if(hsubveractvspang[itopo]->GetBinContent(ix,iy)>0) fracpi= -1*(hsubveractvspang[itopo]->GetBinContent(ix,iy)*mcpotreweight-hdtveractvspang[itopo]->GetBinContent(ix,iy))*100/(hsubveractvspang[itopo]->GetBinContent(ix,iy)*mcpotreweight);
                //cout<<"mc "<<hsubveractvsmuang[itopo]->GetBinContent(ix,iy)*mcpotreweight<<"data "<<hdtveractvsmuang[itopo]->GetBinContent(ix,iy)<< "diff "<<fracmu<<endl;
                if(fracmu>100) fracmu = 100;
                if(fracmu<-100) fracmu = -100;
                if(fracpi>100) fracpi = 100;
                if(fracpi<-100) fracpi = -100;
                hsubveractvsmuang[itopo]->SetBinContent(ix,iy,fracmu);
                hsubveractvspang[itopo]->SetBinContent(ix,iy,fracpi);
                hsubveractvsmuang[itopo]->GetZaxis()->SetRangeUser(-100,100);
                hsubveractvspang[itopo]->GetZaxis()->SetRangeUser(-100,100);
            }
        }
        new TCanvas;
        hsubveractvsmuang[itopo]->Draw("colz");
        gPad->Print("plots/"+subname+Form("_sub_mu_sam%d.eps",itopo));
        
        new TCanvas;
        hsubveractvspang[itopo]->Draw("colz");
        gPad->Print("plots/"+subname+Form("_sub_2ndtrk_sam%d.eps",itopo));
        
        

       Int_t nx = hsubveractvsstartxpln[itopo] -> GetNbinsX()+1;
    Int_t ny = hsubveractvsstartxpln[itopo] -> GetNbinsY()+1;
    for (int ix = 1; ix <= nx; ix++){
        for (int iy = 1; iy <= ny; iy++){
            double fracmu=0;
            if(hsubveractvsstartxpln[itopo]->GetBinContent(ix,iy)>0) fracmu= -1*(hsubveractvsstartxpln[itopo]->GetBinContent(ix,iy)*mcpotreweight-hdtveractvsstartxpln[itopo]->GetBinContent(ix,iy))*100/(hsubveractvsstartxpln[itopo]->GetBinContent(ix,iy)*mcpotreweight);
            double fracpi=0;
            if(hsubveractvsstartypln[itopo]->GetBinContent(ix,iy)>0) fracpi= -1*(hsubveractvsstartypln[itopo]->GetBinContent(ix,iy)*mcpotreweight-hdtveractvsstartypln[itopo]->GetBinContent(ix,iy))*100/(hsubveractvsstartypln[itopo]->GetBinContent(ix,iy)*mcpotreweight);
            //cout<<"mc "<<hsubveractvsstartxpln[itopo]->GetBinContent(ix,iy)*mcpotreweight<<"data "<<hdtveractvsstartxpln[itopo]->GetBinContent(ix,iy)<< "diff "<<fracmu<<endl;
            if(fracmu>100) fracmu = 100;
            if(fracmu<-100) fracmu = -100;
            if(fracpi>100) fracpi = 100;
            if(fracpi<-100) fracpi = -100;
            hsubveractvsstartxpln[itopo]->SetBinContent(ix,iy,fracmu);
            hsubveractvsstartypln[itopo]->SetBinContent(ix,iy,fracpi);
            hsubveractvsstartxpln[itopo]->GetZaxis()->SetRangeUser(-100,100);
            hsubveractvsstartypln[itopo]->GetZaxis()->SetRangeUser(-100,100);
        }
    }
    new TCanvas;
    hsubveractvsstartxpln[itopo]->Draw("colz");
    gPad->Print("plots/"+subname+Form("_sub_startxpln_sam%d.eps",itopo));
    
    new TCanvas;
    hsubveractvsstartypln[itopo]->Draw("colz");
    gPad->Print("plots/"+subname+Form("_sub_startypln_sam%d.eps",itopo));
    }
    
}
