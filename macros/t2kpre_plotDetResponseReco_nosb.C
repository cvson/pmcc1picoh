double getxsecuncertainty(double ratio, double datarate, double bkgratio){
return ((datarate*(1+ratio)-bkgratio)/(datarate-bkgratio)-1)*100;
}  
void t2kpre_plotDetResponseReco_nosb(){
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    
    Int_t icolor;
    Int_t imarker;
    const Int_t NSAMPLE = 3;
    const Int_t NSYSRECO = 5;
    const Int_t NFILE = 12;
    const Int_t NBINCCQE = 5; //need to be consistent w/ inputs/cc1picohbins.txt
    
    const char *nameSample[NSAMPLE] = {"SIG",  "CRI", "CRII"};
    const char *nameSample_long[NSAMPLE]={"SIG",  "CRI", "CRII"};
    
    const char *namesys[NSYSRECO] ={"vertxy","vertz","3dmatch","INmatchpos","INmatchang"};
    const char *namesyslong[NSYSRECO] ={"vertex xy","vertex z","3D matching","INGRID matching pos.","INGRID matching angle"};
    
    const char *colorcode[NSAMPLE] = {"#000000",
        "#0072B2",
        "#D55E00"};
    const char *colorbyfile[NFILE] = {"#496364", "#80CF51", "#A95DC9", "#C15237", "#D1B54D","#8BCFAF",
        "#8291C8", "#C94C87", "#CDA09B", "#5C632F","#562E44"};
    const char *colorbybin[NBINCCQE] = {
    	"#000000",
	"#E69F00",
	"#009E73",
	"#0072B2",
	"#D55E00"
    }
    
    const int markerStyle[NSAMPLE] = {20, 21, 22};
   const int markerStyleBin[NBINCCQE] = {20, 21, 22, 24, 25/*, 26,27,28,29*/}; 
    
    TFile *pFile = new TFile("../inputs/detresponsefunction_reco.root");
    
    TGraph *pgrccqesub[NSYSRECO][NSAMPLE][NBINCCQE];
    TH1F *hbinccqe[NSAMPLE][NFILE];
    TH1F *hdatabinccqe[NSAMPLE][NFILE];
    
    for (int isam=0; isam<NSAMPLE; ++isam) {
        
        for (int ifile=0; ifile < NFILE; ++ifile) {
            hbinccqe[isam][ifile] = (TH1F*)pFile->Get(Form("hbinccqe_sam%d_id%d",isam,ifile));
            hdatabinccqe[isam][ifile] = (TH1F*)pFile->Get(Form("hdatabinccqe_sam%d_id%d",isam,ifile));
        }
        
    }
   
   //vertex xy
    double nevtbyBin_vertxy[3];
    double xsigma_vertxy[3]={150,175,200};

    //vertex z
    double nevtbyBin_vertz[3];
    double xsigma_vertz[3]={2,3,4};

    //3D matching
    double nevtbyBin_3dmatch[3];
    double xsigma_3dmatch[3]={3,4,5};

    //INGRID matching position
    double nevtbyBin_INmatchpos[3];
    double xsigma_INmatchpos[3]={75,85,95};

    //INGRID matching angle
    double nevtbyBin_INmatchang[3];
    double xsigma_INmatchang[3]={30,35,40};
    ///////////////////For data
    //vertex xy
    double nevtbyBindata_vertxy[3];

    //vertex z
    double nevtbyBindata_vertz[3];

    //3D matching
    double nevtbyBindata_3dmatch[3];

    //INGRID matching position
    double nevtbyBindata_INmatchpos[3];

    //INGRID matching angle
    double nevtbyBindata_INmatchang[3];

    ///////////////////For sub data-MC
    TGraph *pgrccqesub_vertxy[NSAMPLE];
    double nevtbyBinsub_vertxy[3];

    //vertex z
    TGraph *pgrccqesub_vertz[NSAMPLE];
    double nevtbyBinsub_vertz[3];

    //3D matching
    TGraph *pgrccqesub_3dmatch[NSAMPLE];
    double nevtbyBinsub_3dmatch[3];

    //INGRID matching position
    TGraph *pgrccqesub_INmatchpos[NSAMPLE];
    double nevtbyBinsub_INmatchpos[3];

    //INGRID matching angle
    TGraph *pgrccqesub_INmatchang[NSAMPLE];
    double nevtbyBinsub_INmatchang[3];

    TGraph *pgrall[NSAMPLE][NSYSRECO];
    for (int isam=0; isam<NSAMPLE; ++isam) {
     //vertex xy
    cout<<"Processing sample "<<isam<<endl;
            nevtbyBin_vertxy[0] = hbinccqe[isam][4]->GetSumOfWeights();
            nevtbyBin_vertxy[1] = hbinccqe[isam][5]->GetSumOfWeights();
            nevtbyBin_vertxy[2] = hbinccqe[isam][6]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_vertxy[0]!=0) {
                    nevtbyBin_vertxy[isub] /= hbinccqe[isam][4]->GetSumOfWeights();
                }
                else nevtbyBin_vertxy[isub] = 1;
            }
	 //vertex z
            nevtbyBin_vertz[0] = hbinccqe[isam][2]->GetSumOfWeights();
            nevtbyBin_vertz[1] = hbinccqe[isam][3]->GetSumOfWeights();
            nevtbyBin_vertz[2] = hbinccqe[isam][4]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_vertz[0]!=0) {
                    nevtbyBin_vertz[isub] /= hbinccqe[isam][2]->GetSumOfWeights();;
                }
                else nevtbyBin_vertz[isub] = 1;
            }


            //3dmatching
            nevtbyBin_3dmatch[0] = hbinccqe[isam][3]->GetSumOfWeights();
            nevtbyBin_3dmatch[1] = hbinccqe[isam][4]->GetSumOfWeights();
            nevtbyBin_3dmatch[2] = hbinccqe[isam][9]->GetSumOfWeights();
            cout <<"TESTING "<< nevtbyBin_3dmatch[0]<<" vs "<<nevtbyBin_3dmatch[1]<<" vs "<<nevtbyBin_3dmatch[2]<<endl;
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_3dmatch[0]!=0) {
                    nevtbyBin_3dmatch[isub] /= hbinccqe[isam][3]->GetSumOfWeights();
                }
                else nevtbyBin_3dmatch[isub] = 1;
            }


            //INGRID match position
            nevtbyBin_INmatchpos[0] = hbinccqe[isam][1]->GetSumOfWeights();
            nevtbyBin_INmatchpos[1] = hbinccqe[isam][4]->GetSumOfWeights();
            nevtbyBin_INmatchpos[2] = hbinccqe[isam][10]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_INmatchpos[0]!=0) {
                    nevtbyBin_INmatchpos[isub] /= hbinccqe[isam][1]->GetSumOfWeights();
                }
                else nevtbyBin_INmatchpos[isub] = 1;
            }

 	//INGRID match angle
            nevtbyBin_INmatchang[0] = hbinccqe[isam][0]->GetSumOfWeights();
            nevtbyBin_INmatchang[1] = hbinccqe[isam][4]->GetSumOfWeights();
            nevtbyBin_INmatchang[2] = hbinccqe[isam][11]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                if (nevtbyBin_INmatchang[0]!=0) {
                    nevtbyBin_INmatchang[isub] /= hbinccqe[isam][0]->GetSumOfWeights();
                }
                else nevtbyBin_INmatchang[isub] = 1;
            }

            ////////////////////For data
            //vertex xy
            nevtbyBindata_vertxy[0] = hdatabinccqe[isam][4]->GetSumOfWeights();
            nevtbyBindata_vertxy[1] = hdatabinccqe[isam][5]->GetSumOfWeights();
            nevtbyBindata_vertxy[2] = hdatabinccqe[isam][6]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                cout<<"Data vertxy "<<nevtbyBindata_vertxy[isub]<<endl;
                if (nevtbyBindata_vertxy[0]!=0) {
                    nevtbyBindata_vertxy[isub] /= hdatabinccqe[isam][4]->GetSumOfWeights();
                }
                else nevtbyBindata_vertxy[isub] = 1;
		cout<<"Data ratio vertxy "<<nevtbyBindata_vertxy[isub]<<" mc "<<nevtbyBin_vertxy[isub]<<endl;
            }



            //vertex z
            nevtbyBindata_vertz[0] = hdatabinccqe[isam][2]->GetSumOfWeights();
            nevtbyBindata_vertz[1] = hdatabinccqe[isam][3]->GetSumOfWeights();
            nevtbyBindata_vertz[2] = hdatabinccqe[isam][4]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                cout<<"Data vertz "<<nevtbyBindata_vertz[isub]<<endl;
                if (nevtbyBindata_vertz[0]!=0) {
                    nevtbyBindata_vertz[isub] /= hdatabinccqe[isam][2]->GetSumOfWeights();
                }
                else nevtbyBindata_vertz[isub] = 1; 
  		cout<<"Data ratio vertz "<<nevtbyBindata_vertz[isub]<<" mc "<<nevtbyBin_vertz[isub]<<endl;
            }

           //3dmatching
            nevtbyBindata_3dmatch[0] = hdatabinccqe[isam][3]->GetSumOfWeights();
            nevtbyBindata_3dmatch[1] = hdatabinccqe[isam][4]->GetSumOfWeights();
            nevtbyBindata_3dmatch[2] = hdatabinccqe[isam][9]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                cout<<"Data 3dmatch "<<nevtbyBindata_3dmatch[isub]<<endl;
                if (nevtbyBindata_3dmatch[0]!=0) {
                    nevtbyBindata_3dmatch[isub] /= hdatabinccqe[isam][3]->GetSumOfWeights();
                }
                else nevtbyBindata_3dmatch[isub] = 1;
                cout<<"Data ratio 3dmatch "<<nevtbyBindata_3dmatch[isub]<<" mc "<<nevtbyBin_3dmatch[isub]<<endl;
            }


            //INGRID match position
            nevtbyBindata_INmatchpos[0] = hdatabinccqe[isam][1]->GetSumOfWeights();
            nevtbyBindata_INmatchpos[1] = hdatabinccqe[isam][4]->GetSumOfWeights();
            nevtbyBindata_INmatchpos[2] = hdatabinccqe[isam][10]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                cout<<"Data pos. match "<<nevtbyBindata_INmatchpos[isub]<<endl;
                if (nevtbyBindata_INmatchpos[0]!=0) {
                    nevtbyBindata_INmatchpos[isub] /= hdatabinccqe[isam][1]->GetSumOfWeights();
                }
                else nevtbyBindata_INmatchpos[isub] = 1;
		cout<<"Data ratio pos. match "<<nevtbyBindata_INmatchpos[isub]<<" mc "<<nevtbyBin_INmatchpos[isub]<<endl;
            }


            //INGRID match angle
            nevtbyBindata_INmatchang[0] = hdatabinccqe[isam][0]->GetSumOfWeights();
            nevtbyBindata_INmatchang[1] = hdatabinccqe[isam][4]->GetSumOfWeights();
            nevtbyBindata_INmatchang[2] = hdatabinccqe[isam][11]->GetSumOfWeights();
            for (int isub=0; isub<3; isub++) {
                cout<<"Data ang. match "<<nevtbyBindata_INmatchang[isub]<<endl;
                if (nevtbyBindata_INmatchang[0]!=0) {
                    nevtbyBindata_INmatchang[isub] /= hdatabinccqe[isam][0]->GetSumOfWeights();
                }
                else nevtbyBindata_INmatchang[isub] = 1;
                cout<<"Data ratio ang. match "<<nevtbyBindata_INmatchang[isub]<<" mc "<<nevtbyBin_INmatchang[isub]<<endl;
            }

	     ///////////////////For subtraction

            for (int isub=0; isub<3; isub++) {
                nevtbyBinsub_vertxy[isub] = nevtbyBindata_vertxy[isub] - nevtbyBin_vertxy[isub];
                nevtbyBinsub_vertz[isub] = nevtbyBindata_vertz[isub] - nevtbyBin_vertz[isub];
                nevtbyBinsub_3dmatch[isub] = nevtbyBindata_3dmatch[isub] - nevtbyBin_3dmatch[isub];
                nevtbyBinsub_INmatchpos[isub] = nevtbyBindata_INmatchpos[isub] - nevtbyBin_INmatchpos[isub];
                nevtbyBinsub_INmatchang[isub] = nevtbyBindata_INmatchang[isub] - nevtbyBin_INmatchang[isub];
            cout<<"SAM "<<isam<<"vertxy "<<nevtbyBinsub_vertxy[isub]<<" vertz "<<nevtbyBinsub_vertz[isub]<<" 3dmatch "<<nevtbyBinsub_3dmatch[isub]<<" INGRID pos "<<nevtbyBinsub_INmatchpos[isub]<<" ang "<<nevtbyBinsub_INmatchang[isub]<<endl;
	    }
         //fill graph 
	pgrall[isam][0] = new TGraph(3,xsigma_vertxy,nevtbyBinsub_vertxy);
	pgrall[isam][1] = new TGraph(3,xsigma_vertz,nevtbyBinsub_vertz);
	pgrall[isam][2] = new TGraph(3,xsigma_3dmatch,nevtbyBinsub_3dmatch);
	pgrall[isam][3] = new TGraph(3,xsigma_INmatchpos,nevtbyBinsub_INmatchpos);
	pgrall[isam][4] = new TGraph(3,xsigma_INmatchang,nevtbyBinsub_INmatchang);
     }
    double aVariation;
    double aVariationAll;
    double tempMaxGraph;
    double tempMinGraph;
    double xsecrat03;
    double xsecrat03vertex;
    double xsecrat03match;
    double xsecrat04;
    double xsecrat04vertex;
    double xsecrat04match;
	double nevtratvertex ;
    double nevtratmatch ;
   for (int isam=0; isam<NSAMPLE; ++isam) {
   cout<<"Processing sample "<<isam<<endl;
    aVariationAll = 0; //reset
    xsecrat03vertex = 0;
    xsecrat03match = 0;
    xsecrat04vertex = 0;
    xsecrat04match = 0;
    nevtratvertex = 0;
    nevtratmatch = 0;

    for (Int_t isys=0; isys<NSYSRECO; ++isys) {
          tempMaxGraph = TMath::Abs(TMath::MaxElement(3,pgrall[isam][isys]->GetY()));
                tempMinGraph = TMath::Abs(TMath::MinElement(3,pgrall[isam][isys]->GetY()));
                aVariation = (tempMaxGraph>tempMinGraph)? tempMaxGraph:tempMinGraph;
                xsecrat03 = getxsecuncertainty(aVariation,0.616,0.4512);
		xsecrat04 = getxsecuncertainty(aVariation,0.671,0.4512);
		if(isys==0||isys==1){
		 nevtratvertex +=pow(aVariation,2);
		xsecrat03vertex +=pow(xsecrat03,2);
		xsecrat04vertex +=pow(xsecrat04,2);	
		} 
		if(isys==3||isys==4){
		nevtratmatch +=pow(aVariation,2);
                xsecrat03match +=pow(xsecrat03,2);
                xsecrat04match +=pow(xsecrat04,2);
		}
		cout<<"syst "<<isys<<" val "<<aVariation<<" xsec % "<<xsecrat03<<" rat04 "<<xsecrat04<<endl;
                aVariationAll += pow(aVariation,2);
    }   
    cout<<"final variation "<<TMath::Sqrt(aVariationAll)<<" xsec %"<<getxsecuncertainty(TMath::Sqrt(aVariationAll), 0.616,0.4512)<<" rat04 "<<getxsecuncertainty(TMath::Sqrt(aVariationAll), 0.671,0.4512)<<endl;
	cout<<"combine vertex "<<TMath::Sqrt(nevtratvertex)<<" rat03 "<<TMath::Sqrt(xsecrat03vertex)<<" rat04 "<<TMath::Sqrt(xsecrat04vertex)<<endl;
	cout<<"combine match "<<TMath::Sqrt(nevtratmatch)<<" rat03 "<<TMath::Sqrt(xsecrat03match)<<" rat04 "<<TMath::Sqrt(xsecrat04match)<<endl;
    }
}
