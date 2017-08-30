#include "cccoh_ana1x.h"

bool fv(float x, float y, float z){
  bool infv;
  //if(fabs(x)<50&&fabs(y)<50&&z>-200)infv=true;
  if(fabs(x)<50&&fabs(y)<50&&z>-152&&z<-90)infv=true;
  else infv=false;
  return infv;
};

void t2kpre_T2KReWeightGetCCcohRev_v1r25(int nw = 0){
  
  char Output[100];
  float nevt=0;
  sprintf(Output,"nevent%d_cccoh.txt",nw);
  ofstream output(Output);
 //v1r19 piless fixed 
/*string fnominal = "/export/scraid2/data/cvson/MC/pionFS_pm/merged_pmmc_onlybasic_bugfix.root";
string fweight  = "/home/cvson/scraid2/MC/t2kreweight/v1r19piless02cor/merged_weight.root";
string fccqe  = "/home/cvson/cc1picoh/FIT/datafsipionFS/merged_ccqe_forResponseFunction_pionFS_v1r19piless02cor.root";
*/
//v1r25
string fnominal = "/export/scraid2/data/cvson/MC/pm/newneut/all_merged_pmmc_onlybasic_bugfix_3974files.root";
string fweight  = "/export/scraid2/data/cvson/pmmc/newneut/nd2numu/all_merged_weight_3974file.root";
string fccqe  = "/home/cvson/cc1picoh/FIT/datafsipionFS/all_merged_rwv1r25_neut5d3d2_coh_byorder.root";

  TTree* tree_nominal ;
  TTree* tree_ccqe;
  
  fNominal = new TFile(fnominal.c_str());
  fCCQE    = new TFile(fccqe.c_str());
  
  tree_nominal  = (TTree*)fNominal->Get("tree");
  tree_nominal  -> AddFriend("weightstree",fweight.c_str());
  
  tree_ccqe  = (TTree*)fCCQE->Get("tree");

  int nbin; double min, max; char draw[300], select[300];
  
  nbin = 100; min = 0; max = 50;
  
  //sprintf(select,"norm*totcrsne*2.8647e-13/(1100*2)");
  //sprintf(select,"norm*totcrsne*2.8647e-13*6.04193507503274721/(1974*10)");
   sprintf(select,"norm*totcrsne*2.8647e-13*6.04193507503274721/(3974*10)");
  sprintf(draw,"nuE");
  
  TH1F*    fHint  = new TH1F("fHint" , "fHint" , nbin, min, max);
  TH1F*    fHdet_qe  = new TH1F("fHdet_qe" , "fHdet_qe" , nbin, min, max);
  TH1F*    fHdet_nqe  = new TH1F("fHdet_nqe" , "fHdet_nqe" , nbin, min, max);

  tree_nominal -> Project("fHint" , draw, Form("(%s)*weights.At(%d)*(weights.At(%d)>0&&weights.At(%d)<100)*(inttype==16)*fv(xnu,ynu,znu)", select,nw,nw,nw ) );
  tree_ccqe -> Project("fHdet_qe" , draw, Form("(%s)*reweight[%d]*(reweight[%d]>0&&reweight[%d]<100)*(%s&&inttype==16)", select,nw,nw,nw,cccoh ) );
  tree_ccqe -> Project("fHdet_nqe" , draw, Form("(%s)*reweight[%d]*(reweight[%d]>0&&reweight[%d]<100)*(%s&&inttype!=16)", select,nw,nw,nw,cccoh ) );
  
  float nint     = fHint->GetSumOfWeights();
  float ndet_qe  = fHdet_qe->GetSumOfWeights();
  float ndet_nqe = fHdet_nqe->GetSumOfWeights();
  output<<nint<<" "<<ndet_qe<<" "<<ndet_nqe<<endl;

}
