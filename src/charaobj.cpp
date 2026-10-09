#include "ffcc/combi.h"
#include "ffcc/ptrarray.h"
#include "ffcc/charaobj.h"
#include "ffcc/itemobj.h"
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

#ifdef VERSION_GCCP01
static const int kCounterDamageStatusFrames = 25;
static const int kLateItemParticleFrame = 16;
#else
static const int kCounterDamageStatusFrames = 30;
static const int kLateItemParticleFrame = 20;
#endif

extern char SoundBuffer[];


STATIC_ASSERT(sizeof(CCombi2Set) == 6);
STATIC_ASSERT(sizeof(CCombi2) == 0x1A);
STATIC_ASSERT(offsetof(CCombi2, m_command) == 0x18);

static Vec* l_pHitCross = 0;
static int l_idxAttackCol = 0;
extern "C" {
}

static inline float& CharaObjTargetAngle(CGCharaObj* charaObj)
{
	return charaObj->m_targetAngle;
}

static __inline float CharaObjGetRotateY(const Vec& vector)
{
	if (vector.x == 0.0f && vector.z == 0.0f) {
		return 0.0f;
	}

	return static_cast<float>(atan2(vector.x, vector.z));
}

static __inline void CharaObjEndSlots(CGCharaObj* charaObj, unsigned int slotMask)
{
	for (int i = 0; i < 0x16; i++) {
		if ((slotMask & (1U << i)) != 0) {
			CFlatRuntime2Storage().EndParticleSlot(charaObj->m_particleSlots[i], 1);
		}
	}
}

static __inline void CharaObjPutMonsterScaledParticle(CGCharaObj* charaObj, int particleNo, int slot, float scale)
{
	charaObj->putParticle(particleNo, slot, static_cast<CGObject*>(charaObj), 0.1f * charaObj->m_attackColRadius * scale, 0);
}

static __inline bool CharaObjSkipComboScript(CGPrgObj* obj)
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

static inline bool CharaObjIsPlayerCid(unsigned int cid)
{
	return (cid & 0x6D) == 0x6D;
}

static inline bool CharaObjIsElementalStatus(int staType)
{
	return staType == 4 || staType == 0x1C || staType < 3 ||
	       static_cast<unsigned int>(staType - 8) <= 2 || staType == 6 || staType == 3;
}

static inline bool CharaObjIsBreakStatus(int staType)
{
	return static_cast<unsigned int>(staType - 0x24) <= 1 || staType == 0x69 || staType == 0x6A;
}

struct CharaObjSignedLowBit
{
	signed char m_pad : 7;
	signed char m_low : 1;
};

static __inline bool CharaObjCanFrontGuard(CGCharaObj* self, CGPrgObj* sourceObj)
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

static inline unsigned int CharaObjResolveHitParticleBank(CGPrgObj* sourceObj, unsigned int particleBank)
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
static inline int CharaObjGameFlagBit5Set()
{
	return static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(CFlatGameFlags()) << 26 >> 30) << 30 >> 31) != 0;
}

static inline int CharaObjDecodeHitParticleSe(unsigned short seData)
{
	return (seData == 0xFFFF) ? 0 : (seData & 0xFF) + static_cast<int>(seData >> 8) * 1000;
}

static inline int CharaObjDecodeSe(unsigned short encodedSe)
{
	if (encodedSe == 0xFFFF) {
		return 0;
	}
	return (encodedSe & 0xFF) + ((encodedSe >> 8) * 1000);
}

static inline int CharaObjResolveParticleBank(CGCharaObj* charaObj, int particleClass)
{
	switch (particleClass) {
	case 0xFE:
		return charaObj->m_charaModelHandle->GetPdtId();
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

static __inline SCharaItemRow* CharaObjItemRow(int itemId)
{
	SCharaItemRow* row = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	row += itemId;
	return row;
}

static __inline float CharaObjGetStatusMultiplier(int offset)
{
	return (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + offset)) * 0.01f) + 1.0e-07f;
}

static __inline float CharaObjGetMonsterScale(unsigned char* script9, bool isMon)
{
	if (!isMon || script9 == 0) {
		return 1.0f;
	}
	return static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0x1B4)) * 0.01f;
}

/*
 * --INFO--
 * PAL Address: 0x80112C40
 * PAL Size: 276b
 * EN Address: 0x8012aec0
 * EN Size: 268b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onCreate()
{
	CGPrgObj::onCreate();

	static int monCounter = 0;
	m_updateCounter = monCounter++;

	m_unk63CBits.m_bit80 = 0;
	resetIgnoreHit();
	m_comboFrame = 0;
	m_comboFramePrev = 0;
	m_comboState = 0;
	m_damageParticle = -1;
	m_unk688 = 0;
	m_pushScale = 1.0f;
	m_alpha = 1.0f;
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
 * PAL Address: 0x80112B1C
 * PAL Size: 168b
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
 * PAL Address: 0x801129D0
 * PAL Size: 332b
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
 * EN Address: 0x8012b054
 * EN Size: 136b
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

	m_unk63CBits.m_bit80 = 0;
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
 * PAL Address: UNUSED
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGCharaObj::decIgnoreHit()
{
	for (int i = 0; i < 4; i++) {
		if (m_ignoreHit[i].m_flagBits.m_flag_80 && m_ignoreHit[i].m_timer != 0) {
			if (--m_ignoreHit[i].m_timer == 0) {
				m_ignoreHit[i].m_flagBits.m_flag_80 = 0;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80112618
 * PAL Size: 952b
 * EN Address: 0x8012b190
 * EN Size: 624b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::onFramePostCalc()
{
	if (m_scriptHandle->m_statusTimers[2] != 0) {
		if (m_stateTick != 0 &&
		    (m_stateTick % static_cast<int>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x3A))) == 0) {
			if (m_scriptHandle->m_hp > 1 &&
			    !CharaObjGameFlagBit5Set()) {
				playSe3D(0x19, 0x32, 0x96, 0, 0);
				addHp(-1, 0);
			}
		}
	}

	for (int i = 0; i < 0x27; i++) {
		int statusValue = static_cast<int>(m_scriptHandle->m_statusTimers[i]) - 1;
		if (statusValue != 0 && i == 2) {
			m_stateTick += 1;
		}

		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		    (i == 0 || i == 4 || i == 9 || i == 3) &&
		    statusValue > 0) {
			unsigned short padMask = Pad.GetButtonDown(m_animStateMisc);
			if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
				padMask |= Pad.GetButtonDownAnalog(m_animStateMisc);
			}
			if ((padMask & 0xF) != 0) {
				statusValue -= *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x3C);
				System.Printf("ギアガチャ\n");
			}
		}

		setSta(i, statusValue);
	}

	if (m_scriptHandle->m_statusTimers[0] != 0 ||
	    m_scriptHandle->m_statusTimers[9] != 0 ||
	    m_scriptHandle->m_statusTimers[3] != 0) {
		m_displayFlags &= ~2;
		m_unk63CBits.m_bit80 = 0;
	} else {
		m_displayFlags |= 2;
	}

	m_updateCounter++;
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
			m_partyDistance[i] = 0.0f;
			m_partyDelta[i].x = m_partyDelta[i].y = m_partyDelta[i].z = 0.0f;
			m_partyAngle[i] = 0.0f;
		}

		m_partyRank[i] = 0;
		for (int j = 0; j < i; j++) {
			if (0.0f == m_partyDistance[i]) {
				m_partyRank[i] += 1;
			} else if (0.0f == m_partyDistance[j]) {
				m_partyRank[j] += 1;
			} else if (m_partyDistance[i] < m_partyDistance[j]) {
				m_partyRank[j] += 1;
			} else {
				m_partyRank[i] += 1;
			}
		}
	}

	m_pushScale = 1.0f;
	if (m_scriptHandle->m_statusTimers[8] != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x34)) * 0.01f) + 1.0e-07f;
	}
	if (m_scriptHandle->m_statusTimers[7] != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x36)) * 0.01f) + 1.0e-07f;
	}
	if (m_scriptHandle->m_statusTimers[1] != 0) {
		m_pushScale *= (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x40)) * 0.01f) + 1.0e-07f;
	}
	m_pushScale = (m_pushScale < 1.2f) ? m_pushScale : 1.2f;

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

	CGObjWork* script = m_scriptHandle;
	if (script->m_statusTimers[0] != 0 ||
	    script->m_statusTimers[9] != 0 ||
	    script->m_statusTimers[3] != 0) {
		push += 0x19;
	}

	unsigned short cid = GetCID();
	if ((cid & 0x6D) == 0x6D) {
		if (static_cast<CGPartyObj*>(this)->m_partyData.carryObject != nullptr) {
			push += 10;
		}
		if (Pad.IsGba(m_animStateMisc) != 0) {
			push += 0x19;
		}
		if (m_weaponNodeFlagAll.m_bits1.m_shield == 0) {
			push += 0x19;
		}
	}

	m_pushParamB = static_cast<unsigned char>(push < 0x19 ? push : 0x19);
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && static_cast<CGMonObj*>(this)->m_chaseState == 4) {
		m_pushParamB = 100;
	}

	if ((AStar.m_flags & 1) != 0) {
		m_aStarGroupId = AStar.calcSpecialPolygonGroup(&m_worldPosition);
	} else {
		m_aStarGroupId = static_cast<unsigned char>(m_lastBgGroup);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801120C0
 * PAL Size: 296b
 * EN Address: 0x8012b890
 * EN Size: 336b
 * JP Address: TODO
 * JP Size: TODO
 */
float CGCharaObj::onAlphaUpdate()
{
	float alpha = m_alpha;

	if (m_scriptHandle->m_hp != 0) {
		if (((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		     m_scriptHandle->m_hp == 0) ||
		    ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		     (m_scriptHandle->m_romWork[0x7F] & 1) != 0 &&
		     static_cast<CGMonObj*>(this)->m_unk6BA == 0)) {
			int createSerial = m_updateCounter;
			float alphaWave = static_cast<float>(sin(static_cast<double>(0.05f * static_cast<float>(createSerial))));
			float alphaDelta = 0.15f * alphaWave;
			alpha = alpha + alphaDelta;
		}
	}

	float slope = m_alphaTarget;
	float clamped;
	if (alpha < 0.0f) {
		clamped = 0.0f;
	} else if (1.0f < alpha) {
		clamped = 1.0f;
	} else {
		clamped = alpha;
	}
	return slope * clamped;
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
 * PAL Address: 0x8011191C
 * PAL Size: 4b
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
						putParticleFromItem(m_itemId, 2, m_particleSlots[1], &m_comboCenter);
						putParticleFromItem(m_itemId, 3, m_particleSlots[1], &m_comboCenter);
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
					reqAnim(6, 1, 0);

					if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
						playSe3D(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) + 0x10,
						         0x32, 0x96, 0, 0);
					}
				}
				break;
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

				if (m_scriptHandle->m_statusTimers[4] == 0) {
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
					bool isMonster = (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD;
					reqAnim(isMonster ? m_unk558 : m_unk55C, 0, 0);
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
 * PAL Address: N/A (not in Ghidra export)
 * PAL Size: N/A
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
 * EN Address: 0x8012bb84
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::resetIgnoreHit()
{
	m_ignoreHit[0].m_flagBits.m_flag_80 = 0;
	m_ignoreHit[1].m_flagBits.m_flag_80 = 0;
	m_ignoreHit[2].m_flagBits.m_flag_80 = 0;
	m_ignoreHit[3].m_flagBits.m_flag_80 = 0;
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
 * PAL Address: 0x80111500
 * PAL Size: 8b
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

	int i;
	for (i = 0; i < 4; i++) {
		if (m_ignoreHit[i].m_flagBits.m_flag_80 != 0) {
			if (m_ignoreHit[i].m_source == sourceObj) {
				return 2;
			}
		} else {
			m_ignoreHit[i].m_flagBits.m_flag_80 = 1;
			m_ignoreHit[i].m_source = sourceObj;

			unsigned int particleIndex = static_cast<unsigned int>(m_itemId);
			SCharaItemRow* lifeRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			unsigned short particleLife = lifeRows[particleIndex].m_actionType;
			m_ignoreHit[i].m_timer = (particleLife == 3) ? 0x1E : 0;
			break;
		}
	}
	if (i == 4) {
		return 2;
	}
	if ((sourceObj->m_objectFlags & 0x100) != 0) {
		bonus(3, 0, (CGPrgObj*)0);
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
	SCharaItemRow* items = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	if ((items[particleIndex].m_particleFlags & 0x100) != 0) {
		PartMng.pppEndPart(effectIndex);
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
	int particleSpec;
	unsigned short particleFlags;
	unsigned short seSpec;

	if (itemId == 0x1FA || itemId == 0x237) {
		particleOffset = l_idxAttackCol;
	}

	SCharaItemRow* items = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	int particleBank = items[itemId].m_particleBank;
	if (particleBank != 0xFFFF && particleBank != 0xFF) {
		if (particleBank == 0xFE) {
			particleBank = sourceObj->m_charaModelHandle->GetPdtId();
		}
		if (particleBank == 0xFD) {
			particleBank = 0xFFFFFFFF;
		}
		particleSpec = items[itemId].m_particleSpec;
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
				CFlatRuntime2Storage().SetParticleWorkPos(*l_pHitCross, 0.0f);
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
	int isIceJ = 0;
	int isMon = 0;
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
		isMon = 1;
		if (m_scriptHandle->m_romWork[0x7E] == 0xB) {
			isIceJ = 1;
		}
	}

	clampedValue = value < 0 ? 0 : value;
	CGObjWork* work = SAFE_CAST_WORK(m_scriptHandle);
	int current = work->m_statusTimers[staIndex];

	if (current != 0 && clampedValue == 0) {
		switch (staIndex) {
			case 0x1B:
				endPSlotBit(0x400);
				break;
			case 1:
				endPSlotBit(0x40);
				break;
			case 0:
				endPSlotBit(0x4);
				if (isIceJ) {
					int modelPdtNo = m_charaModelHandle->GetPdtId();
					putParticle((modelPdtNo << 8) | 0x16, 0, this, 1.0f, 0);
				} else {
					putParticle(0x10B, 0, this, 0.1f * m_attackColRadius, 0);
				}
				playSe3D(0x16, 0x32, 0x96, 0, 0);
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
					reinterpret_cast<CGMonObj*>(this)->setIceJEffect(1);
				}
				break;
			case 4:
				endPSlotBit(0x80);
				break;
			case 10:
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (m_scriptHandle->m_romWork[0x7F] & 4) != 0 &&
					m_scriptHandle->m_hp != 0) {
					reinterpret_cast<CGMonObj*>(this)->flyUp();
				}
				break;
			case 0x1C:
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (m_scriptHandle->m_romWork[0x7F] & 1) != 0) {
					reinterpret_cast<CGMonObj*>(this)->undeadOn();
				}
				break;
			case 9: {
				endPSlotBit(0x4000);
				float monsterScale;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					monsterScale = static_cast<float>(m_scriptHandle->m_romWork[0xDA]) * 0.01f;
				} else {
					monsterScale = 1.0f;
				}
				int particleNo = isMon ? 0x6D : 0x11;
				float scaledRadius = 0.1f * m_attackColRadius;
				putParticle(particleNo | 0x100, 0, this, scaledRadius * monsterScale, 0);
				break;
			}
			case 8: {
				endPSlotBit(0x2000);
				float monsterScale;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					monsterScale = static_cast<float>(m_scriptHandle->m_romWork[0xDA]) * 0.01f;
				} else {
					monsterScale = 1.0f;
				}
				int particleNo = isMon ? 0x6F : 0x13;
				float scaledRadius = 0.1f * m_attackColRadius;
				putParticle(particleNo | 0x100, 0, this, scaledRadius * monsterScale, 0);
				break;
			}
			case 7: {
				endPSlotBit(0x8000);
				int particleNo = isMon ? 0x71 : 0x15;
				putParticle(particleNo | 0x100, 0, this, 0.1f * m_attackColRadius, 0);
				break;
			}
			case 3:
				endPSlotBit(0x40000);
				putParticle(0x10E, 0, this, 0.1f * m_attackColRadius, 0);
				playSe3D(0x3A, 0x32, 0x96, 0, 0);
				break;
			case 2:
				endPSlotBit(0x80000);
				break;
			case 6:
				endPSlotBit(0x100000);
				break;
				break;
			default:
				break;
		}
	} else if (current == 0 && clampedValue != 0) {
		switch (staIndex) {
			case 0x1B:
				endPSlotBit(0x400);
				putParticle(0x11C, m_particleSlots[10], this, 1.0f, 0x1290D);
				break;
			case 1:
				endPSlotBit(0x40);
				if (isIceJ) {
					int modelPdtNo = m_charaModelHandle->GetPdtId();
					putParticle((modelPdtNo << 8) | 0x14, m_particleSlots[6], this, 1.0f, 0);
				} else {
					putParticle(0x12A, m_particleSlots[6], this, 0.1f * m_attackColRadius, 0);
				}
				break;
			case 0:
				endPSlotBit(0x4);
				if (isIceJ) {
					int modelPdtNo = m_charaModelHandle->GetPdtId();
					putParticleBindTrace((modelPdtNo << 8) | 0x15, m_particleSlots[2], this, 1.0f, 0);
				} else {
					putParticle(0x10A, m_particleSlots[2], this, 0.1f * m_attackColRadius, 0);
				}
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
					reinterpret_cast<CGMonObj*>(this)->setIceJEffect(0);
				}
				break;
			case 4:
				endPSlotBit(0x80);
				if (isIceJ) {
					int modelPdtNo = m_charaModelHandle->GetPdtId();
					putParticle((modelPdtNo << 8) | 0x17, m_particleSlots[7], this, 1.0f, 0);
				} else {
					putParticle(0x130, m_particleSlots[7], this, 0.1f * m_attackColRadius, 0);
				}
				break;
			case 10:
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (m_scriptHandle->m_romWork[0x7F] & 4) != 0) {
					reinterpret_cast<CGMonObj*>(this)->flyDown();
				}
				break;
			case 0x1C:
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && (m_scriptHandle->m_romWork[0x7F] & 1) != 0) {
					reinterpret_cast<CGMonObj*>(this)->undeadOff();
				}
				break;
			case 9: {
				endPSlotBit(0x4000);
				float monsterScale;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					monsterScale = static_cast<float>(m_scriptHandle->m_romWork[0xDA]) * 0.01f;
				} else {
					monsterScale = 1.0f;
				}
				int particleNo = isMon ? 0x6C : 0x10;
				float scaledRadius = 0.1f * m_attackColRadius;
				putParticle(particleNo | 0x100, m_particleSlots[14], this, scaledRadius * monsterScale, 0);
				break;
			}
			case 8: {
				endPSlotBit(0x2000);
				float monsterScale;
				if ((((static_cast<unsigned int>(__cntlzw(0xAD - (static_cast<unsigned short>(GetCID()) & 0xAD))) >> 5) & 0xFFU) != 0)) {
					monsterScale = static_cast<float>(m_scriptHandle->m_romWork[0xDA]) * 0.01f;
				} else {
					monsterScale = 1.0f;
				}
				int particleNo = isMon ? 0x6E : 0x12;
				float scaledRadius = 0.1f * m_attackColRadius;
				putParticle(particleNo | 0x100, m_particleSlots[13], this, scaledRadius * monsterScale, 0);
				break;
			}
			case 7: {
				endPSlotBit(0x8000);
				int particleNo = isMon ? 0x70 : 0x14;
				putParticle(particleNo | 0x100, m_particleSlots[15], this, 0.1f * m_attackColRadius, 0);
				break;
			}
			case 3:
				endPSlotBit(0x40000);
				putParticleBindTrace(0x10D, m_particleSlots[18], this, 0.1f * m_attackColRadius, 0);
				break;
			case 2:
				m_stateTick = 0;
				endPSlotBit(0x80000);
				putParticleBindTrace(0x10C, m_particleSlots[19], this, 0.1f * m_attackColRadius, 0);
				break;
			case 6:
				endPSlotBit(0x100000);
				putParticleBindTrace(0x107, m_particleSlots[20], this, 0.1f * m_attackColRadius, 0);
				break;
			case 0x65:
			case 0x66:
			default:
				break;
		}
	}

	work = SAFE_CAST_WORK(m_scriptHandle);
	work->m_statusTimers[staIndex] = static_cast<unsigned short>(clampedValue);
}

/*
 * --INFO--
 * PAL Address: 0x8010FD54
 * PAL Size: 2172b
 * EN Address: 0x8010F0B4
 * EN Size: 2172b
 * JP Address: 0x8010BD40
 * JP Size: 2172b
 */
void CGCharaObj::effective(int staIndex, int amount, CGPrgObj* sourceObj, int& outValue)
{
	int i;

	switch (staIndex) {
		case 0x24:
			if (m_scriptHandle->m_statusTimers[0] != 0) {
				setSta(0, 0);
			}
			break;
		case 0x64:
			if (m_scriptHandle->m_statusTimers[0] != 0) {
				setSta(0, 0);
			}
			break;
		case 0x25:
			if (m_scriptHandle->m_statusTimers[0] != 0) {
				setSta(0, 0);
			}
			if ((static_cast<unsigned short>(GetCID()) & 0xAD) != 0xAD ||
				(m_scriptHandle->m_romWork[0x7F] & 8) == 0) {
				CVector delta = CVector(m_worldPosition) - CVector(sourceObj->m_worldPosition);
				moveVectorH(delta, 2.0f, 8);
				m_rotTargetY = static_cast<float>(atan2(-static_cast<double>(delta.x), -static_cast<double>(delta.z)));
				changeStat(0x19, 0, 0);
			}
			break;
		case 0x69:
			if (m_scriptHandle->m_statusTimers[0] != 0) {
				setSta(0, 0);
			}
			changeStat(4, 0, 0);
			break;
		case 0x6B:
			if (m_scriptHandle->m_statusTimers[4] != 0) {
				setSta(4, 0);
			}
			if (m_scriptHandle->m_statusTimers[0] == 0 &&
				m_scriptHandle->m_statusTimers[9] == 0 &&
				m_scriptHandle->m_statusTimers[3] == 0) {
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
			if (m_scriptHandle->m_statusTimers[0] != 0) {
				setSta(0, 0);
				setSta(1, 0);
				outValue = 0;
			} else {
				setSta(1, calcSta(1, amount, reinterpret_cast<CGObject*>(sourceObj)));
				setSta(4, 0);
			}
			break;
		case 0:
			if (m_scriptHandle->m_statusTimers[1] != 0) {
				setSta(0, 0);
				setSta(1, 0);
				outValue = 0;
			} else {
				setSta(0, calcSta(0, amount, reinterpret_cast<CGObject*>(sourceObj)));
				setSta(4, 0);
				Sound.StopSe3DGroup(m_particleId);
				{
					i = 0;
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
			addHp(m_scriptHandle->m_maxHp, 0);
			sourceObj->bonus(0x16, amount, this);
			outValue = 0;
			putHitParticleFromItem(sourceObj, amount);
			break;
		case 0x67:
			for (i = 0; i < 0x27; i++) {
				setSta(i, 0);
			}
			m_displayFlags |= 2;
			putHitParticleFromItem(sourceObj, amount);
			break;
		case 0x65:
			if (Game.m_gameWork.m_gameOverFlag == 0) {
				if (amount == 0x225) {
					addHp(m_scriptHandle->m_maxHp, 0);
				} else {
					addHp(8, 0);
				}
				changeStat(0x22, 0, 0);
				putHitParticleFromItem(sourceObj, amount);
			} else {
				System.Printf("ゲームオーバーなのでレイズ系の回復処理を無視します。\n");
			}
			outValue = 0;
			break;
		case 0x1C:
			setSta(0x1C, calcSta(0x1C, amount, reinterpret_cast<CGObject*>(sourceObj)));
			break;
		case 8:
			if (m_scriptHandle->m_statusTimers[7] != 0) {
				setSta(7, 0);
				setSta(8, 0);
			} else {
				setSta(8, calcSta(8, amount, reinterpret_cast<CGObject*>(sourceObj)));
				putHitParticleFromItem(sourceObj, amount);
			}
			outValue = 0;
			break;
		case 7:
			if (m_scriptHandle->m_statusTimers[8] != 0) {
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
				i = 0;
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
				i = 0;
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

static inline bool CharaObjIsMultiStage()
{
	return Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF;
}

static inline bool CharaObjIsMultiCaravan(CGObject* obj)
{
	return CharaObjIsMultiStage() && obj->IsKindOf(0x6D);
}

static inline bool CharaObjIsJoybusCaravan(CGObject* obj)
{
	return CharaObjIsMultiCaravan(obj) && reinterpret_cast<CCaravanWork*>(static_cast<CGPrgObj*>(obj)->m_scriptHandle)->m_joybusCaravanId != 0;
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
static inline unsigned short CharaObjGetPower(CGObject* source, int amount)
{
	bool isPrgObj = source->IsKindOf(0x2D);
	if (isPrgObj) {
		CGPrgObj* powerSource;
		if (CharaObjIsJoybusCaravan(source)) {
			powerSource = Game.m_partyObjArr[0];
		} else {
			powerSource = static_cast<CGPrgObj*>(source);
		}
		return powerSource->m_scriptHandle->m_romWork[0xCC];
	}
	SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	return powerRows[amount].m_power;
}

int CGCharaObj::calcSta(int staIndex, int amount, CGObject* source)
{
	if (staIndex == 0 || staIndex == 4) {
		CGObjWork* work = m_scriptHandle;
		if (work->m_statusTimers[staIndex] != 0) {
			System.Printf("効果時間上書きなし\n");
			CGObjWork* work2 = m_scriptHandle;
			return work2->m_statusTimers[staIndex];
		}
	}

	unsigned int base = 0;
	int itemType;
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

	if (amount >= 0x1F5) {
		SCharaItemRow* kindRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		itemType = kindRows[amount].m_kind;
	} else {
		itemType = 1;
	}

	unsigned int power = CharaObjGetPower(source, amount);
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
	if (source->IsKindOf(0x6D) && (itemType == 1 || itemType == 9)) {
		affinity = static_cast<unsigned char>(reinterpret_cast<CCaravanWork*>(static_cast<CGPrgObj*>(source)->m_scriptHandle)->m_equipEffectParams[2]);
	}

	int selfCid = static_cast<unsigned short>(GetCID());
	if ((selfCid & 0x6D) == 0x6D && (itemType == 8 || itemType == 9)) {
		affinity -= static_cast<unsigned char>(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_equipEffectParams[3]);
	}

	unsigned int total = affinity + (base * power);
	unsigned int next = static_cast<int>(total) < 0 ? 0 : total;
	System.Printf("効果時間 %d * %d + %d = %d\n", base, power, affinity, next);
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
	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && (DbgMenuPcs.GetDbgFlag() & 4) != 0) {
		return;
	}

	int hpValue = m_scriptHandle->m_hp;
	int next = hpValue;

	if (hpValue != 0 && delta < 0) {
		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		    reinterpret_cast<CharaObjSignedLowBit*>(&CFlatGameFlags())->m_low != 0 &&
		    static_cast<int>(hpValue + delta) <= 0) {
			delta = -(static_cast<int>(hpValue) - 1);
		}

		if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
			if (m_scriptHandle->m_baseDataIndex == 0x9A &&
			    static_cast<CGMonObj*>(this)->m_actionBranch == 0) {
				*reinterpret_cast<int*>(CGMonObj::m_boss + 0x24) -= delta;
				delta = 0;
			}
			if (m_scriptHandle->m_baseDataIndex == 0x88) {
				*reinterpret_cast<int*>(CGMonObj::m_boss + 0x88) -= delta;
			}
			if (m_scriptHandle->m_baseDataIndex == 0x70 &&
			    static_cast<int>(hpValue + delta) <= 0) {
				delta = -(static_cast<int>(hpValue) - 1);
			}
		}

		next = hpValue + delta < 0 ? 0 : hpValue + delta;
		m_scriptHandle->m_hp = static_cast<unsigned short>(next);
		m_worldParam = 1.0f;

		if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
			CGPartyObj* party = static_cast<CGPartyObj*>(this);
			if (party->m_partyData.flags.commandActive) {
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
			for (int i = 2; i < reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_numCmdListSlots; i++) {
				if (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCmdListItem(i) == 0x125) {
					reinterpret_cast<CCaravanWork*>(m_scriptHandle)->DelCmdListAndItem(i, 1);
					party->m_partyData.flags.flag04 = 1;
					return;
				}
			}
		}
		return;
	}

	if (delta > 0) {
		int maxHp = m_scriptHandle->m_maxHp;
		int result = maxHp;
		if (hpValue + delta < maxHp) {
			result = hpValue + delta;
		}
		m_scriptHandle->m_hp = static_cast<unsigned short>(result);
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
	SCharaItemRow* itemRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	int normFlag = 0;
	if ((itemRows[itemId].m_flags32 & 1) != 0 || forceNormal != 0) {
		normFlag = 1;
	}
	int isNormal = normFlag & 0xFF;

	outA = 3;
	switch (staIndex) {
		case 0x24:
		case 0x25:
		case 0x69:
		case 0x6A:
		case 0x6B:
		case 100:
			outA = m_scriptHandle->m_elementResistances[0];
			break;
		case 1: outA = m_scriptHandle->m_elementResistances[1]; break;
		case 0: outA = m_scriptHandle->m_elementResistances[2]; break;
		case 4: outA = m_scriptHandle->m_elementResistances[3]; break;
		case 8: outA = m_scriptHandle->m_elementResistances[4]; break;
		case 9: outA = m_scriptHandle->m_elementResistances[5]; break;
		case 10: outA = m_scriptHandle->m_elementResistances[6]; break;
		case 0x1C: outA = m_scriptHandle->m_elementResistances[7]; break;
		case 2: outA = m_scriptHandle->m_elementResistances[8]; break;
		case 6: outA = m_scriptHandle->m_elementResistances[9]; break;
		case 3: outA = m_scriptHandle->m_elementResistances[10]; break;
		default:
			break;
	}

	if (m_scriptHandle->m_statusTimers[28] == 0 && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		(m_scriptHandle->m_romWork[0x7F] & 1) != 0 &&
		staIndex != 0x1C) {
		outA = outA < 2 ? 2 : outA;
	}
	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		(m_scriptHandle->m_romWork[0x7F] & 4) != 0 &&
		m_scriptHandle->m_statusTimers[10] == 0) {
		outA = outA < 2 ? 2 : outA;
	}

	if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && m_scriptHandle->m_baseDataIndex == 0x7F &&
	    static_cast<signed char>(static_cast<int>(static_cast<unsigned int>(CGMonObj::m_boss[0x10]) << 24 >> 30) << 30 >> 31) != 0) {
		outA = 3;
	}

	if (m_scriptHandle->m_statusTimers[27] != 0) {
		outA = 3;
	}

	System.Printf("耐性=%d\n", outA);

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
	outC = outA < 3;
}

/*
 * --INFO--
 * PAL Address: 0x8010D700
 * PAL Size: 6984b
 * EN Address: 0x8010CA60
 * EN Size: 6984b
 * JP Address: 0x80109740
 * JP Size: 6900b
 */
void CGCharaObj::onDamage(CGPrgObj* sourceObj, int itemId, int attackColIndex, int, Vec* hitPos)
{
	l_pHitCross = hitPos;
	l_idxAttackCol = attackColIndex;

	int damageAmount;
	int staType;
	int counterType;
	int counterItem;
	int counterSe;
	int resistType;
	int allowEffect;
	int effectResult;

	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && m_scriptHandle->m_statusTimers[5] != 0) {
		System.Printf("生き返り後の無敵期間でダメージOFF中\n");
		return;
	}
	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && (DbgMenuPcs.GetDbgFlag() & 4) != 0) {
		System.Printf("デバッグ無敵でダメージOFF中\n");
		return;
	}
	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && m_motionMode != 1) {
		System.Printf("motionModeがeventなのでダメージ無視\n");
		return;
	}
	if (m_weaponNodeFlagBits.m_prg == 0) {
		System.Printf("prgがoffなのでダメージ無視\n");
		return;
	}

	SCharaItemRow* itemRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	staType = itemRows[itemId].m_staType;
	if (staType != 0x67 && staType != 0x65 && staType != 0x66 && CharaObjGameFlagBit5Set()) {
		System.Printf("スクリプトから攻撃ダメージOFF中\n");
		return;
	}

	int particleLife = itemRows[itemId].m_actionType;
	int itemEffect = itemRows[itemId].m_effect;
	int scriptDefense = m_scriptHandle->m_statusTimers[0];
	int damageClamp;
	calcRegist(staType, itemId, resistType, allowEffect, effectResult, 0);

	if (resistType == 3) {
		if (staType == 4 || staType == 0x1C || static_cast<unsigned int>(staType) <= 2 ||
		    static_cast<unsigned int>(staType - 8) <= 2 || staType == 6 || staType == 3) {
			putParticle(0x201, 0, hitPos, 2.0f * (0.1f * m_attackColRadius), 0x65);
		} else if (static_cast<unsigned int>(staType - 0x24) <= 1 || staType == 0x69 || staType == 0x6A) {
			putParticle(0x200, 0, hitPos, 2.0f * (0.1f * m_attackColRadius), 0x1D);
		}
	} else if ((resistType > 1 || (resistType == 1 &&
	           ((CharaObjItemRow(itemId)->m_flags32 & 1) == 0))) &&
	           (static_cast<unsigned int>(staType - 8) <= 1 || staType == 6 || staType == 3)) {
		putParticle(0x201, 0, hitPos, 2.0f * (0.1f * m_attackColRadius), 0x65);
	}

	damageClamp = 0;
	if (m_lastStateId == 8 && m_subState == 1 &&
	    ((CharaObjItemRow(itemId)->m_flags2C & 8) == 0)) {
		CVector frontDelta = CVector(sourceObj->m_worldPosition) - CVector(m_worldPosition);
		float frontMag = PSVECMag(frontDelta);
		if (frontMag > 0.0f) {
			frontDelta = frontDelta * (1.0f / frontMag);
			CVector facing;
			facing.x = sinf(m_rotBaseY);
			facing.y = 0.0f;
			facing.z = cosf(m_rotBaseY);
			if (PSVECDotProduct(frontDelta, reinterpret_cast<Vec*>(&facing)) > 0.0f) {
				playSe3D(0x1D, 0x32, 0x96, 0, 0);
				putParticle(0x200, 0, hitPos, 0.1f * m_attackColRadius, 0);
				if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D) {
					sourceObj->changeStat(0x13, 0, 0);
				}
				if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) {
					changeSubStat(2);
					if (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId == 0) {
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
	    m_weaponNodeFlagAll.m_bits1.m_bit20 != 0) {
		SCharaItemRow* kindRows1556 = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		int currentKind = kindRows1556[m_itemId].m_status & 0xFF;
		if (currentKind == 2) {
#ifndef VERSION_GCCJGC
			if (staType != 0x66 && staType != 0x67 && staType != 7)
#endif
			{
				CVector delta = CVector(m_worldPosition) - CVector(sourceObj->m_worldPosition);
				moveVectorH(delta, 2.0f, 10);
				m_rotTargetY = static_cast<float>(atan2(-static_cast<double>(delta.x), -static_cast<double>(delta.z)));
				changeStat(0x1A, 0, 0);
			}
		} else if (currentKind == 3) {
			effectResult = 0;
			allowEffect = 0;
		}
	}

	if (itemEffect == 0x1F8 &&
	    sourceObj->m_weaponNodeFlagAll.m_bits1.m_bit20 != 0 &&
	    ((CharaObjItemRow(m_itemId)->m_status & 0xFF) == 3)) {
		CVector delta = CVector(m_worldPosition) - CVector(sourceObj->m_worldPosition);
		moveVectorH(delta, 2.0f, 10);
		m_rotTargetY = static_cast<float>(atan2(-static_cast<double>(delta.x), -static_cast<double>(delta.z)));
		changeStat(0x19, 0, 0);
	}

	if (m_scriptHandle->m_statusTimers[27] != 0) {
		allowEffect = 0;
		effectResult = 0;
	}
	if (m_scriptHandle->m_statusTimers[3] != 0) {
		allowEffect = 0;
	}
	if (m_scriptHandle->m_statusTimers[9] != 0 && (staType == 8 || staType == 7)) {
		allowEffect = 0;
		effectResult = 0;
	}
	if (m_scriptHandle->m_hp == 0) {
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
		effective(static_cast<int>(staType), itemId, sourceObj, effectResult);
	}

	damageAmount = 0;
	if (effectResult != 0) {
		int itemKind;
		if (itemId >= 0x1F5) {
			SCharaItemRow* kindRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			itemKind = kindRows[itemId].m_kind;
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
				unsigned int basePower;
				if (itemEffect == 0x1F8) {
					basePower = CharaObjItemRow(itemId)->m_basePower;
				} else {
					basePower = 0;
				}
				if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && itemId == 0x206) {
					int castCurrent = static_cast<CGCharaObj*>(sourceObj)->m_unk68C;
					int castEnd = static_cast<CGCharaObj*>(sourceObj)->m_comboFramePrev;
					if (castCurrent * 3 <= castEnd) {
						basePower <<= 2;
					} else if (castCurrent * 2 <= castEnd) {
						basePower <<= 1;
					}
				}

				unsigned int sourcePower = sourceObj->m_scriptHandle->m_strength;
				int clampedDamage = 1;
				float multiplier = CharaObjGetStatusMultiplier(0x2C);
				unsigned int defense = m_scriptHandle->m_defense;
				int rawDamage = static_cast<int>(multiplier * static_cast<float>(static_cast<int>(basePower + sourcePower))) - defense;
				if (rawDamage >= 1) {
					clampedDamage = rawDamage;
				}
				unsigned char hasBonus = 0;
				if (sourceObj->IsKindOf(0x6D) != 0 && itemEffect == 0x1F8) {
					hasBonus = 1;
				}
				unsigned int bonus = hasBonus ? static_cast<int>(static_cast<unsigned char>(reinterpret_cast<CCaravanWork*>(sourceObj->m_scriptHandle)->m_equipEffectParams[5])) : 0;
				damageAmount = clampedDamage + bonus;
				if (scriptDefense != 0) {
					damageAmount = static_cast<int>(static_cast<float>(damageAmount) * CharaObjGetStatusMultiplier(0x42));
				}
				System.Printf("PC->MON ATTACKダメージ min1((%d + %d) * %f - %d) + %d = %d\n", basePower, sourcePower, multiplier, defense, bonus, damageAmount);

				if (staType != 0x6A && (static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
				    (m_scriptHandle->m_romWork[0x7F] & 0x100) != 0 &&
				    (Game.m_gameWork.m_chaliceElement & 4U) == 0 &&
				    sourceObj->m_scriptHandle->m_elementResistances[3] == 0) {
					unsigned int srcEntryKind =
						CharaObjItemRow(static_cast<CGCharaObj*>(sourceObj)->m_itemId)->m_status & 0xFF;
					if (sourceObj->m_lastStateId == 6 && srcEntryKind <= 1) {
						break;
					}
					reinterpret_cast<CGCharaObj*>(sourceObj)->setSta(4, kCounterDamageStatusFrames);
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
				unsigned int basePower = powerRows[itemId].m_basePower;
				CGPrgObj* powerSource;
				if (CharaObjIsJoybusCaravan(sourceObj)) {
					powerSource = Game.m_partyObjArr[0];
				} else {
					powerSource = sourceObj;
				}

				unsigned int sourcePower = powerSource->m_scriptHandle->m_magic;
				int clampedDamage = 1;
				float multiplier = CharaObjGetStatusMultiplier(0x2E);
				unsigned int defense = m_scriptHandle->m_defense;
				int rawDamage = static_cast<int>(multiplier * static_cast<float>(static_cast<int>(basePower + sourcePower))) - defense;
				if (rawDamage >= 1) {
					clampedDamage = rawDamage;
				}
				unsigned int bonus = sourceObj->IsKindOf(0x6D) ?
					static_cast<unsigned int>(static_cast<unsigned char>(reinterpret_cast<CCaravanWork*>(sourceObj->m_scriptHandle)->m_equipEffectParams[6])) : 0;
				damageAmount = clampedDamage + bonus;
				System.Printf("PC->MON MAGICダメージ min1((%d + %d) * %f - %d) + %d = %d\n", basePower, sourcePower, multiplier, defense, bonus, damageAmount);
				break;
			}
			case 10: {
				if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD && static_cast<CGMonObj*>(this)->m_unk6C2 != 0) {
					damageAmount = 1;
				} else {
					float recoilRate = (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x26 + resistType * 2)) * 0.01f) + 1.0e-07f;
					int raw = static_cast<int>(static_cast<float>(static_cast<unsigned int>(m_scriptHandle->m_hp)) * recoilRate);
					damageAmount = 1;
					if (raw >= 1) {
						damageAmount = raw;
					}
					if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
						static_cast<CGMonObj*>(this)->m_unk6C2 = 1;
					}
				}
				System.Printf("PC->MON GRAダメージ %d\n", damageAmount);
				int nextSta = calcSta(10, itemId, sourceObj);
				setSta(10, nextSta);
				break;
			}
			default:
				System.Printf("STA_%d 未対応\n", staType);
				break;
			}
		} else if (itemKind == 8 || (itemKind == 9 && (static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D && (static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD) == 0xAD)) {
			switch (staType) {
			case 0x24:
			case 0x25:
			case 100:
			case 0x69:
			case 0x6A: {
				int defense = m_scriptHandle->m_defense;
				SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				unsigned int basePower = powerRows[itemId].m_basePower;
				unsigned int sourcePower = sourceObj->m_scriptHandle->m_strength;
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
				System.Printf("MON->PC ATTACKダメージ (%d + %d) - %d * %f = %d\n", basePower, sourcePower, defense, multiplier, damageAmount);
				break;
			}
			case 0:
			case 1:
			case 2:
			case 4:
			case 0x1C: {
				int defense = m_scriptHandle->m_defense;
				SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				unsigned int basePower = powerRows[itemId].m_basePower;
				unsigned int sourcePower = sourceObj->m_scriptHandle->m_magic;
				float multiplier = CharaObjGetStatusMultiplier(0x32);
				int guardValue = static_cast<int>(defense * multiplier);
				int computed32 = static_cast<int>(basePower + sourcePower) - guardValue;
				damageAmount = 1;
				if (computed32 >= 1) {
					damageAmount = computed32;
				}
				System.Printf("MON->PC MAGICダメージ (%d + %d) - %d * %f = %d\n", basePower, sourcePower, defense, multiplier, damageAmount);
				break;
			}
			case 10: {
				float recoilRate = (static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x26 + resistType * 2)) * 0.01f) + 1.0e-07f;
				int raw = static_cast<int>(static_cast<float>(static_cast<unsigned int>(sourceObj->m_scriptHandle->m_hp)) * recoilRate);
				damageAmount = (raw < 1) ? 1 : raw;
				System.Printf("MON->PC GRAダメージ %d\n", damageAmount);
				break;
			}
			default:
				System.Printf("STA_%d 未対応\n", staType);
				break;
			}
		} else if (itemKind == 9 && (static_cast<unsigned short>(GetCID()) & 0x2D) == 0x2D &&
		           ((static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD) == 0xAD || (static_cast<unsigned short>(sourceObj->GetCID()) & 0x1D) == 0x1D)) {
			switch (staType) {
			case 0:
			case 1:
			case 4: {
				SCharaItemRow* powerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				unsigned int basePower = powerRows[itemId].m_basePower;
				unsigned short rawSourcePower;
				if (sourceObj->IsKindOf(0xAD) != 0) {
					rawSourcePower = sourceObj->m_scriptHandle->m_magic;
				} else {
					SCharaItemRow* srcPowerRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
					rawSourcePower = srcPowerRows[itemId].m_sourcePower;
				}
				unsigned int sourcePower = rawSourcePower;
				unsigned int defense = m_scriptHandle->m_defense;
				float defenseRate;
				if (sourceObj->IsKindOf(0xAD) != 0) {
					defenseRate = CharaObjGetStatusMultiplier(0x32);
				} else {
					defenseRate = 1.0f;
				}
				int guardValue = static_cast<int>(static_cast<float>(static_cast<int>(defense)) * defenseRate);
				int computedGuard = static_cast<int>(basePower + sourcePower) - guardValue;
				damageAmount = 1;
				if (computedGuard >= 1) {
					damageAmount = computedGuard;
				}
				System.Printf("MON/ITEM->MON/PARTY MAGICダメージ (%d + %d) - %d * %f = %d\n", basePower, sourcePower, defense, defenseRate, damageAmount);
				break;
			}
			case 0x25:
				damageAmount = 10;
				if (itemId == 0x4AA) {
					damageAmount = 1;
				}
				break;
			default:
				System.Printf("STA_%d 未対応\n", staType);
				break;
			}
		}

#ifdef VERSION_GCCJGC
		if (staType != 4 && m_scriptHandle->m_statusTimers[4] != 0) {
#else
		if (staType != 4 &&
		    !((static_cast<unsigned short>(sourceObj->GetCID()) & 0xAD) == 0xAD && sourceObj->m_scriptHandle->m_baseDataIndex == 6 && staType == 0x6A) &&
		    m_scriptHandle->m_statusTimers[4] != 0) {
#endif
			setSta(4, 0);
		}
		if (m_scriptHandle->m_statusTimers[0] != 0 && staType != 2 && staType != 0) {
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
		    (m_scriptHandle->m_romWork[0x7F] & 4) != 0 &&
		    m_scriptHandle->m_statusTimers[10] == 0) {
			damageAmount = (damageAmount >= 1) ? 1 : damageAmount;
		}
		if (m_scriptHandle->m_statusTimers[28] == 0 && (static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD &&
		    (m_scriptHandle->m_romWork[0x7F] & 1) != 0 &&
		    staType != 0x1C) {
			damageAmount = (damageAmount >= 1) ? 1 : damageAmount;
		}
		if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x2D) == 0x2D && static_cast<CGCharaObj*>(sourceObj)->m_comboItemState >= 0 &&
		    static_cast<CGCharaObj*>(sourceObj)->m_comboLinkCount != 0) {
			System.Printf("魔法剣でダメージを%d倍\n", static_cast<CGCharaObj*>(sourceObj)->m_comboLinkCount);
			damageAmount *= static_cast<CGCharaObj*>(sourceObj)->m_comboLinkCount;
		}

		if (damageAmount != 0) {
			addHp(-damageAmount, sourceObj);
			int isDead = m_scriptHandle->m_hp == 0;
			if (isDead != 0) {
				bonus(0, itemId, sourceObj);
				sourceObj->bonus(1, itemId, this);
			}
			SCharaItemRow* bonusRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			if ((bonusRows[itemId].m_flags32 & 1) != 0 ||
			    ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D && static_cast<CGCharaObj*>(sourceObj)->m_comboItemState >= 0)) {
				bonus(0x15, itemId, sourceObj);
				sourceObj->bonus(0x11, itemId, this);
				if (isDead != 0) {
					sourceObj->bonus(0xC, itemId, this);
				}
				for (int i = 0; i < static_cast<CGCharaObj*>(sourceObj)->m_comboLinkCount; i++) {
					static_cast<CGCharaObj*>(sourceObj)->m_comboLinks[i]->bonus(0x11, itemId, this);
					if (isDead != 0) {
						static_cast<CGCharaObj*>(sourceObj)->m_comboLinks[i]->bonus(0xC, itemId, this);
					}
				}
			} else {
				if (itemEffect == 0x1F8 || particleLife != 2) {
					if (itemEffect == 0x1F8) {
						bonus(0x13, itemId, sourceObj);
						sourceObj->bonus(0xF, itemId, this);
						if (isDead != 0) {
							sourceObj->bonus(10, itemId, this);
						}
					} else {
						bonus(0x12, itemId, sourceObj);
						sourceObj->bonus(0xE, itemId, this);
						if (isDead != 0) {
							sourceObj->bonus(9, itemId, this);
						}
					}
				}
			}
			putHitParticleFromItem(sourceObj, itemId);
			if ((static_cast<unsigned short>(GetCID()) & 0xAD) == 0xAD) {
				CGObjWork* work = m_scriptHandle;
				int seNo = work->m_romWork[0xC9] +
					(work->m_romWork[0xC8] * 1000) + 6 +
					Math.Rand(3);
				playSe3D(seNo, 0x32, 0x96, 0, 0);
			}
		}

		if ((static_cast<unsigned short>(sourceObj->GetCID()) & 0x6D) == 0x6D &&
		    m_scriptHandle->m_hp != 0) {
			int counterState = static_cast<CGCharaObj*>(sourceObj)->m_comboItemState;
			if (counterState >= 0) {
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
				calcRegist(counterType, counterItem, resistType, allowEffect, effectResult, 1);
				if (allowEffect != 0) {
					if ((m_bgColMask & 0x80000) != 0) {
						effective(counterType, counterItem, sourceObj, effectResult);
						playSe3D(counterSe, 0x32, 0x96, 0, 0);
					} else {
						System.Printf("属性剣が、ダメージコリジョンOFF中なので実行しない。\n");
					}
				}
			} else {
				if (((DbgMenuPcs.GetDbgFlag() & 0x20) != 0 ||
				     static_cast<CGPartyObj*>(sourceObj)->m_partyData.unk6CC == 2) &&
				    (calcRegist(0x69, itemId, resistType, allowEffect, effectResult, 0), allowEffect != 0)) {
					int chance = IsKindOf(0xAD) ? m_scriptHandle->m_romWork[0xCD] : 0x32;
					if (chance != 0 && (DbgMenuPcs.GetDbgFlag() & 0x20) != 0) {
						chance = 100;
					}
					if (chance != 0 && static_cast<unsigned int>(Math.Rand(100)) <= static_cast<unsigned int>(chance)) {
						if ((m_bgColMask & 0x80000) != 0) {
							effective(0x69, itemId, sourceObj, effectResult);
						} else {
							System.Printf("ノックバックが、ダメージコリジョンOFF中なので実行しない。\n");
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
		int isDead = m_scriptHandle->m_hp == 0;
		bonus(0x14, itemId, sourceObj);
		sourceObj->bonus(0x10, itemId, this);
		if (isDead != 0) {
			sourceObj->bonus(0x0B, itemId, this);
		}
	}

}


/*
 * --INFO--
 * PAL Address: 0x8010CBC8
 * PAL Size: 2872b
 * EN Address: 0x8010BF28
 * EN Size: 2872b
 * JP Address: 0x80108C18
 * JP Size: 2856b
 */
void CGCharaObj::putParticleFromItem(int effectId, int effectArg0, int effectArg1, Vec* pos)
{
	SCharaItemRow* rows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	int particleBank = rows[effectId].m_particleBank;
	int particleEntry;
	int particleNo;
	int seNo;
	int emittedCustom;
	int hasParticle;

	switch (particleBank) {
	default:
		break;
	case 0xFD:
		particleBank = -1;
		break;
	case 0xFE:
		particleBank = m_charaModelHandle->GetPdtId();
		break;
	case 0xFF:
		hasParticle = 0;
		goto checkParticle;
	}

	if (particleBank == -1) {
		hasParticle = 0;
		goto checkParticle;
	}
	{
		SCharaItemRow* entryRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		particleEntry = entryRows[effectId].m_particleEntries[effectArg0];
	}
	if (particleEntry == 0xFFFF) {
		hasParticle = 0;
		goto checkParticle;
	}
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

checkParticle:
	if (hasParticle == 0) {
		if (effectArg0 == 2) {
			unsigned short seSpec = rows[effectId].m_se2;
			seNo = (seSpec == 0xFFFF) ? 0 : ((seSpec & 0xFF) + ((seSpec >> 8) * 1000));
			if (seNo != 0) {
				int seHandle = playSe3D(seNo, 0x32, 0x96, 0, pos);
				Sound.SetSe3DGroup(seHandle, m_particleId);
			}
	}
	} else {
		CFlatRuntime2Storage().ResetParticleWork((particleBank << 8) | particleNo, effectArg1);
		SCharaItemRow* scaleRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		CFlatRuntime2Storage().SetParticleWorkScale((static_cast<float>(scaleRows[effectId].m_scale) * 0.01f) + 1.0e-07f);
		CFlatRuntime2Storage().SetParticleWorkParam(effectId, this);
		SCharaItemRow* speedRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		CFlatRuntime2Storage().SetParticleWorkSpeed((static_cast<float>(speedRows[effectId].m_speed) * 0.01f) + 1.0e-07f);
		seNo = 0;

		switch (effectArg0) {
		case 0: {
			SCharaItemRow* seRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			int decoded = CharaObjDecodeSe(seRows[effectId].m_se);
			if (decoded != 0) {
				unsigned short seFlag = seRows[effectId].m_seFlag;
				if ((seFlag & 0x8000) != 0) {
					CFlatRuntime2Storage().SetParticleWorkSe(decoded, 2, seFlag & 0xFF);
				} else {
					seNo = decoded;
				}
			}
			break;
		}
		case 1: {
			SCharaItemRow* seRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			int decoded = CharaObjDecodeSe(seRows[effectId].m_se1);
			if (decoded != 0) {
				unsigned short seFlag = seRows[effectId].m_seFlag1;
				if ((seFlag & 0x8000) != 0) {
					CFlatRuntime2Storage().SetParticleWorkSe(decoded, 2, seFlag & 0xFF);
				} else {
					seNo = decoded;
				}
			}
			break;
		}
		case 2: {
			SCharaItemRow* seRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			int decoded = CharaObjDecodeSe(seRows[effectId].m_se2);
			if (decoded != 0) {
				if ((seRows[effectId].m_particleFlags & 0x400) != 0) {
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
			SCharaItemRow* colRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			int itemType = colRows[effectId].m_kind;
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
			CFlatRuntime2Storage().SetParticleWorkCol(colType, -1, (static_cast<float>(colRows[effectId].m_field04) * 0.01f) + 1.0e-07f);
		}

		if ((particleEntry & 0x100) != 0) {
			CFlatRuntime2Storage().SetParticleWorkBind(this);
		} else if ((particleEntry & 0x200) != 0) {
			SCharaItemRow* distRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			float distance = static_cast<float>(distRows[effectId].m_distance) * 1.0f;
			Vec offsetPos;
			offsetPos.x = m_worldPosition.x + sinf(m_rotTargetY) * distance;
			offsetPos.y = m_worldPosition.y;
			offsetPos.z = m_worldPosition.z + cosf(m_rotTargetY) * distance;
			CFlatRuntime2Storage().SetParticleWorkPos(offsetPos, m_rotTargetY);
			CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, 0.0f);
			SCharaItemRow* traceRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			if ((traceRows[effectId].m_particleFlags & 0x2000) != 0) {
				int partyIndex = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6C4);
				if (partyIndex >= 0 && partyIndex < 4) {
					CFlatRuntime2Storage().SetParticleWorkTrace(Game.m_partyObjArr[partyIndex]);
				}
			}
			SCharaItemRow* targetRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			if ((targetRows[effectId].m_particleFlags & 0x4000) != 0) {
				CFlatRuntime2Storage().SetParticleWorkPos(m_worldPosition, m_rotTargetY);
				CFlatRuntime2Storage().SetParticleWorkTarget(m_comboCenter);
				CFlatRuntime2Storage().SetParticleWorkTrace(this);
			}
		} else if (pos != 0) {
			CFlatRuntime2Storage().SetParticleWorkPos(*pos, m_rotTargetY);
		} else if ((particleEntry & 0x400) != 0) {
			CFlatRuntime2Storage().SetParticleWorkPos(m_comboCenter, 0.0f);
		} else {
			CFlatRuntime2Storage().SetParticleWorkPos(m_worldPosition, m_rotTargetY);
		}

		Vec sideOffset;
		emittedCustom = 0;
		switch (effectId) {
		case 0x410:
			if (effectArg0 == 2 || effectArg0 == 3) {
				float baseAngle = m_rotTargetY;
				float angleOffset;
				if (effectArg0 == 2) {
					angleOffset = 1.5707964f;
				} else {
					angleOffset = -1.5707964f;
				}
				float angle = baseAngle + angleOffset;
				CFlatRuntime2Storage().m_particleWorkPos.x = 18.0f * sinf(angle) + m_worldPosition.x;
				CFlatRuntime2Storage().m_particleWorkPos.z = 18.0f * cosf(angle) + m_worldPosition.z;
				CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, 0.0f);
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
				if (m_stateFrame >= kLateItemParticleFrame) {
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | 0x1D);
					CVector randomPos = CVector(0.0f, 7.0f, 165.0f) + CVector(Math.RandFPM(60.0f), 0.0f, Math.RandFPM(60.0f));
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
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) + 0x75));
				} else if (a * 2 <= b) {
					CFlatRuntime2Storage().SetParticleWorkNo((particleBank << 8) | (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) + 0x73));
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
				for (int i = 0; i < 2; i++) {
					PSMTXRotRad(rotMtx, 'y', m_rotTargetY);
					int side = (i == 0) ? 76 : -76;
					PSMTXMultVec(rotMtx, CVector(static_cast<float>(side), 0.0f, 60.0f), &sideOffset);
					CFlatRuntime2Storage().m_particleWorkPos.x = m_worldPosition.x + sideOffset.x;
					CFlatRuntime2Storage().m_particleWorkPos.y = m_worldPosition.y + sideOffset.y;
					CFlatRuntime2Storage().m_particleWorkPos.z = m_worldPosition.z + sideOffset.z;
					CFlatRuntime2Storage().SetParticleWorkVector(m_rotTargetY, 0.0f);
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
			SCharaItemRow* fanRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			int fanCount = fanRows[effectId].m_fanCount;
			if (effectArg0 == 3 && fanCount > 1) {
				for (int i = 0; i < fanCount; i++) {
					CFlatRuntime2Storage().SetParticleWorkVector(6.2831855f * static_cast<float>(i) / static_cast<float>(fanCount), 0.0f);
					CFlatRuntime2Storage().PutParticleWork();
				}
			} else {
				CFlatRuntime2Storage().PutParticleWork();
			}
		}
		}
}

/*
 * --INFO--
 * PAL Address: 0x8010CAF0
 * PAL Size: 216b
 * EN Address: 0x8010BE5C
 * EN Size: 204b
 * JP Address: 0x80108B4C
 * JP Size: 204b
 */
int la(CGObject* object)
{
	CCharaPcs::CHandle* model = object->m_charaModelHandle;
	bool hasMotion = false;
	int result;
	if (model != 0 && model->m_model != 0) {
		hasMotion = true;
	}

	if (!hasMotion) {
		result = 1;
	} else {
		CChara::CModel* motion = model->m_model;
		if (motion->m_anim != 0) {
#ifdef VERSION_GCCP01
			int frame;
			int period = static_cast<int>(1.0f + (motion->m_animEnd -
				motion->m_animStart));
			if (period == 1) {
				result = 1;
			} else {
				frame = static_cast<int>(object->m_turnSpeed);
				int frameMod = frame % period;
				if (object->m_lastBgAttr < 0.0f) {
					result = __rlwnm(1, static_cast<unsigned int>(__cntlzw(frameMod)), 31, 31) & 0xFF;
				} else {
					bool isPeriod = (period <= frame);
					result = isPeriod;
				}
			}
#else
			int period = static_cast<int>(1.0f + (motion->m_animEnd -
				motion->m_animStart));
			int frame;
			if (period == 1) {
				result = 1;
			} else {
				frame = static_cast<int>(object->m_turnSpeed);
				frame %= period;
				if (object->m_lastBgAttr < 0.0f) {
					result = __rlwnm(1, static_cast<unsigned int>(__cntlzw(frame)), 31, 31) & 0xFF;
				} else {
					bool isPeriod = (frame == 0);
					result = isPeriod;
				}
			}
#endif
		} else {
			result = 1;
		}
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x8010C704
 * PAL Size: 1004b
 * EN Address: 0x8010BA7C
 * EN Size: 992b
 * JP Address: 0x8010876C
 * JP Size: 992b
 */
void CGCharaObj::statAttack()
{
	unsigned short cid = GetCID();

	if ((cid & 0xAD) == 0xAD && m_subState == 0) {
		int animPoint = m_scriptHandle->m_baseDataIndex;
		if (animPoint == 0x88 || animPoint == 0x87) {
			if (la(this)) {
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

	SCharaItemRow* rows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	if ((rows[m_itemId].m_seFlag & 0x8000) == 0 && m_stateFrame == rows[m_itemId].m_seFlag) {
		int seSpec = rows[m_itemId].m_se;
		if (seSpec != 0) {
			int seNo = (seSpec == 0xFFFF) ? 0 : ((seSpec & 0xFF) + ((seSpec >> 8) * 1000));
			playSe3D(seNo, 0x32, 0x96, 0, 0);
		}
	}

	rows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	if ((rows[m_itemId].m_seFlag1 & 0x8000) == 0 && m_stateFrame == rows[m_itemId].m_seFlag1) {
		int seSpec = rows[m_itemId].m_se1;
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
 * PAL Address: 0x8010C2F0
 * PAL Size: 964b
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
	int result;

	if ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		Game.m_gameWork.m_menuStageMode != 0 &&
		Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
		(static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId != 0) {
		return 0;
	}

	SCharaItemRow* castRows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	unsigned int baseCast = castRows[itemId].m_power;
	float castScale;

	if (m_scriptHandle->m_statusTimers[8] != 0) {
		castScale = CharaObjGetStatusMultiplier(0x0);
	} else if (m_scriptHandle->m_statusTimers[7] != 0) {
		castScale = CharaObjGetStatusMultiplier(0x2);
	} else {
		castScale = 1.0f;
	}

	SCharaItemRow* typeRows = castRows;
	int itemType = typeRows[itemId].m_actionType;
	int itemNo = typeRows[itemId].m_effect;

	if (itemNo != 0x1F8 && itemType == 2) {
		int castBonus = m_scriptHandle->m_romWork[0xCA];
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
				castBonus = castBonus < 0 ? 0 : castBonus;
			}
		}

		unsigned int playerCid = (static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D;
		unsigned int castReduction = playerCid != 0 ? static_cast<unsigned char>(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_equipEffectParams[0]) : 0;
		int totalCast = static_cast<int>(baseCast + castBonus) - static_cast<int>(castReduction);
		result = static_cast<int>(castScale * static_cast<float>(totalCast));
		result = result < 0 ? 0 : result;
		System.Printf("魔法キャスト: (%d + %d - %d) * %f = %d\n", baseCast, castBonus, castReduction, castScale, result);
	} else if (itemType == 3) {
		result = static_cast<int>(baseCast);
		System.Printf("回転キャスト: %d\n", baseCast);
	} else if (itemType == 4) {
		result = static_cast<int>(baseCast);
		System.Printf("防御キャスト: %d\n", baseCast);
	} else if (itemNo == 0x1F8) {
		int castBonus = m_scriptHandle->m_romWork[0xCB];
		unsigned int playerCid = (static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D;
		unsigned int castReduction = playerCid != 0 ? static_cast<unsigned char>(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_equipEffectParams[1]) : 0;
		int totalCast = static_cast<int>(baseCast + castBonus) - static_cast<int>(castReduction);
		result = static_cast<int>(castScale * static_cast<float>(totalCast));
		result = result < 0 ? 0 : result;
		System.Printf("チャージキャスト: (%d + %d - %d) * %f = %d\n", baseCast, castBonus, castReduction, castScale, result);
	}

	return result;
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
void CGCharaObj::onDrawDebug(CFont* font, float posX, float& posY, float posZ)
{
	if ((m_weaponNodeFlagBits.m_prg && (static_cast<int>(CFlatCenterState()) == 0)) &&
	    ((DbgMenuPcs.GetDbgFlag() & 0x80) != 0)) {
		char text[0x100];
		unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
		double posYDouble;

		sprintf(text, "%d/%d %d %d %d",
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
				if ((static_cast<int>(System.GetCounter()) % 0x1E) == 0) {
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
 * EN Address: 0x8010AD30
 * EN Size: 1804b
 * JP Address: 0x80107A30
 * JP Size: 1788b
 */
void CGCharaObj::combi2()
{
#ifdef VERSION_GCCP01
	const int kComboWaitFrames = 66;
#else
	const int kComboWaitFrames = 80;
#endif
	int i;
	int j;
	int k;
	int hasNearbyPartner;
	int playedComboSe;
	CGPartyObj* leadParty;
	CGPartyObj* candidates[5];
	int candidateCount = 0;
	CVector comboCenter;

	for (i = 0; i < 4; i++) {
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

	for (i = 0; i < candidateCount; i++) {
		CGPartyObj* party = candidates[i];
		if (party == 0 || party->m_comboState == 0) {
			continue;
		}

		hasNearbyPartner = 0;
		for (j = 0; j < candidateCount; j++) {
			if (i == j) {
				continue;
			}

			CGPartyObj* other = candidates[j];
			if (other == 0 || other->m_comboState == 0) {
				continue;
			}

			if (PSVECDistance(&party->m_comboCenter, &other->m_comboCenter) < 20.0f) {
				hasNearbyPartner = 1;
				break;
			}
		}

		PartyObjFlags& comboFlags = party->m_partyData.flags;
		if (hasNearbyPartner && comboFlags.flag40 == 0) {
			goto changed;
		}
		if (!hasNearbyPartner && comboFlags.flag40 != 0) {
			goto changed;
		}
		continue;
	changed:
		comboFlags.flag40 = static_cast<signed char>(hasNearbyPartner);
		comboFlags.flag10 = 1;
		party->playSe3D(hasNearbyPartner ? 0x3C : 0x3D, 0x32, 0x96, 0, 0);
	}

	for (i = 0; i < candidateCount - 1; i++) {
		for (j = i + 1; j < candidateCount; j++) {
			if (candidates[i]->m_comboFrame < candidates[j]->m_comboFrame) {
				CGPartyObj* swap = candidates[i];
				candidates[i] = candidates[j];
				candidates[j] = swap;
			}
		}
	}

	for (i = 1; i < candidateCount; i++) {
		if (20.0f < PSVECDistance(&candidates[0]->m_comboCenter, &candidates[i]->m_comboCenter)) {
			for (k = i; k < candidateCount - 1; k++) {
				candidates[k] = candidates[k + 1];
			}
			candidateCount--;
			i--;
		}
	}

	if (candidates[0]->m_comboFrame == 0) {
		return;
	}

	int fallback;
	int comboIndex = searchCombi(candidateCount, candidates, fallback);
	if (comboIndex >= 0) {
	if (fallback != 0 && candidates[0]->m_comboFrame < kComboWaitFrames) {
		return;
	}

	CCombi2* comboData = &Game.m_combiTable[comboIndex];
	int participantCount = comboData->GetNumSet();

	const int isShared1F8 = comboData->m_sets[participantCount - 1].m_item == 0x1F8;
	if (isShared1F8 == 0) {
		comboCenter.Identity();
		for (i = 0; i < participantCount; i++) {
			CVector candidateCenter(candidates[i]->m_comboCenter);
			PSVECAdd(reinterpret_cast<Vec*>(&comboCenter), reinterpret_cast<Vec*>(&candidateCenter), reinterpret_cast<Vec*>(&comboCenter));
		}
		comboCenter /= static_cast<float>(participantCount);
	}

	System.Printf("combi: %d: combi%dに決定\n", System.GetCounter(), comboData->m_command);

	leadParty = candidates[participantCount - 1];
	playedComboSe = 0;
	for (i = 0; i < participantCount; i++) {
		CGPartyObj* party = candidates[i];
		unsigned int comboMode = 0xFFFFFFFF;

		if (isShared1F8 != 0) {
			switch (comboData->m_command) {
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
				party->m_comboItemState = static_cast<int>(comboMode);
				party->playSe3D(0x3F, 0x32, 0x96, 0, 0);
			} else {
				party->m_comboCenter = leadParty->m_worldPosition;
				party->m_itemId = 0;
			}
		} else {
			party->m_comboCenter = comboCenter;
			if (playedComboSe == 0 &&
			    (Game.m_gameWork.m_menuStageMode == 0 || Game.m_gameWork.m_bossArtifactStageIndex >= 0xF ||
			     (static_cast<unsigned short>(party->GetCID()) & 0x6D) != 0x6D ||
			     *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party->m_scriptHandle) + 0x3B4) == 0)) {
				party->m_itemId = comboData->m_command;
				party->playSe3D(0x3F, 0x32, 0x96, 0, 0);
				playedComboSe = 1;
			} else {
				party->m_itemId = 0;
			}
		}

		party->m_comboState = 0;
		party->m_comboFrame = 0;
		party->addSubStat();
		party->putComboParticle();

		party->m_comboScriptArg = comboData->m_command;
		party->m_comboScriptMode = comboMode;
		party->m_comboLinkCount = 0;

		for (j = 0; j < participantCount; j++) {
			CGPartyObj* other = candidates[j];
			if (party == other) {
				continue;
			}
			party->m_comboLinks[party->m_comboLinkCount++] = other;
		}
	}

	combi2();
	return;
	}

	if (fallback == 0 || candidates[0]->m_comboFrame >= kComboWaitFrames) {
		candidates[0]->m_comboState = 0;
		candidates[0]->m_comboFrame = 0;
		candidates[0]->addSubStat();
		combi2();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8010B8B8
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGCharaObj::sendCombiToScript(CGCharaObj* target, int scriptArg, int)
{
	int entry = 0;
	while (entry < m_comboLinkCount) {
		if (m_comboLinks[entry] != 0) {
			if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
			    (static_cast<unsigned short>(m_comboLinks[entry]->GetCID()) & 0x6D) == 0x6D &&
			    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_comboLinks[entry]->m_scriptHandle) + 0x3B4) != 0) {
				goto next_link;
			} else if (m_comboLinks[entry]->m_lastStateId != 6 && m_comboLinks[entry]->m_lastStateId != 2) {
				break;
			}
		}
next_link:
		entry++;
	}
	if (entry == m_comboLinkCount) {
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
 * PAL Address: UNUSED
 * PAL Size: 84b
 * EN Address: 0x80132818
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CGCharaObj::scCheckItem(CCombi2Set* set, CGCharaObj* object, int lastSlot)
{
    int item = object->m_itemId;
    SCharaItemRow* items = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
    int kind = items[item].m_effect;
    if ((lastSlot && kind == 0x1F8 && set->m_item == 0x1F8) || item == set->m_item) {
        return 1;
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 88b
 * EN Address: 0x80132880
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CGCharaObj::scCheckTime(CCombi2Set* set, CGCharaObj* first, CGCharaObj* object, int checkMinimum)
{
    int frames = first->m_comboFrame - object->m_comboFrame;
    if (first == object || ((!checkMinimum || set->m_minFrames <= frames) && set->m_maxFrames >= frames)) {
        return 1;
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8010B690
 * PAL Size: 552b
 * EN Address: 0x8010AA08
 * EN Size: 552b
 * JP Address: 0x80107708
 * JP Size: 552b
 */
int CGCharaObj::searchCombi(int count, CGPartyObj** partyList, int& outFallback)
{
	int found = -1;
	outFallback = 0;

	CCombi2* combiCursor = Game.m_combiTable;
	for (int combiIndex = 0; combiIndex < static_cast<int>(Game.m_combiCount); combiIndex++, combiCursor++) {
		int reqCount = combiCursor->GetNumSet();

		if (count < reqCount) {
			break;
		}

		int reqLast = reqCount - 1;
		CCombi2Set* slotCursor = combiCursor->m_sets;
		CGCharaObj* partyObj;
		int slot = 0;
		for (; slot < reqCount; slot++, slotCursor++) {
			partyObj = partyList[slot];
			if (partyObj->m_comboFrame == 0) {
				CCombi2Set* fallbackCursor = slotCursor;
				for (; slot < reqCount; slot++, fallbackCursor++) {
					int itemMatch = scCheckItem(fallbackCursor, partyObj, slot == count - 1);
					if (itemMatch) {
						int closeOk = scCheckTime(slotCursor, partyList[0], partyObj, 0);
						if (closeOk) {
							break;
						}
					}
				}
				if (slot < count) {
					outFallback = 1;
					goto done;
				}
				break;
			}

			if (!scCheckItem(slotCursor, partyObj, slot == count - 1) || !scCheckTime(slotCursor, partyList[0], partyObj, 1)) {
				break;
			}

			if (slot == reqLast) {
				found = combiIndex;
			}
		}
	}

done:
	return found;
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

void CGPrgObj::bonus(int, int, CGPrgObj*)
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
void CGCharaObj::enableDamageCol(int)
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
void CGCharaObj::enableAttackCol(int, int, int)
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
void CGCharaObj::onStatShield()
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
void CGCharaObj::onStatAttack(int)
{
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
void CGCharaObj::onStatDie()
{
}
int CGCharaObj::GetCID()
{
	return 0x2D;
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

