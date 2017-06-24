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
    //TString ipFile = "../../datafsipionFS/merged_ccqe_forResponseFunction_pionFS.root";
	TString ipFile = "../../datafsipionFS/all_merged_rwv1r25_neut5d3d2_coh_byorder.root";
    //TString opFile = Form("../outputs/testResponseFunction_para%d.root",ithParameter);
   
    baseTreeWeight *pbaseTreeWeight = new baseTreeWeight();
    int ithParameter = 4;
    TString opFile = "../inputs/responsefunction_MECNorm.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 6;
    opFile = "../inputs/responsefunction_MECNorm.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 7;
    opFile = "../inputs/responsefunction_CA5RES.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 8;
    opFile = "../inputs/responsefunction_MaNFFRES.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 9;
    opFile = "../inputs/responsefunction_BgSclRES.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    
    ithParameter = 14;
    opFile = "../inputs/responsefunction_dismpishp.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
   
    ithParameter = 18;
    opFile = "../inputs/responsefunction_FrAbs_pi.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);

   ithParameter = 20;
    opFile = "../inputs/responsefunction_FrInelLow_pi.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);

ithParameter = 21;
    opFile = "../inputs/responsefunction_FrPiProd_pi.root";
    pbaseTreeWeight->MakeResponseFunction(ipFile,"tree",opFile,v_pedges,v_cthedges,ithParameter);
    /*opFile = "../inputs/responsefunction_AllElse.root";
    pbaseTreeWeight->MakeResponseFunctionAllElse(ipFile,"tree",opFile,v_pedges,v_cthedges);
    */
    //TODO: INCLUDE NuE sample
    
    //pm

    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
