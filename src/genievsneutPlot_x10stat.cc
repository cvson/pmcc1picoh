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
    //string fmcInputFile = "../../datafsi/mcgenie_merged_ccqe_tot_addpidFFnew.root";
    //string fdtInputFile = "../../datafsi/mc_merged_ccqe_addpidFFnew.root";
    string fccqebin = "../inputs/cc1picohbins.txt";
    
    //string fnameout = "../outputs/neutvsgenie_sample_newbin2_fsicomb.root";
    
    /*string fmcInputFile = "../../datafsipionFS/mconly_pionFSpm_merged_ccqe_addpidFFnew_addnue.root";
    string fdtInputFile = "../../datafsipionFS/mconly_genie_pionFSpm_merged_ccqe_addpidFFnew_addnue.root";
    string fnameout = "../outputs/neutvsgenie_sample_ana1x50mepionFS_5binsptheta.root";
    */
    //should change baseTree::GetInteractionType 
    string fmcInputFile = "../../datafsipionFS/mconly_genie_pionFSpm_merged_ccqe_addpidFFnew_addnue.root";
    string fdtInputFile = "../../datafsipionFS/mconly_pionFSpm_merged_ccqe_addpidFFnew_addnue.root";
    string fnameout = "../outputs/genievsneut_sample_ana1x50mepionFS_5binsptheta_x10stat.root";

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
    //double potData = 6.04193507503274721e20;
    double potData = 6.0e21;
    double potMC = 3950*1.e21;
    //double potGENIE = potMC;
    FitSample sam1(0, "SIG",v_pedges, v_cthedges,tdata);
    sam1.SetNorm(potData/potMC);
    samples.push_back(&sam1);
    
    FitSample sam2(1, "CRI",v_pedges, v_cthedges,tdata);
    sam2.SetNorm(potData/potMC);
    samples.push_back(&sam2);
    
    FitSample sam3(2, "CRII",v_pedges, v_cthedges,tdata);
    sam3.SetNorm(potData/potMC);
    samples.push_back(&sam3);
    
    FitSample sam4(3, "CRIII",v_pedges, v_cthedges,tdata);
    sam4.SetNorm(potData/potMC);
    samples.push_back(&sam4);
    

    
    //Make it Manually
    const char *bsnameTag[4] = {"SIG", "CRI", "CRII", "CRIII"};
    
    //THIS IS RELOAD SAMPLE from MC tree
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
    //THIS is FAKING FILLEVENT HISTO for data, please ignore *_pred and *_mc
    //this is suffered from a similar scaling from norm.
    //THIS IS RELOAD sample with fake data
    baseTree *pbaseTreedt = new baseTree();
    pbaseTreedt->Init(tdata);
    pbaseTreedt->GetEvents(samples);
    for(size_t s=0;s<samples.size();s++){
        ((FitSample*)(samples[s]))->FillEventHisto(4);
        ((FitSample*)(samples[s]))->Write(fout,bsnameTag[s],0);
        ((FitSample*)(samples[s]))->ClearEvents();
    }
    fout->Close();
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
