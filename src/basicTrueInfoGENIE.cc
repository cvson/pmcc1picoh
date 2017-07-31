#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <TCanvas.h>
#include <TH1F.h>
#include "baseTreeTrueInfo.hh"
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

    //basic true information
    TString ipFile = "../../datafsipionFS/genie_merged_pmmc_ccqe_trueinfo.root";
    TString opFile = "../outputs/trueinfo_genie";
   //Int_t isample =val; 
    baseTreeTrueInfo *pbaseTreeTrueInfo = new baseTreeTrueInfo();
    pbaseTreeTrueInfo->MakeBasicHistoBySample(ipFile,"tree",opFile, isample,true);
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}