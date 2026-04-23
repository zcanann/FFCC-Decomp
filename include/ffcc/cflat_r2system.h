#ifndef _FFCC_CFLAT_R2SYSTEM_H_
#define _FFCC_CFLAT_R2SYSTEM_H_

#include "ffcc/cflat_runtime.h"

#include <dolphin/gx.h>

class CFlatRuntime;

class CFlatRuntime2
{
	void onSystemFunc(CFlatRuntime::CObject*, int, int, int&);
	CFlatRuntime::CVal* onSystemVal(CFlatRuntime::CObject*, int);
	void onSetSystemVal(int, CFlatRuntime::CStack*, int);
	unsigned int isLoadLayerASyncCompleted(int);
	void loadLayerASync(int, char*);
	void drawLayer(int, char*, int, int, int, int, int, int, float, float, _GXColor*, int);
	void loadLayer(int, char*);
	void SysControl(int, int);
	int GetSysControl(int);
	void resetSpawnBit(int);
};

#endif // _FFCC_CFLAT_R2SYSTEM_H_
