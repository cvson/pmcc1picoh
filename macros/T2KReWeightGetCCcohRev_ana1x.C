#include "cccoh_ana1x.h"

bool fv(float x, float y, float z){
  bool infv;
  //if(fabs(x)<50&&fabs(y)<50&&z>-200)infv=true;
  if(fabs(x)<50&&fabs(y)<50&&z>-152&&z<-90)infv=true;
  else infv=false;
  return infv;
};

void T2KReWeightGetCCcohRev_ana1x(int nw = 0){
  
  char Output[100];
  float nevt=0;
  sprintf(Output,"nevent%d_cccoh.txt",nw);
  ofstream output(Output);
  
    string fnominal = "/home/cvson/cc1picoh/FIT/mc4t2kreweight/merged_onlybasic.root";
    string fweight  = "/home/cvson/cc1picoh/FIT/mc4t2kreweight/merged_weight.root";
    //string fccqe  = "/home/cvson/cc1picoh/FIT/mc4t2kreweight/merged_ccqe.root";
    string fccqe  = "/home/cvson/cc1picoh/FIT/datafsicornorange/merged_ccqe_forResponseFunction.root";
  
  TTree* tree_nominal ;
  TTree* tree_ccqe;
  
  fNominal = new TFile(fnominal.c_str());
  fCCQE    = new TFile(fccqe.c_str());
  
  tree_nominal  = (TTree*)fNominal->Get("tree");
  tree_nominal  -> AddFriend("weightstree",fweight.c_str());
  
  tree_ccqe  = (TTree*)fCCQE->Get("tree");

  int nbin; double min, max; char draw[300], select[300];
  
  nbin = 100; min = 0; max = 50;
  
  sprintf(select,"norm*totcrsne*2.8647e-13/(1100*2)");
  sprintf(draw,"nuE");
  
  TH1F*    fHint  = new TH1F("fHint" , "fHint" , nbin, min, max);
  TH1F*    fHdet_qe  = new TH1F("fHdet_qe" , "fHdet_qe" , nbin, min, max);
  TH1F*    fHdet_nqe  = new TH1F("fHdet_nqe" , "fHdet_nqe" , nbin, min, max);

  tree_nominal -> Project("fHint" , draw, Form("(%s)*weights.At(%d)*(weights.At(%d)>0&&weights.At(%d)<100)*(inttype==16)*fv(xnu,ynu,znu)", select,nw,nw,nw ) );
  tree_ccqe -> Project("fHdet_qe" , draw, Form("(%s)*reweight[%d]*(reweight[%d]>0&&reweight[%d]<100)*(%s&&inttype==16)", select,nw,nw,nw,cccohmva ) );
  tree_ccqe -> Project("fHdet_nqe" , draw, Form("(%s)*reweight[%d]*(reweight[%d]>0&&reweight[%d]<100)*(%s&&inttype!=16)", select,nw,nw,nw,cccohmva ) );
  
  float nint     = fHint->GetSumOfWeights();
  float ndet_qe  = fHdet_qe->GetSumOfWeights();
  float ndet_nqe = fHdet_nqe->GetSumOfWeights();
  output<<nint<<" "<<ndet_qe<<" "<<ndet_nqe<<endl;

}
