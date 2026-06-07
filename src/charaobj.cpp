#include "ffcc/ptrarray.h"
#include "ffcc/charaobj.h"
#include "ffcc/astar.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/fontman.h"
#include "ffcc/gobjwork.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/monobj.h"
#include "ffcc/partyobj.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_minigame.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/vector.h"
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern char SoundBuffer[];

extern "C" char sCharaObjDebugStatFormat[];
extern "C" char s_CGCharaObj_801DC548[];
extern "C" char lbl_801DC590[];
extern "C" char lbl_801DC8CC[];
extern "C" char lbl_801DC8D8[];
extern "C" char lbl_801DC8EC[];
extern "C" char lbl_801DC908[];
extern "C" char lbl_801DC940[];

static Vec* l_pHitCross = 0;
static int l_idxAttackCol = 0;
int gCGCharaObjCreateSerial = 0;
char gCGCharaObjCreateSerialInit = 0;
extern "C" {
extern const float kOneF32;
extern const float kHalfF32;
extern const float FLOAT_80331988;
extern const float FLOAT_803319A8;
extern const float FLOAT_803319AC;
extern const float FLOAT_8033198C;
extern const float FLOAT_80331990;
extern const float FLOAT_80331994;
extern const float FLOAT_80331998;
extern const float FLOAT_8033199C;
extern const float FLOAT_803319A0;
extern const float FLOAT_803319A4;
}

static float& CharaObjTargetAngle(CGCharaObj* charaObj)
{
	return charaObj->m_targetAngle;
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
	return slot & ~((~(Pad.m_debugPadPort - static_cast<int>(slot) | static_cast<int>(slot) - Pad.m_debugPadPort) >> 31));
}

static bool CharaObjUseDebugPad(unsigned char slot)
{
	return (Pad.m_debugPadLock != 0) || ((slot == 0) && (Pad.m_debugPadPort != -1));
}

static unsigned short CharaObjGetPadState(unsigned char slot, int baseOffset)
{
	if (CharaObjUseDebugPad(slot)) {
		return 0;
	}

	int idx = CharaObjGetPadSlotIndex(slot);
	const CPad::PadInput& input = Pad.GetPadInputs()[idx];
	if (baseOffset == 0x4) {
		return input.button[0];
	}
	if (baseOffset == 0x8) {
		return input.buttonDown[0];
	}

	return input.repeatButton;
}

static unsigned short CharaObjGetPadHeld(unsigned char slot)
{
	return CharaObjGetPadState(slot, 0x4);
}

static unsigned short CharaObjGetPadStatusReduceMask(unsigned char slot)
{
	unsigned short mask = CharaObjGetPadState(slot, 0x8);
	unsigned int miniGameFlags = MiniGamePcs.m_flags;
	if ((miniGameFlags & 0x100) != 0) {
		mask |= CharaObjGetPadState(slot, 0x10);
	}

	return mask;
}

static void CharaObjEndSlots(CGCharaObj* charaObj, unsigned int slotMask)
{
	for (int i = 0; i < 0x16; i++) {
		if ((slotMask & (1U << i)) != 0) {
			CFlatRuntime2Storage().EndParticleSlot(charaObj->m_particleSlots[i], 1);
		}
	}
}

static int CharaObjGetModelPdtNo(CGCharaObj* charaObj)
{
	if (charaObj->m_charaModelHandle->m_pdtLoadRef == 0) {
		return -1;
	}
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(charaObj->m_charaModelHandle->m_pdtLoadRef) + 0x14);
}

struct CharaObjModelAnimState
{
	unsigned char m_padB4[0xB4];
	float m_time;
	unsigned char m_padBC[4];
	float m_animStart;
	float m_animEnd;
	unsigned char m_padC8[0xC];
	CChara::CAnim* m_anim;
};

static bool CharaObjIsAttackAnimBoundary(CGCharaObj* charaObj)
{
	if (charaObj->m_charaModelHandle == 0 || charaObj->m_charaModelHandle->m_model == 0) {
		return true;
	}

	CharaObjModelAnimState* model = reinterpret_cast<CharaObjModelAnimState*>(charaObj->m_charaModelHandle->m_model);
	if (model->m_anim == 0) {
		return true;
	}

	int span = static_cast<int>(kOneF32 + (model->m_animEnd - model->m_animStart));
	if (span == 1) {
		return true;
	}

	int frame = static_cast<int>(charaObj->m_turnSpeed);
	if (FLOAT_80331988 <= charaObj->m_lastBgAttr) {
		return span <= frame;
	}

	return (frame % span) == 0;
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
	return charaObj->m_comboCenter;
}

static Vec& CharaObjComboTarget(CGCharaObj* charaObj)
{
	return charaObj->m_comboTarget;
}

static int& CharaObjComboItemState(CGCharaObj* charaObj)
{
	return charaObj->m_comboItemState;
}

static int& CharaObjComboScriptArg(CGCharaObj* charaObj)
{
	return charaObj->m_comboScriptArg;
}

static unsigned int& CharaObjComboScriptMode(CGCharaObj* charaObj)
{
	return charaObj->m_comboScriptMode;
}

static int& CharaObjComboLinkCount(CGCharaObj* charaObj)
{
	return charaObj->m_comboLinkCount;
}

static CGPrgObj** CharaObjComboLinks(CGCharaObj* charaObj)
{
	return charaObj->m_comboLinks;
}

static unsigned char& CharaObjComboFlags(CGPartyObj* party)
{
	return party->m_partyData.partyFlags;
}

static bool CharaObjSkipComboScript(CGPrgObj* obj)
{
	if (obj == 0) {
		return true;
	}

	if (Game.m_gameWork.m_menuStageMode == 0 || Game.m_gameWork.m_bossArtifactStageIndex >= 0xF) {
		return false;
	}

	return ((static_cast<unsigned short>(obj->GetCID()) & 0x6D) == 0x6D) &&
	       (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(obj->m_scriptHandle) + 0x3B4) != 0);
}

static bool CharaObjIsPlayerCid(unsigned int cid)
{
	return (cid & 0x6D) == 0x6D;
}

static bool CharaObjIsElementalStatus(int staType)
{
	return staType == 4 || staType == 0x1C || staType < 3 ||
	       static_cast<unsigned int>(staType - 8) <= 2 || staType == 6 || staType == 3;
}

static bool CharaObjIsBreakStatus(int staType)
{
	return static_cast<unsigned int>(staType - 0x24) <= 1 || staType == 0x69 || staType == 0x6A;
}

struct CharaObjIgnoreFlagBits
{
	unsigned char m_active : 1;
	unsigned char m_pad : 7;
};

static bool CharaObjCanFrontGuard(CGCharaObj* self, CGPrgObj* sourceObj)
{
	CVector selfPos(self->m_worldPosition);
	CVector sourcePos(sourceObj->m_worldPosition);
	CVector deltaVec;
	PSVECSubtract(reinterpret_cast<Vec*>(&sourcePos), reinterpret_cast<Vec*>(&selfPos), reinterpret_cast<Vec*>(&deltaVec));

	Vec delta;
	delta.x = deltaVec.x;
	delta.y = deltaVec.y;
	delta.z = deltaVec.z;
	float mag = PSVECMag(&delta);
	if (mag <= 0.0f) {
		return false;
	}

	CVector scaledVec;
	PSVECScale(&delta, reinterpret_cast<Vec*>(&scaledVec), 1.0f / mag);
	Vec scaledDelta;
	scaledDelta.x = scaledVec.x;
	scaledDelta.y = scaledVec.y;
	scaledDelta.z = scaledVec.z;

	CVector facing;
	facing.x = sinf(self->m_rotBaseY);
	facing.y = 0.0f;
	facing.z = cosf(self->m_rotBaseY);
	float dot = PSVECDotProduct(&scaledDelta, reinterpret_cast<Vec*>(&facing));
	return dot > 0.0f;
}

static unsigned int CharaObjResolveHitParticleBank(CGPrgObj* sourceObj, unsigned int particleBank)
{
	if (particleBank == 0xFE) {
		int sourceData = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0xF8);
		int effectData = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceData) + 0x178);
		return effectData != 0 ? *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(effectData) + 0x14)
		                       : 0xFFFFFFFF;
	}

	if (particleBank == 0xFD) {
		return 0xFFFFFFFF;
	}

	return particleBank;
}

static int CharaObjDecodeHitParticleSe(unsigned short seData)
{
	return (seData == 0xFFFF) ? 0 : (seData & 0xFF) + static_cast<int>(seData >> 8) * 1000;
}

static int CharaObjDecodeSe(unsigned short encodedSe)
{
	if (encodedSe == 0 || encodedSe == 0xFFFF) {
		return 0;
	}
	return (encodedSe & 0xFF) + ((encodedSe >> 8) * 1000);
}

static unsigned int CharaObjResolveParticleBank(CGCharaObj* charaObj, unsigned int particleClass)
{
	if (particleClass == 0xFE) {
		int pdtNo = CharaObjGetModelPdtNo(charaObj);
		return (pdtNo >= 0) ? static_cast<unsigned int>(pdtNo) : 0xFFFFFFFF;
	} else if (particleClass >= 0xFD && particleClass <= 0xFF) {
		return 0xFFFFFFFF;
	} else {
		return particleClass;
	}
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

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int createSerial = gCGCharaObjCreateSerial;
	gCGCharaObjCreateSerial = createSerial + 1;
	*reinterpret_cast<int*>(self + 0x54C) = createSerial;

	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x63C)->m_active = 0;
	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x640)->m_active = 0;
	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x648)->m_active = 0;
	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x650)->m_active = 0;
	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x658)->m_active = 0;
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
		m_particleSlots[i] = CFlatRuntime2Storage().GetFreeParticleSlot();
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
	switch (state) {
		case 9:
			for (int i = 0; i < 0x27; i++) {
				setSta(i, 0);
			}
			m_displayFlags |= 2;
			break;

		case 2:
		case 6:
			m_castTimeTick = 0;
			m_stateResetCounter = 0;
			m_stateResetLimit = -1;
			break;
	}

	reinterpret_cast<unsigned char*>(this)[0x63C] =
		static_cast<unsigned char>(reinterpret_cast<unsigned char*>(this)[0x63C] << 1) >> 1;
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

	if (state == 6) {
		goto cancel_damage;
	}
	if (state < 6) {
		if (state == 2) {
			goto cancel_state2;
		}
		goto cancel_done;
	}
	if (state == 0x12) {
		goto cancel_state18;
	}
	goto cancel_done;

cancel_state18:
	{
		unsigned char* self = reinterpret_cast<unsigned char*>(this);
		int i = 0;
		for (; i < 0x16; i++, self += 4) {
			if (((1U << i) & 1U) != 0) {
				CFlatRuntime2Storage().EndParticleSlot(*reinterpret_cast<int*>(self + 0x564), 1);
			}
		}
	}
	goto cancel_done;

cancel_state2:
	{
		unsigned char* self = reinterpret_cast<unsigned char*>(this);
		int i = 0;
		for (; i < 0x16; i++, self += 4) {
			if (((1U << i) & 0x18U) != 0) {
				CFlatRuntime2Storage().EndParticleSlot(*reinterpret_cast<int*>(self + 0x564), 1);
			}
		}
	}
	goto cancel_done;

cancel_damage:
	{
		unsigned char* self = reinterpret_cast<unsigned char*>(this);
		int i = 0;
		for (; i < 0x16; i++, self += 4) {
			if (((1U << i) & 0x138U) != 0) {
				CFlatRuntime2Storage().EndParticleSlot(*reinterpret_cast<int*>(self + 0x564), 1);
			}
		}
	}
	m_damageParticle = -1;

cancel_done:
	m_comboFrame = 0;
	m_comboState = 0;

	enableAttackCol(0, 0, 0);
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
	if (*reinterpret_cast<short*>(script + 0x42) != 0) {
		unsigned short tickDiv = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x3A);
		if (m_stateTick != 0 && (m_stateTick % static_cast<int>(tickDiv)) == 0) {
			if (*reinterpret_cast<unsigned short*>(script + 0x1C) > 1 &&
			    (CFlatGameFlags() & CFlatGameFlag_Bit5) == 0) {
				playSe3D(0x19, 0x32, 0x96, 0, 0);
				addHp(-1, 0);
			}
		}
	}

	for (int i = 0, statusOffset = 0; i < 0x27; i++, statusOffset += 2) {
		int statusValue = static_cast<int>(*reinterpret_cast<unsigned short*>(script + 0x3E + statusOffset)) - 1;
		if (statusValue != 0 && i == 2) {
			m_stateTick += 1;
		}

		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		    (i == 0 || i == 4 || i == 9 || i == 3) &&
		    statusValue > 0) {
			char slot = m_animStateMisc;
			unsigned short padMask = 0;
			bool useDebugPad = (Pad.m_debugPadLock != 0) || ((slot == 0) && (Pad.m_debugPadPort != -1));
			if (!useDebugPad) {
				int idx = slot & ~((~(Pad.m_debugPadPort - static_cast<int>(slot) | static_cast<int>(slot) - Pad.m_debugPadPort)) >> 31);
				padMask = Pad.GetPadInputs()[idx].buttonDown[0];
			}
			if ((MiniGamePcs.m_flags & 0x100) != 0) {
				useDebugPad = (Pad.m_debugPadLock != 0) || ((slot == 0) && (Pad.m_debugPadPort != -1));
				unsigned short heldMask = 0;
				if (!useDebugPad) {
					int idx = slot & ~((~(Pad.m_debugPadPort - static_cast<int>(slot) | static_cast<int>(slot) - Pad.m_debugPadPort)) >> 31);
					heldMask = Pad.GetPadInputs()[idx].repeatButton;
				}
				padMask |= heldMask;
			}
			if ((padMask & 0xF) != 0) {
				statusValue -= *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x3C);
				System.Printf(const_cast<char*>(lbl_801DC940));
			}
		}

		setSta(i, statusValue);
	}

	script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	if (*reinterpret_cast<unsigned short*>(script + 0x3E) == 0 &&
	    *reinterpret_cast<unsigned short*>(script + 0x50) == 0 &&
	    *reinterpret_cast<unsigned short*>(script + 0x44) == 0) {
		m_displayFlags |= 2;
	} else {
		m_displayFlags &= ~2;
		reinterpret_cast<unsigned char*>(this)[0x63C] &= 0x7F;
	}

	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x38) += 1;

	if ((static_cast<signed char>(m_ignoreHit[0].m_flag) < 0) && m_ignoreHit[0].m_timer != 0) {
		m_ignoreHit[0].m_timer = static_cast<unsigned short>(m_ignoreHit[0].m_timer - 1);
		if (m_ignoreHit[0].m_timer == 0) {
			m_ignoreHit[0].m_flag &= 0x7F;
		}
	}
	if ((static_cast<signed char>(m_ignoreHit[1].m_flag) < 0) && m_ignoreHit[1].m_timer != 0) {
		m_ignoreHit[1].m_timer = static_cast<unsigned short>(m_ignoreHit[1].m_timer - 1);
		if (m_ignoreHit[1].m_timer == 0) {
			m_ignoreHit[1].m_flag &= 0x7F;
		}
	}
	if ((static_cast<signed char>(m_ignoreHit[2].m_flag) < 0) && m_ignoreHit[2].m_timer != 0) {
		m_ignoreHit[2].m_timer = static_cast<unsigned short>(m_ignoreHit[2].m_timer - 1);
		if (m_ignoreHit[2].m_timer == 0) {
			m_ignoreHit[2].m_flag &= 0x7F;
		}
	}
	if ((static_cast<signed char>(m_ignoreHit[3].m_flag) < 0) && m_ignoreHit[3].m_timer != 0) {
		m_ignoreHit[3].m_timer = static_cast<unsigned short>(m_ignoreHit[3].m_timer - 1);
		if (m_ignoreHit[3].m_timer == 0) {
			m_ignoreHit[3].m_flag &= 0x7F;
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
		CharaObjTargetAngle(this) = reinterpret_cast<CVector*>(&m_targetDelta)->GetRotateY();
	}

	for (int i = 0; i < 4; i++) {
		CGPartyObj* partyObj = Game.m_partyObjArr[i];
		if (partyObj != 0) {
			PSVECSubtract(&partyObj->m_worldPosition, &m_worldPosition, &m_partyDelta[i]);
			m_partyDistance[i] = PSVECMag(&m_partyDelta[i]);
			m_partyAngle[i] = reinterpret_cast<CVector*>(&m_partyDelta[i])->GetRotateY();
		} else {
			m_partyDistance[i] = FLOAT_80331988;
			m_partyDelta[i].z = FLOAT_80331988;
			m_partyDelta[i].y = FLOAT_80331988;
			m_partyDelta[i].x = FLOAT_80331988;
			m_partyAngle[i] = FLOAT_80331988;
		}

		m_partyRank[i] = 0;
		for (int j = 0; j < i; j++) {
			if (m_partyDistance[i] == 0.0f) {
				m_partyRank[i] += 1;
			} else if (m_partyDistance[j] == 0.0f) {
				m_partyRank[j] += 1;
			} else if (m_partyDistance[i] >= m_partyDistance[j]) {
				m_partyRank[i] += 1;
			} else {
				m_partyRank[j] += 1;
			}
		}
	}

	m_pushScale = 1.0f;
	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	if (*reinterpret_cast<unsigned short*>(script + 0x4E) != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x34)) * 0.01f) + kOneF32;
	}
	if (*reinterpret_cast<short*>(script + 0x4C) != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x36)) * 0.01f) + kOneF32;
	}
	if (*reinterpret_cast<short*>(script + 0x40) != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x40)) * 0.01f) + kOneF32;
	}
	float pushScale = 1.5f;
	if (m_pushScale < 1.5f) {
		pushScale = m_pushScale;
	}
	m_pushScale = pushScale;

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

	if (*reinterpret_cast<unsigned short*>(script + 0x3E) != 0 ||
	    *reinterpret_cast<unsigned short*>(script + 0x50) != 0 ||
	    *reinterpret_cast<unsigned short*>(script + 0x44) != 0) {
		push += 0x19;
	}

	unsigned short cid = GetCID();
	if ((cid & 0x6D) == 0x6D) {
		if (static_cast<CGPartyObj*>(this)->m_partyData.carryObject != nullptr) {
			push += 10;
		}
		unsigned char slot = m_animStateMisc;
		int padHeld = 0;
		bool useDebugPad = (Pad.m_debugPadLock != 0) || ((slot == 0) && (Pad.m_debugPadPort != -1));
		if (!useDebugPad) {
			int idx = slot & ~((~(Pad.m_debugPadPort - static_cast<int>(slot) | static_cast<int>(slot) - Pad.m_debugPadPort)) >> 31);
			padHeld = Pad.GetPadInputs()[idx].gbaMode;
		}
		if (padHeld != 0) {
			push += 0x19;
		}
		if (static_cast<signed char>(reinterpret_cast<unsigned char*>(this)[0x9B]) >= 0) {
			push += 0x19;
		}
	}

	m_pushParamB = static_cast<unsigned char>(push < 0x19 ? push : 0x19);
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && static_cast<CGMonObj*>(this)->m_chaseState == 4) {
		m_pushParamB = 100;
	}

	if ((DbgMenuPcs.GetDbgFlagsRaw() & 1) != 0) {
		m_aStarGroupId = static_cast<unsigned short>(AStar.calcSpecialPolygonGroup(&m_worldPosition));
	} else {
		m_aStarGroupId = static_cast<unsigned short>(static_cast<unsigned char>(m_lastBgGroup));
	}
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
	float alpha = m_alpha;

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		if (((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		     *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) ||
		    ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		     (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0 &&
		     static_cast<CGMonObj*>(this)->m_unk6BA == 0)) {
			int createSerial = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x54C);
			float alphaWave = static_cast<float>(sin(static_cast<double>(0.1f * static_cast<float>(createSerial))));
			float alphaDelta = 0.05f * alphaWave;
			alpha = alpha + alphaDelta;
		}
	}

	float slope = m_stepSlopeLimit;
	if (alpha < 0.0f) {
		alpha = 0.0f;
	}
	if (1.0f < alpha) {
		alpha = 1.0f;
	}
	return slope * alpha;
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
	for (int i = 0; i < 0x16; i++) {
		if ((static_cast<unsigned int>(slotMask) & (1U << i)) != 0) {
			CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
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
	for (int i = 0; i < 0x16; i++) {
		if (((unsigned int)slotMask & (1U << i)) != 0) {
			CFlatRuntime2Storage().DeleteParticleSlot(m_particleSlots[i], 1);
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
	if (m_stateFrameGate != 0) {
		return;
	}

	switch (m_lastStateId) {
		case 1:
		case 0x12:
			statAttack();
			break;

		case 2:
			if (m_subState == 1) {
				if (m_subFrame == 0) {
					reqAnim(m_unk554, 1, 0);
				}
			} else if (m_subState < 1) {
				if (m_subState >= 0) {
					if (m_subFrame == 0) {
						reqAnim(m_attackAnimId, 0, 0);
					}

					if (isLoopAnim() != 0) {
						if (m_itemId == 0x103) {
							changeSubStat(2);
						} else {
							changeSubStat(1);
						}
						return;
					}
				}
			} else if (m_subState < 3) {
				if (m_subFrame == 0) {
					for (int i = 0; i < 0x16; i++) {
						if ((8U & (1U << i)) != 0) {
							CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
						}
					}
					reqAnim(m_unk558, 0, 0);
				}

				if (m_itemId != 0 && m_subFrame == 10) {
					for (int i = 0; i < 0x16; i++) {
						if ((2U & (1U << i)) != 0) {
							CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
						}
					}
					putParticleFromItem(m_itemId, 2, m_particleSlots[1], &CharaObjComboCenter(this));
					putParticleFromItem(m_itemId, 3, m_particleSlots[1], &CharaObjComboCenter(this));
				}
			}

			onStatMagic();
			break;

		case 4:
			if (m_stateFrame == 0) {
				Sound.StopSe3DGroup(m_particleId);
				for (int i = 0; i < 0x16; i++) {
					if ((0x3BU & (1U << i)) != 0) {
						CFlatRuntime2Storage().DeleteParticleSlot(m_particleSlots[i], 1);
					}
				}
				reqAnim(4, 0, 0);
			}

			if (isLoopAnim() != 0) {
				changeStat(0, 0, 0);
			}
			break;

		case 8:
			if (m_subState == 2) {
				if (m_subFrame == 0) {
					reqAnim(m_unk558, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeSubStat(1);
					return;
				}
			} else if (m_subState == 0) {
				if (m_subFrame == 0) {
					reqAnim(m_attackAnimId, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeSubStat(1);
					return;
				}
			} else if (m_subState == 1) {
				if (m_subFrame == 0) {
					reqAnim(m_unk554, 1, 0);
				}
			} else if (m_subState < 4) {
				if (m_subFrame == 0) {
					reqAnim(((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) ? m_unk558 : m_unk55C, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeStat(0, 0, 0);
					return;
				}
			}

			onStatShield();
			break;

		case 9:
			if (m_subState == 0 && m_subFrame == 0) {
				Sound.StopSe3DGroup(m_particleId);
				for (int i = 0; i < 0x16; i++) {
					if ((0x3BU & (1U << i)) != 0) {
						CFlatRuntime2Storage().DeleteParticleSlot(m_particleSlots[i], 1);
					}
				}
				reqAnim(6, 1, 0);

				if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
					playSe3D(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) + 0x10,
					         0x32, 0x96, 0, 0);
				}
			}

			onStatDie();
			break;

		case 0xA:
			if (m_subState == 1) {
				if (m_subFrame == 0) {
					reqAnim(0x1B, 1, 0);
				}

				if (m_scriptHandle != 0 &&
				    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x46) == 0) {
					changeSubStat(2);
				}
			} else if (m_subState == 0) {
				if (m_subFrame == 0) {
					Sound.StopSe3DGroup(m_particleId);
					for (int i = 0; i < 0x16; i++) {
						if ((0x3BU & (1U << i)) != 0) {
							CFlatRuntime2Storage().DeleteParticleSlot(m_particleSlots[i], 1);
						}
					}
					reqAnim(0x1A, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeSubStat(1);
				}
			} else if (m_subState < 3) {
				if (m_subFrame == 0) {
					reqAnim(0x1C, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeStat(0, 0, 0);
				}
			}
			break;

		case 0x19:
			if (m_stateFrame == 0) {
				if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
					static_cast<CGPartyObj*>(this)->carry(1, 0, 1);
				}

				Sound.StopSe3DGroup(m_particleId);
				for (int i = 0; i < 0x16; i++) {
					if ((0x3BU & (1U << i)) != 0) {
						CFlatRuntime2Storage().DeleteParticleSlot(m_particleSlots[i], 1);
					}
				}
				reqAnim(0x1D, 0, 0);
			}

			if (isLoopAnim() != 0) {
				changeStat(0, 0, 0);
			}
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
	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x640)->m_active = 0;
	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x648)->m_active = 0;
	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x650)->m_active = 0;
	reinterpret_cast<CharaObjIgnoreFlagBits*>(self + 0x658)->m_active = 0;
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
	Sound.StopSe3DGroup(m_particleId);
	int i = 0;
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	for (; i < 0x16; i++, self += 4) {
		if (((1U << i) & 0x3bU) != 0) {
			CFlatRuntime2Storage().DeleteParticleSlot(*reinterpret_cast<int*>(self + 0x564), 1);
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
int CGCharaObj::onHit(int hitArg, CGObject* sourceObj, int hitType, Vec* hitPos)
{
	unsigned short sourceCid = sourceObj->GetCID();
	if ((sourceCid & 0x6D) == 0x6D && Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		sourceCid = sourceObj->GetCID();
		if ((sourceCid & 0x6D) == 0x6D && sourceObj->m_scriptHandle[0xED] != 0) {
			return 0;
		}
	}

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int slot = 4;
	for (int i = 0; i < 4; i++) {
		IgnoreHitSlot& slotData = m_ignoreHit[i];
		unsigned char flag = slotData.m_flag;
		if ((flag & 0x80) != 0) {
			if (slotData.m_source == sourceObj) {
				return 2;
			}
		} else {
			slot = i;
			slotData.m_flag = static_cast<unsigned char>((flag & 0x7F) | 0x80);
			slotData.m_source = sourceObj;

			unsigned int particleIndex = static_cast<unsigned int>(m_itemId);
			unsigned short particleLife =
				*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (particleIndex * 0x48) + 0xE);
			slotData.m_timer = (particleLife == 3) ? 0x1E : 0;
			break;
		}
	}

	if (slot == 4) {
		return 2;
	}

	if ((sourceObj->m_objectFlags & 0x100) != 0) {
		changeStat(3, 0, 0);
	}

	sourceCid = sourceObj->GetCID();
	if ((sourceCid & 0x2D) == 0x2D) {
		static_cast<CGCharaObj*>(sourceObj)->onDamage(this, m_itemId, hitArg, hitType, hitPos);
	}

	return 1;
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
	unsigned short cid = GetCID();

	if ((cid & 0x6D) == 0x6D && Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		cid = GetCID();
		if ((cid & 0x6D) == 0x6D && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) != 0) {
			return;
		}
	}

	int particleIndex = hitParam->m_particleIndex;
	int classId = hitParam->m_classId;
	CGPrgObj* sourceObj;
	if (classId != 0) {
		sourceObj = reinterpret_cast<CGPrgObj*>(CFlatRuntime2Storage().intToClass(classId));
	} else {
		sourceObj = 0;
	}

	unsigned short sourceCid = sourceObj->GetCID();
	if ((sourceCid & 0xD) == 0xD) {
		onDamage(sourceObj, particleIndex, -1, colliderIndex, hitPos);
	}

	CFlatRuntime2Storage().IgnoreParticle(effectIndex, this);
	int particleFlagOffset = particleIndex * 0x48 + 0xC;
	if ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + particleFlagOffset) & 0x100) != 0) {
		PartMng.pppEndPart(effectIndex);
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
void CGCharaObj::putHitParticleFromItem(CGPrgObj* sourceObj, int itemId)
{
	int particleOffset = 0;
	unsigned int particleBank;
	unsigned short particleSpec;
	unsigned short particleFlags;
	unsigned short seSpec;

	if (itemId == 0x1FA || itemId == 0x237) {
		particleOffset = l_idxAttackCol;
	}

	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + itemId * 0x48;
	particleBank = static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(itemData + 0x12));
	if (particleBank != 0xFFFF && particleBank != 0xFF) {
		if (particleBank == 0xFE) {
			int sourceData = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0xF8);
			int effectData = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceData) + 0x178);
			particleBank = effectData != 0 ? *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(effectData) + 0x14)
			                               : 0xFFFFFFFF;
		}
		if (particleBank == 0xFD) {
			particleBank = 0xFFFFFFFF;
		}
		particleSpec = *reinterpret_cast<unsigned short*>(itemData + 0x1C);
		if (particleSpec != 0xFFFF) {
			if ((particleSpec & 0x1000) != 0) {
				particleBank = 1;
			} else if ((particleSpec & 0x2000) != 0) {
				particleBank = 2;
			} else if ((particleSpec & 0x4000) != 0) {
				particleBank = 3;
			}

			CFlatRuntime2Storage().ResetParticleWork((particleBank << 8) | ((particleSpec & 0xFF) + particleOffset), 0);
			particleFlags = *reinterpret_cast<unsigned short*>(itemData + 0x0C);
			if ((particleFlags & 0x200) != 0) {
				CFlatRuntime2Storage().SetParticleWorkBind(sourceObj);
			} else {
				CFlatRuntime2Storage().SetParticleWorkPos(*l_pHitCross, 1.0f);
			}
			CFlatRuntime2Storage().PutParticleWork();
		}
	}

	seSpec = *reinterpret_cast<unsigned short*>(itemData + 0x42);
	int seNo = CharaObjDecodeHitParticleSe(seSpec);
	if (seNo != 0) {
		playSe3D(seNo + particleOffset, 0x32, 0x96, 0, 0);
	}
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
void CGCharaObj::onDamage(CGPrgObj* sourceObj, int itemId, int attackColIndex, int, Vec* hitPos)
{
	l_pHitCross = hitPos;
	l_idxAttackCol = attackColIndex;

	int resolvedItemId = itemId;
	int staType;
	int resistType;
	int allowEffect;
	int damageClamp;
	int effectResult;
	char* dbg = s_CGCharaObj_801DC548;

	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x48) != 0) {
		System.Printf(dbg + 0xF0);
		return;
	}
	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && (DbgMenuPcs.GetDbgFlagsRaw() & 4) != 0) {
		System.Printf(dbg + 0x118);
		return;
	}
	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && *reinterpret_cast<short*>(&m_lastMapIdHit) != 1) {
		System.Printf(dbg + 0x138);
		return;
	}
	if (static_cast<int>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&m_weaponNodeFlags)) << 0x18) >= 0) {
		System.Printf(dbg + 0x160);
		return;
	}

	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + resolvedItemId * 0x48;
	staType = *reinterpret_cast<unsigned short*>(itemData + 8);
	if (static_cast<int>(staType) != 0x67 && static_cast<int>(staType) != 0x65 && static_cast<int>(staType) != 0x66 && (CFlatGameFlags() & CFlatGameFlag_Bit5) != 0) {
		System.Printf(dbg + 0x17C);
		return;
	}

	unsigned int particleLife = particleLife;
	unsigned short itemEffect = *reinterpret_cast<unsigned short*>(itemData);
	short scriptDefense = scriptDefense;
	calcRegist(static_cast<int>(staType), resolvedItemId, resistType, allowEffect, effectResult, 0);

	if (resistType == 3) {
		if (CharaObjIsElementalStatus(staType)) {
			putParticle(0x201, 0, hitPos, FLOAT_803319A8 * (FLOAT_803319AC * m_attackColRadius), 0x65);
		} else if (CharaObjIsBreakStatus(staType)) {
			putParticle(0x200, 0, hitPos, FLOAT_803319A8 * (FLOAT_803319AC * m_attackColRadius), 0x1D);
		}
	} else if ((resistType > 1 || (resistType == 1 &&
	           ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + resolvedItemId * 0x48 + 0x32) & 1) == 0))) &&
	           (static_cast<unsigned int>(staType - 8) <= 1 || staType == 6 || staType == 3)) {
		putParticle(0x201, 0, hitPos, FLOAT_803319A8 * (FLOAT_803319AC * m_attackColRadius), 0x65);
	}

	damageClamp = 0;
	if (m_lastStateId == 8 && m_subState == 1 &&
	    ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + resolvedItemId * 0x48 + 0x2C) & 8) == 0)) {
		CVector selfPos(m_worldPosition);
		CVector sourcePos(sourceObj->m_worldPosition);
		CVector deltaVec;
		PSVECSubtract(reinterpret_cast<Vec*>(&sourcePos), reinterpret_cast<Vec*>(&selfPos), reinterpret_cast<Vec*>(&deltaVec));
		Vec frontDelta;
		frontDelta.x = deltaVec.x;
		frontDelta.y = deltaVec.y;
		frontDelta.z = deltaVec.z;
		float frontMag = PSVECMag(&frontDelta);
		if (FLOAT_80331988 < frontMag) {
			CVector scaledVec;
			PSVECScale(&frontDelta, reinterpret_cast<Vec*>(&scaledVec), kOneF32 / frontMag);
			frontDelta.x = scaledVec.x;
			frontDelta.y = scaledVec.y;
			frontDelta.z = scaledVec.z;
			CVector facing;
			facing.x = sinf(m_rotBaseY);
			facing.y = FLOAT_80331988;
			facing.z = cosf(m_rotBaseY);
			if (FLOAT_80331988 < PSVECDotProduct(&frontDelta, reinterpret_cast<Vec*>(&facing))) {
				playSe3D(0x1D, 0x32, 0x96, 0, 0);
				putParticle(0x200, 0, hitPos, FLOAT_803319AC * m_attackColRadius, 0);
				if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D) {
					sourceObj->changeStat(0x13, 0, 0);
				}
				if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
					changeSubStat(2);
					if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) == 0) {
						effectResult = 0;
					} else {
						damageClamp = 1;
					}
				} else {
					effectResult = 0;
				}
				allowEffect = 0;
			}
		}
	}

	if (m_lastStateId == 6 &&
	    static_cast<int>((static_cast<unsigned int>(*(reinterpret_cast<unsigned char*>(&m_weaponNodeFlags) + 1)) << 0x1A) |
	                     (static_cast<unsigned int>(*(reinterpret_cast<unsigned char*>(&m_weaponNodeFlags) + 1)) >> 6)) < 0) {
		int currentKind =
			*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + m_itemId * 0x48 + 0x0A) & 0xFF;
		if (currentKind == 2) {
			if (staType != 0x66 && staType != 0x67 && staType != 7) {
				CVector sourcePos(sourceObj->m_worldPosition);
				CVector selfPos(m_worldPosition);
				CVector deltaVec;
				PSVECSubtract(reinterpret_cast<Vec*>(&selfPos), reinterpret_cast<Vec*>(&sourcePos), reinterpret_cast<Vec*>(&deltaVec));
				Vec delta;
				delta.x = deltaVec.x;
				delta.y = deltaVec.y;
				delta.z = deltaVec.z;
				moveVectorH(&delta, 10.0f, 10);
				m_rotTargetY = static_cast<float>(atan2(-static_cast<double>(delta.x), -static_cast<double>(delta.z)));
				changeStat(0x1A, 0, 0);
			}
		} else if (currentKind == 3) {
			allowEffect = 0;
			effectResult = 0;
		}
	}

	if (itemEffect == 0x1F8 && (sourceObj->m_weaponNodeFlags & 0x20) != 0 &&
	    ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + m_itemId * 0x48 + 0x0A) & 0xFF) == 3)) {
		CVector sourcePos(sourceObj->m_worldPosition);
		CVector selfPos(m_worldPosition);
		CVector deltaVec;
		PSVECSubtract(reinterpret_cast<Vec*>(&selfPos), reinterpret_cast<Vec*>(&sourcePos), reinterpret_cast<Vec*>(&deltaVec));
		Vec delta;
		delta.x = deltaVec.x;
		delta.y = deltaVec.y;
		delta.z = deltaVec.z;
		moveVectorH(&delta, 10.0f, 10);
		m_rotTargetY = static_cast<float>(atan2(-static_cast<double>(delta.x), -static_cast<double>(delta.z)));
		changeStat(0x19, 0, 0);
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x74) != 0) {
		allowEffect = 0;
		effectResult = 0;
	}
	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x44) != 0) {
		allowEffect = 0;
	}
	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x50) != 0 && (staType == 8 || staType == 7)) {
		allowEffect = 0;
		effectResult = 0;
	}
	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
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

	int damageAmount = 0;
	if (effectResult != 0) {
		int itemKind = 1;
		if (resolvedItemId >= 0x1F5) {
			itemKind = *reinterpret_cast<short*>(itemData + 2);
		}

		if (itemKind == 1 || (itemKind == 9 && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D)) {
			switch (staType) {
			case 0:
			case 1:
			case 4:
			case 0x1C: {
				unsigned int basePower = *reinterpret_cast<unsigned short*>(itemData + 6);
				CGPrgObj* powerSource = sourceObj;
				if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
				    (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && sourceObj->m_scriptHandle[0xED] != 0) {
					powerSource = Game.m_partyObjArr[0];
				}

				unsigned int sourcePower = *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(powerSource->m_scriptHandle) + 0x20);
				float multiplier = CharaObjGetStatusMultiplier(0x2E);
				unsigned int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				int rawDamage = static_cast<int>(multiplier * static_cast<float>(basePower + sourcePower)) - defense;
				if (rawDamage < 1) {
					rawDamage = 1;
				}
				unsigned int bonus = (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D ?
					static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(
						reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0xBDE)) :
					0;
				damageAmount = rawDamage + bonus;
				System.Printf(dbg + 0x1DC, basePower, sourcePower, defense, bonus, damageAmount);
				break;
			}
			case 0x24:
			case 0x25:
			case 100:
			case 0x69:
			case 0x6A: {
				unsigned int basePower = (itemEffect == 0x1F8) ?
					*reinterpret_cast<unsigned short*>(itemData + 6) :
					0;
				if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && resolvedItemId == 0x206) {
					int castCurrent = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0x68C);
					int castEnd = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0x664);
					if (castCurrent * 3 <= castEnd) {
						basePower <<= 2;
					} else if (castCurrent * 2 <= castEnd) {
						basePower <<= 1;
					}
				}

				unsigned int sourcePower = *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x1E);
				float multiplier = CharaObjGetStatusMultiplier(0x2C);
				unsigned int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				int rawDamage = static_cast<int>(multiplier * static_cast<float>(basePower + sourcePower)) - defense;
				if (rawDamage < 1) {
					rawDamage = 1;
				}
				unsigned int bonus = ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && itemEffect == 0x1F8) ?
					static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(
						reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0xBDD)) :
					0;
				damageAmount = rawDamage + bonus;
				if (scriptDefense != 0) {
					damageAmount = static_cast<int>(static_cast<float>(damageAmount) * CharaObjGetStatusMultiplier(0x42));
				}
				System.Printf(dbg + 0x1A0, basePower, sourcePower, defense, bonus, damageAmount);

				if (staType != 0x6A && (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
				    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 0x100) != 0 &&
				    (Game.m_gameWork.m_chaliceElement & 4U) == 0 &&
				    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x2E) == 0) {
					if (sourceObj->m_lastStateId == 6 &&
					    (*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0x560) * 0x48 + 10) & 0xFF) <= 1) {
						break;
					}
					reinterpret_cast<CGCharaObj*>(sourceObj)->setSta(4, 0x19);
					sourceObj->changeStat(10, 0, 0);
					reinterpret_cast<CGCharaObj*>(sourceObj)->addHp(-1, 0);
				}
				break;
			}
			case 10: {
				int recoilDamage;
				unsigned char* selfReactive = reinterpret_cast<unsigned char*>(this) + 0x6C2;
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && *selfReactive != 0) {
					recoilDamage = 1;
				} else {
					float recoilRate = (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x26 + resistType * 2)) * 0.01f) + 1.0f;
					int raw = static_cast<int>(static_cast<float>(static_cast<int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C))) * recoilRate);
					recoilDamage = (raw < 1) ? 1 : raw;
					if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
						*selfReactive = 1;
					}
				}
				System.Printf(dbg + 0x218, recoilDamage);
				int nextSta = calcSta(10, resolvedItemId, sourceObj);
				setSta(10, nextSta);
				break;
			}
			default:
				System.Printf(dbg + 0x230, staType);
				break;
			}
		} else if (itemKind == 8 || (itemKind == 9 && (static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && (static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD) == 0xAD)) {
			switch (staType) {
			case 0:
			case 1:
			case 2:
			case 4:
			case 0x1C: {
				unsigned int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				unsigned int basePower = *reinterpret_cast<unsigned short*>(itemData + 6);
				unsigned int sourcePower = *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x20);
				int guardValue = static_cast<int>(defense * CharaObjGetStatusMultiplier(0x32));
				damageAmount = static_cast<int>(basePower + sourcePower) - guardValue;
				if (damageAmount < 1) {
					damageAmount = 1;
				}
				System.Printf(dbg + 0x274);
				break;
			}
			case 0x24:
			case 0x25:
			case 100:
			case 0x69:
			case 0x6A: {
				unsigned int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				unsigned int basePower = *reinterpret_cast<unsigned short*>(itemData + 6);
				unsigned int sourcePower = *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x1E);
				int guardValue = static_cast<int>(defense * CharaObjGetStatusMultiplier(0x30));
				damageAmount = static_cast<int>(basePower + sourcePower) - guardValue;
				if (damageAmount < 1) {
					damageAmount = 1;
				}
				if (scriptDefense != 0) {
					damageAmount = static_cast<int>(damageAmount * CharaObjGetStatusMultiplier(0x42));
				}
				System.Printf(dbg + 0x240);
				break;
			}
			case 10: {
				float recoilRate = (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x26 + resistType * 2)) * 0.01f) + 1.0f;
				int raw = static_cast<int>(static_cast<float>(static_cast<int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x1C))) * recoilRate);
				damageAmount = (raw < 1) ? 1 : raw;
				System.Printf(dbg + 0x2A4, damageAmount);
				break;
			}
			default:
				System.Printf(dbg + 0x230, staType);
				break;
			}
		} else if (itemKind == 9 && (static_cast<unsigned short>(GetCID()) & 0x2D) == 0x2D &&
		           ((static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD) == 0xAD || (static_cast<unsigned short>(sourceObj->GetCID()) & 0x1D) == 0x1D)) {
			switch (staType) {
			case 0:
			case 1:
			case 4: {
				unsigned int basePower = *reinterpret_cast<unsigned short*>(itemData + 6);
				unsigned int sourcePower = (static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD) == 0xAD ?
					*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x20) :
					*reinterpret_cast<unsigned short*>(itemData + 0x30);
				unsigned int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				float defenseRate = kOneF32;
				if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD) == 0xAD) {
					defenseRate = CharaObjGetStatusMultiplier(0x32);
				}
				int guardValue = static_cast<int>(static_cast<float>(static_cast<int>(defense)) * defenseRate);
				damageAmount = static_cast<int>(basePower + sourcePower) - guardValue;
				if (damageAmount < 1) {
					damageAmount = 1;
				}
				System.Printf(dbg + 0x2BC, basePower, sourcePower, defense, damageAmount);
				break;
			}
			case 0x25:
				damageAmount = (resolvedItemId == 0x4AA) ? 1 : 10;
				break;
			default:
				System.Printf(dbg + 0x230, staType);
				break;
			}
		}

		if (staType != 4 &&
		    !((static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD) == 0xAD && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x10) == 6 && staType == 0x6A) &&
		    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x46) != 0) {
			setSta(4, 0);
		}
		if (scriptDefense != 0 && staType != 2 && staType != 0) {
			setSta(0, 0);
		}

		if (damageClamp != 0) {
			damageAmount = (damageAmount < 2) ? 0 : 1;
		}

		if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 4) != 0 &&
		    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x52) == 0 && damageAmount < 1) {
			damageAmount = 1;
		}
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x76) == 0 && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0 &&
		    staType != 0x1C && damageAmount < 1) {
			damageAmount = 1;
		}
		CGCharaObj* sourceChara = reinterpret_cast<CGCharaObj*>(sourceObj);
		if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x2D) == 0x2D && sourceChara->m_comboItemState >= 0 &&
		    sourceChara->m_comboLinkCount != 0) {
			System.Printf(dbg + 0x2F8);
			damageAmount *= sourceChara->m_comboLinkCount;
		}

		if (damageAmount != 0) {
			addHp(-damageAmount, sourceObj);
			bool selfHasGuard = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0;
			if (selfHasGuard) {
				bonus(0, resolvedItemId, sourceObj);
				sourceObj->bonus(1, resolvedItemId, this);
			}
			if ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + resolvedItemId * 0x48 + 0x32) & 1) == 0 &&
			    ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) != 0x6D || static_cast<int>(sourceObj->m_capsuleHalfHeight) < 0)) {
				if (itemEffect == 0x1F8 || particleLife != 2) {
					if (itemEffect == 0x1F8) {
						bonus(0x13, resolvedItemId, sourceObj);
						sourceObj->bonus(0xF, resolvedItemId, this);
						if (selfHasGuard) {
							sourceObj->bonus(10, resolvedItemId, this);
						}
					} else {
						bonus(0x12, resolvedItemId, sourceObj);
						sourceObj->bonus(0xE, resolvedItemId, this);
						if (selfHasGuard) {
							sourceObj->bonus(9, resolvedItemId, this);
						}
					}
				}
			} else {
				bonus(0x15, resolvedItemId, sourceObj);
				sourceObj->bonus(0x11, resolvedItemId, this);
				if (selfHasGuard) {
					sourceObj->bonus(0xC, resolvedItemId, this);
				}
				for (int i = 0; i < sourceChara->m_comboLinkCount; i++) {
					sourceChara->m_comboLinks[i]->bonus(0x11, resolvedItemId, this);
					if (selfHasGuard) {
						sourceChara->m_comboLinks[i]->bonus(0xC, resolvedItemId, this);
					}
				}
			}
			putHitParticleFromItem(sourceObj, resolvedItemId);
			if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
				unsigned char* script9 = reinterpret_cast<unsigned char*>(m_scriptHandle[9]);
				int seNo = *reinterpret_cast<unsigned short*>(script9 + 0x192) +
					(*reinterpret_cast<unsigned short*>(script9 + 0x190) * 1000) + 6 +
					Math.Rand(3);
				playSe3D(seNo, 0x32, 0x96, 0, 0);
			}
		}

		if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D &&
		    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			int counterState = sourceChara->m_comboItemState;
			if (counterState >= 0) {
				int counterType;
				int counterItem;
				int counterSe;
				if (counterState == 1) {
					counterType = 0;
					counterItem = 0x20B;
					counterSe = 0x7E2;
				} else if (counterState < 1) {
					counterType = 1;
					counterItem = 0x207;
					counterSe = 0x7E1;
				} else if (counterState < 3) {
					counterType = 4;
					counterItem = 0x20F;
					counterSe = 0x7E3;
				}
				int counterResist;
				int counterAllow;
				int counterEffect;
				calcRegist(counterType, counterItem, counterResist, counterAllow, counterEffect, 1);
				if (counterAllow != 0) {
					if ((m_bgColMask & 0x80000) != 0) {
						effective(counterType, counterItem, sourceObj, counterEffect);
						playSe3D(counterSe, 0x32, 0x96, 0, 0);
					} else {
						System.Printf(dbg + 0x310);
					}
				}
			} else {
				int counterResist;
				int counterAllow;
				int counterEffect;
				if (((DbgMenuPcs.GetDbgFlagsRaw() & 0x20) != 0 ||
				     *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0x6CC) == 2) &&
				    (calcRegist(0x69, resolvedItemId, counterResist, counterAllow, counterEffect, 0), counterAllow != 0)) {
					int chance;
					if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
						chance = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x19A);
					} else {
						chance = 0x32;
					}
					if (chance != 0 && (DbgMenuPcs.GetDbgFlagsRaw() & 0x20) != 0) {
						chance = 100;
					}
					if (chance != 0 && Math.Rand(100) <= static_cast<unsigned int>(chance)) {
						if ((m_bgColMask & 0x80000) != 0) {
							effective(0x69, resolvedItemId, sourceObj, counterEffect);
						} else {
							System.Printf(dbg + 0x348);
						}
					}
				}
			}
		}

		sourceObj->onAttacked(this);
	}

	if (itemEffect != 0x1F8 && particleLife == 2 &&
	    (allowEffect != 0 || damageAmount != 0) &&
	    staType != 0x66 && staType != 0x67 && staType != 0x65) {
		bonus(0x14, resolvedItemId, sourceObj);
		sourceObj->bonus(0x10, resolvedItemId, this);
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			sourceObj->bonus(0x0B, resolvedItemId, this);
		}
	}

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
	bool isIceJ = false;
	bool isMon = false;
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
		isMon = true;
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFC) == 0xB) {
			isIceJ = true;
		}
	}

	unsigned char* staSlot = reinterpret_cast<unsigned char*>(m_scriptHandle) + (staIndex * 2);
	unsigned short current = *reinterpret_cast<unsigned short*>(staSlot + 0x3E);
	value &= ~(value >> 31);

	if (current == 0 && value != 0) {
		switch (staIndex) {
			case 0x1B:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x400U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticle(0x11C, m_particleSlots[10], this, 1.0f, 0x1290D);
				break;
			case 1:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x40U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				if (isIceJ) {
					int modelPdtNo = CharaObjGetModelPdtNo(this);
					putParticle((modelPdtNo << 8) | 0x14, m_particleSlots[6], this, 1.0f, 0);
				} else {
					putParticle(0x12A, m_particleSlots[6], this, 20.0f * m_attackColRadius, 0);
				}
				break;
			case 0:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x4U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				if (isIceJ) {
					int modelPdtNo = CharaObjGetModelPdtNo(this);
					putParticleBindTrace((modelPdtNo << 8) | 0x15, m_particleSlots[2], this, 1.0f, 0);
				} else {
					putParticle(0x10A, m_particleSlots[2], this, 20.0f * m_attackColRadius, 0);
				}
				if (isMon) {
					reinterpret_cast<CGMonObj*>(this)->setIceJEffect(0);
				}
				break;
			case 4:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x80U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				if (isIceJ) {
					int modelPdtNo = CharaObjGetModelPdtNo(this);
					putParticle((modelPdtNo << 8) | 0x17, m_particleSlots[7], this, 1.0f, 0);
				} else {
					putParticle(0x130, m_particleSlots[7], this, 20.0f * m_attackColRadius, 0);
				}
				break;
			case 10:
				if (isMon && (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 4) != 0) {
					reinterpret_cast<CGMonObj*>(this)->flyDown();
				}
				break;
			case 9: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x4000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				float monsterScale;
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
					monsterScale = static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x1B4)) * 0.01f;
				} else {
					monsterScale = 1.0f;
				}
				int particleNo = isMon ? 0x6C : 0x10;
				putParticle(particleNo | 0x100, m_particleSlots[14], this, 20.0f * m_attackColRadius * monsterScale, 0);
				break;
			}
			case 8: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x2000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				float monsterScale;
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
					monsterScale = static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x1B4)) * 0.01f;
				} else {
					monsterScale = 1.0f;
				}
				int particleNo = isMon ? 0x6E : 0x12;
				putParticle(particleNo | 0x100, m_particleSlots[13], this, 20.0f * m_attackColRadius * monsterScale, 0);
				break;
			}
			case 7: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x8000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				int particleNo = isMon ? 0x70 : 0x14;
				putParticle(particleNo | 0x100, m_particleSlots[15], this, 20.0f * m_attackColRadius, 0);
				break;
			}
			case 3:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x40000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticleBindTrace(0x10D, m_particleSlots[18], this, 20.0f * m_attackColRadius, 0);
				break;
			case 2:
				m_castTimeTick = 0;
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x80000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticleBindTrace(0x10C, m_particleSlots[19], this, 20.0f * m_attackColRadius, 0);
				break;
			case 6:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x100000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticleBindTrace(0x107, m_particleSlots[20], this, 20.0f * m_attackColRadius, 0);
				break;
			case 0x1C:
				if (isMon && (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0) {
					reinterpret_cast<CGMonObj*>(this)->undeadOff();
				}
				break;
			default:
				break;
		}
	} else if (current != 0 && value == 0) {
		switch (staIndex) {
			case 0x1B:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x400U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				break;
			case 1:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x40U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				break;
			case 0:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x4U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				if (isIceJ) {
					int modelPdtNo = CharaObjGetModelPdtNo(this);
					putParticle((modelPdtNo << 8) | 0x16, 0, this, 1.0f, 0);
				} else {
					putParticle(0x10B, 0, this, 20.0f * m_attackColRadius, 0);
				}
				playSe3D(0x16, 0x32, 0x96, 0, 0);
				if (isMon) {
					reinterpret_cast<CGMonObj*>(this)->setIceJEffect(1);
				}
				break;
			case 4:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x80U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				break;
			case 10:
				if (isMon && (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 4) != 0 &&
					*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
					reinterpret_cast<CGMonObj*>(this)->flyUp();
				}
				break;
			case 0x1C:
				if (isMon && (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0) {
					reinterpret_cast<CGMonObj*>(this)->undeadOn();
				}
				break;
			case 9: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x4000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				float monsterScale;
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
					monsterScale = static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x1B4)) * 0.01f;
				} else {
					monsterScale = 1.0f;
				}
				int particleNo = isMon ? 0x6D : 0x11;
				putParticle(particleNo | 0x100, 0, this, 20.0f * m_attackColRadius * monsterScale, 0);
				break;
			}
			case 8: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x2000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				float monsterScale;
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
					monsterScale = static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x1B4)) * 0.01f;
				} else {
					monsterScale = 1.0f;
				}
				int particleNo = isMon ? 0x6F : 0x13;
				putParticle(particleNo | 0x100, 0, this, 20.0f * m_attackColRadius * monsterScale, 0);
				break;
			}
			case 7: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x8000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				int particleNo = isMon ? 0x71 : 0x15;
				putParticle(particleNo | 0x100, 0, this, 20.0f * m_attackColRadius, 0);
				break;
			}
			case 3:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x40000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticle(0x10E, 0, this, 20.0f * m_attackColRadius, 0);
				playSe3D(0x3A, 0x32, 0x96, 0, 0);
				break;
			case 2:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x80000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				break;
			case 6:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x100000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				break;
			case 0x67:
				break;
			default:
				break;
		}
	}

	*reinterpret_cast<short*>(staSlot + 0x3E) = static_cast<short>(value);
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
void CGCharaObj::effective(int staIndex, int amount, CGPrgObj* sourceObj, int& outValue)
{
	switch (staIndex) {
		case 0x24:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) != 0) {
				setSta(0, 0);
			}
			break;
		case 0x64:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) != 0) {
				setSta(0, 0);
			}
			break;
		case 0x25:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) != 0) {
				setSta(0, 0);
			}
			if ((static_cast<unsigned short>(GetCID()) & 0xAD) != 0xAD ||
				(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 8) == 0) {
				CVector sourcePos(sourceObj->m_worldPosition);
				CVector selfPos(m_worldPosition);
				CVector deltaVec;
				PSVECSubtract(reinterpret_cast<Vec*>(&selfPos), reinterpret_cast<Vec*>(&sourcePos), reinterpret_cast<Vec*>(&deltaVec));
				Vec delta;
				delta.x = deltaVec.x;
				delta.y = deltaVec.y;
				delta.z = deltaVec.z;
				moveVectorH(&delta, 8.0f, 8);
				m_rotTargetY = static_cast<float>(atan2(-static_cast<double>(delta.x), -static_cast<double>(delta.z)));
				changeStat(0x19, 0, 0);
			}
			break;
		case 0x68:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) != 0) {
				setSta(0, 0);
			}
			changeStat(4, 0, 0);
			break;
		case 0x6B:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x46) != 0) {
				setSta(4, 0);
			}
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) == 0 &&
				*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x50) == 0 &&
				*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x44) == 0) {
				changeStat(0x1A, 0, 0);
			}
			break;
		case 0x6A:
			setSta(4, calcSta(4, amount, reinterpret_cast<CGObject*>(sourceObj)));
			setSta(0, 0);
			setSta(1, 0);
			changeStat(10, 0, 0);
			break;
		case 1:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) == 0) {
				setSta(1, calcSta(1, amount, reinterpret_cast<CGObject*>(sourceObj)));
				setSta(4, 0);
			} else {
				setSta(0, 0);
				setSta(1, 0);
				outValue = 0;
			}
			break;
		case 0:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x40) == 0) {
				setSta(0, calcSta(0, amount, reinterpret_cast<CGObject*>(sourceObj)));
				setSta(4, 0);
				Sound.StopSe3DGroup(m_particleId);
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x3bU) != 0) {
						CFlatRuntime2Storage().DeleteParticleSlot(
							*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x564 + i * 4), 1);
					}
				}
				changeStat(0, 0, 0);
			} else {
				setSta(0, 0);
				setSta(1, 0);
				outValue = 0;
			}
			break;
		case 4:
			setSta(4, calcSta(4, amount, reinterpret_cast<CGObject*>(sourceObj)));
			setSta(0, 0);
			setSta(1, 0);
			changeStat(10, 0, 0);
			break;
		case 0x66:
			addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), 0);
			sourceObj->bonus(0x16, amount, this);
			outValue = 0;
			putHitParticleFromItem(sourceObj, amount);
			break;
		case 0x69:
			for (int i = 0; i < 0x27; i++) {
				setSta(i, 0);
			}
			m_displayFlags |= 2;
			putHitParticleFromItem(sourceObj, amount);
			break;
		case 0x65:
			if (Game.m_gameWork.m_gameOverFlag == 0) {
				if (amount == 0x225) {
					addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), 0);
				} else {
					addHp(8, 0);
				}
				changeStat(0x22, 0, 0);
				putHitParticleFromItem(sourceObj, amount);
			} else {
				System.Printf(lbl_801DC908);
			}
			outValue = 0;
			break;
		case 0x1C:
			setSta(0x1C, calcSta(0x1C, amount, reinterpret_cast<CGObject*>(sourceObj)));
			break;
		case 8:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x4C) == 0) {
				setSta(8, calcSta(8, amount, reinterpret_cast<CGObject*>(sourceObj)));
				putHitParticleFromItem(sourceObj, amount);
			} else {
				setSta(7, 0);
				setSta(8, 0);
			}
			outValue = 0;
			break;
		case 7:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x4E) == 0) {
				setSta(7, calcSta(7, amount, reinterpret_cast<CGObject*>(sourceObj)));
				putHitParticleFromItem(sourceObj, amount);
			} else {
				setSta(7, 0);
				setSta(8, 0);
			}
			outValue = 0;
			break;
		case 9:
			setSta(7, 0);
			setSta(8, 0);
			setSta(9, calcSta(9, amount, reinterpret_cast<CGObject*>(sourceObj)));
			outValue = 0;
			putHitParticleFromItem(sourceObj, amount);
			Sound.StopSe3DGroup(m_particleId);
			for (int i = 0; i < 0x16; i++) {
				if (((1U << i) & 0x3bU) != 0) {
					CFlatRuntime2Storage().DeleteParticleSlot(
						*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x564 + i * 4), 1);
				}
			}
			changeStat(0, 0, 0);
			break;
		case 6:
			setSta(6, calcSta(6, amount, reinterpret_cast<CGObject*>(sourceObj)));
			outValue = 0;
			putHitParticleFromItem(sourceObj, amount);
			break;
		case 2:
			setSta(2, calcSta(2, amount, reinterpret_cast<CGObject*>(sourceObj)));
			break;
		case 3:
			setSta(1, 0);
			setSta(0, 0);
			setSta(4, 0);
			setSta(9, 0);
			setSta(7, 0);
			setSta(8, 0);
			setSta(3, calcSta(3, amount, reinterpret_cast<CGObject*>(sourceObj)));
			outValue = 0;
			putHitParticleFromItem(sourceObj, amount);
			Sound.StopSe3DGroup(m_particleId);
			for (int i = 0; i < 0x16; i++) {
				if (((1U << i) & 0x3bU) != 0) {
					CFlatRuntime2Storage().DeleteParticleSlot(
						*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x564 + i * 4), 1);
				}
			}
			changeStat(0, 0, 0);
			break;
	}
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
int CGCharaObj::calcSta(int staIndex, int amount, CGObject* source)
{
	if ((staIndex == 0 || staIndex == 4) &&
		*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E + (staIndex * 2)) != 0) {
		System.Printf(const_cast<char*>(lbl_801DC8D8));
		return static_cast<int>(*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E + (staIndex * 2)));
	}

	unsigned int base = 0;
	switch (staIndex) {
		case 0:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x10);
			break;
		case 1:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x0E);
			break;
		case 2:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x1E);
			break;
		case 3:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x22);
			break;
		case 4:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x12);
			break;
		case 6:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x20);
			break;
		case 7:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x18);
			break;
		case 8:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x14);
			break;
		case 9:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x16);
			break;
		case 10:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x1A);
			break;
		case 0x1C:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x1C);
			break;
		case 0x6A:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x24);
			break;
		default:
			break;
	}

	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + (amount * 0x48);
	short itemType = 1;
	if (amount >= 0x1F5) {
		itemType = *reinterpret_cast<short*>(itemData + 2);
	}

	CGPrgObj* sourceObj = reinterpret_cast<CGPrgObj*>(source);
	unsigned short powerValue;
	if ((((static_cast<unsigned int>(__cntlzw(0x2D - (static_cast<unsigned short>(source->GetCID()) & 0x2D)))) >> 5) & 0xFFU) == 0) {
		powerValue = *reinterpret_cast<unsigned short*>(itemData + 0x2E);
	} else {
		bool stageModeActive = false;
		bool usePartySource = false;
		bool usePartyLeader = false;

		if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			stageModeActive = true;
		}
		if (stageModeActive) {
			if ((((static_cast<unsigned int>(__cntlzw(0x6D - (static_cast<unsigned short>(source->GetCID()) & 0x6D)))) >> 5) & 0xFFU) != 0) {
				usePartySource = true;
			}
		}
		if (usePartySource && sourceObj->m_scriptHandle[0xED] != 0) {
			usePartyLeader = true;
		}

		CGPrgObj* powerSource = sourceObj;
		if (usePartyLeader) {
			powerSource = Game.m_partyObjArr[0];
		}
		powerValue = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(powerSource->m_scriptHandle[9]) + 0x198);
	}

	unsigned int power = powerValue;
	if ((static_cast<unsigned short>(source->GetCID()) & 0xAD) == 0xAD) {
		int stageLevel;
		if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			stageLevel = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
			if (stageLevel > 2) {
				stageLevel = 2;
			}
		} else {
			stageLevel = 0;
		}

		if (stageLevel > 0) {
			power += *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + (stageLevel * 2) + 0x5C);
		}
	}

	unsigned int affinity = 0;
	if ((static_cast<unsigned short>(source->GetCID()) & 0x6D) == 0x6D && (itemType == 1 || itemType == 9)) {
		affinity = static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0xBDA));
	}

	unsigned int selfCid = static_cast<unsigned int>(GetCID());
	if ((selfCid & 0x6D) == 0x6D && (itemType == 8 || itemType == 9)) {
		affinity -= *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBDB);
	}

	unsigned int next = affinity + (base * power);
	next &= ~((static_cast<int>(next)) >> 31);
	System.Printf(const_cast<char*>(lbl_801DC8EC), base, power, affinity, next);
	return static_cast<int>(next);
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
void CGCharaObj::addHp(int delta, CGPrgObj* sourceObj)
{
	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
	    (MiniGamePcs.m_flags & 4) != 0) {
		return;
	}

	unsigned int hpValue = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C);
	unsigned int next = hpValue;

	if (delta > 0) {
		unsigned short maxHp = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A);
		next = hpValue + delta;
		if (static_cast<int>(next) > static_cast<int>(maxHp)) {
			next = maxHp;
		}
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) = static_cast<unsigned short>(next);
	} else if (delta < 0 && hpValue != 0) {
		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && (CFlatGameFlags() & CFlatGameFlag_Bit0) != 0 &&
		    static_cast<int>(hpValue + delta) <= 0) {
			delta = -(static_cast<int>(hpValue) - 1);
		}

		if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
			if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x10) == 0x9A &&
			    static_cast<CGMonObj*>(this)->m_actionBranch == 0) {
				*reinterpret_cast<int*>(CGMonObj::m_boss + 0x24) -= delta;
				delta = 0;
			}
			if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x10) == 0x88) {
				*reinterpret_cast<int*>(CGMonObj::m_boss + 0x88) -= delta;
			}
			if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x10) == 0x70 &&
			    static_cast<int>(hpValue + delta) <= 0) {
				delta = -(static_cast<int>(hpValue) - 1);
			}
		}

		next = hpValue + delta;
		next &= ~(static_cast<int>(next) >> 31);
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) = static_cast<unsigned short>(next);
		m_worldParam = kOneF32;

		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
			CGPartyObj* party = static_cast<CGPartyObj*>(this);
			if (static_cast<signed char>(party->m_partyData.partyFlags) < 0) {
				int stackArgs[2];
				stackArgs[0] = -1;
				stackArgs[1] = 0;
				gCFlatRuntime().SystemCall(
					reinterpret_cast<CFlatRuntime::CObject*>(this), 2, 0x14, 2,
					reinterpret_cast<CFlatRuntime::CStack*>(stackArgs), 0);
			}
			party->carry(1, 0, 1);
		}

		if (sourceObj != 0) {
			onDamaged(sourceObj);
		}
	}

	if (next != 0) {
		return;
	}

	for (int i = 0; i < 0x27; i++) {
		setSta(i, 0);
	}
	m_displayFlags |= 2;
	changeStat(9, 0, 0);

	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
		CGPartyObj* party = static_cast<CGPartyObj*>(this);
		CCaravanWork* caravan = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
		for (int i = 2; i < *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBAA); i++) {
			if (caravan->DelCmdListAndItem(i) == 0x125) {
				caravan->GetNumCombi(i, 1);
				unsigned char& flags = party->m_partyData.partyFlags;
				flags = (flags & 0xFB) | 4;
				return;
			}
		}
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
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + (itemId * 0x48);

	int isNormal = 0;
	if ((*reinterpret_cast<unsigned short*>(itemData + 0x32) & 1) != 0 || forceNormal != 0) {
		isNormal = 1;
	}

	outA = 3;
	switch (staIndex) {
		case 0: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x2C); break;
		case 1: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x2A); break;
		case 2: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x38); break;
		case 3: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3C); break;
		case 4: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x2E); break;
		case 6: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3A); break;
		case 8: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x30); break;
		case 9: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x32); break;
		case 10: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x34); break;
		case 0x1C: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x36); break;
		case 0x24:
		case 0x25:
		case 0x26:
		case 0x69:
		case 0x6A:
		case 0x6B:
		case 100:
			outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x28);
			break;
		default:
			break;
	}

	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x76) == 0 && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0 &&
		staIndex != 0x1C) {
		int clamped = 2;
		if (outA > 1) {
			clamped = outA;
		}
		outA = clamped;
	}
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 4) != 0 &&
		*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x52) == 0) {
		int clamped = 2;
		if (outA > 1) {
			clamped = outA;
		}
		outA = clamped;
	}

	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x10) == 0x7F &&
	    static_cast<signed char>(SoundBuffer[0x4FC]) < 0) {
		outA = 3;
	}

	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x74) != 0) {
		outA = 3;
	}

	System.Printf(const_cast<char*>(lbl_801DC8CC), outA);

	if (outA == 1) {
		outB = (isNormal != 0) ? 1 : 0;
	} else if (outA == 0) {
		outB = 1;
	} else {
		outB = 0;
	}
	outC = (outA ^ 3) / 2;
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
int CGCharaObj::getItemPdt(int itemId, int level, int& outEffect, int& outArg0, int& outArg1)
{
	bool hasMotion = false;
	int result;
	CCharaPcs::CHandle* model = m_charaModelHandle;
	if (model != 0 && *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(model) + 0x168) != 0) {
		hasMotion = true;
	}

	if (!hasMotion) {
		result = 1;
	} else {
		unsigned char* motion = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(model) + 0x168));
		if (*reinterpret_cast<void**>(motion + 0xD0) != 0) {
			int frame;
			int period = static_cast<int>(kOneF32 + (*reinterpret_cast<float*>(motion + 0xC0) -
				*reinterpret_cast<float*>(motion + 0xBC)));
			if (period == 1) {
				result = 1;
			} else {
				frame = static_cast<int>(m_turnSpeed);
				int frameMod = frame % period;
				if (m_lastBgAttr < FLOAT_80331988) {
					result = static_cast<unsigned int>(__cntlzw(frameMod)) >> 5;
				} else {
					bool isPeriod = (period <= frame);
					result = isPeriod;
				}
			}
		} else {
			result = 1;
		}
	}

	return result;
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
	unsigned int particleBank = CharaObjResolveParticleBank(this, particleClass);
	unsigned short particleEntry = 0xFFFF;
	unsigned short particleFlags = 0;
	unsigned int particleNo = effectId;
	int seNo = 0;
	bool emittedCustom = false;
	bool hasParticle = false;

	if (particleBank != 0xFFFFFFFF) {
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
				particleNo += *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0);
			}

			if ((particleFlags & 0x800) != 0 && m_scriptHandle != 0) {
				particleNo += *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2);
			}
			hasParticle = true;
		}
	}

	if (hasParticle) {
		CFlatRuntime2Storage().ResetParticleWork((particleBank << 8) | particleNo, effectArg1);
		CFlatRuntime2Storage().SetParticleWorkScale(*reinterpret_cast<unsigned short*>(itemData + 0x10) * 0.01f);
		CFlatRuntime2Storage().SetParticleWorkParam(effectId, this);
		CFlatRuntime2Storage().SetParticleWorkSpeed(*reinterpret_cast<unsigned short*>(itemData + 0x26) * 0.01f);

		switch (effectArg0) {
		case 0:
			seNo = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(itemData + 0x38));
			if (seNo != 0 && (*reinterpret_cast<unsigned short*>(itemData + 0x3A) & 0x8000) != 0) {
				CFlatRuntime2Storage().SetParticleWorkSe(seNo, 2, *reinterpret_cast<unsigned short*>(itemData + 0x3A) & 0xFF);
				seNo = 0;
			}
			break;
		case 1:
			seNo = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(itemData + 0x3C));
			if (seNo != 0 && (*reinterpret_cast<unsigned short*>(itemData + 0x3E) & 0x8000) != 0) {
				CFlatRuntime2Storage().SetParticleWorkSe(seNo, 2, *reinterpret_cast<unsigned short*>(itemData + 0x3E) & 0xFF);
				seNo = 0;
			}
			break;
		case 2:
			seNo = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(itemData + 0x40));
			if (seNo != 0 && (*reinterpret_cast<unsigned short*>(itemData + 0x0C) & 0x400) != 0) {
				CFlatRuntime2Storage().SetParticleWorkSe(seNo, 2, 0);
				seNo = 0;
			}
			break;
		default:
			break;
		}

		if (effectId > 500) {
			unsigned short itemType = *reinterpret_cast<unsigned short*>(itemData + 2);
			int colType;
			if (itemType == 4) {
				colType = 4;
			} else if (itemType < 4) {
				if (itemType == 1) {
					colType = 1;
				}
			} else if (itemType == 9) {
				colType = 9;
			} else if (itemType < 9 && itemType > 7) {
				colType = 8;
			}
			CFlatRuntime2Storage().SetParticleWorkCol(colType, -1, *reinterpret_cast<unsigned short*>(itemData + 4) * 0.01f);
		}

		if ((particleFlags & 0x100) != 0) {
			CFlatRuntime2Storage().SetParticleWorkBind(this);
		} else if ((particleFlags & 0x200) != 0) {
			float distance = *reinterpret_cast<unsigned short*>(itemData + 0x2A) * 1.0f;
			Vec offsetPos;
			offsetPos.x = m_worldPosition.x + sinf(m_rotTargetY) * distance;
			offsetPos.y = m_worldPosition.y;
			offsetPos.z = m_worldPosition.z + cosf(m_rotTargetY) * distance;
			CFlatRuntime2Storage().SetParticleWorkPos(offsetPos, m_rotTargetY);
			CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, 0.0f);
			if ((*reinterpret_cast<unsigned short*>(itemData + 0x0C) & 0x2000) != 0) {
				int partyIndex = static_cast<int>(m_rotationX);
				if (partyIndex >= 0 && partyIndex < 4) {
					CFlatRuntime2Storage().SetParticleWorkTrace(Game.m_partyObjArr[partyIndex]);
				}
			}
			if ((*reinterpret_cast<unsigned short*>(itemData + 0x0C) & 0x4000) != 0) {
				CFlatRuntime2Storage().SetParticleWorkPos(m_worldPosition, m_rotTargetY);
				CFlatRuntime2Storage().SetParticleWorkTarget(m_jumpOffset);
				CFlatRuntime2Storage().SetParticleWorkTrace(this);
			}
		} else if (pos != 0) {
			CFlatRuntime2Storage().SetParticleWorkPos(*pos, m_rotTargetY);
		} else if ((particleFlags & 0x400) != 0) {
			CFlatRuntime2Storage().SetParticleWorkPos(m_jumpOffset, 0.0f);
		} else {
			CFlatRuntime2Storage().SetParticleWorkPos(m_worldPosition, m_rotTargetY);
		}

		if (effectId == 0x410) {
			if (effectArg0 == 2 || effectArg0 == 3) {
				float angleOffset = FLOAT_80331990;
				if (effectArg0 == 2) {
					angleOffset = FLOAT_8033198C;
				}
				float angle = m_rotTargetY + angleOffset;
				CFlatParticleWorkPosition().x = FLOAT_80331994 * sinf(angle) + m_worldPosition.x;
				CFlatParticleWorkPosition().z = FLOAT_80331994 * cosf(angle) + m_worldPosition.z;
				CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, 0.0f);
				CFlatRuntime2Storage().PutParticleWork();
				emittedCustom = true;
			}
		} else if (effectId < 0x410) {
			if (effectId == 0x3B4) {
				if (effectArg0 == 3) {
					if (pos == 0) {
						return;
					}
					CFlatRuntime2Storage().SetParticleWorkPos(*pos, m_rotTargetY);
					CFlatRuntime2Storage().PutParticleWork();
					emittedCustom = true;
				}
			} else if (effectId == 0x409 && effectArg0 == 3) {
				for (int i = 3; i < 9; i++) {
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | i);
					CFlatRuntime2Storage().PutParticleWork();
				}
				emittedCustom = true;
			}
		} else if (effectId < 0x479) {
			if (effectId < 0x46F) {
				if (effectId > 0x46C) {
					if (effectArg0 == 2) {
						if (m_stateFrame > 0xF) {
							CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | 0x1D);
							float rand0 = Math.RandFPM(FLOAT_80331998);
							float rand1 = Math.RandFPM(FLOAT_80331998);
							CVector randomOffset(rand1, FLOAT_80331988, rand0);
							CVector randomBase(FLOAT_80331988, FLOAT_8033199C, FLOAT_803319A0);
							CVector randomResult;
							PSVECAdd(reinterpret_cast<Vec*>(&randomBase), reinterpret_cast<Vec*>(&randomOffset), reinterpret_cast<Vec*>(&randomResult));
							Vec randomPos;
							randomPos.x = randomResult.x;
							randomPos.y = randomResult.y;
							randomPos.z = randomResult.z;
							CFlatRuntime2Storage().SetParticleWorkPos(randomPos, m_rotTargetY);
							CFlatRuntime2Storage().PutParticleWork();
						}
						emittedCustom = true;
					}
					if (effectArg0 == 3) {
						for (int i = 0x0D; i < 0x1D; i++) {
							CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | i);
							CFlatRuntime2Storage().PutParticleWork();
						}
						emittedCustom = true;
					}
				}
			} else if (effectId > 0x472 && effectArg0 == 3) {
				for (int i = 7; i < 0x0C; i++) {
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | i);
					CFlatRuntime2Storage().PutParticleWork();
				}
				emittedCustom = true;
			}
		} else if (effectId > 0x49C && effectId < 0x4A0 && effectArg0 == 2) {
			Mtx rotMtx;
			PSMTXRotRad(rotMtx, 'y', m_rotTargetY);
			for (int i = 0; i < 2; i++) {
				float side = (i == 0) ? 76.0f : -76.0f;
				Vec sidePos = { side, 0.0f, FLOAT_80331998 };
				Vec offsetPos;
				PSMTXMultVec(rotMtx, &sidePos, &offsetPos);
				CFlatParticleWorkPosition().x = m_worldPosition.x + offsetPos.x;
				CFlatParticleWorkPosition().y = m_worldPosition.y + offsetPos.y;
				CFlatParticleWorkPosition().z = m_worldPosition.z + offsetPos.z;
				CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, 0.0f);
				CFlatRuntime2Storage().PutParticleWork();
			}
			emittedCustom = true;
		}

		if (seNo != 0) {
			Vec* sePos = (effectArg0 == 2) ? pos : 0;
			int seHandle = playSe3D(seNo, 0x32, 0x96, 0, sePos);
			Sound.SetSe3DGroup(seHandle, m_particleId);
		}

		if (!emittedCustom) {
			int fanCount = *reinterpret_cast<unsigned short*>(itemData + 0x24);
			if (effectArg0 == 3 && fanCount > 1) {
				for (int i = 0; i < fanCount; i++) {
					CFlatRuntime2Storage().SetParticleWorkVector(FLOAT_803319A4 * static_cast<float>(i) / static_cast<float>(fanCount), FLOAT_80331988);
					CFlatRuntime2Storage().PutParticleWork();
				}
			} else {
				CFlatRuntime2Storage().PutParticleWork();
			}
		}
	} else if (effectArg0 == 2) {
		unsigned short seSpec = *reinterpret_cast<unsigned short*>(itemData + 0x40);
		seNo = (seSpec == 0xFFFF) ? 0 : ((seSpec & 0xFF) + ((seSpec >> 8) * 1000));
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
	unsigned short cid = GetCID();

	if ((cid & 0xAD) == 0xAD && m_subState == 0) {
		int animPoint = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x10);
		if (animPoint == 0x88 || animPoint == 0x87) {
			if (!CharaObjIsAttackAnimBoundary(this)) {
				return;
			}
			m_subState = 1;
			m_stateFrame = 0;
		}
	}

	onStatAttack(0);

	if (m_stateFrame == 0) {
		m_ignoreHit[0].m_flag &= 0x7F;
		m_ignoreHit[1].m_flag &= 0x7F;
		m_ignoreHit[2].m_flag &= 0x7F;
		m_ignoreHit[3].m_flag &= 0x7F;

		putParticleFromItem(m_itemId, 0, m_particleSlots[0], 0);
		putParticleFromItem(m_itemId, 1, m_particleSlots[0], 0);
		putParticleFromItem(m_itemId, 2, m_particleSlots[0], 0);
		putParticleFromItem(m_itemId, 3, m_particleSlots[0], 0);
		reqAnim(m_attackAnimId, 0, 0);
	}

	if (m_stateFrame == m_castFrameStart) {
		enableAttackCol(1, 0, 0);
	}
	if (m_stateFrame == m_castFrameEnd) {
		enableAttackCol(0, 0, 0);
	}

	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + m_itemId * 0x48;
	unsigned short seFrame = *reinterpret_cast<unsigned short*>(itemData + 0x3A);
	if ((seFrame & 0x8000) == 0 && m_stateFrame == seFrame) {
		unsigned int seSpec = *reinterpret_cast<unsigned short*>(itemData + 0x38);
		if (seSpec != 0) {
			int seNo = (seSpec == 0xFFFF) ? 0 : ((seSpec & 0xFF) + ((seSpec >> 8) * 1000));
			playSe3D(seNo, 0x32, 0x96, 0, 0);
		}
	}

	itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + m_itemId * 0x48;
	seFrame = *reinterpret_cast<unsigned short*>(itemData + 0x3E);
	if ((seFrame & 0x8000) == 0 && m_stateFrame == seFrame) {
		unsigned int seSpec = *reinterpret_cast<unsigned short*>(itemData + 0x3C);
		if (seSpec != 0) {
			if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
				int seNo = (seSpec == 0xFFFF) ? 0 : ((seSpec & 0xFF) + ((seSpec >> 8) * 1000));
				playSe3D(seNo + Math.Rand(3), 0x32, 0x96, 0, 0);
			} else {
				playSe3D(seSpec, 0x32, 0x96, 0, 0);
			}
		}
	}

	onStatAttack(1);
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
int CGCharaObj::calcCastTime(int itemId)
{
	unsigned short cid = GetCID();

	if ((cid & 0x6D) == 0x6D &&
		Game.m_gameWork.m_menuStageMode != 0 &&
		Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
		(static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) != 0) {
		return 0;
	}

	int itemOffset = itemId * 0x48;
	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + itemOffset;
	unsigned short itemNo = *reinterpret_cast<unsigned short*>(itemData + 0x0);
	unsigned int baseCast = *reinterpret_cast<unsigned short*>(itemData + 0x2E);
	unsigned short itemType = *reinterpret_cast<unsigned short*>(itemData + 0xE);
	float castScale = kOneF32;

	if (*reinterpret_cast<unsigned short*>(script + 0x4E) != 0) {
		castScale = CharaObjGetStatusMultiplier(0x0);
	} else if (*reinterpret_cast<unsigned short*>(script + 0x4C) != 0) {
		castScale = CharaObjGetStatusMultiplier(0x2);
	}

	if (itemNo != 0x1F8 && itemType == 2) {
		unsigned int castBonus = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x194);
		if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
			int stageLevel;
			if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
				int stage = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
				stageLevel = 2;
				if (stage < 2) {
					stageLevel = stage;
				}
			} else {
				stageLevel = 0;
			}
			if (stageLevel > 0) {
				castBonus -= *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x58 + (stageLevel * 2));
				castBonus &= ~((int)castBonus >> 31);
			}
		}

		unsigned int playerCid = (static_cast<unsigned int>(__cntlzw(0x6D - static_cast<int>(static_cast<unsigned short>(GetCID()) & 0x6D))) >> 5) & 0xFFU;
		unsigned int castReduction = playerCid != 0 ? static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(script + 0xBD8)) : 0;
		int totalCast = static_cast<int>(baseCast + castBonus) - static_cast<int>(castReduction);
		int cast = static_cast<int>(castScale * static_cast<float>(totalCast));
		System.Printf(sCharaObjDebugStatFormat + 0x10, baseCast, castBonus, castScale);
		return cast & ~(cast >> 31);
	}

	if (itemType == 3) {
		System.Printf(sCharaObjDebugStatFormat + 0x38, baseCast);
		return static_cast<int>(baseCast);
	}
	if (itemType == 4) {
		System.Printf(sCharaObjDebugStatFormat + 0x4C, baseCast);
		return static_cast<int>(baseCast);
	}
	if (itemNo == 0x1F8) {
		unsigned int castBonus = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x196);
		unsigned int playerCid = (static_cast<unsigned int>(__cntlzw(0x6D - static_cast<int>(static_cast<unsigned short>(GetCID()) & 0x6D))) >> 5) & 0xFFU;
		unsigned int castReduction = playerCid != 0 ? static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(script + 0xBD9)) : 0;
		int totalCast = static_cast<int>(baseCast + castBonus) - static_cast<int>(castReduction);
		int cast = static_cast<int>(castScale * static_cast<float>(totalCast));
		System.Printf(sCharaObjDebugStatFormat + 0x60, baseCast, castBonus, castScale);
		return cast & ~(cast >> 31);
	}

	return static_cast<int>(baseCast);
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
	if (((reinterpret_cast<unsigned char*>(this)[0x9A] & 0x80) != 0 && (CFlatCenterState() == 0)) &&
	    ((DbgMenuPcs.GetDbgFlagsRaw() & 0x80) != 0)) {
		char text[0x100];
		unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
		double posYDouble;
		double widthDouble;

		sprintf(text, sCharaObjDebugStatFormat,
		        *reinterpret_cast<unsigned short*>(script + 0x1C),
		        *reinterpret_cast<unsigned short*>(script + 0x1A),
		        *reinterpret_cast<unsigned short*>(script + 0x1E),
		        *reinterpret_cast<unsigned short*>(script + 0x20),
		        *reinterpret_cast<unsigned short*>(script + 0x22));

		posYDouble = (double)posY;
		widthDouble = (double)font->GetWidth(text);
		font->SetPosX(-(float)((double)kHalfF32 * widthDouble - (double)posX));
		font->SetPosY((float)posYDouble);
		font->SetPosZ((float)posZ);
		font->Draw(text);
		posY -= (float)((double)(unsigned short)font->m_glyphHeight * (double)font->scaleY);
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
	for (int i = 0; i < 4; i++) {
		CGPartyObj* partyObj = Game.m_partyObjArr[i];
		if (partyObj == 0) {
			continue;
		}

		unsigned char* partyRaw = reinterpret_cast<unsigned char*>(partyObj);
		if (static_cast<signed char>(partyRaw[0x9A]) < 0 &&
		    static_cast<signed char>(partyRaw[0x9B]) < 0) {
			unsigned char* script = reinterpret_cast<unsigned char*>(partyObj->m_scriptHandle);
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
	CVector comboCenter;

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
	if (isSharedResult) {
		comboCenter.Identity();
		for (int i = 0; i < participantCount; i++) {
			PSVECAdd(reinterpret_cast<Vec*>(&comboCenter), &CharaObjComboCenter(candidates[i]), reinterpret_cast<Vec*>(&comboCenter));
		}
		PSVECScale(reinterpret_cast<Vec*>(&comboCenter), reinterpret_cast<Vec*>(&comboCenter), 1.0f / static_cast<float>(participantCount));
	}

	System.Printf(const_cast<char*>(lbl_801DC590), System.m_frameCounter, comboCmd);

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
		CharaObjComboLinkCount(party) = 0;

		int linkCount = 0;
		CGPrgObj** comboLinks = CharaObjComboLinks(party);
		for (int j = 0; j < participantCount; j++) {
			CGPartyObj* other = candidates[j];
			if (party == other) {
				continue;
			}
			comboLinks[linkCount++] = other;
		}
		CharaObjComboLinkCount(party) = linkCount;
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
	CGPrgObj** comboLinks = CharaObjComboLinks(this);
	while (entry < CharaObjComboLinkCount(this)) {
		CGPrgObj* link = comboLinks[entry];
		if (link != 0) {
			if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
			    (static_cast<unsigned short>(link->GetCID()) & 0x6D) == 0x6D &&
			    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(link->m_scriptHandle) + 0x3B4) != 0) {
				goto next_link;
			} else if (link->m_lastStateId != 6 && link->m_lastStateId != 2) {
				break;
			}
		}
next_link:
		entry++;
	}
	if (entry == CharaObjComboLinkCount(this)) {
		int stackArgs[2];
		stackArgs[0] = reinterpret_cast<int>(target);
		stackArgs[1] = scriptArg;
		gCFlatRuntime().SystemCall(
			reinterpret_cast<CFlatRuntime::CObject*>(this), 2, 0x17, 2,
			reinterpret_cast<CFlatRuntime::CStack*>(stackArgs), 0);
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
	int lastSlot = count - 1;
	outFallback = 0;

	unsigned short* combiCursor = reinterpret_cast<unsigned short*>(Game.unk_flat3_field_1C_0xc7d8);
	for (int combiIndex = 0; combiIndex < static_cast<int>(Game.unk_flat3_count_0xc7d4); combiIndex++, combiCursor += 0xD) {
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

		for (int slot = 0; slot < reqCount; slot++) {
			CGPartyObj* obj = partyList[slot];
			CGCharaObj* partyObj = reinterpret_cast<CGCharaObj*>(obj);
			if (partyObj->m_comboFrame == 0) {
				unsigned short* fallbackCursor = combiCursor + slot * 3;
				int scanSlot = slot;
				for (int remaining = reqCount - slot; remaining != 0; remaining--, scanSlot++, fallbackCursor += 3) {
					unsigned int objParticle = static_cast<unsigned int>(partyObj->m_itemId);
					int itemMatch;
					if ((scanSlot == lastSlot &&
						*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (objParticle * 0x48)) == 0x1F8 &&
						fallbackCursor[0] == 0x1F8) ||
						objParticle == fallbackCursor[0]) {
						itemMatch = 1;
					} else {
						itemMatch = 0;
					}
					if (itemMatch) {
						if (partyList[0] == obj || reinterpret_cast<CGCharaObj*>(partyList[0])->m_comboFrame <= static_cast<int>(combiCursor[slot * 3 + 2])) {
							break;
						}
					}
				}
				if (scanSlot < count) {
					outFallback = 1;
					return found;
				}
				break;
			}

			unsigned int objParticle = static_cast<unsigned int>(partyObj->m_itemId);
			int itemMatch;
			if ((slot == lastSlot &&
				*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (objParticle * 0x48)) == 0x1F8 &&
				combiCursor[slot * 3 + 0] == 0x1F8) ||
				objParticle == combiCursor[slot * 3 + 0]) {
				itemMatch = 1;
			} else {
				itemMatch = 0;
			}
			if (!itemMatch) {
				break;
			}

			int diff = reinterpret_cast<CGCharaObj*>(partyList[0])->m_comboFrame - partyObj->m_comboFrame;
			int minWindow = static_cast<int>(combiCursor[slot * 3 + 1]);
			int maxWindow = static_cast<int>(combiCursor[slot * 3 + 2]);
			if (!(partyList[0] == obj || (minWindow <= diff && diff <= maxWindow))) {
				break;
			}

			if (slot == reqCount - 1) {
				found = combiIndex;
			}
		}
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
