#define HE
//#define LE

#include "/home/kikawa/macros/cccoh.h"
#include "common.h"

void macro_systematic(){

  string fsignal="/home/kikawa/scraid2/MC/pm/merged_ccqe.root";
  string fbar="/home/kikawa/scraid2/MC/pm_bar/merged_ccqe.root";
  string fbg="/home/kikawa/scraid2/MC/wall/merged_ccqe_tot.root";
  string fbg2="/home/kikawa/scraid2/MC/ingrid/merged_ccqe_nd3.root";
  string fdata="/home/kikawa/scraid2/data/merged_ccqe.root";

  TGaxis::SetMaxDigits(4);
  fTFSignal = new TFile(fsignal.c_str());
  fTFBar = new TFile(fbar.c_str());
  //fTFBG     = new TFile(fbg.c_str());
  //fTFBG2    = new TFile(fbg2.c_str());
  fTFData   = new TFile(fdata.c_str());
  fTFRatio   = new TFile(fratio.c_str());

  tree_sig  = (TTree*)fTFSignal->Get("tree"); 
  tree_bar  = (TTree*)fTFBar->Get("tree"); 
  //tree_bg   = (TTree*)fTFBG    ->Get("tree"); 
  //tree_bg2   = (TTree*)fTFBG2    ->Get("tree"); 
  tree_data = (TTree*)fTFData  ->Get("tree"); 

  getreweight();

  ofstream output1;
  ofstream output2;
  char Output1[300];
  char Output2[300];
  
  int nbin; double min, max; char draw[300], xtitle[300], select[300], select1[300], select2[300], title[300];
  
  TH1F*    fHdata = new TH1F("fHdata", "fHdata", 20, 0, 90);
  TH1F*    fHcc   = new TH1F("fHcc", "fHcc", 20, 0, 90);
  TH1F*    fHbg   = new TH1F("fHbg", "fHbg", 20, 0, 90);
  TH1F*    fHbg2  = new TH1F("fHbg2", "fHbg2", 20, 0, 90);
  TH1F*    fHba   = new TH1F("fHba", "fHba", 20, 0, 90);

  double n_data1[10], n_mc1[10],n_data2[10], n_mc2[10];
  int jmax;

  for(int i=0;i<2;i++){


#ifdef HE
    switch(i){
    case 0:
      cout<<"FV cut"<<endl;
      sprintf(Output1,"fv_ccqe1_he.txt");
      sprintf(Output2,"fv_ccqe2_he.txt");
      jmax=4;
      break;
    case 1:
      cout<<"Front Veto cut"<<endl;
      sprintf(Output1,"front_veto_ccqe1_he.txt");
      sprintf(Output2,"front_veto_ccqe2_he.txt");
      jmax=3;
      break;
    }
#endif

#ifdef LE
    switch(i){
    case 0:
      cout<<"FV cut"<<endl;
      sprintf(Output1,"fv_ccqe1_le.txt");
      sprintf(Output2,"fv_ccqe2_le.txt");
      jmax=4;
      break;
    case 1:
      cout<<"Front Veto cut"<<endl;
      sprintf(Output1,"front_veto_ccqe1_le.txt");
      sprintf(Output2,"front_veto_ccqe2_le.txt");
      jmax=3;
      break;
    }
#endif
    

    ofstream output1(Output1);
    //ofstream output2(Output2);

    for(int j=0;j<jmax;j++){

      switch(i){
      case 0:
	switch(j){
	case 0:
	  sprintf(select,"startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50");
	  break;
	case 1:
	  sprintf(select,"startxch>=7*50&&startxch<17*50&startych>=7*50&&startych<17*50");
	  break;
	case 2:
	  sprintf(select,"startxch>=4*50&&startxch<20*50&&startych>=4*50&&startych<20*50&&!(startxch>=7*50&&startxch<17*50&&startych>=7*50&&startych<17*50)");
	  break;
	case 3:
	  sprintf(select,"startxch>=2*50&&startxch<22*50&&startych>=2*50&&startych<22*50&&!(startxch>=4*50&&startxch<20*50&&startych>=4*50&&startych<20*50)");
	  break;
	}
	break;


      case 1:
        switch(j){
        case 0:
          sprintf(select,"startxpln>=2&&startypln>=2");
          break;
        case 1:
          sprintf(select,"startxpln>=3&&startypln>=3");
          break;
        case 2:
          sprintf(select,"startxpln>=4&&startypln>=4");
          break;
        }
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

      //sprintf(select,"hastrk&&matchtrk&&!vetowtracking&&!edgewtracking");

      fHdata->Reset();
      fHcc  ->Reset();
      fHbg  ->Reset();
      fHba  ->Reset();

      tree_data      -> Project("fHdata", "1", Form("%s", select1) );
      tree_sig       -> Project("fHcc", "1", Form("reweight(3,nuE)*norm*totcrsne*2.8647e-13*%e/(%d*1e21)*(%s)", npot, nmc, select1) );
      tree_bar       -> Project("fHba", "1", Form("reweight(3,nuE)*norm*totcrsne*2.916e-12*%e/(%d*1e21)*(%s)", npot, nbar, select1) );
      //tree_bg        -> Project("fHbg", "1", Form("1.106*norm*totcrsne*6.9e-12*%e/(%d*1e21*1.3*(%s))", npot, nbg, select1) );
      //tree_bg2       -> Project("fHbg2", "1", Form("reweight(3,nuE)*norm*totcrsne*2.916e-12*%e/(%d*1e21)*(%s)", npot, nbg2, select1) );

      n_data1[j] = fHdata->GetSumOfWeights();
      n_mc1[j]   = fHcc->GetSumOfWeights() + fHba->GetSumOfWeights() + fHbg->GetSumOfWeights()+ fHbg2->GetSumOfWeights();

      //fHdata->Reset();
      //fHcc  ->Reset();
      //fHbg  ->Reset();
      //fHba  ->Reset();

      //tree_data      -> Project("fHdata", "1", Form("%s", select2) );
      //tree_sig       -> Project("fHcc", "1", Form("reweight(3,nuE)*norm*totcrsne*2.8647e-13*%e/(%d*1e21)*(%s)", npot, nmc, select2) );
      //tree_bar       -> Project("fHba", "1", Form("reweight(3,nuE)*norm*totcrsne*2.916e-12*%e/(%d*1e21)*(%s)", npot, nbar, select2) );
      //tree_bg        -> Project("fHbg", "1", Form("1.106*norm*totcrsne*6.9e-12*%e/(%d*1e21*1.3*(%s))", npot, nbg, select2) );
      //tree_bg2       -> Project("fHbg2", "1", Form("reweight(3,nuE)*norm*totcrsne*2.916e-12*%e/(%d*1e21)*(%s)", npot, nbg2, select2) );

      //n_data2[j] = fHdata->GetSumOfWeights();
      //n_mc2[j]   = fHcc->GetSumOfWeights() + fHba->GetSumOfWeights() + fHbg->GetSumOfWeights()+ fHbg2->GetSumOfWeights();

      output1 << n_data1[j] <<" "<< n_mc1[j]<<" "<<n_data1[j]/n_data1[0] <<" "<< n_mc1[j]/n_mc1[0] <<" "<< n_data1[j]/n_data1[0] - n_mc1[j]/n_mc1[0] <<endl;
      //output2 << n_data2[j] <<" "<< n_mc2[j]<<" "<<n_data2[j]/n_data2[0] <<" "<< n_mc2[j]/n_mc2[0] <<" "<< n_data2[j]/n_data2[0] - n_mc2[j]/n_mc2[0] <<endl;
      
    }
  }      
}
