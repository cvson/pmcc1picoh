2017-09-07
this for neut 5.3.2, copied form neut532-fixresf-fin3bin branch
Use sample with low vertex activity cut and skipp repsonse function for numubar, nue, wall and ingrid
Using 6 samples, three low vertex and three high vertex
For data in sideband, can stat. fluctuate

0. pull to scbn:/home/cvson/cc1picoh/FIT/pmcc1picoh_git_neut532
1. fit on 3 bins of p-theta 
2. Four sample maximum -Signal (pidfsid>0.08 && mumucl>0.6 && pmucl>0.25), sideband (pidfsi<0.08 && mumucl>0.6 && pmucl>0.25), sideband (pidfsi<0.08 && mumucl>0.6 && pmucl<0.25) sideband (pidfsi<0.08 && mumucl<0.6)
3. response function:use v1r25 t2kreweight, major parameter, CA5, axial mass, bkg. scale, DIS shape, MACCQE, MEC Norm, FSI
...Parameter range defined in src/XsecParameters::XsecParameters, all zero for priors, limit from -5 sigma to 5 sigma, except PilessDcy, from -1.0 to 1.0
4. included obervable information of vertex activity, other angles, Qsq
