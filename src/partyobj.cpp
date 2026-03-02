#include "ffcc/partyobj.h"
#include "ffcc/gobjwork.h"
#include "ffcc/pad.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/p_game.h"
#include "ffcc/itemobj.h"

#include <math.h>

extern "C" int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
extern "C" void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
extern "C" void GetHitFaceNormal__7CMapObjFP3Vec(void*, Vec*);
extern "C" int CanCreateFromScript__9CGItemObjFv();
extern "C" CGObject* FindGObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" void* CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(
    int type, int createMode, int itemId, CGObject* owner, float arg, void* cfs);
extern unsigned char CFlat[];

extern float FLOAT_80331a78;
extern float FLOAT_80331a9c;
extern float FLOAT_80331aa0;
extern float FLOAT_80331ac4;
extern float FLOAT_80331ac8;
extern float FLOAT_80331acc;
extern float FLOAT_80331ad0;
extern float FLOAT_80331ad4;
extern float FLOAT_80331ad8;

static unsigned short getPadHeldForSlot(int slot)
{
	if (Pad._452_4_ != 0 || (slot == 0 && Pad._448_4_ != -1)) {
		return 0;
	}

	int idx = slot & ~((~(Pad._448_4_ - slot | slot - Pad._448_4_) >> 31));
	return *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 0x4 + idx * 0x54);
}

static unsigned short getPadTrigForSlot(int slot)
{
	if (Pad._452_4_ != 0 || (slot == 0 && Pad._448_4_ != -1)) {
		return 0;
	}

	int idx = slot & ~((~(Pad._448_4_ - slot | slot - Pad._448_4_) >> 31));
	return *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + 0x8 + idx * 0x54);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CATEGOLY2TYPE(int value)
{
	switch (value) {
	case 0:
		return 0;
	case 1:
		return 9;
	case 2:
		return 6;
	case 3:
		return 2;
	default:
		return -1;
	}
}

/*
 * --INFO--
 * PAL Address: 0x801248a4
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onCreate()
{
	CGCharaObj::onCreate();

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<int*>(self + 0x6D0) = 0;
	*reinterpret_cast<int*>(self + 0x6C8) = 0;
	*reinterpret_cast<int*>(self + 0x6CC) = 0;
	*reinterpret_cast<int*>(self + 0x6BC) = 0;
	*reinterpret_cast<int*>(self + 0x6C0) = -1;
	*reinterpret_cast<unsigned short*>(self + 0x6D2) = 0;

	self[0x6B8] &= 0x7F;
	self[0x6B8] &= 0xF7;
	self[0x6B8] &= 0xBF;
	self[0x6B8] &= 0xDF;
	self[0x6B8] &= 0xEF;
	self[0x6B8] &= 0xFB;
	self[0x6B8] &= 0xFD;

	*reinterpret_cast<float*>(self + 0x5BC) = FLOAT_80331a78;
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
 * PAL Address: 0x80124540
 * PAL Size: 768b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onChangeStat(int state)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	self[0x6B8] &= 0xBF;

	switch (state) {
	case 0:
		self[0x6B8] |= 0x40;
		break;
	case 1: {
		int attackSel = *reinterpret_cast<int*>(self + 0x6C8);
		*reinterpret_cast<int*>(self + 0x550) = (attackSel == 0) ? 5 : ((attackSel == 1) ? 8 : 9);
		break;
	}
	case 2:
		*reinterpret_cast<int*>(self + 0x550) = 0x0F;
		*reinterpret_cast<int*>(self + 0x554) = 0x10;
		*reinterpret_cast<int*>(self + 0x558) = 0x11;
		if (*reinterpret_cast<int*>(self + 0x560) != 0x103) {
			calcCastTime(*reinterpret_cast<int*>(self + 0x560));
		}
		break;
	case 6:
		*reinterpret_cast<int*>(self + 0x550) = 0x12;
		*reinterpret_cast<int*>(self + 0x554) = 0x13;
		calcCastTime(*reinterpret_cast<int*>(self + 0x560));
		break;
	case 8:
		*reinterpret_cast<int*>(self + 0x550) = 0x15;
		*reinterpret_cast<int*>(self + 0x554) = 0x16;
		*reinterpret_cast<int*>(self + 0x558) = 0x17;
		*reinterpret_cast<int*>(self + 0x55C) = 0x18;
		break;
	default:
		break;
	}

	CGCharaObj::onChangeStat(state);
}

/*
 * --INFO--
 * PAL Address: 0x80123d50
 * PAL Size: 2032b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onCancelStat(int state)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);

	switch (m_lastStateId) {
	case 2:
		self[0x6B8] &= 0xBF;
		self[0x6B8] &= 0xDF;
		endPSlotBit(0x10);
		endPSlotBit(0x100);
		break;
	case 6:
		*reinterpret_cast<float*>(self + 0x4FC) = FLOAT_80331a78;
		break;
	case 9:
	case 0x0B:
	case 0x0C:
	case 0x0D:
	case 0x22:
		if (((self[0x6B8] & 0x04) != 0) && (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0)) {
			addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
			self[0x6B8] &= 0xFB;
		}
		enableDamageCol(1);
		setIdleMotion();
		if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
			*reinterpret_cast<float*>(self + 0x694) = 1.0f;
			m_bgColMask &= 0xFFFEFFF1;
		} else {
			endPSlotBit(0x10000);
			*reinterpret_cast<float*>(self + 0x694) = 0.5f;
			m_bgColMask |= 0x1000E;
		}
		break;
	case 0x0F:
		checkAndSetWeapon();
		break;
	case 0x14:
	case 0x15:
		enableDamageCol(1);
		break;
	default:
		break;
	}

	CGCharaObj::onCancelStat(state);
}

/*
 * --INFO--
 * PAL Address: 0x801238c8
 * PAL Size: 1160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::menu()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (Game.game.m_gameWork.m_gamePaused != 0) {
		return;
	}

	// Ghidra indicates this gates menu by controller role and stage mode.
	if ((self[0x6B8] & 0x10) == 0) {
		if (Game.game.m_gameWork.m_menuStageMode == 0) {
			command();
		}
		return;
	}

	// Local player can always force command handling in menu stage.
	if (m_animStateMisc == 0 || Game.game.m_gameWork.m_menuStageMode != 0) {
		command();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80123454
 * PAL Size: 1140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onFrameAlways()
{
	CGPrgObj::onFrameAlways();
	if (m_scriptHandle == nullptr) {
		return;
	}

	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0 || (m_lastMapIdHit != 1)) {
		LoadWeapon(-1, 0);
		LoadShield(-1);
	} else {
		int weaponItem;
		int weaponRef;
		reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCurrentWeaponItem(weaponItem, weaponRef);
		if (m_weaponModelHandle == nullptr) {
			if (weaponItem <= 0) {
				LoadWeapon(-1, 0);
			} else {
				LoadWeapon(weaponItem & 0xFFF, weaponItem >> 12);
			}
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->SetCurrentWeaponIdx(weaponRef);
			*(reinterpret_cast<unsigned char*>(this) + 0x6C4) &= 0xDF;
		}

		int shieldIndex = reinterpret_cast<short*>(m_scriptHandle)[0x2C];
		if (shieldIndex <= 0) {
			LoadShield(-1);
		}
	}

	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->CalcStatus();
	CheckMenu();
}

/*
 * --INFO--
 * PAL Address: 0x801233ec
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::CheckMenu()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->menu();
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x801230a0
 * PAL Size: 844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onFramePreCalc()
{
	CGCharaObj::onFramePreCalc();
}

/*
 * --INFO--
 * PAL Address: 0x80122fdc
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onFramePostCalc()
{
	if (m_scriptHandle == nullptr) {
		return;
	}

	if (Game.game.m_gameWork.m_menuStageMode != 0 &&
	    Game.game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
	    m_scriptHandle[0xED] != nullptr) {
		ghostPartyMog();
	} else {
		command();
		shouki();
	}

	*reinterpret_cast<CGBaseObj**>(reinterpret_cast<unsigned char*>(this) + 0x6E4) = (CGBaseObj*)0;
	*reinterpret_cast<CGBaseObj**>(reinterpret_cast<unsigned char*>(this) + 0x6E8) = (CGBaseObj*)0;
	*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x6EC) = 1000000.0f;
	CGCharaObj::onFramePostCalc();
}

/*
 * --INFO--
 * PAL Address: 0x80121f40
 * PAL Size: 4252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::command()
{
	if (m_scriptHandle == nullptr) {
		return;
	}

	canPlayerGoMenu();
	shouki();

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int mode = *reinterpret_cast<short*>(self + 0x6F4);
	CGObject* target = *reinterpret_cast<CGObject**>(self + 0x6E4);
	callCommandScript(mode, target);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::callCommandScript(int mode, CGObject* target)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<CGObject**>(self + 0x6E4) = target;

	switch (mode) {
	case 0:
		if (target != nullptr && m_lastStateId == 0 && target != this) {
			changeStat(0x0C, 0, 0);
		}
		break;
	case 1:
		if (m_lastStateId == 0) {
			changeStat(1, 0, 0);
		}
		break;
	case 2:
		if (canPlayerUseItem() != 0) {
			useItem(0);
		}
		break;
	case 3:
		if (canPlayerPutItem() != 0) {
			putItem(0);
		}
		break;
	case 4:
		if (m_lastStateId == 0) {
			changeStat(0x0B, 0, 0);
		}
		break;
	case 5:
		if (m_lastStateId == 0) {
			changeStat(0x0D, 0, 0);
		}
		break;
	default:
		break;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80121ba4
 * PAL Size: 924b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::shouki()
{
	canPlayerGoMenu();
	commandFinished();
}

/*
 * --INFO--
 * PAL Address: 0x80120b94
 * PAL Size: 4112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onFrameStat()
{
	CGCharaObj::onFrameStat();

	if (m_scriptHandle == nullptr) {
		return;
	}

	if (m_lastStateId == 2 || m_lastStateId == 6) {
		moveCenterTargetParticle();
		checkTargetParticle();
	}
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
 * PAL Address: 0x80120A90
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::enableAttackCol(int attackNo, int onOff, int isFriendly)
{
	(void)attackNo;
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (onOff == 0) {
		*reinterpret_cast<int*>(self + 0x20C) = 0;
		*reinterpret_cast<int*>(self + 0x23C) = 0;
		*reinterpret_cast<int*>(self + 0x26C) = 0;
		return;
	}

	resetIgnoreHit();
	unsigned int hitMask = (isFriendly != 0) ? 7u : 1u;
	*reinterpret_cast<unsigned int*>(self + 0x20C) = (hitMask & 1u) ? 1u : 0u;
	*reinterpret_cast<unsigned int*>(self + 0x23C) = (hitMask & 2u) ? 1u : 0u;
	*reinterpret_cast<unsigned int*>(self + 0x26C) = (hitMask & 4u) ? 1u : 0u;
}

/*
 * --INFO--
 * PAL Address: 0x801209d4
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::enableDamageCol(int onOff)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	unsigned int hitMask = 4;
	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		hitMask = 8;
	}

	if (onOff == 0) {
		*reinterpret_cast<unsigned int*>(self + 0x384) = 0;
		*reinterpret_cast<unsigned int*>(self + 0x3AC) = 0;
	} else {
		*reinterpret_cast<unsigned int*>(self + 0x384) = hitMask;
		*reinterpret_cast<unsigned int*>(self + 0x3AC) = hitMask;
	}
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
 * PAL Address: 0x8011ff8c
 * PAL Size: 2560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	if (m_subState == 0 && m_subFrame == 0) {
		putTargetParticle(0, 1);
	}

	unsigned short trig = getPadTrigForSlot(static_cast<unsigned char>(m_animStateMisc));
	if ((trig & 0x200) != 0) {
		changeStat(0, 0, 0);
		return;
	}

	onStatAttack(1);
}

/*
 * --INFO--
 * PAL Address: 0x8011fda8
 * PAL Size: 484b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::getBestAngleObject(float, float)
{
	CGPrgObj* best = 0;
	float bestAbsAngle = 0.0f;

	for (CGObject* obj = FindGObjFirst__13CFlatRuntime2Fv(CFlat); obj != 0;
	     obj = FindGObjNext__13CFlatRuntime2FP8CGObject(CFlat, obj)) {
		if (obj == this) {
			continue;
		}

		const unsigned int flags = obj->m_attrFlags;
		if ((flags & 0x18) == 0) {
			continue;
		}

		if ((flags & 0x08) != 0) {
			if ((obj->m_displayFlags & 1) == 0) {
				continue;
			}
			if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(obj->m_scriptHandle) + 0x1C) == 0) {
				continue;
			}
		}

		Vec diff;
		PSVECSubtract(&obj->m_worldPosition, &m_worldPosition, &diff);
		diff.y = 0.0f;
		if (PSVECSquareMag(&diff) <= 0.0f) {
			continue;
		}

		const float absAngle = fabsf(getTargetRot(reinterpret_cast<CGPrgObj*>(obj)));
		if (absAngle > bestAbsAngle) {
			bestAbsAngle = absAngle;
			best = reinterpret_cast<CGPrgObj*>(obj);
		}
	}

	if (best != 0) {
		dstTargetRot(best);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011fa88
 * PAL Size: 800b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onStatAttack(int chargeType)
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

	if ((chargeType != 0) && (m_stateFrame > 0)) {
		unsigned char* self = reinterpret_cast<unsigned char*>(this);
		if ((Pad._452_4_ == 0) && (Pad._448_4_ == -1) && ((Pad._8_2_ & 0x100) != 0)) {
			if ((self[0x6C4] & 0x80) != 0) {
				self[0x6C4] |= 0x40;
			} else {
				self[0x6C4] |= 0x80;
			}
		}
	}

	if (isLoopAnim() != 0) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011f9dc
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onStatShield()
{
	if (m_subState == 1) {
		unsigned short trig = 0;
		if ((Pad._452_4_ == 0) && (Pad._448_4_ == -1)) {
			trig = static_cast<unsigned short>(Pad._4_2_);
		}
		if ((trig & 0x100) == 0) {
			changeSubStat(3);
		}
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
 * PAL Address: 0x8011f5a4
 * PAL Size: 1028b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::putTargetParticle(int targetSide, int doInit)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (doInit != 0) {
		self[0x6B8] = (self[0x6B8] & 0xBF) | ((targetSide != 0) ? 0x40 : 0x00);
		self[0x6B8] &= 0xEF;
	}
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	self[0x6B8] &= 0xAF;
	*reinterpret_cast<int*>(self + 0x668) = 0;
	*reinterpret_cast<int*>(self + 0x660) = 0;
	*reinterpret_cast<Vec*>(self + 0x678) = m_worldPosition;
	*reinterpret_cast<Vec*>(self + 0x66C) = m_worldPosition;
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	unsigned char flags = self[0x6B8];

	if ((flags & 0x10) != 0) {
		putTargetParticle((flags & 0x80) ? 1 : 0, 0);
		self[0x6B8] &= 0xEF;
	}

	Vec delta;
	PSVECSubtract(reinterpret_cast<Vec*>(self + 0x66C), &m_worldPosition, &delta);
	if (delta.x == FLOAT_80331a78 && delta.z == FLOAT_80331a78) {
		self[0x6B8] &= 0xDF;
	} else {
		self[0x6B8] |= 0x20;
	}
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
 * PAL Address: 0x8011e32c
 * PAL Size: 1348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x8011e1b4
 * PAL Size: 376b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	canPlayerGoMenu();
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if ((self[0x6B8] & 0x20) != 0) {
		checkTargetParticle();
	}

	if (m_lastStateId == 0) {
		unsigned short held = getPadHeldForSlot(static_cast<unsigned char>(m_animStateMisc));
		if ((held & 0x100) == 0 && m_subState == 1) {
			changeSubStat(0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011e194
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onPush(CGBaseObj* other, int pushType)
{
	(void)other;
	(void)pushType;
}

/*
 * --INFO--
 * PAL Address: 0x8011e0ec
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onTalk(CGBaseObj* other, int talkType)
{
	(void)talkType;
	if (other == nullptr) {
		return;
	}

	CGObject* targetObj = reinterpret_cast<CGObject*>(other);
	if (targetObj->GetCID() == 0x23) {
		*reinterpret_cast<CGBaseObj**>(reinterpret_cast<unsigned char*>(this) + 0x6E8) = other;
		return;
	}

	float dist = PSVECDistance(&m_worldPosition, &targetObj->m_worldPosition);
	float* bestDist = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x6EC);
	if (dist < *bestDist) {
		*reinterpret_cast<CGBaseObj**>(reinterpret_cast<unsigned char*>(this) + 0x6E4) = other;
		*bestDist = dist;
	}
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
 * PAL Address: 0x8011da84
 * PAL Size: 1620b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::carry(int carryType, CGObject* object, int forceMode)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	CGObject*& carryObj = *reinterpret_cast<CGObject**>(self + 0x6F0);

	if (carryType == 0) {
		if (carryObj != nullptr) {
			if (m_lastStateId == 0x0B) {
				changeStat(0, 0, 0);
			}
			reinterpret_cast<CGItemObj*>(carryObj)->carry(this, 1, 0);
			carryObj = (CGObject*)0;
		}

		carryObj = object;
		if (carryObj != nullptr) {
			rotTarget(reinterpret_cast<CGPrgObj*>(carryObj));
			changeStat(0x0B, 0, 0);
			reinterpret_cast<CGItemObj*>(carryObj)->carry(this, 0, (forceMode != 0) ? 0 : 5);
		}
	} else if ((carryType == 1 || carryType == 2) && carryObj != nullptr) {
		reinterpret_cast<CGItemObj*>(carryObj)->carry(this, carryType, (forceMode != 0) ? 0 : 5);
		carryObj = (CGObject*)0;
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
	if (m_subState == 0 && m_subFrame == 0) {
		reqAnim(0x1D, 0, 0);
	}

	unsigned short trig = getPadTrigForSlot(static_cast<unsigned char>(m_animStateMisc));
	if ((trig & 0x200) != 0) {
		carry(2, (CGObject*)0, 1);
		changeStat(0, 0, 0);
		return;
	}

	if (isLoopAnim() != 0 || m_subFrame > 0x1E) {
		carry(1, (CGObject*)0, 1);
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011d710
 * PAL Size: 884b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::statPut()
{
	if (m_stateFrame == 0) {
		int anim = 0x0E;
		if (m_lastStateId == 0x0D) {
			anim = 0x19;
		} else if (m_lastStateId == 0x1B) {
			anim = 9;
		}
		reqAnim(anim, 0, 0);
	}

	if (isLoopAnim() != 0) {
		carry(2, (CGObject*)0, 1);
		setIdleMotion();
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
	if (m_subState == 0 && m_subFrame == 0) {
		reqAnim(0x21, 0, 0);
	}

	unsigned short trig = getPadTrigForSlot(static_cast<unsigned char>(m_animStateMisc));
	if ((trig & 0x200) != 0) {
		changeStat(0, 0, 0);
		return;
	}

	if (isLoopAnim() != 0 || m_subFrame > 0x1E) {
		carry(0, *reinterpret_cast<CGObject**>(reinterpret_cast<unsigned char*>(this) + 0x6E4), 1);
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011d1cc
 * PAL Size: 1348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::bonus(int kind, int value, CGPrgObj* source)
{
	(void)source;
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (kind == 0) {
		*reinterpret_cast<int*>(self + 0x6F8) = value;
	} else if (kind == 1) {
		addHp(value, (CGPrgObj*)0);
	}
	commandFinished();
}

/*
 * --INFO--
 * PAL Address: 0x8011d170
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	unsigned short trig = getPadTrigForSlot(static_cast<unsigned char>(m_animStateMisc));
	if (m_lastStateId == 0 && (trig & 0x200) != 0) {
		self[0x6B8] |= 0x10;
	} else if ((m_lastStateId != 0) || ((trig & 0x200) == 0)) {
		self[0x6B8] &= 0xEF;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011cee4
 * PAL Size: 652b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::useItem(int itemId)
{
	if (canPlayerUseItem() == 0) {
		return;
	}
	if (itemId >= 0) {
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6E0) = itemId;
	}
	changeStat(0x1A, 0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8011ce3c
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x8011cd10
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::putItem(int)
{
	if (canPlayerPutItem() == 0) {
		return;
	}

	int itemId = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6E0);
	void* created = CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(
	    0, 9, itemId, this, FLOAT_80331a78, nullptr);
	if (created == nullptr) {
		return;
	}

	*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(created) + 0x562) =
	    static_cast<short>(reinterpret_cast<int>(m_scriptHandle[0xED]));
	if (Game.game.m_gameWork.m_menuStageMode == 0) {
		changeStat(0x1B, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011cbdc
 * PAL Size: 308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::putGil(int amount)
{
	if (canPlayerPutItem() == 0) {
		return;
	}

	void* created = CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(
	    2, 1, amount, this, FLOAT_80331a78, nullptr);
	if (created == nullptr) {
		return;
	}

	*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(created) + 0x560) = 1;
	*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(created) + 0x562) =
	    static_cast<short>(reinterpret_cast<int>(m_scriptHandle[0xED]));
	if (Game.game.m_gameWork.m_menuStageMode == 0) {
		changeStat(0x1B, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statRebound()
{
	if ((m_subState == 0) && (m_subFrame == 0)) {
		reqAnim(0x1C, 0, 0);
		enableDamageCol(0);
	}

	if (m_subFrame == 8) {
		playSe3D(0x22, 0x32, 0x96, 0, 0);
	}

	if (isLoopAnim() != 0 || m_subFrame > 0x1E) {
		enableDamageCol(1);
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011cab8
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	if (m_subFrame == 0) {
		enableDamageCol(0);
		commandFinished();
		CancelMove(1);
	}

	moveCenterTargetParticle();
	checkTargetParticle();

	if (m_subFrame > 0x20) {
		enableDamageCol(1);
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statJump()
{
	if ((m_subState == 0) && (m_subFrame == 0)) {
		reqAnim(0x22, 0, 0);
		enableDamageCol(0);
	}

	if (m_subFrame == 1) {
		playSe3D(0x1F, 0x32, 0x96, 0, 0);
	}

	if (isLoopAnim() != 0) {
		enableDamageCol(1);
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	changeWeapon(*reinterpret_cast<int*>(self + 0x6DC),
	             *reinterpret_cast<int*>(self + 0x6E0),
	             0);

	if (m_subFrame > 1) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::changeWeapon(int weaponRef, int weaponItem, int forceIdle)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<int*>(self + 0x6DC) = weaponRef;
	*reinterpret_cast<int*>(self + 0x6E0) = weaponItem;

	if (weaponItem <= 0) {
		LoadWeapon(-1, 0);
	} else {
		LoadWeapon(weaponItem & 0xFFF, weaponItem >> 12);
	}

	if (m_scriptHandle != nullptr) {
		reinterpret_cast<CCaravanWork*>(m_scriptHandle)->SetCurrentWeaponIdx(weaponRef);
	}

	if (forceIdle != 0 || m_lastStateId != 0) {
		setIdleMotion();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011c9c8
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::CheckGameOver()
{
	Game.game.m_gameWork.m_gameOverFlag = 1;
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party == nullptr) {
			continue;
		}
		if (party->m_scriptHandle == nullptr) {
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
 * PAL Address: 0x8011c7e0
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::SetBonusCondition(int useRandom, int bonus0, int bonus1, int bonus2, int bonus3)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (useRandom == 0) {
		switch ((reinterpret_cast<unsigned int>(this) >> 2) & 3) {
		case 0:
			*reinterpret_cast<int*>(self + 0x6F8) = bonus0;
			break;
		case 1:
			*reinterpret_cast<int*>(self + 0x6F8) = bonus1;
			break;
		case 2:
			*reinterpret_cast<int*>(self + 0x6F8) = bonus2;
			break;
		default:
			*reinterpret_cast<int*>(self + 0x6F8) = bonus3;
			break;
		}
	} else {
		*reinterpret_cast<int*>(self + 0x6F8) = (bonus0 + bonus1 + bonus2 + bonus3) & 0xFF;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011c6e8
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::InitFinished()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCurrentWeaponItem(
	    *reinterpret_cast<int*>(self + 0x6DC),
	    *reinterpret_cast<int*>(self + 0x6E0));
	enableDamageCol(1);
	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBD0) = 0;
	if ((Game.game.m_gameWork.m_menuStageMode != 0) &&
	    (Game.game.m_gameWork.m_bossArtifactStageIndex < 0x0F) &&
	    (m_scriptHandle[0xED] != nullptr)) {
		*reinterpret_cast<float*>(self + 0x144) = 0.0f;
		*reinterpret_cast<float*>(self + 0x134) = 0.0f;
		*reinterpret_cast<float*>(self + 0x13C) = 1.0f;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011c678
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::IsDispRader()
{
	if (CGObject::IsDispRader()) {
		bool canDisp =
		    ((int)((unsigned int)(unsigned char)m_weaponNodeFlags << 24) < 0) &&
		    ((int)((unsigned int)(unsigned char)(m_weaponNodeFlags >> 8) << 24) < 0);
		(void)canDisp;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011c59c
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::ChangeCommandMode(int mode)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (*reinterpret_cast<short*>(self + 0x6F4) != mode) {
		*reinterpret_cast<short*>(self + 0x6F4) = static_cast<short>(mode);
		*reinterpret_cast<int*>(self + 0x6EC) = 0;
		*reinterpret_cast<CGObject**>(self + 0x6E4) = (CGObject*)0;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::checkAndSetWeapon()
{
	if (m_scriptHandle == nullptr) {
		return;
	}

	int weaponItem;
	int weaponRef;
	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCurrentWeaponItem(weaponItem, weaponRef);
	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6DC) = weaponRef;
	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6E0) = weaponItem;
	if (weaponItem <= 0) {
		LoadWeapon(-1, 0);
	} else {
		LoadWeapon(weaponItem & 0xFFF, weaponItem >> 12);
	}

	int shieldIndex = reinterpret_cast<short*>(m_scriptHandle)[0x2C];
	if (shieldIndex <= 0) {
		LoadShield(-1);
	} else {
		int shieldItem = reinterpret_cast<short*>(m_scriptHandle)[0x5B + shieldIndex];
		LoadShield((shieldItem > 0) ? (shieldItem & 0xFFF) : -1);
	}

	setIdleMotion();
}

/*
 * --INFO--
 * PAL Address: 0x8011c184
 * PAL Size: 1048b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::changeMotionMode(int mode)
{
	ChangeCommandMode(mode);
	changeStat(0, 0, 0);
	setIdleMotion();
}

/*
 * --INFO--
 * PAL Address: 0x8011c02c
 * PAL Size: 344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x8011bd30
 * PAL Size: 764b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::setAlive(int restoreDamageCol, int keepTarget)
{
	enableDamageCol(1);
	setIdleMotion();
	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
		m_bgColMask &= 0xFFFEFFF1;
	} else {
		m_bgColMask |= 0x1000E;
	}

	if (restoreDamageCol == 0) {
		enableDamageCol(0);
	}
	if (keepTarget == 0) {
		endTargetParticle();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011bce0
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x8011bc34
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onDamaged(CGPrgObj* attacker)
{
	CGPrgObj::onDamaged(attacker);
	if (m_lastStateId == 0) {
		*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x6B8) |= 0x20;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011bb88
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onAttacked(CGPrgObj* attacker)
{
	CGPrgObj::onAttacked(attacker);
	if (attacker != nullptr && m_lastStateId == 0) {
		rotTarget(attacker);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void stageWeather()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->canPlayerGoMenu();
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void magicReady()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->ChangeCommandMode(2);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void chooseMagic()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->useItem(-1);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void decMagic(int amount)
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->bonus(0, -amount, (CGPrgObj*)0);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcWeightMax()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->checkAndSetWeapon();
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011b9c8
 * PAL Size: 448b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::gpmCalcDist(Vec*, float&)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	Vec* outVec = reinterpret_cast<Vec*>(self + 0x5E0);
	float* outDist = reinterpret_cast<float*>(self + 0x5D0);
	outVec->y = 0.0f;
	float dist = PSVECMag(outVec);
	if (dist < *outDist) {
		*outDist = dist;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011b790
 * PAL Size: 568b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::gpmCol()
{
	gpmMove();
}

/*
 * --INFO--
 * PAL Address: 0x8011b268
 * PAL Size: 1320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::ghostPartyMog()
{
	gpmMove();
}

/*
 * --INFO--
 * PAL Address: 0x8011a94c
 * PAL Size: 2332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::gpmMove()
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	CGPartyObj* leader = Game.game.m_partyObjArr[0];
	if (leader == nullptr || leader == this || m_scriptHandle == nullptr) {
		return;
	}

	Vec toLeader;
	PSVECSubtract(&leader->m_worldPosition, &m_worldPosition, &toLeader);
	toLeader.y = 0.0f;
	float dist = PSVECMag(&toLeader);
	float nearDist = m_nearColRadius + leader->m_nearColRadius;

	if (dist > nearDist * 1.25f) {
		dstTargetRot(reinterpret_cast<CGPrgObj*>(leader));
		moveVector(&toLeader, m_moveBaseSpeed * 0.9f, 1);
		*reinterpret_cast<float*>(self + 0x5D0) = dist;
	} else if ((m_lastStateId == 2) && (dist < nearDist * 0.75f)) {
		changeStat(0, 0, 0);
	}

	if ((leader->m_lastStateId == 2 || leader->m_lastStateId == 6) &&
	    (leader->m_subState == 1) &&
	    (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x668) != 0) &&
	    (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x660) == 0) &&
	    (dist < nearDist * 0.6f)) {
		CancelMove(1);
		rotTarget(reinterpret_cast<CGPrgObj*>(leader));
		carry(0, reinterpret_cast<CGObject*>(leader), 0);
	}
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
 * PAL Address: 0x8011a59c
 * PAL Size: 892b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onDrawDebug(CFont* font, float x, float& y, float z)
{
	CGCharaObj::onDrawDebug(font, x, y, z);
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
