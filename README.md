2017-05-12
this is based version to be managed by GIT
Use sample with no-vertex activity cut

0. pull to scbn:/home/cvson/cc1picoh/FIT/pmcc1picoh_git_onebin
1. fit on 1 bins of p-theta --> test binning
2. Four sample maximum -Signal (pidfsid>0.08 && mumucl>0.6 && pmucl>0.25), sideband (pidfsi<0.08 && mumucl>0.6 && pmucl>0.25), sideband (pidfsi<0.08 && mumucl>0.6 && pmucl<0.25) sideband (pidfsi<0.08 && mumucl<0.6)
3. response function: -- use v1r19piless02 cor: tot_merged_ccqe_forResponseFunction_pionFS_v1r19piless02cor.root -- fix float issue -- 7 parameters: 1-MACCQE, 2-MAres, 3-CC1piE0, 4-CC1piE1, 5-CCoth, 6-PilessDcy, 7-allelse
...Parameter range defined in src/XsecParameters::XsecParameters, all zero for priors, limit from -5 sigma to 5 sigma, except PilessDcy, from -1.0 to 1.0
4. included obervable information of vertex activity, other angles, Qsq
