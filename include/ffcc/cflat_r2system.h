#ifndef _FFCC_CFLAT_R2SYSTEM_H_
#define _FFCC_CFLAT_R2SYSTEM_H_

#include "ffcc/cflat_runtime.h"

#include <dolphin/gx.h>

class CFlatRuntime;
class CGObject;
struct Vec;

class CFlatRuntime2
{
	void onSystemFunc(CFlatRuntime::CObject*, int, int, int&);
	CFlatRuntime::CVal* onSystemVal(CFlatRuntime::CObject*, int);
	void onSetSystemVal(int, CFlatRuntime::CStack*, int);
	int CcClass2D(int, int, Vec*, float, float, int, CGObject**);
	unsigned int isLoadLayerASyncCompleted(int);
	void loadLayerASync(int, char*);
	void drawLayer(int, char*, int, int, int, int, int, int, float, float, _GXColor*, int);
	void loadLayer(int, char*);
	void PutParticleWork();
	void ResetParticleWork(int, int);
	void SetParticleWorkPos(Vec&, float);
	void SetParticleWorkTarget(Vec&);
	void SetParticleWorkVector(float, float);
	void SetParticleWorkScale(float);
	void SetParticleWorkCol(int, int, float);
	void SetParticleWorkSpeed(float);
	void GetFreeParticleSlot();
	void EndParticleSlot(int, int);
	void initAllFinished();
	void SysControl(int, int);
	int GetSysControl(int);
	void resetSpawnBit(int);
};

#endif // _FFCC_CFLAT_R2SYSTEM_H_
