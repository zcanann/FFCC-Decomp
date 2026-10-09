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
#include "ffcc/p_map.h"
#include "ffcc/joybusconst.h"
#include "ffcc/cardconst.h"

#include <math.h>
#include "ffcc/fontman.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

inline int CSystem::GetErrorLevel()
{
	return m_execParam;
}

class CAStar {
public:
	void addRealTime(CGPartyObj*);

	unsigned char m_data[0x24A8];
};

extern CAStar AStar;

extern int __float_huge[];

#ifdef VERSION_GCCP01
static const int kPartyObjCarryArcFrames = 11;
#else
static const int kPartyObjCarryArcFrames = 14;
#endif

GhostPartyWork CGPartyObj::m_ghostWork;

struct SScriptFoodView { // script overlay: food table at +0x3B8
	unsigned char pad[0x3B8];
	unsigned short m_foods[8];
};

// Padded row views over the CFlatData item table (stride 0x48).
struct SCfdItemRow {
	unsigned short m_kind;     // 0x00
	unsigned short m_model;    // 0x02
	unsigned char pad4[4];     // 0x04
	unsigned short m_field8;   // 0x08
	unsigned short m_fieldA;   // 0x0A
	unsigned char padC[0x14];  // 0x0C
	unsigned short m_field20;  // 0x20
	unsigned char pad22[0xE];  // 0x22
	unsigned short m_field30;  // 0x30
	unsigned short m_field32;  // 0x32
	unsigned char pad34[0x14]; // 0x34
};

struct SAtkRec {
	unsigned short m_attackStartFrame;
	unsigned short m_attackEndFrame;
	unsigned short m_moveStartFrame;
	unsigned short m_moveEndFrame;
	unsigned short m_moveSpeed;
	unsigned short m_controlStartFrame;
	unsigned short m_comboStartFrame;
	unsigned short m_comboEndFrame;
	unsigned short m_comboNextFrame;
};

STATIC_ASSERT(sizeof(SAtkRec) == 0x12);

struct SChargePhase {
	unsigned short m_attackCol;
	unsigned short m_attackStartFrame;
	unsigned short m_attackEndFrame;
	unsigned short m_moveStartFrame;
	unsigned short m_moveEndFrame;
	unsigned short m_moveSpeed;
};

struct SChargeRec {
	SChargePhase m_phases[5];
	unsigned short m_twistLimit;
	unsigned short m_twistStartFrame;
	unsigned short m_twistEndFrame;
};

STATIC_ASSERT(sizeof(SChargePhase) == 0xC);
STATIC_ASSERT(sizeof(SChargeRec) == 0x42);
STATIC_ASSERT(offsetof(SChargeRec, m_twistLimit) == 0x3C);

struct SPartyAnimRow {
	SAtkRec m_attacks[3];
	SChargeRec m_chargeAttacks[6];
	unsigned short m_carryAnim0;
	unsigned short m_carryAnim1;
	unsigned short m_carryAnim2;
	unsigned short m_carryAnim3;
};

STATIC_ASSERT(sizeof(SPartyAnimRow) == 0x1CA);
STATIC_ASSERT(offsetof(SPartyAnimRow, m_chargeAttacks) == 0x36);
STATIC_ASSERT(offsetof(SPartyAnimRow, m_carryAnim0) == 0x1C2);

static inline int getEquipWeaponInventoryItem(CCaravanWork* work)
{
	int equip0 = work->m_equipment[0];
	return equip0 >= 0 ? work->m_inventoryItems[equip0] : 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 304b
 * EN Address: 0x801418DC
 * EN Size: 268b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGPartyObj::changeWeapon(int weaponIndex, int itemId, int immediate)
{
	if (immediate) {
		if (itemId <= 0) {
			LoadWeapon(-1, 0);
		} else {
			SItemFlatRow* rows = reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2]);
			unsigned short model = rows[itemId].m_model;
			LoadWeapon(model & 0xFFF, model >> 12);
		}
		m_partyData.weaponIndex = weaponIndex;
		m_partyData.weaponItemId = itemId;
		reinterpret_cast<CCaravanWork*>(m_scriptHandle)->SetCurrentWeaponIdx(m_partyData.weaponIndex);
		m_partyData.commandFlagBits.flag20 = 0;
	} else {
		m_partyData.pendingWeaponIndex = weaponIndex;
		m_partyData.pendingWeaponItemId = itemId;
		m_partyData.commandFlagBits.flag20 = 1;
		changeStat(0x0F, 0, 0);
	}
}

static inline void UpdateGhostPartyDamageCounters(CGPrgObj* attacker)
{
	if (attacker->IsKindOf(0xAD) && Game.m_gameWork.m_menuStageMode != 0) {
		CGPartyObj::m_ghostWork.counters[0]++;
		CGPartyObj::m_ghostWork.counters[1]++;
		CGPartyObj::m_ghostWork.counters[2]++;
		System.Printf("\x90\xD4=%d/%d \x97\xCE=%d/%d \x90\xC2=%d/%d\n",
		    CGPartyObj::m_ghostWork.counters[0], Chara.MogFur().m_radarLevel[0],
		    CGPartyObj::m_ghostWork.counters[1], Chara.MogFur().m_radarLevel[1],
		    CGPartyObj::m_ghostWork.counters[2], Chara.MogFur().m_radarLevel[2]);
	}
}

static bool isMenuPcsCommandBusy()
{
	return MenuPcs.m_mode != 0;
}

static unsigned short getItemKindFromCfd(int itemId)
{
	if (itemId <= 0 || Game.unkCFlatData0[2] == 0) {
		return 0;
	}

	return *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48);
}

static bool isBossArtifactStage()
{
	return Game.m_gameWork.m_menuStageMode != 0 && Game.m_gameWork.m_bossArtifactStageIndex < 0x0F;
}

static bool isFrameInterval(int frame, int interval)
{
	return frame % interval == 0;
}

static inline bool isGhostPartyTargetMode(CGPartyObj* self)
{
	return Game.m_gameWork.m_menuStageMode != 0 &&
	       Game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
	       self->IsKindOf(0x6D) &&
	       reinterpret_cast<CCaravanWork*>(self->m_scriptHandle)->m_joybusCaravanId != 0;
}

static inline int getCarryAnimNo(CGPartyObj* self, int carryType)
{
	if (isGhostPartyTargetMode(self)) {
#ifdef VERSION_GCCP01
		return 5;
#else
		return 7;
#endif
	}

	unsigned short anim;
	if (carryType == 0) {
		if (CFlatItemCarryMode() == 1) {
			unsigned char* script = reinterpret_cast<unsigned char*>(self->m_scriptHandle);
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			anim = rows[*reinterpret_cast<unsigned short*>(script + 0x3E2) +
			            *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2].m_carryAnim2;
		} else {
			unsigned char* script = reinterpret_cast<unsigned char*>(self->m_scriptHandle);
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			anim = rows[*reinterpret_cast<unsigned short*>(script + 0x3E2) +
			            *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2].m_carryAnim0;
		}
	} else {
		if (CFlatItemCarryMode() == 1) {
			unsigned char* script = reinterpret_cast<unsigned char*>(self->m_scriptHandle);
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			anim = rows[*reinterpret_cast<unsigned short*>(script + 0x3E2) +
			            *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2].m_carryAnim3;
		} else {
			unsigned char* script = reinterpret_cast<unsigned char*>(self->m_scriptHandle);
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			anim = rows[*reinterpret_cast<unsigned short*>(script + 0x3E2) +
			            *reinterpret_cast<unsigned short*>(script + 0x3E0) * 2].m_carryAnim1;
		}
	}
	return anim;
}

inline void CMapPcs::CalcHitPosition(Vec* hitPosition)
{
	MapMng.m_hitMapObj->CalcHitPosition(hitPosition);
}

inline void CMapPcs::GetHitFaceNormal(Vec* normal)
{
	MapMng.m_hitMapObj->GetHitFaceNormal(normal);
}

inline int CMapPcs::CalcHitSlide(Vec* move, float scale)
{
	return MapMng.m_hitMapObj->CalcHitSlide(move, scale);
}

inline int CMapPcs::CheckHitCylinderNear(Vec* cylinderBottom, Vec* direction, float radius, unsigned long hitMask)
{
	CMapCylinder cylinder;

	cylinder.m_bottom = *cylinderBottom;
	cylinder.m_axis = *direction;
	cylinder.m_radius = radius;

	return MapMng.CheckHitCylinderNear(&cylinder, direction, hitMask);
}

// Original passes only two args at both statCharge/checkTargetParticle call
// sites (target never loads r6); bind the mangled symbol with a 2-arg shape.
extern "C" void sendCombiToScript__10CGCharaObjFP10CGCharaObjii(CGCharaObj* self, CGCharaObj* target, int scriptArg);

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
 * PAL Address: 0x801248A4
 * PAL Size: 244b
 * EN Address: 0x80123BD4
 * EN Size: 244b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onCreate()
{
	CGCharaObj::onCreate();

	PartyObjOverlay& party = m_partyData;
	party.unk6D0 = 0;
	float targetDist = 0.0f;
	party.attackSel = 0;
	party.unk6CC = 0;
	party.unk6BC = 0;
	party.target = 0;
	party.targetOverride = 0;
	party.unk6ECFloat = INFINITY;
	party.carryObject = 0;

	party.flags.commandActive = 0;
	party.flags.flag08 = 0;
	party.weaponIndex = 0;
	party.weaponItemId = 0;
	party.flags.flag40 = 0;
	party.flags.flag20 = 0;
	party.flags.flag10 = 0;
	party.flags.flag04 = 0;
	party.flags.flag02 = 0;

	m_targetDist = targetDist;
	party.unk6C0 = -1;
	party.commandMode = 0;

	static int q = 0;
	if (q == 0) {
		q = 1;
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
	PartyObjOverlay& party = m_partyData;
	if (party.flags.flag04) {
		addHp(m_scriptHandle->m_maxHp, static_cast<CGPrgObj*>(0));
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
	PartyObjOverlay& party = m_partyData;
	m_weaponNodeFlagAll.m_bits1.m_menuReady = 0;

	switch (state) {
	case -20:
		break;
	case 0:
		m_weaponNodeFlagAll.m_bits1.m_menuReady = 1;
		break;
	case 1: {
		int attackSel = party.attackSel;
		m_attackAnimId = (attackSel == 0) ? 5 : ((attackSel == 1) ? 7 : 8);
		{
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			m_castFrameStart =
			    rows[reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag +
			         reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId * 2]
			        .m_attacks[attackSel].m_attackStartFrame;
		}
		{
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			m_castFrameEnd =
			    rows[reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag +
			        reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId * 2]
			        .m_attacks[attackSel].m_attackEndFrame;
		}
		{
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			m_castFrameCurrent =
			    rows[reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag +
			        reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId * 2]
			        .m_attacks[attackSel].m_controlStartFrame;
		}
		break;
	}
	case 2:
		m_attackAnimId = 0x0F;
		m_unk554 = 0x10;
		m_unk558 = 0x11;
		int castTime;
		if (m_itemId == 0x103) {
			castTime = 0;
		} else {
			castTime = calcCastTime(m_itemId);
		}
		m_unk68C = castTime;
		break;
	case 8:
		m_attackAnimId = 0x15;
		m_unk554 = 0x16;
		m_unk558 = 0x17;
		m_unk55C = 0x18;
		break;
	case 6:
		System.Printf("\x83`\x83\x83\x81[\x83W\x83" "A\x83" "C\x83" "e\x83\x80\x94\xD4\x8D\x86\x95\xCF\x8A\xB7%d->", m_itemId);
		{
			SCfdItemRow* rows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
			m_itemId = rows[m_itemId].m_fieldA;
		}
		System.Printf("%d\n", m_itemId);
		m_attackAnimId = 0x12;
		m_unk554 = 0x13;
		SCfdItemRow* kindRows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
		unsigned short itemKind = kindRows[m_itemId].m_fieldA;
		int itemHigh = itemKind >> 8;
		int itemLow = itemKind & 0xFF;
		System.Printf("\x83`\x83\x83\x81[\x83W\x83\x82\x81[\x83V\x83\x87\x83\x93idx=%d\n", itemHigh);
		System.Printf("\x83`\x83\x83\x81[\x83W\x83^\x83" "C\x83v=%d\n", itemLow);
		m_unk558 = itemHigh + 0x2A;
		{
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			m_castFrameStart =
			    rows[reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag +
			        reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId * 2]
			        .m_chargeAttacks[itemLow].m_phases[0].m_attackStartFrame;
		}
		{
			SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
			m_castFrameEnd =
			    rows[reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag +
			        reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId * 2]
			        .m_chargeAttacks[itemLow].m_phases[0].m_attackEndFrame;
		}
		m_unk68C = calcCastTime(m_itemId);
		if (Game.m_gameWork.m_menuStageMode != 0) {
			int cmdListItem =
			    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetWeaponAttrib(m_partyData.weaponIndex);
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
	PartyObjOverlay& party = m_partyData;

	switch (m_lastStateId) {
	case 2:
		party.flags.flag40 = 0;
		party.flags.flag20 = 0;
		endPSlotBit(0x10);
		endPSlotBit(0x100);
		break;
	case 0x0F:
		if (m_partyData.commandFlagBits.flag20 != 0) {
			changeWeapon(party.pendingWeaponIndex, party.pendingWeaponItemId, 1);
		}
		break;
	case 0x15:
		enableDamageCol(1);
		break;
	case 0x14:
		m_alpha = 1.0f;
		enableDamageCol(1);
		break;
	case 0x0B:
		{
			setIdleMotion();
		}
		break;
	case 0x0C:
	case 0x0D:
		{
			setIdleMotion();
		}
		break;
	case 9:
		if (state == 0x22) {
			break;
		}
		if (party.flags.flag04) {
			if (m_scriptHandle->m_hp == 0) {
				addHp(m_scriptHandle->m_maxHp, static_cast<CGPrgObj*>(0));
			}
			party.flags.flag04 = 0;
		}
		enableDamageCol(1);
		{
			setIdleMotion();
		}
		if (m_scriptHandle->m_hp != 0) {
			endPSlotBit(0x10000);
			m_alpha = 1.0f;
			m_bgColMask |= 0x1000E;
		} else {
			m_alpha = 0.3f;
			m_bgColMask &= 0xFFFEFFF1;
		}
		break;
	case 0x22:
		if (party.flags.flag04) {
			if (m_scriptHandle->m_hp == 0) {
				addHp(m_scriptHandle->m_maxHp, static_cast<CGPrgObj*>(0));
			}
			party.flags.flag04 = 0;
		}
		enableDamageCol(1);
		{
			setIdleMotion();
		}
		if (m_scriptHandle->m_hp != 0) {
			endPSlotBit(0x10000);
			m_alpha = 1.0f;
			m_bgColMask |= 0x1000E;
		} else {
			m_alpha = 0.3f;
			m_bgColMask &= 0xFFFEFFF1;
		}
		break;
	case 6:
		m_twistTarget = 0.0f;
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
	PartyObjOverlay& party = m_partyData;
	int portIndex = reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId;

	if (party.flags.flag08) {
		if (Game.m_gameWork.m_menuStageMode != 0 ||
		    Joybus.GetPadType(m_animStateMisc) != 0x40000) {
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
			unsigned short trig = Pad.GetGbaButtonDown(m_animStateMisc);
			if ((trig & 0x10) != 0) {
				goto openMenu;
			}
		}

		if (Game.m_gameWork.m_menuStageMode == 0) {
			return;
		}

		if ((Pad.GetButtonDown(m_animStateMisc) & 0x800) == 0) {
			return;
		}

	openMenu:
		if (Game.m_gameWork.m_menuStageMode == 0) {
			int connected = Pad.IsGba(static_cast<char>(m_animStateMisc));
			if (connected != 0) {
				if ((CFlatEventFlags() & CFlatEventFlagByte_GbaSound) != 0) {
					Sound.PlaySe(8, 0x40, 0x7F, 0);
				}
			} else if ((CFlatEventFlags() & CFlatEventFlagByte_GbaSound) != 0) {
				Sound.PlaySe(7, 0x40, 0x7F, 0);
			}

			Joybus.ChgCtrlMode(portIndex);
			return;
		}

		if (canPlayerGoMenu()) {
			Joybus.ChgCtrlMode(portIndex);
			Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 1;
		} else {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
		}
		return;
	}

	if (Game.m_gameWork.m_menuStageMode != 0) {
		return;
	}

	if (Pad.IsGba(static_cast<char>(m_animStateMisc)) == 0) {
		return;
	}

	if (System.GetErrorLevel() >= 3U) {
		System.Printf("\x83t\x83\x8A\x83" "b\x83v\x8B\xD6\x8E~\x82\xC5GBA\x82\xC8\x82\xCC\x82\xC5GC\x82\xC9\x96\xDF\x82\xB5\x82\xDC\x82\xB7\x81" "BidxParty=%d internal=%d\n", portIndex, Joybus.GetCtrlMode(m_animStateMisc));
	}

	Joybus.ChgCtrlMode(portIndex);
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
	if (m_scriptHandle == nullptr) {
		return;
	}

	PartyObjOverlay& party = m_partyData;
	if (party.target != nullptr &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(party.target) + 0x38)) << 24) & 0xC0000000) >> 31) != 0)) {
		party.target = 0;
	}

	checkAndSetWeapon();

	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->CalcStatus();
	int port = reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId;
	int showTraceParticle;
	if ((static_cast<int>(Game.m_gameWork.m_gameInitFlag) == 0) ||
	    (CFlatRuntime2Storage().m_gameFlagBits.m_flagBit3 == 0) ||
	    (CFlatRuntime2Storage().m_gameFlagBits.m_flagBit2 == 0) ||
	    ((m_weaponNodeFlagBits.m_prg == 0) ||
	     (m_weaponNodeFlagAll.m_bits1.m_shield == 0)) ||
	    (m_lastStateId == 6 || m_lastStateId == 2)) {
		goto traceZero;
	}
	if ((Game.m_gameWork.m_menuStageMode != 0) &&
	    (Game.m_gameWork.m_menuStageMode != 0) &&
	    (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F) &&
	    IsKindOf(0x6D) &&
	    (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId != 0)) {
		showTraceParticle = 0;
	} else {
		showTraceParticle = 1;
	}
	goto traceJoin;
traceZero:
	showTraceParticle = 0;
traceJoin:

	if (showTraceParticle && CFlat.m_partyTraceParticleSlot[port] == 0) {
		CFlat.m_partyTraceParticleSlot[port] = CFlat.GetFreeParticleSlot();
		putParticleTrace((port + 0x42U) | 0x100, CFlat.m_partyTraceParticleSlot[port], this, 1.0f, 0);
	} else if (!showTraceParticle && CFlat.m_partyTraceParticleSlot[port] != 0) {
		CFlat.EndParticleSlot(CFlat.m_partyTraceParticleSlot[port], 0);
		CFlat.m_partyTraceParticleSlot[port] = 0;
	}

	if (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId == 0 && (DbgMenuPcs.GetDbgFlag() & 0x400) != 0) {
		AStar.addRealTime(this);
	}

	if ((DbgMenuPcs.GetDbgFlag() & 0x2000) != 0) {
		int itemId;
		do {
			itemId = Math.Rand(0x155) + 0x9F;
			unsigned char* itemData = reinterpret_cast<unsigned char*>(Game.unkCFlatData0[2] + itemId * 0x48);
		} while ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48) == 0) ||
		         ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 2) & 0x0FFF) == 0) ||
		         ((*reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48 + 2) & 0x0FFF) == 0xFFFF) ||
		         (itemId == 400));

		if (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId == 0) {
			CGItemObj::CreateFromScript(0, 4, itemId, this, 0.0f, (CGItemObj::CCFS*)0);
			if (static_cast<unsigned int>(Math.Rand(10)) == 0) {
				CGItemObj::CreateFromScript(2, 4, 0x3039, this, 0.0f, (CGItemObj::CCFS*)0);
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
 * EN Address: 0x8013B6F4
 * EN Size: 688b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onFramePreCalc()
{
	if (m_scriptHandle == nullptr) {
		return;
	}

	CGCharaObj::onFramePreCalc();

	if (Game.unk_flat3_0xc7d0 != 0) {
		const Vec* chalicePos = &reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0)->m_worldPosition;
		m_targetDist = PSVECDistance(&m_worldPosition, chalicePos);
	}

	if (m_unk63CBits.m_bit80 != 0 && m_partyData.flags.commandActive == 0) {
		if (m_weaponNodeFlagAll.m_bits1.m_menuReady == 0) {
			unsigned short held = Pad.GetButton(m_animStateMisc);
			if (held != 0) {
				changeStat(0, 0, 0);
			}
		}

		int weaponIndex;
		int itemId;
		if (static_cast<int>(CFlatCenterState()) == 0) {
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCurrentWeaponItem(weaponIndex, itemId);
			if (m_partyData.weaponIndex != weaponIndex || m_partyData.weaponItemId != itemId) {
				bool needsImmediateChange = !m_weaponNodeFlagBits.m_prg ||
				    !m_weaponNodeFlagAll.m_bits1.m_shield || m_partyData.carryObject != 0 ||
				    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_statusTimers[0] != 0 ||
				    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_statusTimers[9] != 0 ||
				    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_statusTimers[3] != 0;
				changeWeapon(weaponIndex, itemId, needsImmediateChange);
			}
		}
	}

	bonus(2, 0, 0);

	if (Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
		if (m_partyData.carryObject != nullptr ||
		    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_hp == 0) {
			float speedScale;
			if (static_cast<int>(CFlatCenterState()) == 0) {
				speedScale = 1.25f;
			} else {
				speedScale = 1.0f;
			}
#ifdef VERSION_GCCP01
			m_moveBaseSpeed = static_cast<float>(static_cast<int>(1.2f * speedScale));
#else
			m_moveBaseSpeed = speedScale;
#endif
		} else {
			m_moveBaseSpeed = 2.0f;
		}
		m_moveBaseSpeed *= m_pushScale;
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
	    IsKindOf(0x6D) &&
	    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId != 0) {
		ghostPartyMog();
	} else {
		command();
		shouki();
	}

	m_partyData.carryTarget = (CGBaseObj*)0;
	m_partyData.secondaryTarget = (CGBaseObj*)0;
	m_partyData.targetSearchDistance = INFINITY;
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
	if (isMenuPcsCommandBusy()) {
		return;
	}

	PartyObjOverlay& party = m_partyData;
#define caravan reinterpret_cast<CCaravanWork*>(m_scriptHandle)
#define padSlot static_cast<char>(m_animStateMisc)
	int primaryAvailable = false;
	int primaryCommand = -1;
	int secondaryAvailable = false;
	int secondaryCommand = -1;
	int ringCommand = -1;
	int ringCommandArg = -1;

	if (party.flags.commandActive == 0) {

	if ((m_scriptHandle->m_hp != 0) &&
	    ((party.commandMode & 1) != 0) &&
	    Joybus.GetCtrlMode(m_animStateMisc) != 1) {
		int cmdDir = 0;

		if ((Pad.GetButton(padSlot) & 0x60) == 0x60) {
			caravan->SetIdxCmdList(0);
		} else if ((Pad.GetButtonDown(padSlot) & 0x20) != 0) {
			cmdDir = 1;
		} else if ((Pad.GetButtonDown(padSlot) & 0x40) != 0) {
			cmdDir = -1;
		}

		if (cmdDir != 0) {
			Sound.PlaySe(0x0C, 0x40, 0x7F, 0);
			CCaravanWork* cmdDirCaravan = caravan;
			cmdDirCaravan->SetIdxCmdList(cmdDirCaravan->GetNextCmdListIdx(cmdDirCaravan->GetIdxCmdList(), cmdDir));
		}

		const int cmdIdx = caravan->GetIdxCmdList();
		if (cmdIdx == 0) {
			ringCommand = 1;
		} else if (caravan->GetIdxCmdList() == 1) {
			ringCommand = 9;
		} else {
			CCaravanWork* delCaravan = caravan;
			const int itemId = delCaravan->GetCmdListItem(delCaravan->GetIdxCmdList());
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
	     (m_unk63CBits.m_bit80 != 0) &&
	     (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(this)[0x9B]) << 24) & 0xC0000000) >> 31) != 0)) &&
	    Joybus.GetCtrlMode(padSlot) != 1) {
		if (m_scriptHandle->m_hp != 0) {
		if (party.secondaryTarget != nullptr) {
			primaryAvailable = true;
			primaryCommand = 0x0C;
		}

		CGObject* target = party.target;
		if (target != nullptr) {
			unsigned char* targetBytes = reinterpret_cast<unsigned char*>(target);
			const int targetState = *reinterpret_cast<int*>(targetBytes + 0x500);

			switch (targetState) {
			case 0xCC:
				secondaryAvailable = true;
				secondaryCommand = 6;
				break;
			case 0x0A:
			case 0x0C:
			case 0x0D:
			case 0x0E:
			case 0x0F:
			case 0x10:
			case 0x11:
				if (*reinterpret_cast<unsigned int*>(targetBytes + 0x550) == 0) {
					secondaryAvailable = true;
					secondaryCommand = 4;
				}
				break;
			case 0x12:
			case 0x13:
			case 0x14:
			case 0x15:
			case 0x16:
			case 0x17:
			case 0x18:
			case 0x1C:
			case 0x1D:
			case 0x1E:
			case 0x1F:
			case 0x20:
			case 0x21:
			case 0x24:
				if (*reinterpret_cast<unsigned int*>(targetBytes + 0x550) == 0) {
					secondaryAvailable = true;
					if ((targetState == 0x24 && caravan->CanAddTmpArtifact(1) != 0) ||
					    (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x500) == 0x20 &&
					     caravan->CanAddGil(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x558)) != 0) ||
					    ((*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x500) != 0x24 &&
					      *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x500) != 0x20) &&
					     SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_inventoryItemCount + 1 <= 0x40)) {
						secondaryCommand = 0x17;
					} else {
						secondaryCommand = 4;
					}
				}
				break;
			case 0xC8:
				if (static_cast<int>(CFlatCenterState()) == 0) {
					secondaryAvailable = true;
					secondaryCommand = 0x0B;
				} else {
					primaryAvailable = true;
					primaryCommand = 0x0B;
				}
				break;
			case 0xC9:
				if (static_cast<int>(CFlatCenterState()) == 0) {
					secondaryAvailable = true;
					secondaryCommand = 0x0A;
				} else {
					primaryAvailable = true;
					primaryCommand = 0x0A;
				}
				break;
			case 0xCA:
				if (static_cast<int>(CFlatCenterState()) == 0) {
					secondaryAvailable = true;
					secondaryCommand = 0x1C;
				} else {
					primaryAvailable = true;
					primaryCommand = 0x1C;
				}
				break;
			}
		}

		if (party.carryObject != nullptr) {
			const int carryState = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.carryObject) + 0x500);
			secondaryAvailable = true;
			if (carryState == 0x0D) {
				secondaryCommand = 7;
			} else if (carryState == 0x0E) {
				secondaryCommand = 8;
			} else {
				secondaryCommand = 5;
			}
			primaryAvailable = true;
			primaryCommand = -1;
		}
		} else {
			primaryAvailable = true;
			primaryCommand = 0x1B;
		}
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
			if ((Pad.GetButtonDown(padSlot) & 0x20) != 0) {
				cmdDir = 1;
			} else if ((Pad.GetButtonDown(padSlot) & 0x40) != 0) {
				cmdDir = -1;
			}
			if (cmdDir != 0) {
				Sound.PlaySe(0x0C, 0x40, 0x7F, 0);
				int& charaCommand = Chara.MogFur().m_commandIndex;
				int adjusted = charaCommand + cmdDir;
				charaCommand = adjusted;
				if (adjusted < 0) {
					adjusted += 5;
				} else if (adjusted > 4) {
					adjusted -= 5;
				}
				charaCommand = adjusted;
			}
			const int charaCommand = Chara.MogFur().m_commandIndex;
			ringCommand = charaCommand + 0x1E;
			ringCommandArg = charaCommand;
		}
	}

	MenuPcs.GetRingMenu(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId)->SetBattleCommand(0, primaryCommand, -1);
	MenuPcs.GetRingMenu(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId)->SetBattleCommand(1, secondaryCommand, -1);
	MenuPcs.GetRingMenu(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId)->SetBattleCommand(2, ringCommand, ringCommandArg);

	}

	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != 0) {
		return;
	}

	const unsigned short trig = Pad.GetButtonDown(padSlot);
	if ((trig & 0x100) != 0) {
		if (primaryAvailable) {
			if (primaryCommand == 0x1B) {
				changeStat(0x20, 0, 0);
			}

			CGObject* scriptTarget = party.secondaryTarget != nullptr ?
				reinterpret_cast<CGObject*>(party.secondaryTarget) : party.target;
			party.flags.commandActive = 1;

			CFlatRuntime::CStack stack[2];
			stack[0].m_word = primaryCommand;
			stack[1].m_word = scriptTarget != nullptr ?
				*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(scriptTarget) + 0x30) : 0;
			gCFlatRuntime().SystemCall(this, 2, 0x14, 2, stack, 0);
			return;
		}

		if ((m_weaponNodeFlagAll.m_bits1.m_shield != 0) &&
		    (m_unk63CBits.m_bit80 != 0) &&
		    caravan->m_hp != 0 &&
		    ringCommand != -1 &&
		    (party.commandMode & 8) == 0) {
			party.unk6BC = caravan->GetIdxCmdList();
			const int cmdIdx = party.unk6BC;
			if (cmdIdx == 0) {
				int weaponItem;
				int weaponRef;
				caravan->GetCurrentWeaponItem(weaponItem, weaponRef);
				if (weaponItem != party.unk6BC ||
				    weaponRef != getEquipWeaponInventoryItem(caravan)) {
					changeWeapon(party.unk6BC, getEquipWeaponInventoryItem(caravan), 0);
					return;
				}

				m_itemId = getEquipWeaponInventoryItem(caravan);
				changeStat(7, 0, 0);
				return;
			}

			if (cmdIdx == 1) {
				const int element =
				    SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_tribeId;
				switch (element) {
				case 0:
				case 1:
					changeStat(8, 0, 0);
					break;
				case 2:
					changeStat(0x14, 0, 0);
					break;
				case 3:
					changeStat(0x15, 0, 0);
					break;
				}
				return;
			}

			const int itemId = caravan->GetCmdListItem(cmdIdx);
			const unsigned short itemKind = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48);
			switch (itemKind) {
			case 0x100:
				if (itemId == 0x103) {
					if (static_cast<unsigned int>(Math.Rand(3)) == 0) {
						ClearAllSta();
						setSta(0x1B, 900);
						caravan->DelCmdListAndItem(party.unk6BC, 1);
						return;
					}
					m_itemId = itemId;
					changeStat(2, 0, 2);
					return;
				}
				{
					SCfdItemRow* rows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
					m_itemId = rows[itemId].m_fieldA;
				}
				changeStat(2, 0, 0);
				return;
			case 0x1F5:
				m_itemId = itemId;
				changeStat(2, 0, 0);
				return;
			case 1: {
				int weaponItem;
				int weaponRef;
				caravan->GetCurrentWeaponItem(weaponItem, weaponRef);
				if (weaponItem != caravan->GetIdxCmdList() || weaponRef != itemId) {
					changeWeapon(caravan->GetIdxCmdList(), itemId, 0);
					return;
				}
				m_itemId = itemId;
				changeStat(7, 0, 0);
				return;
			}
			case 0x125:
				m_itemId = 0x220;
				changeStat(2, 0, 2);
				return;
			case 0x186:
			case 0x17D:
				if (useItem(itemId) != 0) {
					caravan->DelCmdListAndItem(party.unk6BC, 1);
				}
				return;
			case 0xDF: {
				SCfdItemRow* rows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
				m_itemId = rows[itemId].m_fieldA;
				changeStat(2, 0, 0);
				break;
			}
			}
		}
		return;
	}

	if ((Pad.GetButtonDown(padSlot) & 0x200) == 0) {
		return;
	}
	if (!secondaryAvailable) {
		return;
	}

	if ((m_weaponNodeFlagAll.m_bits1.m_shield != 0) &&
	    (m_unk63CBits.m_bit80 != 0) &&
	    caravan->m_hp != 0 &&
	    ringCommand != -1 &&
	    secondaryCommand == 6) {
		int weaponItem;
		int weaponRef;
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
		switch (kind) {
		case 1:
		case 0x100:
		case 0x125:
			kindClass = 0;
			break;
		case 0x190:
			kindClass = 1;
			break;
		default:
			kindClass = 2;
			break;
		}

		if (kindClass == 0 || kindClass == 2) {
			int addedItem;
			if (itemIdx >= 0x9F && itemIdx <= 0xFF) {
				caravan->AddTmpArtifact(itemIdx, &addedItem);
				System.Printf("\x83" "A\x81[\x83" "e\x83" "B\x83t\x83@\x83N\x83g\x92\xC7\x89\xC1 item=%d\n", *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504));
			} else {
				caravan->AddItem(itemIdx, &addedItem);
				System.Printf("\x83" "A\x83" "C\x83" "e\x83\x80\x92\xC7\x89\xC1 item=%d\n", *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504));
			}
			if (kindClass == 0 && caravan->CanAddComList(1) != 0) {
				int addedSlot;
				caravan->AddComList(addedItem, &addedSlot);
				System.Printf("\x83R\x83}\x83\x93\x83h\x83\x8A\x83X\x83g\x92\xC7\x89\xC1 itemidx=%d comidx=%d\n", addedItem, addedSlot);
			}
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(party.target) + 0x560) != 1) {
				bonus(4, *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504), 0);
			}
		} else if (itemIdx == 0x190) {
			bonus(5, 0x190, 0);
			System.Printf("\x83M\x83\x8B = %d\n", *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x558));
			caravan->AddGil(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x558));
			if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(party.target) + 0x560) != 1) {
				bonus(4, *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(party.target) + 0x504), 0);
			}
		}
	}

	CGObject* tgt = party.target;
	party.flags.commandActive = 1;
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
	m_partyData.target = target;

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
	if (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_hp != 0 &&
	    (CFlatRuntime2Storage().m_gameFlagBits.m_flagBit7 != 0 ||
	     CFlatRuntime2Storage().m_gameFlagBits.m_flagBit4 != 0) &&
	    m_weaponNodeFlagAll.m_bits1.m_shield != 0) {

		const Vec* chalicePos = &reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0)->m_worldPosition;
		float chaliceDist = PSVECDistance(&m_worldPosition, chalicePos);
		if (1.1f * Game.unkFloat_0xca10 < chaliceDist ||
		    CFlatRuntime2Storage().m_gameFlagBits.m_flagBit4 != 0) {
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
			if (0.95f * Game.unkFloat_0xca10 <= chaliceDist) {
				int flagFrame = m_updateCounter;
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
		    CFlatRuntime2Storage().m_gameFlagBits.m_flagBit4 == 0) {
			int healCount = 0;
			if (m_partyData.carryObject == reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0)) {
				if (isFrameInterval(m_updateCounter, *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 4))) {
					healCount = 1;
				}
			} else {
				if (isFrameInterval(m_updateCounter, *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 6))) {
					healCount = 1;
				}
			}
			const unsigned int periodicHeal = static_cast<unsigned char>(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_equipEffectParams[4]);
			if (periodicHeal != 0 && isFrameInterval(m_updateCounter, periodicHeal)) {
				healCount += 1;
			}
			if (healCount != 0) {
				addHp(healCount, static_cast<CGPrgObj*>(0));
			}
		} else if (m_unk688 == 2) {
			unsigned int damageInterval = reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_romWork[CRomWork::ShoukiDamageIntervalOffset];
			if ((reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_equipEffectFlags & 0x2000) != 0) {
				damageInterval += *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 8);
			}
			if (isFrameInterval(m_updateCounter, damageInterval)) {
				playSe3D(0x19, 0x32, 0x96, 0, 0);
				if (CFlatRuntime2Storage().m_gameFlagBits.m_flagBit5 == 0) {
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
}

/*
 * --INFO--
 * PAL Address: 0x80120b94
 * PAL Size: 4112b
 * EN Address: 0x8011fef4
 * EN Size: 4112b
 * JP Address: 0x8011ca7c
 * JP Size: 4116b
 */
void CGPartyObj::onFrameStat()
{
	if (m_scriptHandle == nullptr) {
		return;
	}

	switch (m_lastStateId) {
	case 0:
		if (m_stateFrame == 0) {
			if (m_partyData.flags.flag02) {
				reqAnim(0x27, 0, 0);
				m_partyData.flags.flag02 = 0;
			} else {
				reqAnim(-1, 0, 0);
			}
		}
		if ((m_partyData.flags.commandActive != 0) ||
		    (m_scriptHandle->m_statusTimers[0] != 0) ||
		    (m_scriptHandle->m_statusTimers[9] != 0) ||
		    (m_scriptHandle->m_statusTimers[3] != 0)) {
			m_weaponNodeFlagAll.m_bits1.m_menuReady = 0;
			m_unk63CBits.m_bit80 = 0;
		} else {
			m_weaponNodeFlagAll.m_bits1.m_menuReady = 1;
			m_unk63CBits.m_bit80 = 1;
		}
		if (((DbgMenuPcs.GetDbgFlag() & 8) != 0) ||
		    ((Game.unk_flat3_0xc7d0 != 0) &&
		     (Joybus.GetCtrlMode(m_animStateMisc) == 1) &&
		     (m_unk63CBits.m_bit80 != 0) &&
		     (m_weaponNodeFlagAll.m_bits1.m_shield != 0) &&
		     (m_weaponNodeFlagAll.m_bits1.m_menuReady != 0) &&
		     (m_partyData.flags.commandActive == 0))) {
			if ((0.95f * Game.unkFloat_0xca10 < m_targetDist) &&
			    (m_scriptHandle->m_statusTimers[0] == 0) &&
			    (m_scriptHandle->m_statusTimers[9] == 0) &&
			    (m_scriptHandle->m_statusTimers[3] == 0) &&
			    (Game.m_gameWork.m_bossArtifactStageIndex != 0x17)) {
				Vec moveVec;
				CVector diff = CVector(reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0)->m_worldPosition) - CVector(m_worldPosition);
				moveVec.x = diff.x;
				moveVec.y = diff.y;
				moveVec.z = diff.z;
				moveVector(&moveVec, m_moveBaseSpeed, 0x0F);
			}
		}
		if ((m_weaponNodeFlagAll.m_bits1.m_shield != 0) &&
		    Game.m_gameWork.m_menuStageMode != 0 &&
		    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId == 0) {
			CGPartyObj* gbaParty = Game.m_partyObjArr[1];
			CGObject* chaliceObj = reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0);
			if (gbaParty != nullptr && gbaParty->m_lastStateId == 0) {
				unsigned short held = Pad.GetButton(m_animStateMisc);
				int heldMask = held & 0x400;
				unsigned short up = Pad.GetButtonUp(m_animStateMisc);
				if ((up & 0x400) != 0) {
					if (CGPartyObj::m_ghostWork.holdTimer < 10 &&
					    m_partyData.carryObject != chaliceObj) {
						CGPartyObj::m_ghostWork.flagBits.flag80 = (gbaParty->m_partyData.carryObject != nullptr);
					}
				} else if (heldMask != 0) {
					CGPartyObj::m_ghostWork.holdTimer++;
					if (CGPartyObj::m_ghostWork.holdTimer >= 10 && CGPartyObj::m_ghostWork.moodTimer == 0) {
						CGPartyObj::m_ghostWork.moodTimer = 2;
					}
				} else {
					CGPartyObj::m_ghostWork.holdTimer = 0;
				}
			}
		}
		break;
	case 0x20:
		if (m_stateFrame == 0) {
			reqAnim(0x31, 0, 0);
		} else if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
		}
		break;
	case 6:
		statCharge();
		break;
	case 7:
		if (m_stateFrame == 0) {
			m_partyData.unk6D0 = 0;
		}
		if ((Pad.GetButton(m_animStateMisc) & 0x100) == 0) {
			changeStat(1, 0, 0);
		} else {
			m_partyData.unk6D0++;
#ifdef VERSION_GCCP01
			if (m_partyData.unk6D0 >= 6) {
#else
			if (m_partyData.unk6D0 >= 8) {
#endif
				changeStat(6, 0, 0);
			} else {
				if ((Pad.GetButtonDown(m_animStateMisc) & 0x200) != 0) {
					changeStat(0, 0, 0);
				}
			}
		}
		break;
	case 0x0B:
		statCarry();
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
#ifdef VERSION_GCCP01
		if (m_stateFrame == 4) {
#else
		if (m_stateFrame == 5) {
#endif
			changeWeapon(m_partyData.pendingWeaponIndex, m_partyData.pendingWeaponItemId, 1);
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
				m_alpha = 0.25f;
				reqAnim(0x16, 1, 0);
				enableDamageCol(0);
			}
			if ((Pad.GetButton(m_animStateMisc) & 0x100) == 0) {
#ifdef VERSION_GCCP01
				if (m_subFrame >= 0x19) {
#else
				if (m_subFrame >= 0x1E) {
#endif
					playSe3D(0x30, 0x32, 0x96, 0, 0);
				}
				m_alpha = 1.0f;
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
#ifdef VERSION_GCCP01
		if (m_stateFrame == 3 && Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
#else
		if (m_stateFrame == 4 && Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
#endif
			moveVectorHRot(3.1415927f + m_rotTargetY, 0.0f, 1.0f, 10);
		}
		if (isLoopAnim() != 0) {
			changeStat(0, 0, 0);
			enableDamageCol(1);
		}
		break;
	case 0x1A:
		statKorobi();
		break;
	case 0x22: {
#define script (reinterpret_cast<unsigned char*>(m_scriptHandle))
		if (m_stateFrame == 0) {
			if (m_partyData.flags.flag04) {
				if (*reinterpret_cast<unsigned short*>(script + 0x1C) == 0) {
					addHp(*reinterpret_cast<unsigned short*>(script + 0x1A), static_cast<CGPrgObj*>(0));
				}
				m_partyData.flags.flag04 = 0;
			}
			enableDamageCol(1);
			setIdleMotion();
			if (m_currentAnimSlot == 6) {
				reqAnim(0x26, 0, 0);
			} else {
				reqAnim(0x27, 0, 0);
			}
			if (*reinterpret_cast<unsigned short*>(script + 0x1C) != 0) {
				endPSlotBit(0x10000);
				m_alpha = 1.0f;
				m_bgColMask |= 0x1000E;
				m_scriptHandle->m_statusTimers[5] = 0x5A;
			} else {
				m_alpha = 0.3f;
				m_bgColMask &= 0xFFFEFFF1;
				int port = SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_joybusCaravanId;
				endPSlotBit(0x10000);
				putParticle(port + 3U | 0x100, m_particleSlots[16], this, 1.0f, 0);
				playSe3D(0x2D, 0x32, 0x96, 0, 0);
			}
		} else if (isLoopAnim() != 0) {
			if (*reinterpret_cast<unsigned short*>(script + 0x1C) != 0) {
				m_partyData.flags.flag02 = 1;
			}
			changeStat(0, 0, 0);
		}
#undef script
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
	if (enabled != 0) {
		resetIgnoreHit();
		bool col0Enabled = false;
		if (isFriendly == 0 || (hitMask & 1) != 0) {
			col0Enabled = true;
		}
		m_attackColliders[0].m_hitMask = col0Enabled != false;
		bool col1Enabled = false;
		if (isFriendly != 0 && (hitMask & 2) != 0) {
			col1Enabled = true;
		}
		m_attackColliders[1].m_hitMask = col1Enabled != false;
		bool col2Enabled = false;
		if (isFriendly != 0 && (hitMask & 4) != 0) {
			col2Enabled = true;
		}
		m_attackColliders[2].m_hitMask = col2Enabled != false;
	} else {
		m_attackColliders[0].m_hitMask = 0;
		m_attackColliders[1].m_hitMask = 0;
		m_attackColliders[2].m_hitMask = 0;
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
	unsigned int hitMask = 4;
	if (m_scriptHandle->m_hp != 0) {
		hitMask = 8;
	}

	if (onOff != 0 &&
	    (Game.m_gameWork.m_menuStageMode == 0 ||
	     Game.m_gameWork.m_bossArtifactStageIndex >= 0x0F ||
	     !IsKindOf(0x6D) ||
	     reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId == 0)) {
		m_damageColliders[0].m_hitMask = hitMask;
		m_damageColliders[1].m_hitMask = hitMask;
	} else {
		m_damageColliders[0].m_hitMask = 0;
		m_damageColliders[1].m_hitMask = 0;
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
 * EN Address: 0x8013D870
 * EN Size: 2412b
 * JP Address: 0x8011bef4
 * JP Size: 2432b
 */
void CGPartyObj::statCharge()
{
	switch (m_subState) {
	case 0:
		if (m_subFrame == 0) {
			m_comboFramePrev = 0;
			reqAnim(m_attackAnimId, 0, 0);
			putParticle(0x210, m_particleSlots[3], reinterpret_cast<CGObject*>(this), 1.0f, 0x7EE);
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
				putParticle(0x578, 0, reinterpret_cast<CGObject*>(this), 1.0f, 0x80D);
			} else if (counter == window << 1) {
				putParticle(0x577, 0, reinterpret_cast<CGObject*>(this), 1.0f, 0x80D);
			}
		}
		m_comboFramePrev++;
		break;
	case 2: {
		if (m_subFrame == 0) {
			endPSlotBit(8);
			bonus(0x18, 0, 0);
		}
#ifdef VERSION_GCCP01
		if (m_subFrame == 5 && m_comboItemState >= 0) {
#else
		if (m_subFrame == 6 && m_comboItemState >= 0) {
#endif
			endPSlotBit(0x20);
			CFlat.ResetParticleWork(
			    (m_comboItemState + 0x1C + reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId * 5) | 0x400,
			    m_particleSlots[5]);
			CFlat.SetParticleWorkBind(reinterpret_cast<CFlatRuntime::CObject*>(this));
			CFlat.PutParticleWork();
			playSe3D(m_comboItemState + 0x7EB, 0x32, 0x96, 0, 0);
		}

		int phase = (m_comboItemState != -1) ? m_subFrame - 0x10 : m_subFrame;
		SCfdItemRow* cfdRows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
		int itemType = cfdRows[m_itemId].m_fieldA & 0xFF;

		if (phase == 0) {
			if (m_comboLinkCount != 0) {
				sendCombiToScript__10CGCharaObjFP10CGCharaObjii(this, reinterpret_cast<CGCharaObj*>(m_comboScriptArg), m_comboScriptMode);
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
				case 0x1FC:
					base = 0x1B;
					break;
				case 0x23D:
					base = 0x6F;
					break;
				}
				if (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_hp > 1) {
					addHp(-1, static_cast<CGPrgObj*>(0));
				}
				putParticle((base + reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag) | 0x500, 0,
				    reinterpret_cast<CGObject*>(this), 1.0f, 0);
			}
		}

		SCfdItemRow* phaseRows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
		if (phase == phaseRows[m_itemId].m_field20) {
			putParticleFromItem(m_itemId, 3, m_particleSlots[0], static_cast<Vec*>(0));
		}

		SPartyAnimRow* animRows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
		SCfdItemRow* rowRows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
		SChargeRec* table = &animRows[reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag +
		                            reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId * 2]
		                        .m_chargeAttacks[rowRows[m_itemId].m_fieldA >> 8];

		SChargePhase* p = table->m_phases;
		for (int i = 0; i < 5; i++, p++) {
			if (phase == p->m_moveStartFrame && Game.m_gameWork.m_bossArtifactStageIndex != 0x17) {
				unsigned int dist = (p->m_moveEndFrame - p->m_moveStartFrame) + 1;
				if (i == 0 && (itemType == 2 || itemType == 3)) {
					Vec delta;
					PSVECSubtract(&m_comboCenter, &m_worldPosition, &delta);
					float mag = PSVECMag(&delta);
					CVector dest(m_comboCenter);
					SCfdItemRow* flagRows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
					if ((flagRows[m_itemId].m_field32 & 0x10) != 0) {
						unsigned int maxReach = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x70);
						if (static_cast<float>(maxReach) < mag) {
							dest = CVector(m_worldPosition) +
							       (CVector(delta) * (mag - static_cast<float>(maxReach))) / mag;
							mag = mag - static_cast<float>(*reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x70));
						} else {
							mag = 0.0f;
						}
					}
					if (0.0f != mag) {
						Move(reinterpret_cast<Vec*>(&dest), mag / static_cast<float>(static_cast<int>(dist)), dist, 1, 1, 0, 1);
					}
				} else {
					moveVectorRot(m_rotTargetY, 0.0f, 0.01f * static_cast<float>(p->m_moveSpeed),
					    dist);
				}
			}
			if (phase == p->m_attackStartFrame) {
				enableAttackCol(1, 1, p->m_attackCol);
			}
			if (phase == p->m_attackEndFrame) {
				enableAttackCol(0, 0, 0);
			}
		}

		if (phase >= 0 && isLoopAnim() != 0) {
			changeStat(0, 0, 0);
			return;
		}

		unsigned int twistLimit = table->m_twistLimit;
		if (twistLimit != 0) {
			float angLimit = 0.017453292f * static_cast<float>(twistLimit);
			if (phase == table->m_twistStartFrame) {
				CVector diff = CVector(m_comboCenter) - CVector(m_worldPosition);
				float horiz = sqrtf(diff.z * diff.z + diff.x * diff.x);
				if (0.0f != diff.y && 0.0f != horiz) {
					float ang = -static_cast<float>(atan2(diff.y, horiz));
					m_twistTarget = (ang < -angLimit) ? -angLimit : ((angLimit < ang) ? angLimit : ang);
				}
			} else if (phase == table->m_twistEndFrame) {
				m_twistTarget = 0.0f;
			}
		}
		break;
	}
	}

	if (m_subState <= 1) {
		int slot = m_animStateMisc;
		if ((Pad.GetButton(slot) & 0x100) == 0) {
			if (m_subState == 0 || (m_subState == 1 && m_comboState == 0)) {
				changeStat(0, 0, 0);
			} else {
				m_comboFrame++;
			}
		} else if ((Pad.GetButton(slot) & 0x200) != 0) {
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

	unsigned short trig = Pad.GetButtonDown(m_animStateMisc);
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
			if (obj->m_scriptHandle->m_hp == 0) {
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
			if (m_worldPosition.y + 2.0f * obj->m_bodyEllipsoidRadius >= obj->m_worldPosition.y &&
			    m_worldPosition.y - 2.0f * obj->m_bodyEllipsoidRadius <= obj->m_worldPosition.y) {
				Vec diff;
				PSVECSubtract(&obj->m_worldPosition, &m_worldPosition, &diff);
				diff.y = 0.0f;
				float distSq = PSVECSquareMag(&diff);
				float radiusSq = radius * radius;
				if (0.0f < distSq && distSq < radiusSq) {
					float absAngle = fabsf(dstTargetRot(static_cast<CGPrgObj*>(obj)));
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
 * EN Address: 0x8013E500
 * EN Size: 724b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::onStatAttack(int chargeType)
{
	PartyObjOverlay& party = m_partyData;

	if (chargeType == 0) {
		if (m_stateFrame != 0) {
			return;
		}

		party.unk6CC = party.attackSel;
		party.attackSel = 0;
		party.commandFlagBits.commandActive = 0;
		party.commandFlagBits.flag40 = 0;

		CGPrgObj* target = getBestAngleObject(2.0f * m_bodyEllipsoidRadius, 0.7853982f);
		if (target != 0) {
			m_rotTargetY = atan2(target->m_worldPosition.x - m_worldPosition.x,
			                     target->m_worldPosition.z - m_worldPosition.z);
		}
		return;
	}

	const int chain = party.unk6CC;
	SPartyAnimRow* rows = reinterpret_cast<SPartyAnimRow*>(Game.unk_flat3_field_30_0xc7e0);
	SAtkRec* attackEntry = &rows[reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_genderFlag +
	                           reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tribeId * 2]
	                       .m_attacks[chain];

	if (chain > 0 && m_stateFrame == attackEntry->m_moveStartFrame && !Game.m_gameWork.IsStreamStage()) {
		const float stepSpeed = 0.01f * static_cast<float>(attackEntry->m_moveSpeed);
		moveVectorRot(m_rotTargetY, 0.0f, stepSpeed,
		    (attackEntry->m_moveEndFrame - attackEntry->m_moveStartFrame) + 1);
	}

	if (m_stateFrame >= attackEntry->m_comboStartFrame &&
	    m_stateFrame <= attackEntry->m_comboEndFrame) {
		if ((Pad.GetButtonDown(m_animStateMisc) & 0x100) != 0) {
			party.commandFlagBits.commandActive = 1;
		}
	} else {
		if ((Pad.GetButtonDown(m_animStateMisc) & 0x100) != 0) {
			party.commandFlagBits.flag40 = 1;
		}
	}

	if (m_stateFrame == attackEntry->m_comboNextFrame) {
		if (party.commandFlagBits.commandActive != 0 && party.commandFlagBits.flag40 == 0 && party.unk6CC < 2) {
			party.attackSel = party.unk6CC + 1;
			changeStat(1, 0, 0);
			return;
		}
	}

	if (m_stateFrame == m_castFrameCurrent) {
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
		int padSlot = m_animStateMisc;
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
 * EN Address: 0x8011ED08
 * EN Size: 52b
 * JP Address: 0x8011B910
 * JP Size: 52b
 */
void CGPartyObj::putComboParticle()
{
	putParticle(0x153, 0, this, 1.0f, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8011f5a4
 * PAL Size: 1028b
 * EN Address: 0x8013E87C
 * EN Size: 792b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::putTargetParticle(int targetSide, int doInit)
{
	PartyObjOverlay& party = m_partyData;
	if (doInit != 0) {
		party.flags.flag40 = targetSide;
		party.flags.flag10 = 0;

		Vec rayDir;
		rayDir.x = sinf(m_rotTargetY) * 10.0f;
		rayDir.y = 0.0f;
		rayDir.z = cosf(m_rotTargetY) * 10.0f;

		Vec faceNormal;
		float radius;
		if (isGhostPartyTargetMode(this)) {
			radius = 3.0f;
		} else {
			radius = 4.0f;
		}

		if (MapPcs.CheckHitCylinderNear(CVector(m_worldPosition) + CVector(0.0f, 5.0f, 0.0f), &rayDir, radius, 0x30) != 0) {
			MapPcs.CalcHitPosition(&m_comboCenter);
		} else {
			PSVECAdd(CVector(m_worldPosition) + CVector(0.0f, 5.0f, 0.0f), &rayDir, &m_comboCenter);
		}
		if (MapPcs.CheckHitCylinderNear(&m_comboCenter, CVector(0.0f, -100.0f, 0.0f), 0.0f, 0x30) != 0) {
			MapPcs.CalcHitPosition(&m_comboCenter);
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_targetCursorPosA = m_comboCenter;
			MapPcs.GetHitFaceNormal(&faceNormal);
			reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_targetCursorPosB = faceNormal;
		}
		m_comboTarget = m_comboCenter;
	}

	endTargetParticle();
	CCaravanWork* work = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
	int ofs = (targetSide != 0) ? 4 : 0;
	CFlat.ResetParticleWork((ofs + 0x47 + work->m_joybusCaravanId) | 0x100, m_particleSlots[4]);
	CFlat.SetParticleWorkPos(m_comboCenter, 0.0f);
	CFlat.SetParticleWorkParam(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId, 0);
	CFlat.PutParticleWork();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: 0x8013EB94
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CGPartyObj::endTargetParticle()
{
	endPSlotBit(0x10);
}

/*
 * --INFO--
 * PAL Address: 0x8011F574
 * PAL Size: 48b
 * EN Address: 0x8013EBC0
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPartyObj::isDispTarget()
{
	return (m_lastStateId == 2 || m_lastStateId == 6) && m_comboState != 0;
}

/*
 * --INFO--
 * PAL Address: 0x8011F520
 * PAL Size: 84b
 * EN Address: 0x8013EC20
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
int CGPartyObj::isRideTarget()
{
	return isDispTarget() && m_partyData.flags.flag40;
}

/*
 * --INFO--
 * PAL Address:	8011ead4
 * PAL Size:	2636b
 * EN Address:	0x8013EC84
 * EN Size:	2464b
 * JP Address:	TODO
 * JP Size:	TODO
 */
void CGPartyObj::checkTargetParticle()
{
	PartyObjOverlay& party = m_partyData;

	if (party.flags.flag10) {
		putTargetParticle(party.flags.flag40, 0);
		party.flags.flag10 = 0;
	}

	CVector input;
	input.Identity();

	if ((Game.m_gameWork.m_menuStageMode == 0) ||
	    (Game.m_gameWork.m_bossArtifactStageIndex >= 0x0F) ||
	    !IsKindOf(0x6D) ||
	    (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId == 0)) {
		if ((DbgMenuPcs.GetDbgFlag() & 0x100) != 0) {
			input.x -= Pad.GetLeftStickX(m_animStateMisc);
			input.z += Pad.GetLeftStickY(m_animStateMisc);
		}

			if (input.x == 0.0f && input.z == 0.0f) {
				unsigned short held = Pad.GetButton(m_animStateMisc);
			if ((held & 1) != 0) {
				input.x += 1.0f;
			}
			if ((held & 2) != 0) {
				input.x -= 1.0f;
			}
			if ((held & 8) != 0) {
				input.z += 1.0f;
			}
			if ((held & 4) != 0) {
				input.z -= 1.0f;
			}
		}
	} else {
		CGPartyObj* leader = Game.m_partyObjArr[0];
		if ((leader->m_lastStateId == 2 || leader->m_lastStateId == 6) &&
		    leader->m_comboState != 0) {
			CVector toLeaderTarget = CVector(m_comboCenter) - CVector(leader->m_comboCenter);
			if (PSVECMag(toLeaderTarget) > 10.0f) {
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
		PSVECScale(reinterpret_cast<Vec*>(&input), reinterpret_cast<Vec*>(&input), 2.0f);

			float angle;
			if (isGhostPartyTargetMode(this)) {
				angle = 3.1415927f;
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

		maxRange = 0.0f;
		if (m_lastStateId == 2) {
			CCaravanWork* work = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
			unsigned int vNode = work->m_romWork[0xCD];
			SCfdItemRow* rows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
			unsigned int vItem = rows[m_itemId].m_field30;
			float base = static_cast<float>(vItem) + static_cast<float>(vNode);
			int vFlag;
			if ((work->m_equipEffectFlags & 0x4000) != 0) {
				vFlag = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x0A);
			} else {
				vFlag = 0;
			}
			maxRange += base + static_cast<float>(vFlag);
		} else {
			CCaravanWork* work = reinterpret_cast<CCaravanWork*>(m_scriptHandle);
			unsigned int vNode = work->m_romWork[0xCE];
			SCfdItemRow* rows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
			unsigned int vItem = rows[m_itemId].m_field30;
			float base = static_cast<float>(vItem) + static_cast<float>(vNode);
			int vFlag;
			if ((work->m_equipEffectFlags & 0x8000) != 0) {
				vFlag = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x0C);
			} else {
				vFlag = 0;
			}
			maxRange += base + static_cast<float>(vFlag);
		}

		CVector move = CVector(*targetPos) - CVector(m_worldPosition);
		if (dist > maxRange) {
			Vec scaled;
			PSVECScale(move, &scaled, maxRange / dist);
			PSVECAdd(&m_worldPosition, &scaled, targetPos);
		}

		move = CVector(*targetPos) - CVector(*centerPos);
		int iter = 4;
		do {
			float radius;
			if (isGhostPartyTargetMode(this)) {
				radius = 3.0f;
			} else {
				radius = 4.0f;
			}

			if (MapPcs.CheckHitCylinderNear(CVector(*centerPos) + CVector(0.0f, 5.0f, 0.0f), move, radius, 0x30) == 0) {
				break;
			}
			if (iter == 1) {
				move.x = 0.0f;
				move.y = 0.0f;
				move.z = 0.0f;
			} else {
				MapPcs.CalcHitSlide(move, 10.0f);
			}
			iter--;
		} while (iter > 0);

		PSVECAdd(CVector(*centerPos) + CVector(0.0f, 5.0f, 0.0f), move, targetPos);

		if (MapPcs.CheckHitCylinderNear(targetPos, CVector(0.0f, -100.0f, 0.0f), 0.0f, 0x30) != 0) {
			MapPcs.CalcHitPosition(targetPos);
			{
				Vec faceNormal;
				reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_targetCursorPosA = *targetPos;
				MapPcs.GetHitFaceNormal(&faceNormal);
				reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_targetCursorPosB = faceNormal;
			}
		}

		*centerPos = *targetPos;
#undef targetPos
#undef centerPos
	} else {
		party.flags.flag20 = 0;
	}

	CVector delta = CVector(m_comboCenter) - CVector(m_worldPosition);
	if (0.0f < PSVECMag(delta)) {
		m_rotTargetY = atan2(delta.x, delta.z);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011E870
 * PAL Size: 612b
 * EN Address: 0x8013F624
 * EN Size: 448b
 * JP Address: 0x8011a7e8
 * JP Size: 612b
 */
void CGPartyObj::moveCenterTargetParticle()
{
	int step = m_subFrame;

#ifdef VERSION_GCCP01
	if (step >= 5) {
#else
	if (step >= 6) {
#endif
		return;
	}

	float wave = static_cast<float>(sin(1.5707964f * ((float)(step + 1) / 6.0f)));

	CVector hitPos = CVector(m_comboTarget) + (CVector(m_comboCenter) - CVector(m_comboTarget)) * wave;

	Vec hitNormal;
	if (MapPcs.CheckHitCylinderNear(hitPos + CVector(0.0f, 5.0f, 0.0f),
	                                CVector(0.0f, -100.0f, 0.0f), 0.0f, 0x30) != 0) {
		MapPcs.CalcHitPosition(hitPos);
		MapPcs.GetHitFaceNormal(&hitNormal);

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
 * EN Address: 0x8013F7E4
 * EN Size: 1200b
 * JP Address: 0x8011a2a4
 * JP Size: 1348b
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
			if ((m_stateArg & 2) != 0) {
				reinterpret_cast<CCaravanWork*>(m_scriptHandle)->DelCmdListAndItem(m_partyData.unk6BC, 1);
			}
		}
#ifdef VERSION_GCCP01
		if (m_subFrame == 8 && m_comboLinkCount != 0) {
#else
		if (m_subFrame == 10 && m_comboLinkCount != 0) {
#endif
			sendCombiToScript__10CGCharaObjFP10CGCharaObjii(this, reinterpret_cast<CGCharaObj*>(m_comboScriptArg), m_comboScriptMode);
		}
		moveCenterTargetParticle();
#ifdef VERSION_GCCP01
		if (m_subFrame >= 0x12) {
#else
		if (m_subFrame >= 0x16) {
#endif
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

	int magicReady = (m_itemId == 0x103) ? 1 : 0;

	if (!isGhostPartyTargetMode(this)) {
		unsigned short held = Pad.GetButton(m_animStateMisc);
		if ((held & 0x100) == 0) {
			if (m_subState == 0 || (m_subState == 1 && m_comboState == 0)) {
				if (magicReady == 0) {
					changeStat(0, 0, 0);
				}
			} else {
				if (m_comboFrame == 1) {
					putParticleTrace(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId + 0x4FU | 0x100,
					    m_particleSlots[8], this, 1.0f, 0);
					playSe3D(0x3E, 0x32, 0x96, 0, 0);
				}
				m_comboFrame++;
			}
		} else {
			unsigned short trig = Pad.GetButton(m_animStateMisc);
			if ((trig & 0x200) != 0 && magicReady == 0) {
				changeStat(0, 0, 0);
			}
		}
		return;
	}

	if (m_subState == 1 && m_comboState != 0 &&
	    CGPartyObj::m_ghostWork.flagBits.flag40 != 0) {
		if (m_comboFrame == 1) {
			putParticleTrace(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId + 0x4FU | 0x100,
			    m_particleSlots[8], this, 1.0f, 0);
			playSe3D(0x3E, 0x32, 0x96, 0, 0);
		}
		m_comboFrame++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011e1b4
 * PAL Size: 376b
 * EN Address: 0x8011d514
 * EN Size: 376b
 * JP Address: 0x8011a12c
 * JP Size: 376b
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
			if (m_partyData.flags.flag04) {
				putParticleFromItem(0x220, 2, 0, &m_worldPosition);
				putParticleFromItem(0x220, 3, 0, &m_worldPosition);
				changeSubStat(2);
			}
#ifdef VERSION_GCCP01
		} else if (m_subFrame == 0x19) {
#else
		} else if (m_subFrame == 0x1E) {
#endif
			changeStat(0x22, 0, 0);
		}
		break;
	case 2:
#ifdef VERSION_GCCP01
		if (m_subFrame >= 0xBB) {
#else
		if (m_subFrame >= 0xE1) {
#endif
			if (System.GetErrorLevel() >= 2U) {
				System.Printf("\x89\xBD\x82\xE7\x82\xA9\x82\xCC\x8C\xB4\x88\xF6\x82\xC5" "15\x95" "b\x8A\xD4\x82\xCC\x8A\xD4\x82\xC9\x83t\x83" "F\x83j\x83" "b\x83N\x83X\x82\xCC\x94\xF6\x82\xAA\x82\xA9\x82\xA9\x82\xE7\x82\xC8\x82\xA9\x82\xC1\x82\xBD\x82\xCC\x82\xC5\x8B\xAD\x90\xA7\x93I\x82\xC9\x95\x9C\x8A\x88\x82\xB3\x82\xB9\x82\xDC\x82\xB7\x81" "B\n");
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
	if ((m_partyData.partyFlags & 0x20) != 0) {
		checkTargetParticle();
	}

	if (m_lastStateId == 0) {
		unsigned short held = Pad.GetButton(m_animStateMisc);
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
	if (reinterpret_cast<CGObject*>(other)->IsKindOf(5)) {
		if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(other) + 0x500) == 0x23) {
			m_partyData.secondaryTarget = other;
		} else {
			float dist = PSVECDistance(&m_worldPosition, &reinterpret_cast<CGObject*>(other)->m_worldPosition);
			if (dist < m_partyData.targetSearchDistance) {
				m_partyData.carryTarget = other;
				m_partyData.targetSearchDistance = dist;
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
	m_partyData.flags.commandActive = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8011da84
 * PAL Size: 1620b
 * EN Address: 0x8013FFA4
 * EN Size: 980b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::carry(int carryType, CGObject* object, int forceMode)
{
	if (carryType == 0) {
		if (m_partyData.carryObject != nullptr) {
			carry(1, (CGObject*)0, 1);
		}

		if (forceMode != 0) {
			m_partyData.carryObject = object;
			setIdleMotion();
			reinterpret_cast<CGItemObj*>(m_partyData.carryObject)->carry(this, 0, 0);
		} else {
			m_partyData.carryObject = object;
			rotTarget(reinterpret_cast<CGPrgObj*>(m_partyData.carryObject));
			changeStat(0x0B, 0, 0);
			reinterpret_cast<CGItemObj*>(m_partyData.carryObject)->carry(this, 0, getCarryAnimNo(this, 0));
		}
	} else if ((carryType == 1 || carryType == 2) && m_partyData.carryObject != nullptr) {
		if (forceMode != 0) {
			if (m_lastStateId == 0x0B) {
				changeStat(0, 0, 0);
			}
			reinterpret_cast<CGItemObj*>(m_partyData.carryObject)->carry(this, carryType, 0);
			m_partyData.carryObject = (CGObject*)0;
			setIdleMotion();
		} else {
			changeStat((carryType == 1) ? 0x0C : 0x0D, 0, 0);
			reinterpret_cast<CGItemObj*>(m_partyData.carryObject)->carry(this, carryType, getCarryAnimNo(this, 1));
			m_partyData.carryObject = (CGObject*)0;
		}
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CGPartyObj::statCarry()
{
	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
	    IsKindOf(0x6D) &&
	    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId != 0) {
		static float d;
		static float h;
		CGObject* chalice = reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0);
		if (m_stateFrame == 0) {
			CancelMove(1);
			d = m_targetDist - 6.0f;
			h = chalice->m_worldPosition.y - m_worldPosition.y;
		}

		if (m_stateFrame <= kPartyObjCarryArcFrames) {
			const float phase = sinf((3.1415927f * static_cast<float>(m_stateFrame)) / kPartyObjCarryArcFrames);
			m_extraMoveVec.x = d * (phase * sinf(m_rotBaseY));
			m_extraMoveVec.z = d * (phase * cosf(m_rotBaseY));
			m_extraMoveVec.y = h * phase + 10.0f;
		}
	}
	if (m_stateFrame == 0) {
		reqAnim(0x0D, 0, 0);
		playSe3D(0x22, 0x32, 0x96, 0, 0);
	}
	if (isLoopAnim() != 0) {
		setIdleMotion();
		changeStat(0, 0, 0);
		m_extraMoveVec.x = 0.0f;
		m_extraMoveVec.z = 0.0f;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011d710
 * PAL Size: 884b
 * EN Address: 0x8011ca70
 * EN Size: 884b
 * JP Address: 0x80119688
 * JP Size: 884b
 */
void CGPartyObj::statPut()
{
	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
	    IsKindOf(0x6D) &&
	    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId != 0) {
		static float d;
		static float h;
		CGObject* chalice = reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0);
		if (m_stateFrame == 0) {
			CancelMove(1);
			d = 3.0f;
			h = chalice->m_worldPosition.y - m_worldPosition.y;
		}

		if (m_stateFrame <= kPartyObjCarryArcFrames) {
			const float phase = sinf((3.1415927f * static_cast<float>(m_stateFrame)) / kPartyObjCarryArcFrames);
			m_extraMoveVec.x = d * (phase * sinf(m_rotBaseY));
			m_extraMoveVec.z = d * (phase * cosf(m_rotBaseY));
			m_extraMoveVec.y = h * phase + 10.0f;
		}
	}

	if (m_stateFrame == 0) {
		int seNo;
		int anim;
		int direct = 0;
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
			anim = (m_motionMode == 1) ? 0x28 : 9;
			direct = 0;
			seNo = 0x24;
			break;
		}
		reqAnim(anim, 0, direct);
		playSe3D(seNo, 0x32, 0x96, 0, 0);
	}

	if (isLoopAnim() != 0) {
		PartyObjOverlay& party = m_partyData;
		setIdleMotion();
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

	unsigned short trig = Pad.GetButtonDown(m_animStateMisc);
	if ((trig & 0x200) != 0) {
		changeStat(0, 0, 0);
		return;
	}

	if (isLoopAnim() != 0 || m_subFrame > 0x1E) {
		carry(0, reinterpret_cast<CGObject*>(m_partyData.carryTarget), 1);
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
	if (source != nullptr && !source->IsKindOf(0x2D)) {
		return;
	}

	int currentAdd;
	int currentSub;
	unsigned int stageAdd;
	unsigned int stageSub;
	int addValue;
	int subValue;
	int bonusSlot;
	bonusSlot = reinterpret_cast<unsigned char*>(m_scriptHandle)[0xBA4];
	subValue = 0;
	addValue = 0;
	currentAdd = SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[3];
	currentSub = SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[4];
	stageAdd = Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex].m_entries[bonusSlot + 8].m_values[3];
	stageSub = Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex].m_entries[bonusSlot + 9].m_values[0];

	if (kind == 0) {
		int count = SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[2];
		System.Printf("bonus: \x8E\xA9\x8E\x80\x96S(\x8A\xEE\x96{\x92l)=%d\n", count + 1);
		SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[2] = count + 1;
	}
	if (kind == 1) {
		int count = SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[0];
		System.Printf("bonus: \x93G\x8E\x80\x96S(\x8A\xEE\x96{\x92l)=%d\n", count + 1);
		SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[0] = count + 1;
	}
	if (kind == 4) {
		int count = SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[1];
		System.Printf("bonus: \x83" "A\x83" "C\x83" "e\x83\x80\x8E\xE6\x93\xBE(\x8A\xEE\x96{\x92l)=%d\n", count + 1);
		SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[1] = count + 1;
	}

	switch (bonusSlot) {
	default:
		break;
	case 0:
		if (kind == 2 && (static_cast<int>(System.GetCounter()) % 30) == 0) {
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
			SCfdItemRow* rows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
			int item = rows[value].m_field8;
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
		System.Printf("AVOID_TOUSEKI \x96\xA2\x91\xCE\x89\x9E\n");
		break;
	case 0x16:
		if (kind == 0x14) {
			addValue = stageAdd;
		}
		break;
	case 0x17:
		if (kind == 1 &&
		    (source->m_scriptHandle->m_romWork[0x7F] & 4) != 0) {
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
		currentAdd += addValue;
		int total = currentAdd < 0 ? 0 : (currentAdd > 100 ? 100 : currentAdd);
		if (bonusSlot != 0) {
			System.Printf("bonus: \x8F\xF0\x8C\x8F=%d \x93\xC1\x8E\xEAup=%d\n", bonusSlot, total);
		}
		SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[3] = static_cast<unsigned short>(total);
	}

	if (subValue != 0) {
		currentSub -= subValue;
		int total = currentSub < 0 ? 0 : (currentSub > 100 ? 100 : currentSub);
		System.Printf("bonus: \x8F\xF0\x8C\x8F=%d \x93\xC1\x8E\xEA" "down=%d\n", bonusSlot, total);
		SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_artifactRelated[4] = static_cast<unsigned short>(total);
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

	if (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(weaponFlags[0]) << 24) & 0xC0000000) >> 31) != 0) {
		if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(weaponFlags[1]) << 24) & 0xC0000000) >> 31) != 0) &&
		    (m_unk63CBits.m_bit80 != 0)) {
			if (m_scriptHandle->m_hp != 0) {
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
int CGPartyObj::canPlayerGoMenu()
{
	if ((m_weaponNodeFlagBits.m_prg != 0) &&
	    ((m_weaponNodeFlagAll.m_bits1.m_shield != 0) ||
	     ((m_partyData.commandMode & 2) != 0) ||
	     ((m_partyData.commandMode & 4) != 0)) &&
	    (m_unk63CBits.m_bit80 != 0) &&
	    (m_scriptHandle->m_hp != 0)) {
		return 1;
	}
	return 0;
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
	int result;

	if (!canPlayerUseItem()) {
		result = 0;
	} else {
		int itemKind = *reinterpret_cast<unsigned short*>(Game.unkCFlatData0[2] + itemId * 0x48);
		if (((itemId == 0x17D) || (itemId == 0x186)) &&
		    (m_scriptHandle->m_hp == 0)) {
			result = 0;
		} else {
			System.Printf("\x83" "A\x83" "C\x83" "e\x83\x80\x8Eg\x97p item=%d categoly=%d\n", itemId, itemKind);
			bonus(5, itemId, 0);

			switch (itemKind) {
			case 0x17D: {
				int heal;
				int foodIndex = itemId - 0x17D;
				if ((foodIndex >= 0) && (foodIndex < 8)) {
					unsigned char* script = reinterpret_cast<unsigned char*>(m_scriptHandle);
					SScriptFoodView* foods = reinterpret_cast<SScriptFoodView*>(script);
					int value = foods->m_foods[foodIndex] / 10;
					heal = 1;
					if (value >= 1) {
						heal = value;
					}
					SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_tempStatBuffTimer = *reinterpret_cast<unsigned short*>(Game.unk_flat3_field_8_0xc7dc + 0x68);
					SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_tempStatBuffId = itemId;
				} else {
					heal = 4;
				}
				addHp(heal, 0);
				System.Printf("\x90H\x82\xD7\x82\xE0\x82\xCC\x89\xF1\x95\x9C\x92l = %d\n", heal);
				break;
			}
			case 0x186: {
				int heal;
				if ((itemId == 0x188) &&
				    (SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_tribeId == 2)) {
					heal = 4;
				} else {
					heal = 2;
				}
				addHp(heal, 0);
				System.Printf("\x88\xF9\x82\xDD\x95\xA8\x89\xF1\x95\x9C\x92l = %d\n", heal);
				break;
			}
			}

			CFlatRuntime::CStack stack[2];
			unsigned char pausedFlag = 0;
			if ((Game.m_gameWork.m_menuStageMode != 0) && (Game.m_gameWork.m_gamePaused != 0)) {
				pausedFlag = 1;
			}
			stack[0].m_word = itemId;
			stack[1].m_word = pausedFlag;
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
	unsigned char* weaponFlags = reinterpret_cast<unsigned char*>(&m_weaponNodeFlags);

	if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(weaponFlags[0]) << 24) & 0xC0000000) >> 31) != 0) &&
	    (static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(weaponFlags[1]) << 24) & 0xC0000000) >> 31) != 0) &&
	    (m_unk63CBits.m_bit80 != 0) &&
	    (m_scriptHandle->m_hp != 0) &&
	    (m_partyData.carryObject == nullptr)) {
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
	    (created = CGItemObj::CreateFromScript(0, 9, itemId, this, 0.0f, (CGItemObj::CCFS*)0)) != nullptr) {
		*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(created) + 0x562) =
		    static_cast<short>(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId);
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
	    (created = CGItemObj::CreateFromScript(2, 1, amount, this, 0.0f, (CGItemObj::CCFS*)0)) != nullptr) {
		*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(created) + 0x560) = 1;
		*reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(created) + 0x562) =
		    static_cast<short>(reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId);
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
	PartyObjOverlay& party = m_partyData;
	changeWeapon(party.weaponIndex, party.weaponItemId, 0);

	if (m_subFrame > 1) {
		changeStat(0, 0, 0);
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
		    party->IsKindOf(0x6D) &&
		    (reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->m_joybusCaravanId != 0)) {
			continue;
		}

		if ((party->m_scriptHandle->m_hp == 0) &&
		    (party->m_partyData.flags.flag04 == 0)) {
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
	int chosenBonus[4];
	int bonusCount;
	CGame::CBossArtifactStage* bossArtifacts;
	int chosenCount;

	bonusCount = Game.GetNumBonus();

	System.Printf("\x83{\x81[\x83i\x83X\x83" "C\x83\x93\x83" "f\x83" "b\x83N\x83X\x8D\xC5\x91\xE5=%d\n", bonusCount);

	chosenCount = 0;
	bossArtifacts = &Game.m_bossArtifactBase[Game.m_gameWork.m_bossArtifactStageIndex];

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

			chosenBonus[chosenCount++] = bonusIndex;

			reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)
			    ->SetBonusCondition(bossArtifacts->m_bonusConditions[bonusIndex]);
			if (System.GetErrorLevel() >= 3U) {
				System.Printf("party%d \x83{\x81[\x83i\x83Xidx=%d \x92\x86\x90g=%d\n", slot, bonusIndex,
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
			if (System.GetErrorLevel() >= 3U) {
				System.Printf("party%d \x8C\xC5\x92\xE8\x83{\x81[\x83i\x83X=%d\n", slot, bonus);
			}
		}

		reinterpret_cast<CCaravanWork*>(party->m_scriptHandle)->CalcStatus();
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011C6E8
 * PAL Size: 248b
 * EN Address: 0x8011BA48
 * EN Size: 248b
 * JP Address: 0x80118668
 * JP Size: 240b
 */
void CGPartyObj::InitFinished()
{
	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->GetCurrentWeaponItem(
	    m_partyData.weaponIndex,
	    m_partyData.weaponItemId);
	enableDamageCol(1);
#ifndef VERSION_GCCJGC
	reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_tempStatBuffTimer = 0;
#endif
	if (Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_menuStageMode != 0 &&
	    Game.m_gameWork.m_bossArtifactStageIndex < 0x0F &&
	    IsKindOf(0x6D) &&
	    reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId != 0) {
		m_pushParamA = 0;
		m_bodyEllipsoidRadius = 3.0f;
		m_capsuleHalfHeight = 3.0f;
		m_extraMoveVec.y = 10.0f;
		m_turnFactor = 0.15f;
		CGPartyObj::m_ghostWork.flagBits.flag80 = m_partyData.carryObject == 0;
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
	PartyObjOverlay& party = m_partyData;
	if (party.commandMode != mode) {
		party.commandMode = static_cast<short>(mode);

		if (MenuPcs.GetRingMenu(SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_joybusCaravanId) != 0) {
			MenuPcs.GetRingMenu(SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_joybusCaravanId)->SetBattleCommand(0, -1, -1);
			MenuPcs.GetRingMenu(SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_joybusCaravanId)->SetBattleCommand(1, -1, -1);
			MenuPcs.GetRingMenu(SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_joybusCaravanId)->SetBattleCommand(2, -1, -1);
		} else {
			if (System.GetErrorLevel() >= 2U) {
				System.Printf("\x83\x8A\x83\x93\x83O\x83\x81\x83j\x83\x85\x81[\x82\xAA\x82\xB7\x82\xC5\x82\xC9\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1\x81" "B\n");
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
	if (m_scriptHandle->m_hp != 0 &&
	    (m_motionMode == 1)) {
		if (m_weaponModelHandle == nullptr) {
			changeWeapon(m_partyData.weaponIndex, m_partyData.weaponItemId, 1);
		}

		CCaravanWork* work = SAFE_CAST_CARAVAN_WORK(m_scriptHandle);
		int shieldIndex = work->m_equipment[2];
		int shieldItem;
		if (shieldIndex >= 0) {
			shieldItem = work->m_inventoryItems[shieldIndex];
		} else {
			shieldItem = 0;
		}
		if (shieldItem > 0) {
			SCfdItemRow* rows = reinterpret_cast<SCfdItemRow*>(Game.unkCFlatData0[2]);
			int shieldModel = rows[shieldItem].m_model & 0xFFF;
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
	PartyObjOverlay& party = m_partyData;

	if (m_motionMode == mode) {
		return;
	}

	m_motionMode = static_cast<short>(mode);
	changeStat(0, 0, 0);

	setIdleMotion();

	CancelAnim(1);

	setAlive(1, 1);

	if (mode == 1 && party.carryObject == 0 &&
	    m_scriptHandle->m_hp != 0) {
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
	if (m_partyData.carryObject != 0) {
		if (CFlatItemCarryMode() == 0) {
			if (m_motionMode == 1) {
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
		if (m_scriptHandle->m_hp != 0) {
			if (m_motionMode == 1) {
				SetAnimSlot(0, 0);
				SetAnimSlot(1, 1);
			} else {
				SetAnimSlot(0x25, 0);
				SetAnimSlot(0x30, 1);
			}
		} else if (m_motionMode == 1) {
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
	PartyObjOverlay& party = m_partyData;

	if (party.flags.flag04) {
		if (m_scriptHandle->m_hp == 0) {
			addHp(m_scriptHandle->m_maxHp, static_cast<CGPrgObj*>(0));
		}
		party.flags.flag04 = 0;
	}

	enableDamageCol(1);

	setIdleMotion();

	if (restoreDamageCol == 0) {
		if (m_currentAnimSlot == 6) {
			reqAnim(0x26, 0, 0);
		} else {
			reqAnim(0x27, 0, 0);
		}
	}

	if (m_scriptHandle->m_hp != 0) {
		endPSlotBit(0x10000);
		m_alpha = 1.0f;
		m_bgColMask |= 0x1000E;
		if (restoreDamageCol == 0) {
			m_scriptHandle->m_statusTimers[5] = 0x5A;
		}
	} else {
		m_alpha = 0.3f;
		m_bgColMask &= 0xFFFEFFF1;
		int port = SAFE_CAST_CARAVAN_WORK(m_scriptHandle)->m_joybusCaravanId;

		if (restoreDamageCol == 0 || keepTarget != 0) {
			endPSlotBit(0x10000);
			putParticle((port + 3) | 0x100,
			            m_particleSlots[16], this, 1.0f, 0);
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
	CGItemObj::CreateFromScript(0, 2, 399, this, 0.0f, &ccfs);
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
 * EN Address: 0x80142834
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline int stageWeather()
{
	switch (Game.m_gameWork.m_bossArtifactStageIndex) {
	default:
	case 0:
	case 1:
	case 2:
	case 3:
		return 0;
	case 6:
	case 10:
		return 1;
	case 4:
	case 8:
	case 9:
	case 0x0B:
	case 0x0C:
	case 0x0D:
		return 2;
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
static inline int magicReady()
{
	if (CGPartyObj::m_ghostWork.counters[0] >= Chara.MogFur().m_radarLevel[0] ||
	    CGPartyObj::m_ghostWork.counters[1] >= Chara.MogFur().m_radarLevel[1] ||
	    CGPartyObj::m_ghostWork.counters[2] >= Chara.MogFur().m_radarLevel[2]) {
		return 1;
	}
	return 0;
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
static inline int chooseMagic()
{
	int choices = 0;
	int i;
	for (i = 0; i < 3; i++) {
		if (CGPartyObj::m_ghostWork.counters[i] >= Chara.MogFur().m_radarLevel[i]) {
			choices++;
		}
	}

	int pick = Math.Rand(choices);
	int cursor = 0;
	for (i = 0; i < 3; i++) {
		if (CGPartyObj::m_ghostWork.counters[i] >= Chara.MogFur().m_radarLevel[i]) {
			if (cursor == pick) {
				return i;
			}
			cursor++;
		}
	}
	return 0;
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
static inline void decMagic(int slotSel)
{
	for (int slot = 0; slot < 3; slot++) {
		if (slot == slotSel) {
			CGPartyObj::m_ghostWork.counters[slot] = 0;
		} else {
			CGPartyObj::m_ghostWork.counters[slot] = CGPartyObj::m_ghostWork.counters[slot] / 2;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 200b
 * EN Address: 0x80142A5C
 * EN Size: 220b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline int calcWeightMax()
{
	int weather = stageWeather();
	float rate = static_cast<float>(Chara.MogFur().m_alphaScore) / 100.0f;
	float scale;
	switch (weather) {
	default:
		scale = 1.0f;
		break;
	case 1:
		scale = 0.5f * (1.0f - rate) + 0.5f;
		break;
	case 2:
		scale = 0.5f * rate + 0.5f;
		break;
	}
	int weightMax = 1800.0f * scale;
	return weightMax;
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
	GhostPartyWork& ghostWork = m_ghostWork;
	int& activeTrailCount = ghostWork.activeTrailCount;

	if (activeTrailCount == 0) {
	reset:
		activeTrailCount = 0;
		outVec->x = m_partyDelta[0].x;
		outVec->y = m_partyDelta[0].y;
		outVec->z = m_partyDelta[0].z;
		outVec->y = 0.0f;

		outDist = PSVECMag(outVec);
		outDist = (outDist < m_partyDistance[0]) ? outDist : m_partyDistance[0];
		return;
	}

	CVector unused;
	int capturedCurrent = 0;
	GhostPartyWork& loopWork = m_ghostWork;
	int& loopTrailIndex = loopWork.trailIndex;

	outDist = 0.0f;
	float flatLen = 0.0f;
	for (int i = 0; i < activeTrailCount; i++) {
		if (loopTrailIndex <= i) {
			Vec* nextPos;
			if (i == loopTrailIndex) {
				nextPos = &m_worldPosition;
			} else {
				nextPos = &m_ghostWork.trailPositions[i - 1];
			}
			Vec delta;
			PSVECSubtract(&loopWork.trailPositions[i], nextPos, &delta);
			outDist += PSVECMag(&delta);

			delta.y = 0.0f;
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
	}

	outDist = (outDist < flatLen) ? outDist : flatLen;
	if (outDist > 300.0) {
		goto reset;
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
	CGPartyObj* leader = Game.m_partyObjArr[0];
	GhostPartyWork& ghostWork = m_ghostWork;
	int& activeTrailCount = ghostWork.activeTrailCount;
	Vec* trailBase = ghostWork.trailPositions;
	int i = 0;
	do {
		Vec* pos = (i == 0) ? &m_worldPosition
		                    : &trailBase[i - 1];

		CVector diffVec = CVector(leader->m_worldPosition) - CVector(*pos);

		if (MapPcs.CheckHitCylinderNear(CVector(pos->x, 10.0f + pos->y, pos->z), diffVec, m_capsuleHalfHeight,
		                                leader->m_bgHitMask & ~0x10U) != 0) {
			activeTrailCount = activeTrailCount < i + 1 ? activeTrailCount : i + 1;
		} else {
			trailBase[i] = leader->m_worldPosition;
			activeTrailCount = i + 1;
			m_ghostWork.trailIndex = m_ghostWork.trailIndex < i ? m_ghostWork.trailIndex : i;
			break;
		}
		i++;
	} while (static_cast<unsigned int>(i) < 5);
	int lastTrailIndex = activeTrailCount;
	lastTrailIndex--;
	m_ghostWork.trailIndex = m_ghostWork.trailIndex < (lastTrailIndex < 0 ? 0 : lastTrailIndex)
	    ? m_ghostWork.trailIndex : (lastTrailIndex < 0 ? 0 : lastTrailIndex);
}

/*
 * --INFO--
 * PAL Address: 0x8011b268
 * PAL Size: 1320b
 * EN Address: 0x80142FDC
 * EN Size: 1196b
 * JP Address: TODO
 * JP Size: TODO
 */
void CGPartyObj::ghostPartyMog()
{
	unsigned int distFar;
	CGPartyObj* leader = Game.m_partyObjArr[0];

	gpmCol();
	gpmMove();

	distFar = calcWeightMax();

	if (static_cast<double>(m_partyDistance[0]) > 90.0) {
		CGPartyObj::m_ghostWork.state = 1;
	} else {
		int exceeded;
		if (static_cast<int>(CGPartyObj::m_ghostWork.counters[0]) >= Chara.MogFur().m_radarLevel[0] ||
		    static_cast<int>(CGPartyObj::m_ghostWork.counters[1]) >= Chara.MogFur().m_radarLevel[1] ||
		    static_cast<int>(CGPartyObj::m_ghostWork.counters[2]) >= Chara.MogFur().m_radarLevel[2]) {
			exceeded = 1;
		} else {
			exceeded = 0;
		}

		if (exceeded && CGPartyObj::m_ghostWork.flagBits.flag10 == 0) {
			CGPartyObj::m_ghostWork.flagBits.flag10 = 1;
			CGPartyObj::m_ghostWork.state = 2;
			putParticle(299, 0, this, 1.0f, 0);
		} else if (CGPartyObj::m_ghostWork.flagBits.flag08 == 0 &&
		           static_cast<int>(CGPartyObj::m_ghostWork.pressure) >= 10) {
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
			switch (moodMode) {
			case 0:
				break;
			case 1:
				if (Chara.MogFur().m_alphaScore < 0x32) {
					CGPartyObj::m_ghostWork.state = 5;
				} else if (Chara.MogFur().m_alphaScore >= 0x5F) {
					CGPartyObj::m_ghostWork.state = 4;
				}
				break;
			case 2:
				if (Chara.MogFur().m_alphaScore < 0x32) {
					CGPartyObj::m_ghostWork.state = 6;
				}
				break;
			}
			CGPartyObj::m_ghostWork.flagBits.flag08 = 1;
		} else {
			if (CGPartyObj::m_ghostWork.flagBits.flag04 == 0) {
				if (static_cast<int>(CGPartyObj::m_ghostWork.pressure) >= calcWeightMax()) {
					CGPartyObj::m_ghostWork.state = 3;
					CGPartyObj::m_ghostWork.flagBits.flag04 = 1;
					goto messageMenu;
				}
			}
			if (CGPartyObj::m_ghostWork.flagBits.flag04 == 0 && static_cast<int>(CGPartyObj::m_ghostWork.settleTimer) > 0x96) {
				CGPartyObj::m_ghostWork.state = 8;
			} else {
				CGPartyObj::m_ghostWork.state = 0;
				CGPartyObj::m_ghostWork.field20 = 0;
			}
		}
	}

messageMenu:
	if ((leader->m_weaponNodeFlagAll.m_bits1.m_shield != 0) &&
	    CGPartyObj::m_ghostWork.state != 0 &&
	    CGPartyObj::m_ghostWork.state != CGPartyObj::m_ghostWork.field20) {
		if (!MenuPcs.m_battleMesMenus[5]->IsUse()) {
			CGPartyObj::m_ghostWork.field20 = CGPartyObj::m_ghostWork.state;
			MenuPcs.m_battleMesMenus[5]->Open(Game.m_cFlatDataArr[1].GetMes(CGPartyObj::m_ghostWork.state - 1), 0x260, 0x20, 0x8E20, 0, 0x65, 0x8B);
		}
	}

	int auraSlot = 0;
	int gauge = CGPartyObj::m_ghostWork.pressure;
	if (gauge > static_cast<int>(distFar * 3) / 3) {
		auraSlot = 0xF;
	} else if (gauge > static_cast<int>(distFar << 1) / 3) {
		auraSlot = 0xE;
	} else if (gauge > static_cast<int>(distFar) / 3) {
		auraSlot = 0xD;
	}

	int prevSlot = CGPartyObj::m_ghostWork.auraSlot;
	if (prevSlot != auraSlot) {
		endPSlotBit(0x400);
		if (auraSlot != 0) {
			putParticle(auraSlot | 0x200, m_particleSlots[10], this, 1.0f, 0);
		}
		CGPartyObj::m_ghostWork.auraSlot = auraSlot;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8011a94c
 * PAL Size: 2332b
 * EN Address: 0x80143488
 * EN Size: 2532b
 * JP Address: 0x801168fc
 * JP Size: 2332b
 */
void CGPartyObj::gpmMove()
{
	int pressureLimit;
	CGPartyObj* leader = Game.m_partyObjArr[0];
	CGObject* chalice = reinterpret_cast<CGObject*>(Game.unk_flat3_0xc7d0);

	if (leader->m_lastStateId == 0 &&
	    leader->m_animSlotSel == 0x0C &&
	    leader->m_partyData.carryObject == chalice) {
		CGPartyObj::m_ghostWork.settleTimer++;
	} else {
		CGPartyObj::m_ghostWork.settleTimer = 0;
	}

	if (0.1f < CGPartyObj::m_ghostWork.carrySpeed) {
		moveVector(&CGPartyObj::m_ghostWork.carryDir, CGPartyObj::m_ghostWork.carrySpeed, 1);
	}
	CGPartyObj::m_ghostWork.carrySpeed *= 0.95f;

	pressureLimit = calcWeightMax();
	if (0.5f < CGPartyObj::m_ghostWork.carrySpeed) {
		int delta = -2;
		if (m_partyData.carryObject != nullptr) {
			delta = 2;
		}
		CGPartyObj::m_ghostWork.pressure += delta;
	} else if (m_partyData.carryObject != nullptr) {
		CGPartyObj::m_ghostWork.pressure -= 3;
	} else {
		CGPartyObj::m_ghostWork.pressure -= 4;
	}

	int clampedPressure = CGPartyObj::m_ghostWork.pressure;
	if (clampedPressure < 0) {
		clampedPressure = 0;
	} else if (pressureLimit + 100 < clampedPressure) {
		clampedPressure = pressureLimit + 100;
	}
	CGPartyObj::m_ghostWork.pressure = clampedPressure;

	if (CGPartyObj::m_ghostWork.pressure < pressureLimit / 3) {
		CGPartyObj::m_ghostWork.flagBits.flag04 = 0;
	}
	int moodTimer = CGPartyObj::m_ghostWork.moodTimer - 1;
	CGPartyObj::m_ghostWork.moodTimer = moodTimer < 0 ? 0 : moodTimer;

	Vec pathVec;
	float pathDist;
	gpmCalcDist(&pathVec, pathDist);

	Vec toChalice;
	toChalice = m_targetDelta;
	toChalice.y = 0.0f;
	float followDist = PSVECMag(&toChalice);
	float chaliceDist = m_targetDist;
	followDist = followDist < chaliceDist ? followDist : chaliceDist;

	if (m_lastStateId == 0 &&
	    (m_unk63CBits.m_bit80 != 0)) {
		int moveKind = 0;
		if (CGPartyObj::m_ghostWork.flagBits.flag80 != 0) {
			moveKind = 0;
			if (m_partyData.carryObject != nullptr) {
				CGPartyObj::m_ghostWork.carrySpeed = 0.0f;
				carry(1, static_cast<CGObject*>(0), 0);
				return;
			}

			float limit = (CGPartyObj::m_ghostWork.moodTimer != 0) ? 0.3f : 0.7f;
			if (pathDist < Game.unkFloat_0xca10 * limit) {
				if ((leader->m_lastStateId == 2 || leader->m_lastStateId == 6) &&
				    leader->m_subState == 1 &&
				    leader->m_comboState != 0 &&
				    leader->m_comboFrame == 0) {
					if (magicReady() == 0) {
						return;
					}

					CGPartyObj::m_ghostWork.slotSel = chooseMagic();

					switch (CGPartyObj::m_ghostWork.slotSel) {
					case 0:
						m_itemId = 0x207;
						break;
					case 1:
						m_itemId = 0x20F;
						break;
					case 2:
						m_itemId = 0x20B;
						break;
					}
					changeStat(2, 0, 0);
					CGPartyObj::m_ghostWork.gauge = 0;
					CGPartyObj::m_ghostWork.flagBits.flag40 = 0;
					CGPartyObj::m_ghostWork.flagBits.flag20 = 0;
				}
				return;
			}
		} else {
			if (m_partyData.carryObject == nullptr &&
			    (chalice->m_weaponNodeFlagBits.m_prg != 0) &&
			    !reinterpret_cast<CGItemObj*>(chalice)->isCarry()) {
				float pickupRadius = (leader->m_bodyEllipsoidRadius + chalice->m_bodyEllipsoidRadius) * 1.5f;
				if (chaliceDist < pickupRadius) {
					CancelMove(1);
					rotTarget(reinterpret_cast<CGPrgObj*>(chalice));
					CGPartyObj::m_ghostWork.carrySpeed = 0.0f;
					carry(0, chalice, 0);
					return;
				}
				moveKind = 1;
			}

			if (moveKind == 0) {
				float limit = (CGPartyObj::m_ghostWork.moodTimer != 0) ? 0.3f : 0.5f;
				if (pathDist < Game.unkFloat_0xca10 * limit) {
					return;
				}
			}
			if (moveKind == 1) {
				float keepDist = (leader->m_bodyEllipsoidRadius + chalice->m_bodyEllipsoidRadius) / 2.0f;
				if (followDist < keepDist) {
					return;
				}
			}
		}

		if (CGPartyObj::m_ghostWork.field04 != moveKind) {
			CGPartyObj::m_ghostWork.field04 = moveKind;
			CGPartyObj::m_ghostWork.field08 = 0;
		}

		CVector moveDir;
		if (moveKind == 0) {
			moveDir = CVector(pathVec);
		} else {
			moveDir = CVector(toChalice);
		}

		CGPartyObj::m_ghostWork.carryDir = *reinterpret_cast<Vec*>(&moveDir);
		CGPartyObj::m_ghostWork.carrySpeed += 0.1f;
#ifdef VERSION_GCCP01
		float speedScale = (CGPartyObj::m_ghostWork.pressure >= pressureLimit) ? 1.0f : 4.0f;
#else
		float speedScale = (CGPartyObj::m_ghostWork.pressure >= pressureLimit) ? 1.0f : 3.5f;
#endif
		float newSpeed = CGPartyObj::m_ghostWork.carrySpeed;
		if (newSpeed < 0.0f) {
			newSpeed = 0.0f;
		} else {
			float speedLimit = speedScale * (m_moveBaseSpeed * Game.m_partyObjArr[0]->m_pushScale);
			newSpeed = speedLimit < newSpeed ? speedLimit : newSpeed;
		}
		CGPartyObj::m_ghostWork.carrySpeed = newSpeed;

		CGPartyObj::m_ghostWork.field08++;
#ifdef VERSION_GCCP01
		if (CGPartyObj::m_ghostWork.field08 == 4) {
#else
		if (CGPartyObj::m_ghostWork.field08 == 5) {
#endif
			CGPartyObj::m_ghostWork.field08 = 0;
		}
		return;
	}

	if (m_lastStateId != 2) {
		return;
	}
	if (CGPartyObj::m_ghostWork.flagBits.flag80 == 0) {
		changeStat(0, 0, 0);
		return;
	}

	if (leader->m_lastStateId != 2 && leader->m_lastStateId != 6) {
		if (CGPartyObj::m_ghostWork.flagBits.flag20 == 0) {
			changeStat(0, 0, 0);
			return;
		}
	} else {
		if (m_subState != 1) {
			return;
		}
		if (m_comboState == 0) {
			return;
		}
		if (leader->m_partyData.flags.flag20 != 0) {
			CGPartyObj::m_ghostWork.gauge = 0;
		}
		if (m_partyData.flags.flag40 == 0) {
			return;
		}

		CGPartyObj::m_ghostWork.flagBits.flag20 = 1;
		CGPartyObj::m_ghostWork.gauge++;
		if (CGPartyObj::m_ghostWork.gauge <= 0xF) {
			return;
		}
		if (CGPartyObj::m_ghostWork.flagBits.flag40 != 0) {
			return;
		}
	}

	CGPartyObj::m_ghostWork.flagBits.flag40 = 1;
	decMagic(CGPartyObj::m_ghostWork.slotSel);
	CGPartyObj::m_ghostWork.flagBits.flag10 = 0;
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

	if ((static_cast<signed char>(static_cast<int>((static_cast<unsigned int>(reinterpret_cast<unsigned char*>(this)[0x9A]) << 24) & 0xC0000000) >> 31) != 0) &&
	    (static_cast<int>(CFlatCenterState()) == 0) &&
	    ((DbgMenuPcs.GetDbgFlag() & 0x80) != 0)) {
		char text[256];
		if ((Game.m_gameWork.m_menuStageMode != 0) &&
		    (Game.m_gameWork.m_bossArtifactStageIndex < 0x0F) &&
		    IsKindOf(0x6D) && (reinterpret_cast<CCaravanWork*>(m_scriptHandle)->m_joybusCaravanId != 0)) {
			int weightMax = calcWeightMax();

			sprintf(text, "%d/%d %d/%d %d/%d", CGPartyObj::m_ghostWork.counters[0], Chara.MogFur().m_radarLevel[0],
			        CGPartyObj::m_ghostWork.counters[1], Chara.MogFur().m_radarLevel[1],
			        CGPartyObj::m_ghostWork.counters[2], Chara.MogFur().m_radarLevel[2]);

			float curY = y;
			float width = static_cast<float>(font->GetWidth(text));
			font->SetPosX(x - width * 0.5f);
			font->SetPosY(curY);
			font->SetPosZ(z);
			font->Draw(text);
			float lineH = static_cast<float>(font->m_glyphHeight) * font->scaleY;
			y = y - lineH;

			sprintf(text, "%d/%d a=%d", CGPartyObj::m_ghostWork.pressure,
			        weightMax, Chara.MogFur().m_alphaScore);

			float curY2 = y;
			width = static_cast<float>(font->GetWidth(text));
			font->SetPosX(x - width * 0.5f);
			font->SetPosY(curY2);
			font->SetPosZ(z);
			font->Draw(text);
		} else {
			unsigned char* work = reinterpret_cast<unsigned char*>(m_scriptHandle);
			sprintf(text, "%d %d %d %d %d %d", work[0xBA4], *reinterpret_cast<unsigned short*>(work + 0xBC4),
			        *reinterpret_cast<unsigned short*>(work + 0xBC6), *reinterpret_cast<unsigned short*>(work + 0xBC8),
			        *reinterpret_cast<unsigned short*>(work + 0xBCA), *reinterpret_cast<unsigned short*>(work + 0xBCC));

			float curY3 = y;
			float width = static_cast<float>(font->GetWidth(text));
			font->SetPosX(x - width * 0.5f);
			font->SetPosY(curY3);
			font->SetPosZ(z);
			font->Draw(text);
		}
		{
			float lineH = static_cast<float>(font->m_glyphHeight) * font->scaleY;
			y = y - lineH;
		}
	}
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
