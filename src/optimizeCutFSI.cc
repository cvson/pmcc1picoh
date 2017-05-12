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
    //pbaseTree->OptimizeFSICut("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/optimizeCutFSI.root");
   // pbaseTree->OptimizeFSICut("../../datafsi/datamc_merged_ccqe_addpidFFnew.root","../outputs/optimizeCutFSI_FSI.root");
   
    pbaseTree->OptimizeFSICut("../../datafsi/datamc_merged_ccqe_addpidFFnew_addnue.root","../outputs/optimizeCutFSI_FSI_addnue.root");
 
   //pm
    /*std::cout<<" PM "<<std::endl;
    pbaseTree->MakeBasicHisto("../../data/pm_merged_ccqe_tot_addpidFFnew.root","../outputs/basicHisto_pm.root");
    
    //pmbar
    std::cout<<" PMBAR "<<std::endl;
    pbaseTree->MakeBasicHisto("../../data/pmbar_merged_ccqe_addpidFFnew.root","../outputs/basicHisto_pmbar.root");
    
    //ingrid
    std::cout<<" INGRID "<<std::endl;
    pbaseTree->MakeBasicHisto("../../data/ingrid_merged_nd3_ccqe_tot_addpidFFnew.root","../outputs/basicHisto_ingrid.root");
    
    //wall
    std::cout<<" WALL "<<std::endl;
    pbaseTree->MakeBasicHisto("../../data/wall_merged_ccqe_tot_addpidFFnew.root","../outputs/basicHisto_wall.root");
    
    //genie
    std::cout<<" GENIE "<<std::endl;
    pbaseTree->MakeBasicHisto("../../data/genie_merged_ccqe_tot_addpidFFnew.root","../outputs/basicHisto_genie.root");
    */
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
