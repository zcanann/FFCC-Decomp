#include "ffcc/ptrarray.h"
#include "ffcc/monobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/gobjwork.h"
#include "ffcc/itemobj.h"
#include "ffcc/fontman.h"
#include "ffcc/math.h"
#include "ffcc/astar.h"
#include "ffcc/game.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/monobj_table.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/p_map.h"
#include "ffcc/partyobj.h"
#include "ffcc/sound.h"
#include "ffcc/gbaque.h"
#include "ffcc/joybusconst.h"
#include "ffcc/linkage.h"
#include "ffcc/vector.h"
#include "PowerPC_EABI_Support/Runtime/ptmf.h"

#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

STATIC_ASSERT(offsetof(CGObject, m_homeRotY) == 0x1BC);
STATIC_ASSERT(offsetof(CGCharaObj, m_alpha) == 0x694);
STATIC_ASSERT(offsetof(CGCharaObj, m_particleSlots) + 12 * sizeof(int) == 0x594);
STATIC_ASSERT(offsetof(CGCharaObj, m_partyDistance) == 0x5D0);
STATIC_ASSERT(offsetof(CGCharaObj, m_partyRank) == 0x620);
STATIC_ASSERT(offsetof(CCaravanWork, m_joybusCaravanId) == 0x3B4);

CGMonObj::AiWork CGMonObj::m_aiWork;
u8 CGMonObj::m_boss[0x8C];

extern "C" float g_hit_t;
extern "C" float g_hit_t_slide_min;


inline int CMapPcs::CheckHitCylinderNear(Vec* cylinderBottom, Vec* direction, float radius, unsigned long hitMask)
{
	CMapCylinder cylinder;

	cylinder.m_bottom = *cylinderBottom;
	cylinder.m_axis = *direction;
	cylinder.m_radius = radius;

	return MapMng.CheckHitCylinderNear(&cylinder, direction, hitMask);
}

inline float CMapPcs::GetHitT()
{
	return g_hit_t_slide_min;
}

struct CMonAiAction {
	unsigned short m_flags;
	unsigned short m_minDist;
	unsigned short m_maxDist;
	unsigned short m_chance;
	unsigned short m_type;
	unsigned short m_group;
	unsigned short m_range;
	unsigned short m_changeStat;
};

static inline unsigned char* CGMonObj_GetAiData(CGMonObj* monObj)
{
	if (monObj->m_aiState == 0) {
		return reinterpret_cast<unsigned char*>(monObj->m_scriptHandle->m_romWork);
	}
	return reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
		(monObj->m_aiState + monObj->m_scriptHandle->m_romWork[0x80]) * 0x1D0 + 0x10;
}

static inline void CGMonObj_SetChaseMove(CGMonObj* monObj, CGPartyObj* target, unsigned int flags)
{
	if (monObj->m_moveWork.m_mode != 4) {
		monObj->m_moveWork.Clear();
		monObj->m_moveWork.m_flags = 0x855;
		if ((monObj->m_scriptHandle->m_romWork[0x7F] & 4) != 0) {
			monObj->m_moveWork.m_flags |= 0x400;
		}
		if ((*reinterpret_cast<unsigned short*>(CGMonObj_GetAiData(monObj) + 0x102) & 0x80) != 0) {
			monObj->m_moveWork.m_flags |= 0x20000;
		}
		monObj->m_moveWork.SetFlags(flags, 0);
		monObj->m_moveWork.m_mode = 4;
		monObj->m_moveWork.m_range =
			static_cast<float>(monObj->m_scriptHandle->m_romWork[0x67]);
		monObj->m_moveWork.m_limitFrame = monObj->m_scriptHandle->m_romWork[0xDB];
	}
	monObj->m_moveWork.m_target = reinterpret_cast<CGCharaObj*>(target);
}

static inline void CGMonObj_SetAttackMove(CGMonObj* monObj, CGPartyObj* target, float range, int changeStat)
{
	if (monObj->m_moveWork.m_mode != 2) {
		monObj->m_moveWork.Clear();
		monObj->m_moveWork.m_flags = 0x325;
		if ((*reinterpret_cast<unsigned short*>(CGMonObj_GetAiData(monObj) + 0x102) & 0x40) != 0) {
			monObj->m_moveWork.m_flags |= 0x10000;
		}
		monObj->m_moveWork.SetFlags(0, 0);
		monObj->m_moveWork.m_mode = 2;
	}
	monObj->m_moveWork.m_target = reinterpret_cast<CGCharaObj*>(target);
	monObj->m_moveWork.m_range = range;
	monObj->m_moveWork.m_changeStat = changeStat;
}

static inline int CGMonObj_SearchNoticeParty(CGMonObj* monObj)
{
	if (monObj->m_targetDist < ((Game.m_gameWork.m_soundOptionFlag != 0) ? 10000.0 : 180.0)) {
		float hitScale;
		int colIndex;
		monObj->checkCol(6, monObj->m_rotBaseY,
		                 static_cast<float>(monObj->m_scriptHandle->m_romWork[0x64]),
		                 &hitScale, &colIndex);
		if (colIndex >= 0) {
			return colIndex;
		}
	}
	return -1;
}

static inline void CGMonObj_MoveToTarget(CGMonObj* monObj, float speedScale)
{
	monObj->moveVector(CVector(monObj->m_worldPosition) - CVector(reinterpret_cast<CGObject*>(Game.m_partyObjArr[monObj->m_targetPartyIndex])->m_worldPosition), speedScale, 1);
}

static inline void CGMonObj_ChaseTarget(CGMonObj* monObj)
{
	float speedScale = monObj->m_pushScale *
		(0.01f * static_cast<float>(monObj->m_scriptHandle->m_romWork[0x6A]) + 0.0000001f);
	CGMonObj_MoveToTarget(monObj, speedScale);
}

/*
 * --INFO--
 * PAL Address: 0x8011A4CC
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onCreate()
{
	CGCharaObj::onCreate();

	m_targetPartyIndex = -1;
	m_aiState = 0;
	m_aiStatePrev = 0;
	m_unk6C8 = 0;
	m_unk6CC = 0;
	m_actionBranch = 0;
	m_unk6B8 = 0;
	m_unk6B9 = 0;
	m_unk6BA = 0;
	m_unk6BC = 0;
	m_unk6BD = 0;
	m_unk6BE = 0;
	m_attackDelay = 0;
	m_aliveFrames = 0;
	m_unk6BF = 0;
	m_unk6C0 = 0;
	m_unk6C2 = 0;
	m_unk6C3 = 0;
	m_chaseState = 0;
	m_chaseTimer = 0;
	m_chaseDirty = 0;
	m_stepSeHandle = 0;
	m_moveWork.Clear();
	m_unk6E0 = 0;
	m_unk6C1 = 0;
}


/*
 * --INFO--
 * PAL Address: 0x8011A4AC
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onDestroy()
{
	CGCharaObj::onDestroy();
}

/*
 * --INFO--
 * PAL Address: 0x8011A290
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onFramePreCalc()
{
#define object (reinterpret_cast<CGObject*>(this))
#define mon (reinterpret_cast<unsigned char*>(this))

	CGCharaObj::onFramePreCalc();
	m_aliveFrames += 1;

	if (object->m_scriptHandle->m_romWork[0x86] == 1) {
		unsigned char* aiData;
		short& aiState = m_aiState;
		short& aiStatePrev = m_aiStatePrev;

		if (aiState == 0) {
			aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
		} else {
			aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
				(aiState + *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork) + 0x100)) * 0x1D0 + 0x10;
		}

		aiState = (this->*m_funcs->calcBranch)(*reinterpret_cast<unsigned short*>(aiData + 0x102) & 3);

		if (aiState != aiStatePrev) {
			aiStatePrev = aiState;
			m_unk6CC = 0;
		}
	}

	if ((object->m_scriptHandle->m_statusTimers[0] == 0) &&
		(object->m_scriptHandle->m_statusTimers[9] == 0) &&
		(object->m_scriptHandle->m_statusTimers[3] == 0) &&
		(object->m_scriptHandle->m_statusTimers[4] == 0) &&
		(static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(mon[0x63C]) << 24) & 0xC0000000) >> 31) != 0) &&
		(m_unk6B9 == 0) &&
		(m_unk6C1 == 0)) {
		if (object->m_scriptHandle->m_romWork[0x86] == 1) {
			CGMonObj::m_aiWork.m_state = -1;
		} else {
			CGMonObj::m_aiWork.m_state = 0;
		}
		CGMonObj::m_aiWork.m_target = m_targetPartyIndex;
		CGMonObj::m_aiWork.m_priority = -1;

		int classId = object->m_scriptHandle->m_baseDataIndex;
		int aiLocal = 0;
		if ((0x9A <= classId) ||
			(classId < 0x8E)) {
			(this->*m_funcs->logic)();
		} else {
			aiAddDuct(aiLocal);
		}

		if (object->m_scriptHandle->m_romWork[0x86] == 1) {
			if ((CGMonObj::m_aiWork.m_state != -1) && (CGMonObj::m_aiWork.m_state != reinterpret_cast<CGPrgObj*>(this)->m_lastStateId)) {
				reinterpret_cast<CGPrgObj*>(this)->changeStat(CGMonObj::m_aiWork.m_state, 0, 0);
			}
		} else if (CGMonObj::m_aiWork.m_state != reinterpret_cast<CGPrgObj*>(this)->m_lastStateId) {
			reinterpret_cast<CGPrgObj*>(this)->changeStat(CGMonObj::m_aiWork.m_state, 0, 0);
		}
	}
#undef object
#undef mon
}

/*
 * --INFO--
 * PAL Address: 0x8011A248
 * PAL Size: 72b
 * EN Address: 0x801195A8
 * EN Size: 72b
 * JP Address: 0x80116200
 * JP Size: 64b
 */
void CGMonObj::flyDown()
{
	changeStat(0x17, 0, 0);
	m_unk6B9 = 1;
#ifndef VERSION_GCCJGC
	damageDelete();
#endif
}

/*
 * --INFO--
 * PAL Address: 0x8011A21C
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::flyUp()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	prgObj->changeStat(0x16, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8011A0F4
 * PAL Size: 296b
 * EN Address: 0x80133144
 * EN Size: 116b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::undeadOff()
{
	m_alpha = 1.0f;

	setUndeadEffect(m_weaponNodeFlagBits.m_prg, 0);

	if (m_scriptHandle->m_romWork[0x7E] == 0xB) {
		SetTexAnim("u0");
	}

	m_unk6BA = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80119F74
 * PAL Size: 384b
 * EN Address: 0x801331B8
 * EN Size: 240b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::undeadOn()
{
	m_alpha = 0.4f;
	int classId = m_scriptHandle->m_baseDataIndex;
	setUndeadEffect(m_weaponNodeFlagBits.m_prg, 1);

	if (m_scriptHandle->m_romWork[0x7E] == 0xB) {
		SetTexAnim("u1");
	}

	if (m_weaponNodeFlagBits.m_prg != 0) {
		if (classId == 0x83) {
			playSe3D(0x987A, 0x32, 0x96, 0, (Vec*)0);
		} else if (classId == 0x7F) {
			playSe3D(0x11585, 0x32, 0x96, 0, (Vec*)0);
		}
	}

	m_unk6BA = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80119EC0
 * PAL Size: 180b
 * EN Address: 0x801332A8
 * EN Size: 284b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::rotTarget(int targetPartyIndex, float rotLimit)
{
	if (targetPartyIndex >= 0) {
		float targetRot = getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[targetPartyIndex]));
		if (rotLimit > 2.0943952f) {
			m_rotTargetY = targetRot;
		} else {
			float delta = Math.DstRot(targetRot, m_homeRotY);
			float clamped = delta < -rotLimit ? -rotLimit : (rotLimit < delta ? rotLimit : delta);
			m_rotTargetY = m_homeRotY + clamped;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80119A64
 * PAL Size: 1116b
 * EN Address: 0x801333C4
 * EN Size: 664b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onStatAttack(int state)
{
#define prgObj (reinterpret_cast<CGPrgObj*>(this))
#define object (reinterpret_cast<CGObject*>(this))
	SCharaItemRow* attackData = &reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2])[m_itemId];
	int attackType = attackData->m_actionType;
	unsigned short attackFlags = attackData->m_flags32;

	if (state == 0) {
		if ((prgObj->m_stateFrame == 0) && (m_targetPartyIndex >= 0)) {
			m_comboCenter = reinterpret_cast<CGObject*>(Game.m_partyObjArr[m_targetPartyIndex])->m_worldPosition;
			if (state == 3) {
				return;
			}

			if ((attackFlags & 2) == 0) {
				rotTarget(m_targetPartyIndex, 0.017453292f * static_cast<float>(object->m_scriptHandle->m_romWork[0xCE]));
			}

			CGPartyObj* target = Game.m_partyObjArr[m_targetPartyIndex];
			reinterpret_cast<CGPrgObj*>(target)->bonus(0x17, m_itemId, reinterpret_cast<CGPrgObj*>(target));
		}
		return;
	}

	if (attackType == 3) {
		switch (prgObj->m_subState) {
		case 0:
			if (prgObj->isLoopAnim() != 0) {
				prgObj->addSubStat();
			}
			break;
		case 1:
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(m_unk554, 1, 0);
			}
			SCharaItemRow* rows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
			if (prgObj->m_subFrame == rows[m_itemId].m_power) {
				prgObj->addSubStat();
			}
			break;
		case 2:
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(m_unk558, 0, 0);
				reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(1);
			}
			if (prgObj->isLoopAnim() != 0) {
				setAttackAfter(m_itemId);
			}
			break;
		}
		return;
	}

	if ((__cntlzw(prgObj->m_stateArg) >> 5 & 1) && (prgObj->isLoopAnim() != 0)) {
		setAttackAfter(m_itemId);
	}
#undef prgObj
#undef object
#undef mon
}

/*
 * --INFO--
 * PAL Address: 0x80119930
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::setAttackAfter(int attackKind)
{
	SCharaItemRow* rows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
	int delay = rows[attackKind].m_status;
	if (delay == 0xFFFF) {
		delay = 0;
	}

	int stageRank;
	if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		int rawStage = Game.m_gameWork.m_bossArtifactStageTable[Game.m_gameWork.m_bossArtifactStageIndex];
		stageRank = 2;
		if (rawStage < 2) {
			stageRank = rawStage;
		}
	} else {
		stageRank = 0;
	}

	if (0 < stageRank) {
		delay -= reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unk_flat3_field_8_0xc7dc) + 0x58)[stageRank];
		delay &= ~((int)delay >> 31);
	}

	if (delay != 0) {
		int range = delay / 5;
		int clampedRange = 1;
		if (range >= 1) {
			clampedRange = range;
		}

		delay += Math.Rand(clampedRange);
		m_attackDelay = delay;
		changeStat(0x11, 0, 0);
	} else {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80119674
 * PAL Size: 700b
 * EN Address: 0x80133808
 * EN Size: 756b
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::getNearParty(int targetOrdinal, int flags, float minDist, float maxDist, int classId)
{
	int foundCount = 0;
	int selectedPartyIndex = -1;

	for (int slot = 0; slot < 4; slot++) {
		int partyIndex = m_partyRank[slot];
		CGPartyObj* party = Game.m_partyObjArr[partyIndex];

		if ((party != NULL) &&
			(((Game.m_gameWork.m_menuStageMode == 0) ||
				(0xF <= Game.m_gameWork.m_bossArtifactStageIndex) ||
				!party->IsKindOf(0x6D) ||
				(reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->m_joybusCaravanId == 0))) &&
			(((flags & 1) == 0) ||
				((reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->m_hp != 0) &&
					(party->m_lastStateId != 9) && (party->m_lastStateId != 0x22) &&
					((Game.m_gameWork.m_menuStageMode == 0) ||
						(0xF <= Game.m_gameWork.m_bossArtifactStageIndex) ||
						!party->IsKindOf(0x6D) ||
						(reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->m_joybusCaravanId == 0)))) &&
			(((flags & 0x10) == 0) ||
				(reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->m_statusTimers[8] != 0)) &&
			(((flags & 0x20) == 0) ||
				(((party->m_lastStateId == 6) || (party->m_lastStateId == 2)) &&
					(party->m_subState == 1))) &&
			(((flags & 0x40) == 0) ||
				((party->m_partyData.unk6C0 >= 0) &&
					(reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->m_baseDataIndex == classId))) &&
			(((flags & 2) != 0) || !(m_partyDistance[partyIndex] < minDist)) &&
			(((flags & 4) != 0) || !(maxDist < m_partyDistance[partyIndex]))) {
			if (((flags & 8) != 0) && (0.0f < m_partyDistance[partyIndex])) {
				Vec toParty;
				Vec facing;
				PSVECSubtract(&party->m_worldPosition, &m_worldPosition, &toParty);
				PSVECScale(&toParty, &toParty, 1.0f / m_partyDistance[partyIndex]);
				facing.x = sin(m_rotTargetY);
				facing.y = 0.0f;
				facing.z = cos(m_rotTargetY);
				if (PSVECDotProduct(&toParty, &facing) <= 0.0f) {
					continue;
				}
			}

			if ((targetOrdinal == -1) || (targetOrdinal == foundCount)) {
				selectedPartyIndex = partyIndex;
				if (targetOrdinal == foundCount) {
					break;
				}
			}
			foundCount++;
		}
	}

	return selectedPartyIndex;
}

/*
 * --INFO--
 * PAL Address: 0x80119528
 * PAL Size: 332b
 * EN Address: 0x80118888
 * EN Size: 332b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onChangeStat(int state)
{
	(this->*m_funcs->changeStat)(state);

	switch (state) {
	case 3:
	case 4:
	case 5:
		break;
	case -14:
	case -13:
	case -12:
	case -11:
	case -10:
	case -9:
	case -8:
	case -7:
	case -6:
	case -5:
		setActionParam(state);
		break;
	}

	CGCharaObj::onChangeStat(state);
}

/*
 * --INFO--
 * PAL Address: 0x80119428
 * PAL Size: 256b
 * EN Address: 0x80118788
 * EN Size: 256b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::setActionParam(int state)
{
	state += 0xE;
	m_itemId = SAFE_CAST_MON_WORK(m_scriptHandle)->m_actionItems[state];
	m_attackAnimId = SAFE_CAST_MON_WORK(m_scriptHandle)->m_actionAnimations[state];
	m_unk554 = m_attackAnimId + 1;
	m_unk558 = m_unk554 + 1;
	m_unk55C = m_unk558 + 1;

	const SCharaItemRow* items = reinterpret_cast<const SCharaItemRow*>(Game.unkCFlatData0[2]);
	int actionType = items[m_itemId].m_actionType;
	switch (actionType) {
	case 0:
	case 1:
	case 3:
		items = reinterpret_cast<const SCharaItemRow*>(Game.unkCFlatData0[2]);
		m_castFrameStart = items[m_itemId].m_attackStartFrame;
		items = reinterpret_cast<const SCharaItemRow*>(Game.unkCFlatData0[2]);
		m_castFrameEnd = items[m_itemId].m_attackEndFrame;
		items = reinterpret_cast<const SCharaItemRow*>(Game.unkCFlatData0[2]);
		m_castFrameCurrent = items[m_itemId].m_attackEndFrame;
		break;
	case 2:
		m_unk68C = CGCharaObj::calcCastTime(m_itemId);
		break;
	case 4:
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80119278
 * PAL Size: 432b
 * EN Address: 0x801185D8
 * EN Size: 432b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onCancelStat(int state)
{
	(this->*m_funcs->cancelStat)();

	switch (m_lastStateId) {
	case 0x1D:
		CancelMove(1);
		break;

	case 0x16:
		m_unk6B9 = 0;
		SetAnimSlot(0, 0);
		SetAnimSlot(1, 1);
		SetAnimSlot(4, 4);
		SetAnimSlot(6, 6);
		break;

	case 0x17:
		m_unk6B9 = 1;
		SetAnimSlot(0x28, 0);
		SetAnimSlot(0x29, 1);
		SetAnimSlot(0x2A, 4);
		SetAnimSlot(0x2B, 6);
		break;

	case 0x21:
		moveCancel();
		if ((m_moveWork.m_stateFlags & 2) == 0) {
			(this->*m_funcs->moveCancel)();
		}
		break;

	case 0x18:
		m_actionBranch = 1;
		SetAnimSlot(0, 0);
		SetAnimSlot(4, 4);
		m_bgColMask |= 0x50000;
		m_bgColMask &= 0xFFFFFFF7;
		m_objectFlags &= 0xFFFFFFEF;
		break;
	}

	CGCharaObj::onCancelStat(state);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 72b
 * EN Address: 0x80133E7C
 * EN Size: 84b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CGMonObj::isValidTarget()
{
	if ((m_targetPartyIndex < 0) ||
		((m_targetPartyIndex >= 0) &&
		 (reinterpret_cast<CGObject*>(Game.m_partyObjArr[m_targetPartyIndex])->m_scriptHandle->m_hp == 0))) {
		return 0;
	}
	return 1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 320b
 * EN Address: 0x80133ED0
 * EN Size: 160b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::seKiduki()
{
	if (m_unk6B8 == 0) {
		CGObjWork* scriptHandle = m_scriptHandle;
		int se = Math.Rand(3);
		unsigned short* romWork = scriptHandle->m_romWork;
		se += romWork[0xC8] * 1000 + romWork[0xC9];
		playSe3D(se, 0x32, 0x96, 0, reinterpret_cast<Vec*>(NULL));
		m_unk6B8 = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onFrameStat()
{
#define prgObj (reinterpret_cast<CGPrgObj*>(this))
#define object (reinterpret_cast<CGObject*>(this))
#define mon (reinterpret_cast<unsigned char*>(this))
#define SET_DRAW_FLAG() do { struct B63C { unsigned char hi : 1; unsigned char lo : 7; }; \
		reinterpret_cast<B63C*>(mon + 0x63C)->hi = 1; } while (0)

	switch (*reinterpret_cast<int*>(mon + 0x520)) {
	case 3:
	case 0x11:
	case 0x1E:
		if (object->m_scriptHandle->m_hp != 0) {
			if (!isValidTarget()) {
				m_targetPartyIndex = -1;
				prgObj->changeStat(0, 0, 0);
			}
		}
		break;
	}

	(this->*m_funcs->frameStat)();

	switch (*reinterpret_cast<int*>(mon + 0x520)) {
	case 0:
		if (m_aliveFrames >= 0x2D) {
			SET_DRAW_FLAG();
		}
		if (prgObj->m_stateFrame == 0) {
			prgObj->reqAnim(-1, 0, 0);
		}
		break;


	case 3: {
		SET_DRAW_FLAG();
		if (prgObj->m_stateFrame == 0) {
			object->CancelAnim(1);
			seKiduki();
		}

		int targetPartyIndex = m_targetPartyIndex;
		if ((targetPartyIndex >= 0) && (targetPartyIndex < 4)) {
			CGPartyObj* target = Game.m_partyObjArr[targetPartyIndex];
			Vec src = reinterpret_cast<CGObject*>(target)->m_worldPosition;
			Vec delta;
			PSVECSubtract(&src, &object->m_worldPosition, &delta);
			float speedScale = *reinterpret_cast<float*>(mon + 0x690) *
				(0.01f * static_cast<float>(object->m_scriptHandle->m_romWork[0x6A]) + 0.0000001f);
			object->MoveVector(&delta, speedScale, 1, 1, 0, 1);
		} else {
			prgObj->changeStat(0, 0, 0);
		}
		break;
	}


	case 0x1C: {
		SET_DRAW_FLAG();
		if (prgObj->m_stateFrame == 0) {
			object->CancelAnim(1);
		}
		Vec delta;
		PSVECSubtract(&m_homePosition, &object->m_worldPosition, &delta);
		float speedScale = *reinterpret_cast<float*>(mon + 0x690) *
			(0.01f * static_cast<float>(object->m_scriptHandle->m_romWork[0x6A]) + 0.0000001f);
		object->MoveVector(&delta, speedScale, 1, 1, 0, 1);
		break;
	}


	case 0x11: {
		if (prgObj->m_stateFrame == 0) {
			prgObj->reqAnim(-1, 0, 0);
		}

		unsigned char* aiData = CGMonObj_GetAiData(this);
		unsigned char* script9 = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
		float range = static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0xCE));

		int aiActionKind = *reinterpret_cast<unsigned short*>(aiData + 0x10A);
		if (aiActionKind == 2) {
			if (*reinterpret_cast<unsigned short*>(script9 + 0x10C) == 1) {
				if (prgObj->m_subState == 0) {
					unsigned int chaseFlag = 0;
					unsigned char* aiData2;
					if (m_aiState == 0) {
						aiData2 = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
					} else {
						aiData2 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(m_aiState + object->m_scriptHandle->m_romWork[0x80]) * 0x1D0 + 0x10;
					}
					if ((*reinterpret_cast<unsigned short*>(aiData2 + 0x102) & 0x10) != 0) {
						chaseFlag |= 0x8000;
					}
					CGMonObj_SetChaseMove(this, Game.m_partyObjArr[m_targetPartyIndex], chaseFlag);
					moveFrame();
					if (((m_moveWork.m_stateFlags & 1) != 0) ||
						(object->m_stateFlags0Bits.unk1 != 0)) {
						prgObj->reqAnim(-1, 0, 0);
						if (m_targetPartyIndex >= 0) {
							object->m_rotTargetY = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]));
						}
						prgObj->m_subState = 1;
					}
				}
			} else {
				if ((prgObj->m_stateFrame == 0) &&
					(m_partyDistance[m_targetPartyIndex] < range)) {
					prgObj->m_subState = 1;
				}
				if (prgObj->m_subState == 1) {
					unsigned char* script9b = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
					int frame = prgObj->m_stateFrame;
					int limit = *reinterpret_cast<unsigned short*>(script9b + 0x1B6);
					if (frame <= limit) {
						if ((object->m_stateFlags0Bits.unk1 != 0) ||
							(frame == limit) ||
							(m_partyDistance[m_targetPartyIndex] >= range)) {
							prgObj->m_subState = 0;
							object->m_rotTargetY = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]));
						} else {
							float speedScale = *reinterpret_cast<float*>(mon + 0x690) *
								(0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(script9b + 0xD4)) + 0.0000001f);
							CVector delta = CVector(object->m_worldPosition) - CVector(reinterpret_cast<CGObject*>(Game.m_partyObjArr[m_targetPartyIndex])->m_worldPosition);
							object->moveVector(delta, speedScale, 1);
						}
					}
				}
			}
		}
		if (m_attackDelay <= static_cast<int>(prgObj->m_stateFrame)) {
			prgObj->changeStat(0, 0, 0);
		}
		break;
	}


	case 0x10:
		SET_DRAW_FLAG();
		statWatch();
		break;


	case 0x1D:
		SET_DRAW_FLAG();
		statAround();
		break;


	case 0x1E: {
		CGMonObj_ChaseTarget(this);

		unsigned char* script9 = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
		float reachDist = static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0xCE));
		if ((static_cast<int>(prgObj->m_stateFrame) == *reinterpret_cast<unsigned short*>(script9 + 0x1B6)) ||
			(reachDist <= m_partyDistance[m_targetPartyIndex]) ||
			(object->m_stateFlags0Bits.unk1 != 0)) {
			prgObj->changeStat(0, 0, 0);
			if (m_targetPartyIndex >= 0) {
				object->m_rotTargetY = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]));
			}
		}
		break;
	}


	case 0x16:
		if (prgObj->m_stateFrame == 0) {
			prgObj->reqAnim(0x2C, 0, 0);
		} else if (prgObj->isLoopAnim() != 0) {
			m_unk6B9 = 0;
			prgObj->changeStat(0, 0, 0);
		}
		break;


	case 0x17:
		if (prgObj->m_stateFrame == 0) {
			prgObj->reqAnim(0x2D, 0, 0);
		} else if (prgObj->isLoopAnim() != 0) {
			m_unk6B9 = 1;
			prgObj->changeStat(0, 0, 0);
		}
		break;


	case 0x32: {
		if (prgObj->m_stateFrame == 0) {
			int classId = object->m_scriptHandle->m_baseDataIndex;
			int anim;
			unsigned int soundId;
			if ((static_cast<unsigned int>(classId) - 0x10 <= 2) || (classId == 0x5E)) {
				anim = 0xF;
				soundId = 0x2EF1;
			} else {
				anim = 0xD;
				soundId = 0xCB37;
			}
			*reinterpret_cast<float*>(mon + 0x694) = 1.0f;
			object->m_weaponNodeFlagBits.m_unk10 = 1;
			object->m_groundHitOffset.x = object->m_groundHitOffset.y = object->m_groundHitOffset.z = 0.0f;
			object->m_bgColMask |= 0x11;
			object->m_displayFlags |= 1;
			*reinterpret_cast<float*>(mon + 0x6F8) = object->unk_0x168;
			*reinterpret_cast<float*>(mon + 0x6FC) = object->unk_0x16C;
			*reinterpret_cast<float*>(mon + 0x700) = object->unk_0x170;
			object->m_worldPosition.x = *reinterpret_cast<float*>(mon + 0x6F8);
			object->m_worldPosition.y = *reinterpret_cast<float*>(mon + 0x6FC);
			object->m_worldPosition.z = *reinterpret_cast<float*>(mon + 0x700);
			prgObj->reqAnim(anim, 0, 0);
			prgObj->playSe3D(soundId, 0x32, 0x96, 0, (Vec*)0);
			if (anim == 0xF) {
				if (classId == 0x5E) {
					int dataNo = object->m_charaModelHandle->GetPdtSlot();
					prgObj->putParticle((dataNo << 8) | 8, 0, object, 1.0f, 0);
				} else {
					int dataNo = object->m_charaModelHandle->GetPdtSlot();
					prgObj->putParticle((dataNo << 8) | 7, 0, object, 1.0f, 0);
				}
			} else {
				int dataNo = object->m_charaModelHandle->GetPdtSlot();
				prgObj->putParticle((dataNo << 8) | 2, 2, object, 1.0f, 0);
			}
		}
		if (prgObj->isLoopAnim() != 0) {
			prgObj->changeStat(0, 0, 0);
			object->m_bgColMask |= 0xD0002;
			enableDamageCol(1);
			m_actionBranch = 1;
		}
		break;
	}


	case 0x33: {
		if (prgObj->m_stateFrame == 0) {
			int seId = (object->m_scriptHandle->m_baseDataIndex == 0x3C) ? 0x7937 : 0x7936;
			*reinterpret_cast<float*>(mon + 0x694) = 1.0f;
			object->m_weaponNodeFlagBits.m_unk10 = 1;
			object->m_groundHitOffset.x = object->m_groundHitOffset.y = object->m_groundHitOffset.z = 0.0f;
			object->m_bgColMask |= 0x11;
			object->m_displayFlags |= 1;
			prgObj->reqAnim(0xD, 0, 0);
			prgObj->playSe3D(seId, 0x32, 0x96, 0, (Vec*)0);
			int dataNo = object->m_charaModelHandle->GetPdtSlot();
			prgObj->putParticle((dataNo << 8) | 4, 0, object, 1.0f, 0);
		}
		if (prgObj->isLoopAnim() != 0) {
			prgObj->changeStat(0, 0, 0);
			object->m_bgColMask |= 0xD0002;
			enableDamageCol(1);
			m_actionBranch = 1;
		}
		break;
	}


	case 0x34: {
		if (prgObj->m_stateFrame == 0) {
			int soundId;
			int particleBase;
			if (object->m_scriptHandle->m_baseDataIndex == 0x39) {
				particleBase = 4;
				soundId = 0xC36E;
			} else {
				particleBase = 5;
				soundId = 0xB3D1;
			}
			object->m_weaponNodeFlagBits.m_unk10 = 1;
			object->m_groundHitOffset.x = object->m_groundHitOffset.y = object->m_groundHitOffset.z = 0.0f;
			object->m_bgColMask |= 0x11;
			object->m_displayFlags |= 1;
			prgObj->reqAnim(0xB, 0, 0);
			prgObj->playSe3D(soundId, 0x32, 0x96, 0, (Vec*)0);
			int dataNo = object->m_charaModelHandle->GetPdtSlot();
			prgObj->putParticle(particleBase | (dataNo << 8), 0, object, 1.0f, 0);
		}
		if (prgObj->isLoopAnim() != 0) {
			prgObj->changeStat(0, 0, 0);
			object->m_bgColMask |= 0xD0002;
			enableDamageCol(1);
			object->m_displayFlags |= 1;
			m_actionBranch = 1;
			object->SetAnimSlot(0, 0);
			if (object->m_scriptHandle->m_baseDataIndex == 0x39) {
				object->SetAnimSlot(1, 1);
				object->SetAnimSlot(4, 4);
				object->SetAnimSlot(6, 6);
			}
		}
		break;
	}


	case 0x35:
		if (prgObj->m_stateFrame == 0) {
			*reinterpret_cast<float*>(mon + 0x694) = 1.0f;
			object->m_displayFlags |= 1;
			float speedScale = 0.01f * static_cast<float>(object->m_scriptHandle->m_romWork[0x6A]) + 0.0000001f;
			object->moveVectorRot(object->m_rotBaseY, 0.0f, speedScale, 0x14);
		}
		if (prgObj->m_stateFrame == MON_FRAMES(0x14, 0x10)) {
			object->m_bgColMask |= 0xD0002;
			prgObj->changeStat(0, 0, 0);
		}
		break;


	case 0x36:
		if (prgObj->m_subState == 0) {
			if (prgObj->m_subFrame == 0) {
				int dataNo = object->m_charaModelHandle->GetPdtSlot();
				prgObj->putParticle((dataNo << 8) | 4, 0, object, 1.0f, 0);
				prgObj->reqAnim(0xF, 1, 0);
				unsigned int soundId = 0;
				int classId = object->m_scriptHandle->m_baseDataIndex;
				switch (classId) {
				case 0xA9:
					soundId = 0x1213A;
					break;
				case 0x9C:
				case 0xA7:
					soundId = 0x12130;
					break;
				case 0xA8:
					soundId = 0x12126;
					break;
				}
				prgObj->playSe3D(soundId, 0x32, 0x96, 0, (Vec*)0);
			}
			if (prgObj->m_subFrame == MON_FRAMES(0x3C, 0x32)) {
				prgObj->changeSubStat(1);
			}
		} else {
			if (prgObj->m_subState == 1) {
				if (prgObj->m_subFrame == 0) {
					prgObj->reqAnim(0x10, 0, 0);
				} else if (prgObj->isLoopAnim() != 0) {
					prgObj->changeStat(0, 0, 0);
				}
			}
		}
		break;

	case 0x18:
		if (prgObj->m_stateFrame == 0) {
			m_actionBranch = 1;
			prgObj->reqAnim(0x10, 0, 0);
			object->SetAnimSlot(0, 0);
			object->SetAnimSlot(4, 4);
			object->m_bgColMask = object->m_bgColMask | 0x50000;
			object->m_bgColMask = object->m_bgColMask & 0xFFFFFFF7;
			object->m_objectFlags = object->m_objectFlags & 0xFFFFFFEF;
		}
		if (prgObj->isLoopAnim() != 0) {
			prgObj->changeStat(0, 0, 0);
		}
		break;


	case 0x21:
		SET_DRAW_FLAG();
		moveFrame();
		break;

	}

	CGCharaObj::onFrameStat();
#undef prgObj
#undef object
#undef mon
#undef SET_DRAW_FLAG
}


/*
 * --INFO--
 * PAL Address: 0x80117D5C
 * PAL Size: 756b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onStatMagic()
{
#define prgObj (reinterpret_cast<CGPrgObj*>(this))
#define object (reinterpret_cast<CGObject*>(this))
#define mon (reinterpret_cast<unsigned char*>(this))
	switch (prgObj->m_subState) {
	case 0:
		if (prgObj->m_subFrame == 0) {
			int targetPartyIndex = m_targetPartyIndex;
			if (targetPartyIndex >= 0) {
				CGPartyObj* target = Game.m_partyObjArr[targetPartyIndex];
				m_comboCenter = reinterpret_cast<CGObject*>(target)->m_worldPosition;

				SCharaItemRow* rows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
				if ((rows[m_itemId].m_flags32 & 2) == 0) {
					rotTarget(m_targetPartyIndex, 0.017453292f * static_cast<float>(object->m_scriptHandle->m_romWork[0xCE]));
				}

				CGPrgObj* targetPrg = reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]);
				targetPrg->bonus(0x17, *reinterpret_cast<int*>(mon + 0x560), targetPrg);
			}

			CGCharaObj::putParticleFromItem(
				*reinterpret_cast<int*>(mon + 0x560), 0, *reinterpret_cast<int*>(mon + 0x570), (Vec*)0);
			CGCharaObj::putParticleFromItem(
				*reinterpret_cast<int*>(mon + 0x560), 1, *reinterpret_cast<int*>(mon + 0x570), (Vec*)0);
		}
		return;

	case 1:
		if (prgObj->m_subFrame > *reinterpret_cast<int*>(mon + 0x68C)) {
			prgObj->changeSubStat(2);
		}
		return;

	case 2:
		if (prgObj->isLoopAnim() != 0) {
			setAttackAfter(*reinterpret_cast<int*>(mon + 0x560));
		}
		return;
	}
#undef prgObj
#undef object
#undef mon
}

/*
 * --INFO--
 * PAL Address: 0x80117C30
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onAnimPoint(int param2, int param3)
{
#define object (reinterpret_cast<CGObject*>(this))
	int soundEffect;
	int particleId = 0xFFFF;
	int soundId = 0xFFFF;

	switch (param3) {
	case 10:
	case 11:
		particleId = object->m_scriptHandle->m_romWork[0xD2];
		if ((particleId != 0xFFFF) && (param3 == 10)) {
			particleId += 1;
		}
		soundId = SAFE_CAST_MON_WORK(object->m_scriptHandle)->m_romWork[0xD3];
		break;
	}

	if (particleId != 0xFFFF) {
		int dataNo = object->m_charaModelHandle->GetPdtSlot();
		reinterpret_cast<CGPrgObj*>(this)->putParticle(particleId | (dataNo << 8), 0, object, 1.0f, 0);
	}

	if (soundId != 0xFFFF) {
		if (soundId == 0xFFFF) {
			soundEffect = 0;
		} else {
			soundEffect = (soundId & 0xFF) + ((int)soundId >> 8) * 1000;
		}
		reinterpret_cast<CGPrgObj*>(this)->playSe3D(
			soundEffect,
			0x32,
			0x96,
			0,
			(Vec*)0
		);
	}

	CGCharaObj::onAnimPoint(param2, param3);
#undef object
}

/*
 * --INFO--
 * PAL Address: 0x80117B30
 * PAL Size: 256b
 * EN Address: 0x80116E90
 * EN Size: 256b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::enableAttackCol(int enabled, int, int)
{
	if (enabled != 0) {
		int attackKind = m_itemId;
		const SCharaItemRow* attackData = &reinterpret_cast<const SCharaItemRow*>(Game.unkCFlatData0[2])[attackKind];
		int colMask = attackData->m_particleFlags;
		int colValue = (attackKind >= 0x1F5) ? attackData->m_kind : 1;

		for (int i = 0; i < 8; i++) {
			if (((colMask >> i) & 1) != 0) {
				SetAttackColMask(i, colValue);
			}
		}
	} else {
		SetAttackColMask(-1, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80117B08
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::enableDamageCol(int enabled)
{
	if (enabled != 0) {
		m_damageColliders[0].m_hitMask = 1;
		m_damageColliders[1].m_hitMask = 1;
	} else {
		m_damageColliders[0].m_hitMask = 0;
		m_damageColliders[1].m_hitMask = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80117A18
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::getReplaceStat(int state)
{
	switch (state) {
	case 0:
	case 3:
	case 0x1C:
		if (m_lastStateId == state) {
			state = -1;
		}
		break;
	case -0xE:
	case -0xD:
	case -0xC:
	case -0xB:
	case -0xA:
	case -9:
	case -8:
	case -7:
	case -6:
	case -5:
		{
			CMonWork* work = SAFE_CAST_MON_WORK(m_scriptHandle);
			int index = state + 0xE;
			int action = work->m_actionItems[index];
			const SCharaItemRow* items = reinterpret_cast<const SCharaItemRow*>(Game.unkCFlatData0[2]);
			switch (items[action].m_actionType) {
			case 0:
			case 1:
				state = 1;
				break;
			case 2:
				state = 2;
				break;
			case 3:
				state = 0x12;
				break;
			case 4:
				state = 8;
				break;
			}
		}
		break;
	default:
		return CGCharaObj::getReplaceStat(state);
	}

	return state;
}

/*
 * --INFO--
 * PAL Address: 0x801179BC
 * PAL Size: 92b
 * EN Address: 0x80116D1C
 * EN Size: 92b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onStatShield()
{
	if (m_subState == 1) {
		SCharaItemRow* rows = reinterpret_cast<SCharaItemRow*>(Game.unkCFlatData0[2]);
		if (m_subFrame == rows[m_itemId].m_power) {
			changeSubStat(3);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80117690
 * PAL Size: 812b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onStatDie()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	int subState = *reinterpret_cast<int*>(mon + 0x52C);

	switch (subState) {
	case 0:
		if (*reinterpret_cast<int*>(mon + 0x530) == 0) {
			unsigned char* aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
			reinterpret_cast<CGPrgObj*>(this)->playSe3D(
				*reinterpret_cast<unsigned short*>(aiData + 0x190) * 1000 + *reinterpret_cast<unsigned short*>(aiData + 0x192) + 9,
				0x32,
				0x96,
				0,
				(Vec*)0
			);

			int pId = object->m_scriptHandle->m_romWork[0xCF];
			if (pId != 0xFFFF) {
				int dataNo = -1;
				dataNo = object->m_charaModelHandle->GetPdtSlot();
				reinterpret_cast<CGPrgObj*>(this)->putParticle(pId | (dataNo << 8), 0, object, 0.1f * object->m_attackColRadius, 0);
			}

			int option = *reinterpret_cast<short*>(&Game.m_gameWork.m_optionValue);
			if (option < 9 && m_repop.delay == 0) {
				CFlat.m_spawnBits[option] |= 1ULL << object->m_scriptHandle->m_saveSlot;
			}
			return;
		}

		if (reinterpret_cast<CGPrgObj*>(this)->isLoopAnimDirect() != 0) {
			reinterpret_cast<CGPrgObj*>(this)->changeSubStat(1);
		}
		return;

	case 1: {
		unsigned char* aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
#define subFrame (*reinterpret_cast<int*>(mon + 0x530))

		if ((*reinterpret_cast<unsigned short*>(aiData + 0xFE) & 2) == 0) {
			goto deathElse;
		}
		if (subFrame == 0) {
			int classId = object->m_scriptHandle->m_baseDataIndex;
			int particleId;
			switch (classId) {
			case 4:
				particleId = 0x253;
				break;
			case 5:
				particleId = 599;
				break;
			case 6:
				particleId = 0x25B;
				break;
			}

			*reinterpret_cast<int*>(mon + 0x560) = particleId;
			CGCharaObj::putParticleFromItem(*reinterpret_cast<int*>(mon + 0x560), 0, *reinterpret_cast<int*>(mon + 0x564), (Vec*)0);
			CGCharaObj::putParticleFromItem(*reinterpret_cast<int*>(mon + 0x560), 1, *reinterpret_cast<int*>(mon + 0x564), (Vec*)0);
			CGCharaObj::putParticleFromItem(*reinterpret_cast<int*>(mon + 0x560), 2, *reinterpret_cast<int*>(mon + 0x564), (Vec*)0);
			CGCharaObj::putParticleFromItem(*reinterpret_cast<int*>(mon + 0x560), 3, *reinterpret_cast<int*>(mon + 0x564), (Vec*)0);
			return;
		}
		if (subFrame != MON_FRAMES(0x1E, 0x19)) {
			return;
		}

	deathCleanup:
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x231000);
		*reinterpret_cast<float*>(mon + 0x694) = 0.0f;
		enableAttackCol(0, 0, 0);
		object->m_bgColMask &= 0xFFF6FFFD;
		reinterpret_cast<CGPrgObj*>(this)->playSe3D(0x17, 0x32, 0x96, 0, (Vec*)0);
		reinterpret_cast<CGPrgObj*>(this)->putParticle(0x116, 0, object, 0.1f * object->m_attackColRadius, 0);
		CGItemObj::CreateFromScript(1, 0, 0, object, 0.0f, 0);
		object->PutDropItem();
		reinterpret_cast<CGPrgObj*>(this)->changeSubStat(2);
		return;

	deathElse:
		if (subFrame == 0) {
			goto deathCleanup;
		}
		return;
#undef subFrame
	}

	case 2: {
		unsigned short repopDelay = m_repop.delay;
		if ((repopDelay != 0) && (*reinterpret_cast<int*>(mon + 0x530) == static_cast<int>(repopDelay) * 0x1E)) {
			setRepop(0);
		}
		return;
	}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011740C
 * PAL Size: 644b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onDrawDebug(CFont* font, float posX, float& posY, float posZ)
{
	CGCharaObj* charaObj = reinterpret_cast<CGCharaObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	charaObj->CGCharaObj::onDrawDebug(font, posX, posY, posZ);

	if ((static_cast<signed char>((static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags)) << 24) & 0xC0000000) >> 31)) != 0) &&
			(static_cast<int>(CFlatCenterState()) == 0) &&
		((DbgMenuPcs.GetDbgFlagsRaw() & 0x80) != 0)) {
		char text[0x100];
		int aiMasked = m_groupTag & 0x7FFF;
		sprintf(text, "%d %c %d %c", object->m_scriptHandle->m_saveSlot,
		        aiMasked == 0 ? '-' : aiMasked + 0x40,
		        m_chaseState, m_targetPartyIndex >= 0 ? m_targetPartyIndex + '0' : '-');
		font->SetPos(posX - font->GetWidth(text) * 0.5f, posY, posZ);
		font->Draw(text);
		posY -= font->GetHeight();

		int targetDist;
		if (m_targetPartyIndex >= 0) {
			targetDist = static_cast<int>(m_partyDistance[m_targetPartyIndex]);
		} else {
			targetDist = 0;
		}

		int chaseRange = static_cast<int>(static_cast<float>(object->m_scriptHandle->m_romWork[0x66]));
		int spawnDist = static_cast<int>(PSVECDistance(&m_homePosition, &object->m_worldPosition));
		sprintf(text, "%d %d/%d", targetDist, spawnDist, chaseRange);
		font->SetPos(posX - font->GetWidth(text) * 0.5f, posY, posZ);
		font->Draw(text);
		posY -= font->GetHeight();
	}
}

/*
 * --INFO--
 * PAL Address: 0x801173B4
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onAttacked(CGPrgObj*)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	m_unk6C0 = 1;

	if (m_funcs->attacked != 0) {
		(this->*m_funcs->attacked)();
	}
}

/*
 * --INFO--
 * PAL Address: 0x801170E0
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onDamaged(CGPrgObj* prgObj)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	m_unk6BF = 1;

	unsigned short prgFlags = static_cast<unsigned short>(prgObj->GetCID());
	if ((prgFlags & 0x6D) == 0x6D) {
		unsigned char* aiData;
		if (m_aiState == 0) {
			aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
		} else {
			aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
				(m_aiState +
					object->m_scriptHandle->m_romWork[0x80]) * 0x1D0 + 0x10;
		}

		int attackerIndex = SAFE_CAST_CARAVAN_WORK(prgObj->m_scriptHandle)->m_joybusCaravanId;
		if ((static_cast<int>(*reinterpret_cast<unsigned short*>(aiData + 0x106)) == 1) || (m_targetPartyIndex < 0)) {
			if ((static_cast<unsigned int>(Game.m_gameWork.m_menuStageMode) != 0) && (Game.m_gameWork.m_bossArtifactStageIndex < 0xF)) {
				prgFlags = static_cast<unsigned short>(prgObj->GetCID());
				if ((prgFlags & 0x6D) == 0x6D) {
					if (SAFE_CAST_CARAVAN_WORK(prgObj->m_scriptHandle)->m_joybusCaravanId != 0) {
						goto skip_target_update;
					}
				}
			}
			m_targetPartyIndex = attackerIndex;
		}

skip_target_update:
		int teamNo = object->m_scriptHandle->m_saveSlot;
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(prgObj) + 0x6C0) = teamNo;
		GbaQue.SetHitEnemy(SAFE_CAST_CARAVAN_WORK(prgObj->m_scriptHandle)->m_joybusCaravanId, teamNo);

		unsigned short groupTag = m_groupTag;
		if ((groupTag & 0x7FFF) != 0) {
			for (CGMonObj* other = CFlat.FindGMonObjFirst(); other != nullptr;
				other = CFlat.FindGMonObjNext(other)) {
				if (other == this) {
					continue;
				}

				if ((other->m_groupTag & 0x7FFF) == 0) {
					continue;
				}
				if ((groupTag & 0x7FFF) != (other->m_groupTag & 0x7FFF)) {
					continue;
				}

				link(reinterpret_cast<CGPartyObj*>(prgObj), other);
			}
		}
	}

	if (*reinterpret_cast<int*>(mon + 0x520) == 0x11) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0, 0, 0);
	}

	int classId = object->m_scriptHandle->m_baseDataIndex;
	if ((m_actionBranch == 0) && (classId == 0x55)) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0x18, 0, 0);
	}

	mlSet(2);

	if (m_funcs->damaged != 0) {
		(this->*m_funcs->damaged)();
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 312b
 * EN Address: 0x80135BE4
 * EN Size: 236b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::link(CGPartyObj* party, CGMonObj* other)
{
	CGObjWork* otherScript = other->m_scriptHandle;
	if (otherScript->m_hp == 0) {
		return;
	}
	if (otherScript->m_statusTimers[0] != 0) {
		return;
	}
	if (otherScript->m_statusTimers[9] != 0) {
		return;
	}
	if (otherScript->m_statusTimers[3] != 0) {
		return;
	}

	other->m_targetPartyIndex = SAFE_CAST_CARAVAN_WORK(party->m_scriptHandle)->m_joybusCaravanId;
	other->m_unk6BD = 1;

	int otherClassId = other->m_scriptHandle->m_baseDataIndex;
	if (other->m_chaseState != 4) {
		other->mlSet(2);
	} else if ((other->m_actionBranch == 0) && (otherClassId == 0x55)) {
		other->changeStat(0x18, 0, 0);
		other->mlSet(2);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80117090
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::aiTarget()
{
	int partyIndex = getNearParty(0, 7, 0.0f, INFINITY, -1);
	if (partyIndex >= 0) {
		m_targetPartyIndex = partyIndex;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80117044
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::aiTargetAttackRomMon(int classId)
{
	int partyIndex = getNearParty(-1, 0x47, 0.0f, 0.0f, classId);
	if (partyIndex >= 0) {
		m_targetPartyIndex = partyIndex;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80116870
 * PAL Size: 2004b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::checkCol(int flags, float rotY, float distance, float* hitScale, int* hitPartyIndex)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	if (hitScale != NULL) {
		*hitScale = 1.0f;
	}
	if (hitPartyIndex != NULL) {
		*hitPartyIndex = -1;
	}

	CVector startPos;
	CVector forward;
	CVector move;
	startPos = CVector(object->m_worldPosition.x, object->m_worldPosition.y, object->m_worldPosition.z);
	float sinY = static_cast<float>(sin(static_cast<double>(rotY)));
	float cosY = static_cast<float>(cos(static_cast<double>(rotY)));
	forward = CVector(sinY, 0.0f, cosY);
	move = forward * distance;

	unsigned short aiFlags = *reinterpret_cast<unsigned short*>(CGMonObj_GetAiData(this) + 0x102);
	if ((m_bind != 0) &&
		(((m_chaseState == 4) && ((aiFlags & 8) == 0)) ||
		 ((m_chaseState != 4) && ((aiFlags & 4) == 0)))) {
		unsigned char* bind = m_bind;
		unsigned char* modelData = *reinterpret_cast<unsigned char**>(
			reinterpret_cast<unsigned char*>(object->m_charaModelHandle) + 0x168);
		Mtx bindMtx;
		PSMTXCopy(*reinterpret_cast<Mtx*>(bind + 0x6C), bindMtx);
		bindMtx[0][3] = bindMtx[0][3] + *reinterpret_cast<float*>(modelData + 0x74);
		bindMtx[1][3] = bindMtx[1][3] + *reinterpret_cast<float*>(modelData + 0x84);
		bindMtx[2][3] = bindMtx[2][3] + *reinterpret_cast<float*>(modelData + 0x94);
		startPos.x = bindMtx[0][3];
		startPos.y = bindMtx[1][3];
		startPos.z = bindMtx[2][3];

		PSMTXMultVecSR(bindMtx, CVector(1.0f, 0.0f, 0.0f), reinterpret_cast<Vec*>(&forward));
		forward.y = 0.0f;
		forward.Normalize();
		move = forward * distance;
	}

	if ((flags & 1) != 0) {
		unsigned short cylHitArg = object->m_scriptHandle->m_romWork[0xD9];
		float cylRadius = 0.5f * object->m_bodyEllipsoidRadius;
		int hit = MapPcs.CheckHitCylinderNear(startPos, move, cylRadius, cylHitArg);
		if (hit != 0) {
			float hitT = MapPcs.GetHitT();
			if (hitScale != NULL) {
				*hitScale = hitT;
			}
			PSVECScale(reinterpret_cast<Vec*>(&move), reinterpret_cast<Vec*>(&move), hitT);
			distance = distance * hitT;
		}
		CFlat.AddDebugDrawCC(reinterpret_cast<Vec*>(&startPos), reinterpret_cast<Vec*>(&move), cylRadius, 1, hit);
	}

	if ((flags & 2) != 0) {
		float halfAngle = 0.5f * (0.017453292f *
			static_cast<float>(object->m_scriptHandle->m_romWork[0x65]));
		float sideDist;
		if (0.0f == halfAngle) {
			sideDist = 0.0f;
		} else {
			sideDist = 20.0f / static_cast<float>(tan(static_cast<double>(halfAngle)));
		}

		CVector coneStart = startPos;
		coneStart -= forward * sideDist;

		float coneLength = distance + sideDist;
		move += forward * sideDist;

		int didHit = 0;
		for (int rank = 0; rank < 4; rank++) {
			if (((flags & 4) != 0) && (((m_updateCounter + rank) % 4) != 0)) {
				continue;
			}

			int partyIndex = m_partyRank[rank];
			CGPartyObj* partyObj = Game.m_partyObjArr[partyIndex];
			if (partyObj == NULL) {
				continue;
			}

			if (((Game.m_gameWork.m_menuStageMode != 0) &&
				 (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) &&
				 partyObj->IsKindOf(0x6D) &&
				 (reinterpret_cast<CCaravanWork*>(partyObj->m_scriptHandle)->m_joybusCaravanId != 0)) ||
				(reinterpret_cast<CCaravanWork*>(partyObj->m_scriptHandle)->m_hp == 0) ||
				(partyObj->m_lastStateId == 9) ||
				(partyObj->m_lastStateId == 0x22) ||
				((Game.m_gameWork.m_menuStageMode != 0) &&
				 (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) &&
				 partyObj->IsKindOf(0x6D) &&
				 (reinterpret_cast<CCaravanWork*>(partyObj->m_scriptHandle)->m_joybusCaravanId != 0)) ||
				!(m_partyDistance[partyIndex] <
				 (coneLength - sideDist))) {
				continue;
			}

			CVector partyPos = CVector(partyObj->m_worldPosition.x,
				partyObj->m_worldPosition.y + partyObj->unk_0x184, partyObj->m_worldPosition.z);
			CVector targetDelta = partyPos - coneStart;
			float targetDist = PSVECMag(targetDelta);
			if (!(0.0f < targetDist)) {
				continue;
			}

			CVector targetDir;
			PSVECNormalize(targetDelta, targetDir);
			float dot = PSVECDotProduct(reinterpret_cast<Vec*>(&forward), reinterpret_cast<Vec*>(&targetDir));
			if (!((sideDist - object->m_bodyEllipsoidRadius) <= targetDist) ||
				((halfAngle != 0.0f) &&
				 !(0.0f < dot))) {
				continue;
			}

			float angle = static_cast<float>(acos(static_cast<double>(dot)));
			if ((halfAngle != 0.0f) &&
				!(angle < halfAngle)) {
				continue;
			}

			didHit = 1;
			float cylRadius = 0.5f * object->m_bodyEllipsoidRadius;
			unsigned short hitMask = object->m_scriptHandle->m_romWork[0xD9];
			int mapHit = MapPcs.CheckHitCylinderNear(startPos, partyPos - startPos, cylRadius, hitMask);
			CVector debugDelta = targetDelta;
			if (mapHit != 0) {
				PSVECScale(debugDelta, debugDelta, MapPcs.GetHitT());
			}
			CFlat.AddDebugDrawCC(startPos, debugDelta, cylRadius, 1, mapHit == 0);

			if (mapHit == 0) {
				if (hitPartyIndex != NULL) {
					*hitPartyIndex = reinterpret_cast<CCaravanWork*>(partyObj->m_scriptHandle)->m_joybusCaravanId;
				}
				break;
			}
		}

		if (halfAngle != 0.0f) {
			float debugRadius = coneLength * static_cast<float>(tan(static_cast<double>(halfAngle)));
			CFlat.AddDebugDrawCC(coneStart, move, debugRadius, 0, didHit);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80116654
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::mlHide()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	if (m_unk6BE != 0) {
		return;
	}

	int notice = false;
	int partyIndex;

	if (m_unk6BD != 0) {
		partyIndex = m_targetPartyIndex;
	} else {
		partyIndex = CGMonObj_SearchNoticeParty(this);
	}

	if (partyIndex >= 0) {
		CGObject* object = reinterpret_cast<CGObject*>(this);
		int action = m_actionBranch;
		unsigned short noticeFlags = object->m_scriptHandle->m_romWork[0x7F];
		int monClass = object->m_scriptHandle->m_baseDataIndex;

		if ((action == 0) && ((noticeFlags & 0x80) != 0)) {
			notice = true;
			CGMonObj::m_aiWork.m_state = 0x32;
		} else if ((action == 0) && ((noticeFlags & 0x20) != 0)) {
			notice = true;
			CGMonObj::m_aiWork.m_state = 0x33;
		} else if ((action == 0) && (((noticeFlags & 0x40) != 0) || (monClass == 0x39))) {
			notice = true;
			CGMonObj::m_aiWork.m_state = 0x34;
		}
	}

	int classId = (*reinterpret_cast<int**>(mon + 0x58))[4];
	switch (classId) {
	case 0x6A:
		notice = true;
		CGMonObj::m_aiWork.m_state = 0x35;
		break;
	case 0x70:
	case 0x7B:
		notice = true;
		break;
	}

	if (notice) {
#ifndef VERSION_GCCJGC
		if (classId == 0x7B) {
			mlSet(0);
		} else
#endif
		if (m_unk6BD != 0) {
			mlSet(2);
		} else {
			mlSet(2);
		}

		m_targetPartyIndex = partyIndex;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlEscape()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
#define script9 (reinterpret_cast<unsigned char*>(m_scriptHandle->m_romWork))
	float maxDist = static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0xCC));
	float homeDist = PSVECDistance(&m_homePosition, reinterpret_cast<Vec*>(mon + 0x15C));
	unsigned char* aiData;

	short aiState = m_aiState;
	if (aiState == 0) {
		aiData = script9;
	} else {
		aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
		         (aiState + *reinterpret_cast<unsigned short*>(script9 + 0x100)) *
		             0x1D0 +
		         0x10;
	}

	unsigned short aiFlags = *reinterpret_cast<unsigned short*>(aiData + 0x102);
	if ((m_targetPartyIndex >= 0) &&
	    ((aiFlags & 0x20) != 0)) {
		moveCancel();
		mlSet(2);
		return;
	}

	if (((aiFlags & 0x20) != 0) ||
	    ((*reinterpret_cast<unsigned short*>(script9 + 0xFE) & 8) != 0)) {
		moveCancel();
		mlSet(0);
		return;
	}

	if (*reinterpret_cast<unsigned short*>(script9 + 0x10C) == 1) {
		CGMonObj::m_aiWork.m_state = 0x21;
		if (m_moveWork.m_mode != 3) {
			m_moveWork.Clear();
			m_moveWork.m_flags = 0x806;
			m_moveWork.m_mode = 3;
		}
		m_moveWork.m_targetPos = m_homePosition;
	}

	CGObjWork* handle = m_scriptHandle;
	if (((handle->m_romWork[0x86] != 1) || (m_moveWork.m_frame < MON_FRAMES(0x1E, 0x19))) &&
	    ((SAFE_CAST_MON_WORK(handle)->m_romWork[0x86] == 1) || !(homeDist < 0.5f * maxDist))) {
		goto check_home;
	}

	{
		int partyIndex = CGMonObj_SearchNoticeParty(this);

		if (partyIndex >= 0) {
			m_targetPartyIndex = partyIndex;
			if (*reinterpret_cast<unsigned short*>(script9 + 0x10C) == 1) {
				mlSet(2);
			} else {
				mlSet(1);
			}
			return;
		}
	}

check_home:
	if ((homeDist < 10.0f) ||
	    (m_chaseTimer == static_cast<int>(*reinterpret_cast<unsigned short*>(script9 + 0x1B8)))) {
		m_homePosition = *reinterpret_cast<Vec*>(mon + 0x15C);
		moveCancel();
		mlSet(0);
	} else if (*reinterpret_cast<unsigned short*>(script9 + 0x10C) != 1) {
		CGMonObj::m_aiWork.m_state = 0x1C;
	}
#undef script9
}

/*
 * --INFO--
 * PAL Address: 0x801162B4
 * PAL Size: 60b
 * EN Address: 0x80115614
 * EN Size: 60b
 * JP Address: 0x8011228C
 * JP Size: 60b
 */
void CGMonObj::moveCancel()
{
	CGMonObj::m_aiWork.m_state = 0;
	m_moveWork.Clear();
}

/*
 * --INFO--
 * PAL Address: 0x80115C00
 * PAL Size: 1716b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::mlMove()
{
	CGMonObj* monObj = this;
	unsigned char* mon = reinterpret_cast<unsigned char*>(monObj);
	CGObject* object = reinterpret_cast<CGObject*>(monObj);
	int& targetPartyIndex = monObj->m_targetPartyIndex;
#define actionState (CGMonObj::m_aiWork.m_state)
#define script (reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork))

	if (targetPartyIndex >= 0) {
		float homeRange = static_cast<float>(*reinterpret_cast<unsigned short*>(script + 0xCC));
		float homeDist = PSVECDistance(&monObj->m_homePosition, &object->m_worldPosition);
		if (!(homeRange <= homeDist)) {
			goto body;
		}
	}

	targetPartyIndex = -1;
	monObj->moveCancel();
	monObj->mlSet(3);
	return;

body:
	{
			if (monObj->m_unk6BD != 0) {
				float reacquireRange = static_cast<float>(*reinterpret_cast<unsigned short*>(script + 0xC8));
				int hitPartyIndex;
				monObj->checkCol(6, object->m_rotBaseY, reacquireRange, (float*)NULL, &hitPartyIndex);
				if (hitPartyIndex >= 0) {
					targetPartyIndex = hitPartyIndex;
					monObj->m_unk6BD = 0;
				}
			}

			int nextAction = monObj->mlAttackCheck(targetPartyIndex);
			if (nextAction == -2) {
				monObj->moveCancel();
				monObj->mlSet(0);
				return;
			}
			if (nextAction == -1) {
				CGObjWork* handle = object->m_scriptHandle;
				unsigned char* scriptB = reinterpret_cast<unsigned char*>(handle->m_romWork);
				if (*reinterpret_cast<unsigned short*>(scriptB + 0x10C) == 1) {
					unsigned char* aiScript;
					short aiState = monObj->m_aiState;
					if (aiState == 0) {
						aiScript = scriptB;
					} else {
						aiScript = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(static_cast<int>(aiState) + *reinterpret_cast<unsigned short*>(scriptB + 0x100)) * 0x1D0 + 0x10;
					}
					unsigned short aiFlags = *reinterpret_cast<unsigned short*>(aiScript + 0x102);
					if (((SAFE_CAST_MON_WORK(handle)->m_romWork[0x7F] & 8) != 0) ||
						((aiFlags & 0x100) != 0)) {
						monObj->moveCancel();
						monObj->mlSet(2);
						return;
					}

					CGPartyObj* target = Game.m_partyObjArr[targetPartyIndex];
					actionState = 0x21;
					if (monObj->m_moveWork.m_mode != 1) {
						monObj->m_moveWork.Clear();
						monObj->m_moveWork.m_flags = 0x205;
						short aiState2 = monObj->m_aiState;
						if (aiState2 == 0) {
							aiScript = script;
						} else {
							aiScript = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
								(static_cast<int>(aiState2) + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
						}
						if ((*reinterpret_cast<unsigned short*>(aiScript + 0x102) & 0x40) != 0) {
							monObj->m_moveWork.m_flags |= 0x10000;
						}
						monObj->m_moveWork.m_mode = 1;
					}
					monObj->m_moveWork.m_target = target;
					if (((monObj->m_moveWork.m_stateFlags & 1) != 0) ||
						(monObj->m_moveWork.m_frame >=
						 static_cast<int>(*reinterpret_cast<unsigned short*>(script + 0x1BA)))) {
						monObj->moveCancel();
						monObj->mlSet(3);
					}
					return;
				}

				if (monObj->m_chaseTimer >=
					static_cast<int>(*reinterpret_cast<unsigned short*>(script + 0x1BA))) {
					monObj->mlSet(3);
					return;
				}
				actionState = 3;
				return;
			}

			CGObjWork* handleB = object->m_scriptHandle;
			unsigned char* scriptC = reinterpret_cast<unsigned char*>(handleB->m_romWork);
			if (*reinterpret_cast<unsigned short*>(scriptC + 0x10C) == 1) {
				if (nextAction >= 100) {
					actionState = nextAction;
				} else {
					short aiState = monObj->m_aiState;
					if ((reinterpret_cast<CMonAiAction*>(CGMonObj_GetAiData(monObj) + 0x110)[nextAction].m_flags & 0x20) != 0) {
						CGPartyObj* target = Game.m_partyObjArr[targetPartyIndex];
						actionState = 0x21;
						monObj->moveChase(target);
						monObj->mlSet(5);
						return;
					}

					unsigned char* aiScript3;
					if (aiState == 0) {
						aiScript3 = reinterpret_cast<unsigned char*>(SAFE_CAST_MON_WORK(handleB)->m_romWork);
					} else {
						aiScript3 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(aiState + SAFE_CAST_MON_WORK(handleB)->m_romWork[0x80]) * 0x1D0 + 0x10;
					}
					float actionRange = static_cast<float>(reinterpret_cast<CMonAiAction*>(aiScript3 + 0x110)[nextAction].m_range);
					unsigned char* aiScript4;
					if (aiState == 0) {
						aiScript4 = reinterpret_cast<unsigned char*>(SAFE_CAST_MON_WORK(handleB)->m_romWork);
					} else {
						aiScript4 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(aiState + SAFE_CAST_MON_WORK(handleB)->m_romWork[0x80]) * 0x1D0 + 0x10;
					}
					int actionParam = static_cast<short>(reinterpret_cast<CMonAiAction*>(aiScript4 + 0x110)[nextAction].m_changeStat);
					CGPartyObj* target = Game.m_partyObjArr[targetPartyIndex];
					actionState = 0x21;
					CGMonObj_SetAttackMove(monObj, target, actionRange, actionParam);
				}
			} else {
				actionState = nextAction - 0xE;
			}
			monObj->mlSet(1);
			return;
	}
#undef script
#undef actionState
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 24b
 * EN Address: 0x8013659C
 * EN Size: 24b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::mlSet(int state)
{
	m_chaseState = state;
	m_chaseTimer = 0;
	m_chaseDirty = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlWaitingCheck()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlAway()
{
	// TODO
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlWaiting()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlEscapeCheck()
{
	// TODO
}


/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::resetWork()
{
	m_targetPartyIndex = -1;
	m_aiState = 0;
	m_aiStatePrev = 0;
	m_unk6C8 = 0;
	m_unk6CC = 0;
	m_actionBranch = 0;
	m_unk6B8 = 0;
	m_unk6B9 = 0;
	m_unk6BA = 0;
	m_unk6BC = 0;
	m_unk6BD = 0;
	m_unk6BE = 0;
	m_attackDelay = 0;
	m_aliveFrames = 0;
	m_unk6BF = 0;
	m_unk6C0 = 0;
	m_unk6C2 = 0;
	m_unk6C3 = 0;
	m_chaseState = 0;
	m_chaseTimer = 0;
	m_chaseDirty = 0;
	m_stepSeHandle = 0;
	m_moveWork.Clear();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::moveChase(CGCharaObj* target)
{
	if (m_moveWork.m_mode != 4) {
		m_moveWork.Clear();
		m_moveWork.m_flags = 0x855;
		if ((SAFE_CAST_MON_WORK(m_scriptHandle)->m_romWork[0x7F] & 4) != 0) {
			m_moveWork.m_flags |= 0x400;
		}
		if ((*reinterpret_cast<unsigned short*>(CGMonObj_GetAiData(this) + 0x102) & 0x80) != 0) {
			m_moveWork.m_flags |= 0x20000;
		}
		m_moveWork.SetFlags(0, 0);
		m_moveWork.m_mode = 4;
		m_moveWork.m_range = static_cast<float>(SAFE_CAST_MON_WORK(m_scriptHandle)->m_romWork[0x6B]);
		m_moveWork.m_limitFrame = SAFE_CAST_MON_WORK(m_scriptHandle)->m_romWork[0xDB];
	}
	m_moveWork.m_target = target;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveEscape()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveAway(CGCharaObj*, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveChaseAndStat(CGCharaObj*, int, float, int, int)
{
	// TODO
}


/*
 * --INFO--
 * PAL Address: 0x8011467C
 * PAL Size: 1272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
/*
 * --INFO--
 * PAL Address: 0x8011548C
 * PAL Size: 1908b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */

int CGMonObj::mlAttackCheck(int partyIndex)
{
	CGMonObj* monObj = this;
	unsigned char* mon = reinterpret_cast<unsigned char*>(monObj);
	CGObject* object = reinterpret_cast<CGObject*>(monObj);
#define baseScript (reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork))
#define aiScript (monObj->m_aiState == 0 \
		? baseScript \
		: reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) + \
			(monObj->m_aiState + *reinterpret_cast<unsigned short*>(baseScript + 0x100)) * 0x1D0 + 0x10)
#define aiScriptW (monObj->m_aiState == 0 		? reinterpret_cast<unsigned char*>(SAFE_CAST_MON_WORK(object->m_scriptHandle)->m_romWork) 		: reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) + 			(monObj->m_aiState + SAFE_CAST_MON_WORK(object->m_scriptHandle)->m_romWork[0x80]) * 0x1D0 + 0x10)
	int selectedAction = -1;
	if (monObj->m_funcs->attackCheck != 0) {
		int result = (monObj->*monObj->m_funcs->attackCheck)(partyIndex);
		if (result == -2) {
			return -1;
		}
		if (result != -1) {
			return result;
		}
	}

	float targetDist = monObj->m_partyDistance[partyIndex];

	int selectorType = *reinterpret_cast<unsigned short*>(aiScript + 0x108);
	if (selectorType == 0xFFFF) {
		return -1;
	}

	int groupTable[8] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};
	int groupCount[8] = {0, 0, 0, 0, 0, 0, 0, 0};

	for (int actionIndex = 0; actionIndex < 8; actionIndex++) {
		int actionOffset = actionIndex * 0x10;
		int actionFlags = *reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x110);
		if (actionFlags == 0xFFFF) {
			if (actionIndex == 0) {
				return -2;
			}
			continue;
		}

		int actionType;
		if (*reinterpret_cast<unsigned short*>(baseScript + 0x10C) == 1) {
			actionType = actionFlags & 3;
		} else {
			actionType = *reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x118);
		}

		if ((actionType == 3) && (Game.m_gameWork.m_menuStageMode != 0)) {
			continue;
		}

		int artifactLevel;
		if (Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			int idx = Game.m_gameWork.m_bossArtifactStageIndex;
			int stage = Game.m_gameWork.m_bossArtifactStageTable[idx];
			artifactLevel = stage < 2 ? stage : 2;
		} else {
			artifactLevel = 0;
		}

		if (((actionType == 1) && (artifactLevel <= 0)) ||
			((actionType == 2) && (artifactLevel <= 1))) {
			continue;
		}

		if ((actionFlags & 0x40) != 0) {
			float targetRot = monObj->m_partyAngle[partyIndex];
			float baseRot =
				0.017453292f * static_cast<float>(*reinterpret_cast<unsigned short*>(aiScriptW + actionOffset + 0x118)) +
				object->m_rotBaseY;
			float angleDelta = (float)__fabs(Math.DstRot(targetRot, baseRot));
			System.Printf("ACT_FLAG_ROT_CHECK 差分=%f度。\n", 57.29578f * angleDelta);
			float angleLimit =
				0.017453292f * static_cast<float>(*reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x11A));
			if (!(angleDelta < angleLimit)) {
				continue;
			}
			System.Printf("\x92\xca\x89\xdf\x81\x42\n");
		}

		if (selectorType == 0) {
			int maxDistRaw = *reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x114);
			float minDist = static_cast<float>(static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x112)));
			unsigned int chance = *reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x116);

			if ((targetDist < static_cast<float>(maxDistRaw)) && (minDist < targetDist)) {

			int forceAction = 0;
			CGPartyObj* party = Game.m_partyObjArr[partyIndex];
			int partyState = reinterpret_cast<CGPrgObj*>(party)->m_lastStateId;
			if (((partyState == 1) || (partyState == 7)) &&
				((float)__fabs(Math.DstRot(object->m_rotBaseY, reinterpret_cast<CGObject*>(party)->m_rotBaseY)) > 1.5707964f)) {
				if (((*reinterpret_cast<unsigned short*>(baseScript + 0x10C) == 1) &&
						(monObj->m_forcedAction ==
							static_cast<short>(*reinterpret_cast<unsigned short*>(aiScriptW + actionOffset + 0x11E)))) ||
					((SAFE_CAST_MON_WORK(object->m_scriptHandle)->m_romWork[0x86] != 1) &&
						(monObj->m_forcedAction == actionIndex))) {
					forceAction = 1;
				}
			}

			if (forceAction || (Math.Rand(100) <= chance)) {
				selectedAction = actionIndex;
				if (*reinterpret_cast<unsigned short*>(baseScript + 0x10C) == 1) {
					break;
				}
				if (forceAction) {
					break;
				}
			}
			}
		} else {
			unsigned int groupIndex;
			if (*reinterpret_cast<unsigned short*>(baseScript + 0x10C) == 1) {
				groupIndex = (actionFlags >> 2) & 7;
			} else {
				groupIndex = *reinterpret_cast<unsigned short*>(aiScriptW + actionOffset + 0x11A);
			}

			groupTable[actionIndex] = groupIndex;
			groupCount[groupIndex] += 1;
		}
	}

	if (selectorType == 1) {
		int count;
		for (;;) {
			int cursor = monObj->m_unk6CC;
			count = groupCount[cursor];
			if (count != 0) {
				break;
			}
			monObj->m_unk6CC = cursor + 1;
			if (monObj->m_unk6CC >= 8) {
				monObj->m_unk6CC = 0;
			}
		}

		int pick = Math.Rand(count);
		int seen = 0;
		for (int i = 0; i < 8; i++) {
			if (monObj->m_unk6CC == groupTable[i]) {
				if (seen == pick) {
					selectedAction = i;
					monObj->m_unk6CC++;
					break;
				}
				seen++;
			}
		}
	}

	return selectedAction;
#undef aiScript
#undef aiScriptW
#undef baseScript
}

/*
 * --INFO--
 * PAL Address: 0x80114B74
 * PAL Size: 2328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::mlAttack()
{
	CGMonObj* monObj = this;
#define mon (reinterpret_cast<unsigned char*>(monObj))
#define object (reinterpret_cast<CGObject*>(monObj))
	int& targetPartyIndex = monObj->m_targetPartyIndex;
	int& chaseState = monObj->m_chaseState;
	int& chaseTimer = monObj->m_chaseTimer;
#define actionState (CGMonObj::m_aiWork.m_state)
#define script (reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork))

	if (reinterpret_cast<CGPrgObj*>(monObj)->m_lastStateId == 0) {
		monObj->m_unk6BD = 0;
		float homeRange = static_cast<float>(*reinterpret_cast<unsigned short*>(script + 0xCC));
		float homeDist = PSVECDistance(&monObj->m_homePosition, &object->m_worldPosition);
		if (homeRange <= homeDist) {
			monObj->moveCancel();
			chaseState = 3;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
			return;
		}

		int targetMode = *reinterpret_cast<unsigned short*>(CGMonObj_GetAiData(monObj) + 0x106);
		if (targetMode == 0xFFFF) {
			chaseState = 0;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
			return;
		}

		int selectedTarget = -1;

		if (targetMode >= 10) {
			selectedTarget = (monObj->*monObj->m_funcs->target)(targetMode);
		} else {
			int slot;
			int validCount = 0;
			for (slot = 0; slot < 4; slot++) {
				CGPartyObj* party = Game.m_partyObjArr[m_partyRank[slot]];
				if ((party != NULL) &&
					(reinterpret_cast<CGObject*>(party)->m_scriptHandle->m_hp != 0) &&
					(reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 9) &&
					(reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 0x22) &&
					((Game.m_gameWork.m_menuStageMode == 0) ||
					 (0xF <= Game.m_gameWork.m_bossArtifactStageIndex) ||
					 ((static_cast<unsigned short>(reinterpret_cast<CGPrgObj*>(party)->GetCID()) & 0x6D) != 0x6D) ||
					 (SAFE_CAST_CARAVAN_WORK(reinterpret_cast<CGObject*>(party)->m_scriptHandle)->m_joybusCaravanId == 0))) {
					validCount++;
				}
			}

			int pick = Math.Rand(validCount);
			int accum = -1;
			int minHp = 10000000;
			int validIndex = 0;
			float homeRange2 = static_cast<float>(
				*reinterpret_cast<unsigned short*>(script + 0xCC));

			for (slot = 0; slot < 4; slot++) {
				int partyIndex = m_partyRank[slot];
				CGPartyObj* party = Game.m_partyObjArr[partyIndex];
				if ((party != NULL) &&
					(reinterpret_cast<CGObject*>(party)->m_scriptHandle->m_hp != 0) &&
					(reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 9) &&
					(reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 0x22) &&
					((Game.m_gameWork.m_menuStageMode == 0) ||
					 (0xF <= Game.m_gameWork.m_bossArtifactStageIndex) ||
					 ((static_cast<unsigned short>(reinterpret_cast<CGPrgObj*>(party)->GetCID()) & 0x6D) != 0x6D) ||
					 (SAFE_CAST_CARAVAN_WORK(reinterpret_cast<CGObject*>(party)->m_scriptHandle)->m_joybusCaravanId == 0))) {
					if (monObj->m_partyDistance[partyIndex] < homeRange2) {
						selectedTarget = partyIndex;
						if (targetMode == 0) {
							break;
						}
					}
					if ((targetMode == 3) &&
						((reinterpret_cast<CGPrgObj*>(party)->m_lastStateId == 6) ||
						 (reinterpret_cast<CGPrgObj*>(party)->m_lastStateId == 2))) {
						accum = partyIndex;
					} else if (targetMode == 2) {
						int hp = reinterpret_cast<CGObject*>(party)->m_scriptHandle->m_hp;
						if (hp < minHp) {
							minHp = hp;
							accum = partyIndex;
						}
					} else if ((targetMode == 4) && (validIndex == pick)) {
						accum = partyIndex;
					}
					validIndex++;
				}
			}

			switch (targetMode) {
			case 0:
				break;
			case 1:
				selectedTarget = targetPartyIndex;
				break;
			case 2:
			case 3:
			case 4:
				if (accum >= 0) {
					selectedTarget = accum;
				}
				break;
			}
		}

		if (selectedTarget >= 0) {

		targetPartyIndex = selectedTarget;
		switch (*reinterpret_cast<unsigned short*>(CGMonObj_GetAiData(monObj) + 0x10A)) {
		case 1:
			if (monObj->m_unk6BC == 0) {
				if (monObj->m_partyDistance[targetPartyIndex] <
					static_cast<float>(SAFE_CAST_MON_WORK(object->m_scriptHandle)->m_romWork[0x67])) {
					if (*reinterpret_cast<unsigned short*>(script + 0x10C) == 1) {
						chaseState = 5;
						chaseTimer = 0;
						monObj->m_chaseDirty = 1;
					} else {
						actionState = 0x1E;
					}
					monObj->m_unk6BC = 1;
					return;
				}
			} else {
				monObj->m_unk6BC = 0;
			}
			break;
		}

		int attackResult = monObj->mlAttackCheck(selectedTarget);
		if (attackResult == -2) {
			monObj->moveCancel();
			chaseState = 0;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		} else if (attackResult == -1) {
			monObj->moveCancel();
			chaseState = 2;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		} else {
			CGObjWork* handle = object->m_scriptHandle;
			unsigned char* aiData = reinterpret_cast<unsigned char*>(handle->m_romWork);
			if (*reinterpret_cast<unsigned short*>(aiData + 0x10C) == 1) {
				if (attackResult >= 100) {
					actionState = attackResult;
				} else {
					short aiState = monObj->m_aiState;
					if ((reinterpret_cast<CMonAiAction*>(CGMonObj_GetAiData(monObj) + 0x110)[attackResult].m_flags & 0x20) != 0) {
						CGPartyObj* party = Game.m_partyObjArr[selectedTarget];
						actionState = 0x21;
						monObj->moveChase(party);
						chaseState = 5;
						chaseTimer = 0;
						monObj->m_chaseDirty = 1;
						return;
					}
					unsigned char* aiData3;
					if (aiState == 0) {
						aiData3 = reinterpret_cast<unsigned char*>(SAFE_CAST_MON_WORK(handle)->m_romWork);
					} else {
						aiData3 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(aiState + SAFE_CAST_MON_WORK(handle)->m_romWork[0x80]) * 0x1D0 + 0x10;
					}
					float range = static_cast<float>(reinterpret_cast<CMonAiAction*>(aiData3 + 0x110)[attackResult].m_range);
					unsigned char* aiData4;
					if (aiState == 0) {
						aiData4 = reinterpret_cast<unsigned char*>(SAFE_CAST_MON_WORK(handle)->m_romWork);
					} else {
						aiData4 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(aiState + SAFE_CAST_MON_WORK(handle)->m_romWork[0x80]) * 0x1D0 + 0x10;
					}
					int changeStat = static_cast<short>(reinterpret_cast<CMonAiAction*>(aiData4 + 0x110)[attackResult].m_changeStat);
					CGPartyObj* party = Game.m_partyObjArr[selectedTarget];
					actionState = 0x21;
					CGMonObj_SetAttackMove(monObj, party, range, changeStat);
				}
			} else {
				actionState = attackResult - 0xE;
			}
			chaseState = 1;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		}
		} else {
			monObj->moveCancel();
			chaseState = 3;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		}
		return;
	}

	if (reinterpret_cast<CGPrgObj*>(monObj)->m_lastStateId == 0x21) {
		if ((*reinterpret_cast<unsigned short*>(script + 0x10C) == 1) &&
			(((monObj->m_moveWork.m_stateFlags & 1) != 0) ||
			 (monObj->m_moveWork.m_frame >=
			  static_cast<int>(*reinterpret_cast<unsigned short*>(script + 0x1BC))))) {
			monObj->moveCancel();
			chaseState = 3;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		}
	}
#undef script
#undef actionState
#undef object
#undef mon
}

/*
 * --INFO--
 * PAL Address: 0x8011467C
 * PAL Size: 1272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::aiAddDefault(int& targetIndex)
{
#define monObj (this)
#define mon (reinterpret_cast<unsigned char*>(this))
#define object (reinterpret_cast<CGObject*>(this))
#define prgObj (reinterpret_cast<CGPrgObj*>(this))
	switch (m_chaseState) {
	case 4:
		monObj->mlHide();
		break;

	case 0: {
		if (object->m_scriptHandle->m_romWork[0x86] == 1) {
			monObj->moveCancel();
		}
		if (m_chaseTimer == 0) {
			object->m_rotTargetY = object->m_homeRotY;
		}

		int hitPartyIndex = CGMonObj_SearchNoticeParty(monObj);

		if (hitPartyIndex >= 0) {
			m_targetPartyIndex = hitPartyIndex;
			mlSet(2);
			monObj->seKiduki();
		} else {
			unsigned char* aiData;
			if (monObj->m_aiState == 0) {
				aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle->m_romWork);
			} else {
				aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
					(monObj->m_aiState +
					 object->m_scriptHandle->m_romWork[0x80]) *
						0x1D0 +
					0x10;
			}
			unsigned short alertMode = *reinterpret_cast<unsigned short*>(aiData + 0x104);
			switch (alertMode) {
			case 0:
				CGMonObj::m_aiWork.m_state = 0;
				break;
			case 1:
				CGMonObj::m_aiWork.m_state = 0x10;
				break;
			case 2: {
				double soundLimit2 = (Game.m_gameWork.m_soundOptionFlag != 0) ? 10000.0 : 180.0;
				if (static_cast<double>(*reinterpret_cast<float*>(mon + 0x5BC)) < soundLimit2) {
					CGMonObj::m_aiWork.m_state = 0x1D;
					float repopDist =
						static_cast<float>(object->m_scriptHandle->m_romWork[0x66]);
					float homeDist = PSVECDistance(&monObj->m_homePosition, &object->m_worldPosition);
					if (static_cast<double>(repopDist) <= static_cast<double>(homeDist)) {
						monObj->mlEscape();
					}
				} else {
					CGMonObj::m_aiWork.m_state = 0;
				}
				break;
			}
			}
		}
		break;
	}

	case 2:
		monObj->mlMove();
		break;

	case 1:
		monObj->mlAttack();
		break;

	case 3:
		monObj->mlEscape();
		break;

	case 5: {
		{
			if (m_targetPartyIndex >= 0) {
				CGMonObj::m_aiWork.m_state = 0x21;
				CGMonObj_SetChaseMove(monObj, Game.m_partyObjArr[m_targetPartyIndex], 0);
				if (((monObj->m_moveWork.m_stateFlags & 1) != 0) ||
					(object->m_stateFlags0Bits.unk1 != 0)) {
					monObj->moveCancel();
					if (m_targetPartyIndex >= 0) {
						object->m_rotTargetY = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]));
					}
					mlSet(1);
				}
			} else {
				monObj->moveCancel();
				mlSet(0);
			}
		}
		break;
	}

	}

	if (monObj->m_chaseDirty != 0) {
		monObj->m_chaseDirty = 0;
	} else {
		m_chaseTimer += 1;
	}
#undef prgObj
#undef object
#undef mon
#undef monObj
}


/*
 * --INFO--
 * PAL Address: 0x801145D0
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::aiSeq(int seqId, int priority, int currentState, int nextState, int chance, int fallbackState)
{
	int& aiState = m_unk6C8;
#define aiPriority (CGMonObj::m_aiWork.m_priority)
#define aiBranch (CGMonObj::m_aiWork.m_state)

	if (priority <= aiPriority) {
		return 0;
	}

	if (currentState == aiState) {
		if (Math.Rand(100) <= static_cast<unsigned int>(chance)) {
			if (aiPriority < priority) {
				aiBranch = seqId;
				aiPriority = priority;
			}
			aiState = nextState;
			return 1;
		}
		if (fallbackState >= 0) {
			aiState = fallbackState;
		}
	}

	return 0;
#undef aiPriority
#undef aiBranch
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 168b
 * EN Address: 0x80138A98
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::statWatch()
{
	if (m_stateFrame == 0) {
		reqAnim(-1, 0, 0);
	}
	if (static_cast<unsigned int>(Math.Rand(0x32)) == 0) {
		if (static_cast<unsigned int>(Math.Rand(2)) == 0) {
			m_rotTargetY += 0.2f;
		} else {
			m_rotTargetY -= 0.2f;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 432b
 * EN Address: 0x80138B44
 * EN Size: 376b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::statAround()
{
	switch (m_subState) {
	case 0:
		if (m_subFrame == 0) {
			CGObjWork* work = m_scriptHandle;
			int rand = Math.Rand(0x50);
			float angle = 2.0f * (3.1415927f * Math.RandF());
			float speedScale = m_pushScale * (0.01f * static_cast<float>(work->m_romWork[0x6A]) + 0.0000001f);
			moveVectorRot(angle, 0.0f, 0.25f * speedScale, rand + 10);
		} else if ((m_weaponNodeFlagAll.m_bits1.m_bit20 == 0) || (m_stateFlags0Bits.unk1 != 0)) {
			CancelMove(1);
			changeSubStat(1);
		}
		break;
	case 1:
		if (static_cast<unsigned int>(Math.Rand(100)) == 0) {
			changeSubStat(0);
		}
		break;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::statAway()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::setAI(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x801143D0
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onFrameAlways()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	CGObjWork* scriptHandle = object->m_scriptHandle;

	if (scriptHandle != nullptr) {
		if ((scriptHandle->m_romWork[0x7F] & 4) != 0) {
			int hasNearParty = 0;
			if (m_unk6B9 == 0) {
				for (int i = 0; i < 4; i++) {
					CGPartyObj* party = Game.m_partyObjArr[i];
					if (party != nullptr && party->m_comboState != 0) {
						float dist = PSVECDistance(&party->m_comboCenter, &object->m_worldPosition);
						if (dist < 10.0f + object->m_bodyEllipsoidRadius) {
							hasNearParty = 1;
							break;
						}
					}
				}
			}

			if (hasNearParty != m_unk6C3) {
				if ((object->m_scriptHandle->m_romWork[0x7F] & 4) != 0) {
					reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x200000);
					if (hasNearParty != 0) {
						reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace(
							0x146,
							*reinterpret_cast<int*>(mon + 0x5B8),
							object,
							1.0f,
							0
						);
					}
				}
				m_unk6C3 = hasNearParty;
			}
		}

		SAFE_CAST_MON_WORK(object->m_scriptHandle)->CalcStatus();
		(this->*m_funcs->always)();

		footSe();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80114208
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::InitFinished()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	m_homePosition.x = object->unk_0x168;
	m_homePosition.y = object->unk_0x16C;
	m_homePosition.z = object->unk_0x170;

	int classId = object->m_scriptHandle->m_baseDataIndex;
	switch (classId) {
	default:
		m_funcs = &funcsDefault;
		break;
	case 0x5B:
		m_funcs = &funcsGiantCrab;
		break;
	case 0x71:
		m_funcs = &funcsGolem;
		break;
	case 0x6B:
		m_funcs = &funcsArmstrong;
		break;
	case 0x63:
		m_funcs = &funcsOrcKing;
		break;
	case 0x67:
		m_funcs = &funcsGoblinKing;
		break;
	case 0x5F:
		m_funcs = &funcsMolbol;
		break;
	case 0x73:
		m_funcs = &funcsLizardmanKing;
		break;
	case 0x77:
		m_funcs = &funcsCaveWorm;
		break;
	case 0x6F:
		m_funcs = &funcsGigasLoad;
		break;
	case 0x70:
		m_funcs = &funcsWifeLamia;
		break;
	case 0x88:
		m_funcs = &funcsMeteoParasiteC;
		break;
	case 0x85:
	case 0x86:
	case 0x87:
		m_funcs = &funcsMeteoParasite;
		break;
	case 0x8E:
	case 0x8F:
	case 0x90:
	case 0x91:
	case 0x92:
	case 0x93:
	case 0x94:
	case 0x95:
	case 0x96:
	case 0x97:
	case 0x98:
	case 0x99:
		m_funcs = &funcsDuct;
		break;
	case 0x83:
		m_funcs = &funcsDragonZombie;
		break;
	case 0x7B:
		m_funcs = &funcsAntrion;
		break;
	case 0x79:
		m_funcs = &funcsTetsukyojin;
		break;
	case 0x7F:
		m_funcs = &funcsLich;
		break;
	case 0x9B:
		m_funcs = &funcsRamoe;
		break;
	case 0x9A:
		m_funcs = &funcsLastBoss;
		break;
	case 0x9E:
		m_funcs = &funcsSaw;
		break;
	case 0x74:
	case 0x75:
		m_funcs = &funcsLKShooter;
		break;
	}

	(this->*m_funcs->initFinished)();
}

/*
 * --INFO--
 * PAL Address: 0x80114004
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::initFinishedFuncDefault()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	// Script value is authored in centi-units.
	object->m_turnFactor = 0.01f * static_cast<float>(object->m_scriptHandle->m_romWork[0xD8]);

	CCharaPcs::CHandle* handle = object->m_charaModelHandle;
	if (handle != NULL) {
		CChara::CModel* model = handle->m_model;
		if (model != NULL) {
			int nodeIdx = model->SearchNode("head");
			if (nodeIdx >= 0) {
				m_bind = reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_model->m_nodes + nodeIdx);
			}
		}
	}

	int animPoint = object->m_scriptHandle->m_romWork[0xD0];
	if (animPoint != 0xFFFF) {
		object->AddAnimPoint(1, animPoint, 0xB);
	}

	animPoint = object->m_scriptHandle->m_romWork[0xD1];
	if (animPoint != 0xFFFF) {
		object->AddAnimPoint(1, animPoint, 0xA);
	}

	m_forcedAction = -1;
	for (int forcedAction = 0; forcedAction < 8; forcedAction++) {
		int attackId = SAFE_CAST_MON_WORK(m_scriptHandle)->m_actionItems[forcedAction];
		if ((attackId != 0xFFFF) &&
			(static_cast<int>(reinterpret_cast<const SCharaItemRow*>(Game.unkCFlatData0[2])[attackId].m_actionType) == 4)) {
			m_forcedAction = forcedAction;
			break;
		}
	}

	setRepop(1);
}

/*
 * --INFO--
 * PAL Address: 0x80113F58
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::setIceJEffect(int enabled)
{
#define object (reinterpret_cast<CGObject*>(this))
	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x20000);

	if (enabled != 0) {
		unsigned short count = object->m_scriptHandle->m_romWork[0xD5];
		for (int i = 0; i < static_cast<int>(static_cast<unsigned short>(count)); i++) {
			int dataNo = object->m_charaModelHandle->GetPdtSlot();
			reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace((i + 0x5A) | (dataNo << 8), *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x5A8), object, 1.0f, 0);
		}
	}
#undef object
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::setFlyEffect(int, int)
{
	// TODO
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 576b
 * EN Address: 0x80139454
 * EN Size: 336b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::setUndeadEffect(int weaponMode, int enabled)
{
	int isUndead = m_scriptHandle->m_romWork[0x7E] == 0xB;
	if (!isUndead) {
		weaponMode = 1;
	}
	endPSlotBit(0x1000);
	int count = weaponMode ?
		m_scriptHandle->m_romWork[0xD6] :
		m_scriptHandle->m_romWork[0xD7];
	int particleBase = weaponMode ? 0x46 : 0x3C;
	if (enabled) {
		for (int i = 0; i < count; i++) {
			int dataNo = m_charaModelHandle->GetPdtSlot();
			int particleId = particleBase + i;
			putParticleBindTrace(particleId | (dataNo << 8), m_particleSlots[12], this, 1.0f, 0);
		}
	} else if (isUndead && count != 0) {
		int dataNo = m_charaModelHandle->GetPdtSlot();
		putParticleBindTrace((particleBase + 9) | (dataNo << 8), m_particleSlots[12], this, 1.0f, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80113EFC
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CGMonObj::IsDispRader()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char result = 0;
	int isDispRader = object->CGObject::IsDispRader();
	if (isDispRader != 0 &&
	    static_cast<signed char>(
	        static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags)) << 24) &
	                         0xC0000000) >>
	        31) != 0) {
		result = 1;
	}
	return result;
}


/*
 * --INFO--
 * PAL Address: 0x80113960
 * PAL Size: 1436b
 * EN Address: 0x80139608
 * EN Size: 924b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::setRepop(int mode)
{
#define object (reinterpret_cast<CGObject*>(this))
	CGObjWork* scriptHandle = object->m_scriptHandle;
	int classId = scriptHandle->m_baseDataIndex;

	int spawnIndex = scriptHandle->m_saveSlot;
	int option;
	if ((mode != 0) && (option = static_cast<int>(*reinterpret_cast<short*>(&Game.m_gameWork.m_optionValue)), option < 9)) {
		u64 bit = 1ULL << spawnIndex;
		if ((CFlat.m_spawnBits[option] & bit) != 0) {
			scriptHandle->m_hp = 0;
			object->m_bgColMask = 0;
			object->m_displayFlags = 0;
			object->m_weaponNodeFlagBits.m_unk10 = 0;
			reinterpret_cast<CGPrgObj*>(this)->changeStat(0x28, 0, 0);
			return;
		}
	}

	if (mode == 0) {
		m_homePosition.x = object->unk_0x168;
		m_homePosition.y = object->unk_0x16C;
		m_homePosition.z = object->unk_0x170;
		object->m_worldPosition = m_homePosition;
		float baseRot = object->m_homeRotY;
		object->m_rotBaseY = baseRot;
		object->m_rotTargetY = baseRot;

		CGObjWork* repopHandle = object->m_scriptHandle;
		repopHandle->m_hp =
			repopHandle->m_maxHp;
		resetWork();
	}

	enableAttackCol(0, 0, 0);
	enableDamageCol(1);
	reinterpret_cast<CGPrgObj*>(this)->changeStat(0, 0, 0);

	int scriptFlags = object->m_scriptHandle->m_romWork[0x7F];

	if ((scriptFlags & 0x80) != 0 || (scriptFlags & 0x20) != 0) {
		if (mode == 0) {
			object->m_bgColMask |= 0x10002;
		}
		mlSet(4);
		enableDamageCol(0);
	} else {
		if ((scriptFlags & 0x40) != 0 || classId == 0x39) {
			mlSet(4);
			enableDamageCol(0);
			if ((scriptFlags & 0x40) != 0) {
				object->SetAnimSlot(10, 0);
			}
		}

		if ((scriptFlags & 0x200) != 0) {
			reinterpret_cast<CGPrgObj*>(this)->changeStat(0x36, 0, 0);
		}

		if (mode == 0) {
			reinterpret_cast<CGPrgObj*>(this)->playSe3D(0x18, 0x32, 0x96, 0, (Vec*)0);
			reinterpret_cast<CGPrgObj*>(this)->putParticle(300, 0, &object->m_worldPosition, 1.0f, 0);
			object->m_bgColMask |= 0x90002;
			m_alpha = 1.0f;
		}
	}

	switch (classId) {
	case 0x55:
		mlSet(4);
		break;
	}

	unsigned short countA = object->m_scriptHandle->m_romWork[0xD4];
	for (int i = 0; i < static_cast<int>(countA); i++) {
		int particleBase = 0;
		switch (classId) {
		case 0xA9:
			particleBase = 0;
			break;
		case 0x9C:
			particleBase = 1;
			break;
		case 0xA7:
		case 0xA8:
			particleBase = 2;
			break;
		}

		int dataNo = object->m_charaModelHandle->GetPdtSlot();
		int particleId = i + 0x50 + particleBase;
		reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace(particleId | (dataNo << 8), m_particleSlots[16], object, 1.0f, 0);
	}

	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x20000);

	unsigned short countB = object->m_scriptHandle->m_romWork[0xD5];
	for (int i = 0; i < static_cast<int>(countB); i++) {
		int dataNo = object->m_charaModelHandle->GetPdtSlot();
		reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace((i + 0x5A) | (dataNo << 8), m_particleSlots[17], object, 1.0f, 0);
	}

	if ((object->m_scriptHandle->m_romWork[0x7F] & 1) == 0) {
		return;
	}

	m_alpha = 0.4f;
	scriptHandle = object->m_scriptHandle;
	classId = scriptHandle->m_baseDataIndex;
	setUndeadEffect(m_weaponNodeFlagBits.m_prg, 1);

	if (object->m_scriptHandle->m_romWork[0x7E] == 0xB) {
		object->SetTexAnim("u1");
	}

	if (object->m_weaponNodeFlagBits.m_prg != 0) {
		if (classId == 0x83) {
			reinterpret_cast<CGPrgObj*>(this)->playSe3D(0x987A, 0x32, 0x96, 0, (Vec*)0);
		} else if (classId == 0x7F) {
			reinterpret_cast<CGPrgObj*>(this)->playSe3D(0x11585, 0x32, 0x96, 0, (Vec*)0);
		}
	}

	m_unk6BA = 0;
#undef object
}

/*
 * --INFO--
 * PAL Address: 0x8011367C
 * PAL Size: 740b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveAStar(int startGroup, int forbiddenGroup, Vec& targetPos)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);

	short& routeFrom = m_moveWork.m_routeFrom;
	short& routePrev = m_moveWork.m_routePrev;

	if (((m_moveWork.m_flags & 0x30000) != 0) && AStar.isAStar()) {
		if (routeFrom == 0) {
			routeFrom = static_cast<short>(startGroup);
		}
		if (((m_moveWork.m_flags & 0x10000) != 0) && ((m_moveWork.m_flags & 0x40) == 0)) {
			short currentRoute = routeFrom;
			if ((currentRoute != 0) && (forbiddenGroup != 0) && (currentRoute != forbiddenGroup)) {
				unsigned char* routeStep = AStar.m_routeTable[currentRoute][forbiddenGroup];
				CAStar::CAPos* portalPos = &AStar.m_portals[routeStep[1]];
				float portalDist = PSVECDistance(&object->m_worldPosition, &portalPos->m_position);
				if ((portalDist < object->m_capsuleHalfHeight) || (startGroup == routeStep[0])) {
					routeFrom = routeStep[0];
					portalPos = &AStar.m_portals[AStar.m_routeTable[routeStep[0]][forbiddenGroup][1]];
				}
				targetPos.x = portalPos->m_position.x;
				targetPos.y = portalPos->m_position.y;
				targetPos.z = portalPos->m_position.z;
			}
		} else {
			CAStar::CAPos* escapePos;
			if ((routeFrom != 0) && (forbiddenGroup != 0) &&
				((escapePos = AStar.getEscapePos(object->m_worldPosition, targetPos, routeFrom, routePrev)) != NULL)) {
				int nextGroup = escapePos->GetOthers(routeFrom);
				unsigned char* routeStep = AStar.m_routeTable[routeFrom][nextGroup];
				float portalDist = PSVECDistance(&object->m_worldPosition, &escapePos->m_position);
				if ((portalDist < object->m_capsuleHalfHeight) || (startGroup == routeStep[0])) {
					routePrev = routeFrom;
					routeFrom = routeStep[0];
					escapePos = &AStar.m_portals[AStar.m_routeTable[routeStep[0]][forbiddenGroup][1]];
				}

				float targetDist = PSVECDistance(&targetPos, &object->m_worldPosition);
				CVector dir = CVector(object->m_worldPosition) - CVector(escapePos->m_position);
				dir.Normalize();
				targetPos = CVector(object->m_worldPosition) + dir * targetDist;
			}
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80113098
 * PAL Size: 1508b
 * EN Address: 0x80139CC0
 * EN Size: 1812b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveFrame()
{
	unsigned int& moveStateFlags = m_moveWork.m_stateFlags;
	unsigned int& moveFlags = m_moveWork.m_flags;
	float& moveSpeed = m_moveWork.m_speed;
	float& moveRange = m_moveWork.m_range;
	unsigned int& moveLimitFrame = m_moveWork.m_limitFrame;
	int& moveFrame = m_moveWork.m_frame;
	int& moveChangeStat = m_moveWork.m_changeStat;
	float& moveSpeedRate = m_pushScale;
	short& aStarGroupId = m_aStarGroupId;

	CVector targetPos;
	CVector moveDirection;
	float rotY;
	float distance;
	float targetDist;

	if ((moveStateFlags & 1) != 0) {
		return;
	}

	(this->*m_funcs->moveFrame)();

	if ((moveFlags & 1) != 0) {
		targetPos = CVector(m_moveWork.m_target->m_worldPosition);
		targetDist = PSVECDistance(static_cast<Vec*>(targetPos), &m_worldPosition);

		if (((moveFlags & 0x30000) != 0) && AStar.isAStar()) {
			short targetAStarGroupId = m_moveWork.m_target->m_aStarGroupId;
			moveAStar(aStarGroupId, targetAStarGroupId, targetPos);
		}
	} else if ((moveFlags & 2) != 0) {
		targetPos = CVector(m_moveWork.m_targetPos);
		targetDist = PSVECDistance(static_cast<Vec*>(targetPos), &m_worldPosition);

		if (((moveFlags & 0x30000) != 0) && AStar.isAStar()) {
			int polygonGroup = AStar.calcPolygonGroup(static_cast<Vec*>(targetPos), static_cast<int>(m_bgHitMask));
			moveAStar(aStarGroupId, polygonGroup, targetPos);
		}
	} else if ((moveFlags & 0x2000) != 0) {
		targetPos = CVector(m_worldPosition) + CVector(m_moveWork.m_targetPos);
		targetDist = PSVECDistance(static_cast<Vec*>(targetPos), &m_worldPosition);
	}

	moveDirection = targetPos - CVector(m_worldPosition);
	if ((moveFlags & 0x40) != 0) {
		moveDirection = CVector(-moveDirection.x, -moveDirection.y, -moveDirection.z);
	}

	rotY = moveDirection.GetRotateY();
	distance = PSVECMag(static_cast<Vec*>(moveDirection));

	if ((((moveFlags & 0x20) != 0) && (targetDist < moveRange)) ||
		(((moveFlags & 0x40) != 0) && (targetDist >= moveRange))) {
	moveCancelExit:
		moveStateFlags |= 1;
		(this->*m_funcs->moveCancel)();
		moveStateFlags |= 2;
		if ((moveFlags & 0x100) != 0) {
			changeStat(moveChangeStat, 0, 0);
		}
		return;
	}

	if ((moveFlags & 4) != 0) {
		float oldRotY = m_rotBaseY;
		if ((moveFlags & 0x8000) != 0) {
			oldRotY += 3.1415927f;
		}

		float dstRot = Math.DstRot(rotY, oldRotY);
		float turnFactor = m_turnFactor;
		float baseDelta = dstRot * turnFactor;
		float rotDelta = dstRot * (1.0f - turnFactor);
		rotY = rotY - rotDelta;
		m_rotBaseY = m_rotBaseY + baseDelta;
		m_rotTargetY = m_rotBaseY;

		float s = sinf(dstRot);
		float c = cosf(dstRot);
		float x = moveDirection.x;
		moveDirection.x = (c * x) - (s * moveDirection.z);
		moveDirection.z = (s * x) + (c * moveDirection.z);
		distance = PSVECMag(static_cast<Vec*>(moveDirection));
	}

	if (((moveFlags & 0x80) != 0) && (m_stateFlags0Bits.unk1 != 0)) {
		goto moveCancelExit;
	}

	float stepDist;
	if ((moveFlags & 0x200) != 0) {
		unsigned short speedScale = m_scriptHandle->m_romWork[0x6A];
		stepDist = moveSpeedRate * (0.01f * speedScale + 0.0000001f);
	} else if ((moveFlags & 0x800) != 0) {
		unsigned short speedScale = m_scriptHandle->m_romWork[0x6A];
		stepDist = moveSpeedRate * (0.01f * speedScale + 0.0000001f);
	} else {
		stepDist = moveSpeed;
	}

	CVector moveDelta;
	if ((moveFlags & 0x1000) != 0) {
		moveDelta = moveDirection;
	} else {
		if (__fabs(distance) < 0.00001f) {
			moveDelta = CVector(0.0f, 0.0f, 0.0f);
		} else {
			moveDelta = moveDirection * ((1.0f / distance) * stepDist);
		}
	}

	if ((moveFlags & 0x4000) != 0) {
		PSVECAdd(&m_groundHitOffset, static_cast<Vec*>(moveDelta), &m_groundHitOffset);
	} else {
		m_groundHitOffset.x += moveDelta.x;
		m_groundHitOffset.z += moveDelta.z;
	}

	targetDist -= stepDist;
	if ((moveFlags & 0x8000) != 0) {
		m_rotTargetY = 3.1415927f + rotY;
	} else {
		m_rotTargetY = rotY;
	}

	if (((moveFlags & 0x20) == 0 || !(targetDist < moveRange)) &&
		((moveFlags & 0x40) == 0 || !(targetDist >= moveRange))) {
		if ((moveFrame == 0) && ((moveFlags & 0x400) == 0)) {
			reqAnim(1, 1, 0);
		}

		moveFrame++;
		if (((moveFlags & 0x10) == 0) || ((int)moveLimitFrame > moveFrame)) {
			return;
		}
	}

	goto moveCancelExit;
}

/*
 * --INFO--
 * PAL Address: 0x8011306C
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::logicFuncDefault()
{
	int targetIndex = 0;
	aiAddDefault(targetIndex);
}

/*
 * --INFO--
 * PAL Address: 0x80112FD4
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::calcBranchFuncDefault(int branchType)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	int result = 0;

	if (branchType == 1) {
		unsigned char* script = reinterpret_cast<unsigned char*>(object->m_scriptHandle);
		unsigned short max = *reinterpret_cast<unsigned short*>(script + 0x1A);
		unsigned short current = *reinterpret_cast<unsigned short*>(script + 0x1C);
		if (static_cast<int>(current) < static_cast<int>(static_cast<unsigned int>(max) >> 1)) {
			result = 1;
		}
	} else if (branchType == 2) {
		unsigned char* script = reinterpret_cast<unsigned char*>(object->m_scriptHandle);
		unsigned short max = *reinterpret_cast<unsigned short*>(script + 0x1A);
		unsigned short current = *reinterpret_cast<unsigned short*>(script + 0x1C);
		if (current < (max / 3)) {
			result = 2;
		} else if (current < ((max * 2) / 3)) {
			result = 1;
		}
	} else if (branchType != 0) {
		result = 0;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x80112ED4
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::sysControl(int controlType)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);

	switch (controlType) {
	case 6:
		m_repop.delay = 0;
		break;

	case 7:
		m_unk6BE = 1;
		mlSet(4);
		object->m_bgColMask &= 0xFFF7FFFD;
		object->m_displayFlags &= 0xFFFFFFFE;
		break;

	case 8:
		m_unk6BE = 0;
		break;

	case 0xD:
		m_unk6C1 = 0;
		break;

	case 0xC:
		m_unk6C1 = 1;
		break;

	case 0xF:
		setRepop(0);
		break;

	case 0x10:
		object->m_displayFlags |= 0x400000;
		break;

	case 0x11:
		object->m_displayFlags &= 0xFFBFFFFF;
		break;

	case 0x16:
		object->m_weaponNodeFlagBits.m_control3 = 0;
		break;

	case 0x15:
		object->m_weaponNodeFlagBits.m_control3 = 1;
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80112D5C
 * PAL Size: 376b
 * EN Address: 0x8013A5E8
 * EN Size: 136b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onChangePrg(int value)
{
	if ((m_weaponNodeFlagBits.m_prg != value) &&
		(m_scriptHandle->m_romWork[0x7E] == 0xB)) {
		int enabled = m_unk6BA == 0;
		setUndeadEffect(value, enabled);
	}
	CGCharaObj::onChangePrg(value);
}
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 220b
 * EN Address: 0x8013A670
 * EN Size: 272b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGMonObj::footSe()
{
	unsigned short stepSeRaw = m_scriptHandle->m_romWork[0xDF];
	int stepSeId;
	if (stepSeRaw == 0xFFFF) {
		stepSeId = 0;
	} else {
		stepSeId = (stepSeRaw & 0xFF) + ((stepSeRaw >> 8) * 1000);
	}

	if (stepSeId != 0) {
		int& stepSeHandle = m_stepSeHandle;
		if (m_currentAnimSlot == m_animSlots[1]) {
			if (stepSeHandle != 0) {
				Sound.ChangeSe3DPos(stepSeHandle, &m_worldPosition);
			} else {
				stepSeHandle = playSe3D(stepSeId, 0x32, 0x96, 0, (Vec*)0);
			}
		} else if (stepSeHandle != 0) {
			Sound.FadeOutSe3D(stepSeHandle, 0x32);
			stepSeHandle = 0;
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x80112d54
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::GetCID()
{
	return 0xAD;
}


