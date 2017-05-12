//#include "/home/kikawa/macros/cccoh.h"
#include "/home/cvson/cc1picoh/syst/cccoh.h"

#define NMOD 14
#define NBIN 200
#define NMIN 0
#define NMAX 10

TH1D*  tratio[NMOD];
TH1D*  tratio2[NMOD];
double rwratio[NMOD][NBIN];
string fratio="/home/kikawa/macros/nd34_tuned_11bv3.1_250ka.root";


double reweight(int mod, float Enu){
    double wratio;
    int intnue;
    intnue=Enu/NMAX*NBIN;
    if(intnue>=NBIN)intnue=NBIN-1;
    wratio=rwratio[mod][intnue];
    return wratio;
};

void getreweight(){
    fTFRatio   = new TFile(fratio.c_str());
    for(int i=0;i<NMOD;i++){
        char histname[300];
        char histname2[300];
        sprintf(histname,"ing%d_tune_numu",i);
        sprintf(histname2,"ing%d_nom_numu",i);
        tratio[i]= (TH1D*)fTFRatio  ->Get(histname);
        tratio2[i]= (TH1D*)fTFRatio  ->Get(histname2);
        for(int j=0;j<NBIN;j++){
            if(tratio2[i]->GetBinContent(j+1)!=0)
                rwratio[i][j]=(tratio[i]->GetBinContent(j+1))/(tratio2[i]->GetBinContent(j+1));
            else
                rwratio[i][j]=1;
        }
    }
    
};


bool fv(float x, float y, float z){
    bool infv;
    if(fabs(x)<50&&fabs(y)<50&&z>-200)infv=true;
    else infv=false;
    return infv;
};


void MkEnuHist_mva(){
    
    getreweight();
    
    //float xbins[]={0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 30.0};
    float xbins[]={0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 30.0};
    
    //TFile* fmc     = new TFile("/home/kikawa/scraid2/MC/pm/merged_ccqe.root");
    TFile* fmc     = new TFile("/home/cvson/cc1picoh/frkikawa/meAna/ip4tmva/pm_merged_ccqe_tot_addpid_ver3.root");
    //TFile* fflux     = new TFile("/home/kikawa/scraid1/hist_flux/merged.root");
    //Missing this file
    //TFile* fflux     = new TFile("/home/kikawa/ingrid_flux/merged.root");
    //copy over from Kikawa'san output
    TFile* fflux    =   new TFile("cccoh_frkikawa.root");
    
    TTree* tree_mc = (TTree*)fmc->Get("tree");
    //TTree* tree_flux = (TTree*)fflux->Get("h3002");
    
    TH1F *qeint =new TH1F("qeint","qeint",43,xbins);
    TH1F *nqeint =new TH1F("nqeint","nqeint",43,xbins);
    TH1F *qedet =new TH1F("qedet","qedet",43,xbins);
    TH1F *nqedet =new TH1F("nqedet","nqedet",43,xbins);
    //TH1F *flux  = new TH1F("flux","flux",43,xbins);
    
    tree_mc -> Project("qeint","nuE","norm*totcrsne*fv(xnu,ynu,znu)*(inttype==16)");
    tree_mc -> Project("qedet","nuE",Form("norm*totcrsne*(%s)*(inttype==16)",cccohmva));//changehere
    tree_mc -> Project("nqeint","nuE","norm*totcrsne*fv(xnu,ynu,znu)*(inttype!=16)");
    tree_mc -> Project("nqedet","nuE",Form("norm*totcrsne*(%s)*(inttype!=16)",cccohmva));//changehere
    
    //tree_flux ->Project("flux","Enu","reweight(3,Enu)*norm*(xnu>-50&&xnu<50&&ynu>-50&&ynu<50&&idfd==2&&mode<20)/100/100/1980");
    TH1F *flux = fflux->Get("flux");
    TFile* file = new TFile("cccoh_mva.root", "RECREATE" );
    
    qeint ->Write();
    qedet ->Write();
    nqeint ->Write();
    nqedet ->Write();
    flux ->Write();
    file->Write();
    file->Close();
    
    /*
     gStyle->SetOptStat(0);
     gStyle->SetOptTitle(0);
     hdet->SetLineColor(kRed);
     hdet->SetLineWidth(2);
     //hint->SetLineWidth(2);
     //hint->GetYaxis()->SetTitle("# of events [a.u.]");
     hdet->GetYaxis()->SetTitle("# of events [a.u.]");
     //hint->GetXaxis()->SetTitle("E_{#nu} [GeV]");
     hdet->GetXaxis()->SetTitle("E_{#nu} [GeV]");
     //hint->Draw();
     //hdet->Draw("same");
     hdet->Draw();
     
     TLegend* leg=new TLegend(0.45,0.77,0.8.,0.9);
     
     leg  -> SetFillColor  (0);
     leg  -> SetShadowColor(0);
     leg  -> SetLineWidth  (0);
     leg  -> SetLineColor  (0);
     leg  -> SetTextSize   (0.06);
     //leg         -> AddEntry(hint,"# of interactions in FV", "l");
     leg         -> AddEntry(hdet,"# of selected events", "l");
     leg         -> Draw("");
     */
    
}
