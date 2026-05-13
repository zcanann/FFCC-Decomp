#include "ffcc/itemobj.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/math.h"
#include "ffcc/partMng.h"
#include "ffcc/partyobj.h"
#include "ffcc/prgobj.h"
#include "ffcc/game.h"
#include "ffcc/vector.h"

#include <math.h>
#include <string.h>
#include "ffcc/fontman.h"

extern "C" void onCreate__8CGPrgObjFv(void*);
extern "C" void onDestroy__8CGPrgObjFv(void*);
extern "C" int GetFreeParticleSlot__13CFlatRuntime2Fv(void*);
extern "C" void DeleteParticleSlot__13CFlatRuntime2Fii(void*, int, int);
extern "C" void __dt__Q29CCharaPcs7CHandleFv(void*, int);
extern "C" void Attach__8CGObjectFP8CGObjectPcP3Vec(void*, void*, char*, Vec*);
extern "C" void Detach__8CGObjectFv(void*);
extern "C" void changeStat__8CGPrgObjFiii(void*, int, int, int);
extern "C" float CalcSafePos__8CGObjectFiP8CGObjectP3Vec(void*, int, void*, Vec*);
extern "C" void moveVectorHRot__8CGObjectFfffi(void*, float, float, float, int);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, int, int, int, int, void*, void*);
extern "C" void LoadModel__8CGObjectFiUlUli(void*, int, unsigned long, unsigned long, int);
extern "C" void LoadAnim__8CGObjectFPciiiUl(void*, char*, int, int, int, unsigned long);
extern "C" void SetAnimSlot__8CGObjectFii(void*, int, int);
extern "C" void PlayAnim__8CGObjectFiiiiiPSc(void*, int, int, int, int, int, signed char*);
extern "C" void DispCharaParts__8CGObjectFi(void*, int);
extern "C" void putParticle__8CGPrgObjFiiP8CGObjectfi(void*, int, int, void*, float, int);
extern "C" void putParticleTrace__8CGPrgObjFiiP8CGObjectfi(void*, int, int, void*, float, int);
extern "C" float RandF__5CMathFf(float, CMath*);
extern "C" unsigned int getNumFreeObject__13CFlatRuntime2Fi(void*, int);
extern "C" void* FindGItemObjFirst__13CFlatRuntime2Fv(void*);
extern "C" void* FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(void*, void*);
extern "C" void deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void Printf__7CSystemFPce(void*, char*, ...);
extern "C" void EndParticleSlot__13CFlatRuntime2Fii(void*, int, int);
extern "C" void ResetParticleWork__13CFlatRuntime2Fii(void*, int, int);
extern "C" void SetParticleWorkPos__13CFlatRuntime2FR3Vecf(void*, Vec&, float);
extern "C" void SetParticleWorkCol__13CFlatRuntime2Fiif(void*, int, int, float);
extern "C" void SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(void*, int, void*);
extern "C" void PutParticleWork__13CFlatRuntime2Fv(void*);
extern "C" void addSubStat__8CGPrgObjFv(void*);
extern "C" void IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(void*, int, void*);
extern "C" int intToClass__13CFlatRuntime2Fi(void*, int);
extern "C" float RandFPM__5CMathFf(float, CMath*);
extern "C" void SetPosBG__8CGObjectFP3Veci(void*, Vec*, int);
extern "C" void MoveVector__8CGObjectFP3Vecfiiii(void*, Vec*, float, int, int, int, int);
extern "C" void EndParticle__13CFlatRuntime2FPQ29CCharaPcs7CHandle(void*, void*);
extern "C" void* __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
extern "C" void* __ct__Q29CCharaPcs7CHandleFv(void*);
extern "C" void Add__Q29CCharaPcs7CHandleFv(void*);
extern "C" void LoadModelASync__Q29CCharaPcs7CHandleFiUlUl(void*, int, unsigned long, unsigned long);
extern "C" int IsLoadModelASyncCompleted__Q29CCharaPcs7CHandleFv(void*);
extern "C" void SetDamageCol__8CGObjectFiPcffP3Vec(void*, int, char*, float, float, Vec*);
extern "C" void onFrame__8CGPrgObjFv(void*);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, int, int, int, int);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
extern "C" void putParticle__8CGPrgObjFiiP3Vecfi(void*, int, int, Vec*, float, int);
extern "C" void playSe3D__8CGPrgObjFiiiiP3Vec(void*, int, int, int, int, Vec*);
extern "C" void pppSetLocSlot__8CPartMngFiP3Vec(void*, int, Vec*);
extern float FLOAT_80331b20;
extern float FLOAT_80331b1c;
extern float FLOAT_80331b24;
extern float FLOAT_80331b28;
extern float FLOAT_80331b2c;
extern const float FLOAT_80331b18;
extern float FLOAT_80331b30;
extern float FLOAT_80331b34;
extern float FLOAT_80331b38;
extern float FLOAT_80331b3c;
extern float FLOAT_80331b40;
extern float FLOAT_80331b4c;
extern float FLOAT_80331b50;
extern float FLOAT_80331b54;
extern float FLOAT_80331b58;
extern float FLOAT_80331b8c;
extern float FLOAT_80331b90;
extern float FLOAT_80331b94;
extern float FLOAT_80331b98;
extern float FLOAT_80331bb8;
extern float FLOAT_80331bb0;
extern float FLOAT_80331b9c;
extern float FLOAT_80331bbc;
extern float FLOAT_80331b78;
extern float FLOAT_80331ba8;
extern float FLOAT_80331bac;
extern float FLOAT_80331bb4;
extern float FLOAT_80331bc0;
extern float FLOAT_80331bc4;
extern float FLOAT_80331b68;
extern double DOUBLE_80331ba0;
extern double DOUBLE_80331b60;
extern double DOUBLE_80331b70;
u32 gItemObjCreateFlags;
extern char SoundBuffer[];
extern char SoundBuffer_1260_[];
extern const char DAT_80331b7c[];
extern const char DAT_80331b84[];
extern char DAT_80331bc8[];
static const char DAT_801dcec0[] = "num free item = %d\n";
static const char DAT_801dced4[] = {
    (char)0x8F, (char)0xC1, (char)0x82, (char)0xB9, (char)0x82, (char)0xE9, (char)0x83, 0x49,
    (char)0x83, 0x75, (char)0x83, 0x57, (char)0x83, 0x46, (char)0x83, 0x4E,
    (char)0x83, 0x67, (char)0x82, (char)0xAA, (char)0x82, (char)0xA0, (char)0x82, (char)0xE8,
    (char)0x82, (char)0xDC, (char)0x82, (char)0xB9, (char)0x82, (char)0xF1, (char)0x81, 0x42,
    (char)0x0A, (char)0x00, (char)0x00, (char)0x00,
};
static const char DAT_801dcef8[] = "num delete item = %d\n";
static const char DAT_801dcf10[] = {
    (char)0x83, 0x41, (char)0x83, 0x43, (char)0x83, 0x65, (char)0x83, (char)0x80,
    (char)0x82, (char)0xF0, (char)0x90, (char)0xB6, (char)0x90, (char)0xAC, (char)0x82, (char)0xC5,
    (char)0x82, (char)0xAB, (char)0x82, (char)0xDC, (char)0x82, (char)0xB9, (char)0x82, (char)0xF1,
    (char)0x82, (char)0xC5, (char)0x82, (char)0xB5, (char)0x82, (char)0xBD, (char)0x81, 0x42,
    (char)0x0A, (char)0x00, (char)0x00, (char)0x00,
};
static const char DAT_801dcf80[] = {
    (char)0x8E, (char)0x9E, (char)0x8A, (char)0xD4, (char)0x82, (char)0xA9, (char)0x8B, (char)0x97,
    (char)0x97, (char)0xA3, (char)0x82, (char)0xC5, (char)0x83, 0x41, (char)0x83, 0x43,
    (char)0x83, 0x65, (char)0x83, (char)0x80, (char)0x82, (char)0xAA, (char)0x8F, (char)0xC1,
    (char)0x82, (char)0xA6, (char)0x82, (char)0xDC, (char)0x82, (char)0xB7, (char)0x81, 0x42,
    (char)0x0A, (char)0x00, (char)0x00, (char)0x00,
};
static const char DAT_801dcf34[] = {
    (char)0x8E, 0x76, (char)0x82, (char)0xA2, (char)0x8F, 0x6F, (char)0x83, 0x4A,
    (char)0x83, 0x76, (char)0x83, 0x5A, (char)0x83, (char)0x8B, (char)0x8D, (char)0xEC,
    (char)0x90, (char)0xAC, 0x20, 0x69, 0x64, 0x78, 0x50, 0x61,
    0x72, 0x74, 0x79, 0x20, 0x3D, 0x20, 0x25, 0x64,
    (char)0x0A, (char)0x00, (char)0x00, (char)0x00,
};
static const char DAT_801dcf58[] = "itemobj.cpp";
static const char DAT_801dcf64[] = {
    (char)0x8E, 0x76, (char)0x82, (char)0xA2, (char)0x8F, 0x6F, (char)0x83, 0x4A,
    (char)0x83, 0x76, (char)0x83, 0x5A, (char)0x83, (char)0x8B, (char)0x94, (char)0xF1,
    (char)0x93, (char)0xAF, (char)0x8A, (char)0xFA, (char)0x8A, 0x4A, (char)0x8E, 0x6E,
    (char)0x0A, (char)0x00, (char)0x00, (char)0x00,
};
static const char DAT_801dd010[] = {
    (char)0x8E, 0x76, (char)0x82, (char)0xA2, (char)0x8F, 0x6F, (char)0x83, 0x4A,
    (char)0x83, 0x76, (char)0x83, 0x5A, (char)0x83, (char)0x8B, (char)0x94, (char)0xF1,
    (char)0x93, (char)0xAF, (char)0x8A, (char)0xFA, (char)0x8F, 0x49, (char)0x97, (char)0xB9,
    (char)0x0A, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
    0x43, 0x47, 0x50, 0x72, 0x67, 0x4F, 0x62, 0x6A,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, 0x43, 0x46, 0x6C, 0x61,
    0x74, 0x52, 0x75, 0x6E, 0x74, 0x69, 0x6D, 0x65,
    0x3A, 0x3A, 0x43, 0x4F, 0x62, 0x6A, 0x65, 0x63,
    0x74, (char)0x00, (char)0x00, (char)0x00,
};
static const char DAT_801dcfa4[] = {
    (char)0x8E, 0x76, (char)0x82, (char)0xA2, (char)0x8F, 0x6F, (char)0x83, 0x4A,
    (char)0x83, 0x76, (char)0x83, 0x5A, (char)0x83, (char)0x8B, (char)0x8E, (char)0xB8,
    (char)0x94, 0x73, 0x20, 0x69, 0x64, 0x78, 0x50, 0x61,
    0x72, 0x74, 0x79, 0x20, 0x3D, 0x20, 0x25, 0x64,
    (char)0x0A, (char)0x00, (char)0x00, (char)0x00,
};
static const char DAT_801dcfc8[] = {
    (char)0x8E, 0x76, (char)0x82, (char)0xA2, (char)0x8F, 0x6F, (char)0x83, 0x4A,
    (char)0x83, 0x76, (char)0x83, 0x5A, (char)0x83, (char)0x8B, (char)0x90, (char)0xAC,
    (char)0x8C, (char)0xF7, 0x20, 0x69, 0x64, 0x78, 0x50, 0x61,
    0x72, 0x74, 0x79, 0x20, 0x3D, 0x20, 0x25, 0x64,
    (char)0x0A, (char)0x00, (char)0x00, (char)0x00,
};
static const char DAT_801dcfec[] = {
    (char)0x8E, 0x76, (char)0x82, (char)0xA2, (char)0x8F, 0x6F, (char)0x96, (char)0x82,
    (char)0x90, (char)0xCE, (char)0x82, (char)0xF0, (char)0x90, (char)0xB6, (char)0x90, (char)0xAC,
    (char)0x82, (char)0xC5, (char)0x82, (char)0xAB, (char)0x82, (char)0xDC, (char)0x82, (char)0xB9,
    (char)0x82, (char)0xF1, (char)0x82, (char)0xC5, (char)0x82, (char)0xB5, (char)0x82, (char)0xBD,
    (char)0x81, 0x42, (char)0x0A, (char)0x00,
};
static const char s_f051_root_801dceb4[] = "f051_root";
static const char s_stand_80331B44[] = "stand";
extern "C" char m_aiWork__8CGMonObj[];

struct ItemObjFlatTableEntry {
	int count;
	const char** index;
	char* buffer;
};

struct ItemObjFlatData {
	char pad[0x6c];
	ItemObjFlatTableEntry table[8];
};

struct CMapCylinderRaw {
	Vec m_bottom;
	Vec m_top;
	Vec m_axis;
	float m_radius;
	Vec m_boundsMin;
	Vec m_boundsMax;
};

/*
 * --INFO--
 * PAL Address: 0x80124b80
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPrgObj::getReplaceStat(int state)
{
	return state;
}

/*
 * --INFO--
 * PAL Address: 0x80126f94
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onCreate()
{
	onCreate__8CGPrgObjFv(this);
	m_flagBits.bits.unk0 = 0;
	m_owner = 0;
	m_scriptArg = 0;
	m_createFlags = 0;
	unk_0x562 = 0;
	m_pendingModelHandle = 0;
	m_itemJumpCountdown = 0;
	memset(&m_memoryCapsuleNameIndex, 0, 0xc);
	m_particleSlot = GetFreeParticleSlot__13CFlatRuntime2Fv(CFlat);
}

/*
 * --INFO--
 * PAL Address: 0x80126f3c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onDestroy()
{
	unsigned char* self = (unsigned char*)this;
	void* handle = *(void**)(self + 0x564);

	if (handle != 0) {
		__dt__Q29CCharaPcs7CHandleFv(handle, 1);
	}

	DeleteParticleSlot__13CFlatRuntime2Fii(CFlat, *(int*)(self + 0x55c), 0);
	onDestroy__8CGPrgObjFv(self);
}

/*
 * --INFO--
 * PAL Address: 0x80126f38
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onFramePreCalc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80126f08
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onFramePostCalc()
{
	unsigned char* self = (unsigned char*)this;

	if (static_cast<signed char>(
	        static_cast<int>((static_cast<unsigned int>(self[0x50]) << 28) & 0xC0000000) >> 31) != 0 &&
	    *(void**)(self + 0x550) == 0) {
		*(int*)(self + 0x94) = *(int*)(self + 0x94) - 1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80126ee0
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onChangeStat(int state)
{
	unsigned char* self = (unsigned char*)this;

	if (state < 0x28 && state >= 0x26) {
		*(unsigned int*)(self + 0x1c0) = *(unsigned int*)(self + 0x1c0) & 0xfff7fffe;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80126eb4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onCancelStat(int)
{
	unsigned char* self = (unsigned char*)this;

	if (*(int*)(self + 0x520) == 0x1b) {
		*(unsigned int*)(self + 0x1c0) = *(unsigned int*)(self + 0x1c0) | 2;
		*(float*)(self + 0x17c) = FLOAT_80331b18;
		*(float*)(self + 0x178) = FLOAT_80331b18;
		*(float*)(self + 0x174) = FLOAT_80331b18;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80126d08
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onFrame()
{
	unsigned char* self = (unsigned char*)this;
	void* handle = m_pendingModelHandle;

	if (handle != 0 && IsLoadModelASyncCompleted__Q29CCharaPcs7CHandleFv(handle) != 0) {
		if ((unsigned int)System.m_execParam >= 3U) {
			Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dd010));
		}

		m_charaModelHandle = reinterpret_cast<CCharaPcs::CHandle*>(m_pendingModelHandle);
		m_pendingModelHandle = 0;

		if (m_worldParamA == 0xCB) {
			LoadAnim__8CGObjectFPciiiUl(this, m_pendingAnimName, 0, 0, 2, m_pendingAnimFlags);
			SetAnimSlot__8CGObjectFii(this, 0, 0);
			PlayAnim__8CGObjectFiiiiiPSc(this, 0, 1, 0, -1, -1, 0);

			CGObject* owner = m_owner;
			int ownerScriptSlot = *(int*)(*(int*)((unsigned char*)owner + 0x58) + 0x3B4);
			int soundEntry = *(int*)(*(int*)(*(int*)SoundBuffer_1260_ + 0xF8) + 0x178);
			if (soundEntry != 0) {
				soundEntry = *(int*)(soundEntry + 0x14);
			} else {
				soundEntry = -1;
			}

			unsigned char* itemTable = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]);
			float particleValue = static_cast<float>(*reinterpret_cast<unsigned short*>(itemTable + m_worldParamB * 0x48 + 0x10));
			float particleScale = FLOAT_80331b50 * (float)particleValue + FLOAT_80331b4c;
			putParticle__8CGPrgObjFiiP8CGObjectfi(
			    this, (soundEntry << 8) | ownerScriptSlot, m_particleSlot, this, particleScale, 0x12909);

			CVector zero(FLOAT_80331b20, FLOAT_80331b20, FLOAT_80331b20);
			SetDamageCol__8CGObjectFiPcffP3Vec(
			    this, 0, DAT_80331bc8, FLOAT_80331bb8, FLOAT_80331bb8, reinterpret_cast<Vec*>(&zero));
			*reinterpret_cast<unsigned int*>(&m_damageColliders[1].m_localPosition.x) = 8;
			addSubStat__8CGPrgObjFv(this);
		}
	}

	onFrame__8CGPrgObjFv(this);
}

/*
 * --INFO--
 * PAL Address: 0x80125fb0
 * PAL Size: 3416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onFrameStat()
{
	unsigned char* self = (unsigned char*)this;
	CGPrgObj* prgObj = (CGPrgObj*)this;
	int stateId = *(int*)(self + 0x520);
	float zero = FLOAT_80331b20;

	switch (stateId) {
	case 0: {
		int hasOwner = *(int*)(self + 0x550) != 0;
		int isActive = (self[0x50] & 8) != 0;

		if (!hasOwner && isActive) {
			double distance = (double)FLOAT_80331b20;

			if (Game.unk_flat3_0xc7d0 == 0) {
				if (*(int*)(CFlat + 0x4780) == 1) {
					Vec partyCenter;

					partyCenter.x = (Game.m_partyMinX + Game.m_partyMaxX) * FLOAT_80331b3c;
					partyCenter.y = (Game.m_partyMinY + Game.m_partyMaxY) * FLOAT_80331b3c;
					partyCenter.z = (Game.m_partyMinZ + Game.m_partyMaxZ) * FLOAT_80331b3c;
					distance = (double)PSVECDistance((Vec*)(self + 0x15c), &partyCenter);
				}
			} else {
				distance = (double)PSVECDistance((Vec*)(self + 0x15c), (Vec*)(Game.unk_flat3_0xc7d0 + 0x15c));
			}

			if (*(int*)(self + 0x94) < 1 || DOUBLE_80331ba0 < distance) {
				Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dcf80));
				*(float*)(self + 0x4b8) = FLOAT_80331b54;
				*(float*)(self + 0x4b4) = zero;
				*(unsigned int*)(self + 0x1c0) = 1;
				EndParticle__13CFlatRuntime2FPQ29CCharaPcs7CHandle(CFlat, *(void**)(self + 0xf8));
				changeStat__8CGPrgObjFiii(this, 9, 0, 0);
			}
		}
		break;
	}
	case 9:
		if (*(int*)(self + 0x528) == 8) {
			self[0x38] = (self[0x38] & 0x7f) | 0x80;
		}
		break;
	case 0xB:
		if (*(int*)(self + 0x528) == *(int*)(self + 0x554)) {
			CVector attachOffset(FLOAT_80331b20, FLOAT_80331b20, FLOAT_80331b20);
			bool useBossAttachName = false;

			if (Game.m_gameWork.m_menuStageMode != 0) {
				CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
				bool condA = false;
				bool condB = false;
				bool condC = false;

				if (Game.m_gameWork.m_menuStageMode != 0 &&
				    Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
					condC = true;
				}
				if (condC) {
					unsigned int cid = static_cast<unsigned short>(carryObj->GetCID());
					unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
					if (((stageCarry >> 5) & 0xFF) != 0) {
						condB = true;
					}
				}
				if (condB &&
				    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(carryObj->m_scriptHandle) + 0x3B4) != 0) {
					condA = true;
				}
				if (condA) {
					useBossAttachName = true;
				}
			}

			const char* attachName = DAT_80331b84;
			if (useBossAttachName) {
				attachName = DAT_80331b7c;
			}
			Attach__8CGObjectFP8CGObjectPcP3Vec(this, *(void**)(self + 0x550), const_cast<char*>(attachName),
			                                    reinterpret_cast<Vec*>(&attachOffset));
			changeStat__8CGPrgObjFiii(this, 0, 0, 0);
			*(float*)(self + 0x144) = FLOAT_80331b20;
		}
		break;
	case 0xC:
	case 0xD:
		if (*(int*)(self + 0x528) == *(int*)(self + 0x554)) {
			CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
			Vec safePos;
			float launchSpeed = FLOAT_80331b40;

			if (*(int*)(self + 0x520) == 0xC) {
				bool useMenuLaunchSpeed = false;

				if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
					unsigned int carryCid = static_cast<unsigned short>(carryObj->GetCID());
					if ((carryCid & 0x6D) == 0x6D &&
					    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(carryObj->m_scriptHandle) + 0x3B4) != 0) {
						useMenuLaunchSpeed = true;
					}
				}

				if (useMenuLaunchSpeed) {
					launchSpeed = FLOAT_80331b18;
				} else if (*(int*)(CFlat + 0x4780) == 1) {
					unsigned int carryCid = static_cast<unsigned short>(carryObj->GetCID());
					if ((carryCid & 0x6D) == 0x6D &&
					    1 < *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(carryObj->m_scriptHandle) + 0x3E0)) {
						launchSpeed = FLOAT_80331b18;
					} else {
						launchSpeed = FLOAT_80331ba8;
					}
				} else {
					launchSpeed = FLOAT_80331b90;
				}
			}

			float safeDist = CalcSafePos__8CGObjectFiP8CGObjectP3Vec(this, 0x41, carryObj, &safePos);

			if (FLOAT_80331b20 < safeDist) {
				moveVectorHRot__8CGObjectFfffi(
				    carryObj, FLOAT_80331b8c + *(float*)((unsigned char*)carryObj + 0x1A8), FLOAT_80331b20,
				    safeDist / FLOAT_80331b90, 3);
			}

			Detach__8CGObjectFv(this);
			*(Vec*)(self + 0x15C) = safePos;

			float ownerRotY = *(float*)((unsigned char*)carryObj + 0x1B4);
			CVector moveVec((float)sin((double)ownerRotY), FLOAT_80331b54, (float)cos((double)ownerRotY));
			MoveVector__8CGObjectFP3Vecfiiii(this, reinterpret_cast<Vec*>(&moveVec), launchSpeed, 1, 0, 1, 0);

			*(int*)(self + 0x550) = 0;
			*(int*)(self + 0x56C) = 8;
			*(float*)(self + 0x144) = FLOAT_80331b20;
		}

		if (*(int*)(self + 0x554) <= *(int*)(self + 0x528)) {
			int worldParamA = *(int*)(self + 0x500);
			bool isActive = (self[0x50] & 0x80) != 0;

			if ((worldParamA == 1 || worldParamA == 2) && isActive) {
				changeStat__8CGPrgObjFiii(this, 0x1F, 0, 0);
			} else if (isActive) {
				changeStat__8CGPrgObjFiii(this, 0, 0, 0);
			}
		}
		break;
	case 0xE:
		if (*(int*)(self + 0x528) == 0) {
			prgObj->m_bgColMask = 0;
			prgObj->m_weaponNodeFlags &= 0xFFEF;
			prgObj->m_groundHitOffset.z = zero;
			prgObj->m_groundHitOffset.y = zero;
			prgObj->m_groundHitOffset.x = zero;
		} else if (*(int*)(self + 0x528) == 4) {
			prgObj->m_bgDownDist = FLOAT_80331b68;
			prgObj->m_stepSlopeLimit = zero;
			EndParticle__13CFlatRuntime2FPQ29CCharaPcs7CHandle(CFlat, prgObj->m_charaModelHandle);
		} else if (*(int*)(self + 0x528) == 0xC) {
			self[0x38] = (self[0x38] & 0x7F) | 0x80;
		}

		if (7 < *(int*)(self + 0x528)) {
			CGObject* carryObj = *(CGObject**)(self + 0x550);

			prgObj->m_rotTargetY = prgObj->m_rotTargetY + FLOAT_80331b54;
			prgObj->m_worldPosition.x =
			    FLOAT_80331b54 * (carryObj->m_worldPosition.x - prgObj->m_worldPosition.x) + prgObj->m_worldPosition.x;
			prgObj->m_worldPosition.y =
			    FLOAT_80331b54 * (FLOAT_80331b3c * carryObj->unk_0x188 + carryObj->m_worldPosition.y - prgObj->m_worldPosition.y) +
			    prgObj->m_worldPosition.y;
			prgObj->m_worldPosition.z =
			    FLOAT_80331b54 * (carryObj->m_worldPosition.z - prgObj->m_worldPosition.z) + prgObj->m_worldPosition.z;
			prgObj->m_rotationX = prgObj->m_rotationX * FLOAT_80331bac;
			prgObj->m_rotationY = prgObj->m_rotationY * FLOAT_80331bac;
			prgObj->m_rotationZ = prgObj->m_rotationZ * FLOAT_80331bac;
		}
		break;
	case 0x1b:
		if (*(int*)(self + 0x528) < 9) {
			float wobble = (float)sin((double)(FLOAT_80331b9c * (float)(*(int*)(self + 0x528)) * FLOAT_80331b68));

			*(float*)(self + 0x17c) = wobble;
			*(float*)(self + 0x178) = wobble;
			*(float*)(self + 0x174) = wobble;

			if (*(int*)(self + 0x528) == 8) {
				changeStat__8CGPrgObjFiii(this, 0, 0, 0);
			}
		}
		break;
	case 0x1F:
		pppSetLocSlot__8CPartMngFiP3Vec(&PartMng, *(int*)(self + 0x55C), &prgObj->m_worldPosition);

		if (*(int*)(self + 0x52C) == 1) {
			if (*(int*)(self + 0x530) == 0x7D) {
				EndParticleSlot__13CFlatRuntime2Fii(CFlat, *(int*)(self + 0x55C), 0);
			}
		} else if (*(int*)(self + 0x52C) == 0 && *(int*)(self + 0x530) == 0) {
			int particleNoA;
			int particleNoB;

			if (*(int*)(self + 0x500) == 2) {
				particleNoA = 0x19;
				particleNoB = 0x1E;
			} else {
				particleNoA = 0x18;
				particleNoB = 0x1D;
			}

			putParticle__8CGPrgObjFiiP3Vecfi(this, particleNoA | 0x100, 0, &prgObj->m_worldPosition, FLOAT_80331b18, 0);
			putParticle__8CGPrgObjFiiP3Vecfi(
			    this, particleNoB | 0x100, *(int*)(self + 0x55C), &prgObj->m_worldPosition, FLOAT_80331b18, 0);
			playSe3D__8CGPrgObjFiiiiP3Vec(this, 0x1A, 0x32, 0x96, 0, 0);
			prgObj->m_displayFlags &= ~1;
			prgObj->m_bgColMask &= 0xFFFFFFF1;
			prgObj->m_moveOffset.z = zero;
			prgObj->m_moveOffset.x = zero;
			prgObj->m_bgColMask |= 0x80000;

			CVector damageOffset(zero, zero, zero);
			SetDamageCol__8CGObjectFiPcffP3Vec(this, 0, const_cast<char*>(s_f051_root_801dceb4), FLOAT_80331b78, FLOAT_80331b78,
			                                  reinterpret_cast<Vec*>(&damageOffset));
			prgObj->m_damageColliders[1].m_localPosition.x = 9.0f;
		}
		break;
	case 0x23:
		if (*(int*)(self + 0x52C) == 1) {
			CCharaPcs::CHandle* handle = prgObj->m_charaModelHandle;
			if (handle != 0 && handle->m_model != 0) {
				unsigned char* model = reinterpret_cast<unsigned char*>(handle->m_model);
				model[0x10C] = (model[0x10C] & 0x7F) | 0x80;
			}

			if (*(int*)(self + 0x530) < 9) {
				float wobble = (float)sin((double)(FLOAT_80331b9c * (float)(*(int*)(self + 0x530)) * FLOAT_80331b68));

				prgObj->m_rotationZ = wobble;
				prgObj->m_rotationY = wobble;
				prgObj->m_rotationX = wobble;

				if (*(int*)(self + 0x530) == 8) {
					prgObj->m_bgColMask |= 0x80000;
					changeStat__8CGPrgObjFiii(this, 0x24, 0, 0);
				}
			}
		}
		break;
	case 0x24:
		prgObj->m_moveOffset.x = FLOAT_80331bb0;
		prgObj->m_moveOffset.y = zero;
		prgObj->m_moveOffset.z = FLOAT_80331bb0;
		prgObj->m_rotTargetY = prgObj->m_rotTargetY + FLOAT_80331b50;

		if (prgObj->m_worldPosition.y < FLOAT_80331b1c) {
			prgObj->m_groundHitOffset.y += FLOAT_80331bb4 * prgObj->m_moveTimer;
		} else if (FLOAT_80331bb8 < prgObj->m_worldPosition.y) {
			prgObj->m_groundHitOffset.y = -(FLOAT_80331bb4 * prgObj->m_moveTimer - prgObj->m_groundHitOffset.y);
		}

		{
			float timer = prgObj->m_moveTimer;
			float minClamp = FLOAT_80331ba8 * -timer;
			float maxClamp = FLOAT_80331ba8 * timer;
			float current = prgObj->m_groundHitOffset.y;

			if (minClamp <= current && current <= maxClamp) {
				prgObj->m_groundHitOffset.y = current;
			} else if (current < minClamp) {
				prgObj->m_groundHitOffset.y = minClamp;
			} else {
				prgObj->m_groundHitOffset.y = maxClamp;
			}
		}

		prgObj->m_groundHitOffset.x =
		    -FLOAT_80331b50 * (prgObj->m_worldPosition.x - *(float*)(*(unsigned char**)(self + 0x550) + 0x15C));
		prgObj->m_groundHitOffset.z =
		    -FLOAT_80331b50 * (prgObj->m_worldPosition.z - *(float*)(*(unsigned char**)(self + 0x550) + 0x164));
		break;
	case 0x25: {
		CVector monTarget(*reinterpret_cast<Vec*>(m_aiWork__8CGMonObj + 4));
		CVector worldPos(prgObj->m_worldPosition);
		CVector delta;

		prgObj->m_moveOffset.y = FLOAT_80331bb0;
		prgObj->m_rotTargetY = prgObj->m_rotTargetY + FLOAT_80331bbc;
		PSVECSubtract(reinterpret_cast<Vec*>(&monTarget), reinterpret_cast<Vec*>(&worldPos), reinterpret_cast<Vec*>(&delta));
		monTarget.x = delta.x;
		monTarget.y = delta.y;
		monTarget.z = delta.z;

		float distance = PSVECMag(reinterpret_cast<Vec*>(&monTarget));
		if (distance < FLOAT_80331bb8) {
			changeStat__8CGPrgObjFiii(this, 0x27, 0, 0);
		} else if (distance <= zero) {
			prgObj->m_groundHitOffset.z = zero;
			prgObj->m_groundHitOffset.y = zero;
			prgObj->m_groundHitOffset.x = zero;
		} else {
			float moveScale = FLOAT_80331bc0 * prgObj->m_moveTimer;

			prgObj->m_groundHitOffset.x += FLOAT_80331bc4 * monTarget.x * moveScale;
			prgObj->m_groundHitOffset.y += FLOAT_80331bc4 * monTarget.y * moveScale;
			prgObj->m_groundHitOffset.z += FLOAT_80331bc4 * monTarget.z * moveScale;
		}
		break;
	}
	case 0x26:
	case 0x27: {
		int ownerSlot;
		int pdtNo = -1;
		int particleNo = (stateId == 0x26) ? 4 : 0x13;

		prgObj->m_groundHitOffset.z = zero;
		prgObj->m_groundHitOffset.y = zero;
		prgObj->m_groundHitOffset.x = zero;

		if (*(int*)(self + 0x528) == 0) {
			prgObj->m_stepSlopeLimit = zero;
			EndParticleSlot__13CFlatRuntime2Fii(CFlat, *(int*)(self + 0x55C), 0);

			int soundEntry = *(int*)(*(int*)(*(int*)SoundBuffer_1260_ + 0xF8) + 0x178);
			if (soundEntry != 0) {
				pdtNo = *(int*)(soundEntry + 0x14);
			}

			float particleScale =
			    FLOAT_80331b50 * (float)*(unsigned short*)(Game.unkCFlatData0[2] + prgObj->m_worldParamB * 0x48 + 0x10) +
			    FLOAT_80331b4c;
			putParticle__8CGPrgObjFiiP8CGObjectfi(this, (pdtNo << 8) | particleNo, *(int*)(self + 0x55C), this,
			                                      particleScale, (stateId == 0x26) ? 0x12908 : 0x12903);
		} else if (*(int*)(self + 0x528) == 0xD) {
			ownerSlot = *(int*)(*(unsigned char**)(*(unsigned char**)(self + 0x550) + 0x58) + 0x3B4);

			if ((unsigned int)System.m_execParam > 2U) {
				Printf__7CSystemFPce(
				    &System, const_cast<char*>((stateId == 0x26) ? DAT_801dcfc8 : DAT_801dcfa4), ownerSlot);
			}

			*(int*)(SoundBuffer + ownerSlot * 4 + 0x4F4) = 0;
			if (stateId == 0x26) {
				CGPrgObj* newItem = CreateFromScript(0, 0, 0x103, 0, FLOAT_80331b20, 0);
				if (newItem == 0) {
					if ((unsigned int)System.m_execParam > 1U) {
						Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dcfec));
					}
				} else {
					unsigned char* newItemSelf = reinterpret_cast<unsigned char*>(newItem);

					*reinterpret_cast<float*>(newItemSelf + 0x168) = prgObj->m_worldPosition.x;
					*reinterpret_cast<float*>(newItemSelf + 0x16C) = prgObj->m_worldPosition.y;
					*reinterpret_cast<float*>(newItemSelf + 0x170) = prgObj->m_worldPosition.z;
					newItem->m_worldPosition.x = *reinterpret_cast<float*>(newItemSelf + 0x168);
					newItem->m_worldPosition.y = *reinterpret_cast<float*>(newItemSelf + 0x16C);
					newItem->m_worldPosition.z = *reinterpret_cast<float*>(newItemSelf + 0x170);

					CFlatRuntime::CStack stack;
					stack.m_word = 1;
					SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
					    &CFlat, *(int*)(self + 0x550), 2, 0x16, 1, &stack, 0);
				}
			} else {
				CFlatRuntime::CStack stack;
				stack.m_word = 0;
				SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
				    &CFlat, *(int*)(self + 0x550), 2, 0x16, 1, &stack, 0);
			}

			self[0x38] = (self[0x38] & 0x7F) | 0x80;
		}
		break;
	}
	default:
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80125eac
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGItemObj::DeleteOld(int deleteMask, int maxDeleteCount, CFlatRuntime::CObject*, CFlatRuntime::CObject*)
{
	int deletedCount = 0;

	while (deletedCount < maxDeleteCount) {
		unsigned char* bestItemObj = 0;
		int bestScriptObjectPos = 0x00989680;

		for (unsigned char* itemObj = (unsigned char*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat);
			 itemObj != 0;
			 itemObj = (unsigned char*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj)) {
			if (*(void**)(itemObj + 0x550) == 0 &&
				static_cast<signed char>(
				    static_cast<int>((static_cast<unsigned int>(itemObj[0x50]) << 28) & 0xC0000000) >> 31) != 0 &&
				(((int)(char)itemObj[0x53] & deleteMask) != 0) && *(int*)(itemObj + 0x94) < bestScriptObjectPos) {
				bestScriptObjectPos = *(int*)(itemObj + 0x94);
				bestItemObj = itemObj;
			}
		}

		if (bestItemObj != 0) {
			deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject(CFlat, bestItemObj);
		} else {
			if ((unsigned int)System.m_execParam >= 3) {
				Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dced4));
			}
			break;
		}

		deletedCount++;
	}

	return deletedCount;
}

/*
 * --INFO--
 * PAL Address: 0x80125e74
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CGItemObj::CanCreateFromScript()
{
	unsigned int numFreeObjects = getNumFreeObject__13CFlatRuntime2Fi(CFlat, 5);

	return (-numFreeObjects & ~numFreeObjects) >> 31;
}

/*
 * --INFO--
 * PAL Address: 0x801259e4
 * PAL Size: 1168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGPrgObj* CGItemObj::CreateFromScript(
    int createMode, int createFlags, int scriptArg, CGObject* owner, float launchAngle, CGItemObj::CCFS* ccfs)
{
	int freeItemCount = getNumFreeObject__13CFlatRuntime2Fi(CFlat, 5);
	Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dcec0), freeItemCount);

	if (freeItemCount == 0) {
		int deletedCount = 0;
		int bestScriptObjectPos = 0x00989680;
		unsigned char* bestItemObj = 0;

		for (unsigned char* itemObj = (unsigned char*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat);
		     itemObj != 0;
		     itemObj = (unsigned char*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj)) {
			int canDelete = (itemObj[0x53] & 1) != 0;
			int scriptObjectPos = *(int*)(itemObj + 0x94);

			if (*(void**)(itemObj + 0x550) == 0 &&
			    static_cast<signed char>(
			        static_cast<int>((static_cast<unsigned int>(itemObj[0x50]) << 28) & 0xC0000000) >> 31) != 0 &&
			    canDelete != 0 && scriptObjectPos < bestScriptObjectPos) {
				bestScriptObjectPos = scriptObjectPos;
				bestItemObj = itemObj;
			}
		}

		if (bestItemObj != 0) {
			deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject(CFlat, bestItemObj);
			deletedCount = 1;
		} else {
			if (2U < (unsigned int)System.m_execParam) {
				Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dced4));
			}
		}

		Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dcef8), deletedCount);
		if (deletedCount == 0) {
			if (2U < (unsigned int)System.m_execParam) {
				Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dcf10));
			}
			return 0;
		}
	}

	gItemObjCreateFlags = createFlags;
	CFlatRuntime::CStack inStack[5];
	CFlatRuntime::CStack outStack;
	inStack[0].m_word = createMode;
	inStack[1].m_word = createFlags;
	inStack[2].m_word = scriptArg;
	inStack[3].m_word = owner != 0 ? owner->m_particleId : 0;
	*reinterpret_cast<float*>(&inStack[4].m_word) = launchAngle;
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	    &CFlat, 0, 1, 7, 5, inStack, &outStack);

	CGPrgObj* newItem = 0;
	if (createMode != 1) {
		newItem = (CGPrgObj*)intToClass__13CFlatRuntime2Fi(CFlat, (int)outStack.m_word);
		unsigned char* itemSelf = (unsigned char*)newItem;

		if (createMode == 2) {
			*(int*)(itemSelf + 0x558) = scriptArg;
			newItem->m_radiusCtrl.y = FLOAT_80331b18;
		}

		changeStat__8CGPrgObjFiii(newItem, 0x1B, 0, 0);

		if ((createFlags & 1) != 0) {
			float safePosDist;
			Vec safePos;
			float yRot = owner->m_rotBaseY + RandFPM__5CMathFf(FLOAT_80331b54, &Math);

			newItem->m_worldPosition.x = FLOAT_80331b1c * (float)sin((double)yRot) + owner->m_worldPosition.x;
			newItem->m_worldPosition.y = FLOAT_80331b1c + owner->m_worldPosition.y;
			newItem->m_worldPosition.z = FLOAT_80331b1c * (float)cos((double)yRot) + owner->m_worldPosition.z;

			safePosDist = CalcSafePos__8CGObjectFiP8CGObjectP3Vec(newItem, 0x41, owner, &safePos);
			if (FLOAT_80331b20 < safePosDist) {
				moveVectorHRot__8CGObjectFfffi(
				    owner, FLOAT_80331b8c + owner->m_rotBaseY, FLOAT_80331b20, safePosDist / FLOAT_80331b90, 3);
			}

			newItem->m_worldPosition = safePos;
			SetPosBG__8CGObjectFP3Veci(newItem, &safePos, 1);
		}

		if ((createFlags & 4) != 0) {
			newItem->m_worldPosition = owner->m_worldPosition;
			SetPosBG__8CGObjectFP3Veci(newItem, &newItem->m_worldPosition, 1);

			CVector moveVec((float)sin((double)launchAngle), FLOAT_80331b1c, (float)cos((double)launchAngle));
			MoveVector__8CGObjectFP3Vecfiiii(newItem, (Vec*)&moveVec, FLOAT_80331b94, 1, 0, 1, 0);
		}

		if ((createFlags & 2) != 0) {
			changeStat__8CGPrgObjFiii(newItem, 0x23, 0, 0);
			newItem->m_worldPosition.x = owner->m_worldPosition.x;
			newItem->m_worldPosition.y = owner->m_worldPosition.y + FLOAT_80331b98;
			newItem->m_worldPosition.z = owner->m_worldPosition.z;
			*(CGObject**)(itemSelf + 0x550) = owner;

			void* ownerScriptSlot = owner->m_scriptHandle[0xED];
			if ((unsigned int)System.m_execParam > 2U) {
				Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dcf34), ownerScriptSlot);
			}
			*(CGPrgObj**)(SoundBuffer + (int)ownerScriptSlot * 4 + 0x4F4) = newItem;

			void* handle = __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci(
			    0x194, Game.m_mainStage, const_cast<char*>(DAT_801dcf58), 0x28E);
			if (handle != 0) {
				handle = __ct__Q29CCharaPcs7CHandleFv(handle);
			}
			*(void**)(itemSelf + 0x564) = handle;
			Add__Q29CCharaPcs7CHandleFv(*(void**)(itemSelf + 0x564));

			unsigned int* ccfsData = (unsigned int*)ccfs;
			LoadModelASync__Q29CCharaPcs7CHandleFiUlUl(*(void**)(itemSelf + 0x564), 2, ccfsData[1], ccfsData[2]);

			if ((unsigned int)System.m_execParam > 2U) {
				Printf__7CSystemFPce(&System, const_cast<char*>(DAT_801dcf64));
			}

			*(int*)(itemSelf + 0x56C) = (int)ccfsData[3];
			*(int*)(itemSelf + 0x570) = (int)ccfsData[4];
			*(int*)(itemSelf + 0x574) = (int)ccfsData[0];
		}
	}

	return newItem;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::safeDetach(int, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80125650
 * PAL Size: 916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::carry(CGPartyObj* partyObj, int carryState, int carryMode)
{
	unsigned char* self = (unsigned char*)this;
	CFlatRuntime::CStack stack[3];
	int canSystemCall = 0;

	if (carryState == 0) {
		bool isStageCarry = false;
		bool isMenuBossStage = false;

		if (Game.m_gameWork.m_menuStageMode != 0 &&
			Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			isMenuBossStage = true;
		}
		if (isMenuBossStage) {
			unsigned int cid = static_cast<unsigned short>(partyObj->GetCID());
			unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
			if (((stageCarry >> 5) & 0xFF) != 0) {
				isStageCarry = true;
			}
		}
		if (isStageCarry && *(int*)(*(unsigned char**)((unsigned char*)partyObj + 0x58) + 0x3B4) != 0) {
			canSystemCall = 1;
		}

		*(CGPartyObj**)(self + 0x550) = partyObj;
		*(int*)(self + 0x554) = carryMode;

		if (carryMode == 0) {
			CVector attachOffset(FLOAT_80331b20, FLOAT_80331b20, FLOAT_80331b20);
			bool useBossAttachName = false;

			if (Game.m_gameWork.m_menuStageMode != 0) {
				bool condA = false;
				bool condB = false;
				bool condC = false;

				if (Game.m_gameWork.m_menuStageMode != 0 &&
					Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
					condC = true;
				}
				if (condC) {
					unsigned int cid = static_cast<unsigned short>(partyObj->GetCID());
					unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
					if (((stageCarry >> 5) & 0xFF) != 0) {
						condB = true;
					}
				}
				if (condB && *(int*)(*(unsigned char**)((unsigned char*)partyObj + 0x58) + 0x3B4) != 0) {
					condA = true;
				}
				if (condA) {
					useBossAttachName = true;
				}
			}

			const char* attachName = DAT_80331b84;
			if (useBossAttachName) {
				attachName = DAT_80331b7c;
			}
			Attach__8CGObjectFP8CGObjectPcP3Vec(this, partyObj, const_cast<char*>(attachName),
			                                    reinterpret_cast<Vec*>(&attachOffset));
			changeStat__8CGPrgObjFiii(this, 0, 0, 0);
			*(float*)(self + 0x144) = FLOAT_80331b20;
		} else {
			changeStat__8CGPrgObjFiii(this, 0xB, 0, 0);
		}
	} else if (carryState == 1 || carryState == 2) {
		bool isStageCarry = false;
		bool isMenuBossStage = false;

		if (Game.m_gameWork.m_menuStageMode != 0 &&
			Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			isMenuBossStage = true;
		}
		if (isMenuBossStage) {
			CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
			unsigned int cid = static_cast<unsigned short>(carryObj->GetCID());
			unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
			if (((stageCarry >> 5) & 0xFF) != 0) {
				isStageCarry = true;
			}
		}
		if (isStageCarry && *(int*)(*(unsigned char**)(*(unsigned char**)(self + 0x550) + 0x58) + 0x3B4) != 0) {
			canSystemCall = 1;
		}

		*(int*)(self + 0x554) = carryMode;

		if (carryMode == 0) {
			Vec safePos;
			float safeDist = CalcSafePos__8CGObjectFiP8CGObjectP3Vec(
				this, 0x41, *(CGPartyObj**)(self + 0x550), &safePos);
			if (FLOAT_80331b20 < safeDist) {
				CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
				moveVectorHRot__8CGObjectFfffi(
					carryObj,
					FLOAT_80331b8c + *(float*)((unsigned char*)carryObj + 0x1A8),
					FLOAT_80331b20,
					safeDist / FLOAT_80331b90,
					3);
			}
			Detach__8CGObjectFv(this);
			*(Vec*)(self + 0x15C) = safePos;
			*(int*)(self + 0x550) = 0;
			changeStat__8CGPrgObjFiii(this, 0, 0, 0);
			*(int*)(self + 0x56C) = 8;
			*(float*)(self + 0x144) = FLOAT_80331b20;
		} else {
			changeStat__8CGPrgObjFiii(this, ((int)~(carryState - 1 | 1 - carryState) >> 0x1F) + 0xD, 0, 0);
		}

		*reinterpret_cast<u32*>(self + 0x94) = 0x1194;
	}

	if ((*(unsigned int*)(self + 0x5C) & 0x10) != 0 && canSystemCall != 0) {
		stack[0].m_word = 3;
		stack[1].m_word = static_cast<unsigned int>((-carryState | carryState) >> 0x1F);
		stack[2].m_word = 0;
		SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
			&CFlat, 0, 1, 9, 3, stack, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012564c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onChangePrg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::statPot()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801254cc
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onFrameAlways()
{
	unsigned char* self = (unsigned char*)this;
	int countdown = *(int*)(self + 0x56C);

	if (countdown != 0) {
		int next = countdown - 1;
		*(int*)(self + 0x56C) = next & ~(next >> 0x1F);
		float radius = *(float*)(self + 0x568) * (float)(8 - *(int*)(self + 0x56C));
		*(float*)(self + 0x144) = radius * FLOAT_80331b68;
	}

	if (*(int*)(self + 0x500) == 0xA) {
		int canUseTrace;

		if (static_cast<int>(Game.m_gameWork.m_gameInitFlag) != 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(*(unsigned char*)(CFlat + 4836)) << 28) & 0xC0000000) >> 31) != 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(*(unsigned char*)(CFlat + 4836)) << 29) & 0xC0000000) >> 31) != 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(*(unsigned char*)(self + 0x9A)) << 24) & 0xC0000000) >> 31) != 0 &&
		    *(int*)(CFlat + 4780) == 0 && *(void**)(self + 0x550) == 0) {
			canUseTrace = true;
		} else {
			canUseTrace = false;
		}

		if (canUseTrace && *(int*)(CFlat + 66604) == 0) {
			*(int*)(CFlat + 66604) = GetFreeParticleSlot__13CFlatRuntime2Fv(CFlat);
			putParticleTrace__8CGPrgObjFiiP8CGObjectfi(this, 0x141, *(int*)(CFlat + 66604), this, FLOAT_80331b18, 0);
		} else if (!canUseTrace && *(int*)(CFlat + 66604) != 0) {
			EndParticleSlot__13CFlatRuntime2Fii(CFlat, *(int*)(CFlat + 66604), 0);
			*(int*)(CFlat + 66604) = 0;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012529C
 * PAL Size: 556b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onHitParticle(int effectIndex, int, int, int, Vec*, PPPIFPARAM* hitParam)
{
	unsigned char* self = (unsigned char*)this;
	int worldParamA = *(int*)(self + 0x500);
	unsigned char* particleRow = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2] + hitParam->m_particleIndex * 0x48);
	int particleAttr = (int)*reinterpret_cast<unsigned short*>(particleRow + 8);

	if (worldParamA == 0xD || worldParamA == 0xE) {
		if (((particleAttr == 0 || particleAttr == 4) && worldParamA == 0xD) ||
		    (particleAttr == 1 && worldParamA == 0xE)) {
			int particleNo;
			int classControl;

			switch (particleAttr) {
			case 1:
				particleNo = 0x20;
				classControl = 0x491;
				break;
			case 0:
				particleNo = 0x1F;
				classControl = 0x492;
				break;
			case 4:
				particleNo = 0x2F;
				classControl = 0x493;
				break;
			}

			EndParticleSlot__13CFlatRuntime2Fii(CFlat, *(int*)(self + 0x55C), 0);
			ResetParticleWork__13CFlatRuntime2Fii(CFlat, particleNo | 0x100, *(int*)(self + 0x55C));
			SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, *(Vec*)(self + 0x15C), FLOAT_80331b20);
			SetParticleWorkCol__13CFlatRuntime2Fiif(CFlat, 9, 0, FLOAT_80331b18);
			SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(CFlat, classControl, this);
			PutParticleWork__13CFlatRuntime2Fv(CFlat);
			*(unsigned int*)(self + 0x1C0) &= 0xFFF7FFFF;
			addSubStat__8CGPrgObjFv(this);
		}
	} else {
		if (((worldParamA != 0xCB) || (*(int*)(self + 0x520) != 0x24)) && *(int*)(self + 0x520) != 0x25) {
			return;
		}

		if ((static_cast<unsigned int>(particleAttr - 0x66) <= 1U) || (particleAttr == 0x65)) {
			int classId = hitParam->m_classId;
			unsigned char* classObj;

			if (classId != 0) {
				classObj = (unsigned char*)intToClass__13CFlatRuntime2Fi(CFlat, classId);
			} else {
				classObj = 0;
			}

			void* objectBehavior = *(void**)(classObj + 0x48);
			unsigned int cid =
			    reinterpret_cast<unsigned int (*)(void*)>((*reinterpret_cast<void***>(objectBehavior))[3])(
			        objectBehavior);

			if ((cid & 0x6D) == 0x6D && *(void**)(self + 0x550) == classObj) {
				changeStat__8CGPrgObjFiii(this, 0x26, 0, 0);
			}
		}
	}

	IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(CFlat, effectIndex, this);
}

/*
 * --INFO--
 * PAL Address: 0x80124FE0
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::loadModel()
{
	unsigned char* self = (unsigned char*)this;
	int modelNo = -1;
	int modelVariant = 0;
	int modelFlag = 0;
	unsigned long animFlags = (unsigned long)-1;
	char* standAnim = const_cast<char*>(s_stand_80331B44);
	int useParticleTable = 1;
	int itemType = *(int*)(self + 0x500);

	switch (itemType) {
	case 0xA:
		modelNo = 8;
		useParticleTable = 0;
		break;
	case 0xC:
		modelNo = 0x27;
		useParticleTable = 0;
		break;
	case 0xD:
		modelNo = 0x33;
		useParticleTable = 0;
		break;
	case 0xE:
		modelNo = 0x33;
		modelVariant = 1;
		useParticleTable = 0;
		break;
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x1F:
	case 0x20:
	case 0x21:
	case 0x24: {
		int itemEntryOffset = *(int*)(self + 0x504) * 0x48 + 2;
		int itemEntry = *(unsigned short*)(Game.unkCFlatData0[2] + itemEntryOffset);

		self[0x53] = 1;
		modelNo = itemEntry & 0xFFF;
		modelVariant = itemEntry >> 0xC;
		self[0x50] = static_cast<unsigned char>(__rlwimi(self[0x50], 1, 3, 28, 28));
		*(int*)(self + 0x94) = 0x1194;
		animFlags = 0x12;
		modelFlag = 1;
		break;
	}
	case 0xCB:
	default:
		break;
	}

	if (modelNo >= 0) {
		LoadModel__8CGObjectFiUlUli(this, 3, modelNo, modelVariant, modelFlag);
		LoadAnim__8CGObjectFPciiiUl(this, standAnim, 0, 0, 3, animFlags);
		SetAnimSlot__8CGObjectFii(this, 0, 0);
		PlayAnim__8CGObjectFiiiiiPSc(this, 0, 1, 0, -1, -1, 0);
	}

	if (*(int*)(self + 0x500) == 0x12) {
		DispCharaParts__8CGObjectFi(this, 0);
		self[0x50] = static_cast<unsigned char>(__rlwimi(self[0x50], 1, 4, 27, 27));
	}

	if (useParticleTable != 0) {
		for (int i = 0; i < 3; i++) {
			if (i != 0 || m_createFlags != 1) {
				int entryBase = Game.unkCFlatData0[2] + *(int*)(self + 0x504) * 0x48;
				int particleNo = *(unsigned short*)(entryBase + i * 2 + 0x14);

				if (particleNo != 0xFFFF) {
					float particleScale =
					    FLOAT_80331b50 * (float)(unsigned short)*(unsigned short*)(entryBase + 0x10) + FLOAT_80331b4c;
					putParticle__8CGPrgObjFiiP8CGObjectfi(
					    this, particleNo | 0x100, *(int*)(self + 0x55C), this, particleScale, 0);
				}
			}
		}
	}

	if (*(int*)(self + 0x500) == 0xCB) {
		*(float*)(self + 0x1D4) = FLOAT_80331b54 - RandF__5CMathFf(FLOAT_80331b58, &Math);
		*(unsigned char*)(self + 0x9A) =
		    static_cast<unsigned char>(__rlwimi(*(unsigned char*)(self + 0x9A), 0, 2, 29, 29));
	}

	self[0x54C] = static_cast<unsigned char>(__rlwimi(self[0x54C], 1, 7, 24, 24));
}

/*
 * --INFO--
 * PAL Address: 0x80124fac
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onNewFinished()
{
	*(float*)((u8*)this + 0x568) = *(float*)((u8*)this + 0x144);
	*(u16*)((u8*)this + 0x560) = (u16)((gItemObjCreateFlags >> 3) & 1);
	loadModel();
}

/*
 * --INFO--
 * PAL Address: 0x80124e04
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::DrawOmoideName(CFont* font)
{
	unsigned char* self = (unsigned char*)this;

	if ((signed char)((int)(((unsigned int)*(unsigned char*)(self + 0x9A) << 0x1A) & 0xC0000000) >> 31) != 0) {
		void* charaHandle = *(void**)(self + 0xF8);
		bool hasModel = false;
		if (charaHandle != 0 && *(void**)((unsigned char*)charaHandle + 0x168) != 0) {
			hasModel = true;
		}

		if (hasModel && *(int*)(self + 0x500) == 0xCB && FLOAT_80331b20 < *(float*)(self + 0x74) &&
		    FLOAT_80331b20 != *(float*)(self + 0x4B0)) {
			font->SetTlut(7);

			int alphaInt = (int)(FLOAT_80331b30 * *(float*)(self + 0x4B0));
			GXColor constructedColor;
			GXColor textColor = *(GXColor*)__ct__6CColorFUcUcUcUc(&constructedColor, 0xFF, 0xFF, 0xFF, alphaInt);
			SetColor__5CFontF8_GXColor(font, &textColor);

			const ItemObjFlatData* flatData = reinterpret_cast<const ItemObjFlatData*>(&Game.m_cFlatDataArr[1]);
			const char* name = flatData->table[2].index[*(int*)(self + 0x570)];
			float width = font->GetWidth(name);
			float depthScale = FLOAT_80331b18 / (*(float*)(self + 0x74) - FLOAT_80331b1c);
			float posY = FLOAT_80331b34 - FLOAT_80331b34 * *(float*)(self + 0x6C) * depthScale;
			float posZ = *(float*)(self + 0x70) * depthScale;
			float posX =
			    -(FLOAT_80331b3c * width - (FLOAT_80331b38 * *(float*)(self + 0x68) * depthScale + FLOAT_80331b38));

			font->SetPosX(posX);
			font->SetPosY(posY - FLOAT_80331b40);
			font->SetPosZ(posZ);
			font->Draw(name);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80124cb8
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::ItemJump(int state, float jump)
{
	for (CGItemObj* itemObj = static_cast<CGItemObj*>(FindGItemObjFirst__13CFlatRuntime2Fv(CFlat)); itemObj != 0;
	     itemObj = static_cast<CGItemObj*>(FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj))) {
		CGObject* object = reinterpret_cast<CGObject*>(itemObj);

		if ((object->m_objectFlags & 0x10) == 0) {
			unsigned int mapMask = object->m_bgHitMask;
			CMapCylinderRaw cylinder;
			Vec move;

			move.x = FLOAT_80331b20;
			move.y = FLOAT_80331b24;
			move.z = FLOAT_80331b20;

			cylinder.m_bottom = object->m_worldPosition;
			cylinder.m_bottom.y += FLOAT_80331b1c;
			cylinder.m_top.x = FLOAT_80331b20;
			cylinder.m_top.y = FLOAT_80331b20;
			cylinder.m_top.z = FLOAT_80331b20;
			cylinder.m_axis.x = FLOAT_80331b20;
			cylinder.m_axis.y = FLOAT_80331b24;
			cylinder.m_axis.z = FLOAT_80331b20;
			cylinder.m_radius = FLOAT_80331b20;
			cylinder.m_boundsMin.x = FLOAT_80331b28;
			cylinder.m_boundsMin.y = FLOAT_80331b28;
			cylinder.m_boundsMin.z = FLOAT_80331b28;
			cylinder.m_boundsMax.x = FLOAT_80331b2c;
			cylinder.m_boundsMax.y = FLOAT_80331b2c;
			cylinder.m_boundsMax.z = FLOAT_80331b2c;

			if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(
			        &MapMng, reinterpret_cast<CMapCylinder*>(&cylinder), &move, mapMask) != 0 &&
			    g_hit_f->m_groupIndex == state) {
				object->m_groundHitOffset.y += jump;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80124c2c
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::DeleteAllFieldItem()
{
	for (CGItemObj* itemObj = (CGItemObj*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat); itemObj != 0;
	     itemObj = (CGItemObj*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj)) {
		if (itemObj->m_owner == 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(itemObj->m_stateFlags0) << 28) & 0xC0000000) >> 31) != 0) {
			itemObj->m_flags |= 0x80;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80124b88
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::DispAllFieldItem(int show)
{
	for (CGItemObj* itemObj = (CGItemObj*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat); itemObj != 0;
	     itemObj = (CGItemObj*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj)) {
		if (itemObj->m_owner == 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(itemObj->m_stateFlags0) << 28) & 0xC0000000) >> 31) != 0) {
			if (show != 0) {
				itemObj->m_displayFlags &= 0xffbfffff;
			} else {
				itemObj->m_displayFlags |= 0x400000;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80124b78
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGItemObj::GetCID()
{
	return 0x1d;
}
