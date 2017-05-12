#include "cccoh_ana1x.h"
void t2kpre_detsyst_else(){
	double unMassTarget = 0.0025;//
	double errunMassTargetNom;
	errunMassTargetNom = ((result*(1+unMassTarget)-bgrat)/(result-bgrat)-1)*100;

	double errunMassTargetana1x;
        errunMassTargetana1x = ((resultmva*(1+unMassTarget)-bgratmva)/(resultmva-bgratmva)-1)*100;
        cout<<"Nominal "<<errunMassTargetNom<<" ana1xrat03 "<<errunMassTargetana1x<<endl;
        resultmva = 0.671;	
	//result_qemva = 0.40;

         errunMassTargetana1x = ((resultmva*(1+unMassTarget)-bgratmva)/(resultmva-bgratmva)-1)*100;
         cout<<"Nominal "<<errunMassTargetNom<<" ana1xrat04 "<<errunMassTargetana1x<<endl;
	resultmva = 0.616;//return normal
        //2D track reconstruction
	double un2DTrkReco = 0.0049;//
    double errun2DTrkRecoNom;
    errun2DTrkRecoNom = ((result*(1+un2DTrkReco)-bgrat)/(result-bgrat)-1)*100;
    
    double errun2DTrkRecoana1x;
    errun2DTrkRecoana1x = ((resultmva*(1+un2DTrkReco)-bgratmva)/(resultmva-bgratmva)-1)*100;
    cout<<"Nominal "<<errun2DTrkRecoNom<<" ana1xrat03 "<<errun2DTrkRecoana1x<<endl;
    resultmva = 0.671;
    //result_qemva = 0.40;
    
    errun2DTrkRecoana1x = ((resultmva*(1+un2DTrkReco)-bgratmva)/(resultmva-bgratmva)-1)*100;
    cout<<"Nominal "<<errun2DTrkRecoNom<<" ana1xrat04 "<<errun2DTrkRecoana1x<<endl;
      resultmva = 0.616;//return normal
     
       //background from external material
       double errExternal = (-(result-(bgrat*(1+0.35*0.0008/bgrat)))/(result-bgrat)+1)*100;
       double errExternalana1x = (-(resultmva-(bgratmva*(1+0.35*0.0031/bgratmva)))/(resultmva-bgratmva)+1)*100; 
       cout<<" background from outside "<<errExternal<<" ana1x "<<errExternalana1x<<endl;
       resultmva = 0.671;
       double errExternalana1x = (-(resultmva-(bgratmva*(1+0.35*0.0031/bgratmva)))/(resultmva-bgratmva)+1)*100;
       cout<<" background from outside "<<errExternal<<" ana1x "<<errExternalana1x<<endl;
	resultmva = 0.616;//return normal

	float unoise=3;
	float uhiteff=0.23;
  	float upe=2.4;
 
	float slope_noise_bkgonly_nom = 0.1598;//%
        float slope_noise_bkgonly_ana1x = 0.1041;//%

        cout<<"noise bkgonly nom "<<slope_noise_bkgonly_nom*unoise<<" ana1x "<<slope_noise_bkgonly_ana1x*unoise<<endl;


        float slope_hiteff_bkgonly_nom = 12.88;//%
	float slope_hiteff_bkgonly_ana1x = 10.77;//%
    
   	 cout<<"hiteff bkgonly nom "<<slope_hiteff_bkgonly_nom*uhiteff<<" ana1x "<<slope_hiteff_bkgonly_ana1x*uhiteff<<endl;


	float slope_pe_bkgonly_nom = 5.624;//%
	float slope_pe_bkgonly_ana1x = 4.315;//%
    
    	cout<<"pe bkgonly nom "<<slope_pe_bkgonly_nom*upe<<" ana1x "<<slope_pe_bkgonly_ana1x*upe<<endl;

//birk effect
cout<<"CHECK BIRK effect"<<endl;
//double result = 0.63;
double nom_nomsig = 231.652;
double nom_plussig = 237.269;
double nom_minussig = 222.993;

double nom_nombkg = 203.866;
double nom_plusbkg = 219.544;
double nom_minusbkg = 191.992;

double datafix = result*(nom_nomsig+nom_nombkg);//keep unchange
double xsecnom_nom = (datafix - nom_nombkg)/nom_nomsig;//data-background/signal efficiency
double xsecnom_plus = (datafix - nom_plusbkg)/nom_plussig;
double xsecnom_minus = (datafix - nom_minusbkg)/nom_minussig;

double nom_shiftplus = TMath::Abs((xsecnom_plus/xsecnom_nom-1))*100;
double nom_shiftminus = TMath::Abs((xsecnom_minus/xsecnom_nom-1))*100;
cout<<"nom shift plus "<<nom_shiftplus<<" minus "<<nom_shiftminus<<endl;


cout<<"BIRK effect in Analysis I"<<endl;
    double ana1x_nomsig = 336.162;
    double ana1x_plussig = 330.894;
    double ana1x_minussig = 321.684;
    
    double ana1x_nombkg = 276.337;
    double ana1x_plusbkg = 284.236;
    double ana1x_minusbkg = 269.292;
    
    double resultmva=0.616;
    double datafix = resultmva*(ana1x_nomsig+ana1x_nombkg);//keep unchange
    double xsecana1x_nom = (datafix - ana1x_nombkg)/ana1x_nomsig;//data-background/signal efficiency
    double xsecana1x_plus = (datafix - ana1x_plusbkg)/ana1x_plussig;
    double xsecana1x_minus = (datafix - ana1x_minusbkg)/ana1x_minussig;
    
    double ana1x_shiftplus = TMath::Abs((xsecana1x_plus/xsecana1x_nom-1))*100;
    double ana1x_shiftminus = TMath::Abs((xsecana1x_minus/xsecana1x_nom-1))*100;
    cout<<"ana1x shift plus "<<ana1x_shiftplus<<" minus "<<ana1x_shiftminus<<endl;

    //change the rate 
    resultmva = 0.671;//
    datafix = resultmva*(ana1x_nomsig+ana1x_nombkg);//keep unchange
     xsecana1x_nom = (datafix - ana1x_nombkg)/ana1x_nomsig;//data-background/signal efficiency
     xsecana1x_plus = (datafix - ana1x_plusbkg)/ana1x_plussig;
     xsecana1x_minus = (datafix - ana1x_minusbkg)/ana1x_minussig;

     ana1x_shiftplus = TMath::Abs((xsecana1x_plus/xsecana1x_nom-1))*100;
     ana1x_shiftminus = TMath::Abs((xsecana1x_minus/xsecana1x_nom-1))*100;
    cout<<"rat04 ana1x shift plus "<<ana1x_shiftplus<<" minus "<<ana1x_shiftminus<<endl;

cout<<"BIRK effect in Analysis II"<<endl;
    double ana2x_nomsig = 246.496;
    double ana2x_plussig = 241.615;
    double ana2x_minussig = 230.851;
    
    double ana2x_nombkg = 124.515;
    double ana2x_plusbkg = 132.491;
    double ana2x_minusbkg = 121.043;
    
    double resultmva_ana2x=0.535;
    double datafix = resultmva_ana2x*(ana2x_nomsig+ana2x_nombkg);//keep unchange
    double xsecana2x_nom = (datafix - ana2x_nombkg)/ana2x_nomsig;//data-background/signal efficiency
    double xsecana2x_plus = (datafix - ana2x_plusbkg)/ana2x_plussig;
    double xsecana2x_minus = (datafix - ana2x_minusbkg)/ana2x_minussig;
    
    double ana2x_shiftplus = TMath::Abs((xsecana2x_plus/xsecana2x_nom-1))*100;
    double ana2x_shiftminus = TMath::Abs((xsecana2x_minus/xsecana2x_nom-1))*100;
    cout<<"ana2x_ shift plus "<<ana2x_shiftplus<<" minus "<<ana2x_shiftminus<<endl;

resultmva_ana2x = 0.601;
datafix = resultmva_ana2x*(ana2x_nomsig+ana2x_nombkg);//keep unchange
     xsecana2x_nom = (datafix - ana2x_nombkg)/ana2x_nomsig;//data-background/signal efficiency
     xsecana2x_plus = (datafix - ana2x_plusbkg)/ana2x_plussig;
     xsecana2x_minus = (datafix - ana2x_minusbkg)/ana2x_minussig;

     ana2x_shiftplus = TMath::Abs((xsecana2x_plus/xsecana2x_nom-1))*100;
     ana2x_shiftminus = TMath::Abs((xsecana2x_minus/xsecana2x_nom-1))*100;
    cout<<"rat04 ana2x_ shift plus "<<ana2x_shiftplus<<" minus "<<ana2x_shiftminus<<endl;

//PE variation effect
    cout<<"CHECK PE variation effect in previous Analysis"<<endl;
     result = 0.63;
     nom_nomsig = 231.652;
     nom_plussig = 221.919;
     nom_minussig = 235.189;
    
     nom_nombkg = 203.866;
     nom_plusbkg = 191.742;
     nom_minusbkg = 212.293;
    
     datafix = result*(nom_nomsig+nom_nombkg);//keep unchange
     xsecnom_nom = (datafix - nom_nombkg)/nom_nomsig;//data-background/signal efficiency
     xsecnom_plus = (datafix - nom_plusbkg)/nom_plussig;
     xsecnom_minus = (datafix - nom_minusbkg)/nom_minussig;
    
     nom_shiftplus = TMath::Abs((xsecnom_plus/xsecnom_nom-1))*100;
     nom_shiftminus = TMath::Abs((xsecnom_minus/xsecnom_nom-1))*100;
    cout<<"nom shift plus "<<nom_shiftplus<<" minus "<<nom_shiftminus<<endl;
    
    
    cout<<"CHECK PE variation effect in Analysis I"<<endl;
     ana1x_nomsig = 336.162;
     ana1x_plussig = 334.423;
     ana1x_minussig = 337.232;
    
     ana1x_nombkg = 276.337;
     ana1x_plusbkg = 269.805;
     ana1x_minusbkg = 285.909;
    
     resultmva=0.616;
     datafix = resultmva*(ana1x_nomsig+ana1x_nombkg);//keep unchange
     xsecana1x_nom = (datafix - ana1x_nombkg)/ana1x_nomsig;//data-background/signal efficiency
     xsecana1x_plus = (datafix - ana1x_plusbkg)/ana1x_plussig;
     xsecana1x_minus = (datafix - ana1x_minusbkg)/ana1x_minussig;
    
     ana1x_shiftplus = TMath::Abs((xsecana1x_plus/xsecana1x_nom-1))*100;
     ana1x_shiftminus = TMath::Abs((xsecana1x_minus/xsecana1x_nom-1))*100;
    cout<<"ana1x shift plus "<<ana1x_shiftplus<<" minus "<<ana1x_shiftminus<<endl;
   //change the rate 
    resultmva = 0.671;//
    datafix = resultmva*(ana1x_nomsig+ana1x_nombkg);//keep unchange
     xsecana1x_nom = (datafix - ana1x_nombkg)/ana1x_nomsig;//data-background/signal efficiency
     xsecana1x_plus = (datafix - ana1x_plusbkg)/ana1x_plussig;
     xsecana1x_minus = (datafix - ana1x_minusbkg)/ana1x_minussig;

     ana1x_shiftplus = TMath::Abs((xsecana1x_plus/xsecana1x_nom-1))*100;
     ana1x_shiftminus = TMath::Abs((xsecana1x_minus/xsecana1x_nom-1))*100;
    cout<<"rat04 ana1x shift plus "<<ana1x_shiftplus<<" minus "<<ana1x_shiftminus<<endl;
 
    cout<<"CHECK PE variation effect in Analysis II"<<endl;
     ana2x_nomsig = 246.496;
     ana2x_plussig = 241.168;
     ana2x_minussig = 251.545;
    
     ana2x_nombkg = 124.515;
     ana2x_plusbkg = 119.383;
     ana2x_minusbkg = 129.316;
    
     resultmva_ana2x=0.535;
     datafix = resultmva_ana2x*(ana2x_nomsig+ana2x_nombkg);//keep unchange
     xsecana2x_nom = (datafix - ana2x_nombkg)/ana2x_nomsig;//data-background/signal efficiency
     xsecana2x_plus = (datafix - ana2x_plusbkg)/ana2x_plussig;
     xsecana2x_minus = (datafix - ana2x_minusbkg)/ana2x_minussig;
    
     ana2x_shiftplus = TMath::Abs((xsecana2x_plus/xsecana2x_nom-1))*100;
     ana2x_shiftminus = TMath::Abs((xsecana2x_minus/xsecana2x_nom-1))*100;
    cout<<"ana2x_ shift plus "<<ana2x_shiftplus<<" minus "<<ana2x_shiftminus<<endl;

resultmva_ana2x = 0.601;
datafix = resultmva_ana2x*(ana2x_nomsig+ana2x_nombkg);//keep unchange
     xsecana2x_nom = (datafix - ana2x_nombkg)/ana2x_nomsig;//data-background/signal efficiency
     xsecana2x_plus = (datafix - ana2x_plusbkg)/ana2x_plussig;
     xsecana2x_minus = (datafix - ana2x_minusbkg)/ana2x_minussig;

     ana2x_shiftplus = TMath::Abs((xsecana2x_plus/xsecana2x_nom-1))*100;
     ana2x_shiftminus = TMath::Abs((xsecana2x_minus/xsecana2x_nom-1))*100;
    cout<<"rat04 ana2x_ shift plus "<<ana2x_shiftplus<<" minus "<<ana2x_shiftminus<<endl;

/*double nom_resultplus = result*(nom_nomsig+nom_nombkg)/(nom_plussig+nom_plusbkg);
double nom_resultminus = result*(nom_nomsig+nom_nombkg)/(nom_minussig+nom_minusbkg);

double nom_bgratplus = nom_plusbkg/(nom_plussig+nom_plusbkg);
double nom_bgratminus = nom_minusbkg/(nom_minussig+nom_minusbkg);
cout<<"nom "<<result<<"/"<<bgrat<<" plus "<<nom_resultplus<<"/"<<nom_bgratplus<<" minus "<<nom_resultminus<<"/"<<nom_bgratminus<<endl;
double shiftplus = TMath::Abs((nom_resultplus-nom_bgratplus)*((nom_plussig+nom_plusbkg)/nom_plussig)/((result-bgrat)*((nom_nomsig+nom_nombkg)/nom_nomsig))-1)*100;
double shiftminus = TMath::Abs((nom_resultminus-nom_bgratminus)*(nom_minussig+nom_minusbkg)/((result-bgrat)*(nom_nomsig+nom_nombkg))-1)*100;
cout<<"shift plus "<<shiftplus<<"% "<<" minus "<<shiftminus<<"%"<<endl;
*/
}
