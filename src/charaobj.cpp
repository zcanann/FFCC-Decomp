#include "ffcc/charaobj.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <string.h>

extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	void*, int, int, int, int, void*, void*);
extern "C" void DeleteParticleSlot__13CFlatRuntime2Fii(void*, int);
extern "C" int GetFreeParticleSlot__13CFlatRuntime2Fv(void*);
extern "C" void EndParticleSlot__13CFlatRuntime2Fii(void*, int, int);
extern "C" int intToClass__13CFlatRuntime2Fi(void*, int);
extern "C" void IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(void*, int, void*);
extern "C" void pppEndPart__8CPartMngFi(void*, int);

extern unsigned char CFlat[];
extern CPartMng PartMng;
extern int DAT_8032ee68;
extern unsigned char DAT_8032ee6c;
extern float FLOAT_80331964;

/*
 * --INFO--
 * PAL Address: 0x8010b67c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::bonus(int, int, CGPrgObj*)
{
}

/*
 * --INFO--
 * PAL Address: 0x8010b680
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onFrameAlways()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010b684
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onFrameAlwaysAfter()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B688
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onDamaged(CGPrgObj*)
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B68C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPrgObj::onAttacked(CGPrgObj*)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void SAFE_CAST_WORK(CGObjWork*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80112C40
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onCreate()
{
	CGPrgObj::onCreate();

	if (DAT_8032ee6c == 0) {
		DAT_8032ee68 = 0;
		DAT_8032ee6c = 1;
	}

	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x54D) = DAT_8032ee68;
	DAT_8032ee68 += 1;

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	self[0x63C] &= 0x7F;
	self[0x640] &= 0x7F;
	self[0x648] &= 0x7F;
	self[0x650] &= 0x7F;
	self[0x658] &= 0x7F;
	*reinterpret_cast<int*>(self + 0x660) = 0;
	*reinterpret_cast<int*>(self + 0x664) = 0;
	*reinterpret_cast<int*>(self + 0x668) = 0;
	*reinterpret_cast<int*>(self + 0x684) = -1;
	*reinterpret_cast<int*>(self + 0x688) = 0;
	*reinterpret_cast<float*>(self + 0x690) = FLOAT_80331964;
	*reinterpret_cast<float*>(self + 0x694) = FLOAT_80331964;
	m_aStarGroupId = 0;
	*reinterpret_cast<int*>(self + 0x6A0) = 0;
	*reinterpret_cast<int*>(self + 0x6A8) = 0;
	memset(self + 0x6AC, 0, 0xC);

	for (int i = 0; i < 0x16; i++) {
		*reinterpret_cast<int*>(self + 0x564 + (i * 4)) = GetFreeParticleSlot__13CFlatRuntime2Fv(CFlat);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80112C20
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onDestroy()
{
	CGPrgObj::onDestroy();
}

/*
 * --INFO--
 * PAL Address: 0x80112BC4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::ClearAllSta()
{
	for (int i = 0; i < 0x27; i++) {
		setSta(i, 0);
	}
	m_displayFlags |= 2;
}

/*
 * --INFO--
 * PAL Address: 0x80112B1C
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onChangeStat(int state)
{
	if (state == 2 || state == 6) {
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6A8) = 0;
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x698) = 0;
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x69C) = -1;
	} else if (state == 9) {
		for (int i = 0; i < 0x27; i++) {
			setSta(i, 0);
		}
		m_displayFlags |= 2;
	}

	*(reinterpret_cast<unsigned char*>(this) + 0x63C) &= 0x7F;
}

/*
 * --INFO--
 * PAL Address: 0x801129D0
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onCancelStat(int)
{
	int state = m_lastStateId;
	int* slots = reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x564);

	if (state == 6) {
		for (int i = 0; i < 0x16; i++) {
			if (((1U << i) & 0x138U) != 0) {
				EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 0);
			}
		}
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x684) = -1;
	} else if (state == 2) {
		for (int i = 0; i < 0x16; i++) {
			if (((1U << i) & 0x18U) != 0) {
				EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 0);
			}
		}
	} else if (state == 0x12) {
		for (int i = 0; i < 0x16; i++) {
			if (((1U << i) & 1U) != 0) {
				EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 0);
			}
		}
	}

	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x660) = 0;
	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x668) = 0;

	typedef void (*VCall90)(void*, int, int, int);
	VCall90 fn = *reinterpret_cast<VCall90*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x48) + 0x90);
	fn(this, 0, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80112618
 * PAL Size: 952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onFramePostCalc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801121E8
 * PAL Size: 1072b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onFramePreCalc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801120C0
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onAlphaUpdate()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80112058
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::endPSlotBit(int slotMask)
{
	int* slots = reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x564);
	for (int i = 0; i < 0x16; i++) {
		if ((static_cast<unsigned int>(slotMask) & (1U << i)) != 0) {
			EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80111FF0
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::deletePSlotBit(int slotMask)
{
	int* slots = (int*)((char*)this + 0x564);
	for (int i = 0; i < 0x16; i++) {
		if (((unsigned int)slotMask & (1U << i)) != 0) {
			DeleteParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i]);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80111920
 * PAL Size: 1744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onFrameStat()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8011191C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onAnimPoint(int, int)
{
}

/*
 * --INFO--
 * PAL Address: 0x801118E4
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::resetIgnoreHit()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	self[0x640] &= 0x7F;
	self[0x648] &= 0x7F;
	self[0x650] &= 0x7F;
	self[0x658] &= 0x7F;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::decIgnoreHit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80111858
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::damageDelete()
{
	int* slots = (int*)((char*)this + 0x564);

	Sound.StopSe3DGroup(*(short*)((char*)this + 0x30));
	for (int i = 0; i < 0x16; i++) {
		if (((1U << i) & 0x3bU) != 0) {
			DeleteParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i]);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80111678
 * PAL Size: 480b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onHit(int, CGObject*, int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80111508
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onHitParticle(int effectIndex, int, int, int colliderIndex, Vec* hitPos, PPPIFPARAM* hitParam)
{
	typedef unsigned int (*VCall0C)(void*);
	typedef void (*VCall80)(void*, void*, int, int, int, Vec*);

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	VCall0C cidFn = *reinterpret_cast<VCall0C*>(*reinterpret_cast<int*>(self + 0x48) + 0x0C);
	unsigned int cid = cidFn(this);

	bool skip = false;
	if ((cid & 0x6D) == 0x6D && Game.game.m_gameWork.m_menuStageMode != 0 && Game.game.m_gameWork.m_bossArtifactStageIndex <= 0xE) {
		cid = cidFn(this);
		if ((cid & 0x6D) == 0x6D && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) != 0) {
			skip = true;
		}
	}

	if (skip) {
		return;
	}

	int particleIndex = hitParam->m_particleIndex;
	CGPrgObj* sourceObj = 0;
	if (hitParam->m_classId != 0) {
		sourceObj = reinterpret_cast<CGPrgObj*>(intToClass__13CFlatRuntime2Fi(CFlat, static_cast<int>(hitParam->m_classId)));
	}

	if (sourceObj != 0) {
		unsigned int sourceCid = cidFn(sourceObj);
		if ((sourceCid & 0xD) == 0xD) {
			VCall80 hitFn = *reinterpret_cast<VCall80*>(*reinterpret_cast<int*>(self + 0x48) + 0x80);
			hitFn(this, sourceObj, particleIndex, -1, colliderIndex, hitPos);
		}
	}

	IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(CFlat, static_cast<short>(effectIndex), this);
	if ((*reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + (particleIndex * 0x48) + 0xC) & 0x100) != 0) {
		pppEndPart__8CPartMngFi(&PartMng, effectIndex);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80111500
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGCharaObj::getReplaceStat(int state)
{
	return state;
}

/*
 * --INFO--
 * PAL Address: 0x8011134C
 * PAL Size: 436b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::putHitParticleFromItem(CGPrgObj*, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801105D0
 * PAL Size: 3452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::setSta(int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010FD54
 * PAL Size: 2172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::effective(int, int, CGPrgObj*, int&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010F8D8
 * PAL Size: 1148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::calcSta(int, int, CGObject*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010F5BC
 * PAL Size: 796b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::addHp(int, CGPrgObj*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010F248
 * PAL Size: 884b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::calcRegist(int, int, int&, int&, int&, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010D700
 * PAL Size: 6984b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onDamage(CGPrgObj*, int, int, int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010CAF0
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::getItemPdt(int, int, int&, int&, int&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010CBC8
 * PAL Size: 2872b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::putParticleFromItem(int, int, int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statShield()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void la(CGObject*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010C704
 * PAL Size: 1000b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::statAttack()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statDie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statMagic()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statKizetsu()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010C700
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onStatMagic()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statDamage()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statButtobi()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010C6B4
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onChangePrg(int arg)
{
	if (arg == 0) {
		changeStat(0, 0, 0);
		CancelAnim(0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8010C2F0
 * PAL Size: 964b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::calcCastTime(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010C1A8
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onDrawDebug(CFont*, float, float&, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::addSe(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::seDamageDelete()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010C0C4
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::StaticFrame()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010B9B8
 * PAL Size: 1804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::combi2()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010b8b8
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::sendCombiToScript(CGCharaObj* target, int scriptArg, int)
{
	int entry = 0;
	CGame* linkCursor = &Game.game;
	int linkCount = *reinterpret_cast<int*>(&Game.game.m_gameWork.m_linkTable[3][0][0]);

	while (entry < linkCount) {
		int linkHead = *reinterpret_cast<int*>(&linkCursor->m_gameWork.m_linkTable[3][0][0]);
		CGPrgObj* obj = *reinterpret_cast<CGPrgObj**>(linkHead + 4);
		bool skip = (obj == 0);

		if (!skip) {
			if (Game.game.m_gameWork.m_menuStageMode != 0 && Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
				(obj->GetCID() & 0x6D) == 0x6D &&
				*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(obj->m_scriptHandle) + 0x3B4) != 0) {
				skip = true;
			}

			if (obj->m_lastStateId == 6 || obj->m_lastStateId == 2) {
				skip = true;
			}
		}

		if (!skip) {
			break;
		}

		linkCursor = reinterpret_cast<CGame*>(reinterpret_cast<unsigned char*>(linkCursor) + 4);
		entry++;
	}

	if (entry == linkCount) {
		int stackArgs[2];
		stackArgs[0] = reinterpret_cast<int>(target);
		stackArgs[1] = scriptArg;
		SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
			CFlat, reinterpret_cast<int>(this), 2, 0x17, 2, stackArgs, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::scCheckItem(CCombi2Set*, CGCharaObj*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::scCheckTime(CCombi2Set*, CGCharaObj*, CGCharaObj*, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010B690
 * PAL Size: 552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::searchCombi(int, CGPartyObj **, int&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8010B674
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::enableAttackCol(int, int, int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B670
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onStatShield()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B66C
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onStatAttack(int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B668
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onStatDie()
{
}

/*
 * --INFO--
 * PAL Address: 0x8010B660
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGCharaObj::GetCID()
{
	return 0x2D;
}

/*
 * --INFO--
 * PAL Address: 0x8010B678
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::enableDamageCol(int)
{
}
