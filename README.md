2017-05-12
this is based version to be managed by GIT
0. pull to scbn:/home/cvson/cc1picoh/FIT/pmcc1picoh_base4copy
1. fit on 5 bins of p-theta
2. Four sample maximum -Signal: from analysis I, veract <50 MeV -Sideband -Antipid with cc1pi-enhanced -Antipid with CC0pi-enhanced
3. response function: -- use v1r19piless02 cor: tot_merged_ccqe_forResponseFunction_pionFS_v1r19piless02cor.root -- fix float issue -- 7 parameters: 1-MACCQE, 2-MAres, 3-CC1piE0, 4-CC1piE1, 5-CCoth, 6-PilessDcy, 7-allelse
...Parameter range defined in src/XsecParameters::XsecParameters, all zero for priors, limit from -5 sigma to 5 sigma, except PilessDcy, from -1.0 to 1.0
4. included obervable information of vertex activity, other angles, Qsq
