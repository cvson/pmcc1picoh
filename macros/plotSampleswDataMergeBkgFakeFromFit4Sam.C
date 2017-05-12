{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    TFile *pfile = new TFile("../outputs/four/fittoy_result_1allpara.root");
    string tag = "nominal";
    string tagfit = "fit";
    const int nreac = 9;//10;
    const int nsample = 4;
    const char *m_name[] = {"SIG", "CRI", "CRIICHiPID", "M2TRKHiPID"};
    const char *m_namelong[] = {"Signal", "Control I", "Control II", "Control III"};
    const char *names[] = {"sig", "ccqe", "cc1pi", "ccother", "nc", "numubar", "nue", "ingrid", "wall"};
    const char *m_color4merge[] = {"#4F4737", "#B74E72", "#7E81B0", "#95C34D", "#C56E3B", "#95C4A8", "#AD5DC9"};
        Int_t icolor;
    TH1D *hccqebin_rec[nsample][nreac];//mc
    TH1D *hccqebin_rec_fit[nsample][nreac];//fit
    
    TH1D *hccqebin_rec_data[nsample];
    
    //mc
    TH1D *hccqebin_rec_otherbkg[nsample];//nc, nue, ingrid, wall
    //fit
    TH1D *hccqebin_rec_otherbkg_fit[nsample];//nc, nue, ingrid, wall
    
    for(int isam=0;isam<nsample;isam++){
        hccqebin_rec_data[isam]= (TH1D*)pfile->Get(Form("evhist_sam%d_iter0_data",isam));
        for(int ireac=0;ireac<nreac;ireac++)
        {
            hccqebin_rec[isam][ireac] = (TH1D*)pfile->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tag.c_str()));
            //fit
            hccqebin_rec_fit[isam][ireac] = (TH1D*)pfile->Get(Form("%s_ccqebins_rec_%s_%s",m_name[isam],names[ireac],tagfit.c_str()));
        }//end for ireac
        
    }//end for isam
    //Dummy TLegend
    //new TCanvas;
    TLegend* leg0 = new TLegend(.2, .5, 0.45, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.035);
    leg0->AddEntry(hccqebin_rec_data[0], "GENIE MC","lp");
    for (int ireac=0;ireac<nreac;ireac++){
        if(ireac<4 || ireac==5)leg0->AddEntry(hccqebin_rec[0][ireac], names[ireac],"lf");
    }
    leg0->AddEntry(hccqebin_rec[0][6], "otherbkg","lf");
    leg0->SetFillStyle(0);
    
    //leg0->Draw();
    //gPad->Print("plots/fakefit_newbin_mergebkg_dummyLegend.eps");
    
   
    THStack* fHstach_ccqebin_rec[nsample];//mc
    THStack* fHstach_ccqebin_rec_fit[nsample];//fit

    for(int isam=0;isam<nsample;isam++){
        //fake
        fHstach_ccqebin_rec[isam]= new THStack(Form("fHstach_ccqebin_rec_sam%d",isam),Form("fHstach_ccqebin_rec_sam%d",isam));
        //fit
        fHstach_ccqebin_rec_fit[isam]= new THStack(Form("fHstach_ccqebin_rec_fit_sam%d",isam),Form("fHstach_ccqebin_rec_fit_sam%d",isam));
        
        hccqebin_rec_otherbkg[isam] = (TH1D*) hccqebin_rec[isam][4]->Clone(Form("hccqebin_rec_otherbkg_sam%d",isam));
        //fit
        hccqebin_rec_otherbkg_fit[isam] = (TH1D*) hccqebin_rec_fit[isam][4]->Clone(Form("hccqebin_rec_fit_otherbkg_sam%d",isam));
        
        
        for(int ireac=6; ireac<9; ++ireac){
            hccqebin_rec_otherbkg[isam]->Add(hccqebin_rec[isam][ireac]);//mc
            //fit
            hccqebin_rec_otherbkg_fit[isam]->Add(hccqebin_rec_fit[isam][ireac]);
        }

        icolor = TColor::GetColor(m_color4merge[6]);
        hccqebin_rec_otherbkg[isam]->SetLineColor(icolor);
        hccqebin_rec_otherbkg[isam]->SetFillColor(icolor);
        fHstach_ccqebin_rec[isam]->Add(hccqebin_rec_otherbkg[isam]);
        //fit
        hccqebin_rec_otherbkg_fit[isam]->SetLineColor(icolor);
        hccqebin_rec_otherbkg_fit[isam]->SetFillColor(icolor);
        fHstach_ccqebin_rec_fit[isam]->Add(hccqebin_rec_otherbkg_fit[isam]);
        
        for(int ireac=nreac-1;ireac>=0;ireac--){
            if(ireac<4) icolor = TColor::GetColor(m_color4merge[ireac+1]);
            else if (ireac==5) icolor = TColor::GetColor(m_color4merge[5]);
            else icolor = TColor::GetColor(m_color4merge[6]);//nothing to do
 
            hccqebin_rec[isam][ireac]->SetLineColor(icolor);
            hccqebin_rec[isam][ireac]->SetFillColor(icolor);
            
            //fit
            hccqebin_rec_fit[isam][ireac]->SetLineColor(icolor);
            hccqebin_rec_fit[isam][ireac]->SetFillColor(icolor);
            
            if(ireac<4 || ireac==5){
                fHstach_ccqebin_rec[isam]->Add(hccqebin_rec[isam][ireac]);
                //fit
                fHstach_ccqebin_rec_fit[isam]->Add(hccqebin_rec_fit[isam][ireac]);
            }
            
        }
       
        
        TLatex* tlx=new TLatex(0.42, 0.95,Form("Sample: %s",m_namelong[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        
        
        new TCanvas;
        fHstach_ccqebin_rec[isam]->Draw();
        fHstach_ccqebin_rec[isam]->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
        fHstach_ccqebin_rec[isam]->GetYaxis()->SetTitle("Number of Events");
        /*if(fHstach_ccqebin_rec[isam]->GetMaximum()> hccqebin_rec_data[isam]->GetMaximum())fHstach_ccqebin_rec[isam]->SetMaximum(fHstach_ccqebin_rec[isam]->GetMaximum()*1.2);
        else fHstach_ccqebin_rec[isam]->SetMaximum(hccqebin_rec_data[isam]->GetMaximum()*1.5);*/
        if(isam==0)fHstach_ccqebin_rec[isam]->SetMaximum(hccqebin_rec_data[isam]->GetMaximum()*1.5);
        else fHstach_ccqebin_rec[isam]->SetMaximum(hccqebin_rec_data[isam]->GetMaximum()*1.3);
        titleStyle(fHstach_ccqebin_rec[isam]);
        hccqebin_rec_data[isam]->SetMarkerStyle(8);
        hccqebin_rec_data[isam]->SetMarkerSize(1.1);
        hccqebin_rec_data[isam]->Draw("ep same");
        tlx->Draw();
        if (isam==0){
            leg0->SetX1NDC(.17);
            leg0->SetX2NDC(.31);
        }
        else if (isam==1){
            leg0->SetX1NDC(.2);
            leg0->SetX2NDC(.35);
        }
        else if (isam>1){
            leg0->SetX1NDC(.6);
            leg0->SetX2NDC(.85);
        }
        
        leg0->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/4samfakefit_newbin_mergebkg_hdatamc_ccqebin_rec_sam%d_newbin2.eps",isam));
        
        //fit
        new TCanvas;
        fHstach_ccqebin_rec_fit[isam]->Draw();
        fHstach_ccqebin_rec_fit[isam]->GetXaxis()->SetTitle("Reconstructed p-cos(#theta) bins");
        fHstach_ccqebin_rec_fit[isam]->GetYaxis()->SetTitle("Number of Events");
        if(isam==0)fHstach_ccqebin_rec_fit[isam]->SetMaximum(hccqebin_rec_data[isam]->GetMaximum()*1.5);
        else fHstach_ccqebin_rec_fit[isam]->SetMaximum(hccqebin_rec_data[isam]->GetMaximum()*1.3);
        titleStyle(fHstach_ccqebin_rec_fit[isam]);
        hccqebin_rec_data[isam]->SetMarkerStyle(8);
        hccqebin_rec_data[isam]->SetMarkerSize(1.1);
        hccqebin_rec_data[isam]->Draw("ep same");
        tlx->Draw();
        if (isam==0){
            leg0->SetX1NDC(.17);
            leg0->SetX2NDC(.31);
        }
        else if (isam==1){
            leg0->SetX1NDC(.2);
            leg0->SetX2NDC(.35);
        }
        else if (isam>1){
            leg0->SetX1NDC(.6);
            leg0->SetX2NDC(.85);
        }
        
        leg0->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/4samfakefit_newbin_mergebkg_hdatamc_ccqebin_rec_fit_sam%d_newbin2.eps",isam));
    }
    
    
    
    
    
    
}