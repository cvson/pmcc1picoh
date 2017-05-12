{
    
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    TString opFilename = "../outputs/checkT2KReweight_pionFSff_v1r19piless02cor.root";
    //TString opFilename = "../outputs/checkT2KReweight_pionFSff_v1r19wrong.root";
    TFile *popfile = new TFile(opFilename);
    TString saveName = "checkT2KReweight_pionFSff_v1r19";
    //TString saveName = "checkT2KReweight_pionFSff_v1r19wro";
    const Int_t NPARAMETER = 25;
    const Int_t NVARIATION = 7;
    const Int_t NINTERACTION = 5;

    
    TH1F *hreweight[NPARAMETER][NVARIATION];
    TH1F *henmc[NPARAMETER][NVARIATION][NINTERACTION];    
    
    for (Int_t ipara=0; ipara<NPARAMETER; ipara++) {
        for (Int_t ivari=0; ivari<NVARIATION; ivari++) {
            hreweight[ipara][ivari] = (TH1F*)popfile->Get(Form("hweight_para%d_sigma%d",ipara,ivari));
            hreweight[ipara][ivari] ->GetXaxis()->SetTitle("Weight values");
 	    hreweight[ipara][ivari] ->GetXaxis()->SetRangeUser(-10,10);
            for (Int_t iitype=0; iitype<NINTERACTION; iitype++) {
	    henmc[ipara][ivari][iitype] = (TH1F*)popfile->Get(Form("henmc_para%d_sigma%d_type%d",ipara,ivari,iitype));
	    henmc[ipara][ivari][iitype]->GetXaxis()->SetTitle("True Neutrino Energy (GeV)");
            henmc[ipara][ivari][iitype]->GetYaxis()->SetTitle("Number of Events"); 
           }
        }
    }
    for (Int_t iitype=0; iitype<NINTERACTION; iitype++) {
	  TString subname = Form("_type%d",iitype);
          double nnom = henmc[22][3][iitype]->GetSumOfWeights();
          double nplus = henmc[22][4][iitype]->GetSumOfWeights();
          double nminus = henmc[22][2][iitype]->GetSumOfWeights();
	  double shiftplus = (nplus-nnom)/nnom;
          double shiftminus =  (nminus-nnom)/nnom;
          cout<<"shift plus "<<shiftplus<<" minus "<<shiftminus<<endl;
          plot3hist(false, henmc[22][3][iitype],"Nominal",henmc[22][2][iitype],"-1#sigma variation",henmc[22][4][iitype],"+1#sigma variation",saveName+"_pilessDcyEn"+subname,0.5,0.65);
    	  plot3hist(false, henmc[23][3][iitype],"Nominal",henmc[23][2][iitype],"-1#sigma variation",henmc[23][4][iitype],"+1#sigma variation",saveName+"_piEnuShapeEn"+subname,0.5,0.65);
    }
    plot3hist(false, hreweight[22][3],"Nominal",hreweight[22][2],"-1#sigma variation",hreweight[22][4],"+1#sigma variation",saveName+"_pilessDcy",0.2,0.5);
    plot3hist(false, hreweight[23][3],"Nominal",hreweight[23][2],"-1#sigma variation",hreweight[23][4],"+1#sigma variation",saveName+"_piEnuShape",0.2,0.5);
       
}
