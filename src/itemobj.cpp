#include "ffcc/ptrarray.h"
#include "ffcc/itemobj.h"
#include "ffcc/color.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/math.h"
#include "ffcc/monobj.h"
#include "ffcc/partMng.h"
#include "ffcc/partyobj.h"
#include "ffcc/prgobj.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/game.h"
#include "ffcc/vector.h"

#include <math.h>
#include <string.h>
#include "ffcc/fontman.h"

extern const float kItemObjHeightOffset;
extern const float kItemObjUnitScale;
extern const float kItemObjZero = 0.0f;
extern const float kItemObjGroundProbeDown = -2000.0f;
extern const float kItemObjBoundsInitMin = 10000000000.0f;
extern const float kItemObjBoundsInitMax = -10000000000.0f;
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
u32 gItemObjCreateFlags;
extern char SoundBuffer[];
extern const char sItemObjStringTableBase[];
extern const char sItemNoDeletableObjectMsg[];
extern const char sItemMemoryCapsuleAsyncEndMsg[];

enum ItemObjStringOffset {
	kItemObjStrF051Root = 0x94,
	kItemObjStrNumFreeItemFmt = 0xA0,
	kItemObjStrNoDeletableObjectMsg = 0xB4,
	kItemObjStrNumDeleteItemFmt = 0xD8,
	kItemObjStrCreateFailedMsg = 0xF0,
	kItemObjStrMemoryCapsuleCreateFmt = 0x114,
	kItemObjStrItemobjCpp = 0x138,
	kItemObjStrMemoryCapsuleAsyncStartMsg = 0x144,
	kItemObjStrExpireByTimeOrDistanceMsg = 0x160,
	kItemObjStrMemoryCapsuleFailedFmt = 0x184,
	kItemObjStrMemoryCapsuleSuccessFmt = 0x1A8,
	kItemObjStrMemoryMagiciteCreateFailedMsg = 0x1CC,
};

static inline CFlatRuntime2* ItemCFlatRuntime()
{
	return &CFlat;
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
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(itemObj->m_stateFlags0) << 28) & 0xC0000000) >> 31) != 0) {
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
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(itemObj->m_stateFlags0) << 28) & 0xC0000000) >> 31) != 0) {
			itemObj->m_flags = static_cast<unsigned char>(__rlwimi(itemObj->m_flags, 1, 7, 24, 24));
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
		CGObject* object = reinterpret_cast<CGObject*>(itemObj);

		if ((object->m_objectFlags & 0x10) == 0) {
			Vec bottom = object->m_worldPosition;
			Vec move;

			move.x = kItemObjZero;
			move.z = kItemObjZero;
			move.y = kItemObjGroundProbeDown;
			bottom.y += kItemObjHeightOffset;
			unsigned int mapMask = object->m_bgHitMask;
			CMapCylinder cylinder(kItemObjBoundsInitMin, kItemObjBoundsInitMax);
			cylinder.m_bottom = bottom;
			cylinder.m_axis.x = kItemObjZero;
			cylinder.m_axis.y = kItemObjGroundProbeDown;
			cylinder.m_axis.z = kItemObjZero;
			cylinder.m_radius = kItemObjZero;

			if (MapMng.CheckHitCylinderNear(&cylinder, &move, mapMask) != 0 &&
			    g_hit_f->m_groupIndex == state) {
				object->m_groundHitOffset.y += jump;
			}
		}
	}
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
	unsigned char* self = (unsigned char*)this;

	if ((signed char)((int)(((unsigned int)*(unsigned char*)(self + 0x9A) << 0x1A) & 0xC0000000) >> 31) != 0) {
		void* charaHandle = *(void**)(self + 0xF8);
		bool hasModel = false;
		if (charaHandle != 0 && *(void**)((unsigned char*)charaHandle + 0x168) != 0) {
			hasModel = true;
		}

		if (hasModel && *(int*)(self + 0x500) == 0xCB && 0.0f < *(float*)(self + 0x74) &&
		    0.0f != *(float*)(self + 0x4B0)) {
			font->SetTlut(7);

			font->SetColor(CColor(0xFF, 0xFF, 0xFF, 255.0f * *(float*)(self + 0x4B0)).color);

			const char* name = Game.m_cFlatDataArr[1].TableStrings(2)[*(int*)(self + 0x570)];
			float width = font->GetWidth(name);
			float depthScale = kItemObjUnitScale / (*(float*)(self + 0x74) - kItemObjHeightOffset);
			float posY = 224.0f - 224.0f * *(float*)(self + 0x6C) * depthScale;
			float posZ = *(float*)(self + 0x70) * depthScale;
			float posX =
			    -(0.5f * width - (320.0f * *(float*)(self + 0x68) * depthScale + 320.0f));

			font->SetPosX(posX);
			font->SetPosY(posY - 11.0f);
			font->SetPosZ(posZ);
			font->Draw(name);
		}
	}
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
	m_createFlags = static_cast<u16>((gItemObjCreateFlags >> 3) & 1);
	loadModel();
}

/*
 * --INFO--
 * PAL Address: 0x80124FE0
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::loadModel()
{
	unsigned char* self = (unsigned char*)this;
	int modelNo = -1;
	int modelVariant = 0;
	int modelFlag = 0;
	unsigned long animFlags = (unsigned long)-1;
	char* standAnim = const_cast<char*>(sStandAnim);
	int useParticleTable = 1;
	int itemType = *(int*)(self + 0x500);

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
		int itemEntryOffset = *(int*)(self + 0x504) * 0x48 + 2;
		int itemEntry = *(unsigned short*)(Game.unkCFlatData0[2] + itemEntryOffset);

		self[0x53] = 1;
		modelNo = itemEntry & 0xFFF;
		modelVariant = itemEntry >> 0xC;
		self[0x50] = static_cast<unsigned char>(__rlwimi(self[0x50], 1, 3, 28, 28));
		*(int*)(self + 0x94) = 0x1194;
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

	if (*(int*)(self + 0x500) == 0x12) {
		DispCharaParts(0);
		self[0x50] = static_cast<unsigned char>(__rlwimi(self[0x50], 1, 4, 27, 27));
	}

	if (useParticleTable != 0) {
		for (int i = 0; i < 3; i++) {
			if (i != 0 || m_createFlags != 1) {
				int entryBase = Game.unkCFlatData0[2] + *(int*)(self + 0x504) * 0x48;
				int particleNo = *(unsigned short*)(entryBase + i * 2 + 0x14);

				if (particleNo != 0xFFFF) {
					const float& particleScaleStep = kItemObjFineStep;
					const float& particleScaleBase = kItemObjParticleScaleBase;
					float particleScale =
					    particleScaleStep * (float)(unsigned short)*(unsigned short*)(entryBase + 0x10) + particleScaleBase;
					putParticle(particleNo | 0x100, *(int*)(self + 0x55C), this, particleScale, 0);
				}
			}
		}
	}

	if (*(int*)(self + 0x500) == 0xCB) {
		const float& randBase = kItemObjMotionStep;
		const float& randRange = kItemObjParticleRandomRange;
		*(float*)(self + 0x1D4) = randBase - Math.RandF(randRange);
		*(unsigned char*)(self + 0x9A) =
		    static_cast<unsigned char>(__rlwimi(*(unsigned char*)(self + 0x9A), 0, 2, 29, 29));
	}

	self[0x54C] = static_cast<unsigned char>(__rlwimi(self[0x54C], 1, 7, 24, 24));
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
#pragma push
#pragma optimization_level 2
void CGItemObj::onHitParticle(int effectIndex, int, int, int, Vec*, PPPIFPARAM* hitParam)
{
	unsigned char* self = (unsigned char*)this;
	int worldParamA = *(int*)(self + 0x500);
	unsigned char* particleRow = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2] + hitParam->m_particleIndex * 0x48);
	int particleAttr = (int)*reinterpret_cast<unsigned short*>(particleRow + 8);

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

			ItemCFlatRuntime()->EndParticleSlot(*(int*)(self + 0x55C), 0);
			ItemCFlatRuntime()->ResetParticleWork(particleNo | 0x100, *(int*)(self + 0x55C));
			ItemCFlatRuntime()->SetParticleWorkPos(*(Vec*)(self + 0x15C), kItemObjZero);
			ItemCFlatRuntime()->SetParticleWorkCol(9, 0, kItemObjUnitScale);
			ItemCFlatRuntime()->SetParticleWorkParam(classControl, this);
			ItemCFlatRuntime()->PutParticleWork();
			*(unsigned int*)(self + 0x1C0) &= 0xFFF7FFFF;
			addSubStat();
		}
	} else {
		if (((worldParamA != 0xCB) || (*(int*)(self + 0x520) != 0x24)) && *(int*)(self + 0x520) != 0x25) {
			return;
		}

		if ((static_cast<unsigned int>(particleAttr - 0x66) <= 1U) || (particleAttr == 0x65)) {
			int classId = hitParam->m_classId;
			CGObject* classObj;

			if (classId != 0) {
				classObj = reinterpret_cast<CGObject*>(ItemCFlatRuntime()->intToClass(classId));
			} else {
				classObj = 0;
			}

			unsigned short cid = classObj->GetCID();

			if ((cid & 0x6D) == 0x6D && *(void**)(self + 0x550) == classObj) {
				changeStat(0x26, 0, 0);
			}
		}
	}

	ItemCFlatRuntime()->IgnoreParticle(effectIndex, this);
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x801254cc
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_propagation off
void CGItemObj::onFrameAlways()
{
	unsigned char* self = (unsigned char*)this;
	int countdown = m_itemJumpCountdown;

	if (countdown != 0) {
		const float& scale = kItemObjWobblePhaseScale;
		int next = countdown - 1;
		m_itemJumpCountdown = next & ~(next >> 0x1F);
		float radius = m_savedBodyRadius * (float)(8 - m_itemJumpCountdown);
		m_bodyEllipsoidRadius = radius * scale;
	}

	if (m_worldParamA == 0xA) {
		int canUseTrace;

		if (static_cast<int>(Game.m_gameWork.m_gameInitFlag) != 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 28) & 0xC0000000) >> 31) != 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 29) & 0xC0000000) >> 31) != 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(*(unsigned char*)(self + 0x9A)) << 24) & 0xC0000000) >> 31) != 0 &&
		    static_cast<int>(CFlatCenterState()) == 0 && *(void**)(self + 0x550) == 0) {
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
#pragma pop

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
 * PAL Address: 0x80125650
 * PAL Size: 916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::carry(CGPartyObj* partyObj, int carryState, int carryMode)
{
	unsigned char* self = (unsigned char*)this;
	CFlatRuntime::CStack stack[3];
	int canSystemCall = 0;

	if (carryState == 0) {
		bool isStageCarry = false;
		bool isMenuBossStage = false;

		if (Game.m_gameWork.m_menuStageMode != 0 &&
			Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			isMenuBossStage = true;
		}
		if (isMenuBossStage) {
			unsigned short cid = static_cast<unsigned short>(partyObj->GetCID());
			unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
			if (((stageCarry >> 5) & 0xFF) != 0) {
				isStageCarry = true;
			}
		}
		if (isStageCarry && *(int*)(*(unsigned char**)((unsigned char*)partyObj + 0x58) + 0x3B4) != 0) {
			canSystemCall = 1;
		}

		*(CGPartyObj**)(self + 0x550) = partyObj;
		*(int*)(self + 0x554) = carryMode;

		if (carryMode == 0) {
			CVector attachOffset(kItemObjZero, kItemObjZero, kItemObjZero);
			Vec* attachOffsetPtr = reinterpret_cast<Vec*>(&attachOffset);
			bool useBossAttachName = false;

			if (Game.m_gameWork.m_menuStageMode != 0) {
				bool condA = false;
				bool condB = false;
				bool condC = false;

				if (Game.m_gameWork.m_menuStageMode != 0 &&
					Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
					condC = true;
				}
				if (condC) {
					unsigned short cid = static_cast<unsigned short>(partyObj->GetCID());
					unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
					if (((stageCarry >> 5) & 0xFF) != 0) {
						condB = true;
					}
				}
				if (condB && *(int*)(*(unsigned char**)((unsigned char*)partyObj + 0x58) + 0x3B4) != 0) {
					condA = true;
				}
				if (condA) {
					useBossAttachName = true;
				}
			}

			const char* attachName = s_itemAttachLeftItem;
			if (useBossAttachName) {
				attachName = s_itemAttachCenterItem3;
			}
			Attach(partyObj, const_cast<char*>(attachName), attachOffsetPtr);
			changeStat(0, 0, 0);
			*(float*)(self + 0x144) = kItemObjZero;
		} else {
			changeStat(0xB, 0, 0);
		}
	} else if (carryState == 1 || carryState == 2) {
		bool isStageCarry = false;
		bool isMenuBossStage = false;

		if (Game.m_gameWork.m_menuStageMode != 0 &&
			Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
			isMenuBossStage = true;
		}
		if (isMenuBossStage) {
			CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
			unsigned short cid = static_cast<unsigned short>(carryObj->GetCID());
			unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
			if (((stageCarry >> 5) & 0xFF) != 0) {
				isStageCarry = true;
			}
		}
		if (isStageCarry && *(int*)(*(unsigned char**)(*(unsigned char**)(self + 0x550) + 0x58) + 0x3B4) != 0) {
			canSystemCall = 1;
		}

		*(int*)(self + 0x554) = carryMode;

		if (carryMode == 0) {
			Vec safePos;
			float safeDist = CalcSafePos(0x41, *(CGPartyObj**)(self + 0x550), &safePos);
			if (safeDist > kItemObjZero) {
				CGPartyObj* carryObj = *(CGPartyObj**)(self + 0x550);
				carryObj->moveVectorHRot(
					kItemObjPi + *(float*)((unsigned char*)carryObj + 0x1A8),
					kItemObjZero,
					safeDist / kItemObjSafeMoveDivisor,
					3);
			}
			Detach();
			*(Vec*)(self + 0x15C) = safePos;
			*(int*)(self + 0x550) = 0;
			changeStat(0, 0, 0);
			*(int*)(self + 0x56C) = 8;
			*(float*)(self + 0x144) = kItemObjZero;
		} else {
			changeStat(((int)~(carryState - 1 | 1 - carryState) >> 0x1F) + 0xD, 0, 0);
		}

		*reinterpret_cast<u32*>(self + 0x94) = 0x1194;
	}

	if ((*(unsigned int*)(self + 0x5C) & 0x10) != 0 && canSystemCall != 0) {
		stack[0].m_word = 3;
		stack[1].m_word = static_cast<unsigned int>(-carryState | carryState) >> 0x1F;
		stack[2].m_word = 0;
		gCFlatRuntime().SystemCall(0, 1, 9, 3, stack, 0);
	}
}

/*
 * --INFO--
 * PAL Address: 0x801259e4
 * PAL Size: 1168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CGPrgObj* CGItemObj::CreateFromScript(
    int createMode, int createFlags, int scriptArg, CGObject* owner, float launchAngle, CGItemObj::CCFS* ccfs)
{
	char* itemObjStrings = const_cast<char*>(sItemObjStringTableBase);
	int freeItemCount = ItemCFlatRuntime()->getNumFreeObject(5);
	System.Printf(itemObjStrings + kItemObjStrNumFreeItemFmt, freeItemCount);

	if (freeItemCount == 0) {
		CFlatRuntime2* runtime = ItemCFlatRuntime();
		int deletedCount = 0;
		unsigned char* bestItemObj = 0;
		int bestScriptObjectPos = 0x00989680;

		for (unsigned char* itemObj = reinterpret_cast<unsigned char*>(runtime->FindGItemObjFirst());
			 itemObj != 0;
		     itemObj = reinterpret_cast<unsigned char*>(
		         runtime->FindGItemObjNext(reinterpret_cast<CGItemObj*>(itemObj)))) {
			if (*(void**)(itemObj + 0x550) == 0 &&
			    static_cast<signed char>(
			        static_cast<int>((static_cast<unsigned int>(itemObj[0x50]) << 28) & 0xC0000000) >> 31) != 0 &&
			    (itemObj[0x53] & 1) != 0 && *(int*)(itemObj + 0x94) < bestScriptObjectPos) {
				bestScriptObjectPos = *(int*)(itemObj + 0x94);
				bestItemObj = itemObj;
			}
		}

		if (bestItemObj != 0) {
			runtime->deleteObject(reinterpret_cast<CFlatRuntime::CObject*>(bestItemObj));
			deletedCount = 1;
		} else {
			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf(itemObjStrings + kItemObjStrNoDeletableObjectMsg);
			}
		}

		System.Printf(itemObjStrings + kItemObjStrNumDeleteItemFmt, deletedCount);
		if (deletedCount == 0) {
			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf(itemObjStrings + kItemObjStrCreateFailedMsg);
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
	*reinterpret_cast<float*>(&inStack[4].m_word) = launchAngle;
	gItemObjCreateFlags = createFlags;
	gCFlatRuntime().SystemCall(0, 1, 7, 5, inStack, &outStack);

	CGPrgObj* newItem = 0;
	if (createMode != 1) {
		newItem = (CGPrgObj*)CFlat.intToClass((int)outStack.m_word);
		unsigned char* itemSelf = (unsigned char*)newItem;

		if (createMode == 2) {
			*(int*)(itemSelf + 0x558) = scriptArg;
			newItem->m_radiusCtrl.y = kItemObjUnitScale;
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
			if (safePosDist > kItemObjZero) {
				owner->moveVectorHRot(kItemObjPi + owner->m_rotBaseY, kItemObjZero,
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
			*(CGObject**)(itemSelf + 0x550) = owner;

			void* ownerScriptSlot = owner->m_scriptHandle[0xED];
			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf(itemObjStrings + kItemObjStrMemoryCapsuleCreateFmt, ownerScriptSlot);
			}
			*(CGPrgObj**)(CGMonObj::m_boss + (int)ownerScriptSlot * 4 + 8) = newItem;

			CCharaPcs::CHandle* handle =
			    new (Game.m_mainStage, itemObjStrings + kItemObjStrItemobjCpp, 0x28E) CCharaPcs::CHandle;
			reinterpret_cast<CGItemObj*>(newItem)->m_pendingModelHandle = handle;
			handle->Add();

			reinterpret_cast<CGItemObj*>(newItem)->m_pendingModelHandle->LoadModelASync(2, ccfs->m_modelId, ccfs->m_modelParam);

			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf(itemObjStrings + kItemObjStrMemoryCapsuleAsyncStartMsg);
			}

			reinterpret_cast<CGItemObj*>(newItem)->m_pendingAnimFlags = ccfs->m_pendingAnimFlags;
			reinterpret_cast<CGItemObj*>(newItem)->m_pendingAnimName = ccfs->m_pendingAnimName;
			reinterpret_cast<CGItemObj*>(newItem)->m_memoryCapsuleNameIndex = ccfs->m_memoryCapsuleNameIndex;
		}
	}

	return newItem;
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
	unsigned int numFreeObjects = ItemCFlatRuntime()->getNumFreeObject(5);

	return (-numFreeObjects & ~numFreeObjects) >> 31;
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
		unsigned char* bestItemObj = 0;
		int bestScriptObjectPos = 0x00989680;

		for (unsigned char* itemObj = reinterpret_cast<unsigned char*>(ItemCFlatRuntime()->FindGItemObjFirst());
			 itemObj != 0;
			 itemObj = reinterpret_cast<unsigned char*>(
			     ItemCFlatRuntime()->FindGItemObjNext(reinterpret_cast<CGItemObj*>(itemObj)))) {
			if (*(void**)(itemObj + 0x550) == 0 &&
				static_cast<signed char>(
				    static_cast<int>((static_cast<unsigned int>(itemObj[0x50]) << 28) & 0xC0000000) >> 31) != 0 &&
				(((int)(char)itemObj[0x53] & deleteMask) != 0) && *(int*)(itemObj + 0x94) < bestScriptObjectPos) {
				bestScriptObjectPos = *(int*)(itemObj + 0x94);
				bestItemObj = itemObj;
			}
		}

		if (bestItemObj != 0) {
			gCFlatRuntime().deleteObject(reinterpret_cast<CFlatRuntime::CObject*>(bestItemObj));
		} else {
			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf(const_cast<char*>(sItemNoDeletableObjectMsg));
			}
			break;
		}

		deletedCount++;
	}

	return deletedCount;
}

/*
 * --INFO--
 * PAL Address: 0x80125fb0
 * PAL Size: 3416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onFrameStat()
{
	unsigned char* self = (unsigned char*)this;
	CGPrgObj* prgObj = (CGPrgObj*)this;
	int stateId = m_lastStateId;
	char* itemObjStrings = const_cast<char*>(sItemObjStringTableBase);
	float zero = kItemObjZero;

	switch (stateId) {
	case 0x1b:
		if (m_stateFrame <= 8) {
			float wobble = (float)sin((double)(kItemObjHalfPi * (float)m_stateFrame * kItemObjWobblePhaseScale));

			m_rotationZ = wobble;
			m_rotationY = wobble;
			m_rotationX = wobble;

			if (m_stateFrame == 8) {
				changeStat(0, 0, 0);
			}
		}
		break;
	case 0: {
		if (m_owner == 0 &&
		    static_cast<signed char>(
		        static_cast<int>((static_cast<unsigned int>(m_stateFlags0) << 28) & 0xC0000000) >> 31) != 0) {
			float distance = kItemObjZero;

			if (Game.unk_flat3_0xc7d0 != 0) {
				distance = PSVECDistance((Vec*)(self + 0x15c), (Vec*)(Game.unk_flat3_0xc7d0 + 0x15c));
			} else {
				if (static_cast<int>(CFlatCenterState()) == 1) {
					Vec partyCenter;

					partyCenter.x = (Game.m_partyMinX + Game.m_partyMaxX) * kItemObjHalf;
					partyCenter.y = (Game.m_partyMinY + Game.m_partyMaxY) * kItemObjHalf;
					partyCenter.z = (Game.m_partyMinZ + Game.m_partyMaxZ) * kItemObjHalf;
					distance = PSVECDistance((Vec*)(self + 0x15c), &partyCenter);
				}
			}

			if (*(int*)(self + 0x94) <= 0 || distance > kItemObjExpireDistance) {
				System.Printf(itemObjStrings + kItemObjStrExpireByTimeOrDistanceMsg);
				m_bgDownDist = kItemObjMotionStep;
				m_stepSlopeLimit = zero;
				m_bgColMask = 1;
				ItemCFlatRuntime()->EndParticle(m_charaModelHandle);
				changeStat(9, 0, 0);
			}
		}
		break;
	}
	case 0xB:
		if (m_stateFrame == m_carryFrame) {
			CVector attachOffset(kItemObjZero, kItemObjZero, kItemObjZero);
			Vec* attachOffsetPtr = reinterpret_cast<Vec*>(&attachOffset);
			bool useBossAttachName = false;

			if (Game.m_gameWork.m_menuStageMode != 0) {
				bool condA = false;
				bool condB = false;
				bool condC = false;

				if (Game.m_gameWork.m_menuStageMode != 0 &&
				    Game.m_gameWork.m_bossArtifactStageIndex < 0xF) {
					condC = true;
				}
				if (condC) {
					unsigned int cid = static_cast<unsigned short>(m_owner->GetCID());
					unsigned int stageCarry = (unsigned int)__cntlzw(0x6D - (cid & 0x6D));
					if (((stageCarry >> 5) & 0xFF) != 0) {
						condB = true;
					}
				}
				if (condB &&
				    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_owner->m_scriptHandle) + 0x3B4) != 0) {
					condA = true;
				}
				if (condA) {
					useBossAttachName = true;
				}
			}

			CGObject* attachOwner = m_owner;
			const char* attachName = s_itemAttachLeftItem;
			if (useBossAttachName) {
				attachName = s_itemAttachCenterItem3;
			}
			Attach(attachOwner, const_cast<char*>(attachName), attachOffsetPtr);
			changeStat(0, 0, 0);
			m_bodyEllipsoidRadius = kItemObjZero;
		}
		break;
	case 0xC:
	case 0xD:
		if (m_stateFrame == m_carryFrame) {
			Vec safePos;
			float launchSpeed;

			if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_menuStageMode != 0 &&
			    Game.m_gameWork.m_bossArtifactStageIndex < 0xF &&
			    (static_cast<unsigned short>(m_owner->GetCID()) & 0x6D) == 0x6D &&
			    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_owner->m_scriptHandle) + 0x3B4) != 0) {
				launchSpeed = kItemObjUnitScale;
			} else if (static_cast<int>(CFlatCenterState()) == 1) {
				int carryCid = static_cast<unsigned short>(m_owner->GetCID());
				if ((carryCid & 0x6D) == 0x6D &&
				    2 <= *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_owner->m_scriptHandle) + 0x3E0)) {
					launchSpeed = kItemObjUnitScale;
				} else {
					launchSpeed = kItemObjDouble;
				}
			} else {
				launchSpeed = kItemObjSafeMoveDivisor;
			}

			float safeDist = CalcSafePos(0x41, m_owner, &safePos);

			if (safeDist > kItemObjZero) {
				m_owner->moveVectorHRot(kItemObjPi + m_owner->m_rotBaseY, kItemObjZero,
				                        safeDist / kItemObjSafeMoveDivisor, 3);
			}

			Detach();
			m_worldPosition = safePos;

			float moveSpeed;
			if (m_lastStateId == 0xC) {
				moveSpeed = launchSpeed;
			} else {
				moveSpeed = kItemObjThrowMoveSpeed;
			}

			float ownerCos = (float)cos((double)m_owner->m_rotTargetY);
			float ownerSin = (float)sin((double)m_owner->m_rotTargetY);
			const CVector& moveVec = CVector(ownerSin, kItemObjMotionStep, ownerCos);
			MoveVector(reinterpret_cast<Vec*>(const_cast<CVector*>(&moveVec)), moveSpeed, 1, 0, 1, 0);

			m_owner = 0;
			m_itemJumpCountdown = 8;
			m_bodyEllipsoidRadius = kItemObjZero;
		}

		if (m_carryFrame <= m_stateFrame) {
			int worldParamA = m_worldParamA;

			if ((worldParamA == 0xD || worldParamA == 0xE) &&
			    static_cast<signed char>(
			        static_cast<int>((static_cast<unsigned int>(self[0x50]) << 24) & 0xC0000000) >> 31) != 0) {
				changeStat(0x1F, 0, 0);
			} else if (static_cast<signed char>(
			               static_cast<int>((static_cast<unsigned int>(self[0x50]) << 24) & 0xC0000000) >> 31) != 0) {
				changeStat(0, 0, 0);
			}
		}
		break;
	case 0xE:
		if (m_stateFrame == 0) {
			prgObj->m_bgColMask = 0;
			*reinterpret_cast<unsigned char*>(&prgObj->m_weaponNodeFlags) =
			    static_cast<unsigned char>(__rlwimi(*reinterpret_cast<unsigned char*>(&prgObj->m_weaponNodeFlags), 0, 4, 27, 27));
			prgObj->m_groundHitOffset.z = zero;
			prgObj->m_groundHitOffset.y = zero;
			prgObj->m_groundHitOffset.x = zero;
		} else if (m_stateFrame == 4) {
			prgObj->m_bgDownDist = kItemObjWobblePhaseScale;
			prgObj->m_stepSlopeLimit = zero;
			ItemCFlatRuntime()->EndParticle(prgObj->m_charaModelHandle);
		} else if (m_stateFrame == 0xC) {
			self[0x38] = static_cast<unsigned char>(__rlwimi(self[0x38], 1, 7, 24, 24));
		}

		if (7 < m_stateFrame) {
			prgObj->m_rotTargetY = prgObj->m_rotTargetY + kItemObjMotionStep;
			prgObj->m_worldPosition.x =
			    kItemObjMotionStep * (m_owner->m_worldPosition.x - prgObj->m_worldPosition.x) + prgObj->m_worldPosition.x;
			prgObj->m_worldPosition.y =
			    kItemObjMotionStep * (kItemObjHalf * m_owner->unk_0x188 + m_owner->m_worldPosition.y - prgObj->m_worldPosition.y) +
			    prgObj->m_worldPosition.y;
			prgObj->m_worldPosition.z =
			    kItemObjMotionStep * (m_owner->m_worldPosition.z - prgObj->m_worldPosition.z) + prgObj->m_worldPosition.z;
			prgObj->m_rotationX = prgObj->m_rotationX * kItemObjRotationDamping;
			prgObj->m_rotationY = prgObj->m_rotationY * kItemObjRotationDamping;
			prgObj->m_rotationZ = prgObj->m_rotationZ * kItemObjRotationDamping;
		}
		break;
	case 9:
		if (m_stateFrame == 8) {
			self[0x38] = static_cast<unsigned char>(__rlwimi(self[0x38], 1, 7, 24, 24));
		}
		break;
	case 0x1F:
		PartMng.pppSetLocSlot(m_particleSlot, &prgObj->m_worldPosition);

		if (m_subState != 1) {
			if (m_subState < 1 && 0 <= m_subState && m_subFrame == 0) {
			int particleNoA;
			int particleNoB;

			if (m_worldParamA == 0xE) {
				particleNoA = 0x19;
				particleNoB = 0x1E;
			} else {
				particleNoA = 0x18;
				particleNoB = 0x1D;
			}

			putParticle(particleNoA | 0x100, 0, &prgObj->m_worldPosition, kItemObjUnitScale, 0);
			putParticle(particleNoB | 0x100, m_particleSlot, &prgObj->m_worldPosition, kItemObjUnitScale, 0);
			playSe3D(0x1A, 0x32, 0x96, 0, 0);
			prgObj->m_displayFlags &= ~1;
			prgObj->m_bgColMask &= 0xFFFFFFF1;
			prgObj->m_moveOffset.z = zero;
			prgObj->m_moveOffset.x = zero;
			prgObj->m_bgColMask |= 0x80000;

			const CVector& damageOffset = CVector(zero, zero, zero);
			SetDamageCol(0, itemObjStrings + kItemObjStrF051Root, kItemObjDamageRadius, kItemObjDamageRadius,
			             reinterpret_cast<Vec*>(const_cast<CVector*>(&damageOffset)));
			*reinterpret_cast<int*>(&prgObj->m_damageColliders[1].m_localPosition.x) = 9;
			}
		} else if (m_subFrame == 0x7D) {
			ItemCFlatRuntime()->EndParticleSlot(m_particleSlot, 0);
		}
		break;
	case 0x23:
		if (m_subState != 0 && m_subState == 1) {
			CCharaPcs::CHandle* handle = prgObj->m_charaModelHandle;
			if (handle != 0 && handle->m_model != 0) {
				unsigned char* model = reinterpret_cast<unsigned char*>(handle->m_model);
				model[0x10C] = static_cast<unsigned char>(__rlwimi(model[0x10C], 1, 7, 24, 24));
			}

			if (m_subFrame <= 8) {
				float wobble = (float)sin((double)(kItemObjHalfPi * (float)m_subFrame * kItemObjWobblePhaseScale));

				prgObj->m_rotationZ = wobble;
				prgObj->m_rotationY = wobble;
				prgObj->m_rotationX = wobble;

				if (m_subFrame == 8) {
					prgObj->m_bgColMask |= 0x80000;
					changeStat(0x24, 0, 0);
				}
			}
		}
		break;
	case 0x24:
		prgObj->m_moveOffset.x = kItemObjMoveOffsetXZ;
		prgObj->m_moveOffset.y = kItemObjUnitScale;
		prgObj->m_moveOffset.z = kItemObjMoveOffsetXZ;

		if (prgObj->m_worldPosition.y < kItemObjHeightOffset) {
			prgObj->m_groundHitOffset.y += kItemObjBounceAccel * prgObj->m_moveTimer;
		} else if (prgObj->m_worldPosition.y > kItemObjMemoryRadius) {
			prgObj->m_groundHitOffset.y = -(kItemObjBounceAccel * prgObj->m_moveTimer - prgObj->m_groundHitOffset.y);
		}

		{
			float timer = prgObj->m_moveTimer;
			float current = prgObj->m_groundHitOffset.y;
			float clamped = kItemObjDouble * -timer;

			if (!(current < clamped)) {
				float maxClamp = kItemObjDouble * timer;
				clamped = current;
				if (maxClamp < current) {
					clamped = maxClamp;
				}
			}
			prgObj->m_groundHitOffset.y = clamped;
		}

		prgObj->m_rotTargetY = prgObj->m_rotTargetY + kItemObjFineStep;
		prgObj->m_groundHitOffset.x =
		    kItemObjFineStep * -(prgObj->m_worldPosition.x - *(float*)(*(unsigned char**)(self + 0x550) + 0x15C));
		prgObj->m_groundHitOffset.z =
		    kItemObjFineStep * -(prgObj->m_worldPosition.z - *(float*)(*(unsigned char**)(self + 0x550) + 0x164));
		break;
	case 0x25: {
		prgObj->m_moveOffset.y = kItemObjMoveOffsetXZ;
		prgObj->m_rotTargetY = prgObj->m_rotTargetY + kItemObjMemoryTurnStep;

		CVector monTarget(*reinterpret_cast<Vec*>(CGMonObj::m_aiWork + 4));
		CVector worldPos(prgObj->m_worldPosition);
		CVector delta;

		PSVECSubtract(reinterpret_cast<Vec*>(&monTarget), reinterpret_cast<Vec*>(&worldPos), reinterpret_cast<Vec*>(&delta));
		monTarget.x = delta.x;
		monTarget.y = delta.y;
		monTarget.z = delta.z;

		float distance = PSVECMag(reinterpret_cast<Vec*>(&monTarget));
		if (distance < kItemObjMemoryRadius) {
			changeStat(0x27, 0, 0);
		} else if (distance > zero) {
			float moveScale = kItemObjMemoryChaseAccel * prgObj->m_moveTimer;

			prgObj->m_groundHitOffset.x += kItemObjMemoryChaseScale * monTarget.x * moveScale;
			prgObj->m_groundHitOffset.y += kItemObjMemoryChaseScale * monTarget.y * moveScale;
			prgObj->m_groundHitOffset.z += kItemObjMemoryChaseScale * monTarget.z * moveScale;
		} else {
			prgObj->m_groundHitOffset.z = zero;
			prgObj->m_groundHitOffset.y = zero;
			prgObj->m_groundHitOffset.x = zero;
		}
		break;
	}
	case 0x27: {
		int pdtNo = -1;

		prgObj->m_groundHitOffset.z = zero;
		prgObj->m_groundHitOffset.y = zero;
		prgObj->m_groundHitOffset.x = zero;

		if (m_stateFrame == 0) {
			prgObj->m_stepSlopeLimit = zero;
			ItemCFlatRuntime()->EndParticleSlot(m_particleSlot, 0);

			int* soundData = *(int**)(*(int*)(*reinterpret_cast<int*>(CGMonObj::m_boss) + 0xF8) + 0x178);
			if (soundData != 0) {
				pdtNo = soundData[5];
			} else {
				pdtNo = -1;
			}

			float particleScale =
			    kItemObjFineStep * (float)*(unsigned short*)(Game.unkCFlatData0[2] + prgObj->m_worldParamB * 0x48 + 0x10) +
			    kItemObjParticleScaleBase;
			putParticle((pdtNo << 8) | 0x13, m_particleSlot, this, particleScale, 0x12903);
		} else if (m_stateFrame == 0xD) {
			int ownerSlot = *(int*)(*(unsigned char**)(*(unsigned char**)(self + 0x550) + 0x58) + 0x3B4);

			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf(itemObjStrings + kItemObjStrMemoryCapsuleFailedFmt, ownerSlot);
			}

			CFlatRuntime::CStack stack;
			stack.m_word = 0;
			*(int*)(CGMonObj::m_boss + ownerSlot * 4 + 8) = 0;
			gCFlatRuntime().SystemCall(
			    *reinterpret_cast<CFlatRuntime::CObject**>(self + 0x550), 2, 0x16, 1, &stack, 0);

			self[0x38] = static_cast<unsigned char>(__rlwimi(self[0x38], 1, 7, 24, 24));
		}
		break;
	}
	case 0x26: {
		int pdtNo = -1;

		prgObj->m_groundHitOffset.z = zero;
		prgObj->m_groundHitOffset.y = zero;
		prgObj->m_groundHitOffset.x = zero;

		if (m_stateFrame == 0) {
			prgObj->m_stepSlopeLimit = zero;
			ItemCFlatRuntime()->EndParticleSlot(m_particleSlot, 0);

			int* soundData = *(int**)(*(int*)(*reinterpret_cast<int*>(CGMonObj::m_boss) + 0xF8) + 0x178);
			if (soundData != 0) {
				pdtNo = soundData[5];
			} else {
				pdtNo = -1;
			}

			float particleScale =
			    kItemObjFineStep * (float)*(unsigned short*)(Game.unkCFlatData0[2] + prgObj->m_worldParamB * 0x48 + 0x10) +
			    kItemObjParticleScaleBase;
			putParticle((pdtNo << 8) | 4, m_particleSlot, this, particleScale, 0x12908);
		} else if (m_stateFrame == 0xD) {
			int ownerSlot = *(int*)(*(unsigned char**)(*(unsigned char**)(self + 0x550) + 0x58) + 0x3B4);

			if ((unsigned int)System.m_execParam >= 3U) {
				System.Printf(itemObjStrings + kItemObjStrMemoryCapsuleSuccessFmt, ownerSlot);
			}

			*(int*)(CGMonObj::m_boss + ownerSlot * 4 + 8) = 0;
			CGPrgObj* newItem = CreateFromScript(0, 0, 0x103, 0, kItemObjZero, 0);
			if (newItem != 0) {
				unsigned char* newItemSelf = reinterpret_cast<unsigned char*>(newItem);

				*reinterpret_cast<float*>(newItemSelf + 0x168) = prgObj->m_worldPosition.x;
				*reinterpret_cast<float*>(newItemSelf + 0x16C) = prgObj->m_worldPosition.y;
				*reinterpret_cast<float*>(newItemSelf + 0x170) = prgObj->m_worldPosition.z;
				newItem->m_worldPosition.x = *reinterpret_cast<float*>(newItemSelf + 0x168);
				newItem->m_worldPosition.y = *reinterpret_cast<float*>(newItemSelf + 0x16C);
				newItem->m_worldPosition.z = *reinterpret_cast<float*>(newItemSelf + 0x170);

				CFlatRuntime::CStack stack;
				stack.m_word = 1;
				gCFlatRuntime().SystemCall(
				    *reinterpret_cast<CFlatRuntime::CObject**>(self + 0x550), 2, 0x16, 1, &stack, 0);
			} else {
				if ((unsigned int)System.m_execParam > 1U) {
					System.Printf(itemObjStrings + kItemObjStrMemoryMagiciteCreateFailedMsg);
				}
			}

			self[0x38] = static_cast<unsigned char>(__rlwimi(self[0x38], 1, 7, 24, 24));
		}
		break;
	}
	default:
		break;
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
	unsigned char* self = (unsigned char*)this;
	CCharaPcs::CHandle* handle = m_pendingModelHandle;

	if (handle != 0 && handle->IsLoadModelASyncCompleted()) {
		if ((unsigned int)System.m_execParam >= 3U) {
			System.Printf(const_cast<char*>(sItemMemoryCapsuleAsyncEndMsg));
		}

		m_charaModelHandle = reinterpret_cast<CCharaPcs::CHandle*>(m_pendingModelHandle);
		m_pendingModelHandle = 0;

		if (m_worldParamA == 0xCB) {
			LoadAnim(m_pendingAnimName, 0, 0, 2, m_pendingAnimFlags);
			SetAnimSlot(0, 0);
			PlayAnim(0, 1, 0, -1, -1, 0);

			CGObject* owner = m_owner;
			int ownerScriptSlot = *(int*)(*(int*)((unsigned char*)owner + 0x58) + 0x3B4);
			int* soundData = *(int**)(*(int*)(*reinterpret_cast<int*>(CGMonObj::m_boss) + 0xF8) + 0x178);
			int soundEntry;
			if (soundData != 0) {
				soundEntry = soundData[5];
			} else {
				soundEntry = -1;
			}

			unsigned char* itemTable = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2]);
			float particleValue = static_cast<float>(*reinterpret_cast<unsigned short*>(itemTable + m_worldParamB * 0x48 + 0x10));
			float particleScale = kItemObjFineStep * (float)particleValue + kItemObjParticleScaleBase;
			putParticle(ownerScriptSlot | (soundEntry << 8), m_particleSlot, this, particleScale, 0x12909);

			SetDamageCol(0, const_cast<char*>(s_itemDamageBoneHip), kItemObjMemoryRadius, kItemObjMemoryRadius,
			             CVector(kItemObjZero, kItemObjZero, kItemObjZero));
			*reinterpret_cast<unsigned int*>(&m_damageColliders[1].m_localPosition.x) = 8;
			addSubStat();
		}
	}

	CGPrgObj::onFrame();
}

/*
 * --INFO--
 * PAL Address: 0x80126eb4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onCancelStat(int)
{
	unsigned char* self = (unsigned char*)this;

	if (*(int*)(self + 0x520) == 0x1b) {
		*(unsigned int*)(self + 0x1c0) = *(unsigned int*)(self + 0x1c0) | 2;
		*(float*)(self + 0x17c) = kItemObjUnitScale;
		*(float*)(self + 0x178) = kItemObjUnitScale;
		*(float*)(self + 0x174) = kItemObjUnitScale;
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
	unsigned char* self = (unsigned char*)this;

	if (state < 0x28 && state >= 0x26) {
		*(unsigned int*)(self + 0x1c0) = *(unsigned int*)(self + 0x1c0) & 0xfff7fffe;
	}
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
	unsigned char* self = (unsigned char*)this;

	if (static_cast<signed char>(
	        static_cast<int>((static_cast<unsigned int>(self[0x50]) << 28) & 0xC0000000) >> 31) != 0 &&
	    *(void**)(self + 0x550) == 0) {
		*(int*)(self + 0x94) = *(int*)(self + 0x94) - 1;
	}
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
 * PAL Address: 0x80126f3c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGItemObj::onDestroy()
{
	unsigned char* self = (unsigned char*)this;

	if (*(void**)(self + 0x564) != 0) {
		delete reinterpret_cast<CCharaPcs::CHandle*>(*(void**)(self + 0x564));
	}

	ItemCFlatRuntime()->DeleteParticleSlot(*(int*)(self + 0x55c), 0);
	CGPrgObj::onDestroy();
}

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
