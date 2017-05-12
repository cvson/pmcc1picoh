#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>
#define nbin 43

#include <TCanvas.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TFile.h>
#include <TMath.h>
#include <TMatrixT.h>
#include <TMatrixTSym.h>
#include <TVectorT.h>
#include <TDecompChol.h>

using namespace std;

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

int main(int argc, char *argv[])
{
    string ffluxcov     = "../inputs/flux_cov_full.root";
    string fnameout = "../outputs/testFluxCovariance.root";
    TFile *finfluxcov = TFile::Open(ffluxcov.c_str()); //contains flux and det. systematics info
    /*************************************** FLUX *****************************************/
    //int nbin = 43;
    const Double_t xbins[]={0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 30.0};
    //setup enu bins and covm for flux
    TMatrixDSym *cov_flux_in   = (TMatrixDSym*)finfluxcov->Get("flux_cov");
    if(cov_flux_in==NULL){
        cout << "Cannot get matrix from " << finfluxcov->GetPath() << endl;
        exit;
    }
    
    float cov_mat[nbin][nbin];
    for(int i=0; i<nbin; i++)
        for(int j=0; j<nbin; j++)
            cov_mat[i][j] = (*cov_flux_in)(i+258, j+258);
    
    TH2F *h1=new TH2F("h1","",nbin,0,nbin,nbin,0,nbin);
    for(int i=0;i<nbin;i++){
        for(int j=0;j<nbin;j++){
            h1->Fill(i+0.0001,j+0.0001,cov_mat[i][j]);
        }
    }
    //this is for test
    TAxis *nd_numu_bins = new TAxis(nbin,xbins);
    vector<double> enubins;
    enubins.push_back(nd_numu_bins->GetBinLowEdge(1));
    for(int i=0;i<nd_numu_bins->GetNbins();i++)
    {
        enubins.push_back(nd_numu_bins->GetBinUpEdge(i+1));
        cout<<"at "<<i<<" enubins "<<enubins.at(i)<<endl;
    }
    //////////////////////
    h1->GetXaxis()->SetTitle("Energy bins");
    h1->GetYaxis()->SetTitle("Energy bins");
    
    float chol_mat[nbin][nbin];
    cholcov_conv(cov_mat, chol_mat);
    TH2F *h2=new TH2F("h2","",nbin,0,nbin,nbin,0,nbin);
    for(int i=0;i<nbin;i++){
        for(int j=0;j<nbin;j++){
            h2->Fill(i+0.0001,j+0.0001,chol_mat[i][j]);
        }
    }
    h2->GetXaxis()->SetTitle("Energy bins");
    h2->GetYaxis()->SetTitle("Energy bins");
    /*****************************************************************************************/
    TFile *fout = TFile::Open(fnameout.c_str(), "RECREATE");
    cout<<"file open"<<endl;
    h1->Write("hfluxcovmatrix");
    h2->Write("hfluxcovmatrix_chol");
    h1->Delete();
    h2->Delete();
    fout->Close();
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}