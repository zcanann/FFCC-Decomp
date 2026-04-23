#include "ffcc/charaobj.h"
#include "ffcc/fontman.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/monobj.h"
#include "ffcc/partyobj.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_minigame.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	void*, int, int, int, int, void*, void*);
extern "C" void DeleteParticleSlot__13CFlatRuntime2Fii(void*, int);
extern "C" int GetFreeParticleSlot__13CFlatRuntime2Fv(void*);
extern "C" void EndParticleSlot__13CFlatRuntime2Fii(void*, int, int);
extern "C" void ResetParticleWork__13CFlatRuntime2Fii(void*, int, int);
extern "C" void SetParticleWorkScale__13CFlatRuntime2Ff(void*, float);
extern "C" void SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(void*, int, void*);
extern "C" void SetParticleWorkSpeed__13CFlatRuntime2Ff(void*, float);
extern "C" void SetParticleWorkSe__13CFlatRuntime2Fiii(void*, int, int, int);
extern "C" void SetParticleWorkCol__13CFlatRuntime2Fiif(void*, int, int, float);
extern "C" void SetParticleWorkPos__13CFlatRuntime2FR3Vecf(void*, Vec&, float);
extern "C" void SetParticleWorkVector__13CFlatRuntime2Fff(void*, float, float);
extern "C" void SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void SetParticleWorkTarget__13CFlatRuntime2FR3Vec(void*, Vec&);
extern "C" void SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(void*, void*);
extern "C" void SetParticleWorkNo__13CFlatRuntime2Fi(void*, int);
extern "C" void PutParticleWork__13CFlatRuntime2Fv(void*);
extern "C" int intToClass__13CFlatRuntime2Fi(void*, int);
extern "C" void IgnoreParticle__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(void*, int, void*);
extern "C" void pppEndPart__8CPartMngFi(void*, int);
extern "C" unsigned char calcSpecialPolygonGroup__6CAStarFP3Vec(void*, Vec*);

extern "C" char sCharaObjDebugStatFormat[];

int gCGCharaObjCreateSerial = 0;
unsigned char gCGCharaObjCreateSerialInit = 0;
extern "C" {
extern const float kOneF32;
extern const float kHalfF32;
}

static float& CharaObjTargetAngle(CGCharaObj* charaObj)
{
	return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(charaObj) + 0x5CC);
}

static float CharaObjGetRotateY(const Vec& vector)
{
	if (vector.x == 0.0f && vector.z == 0.0f) {
		return 0.0f;
	}

	return static_cast<float>(atan2(vector.x, vector.z));
}

static float CharaObjGetStatusMultiplier(int offset)
{
	return (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + offset)) * 0.01f) + 1.0f;
}

static int CharaObjGetPadSlotIndex(unsigned char slot)
{
	return slot & ~((~(Pad._448_4_ - static_cast<int>(slot) | static_cast<int>(slot) - Pad._448_4_) >> 31));
}

static bool CharaObjUseDebugPad(unsigned char slot)
{
	return (Pad._452_4_ != 0) || ((slot == 0) && (Pad._448_4_ != -1));
}

static unsigned short CharaObjGetPadState(unsigned char slot, int baseOffset)
{
	if (CharaObjUseDebugPad(slot)) {
		return 0;
	}

	int idx = CharaObjGetPadSlotIndex(slot);
	return *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + baseOffset + idx * 0x54);
}

static unsigned short CharaObjGetPadHeld(unsigned char slot)
{
	return CharaObjGetPadState(slot, 0x4);
}

static unsigned short CharaObjGetPadStatusReduceMask(unsigned char slot)
{
	unsigned short mask = CharaObjGetPadState(slot, 0x8);
	unsigned int miniGameFlags = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&MiniGamePcs) + 0x6484);
	if ((miniGameFlags & 0x100) != 0) {
		mask |= CharaObjGetPadState(slot, 0x10);
	}

	return mask;
}

static void CharaObjEndSlots(CGCharaObj* charaObj, unsigned int slotMask)
{
	for (int i = 0; i < 0x16; i++) {
		if ((slotMask & (1U << i)) != 0) {
			EndParticleSlot__13CFlatRuntime2Fii(CFlat, charaObj->m_particleSlots[i], 1);
		}
	}
}

static int CharaObjGetModelPdtNo(CGCharaObj* charaObj)
{
	if (charaObj->m_charaModelHandle == 0 || charaObj->m_charaModelHandle->m_pdtLoadRef == 0) {
		return -1;
	}
	return reinterpret_cast<int*>(charaObj->m_charaModelHandle->m_pdtLoadRef)[2];
}

static float CharaObjGetMonsterScale(unsigned char* script9, bool isMon)
{
	if (!isMon || script9 == 0) {
		return 1.0f;
	}
	return static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0x1B4)) * 0.01f;
}

static void CharaObjPutMonsterScaledParticle(CGCharaObj* charaObj, int particleNo, int slot, float scale)
{
	charaObj->putParticle(particleNo, slot, static_cast<CGObject*>(charaObj), 20.0f * charaObj->m_attackColRadius * scale, 0);
}

static Vec& CharaObjComboCenter(CGCharaObj* charaObj)
{
	return *reinterpret_cast<Vec*>(reinterpret_cast<unsigned char*>(charaObj) + 0x66C);
}

static Vec& CharaObjComboTarget(CGCharaObj* charaObj)
{
	return *reinterpret_cast<Vec*>(reinterpret_cast<unsigned char*>(charaObj) + 0x678);
}

static int& CharaObjComboItemState(CGCharaObj* charaObj)
{
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(charaObj) + 0x684);
}

static int& CharaObjComboScriptArg(CGCharaObj* charaObj)
{
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(charaObj) + 0x698);
}

static unsigned int& CharaObjComboScriptMode(CGCharaObj* charaObj)
{
	return *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(charaObj) + 0x69C);
}

static float& CharaObjComboLinkCount(CGCharaObj* charaObj)
{
	return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(charaObj) + 0x6A8);
}

static CGPrgObj** CharaObjComboLinks(CGCharaObj* charaObj)
{
	return reinterpret_cast<CGPrgObj**>(reinterpret_cast<unsigned char*>(charaObj) + 0x6AC);
}

static unsigned char& CharaObjComboFlags(CGCharaObj* charaObj)
{
	return *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(charaObj) + 0x6B8);
}

static bool CharaObjSkipComboScript(CGPrgObj* obj)
{
	if (obj == 0) {
		return true;
	}

	if (Game.m_gameWork.m_menuStageMode == 0 || Game.m_gameWork.m_bossArtifactStageIndex >= 0xF) {
		return false;
	}

	return ((obj->GetCID() & 0x6D) == 0x6D) &&
	       (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(obj->m_scriptHandle) + 0x3B4) != 0);
}

static bool CharaObjIsPlayerCid(unsigned int cid)
{
	return (cid & 0x6D) == 0x6D;
}

static bool CharaObjIsElementalStatus(unsigned int staType)
{
	return staType == 0 || staType == 1 || staType == 3 || staType == 4 ||
	       staType == 6 || staType == 8 || staType == 9 || staType == 0x1C;
}

static bool CharaObjIsBreakStatus(unsigned int staType)
{
	return staType == 0x24 || staType == 0x25 || staType == 0x69 || staType == 0x6A;
}

static bool CharaObjCanFrontGuard(CGCharaObj* self, CGPrgObj* sourceObj)
{
	Vec delta;
	Vec facing;
	float magSq;
	float invMag;
	float dot;

	if (sourceObj == 0) {
		return false;
	}

	delta.x = sourceObj->m_worldPosition.x - self->m_worldPosition.x;
	delta.y = 0.0f;
	delta.z = sourceObj->m_worldPosition.z - self->m_worldPosition.z;
	magSq = delta.x * delta.x + delta.z * delta.z;
	if (magSq <= 0.0f) {
		return false;
	}

	invMag = 1.0f / sqrtf(magSq);
	delta.x *= invMag;
	delta.z *= invMag;
	facing.x = sinf(self->m_rotBaseY);
	facing.y = 0.0f;
	facing.z = cosf(self->m_rotBaseY);
	dot = delta.x * facing.x + delta.z * facing.z;
	return dot > 0.0f;
}

static int CharaObjDecodeSe(unsigned short encodedSe)
{
	if (encodedSe == 0 || encodedSe == 0xFFFF) {
		return 0;
	}
	return (encodedSe & 0xFF) + ((encodedSe >> 8) * 1000);
}

static int CharaObjResolveParticleBank(CGCharaObj* charaObj, unsigned short particleClass)
{
	if (particleClass == 0xFE) {
		int pdtNo = CharaObjGetModelPdtNo(charaObj);
		return (pdtNo >= 0) ? pdtNo : -1;
	}
	if (particleClass >= 0xFD && particleClass <= 0xFF) {
		return -1;
	}
	return particleClass;
}

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

	if (gCGCharaObjCreateSerialInit == 0) {
		gCGCharaObjCreateSerial = 0;
		gCGCharaObjCreateSerialInit = 1;
	}

	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x54D) = gCGCharaObjCreateSerial;
	gCGCharaObjCreateSerial += 1;

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
	m_pushScale = kOneF32;
	m_alpha = kOneF32;
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
				EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 1);
			}
		}
		m_damageParticle = -1;
	} else if (state == 2) {
		for (int i = 0; i < 0x16; i++) {
			if (((1U << i) & 0x18U) != 0) {
				EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 1);
			}
		}
	} else if (state == 0x12) {
		for (int i = 0; i < 0x16; i++) {
			if (((1U << i) & 1U) != 0) {
				EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 1);
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
	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	if (script != 0) {
		if (*reinterpret_cast<short*>(script + 0x42) != 0) {
			unsigned short tickDiv = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x3A);
			if (m_stateTick != 0 && tickDiv != 0 && (m_stateTick % static_cast<int>(tickDiv)) == 0) {
				playSe3D(0x19, 0x32, 0x96, 0, 0);
				addHp(-1, 0);
			}
		}

		unsigned int cid = GetCID();
		for (int i = 0; i < 0x27; i++) {
			int statusValue = static_cast<int>(*reinterpret_cast<short*>(script + 0x3E + i * 2)) - 1;
			if (statusValue != 0 && i == 2) {
				m_stateTick += 1;
			}

			if (CharaObjIsPlayerCid(cid) &&
			    (i == 0 || i == 3 || i == 4 || i == 9) &&
			    statusValue > 0) {
				unsigned short padMask = CharaObjGetPadStatusReduceMask(m_animStateMisc);
				if ((padMask & 0xF) != 0) {
					statusValue -= *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x3C);
				}
			}

			setSta(i, statusValue);
		}

		if (*reinterpret_cast<short*>(script + 0x3E) == 0 &&
		    *reinterpret_cast<short*>(script + 0x14) == 0 &&
		    *reinterpret_cast<short*>(script + 0x11) == 0) {
			m_displayFlags |= 2;
		} else {
			m_displayFlags &= ~2;
			m_ignoreHit[0].m_flag &= 0x7F;
		}
	}

	m_flags = static_cast<unsigned char>(m_flags + 1);

	for (int i = 0; i < 4; i++) {
		IgnoreHitSlot& slot = m_ignoreHit[i];
		if ((static_cast<signed char>(slot.m_flag) < 0) && slot.m_timer != 0) {
			slot.m_timer = static_cast<unsigned short>(slot.m_timer - 1);
			if (slot.m_timer == 0) {
				slot.m_flag &= 0x7F;
			}
		}
	}
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
	if (Game.unk_flat3_0xc7d0 != 0) {
		PSVECSubtract(reinterpret_cast<Vec*>(Game.unk_flat3_0xc7d0 + 0x15C), &m_worldPosition,
			&m_targetDelta);
		m_targetDist = PSVECMag(&m_targetDelta);
		CharaObjTargetAngle(this) = CharaObjGetRotateY(m_targetDelta);
	} else {
		m_targetDelta.x = 0.0f;
		m_targetDelta.y = 0.0f;
		m_targetDelta.z = 0.0f;
		m_targetDist = 0.0f;
		CharaObjTargetAngle(this) = 0.0f;
	}

	for (int i = 0; i < 4; i++) {
		CGPartyObj* partyObj = Game.m_partyObjArr[i];
		m_partyRank[i] = 0;
		if (partyObj == 0) {
			m_partyDistance[i] = 0.0f;
			m_partyDelta[i].x = 0.0f;
			m_partyDelta[i].y = 0.0f;
			m_partyDelta[i].z = 0.0f;
			m_partyAngle[i] = 0.0f;
		} else {
			PSVECSubtract(&partyObj->m_worldPosition, &m_worldPosition, &m_partyDelta[i]);
			m_partyDistance[i] = PSVECMag(&m_partyDelta[i]);
			m_partyAngle[i] = CharaObjGetRotateY(m_partyDelta[i]);
		}

		for (int j = 0; j < i; j++) {
			if (m_partyDistance[i] == 0.0f) {
				m_partyRank[i] += 1;
			} else if (m_partyDistance[j] == 0.0f) {
				m_partyRank[j] += 1;
			} else if (m_partyDistance[j] <= m_partyDistance[i]) {
				m_partyRank[i] += 1;
			} else {
				m_partyRank[j] += 1;
			}
		}
	}

	m_pushScale = 1.0f;
	if (m_scriptHandle != 0) {
		unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
		if (*reinterpret_cast<short*>(script + 0x4E) != 0) {
			m_pushScale *= CharaObjGetStatusMultiplier(0x34);
		}
		if (*reinterpret_cast<short*>(script + 0x4C) != 0) {
			m_pushScale *= CharaObjGetStatusMultiplier(0x36);
		}
		if (*reinterpret_cast<short*>(script + 0x40) != 0) {
			m_pushScale *= CharaObjGetStatusMultiplier(0x40);
		}
	}
	if (m_pushScale > 1.5f) {
		m_pushScale = 1.5f;
	}

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

	unsigned int cid = GetCID();
	if (CharaObjIsPlayerCid(cid)) {
		if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6F0) != 0) {
			push += 10;
		}
		if (CharaObjGetPadHeld(m_animStateMisc) != 0) {
			push += 0x19;
		}
		if (static_cast<signed char>(reinterpret_cast<unsigned char*>(this)[0x9B]) >= 0) {
			push += 0x19;
		}
	}

	m_pushParamB = static_cast<unsigned char>(push < 0x19 ? push : 0x19);
	if ((cid & 0xAD) == 0xAD && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6D8) == 4) {
		m_pushParamB = 100;
	}

	if ((DbgMenuPcs.GetDbgFlagsRaw() & 1) == 0) {
		m_aStarGroupId = static_cast<unsigned short>(static_cast<unsigned char>(m_lastBgGroup));
	} else {
		m_aStarGroupId = static_cast<unsigned short>(
			calcSpecialPolygonGroup__6CAStarFP3Vec(reinterpret_cast<unsigned char*>(&DbgMenuPcs) + 0x2A5C, &m_worldPosition));
	}
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
float CGCharaObj::onAlphaUpdate()
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
	return alpha;
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
			EndParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i], 1);
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
	if ((sourceCid & 0x6D) == 0x6D && Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
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
				*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (particleIndex * 0x48) + 0xE);
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
	if ((cid & 0x6D) == 0x6D && Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex <= 0xE) {
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
	if ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (particleIndex * 0x48) + 0xC) & 0x100) != 0) {
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
	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	if (script == 0) {
		return;
	}

	unsigned int cid = GetCID();
	bool isMon = (cid & 0xAD) == 0xAD;
	unsigned char* script9 = (m_scriptHandle[9] != 0) ? reinterpret_cast<unsigned char*>(m_scriptHandle[9]) : 0;
	bool isIceJ = isMon && script9 != 0 && *reinterpret_cast<short*>(script9 + 0xFC) == 0xB;

	int current = *reinterpret_cast<short*>(script + 0x3E + (staIndex * 2));
	value &= ~(value >> 31);

	if (current == 0) {
		if (value != 0) {
			switch (staIndex) {
				case 0:
					CharaObjEndSlots(this, 0x4);
					if (isIceJ) {
						putParticleBindTrace((CharaObjGetModelPdtNo(this) << 8) | 0x15, m_particleSlots[2], this, 1.0f, 0);
					} else {
						putParticle(0x10A, m_particleSlots[2], this, 20.0f * m_attackColRadius, 0);
					}
					if (isMon) {
						reinterpret_cast<CGMonObj*>(this)->setIceJEffect(0);
					}
					break;
				case 1:
					CharaObjEndSlots(this, 0x40);
					if (isIceJ) {
						putParticle((CharaObjGetModelPdtNo(this) << 8) | 0x14, m_particleSlots[6], this, 1.0f, 0);
					} else {
						putParticle(0x12A, m_particleSlots[6], this, 20.0f * m_attackColRadius, 0);
					}
					break;
				case 2:
					m_castTimeTick = 0;
					CharaObjEndSlots(this, 0x80000);
					putParticleBindTrace(0x10C, m_particleSlots[19], this, 20.0f * m_attackColRadius, 0);
					break;
				case 3:
					CharaObjEndSlots(this, 0x40000);
					putParticleBindTrace(0x10D, m_particleSlots[18], this, 20.0f * m_attackColRadius, 0);
					break;
				case 4:
					CharaObjEndSlots(this, 0x80);
					if (isIceJ) {
						putParticle((CharaObjGetModelPdtNo(this) << 8) | 0x17, m_particleSlots[7], this, 1.0f, 0);
					} else {
						putParticle(0x130, m_particleSlots[7], this, 20.0f * m_attackColRadius, 0);
					}
					break;
				case 6:
					CharaObjEndSlots(this, 0x100000);
					putParticleBindTrace(0x107, m_particleSlots[20], this, 20.0f * m_attackColRadius, 0);
					break;
				case 7: {
					CharaObjEndSlots(this, 0x8000);
					int particleNo = isMon ? 0x170 : 0x114;
					putParticle(particleNo, m_particleSlots[15], this, 20.0f * m_attackColRadius, 0);
					break;
				}
				case 8: {
					CharaObjEndSlots(this, 0x2000);
					int particleNo = (isMon ? 0x16E : 0x112) | 0x100;
					CharaObjPutMonsterScaledParticle(this, particleNo, m_particleSlots[13], CharaObjGetMonsterScale(script9, isMon));
					break;
				}
				case 9: {
					CharaObjEndSlots(this, 0x4000);
					int particleNo = (isMon ? 0x16C : 0x110) | 0x100;
					CharaObjPutMonsterScaledParticle(this, particleNo, m_particleSlots[14], CharaObjGetMonsterScale(script9, isMon));
					break;
				}
				case 10:
					if (isMon && script9 != 0 && (*reinterpret_cast<unsigned short*>(script9 + 0xFE) & 4) != 0) {
						reinterpret_cast<CGMonObj*>(this)->flyDown();
					}
					break;
				case 0x1B:
					CharaObjEndSlots(this, 0x400);
					putParticle(0x11C, m_particleSlots[10], this, 1.0f, 0x1290D);
					break;
				case 0x1C:
					if (isMon && script9 != 0 && (*reinterpret_cast<unsigned short*>(script9 + 0xFE) & 1) != 0) {
						reinterpret_cast<CGMonObj*>(this)->undeadOff();
					}
					break;
				default:
					break;
			}
		}
	} else {
		switch (staIndex) {
			case 0:
				CharaObjEndSlots(this, 0x4);
				if (isIceJ) {
					putParticle((CharaObjGetModelPdtNo(this) << 8) | 0x16, 0, this, 1.0f, 0);
				} else {
					putParticle(0x10B, 0, this, 20.0f * m_attackColRadius, 0);
				}
				playSe3D(0x16, 0x32, 0x96, 0, 0);
				if (isMon) {
					reinterpret_cast<CGMonObj*>(this)->setIceJEffect(1);
				}
				break;
			case 1:
				CharaObjEndSlots(this, 0x40);
				break;
			case 2:
				CharaObjEndSlots(this, 0x80000);
				break;
			case 3:
				CharaObjEndSlots(this, 0x40000);
				putParticle(0x10E, 0, this, 20.0f * m_attackColRadius, 0);
				playSe3D(0x3A, 0x32, 0x96, 0, 0);
				break;
			case 4:
				CharaObjEndSlots(this, 0x80);
				break;
			case 6:
				CharaObjEndSlots(this, 0x100000);
				break;
			case 7: {
				CharaObjEndSlots(this, 0x8000);
				int particleNo = (isMon ? 0x171 : 0x115) | 0x100;
				putParticle(particleNo, 0, this, 20.0f * m_attackColRadius, 0);
				break;
			}
			case 8: {
				CharaObjEndSlots(this, 0x2000);
				int particleNo = (isMon ? 0x16F : 0x113) | 0x100;
				CharaObjPutMonsterScaledParticle(this, particleNo, 0, CharaObjGetMonsterScale(script9, isMon));
				break;
			}
			case 9: {
				CharaObjEndSlots(this, 0x4000);
				int particleNo = (isMon ? 0x16D : 0x111) | 0x100;
				CharaObjPutMonsterScaledParticle(this, particleNo, 0, CharaObjGetMonsterScale(script9, isMon));
				break;
			}
			case 10:
				if (isMon && script9 != 0 && (*reinterpret_cast<unsigned short*>(script9 + 0xFE) & 4) != 0 &&
					*reinterpret_cast<short*>(script + 0x1C) != 0) {
					reinterpret_cast<CGMonObj*>(this)->flyUp();
				}
				break;
			case 0x1B:
				CharaObjEndSlots(this, 0x400);
				break;
			case 0x1C:
				if (isMon && script9 != 0 && (*reinterpret_cast<unsigned short*>(script9 + 0xFE) & 1) != 0) {
					reinterpret_cast<CGMonObj*>(this)->undeadOn();
				}
				break;
			default:
				break;
		}
	}

	*reinterpret_cast<short*>(script + 0x3E + (staIndex * 2)) = static_cast<short>(value);
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
			if (Game.m_gameWork.m_gameOverFlag == 0) {
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
	unsigned char* gameFlat = reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc);
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

	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + (amount * 0x48);
	short itemType = (amount < 0x1F5) ? 1 : *reinterpret_cast<short*>(itemData + 2);

	unsigned int sourceCid = source->GetCID();
	unsigned int power = 0;
	if ((sourceCid & 0x2D) == 0x2D) {
		CGObject* statSource = source;
		if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
			(sourceCid & 0x6D) == 0x6D &&
			source->m_scriptHandle != 0 && source->m_scriptHandle[0xED] != 0) {
			statSource = reinterpret_cast<CGObject*>(Game.m_partyObjArr[0]);
		}
		if (statSource != 0 && statSource->m_scriptHandle != 0 && statSource->m_scriptHandle[9] != 0) {
			power = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(statSource->m_scriptHandle[9]) + 0x198);
		}
	} else {
		power = *reinterpret_cast<unsigned short*>(itemData + 0x2E);
	}

	if ((sourceCid & 0xAD) == 0xAD) {
		int stageLevel = 0;
		if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			stageLevel = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
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
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + (itemId * 0x48);

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
void CGCharaObj::onDamage(CGPrgObj* sourceObj, int itemId, int, int, Vec* hitPos)
{
	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	unsigned int cid = GetCID();
	int resolvedItemId = itemId;
	unsigned int staType;
	int resistType = 0;
	int allowEffect = 0;
	int severity = 0;
	int effectResult = 0;

	if (m_scriptHandle == 0) {
		damageDelete();
		changeStat(6, 0, 0);
		return;
	}

	if (resolvedItemId < 0) {
		resolvedItemId = m_itemId;
	}
	if (resolvedItemId < 0) {
		return;
	}

	if (CharaObjIsPlayerCid(cid) && *reinterpret_cast<short*>(script + 0x12) != 0) {
		return;
	}
	if (CharaObjIsPlayerCid(cid) && static_cast<unsigned short>((m_lastMapIdExtra << 8) | m_lastMapIdHit) != 1) {
		return;
	}
	if ((m_weaponNodeFlags & 0x80) == 0) {
		return;
	}

	staType = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + resolvedItemId * 0x48 + 8);
	calcRegist(static_cast<int>(staType), resolvedItemId, resistType, allowEffect, severity, 0);

	if (resistType == 3) {
		if (CharaObjIsElementalStatus(staType)) {
			putParticle(0x201, 0, hitPos, m_attackColRadius, 0x65);
		} else if (CharaObjIsBreakStatus(staType)) {
			putParticle(0x200, 0, hitPos, m_attackColRadius, 0x1D);
		}
	} else if ((resistType > 1 || (resistType == 1 &&
	           ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + resolvedItemId * 0x48 + 0x32) & 1) == 0))) &&
	           CharaObjIsElementalStatus(staType)) {
		putParticle(0x201, 0, hitPos, m_attackColRadius, 0x65);
	}

	if (m_lastStateId == 8 && m_subState == 1 &&
	    ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + resolvedItemId * 0x48 + 0x2C) & 8) == 0) &&
	    CharaObjCanFrontGuard(this, sourceObj)) {
		playSe3D(0x1D, 0x32, 0x96, 0, 0);
		putParticle(0x200, 0, hitPos, m_attackColRadius, 0);
		if (sourceObj != 0 && CharaObjIsPlayerCid(sourceObj->GetCID())) {
			sourceObj->changeStat(0x13, 0, 0);
		}
		if (CharaObjIsPlayerCid(cid)) {
			changeSubStat(2);
		}
		allowEffect = 0;
		effectResult = 0;
	}

	if (*reinterpret_cast<short*>(script + 0x1D) != 0) {
		allowEffect = 0;
		effectResult = 0;
	}
	if (*reinterpret_cast<short*>(script + 0x11) != 0) {
		allowEffect = 0;
	}
	if (*reinterpret_cast<short*>(script + 0x14) != 0 && (staType == 7 || staType == 8)) {
		allowEffect = 0;
		effectResult = 0;
	}
	if (*reinterpret_cast<short*>(script + 7) == 0) {
		if (staType == 0x65) {
			allowEffect = 1;
			effectResult = 0;
		} else {
			allowEffect = 0;
			effectResult = 0;
		}
	} else if (staType == 0x65) {
		allowEffect = 0;
		effectResult = 0;
	} else if (staType == 0x66 || staType == 0x67 || staType == 7) {
		allowEffect = 1;
		effectResult = 0;
	}

	if (allowEffect != 0) {
		effective(static_cast<int>(staType), resolvedItemId, sourceObj, effectResult);
	}

	if (effectResult == 0) {
		damageDelete();
		changeStat(6, 0, 0);
		return;
	}

	if (staType == 0x1C || staType == 4 || staType < 2) {
		changeStat(6, 0, 0);
	} else if (staType == 0x25 || staType == 0x68 || staType == 0x6A) {
		changeStat(0x19, 0, 0);
	} else if (staType == 0x6B) {
		changeStat(0x1A, 0, 0);
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
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + effectId * 0x48;
	unsigned short particleClass = *reinterpret_cast<unsigned short*>(itemData + 0x12);
	int particleBank = CharaObjResolveParticleBank(this, particleClass);
	unsigned short particleEntry = 0xFFFF;
	unsigned short particleFlags = 0;
	int particleNo = -1;
	int seNo = 0;
	bool emittedCustom = false;

	if (particleBank >= 0) {
		particleEntry = *reinterpret_cast<unsigned short*>(itemData + 0x14 + effectArg0 * 2);
		if (particleEntry != 0xFFFF) {
			particleFlags = particleEntry;
			particleNo = particleEntry & 0xFF;

			if ((particleFlags & 0x1000) != 0) {
				particleBank = 1;
			} else if ((particleFlags & 0x2000) != 0) {
				particleBank = 2;
			} else if ((particleFlags & 0x4000) != 0) {
				particleBank = 3;
			} else if (particleBank == 1 && particleNo < 8 && m_scriptHandle != 0) {
				particleNo += *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xF8);
			}

			if ((particleFlags & 0x800) != 0 && m_scriptHandle != 0) {
				particleNo += *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2);
			}
		}
	}

	if (particleNo >= 0) {
		ResetParticleWork__13CFlatRuntime2Fii(CFlat, (particleBank << 8) | particleNo, effectArg1);
		SetParticleWorkScale__13CFlatRuntime2Ff(CFlat, *reinterpret_cast<unsigned short*>(itemData + 0x10) * 0.01f);
		SetParticleWorkParam__13CFlatRuntime2FiPQ212CFlatRuntime7CObject(CFlat, effectId, this);
		SetParticleWorkSpeed__13CFlatRuntime2Ff(CFlat, *reinterpret_cast<unsigned short*>(itemData + 0x26) * 0.01f);

		if (effectId > 500) {
			unsigned short itemType = *reinterpret_cast<unsigned short*>(itemData + 2);
			int colType = -1;
			if (itemType == 1 || itemType == 4 || itemType == 8 || itemType == 9) {
				colType = itemType;
			}
			if (colType >= 0) {
				SetParticleWorkCol__13CFlatRuntime2Fiif(CFlat, colType, -1, *reinterpret_cast<unsigned short*>(itemData + 4) * 0.01f);
			}
		}

		switch (effectArg0) {
		case 0:
			seNo = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(itemData + 0x38));
			if (seNo != 0 && (*reinterpret_cast<unsigned short*>(itemData + 0x3A) & 0x8000) != 0) {
				SetParticleWorkSe__13CFlatRuntime2Fiii(CFlat, seNo, 2, *reinterpret_cast<unsigned short*>(itemData + 0x3A) & 0xFF);
				seNo = 0;
			}
			break;
		case 1:
			seNo = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(itemData + 0x3C));
			if (seNo != 0 && (*reinterpret_cast<unsigned short*>(itemData + 0x3E) & 0x8000) != 0) {
				SetParticleWorkSe__13CFlatRuntime2Fiii(CFlat, seNo, 2, *reinterpret_cast<unsigned short*>(itemData + 0x3E) & 0xFF);
				seNo = 0;
			}
			break;
		case 2:
			seNo = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(itemData + 0x40));
			if (seNo != 0 && (*reinterpret_cast<unsigned short*>(itemData + 0x0C) & 0x400) != 0) {
				SetParticleWorkSe__13CFlatRuntime2Fiii(CFlat, seNo, 2, 0);
				seNo = 0;
			}
			break;
		default:
			break;
		}

		if ((particleFlags & 0x100) != 0) {
			SetParticleWorkBind__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, this);
		} else if ((particleFlags & 0x200) != 0) {
			float distance = *reinterpret_cast<unsigned short*>(itemData + 0x2A) * 1.0f;
			Vec offsetPos;
			offsetPos.x = m_worldPosition.x + sinf(m_rotTargetY) * distance;
			offsetPos.y = m_worldPosition.y;
			offsetPos.z = m_worldPosition.z + cosf(m_rotTargetY) * distance;
			SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, offsetPos, m_rotTargetY);
			SetParticleWorkVector__13CFlatRuntime2Fff(CFlat, m_rotTargetY, 0.0f);
			if ((*reinterpret_cast<unsigned short*>(itemData + 0x0C) & 0x4000) != 0) {
				SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, m_worldPosition, m_rotTargetY);
				SetParticleWorkTarget__13CFlatRuntime2FR3Vec(CFlat, m_jumpOffset);
				SetParticleWorkTrace__13CFlatRuntime2FPQ212CFlatRuntime7CObject(CFlat, this);
			}
		} else if (pos != 0) {
			SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, *pos, m_rotTargetY);
		} else if ((particleFlags & 0x400) != 0) {
			SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, m_jumpOffset, 0.0f);
		} else {
			SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, m_worldPosition, m_rotTargetY);
		}

		if (effectId == 0x3B4 && effectArg0 == 3 && pos != 0) {
			SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, *pos, m_rotTargetY);
			PutParticleWork__13CFlatRuntime2Fv(CFlat);
			emittedCustom = true;
		} else if (effectId == 0x409 && effectArg0 == 3) {
			for (int i = 3; i < 9; i++) {
				SetParticleWorkNo__13CFlatRuntime2Fi(CFlat, (particleBank << 8) | i);
				PutParticleWork__13CFlatRuntime2Fv(CFlat);
			}
			emittedCustom = true;
		} else if (effectId > 0x46C && effectId < 0x46F) {
			if (effectArg0 == 2 && m_stateFrame > 0xF) {
				Vec randomPos;
				randomPos.x = m_worldPosition.x + Math.RandFPM(20.0f);
				randomPos.y = m_worldPosition.y + 1.0f;
				randomPos.z = m_worldPosition.z + Math.RandFPM(20.0f);
				SetParticleWorkNo__13CFlatRuntime2Fi(CFlat, (particleBank << 8) | 0x1D);
				SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, randomPos, m_rotTargetY);
				PutParticleWork__13CFlatRuntime2Fv(CFlat);
				emittedCustom = true;
			} else if (effectArg0 == 3) {
				for (int i = 0x0D; i < 0x1D; i++) {
					SetParticleWorkNo__13CFlatRuntime2Fi(CFlat, (particleBank << 8) | i);
					PutParticleWork__13CFlatRuntime2Fv(CFlat);
				}
				emittedCustom = true;
			}
		} else if (effectId > 0x472 && effectId < 0x479 && effectArg0 == 3) {
			for (int i = 7; i < 0x0C; i++) {
				SetParticleWorkNo__13CFlatRuntime2Fi(CFlat, (particleBank << 8) | i);
				PutParticleWork__13CFlatRuntime2Fv(CFlat);
			}
			emittedCustom = true;
		} else if (effectId > 0x49C && effectId < 0x4A0 && effectArg0 == 2) {
			for (int i = 0; i < 2; i++) {
				float side = (i == 0) ? 76.0f : -76.0f;
				Vec sidePos;
				sidePos.x = m_worldPosition.x + cosf(m_rotTargetY) * side;
				sidePos.y = m_worldPosition.y;
				sidePos.z = m_worldPosition.z - sinf(m_rotTargetY) * side;
				SetParticleWorkPos__13CFlatRuntime2FR3Vecf(CFlat, sidePos, m_rotTargetY);
				SetParticleWorkVector__13CFlatRuntime2Fff(CFlat, m_rotTargetY, 0.0f);
				PutParticleWork__13CFlatRuntime2Fv(CFlat);
			}
			emittedCustom = true;
		}

		if (seNo != 0) {
			Vec* sePos = (effectArg0 == 2) ? pos : 0;
			int seHandle = playSe3D(seNo, 0x32, 0x96, 0, sePos);
			Sound.SetSe3DGroup(seHandle, m_particleId);
		}

		if (!emittedCustom) {
			unsigned short fanCount = *reinterpret_cast<unsigned short*>(itemData + 0x24);
			if (effectArg0 == 3 && fanCount > 1) {
				for (int i = 0; i < fanCount; i++) {
					float t = (fanCount > 1) ? ((float)i / (float)(fanCount - 1)) : 0.0f;
					SetParticleWorkVector__13CFlatRuntime2Fff(CFlat, t * 0.75f, 0.0f);
					PutParticleWork__13CFlatRuntime2Fv(CFlat);
				}
			} else {
				PutParticleWork__13CFlatRuntime2Fv(CFlat);
			}
		}
	} else if (effectArg0 == 2) {
		seNo = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(itemData + 0x40));
		if (seNo != 0) {
			int seHandle = playSe3D(seNo, 0x32, 0x96, 0, pos);
			Sound.SetSe3DGroup(seHandle, m_particleId);
		}
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
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + itemOffset;

	unsigned int baseCast = *reinterpret_cast<unsigned short*>(itemData + 0x2E);
	unsigned short itemType = *reinterpret_cast<unsigned short*>(itemData + 0xE);
	unsigned int cast = baseCast;

	if (itemType == 2) {
		unsigned int cid = GetCID();
		if ((cid & 0xAD) == 0xAD && Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			int stage = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
			if (stage > 2) {
				stage = 2;
			}
			if (stage > 0) {
				unsigned short bonus = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x58 + (stage * 2));
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
void CGCharaObj::onDrawDebug(CFont* font, float posX, float& posY, float posZ)
{
	if ((((int)((unsigned int)(unsigned char)m_weaponNodeFlags << 0x18) < 0) && (*reinterpret_cast<unsigned int*>(CFlat + 0x12AC) == 0)) &&
	    ((*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&MiniGamePcs) + 0x6484) & 0x80) != 0)) {
		char text[0x110];
		unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
		double posYDouble;
		double widthDouble;

		sprintf(text, sCharaObjDebugStatFormat,
		        *reinterpret_cast<short*>(script + 0x1C),
		        *reinterpret_cast<short*>(script + 0x1A),
		        *reinterpret_cast<short*>(script + 0x1E),
		        *reinterpret_cast<short*>(script + 0x20),
		        *reinterpret_cast<short*>(script + 0x22));

		posYDouble = (double)posY;
		widthDouble = (double)font->GetWidth(text);
		font->SetPosX(-(float)((double)kHalfF32 * widthDouble - (double)posX));
		font->SetPosY((float)posYDouble);
		font->SetPosZ((float)posZ);
		font->Draw(text);
		posY -= (float)((double)(unsigned short)font->m_glyphWidth * (double)font->scaleY);
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
void CGCharaObj::addSe(int)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int particle = m_itemId;
	unsigned short se = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (particle * 0x48) + 0x38);
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

	for (int i = 0; i < 4; i++) {
		CGPartyObj* partyObj = Game.m_partyObjArr[i];
		if (partyObj == 0) {
			continue;
		}

		unsigned char* partyRaw = reinterpret_cast<unsigned char*>(partyObj);
		if (static_cast<signed char>(partyRaw[0x9A]) < 0 &&
		    static_cast<signed char>(partyRaw[0x9B]) < 0) {
			unsigned char* script = reinterpret_cast<unsigned char*>(partyObj->m_scriptHandle);
			if (script != 0) {
				unsigned short hp = *reinterpret_cast<unsigned short*>(script + 0x1C);
				unsigned short maxHp = *reinterpret_cast<unsigned short*>(script + 0x1A);
				if (hp != 0 && hp <= (maxHp >> 2)) {
					if ((System.m_frameCounter % 0x1E) == 0) {
						Sound.PlaySe(0x53, 0x40, 0x7F, 0);
					}
					break;
				}
			}
		}
	}

	combi2();
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
	CGPartyObj* candidates[5];
	int candidateCount = 0;

	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.m_partyObjArr[i];
		if (party == 0) {
			continue;
		}

		if ((party->m_lastStateId == 6 || party->m_lastStateId == 2) && party->m_subState == 1) {
			candidates[candidateCount++] = party;
		}
	}

	if (candidateCount == 0) {
		return;
	}

	for (int i = 0; i < candidateCount; i++) {
		CGPartyObj* party = candidates[i];
		if (party == 0 || party->m_comboState == 0) {
			continue;
		}

		bool hasNearbyPartner = false;
		for (int j = 0; j < candidateCount; j++) {
			if (i == j) {
				continue;
			}

			CGPartyObj* other = candidates[j];
			if (other == 0 || other->m_comboState == 0) {
				continue;
			}

			if (PSVECDistance(&CharaObjComboCenter(party), &CharaObjComboCenter(other)) < 20.0f) {
				hasNearbyPartner = true;
				break;
			}
		}

		unsigned char& comboFlags = CharaObjComboFlags(party);
		const bool hadNearbyPartner = (comboFlags & 0x40) != 0;
		if (hasNearbyPartner != hadNearbyPartner) {
			comboFlags = (comboFlags & ~0x40) | (hasNearbyPartner ? 0x40 : 0);
			comboFlags = (comboFlags & ~0x10) | 0x10;
			party->playSe3D(hasNearbyPartner ? 0x3E : 0x3D, 0x32, 0x96, 0, 0);
		}
	}

	for (int i = 0; i < candidateCount - 1; i++) {
		for (int j = i + 1; j < candidateCount; j++) {
			if (candidates[i]->m_comboFrame < candidates[j]->m_comboFrame) {
				CGPartyObj* swap = candidates[i];
				candidates[i] = candidates[j];
				candidates[j] = swap;
			}
		}
	}

	for (int i = 1; i < candidateCount; ) {
		if (PSVECDistance(&CharaObjComboCenter(candidates[0]), &CharaObjComboCenter(candidates[i])) > 20.0f) {
			for (int j = i; j < candidateCount - 1; j++) {
				candidates[j] = candidates[j + 1];
			}
			candidateCount--;
			continue;
		}
		i++;
	}

	if (candidates[0]->m_comboFrame == 0) {
		return;
	}

	int fallback = 0;
	int comboIndex = searchCombi(candidateCount, candidates, fallback);
	if (comboIndex < 0) {
		if (fallback == 0 || candidates[0]->m_comboFrame > 0x41) {
			candidates[0]->m_comboState = 0;
			candidates[0]->m_comboFrame = 0;
			candidates[0]->addSubStat();
			combi2();
		}
		return;
	}

	if (fallback != 0 && candidates[0]->m_comboFrame <= 0x41) {
		return;
	}

	unsigned short* comboData = reinterpret_cast<unsigned short*>(Game.unk_flat3_field_1C_0xc7d8) + comboIndex * 0xD;
	int participantCount = 0;
	if (comboData[0] != 0) {
		participantCount = 1;
		if (comboData[3] != 0) {
			participantCount = 2;
			if (comboData[6] != 0) {
				participantCount = 3;
				if (comboData[9] != 0) {
					participantCount = 4;
				}
			}
		}
	}

	const unsigned short comboCmd = comboData[0xC];
	const bool isSharedResult = comboData[participantCount * 3 - 3] != 0x1F8;
	Vec comboCenter = {0.0f, 0.0f, 0.0f};
	if (isSharedResult) {
		for (int i = 0; i < participantCount; i++) {
			PSVECAdd(&comboCenter, &CharaObjComboCenter(candidates[i]), &comboCenter);
		}
		PSVECScale(&comboCenter, &comboCenter, 1.0f / static_cast<float>(participantCount));
	}

	CGPartyObj* leadParty = candidates[participantCount - 1];
	bool playedComboSe = false;
	for (int i = 0; i < participantCount; i++) {
		CGPartyObj* party = candidates[i];
		unsigned int comboMode = 0xFFFFFFFF;

		if (isSharedResult) {
			CharaObjComboCenter(party) = comboCenter;
			if (playedComboSe || CharaObjSkipComboScript(party)) {
				CharaObjComboScriptArg(party) = 0;
			} else {
				CharaObjComboScriptArg(party) = comboCmd;
				party->playSe3D(0x3F, 0x32, 0x96, 0, 0);
				playedComboSe = true;
			}
		} else {
			if (comboCmd == 0x207) {
				comboMode = 0;
			} else if (comboCmd == 0x20B) {
				comboMode = 1;
			} else if (comboCmd == 0x20F) {
				comboMode = 2;
			}

			if (party == leadParty) {
				CharaObjComboItemState(party) = static_cast<int>(comboMode);
				party->playSe3D(0x3F, 0x32, 0x96, 0, 0);
			} else {
				CharaObjComboCenter(party) = leadParty->m_worldPosition;
				CharaObjComboScriptArg(party) = 0;
			}
		}

		party->m_comboState = 0;
		party->m_comboFrame = 0;
		party->addSubStat();
		party->putComboParticle();

		CharaObjComboScriptArg(party) = comboCmd;
		CharaObjComboScriptMode(party) = comboMode;
		CharaObjComboLinkCount(party) = 0.0f;

		int linkCount = 0;
		CGPrgObj** comboLinks = CharaObjComboLinks(party);
		for (int j = 0; j < participantCount; j++) {
			CGPartyObj* other = candidates[j];
			if (party == other) {
				continue;
			}
			comboLinks[linkCount++] = other;
		}
		CharaObjComboLinkCount(party) = static_cast<float>(linkCount);
	}

	combi2();
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
	CGame* linkCursor = &Game;
	int linkCount = *reinterpret_cast<int*>(&Game.m_gameWork.m_linkTable[3][0][0]);

	while (entry < linkCount) {
		int linkHead = *reinterpret_cast<int*>(&linkCursor->m_gameWork.m_linkTable[3][0][0]);
		CGPrgObj* obj = *reinterpret_cast<CGPrgObj**>(linkHead + 4);
		bool skip = (obj == 0);

		if (!skip) {
			if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
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

	unsigned short* combiCursor = reinterpret_cast<unsigned short*>(Game.unk_flat3_field_1C_0xc7d8);
	for (int combiIndex = 0; combiIndex < Game.unk_flat3_count_0xc7d4; combiIndex++, combiCursor += 0xD) {
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
					*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (objParticle * 0x48));
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
