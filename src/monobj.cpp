#include "ffcc/monobj.h"
#include "ffcc/charaobj.h"

#include <string.h>

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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::setAttackAfter(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::enableDamageCol(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onAttacked(CGPrgObj*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGMonObj::onFrameAlways()
{
	// TODO
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
