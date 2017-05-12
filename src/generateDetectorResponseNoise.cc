#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <TCanvas.h>
#include <TH1F.h>
#include "baseTreeDet.hh"
using namespace std;

int main(int argc, char *argv[])
{
    string fccqebin = "../inputs/cc1picohbins.txt";
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
    baseTreeDet *pbaseTreeDet = new baseTreeDet();
    TObjArray ipFileArray;
    TObjArray ipFileArraydata;
    const Int_t NFILEPE = 16;
    TFile *pfile;
    for (Int_t ifile=0; ifile<NFILEPE; ifile++) {
        pfile = new TFile(Form("../../systfsi/frKikawa/MC/pm/noise/merged_ccqe_%d.root",ifile));
        ipFileArray.Add(pfile);
    }
   
    
    TString opFile = "../inputs/detresponsefunction_noise.root";
    pbaseTreeDet->MakeMPPCNoiseSyt(&ipFileArray, "tree",opFile,v_pedges,v_cthedges);
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}