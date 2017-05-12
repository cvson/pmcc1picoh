//#define HE
//#define LE
#include "common.h"
#include "cccoh_ana1x.h"
void t2kpre_detsyst_pe_getevt_cccoh_ana1xsig(){
  
  char Output1[100];
  char Output2[100];
  char Output1_cc[100];
  char Output2_cc[100];
  char Output1_nc[100];
  char Output2_nc[100];
  char FileName1[100];
  char FileName2[100];

  sprintf(Output1,"detsyst/pe_ana1xsig_nevent_cccoh1.txt");
  sprintf(Output2,"detsyst/pe_ana1xsig_nevent_cccoh2.txt");
  sprintf(Output1_cc,"detsyst/pe_ana1xsig_nevent_cccoh1_qe.txt");
  sprintf(Output2_cc,"detsyst/pe_ana1xsig_nevent_cccoh2_qe.txt");
  sprintf(Output1_nc,"detsyst/pe_ana1xsig_nevent_cccoh1_nqe.txt");
  sprintf(Output2_nc,"detsyst/pe_ana1xsig_nevent_cccoh2_nqe.txt");


  ofstream output1(Output1);
  ofstream output2(Output2);
  ofstream output1_cc(Output1_cc);
  ofstream output2_cc(Output2_cc);
  ofstream output1_nc(Output1_nc);
  ofstream output2_nc(Output2_nc);
  float ndet1_1,ndet2_1,ndet1_2,ndet2_2;
  float ndet1_1_cc,ndet2_1_cc,ndet1_2_cc,ndet2_2_cc;
  float ndet1_1_nc,ndet2_1_nc,ndet1_2_nc,ndet2_2_nc;
  int nbin; double min, max; char draw[300],select1[300],select2[300],select1_cc[300],select2_cc[300],select1_nc[300],select2_nc[300];
  nbin = 100; min = 0; max = 50;
  //fTFRatio   = new TFile(fratio.c_str());
  //getreweight();
  sprintf(select1,"(%s)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",cccohmva);
  sprintf(select2,"(%s)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",ccincl);
  sprintf(select1_cc,"(%s&&inttype==16)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",cccohmva);
  sprintf(select2_cc,"(%s&&inttype<40)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",ccincl);
  sprintf(select1_nc,"(%s&&inttype!=16)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",cccohmva);
  sprintf(select2_nc,"(%s&&inttype>=40)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",ccincl);


  sprintf(draw,"nuE");
  
  for(int i=0;i<=8;i++){

    sprintf(FileName1,"../../systfsi/frKikawa/MC/pm/pe/merged_ccqe_%d.root",i);
    TFile* fFile1 = new TFile(FileName1);
    TTree* tree1  = (TTree*)fFile1->Get("tree");
    TH1F*  fHdet1_1 = new TH1F("fHdet1_1" , "fHdet1_1" , nbin, min, max);
    TH1F*  fHdet1_2 = new TH1F("fHdet1_2" , "fHdet1_2" , nbin, min, max);
    TH1F*  fHdet1_1_cc = new TH1F("fHdet1_1_cc" , "fHdet1_1_cc" , nbin, min, max);
    TH1F*  fHdet1_2_cc = new TH1F("fHdet1_2_cc" , "fHdet1_2_cc" , nbin, min, max);
    TH1F*  fHdet1_1_nc = new TH1F("fHdet1_1_nc" , "fHdet1_1_nc" , nbin, min, max);
    TH1F*  fHdet1_2_nc = new TH1F("fHdet1_2_nc" , "fHdet1_2_nc" , nbin, min, max);
    tree1 -> Project("fHdet1_1" , draw, select1 );
    tree1 -> Project("fHdet1_2" , draw, select2 );
    tree1 -> Project("fHdet1_1_cc" , draw, select1_cc );
    tree1 -> Project("fHdet1_2_cc" , draw, select2_cc );
    tree1 -> Project("fHdet1_1_nc" , draw, select1_nc );
    tree1 -> Project("fHdet1_2_nc" , draw, select2_nc );
    ndet1_1 = fHdet1_1->GetSumOfWeights();
    ndet1_2 = fHdet1_2->GetSumOfWeights();
    ndet1_1_cc = fHdet1_1_cc->GetSumOfWeights();
    ndet1_2_cc = fHdet1_2_cc->GetSumOfWeights();
    ndet1_1_nc = fHdet1_1_nc->GetSumOfWeights();
    ndet1_2_nc = fHdet1_2_nc->GetSumOfWeights();
    output1<<2.5*(i-4)         <<" "<<ndet1_1<<endl;
    output2<<2.5*(i-4)         <<" "<<ndet1_2<<endl;
    output1_cc<<2.5*(i-4)        <<" "<<ndet1_1_cc<<endl;
    output2_cc<<2.5*(i-4)        <<" "<<ndet1_2_cc<<endl;
    output1_nc<<2.5*(i-4)        <<" "<<ndet1_1_nc<<endl;
    output2_nc<<2.5*(i-4)        <<" "<<ndet1_2_nc<<endl;

  }
}
