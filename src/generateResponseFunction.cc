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
    std::cout<<"Generate response funcion"<<std::endl;
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
    //TString ipFile = "../../datafsicornorange/merged_ccqe_forResponseFunction.root";
    TString ipFile = "../../datafsipionFS/merged_ccqe_forResponseFunction_pionFS.root";

    //TString opFile = Form("../outputs/testResponseFunction_para%d.root",ithParameter);
   
    baseTreeWeight *pbaseTreeWeight = new baseTreeWeight();
    int ithParameter = 0;
    TString opFile = "../inputs/responsefunction_MACCQE.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 1;
    opFile = "../inputs/responsefunction_MARES.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 13;
    opFile = "../inputs/responsefunction_CC1piE0.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 14;
    opFile = "../inputs/responsefunction_CC1piE1.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 16;
    opFile = "../inputs/responsefunction_CCother.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 22;
    opFile = "../inputs/responsefunction_PilessDcy.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
   
    ithParameter = 23;
    opFile = "../inputs/responsefunction_1piEnuShape.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);

    opFile = "../inputs/responsefunction_AllElse.root";
    pbaseTreeWeight->MakeResponseFunctionAllElse(ipFile,"tree",opFile,v_pedges,v_cthedges);
    //TODO: INCLUDE NuE sample
    
    /*baseTreeWeight *pbaseTreeWeight = new baseTreeWeight();
    std::cout<<" DATA "<<std::endl;
    pbaseTreeWeight->MakeBasicHisto("/home/t2k/cvson/gpfs/ingrid/backup/dataProcess/fix20150420/data_merged_ccqe_addpidFFnew.root","../outputs/basicHisto_data.root");*/
    //pm

    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
