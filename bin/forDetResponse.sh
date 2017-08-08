#!/bin/sh 
 ./generateDetectorResponsePEvar.exe 
 ./generateDetectorResponseBirk.exe 
 ./generateDetectorResponseReco.exe 
 ./generateDetectorResponseFVTime.exe 
 ./generateDetectorResponseNoise.exe 
 ./generateDetectorResponseHitEff.exe

#root -b -q ../macros/t2kpre_plotDetResponse_pevar_1bin.C
#root -b -q ../macros/t2kpre_plotDetResponse_birk_1bin.C
#root -b -q ../macros/t2kpre_plotDetResponseReco_1bin.C
#root -b -q ../macros/t2kpre_plotDetResponse_FVTime_1bin.C
#root -b -q ../macros/t2kpre_plotDetResponse_FVTime_nosig_1bin.C
#root -b -q ../macros/t2kpre_plotDetResponse_hiteff_1bin.C
# root -b -q ../macros/t2kpre_plotDetResponse_hiteff_1bin_nosb.C
#root -b -q ../macros/t2kpre_plotDetResponse_noise_1bin.C
#root -b -q ../macros/t2kpre_plotDetResponse_noise_1bin_nosb.C
#root -b -q ../macros/t2kpre_plotAllDetUncertaintyNew_1bin.C

