#!/bin/sh
root -b -q t2kpre_plotDetResponse_pevar.C
root -b -q t2kpre_plotDetResponse_birk.C

root -b -q t2kpre_plotDetResponseReco.C
root -b -q t2kpre_plotDetResponseReco_nosig.C

root -b -q t2kpre_plotDetResponse_FVTime_nosig.C

root -b -q t2kpre_plotDetResponse_noise.C
root -b -q t2kpre_plotDetResponse_noise_nosb.C

root -b -q t2kpre_plotDetResponse_hiteff.C
root -b -q t2kpre_plotDetResponse_hiteff_nosb.C


#cd ../inputs
#rm -rf detresponse_FVTime_5bptheta_newFV_fixReweight.root
#ln -s detresponse_FVTime.root detresponse_FVTime_5bptheta_newFV_fixReweight.root
root -b -q t2kpre_plotAllDetUncertaintyNew.C

