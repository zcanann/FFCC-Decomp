#include "ffcc/monobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/gobjwork.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/vector.h"
#include "PowerPC_EABI_Support/Runtime/ptmf.h"

#include <math.h>
#include <string.h>

extern CMath Math;
extern unsigned char DbgMenuPcs[];
extern unsigned char ARRAY_8030918c[];

extern "C" void __ptmf_scall(void*, void*);
extern "C" int calcPolygonGroup__6CAStarFP3Veci(void*, Vec*, int);

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
	CGCharaObj* charaObj = reinterpret_cast<CGCharaObj*>(this);
	charaObj->onCreate();

	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<unsigned int*>(mon + 0x6C4) = static_cast<unsigned int>(-1);
	*reinterpret_cast<unsigned short*>(mon + 0x6E4) = 0;
	*reinterpret_cast<unsigned short*>(mon + 0x6E6) = 0;
	*reinterpret_cast<unsigned int*>(mon + 0x6C8) = 0;
	*reinterpret_cast<unsigned int*>(mon + 0x6CC) = 0;
	mon[0x6B4] = 0;
	mon[0x6B8] = 0;
	mon[0x6B9] = 0;
	mon[0x6BA] = 0;
	mon[0x6BC] = 0;
	mon[0x6BD] = 0;
	mon[0x6BE] = 0;
	*reinterpret_cast<unsigned int*>(mon + 0x6F0) = 0;
	*reinterpret_cast<unsigned int*>(mon + 0x6F4) = 0;
	mon[0x6BF] = 0;
	mon[0x6C0] = 0;
	mon[0x6C2] = 0;
	mon[0x6C3] = 0;
	*reinterpret_cast<unsigned int*>(mon + 0x6D8) = 0;
	*reinterpret_cast<unsigned int*>(mon + 0x6DC) = 0;
	mon[0x6BB] = 0;
	*reinterpret_cast<unsigned int*>(mon + 0x704) = 0;
	memset(mon + 0x70C, 0, 0x34);
	*reinterpret_cast<unsigned int*>(mon + 0x6E0) = 0;
	mon[0x6C1] = 0;
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
	CGCharaObj* charaObj = reinterpret_cast<CGCharaObj*>(this);
	charaObj->onDestroy();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::resetWork()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onFramePreCalc()
{
	// TODO
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
	mon[0x6B9] = 1;
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::undeadOff()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::undeadOn()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::rotTarget(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onStatAttack(int)
{
	// TODO
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
	unsigned int delay = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + attackKind * 0x48 + 0xA);
	if (delay == 0xFFFF) {
		delay = 0;
	}

	int stageRank = 0;
	if (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
		stageRank = Game.game.m_gameWork.m_bossArtifactStageTable[Game.game.m_gameWork.m_bossArtifactStageIndex];
		if (2 < stageRank) {
			stageRank = 2;
		}
	}

	if (0 < stageRank) {
		delay -= *reinterpret_cast<unsigned short*>(Game.game.unk_flat3_field_8_0xc7dc + stageRank * 2 + 0x58);
		delay &= ~((int)delay >> 31);
	}

	if (delay == 0) {
		reinterpret_cast<CGPrgObj*>(this)->changeStat(0, 0, 0);
		return;
	}

	int range = (int)delay / 5 + ((int)delay >> 31);
	range -= range >> 31;
	if (range < 1) {
		range = 1;
	}

	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<unsigned int*>(mon + 0x6F0) = delay + Math.Rand(range);
	reinterpret_cast<CGPrgObj*>(this)->changeStat(0x11, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::getNearParty(int, int, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onChangeStat(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::setActionParam(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onCancelStat(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::isValidTarget()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::seKiduki()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onFrameStat()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onStatMagic()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onAnimPoint(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::enableAttackCol(int, int, int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::getReplaceStat(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onStatShield()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onStatDie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onDrawDebug(CFont*, float, float&, float)
{
	// TODO
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
	mon[0x6C0] = 1;

	if (__ptmf_test(reinterpret_cast<__ptmf*>(mon + 0x780)) != 0) {
		__ptmf_scall(this, mon + 0x708);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onDamaged(CGPrgObj*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::aiTarget()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::aiTargetAttackRomMon(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::checkCol(int, float, float, float*, int*)
{
	// TODO
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
void CGMonObj::mlAttackCheck(int)
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::aiSeq(int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::statWatch()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::statAround()
{
	// TODO
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
			char hasNearParty = 0;
			if (mon[0x6B9] == 0) {
				for (int i = 0; i < 4; i++) {
					CGPartyObj* party = Game.game.m_partyObjArr[i];
					if (party != nullptr && *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(party) + 0x668) != 0) {
						float dist = PSVECDistance(
							reinterpret_cast<Vec*>(reinterpret_cast<unsigned char*>(party) + 0x66C),
							&object->m_worldPosition
						);
						if (dist < 60.0f + object->m_bodyEllipsoidRadius) {
							hasNearParty = 1;
							break;
						}
					}
				}
			}

			if (hasNearParty != mon[0x6C3]) {
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
				mon[0x6C3] = hasNearParty;
			}
		}

		reinterpret_cast<CMonWork*>(object->m_scriptHandle)->CalcStatus();
		__ptmf_scall(this, mon + 0x708);

		unsigned short stepSeRaw = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1BE);
		int stepSeId = 0;
		if (stepSeRaw != 0xFFFF) {
			stepSeId = (stepSeRaw & 0xFF) + ((stepSeRaw >> 8) * 1000);
		}

		if (stepSeId != 0) {
			int& stepSeHandle = *reinterpret_cast<int*>(mon + 0x704);
			if (object->m_currentAnimSlot == static_cast<char>(object->m_animStartFrame)) {
				if (stepSeHandle == 0) {
					stepSeHandle = reinterpret_cast<CGPrgObj*>(this)->playSe3D(stepSeId, 0x32, 0x96, 0, (Vec*)0);
				} else {
					Sound.ChangeSe3DPos(stepSeHandle, &object->m_worldPosition);
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::InitFinished()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::initFinishedFuncDefault()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::setIceJEffect(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::IsDispRader()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::setRepop(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::statMove()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveAStar(int, int, Vec&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::moveFrame()
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);

	unsigned int& moveStateFlags = *reinterpret_cast<unsigned int*>(mon + 0x710);
	unsigned int& moveFlags = *reinterpret_cast<unsigned int*>(mon + 0x70C);
	Vec& moveTarget = *reinterpret_cast<Vec*>(mon + 0x718);
	float& moveSpeed = *reinterpret_cast<float*>(mon + 0x724);
	float& moveRange = *reinterpret_cast<float*>(mon + 0x728);
	unsigned int& moveLimitFrame = *reinterpret_cast<unsigned int*>(mon + 0x72C);
	int& moveFrame = *reinterpret_cast<int*>(mon + 0x730);
	int& moveChangeStat = *reinterpret_cast<int*>(mon + 0x738);
	float& moveSpeedRate = *reinterpret_cast<float*>(mon + 0x690);
	short& aStarGroupId = *reinterpret_cast<short*>(mon + 0x6A4);

	Vec local_68;
	Vec local_74;
	float in_f29 = 0.0f;

	if ((moveStateFlags & 1) != 0) {
		return;
	}

	__ptmf_scall(this, mon + 0x708);

	if ((moveFlags & 1) != 0) {
		unsigned char* target = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(mon + 0x714));
		local_68 = *reinterpret_cast<Vec*>(target + 0x15C);
		in_f29 = PSVECDistance(&local_68, &object->m_worldPosition);

		if (((moveFlags & 0x30000) != 0) && (*reinterpret_cast<unsigned int*>(ARRAY_8030918c) != 0)) {
			short targetAStarGroupId = *reinterpret_cast<short*>(target + 0x6A4);
			moveAStar(aStarGroupId, targetAStarGroupId, local_68);
		}
	} else if ((moveFlags & 2) != 0) {
		local_68 = moveTarget;
		in_f29 = PSVECDistance(&local_68, &object->m_worldPosition);

		if (((moveFlags & 0x30000) != 0) && (*reinterpret_cast<unsigned int*>(ARRAY_8030918c) != 0)) {
			int polygonGroup = calcPolygonGroup__6CAStarFP3Veci(DbgMenuPcs + 0x2A5C, &local_68, (int)object->m_moveVec.x);
			moveAStar(aStarGroupId, polygonGroup, local_68);
		}
	} else if ((moveFlags & 0x2000) != 0) {
		PSVECAdd(&object->m_worldPosition, &moveTarget, &local_68);
		in_f29 = PSVECDistance(&local_68, &object->m_worldPosition);
	}

	PSVECSubtract(&local_68, &object->m_worldPosition, &local_74);
	if ((moveFlags & 0x40) != 0) {
		local_74.x = -local_74.x;
		local_74.y = -local_74.y;
		local_74.z = -local_74.z;
	}

	CVector moveVec(local_74);
	float rotY = moveVec.GetRotateY();
	float distance = PSVECMag(&local_74);

	if (((moveFlags & 0x20) != 0) && (moveRange <= in_f29)) {
		moveStateFlags |= 1;
		__ptmf_scall(this, mon + 0x708);
		moveStateFlags |= 2;
		if ((moveFlags & 0x100) != 0) {
			reinterpret_cast<CGPrgObj*>(this)->changeStat(moveChangeStat, 0, 0);
		}
		return;
	}
	if (((moveFlags & 0x40) != 0) && (in_f29 < moveRange)) {
		moveStateFlags |= 1;
		__ptmf_scall(this, mon + 0x708);
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
		distance = PSVECMag(&local_74);
	}

	if (((moveFlags & 0x80) != 0) && (((int)((unsigned int)object->m_stateFlags0 << 0x19) | ((unsigned int)object->m_stateFlags0 >> 7)) < 0)) {
		moveStateFlags |= 1;
		__ptmf_scall(this, mon + 0x708);
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
			PSVECScale(&local_74, &moveDelta, (1.0f / distance) * stepDist);
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
		if (((moveFlags & 0x10) == 0) || (moveFrame < (int)moveLimitFrame)) {
			return;
		}
	}

	moveStateFlags |= 1;
	__ptmf_scall(this, mon + 0x708);
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
extern "C" void MonObjRelated(CGMonObj* monObj, int* targetIndex)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(monObj);
	int* chaseState = reinterpret_cast<int*>(mon + 0x6D8);
	int* chaseTimer = reinterpret_cast<int*>(mon + 0x6DC);
	int* targetPartyIdx = reinterpret_cast<int*>(mon + 0x6C4);

	switch (*chaseState) {
	case 1:
		if (targetIndex != NULL) {
			*targetIndex = *targetPartyIdx;
		}
		break;

	case 2:
		if (targetIndex != NULL) {
			*targetIndex = *targetPartyIdx;
		}
		*reinterpret_cast<unsigned char*>(mon + 0x6B8) = 1;
		break;

	case 5:
		if (*targetPartyIdx < 0) {
			memset(mon + 0x70C, 0, 0x34);
			*chaseState = 0;
			*chaseTimer = 0;
			*reinterpret_cast<unsigned char*>(mon + 0x6BB) = 1;
		}
		break;
	}

	if (*reinterpret_cast<unsigned char*>(mon + 0x6BB) == 0) {
		*chaseTimer += 1;
	} else {
		*reinterpret_cast<unsigned char*>(mon + 0x6BB) = 0;
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
	MonObjRelated(this, &targetIndex);
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
	unsigned char* script = reinterpret_cast<unsigned char*>(object->m_scriptHandle);
	unsigned short current = *reinterpret_cast<unsigned short*>(script + 0x1C);
	unsigned short max = *reinterpret_cast<unsigned short*>(script + 0x1A);

	if (branchType == 1) {
		if (current < (max >> 1)) {
			return 1;
		}
	} else if (branchType == 2) {
		if (current < (max / 3)) {
			return 2;
		}
		if (current < ((max * 2) / 3)) {
			return 1;
		}
	}

	return 0;
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
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);

	switch (controlType) {
	case 6:
		*reinterpret_cast<unsigned short*>(mon + 0x6D6) = 0;
		break;

	case 7:
		mon[0x6BE] = 1;
		*reinterpret_cast<unsigned int*>(mon + 0x6D8) = 4;
		*reinterpret_cast<unsigned int*>(mon + 0x6DC) = 0;
		mon[0x6BB] = 1;
		object->m_bgColMask &= 0xFFF7FFFD;
		object->m_displayFlags &= 0xFFFFFFFE;
		break;

	case 8:
		mon[0x6BE] = 0;
		break;

	case 0xC:
		mon[0x6C1] = 1;
		break;

	case 0xD:
		mon[0x6C1] = 0;
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

	case 0x15:
		object->m_weaponNodeFlags = (object->m_weaponNodeFlags & 0xF7) | 8;
		break;

	case 0x16:
		object->m_weaponNodeFlags &= 0xF7;
		break;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onChangePrg(int)
{
	// TODO
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
	// TODO
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
