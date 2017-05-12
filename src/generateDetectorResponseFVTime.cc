#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <TCanvas.h>
#include <TH1F.h>
#include "baseTree.hh"
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
    baseTree *pbaseTree = new baseTree();
    
    //TString ipFile = "../../datafsi/datamc_merged_ccqe_addpidFFnew.root";
    TString ipFile = "../../datafsipionFS/datamc_pionFSpm_merged_ccqe_addpidFFnew_addnue.root";
    TString opFile = "../inputs/detresponse_FVTime.root";
    pbaseTree->GenerateDetSyst(ipFile, "tree",opFile,v_pedges,v_cthedges);
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
