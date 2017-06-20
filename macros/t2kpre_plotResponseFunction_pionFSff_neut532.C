{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    /*const Int_t NPARAMETER = 9;
    const char *namePara[NPARAMETER] = {"MECNorm","MACCQE","CA5RES","MaNFFRES","BgSclRES","dismpishp","FrAbs_pi","FrInelLow_pi","FrPiProd_pi"};
    */
    const Int_t NPARAMETER = 6;
    const char *namePara[NPARAMETER] = {"MECNorm","MACCQE","CA5RES","MaNFFRES","BgSclRES","dismpishp"};
    const char *colorcode[] = {"#000000","#77BE89",
        "#C557BA",
        "#C14E4C",
        "#C09A49",
        "#4F4337",
        "#A2B3BE",
        "#8FCE4A",
        "#7163A3"};
    Int_t icolor;
    const int markerStyle[] = {20, 21, 22, 24, 25, 26,27,28,29};
    Int_t imarker;
    /*const Int_t NSAMPLE = 2;
    const char *nameSample[NSAMPLE] = {"SIG", "SIDEBAND"};
    const char *nameSample_long[NSAMPLE]={"SIG", "SIDEBAND"};
    */
    const Int_t NSAMPLE = 4;
    const char *nameSample[] = {"SIG", "SIDEBAND","CR-I","CR-II"};
    const char *nameSample_long[]={"SIG", "SIDEBAND","CR-I","CR-II"};

   
    const Int_t NINTERACTION = 6;
    const char *nameInteraction[NINTERACTION] ={"cccoh#pi","cc0#pi","cc1#pi","ccother","nc-antinu","wall-ingrid"};
    
    const Int_t NBINCCQE = 1;//need to be consistent w/ inputs/cc1picohbins.txt
   
    const char *colorbin[] = {
        "#000000",
"#E69F00",
"#009E73",
"#0072B2",
"#D55E00"
        };
const int markerStyleBin[] = {20, 21, 22, 24, 25};

    TFile *pFile[NPARAMETER];
    for (Int_t ipara=0; ipara<NPARAMETER; ++ipara){
        pFile[ipara] = new TFile(Form("../inputs/responsefunction_%s.root",namePara[ipara]));
    }
    TGraph *pgrccqe[NPARAMETER][NSAMPLE][NINTERACTION][NBINCCQE];//
    
    for (Int_t ipara=0; ipara<NPARAMETER; ++ipara){
        icolor = TColor::GetColor(colorcode[ipara]);
        imarker = markerStyle[ipara];
        for (Int_t isam=0; isam<NSAMPLE; ++isam) {
            for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
                for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
                    pgrccqe[ipara][isam][iinttype][ibin] = (TGraph*) pFile[ipara]->Get(Form("response_sample%d_reaction%d_bin%d",isam,iinttype,ibin));
                    pgrccqe[ipara][isam][iinttype][ibin]->SetLineColor(icolor);
                    pgrccqe[ipara][isam][iinttype][ibin]->SetMarkerColor(icolor);
                    pgrccqe[ipara][isam][iinttype][ibin]->SetMarkerStyle(imarker);
                }
            }//end iinttype
        }//end isam
    }//end ipara
    //dummy TLegend
    TLegend* leg0 = new TLegend(.25, .65, 0.5, .9);
    leg0->SetFillStyle(0);
    leg0->SetBorderSize(0);
    leg0->SetTextSize(0.037);
    for (int ipara=0;ipara<NPARAMETER;ipara++){
        leg0->AddEntry(pgrccqe[ipara][0][0][0], namePara[ipara],"pl");
    }
    leg0->SetFillStyle(0);
    //draw
    for (Int_t isam=0; isam<NSAMPLE; ++isam) {
        for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
            for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
                new TCanvas;
                pgrccqe[0][isam][iinttype][ibin]->GetXaxis()->SetTitle("Parameter variation (#sigma)");
                pgrccqe[0][isam][iinttype][ibin]->GetYaxis()->SetTitle("Event variation (by bin)");
                
                titleStyle(pgrccqe[0][isam][iinttype][ibin]);
                //pgrccqe[0][isam][iinttype][ibin]->SetTitle(Form("%s %s bin%d",nameSample_long[isam],nameInteraction[iinttype],ibin));
                //pgrccqe[0][isam][iinttype][ibin]->CenterTitle();
                pgrccqe[0][isam][iinttype][ibin]->GetYaxis()->SetRangeUser(0,2);
                pgrccqe[0][isam][iinttype][ibin]->Draw("APL");
                for (Int_t ipara=1; ipara<NPARAMETER; ++ipara){
                    pgrccqe[ipara][isam][iinttype][ibin]->Draw("PL same");
                }
                TLatex* tlx=new TLatex(0.42, 0.95,Form("%s-%s-bin%d",nameSample_long[isam],nameInteraction[iinttype],ibin));
                tlx->SetNDC(kTRUE); // <- use NDC coordinate
                tlx->SetTextSize(0.05);
                tlx->SetTextAlign(21);
                tlx->Draw();
                leg0->Draw("same");
                gPad->Modified();
                gPad->Print(Form("plots/neut532_1bptheta_sam%d_int%d_bin%d_compSyst.eps",isam,iinttype,ibin));
            }
        }
    }
   
//draw by bin with main parameter, compare bin/signalvs sideband
for (Int_t ipara=0; ipara<NPARAMETER; ++ipara){
for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
	new TCanvas;
	for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
           icolor = TColor::GetColor(colorbin[ibin]);
           imarker = markerStyleBin[ibin]; 
           pgrccqe[ipara][0][iinttype][ibin]->SetLineColor(icolor);
           pgrccqe[ipara][0][iinttype][ibin]->SetMarkerColor(icolor);
           pgrccqe[ipara][0][iinttype][ibin]->SetMarkerStyle(imarker);
          // if(ibin==0)pgrccqe[ipara][0][iinttype][ibin]->Draw("APL");
           //else pgrccqe[ipara][0][iinttype][ibin]->Draw("PL same");

           pgrccqe[ipara][1][iinttype][ibin]->SetLineColor(icolor);
           pgrccqe[ipara][1][iinttype][ibin]->SetMarkerColor(icolor);
           pgrccqe[ipara][1][iinttype][ibin]->SetMarkerStyle(imarker);
           pgrccqe[ipara][1][iinttype][ibin]->SetLineStyle(7);
           //pgrccqe[ipara][1][iinttype][ibin]->Draw("PL same");
	}
      /*TLatex* tlx=new TLatex(0.42, 0.95,Form("%s-%s",namePara[isam],nameInteraction[iinttype]));
                tlx->SetNDC(kTRUE); // <- use NDC coordinate
                tlx->SetTextSize(0.05);
                tlx->SetTextAlign(21);
                tlx->Draw();
      gPad->Modified();
      gPad->Print(Form("plots/neut532_1bptheta_para%d_int%d_compsigvssb.eps",ipara,iinttype));
*/
}
}

TLegend* leg0bin = new TLegend(.75, .21, 0.95, .55);
    leg0bin->SetFillStyle(0);
    leg0bin->SetBorderSize(0);
    leg0bin->SetTextSize(0.037);
    for (int ibin=0;ibin<NBINCCQE;ibin++){
        leg0bin->AddEntry(pgrccqe[0][0][0][ibin], Form("Bin %d",ibin),"pl");
    }
  TH1F *h1 = new TH1F("h1","TLegend Example",200,-10,10);
//h1->SetLineColor("kBlack");
 TH1F *h2 = new TH1F("h2","TLegend Example",200,-10,10);
//h2->SetLineColor("kBlack");
h2->SetLineStyle(7);
leg0bin->AddEntry(h1,"Signal","l");
leg0bin->AddEntry(h2,"Sideband","l"); 
    leg0bin->SetFillStyle(0);
for (Int_t ipara=0; ipara<NPARAMETER; ++ipara){
for (Int_t iinttype=0; iinttype<NINTERACTION; ++iinttype) {
        new TCanvas;
        for (Int_t ibin=0; ibin<NBINCCQE; ibin++) {
           if(ibin==0){
pgrccqe[ipara][0][iinttype][ibin]->GetYaxis()->SetRangeUser(0,2);
pgrccqe[ipara][0][iinttype][ibin]->GetXaxis()->SetTitle("Parameter variation (#sigma)");
                pgrccqe[ipara][0][iinttype][ibin]->GetYaxis()->SetTitle("Event variation (by bin)");
titleStyle(pgrccqe[ipara][0][iinttype][ibin]);pgrccqe[ipara][0][iinttype][ibin]->Draw("APL");}
           else pgrccqe[ipara][0][iinttype][ibin]->Draw("PL same");

           pgrccqe[ipara][1][iinttype][ibin]->Draw("PL same");
        }
      TLatex* tlx=new TLatex(0.42, 0.95,Form("%s-%s",namePara[ipara],nameInteraction[iinttype]));
                tlx->SetNDC(kTRUE); // <- use NDC coordinate
                tlx->SetTextSize(0.05);
                tlx->SetTextAlign(21);
                tlx->Draw();
      leg0bin->Draw("same");
      gPad->Modified();
      gPad->Print(Form("plots/neut532_1bptheta_para%d_int%d_compsigvssb.eps",ipara,iinttype));
}
}


}
