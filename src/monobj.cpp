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
#include "ffcc/partyobj.h"
#include "ffcc/sound.h"
#include "ffcc/gbaque.h"
#include "ffcc/linkage.h"
#include "ffcc/vector.h"
#include "PowerPC_EABI_Support/Runtime/ptmf.h"

#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

u8 CGMonObj::m_aiWork[0xC];
u8 CGMonObj::m_boss[0x8C];

extern "C" float g_hit_t;
extern float kMonObjDefaultScale;
extern float FLOAT_803319C4;
extern "C" const float kMonObjEpsilon = 0.0000001f;
extern "C" const float kMonObjHundredth = 0.01f;
extern "C" const double kMonObjSmallStepF64 = 0.000009999999747378752;
extern "C" const float kMonObjZero = 0.0f;
extern "C" const double kMonObjUnsignedIntBias = 4503599627370496.0;
extern "C" const float kMonObjTwoFifths = 0.4f;
static const char s_monObjTexAnimU1[3] = "u1";
static const char s_monObjHeadNode[] = "head";
extern "C" const float kMonObjHomeSnapDistance = 10.0f;
extern "C" const float kMonObjTwo = 2.0f;
extern "C" const float kMonObjQuarter = 0.25f;
extern "C" const float kMonObjFifth = 0.2f;
extern "C" const double kMonObjSignedIntBias = 4503601774854144.0;
extern "C" const double kMonObjWideSoundRange = 10000.0;
extern "C" const double kMonObjNormalSoundRange = 180.0;
extern "C" const float kMonObjDegToRad = 0.017453292f;
extern "C" const float kMonObjRadToDeg = 57.29578f;
static const char s_monObjPassThroughText[] = "\x92\xca\x89\xdf\x81\x42\n";
extern "C" const float kMonObjHalfPi = 1.5707964f;
extern "C" const float kMonObjHalf = 0.5f;
extern "C" const float kMonObjMaxBound = 10000000000.0f;
extern "C" const float kMonObjMinBound = -10000000000.0f;
extern "C" const float kMonObjConeSideRadius = 20.0f;
extern "C" const float kMonObjParticleRadiusScale = 0.1f;
extern "C" const float kMonObjTwoThirdsPi = 2.0943952f;
static const char s_monObjTexAnimU0[3] = "u0";
extern "C" const float kMonObjPercentMax = 100.0f;
extern "C" const float kMonObjOne = 1.0f;
static const char s_monObjAiStateFmt[] = "%d:%c %d:%c";
static const char s_monObjDistanceFmt[] = "%d %d %d";

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
	memset(&m_moveWork, 0, sizeof(m_moveWork));
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
 * PAL Address: 0x801162B4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::resetWork()
{
	*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
	memset(&m_moveWork, 0, sizeof(m_moveWork));
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
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	CGCharaObj::onFramePreCalc();
	m_aliveFrames += 1;

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x10C) == 1) {
		unsigned char* aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
		short& aiState = m_aiState;
		short& aiStatePrev = m_aiStatePrev;

		if (aiState != 0) {
			aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
				(aiState + *reinterpret_cast<unsigned short*>(
					reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x100)) * 0x1D0 + 0x10;
		}

		aiState = (this->*m_funcs->calcBranch)(*reinterpret_cast<unsigned short*>(aiData + 0x102) & 3);

		if (aiState != aiStatePrev) {
			aiStatePrev = aiState;
			m_unk6CC = 0;
		}
	}

	if ((*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + 0x3E) == 0) &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + 0x50) == 0) &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + 0x44) == 0) &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + 0x46) == 0) &&
		(static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(mon[0x63C]) << 24) & 0xC0000000) >> 31) != 0) &&
		(m_unk6B9 == 0) &&
		(m_unk6C1 == 0)) {
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x10C) == 1) {
			*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = -1;
		} else {
			*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
		}
		*reinterpret_cast<int*>(CGMonObj::m_aiWork + 8) = m_targetPartyIndex;
		*reinterpret_cast<int*>(CGMonObj::m_aiWork + 0) = -1;

		if ((reinterpret_cast<unsigned int>(object->m_scriptHandle[4]) < 0x9A) &&
			(0x8D < reinterpret_cast<unsigned int>(object->m_scriptHandle[4]))) {
			int aiLocal = 0;
			aiAddDuct(aiLocal);
		} else {
			(this->*m_funcs->logic)();
		}

		int nextState = *reinterpret_cast<int*>(CGMonObj::m_aiWork + 4);
		if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x10C) == 1) {
			if ((nextState != -1) && (nextState != prgObj->m_lastStateId)) {
				prgObj->changeStat(nextState, 0, 0);
			}
		} else if (nextState != prgObj->m_lastStateId) {
			prgObj->changeStat(nextState, 0, 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011A248
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::flyDown()
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGCharaObj* charaObj = reinterpret_cast<CGCharaObj*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	prgObj->changeStat(0x17, 0, 0);
	m_unk6B9 = 1;
	charaObj->damageDelete();
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::undeadOff()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);

	*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x694) = 0.0f;

	unsigned char weaponFlags = *reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags);
	int weaponMode = static_cast<int>((static_cast<unsigned int>(weaponFlags) << 24) & 0xC0000000) >> 31;
	int isUndead =
		(static_cast<unsigned int>(
			 __cntlzw(0xB - *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC))) >>
		 5) &
		0xFF;
	if (isUndead == 0) {
		weaponMode = 1;
	}

	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x1000);

	unsigned short count = (weaponMode != 0) ?
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AC) :
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AE);
	int particleBase = (weaponMode != 0) ? 0x46 : 0x3C;

	if ((isUndead != 0) && (count != 0)) {
		int dataNo = object->m_charaModelHandle->GetPdtSlot();
		reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace((particleBase + 9) | (dataNo << 8), *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x594), object, 0.0f, 0);
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) == 0xB) {
		object->SetTexAnim(const_cast<char*>(s_monObjTexAnimU0));
	}

	m_unk6BA = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80119F74
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::undeadOn()
{
#define object (reinterpret_cast<CGObject*>(this))
	*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x694) = kMonObjTwoFifths;
	void* classId = object->m_scriptHandle[4];
	unsigned char weaponFlags = *reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags);
	int weaponMode = static_cast<int>((static_cast<unsigned int>(weaponFlags) << 24) & 0xC0000000) >> 31;
	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) != 0xB) {
		weaponMode = 1;
	}

	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x1000);

	unsigned short count = (weaponMode != 0) ?
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AC) :
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AE);
	int particleBase = (weaponMode != 0) ? 0x46 : 0x3C;

	for (int i = 0; i < static_cast<int>(count); i++) {
		int dataNo = object->m_charaModelHandle->GetPdtSlot();
		reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace((particleBase + i) | (dataNo << 8), *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x594), object, kMonObjDefaultScale, 0);
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) == 0xB) {
		object->SetTexAnim(const_cast<char*>(s_monObjTexAnimU1));
	}

	if (static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags)) << 24)) < 0) {
		if (classId == reinterpret_cast<void*>(0x83)) {
			reinterpret_cast<CGPrgObj*>(this)->playSe3D(0x987A, 0x32, 0x96, 0, (Vec*)0);
		} else if (classId == reinterpret_cast<void*>(0x7F)) {
			reinterpret_cast<CGPrgObj*>(this)->playSe3D(0x11585, 0x32, 0x96, 0, (Vec*)0);
		}
	}

	m_unk6BA = 0;
#undef object
}

/*
 * --INFO--
 * PAL Address: 0x80119EC0
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::rotTarget(int targetPartyIndex, float rotLimit)
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);

	if (targetPartyIndex >= 0) {
		float targetRot = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[targetPartyIndex]));
		if (rotLimit > kMonObjTwoThirdsPi) {
			object->m_rotTargetY = targetRot;
		} else {
			float delta = Math.DstRot(targetRot, *reinterpret_cast<float*>(&object->m_bgFlags));
			float clamped = -rotLimit;
			if (!(delta < clamped)) {
				if (rotLimit < delta) {
					clamped = rotLimit;
				} else {
					clamped = delta;
				}
			}
			object->m_rotTargetY = *reinterpret_cast<float*>(&object->m_bgFlags) + clamped;
		}
	}
}

static inline void CGMonObj_SetAttackAfter(CGMonObj* monObj, int attackKind)
{
	int delay = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (attackKind * 0x48 + 0xA));
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
		delay -= *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + (stageRank * 2 + 0x58));
		delay &= ~((int)delay >> 31);
	}

	if (delay != 0) {
		int range = delay / 5;
		int clampedRange = 1;
		if (0 < range) {
			clampedRange = range;
		}

		monObj->m_attackDelay = delay + Math.Rand(clampedRange);
		reinterpret_cast<CGPrgObj*>(monObj)->changeStat(0x11, 0, 0);
	} else {
		reinterpret_cast<CGPrgObj*>(monObj)->changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80119A64
 * PAL Size: 1116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onStatAttack(int state)
{
#define prgObj (reinterpret_cast<CGPrgObj*>(this))
#define object (reinterpret_cast<CGObject*>(this))
#define mon (reinterpret_cast<unsigned char*>(this))
	unsigned char* attackData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + *reinterpret_cast<int*>(mon + 0x560) * 0x48;
	int attackType = *reinterpret_cast<unsigned short*>(attackData + 0xE);
	unsigned short attackFlags = *reinterpret_cast<unsigned short*>(attackData + 0x32);

	if (state == 0) {
		if ((prgObj->m_stateFrame == 0) && (m_targetPartyIndex >= 0)) {
			CGPartyObj* target = Game.m_partyObjArr[m_targetPartyIndex];
			m_comboCenter = reinterpret_cast<CGObject*>(target)->m_worldPosition;

			if ((attackFlags & 2) == 0) {
				float rotLimit = kMonObjDegToRad * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x19C));
				if (m_targetPartyIndex >= 0) {
					float targetRot = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]));
					if (rotLimit > kMonObjTwoThirdsPi) {
						object->m_rotTargetY = targetRot;
					} else {
						float delta = Math.DstRot(targetRot, *reinterpret_cast<float*>(&object->m_bgFlags));
						float clamped = -rotLimit;
						if (!(delta < clamped)) {
							if (rotLimit < delta) {
								clamped = rotLimit;
							} else {
								clamped = delta;
							}
						}
						object->m_rotTargetY = *reinterpret_cast<float*>(&object->m_bgFlags) + clamped;
					}
				}
			}

			target = Game.m_partyObjArr[m_targetPartyIndex];
			reinterpret_cast<CGPrgObj*>(target)->bonus(0x17, *reinterpret_cast<int*>(mon + 0x560), reinterpret_cast<CGPrgObj*>(target));
		}
		return;
	}

	if (attackType == 3) {
		if (prgObj->m_subState == 1) {
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(*reinterpret_cast<int*>(mon + 0x554), 1, 0);
			}
			if (prgObj->m_subFrame == *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) + (*reinterpret_cast<int*>(mon + 0x560) * 0x48 + 0x2E))) {
				prgObj->addSubStat();
			}
		} else if (prgObj->m_subState == 0) {
			if (prgObj->isLoopAnim() != 0) {
				prgObj->addSubStat();
			}
		} else if (prgObj->m_subState < 3) {
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(*reinterpret_cast<int*>(mon + 0x558), 0, 0);
				reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(1);
			}
			if (prgObj->isLoopAnim() != 0) {
				CGMonObj_SetAttackAfter(this, *reinterpret_cast<int*>(mon + 0x560));
			}
		}
		return;
	}

	if ((prgObj->m_stateArg == 0) && (prgObj->isLoopAnim() != 0)) {
		CGMonObj_SetAttackAfter(this, *reinterpret_cast<int*>(mon + 0x560));
	}
#undef attackData
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
	CGMonObj_SetAttackAfter(this, attackKind);
}

/*
 * --INFO--
 * PAL Address: 0x80119674
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::getNearParty(int targetOrdinal, int flags, float minDist, float maxDist, int classId)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	CGObject* monObject = reinterpret_cast<CGObject*>(this);
	int foundCount = 0;
	int selectedPartyIndex = -1;

	unsigned char* slotPtr = mon;
	for (int slot = 0; slot < 4; slot++) {
		int partyIndex = *reinterpret_cast<int*>(slotPtr + 0x620);
		CGPartyObj* party = Game.m_partyObjArr[partyIndex];
		CGPrgObj* partyPrg = reinterpret_cast<CGPrgObj*>(party);
		CGObject* partyObj = reinterpret_cast<CGObject*>(party);

		if ((party != NULL) &&
			(((Game.m_gameWork.m_menuStageMode == 0) ||
				(0xE < Game.m_gameWork.m_bossArtifactStageIndex) ||
				((static_cast<unsigned short>(partyPrg->GetCID()) & 0x6D) != 0x6D) ||
				(partyObj->m_scriptHandle[0xED] == NULL))) &&
			(((flags & 1) == 0) ||
				((*reinterpret_cast<short*>(partyObj->m_scriptHandle + 7) != 0) &&
					(partyPrg->m_lastStateId != 9) && (partyPrg->m_lastStateId != 0x22) &&
					((Game.m_gameWork.m_menuStageMode == 0) ||
						(0xE < Game.m_gameWork.m_bossArtifactStageIndex) ||
						((static_cast<unsigned short>(partyPrg->GetCID()) & 0x6D) != 0x6D) ||
						(partyObj->m_scriptHandle[0xED] == NULL)))) &&
			(((flags & 0x10) == 0) ||
				(*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(partyObj->m_scriptHandle) + 0x4E) != 0)) &&
			(((flags & 0x20) == 0) ||
				(((partyPrg->m_lastStateId == 6) || (partyPrg->m_lastStateId == 2)) &&
					(partyPrg->m_subState == 1))) &&
			(((flags & 0x40) == 0) ||
				((static_cast<signed char>(party->m_partyData.unk6C0) >= 0) &&
					(partyObj->m_scriptHandle[4] == reinterpret_cast<void*>(classId)))) &&
			(((flags & 2) != 0) || (minDist <= *reinterpret_cast<float*>(mon + 0x5D0 + partyIndex * 4))) &&
			(((flags & 4) != 0) || (*reinterpret_cast<float*>(mon + 0x5D0 + partyIndex * 4) <= maxDist))) {
			if (((flags & 8) != 0) && (0.0f < *reinterpret_cast<float*>(mon + 0x5D0 + partyIndex * 4))) {
				Vec toParty;
				Vec facing;
				PSVECSubtract(&partyObj->m_worldPosition, &monObject->m_worldPosition, &toParty);
				PSVECScale(&toParty, &toParty, kMonObjDefaultScale / *reinterpret_cast<float*>(mon + 0x5D0 + partyIndex * 4));
				facing.x = sin(monObject->m_rotTargetY);
				facing.y = 0.0f;
				facing.z = cos(monObject->m_rotTargetY);
				if (PSVECDotProduct(&toParty, &facing) <= 0.0f) {
					goto next_slot;
				}
			}

			if (((targetOrdinal == -1) || (targetOrdinal == foundCount)) &&
				(selectedPartyIndex = partyIndex, targetOrdinal == foundCount)) {
				return partyIndex;
			}
			foundCount++;
		}

	next_slot:
		slotPtr += 4;
	}

	return selectedPartyIndex;
}

/*
 * --INFO--
 * PAL Address: 0x80119528
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onChangeStat(int state)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	(this->*m_funcs->changeStat)(state);

	if ((state < 3) && (state < -4) && (state >= -14)) {
		int scriptOffset = (state + 0xE) * 2;
		unsigned int action = *reinterpret_cast<unsigned short*>((unsigned char*)object->m_scriptHandle + scriptOffset + 0xD0);
		unsigned int motion = *reinterpret_cast<unsigned short*>((unsigned char*)object->m_scriptHandle + scriptOffset + 0xF0);
		int actionType;

		*reinterpret_cast<unsigned int*>(mon + 0x560) = action;
		*reinterpret_cast<unsigned int*>(mon + 0x550) = motion;
		*reinterpret_cast<int*>(mon + 0x554) = *reinterpret_cast<int*>(mon + 0x550) + 1;
		*reinterpret_cast<int*>(mon + 0x558) = *reinterpret_cast<int*>(mon + 0x554) + 1;
		*reinterpret_cast<int*>(mon + 0x55C) = *reinterpret_cast<int*>(mon + 0x558) + 1;

		actionType = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<int*>(mon + 0x560) * 0x48 + 0xE);
		if ((actionType == 3) || ((actionType < 2) && (actionType >= 0))) {
			*reinterpret_cast<unsigned int*>(mon + 0x630) =
				*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<int*>(mon + 0x560) * 0x48 + 0x20);
			*reinterpret_cast<unsigned int*>(mon + 0x634) =
				*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (*reinterpret_cast<int*>(mon + 0x560) * 0x48 + 0x22));
			*reinterpret_cast<unsigned int*>(mon + 0x638) =
				*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (*reinterpret_cast<int*>(mon + 0x560) * 0x48 + 0x22));
		} else if (actionType == 2) {
			*reinterpret_cast<unsigned int*>(mon + 0x68C) =
				CGCharaObj::calcCastTime(*reinterpret_cast<int*>(mon + 0x560));
		}
	}

	CGCharaObj::onChangeStat(state);
}

/*
 * --INFO--
 * PAL Address: 0x80119428
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::setActionParam(int state)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	unsigned char* script = reinterpret_cast<unsigned char*>(object->m_scriptHandle);

	int scriptOffset = (state + 0xE) * 2;
	unsigned int action = *reinterpret_cast<unsigned short*>(script + scriptOffset + 0xD0);
	*reinterpret_cast<unsigned int*>(mon + 0x560) = action;

	unsigned int motion = *reinterpret_cast<unsigned short*>(script + scriptOffset + 0xF0);
	*reinterpret_cast<unsigned int*>(mon + 0x550) = motion;
	*reinterpret_cast<int*>(mon + 0x554) = *reinterpret_cast<int*>(mon + 0x550) + 1;
	*reinterpret_cast<int*>(mon + 0x558) = *reinterpret_cast<int*>(mon + 0x554) + 1;
	*reinterpret_cast<int*>(mon + 0x55C) = *reinterpret_cast<int*>(mon + 0x558) + 1;

	int actionType = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<unsigned int*>(mon + 0x560) * 0x48 + 0xE);
	if (actionType != 3) {
		if (2 < actionType) {
			return;
		}
		if (1 < actionType) {
			*reinterpret_cast<int*>(mon + 0x68C) = CGCharaObj::calcCastTime(*reinterpret_cast<int*>(mon + 0x560));
			return;
		}
	}
	*reinterpret_cast<unsigned int*>(mon + 0x630) =
		*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<unsigned int*>(mon + 0x560) * 0x48 + 0x20);
	*reinterpret_cast<unsigned int*>(mon + 0x634) =
		*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (*reinterpret_cast<unsigned int*>(mon + 0x560) * 0x48 + 0x22));
	*reinterpret_cast<unsigned int*>(mon + 0x638) =
		*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (*reinterpret_cast<unsigned int*>(mon + 0x560) * 0x48 + 0x22));
}

/*
 * --INFO--
 * PAL Address: 0x80119278
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onCancelStat(int state)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	(this->*m_funcs->cancelStat)();

	switch (*reinterpret_cast<int*>(mon + 0x520)) {
	case 0x1D:
		object->CancelMove(1);
		break;

	case 0x16:
		m_unk6B9 = 0;
		object->SetAnimSlot(0, 0);
		object->SetAnimSlot(1, 1);
		object->SetAnimSlot(4, 4);
		object->SetAnimSlot(6, 6);
		break;

	case 0x17:
		m_unk6B9 = 1;
		object->SetAnimSlot(0x28, 0);
		object->SetAnimSlot(0x29, 1);
		object->SetAnimSlot(0x2A, 4);
		object->SetAnimSlot(0x2B, 6);
		break;

	case 0x21:
		*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
		memset(&m_moveWork, 0, sizeof(m_moveWork));
		if ((m_moveWork.m_stateFlags & 2) == 0) {
			(this->*m_funcs->moveCancel)();
		}
		break;

	case 0x18:
		m_actionBranch = 1;
		object->SetAnimSlot(0, 0);
		object->SetAnimSlot(4, 4);
		object->m_bgColMask |= 0x50000;
		object->m_bgColMask &= 0xFFFFFFF7;
		object->m_objectFlags &= 0xFFFFFFEF;
		break;
	}

	CGCharaObj::onCancelStat(state);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::isValidTarget()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
#define script9 (reinterpret_cast<unsigned char*>(reinterpret_cast<CGObject*>(this)->m_scriptHandle[9]))
	float maxDist = static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0xCC));
	float homeDist = PSVECDistance(&m_homePosition, reinterpret_cast<Vec*>(mon + 0x15C));
	unsigned char* aiData;

	if (m_aiState == 0) {
		aiData = script9;
	} else {
		aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
		         (m_aiState + *reinterpret_cast<unsigned short*>(script9 + 0x100)) *
		             0x1D0 +
		         0x10;
	}

	unsigned short aiFlags = *reinterpret_cast<unsigned short*>(aiData + 0x102);
	if ((m_targetPartyIndex >= 0) &&
	    ((aiFlags & 0x20) != 0)) {
		*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
		memset(&m_moveWork, 0, sizeof(m_moveWork));
		m_chaseState = 2;
		m_chaseTimer = 0;
		m_chaseDirty = 1;
		return;
	}

	if (((aiFlags & 0x20) != 0) ||
	    ((*reinterpret_cast<unsigned short*>(script9 + 0xFE) & 8) != 0)) {
		*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
		memset(&m_moveWork, 0, sizeof(m_moveWork));
		m_chaseState = 0;
		m_chaseTimer = 0;
		m_chaseDirty = 1;
		return;
	}

	if (*reinterpret_cast<unsigned short*>(script9 + 0x10C) == 1) {
		*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x21;
		if (m_moveWork.m_mode != 3) {
			memset(&m_moveWork, 0, sizeof(m_moveWork));
			m_moveWork.m_flags = 0x806;
			m_moveWork.m_mode = 3;
		}
		m_moveWork.m_targetPos = m_homePosition;
	}

	if (((*reinterpret_cast<unsigned short*>(script9 + 0x10C) != 1) || (m_moveWork.m_frame < 0x19)) &&
	    ((*reinterpret_cast<unsigned short*>(script9 + 0x10C) == 1) || (homeDist >= kMonObjHalf * maxDist))) {
		goto check_home;
	}

	{
		double soundLimit = kMonObjNormalSoundRange;
		if (Game.m_gameWork.m_soundOptionFlag != 0) {
			soundLimit = kMonObjWideSoundRange;
		}

		int partyIndex = -1;
		if (soundLimit > static_cast<double>(*reinterpret_cast<float*>(mon + 0x5BC))) {
			float hitScale;
			checkCol(6, *reinterpret_cast<float*>(mon + 0x1A8),
			         static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0xC8)),
			         &hitScale, &partyIndex);
			if (partyIndex < 0) {
				partyIndex = -1;
			}
		}

		if (partyIndex >= 0) {
			m_targetPartyIndex = partyIndex;
			if (*reinterpret_cast<unsigned short*>(script9 + 0x10C) == 1) {
				m_chaseState = 2;
			} else {
				m_chaseState = 1;
			}
			m_chaseTimer = 0;
			m_chaseDirty = 1;
			return;
		}
	}

check_home:
	if ((homeDist < kMonObjHomeSnapDistance) ||
	    (static_cast<unsigned int>(m_chaseTimer) == *reinterpret_cast<unsigned short*>(script9 + 0x1B8))) {
		m_homePosition = *reinterpret_cast<Vec*>(mon + 0x15C);
		*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
		memset(&m_moveWork, 0, sizeof(m_moveWork));
		m_chaseState = 0;
		m_chaseTimer = 0;
		m_chaseDirty = 1;
	} else if (*reinterpret_cast<unsigned short*>(script9 + 0x10C) != 1) {
		*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x1C;
	}
#undef script9
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
void CGMonObj::seKiduki()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	if (m_unk6BE != 0) {
		return;
	}

	bool notice = false;
	int partyIndex;

	if (m_unk6BD != 0) {
		partyIndex = m_targetPartyIndex;
	} else {
		double soundLimit = (Game.m_gameWork.m_soundOptionFlag != 0) ? kMonObjWideSoundRange : kMonObjNormalSoundRange;

		if (static_cast<double>(*reinterpret_cast<float*>(mon + 0x5BC)) < soundLimit) {
			int* scriptHandle = *reinterpret_cast<int**>(mon + 0x58);
			unsigned char* script = reinterpret_cast<unsigned char*>(scriptHandle[9]);
			float hitScale;

			checkCol(6, *reinterpret_cast<float*>(mon + 0x1A8),
			         static_cast<float>(*reinterpret_cast<unsigned short*>(script + 0xC8)),
			         &hitScale, &partyIndex);
			if (partyIndex >= 0) {
				goto haveNotice;
			}
		}
		partyIndex = -1;
	}

haveNotice:
	if (partyIndex >= 0) {
		int action = m_actionBranch;
		int* scriptHandle = *reinterpret_cast<int**>(mon + 0x58);
		unsigned char* script = reinterpret_cast<unsigned char*>(scriptHandle[9]);
		unsigned short noticeFlags = *reinterpret_cast<unsigned short*>(script + 0xFE);

		if ((action == 0) && ((noticeFlags & 0x80) != 0)) {
			notice = true;
			*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x32;
		} else if ((action == 0) && ((noticeFlags & 0x20) != 0)) {
			notice = true;
			*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x33;
		} else if ((action == 0) && (((noticeFlags & 0x40) != 0) || (scriptHandle[4] == 0x39))) {
			notice = true;
			*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x34;
		}
	}

	int classId = (*reinterpret_cast<int**>(mon + 0x58))[4];
	if (classId != 0x70) {
		if (classId < 0x70) {
			if (classId == 0x6A) {
				notice = true;
				*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x35;
			}
		} else if (classId == 0x7B) {
			notice = true;
		}
	} else {
		notice = true;
	}

	if (notice) {
		if (classId == 0x7B) {
			m_chaseState = 0;
			m_chaseTimer = 0;
			m_chaseDirty = 1;
		} else if (m_unk6BD == 0) {
			m_chaseState = 2;
			m_chaseTimer = 0;
			m_chaseDirty = 1;
		} else {
			m_chaseState = 2;
			m_chaseTimer = 0;
			m_chaseDirty = 1;
		}

		m_targetPartyIndex = partyIndex;
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
		if (*reinterpret_cast<unsigned short*>(object->m_scriptHandle + 7) != 0) {
			int targetPartyIndex = m_targetPartyIndex;
			int hasValidTarget;
			if ((targetPartyIndex < 0) ||
				((targetPartyIndex >= 0) &&
				 (*reinterpret_cast<unsigned short*>(reinterpret_cast<CGObject*>(Game.m_partyObjArr[targetPartyIndex])->m_scriptHandle + 7) == 0))) {
				hasValidTarget = 0;
			} else {
				hasValidTarget = 1;
			}
			if (!hasValidTarget) {
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
		if ((prgObj->m_stateFrame == 0) && (object->CancelAnim(1), m_unk6B8 == 0)) {
			void** scriptHandle = object->m_scriptHandle;
			int rand = Math.Rand(3);
			unsigned char* script9 = reinterpret_cast<unsigned char*>(scriptHandle[9]);
			prgObj->playSe3D(
				static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(script9 + 0x192)) +
				(static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(script9 + 0x190)) * 1000 + rand),
				0x32, 0x96, 0, (Vec*)0);
			m_unk6B8 = 1;
		}

		int targetPartyIndex = m_targetPartyIndex;
		if ((targetPartyIndex >= 0) && (targetPartyIndex < 4)) {
			CGPartyObj* target = Game.m_partyObjArr[targetPartyIndex];
			Vec src = reinterpret_cast<CGObject*>(target)->m_worldPosition;
			Vec delta;
			PSVECSubtract(&src, &object->m_worldPosition, &delta);
			float speedScale = *reinterpret_cast<float*>(mon + 0x690) *
				(0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xD4)) + 0.8f);
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
			(0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xD4)) + 0.8f);
		object->MoveVector(&delta, speedScale, 1, 1, 0, 1);
		break;
	}


	case 0x11: {
		if (prgObj->m_stateFrame == 0) {
			prgObj->reqAnim(-1, 0, 0);
		}

		short aiState = m_aiState;
		unsigned char* aiData;
		if (aiState == 0) {
			aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
		} else {
			aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
				(aiState + *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x100)) * 0x1D0 + 0x10;
		}
		unsigned char* script9 = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
		float range = static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0xCE));

		if (*reinterpret_cast<unsigned short*>(aiData + 0x10A) == 2) {
			if (*reinterpret_cast<unsigned short*>(script9 + 0x10C) == 1) {
				if (prgObj->m_subState == 0) {
					unsigned int chaseFlag = 0;
					unsigned char* aiData2 = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
					if (aiState != 0) {
						aiData2 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(aiState + *reinterpret_cast<unsigned short*>(aiData2 + 0x100)) * 0x1D0 + 0x10;
					}
					if ((*reinterpret_cast<unsigned short*>(aiData2 + 0x102) & 0x10) != 0) {
						chaseFlag = 0x8000;
					}
					CGPartyObj* target = Game.m_partyObjArr[m_targetPartyIndex];
					if (m_moveWork.m_mode != 4) {
						memset(&m_moveWork, 0, 0x34);
						m_moveWork.m_flags = 0x855;
						if ((*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFE) & 4) != 0) {
							m_moveWork.m_flags |= 0x400;
						}
						unsigned char* aiData3;
						if (m_aiState == 0) {
							aiData3 = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
						} else {
							aiData3 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
								(m_aiState + *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x100)) * 0x1D0 + 0x10;
						}
						if ((*reinterpret_cast<unsigned short*>(aiData3 + 0x102) & 0x80) != 0) {
							m_moveWork.m_flags |= 0x20000;
						}
						m_moveWork.m_flags |= chaseFlag;
						m_moveWork.m_flags = m_moveWork.m_flags;
						m_moveWork.m_mode = 4;
						m_moveWork.m_range =
							static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xCE));
						m_moveWork.m_limitFrame =
							*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1B6);
					}
					m_moveWork.m_target = reinterpret_cast<CGCharaObj*>(target);
					moveFrame();
					if (((m_moveWork.m_stateFlags & 1) != 0) ||
						(static_cast<int>((static_cast<unsigned int>(object->m_stateFlags0) << 25) | (static_cast<unsigned int>(object->m_stateFlags0) >> 7)) < 0)) {
						prgObj->reqAnim(-1, 0, 0);
						if (-1 < m_targetPartyIndex) {
							object->m_rotTargetY = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]));
						}
						prgObj->m_subState = 1;
					}
				}
			} else {
				if ((prgObj->m_stateFrame == 0) &&
					(*reinterpret_cast<float*>(mon + 0x5D0 + m_targetPartyIndex * 4) < range)) {
					prgObj->m_subState = 1;
				}
				if (prgObj->m_subState == 1) {
					unsigned char* script9b = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
					unsigned int limit = *reinterpret_cast<unsigned short*>(script9b + 0x1B6);
					if (static_cast<int>(prgObj->m_stateFrame) <= static_cast<int>(limit)) {
						if ((static_cast<int>((static_cast<unsigned int>(object->m_stateFlags0) << 25) | (static_cast<unsigned int>(object->m_stateFlags0) >> 7)) < 0) ||
							(static_cast<unsigned int>(prgObj->m_stateFrame) == limit) ||
							(range <= *reinterpret_cast<float*>(mon + 0x5D0 + m_targetPartyIndex * 4))) {
							prgObj->m_subState = 0;
							object->m_rotTargetY = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]));
						} else {
							float speedScale = *reinterpret_cast<float*>(mon + 0x690) *
								(0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(script9b + 0xD4)) + 0.8f);
							CVector targetVec(reinterpret_cast<CGObject*>(Game.m_partyObjArr[m_targetPartyIndex])->m_worldPosition);
							CVector myVec(object->m_worldPosition);
							CVector diff;
							PSVECSubtract(static_cast<Vec*>(myVec), static_cast<Vec*>(targetVec), static_cast<Vec*>(diff));
							Vec delta;
							delta.x = diff.x;
							delta.y = diff.y;
							delta.z = diff.z;
							object->moveVector(&delta, speedScale, 1);
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
		if (prgObj->m_stateFrame == 0) {
			prgObj->reqAnim(-1, 0, 0);
		}
		if (Math.Rand(0x32) == 0) {
			if (Math.Rand(2) == 0) {
				object->m_rotTargetY += 0.2f;
			} else {
				object->m_rotTargetY -= 0.2f;
			}
		}
		break;


	case 0x1D:
		SET_DRAW_FLAG();
		if (prgObj->m_subState == 1) {
			if (Math.Rand(100) == 0) {
				prgObj->changeSubStat(0);
			}
		} else if ((prgObj->m_subState < 1) && (-1 < prgObj->m_subState)) {
			if (prgObj->m_subFrame == 0) {
				void** scriptHandle = object->m_scriptHandle;
				int rand = Math.Rand(0x50);
				float randF = Math.RandF();
				float speedScale = *reinterpret_cast<float*>(mon + 0x690) *
					(0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle[9]) + 0xD4)) + 0.8f);
				object->moveVectorRot(kMonObjTwo * (FLOAT_803319C4 * randF), 0.0f, kMonObjQuarter * speedScale, rand + 10);
			} else {
				unsigned char weaponFlags1 = object->m_weaponNodeFlagBytes.m_flags1;
				if ((static_cast<int>((static_cast<unsigned int>(weaponFlags1) << 26) | (static_cast<unsigned int>(weaponFlags1) >> 6)) >= 0) ||
					(static_cast<int>((static_cast<unsigned int>(object->m_stateFlags0) << 25) | (static_cast<unsigned int>(object->m_stateFlags0) >> 7)) < 0)) {
					object->CancelMove(1);
					prgObj->changeSubStat(1);
				}
			}
		}
		break;


	case 0x1E: {
		float speedScale = *reinterpret_cast<float*>(mon + 0x690) *
			(0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xD4)) + 0.8f);
		CVector targetVec(reinterpret_cast<CGObject*>(Game.m_partyObjArr[m_targetPartyIndex])->m_worldPosition);
		CVector myVec(object->m_worldPosition);
		CVector diff;
		PSVECSubtract(static_cast<Vec*>(myVec), static_cast<Vec*>(targetVec), static_cast<Vec*>(diff));
		Vec delta;
		delta.x = diff.x;
		delta.y = diff.y;
		delta.z = diff.z;
		object->moveVector(&delta, speedScale, 1);

		unsigned char* script9 = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
		if ((static_cast<unsigned int>(prgObj->m_stateFrame) == *reinterpret_cast<unsigned short*>(script9 + 0x1B6)) ||
			(static_cast<float>(*reinterpret_cast<unsigned short*>(script9 + 0xCE)) <= *reinterpret_cast<float*>(mon + 0x5D0 + m_targetPartyIndex * 4)) ||
			(static_cast<int>((static_cast<unsigned int>(object->m_stateFlags0) << 25) | (static_cast<unsigned int>(object->m_stateFlags0) >> 7)) < 0)) {
			prgObj->changeStat(0, 0, 0);
			if (-1 < m_targetPartyIndex) {
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
			void* classId = object->m_scriptHandle[4];
			int anim;
			unsigned int soundId;
			if ((reinterpret_cast<unsigned int>(classId) - 0x10 < 3) || (classId == reinterpret_cast<void*>(0x5E))) {
				anim = 0xF;
				soundId = 0x2EF1;
			} else {
				anim = 0xD;
				soundId = 0xCB37;
			}
			*reinterpret_cast<float*>(mon + 0x694) = kMonObjDefaultScale;
			object->m_weaponNodeFlagBytes.m_flags0 = (object->m_weaponNodeFlagBytes.m_flags0 & 0xEF) | 0x10;
			object->m_groundHitOffset.z = 0.0f;
			object->m_groundHitOffset.y = 0.0f;
			object->m_groundHitOffset.x = 0.0f;
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
				if (classId == reinterpret_cast<void*>(0x5E)) {
					int dataNo = object->m_charaModelHandle->GetPdtSlot();
					prgObj->putParticle((dataNo << 8) | 8, 0, object, kMonObjDefaultScale, 0);
				} else {
					int dataNo = object->m_charaModelHandle->GetPdtSlot();
					prgObj->putParticle((dataNo << 8) | 7, 0, object, kMonObjDefaultScale, 0);
				}
			} else {
				int dataNo = object->m_charaModelHandle->GetPdtSlot();
				prgObj->putParticle((dataNo << 8) | 2, 2, object, kMonObjDefaultScale, 0);
			}
		}
		if (prgObj->isLoopAnim() != 0) {
			prgObj->changeStat(0, 0, 0);
			object->m_bgColMask |= 0xD0002;
			enableDamageCol(1);
			*reinterpret_cast<int*>(mon + 0x6B0) = 1;
		}
		break;
	}


	case 0x33: {
		if (prgObj->m_stateFrame == 0) {
			void* classId = object->m_scriptHandle[4];
			*reinterpret_cast<float*>(mon + 0x694) = kMonObjDefaultScale;
			unsigned int clz = __cntlzw(0x3C - reinterpret_cast<int>(classId));
			object->m_weaponNodeFlagBytes.m_flags0 = (object->m_weaponNodeFlagBytes.m_flags0 & 0xEF) | 0x10;
			object->m_groundHitOffset.z = 0.0f;
			object->m_groundHitOffset.y = 0.0f;
			object->m_groundHitOffset.x = 0.0f;
			object->m_bgColMask |= 0x11;
			object->m_displayFlags |= 1;
			prgObj->reqAnim(0xD, 0, 0);
			prgObj->playSe3D((clz >> 5) + 0x7936, 0x32, 0x96, 0, (Vec*)0);
			int dataNo = object->m_charaModelHandle->GetPdtSlot();
			prgObj->putParticle((dataNo << 8) | 4, 0, object, kMonObjDefaultScale, 0);
		}
		if (prgObj->isLoopAnim() != 0) {
			prgObj->changeStat(0, 0, 0);
			object->m_bgColMask |= 0xD0002;
			enableDamageCol(1);
			*reinterpret_cast<int*>(mon + 0x6B0) = 1;
		}
		break;
	}


	case 0x34: {
		if (prgObj->m_stateFrame == 0) {
			unsigned int particleBase;
			unsigned int soundId;
			if (object->m_scriptHandle[4] == reinterpret_cast<void*>(0x39)) {
				particleBase = 4;
				soundId = 0xC36E;
			} else {
				particleBase = 5;
				soundId = 0xB3D1;
			}
			object->m_weaponNodeFlagBytes.m_flags0 = (object->m_weaponNodeFlagBytes.m_flags0 & 0xEF) | 0x10;
			object->m_groundHitOffset.z = 0.0f;
			object->m_groundHitOffset.y = 0.0f;
			object->m_groundHitOffset.x = 0.0f;
			object->m_bgColMask |= 0x11;
			object->m_displayFlags |= 1;
			prgObj->reqAnim(0xB, 0, 0);
			prgObj->playSe3D(soundId, 0x32, 0x96, 0, (Vec*)0);
			int dataNo = object->m_charaModelHandle->GetPdtSlot();
			prgObj->putParticle(particleBase | (dataNo << 8), 0, object, kMonObjDefaultScale, 0);
		}
		if (prgObj->isLoopAnim() != 0) {
			prgObj->changeStat(0, 0, 0);
			object->m_bgColMask |= 0xD0002;
			enableDamageCol(1);
			object->m_displayFlags |= 1;
			*reinterpret_cast<int*>(mon + 0x6B0) = 1;
			object->SetAnimSlot(0, 0);
			if (object->m_scriptHandle[4] == reinterpret_cast<void*>(0x39)) {
				object->SetAnimSlot(1, 1);
				object->SetAnimSlot(4, 4);
				object->SetAnimSlot(6, 6);
			}
		}
		break;
	}


	case 0x35:
		if (prgObj->m_stateFrame == 0) {
			*reinterpret_cast<float*>(mon + 0x694) = kMonObjDefaultScale;
			object->m_displayFlags |= 1;
			float speedScale = *reinterpret_cast<float*>(mon + 0x690) *
				(0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xD4)) + 0.8f);
			object->moveVectorRot(object->m_rotBaseY, 0.0f, speedScale, 0x14);
		}
		if (prgObj->m_stateFrame == 0x10) {
			object->m_bgColMask |= 0xD0002;
			prgObj->changeStat(0, 0, 0);
		}
		break;


	case 0x36:
		if (prgObj->m_subState != 0) {
			if (prgObj->m_subState == 1) {
				if (prgObj->m_subFrame == 0) {
					prgObj->reqAnim(0x10, 0, 0);
				} else if (prgObj->isLoopAnim() != 0) {
					prgObj->changeStat(0, 0, 0);
				}
			}
			break;
		}
		if (prgObj->m_subFrame == 0) {
			int dataNo = object->m_charaModelHandle->GetPdtSlot();
			prgObj->putParticle((dataNo << 8) | 4, 0, object, kMonObjDefaultScale, 0);
			prgObj->reqAnim(0xF, 1, 0);
			unsigned int soundId = 0;
			void* classId = object->m_scriptHandle[4];
			if (classId == reinterpret_cast<void*>(0xA7)) {
				soundId = 0x12130;
			} else if (reinterpret_cast<int>(classId) < 0xA7) {
				if (classId == reinterpret_cast<void*>(0x9C)) {
					soundId = 0x12130;
				}
			} else if (classId == reinterpret_cast<void*>(0xA9)) {
				soundId = 0x1213A;
			} else if (reinterpret_cast<int>(classId) < 0xA9) {
				soundId = 0x12126;
			}
			prgObj->playSe3D(soundId, 0x32, 0x96, 0, (Vec*)0);
		}
		if (prgObj->m_subFrame == 0x32) {
			prgObj->changeSubStat(1);
		}
		break;

	case 0x18:
		if (prgObj->m_stateFrame == 0) {
			*reinterpret_cast<int*>(mon + 0x6B0) = 1;
			prgObj->reqAnim(0x10, 0, 0);
			object->SetAnimSlot(0, 0);
			object->SetAnimSlot(4, 4);
			object->m_bgColMask = (object->m_bgColMask | 0x50000) & 0xFFFFFFF7;
			object->m_displayFlags &= 0xFFFFFFEF;
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

				if ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (*reinterpret_cast<int*>(mon + 0x560) * 0x48 + 0x32)) & 2) == 0) {
					float rotLimit = kMonObjDegToRad *
						static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x19C));
					if (m_targetPartyIndex >= 0) {
						float targetRot = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[m_targetPartyIndex]));
						if (rotLimit > kMonObjTwoThirdsPi) {
							object->m_rotTargetY = targetRot;
						} else {
							float delta = Math.DstRot(targetRot, *reinterpret_cast<float*>(&object->m_bgFlags));
							float clamped = -rotLimit;
							if (!(delta < clamped)) {
								if (rotLimit < delta) {
									clamped = rotLimit;
								} else {
									clamped = delta;
								}
							}
							object->m_rotTargetY = *reinterpret_cast<float*>(&object->m_bgFlags) + clamped;
						}
					}
				}

				CGPrgObj* targetPrg = reinterpret_cast<CGPrgObj*>(target);
				targetPrg->bonus(0x17, *reinterpret_cast<int*>(mon + 0x560), targetPrg);
			}

			CGCharaObj::putParticleFromItem(
				*reinterpret_cast<int*>(mon + 0x560), 0, *reinterpret_cast<int*>(mon + 0x570), (Vec*)0);
			CGCharaObj::putParticleFromItem(
				*reinterpret_cast<int*>(mon + 0x560), 1, *reinterpret_cast<int*>(mon + 0x570), (Vec*)0);
		}
		return;

	case 1:
		if (*reinterpret_cast<int*>(mon + 0x68C) < prgObj->m_subFrame) {
			prgObj->changeSubStat(2);
		}
		return;
	}

	if ((prgObj->m_subState < 3) && (prgObj->isLoopAnim() != 0)) {
		CGMonObj_SetAttackAfter(this, *reinterpret_cast<int*>(mon + 0x560));
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

	if ((param3 < 0xC) && (param3 >= 0xA)) {
		unsigned char* scriptData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
		particleId = *reinterpret_cast<unsigned short*>(scriptData + 0x1A4);
		if ((particleId != 0xFFFF) && (param3 == 10)) {
			particleId += 1;
		}
		soundId = *reinterpret_cast<unsigned short*>(scriptData + 0x1A6);
	}

	if (particleId != 0xFFFF) {
		int dataNo = object->m_charaModelHandle->GetPdtSlot();
		reinterpret_cast<CGPrgObj*>(this)->putParticle(particleId | (dataNo << 8), 0, object, kMonObjDefaultScale, 0);
	}

	if (soundId != 0xFFFF) {
		if (soundId != 0xFFFF) {
			soundEffect = (soundId & 0xFF) + ((int)soundId >> 8) * 1000;
		} else {
			soundEffect = 0;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::enableAttackCol(int enabled, int, int)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	if (enabled != 0) {
		int attackKind = *reinterpret_cast<int*>(mon + 0x560);
		unsigned char* attackData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]) +
			attackKind * 0x48;
		unsigned int colMask = *reinterpret_cast<unsigned short*>(attackData + 0xC);
		unsigned int colValue;
		if (attackKind >= 0x1F5) {
			colValue = *reinterpret_cast<unsigned short*>(attackData + 2);
		} else {
			colValue = 1;
		}

		for (int i = 0; i < 8; i++) {
			if ((((int)colMask >> i) & 1) != 0) {
				if (i == -1) {
					*reinterpret_cast<unsigned int*>(mon + 0x20C) = colValue;
					*reinterpret_cast<unsigned int*>(mon + 0x23C) = colValue;
					*reinterpret_cast<unsigned int*>(mon + 0x26C) = colValue;
					*reinterpret_cast<unsigned int*>(mon + 0x29C) = colValue;
					*reinterpret_cast<unsigned int*>(mon + 0x2CC) = colValue;
					*reinterpret_cast<unsigned int*>(mon + 0x2FC) = colValue;
					*reinterpret_cast<unsigned int*>(mon + 0x32C) = colValue;
					*reinterpret_cast<unsigned int*>(mon + 0x35C) = colValue;
				} else {
					*reinterpret_cast<unsigned int*>(mon + 0x20C + i * 0x30) = colValue;
				}
			}
		}
	} else {
		*reinterpret_cast<unsigned int*>(mon + 0x20C) = 0;
		*reinterpret_cast<unsigned int*>(mon + 0x23C) = 0;
		*reinterpret_cast<unsigned int*>(mon + 0x26C) = 0;
		*reinterpret_cast<unsigned int*>(mon + 0x29C) = 0;
		*reinterpret_cast<unsigned int*>(mon + 0x2CC) = 0;
		*reinterpret_cast<unsigned int*>(mon + 0x2FC) = 0;
		*reinterpret_cast<unsigned int*>(mon + 0x32C) = 0;
		*reinterpret_cast<unsigned int*>(mon + 0x35C) = 0;
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
	CGObject* object = reinterpret_cast<CGObject*>(this);

	unsigned int& damageCol1X =
		*reinterpret_cast<unsigned int*>(&object->m_damageColliders[1].m_localPosition.x);
	unsigned int& damageCol2X =
		*reinterpret_cast<unsigned int*>(&object->m_damageColliders[2].m_localPosition.x);

	if (enabled != 0) {
		damageCol1X = 1;
		damageCol2X = 1;
	} else {
		damageCol1X = 0;
		damageCol2X = 0;
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
	CGObject* object = reinterpret_cast<CGObject*>(this);

	switch (state) {
	case 0:
	case 3:
	case 0x1C:
		if (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId == state) {
			state = -1;
		}
		break;
	default:
	if ((state < -4) && (-0xE <= state)) {
		unsigned short action = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + ((state + 0xE) * 2 + 0xD0));
		unsigned short actionType = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (action * 0x48 + 0xE));
		switch (actionType) {
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
	} else {
		state = CGCharaObj::getReplaceStat(state);
	}
		break;
	}

	return state;
}

/*
 * --INFO--
 * PAL Address: 0x801179BC
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onStatShield()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	if (*reinterpret_cast<int*>(mon + 0x52C) == 1) {
		int subFrame = *reinterpret_cast<int*>(mon + 0x530);
		int action = *reinterpret_cast<int*>(mon + 0x560);
		int waitFrame = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + (action * 0x48 + 0x2E));

		if (subFrame == waitFrame) {
			reinterpret_cast<CGPrgObj*>(this)->changeSubStat(3);
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
			unsigned char* aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
			reinterpret_cast<CGPrgObj*>(this)->playSe3D(
				*reinterpret_cast<unsigned short*>(aiData + 0x190) * 1000 + *reinterpret_cast<unsigned short*>(aiData + 0x192) + 9,
				0x32,
				0x96,
				0,
				(Vec*)0
			);

			int pId = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x19E);
			if (pId != 0xFFFF) {
				int dataNo = -1;
				dataNo = object->m_charaModelHandle->GetPdtSlot();
				reinterpret_cast<CGPrgObj*>(this)->putParticle(pId | (dataNo << 8), 0, object, kMonObjParticleRadiusScale * object->m_attackColRadius, 0);
			}

			int option = *reinterpret_cast<short*>(&Game.m_gameWork.m_optionValue);
			if (option < 9 && m_repop.delay == 0) {
				int shift = reinterpret_cast<int>(object->m_scriptHandle[2]);
				unsigned long long bit = 1ULL << shift;
				CFlatSpawnBitHi(option) |= static_cast<unsigned int>(bit);
				CFlatSpawnBitLo(option) |= static_cast<unsigned int>(bit >> 32);
			}
			return;
		}

		if (reinterpret_cast<CGPrgObj*>(this)->isLoopAnimDirect() != 0) {
			reinterpret_cast<CGPrgObj*>(this)->changeSubStat(1);
		}
		return;

	case 1: {
		unsigned char* aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
		int subFrame = *reinterpret_cast<int*>(mon + 0x530);

		if ((*reinterpret_cast<unsigned short*>(aiData + 0xFE) & 2) == 0) {
			if (subFrame != 0) {
				return;
			}
		} else {
			if (subFrame == 0) {
				int particleId = *reinterpret_cast<int*>(mon + 0x560);
				void* classId = object->m_scriptHandle[4];
				if (classId == reinterpret_cast<void*>(5)) {
					particleId = 599;
				} else if (reinterpret_cast<int>(classId) < 5) {
					if (3 < reinterpret_cast<int>(classId)) {
						particleId = 0x253;
					}
				} else if (reinterpret_cast<int>(classId) < 7) {
					particleId = 0x25B;
				}

				*reinterpret_cast<int*>(mon + 0x560) = particleId;
				CGCharaObj::putParticleFromItem(*reinterpret_cast<int*>(mon + 0x560), 0, *reinterpret_cast<int*>(mon + 0x564), (Vec*)0);
				CGCharaObj::putParticleFromItem(*reinterpret_cast<int*>(mon + 0x560), 1, *reinterpret_cast<int*>(mon + 0x564), (Vec*)0);
				CGCharaObj::putParticleFromItem(*reinterpret_cast<int*>(mon + 0x560), 2, *reinterpret_cast<int*>(mon + 0x564), (Vec*)0);
				CGCharaObj::putParticleFromItem(*reinterpret_cast<int*>(mon + 0x560), 3, *reinterpret_cast<int*>(mon + 0x564), (Vec*)0);
				return;
			}
			if (subFrame != 0x19) {
				return;
			}
		}

		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x231000);
		*reinterpret_cast<float*>(mon + 0x694) = kMonObjZero;
		enableAttackCol(0, 0, 0);
		object->m_bgColMask &= 0xFFF6FFFD;
		reinterpret_cast<CGPrgObj*>(this)->playSe3D(0x17, 0x32, 0x96, 0, (Vec*)0);
		reinterpret_cast<CGPrgObj*>(this)->putParticle(0x116, 0, object, kMonObjParticleRadiusScale * object->m_attackColRadius, 0);
		CGItemObj::CreateFromScript(1, 0, 0, object, kMonObjZero, 0);
		object->PutDropItem();
		reinterpret_cast<CGPrgObj*>(this)->changeSubStat(2);
		return;
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

	if ((((static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags)) << 24) & 0xC0000000) >> 31) != 0) &&
			(CFlatCenterState() == 0)) &&
		((*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&DbgMenuPcs) + 0x6484) & 0x80) != 0)) {
		char text[0x100];
		unsigned short aiState = static_cast<unsigned short>(m_aiState);
		int targetIndex = m_targetPartyIndex;
		int targetChar = '-';
		int aiChar = '-';

		if (targetIndex >= 0) {
			targetChar = targetIndex + '0';
		}
		if ((aiState & 0x7FFF) != 0) {
			aiChar = (aiState & 0x7FFF) + 0x40;
		}

		sprintf(text, s_monObjAiStateFmt, (int)object->m_scriptHandle[2], aiChar,
		        m_actionBranch, targetChar);
		font->SetPosX(posX - static_cast<float>(font->GetWidth(text)) * 0.5f);
		font->SetPosY(posY);
		font->SetPosZ(posZ);
		font->Draw(text);
		posY -= static_cast<float>(font->m_glyphWidth) * font->scaleY;

		int targetDist = 0;
		if (targetIndex >= 0) {
			targetDist = static_cast<int>(*reinterpret_cast<float*>(mon + targetIndex * 4 + 0x5D0));
		}

		int chaseRange = static_cast<int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xCC));
		int spawnDist = static_cast<int>(PSVECDistance(&m_homePosition, &object->m_worldPosition));
		sprintf(text, s_monObjDistanceFmt, targetDist, spawnDist, chaseRange);
		font->SetPosX(posX - static_cast<float>(font->GetWidth(text)) * 0.5f);
		font->SetPosY(posY);
		font->SetPosZ(posZ);
		font->Draw(text);
		posY -= static_cast<float>(font->m_glyphWidth) * font->scaleY;
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
#define prgScript (*reinterpret_cast<void***>(reinterpret_cast<unsigned char*>(prgObj) + 0x58))

	m_unk6BF = 1;

	unsigned short prgFlags = static_cast<unsigned short>(prgObj->GetCID());
	if ((prgFlags & 0x6D) == 0x6D) {
		unsigned char* aiData;
		if (m_aiState == 0) {
			aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
		} else {
			aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
				(m_aiState +
					*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x100)) * 0x1D0 + 0x10;
		}

		int attackerIndex = reinterpret_cast<int>(prgScript[0xED]);
		if ((static_cast<int>(*reinterpret_cast<unsigned short*>(aiData + 0x106)) == 1) || (m_targetPartyIndex < 0)) {
			if ((static_cast<unsigned int>(Game.m_gameWork.m_menuStageMode) != 0) && (Game.m_gameWork.m_bossArtifactStageIndex < 0xF)) {
				prgFlags = static_cast<unsigned short>(prgObj->GetCID());
				if ((prgFlags & 0x6D) == 0x6D) {
					if (reinterpret_cast<int>(prgScript[0xED]) != 0) {
						goto skip_target_update;
					}
				}
			}
			m_targetPartyIndex = attackerIndex;
		}

skip_target_update:
		int teamNo = reinterpret_cast<int>(object->m_scriptHandle[2]);
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(prgObj) + 0x6C0) = teamNo;
		GbaQue.SetHitEnemy(reinterpret_cast<int>(prgScript[0xED]), teamNo);

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

				void** otherScript = reinterpret_cast<CGObject*>(other)->m_scriptHandle;
				if (*reinterpret_cast<unsigned short*>(otherScript + 7) == 0) {
					continue;
				}
				if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(otherScript) + 0x3E) != 0) {
					continue;
				}
				if (*reinterpret_cast<unsigned short*>(otherScript + 0x14) != 0) {
					continue;
				}
				if (*reinterpret_cast<unsigned short*>(otherScript + 0x11) != 0) {
					continue;
				}

				other->m_targetPartyIndex = reinterpret_cast<int>(prgScript[0xED]);
				other->m_unk6BD = 1;

				int otherClassId = reinterpret_cast<int>(reinterpret_cast<CGObject*>(other)->m_scriptHandle[4]);
				if (other->m_chaseState != 4) {
					other->m_chaseState = 2;
					other->m_chaseTimer = 0;
					other->m_chaseDirty = 1;
				} else if ((other->m_actionBranch == 0) && (otherClassId == 0x55)) {
					reinterpret_cast<CGPrgObj*>(other)->changeStat(0x18, 0, 0);
					other->m_chaseState = 2;
					other->m_chaseTimer = 0;
					other->m_chaseDirty = 1;
				}
			}
		}
	}

	if (*reinterpret_cast<int*>(mon + 0x520) == 0x11) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0, 0, 0);
	}

	int classId = reinterpret_cast<int>(object->m_scriptHandle[4]);
	if ((m_actionBranch == 0) && (classId == 0x55)) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0x18, 0, 0);
	}

	m_chaseState = 2;
	m_chaseTimer = 0;
	m_chaseDirty = 1;

	if (m_funcs->damaged != 0) {
		(this->*m_funcs->damaged)();
	}
#undef prgScript
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::link(CGPartyObj*, CGMonObj*)
{
	// TODO
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
		*hitScale = kMonObjDefaultScale;
	}
	if (hitPartyIndex != NULL) {
		*hitPartyIndex = -1;
	}

	CVector startPos;
	CVector forward;
	CVector move;
	{
		CVector tmp(object->m_worldPosition.x, object->m_worldPosition.y, object->m_worldPosition.z);
		startPos.x = tmp.x;
		startPos.y = tmp.y;
		startPos.z = tmp.z;
	}
	{
		float sinY = static_cast<float>(sin(static_cast<double>(rotY)));
		float cosY = static_cast<float>(cos(static_cast<double>(rotY)));
		CVector tmp(sinY, kMonObjZero, cosY);
		forward.x = tmp.x;
		forward.y = tmp.y;
		forward.z = tmp.z;
	}
	{
		CVector scaled;
		PSVECScale(reinterpret_cast<Vec*>(&forward), reinterpret_cast<Vec*>(&scaled), distance);
		move.x = scaled.x;
		move.y = scaled.y;
		move.z = scaled.z;
	}

	unsigned char* aiScript;
	if (m_aiState == 0) {
		aiScript = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
	} else {
		aiScript = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
			(static_cast<int>(m_aiState) +
			 *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x100)) * 0x1D0 + 0x10;
	}

	unsigned short aiFlags = *reinterpret_cast<unsigned short*>(aiScript + 0x102);
	if ((m_bind != 0) &&
		(((m_chaseState == 4) && ((aiFlags & 8) == 0)) ||
		 ((m_chaseState != 4) && ((aiFlags & 4) == 0)))) {
		unsigned char* bind = m_bind;
		unsigned char* modelData = *reinterpret_cast<unsigned char**>(
			reinterpret_cast<unsigned char*>(object->m_charaModelHandle) + 0x168);
		Mtx bindMtx;
		PSMTXCopy(*reinterpret_cast<Mtx*>(bind + 0x6C), bindMtx);
		startPos.x = bindMtx[0][3] + *reinterpret_cast<float*>(modelData + 0x74);
		startPos.y = bindMtx[1][3] + *reinterpret_cast<float*>(modelData + 0x84);
		startPos.z = bindMtx[2][3] + *reinterpret_cast<float*>(modelData + 0x94);
		bindMtx[0][3] = startPos.x;
		bindMtx[1][3] = startPos.y;
		bindMtx[2][3] = startPos.z;

		CVector localForward(kMonObjDefaultScale, kMonObjZero, kMonObjZero);
		PSMTXMultVecSR(bindMtx, reinterpret_cast<Vec*>(&localForward), reinterpret_cast<Vec*>(&forward));
		forward.y = kMonObjZero;
		forward.Normalize();
		{
			CVector scaled;
			PSVECScale(reinterpret_cast<Vec*>(&forward), reinterpret_cast<Vec*>(&scaled), distance);
			move.x = scaled.x;
			move.y = scaled.y;
			move.z = scaled.z;
		}
	}

	if ((flags & 1) != 0) {
		CMapCylinder hitCylinder;
		hitCylinder.m_axis.x = kMonObjHalf * object->m_bodyEllipsoidRadius;
		hitCylinder.m_axis.y = kMonObjMaxBound;
		hitCylinder.m_axis.z = kMonObjMinBound;
		hitCylinder.m_radius = kMonObjMinBound;
		hitCylinder.m_bound.m_min.x = kMonObjMinBound;
		hitCylinder.m_bound.m_min.y = kMonObjMaxBound;
		hitCylinder.m_bound.m_min.z = kMonObjMaxBound;
		hitCylinder.m_bound.m_max.x = kMonObjMaxBound;
		hitCylinder.m_bound.m_max.y = kMonObjMaxBound;
		hitCylinder.m_bound.m_max.z = kMonObjMinBound;
		hitCylinder.m_bottom.x = startPos.x;
		hitCylinder.m_bottom.y = startPos.y;
		hitCylinder.m_bottom.z = startPos.z;
		hitCylinder.m_top.x = move.x;
		hitCylinder.m_top.y = move.y;
		hitCylinder.m_top.z = move.z;

		int hit = MapMng.CheckHitCylinderNear(&hitCylinder, reinterpret_cast<Vec*>(&move), *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1B2));
		if (hit != 0) {
			if (hitScale != NULL) {
				*hitScale = g_hit_t;
			}
			PSVECScale(reinterpret_cast<Vec*>(&move), reinterpret_cast<Vec*>(&move), g_hit_t);
			distance = static_cast<float>(static_cast<double>(distance) * static_cast<double>(g_hit_t));
		}
		gCFlatRuntime2.AddDebugDrawCC(reinterpret_cast<Vec*>(&startPos), reinterpret_cast<Vec*>(&move), hitCylinder.m_axis.x, 1, hit);
	}

	if ((flags & 2) != 0) {
		float halfAngle = kMonObjHalf * kMonObjDegToRad *
			static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xCA));
		float sideDist = kMonObjZero;
		if (kMonObjZero != halfAngle) {
			sideDist = kMonObjConeSideRadius / static_cast<float>(tan(static_cast<double>(halfAngle)));
		}

		Vec coneStart;
		coneStart.x = startPos.x;
		coneStart.y = startPos.y;
		coneStart.z = startPos.z;
		{
			CVector scaled;
			PSVECScale(reinterpret_cast<Vec*>(&forward), reinterpret_cast<Vec*>(&scaled), sideDist);
			Vec sideOffset;
			sideOffset.x = scaled.x;
			sideOffset.y = scaled.y;
			sideOffset.z = scaled.z;
			PSVECSubtract(&coneStart, &sideOffset, &coneStart);
		}

		float coneLength = static_cast<float>(static_cast<double>(distance) + static_cast<double>(sideDist));
		{
			CVector scaled;
			PSVECScale(reinterpret_cast<Vec*>(&forward), reinterpret_cast<Vec*>(&scaled), sideDist);
			Vec sideOffset;
			sideOffset.x = scaled.x;
			sideOffset.y = scaled.y;
			sideOffset.z = scaled.z;
			PSVECAdd(reinterpret_cast<Vec*>(&move), &sideOffset, reinterpret_cast<Vec*>(&move));
		}

		unsigned char didHit = 0;
		for (int rank = 0; rank < 4; rank++) {
			if (((flags & 4) != 0) && (((static_cast<int>(mon[0x54C]) + rank) & 3) != 0)) {
				continue;
			}

			int partyIndex = *reinterpret_cast<int*>(mon + 0x620 + rank * 4);
			CGPartyObj* partyObj = Game.m_partyObjArr[partyIndex];
			if (partyObj == NULL) {
				continue;
			}

			unsigned int partyFlags = partyObj->GetCID();
			bool targetHidden =
				(Game.m_gameWork.m_menuStageMode != 0) &&
				(Game.m_gameWork.m_bossArtifactStageIndex < 0xF) &&
				((partyFlags & 0x6D) == 0x6D) &&
				(partyObj->m_scriptHandle[0xED] != NULL);
			if (targetHidden ||
				(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(partyObj->m_scriptHandle) + 7) == 0) ||
				(partyObj->m_lastStateId == 9) ||
				(partyObj->m_lastStateId == 0x22) ||
				(static_cast<double>(*reinterpret_cast<float*>(mon + partyIndex * 4 + 0x5D0)) >=
				 static_cast<double>(static_cast<float>(static_cast<double>(coneLength) - static_cast<double>(sideDist))))) {
				continue;
			}

			Vec partyPos;
			{
				CVector partyPosVec(partyObj->m_worldPosition.x,
					partyObj->m_worldPosition.y + partyObj->unk_0x184, partyObj->m_worldPosition.z);
				partyPos.x = partyPosVec.x;
				partyPos.y = partyPosVec.y;
				partyPos.z = partyPosVec.z;
			}

			Vec targetDelta;
			{
				CVector delta;
				PSVECSubtract(&partyPos, &coneStart, reinterpret_cast<Vec*>(&delta));
				targetDelta.x = delta.x;
				targetDelta.y = delta.y;
				targetDelta.z = delta.z;
			}
			float targetDist = PSVECMag(&targetDelta);
			if (static_cast<double>(kMonObjZero) >= static_cast<double>(targetDist)) {
				continue;
			}

			CVector targetDir;
			PSVECNormalize(&targetDelta, reinterpret_cast<Vec*>(&targetDir));
			float dot = PSVECDotProduct(reinterpret_cast<Vec*>(&forward), reinterpret_cast<Vec*>(&targetDir));
			if ((static_cast<double>(
			         static_cast<float>(static_cast<double>(sideDist) -
			                            static_cast<double>(object->m_bodyEllipsoidRadius))) >
			     static_cast<double>(targetDist)) ||
				((static_cast<double>(kMonObjZero) != static_cast<double>(halfAngle)) &&
				 (static_cast<double>(kMonObjZero) >= static_cast<double>(dot)))) {
				continue;
			}

			float angle = static_cast<float>(acos(static_cast<double>(dot)));
			if ((static_cast<double>(kMonObjZero) != static_cast<double>(halfAngle)) &&
				(static_cast<double>(angle) >= static_cast<double>(halfAngle))) {
				continue;
			}

			didHit = 1;
			float cylRadius = kMonObjHalf * object->m_bodyEllipsoidRadius;
			unsigned short hitMask = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1B2);
			Vec cylTop;
			{
				CVector delta;
				PSVECSubtract(&partyPos, reinterpret_cast<Vec*>(&startPos), reinterpret_cast<Vec*>(&delta));
				cylTop.x = delta.x;
				cylTop.y = delta.y;
				cylTop.z = delta.z;
			}
			CMapCylinder hitCylinder;
			hitCylinder.m_axis.y = kMonObjMaxBound;
			hitCylinder.m_axis.z = kMonObjMinBound;
			hitCylinder.m_radius = kMonObjMinBound;
			hitCylinder.m_bound.m_min.x = kMonObjMinBound;
			hitCylinder.m_bound.m_min.y = kMonObjMaxBound;
			hitCylinder.m_bound.m_min.z = kMonObjMaxBound;
			hitCylinder.m_bound.m_max.x = kMonObjMaxBound;
			hitCylinder.m_bound.m_max.y = kMonObjMaxBound;
			hitCylinder.m_bound.m_max.z = kMonObjMinBound;
			hitCylinder.m_bottom.x = startPos.x;
			hitCylinder.m_bottom.y = startPos.y;
			hitCylinder.m_bottom.z = startPos.z;
			hitCylinder.m_top = cylTop;
			hitCylinder.m_axis.x = cylRadius;

			int mapHit = MapMng.CheckHitCylinderNear(&hitCylinder, &cylTop, hitMask);
			Vec debugDelta;
			debugDelta.x = targetDelta.x;
			debugDelta.y = targetDelta.y;
			debugDelta.z = targetDelta.z;
			if (mapHit != 0) {
				PSVECScale(&debugDelta, &debugDelta, g_hit_t);
			}
			gCFlatRuntime2.AddDebugDrawCC(reinterpret_cast<Vec*>(&startPos), &debugDelta, cylRadius, 1, mapHit == 0);

			if (mapHit == 0) {
				if (hitPartyIndex != NULL) {
					*hitPartyIndex = reinterpret_cast<int>(partyObj->m_scriptHandle[0xED]);
				}
				break;
			}
		}

		if (static_cast<double>(kMonObjZero) != static_cast<double>(halfAngle)) {
			float debugRadius = static_cast<float>(
				static_cast<double>(coneLength) * static_cast<double>(static_cast<float>(tan(static_cast<double>(halfAngle)))));
			gCFlatRuntime2.AddDebugDrawCC(&coneStart, reinterpret_cast<Vec*>(&move), debugRadius, 0, didHit);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlSet(int)
{
	// TODO
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
void CGMonObj::mlHide()
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlEscape()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveCancel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveChase(CGCharaObj*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlMove()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::mlAttack()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::aiAddDefault(int&)
{
	// TODO
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
#define aiPriority (*reinterpret_cast<int*>(CGMonObj::m_aiWork + 0))
#define aiBranch (*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4))

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
	void** scriptHandle = object->m_scriptHandle;

	if (scriptHandle != nullptr) {
		if ((*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle[9]) + 0xFE) & 4) != 0) {
			int hasNearParty = 0;
			if (m_unk6B9 == 0) {
				for (int i = 0; i < 4; i++) {
					CGPartyObj* party = Game.m_partyObjArr[i];
					if (party != nullptr && party->m_comboState != 0) {
						float dist = PSVECDistance(&party->m_comboCenter, &object->m_worldPosition);
						if (dist < 60.0f + object->m_bodyEllipsoidRadius) {
							hasNearParty = 1;
							break;
						}
					}
				}
			}

			if (hasNearParty != m_unk6C3) {
				if ((*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFE) & 4) != 0) {
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

		reinterpret_cast<CMonWork*>(object->m_scriptHandle)->CalcStatus();
		(this->*m_funcs->always)();

		unsigned short stepSeRaw = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1BE);
		int stepSeId;
		if (stepSeRaw == 0xFFFF) {
			stepSeId = 0;
		} else {
			stepSeId = (stepSeRaw & 0xFF) + ((stepSeRaw >> 8) * 1000);
		}

		if (stepSeId != 0) {
			int& stepSeHandle = m_stepSeHandle;
			if (object->m_currentAnimSlot == *reinterpret_cast<char*>(&object->m_animStartFrame)) {
				if (stepSeHandle != 0) {
					Sound.ChangeSe3DPos(stepSeHandle, &object->m_worldPosition);
				} else {
					stepSeHandle = reinterpret_cast<CGPrgObj*>(this)->playSe3D(stepSeId, 0x32, 0x96, 0, (Vec*)0);
				}
			} else if (stepSeHandle != 0) {
				Sound.FadeOutSe3D(stepSeHandle, 0x32);
				stepSeHandle = 0;
			}
		}
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

	void* classId = object->m_scriptHandle[4];
	switch (reinterpret_cast<unsigned int>(classId)) {
	case 0x5B:
		m_funcs = &funcsGiantCrab;
		break;
	case 0x5F:
		m_funcs = &funcsMolbol;
		break;
	case 0x63:
		m_funcs = &funcsOrcKing;
		break;
	case 0x67:
		m_funcs = &funcsGoblinKing;
		break;
	case 0x6B:
		m_funcs = &funcsArmstrong;
		break;
	case 0x6F:
		m_funcs = &funcsGigasLoad;
		break;
	case 0x70:
		m_funcs = &funcsWifeLamia;
		break;
	case 0x71:
		m_funcs = &funcsGolem;
		break;
	case 0x73:
		m_funcs = &funcsLizardmanKing;
		break;
	case 0x74:
	case 0x75:
		m_funcs = &funcsLKShooter;
		break;
	case 0x77:
		m_funcs = &funcsCaveWorm;
		break;
	case 0x79:
		m_funcs = &funcsTetsukyojin;
		break;
	case 0x7B:
		m_funcs = &funcsAntrion;
		break;
	case 0x7F:
		m_funcs = &funcsLich;
		break;
	case 0x83:
		m_funcs = &funcsDragonZombie;
		break;
	case 0x85:
	case 0x86:
	case 0x87:
		m_funcs = &funcsMeteoParasite;
		break;
	case 0x88:
		m_funcs = &funcsMeteoParasiteC;
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
	case 0x9A:
		m_funcs = &funcsLastBoss;
		break;
	case 0x9B:
		m_funcs = &funcsRamoe;
		break;
	case 0x9E:
		m_funcs = &funcsSaw;
		break;
	default:
		m_funcs = &funcsDefault;
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
	object->m_hitNormal.x = 0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1B0));

	CCharaPcs::CHandle* handle = object->m_charaModelHandle;
	if (handle != NULL) {
		CChara::CModel* model = handle->m_model;
		if (model != NULL) {
			int nodeIdx = model->SearchNode(const_cast<char*>(s_monObjHeadNode));
			if (nodeIdx >= 0) {
				m_bind = reinterpret_cast<unsigned char*>(object->m_charaModelHandle->m_model->m_nodes + nodeIdx);
			}
		}
	}

	int animPoint = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1A0);
	if (animPoint != 0xFFFF) {
		object->AddAnimPoint(1, animPoint, 0xB);
	}

	animPoint = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1A2);
	if (animPoint != 0xFFFF) {
		object->AddAnimPoint(1, animPoint, 0xA);
	}

	m_forcedAction = -1;
	for (int attackBase = 0, slotBase = 0; slotBase < 0x10; attackBase += 4, slotBase += 8) {
		unsigned int attackId = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + slotBase + 0xD0);
		if ((attackId != 0xFFFF) &&
			(*reinterpret_cast<short*>(Game.unkCFlatData0[2] + attackId * 0x48 + 0xE) == 4)) {
			m_forcedAction = attackBase;
			break;
		}

		attackId = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + slotBase + 0xD2);
		if ((attackId != 0xFFFF) &&
			(*reinterpret_cast<short*>(Game.unkCFlatData0[2] + attackId * 0x48 + 0xE) == 4)) {
			m_forcedAction = attackBase + 1;
			break;
		}

		attackId = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + slotBase + 0xD4);
		if ((attackId != 0xFFFF) &&
			(*reinterpret_cast<short*>(Game.unkCFlatData0[2] + attackId * 0x48 + 0xE) == 4)) {
			m_forcedAction = attackBase + 2;
			break;
		}

		attackId = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + slotBase + 0xD6);
		if ((attackId != 0xFFFF) &&
			(*reinterpret_cast<short*>(Game.unkCFlatData0[2] + attackId * 0x48 + 0xE) == 4)) {
			m_forcedAction = attackBase + 3;
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
		unsigned short count = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AA);
		for (int i = 0; i < static_cast<int>(count); i++) {
			int dataNo = object->m_charaModelHandle->GetPdtSlot();
			reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace((i + 0x5A) | (dataNo << 8), *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x5A8), object, kMonObjDefaultScale, 0);
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::setUndeadEffect(int, int)
{
	// TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::setRepop(int mode)
{
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	void** scriptHandle = object->m_scriptHandle;
	void* classId = scriptHandle[4];

	int option;
	if ((mode != 0) && (option = static_cast<int>(*reinterpret_cast<short*>(&Game.m_gameWork.m_optionValue)), option < 9)) {
		unsigned long long bit = 1ULL << reinterpret_cast<int>(scriptHandle[2]);
		if (((CFlatSpawnBitHi(option) & static_cast<unsigned int>(bit)) |
			 (CFlatSpawnBitLo(option) & static_cast<unsigned int>(bit >> 32))) != 0) {
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle) + 0x1C) = 0;
			object->m_bgColMask = 0;
			object->m_displayFlags = 0;
			object->m_weaponNodeFlags &= 0xFFEF;
			prgObj->changeStat(0x28, 0, 0);
			return;
		}
	}

	if (mode == 0) {
		m_homePosition.x = object->unk_0x168;
		m_homePosition.y = object->unk_0x16C;
		m_homePosition.z = object->unk_0x170;
		object->m_worldPosition = m_homePosition;
		object->m_rotBaseY = *reinterpret_cast<float*>(&object->m_bgFlags);
		object->m_rotTargetY = object->m_rotBaseY;

		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle) + 0x1C) =
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle) + 0x1A);
		m_targetPartyIndex = -1;
		m_aiState = 0;
		m_aiStatePrev = 0;
		m_unk6C8 = 0;
		m_unk6CC = 0;
		mon[0x6B4] = 0;
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
		memset(&m_moveWork, 0, sizeof(m_moveWork));
	}

	enableAttackCol(0, 0, 0);
	enableDamageCol(1);
	prgObj->changeStat(0, 0, 0);

	unsigned char* monsterScript = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
	unsigned short scriptFlags = *reinterpret_cast<unsigned short*>(monsterScript + 0xFE);

	if ((scriptFlags & 0x80) == 0 && (scriptFlags & 0x20) == 0) {
		if ((scriptFlags & 0x40) != 0 || classId == reinterpret_cast<void*>(0x39)) {
			m_chaseState = 4;
			m_chaseTimer = 0;
			m_chaseDirty = 1;
			enableDamageCol(0);
			if ((scriptFlags & 0x40) != 0) {
				object->SetAnimSlot(10, 0);
			}
		}

		if ((scriptFlags & 0x200) != 0) {
			prgObj->changeStat(0x36, 0, 0);
		}

		if (mode == 0) {
			prgObj->playSe3D(0x18, 0x32, 0x96, 0, (Vec*)0);
			prgObj->putParticle(300, 0, &object->m_worldPosition, 0.0f, 0);
			object->m_bgColMask |= 0x90002;
			*reinterpret_cast<float*>(mon + 0x694) = 0.0f;
		}
	} else {
		if (mode == 0) {
			object->m_bgColMask |= 0x10002;
		}
		m_chaseState = 4;
		m_chaseTimer = 0;
		m_chaseDirty = 1;
		enableDamageCol(0);
	}

	if (classId == reinterpret_cast<void*>(0x55)) {
		m_chaseState = 4;
		m_chaseTimer = 0;
		m_chaseDirty = 1;
	}

	unsigned short countA = *reinterpret_cast<unsigned short*>(monsterScript + 0x1A8);
	for (int i = 0; i < static_cast<int>(countA); i++) {
		int particleBase = 0;
		if (reinterpret_cast<int>(classId) < 0xA7) {
			if (classId == reinterpret_cast<void*>(0x9C)) {
				particleBase = 1;
			}
		} else if (classId == reinterpret_cast<void*>(0xA9)) {
			particleBase = 0;
		} else if (reinterpret_cast<int>(classId) < 0xA9) {
			particleBase = 2;
		}

		int dataNo = object->m_charaModelHandle != nullptr ? object->m_charaModelHandle->GetPdtSlot() : -1;
		prgObj->putParticleBindTrace((i + particleBase + 0x50) | (dataNo << 8), *reinterpret_cast<int*>(mon + 0x5A4), object, 0.0f, 0);
	}

	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x20000);

	unsigned short countB = *reinterpret_cast<unsigned short*>(monsterScript + 0x1AA);
	for (int i = 0; i < static_cast<int>(countB); i++) {
		int dataNo = object->m_charaModelHandle != nullptr ? object->m_charaModelHandle->GetPdtSlot() : -1;
		prgObj->putParticleBindTrace((i + 0x5A) | (dataNo << 8), *reinterpret_cast<int*>(mon + 0x5A8), object, 0.0f, 0);
	}

	if ((scriptFlags & 1) == 0) {
		return;
	}

	*reinterpret_cast<float*>(mon + 0x694) = 1.0f;
	scriptHandle = object->m_scriptHandle;
	classId = scriptHandle[4];
	int weaponMode = static_cast<int>((static_cast<unsigned int>(object->m_weaponNodeFlags) << 24) >> 31);
	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(scriptHandle[9]) + 0xFC) != 0xB) {
		weaponMode = 1;
	}

	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x1000);

	unsigned short countC = (weaponMode == 0) ?
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle[9]) + 0x1AE) :
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle[9]) + 0x1AC);
	int particleBase = (weaponMode == 0) ? 0x3C : 0x46;

	for (int i = 0; i < static_cast<int>(countC); i++) {
		int dataNo = object->m_charaModelHandle != nullptr ? object->m_charaModelHandle->GetPdtSlot() : -1;
		prgObj->putParticleBindTrace((particleBase + i) | (dataNo << 8), *reinterpret_cast<int*>(mon + 0x594), object, 0.0f, 0);
	}

	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(scriptHandle[9]) + 0xFC) == 0xB) {
		object->SetTexAnim(const_cast<char*>(s_monObjTexAnimU1));
	}

	if (static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags)) << 24)) < 0) {
		if (classId == reinterpret_cast<void*>(0x83)) {
			prgObj->playSe3D(0x987A, 0x32, 0x96, 0, (Vec*)0);
		} else if (classId == reinterpret_cast<void*>(0x7F)) {
			prgObj->playSe3D(0x11585, 0x32, 0x96, 0, (Vec*)0);
		}
	}

	m_unk6BA = 0;
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

	if (((m_moveWork.m_flags & 0x30000) != 0) && (AStar.m_portalCount != 0)) {
		if (routeFrom == 0) {
			routeFrom = static_cast<short>(startGroup);
		}
		if (((m_moveWork.m_flags & 0x10000) != 0) && ((m_moveWork.m_flags & 0x40) == 0)) {
			short currentRoute = routeFrom;
			if ((currentRoute != 0) && (forbiddenGroup != 0) && (currentRoute != forbiddenGroup)) {
				unsigned char* routeStep = AStar.m_routeTable[currentRoute - 1][forbiddenGroup + 0x36];
				CAStar::CAPos* portalPos = &AStar.m_portals[routeStep[1]];
				float portalDist = PSVECDistance(&object->m_worldPosition, &portalPos->m_position);
				if ((portalDist < object->m_capsuleHalfHeight) || (startGroup == routeStep[0])) {
					routeFrom = routeStep[0];
					portalPos = &AStar.m_portals[AStar.m_routeTable[routeStep[0] - 1][forbiddenGroup + 0x36][1]];
				}
				targetPos.x = portalPos->m_position.x;
				targetPos.y = portalPos->m_position.y;
				targetPos.z = portalPos->m_position.z;
			}
		} else {
			CAStar::CAPos* escapePos;
			if ((routeFrom != 0) && (forbiddenGroup != 0) &&
				((escapePos = AStar.getEscapePos(object->m_worldPosition, targetPos, routeFrom, routePrev)) != NULL)) {
				unsigned int nextGroup = escapePos->m_groupA;
				if (static_cast<short>(nextGroup) == routeFrom) {
					nextGroup = escapePos->m_groupB;
				}
				unsigned char* routeStep = AStar.m_routeTable[routeFrom - 1][nextGroup + 0x36];
				float portalDist = PSVECDistance(&object->m_worldPosition, &escapePos->m_position);
				if ((portalDist < object->m_capsuleHalfHeight) || (startGroup == routeStep[0])) {
					routePrev = routeFrom;
					routeFrom = routeStep[0];
					escapePos = &AStar.m_portals[AStar.m_routeTable[routeStep[0] - 1][forbiddenGroup + 0x36][1]];
				}

				float targetDist = PSVECDistance(&targetPos, &object->m_worldPosition);
				CVector portalVec(escapePos->m_position);
				CVector myVec(object->m_worldPosition);
				Vec dirRaw;
				PSVECSubtract(myVec, portalVec, &dirRaw);
				CVector dir;
				dir.x = dirRaw.x;
				dir.y = dirRaw.y;
				dir.z = dirRaw.z;
				dir.Normalize();
				Vec scaled;
				PSVECScale(dir, &scaled, targetDist);
				Vec dirScaled;
				dirScaled.x = scaled.x;
				dirScaled.y = scaled.y;
				dirScaled.z = scaled.z;
				CVector myVec2(object->m_worldPosition);
				Vec result;
				PSVECAdd(myVec2, &dirScaled, &result);
				targetPos.x = result.x;
				targetPos.y = result.y;
				targetPos.z = result.z;
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrame()
{
	CGObject* object = reinterpret_cast<CGObject*>(this);

	unsigned int& moveStateFlags = m_moveWork.m_stateFlags;
	unsigned int& moveFlags = m_moveWork.m_flags;
	Vec& moveTarget = m_moveWork.m_targetPos;
	float& moveSpeed = m_moveWork.m_speed;
	float& moveRange = m_moveWork.m_range;
	unsigned int& moveLimitFrame = m_moveWork.m_limitFrame;
	int& moveFrame = m_moveWork.m_frame;
	int& moveChangeStat = m_moveWork.m_changeStat;
	float& moveSpeedRate = m_pushScale;
	short& aStarGroupId = m_aStarGroupId;

	CVector local_68;
	CVector local_74;
	float in_f29 = 0.0f;

	if ((moveStateFlags & 1) != 0) {
		return;
	}

	(this->*m_funcs->moveFrame)();

	if ((moveFlags & 1) != 0) {
		CGCharaObj* target = m_moveWork.m_target;
		{
			CVector tmp(target->m_worldPosition);
			local_68.x = tmp.x;
			local_68.y = tmp.y;
			local_68.z = tmp.z;
		}
		in_f29 = PSVECDistance(reinterpret_cast<Vec*>(&local_68), &object->m_worldPosition);

		if (((moveFlags & 0x30000) != 0) && (AStar.m_portalCount != 0)) {
			short targetAStarGroupId = target->m_aStarGroupId;
			moveAStar(aStarGroupId, targetAStarGroupId, local_68);
		}
	} else if ((moveFlags & 2) != 0) {
		{
			CVector tmp(moveTarget);
			local_68.x = tmp.x;
			local_68.y = tmp.y;
			local_68.z = tmp.z;
		}
		in_f29 = PSVECDistance(reinterpret_cast<Vec*>(&local_68), &object->m_worldPosition);

		if (((moveFlags & 0x30000) != 0) && (AStar.m_portalCount != 0)) {
			int polygonGroup = AStar.calcPolygonGroup(reinterpret_cast<Vec*>(&local_68), static_cast<int>(object->m_bgHitMask));
			moveAStar(aStarGroupId, polygonGroup, local_68);
		}
	} else if ((moveFlags & 0x2000) != 0) {
		CVector tmpTarget(moveTarget);
		CVector result;
		PSVECAdd(&object->m_worldPosition, reinterpret_cast<Vec*>(&tmpTarget), reinterpret_cast<Vec*>(&result));
		local_68.x = result.x;
		local_68.y = result.y;
		local_68.z = result.z;
		in_f29 = PSVECDistance(reinterpret_cast<Vec*>(&local_68), &object->m_worldPosition);
	}

	{
		CVector tmpWorld(object->m_worldPosition);
		CVector result;
		PSVECSubtract(reinterpret_cast<Vec*>(&local_68), reinterpret_cast<Vec*>(&tmpWorld), reinterpret_cast<Vec*>(&result));
		local_74.x = result.x;
		local_74.y = result.y;
		local_74.z = result.z;
	}
	if ((moveFlags & 0x40) != 0) {
		CVector neg(-local_74.x, -local_74.y, -local_74.z);
		local_74.x = neg.x;
		local_74.y = neg.y;
		local_74.z = neg.z;
	}

	float rotY = local_74.GetRotateY();
	float distance = PSVECMag(reinterpret_cast<Vec*>(&local_74));

	if (((moveFlags & 0x20) != 0) && (moveRange <= in_f29)) {
		moveStateFlags |= 1;
		(this->*m_funcs->moveCancel)();
		moveStateFlags |= 2;
		if ((moveFlags & 0x100) != 0) {
			reinterpret_cast<CGPrgObj*>(this)->changeStat(moveChangeStat, 0, 0);
		}
		return;
	}
	if (((moveFlags & 0x40) != 0) && (in_f29 < moveRange)) {
		moveStateFlags |= 1;
		(this->*m_funcs->moveCancel)();
		moveStateFlags |= 2;
		if ((moveFlags & 0x100) != 0) {
			reinterpret_cast<CGPrgObj*>(this)->changeStat(moveChangeStat, 0, 0);
		}
		return;
	}

	if ((moveFlags & 4) != 0) {
		float oldRotY = object->m_rotBaseY;
		if ((moveFlags & 0x8000) != 0) {
			oldRotY += 3.1415927f;
		}

		float dstRot = Math.DstRot(rotY, oldRotY);
		float hitNrmX = object->m_hitNormal.x;
		rotY = rotY - (dstRot * (1.0f - hitNrmX));
		object->m_rotBaseY += dstRot * hitNrmX;
		object->m_rotTargetY = object->m_rotBaseY;

		float s = sinf(dstRot);
		float c = cosf(dstRot);
		float x = local_74.x;
		local_74.x = (c * x) - (s * local_74.z);
		local_74.z = (s * x) + (c * local_74.z);
		distance = PSVECMag(reinterpret_cast<Vec*>(&local_74));
	}

	if (((moveFlags & 0x80) != 0) && (((int)((unsigned int)object->m_stateFlags0 << 0x19) | ((unsigned int)object->m_stateFlags0 >> 7)) < 0)) {
		moveStateFlags |= 1;
		(this->*m_funcs->moveCancel)();
		moveStateFlags |= 2;
		if ((moveFlags & 0x100) != 0) {
			reinterpret_cast<CGPrgObj*>(this)->changeStat(moveChangeStat, 0, 0);
		}
		return;
	}

	float stepDist;
	if ((moveFlags & 0x200) != 0) {
		unsigned short speedScale = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xD4);
		stepDist = moveSpeedRate * (0.001f * speedScale + 1.0f);
	} else if ((moveFlags & 0x800) != 0) {
		unsigned short speedScale = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xD4);
		stepDist = moveSpeedRate * (0.001f * speedScale + 1.0f);
	} else {
		stepDist = moveSpeed;
	}

	Vec moveDelta;
	if ((moveFlags & 0x1000) == 0) {
		if (fabsf(distance) >= 0.001f) {
			PSVECScale(reinterpret_cast<Vec*>(&local_74), &moveDelta, (1.0f / distance) * stepDist);
		} else {
			moveDelta.x = 0.0f;
			moveDelta.y = 0.0f;
			moveDelta.z = 0.0f;
		}
	} else {
		moveDelta = local_74;
	}

	if ((moveFlags & 0x4000) == 0) {
		object->m_groundHitOffset.x += moveDelta.x;
		object->m_groundHitOffset.z += moveDelta.z;
	} else {
		PSVECAdd(&object->m_groundHitOffset, &moveDelta, &object->m_groundHitOffset);
	}

	if ((moveFlags & 0x8000) == 0) {
		object->m_rotTargetY = rotY;
	} else {
		object->m_rotTargetY = 3.1415927f + rotY;
	}

	if (((moveFlags & 0x20) == 0 || moveRange <= (in_f29 - stepDist)) &&
		((moveFlags & 0x40) == 0 || (in_f29 - stepDist) < moveRange)) {
		if ((moveFrame == 0) && ((moveFlags & 0x400) == 0)) {
			reinterpret_cast<CGPrgObj*>(this)->reqAnim(1, 1, 0);
		}

		moveFrame++;
		if (((moveFlags & 0x10) == 0) || ((int)moveLimitFrame > moveFrame)) {
			return;
		}
	}

	moveStateFlags |= 1;
	(this->*m_funcs->moveCancel)();
	moveStateFlags |= 2;
	if ((moveFlags & 0x100) != 0) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(moveChangeStat, 0, 0);
	}
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
#pragma dont_inline on
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
#define baseScript (reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]))
#define aiScript (monObj->m_aiState == 0 \
		? baseScript \
		: reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) + \
			(monObj->m_aiState + *reinterpret_cast<unsigned short*>(baseScript + 0x100)) * 0x1D0 + 0x10)
	if (monObj->m_funcs->attackCheck != 0) {
		int result = (monObj->*monObj->m_funcs->attackCheck)(partyIndex);
		if (result == -2) {
			return -1;
		}
		if (result != -1) {
			return result;
		}
	}

	float targetDist = *reinterpret_cast<float*>(mon + partyIndex * 4 + 0x5D0);

	int selectorType = *reinterpret_cast<unsigned short*>(aiScript + 0x108);
	if (selectorType == 0xFFFF) {
		return -1;
	}

	unsigned int groupTable[8] = { 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };
	int groupCount[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
	int selectedAction = -1;

	for (int actionIndex = 0; actionIndex < 8; actionIndex++) {
		int actionOffset = actionIndex * 0x10;
		unsigned short actionFlags = *reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x110);
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
			float targetRot = *reinterpret_cast<float*>(mon + partyIndex * 4 + 0x610);
			float baseRot =
				kMonObjDegToRad * static_cast<float>(*reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x118)) +
				object->m_rotBaseY;
			float angleDelta = (float)__fabs(Math.DstRot(targetRot, baseRot));
			System.Printf(
				const_cast<char*>("ACT_FLAG_ROT_CHECK \x8d\xb7\x95\xaa=%f\x93x\x81\x42\n"),
				kMonObjRadToDeg * angleDelta);
			float angleLimit =
				kMonObjDegToRad * static_cast<float>(*reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x11A));
			if (!(angleDelta < angleLimit)) {
				continue;
			}
			System.Printf(const_cast<char*>(s_monObjPassThroughText));
		}

		if (selectorType == 0) {
			float maxDist = static_cast<float>(*reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x114));
			float minDist = static_cast<float>(static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x112)));
			unsigned short chance = *reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x116);

			if ((targetDist < maxDist) && (minDist < targetDist)) {

			bool forceAction = false;
			CGPartyObj* party = Game.m_partyObjArr[partyIndex];
			int partyState = reinterpret_cast<CGPrgObj*>(party)->m_lastStateId;
			if (((partyState == 1) || (partyState == 7)) &&
				((float)__fabs(Math.DstRot(object->m_rotBaseY, reinterpret_cast<CGObject*>(party)->m_rotBaseY)) > kMonObjHalfPi)) {
				if (*reinterpret_cast<unsigned short*>(baseScript + 0x10C) == 1) {
					if (monObj->m_forcedAction != *reinterpret_cast<short*>(aiScript + actionOffset + 0x11E)) {
						goto skipForce;
					}
				} else if ((*reinterpret_cast<unsigned short*>(baseScript + 0x10C) == 1) ||
					(monObj->m_forcedAction != actionIndex)) {
					goto skipForce;
				}
				forceAction = true;
			}
		skipForce:

			if (forceAction || (Math.Rand(100) <= chance)) {
				selectedAction = actionIndex;
				if ((*reinterpret_cast<unsigned short*>(baseScript + 0x10C) == 1) || forceAction) {
					break;
				}
			}
			}
		} else {
			unsigned int groupIndex;
			if (*reinterpret_cast<unsigned short*>(baseScript + 0x10C) == 1) {
				groupIndex = (actionFlags >> 2) & 7;
			} else {
				groupIndex = *reinterpret_cast<unsigned short*>(aiScript + actionOffset + 0x11A);
			}

			if (groupIndex < 8) {
				groupTable[actionIndex] = groupIndex;
				groupCount[groupIndex] += 1;
			}
		}
	}

	if (selectorType == 1) {
		int& groupCursor = monObj->m_unk6CC;
		while (groupCount[groupCursor] == 0) {
			groupCursor += 1;
			if (groupCursor >= 8) {
				groupCursor = 0;
			}
		}

		int pick = Math.Rand(8);
		int seen = 0;
		int i = 0;
		unsigned int* groupPtr = groupTable;
		int iter = 2;
		do {
			if (static_cast<unsigned int>(groupCursor) == groupPtr[0]) {
				if (seen == pick) {
					groupCursor += 1;
					return i;
				}
				seen += 1;
			}
			if (static_cast<unsigned int>(groupCursor) == groupPtr[1]) {
				if (seen == pick) {
					groupCursor += 1;
					return i + 1;
				}
				seen += 1;
			}
			if (static_cast<unsigned int>(groupCursor) == groupPtr[2]) {
				if (seen == pick) {
					groupCursor += 1;
					return i + 2;
				}
				seen += 1;
			}
			if (static_cast<unsigned int>(groupCursor) == groupPtr[3]) {
				if (seen == pick) {
					groupCursor += 1;
					return i + 3;
				}
				seen += 1;
			}
			groupPtr += 4;
			i += 4;
			iter -= 1;
		} while (iter != 0);
	}

	return selectedAction;
#undef aiScript
#undef baseScript
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
void CGMonObj::statAround()
{
	CGMonObj* monObj = this;
	unsigned char* mon = reinterpret_cast<unsigned char*>(monObj);
	CGObject* object = reinterpret_cast<CGObject*>(monObj);
	int& targetPartyIndex = monObj->m_targetPartyIndex;
#define actionState (*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4))
#define script (reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]))

	if (targetPartyIndex >= 0) {
		float homeRange = static_cast<float>(*reinterpret_cast<unsigned short*>(script + 0xCC));
		float homeDist = PSVECDistance(&monObj->m_homePosition, &object->m_worldPosition);
		if (!(homeRange <= homeDist)) {
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
				actionState = 0;
				memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
				monObj->m_chaseState = 0;
				monObj->m_chaseTimer = 0;
				monObj->m_chaseDirty = 1;
				return;
			}
			if (nextAction == -1) {
				if (*reinterpret_cast<unsigned short*>(script + 0x10C) != 1) {
					if (static_cast<int>(*reinterpret_cast<unsigned short*>(script + 0x1BA)) <=
						monObj->m_chaseTimer) {
						monObj->m_chaseState = 3;
						monObj->m_chaseTimer = 0;
						monObj->m_chaseDirty = 1;
						return;
					}
					actionState = 3;
					return;
				}

				unsigned char* aiScript = script;
				short aiState = monObj->m_aiState;
				if (aiState != 0) {
					aiScript = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
						(static_cast<int>(aiState) + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
				}
				if (((*reinterpret_cast<unsigned short*>(script + 0xFE) & 8) == 0) &&
					((*reinterpret_cast<unsigned short*>(aiScript + 0x102) & 0x100) == 0)) {
					actionState = 0x21;
					if (monObj->m_moveWork.m_mode != 1) {
						memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
						monObj->m_moveWork.m_flags = 0x205;
						if (aiState == 0) {
							aiScript = script;
						} else {
							aiScript = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
								(static_cast<int>(aiState) + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
						}
						if ((*reinterpret_cast<unsigned short*>(aiScript + 0x102) & 0x40) != 0) {
							monObj->m_moveWork.m_flags |= 0x10000;
						}
						monObj->m_moveWork.m_mode = 1;
					}
					monObj->m_moveWork.m_target = Game.m_partyObjArr[targetPartyIndex];
					if (((monObj->m_moveWork.m_stateFlags & 1) != 0) ||
						(static_cast<int>(*reinterpret_cast<unsigned short*>(script + 0x1BA)) <=
						 monObj->m_moveWork.m_frame)) {
						actionState = 0;
						memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
						monObj->m_chaseState = 3;
						monObj->m_chaseTimer = 0;
						monObj->m_chaseDirty = 1;
					}
					return;
				}

				actionState = 0;
				memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
				monObj->m_chaseState = 2;
				monObj->m_chaseTimer = 0;
				monObj->m_chaseDirty = 1;
				return;
			}

			if (*reinterpret_cast<unsigned short*>(script + 0x10C) == 1) {
				actionState = nextAction;
				if (nextAction < 100) {
#define AISCRIPT ((monObj->m_aiState == 0) \
	? script \
	: (reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) + \
		(static_cast<int>(monObj->m_aiState) + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10))
					int actionOffset = nextAction * 0x10;
					if ((*reinterpret_cast<unsigned short*>(AISCRIPT + (actionOffset + 0x110)) & 0x20) != 0) {
						actionState = 0x21;
						CGPartyObj* target = Game.m_partyObjArr[targetPartyIndex];
						if (monObj->m_moveWork.m_mode != 4) {
							memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
							monObj->m_moveWork.m_flags = 0x855;
							if ((*reinterpret_cast<unsigned short*>(script + 0xFE) & 4) != 0) {
								monObj->m_moveWork.m_flags |= 0x400;
							}
							if ((*reinterpret_cast<unsigned short*>(AISCRIPT + 0x102) & 0x80) != 0) {
								monObj->m_moveWork.m_flags |= 0x20000;
							}
							monObj->m_moveWork.m_mode = 4;
							monObj->m_moveWork.m_range = static_cast<float>(*reinterpret_cast<unsigned short*>(script + 0xD6));
							monObj->m_moveWork.m_limitFrame = *reinterpret_cast<unsigned short*>(script + 0x1B6);
						}
						monObj->m_moveWork.m_target = target;
						monObj->m_chaseState = 5;
						monObj->m_chaseTimer = 0;
						monObj->m_chaseDirty = 1;
						return;
					}

					float actionRange = static_cast<float>(*reinterpret_cast<unsigned short*>(AISCRIPT + (actionOffset + 0x11C)));
					short actionParam = *reinterpret_cast<short*>(AISCRIPT + actionOffset + 0x11E);
					actionState = 0x21;
					CGPartyObj* target = Game.m_partyObjArr[targetPartyIndex];
					if (monObj->m_moveWork.m_mode != 2) {
						memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
						monObj->m_moveWork.m_flags = 0x325;
						if ((*reinterpret_cast<unsigned short*>(AISCRIPT + 0x102) & 0x40) != 0) {
							monObj->m_moveWork.m_flags |= 0x10000;
						}
						monObj->m_moveWork.m_mode = 2;
					}
					monObj->m_moveWork.m_target = target;
					monObj->m_moveWork.m_range = actionRange;
					monObj->m_moveWork.m_changeStat = static_cast<int>(actionParam);
#undef AISCRIPT
				}
			} else {
				actionState = nextAction - 0xE;
			}
			monObj->m_chaseState = 1;
			monObj->m_chaseTimer = 0;
			monObj->m_chaseDirty = 1;
			return;
		}
	}

	targetPartyIndex = -1;
	actionState = 0;
	memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
	monObj->m_chaseState = 3;
	monObj->m_chaseTimer = 0;
	monObj->m_chaseDirty = 1;
#undef script
#undef actionState
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
void CGMonObj::statWatch()
{
	CGMonObj* monObj = this;
	unsigned char* mon = reinterpret_cast<unsigned char*>(monObj);
	CGObject* object = reinterpret_cast<CGObject*>(monObj);
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(monObj);
	int& targetPartyIndex = monObj->m_targetPartyIndex;
	int& chaseState = monObj->m_chaseState;
	int& chaseTimer = monObj->m_chaseTimer;
#define actionState (*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4))
#define script (reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]))

	if (prgObj->m_lastStateId == 0) {
		monObj->m_unk6BD = 0;
		float homeRange = static_cast<float>(*reinterpret_cast<unsigned short*>(script + 0xCC));
		float homeDist = PSVECDistance(&monObj->m_homePosition, &object->m_worldPosition);
		if (homeRange <= homeDist) {
			actionState = 0;
			memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
			chaseState = 3;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
			return;
		}

		unsigned char* aiScript;
		if (monObj->m_aiState == 0) {
			aiScript = script;
		} else {
			aiScript = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
				(static_cast<int>(monObj->m_aiState) + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
		}

		int targetMode = *reinterpret_cast<unsigned short*>(aiScript + 0x106);
		int selectedTarget = -1;
		if (targetMode == 0xFFFF) {
			chaseState = 0;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
			return;
		}

		if (targetMode >= 10) {
			selectedTarget = (monObj->*monObj->m_funcs->target)(targetMode);
		} else {
			// Pass 1: count valid party members.
			int validCount = 0;
			for (int slot = 0; slot < 4; slot++) {
				CGPartyObj* party = Game.m_partyObjArr[*reinterpret_cast<int*>(mon + slot * 4 + 0x620)];
				if ((party != NULL) &&
					(*reinterpret_cast<unsigned short*>(reinterpret_cast<CGObject*>(party)->m_scriptHandle + 7) != 0) &&
					(reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 9) &&
					(reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 0x22) &&
					((Game.m_gameWork.m_menuStageMode == 0) ||
					 (0xF <= Game.m_gameWork.m_bossArtifactStageIndex) ||
					 ((static_cast<unsigned short>(reinterpret_cast<CGPrgObj*>(party)->GetCID()) & 0x6D) != 0x6D) ||
					 (reinterpret_cast<CGObject*>(party)->m_scriptHandle[0xED] == NULL))) {
					validCount++;
				}
			}

			int pick = Math.Rand(validCount);
			unsigned int minHp = 10000000;
			int validIndex = 0;
			double homeRange2 = static_cast<double>(static_cast<float>(
				*reinterpret_cast<unsigned short*>(script + 0xCC)));
			int accum = -1;
			int mode0Target = -1;

			// Pass 2: select target.
			int result = -1;
			for (int slot = 0; slot < 4; slot++) {
				int partyIndex = *reinterpret_cast<int*>(mon + slot * 4 + 0x620);
				CGPartyObj* party = Game.m_partyObjArr[partyIndex];
				int candidate = accum;
				if ((party != NULL) &&
					(*reinterpret_cast<unsigned short*>(reinterpret_cast<CGObject*>(party)->m_scriptHandle + 7) != 0) &&
					(reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 9) &&
					(reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 0x22) &&
					((Game.m_gameWork.m_menuStageMode == 0) ||
					 (0xF <= Game.m_gameWork.m_bossArtifactStageIndex) ||
					 ((static_cast<unsigned short>(reinterpret_cast<CGPrgObj*>(party)->GetCID()) & 0x6D) != 0x6D) ||
					 (reinterpret_cast<CGObject*>(party)->m_scriptHandle[0xED] == NULL))) {
					if ((static_cast<double>(*reinterpret_cast<float*>(mon + partyIndex * 4 + 0x5D0)) < homeRange2) &&
						(mode0Target = partyIndex, targetMode == 0)) {
						result = partyIndex;
						break;
					}
					candidate = partyIndex;
					if ((targetMode != 3) ||
						((reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 6) &&
						 (reinterpret_cast<CGPrgObj*>(party)->m_lastStateId != 2))) {
						if (targetMode == 2) {
							unsigned int hp = *reinterpret_cast<unsigned short*>(
								reinterpret_cast<CGObject*>(party)->m_scriptHandle + 7);
							candidate = accum;
							if (hp < minHp) {
								minHp = hp;
								candidate = partyIndex;
							}
						} else {
							candidate = accum;
							if ((targetMode == 4) && (validIndex == pick)) {
								candidate = partyIndex;
							}
						}
					}
					validIndex++;
				}
				result = mode0Target;
				accum = candidate;
			}

			if (targetMode == 1) {
				result = targetPartyIndex;
			} else if ((targetMode != 0) && (targetMode < 5) && (-1 < accum)) {
				result = accum;
			}
			selectedTarget = result;
		}

		if (selectedTarget < 0) {
			actionState = 0;
			memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
			chaseState = 3;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
			return;
		}

		targetPartyIndex = selectedTarget;
		if (monObj->m_aiState == 0) {
			aiScript = script;
		} else {
			aiScript = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
				(static_cast<int>(monObj->m_aiState) + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
		}

		if (*reinterpret_cast<short*>(aiScript + 0x10A) == 1) {
			if (monObj->m_unk6BC == 0) {
				unsigned char* scriptBase = script;
				if (*reinterpret_cast<float*>(mon + targetPartyIndex * 4 + 0x5D0) <
					static_cast<float>(*reinterpret_cast<unsigned short*>(scriptBase + 0xCE))) {
					if (*reinterpret_cast<unsigned short*>(scriptBase + 0x10C) == 1) {
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
		}

		actionState = monObj->mlAttackCheck(selectedTarget);
		if (actionState == -2) {
			actionState = 0;
			memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
			chaseState = 0;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		} else if (actionState == -1) {
			actionState = 0;
			memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
			chaseState = 2;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		} else {
			unsigned char* scriptBase = script;
			if (*reinterpret_cast<unsigned short*>(scriptBase + 0x10C) == 1) {
				if (actionState < 100) {
					short aiState = monObj->m_aiState;
					unsigned char* aiData = scriptBase;
					if (aiState != 0) {
						aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(aiState + *reinterpret_cast<unsigned short*>(scriptBase + 0x100)) * 0x1D0 + 0x10;
					}
					int actionOff = actionState * 0x10;
					if ((*reinterpret_cast<unsigned short*>(aiData + actionOff + 0x110) & 0x20) != 0) {
						actionState = 0x21;
						CGPartyObj* party = Game.m_partyObjArr[selectedTarget];
						if (monObj->m_moveWork.m_mode != 4) {
							memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
							monObj->m_moveWork.m_flags = 0x855;
							if ((*reinterpret_cast<unsigned short*>(script + 0xFE) & 4) != 0) {
								monObj->m_moveWork.m_flags |= 0x400;
							}
							unsigned char* aiData2;
							if (monObj->m_aiState == 0) {
								aiData2 = script;
							} else {
								aiData2 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
									(static_cast<int>(monObj->m_aiState) + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
							}
							if ((*reinterpret_cast<unsigned short*>(aiData2 + 0x102) & 0x80) != 0) {
								monObj->m_moveWork.m_flags |= 0x20000;
							}
							monObj->m_moveWork.m_flags = monObj->m_moveWork.m_flags;
							monObj->m_moveWork.m_mode = 4;
							monObj->m_moveWork.m_range =
								static_cast<float>(*reinterpret_cast<unsigned short*>(script + 0xD6));
							monObj->m_moveWork.m_limitFrame =
								*reinterpret_cast<unsigned short*>(script + 0x1B6);
						}
						monObj->m_moveWork.m_target = reinterpret_cast<CGCharaObj*>(party);
						chaseState = 5;
						chaseTimer = 0;
						monObj->m_chaseDirty = 1;
						return;
					}
					unsigned char* aiData3;
					if (aiState == 0) {
						aiData3 = script;
					} else {
						aiData3 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(aiState + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
					}
					float range = static_cast<float>(
						*reinterpret_cast<unsigned short*>(aiData3 + actionOff + 0x11C));
					unsigned char* aiData4;
					if (aiState == 0) {
						aiData4 = script;
					} else {
						aiData4 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(aiState + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
					}
					short changeStat = *reinterpret_cast<short*>(aiData4 + actionOff + 0x11E);
					actionState = 0x21;
					CGPartyObj* party = Game.m_partyObjArr[selectedTarget];
					if (monObj->m_moveWork.m_mode != 2) {
						memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
						monObj->m_moveWork.m_flags = 0x325;
						unsigned char* aiData5;
						if (monObj->m_aiState == 0) {
							aiData5 = script;
						} else {
							aiData5 = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
								(static_cast<int>(monObj->m_aiState) + *reinterpret_cast<unsigned short*>(script + 0x100)) * 0x1D0 + 0x10;
						}
						if ((*reinterpret_cast<unsigned short*>(aiData5 + 0x102) & 0x40) != 0) {
							monObj->m_moveWork.m_flags |= 0x10000;
						}
						monObj->m_moveWork.m_flags = monObj->m_moveWork.m_flags;
						monObj->m_moveWork.m_mode = 2;
					}
					monObj->m_moveWork.m_target = reinterpret_cast<CGCharaObj*>(party);
					monObj->m_moveWork.m_range = range;
					monObj->m_moveWork.m_changeStat = static_cast<int>(changeStat);
				}
			} else {
				actionState = actionState - 0xE;
			}
			chaseState = 1;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		}
		return;
	}

	if (prgObj->m_lastStateId == 0x21) {
		if ((*reinterpret_cast<unsigned short*>(script + 0x10C) == 1) &&
			(((monObj->m_moveWork.m_stateFlags & 1) != 0) ||
			 (monObj->m_moveWork.m_frame >=
			  static_cast<int>(*reinterpret_cast<unsigned short*>(script + 0x1BC))))) {
			actionState = 0;
			memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
			chaseState = 3;
			chaseTimer = 0;
			monObj->m_chaseDirty = 1;
		}
	}
#undef script
#undef actionState
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
void CGMonObj::statMove(int* targetIndex)
{
	CGMonObj* monObj = this;
	unsigned char* mon = reinterpret_cast<unsigned char*>(monObj);
	CGObject* object = reinterpret_cast<CGObject*>(monObj);
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(monObj);
	int* chaseState = &monObj->m_chaseState;
	int* chaseTimer = &monObj->m_chaseTimer;
	int* targetPartyIdx = &monObj->m_targetPartyIndex;

	int state = *chaseState;
	switch (state) {
	case 4:
		monObj->seKiduki();
		break;

	default: {
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x10C) == 1) {
			*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
			memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
		}
		if (*chaseTimer == 0) {
			object->m_rotTargetY = *reinterpret_cast<float*>(&object->m_bgFlags);
		}

		double soundLimit = (Game.m_gameWork.m_soundOptionFlag != 0) ? kMonObjWideSoundRange : kMonObjNormalSoundRange;

		int hitPartyIndex;
		if (static_cast<double>(*reinterpret_cast<float*>(mon + 0x5BC)) < soundLimit) {
			float hitScale;
			monObj->checkCol(6, object->m_rotBaseY,
				static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xC8)),
				&hitScale, &hitPartyIndex);
			if (hitPartyIndex >= 0) {
				goto haveHit;
			}
		}
		hitPartyIndex = -1;
	haveHit:;

		if (hitPartyIndex < 0) {
			unsigned char* aiData;
			if (monObj->m_aiState == 0) {
				aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
			} else {
				aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
					(monObj->m_aiState +
					 *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x100)) *
						0x1D0 +
					0x10;
			}
			unsigned short alertMode = *reinterpret_cast<unsigned short*>(aiData + 0x104);
			switch (alertMode) {
			case 0:
				*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
				break;
			case 1:
				*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x10;
				break;
			case 2: {
				double soundLimit2 = (Game.m_gameWork.m_soundOptionFlag != 0) ? kMonObjWideSoundRange : kMonObjNormalSoundRange;
				if (static_cast<double>(*reinterpret_cast<float*>(mon + 0x5BC)) < soundLimit2) {
					*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x1D;
					float repopDist =
						static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xCC));
					float homeDist = PSVECDistance(&monObj->m_homePosition, &object->m_worldPosition);
					if (static_cast<double>(repopDist) <= static_cast<double>(homeDist)) {
						monObj->isValidTarget();
					}
				} else {
					*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
				}
				break;
			}
			}
		} else {
			*targetPartyIdx = hitPartyIndex;
			*chaseState = 2;
			*chaseTimer = 0;
			monObj->m_chaseDirty = 1;
			if (monObj->m_unk6B8 == 0) {
				void** scriptHandle = object->m_scriptHandle;
				int randVal = Math.Rand(3);
				unsigned char* script = reinterpret_cast<unsigned char*>(scriptHandle[9]);
				prgObj->playSe3D(
					*reinterpret_cast<unsigned short*>(script + 0x192) +
						*reinterpret_cast<unsigned short*>(script + 0x190) * 1000 + randVal,
					0x32, 0x96, 0, reinterpret_cast<Vec*>(NULL));
				monObj->m_unk6B8 = 1;
			}
		}
		break;
	}

	case 2:
		monObj->statAround();
		break;

	case 1:
		monObj->statWatch();
		break;

	case 3:
		monObj->isValidTarget();
		break;

	case 5: {
		{
			if (*targetPartyIdx < 0) {
				*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
				memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
				*chaseState = 0;
				*chaseTimer = 0;
				monObj->m_chaseDirty = 1;
			} else {
				*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0x21;
				CGPartyObj* partyObj = Game.m_partyObjArr[*targetPartyIdx];
				if (monObj->m_moveWork.m_mode != 4) {
					memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
					monObj->m_moveWork.m_flags = 0x855;
					if ((*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFE) & 4) != 0) {
						monObj->m_moveWork.m_flags |= 0x400;
					}
					unsigned char* aiData;
					if (monObj->m_aiState == 0) {
						aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
					} else {
						aiData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[1]) +
							(monObj->m_aiState +
							 *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x100)) *
								0x1D0 +
							0x10;
					}
					if ((*reinterpret_cast<unsigned short*>(aiData + 0x102) & 0x80) != 0) {
						monObj->m_moveWork.m_flags |= 0x20000;
					}
					monObj->m_moveWork.m_mode = 4;
					monObj->m_moveWork.m_range =
						static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xCE));
					monObj->m_moveWork.m_limitFrame = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1B6);
				}
				monObj->m_moveWork.m_target = partyObj;
				if (((monObj->m_moveWork.m_stateFlags & 1) != 0) ||
					((object->m_stateFlags0 & 0x40) != 0)) {
					*reinterpret_cast<int*>(CGMonObj::m_aiWork + 4) = 0;
					memset(&monObj->m_moveWork, 0, sizeof(monObj->m_moveWork));
					if (*targetPartyIdx >= 0) {
						object->m_rotTargetY = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.m_partyObjArr[*targetPartyIdx]));
					}
					*chaseState = 1;
					*chaseTimer = 0;
					monObj->m_chaseDirty = 1;
				}
			}
		}
		break;
	}

	}

	if (monObj->m_chaseDirty == 0) {
		*chaseTimer += 1;
	} else {
		monObj->m_chaseDirty = 0;
	}
}
#pragma dont_inline off

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
	statMove(&targetIndex);
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
		m_chaseState = 4;
		m_chaseTimer = 0;
		m_chaseDirty = 1;
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
		*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags) =
			static_cast<unsigned char>(__rlwimi(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags), 0, 3, 28, 28));
		break;

	case 0x15:
		*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags) =
			static_cast<unsigned char>(__rlwimi(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags), 1, 3, 28, 28));
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80112D5C
 * PAL Size: 376b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onChangePrg(int value)
{
#define object (reinterpret_cast<CGObject*>(this))
#define mon (reinterpret_cast<unsigned char*>(this))
	unsigned int weaponModeBits = (static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&object->m_weaponNodeFlags)) << 24) & 0xC0000000;
	if ((static_cast<int>(weaponModeBits) >> 31) != value &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) == 0xB)) {
		int isUndead =
			(static_cast<unsigned int>(
				 __cntlzw(0xB - *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC))) >>
			 5) &
			0xFF;
		int isNormal = (static_cast<unsigned int>(__cntlzw(m_unk6BA)) >> 5) & 0xFF;
		int mode = value;
		if (isUndead == 0) {
			mode = 1;
		}

		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x1000);

		int count = (mode != 0) ?
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AC) :
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AE);
		int particleBase = 0x3C;
		if (mode != 0) {
			particleBase = 0x46;
		}

		if (isNormal != 0) {
			for (int i = 0; i < static_cast<int>(count); i++) {
				int dataNo = object->m_charaModelHandle->GetPdtSlot();
				reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace(
					(particleBase + i) | (dataNo << 8),
					*reinterpret_cast<int*>(mon + 0x594),
					object,
					kMonObjDefaultScale,
					0
				);
			}
		} else {
			if ((isUndead != 0) && (count != 0)) {
				int dataNo = object->m_charaModelHandle->GetPdtSlot();
				reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace(
					(particleBase + 9) | (dataNo << 8),
					*reinterpret_cast<int*>(mon + 0x594),
					object,
					kMonObjDefaultScale,
					0
				);
			}
		}
	}

	CGCharaObj::onChangePrg(value);
#undef object
#undef mon
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::footSe()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::CMoveWork::Clear()
{
	memset(this, 0, sizeof(*this));
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
