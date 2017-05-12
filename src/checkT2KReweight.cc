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
    TString ipFile = "../../datafsipionFS/merged_ccqe_forResponseFunction_pionFS.root";
    
    TString opFile = "../outputs/checkT2KReweight_pionFSff.root";
   
    baseTreeWeight *pbaseTreeWeight = new baseTreeWeight();
    pbaseTreeWeight->checkWeight(ipFile,"tree",opFile);
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
