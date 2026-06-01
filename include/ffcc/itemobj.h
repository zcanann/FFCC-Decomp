#ifndef _FFCC_ITEMOBJ_H_
#define _FFCC_ITEMOBJ_H_

#include "ffcc/cflat_runtime.h"
#include "ffcc/prgobj.h"

#include <dolphin/types.h>

class CGObject;
class CGPartyObj;
class CFlatRuntime;
class CFont;
struct Vec;
class PPPIFPARAM;

class CGItemObj : public CGPrgObj
{
public:
	CGItemObj();

	struct CCFS
	{
		int m_memoryCapsuleNameIndex;
		unsigned int m_modelId;
		unsigned int m_modelParam;
		unsigned int m_pendingAnimFlags;
		char* m_pendingAnimName;
	};

	void onCreate();
	void onDestroy();
	void onFramePreCalc();
	void onFramePostCalc();
	void onChangeStat(int);
	void onCancelStat(int);
	void onFrame();
	void onFrameStat();
	static int DeleteOld(int, int, CFlatRuntime::CObject*, CFlatRuntime::CObject*);
	static unsigned int CanCreateFromScript();
	static CGPrgObj* CreateFromScript(int, int, int, CGObject*, float, CGItemObj::CCFS*);
	void carry(CGPartyObj*, int, int);
	void onChangePrg(int);
	void onFrameAlways();
	void onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*);
	void loadModel();
	void onNewFinished();
	void DrawOmoideName(CFont*);
	static void ItemJump(int, float);
	static void DeleteAllFieldItem();
	static void DispAllFieldItem(int);
	int GetCID();

	CGObject* m_owner;             // 0x550
	int m_carryFrame;              // 0x554
	int m_scriptArg;               // 0x558
	int m_particleSlot;            // 0x55C
	u16 m_createFlags;             // 0x560
	u16 unk_0x562;                 // 0x562
	CCharaPcs::CHandle* m_pendingModelHandle; // 0x564
	float m_savedBodyRadius;       // 0x568
	int m_itemJumpCountdown;       // 0x56C
	int m_memoryCapsuleNameIndex;  // 0x570
	u32 m_pendingAnimFlags;        // 0x574
	char* m_pendingAnimName;       // 0x578
};

typedef int CGItemObj_size_mismatch[(sizeof(CGItemObj) == 0x57C) ? 1 : -1];

#endif // _FFCC_ITEMOBJ_H_
