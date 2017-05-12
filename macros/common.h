#define NMOD 14
#define NBIN 200
#define NMIN 0
#define NMAX 10

/*
float npot = 5.8416862e20;
int   nmc  = 987;
int   nbar  = 1;
int   nbg  = 22480;
int   nbg2  = 1975;
*/

float npot = 6.04193507503274721e20;
int   nmc  = 986;//1975; in systematics
int   nbar  = 986;//986
int   nbg  = 31085+24461;
int   nbg2  = 3941+3941;

TFile* fTFSignal;
TFile* fTFBG;
TFile* fTFBG2;
TFile* fTFData;
TFile* fTFBar;
TFile* fTFRatio;

TTree* tree_sig ;
TTree* tree_bg  ;
TTree* tree_bg2  ;
TTree* tree_bar ;
TTree* tree_data;

//string fratio="/export/scraid1/data/beamMC/tune/11bv3.1/nd34/nd34_tuned_11bv3.1_250ka.root";
//string fratio="/home/kikawa/macros/nd34_tuned_11bv3.1_250ka.root";
//string fratio="/Users/soncao/data/cc1picoh/nd34_tuned_11bv3.1_250ka.root";
string fratio="/home/cvson/cc1picoh/FIT/data/nd34_tuned_11bv3.1_250ka.root";
TH1D*  tratio[NMOD];
TH1D*  tratio2[NMOD];
double rwratio[NMOD][NBIN];

double reweight(int mod, float Enu){
  double wratio;
  int intnue;
  intnue=Enu/NMAX*NBIN;
  if(intnue>=NBIN)intnue=NBIN-1;
  wratio=rwratio[mod][intnue];
  return wratio;
};



void getreweight(){

  for(int i=0;i<NMOD;i++){
    char histname[300];
    char histname2[300];
    sprintf(histname,"ing%d_tune_numu",i);
    sprintf(histname2,"ing%d_nom_numu",i);
    tratio[i]= (TH1D*)fTFRatio  ->Get(histname);
    tratio2[i]= (TH1D*)fTFRatio  ->Get(histname2);
    for(int j=0;j<NBIN;j++){
      if(tratio2[i]->GetBinContent(j+1)!=0)
        rwratio[i][j]=(tratio[i]->GetBinContent(j+1))/(tratio2[i]->GetBinContent(j+1));
      else
        rwratio[i][j]=1;
    }
  }

};


