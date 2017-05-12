//char cccoh[200]="Ntrack==2&&mumucl>0.6&&pmucl>0.25&&muang_t<15&&veract<420";
//char cccoh[200]="Ntrack==2&&mumucl>0.6&&pmucl>0.25&&muang_t<15&&veract*7.6634e-2<34";
char cccoh[200]="Ntrack==2&&mumucl>0.6&&pmucl>0.25&&pang<90&&muang_t<15&&veract*7.66339869e-2<34";
//char cccohmva[200]="Ntrack==2 && pang<90 && !(mufc==0 && pene<9) && pidfsi>0.05 && veract*7.6634e-2<50 && pidfsi1prescor>-0.05 && pidfsiccqecor<0.0";
char cccohmva[200]="Ntrack==2 && pang<90 && !(mufc==0 && pene<9) && pidfsi>0.05 && veract*7.6634e-2<50";
char ccincl[200]="1";

//float result=0.619;
//float result_qe=0.305;
//float bgrat=0.4516;
//from Kikawa-san 
//float result=0.6305;
//float result_qe=0.307;
//float bgrat=0.4665;

//float result=0.630;//ratio of data to prediction?
float result=0.63;//result_qe + (1-result_qe)*bgrat
//float result_qe=0.3044;//(0.63-0.4681)/(1-0.4681)
float result_qe=0.30;//data-bkg/sig
float bgrat=0.4681;//1-purity?

////float resultmva=0.700280112;//380/542.64
//float resultmva=0.616;//0.30 + 0.7*0.4512
//float result_qemva=0.30;//assume (data-bkg)/signal
float resultmva=0.671;//0.40 + 0.6*0.4512
float result_qemva=0.40;//assume (data-bkg)/signal
//float result_qemva=0.472;
float bgratmva=0.4512;//1-purity

