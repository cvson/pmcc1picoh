2017-05-12
this is based version to be managed by GIT
This is to test using response function from signal for sideband
1. fit on 5 bins of p-theta

2. Four sample maximum
  -Signal: from analysis I, veract <50 MeV
  -Sideband
  -Antipid with cc1pi-enhanced
  -Antipid with CC0pi-enhanced 

3. response function: 
-- use v1r19piless02 cor: tot_merged_ccqe_forResponseFunction_pionFS_v1r19piless02cor.root
-- fix float issue
-- 7 parameters: 1-MACCQE, 2-MAres, 3-CC1piE0, 4-CC1piE1, 5-CCoth, 6-PilessDcy, 7-allelse

4. included obervable information of vertex activity, other angles, Qsq

5. use response function for signal sample to apply for sideband
XsecParameters::StoreResponseFunctions
sprintf(name,"response_sample%d_reaction%d_bin%d",stInt,rtInt+1,br);//this normal
—>sprintf(name,"response_sample%d_reaction%d_bin%d",s_SIG,rtInt+1,br);





