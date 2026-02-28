#include "ffcc/charaobj.h"
#include "ffcc/p_game.h"

extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	void*, int, int, int, int, void*, void*);
extern "C" void DeleteParticleSlot__13CFlatRuntime2Fii(void*, int);

extern unsigned char CFlat[];

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
 * Address:	TODO
 * Size:	TODO
 */
void SAFE_CAST_WORK(CGObjWork*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onCreate()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onChangeStat(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onCancelStat(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onFramePostCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onFramePreCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onAlphaUpdate()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::endPSlotBit(int)
{
	// TODO
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
	int* slots = (int*)((char*)this + 0x564);
	for (int i = 0; i < 0x16; i++) {
		if (((unsigned int)slotMask & (1U << i)) != 0) {
			DeleteParticleSlot__13CFlatRuntime2Fii(CFlat, slots[i]);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onFrameStat()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onAnimPoint(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::resetIgnoreHit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::decIgnoreHit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::damageDelete()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onHit(int, CGObject*, int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onHitParticle(int, int, int, int, Vec*, PPPIFPARAM*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGCharaObj::getReplaceStat(int state)
{
	// TODO
	return state;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::putHitParticleFromItem(CGPrgObj*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::setSta(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::effective(int, int, CGPrgObj*, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::calcSta(int, int, CGObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::addHp(int, CGPrgObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::calcRegist(int, int, int&, int&, int&, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onDamage(CGPrgObj*, int, int, int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::getItemPdt(int, int, int&, int&, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::putParticleFromItem(int, int, int, Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statShield()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void la(CGObject*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statAttack()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statDie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statMagic()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statKizetsu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onStatMagic()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statDamage()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::statButtobi()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onChangePrg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::calcCastTime(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onDrawDebug(CFont*, float, float&, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::addSe(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::seDamageDelete()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::StaticFrame()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::combi2()
{
	// TODO
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
	CGame* linkCursor = &Game.game;
	int linkCount = *reinterpret_cast<int*>(&Game.game.m_gameWork.m_linkTable[3][0][0]);

	while (entry < linkCount) {
		int linkHead = *reinterpret_cast<int*>(&linkCursor->m_gameWork.m_linkTable[3][0][0]);
		CGPrgObj* obj = *reinterpret_cast<CGPrgObj**>(linkHead + 4);
		bool skip = (obj == 0);

		if (!skip) {
			if (Game.game.m_gameWork.m_menuStageMode != 0 && Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
				(obj->GetCID() & 0x6D) == 0x6D &&
				*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(obj->m_scriptHandle) + 0x3B4) != 0) {
				skip = true;
			}

			if (obj->m_lastStateId == 6 || obj->m_lastStateId == 2) {
				skip = true;
			}
		}

		if (!skip) {
			break;
		}

		linkCursor = reinterpret_cast<CGame*>(reinterpret_cast<unsigned char*>(linkCursor) + 4);
		entry++;
	}

	if (entry == linkCount) {
		int stackArgs[2];
		stackArgs[0] = reinterpret_cast<int>(target);
		stackArgs[1] = scriptArg;
		SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
			CFlat, reinterpret_cast<int>(this), 2, 0x17, 2, stackArgs, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::scCheckItem(CCombi2Set*, CGCharaObj*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::scCheckTime(CCombi2Set*, CGCharaObj*, CGCharaObj*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::searchCombi(int, CGPartyObj **, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::enableAttackCol(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onStatShield()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onStatAttack(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::onStatDie()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CGCharaObj::GetCID()
{
	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGCharaObj::enableDamageCol(int)
{
	// TODO
}
