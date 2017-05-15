#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <TCanvas.h>
#include <TH1F.h>
#include "baseTreeWeight.hh"
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
    //t2kreweight v1r19 neut 5.1.4.2
   // TString ipFile = "../../datafsipionFS/merged_ccqe_forResponseFunction_pionFS.root";
    //TString opFile = "../outputs/checkT2KReweight_pionFSff.root";

    //t2kreweight v1r25 neut 5.3.2
    TString ipFile = "../../datafsipionFS/rwv1r25_neut5d3d2_run1.root";
    TString opFile = "../outputs/OneSigmaT2KReweight_rwv1r25_neut5d3d2";
   //Int_t isample =val; 
    baseTreeWeight *pbaseTreeWeight = new baseTreeWeight();
    pbaseTreeWeight->PlotOneSigma(ipFile,"tree",opFile, isample);
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
