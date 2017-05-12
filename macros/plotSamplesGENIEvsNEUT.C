{
    gROOT->ProcessLine(".x ../..//rootlogon.C");
    gROOT->ProcessLine(".L ../..//basicPlotUtil.C");
    
    TFile *pfile = new TFile("../outputs/genievsneut_sample_newbin2_fsicomb.root");
    TString subsubname = "genievsneut";
    string tag = "nominal";
    const int nreac = 8;//10;
    const int nsample = 4;
    const char *m_name[] = {"SIG", "CRI", "CRII", "CRIII"};
    const char *m_namelong[] = {"SIG", "CRI", "CRII", "CRIII"};
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid"};
    const char *m_color4merge[] = {"#4F4737", "#B74E72", "#7E81B0", "#95C34D", "#C56E3B", "#95C4A8", "#AD5DC9"};
        Int_t icolor;
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
    
    TH1D *henu_true_otherbkg[nsample];//newadd
    TH1D *henu_rec_otherbkg[nsample];
    TH1D *hpmu_rec_otherbkg[nsample];
    TH1D *hcth_rec_otherbkg[nsample];
    TH2D *hpmucth_rec_otherbkg[nsample];
    TH1D *hpmu_true_otherbkg[nsample];
    TH1D *hcth_true_otherbkg[nsample];
    TH1D *hccqebin_true_otherbkg[nsample];
    TH1D *hccqebin_rec_otherbkg[nsample];//nc, nue, ingrid, wall
    
    
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
    TLegend* leg0 = new TLegend(.2, .38, 0.45, .9);
    //      leg->AddEntry((TObject*)0, "Energy estimator", "");
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.045);
    
    leg0->AddEntry(hccqebin_rec_data[0], "GENIE MC","lp");
    for (int ireac=0;ireac<nreac;ireac++){
        if(ireac<4 || ireac==5)leg0->AddEntry(henu_true[0][ireac], names[ireac],"lf");
        
    }
    
    leg0->AddEntry(henu_true[0][6], "otherbkg","lf");
    leg0->SetFillStyle(0);
    
    leg0->Draw();
    gPad->Print("plots/newbin2_mergebkg_dummyLegend.eps");
    
    
    //no data
    TLegend* leg0nodt = new TLegend(.2, .38, 0.45, .9);
    //      leg->AddEntry((TObject*)0, "Energy estimator", "");
    leg0nodt->SetFillStyle(0);
    leg0nodt->SetBorderSize(0);
    leg0nodt->SetTextSize(0.045);
    
    for (int ireac=0;ireac<nreac;ireac++){
        if(ireac<4 || ireac==5)leg0nodt->AddEntry(henu_true[0][ireac], names[ireac],"lf");
        
    }
    
    leg0nodt->AddEntry(henu_true[0][6], "otherbkg","lf");
    leg0nodt->SetFillStyle(0);
    
    THStack* fHstach_enu_true[nsample];//    = new THStack("fHstach_enu_true","fHstach_enu_true");
    THStack* fHstach_enu_rec[nsample];//    = new THStack("fHstach_enu_rec","fHstach_enu_rec");
    THStack* fHstach_pmu_rec[nsample];//    = new THStack("fHstach_pmu_rec","fHstach_pmu_rec");
    THStack* fHstach_costh_rec[nsample];//    = new THStack("fHstach_costh_rec","fHstach_costh_rec");
    THStack* fHstach_pmu_true[nsample];//    = new THStack("fHstach_pmu_true","fHstach_pmu_true");
    THStack* fHstach_costh_true[nsample];//    = new THStack("fHstach_costh_true","fHstach_costh_true");
    THStack* fHstach_ccqebin_true[nsample];//    = new THStack("fHstach_ccqebin_true","fHstach_ccqebin_true");
    THStack* fHstach_ccqebin_rec[nsample];//    = new THStack("fHstach_ccqebin_rec","fHstach_ccqebin_rec");

    for(int isam=0;isam<nsample;isam++){
        fHstach_enu_true[isam]= new THStack(Form("fHstach_enu_true_sam%d",isam),Form("fHstach_enu_true_sam%d",isam));
        fHstach_enu_rec[isam]= new THStack(Form("fHstach_enu_rec_sam%d",isam),Form("fHstach_enu_rec_sam%d",isam));
        fHstach_pmu_rec[isam]= new THStack(Form("fHstach_pmu_rec_sam%d",isam),Form("fHstach_pmu_rec_sam%d",isam));
        fHstach_costh_rec[isam]= new THStack(Form("fHstach_costh_rec_sam%d",isam),Form("fHstach_costh_rec_sam%d",isam));
        fHstach_pmu_true[isam]= new THStack(Form("fHstach_pmu_true_sam%d",isam),Form("fHstach_pmu_true_sam%d",isam));
        fHstach_costh_true[isam]= new THStack(Form("fHstach_costh_true_sam%d",isam),Form("fHstach_costh_true_sam%d",isam));
        fHstach_ccqebin_true[isam]= new THStack(Form("fHstach_ccqebin_true_sam%d",isam),Form("fHstach_ccqebin_true_sam%d",isam));
        fHstach_ccqebin_rec[isam]= new THStack(Form("fHstach_ccqebin_rec_sam%d",isam),Form("fHstach_ccqebin_rec_sam%d",isam));
        
        hccqebin_rec_otherbkg[isam] = (TH1D*) hccqebin_rec[isam][4]->Clone(Form("hccqebin_rec_otherbkg_sam%d",isam));
        henu_true_otherbkg[isam] = (TH1D*) henu_true[isam][4]->Clone(Form("henu_true_otherbkg_sam%d",isam));
        henu_rec_otherbkg[isam] = (TH1D*) henu_rec[isam][4]->Clone(Form("henu_rec_otherbkg_sam%d",isam));
        hpmu_rec_otherbkg[isam] = (TH1D*) hpmu_rec[isam][4]->Clone(Form("hpmu_rec_otherbkg_sam%d",isam));
        hcth_rec_otherbkg[isam] = (TH1D*) hcth_rec[isam][4]->Clone(Form("hcth_rec_otherbkg_sam%d",isam));
        hpmucth_rec_otherbkg[isam] = (TH2D*) hpmucth_rec[isam][4]->Clone(Form("hpmucth_rec_otherbkg_sam%d",isam));
        hpmu_true_otherbkg[isam] = (TH1D*) hpmu_true[isam][4]->Clone(Form("hpmu_true_otherbkg_sam%d",isam));
        
        hcth_true_otherbkg[isam] = (TH1D*) hcth_true[isam][4]->Clone(Form("hcth_true_otherbkg_sam%d",isam));
        
        hccqebin_true_otherbkg[isam] = (TH1D*) hccqebin_true[isam][4]->Clone(Form("hccqebin_true_otherbkg_sam%d",isam));
        
        for(int ireac=6; ireac<nreac; ++ireac){
            hccqebin_rec_otherbkg[isam]->Add(hccqebin_rec[isam][ireac]);
            henu_true_otherbkg[isam]->Add(henu_true[isam][ireac]);
            henu_rec_otherbkg[isam]->Add(henu_rec[isam][ireac]);
            hpmu_rec_otherbkg[isam]->Add(hpmu_rec[isam][ireac]);
            hcth_rec_otherbkg[isam]->Add(hcth_rec[isam][ireac]);
            hpmucth_rec_otherbkg[isam]->Add(hpmucth_rec[isam][ireac]);
            hpmu_true_otherbkg[isam]->Add(hpmu_true[isam][ireac]);
            hcth_true_otherbkg[isam]->Add(hcth_true[isam][ireac]);
            hccqebin_true_otherbkg[isam]->Add(hccqebin_true[isam][ireac]);
        }
        
        
        
        icolor = TColor::GetColor(m_color4merge[6]);
        hccqebin_rec_otherbkg[isam]->SetLineColor(icolor);
        hccqebin_rec_otherbkg[isam]->SetFillColor(icolor);
        
        henu_true_otherbkg[isam]->SetLineColor(icolor);
        henu_true_otherbkg[isam]->SetFillColor(icolor);
        
        henu_rec_otherbkg[isam]->SetLineColor(icolor);
        henu_rec_otherbkg[isam]->SetFillColor(icolor);
        
        hpmu_rec_otherbkg[isam]->SetLineColor(icolor);
        hpmu_rec_otherbkg[isam]->SetFillColor(icolor);
        
        hcth_rec_otherbkg[isam]->SetLineColor(icolor);
        hcth_rec_otherbkg[isam]->SetFillColor(icolor);
        
        
        hpmu_true_otherbkg[isam]->SetLineColor(icolor);
        hpmu_true_otherbkg[isam]->SetFillColor(icolor);
        
        hcth_true_otherbkg[isam]->SetLineColor(icolor);
        hcth_true_otherbkg[isam]->SetFillColor(icolor);
        
        hccqebin_true_otherbkg[isam]->SetLineColor(icolor);
        hccqebin_true_otherbkg[isam]->SetFillColor(icolor);
        
        fHstach_enu_true[isam]->Add(henu_true_otherbkg[isam]);
        fHstach_enu_rec[isam]->Add(henu_rec_otherbkg[isam]);
        fHstach_pmu_rec[isam]->Add(hpmu_rec_otherbkg[isam]);
        fHstach_costh_rec[isam]->Add(hcth_rec_otherbkg[isam]);
        fHstach_pmu_true[isam]->Add(hpmu_true_otherbkg[isam]);
        fHstach_costh_true[isam]->Add(hcth_true_otherbkg[isam]);
        fHstach_ccqebin_true[isam]->Add(hccqebin_true_otherbkg[isam]);
        fHstach_ccqebin_rec[isam]->Add(hccqebin_rec_otherbkg[isam]);
        
        for(int ireac=nreac-1;ireac>=0;ireac--){
            if(ireac<4) icolor = TColor::GetColor(m_color4merge[ireac+1]);
            else if (ireac==5) icolor = TColor::GetColor(m_color4merge[5]);
            else icolor = TColor::GetColor(m_color4merge[6]);//nothing to do
            
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
            
            if(ireac<4 || ireac==5){
                fHstach_enu_true[isam]->Add(henu_true[isam][ireac]);
                fHstach_enu_rec[isam]->Add(henu_rec[isam][ireac]);
                fHstach_pmu_rec[isam]->Add(hpmu_rec[isam][ireac]);
                fHstach_costh_rec[isam]->Add(hcth_rec[isam][ireac]);
                fHstach_pmu_true[isam]->Add(hpmu_true[isam][ireac]);
                fHstach_costh_true[isam]->Add(hcth_true[isam][ireac]);
                fHstach_ccqebin_true[isam]->Add(hccqebin_true[isam][ireac]);
                fHstach_ccqebin_rec[isam]->Add(hccqebin_rec[isam][ireac]);
            }
            
        }
       
        
        TLatex* tlx=new TLatex(0.42, 0.95,Form("Sample: %s",m_namelong[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        
        new TCanvas;
        fHstach_ccqebin_rec[isam]->Draw();
        fHstach_ccqebin_rec[isam]->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
        fHstach_ccqebin_rec[isam]->GetYaxis()->SetTitle("Number of Events");
        if(fHstach_ccqebin_rec[isam]->GetMaximum()> hccqebin_rec_data[isam]->GetMaximum())fHstach_ccqebin_rec[isam]->SetMaximum(fHstach_ccqebin_rec[isam]->GetMaximum()*1.2);
        else fHstach_ccqebin_rec[isam]->SetMaximum(hccqebin_rec_data[isam]->GetMaximum()*1.5);
        
        titleStyle(fHstach_ccqebin_rec[isam]);
        hccqebin_rec_data[isam]->SetMarkerStyle(8);
        hccqebin_rec_data[isam]->SetMarkerSize(1.1);
        //icolor = TColor::GetColor(m_color4merge[0]);
        //hccqebin_rec_data[isam]->SetMarkerColor(icolor);
        hccqebin_rec_data[isam]->Draw("ep same");
        //hccqebin_rec_data[isam]->Draw("ep same");
        tlx->Draw();
        if (isam>1){
            leg0->SetX1NDC(0.70);
            leg0->SetX2NDC(0.85);
        }
       leg0->Draw();
        
        gPad->Modified();
        gPad->Print(Form("plots/genievsneut_newbin2_mergebkg_hdatamc_ccqebin_rec_sam%d.eps",isam));
        
    }//end isam
    
    
    
    
    
    
}