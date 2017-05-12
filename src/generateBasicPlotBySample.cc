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
int isample;
        if (argc >= 2)
    {
        std::istringstream iss( argv[1] );
        //int isample;

        if (iss >> isample)
        {
        std::cout<<"proceeding sample "<<isample<<std::endl;
            // Conversion successful
        }
    }

    std::cout<<"Generate basic plots for sample "<<isample<<std::endl;
	std::cout<<"Refer sample in baseTree.hh"<<std::endl;
    //TODO: INCLUDE NuE sample
    
    baseTree *pbaseTree = new baseTree();
    //data
    std::cout<<" DATA "<<std::endl;

     //pbaseTree->MakeBasicHistoBySample("../../datafsipionFS/datamc_pionFSpm_merged_ccqe_addpidFFnew_addnue.root","../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_all",isample);

    pbaseTree->MakeBasicHistoBySample("../../datafsipionFS/datamc_neut5d1d4d2_20170307.root","../outputs/basicHisto_20170307",isample);
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
