#include "ffcc/itemobj.h"
#include "ffcc/math.h"
#include "ffcc/prgobj.h"
#include "ffcc/p_game.h"
#include "ffcc/vector.h"

#include <string.h>

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
extern "C" float RandF__5CMathFf(float, CMath*);
extern "C" unsigned int getNumFreeObject__13CFlatRuntime2Fi(void*, int);
extern unsigned char CFlat[];
extern CMath Math;
extern float FLOAT_80331b20;
extern float FLOAT_80331b4c;
extern float FLOAT_80331b50;
extern float FLOAT_80331b54;
extern float FLOAT_80331b58;
extern float FLOAT_80331b8c;
extern float FLOAT_80331b90;
extern char DAT_80331b7c[];
extern char DAT_80331b84[];

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
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onFrameStat()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::DeleteOld(int, int, CFlatRuntime::CObject*, CFlatRuntime::CObject*)
{
	// TODO
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
	unsigned int freeObjects = getNumFreeObject__13CFlatRuntime2Fi(CFlat, 5);
	return (-freeObjects & ~freeObjects) >> 31;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::CreateFromScript(int, int, int, CGObject*, float, CGItemObj::CCFS*)
{
	// TODO
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::DrawOmoideName(CFont*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::ItemJump(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::DeleteAllFieldItem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGItemObj::DispAllFieldItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGItemObj::GetCID()
{
	return 0;
}
