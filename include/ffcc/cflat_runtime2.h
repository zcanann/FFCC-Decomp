#ifndef _FFCC_CFLAT_RUNTIME2_H_
#define _FFCC_CFLAT_RUNTIME2_H_

#include "ffcc/cflat_runtime.h"
#include "ffcc/cflat_data.h"
#include "ffcc/gobject.h"
#include "ffcc/line.h"
#include "ffcc/memory.h"
#include "ffcc/file.h"
#include "ffcc/p_chara.h"
#include "ffcc/partMng.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class CGObject;
class CFlatRuntime;
class CGBaseObj;
class CGQuadObj;
class CGMonObj;
class CGItemObj;
class CTextureSet;
struct Vec;

struct CFlatLayerResource {
	int m_allocStage;
	CTextureSet* m_textureSet;
	CFile::CHandle* m_fileHandle;
};

struct CFlatPathPoint
{
	float m_distance;
	Vec m_position;
};

extern int gCFlatRuntime2DebugDrawOverflowFrame;
extern char gCFlatRuntime2DebugDrawOverflowInit;
extern const char sCFlatRuntime2DebugDrawOverflowMsg[];
extern u32 CFlatFlags;

class CFlatRuntime2 : public CFlatRuntime
{
public:
	struct CDebugDrawCC
	{
		union {
			u8 m_flags;
			struct {
				s8 m_bit7 : 1;
				s8 m_bit6 : 1;
				s8 m_bitsLow : 6;
			} m_flagBits;
		};
		u8 m_pad[3];
		Vec m_from;
		Vec m_to;
		float m_radius;
	};

	struct CMapObjectInfo
	{
		s8 m_type;
		s8 m_drawFlag;
		u8 m_pad02[2];
		float m_x;
		float m_y;
		float m_z;
		float m_radius;
	};

	class CParticleWork
	{
	public:
		CParticleWork()
		{
			m_soundEffectParams.m_soundEffectHandle = -1;
			m_soundEffectParams.m_soundEffectSlot = -1;
			m_soundEffectParams.m_soundEffectStopFlag = 0;
			m_soundEffectParams.m_soundEffectKind = 1;
			m_soundEffectParams.m_soundEffectStartFrame = 0;
			m_soundEffectParams.m_soundEffectStartedOnce = 0;
			m_soundEffectParams.m_soundEffectFadeFrames = 0x1E;
			m_hitParam.m_particleIndex = 0;
			m_hitParam.m_classId = 0;
			m_hitParam.m_hitObjectCount = 0;
			m_hitParam.m_hitFlags = 0;
			m_pos = 0;
			m_posVec = 0;
			m_scale = 0;
			m_target = 0;
			m_arg = 0;
			m_bind = 0;
			m_trace = 0;
			m_color0 = 0;
			m_color1 = 0;
			m_speed = 1.0f;
			m_colorLerp = 1.0f;
			m_enable = 0;
		}

		float* m_pos;
		float* m_posVec;
		float* m_scale;
		float* m_target;
		int m_arg;
		CFlatRuntime::CObject* m_bind;
		CFlatRuntime::CObject* m_trace;
		int m_color0;
		int m_color1;
		float m_speed;
		float m_colorLerp;
		u8 m_enable;
		u8 m_pad2D[3];
		PPPSEST m_soundEffectParams;
		PPPIFPARAM m_hitParam;
	};
	
	CFlatRuntime2();
	~CFlatRuntime2();

	virtual CMemory::CStage* getStage();
	virtual CMemory::CStage* getDebugStage();

	virtual void onNewObject(CFlatRuntime::CObject*);
	virtual void onDeleteObject(CFlatRuntime::CObject*);

	unsigned int getNumFreeObject(int);
	virtual CGObject* getFreeObject(int);
	virtual void* intToClass(int);

	virtual int Frame(int, int);
	int Load(char*);

	CGObject* FindGObjFirst();
	CGObject* FindGObjNext(CGObject*);

	CGBaseObj* FindGBaseObjFirst();
	CGBaseObj* FindGBaseObjNext(CGBaseObj*);

	CGQuadObj* FindGQuadObjFirst();
	CGQuadObj* FindGQuadObjNext(CGQuadObj*);

	CGMonObj* FindGMonObjFirst();
	CGMonObj* FindGMonObjNext(CGMonObj*);

	CGItemObj* FindGItemObjFirst();
	CGItemObj* FindGItemObjNext(CGItemObj*);

	virtual void Destroy();
	void Calc();
	void Draw();

	void AddDebugDrawCC(Vec*, Vec*, float, int, int);
	int CcClass2D(int, int, Vec*, float, float, int, CGObject **);

	void loadLayer(int, char*);
	unsigned int isLoadLayerASyncCompleted(int);
	void loadLayerASync(int, char*);
	void drawLayer(int, char*, int, int, int, int, int, int, float, float, _GXColor*, int);

	void PutParticle(int, Vec&, float);
	int PutParticleWork();
	void ResetParticleWork(int, int);

	void SetParticleWorkNo(int);
	void SetParticleWorkPos(Vec&, float);
	void SetParticleWorkTarget(Vec&);
	void SetParticleWorkVector(float, float);
	void SetParticleWorkScale(float);
	void SetParticleWorkCol(int, int, float);
	void SetParticleWorkTrace(CFlatRuntime::CObject*);
	void SetParticleWorkSpeed(float);
	void SetParticleWorkBind(CFlatRuntime::CObject*);
	void SetParticleWorkParam(int, CFlatRuntime::CObject*);
	void SetParticleWorkSe(int, int, int);

	int GetFreeParticleSlot();
	void EndParticleSlot(int, int);
	void EndParticle(CCharaPcs::CHandle*);
	void DeleteParticleSlot(int, int);
	void IgnoreParticle(int, CFlatRuntime::CObject*);

	void initAllFinished();
	virtual void reqFinished(int, CFlatRuntime::CObject*);

	void SysControl(int, int);
	int GetSysControl(int);

	void resetSpawnBit(int);
	void resetChangeScript();
	void ResetNewGame();

private:
	virtual int onSystemFunc(CFlatRuntime::CObject*, int, int, int&);
	virtual int onClassSystemFunc(CFlatRuntime::CObject*, int, int, int&);

	virtual CFlatRuntime::CVal* onSystemVal(CFlatRuntime::CObject*, int);
	virtual CFlatRuntime::CVal* onClassSystemVal(CFlatRuntime::CObject*, int);

	virtual void onSetSystemVal(int, CFlatRuntime::CStack*, int);
	virtual void onSetClassSystemVal(int, CFlatRuntime::CObject*, CFlatRuntime::CStack*, int);

public:
	u32 m_debugFlags;               // 0x129C
	u32 m_eventFlags;               // 0x12A0
	u32 m_eventMask;                // 0x12A4
	u32 m_padInputDisableMask;      // 0x12A8
	u32 m_centerState;              // 0x12AC
	float m_centerDistanceScale;    // 0x12B0
	Mtx m_centerMatrix;             // 0x12B4
	union {
		u8 m_gameFlags;             // 0x12E4
		struct {
			s8 m_flagBit7 : 1;
			s8 m_flagBit6 : 1;
			s8 m_flagBit5 : 1;
			s8 m_flagBit4 : 1;
			s8 m_flagBit3 : 1;
			s8 m_flagBit2 : 1;
			s8 m_flagBit1 : 1;
			s8 m_flagBit0 : 1;
		} m_gameFlagBits;
	};
	u8 m_pad_12E5_12E8[0x3];        // 0x12E5
	int m_bossState;                // 0x12E8
	int m_bossSubState;             // 0x12EC
	u64 m_spawnBits[9];             // 0x12F0
	float m_moveTime;               // 0x1338
	float m_bgCollisionTime;        // 0x133C
	float m_objectCollisionTime;    // 0x1340
	float m_updateTime;             // 0x1344
	float m_hitTime;                // 0x1348
	CMapObjectInfo m_mapObjectInfo[32]; // 0x134C
	char m_savedNextScript[0x100];  // 0x15CC
	CParticleWork m_particleWork;
	int m_particleWorkNoHi;         // 0x1738
	u32 m_particleWorkNoLo;         // 0x173C
	Vec m_particleWorkPos;          // 0x1740
	float m_particleWorkPosVecBase; // 0x174C
	float m_particleWorkPosAngle;   // 0x1750
	float m_particleWorkPosPad;     // 0x1754
	Vec m_particleWorkScale;        // 0x1758
	Vec m_particleWorkTarget;       // 0x1764
	CFlatLayerResource m_layerResources[8]; // 0x1770
	u8 m_pad_17D0_17D4[4];        // 0x17D0
	int m_pathPointCount;           // 0x17D4
	float m_pathTotalDistance;      // 0x17D8
	CFlatPathPoint m_pathPoints[0x40]; // 0x17DC
	CLine<64> m_debugLines[16];
	int m_debugDrawCCCount;         // 0xCD1C
	CDebugDrawCC m_debugDrawCCEntries[16]; // 0xCD20
	CFlatData m_flatData;
	u8 m_pad_E3F4_E400[0xC];        // 0xE3F4
	int m_debugDataBuffer[0x800];   // 0xE400
	int m_debugDataIndex;           // 0x10400
	int m_initAllFinishedFlag;      // 0x10404
	int m_letterEventEnabled;       // 0x10408
	unsigned int m_workAssignIndex; // 0x1040C
	unsigned int m_partyAssignIndex; // 0x10410
	int m_cameraScriptTargetMode;   // 0x10414
	int m_saveSceneEnabled;         // 0x10418
	int m_partyTraceParticleSlot[4]; // 0x1041C
	int m_itemTraceParticleSlot;    // 0x1042C
	u8 m_pad_10430_10440[0x10];     // 0x10430
};

STATIC_ASSERT(sizeof(CFlatRuntime2) == 0x10440);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_debugFlags) == 0x129C);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_eventFlags) == 0x12A0);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_padInputDisableMask) == 0x12A8);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_centerState) == 0x12AC);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_centerMatrix) == 0x12B4);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_gameFlags) == 0x12E4);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_spawnBits) == 0x12F0);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_moveTime) == 0x1338);
STATIC_ASSERT(sizeof(CFlatRuntime2::CMapObjectInfo) == 0x14);
STATIC_ASSERT(offsetof(CFlatRuntime2::CMapObjectInfo, m_drawFlag) == 0x01);
STATIC_ASSERT(offsetof(CFlatRuntime2::CMapObjectInfo, m_x) == 0x04);
STATIC_ASSERT(offsetof(CFlatRuntime2::CMapObjectInfo, m_radius) == 0x10);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_mapObjectInfo) == 0x134C);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_savedNextScript) == 0x15CC);
STATIC_ASSERT(sizeof(CFlatRuntime2::CParticleWork) == 0x6C);
STATIC_ASSERT(offsetof(CFlatRuntime2::CParticleWork, m_hitParam) == 0x44);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_particleWork) == 0x16CC);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_particleWorkNoHi) == 0x1738);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_particleWorkPos) == 0x1740);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_particleWorkScale) == 0x1758);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_particleWorkTarget) == 0x1764);
STATIC_ASSERT(sizeof(CLine<64>) == 0xB14);
STATIC_ASSERT(offsetof(CLine<64>, pointCount) == 0x18);
STATIC_ASSERT(offsetof(CLine<64>, m_mask) == 0x2C);
STATIC_ASSERT(offsetof(CLine<64>, points) == 0x30);
STATIC_ASSERT(offsetof(CLine<64>, totalLength) == 0xB10);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_debugLines) == 0x1BDC);
STATIC_ASSERT(sizeof(CFlatRuntime2::CDebugDrawCC) == 0x20);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_debugDrawCCCount) == 0xCD1C);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_debugDrawCCEntries) == 0xCD20);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_flatData) == 0xCF20);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_debugDataBuffer) == 0xE400);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_debugDataIndex) == 0x10400);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_initAllFinishedFlag) == 0x10404);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_letterEventEnabled) == 0x10408);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_workAssignIndex) == 0x1040C);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_partyAssignIndex) == 0x10410);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_cameraScriptTargetMode) == 0x10414);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_saveSceneEnabled) == 0x10418);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_partyTraceParticleSlot) == 0x1041C);
STATIC_ASSERT(offsetof(CFlatRuntime2, m_itemTraceParticleSlot) == 0x1042C);

extern CFlatRuntime2& gCFlatRuntime2;
extern CFlatRuntime2 CFlat;

#endif // _FFCC_CFLAT_RUNTIME2_H_
