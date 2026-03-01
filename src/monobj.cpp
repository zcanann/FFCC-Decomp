#include "ffcc/monobj.h"
#include "ffcc/charaobj.h"
#include "ffcc/gobjwork.h"
#include "ffcc/fontman.h"
#include "ffcc/math.h"
#include "ffcc/astar.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/gbaque.h"
#include "ffcc/vector.h"
#include "PowerPC_EABI_Support/Runtime/ptmf.h"

#include <math.h>
#include <string.h>

extern CMath Math;
extern unsigned char DbgMenuPcs[];
extern unsigned char ARRAY_8030918c[];
extern unsigned char CFlat[];
extern "C" char DAT_803319ec[];
extern "C" char DAT_80331a4c[];

extern "C" void __ptmf_scall(void*, void*);
extern "C" void aiAddDuct__8CGMonObjFRi(CGMonObj*, int&);
extern "C" int calcPolygonGroup__6CAStarFP3Veci(void*, Vec*, int);
extern "C" CGMonObj* FindGMonObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGMonObj* FindGMonObjNext__13CFlatRuntime2FP8CGMonObj(void*, CGMonObj*);
extern "C" int getNearParty__8CGMonObjFiiffi(CGMonObj*, int, int, float, float, int);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void SetHitEnemy__8GbaQueueFii(void*, int, int);
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void SetPosZ__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);
extern "C" float DAT_8032ec24;
extern "C" void* DAT_80212a1c[];
extern "C" void* DAT_80212b30[];
extern "C" void* DAT_80212c38[];
extern "C" void* DAT_80212d4c[];
extern "C" void* DAT_80212e54[];
extern "C" void* DAT_80212f5c[];
extern "C" void* DAT_80213064[];
extern "C" void* DAT_8021316c[];
extern "C" void* DAT_80213274[];
extern "C" void* DAT_80213394[];
extern "C" void* DAT_802134a8[];
extern "C" void* DAT_802135bc[];
extern "C" void* DAT_802136dc[];
extern "C" void* DAT_802137f0[];
extern "C" void* DAT_802138f8[];
extern "C" void* DAT_80213a00[];
extern "C" void* DAT_80213b08[];
extern "C" void* DAT_80213c10[];
extern "C" void* DAT_80213d24[];
extern "C" void* DAT_80213e2c[];
extern "C" void* DAT_80213f40[];
extern "C" void* DAT_80214054[];

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
	unsigned char* scriptBase = reinterpret_cast<unsigned char*>(object->m_scriptHandle);
	unsigned char* script9 = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);

	reinterpret_cast<CGCharaObj*>(this)->onFramePreCalc();
	*reinterpret_cast<unsigned int*>(mon + 0x6F4) += 1;

	if (*reinterpret_cast<short*>(script9 + 0x10C) == 1) {
		unsigned char* aiData = script9;
		short& aiState = *reinterpret_cast<short*>(mon + 0x6E4);
		short& aiStatePrev = *reinterpret_cast<short*>(mon + 0x6E6);

		if (aiState != 0) {
			aiData = reinterpret_cast<unsigned char*>(Game.game.unkCFlatData0[1]) +
				(aiState + *reinterpret_cast<unsigned short*>(script9 + 0x100)) * 0x1D0 + 0x10;
		}

		__ptmf_scall(this, *reinterpret_cast<unsigned short*>(aiData + 0x102) & 3, mon + 0x708);

		if (aiState != aiStatePrev) {
			aiStatePrev = aiState;
			*reinterpret_cast<unsigned int*>(mon + 0x6CC) = 0;
		}
	}

	if ((*reinterpret_cast<short*>(scriptBase + 0x3E) == 0) &&
		(*reinterpret_cast<short*>(scriptBase + 0x50) == 0) &&
		(*reinterpret_cast<short*>(scriptBase + 0x44) == 0) &&
		(*reinterpret_cast<short*>(scriptBase + 0x46) == 0) &&
		(static_cast<int>(static_cast<unsigned int>(mon[0x63C]) << 24) < 0) &&
		(mon[0x6B9] == 0) &&
		(mon[0x6C1] == 0)) {
		*reinterpret_cast<int*>(mon + 0x6D8) = (*reinterpret_cast<short*>(script9 + 0x10C) == 1) ? -1 : 0;
		*reinterpret_cast<int*>(mon + 0x6DC) = *reinterpret_cast<int*>(mon + 0x6C4);
		*reinterpret_cast<int*>(mon + 0x6D0) = -1;

		if ((reinterpret_cast<unsigned int>(object->m_scriptHandle[4]) < 0x9A) &&
			(0x8D < reinterpret_cast<unsigned int>(object->m_scriptHandle[4]))) {
			int aiLocal = 0;
			aiAddDuct__8CGMonObjFRi(this, aiLocal);
		} else {
			__ptmf_scall(this, mon + 0x708);
		}

		int nextState = *reinterpret_cast<int*>(mon + 0x6D8);
		if (*reinterpret_cast<short*>(script9 + 0x10C) == 1) {
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
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	*reinterpret_cast<float*>(mon + 0x694) = 0.0f;

	int weaponMode = static_cast<int>((static_cast<unsigned int>(object->m_weaponNodeFlags) << 24) >> 31);
	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) != 0xB) {
		weaponMode = 1;
	}

	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x1000);

	unsigned short count = (weaponMode == 0) ?
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AE) :
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AC);
	int particleBase = (weaponMode == 0) ? 0x3C : 0x46;

	if ((mon[0x6BA] != 0) && (count != 0)) {
		void* pdtLoadRef = nullptr;
		if (object->m_charaModelHandle != nullptr) {
			pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
		}
		int dataNo = (pdtLoadRef != nullptr) ? reinterpret_cast<int*>(pdtLoadRef)[5] : -1;
		prgObj->putParticleBindTrace((particleBase + 9) | (dataNo << 8), *reinterpret_cast<int*>(mon + 0x594), object, 0.0f, 0);
	}

	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) == 0xB) {
		object->SetTexAnim(DAT_80331a4c);
	}

	mon[0x6BA] = 1;
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
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	*reinterpret_cast<float*>(mon + 0x694) = 1.0f;
	void* classId = object->m_scriptHandle[4];
	int weaponMode = static_cast<int>((static_cast<unsigned int>(object->m_weaponNodeFlags) << 24) >> 31);
	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) != 0xB) {
		weaponMode = 1;
	}

	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x1000);

	unsigned short count = (weaponMode == 0) ?
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AE) :
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1AC);
	int particleBase = (weaponMode == 0) ? 0x3C : 0x46;

	for (int i = 0; i < static_cast<int>(count); i++) {
		void* pdtLoadRef = nullptr;
		if (object->m_charaModelHandle != nullptr) {
			pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
		}
		int dataNo = (pdtLoadRef != nullptr) ? reinterpret_cast<int*>(pdtLoadRef)[5] : -1;
		prgObj->putParticleBindTrace((particleBase + i) | (dataNo << 8), *reinterpret_cast<int*>(mon + 0x594), object, 0.0f, 0);
	}

	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) == 0xB) {
		object->SetTexAnim(DAT_803319ec);
	}

	if (static_cast<int>((static_cast<unsigned int>(object->m_weaponNodeFlags) << 24)) < 0) {
		if (classId == reinterpret_cast<void*>(0x83)) {
			prgObj->playSe3D(0x987A, 0x32, 0x96, 0, (Vec*)0);
		} else if (classId == reinterpret_cast<void*>(0x7F)) {
			prgObj->playSe3D(0x11585, 0x32, 0x96, 0, (Vec*)0);
		}
	}

	mon[0x6BA] = 0;
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

	if (-1 < targetPartyIndex) {
		float targetRot = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(Game.game.m_partyObjArr[targetPartyIndex]));
		if (rotLimit <= 3.1415927f) {
			float delta = Math.DstRot(targetRot, static_cast<float>(object->m_bgFlags));
			if (delta < -rotLimit) {
				delta = -rotLimit;
			} else if (rotLimit < delta) {
				delta = rotLimit;
			}
			object->m_rotTargetY = static_cast<float>(object->m_bgFlags) + delta;
		} else {
			object->m_rotTargetY = targetRot;
		}
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
	CGPrgObj* prgObj = reinterpret_cast<CGPrgObj*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	unsigned char* attackBase = reinterpret_cast<unsigned char*>(Game.game.unkCFlatData0[2]);
	unsigned char* attackData = attackBase + *reinterpret_cast<int*>(mon + 0x560) * 0x48;
	unsigned short attackFlags = *reinterpret_cast<unsigned short*>(attackData + 0x32);
	int targetPartyIndex = *reinterpret_cast<int*>(mon + 0x6C4);

	if (state == 0) {
		if ((prgObj->m_stateFrame == 0) && (-1 < targetPartyIndex)) {
			CGPartyObj* target = Game.game.m_partyObjArr[targetPartyIndex];
			*reinterpret_cast<Vec*>(mon + 0x66C) = reinterpret_cast<CGObject*>(target)->m_worldPosition;

			if ((attackFlags & 2) == 0) {
				float rotLimit = 0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x19C));
				if (-1 < targetPartyIndex) {
					float targetRot = prgObj->getTargetRot(reinterpret_cast<CGPrgObj*>(target));
					if (rotLimit <= 3.1415927f) {
						float delta = Math.DstRot(targetRot, static_cast<float>(object->m_bgFlags));
						if (delta < -rotLimit) {
							delta = -rotLimit;
						} else if (rotLimit < delta) {
							delta = rotLimit;
						}
						object->m_rotTargetY = static_cast<float>(object->m_bgFlags) + delta;
					} else {
						object->m_rotTargetY = targetRot;
					}
				}
			}

			target = Game.game.m_partyObjArr[targetPartyIndex];
			reinterpret_cast<CGPrgObj*>(target)->bonus(0x17, *reinterpret_cast<int*>(mon + 0x560), reinterpret_cast<CGPrgObj*>(target));
		}
		return;
	}

	if (*reinterpret_cast<short*>(attackData + 0xE) == 3) {
		if (prgObj->m_subState == 1) {
			if (prgObj->m_subFrame == 0) {
				prgObj->reqAnim(*reinterpret_cast<int*>(mon + 0x554), 1, 0);
			}
			if (prgObj->m_subFrame == *reinterpret_cast<unsigned short*>(attackData + 0x2E)) {
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
				setAttackAfter(*reinterpret_cast<int*>(mon + 0x560));
			}
		}
		return;
	}

	if ((prgObj->m_stateArg == 0) && (prgObj->isLoopAnim() != 0)) {
		setAttackAfter(*reinterpret_cast<int*>(mon + 0x560));
	}
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
 * PAL Address: 0x80119528
 * PAL Size: 324b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onChangeStat(int state)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	__ptmf_scall(this, mon + 0x708);

	if (state <= -6 && state >= -14) {
		setActionParam(state);
	}

	reinterpret_cast<CGCharaObj*>(this)->onChangeStat(state);
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
	*reinterpret_cast<int*>(mon + 0x554) = static_cast<int>(motion) + 1;
	*reinterpret_cast<int*>(mon + 0x558) = *reinterpret_cast<int*>(mon + 0x554) + 1;
	*reinterpret_cast<int*>(mon + 0x55C) = *reinterpret_cast<int*>(mon + 0x558) + 1;

	int actionOffset = static_cast<int>(action) * 0x48;
	unsigned short actionType = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + actionOffset + 0xE);
	if (actionType <= 3) {
		if (actionType < 2 || actionType == 3) {
			*reinterpret_cast<unsigned int*>(mon + 0x630) = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + actionOffset + 0x20);
			*reinterpret_cast<unsigned int*>(mon + 0x634) = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + actionOffset + 0x22);
			*reinterpret_cast<unsigned int*>(mon + 0x638) = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + actionOffset + 0x22);
		} else if (actionType == 2) {
			reinterpret_cast<CGCharaObj*>(this)->calcCastTime(static_cast<int>(action));
		}
	}
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

	if (state == 0 || state == 3 || state == 0x1C) {
		if (reinterpret_cast<CGPrgObj*>(this)->m_lastStateId == state) {
			state = -1;
		}
	} else if ((state < -4) && (state > -0xF)) {
		unsigned short action = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle) + (state + 0xE) * 2 + 0xD0);
		unsigned short actionType = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + action * 0x48 + 0xE);
		if (actionType == 3) {
			return 0x12;
		}
		if (actionType < 2) {
			return 1;
		}
		if (actionType == 2) {
			return 2;
		}
		if (actionType == 4) {
			return 8;
		}
	} else {
		state = reinterpret_cast<CGCharaObj*>(this)->getReplaceStat(state);
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
		unsigned int subFrame = *reinterpret_cast<unsigned int*>(mon + 0x530);
		int action = *reinterpret_cast<int*>(mon + 0x560);
		unsigned int waitFrame = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + action * 0x48 + 0x2E);

		if (subFrame == waitFrame) {
			reinterpret_cast<CGPrgObj*>(this)->changeSubStat(3);
		}
	}
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

	charaObj->onDrawDebug(font, posX, posY, posZ);

	if ((((int)((unsigned int)object->m_weaponNodeFlags << 0x18) < 0) &&
			(*reinterpret_cast<unsigned int*>(CFlat + 0x12AC) == 0)) &&
		((*reinterpret_cast<unsigned int*>(DbgMenuPcs + 0x6484) & 0x80) != 0)) {
		char text[0x100];
		unsigned short aiState = *reinterpret_cast<unsigned short*>(mon + 0x6E4);
		int targetIndex = *reinterpret_cast<int*>(mon + 0x6C4);
		int targetChar = '-';
		int aiChar = '-';

		if (targetIndex >= 0) {
			targetChar = targetIndex + '0';
		}
		if ((aiState & 0x7FFF) != 0) {
			aiChar = (aiState & 0x7FFF) + 0x40;
		}

		sprintf(text, "%d:%c %d:%c", (int)object->m_scriptHandle[2], aiChar, *reinterpret_cast<int*>(mon + 0x6D0), targetChar);
		SetPosX__5CFontFf(posX - static_cast<float>(GetWidth__5CFontFPc(font, text)) * 0.5f, font);
		SetPosY__5CFontFf(posY, font);
		SetPosZ__5CFontFf(posZ, font);
		Draw__5CFontFPc(font, text);
		posY -= static_cast<float>(font->m_glyphWidth) * font->scaleY;

		int targetDist = 0;
		if (targetIndex >= 0) {
			targetDist = static_cast<int>(*reinterpret_cast<float*>(mon + targetIndex * 4 + 0x5D0));
		}

		int chaseRange = static_cast<int>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xCC));
		int spawnDist = static_cast<int>(PSVECDistance(reinterpret_cast<Vec*>(mon + 0x6F8), &object->m_worldPosition));
		sprintf(text, "%d %d %d", targetDist, spawnDist, chaseRange);
		SetPosX__5CFontFf(posX - static_cast<float>(GetWidth__5CFontFPc(font, text)) * 0.5f, font);
		SetPosY__5CFontFf(posY, font);
		SetPosZ__5CFontFf(posZ, font);
		Draw__5CFontFPc(font, text);
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
	mon[0x6C0] = 1;

	if (__ptmf_test(reinterpret_cast<__ptmf*>(mon + 0x780)) != 0) {
		__ptmf_scall(this, mon + 0x708);
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
	void** prgScript = *reinterpret_cast<void***>(reinterpret_cast<unsigned char*>(prgObj) + 0x58);
	typedef unsigned int (*GetFlagsFn)(CGPrgObj*);
	GetFlagsFn getFlags = *reinterpret_cast<GetFlagsFn*>(
		reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(prgObj) + 0x48)) + 0xC
	);

	mon[0x6BF] = 1;

	unsigned int prgFlags = getFlags(prgObj);
	if ((prgFlags & 0x6D) == 0x6D) {
		unsigned char* aiData = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
		if (*reinterpret_cast<short*>(mon + 0x6E4) != 0) {
			aiData = reinterpret_cast<unsigned char*>(Game.game.unkCFlatData0[1]) +
				(*reinterpret_cast<short*>(mon + 0x6E4) +
					*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x100)) * 0x1D0 + 0x10;
		}

		int attackerIndex = reinterpret_cast<int>(prgScript[0xED]);
		if ((*reinterpret_cast<short*>(aiData + 0x106) == 1) || (*reinterpret_cast<int*>(mon + 0x6C4) < 0)) {
			if ((Game.game.m_gameWork.m_menuStageMode != '\0') && (Game.game.m_gameWork.m_bossArtifactStageIndex < 0xF)) {
				prgFlags = getFlags(prgObj);
				if ((prgFlags & 0x6D) == 0x6D) {
					if (prgScript[0xED] != nullptr) {
						goto skip_target_update;
					}
				}
			}
			*reinterpret_cast<int*>(mon + 0x6C4) = attackerIndex;
		}

skip_target_update:
		int teamNo = reinterpret_cast<int>(object->m_scriptHandle[2]);
		*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(prgObj) + 0x5BC) = static_cast<float>(teamNo);
		SetHitEnemy__8GbaQueueFii(&GbaQue, attackerIndex, teamNo);

		unsigned short groupTag = *reinterpret_cast<unsigned short*>(mon + 0x6D4);
		if ((groupTag & 0x7FFF) != 0) {
			for (CGMonObj* other = FindGMonObjFirst__13CFlatRuntime2Fv(CFlat); other != nullptr;
				other = FindGMonObjNext__13CFlatRuntime2FP8CGMonObj(CFlat, other)) {
				if (other == this) {
					continue;
				}

				unsigned char* otherMon = reinterpret_cast<unsigned char*>(other);
				if ((*reinterpret_cast<unsigned short*>(otherMon + 0x6D4) & 0x7FFF) == 0) {
					continue;
				}
				if ((groupTag & 0x7FFF) != (*reinterpret_cast<unsigned short*>(otherMon + 0x6D4) & 0x7FFF)) {
					continue;
				}

				void** otherScript = reinterpret_cast<CGObject*>(other)->m_scriptHandle;
				if (*reinterpret_cast<short*>(otherScript + 7) == 0) {
					continue;
				}
				if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(otherScript) + 0x3E) != 0) {
					continue;
				}
				if (*reinterpret_cast<short*>(otherScript + 0x14) != 0) {
					continue;
				}
				if (*reinterpret_cast<short*>(otherScript + 0x11) != 0) {
					continue;
				}

				*reinterpret_cast<int*>(otherMon + 0x6C4) = attackerIndex;
				otherMon[0x6BD] = 1;

				if (*reinterpret_cast<int*>(otherMon + 0x6D8) == 4) {
					if ((static_cast<int>(static_cast<unsigned int>(otherMon[0x63C]) << 24) >= 0) &&
						(reinterpret_cast<CGObject*>(other)->m_scriptHandle[4] == reinterpret_cast<void*>(0x55))) {
						reinterpret_cast<CGPrgObj*>(other)->changeStat(0x18, 0, 0);
						*reinterpret_cast<int*>(otherMon + 0x6D8) = 2;
						*reinterpret_cast<int*>(otherMon + 0x6DC) = 0;
						otherMon[0x6BB] = 1;
					}
				} else {
					*reinterpret_cast<int*>(otherMon + 0x6D8) = 2;
					*reinterpret_cast<int*>(otherMon + 0x6DC) = 0;
					otherMon[0x6BB] = 1;
				}
			}
		}
	}

	if (*reinterpret_cast<int*>(mon + 0x520) == 0x11) {
		prgObj->changeStat(0, 0, 0);
	}

	if ((static_cast<int>(static_cast<unsigned int>(mon[0x63C]) << 24) >= 0) &&
		(object->m_scriptHandle[4] == reinterpret_cast<void*>(0x55))) {
		prgObj->changeStat(0x18, 0, 0);
	}

	*reinterpret_cast<int*>(mon + 0x6D8) = 2;
	*reinterpret_cast<int*>(mon + 0x6DC) = 0;
	mon[0x6BB] = 1;

	if (__ptmf_test(reinterpret_cast<__ptmf*>(mon + 0x774)) != 0) {
		__ptmf_scall(this, mon + 0x708);
	}
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
	int partyIndex = getNearParty__8CGMonObjFiiffi(this, 0, 7, 0.0f, DAT_8032ec24, -1);
	if (partyIndex >= 0) {
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6C4) = partyIndex;
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
	int partyIndex = getNearParty__8CGMonObjFiiffi(this, -1, 0x47, 0.0f, 0.0f, classId);
	if (partyIndex >= 0) {
		*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6C4) = partyIndex;
	}
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
 * PAL Address: 0x801162B4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void fn_801162B4(CGMonObj* monObj)
{
	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(monObj) + 0x6C8) = 0;
	memset(reinterpret_cast<unsigned char*>(monObj) + 0x70C, 0, 0x34);
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
 * PAL Address: 0x801145D0
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CGMonObj::aiSeq(int seqId, int priority, int currentState, int nextState, int chance, int fallbackState)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	int& aiState = *reinterpret_cast<int*>(mon + 0x6C8);
	int& aiPriority = *reinterpret_cast<int*>(mon + 0x6CC);

	if (aiPriority < priority && currentState == aiState) {
		if (Math.Rand(100) <= static_cast<unsigned int>(chance)) {
			if (aiPriority < priority) {
				aiPriority = priority;
				*reinterpret_cast<int*>(mon + 0x6D0) = seqId;
			}
			aiState = nextState;
			return 1;
		}
		if (fallbackState >= 0) {
			aiState = fallbackState;
		}
	}

	return 0;
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
	void* classId = object->m_scriptHandle[4];

	*reinterpret_cast<float*>(mon + 0x6F8) = object->unk_0x168;
	*reinterpret_cast<float*>(mon + 0x6FC) = object->unk_0x16C;
	*reinterpret_cast<float*>(mon + 0x700) = object->unk_0x170;

	switch (reinterpret_cast<unsigned int>(classId)) {
	case 0x5B:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80212b30;
		break;
	case 0x5F:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213064;
		break;
	case 0x63:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80212c38;
		break;
	case 0x67:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80212f5c;
		break;
	case 0x6B:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80212e54;
		break;
	case 0x6F:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213394;
		break;
	case 0x70:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_802134a8;
		break;
	case 0x71:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80212d4c;
		break;
	case 0x73:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_8021316c;
		break;
	case 0x74:
	case 0x75:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80214054;
		break;
	case 0x77:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213274;
		break;
	case 0x79:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213b08;
		break;
	case 0x7B:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213a00;
		break;
	case 0x7F:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213c10;
		break;
	case 0x83:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_802138f8;
		break;
	case 0x85:
	case 0x86:
	case 0x87:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_802135bc;
		break;
	case 0x88:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_802136dc;
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
		*reinterpret_cast<void**>(mon + 0x708) = DAT_802137f0;
		break;
	case 0x9A:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213f40;
		break;
	case 0x9B:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213e2c;
		break;
	case 0x9E:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80213d24;
		break;
	default:
		*reinterpret_cast<void**>(mon + 0x708) = DAT_80212a1c;
		break;
	}

	__ptmf_scall(this, mon + 0x708);
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
	unsigned char* scriptBase = reinterpret_cast<unsigned char*>(object->m_scriptHandle);

	// Script value is authored in centi-units.
	object->m_hitNormal.x = 0.01f * static_cast<float>(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1B0));

	short animPoint = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1A0);
	if (animPoint != -1) {
		object->AddAnimPoint(1, animPoint, 0xB);
	}

	animPoint = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0x1A2);
	if (animPoint != -1) {
		object->AddAnimPoint(1, animPoint, 0xA);
	}

	*reinterpret_cast<int*>(mon + 0x6E8) = -1;
	for (int attackBase = 0, slotBase = 0; slotBase < 8; attackBase += 4, slotBase += 8) {
		unsigned int attackId = *reinterpret_cast<unsigned short*>(scriptBase + slotBase + 0xD0);
		if ((attackId != 0xFFFF) &&
			(*reinterpret_cast<short*>(Game.game.unkCFlatData0[2] + attackId * 0x48 + 0xE) == 4)) {
			*reinterpret_cast<int*>(mon + 0x6E8) = attackBase;
			break;
		}

		attackId = *reinterpret_cast<unsigned short*>(scriptBase + slotBase + 0xD2);
		if ((attackId != 0xFFFF) &&
			(*reinterpret_cast<short*>(Game.game.unkCFlatData0[2] + attackId * 0x48 + 0xE) == 4)) {
			*reinterpret_cast<int*>(mon + 0x6E8) = attackBase + 1;
			break;
		}

		attackId = *reinterpret_cast<unsigned short*>(scriptBase + slotBase + 0xD4);
		if ((attackId != 0xFFFF) &&
			(*reinterpret_cast<short*>(Game.game.unkCFlatData0[2] + attackId * 0x48 + 0xE) == 4)) {
			*reinterpret_cast<int*>(mon + 0x6E8) = attackBase + 2;
			break;
		}

		attackId = *reinterpret_cast<unsigned short*>(scriptBase + slotBase + 0xD6);
		if ((attackId != 0xFFFF) &&
			(*reinterpret_cast<short*>(Game.game.unkCFlatData0[2] + attackId * 0x48 + 0xE) == 4)) {
			*reinterpret_cast<int*>(mon + 0x6E8) = attackBase + 3;
			break;
		}
	}

	setRepop(1);
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

	bool allowRepop = (mode == 0);
	if (!allowRepop) {
		int option = static_cast<short>(Game.game.m_gameWork.m_optionValue);
		if (8 < option) {
			allowRepop = true;
		} else {
			int shift = reinterpret_cast<int>(scriptHandle[2]);
			unsigned long long bit = (shift < 64) ? (1ULL << shift) : 0ULL;
			unsigned int cflatHi = *reinterpret_cast<unsigned int*>(CFlat + 0x12F4 + option * 8);
			unsigned int cflatLo = *reinterpret_cast<unsigned int*>(CFlat + 0x12F0 + option * 8);
			if ((cflatHi & static_cast<unsigned int>(bit)) == 0 &&
				(cflatLo & static_cast<unsigned int>(bit >> 32)) == 0) {
				allowRepop = true;
			}
		}
	}

	if (!allowRepop) {
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle) + 0x1C) = 0;
		object->m_bgColMask = 0;
		object->m_displayFlags = 0;
		object->m_weaponNodeFlags &= 0xFFEF;
		prgObj->changeStat(0x28, 0, 0);
		return;
	}

	if (mode == 0) {
		*reinterpret_cast<float*>(mon + 0x6F8) = object->unk_0x168;
		*reinterpret_cast<float*>(mon + 0x6FC) = object->unk_0x16C;
		*reinterpret_cast<float*>(mon + 0x700) = object->unk_0x170;
		object->m_worldPosition.x = *reinterpret_cast<float*>(mon + 0x6F8);
		object->m_worldPosition.y = *reinterpret_cast<float*>(mon + 0x6FC);
		object->m_worldPosition.z = *reinterpret_cast<float*>(mon + 0x700);
		object->m_rotBaseY = static_cast<float>(object->m_bgFlags);
		object->m_rotTargetY = object->m_rotBaseY;

		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle) + 0x1C) =
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(scriptHandle) + 0x1A);
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
	}

	typedef void (*Virtual90)(CGMonObj*, int, int, int);
	typedef void (*Virtual94)(CGMonObj*, int);
	void** vtable = *reinterpret_cast<void***>(this);
	reinterpret_cast<Virtual90>(vtable[0x90 / 4])(this, 0, 0, 0);
	reinterpret_cast<Virtual94>(vtable[0x94 / 4])(this, 1);
	prgObj->changeStat(0, 0, 0);

	unsigned char* monsterScript = reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]);
	unsigned short scriptFlags = *reinterpret_cast<unsigned short*>(monsterScript + 0xFE);

	if ((scriptFlags & 0x80) == 0 && (scriptFlags & 0x20) == 0) {
		if ((scriptFlags & 0x40) != 0 || classId == reinterpret_cast<void*>(0x39)) {
			*reinterpret_cast<unsigned int*>(mon + 0x6D8) = 4;
			*reinterpret_cast<unsigned int*>(mon + 0x6DC) = 0;
			mon[0x6BB] = 1;
			reinterpret_cast<Virtual94>(vtable[0x94 / 4])(this, 0);
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
		*reinterpret_cast<unsigned int*>(mon + 0x6D8) = 4;
		*reinterpret_cast<unsigned int*>(mon + 0x6DC) = 0;
		mon[0x6BB] = 1;
		reinterpret_cast<Virtual94>(vtable[0x94 / 4])(this, 0);
	}

	if (classId == reinterpret_cast<void*>(0x55)) {
		*reinterpret_cast<unsigned int*>(mon + 0x6D8) = 4;
		*reinterpret_cast<unsigned int*>(mon + 0x6DC) = 0;
		mon[0x6BB] = 1;
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

		void* pdtLoadRef = nullptr;
		if (object->m_charaModelHandle != nullptr) {
			pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
		}
		int dataNo = (pdtLoadRef != nullptr) ? reinterpret_cast<int*>(pdtLoadRef)[5] : -1;
		prgObj->putParticleBindTrace((i + particleBase + 0x50) | (dataNo << 8), *reinterpret_cast<int*>(mon + 0x5A4), object, 0.0f, 0);
	}

	reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x20000);

	unsigned short countB = *reinterpret_cast<unsigned short*>(monsterScript + 0x1AA);
	for (int i = 0; i < static_cast<int>(countB); i++) {
		void* pdtLoadRef = nullptr;
		if (object->m_charaModelHandle != nullptr) {
			pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
		}
		int dataNo = (pdtLoadRef != nullptr) ? reinterpret_cast<int*>(pdtLoadRef)[5] : -1;
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
		void* pdtLoadRef = nullptr;
		if (object->m_charaModelHandle != nullptr) {
			pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
		}
		int dataNo = (pdtLoadRef != nullptr) ? reinterpret_cast<int*>(pdtLoadRef)[5] : -1;
		prgObj->putParticleBindTrace((particleBase + i) | (dataNo << 8), *reinterpret_cast<int*>(mon + 0x594), object, 0.0f, 0);
	}

	if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(scriptHandle[9]) + 0xFC) == 0xB) {
		object->SetTexAnim(DAT_803319ec);
	}

	if (static_cast<int>((static_cast<unsigned int>(object->m_weaponNodeFlags) << 24)) < 0) {
		if (classId == reinterpret_cast<void*>(0x83)) {
			prgObj->playSe3D(0x987A, 0x32, 0x96, 0, (Vec*)0);
		} else if (classId == reinterpret_cast<void*>(0x7F)) {
			prgObj->playSe3D(0x11585, 0x32, 0x96, 0, (Vec*)0);
		}
	}

	mon[0x6BA] = 0;
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
 * PAL Address: 0x8011367C
 * PAL Size: 740b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::moveAStar(int startGroup, int forbiddenGroup, Vec& targetPos)
{
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);
	CGObject* object = reinterpret_cast<CGObject*>(this);

	unsigned int moveFlags = *reinterpret_cast<unsigned int*>(mon + 0x70C);
	short& routeFrom = *reinterpret_cast<short*>(mon + 0x73C);
	short& routePrev = *reinterpret_cast<short*>(mon + 0x73E);

	if (((moveFlags & 0x30000) == 0) || (*reinterpret_cast<unsigned int*>(ARRAY_8030918c) == 0)) {
		return;
	}

	if (routeFrom == 0) {
		routeFrom = static_cast<short>(startGroup);
	}

	if (((moveFlags & 0x10000) == 0) || ((moveFlags & 0x40) != 0)) {
		if ((routeFrom == 0) || (forbiddenGroup == 0)) {
			return;
		}

		CAStar::CAPos* escapePos = AStar.getEscapePos(object->m_worldPosition, targetPos, routeFrom, routePrev);
		if (escapePos == nullptr) {
			return;
		}

		unsigned int nextGroup = escapePos->m_groupA;
		if (static_cast<short>(nextGroup) == routeFrom) {
			nextGroup = escapePos->m_groupB;
		}

		unsigned char* routeStep = AStar.m_routeTable[routeFrom - 1][nextGroup + 0x36];
		float portalDist = PSVECDistance(&object->m_worldPosition, &escapePos->m_position);
		if ((portalDist < object->m_capsuleHalfHeight) || (startGroup == routeStep[0])) {
			routePrev = routeFrom;
			routeFrom = routeStep[0];
			escapePos = reinterpret_cast<CAStar::CAPos*>(ARRAY_8030918c) +
				AStar.m_routeTable[routeStep[0] - 1][forbiddenGroup + 0x36][1];
		}

		float targetDist = PSVECDistance(&targetPos, &object->m_worldPosition);
		Vec dirRaw;
		PSVECSubtract(&object->m_worldPosition, &escapePos->m_position, &dirRaw);
		CVector dir(dirRaw);
		dir.Normalize();
		targetPos.x = object->m_worldPosition.x + dir.x * targetDist;
		targetPos.y = object->m_worldPosition.y + dir.y * targetDist;
		targetPos.z = object->m_worldPosition.z + dir.z * targetDist;
		return;
	}

	short currentRoute = routeFrom;
	if ((currentRoute == 0) || (forbiddenGroup == 0) || (currentRoute == forbiddenGroup)) {
		return;
	}

	unsigned char* routeStep = AStar.m_routeTable[currentRoute - 1][forbiddenGroup + 0x36];
	CAStar::CAPos* portalPos = reinterpret_cast<CAStar::CAPos*>(ARRAY_8030918c) + routeStep[1];
	float portalDist = PSVECDistance(&object->m_worldPosition, &portalPos->m_position);
	if ((portalDist < object->m_capsuleHalfHeight) || (startGroup == routeStep[0])) {
		routeFrom = routeStep[0];
		portalPos = reinterpret_cast<CAStar::CAPos*>(ARRAY_8030918c) +
			AStar.m_routeTable[routeStep[0] - 1][forbiddenGroup + 0x36][1];
	}

	targetPos.x = portalPos->m_position.x;
	targetPos.y = portalPos->m_position.y;
	targetPos.z = portalPos->m_position.z;
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
 * PAL Address: 0x80112D5C
 * PAL Size: 376b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGMonObj::onChangePrg(int value)
{
	CGObject* object = reinterpret_cast<CGObject*>(this);
	unsigned char* mon = reinterpret_cast<unsigned char*>(this);

	if ((((char)object->m_weaponNodeFlags) >> 7) != value &&
		(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + 0xFC) == 0xB)) {
		reinterpret_cast<CGCharaObj*>(this)->endPSlotBit(0x1000);

		unsigned short count = *reinterpret_cast<unsigned short*>(
			reinterpret_cast<unsigned char*>(object->m_scriptHandle[9]) + (value != 0 ? 0x1AC : 0x1AE)
		);
		int particleBase = (value != 0) ? 0x46 : 0x3C;

		void* pdtLoadRef = nullptr;
		if (object->m_charaModelHandle != nullptr) {
			pdtLoadRef = object->m_charaModelHandle->m_pdtLoadRef;
		}
		int dataNo = (pdtLoadRef != nullptr) ? reinterpret_cast<int*>(pdtLoadRef)[5] : -1;
		int modelSlot = *reinterpret_cast<int*>(mon + 0x594);

		if (mon[0x6BA] != 0) {
			if (count != 0) {
				reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace(
					(particleBase + 9) | (dataNo << 8),
					modelSlot,
					object,
					0.0f,
					0
				);
			}
		} else {
			for (int i = 0; i < (int)count; i++) {
				reinterpret_cast<CGPrgObj*>(this)->putParticleBindTrace(
					(particleBase + i) | (dataNo << 8),
					modelSlot,
					object,
					0.0f,
					0
				);
			}
		}
	}

	reinterpret_cast<CGCharaObj*>(this)->onChangePrg(value);
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
