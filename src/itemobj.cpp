#include "ffcc/itemobj.h"
#include "ffcc/math.h"
#include "ffcc/prgobj.h"
#include "ffcc/p_game.h"
#include "ffcc/vector.h"

#include <math.h>
#include <string.h>

class CMapMng;

extern "C" void onCreate__8CGPrgObjFv(void*);
extern "C" void onDestroy__8CGPrgObjFv(void*);
extern "C" int GetFreeParticleSlot__13CFlatRuntime2Fv(void*);
extern "C" void DeleteParticleSlot__13CFlatRuntime2Fii(void*, int);
extern "C" void __dt__Q29CCharaPcs7CHandleFv(void*, int);
extern "C" int __cntlzw(unsigned int);
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
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void SetPosZ__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);
extern "C" int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, void*, void*, unsigned int);

extern unsigned char CFlat[];
extern CMapMng MapMng;
extern CMath Math;
extern float FLOAT_80331b20;
extern float FLOAT_80331b1c;
extern float FLOAT_80331b24;
extern float FLOAT_80331b28;
extern float FLOAT_80331b2c;
extern float FLOAT_80331b18;
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
extern float FLOAT_80331b68;
extern double DOUBLE_80331ba0;
extern unsigned char DAT_8032ec90[];
extern int DAT_8032ee90;
extern char SoundBuffer[];
extern char DAT_80331b7c[];
extern char DAT_80331b84[];
extern char DAT_80331bc8[];
extern char DAT_801dcec0[];
extern char DAT_801dced4[];
extern char DAT_801dcef8[];
extern char DAT_801dcf10[];
extern char DAT_801dcf80[];
extern char DAT_801dcf34[];
extern char DAT_801dcf58[];
extern char DAT_801dcf64[];
extern char DAT_801dd010[];

struct ItemObjFlatTableEntry {
	int count;
	const char** index;
	char* buffer;
};

struct ItemObjFlatData {
	char pad[0x6c];
	ItemObjFlatTableEntry table[8];
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
	unsigned char* self = (unsigned char*)this;

	onCreate__8CGPrgObjFv(self);
	self[0x54d] &= 0x7f;
	*(int*)(self + 0x550) = 0;
	*(int*)(self + 0x558) = 0;
	*(unsigned short*)(self + 0x560) = 0;
	*(unsigned short*)(self + 0x562) = 0;
	*(int*)(self + 0x564) = 0;
	*(int*)(self + 0x56c) = 0;
	memset(self + 0x570, 0, 0xc);
	*(int*)(self + 0x55c) = GetFreeParticleSlot__13CFlatRuntime2Fv(CFlat);
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

	if (*(int*)(self + 0x564) != 0) {
		__dt__Q29CCharaPcs7CHandleFv(*(void**)(self + 0x564), 1);
	}

	DeleteParticleSlot__13CFlatRuntime2Fii(CFlat, *(int*)(self + 0x55c));
	onDestroy__8CGPrgObjFv(self);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
	unsigned int stateBits = ((unsigned int)self[0x50] << 0x1c) | ((unsigned int)self[0x50] >> 4);

	if ((int)stateBits < 0 && *(int*)(self + 0x550) == 0) {
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

	if (state >= 0x26 && state <= 0x27) {
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
	extern float FLOAT_80331b18;
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
	void* pendingHandle = *(void**)(self + 0x564);

	if (pendingHandle != 0 && IsLoadModelASyncCompleted__Q29CCharaPcs7CHandleFv(pendingHandle) != 0) {
		if ((unsigned int)System.m_execParam > 2U) {
			Printf__7CSystemFPce(&System, DAT_801dd010);
		}

		*(void**)(self + 0xF8) = pendingHandle;
		*(void**)(self + 0x564) = 0;

		if (*(int*)(self + 0x500) == 0xCB) {
			LoadAnim__8CGObjectFPciiiUl(this, 0, 0, 0, 0, 0);
			SetAnimSlot__8CGObjectFii(this, 0, 0);
			PlayAnim__8CGObjectFiiiiiPSc(this, 0, 1, 0, -1, -1, 0);

			int soundEntry = *(int*)(*(int*)(SoundBuffer + 0x1260 + 0xF8) + 0x178);
			if (soundEntry == 0) {
				soundEntry = -1;
			} else {
				soundEntry = *(int*)(soundEntry + 0x14);
			}

			int ownerAttr = *(int*)(*(int*)(*(int*)(self + 0x550) + 0x58) + 0x3B4);
			int itemDataEntry = Game.game.unkCFlatData0[2] + *(int*)(self + 0x504) * 0x48;
			float particleScale =
			    FLOAT_80331b50 * (float)(unsigned short)*(unsigned short*)(itemDataEntry + 0x10) + FLOAT_80331b4c;

			putParticle__8CGPrgObjFiiP8CGObjectfi(this, (soundEntry << 8) | ownerAttr, *(int*)(self + 0x558), this,
			                                      particleScale, 0x12909);

			CVector zero(FLOAT_80331b20, FLOAT_80331b20, FLOAT_80331b20);
			SetDamageCol__8CGObjectFiPcffP3Vec(this, 0, DAT_80331bc8, FLOAT_80331bb8, FLOAT_80331bb8,
			                                   reinterpret_cast<Vec*>(&zero));
			*(int*)(self + 0x384) = 8;
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
		unsigned char stateFlags = self[0x50];
		int isActive = (int)(((unsigned int)stateFlags << 0x1c) | ((unsigned int)stateFlags >> 4)) < 0;

		if (!hasOwner && isActive) {
			double distance = (double)FLOAT_80331b20;

			if (Game.game.unk_flat3_0xc7d0 == 0) {
				if (*(int*)(CFlat + 0x4780) == 1) {
					Vec partyCenter;

					partyCenter.x = (Game.game.m_partyMinX + Game.game.m_partyMaxX) * FLOAT_80331b3c;
					partyCenter.y = (Game.game.m_partyMinY + Game.game.m_partyMaxY) * FLOAT_80331b3c;
					partyCenter.z = (Game.game.m_partyMinZ + Game.game.m_partyMaxZ) * FLOAT_80331b3c;
					distance = (double)PSVECDistance((Vec*)(self + 0x15c), &partyCenter);
				}
			} else {
				distance = (double)PSVECDistance((Vec*)(self + 0x15c), (Vec*)(Game.game.unk_flat3_0xc7d0 + 0x15c));
			}

			if (*(int*)(self + 0x94) < 1 || DOUBLE_80331ba0 < distance) {
				Printf__7CSystemFPce(&System, DAT_801dcf80);
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
			self[0x54d] = (self[0x54d] & 0x7f) | 0x80;
		}
		break;
	case 0xB:
		if (*(int*)(self + 0x528) == *(int*)(self + 0x554)) {
			CVector attachOffset(FLOAT_80331b20, FLOAT_80331b20, FLOAT_80331b20);
			bool useBossAttachName = false;

			if (Game.game.m_gameWork.m_menuStageMode != 0) {
				bool condA = false;
				bool condB = false;
				bool condC = false;

				if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
					condC = true;
				}
				if (condC) {
					CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
					typedef unsigned int (*PartyVFunc)(CGPartyObj*);
					PartyVFunc getCid = reinterpret_cast<PartyVFunc>((*reinterpret_cast<void***>(carryObj))[3]);
					unsigned int cid = getCid(carryObj);
					unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
					if (((stageCarry >> 5) & 0xFF) != 0) {
						condB = true;
					}
				}
				if (condB && *(int*)(*(unsigned char**)(*(unsigned char**)(self + 0x550) + 0x58) + 0x3B4) != 0) {
					condA = true;
				}
				if (condA) {
					useBossAttachName = true;
				}
			}

			char* attachName = DAT_80331b84;
			if (useBossAttachName) {
				attachName = DAT_80331b7c;
			}
			Attach__8CGObjectFP8CGObjectPcP3Vec(this, *(void**)(self + 0x550), attachName,
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
			float safeDist = CalcSafePos__8CGObjectFiP8CGObjectP3Vec(this, 0x41, carryObj, &safePos);

			if (FLOAT_80331b20 < safeDist) {
				moveVectorHRot__8CGObjectFfffi(
				    carryObj, FLOAT_80331b8c + *(float*)((unsigned char*)carryObj + 0x1A8), FLOAT_80331b20,
				    safeDist / FLOAT_80331b90, 3);
			}

			Detach__8CGObjectFv(this);
			*(Vec*)(self + 0x15C) = safePos;

			float launchSpeed = FLOAT_80331b90;
			if (*(int*)(self + 0x520) != 0xC) {
				launchSpeed = FLOAT_80331b40;
			}

			float ownerRotY = *(float*)((unsigned char*)carryObj + 0x1B4);
			CVector moveVec((float)sin((double)ownerRotY), FLOAT_80331b54, (float)cos((double)ownerRotY));
			MoveVector__8CGObjectFP3Vecfiiii(this, reinterpret_cast<Vec*>(&moveVec), launchSpeed, 1, 0, 1, 0);

			*(int*)(self + 0x550) = 0;
			*(int*)(self + 0x56C) = 8;
			*(float*)(self + 0x144) = FLOAT_80331b20;
		}

		if (*(int*)(self + 0x554) <= *(int*)(self + 0x528)) {
			int worldParamA = *(int*)(self + 0x500);
			bool isActive = (int)((unsigned int)self[0x50] << 0x18) < 0;

			if ((worldParamA == 1 || worldParamA == 2) && isActive) {
				changeStat__8CGPrgObjFiii(this, 0x1F, 0, 0);
			} else if (isActive) {
				changeStat__8CGPrgObjFiii(this, 0, 0, 0);
			}
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
	case 0x23:
		if (*(int*)(self + 0x52c) == 1 && *(int*)(self + 0x530) < 9) {
			float wobble = (float)sin((double)(FLOAT_80331b9c * (float)(*(int*)(self + 0x530)) * FLOAT_80331b68));

			prgObj->m_rotationZ = wobble;
			prgObj->m_rotationY = wobble;
			prgObj->m_rotationX = wobble;
		}
		break;
	case 0x24:
		prgObj->m_moveOffset.x = FLOAT_80331bb0;
		prgObj->m_moveOffset.y = zero;
		prgObj->m_moveOffset.z = FLOAT_80331bb0;
		prgObj->m_rotTargetY = prgObj->m_rotTargetY + FLOAT_80331b50;
		break;
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
	unsigned char* bestItemObj;
	int deletedCount = 0;

	while (deletedCount < maxDeleteCount) {
		void* bestScriptObject = (void*)0x00989680;
		bestItemObj = 0;

		for (unsigned char* itemObj = (unsigned char*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat);
			 itemObj != 0;
			 itemObj = (unsigned char*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj)) {
			unsigned char flags = itemObj[0x50];
			unsigned char priorityMask = itemObj[0x53];
			int isActive = (int)(((unsigned int)flags << 28) | ((unsigned int)flags >> 4)) < 0;
			int scriptObjectPos = *(int*)(itemObj + 0x48);

			if (*(int*)(itemObj + 0x44) == 0 && isActive != 0 && (priorityMask & deleteMask) != 0 &&
				scriptObjectPos < (int)bestScriptObject) {
				bestScriptObject = (void*)scriptObjectPos;
				bestItemObj = itemObj;
			}
		}

		if (bestItemObj == 0) {
			break;
		}

		deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject(CFlat, bestItemObj);
		deletedCount++;
	}

	if ((unsigned int)System.m_execParam > 2U && deletedCount < maxDeleteCount) {
		Printf__7CSystemFPce(&System, DAT_801dced4);
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
	Printf__7CSystemFPce(&System, DAT_801dcec0, freeItemCount);

	if (freeItemCount == 0) {
		int deletedCount = 0;
		unsigned char* bestItemObj = 0;
		void* bestScriptPos = reinterpret_cast<void*>(0x00989680);

		for (unsigned char* itemObj = (unsigned char*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat);
		     itemObj != 0;
		     itemObj = (unsigned char*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj)) {
			unsigned char flags = itemObj[0x50];
			int isActive = (int)(((unsigned int)flags << 28) | ((unsigned int)flags >> 4)) < 0;
			int canDelete = (itemObj[0x53] & 1) != 0;
			int scriptPos = *(int*)(itemObj + 0x48);

			if (*(int*)(itemObj + 0x44) == 0 && isActive != 0 && canDelete != 0 &&
			    scriptPos < (int)bestScriptPos) {
				bestScriptPos = (void*)scriptPos;
				bestItemObj = itemObj;
			}
		}

		if (bestItemObj == 0) {
			if ((unsigned int)System.m_execParam > 2U) {
				Printf__7CSystemFPce(&System, DAT_801dced4);
			}
		} else {
			deleteObject__12CFlatRuntimeFPQ212CFlatRuntime7CObject(CFlat, bestItemObj);
			deletedCount = 1;
		}

		Printf__7CSystemFPce(&System, DAT_801dcef8, deletedCount);
		if (deletedCount == 0) {
			if ((unsigned int)System.m_execParam > 2U) {
				Printf__7CSystemFPce(&System, DAT_801dcf10);
			}
			return 0;
		}
	}

	int ownerParticleId = 0;
	if (owner != 0) {
		ownerParticleId = *(short*)((unsigned char*)owner + 0x30);
	}

	DAT_8032ee90 = createFlags;
	CFlatRuntime::CStack inStack[3];
	CFlatRuntime::CStack outStack;
	inStack[0].m_word = createMode;
	inStack[1].m_word = createFlags;
	inStack[2].m_word = scriptArg;
	SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	    &CFlat, 0, 1, 7, 5, inStack, &outStack);

	if (createMode == 1) {
		return 0;
	}

	CGPrgObj* newItem = (CGPrgObj*)intToClass__13CFlatRuntime2Fi(CFlat, (int)outStack.m_word);
	unsigned char* itemSelf = (unsigned char*)newItem;

	if (createMode == 2) {
		*(int*)(itemSelf + 0x558) = scriptArg;
		newItem->m_radiusCtrl.y = FLOAT_80331b18;
	}

	changeStat__8CGPrgObjFiii(newItem, 0x1B, 0, 0);

	if ((createFlags & 1) != 0 && owner != 0) {
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

	if ((createFlags & 4) != 0 && owner != 0) {
		newItem->m_worldPosition = owner->m_worldPosition;
		SetPosBG__8CGObjectFP3Veci(newItem, &newItem->m_worldPosition, 1);

		CVector moveVec((float)sin((double)launchAngle), FLOAT_80331b1c, (float)cos((double)launchAngle));
		MoveVector__8CGObjectFP3Vecfiiii(newItem, (Vec*)&moveVec, FLOAT_80331b94, 1, 0, 1, 0);
	}

	if ((createFlags & 2) != 0 && owner != 0) {
		changeStat__8CGPrgObjFiii(newItem, 0x23, 0, 0);
		newItem->m_worldPosition.x = owner->m_worldPosition.x;
		newItem->m_worldPosition.y = owner->m_worldPosition.y + FLOAT_80331b98;
		newItem->m_worldPosition.z = owner->m_worldPosition.z;
		*(CGObject**)(itemSelf + 0x550) = owner;

		void* ownerScriptSlot = owner->m_scriptHandle[0xED];
		if ((unsigned int)System.m_execParam > 2U) {
			Printf__7CSystemFPce(&System, DAT_801dcf34, ownerScriptSlot);
		}
		*(CGPrgObj**)(SoundBuffer + (int)ownerScriptSlot * 4 + 0x4F4) = newItem;

		void* handle = __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci(
		    0x194, Game.game.m_mainStage, DAT_801dcf58, 0x28E);
		if (handle != 0) {
			handle = __ct__Q29CCharaPcs7CHandleFv(handle);
		}
		*(void**)(itemSelf + 0x564) = handle;
		Add__Q29CCharaPcs7CHandleFv(*(void**)(itemSelf + 0x564));

		if (ccfs != 0) {
			unsigned int* ccfsData = (unsigned int*)ccfs;
			LoadModelASync__Q29CCharaPcs7CHandleFiUlUl(*(void**)(itemSelf + 0x564), 2, ccfsData[1], ccfsData[2]);
			*(int*)(itemSelf + 0x56C) = (int)ccfsData[3];
			*(int*)(itemSelf + 0x570) = (int)ccfsData[4];
			*(int*)(itemSelf + 0x574) = (int)ccfsData[0];
		}

		if ((unsigned int)System.m_execParam > 2U) {
			Printf__7CSystemFPce(&System, DAT_801dcf64);
		}
	}

	(void)ownerParticleId;
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
	int canSystemCall = 0;

	if (carryState == 0) {
		bool isStageCarry = false;
		bool isMenuBossStage = false;

		if (Game.game.m_gameWork.m_menuStageMode != 0 &&
			Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			isMenuBossStage = true;
		}
		if (isMenuBossStage) {
			typedef unsigned int (*PartyVFunc)(CGPartyObj*);
			PartyVFunc getCid = reinterpret_cast<PartyVFunc>((*reinterpret_cast<void***>(partyObj))[3]);
			unsigned int cid = getCid(partyObj);
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

			if (Game.game.m_gameWork.m_menuStageMode != 0) {
				bool condA = false;
				bool condB = false;
				bool condC = false;

				if (Game.game.m_gameWork.m_menuStageMode != 0 &&
					Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
					condC = true;
				}
				if (condC) {
					typedef unsigned int (*PartyVFunc)(CGPartyObj*);
					PartyVFunc getCid = reinterpret_cast<PartyVFunc>((*reinterpret_cast<void***>(partyObj))[3]);
					unsigned int cid = getCid(partyObj);
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

			char* attachName = DAT_80331b84;
			if (useBossAttachName) {
				attachName = DAT_80331b7c;
			}
			Attach__8CGObjectFP8CGObjectPcP3Vec(this, partyObj, attachName, reinterpret_cast<Vec*>(&attachOffset));
			changeStat__8CGPrgObjFiii(this, 0, 0, 0);
			*(float*)(self + 0x144) = FLOAT_80331b20;
		} else {
			changeStat__8CGPrgObjFiii(this, 0xB, 0, 0);
		}
	} else if (carryState == 1 || carryState == 2) {
		bool isStageCarry = false;
		bool isMenuBossStage = false;

		if (Game.game.m_gameWork.m_menuStageMode != 0 &&
			Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			isMenuBossStage = true;
		}
		if (isMenuBossStage) {
			CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
			typedef unsigned int (*PartyVFunc)(CGPartyObj*);
			PartyVFunc getCid = reinterpret_cast<PartyVFunc>((*reinterpret_cast<void***>(carryObj))[3]);
			unsigned int cid = getCid(carryObj);
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
			CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
			Vec safePos;
			float safeDist = CalcSafePos__8CGObjectFiP8CGObjectP3Vec(this, 0x41, carryObj, &safePos);
			if (FLOAT_80331b20 < safeDist) {
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

		self[0x94] = 0;
		self[0x95] = 0;
		self[0x96] = 0x11;
		self[0x97] = 0x94;
	}

	if ((*(unsigned int*)(self + 0x5C) & 0x10) != 0 && canSystemCall != 0) {
		CFlatRuntime::CStack stack[3];
		stack[0].m_word = 3;
		stack[1].m_word = static_cast<unsigned int>((-carryState | carryState) >> 0x1F);
		stack[2].m_word = 0;
		SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
			&CFlat, 0, 1, 9, 3, stack, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onFrameAlways()
{
	unsigned char* self = (unsigned char*)this;
	unsigned int countdown = *(unsigned int*)(self + 0x568);

	if (countdown != 0) {
		unsigned int next = countdown - 1;
		*(unsigned int*)(self + 0x568) = next & ~((int)next >> 0x1F);
		*(float*)(self + 0x144) = *(float*)(self + 0x56C) * (float)(8 - *(int*)(self + 0x568)) * FLOAT_80331b68;
	}

	if (*(int*)(self + 0x500) == 0xA) {
		unsigned char flatFlags = *(unsigned char*)(CFlat + 4836);
		int* traceParticleSlot = (int*)(CFlat + 66604);
		bool canUseTrace =
		    Game.game.m_gameWork.m_gameInitFlag != 0 &&
		    (int)(((unsigned int)flatFlags << 0x1C) | ((unsigned int)flatFlags >> 4)) < 0 &&
		    (int)(((unsigned int)flatFlags << 0x1D) | ((unsigned int)flatFlags >> 3)) < 0 &&
		    (int)((unsigned int)*(unsigned char*)(self + 0x9A) << 0x18) < 0 &&
		    *(int*)(CFlat + 4780) == 0 &&
		    *(int*)(self + 0x550) == 0;

		if (canUseTrace && *traceParticleSlot == 0) {
			*traceParticleSlot = GetFreeParticleSlot__13CFlatRuntime2Fv(CFlat);
			putParticleTrace__8CGPrgObjFiiP8CGObjectfi(this, 0x141, *traceParticleSlot, this, FLOAT_80331b18, 0);
		} else if (!canUseTrace && *traceParticleSlot != 0) {
			EndParticleSlot__13CFlatRuntime2Fii(CFlat, *traceParticleSlot, 0);
			*traceParticleSlot = 0;
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
	unsigned int particleAttr = (unsigned int)*(unsigned short*)(Game.game.unkCFlatData0[2] +
	                                                             *(int*)((unsigned char*)hitParam + 0x0) * 0x48 + 8);

	if (worldParamA == 0xD || worldParamA == 0xE) {
		if (((particleAttr == 0 || particleAttr == 4) && worldParamA == 0xD) ||
		    (particleAttr == 1 && worldParamA == 0xE)) {
			int particleNo = 0;
			int classControl = 0;

			if (particleAttr == 1) {
				particleNo = 0x20;
				classControl = 0x491;
			} else if (particleAttr == 0) {
				particleNo = 0x1F;
				classControl = 0x492;
			} else if (particleAttr == 4) {
				particleNo = 0x2F;
				classControl = 0x493;
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
		if ((worldParamA != 0xCB || *(int*)(self + 0x520) == 0x24) && *(int*)(self + 0x520) != 0x25) {
			if ((particleAttr >= 0x65 && particleAttr <= 0x67)) {
				unsigned char* classObj = 0;

				if (*(short*)((unsigned char*)hitParam + 4) != 0) {
					classObj =
					    (unsigned char*)intToClass__13CFlatRuntime2Fi(CFlat, (int)*(short*)((unsigned char*)hitParam + 4));
				}

				if (classObj != 0) {
					void* objectBehavior = *(void**)(classObj + 0x48);
					unsigned int cid =
					    reinterpret_cast<unsigned int (*)(void*)>((*reinterpret_cast<void***>(objectBehavior))[3])(
					        objectBehavior);

					if ((cid & 0x6D) == 0x6D && *(void**)(self + 0x550) == classObj) {
						changeStat__8CGPrgObjFiii(this, 0x26, 0, 0);
					}
				}
			}
		} else {
			return;
		}
	}

	IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(CFlat, (short)effectIndex, this);
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
	int useParticleTable = 1;
	int worldParamA = *(int*)(self + 0x500);
	int worldParamB = *(int*)(self + 0x504);

	if (worldParamA < 0x18) {
		if (worldParamA == 0xD) {
			modelNo = 0x33;
			useParticleTable = 0;
		} else if (worldParamA < 0xD) {
			if (worldParamA != 0xB) {
				if (worldParamA > 9) {
					modelNo = 8;
					useParticleTable = 0;
				}
			} else {
				modelNo = 0x27;
				useParticleTable = 0;
			}
		} else if (worldParamA < 0x12 && worldParamA < 0xF) {
			modelNo = 0x33;
			modelVariant = 1;
			useParticleTable = 0;
		}
	} else if (worldParamA >= 0x1F && worldParamA <= 0x21) {
		unsigned short itemEntry = *(unsigned short*)(Game.game.unkCFlatData0[2] + worldParamB * 0x48 + 2);

		self[0x53] = 1;
		modelNo = itemEntry & 0xFFF;
		modelVariant = itemEntry >> 0xC;
		self[0x50] = (self[0x50] & 0xF7) | 8;
		self[0x94] = 0;
		self[0x95] = 0;
		self[0x96] = 0x11;
		self[0x97] = 0x94;
		modelFlag = 1;
	}

	if (modelNo >= 0) {
		LoadModel__8CGObjectFiUlUli(this, 3, modelNo, modelVariant, modelFlag);
		LoadAnim__8CGObjectFPciiiUl(this, 0, 0, 0, 0, 0);
		SetAnimSlot__8CGObjectFii(this, 0, 0);
		PlayAnim__8CGObjectFiiiiiPSc(this, 0, 1, 0, -1, -1, 0);
	}

	if (worldParamA == 0x12) {
		DispCharaParts__8CGObjectFi(this, 0);
		self[0x50] = (self[0x50] & 0xEF) | 0x10;
	}

	if (useParticleTable != 0) {
		for (int i = 0; i < 3; i++) {
			if (i != 0 || *(short*)(self + 0x550) != 1) {
				int entryBase = Game.game.unkCFlatData0[2] + worldParamB * 0x48;
				unsigned short particleNo = *(unsigned short*)(entryBase + i * 2 + 0x14);

				if (particleNo != 0xFFFF) {
					float particleScale =
					    FLOAT_80331b50 * (float)(unsigned short)*(unsigned short*)(entryBase + 0x10) + FLOAT_80331b4c;
					putParticle__8CGPrgObjFiiP8CGObjectfi(
					    this, particleNo | 0x100, *(int*)(self + 0x554), this, particleScale, 0);
				}
			}
		}
	}

	if (worldParamA == 0xCB) {
		*(int*)(self + 0x1D4) = (int)(FLOAT_80331b54 - RandF__5CMathFf(FLOAT_80331b58, &Math));
		*(unsigned char*)(self + 0x9A) &= 0xFB;
	}

	self[0x54D] = (self[0x54D] & 0x7F) | 0x80;
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
	extern int DAT_8032ee90;
	unsigned char* self = (unsigned char*)this;

	*(int*)(self + 0x568) = *(int*)(self + 0x144);
	*(unsigned short*)(self + 0x560) = (unsigned short)((DAT_8032ee90 >> 3) & 1);
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
	unsigned char nodeFlags = *(unsigned char*)(self + 0x9A);
	unsigned int rotatedFlags = ((unsigned int)nodeFlags << 26) | ((unsigned int)nodeFlags >> 6);

	if ((int)rotatedFlags >= 0) {
		return;
	}

	void* charaHandle = *(void**)(self + 0xF8);
	bool hasModel = false;
	if (charaHandle != 0 && *(void**)((unsigned char*)charaHandle + 0x168) != 0) {
		hasModel = true;
	}

	if (!hasModel || *(int*)(self + 0x500) != 0xCB || *(float*)(self + 0x74) <= FLOAT_80331b20 ||
	    *(float*)(self + 0x4B0) == FLOAT_80331b20) {
		return;
	}

	SetTlut__5CFontFi(font, 7);

	int alphaInt = (int)(FLOAT_80331b30 * *(float*)(self + 0x4B0));
	GXColor textColor;
	__ct__6CColorFUcUcUcUc(&textColor, 0xFF, 0xFF, 0xFF, (unsigned char)alphaInt);
	SetColor__5CFontF8_GXColor(font, &textColor);

	const ItemObjFlatData* flatData = reinterpret_cast<const ItemObjFlatData*>(&Game.game.m_cFlatDataArr[1]);
	const char* name = flatData->table[2].index[*(int*)(self + 0x570)];
	int width = GetWidth__5CFontFPc(font, name);
	float depthScale = FLOAT_80331b18 / (*(float*)(self + 0x74) - FLOAT_80331b1c);
	float posZ = *(float*)(self + 0x70) * depthScale;
	float posY = -(FLOAT_80331b34 * *(float*)(self + 0x6C) * depthScale - FLOAT_80331b34);
	float posX = -(FLOAT_80331b3c * (float)width - (FLOAT_80331b38 * *(float*)(self + 0x68) * depthScale + FLOAT_80331b38));

	SetPosX__5CFontFf(posX, font);
	SetPosY__5CFontFf(posY - FLOAT_80331b40, font);
	SetPosZ__5CFontFf(posZ, font);
	Draw__5CFontFPc(font, name);
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
	for (unsigned char* itemObj = (unsigned char*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat); itemObj != 0;
	     itemObj = (unsigned char*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj)) {
		if ((*(unsigned int*)(itemObj + 0x60) & 0x10) != 0) {
			continue;
		}

		float local_78;
		float local_74;
		float local_70;
		float local_6c;
		float local_68;
		float local_64;
		float local_60;
		float local_5c;
		float local_58;
		float local_48;
		float local_44;
		float local_40;
		float local_3c;
		float local_38;
		float local_34;
		float local_30;
		float local_2c;
		float local_28;
		float local_24;

		local_6c = *(float*)(itemObj + 0x68);
		local_64 = *(float*)(itemObj + 0x70);
		local_68 = *(float*)(itemObj + 0x6c) + FLOAT_80331b1c;
		local_78 = FLOAT_80331b20;
		local_70 = FLOAT_80331b20;
		local_74 = FLOAT_80331b24;
		local_30 = FLOAT_80331b28;
		local_34 = FLOAT_80331b28;
		local_38 = FLOAT_80331b28;
		local_24 = FLOAT_80331b2c;
		local_28 = FLOAT_80331b2c;
		local_2c = FLOAT_80331b2c;
		local_48 = FLOAT_80331b20;
		local_44 = FLOAT_80331b24;
		local_40 = FLOAT_80331b20;
		local_3c = FLOAT_80331b20;
		local_60 = local_6c;
		local_5c = local_68;
		local_58 = local_64;
		if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &local_60, &local_78, *(unsigned int*)(itemObj + 0x1c4)) != 0 &&
		    DAT_8032ec90[0x47] == state) {
			*(float*)(itemObj + 0x108) = *(float*)(itemObj + 0x108) + jump;
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
	unsigned char* itemObj = (unsigned char*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat);

	while (itemObj != 0) {
		unsigned char stateFlags = itemObj[0x50];
		unsigned int rotated = (unsigned int)stateFlags >> 4;
		rotated |= (unsigned int)stateFlags << 0x1c;
		int isActive = (int)(rotated >> 0x1f);

		if (*(int*)(itemObj + 0x550) == 0 && isActive != 0) {
			itemObj[0x38] = (itemObj[0x38] & 0x7f) | 0x80;
		}

		itemObj = (unsigned char*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj);
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
	unsigned char* itemObj = (unsigned char*)FindGItemObjFirst__13CFlatRuntime2Fv(CFlat);

	while (itemObj != 0) {
		unsigned char stateFlags = itemObj[0x50];
		int isActive = (int)(((unsigned int)stateFlags << 0x1c) | ((unsigned int)stateFlags >> 4)) < 0;

		if (*(int*)(itemObj + 0x550) == 0 && isActive != 0) {
			if (show == 0) {
				*(unsigned int*)(itemObj + 0x60) |= 0x400000;
			} else {
				*(unsigned int*)(itemObj + 0x60) &= 0xffbfffff;
			}
		}

		itemObj = (unsigned char*)FindGItemObjNext__13CFlatRuntime2FP9CGItemObj(CFlat, itemObj);
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
