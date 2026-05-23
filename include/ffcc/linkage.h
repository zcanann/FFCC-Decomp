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

enum CFlatGameFlag {
    CFlatGameFlag_Bit0 = 0x01,
    CFlatGameFlag_Bit1 = 0x02,
    CFlatGameFlag_Mark = 0x04,
    CFlatGameFlag_Bit5 = 0x20,
    CFlatGameFlag_Shouki = 0x80,
};

static inline u32& CFlatRuntimeDebugFlags()
{
    return *reinterpret_cast<u32*>(CFlat + 0x129C);
}

static inline u32& CFlatEventFlags()
{
    return *reinterpret_cast<u32*>(CFlat + 0x12A0);
}

static inline u32& CFlatEventMask()
{
    return *reinterpret_cast<u32*>(CFlat + 0x12A4);
}

static inline u32 CFlatEnabledEventFlags()
{
    return CFlatEventFlags() & CFlatEventMask();
}

static inline u32& CFlatCenterState()
{
    return *reinterpret_cast<u32*>(CFlat + 0x12AC);
}

static inline u8& CFlatGameFlags()
{
    return CFlat[0x12E4];
}

static inline int& CFlatBossState()
{
    return *reinterpret_cast<int*>(CFlat + 0x12E8);
}

static inline int& CFlatBossSubState()
{
    return *reinterpret_cast<int*>(CFlat + 0x12EC);
}

#endif // _FFCC_LINKAGE_H_
