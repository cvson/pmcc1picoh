#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <sstream>
#include <assert.h>

#include <TCanvas.h>
#include <TH1F.h>
#include "baseTreeDet.hh"
using namespace std;

int main(int argc, char *argv[])
{
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
    baseTreeDet *pbaseTreeDet = new baseTreeDet();
    //this is with tuned pe as function of muon angle
    TString pfile = "../../datafsipionFS/datamc_pevartot_merged_ccqe_addpidFFnew_addnue.root";
    TString opFile = "../inputs/detresponsefunction_pevar_nom.root";
   pbaseTreeDet->MakeSingleHisto(pfile,"tree",opFile,v_pedges,v_cthedges,0); 
   //change veact in baseTreeDet::MakeSingleHisto
    opFile = "../inputs/detresponsefunction_pevar_shiftplus.root";
    pbaseTreeDet->MakeSingleHisto(pfile,"tree",opFile,v_pedges,v_cthedges,1);
   opFile = "../inputs/detresponsefunction_pevar_shiftminus.root";
   pbaseTreeDet->MakeSingleHisto(pfile,"tree",opFile,v_pedges,v_cthedges,-1); 
   //to make nominal with nominal MC 
   pfile = "../../datafsipionFS/datamc_pionFSpm_merged_ccqe_addpidFFnew_addnue.root";
   opFile = "../inputs/detresponsefunction_nominal.root";
   pbaseTreeDet->MakeSingleHisto(pfile,"tree",opFile,v_pedges,v_cthedges,0);
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}
