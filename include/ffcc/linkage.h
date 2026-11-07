#ifndef _FFCC_LINKAGE_H_
#define _FFCC_LINKAGE_H_

#include "global.h"
#include "dolphin/mtx.h"
#include "ffcc/cflat_runtime2.h"

extern CFlatRuntime2 CFlat;
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
extern CMapMng g_MapMng;
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
extern CFlatRuntime2& gCFlatRuntime2;
class CChara;
extern CChara& gChara;

enum CFlatRuntimeDebugFlag {
    CFlatRuntimeDebugFlag_QuadBounds = 0x00010000,
    CFlatRuntimeDebugFlag_ParticleLines = 0x00020000,
    CFlatRuntimeDebugFlag_ClassCollision = 0x00100000,
    CFlatRuntimeDebugFlag_ParticleHitSpheres = 0x00200000,
    CFlatRuntimeDebugFlag_Sound = 0x00400000,
    CFlatRuntimeDebugFlag_Wind = 0x00800000,
    CFlatRuntimeDebugFlag_Camera = 0x01000000,
    CFlatRuntimeDebugFlag_MapBounds = 0x02000000,
};

enum CFlatEventFlagByte {
    CFlatEventFlagByte_GbaSound = 0x08,
};

#endif // _FFCC_LINKAGE_H_
