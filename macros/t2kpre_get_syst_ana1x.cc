#include "/home/kikawa/macros/cccoh.h"

float ratio[3];

float get_maxdiff(char* filename, int nomi, float nqeratio){
  float data[10],mc[10],rdata[10],rmc[10],diff[10],largest,tmp,stat;
  int n;
  ifstream file(filename);
  n=0;
  largest=0;
  while(file>>data[n]>>mc[n]>>rdata[n]>>rmc[n]>>diff[n]){n++;}

  for(int i=0;i<n;i++){
    rdata[i]=data[i]/data[nomi];
    rmc[i]=mc[i]/mc[nomi];
    diff[i]=fabs(rdata[i]-rmc[i]);
    stat=sqrt(fabs(data[i]-data[nomi]))/data[nomi];
    //if(stat<diff[i])diff[i]=sqrt(diff[i]*diff[i]-stat*stat);
    //else            diff[i]=0;
    if(largest<diff[i])largest=diff[i];
  }
  largest = fabs((result*(1+largest)-nqeratio)/(result-nqeratio)-1)*100;
  return largest;
};

float get_maxdiff_timing(char* filename, int nomi, float nqeratio){
  float data[10],mc[10],rdata[10],rmc[10],largest,tmp;
  int n;
  ifstream file(filename);
  n=0;
  largest=0;
  while(file>>data[n]>>rdata[n]){n++;}

  for(int i=0;i<n;i++){
    rdata[i]=data[i]/data[nomi];
    tmp=fabs(rdata[i]-1);
    if(largest<tmp)largest=tmp;
  }
  largest = fabs((result*(1+largest)-nqeratio)/(result-nqeratio)-1)*100;
  return largest;
};


float get_err(char* filename, float unc){
  float slope,serr;
  ifstream file(filename);
  file>>slope;
  serr=fabs(slope*unc);
  return serr;
};

void get_syst(){
  float nqeratio[3];
  float err[3][11];
  memset(err,0,sizeof(err));
  
  float nqe1,nqe2,qe1,qe2,tmp;

  float unoise=3;
  float uhiteff=0.23;
  float upe=2.4;



  ifstream qefile1("/home/kikawa/scraid2/MC/pm/hiteff/nevent_cccoh1_qe.txt");
  //ifstream qefile2("/home/kikawa/scraid2/MC/pm/hiteff/nevent_cccoh2_qe.txt");
  ifstream nqefile1("/home/kikawa/scraid2/MC/pm/hiteff/nevent_cccoh1_nqe.txt");
  //ifstream nqefile2("/home/kikawa/scraid2/MC/pm/hiteff/nevent_cccoh2_nqe.txt");
  qefile1>>tmp>>qe1;
  //qefile2>>tmp>>qe2;
  nqefile1>>tmp>>nqe1;
  //nqefile2>>tmp>>nqe2;
  nqeratio[0]=nqe1/(qe1+nqe1);
  //nqeratio[1]=nqe2/(qe2+nqe2);

  //ofstream output("syst_new.txt");
    ofstream output("syst_kikawa.txt");

  /*err[0][0] = get_maxdiff("ingrid_angle_ccqe1_he.txt",1,nqeratio[0]);
  err[0][1] = get_maxdiff("ingrid_position_ccqe1_he.txt",1,nqeratio[0]);
  err[0][2] = get_maxdiff("matching_ccqe1_he.txt",1,nqeratio[0]);
  err[0][3] = get_maxdiff("vertexingxy_ccqe1_he.txt",1,nqeratio[0]);
  err[0][4] = get_maxdiff("vertexingz_ccqe1_he.txt",1,nqeratio[0]);
  err[0][5] = get_maxdiff_timing("timing_ccqe1_he.txt",1,nqeratio[0]);
  err[0][6] = get_maxdiff("front_veto_ccqe1_he.txt",1,nqeratio[0]);
  err[0][7] = get_maxdiff("fv_ccqe1_he.txt",0,nqeratio[0]);*/
    //test from Kikawa'san
    err[0][0] = get_maxdiff("/home/kikawa/macros/detsys_cccoh/ingrid_angle_ccqe1_he.txt",1,nqeratio[0]);
    err[0][1] = get_maxdiff("/home/kikawa/macros/detsys_cccoh/ingrid_position_ccqe1_he.txt",1,nqeratio[0]);
    err[0][2] = get_maxdiff("/home/kikawa/macros/detsys_cccoh/matching_ccqe1_he.txt",1,nqeratio[0]);
    err[0][3] = get_maxdiff("/home/kikawa/macros/detsys_cccoh/vertexingxy_ccqe1_he.txt",1,nqeratio[0]);
    err[0][4] = get_maxdiff("/home/kikawa/macros/detsys_cccoh/vertexingz_ccqe1_he.txt",1,nqeratio[0]);
    err[0][5] = get_maxdiff_timing("/home/kikawa/macros/detsys_cccoh/timing_ccqe1_he.txt",1,nqeratio[0]);
    err[0][6] = get_maxdiff("/home/kikawa/macros/detsys_cccoh/front_veto_ccqe1_he.txt",1,nqeratio[0]);
    err[0][7] = get_maxdiff("/home/kikawa/macros/detsys_cccoh/fv_ccqe1_he.txt",0,nqeratio[0]);
    
  err[0][8] = get_err("/home/kikawa/scraid2/MC/pm/noise/slope_cccoh1.txt",unoise);
  err[0][9] = get_err("/home/kikawa/scraid2/MC/pm/hiteff/slope_cccoh1.txt",uhiteff);
  err[0][10]= get_err("/home/kikawa/scraid2/MC/pm/pe/slope_cccoh1.txt",upe);



  float qadsum[3];
  for(int i=0;i<1;i++){
    for(int j=0;j<11;j++){
      qadsum[i]+=err[i][j]*err[i][j];
      output<<err[i][j]<<endl;
    }
    qadsum[i]=sqrt(qadsum[i]);
    output<<"****Total****"<<endl;
    output<<qadsum[i]<<endl;
    output<<endl;
  }
}
