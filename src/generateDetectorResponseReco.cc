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
    TObjArray ipFileArray;
    TObjArray ipFileArraydata;
    const Int_t NFILEPE = 12;
    TFile *pfile;
    /*for (Int_t ifile=0; ifile<NFILEPE; ifile++) {
        pfile = new TFile(Form("../../systfsi/frKikawa/MC/pm/pe/merged_ccqe_%d.root",ifile));
        ipFileArray.Add(pfile);
    }*/
    //0
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_30_85_4_2_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //1
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_75_4_2_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //2
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_85_2_2_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //3
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_85_3_2_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //4
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_85_4_2_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //5
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_85_4_2_175_ccqe.root");
    ipFileArray.Add(pfile);
    
    //6
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_85_4_2_200_ccqe.root");
    ipFileArray.Add(pfile);
    
    //7
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_85_4_3_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //8
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_85_4_4_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //9
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_85_5_2_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //10
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_35_95_4_2_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //11
    pfile = new TFile("../../systfsi/frKikawa/MC/pm/sys/merged_40_85_4_2_150_ccqe.root");
    ipFileArray.Add(pfile);
    
    //add for data
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_30_85_4_2_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //1
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_75_4_2_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //2
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_85_2_2_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //3
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_85_3_2_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //4
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_85_4_2_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //5
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_85_4_2_175_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //6
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_85_4_2_200_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //7
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_85_4_3_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //8
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_85_4_4_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //9
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_85_5_2_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //10
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_35_95_4_2_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    //11
    pfile = new TFile("../../systfsi/frKikawa/data/sys/merged_40_85_4_2_150_ccqe.root");
    ipFileArraydata.Add(pfile);
    
    TString opFile = "../inputs/detresponsefunction_reco.root";
    pbaseTreeDet->MakeResponseFunctionReco(&ipFileArray, &ipFileArraydata, "tree",opFile,v_pedges,v_cthedges);
    
    
    std::cout<<"Processing successfully"<<std::endl;
    return 0;
}