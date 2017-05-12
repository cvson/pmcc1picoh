//#include "/home/kikawa/macros/cccoh.h"
#include "cccoh.h"

float GetError(TH1F *h1, bool posi){
    float width = h1->GetBinWidth(1);
    int nbint = h1->GetNbinsX();
    int nbin = nbint/2;
    double total=0;
    for(int i=0;i<nbin;i++){
        if(posi)total+=h1->GetBinContent(nbin+i+1);
        else    total+=h1->GetBinContent(nbin-i);
    }
    double sum=0;
    float err;
    for(int i=0;i<nbin;i++){
        if(posi)sum+=h1->GetBinContent(nbin+i+1);
        else    sum+=h1->GetBinContent(nbin-i);
        if(sum/total>0.682){
            err=i*width;
            break;
        }
    }
    
    return err;
};


void Draw_Result_revrev(){
    gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
    //TFile *_file0 = TFile::Open("/home/kikawa/macros/flux_err_cccoh/toymc.root");
    //TFile *_file0 = TFile::Open("toymc_nom.root");
    TFile *_file0 = TFile::Open("toymc_mva.root");
    
    //float bg_ratio=1-((qedet->GetSumOfWeights())/(qedet->GetSumOfWeights()+nqedet->GetSumOfWeights()));
    
    float bg_ratio=1-((qedet->GetSumOfWeights())/(qedet->GetSumOfWeights()+nqedet->GetSumOfWeights()));
    //bg_ratio=bgrat;
    bg_ratio=bgratmva;
    
    //TCanvas *c1 = new TCanvas("c1","c1",0,0,1000,800);
    //gStyle->SetOptTitle(0);
    //gStyle->SetOptStat(1100);
    //gStyle->SetOptStat(0);
    
    //tree->Draw(Form("((%e-%e*nqedet)/(%e-%e)/flux/qeeff-1)*100>>h1(40000,-200,200)",result, bg_ratio, result, bg_ratio));
    tree->Draw(Form("((%e-%e*nqedet)/(%e-%e)/flux/qeeff-1)*100>>h1(40000,-200,200)",resultmva, bg_ratio, resultmva, bg_ratio));
    h1->GetXaxis()->SetTitle("Variation of #sigma_{CC-coh.#pi} [%]");
    Int_t ci;
     ci = TColor::GetColor("#B45F04");
    
    h1->SetFillColor(ci);
    gStyle->SetOptStat(1100);
    float err=h1->GetRMS();
    
    cout<<err<<endl;
    
    cout<<GetError(h1,0)<<" "<<GetError(h1,1)<<endl;
    plot1hist_stat(h1,"xsec_variation_toymc_mva",true);
}
