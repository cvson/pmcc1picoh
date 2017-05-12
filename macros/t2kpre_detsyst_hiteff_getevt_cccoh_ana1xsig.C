//#define HE
//#define LE

#include "cccoh_ana1x.h"

void t2kpre_detsyst_hiteff_getevt_cccoh_ana1xsig(){
  
  char Output1[100];
  char Output2[100];
  char Output1_cc[100];
  char Output2_cc[100];
  char Output1_nc[100];
  char Output2_nc[100];
  char FileName[100];
  char HitFile[100];

  sprintf(Output1,"detsyst/hiteff_ana1xsig_nevent_cccoh1.txt");
  sprintf(Output2,"detsyst/hiteff_ana1xsig_nevent_cccoh2.txt");
  sprintf(Output1_cc,"detsyst/hiteff_ana1xsig_nevent_cccoh1_qe.txt");
  sprintf(Output2_cc,"detsyst/hiteff_ana1xsig_nevent_cccoh2_qe.txt");
  sprintf(Output1_nc,"detsyst/hiteff_ana1xsig_nevent_cccoh1_nqe.txt");
  sprintf(Output2_nc,"detsyst/hiteff_ana1xsig_nevent_cccoh2_nqe.txt");


  ofstream output1(Output1);
  ofstream output2(Output2);
  ofstream output1_cc(Output1_cc);
  ofstream output2_cc(Output2_cc);
  ofstream output1_nc(Output1_nc);
  ofstream output2_nc(Output2_nc);
  float ndet1,ndet2;
  float ndet1_cc,ndet2_cc;
  float ndet1_nc,ndet2_nc;
  float neff;
  float neff_cc;
  float neff_nc;
  int nbin; double min, max; char draw[300], select1[300], select2[300],select1_cc[300],select2_cc[300],select1_nc[300],select2_nc[300];
  nbin = 100; min = 0; max = 50;

  sprintf(select1,"(%s)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",cccohmva);
  sprintf(select2,"(%s)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",ccincl);
  sprintf(select1_cc,"(%s&&inttype==16)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",cccohmva);
  sprintf(select2_cc,"(%s&&inttype==1)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",ccincl);
  sprintf(select1_nc,"(%s&&inttype!=16)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",cccohmva);
  sprintf(select2_nc,"(%s&&inttype!=1)*norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)",ccincl);

  sprintf(draw,"nuE");
  
  for(int i=2;i<=6;i++){

    sprintf(FileName,"../../systfsi/frKikawa/MC/pm/hiteff/merged_ccqe_%d.root",i);
    sprintf(HitFile,"../../systfsi/frKikawa/MC/pm/hiteff/merged_hiteff_%d.root",i);

    TFile* fFile = new TFile(FileName);
    TFile* fHit = new TFile(HitFile);
    TTree* tree  = (TTree*)fFile->Get("tree");
    TTree* hittree  = (TTree*)fHit->Get("tree");
    
    TH1F*  fHdet1 = new TH1F("fHdet1" , "fHdet1" , nbin, min, max);
    TH1F*  fHdet2 = new TH1F("fHdet2" , "fHdet2" , nbin, min, max);
    TH1F*  fHdet1_cc = new TH1F("fHdet1_cc" , "fHdet1_cc" , nbin, min, max);
    TH1F*  fHdet2_cc = new TH1F("fHdet2_cc" , "fHdet2_cc" , nbin, min, max);
    TH1F*  fHdet1_nc = new TH1F("fHdet1_nc" , "fHdet1_nc" , nbin, min, max);
    TH1F*  fHdet2_nc = new TH1F("fHdet2_nc" , "fHdet2_nc" , nbin, min, max);
    TH1F*  fHhit = new TH1F("fHhit" , "fHhit" , 2, 0, 2);
    tree -> Project("fHdet1" , draw, select1 );
    tree -> Project("fHdet2" , draw, select2 );
    tree -> Project("fHdet1_cc" , draw, select1_cc );
    tree -> Project("fHdet2_cc" , draw, select2_cc );
    tree -> Project("fHdet1_nc" , draw, select1_nc );
    tree -> Project("fHdet2_nc" , draw, select2_nc );
    hittree -> Project("fHhit" ,"hit_miss" , "norm*totcrsne*2.8647e-13*6.04193507503274721e20/(986*1.0e21)" );

    ndet1 = fHdet1->GetSumOfWeights();
    ndet2 = fHdet2->GetSumOfWeights();
    ndet1_cc = fHdet1_cc->GetSumOfWeights();
    ndet2_cc = fHdet2_cc->GetSumOfWeights();
    ndet1_nc = fHdet1_nc->GetSumOfWeights();
    ndet2_nc = fHdet2_nc->GetSumOfWeights();
    neff = fHhit->GetMean();

    output1<<neff<<" "<<ndet1<<endl;
    output2<<neff<<" "<<ndet2<<endl;
    output1_cc<<neff<<" "<<ndet1_cc<<endl;
    output2_cc<<neff<<" "<<ndet2_cc<<endl;
    output1_nc<<neff<<" "<<ndet1_nc<<endl;
    output2_nc<<neff<<" "<<ndet2_nc<<endl;

  }
}
