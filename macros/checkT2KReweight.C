{
    
    gROOT->ProcessLine(".x ../../rootlogon.C");
    gROOT->ProcessLine(".L ../../basicPlotUtil.C");
    TString opFilename = "../outputs/checkT2KReweight_pionFSff.root";
    TFile *popfile = new TFile(opFilename);
    TString saveName = "checkT2KReweight_pionFSff";
    const Int_t NPARAMETER = 25;
    const Int_t NVARIATION = 7;
    
    TH1F *hreweight[NPARAMETER][NVARIATION];
    
    
    for (Int_t ipara=0; ipara<NPARAMETER; ipara++) {
        for (Int_t ivari=0; ivari<NVARIATION; ivari++) {
            hreweight[ipara][ivari] = (TH1F*)popfile->Get(Form("hweight_para%d_sigma%d",ipara,ivari));
            hreweight[ipara][ivari] ->GetXaxis()->SetTitle("Weight values");
        }
    }
    plot3hist(false, hreweight[22][3],"Nominal",hreweight[22][2],"-1#sigma variation",hreweight[22][4],"+1#sigma variation",saveName+"_pilessDcy",0.5,0.5);
    plot3hist(false, hreweight[23][3],"Nominal",hreweight[23][2],"-1#sigma variation",hreweight[23][4],"+1#sigma variation",saveName+"_piEnuShape",0.5,0.5);
       
}
