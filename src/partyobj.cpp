#include "ffcc/ptrarray.h"
#include "ffcc/partyobj.h"
#include "ffcc/chara.h"
#include "ffcc/cflat_runtime2.h"
#include "ffcc/gobjwork.h"
#include "ffcc/game.h"
#include "ffcc/pad.h"
#include "ffcc/map.h"
#include "ffcc/maphit.h"
#include "ffcc/joybus.h"
#include "ffcc/linkage.h"
#include "ffcc/math.h"
#include "ffcc/vector.h"
#include "ffcc/p_menu.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_minigame.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/ringmenu.h"
#include "ffcc/sound.h"
#include "ffcc/itemobj.h"
#include "ffcc/monobj.h"
#include "ffcc/mesmenu.h"

#include <math.h>
#include "ffcc/fontman.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

class CAStar {
public:
	void addRealTime(CGPartyObj*);
};

extern const char lbl_801DCA48[];
extern const char lbl_801DCCB0[];
extern const char lbl_801DCD78[];
extern const char lbl_80331B0C[];
extern const char sBossGhostPartyCountersFmt[];
extern const char sMissingRingMenuFmt[];
extern int __float_huge[];

static const char s_partyObjGhostFmt[] = "%d/%d %d/%d %d/%d";
static const char s_partyObjGhostAngleFmt[] = "%d/%d a=%d";
static const char s_partyObjDebugScriptFmt[] = "%d %d %d %d %d %d";
extern "C" const float kMonObjPercentMax;
extern "C" const float kMonObjOne;
extern const float FLOAT_80331A58 = 0.5f;
extern const float FLOAT_80331A5C = 1800.0f;
extern const double DOUBLE_80331A60 = 4503601774854144.0;
extern const double DOUBLE_80331A68 = 4503599627370496.0;
extern const float FLOAT_80331A70 = 0.1f;
extern const float FLOAT_80331a74 = 0.95f;
extern const float FLOAT_80331a78 = 0.0f;
extern const float FLOAT_80331A7C = 0.3f;
extern const float FLOAT_80331A80 = 0.7f;
extern const float FLOAT_80331A84 = 1.5f;
extern const float FLOAT_80331A88 = 4.0f;
extern const double DOUBLE_80331A90 = 90.0;
extern const float FLOAT_80331A98 = 10.0f;
extern const float FLOAT_80331a9c = 10000000000.0f;
extern const float FLOAT_80331aa0 = -10000000000.0f;
extern const double DOUBLE_80331AA8 = 300.0;
extern const float FLOAT_80331AB0 = 3.0f;
extern const float FLOAT_80331AB4 = 0.15f;
extern const float FLOAT_80331AB8 = 3.1415927f;
extern const float FLOAT_80331ABC = 0.25f;
extern const float FLOAT_80331AC0 = 11.0f;
extern const float FLOAT_80331ac4 = 6.0f;
extern const float FLOAT_80331ac8 = 1.5707964f;
extern const float FLOAT_80331acc = -100.0f;
extern const float FLOAT_80331ad0 = 5.0f;
extern const float FLOAT_80331ad4 = 2.0f;
extern const float FLOAT_80331ad8 = 0.7853982f;
extern const float FLOAT_80331ADC = 0.01f;
extern const float FLOAT_80331AE0 = 0.017453292f;
extern const double DOUBLE_80331AE8 = 0.5;
extern const double DOUBLE_80331AF0 = 3.0;
extern const double DOUBLE_80331AF8 = 0.0;
extern const float FLOAT_80331b00 = 1.1f;
extern const float FLOAT_80331b04 = 1.2f;
extern const float FLOAT_80331b08 = 1.25f;
extern const char lbl_80331B0C[] = "%d\n";
extern const char s_CMcPcsName[] = "CMcPcs";
extern float FLOAT_8032EE78;
extern float FLOAT_8032EE7C;
extern float FLOAT_8032EE80;
extern float FLOAT_8032EE84;
int s_partyObjCreated_8032EE70;
extern char s_partyObjCreatedInit_8032EE74;

unsigned char CGPartyObj::m_ghostWork[0x90];
#define sGhostPartyWork (*reinterpret_cast<GhostPartyWork*>(CGPartyObj::m_ghostWork))

struct BossGhostPartyCounters {
	unsigned char _pad0[0x24];
	int thresholdA;
	int thresholdB;
	int thresholdC;
};

#define sBossGhostPartyCounters (*reinterpret_cast<BossGhostPartyCounters*>(CGPartyObj::m_ghostWork))

struct GhostMogMenuWork {
	struct {
		signed char carryActive : 1;
		signed char flag40 : 1;
		signed char _bits : 6;
	} flags;
	unsigned char _pad1[0x3F];
	int mood;
	int holdTimer;
};

#define sGhostMogMenuWork (*reinterpret_cast<GhostMogMenuWork*>(CGPartyObj::m_ghostWork))

static inline PartyObjOverlay& PartyData(CGPartyObj* self)
{
	return self->m_partyData;
}

static inline int& CharaGhostValue(int offset)
{
	return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Chara) + offset);
}

static inline int& PartyTraceParticleSlot(int port)
{
	return CFlatPartyTraceParticleSlot(port);
}

static inline void UpdateGhostPartyDamageCounters(CGPrgObj* attacker)
{
	if (((static_cast<unsigned short>(attacker->GetCID()) & 0xAD) == 0xAD) && Game.m_gameWork.m_menuStageMode != 0) {
		sBossGhostPartyCounters.thresholdA++;
		sBossGhostPartyCounters.thresholdB++;
		sBossGhostPartyCounters.thresholdC++;
		System.Printf(const_cast<char*>(sBossGhostPartyCountersFmt),
		    sBossGhostPartyCounters.thresholdA, CharaGhostValue(0x2048),
		    sBossGhostPartyCounters.thresholdB, CharaGhostValue(0x204C),
		    sBossGhostPartyCounters.thresholdC, CharaGhostValue(0x2050));
	}
}

static unsigned short getPadHeldForSlot(int slot)
{
	bool blocked = Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1);
	if (blocked) {
		return 0;
	}

	int selectedPort = Pad.m_debugPadPort;
	unsigned int idx = slot & ~((int)~(selectedPort - slot | slot - selectedPort) >> 31);
	return Pad.GetPadInputs()[idx].button[0];
}

static unsigned short getPadTrigForSlot(int slot)
{
	bool blocked = Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1);
	if (blocked) {
		return 0;
	}

	int selectedPort = Pad.m_debugPadPort;
	unsigned int idx = slot & ~((int)~(selectedPort - slot | slot - selectedPort) >> 31);
	return Pad.GetPadInputs()[idx].buttonDown[0];
}

static int getPadConnectedForSlot(int slot)
{
	bool blocked = Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1);
	if (blocked) {
		return 0;
	}

	int selectedPort = Pad.m_debugPadPort;
	unsigned int idx = slot & ~((int)~(selectedPort - slot | slot - selectedPort) >> 31);
	return Pad.GetPadInputs()[idx].gbaMode;
}

static unsigned short getPadButtonUpForSlot(int slot)
{
	bool blocked = Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1);
	if (blocked) {
		return 0;
	}

	int selectedPort = Pad.m_debugPadPort;
	unsigned int idx = slot & ~((int)~(selectedPort - slot | slot - selectedPort) >> 31);
	return Pad.GetPadInputs()[idx].buttonUp;
}

static bool isMenuPcsCommandBusy()
{
	return MenuPcs.m_mode != 0;
}

static CRingMenu* getBattleRingMenuForPort(int port)
{
	return MenuPcs.m_battleRingMenus[port];
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

static float getPadLeftStickXForSlot(int slot)
{
	bool blocked = Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1);
	if (blocked) {
		return 0.0f;
	}

	int selectedPort = Pad.m_debugPadPort;
	unsigned int idx = slot & ~((int)~(selectedPort - slot | slot - selectedPort) >> 31);
	return Pad.GetPadInputs()[idx].stickXF;
}

static float getPadLeftStickYForSlot(int slot)
{
	bool blocked = Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1);
	if (blocked) {
		return 0.0f;
	}

	int selectedPort = Pad.m_debugPadPort;
	unsigned int idx = slot & ~((int)~(selectedPort - slot | slot - selectedPort) >> 31);
	return Pad.GetPadInputs()[idx].stickYF;
}

static bool isBossArtifactStage()
{
	return Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0x0F;
}

static inline float LoadFloat(const float& value)
{
	return value;
}

static bool isFrameInterval(int frame, int interval)
{
	return frame % interval == 0;
}

static inline bool isGhostPartyTargetMode(CGPartyObj* self)
{
	bool result = false;
	bool cidMatch = false;
	bool stageOk = false;

	if (Game.m_gameWork.m_menuStageMode != 0) {
		if (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F) {
			stageOk = true;
		}
	}
	if (stageOk) {
		if ((__cntlzw(0x6D - (static_cast<unsigned short>(self->GetCID()) & 0x6D)) >> 5 & 0xFF) != 0) {
			cidMatch = true;
		}
	}
	if (cidMatch) {
		if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(self->m_scriptHandle) + 0x3B4) != 0) {
			result = true;
		}
	}
	return result;
}

static inline int getCarryAnimNo(CGPartyObj* self, int carryType)
{
	if (isGhostPartyTargetMode(self)) {
		return 5;
	}

	if (carryType == 0) {
		if (CFlatItemCarryMode() == 1) {
			unsigned char* script = reinterpret_cast<unsigned char*>(self->m_scriptHandle);
			unsigned int table = Game.unk_flat3_field_30_0xc7e0 +
			    (*reinterpret_cast<unsigned short*>(script + 0x3E2) +
			     *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2) * 0x1CA;
			return *reinterpret_cast<unsigned short*>(table + 0x1C6);
		}
		unsigned char* script = reinterpret_cast<unsigned char*>(self->m_scriptHandle);
		unsigned int table = Game.unk_flat3_field_30_0xc7e0 +
		    (*reinterpret_cast<unsigned short*>(script + 0x3E2) +
		     *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2) * 0x1CA;
		return *reinterpret_cast<unsigned short*>(table + 0x1C2);
	} else {
		if (CFlatItemCarryMode() == 1) {
			unsigned char* script = reinterpret_cast<unsigned char*>(self->m_scriptHandle);
			unsigned int table = Game.unk_flat3_field_30_0xc7e0 +
			    (*reinterpret_cast<unsigned short*>(script + 0x3E2) +
			     *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2) * 0x1CA;
			return *reinterpret_cast<unsigned short*>(table + 0x1C8);
		}
		unsigned char* script = reinterpret_cast<unsigned char*>(self->m_scriptHandle);
		unsigned int table = Game.unk_flat3_field_30_0xc7e0 +
		    (*reinterpret_cast<unsigned short*>(script + 0x3E2) +
		     *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2) * 0x1CA;
		return *reinterpret_cast<unsigned short*>(table + 0x1C4);
	}
}

static CMapObj* getMapHitObject()
{
	return MapMng.m_hitMapObj;
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
	float targetDist = FLOAT_80331a78;
	party.attackSel = 0;
	party.unk6CC = 0;
	party.unk6BC = 0;
	party.target = 0;
	party.targetOverride = 0;
	party.unk6ECFloat = INFINITY;
	party.carryObject = 0;

	party.flags.commandActive = 0;
	party.flags.flag08 = 0;
	party.weaponItem = 0;
	party.pendingWeaponItem = 0;
	party.flags.flag40 = 0;
	party.flags.flag20 = 0;
	party.flags.flag10 = 0;
	party.flags.flag04 = 0;
	party.flags.flag02 = 0;

	m_targetDist = targetDist;
	party.unk6C0 = -1;
	party.commandMode = 0;

	if (s_partyObjCreatedInit_8032EE74 == 0) {
		s_partyObjCreated_8032EE70 = 0;
		s_partyObjCreatedInit_8032EE74 = 1;
	}

	if (s_partyObjCreated_8032EE70 == 0) {
		s_partyObjCreated_8032EE70 = 1;
	}
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
	PartyObjOverlay& party = PartyData(this);
	if (party.flags.flag04) {
		addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
		party.flags.flag04 = 0;
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
	const char* msgBase = lbl_801DCA48;
	m_weaponNodeFlagAll.m_bits1.m_menuReady = 0;

	switch (state) {
	case -20:
		break;
	case 0:
		m_weaponNodeFlagAll.m_bits1.m_menuReady = 1;
		break;
	case 1: {
		int attackSel = party.attackSel;
		*reinterpret_cast<int*>(self + 0x550) = (attackSel == 0) ? 5 : ((attackSel == 1) ? 7 : 8);
		int row = attackSel * 0x12;
		*reinterpret_cast<int*>(self + 0x630) =
		    *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_30_0xc7e0 +
		        (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) +
		         *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) * 2) * 0x1CA + row);
		*reinterpret_cast<int*>(self + 0x634) =
		    *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_30_0xc7e0 +
		        (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) +
		         *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) * 2) * 0x1CA + row + 2);
		*reinterpret_cast<int*>(self + 0x638) =
		    *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_30_0xc7e0 +
		        (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) +
		         *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) * 2) * 0x1CA + row + 10);
		break;
	}
	case 2:
		*reinterpret_cast<int*>(self + 0x550) = 0x0F;
		*reinterpret_cast<int*>(self + 0x554) = 0x10;
		*reinterpret_cast<int*>(self + 0x558) = 0x11;
		int castTime;
		if (*reinterpret_cast<int*>(self + 0x560) == 0x103) {
			castTime = 0;
		} else {
			castTime = calcCastTime(*reinterpret_cast<int*>(self + 0x560));
		}
		*reinterpret_cast<int*>(self + 0x68C) = castTime;
		break;
	case 8:
		*reinterpret_cast<int*>(self + 0x550) = 0x15;
		*reinterpret_cast<int*>(self + 0x554) = 0x16;
		*reinterpret_cast<int*>(self + 0x558) = 0x17;
		*reinterpret_cast<int*>(self + 0x55C) = 0x18;
		break;
	case 6:
		System.Printf(const_cast<char*>(msgBase + 0x370), *reinterpret_cast<int*>(self + 0x560));
		*reinterpret_cast<int*>(self + 0x560) =
		    *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<int*>(self + 0x560) * 0x48 + 10);
		System.Printf(const_cast<char*>(lbl_80331B0C), *reinterpret_cast<int*>(self + 0x560));
		*reinterpret_cast<int*>(self + 0x550) = 0x12;
		*reinterpret_cast<int*>(self + 0x554) = 0x13;
		unsigned short itemKind =
		    *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<int*>(self + 0x560) * 0x48 + 10);
		int itemHigh = itemKind >> 8;
		int itemLow = itemKind & 0xFF;
		System.Printf(const_cast<char*>(msgBase + 0x390), itemHigh);
		System.Printf(const_cast<char*>(msgBase + 0x3AC), itemLow);
		*reinterpret_cast<int*>(self + 0x558) = itemHigh + 0x2A;
		{
			int row = itemLow * 0x42;
			*reinterpret_cast<int*>(self + 0x630) =
			    *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_30_0xc7e0 +
			        (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) +
			         *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) * 2) * 0x1CA + row + 0x38);
			*reinterpret_cast<int*>(self + 0x634) =
			    *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_30_0xc7e0 +
			        (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) +
			         *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) * 2) * 0x1CA + row + 0x3A);
		}
		*reinterpret_cast<int*>(self + 0x68C) = calcCastTime(*reinterpret_cast<int*>(self + 0x560));
		if (Game.m_gameWork.m_menuStageMode != 0) {
			int cmdListItem =
			    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCmdListItem(PartyData(this).weaponItem);
			if (cmdListItem >= 0) {
				m_comboItemState = cmdListItem;
			}
		}
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
		party.flags.flag40 = 0;
		party.flags.flag20 = 0;
		endPSlotBit(0x10);
		endPSlotBit(0x100);
		break;
	case 0x0F:
		if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x6C4]) << 26) & 0xC0000000) >> 31) != 0) {
			int weaponB = *reinterpret_cast<int*>(self + 0x6D4);
			int weaponA = *reinterpret_cast<int*>(self + 0x6D8);
			if (weaponA <= 0) {
				LoadWeapon(-1, 0);
			} else {
				unsigned short packedItem = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + weaponA * 0x48 + 2);
				LoadWeapon(packedItem & 0xFFF, packedItem >> 12);
			}
			*reinterpret_cast<int*>(self + 0x6DC) = weaponB;
			*reinterpret_cast<int*>(self + 0x6E0) = weaponA;
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->SetCurrentWeaponIdx(*reinterpret_cast<int*>(self + 0x6DC));
			party.commandFlagBits.flag20 = 0;
		}
		break;
	case 0x15:
		enableDamageCol(1);
		break;
	case 0x14:
		m_alpha = kMonObjOne;
		enableDamageCol(1);
		break;
	case 0x0B:
		{
			if (party.carryObject != 0) {
				if (CFlatItemCarryMode() == 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
			} else {
				if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0, 0);
						SetAnimSlot(1, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x30, 1);
					}
				} else {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					}
				}
			}
		}
		break;
	case 0x0C:
	case 0x0D:
		{
			if (party.carryObject != 0) {
				if (CFlatItemCarryMode() == 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
			} else {
				if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0, 0);
						SetAnimSlot(1, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x30, 1);
					}
				} else {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					}
				}
			}
		}
		break;
	case 9:
		if (state == 0x22) {
			break;
		}
		if (party.flags.flag04) {
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
				addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
			}
			party.flags.flag04 = 0;
		}
		enableDamageCol(1);
		{
			if (party.carryObject != 0) {
				if (CFlatItemCarryMode() == 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
			} else {
				if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0, 0);
						SetAnimSlot(1, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x30, 1);
					}
				} else {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					}
				}
			}
		}
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			endPSlotBit(0x10000);
			m_alpha = kMonObjOne;
			m_bgColMask |= 0x1000E;
		} else {
			m_alpha = FLOAT_80331A7C;
			m_bgColMask &= 0xFFFEFFF1;
		}
		break;
	case 0x22:
		if (party.flags.flag04) {
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
				addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
			}
			party.flags.flag04 = 0;
		}
		enableDamageCol(1);
		{
			if (party.carryObject != 0) {
				if (CFlatItemCarryMode() == 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
			} else {
				if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0, 0);
						SetAnimSlot(1, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x30, 1);
					}
				} else {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					}
				}
			}
		}
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			endPSlotBit(0x10000);
			m_alpha = kMonObjOne;
			m_bgColMask |= 0x1000E;
		} else {
			m_alpha = FLOAT_80331A7C;
			m_bgColMask &= 0xFFFEFFF1;
		}
		break;
	case 6:
		*reinterpret_cast<float*>(self + 0x4FC) = FLOAT_80331a78;
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
	void* portIndex = m_scriptHandle[0xED];

	if (party.flags.flag08) {
		if (Game.m_gameWork.m_menuStageMode != 0 ||
		    Joybus.GetPadType(static_cast<char>(m_animStateMisc)) != 0x40000) {
			if (Game.m_gameWork.m_menuStageMode == 0) {
				return;
			}
			if (Game.m_gameWork.m_gamePaused != 0) {
				return;
			}
			if (static_cast<char>(m_animStateMisc) != 0) {
				return;
			}
		}

		if (Game.m_gameWork.m_menuStageMode == 0) {
			int slot = static_cast<char>(m_animStateMisc);
			bool bVar3 = false;
			if (Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1)) {
				bVar3 = true;
			}
			unsigned short trig = bVar3 ? 0 : Pad.GetPadInputs()[slot & ~((~(Pad.m_debugPadPort - slot | slot - Pad.m_debugPadPort) >> 0x1F))].buttonDown[1];
			if ((trig & 0x10) != 0) {
				goto LAB_OPEN;
			}
		}

		if (Game.m_gameWork.m_menuStageMode == 0) {
			return;
		}

		{
			int slot = static_cast<char>(m_animStateMisc);
			bool bVar3 = false;
			if (Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1)) {
				bVar3 = true;
			}
			unsigned short trig = bVar3 ? 0 : Pad.GetPadInputs()[slot & ~((~(Pad.m_debugPadPort - slot | slot - Pad.m_debugPadPort) >> 0x1F))].buttonDown[0];
			if ((trig & 0x800) == 0) {
				return;
			}
		}

	LAB_OPEN:
		if (Game.m_gameWork.m_menuStageMode == 0) {
			int slot = static_cast<char>(m_animStateMisc);
			bool bVar3 = false;
			if (Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1)) {
				bVar3 = true;
			}
			int connected = bVar3 ? 0 : Pad.GetPadInputs()[slot & ~((~(Pad.m_debugPadPort - slot | slot - Pad.m_debugPadPort) >> 0x1F))].gbaMode;
			if (connected != 0) {
				if ((CFlatEventFlags() & CFlatEventFlagByte_GbaSound) != 0) {
					Sound.PlaySe(8, 0x40, 0x7F, 0);
				}
			} else if ((CFlatEventFlags() & CFlatEventFlagByte_GbaSound) != 0) {
				Sound.PlaySe(7, 0x40, 0x7F, 0);
			}

			Joybus.ChgCtrlMode(reinterpret_cast<int>(portIndex));
			return;
		}

		int bVar3;
		if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&m_weaponNodeFlags)) << 24) & 0xC0000000) >> 31) != 0) &&
		    ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(&m_weaponNodeFlags)[1]) << 24) & 0xC0000000) >> 31) != 0) ||
		     ((party.commandMode & 2) != 0) ||
		     ((party.commandMode & 4) != 0)) &&
		    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x63C)) << 24) & 0xC0000000) >> 31) != 0) &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0)) {
			bVar3 = 1;
		} else {
			bVar3 = 0;
		}

		if (bVar3) {
			Joybus.ChgCtrlMode(reinterpret_cast<int>(portIndex));
			Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 1;
		} else {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
		}
		return;
	}

	if (Game.m_gameWork.m_menuStageMode != 0) {
		return;
	}

	{
		int slot = static_cast<char>(m_animStateMisc);
		bool bVar3 = false;
		if (Pad.m_debugPadLock != 0 || (slot == 0 && Pad.m_debugPadPort != -1)) {
			bVar3 = true;
		}
		int connected = bVar3 ? 0 : Pad.GetPadInputs()[slot & ~((~(Pad.m_debugPadPort - slot | slot - Pad.m_debugPadPort) >> 0x1F))].gbaMode;
		if (connected == 0) {
			return;
		}
	}

	if (static_cast<unsigned int>(System.m_execParam) >= 3) {
		System.Printf(const_cast<char*>("port:%d mode:%d"), portIndex, Joybus.GetCtrlMode(static_cast<signed char>(m_animStateMisc)));
	}

	Joybus.ChgCtrlMode(reinterpret_cast<int>(portIndex));
	if ((CFlatEventFlags() & CFlatEventFlagByte_GbaSound) != 0) {
		Sound.PlaySe(8, 0x40, 0x7F, 0);
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

	PartyObjOverlay& party = PartyData(this);
	if (party.target != nullptr &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(party.target) + 0x38)) << 24) & 0xC0000000) >> 31) != 0)) {
		party.target = 0;
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0 &&
	    (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1)) {
		if (m_weaponModelHandle == nullptr) {
			int weaponItem = party.pendingWeaponItem;
			int weaponRef = party.weaponItem;
			if (weaponItem <= 0) {
				LoadWeapon(-1, 0);
			} else {
				unsigned short packedItem = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + weaponItem * 0x48 + 2);
				LoadWeapon(packedItem & 0xFFF, packedItem >> 12);
			}
			party.weaponItem = weaponRef;
			party.pendingWeaponItem = weaponItem;
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->SetCurrentWeaponIdx(party.weaponItem);
			party.commandFlagBits.flag20 = 0;
		}

		unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
		int shieldIndex = *reinterpret_cast<short*>(script + 0xB0);
		int shieldItem;
		if (shieldIndex >= 0) {
			shieldItem = *reinterpret_cast<short*>(script + shieldIndex * 2 + 0xB6);
		} else {
			shieldItem = 0;
		}
		if (shieldItem > 0) {
			int shieldModel = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + shieldItem * 0x48 + 2) & 0xFFF;
			if (m_shieldModelHandle == nullptr || static_cast<unsigned int>(m_shieldModelHandle->m_charaNo) != static_cast<unsigned int>(shieldModel)) {
				LoadShield(shieldModel);
			}
		} else {
			LoadShield(-1);
		}
	} else {
		LoadWeapon(-1, 0);
		LoadShield(-1);
	}

	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->CalcStatus();
	int port = reinterpret_cast<int>(m_scriptHandle[0xED]);
	int showTraceParticle;
	if ((static_cast<int>(Game.m_gameWork.m_gameInitFlag) == 0) ||
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 28) & 0xC0000000) >> 31) == 0) ||
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 29) & 0xC0000000) >> 31) == 0) ||
	    ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(&m_weaponNodeFlags)) << 24) & 0xC0000000) >> 31) == 0) ||
	     (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*(reinterpret_cast<unsigned char*>(&m_weaponNodeFlags) + 1)) << 24) & 0xC0000000) >> 31) == 0)) ||
	    (m_lastStateId == 6 || m_lastStateId == 2)) {
		showTraceParticle = 0;
	} else if ((Game.m_gameWork.m_menuStageMode != 0) &&
		    (Game.m_gameWork.m_menuStageMode != 0) &&
		    (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F) &&
		    ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) &&
		    (reinterpret_cast<int>(m_scriptHandle[0xED]) != 0)) {
		showTraceParticle = 0;
	} else {
		showTraceParticle = 1;
	}

	int& traceSlot = PartyTraceParticleSlot(port);
	if (showTraceParticle && traceSlot == 0) {
		traceSlot = CFlat.GetFreeParticleSlot();
		putParticleTrace((port + 0x42U) | 0x100, traceSlot, this, kMonObjOne, 0);
	} else if (!showTraceParticle && traceSlot != 0) {
		CFlat.EndParticleSlot(traceSlot, 1);
		traceSlot = 0;
	}

	if (reinterpret_cast<int>(m_scriptHandle[0xED]) == 0 && (MiniGamePcs.m_flags & 0x400) != 0) {
		reinterpret_cast<CAStar*>(reinterpret_cast<unsigned char*>(&DbgMenuPcs) + 0x2A5C)->addRealTime(this);
	}

	if ((MiniGamePcs.m_flags & 0x2000) != 0) {
		int itemId;
		do {
			itemId = Math.Rand(0x155) + 0x9F;
			unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2] + itemId * 0x48);
		} while ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48) == 0) ||
		         ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 2) & 0x0FFF) == 0) ||
		         ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 2) & 0x0FFF) == 0x0FFF) ||
		         (itemId == 400));

		if (reinterpret_cast<int>(m_scriptHandle[0xED]) == 0) {
			CGItemObj::CreateFromScript(0, 4, itemId, this, FLOAT_80331a78, (CGItemObj::CCFS*)0);
			if (static_cast<unsigned int>(Math.Rand(10)) == 0) {
				CGItemObj::CreateFromScript(2, 4, 0x3039, this, FLOAT_80331a78, (CGItemObj::CCFS*)0);
			}
		}

		int modelId = Math.Rand(0x1A) + 1;
		if (modelId == 0x0F) {
			modelId = 1;
		}
		LoadWeapon(modelId, 0);

		modelId = Math.Rand(0x1A) + 1;
		if (modelId == 0x0F) {
			modelId = 1;
		}
		LoadShield(modelId);
	}

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
		*reinterpret_cast<float*>(self + 0x5BC) = PSVECDistance(&m_worldPosition, chalicePos);
	}

	if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x63C]) << 24) & 0xC0000000) >> 31) != 0) &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(party.partyFlags) << 24) & 0xC0000000) >> 31) == 0) &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x9B]) << 25) & 0xC0000000) >> 31) == 0)) {
		unsigned short held = getPadHeldForSlot(static_cast<signed char>(m_animStateMisc));
		if (held != 0) {
			changeStat(0, 0, 0);
		}
	}

	int weaponItem;
	int weaponRef;
	if (static_cast<int>(CFlatCenterState()) == 0) {
		reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCurrentWeaponItem(weaponItem, weaponRef);
		if (party.weaponItem != weaponItem || party.pendingWeaponItem != weaponRef) {
		bool canImmediateSwap =
		    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x9A]) << 24) & 0xC0000000) >> 31) != 0) &&
		    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x9B]) << 24) & 0xC0000000) >> 31) != 0) &&
		    (party.carryObject == nullptr) &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) == 0) &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x50) == 0) &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x44) == 0);

		if (canImmediateSwap) {
			if (weaponItem <= 0) {
				LoadWeapon(-1, 0);
			} else {
				unsigned short packedItem = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + weaponItem * 0x48 + 2);
				LoadWeapon(packedItem & 0x0FFF, packedItem >> 12);
			}
			party.weaponItem = weaponItem;
			party.pendingWeaponItem = weaponRef;
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->SetCurrentWeaponIdx(party.weaponItem);
			party.commandFlagBits.flag20 = 0;
		} else {
			*reinterpret_cast<int*>(self + 0x6D4) = weaponItem;
			party.weaponRef = weaponRef;
			party.commandFlagBits.flag20 = 1;
			changeStat(0x0F, 0, 0);
		}
		}
	}

	bonus(2, 0, 0);

	if (Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
		if (party.carryObject != nullptr ||
		    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
			float speedScale;
			if (static_cast<int>(CFlatCenterState()) == 0) {
				speedScale = FLOAT_80331b08;
			} else {
				speedScale = kMonObjOne;
			}
			m_moveBaseSpeed = static_cast<float>(static_cast<int>(FLOAT_80331b04 * speedScale));
		} else {
			m_moveBaseSpeed = FLOAT_80331ad4;
		}
		m_moveBaseSpeed *= *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x690);
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
	    (static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
	    reinterpret_cast<int*>(m_scriptHandle)[0xED] != 0) {
		ghostPartyMog();
	} else {
		command();
		shouki();
	}

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	*reinterpret_cast<CGBaseObj**>(self + 0x6E4) = (CGBaseObj*)0;
	*reinterpret_cast<CGBaseObj**>(self + 0x6E8) = (CGBaseObj*)0;
	*reinterpret_cast<float*>(self + 0x6EC) = INFINITY;
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
	const char* msgBase = lbl_801DCA48;
	if (isMenuPcsCommandBusy()) {
		return;
	}

	PartyObjOverlay& party = PartyData(this);
#define caravan reinterpret_cast<CCaravanWork*>(m_scriptHandle)
#define padSlot static_cast<char>(m_animStateMisc)
	bool primaryAvailable = false;
	int primaryCommand = -1;
	bool secondaryAvailable = false;
	int secondaryCommand = -1;
	int ringCommand = -1;
	int ringCommandArg = -1;

	if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(party.partyFlags) << 24) & 0xC0000000) >> 31) == 0) {

	if ((*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) &&
	    ((party.commandMode & 1) != 0) &&
	    Joybus.GetCtrlMode(padSlot) != 1) {
		int cmdDir = 0;

		if ((getPadHeldForSlot(padSlot) & 0x60) == 0x60) {
			caravan->IsUseCmdList(0);
		} else if ((getPadTrigForSlot(padSlot) & 0x20) != 0) {
			cmdDir = 1;
		} else if ((getPadTrigForSlot(padSlot) & 0x40) != 0) {
			cmdDir = -1;
		}

		if (cmdDir != 0) {
			Sound.PlaySe(0x0C, 0x40, 0x7F, 0);
			CCaravanWork* cmdDirCaravan = caravan;
			const int curCmd = cmdDirCaravan->GetIdxCmdList();
			cmdDirCaravan->IsUseCmdList(cmdDirCaravan->GetNextCmdListIdx(curCmd, cmdDir));
		}

		const int cmdIdx = caravan->GetIdxCmdList();
		if (cmdIdx == 0) {
			ringCommand = 1;
		} else if (caravan->GetIdxCmdList() == 1) {
			ringCommand = 9;
		} else {
			CCaravanWork* delCaravan = caravan;
			const int itemId = delCaravan->DelCmdListAndItem(delCaravan->GetIdxCmdList());
			const int itemKind = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48);
			switch (itemKind) {
			case 1:
			case 0xDF:
			case 0x100:
			case 0x125:
			case 0x17D:
			case 0x186:
			case 0x1F5:
				ringCommand = itemId | 0x8000;
				break;
			}
		}
		ringCommandArg = caravan->GetIdxCmdList();
	}

	if (((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(this)[0x9A]) << 24) & 0xC0000000) >> 31) != 0) &&
	     (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(this)[0x63C]) << 24) & 0xC0000000) >> 31) != 0) &&
	     (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(this)[0x9B]) << 24) & 0xC0000000) >> 31) != 0)) &&
	    Joybus.GetCtrlMode(padSlot) != 1) {
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		if (party.secondaryTarget != nullptr) {
			primaryAvailable = true;
			primaryCommand = 0x0C;
		}

		CGObject* target = party.target;
		if (target != nullptr) {
			unsigned char* targetBytes = reinterpret_cast<unsigned char*>(target);
			const int targetState = *reinterpret_cast<int*>(targetBytes + 0x500);

			if (targetState == 0x24) {
				goto tmpArtifactBlock;
			}
			if (targetState < 0x24) {
				if (targetState < 0x12) {
					if (targetState != 0x0B && (targetState > 0x0A || targetState > 0x09) &&
					    *reinterpret_cast<int*>(targetBytes + 0x550) == 0) {
						secondaryAvailable = true;
						secondaryCommand = 4;
					}
				} else if (targetState < 0x1C) {
					if (targetState < 0x19) {
tmpArtifactBlock:
#define freshTargetBytes (reinterpret_cast<unsigned char*>(party.target))
						if (*reinterpret_cast<int*>(targetBytes + 0x550) == 0) {
							secondaryAvailable = true;
							if ((targetState == 0x24 && caravan->CanAddTmpArtifact(1) != 0) ||
							    (*reinterpret_cast<int*>(freshTargetBytes + 0x500) == 0x20 &&
							     caravan->CanAddGil(*reinterpret_cast<int*>(freshTargetBytes + 0x558)) != 0) ||
							    ((*reinterpret_cast<int*>(freshTargetBytes + 0x500) != 0x24 &&
							      *reinterpret_cast<int*>(freshTargetBytes + 0x500) != 0x20) &&
							     *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xB4) + 1 <= 0x40)) {
								secondaryCommand = 0x17;
							} else {
								secondaryCommand = 4;
							}
						}
#undef freshTargetBytes
					}
				} else if (targetState < 0x22) {
					goto tmpArtifactBlock;
				}
			} else if (targetState < 0xCA) {
				if (targetState == 0xC8) {
					if (static_cast<int>(CFlatCenterState()) == 0) {
						secondaryAvailable = true;
						secondaryCommand = 0x0B;
					} else {
						primaryAvailable = true;
						primaryCommand = 0x0B;
					}
				} else if (targetState > 0xC7) {
					if (static_cast<int>(CFlatCenterState()) == 0) {
						secondaryAvailable = true;
						secondaryCommand = 0x0A;
					} else {
						primaryAvailable = true;
						primaryCommand = 0x0A;
					}
				}
			} else if (targetState == 0xCA) {
				if (static_cast<int>(CFlatCenterState()) == 0) {
					secondaryAvailable = true;
					secondaryCommand = 0x1C;
				} else {
					primaryAvailable = true;
					primaryCommand = 0x1C;
				}
			} else if (targetState == 0xCC) {
				secondaryAvailable = true;
				secondaryCommand = 6;
			}
		}

		if (party.carryObject != nullptr) {
			const int carryState = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.carryObject) + 0x500);
			secondaryAvailable = true;
			primaryAvailable = true;
			primaryCommand = -1;
			switch (carryState) {
			case 0x0D:
				secondaryCommand = 7;
				break;
			case 0x0E:
				secondaryCommand = 8;
				break;
			default:
				secondaryCommand = 5;
				break;
			}
		} else if (caravan->m_hp == 0) {
			primaryAvailable = true;
			primaryCommand = 0x1B;
		}

		if (Joybus.GetCtrlMode(padSlot) != 1) {
		if ((party.commandMode & 2) != 0) {
			secondaryAvailable = false;
			primaryAvailable = true;
			primaryCommand = 0x1A;
		}
		if ((party.commandMode & 4) != 0) {
			secondaryAvailable = false;
			primaryAvailable = true;
			primaryCommand = 0x1D;
		}
		if ((party.commandMode & 8) != 0) {
			secondaryAvailable = true;
			secondaryCommand = 0x1A;
			primaryAvailable = false;
			int cmdDir = 0;
			if ((getPadTrigForSlot(padSlot) & 0x20) != 0) {
				cmdDir = 1;
			} else if ((getPadTrigForSlot(padSlot) & 0x40) != 0) {
				cmdDir = -1;
			}
			if (cmdDir != 0) {
				Sound.PlaySe(0x0C, 0x40, 0x7F, 0);
				int& charaCommand = Chara.MogFur().m_commandIndex;
				charaCommand += cmdDir;
				if (charaCommand < 0) {
					charaCommand += 5;
				} else if (charaCommand > 4) {
					charaCommand -= 5;
				}
			}
			const int charaCommand = Chara.MogFur().m_commandIndex;
			ringCommand = charaCommand + 0x1E;
			ringCommandArg = charaCommand;
		}
		}
		}
	}

	CRingMenu* ring = getBattleRingMenuForPort(getPartyJoybusPort(this));
	ring->SetBattleCommand(0, primaryCommand, -1);
	ring->SetBattleCommand(1, secondaryCommand, -1);
	ring->SetBattleCommand(2, ringCommand, ringCommandArg);

	}

	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != 0) {
		return;
	}

	const unsigned short trig = getPadTrigForSlot(padSlot);
	if ((trig & 0x100) != 0) {
		if (primaryAvailable) {
			if (primaryCommand == 0x1B) {
				changeStat(0x20, 0, 0);
			}

			CGObject* scriptTarget = party.secondaryTarget != nullptr ?
				reinterpret_cast<CGObject*>(party.secondaryTarget) : party.target;
			party.partyFlags |= 0x80;

			CFlatRuntime::CStack stack[2];
			stack[0].m_word = primaryCommand;
			stack[1].m_word = scriptTarget != nullptr ?
				*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(scriptTarget) + 0x30) : 0;
			gCFlatRuntime().SystemCall(this, 2, 0x14, 2, stack, 0);
			return;
		}

		if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(&m_weaponNodeFlags)[1]) << 24) & 0xC0000000) >> 31) == 0) ||
		    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x63C)) << 24) & 0xC0000000) >> 31) == 0) ||
		    caravan->m_hp == 0 ||
		    ringCommand == -1 ||
		    ((*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0x6F4) & 8) != 0)) {
			return;
		}

		const int cmdIdx = caravan->GetIdxCmdList();
		party.unk6BC = cmdIdx;
		if (cmdIdx == 0) {
			int weaponItem;
			int weaponRef;
			caravan->GetCurrentWeaponItem(weaponItem, weaponRef);
			if (weaponItem != party.unk6BC ||
			    weaponRef != (caravan->m_equipment[0] >= 0 ? caravan->m_inventoryItems[caravan->m_equipment[0]] : 0)) {
				*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6D4) = cmdIdx;
				party.weaponRef = caravan->m_equipment[0] >= 0 ? caravan->m_inventoryItems[caravan->m_equipment[0]] : 0;
				party.commandFlagBits.flag20 = 1;
				changeStat(0x0F, 0, 0);
				return;
			}

			m_itemId = weaponRef;
			changeStat(7, 0, 0);
			return;
		}

		if (cmdIdx == 1) {
			const int element =
			    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0);
			if (element == 2) {
				changeStat(0x14, 0, 0);
				return;
			}
			if (element > 2) {
				if (element >= 4) {
					return;
				}
				changeStat(0x15, 0, 0);
				return;
			}
			if (element >= 0) {
				changeStat(8, 0, 0);
			}
			return;
		}

		const int itemId = caravan->DelCmdListAndItem(cmdIdx);
		const int kindOffset = itemId * 0x48;
		const unsigned short itemKind = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + kindOffset);
		if (itemKind == 0x125) {
			m_itemId = 0x220;
			changeStat(2, 0, 2);
			return;
		}
		if (itemKind > 0x124) {
			if (itemKind != 0x186) {
				if (itemKind > 0x185) {
					if (itemKind != 0x1F5) {
						return;
					}
					m_itemId = itemId;
					changeStat(2, 0, 0);
					return;
				}
				if (itemKind != 0x17D) {
					return;
				}
			}
			if (useItem(itemId) != 0) {
				caravan->GetNumCombi(party.unk6BC, 1);
			}
			return;
		}
		if (itemKind == 0xDF) {
			m_itemId = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + kindOffset + 10);
			changeStat(2, 0, 0);
			return;
		}
		if (itemKind < 0xDF) {
			if (itemKind != 1) {
				return;
			}
			int weaponItem;
			int weaponRef;
			caravan->GetCurrentWeaponItem(weaponItem, weaponRef);
			if (weaponItem != caravan->GetIdxCmdList() || weaponRef != itemId) {
				*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6D4) = caravan->GetIdxCmdList();
				party.weaponRef = itemId;
				party.commandFlagBits.flag20 = 1;
				changeStat(0x0F, 0, 0);
				return;
			}
			m_itemId = itemId;
			changeStat(7, 0, 0);
			return;
		}
		if (itemKind != 0x100) {
			return;
		}
		if (itemId == 0x103) {
			if (Math.Rand(3) == 0) {
				ClearAllSta();
				setSta(0x1B, 900);
				caravan->GetNumCombi(party.unk6BC, 1);
				return;
			}
			m_itemId = 0x103;
			changeStat(2, 0, 2);
			return;
		}
		m_itemId = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + kindOffset + 10);
		changeStat(2, 0, 0);
		return;
	}

	if ((getPadTrigForSlot(padSlot) & 0x200) == 0) {
		return;
	}
	if (!secondaryAvailable) {
		return;
	}

	if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(&m_weaponNodeFlags)[1]) << 24) & 0xC0000000) >> 31) != 0) &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x63C)) << 24) & 0xC0000000) >> 31) != 0) &&
	    caravan->m_hp != 0 &&
	    ringCommand != -1 &&
	    secondaryCommand == 6) {
		int weaponItem = 0;
		int weaponRef = 0;
		caravan->GetCurrentWeaponItem(weaponItem, weaponRef);
		m_itemId = weaponRef;
		changeStat(1, 0, 0);
	} else if (secondaryCommand == 4) {
		carry(0, party.target, 0);
	} else if (static_cast<unsigned int>(secondaryCommand - 2) <= 1 || secondaryCommand == 0x17) {
		rotTarget(reinterpret_cast<CGPrgObj*>(party.target));
		changeStat(0x0E, 0, 0);
		*reinterpret_cast<CGPartyObj**>(reinterpret_cast<unsigned char*>(party.target) + 0x550) = this;
		reinterpret_cast<CGPrgObj*>(party.target)->changeStat(0x0E, 0, 0);

		int itemIdx = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504);
		int kind = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemIdx * 0x48);
		int kindClass;
		if (kind == 0x125) {
			kindClass = 0;
		} else if (kind > 0x125) {
			kindClass = (kind == 0x190) ? 1 : 2;
		} else if (kind == 0x100 || kind == 1) {
			kindClass = 0;
		} else {
			kindClass = 2;
		}

		if (kindClass == 0 || kindClass == 2) {
			int addedItem;
			if (itemIdx >= 0x9F && itemIdx <= 0xFF) {
				caravan->AddTmpArtifact(itemIdx, &addedItem);
				System.Printf(const_cast<char*>(msgBase + 0x2C0), *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504));
			} else {
				caravan->AddItem(static_cast<short>(itemIdx), &addedItem);
				System.Printf(const_cast<char*>(msgBase + 0x2E0), *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504));
			}
			if (kindClass == 0 && caravan->CanAddComList(1) != 0) {
				int addedSlot;
				caravan->AddComList(static_cast<short>(addedItem), &addedSlot);
				System.Printf(const_cast<char*>(msgBase + 0x2F8), addedItem, addedSlot);
			}
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(party.target) + 0x560) != 1) {
				bonus(4, *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504), 0);
			}
		} else if (itemIdx == 0x190) {
			bonus(5, 0x190, 0);
			System.Printf(const_cast<char*>(msgBase + 0x324), *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x558));
			caravan->AddGil(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x558));
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(party.target) + 0x560) != 1) {
				bonus(4, *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504), 0);
			}
		}
	}

	party.flags.commandActive = 1;
	CGObject* tgt = party.target;
	CFlatRuntime::CStack stack[2];
	stack[0].m_word = secondaryCommand;
	stack[1].m_word = tgt != nullptr ? *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(tgt) + 0x30) : 0;
	gCFlatRuntime().SystemCall(this, 2, 0x14, 2, stack, 0);
	if (secondaryCommand == 5) {
		carry(1, static_cast<CGObject*>(0), 0);
	} else if (secondaryCommand == 7 || secondaryCommand == 8) {
		carry(2, static_cast<CGObject*>(0), 0);
	}
#undef padSlot
#undef caravan
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::callCommandScript(int mode, CGObject* target)
{
	PartyData(this).target = target;

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
#define script reinterpret_cast<unsigned char*>(m_scriptHandle)

	if (*reinterpret_cast<unsigned short*>(script + 0x1C) != 0 &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 24) & 0xC0000000) >> 31) != 0 ||
	     static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 27) & 0xC0000000) >> 31) != 0) &&
	    static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(m_weaponNodeFlagBytes.m_flags1) << 24) & 0xC0000000) >> 31) != 0) {

	const Vec* chalicePos = reinterpret_cast<Vec*>(Game.unk_flat3_0xc7d0 + 0x15C);
	float chaliceDist = PSVECDistance(&m_worldPosition, chalicePos);
	if (FLOAT_80331b00 * Game.unkFloat_0xca10 < chaliceDist ||
	    static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 27) & 0xC0000000) >> 31) != 0) {
		if (m_unk688 != 2) {
			deletePSlotBit(0x200);
			CFlat.ResetParticleWork(1, m_particleSlots[9]);
			CFlat.SetParticleWorkTrace(reinterpret_cast<CFlatRuntime::CObject*>(Game.unk_flat3_0xc7d0));
			CFlat.SetParticleWorkBind(this);
			CFlat.PutParticleWork();
		}
		m_unk688 = 2;
	} else {
		deletePSlotBit(0x200);
		if (FLOAT_80331a74 * Game.unkFloat_0xca10 <= chaliceDist) {
			int flagFrame = *reinterpret_cast<int*>(&m_flagBits);
			if (flagFrame % 4 == 0) {
				playSe3D(0x1E, 0x32, 0x96, 0, 0);
				CFlat.ResetParticleWork(2, 0);
				CFlat.SetParticleWorkPos(m_worldPosition, m_rotBaseY);
				CFlat.SetParticleWorkTrace(reinterpret_cast<CFlatRuntime::CObject*>(Game.unk_flat3_0xc7d0));
				CFlat.SetParticleWorkBind(this);
				CFlat.PutParticleWork();
			}
			m_unk688 = 1;
		} else {
			m_unk688 = 0;
		}
	}

	if (m_unk688 == 0 &&
	    static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 27) & 0xC0000000) >> 31) == 0) {
		int healCount = 0;
		if (PartyData(this).carryObject == reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0)) {
			if (isFrameInterval(*reinterpret_cast<int*>(&m_flagBits), *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 4))) {
				healCount = 1;
			}
		} else {
			if (isFrameInterval(*reinterpret_cast<int*>(&m_flagBits), *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 6))) {
				healCount = 1;
			}
		}
		const unsigned int periodicHeal = script[0xBDC];
		if (periodicHeal != 0 && isFrameInterval(*reinterpret_cast<int*>(&m_flagBits), periodicHeal)) {
			healCount += 1;
		}
		if (healCount != 0) {
			addHp(healCount, static_cast<CGPrgObj*>(0));
		}
	} else if (m_unk688 == 2) {
		unsigned char* script9 = reinterpret_cast<unsigned char*>(m_scriptHandle[9]);
		unsigned int damageInterval = *reinterpret_cast<unsigned short*>(script9 + 0xF4);
		if ((*reinterpret_cast<unsigned int*>(script + 0x3B0) & 0x2000) != 0) {
			damageInterval += *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 8);
		}
		if (isFrameInterval(*reinterpret_cast<int*>(&m_flagBits), damageInterval)) {
			playSe3D(0x19, 0x32, 0x96, 0, 0);
			if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(CFlatGameFlags()) << 26) & 0xC0000000) >> 31) == 0) {
				addHp(-1, static_cast<CGPrgObj*>(0));
			}
		}
	}
		return;
	}

	if (m_unk688 != 0) {
		deletePSlotBit(0x200);
		m_unk688 = 0;
	}
#undef script
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
	if (m_scriptHandle == nullptr) {
		return;
	}

	PartyObjOverlay& party = PartyData(this);

	switch (m_lastStateId) {
	case 0:
		if (m_stateFrame == 0) {
			if (party.flags.flag02) {
				reqAnim(0x27, 0, 0);
				party.flags.flag02 = 0;
			} else {
				reqAnim(-1, 0, 0);
			}
		}
		if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(party.partyFlags) << 24) & 0xC0000000) >> 31) != 0) ||
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) != 0) ||
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x50) != 0) ||
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x44) != 0)) {
			m_weaponNodeFlagAll.m_bits1.m_menuReady = 0;
			m_unk63CBits.m_bit80 = 0;
		} else {
			m_weaponNodeFlagAll.m_bits1.m_menuReady = 1;
			m_unk63CBits.m_bit80 = 1;
		}
		unsigned char* onFrameSelf = reinterpret_cast<unsigned char*>(this);
		if (((DbgMenuPcs.GetDbgFlagsRaw() & 8) != 0) ||
		    ((Game.unk_flat3_0xc7d0 != 0) &&
		     (Joybus.GetCtrlMode(static_cast<char>(m_animStateMisc)) == 1) &&
		     (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(onFrameSelf[0x63C]) << 24) & 0xC0000000) >> 31) != 0) &&
		     (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(onFrameSelf[0x9B]) << 24) & 0xC0000000) >> 31) != 0) &&
		     (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(onFrameSelf[0x9B]) << 25) & 0xC0000000) >> 31) != 0) &&
		     (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(party.partyFlags) << 24) & 0xC0000000) >> 31) == 0))) {
			if ((FLOAT_80331a74 * Game.unkFloat_0xca10 < m_targetDist) &&
			    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E) == 0) &&
			    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x50) == 0) &&
			    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x44) == 0) &&
			    (Game.m_gameWork.m_bossArtifactStageIndex != 0x17)) {
				CVector worldPos(m_worldPosition);
				const CVector& chalicePos = CVector(*reinterpret_cast<Vec*>(Game.unk_flat3_0xc7d0 + 0x15C));
				CVector diff;
				PSVECSubtract((Vec*)&chalicePos, reinterpret_cast<Vec*>(&worldPos), reinterpret_cast<Vec*>(&diff));
				Vec moveVec;
				moveVec.x = diff.x;
				moveVec.y = diff.y;
				moveVec.z = diff.z;
				moveVector(&moveVec, m_moveBaseSpeed, 0x0F);
			}
		}
		if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(m_weaponNodeFlagBytes.m_flags1) << 24) & 0xC0000000) >> 31) != 0) &&
		    Game.m_gameWork.m_menuStageMode != 0 &&
		    reinterpret_cast<int*>(m_scriptHandle)[0xED] == 0 &&
		    Game.m_partyObjArr[1] != nullptr &&
		    Game.m_partyObjArr[1]->m_lastStateId == 0) {
			unsigned short held = getPadHeldForSlot(static_cast<signed char>(m_animStateMisc));
			unsigned short up = getPadButtonUpForSlot(static_cast<char>(m_animStateMisc));
			if ((up & 0x400) != 0) {
				if (sGhostMogMenuWork.holdTimer < 10 &&
				    party.carryObject != reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0)) {
					sGhostMogMenuWork.flags.carryActive = (party.carryObject != nullptr);
				}
			} else if ((held & 0x400) != 0) {
				sGhostMogMenuWork.holdTimer++;
				if (sGhostMogMenuWork.holdTimer >= 10 && sGhostMogMenuWork.mood == 0) {
					sGhostMogMenuWork.mood = 2;
				}
			} else {
				sGhostMogMenuWork.holdTimer = 0;
			}
		}
		break;
	case 6:
		statCharge();
		break;
	case 7:
		if (m_stateFrame == 0) {
			party.unk6D0 = 0;
		}
		if ((getPadHeldForSlot(static_cast<signed char>(m_animStateMisc)) & 0x100) == 0) {
			changeStat(1, 0, 0);
		} else {
			party.unk6D0++;
			if (party.unk6D0 >= 6) {
				changeStat(6, 0, 0);
			} else {
				if ((getPadTrigForSlot(static_cast<signed char>(m_animStateMisc)) & 0x200) != 0) {
					changeStat(0, 0, 0);
				}
			}
		}
		break;
	case 0x0B:
		if (Game.m_gameWork.m_menuStageMode != 0 &&
		    Game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
		    (static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
		    reinterpret_cast<int*>(m_scriptHandle)[0xED] != 0) {
			if (m_stateFrame == 0) {
				CancelMove(1);
				FLOAT_8032EE78 = m_targetDist - FLOAT_80331ac4;
				FLOAT_8032EE7C = *reinterpret_cast<float*>(Game.unk_flat3_0xc7d0 + 0x160) - m_worldPosition.y;
			}

			if (m_stateFrame <= 0x0B) {
				const float phase = sinf((FLOAT_80331AB8 * static_cast<float>(m_stateFrame)) / FLOAT_80331AC0);
				m_extraMoveVec.x = FLOAT_8032EE78 * phase * sinf(m_rotBaseY);
				m_extraMoveVec.z = FLOAT_8032EE78 * phase * cosf(m_rotBaseY);
				m_extraMoveVec.y = FLOAT_8032EE7C * phase + FLOAT_80331A98;
			}
		}
		if (m_stateFrame == 0) {
			reqAnim(0x0D, 0, 0);
			playSe3D(0x22, 0x32, 0x96, 0, 0);
		}
		if (isLoopAnim() != 0) {
			short mapId = *reinterpret_cast<short*>(&m_lastMapIdHit);
			if (party.carryObject == nullptr) {
				if (*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
					if (mapId == 1) {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					}
				} else if (mapId == 1) {
					SetAnimSlot(0, 0);
					SetAnimSlot(1, 1);
				} else {
					SetAnimSlot(0x25, 0);
					SetAnimSlot(0x30, 1);
				}
			} else if (CFlatItemCarryMode() == 0) {
				if (mapId == 1) {
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
			changeStat(0, 0, 0);
			m_extraMoveVec.x = FLOAT_80331a78;
			m_extraMoveVec.z = FLOAT_80331a78;
		}
		break;
	case 0x0C:
	case 0x0D:
	case 0x1B:
		statPut();
		break;
	case 0x0E:
		if (m_stateFrame == 0) {
			reqAnim(9, 0, 0);
			playSe3D(0x1F, 0x32, 0x96, 0, 0);
		}
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
		}
		break;
	case 0x0F:
		if (m_stateFrame == 0) {
			reqAnim(0x29, 0, 0);
		}
		if (m_stateFrame == 4) {
			int weaponItem = party.weaponRef;
			int weaponRef = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x6D4);
			if (weaponItem <= 0) {
				LoadWeapon(-1, 0);
			} else {
				unsigned short itemKind = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + weaponItem * 0x48 + 2);
				LoadWeapon(itemKind & 0xFFF, itemKind >> 12);
			}
			party.weaponItem = weaponRef;
			party.pendingWeaponItem = weaponItem;
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->SetCurrentWeaponIdx(party.weaponItem);
			party.commandFlagBits.flag20 = 0;
		}
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
		}
		break;
	case 0x13:
		if (m_stateFrame == 0) {
			damageDelete();
			reqAnim(0x21, 0, 0);
		}
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
		}
		break;
	case 0x14:
		switch (m_subState) {
		case 0:
			if (m_subFrame == 0) {
				playSe3D(0x2F, 0x32, 0x96, 0, 0);
				reqAnim(0x15, 0, 0);
			}
			if (isLoopAnim() != 0) {
				changeSubStat(1);
			}
			break;
		case 1:
			if (m_subFrame == 0) {
				m_alpha = FLOAT_80331ABC;
				reqAnim(0x16, 1, 0);
				enableDamageCol(0);
			}
			if ((getPadHeldForSlot(static_cast<signed char>(m_animStateMisc)) & 0x100) == 0) {
				if (m_subFrame >= 0x19) {
					playSe3D(0x30, 0x32, 0x96, 0, 0);
				}
				m_alpha = kMonObjOne;
				changeSubStat(2);
				enableDamageCol(1);
			}
			break;
		case 2:
			if (m_subFrame == 0) {
				reqAnim(0x17, 0, 0);
			}
			if (isLoopAnim() != 0) {
				changeStat(0, 0, 0);
			}
			break;
		}
		break;
	case 0x15:
		if (m_stateFrame == 0) {
			playSe3D(0x40, 0x32, 0x96, 0, 0);
			reqAnim(0x15, 0, 0);
			enableDamageCol(0);
		}
		if (m_stateFrame == 3 && Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
			moveVectorHRot(FLOAT_80331AB8 + m_rotTargetY, FLOAT_80331a78, kMonObjOne, 10);
		}
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
			enableDamageCol(1);
		}
		break;
	case 0x1A:
		statKorobi();
		break;
	case 0x20:
		if (m_stateFrame == 0) {
			reqAnim(0x31, 0, 0);
		} else if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
		}
		break;
	case 0x22: {
		unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
		if (m_stateFrame == 0) {
			if (party.flags.flag04) {
				if (*reinterpret_cast<unsigned short*>(script + 0x1C) == 0) {
					addHp(*reinterpret_cast<unsigned short*>(script + 0x1A), static_cast<CGPrgObj*>(0));
				}
				party.flags.flag04 = 0;
			}
			enableDamageCol(1);
			short mapId = *reinterpret_cast<short*>(&m_lastMapIdHit);
			if (party.carryObject == nullptr) {
				if (*reinterpret_cast<short*>(script + 0x1C) == 0) {
					if (mapId == 1) {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					}
				} else if (mapId == 1) {
					SetAnimSlot(0, 0);
					SetAnimSlot(1, 1);
				} else {
					SetAnimSlot(0x25, 0);
					SetAnimSlot(0x30, 1);
				}
			} else if (CFlatItemCarryMode() == 0) {
				if (mapId == 1) {
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
			if (m_currentAnimSlot == 6) {
				reqAnim(0x26, 0, 0);
			} else {
				reqAnim(0x27, 0, 0);
			}
			if (*reinterpret_cast<unsigned short*>(script + 0x1C) != 0) {
				endPSlotBit(0x10000);
				m_alpha = kMonObjOne;
				m_bgColMask |= 0x1000E;
				*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x48) = 0x5A;
			} else {
				m_alpha = FLOAT_80331A7C;
				m_bgColMask &= 0xFFFEFFF1;
				void* port = m_scriptHandle[0xED];
				endPSlotBit(0x10000);
				putParticle(reinterpret_cast<int>(port) + 3U | 0x100, m_particleSlots[16], this, kMonObjOne, 0);
				playSe3D(0x2D, 0x32, 0x96, 0, 0);
			}
		} else if (isLoopAnim() != 0) {
			if (*reinterpret_cast<unsigned short*>(script + 0x1C) != 0) {
				party.flags.flag02 = 1;
			}
			changeStat(0, 0, 0);
		}
		break;
	}
	default:
		break;
	}

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
 * PAL Address: 0x80120A90
 * PAL Size: 228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::enableAttackCol(int enabled, int isFriendly, int hitMask)
{
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (enabled != 0) {
		resetIgnoreHit();
		bool col0Enabled = false;
		if (isFriendly == 0 || (hitMask & 1) != 0) {
			col0Enabled = true;
		}
		*reinterpret_cast<unsigned int*>(self + 0x20C) = col0Enabled != false;
		bool col1Enabled = false;
		if (isFriendly != 0 && (hitMask & 2) != 0) {
			col1Enabled = true;
		}
		*reinterpret_cast<unsigned int*>(self + 0x23C) = col1Enabled != false;
		bool col2Enabled = false;
		if (isFriendly != 0 && (hitMask & 4) != 0) {
			col2Enabled = true;
		}
		*reinterpret_cast<unsigned int*>(self + 0x26C) = col2Enabled != false;
	} else {
		*reinterpret_cast<int*>(self + 0x20C) = 0;
		*reinterpret_cast<int*>(self + 0x23C) = 0;
		*reinterpret_cast<int*>(self + 0x26C) = 0;
	}
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
	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		hitMask = 8;
	}

	if (onOff != 0 &&
	    (Game.m_gameWork.m_menuStageMode == 0 ||
	     Game.m_gameWork.m_bossArtifactStageIndex >= 0x0F ||
	     (static_cast<unsigned short>(GetCID()) & 0x6D) != 0x6D ||
	     *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) == 0)) {
		*reinterpret_cast<unsigned int*>(self + 0x384) = hitMask;
		*reinterpret_cast<unsigned int*>(self + 0x3AC) = hitMask;
	} else {
		*reinterpret_cast<unsigned int*>(self + 0x384) = 0;
		*reinterpret_cast<unsigned int*>(self + 0x3AC) = 0;
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
	switch (state) {
	case 7:
		break;
	case -20:
		state = -1;
		break;
	default:
		return CGCharaObj::getReplaceStat(state);
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
	switch (m_subState) {
	case 0:
		if (m_subFrame == 0) {
			m_comboFramePrev = 0;
			reqAnim(m_attackAnimId, 0, 0);
			putParticle(0x210, m_particleSlots[3], reinterpret_cast<CGObject*>(this), kMonObjOne, 0x7EE);
		}
		if (isLoopAnim() != 0) {
			changeSubStat(1);
			return;
		}
		break;
	case 1:
		if (m_subFrame == 0) {
			reqAnim(m_unk554, 1, 0);
		}
		if (m_comboState == 0 && m_subFrame > m_unk68C) {
			putTargetParticle(0, 1);
			m_comboState = 1;
		}
		if (m_comboState != 0) {
			checkTargetParticle();
		}
		if (m_itemId == 0x206) {
			int window = m_unk68C;
			int counter = m_comboFramePrev;
			if (counter == window * 3) {
				putParticle(0x578, 0, reinterpret_cast<CGObject*>(this), kMonObjOne, 0x80D);
			} else if (counter == window << 1) {
				putParticle(0x577, 0, reinterpret_cast<CGObject*>(this), kMonObjOne, 0x80D);
			}
		}
		m_comboFramePrev++;
		break;
	case 2: {
		if (m_subFrame == 0) {
			endPSlotBit(8);
			bonus(0x18, 0, 0);
		}
		if (m_subFrame == 5 && m_comboItemState >= 0) {
			endPSlotBit(0x20);
			CFlat.ResetParticleWork(
			    (m_comboItemState + *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) * 5 + 0x1C) | 0x400,
			    m_particleSlots[5]);
			CFlat.SetParticleWorkBind(reinterpret_cast<CFlatRuntime::CObject*>(this));
			CFlat.PutParticleWork();
			playSe3D(m_comboItemState + 0x7EB, 0x32, 0x96, 0, 0);
		}

		int phase;
		if (m_comboItemState != -1) {
			phase = m_subFrame - 0x10;
		} else {
			phase = m_subFrame;
		}
		int itemType =
		    *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + m_itemId * 0x48 + 10) & 0xFF;

		if (phase == 0) {
			if (m_comboLinkCount != 0) {
				sendCombiToScript(reinterpret_cast<CGCharaObj*>(m_comboScriptArg), m_comboScriptMode, m_subFrame);
			}
			resetIgnoreHit();
			putParticleFromItem(m_itemId, 0, m_particleSlots[0], static_cast<Vec*>(0));
			putParticleFromItem(m_itemId, 1, m_particleSlots[0], static_cast<Vec*>(0));
			putParticleFromItem(m_itemId, 2, m_particleSlots[0], static_cast<Vec*>(0));
			reqAnim(m_unk558, 0, 0);
			endPSlotBit(0x10);
			int item = m_itemId;
			if (item == 0x1FC || item == 0x23D) {
				int base;
				switch (item) {
				case 0x23D:
					base = 0x6F;
					break;
				case 0x1FC:
					base = 0x1B;
					break;
				}
				if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) > 1) {
					addHp(-1, static_cast<CGPrgObj*>(0));
				}
				putParticle((base + *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2)) | 0x500, 0,
				    reinterpret_cast<CGObject*>(this), kMonObjOne, 0);
			}
		}

		if (phase == *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + m_itemId * 0x48 + 0x20)) {
			putParticleFromItem(m_itemId, 3, m_particleSlots[0], static_cast<Vec*>(0));
		}

		int entry = (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E2) +
		             *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) * 2) * 0x1CA;
		int row = (static_cast<int>(*reinterpret_cast<unsigned short*>(
		               Game.unkCFlatData0[2] + m_itemId * 0x48 + 10)) >> 8) * 0x42;
		unsigned short* table =
		    reinterpret_cast<unsigned short*>(Game.unk_flat3_field_30_0xc7e0 + entry + row + 0x36);

		unsigned short* p = table;
		for (int i = 0; i < 5; i++, p += 6) {
			if (phase == p[3] && Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
				unsigned int dist = (p[4] - p[3]) + 1;
				if (i == 0 && (itemType == 2 || itemType == 3)) {
					Vec delta;
					PSVECSubtract(&m_comboCenter, &m_worldPosition, &delta);
					float mag = PSVECMag(&delta);
					CVector dest(m_comboCenter);
					if ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + m_itemId * 0x48 + 0x32) & 0x10) != 0) {
						unsigned int maxReach = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x70);
						if (static_cast<float>(maxReach) < mag) {
							const CVector& dir = CVector(delta);
							CVector scaled;
							PSVECScale((Vec*)&dir, reinterpret_cast<Vec*>(&scaled), mag - static_cast<float>(maxReach));
							Vec scaledCopy;
							scaledCopy.x = scaled.x;
							scaledCopy.y = scaled.y;
							scaledCopy.z = scaled.z;
							CVector unit;
							PSVECScale(&scaledCopy, reinterpret_cast<Vec*>(&unit), kMonObjOne / mag);
							Vec unitCopy;
							unitCopy.x = unit.x;
							unitCopy.y = unit.y;
							unitCopy.z = unit.z;
							const CVector& origin = CVector(m_worldPosition);
							CVector sum;
							PSVECAdd((Vec*)&origin, reinterpret_cast<Vec*>(&unitCopy), reinterpret_cast<Vec*>(&sum));
							dest.x = sum.x;
							dest.y = sum.y;
							dest.z = sum.z;
							mag = mag - static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x70));
						} else {
							mag = FLOAT_80331a78;
						}
					}
					if (FLOAT_80331a78 != mag) {
						Move(reinterpret_cast<Vec*>(&dest), mag / static_cast<float>(static_cast<int>(dist)), dist, 1, 1, 0, 1);
					}
				} else {
					moveVectorRot(m_rotTargetY, FLOAT_80331a78, FLOAT_80331ADC * static_cast<float>(p[5]),
					    dist);
				}
			}
			if (phase == p[1]) {
				enableAttackCol(1, 1, p[0]);
			}
			if (phase == p[2]) {
				enableAttackCol(0, 0, 0);
			}
		}

		if (phase >= 0 && isLoopAnim() != 0) {
			changeStat(0, 0, 0);
			return;
		}

		unsigned int limitFrames = table[0x1E];
		if (limitFrames != 0) {
			float angLimit = FLOAT_80331AE0 * static_cast<float>(limitFrames);
			if (phase == table[0x1F]) {
				CVector worldPos(m_worldPosition);
				const CVector& center = CVector(m_comboCenter);
				CVector diff;
				PSVECSubtract((Vec*)&center, reinterpret_cast<Vec*>(&worldPos), reinterpret_cast<Vec*>(&diff));
				float horizSq = diff.z * diff.z + diff.x * diff.x;
				float horiz = (horizSq > FLOAT_80331a78) ? sqrtf(horizSq) : horizSq;
				if (FLOAT_80331a78 != diff.y && FLOAT_80331a78 != horiz) {
					float ang = -static_cast<float>(atan2(diff.y, horiz));
					float clamped = -angLimit;
					if (ang < -angLimit) {
						clamped = -angLimit;
					} else {
						clamped = ang;
						if (angLimit < ang) {
							clamped = angLimit;
						}
					}
					*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x4FC) = clamped;
				}
			} else if (phase == table[0x20]) {
				*reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x4FC) = FLOAT_80331a78;
			}
		}
		break;
	}
	}

	if (m_subState <= 1) {
		int slot = static_cast<signed char>(m_animStateMisc);
		if ((getPadHeldForSlot(slot) & 0x100) == 0) {
			if (m_subState == 0 || (m_subState == 1 && m_comboState == 0)) {
				changeStat(0, 0, 0);
			} else {
				m_comboFrame++;
			}
		} else if ((getPadHeldForSlot(slot) & 0x200) != 0) {
			changeStat(0, 0, 0);
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::statAttackSel()
{
	if (m_subState == 0 && m_subFrame == 0) {
		putTargetParticle(0, 1);
	}

	unsigned short trig = getPadTrigForSlot(static_cast<signed char>(m_animStateMisc));
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
extern "C" float dstTargetRot__8CGPrgObjFP8CGPrgObj(CGPrgObj*, CGPrgObj*);

CGPrgObj* CGPartyObj::getBestAngleObject(float range, float)
{
	CGPrgObj* best = 0;
	float bestAbsAngle = 0.0f;

	for (CGObject* obj = CFlat.FindGObjFirst(); obj != 0; obj = CFlat.FindGObjNext(obj)) {
		const unsigned int flags = obj->m_attrFlags;
		if ((flags & 0x18) == 0) {
			continue;
		}

		if ((flags & 0x08) != 0) {
			if ((obj->m_displayFlags & 1) == 0) {
				continue;
			}
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(obj->m_scriptHandle) + 0x1C) == 0) {
				continue;
			}
		}

		if (obj->m_worldPosition.x == m_worldPosition.x) {
			continue;
		}
		if (obj->m_worldPosition.z == m_worldPosition.z) {
			continue;
		}

		float radius = obj->m_bodyEllipsoidRadius + (range + m_bodyEllipsoidRadius);
		if (m_worldPosition.x - radius <= obj->m_worldPosition.x &&
		    m_worldPosition.z - radius <= obj->m_worldPosition.z &&
		    m_worldPosition.x + radius >= obj->m_worldPosition.x &&
		    m_worldPosition.z + radius >= obj->m_worldPosition.z) {
			float yRange = FLOAT_80331ad4 * obj->m_bodyEllipsoidRadius;
			if (m_worldPosition.y + yRange >= obj->m_worldPosition.y &&
			    m_worldPosition.y - yRange <= obj->m_worldPosition.y) {
				Vec diff;
				PSVECSubtract(&obj->m_worldPosition, &m_worldPosition, &diff);
				diff.y = 0.0f;
				float distSq = PSVECSquareMag(&diff);
				if (0.0f < distSq && distSq < radius * radius) {
					float absAngle = fabsf(dstTargetRot__8CGPrgObjFP8CGPrgObj(this, reinterpret_cast<CGPrgObj*>(obj)));
					if (absAngle > bestAbsAngle) {
						bestAbsAngle = absAngle;
						best = reinterpret_cast<CGPrgObj*>(obj);
					}
				}
			}
		}
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
		party.commandFlagBits.commandActive = 0;
		party.commandFlagBits.flag40 = 0;

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

	if (chain > 0 && m_stateFrame == *reinterpret_cast<unsigned short*>(attackEntry + 4) && Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
		const float stepSpeed = FLOAT_80331ADC * static_cast<float>(*reinterpret_cast<unsigned short*>(attackEntry + 8));
		moveVectorRot(m_rotTargetY, FLOAT_80331a78, stepSpeed,
		    (*reinterpret_cast<unsigned short*>(attackEntry + 6) - *reinterpret_cast<unsigned short*>(attackEntry + 4)) + 1);
	}

	if (m_stateFrame >= *reinterpret_cast<unsigned short*>(attackEntry + 0x0C) &&
	    m_stateFrame <= *reinterpret_cast<unsigned short*>(attackEntry + 0x0E)) {
		if ((getPadTrigForSlot(static_cast<signed char>(m_animStateMisc)) & 0x100) != 0) {
			party.commandFlagBits.commandActive = 1;
		}
	} else {
		if ((getPadTrigForSlot(static_cast<signed char>(m_animStateMisc)) & 0x100) != 0) {
			party.commandFlagBits.flag40 = 1;
		}
	}

	if (m_stateFrame == *reinterpret_cast<unsigned short*>(attackEntry + 0x10)) {
		if (party.commandFlagBits.commandActive != 0 && party.commandFlagBits.flag40 == 0 && party.unk6CC < 2) {
			party.attackSel = party.unk6CC + 1;
			changeStat(1, 0, 0);
			return;
		}
	}

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (m_stateFrame == *reinterpret_cast<int*>(self + 0x638)) {
		m_unk63CBits.m_bit80 = 1;
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
		unsigned short trig;
		int padSlot = static_cast<signed char>(m_animStateMisc);
		bool suppressInput = (Pad.m_debugPadLock != 0) || ((padSlot == 0) && (Pad.m_debugPadPort != -1));
		if (suppressInput) {
			trig = 0;
		} else {
			int selectedPort = Pad.m_debugPadPort;
			unsigned int padIndex =
			    padSlot &
			    ~((int)~(selectedPort - padSlot | padSlot - selectedPort) >> 31);
			trig = Pad.GetPadInputs()[padIndex].button[0];
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
	putParticle(0x153, 0, reinterpret_cast<CGObject*>(this), kMonObjOne, 0);
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
	PartyObjOverlay& party = PartyData(this);
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if (doInit != 0) {
		party.flags.flag40 = targetSide;
		party.flags.flag10 = 0;

		Vec rayDir;
		rayDir.x = sinf(m_rotTargetY) * FLOAT_80331A98;
		rayDir.y = FLOAT_80331a78;
		rayDir.z = cosf(m_rotTargetY) * FLOAT_80331A98;
		bool bossStage = false;
		bool bossCid = false;
		bool bossTarget = false;
		if ((Game.m_gameWork.m_menuStageMode != 0) &&
		    (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F)) {
			bossStage = true;
		}
		if (bossStage && ((__cntlzw(0x6D - (static_cast<unsigned short>(GetCID()) & 0x6D)) >> 5 & 0xFF) != 0)) {
			bossCid = true;
		}
		if (bossCid && (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) != 0)) {
			bossTarget = true;
		}
		float radius;
		if (bossTarget) {
			radius = FLOAT_80331AB0;
		} else {
			radius = FLOAT_80331A88;
		}

		CVector startOffset(FLOAT_80331a78, FLOAT_80331ad0, FLOAT_80331a78);
		const CVector& worldPos = CVector(m_worldPosition);
		CVector startPos;
		PSVECAdd((Vec*)&worldPos, reinterpret_cast<Vec*>(&startOffset), reinterpret_cast<Vec*>(&startPos));

		CMapCylinder hitCylinder(FLOAT_80331a9c, FLOAT_80331aa0);
		hitCylinder.m_bottom.x = startPos.x;
		hitCylinder.m_bottom.y = startPos.y;
		hitCylinder.m_bottom.z = startPos.z;
		hitCylinder.m_axis = rayDir;
		hitCylinder.m_radius = radius;

		if (MapMng.CheckHitCylinderNear(&hitCylinder, &rayDir, 0x30) != 0) {
			CMapObj* hitObj = getMapHitObject();
			hitObj->CalcHitPosition(&m_comboCenter);
		} else {
			CVector startOffset2(FLOAT_80331a78, FLOAT_80331ad0, FLOAT_80331a78);
			const CVector& worldPos2 = CVector(m_worldPosition);
			CVector startPos2;
			PSVECAdd((Vec*)&worldPos2, reinterpret_cast<Vec*>(&startOffset2), reinterpret_cast<Vec*>(&startPos2));
			Vec startPosVec;
			startPosVec.x = startPos2.x;
			startPosVec.y = startPos2.y;
			startPosVec.z = startPos2.z;
			PSVECAdd(&startPosVec, &rayDir, &m_comboCenter);
		}
		const CVector& down = CVector(FLOAT_80331a78, FLOAT_80331acc, FLOAT_80331a78);
		CMapCylinder floorCylinder(FLOAT_80331a9c, FLOAT_80331aa0);
		floorCylinder.m_bottom = m_comboCenter;
		floorCylinder.m_axis = *(Vec*)&down;
		floorCylinder.m_radius = FLOAT_80331a78;
		if (MapMng.CheckHitCylinderNear(&floorCylinder, (Vec*)&down, 0x30) != 0) {
			CMapObj* hitObj = getMapHitObject();
			hitObj->CalcHitPosition(&m_comboCenter);
			CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
			Vec faceNormal;
			caravanWork->m_targetCursorPosA = m_comboCenter;
			hitObj->GetHitFaceNormal(&faceNormal);
			caravanWork->m_targetCursorPosB = faceNormal;
		}
		m_comboTarget = m_comboCenter;
	}

	endPSlotBit(0x10);
	CFlat.ResetParticleWork(((targetSide != 0) ? 4 : 0) +
	                                     *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) +
	                                     0x147 | 0x100,
	                                 m_particleSlots[4]);
	CFlat.SetParticleWorkPos(m_comboCenter, FLOAT_80331a78);
	CFlat.SetParticleWorkParam(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4), 0);
	CFlat.PutParticleWork();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::endTargetParticle()
{
	PartyObjOverlay& party = PartyData(this);
	party.partyFlags &= 0xAF;
	m_comboState = 0;
	m_comboFrame = 0;
	m_comboTarget = m_worldPosition;
	m_comboCenter = m_worldPosition;
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
	unsigned char result = 0;
	if ((m_lastStateId == 2 || m_lastStateId == 6) &&
	    (*reinterpret_cast<int*>(self + 0x668) != 0)) {
		result = 1;
	}

	return result;
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
	PartyObjOverlay& party = PartyData(this);
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	bool hasTarget = false;
	unsigned char result = 0;

	if (m_lastStateId == 2 || m_lastStateId == 6) {
		if (*reinterpret_cast<int*>(self + 0x668) != 0) {
			hasTarget = true;
		}
	}

	if (hasTarget) {
		unsigned char flags = party.partyFlags;
		if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(flags) << 25) & 0xC0000000) >> 31) != 0) {
			result = 1;
		}
	}

	return result;
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
	PartyObjOverlay& party = PartyData(this);
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	unsigned char flags = party.partyFlags;

	if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(flags) << 27) & 0xC0000000) >> 31) != 0) {
		putTargetParticle(static_cast<int>((static_cast<unsigned int>(flags) << 25) & 0xC0000000) >> 31, 0);
		party.flags.flag10 = 0;
	}

	CVector input;
	input.Identity();

	if ((Game.m_gameWork.m_menuStageMode == 0) ||
	    (Game.m_gameWork.m_bossArtifactStageIndex >= 0x0F) ||
	    ((static_cast<unsigned short>(GetCID()) & 0x6D) != 0x6D) ||
	    (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) == 0)) {
		if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x100) != 0) {
			input.x -= getPadLeftStickXForSlot(static_cast<signed char>(m_animStateMisc));
			input.z += getPadLeftStickYForSlot(static_cast<signed char>(m_animStateMisc));
		}

			if (input.x == 0.0f && input.z == 0.0f) {
				unsigned short held = getPadHeldForSlot(static_cast<signed char>(m_animStateMisc));
			if ((held & 1) != 0) {
				input.x += kMonObjOne;
			}
			if ((held & 2) != 0) {
				input.x -= kMonObjOne;
			}
			if ((held & 8) != 0) {
				input.z += kMonObjOne;
			}
			if ((held & 4) != 0) {
				input.z -= kMonObjOne;
			}
		}
	} else {
		CGPartyObj* leader = Game.m_partyObjArr[0];
		if ((leader->m_lastStateId == 2 || leader->m_lastStateId == 6) &&
		    leader->m_comboState != 0) {
			CVector leaderCenter(leader->m_comboCenter);
			const CVector& selfCenter = CVector(m_comboCenter);
			CVector subResult;
			PSVECSubtract((Vec*)&selfCenter, reinterpret_cast<Vec*>(&leaderCenter), reinterpret_cast<Vec*>(&subResult));
			Vec toLeaderTarget;
			toLeaderTarget.x = subResult.x;
			toLeaderTarget.y = subResult.y;
			toLeaderTarget.z = subResult.z;
			if (PSVECMag(&toLeaderTarget) > FLOAT_80331A98) {
				input.x = toLeaderTarget.x;
				input.z = toLeaderTarget.z;
			}
		}
	}

	if (input.x != 0.0f || input.z != 0.0f) {
#define targetPos (&m_comboCenter)
#define centerPos (&m_comboTarget)
		float maxRange;

		party.flags.flag20 = 1;
		input.Normalize();
		PSVECScale(reinterpret_cast<Vec*>(&input), reinterpret_cast<Vec*>(&input), FLOAT_80331ad4);

			float angle;
			if (isGhostPartyTargetMode(this)) {
				angle = FLOAT_80331AB8;
			} else {
				angle = CameraPcs.m_yaw;
			}

		float s = sin(angle);
		float c = cos(angle);
		float inX = input.x;
		float inZ = input.z;
		targetPos->x += inX * c - inZ * s;
		targetPos->z += inX * s + inZ * c;

		float dist = PSVECDistance(&m_worldPosition, targetPos);

		float zero = LoadFloat(FLOAT_80331a78);
		int scriptPtr = *reinterpret_cast<int*>(self + 0x58);
		if (*reinterpret_cast<int*>(self + 0x520) == 2) {
			unsigned int vNode = *reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(scriptPtr + 0x24) + 0x19A);
			unsigned int vItem = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<int*>(self + 0x560) * 0x48 + 0x30);
			int vFlag;
			if ((*reinterpret_cast<unsigned int*>(scriptPtr + 0x3B0) & 0x4000) == 0) {
				vFlag = 0;
			} else {
				vFlag = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x0A);
			}
			maxRange = zero + (static_cast<float>(vItem) + static_cast<float>(vNode) + static_cast<float>(vFlag));
		} else {
			unsigned int vNode = *reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(scriptPtr + 0x24) + 0x19C);
			unsigned int vItem = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + *reinterpret_cast<int*>(self + 0x560) * 0x48 + 0x30);
			int vFlag;
			if ((*reinterpret_cast<unsigned int*>(scriptPtr + 0x3B0) & 0x8000) == 0) {
				vFlag = 0;
			} else {
				vFlag = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x0C);
			}
			maxRange = zero + (static_cast<float>(vItem) + static_cast<float>(vNode) + static_cast<float>(vFlag));
		}

		CVector worldPosV(m_worldPosition);
		const CVector& targetCenterV = CVector(*targetPos);
		CVector fromCenterResult;
		PSVECSubtract((Vec*)&targetCenterV, reinterpret_cast<Vec*>(&worldPosV), reinterpret_cast<Vec*>(&fromCenterResult));
		Vec fromCenter;
		fromCenter.x = fromCenterResult.x;
		fromCenter.y = fromCenterResult.y;
		fromCenter.z = fromCenterResult.z;
		if (dist > maxRange) {
			Vec scaled;
			PSVECScale(&fromCenter, &scaled, maxRange / dist);
			PSVECAdd(&m_worldPosition, &scaled, targetPos);
		}

		CVector targetCenterV2(*targetPos);
		const CVector& centerTargetV = CVector(*centerPos);
		CVector moveResult;
		PSVECSubtract(reinterpret_cast<Vec*>(&targetCenterV2), (Vec*)&centerTargetV, reinterpret_cast<Vec*>(&moveResult));
		Vec move;
		move.x = moveResult.x;
		move.y = moveResult.y;
		move.z = moveResult.z;
		int iter = 4;
		do {
			bool loopBossStage = false;
			bool loopBossCid = false;
			bool loopBossTarget = false;
			if ((Game.m_gameWork.m_menuStageMode != 0) &&
			    (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F)) {
				loopBossStage = true;
			}
			if (loopBossStage && ((__cntlzw(0x6D - (static_cast<short>(GetCID()) & 0x6D)) >> 5 & 0xFF) != 0)) {
				loopBossCid = true;
			}
			if (loopBossCid && (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) != 0)) {
				loopBossTarget = true;
			}
			float radius;
			if (loopBossTarget) {
				radius = FLOAT_80331AB0;
			} else {
				radius = FLOAT_80331A88;
			}

			CVector up(FLOAT_80331a78, FLOAT_80331ad0, FLOAT_80331a78);
			const CVector& centerForBottom = CVector(*centerPos);
			CVector bottomResult;
			PSVECAdd((Vec*)&centerForBottom, reinterpret_cast<Vec*>(&up), reinterpret_cast<Vec*>(&bottomResult));
			Vec bottom;
			bottom.x = bottomResult.x;
			bottom.y = bottomResult.y;
			bottom.z = bottomResult.z;

			CMapCylinder hitCylinder(FLOAT_80331a9c, FLOAT_80331aa0);
			hitCylinder.m_bottom = bottom;
			hitCylinder.m_top = move;
			hitCylinder.m_radius = radius;

			if (MapMng.CheckHitCylinderNear(&hitCylinder, &move, 0x30) == 0) {
				break;
			}
			if (iter == 1) {
				move.x = FLOAT_80331a78;
				move.y = FLOAT_80331a78;
				move.z = FLOAT_80331a78;
			} else {
				getMapHitObject()->CalcHitSlide(&move, FLOAT_80331A98);
			}
			iter--;
		} while (iter > 0);

		CVector upFinal(FLOAT_80331a78, FLOAT_80331ad0, FLOAT_80331a78);
		const CVector& centerFinal = CVector(*centerPos);
		CVector addUpResult;
		PSVECAdd((Vec*)&centerFinal, reinterpret_cast<Vec*>(&upFinal), reinterpret_cast<Vec*>(&addUpResult));
		Vec centerPlusUp;
		centerPlusUp.x = addUpResult.x;
		centerPlusUp.y = addUpResult.y;
		centerPlusUp.z = addUpResult.z;
		PSVECAdd(&centerPlusUp, &move, targetPos);

		const CVector& down = CVector(FLOAT_80331a78, FLOAT_80331acc, FLOAT_80331a78);
		CMapCylinder floorCylinder(FLOAT_80331a9c, FLOAT_80331aa0);
		floorCylinder.m_bottom.x = targetPos->x;
		floorCylinder.m_bottom.y = targetPos->y;
		floorCylinder.m_bottom.z = targetPos->z;
		floorCylinder.m_top = *(Vec*)&down;
		floorCylinder.m_radius = FLOAT_80331a78;

		if (MapMng.CheckHitCylinderNear(&floorCylinder, (Vec*)&down, 0x30) != 0) {
			getMapHitObject()->CalcHitPosition(targetPos);
			if (m_scriptHandle != nullptr) {
				CCaravanWork* work = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
				Vec faceNormal;
				work->m_targetCursorPosA = *targetPos;
				getMapHitObject()->GetHitFaceNormal(&faceNormal);
				work->m_targetCursorPosB = faceNormal;
			}
		}

		*centerPos = *targetPos;
#undef targetPos
#undef centerPos
	} else {
		party.flags.flag20 = 0;
	}

	CVector worldPosFinal(m_worldPosition);
	const CVector& comboCenterFinal = CVector(m_comboCenter);
	CVector deltaResult;
	PSVECSubtract((Vec*)&comboCenterFinal, reinterpret_cast<Vec*>(&worldPosFinal), reinterpret_cast<Vec*>(&deltaResult));
	Vec delta;
	delta.x = deltaResult.x;
	delta.y = deltaResult.y;
	delta.z = deltaResult.z;
	if (FLOAT_80331a78 < PSVECMag(&delta)) {
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

	CVector centerPos(m_comboTarget);
	const CVector& targetPos = CVector(m_comboCenter);
	CVector subResult;
	PSVECSubtract((Vec*)&targetPos, reinterpret_cast<Vec*>(&centerPos), reinterpret_cast<Vec*>(&subResult));
	Vec toTarget;
	toTarget.x = subResult.x;
	toTarget.y = subResult.y;
	toTarget.z = subResult.z;

	CVector scaleResult;
	PSVECScale(&toTarget, reinterpret_cast<Vec*>(&scaleResult), wave);
	Vec movement;
	movement.x = scaleResult.x;
	movement.y = scaleResult.y;
	movement.z = scaleResult.z;

	const CVector& centerPos2 = CVector(m_comboTarget);
	CVector addResult;
	PSVECAdd((Vec*)&centerPos2, &movement, reinterpret_cast<Vec*>(&addResult));
	Vec hitPos;
	hitPos.x = addResult.x;
	hitPos.y = addResult.y;
	hitPos.z = addResult.z;

	const CVector& moveVec = CVector(FLOAT_80331a78, FLOAT_80331acc, FLOAT_80331a78);
	CVector yOffset(FLOAT_80331a78, FLOAT_80331ad0, FLOAT_80331a78);
	Vec hitNormal;

	CVector bottomResult;
	PSVECAdd(&hitPos, reinterpret_cast<Vec*>(&yOffset), reinterpret_cast<Vec*>(&bottomResult));

	CMapCylinder hitCylinder(FLOAT_80331a9c, FLOAT_80331aa0);
	hitCylinder.m_bottom.x = bottomResult.x;
	hitCylinder.m_bottom.y = bottomResult.y;
	hitCylinder.m_bottom.z = bottomResult.z;
	hitCylinder.m_top = *(Vec*)&moveVec;
	hitCylinder.m_radius = FLOAT_80331a78;

	if (MapMng.CheckHitCylinderNear(&hitCylinder, (Vec*)&moveVec, 0x30) != 0) {
		CMapObj* hitObj = getMapHitObject();
		hitObj->CalcHitPosition(&hitPos);
		hitObj->GetHitFaceNormal(&hitNormal);

		CCaravanWork* work = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
		work->m_targetCursorPosB = hitNormal;
	}

	CCaravanWork* work = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
	work->m_targetCursorPosA = hitPos;
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
	switch (m_subState) {
	case 0:
		if (m_subFrame == 0 && m_itemId != 0x103) {
			putParticleFromItem(m_itemId, 0, m_particleSlots[3], &m_worldPosition);
			putParticleFromItem(m_itemId, 1, m_particleSlots[3], static_cast<Vec*>(0));
		}
		break;
	case 1:
		if (m_comboState == 0 && m_subFrame > m_unk68C) {
			putTargetParticle(0, 1);
			m_comboState = 1;
		}
		if (m_comboState != 0) {
			checkTargetParticle();
		}
		break;
	case 2:
		if (m_subFrame == 0) {
			bonus(0x19, 0, 0);
			if (m_itemId == 0x103) {
				m_comboCenter = m_worldPosition;
				m_comboTarget = m_comboCenter;
				switch (Math.Rand(4)) {
				case 0:
					m_itemId = 0x230;
					break;
				case 1:
					m_itemId = 0x231;
					break;
				case 2:
					m_itemId = 0x232;
					break;
				case 3:
					m_itemId = 0x238;
					break;
				}
			}
			endPSlotBit(0x10);
			endPSlotBit(0x100);
			if ((*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x524) & 2) != 0) {
				reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetNumCombi(PartyData(this).unk6BC, 1);
			}
		}
		if (m_subFrame == 8 && m_comboLinkCount != 0) {
			sendCombiToScript(reinterpret_cast<CGCharaObj*>(m_comboScriptArg), m_comboScriptMode, m_subFrame);
		}
		moveCenterTargetParticle();
		if (m_subFrame >= 0x12) {
			m_unk63CBits.m_bit80 = 1;
		}
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
			return;
		}
		break;
	}

	if (m_subState > 1) {
		return;
	}

	bool canTargetMagic = false;
	bool ghostTargetActive = false;
	bool menuStageGhost = false;
	const int magicReady = static_cast<int>(static_cast<unsigned int>(__cntlzw(0x103 - m_itemId)) >> 5);
	if (Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0x0F) {
		menuStageGhost = true;
	}
	if (menuStageGhost) {
		if ((__cntlzw(0x6D - (static_cast<unsigned short>(GetCID()) & 0x6D)) >> 5 & 0xFF) != 0) {
			canTargetMagic = true;
		}
	}
	if (canTargetMagic && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) != 0) {
		ghostTargetActive = true;
	}

	if (!ghostTargetActive) {
		unsigned short held = getPadHeldForSlot(static_cast<signed char>(m_animStateMisc));
		if ((held & 0x100) == 0) {
			if (m_subState == 0 || (m_subState == 1 && m_comboState == 0)) {
				if (magicReady == 0) {
					changeStat(0, 0, 0);
				}
			} else {
				if (m_comboFrame == 1) {
					putParticleTrace(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) + 0x4FU | 0x100,
					    m_particleSlots[8], this, kMonObjOne, 0);
					playSe3D(0x3E, 0x32, 0x96, 0, 0);
				}
				m_comboFrame++;
			}
		} else {
			unsigned short trig = getPadHeldForSlot(static_cast<unsigned char>(m_animStateMisc));
			if ((trig & 0x200) != 0 && magicReady == 0) {
				changeStat(0, 0, 0);
			}
		}
		return;
	}

	if (m_subState == 1 && m_comboState != 0 &&
	    sGhostMogMenuWork.flags.flag40 != 0) {
		if (m_comboFrame == 1) {
			putParticleTrace(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) + 0x4FU | 0x100,
			    m_particleSlots[8], this, kMonObjOne, 0);
			playSe3D(0x3E, 0x32, 0x96, 0, 0);
		}
		m_comboFrame++;
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
	switch (m_subState) {
	case 0:
		if (m_subFrame == 0) {
			enableDamageCol(0);
		}
		if (isLoopAnimDirect() != 0) {
			changeSubStat(1);
		}
		break;
	case 1:
		if (m_subFrame == 0) {
			m_bgColMask &= 0xFFFEFFF1;
			enableDamageCol(1);
			if (PartyData(this).flags.flag04) {
				putParticleFromItem(0x220, 2, 0, &m_worldPosition);
				putParticleFromItem(0x220, 3, 0, &m_worldPosition);
				changeSubStat(2);
			}
		} else if (m_subFrame == 0x19) {
			changeStat(0x22, 0, 0);
		}
		break;
	case 2:
		if (m_subFrame >= 0xBB) {
			if ((unsigned int)System.m_execParam >= 2) {
				System.Printf(const_cast<char*>(lbl_801DCCB0));
			}
			changeStat(0x22, 0, 0);
		}
		break;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::statAlive()
{
	setAlive(1, 0);
	canPlayerGoMenu();
	if ((PartyData(this).partyFlags & 0x20) != 0) {
		checkTargetParticle();
	}

	if (m_lastStateId == 0) {
		unsigned short held = getPadHeldForSlot(static_cast<signed char>(m_animStateMisc));
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
	CGBaseObj::onPush(other, pushType);
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if ((static_cast<unsigned short>(reinterpret_cast<CGObject*>(other)->GetCID()) & 5) == 5) {
		if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(other) + 0x500) == 0x23) {
			*reinterpret_cast<CGBaseObj**>(self + 0x6E8) = other;
		} else {
			float dist = PSVECDistance(&m_worldPosition, &reinterpret_cast<CGObject*>(other)->m_worldPosition);
			if (dist < *reinterpret_cast<float*>(self + 0x6EC)) {
				*reinterpret_cast<CGBaseObj**>(self + 0x6E4) = other;
				*reinterpret_cast<float*>(self + 0x6EC) = dist;
			}
		}
	}
	CGBaseObj::onTalk(other, talkType);
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
	PartyData(this).flags.commandActive = 0;
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
	if (carryType == 0) {
		if (PartyData(this).carryObject != nullptr) {
			if (m_lastStateId == 0x0B) {
				changeStat(0, 0, 0);
			}
			reinterpret_cast<CGItemObj*>(PartyData(this).carryObject)->carry(this, 1, 0);
			PartyData(this).carryObject = (CGObject*)0;
			setIdleMotion();
		}

		if (forceMode != 0) {
			PartyData(this).carryObject = object;
			if (PartyData(this).carryObject != nullptr) {
				if (CFlatItemCarryMode() == 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
			} else if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
				if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
					SetAnimSlot(0, 0);
					SetAnimSlot(1, 1);
				} else {
					SetAnimSlot(0x25, 0);
					SetAnimSlot(0x30, 1);
				}
			} else {
				if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
					SetAnimSlot(0x25, 0);
					SetAnimSlot(0x24, 1);
				} else {
					SetAnimSlot(0x25, 0);
					SetAnimSlot(0x24, 1);
				}
			}
			reinterpret_cast<CGItemObj*>(PartyData(this).carryObject)->carry(this, 0, 0);
		} else {
			PartyData(this).carryObject = object;
			rotTarget(reinterpret_cast<CGPrgObj*>(PartyData(this).carryObject));
			changeStat(0x0B, 0, 0);
			reinterpret_cast<CGItemObj*>(PartyData(this).carryObject)->carry(this, 0, getCarryAnimNo(this, 0));
		}
	} else if ((carryType == 1 || carryType == 2) && PartyData(this).carryObject != nullptr) {
		if (forceMode != 0) {
			if (m_lastStateId == 0x0B) {
				changeStat(0, 0, 0);
			}
			reinterpret_cast<CGItemObj*>(PartyData(this).carryObject)->carry(this, carryType, 0);
			PartyData(this).carryObject = (CGObject*)0;
				if (PartyData(this).carryObject != nullptr) {
					if (CFlatItemCarryMode() == 0) {
						if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
				} else if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0, 0);
						SetAnimSlot(1, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x30, 1);
					}
				} else {
					if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					} else {
						SetAnimSlot(0x25, 0);
						SetAnimSlot(0x24, 1);
					}
				}
		} else {
			changeStat((carryType == 1) ? 0x0C : 0x0D, 0, 0);
			reinterpret_cast<CGItemObj*>(PartyData(this).carryObject)->carry(this, carryType, getCarryAnimNo(this, carryType));
			PartyData(this).carryObject = (CGObject*)0;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::statCarry()
{
	if (m_subState == 0 && m_subFrame == 0) {
		reqAnim(0x1D, 0, 0);
	}

	unsigned short trig = getPadTrigForSlot(static_cast<signed char>(m_animStateMisc));
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
	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
	    (static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
	    reinterpret_cast<int*>(m_scriptHandle)[0xED] != 0) {
		unsigned int chalice = Game.unk_flat3_0xc7d0;
		if (m_stateFrame == 0) {
			CancelMove(1);
			FLOAT_8032EE80 = FLOAT_80331AB0;
			FLOAT_8032EE84 = *reinterpret_cast<float*>(chalice + 0x160) - m_worldPosition.y;
		}

		if (m_stateFrame <= 0x0B) {
			const float phase = sinf((FLOAT_80331AB8 * static_cast<float>(m_stateFrame)) / FLOAT_80331AC0);
			m_extraMoveVec.x = FLOAT_8032EE80 * (phase * sinf(m_rotBaseY));
			m_extraMoveVec.z = FLOAT_8032EE80 * (phase * cosf(m_rotBaseY));
			m_extraMoveVec.y = FLOAT_8032EE84 * phase + FLOAT_80331A98;
		}
	}

	if (m_stateFrame == 0) {
		int seNo;
		int anim;
		switch (m_lastStateId) {
		case 0x0C:
			anim = 0x0E;
			seNo = 0x23;
			break;
		case 0x0D:
			anim = 0x19;
			seNo = 0x24;
			break;
		case 0x1B:
			anim = (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) ? 0x28 : 9;
			seNo = 0x24;
			break;
		}
		reqAnim(anim, 0, 0);
		playSe3D(seNo, 0x32, 0x96, 0, 0);
	}

	if (isLoopAnim() != 0) {
		PartyObjOverlay& party = PartyData(this);
		if (party.carryObject != 0) {
			if (static_cast<int>(CFlatCenterState()) == 0) {
				if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
		} else if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
				SetAnimSlot(0, 0);
				SetAnimSlot(1, 1);
			} else {
				SetAnimSlot(0x25, 0);
				SetAnimSlot(0x30, 1);
			}
		} else if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		} else {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		}
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::statPickup()
{
	if (m_subState == 0 && m_subFrame == 0) {
		reqAnim(0x21, 0, 0);
	}

	unsigned short trig = getPadTrigForSlot(static_cast<signed char>(m_animStateMisc));
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
	const char* msgBase = lbl_801DCA48;
	if (source != nullptr && (static_cast<unsigned short>(source->GetCID()) & 0x2D) != 0x2D) {
		return;
	}

	int bonusSlot = reinterpret_cast<unsigned char*>(m_scriptHandle)[0xBA4];
	int addValue = 0;
	int subValue = 0;
	unsigned short currentAdd = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBCA);
	unsigned short currentSub = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBCC);
	CGame::CBossArtifactStage* bossArtifacts =
		&Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex];
	unsigned int stageAdd = bossArtifacts->m_entries[bonusSlot + 8].m_values[3];
	unsigned int stageSub = bossArtifacts->m_entries[bonusSlot + 9].m_values[0];

	if (kind == 0) {
		int count = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBC8);
		System.Printf(const_cast<char*>(msgBase + 0x1C0), count + 1);
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBC8) = count + 1;
	}
	if (kind == 1) {
		int count = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBC4);
		System.Printf(const_cast<char*>(msgBase + 0x1DC), count + 1);
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBC4) = count + 1;
	}
	if (kind == 4) {
		int count = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBC6);
		System.Printf(const_cast<char*>(msgBase + 0x1F8), count + 1);
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBC6) = count + 1;
	}

	switch (bonusSlot) {
	default:
		break;
	case 0:
		if (kind == 2 && (static_cast<int>(System.m_frameCounter) % 30) == 0) {
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
			int item = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + value * 0x48);
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
			int item = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + value * 0x48);
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
		if ((unsigned int)(kind - 0x12) <= 2 || kind == 0x15) {
			subValue = stageSub;
		}
		if (kind == 0x17) {
			addValue = stageAdd;
		}
		break;
	case 0x0B:
		if ((unsigned int)(kind - 0x0E) <= 2 || kind == 0x11) {
			addValue = stageAdd;
		}
		break;
	case 0x0C:
		if ((unsigned int)(kind - 0x12) <= 2 || kind == 0x15) {
			subValue = stageSub;
		}
		break;
	case 0x0D:
		if (kind == 0x12) {
			int item = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + value * 0x48 + 8);
			if (item < 0x69) {
				if (item >= 0x26 || item < 0x24) {
					break;
				}
			} else if (item >= 0x6B) {
				break;
			}
			addValue = stageAdd;
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
		System.Printf(const_cast<char*>(msgBase + 0x218));
		break;
	case 0x16:
		if (kind == 0x14) {
			addValue = stageAdd;
		}
		break;
	case 0x17:
		if (kind == 1 &&
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
		int total = static_cast<int>(currentAdd) + addValue;
		if (total < 0) {
			total = 0;
		} else {
			total = total > 100 ? 100 : total;
		}
		if (bonusSlot != 0) {
			System.Printf(const_cast<char*>(msgBase + 0x230), bonusSlot, total);
		}
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBCA) = static_cast<unsigned short>(total);
	}

	if (subValue != 0) {
		int total = static_cast<int>(currentSub) - static_cast<int>(subValue);
		if (total < 0) {
			total = 0;
		} else {
			total = total > 100 ? 100 : total;
		}
		System.Printf(const_cast<char*>(msgBase + 0x24C), bonusSlot, total);
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBCC) = static_cast<unsigned short>(total);
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
	unsigned char* self = reinterpret_cast<unsigned char*>(this);

	if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(weaponFlags[0]) << 24) & 0xC0000000) >> 31) != 0) {
		if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(weaponFlags[1]) << 24) & 0xC0000000) >> 31) != 0) &&
		    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x63C]) << 24) & 0xC0000000) >> 31) != 0)) {
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
				goto canUse;
			}
		}
	}

	return 0;

canUse:
	return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::canPlayerGoMenu()
{
	PartyObjOverlay& party = PartyData(this);
	unsigned short trig = getPadTrigForSlot(static_cast<signed char>(m_animStateMisc));
	if (m_lastStateId == 0 && (trig & 0x200) != 0) {
		party.partyFlags |= 0x10;
	} else if ((m_lastStateId != 0) || ((trig & 0x200) == 0)) {
		party.partyFlags &= 0xEF;
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
int CGPartyObj::useItem(int itemId)
{
	int canUse;
	int result;
	const char* msgBase = lbl_801DCA48;

	unsigned char* self = reinterpret_cast<unsigned char*>(this);
	if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x9A]) << 24) & 0xC0000000) >> 31) == 0) ||
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x9B]) << 24) & 0xC0000000) >> 31) == 0) ||
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x63C]) << 24) & 0xC0000000) >> 31) == 0) ||
	    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0)) {
		canUse = 0;
	} else {
		canUse = 1;
	}

	if (!canUse) {
		result = 0;
	} else {
		int itemKind = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48);
		if (((itemId == 0x17D) || (itemId == 0x186)) &&
		    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0)) {
			result = 0;
		} else {
			System.Printf(const_cast<char*>(msgBase + 0x170), itemId, itemKind);
			bonus(5, itemId, 0);

			switch (itemKind) {
			case 0x17D: {
				int heal;
				int foodIndex = itemId - 0x17D;
				if ((foodIndex >= 0) && (foodIndex < 8)) {
					unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
					int value = *reinterpret_cast<unsigned short*>(script + foodIndex * 2 + 0x3B8) / 10;
					heal = 1;
					if (value >= 1) {
						heal = value;
					}
					m_scriptHandle[0x2F4] =
					    reinterpret_cast<void*>(static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x68)));
					m_scriptHandle[0x2F5] = reinterpret_cast<void*>(itemId);
				} else {
					heal = 4;
				}
				addHp(heal, 0);
				System.Printf(const_cast<char*>(msgBase + 0x194), heal);
				break;
			}
			case 0x186: {
				int heal;
				if ((itemId == 0x188) &&
				    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3E0) == 2)) {
					heal = 4;
				} else {
					heal = 2;
				}
				addHp(heal, 0);
				System.Printf(const_cast<char*>(msgBase + 0x1AC), heal);
				break;
			}
			}

			CFlatRuntime::CStack stack[2];
			unsigned char pausedFlag = 0;
			if ((Game.m_gameWork.m_menuStageMode != 0) && (Game.m_gameWork.m_gamePaused != 0)) {
				pausedFlag = 1;
			}
			stack[1].m_word = pausedFlag;
			stack[0].m_word = itemId;
			gCFlatRuntime().SystemCall(this, 2, 0x15, 2, stack, 0);
			result = 1;
		}
	}
	return result;
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

	if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(weaponFlags[0]) << 24) & 0xC0000000) >> 31) != 0) &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(weaponFlags[1]) << 24) & 0xC0000000) >> 31) != 0) &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x63C]) << 24) & 0xC0000000) >> 31) != 0) &&
	    (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) &&
	    (PartyData(this).carryObject == nullptr)) {
		if (Game.m_gameWork.m_menuStageMode != 0 && static_cast<int>(CGItemObj::CanCreateFromScript()) == 0) {
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
int CGPartyObj::putItem(int itemId)
{
	int result;
	CGPrgObj* created;
	if (canPlayerPutItem() != 0 &&
	    (created = CGItemObj::CreateFromScript(0, 9, itemId, this, FLOAT_80331a78, (CGItemObj::CCFS*)0)) != nullptr) {
		*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(created) + 0x562) =
		    static_cast<short>(reinterpret_cast<int>(m_scriptHandle[0xED]));
		if (Game.m_gameWork.m_menuStageMode == 0) {
			changeStat(0x1B, 0, 0);
		}
		result = 1;
	} else {
		result = 0;
	}
	return result;
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
int CGPartyObj::putGil(int amount)
{
	int result;
	CGPrgObj* created;
	if (canPlayerPutItem() != 0 &&
	    (created = CGItemObj::CreateFromScript(2, 1, amount, this, FLOAT_80331a78, (CGItemObj::CCFS*)0)) != nullptr) {
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(created) + 0x560) = 1;
		*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(created) + 0x562) =
		    static_cast<short>(reinterpret_cast<int>(m_scriptHandle[0xED]));
		if (Game.m_gameWork.m_menuStageMode == 0) {
			changeStat(0x1B, 0, 0);
		}
		result = 1;
	} else {
		result = 0;
	}
	return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::statRebound()
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
	switch (m_subState) {
	case 0:
		if (m_subFrame == 0) {
			damageDelete();
			carry(1, (CGObject*)0, 1);
			reqAnim(0x1E, 0, 0);
		}
		if (isLoopAnim() != 0) {
			changeSubStat(1);
		}
		break;
	case 1:
		if (m_subFrame == 0) {
			reqAnim(0x1F, 0, 0);
		}
		if (isLoopAnim() != 0) {
			changeSubStat(2);
		}
		break;
	case 2:
		if (m_subFrame == 0) {
			reqAnim(0x20, 0, 0);
		}
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
		}
		break;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::statHide()
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
inline void CGPartyObj::statJump()
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
inline void CGPartyObj::statWeaponChange()
{
	PartyObjOverlay& party = PartyData(this);
	changeWeapon(party.weaponItem, party.pendingWeaponItem, 0);

	if (m_subFrame > 1) {
		changeStat(0, 0, 0);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::changeWeapon(int weaponRef, int weaponItem, int forceIdle)
{
	PartyObjOverlay& party = PartyData(this);
	party.weaponItem = weaponRef;
	party.pendingWeaponItem = weaponItem;

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

		if ((Game.m_gameWork.m_menuStageMode != 0) && (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F) &&
		    ((static_cast<unsigned short>(party->GetCID()) & 0x6D) == 0x6D) &&
		    (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party->m_scriptHandle) + 0x3B4) != 0)) {
			continue;
		}

		if ((*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(party->m_scriptHandle) + 0x1C) == 0) &&
		    (PartyData(party).flags.flag04 == 0)) {
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
	const char* msgBase = lbl_801DCA48;
	int bonusCount = 0x10;
	if (Game.m_gameWork.m_radarType != 0) {
		bonusCount = 4;
	}

	System.Printf(const_cast<char*>(msgBase + 0x114), bonusCount);

	int chosenBonus[5];
	int chosenCount = 0;
	int chosenByteOff = 0;
	CGame::CBossArtifactStage* bossArtifacts =
		&Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex];

	for (int slot = 0; slot < 4; slot++) {
		CGPartyObj* party = Game.m_partyObjArr[slot];
		if (party == nullptr) {
			continue;
		}

		if (useRandom != 0) {
			int bonusIndex;
			for (;;) {
				bonusIndex = Math.Rand(bonusCount);

				int* scan = chosenBonus;
				int duplicateIndex = 0;
				while (duplicateIndex < chosenCount) {
					if (bonusIndex == *scan) {
						break;
					}
					scan++;
					duplicateIndex++;
				}

				if (duplicateIndex == chosenCount) {
					break;
				}
			}

			*reinterpret_cast<int*>(reinterpret_cast<char*>(chosenBonus) + chosenByteOff) = bonusIndex;
			chosenCount++;
			chosenByteOff += 4;

			reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)
			    ->SetBonusCondition(bossArtifacts->m_bonusConditions[bonusIndex]);
			if ((unsigned int)System.m_execParam >= 3) {
				System.Printf(const_cast<char*>(msgBase + 0x134), slot, bonusIndex,
				    bossArtifacts->m_bonusConditions[bonusIndex]);
			}
		} else {
			int bonus;
			switch (slot) {
			case 0:
				bonus = bonus0;
				break;
			case 1:
				bonus = bonus1;
				break;
			case 2:
				bonus = bonus2;
				break;
			case 3:
				bonus = bonus3;
				break;
			}

			reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->SetBonusCondition(bonus);
			if ((unsigned int)System.m_execParam >= 3) {
				System.Printf(const_cast<char*>(msgBase + 0x154), slot, bonus);
			}
		}

		reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->CalcStatus();
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
	    PartyData(this).weaponItem,
	    PartyData(this).pendingWeaponItem);
	enableDamageCol(1);
	*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0xBD0) = 0;
	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
	    (static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D &&
	    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x3B4) != 0) {
		*reinterpret_cast<unsigned char*>(self + 0xE6) = 0;
		*reinterpret_cast<float*>(self + 0x144) = FLOAT_80331AB0;
		*reinterpret_cast<float*>(self + 0x134) = FLOAT_80331AB0;
		*reinterpret_cast<float*>(self + 0x13C) = FLOAT_80331A98;
		*reinterpret_cast<float*>(self + 0x4E8) = FLOAT_80331AB4;
		unsigned int leadingZeros = __cntlzw(*reinterpret_cast<unsigned int*>(self + 0x6F0));
		sGhostPartyWork.flagBits.flag80 = static_cast<signed char>(leadingZeros >> 5);
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
unsigned int CGPartyObj::IsDispRader()
{
	unsigned char result = 0;
	if (static_cast<int>(CGObject::IsDispRader()) != 0) {
		unsigned char* weaponFlags = reinterpret_cast<unsigned char*>(&m_weaponNodeFlags);
		if ((static_cast<signed char>(
		         static_cast<int>((static_cast<unsigned int>(weaponFlags[0]) << 24) & 0xC0000000) >> 31) != 0) &&
		    (static_cast<signed char>(
		         static_cast<int>((static_cast<unsigned int>(weaponFlags[1]) << 24) & 0xC0000000) >> 31) != 0)) {
			result = 1;
		}
	}
	return result;
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
	PartyObjOverlay& party = PartyData(this);
	if (party.commandMode != mode) {
		party.commandMode = static_cast<short>(mode);

		CRingMenu** battleMenus = MenuPcs.m_battleRingMenus;
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
		int port = caravanWork->m_joybusCaravanId;
		CRingMenu* ring = battleMenus[port];
		if (ring != 0) {
			ring->SetBattleCommand(0, -1, -1);

			caravanWork = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
			port = caravanWork->m_joybusCaravanId;
			battleMenus[port]->SetBattleCommand(1, -1, -1);

			caravanWork = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
			port = caravanWork->m_joybusCaravanId;
			battleMenus[port]->SetBattleCommand(2, -1, -1);
		} else {
			if ((unsigned int)System.m_execParam >= 2) {
				System.Printf(const_cast<char*>(sMissingRingMenuFmt));
			}
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CGPartyObj::checkAndSetWeapon()
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
	PartyObjOverlay& party = PartyData(this);

	if (*reinterpret_cast<short*>(&m_lastMapIdHit) == mode) {
		return;
	}

	*reinterpret_cast<short*>(&m_lastMapIdHit) = static_cast<short>(mode);
	changeStat(0, 0, 0);

	if (party.carryObject != 0) {
		if (CFlatItemCarryMode() == 0) {
			if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
	} else {
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
				SetAnimSlot(0, 0);
				SetAnimSlot(1, 1);
			} else {
				SetAnimSlot(0x25, 0);
				SetAnimSlot(0x30, 1);
			}
		} else if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		} else {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		}
	}

	CancelAnim(1);

	if (party.flags.flag04) {
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
			addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
		}
		party.flags.flag04 = 0;
	}

	enableDamageCol(1);

	if (party.carryObject != 0) {
		if (CFlatItemCarryMode() == 0) {
			if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
	} else {
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
				SetAnimSlot(0, 0);
				SetAnimSlot(1, 1);
			} else {
				SetAnimSlot(0x25, 0);
				SetAnimSlot(0x30, 1);
			}
		} else if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		} else {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		}
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		endPSlotBit(0x10000);
		*reinterpret_cast<float*>(self + 0x694) = kMonObjOne;
		m_bgColMask |= 0x1000E;
	} else {
		*reinterpret_cast<float*>(self + 0x694) = FLOAT_80331A7C;
		m_bgColMask &= 0xFFFEFFF1;
		int particlePort = reinterpret_cast<int>(m_scriptHandle[0xED]);
		endPSlotBit(0x10000);
		putParticle((particlePort + 3) | 0x100,
		    *reinterpret_cast<int*>(self + 0x5A4), this, kMonObjOne, 0);
	}

	if (mode == 1 && party.carryObject == 0 &&
	    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		party.flags.flag02 = 1;
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
	if (PartyData(this).carryObject != 0) {
		if (CFlatItemCarryMode() == 0) {
			if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
	} else {
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
			if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
				SetAnimSlot(0, 0);
				SetAnimSlot(1, 1);
			} else {
				SetAnimSlot(0x25, 0);
				SetAnimSlot(0x30, 1);
			}
		} else if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		} else {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x24, 1);
		}
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
	PartyObjOverlay& party = PartyData(this);

	if (party.flags.flag04) {
		if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) == 0) {
			addHp(*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1A), static_cast<CGPrgObj*>(0));
		}
		party.flags.flag04 = 0;
	}

	enableDamageCol(1);

	if (party.carryObject != 0) {
		if (static_cast<int>(CFlatCenterState()) == 0) {
			if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
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
	} else if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
			SetAnimSlot(0, 0);
			SetAnimSlot(1, 1);
		} else {
			SetAnimSlot(0x25, 0);
			SetAnimSlot(0x30, 1);
		}
	} else if (*reinterpret_cast<short*>(&m_lastMapIdHit) == 1) {
		SetAnimSlot(0x25, 0);
		SetAnimSlot(0x24, 1);
	} else {
		SetAnimSlot(0x25, 0);
		SetAnimSlot(0x24, 1);
	}

	if (restoreDamageCol == 0) {
		if (m_currentAnimSlot == 6) {
			reqAnim(0x26, 0, 0);
		} else {
			reqAnim(0x27, 0, 0);
		}
	}

	if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x1C) != 0) {
		endPSlotBit(0x10000);
		m_alpha = kMonObjOne;
		m_bgColMask |= 0x1000E;
		if (restoreDamageCol == 0) {
			*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(m_scriptHandle) + 0x48) = 0x5A;
		}
	} else {
		m_alpha = FLOAT_80331A7C;
		m_bgColMask &= 0xFFFEFFF1;
		void* port = m_scriptHandle[0xED];

		if (restoreDamageCol == 0 || keepTarget != 0) {
			endPSlotBit(0x10000);
			putParticle((reinterpret_cast<int>(port) + 3) | 0x100,
			            m_particleSlots[16], this, kMonObjOne, 0);
		}

		if (restoreDamageCol == 0) {
			playSe3D(0x2D, 0x32, 0x96, 0, 0);
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
	CGItemObj::CCFS ccfs;
	ccfs.m_memoryCapsuleNameIndex = arg0;
	ccfs.m_modelId = arg1;
	ccfs.m_modelParam = arg2;
	ccfs.m_pendingAnimFlags = arg3;
	ccfs.m_pendingAnimName = arg4;
	CGItemObj::CreateFromScript(0, 2, 399, this, FLOAT_80331a78, &ccfs);
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
	UpdateGhostPartyDamageCounters(attacker);
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
	UpdateGhostPartyDamageCounters(attacker);
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
inline void magicReady()
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
inline void chooseMagic()
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
inline void decMagic(int amount)
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
inline void calcWeightMax()
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
void CGPartyObj::gpmCalcDist(Vec* outVec, float& outDist)
{
	unsigned char* countBase = CGPartyObj::m_ghostWork;
	unsigned char* ghostWork = CGPartyObj::m_ghostWork;
	int& activeTrailCount = *reinterpret_cast<int*>(countBase + 0x48);

	if (activeTrailCount == 0) {
		activeTrailCount = 0;
		outVec->x = m_partyDelta[0].x;
		outVec->y = m_partyDelta[0].y;
		outVec->z = m_partyDelta[0].z;
		outVec->y = FLOAT_80331a78;

		outDist = PSVECMag(outVec);
		outDist = (outDist < m_partyDistance[0]) ? outDist : m_partyDistance[0];
		return;
	}

	CVector unused;
	float flatLen = 0.0f;
	int capturedCurrent = 0;
	unsigned char* loopBase = CGPartyObj::m_ghostWork;
	int& loopTrailIndex = *reinterpret_cast<int*>(loopBase + 0x4C);
	unsigned char* leaderPtr = loopBase;

	outDist = 0.0f;
	for (int i = 0; i < activeTrailCount; i++) {
		if (loopTrailIndex <= i) {
			Vec* nextPos;
			if (i == loopTrailIndex) {
				nextPos = &m_worldPosition;
			} else {
				nextPos = reinterpret_cast<Vec*>(CGPartyObj::m_ghostWork + (i - 1) * 0xC + 0x50);
			}
			Vec delta;
			PSVECSubtract(reinterpret_cast<Vec*>(leaderPtr + 0x50), nextPos, &delta);
			outDist += PSVECMag(&delta);

			delta.y = FLOAT_80331a78;
			float flatStep = PSVECMag(&delta);
			flatLen += flatStep;

			if (!capturedCurrent && i == loopTrailIndex) {
				capturedCurrent = 1;
				outVec->x = delta.x;
				outVec->y = delta.y;
				outVec->z = delta.z;
				if (flatStep < m_capsuleHalfHeight) {
					loopTrailIndex++;
				}
			}
		}
		leaderPtr += 0xC;
	}

	outDist = (outDist < flatLen) ? outDist : flatLen;
	if (outDist > DOUBLE_80331AA8) {
		activeTrailCount = 0;
		outVec->x = m_partyDelta[0].x;
		outVec->y = m_partyDelta[0].y;
		outVec->z = m_partyDelta[0].z;
		outVec->y = FLOAT_80331a78;

		outDist = PSVECMag(outVec);
		float maxDist = m_partyDistance[0];
		if (outDist < maxDist) {
			maxDist = outDist;
		}
		outDist = maxDist;
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
#pragma push
#pragma opt_common_subs off
void CGPartyObj::gpmCol()
{
	unsigned char* ghostWork = CGPartyObj::m_ghostWork;
	int& activeTrailCount = *reinterpret_cast<int*>(ghostWork + 0x48);
#define trailIndex (*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x4C))
	CGPartyObj* leader = Game.m_partyObjArr[0];

	unsigned char* trailBase = ghostWork + 0x50;
	int newIndex = 0;
	int i = 0;
	do {
		Vec* pos = (i == 0) ? &m_worldPosition
		                    : reinterpret_cast<Vec*>(trailBase + (i - 1) * 0xC);

		Vec diffVec;
		CVector posV(*pos);
		const CVector& leaderV = CVector(leader->m_worldPosition);
		CVector diff;
		PSVECSubtract((Vec*)&leaderV, reinterpret_cast<Vec*>(&posV), reinterpret_cast<Vec*>(&diff));
		diffVec.x = diff.x;
		diffVec.y = diff.y;
		diffVec.z = diff.z;

		unsigned int flags = leader->m_bgHitMask & ~0x10U;
		float halfHeight = m_capsuleHalfHeight;
		CVector bottom(pos->x, FLOAT_80331A98 + pos->y, pos->z);

		CMapCylinder cylinder(FLOAT_80331a9c, FLOAT_80331aa0);
		cylinder.m_bottom.x = bottom.x;
		cylinder.m_bottom.y = bottom.y;
		cylinder.m_bottom.z = bottom.z;
		cylinder.m_top.x = diffVec.x;
		cylinder.m_top.y = diffVec.y;
		cylinder.m_top.z = diffVec.z;
		cylinder.m_axis.x = halfHeight;

		if (MapMng.CheckHitCylinderNear(&cylinder, &diffVec, flags) != 0) {
			int capped = activeTrailCount;
			if (capped >= i + 1) {
				capped = i + 1;
			}
			i++;
			activeTrailCount = capped;
			newIndex = trailIndex;
		} else {
			*reinterpret_cast<float*>(trailBase + i * 0xC) = leader->m_worldPosition.x;
			Vec* slot = reinterpret_cast<Vec*>(trailBase + i * 0xC);
			slot->y = leader->m_worldPosition.y;
			slot->z = leader->m_worldPosition.z;
			activeTrailCount = i + 1;
			if (trailIndex < i) {
				newIndex = trailIndex;
			} else {
				newIndex = i;
			}
			break;
		}
	} while (static_cast<unsigned int>(i) < 5);

	trailIndex = newIndex;
#define gpmColClamp ((activeTrailCount - 1) & ~((activeTrailCount - 1) >> 31))
	if (trailIndex >= gpmColClamp) {
		trailIndex = gpmColClamp;
	}
#undef gpmColClamp
#undef trailIndex
}
#pragma pop

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

	gpmCol();
	gpmMove();

	int stageMode;
	switch (Game.m_gameWork.m_bossArtifactStageIndex) {
	default:
	case 0:
	case 1:
	case 2:
	case 3:
		stageMode = 0;
		break;
	case 6:
	case 10:
		stageMode = 1;
		break;
	case 4:
	case 8:
	case 9:
	case 0x0B:
	case 0x0C:
	case 0x0D:
		stageMode = 2;
		break;
	}

	float ramp = static_cast<float>(CharaGhostValue(0x2054)) / kMonObjPercentMax;
	float scale;
	switch (stageMode) {
	default:
		scale = kMonObjOne;
		break;
	case 1:
		scale = FLOAT_80331A58 * (kMonObjOne - ramp) + FLOAT_80331A58;
		break;
	case 2:
		scale = FLOAT_80331A58 * ramp + FLOAT_80331A58;
		break;
	}
	unsigned int distFar = static_cast<unsigned int>(static_cast<int>(FLOAT_80331A5C * scale));

	unsigned char* flags = &CGPartyObj::m_ghostWork[0];
#define bossState (*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x1C))

	if (static_cast<double>(m_partyDistance[0]) > DOUBLE_80331A90) {
		bossState = 1;
	} else {
		int exceeded;
		if (static_cast<int>(*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x24)) >= CharaGhostValue(0x2048) ||
		    static_cast<int>(*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x28)) >= CharaGhostValue(0x204C) ||
		    static_cast<int>(*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x2C)) >= CharaGhostValue(0x2050)) {
			exceeded = 1;
		} else {
			exceeded = 0;
		}

		if (exceeded && sGhostPartyWork.flagBits.flag10 == 0) {
			sGhostPartyWork.flagBits.flag10 = 1;
			bossState = 2;
			putParticle(299, 0, this, kMonObjOne, 0);
		} else if (sGhostPartyWork.flagBits.flag08 == 0 &&
		           static_cast<int>(*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x38)) >= 10) {
			int moodMode;
			switch (Game.m_gameWork.m_bossArtifactStageIndex) {
			default:
			case 0:
			case 1:
			case 2:
			case 3:
				moodMode = 0;
				break;
			case 6:
			case 10:
				moodMode = 1;
				break;
			case 4:
			case 8:
			case 9:
			case 0x0B:
			case 0x0C:
			case 0x0D:
				moodMode = 2;
				break;
			}
			if (moodMode == 1) {
				if (CharaGhostValue(0x2054) < 0x32) {
					bossState = 5;
				} else if (CharaGhostValue(0x2054) >= 0x5F) {
					bossState = 4;
				}
			} else if (moodMode > 1 && moodMode < 3 && CharaGhostValue(0x2054) < 0x32) {
				bossState = 6;
			}
			sGhostPartyWork.flagBits.flag08 = 1;
		} else {
			if (sGhostPartyWork.flagBits.flag10 == 0) {
				int innerMode;
				switch (Game.m_gameWork.m_bossArtifactStageIndex) {
				default:
				case 0:
				case 1:
				case 2:
				case 3:
					innerMode = 0;
					break;
				case 6:
				case 10:
					innerMode = 1;
					break;
				case 4:
				case 8:
				case 9:
				case 0x0B:
				case 0x0C:
				case 0x0D:
					innerMode = 2;
					break;
				}
				float innerScale;
				switch (innerMode) {
				default:
					innerScale = kMonObjOne;
					break;
				case 1:
					innerScale = FLOAT_80331A58 * (kMonObjOne - ramp) + FLOAT_80331A58;
					break;
				case 2:
					innerScale = FLOAT_80331A58 * ramp + FLOAT_80331A58;
					break;
				}
				if (static_cast<int>(*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x38)) >= static_cast<int>(FLOAT_80331A5C * innerScale)) {
					bossState = 3;
					sGhostPartyWork.flagBits.flag04 = 1;
					goto messageMenu;
				}
			}
			if (sGhostPartyWork.flagBits.flag10 == 0 && static_cast<int>(*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x3C)) > 0x96) {
				bossState = 8;
			} else {
				bossState = 0;
				*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x20) = 0;
			}
		}
	}

messageMenu:
	if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(&leader->m_weaponNodeFlags)[1]) << 24) & 0xC0000000) >> 31) != 0) &&
	    bossState != 0 &&
	    bossState != *reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x20)) {
#define mesMenu (*reinterpret_cast<CMesMenu**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0x120))
		if (!mesMenu->IsActiveMessage()) {
			*reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x20) = bossState;
			mesMenu->Open(Game.m_cFlatDataArr[1].Message(bossState - 1), 0x260, 0x20, 0x8E20, 0, 0x65, 0x8B);
		}
#undef mesMenu
	}

	int auraSlot = 0;
	int gauge = *reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x38);
	if (gauge > static_cast<int>(distFar * 3) / 3) {
		auraSlot = 0xF;
	} else if (gauge > static_cast<int>(distFar << 1) / 3) {
		auraSlot = 0xE;
	} else if (gauge > static_cast<int>(distFar) / 3) {
		auraSlot = 0xD;
	}

	int prevSlot = *reinterpret_cast<int*>(CGPartyObj::m_ghostWork + 0x8C);
	if (prevSlot != auraSlot) {
		endPSlotBit(0x400);
		prevSlot = auraSlot;
		if (auraSlot != 0) {
			putParticle(auraSlot | 0x200, m_particleSlots[10], this, kMonObjOne, 0);
		}
	}
	*reinterpret_cast<unsigned int*>(CGPartyObj::m_ghostWork + 0x8C) = prevSlot;
#undef bossState
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

	if (leader->m_lastStateId == 0 &&
	    leader->m_animSlotSel == 0x0C &&
	    PartyData(leader).carryObject == chalice) {
		sGhostPartyWork.settleTimer++;
	} else {
		sGhostPartyWork.settleTimer = 0;
	}

	if (FLOAT_80331A70 < sGhostPartyWork.carrySpeed) {
		moveVector(&sGhostPartyWork.carryDir, sGhostPartyWork.carrySpeed, 1);
	}
	sGhostPartyWork.carrySpeed *= FLOAT_80331a74;

	int stageMode;
	switch (Game.m_gameWork.m_bossArtifactStageIndex) {
	default:
	case 0:
	case 1:
	case 2:
	case 3:
		stageMode = 0;
		break;
	case 6:
	case 10:
		stageMode = 1;
		break;
	case 4:
	case 8:
	case 9:
	case 0x0B:
	case 0x0C:
	case 0x0D:
		stageMode = 2;
		break;
	}

	float frameScale = static_cast<float>(CharaGhostValue(0x2054)) / kMonObjPercentMax;
	float pressureScale;
	switch (stageMode) {
	default:
		pressureScale = kMonObjOne;
		break;
	case 1:
		pressureScale = FLOAT_80331A58 * (kMonObjOne - frameScale) + FLOAT_80331A58;
		break;
	case 2:
		pressureScale = FLOAT_80331A58 * frameScale + FLOAT_80331A58;
		break;
	}

	int pressureLimit = static_cast<int>(FLOAT_80331A5C * pressureScale);
	if (FLOAT_80331A58 < sGhostPartyWork.carrySpeed) {
		int delta = -2;
		if (PartyData(this).carryObject != nullptr) {
			delta = 2;
		}
		sGhostPartyWork.pressure += delta;
	} else if (PartyData(this).carryObject != nullptr) {
		sGhostPartyWork.pressure -= 3;
	} else {
		sGhostPartyWork.pressure -= 4;
	}

	int clampedPressure = sGhostPartyWork.pressure;
	if (clampedPressure < 0) {
		clampedPressure = 0;
	} else if (pressureLimit + 100 < clampedPressure) {
		clampedPressure = pressureLimit + 100;
	}
	sGhostPartyWork.pressure = clampedPressure;

	if (sGhostPartyWork.pressure < pressureLimit / 3) {
		sGhostPartyWork.flagBits.flag04 = 0;
	}
	{
		int trailDec = sGhostPartyWork.activeTrailCount - 1;
		sGhostPartyWork.activeTrailCount = trailDec & ~(trailDec >> 31);
	}

	Vec pathVec;
	float pathDist;
	gpmCalcDist(&pathVec, pathDist);

	Vec toLeader;
	toLeader = m_targetDelta;
	toLeader.y = 0.0f;
	float dist = PSVECMag(&toLeader);
	float nearDist = m_nearColRadius + leader->m_nearColRadius;
	float clampedDist = (dist > *reinterpret_cast<float*>(self + 0x5BC)) ? *reinterpret_cast<float*>(self + 0x5BC) : dist;

	if (m_lastStateId == 0 &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(self[0x63C]) << 24) & 0xC0000000) >> 31) != 0)) {
		int moveKind;
		if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(sGhostPartyWork.flags) << 24) & 0xC0000000) >> 31) != 0) {
			moveKind = 0;
			if (PartyData(this).carryObject != nullptr) {
				sGhostPartyWork.carrySpeed = 0.0f;
				carry(1, static_cast<CGObject*>(0), 0);
				return;
			}

			float limit = (sGhostPartyWork.activeTrailCount != 0) ? FLOAT_80331A7C : FLOAT_80331A80;
			if (pathDist < Game.unkFloat_0xca10 * limit) {
				if ((leader->m_lastStateId != 2 && leader->m_lastStateId != 6) ||
				    leader->m_subState != 1 ||
				    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x668) == 0 ||
				    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(leader) + 0x660) != 0) {
					return;
				}

				if (sGhostPartyWork.thresholdA < CharaGhostValue(0x2048) &&
				    sGhostPartyWork.thresholdB < CharaGhostValue(0x204C) &&
				    sGhostPartyWork.thresholdC < CharaGhostValue(0x2050)) {
					return;
				}

				int choices = 0;
				if (sGhostPartyWork.thresholdA >= CharaGhostValue(0x2048)) {
					choices++;
				}
				if (sGhostPartyWork.thresholdB >= CharaGhostValue(0x204C)) {
					choices++;
				}
				if (sGhostPartyWork.thresholdC >= CharaGhostValue(0x2050)) {
					choices++;
				}

				int pick = Math.Rand(choices);
				int cursor = 0;
				int newSlotSel;
				if (sGhostPartyWork.thresholdA >= CharaGhostValue(0x2048) && cursor == pick) {
					newSlotSel = 0;
				} else {
					if (sGhostPartyWork.thresholdA >= CharaGhostValue(0x2048)) {
						cursor++;
					}
					if (sGhostPartyWork.thresholdB >= CharaGhostValue(0x204C) && cursor == pick) {
						newSlotSel = 1;
					} else {
						if (sGhostPartyWork.thresholdB >= CharaGhostValue(0x204C)) {
							cursor++;
						}
						if (sGhostPartyWork.thresholdC >= CharaGhostValue(0x2050) && cursor == pick) {
							newSlotSel = 2;
						} else {
							newSlotSel = 0;
						}
					}
				}
				sGhostPartyWork.slotSel = newSlotSel;

				switch (sGhostPartyWork.slotSel) {
				case 1:
					*reinterpret_cast<int*>(self + 0x560) = 0x20F;
					break;
				case 0:
					*reinterpret_cast<int*>(self + 0x560) = 0x207;
					break;
				case 2:
					*reinterpret_cast<int*>(self + 0x560) = 0x20B;
					break;
				}
				changeStat(2, 0, 0);
				sGhostPartyWork.gauge = 0;
				PartyData(this).flags.flag40 = 0;
				PartyData(this).flags.flag20 = 0;
				return;
			}
		} else {
			moveKind = 0;
			if (chalice != nullptr &&
			    PartyData(this).carryObject == nullptr &&
			    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(chalice) + 0x9A)) << 24) & 0xC0000000) >> 31) != 0) &&
			    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(chalice) + 0x550) == 0) {
				float pickupRadius = (leader->m_bodyEllipsoidRadius + *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(chalice) + 0x144)) * FLOAT_80331A84;
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
				float limit = (sGhostPartyWork.activeTrailCount != 0) ? FLOAT_80331A7C : FLOAT_80331A58;
				if (pathDist < Game.unkFloat_0xca10 * limit) {
					return;
				}
			}
			if (moveKind == 1 && chalice != nullptr) {
				float keepDist = (leader->m_bodyEllipsoidRadius + *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(chalice) + 0x144)) * FLOAT_80331A58;
				if (clampedDist < keepDist) {
					return;
				}
			}
		}

		if (sGhostPartyWork.field04 != moveKind) {
			sGhostPartyWork.field04 = moveKind;
			sGhostPartyWork.field08 = 0;
		}

		CVector moveDir;
		if (moveKind == 0) {
			CVector pathVecV(pathVec);
			moveDir.x = pathVecV.x;
			moveDir.y = pathVecV.y;
			moveDir.z = pathVecV.z;
		} else {
			CVector toLeaderV(toLeader);
			moveDir.x = toLeaderV.x;
			moveDir.y = toLeaderV.y;
			moveDir.z = toLeaderV.z;
		}

		float nextSpeed = sGhostPartyWork.carrySpeed + FLOAT_80331A70;
		float speedScale = (pressureLimit <= sGhostPartyWork.pressure) ? kMonObjOne : FLOAT_80331A88;
		if (nextSpeed < 0.0f) {
			sGhostPartyWork.carrySpeed = nextSpeed;
		} else {
			float speedLimit = speedScale * m_moveBaseSpeed * *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(Game.m_partyObjArr[0]) + 0x690);
			sGhostPartyWork.carrySpeed = (speedLimit < nextSpeed) ? speedLimit : nextSpeed;
		}

		sGhostPartyWork.carryDir = *reinterpret_cast<Vec*>(&moveDir);
		if (sGhostPartyWork.field08 + 1 != 4) {
			sGhostPartyWork.field08++;
		} else {
			sGhostPartyWork.field08 = 0;
		}
		return;
	}

	if (m_lastStateId != 2) {
		return;
	}
	if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(sGhostPartyWork.flags) << 24) & 0xC0000000) >> 31) == 0) {
		changeStat(0, 0, 0);
		return;
	}

	if (leader->m_lastStateId != 2 && leader->m_lastStateId != 6) {
		if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(sGhostPartyWork.flags) << 26) & 0xC0000000) >> 31) == 0) {
			changeStat(0, 0, 0);
			return;
		}
	} else {
		if (m_subState != 1) {
			return;
		}
		if (*reinterpret_cast<int*>(self + 0x668) == 0) {
			return;
		}
		if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(PartyData(leader).partyFlags) << 26) & 0xC0000000) >> 31) != 0) {
			sGhostPartyWork.gauge = 0;
		}
		if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(PartyData(this).partyFlags) << 25) & 0xC0000000) >> 31) == 0) {
			return;
		}

		PartyData(this).partyFlags |= 0x20;
		sGhostPartyWork.gauge++;
		if (sGhostPartyWork.gauge <= 0xF) {
			return;
		}
		if (static_cast<unsigned char>(static_cast<unsigned int>((static_cast<unsigned int>(PartyData(this).partyFlags) << 25) & 0xC0000000) >> 31) != 0) {
			return;
		}
	}

	{
		unsigned char* base = CGPartyObj::m_ghostWork;
		const int slotSel = sGhostPartyWork.slotSel;
		for (int slot = 0; slot < 3; slot++) {
			if (slot == slotSel) {
				*reinterpret_cast<int*>(base + 0x24) = 0;
			} else {
				*reinterpret_cast<int*>(base + 0x24) = *reinterpret_cast<int*>(base + 0x24) / 2;
			}
			base += 4;
		}
	}
	PartyData(this).partyFlags = (PartyData(this).partyFlags & 0xAF) | 0x40;
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

	if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(this)[0x9A]) << 24) & 0xC0000000) >> 31) == 0) ||
	    (static_cast<int>(CFlatCenterState()) != 0) ||
	    ((*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&DbgMenuPcs) + 4) & 0x80) == 0)) {
		return;
	}

	char text[256];
	if ((Game.m_gameWork.m_menuStageMode != 0) &&
	    (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F) &&
	    ((static_cast<unsigned short>(GetCID()) & 0x6D) == 0x6D) && (reinterpret_cast<int*>(m_scriptHandle)[0xED] != 0)) {
		unsigned int bossKind;
		switch (Game.m_gameWork.m_bossArtifactStageIndex) {
		default:
		case 0:
		case 1:
		case 2:
		case 3:
			bossKind = 0;
			break;
		case 6:
		case 0x0A:
			bossKind = 1;
			break;
		case 4:
		case 8:
		case 9:
		case 0x0B:
		case 0x0C:
		case 0x0D:
			bossKind = 2;
			break;
		}

		float rate = static_cast<float>(CharaGhostValue(0x2054)) / kMonObjPercentMax;
		double angleScale;
		switch (bossKind) {
		default:
			angleScale = kMonObjOne;
			break;
		case 1:
			angleScale = FLOAT_80331A58 * (kMonObjOne - rate) + FLOAT_80331A58;
			break;
		case 2:
			angleScale = FLOAT_80331A58 * rate + FLOAT_80331A58;
			break;
		}

		sprintf(text, s_partyObjGhostFmt, sGhostPartyWork.thresholdA, CharaGhostValue(0x2048),
		        sGhostPartyWork.thresholdB, CharaGhostValue(0x204C),
		        sGhostPartyWork.thresholdC, CharaGhostValue(0x2050));

		float width = static_cast<float>(font->GetWidth(text));
		font->SetPosX(x - width * 0.5f);
		font->SetPosY(y);
		font->SetPosZ(z);
		font->Draw(text);
		y -= static_cast<float>(font->m_glyphHeight) * font->scaleY;

		sprintf(text, s_partyObjGhostAngleFmt, sGhostPartyWork.pressure,
		        static_cast<int>(FLOAT_80331A5C * angleScale), CharaGhostValue(0x2054));

		width = static_cast<float>(font->GetWidth(text));
		font->SetPosX(x - width * 0.5f);
		font->SetPosY(y);
		font->SetPosZ(z);
		font->Draw(text);
	} else {
		unsigned char* work = reinterpret_cast<unsigned char*>(m_scriptHandle);
		sprintf(text, s_partyObjDebugScriptFmt, work[0xBA4], *reinterpret_cast<short*>(work + 0xBC4),
		        *reinterpret_cast<unsigned short*>(work + 0xBC6), *reinterpret_cast<unsigned short*>(work + 0xBC8),
		        *reinterpret_cast<unsigned short*>(work + 0xBCA), *reinterpret_cast<unsigned short*>(work + 0xBCC));

		float width = static_cast<float>(font->GetWidth(text));
		font->SetPosX(x - width * 0.5f);
		font->SetPosY(y);
		font->SetPosZ(z);
		font->Draw(text);
	}
	y -= static_cast<float>(font->m_glyphHeight) * font->scaleY;
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
