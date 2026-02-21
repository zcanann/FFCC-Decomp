#ifndef _FFCC_CFLAT_RUNTIME2_H_
#define _FFCC_CFLAT_RUNTIME2_H_

#include "ffcc/cflat_runtime.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara.h"

#include <dolphin/gx.h>

class CGObject;
class CFlatRuntime;
class CGBaseObj;
class CGQuadObj;
class CGMonObj;
class CGItemObj;
struct Vec;

class CFlatRuntime2
{
	class CParticleWork
	{
		CParticleWork();
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
	void Load(char*);

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
	void CcClass2D(int, int, Vec*, float, float, int, CGObject **);

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

#endif // _FFCC_CFLAT_RUNTIME2_H_
