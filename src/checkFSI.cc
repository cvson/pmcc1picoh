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
    //require both two forward
    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_oldsel_correctm2trk.root");
    
    //vertexactivity >475
    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_oldsel_correctm2trk_optimized.root");
    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_fsisel_finalcomb.root");
    
    //add nue-sample and more topologies to check
    pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew_addnue.root","../outputs/checkFSI_fsisel_finalcomb_addnue.root");
    
    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_fsisel_final.root");
    
    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_fsiselopt8.root");
    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_fsiselopt9.root");

    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_fsiselopt10.root");
    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_fsiselopt11.root");
    //pbaseTree->CheckFSI("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/checkFSI_fsiselopt12.root");
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
