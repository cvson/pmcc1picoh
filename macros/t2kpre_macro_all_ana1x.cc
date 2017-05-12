#define HE
//#define LE

#include "common.h"
#include "t2kpre_macro_systematic.cc"
#include "t2kpre_macro_systematic2.cc"
#include "t2kpre_macro_systematic3.cc"

void t2kpre_macro_all(){
  t2kpre_macro_systematic();
  t2kpre_macro_systematic2();
  t2kpre_macro_systematic3();
}
