#ifndef _FFCC_PPP_LINKAGE_H_
#define _FFCC_PPP_LINKAGE_H_

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern int ppvUserStopPartF;
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
extern signed char gPppInSubFrameCalc;
extern unsigned char ppvIsLoopCalc;
extern unsigned char ppvIs2ndCalc;

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_LINKAGE_H_
