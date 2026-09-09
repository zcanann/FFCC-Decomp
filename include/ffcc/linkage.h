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

enum CFlatEventFlagByte {
    CFlatEventFlagByte_GbaSound = 0x08,
};

static inline u8* CFlatBytes()
{
    return reinterpret_cast<u8*>(&CFlat);
}

static inline CFlatRuntime2& CFlatRuntime2Storage()
{
    return CFlat;
}

static inline u32& CFlatRuntimeDebugFlags()
{
    return CFlatRuntime2Storage().m_debugFlags;
}

static inline CFlatRuntime& gCFlatRuntime()
{
    return CFlat;
}

static inline float& CFlatPerformanceTotalTime()
{
    return gCFlatRuntime().m_performance.m_totalTime;
}

static inline u32& CFlatEventFlags()
{
    return CFlatRuntime2Storage().m_eventFlags;
}

static inline u32& CFlatEventMask()
{
    return CFlatRuntime2Storage().m_eventMask;
}

static inline u32 CFlatEnabledEventFlags()
{
    return CFlatEventFlags() & CFlatEventMask();
}

static inline u8& CFlatEventFlagsByte()
{
    return reinterpret_cast<u8*>(&CFlatRuntime2Storage().m_eventFlags)[0];
}

static inline u32& CFlatCenterState()
{
    return CFlatRuntime2Storage().m_centerState;
}

static inline float& CFlatCenterDistanceScale()
{
    return CFlatRuntime2Storage().m_centerDistanceScale;
}

static inline Mtx& CFlatCenterMatrix()
{
    return CFlatRuntime2Storage().m_centerMatrix;
}

static inline u8& CFlatGameFlags()
{
    return CFlatRuntime2Storage().m_gameFlags;
}

static inline int& CFlatBossState()
{
    return CFlatRuntime2Storage().m_bossState;
}

static inline int& CFlatBossSubState()
{
    return CFlatRuntime2Storage().m_bossSubState;
}

static inline u64& CFlatSpawnBits(int index)
{
    return CFlatRuntime2Storage().m_spawnBits[index];
}

static inline int& CFlatItemCarryMode()
{
    return reinterpret_cast<int&>(CFlatRuntime2Storage().m_centerState);
}

static inline int& CFlatLetterEventEnabled()
{
    return CFlatRuntime2Storage().m_letterEventEnabled;
}

static inline int& CFlatSaveSceneEnabled()
{
    return CFlatRuntime2Storage().m_saveSceneEnabled;
}

static inline int& CFlatPartyTraceParticleSlot(int port)
{
    return CFlatRuntime2Storage().m_partyTraceParticleSlot[port];
}

static inline int& CFlatItemTraceParticleSlot()
{
    return CFlatRuntime2Storage().m_itemTraceParticleSlot;
}

static inline Vec& CFlatParticleWorkPosition()
{
    return CFlatRuntime2Storage().m_particleWorkPos;
}

static inline float& CFlatMoveTime()
{
    return CFlatRuntime2Storage().m_moveTime;
}

static inline float& CFlatBgCollisionTime()
{
    return CFlatRuntime2Storage().m_bgCollisionTime;
}

static inline float& CFlatObjectCollisionTime()
{
    return CFlatRuntime2Storage().m_objectCollisionTime;
}

static inline float& CFlatUpdateTime()
{
    return CFlatRuntime2Storage().m_updateTime;
}

static inline float& CFlatHitTime()
{
    return CFlatRuntime2Storage().m_hitTime;
}

#endif // _FFCC_LINKAGE_H_
