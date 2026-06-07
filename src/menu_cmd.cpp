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

static const char* GetLocalizedStrikeName(int itemId)
{
	int idx = -1;
	if (itemId == 0x207) {
		idx = 0;
	} else if (itemId == 0x20B) {
		idx = 1;
	} else if (itemId == 0x20F) {
		idx = 2;
	} else if (itemId == 0x222) {
		idx = 3;
	} else if (itemId == 0x227) {
		idx = 4;
	}

	if (idx < 0) {
		return 0;
	}

	const char** names = s_SkillStr_us;
	switch (Game.m_gameWork.m_languageId) {
	case 2:
		names = s_SkillStr_ge;
		break;
	case 3:
		names = s_SkillStr_it;
		break;
	case 4:
		names = s_SkillStr_fr;
		break;
	case 5:
		names = s_SkillStr_sp;
		break;
	default:
		break;
	}

	return names[idx];
}

static const char* GetUniteListName(int itemId)
{
	const char* localized = GetLocalizedStrikeName(itemId);
	if (localized != 0 && localized[0] != '\0') {
		return localized;
	}

	char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
	return flatText[itemId * 5 + 4];
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
	u8 initialized;
	u8 unitePanelInitialized;
	unsigned char pad_000D[0x10 - 0x0D];
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
	s16 prevMode;
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
	return (0xde < itemId) && (itemId < 0xe4);
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
	int iVar5 = 0;
	iVar8 = 8;
	float fVar3 = kCmdMenuZero;
	float fVar4 = kCmdMenuSmallOffset;
	do {
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

		if ((1 < iVar5) && (caravanWork->m_commandListInventorySlotRef[iVar5] < 0)) {
			entry->v += static_cast<float>(static_cast<double>(entry->height));
		}

		entry->startFrame = iVar5;
		iVar5++;
		entry->duration = 3;
		entry++;
		iVar8--;
	} while (iVar8 != 0);

	GetCmdListStorage(this)->count = 8;
	CmdInit1();
	GetCmdItem();
	CmdState* cmd = GetCmdStateView(this);
	cmd->selected = 2;
	cmd->initialized = 1;
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
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;
	const s32 start = static_cast<s32>(list->count);
	CmdListEntry* basePanel = &entries[start];

	basePanel->tex = 0x2e;
	basePanel->x = 0xb8;
	basePanel->y = 0x28;
	basePanel->width = 0x78;
	basePanel->height = 0x108;
	basePanel->u = kCmdMenuBasePanelU;
	basePanel->v = kCmdMenuSmallOffset;
	basePanel->scale = kCmdMenuOne;
	basePanel->startFrame = 5;
	basePanel->duration = 5;

	u32 tex = 0x2f;
	if (GetCmdLayoutFlag(this) == 0) {
		tex = 0x46;
	}

	CmdListEntry* leftIcon = &entries[start + 1];
	leftIcon->tex = tex;
	leftIcon->x = 0xa0;
	leftIcon->y = 0xe;
	leftIcon->width = 0x30;
	leftIcon->height = 0x30;
	leftIcon->u = kCmdMenuZero;
	leftIcon->v = kCmdMenuZero;
	leftIcon->scale = kCmdMenuOne;
	leftIcon->startFrame = 0;
	leftIcon->duration = 5;

	CmdListEntry* rightIcon = &entries[start + 2];
	rightIcon->tex = tex;
	rightIcon->width = 0x30;
	rightIcon->height = 0x30;
	rightIcon->x = 0xa5;
	rightIcon->y = static_cast<s16>(0x150 - rightIcon->height);
	rightIcon->u = kCmdMenuZero;
	rightIcon->v = kCmdMenuZero;
	rightIcon->scale = kCmdMenuThreeQuarter;
	rightIcon->startFrame = 0;
	rightIcon->duration = 5;

	CmdListEntry* choicePanel = &entries[start + 3];
	choicePanel->flags = 2;
	choicePanel->tex = 0x2e;
	choicePanel->x = 0xa0;
	choicePanel->y = 8;
	choicePanel->width = 0x48;
	choicePanel->height = 0x140;
	choicePanel->u = kCmdMenuZero;
	choicePanel->v = kCmdMenuZero;
	choicePanel->startFrame = 0;
	choicePanel->duration = 5;

	s16 y = 0;
	for (s32 i = 0; i < 4; i++) {
		CmdListEntry* entry = &entries[start + 4 + i * 2];
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

		entry = &entries[start + 5 + i * 2];
		entry->flags = 2;
		entry->tex = 0x37;
		entry->x = static_cast<s16>(basePanel->x + 0x24);
		entry->y = static_cast<s16>(basePanel->y + y + 0x20);
		entry->width = 200;
		entry->height = 0x28;
		entry->u = kCmdMenuZero;
		entry->v = kCmdMenuZero;
		entry->startFrame = 7;
		entry->duration = 5;
		y += 0x40;
	}

	list->listEnd = static_cast<s16>(start + 0xc);

	const u32 count = static_cast<u32>(static_cast<s32>(list->listEnd) - static_cast<s32>(list->count));
	CmdListEntry* entry = &entries[list->count];
	for (u32 i = 0; i < count; i++) {
		entry[i].timer = 0;
		entry[i].alpha = kCmdMenuZero;
	}
}

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
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;
	const s16 start = list->count;
	const s32 startIndex = start;

	entries[startIndex].tex = 0x2e;
	entries[startIndex].startFrame = 2;
	entries[startIndex].duration = 5;

	u32 tex = 0x2f;
	if (GetCmdLayoutFlag(this) == 0) {
		tex = 0x46;
	}

	entries[startIndex + 1].tex = tex;
	entries[startIndex + 1].startFrame = 7;
	entries[startIndex + 1].duration = 5;
	entries[startIndex + 2].tex = tex;
	entries[startIndex + 2].startFrame = 7;
	entries[startIndex + 2].duration = 5;

	entries[startIndex + 3].flags = 2;
	entries[startIndex + 3].tex = 0x2e;
	entries[startIndex + 3].startFrame = 7;
	entries[startIndex + 3].duration = 5;

	for (s32 i = 4; i < 12; i++) {
		CmdListEntry* entry = &entries[startIndex + i];
		entry->flags = 2;
		entry->tex = 0x37;
		entry->startFrame = 0;
		entry->duration = 5;
	}

	list->listEnd = start + 0xc;

	const u32 count = static_cast<u32>(static_cast<s32>(list->listEnd) - static_cast<s32>(list->count));
	CmdListEntry* entry = &entries[list->count];
	const float alpha = kCmdMenuOne;
	for (u32 i = 0; i < count; i++) {
		entry[i].timer = 0;
		entry[i].alpha = alpha;
	}
}

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
	CmdState* cmd = GetCmdStateView(this);

	if (cmd->initialized == 0) {
		CmdInit();
	}

	cmd = GetCmdStateView(this);
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;
	s32 finishedCount = 0;
	cmd->transitionTimer = static_cast<s16>(cmd->transitionTimer + 1);

	u32 count = static_cast<u32>(list->count);
	CmdListEntry* entry = entries;
	const s32 timer = static_cast<s32>(cmd->transitionTimer);
	const s32 entryCount = static_cast<s32>(count);

	for (s32 i = 0; i < entryCount; i++) {
		if (entry->startFrame > timer) {
			entry++;
			continue;
		}
		if ((entry->startFrame + entry->duration) <= timer) {
			finishedCount += 1;
			entry->alpha = kCmdMenuOne;
			entry++;
			continue;
		}
		entry->timer++;
		entry->alpha = static_cast<float>(
		    (kCmdMenuOneD / static_cast<double>(entry->duration)) *
		    static_cast<double>(entry->timer));
		entry++;
	}

	bool done = false;
	if (list->count == finishedCount) {
		float anim = kCmdMenuOne;
		entry = entries;
		if (static_cast<s32>(count) > 0) {
			u32 batch = count >> 3;
			if (batch != 0) {
				do {
					entry[0].startFrame = 0;
					entry[0].duration = 1;
					entry[0].alpha = anim;
					entry[1].startFrame = 0;
					entry[1].duration = 1;
					entry[1].alpha = anim;
					entry[2].startFrame = 0;
					entry[2].duration = 1;
					entry[2].alpha = anim;
					entry[3].startFrame = 0;
					entry[3].duration = 1;
					entry[3].alpha = anim;
					entry[4].startFrame = 0;
					entry[4].duration = 1;
					entry[4].alpha = anim;
					entry[5].startFrame = 0;
					entry[5].duration = 1;
					entry[5].alpha = anim;
					entry[6].startFrame = 0;
					entry[6].duration = 1;
					entry[6].alpha = anim;
					entry[7].startFrame = 0;
					entry[7].duration = 1;
					entry[7].alpha = anim;
					entry += 8;
					batch -= 1;
				} while (batch != 0);
				count &= 7;
				if (count == 0) {
					done = true;
				}
			}

			if (done == false) {
				do {
					entry->startFrame = 0;
					entry->duration = 1;
					entry->alpha = anim;
					entry++;
					count -= 1;
				} while (count != 0);
			}
		}
		done = true;
	}

	if (done) {
		UniteOpenAnim(-1);
	}
}

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
	u32 actionHandled = 0;
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	CmdState* cmd = GetCmdStateView(this);

	caravanWork->CalcStatus();

	cmd->prevMode = cmd->mode;

	s16 mode = cmd->mode;
	s16 state = cmd->phase;

	if ((mode == 0) || (state == 1)) {
		actionHandled = CmdCtrlCur();
	} else if ((mode == 1) && (state == 0)) {
		actionHandled = CmdOpen0();
		if (actionHandled != 0) {
			actionHandled = 0;
			cmd->phase = static_cast<s16>(cmd->phase + 1);
		}
	} else if ((mode == 1) && (state == 2)) {
		actionHandled = CmdClose0();
		if (actionHandled != 0) {
			if (cmd->commandResult == 0) {
				cmd->phase = static_cast<s16>(cmd->phase + 1);
			} else {
				cmd->phase = 0;
				cmd->mode = 3;
				cmd->transitionTimer = 0;
				cmd->commandResult = 0;
				CmdInit1();
			}
			actionHandled = 0;
		}
	} else if ((mode == 1) && (state == 3)) {
		actionHandled = static_cast<u32>(UniteOpenAnim(-1));
		if (actionHandled != 0) {
			cmd->phase = 0;
			cmd->mode = 0;
			cmd->transitionTimer = 0;
			CmdInit1();
			actionHandled = 0;
		}
	} else if ((mode == 2) && (state == 0)) {
		actionHandled = CmdOpen1();
		if (actionHandled != 0) {
			actionHandled = 0;
			cmd->phase = static_cast<s16>(cmd->phase + 1);
		}
	} else if ((mode == 2) && (state == 2)) {
		actionHandled = CmdClose1();
		if (actionHandled != 0) {
			if (cmd->commandResult == 0) {
				cmd->mode = 0;
			} else {
				cmd->uniteState = 0;
				cmd->mode = 3;
			}
			actionHandled = 0;
			cmd->phase = 0;
			cmd->transitionTimer = 0;
		}
	} else if ((mode == 3) && (state == 0)) {
		cmd->transitionTimer = static_cast<s16>(cmd->transitionTimer + 1);

		s32 selected = static_cast<s32>(cmd->selected);
		s32 prev = selected - 1;
		for (; prev > 2; --prev) {
			if (caravanWork->m_commandListExtra[prev] >= 0) {
				break;
			}
		}

		s32 next = selected + 1;
		s32 limit = static_cast<s32>(caravanWork->m_numCmdListSlots);
		for (; next < limit; ++next) {
			if (caravanWork->m_commandListExtra[next] >= 0) {
				break;
			}
		}

		CmdListStorage* list = GetCmdListStorage(this);
		float minAnim = static_cast<float>(kCmdMenuHalfD);
		double timer = static_cast<double>(static_cast<s32>(cmd->transitionTimer));
		double anim = -((kCmdMenuAlphaStepD * timer) - kCmdMenuOneD);
		for (s32 i = 0; i < static_cast<s32>(list->count); i++) {
			if ((i < prev) || (next < i)) {
				float value = static_cast<float>(anim);
				if (static_cast<double>(value) < static_cast<double>(minAnim)) {
					value = kCmdMenuHalf;
				}
				list->entries[i].alpha = value;
			}
		}

		actionHandled = (static_cast<double>(static_cast<s32>(cmd->transitionTimer)) >= kCmdMenuTransitionFramesD);
		if (actionHandled != 0) {
			GetCmdStateSelections(cmd)[mode] = static_cast<s16>(prev);
			actionHandled = 0;
			cmd->phase = static_cast<s16>(cmd->phase + 1);
		}
	} else if ((mode == 3) && (state == 2)) {
		actionHandled = CmdClose2();
		if (actionHandled != 0) {
			actionHandled = 0;
			cmd->phase = 0;
			cmd->mode = 0;
			cmd->transitionTimer = 0;
			cmd->commandResult = 0;
		}
	}

	if (actionHandled == 0) {
		return;
	}

	CmdListStorage* list = GetCmdListStorage(this);
	for (s32 i = 0; i < static_cast<s32>(list->count); i++) {
		list->entries[i].alpha = kCmdMenuOne;
		list->entries[i].scale = kCmdMenuOne;
	}

	u32 count = static_cast<u32>(caravanWork->m_numCmdListSlots);
	for (s32 i = static_cast<s32>(count) - 1, idx = 0; i >= 0; i--, idx++) {
		list->entries[i].startFrame = idx;
		list->entries[i].duration = 3;
	}

	cmd->commandResult = 0;
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
	CmdState* cmd = GetCmdStateView(this);
	if (cmd->commandResult == 0) {
		if (UniteCloseAnim(-1) != 0) {
			cmd->transitionTimer = 0;
			cmd->commandResult = 1;
		}
		return 0;
	}

	s32 doneCount = 0;
	cmd->transitionTimer = cmd->transitionTimer + 1;

	CmdListStorage* list = GetCmdListStorage(this);
	u32 count = static_cast<u32>(list->count);
	CmdListEntry* entry = list->entries;
	s32 closeTimer = static_cast<s32>(cmd->transitionTimer);
	const s32 entryCount = static_cast<s32>(count);

	for (s32 i = 0; i < entryCount; i++) {
		if (entry->startFrame <= closeTimer) {
			if (closeTimer >= (entry->startFrame + entry->duration)) {
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

	if (list->count == doneCount) {
		entry = list->entries;
		if (count != 0) {
			u32 blockCount = count >> 3;
			if (blockCount != 0) {
				do {
					entry[0].startFrame = 0;
					entry[0].duration = 1;
					entry[0].alpha = 0.0f;
					entry[1].startFrame = 0;
					entry[1].duration = 1;
					entry[1].alpha = 0.0f;
					entry[2].startFrame = 0;
					entry[2].duration = 1;
					entry[2].alpha = 0.0f;
					entry[3].startFrame = 0;
					entry[3].duration = 1;
					entry[3].alpha = 0.0f;
					entry[4].startFrame = 0;
					entry[4].duration = 1;
					entry[4].alpha = 0.0f;
					entry[5].startFrame = 0;
					entry[5].duration = 1;
					entry[5].alpha = 0.0f;
					entry[6].startFrame = 0;
					entry[6].duration = 1;
					entry[6].alpha = 0.0f;
					entry[7].startFrame = 0;
					entry[7].duration = 1;
					entry[7].alpha = 0.0f;
					entry += 8;
					blockCount = blockCount - 1;
				} while (blockCount != 0);
				count = count & 7;
				if (count == 0) {
					return 1;
				}
			}
			do {
				entry->startFrame = 0;
				entry->duration = 1;
				entry->alpha = 0.0f;
				entry++;
				count = count - 1;
			} while (count != 0);
		}
		return 1;
	}

	return 0;
}

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
	u8* self = reinterpret_cast<u8*>(this);
	CmdState* cmd = GetCmdStateView(this);
	CmdListStorage* cmdList = GetCmdListStorage(this);
	CmdListEntry* entries = cmdList->entries;
	CCaravanWork* const caravan = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	CmdListEntry* entry = entries;
	const s16 cmdMode = cmd->mode;
	const s16 animState = cmd->animState;
	s32 i;
	s32 helpId = -1;
	bool hasItemHelp = false;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	for (i = 0; i < cmdList->count; i++) {
		const s32 tex = entry->tex;
		if (tex >= 0) {
			const float x = static_cast<float>(entry->x);
			float y = static_cast<float>(entry->y);
			const float w = static_cast<float>(entry->width);
			float h = static_cast<float>(entry->height);
			float t = kCmdMenuSmallOffset;

			if ((i > 7) || (caravan->m_commandListExtra[i] == 0)) {
				SetTexture(static_cast<CMenuPcs::TEX>(tex));
				if ((caravan->m_commandListInventorySlotRef[i] > 1) &&
				    (caravan->m_commandListInventorySlotRef[i] == -1)) {
					t += h;
				}
				if ((animState == 1) && (i < caravan->m_numCmdListSlots) &&
				    (i == cmd->selected)) {
					t = kCmdMenuSelectedUvY;
					y -= kCmdMenuSmallOffset;
					h += kCmdMenuSmallOffset;
				}

				GXColor boxColor;
				boxColor.r = 0xFF;
				boxColor.g = 0xFF;
				boxColor.b = 0xFF;
				boxColor.a = static_cast<u8>(kCmdMenuAlphaMax * entry->alpha);
				GXSetChanMatColor(GX_COLOR0A0, boxColor);

				DrawRect(
				    0, x, y, w, h, entry->u, t, entry->scale, entry->scale, 0.0f);
			}
		}
		entry++;
	}

	CFont* nameFont = m_fonts[4];
	nameFont->SetMargin(kCmdMenuOne);
	nameFont->SetShadow(0);
	nameFont->SetScale(kCmdMenuTextScale);
	nameFont->DrawInit();

	entry = entries;
	for (i = 0; i < caravan->m_numCmdListSlots; i++) {
		if ((i > 7) || (caravan->m_commandListExtra[i] == 0)) {
			float alpha = entry->alpha;
			if (cmdMode == 3) {
				alpha = kCmdMenuOne;
			}

			GXColor textColor;
			textColor.r = 0xFF;
			textColor.g = 0xFF;
			textColor.b = 0xFF;
			textColor.a = static_cast<u8>(kCmdMenuAlphaMax * alpha);
			nameFont->SetColor(textColor);

			const char* text;
			if (i < 2) {
				text = GetMenuStr(i + 9);
			} else {
				const s16 cmdId = caravan->m_commandListInventorySlotRef[i];
				if (cmdId < 0) {
					entry++;
					continue;
				}
				const s16 skillId = caravan->m_inventoryItems[cmdId];
				char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
				text = flatText[skillId * 5 + 4];
				if ((cmdMode == 0) && (i == cmd->selected)) {
					hasItemHelp = true;
					helpId = skillId;
				}
			}

			const float textW = static_cast<float>(nameFont->GetWidth(text));
			const float px = static_cast<float>(entry->x) + ((static_cast<float>(entry->width) - textW) * 0.5f);
			const float py = static_cast<float>(entry->y + 3) - kCmdMenuTextYOffset;
			nameFont->SetPosX(px);
			nameFont->SetPosY(py);
			nameFont->Draw(text);
		}
		entry++;
	}

	DrawInit();
	DrawUniteList();

	entry = entries;
	for (i = 0; i < caravan->m_numCmdListSlots; i++) {
		if ((i > 1) && (caravan->m_commandListInventorySlotRef[i] >= 0)) {
			DrawSingleIcon(
			    caravan->m_inventoryItems[caravan->m_commandListInventorySlotRef[i]],
			    entry->x + entry->width - 0x10, entry->y - 2, entry->alpha, 0, 0.0f);
		}
		entry++;
	}

	if (cmdMode == 2) {
		CmdListEntry* panel = &entries[cmdList->listEnd + 3];
		SetTexture(static_cast<CMenuPcs::TEX>(panel->tex));

		GXColor panelColor;
		panelColor.r = 0xFF;
		panelColor.g = 0xFF;
		panelColor.b = 0xFF;
		panelColor.a = static_cast<u8>(kCmdMenuAlphaMax * panel->alpha);
		GXSetChanMatColor(GX_COLOR0A0, panelColor);
		DrawRect(
		    0, static_cast<float>(panel->x), static_cast<float>(panel->y),
		    static_cast<float>(panel->width), static_cast<float>(panel->height),
		    panel->u, panel->v, kCmdMenuOne, panel->scale, 0.0f);

		CFont* choiceFont = m_fonts[0];
		choiceFont->SetMargin(kCmdMenuOne);
		choiceFont->SetShadow(1);
		choiceFont->SetScale(kCmdMenuTextScale);
		choiceFont->DrawInit();
		choiceFont->SetTlut(7);
		choiceFont->SetColor(panelColor);

		const s32 choices = (kCmdMenuOneD == static_cast<double>(panel->scale)) ? 2 : 3;
		const float pitch = static_cast<float>(
		    ((static_cast<float>(panel->height) * panel->scale) - kCmdMenuChoicePaddingD) /
		    static_cast<float>(choices));
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
			choiceFont->SetPosX(static_cast<float>(panel->x + 0x18));
			choiceFont->SetPosY(
			    ((pitch - static_cast<float>(kCmdMenuTextLineHeightD)) * static_cast<float>(kCmdMenuHalfD)) +
			    ((pitch * static_cast<float>(choice)) + static_cast<float>(panel->y + 8)) -
			    kCmdMenuTextYOffset);
			choiceFont->Draw(text);
		}
		DrawInit();
	}

	if ((cmdMode == 1) && (cmd->phase == 1)) {
		const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const float mark = CalcListPos(cmd->scrollTop, letter[0], 1);
		CmdListEntry* listPos = &entries[cmdList->count];
		if (mark > kCmdMenuZero) {
			DrawListPosMark(static_cast<float>(listPos->x), static_cast<float>(listPos->y), mark);
		}
	}

	if (((cmdMode == 0) && (animState == 1)) ||
	    ((cmdMode != 0) && (cmd->phase == 1))) {
		float cursorX = kCmdMenuOne;
		float cursorY = kCmdMenuOne;
		CmdListEntry* cursorEntry = entries;
		bool cursorOnUnite = false;

		if ((cmdMode == 0) || (cmdMode == 3)) {
			s32 index = GetCmdStateSelections(cmd)[cmdMode];
			if (caravan->m_commandListExtra[index] == 0) {
				cursorEntry = &entries[index];
			} else {
				s32 uniteIdx = 0;
				while ((uniteIdx < s_unitePanelCount) && (s_UniteTop[uniteIdx] != index)) {
					uniteIdx++;
				}
				cursorEntry = &entries[cmdList->listEnd + uniteIdx];
				cursorOnUnite = true;
			}
			cursorX = static_cast<float>(cursorEntry->x - 0x14);
			if (cursorOnUnite) {
				cursorY = static_cast<float>(cursorEntry->y) +
				          (static_cast<float>(cursorEntry->height - 0x20) * static_cast<float>(kCmdMenuHalfD));
			} else {
				cursorY = static_cast<float>(cursorEntry->y);
				if (cmdMode != 0) {
					cursorY += kCmdMenuSmallOffset;
				}
			}
		} else if (cmdMode == 1) {
			const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
			s32 idx = 0;
			CmdListEntry* scan = &entries[cmdList->count];
			while (idx < 8) {
				if (scan->tex == 0x37) {
					break;
				}
				scan++;
				idx++;
			}
			const s32 cur = cmd->itemSelected + cmd->scrollTop;
			s32 wrapped = cur;
			if (letter[0] <= cur) {
				wrapped -= letter[0];
			}
			scan += wrapped;
			cursorX = static_cast<float>(scan->x - 0x14);
			cursorY = static_cast<float>(scan->y);
		} else {
			CmdListEntry* panel = &entries[cmdList->listEnd + 3];
			const s32 choices = (kCmdMenuOneD == static_cast<double>(panel->scale)) ? 2 : 3;
			const float pitch = static_cast<float>(
			    ((static_cast<float>(panel->height) * panel->scale) - kCmdMenuChoicePaddingD) /
			    static_cast<float>(choices));
			cursorX = static_cast<float>(panel->x - 0x14);
			cursorY = ((pitch - static_cast<float>(kCmdMenuTextLineHeightD)) * static_cast<float>(kCmdMenuHalfD)) +
			          ((pitch * static_cast<float>(cmd->choice)) + static_cast<float>(panel->y + 8));
		}

		const s32 frame = System.m_frameCounter & 7;
		DrawCursor(static_cast<s32>(cursorX + static_cast<float>(frame)), static_cast<s32>(cursorY), kCmdMenuOne);
	}

	if (!hasItemHelp) {
		helpId = -1;
	}
	if ((cmdMode == 0) && (helpId == -1) &&
	    (caravan->m_commandListExtra[cmd->selected] == 0)) {
		helpId = 0x266;
	}
	if (cmdMode == 1) {
		const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		s32 idx = cmd->itemSelected + cmd->scrollTop;
		if (letter[0] <= idx) {
			idx -= letter[0];
		}
		if (idx < 2) {
			helpId = idx + 0x259;
		}
	}
	if (cmdMode == 2) {
		if (cmd->choice == 0) {
			helpId = 0x25B;
		} else {
			helpId = -1;
		}
	}

	float helpAlpha = entries[cmdList->count].alpha;
	if ((cmdMode == 0) || (cmdMode == 2)) {
		helpAlpha = entries[0].alpha;
	}

	GXColor helpColor;
	helpColor.r = 0xFF;
	helpColor.g = 0xFF;
	helpColor.b = 0xFF;
	helpColor.a = static_cast<u8>(kCmdMenuAlphaMax * helpAlpha);
	DrawHelpMessage(
	    helpId, m_fonts[0], 0, static_cast<s32>(-kCmdMenuHelpXOffset), helpColor, 0,
	    kCmdMenuHalf, kCmdMenuScreenHalfWidth);
}

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
	bool blocked = false;
	unsigned int press;
	u16 hold;
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

	if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		press = Pad.GetPadInputs()[0].buttonDown[0];
	}

	blocked = false;
	if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		hold = Pad.GetPadInputs()[0].repeatButton;
	}

	if (hold == 0) {
		return 0;
	}

	CmdState* cmd = GetCmdStateView(this);
	CmdListStorage* cmdList = GetCmdListStorage(this);
	int mode = cmd->mode;

	if (mode == 0) {
		s16 cmdCount = caravanWork->m_numCmdListSlots;

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (cmd->selected < cmdCount - 1) {
					cmd->selected++;
				} else {
					cmd->selected = 2;
				}

				int cursor = cmd->selected;
				if (caravanWork->m_commandListExtra[cursor] < 0) {
					if (caravanWork->m_commandListExtra[cursor + 1] < 0) {
						if (caravanWork->m_commandListExtra[cursor + 2] >= 0) {
							cmd->selected = static_cast<s16>(cursor + 2);
						}
					} else {
						cmd->selected = static_cast<s16>(cursor + 1);
					}
					if (cmd->selected > cmdCount - 1) {
						cmd->selected = 2;
					}
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (cmd->selected < 3) {
				cmd->selected = static_cast<s16>(cmdCount - 1);
			} else {
				cmd->selected--;
			}

			int cursor = cmd->selected;
			if (caravanWork->m_commandListExtra[cursor] < 0) {
				if (caravanWork->m_commandListExtra[cursor - 1] < 0) {
					if (caravanWork->m_commandListExtra[cursor - 2] >= 0) {
						cmd->selected = static_cast<s16>(cursor - 2);
					}
				} else {
					cmd->selected = static_cast<s16>(cursor - 1);
				}
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x20) != 0) {
				cmd->action = 1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x40) != 0) {
				cmd->action = -1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					cmd->submenuFlag = 1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
					return 1;
				}
			} else {
				if (caravanWork->m_commandListExtra[cmd->selected] == 0) {
					cmd->mode = 1;
				} else {
					cmd->submenuFlag = 0;
					cmd->mode = 2;
				}
				cmd->phase = 0;
				cmd->transitionTimer = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
	} else if (mode == 1) {
		s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int itemCount = static_cast<int>(list[0]);

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (((itemCount < 9) || (cmd->itemSelected < 7)) &&
				    ((itemCount <= 8) || ((itemCount - 1) > cmd->itemSelected))) {
					if (itemCount < 9) {
						cmd->itemSelected = 0;
					} else if (cmd->scrollTop < itemCount - 1) {
						cmd->scrollTop++;
					} else {
						cmd->scrollTop = 0;
					}
				} else {
					cmd->itemSelected++;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (cmd->itemSelected == 0) {
				if (itemCount < 9) {
					cmd->itemSelected = static_cast<s16>(itemCount - 1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else if (cmd->scrollTop == 0) {
					cmd->scrollTop = static_cast<s16>(itemCount - 1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					cmd->scrollTop--;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			} else {
				cmd->itemSelected--;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					cmd->phase++;
					cmd->transitionTimer = 0;
					cmd->commandResult = 0;
					CmdInit2();
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				int selected = static_cast<int>(cmd->scrollTop) + static_cast<int>(cmd->itemSelected);
				if (itemCount <= selected) {
					selected -= itemCount;
				}

				u32 canUse = 0;
				if (selected < 0 || list[0] <= selected) {
					canUse = 0;
				} else if (selected == 0) {
					canUse = static_cast<u32>(caravanWork->m_commandListInventorySlotRef[cmd->selected] >= 0);
				} else if (selected == 1) {
					int combo[5][2];
					canUse = static_cast<u32>(ChkUnite(cmd->selected, combo) > 0);
				} else {
					canUse = static_cast<u32>(EquipChk(static_cast<int>(list[selected - 1])) != 0);
				}

				if ((canUse & 0xFF) == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (selected == 0) {
						caravanWork->ChgCmdLst(cmd->selected, -1);
					} else if (selected != 1) {
						caravanWork->ChgCmdLst(cmd->selected, list[selected - 1]);
					}

					cmd->commandResult = 0;
					if (selected != 0) {
						int comboChoice[2][2];
						int comboCount = ChkUnite(cmd->selected, comboChoice);
						if (comboCount == 1) {
							const int recipe = comboChoice[0][0];
							caravanWork->UniteComList(
							    comboChoice[0][1], GetUniteRecipeCount(recipe), GetUniteRecipeCmd(recipe));
						} else if (comboCount > 1) {
							cmd->commandResult = 1;
						}
					}

					cmd->phase++;
					cmd->transitionTimer = 0;
					CmdInit2();
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			}
		}
	} else if (mode == 2) {
		int maxPos;
		if (kCmdMenuOneD == static_cast<double>(cmdList->entries[cmdList->listEnd + 3].scale)) {
			maxPos = 2;
		} else {
			maxPos = 3;
		}

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (cmd->choice < maxPos - 1) {
					cmd->choice++;
				} else {
					cmd->choice = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (cmd->choice == 0) {
				cmd->choice = static_cast<s16>(maxPos - 1);
			} else {
				cmd->choice--;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			cmd->uniteState = 0;
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					cmd->phase++;
					cmd->transitionTimer = 0;
					cmd->commandResult = -1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				cmd->phase++;
				cmd->transitionTimer = 0;
				cmd->commandResult = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
	} else {
		if ((hold & 0xC) != 0) {
			int selected = cmd->selected;
			int prev = selected - 1;
			int remaining = selected - 3;
			if (prev > 2) {
				do {
					if (caravanWork->m_commandListExtra[prev] >= 0) {
						break;
					}
					prev--;
					remaining--;
				} while (remaining != 0);
			}

			int next = selected + 1;
			remaining = caravanWork->m_numCmdListSlots - next;
			if (next < caravanWork->m_numCmdListSlots) {
				do {
					if (caravanWork->m_commandListExtra[next] >= 0) {
						break;
					}
					next++;
					remaining--;
				} while (remaining != 0);
			}

			s16* modeCursor = GetCmdStateSelections(cmd) + mode;
			if (*modeCursor == prev) {
				*modeCursor = static_cast<s16>(next);
			} else {
				*modeCursor = static_cast<s16>(prev);
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			cmd->commandResult = 0;
			cmd->uniteState = 0;
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					cmd->commandResult = -1;
					cmd->phase++;
					cmd->transitionTimer = 0;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			} else {
				cmd->phase++;
				cmd->transitionTimer = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		}
	}

	return 0;
}

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
	CmdState* cmd = GetCmdStateView(this);
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;

	cmd->transitionTimer = static_cast<s16>(cmd->transitionTimer + 1);
	const s32 timer = static_cast<s32>(cmd->transitionTimer);
	if (timer < 5) {
		entries[cmd->selected].x = static_cast<s16>(entries[cmd->selected].x - 0x13);
	}

	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(list->listEnd) - static_cast<s32>(list->count);
	CmdListEntry* entry = &entries[list->count];
	const float fVar1 = kCmdMenuZero;

	for (s32 i = 0; i < entryCount; i++) {
		if (entry->startFrame <= timer) {
			if (timer >= entry->startFrame + entry->duration) {
				doneCount++;
				entry->alpha = kCmdMenuOne;
				entry->dx = fVar1;
				entry->dy = fVar1;
			} else {
				entry->timer++;
				const float t = static_cast<float>(
					(kCmdMenuOneD / static_cast<double>(entry->duration)) *
					static_cast<double>(entry->timer));
				entry->alpha = t;
				if ((entry->flags & 2) == 0) {
					entry->dx = t * (entry->targetX - static_cast<float>(entry->x));
					entry->dy = t * (entry->targetY - static_cast<float>(entry->y));
				}
			}
		}

		entry++;
	}

	return static_cast<unsigned int>(entryCount == doneCount);
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
	u8* self = reinterpret_cast<u8*>(this);
	CmdState* cmd = GetCmdStateView(this);
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;

	cmd->transitionTimer = static_cast<s16>(cmd->transitionTimer + 1);
	s32 time = static_cast<s32>(cmd->transitionTimer);

	if (time > 7) {
		entries[cmd->selected].x = static_cast<s16>(entries[cmd->selected].x + 0x13);
	}

	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(list->listEnd) - static_cast<s32>(list->count);
	CmdListEntry* entry = &entries[list->count];

	for (s32 i = 0; i < entryCount; i++) {
		if (entry->startFrame <= time) {
			if (time >= (entry->startFrame + entry->duration)) {
				doneCount++;
				entry->alpha = 0.0f;
				entry->dx = 0.0f;
				entry->dy = 0.0f;
			} else {
				entry->timer++;
				const f32 t = static_cast<f32>(
				    1.0 - (static_cast<f64>(entry->timer) /
				           static_cast<f64>(entry->duration)));

				entry->alpha = t;
				if ((entry->flags & 2) == 0) {
					entry->dx = t * (entry->targetX - static_cast<f32>(entry->x));
					entry->dy = t * (entry->targetY - static_cast<f32>(entry->y));
				}
			}
		}
		entry++;
	}

	if (entryCount == doneCount) {
		entries[cmd->selected].x = entries[0].x;
	}

	return static_cast<unsigned int>(entryCount == doneCount);
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
void CMenuPcs::GetCmdItem()
{
	const CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	s16* write = list;
	s32 count = 0;

	for (s32 i = 0; i < 0x40; i++) {
		s32 itemType = GetItemType(i, 0);
		if ((itemType != 0) && (itemType != 5) && (itemType != 6) && (itemType != 8) && (itemType != 9)) {
			if ((itemType != 1) ||
			    (GetItemIcon(caravanWork->m_inventoryItems[i]) == (caravanWork->m_tribeId & 3))) {
				write++;
				*write = static_cast<s16>(i);
				count++;
			}
		}
	}

	s16* write2 = list + count;
	for (s32 i = 0; i < 0x49; i++) {
		s32 arti = i + 0x9f;
		if (caravanWork->m_artifacts[i] == arti) {
			if (IsMagicArti(arti)) {
				count++;
				write2++;
				*write2 = static_cast<s16>(i + 0x40);
			}
		}
	}

	s16* write3 = list + count;
	if (IsMagicArti(caravanWork->m_treasures[0])) {
		count++;
		write3++;
		*write3 = 0xa0;
	}
	if (IsMagicArti(caravanWork->m_treasures[1])) {
		count++;
		write3++;
		*write3 = 0xa1;
	}
	if (IsMagicArti(caravanWork->m_treasures[2])) {
		count++;
		write3++;
		*write3 = 0xa2;
	}
	if (IsMagicArti(caravanWork->m_treasures[3])) {
		count++;
		write3[1] = 0xa3;
	}

	*reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0)) = static_cast<s16>(count + 2);
}

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
	CmdState* const cmd = GetCmdStateView(this);

	int candidates[10];
	int itemKinds[11];
	int matches[10];

	memset(candidates, -1, sizeof(candidates));
	memset(itemKinds, -1, sizeof(itemKinds));
	memset(matches, -1, sizeof(matches));

	if (comboOut != nullptr) {
		for (int i = 0; i < 5; i++) {
			comboOut[i][0] = -1;
			comboOut[i][1] = -1;
		}
	}

	const s16 selectedState = caravan->m_commandListExtra[selected];
	const u32 selectedNegMask = static_cast<u32>(-selectedState) & ~static_cast<u32>(selectedState);

	if ((cmd->mode == 1) && (cmd->phase == 2)) {
		if (selectedState < 0) {
			selected--;
		}
		if (caravan->m_commandListExtra[selected] < 0) {
			selected--;
		}
	}

	int write = 2;
	for (int slot = 2; slot < 8;) {
		int nextWrite = write;
		int nextSlot = slot + 1;

		if (slot == selected) {
			if (caravan->m_commandListExtra[slot] == 0) {
				candidates[write] = 0;
			} else {
				candidates[write] = 0;
				candidates[write + 1] = 0;
				nextWrite = write + 1;
				nextSlot = slot + 2;
				if (caravan->m_commandListExtra[slot + 1] < 0) {
					candidates[write + 2] = 0;
					nextWrite = write + 2;
					nextSlot = slot + 3;
				}
			}
		} else {
			const u32 v = static_cast<u32>(caravan->m_commandListExtra[slot]);
			candidates[write] = static_cast<s32>((-v | v) >> 31);
		}

		write = nextWrite + 1;
		slot = nextSlot;
	}

	int index = 2;
	for (int slot = 2; slot < 8; slot++, index++) {
		if (caravan->m_numCmdListSlots <= slot) {
			break;
		}
		const s16 itemRef = caravan->m_commandListInventorySlotRef[slot];
		if (itemRef < 0) {
			continue;
		}

		const int itemId = caravan->m_inventoryItems[itemRef];
		const int icon = GetItemIcon(itemId);

		if ((itemId > 0xde) && (itemId < 0xe4)) {
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
		} else if ((icon == 0) || (icon == 1) || (icon == 2) || (icon == 3)) {
			itemKinds[index] = 999;
		} else if ((icon == 0x10) || (icon == 0x11)) {
			itemKinds[index] = itemId;
		}
	}

	int matchCount = 0;
	if (itemKinds[selected] > 0) {
		if ((itemKinds[selected] == 999) && (selected > 2)) {
			int patIdx = 0;
			for (const s16* pat = s_uniteRecipePatterns; pat[1] >= 0; pat += 6, patIdx++) {
				if ((pat[0] == 0) || ((pat[2] == 2) && (static_cast<s32>(selectedNegMask) < 0))) {
					continue;
				}
				int ok = 0;
				for (int k = 0; k < pat[2]; k++) {
					const int slot = selected - (pat[2] - 1 - k);
					if (candidates[slot] != 0) {
						break;
					}
					if (pat[3 + k] == itemKinds[slot]) {
						ok++;
					}
				}
				if (ok == pat[2] - 1) {
					matches[matchCount * 2] = patIdx;
					matches[matchCount * 2 + 1] = selected - (pat[2] - 1);
					matchCount++;
				}
			}
		} else if (static_cast<s32>(selectedNegMask) >= 0) {
			const int baseLen = static_cast<int>(s_uniteRecipePatterns[2]);
			int start = selected - (baseLen - 1);
			for (int i = 0; i < baseLen; i++, start++) {
				int ok = 0;
				for (int k = 0; k < baseLen; k++) {
					const int slot = i + (selected - ((baseLen - 1) - k));
					if (candidates[slot] != 0) {
						break;
					}
					if (s_uniteRecipePatterns[3 + k] == itemKinds[slot]) {
						ok++;
					}
				}
				if (ok == baseLen) {
					matches[matchCount * 2] = 0;
					matches[matchCount * 2 + 1] = start;
					matchCount++;
				}
			}
		}

		int group = 1;
		int* matchWrite = matches + matchCount * 2;
		for (const s16* pat = s_uniteRecipePatterns + 6; pat[1] >= 0; pat += 6, group++) {
			if (((pat[0] != 0) && (itemKinds[selected] == 999) && (selected >= 3)) ||
			    ((pat[2] == 2) && (static_cast<s32>(selectedNegMask) < 0))) {
				continue;
			}

			const int len = static_cast<int>(pat[2]);
			for (int start = 0; start < len; start++) {
				if ((start == 0) && (static_cast<s32>(selectedNegMask) < 0)) {
					start = 1;
				}

				int ok = 0;
				for (int k = 0; k < len; k++) {
					const int slot = start + (selected - ((len - 1) - k));
					if (candidates[slot] != 0) {
						break;
					}
					if (pat[3 + k] == itemKinds[slot]) {
						ok++;
					}
				}

				if (ok == len) {
					matchWrite[0] = group;
					matchWrite[1] = start + (selected - (len - 1));
					matchWrite += 2;
					matchCount++;
				}
			}
		}
	}

	if (comboOut != nullptr) {
		for (int rank = 0; rank < 2; rank++) {
			int (*dst)[2] = comboOut;
			for (int i = 0; i < matchCount; i++) {
				const int* m = &matches[i * 2];
				if (rank + 2 == s_uniteRecipePatterns[2 + m[0] * 6]) {
					dst[0][0] = m[0];
					dst[0][1] = m[1];
					dst++;
				}
			}
			comboOut = dst;
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
	CmdListStorage* const list = GetCmdListStorage(this);
	CmdListEntry* const entries = list->entries;
	CmdState* const cmd = GetCmdStateView(this);
	s16 selected = cmd->selected;
	const s16 foodCount = caravan->m_numCmdListSlots;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	s_unitePanelCount = 0;
	bool active = false;
	for (s32 i = 0; i < 8; i++) {
		const s32 slotType = caravan->m_commandListExtra[i];
		if (i == selected) {
			active = true;
		} else if (slotType >= 0) {
			active = false;
		}

		if (i >= foodCount) {
			break;
		}

		if (slotType == 0) {
			continue;
		}

		CmdListEntry* const entry = &entries[i];
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<u8>(kCmdMenuAlphaMax * entry->alpha);
		GXSetChanMatColor((_GXChannelID)4, color);

		s32 groupSize = 1;
		if (slotType > 0) {
			if ((i + 2 < 8) && (caravan->m_commandListExtra[i + 2] == -1)) {
				groupSize = 3;
			} else {
				groupSize = 2;
			}
		}

		if (slotType > 0) {
			selected = cmd->selected;
			if ((i <= selected) && (selected < i + groupSize)) {
				if ((cmd->phase == 3) && (i != selected)) {
					cmd->selected = static_cast<s16>(i);
				}
				active = true;
			}
		}

		SetTexture(static_cast<CMenuPcs::TEX>((groupSize == 2) ? 0x36 : 0x35));
		DrawRect(0,
			static_cast<float>(entry->x + 4),
			static_cast<float>(entry->y) - kCmdMenuSmallOffset,
			static_cast<float>(entry->width) - 8.0f,
			kCmdMenuUniteBarHeight,
			static_cast<float>(entry->u),
			active ? kCmdMenuUniteBarHeight : kCmdMenuZero,
			kCmdMenuOne,
			kCmdMenuOne,
			kCmdMenuOne);
	}

	CFont* const font = m_fonts[0];
	font->SetMargin(kCmdMenuOne);
	font->SetShadow(1);
	font->SetScale(kCmdMenuTextScale);
	font->DrawInit();
	font->SetTlut(7);

	const s16 topX = entries[0].x;
	for (s32 i = 0; i < foodCount; i++) {
		const s16 slotType = caravan->m_commandListExtra[i];
		if ((i <= 7) && (slotType == 0)) {
			continue;
		}

		CmdListEntry* const entry = &entries[i];
		const float alpha = (cmd->mode == 3) ? kCmdMenuOne : entry->alpha;

		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<u8>(kCmdMenuAlphaMax * alpha);
		font->SetColor(color);

		const char* text = 0;
		if (i < 2) {
			text = GetMenuStr(i + 9);
		} else {
			const s16 itemIdx = caravan->m_commandListInventorySlotRef[i];
			if (itemIdx < 0) {
				continue;
			}
			const s16 skillId = caravan->m_inventoryItems[itemIdx];
			char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
			text = flatText[skillId * 5 + 4];
		}

		const float width = static_cast<float>(font->GetWidth(text));
		float x = (static_cast<float>(entry->width) - width) * static_cast<float>(kCmdMenuHalfD) + static_cast<float>(entry->x);
		if (topX != entry->x) {
			float diff = static_cast<float>(topX - entry->x);
			if (diff < kCmdMenuOne) {
				diff = -diff;
			}
			const float t = diff * 0.125f;
			const float target = static_cast<float>(entry->x + entry->width - 0x18) - width;
			x = (target - x) * t + x;
		}

		font->SetPosX(x);
		font->SetPosY(static_cast<float>(entry->y + 3) - kCmdMenuTextYOffset);
		font->Draw(text);
	}

	DrawInit();
	s_unitePanelCount = 0;
	CmdListEntry* const unitePanels = &entries[list->listEnd];
	for (s32 i = 0; i < 8; i++) {
		if (i >= foodCount) {
			break;
		}

		const s16 slotType = caravan->m_commandListExtra[i];
		if (slotType <= 0) {
			continue;
		}

		s32 groupSize = 2;
		if ((i + 2 < 8) && (caravan->m_commandListExtra[i + 2] == -1)) {
			groupSize = 3;
		}

		if (i > 0) {
			const s16 prevType = caravan->m_commandListExtra[i - 1];
			if ((prevType > 0) && (groupSize != 3)) {
				continue;
			}
		}

		if (s_unitePanelCount >= 3) {
			continue;
		}

		const s32 labelAnchor = (i == selected) ? i + 1 : i;
		CmdListEntry* const endEntry = &entries[i + groupSize - 1];
		CmdListEntry* const anchorEntry = &entries[labelAnchor];
		CmdListEntry* const startEntry = &entries[i];
		const bool active = (i <= selected) && (selected < i + groupSize);
		const float panelX = static_cast<float>(topX * 2 - anchorEntry->x);
		const float panelY = (static_cast<float>(endEntry->width + endEntry->height - startEntry->width) -
		                      kCmdMenuPanelSize64) * static_cast<float>(kCmdMenuHalfD) +
		                     static_cast<float>(startEntry->y);
		const float panelTone = active ? kCmdMenuPanelSize64 : kCmdMenuZero;
		float panelAlpha;
		if (cmd->mode == 3) {
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

		CmdListEntry* const panel = &unitePanels[s_unitePanelCount];
		panel->x = static_cast<s16>(panelX);
		panel->y = static_cast<s16>(panelY);
		panel->width = static_cast<s16>(kCmdMenuUnitePanelWidth);
		panel->height = static_cast<s16>(kCmdMenuPanelSize64);
		panel->u = kCmdMenuZero;
		panel->v = panelTone;
		panel->alpha = panelAlpha;
		s_UniteTop[s_unitePanelCount] = i;
		s_unitePanelCount++;

		SetTexture(static_cast<CMenuPcs::TEX>(0x38));
		DrawRect(0,
			panelX,
			panelY - kCmdMenuPanelInset,
			kCmdMenuUnitePanelWidth,
			kCmdMenuPanelSize64,
			kCmdMenuPanelInset,
			panelTone,
			kCmdMenuOne,
			kCmdMenuOne,
			kCmdMenuOne);
	}

	font->SetMargin(kCmdMenuOne);
	font->SetShadow(1);
	font->SetScale(kCmdMenuOne);
	font->DrawInit();
	font->SetTlut(6);

	for (s32 i = 0; i < s_unitePanelCount; i++) {
		CmdListEntry* const panel = &unitePanels[i];
		const float alpha = (cmd->mode == 3) ? kCmdMenuOne : panel->alpha;
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<u8>(kCmdMenuAlphaMax * alpha);
		font->SetColor(color);

		const int itemId = caravan->m_commandListExtra[s_UniteTop[i]];
		const char* text = GetUniteListName(itemId);
		const float width = static_cast<float>(font->GetWidth(text));
		font->SetPosX((static_cast<float>(panel->width) - width) *
		                  static_cast<float>(kCmdMenuHalfD) +
		              static_cast<float>(panel->x));
		font->SetPosY(((static_cast<float>(panel->height) - static_cast<float>(kCmdMenuTextLineHeightD)) *
		                   static_cast<float>(kCmdMenuHalfD) +
		               static_cast<float>(panel->y)) -
		              kCmdMenuTextYOffset - static_cast<float>(kCmdMenuTextBaselineOffsetD));
		font->Draw(text);
	}

	DrawInit();
	if ((cmd->mode == 0) &&
	    (caravan->m_commandListExtra[selected] != 0)) {
		int helpId = caravan->m_commandListExtra[selected];
		if (helpId == 0x207 || helpId == 0x20B || helpId == 0x20F) {
			helpId += 2;
		}

		const float alpha = entries[0].alpha;
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<u8>(kCmdMenuAlphaMax * alpha);
		DrawHelpMessage(
			helpId, font, 0,
			static_cast<int>(-(kCmdMenuUnitePanelWidth * kCmdMenuHalf - kCmdMenuScreenHalfWidth)),
			color, 0, kCmdMenuHalf, kCmdMenuScreenHalfWidth);
	}
}

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
	if (s_unitePanelCount == 0) {
		return 1;
	}

	CmdListEntry* entries = GetCmdListEntries(this);
	float baseX = static_cast<float>(entries[0].x);
	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);

	if (topIdx > 0) {
		int i = 0;
		int k = 3;
		do {
			int idx = i + s_UniteTop[topIdx];
			CmdListEntry* entry = &entries[idx];
			if ((i != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
				break;
			}

			entry->x = static_cast<s16>(static_cast<double>(entry->x) + kCmdMenuUniteSlideStepD);
			if (fabs(static_cast<double>(static_cast<float>(entry->x) - baseX)) >
			    kCmdMenuUniteSlideLimitD) {
				entry->x = static_cast<s16>(kCmdMenuPanelSize64 + baseX);
				return 1;
			}

			i++;
			k--;
		} while (k != 0);
	} else {
		int finished = 0;
		float targetX = kCmdMenuPanelSize64 + baseX;
		s32* top = s_UniteTop;
		for (int i = 0; i < s_unitePanelCount; i++) {
			int j = 0;
			int k = 3;
			do {
				int idx = j + *top;
				CmdListEntry* entry = &entries[idx];
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

				j++;
				k--;
			} while (k != 0);
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

	CmdListEntry* entries = GetCmdListEntries(this);
	float baseX = static_cast<float>(entries[0].x);
	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);

	if (topIdx >= 0) {
		int finished = 0;
		for (int i = 0; i < 3; i++) {
			int idx = i + s_UniteTop[topIdx];
			CmdListEntry* entry = &entries[idx];
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
		s32* top = s_UniteTop;
		for (int i = 0; i < s_unitePanelCount; i++) {
			for (int j = 0; j < 3; j++) {
				int idx = j + *top;
				CmdListEntry* entry = &entries[idx];
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
	u8* self = reinterpret_cast<u8*>(this);
	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	CmdState* cmd = GetCmdStateView(this);
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;

	cmd->transitionTimer = static_cast<s16>(cmd->transitionTimer + 1);

	const s32 selected = static_cast<s32>(cmd->selected);
	const f32 t = static_cast<f32>(
		-((kCmdMenuTransitionStepD * static_cast<f64>(cmd->transitionTimer)) - kCmdMenuOneD)
	);
	entries[selected].alpha = t;

	s32 chainCount = 1;
	if (caravanWork->m_commandListExtra[selected + 1] == -1) {
		chainCount = 2;
		entries[selected + 1].alpha = t;
		if (caravanWork->m_commandListExtra[selected + 2] == -1) {
			chainCount = 3;
			entries[selected + 2].alpha = t;
		}
	}

	s32 slot = 0;
	if ((selected != s_UniteTop[0]) && ((slot = 1), selected != s_UniteTop[1]) &&
	    ((slot = 2), selected != s_UniteTop[2])) {
		slot = 3;
	}

	CmdListEntry* const animEntry = &entries[list->listEnd + 3];
	CmdListEntry* const baseEntry = &entries[list->listEnd + slot];

	if (cmd->unitePanelInitialized == 0) {
		const s32 endX = static_cast<s32>(static_cast<f64>(baseEntry->x + baseEntry->width) - kCmdMenuPanelRightInsetD);
		animEntry->x = static_cast<s16>(endX);

		if (chainCount == 2) {
			int combo[5][2];
			chainCount = ChkUnite(static_cast<int>(cmd->selected), combo);
		} else {
			chainCount = 0;
		}

		f32 panelScale = 1.0f;
		if (chainCount != 0) {
			panelScale = static_cast<f32>(kCmdMenuUnitePanelScaleD);
		}
		animEntry->scale = panelScale;
		animEntry->width = 0xC0;
		animEntry->height = 0x40;
		animEntry->y = static_cast<s16>(((-((static_cast<f64>(animEntry->height) * animEntry->scale) -
		                                    static_cast<f64>(baseEntry->height)) *
		                                   kCmdMenuHalfD) +
		                                  static_cast<f64>(baseEntry->y)) -
		                                 kCmdMenuUnitePanelYOffsetD);
		animEntry->u = kCmdMenuZero;
		animEntry->v = kCmdMenuZero;
		animEntry->tex = 0x39;
		cmd->unitePanelInitialized = 1;
	}

	animEntry->alpha = static_cast<f32>(kCmdMenuTransitionStepD * static_cast<f64>(cmd->transitionTimer));
	u32 done = static_cast<u32>(static_cast<f64>(cmd->transitionTimer) >= kCmdMenuTransitionFramesD);
	if (done != 0) {
		cmd->choice = 0;
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
	u8* self = reinterpret_cast<u8*>(this);
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	CmdState* cmd = GetCmdStateView(this);
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;

	cmd->transitionTimer = static_cast<s16>(cmd->transitionTimer + 1);
	const s16 timer = cmd->transitionTimer;
	s32 state = cmd->uniteState;
	u32 done = 0;

	if (state == 0) {
		const s16 selected = cmd->selected;
		const float t = static_cast<float>(kCmdMenuTransitionStepD * static_cast<f64>(timer));
		entries[selected].alpha = t;

		if (caravanWork->m_commandListExtra[selected + 1] == -1) {
			entries[selected + 1].alpha = t;
			if (caravanWork->m_commandListExtra[selected + 2] == -1) {
				entries[selected + 2].alpha = t;
			}
		}

		entries[static_cast<s32>(list->listEnd) + 3].alpha =
			static_cast<float>(-(kCmdMenuTransitionStepD * static_cast<f64>(timer) - kCmdMenuOneD));

		done = static_cast<u32>(static_cast<f64>(timer) >= kCmdMenuTransitionFramesD);
		if ((done != 0) && (cmd->commandResult != 0)) {
			cmd->commandResult = 0;
			if (cmd->choice == 0) {
				cmd->uniteState = 1;
				done = 0;
			} else if ((static_cast<double>(entries[static_cast<s32>(list->listEnd) + 3].scale) ==
			            kCmdMenuOneD) && (cmd->choice == 1)) {
				cmd->uniteState = 2;
				done = 0;
			}
		}
		if (done != 0) {
			cmd->commandResult = 0;
		}
	} else if (state == 1) {
		const s16 selected = cmd->selected;
		s32 uniteIdx = 0;
		s32 topCount = s_unitePanelCount;
		for (; uniteIdx < topCount; uniteIdx++) {
			if (s_UniteTop[uniteIdx] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx) != 0);
		if (done != 0) {
			s32 ununiteCount = 1;
			if (caravanWork->m_commandListExtra[selected + 1] == -1) {
				ununiteCount = 2;
				if (caravanWork->m_commandListExtra[selected + 2] == -1) {
					ununiteCount = 3;
				}
			}
			caravanWork->UnuniteComList(selected, ununiteCount);
		}
	} else if (state == 2) {
		const s16 selected = cmd->selected;
		int combo[2][2];
		const s32 count = ChkUnite(static_cast<int>(selected), combo);
		if (count == 1) {
			done = 0;
			cmd->uniteState = 3;
		} else {
			done = 1;
			cmd->commandResult = 1;
		}
	} else if (state == 3) {
		const s16 selected = cmd->selected;
		s32 uniteIdx = 0;
		s32 topCount = s_unitePanelCount;
		for (; uniteIdx < topCount; uniteIdx++) {
			if (s_UniteTop[uniteIdx] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx) != 0);
		if (done != 0) {
			int combo[2][2];
			ChkUnite(static_cast<int>(selected), combo);

			s32 ununiteCount = 1;
			if (caravanWork->m_commandListExtra[selected + 1] == -1) {
				ununiteCount = 2;
				if (caravanWork->m_commandListExtra[selected + 2] == -1) {
					ununiteCount = 3;
				}
			}

			caravanWork->UnuniteComList(selected, ununiteCount);
			caravanWork->UniteComList(combo[0][1], GetUniteRecipeCount(combo[0][0]), GetUniteRecipeCmd(combo[0][0]));

			done = 0;
			cmd->selected = static_cast<s16>(combo[0][1]);
			cmd->uniteState = 4;
		}
	} else if (state == 4) {
		done = static_cast<u32>(UniteOpenAnim(-1) != 0);
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
	CmdState* const cmd = GetCmdStateView(this);
	CmdListStorage* const list = GetCmdListStorage(this);
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

	const s32 selected = static_cast<s32>(cmd->selected);
	const s32 modeSel = static_cast<s32>(GetCmdStateSelections(cmd)[cmd->mode]);

	cmd->transitionTimer = static_cast<s16>(cmd->transitionTimer + 1);

	switch (cmd->uniteState) {
	case 0:
		cmd->transitionTimer = 0;
		if (cmd->commandResult < 0) {
			cmd->uniteState = 3;
		} else if (caravanWork->m_commandListExtra[selected] == 0) {
			cmd->uniteState = 2;
		} else {
			cmd->uniteState = 1;
		}
		return 0;
	case 1: {
		s32 uniteIdx = 0;
		for (; uniteIdx < s_unitePanelCount; uniteIdx++) {
			if (s_UniteTop[uniteIdx] == selected) {
				break;
			}
		}

		if (UniteCloseAnim(uniteIdx) != 0) {
			int combo[2][2];
			ChkUnite(selected, combo);

			s32 comboIdx = 0;
			if (combo[0][1] < combo[1][1]) {
				comboIdx = (combo[0][1] == modeSel) ? 0 : 1;
			} else {
				comboIdx = (combo[1][1] == modeSel) ? 1 : 0;
			}

			s32 ununiteCount = 1;
			if (caravanWork->m_commandListExtra[selected + 1] == -1) {
				ununiteCount = 2;
				if (caravanWork->m_commandListExtra[selected + 2] == -1) {
					ununiteCount = 3;
				}
			}

			caravanWork->UnuniteComList(selected, ununiteCount);
			caravanWork->UniteComList(
			    combo[comboIdx][1], GetUniteRecipeCount(combo[comboIdx][0]), GetUniteRecipeCmd(combo[comboIdx][0]));
			cmd->selected = static_cast<s16>(combo[comboIdx][1]);
			cmd->uniteState = 2;
		}
		return 0;
	}
	case 2:
		if (caravanWork->m_commandListExtra[selected] == 0) {
			int combo[2][2];
			ChkUnite(selected, combo);

			s32 comboIdx = 0;
			if (combo[0][1] < combo[1][1]) {
				comboIdx = (combo[0][1] == modeSel) ? 0 : 1;
			} else {
				comboIdx = (combo[1][1] == modeSel) ? 1 : 0;
			}

			caravanWork->UniteComList(
				combo[comboIdx][1], GetUniteRecipeCount(combo[comboIdx][0]), GetUniteRecipeCmd(combo[comboIdx][0]));
			cmd->selected = static_cast<s16>(combo[comboIdx][1]);
		} else if (UniteOpenAnim(-1) != 0) {
			cmd->uniteState = 3;
		}
		return 0;
	case 3:
		for (s32 i = 0; i < static_cast<s32>(list->count); i++) {
			CmdListEntry* entry = &list->entries[i];
			if (static_cast<f64>(entry->alpha) < kCmdMenuOneD) {
				entry->alpha = static_cast<f32>((kCmdMenuAlphaStepD * static_cast<f64>(cmd->transitionTimer)) + kCmdMenuHalfD);
				if (static_cast<f64>(entry->alpha) > kCmdMenuOneD) {
					entry->alpha = kCmdMenuOne;
				}
			}
		}
		return static_cast<u32>(static_cast<f64>(cmd->transitionTimer) >= kCmdMenuTransitionFramesD);
	default:
		return 0;
	}
}

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
