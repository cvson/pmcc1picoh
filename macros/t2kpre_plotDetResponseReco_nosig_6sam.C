{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 6;
    const Int_t NSYSRECO = 5;
    const Int_t NFILE = 11;
    const Int_t NBINCCQE = 5; //need to be consistent w/ inputs/cc1picohbins.txt
    
    const char *nameSample[] = {"SIG",  "CRI", "CRII","CRIII","CRIV","CRV"};
    const char *nameSample_long[]={"SIG",  "CRI", "CRII","CRIII","CRIV","CRV"};
    
    const char *namesys[NSYSRECO] ={"vertxy","vertz","3dmatch","INmatchpos","INmatchang"};
    const char *namesyslong[NSYSRECO] ={"vertex xy","vertex z","3D matching","INGRID matching pos.","INGRID matching angle"};
    
    const char *colorcode[] = {"#000000",
        "#0072B2",
        "#D55E00",
	"#CC79A7",
        "#E69F00",
        "#F0E442"
};
    const char *colorbyfile[NFILE] = {"#496364", "#80CF51", "#A95DC9", "#C15237", "#D1B54D","#8BCFAF",
        "#8291C8", "#C94C87", "#CDA09B", "#5C632F","#562E44"};
    /*const char *colorbybin[NBINCCQE] = {"#9E62B5",
        "#90CB5F",
        "#83A0A3",
        "#A6444B",
        "#92783C"};
    */

    /*const char *colorbybin[NBINCCQE] = {"#C04F37",//NBINCCQE=10
        "#71C44C",
        "#C559CD",
        "#9AAAC1",
        "#464035",
        "#B14E79",
        "#81C8A1",
        "#CCBC43",
        "#6B63AC",
        "#B29263"};*/
    /*const char *colorbybin[NBINCCQE] = {
        "#C04F37",//NBINCCQE=9
        "#71C44C",
        "#C559CD",
        "#9AAAC1",
        "#464035",
        "#B14E79",
        "#81C8A1",
        "#CCBC43",
        "#6B63AC"
        };
    */
    const char *colorbybin[NBINCCQE] = {
    "#000000",
"#E69F00",
"#009E73",
"#0072B2",
"#D55E00"
    }
    
    const int markerStyle[] = {20, 21, 22,23,24,25};
   const int markerStyleBin[NBINCCQE] = {20, 21, 22, 24, 25/*, 26,27,28,29*/}; 
    
    TFile *pFile = new TFile("../inputs/detresponsefunction_reco.root");
    
    TGraph *pgrccqesub[NSYSRECO][NSAMPLE][NBINCCQE];
    TH1F *hbinccqe[NSAMPLE][NFILE];
    TH1F *hdatabinccqe[NSAMPLE][NFILE];
    
    for (int isam=0; isam<NSAMPLE; ++isam) {
        
        for (int ifile=0; ifile < NFILE; ++ifile) {
            icolor = TColor::GetColor(colorbyfile[ifile]);
            hbinccqe[isam][ifile] = (TH1F*)pFile->Get(Form("hbinccqe_sam%d_id%d",isam,ifile));
            hdatabinccqe[isam][ifile] = (TH1F*)pFile->Get(Form("hdatabinccqe_sam%d_id%d",isam,ifile));
            hbinccqe[isam][ifile]->SetLineColor(icolor);
            hdatabinccqe[isam][ifile]->SetLineColor(icolor);
        }
        new TCanvas;
        hbinccqe[isam][0]->GetXaxis()->SetTitle("p-#theta bins");
        hbinccqe[isam][0]->GetYaxis()->SetTitle("Number of events");
        titleStyle(hbinccqe[isam][0]);
        hbinccqe[isam][0]->SetMinimum(0);
        hbinccqe[isam][0]->Draw();
        for (int ifile=1; ifile < NFILE; ++ifile) {
            hbinccqe[isam][ifile]->Draw("same");
        }
        TLatex* tlx=new TLatex(0.42, 0.95,Form("%s ",nameSample_long[isam]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Print(Form("plots/detresponse_reconosig_5bptheta_hbinccqe_mc_sam%d_compAll.eps",isam));
        
        new TCanvas;
        hdatabinccqe[isam][0]->GetXaxis()->SetTitle("p-#theta bins");
        hdatabinccqe[isam][0]->GetYaxis()->SetTitle("Number of events");
        titleStyle(hdatabinccqe[isam][0]);
        hdatabinccqe[isam][0]->SetMinimum(0);
        hdatabinccqe[isam][0]->Draw();
        
        for (int ifile=1; ifile < NFILE; ++ifile) {
            hdatabinccqe[isam][ifile]->Draw("same");
        }
        tlx->Draw();
        gPad->Print(Form("plots/detresponse_reconosig_5bptheta_hbinccqe_data_sam%d_compAll.eps",isam));
        
    }
    
    for (Int_t isys=0; isys<NSYSRECO; ++isys) {
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            icolor = TColor::GetColor(colorcode[isam]);
            imarker = markerStyle[isam];
            for (Int_t ibin=0; ibin<NBINCCQE; ++ibin) {
                pgrccqesub[isys][isam][ibin] = (TGraph*)pFile->Get(Form("response_sub_%s_sample%d_bin%d",namesys[isys],isam,ibin));
                pgrccqesub[isys][isam][ibin]->SetLineColor(icolor);
                pgrccqesub[isys][isam][ibin]->SetMarkerColor(icolor);
                pgrccqesub[isys][isam][ibin]->SetMarkerStyle(imarker);
            }
        }
    }
    //dummy TLegend
    TLegend* leg0 = new TLegend(.25, .62, 0.5, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.035);
    for (int isam=1;isam<2;isam++){
        leg0->AddEntry(pgrccqesub[0][isam][0], nameSample_long[isam],"pl");
    }
    leg0->SetFillStyle(0);
    
    //plot compare by SAMPLE
    for (Int_t isys=0; isys<NSYSRECO; ++isys) {
        for (Int_t ibin=0; ibin<NBINCCQE; ++ibin) {
            new TCanvas;
            pgrccqesub[isys][1][ibin]->GetYaxis()->SetTitle("Data-MC difference");
            pgrccqesub[isys][1][ibin]->GetXaxis()->SetTitle("Variations");
            
            titleStyle(pgrccqesub[isys][1][ibin]);
            pgrccqesub[isys][1][ibin]->GetYaxis()->SetRangeUser(-0.2,0.2);
            pgrccqesub[isys][1][ibin]->Draw("APL");
            /*for (Int_t isam=1; isam<2; ++isam){
                pgrccqesub[isys][isam][ibin]->Draw("PL same");
            }*/
            TLatex* tlx=new TLatex(0.42, 0.95,Form("%s bin%d",namesyslong[isys],ibin));
            tlx->SetNDC(kTRUE); // <- use NDC coordinate
            tlx->SetTextSize(0.05);
            tlx->Draw();
            leg0->Draw("same");
            gPad->Modified();
            gPad->Print(Form("plots/detresponse_reconosig_5bptheta_%s_bin%d_compSyst.eps",namesys[isys],ibin));
        }
    }
    
    //plot compare by BIN
    for (Int_t isys=0; isys<NSYSRECO; ++isys) {
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            for (Int_t ibin=0; ibin<NBINCCQE; ++ibin) {
                icolor = TColor::GetColor(colorbybin[ibin]);
                pgrccqesub[isys][isam][ibin]->SetLineColor(icolor);
                pgrccqesub[isys][isam][ibin]->SetMarkerColor(icolor);
                imarker = markerStyleBin[ibin];
                pgrccqesub[isys][isam][ibin]->SetMarkerStyle(imarker);
                if(isam==1) pgrccqesub[isys][isam][ibin]->SetLineStyle(7);
            }
            //new TCanvas;
            pgrccqesub[isys][isam][0]->GetYaxis()->SetTitle("Data-MC difference");
            pgrccqesub[isys][isam][0]->GetXaxis()->SetTitle("Variations");
            
            titleStyle(pgrccqesub[isys][isam][0]);
            pgrccqesub[isys][isam][0]->GetYaxis()->SetRangeUser(-0.2,0.2);
            //pgrccqesub[isys][isam][0]->Draw("APL");
            /*for (Int_t ibin=1; ibin<NBINCCQE; ++ibin){
                pgrccqesub[isys][isam][ibin]->Draw("PL same");
            }
            TLatex* tlx=new TLatex(0.42, 0.95,Form("%s: %s",nameSample_long[isam],namesyslong[isys]));
            tlx->SetNDC(kTRUE); // <- use NDC coordinate
            tlx->SetTextSize(0.05);
            tlx->Draw();
            gPad->Modified();
            gPad->Print(Form("plots/detresponse_reconosig_5bptheta_%s_%s_compAllBin.eps",nameSample[isam], namesys[isys]));
          */
          }
    }
    TLegend* leg0bin = new TLegend(.75, .21, 0.95, .55);
    leg0bin->SetFillStyle(0);
    leg0bin->SetBorderSize(0);
    leg0bin->SetTextSize(0.037);
    for (int ibin=0;ibin<NBINCCQE;ibin++){
        leg0bin->AddEntry(pgrccqesub[0][0][ibin], Form("Bin %d",ibin),"pl");
    }
  TH1F *h1 = new TH1F("h1","TLegend Example",200,-10,10);
//h1->SetLineColor("kBlack");
 TH1F *h2 = new TH1F("h2","TLegend Example",200,-10,10);
//h2->SetLineColor("kBlack");
h2->SetLineStyle(7);
//leg0bin->AddEntry(h1,"Signal","l");
leg0bin->AddEntry(h2,"Sideband","l");
    leg0bin->SetFillStyle(0);

for (Int_t isys=0; isys<NSYSRECO; ++isys) {
	new TCanvas;
	//pgrccqesub[isys][0][0]->Draw("APL");
	pgrccqesub[isys][1][0]->Draw("APL");
	for (Int_t ibin=1; ibin<NBINCCQE; ++ibin) {
		//pgrccqesub[isys][0][ibin]->Draw("PL same");
		pgrccqesub[isys][1][ibin]->Draw("PL same");
	}
	leg0bin->Draw("same");
	TLatex* tlx=new TLatex(0.42, 0.95,Form("Syst: %s",namesyslong[isys]));
        tlx->SetNDC(kTRUE); // <- use NDC coordinate
        tlx->SetTextSize(0.05);
        tlx->Draw();
        gPad->Modified();
        gPad->Print(Form("plots/detresponse_reconosig_5bptheta_sigvssb_%s_compAllBin.eps", namesys[isys]));
}

    //Storage uncertainty
    //TGraph *pgrccqesub[NSYSRECO][NSAMPLE][NBINCCQE];
    TGraph *pUncertaintyComb[NSAMPLE];
    TGraph *pUncertainty[NSYSRECO][NSAMPLE];//for each individual
    TFile *popfile = new TFile("../inputs/detresponse_reconosig_5bptheta_uncertainty.root","RECREATE");
    double aVariation[NBINCCQE];
    double aVariationAll[NBINCCQE];
    double tempMaxGraph;
    double tempMinGraph;
    double xBinValue[NBINCCQE];
    for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
        xBinValue[ibin] = ibin+0.5;
    }
    
    for (int isam=0; isam<NSAMPLE; ++isam) {
        //reset
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
            aVariationAll[ibin] = 0;
        }
        
        for (Int_t isys=0; isys<NSYSRECO; ++isys) {
            for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
                tempMaxGraph = TMath::Abs(TMath::MaxElement(3,pgrccqesub[isys][isam][ibin]->GetY()));
                tempMinGraph = TMath::Abs(TMath::MinElement(3,pgrccqesub[isys][isam][ibin]->GetY()));
                aVariation[ibin] = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;
                //there no events in bin 7 and bin9 of CRIIB--> 100%
                if(isam==3 && (ibin==7 || ibin==9)) aVariation[ibin] = 1.;
                cout<<"SYS "<<isys<<" SAM "<<isam<<" BIN "<<ibin<<" abs(MAX) "<<tempMaxGraph<<" abs(MIN) "<<tempMinGraph<<" val "<<aVariation[ibin]<<endl;
                
                aVariationAll[ibin] += pow(aVariation[ibin],2);
                
            }
            pUncertainty[isys][isam] = new TGraph(NBINCCQE,xBinValue,aVariation);
            pUncertainty[isys][isam]->Write(Form("detresponse_reconosig_5bptheta_uncertainty_sam%d_sys%d",isam,isys));
        }
        //make square root
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
            if (aVariationAll[ibin]>1.0) aVariationAll[ibin] =1;
            else aVariationAll[ibin] = TMath::Sqrt(aVariationAll[ibin]);
            cout<<" SAM "<<isam<<" bin "<<ibin<<" COMBERROR "<<aVariationAll[ibin]<<endl;
        }
        
        pUncertaintyComb[isam] = new TGraph(NBINCCQE,xBinValue,aVariationAll);
        pUncertaintyComb[isam]->Write(Form("detresponse_reconosig_5bpthetaall_uncertainty_sam%d",isam));
    }
    
    popfile->Write();
    popfile->Close();
    
}
