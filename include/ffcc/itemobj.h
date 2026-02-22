#ifndef _FFCC_ITEMOBJ_H_
#define _FFCC_ITEMOBJ_H_

#include "ffcc/cflat_runtime.h"

class CGObject;
class CGPartyObj;
class CFlatRuntime;
class CFont;
struct Vec;
class PPPIFPARAM;

class CGItemObj
{
public:
	struct CCFS
	{
	};

	void onCreate();
	void onDestroy();
	void onFramePreCalc();
	void onFramePostCalc();
	void onChangeStat(int);
	void onCancelStat(int);
	void onFrame();
	void onFrameStat();
	void DeleteOld(int, int, CFlatRuntime::CObject*, CFlatRuntime::CObject*);
	unsigned int CanCreateFromScript();
	void CreateFromScript(int, int, int, CGObject*, float, CGItemObj::CCFS*);
	void safeDetach(int, float);
	void carry(CGPartyObj*, int, int);
	void onChangePrg(int);
	void statPot();
	void onFrameAlways();
	void onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*);
	void loadModel();
	void onNewFinished();
	void DrawOmoideName(CFont*);
	void ItemJump(int, float);
	void DeleteAllFieldItem();
	void DispAllFieldItem(int);
	int GetCID();
};

#endif // _FFCC_ITEMOBJ_H_
