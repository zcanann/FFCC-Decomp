#ifndef _FFCC_CFLAT_RUNTIME2_H_
#define _FFCC_CFLAT_RUNTIME2_H_

#include "ffcc/cflat_runtime.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class CGObject;
class CFlatRuntime;
class CGBaseObj;
class CGQuadObj;
class CGMonObj;
class CGItemObj;
struct Vec;

extern int gCFlatRuntime2DebugDrawOverflowFrame;
extern unsigned char gCFlatRuntime2DebugDrawOverflowInit;
extern const char sCFlatRuntime2DebugDrawOverflowMsg[];
extern unsigned char CFlat[0x10440];
extern u32 CFlatFlags;
extern Mtx gFlatPosMtx;

class CFlatRuntime2
{
public:
	class CParticleWork
	{
	public:
		CParticleWork()
		{
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
			m_seNo = -1;
			m_seUnk0 = 0;
			m_seKind = 1;
			m_seUnk2 = 0;
			m_seParam = 0;
			m_seDelay = 0x1E;
			m_seFrame = -1;
			m_paramNo = 0;
			m_paramId = 0;
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
		int m_seNo;
		u8 m_seUnk0;
		u8 m_seKind;
		u8 m_seUnk2;
		u8 m_seUnk3;
		int m_seParam;
		int m_seDelay;
		int m_seFrame;
		int m_paramNo;
		short m_paramId;
		u8 m_pad4A[2];
		int m_extra[8];
	};
	
	CFlatRuntime2();
	~CFlatRuntime2();

	CMemory::CStage* getStage();
	CMemory::CStage* getDebugStage();

	void onNewObject(CFlatRuntime::CObject*);
	void onDeleteObject(CFlatRuntime::CObject*);

	unsigned int getNumFreeObject(int);
	CGObject* getFreeObject(int);
	void* intToClass(int);

	void Frame(int, int);
	int Load(char*);

	CGObject* FindGObjFirst();
	CGObject* FindGObjNext(CGObject*);

	void FindGBaseObjFirst();
	void FindGBaseObjNext(CGBaseObj*);

	CGQuadObj* FindGQuadObjFirst();
	CGQuadObj* FindGQuadObjNext(CGQuadObj*);

	CGMonObj* FindGMonObjFirst();
	CGMonObj* FindGMonObjNext(CGMonObj*);

	CGItemObj* FindGItemObjFirst();
	CGItemObj* FindGItemObjNext(CGItemObj*);

	void Destroy();
	void Calc();
	void Draw();

	void AddDebugDrawCC(Vec*, Vec*, float, int, int);
	int CcClass2D(int, int, Vec*, float, float, int, CGObject **);

	void loadLayer(int, char*);
	unsigned int isLoadLayerASyncCompleted(int);
	void loadLayerASync(int, char*);
	void drawLayer(int, char*, int, int, int, int, int, int, float, float, _GXColor*, int);

	void PutParticle(int, Vec&, float);
	void PutParticleWork();
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

	void GetFreeParticleSlot();
	void EndParticleSlot(int, int);
	void EndParticle(CCharaPcs::CHandle*);
	void DeleteParticleSlot(int, int);
	void IgnoreParticle(int, CFlatRuntime::CObject*);

	void initAllFinished();
	void reqFinished(int, CFlatRuntime::CObject*);

	void SysControl(int, int);
	int GetSysControl(int);

	void resetSpawnBit(int);
	void resetChangeScript();
	void ResetNewGame();
};

extern CFlatRuntime2& gCFlatRuntime2;

#endif // _FFCC_CFLAT_RUNTIME2_H_
