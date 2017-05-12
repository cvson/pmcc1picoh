//#define MKPLOT
#define nbin 43
//#include "/home/kikawa/set_plot_style2.C"
TRandom3 rand;

void draw_matrix(float mat[nbin][nbin]){
    //set_plot_style2();
    //gROOT->ProcessLine(".x /home/cvson/rootlogon.C");
    //gROOT->ProcessLine(".L /home/cvson/basicPlotUtil.C");
    
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(0);
    TCanvas *c1 = new TCanvas("c1","c1",0,0,800,600);
    TH2F *h1=new TH2F("h1","h1",nbin,0,nbin,nbin,0,nbin);
    h1->GetZaxis()->SetRangeUser(-0.045,0.045);
    h1->Reset();
    for(int i=0;i<nbin;i++){
        for(int j=0;j<nbin;j++){
            h1->Fill(i+0.0001,j+0.0001,mat[i][j]);
        }
    }
    h1->Draw("colz");
    h1->GetXaxis()->SetTitle("Energy bin");
    h1->GetYaxis()->SetTitle("Energy bin");
    //plot2dcolz(h1,"neuflux_fraccovmatrix");
    c1->Update();
    
    char ans[8];
    fgets(ans,8,stdin);
    
};

void cholcov_conv(float covmat[nbin][nbin], float cholcovmat[nbin][nbin])
{
    memset(cholcovmat,0,sizeof(cholcovmat));
    for ( Int_t j=0; j<nbin; j++ ) {
        Double_t s = covmat[j][j] ;
        for ( Int_t k=0; k<j; k++ ) {
            s -= cholcovmat[j][k]*cholcovmat[j][k] ;
        }
        if(s<0){
            std::cout << "strange !" << j << " " << s << std::endl ;
            exit(0) ;
        }
        cholcovmat[j][j] = sqrt(s) ;
        
        for ( Int_t i=j+1; i<nbin; i++ ) {
            s = covmat[i][j] ;
            for ( Int_t k=0; k<j; k++ ) {
                s -= cholcovmat[i][k]*cholcovmat[j][k] ;
            }
            if ( TMath::Abs(s)<0.000000000001 )
                cholcovmat[i][j] = 0. ;
            else
                cholcovmat[i][j] = s/cholcovmat[j][j] ;
        }
    }
    
};


void FluxErr_ana1x(){
    
    //TFile *fop = TFile::Open("/home/kikawa/for_pm_v3/flux_cov/flux_cov_full.root");
    TFile *fop = TFile::Open("/home/cvson/cc1picoh/syst/flux_cov_full.root");
    TMatrixDSym *mat = (TMatrixDSym*)fop->Get("flux_cov");
    if(mat==NULL){
        cout << "Cannot get matrix from " << fop->GetPath() << endl;
        exit;
    }
    
    float cov_mat[nbin][nbin];
    for(int i=0; i<nbin; i++)
        for(int j=0; j<nbin; j++)
            cov_mat[i][j] = (*mat)(i+258, j+258);
    
#ifdef MKPLOT
    draw_matrix(cov_mat);
#endif
    
    float chol_mat[nbin][nbin];
    cholcov_conv(cov_mat, chol_mat);
    
#ifdef MKPLOT
    draw_matrix(chol_mat);
#endif
    
    int nthrows = 1000000;
    float weight[nbin],nrand[nbin];
    TH1F*  hqeint;
    TH1F*  hqedet;
    TH1F*  hnqeint;
    TH1F*  hnqedet;
    TH1F*  hflux;
    
    //TFile *fccqe  = new TFile("cccoh.root");
    //TFile *fccqe  = new TFile("cccoh_frkikawa.root");
    //TFile *fccqe  = new TFile("cccoh_mva.root");
    TFile *fccqe  = new TFile("cccoh_ana1x.root");
    
    hqeint  = (TH1F*)fccqe  -> Get("qeint");//all signal
    
    hnqeint  = (TH1F*)fccqe  -> Get("nqeint");//all background
    
    hqedet  = (TH1F*)fccqe  -> Get("qedet");//all signal-selected
    
    hnqedet  = (TH1F*)fccqe  -> Get("nqedet");// all background-selected
    
    hflux   = (TH1F*)fccqe  -> Get("flux");
    
    
    //TFile *fout = new TFile("toymc_nom.root","recreate");
    TFile *fout = new TFile("toymc_ana1x.root","recreate");
    
    TTree *tree = new TTree("tree","tree");
    //float pm,ing,pm_int,ing_int,pm_det,ing_det;
    //float pm_ccint,ing_ccint,pm_ccdet,ing_ccdet,pm_ncint,ing_ncint,pm_ncdet,ing_ncdet,pm_cceff,ing_cceff,pm_nceff,ing_nceff,pm_flux,ing_flux;
    
    float qeint,nqeint,
    qedet,nqedet,
    qeeff,nqeeff,
    flux;
    
    tree->Branch("qeint",&qeint,"qeint/F");//all signal interaction
    tree->Branch("nqeint",&nqeint,"nqeint/F");//all background interaction
    
    tree->Branch("qedet",&qedet,"qedet/F");// all selected-signal
    
    tree->Branch("nqedet",&nqedet,"nqedet/F");//all selected-background
    
    tree->Branch("qeeff",&qeeff,"qeeff/F");//efficiency of signal selection
    
    tree->Branch("nqeeff",&nqeeff,"nqeeff/F");//efficiency of background selection
    
    tree->Branch("flux",&flux,"flux/F");
    
    
    //float pm0_ccint=0,ing0_ccint=0,pm0_ccdet=0,ing0_ccdet=0,pm0_ncint=0,ing0_ncint=0,pm0_ncdet=0,ing0_ncdet=0,pm0_cceff=0,ing0_cceff=0,pm0_nceff=0,ing0_nceff=0,pm0_flux=0,ing0_flux=0;
    
    float qeint_nomi=0,nqeint_nomi=0,
    qedet_nomi=0,nqedet_nomi=0,
    qeeff_nomi=0,nqeeff_nomi=0,
    flux_nomi=0;
    
    
    for(int j=0;j<nbin;j++){
        qeint_nomi   += hqeint   -> GetBinContent(j+1);
        nqeint_nomi  += hnqeint  -> GetBinContent(j+1);
        qedet_nomi  += hqedet  -> GetBinContent(j+1);
        nqedet_nomi += hnqedet -> GetBinContent(j+1);
        flux_nomi    += hflux    -> GetBinContent(j+1);
    }
    //make toy simulation
    for(int i=0;i<nthrows;i++){
        if(i%10000==0)cout<<i<<endl;
        //pm_ccint=0,ing_ccint=0,pm_ccdet=0,ing_ccdet=0,pm_ncint=0,ing_ncint=0,pm_ncdet=0,ing_ncdet=0,pm_cceff=0,ing_cceff=0,pm_nceff=0,ing_nceff=0,pm_flux=0,ing_flux=0;
        qeint=0;nqeint=0;
        qedet=0;nqedet=0;
        qeeff=0;nqeeff=0;
        flux=0;
        
        for(int k=0;k<nbin;k++){
            nrand[k]=rand.Gaus();//gaussian random
        }
        
        //fluctuate the weight
        for(int j=0;j<nbin;j++){
            weight[j]=1;
            for(int k=0;k<=j;k++){
                weight[j]+=chol_mat[j][k]*nrand[k];
            }
            
            qeint   += hqeint   -> GetBinContent(j+1)*weight[j];
            nqeint  += hnqeint  -> GetBinContent(j+1)*weight[j];
            qedet  += hqedet  -> GetBinContent(j+1)*weight[j];
            nqedet += hnqedet -> GetBinContent(j+1)*weight[j];
            flux    += hflux    -> GetBinContent(j+1)*weight[j];
            
        }
        
        
        qeint    /=   qeint_nomi;
        nqeint   /=   nqeint_nomi;
        qedet   /=   qedet_nomi;
        nqedet  /=   nqedet_nomi;
        flux     /=   flux_nomi;
        
        qeeff  = qedet/qeint;
        nqeeff = nqedet/nqeint;
        
        tree->Fill();
    }
    tree->Write();
    
    hqedet  ->Write();
    hnqedet ->Write();
    
    fout->Close();
}
