#include "ffcc/ptrarray.h"
#include "ffcc/itemobj.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/math.h"
#include "ffcc/monobj_boss.h"
#include "ffcc/partMng.h"
#include "ffcc/partyobj.h"
#include "ffcc/prgobj.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/game.h"
#include "ffcc/vector.h"
#include "ffcc/joybusconst.h"
#include "ffcc/cardconst.h"

#include <math.h>
#include <string.h>
#include "ffcc/fontman.h"
#ifdef VERSION_GCCP01
static const int kItemObjExpandFrames = 8;
static const int kItemObjReleaseLifetime = 4500;
static const int kItemObjFadeStartFrame = 4;
static const int kItemObjDeleteFrame = 12;
static const int kItemObjHomeStartFrame = 7;
static const int kItemObjParticleEndFrame = 125;
static const int kItemObjCapsuleUseFrame = 13;
#else
static const int kItemObjExpandFrames = 10;
static const int kItemObjReleaseLifetime = 5400;
static const int kItemObjFadeStartFrame = 5;
static const int kItemObjDeleteFrame = 15;
static const int kItemObjHomeStartFrame = 9;
static const int kItemObjParticleEndFrame = 150;
static const int kItemObjCapsuleUseFrame = 16;
#endif

extern const float kItemObjUnitScale = 1.0f;
extern const float kItemObjHeightOffset = 10.0f;
extern const float kItemObjZero = 0.0f;
extern const float kItemObjGroundProbeDown = -2000.0f;
extern const float kItemObjFontAlphaMax = 255.0f;
extern const float kItemObjScreenHalfHeight = 224.0f;
extern const float kItemObjScreenHalfWidth = 320.0f;
extern const float kItemObjHalf = 0.5f;
extern const float kItemObjThrowMoveSpeed = 11.0f;
static const char sStandAnim[] = "stand";
extern const float kItemObjParticleScaleBase = 1.0e-7f;
extern const float kItemObjFineStep = 0.01f;
extern const float kItemObjMotionStep = 0.1f;
extern const float kItemObjParticleRandomRange = 0.05f;
extern const double kItemObjU32ToDoubleBias = 4503599627370496.0;
extern const float kItemObjWobblePhaseScale = 0.125f;
extern const double kItemObjS32ToDoubleBias = 4503601774854144.0;
extern const float kItemObjDamageRadius = 15.0f;
static const char s_itemAttachCenterItem3[] = "c_item3";
static const char s_itemAttachLeftItem[] = "l_item";
extern const float kItemObjPi = 3.1415927410125732f;
extern const float kItemObjSafeMoveDivisor = 3.0f;
extern const float kItemObjLaunchSpeed = 8.0f;
extern const float kItemObjLaunchYOffset = 50.0f;
extern const float kItemObjHalfPi = 1.5707963705062866f;
extern const double kItemObjExpireDistance = 300.0;
extern const float kItemObjDouble = 2.0f;
extern const float kItemObjRotationDamping = 0.75f;
extern const float kItemObjMoveOffsetXZ = 0.8999999761581421f;
extern const float kItemObjBounceAccel = 0.20000000298023224f;
extern const float kItemObjMemoryRadius = 20.0f;
extern const float kItemObjMemoryTurnStep = 0.25f;
extern const float kItemObjMemoryChaseAccel = 0.019999999552965164f;
extern const float kItemObjMemoryChaseScale = 1.5f;
static const char s_itemDamageBoneHip[] = "hip";
u32 g_tempFlag;
extern char SoundBuffer[];

static inline CFlatRuntime2* ItemCFlatRuntime()
{
	return &CFlat;
}

static inline bool ItemIsMultiBossStage()
{
	return Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0xF;
}

static inline bool ItemIsMultiBossCaravan(CGObject* const& obj)
{
	return ItemIsMultiBossStage() && obj->IsKindOf(0x6D);
}

static inline bool ItemIsGbaCaravan(CGObject* const& obj)
{
	return ItemIsMultiBossCaravan(obj) && reinterpret_cast<CCaravanWork*>(obj->m_scriptHandle)->m_joybusCaravanId != 0;
}

STATIC_ASSERT(offsetof(LastBossWork, m_capsules) == 0x08);
STATIC_ASSERT(offsetof(LastBossWork, m_targetPosition) == 0x18);
STATIC_ASSERT(offsetof(LastBossWork, m_phaseTimer) == 0x24);
STATIC_ASSERT(offsetof(CGObject, m_lifeTimer) == 0x94);

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
	CGPrgObj::onCreate();
	m_flagBits.bits.unk0 = 0;
	m_owner = 0;
	m_scriptArg = 0;
	m_createFlags = 0;
	unk_0x562 = 0;
	m_pendingModelHandle = 0;
	m_itemJumpCountdown = 0;
	memset(&m_memoryCapsuleNameIndex, 0,
	       sizeof(m_memoryCapsuleNameIndex) + sizeof(m_pendingAnimFlags) + sizeof(m_pendingAnimName));
	m_particleSlot = ItemCFlatRuntime()->GetFreeParticleSlot();
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
	if (m_pendingModelHandle != 0) {
		delete m_pendingModelHandle;
	}

	ItemCFlatRuntime()->DeleteParticleSlot(m_particleSlot, 0);
	CGPrgObj::onDestroy();
}

/*
 * --INFO--
 * PAL Address: 0x80126f38
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	if (m_stateFlags0Bits.unk4 != 0 &&
	    m_owner == 0) {
		m_lifeTimer = m_lifeTimer - 1;
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
	if (state < 0x28 && state >= 0x26) {
		m_bgColMask &= 0xfff7fffe;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80126EB4
 * PAL Size: 44b
 * EN Address: 0x801261E4
 * EN Size: 44b
 * JP Address: 0x80122D98
 * JP Size: 44b
 */
void CGItemObj::onCancelStat(int)
{
	if (m_lastStateId == 0x1b) {
		m_bgColMask |= 2;
		m_rotationX = m_rotationY = m_rotationZ = kItemObjUnitScale;
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
	CCharaPcs::CHandle* handle = m_pendingModelHandle;

	if (handle != 0 && handle->IsLoadModelASyncCompleted()) {
		if ((unsigned int)System.m_execParam >= 3U) {
			System.Printf("\x8Ev\x82\xA2\x8Fo\x83J\x83v\x83Z\x83\x8B\x94\xF1\x93\xAF\x8A\xFA\x8FI\x97\xB9\n");
		}

		m_charaModelHandle = m_pendingModelHandle;
		m_pendingModelHandle = 0;

		if (m_worldParamA == 0xCB) {
			LoadAnim(m_pendingAnimName, 0, 0, 2, m_pendingAnimFlags);
			SetAnimSlot(0, 0);
			PlayAnim(0, 1, 0, -1, -1, 0);

			CCaravanWork* ownerData = reinterpret_cast<CCaravanWork*>(m_owner->m_scriptHandle);
			int soundEntry = reinterpret_cast<LastBossWork*>(CGMonObj::m_boss)->m_boss->m_charaModelHandle->GetPdtSlot();

			SItemFlatRow* itemRows = reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2]);
			float particleScale = kItemObjFineStep * static_cast<float>(static_cast<unsigned int>(itemRows[m_worldParamB].m_fineValue)) + kItemObjParticleScaleBase;
			putParticle((soundEntry << 8) | ownerData->m_joybusCaravanId, m_particleSlot, this, particleScale, 0x12909);

			SetDamageCol(0, const_cast<char*>(s_itemDamageBoneHip), kItemObjMemoryRadius, kItemObjMemoryRadius,
			             CVector(kItemObjZero, kItemObjZero, kItemObjZero));
			m_damageColliders[0].m_hitMask = 8;
			addSubStat();
		}
	}

	CGPrgObj::onFrame();
}

/*
 * --INFO--
 * PAL Address: 0x80125fb0
 * PAL Size: 3416b
 * EN Address: 0x801252E0
 * EN Size: 3416b
 * JP Address: 0x80121E60
 * JP Size: 3468b
 */
void CGItemObj::onFrameStat()
{
	int stateId = m_lastStateId;
	float zero = kItemObjZero;

	switch (stateId) {
	case 0x1b:
		if (m_stateFrame <= kItemObjExpandFrames) {
			float wobble = kItemObjHalfPi * (float)m_stateFrame;
#ifdef VERSION_GCCP01
			wobble *= kItemObjWobblePhaseScale;
#else
			wobble /= 10.0f;
#endif
			wobble = (float)sin((double)wobble);

			m_rotationZ = wobble;
			m_rotationY = wobble;
			m_rotationX = wobble;

			if (m_stateFrame == kItemObjExpandFrames) {
				changeStat(0, 0, 0);
			}
		}
		break;
	case 0: {
		if (m_owner == 0 &&
		    m_stateFlags0Bits.unk4 != 0) {
			float distance = kItemObjZero;

			if (Game.unk_flat3_0xc7d0 != 0) {
				distance = PSVECDistance(&m_worldPosition, &reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0)->m_worldPosition);
			} else {
				if (static_cast<int>(CFlatCenterState()) == 1) {
					Vec partyCenter;

					partyCenter.x = (Game.m_partyBound.m_min.x + Game.m_partyBound.m_max.x) * kItemObjHalf;
					partyCenter.y = (Game.m_partyBound.m_min.y + Game.m_partyBound.m_max.y) * kItemObjHalf;
					partyCenter.z = (Game.m_partyBound.m_min.z + Game.m_partyBound.m_max.z) * kItemObjHalf;
					distance = PSVECDistance(&m_worldPosition, &partyCenter);
				}
			}

			if (m_lifeTimer <= 0 || distance > kItemObjExpireDistance) {
				System.Printf("\x8E\x9E\x8A\xD4\x82\xA9\x8B\x97\x97\xA3\x82\xC5\x83" "A\x83" "C\x83" "e\x83\x80\x82\xAA\x8F\xC1\x82\xA6\x82\xDC\x82\xB7\x81" "B\n");
				m_alphaStep = kItemObjMotionStep;
				m_alphaTarget = zero;
				m_bgColMask = 1;
				ItemCFlatRuntime()->EndParticle(m_charaModelHandle);
				changeStat(9, 0, 0);
			}
		}
		break;
	}
	case 0xB:
		if (m_stateFrame == m_carryFrame) {
			const CVector& attachOffset = CVector(kItemObjZero, kItemObjZero, kItemObjZero);
			bool useBossAttachName = false;

			if (Game.m_gameWork.m_menuStageMode != 0) {
				if (ItemIsGbaCaravan(m_owner)) {
					useBossAttachName = true;
				}
			}

			CGObject* attachOwner = m_owner;
			CGObject* attachSelf = this;
			attachSelf->Attach(attachOwner, const_cast<char*>(useBossAttachName ? s_itemAttachCenterItem3 : s_itemAttachLeftItem), reinterpret_cast<Vec*>(const_cast<CVector*>(&attachOffset)));
			changeStat(0, 0, 0);
			m_bodyEllipsoidRadius = kItemObjZero;
		}
		break;
	case 0xC:
	case 0xD:
		if (m_stateFrame == m_carryFrame) {
			float launchSpeed;

			if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_menuStageMode != 0 &&
			    Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
			    (static_cast<unsigned short>(m_owner->GetCID()) & 0x6D) == 0x6D &&
			    reinterpret_cast<CCaravanWork*>(m_owner->m_scriptHandle)->m_joybusCaravanId != 0) {
				launchSpeed = kItemObjUnitScale;
			} else if (static_cast<int>(CFlatCenterState()) == 1) {
				int carryCid = static_cast<unsigned short>(m_owner->GetCID());
				if ((carryCid & 0x6D) == 0x6D &&
				    2 <= reinterpret_cast<CCaravanWork*>(m_owner->m_scriptHandle)->m_tribeId) {
					launchSpeed = kItemObjUnitScale;
				} else {
					launchSpeed = kItemObjDouble;
				}
			} else {
				launchSpeed = kItemObjSafeMoveDivisor;
			}

			safeDetach(1, launchSpeed);
			m_itemJumpCountdown = kItemObjExpandFrames;
			m_bodyEllipsoidRadius = kItemObjZero;
		}

		if (m_carryFrame <= m_stateFrame) {
			int worldParamA = m_worldParamA;

			if (worldParamA == 0xD || worldParamA == 0xE) {
				if (m_stateFlags0Bits.unk0 != 0) {
					changeStat(0x1F, 0, 0);
				}
			} else if (m_stateFlags0Bits.unk0 != 0) {
				changeStat(0, 0, 0);
			}
		}
		break;
	case 0xE:
		if (m_stateFrame == 0) {
			m_bgColMask = 0;
			m_weaponNodeFlagBits.m_unk10 = 0;
			m_groundHitOffset.x = m_groundHitOffset.y = m_groundHitOffset.z = zero;
		} else if (m_stateFrame == kItemObjFadeStartFrame) {
#ifdef VERSION_GCCP01
			m_alphaStep = kItemObjWobblePhaseScale;
#else
			m_alphaStep = kItemObjMotionStep;
#endif
			m_alphaTarget = zero;
			ItemCFlatRuntime()->EndParticle(m_charaModelHandle);
		} else if (m_stateFrame == kItemObjDeleteFrame) {
			CFlatRuntime::CObject::m_flagBits.m_deleteFlag = 1;
		}

		if (kItemObjHomeStartFrame < m_stateFrame) {
			m_rotTargetY += kItemObjMotionStep;
			m_worldPosition.x += kItemObjMotionStep * (m_owner->m_worldPosition.x - m_worldPosition.x);
			m_worldPosition.y += kItemObjMotionStep * (kItemObjHalf * m_owner->unk_0x188 + m_owner->m_worldPosition.y - m_worldPosition.y);
			m_worldPosition.z += kItemObjMotionStep * (m_owner->m_worldPosition.z - m_worldPosition.z);
			m_rotationX *= kItemObjRotationDamping;
			m_rotationY *= kItemObjRotationDamping;
			m_rotationZ *= kItemObjRotationDamping;
		}
		break;
	case 9:
		if (m_stateFrame == kItemObjExpandFrames) {
			CFlatRuntime::CObject::m_flagBits.m_deleteFlag = 1;
		}
		break;
	case 0x1F:
		statPot();
		break;
	case 0x23:
		if (m_subState != 0 && m_subState == 1) {
			CCharaPcs::CHandle* handle = m_charaModelHandle;
			if (handle != 0 && handle->m_model != 0) {
				handle->m_model->m_flags10CBits.m_flag10C_80 = 1;
			}

			if (m_subFrame <= kItemObjExpandFrames) {
				float wobble = kItemObjHalfPi * (float)m_subFrame;
#ifdef VERSION_GCCP01
				wobble *= kItemObjWobblePhaseScale;
#else
				wobble /= 10.0f;
#endif
				wobble = (float)sin((double)wobble);

				m_rotationZ = wobble;
				m_rotationY = wobble;
				m_rotationX = wobble;

				if (m_subFrame == kItemObjExpandFrames) {
					m_bgColMask |= 0x80000;
					changeStat(0x24, 0, 0);
				}
			}
		}
		break;
	case 0x24:
		m_moveOffset.x = kItemObjMoveOffsetXZ;
		m_moveOffset.y = kItemObjUnitScale;
		m_moveOffset.z = kItemObjMoveOffsetXZ;

		if (m_worldPosition.y < kItemObjHeightOffset) {
			m_groundHitOffset.y += kItemObjBounceAccel * m_moveTimer;
		} else if (m_worldPosition.y > kItemObjMemoryRadius) {
			m_groundHitOffset.y = -(kItemObjBounceAccel * m_moveTimer - m_groundHitOffset.y);
		}

		m_groundHitOffset.y = (m_groundHitOffset.y < kItemObjDouble * -m_moveTimer)
		                          ? kItemObjDouble * -m_moveTimer
		                          : ((kItemObjDouble * m_moveTimer < m_groundHitOffset.y) ? kItemObjDouble * m_moveTimer : m_groundHitOffset.y);

		m_rotTargetY += kItemObjFineStep;
		m_groundHitOffset.x =
		    kItemObjFineStep * -(m_worldPosition.x - m_owner->m_worldPosition.x);
		m_groundHitOffset.z =
		    kItemObjFineStep * -(m_worldPosition.z - m_owner->m_worldPosition.z);
		break;
	case 0x25: {
		m_moveOffset.y = kItemObjMoveOffsetXZ;
		m_rotTargetY += kItemObjMemoryTurnStep;

		CVector delta(reinterpret_cast<LastBossWork*>(CGMonObj::m_boss)->m_targetPosition);
		delta = delta - CVector(m_worldPosition);
		float distance = PSVECMag(delta);
		if (distance < kItemObjMemoryRadius) {
			changeStat(0x27, 0, 0);
		} else if (distance > zero) {
			float moveScale = kItemObjMemoryChaseAccel * m_moveTimer;

			m_groundHitOffset.x += kItemObjMemoryChaseScale * delta.x * moveScale;
			m_groundHitOffset.y += kItemObjMemoryChaseScale * delta.y * moveScale;
			m_groundHitOffset.z += kItemObjMemoryChaseScale * delta.z * moveScale;
		} else {
			m_groundHitOffset.x = m_groundHitOffset.y = m_groundHitOffset.z = zero;
		}
		break;
	}
	case 0x27: {
		int pdtNo = -1;

		m_groundHitOffset.x = m_groundHitOffset.y = m_groundHitOffset.z = zero;

		if (m_stateFrame == 0) {
			m_alphaTarget = zero;
			ItemCFlatRuntime()->EndParticleSlot(m_particleSlot, 0);

			pdtNo = reinterpret_cast<LastBossWork*>(CGMonObj::m_boss)->m_boss->m_charaModelHandle->GetPdtSlot();

			SItemFlatRow* itemRows = reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2]);
			float particleScale = kItemObjFineStep * static_cast<float>(static_cast<unsigned int>(itemRows[m_worldParamB].m_fineValue)) + kItemObjParticleScaleBase;
			putParticle((pdtNo << 8) | 0x13, m_particleSlot, this, particleScale, 0x12903);
		} else if (m_stateFrame == kItemObjCapsuleUseFrame) {
			int ownerSlot = reinterpret_cast<CCaravanWork*>(m_owner->m_scriptHandle)->m_joybusCaravanId;

			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf("\x8Ev\x82\xA2\x8Fo\x83J\x83v\x83Z\x83\x8B\x8E\xB8\x94s idxParty = %d\n", ownerSlot);
			}

			CFlatRuntime::CStack stack;
			stack.m_word = 0;
			reinterpret_cast<LastBossWork*>(CGMonObj::m_boss)->m_capsules[ownerSlot] = 0;
			gCFlatRuntime().SystemCall(
			    m_owner, 2, 0x16, 1, &stack, 0);

			CFlatRuntime::CObject::m_flagBits.m_deleteFlag = 1;
		}
		break;
	}
	case 0x26: {
		int pdtNo = -1;

		m_groundHitOffset.x = m_groundHitOffset.y = m_groundHitOffset.z = zero;

		if (m_stateFrame == 0) {
			m_alphaTarget = zero;
			ItemCFlatRuntime()->EndParticleSlot(m_particleSlot, 0);

			pdtNo = reinterpret_cast<LastBossWork*>(CGMonObj::m_boss)->m_boss->m_charaModelHandle->GetPdtSlot();

			SItemFlatRow* itemRows = reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2]);
			float particleScale = kItemObjFineStep * static_cast<float>(static_cast<unsigned int>(itemRows[m_worldParamB].m_fineValue)) + kItemObjParticleScaleBase;
			putParticle((pdtNo << 8) | 4, m_particleSlot, this, particleScale, 0x12908);
		} else if (m_stateFrame == kItemObjCapsuleUseFrame) {
			int ownerSlot = reinterpret_cast<CCaravanWork*>(m_owner->m_scriptHandle)->m_joybusCaravanId;

			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf("\x8Ev\x82\xA2\x8Fo\x83J\x83v\x83Z\x83\x8B\x90\xAC\x8C\xF7 idxParty = %d\n", ownerSlot);
			}

			reinterpret_cast<LastBossWork*>(CGMonObj::m_boss)->m_capsules[ownerSlot] = 0;
			CGPrgObj* newItem = CreateFromScript(0, 0, 0x103, 0, kItemObjZero, 0);
			if (newItem != 0) {
				newItem->unk_0x168 = m_worldPosition.x;
				newItem->unk_0x16C = m_worldPosition.y;
				newItem->unk_0x170 = m_worldPosition.z;
				newItem->m_worldPosition.x = newItem->unk_0x168;
				newItem->m_worldPosition.y = newItem->unk_0x16C;
				newItem->m_worldPosition.z = newItem->unk_0x170;

				CFlatRuntime::CStack stack;
				stack.m_word = 1;
				gCFlatRuntime().SystemCall(
				    m_owner, 2, 0x16, 1, &stack, 0);
			} else {
				if ((unsigned int)System.m_execParam >= 2U) {
					System.Printf("\x8Ev\x82\xA2\x8Fo\x96\x82\x90\xCE\x82\xF0\x90\xB6\x90\xAC\x82\xC5\x82\xAB\x82\xDC\x82\xB9\x82\xF1\x82\xC5\x82\xB5\x82\xBD\x81" "B\n");
				}
			}

			CFlatRuntime::CObject::m_flagBits.m_deleteFlag = 1;
		}
		break;
	}
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
	int deletedCount = 0;

	while (deletedCount < maxDeleteCount) {
		CGItemObj* bestItemObj = 0;
		int shortestLifetime = 0x00989680;

		for (CGItemObj* itemObj = ItemCFlatRuntime()->FindGItemObjFirst();
			 itemObj != 0;
			 itemObj = ItemCFlatRuntime()->FindGItemObjNext(itemObj)) {
			if (itemObj->m_owner == 0 &&
				itemObj->m_stateFlags0Bits.unk4 != 0 &&
				(((int)(char)itemObj->m_ownerSlot & deleteMask) != 0) && itemObj->m_lifeTimer < shortestLifetime) {
				shortestLifetime = itemObj->m_lifeTimer;
				bestItemObj = itemObj;
			}
		}

		if (bestItemObj != 0) {
			gCFlatRuntime().deleteObject(bestItemObj);
		} else {
			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf("\x8F\xC1\x82\xB9\x82\xE9\x83I\x83u\x83W\x83" "F\x83N\x83g\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1\x81" "B\n");
			}
			break;
		}

		deletedCount++;
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
	int numFreeObjects = ItemCFlatRuntime()->getNumFreeObject(5);

	return numFreeObjects > 0;
}

/*
 * --INFO--
 * PAL Address: 0x801259E4
 * PAL Size: 1168b
 * EN Address: 0x80124D14
 * EN Size: 1168b
 * JP Address: 0x80121890
 * JP Size: 1172b
 */
CGPrgObj* CGItemObj::CreateFromScript(
    int createMode, int createFlags, int scriptArg, CGObject* owner, float launchAngle, CGItemObj::CCFS* ccfs)
{
	int freeItemCount = ItemCFlatRuntime()->getNumFreeObject(5);
	System.Printf("num free item = %d\n", freeItemCount);

	if (freeItemCount == 0) {
		int deletedCount = DeleteOld(1, 1, 0, 0);

		System.Printf("num delete item = %d\n", deletedCount);
		if (deletedCount == 0) {
			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf("\x83" "A\x83" "C\x83" "e\x83\x80\x82\xF0\x90\xB6\x90\xAC\x82\xC5\x82\xAB\x82\xDC\x82\xB9\x82\xF1\x82\xC5\x82\xB5\x82\xBD\x81" "B\n");
			}
			return 0;
		}
	}

	CFlatRuntime::CStack inStack[5];
	CFlatRuntime::CStack outStack;
	inStack[0].m_word = createMode;
	inStack[1].m_word = createFlags;
	inStack[2].m_word = scriptArg;
	inStack[3].m_word = owner != 0 ? owner->m_particleId : 0;
	inStack[4].m_float = launchAngle;
	g_tempFlag = createFlags;
	gCFlatRuntime().SystemCall(0, 1, 7, 5, inStack, &outStack);

	if (createMode != 1) {
		CGItemObj* newItem = static_cast<CGItemObj*>(CFlat.intToClass((int)outStack.m_word));

		if (createMode == 2) {
			newItem->m_scriptArg = scriptArg;
			newItem->m_swayTarget.x = kItemObjUnitScale;
		}

		newItem->changeStat(0x1B, 0, 0);

		if ((createFlags & 1) != 0) {
			float safePosDist;
			Vec safePos;
			float yRot = owner->m_rotBaseY + Math.RandFPM(kItemObjMotionStep);

			newItem->m_worldPosition.x = kItemObjHeightOffset * (float)sin((double)yRot) + owner->m_worldPosition.x;
			newItem->m_worldPosition.y = kItemObjHeightOffset + owner->m_worldPosition.y;
			newItem->m_worldPosition.z = kItemObjHeightOffset * (float)cos((double)yRot) + owner->m_worldPosition.z;

			safePosDist = newItem->CalcSafePos(0x41, owner, &safePos);
			float zero = kItemObjZero;
			if (safePosDist > zero) {
				owner->moveVectorHRot(kItemObjPi + owner->m_rotBaseY, zero,
				                       safePosDist / kItemObjSafeMoveDivisor, 3);
			}

			newItem->m_worldPosition = safePos;
			newItem->SetPosBG(&safePos, 1);
		}

		if ((createFlags & 4) != 0) {
			newItem->m_worldPosition = owner->m_worldPosition;
			newItem->SetPosBG(&newItem->m_worldPosition, 1);

			const CVector& moveVec = CVector((float)sin((double)launchAngle), kItemObjHeightOffset, (float)cos((double)launchAngle));
			newItem->MoveVector((Vec*)const_cast<CVector*>(&moveVec), kItemObjLaunchSpeed, 1, 0, 1, 0);
		}

		if ((createFlags & 2) != 0) {
			newItem->changeStat(0x23, 0, 0);
			newItem->m_worldPosition.x = owner->m_worldPosition.x;
			newItem->m_worldPosition.y = owner->m_worldPosition.y + kItemObjLaunchYOffset;
			newItem->m_worldPosition.z = owner->m_worldPosition.z;
			newItem->m_owner = owner;

			int ownerScriptSlot = reinterpret_cast<CCaravanWork*>(owner->m_scriptHandle)->m_joybusCaravanId;
			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf("\x8Ev\x82\xA2\x8Fo\x83J\x83v\x83Z\x83\x8B\x8D\xEC\x90\xAC idxParty = %d\n", ownerScriptSlot);
			}
			reinterpret_cast<LastBossWork*>(CGMonObj::m_boss)->m_capsules[ownerScriptSlot] = newItem;

			CCharaPcs::CHandle* handle =
			    new (Game.m_mainStage, "itemobj.cpp", 0x28E) CCharaPcs::CHandle;
			newItem->m_pendingModelHandle = handle;
			newItem->m_pendingModelHandle->Add();

			newItem->m_pendingModelHandle->LoadModelASync(2, ccfs->m_modelId, ccfs->m_modelParam);

			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf("\x8Ev\x82\xA2\x8Fo\x83J\x83v\x83Z\x83\x8B\x94\xF1\x93\xAF\x8A\xFA\x8AJ\x8En\n");
			}

			newItem->m_pendingAnimFlags = ccfs->m_pendingAnimFlags;
			newItem->m_pendingAnimName = ccfs->m_pendingAnimName;
			newItem->m_memoryCapsuleNameIndex = ccfs->m_memoryCapsuleNameIndex;
		}

		return newItem;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGItemObj::safeDetach(int throwItem, float speed)
{
	Vec safePos;
	float safeDist = CalcSafePos(0x41, m_owner, &safePos);

	float zero = kItemObjZero;
	if (safeDist > zero) {
		m_owner->moveVectorHRot(kItemObjPi + m_owner->m_rotBaseY, zero,
		                        safeDist / kItemObjSafeMoveDivisor, 3);
	}

	Detach();
	m_worldPosition = safePos;

	if (throwItem != 0) {
		float moveSpeed;
		if (m_lastStateId == 0xC) {
			moveSpeed = speed;
		} else {
			moveSpeed = kItemObjThrowMoveSpeed;
		}

		float ownerCos = (float)cos((double)m_owner->m_rotTargetY);
		float ownerSin = (float)sin((double)m_owner->m_rotTargetY);
		const CVector& moveVec = CVector(ownerSin, kItemObjMotionStep, ownerCos);
		MoveVector(reinterpret_cast<Vec*>(const_cast<CVector*>(&moveVec)), moveSpeed, 1, 0, 1, 0);
	}

	m_owner = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80125650
 * PAL Size: 916b
 * EN Address: 0x80124980
 * EN Size: 916b
 * JP Address: 0x801214FC
 * JP Size: 916b
 */
void CGItemObj::carry(CGPartyObj* partyObj, int carryState, int carryMode)
{
	CFlatRuntime::CStack stack[3];
	int canSystemCall;

	if (carryState == 0) {
		canSystemCall = ItemIsGbaCaravan(partyObj);

		m_owner = partyObj;
		m_carryFrame = carryMode;

		if (carryMode == 0) {
			const CVector& attachOffset = CVector(kItemObjZero, kItemObjZero, kItemObjZero);
			Vec* attachOffsetPtr = reinterpret_cast<Vec*>(const_cast<CVector*>(&attachOffset));
			bool useBossAttachName = Game.m_gameWork.m_menuStageMode != 0 && ItemIsGbaCaravan(partyObj);

			CGObject* attachSelf = this;
			attachSelf->Attach(partyObj, const_cast<char*>(useBossAttachName ? s_itemAttachCenterItem3 : s_itemAttachLeftItem), attachOffsetPtr);
			changeStat(0, 0, 0);
			m_bodyEllipsoidRadius = kItemObjZero;
		} else {
			changeStat(0xB, 0, 0);
		}
	} else if (carryState == 1 || carryState == 2) {
		canSystemCall = ItemIsGbaCaravan(m_owner);

		m_carryFrame = carryMode;

		if (carryMode == 0) {
			safeDetach(0, kItemObjZero);
			changeStat(0, 0, 0);
			m_itemJumpCountdown = kItemObjExpandFrames;
			m_bodyEllipsoidRadius = kItemObjZero;
		} else {
			changeStat(carryState == 1 ? 0xC : 0xD, 0, 0);
		}

		m_lifeTimer = kItemObjReleaseLifetime;
	}

	if ((m_objectFlags & 0x10) != 0 && canSystemCall != 0) {
		stack[0].m_word = 3;
		stack[1].m_word = carryState != 0;
		stack[2].m_word = 0;
		gCFlatRuntime().SystemCall(0, 1, 9, 3, stack, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012564c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onChangePrg(int)
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
void CGItemObj::statPot()
{
	PartMng.pppSetLocSlot(m_particleSlot, &m_worldPosition);

	switch (m_subState) {
	case 0:
		if (m_subFrame == 0) {
			int particleNoA;
			int particleNoB;

			if (m_worldParamA == 0xE) {
				particleNoA = 0x19;
				particleNoB = 0x1E;
			} else {
				particleNoA = 0x18;
				particleNoB = 0x1D;
			}

			putParticle(particleNoA | 0x100, 0, &m_worldPosition, kItemObjUnitScale, 0);
			putParticle(particleNoB | 0x100, m_particleSlot, &m_worldPosition, kItemObjUnitScale, 0);
			playSe3D(0x1A, 0x32, 0x96, 0, 0);
			m_displayFlags &= ~1;
			m_bgColMask &= 0xFFFFFFF1;
			m_moveOffset.x = m_moveOffset.z = kItemObjZero;
			m_bgColMask |= 0x80000;

			const CVector& damageOffset = CVector(kItemObjZero, kItemObjZero, kItemObjZero);
			SetDamageCol(0, "f051_root", kItemObjDamageRadius, kItemObjDamageRadius,
			             reinterpret_cast<Vec*>(const_cast<CVector*>(&damageOffset)));
			m_damageColliders[0].m_hitMask = 9;
		}
		break;
	case 1:
		if (m_subFrame == kItemObjParticleEndFrame) {
			ItemCFlatRuntime()->EndParticleSlot(m_particleSlot, 0);
		}
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801254cc
 * PAL Size: 384b
 * EN Address: 0x801247FC
 * EN Size: 384b
 * JP Address: 0x80121378
 * JP Size: 384b
 */
void CGItemObj::onFrameAlways()
{
	int countdown = m_itemJumpCountdown;

	if (countdown != 0) {
#ifdef VERSION_GCCP01
		const float& scale = kItemObjWobblePhaseScale;
#endif
		countdown--;
		m_itemJumpCountdown = countdown < 0 ? 0 : countdown;
		float radius = m_savedBodyRadius * (float)(kItemObjExpandFrames - m_itemJumpCountdown);
#ifdef VERSION_GCCP01
		m_bodyEllipsoidRadius = radius * scale;
#else
		m_bodyEllipsoidRadius = radius / 10.0f;
#endif
	}

	if (m_worldParamA == 0xA) {
		int canUseTrace;

		if (static_cast<int>(Game.m_gameWork.m_gameInitFlag) != 0 &&
		    CFlatRuntime2Storage().m_gameFlagBits.m_flagBit3 != 0 &&
		    CFlatRuntime2Storage().m_gameFlagBits.m_flagBit2 != 0 &&
		    m_weaponNodeFlagBits.m_prg != 0 &&
		    static_cast<int>(CFlatCenterState()) == 0 && m_owner == 0) {
			canUseTrace = true;
		} else {
			canUseTrace = false;
		}

		if (canUseTrace && CFlatItemTraceParticleSlot() == 0) {
			CFlatItemTraceParticleSlot() = ItemCFlatRuntime()->GetFreeParticleSlot();
			putParticleTrace(0x141, CFlatItemTraceParticleSlot(), this, kItemObjUnitScale, 0);
		} else if (!canUseTrace && CFlatItemTraceParticleSlot() != 0) {
			ItemCFlatRuntime()->EndParticleSlot(CFlatItemTraceParticleSlot(), 0);
			CFlatItemTraceParticleSlot() = 0;
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
	int worldParamA = m_worldParamA;
	SItemFlatRow* particleRows = reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2]);
	int particleAttr = particleRows[hitParam->m_particleIndex].m_attribute;

	if (worldParamA == 0xD || worldParamA == 0xE) {
		if (((particleAttr == 0 || particleAttr == 4) && worldParamA == 0xD) ||
		    (particleAttr == 1 && worldParamA == 0xE)) {
			int particleNo;
			int classControl;

			switch (particleAttr) {
			case 1:
				particleNo = 0x20;
				classControl = 0x491;
				break;
			case 0:
				particleNo = 0x1F;
				classControl = 0x492;
				break;
			case 4:
				particleNo = 0x2F;
				classControl = 0x493;
				break;
			}

			ItemCFlatRuntime()->EndParticleSlot(m_particleSlot, 0);
			ItemCFlatRuntime()->ResetParticleWork(particleNo | 0x100, m_particleSlot);
			ItemCFlatRuntime()->SetParticleWorkPos(m_worldPosition, kItemObjZero);
			ItemCFlatRuntime()->SetParticleWorkCol(9, 0, kItemObjUnitScale);
			ItemCFlatRuntime()->SetParticleWorkParam(classControl, this);
			ItemCFlatRuntime()->PutParticleWork();
			m_bgColMask &= 0xFFF7FFFF;
			addSubStat();
		}
	} else if ((worldParamA == 0xCB && m_lastStateId == 0x24) || m_lastStateId == 0x25) {
		if ((static_cast<unsigned int>(particleAttr - 0x66) <= 1U) || (particleAttr == 0x65)) {
			int classId = hitParam->m_classId;
			CGObject* classObj;

			if (classId != 0) {
				classObj = reinterpret_cast<CGObject*>(ItemCFlatRuntime()->intToClass(classId));
			} else {
				classObj = 0;
			}

			unsigned short cid = classObj->GetCID();

			if ((cid & 0x6D) == 0x6D && m_owner == classObj) {
				changeStat(0x26, 0, 0);
			}
		}
	} else {
		return;
	}

	ItemCFlatRuntime()->IgnoreParticle(effectIndex, this);
}

/*
 * --INFO--
 * PAL Address: 0x80124FE0
 * PAL Size: 700b
 * EN Address: 0x80124310
 * EN Size: 700b
 * JP Address: 0x80120E8C
 * JP Size: 700b
 */
void CGItemObj::loadModel()
{
	int modelNo = -1;
	int modelVariant = 0;
	int modelFlag = 0;
	unsigned long animFlags = (unsigned long)-1;
	char* standAnim = const_cast<char*>(sStandAnim);
	int useParticleTable = 1;
	int itemType = m_worldParamA;

	switch (itemType) {
	case 0xA:
		modelNo = 8;
		useParticleTable = 0;
		break;
	case 0xC:
		modelNo = 0x27;
		useParticleTable = 0;
		break;
	case 0xD:
		modelNo = 0x33;
		useParticleTable = 0;
		break;
	case 0xE:
		modelNo = 0x33;
		modelVariant = 1;
		useParticleTable = 0;
		break;
	case 0x12:
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x1F:
	case 0x20:
	case 0x21:
	case 0x24: {
		const SItemFlatRow* itemRows = reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2]);
		int itemEntry = itemRows[m_worldParamB].m_model;

		m_ownerSlot = 1;
		modelNo = itemEntry & 0xFFF;
		modelVariant = itemEntry >> 0xC;
		m_stateFlags0Bits.unk4 = 1;
		m_lifeTimer = kItemObjReleaseLifetime;
		animFlags = 0x12;
		modelFlag = 1;
		break;
	}
	case 0xCB:
	default:
		break;
	}

	if (modelNo >= 0) {
		LoadModel(3, modelNo, modelVariant, modelFlag);
		LoadAnim(standAnim, 0, 0, 3, animFlags);
		SetAnimSlot(0, 0);
		PlayAnim(0, 1, 0, -1, -1, 0);
	}

	if (m_worldParamA == 0x12) {
		DispCharaParts(0);
		m_stateFlags0Bits.unk3 = 1;
	}

	if (useParticleTable != 0) {
		for (int i = 0; i < 3; i++) {
			if (i != 0 || m_createFlags != 1) {
				const SItemFlatRow* itemRow = &reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2])[m_worldParamB];
				int particleNo = itemRow->m_particles[i];

				if (particleNo != 0xFFFF) {
					const float& particleScaleStep = kItemObjFineStep;
					const float& particleScaleBase = kItemObjParticleScaleBase;
					float particleScale =
					    particleScaleStep * static_cast<float>(itemRow->m_fineValue) + particleScaleBase;
					putParticle(particleNo | 0x100, m_particleSlot, this, particleScale, 0);
				}
			}
		}
	}

	if (m_worldParamA == 0xCB) {
		const float& randBase = kItemObjMotionStep;
		const float& randRange = kItemObjParticleRandomRange;
		m_moveTimer = randBase - Math.RandF(randRange);
		m_weaponNodeFlagBits.m_unk04 = 0;
	}

	m_flagBits.bits.unk0 = 1;
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
	m_savedBodyRadius = m_bodyEllipsoidRadius;
	m_createFlags = static_cast<u16>((g_tempFlag >> 3) & 1);
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
	if (m_weaponNodeFlagBits.m_unk20 != 0) {
		CCharaPcs::CHandle* charaHandle = m_charaModelHandle;
		bool hasModel = false;
		if (charaHandle != 0 && charaHandle->m_model != 0) {
			hasModel = true;
		}

		if (hasModel && m_worldParamA == 0xCB && 0.0f < m_screenDepth &&
		    0.0f != m_currentAlpha) {
			font->SetTlut(7);

			font->SetColor(CColor(0xFF, 0xFF, 0xFF, 255.0f * m_currentAlpha).color);

			const char* name = Game.m_cFlatDataArr[1].TableStrings(2)[m_memoryCapsuleNameIndex];
			float width = font->GetWidth(name);
			float depthScale = kItemObjUnitScale / (m_screenDepth - kItemObjHeightOffset);
			float posY = 224.0f - 224.0f * m_projection.z * depthScale;
			float posZ = m_projection.w * depthScale;
			float posX =
			    -(0.5f * width - (320.0f * m_projection.y * depthScale + 320.0f));

			font->SetPosX(posX);
			font->SetPosY(posY - 11.0f);
			font->SetPosZ(posZ);
			font->Draw(name);
		}
	}
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
	for (CGItemObj* itemObj = ItemCFlatRuntime()->FindGItemObjFirst(); itemObj != 0;
	     itemObj = ItemCFlatRuntime()->FindGItemObjNext(itemObj)) {
		CGObject* object = itemObj;

		if ((object->m_objectFlags & 0x10) == 0) {
			Vec bottom = object->m_worldPosition;
			bottom.y += kItemObjHeightOffset;
			Vec move;

			move.x = kItemObjZero;
			move.z = kItemObjZero;
			move.y = kItemObjGroundProbeDown;
			unsigned int mapMask = object->m_bgHitMask;
			CMapCylinder cylinder;
			cylinder.m_bottom = bottom;
			cylinder.m_axis.x = kItemObjZero;
			cylinder.m_axis.y = kItemObjGroundProbeDown;
			cylinder.m_axis.z = kItemObjZero;
			cylinder.m_radius = kItemObjZero;

			if (MapMng.CheckHitCylinderNear(&cylinder, &move, mapMask) != 0 &&
			    g_hit_lpface_min->m_groupIndex == state) {
				object->m_groundHitOffset.y += jump;
			}
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
	for (CGItemObj* itemObj = ItemCFlatRuntime()->FindGItemObjFirst(); itemObj != 0;
	     itemObj = ItemCFlatRuntime()->FindGItemObjNext(itemObj)) {
		if (itemObj->m_owner == 0 &&
		    itemObj->m_stateFlags0Bits.unk4 != 0) {
			itemObj->CFlatRuntime::CObject::m_flagBits.m_deleteFlag = 1;
		}
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
	for (CGItemObj* itemObj = ItemCFlatRuntime()->FindGItemObjFirst(); itemObj != 0;
	     itemObj = ItemCFlatRuntime()->FindGItemObjNext(itemObj)) {
		if (itemObj->m_owner == 0 &&
		    itemObj->m_stateFlags0Bits.unk4 != 0) {
			if (show != 0) {
				itemObj->m_displayFlags &= 0xffbfffff;
			} else {
				itemObj->m_displayFlags |= 0x400000;
			}
		}
	}
}

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
