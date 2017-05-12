{
    gROOT->ProcessLine(".x /home/t2k/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/t2k/cvson/basicPlotUtil.C");
    
    //TFile *pfile = new TFile("../outputs/mcdata_sample.root");
    TFile *pfile = new TFile("../outputs/mcdata_sample_newbin.root");
    string tag = "nominal";
    const int nreac = 9;//10;
    const int nsample = 7;
    const char *m_name[] = {"SIG", "CRI", "CRIIA", "CRIIB", "CRIIC", "More2trk", "Onetrk"};
    const char *m_namelong[] = {"Signal", "Control I", "Control IIA", "Control IIB", "Control IIC", "> two tracks", "One track"};
    //const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall","genie"};
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall"};
    const char *m_namerainbowcolor[] = {"#7C7B42", "#BF55C4", "#C25B79", "#9BB9BA", "#A5CE44", "#C86134", "#4C373F", "#7ACD8A","#7A76BB"};
    const char *m_color4merge[] = {"#4F4737", "#B74E72", "#7E81B0", "#95C34D", "#C56E3B", "#95C4A8", "#AD5DC9"};

    TH1D *henu_true[nsample][nreac];//newadd
    TH1D *henu_rec[nsample][nreac];
    TH1D *hpmu_rec[nsample][nreac];
    TH1D *hcth_rec[nsample][nreac];
    TH2D *hpmucth_rec[nsample][nreac];
    TH1D *hpmu_true[nsample][nreac];
    TH1D *hcth_true[nsample][nreac];
    TH1D *hccqebin_true[nsample][nreac];
    TH1D *hccqebin_rec[nsample][nreac];
    TH1D *hccqebin_rec_data[nsample];
    
    
    for(int isam=0;isam<nsample;isam++){
        hccqebin_rec_data[isam]= (TH1D*)pfile->Get(Form("%s_data",m_name[isam]));
        for(int ireac=0;ireac<nreac;ireac++)
        {
            //newadd
            henu_true[isam][ireac] = (TH1D*)pfile->Get(Form("%s_TrueEnu_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            
            henu_rec[isam][ireac] = (TH1D*)pfile->Get(Form("%s_RecEnu_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            
            hpmu_rec[isam][ireac] = (TH1D*)pfile->Get(Form("%s_RecPmu_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            
            hcth_rec[isam][ireac] = (TH1D*)pfile->Get(Form("%s_RecCTh_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            
            hpmucth_rec[isam][ireac] = (TH2D*)pfile->Get(Form("%s_RecPmuCTh_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            
            hpmu_true[isam][ireac] = (TH1D*)pfile->Get(Form("%s_TruePmu_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            
            hcth_true[isam][ireac] = (TH1D*)pfile->Get(Form("%s_TrueCTh_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            
            hccqebin_true[isam][ireac] = (TH1D*)pfile->Get(Form("%s_ccqebins_true_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            
            hccqebin_rec[isam][ireac] = (TH1D*)pfile->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tag.c_str()));
        }//end for ireac
        
    }//end for isam
    //Dummy TLegend
    new TCanvas;
    TLegend* leg0 = new TLegend(.22, .32, 0.45, .85);
    //      leg->AddEntry((TObject*)0, "Energy estimator", "");
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.045);
    
    leg0->AddEntry(hccqebin_rec_data[0], "Data","lp");
    for (int ireac=0;ireac<nreac;ireac++){
        leg0->AddEntry(henu_true[0][ireac], names[ireac],"lf");
        
    }
    leg0->SetFillStyle(0);
    
    leg0->Draw();
    gPad->Print("plots/newbin_dummyLegend.eps");
    
    THStack* fHstach_enu_true[nsample];//    = new THStack("fHstach_enu_true","fHstach_enu_true");
    THStack* fHstach_enu_rec[nsample];//    = new THStack("fHstach_enu_rec","fHstach_enu_rec");
    THStack* fHstach_pmu_rec[nsample];//    = new THStack("fHstach_pmu_rec","fHstach_pmu_rec");
    THStack* fHstach_costh_rec[nsample];//    = new THStack("fHstach_costh_rec","fHstach_costh_rec");
    THStack* fHstach_pmu_true[nsample];//    = new THStack("fHstach_pmu_true","fHstach_pmu_true");
    THStack* fHstach_costh_true[nsample];//    = new THStack("fHstach_costh_true","fHstach_costh_true");
    THStack* fHstach_ccqebin_true[nsample];//    = new THStack("fHstach_ccqebin_true","fHstach_ccqebin_true");
    THStack* fHstach_ccqebin_rec[nsample];//    = new THStack("fHstach_ccqebin_rec","fHstach_ccqebin_rec");
    Int_t icolor;
    for(int isam=0;isam<nsample;isam++){
        fHstach_enu_true[isam]= new THStack(Form("fHstach_enu_true_sam%d",isam),Form("fHstach_enu_true_sam%d",isam));
        fHstach_enu_rec[isam]= new THStack(Form("fHstach_enu_rec_sam%d",isam),Form("fHstach_enu_rec_sam%d",isam));
        fHstach_pmu_rec[isam]= new THStack(Form("fHstach_pmu_rec_sam%d",isam),Form("fHstach_pmu_rec_sam%d",isam));
        fHstach_costh_rec[isam]= new THStack(Form("fHstach_costh_rec_sam%d",isam),Form("fHstach_costh_rec_sam%d",isam));
        fHstach_pmu_true[isam]= new THStack(Form("fHstach_pmu_true_sam%d",isam),Form("fHstach_pmu_true_sam%d",isam));
        fHstach_costh_true[isam]= new THStack(Form("fHstach_costh_true_sam%d",isam),Form("fHstach_costh_true_sam%d",isam));
        fHstach_ccqebin_true[isam]= new THStack(Form("fHstach_ccqebin_true_sam%d",isam),Form("fHstach_ccqebin_true_sam%d",isam));
        fHstach_ccqebin_rec[isam]= new THStack(Form("fHstach_ccqebin_rec_sam%d",isam),Form("fHstach_ccqebin_rec_sam%d",isam));
        for(int ireac=nreac-1;ireac>=0;ireac--){
            icolor = TColor::GetColor(m_namerainbowcolor[ireac]);
            
            henu_true[isam][ireac]->SetLineColor(icolor);
            henu_rec[isam][ireac]->SetLineColor(icolor);
            hpmu_rec[isam][ireac]->SetLineColor(icolor);
            hcth_rec[isam][ireac]->SetLineColor(icolor);
            hpmu_true[isam][ireac]->SetLineColor(icolor);
            hcth_true[isam][ireac]->SetLineColor(icolor);
            hccqebin_true[isam][ireac]->SetLineColor(icolor);
            hccqebin_rec[isam][ireac]->SetLineColor(icolor);
            
            henu_true[isam][ireac]->SetFillColor(icolor);
            henu_rec[isam][ireac]->SetFillColor(icolor);
            hpmu_rec[isam][ireac]->SetFillColor(icolor);
            hcth_rec[isam][ireac]->SetFillColor(icolor);
            hpmu_true[isam][ireac]->SetFillColor(icolor);
            hcth_true[isam][ireac]->SetFillColor(icolor);
            hccqebin_true[isam][ireac]->SetFillColor(icolor);
            hccqebin_rec[isam][ireac]->SetFillColor(icolor);
            
            fHstach_enu_true[isam]->Add(henu_true[isam][ireac]);
            fHstach_enu_rec[isam]->Add(henu_rec[isam][ireac]);
            fHstach_pmu_rec[isam]->Add(hpmu_rec[isam][ireac]);
            fHstach_costh_rec[isam]->Add(hcth_rec[isam][ireac]);
            fHstach_pmu_true[isam]->Add(hpmu_true[isam][ireac]);
            fHstach_costh_true[isam]->Add(hcth_true[isam][ireac]);
            fHstach_ccqebin_true[isam]->Add(hccqebin_true[isam][ireac]);
            fHstach_ccqebin_rec[isam]->Add(hccqebin_rec[isam][ireac]);
            
        }
        TLatex* tlx=new TLatex(0.55, 0.85,Form("Sample: %s",m_namelong[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        new TCanvas;
        
        
        fHstach_enu_true[isam]->Draw();
        fHstach_enu_true[isam]->GetXaxis()->SetTitle("True Energy (GeV)");
        fHstach_enu_true[isam]->GetYaxis()->SetTitle("Number of Events");
        titleStyle(fHstach_enu_true[isam]);
        
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hstach_enu_true_sam%d.eps",isam));
        
        new TCanvas;
        fHstach_enu_rec[isam]->Draw();
        fHstach_enu_rec[isam]->GetXaxis()->SetTitle("Reconstructed Energy (GeV)");
        fHstach_enu_rec[isam]->GetYaxis()->SetTitle("Number of Events");
        titleStyle(fHstach_enu_rec[isam]);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hstach_enu_rec_sam%d.eps",isam));
        
        new TCanvas;
        fHstach_pmu_rec[isam]->Draw();
        fHstach_pmu_rec[isam]->GetXaxis()->SetTitle("Reconstructed muon momentum (GeV)");
        fHstach_pmu_rec[isam]->GetYaxis()->SetTitle("Number of Events");
        fHstach_pmu_rec[isam]->GetXaxis()->SetRangeUser(0,2);
        titleStyle(fHstach_pmu_rec[isam]);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hstach_pmu_rec_sam%d.eps",isam));
        
        new TCanvas;
        fHstach_costh_rec[isam]->Draw();
        fHstach_costh_rec[isam]->GetXaxis()->SetTitle("Reconstructed cos(#theta)");
        fHstach_costh_rec[isam]->GetYaxis()->SetTitle("Number of Events");
        titleStyle(fHstach_costh_rec[isam]);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hstach_costh_rec_sam%d.eps",isam));
        
        new TCanvas;
        fHstach_pmu_true[isam]->Draw();
        fHstach_pmu_true[isam]->GetXaxis()->SetTitle("True muon momentum (GeV)");
        fHstach_pmu_true[isam]->GetYaxis()->SetTitle("Number of Events");
        titleStyle(fHstach_pmu_true[isam]);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hstach_pmu_true_sam%d.eps",isam));
        
        new TCanvas;
        fHstach_costh_true[isam]->Draw();
        fHstach_costh_true[isam]->GetXaxis()->SetTitle("True cos(#theta)");
        fHstach_costh_true[isam]->GetYaxis()->SetTitle("Number of Events");
        titleStyle(fHstach_costh_true[isam]);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hstach_costh_true_sam%d.eps",isam));
        
        
        new TCanvas;
        fHstach_ccqebin_true[isam]->Draw();
        fHstach_ccqebin_true[isam]->GetXaxis()->SetTitle("True p-cos(#theta) bins");
        fHstach_ccqebin_true[isam]->GetYaxis()->SetTitle("Number of Events");
        titleStyle(fHstach_ccqebin_true[isam]);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hstach_ccqebin_true_sam%d.eps",isam));
        
        new TCanvas;
        fHstach_ccqebin_rec[isam]->Draw();
        fHstach_ccqebin_rec[isam]->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
        fHstach_ccqebin_rec[isam]->GetYaxis()->SetTitle("Number of Events");
        titleStyle(fHstach_ccqebin_rec[isam]);
        fHstach_ccqebin_rec[isam]->SetMaximum(fHstach_ccqebin_rec[isam]->GetMaximum()*1.2);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hstach_ccqebin_rec_sam%d.eps",isam));
        
        new TCanvas;
        fHstach_ccqebin_rec[isam]->Draw();
        fHstach_ccqebin_rec[isam]->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
        fHstach_ccqebin_rec[isam]->GetYaxis()->SetTitle("Number of Events");
        if(fHstach_ccqebin_rec[isam]->GetMaximum()> hccqebin_rec_data[isam]->GetMaximum())fHstach_ccqebin_rec[isam]->SetMaximum(fHstach_ccqebin_rec[isam]->GetMaximum()*1.2);
        else fHstach_ccqebin_rec[isam]->SetMaximum(hccqebin_rec_data[isam]->GetMaximum()*1.5);
        
        titleStyle(fHstach_ccqebin_rec[isam]);
        hccqebin_rec_data[isam]->SetMarkerStyle(8);
        hccqebin_rec_data[isam]->SetMarkerSize(1.1);
        hccqebin_rec_data[isam]->Draw("ep same");
        tlx->Draw();
        //leg0->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/newbin_hdatamc_ccqebin_rec_sam%d.eps",isam));
        
    }
    

    

    
    
}