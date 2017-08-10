#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <TCanvas.h>
#include <TH1F.h>
#include <TFile.h>
#include <TMath.h>
#include <TMatrixT.h>
#include <TMatrixTSym.h>
#include <TVectorT.h>
#include <TDecompChol.h>

#include "baseTree.hh"
#include "FitSample.hh"
#include "FluxParameters.hh"
#include "ScaleParameters.hh"
#include "XsecParameters.hh"
#include "DetParameters.hh"
#include "Vertex0piParameters.hh"
#include "Vertex1piParameters.hh"
#include "XsecFitter.hh"

using namespace std;

int main(int argc, char *argv[])
{
    string fmcInputFile = "../../datafsipionFS/mconly_neut5d3d2_20170529.root";
    //string fdtInputFile = "../../datafsicornorange/mc_genie_merged_ccqe_addpidFFnew_addnue.root";
    string fdtInputFile = "../../datafsipionFS/mconly_genie_20170529.root";
    string fccqebin = "../inputs/cc1picohbins.txt";
    string fnameout = "../outputs/testFit_onesample_statfluc.root";
    
    //systematics
    string ffluxcov     = "../inputs/flux_cov_full.root";
    int seed        = 87;
    
    char cc;
    while((cc = getopt(argc, argv, "o:s:h:")) != -1)
    {
        switch(cc)
        {
                
            case 'o': //output file
                fnameout = optarg;
                break;
                
            case 's': //random seed
                seed = atoi(optarg);
                break;
                
            case 'h': //help
                std::cout << "USAGE: "
                << argv[0] << " OPTIONS:" << std::endl
                << "-o : \tset name of output file" << std::endl
                << "-s : \tset random seed" << std::endl;
                return 0;
                break;
            default:
                return 1;
        }
    }
    
    /*********************************************************************************/
    
    TFile *fdata = new TFile(TString(fdtInputFile));
    TTree *tdata = (TTree*)(fdata->Get("tree"));
    
    std::vector<std::pair<double, double> > v_pedges;
    std::vector<std::pair<double, double> > v_cthedges;
    ifstream fin(fccqebin.c_str());
    assert(fin.is_open());
    string line;
    while (getline(fin, line))
    {
        stringstream ss(line);
        double p1, p2, cth1, cth2;
        if(!(ss>>cth1>>cth2>>p1>>p2))
        {
            cerr<<"Bad line format: "<<endl
            <<"     "<<line<<endl;
            continue;
        }
        v_pedges.push_back(make_pair(p1,p2));
        v_cthedges.push_back(make_pair(cth1,cth2));
    }
    fin.close();
    
    TFile *fout = TFile::Open(fnameout.c_str(), "RECREATE");
    cout<<"file open"<<endl;
    
    //add data
    vector<AnaSample*> samples;
    double potData = 6.04193507503274721e20;
    double potMC = 3974*1.e21;
    //need to put in ORDER 0, 1, 4, 5, 2, 3
    //consistent with detector covariance matrix ../macros/plotAllDetUncertainty.C
    FitSample sam1(0, "SIG",v_pedges, v_cthedges,tdata);
    sam1.SetNorm(potData/potMC);
    samples.push_back(&sam1);
    
    FitSample sam2(1, "CRI",v_pedges, v_cthedges,tdata);
    sam2.SetNorm(potData/potMC);
    samples.push_back(&sam2);
    
    
    FitSample sam3(2, "CRII",v_pedges, v_cthedges,tdata);
    sam3.SetNorm(potData/potMC);
    samples.push_back(&sam3);
    
    
    /*FitSample sam4(3, "CRIII",v_pedges, v_cthedges,tdata);
    sam4.SetNorm(potData/potMC);
    samples.push_back(&sam4);*/
    

    
    
    baseTree *pbaseTree = new baseTree();
    TFile *pipmcfile = new TFile(TString(fmcInputFile));
    TTree *pipmctree = (TTree*)pipmcfile->Get("tree");
    pbaseTree->Init(pipmctree);
    pbaseTree->GetEvents(samples);
    
    //get brakdown by reaction
    cout<<"Number of Sample "<<samples.size()<<endl;
    for(size_t s=0;s<samples.size();s++){
        ((FitSample*)(samples[s]))->GetSampleBreakdown(fout,"nominal");
    }
    
    cout<<"nominal MC done"<<endl;
    /********************************************************************************/
    /*  FIT PARAMETER                                                               */
    /********************************************************************************/
    //define fit param classes
    vector<AnaFitParameters*> fitpara;
    /*************************************** Scale start *****************************/
    //CC1picoh scale parameters
    ScaleParameters scalepara(fccqebin.c_str());
    scalepara.InitEventMap(samples);
    fitpara.push_back(&scalepara);
    
    cout<<"CC1picoh scale parameters DONE"<<endl;
    /*************************************** Scale end ********************************/

	       /*************************************** Vertex0pi start *****************************/
    //CC0pi migration parameters
    Vertex0piParameters vertex0pipara(fccqebin.c_str());
    vertex0pipara.InitEventMap(samples);
    fitpara.push_back(&vertex0pipara);

    cout<<"Vertex 0pi parameters DONE"<<endl;

    /*************************************** Vertex0pi end ********************************/

      /*************************************** Vertex1pi start *****************************/
    //CC1pi migration parameters
    Vertex1piParameters vertex1pipara(fccqebin.c_str());
    vertex1pipara.InitEventMap(samples);
    fitpara.push_back(&vertex1pipara);

    cout<<"Vertex 1pi parameters DONE"<<endl;

    /*************************************** Vertex1pi end ********************************/
    /*************************************** FLUX start *******************************/
    /*TFile *finfluxcov = TFile::Open(ffluxcov.c_str());
     Int_t nbinhistflux = 43;
     const Double_t xbinshistflux[]={0, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 2.1, 2.2, 2.3, 2.4, 2.5, 2.6, 2.7, 2.8, 2.9, 3.0, 3.1, 3.2, 3.3, 3.4, 3.5, 3.6, 3.7, 3.8, 3.9, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 30.0};
     //setup enu bins and covm for flux
     TAxis *nd_numu_bins = new TAxis(nbinhistflux,xbinshistflux);
     TMatrixDSym *cov_flux_in   = (TMatrixDSym*)finfluxcov->Get("flux_cov");
     TMatrixDSym cov_flux(nd_numu_bins->GetNbins());
     vector<double> enubins;
     enubins.push_back(nd_numu_bins->GetBinLowEdge(1));
     for(int i=0;i<nd_numu_bins->GetNbins();i++)
     {
     enubins.push_back(nd_numu_bins->GetBinUpEdge(i+1));
     for(int j=0;j<nd_numu_bins->GetNbins();j++)
     {
     cov_flux(i, j) = (*cov_flux_in)(i+258,j+258);
     }
     }
     
     finfluxcov->Close();
     
     FluxParameters fluxpara(enubins);
     fluxpara.SetCovarianceMatrix(&cov_flux);
     fluxpara.InitEventMap(samples);
     fitpara.push_back(&fluxpara);
     cout<<"Flux parameters DONE"<<endl;*/
    /*************************************** FLUX end **********************************/
    
    /*************************************** XSec start *******************************/
    vector<TFile*> responsefunctions;
    TFile* MACCQErespfunc = new TFile("../inputs/responsefunction_MECNorm.root");
    responsefunctions.push_back(MACCQErespfunc);
    
    TFile* MAResrespfunc = new TFile("../inputs/responsefunction_MACCQE.root");
    responsefunctions.push_back(MAResrespfunc);
    
    TFile* CC1piE0respfunc = new TFile("../inputs/responsefunction_CA5RES.root");
    responsefunctions.push_back(CC1piE0respfunc);
    
    TFile* CC1piE1respfunc = new TFile("../inputs/responsefunction_MaNFFRES.root");
    responsefunctions.push_back(CC1piE1respfunc);
    
    TFile* CCOthrespfunc = new TFile("../inputs/responsefunction_BgSclRES.root");
    responsefunctions.push_back(CCOthrespfunc);
    
    TFile* PilessDcyrespfunc = new TFile("../inputs/responsefunction_dismpishp.root");
    responsefunctions.push_back(PilessDcyrespfunc);
    
    
    TMatrixDSym cov_xsec(6);
    
    cov_xsec(0,0) = 1.0; //MACCQE
    cov_xsec(0,1) = 0;
    cov_xsec(0,2) = 0;
    cov_xsec(0,3) = 0;//MARes-CC1piE0
    cov_xsec(0,4) = 0;
    cov_xsec(0,5) = 0;
    
    cov_xsec(1,1) = 1.0; //THIS NOT update? 0.0121
    cov_xsec(1,2) = 0;//MARES vs CC1piE0 Figure 20 TN 108
    cov_xsec(1,3) = 0;
    cov_xsec(1,4) = 0;
    cov_xsec(1,5) = 0;
    
    cov_xsec(2,2) = 1.0; //CC1piE0
    cov_xsec(2,3) = 0;
    cov_xsec(2,4) = 0;
    cov_xsec(2,5) = 0;
    
    cov_xsec(3,3) = 1.0; //CC1piE1
    cov_xsec(3,4) = 0;
    cov_xsec(3,5) = 0;
    
    cov_xsec(4,4) = 1.0; //CCother
    cov_xsec(4,5) = 0;
    
    cov_xsec(5,5) = 1.0; //PilessDcy
    
    
    
    
    
    
    XsecParameters xsecpara;
    xsecpara.SetCovarianceMatrix(&cov_xsec);
    xsecpara.StoreResponseFunctions(responsefunctions, v_pedges, v_cthedges);
    xsecpara.InitEventMap(samples);
    fitpara.push_back(&xsecpara);
    
    /*************************************** XSec end **********************************/
    
    /*************************************** Detector start **********************************/
    string fdetcov = "../inputs/detectorAll_5bptheta_covariance_matrix.root";  //USING NEW BINNING DET MATRIX
     TFile *findetcov = TFile::Open(fdetcov.c_str()); //contains flux and det. systematics info
     
     TMatrixDSym *cov_det_in   = (TMatrixDSym*)findetcov->Get("detector_covmat_case0");
     TMatrixDSym cov_det(cov_det_in->GetNrows());
     for(size_t m=0; m<cov_det_in->GetNrows(); m++){
     for(size_t k=0; k<cov_det_in->GetNrows(); k++){
     cov_det(m, k) = (*cov_det_in)(m,k);
     }
     }
     
     findetcov->Close();
     
     DetParameters detpara(samples,"../inputs/cc1picohbins.txt","par_det");
     detpara.SetCovarianceMatrix(&cov_det);
     detpara.InitEventMap(samples);
     fitpara.push_back(&detpara);
    /*************************************** Detector end **********************************/
    /********************************************************************************/
    /*  FITTER                                                                      */
    /********************************************************************************/
    //Instantiate fitter obj
    XsecFitter xsecfit(seed);
    //init w/ para vector
    xsecfit.InitFitter(fitpara);
    
    xsecfit.SetSaveMode(fout, 1);
    
    //do fit: 1 = generate toy dataset from nuisances (WITH stat fluct)
    //        2 = fake data from MC or real data (+ stat fluct)
    //        3 = no nuisance sampling only stat fluctuation
    //xsecfit.Fit(samples, 1);
    xsecfit.Fit(samples, 2);
    
    //xsecfit.Fit(samples, 3);
    
    fout->Close();
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
