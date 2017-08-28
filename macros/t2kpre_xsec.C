{
	double Ntarget = 1.3837e28; //times e28
	double Efficiency = 0.1604;//Kikawa sel neut 5.1.4.2
	double Flux = 3.0254e13;//per cm2
	double NSignal = 229.3;
	double cohxsec = NSignal/(Flux*Ntarget*Efficiency);
	cout<<"cross section "<<cohxsec<<endl; 
	
	double NSignlGENIE;

	//mva selection
	double NSIG_NEUT532 = 330.198;
	double Eff_NEUT532;

	double NSIG_NEUT5142 = 336.163;
	double Eff_NEUT5142;

	double NSIG_GENIE = 162.082;
	double Eff_GENIE;


}
