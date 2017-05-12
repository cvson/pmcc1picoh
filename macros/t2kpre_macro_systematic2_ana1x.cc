#define HE
//#define LE

#include "/home/kikawa/macros/cccoh.h"
#include "common.h"


void macro_systematic2(){


  TGaxis::SetMaxDigits(4);

  fTFRatio   = new TFile(fratio.c_str());

  getreweight();  
  
  int nbin; double min, max; char draw[300], xtitle[300], select1[300], select2[300], title[300];
  int thr[5];

#ifdef HE
  sprintf(select1,"%s",cccoh);
  //sprintf(select1,"%s",ccqe1trk_he);
  //sprintf(select2,"%s",ccqe2trk_he);
#endif

#ifdef LE
  sprintf(select1,"%s",cccoh);
  //sprintf(select1,"%s",ccqe1trk_le);
  //sprintf(select2,"%s",ccqe2trk_le);
#endif


  
  double n_data1[10], n_mc1[10],n_data2[10], n_mc2[10];
  int jmax;
  ofstream output1;
  ofstream output2;
  char Output1[300];
  char Output2[300];

  for(int i=0;i<5;i++){
    

#ifdef HE
    switch(i){
    case 0:
      cout<<"Vertexing XY"<<endl;
      sprintf(Output1,"vertexingxy_ccqe1_he.txt");
      sprintf(Output2,"vertexingxy_ccqe2_he.txt");
      break;
    case 1:
      cout<<"Vertexing Z"<<endl;
      sprintf(Output1,"vertexingz_ccqe1_he.txt");
      sprintf(Output2,"vertexingz_ccqe2_he.txt");
      break;
    case 2:
      cout<<"3D matching"<<endl;
      sprintf(Output1,"matching_ccqe1_he.txt");
      sprintf(Output2,"matching_ccqe2_he.txt");
      break;
    case 3:
      cout<<"INGRID matching position"<<endl;
      sprintf(Output1,"ingrid_position_ccqe1_he.txt");
      sprintf(Output2,"ingrid_position_ccqe2_he.txt");
      break;
    case 4:
      cout<<"INGRID matching angle"<<endl;
      sprintf(Output1,"ingrid_angle_ccqe1_he.txt");
      sprintf(Output2,"ingrid_angle_ccqe2_he.txt");
      break;
    }
#endif

#ifdef LE
    switch(i){
    case 0:
      cout<<"Vertexing XY"<<endl;
      sprintf(Output1,"vertexingxy_ccqe1_le.txt");
      sprintf(Output2,"vertexingxy_ccqe2_le.txt");
      break;
    case 1:
      cout<<"Vertexing Z"<<endl;
      sprintf(Output1,"vertexingz_ccqe1_le.txt");
      sprintf(Output2,"vertexingz_ccqe2_le.txt");
      break;
    case 2:
      cout<<"3D matching"<<endl;
      sprintf(Output1,"matching_ccqe1_le.txt");
      sprintf(Output2,"matching_ccqe2_le.txt");
      break;
    case 3:
      cout<<"INGRID matching position"<<endl;
      sprintf(Output1,"ingrid_position_ccqe1_le.txt");
      sprintf(Output2,"ingrid_position_ccqe2_le.txt");
      break;
    case 4:
      cout<<"INGRID matching angle"<<endl;
      sprintf(Output1,"ingrid_angle_ccqe1_le.txt");
      sprintf(Output2,"ingrid_angle_ccqe2_le.txt");
      break;
    }
#endif


    ofstream output1(Output1);
    //ofstream output2(Output2);

    for(int j=0;j<3;j++){

      switch(i){
      case 0:
	thr[0]=35;
	thr[1]=85;
	thr[2]=4;
	thr[3]=2;
	thr[4]=150+25*j;
	break;
      case 1:
	thr[0]=35;
	thr[1]=85;
	thr[2]=4;
	thr[3]=2+j;
	thr[4]=150;
	break;
      case 2:
	thr[0]=35;
	thr[1]=85;
	thr[2]=3+j;
	//thr[2]=4+j;
	thr[3]=2;
	thr[4]=150;
	break;
      case 3:
	thr[0]=35;
	thr[1]=75+j*10;
	thr[2]=4;
	thr[3]=2;
	thr[4]=150;
	break;
      case 4:
	thr[0]=30+j*5;
	thr[1]=85;
	thr[2]=4;
	thr[3]=2;
	thr[4]=150;
	break;

      }

      cout<<thr[0]<<" "<<thr[1]<<" "<<thr[2]<<" "<<thr[3]<<" "<<thr[4]<<endl;

      char fsignal[300],fbar[300],fbg[300],fbg2[300],fdata[300];
      //changed
      sprintf(fsignal,"/home/kikawa/scraid2/MC/pm/sys/merged_%d_%d_%d_%d_%d_ccqe.root",thr[0],thr[1],thr[2],thr[3],thr[4]);
      sprintf(fbar,"/home/kikawa/scraid2/MC/pm_bar/sys/merged_%d_%d_%d_%d_%d_ccqe.root",thr[0],thr[1],thr[2],thr[3],thr[4]);
      //sprintf(fbg,"/home/kikawa/scraid1/MC/bg4/sys/merged_%d_%d_%d_%d_%d.root",thr[0],thr[1],thr[2],thr[3],thr[4]);
      //sprintf(fbg2,"/home/kikawa/scraid1/pm_bg_horizontal/sys/merged_%d_%d_%d_%d_%d.root",thr[0],thr[1],thr[2],thr[3],thr[4]);
      sprintf(fdata,"/home/kikawa/scraid2/data/sys/merged_%d_%d_%d_%d_%d_ccqe.root",thr[0],thr[1],thr[2],thr[3],thr[4]);


      fTFSignal = new TFile(fsignal);
      fTFBar = new TFile(fbar);
      //fTFBG     = new TFile(fbg);
      //fTFBG2    = new TFile(fbg2);
      fTFData   = new TFile(fdata);

      TH1F*  fHdata = new TH1F("fHdata", "fHdata", 20, 0, 90);
      TH1F*  fHcc   = new TH1F("fHcc", "fHcc",  20, 0, 90);
      TH1F*  fHbg   = new TH1F("fHbg", "fHbg",  20, 0, 90);
      TH1F*  fHbg2   = new TH1F("fHbg2", "fHbg2",  20, 0, 90);
      TH1F*  fHba   = new TH1F("fHba", "fHba",  20, 0, 90);


      tree_sig  = (TTree*)fTFSignal->Get("tree"); 
      tree_bar  = (TTree*)fTFBar   ->Get("tree"); 
      //tree_bg   = (TTree*)fTFBG    ->Get("tree"); 
      //tree_bg2   = (TTree*)fTFBG2    ->Get("tree"); 
      tree_data = (TTree*)fTFData  ->Get("tree"); 
      
      fHdata->Reset();
      fHcc  ->Reset();
      fHbg  ->Reset();
      fHbg2  ->Reset();
      fHba  ->Reset();

      tree_data      -> Project("fHdata", "1", Form("%s", select1) );
      tree_sig       -> Project("fHcc", "1", Form("reweight(3,nuE)*norm*totcrsne*2.8647e-13*%e/(%d*1e21)*(%s)", npot, nmc, select1) );
      tree_bar       -> Project("fHba", "1", Form("reweight(3,nuE)*norm*totcrsne*2.916e-12*%e/(%d*1e21)*(%s)", npot, nbar, select1) );
      //tree_bg        -> Project("fHbg", "1", Form("1.106*norm*totcrsne*6.9e-12*%e/(%d*1e21*1.3*(%s))", npot, nbg, select1) );
      //tree_bg2       -> Project("fHbg2", "1", Form("reweight(3,nuE)*norm*totcrsne*2.916e-12*%e/(%d*1e21)*(%s)", npot, nbg2, select1) );
      
      n_data1[j] = fHdata->GetSumOfWeights();
      n_mc1[j] = fHcc->GetSumOfWeights() + fHba->GetSumOfWeights() + fHbg->GetSumOfWeights() + + fHbg2->GetSumOfWeights();

      //fHdata->Reset();
      //fHcc  ->Reset();
      //fHbg  ->Reset();
      //fHbg2  ->Reset();
      //fHba  ->Reset();


      //tree_data      -> Project("fHdata", "1", Form("%s", select2) );
      //tree_sig       -> Project("fHcc", "1", Form("reweight(3,nuE)*norm*totcrsne*2.8647e-13*%e/(%d*1e21)*(%s)", npot, nmc, select2) );
      //tree_bar       -> Project("fHba", "1", Form("reweight(3,nuE)*norm*totcrsne*2.916e-12*%e/(%d*1e21)*(%s)", npot, nbar, select2) );
      //tree_bg        -> Project("fHbg", "1", Form("1.106*norm*totcrsne*6.9e-12*%e/(%d*1e21*1.3*(%s))", npot, nbg, select2) );
      //tree_bg2       -> Project("fHbg2", "1", Form("reweight(3,nuE)*norm*totcrsne*2.916e-12*%e/(%d*1e21)*(%s)", npot, nbg2, select2) );
      
      //n_data2[j] = fHdata->GetSumOfWeights();
      //n_mc2[j] = fHcc->GetSumOfWeights() + fHba->GetSumOfWeights() + fHbg->GetSumOfWeights() + + fHbg2->GetSumOfWeights();

      output1 << n_data1[j] <<" "<< n_mc1[j]<<" "<<n_data1[j]/n_data1[0] <<" "<< n_mc1[j]/n_mc1[0] <<" "<< n_data1[j]/n_data1[0] - n_mc1[j]/n_mc1[0] <<endl;
      //output2 << n_data2[j] <<" "<< n_mc2[j]<<" "<<n_data2[j]/n_data2[0] <<" "<< n_mc2[j]/n_mc2[0] <<" "<< n_data2[j]/n_data2[0] - n_mc2[j]/n_mc2[0] <<endl;
      	
    }
  }      
}
