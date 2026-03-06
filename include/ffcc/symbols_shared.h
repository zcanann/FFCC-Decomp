#ifndef _FFCC_SYMBOLS_SHARED_H_
#define _FFCC_SYMBOLS_SHARED_H_

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern float kPppAcceleZero;
extern float kPppMoveZero;
extern const float kPppKeLnsZero;
extern const float kKeLnsLineDefaultLength;
extern float kPppBreathModelZero;
extern float kPppChangeTexInit;
extern char kAStarGroupDebugLabel[];
extern f32 kVecInvSqrtHalfConst;
extern f32 kVecInvSqrtThreeConst;
extern unsigned int gGbaStatusWordTriplet0[];
extern unsigned int gGbaStatusWordTriplet1[];
extern unsigned int gGbaStatusWordTriplet2[];
extern unsigned int gGbaStatusWordTriplet3[];
extern unsigned int gGbaStatusWordTable[];
extern u8 gSingMenuItemIconByType[];
extern char* gSingMenuTextTableEn[];
extern char* gSingMenuTextTableDe[];
extern char* gSingMenuTextTableIt[];
extern char* gSingMenuTextTableFr[];
extern char* gSingMenuTextTableEs[];
extern char* gSingMenuHairTableFr[];
extern char* gSingMenuAttrTableEn[];
extern char* gSingMenuAttrTableDe[];
extern char* gSingMenuAttrTableIt[];
extern char* gSingMenuAttrTableFr[];
extern char* gSingMenuAttrTableEs[];
extern unsigned char gMenuProcessTable[];
extern f32 kMenuInitOne;

#ifdef __cplusplus
}
#endif

#endif // _FFCC_SYMBOLS_SHARED_H_
