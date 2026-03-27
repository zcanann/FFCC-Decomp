#ifndef _FFCC_LINKAGE_H_
#define _FFCC_LINKAGE_H_

#include "global.h"
#include "dolphin/mtx.h"

// Canonical linkage declarations for globals that are still represented as
// raw storage in decomped units.
extern unsigned char CFlat[0x10440];
class CChara;
extern CChara Chara;
class CFile;
extern CFile File;
class CGraphic;
extern CGraphic Graphic;
class GbaQueue;
extern GbaQueue GbaQue;
class JoyBus;
extern JoyBus Joybus;
class CMaterialMan;
extern CMaterialMan MaterialMan;
class CMapMng;
extern CMapMng MapMng;
class CMemory;
extern CMemory Memory;
class CMemoryCardMan;
extern CMemoryCardMan MemoryCardMan;
class CGame;
extern CGame Game;
class CGamePcs;
extern CGamePcs GamePcs;
class CMenuPcs;
extern CMenuPcs MenuPcs;
class CMaterialEditorPcs;
extern CMaterialEditorPcs MaterialEditorPcs;
class CCameraPcs;
extern CCameraPcs CameraPcs;
class CCharaPcs;
extern CCharaPcs CharaPcs;
class CPad;
extern CPad Pad;
class CSound;
extern CSound Sound;
class CSystem;
extern CSystem System;
class CUSB;
extern CUSB USB;
class CAmemCacheSet;
extern CAmemCacheSet ppvAmemCacheSet;
extern u32 CFlatFlags;
extern Mtx gFlatPosMtx;
class CFlatRuntime2;
extern CFlatRuntime2& gCFlatRuntime2;
class CChara;
extern CChara& gChara;

#endif // _FFCC_LINKAGE_H_
