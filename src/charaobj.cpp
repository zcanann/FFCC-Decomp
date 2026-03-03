#include "ffcc/charaobj.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include <math.h>
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
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void SAFE_CAST_WORK(CGObjWork*)
{
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
	m_comboFrame = 0;
	m_comboFramePrev = 0;
	m_comboState = 0;
	m_damageParticle = -1;
	m_unk688 = 0;
	m_pushScale = FLOAT_80331964;
	m_alpha = FLOAT_80331964;
	m_aStarGroupId = 0;
	m_stateTick = 0;
	m_castTimeTick = 0;
	memset(m_unk6AC, 0, sizeof(m_unk6AC));

	for (int i = 0; i < 0x16; i++) {
		m_particleSlots[i] = GetFreeParticleSlot__13CFlatRuntime2Fv(CFlat);
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
		m_castTimeTick = 0;
		m_stateResetCounter = 0;
		m_stateResetLimit = -1;
	} else if (state == 9) {
		for (int i = 0; i < 0x27; i++) {
			setSta(i, 0);
		}
		m_displayFlags |= 2;
	}

	m_ignoreHit[0].m_flag &= 0x7F;
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
	int* slots = m_particleSlots;

	if (state == 6) {
		for (int i = 0; i < 0x16; i++) {
			if (((1U << i) & 0x138U) != 0) {
				EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 0);
			}
		}
		m_damageParticle = -1;
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

	m_comboFrame = 0;
	m_comboState = 0;

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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	void** script = m_scriptHandle;
	if (script != 0) {
		if (*reinterpret_cast<short*>(self + 0x42) != 0) {
			int healTick = m_stateTick;
			unsigned short tickDiv = *reinterpret_cast<unsigned short*>(Game.game.unk_flat3_field_8_0xc7dc + 0x3A);
			if (healTick != 0 && tickDiv != 0 && (healTick % static_cast<int>(tickDiv)) == 0) {
				playSe3D(0x19, 0x32, 0x96, 0, 0);
				addHp(-1, 0);
			}
		}

		for (int i = 0; i < 0x27; i++) {
			short v = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(script) + 0x3E + (i * 2));
			setSta(i, static_cast<int>(v) - 1);
			if (i == 2 && v > 1) {
				m_stateTick += 1;
			}
		}

		if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(script) + 0x3E) == 0 &&
			*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(script) + 0x14) == 0 &&
			*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(script) + 0x11) == 0) {
			m_displayFlags |= 2;
		} else {
			m_displayFlags &= ~2;
			m_ignoreHit[0].m_flag &= 0x7F;
		}
	}

	m_flags = static_cast<unsigned char>(m_flags + 1);

	decIgnoreHit();
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);

	if (Game.game.unk_flat3_0xc7d0 != 0) {
		PSVECSubtract(reinterpret_cast<Vec*>(Game.game.unk_flat3_0xc7d0 + 0x15C), &m_worldPosition,
			&m_targetDelta);
		m_targetDist = PSVECMag(&m_targetDelta);
	}

	for (int i = 0; i < 4; i++) {
		int partyObj = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Game.game.m_partyObjArr[0]) + (i * 4));
		float* dist = &m_partyDistance[i];
		float* ang = &m_partyAngle[i];
		int* rank = &m_partyRank[i];
		*rank = 0;
		if (partyObj == 0) {
			*dist = 0.0f;
			*ang = 0.0f;
		} else {
			PSVECSubtract(reinterpret_cast<Vec*>(partyObj + 0x15C), &m_worldPosition,
				&m_partyDelta[i]);
			*dist = PSVECMag(&m_partyDelta[i]);
		}
	}

	m_pushScale = 1.0f;

	unsigned int push = 0;
	switch (m_lastStateId) {
		case 1: case 2: case 4: case 6: case 7: case 8: case 9:
		case 10: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF:
		case 0x12: case 0x13: case 0x16: case 0x17: case 0x19:
		case 0x1B: case 0x22:
			push = 0x19;
			break;
		default:
			break;
	}
	m_pushParamB = static_cast<unsigned char>(push > 0x19 ? 0x19 : push);

	m_lastBgGroupCopy = m_lastBgGroup;
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	float alpha = m_alpha;

	if (m_scriptHandle != 0 && *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		alpha += sinf(static_cast<float>(m_flags) * 0.1f) * 0.05f;
	}

	if (alpha < 0.0f) {
		alpha = 0.0f;
	} else if (alpha > 1.0f) {
		alpha = 1.0f;
	}

	m_alpha = alpha;
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
	int* slots = m_particleSlots;
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
	int* slots = m_particleSlots;
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
	switch (m_lastStateId) {
		case 0:
			break;
		case 1:
		case 3:
		case 4:
		case 5:
		case 7:
		case 8:
		case 0xA:
			statAttack();
			break;
		case 2:
			statButtobi();
			break;
		case 6:
			statDamage();
			break;
		case 9:
			statDie();
			break;
		case 0xC:
		case 0xD:
			statMagic();
			break;
		case 0xE:
			statShield();
			break;
		default:
			statKizetsu();
			break;
	}
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
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::decIgnoreHit()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	for (int i = 0; i < 4; i++) {
		IgnoreHitSlot& slot = m_ignoreHit[i];
		if ((slot.m_flag & 0x80) != 0 && slot.m_timer != 0) {
			slot.m_timer = static_cast<unsigned short>(slot.m_timer - 1);
			if (slot.m_timer == 0) {
				slot.m_flag &= 0x7F;
			}
		}
	}
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
	int* slots = m_particleSlots;

	Sound.StopSe3DGroup(m_particleId);
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
void CGCharaObj::onHit(int hitArg, CGObject* sourceObj, int hitType, Vec* hitPos)
{
	typedef unsigned int (*VCall0C)(void*);
	typedef void (*VCall80)(void*, void*, int, int, int, Vec*);

	if (sourceObj == 0) {
		return;
	}

	VCall0C cidFn = *reinterpret_cast<VCall0C*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0x48) + 0x0C);
	unsigned int sourceCid = cidFn(sourceObj);
	if ((sourceCid & 0x6D) == 0x6D && Game.game.m_gameWork.m_menuStageMode != 0 && Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		sourceCid = cidFn(sourceObj);
		if ((sourceCid & 0x6D) == 0x6D && sourceObj->m_scriptHandle != 0 && sourceObj->m_scriptHandle[0xED] != 0) {
			return;
		}
	}

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int slot = -1;
	for (int i = 0; i < 4; i++) {
		IgnoreHitSlot& slotData = m_ignoreHit[i];
		if ((slotData.m_flag & 0x80) == 0) {
			slot = i;
			slotData.m_flag = static_cast<unsigned char>((slotData.m_flag & 0x7F) | 0x80);
			slotData.m_source = sourceObj;

			unsigned int particleIndex = static_cast<unsigned int>(m_itemId);
			unsigned short particleLife =
				*reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + (particleIndex * 0x48) + 0xE);
			slotData.m_timer = (particleLife >= 3) ? 0x1E : 0;
			break;
		}
		if (slotData.m_source == sourceObj) {
			return;
		}
	}

	if (slot < 0) {
		return;
	}

	if ((sourceObj->m_objectFlags & 0x100) != 0) {
		changeStat(3, 0, 0);
	}

	sourceCid = cidFn(sourceObj);
	if ((sourceCid & 0x2D) == 0x2D) {
		VCall80 onHitVCall = *reinterpret_cast<VCall80*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0x48) + 0x80);
		onHitVCall(sourceObj, this, m_itemId, hitArg, hitType, hitPos);
	}
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
	int item = 0;
	int p0 = 0;
	int p1 = 0;
	getItemPdt(0, 0, item, p0, p1);
	putParticleFromItem(item, p0, p1, &m_worldPosition);
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
void CGCharaObj::setSta(int staIndex, int value)
{
	if (m_scriptHandle == 0) {
		return;
	}
	if (staIndex < 0 || staIndex >= 0x27) {
		return;
	}
	if (value < 0) {
		value = 0;
	}
	*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E + (staIndex * 2)) =
		static_cast<short>(value);
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
void CGCharaObj::effective(int staIndex, int amount, CGPrgObj*, int& outValue)
{
	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	if (script == 0) {
		outValue = 0;
		return;
	}

	CGObject* source = reinterpret_cast<CGObject*>(this);
	int next = 0;

	switch (staIndex) {
		case 0:
			if (*reinterpret_cast<short*>(script + 0x10) == 0) {
				calcSta(0, amount, source);
				setSta(4, 0);
				Sound.StopSe3DGroup(m_particleId);
				damageDelete();
				changeStat(0, 0, 0);
			} else {
				setSta(0, 0);
				setSta(1, 0);
				next = 0;
			}
			break;
		case 1:
			if (*reinterpret_cast<short*>(script + 0x3E) == 0) {
				calcSta(1, amount, source);
				setSta(4, 0);
			} else {
				setSta(0, 0);
				setSta(1, 0);
				next = 0;
			}
			break;
		case 2:
			calcSta(2, amount, source);
			break;
		case 3:
			setSta(1, 0);
			setSta(0, 0);
			setSta(4, 0);
			setSta(9, 0);
			setSta(7, 0);
			setSta(8, 0);
			calcSta(3, amount, source);
			putHitParticleFromItem(0, amount);
			Sound.StopSe3DGroup(m_particleId);
			damageDelete();
			changeStat(0, 0, 0);
			next = 0;
			break;
		case 4:
			calcSta(4, amount, source);
			setSta(0, 0);
			setSta(1, 0);
			changeStat(10, 0, 0);
			break;
		case 6:
			calcSta(6, amount, source);
			putHitParticleFromItem(0, amount);
			next = 0;
			break;
		case 7:
			if (*reinterpret_cast<short*>(script + 0x4E) == 0) {
				calcSta(7, amount, source);
				putHitParticleFromItem(0, amount);
			} else {
				setSta(7, 0);
				setSta(8, 0);
			}
			next = 0;
			break;
		case 8:
			if (*reinterpret_cast<short*>(script + 0x13) == 0) {
				calcSta(8, amount, source);
				putHitParticleFromItem(0, amount);
			} else {
				setSta(7, 0);
				setSta(8, 0);
			}
			next = 0;
			break;
		case 9:
			setSta(7, 0);
			setSta(8, 0);
			calcSta(9, amount, source);
			putHitParticleFromItem(0, amount);
			Sound.StopSe3DGroup(m_particleId);
			damageDelete();
			changeStat(0, 0, 0);
			next = 0;
			break;
		case 0x1C:
			calcSta(0x1C, amount, source);
			break;
		case 0x25:
			if (*reinterpret_cast<short*>(script + 0x3E) != 0) {
				setSta(0, 0);
			}
			changeStat(0x19, 0, 0);
			break;
		case 100:
			if (Game.game.m_gameWork.m_gameOverFlag == 0) {
				if (amount == 0x225) {
					addHp(*reinterpret_cast<unsigned short*>(script + 0x1A), 0);
				} else {
					addHp(8, 0);
				}
				changeStat(0x22, 0, 0);
				putHitParticleFromItem(0, amount);
			}
			next = 0;
			break;
		case 0x66:
			addHp(*reinterpret_cast<unsigned short*>(script + 0x1A), 0);
			putHitParticleFromItem(0, amount);
			next = 0;
			break;
		case 0x68:
			if (*reinterpret_cast<short*>(script + 0x3E) != 0) {
				setSta(0, 0);
			}
			changeStat(4, 0, 0);
			break;
		case 0x69:
			for (int i = 0; i < 0x27; i++) {
				setSta(i, 0);
			}
			m_displayFlags |= 2;
			putHitParticleFromItem(0, amount);
			break;
		case 0x6A:
			calcSta(4, amount, source);
			setSta(0, 0);
			setSta(1, 0);
			changeStat(10, 0, 0);
			break;
		case 0x6B:
			if (*reinterpret_cast<short*>(script + 0x46) != 0) {
				setSta(4, 0);
			}
			if (*reinterpret_cast<short*>(script + 0x3E) == 0 &&
				*reinterpret_cast<short*>(script + 0x14) == 0 &&
				*reinterpret_cast<short*>(script + 0x11) == 0) {
				changeStat(0x1A, 0, 0);
			}
			break;
		default:
			break;
	}

	if (staIndex >= 0 && staIndex < 0x27) {
		next = *reinterpret_cast<short*>(script + 0x3E + (staIndex * 2));
	}
	outValue = next;
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
void CGCharaObj::calcSta(int staIndex, int amount, CGObject* source)
{
	if (m_scriptHandle == 0 || source == 0) {
		return;
	}

	short* staPtr = reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E + (staIndex * 2));
	if ((staIndex == 0 || staIndex == 4) && *staPtr != 0) {
		return;
	}

	unsigned int base = 0;
	unsigned char* gameFlat = reinterpret_cast<unsigned char*>(Game.game.unk_flat3_field_8_0xc7dc);
	switch (staIndex) {
		case 0: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x10); break;
		case 1: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x0E); break;
		case 3: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x12); break;
		case 4: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x22); break;
		case 5: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x20); break;
		case 6: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x1E); break;
		case 7: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x18); break;
		case 8: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x14); break;
		case 9: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x16); break;
		case 0x0A: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x1A); break;
		case 0x1C: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x1C); break;
		case 0x6A: base = *reinterpret_cast<unsigned short*>(gameFlat + 0x24); break;
		default: break;
	}

	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.game.unkCFlatData0[2]) + (amount * 0x48);
	short itemType = (amount < 0x1F5) ? 1 : *reinterpret_cast<short*>(itemData + 2);

	unsigned int sourceCid = source->GetCID();
	unsigned int power = 0;
	if ((sourceCid & 0x2D) == 0x2D) {
		CGObject* statSource = source;
		if (Game.game.m_gameWork.m_menuStageMode != 0 && Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
			(sourceCid & 0x6D) == 0x6D &&
			source->m_scriptHandle != 0 && source->m_scriptHandle[0xED] != 0) {
			statSource = reinterpret_cast<CGObject*>(Game.game.m_partyObjArr[0]);
		}
		if (statSource != 0 && statSource->m_scriptHandle != 0 && statSource->m_scriptHandle[9] != 0) {
			power = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(statSource->m_scriptHandle[9]) + 0x198);
		}
	} else {
		power = *reinterpret_cast<unsigned short*>(itemData + 0x2E);
	}

	if ((sourceCid & 0xAD) == 0xAD) {
		int stageLevel = 0;
		if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			stageLevel = Game.game.m_gameWork.m_bossArtifactStageTable[Game.game.m_gameWork.m_bossArtifactStageIndex];
			if (stageLevel > 2) {
				stageLevel = 2;
			}
		}
		if (stageLevel > 0) {
			power += *reinterpret_cast<unsigned short*>(gameFlat + 0x5C + (stageLevel * 2));
		}
	}

	int affinity = 0;
	if ((sourceCid & 0x6D) == 0x6D && (itemType == 1 || itemType == 9) && source->m_scriptHandle != 0) {
		affinity += static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(source->m_scriptHandle) + 0xBDA));
	}
	if ((GetCID() & 0x6D) == 0x6D && (itemType == 8 || itemType == 9)) {
		affinity -= static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBDB));
	}

	int next = affinity + static_cast<int>(base * power);
	if (next < 0) {
		next = 0;
	}
	setSta(staIndex, next);
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
void CGCharaObj::addHp(int delta, CGPrgObj*)
{
	if (m_scriptHandle == 0) {
		return;
	}

	short* hp = reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x42);
	unsigned short maxHp = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A);
	int next = static_cast<int>(*hp);

	if (delta > 0) {
		next += delta;
		if (next > static_cast<int>(maxHp)) {
			next = static_cast<int>(maxHp);
		}
	} else {
		next += delta;
		if ((GetCID() & 0x6D) == 0x6D && next < 1) {
			next = 1;
		}
	}

	if (next < 0) {
		next = 0;
	}

	*hp = static_cast<short>(next);
	m_worldParam = 1.0f;

	if (next == 0) {
		for (int i = 0; i < 0x27; i++) {
			setSta(i, 0);
		}
		m_displayFlags |= 2;
		changeStat(9, 0, 0);
	}
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
void CGCharaObj::calcRegist(int staIndex, int itemId, int& outA, int& outB, int& outC, int forceNormal)
{
	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.game.unkCFlatData0[2]) + (itemId * 0x48);

	int isNormal = 0;
	if ((*reinterpret_cast<unsigned short*>(itemData + 0x32) & 1) != 0 || forceNormal != 0) {
		isNormal = 1;
	}

	outA = 3;
	switch (staIndex) {
		case 0: outA = *reinterpret_cast<unsigned short*>(script + 0x2C); break;
		case 1: outA = *reinterpret_cast<unsigned short*>(script + 0x2A); break;
		case 2: outA = *reinterpret_cast<unsigned short*>(script + 0x38); break;
		case 3: outA = *reinterpret_cast<unsigned short*>(script + 0x3C); break;
		case 4: outA = *reinterpret_cast<unsigned short*>(script + 0x2E); break;
		case 6: outA = *reinterpret_cast<unsigned short*>(script + 0x3A); break;
		case 8: outA = *reinterpret_cast<unsigned short*>(script + 0x30); break;
		case 9: outA = *reinterpret_cast<unsigned short*>(script + 0x32); break;
		case 0x0B: outA = *reinterpret_cast<unsigned short*>(script + 0x34); break;
		case 0x1C: outA = *reinterpret_cast<unsigned short*>(script + 0x36); break;
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x69:
		case 0x6A:
		case 0x6B:
		case 100:
			outA = *reinterpret_cast<unsigned short*>(script + 0x28);
			break;
		default:
			break;
	}

	if ((GetCID() & 0xAD) == 0xAD && m_scriptHandle != 0 && m_scriptHandle[9] != 0) {
		unsigned char* monData = reinterpret_cast<unsigned char*>(m_scriptHandle[9]);
		if (*reinterpret_cast<short*>(script + 0x76) == 0 && (*reinterpret_cast<unsigned short*>(monData + 0xFE) & 1) != 0 &&
			staIndex != 0x1C && outA < 2) {
			outA = 2;
		}
		if ((*reinterpret_cast<unsigned short*>(monData + 0xFE) & 4) != 0 && *reinterpret_cast<short*>(script + 0x52) == 0 &&
			outA < 2) {
			outA = 2;
		}
	}

	if (*reinterpret_cast<short*>(script + 0x74) != 0) {
		outA = 3;
	}

	if (outA == 1) {
		outB = (isNormal == 0) ? 1 : 0;
	} else if (outA == 0) {
		outB = 1;
	} else {
		outB = 0;
	}
	outC = ((outA ^ 3) >> 1);
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
	typedef unsigned int (*VCall0C)(void*);

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (m_scriptHandle == 0) {
		damageDelete();
		changeStat(6, 0, 0);
		return;
	}

	int itemId = m_itemId;
	int itemOffset = itemId * 0x48;
	unsigned short staType = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemOffset + 8);

	VCall0C cidFn = *reinterpret_cast<VCall0C*>(*reinterpret_cast<int*>(self + 0x48) + 0x0C);
	unsigned int cid = cidFn(this);
	if ((cid & 0x6D) == 0x6D && *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x12) != 0) {
		return;
	}

	if ((m_weaponNodeFlags & 0x80) == 0) {
		return;
	}

	int regist = 0;
	int blocked = 0;
	int special = 0;
	calcRegist(staType, itemId, regist, blocked, special, 0);

	if (regist == 3) {
		if (staType == 0 || staType == 1 || staType == 3 || staType == 4 || staType == 6 || staType == 8 ||
			staType == 9 || staType == 0x1C) {
			putParticle(0x201, 0, static_cast<Vec*>(0), m_attackColRadius, 0x65);
		} else if (staType == 0x24 || staType == 0x25 || staType == 0x69 || staType == 0x6A) {
			putParticle(0x200, 0, static_cast<Vec*>(0), m_attackColRadius, 0x1D);
		}
	}

	int outValue = 0;
	effective(static_cast<int>(staType), itemId, this, outValue);

	if (blocked != 0) {
		changeStat(6, 0, 0);
		return;
	}

	if (outValue == 0) {
		damageDelete();
		changeStat(6, 0, 0);
	}
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
void CGCharaObj::getItemPdt(int itemId, int level, int& outEffect, int& outArg0, int& outArg1)
{
	outEffect = m_itemId;
	outArg0 = 1;
	outArg1 = 0;

	CCharaPcs::CHandle* model = m_charaModelHandle;
	if (model != 0 && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(model) + 0x168) != 0) {
		unsigned char* motion = reinterpret_cast<unsigned char*>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(model) + 0x168));
		if (*reinterpret_cast<int*>(motion + 0xD0) != 0) {
			unsigned int period = static_cast<unsigned int>(1.0f + (*reinterpret_cast<float*>(motion + 0xC0) -
				*reinterpret_cast<float*>(motion + 0xBC)));
			if (period == 0) {
				period = 1;
			}
			unsigned int frame = static_cast<unsigned int>(m_turnSpeed);
			if (m_radiusCtrl.x >= 1.0f) {
				outArg0 = (period <= frame) ? 1 : 0;
			} else {
				outArg0 = ((frame % period) == 0) ? 1 : 0;
			}
		}
	}

	if (itemId >= 0) {
		outArg1 = level;
	}
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
void CGCharaObj::putParticleFromItem(int effectId, int effectArg0, int effectArg1, Vec* pos)
{
	if (pos == 0) {
		pos = &m_worldPosition;
	}
	putParticle(effectId, effectArg0, pos, 1.0f, effectArg1);
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::statShield()
{
	onStatShield();
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void la(CGObject*)
{
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
	typedef unsigned int (*VCall0C)(void*);
	typedef void (*VCall88)(void*, int);
	typedef void (*VCall90)(void*, int, int, int);

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	VCall0C cidFn = *reinterpret_cast<VCall0C*>(*reinterpret_cast<int*>(self + 0x48) + 0x0C);
	unsigned int cid = cidFn(this);

	if ((cid & 0xAD) == 0xAD && m_subState == 0) {
		void* animPoint = m_scriptHandle != 0 ? m_scriptHandle[4] : 0;
		if (animPoint == reinterpret_cast<void*>(0x88) || animPoint == reinterpret_cast<void*>(0x87)) {
			m_subState = 1;
			m_stateFrame = 0;
		}
	}

	VCall88 vcall88 = *reinterpret_cast<VCall88*>(*reinterpret_cast<int*>(self + 0x48) + 0x88);
	vcall88(this, 0);

	if (m_stateFrame == 0) {
		m_ignoreHit[0].m_flag &= 0x7F;
		m_ignoreHit[1].m_flag &= 0x7F;
		m_ignoreHit[2].m_flag &= 0x7F;
		m_ignoreHit[3].m_flag &= 0x7F;

		int pdt = m_itemId;
		int dataNo = m_particleSlots[0];
		putParticleFromItem(pdt, 0, dataNo, 0);
		putParticleFromItem(pdt, 1, dataNo, 0);
		putParticleFromItem(pdt, 2, dataNo, 0);
		putParticleFromItem(pdt, 3, dataNo, 0);
		reqAnim(m_attackAnimId, 0, 0);
	}

	VCall90 vcall90 = *reinterpret_cast<VCall90*>(*reinterpret_cast<int*>(self + 0x48) + 0x90);
	if (m_stateFrame == static_cast<unsigned int>(m_castFrameStart)) {
		vcall90(this, 1, 0, 0);
	}
	if (m_stateFrame == static_cast<unsigned int>(m_castFrameEnd)) {
		vcall90(this, 0, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::statDie()
{
	onStatDie();
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::statMagic()
{
	onStatMagic();
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::statKizetsu()
{
	setSta(9, 1);
	resetIgnoreHit();
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
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::statDamage()
{
	setSta(6, 1);
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::statButtobi()
{
	setSta(2, 1);
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	m_castTimeTick += 1;

	if (m_scriptHandle == 0) {
		return;
	}

	int itemId = m_itemId;
	int itemOffset = itemId * 0x48;
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.game.unkCFlatData0[2]) + itemOffset;

	unsigned int baseCast = *reinterpret_cast<unsigned short*>(itemData + 0x2E);
	unsigned short itemType = *reinterpret_cast<unsigned short*>(itemData + 0xE);
	unsigned int cast = baseCast;

	if (itemType == 2) {
		unsigned int cid = GetCID();
		if ((cid & 0xAD) == 0xAD && Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			int stage = Game.game.m_gameWork.m_bossArtifactStageTable[Game.game.m_gameWork.m_bossArtifactStageIndex];
			if (stage > 2) {
				stage = 2;
			}
			if (stage > 0) {
				unsigned short bonus = *reinterpret_cast<unsigned short*>(Game.game.unk_flat3_field_8_0xc7dc + 0x58 + (stage * 2));
				if (cast > bonus) {
					cast -= bonus;
				} else {
					cast = 0;
				}
			}
		}
	}

	m_castFrameStart = static_cast<int>(cast);
	m_castFrameEnd = static_cast<int>(cast) + 1;
	m_castFrameCurrent = m_castFrameEnd;
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
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::addSe(int)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int particle = m_itemId;
	unsigned short se = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + (particle * 0x48) + 0x38);
	if (se == 0 || se == 0xFFFF) {
		return;
	}
	int seNo = (se & 0xFF) + ((static_cast<int>(se) >> 8) * 1000);
	playSe3D(seNo, 0x32, 0x96, 0, 0);
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::seDamageDelete()
{
	Sound.StopSe3DGroup(m_particleId);
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
	onAlphaUpdate();
	onFramePreCalc();
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
	CGPartyObj* candidates[4];
	int candidateCount = 0;
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party == 0) {
			continue;
		}
		int state = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party) + 0x520);
		int subState = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party) + 0x52C);
		if ((state == 6 || state == 2) && subState == 1) {
			candidates[candidateCount++] = party;
		}
	}

	if (candidateCount == 0) {
		return;
	}

	int fallback = 0;
	int comboIndex = searchCombi(candidateCount, candidates, fallback);
	if (comboIndex < 0) {
		for (int i = 0; i < candidateCount; i++) {
			*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(candidates[i]) + 0x118) = 0.0f;
			*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(candidates[i]) + 0x110) = 0.0f;
			reinterpret_cast<CGPrgObj*>(candidates[i])->addSubStat();
		}
		return;
	}

	sendCombiToScript(this, comboIndex, fallback);
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
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::scCheckItem(CCombi2Set*, CGCharaObj*, int)
{
}

/*
 * --INFO--
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::scCheckTime(CCombi2Set*, CGCharaObj*, CGCharaObj*, int)
{
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
int CGCharaObj::searchCombi(int count, CGPartyObj** partyList, int& outFallback)
{
	int found = -1;
	outFallback = 0;

	unsigned short* combiCursor = reinterpret_cast<unsigned short*>(Game.game.unk_flat3_field_1C_0xc7d8);
	for (int combiIndex = 0; combiIndex < Game.game.unk_flat3_count_0xc7d4; combiIndex++, combiCursor += 0xD) {
		int reqCount = 0;
		if (combiCursor[0] != 0) {
			reqCount = 1;
			if (combiCursor[3] != 0) {
				reqCount = 2;
				if (combiCursor[6] != 0) {
					reqCount = 3;
					if (combiCursor[9] != 0) {
						reqCount = 4;
					}
				}
			}
		}

		if (count < reqCount) {
			return found;
		}

		bool matched = true;
		CGCharaObj* baseParty = reinterpret_cast<CGCharaObj*>(partyList[0]);
		for (int slot = 0; slot < reqCount; slot++) {
			CGPartyObj* obj = partyList[slot];
			CGCharaObj* partyObj = reinterpret_cast<CGCharaObj*>(obj);
			if (obj == 0 || partyObj->m_comboFrame == 0) {
				matched = false;
				break;
			}

			unsigned int objParticle = static_cast<unsigned int>(partyObj->m_itemId);
			unsigned short reqParticle = combiCursor[slot * 3 + 0];
			bool itemMatch = false;
			if (slot == count - 1) {
				unsigned short itemCode =
					*reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + (objParticle * 0x48));
				if (itemCode == 0x1F8 && reqParticle == 0x1F8) {
					itemMatch = true;
				}
			}
			if (!itemMatch && objParticle != reqParticle) {
				matched = false;
				break;
			}

			int diff = baseParty->m_comboFrame - partyObj->m_comboFrame;
			int minWindow = static_cast<int>(combiCursor[slot * 3 + 1]);
			int maxWindow = static_cast<int>(combiCursor[slot * 3 + 2]);
			if (partyList[0] != obj && (diff < minWindow || diff > maxWindow)) {
				matched = false;
				break;
			}
		}

		if (matched) {
			found = combiIndex;
		}
	}

	if (found < 0 && count > 0) {
		outFallback = 1;
	}
	return found;
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
