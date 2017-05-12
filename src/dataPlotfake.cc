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
#include "XsecFitter.hh"

using namespace std;

int main(int argc, char *argv[])
{
    //this merging all MC file <-- missing Nue
    string fmcInputFile = "../../data/mc_merged_ccqe_addpidFFnew.root";
    //string fdtInputFile = "../../data/data_merged_ccqe_addpidFFnew.root";
    string fdtInputFile = "../../data/mc_merged_ccqe_addpidFFnew.root";
    //string fccqebin = "../inputs/ccqebins_Dec2014.txt";
    string fccqebin = "../inputs/cc1picohbins.txt";
    
    //string fnameout = "../outputs/test.root";
    //string fnameout = "../outputs/testFit_SIGsample.root";
    //string fnameout = "../outputs/testFit_allsample.root";
    //string fnameout = "../outputs/testFit_twosample.root";
    //string fnameout = "../outputs/mcdata_sample.root";
    string fnameout = "../outputs/mcdata_sample_newbin_fake.root";
    //systematics
    string ffluxcov     = "../inputs/flux_cov_full.root";
    
    //int seed        = 1019;
    int seed        = 87;
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
    double potMC = 3950*1.e21;
    FitSample sam1(0, "SIG",v_pedges, v_cthedges,tdata);
    sam1.SetNorm(potData/potMC);
    samples.push_back(&sam1);
    
    FitSample sam2(1, "CRI",v_pedges, v_cthedges,tdata);
    sam2.SetNorm(potData/potMC);
    samples.push_back(&sam2);
    
    FitSample sam3(2, "CRIIA",v_pedges, v_cthedges,tdata);
    sam3.SetNorm(potData/potMC);
    samples.push_back(&sam3);
    
    FitSample sam4(3, "CRIIB",v_pedges, v_cthedges,tdata);
    sam4.SetNorm(potData/potMC);
    samples.push_back(&sam4);
    
    FitSample sam5(4, "CRIIC",v_pedges, v_cthedges,tdata);
    sam5.SetNorm(potData/potMC);
    samples.push_back(&sam5);
    
    FitSample sam6(5, "More2trk",v_pedges, v_cthedges,tdata);
    sam6.SetNorm(potData/potMC);
    samples.push_back(&sam6);
    
    FitSample sam7(6, "Onetrk",v_pedges, v_cthedges,tdata);
    sam7.SetNorm(potData/potMC);
    samples.push_back(&sam7);
    
    //Make it Manually
    const char *bsnameTag[7] = {"SIG", "CRI", "CRIIA", "CRIIB", "CRIIC", "More2trk", "Onetrk"};
    
    baseTree *pbaseTree = new baseTree();
    TFile *pipmcfile = new TFile(TString(fmcInputFile));
    TTree *pipmctree = (TTree*)pipmcfile->Get("tree");
    pbaseTree->Init(pipmctree);
    pbaseTree->GetEvents(samples);
    
    //get brakdown by reaction
    cout<<"Number of Sample "<<samples.size()<<endl;
    for(size_t s=0;s<samples.size();s++){
        ((FitSample*)(samples[s]))->GetSampleBreakdown(fout,"nominal");
        
        ((FitSample*)(samples[s]))->ClearEvents();
    }
    
    
    cout<<"nominal MC done"<<endl;
    
    //for data plot
    baseTree *pbaseTreedt = new baseTree();
    pbaseTreedt->Init(tdata);
    pbaseTreedt->GetEvents(samples);
    for(size_t s=0;s<samples.size();s++){
        ((FitSample*)(samples[s]))->FillEventHisto(3);
        ((FitSample*)(samples[s]))->Write(fout,bsnameTag[s],0);
        ((FitSample*)(samples[s]))->ClearEvents();
    }
    fout->Close();
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
