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
extern "C" char sCharaObjComboDecisionFmt[];
extern "C" char sCharaObjResistanceFmt[];
extern "C" char sCharaObjEffectTimeNoOverwriteMsg[];
extern "C" char sCharaObjEffectTimeCalcFmt[];
extern "C" char lbl_801DC908[];
extern "C" char sCharaObjGearGachaMsg[];

static Vec* l_pHitCross = 0;
static int l_idxAttackCol = 0;
int gCGCharaObjCreateSerial = 0;
char gCGCharaObjCreateSerialInit = 0;
extern "C" {
extern const float kOneF32;
extern const float kCharaObjZero;
extern const float FLOAT_803319A8;
extern const float FLOAT_803319AC;
extern const float kCharaObjHalfPi;
extern const float kCharaObjNegativeHalfPi;
extern const float kCharaObjSideParticleRadius;
extern const float kCharaObjForwardParticleOffset;
extern const float FLOAT_8033199C;
extern const float FLOAT_803319A0;
extern const float FLOAT_803319A4;
extern const float FLOAT_803319B0;
extern const float FLOAT_803319B4;
extern const float FLOAT_803319B8[2];
}

extern const float kQuadObjDebugHeight;

// Padded row view of the CFlat item/particle table (stride 0x48). Real array
// indexing through this struct keeps the field offset as a load displacement
// (target `mulli; add; lhz off(r)`), where raw pointer arithmetic re-associates
// the offset into the index (`addi; lhzx`).
struct SCharaItemRow {
	unsigned short m_effect;        // 0x00
	unsigned short m_kind;          // 0x02
	unsigned short m_field04;       // 0x04
	unsigned short m_basePower;     // 0x06
	unsigned short m_staType;       // 0x08
	unsigned short m_status;        // 0x0A
	unsigned short m_particleFlags; // 0x0C
	unsigned short m_particleLife;  // 0x0E
	unsigned short m_scale;         // 0x10
	unsigned short m_particleBank;  // 0x12
	unsigned short m_particleEntries[4]; // 0x14
	unsigned short m_particleSpec;  // 0x1C
	unsigned char m_pad1E[0x8];     // 0x1E
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

// Padded view of the script handle's status block (u16 slots from 0x3E).
struct SCharaStaBlock {
	unsigned char m_pad00[0x3E];
	unsigned short m_sta[0x20];
};

static float& CharaObjTargetAngle(CGCharaObj* charaObj)
{
	return charaObj->m_targetAngle;
}

static float CharaObjGetRotateY(const Vec& vector)
{
	if (vector.x == kCharaObjZero && vector.z == kCharaObjZero) {
		return kCharaObjZero;
	}

	return static_cast<float>(atan2(vector.x, vector.z));
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
	if (charaObj->m_charaModelHandle->m_pdtLoadRef != 0) {
		return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(charaObj->m_charaModelHandle->m_pdtLoadRef) + 0x14);
	}
	return -1;
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

static int CharaObjIsAttackAnimBoundary(CGCharaObj* charaObj)
{
	bool valid = charaObj->m_charaModelHandle != 0 && charaObj->m_charaModelHandle->m_model != 0;
	if (!valid) {
		return 1;
	}

	CharaObjModelAnimState* model = reinterpret_cast<CharaObjModelAnimState*>(charaObj->m_charaModelHandle->m_model);
	if (model->m_anim != 0) {
		int span = static_cast<int>(kOneF32 + (model->m_animEnd - model->m_animStart));
		if (span == 1) {
			return 1;
		}

		int frame = static_cast<int>(charaObj->m_turnSpeed);
		int remainder = frame % span;
		if (charaObj->m_lastBgAttr < kCharaObjZero) {
			return __rlwnm(1, static_cast<unsigned int>(__cntlzw(remainder)), 31, 31) & 0xFF;
		}

		return (span <= frame) & 0xFF;
	}

	return 1;
}

static void CharaObjPutMonsterScaledParticle(CGCharaObj* charaObj, int particleNo, int slot, float scale)
{
	charaObj->putParticle(particleNo, slot, static_cast<CGObject*>(charaObj), FLOAT_803319AC * charaObj->m_attackColRadius * scale, 0);
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

static int& CharaObjComboItemId(CGCharaObj* charaObj)
{
	return charaObj->m_itemId;
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

struct CharaObjSignedTopBit
{
	signed char m_top : 1;
	signed char m_pad : 7;
};

struct CharaObjSignedLowBit
{
	signed char m_pad : 7;
	signed char m_low : 1;
};

struct CharaObjPartyFlag04
{
	unsigned char m_pad_hi : 5;
	unsigned char m_bit04 : 1;
	unsigned char m_pad_lo : 2;
};

struct CharaObjComboFlagBits
{
	signed char m_bit80 : 1;
	signed char m_nearby : 1;
	signed char m_bit20 : 1;
	signed char m_active : 1;
	signed char m_lo : 4;
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
	if (mag <= kCharaObjZero) {
		return false;
	}

	CVector scaledVec;
	PSVECScale(&delta, reinterpret_cast<Vec*>(&scaledVec), kOneF32 / mag);
	Vec scaledDelta;
	scaledDelta.x = scaledVec.x;
	scaledDelta.y = scaledVec.y;
	scaledDelta.z = scaledVec.z;

	CVector facing;
	facing.x = sinf(self->m_rotBaseY);
	facing.y = kCharaObjZero;
	facing.z = cosf(self->m_rotBaseY);
	float dot = PSVECDotProduct(&scaledDelta, reinterpret_cast<Vec*>(&facing));
	return dot > kCharaObjZero;
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

// Tests CFlatGameFlag_Bit5 (0x20) the way the original source did: the flag
// byte is sign-extracted through a signed char, which the compiler lowers to
// extlwi/srawi/extsb rather than a single rlwinm mask. Returns nonzero if set.
static int CharaObjGameFlagBit5Set()
{
	return static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(CFlatGameFlags()) << 26 >> 30) << 30 >> 31) != 0;
}

static int CharaObjDecodeHitParticleSe(unsigned short seData)
{
	return (seData == 0xFFFF) ? 0 : (seData & 0xFF) + static_cast<int>(seData >> 8) * 1000;
}

static int CharaObjDecodeSe(unsigned short encodedSe)
{
	if (encodedSe == 0xFFFF) {
		return 0;
	}
	return (encodedSe & 0xFF) + ((encodedSe >> 8) * 1000);
}

static int CharaObjResolveParticleBank(CGCharaObj* charaObj, int particleClass)
{
	switch (particleClass) {
	case 0xFE:
		return CharaObjGetModelPdtNo(charaObj);
	case 0xFD:
	case 0xFF:
		return -1;
	default:
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

	reinterpret_cast<CharaObjIgnoreFlagBits*>(reinterpret_cast<unsigned char*>(this) + 0x63C)->m_active = 0;
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

	switch (state) {
		case 0x12:
			{
				int i = 0;
				unsigned char* self = reinterpret_cast<unsigned char*>(this);
				for (; i < 0x16; i++, self += 4) {
					if (((1U << i) & 1U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(*reinterpret_cast<int*>(self + 0x564), 1);
					}
				}
			}
			break;

		case 2:
			{
				unsigned char* self = reinterpret_cast<unsigned char*>(this);
				int i = 0;
				for (; i < 0x16; i++, self += 4) {
					if (((1U << i) & 0x18U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(*reinterpret_cast<int*>(self + 0x564), 1);
					}
				}
			}
			break;

		case 6:
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
			break;
	}

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
	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x42) != 0) {
		if (m_stateTick != 0 &&
		    (m_stateTick % static_cast<int>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x3A))) == 0) {
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) > 1 &&
			    !CharaObjGameFlagBit5Set()) {
				playSe3D(0x19, 0x32, 0x96, 0, 0);
				addHp(-1, 0);
			}
		}
	}

	for (int statusOffset = 0, i = 0; i < 0x27; i++, statusOffset += 2) {
		int statusValue = static_cast<int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E + statusOffset)) - 1;
		if (statusValue != 0 && i == 2) {
			m_stateTick += 1;
		}

		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		    (i == 0 || i == 4 || i == 9 || i == 3) &&
		    statusValue > 0) {
			int slot = static_cast<signed char>(m_animStateMisc);
			unsigned short padMask;
			bool useDebugPad = (Pad.m_debugPadLock != 0) || ((slot == 0) && (Pad.m_debugPadPort != -1));
			if (useDebugPad) {
				padMask = 0;
			} else {
				int activePad = Pad.m_debugPadPort;
				int idx = slot & ~(static_cast<int>(~((activePad - slot) | (slot - activePad))) >> 31);
				padMask = Pad.GetPadInputs()[idx].buttonDown[0];
			}
			if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x100) != 0) {
				useDebugPad = (Pad.m_debugPadLock != 0) || ((slot == 0) && (Pad.m_debugPadPort != -1));
				unsigned short heldMask;
				if (useDebugPad) {
					heldMask = 0;
				} else {
					int activePad = Pad.m_debugPadPort;
					int idx = slot & ~(static_cast<int>(~((activePad - slot) | (slot - activePad))) >> 31);
					heldMask = Pad.GetPadInputs()[idx].stickBitsDown;
				}
				padMask |= heldMask;
			}
			if ((padMask & 0xF) != 0) {
				statusValue -= *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x3C);
				System.Printf(const_cast<char*>(sCharaObjGearGachaMsg));
			}
		}

		setSta(i, statusValue);
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) != 0 ||
	    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x50) != 0 ||
	    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x44) != 0) {
		m_displayFlags &= ~2;
		reinterpret_cast<CharaObjIgnoreFlagBits*>(reinterpret_cast<unsigned char*>(this) + 0x63C)->m_active = 0;
	} else {
		m_displayFlags |= 2;
	}

	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x54C) += 1;

	for (int i = 0; i < 4; i++) {
		if (m_ignoreHit[i].m_flagBits.m_flag_80) {
			int t = m_ignoreHit[i].m_timer;
			if (t != 0) {
				t -= 1;
				m_ignoreHit[i].m_timer = static_cast<short>(t);
				if (static_cast<short>(t) == 0) {
					m_ignoreHit[i].m_flagBits.m_flag_80 = 0;
				}
			}
		}
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
			float alphaWave = static_cast<float>(sin(static_cast<double>(FLOAT_803319B0 * static_cast<float>(createSerial))));
			float alphaDelta = FLOAT_803319B4 * alphaWave;
			alpha = alpha + alphaDelta;
		}
	}

	float slope = m_stepSlopeLimit;
	float clamped;
	if (alpha < kCharaObjZero) {
		clamped = kCharaObjZero;
	} else if (kOneF32 < alpha) {
		clamped = kOneF32;
	} else {
		clamped = alpha;
	}
	return slope * clamped;
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
	if ((m_weaponNodeFlagBits.m_prg && (static_cast<int>(CFlatCenterState()) == 0)) &&
	    ((DbgMenuPcs.GetDbgFlagsRaw() & 0x80) != 0)) {
		char text[0x100];
		unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
		double posYDouble;

		sprintf(text, sCharaObjDebugStatFormat,
		        *reinterpret_cast<unsigned short*>(script + 0x1C),
		        *reinterpret_cast<unsigned short*>(script + 0x1A),
		        *reinterpret_cast<unsigned short*>(script + 0x1E),
		        *reinterpret_cast<unsigned short*>(script + 0x20),
		        *reinterpret_cast<unsigned short*>(script + 0x22));

		posYDouble = (double)posY;
		font->SetPosX(-(0.5f * (float)font->GetWidth(text) - posX));
		font->SetPosY((float)posYDouble);
		font->SetPosZ((float)posZ);
		font->Draw(text);
		float glyphOffset = (float)(unsigned short)font->m_glyphHeight * font->scaleY;
		posY = posY - glyphOffset;
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
			m_partyDistance[i] = kCharaObjZero;
			m_partyDelta[i].z = kCharaObjZero;
			m_partyDelta[i].y = kCharaObjZero;
			m_partyDelta[i].x = kCharaObjZero;
			m_partyAngle[i] = kCharaObjZero;
		}

		m_partyRank[i] = 0;
		for (int j = 0; j < i; j++) {
			if (kCharaObjZero == m_partyDistance[i]) {
				m_partyRank[i] += 1;
			} else if (kCharaObjZero == m_partyDistance[j]) {
				m_partyRank[j] += 1;
			} else if (m_partyDistance[i] < m_partyDistance[j]) {
				m_partyRank[j] += 1;
			} else {
				m_partyRank[i] += 1;
			}
		}
	}

	m_pushScale = kOneF32;
#define CHARA_SCRIPT (reinterpret_cast<unsigned char*>(m_scriptHandle))
	if (*reinterpret_cast<unsigned short*>(CHARA_SCRIPT + 0x4E) != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x34)) * 0.01f) + 1.0e-07f;
	}
	if (*reinterpret_cast<unsigned short*>(CHARA_SCRIPT + 0x4C) != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x36)) * 0.01f) + 1.0e-07f;
	}
	if (*reinterpret_cast<unsigned short*>(CHARA_SCRIPT + 0x40) != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x40)) * 0.01f) + 1.0e-07f;
	}
#undef CHARA_SCRIPT
	float pushScale = m_pushScale;
	if (pushScale < FLOAT_803319B8[0]) {
	} else {
		pushScale = FLOAT_803319B8[0];
	}
	m_pushScale = pushScale;

	int push = 0;
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

	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
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
		int slot = static_cast<signed char>(m_animStateMisc);
		int padHeld;
		bool useDebugPad = (Pad.m_debugPadLock != 0) || ((slot == 0) && (Pad.m_debugPadPort != -1));
		if (useDebugPad) {
			padHeld = 0;
		} else {
			int activePad = Pad.m_debugPadPort;
			int idx = slot & ~(static_cast<int>(~((activePad - slot) | (slot - activePad))) >> 31);
			padHeld = Pad.GetPadInputs()[idx].gbaMode;
		}
		if (padHeld != 0) {
			push += 0x19;
		}
		if (static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(reinterpret_cast<unsigned char*>(this)[0x9B]) << 24 >> 30) << 30 >> 31) == 0) {
			push += 0x19;
		}
	}

	m_pushParamB = static_cast<unsigned char>(push < 0x19 ? push : 0x19);
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && static_cast<CGMonObj*>(this)->m_chaseState == 4) {
		m_pushParamB = 100;
	}

	if ((AStar.m_flags & 1) != 0) {
		m_aStarGroupId = static_cast<unsigned short>(AStar.calcSpecialPolygonGroup(&m_worldPosition));
	} else {
		m_aStarGroupId = static_cast<unsigned short>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0xE8));
	}
}

static float CharaObjGetStatusMultiplier(int offset)
{
	return (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + offset)) * 0.01f) + 1.0e-07f;
}

static float CharaObjGetMonsterScale(unsigned char* script9, bool isMon)
{
	if (!isMon || script9 == 0) {
		return kOneF32;
	}
	return static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0x1B4)) * 0.01f;
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
			switch (m_subState) {
				case 0:
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
					break;
				case 1:
					if (m_subFrame == 0) {
						reqAnim(m_unk554, 1, 0);
					}
					break;
				case 2:
					if (m_subFrame == 0) {
						{
							int i = 0;
							unsigned char* slot = reinterpret_cast<unsigned char*>(this);
							for (; i < 0x16; i++, slot += 4) {
								if ((8U & (1U << i)) != 0) {
									CFlatRuntime2Storage().EndParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
								}
							}
						}
						reqAnim(m_unk558, 0, 0);
					}

					if (m_itemId != 0 && m_subFrame == 10) {
						{
							unsigned char* slot = reinterpret_cast<unsigned char*>(this);
							int i = 0;
							for (; i < 0x16; i++, slot += 4) {
								if ((2U & (1U << i)) != 0) {
									CFlatRuntime2Storage().EndParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
								}
							}
						}
						putParticleFromItem(m_itemId, 2, m_particleSlots[1], &CharaObjComboCenter(this));
						putParticleFromItem(m_itemId, 3, m_particleSlots[1], &CharaObjComboCenter(this));
					}
					break;
			}

			onStatMagic();
			break;

		case 4:
			if (m_stateFrame == 0) {
				Sound.StopSe3DGroup(m_particleId);
				{
					unsigned char* slot = reinterpret_cast<unsigned char*>(this);
					int i = 0;
					for (; i < 0x16; i++, slot += 4) {
						if ((0x3BU & (1U << i)) != 0) {
							CFlatRuntime2Storage().DeleteParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
						}
					}
				}
				reqAnim(4, 0, 0);
			}

			if (isLoopAnim() != 0) {
				changeStat(0, 0, 0);
			}
			break;

		case 0x19:
			if (m_stateFrame == 0) {
				if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
					static_cast<CGPartyObj*>(this)->carry(1, 0, 1);
				}

				Sound.StopSe3DGroup(m_particleId);
				{
					unsigned char* slot = reinterpret_cast<unsigned char*>(this);
					int i = 0;
					for (; i < 0x16; i++, slot += 4) {
						if ((0x3BU & (1U << i)) != 0) {
							CFlatRuntime2Storage().DeleteParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
						}
					}
				}
				reqAnim(0x1D, 0, 0);
			}

			if (isLoopAnim() != 0) {
				changeStat(0, 0, 0);
			}
			break;

		case 9:
			if (m_subState == 0 && m_subFrame == 0) {
				Sound.StopSe3DGroup(m_particleId);
				{
					unsigned char* slot = reinterpret_cast<unsigned char*>(this);
					int i = 0;
					for (; i < 0x16; i++, slot += 4) {
						if ((0x3BU & (1U << i)) != 0) {
							CFlatRuntime2Storage().DeleteParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
						}
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
			switch (m_subState) {
			case 0:
				if (m_subFrame == 0) {
					Sound.StopSe3DGroup(m_particleId);
					{
						unsigned char* slot = reinterpret_cast<unsigned char*>(this);
						int i = 0;
						for (; i < 0x16; i++, slot += 4) {
							if ((0x3BU & (1U << i)) != 0) {
								CFlatRuntime2Storage().DeleteParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
							}
						}
					}
					reqAnim(0x1A, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeSubStat(1);
				}
				break;
			case 1:
				if (m_subFrame == 0) {
					reqAnim(0x1B, 1, 0);
				}

				if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x46) == 0) {
					changeSubStat(2);
				}
				break;
			case 2:
				if (m_subFrame == 0) {
					reqAnim(0x1C, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeStat(0, 0, 0);
				}
				break;
			}
			break;

		case 8:
			switch (m_subState) {
			case 0:
				if (m_subFrame == 0) {
					reqAnim(m_attackAnimId, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeSubStat(1);
					return;
				}
				break;
			case 1:
				if (m_subFrame == 0) {
					reqAnim(m_unk554, 1, 0);
				}
				break;
			case 2:
				if (m_subFrame == 0) {
					reqAnim(m_unk558, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeSubStat(1);
					return;
				}
				break;
			case 3:
				if (m_subFrame == 0) {
					reqAnim((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0) ? m_unk558 : m_unk55C, 0, 0);
				}

				if (isLoopAnim() != 0) {
					changeStat(0, 0, 0);
					return;
				}
				break;
			}

			onStatShield();
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

#pragma push
#pragma opt_common_subs off
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
		if ((sourceCid & 0x6D) == 0x6D &&
			*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x3B4) != 0) {
			return 0;
		}
	}

	for (int i = 0; i < 4; i++) {
		if (m_ignoreHit[i].m_flagBits.m_flag_80 != 0) {
			if (m_ignoreHit[i].m_source == sourceObj) {
				return 2;
			}
		} else {
			m_ignoreHit[i].m_flagBits.m_flag_80 = 1;
			m_ignoreHit[i].m_source = sourceObj;

			unsigned int particleIndex = static_cast<unsigned int>(m_itemId);
			SCharaItemRow* lifeRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			unsigned short particleLife = lifeRows[particleIndex].m_particleLife;
			m_ignoreHit[i].m_timer = (particleLife == 3) ? 0x1E : 0;
			goto foundSlot;
		}
	}
	return 2;

foundSlot:
	if ((sourceObj->m_objectFlags & 0x100) != 0) {
		changeStat(3, 0, 0);
	}

	sourceCid = sourceObj->GetCID();
	if ((sourceCid & 0x2D) == 0x2D) {
		static_cast<CGCharaObj*>(sourceObj)->onDamage(this, m_itemId, hitArg, hitType, hitPos);
	}

	return 1;
}
#pragma pop

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
	int particleBank;
	unsigned short particleSpec;
	unsigned short particleFlags;
	unsigned short seSpec;

	if (itemId == 0x1FA || itemId == 0x237) {
		particleOffset = l_idxAttackCol;
	}

	particleBank = static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + itemId * 0x48 + 0x12));
	if (particleBank != 0xFFFF && particleBank != 0xFF) {
		if (particleBank == 0xFE) {
			int sourceData = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0xF8);
			unsigned int effectData = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceData) + 0x178);
			particleBank = effectData != 0 ? *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(effectData) + 0x14)
			                               : 0xFFFFFFFF;
		}
		if (particleBank == 0xFD) {
			particleBank = 0xFFFFFFFF;
		}
		particleSpec = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + itemId * 0x48 + 0x1C);
		if (particleSpec != 0xFFFF) {
			if ((particleSpec & 0x1000) != 0) {
				particleBank = 1;
			} else if ((particleSpec & 0x2000) != 0) {
				particleBank = 2;
			} else if ((particleSpec & 0x4000) != 0) {
				particleBank = 3;
			}

			CFlatRuntime2Storage().ResetParticleWork((particleBank << 8) | ((particleSpec & 0xFF) + particleOffset), 0);
			SCharaItemRow* flagRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			particleFlags = flagRows[itemId].m_particleFlags;
			if ((particleFlags & 0x200) != 0) {
				CFlatRuntime2Storage().SetParticleWorkBind(this);
			} else {
				CFlatRuntime2Storage().SetParticleWorkPos(*l_pHitCross, kCharaObjZero);
			}
			CFlatRuntime2Storage().PutParticleWork();
		}
	}

	SCharaItemRow* seRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	seSpec = seRows[itemId].m_seSpec;
	int seNo = CharaObjDecodeHitParticleSe(seSpec);
	if (seNo != 0) {
		playSe3D(seNo + particleOffset, 0x32, 0x96, 0, 0);
	}
}

#pragma push
#pragma optimization_level 3
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
	if (static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&m_weaponNodeFlags)) << 24 >> 30) << 30 >> 31) == 0) {
		System.Printf(dbg + 0x160);
		return;
	}

	staType = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + resolvedItemId * 0x48 + 8);
	if (static_cast<int>(staType) != 0x67 && static_cast<int>(staType) != 0x65 && static_cast<int>(staType) != 0x66 && CharaObjGameFlagBit5Set()) {
		System.Printf(dbg + 0x17C);
		return;
	}

	int particleLife = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + resolvedItemId * 0x48 + 0xE);
	int itemEffect = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + resolvedItemId * 0x48);
	int scriptDefense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E);
	calcRegist(static_cast<int>(staType), resolvedItemId, resistType, allowEffect, effectResult, 0);

	if (resistType == 3) {
		if (staType == 4 || staType == 0x1C || static_cast<unsigned int>(staType) <= 2 ||
		    static_cast<unsigned int>(staType - 8) <= 2 || staType == 6 || staType == 3) {
			putParticle(0x201, 0, hitPos, FLOAT_803319A8 * (FLOAT_803319AC * m_attackColRadius), 0x65);
		} else if (static_cast<unsigned int>(staType - 0x24) <= 1 || staType == 0x69 || staType == 0x6A) {
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
		const CVector& sourcePos = CVector(sourceObj->m_worldPosition);
		CVector deltaVec;
		PSVECSubtract((Vec*)&sourcePos, reinterpret_cast<Vec*>(&selfPos), reinterpret_cast<Vec*>(&deltaVec));
		Vec frontDelta;
		frontDelta.x = deltaVec.x;
		frontDelta.y = deltaVec.y;
		frontDelta.z = deltaVec.z;
		float frontMag = PSVECMag(&frontDelta);
		if (frontMag > kCharaObjZero) {
			CVector scaledVec;
			PSVECScale(&frontDelta, reinterpret_cast<Vec*>(&scaledVec), kOneF32 / frontMag);
			frontDelta.x = scaledVec.x;
			frontDelta.y = scaledVec.y;
			frontDelta.z = scaledVec.z;
			CVector facing;
			facing.x = sinf(m_rotBaseY);
			facing.y = kCharaObjZero;
			facing.z = cosf(m_rotBaseY);
			if (PSVECDotProduct(&frontDelta, reinterpret_cast<Vec*>(&facing)) > kCharaObjZero) {
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
	    static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(*(reinterpret_cast<unsigned char*>(&m_weaponNodeFlags) + 1)) << 26 >> 30) << 30 >> 31) != 0) {
		SCharaItemRow* kindRows1556 = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		int currentKind = kindRows1556[m_itemId].m_status & 0xFF;
		if (currentKind == 2) {
			if (staType != 0x66 && staType != 0x67 && staType != 7) {
				CVector sourcePos(sourceObj->m_worldPosition);
				const CVector& selfPos = CVector(m_worldPosition);
				CVector deltaVec;
				PSVECSubtract((Vec*)&selfPos, reinterpret_cast<Vec*>(&sourcePos), reinterpret_cast<Vec*>(&deltaVec));
				Vec delta;
				delta.x = deltaVec.x;
				delta.y = deltaVec.y;
				delta.z = deltaVec.z;
				moveVectorH(&delta, FLOAT_803319A8, 10);
				m_rotTargetY = static_cast<float>(atan2(-static_cast<double>(delta.x), -static_cast<double>(delta.z)));
				changeStat(0x1A, 0, 0);
			}
		} else if (currentKind == 3) {
			allowEffect = 0;
			effectResult = 0;
		}
	}

	if (itemEffect == 0x1F8 &&
	    static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(*(reinterpret_cast<unsigned char*>(&sourceObj->m_weaponNodeFlags) + 1)) << 26 >> 30) << 30 >> 31) != 0 &&
	    ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + m_itemId * 0x48 + 0x0A) & 0xFF) == 3)) {
		CVector sourcePos(sourceObj->m_worldPosition);
		const CVector& selfPos = CVector(m_worldPosition);
		CVector deltaVec;
		PSVECSubtract((Vec*)&selfPos, reinterpret_cast<Vec*>(&sourcePos), reinterpret_cast<Vec*>(&deltaVec));
		Vec delta;
		delta.x = deltaVec.x;
		delta.y = deltaVec.y;
		delta.z = deltaVec.z;
		moveVectorH(&delta, FLOAT_803319A8, 10);
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
		int itemKind;
		if (resolvedItemId >= 0x1F5) {
			SCharaItemRow* kindRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			itemKind = kindRows[resolvedItemId].m_kind;
		} else {
			itemKind = 1;
		}

		if (itemKind == 1 || (itemKind == 9 && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D)) {
			switch (staType) {
			case 0x24:
			case 0x25:
			case 100:
			case 0x69:
			case 0x6A: {
				SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				unsigned int basePower = (itemEffect == 0x1F8) ? powerRows[resolvedItemId].m_basePower : 0;
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
				int clampedDamage = 1;
				float multiplier = CharaObjGetStatusMultiplier(0x2C);
				unsigned int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				int rawDamage = static_cast<int>(multiplier * static_cast<float>(static_cast<int>(basePower + sourcePower))) - defense;
				if (rawDamage >= 1) {
					clampedDamage = rawDamage;
				}
				unsigned char hasBonus = 0;
				if ((((static_cast<unsigned int>(__cntlzw(0x6D - (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D))) >> 5) & 0xFFU) != 0) && itemEffect == 0x1F8) {
					hasBonus = 1;
				}
				int bonus = hasBonus ? static_cast<int>(*reinterpret_cast<unsigned char*>(
					reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0xBDD)) : 0;
				damageAmount = clampedDamage + bonus;
				if (scriptDefense != 0) {
					damageAmount = static_cast<int>(static_cast<float>(damageAmount) * CharaObjGetStatusMultiplier(0x42));
				}
				System.Printf(dbg + 0x1A0, basePower, sourcePower, multiplier, defense, bonus, damageAmount);

				if (staType != 0x6A && (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
				    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 0x100) != 0 &&
				    (Game.m_gameWork.m_chaliceElement & 4U) == 0 &&
				    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x2E) == 0) {
					unsigned int srcEntryKind =
						*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(sourceObj) + 0x560) * 0x48 + 10) & 0xFF;
					if (sourceObj->m_lastStateId == 6 && srcEntryKind <= 1) {
						break;
					}
					reinterpret_cast<CGCharaObj*>(sourceObj)->setSta(4, 0x19);
					sourceObj->changeStat(10, 0, 0);
					reinterpret_cast<CGCharaObj*>(sourceObj)->addHp(-1, 0);
				}
				break;
			}
			case 0:
			case 1:
			case 4:
			case 0x1C: {
				SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				unsigned int basePower = powerRows[resolvedItemId].m_basePower;
				unsigned char condC = 0;
				unsigned char condB = 0;
				unsigned char condA = 0;
				if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
					condA = 1;
				}
				if (condA != 0) {
					if ((((static_cast<unsigned int>(__cntlzw(0x6D - (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D))) >> 5) & 0xFFU) != 0)) {
						condB = 1;
					}
				}
				if (condB != 0) {
					if (sourceObj->m_scriptHandle[0xED] != 0) {
						condC = 1;
					}
				}
				CGPrgObj* powerSource;
				if (condC != 0) {
					powerSource = Game.m_partyObjArr[0];
				} else {
					powerSource = sourceObj;
				}

				unsigned int sourcePower = *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(powerSource->m_scriptHandle) + 0x20);
				int clampedDamage = 1;
				float multiplier = CharaObjGetStatusMultiplier(0x2E);
				unsigned int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				int rawDamage = static_cast<int>(multiplier * static_cast<float>(static_cast<int>(basePower + sourcePower))) - defense;
				if (rawDamage >= 1) {
					clampedDamage = rawDamage;
				}
				unsigned int bonus = ((((static_cast<unsigned int>(__cntlzw(0x6D - (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D))) >> 5) & 0xFFU) != 0)) ?
					static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(
						reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0xBDE)) : 0;
				damageAmount = clampedDamage + bonus;
				System.Printf(dbg + 0x1DC, basePower, sourcePower, multiplier, defense, bonus, damageAmount);
				break;
			}
			case 10: {
				int recoilDamage;
				unsigned char* selfReactive = reinterpret_cast<unsigned char*>(this) + 0x6C2;
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && *selfReactive != 0) {
					recoilDamage = 1;
				} else {
					float recoilRate = (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x26 + resistType * 2)) * 0.01f) + 1.0e-07f;
					int raw = static_cast<int>(static_cast<float>(static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C))) * recoilRate);
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
			case 0x24:
			case 0x25:
			case 100:
			case 0x69:
			case 0x6A: {
				int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				unsigned int basePower = powerRows[resolvedItemId].m_basePower;
				unsigned int sourcePower = *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x1E);
				float multiplier = CharaObjGetStatusMultiplier(0x30);
				int guardValue = static_cast<int>(defense * multiplier);
				int computed30 = static_cast<int>(basePower + sourcePower) - guardValue;
				damageAmount = 1;
				if (computed30 >= 1) {
					damageAmount = computed30;
				}
				if (scriptDefense != 0) {
					damageAmount = static_cast<int>(damageAmount * CharaObjGetStatusMultiplier(0x42));
				}
				System.Printf(dbg + 0x240, basePower, sourcePower, defense, multiplier, damageAmount);
				break;
			}
			case 0:
			case 1:
			case 2:
			case 4:
			case 0x1C: {
				int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				unsigned int basePower = powerRows[resolvedItemId].m_basePower;
				unsigned int sourcePower = *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x20);
				float multiplier = CharaObjGetStatusMultiplier(0x32);
				int guardValue = static_cast<int>(defense * multiplier);
				int computed32 = static_cast<int>(basePower + sourcePower) - guardValue;
				damageAmount = 1;
				if (computed32 >= 1) {
					damageAmount = computed32;
				}
				System.Printf(dbg + 0x274, basePower, sourcePower, defense, multiplier, damageAmount);
				break;
			}
			case 10: {
				float recoilRate = (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x26 + resistType * 2)) * 0.01f) + 1.0e-07f;
				int raw = static_cast<int>(static_cast<float>(static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x1C))) * recoilRate);
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
				SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				unsigned int basePower = powerRows[resolvedItemId].m_basePower;
				unsigned short rawSourcePower;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					rawSourcePower = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0x20);
				} else {
					SCharaItemRow* srcPowerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
					rawSourcePower = srcPowerRows[resolvedItemId].m_sourcePower;
				}
				unsigned int sourcePower = rawSourcePower;
				unsigned int defense = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x22);
				float defenseRate = kOneF32;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					defenseRate = CharaObjGetStatusMultiplier(0x32);
				}
				int guardValue = static_cast<int>(static_cast<float>(static_cast<int>(defense)) * defenseRate);
				int computedGuard = static_cast<int>(basePower + sourcePower) - guardValue;
				damageAmount = 1;
				if (computedGuard >= 1) {
					damageAmount = computedGuard;
				}
				System.Printf(dbg + 0x2BC, basePower, sourcePower, defense, defenseRate, damageAmount);
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
			if (damageAmount <= 1) {
				damageAmount = 0;
			} else {
				damageAmount = 1;
			}
		}

		if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 4) != 0 &&
		    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x52) == 0) {
			damageAmount = (damageAmount >= 1) ? 1 : damageAmount;
		}
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x76) == 0 && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0 &&
		    staType != 0x1C) {
			damageAmount = (damageAmount >= 1) ? 1 : damageAmount;
		}
		CGCharaObj* sourceChara = reinterpret_cast<CGCharaObj*>(sourceObj);
		if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x2D) == 0x2D && sourceChara->m_comboItemState >= 0 &&
		    sourceChara->m_comboLinkCount != 0) {
			System.Printf(dbg + 0x2F8);
			damageAmount *= sourceChara->m_comboLinkCount;
		}

		if (damageAmount != 0) {
			addHp(-damageAmount, sourceObj);
			int selfNoGuard = (static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(
				*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C)))) >> 5) & 0xFF;
			if (selfNoGuard != 0) {
				bonus(0, resolvedItemId, sourceObj);
				sourceObj->bonus(1, resolvedItemId, this);
			}
			SCharaItemRow* bonusRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			if ((bonusRows[resolvedItemId].m_flags32 & 1) != 0 ||
			    ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && sourceChara->m_comboItemState >= 0)) {
				bonus(0x15, resolvedItemId, sourceObj);
				sourceObj->bonus(0x11, resolvedItemId, this);
				if (selfNoGuard != 0) {
					sourceObj->bonus(0xC, resolvedItemId, this);
				}
				for (int i = 0; i < sourceChara->m_comboLinkCount; i++) {
					sourceChara->m_comboLinks[i]->bonus(0x11, resolvedItemId, this);
					if (selfNoGuard != 0) {
						sourceChara->m_comboLinks[i]->bonus(0xC, resolvedItemId, this);
					}
				}
			} else {
				if (itemEffect == 0x1F8 || particleLife != 2) {
					if (itemEffect == 0x1F8) {
						bonus(0x13, resolvedItemId, sourceObj);
						sourceObj->bonus(0xF, resolvedItemId, this);
						if (selfNoGuard != 0) {
							sourceObj->bonus(10, resolvedItemId, this);
						}
					} else {
						bonus(0x12, resolvedItemId, sourceObj);
						sourceObj->bonus(0xE, resolvedItemId, this);
						if (selfNoGuard != 0) {
							sourceObj->bonus(9, resolvedItemId, this);
						}
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
				switch (counterState) {
				case 0:
					counterType = 1;
					counterItem = 0x207;
					counterSe = 0x7E1;
					break;
				case 1:
					counterType = 0;
					counterItem = 0x20B;
					counterSe = 0x7E2;
					break;
				case 2:
					counterType = 4;
					counterItem = 0x20F;
					counterSe = 0x7E3;
					break;
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
					if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
						chance = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x19A);
					} else {
						chance = 0x32;
					}
					if (chance != 0 && (DbgMenuPcs.GetDbgFlagsRaw() & 0x20) != 0) {
						chance = 100;
					}
					if (chance != 0 && static_cast<unsigned int>(Math.Rand(100)) <= static_cast<unsigned int>(chance)) {
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
		int tailNoGuard = (static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C)))) >> 5) & 0xFF;
		bonus(0x14, resolvedItemId, sourceObj);
		sourceObj->bonus(0x10, resolvedItemId, this);
		if (tailNoGuard != 0) {
			sourceObj->bonus(0x0B, resolvedItemId, this);
		}
	}

}
#pragma pop
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
	int clampedValue;
	int slotOff;
	int isIceJ = 0;
	int isMon = 0;
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
		isMon = 1;
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFC) == 0xB) {
			isIceJ = 1;
		}
	}

	slotOff = staIndex * 2;
	int current = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + slotOff + 0x3E);
	clampedValue = value & ~(value >> 31);

	if (current != 0 || clampedValue == 0) {
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
					putParticle((modelPdtNo << 8) | 0x16, 0, this, kOneF32, 0);
				} else {
					putParticle(0x10B, 0, this, FLOAT_803319AC * m_attackColRadius, 0);
				}
				playSe3D(0x16, 0x32, 0x96, 0, 0);
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
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
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 4) != 0 &&
					*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
					reinterpret_cast<CGMonObj*>(this)->flyUp();
				}
				break;
			case 0x1C:
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0) {
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
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					monsterScale = static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x1B4)) * 0.01f;
				} else {
					monsterScale = kOneF32;
				}
				int particleNo = isMon ? 0x6D : 0x11;
				float scaledRadius = FLOAT_803319AC * m_attackColRadius;
				putParticle(particleNo | 0x100, 0, this, scaledRadius * monsterScale, 0);
				break;
			}
			case 8: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x2000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				float monsterScale;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					monsterScale = static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x1B4)) * 0.01f;
				} else {
					monsterScale = kOneF32;
				}
				int particleNo = isMon ? 0x6F : 0x13;
				float scaledRadius = FLOAT_803319AC * m_attackColRadius;
				putParticle(particleNo | 0x100, 0, this, scaledRadius * monsterScale, 0);
				break;
			}
			case 7: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x8000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				int particleNo = isMon ? 0x71 : 0x15;
				putParticle(particleNo | 0x100, 0, this, FLOAT_803319AC * m_attackColRadius, 0);
				break;
			}
			case 3:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x40000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticle(0x10E, 0, this, FLOAT_803319AC * m_attackColRadius, 0);
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
				break;
			default:
				break;
		}
	} else {
		switch (staIndex) {
			case 0x1B:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x400U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticle(0x11C, m_particleSlots[10], this, kOneF32, 0x1290D);
				break;
			case 1:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x40U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				if (isIceJ) {
					int modelPdtNo = CharaObjGetModelPdtNo(this);
					putParticle((modelPdtNo << 8) | 0x14, m_particleSlots[6], this, kOneF32, 0);
				} else {
					putParticle(0x12A, m_particleSlots[6], this, FLOAT_803319AC * m_attackColRadius, 0);
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
					putParticleBindTrace((modelPdtNo << 8) | 0x15, m_particleSlots[2], this, kOneF32, 0);
				} else {
					putParticle(0x10A, m_particleSlots[2], this, FLOAT_803319AC * m_attackColRadius, 0);
				}
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
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
					putParticle((modelPdtNo << 8) | 0x17, m_particleSlots[7], this, kOneF32, 0);
				} else {
					putParticle(0x130, m_particleSlots[7], this, FLOAT_803319AC * m_attackColRadius, 0);
				}
				break;
			case 10:
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 4) != 0) {
					reinterpret_cast<CGMonObj*>(this)->flyDown();
				}
				break;
			case 0x1C:
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0) {
					reinterpret_cast<CGMonObj*>(this)->undeadOff();
				}
				break;
			case 9: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x4000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				float monsterScale;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					monsterScale = static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x1B4)) * 0.01f;
				} else {
					monsterScale = kOneF32;
				}
				int particleNo = isMon ? 0x6C : 0x10;
				float scaledRadius = FLOAT_803319AC * m_attackColRadius;
				putParticle(particleNo | 0x100, m_particleSlots[14], this, scaledRadius * monsterScale, 0);
				break;
			}
			case 8: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x2000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				float monsterScale;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					monsterScale = static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x1B4)) * 0.01f;
				} else {
					monsterScale = kOneF32;
				}
				int particleNo = isMon ? 0x6E : 0x12;
				float scaledRadius = FLOAT_803319AC * m_attackColRadius;
				putParticle(particleNo | 0x100, m_particleSlots[13], this, scaledRadius * monsterScale, 0);
				break;
			}
			case 7: {
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x8000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				int particleNo = isMon ? 0x70 : 0x14;
				putParticle(particleNo | 0x100, m_particleSlots[15], this, FLOAT_803319AC * m_attackColRadius, 0);
				break;
			}
			case 3:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x40000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticleBindTrace(0x10D, m_particleSlots[18], this, FLOAT_803319AC * m_attackColRadius, 0);
				break;
			case 2:
				m_castTimeTick = 0;
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x80000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticleBindTrace(0x10C, m_particleSlots[19], this, FLOAT_803319AC * m_attackColRadius, 0);
				break;
			case 6:
				for (int i = 0; i < 0x16; i++) {
					if (((1U << i) & 0x100000U) != 0) {
						CFlatRuntime2Storage().EndParticleSlot(m_particleSlots[i], 1);
					}
				}
				putParticleBindTrace(0x107, m_particleSlots[20], this, FLOAT_803319AC * m_attackColRadius, 0);
				break;
			case 0x67:
			case 0x68:
			default:
				break;
		}
	}

	*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + slotOff + 0x3E) = static_cast<short>(clampedValue);
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
				const CVector& selfPos = CVector(m_worldPosition);
				CVector deltaVec;
				PSVECSubtract((Vec*)&selfPos, reinterpret_cast<Vec*>(&sourcePos), reinterpret_cast<Vec*>(&deltaVec));
				Vec delta;
				delta.x = deltaVec.x;
				delta.y = deltaVec.y;
				delta.z = deltaVec.z;
				moveVectorH(&delta, FLOAT_803319A8, 8);
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
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) != 0) {
				setSta(0, 0);
				setSta(1, 0);
				outValue = 0;
			} else {
				setSta(1, calcSta(1, amount, reinterpret_cast<CGObject*>(sourceObj)));
				setSta(4, 0);
			}
			break;
		case 0:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x40) != 0) {
				setSta(0, 0);
				setSta(1, 0);
				outValue = 0;
			} else {
				setSta(0, calcSta(0, amount, reinterpret_cast<CGObject*>(sourceObj)));
				setSta(4, 0);
				Sound.StopSe3DGroup(m_particleId);
				{
					int i = 0;
					unsigned char* slot = reinterpret_cast<unsigned char*>(this);
					for (; i < 0x16; i++, slot += 4) {
						if (((1U << i) & 0x3bU) != 0) {
							CFlatRuntime2Storage().DeleteParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
						}
					}
				}
				changeStat(0, 0, 0);
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
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x4C) != 0) {
				setSta(7, 0);
				setSta(8, 0);
			} else {
				setSta(8, calcSta(8, amount, reinterpret_cast<CGObject*>(sourceObj)));
				putHitParticleFromItem(sourceObj, amount);
			}
			outValue = 0;
			break;
		case 7:
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x4E) != 0) {
				setSta(7, 0);
				setSta(8, 0);
			} else {
				setSta(7, calcSta(7, amount, reinterpret_cast<CGObject*>(sourceObj)));
				putHitParticleFromItem(sourceObj, amount);
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
			{
				unsigned char* slot = reinterpret_cast<unsigned char*>(this);
				int i = 0;
				for (; i < 0x16; i++, slot += 4) {
					if (((1U << i) & 0x3bU) != 0) {
						CFlatRuntime2Storage().DeleteParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
					}
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
			{
				unsigned char* slot = reinterpret_cast<unsigned char*>(this);
				int i = 0;
				for (; i < 0x16; i++, slot += 4) {
					if (((1U << i) & 0x3bU) != 0) {
						CFlatRuntime2Storage().DeleteParticleSlot(*reinterpret_cast<int*>(slot + 0x564), 1);
					}
				}
			}
			changeStat(0, 0, 0);
			break;
	}
}

#pragma push
#pragma optimization_level 2
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
	if (staIndex == 0 || staIndex == 4) {
		SCharaStaBlock* staBlock = reinterpret_cast<SCharaStaBlock*>(m_scriptHandle);
		if (staBlock->m_sta[staIndex] != 0) {
			System.Printf(const_cast<char*>(sCharaObjEffectTimeNoOverwriteMsg));
			return static_cast<int>(staBlock->m_sta[staIndex]);
		}
	}

	unsigned int base = 0;
	switch (staIndex) {
		case 1:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x0E);
			break;
		case 0:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x10);
			break;
		case 4:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x12);
			break;
		case 8:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x14);
			break;
		case 9:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x16);
			break;
		case 7:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x18);
			break;
		case 10:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x1A);
			break;
		case 0x1C:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x1C);
			break;
		case 2:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x1E);
			break;
		case 6:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x20);
			break;
		case 3:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x22);
			break;
		case 0x6A:
			base = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x24);
			break;
		default:
			break;
	}

	int itemType;
	if (amount >= 0x1F5) {
		SCharaItemRow* kindRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		itemType = kindRows[amount].m_kind;
	} else {
		itemType = 1;
	}

	CGPrgObj* sourceObj = reinterpret_cast<CGPrgObj*>(source);
	unsigned short powerValue;
	if ((((static_cast<unsigned int>(__cntlzw(0x2D - (static_cast<unsigned short>(source->GetCID()) & 0x2D)))) >> 5) & 0xFFU) != 0) {
		unsigned char usePartyLeader = 0;
		unsigned char usePartySource = 0;
		unsigned char stageModeActive = 0;

		if (static_cast<int>(Game.m_gameWork.m_menuStageMode) != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			stageModeActive = 1;
		}
		if (stageModeActive != 0) {
			if ((((static_cast<unsigned int>(__cntlzw(0x6D - (static_cast<unsigned short>(source->GetCID()) & 0x6D)))) >> 5) & 0xFFU) != 0) {
				usePartySource = 1;
			}
		}
		if (usePartySource != 0 && sourceObj->m_scriptHandle[0xED] != 0) {
			usePartyLeader = 1;
		}

		CGPrgObj* powerSource;
		if (usePartyLeader != 0) {
			powerSource = Game.m_partyObjArr[0];
		} else {
			powerSource = sourceObj;
		}
		powerValue = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(powerSource->m_scriptHandle[9]) + 0x198);
	} else {
		SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		powerValue = powerRows[amount].m_power;
	}

	unsigned int power = powerValue;
	if ((static_cast<unsigned short>(source->GetCID()) & 0xAD) == 0xAD) {
		int stageLevel;
		if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			int rawStage = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
			stageLevel = 2;
			if (rawStage < 2) {
				stageLevel = rawStage;
			}
		} else {
			stageLevel = 0;
		}

		if (stageLevel > 0) {
			power += reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x5C)[stageLevel];
		}
	}

	unsigned int affinity = 0;
	if ((static_cast<unsigned short>(source->GetCID()) & 0x6D) == 0x6D && (itemType == 1 || itemType == 9)) {
		affinity = static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(sourceObj->m_scriptHandle) + 0xBDA));
	}

	int selfCid = static_cast<unsigned short>(GetCID());
	if ((selfCid & 0x6D) == 0x6D && (itemType == 8 || itemType == 9)) {
		affinity -= *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBDB);
	}

	unsigned int next = affinity + (base * power);
	next &= ~((static_cast<int>(next)) >> 31);
	System.Printf(const_cast<char*>(sCharaObjEffectTimeCalcFmt), base, power, affinity, next);
	return static_cast<int>(next);
}
#pragma pop

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
	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && (DbgMenuPcs.GetDbgFlagsRaw() & 4) != 0) {
		return;
	}

	int hpValue = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C);
	int next = hpValue;

	if (hpValue != 0 && delta < 0) {
		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		    reinterpret_cast<CharaObjSignedLowBit*>(&CFlatGameFlags())->m_low != 0 &&
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

		next = (hpValue + delta) & ~(static_cast<int>(hpValue + delta) >> 31);
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) = static_cast<unsigned short>(next);
		m_worldParam = kOneF32;

		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
			CGPartyObj* party = static_cast<CGPartyObj*>(this);
			if (reinterpret_cast<CharaObjSignedTopBit*>(&party->m_partyData.partyFlags)->m_top) {
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
			for (int i = 2; i < *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBAA); i++) {
				if (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->DelCmdListAndItem(i) == 0x125) {
					reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetNumCombi(i, 1);
					reinterpret_cast<CharaObjPartyFlag04*>(&party->m_partyData.partyFlags)->m_bit04 = 1;
					return;
				}
			}
		}
		return;
	}

	if (delta > 0) {
		int maxHp = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A);
		int result = maxHp;
		if (hpValue + delta < maxHp) {
			result = hpValue + delta;
		}
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) = static_cast<unsigned short>(result);
	}
}

#pragma push
#pragma optimization_level 2
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
		case 0x24:
		case 0x25:
		case 0x69:
		case 0x6A:
		case 0x6B:
		case 100:
			outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x28);
			break;
		case 1: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x2A); break;
		case 0: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x2C); break;
		case 4: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x2E); break;
		case 8: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x30); break;
		case 9: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x32); break;
		case 10: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x34); break;
		case 0x1C: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x36); break;
		case 2: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x38); break;
		case 6: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3A); break;
		case 3: outA = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3C); break;
		default:
			break;
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x76) == 0 && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 1) != 0 &&
		staIndex != 0x1C) {
		int clamped = 2;
		if (outA >= 2) {
			clamped = outA;
		}
		outA = clamped;
	}
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0xFE) & 4) != 0 &&
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x52) == 0) {
		int clamped = 2;
		if (outA >= 2) {
			clamped = outA;
		}
		outA = clamped;
	}

	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x10) == 0x7F &&
	    static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(CGMonObj::m_boss[0x10]) << 24 >> 30) << 30 >> 31) != 0) {
		outA = 3;
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x74) != 0) {
		outA = 3;
	}

	System.Printf(const_cast<char*>(sCharaObjResistanceFmt), outA);

	switch (outA) {
	case 0:
		outB = 1;
		break;
	case 1:
		outB = (isNormal != 0) ? 1 : 0;
		break;
	default:
		outB = 0;
		break;
	}
	int xorA = outA ^ 3;
	outC = static_cast<unsigned int>((xorA >> 1) - (xorA & 3)) >> 31;
}
#pragma pop


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
				if (m_lastBgAttr < kCharaObjZero) {
					result = __rlwnm(1, static_cast<unsigned int>(__cntlzw(frameMod)), 31, 31) & 0xFF;
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
#pragma push
#pragma optimization_level 3
void CGCharaObj::putParticleFromItem(int effectId, int effectArg0, int effectArg1, Vec* pos)
{
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + effectId * 0x48;
	unsigned int particleClass = *reinterpret_cast<unsigned short*>(itemData + 0x12);
	int particleBank = CharaObjResolveParticleBank(this, particleClass);
	unsigned short particleEntry;
	int particleNo;
	int seNo = 0;
	int emittedCustom = 0;
	int hasParticle = 0;

	if (particleBank != -1) {
		SCharaItemRow* entryRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		particleEntry = entryRows[effectId].m_particleEntries[effectArg0];
		if (particleEntry != 0xFFFF) {
			particleNo = particleEntry & 0xFF;

			if ((particleEntry & 0x1000) != 0) {
				particleBank = 1;
			} else if ((particleEntry & 0x2000) != 0) {
				particleBank = 2;
			} else if ((particleEntry & 0x4000) != 0) {
				particleBank = 3;
			} else if (particleBank == 1 && particleNo < 8) {
				particleNo += *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0);
			}

			if ((particleEntry & 0x800) != 0) {
				particleNo += *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2);
			}
			hasParticle = 1;
		}
	}

	if (hasParticle == 0) {
		if (effectArg0 == 2) {
			unsigned short seSpec = *reinterpret_cast<unsigned short*>(itemData + 0x40);
			seNo = (seSpec == 0xFFFF) ? 0 : ((seSpec & 0xFF) + ((seSpec >> 8) * 1000));
			if (seNo != 0) {
				int seHandle = playSe3D(seNo, 0x32, 0x96, 0, pos);
				Sound.SetSe3DGroup(seHandle, m_particleId);
			}
	}
	} else {
		CFlatRuntime2Storage().ResetParticleWork((particleBank << 8) | particleNo, effectArg1);
		CFlatRuntime2Storage().SetParticleWorkScale(*reinterpret_cast<short*>(itemData + 0x10) * 0.01f);
		CFlatRuntime2Storage().SetParticleWorkParam(effectId, this);
		CFlatRuntime2Storage().SetParticleWorkSpeed(*reinterpret_cast<short*>(itemData + 0x26) * 0.01f);

		switch (effectArg0) {
		case 0: {
			unsigned char* seData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + effectId * 0x48;
			int decoded = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(seData + 0x38));
			if (decoded != 0) {
				unsigned short seFlag = *reinterpret_cast<unsigned short*>(seData + 0x3A);
				if ((seFlag & 0x8000) != 0) {
					CFlatRuntime2Storage().SetParticleWorkSe(decoded, 2, seFlag & 0xFF);
				} else {
					seNo = decoded;
				}
			}
			break;
		}
		case 1: {
			unsigned char* seData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + effectId * 0x48;
			int decoded = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(seData + 0x3C));
			if (decoded != 0) {
				unsigned short seFlag = *reinterpret_cast<unsigned short*>(seData + 0x3E);
				if ((seFlag & 0x8000) != 0) {
					CFlatRuntime2Storage().SetParticleWorkSe(decoded, 2, seFlag & 0xFF);
				} else {
					seNo = decoded;
				}
			}
			break;
		}
		case 2: {
			unsigned char* seData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + effectId * 0x48;
			int decoded = CharaObjDecodeSe(*reinterpret_cast<unsigned short*>(seData + 0x40));
			if (decoded != 0) {
				if ((*reinterpret_cast<unsigned short*>(seData + 0x0C) & 0x400) != 0) {
					CFlatRuntime2Storage().SetParticleWorkSe(decoded, 2, 0);
				} else {
					seNo = decoded;
				}
			}
			break;
		}
		default:
			break;
		}

		if (effectId >= 501) {
			unsigned char* colData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + effectId * 0x48;
			int itemType = *reinterpret_cast<unsigned short*>(colData + 2);
			int colType;
			switch (itemType) {
			case 1:
				colType = 1;
				break;
			case 8:
				colType = 8;
				break;
			case 4:
				colType = 4;
				break;
			case 9:
				colType = 9;
				break;
			}
			CFlatRuntime2Storage().SetParticleWorkCol(colType, -1, *reinterpret_cast<unsigned short*>(colData + 4) * 0.01f);
		}

		if ((particleEntry & 0x100) != 0) {
			CFlatRuntime2Storage().SetParticleWorkBind(this);
		} else if ((particleEntry & 0x200) != 0) {
			float distance = *reinterpret_cast<short*>(itemData + 0x2A) * 1.0f;
			Vec offsetPos;
			offsetPos.x = m_worldPosition.x + sinf(m_rotTargetY) * distance;
			offsetPos.y = m_worldPosition.y;
			offsetPos.z = m_worldPosition.z + cosf(m_rotTargetY) * distance;
			CFlatRuntime2Storage().SetParticleWorkPos(offsetPos, m_rotTargetY);
			CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, kCharaObjZero);
			if ((*reinterpret_cast<unsigned short*>(itemData + 0x0C) & 0x2000) != 0) {
				int partyIndex = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6C4);
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
		} else if ((particleEntry & 0x400) != 0) {
			CFlatRuntime2Storage().SetParticleWorkPos(m_jumpOffset, kCharaObjZero);
		} else {
			CFlatRuntime2Storage().SetParticleWorkPos(m_worldPosition, m_rotTargetY);
		}

		switch (effectId) {
		case 0x410:
			if (effectArg0 == 2 || effectArg0 == 3) {
				float baseAngle = m_rotTargetY;
				float angleOffset;
				if (effectArg0 == 2) {
					angleOffset = kCharaObjHalfPi;
				} else {
					angleOffset = kCharaObjNegativeHalfPi;
				}
				float angle = baseAngle + angleOffset;
				CFlatParticleWorkPosition().x = kCharaObjSideParticleRadius * sinf(angle) + m_worldPosition.x;
				CFlatParticleWorkPosition().z = kCharaObjSideParticleRadius * cosf(angle) + m_worldPosition.z;
				CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, kCharaObjZero);
				CFlatRuntime2Storage().PutParticleWork();
				emittedCustom = 1;
			}
			break;
		case 0x3B4:
			if (effectArg0 == 3) {
				if (pos == 0) {
					return;
				}
				CFlatRuntime2Storage().SetParticleWorkPos(*pos, m_rotTargetY);
				CFlatRuntime2Storage().PutParticleWork();
				emittedCustom = 1;
			}
			break;
		case 0x473:
		case 0x474:
		case 0x475:
		case 0x476:
		case 0x477:
		case 0x478:
			if (effectArg0 == 3) {
				for (int i = 7; i <= 0x0B; i++) {
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | i);
					CFlatRuntime2Storage().PutParticleWork();
				}
				emittedCustom = 1;
			}
			break;
		case 0x46D:
		case 0x46E:
			if (effectArg0 == 2) {
				if (m_stateFrame >= 0x10) {
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | 0x1D);
					float rand0 = Math.RandFPM(kCharaObjForwardParticleOffset);
					float rand1 = Math.RandFPM(kCharaObjForwardParticleOffset);
					CVector randomOffset(rand1, kCharaObjZero, rand0);
					const CVector& randomBase = CVector(kCharaObjZero, FLOAT_8033199C, FLOAT_803319A0);
					CVector randomResult;
					PSVECAdd((Vec*)&randomBase, reinterpret_cast<Vec*>(&randomOffset), reinterpret_cast<Vec*>(&randomResult));
					Vec randomPos;
					randomPos.x = randomResult.x;
					randomPos.y = randomResult.y;
					randomPos.z = randomResult.z;
					CFlatRuntime2Storage().SetParticleWorkPos(randomPos, m_rotTargetY);
					CFlatRuntime2Storage().PutParticleWork();
				}
				emittedCustom = 1;
			}
			if (effectArg0 == 3) {
				for (int i = 0x0D; i <= 0x1C; i++) {
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | i);
					CFlatRuntime2Storage().PutParticleWork();
				}
				emittedCustom = 1;
			}
			break;
		case 0x206: {
			if (effectArg0 == 2) {
				int a = m_unk68C;
				int b = m_comboFramePrev;
				if (a * 3 <= b) {
					CFlatRuntime2Storage().SetParticleWorkSe(0x872, 2, 0);
				} else if (a * 2 <= b) {
					CFlatRuntime2Storage().SetParticleWorkSe(0x871, 2, 0);
				}
			}
			if (effectArg0 == 3) {
				int a = m_unk68C;
				int b = m_comboFramePrev;
				if (a * 3 <= b) {
					CFlatRuntime2Storage().SetParticleWorkNo(particleNo | (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) + 0x75));
				} else if (a * 2 <= b) {
					CFlatRuntime2Storage().SetParticleWorkNo(particleNo | (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) + 0x73));
				}
			}
			break;
		}
		case 0x409:
			if (effectArg0 == 3) {
				for (int i = 3; i <= 8; i++) {
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | i);
					CFlatRuntime2Storage().PutParticleWork();
				}
				emittedCustom = 1;
			}
			break;
		case 0x49D:
		case 0x49E:
		case 0x49F:
			if (effectArg0 == 2) {
				Mtx rotMtx;
				PSMTXRotRad(rotMtx, 'y', m_rotTargetY);
				for (int i = 0; i < 2; i++) {
					int side = (i == 0) ? 76 : -76;
					const CVector& sidePos = CVector(static_cast<float>(side), kCharaObjZero, kCharaObjForwardParticleOffset);
					Vec offsetPos;
					PSMTXMultVec(rotMtx, (Vec*)&sidePos, &offsetPos);
					CFlatParticleWorkPosition().x = m_worldPosition.x + offsetPos.x;
					CFlatParticleWorkPosition().y = m_worldPosition.y + offsetPos.y;
					CFlatParticleWorkPosition().z = m_worldPosition.z + offsetPos.z;
					CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, kCharaObjZero);
					CFlatRuntime2Storage().PutParticleWork();
				}
				emittedCustom = 1;
			}
			break;
		default:
			break;
		}

		if (seNo != 0) {
			unsigned char useArgPos = 1;
			if (effectArg0 != 2) {
				useArgPos = 0;
			}
			int seHandle = playSe3D(seNo, 0x32, 0x96, 0, (useArgPos != 0) ? pos : 0);
			Sound.SetSe3DGroup(seHandle, m_particleId);
		}

		if (!emittedCustom) {
			int fanCount = *reinterpret_cast<unsigned short*>(itemData + 0x24);
			if (effectArg0 == 3 && fanCount > 1) {
				for (int i = 0; i < fanCount; i++) {
					CFlatRuntime2Storage().SetParticleWorkVector(FLOAT_803319A4 * static_cast<float>(i) / static_cast<float>(fanCount), kCharaObjZero);
					CFlatRuntime2Storage().PutParticleWork();
				}
			} else {
				CFlatRuntime2Storage().PutParticleWork();
			}
		}
		}
}
#pragma pop

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

#pragma push
#pragma optimization_level 3
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
			if (CharaObjIsAttackAnimBoundary(this)) {
				m_subState = 1;
				m_stateFrame = 0;
			} else {
				return;
			}
		}
	}

	onStatAttack(0);

	if (m_stateFrame == 0) {
		m_ignoreHit[0].m_flagBits.m_flag_80 = 0;
		m_ignoreHit[1].m_flagBits.m_flag_80 = 0;
		m_ignoreHit[2].m_flagBits.m_flag_80 = 0;
		m_ignoreHit[3].m_flagBits.m_flag_80 = 0;

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
		int seSpec = *reinterpret_cast<unsigned short*>(itemData + 0x38);
		if (seSpec != 0) {
			int seNo = (seSpec == 0xFFFF) ? 0 : ((seSpec & 0xFF) + ((seSpec >> 8) * 1000));
			playSe3D(seNo, 0x32, 0x96, 0, 0);
		}
	}

	itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + m_itemId * 0x48;
	seFrame = *reinterpret_cast<unsigned short*>(itemData + 0x3E);
	if ((seFrame & 0x8000) == 0 && m_stateFrame == seFrame) {
		int seSpec = *reinterpret_cast<unsigned short*>(itemData + 0x3C);
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
#pragma pop

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
	char* fmt = s_CGCharaObj_801DC548;

	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		Game.m_gameWork.m_menuStageMode != 0 &&
		Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
		(static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) != 0) {
		return 0;
	}

	int itemOffset = itemId * 0x48;
	unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + itemOffset;
	unsigned int baseCast = *reinterpret_cast<unsigned short*>(itemData + 0x2E);
	float castScale;

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x4E) != 0) {
		castScale = CharaObjGetStatusMultiplier(0x0);
	} else if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x4C) != 0) {
		castScale = CharaObjGetStatusMultiplier(0x2);
	} else {
		castScale = kOneF32;
	}

	int itemNo = *reinterpret_cast<short*>(itemData + 0x0);
	int itemType = *reinterpret_cast<unsigned short*>(itemData + 0xE);
	int result;

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
		unsigned int castReduction = playerCid != 0 ? static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBD8)) : 0;
		int totalCast = static_cast<int>(baseCast + castBonus) - static_cast<int>(castReduction);
		int cast = static_cast<int>(castScale * static_cast<float>(totalCast));
		result = cast & ~(cast >> 31);
		System.Printf(fmt + 0x74, baseCast, castBonus, castScale);
	} else if (itemType == 3) {
		result = static_cast<int>(baseCast);
		System.Printf(fmt + 0x9C, baseCast);
	} else if (itemType == 4) {
		result = static_cast<int>(baseCast);
		System.Printf(fmt + 0xB0, baseCast);
	} else if (itemNo == 0x1F8) {
		unsigned int castBonus = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle[9]) + 0x196);
		unsigned int playerCid = (static_cast<unsigned int>(__cntlzw(0x6D - static_cast<int>(static_cast<unsigned short>(GetCID()) & 0x6D))) >> 5) & 0xFFU;
		unsigned int castReduction = playerCid != 0 ? static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBD9)) : 0;
		int totalCast = static_cast<int>(baseCast + castBonus) - static_cast<int>(castReduction);
		int cast = static_cast<int>(castScale * static_cast<float>(totalCast));
		result = cast & ~(cast >> 31);
		System.Printf(fmt + 0xC4, baseCast, castBonus, castScale);
	} else {
		result = static_cast<int>(baseCast);
	}

	return result;
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

		if (partyObj->m_weaponNodeFlagBits.m_prg &&
		    partyObj->m_weaponNodeFlagAll.m_bits1.m_shield) {
			unsigned char* script = reinterpret_cast<unsigned char*>(partyObj->m_scriptHandle);
			unsigned short hp = *reinterpret_cast<unsigned short*>(script + 0x1C);
			if (hp != 0 && static_cast<int>(hp) <= static_cast<int>(static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(script + 0x1A)) >> 2)) {
				if ((static_cast<int>(System.m_frameCounter) % 0x1E) == 0) {
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

		int hasNearbyPartner = 0;
		for (int j = 0; j < candidateCount; j++) {
			if (i == j) {
				continue;
			}

			CGPartyObj* other = candidates[j];
			if (other == 0 || other->m_comboState == 0) {
				continue;
			}

			if (PSVECDistance(&CharaObjComboCenter(candidates[i]), &CharaObjComboCenter(other)) < kQuadObjDebugHeight) {
				hasNearbyPartner = 1;
				break;
			}
		}

		CharaObjComboFlagBits* comboFlags = reinterpret_cast<CharaObjComboFlagBits*>(&CharaObjComboFlags(party));
		if (hasNearbyPartner && comboFlags->m_nearby == 0) {
			goto changed;
		}
		if (!hasNearbyPartner && comboFlags->m_nearby != 0) {
			goto changed;
		}
		continue;
	changed:
		comboFlags->m_nearby = static_cast<signed char>(hasNearbyPartner);
		comboFlags->m_active = 1;
		party->playSe3D((static_cast<int>(-static_cast<int>(hasNearbyPartner) | static_cast<int>(hasNearbyPartner)) >> 31) + 0x3D, 0x32, 0x96, 0, 0);
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
		if (kQuadObjDebugHeight < PSVECDistance(&CharaObjComboCenter(candidates[0]), &CharaObjComboCenter(candidates[i]))) {
			CGPartyObj** shiftCursor = &candidates[i];
			for (int remaining = (candidateCount - 1) - i; remaining != 0; remaining--) {
				shiftCursor[0] = shiftCursor[1];
				shiftCursor++;
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
	unsigned int comboIndex = searchCombi(candidateCount, candidates, fallback);
	if (comboIndex < 0) {
		if (fallback == 0 || candidates[0]->m_comboFrame >= 0x42) {
			candidates[0]->m_comboState = 0;
			candidates[0]->m_comboFrame = 0;
			candidates[0]->addSubStat();
			combi2();
		}
		return;
	}

	if (fallback != 0 && candidates[0]->m_comboFrame < 0x42) {
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

#define comboCmd (comboData[0xC])
	const int isShared1F8 = (static_cast<unsigned int>(__cntlzw(0x1F8 - comboData[participantCount * 3 - 3])) >> 5) & 0xFF;
	if (isShared1F8 == 0) {
		comboCenter.Identity();
		for (int i = 0; i < participantCount; i++) {
			CVector candidateCenter(CharaObjComboCenter(candidates[i]));
			PSVECAdd(reinterpret_cast<Vec*>(&comboCenter), reinterpret_cast<Vec*>(&candidateCenter), reinterpret_cast<Vec*>(&comboCenter));
		}
		PSVECScale(reinterpret_cast<Vec*>(&comboCenter), reinterpret_cast<Vec*>(&comboCenter), kOneF32 / static_cast<float>(participantCount));
	}

	System.Printf(const_cast<char*>(sCharaObjComboDecisionFmt), System.m_frameCounter, comboCmd);

	CGPartyObj* leadParty = candidates[participantCount - 1];
	int playedComboSe = 0;
	for (int i = 0; i < participantCount; i++) {
		CGPartyObj* party = candidates[i];
		unsigned int comboMode = 0xFFFFFFFF;

		if (isShared1F8 != 0) {
			switch (comboCmd) {
			case 0x207:
				comboMode = 0;
				break;
			case 0x20B:
				comboMode = 1;
				break;
			case 0x20F:
				comboMode = 2;
				break;
			}

			if (party == leadParty) {
				CharaObjComboItemState(party) = static_cast<int>(comboMode);
				party->playSe3D(0x3F, 0x32, 0x96, 0, 0);
			} else {
				CharaObjComboCenter(party) = leadParty->m_worldPosition;
				CharaObjComboItemId(party) = 0;
			}
		} else {
			CharaObjComboCenter(party) = comboCenter;
			if (playedComboSe == 0 &&
			    (Game.m_gameWork.m_menuStageMode == 0 || Game.m_gameWork.m_bossArtifactStageIndex >= 0xF ||
			     (static_cast<unsigned short>(party->GetCID()) & 0x6D) != 0x6D ||
			     *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party->m_scriptHandle) + 0x3B4) == 0)) {
				CharaObjComboItemId(party) = comboCmd;
				party->playSe3D(0x3F, 0x32, 0x96, 0, 0);
				playedComboSe = 1;
			} else {
				CharaObjComboItemId(party) = 0;
			}
		}

		party->m_comboState = 0;
		party->m_comboFrame = 0;
		party->addSubStat();
		party->putComboParticle();

		CharaObjComboScriptArg(party) = comboCmd;
		CharaObjComboScriptMode(party) = comboMode;
		CharaObjComboLinkCount(party) = 0;

		CGPrgObj** comboLinks = CharaObjComboLinks(party);
		for (unsigned int j = 0; j < participantCount; j++) {
			CGPartyObj* other = candidates[j];
			if (party == other) {
				continue;
			}
			comboLinks[CharaObjComboLinkCount(party)++] = other;
		}
	}
#undef comboCmd

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
	while (entry < CharaObjComboLinkCount(this)) {
		if (CharaObjComboLinks(this)[entry] != 0) {
			if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
			    (static_cast<unsigned short>(CharaObjComboLinks(this)[entry]->GetCID()) & 0x6D) == 0x6D &&
			    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(CharaObjComboLinks(this)[entry]->m_scriptHandle) + 0x3B4) != 0) {
				goto next_link;
			} else if (CharaObjComboLinks(this)[entry]->m_lastStateId != 6 && CharaObjComboLinks(this)[entry]->m_lastStateId != 2) {
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

		int reqLast = reqCount - 1;
		int slot = 0;
		unsigned short* slotCursor = combiCursor;
		CGPartyObj** slotPtr = partyList;
		for (int remaining = reqCount; remaining > 0; remaining--) {
			CGCharaObj* partyObj = reinterpret_cast<CGCharaObj*>(*slotPtr);
			if (partyObj->m_comboFrame == 0) {
				int scanSlot = remaining;
				unsigned short* fallbackCursor = slotCursor;
				if (slot < reqCount) {
					do {
						int objParticle = partyObj->m_itemId;
						int itemMatch;
						if ((slot == lastSlot &&
							*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (objParticle * 0x48)) == 0x1F8 &&
							fallbackCursor[0] == 0x1F8) ||
							objParticle == fallbackCursor[0]) {
							itemMatch = 1;
						} else {
							itemMatch = 0;
						}
						if (itemMatch) {
							int closeOk;
							if (partyList[0] == reinterpret_cast<CGPartyObj*>(partyObj) ||
								static_cast<int>(slotCursor[2]) >= reinterpret_cast<CGCharaObj*>(partyList[0])->m_comboFrame) {
								closeOk = 1;
							} else {
								closeOk = 0;
							}
							if (closeOk) {
								break;
							}
						}
						slot++;
						fallbackCursor += 3;
						scanSlot--;
					} while (scanSlot != 0);
				}
				if (slot < count) {
					outFallback = 1;
					return found;
				}
				break;
			}

			unsigned int objParticle = static_cast<unsigned int>(partyObj->m_itemId);
			int itemMatch;
			if ((slot == lastSlot &&
				*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (objParticle * 0x48)) == 0x1F8 &&
				slotCursor[0] == 0x1F8) ||
				objParticle == slotCursor[0]) {
				itemMatch = 1;
			} else {
				itemMatch = 0;
			}
			if (!itemMatch) {
				break;
			}

			int diff = reinterpret_cast<CGCharaObj*>(partyList[0])->m_comboFrame - partyObj->m_comboFrame;
			int windowOk;
			if (partyList[0] == reinterpret_cast<CGPartyObj*>(partyObj) ||
				(static_cast<int>(slotCursor[1]) <= diff && static_cast<int>(slotCursor[2]) >= diff)) {
				windowOk = 1;
			} else {
				windowOk = 0;
			}
			if (!windowOk) {
				break;
			}

			if (slot == reqLast) {
				found = combiIndex;
			}
			slot++;
			slotPtr++;
			slotCursor += 3;
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

extern "C" {
__declspec(section ".sdata2") extern const float kCharaObjZero = 0.0f;
__declspec(section ".sdata2") extern const float kCharaObjHalfPi = 1.5707964f;
__declspec(section ".sdata2") extern const float kCharaObjNegativeHalfPi = -1.5707964f;
__declspec(section ".sdata2") extern const float kCharaObjSideParticleRadius = 18.0f;
__declspec(section ".sdata2") extern const float kCharaObjForwardParticleOffset = 60.0f;
__declspec(section ".sdata2") extern const float FLOAT_8033199C = 7.0f;
__declspec(section ".sdata2") extern const float FLOAT_803319A0 = 165.0f;
__declspec(section ".sdata2") extern const float FLOAT_803319A4 = 6.2831855f;
__declspec(section ".sdata2") extern const float FLOAT_803319A8 = 2.0f;
__declspec(section ".sdata2") extern const float FLOAT_803319AC = 0.1f;
__declspec(section ".sdata2") extern const float FLOAT_803319B0 = 0.05f;
__declspec(section ".sdata2") extern const float FLOAT_803319B4 = 0.15f;
__declspec(section ".sdata2") extern const float FLOAT_803319B8[2] = { 1.2f, 0.0f };
__declspec(section ".sdata2") extern const float kMonObjDefaultScale = 1.0f;
__declspec(section ".sdata2") extern const float FLOAT_803319C4 = 3.1415927f;
}
