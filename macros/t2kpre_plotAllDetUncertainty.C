{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    ///////////////////////////////////////////////////////////////////////////////////////
    ///// some Scale
    ///////////////////////////////////////////////////////////////////////////////////////
    const double TargetMass = 0.0025;//technical note
    ///////////////////////////////////////////////////////////////////////////////////////
    ///// Get individual
    ///////////////////////////////////////////////////////////////////////////////////////
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 3;
    const char *nameSample[NSAMPLE] = {"SIG", "CRI", "CRII"};
    const char *nameSample_long[NSAMPLE]={"Signal sample", "Sideband", "CRII"};
    
    const char *colorcode[NSAMPLE] = {"#000000",
        "#0072B2",
        "#D55E00"};
    const int markerStyle[NSAMPLE] = {20, 21, 22};
    
    const Int_t NSYS=5;
    double ymingraph[NSYS]={0,0,0,0,0};
    double ymaxgraph[NSYS]={0.2,0.2,0.2,0.2,0.2};
    const char *subname[NSYS] = {"pe_5bptheta","reco_5bpthetaall","fvtimeall","noise_5bptheta","hiteff_5bptheta"};
    const char *subnamelong[NSYS] = {"Light yield","Track reconstruction","FV + Veto","Noise","Hit efficiency"};
    TFile *paFile[NSYS];
    paFile[0] = new TFile("../inputs/detresponse_pe_5bptheta_uncertainty.root");
    paFile[1] = new TFile("../inputs/detresponse_reco_5bptheta_uncertainty.root");
    paFile[2] = new TFile("../inputs/detresponse_FVTime_5bptheta.root");
    paFile[3] = new TFile("../inputs/detresponse_noise_5bptheta_uncertainty.root");
    paFile[4] = new TFile("../inputs/detresponse_hiteff_5bptheta_uncertainty.root");
    
    TGraph *pUncertainty[NSYS][NSAMPLE];
    TGraph *pUncertaintyComb[NSAMPLE];
    
    for (Int_t isys=0; isys<NSYS; ++isys) {
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            icolor = TColor::GetColor(colorcode[isam]);
            imarker = markerStyle[isam];
            pUncertainty[isys][isam] = (TGraph*)paFile[isys]->Get(Form("detresponse_%s_uncertainty_sam%d",subname[isys],isam));
            //else pUncertainty[isys][isam] = (TGraph*)paFile[isys]->Get(Form("detresponse_%s_5bptheta_uncertainty_sam%d",subname[isys],isam));
            pUncertainty[isys][isam]->SetLineColor(icolor);
            pUncertainty[isys][isam]->SetMarkerColor(icolor);
            pUncertainty[isys][isam]->SetMarkerStyle(imarker);
            pUncertainty[isys][isam]->SetLineWidth(3);
            
        }
        
    }
    //making sum
    Double_t* arrayXgraph = pUncertainty[0][0]->GetX();
    static const int NBINCCQE = pUncertainty[0][0]->GetN();//newadd
    Double_t* arrayYgraph = new Double_t[NBINCCQE];// =pUncertainty[0][0]->GetY();
    
    ///////////////////////////////////////////////////////////////////////////////////////
    ///// Output Detector covariance
    ///////////////////////////////////////////////////////////////////////////////////////
    TFile *popfile = new TFile("../inputs/detectorAll_5bptheta_covariance_matrix.root","RECREATE");
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        icolor = TColor::GetColor(colorcode[isam]);
        imarker = markerStyle[isam];
        for (Int_t ibin=0; ibin<NBINCCQE; ++ibin) {
            arrayYgraph[ibin] = 0;//reset
        }
        
        for (Int_t isys=0; isys<NSYS; ++isys) {
            Double_t* arrayYtmp =pUncertainty[isys][isam]->GetY();
            for (Int_t ibin=0; ibin<NBINCCQE; ++ibin) {
                arrayYgraph[ibin] += pow(arrayYtmp[ibin],2);//reset
                
            }
        }
        
        for (Int_t ibin=0; ibin<NBINCCQE; ++ibin) {
            if(arrayYgraph[ibin]>1) arrayYgraph[ibin] = 1;
            else arrayYgraph[ibin] = TMath::Sqrt(arrayYgraph[ibin]);
            cout<<"SAM "<<isam<<" BIN "<<ibin<<" ERROR "<<arrayYgraph[ibin]<<endl;
        }
        pUncertaintyComb[isam] = new TGraph(NBINCCQE, arrayXgraph, arrayYgraph);
        pUncertaintyComb[isam]->Write(Form("DetUncertainty_sam%d",isam));
        pUncertaintyComb[isam]->SetLineColor(icolor);
        pUncertaintyComb[isam]->SetLineWidth(3);
        pUncertaintyComb[isam]->SetMarkerColor(icolor);
        pUncertaintyComb[isam]->SetMarkerStyle(imarker);
        
    }
    //fill covariance matrix
    //3 cases
    TMatrixDSym *cov_det[3];
    Int_t nparas;
    for (Int_t icase=0; icase<3; ++icase){
        nparas = NBINCCQE*(icase+1);
        cov_det[icase] = new TMatrixDSym(nparas);
        switch(icase){
            case 0:
                //sam 0
                cout<<"FILL case "<<icase<<endl;
                if (cov_det[icase]->GetNrows()!=nparas)cout<<"what's wrong"<<endl;
                for (Int_t ipara=0;ipara<nparas;++ipara){
                    cout<<" VALUE "<<pUncertaintyComb[0]->GetY()[ipara]<<endl;
                    (*cov_det[icase])(ipara,ipara) = pow(pUncertaintyComb[0]->GetY()[ipara],2);
                }
                break;
                
            case 1:
                //sam 0, 1
                cout<<"FILL case "<<icase<<endl;
                if (cov_det[icase]->GetNrows()!=nparas)cout<<"what's wrong"<<endl;
                for (Int_t ipara=0;ipara<nparas;++ipara){
                    
                    if(ipara<NBINCCQE){
                        cout<<" VALUE "<<pUncertaintyComb[0]->GetY()[ipara]<<endl;
                        (*cov_det[icase])(ipara,ipara) = pow(pUncertaintyComb[0]->GetY()[ipara],2);
                    }
                    else {
                        cout<<" VALUE "<<pUncertaintyComb[1]->GetY()[ipara-NBINCCQE]<<endl;
                        (*cov_det[icase])(ipara,ipara) = pow(pUncertaintyComb[1]->GetY()[ipara-NBINCCQE],2);
                    }
                }
                break;
                
            case 2:
                //0, 1,2
                cout<<"FILL case "<<icase<<endl;
                if (cov_det[icase]->GetNrows()!=nparas)cout<<"what's wrong"<<endl;
                for (Int_t ipara=0;ipara<nparas;++ipara){
                    
                    if(ipara<NBINCCQE){
                        cout<<" VALUE "<<pUncertaintyComb[0]->GetY()[ipara]<<endl;
                        (*cov_det[icase])(ipara,ipara) = pow(pUncertaintyComb[0]->GetY()[ipara],2);
                    }
                    else if(ipara<(NBINCCQE*2)){
                        cout<<" VALUE "<<pUncertaintyComb[1]->GetY()[ipara-NBINCCQE]<<endl;
                        (*cov_det[icase])(ipara,ipara) = pow(pUncertaintyComb[1]->GetY()[ipara-NBINCCQE],2);
                    }
                    else{
                        cout<<" VALUE "<<pUncertaintyComb[2]->GetY()[ipara-NBINCCQE*2]<<endl;
                        (*cov_det[icase])(ipara,ipara) = pow(pUncertaintyComb[2]->GetY()[ipara-NBINCCQE*2],2);
                    }
                    
                }
                
                break;
                
                
                
        }
        cov_det[icase]->Write(Form("detector_covmat_case%d",icase));
    }
    
    popfile->Write();
    popfile->Close();
    
    //Drawing
    TLegend* leg0 = new TLegend(.25, .65, 0.5, .85);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.035);
    for (int isam=0;isam<2;isam++){
        leg0->AddEntry(pUncertainty[0][isam], nameSample_long[isam],"pl");
    }
    leg0->SetFillStyle(0);
    
    for (Int_t isys=0; isys<NSYS; ++isys) {
        new TCanvas;
        pUncertainty[isys][0]->GetXaxis()->SetTitle("p_{#mu}-cos(#theta_{#mu}) bins");
        pUncertainty[isys][0]->GetYaxis()->SetTitle("Uncertainty");
        
        titleStyle(pUncertainty[isys][0]);
        pUncertainty[isys][0]->GetYaxis()->SetRangeUser(ymingraph[isys],ymaxgraph[isys]);
        pUncertainty[isys][0]->Draw("APL");
        for (Int_t isam=1; isam<2; ++isam){
            pUncertainty[isys][isam]->Draw("PL same");
        }
        TLatex* tlx=new TLatex(0.42, 0.95,Form("Syst: %s",subnamelong[isys]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        leg0->Draw("same");
        gPad->Modified();
        gPad->Print(Form("plots/alldet_5bptheta_uncertainty_%s_compSample.eps",subname[isys]));
    }
    
    //drawing for all
    new TCanvas;
    pUncertaintyComb[0]->GetXaxis()->SetTitle("p_{#mu}-cos(#theta_{#mu}) bins");
    pUncertaintyComb[0]->GetYaxis()->SetTitle("Uncertainty");
    
    titleStyle(pUncertaintyComb[0]);
    pUncertaintyComb[0]->GetYaxis()->SetRangeUser(0,0.2);
    pUncertaintyComb[0]->Draw("APL");
    for (Int_t isam=1; isam<2; ++isam){
        pUncertaintyComb[isam]->Draw("PL same");
    }
    TLatex* tlx=new TLatex(0.42, 0.95,"All systematics");
    tlx->SetNDC(kTRUE); // <- use NDC coordinate
    tlx->SetTextSize(0.05);
    tlx->Draw();
    leg0->Draw("same");
    gPad->Modified();
    gPad->Print("plots/alldet_5bptheta_alluncertainty_compSample.eps");
    
}
