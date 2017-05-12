//#define MKPLOT
#define nbin 43
TRandom3 rand;

void draw_matrix(float mat[nbin][nbin]){
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


void FluxErrCCcoh(){

    TFile *fop = TFile::Open("/home/kikawa/for_pm/flux_cov/flux_cov_full.root");
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
    TH1F*  hcccoh;
    TH1F*  hccincl;
    TFile *fcccoh  = new TFile("/home/kikawa/macros/cccoh.root");

    hcccoh  = (TH1F*)fcccoh  -> Get("hdet_coh");
    hccincl  = (TH1F*)fcccoh  -> Get("hdet_incl");

    TFile *fout = new TFile("toymc_cccoh.root","recreate");
    TTree *tree = new TTree("tree","tree");

    float cccoh,ccincl;
    tree->Branch("cccoh",&cccoh,"cccoh/F");
    tree->Branch("ccincl",&cccoh,"ccinl/F");
  
    float  ncccoh=0,nccincl=0;
    for(int j=0;j<nbin;j++){
        ncccoh += hcccoh -> GetBinContent(j+1);
        nccincl += hccincl -> GetBinContent(j+1);
    }

    for(int i=0;i<nthrows;i++){
        if(i%10000==0)cout<<i<<endl;
        cccoh=0;ccincl=0;

        for(int k=0;k<nbin;k++){
            nrand[k]=rand.Gaus();
        }

        for(int j=0;j<nbin;j++){
            weight[j]=1;
            for(int k=0;k<=j;k++){
                weight[j]+=chol_mat[j][k]*nrand[k];
            }
            cccoh += hcccoh -> GetBinContent(j+1)*weight[j];
            ccincl += hccincl-> GetBinContent(j+1)*weight[j];
        }

        cccoh = cccoh / ncccoh;
        ccincl = ccincl / nccincl;

        tree->Fill();
    }

    tree->Write();
    fout->Close();
}
