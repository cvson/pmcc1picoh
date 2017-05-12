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
    std::cout<<"Generate basic plots"<<std::endl;
    //TODO: INCLUDE NuE sample
    
    baseTree *pbaseTree = new baseTree();
    //data
    std::cout<<" DATA "<<std::endl;
    
    pbaseTree->CheckVeract("../../datafsi/datamc_merged_ccqe_addpidFFnew_addnue.root","../outputs/CheckVeract_fsisel_finalcomb_addnue.root");
    
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
