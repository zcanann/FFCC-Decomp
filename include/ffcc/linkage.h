#ifndef _FFCC_LINKAGE_H_
#define _FFCC_LINKAGE_H_

#include "global.h"
#include "dolphin/mtx.h"

// Canonical linkage declarations for globals that are still represented as
// raw storage in decomped units.
extern unsigned char CFlat[];
extern unsigned char Chara[];
class CMaterialMan;
extern CMaterialMan MaterialMan;
extern u32 CFlatFlags;
extern Mtx gFlatPosMtx;

#endif // _FFCC_LINKAGE_H_
