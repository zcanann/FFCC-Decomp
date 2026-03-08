#ifndef _FFCC_LINKAGE_H_
#define _FFCC_LINKAGE_H_

#include "global.h"
#include "dolphin/mtx.h"

// Canonical linkage declarations for globals that are still represented as
// raw storage in decomped units.
extern unsigned char CFlat[0x10440];
extern unsigned char Chara[0x2078];
class CMaterialMan;
extern CMaterialMan MaterialMan;
class CMapMng;
extern CMapMng MapMng;
class CGamePcs;
extern CGamePcs Game;
class CSound;
extern CSound Sound;
class CAmemCacheSet;
extern CAmemCacheSet ppvAmemCacheSet;
extern u32 CFlatFlags;
extern Mtx gFlatPosMtx;

#endif // _FFCC_LINKAGE_H_
