#include "ffcc/partyobj.h"
#include "ffcc/gobjwork.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"

#include <math.h>

extern "C" int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
extern "C" void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
extern "C" void GetHitFaceNormal__7CMapObjFP3Vec(void*, Vec*);

extern float FLOAT_80331a78;
extern float FLOAT_80331a9c;
extern float FLOAT_80331aa0;
extern float FLOAT_80331ac4;
extern float FLOAT_80331ac8;
extern float FLOAT_80331acc;
extern float FLOAT_80331ad0;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CATEGOLY2TYPE(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onCreate()
{
	// TODO
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onCancelStat(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::menu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onFrameAlways()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::CheckMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onFramePreCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onFramePostCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::command()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::callCommandScript(int, CGObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::shouki()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onFrameStat()
{
	// TODO
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
void CGPartyObj::enableAttackCol(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::enableDamageCol(int)
{
	// TODO
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statAttackSel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::getBestAngleObject(float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onStatAttack(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onStatShield()
{
	// TODO
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::endTargetParticle()
{
	// TODO
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
	
	// TODO: Implement particle flag checking
	// Complex bit manipulation and field access patterns from Ghidra decomp
	
	// TODO: Implement input handling for target particle movement
	// Includes analog stick and digital pad input processing
	
	// TODO: Implement menu stage vs normal game mode logic  
	// Different behavior when in boss artifact stages
	
	// TODO: Implement collision detection and position constraints
	// Complex map geometry collision checking
	
	// TODO: Implement camera rotation and angle calculations
	// Transform movement vectors based on camera orientation
	
	// For now, basic placeholder to establish compilation baseline
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onStatDie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statAlive()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onPush(CGBaseObj*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onTalk(CGBaseObj*, int)
{
	// TODO
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statCarry()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statPut()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statPickup()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::bonus(int, int, CGPrgObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::canPlayerUseItem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::canPlayerGoMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::useItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::canPlayerPutItem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::putItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::putGil(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statRebound()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statKorobi()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statHide()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statJump()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statWeaponChange()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::changeWeapon(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::CheckGameOver()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::SetBonusCondition(int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::InitFinished()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::IsDispRader()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::ChangeCommandMode(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::checkAndSetWeapon()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::changeMotionMode(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::setIdleMotion()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::setAlive(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::PutMemoryCapsule(int, int, int, int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onDamaged(CGPrgObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::onAttacked(CGPrgObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void stageWeather()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void magicReady()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void chooseMagic()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void decMagic(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcWeightMax()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::gpmCalcDist(Vec*, float&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::gpmCol()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::ghostPartyMog()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::gpmMove()
{
	// TODO
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
	// TODO
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
