#!/bin/sh
root -b -q t2kpre_plotDetResponse_pevar_6sam.C
root -b -q t2kpre_plotDetResponse_birk_6sam.C

root -b -q t2kpre_plotDetResponseReco_6sam.C
root -b -q t2kpre_plotDetResponseReco_nosig_6sam.C

root -b -q t2kpre_plotDetResponse_FVTime_nosig_6sam.C

root -b -q t2kpre_plotDetResponse_noise_6sam.C
root -b -q t2kpre_plotDetResponse_noise_nosb_6sam.C

root -b -q t2kpre_plotDetResponse_hiteff_6sam.C
root -b -q t2kpre_plotDetResponse_hiteff_nosb_6sam.C

cd ../inputs
#rm -rf detresponse_FVTime_5bptheta_newFV_fixReweight.root
#ln -s detresponse_FVTime.root detresponse_FVTime_5bptheta_newFV_fixReweight.root
root -b -q t2kpre_plotAllDetUncertaintyNew_6sam.C

