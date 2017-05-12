#define HE
//#define LE

#include "/home/kikawa/macros/cccoh.h"
#include "common.h"


void macro_systematic3(){

  //string fdata="/home/kikawa/scraid1/data/pm_ingrid/merged_ccqe.root";
    string fdata="/home/kikawa/scraid2/data/merged_ccqe.root";


  TGaxis::SetMaxDigits(4);
  fTFData   = new TFile(fdata.c_str());
  fTFRatio   = new TFile(fratio.c_str());

  tree_data = (TTree*)fTFData  ->Get("tree"); 

  getreweight();

  int nbin; double min, max; char draw[300], xtitle[300], select[300], select1[300], select2[300], title[300];

  char Output1[300];
  char Output2[300];

#ifdef HE
  sprintf(Output1,"timing_ccqe1_he.txt");
  sprintf(Output2,"timing_ccqe2_he.txt");
#endif

#ifdef LE
  sprintf(Output1,"timing_ccqe1_le.txt");
  sprintf(Output2,"timing_ccqe2_le.txt");
#endif

  ofstream output1(Output1);
  //ofstream output2(Output2);
  
  TH1F*    fHdata = new TH1F("fHdata", "fHdata", 14, 0, 14);

  double n_data1[10];
  double n_data2[10];
  int jmax;
    
  cout<<"Timing cut"<<endl;

  for(int j=0;j<3;j++){
    
    switch(j){
    case 0:
      sprintf(select,"exptime<100&&exptime>-100");
      break;
    case 1:
      sprintf(select,"exptime<90&&exptime>-90");
      break;
    case 2:
      sprintf(select,"exptime<80&&exptime>-80");
      break;
    }

#ifdef HE
    sprintf(select1,"%s&&%s",cccoh,select);
    //sprintf(select1,"%s&&%s",ccqe1trk_he,select);
    //sprintf(select2,"%s&&%s",ccqe2trk_he,select);
#endif

#ifdef LE
    sprintf(select1,"%s&&%s",cccoh,select);
    //sprintf(select1,"%s&&%s",ccqe1trk_le,select);
    //sprintf(select2,"%s&&%s",ccqe2trk_le,select);
#endif

    
    fHdata->Reset();
    
    tree_data      -> Project("fHdata", "1", Form("%s", select1) );
    n_data1[j] = fHdata->GetSumOfWeights();
    
    //fHdata->Reset();
    
    //tree_data      -> Project("fHdata", "1", Form("%s", select2) );
    //n_data2[j] = fHdata->GetSumOfWeights();
    
    output1 << n_data1[j] <<" "<<n_data1[j]/n_data1[0] <<endl;
    //output2 << n_data2[j] <<" "<<n_data2[j]/n_data2[0] <<endl;
    
  }
}
