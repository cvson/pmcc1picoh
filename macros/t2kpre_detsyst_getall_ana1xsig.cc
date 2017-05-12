#include "cccoh_ana1x.h"

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
  largest = fabs((resultmva*(1+largest)-nqeratio)/(resultmva-nqeratio)-1)*100;
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
  largest = fabs((resultmva*(1+largest)-nqeratio)/(resultmva-nqeratio)-1)*100;
  return largest;
};


float get_err(char* filename, float unc){
  float slope,serr;
  ifstream file(filename);
  file>>slope;
  serr=fabs(slope*unc);
  return serr;
};

void t2kpre_detsyst_getall_ana1xsig(){
  float nqeratio[3];
  float err[3][11];
  memset(err,0,sizeof(err));
  
  float nqe1,nqe2,qe1,qe2,tmp;

  float unoise=3;
  float uhiteff=0.23;
  float upe=2.4;



  ifstream qefile1("detsyst/hiteff_ana1xsig_nevent_cccoh1_qe.txt");
  //ifstream qefile2("/home/kikawa/scraid2/MC/pm/hiteff/nevent_cccoh2_qe.txt");
  ifstream nqefile1("detsyst/hiteff_ana1xsig_nevent_cccoh1_nqe.txt");
  //ifstream nqefile2("/home/kikawa/scraid2/MC/pm/hiteff/nevent_cccoh2_nqe.txt");
  qefile1>>tmp>>qe1;
  //qefile2>>tmp>>qe2;
  nqefile1>>tmp>>nqe1;
  //nqefile2>>tmp>>nqe2;
  nqeratio[0]=nqe1/(qe1+nqe1);
  //nqeratio[1]=nqe2/(qe2+nqe2);

  //ofstream output("syst_new.txt");
    ofstream output("detsyst/ana1xsig_alldetsyst.txt");

    //test from Kikawa'san
    err[0][0] = get_maxdiff("detsyst/ana1xsig_ingrid_angle_ccqe1_he.txt",1,nqeratio[0]);
    err[0][1] = get_maxdiff("detsyst/ana1xsig_ingrid_position_ccqe1_he.txt",1,nqeratio[0]);
    err[0][2] = get_maxdiff("detsyst/ana1xsig_matching_ccqe1_he.txt",1,nqeratio[0]);
    err[0][3] = get_maxdiff("detsyst/ana1xsig_vertexingxy_ccqe1_he.txt",1,nqeratio[0]);
    err[0][4] = get_maxdiff("detsyst/ana1xsig_vertexingz_ccqe1_he.txt",1,nqeratio[0]);
    err[0][5] = get_maxdiff_timing("detsyst/ana1xsig_timing_ccqe1_he.txt",1,nqeratio[0]);
    err[0][6] = get_maxdiff("detsyst/ana1xsig_front_veto_ccqe1_he.txt",1,nqeratio[0]);
    err[0][7] = get_maxdiff("detsyst/ana1xsig_fv_ccqe1_he.txt",0,nqeratio[0]);
    
  err[0][8] = get_err("detsyst/noise_ana1xsig_slope_cccoh1.txt",unoise);
  err[0][9] = get_err("detsyst/hiteff_ana1xsig_slope_cccoh1.txt",uhiteff);
  err[0][10]= get_err("detsyst/pe_ana1xsig_slope_cccoh1.txt",upe);


const char *systname[11]={"INGangle","INGpos","INGmatch","vertexxy","vertexz","timing","veto","fv","noise","hiteff","pe"}; 
  float qadsum[3];
  for(int i=0;i<1;i++){
    for(int j=0;j<11;j++){
      qadsum[i]+=err[i][j]*err[i][j];
      output<<systname[j]<<" "<<err[i][j]<<endl;
    }
    qadsum[i]=sqrt(qadsum[i]);
    output<<"****Total****"<<endl;
    output<<qadsum[i]<<endl;
    output<<endl;
  }
}
