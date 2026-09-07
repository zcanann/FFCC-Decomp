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

struct SItemFlatRow {
	unsigned short m_kind;
	unsigned short m_model;
	unsigned short m_equipFlags;
	unsigned short m_value;
	unsigned short m_attribute;
	unsigned char m_pad0A[2];
	unsigned short m_stage;
	unsigned char m_pad0E[2];
	unsigned short m_fineValue;
	unsigned char m_pad12[2];
	unsigned short m_particles[3];
	unsigned char m_pad1A[6];
	unsigned short m_price;
	unsigned char m_pad22[2];
	unsigned short m_smithPrice;
	unsigned short m_smithMaterials[3];
	unsigned short m_smithMaterialCounts[3];
	unsigned char m_pad32[6];
	unsigned short m_smithResults[4];
	unsigned char m_pad40[8];
};
STATIC_ASSERT(sizeof(SItemFlatRow) == 0x48);
STATIC_ASSERT(offsetof(SItemFlatRow, m_kind) == 0x00);
STATIC_ASSERT(offsetof(SItemFlatRow, m_attribute) == 0x08);
STATIC_ASSERT(offsetof(SItemFlatRow, m_fineValue) == 0x10);
STATIC_ASSERT(offsetof(SItemFlatRow, m_stage) == 0x0C);
STATIC_ASSERT(offsetof(SItemFlatRow, m_model) == 0x02);
STATIC_ASSERT(offsetof(SItemFlatRow, m_equipFlags) == 0x04);
STATIC_ASSERT(offsetof(SItemFlatRow, m_value) == 0x06);
STATIC_ASSERT(offsetof(SItemFlatRow, m_particles) == 0x14);
STATIC_ASSERT(offsetof(SItemFlatRow, m_price) == 0x20);
STATIC_ASSERT(offsetof(SItemFlatRow, m_smithPrice) == 0x24);
STATIC_ASSERT(offsetof(SItemFlatRow, m_smithMaterials) == 0x26);
STATIC_ASSERT(offsetof(SItemFlatRow, m_smithMaterialCounts) == 0x2C);
STATIC_ASSERT(offsetof(SItemFlatRow, m_smithResults) == 0x38);

// CFlat item and particle table row.
struct SCharaItemRow {
	unsigned short m_effect;        // 0x00
	unsigned short m_kind;          // 0x02
	unsigned short m_field04;       // 0x04
	unsigned short m_basePower;     // 0x06
	unsigned short m_staType;       // 0x08
	unsigned short m_status;        // 0x0A
	unsigned short m_particleFlags; // 0x0C
	unsigned short m_actionType;  // 0x0E
	unsigned short m_scale;         // 0x10
	unsigned short m_particleBank;  // 0x12
	unsigned short m_particleEntries[4]; // 0x14
	unsigned short m_particleSpec;  // 0x1C
	unsigned char m_pad1E[0x2];     // 0x1E
	unsigned short m_attackStartFrame; // 0x20
	unsigned short m_attackEndFrame; // 0x22
	unsigned short m_fanCount;      // 0x24
	unsigned short m_speed;         // 0x26
	unsigned char m_pad28[0x2];     // 0x28
	unsigned short m_distance;      // 0x2A
	unsigned short m_flags2C;       // 0x2C
	unsigned short m_power;         // 0x2E
	unsigned short m_sourcePower;   // 0x30
	unsigned short m_flags32;       // 0x32
	unsigned char m_pad34[0x4];     // 0x34
	unsigned short m_se;            // 0x38
	unsigned short m_seFlag;        // 0x3A
	unsigned short m_se1;           // 0x3C
	unsigned short m_seFlag1;       // 0x3E
	unsigned short m_se2;           // 0x40
	unsigned short m_seSpec;        // 0x42
	unsigned char m_pad44[0x4];     // 0x44
};

STATIC_ASSERT(sizeof(SCharaItemRow) == 0x48);
STATIC_ASSERT(offsetof(SCharaItemRow, m_actionType) == 0x0E);
STATIC_ASSERT(offsetof(SCharaItemRow, m_attackStartFrame) == 0x20);
STATIC_ASSERT(offsetof(SCharaItemRow, m_attackEndFrame) == 0x22);

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
