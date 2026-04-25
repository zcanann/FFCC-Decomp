#include "ffcc/partyobj.h"
#include "ffcc/gobjwork.h"
#include "ffcc/pad.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/joybus.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_minigame.h"
#include "ffcc/ringmenu.h"
#include "ffcc/sound.h"
#include "ffcc/itemobj.h"

#include <math.h>
#include "ffcc/fontman.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" int CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(CMapMng*, CMapCylinder*, Vec*, unsigned int);
extern "C" void CalcHitPosition__7CMapObjFP3Vec(void*, Vec*);
extern "C" void GetHitFaceNormal__7CMapObjFP3Vec(void*, Vec*);
extern "C" int CalcHitSlide__7CMapObjFP3Vecf(void*, Vec*);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
	void*, void*, int, int, int, void*, void*);
extern "C" int CanCreateFromScript__9CGItemObjFv();
extern "C" void Printf__7CSystemFPce(CSystem*, const char*, ...);
extern "C" CGObject* FindGObjFirst__13CFlatRuntime2Fv(void*);
extern "C" CGObject* FindGObjNext__13CFlatRuntime2FP8CGObject(void*, CGObject*);
extern "C" void onPush__9CGBaseObjFP9CGBaseObji(CGBaseObj*, CGBaseObj*, int);
extern "C" void* CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(
    int type, int createMode, int itemId, CGObject* owner, float arg, void* cfs);

static const char s_partyObjStateFmt[] = "mode:%d stat:%d sub:%d frame:%d alive:%d tgt:%d ghost:%d";
static const char s_partyBonusCountFmt[] = "SetBonusCondition num:%d";
static const char s_partyBonusRandomFmt[] = "SetBonusCondition slot:%d idx:%d bonus:%d";
static const char s_partyBonusFixedFmt[] = "SetBonusCondition slot:%d bonus:%d";
static const char s_partyBonusKind0Fmt[] = "bonus kind0:%d";
static const char s_partyBonusKind1Fmt[] = "bonus kind1:%d";
static const char s_partyBonusKind4Fmt[] = "bonus kind4:%d";
static const char s_partyBonusAddFmt[] = "bonus slot:%d add:%d";
static const char s_partyBonusSubFmt[] = "bonus slot:%d sub:%d";
static const char s_partyBonusUnknownFmt[] = "bonus unknown";

extern float FLOAT_80331a78;
extern float FLOAT_80331a54;
extern float FLOAT_80331a74;
extern float FLOAT_80331a9c;
extern float FLOAT_80331aa0;
extern float FLOAT_80331ac4;
extern float FLOAT_80331ac8;
extern float FLOAT_80331acc;
extern float FLOAT_80331ad0;
extern float FLOAT_80331ad4;
extern float FLOAT_80331ad8;
extern float FLOAT_80331ADC;
extern float FLOAT_80331b00;
extern float FLOAT_80331b04;
extern float FLOAT_80331b08;

struct GhostPartyWork {
	int mood;
	int thresholdA;
	int thresholdB;
	int thresholdC;
	int slotSel;
	float carrySpeed;
	int pressure;
	int settleTimer;
	int activeTrailCount;
	int trailIndex;
	Vec trail[5];
	Vec leaderTrail[5];
	Vec carryDir;
	int auraParticle;
};

static GhostPartyWork sGhostPartyWork;

struct PartyObjOverlay {
	unsigned char partyFlags;
	unsigned char _pad6B9[3];
	int unk6BC;
	int unk6C0;
	unsigned char commandFlags;
	unsigned char _pad6C5[3];
	int attackSel;
	int unk6CC;
	int unk6D0;
	unsigned short unk6D2;
	unsigned short _pad6D4;
	int weaponRef;
	int weaponItem;
	union {
		int pendingWeaponItem;
		CGBaseObj* carryTarget;
	};
	union {
		CGObject* target;
		CGBaseObj* secondaryTarget;
	};
	union {
		CGObject* targetOverride;
		float targetSearchDistance;
	};
	union {
		int unk6EC;
		int _legacy6EC;
	};
	CGObject* carryObject;
	short commandMode;
	unsigned short _pad6F6;
	int bonusCondition;
};

static inline PartyObjOverlay& PartyData(CGPartyObj* self)
{
	return *reinterpret_cast<PartyObjOverlay*>(reinterpret_cast<unsigned char*>(self) + 0x6B8);
}

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

static int getPadConnectedForSlot(int slot)
{
	if (Pad._452_4_ != 0 || (slot == 0 && Pad._448_4_ != -1)) {
		return 0;
	}

	int idx = slot & ~((~(Pad._448_4_ - slot | slot - Pad._448_4_) >> 31));
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Pad) + 0x54 + idx * 0x54);
}

static bool isMenuPcsCommandBusy()
{
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x740) != 0;
}

static CRingMenu* getBattleRingMenuForPort(int port)
{
	return *reinterpret_cast<CRingMenu**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x13C + port * 4);
}

static int getPartyJoybusPort(CGPartyObj* self)
{
	return static_cast<int>(reinterpret_cast<unsigned char*>(self->m_scriptHandle)[0xED]);
}

static unsigned short getItemKindFromCfd(int itemId)
{
	if (itemId <= 0 || Game.unkCFlatData0[2] == 0) {
		return 0;
	}

	return *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48);
}

static float getPadAxisForSlot(int slot, int offset)
{
	if (Pad._452_4_ != 0 || (slot == 0 && Pad._448_4_ != -1)) {
		return 0.0f;
	}

	int idx = slot & ~((~(Pad._448_4_ - slot | slot - Pad._448_4_) >> 31));
	return *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(&Pad) + offset + idx * 0x54);
}

static bool isBossArtifactStage()
{
	return Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0x0F;
}

static bool isGhostPartyTargetMode(CGPartyObj* self)
{
	if (!isBossArtifactStage()) {
		return false;
	}
	if ((self->GetCID() & 0x6D) != 0x6D) {
		return false;
	}
	if (self->m_scriptHandle == nullptr) {
		return false;
	}
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(self->m_scriptHandle) + 0x3B4) != 0;
}

static void* getMapHitObject()
{
	return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MapMng) + 0x22A88);
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

	PartyObjOverlay& party = PartyData(this);
	party.unk6D0 = 0;
	party.attackSel = 0;
	party.unk6CC = 0;
	party.unk6BC = 0;
	party.unk6C0 = -1;
	party.unk6D2 = 0;

	party.partyFlags &= 0x7F;
	party.partyFlags &= 0xF7;
	party.partyFlags &= 0xBF;
	party.partyFlags &= 0xDF;
	party.partyFlags &= 0xEF;
	party.partyFlags &= 0xFB;
	party.partyFlags &= 0xFD;

	m_targetDist = FLOAT_80331a78;
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
	unsigned char* partyFlags = &PartyData(this).partyFlags;
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
	PartyObjOverlay& party = PartyData(this);
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	party.partyFlags &= 0xBF;

	switch (state) {
	case 0:
		party.partyFlags |= 0x40;
		break;
	case 1: {
		*reinterpret_cast<int*>(self + 0x550) = (party.attackSel == 0) ? 5 : ((party.attackSel == 1) ? 8 : 9);
		break;
	}
	case 2:
		*reinterpret_cast<int*>(self + 0x550) = 0x0F;
		*reinterpret_cast<int*>(self + 0x554) = 0x10;
		*reinterpret_cast<int*>(self + 0x558) = 0x11;
		*reinterpret_cast<int*>(self + 0x68C) = 0;
		if (*reinterpret_cast<int*>(self + 0x560) != 0x103) {
			*reinterpret_cast<int*>(self + 0x68C) = calcCastTime(*reinterpret_cast<int*>(self + 0x560));
		}
		break;
	case 6:
		*reinterpret_cast<int*>(self + 0x550) = 0x12;
		*reinterpret_cast<int*>(self + 0x554) = 0x13;
		*reinterpret_cast<int*>(self + 0x68C) = calcCastTime(*reinterpret_cast<int*>(self + 0x560));
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
	PartyObjOverlay& party = PartyData(this);
	unsigned char* self = reinterpret_cast<unsigned char*>(this);

	switch (m_lastStateId) {
	case 2:
		party.partyFlags &= 0xBF;
		party.partyFlags &= 0xDF;
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
		if (((party.partyFlags & 0x04) != 0) && (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0)) {
			addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
			party.partyFlags &= 0xFB;
		}
		enableDamageCol(1);
		setIdleMotion();
		if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
			m_alpha = 1.0f;
			m_bgColMask &= 0xFFFEFFF1;
		} else {
			endPSlotBit(0x10000);
			m_alpha = 0.5f;
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
	PartyObjOverlay& party = PartyData(this);
	const unsigned char slot = static_cast<unsigned char>(m_animStateMisc);
	void* portIndex = m_scriptHandle != nullptr ? m_scriptHandle[0xED] : nullptr;

	if ((party.partyFlags & 0x10) == 0) {
		if (Game.m_gameWork.m_menuStageMode != 0) {
			return;
		}

		if (getPadConnectedForSlot(slot) == 0) {
			return;
		}

		if (System.m_execParam > 2) {
			Printf__7CSystemFPce(&System, "port:%d mode:%d", portIndex, Joybus.GetCtrlMode(slot));
		}

		Joybus.ChgCtrlMode(reinterpret_cast<int>(portIndex));
		if ((CFlat[0x12A0] & 8) != 0) {
			Sound.PlaySe(8, 0x40, 0x7F, 0);
		}
		return;
	}

	if (Game.m_gameWork.m_menuStageMode == 0 && Joybus.GetPadType(slot) == 0x40000) {
		unsigned short trig = getPadTrigForSlot(slot);
		if ((trig & 0x10) == 0) {
			return;
		}
	} else {
		if (Game.m_gameWork.m_menuStageMode == 0) {
			return;
		}
		if (Game.m_gameWork.m_gamePaused != 0) {
			return;
		}
		if (slot != 0) {
			return;
		}
		if ((getPadTrigForSlot(slot) & 0x800) == 0) {
			return;
		}
	}

	if (Game.m_gameWork.m_menuStageMode != 0) {
		const bool canOpenStageMenu =
		    ((static_cast<int>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&m_weaponNodeFlags)) << 0x18) < 0) &&
		     ((static_cast<int>(static_cast<unsigned int>(static_cast<unsigned char>(m_shieldAttachNodeIndex)) << 0x18) < 0) ||
		      ((party.commandMode & 2) != 0) ||
		      ((party.commandMode & 4) != 0)) &&
		     (static_cast<int>(static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x63C)) << 0x18) < 0) &&
		     (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0));

		if (canOpenStageMenu) {
			Joybus.ChgCtrlMode(reinterpret_cast<int>(portIndex));
			Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 1;
		} else {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
		}
		return;
	}

	if (getPadConnectedForSlot(slot) == 0) {
		if ((CFlat[0x12A0] & 8) != 0) {
			Sound.PlaySe(7, 0x40, 0x7F, 0);
		}
	} else if ((CFlat[0x12A0] & 8) != 0) {
		Sound.PlaySe(8, 0x40, 0x7F, 0);
	}

	Joybus.ChgCtrlMode(reinterpret_cast<int>(portIndex));
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
			PartyData(this).commandFlags &= 0xDF;
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
		CGPartyObj* party = Game.m_partyObjArr[i];
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
	if (m_scriptHandle == nullptr) {
		return;
	}

	CGCharaObj::onFramePreCalc();

	PartyObjOverlay& party = PartyData(this);
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (Game.unk_flat3_0xc7d0 != 0) {
		const Vec* chalicePos = reinterpret_cast<Vec*>(Game.unk_flat3_0xc7d0 + 0x15C);
		m_projection.z = PSVECDistance(&m_worldPosition, chalicePos);
	}

	if (((self[0x63C] & 0x80) != 0) && ((party.partyFlags & 0x80) == 0)) {
		unsigned short held = getPadHeldForSlot(static_cast<unsigned char>(m_animStateMisc));
		if (held != 0) {
			changeStat(0, 0, 0);
		}
	}

	int weaponItem;
	int weaponRef;
	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCurrentWeaponItem(weaponItem, weaponRef);

	if ((Game.m_gameWork.m_menuStageMode == 0) &&
	    ((party.pendingWeaponItem != weaponItem) || (party.weaponItem != weaponRef))) {
		bool canImmediateSwap =
		    ((party.partyFlags & 0x80) == 0) &&
		    ((party.partyFlags & 0x40) == 0) &&
		    (party.carryObject == nullptr) &&
		    (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) &&
		    (reinterpret_cast<short*>(m_scriptHandle)[0x14] == 0) &&
		    (reinterpret_cast<short*>(m_scriptHandle)[0x11] == 0);

		if (canImmediateSwap) {
			if (weaponItem < 1) {
				LoadWeapon(-1, 0);
			} else {
				unsigned short packedItem = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + weaponItem * 0x48 + 2);
				LoadWeapon(packedItem & 0x0FFF, packedItem >> 12);
			}
			party.pendingWeaponItem = weaponItem;
			party.weaponItem = weaponRef;
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->SetCurrentWeaponIdx(weaponRef);
			party.commandFlags &= 0xDF;
		} else {
			party.pendingWeaponItem = weaponItem;
			party.weaponItem = weaponRef;
			party.commandFlags = (party.commandFlags & 0xDF) | 0x20;
			changeStat(0x0F, 0, 0);
		}
	}

	onChangePrg(2);

	if (Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
		if (party.carryObject == nullptr &&
		    *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			m_moveBaseSpeed = FLOAT_80331ad4;
		} else {
			float speedScale = FLOAT_80331a54;
			if (Game.m_gameWork.m_menuStageMode == 0) {
				speedScale = FLOAT_80331b08;
			}
			m_moveBaseSpeed = FLOAT_80331b04 * speedScale;
		}
		m_moveBaseSpeed *= m_extraMoveVec.z;
	}
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

	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
	    m_scriptHandle[0xED] != nullptr) {
		ghostPartyMog();
	} else {
		command();
		shouki();
	}

	PartyData(this).carryTarget = (CGBaseObj*)0;
	PartyData(this).secondaryTarget = (CGBaseObj*)0;
	PartyData(this).targetSearchDistance = 1000000.0f;
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
	if (isMenuPcsCommandBusy()) {
		return;
	}

	PartyObjOverlay& party = PartyData(this);
	CCaravanWork* caravan = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
	const int padSlot = static_cast<unsigned char>(m_animStateMisc);
	const unsigned short trig = getPadTrigForSlot(padSlot);
	const unsigned short held = getPadHeldForSlot(padSlot);
	bool primaryAvailable = false;
	bool secondaryAvailable = false;
	int primaryCommand = -1;
	int secondaryCommand = -1;
	int ringCommand = -1;
	int ringCommandArg = -1;

	if ((reinterpret_cast<short*>(m_scriptHandle)[7] != 0) &&
	    ((party.commandFlags & 1) != 0) &&
	    Joybus.GetCtrlMode(padSlot) != 1) {
		int cmdDir = 0;

		if ((held & 0x60) == 0x60) {
			caravan->IsUseCmdList(0);
		} else if ((trig & 0x20) != 0) {
			cmdDir = 1;
		} else if ((trig & 0x40) != 0) {
			cmdDir = -1;
		}

		if (cmdDir != 0) {
			Sound.PlaySe(0x0C, 0x40, 0x7F, 0);
			const int curCmd = caravan->GetIdxCmdList();
			caravan->IsUseCmdList(caravan->GetNextCmdListIdx(curCmd, cmdDir));
		}

		const int cmdIdx = caravan->GetIdxCmdList();
		if (cmdIdx == 0) {
			ringCommand = 1;
		} else if (cmdIdx == 1) {
			ringCommand = 9;
		} else {
			const int itemId = caravan->DelCmdListAndItem(cmdIdx, 0);
			const unsigned short itemKind = getItemKindFromCfd(itemId);
			if (itemKind == 1 || itemKind == 0xDF || itemKind == 0x100 ||
			    itemKind == 0x125 || itemKind == 0x17D || itemKind == 0x186 ||
			    itemKind == 0x1F5) {
				ringCommand = itemId | 0x8000;
			}
		}
		ringCommandArg = caravan->GetIdxCmdList();
	}

	if (((static_cast<signed char>(m_weaponNodeFlags) < 0) &&
	     (static_cast<signed char>(m_shieldAttachNodeIndex) < 0) &&
	     (static_cast<signed char>(m_weaponNodeFlags >> 8) < 0)) &&
	    Joybus.GetCtrlMode(padSlot) != 1) {
		if (caravan->m_hp == 0) {
			primaryAvailable = true;
			primaryCommand = 0x1B;
		} else if (party.secondaryTarget != nullptr) {
			primaryAvailable = true;
			primaryCommand = 0x0C;
		}

		CGObject* target = party.target;
		if (target != nullptr) {
			const int targetState = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(target) + 0x500);
			const bool alreadyCarried =
				*reinterpret_cast<CGPartyObj**>(reinterpret_cast<unsigned char*>(target) + 0x550) != nullptr;

			if (!alreadyCarried) {
				if (targetState == 0x0B || targetState == 0x0C || targetState == 0x0D ||
				    targetState == 0x0E || targetState == 0x12 || targetState == 0x13 ||
				    targetState == 0x14 || targetState == 0x15 || targetState == 0x16 ||
				    targetState == 0x17 || targetState == 0x18 || targetState == 0x1C ||
				    targetState == 0x1D || targetState == 0x1E || targetState == 0x1F ||
				    targetState == 0x20 || targetState == 0x21 || targetState == 0x24) {
					secondaryAvailable = true;
					secondaryCommand = 0x17;
				} else if (targetState == 0xC8) {
					if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&CFlat) + 0x12AC) == 0) {
						secondaryAvailable = true;
						secondaryCommand = 0x0B;
					} else {
						primaryAvailable = true;
						primaryCommand = 0x0B;
					}
				} else if (targetState == 0xC9) {
					if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&CFlat) + 0x12AC) == 0) {
						secondaryAvailable = true;
						secondaryCommand = 0x0A;
					} else {
						primaryAvailable = true;
						primaryCommand = 0x0A;
					}
				} else if (targetState == 0xCA) {
					if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&CFlat) + 0x12AC) == 0) {
						secondaryAvailable = true;
						secondaryCommand = 0x1C;
					} else {
						primaryAvailable = true;
						primaryCommand = 0x1C;
					}
				} else if (targetState == 0xCC) {
					secondaryAvailable = true;
					secondaryCommand = 6;
				} else {
					secondaryAvailable = true;
					secondaryCommand = 4;
				}
			}
		}

		if (party.carryObject != nullptr) {
			const int carryState = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.carryObject) + 0x500);
			secondaryAvailable = true;
			primaryAvailable = true;
			primaryCommand = -1;
			if (carryState == 0x0D) {
				secondaryCommand = 7;
			} else if (carryState == 0x0E) {
				secondaryCommand = 8;
			} else {
				secondaryCommand = 5;
			}
		}

		if ((party.commandFlags & 2) != 0) {
			secondaryAvailable = false;
			primaryAvailable = true;
			primaryCommand = 0x1A;
		}
		if ((party.commandFlags & 4) != 0) {
			secondaryAvailable = false;
			primaryAvailable = true;
			primaryCommand = 0x1D;
		}
		if ((party.commandFlags & 8) != 0) {
			secondaryAvailable = true;
			secondaryCommand = 0x1A;
			primaryAvailable = false;
			int cmdDir = 0;
			if ((trig & 0x20) != 0) {
				cmdDir = 1;
			} else if ((trig & 0x40) != 0) {
				cmdDir = -1;
			}
			if (cmdDir != 0) {
				Sound.PlaySe(0x0C, 0x40, 0x7F, 0);
				int& charaCommand = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Chara) + 0x2004);
				charaCommand += cmdDir;
				if (charaCommand < 0) {
					charaCommand += 5;
				} else if (charaCommand > 4) {
					charaCommand -= 5;
				}
			}
			const int charaCommand = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Chara) + 0x2004);
			ringCommand = charaCommand + 0x1E;
			ringCommandArg = charaCommand;
		}
	}

	CRingMenu* ring = getBattleRingMenuForPort(getPartyJoybusPort(this));
	if (ring != nullptr) {
		ring->SetBattleCommand(0, primaryCommand, -1);
		ring->SetBattleCommand(1, secondaryCommand, -1);
		ring->SetBattleCommand(2, ringCommand, ringCommandArg);
	}

	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != 0) {
		return;
	}

	if ((trig & 0x100) != 0) {
		if (primaryAvailable) {
			if (primaryCommand == 0x1B) {
				changeStat(0x20, 0, 0);
			}

			CGObject* scriptTarget = party.secondaryTarget != nullptr ?
				reinterpret_cast<CGObject*>(party.secondaryTarget) : party.target;
			party.commandFlags |= 0x80;

			int stack[2];
			stack[0] = primaryCommand;
			stack[1] = scriptTarget != nullptr ?
				*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(scriptTarget) + 0x30) : 0;
			SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
				&CFlat, this, 2, 0x14, 2, stack, static_cast<void*>(0));
			return;
		}

		if ((static_cast<signed char>(m_weaponNodeFlags >> 8) >= 0) ||
		    (static_cast<signed char>(m_shieldAttachNodeIndex) >= 0) ||
		    caravan->m_hp == 0 ||
		    ringCommand == -1 ||
		    ((party.commandFlags & 8) != 0)) {
			return;
		}

		const int cmdIdx = caravan->GetIdxCmdList();
		party.unk6EC = cmdIdx;
		if (cmdIdx == 0) {
			int weaponItem = 0;
			int weaponRef = 0;
			caravan->GetCurrentWeaponItem(weaponItem, weaponRef);
			if (weaponItem == cmdIdx) {
				const int equippedWeapon =
					caravan->m_equipment[0] < 0 ? 0 : caravan->m_inventoryItems[caravan->m_equipment[0]];
				if (weaponRef == equippedWeapon) {
					m_itemId = weaponRef;
					changeStat(7, 0, 0);
					return;
				}
			}

			party.pendingWeaponItem = cmdIdx;
			party.weaponItem = caravan->m_equipment[0] < 0 ? 0 : caravan->m_inventoryItems[caravan->m_equipment[0]];
			party.commandFlags = (party.commandFlags & 0xDF) | 0x20;
			changeStat(0x0F, 0, 0);
			return;
		}

		if (cmdIdx == 1) {
			const unsigned short element = reinterpret_cast<unsigned short*>(m_scriptHandle)[0xF8];
			if (element == 2) {
				changeStat(0x14, 0, 0);
			} else if (element < 2) {
				changeStat(8, 0, 0);
			} else if (element < 4) {
				changeStat(0x15, 0, 0);
			}
			return;
		}

		const int itemId = caravan->DelCmdListAndItem(cmdIdx, 0);
		const unsigned short itemKind = getItemKindFromCfd(itemId);
		if (itemKind == 1) {
			int weaponItem = 0;
			int weaponRef = 0;
			caravan->GetCurrentWeaponItem(weaponItem, weaponRef);
			if (weaponItem == cmdIdx && weaponRef == itemId) {
				m_itemId = itemId;
				changeStat(7, 0, 0);
				return;
			}
			party.pendingWeaponItem = cmdIdx;
			party.weaponItem = itemId;
			party.commandFlags = (party.commandFlags & 0xDF) | 0x20;
			changeStat(0x0F, 0, 0);
			return;
		}

		if (itemKind == 0x125) {
			m_itemId = 0x220;
			changeStat(2, 0, 2);
			return;
		}
		if (itemKind == 0xDF || itemKind == 0x100) {
			m_itemId = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 10);
			changeStat(2, 0, 0);
			return;
		}
		if (itemKind == 0x17D || itemKind == 0x186) {
			if (useItem(itemId), canPlayerUseItem() != 0) {
				caravan->GetNumCombi(party.unk6EC, 1);
			}
			return;
		}
		if (itemKind == 0x1F5) {
			m_itemId = itemId;
			changeStat(2, 0, 0);
			return;
		}
	}

	if ((trig & 0x200) == 0 || !secondaryAvailable) {
		return;
	}

	if ((static_cast<signed char>(m_weaponNodeFlags >> 8) < 0) &&
	    (static_cast<signed char>(m_shieldAttachNodeIndex) < 0) &&
	    caravan->m_hp != 0 &&
	    ringCommand != -1 &&
	    secondaryCommand == 6) {
		int weaponItem = 0;
		int weaponRef = 0;
		caravan->GetCurrentWeaponItem(weaponItem, weaponRef);
		m_itemId = weaponRef;
		changeStat(1, 0, 0);
		commandFinished();
		return;
	}

	if (secondaryCommand == 4) {
		carry(0, party.target, 0);
		commandFinished();
		return;
	}

	if ((secondaryCommand >= 2 && secondaryCommand <= 3) || secondaryCommand == 0x17) {
		rotTarget(reinterpret_cast<CGPrgObj*>(party.target));
		changeStat(0x0E, 0, 0);
		*reinterpret_cast<CGPartyObj**>(reinterpret_cast<unsigned char*>(party.target) + 0x550) = this;
		reinterpret_cast<CGPrgObj*>(party.target)->changeStat(0x0E, 0, 0);
		commandFinished();
		return;
	}

	callCommandScript(secondaryCommand, party.target);
	commandFinished();
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
	if (m_scriptHandle == nullptr) {
		return;
	}

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	int* shoukiMode = reinterpret_cast<int*>(self + 0x688);

	bool canShouki = (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) &&
	                 ((self[0x6B8] & 0x20) == 0) &&
	                 ((static_cast<unsigned char>(m_weaponNodeFlags >> 8) & 0x40) == 0);

	if (!canShouki || Game.unk_flat3_0xc7d0 == 0) {
		if (*shoukiMode != 0) {
			deletePSlotBit(0x200);
			*shoukiMode = 0;
		}
		return;
	}

	const Vec* chalicePos = reinterpret_cast<Vec*>(Game.unk_flat3_0xc7d0 + 0x15C);
	float chaliceDist = PSVECDistance(&m_worldPosition, chalicePos);
	if (chaliceDist > FLOAT_80331b00 * Game.unkFloat_0xca10) {
		*shoukiMode = 2;
	} else if (chaliceDist < FLOAT_80331a74 * Game.unkFloat_0xca10) {
		*shoukiMode = 0;
	} else {
		*shoukiMode = 1;
	}

	if (*shoukiMode == 0) {
		if ((Game.m_gameWork.m_frameCounter % 30) == 0) {
			addHp(1, static_cast<CGPrgObj*>(0));
		}
	} else if (*shoukiMode == 2) {
		if ((Game.m_gameWork.m_frameCounter % 30) == 0) {
			addHp(-1, static_cast<CGPrgObj*>(0));
		}
	}
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

	switch (m_lastStateId) {
	case 0:
		statAlive();
		break;
	case 2:
		onStatMagic();
		break;
	case 6:
		statCharge();
		break;
	case 7:
		statAttackSel();
		break;
	case 0x0B:
		statCarry();
		break;
	case 0x0C:
		statPickup();
		break;
	case 0x0D:
	case 0x1B:
		statPut();
		break;
	case 0x0E:
		statRebound();
		break;
	case 0x14:
		statHide();
		break;
	case 0x15:
		statJump();
		break;
	case 0x0F:
		statWeaponChange();
		break;
	default:
		break;
	}

	if (m_lastStateId == 2 || m_lastStateId == 6) {
		moveCenterTargetParticle();
		checkTargetParticle();
	}

	shouki();
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (m_subState == 0) {
		if (m_subFrame == 0) {
			reqAnim(0x10, 0, 0);
			putTargetParticle(0, 1);
			*reinterpret_cast<int*>(self + 0x664) = 0;
		}

		moveCenterTargetParticle();
		checkTargetParticle();

		if (isLoopAnim() != 0) {
			changeSubStat(1);
		}
		return;
	}

	if (m_subState == 1) {
		if (m_subFrame == 0) {
			reqAnim(0x11, 0, 0);
			*reinterpret_cast<int*>(self + 0x664) = 0;
		}

		moveCenterTargetParticle();
		checkTargetParticle();

		*reinterpret_cast<int*>(self + 0x664) = *reinterpret_cast<int*>(self + 0x664) + 1;
		if (m_subFrame == 0x0C) {
			putParticle(0x577, 0, this, 0.0f, 0x80D);
		} else if (m_subFrame == 0x12) {
			putParticle(0x578, 0, this, 0.0f, 0x80D);
		}

		unsigned short held = getPadHeldForSlot(static_cast<unsigned char>(m_animStateMisc));
		if ((held & 0x100) == 0 || m_subFrame > 0x20) {
			changeSubStat(2);
		}
		return;
	}

	if (m_subState == 2) {
		if (m_subFrame == 0) {
			endPSlotBit(0x10);
			endPSlotBit(0x100);
			reqAnim(0x12, 0, 0);
		}

		moveCenterTargetParticle();
		checkTargetParticle();
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
		}
		return;
	}

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
CGPrgObj* CGPartyObj::getBestAngleObject(float, float)
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

	return best;
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
	PartyObjOverlay& party = PartyData(this);

	if (chargeType == 0) {
		if (m_stateFrame != 0) {
			return;
		}

		party.unk6CC = party.attackSel;
		party.attackSel = 0;
		party.commandFlags &= 0x7F;
		party.commandFlags &= 0xBF;

		CGPrgObj* target = getBestAngleObject(FLOAT_80331ad4 * m_bodyEllipsoidRadius, FLOAT_80331ad8);
		if (target != 0) {
			m_rotTargetY = atan2(target->m_worldPosition.x - m_worldPosition.x,
			                     target->m_worldPosition.z - m_worldPosition.z);
		}
		return;
	}

	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	const int chain = party.unk6CC;
	unsigned char* attackEntry = reinterpret_cast<unsigned char*>(
	    Game.unk_flat3_field_30_0xc7e0 +
	    ((*reinterpret_cast<unsigned short*>(script + 0x3E2) +
	      *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2) *
	         0x1CA) +
	    chain * 0x12);

	const unsigned short stepStart = *reinterpret_cast<unsigned short*>(attackEntry + 4);
	const unsigned short stepEnd = *reinterpret_cast<unsigned short*>(attackEntry + 6);
	if (chain > 0 && m_stateFrame == stepStart && Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
		const float stepSpeed = FLOAT_80331ADC * static_cast<float>(*reinterpret_cast<unsigned short*>(attackEntry + 8));
		moveVectorRot(m_rotTargetY, FLOAT_80331a78, stepSpeed, (stepEnd - stepStart) + 1);
	}

	const unsigned short comboStart = *reinterpret_cast<unsigned short*>(attackEntry + 0x0C);
	const unsigned short comboEnd = *reinterpret_cast<unsigned short*>(attackEntry + 0x0E);
	if (m_stateFrame < comboStart || comboEnd < m_stateFrame) {
		if ((getPadTrigForSlot(static_cast<unsigned char>(m_animStateMisc)) & 0x100) != 0) {
			party.commandFlags = (party.commandFlags & 0xBF) | 0x40;
		}
	} else {
		if ((getPadTrigForSlot(static_cast<unsigned char>(m_animStateMisc)) & 0x100) != 0) {
			party.commandFlags = (party.commandFlags & 0x7F) | 0x80;
		}
	}

	if (m_stateFrame == *reinterpret_cast<unsigned short*>(attackEntry + 0x10)) {
		if ((party.commandFlags & 0x80) != 0 && (party.commandFlags & 0x40) == 0 && chain < 2) {
			party.attackSel = chain + 1;
			changeStat(1, 0, 0);
			return;
		}
	}

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (m_stateFrame == *reinterpret_cast<int*>(self + 0x638)) {
		self[0x63C] = (self[0x63C] & 0x7F) | 0x80;
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

		Vec rayDir = {
		    sinf(m_rotationY) * FLOAT_80331aa0,
		    FLOAT_80331a78,
		    cosf(m_rotationY) * FLOAT_80331aa0,
		};
		Vec startPos = m_worldPosition;
		startPos.y += FLOAT_80331ad0;

		CMapCylinder hitCylinder;
		hitCylinder.m_bottom = startPos;
		hitCylinder.m_direction = rayDir;
		hitCylinder.m_radius = FLOAT_80331a78;
		hitCylinder.m_height = FLOAT_80331aa0;
		hitCylinder.m_top.x = FLOAT_80331a9c;
		hitCylinder.m_top.y = FLOAT_80331a9c;
		hitCylinder.m_top.z = FLOAT_80331a9c;
		hitCylinder.m_direction2.x = FLOAT_80331aa0;
		hitCylinder.m_direction2.y = FLOAT_80331aa0;
		hitCylinder.m_direction2.z = FLOAT_80331aa0;

		Vec hitPos = startPos;
		if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &hitCylinder, &rayDir, 0x30) != 0) {
			void* hitObj = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MapMng) + 0x22A88);
			CalcHitPosition__7CMapObjFP3Vec(hitObj, &hitPos);
			GetHitFaceNormal__7CMapObjFP3Vec(hitObj, reinterpret_cast<Vec*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBB8));
		} else {
			PSVECAdd(&startPos, &rayDir, &hitPos);
		}

		*reinterpret_cast<Vec*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBAC) = hitPos;
		*reinterpret_cast<Vec*>(self + 0x66C) = hitPos;
		*reinterpret_cast<Vec*>(self + 0x678) = hitPos;
	}

	endPSlotBit(0x10);
	putParticle(0x147 + ((targetSide != 0) ? 4 : 0), 0, this, 0.0f, 0);
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if ((m_lastStateId == 2 || m_lastStateId == 6) &&
	    (*reinterpret_cast<int*>(self + 0x668) != 0)) {
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if ((m_lastStateId == 2 || m_lastStateId == 6) &&
	    (*reinterpret_cast<int*>(self + 0x668) != 0) &&
	    ((PartyData(this).partyFlags & 0x80) != 0)) {
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

	Vec input;
	input.x = 0.0f;
	input.y = 0.0f;
	input.z = 0.0f;

	if (!isGhostPartyTargetMode(this)) {
		if ((*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&MiniGamePcs) + 0x6484) & 0x100) != 0) {
			input.x -= getPadAxisForSlot(static_cast<unsigned char>(m_animStateMisc), 0x24);
			input.z += getPadAxisForSlot(static_cast<unsigned char>(m_animStateMisc), 0x28);
		}

		if (input.x == 0.0f && input.z == 0.0f) {
			unsigned short held = getPadHeldForSlot(static_cast<unsigned char>(m_animStateMisc));
			if ((held & 1) != 0) {
				input.x += FLOAT_80331a54;
			}
			if ((held & 2) != 0) {
				input.x -= FLOAT_80331a54;
			}
			if ((held & 8) != 0) {
				input.z += FLOAT_80331a54;
			}
			if ((held & 4) != 0) {
				input.z -= FLOAT_80331a54;
			}
		}
	} else {
		CGPartyObj* leader = Game.m_partyObjArr[0];
		if (leader != nullptr &&
		    (leader->m_lastStateId == 2 || leader->m_lastStateId == 6) &&
		    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x668) != 0) {
			Vec toLeaderTarget;
			PSVECSubtract(reinterpret_cast<Vec*>(reinterpret_cast<unsigned char*>(leader) + 0x66C),
			              reinterpret_cast<Vec*>(self + 0x66C), &toLeaderTarget);
			toLeaderTarget.y = 0.0f;
			if (PSVECMag(&toLeaderTarget) > 0.001f) {
				input.x = toLeaderTarget.x;
				input.z = toLeaderTarget.z;
			}
		}
	}

	if (input.x == 0.0f && input.z == 0.0f) {
		self[0x6B8] &= 0xDF;
	} else {
		Vec* targetPos = reinterpret_cast<Vec*>(self + 0x66C);
		Vec* centerPos = reinterpret_cast<Vec*>(self + 0x678);
		Vec move;
		Vec fromCenter;
		float maxRange;

		self[0x6B8] |= 0x20;
		PSVECNormalize(&input, &input);
		PSVECScale(&input, &input, FLOAT_80331ad4);

		float angle = CameraPcs._248_4_;
		if (isGhostPartyTargetMode(this)) {
			angle = 0.0f;
		}

		float s = sin(angle);
		float c = cos(angle);
		targetPos->x += input.x * c - input.z * s;
		targetPos->z += input.x * s + input.z * c;

		maxRange = 0.0f;
		if (Game.unkCFlatData0[2] != 0) {
			int itemId = *reinterpret_cast<int*>(self + 0x560);
			maxRange += static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 0x30));
		}
		if (m_scriptHandle != nullptr) {
			unsigned char* work = reinterpret_cast<unsigned char*>(m_scriptHandle);
			if (*reinterpret_cast<int*>(self + 0x520) == 2) {
				maxRange += static_cast<float>(*reinterpret_cast<unsigned short*>(work + 0x19A));
				if ((*reinterpret_cast<unsigned int*>(work + 0x3B0) & 0x4000) != 0 && Game.unk_flat3_field_8_0xc7dc != 0) {
					maxRange += static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x0A));
				}
			} else {
				maxRange += static_cast<float>(*reinterpret_cast<unsigned short*>(work + 0x19C));
				if ((*reinterpret_cast<unsigned int*>(work + 0x3B0) & 0x8000) != 0 && Game.unk_flat3_field_8_0xc7dc != 0) {
					maxRange += static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x0C));
				}
			}
		}
		maxRange = FLOAT_80331a78 + maxRange;

		PSVECSubtract(targetPos, &m_worldPosition, &fromCenter);
		float dist = PSVECMag(&fromCenter);
		if (dist > maxRange && dist > 0.001f) {
			PSVECScale(&fromCenter, &fromCenter, maxRange / dist);
			PSVECAdd(&m_worldPosition, &fromCenter, targetPos);
		}

		PSVECSubtract(targetPos, centerPos, &move);
		for (int i = 0; i < 4; i++) {
			Vec bottom;
			Vec up = {0.0f, FLOAT_80331ad0, 0.0f};
			CMapCylinder hitCylinder;

			PSVECAdd(centerPos, &up, &bottom);
			hitCylinder.m_bottom = bottom;
			hitCylinder.m_direction = move;
			hitCylinder.m_radius = FLOAT_80331a9c;
			hitCylinder.m_height = FLOAT_80331aa0;
			hitCylinder.m_top.x = FLOAT_80331a9c;
			hitCylinder.m_top.y = FLOAT_80331a9c;
			hitCylinder.m_top.z = FLOAT_80331a9c;
			hitCylinder.m_direction2.x = FLOAT_80331aa0;
			hitCylinder.m_direction2.y = FLOAT_80331aa0;
			hitCylinder.m_direction2.z = FLOAT_80331aa0;

			if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &hitCylinder, &move, 0x30) == 0) {
				break;
			}
			if (i == 3) {
				move.x = 0.0f;
				move.y = 0.0f;
				move.z = 0.0f;
			} else {
				CalcHitSlide__7CMapObjFP3Vecf(getMapHitObject(), &move);
			}
		}

		PSVECAdd(centerPos, &move, targetPos);

		Vec down = {0.0f, FLOAT_80331acc, 0.0f};
		CMapCylinder floorCylinder;
		floorCylinder.m_bottom = *targetPos;
		floorCylinder.m_direction = down;
		floorCylinder.m_radius = FLOAT_80331a78;
		floorCylinder.m_height = FLOAT_80331aa0;
		floorCylinder.m_top.x = FLOAT_80331a9c;
		floorCylinder.m_top.y = FLOAT_80331a9c;
		floorCylinder.m_top.z = FLOAT_80331a9c;
		floorCylinder.m_direction2.x = FLOAT_80331aa0;
		floorCylinder.m_direction2.y = FLOAT_80331aa0;
		floorCylinder.m_direction2.z = FLOAT_80331aa0;

		if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &floorCylinder, &down, 0x30) != 0) {
			CalcHitPosition__7CMapObjFP3Vec(getMapHitObject(), targetPos);
			if (m_scriptHandle != nullptr) {
				unsigned char* work = reinterpret_cast<unsigned char*>(m_scriptHandle);
				*reinterpret_cast<Vec*>(work + 0xBAC) = *targetPos;
				GetHitFaceNormal__7CMapObjFP3Vec(getMapHitObject(), reinterpret_cast<Vec*>(work + 0xBB8));
			}
		}

		*centerPos = *targetPos;
	}

	Vec delta;
	PSVECSubtract(reinterpret_cast<Vec*>(self + 0x66C), &m_worldPosition, &delta);
	if (PSVECMag(&delta) > 0.0f) {
		m_rotationY = atan2(delta.x, delta.z);
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (m_subState == 0) {
		if (m_subFrame == 0) {
			putTargetParticle(0, 1);
			*reinterpret_cast<int*>(self + 0x664) = 0;
		}
	} else if (m_subState == 1 && m_subFrame == 0) {
		endPSlotBit(0x10);
		endPSlotBit(0x100);
		*reinterpret_cast<int*>(self + 0x664) = 0;
	}

	moveCenterTargetParticle();
	checkTargetParticle();

	int magicId = *reinterpret_cast<int*>(self + 0x560);
	if (m_subState == 1 && m_subFrame == 0) {
		if (magicId != 0x103) {
			putParticleFromItem(magicId, 0, 0, &m_worldPosition);
			putParticleFromItem(magicId, 1, 0, (Vec*)0);
		}
	}

	if (m_subState == 1 && m_subFrame > 0x11) {
		self[0x6C4] |= 0x80;
	}

	unsigned short held = getPadHeldForSlot(static_cast<unsigned char>(m_animStateMisc));
	if ((held & 0x100) == 0 && m_subState < 2) {
		changeStat(0, 0, 0);
		return;
	}

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
			if ((PartyData(this).partyFlags & 0x04) != 0) {
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
	onPush__9CGBaseObjFP9CGBaseObji(this, other, pushType);
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
		PartyData(this).secondaryTarget = other;
		return;
	}

	float dist = PSVECDistance(&m_worldPosition, &targetObj->m_worldPosition);
	float* bestDist = &PartyData(this).targetSearchDistance;
	if (dist < *bestDist) {
		PartyData(this).carryTarget = other;
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
	PartyData(this).partyFlags &= 0x7F;
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
		carry(0, reinterpret_cast<CGObject*>(PartyData(this).carryTarget), 1);
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
	if (source != nullptr && (source->GetCID() & 0x2D) != 0x2D) {
		return;
	}

	unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
	if (script == nullptr) {
		return;
	}

	unsigned int bonusSlot = script[0xBA4];
	unsigned int addValue = 0;
	unsigned int subValue = 0;
	unsigned short currentAdd = *reinterpret_cast<unsigned short*>(script + 0xBCA);
	unsigned short currentSub = *reinterpret_cast<unsigned short*>(script + 0xBCC);
	int stageEntry = Game.m_bossArtifactBase + Game.m_gameWork.m_bossArtifactStageIndex * 0x168 + bonusSlot * 8;
	unsigned int stageAdd = *reinterpret_cast<unsigned short*>(stageEntry + 0x66);
	unsigned int stageSub = *reinterpret_cast<unsigned short*>(stageEntry + 0x68);

	if (kind == 0) {
		unsigned short count = *reinterpret_cast<unsigned short*>(script + 0xBC8);
		Printf__7CSystemFPce(&System, s_partyBonusKind0Fmt, count + 1);
		*reinterpret_cast<unsigned short*>(script + 0xBC8) = count + 1;
	}
	if (kind == 1) {
		unsigned short count = *reinterpret_cast<unsigned short*>(script + 0xBC4);
		Printf__7CSystemFPce(&System, s_partyBonusKind1Fmt, count + 1);
		*reinterpret_cast<unsigned short*>(script + 0xBC4) = count + 1;
	}
	if (kind == 4) {
		unsigned short count = *reinterpret_cast<unsigned short*>(script + 0xBC6);
		Printf__7CSystemFPce(&System, s_partyBonusKind4Fmt, count + 1);
		*reinterpret_cast<unsigned short*>(script + 0xBC6) = count + 1;
	}

	switch (bonusSlot) {
	default:
		break;
	case 0:
		if (kind == 2 && (System.m_frameCounter % 30) == 0) {
			addValue = stageAdd;
		}
		break;
	case 1:
		if (kind == 3) {
			addValue = stageAdd;
		}
		break;
	case 2:
	case 4:
	case 6:
		if (kind == 4) {
			unsigned short item = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + value * 0x48);
			if ((bonusSlot == 4 && item == 0x100) || (bonusSlot == 6 && item == 400)) {
				addValue = stageAdd;
			} else if (bonusSlot == 2) {
				switch (item) {
				case 0x9F:
				case 0xB6:
				case 0xCC:
				case 0xDB:
				case 0xDF:
				case 0xE4:
				case 0x100:
				case 0x125:
				case 0x126:
				case 0x127:
				case 0x12A:
				case 0x17D:
				case 0x186:
				case 0x191:
					addValue = stageAdd;
					break;
				default:
					break;
				}
			}
		}
		break;
	case 3:
	case 0xE:
		if (kind == 5) {
			short item = *reinterpret_cast<short*>(Game.unkCFlatData0[2] + value * 0x48);
			if ((bonusSlot == 0xE && (item == 0x17D || item == 0x186)) ||
			    (bonusSlot == 3 && item != 0x17D && item != 0x186)) {
				addValue = stageAdd;
			}
		}
		break;
	case 7:
		if (kind == 10) {
			addValue = stageAdd;
		}
		break;
	case 8:
		if (kind == 0x0B) {
			addValue = stageAdd;
		}
		break;
	case 9:
		if (kind == 0x0C) {
			addValue = stageAdd;
		}
		break;
	case 10:
		if ((unsigned int)(kind - 0x12) < 3 || kind == 0x15) {
			subValue = stageSub;
		}
		if (kind == 0x17) {
			addValue = stageAdd;
		}
		break;
	case 0x0B:
		if ((unsigned int)(kind - 0x0E) < 3 || kind == 0x11) {
			addValue = stageAdd;
		}
		break;
	case 0x0C:
		if ((unsigned int)(kind - 0x12) < 3 || kind == 0x15) {
			subValue = stageSub;
		}
		break;
	case 0x0D:
		if (kind == 0x12) {
			unsigned short item = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + value * 0x48 + 8);
			if (item == 0x24 || item == 0x25 || item == 0x69 || item == 0x6A) {
				addValue = stageAdd;
			}
		}
		break;
	case 0x0F:
		if (kind == 9) {
			subValue = stageSub;
		}
		break;
	case 0x10:
		if (kind == 0x18) {
			subValue = stageSub;
		}
		break;
	case 0x11:
		if (kind == 0x19) {
			subValue = stageSub;
		}
		break;
	case 0x12:
	case 0x13:
		if (kind == 0x16 &&
		    ((bonusSlot == 0x12 && source == this) || (bonusSlot == 0x13 && source != this))) {
			subValue = stageSub;
		}
		break;
	case 0x14:
		if (kind == 4) {
			subValue = stageSub;
		}
		break;
	case 0x15:
		Printf__7CSystemFPce(&System, s_partyBonusUnknownFmt);
		break;
	case 0x16:
		if (kind == 0x14) {
			addValue = stageAdd;
		}
		break;
	case 0x17:
		if (kind == 1 && source != nullptr && source->m_scriptHandle != nullptr && source->m_scriptHandle[9] != nullptr &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(source->m_scriptHandle[9]) + 0xFE) & 4) != 0) {
			addValue = stageAdd;
		}
		break;
	case 0x18:
		if (kind == 1) {
			subValue = stageSub;
		}
		break;
	}

	if (addValue != 0) {
		unsigned int total = currentAdd + addValue;
		if (total > 100) {
			total = 100;
		}
		if (bonusSlot != 0) {
			Printf__7CSystemFPce(&System, s_partyBonusAddFmt, bonusSlot, total);
		}
		*reinterpret_cast<unsigned short*>(script + 0xBCA) = static_cast<unsigned short>(total);
	}

	if (subValue != 0) {
		int total = static_cast<int>(currentSub) - static_cast<int>(subValue);
		if (total < 0) {
			total = 0;
		} else if (total > 100) {
			total = 100;
		}
		Printf__7CSystemFPce(&System, s_partyBonusSubFmt, bonusSlot, total);
		*reinterpret_cast<unsigned short*>(script + 0xBCC) = static_cast<unsigned short>(total);
	}
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
		PartyData(this).weaponItem = itemId;
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
		if (Game.m_gameWork.m_menuStageMode != 0 && CanCreateFromScript__9CGItemObjFv() == 0) {
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

	int itemId = PartyData(this).weaponItem;
	void* created = CreateFromScript__9CGItemObjFiiiP8CGObjectfPQ29CGItemObj4CCFS(
	    0, 9, itemId, this, FLOAT_80331a78, nullptr);
	if (created == nullptr) {
		return;
	}

	*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(created) + 0x562) =
	    static_cast<short>(reinterpret_cast<int>(m_scriptHandle[0xED]));
	if (Game.m_gameWork.m_menuStageMode == 0) {
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
	if (Game.m_gameWork.m_menuStageMode == 0) {
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
	Game.m_gameWork.m_gameOverFlag = 1;
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.m_partyObjArr[i];
		if (party == nullptr) {
			continue;
		}

		int keepGameOver = 0;
		if ((Game.m_gameWork.m_menuStageMode != 0) && (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F)) {
			unsigned int status = (*(unsigned int(**)(CGPartyObj*))(*(unsigned char**)((unsigned char*)party + 0x48) + 0xC))(party);
			if (((status & 0x6D) == 0x6D) &&
			    (*(int*)(*(unsigned char**)((unsigned char*)party + 0x58) + 0x3B4) != 0)) {
				keepGameOver = 1;
			}
		}

		if ((keepGameOver != 0) ||
		    ((*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(party->m_scriptHandle) + 0x1C) == 0) &&
		     ((*(reinterpret_cast<unsigned char*>(party) + 0x6B8) & 0x04) == 0))) {
			continue;
		}

		Game.m_gameWork.m_gameOverFlag = 0;
		return;
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
	int bonusCount = 0x10;
	if (Game.m_gameWork.m_radarType != 0) {
		bonusCount = 4;
	}

	Printf__7CSystemFPce(&System, s_partyBonusCountFmt, bonusCount);

	int chosenBonus[5] = {};
	int chosenCount = 0;
	int stageBase = Game.m_bossArtifactBase + Game.m_gameWork.m_bossArtifactStageIndex * 0x168;

	for (int slot = 0; slot < 4; slot++) {
		CGPartyObj* party = Game.m_partyObjArr[slot];
		if (party == nullptr) {
			continue;
		}

		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(party->m_scriptHandle);
		if (useRandom == 0) {
			int bonus = bonus0;
			switch (slot) {
			case 1:
				bonus = bonus1;
				break;
			case 2:
				bonus = bonus2;
				break;
			case 3:
				bonus = bonus3;
				break;
			default:
				break;
			}

			caravanWork->SetBonusCondition(bonus);
			if ((unsigned int)System.m_execParam > 2) {
				Printf__7CSystemFPce(&System, s_partyBonusFixedFmt, slot, bonus);
			}
		} else {
			int bonusIndex;
			for (;;) {
				bonusIndex = Math.Rand(bonusCount);

				int duplicateIndex = 0;
				while (duplicateIndex < chosenCount) {
					if (chosenBonus[duplicateIndex] == bonusIndex) {
						break;
					}
					duplicateIndex++;
				}

				if (duplicateIndex == chosenCount) {
					break;
				}
			}

			chosenBonus[chosenCount] = bonusIndex;
			chosenCount++;

			int bonus = *reinterpret_cast<unsigned short*>(stageBase + bonusIndex * 2);
			caravanWork->SetBonusCondition(bonus);
			if ((unsigned int)System.m_execParam > 2) {
				Printf__7CSystemFPce(&System, s_partyBonusRandomFmt, slot, bonusIndex, bonus);
			}
		}

		caravanWork->CalcStatus();
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
	if ((Game.m_gameWork.m_menuStageMode != 0) &&
	    (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F) &&
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
bool CGPartyObj::IsDispRader()
{
	if (CGObject::IsDispRader()) {
		if (((int)((unsigned int)(unsigned char)m_weaponNodeFlags << 24) < 0) &&
		    ((int)((unsigned int)(unsigned char)(m_weaponNodeFlags >> 8) << 24) < 0)) {
			return true;
		}
	}
	return false;
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
	PartyData(this).weaponRef = weaponRef;
	PartyData(this).weaponItem = weaponItem;
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (*reinterpret_cast<short*>(self + 0x6F4) == mode) {
		return;
	}

	ChangeCommandMode(mode);
	changeStat(0, 0, 0);
	setIdleMotion();
	CancelAnim(1);

	if (m_scriptHandle != nullptr && (self[0x6B8] & 0x04) != 0) {
		if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
			addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
		}
		self[0x6B8] &= 0xFB;
	}

	if (m_scriptHandle != nullptr) {
		endPSlotBit(0x10000);
		if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
			*reinterpret_cast<float*>(self + 0x694) = 1.0f;
			m_bgColMask &= 0xFFFEFFF1;
		} else {
			*reinterpret_cast<float*>(self + 0x694) = 0.5f;
			m_bgColMask |= 0x1000E;
		}
	}

	setIdleMotion();

	if (m_scriptHandle != nullptr &&
	    mode == 1 &&
	    *reinterpret_cast<int*>(self + 0x6F0) == 0 &&
	    *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		self[0x6B8] = (self[0x6B8] & 0xFD) | 0x02;
	}
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
	if (PartyData(this).carryObject == 0) {
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	unsigned char* work = reinterpret_cast<unsigned char*>(m_scriptHandle);
	PartyObjOverlay& party = PartyData(this);

	if ((party.partyFlags & 0x04) != 0) {
		if (*reinterpret_cast<short*>(work + 0x1C) == 0) {
			addHp(*reinterpret_cast<unsigned short*>(work + 0x1A), static_cast<CGPrgObj*>(0));
		}
		party.partyFlags &= 0xFB;
	}

	enableDamageCol(1);

	if (party.carryObject == 0) {
		if (*reinterpret_cast<short*>(work + 0x1C) == 0) {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		} else {
			if (m_lastMapIdHit == 1 && m_lastMapIdExtra == 0) {
				SetAnimSlot(0, 0);
				SetAnimSlot(1, 1);
			} else {
				SetAnimSlot(0x25, 0);
				SetAnimSlot(0x30, 1);
			}
		}
	} else if (*reinterpret_cast<int*>(CFlat + 0x4780) == 0) {
		if (m_lastMapIdHit == 1 && m_lastMapIdExtra == 0) {
			SetAnimSlot(0x0B, 0);
			SetAnimSlot(0x0C, 1);
		} else {
			SetAnimSlot(0x0B, 0);
			SetAnimSlot(2, 1);
		}
	} else {
		SetAnimSlot(0x0B, 0);
		SetAnimSlot(0x0C, 1);
	}

	if (restoreDamageCol == 0) {
		if (m_currentAnimSlot == 6) {
			reqAnim(0x26, 0, 0);
		} else {
			reqAnim(0x27, 0, 0);
		}
	}

	if (*reinterpret_cast<short*>(work + 0x1C) == 0) {
		*reinterpret_cast<float*>(self + 0x694) = 1.0f;
		m_bgColMask &= 0xFFFEFFF1;

		if (restoreDamageCol == 0 || keepTarget != 0) {
			endPSlotBit(0x10000);
			putParticle((reinterpret_cast<int>(m_scriptHandle[0xED]) + 3) | 0x100,
			            *reinterpret_cast<int*>(self + 0x5A4), this, FLOAT_80331a54, 0);
		}

		if (restoreDamageCol == 0) {
			playSe3D(0x2D, 0x32, 0x96, 0, 0);
		}
	} else {
		endPSlotBit(0x10000);
		*reinterpret_cast<float*>(self + 0x694) = FLOAT_80331a54;
		m_bgColMask |= 0x1000E;
		if (restoreDamageCol == 0) {
			*reinterpret_cast<unsigned short*>(work + 0x12) = 0x5A;
		}
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
void CGPartyObj::PutMemoryCapsule(int arg0, int arg1, int arg2, int arg3, char* arg4)
{
	int args[5];
	args[0] = arg0;
	args[1] = arg1;
	args[2] = arg2;
	args[3] = arg3;
	args[4] = reinterpret_cast<int>(arg4);
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
		PartyData(this).partyFlags |= 0x20;
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
 * PAL Address: UNUSED
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void stageWeather()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->canPlayerGoMenu();
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void magicReady()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->ChangeCommandMode(2);
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void chooseMagic()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->useItem(-1);
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void decMagic(int amount)
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.m_partyObjArr[i];
		if (party != nullptr && party->m_scriptHandle != nullptr) {
			party->bonus(0, -amount, (CGPrgObj*)0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void calcWeightMax()
{
	for (int i = 0; i < 4; i++) {
		CGPartyObj* party = Game.m_partyObjArr[i];
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
	Vec* outVec = &m_targetDelta;
	float* outDist = &m_targetDist;

	if (sGhostPartyWork.activeTrailCount > 0) {
		Vec prev = m_worldPosition;
		float worldLen = 0.0f;
		float flatLen = 0.0f;
		bool capturedCurrent = false;

		*outDist = 0.0f;
		for (int i = 0; i < sGhostPartyWork.activeTrailCount && i < 5; i++) {
			Vec* nextPos = (i == sGhostPartyWork.trailIndex) ? &m_worldPosition : &sGhostPartyWork.trail[i];

			Vec delta;
			PSVECSubtract(nextPos, &prev, &delta);
			worldLen += PSVECMag(&delta);

			delta.y = 0.0f;
			flatLen += PSVECMag(&delta);

			if (!capturedCurrent && i == sGhostPartyWork.trailIndex) {
				capturedCurrent = true;
				*outVec = delta;
				if (PSVECMag(&delta) < m_moveBaseSpeed) {
					sGhostPartyWork.trailIndex++;
				}
			}

			prev = *nextPos;
		}

		*outDist = (flatLen < worldLen) ? flatLen : worldLen;
		if (*outDist > 0.01f) {
			return;
		}
	}

	sGhostPartyWork.activeTrailCount = 0;
	*outVec = m_targetDelta;
	outVec->y = 0.0f;

	float dist = PSVECMag(outVec);
	float maxDist = m_targetDist;
	*outDist = (dist < maxDist) ? dist : maxDist;
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
	CGPartyObj* leader = Game.m_partyObjArr[0];
	if (leader == nullptr) {
		return;
	}

	for (int i = 0; i < 5; i++) {
		Vec* basePos = (i == 0) ? &m_worldPosition : &sGhostPartyWork.trail[i];

		Vec moveVec;
		PSVECSubtract(&leader->m_worldPosition, basePos, &moveVec);

		CMapCylinder col;
		col.m_bottom = *basePos;
		col.m_bottom.y += FLOAT_80331aa0;
		col.m_direction = moveVec;
		col.m_radius = m_bodyEllipsoidRadius;
		col.m_height = m_bodyEllipsoidRadius;
		col.m_top.x = FLOAT_80331a9c;
		col.m_top.y = FLOAT_80331a9c;
		col.m_top.z = FLOAT_80331a9c;
		col.m_direction2.x = FLOAT_80331aa0;
		col.m_direction2.y = FLOAT_80331aa0;
		col.m_direction2.z = FLOAT_80331aa0;

		if (CheckHitCylinderNear__7CMapMngFP12CMapCylinderP3VecUl(&MapMng, &col, &moveVec, m_attrFlags & ~0x10U) == 0) {
			sGhostPartyWork.activeTrailCount = i + 1;
			sGhostPartyWork.leaderTrail[i] = leader->m_worldPosition;
			break;
		}

		int nextCount = i + 1;
		if (sGhostPartyWork.activeTrailCount == 0 || sGhostPartyWork.activeTrailCount > nextCount) {
			sGhostPartyWork.activeTrailCount = nextCount;
		}
	}

	if (sGhostPartyWork.activeTrailCount <= 0) {
		sGhostPartyWork.trailIndex = 0;
	} else if (sGhostPartyWork.trailIndex >= sGhostPartyWork.activeTrailCount) {
		sGhostPartyWork.trailIndex = sGhostPartyWork.activeTrailCount - 1;
	}
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
	CGPartyObj* leader = Game.m_partyObjArr[0];
	if (leader == nullptr) {
		return;
	}

	gpmCol();
	gpmMove();

	int stageMode = 0;
	switch (Game.m_gameWork.m_bossArtifactStageIndex) {
	case 4:
	case 8:
	case 9:
	case 0x0B:
	case 0x0C:
	case 0x0D:
		stageMode = 2;
		break;
	case 6:
	case 10:
		stageMode = 1;
		break;
	default:
		stageMode = 0;
		break;
	}

	float frameRatio = (float)(Game.m_gameWork.m_frameCounter % 100) / 100.0f;
	float pressureScale = 1.0f;
	if (stageMode == 2) {
		pressureScale = 0.5f + (frameRatio * 0.5f);
	} else if (stageMode == 1) {
		pressureScale = 0.5f + ((1.0f - frameRatio) * 0.5f);
	}

	int targetPressure = (int)(100.0f * pressureScale);
	float leaderDist = m_targetDist;
	if (leaderDist > Game.unkFloat_0xca10) {
		sGhostPartyWork.mood = 1;
		sGhostPartyWork.pressure += 2;
	} else {
		sGhostPartyWork.mood = 0;
		sGhostPartyWork.pressure -= 1;
	}

	if (sGhostPartyWork.pressure < 0) {
		sGhostPartyWork.pressure = 0;
	} else if (sGhostPartyWork.pressure > (targetPressure + 100)) {
		sGhostPartyWork.pressure = targetPressure + 100;
	}

	if (sGhostPartyWork.auraParticle != 0 && sGhostPartyWork.pressure < targetPressure / 2) {
		endPSlotBit(0x400);
		sGhostPartyWork.auraParticle = 0;
	} else if (sGhostPartyWork.auraParticle == 0 && sGhostPartyWork.pressure > targetPressure) {
		putParticle(0x20D, 0, this, 0.0f, 0);
		sGhostPartyWork.auraParticle = 1;
	}

	if ((leader->m_lastStateId == 2 || leader->m_lastStateId == 6) &&
	    leader->m_subState == 1 &&
	    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x668) != 0 &&
	    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x660) == 0) {
		sGhostPartyWork.thresholdA++;
		sGhostPartyWork.thresholdB = 0;
	} else {
		sGhostPartyWork.thresholdA = 0;
		sGhostPartyWork.thresholdB++;
	}
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
	CGPartyObj* leader = Game.m_partyObjArr[0];
	CGObject* chalice = reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0);
	if (leader == nullptr || leader == this || m_scriptHandle == nullptr) {
		return;
	}

	if (leader->m_lastStateId == 0 &&
	    leader->m_animSlotSel == 0x0C &&
	    *reinterpret_cast<CGObject**>(reinterpret_cast<unsigned char*>(leader) + 0x6F0) == chalice) {
		sGhostPartyWork.settleTimer++;
	} else {
		sGhostPartyWork.settleTimer = 0;
	}

	if (sGhostPartyWork.carrySpeed > 0.05f) {
		moveVector(&sGhostPartyWork.carryDir, sGhostPartyWork.carrySpeed, 1);
	}
	sGhostPartyWork.carrySpeed *= 0.85f;

	int stageMode;
	switch (Game.m_gameWork.m_bossArtifactStageIndex) {
	case 4:
	case 8:
	case 9:
	case 0x0B:
	case 0x0C:
	case 0x0D:
		stageMode = 2;
		break;
	case 6:
	case 10:
		stageMode = 1;
		break;
	default:
		stageMode = 0;
		break;
	}

	float frameScale = static_cast<float>(Game.m_gameWork.m_frameCounter % 100) / 100.0f;
	float pressureScale = 1.0f;
	if (stageMode == 2) {
		pressureScale = 0.5f + frameScale * 0.5f;
	} else if (stageMode == 1) {
		pressureScale = 0.5f + (1.0f - frameScale) * 0.5f;
	}

	int pressureLimit = static_cast<int>(100.0f * pressureScale);
	if (sGhostPartyWork.carrySpeed <= 0.5f) {
		if (*reinterpret_cast<float*>(self + 0x6F0) == 0.0f) {
			sGhostPartyWork.pressure -= 4;
		} else {
			sGhostPartyWork.pressure -= 3;
		}
	} else if (*reinterpret_cast<float*>(self + 0x6F0) != 0.0f) {
		sGhostPartyWork.pressure += 2;
	} else {
		sGhostPartyWork.pressure -= 2;
	}

	if (sGhostPartyWork.pressure < 0) {
		sGhostPartyWork.pressure = 0;
	} else if (sGhostPartyWork.pressure > pressureLimit + 100) {
		sGhostPartyWork.pressure = pressureLimit + 100;
	}

	if (sGhostPartyWork.pressure < pressureLimit / 3) {
		PartyData(this).partyFlags &= 0xFB;
	}
	if (sGhostPartyWork.activeTrailCount > 0) {
		sGhostPartyWork.activeTrailCount--;
	}

	Vec pathVec;
	float pathDist = 0.0f;
	gpmCalcDist(&pathVec, pathDist);

	Vec toLeader;
	PSVECSubtract(&leader->m_worldPosition, &m_worldPosition, &toLeader);
	toLeader.y = 0.0f;
	float dist = PSVECMag(&toLeader);
	float nearDist = m_nearColRadius + leader->m_nearColRadius;
	float clampedDist = (*reinterpret_cast<float*>(self + 0x5C4) < dist) ? *reinterpret_cast<float*>(self + 0x5C4) : dist;

	if (m_lastStateId != 0 || (static_cast<signed char>(m_shieldAttachNodeIndex) >= 0)) {
		if (m_lastStateId != 2) {
			return;
		}
		if (static_cast<signed char>(PartyData(this).partyFlags) >= 0) {
			changeStat(0, 0, 0);
			return;
		}

		if (leader->m_lastStateId == 2 || leader->m_lastStateId == 6) {
			if (m_subState != 1) {
				return;
			}
			if (*reinterpret_cast<int*>(self + 0x668) == 0) {
				return;
			}
			if ((PartyData(leader).partyFlags & 0x40) != 0) {
				sGhostPartyWork.trailIndex = 0;
			}
			if ((PartyData(this).partyFlags & 0x80) == 0) {
				return;
			}

			PartyData(this).partyFlags |= 0x20;
			sGhostPartyWork.trailIndex++;
			if (sGhostPartyWork.trailIndex < 0x10) {
				return;
			}
			if ((PartyData(this).partyFlags & 0x40) != 0) {
				return;
			}
		} else if ((PartyData(this).partyFlags & 0x40) == 0) {
			changeStat(0, 0, 0);
			return;
		}

		sGhostPartyWork.thresholdA = (sGhostPartyWork.slotSel == 0) ? 0 : sGhostPartyWork.thresholdA / 2;
		sGhostPartyWork.thresholdB = (sGhostPartyWork.slotSel == 1) ? 0 : sGhostPartyWork.thresholdB / 2;
		sGhostPartyWork.thresholdC = (sGhostPartyWork.slotSel == 2) ? 0 : sGhostPartyWork.thresholdC / 2;
		PartyData(this).partyFlags = (PartyData(this).partyFlags & 0xAF) | 0x40;
		return;
	}

	int moveKind = 0;
	if (static_cast<signed char>(PartyData(this).partyFlags) >= 0) {
		if (chalice != nullptr &&
		    *reinterpret_cast<float*>(self + 0x6F0) == 0.0f &&
		    (static_cast<signed char>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(chalice) + 0x9A)) < 0) &&
		    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(chalice) + 0x550) == 0) {
			float pickupRadius = (leader->m_bodyEllipsoidRadius + *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(chalice) + 0x144)) * 1.25f;
			if (dist < pickupRadius) {
				CancelMove(1);
				rotTarget(reinterpret_cast<CGPrgObj*>(chalice));
				sGhostPartyWork.carrySpeed = 0.0f;
				carry(0, chalice, 0);
				return;
			}
			moveKind = 1;
		}

		if (moveKind == 0) {
			float limit = (sGhostPartyWork.activeTrailCount != 0) ? 0.75f : 0.5f;
			if (pathDist < Game.unkFloat_0xca10 * limit) {
				return;
			}
		}
		if (moveKind == 1 && chalice != nullptr) {
			float keepDist = (leader->m_bodyEllipsoidRadius + *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(chalice) + 0x144)) * 0.5f;
			if (clampedDist < keepDist) {
				return;
			}
		}
	} else {
		if (*reinterpret_cast<float*>(self + 0x6F0) != 0.0f) {
			sGhostPartyWork.carrySpeed = 0.0f;
			carry(1, static_cast<CGObject*>(0), 0);
			return;
		}

		float limit = (sGhostPartyWork.activeTrailCount != 0) ? 0.75f : 0.8f;
		if (Game.unkFloat_0xca10 * limit > pathDist) {
			if ((leader->m_lastStateId != 2 && leader->m_lastStateId != 6) ||
			    leader->m_subState != 1 ||
			    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x668) == 0 ||
			    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x660) != 0) {
				return;
			}

			int threshold0 = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Chara) + 0x2048);
			int threshold1 = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Chara) + 0x204C);
			int threshold2 = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Chara) + 0x2050);
			if (sGhostPartyWork.thresholdA < threshold0 &&
			    sGhostPartyWork.thresholdB < threshold1 &&
			    sGhostPartyWork.thresholdC < threshold2) {
				return;
			}

			int choices = 0;
			if (sGhostPartyWork.thresholdA >= threshold0) {
				choices++;
			}
			if (sGhostPartyWork.thresholdB >= threshold1) {
				choices++;
			}
			if (sGhostPartyWork.thresholdC >= threshold2) {
				choices++;
			}

			int pick = Math.Rand(choices);
			int cursor = 0;
			if (sGhostPartyWork.thresholdA >= threshold0) {
				if (cursor == pick) {
					sGhostPartyWork.slotSel = 0;
				}
				cursor++;
			}
			if (cursor <= pick && sGhostPartyWork.thresholdB >= threshold1) {
				if (cursor == pick) {
					sGhostPartyWork.slotSel = 1;
				}
				cursor++;
			}
			if (cursor <= pick && sGhostPartyWork.thresholdC >= threshold2) {
				sGhostPartyWork.slotSel = 2;
			}

			if (sGhostPartyWork.slotSel == 1) {
				*reinterpret_cast<int*>(self + 0x550) = 0x20F;
			} else if (sGhostPartyWork.slotSel == 0) {
				*reinterpret_cast<int*>(self + 0x550) = 0x207;
			} else if (sGhostPartyWork.slotSel < 3) {
				*reinterpret_cast<int*>(self + 0x550) = 0x20B;
			}
			changeStat(2, 0, 0);
			sGhostPartyWork.trailIndex = 0;
			PartyData(this).partyFlags &= 0x9F;
			return;
		}
	}

	if (PartyData(this).unk6BC != moveKind) {
		PartyData(this).unk6C0 = 0;
		PartyData(this).unk6BC = moveKind;
	}

	Vec moveDir;
	if (moveKind == 0) {
		moveDir = pathVec;
	} else {
		moveDir = toLeader;
	}

	float nextSpeed = sGhostPartyWork.carrySpeed + 0.05f;
	float speedScale = (pressureLimit <= sGhostPartyWork.pressure) ? 1.0f : 0.9f;
	float speedLimit = speedScale * m_moveBaseSpeed * *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(leader) + 0x690);
	sGhostPartyWork.carrySpeed = (nextSpeed >= 0.0f && speedLimit < nextSpeed) ? speedLimit : nextSpeed;

	PartyData(this).unk6C0++;
	sGhostPartyWork.carryDir = moveDir;
	if (PartyData(this).unk6C0 >= 4) {
		PartyData(this).unk6C0 = 0;
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
	switch (controlType) {
	case 0x13:
		reinterpret_cast<CCaravanWork*>(m_scriptHandle)->BackupTutorialItem(controlValue);
		break;
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
	if (m_scriptHandle == nullptr) {
		return;
	}

	char text[256];
	const int commandMode = PartyData(this).commandMode;
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	const int targetState = *reinterpret_cast<int*>(self + 0x668);
	const int alive = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C);
	sprintf(text, s_partyObjStateFmt, commandMode, m_lastStateId, m_subState, m_subFrame, alive, targetState,
	        sGhostPartyWork.mood);

	float width = static_cast<float>(font->GetWidth(text));
	font->SetPosX(x - width * 0.5f);
	font->SetPosY(y);
	font->SetPosZ(z);
	font->Draw(text);
	y -= 12.0f;
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
