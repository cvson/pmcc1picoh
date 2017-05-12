{

	const Int_t NSYSTCAT = 5;//xsec x3 + bkg x2
	Double_t fluxUn[NSYSTCAT][2];
	fluxUn[0][0] = 43.72;
	fluxUn[0][1] = -36.15;

	fluxUn[1][0] = 41.76;
	fluxUn[1][1] = -34.59;

	fluxUn[2][0] = 34.00;
	fluxUn[2][1] = -28.05;

	fluxUn[3][0] = 10.44;
	fluxUn[3][1] = 10.44;

	fluxUn[4][0] = 10.31;
	fluxUn[4][1] = 10.31;
	//xsec
	Double_t xsecUn[NSYSTCAT][2];
    	xsecUn[0][0] = 49.02;
    	xsecUn[0][1] = -50.56;
    
    	xsecUn[1][0] = 39.47;
    	xsecUn[1][1] = -40.64;
    
   	 xsecUn[2][0] = 29.60;
    	xsecUn[2][1] = -30.48;
    
   	 xsecUn[3][0] = 20.00;
    	xsecUn[3][1] = -20.62;
    
    	xsecUn[4][0] = 17.01;
    	xsecUn[4][1] = -17.52;

	//det
	Double_t detUn[NSYSTCAT][2];
    	detUn[0][0] = 43.72;
    	detUn[0][1] = -36.15;
    
   	 detUn[1][0] = 41.76;
    	detUn[1][1] = -34.59;
    
    	detUn[2][0] = 34.00;
    	detUn[2][1] = -28.05;
    
    	detUn[3][0] = 10.44;
   	 detUn[3][1] = 10.44;
    
    	detUn[4][0] = 10.31;
    	detUn[4][1] = 10.31;

	Double_t detUnTOT[NSYSTCAT][14];
	detUnTOT[0][*]={0.97,0.78,5.14,23.87,0.31,0.17,0.00,1.91,3.76,6.26,3.79,0.0,5.55,10.74};


}
