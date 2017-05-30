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


     //pbaseTree->MakeBasicHistoBySamplev532("../../datafsipionFS/datamc_neut5d3d2_merged_pmmc_ccqe_bugfix_3974files.root","../outputs/basicHisto_datamcfsi_finalcomb_sam4testv2_addnue_morepid_ana1x_pionFSnewBD_50mevff_antipid_neut5d3d2_all",isample);
	//datamc_neut5d3d2_20170307.root only change on numu
       //pbaseTree->MakeBasicHistoBySamplev532("../../datafsipionFS/datamc_neut5d3d2_20170307.root","../outputs/basicHisto_neut5d3d2_20170307",isample);
      //datamc_neut5d3d2_20170529.root --> include change in numubar, nue, ingrid as well, except wall
	pbaseTree->MakeBasicHistoBySamplev532("../../datafsipionFS/datamc_neut5d3d2_20170529.root","../outputs/basicHisto_neut5d3d2_20170529",isample);
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
