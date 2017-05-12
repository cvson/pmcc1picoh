{
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    const Int_t NPARAMETER = 8;
    const char *namePara[NPARAMETER] = {"MACCQE","MARES","CC1piE0","CC1piE1","CCother","PilessDcy","1piEnuShape","AllElse"};
    
    const char *colorcode[NPARAMETER] = {"#77BE89",
        "#C557BA",
        "#C14E4C",
        "#C09A49",
        "#4F4337",
        "#A2B3BE",
        "#8FCE4A",
        "#7163A3"};
    Int_t icolor;
    const int markerStyle[NPARAMETER] = {20, 21, 22, 24, 25, 26,27,28};
    Int_t imarker;
    const Int_t NSAMPLE = 4;
    const char *nameSample[NSAMPLE] = {"SIG", "CRI", "CRII", "CRIII"};
    const char *nameSample_long[NSAMPLE]={"SIG", "CRI", "CRII", "CRIII"};
    
    const Int_t NINTERACTION = 6;
    const char *nameInteraction[NINTERACTION] ={"cc1picoh","ccqe","cc1pi","ccother","nc-antinu","wall-ingrid"};
    
    const Int_t NBINCCQE = 10;
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
                gPad->Print(Form("plots/response_sample%d_interac%d_bin%d_compSyst.eps",isam,iinttype,ibin));
            }
        }
    }
    
}