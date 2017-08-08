2017-05-24
this for neut 5.3.2, copied form neut532-nosignal branch
Four the fourth sample, using more than four samples to constrain CCNpi

0. pull to scbn:/home/cvson/cc1picoh/FIT/pmcc1picoh_git_neut532
1. fit on 1 bins of p-theta --> test binning
2. Four sample maximum -Signal (pidfsid>0.05 && veract<50), cr1 (pidfsi<0.05 & veract<50  && mumucl>0.6 && pmucl>0.25), cr2 (pidfsi<0.05 & veract<50 && mumucl>0.6 && pmucl<0.25) cr3 (Ntrk>2 && pidfsi<0.05 & veract<50 && mumucl<0.6)
3. response function:use v1r25 t2kreweight, major parameter, CA5, axial mass, bkg. scale, DIS shape, MACCQE, MEC Norm, FSI
...Parameter range defined in src/XsecParameters::XsecParameters, all zero for priors, limit from -5 sigma to 5 sigma, except PilessDcy, from -1.0 to 1.0
4. included obervable information of vertex activity, other angles, Qsq
