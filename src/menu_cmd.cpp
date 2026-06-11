#include "ffcc/menu_cmd.h"
#include "ffcc/fontman.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/joybus.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "dolphin/types.h"
#include <math.h>
#include <string.h>

static const char sEmptySkillName[] = "";
static const double kCmdMenuOneD = 1.0;
static const double kCmdMenuHalfD = 0.5;
static const double kCmdMenuAlphaStepD = 0.1;
static const float kCmdMenuOne = 1.0f;
static const double kCmdMenuTransitionFramesD = 5.0;
static const double kCmdMenuS32DoubleBias = 4503601774854144.0;
static const float kCmdMenuHalf = 0.5f;
static const double kCmdMenuTransitionStepD = 0.2;
static const double kCmdMenuPanelRightInsetD = 24.0;
static const double kCmdMenuUnitePanelScaleD = 1.5;
static const double kCmdMenuUnitePanelYOffsetD = 3.0;
static const float kCmdMenuZero = 0.0f;
static const double kCmdMenuUniteSlideStepD = 12.8;
static const double kCmdMenuUniteSlideLimitD = 64.0;
static const float kCmdMenuPanelSize64 = 64.0f;
static const float kCmdMenuAlphaMax = 255.0f;
static const float kCmdMenuSmallOffset = 8.0f;
static const float kCmdMenuUniteBarHeight = 40.0f;
static const float kCmdMenuTextScale = 0.9f;
static const double kCmdMenuUniteAlphaScaleD = 0.015625;
static const float kCmdMenuTextYOffset = 4.0f;
static const float kCmdMenuUnitePanelWidth = 208.0f;
static const float kCmdMenuPanelInset = 2.0f;
static const double kCmdMenuTextLineHeightD = 19.8;
static const double kCmdMenuTextBaselineOffsetD = 2.0;
static const float kCmdMenuScreenHalfWidth = 320.0f;
static const float kCmdMenuThree = 3.0f;
static const float kCmdMenuSelectedUvY = 72.0f;
static const float kCmdMenuTwelve = 12.0f;
static const float kCmdMenuTwentyFour = 24.0f;
static const double kCmdMenuChoicePaddingD = 16.0;
static const float kCmdMenuHelpXOffset = 352.0f;
static const double kCmdMenuZeroD = 0.0;
static const float kCmdMenuBasePanelU = 128.0f;
static const float kCmdMenuThreeQuarter = 0.75f;
static s32 s_unitePanelCount;
static s32 s_UniteTop[3];

extern "C" const s16 s_uniteRecipePatterns[] = {
    0x0000, 0x022A, 0x0003, 0x0107, 0x0105, 0x0105,
    0x0001, 0x0207, 0x0002, 0x0100, 0x03E7, 0x0000,
    0x0001, 0x020B, 0x0002, 0x0101, 0x03E7, 0x0000,
    0x0001, 0x020F, 0x0002, 0x0102, 0x03E7, 0x0000,
    0x0000, 0x0230, 0x0003, 0x0100, 0x0100, 0x0100,
    0x0000, 0x0231, 0x0003, 0x0101, 0x0101, 0x0101,
    0x0000, 0x0232, 0x0003, 0x0102, 0x0102, 0x0102,
    0x0000, 0x0208, 0x0002, 0x0100, 0x0100, 0x0000,
    0x0000, 0x020C, 0x0002, 0x0101, 0x0101, 0x0000,
    0x0000, 0x0210, 0x0002, 0x0102, 0x0102, 0x0000,
    0x0000, 0x0226, 0x0002, 0x0100, 0x0101, 0x0000,
    0x0000, 0x0226, 0x0002, 0x0100, 0x0102, 0x0000,
    0x0000, 0x0226, 0x0002, 0x0101, 0x0100, 0x0000,
    0x0000, 0x0226, 0x0002, 0x0101, 0x0102, 0x0000,
    0x0000, 0x0226, 0x0002, 0x0102, 0x0100, 0x0000,
    0x0000, 0x0226, 0x0002, 0x0102, 0x0101, 0x0000,
    0x0000, 0x0221, 0x0002, 0x0100, 0x0107, 0x0000,
    0x0000, 0x0221, 0x0002, 0x0101, 0x0107, 0x0000,
    0x0000, 0x0221, 0x0002, 0x0102, 0x0107, 0x0000,
    0x0000, 0x0214, 0x0002, 0x0107, 0x0100, 0x0000,
    0x0000, 0x0214, 0x0002, 0x0107, 0x0101, 0x0000,
    0x0000, 0x0214, 0x0002, 0x0107, 0x0102, 0x0000,
    0x0000, 0x023E, 0x0003, 0x0107, 0x0100, 0x0101,
    0x0000, 0x023E, 0x0003, 0x0107, 0x0100, 0x0102,
    0x0000, 0x023E, 0x0003, 0x0107, 0x0101, 0x0100,
    0x0000, 0x023E, 0x0003, 0x0107, 0x0101, 0x0102,
    0x0000, 0x023E, 0x0003, 0x0107, 0x0102, 0x0100,
    0x0000, 0x023E, 0x0003, 0x0107, 0x0102, 0x0101,
    static_cast<s16>(0xFFFF), static_cast<s16>(0xFFFF), static_cast<s16>(0xFFFF),
    static_cast<s16>(0xFFFF), static_cast<s16>(0xFFFF), static_cast<s16>(0xFFFF),
};

static const char s_Flamestrike_801DEA6C[] = "Flamestrike";
static const char s_Icestrike_801DEA78[] = "Icestrike";
static const char s_Thunderstrike_801DEA84[] = "Thunderstrike";
static const char s_Feuer_Hieb_801DEA94[] = "Feuer-Hieb";
static const char s_Eis_Hieb_801DEAA0[] = "Eis-Hieb";
static const char s_Blitz_Hieb_801DEAAC[] = "Blitz-Hieb";
static const char s_Colpo_Fire_801DEAB8[] = "Colpo Fire";
static const char s_Colpo_Blizzard_801DEAC4[] = "Colpo Blizzard";
static const char s_Colpo_Thunder_801DEAD4[] = "Colpo Thunder";
static const char s_Pyro_Frappe_801DEAE4[] = "Pyro-Frappe";
static const char s_Cryo_Frappe_801DEAF0[] = "Cryo-Frappe";
static const char s_Rheo_Frappe_801DEAFC[] = "Rh\351o-Frappe";
static const char s_Efecto_Fuego_801DEB08[] = "Efecto Fuego";
static const char s_Efecto_Hielo_801DEB18[] = "Efecto Hielo";
static const char s_Efecto_Electro_801DEB28[] = "Efecto Electro";

extern "C" const char* s_SkillStr_us[];
extern "C" const char* s_SkillStr_ge[];
extern "C" const char* s_SkillStr_it[];
extern "C" const char* s_SkillStr_fr[];
extern "C" const char* s_SkillStr_sp[];

namespace {

static inline const char* GetStrikeListName(int itemId)
{
	if (itemId == 0x207) {
		switch (Game.m_gameWork.m_languageId) {
		case 2:
			return s_SkillStr_ge[0];
		case 3:
			return s_SkillStr_it[0];
		case 4:
			return s_SkillStr_fr[0];
		case 5:
			return s_SkillStr_sp[0];
		case 1:
		default:
			return s_SkillStr_us[0];
		}
	} else if (itemId == 0x20B) {
		switch (Game.m_gameWork.m_languageId) {
		case 2:
			return s_SkillStr_ge[1];
		case 3:
			return s_SkillStr_it[1];
		case 4:
			return s_SkillStr_fr[1];
		case 5:
			return s_SkillStr_sp[1];
		case 1:
		default:
			return s_SkillStr_us[1];
		}
	} else if (itemId == 0x20F) {
		switch (Game.m_gameWork.m_languageId) {
		case 2:
			return s_SkillStr_ge[2];
		case 3:
			return s_SkillStr_it[2];
		case 4:
			return s_SkillStr_fr[2];
		case 5:
			return s_SkillStr_sp[2];
		case 1:
		default:
			return s_SkillStr_us[2];
		}
	} else if (itemId == 0x222) {
		switch (Game.m_gameWork.m_languageId) {
		case 2:
			return s_SkillStr_ge[3];
		case 3:
			return s_SkillStr_it[3];
		case 4:
			return s_SkillStr_fr[3];
		case 5:
			return s_SkillStr_sp[3];
		case 1:
		default:
			return s_SkillStr_us[3];
		}
	} else if (itemId == 0x227) {
		switch (Game.m_gameWork.m_languageId) {
		case 2:
			return s_SkillStr_ge[4];
		case 3:
			return s_SkillStr_it[4];
		case 4:
			return s_SkillStr_fr[4];
		case 5:
			return s_SkillStr_sp[4];
		case 1:
		default:
			return s_SkillStr_us[4];
		}
	} else {
		char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
		return flatText[itemId * 5 + 4];
	}
}

struct CmdListEntry {
	s16 x;
	s16 y;
	s16 width;
	s16 height;
	float u;
	float v;
	float alpha;
	float scale;
	s32 unk_18;
	s32 tex;
	s32 timer;
	s32 startFrame;
	s32 duration;
	u32 flags;
	float dx;
	float dy;
	float targetX;
	float targetY;
};

struct CmdListStorage {
	s16 count;
	s16 listEnd;
	unsigned char pad_0004[4];
	CmdListEntry entries[64];
};

struct CmdState {
	unsigned char pad_0000[0x06];
	u8 submenuFlag;
	unsigned char pad_0007;
	s8 commandResult;
	unsigned char pad_0009[0x0B - 0x09];
	s8 initialized;
	u8 unitePanelInitialized;
	u8 uniteOpenFlag;
	unsigned char pad_000E[0x10 - 0x0E];
	s16 animState;
	s16 phase;
	s16 uniteState;
	unsigned char pad_0016[0x1E - 0x16];
	s16 action;
	unsigned char pad_0020[0x22 - 0x20];
	s16 transitionTimer;
	unsigned char pad_0024[0x26 - 0x24];
	s16 selected;
	s16 itemSelected;
	s16 choice;
	s16 uniteSelected;
	unsigned char pad_002E[0x30 - 0x2E];
	s16 mode;
	u16 prevMode;
	s16 scrollTop;
};

STATIC_ASSERT(offsetof(CmdListEntry, u) == 0x08);
STATIC_ASSERT(offsetof(CmdListEntry, v) == 0x0C);
STATIC_ASSERT(offsetof(CmdListEntry, alpha) == 0x10);
STATIC_ASSERT(offsetof(CmdListEntry, scale) == 0x14);
STATIC_ASSERT(offsetof(CmdListEntry, tex) == 0x1C);
STATIC_ASSERT(offsetof(CmdListEntry, timer) == 0x20);
STATIC_ASSERT(offsetof(CmdListEntry, startFrame) == 0x24);
STATIC_ASSERT(offsetof(CmdListEntry, duration) == 0x28);
STATIC_ASSERT(offsetof(CmdListEntry, flags) == 0x2C);
STATIC_ASSERT(offsetof(CmdListEntry, dx) == 0x30);
STATIC_ASSERT(offsetof(CmdListEntry, dy) == 0x34);
STATIC_ASSERT(offsetof(CmdListEntry, targetX) == 0x38);
STATIC_ASSERT(offsetof(CmdListEntry, targetY) == 0x3C);
STATIC_ASSERT(sizeof(CmdListEntry) == 0x40);
STATIC_ASSERT(offsetof(CmdListStorage, entries) == 8);
STATIC_ASSERT(sizeof(CmdListStorage) == 0x1008);
STATIC_ASSERT(offsetof(CmdState, submenuFlag) == 0x06);
STATIC_ASSERT(offsetof(CmdState, commandResult) == 0x08);
STATIC_ASSERT(offsetof(CmdState, initialized) == 0x0B);
STATIC_ASSERT(offsetof(CmdState, unitePanelInitialized) == 0x0C);
STATIC_ASSERT(offsetof(CmdState, animState) == 0x10);
STATIC_ASSERT(offsetof(CmdState, phase) == 0x12);
STATIC_ASSERT(offsetof(CmdState, uniteState) == 0x14);
STATIC_ASSERT(offsetof(CmdState, action) == 0x1E);
STATIC_ASSERT(offsetof(CmdState, transitionTimer) == 0x22);
STATIC_ASSERT(offsetof(CmdState, selected) == 0x26);
STATIC_ASSERT(offsetof(CmdState, itemSelected) == 0x28);
STATIC_ASSERT(offsetof(CmdState, choice) == 0x2A);
STATIC_ASSERT(offsetof(CmdState, uniteSelected) == 0x2C);
STATIC_ASSERT(offsetof(CmdState, mode) == 0x30);
STATIC_ASSERT(offsetof(CmdState, prevMode) == 0x32);
STATIC_ASSERT(offsetof(CmdState, scrollTop) == 0x34);

static inline s16* GetCmdState(CMenuPcs* menu)
{
	return menu->m_cmdState;
}

static inline s16* GetCmdList(CMenuPcs* menu)
{
	return menu->m_cmdList;
}

static inline CmdListStorage* GetCmdListStorage(CMenuPcs* menu)
{
	return reinterpret_cast<CmdListStorage*>(GetCmdList(menu));
}

static inline CmdListEntry* GetCmdListEntries(CMenuPcs* menu)
{
	return GetCmdListStorage(menu)->entries;
}

static inline CmdState* GetCmdStateView(CMenuPcs* menu)
{
	return reinterpret_cast<CmdState*>(GetCmdState(menu));
}

static inline CmdState* ModeRow(CmdState* cmd, int m)
{
	return reinterpret_cast<CmdState*>(reinterpret_cast<u8*>(cmd) + m * 2);
}

static inline s16* GetCmdStateSelections(CmdState* cmd)
{
	return &cmd->selected;
}


static inline s16 GetCmdLayoutFlag(CMenuPcs* menu)
{
	return menu->m_cmdLayoutFlag;
}

static inline s16 GetUniteRecipeCmd(int recipe)
{
	return s_uniteRecipePatterns[recipe * 6 + 1];
}

static inline s16 GetUniteRecipeCount(int recipe)
{
	return s_uniteRecipePatterns[recipe * 6 + 2];
}

} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool IsMagicArti(int itemId)
{
	return (0xdf <= itemId) && (itemId <= 0xe3);
}

/*
 * --INFO--
 * PAL Address: 0x8015023c
 * PAL Size: 396b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdInit()
{
	u8* self = reinterpret_cast<u8*>(this);
	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	memset(GetCmdListStorage(this), 0, sizeof(*GetCmdListStorage(this)));

	float fVar2 = kCmdMenuOne;
	CmdListEntry* entries = GetCmdListEntries(this);
	CmdListEntry* entry = entries;
	s32 iVar8 = 8;
	do {
		entry[0].scale = fVar2;
		entry[1].scale = fVar2;
		entry[2].scale = fVar2;
		entry[3].scale = fVar2;
		entry[4].scale = fVar2;
		entry[5].scale = fVar2;
		entry[6].scale = fVar2;
		entry[7].scale = fVar2;
		entry += 8;
		iVar8--;
	} while (iVar8 != 0);

	entry = entries;
	float fVar3 = kCmdMenuZero;
	float fVar4 = kCmdMenuSmallOffset;
	for (s32 iVar5 = 0; iVar5 < 8; iVar5++) {
		if (iVar5 < caravanWork->m_numCmdListSlots) {
			entry->tex = 0x2D;
		} else {
			entry->tex = 0xFFFFFFFF;
		}

		entry->width = 200;
		entry->height = 0x20;
		entry->x = 0x74;
		entry->y = static_cast<s16>(iVar5 * entry->height + 0x28);
		entry->u = fVar3;
		entry->v = fVar4;

		if ((2 <= iVar5) && (caravanWork->m_commandListInventorySlotRef[iVar5] < 0)) {
			entry->v += static_cast<float>(entry->height);
		}

		entry->startFrame = iVar5;
		entry->duration = 3;
		entry++;
	}

	GetCmdListStorage(this)->count = 8;
	CmdInit1();
	GetCmdItem();
	GetCmdStateView(this)->selected = 2;
	GetCmdStateView(this)->initialized = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdInit0()
{
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;

	for (s32 i = 0; i < list->count; i++) {
		entries[i].alpha = kCmdMenuOne;
		entries[i].scale = kCmdMenuOne;
	}

	const u32 count = static_cast<u32>(reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->m_numCmdListSlots);
	if (count == 0) {
		return;
	}

	for (s32 i = static_cast<s32>(count) - 1, idx = 0; i >= 0; i--, idx++) {
		entries[i].startFrame = idx;
		entries[i].duration = 3;
	}

	GetCmdStateView(this)->commandResult = 0;
}

#pragma push
#pragma opt_unroll_loops off
/*
 * --INFO--
 * PAL Address: 0x8014ff0c
 * PAL Size: 816b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdInit1()
{
	s32 idx = static_cast<s32>(GetCmdListStorage(this)->count);
	CmdListEntry* entry;

	entry = &GetCmdListStorage(this)->entries[idx++];
	entry->tex = 0x2e;
	entry->x = 0xb8;
	entry->y = 0x28;
	entry->width = 0x78;
	entry->height = 0x108;
	entry->u = kCmdMenuBasePanelU;
	entry->v = kCmdMenuSmallOffset;
	entry->scale = kCmdMenuOne;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &GetCmdListStorage(this)->entries[idx++];
	entry->tex = (GetCmdLayoutFlag(this) == 0) ? 0x46 : 0x2f;
	entry->x = 0xa0;
	entry->y = 0xe;
	entry->width = 0x30;
	entry->height = 0x30;
	entry->u = kCmdMenuZero;
	entry->v = kCmdMenuZero;
	entry->scale = kCmdMenuOne;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &GetCmdListStorage(this)->entries[idx++];
	entry->tex = (GetCmdLayoutFlag(this) == 0) ? 0x46 : 0x2f;
	entry->width = 0x30;
	entry->height = 0x30;
	entry->x = 0xa5;
	entry->y = static_cast<s16>(0x150 - entry->height);
	entry->u = kCmdMenuZero;
	entry->v = kCmdMenuZero;
	entry->scale = kCmdMenuThreeQuarter;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &GetCmdListStorage(this)->entries[idx++];
	entry->flags = 2;
	entry->tex = 0x2e;
	entry->x = 0xa0;
	entry->y = 8;
	entry->width = 0x48;
	entry->height = 0x140;
	entry->u = kCmdMenuZero;
	entry->v = kCmdMenuZero;
	entry->startFrame = 0;
	entry->duration = 5;

	CmdListEntry* basePanel = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count];
	s16 y = 0;
	for (s32 i = 0; i < 4; i++) {
		entry = &GetCmdListStorage(this)->entries[idx++];
		entry->flags = 2;
		entry->tex = 0x37;
		entry->x = static_cast<s16>(basePanel->x + 0x24);
		entry->y = static_cast<s16>(basePanel->y + y);
		entry->width = 200;
		entry->height = 0x28;
		entry->u = kCmdMenuZero;
		entry->v = kCmdMenuZero;
		entry->startFrame = 7;
		entry->duration = 5;
		y += 0x20;

		entry = &GetCmdListStorage(this)->entries[idx++];
		entry->flags = 2;
		entry->tex = 0x37;
		entry->x = static_cast<s16>(basePanel->x + 0x24);
		entry->y = static_cast<s16>(basePanel->y + y);
		entry->width = 200;
		entry->height = 0x28;
		entry->u = kCmdMenuZero;
		entry->v = kCmdMenuZero;
		entry->startFrame = 7;
		entry->duration = 5;
		y += 0x20;
	}

	GetCmdListStorage(this)->listEnd = static_cast<s16>(idx);

	CmdListStorage* list = GetCmdListStorage(this);
	const s32 count = static_cast<s32>(list->listEnd) - static_cast<s32>(list->count);
	CmdListEntry* fillEntry = &list->entries[list->count];
	for (s32 k = count; k > 0; k--) {
		fillEntry->timer = 0;
		fillEntry->alpha = kCmdMenuZero;
		fillEntry++;
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8014fc50
 * PAL Size: 700b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdInit2()
{
	s32 i = GetCmdListStorage(this)->count;
	CmdListEntry* entry;

	entry = &GetCmdListStorage(this)->entries[i++];
	entry->tex = 0x2e;
	entry->startFrame = 2;
	entry->duration = 5;

	entry = &GetCmdListStorage(this)->entries[i++];
	entry->tex = (GetCmdLayoutFlag(this) == 0) ? 0x46 : 0x2f;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &GetCmdListStorage(this)->entries[i++];
	entry->tex = (GetCmdLayoutFlag(this) == 0) ? 0x46 : 0x2f;
	entry->startFrame = 7;
	entry->duration = 5;

	entry = &GetCmdListStorage(this)->entries[i++];
	entry->flags = 2;
	entry->tex = 0x2e;
	entry->startFrame = 7;
	entry->duration = 5;

	for (s32 j = 0; j < 8; j++) {
		entry = &GetCmdListStorage(this)->entries[i++];
		entry->flags = 2;
		entry->tex = 0x37;
		entry->startFrame = 0;
		entry->duration = 5;
	}

	GetCmdListStorage(this)->listEnd = static_cast<s16>(i);

	CmdListStorage* list = GetCmdListStorage(this);
	s32 k = list->count;
	CmdListEntry* fillEntry = &list->entries[k];
	const float alpha = kCmdMenuOne;
	k = static_cast<s32>(list->listEnd) - k;
	for (; k > 0; k--) {
		fillEntry->timer = 0;
		fillEntry->alpha = alpha;
		fillEntry++;
	}
}

#pragma push
#pragma opt_propagation off
/*
 * --INFO--
 * PAL Address: 0x8014fa78
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdOpen()
{
	if (GetCmdStateView(this)->initialized == 0) {
		CmdInit();
	}

	CmdListEntry* entry;
	s32 finishedCount = 0;
	GetCmdStateView(this)->transitionTimer = static_cast<s16>(GetCmdStateView(this)->transitionTimer + 1);

	CmdListStorage* list = GetCmdListStorage(this);
	const s32 entryCount = list->count;
	entry = list->entries;
	const s32 timer = static_cast<s32>(GetCmdStateView(this)->transitionTimer);

	for (s32 i = 0; i < entryCount; i++) {
		if (entry->startFrame <= timer) {
			if ((entry->startFrame + entry->duration) <= timer) {
				finishedCount += 1;
				entry->alpha = kCmdMenuOne;
			} else {
				entry->timer++;
				f64 durationD = static_cast<double>(entry->duration);
				f64 timerD = static_cast<double>(entry->timer);
				entry->alpha = static_cast<float>((kCmdMenuOneD / durationD) * timerD);
			}
		}
		entry++;
	}

	int done = 0;
	CmdListStorage* const list2 = GetCmdListStorage(this);
	if (list2->count == finishedCount) {
		float anim = kCmdMenuOne;
		entry = list2->entries;
		for (s32 k = entryCount; k > 0; k--) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = anim;
			entry++;
		}
		done = 1;
	}

	if (done) {
		UniteOpenAnim(-1);
	}
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8014f4e8
 * PAL Size: 1424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CmdCtrl()
{
	u8* self = reinterpret_cast<u8*>(this);

	reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->CalcStatus();

	GetCmdStateView(this)->prevMode = GetCmdStateView(this)->mode;

	s32 actionHandled = 0;
	s32 mode = GetCmdStateView(this)->mode;

	if ((mode == 0) || ((mode != 0) && (GetCmdStateView(this)->phase == 1))) {
		actionHandled = CmdCtrlCur();
	} else if ((mode == 1) && (GetCmdStateView(this)->phase == 0)) {
		actionHandled = CmdOpen0();
		if (actionHandled != 0) {
			actionHandled = 0;
			GetCmdStateView(this)->phase = static_cast<s16>(GetCmdStateView(this)->phase + 1);
		}
	} else if ((mode == 1) && (GetCmdStateView(this)->phase == 2)) {
		actionHandled = CmdClose0();
		if (actionHandled != 0) {
			if (GetCmdStateView(this)->commandResult != 0) {
				GetCmdStateView(this)->phase = 0;
				GetCmdStateView(this)->mode = 3;
				GetCmdStateView(this)->transitionTimer = 0;
				GetCmdStateView(this)->commandResult = 0;
				CmdInit1();
			} else {
				GetCmdStateView(this)->phase = static_cast<s16>(GetCmdStateView(this)->phase + 1);
			}
			actionHandled = 0;
		}
	} else if ((mode == 1) && (GetCmdStateView(this)->phase == 3)) {
		actionHandled = UniteOpenAnim(-1);
		if (actionHandled != 0) {
			GetCmdStateView(this)->phase = 0;
			GetCmdStateView(this)->mode = 0;
			GetCmdStateView(this)->transitionTimer = 0;
			CmdInit1();
			actionHandled = 0;
		}
	} else if ((mode == 2) && (GetCmdStateView(this)->phase == 0)) {
		actionHandled = CmdOpen1();
		if (actionHandled != 0) {
			actionHandled = 0;
			GetCmdStateView(this)->phase = static_cast<s16>(GetCmdStateView(this)->phase + 1);
		}
	} else if ((mode == 2) && (GetCmdStateView(this)->phase == 2)) {
		actionHandled = CmdClose1();
		if (actionHandled != 0) {
			if (GetCmdStateView(this)->commandResult != 0) {
				GetCmdStateView(this)->uniteState = 0;
				GetCmdStateView(this)->mode = 3;
			} else {
				GetCmdStateView(this)->mode = 0;
			}
			actionHandled = 0;
			GetCmdStateView(this)->phase = 0;
			GetCmdStateView(this)->transitionTimer = 0;
		}
	} else if ((mode == 3) && (GetCmdStateView(this)->phase == 0)) {
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

		GetCmdStateView(this)->transitionTimer = static_cast<s16>(GetCmdStateView(this)->transitionTimer + 1);

		s32 selected = static_cast<s32>(GetCmdStateView(this)->selected);
		s32 prev;
		for (prev = selected - 1; prev > 2; prev--) {
			if (caravanWork->m_commandListExtra[prev] >= 0) {
				break;
			}
		}

		s32 limit = static_cast<s32>(caravanWork->m_numCmdListSlots);
		s32 next;
		for (next = selected + 1; next < limit; next++) {
			if (caravanWork->m_commandListExtra[next] >= 0) {
				break;
			}
		}

		CmdListEntry* fadeEntry;
		s32 i;
		for (i = 0; i < static_cast<s32>(GetCmdListStorage(this)->count); i++, fadeEntry++) {
			if ((i < prev) || (i > next)) {
				fadeEntry = &GetCmdListStorage(this)->entries[i];
				fadeEntry->alpha = static_cast<float>(
				    -((kCmdMenuAlphaStepD * static_cast<double>(static_cast<s32>(GetCmdStateView(this)->transitionTimer))) - kCmdMenuOneD));
				if (static_cast<double>(fadeEntry->alpha) < kCmdMenuHalfD) {
					fadeEntry->alpha = kCmdMenuHalf;
				}
			}
		}

		if (static_cast<double>(static_cast<s32>(GetCmdStateView(this)->transitionTimer)) >= kCmdMenuTransitionFramesD) {
			actionHandled = 1;
		} else {
			actionHandled = 0;
		}
		if (actionHandled != 0) {
			GetCmdStateSelections(GetCmdStateView(this))[GetCmdStateView(this)->mode] = static_cast<s16>(prev);
		}
		if (actionHandled != 0) {
			actionHandled = 0;
			GetCmdStateView(this)->phase = static_cast<s16>(GetCmdStateView(this)->phase + 1);
		}
	} else if ((mode == 3) && (GetCmdStateView(this)->phase == 2)) {
		actionHandled = CmdClose2();
		if (actionHandled != 0) {
			actionHandled = 0;
			GetCmdStateView(this)->phase = 0;
			GetCmdStateView(this)->mode = 0;
			GetCmdStateView(this)->transitionTimer = 0;
			GetCmdStateView(this)->commandResult = 0;
		}
	}

	if (actionHandled != 0) {
		CmdListEntry* entry = GetCmdListStorage(this)->entries;
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
		for (s32 i = 0; i < static_cast<s32>(GetCmdListStorage(this)->count); i++, entry++) {
			entry->alpha = kCmdMenuOne;
			entry->scale = kCmdMenuOne;
		}

		for (s32 i = static_cast<s32>(caravanWork->m_numCmdListSlots) - 1, idx = 0; i >= 0; i--, idx++) {
			CmdListEntry* e = &GetCmdListStorage(this)->entries[i];
			e->startFrame = idx;
			e->duration = 3;
		}

		GetCmdStateView(this)->commandResult = 0;
	}
	return actionHandled;
}

/*
 * --INFO--
 * PAL Address: 0x8014f2e8
 * PAL Size: 512b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CmdClose()
{
	u8* self = reinterpret_cast<u8*>(this);
	if (GetCmdStateView(this)->commandResult == 0) {
		if (UniteCloseAnim(-1) != 0) {
			GetCmdStateView(this)->transitionTimer = 0;
			GetCmdStateView(this)->commandResult = 1;
		}
		return 0;
	}

	CmdListEntry* entry;
	s32 doneCount = 0;
	GetCmdStateView(this)->transitionTimer = GetCmdStateView(this)->transitionTimer + 1;

	const s32 entryCount = static_cast<s32>(GetCmdListStorage(this)->count);
	entry = GetCmdListStorage(this)->entries;
	s32 closeTimer = static_cast<s32>(GetCmdStateView(this)->transitionTimer);

	for (s32 i = 0; i < entryCount; i++) {
		if (entry->startFrame <= closeTimer) {
			if ((entry->startFrame + entry->duration) <= closeTimer) {
				doneCount = doneCount + 1;
				entry->alpha = 0.0f;
			} else {
				entry->timer++;
				entry->alpha = static_cast<float>(
				    -((1.0 / static_cast<double>(entry->duration)) *
				          static_cast<double>(entry->timer) -
				      1.0));
				if (static_cast<double>(entry->alpha) < 0.0) {
					entry->alpha = 0.0f;
				}
			}
		}
		entry++;
	}

	s32 ret = 0;
	if (doneCount == GetCmdListStorage(this)->count) {
		CmdListEntry* p = GetCmdListStorage(this)->entries;
		for (s32 i = entryCount; i > 0; i--) {
			p->startFrame = 0;
			p->duration = 1;
			p->alpha = 0.0f;
			p++;
		}
		ret = 1;
	}

	return ret;
}

#pragma push
#pragma opt_lifetimes off
/*
 * --INFO--
 * PAL Address: 0x8014dd88
 * PAL Size: 5472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmdDraw()
{
	bool hasItemHelp = false;
	s32 helpId;
	float t;
	float x;
	float y;
	float w;
	GXColor colors[4];

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	CCaravanWork* const caravan = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	const s32 animState = GetCmdStateView(this)->animState;
	const s32 cmdMode = GetCmdStateView(this)->mode;

	CmdListEntry* entry = GetCmdListStorage(this)->entries;
	for (s32 i = 0; i < GetCmdListStorage(this)->count; i++, entry++) {
		const s32 tex = entry->tex;
		if (tex >= 0) {
			x = static_cast<float>(entry->x);
			y = static_cast<float>(entry->y);
			w = static_cast<float>(entry->width);
			float h = static_cast<float>(entry->height);
			const float u = entry->u;

			if ((i >= 8) || (caravan->m_commandListExtra[i] == 0)) {
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
				if ((caravan->m_commandListInventorySlotRef[i] >= 2) &&
				    (caravan->m_commandListInventorySlotRef[i] == -1)) {
					t = kCmdMenuSmallOffset + h;
				} else {
					t = kCmdMenuSmallOffset;
				}
				int __p17 = animState;
				if ((__p17 == 1) && (i < caravan->m_numCmdListSlots) &&
				    (i == GetCmdStateView(this)->selected)) {
					t = kCmdMenuSelectedUvY;
					y -= kCmdMenuSmallOffset;
					h += kCmdMenuSmallOffset;
				}

				colors[0].r = 0xFF;
				colors[0].g = 0xFF;
				colors[0].b = 0xFF;
				colors[0].a = static_cast<u8>(kCmdMenuAlphaMax * entry->alpha);
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);

				MenuPcs.DrawRect(
				    0, x, y, w, h, u, t, entry->scale, entry->scale, 0.0f);
			}
		}
	}

	CFont* nameFont = m_fonts[4];
	nameFont->SetMargin(kCmdMenuOne);
	nameFont->SetShadow(0);
	nameFont->SetScale(kCmdMenuTextScale);
	nameFont->DrawInit();

	CmdListEntry* nameEntry = GetCmdListStorage(this)->entries;
	for (s32 i = 0; i < caravan->m_numCmdListSlots; i++, nameEntry++) {
		if ((i >= 8) || (caravan->m_commandListExtra[i] == 0)) {
			nameFont->SetColor(
			    CColor(0xFF, 0xFF, 0xFF,
			        static_cast<u8>(kCmdMenuAlphaMax *
			            static_cast<float>(cmdMode == 3 ? kCmdMenuOneD : static_cast<double>(nameEntry->alpha))))
			        .color);

			const char* text;
			if (i < 2) {
				text = GetMenuStr(i + 9);
			} else {
				const int cmdId =  (int)(long)(caravan->m_commandListInventorySlotRef[i]);
				if (cmdId >= 0) {
					const int skillId = caravan->m_inventoryItems[cmdId];
					char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
					text = flatText[skillId * 5 + 4];
					if ((GetCmdStateView(this)->mode == 0) && (i == GetCmdStateView(this)->selected)) {
						helpId = skillId;
						hasItemHelp = true;
					}
				} else {
					continue;
				}
			}

			const float textW = static_cast<float>(nameFont->GetWidth(text));
			x = static_cast<double>(nameEntry->x) + ((static_cast<float>(nameEntry->width) - textW) * 0.5);
			y = static_cast<float>(nameEntry->y + 3);
			nameFont->SetPosX(x);
			nameFont->SetPosY(y - kCmdMenuTextYOffset);
			nameFont->Draw(text);
		}
	}

	DrawInit();
	DrawUniteList();

	CmdListEntry* iconEntry = GetCmdListStorage(this)->entries;
	for (s32 i = 0; i < caravan->m_numCmdListSlots; i++, iconEntry++) {
		if ((i >= 2) && (caravan->m_commandListInventorySlotRef[i] >= 0)) {
			y = static_cast<float>(iconEntry->y - 2);
			x = static_cast<float>(iconEntry->x + iconEntry->width - 0x10);
			DrawSingleIcon(
			    caravan->m_inventoryItems[caravan->m_commandListInventorySlotRef[i]],
			    static_cast<s32>(static_cast<float>(iconEntry->x + iconEntry->width - 0x10)),
			    static_cast<s32>(y - kCmdMenuOne), iconEntry->alpha, 0, kCmdMenuOne);
		}
	}

	if (GetCmdStateView(this)->prevMode != 0) {
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		CmdListEntry* row = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count];
		const s16* letterBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const s32 itemCount = letterBuf[0];
		s32 specialRow = 0;
		for (s32 idx = GetCmdListStorage(this)->count; idx < GetCmdListStorage(this)->listEnd; idx++, row++) {
			const s32 tex = row->tex;
			if (tex >= 0) {
				const float rowH = static_cast<float>(row->height);
				float rowU = row->u;
				x = static_cast<float>(row->x);
				y = static_cast<float>(row->y);
				w = static_cast<float>(row->width);
				t = row->v;

				if (idx == GetCmdListStorage(this)->count) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

					colors[0].r = 0xFF;
					colors[0].g = 0xFF;
					colors[0].b = 0xFF;
					colors[0].a = 0xFF;
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0xFF;
					colors[2].r = 0xFF;
					colors[2].g = 0xFF;
					colors[2].b = 0xFF;
					colors[2].a = 0xFF;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0xFF;
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);

					w = row->alpha * w;
					if (w > kCmdMenuZero) {
						MenuPcs.DrawRect(0, x, y, w, rowH, rowU, t, colors,
						    kCmdMenuOne, kCmdMenuOne, 0.0f);
						x += w;
						rowU += w;
					}
					if ((w > kCmdMenuZero) && (w < static_cast<float>(row->width))) {
						colors[1].r = 0xFF;
						colors[1].g = 0xFF;
						colors[1].b = 0xFF;
						colors[1].a = 0;
						colors[3].r = 0xFF;
						colors[3].g = 0xFF;
						colors[3].b = 0xFF;
						colors[3].a = 0;
						w = static_cast<float>(
						    kCmdMenuOneD / static_cast<double>(row->duration));
						w *= static_cast<float>(row->width);
						MenuPcs.DrawRect(0, x, y, w, rowH, rowU, t, colors,
						    kCmdMenuOne, kCmdMenuOne, 0.0f);
					}

					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				} else {
					float rowAlpha = row->alpha;
					s32 rowTex = tex;
					if (tex == 0x37) {
						s32 sel = specialRow + GetCmdStateView(this)->scrollTop;
						if ((itemCount >= 8) && (sel >= itemCount)) {
							sel -= itemCount;
						}

						if (sel < 2) {
							const CCaravanWork* const caravan2 =
							    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
							const s16* canBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
							u8 canUse;
							if ((sel < 0) || (sel >= canBuf[0])) {
								canUse = 0;
							} else if (sel == 0) {
								canUse = static_cast<u32>(
								    caravan2->m_commandListInventorySlotRef[GetCmdStateView(this)->selected] >= 0);
							} else if (sel == 1) {
								int combo[5][2];
								canUse = static_cast<u32>(
								    ChkUnite(GetCmdStateView(this)->selected, combo) != 0);
							} else {
								canUse = static_cast<u32>(static_cast<u8>(EquipChk(static_cast<int>(canBuf[sel - 1]))) == 0);
							}

							if (canUse == 0) {
								rowAlpha = kCmdMenuHalfD * row->alpha;
								rowTex = 0x34;
							}
						} else {
							s32 itemIdx = sel - 2;
							if ((itemCount >= 8) && (itemIdx >= itemCount)) {
								itemIdx -= itemCount;
							}

							int equippable = 1;
							int __p18 = itemIdx;
							if (__p18 + 2 < itemCount) {
								equippable = EquipChk(static_cast<int>(letterBuf[itemIdx + 1]));
							}

							if (static_cast<u8>(equippable) != 0) {
								int __p8 = itemIdx;
								if (__p8 + 2 < itemCount) {
									DrawEquipMark(static_cast<s32>(x - kCmdMenuTwelve),
									    static_cast<s32>(((rowH - kCmdMenuTwentyFour) * kCmdMenuHalfD) + y),
									    row->alpha);
								}
								rowTex = 0x34;
								rowAlpha = kCmdMenuHalfD * row->alpha;
							}
						}

						if ((rowTex == 0x37) &&
						    (specialRow == GetCmdStateView(this)->itemSelected)) {
							t += rowH;
						}
						specialRow++;
					}

					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(rowTex));

					colors[0].r = 0xFF;
					colors[0].g = 0xFF;
					colors[0].b = 0xFF;
					colors[0].a = static_cast<u8>(kCmdMenuAlphaMax * rowAlpha);
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);

					MenuPcs.DrawRect(0, x, y, w, rowH, rowU, t, row->scale,
					    row->scale, 0.0f);
				}
			}
		}
	}

	if (cmdMode == 1) {
		CFont* listFont = m_fonts[0];
		listFont->SetMargin(kCmdMenuOne);
		listFont->SetShadow(0);
		listFont->SetScale(kCmdMenuTextScale);
		listFont->DrawInit();

		const s16* letterBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const s32 itemCount = letterBuf[0];
		CmdListEntry* scan = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count];
		for (s32 idx = GetCmdListStorage(this)->count; idx < GetCmdListStorage(this)->listEnd; idx++) {
			if (scan->tex == 0x37) {
				break;
			}
			scan++;
		}

		CmdListEntry* textRow = scan;
		for (s32 row = 0; row < 8; row++, textRow++) {
			if ((itemCount <= 8) && (row + GetCmdStateView(this)->scrollTop >= itemCount)) {
				break;
			}

			s32 displayIdx =  (s32)(row + GetCmdStateView(this)->scrollTop);
			if (displayIdx >= itemCount) {
				displayIdx -= itemCount;
			}

			const float alpha = textRow->alpha;
			listFont->SetColor(
			    CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(kCmdMenuAlphaMax * alpha)).color);

			const char* text;
			if (displayIdx < 2) {
				text = GetMenuStr(displayIdx + 0x0B);
			} else if (!(displayIdx >= itemCount)) {
				const s16 slot = letterBuf[displayIdx - 1];
				const s16 skillId = caravan->m_inventoryItems[slot];
				char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
				text = flatText[skillId * 5 + 4];

				s32 selDisp = GetCmdStateView(this)->itemSelected + GetCmdStateView(this)->scrollTop;
				if (selDisp >= itemCount) {
					selDisp -= itemCount;
				}
				if (displayIdx == selDisp) {
					int __p21 = skillId;
					helpId = __p21;
					hasItemHelp = true;
				}
			} else {
				continue;
			}

			listFont->GetWidth(text);
			x = static_cast<float>(textRow->x + 0x1C);
			y = static_cast<float>(textRow->y + 0x0B);
			listFont->SetPosX(static_cast<float>(textRow->x + 0x1C));
			listFont->SetPosY(y - kCmdMenuTextYOffset);
			listFont->Draw(text);
		}

		DrawInit();

		CmdListEntry* iconRow = scan;
		for (s32 row =  (int)(unsigned int)(0); row < 8; row++, iconRow++) {
			if ((itemCount <= 8) && (row + GetCmdStateView(this)->scrollTop >= itemCount)) {
				break;
			}

			s32 displayIdx = row + GetCmdStateView(this)->scrollTop;
			if (displayIdx >= itemCount) {
				displayIdx -= itemCount;
			}

			if (displayIdx >= 2) {
				const s16 slot = letterBuf[displayIdx - 1];
				y = static_cast<float>(iconRow->y + 6);
				x = static_cast<float>(iconRow->x + iconRow->width - 0x10);
				DrawSingleIcon(
				    caravan->m_inventoryItems[slot],
				    static_cast<s32>(static_cast<float>(iconRow->x + iconRow->width - 0x10)),
				    static_cast<s32>(y - kCmdMenuOne),
				    iconRow->alpha, 0, kCmdMenuOne);
			}
		}
	}

	if ((cmdMode == 1) && (GetCmdStateView(this)->phase == 1)) {
		const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const float mark = CalcListPos(GetCmdStateView(this)->scrollTop, letter[0], 1);
		CmdListEntry* listPos = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count];
		if (mark > kCmdMenuZero) {
			DrawListPosMark(static_cast<float>(listPos->x), static_cast<float>(listPos->y), mark);
		}
	}

	if (cmdMode == 2) {
		CmdListEntry* panel = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd + 3];
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(panel->tex));

		colors[0].r = 0xFF;
		colors[0].g = 0xFF;
		colors[0].b = 0xFF;
		colors[0].a = static_cast<u8>(kCmdMenuAlphaMax * panel->alpha);
		GXSetChanMatColor(GX_COLOR0A0, colors[0]);
		MenuPcs.DrawRect(
		    0, static_cast<float>(panel->x), static_cast<float>(panel->y),
		    static_cast<float>(panel->width), static_cast<float>(panel->height),
		    panel->u, panel->v, kCmdMenuOne, panel->scale, 0.0f);

		CFont* choiceFont = m_fonts[0];
		choiceFont->SetMargin(kCmdMenuOne);
		choiceFont->SetShadow(1);
		choiceFont->SetScale(kCmdMenuTextScale);
		choiceFont->DrawInit();
		choiceFont->SetTlut(7);
		choiceFont->SetColor(
		    CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(kCmdMenuAlphaMax * panel->alpha)).color);

		const s32 choices = (kCmdMenuOneD == static_cast<double>(panel->scale)) ? 2 : 3;
		for (s32 choice = 0; choice < choices; choice++) {
			const char* text;
			if (choice == 0) {
				text = GetMenuStr(0x0D);
			} else if ((choice == 1) && (choices == 3)) {
				text = GetMenuStr(0x0C);
			} else {
				text = GetMenuStr(0x37);
			}
			choiceFont->GetWidth(text);
			const float pitch = static_cast<float>(
			    ((static_cast<float>(panel->height) * panel->scale) - kCmdMenuChoicePaddingD) /
			    choices);
			y = ((pitch * static_cast<float>(choice)) + static_cast<float>(panel->y + 8)) +
			    ((pitch - kCmdMenuTextLineHeightD) * kCmdMenuHalfD);
			x = static_cast<float>(panel->x + 0x18);
			choiceFont->SetPosX(static_cast<float>(panel->x + 0x18));
			choiceFont->SetPosY(y - kCmdMenuTextYOffset);
			choiceFont->Draw(text);
		}
		DrawInit();
	}

	if (((cmdMode == 0) && (animState == 1)) ||
	    ((cmdMode != 0) && (GetCmdStateView(this)->phase == 1))) {
		CmdListEntry* cursorEntry;
		s32 cursorOnUnite = false;

		if ((cmdMode == 0) || (cmdMode == 3)) {
			s32 index = GetCmdStateSelections(GetCmdStateView(this))[cmdMode];
			if (!(caravan->m_commandListExtra[index] == 0)) {
				s32 uniteIdx;
				for (uniteIdx = 0; uniteIdx < s_unitePanelCount; uniteIdx++) {
					if (s_UniteTop[uniteIdx] == index) {
						break;
					}
				}
				cursorEntry = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd + uniteIdx];
				cursorOnUnite = true;
			} else {
				cursorEntry = &GetCmdListStorage(this)->entries[index];
			}
		} else if (cmdMode == 1) {
			CmdListStorage* const list = GetCmdListStorage(this);
			for (s32 idx = list->count; idx < list->listEnd; idx++) {
				cursorEntry = &list->entries[idx];
				if (cursorEntry->tex == 0x37) {
					break;
				}
			}
			cursorEntry = cursorEntry + GetCmdStateView(this)->itemSelected;
		} else {
			CmdListEntry* panel = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd + 3];
			const s32 choices = (kCmdMenuOneD == static_cast<double>(panel->scale)) ? 2 : 3;
			const float pitch = static_cast<float>(
			    ((static_cast<float>(panel->height) * panel->scale) - kCmdMenuChoicePaddingD) /
			    static_cast<double>(choices));
			x = static_cast<float>(panel->x - 0x14);
			y = ((pitch - kCmdMenuTextLineHeightD) * kCmdMenuHalfD) +
			    ((pitch * static_cast<float>(GetCmdStateView(this)->choice)) + static_cast<float>(panel->y + 8));
		}

		if (cmdMode != 2) {
			if (!cursorOnUnite) {
				x = static_cast<float>(cursorEntry->x - 0x14);
				y = static_cast<float>(cursorEntry->y);
				if (GetCmdStateView(this)->mode != 0) {
					y += kCmdMenuSmallOffset;
				}
			} else {
				y = (cursorEntry->height - 0x20) * kCmdMenuHalfD + cursorEntry->y;
				x = static_cast<float>(cursorEntry->x - 0x14);
			}
		}

		const s32 frame = static_cast<s32>(System.m_frameCounter) % 8;
		DrawCursor(static_cast<s32>(x + static_cast<float>(frame)), static_cast<s32>(y), kCmdMenuOne);
	}

	const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	s32 idx = GetCmdStateView(this)->itemSelected + GetCmdStateView(this)->scrollTop;
	if (idx >= letter[0]) {
		idx -= letter[0];
	}

	CFont* helpFont = m_fonts[0];
	int helpAlpha = static_cast<int>(
	    kCmdMenuAlphaMax * GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count].alpha);
	if (!hasItemHelp) {
		helpId = -1;
	}

	const s16 mode = GetCmdStateView(this)->mode;
	if (mode == 0) {
		if (helpId == -1) {
			if (caravan->m_commandListExtra[GetCmdStateView(this)->selected] == 0) {
				helpId = 0x266;
			}
		}
	}
	if (mode == 1) {
		if (idx < 2) {
			helpId = idx + 0x259;
		}
	}
	if (mode == 2) {
		if (GetCmdStateView(this)->choice == 0) {
			helpId = 0x25B;
		} else {
			helpId = -1;
		}
	}
	if ((mode == 0) || (mode == 2)) {
		helpAlpha = static_cast<int>(kCmdMenuAlphaMax * GetCmdListStorage(this)->entries[0].alpha);
	}

	float helpX = static_cast<float>(-(w * kCmdMenuHalf - kCmdMenuScreenHalfWidth));
	float helpY = kCmdMenuHelpXOffset;
	DrawHelpMessage(
	    helpId, helpFont, static_cast<int>(helpX), static_cast<int>(helpY),
	    CColor(0xFF, 0xFF, 0xFF, helpAlpha).color, 10,
	    kCmdMenuOne, kCmdMenuThree);
}
#pragma pop

#pragma push
#pragma optimization_level 3
/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 2836b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdCtrlCur()
{
	int press;
	int hold;
	s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	const int padLock = Pad.m_debugPadLock;

	bool blocked = false;
	int __p12 = padLock;
	if ((__p12 != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		int __p20 = padIndex;
		int __p18 = __p20;
		const int pressRaw = Pad.GetPadInputs()[__p18].buttonDown[0];
		press = static_cast<s16>(static_cast<u16>(pressRaw));
	}

	blocked = false;
	int __p13 =  (int)(unsigned int)(padLock);
	if ((__p13 != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		int __p14 = padIndex;
		const int holdRaw = Pad.GetPadInputs()[__p14].repeatButton;
		hold = static_cast<s16>(static_cast<u16>(holdRaw));
	}

	if (hold == 0) {
		return 0;
	}

	s32 mode = GetCmdStateView(this)->mode;

	if (mode == 0) {
		const s32 cmdCount = caravanWork->m_numCmdListSlots;

		if ((hold & 8) != 0) {
			CmdState* row = ModeRow(GetCmdStateView(this), mode);
			if (row->selected > 2) {
				row->selected--;
			} else {
				row->selected = static_cast<s16>(cmdCount - 1);
			}

			CmdState* row2 = ModeRow(GetCmdStateView(this), mode);
			const int cursor = row2->selected;
			if (caravanWork->m_commandListExtra[cursor] < 0) {
				const int m1 = cursor - 1;
				if (*reinterpret_cast<const s16*>(reinterpret_cast<const u8*>(caravanWork) + m1 * 2 + 0x214) >= 0) {
					row2->selected = static_cast<s16>(m1);
				} else {
					const int m2 = cursor - 2;
					if (*reinterpret_cast<const s16*>(reinterpret_cast<const u8*>(caravanWork) + m2 * 2 + 0x214) >= 0) {
						row2->selected = static_cast<s16>(m2);
					}
				}
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else {
			if ((hold & 4) != 0) {
				CmdState* row = ModeRow(GetCmdStateView(this), mode);
				if (row->selected < cmdCount - 1) {
					row->selected++;
				} else {
					row->selected = 2;
				}

				CmdState* row2 = ModeRow(GetCmdStateView(this), mode);
				const int cursor = row2->selected;
				if (caravanWork->m_commandListExtra[cursor] < 0) {
					const int p1 = cursor + 1;
					if (*reinterpret_cast<const s16*>(reinterpret_cast<const u8*>(caravanWork) + p1 * 2 + 0x214) >= 0) {
						row2->selected = static_cast<s16>(p1);
					} else {
						const int p2 = cursor + 2;
						if (*reinterpret_cast<const s16*>(reinterpret_cast<const u8*>(caravanWork) + p2 * 2 + 0x214) >= 0) {
							row2->selected = static_cast<s16>(p2);
						}
					}
					CmdState* row3 = ModeRow(GetCmdStateView(this), mode);
					if (row3->selected > cmdCount - 1) {
						row3->selected = 2;
					}
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x20) != 0) {
				GetCmdStateView(this)->action = 1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x40) != 0) {
				GetCmdStateView(this)->action = -1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x100) != 0) {
				if (!(caravanWork->m_commandListExtra[ModeRow(GetCmdStateView(this), mode)->selected] == 0)) {
					GetCmdStateView(this)->unitePanelInitialized = 0;
					GetCmdStateView(this)->mode = 2;
				} else {
					GetCmdStateView(this)->mode = 1;
				}
				GetCmdStateView(this)->phase = 0;
				GetCmdStateView(this)->transitionTimer = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else {
				if ((press & 0x200) != 0) {
					GetCmdStateView(this)->uniteOpenFlag = 1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
					return 1;
				}
			}
		}
	} else if (mode == 1) {
		int itemCount = static_cast<int>(reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0))[0]);

		if (!((hold & 8) == 0)) {
			CmdState* sv1 = GetCmdStateView(this);
			CmdState* row = ModeRow(sv1, mode);
			if (!(row->selected == 0)) {
				row->selected--;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				if (itemCount <= 8) {
					row->selected = static_cast<s16>(itemCount - 1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else if (!(sv1->scrollTop == 0)) {
					sv1->scrollTop--;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					sv1->scrollTop = static_cast<s16>(itemCount - 1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
		} else {
			if ((hold & 4) != 0) {
				if (((itemCount > 8) && (ModeRow(GetCmdStateView(this), mode)->selected < 7)) ||
				    ((itemCount <= 8) &&
				     (ModeRow(GetCmdStateView(this), mode)->selected < itemCount - 1))) {
					ModeRow(GetCmdStateView(this), mode)->selected++;
				} else {
					if (itemCount <= 8) {
						ModeRow(GetCmdStateView(this), mode)->selected = 0;
					} else if (GetCmdStateView(this)->scrollTop < itemCount - 1) {
						GetCmdStateView(this)->scrollTop++;
					} else {
						GetCmdStateView(this)->scrollTop = 0;
					}
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if (!((press & 0x100) == 0)) {
				int comboChoice[5][2];
				int combo[5][2];
				int selected = static_cast<int>(GetCmdStateView(this)->scrollTop) +
				               static_cast<int>(ModeRow(GetCmdStateView(this), mode)->selected);
				if (selected >= itemCount) {
					selected -= itemCount;
				}

				CCaravanWork* const cw = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
				s16* const list2 = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
				const int itemCount2 = list2[0];
				s16* const items = list2 + 1;

				int canUse;
				if ((selected < 0) || (selected >= itemCount2)) {
					canUse = 0;
				} else if (selected == 0) {
					canUse = static_cast<int>(
					    (static_cast<u32>(cw->m_commandListInventorySlotRef[GetCmdStateView(this)->selected]) >> 31) ^ 1);
				} else if (selected == 1) {
					canUse = (ChkUnite(GetCmdStateView(this)->selected, combo) != 0);
				} else {
					canUse = static_cast<int>(
					    static_cast<u32>(__cntlzw(static_cast<u8>(EquipChk(static_cast<int>(items[selected - 2]))))) >> 5);
				}

				if (!((canUse & 0xFF) == 0)) {
					if (selected == 0) {
						caravanWork->ChgCmdLst(GetCmdStateView(this)->selected, -1);
					} else if (selected != 1) {
						caravanWork->ChgCmdLst(GetCmdStateView(this)->selected, list[selected - 1]);
					}

					GetCmdStateView(this)->commandResult = 0;
					if (selected != 0) {
						int comboCount;
						comboCount = ChkUnite(GetCmdStateView(this)->selected, comboChoice);
						if (comboCount == 1) {
							const int recipe = comboChoice[0][0];
							reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->UniteComList(
							    comboChoice[0][1], GetUniteRecipeCount(recipe), GetUniteRecipeCmd(recipe));
						} else if (comboCount > 1) {
							if (!(GetUniteRecipeCount(comboChoice[1][0]) == 2)) {
								const int recipe = comboChoice[0][0];
								reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->UniteComList(
								    comboChoice[0][1], GetUniteRecipeCount(recipe), GetUniteRecipeCmd(recipe));
							} else {
								GetCmdStateView(this)->commandResult = 1;
							}
						}
					}

					GetCmdStateView(this)->phase++;
					GetCmdStateView(this)->transitionTimer = 0;
					CmdInit2();
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				} else {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				}
			} else {
				if ((press & 0x200) != 0) {
					GetCmdStateView(this)->phase++;
					GetCmdStateView(this)->transitionTimer = 0;
					GetCmdStateView(this)->commandResult = 0;
					CmdInit2();
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			}
		}
	int __p13 = mode;
	} else if (__p13 == 2) {
		CmdListStorage* cmdList = GetCmdListStorage(this);
		const int animSlot = cmdList->listEnd + 3;
		int maxPos;
		if (kCmdMenuOneD ==
		    static_cast<double>(*reinterpret_cast<f32*>(reinterpret_cast<u8*>(cmdList) + animSlot * 0x40 + 0x1c))) {
			maxPos = 2;
		} else {
			maxPos = 3;
		}

		if (!((hold & 8) == 0)) {
			CmdState* row = ModeRow(GetCmdStateView(this), mode);
			if (!(row->selected == 0)) {
				row->selected--;
			} else {
				row->selected = static_cast<s16>(maxPos - 1);
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else {
			if ((hold & 4) != 0) {
				CmdState* row = ModeRow(GetCmdStateView(this), mode);
				if (row->selected < maxPos - 1) {
					row->selected++;
				} else {
					row->selected = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			GetCmdStateView(this)->uniteState = 0;
			if (!((press & 0x100) == 0)) {
				GetCmdStateView(this)->phase++;
				GetCmdStateView(this)->transitionTimer = 0;
				GetCmdStateView(this)->commandResult = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else {
				if ((press & 0x200) != 0) {
					GetCmdStateView(this)->phase++;
					GetCmdStateView(this)->transitionTimer = 0;
					GetCmdStateView(this)->commandResult = -1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			}
		}
	} else {
		if ((hold & 0xC) != 0) {
			CmdState* const sv0 = GetCmdStateView(this);
			const int selected = sv0->selected;
			int prev = selected - 1;
			while (prev > 2) {
				if (caravanWork->m_commandListExtra[prev] >= 0) {
					break;
				}
				prev--;
			}

			const int cmdCount = caravanWork->m_numCmdListSlots;
			int next = selected + 1;
			while (next < cmdCount) {
				if (caravanWork->m_commandListExtra[next] >= 0) {
					break;
				}
				next++;
			}

			CmdState* row = ModeRow(sv0, mode);
			if (row->selected == prev) {
				row->selected = static_cast<s16>(next);
			} else {
				row->selected = static_cast<s16>(prev);
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			GetCmdStateView(this)->commandResult = 0;
			GetCmdStateView(this)->uniteState = 0;
			if (!((press & 0x100) == 0)) {
				GetCmdStateView(this)->phase++;
				GetCmdStateView(this)->transitionTimer = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else {
				if ((press & 0x200) != 0) {
					GetCmdStateView(this)->commandResult = -1;
					GetCmdStateView(this)->phase++;
					GetCmdStateView(this)->transitionTimer = 0;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			}
		}
	}

	return 0;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8014d0c4
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdOpen0()
{
	GetCmdStateView(this)->transitionTimer = static_cast<s16>(GetCmdStateView(this)->transitionTimer + 1);
	const s32 timer = static_cast<s32>(GetCmdStateView(this)->transitionTimer);
	const s32 sel = GetCmdStateView(this)->selected;
	CmdListEntry* selEntry = &GetCmdListStorage(this)->entries[sel];
	if (timer < 5) {
		selEntry->x = static_cast<s16>(selEntry->x - 0x13);
	}

	CmdListEntry* entry = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count];
	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(GetCmdListStorage(this)->listEnd) - static_cast<s32>(GetCmdListStorage(this)->count);
	const float fVar1 = kCmdMenuZero;

	for (s32 i = 0; i < entryCount; i++) {
		if (timer >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= timer) {
				doneCount++;
				entry->alpha = kCmdMenuOne;
				entry->dx = fVar1;
				entry->dy = fVar1;
			} else {
				entry->timer++;
				const double step = kCmdMenuOneD / static_cast<double>(entry->duration);
				entry->alpha = static_cast<float>(step * static_cast<double>(entry->timer));
				if ((entry->flags & 2) == 0) {
					const float t = static_cast<float>(
						(kCmdMenuOneD / static_cast<double>(entry->duration)) *
						static_cast<double>(entry->timer));
					const float dx = entry->targetX - static_cast<float>(entry->x);
					const float dy = entry->targetY - static_cast<float>(entry->y);
					entry->dx = dx * t;
					entry->dy = dy * t;
				}
			}
		}

		entry++;
	}

	unsigned int done = 0;
	if (entryCount == doneCount) {
		done = 1;
	}
	return done;
}

/*
 * --INFO--
 * PAL Address: 0x8014cef8
 * PAL Size: 460b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose0()
{
	GetCmdStateView(this)->transitionTimer = static_cast<s16>(GetCmdStateView(this)->transitionTimer + 1);
	s32 time = static_cast<s32>(GetCmdStateView(this)->transitionTimer);
	const s32 sel = GetCmdStateView(this)->selected;

	if (time > 7) {
		CmdListEntry* e = &GetCmdListStorage(this)->entries[sel];
		e->x = static_cast<s16>(e->x + 0x13);
	}

	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(GetCmdListStorage(this)->listEnd) - static_cast<s32>(GetCmdListStorage(this)->count);
	CmdListEntry* entry = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count];

	for (s32 i = 0; i < entryCount; i++) {
		if (time >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= time) {
				doneCount++;
				entry->alpha = 0.0f;
				entry->dx = 0.0f;
				entry->dy = 0.0f;
			} else {
				entry->timer++;
				entry->alpha = static_cast<f32>(
				    1.0 - ((kCmdMenuOneD / static_cast<f64>(entry->duration)) *
				           static_cast<f64>(entry->timer)));
				if ((entry->flags & 2) == 0) {
					const f32 t = static_cast<f32>(
					    1.0 - ((kCmdMenuOneD / static_cast<f64>(entry->duration)) *
					           static_cast<f64>(entry->timer)));
					const f32 dx = entry->targetX - static_cast<f32>(entry->x);
					const f32 dy = entry->targetY - static_cast<f32>(entry->y);
					entry->dx = dx * t;
					entry->dy = dy * t;
				}
			}
		}
		entry++;
	}

	unsigned int done = 0;
	if (entryCount == doneCount) {
		done = 1;
		CmdListEntry* e = &GetCmdListStorage(this)->entries[GetCmdStateView(this)->selected];
		e->x = GetCmdListEntries(this)[0].x;
	}

	return done;
}

/*
 * --INFO--
 * PAL Address: 0x8014cce0
 * PAL Size: 536b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma opt_propagation off
void CMenuPcs::GetCmdItem()
{
	s32 count;
	s16* list;
	const CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	s16* write = list;
	count = 0;
	s32 i = count;

	for (; i < 0x40; i++) {
		s32 itemType = GetItemType(i, 0);
		if ((itemType != 0) && (itemType != 5) && (itemType != 6) && (itemType != 8) && (itemType != 9)) {
			if (itemType == 1) {
				const s32 tribe = caravanWork->m_tribeId & 3;
				const s32 icon = GetItemIcon(caravanWork->m_inventoryItems[i]);
				if (icon != tribe) {
					continue;
				}
			}
			write++;
			*write = static_cast<s16>(i);
			count++;
		}
	}

	s16* write2 = list + count;
	const u8* artrow = reinterpret_cast<const u8*>(caravanWork);
	for (s32 i = 0; i < 0x49; artrow += 2, i++) {
		s32 arti = i + 0x9f;
		if (reinterpret_cast<const CCaravanWork*>(artrow)->m_artifacts[0] == arti) {
			if (IsMagicArti(arti)) {
				count++;
				write2++;
				*write2 = static_cast<s16>(i + 0x40);
			}
		}
	}

	write2 = list + count;
	if (IsMagicArti(caravanWork->m_treasures[0])) {
		count++;
		write2++;
		*write2 = 0xa0;
	}
	if (IsMagicArti(caravanWork->m_treasures[1])) {
		count++;
		write2++;
		*write2 = 0xa1;
	}
	if (IsMagicArti(caravanWork->m_treasures[2])) {
		count++;
		write2++;
		*write2 = 0xa2;
	}
	if (IsMagicArti(caravanWork->m_treasures[3])) {
		count++;
		write2[1] = 0xa3;
	}

	s16* out = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	*out = count + 2;
}
#pragma pop

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkCmdActive(int itemIndex)
{
	CmdState* const cmd = GetCmdStateView(this);
	cmd->commandResult = 0;

	const CCaravanWork* const caravan = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	const s16 selected = cmd->selected;
	int active = 0;

	if (itemIndex == 0) {
		active = caravan->m_commandListInventorySlotRef[selected] >= 0;
	} else if (itemIndex == 1) {
		int combo[5][2];
		active = ChkUnite(selected, combo) > 0;
	} else {
		s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const int index = itemIndex - 1;
		if ((index >= 0) && (index < list[0])) {
			active = EquipChk(static_cast<int>(list[index])) != 0;
		}
	}

	cmd->commandResult = static_cast<s8>(active != 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */

int CMenuPcs::ChkUnite(int selected, int (*comboOut)[2])
{
	u8* self = reinterpret_cast<u8*>(this);
	const CCaravanWork* const caravan = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);

	int itemKinds[10];
	int matches[10];
	int candidates[10];
	int ok;
	int k;

	if (comboOut != nullptr) {
		for (int i = 0; i < 5; i++) {
			comboOut[i][0] = -1;
			comboOut[i][1] = -1;
		}
	}

	const s16 selectedState = caravan->m_commandListExtra[selected];
	const s32 selectedFlag =
	    (static_cast<u32>(-selectedState) & ~static_cast<u32>(selectedState)) >> 31;

	if ((GetCmdStateView(this)->mode == 1) && (GetCmdStateView(this)->phase == 2)) {
		if (selectedState < 0) {
			selected--;
		}
		if (caravan->m_commandListExtra[selected] < 0) {
			selected--;
		}
	}

	memset(candidates, 0xff, sizeof(candidates));

	int write = 2;
	for (int slot = 2; slot < 8; slot++, write++) {
		if (slot == selected) {
			if (caravan->m_commandListExtra[slot] == 0) {
				candidates[write] = 0;
			} else {
				candidates[write] = 0;
				write++;
				candidates[write] = 0;
				slot++;
				if (caravan->m_commandListExtra[slot + 1] < 0) {
					write++;
					candidates[write] = 0;
					slot++;
				}
			}
		} else {
			const s32 v = caravan->m_commandListExtra[slot];
			candidates[write] = (-v | v) >> 31;
		}
	}

	memset(itemKinds, 0xff, sizeof(itemKinds));

	int index = 2;
	for (int slot = 2; slot < 8; slot++, index++) {
		if (caravan->m_numCmdListSlots <= slot) {
			break;
		}
		const int itemRef = caravan->m_commandListInventorySlotRef[slot];
		if (itemRef < 0) {
			continue;
		}

		const int itemId = caravan->m_inventoryItems[itemRef];
		const int icon = GetItemIcon(itemId);

		if (IsMagicArti(itemId)) {
			if (itemId == 0xdf) {
				itemKinds[index] = 0x100;
			} else if (itemId == 0xe0) {
				itemKinds[index] = 0x101;
			} else if (itemId == 0xe1) {
				itemKinds[index] = 0x102;
			} else if (itemId == 0xe2) {
				itemKinds[index] = 0x105;
			} else {
				itemKinds[index] = 0x107;
			}
		} else if (icon == 0) {
			goto setFood;
		} else if (icon == 1) {
			goto setFood;
		} else if (icon == 2) {
			goto setFood;
		} else if (icon == 3) {
		setFood:
			itemKinds[index] = 999;
		} else if (icon == 0x10) {
			goto setItem;
		} else if (icon == 0x11) {
		setItem:
			itemKinds[index] = itemId;
		} else {
			itemKinds[index] = -1;
		}
	}

	int matchCount;
	if (itemKinds[selected] <= 0) {
		return 0;
	}

	matchCount = 0;
	memset(matches, 0xff, sizeof(matches));
	int* mp = matches;
	int w = 0;

	if ((itemKinds[selected] == 999) && (selected > 2)) {
		int patIdx = 0;
		for (const s16* pat = s_uniteRecipePatterns; pat[1] >= 0; pat += 6, patIdx++) {
			if (pat[0] == 0) {
				continue;
			}
			const int len1 = pat[2];
			if ((len1 == 2) && (selectedFlag != 0)) {
				continue;
			}
			ok = 0;
			k = 0;
			for (const s16* q = &pat[3 + ok]; k < len1 - 1; k++, q++) {
				const int slot = selected - (len1 - 1 - k);
				int __p5 = slot;
				if (candidates[__p5] != 0) {
					break;
				}
				if (*q == itemKinds[slot]) {
					ok++;
				}
			}
			if (len1 == ok - 1) {
				mp[0] = patIdx;
				matchCount++;
				*reinterpret_cast<int*>(reinterpret_cast<u8*>(matches) + w + 4) = selected - (len1 - 1);
				mp += 2;
				w += 8;
			}
		}
	} else if (selectedFlag == 0) {
		const int baseLen = static_cast<int>(s_uniteRecipePatterns[2]);
		int start = selected - (baseLen - 1);
		for (int i = 0; i < baseLen; i++, start++) {
			ok = 0;
			k = 0;
			for (const s16* q = &s_uniteRecipePatterns[3 + ok]; k < baseLen; k++, q++) {
				const int slot = i + (selected - ((baseLen - 1) - k));
				if (candidates[slot] != 0) {
					break;
				}
				if (*q == itemKinds[slot]) {
					ok++;
				}
			}
			if (ok == baseLen) {
				mp[0] = 0;
				matchCount++;
				*reinterpret_cast<int*>(reinterpret_cast<u8*>(matches) + w + 4) = start;
				mp += 2;
				w += 8;
			}
		}
	}

	mp = &matches[matchCount * 2];
	w = matchCount * 8;
	int group = 1;
	for (const s16* pat = s_uniteRecipePatterns + 6; pat[1] >= 0; pat += 6, group++) {
		if (((pat[0] != 0) && (itemKinds[selected] == 999) && (selected > 2)) ||
		    ((pat[2] == 2) && (selectedFlag != 0))) {
			continue;
		}

		const int len =  (s32)(static_cast<int>(pat[2]));
		for (int start = 0; start < len; start++) {
			if ((start == 0) && (selectedFlag != 0)) {
				start++;
			}

			ok = 0;
			k = 0;
			for (const s16* q = &pat[3 + ok]; k < len; k++, q++) {
				const int slot = start + (selected - ((len - 1) - k));
				if (candidates[slot] != 0) {
					break;
				}
				if (*q == itemKinds[slot]) {
					ok++;
				}
			}

			if (ok == len) {
				mp[0] = group;
				matchCount++;
				*reinterpret_cast<int*>(reinterpret_cast<u8*>(matches) + w + 4) = start + (selected - (len - 1));
				mp += 2;
				w += 8;
			}
		}
	}

	int (*out)[2] = comboOut;
	for (int rank = 0; rank < 2; rank++) {
		for (int i = 0; i < matchCount; i++) {
			const int* m = &matches[i * 2];
			if (rank + 2 == s_uniteRecipePatterns[2 + m[0] * 6]) {
				out[0][0] = m[0];
				out++;
				out[-1][1] = m[1];
			}
		}
	}

	return matchCount;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdUnite(int selected, int comboIndex)
{
	int combo[5][2];
	const int comboCount = ChkUnite(selected, combo);
	if ((comboIndex < 0) || (comboIndex >= comboCount) || (combo[comboIndex][1] < 0)) {
		return;
	}

	const int recipe = combo[comboIndex][0];
	reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->UniteComList(
		combo[comboIndex][1], GetUniteRecipeCount(recipe), GetUniteRecipeCmd(recipe));
	GetCmdStateView(this)->selected = static_cast<s16>(combo[comboIndex][1]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdDismantle(int selected)
{
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	int count = 1;
	if (caravanWork->m_commandListExtra[selected + 1] < 0) {
		count = 2;
		if (caravanWork->m_commandListExtra[selected + 2] < 0) {
			count = 3;
		}
	}

	caravanWork->UnuniteComList(selected, count);
}

/*
 * --INFO--
 * PAL Address: 0x8014ba20
 * PAL Size: 3228b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawUniteList()
{
	const CCaravanWork* const caravan = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	s32 i;
	s32 active;
	s32 groupSize;
	s32 groupStart;
	float drawY;
	float drawW;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	CmdListEntry* unitePanels = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd];
	const s32 topX = GetCmdListStorage(this)->entries[0].x;
	s_unitePanelCount = 0;
	active = 0;

	for (i = 0; i < 8; i++) {
		if (i == GetCmdStateView(this)->selected) {
			active = 1;
		} else if (caravan->m_commandListExtra[i] >= 0) {
			active = 0;
		}

		if (i >= caravan->m_numCmdListSlots) {
			break;
		}

		if (caravan->m_commandListExtra[i] == 0) {
			continue;
		}

		CmdListEntry* const entry = &GetCmdListStorage(this)->entries[i];
		const float rectX = static_cast<float>(entry->x + 4);
		drawY = static_cast<float>(entry->y);
		drawW = static_cast<float>(entry->width - 8);
		const float rectU = static_cast<float>(entry->u);
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<s8>(kCmdMenuAlphaMax * entry->alpha);
		GXSetChanMatColor((_GXChannelID)4, color);

		if (caravan->m_commandListExtra[i] > 0) {
			groupStart = i;
			if (i + 2 < 8) {
				if (caravan->m_commandListExtra[i + 2] == -1) {
					groupSize = 3;
				} else {
					groupSize = 2;
				}
			} else {
				groupSize = 2;
			}

			if ((i <= GetCmdStateView(this)->selected) && (GetCmdStateView(this)->selected < i + groupSize)) {
				if ((GetCmdStateView(this)->phase == 3) && (i != GetCmdStateView(this)->selected)) {
					GetCmdStateView(this)->selected = static_cast<s16>(i);
				}
				active = 1;
			}
		}

		s32 barTex = 0x35;
		if (groupSize == 2) {
			barTex = 0x36;
		}
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(barTex));
		MenuPcs.DrawRect(0,
			rectX,
			drawY - kCmdMenuSmallOffset,
			drawW,
			kCmdMenuUniteBarHeight,
			rectU,
			active ? kCmdMenuUniteBarHeight : kCmdMenuZero,
			kCmdMenuOne,
			kCmdMenuOne,
			kCmdMenuZero);
	}

	CFont* font = m_fonts[0];
	font->SetMargin(kCmdMenuOne);
	font->SetShadow(1);
	font->SetScale(kCmdMenuTextScale);
	font->DrawInit();
	font->SetTlut(7);

	CmdListEntry* entry = GetCmdListStorage(this)->entries;
	for (i = 0; i < caravan->m_numCmdListSlots; i++, entry++) {
		if ((i < 8) && (caravan->m_commandListExtra[i] == 0)) {
			continue;
		}

		const float alpha = (GetCmdStateView(this)->mode == 3) ? kCmdMenuOne : entry->alpha;
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(kCmdMenuAlphaMax * alpha)).color);

		const char* text;
		if (i < 2) {
			text = GetMenuStr(i + 9);
		} else {
			const s32 itemIdx = caravan->m_commandListInventorySlotRef[i];
			if (itemIdx < 0) {
				continue;
			}
			const s32 skillId = caravan->m_inventoryItems[itemIdx];
			char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
			int __p9 = skillId;
			text = flatText[__p9 * 5 + 4];
		}

		const float width = static_cast<float>(font->GetWidth(text));
		float x = static_cast<float>((static_cast<float>(entry->width) - width) * kCmdMenuHalfD +
		                             static_cast<double>(entry->x));
		if (topX != entry->x) {
			const float t = static_cast<float>(fabs(static_cast<double>(topX - entry->x)) * kCmdMenuUniteAlphaScaleD);
			const float target = static_cast<float>(entry->x + entry->width - 0x18) - width;
			x = (target - x) * t + x;
		}

		drawY = static_cast<float>(entry->y + 3);
		font->SetPosX(x);
		font->SetPosY(drawY - kCmdMenuTextYOffset);
		font->Draw(text);
	}

	DrawInit();
	for (i = 0; i < 8; i++) {
		if (i == GetCmdStateView(this)->selected) {
			active = 1;
		} else if (caravan->m_commandListExtra[i] >= 0) {
			active = 0;
		}

		if (i >= caravan->m_numCmdListSlots) {
			break;
		}

		const s16 slotType = caravan->m_commandListExtra[i];
		if (slotType == 0) {
			continue;
		}

		if (slotType > 0) {
			groupStart = i;
			if (i + 2 < 8) {
				if (caravan->m_commandListExtra[i + 2] == -1) {
					groupSize = 3;
				} else {
					groupSize = 2;
				}
			} else {
				groupSize = 2;
			}

			if ((i <= GetCmdStateView(this)->selected) && (GetCmdStateView(this)->selected < i + groupSize)) {
				active = 1;
			}
		}

		if (i != groupStart + groupSize - 1) {
			continue;
		}

		CmdListEntry* const endEntry = &GetCmdListStorage(this)->entries[i];
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x38));

		const s32 labelAnchor =
		    (!(groupStart == GetCmdStateView(this)->selected)) ? groupStart : groupStart + 1;
		const float panelX =
		    static_cast<float>(topX - (GetCmdListStorage(this)->entries[labelAnchor].x - topX));
		drawW = kCmdMenuUnitePanelWidth;
		const float panelTone = active ? kCmdMenuPanelSize64 : kCmdMenuZero;
		CmdListEntry* const startEntry = &GetCmdListStorage(this)->entries[groupStart];
		drawY = static_cast<float>(
		    (static_cast<float>(endEntry->y + endEntry->height - startEntry->y) - kCmdMenuPanelSize64) *
		        kCmdMenuHalfD +
		    static_cast<double>(startEntry->y));
		float panelAlpha;
		if (GetCmdStateView(this)->mode == 3) {
			panelAlpha = startEntry->alpha;
		} else {
			panelAlpha = static_cast<float>(
			    fabs(static_cast<double>(panelX - static_cast<float>(topX))) * kCmdMenuUniteAlphaScaleD);
		}

		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<u8>(kCmdMenuAlphaMax * panelAlpha);
		GXSetChanMatColor((_GXChannelID)4, color);

		unitePanels[s_unitePanelCount].x = static_cast<u16>(panelX);
		unitePanels[s_unitePanelCount].y = static_cast<s16>(drawY);
		unitePanels[s_unitePanelCount].width = static_cast<s16>(kCmdMenuUnitePanelWidth);
		unitePanels[s_unitePanelCount].height = static_cast<s16>(kCmdMenuPanelSize64);
		unitePanels[s_unitePanelCount].u = kCmdMenuZero;
		unitePanels[s_unitePanelCount].v = panelTone;
		unitePanels[s_unitePanelCount].alpha = panelAlpha;
		s_UniteTop[s_unitePanelCount] = groupStart;
		s_unitePanelCount++;

		MenuPcs.DrawRect(0,
			panelX,
			drawY - kCmdMenuPanelInset,
			kCmdMenuUnitePanelWidth,
			kCmdMenuPanelSize64,
			kCmdMenuZero,
			panelTone,
			kCmdMenuOne,
			kCmdMenuOne,
			kCmdMenuZero);
	}

	font = m_fonts[0];
	font->SetMargin(kCmdMenuOne);
	font->SetShadow(1);
	font->SetScale(kCmdMenuOne);
	font->DrawInit();
	font->SetTlut(6);

	for (i = 0; i < s_unitePanelCount; i++, unitePanels++) {
		const float alpha = (GetCmdStateView(this)->mode == 3) ? kCmdMenuOne : unitePanels->alpha;
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(kCmdMenuAlphaMax * alpha)).color);

		const int itemId = caravan->m_commandListExtra[s_UniteTop[i]];
		const char* text = GetStrikeListName(itemId);
		const float width = static_cast<float>(font->GetWidth(text));
		drawY = static_cast<float>(
		    (static_cast<double>(unitePanels->height) - kCmdMenuTextLineHeightD) * kCmdMenuHalfD +
		    static_cast<double>(unitePanels->y) - kCmdMenuTextBaselineOffsetD);
		font->SetPosX(static_cast<float>((static_cast<float>(unitePanels->width) - width) * kCmdMenuHalfD +
		                                 static_cast<double>(unitePanels->x)));
		font->SetPosY(drawY - kCmdMenuTextYOffset);
		font->Draw(text);
	}

	DrawInit();
	if (GetCmdStateView(this)->mode == 0) {
		const s16 helpSlot = caravan->m_commandListExtra[GetCmdStateView(this)->selected];
		if (helpSlot != 0) {
			int helpId =  (helpSlot + 0);
			const u8 helpAlpha =
			    static_cast<u8>(kCmdMenuAlphaMax * GetCmdListStorage(this)->entries[0].alpha);
			if (helpSlot == 0x207 || helpSlot == 0x20B || helpSlot == 0x20F) {
				helpId += 2;
			}

			CFont* const helpFont = m_fonts[0];
			DrawHelpMessage(
				helpId, helpFont,
				static_cast<int>(-(drawW * kCmdMenuHalf - kCmdMenuScreenHalfWidth)),
				static_cast<int>(drawY),
				CColor(0xFF, 0xFF, 0xFF, helpAlpha).color, 10,
				kCmdMenuOne, kCmdMenuThree);
		}
	}
}

#pragma push
#pragma peephole off
#pragma opt_loop_invariants off
#pragma opt_propagation off
/*
 * --INFO--
 * PAL Address: 0x8014b7ec
 * PAL Size: 564b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::UniteOpenAnim(int topIdx)
{
	int finished;
	float targetX;

	if (s_unitePanelCount == 0) {
		return 1;
	}

	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	float baseX = static_cast<float>(GetCmdListEntries(this)[0].x);

	if (topIdx > 0) {
		for (int i = 0; i < 3; i++) {
			int idx = i + s_UniteTop[topIdx];
			CmdListEntry* entry = &GetCmdListStorage(this)->entries[idx];
			if ((i != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
				break;
			}

			entry->x = static_cast<s16>(static_cast<double>(entry->x) + kCmdMenuUniteSlideStepD);
			if (fabs(static_cast<double>(static_cast<float>(entry->x) - baseX)) >
			    kCmdMenuUniteSlideLimitD) {
				entry->x = static_cast<s16>(kCmdMenuPanelSize64 + baseX);
				return 1;
			}
		}
	} else {
		finished = 0;
		targetX = kCmdMenuPanelSize64 + baseX;
		s32* top = &s_UniteTop[finished];
		for (int i = 0; i < s_unitePanelCount; i++) {
			for (int j = 0; j < 3; j++) {
				int idx = j + *top;
				CmdListEntry* entry = &GetCmdListStorage(this)->entries[idx];
				if ((j != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
					break;
				}

				entry->x = static_cast<s16>(static_cast<double>(entry->x) + kCmdMenuUniteSlideStepD);
				if (fabs(static_cast<double>(static_cast<float>(entry->x) - baseX)) >
				    kCmdMenuUniteSlideLimitD) {
					entry->x = static_cast<s16>(targetX);
					if (j == 0) {
						finished++;
					}
				}
			}
			top++;
		}
		if (finished == s_unitePanelCount) {
			return 1;
		}
	}

	return 0;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8014b5cc
 * PAL Size: 544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::UniteCloseAnim(int topIdx)
{
	if (s_unitePanelCount == 0) {
		return 1;
	}

	float baseX = static_cast<float>(GetCmdListEntries(this)[0].x);
	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);

	if (topIdx >= 0) {
		int finished = 0;
		for (int i = 0; i < 3; i++) {
			int idx = i + s_UniteTop[topIdx];
			CmdListEntry* entry = &GetCmdListStorage(this)->entries[idx];
			if ((i != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
				break;
			}

			entry->x = static_cast<s16>(static_cast<double>(entry->x) - kCmdMenuUniteSlideStepD);
			if (static_cast<float>(entry->x) <= baseX) {
				finished = 1;
				entry->x = static_cast<s16>(baseX);
			}
		}
		if (finished != 0) {
			return 1;
		}
	} else {
		int finished = 0;
		s32* top = &s_UniteTop[finished];
		for (int i = 0; i < s_unitePanelCount; i++) {
			for (int j = 0; j < 3; j++) {
				int idx = j + *top;
				CmdListEntry* entry = &GetCmdListStorage(this)->entries[idx];
				if ((j != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
					break;
				}

				entry->x = static_cast<s16>(static_cast<double>(entry->x) - kCmdMenuUniteSlideStepD);
				if (static_cast<float>(entry->x) <= baseX) {
					entry->x = static_cast<s16>(baseX);
					if (j == 0) {
						finished++;
					}
				}
			}
			top++;
		}
		if (finished == s_unitePanelCount) {
			return 1;
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014b244
 * PAL Size: 904b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdOpen1()
{
	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	s32 i;
	s32 slot;

	GetCmdStateView(this)->transitionTimer = static_cast<s16>(GetCmdStateView(this)->transitionTimer + 1);

	const s32 selected = static_cast<s32>(GetCmdStateView(this)->selected);

	for (i = 0; i < 3; i++) {
		if ((i != 0) && (caravanWork->m_commandListExtra[selected + i] != -1)) {
			break;
		}
		*reinterpret_cast<f32*>(reinterpret_cast<u8*>(GetCmdList(this)) + (selected + i) * 0x40 + 0x18) = static_cast<f32>(
			-((kCmdMenuTransitionStepD * static_cast<f64>(GetCmdStateView(this)->transitionTimer)) - kCmdMenuOneD)
		);
	}
	s32 chainCount = i;

	CmdListEntry* const animEntry = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd + 3];

	for (slot = 0; slot < 3; slot++) {
		if (selected == s_UniteTop[slot]) {
			break;
		}
	}

	CmdListEntry* const baseEntry = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd + slot];

	if (static_cast<s8>(GetCmdStateView(this)->unitePanelInitialized) == 0) {
		const s32 endX = static_cast<s32>(static_cast<f64>(baseEntry->x + baseEntry->width) - kCmdMenuPanelRightInsetD);
		animEntry->x = static_cast<s16>(endX);

		if (chainCount == 2) {
			int combo[5][2];
			chainCount = ChkUnite(static_cast<int>(GetCmdStateView(this)->selected), combo);
		} else {
			chainCount = 0;
		}

		animEntry->scale = static_cast<f32>((chainCount != 0) ? kCmdMenuUnitePanelScaleD : kCmdMenuOneD);
		animEntry->width = 0xC0;
		animEntry->height = 0x40;
		animEntry->y = static_cast<s16>(((-((static_cast<f32>(animEntry->height) * animEntry->scale) -
		                                    static_cast<f32>(baseEntry->height)) *
		                                   kCmdMenuHalfD) +
		                                  static_cast<f64>(baseEntry->y)) -
		                                 kCmdMenuUnitePanelYOffsetD);
		animEntry->u = kCmdMenuZero;
		animEntry->v = kCmdMenuZero;
		animEntry->tex = 0x39;
		GetCmdStateView(this)->unitePanelInitialized = 1;
	}

	animEntry->alpha = static_cast<f32>(kCmdMenuTransitionStepD * static_cast<f64>(GetCmdStateView(this)->transitionTimer));
	u32 done = (static_cast<f64>(GetCmdStateView(this)->transitionTimer) >= kCmdMenuTransitionFramesD) ? 1 : 0;
	int __p5 =   (int)(unsigned int)((done + 0));
	if (__p5 != 0) {
		GetCmdStateView(this)->choice = 0;
	}

	return done;
}

/*
 * --INFO--
 * PAL Address: 0x8014ad90
 * PAL Size: 1204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose1()
{
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

	GetCmdStateView(this)->transitionTimer = static_cast<s16>(GetCmdStateView(this)->transitionTimer + 1);
	s16 state = GetCmdStateView(this)->uniteState;
	s32 done;
	int combo[5][2];

	if (state == 0) {
		const s32 selected = GetCmdStateView(this)->selected;
		s32 i;
		for (i = 0; i < 3; i++) {
			if ((i != 0) && (caravanWork->m_commandListExtra[selected + i] != -1)) {
				break;
			}
			*reinterpret_cast<f32*>(reinterpret_cast<u8*>(GetCmdList(this)) + (selected + i) * 0x40 + 0x18) =
				static_cast<float>(kCmdMenuTransitionStepD * static_cast<f64>(GetCmdStateView(this)->transitionTimer));
		}

		CmdListEntry* const animEntry = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd + 3];
		animEntry->alpha =
			static_cast<float>(-(kCmdMenuTransitionStepD * static_cast<f64>(GetCmdStateView(this)->transitionTimer) - kCmdMenuOneD));
		const s32 nextState = (kCmdMenuOneD == static_cast<f64>(animEntry->scale)) ? 2 : 3;

		done = (static_cast<f64>(GetCmdStateView(this)->transitionTimer) >= kCmdMenuTransitionFramesD) ? 1 : 0;
		if ((done != 0) && (GetCmdStateView(this)->commandResult > 0)) {
			GetCmdStateView(this)->commandResult = 0;
			const s16 choice = GetCmdStateView(this)->choice;
			if (choice == 0) {
				GetCmdStateView(this)->uniteState = 1;
				done = 0;
			} else if ((nextState == 3) && (choice == 1)) {
				GetCmdStateView(this)->uniteState = 2;
				done = 0;
			}
		}
		if (done != 0) {
			GetCmdStateView(this)->commandResult = 0;
		}
	} else if (state == 1) {
		const s32 selected = GetCmdStateView(this)->selected;
		s32 uniteIdx = 0;
		s32 topCount = s_unitePanelCount;
		for (; uniteIdx < topCount; uniteIdx++) {
			if (s_UniteTop[uniteIdx] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx));
		if (done != 0) {
			CCaravanWork* const cw = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
			s32 ununiteCount;
			for (ununiteCount = 0; ununiteCount < 3; ununiteCount++) {
				if ((ununiteCount != 0) && (cw->m_commandListExtra[selected + ununiteCount] != -1)) {
					break;
				}
			}
			cw->UnuniteComList(selected, ununiteCount);
		}
	} else if (state == 2) {
		const s16 selected = GetCmdStateView(this)->selected;
		const s32 count = ChkUnite(static_cast<int>(selected), combo);
		if (count == 1) {
			done = 0;
			GetCmdStateView(this)->uniteState = 3;
		} else {
			done = 1;
			GetCmdStateView(this)->commandResult = 1;
		}
	} else if (state == 3) {
		const s16 selected = GetCmdStateView(this)->selected;
		s32 uniteIdx = 0;
		s32 topCount = s_unitePanelCount;
		for (; uniteIdx < topCount; uniteIdx++) {
			if (s_UniteTop[uniteIdx] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx));
		if (done != 0) {
			ChkUnite(static_cast<int>(selected), combo);

			CCaravanWork* const cw = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
			const s32 sel = GetCmdStateView(this)->selected;
			s32 ununiteCount;
			for (ununiteCount = 0; ununiteCount < 3; ununiteCount++) {
				if ((ununiteCount != 0) && (cw->m_commandListExtra[sel + ununiteCount] != -1)) {
					break;
				}
			}

			cw->UnuniteComList(sel, ununiteCount);
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])
			    ->UniteComList(combo[0][1], GetUniteRecipeCount(combo[0][0]), GetUniteRecipeCmd(combo[0][0]));

			done = 0;
			GetCmdStateView(this)->selected = static_cast<s16>(combo[0][1]);
			GetCmdStateView(this)->uniteState = 4;
		}
	} else if (state == 4) {
		done = static_cast<u32>(UniteOpenAnim(-1));
	}

	return done;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmdOpen2()
{
	CmdState* cmd = GetCmdStateView(this);
	CmdListStorage* list = GetCmdListStorage(this);
	cmd->transitionTimer = static_cast<s16>(cmd->transitionTimer + 1);

	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	s32 selected = static_cast<s32>(cmd->selected);
	s32 prev = selected - 1;
	for (; prev > 2; --prev) {
		if (caravanWork->m_commandListExtra[prev] >= 0) {
			break;
		}
	}

	s32 next = selected + 1;
	const s32 limit = static_cast<s32>(caravanWork->m_numCmdListSlots);
	for (; next < limit; ++next) {
		if (caravanWork->m_commandListExtra[next] >= 0) {
			break;
		}
	}

	const double timer = static_cast<double>(static_cast<s32>(cmd->transitionTimer));
	const float minAnim = static_cast<float>(kCmdMenuHalfD);
	const float anim = static_cast<float>(-((kCmdMenuAlphaStepD * timer) - kCmdMenuOneD));
	for (s32 i = 0; i < static_cast<s32>(list->count); i++) {
		if ((i < prev) || (next < i)) {
			float value = anim;
			if (static_cast<double>(value) < static_cast<double>(minAnim)) {
				value = kCmdMenuHalf;
			}
			list->entries[i].alpha = value;
		}
	}

	if (static_cast<double>(static_cast<s32>(cmd->transitionTimer)) >= kCmdMenuTransitionFramesD) {
		cmd->uniteSelected = static_cast<s16>(prev);
		cmd->phase = static_cast<s16>(cmd->phase + 1);
	}
}

#pragma push
#pragma opt_strength_reduction off
/*
 * --INFO--
 * PAL Address: 0x8014a9dc
 * PAL Size: 948b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::CmdClose2()
{
	u8* self = reinterpret_cast<u8*>(this);
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	int combo[5][2];

	const s32 selected = static_cast<s32>(GetCmdStateView(this)->selected);
	const u32 modeSel = static_cast<s32>(GetCmdStateSelections(GetCmdStateView(this))[GetCmdStateView(this)->mode]);

	GetCmdStateView(this)->transitionTimer = static_cast<s16>(GetCmdStateView(this)->transitionTimer + 1);

	if (GetCmdStateView(this)->uniteState == 0) {
		GetCmdStateView(this)->transitionTimer = 0;
		if (GetCmdStateView(this)->commandResult < 0) {
			GetCmdStateView(this)->uniteState = 3;
		} else if (caravanWork->m_commandListExtra[selected] != 0) {
			GetCmdStateView(this)->uniteState = 1;
		} else {
			GetCmdStateView(this)->uniteState = 2;
		}
		return 0;
	} else if (GetCmdStateView(this)->uniteState == 1) {
		s32 uniteIdx = 0;
		for (s32* p = s_UniteTop; uniteIdx < s_unitePanelCount; p++, uniteIdx++) {
			if (selected == *p) {
				break;
			}
		}

		if (UniteCloseAnim(uniteIdx) != 0) {
			ChkUnite(selected, combo);
			int* comboSel = &combo[0][1];

			s32 comboIdx = 0;
			if (comboSel[0] < comboSel[2]) {
				comboIdx = (modeSel == static_cast<u32>(comboSel[0])) ? 0 : 1;
			} else {
				comboIdx = (modeSel == static_cast<u32>(comboSel[2])) ? 1 : 0;
			}

			const s32 closeSel = GetCmdStateView(this)->selected;
			s32 ununiteCount = 0;
			for (ununiteCount = 0; ununiteCount < 3; ununiteCount++) {
				if ((ununiteCount != 0) &&
				    (reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])
				         ->m_commandListExtra[closeSel + ununiteCount] != -1)) {
					break;
				}
			}

			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])
			    ->UnuniteComList(closeSel, ununiteCount);
			const s16 uniteCount = GetUniteRecipeCount(combo[comboIdx][0]);
			const s16 uniteCmd = GetUniteRecipeCmd(combo[comboIdx][0]);
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->UniteComList(
			    comboSel[comboIdx * 2], uniteCount, uniteCmd);
			GetCmdStateView(this)->selected = static_cast<s16>(comboSel[comboIdx * 2]);
			GetCmdStateView(this)->uniteState = 2;
		}
		return 0;
	} else if (GetCmdStateView(this)->uniteState == 2) {
		if (caravanWork->m_commandListExtra[selected] == 0) {
			ChkUnite(selected, combo);

			s32 comboIdx = 0;
			if (combo[0][1] < combo[1][1]) {
				comboIdx = (modeSel == static_cast<u32>(combo[0][1])) ? 0 : 1;
			} else {
				comboIdx = (!(modeSel == static_cast<u32>(combo[1][1]))) ? 0 : 1;
			}

			const s16 uniteCount = GetUniteRecipeCount(combo[comboIdx][0]);
			int __p6 = comboIdx;
			const s16 uniteCmd = GetUniteRecipeCmd(combo[__p6][0]);
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->UniteComList(
				combo[comboIdx][1], uniteCount, uniteCmd);
			int __p5 = comboIdx;
			GetCmdStateView(this)->selected = static_cast<s16>(combo[__p5][1]);
		} else if (UniteOpenAnim(-1) != 0) {
			GetCmdStateView(this)->uniteState = 3;
		}
		return 0;
	} else if (GetCmdStateView(this)->uniteState == 3) {
		for (s32 i = 0; i < static_cast<s32>(GetCmdListStorage(this)->count); i++) {
			int __p7 = i;
			CmdListEntry* entry = &GetCmdListStorage(this)->entries[__p7];
			if (static_cast<f64>(entry->alpha) >= kCmdMenuOneD) {
				continue;
			}
			entry->alpha = static_cast<f32>((kCmdMenuAlphaStepD * static_cast<f64>(GetCmdStateView(this)->transitionTimer)) + kCmdMenuHalfD);
			if (static_cast<f64>(entry->alpha) > kCmdMenuOneD) {
				entry->alpha = kCmdMenuOne;
			}
		}
		if (static_cast<f64>(GetCmdStateView(this)->transitionTimer) >= kCmdMenuTransitionFramesD) {
			return 1;
		}
		return 0;
	}
	return 0;
}
#pragma pop

/*
 * --INFO--
 * PAL Address: 0x8016233c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
const char* CMenuPcs::GetSkillStr(int index)
{
	const int languageId = Game.m_gameWork.m_languageId;

	if (languageId == 3) {
		goto language_3;
	}
	if (languageId >= 3) {
		goto language_ge_3;
	}
	if (languageId == 1) {
		goto language_default;
	}
	if (languageId >= 1) {
		goto language_2;
	}
	goto language_default;

language_ge_3:
	if (languageId == 5) {
		goto language_5;
	}
	if (languageId >= 5) {
		goto language_default;
	}
	goto language_4;

language_2:
	return s_SkillStr_ge[index];
language_3:
	return s_SkillStr_it[index];
language_4:
	return s_SkillStr_fr[index];
language_5:
	return s_SkillStr_sp[index];
language_default:
	return s_SkillStr_us[index];
}

extern "C" const char* s_SkillStr_us[] = {
    s_Flamestrike_801DEA6C,
    s_Icestrike_801DEA78,
    s_Thunderstrike_801DEA84,
    sEmptySkillName,
    sEmptySkillName,
};

extern "C" const char* s_SkillStr_ge[] = {
    s_Feuer_Hieb_801DEA94,
    s_Eis_Hieb_801DEAA0,
    s_Blitz_Hieb_801DEAAC,
    sEmptySkillName,
    sEmptySkillName,
};

extern "C" const char* s_SkillStr_it[] = {
    s_Colpo_Fire_801DEAB8,
    s_Colpo_Blizzard_801DEAC4,
    s_Colpo_Thunder_801DEAD4,
    sEmptySkillName,
    sEmptySkillName,
};

extern "C" const char* s_SkillStr_fr[] = {
    s_Pyro_Frappe_801DEAE4,
    s_Cryo_Frappe_801DEAF0,
    s_Rheo_Frappe_801DEAFC,
    sEmptySkillName,
    sEmptySkillName,
};

extern "C" const char* s_SkillStr_sp[] = {
    s_Efecto_Fuego_801DEB08,
    s_Efecto_Hielo_801DEB18,
    s_Efecto_Electro_801DEB28,
    sEmptySkillName,
    sEmptySkillName,
};

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetFontItem()
{
	return;
}
