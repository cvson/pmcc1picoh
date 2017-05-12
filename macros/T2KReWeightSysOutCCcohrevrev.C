#include <math.h>

#include "cccoh_ana1x.h"


float x[7],ndet_sig[100][7],ndet_bg[100][7],nint[100][7],ndet_tot[100];

void maxdif(float &a, float &b){
  float tmp;
  if(a<0&&b<0){
    if(a>b){
      a=b;
    }
    b=0;
  }
  else if(a>0&&b>0){
    if(a>b){
      b=a;
    }
    a=0;
  }
  else if(a>0&&b<0){
    tmp=a;
    a=b;
    b=tmp;
  }
};


void T2KReWeightSysOutCCcohrevrev(){
  int nw = 0;
  char FileName[300];
 // ofstream ofile("output_ccqe_revrev.txt");
ofstream ofile("output_cccoh_revrev_nomcheck.txt");  
float syst[2],tot[2];
  memset(tot,0,sizeof(tot));

  for(int i=0;i<25;i++){
    for(int j=0;j<7;j++){
      //sprintf(FileName,"/home/kikawa/macros/t2kreweight_cccoh/nevent%d_cccoh.txt",i*7+j);
      sprintf(FileName,"/home/cvson/cc1picoh/FIT/versionfsicombgenieana1x/macros/t2kreweight_cccoh/nevent%d_cccoh.txt",i*7+j);
      //sprintf(FileName,"/home/cvson/cc1picoh/FIT/versionfsicombgenieana1x/macros/t2kreweight_nomcheck/nevent%d_cccoh.txt",i*7+j);
      ifstream data(FileName);
      data>>nint[i][j]>>ndet_sig[i][j]>>ndet_bg[i][j];
    }
      //result_qe is ratio of data to total prediction
    ndet_tot[i]=ndet_sig[i][3]*result_qe+ndet_bg[i][3];

    syst[0]=(((ndet_tot[i]-ndet_bg[i][4])*nint[i][4]/ndet_sig[i][4])/((ndet_tot[i]-ndet_bg[i][3])*nint[i][3]/ndet_sig[i][3])-1)*100;
    syst[1]=(((ndet_tot[i]-ndet_bg[i][2])*nint[i][2]/ndet_sig[i][2])/((ndet_tot[i]-ndet_bg[i][3])*nint[i][3]/ndet_sig[i][3])-1)*100;

    maxdif(syst[0],syst[1]);

    if(i==15){
      syst[0]=0;
      syst[1]=0;
    }

    ofile<<syst[0]<<" "<<syst[1]<<endl;

    if(!(i==22 ||i==23)){
    tot[0]+=syst[0]*syst[0];
    tot[1]+=syst[1]*syst[1];
    }
  }
  cout<<sqrt(tot[0])<<" "<<sqrt(tot[1])<<endl;
}
