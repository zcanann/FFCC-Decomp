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
class CFlatRuntime;
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

enum CFlatEventFlagByte {
    CFlatEventFlagByte_GbaSound = 0x08,
};

static inline u32& CFlatRuntimeDebugFlags()
{
    return *reinterpret_cast<u32*>(CFlat + 0x129C);
}

static inline CFlatRuntime& gCFlatRuntime()
{
    return *reinterpret_cast<CFlatRuntime*>(CFlat);
}

static inline CFlatRuntime2& CFlatRuntime2Storage()
{
    return *reinterpret_cast<CFlatRuntime2*>(CFlat);
}

static inline int& CFlatPermanentVarCount()
{
    return *reinterpret_cast<int*>(CFlat + 0x4);
}

static inline unsigned char*& CFlatPermanentVarDefs()
{
    return *reinterpret_cast<unsigned char**>(CFlat + 0x8);
}

static inline unsigned char*& CFlatPermanentVarValues()
{
    return *reinterpret_cast<unsigned char**>(CFlat + 0xC);
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

static inline u8& CFlatEventFlagsByte()
{
    return CFlat[0x12A0];
}

static inline u32& CFlatCenterState()
{
    return *reinterpret_cast<u32*>(CFlat + 0x12AC);
}

static inline float& CFlatCenterDistanceScale()
{
    return *reinterpret_cast<float*>(CFlat + 0x12B0);
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

static inline u32& CFlatSpawnBitLo(int index)
{
    return *reinterpret_cast<u32*>(CFlat + 0x12F0 + index * 8);
}

static inline u32& CFlatSpawnBitHi(int index)
{
    return *reinterpret_cast<u32*>(CFlat + 0x12F4 + index * 8);
}

static inline int& CFlatItemCarryMode()
{
    return *reinterpret_cast<int*>(CFlat + 0x4780);
}

static inline int& CFlatLetterEventEnabled()
{
    return *reinterpret_cast<int*>(CFlat + 0x10408);
}

static inline int& CFlatItemTraceParticleSlot()
{
    return *reinterpret_cast<int*>(CFlat + 0x1042C);
}

static inline float& CFlatMoveTime()
{
    return *reinterpret_cast<float*>(CFlat + 0x1338);
}

static inline float& CFlatBgCollisionTime()
{
    return *reinterpret_cast<float*>(CFlat + 0x133C);
}

static inline float& CFlatObjectCollisionTime()
{
    return *reinterpret_cast<float*>(CFlat + 0x1340);
}

static inline float& CFlatUpdateTime()
{
    return *reinterpret_cast<float*>(CFlat + 0x1344);
}

static inline float& CFlatHitTime()
{
    return *reinterpret_cast<float*>(CFlat + 0x1348);
}

#endif // _FFCC_LINKAGE_H_
