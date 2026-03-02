#include "ffcc/partyobj.h"
#include "ffcc/gobjwork.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/p_game.h"

#include <math.h>

extern "C" int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
extern "C" void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
extern "C" void GetHitFaceNormal__7CMapObjFP3Vec(void*, Vec*);
extern "C" int CanCreateFromScript__9CGItemObjFv();
extern "C" void* CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(
    int type, int createMode, int itemId, CGObject* owner, float arg, void* cfs);

extern float FLOAT_80331a78;
extern float FLOAT_80331a9c;
extern float FLOAT_80331aa0;
extern float FLOAT_80331ac4;
extern float FLOAT_80331ac8;
extern float FLOAT_80331acc;
extern float FLOAT_80331ad0;
extern float FLOAT_80331ad4;
extern float FLOAT_80331ad8;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CATEGOLY2TYPE(int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onCreate()
{
	CGCharaObj::onCreate();
}

/*
 * --INFO--
 * PAL Address: 0x80124840
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onDestroy()
{
	unsigned char* partyFlags = reinterpret_cast<unsigned char*>(this) + 0x6B8;
	if ((*partyFlags & 0x04) != 0) {
		addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
		*partyFlags &= ~0x04;
	}

	CGCharaObj::onDestroy();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onChangeStat(int)
{
	CGCharaObj::onChangeStat(0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onCancelStat(int)
{
	CGCharaObj::onCancelStat(0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::menu()
{
	command();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onFrameAlways()
{
	CGPrgObj::onFrameAlways();
	CheckMenu();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::CheckMenu()
{
	canPlayerGoMenu();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onFramePreCalc()
{
	CGCharaObj::onFramePreCalc();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onFramePostCalc()
{
	CGCharaObj::onFramePostCalc();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::command()
{
	shouki();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::callCommandScript(int, CGObject*)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::shouki()
{
	commandFinished();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onFrameStat()
{
	CGCharaObj::onFrameStat();
}

/*
 * --INFO--
 * PAL Address: 0x80120B74
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onAnimPoint(int no, int dataNo)
{
	CGCharaObj::onAnimPoint(no, dataNo);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::enableAttackCol(int attackNo, int onOff, int isFriendly)
{
	CGCharaObj::enableAttackCol(attackNo, onOff, isFriendly);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::enableDamageCol(int onOff)
{
	CGCharaObj::enableDamageCol(onOff);
}

/*
 * --INFO--
 * PAL Address: 0x8012098C
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPartyObj::getReplaceStat(int state)
{
	if (state != 7) {
		if (state == -20) {
			state = -1;
		} else {
			state = CGCharaObj::getReplaceStat(state);
		}
	}

	return state;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statCharge()
{
	moveCenterTargetParticle();
	checkTargetParticle();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statAttackSel()
{
	onStatAttack(0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::getBestAngleObject(float, float)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onStatAttack(int)
{
	if (m_stateFrame == 0) {
		m_rotationZ = m_rotationY;
		m_rotationY = 0.0f;
		unsigned char* flags = reinterpret_cast<unsigned char*>(this) + 0x6B8;
		*flags &= 0x7F;
		*flags &= 0xBF;
		getBestAngleObject(FLOAT_80331ad4 * m_bodyEllipsoidRadius, FLOAT_80331ad8);
		return;
	}

	if (isLoopAnim() != 0) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onStatShield()
{
	if (m_subState == 1 && m_subFrame > 0) {
		changeSubStat(3);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011F9A8
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::putComboParticle()
{
	putParticle(0x153, 0, reinterpret_cast<CGObject*>(this), 0.0f, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::putTargetParticle(int, int)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<Vec*>(self + 0x678) = *reinterpret_cast<Vec*>(self + 0x15C);
	*reinterpret_cast<Vec*>(self + 0x66C) = *reinterpret_cast<Vec*>(self + 0x15C);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::endTargetParticle()
{
	*(reinterpret_cast<unsigned char*>(this) + 0x6B8) &= 0xAF;
}

/*
 * --INFO--
 * PAL Address: 0x8011F574
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPartyObj::isDispTarget()
{
	if ((m_lastStateId == 2 || m_lastStateId == 6) &&
	    (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x668) != 0)) {
		return 1;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8011F520
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPartyObj::isRideTarget()
{
	if ((m_lastStateId == 2 || m_lastStateId == 6) &&
	    (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x668) != 0) &&
	    ((*reinterpret_cast<unsigned char*>(this) + 0x6B8) & 0x80) != 0) {
		return 1;
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address:	8011ead4
 * PAL Size:	2636b
 * EN Address:	TODO
 * EN Size:	TODO
 * JP Address:	TODO
 * JP Size:	TODO
 */
void CGPartyObj::checkTargetParticle()
{
	// Basic particle checking implementation
	// This is a simplified version focusing on compilation and basic structure
	
	// First pass: keep center/target vectors valid while porting larger logic.
	Vec targetPos;
	targetPos.x = 0.0f;
	targetPos.y = 0.0f; 
	targetPos.z = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x8011E870
 * PAL Size: 612b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::moveCenterTargetParticle()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int step = *reinterpret_cast<int*>(self + 0x530);

	if (step >= 5) {
		return;
	}

	float wave = static_cast<float>(sin(FLOAT_80331ac8 * ((float)(step + 1) / FLOAT_80331ac4)));

	Vec centerPos = *reinterpret_cast<Vec*>(self + 0x678);
	Vec targetPos = *reinterpret_cast<Vec*>(self + 0x66C);
	Vec toTarget;
	Vec movement;
	Vec hitPos;
	Vec moveVec = {FLOAT_80331a78, FLOAT_80331acc, FLOAT_80331a78};
	Vec yOffset = {FLOAT_80331a78, FLOAT_80331ad0, FLOAT_80331a78};
	Vec hitNormal;

	PSVECSubtract(&targetPos, &centerPos, &toTarget);
	PSVECScale(&toTarget, &movement, wave);
	PSVECAdd(&centerPos, &movement, &hitPos);

	CMapCylinder hitCylinder;
	PSVECAdd(&hitPos, &yOffset, &hitCylinder.m_bottom);
	hitCylinder.m_direction = moveVec;
	hitCylinder.m_radius = FLOAT_80331a78;
	hitCylinder.m_height = FLOAT_80331aa0;
	hitCylinder.m_top.x = FLOAT_80331a9c;
	hitCylinder.m_top.y = FLOAT_80331a9c;
	hitCylinder.m_top.z = FLOAT_80331a9c;
	hitCylinder.m_direction2.x = FLOAT_80331aa0;
	hitCylinder.m_direction2.y = FLOAT_80331aa0;
	hitCylinder.m_direction2.z = FLOAT_80331aa0;

	if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &hitCylinder, &moveVec, 0x30) != 0) {
		void* hitObj = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MapMng) + 0x22A88);
		CalcHitPosition__7CMapObjFP3Vec(hitObj, &hitPos);
		GetHitFaceNormal__7CMapObjFP3Vec(hitObj, &hitNormal);

		unsigned char* work = reinterpret_cast<unsigned char*>(m_scriptHandle);
		*reinterpret_cast<Vec*>(work + 0xBB8) = hitNormal;
	}

	unsigned char* work = reinterpret_cast<unsigned char*>(m_scriptHandle);
	*reinterpret_cast<Vec*>(work + 0xBAC) = hitPos;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onStatMagic()
{
	moveCenterTargetParticle();
	checkTargetParticle();
	if (isLoopAnim() != 0) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onStatDie()
{
	if (m_subState == 0) {
		if (m_subFrame == 0) {
			reinterpret_cast<CGPrgObj*>(this)->reqAnim(0, 0, 0);
		}
		if (isLoopAnimDirect() != 0) {
			changeSubStat(1);
		}
		return;
	}

	if (m_subState == 1) {
		if (m_subFrame == 0) {
			m_bgColMask &= 0xFFFEFFF1;
			enableDamageCol(1);
			if ((*(reinterpret_cast<unsigned char*>(this) + 0x6B8) & 0x04) != 0) {
				putParticleFromItem(0x220, 2, 0, &m_worldPosition);
				putParticleFromItem(0x220, 3, 0, &m_worldPosition);
				changeSubStat(2);
			}
		} else if (m_subFrame == 0x19) {
			changeStat(0x22, 0, 0);
		}
		return;
	}

	if (m_subState == 2 && m_subFrame > 0xBA) {
		changeStat(0x22, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statAlive()
{
	setAlive(1, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onPush(CGBaseObj*, int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onTalk(CGBaseObj*, int)
{
}

/*
 * --INFO--
 * PAL Address: 0x8011E0D8
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::commandFinished()
{
	*(reinterpret_cast<unsigned char*>(this) + 0x6B8) &= 0x7F;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::carry(int, CGObject*, int)
{
	if (m_lastStateId == 0x0B) {
		changeStat(0, 0, 0);
	}
	setIdleMotion();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statCarry()
{
	if (isLoopAnim() != 0) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statPut()
{
	if (isLoopAnim() != 0) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statPickup()
{
	if (isLoopAnim() != 0) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::bonus(int, int, CGPrgObj*)
{
	// Intentionally lightweight first-pass: original function is item/score heavy.
	commandFinished();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGPartyObj::canPlayerUseItem()
{
	unsigned char* weaponFlags = reinterpret_cast<unsigned char*>(&m_weaponNodeFlags);

	if ((int)((unsigned int)weaponFlags[0] << 0x18) < 0) {
		unsigned char* self = reinterpret_cast<unsigned char*>(this);
		if (((int)((unsigned int)weaponFlags[1] << 0x18) < 0) &&
		    ((int)((unsigned int)self[0x63C] << 0x18) < 0) &&
		    (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0)) {
			return 1;
		}
	}

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::canPlayerGoMenu()
{
	if (m_lastStateId == 0) {
		return;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::useItem(int)
{
	if (canPlayerUseItem() == 0) {
		return;
	}
	changeStat(0x1A, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGPartyObj::canPlayerPutItem()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	unsigned char* weaponFlags = reinterpret_cast<unsigned char*>(&m_weaponNodeFlags);

	if ((int)((unsigned int)weaponFlags[0] << 0x18) < 0 &&
	    (int)((unsigned int)weaponFlags[1] << 0x18) < 0 &&
	    (int)((unsigned int)self[0x63C] << 0x18) < 0 &&
	    (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) &&
	    (*reinterpret_cast<int*>(self + 0x6F0) == 0)) {
		if (Game.game.m_gameWork.m_menuStageMode != 0 && CanCreateFromScript__9CGItemObjFv() == 0) {
			return 0;
		}
		return 1;
	}

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::putItem(int)
{
	if (canPlayerPutItem() == 0) {
		return;
	}
	changeStat(0x1B, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::putGil(int)
{
	if (canPlayerPutItem() == 0) {
		return;
	}
	changeStat(0x1B, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statRebound()
{
	if (isLoopAnim() != 0) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statKorobi()
{
	if (m_subState == 0) {
		if (m_subFrame == 0) {
			damageDelete();
			carry(1, (CGObject*)0, 1);
			reqAnim(0x1E, 0, 0);
		}
		if (isLoopAnim() != 0) {
			changeSubStat(1);
		}
		return;
	}

	if (m_subState == 1) {
		if (m_subFrame == 0) {
			reqAnim(0x1F, 0, 0);
		}
		if (isLoopAnim() != 0) {
			changeSubStat(2);
		}
		return;
	}

	if (m_subState == 2) {
		if (m_subFrame == 0) {
			reqAnim(0x20, 0, 0);
		}
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statHide()
{
	commandFinished();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statJump()
{
	if (isLoopAnim() != 0) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statWeaponChange()
{
	changeWeapon(0, 0, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::changeWeapon(int, int, int)
{
	setIdleMotion();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::CheckGameOver()
{
	Game.game.m_gameWork.m_gameOverFlag = 1;
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party == nullptr) {
			continue;
		}
		if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(party->m_scriptHandle) + 0x1C) != 0) {
			Game.game.m_gameWork.m_gameOverFlag = 0;
			return;
		}
		if ((*(reinterpret_cast<unsigned char*>(party) + 0x6B8) & 0x04) != 0) {
			Game.game.m_gameWork.m_gameOverFlag = 0;
			return;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::SetBonusCondition(int, int, int, int, int)
{
	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6F8) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::InitFinished()
{
	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCurrentWeaponItem(
	    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6DC),
	    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6E0));
	enableDamageCol(1);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::IsDispRader()
{
	(void)CGObject::IsDispRader();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::ChangeCommandMode(int)
{
	*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0x6F4) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::checkAndSetWeapon()
{
	setIdleMotion();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::changeMotionMode(int)
{
	changeStat(0, 0, 0);
	setIdleMotion();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::setIdleMotion()
{
	if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6F0) == 0) {
		if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		} else {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x30, 1);
		}
	} else {
		SetAnimSlot(0x0B, 0);
		SetAnimSlot(0x0C, 1);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::setAlive(int, int)
{
	enableDamageCol(1);
	setIdleMotion();
	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
		m_bgColMask &= 0xFFFEFFF1;
	} else {
		m_bgColMask |= 0x1000E;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::PutMemoryCapsule(int, int, int, int, char*)
{
	int args[5];
	args[0] = 0;
	args[1] = 0;
	args[2] = 0;
	args[3] = 0;
	args[4] = 0;
	CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(0, 2, 399, this, FLOAT_80331a78, args);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onDamaged(CGPrgObj*)
{
	CGPrgObj::onDamaged((CGPrgObj*)0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onAttacked(CGPrgObj*)
{
	CGPrgObj::onAttacked((CGPrgObj*)0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void stageWeather()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void magicReady()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void chooseMagic()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void decMagic(int)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcWeightMax()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::gpmCalcDist(Vec*, float&)
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::gpmCol()
{
	gpmMove();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::ghostPartyMog()
{
	gpmMove();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::gpmMove()
{
}

/*
 * --INFO--
 * PAL Address: 0x8011A918
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::sysControl(int controlType, int controlValue)
{
	if (controlType == 0x13) {
		reinterpret_cast<CCaravanWork*>(m_scriptHandle)->BackupTutorialItem(controlValue);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onDrawDebug(CFont*, float, float&, float)
{
	CGObject::onDrawDebug(0, 0.0f, *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x6FC), 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x8011a57c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onDraw()
{
	CGObject::onDraw();
}

/*
 * --INFO--
 * PAL Address: 0x8011a574
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPartyObj::GetCID()
{
	return 0x6D;
}
