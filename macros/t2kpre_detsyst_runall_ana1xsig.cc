#define HE
//#define LE

#include "common.h"
#include "t2kpre_detsyst_macro_systematic2_ana1xsig.cc"
#include " t2kpre_detsyst_macro_systematic3_ana1xsig.cc"
#include "t2kpre_detsyst_macro_systematic_ana1xsig.cc"

#include "t2kpre_detsyst_hiteff_draw_cccoh_ana1xsig.C"
#include "t2kpre_detsyst_hiteff_getevt_cccoh_ana1xsig.C"

#include "t2kpre_detsyst_noise_draw_cccoh_ana1xsig.C"
#include "t2kpre_detsyst_noise_getevt_cccoh_ana1xsig.C"

#include "t2kpre_detsyst_pe_draw_cccoh_ana1xsig.C"
#include "t2kpre_detsyst_pe_getevt_cccoh_ana1xsig.C"

void t2kpre_detsyst_runall_ana1xsig(){
	t2kpre_detsyst_macro_systematic2_ana1xsig();
	t2kpre_detsyst_macro_systematic3_ana1xsig();
	t2kpre_detsyst_macro_systematic_ana1xsig();

        t2kpre_detsyst_hiteff_draw_cccoh_ana1xsig();
	t2kpre_detsyst_hiteff_getevt_cccoh_ana1xsig();

	t2kpre_detsyst_noise_draw_cccoh_ana1xsig();
	t2kpre_detsyst_noise_getevt_cccoh_ana1xsig()

	t2kpre_detsyst_pe_draw_cccoh_ana1xsig();
	t2kpre_detsyst_pe_getevt_cccoh_ana1xsig();

	
}
