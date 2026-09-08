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

static s32 s_unitePanelCount;
static s32 s_UniteTop[3];

struct UniteRecipe {
    s16 food;
    s16 command;
    s16 count;
    s16 ingredients[3];
};

STATIC_ASSERT(sizeof(UniteRecipe) == 12);

static const UniteRecipe s_Unite[] = {
    { 0x0000, 0x022A, 0x0003, { 0x0107, 0x0105, 0x0105 } },
    { 0x0001, 0x0207, 0x0002, { 0x0100, 0x03E7, 0x0000 } },
    { 0x0001, 0x020B, 0x0002, { 0x0101, 0x03E7, 0x0000 } },
    { 0x0001, 0x020F, 0x0002, { 0x0102, 0x03E7, 0x0000 } },
    { 0x0000, 0x0230, 0x0003, { 0x0100, 0x0100, 0x0100 } },
    { 0x0000, 0x0231, 0x0003, { 0x0101, 0x0101, 0x0101 } },
    { 0x0000, 0x0232, 0x0003, { 0x0102, 0x0102, 0x0102 } },
    { 0x0000, 0x0208, 0x0002, { 0x0100, 0x0100, 0x0000 } },
    { 0x0000, 0x020C, 0x0002, { 0x0101, 0x0101, 0x0000 } },
    { 0x0000, 0x0210, 0x0002, { 0x0102, 0x0102, 0x0000 } },
    { 0x0000, 0x0226, 0x0002, { 0x0100, 0x0101, 0x0000 } },
    { 0x0000, 0x0226, 0x0002, { 0x0100, 0x0102, 0x0000 } },
    { 0x0000, 0x0226, 0x0002, { 0x0101, 0x0100, 0x0000 } },
    { 0x0000, 0x0226, 0x0002, { 0x0101, 0x0102, 0x0000 } },
    { 0x0000, 0x0226, 0x0002, { 0x0102, 0x0100, 0x0000 } },
    { 0x0000, 0x0226, 0x0002, { 0x0102, 0x0101, 0x0000 } },
    { 0x0000, 0x0221, 0x0002, { 0x0100, 0x0107, 0x0000 } },
    { 0x0000, 0x0221, 0x0002, { 0x0101, 0x0107, 0x0000 } },
    { 0x0000, 0x0221, 0x0002, { 0x0102, 0x0107, 0x0000 } },
    { 0x0000, 0x0214, 0x0002, { 0x0107, 0x0100, 0x0000 } },
    { 0x0000, 0x0214, 0x0002, { 0x0107, 0x0101, 0x0000 } },
    { 0x0000, 0x0214, 0x0002, { 0x0107, 0x0102, 0x0000 } },
    { 0x0000, 0x023E, 0x0003, { 0x0107, 0x0100, 0x0101 } },
    { 0x0000, 0x023E, 0x0003, { 0x0107, 0x0100, 0x0102 } },
    { 0x0000, 0x023E, 0x0003, { 0x0107, 0x0101, 0x0100 } },
    { 0x0000, 0x023E, 0x0003, { 0x0107, 0x0101, 0x0102 } },
    { 0x0000, 0x023E, 0x0003, { 0x0107, 0x0102, 0x0100 } },
    { 0x0000, 0x023E, 0x0003, { 0x0107, 0x0102, 0x0101 } },
    { -1, -1, -1, { -1, -1, -1 } },
};

static const char* s_SkillStr_us[] = {
    "Flamestrike",
    "Icestrike",
    "Thunderstrike",
    "",
    "",
};

static const char* s_SkillStr_ge[] = {
    "Feuer-Hieb",
    "Eis-Hieb",
    "Blitz-Hieb",
    "",
    "",
};

static const char* s_SkillStr_it[] = {
    "Colpo Fire",
    "Colpo Blizzard",
    "Colpo Thunder",
    "",
    "",
};

static const char* s_SkillStr_fr[] = {
    "Pyro-Frappe",
    "Cryo-Frappe",
    "Rh\351o-Frappe",
    "",
    "",
};

static const char* s_SkillStr_sp[] = {
    "Efecto Fuego",
    "Efecto Hielo",
    "Efecto Electro",
    "",
    "",
};
namespace {

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
STATIC_ASSERT(offsetof(CmdState, selected[0]) == 0x26);
STATIC_ASSERT(offsetof(CmdState, selected[1]) == 0x28);
STATIC_ASSERT(offsetof(CmdState, selected[2]) == 0x2A);
STATIC_ASSERT(offsetof(CmdState, selected[3]) == 0x2C);
STATIC_ASSERT(offsetof(CmdState, mode) == 0x30);
STATIC_ASSERT(offsetof(CmdState, prevMode) == 0x32);
STATIC_ASSERT(offsetof(CmdState, scrollTop) == 0x34);
STATIC_ASSERT(sizeof(CmdState) == 0x36);

static inline CmdListStorage* GetCmdList(CMenuPcs* menu)
{
	return menu->m_cmdList;
}

static inline CmdListStorage* GetCmdListStorage(CMenuPcs* menu)
{
	return GetCmdList(menu);
}

static inline CmdListEntry* GetCmdListEntries(CMenuPcs* menu)
{
	return GetCmdListStorage(menu)->entries;
}

static inline CmdState* GetCmdStateView(CMenuPcs* menu)
{
	return menu->m_cmdState;
}

static inline s16* GetCmdStateSelections(CmdState* cmd)
{
	return cmd->selected;
}

static inline s16 GetCmdLayoutFlag(CMenuPcs* menu)
{
	return menu->m_cmdLayoutFlag;
}

static inline s16 GetUniteRecipeCmd(int recipe)
{
	return s_Unite[recipe].command;
}

static inline s16 GetUniteRecipeCount(int recipe)
{
	return s_Unite[recipe].count;
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
	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	memset(GetCmdListStorage(this), 0, sizeof(*GetCmdListStorage(this)));

	CmdListEntry* entry = GetCmdListEntries(this);
	for (s32 i = 0; i < 64; i++, entry++) {
		entry->scale = 1.0f;
	}

	entry = GetCmdListEntries(this);
	float fVar3 = 0.0f;
	float fVar4 = 8.0f;
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
	GetCmdStateView(this)->selected[0] = 2;
	GetCmdStateView(this)->initialized = 1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 356b
 * EN Address: 0x8016D928
 * EN Size: 188b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmdInit0()
{
	CmdListStorage* list = GetCmdListStorage(this);
	CmdListEntry* entries = list->entries;

	for (s32 i = 0; i < list->count; i++) {
		entries[i].alpha = 1.0f;
		entries[i].scale = 1.0f;
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
	s16 y = 0;
	s32 tex = 0x2f;
	s32 idx = static_cast<s32>(GetCmdListStorage(this)->count);
	CmdListEntry* entry;

	entry = &GetCmdListStorage(this)->entries[idx++];
	entry->tex = 0x2e;
	entry->x = 0xb8;
	entry->y = 0x28;
	entry->width = 0x78;
	entry->height = 0x108;
	entry->u = 128.0f;
	entry->v = 8.0f;
	entry->scale = 1.0f;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &GetCmdListStorage(this)->entries[idx++];
	if (GetCmdLayoutFlag(this) == 0) {
		tex = 0x46;
	}
	entry->tex = tex;
	entry->x = 0xa0;
	entry->y = 0xe;
	entry->width = 0x30;
	entry->height = 0x30;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->scale = 1.0f;
	entry->startFrame = 0;
	entry->duration = 5;

	tex = 0x2f;
	entry = &GetCmdListStorage(this)->entries[idx++];
	if (GetCmdLayoutFlag(this) == 0) {
		tex = 0x46;
	}
	entry->tex = tex;
	entry->width = 0x30;
	entry->height = 0x30;
	entry->x = 0xa5;
	entry->y = static_cast<s16>(0x150 - entry->height);
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->scale = 0.75f;
	entry->startFrame = y;
	entry->duration = 5;

	entry = &GetCmdListStorage(this)->entries[idx++];
	entry->flags = 2;
	entry->tex = 0x2e;
	entry->x = 0xa0;
	entry->y = 8;
	entry->width = 0x48;
	entry->height = 0x140;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->startFrame = y;
	entry->duration = 5;

	CmdListEntry* basePanel = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count];
	for (s32 i = 0; i < 8; i++) {
		entry = &GetCmdListStorage(this)->entries[idx++];
		entry->flags = 2;
		entry->tex = 0x37;
		entry->x = static_cast<s16>(basePanel->x + 0x24);
		entry->y = static_cast<s16>(basePanel->y + y);
		entry->width = 200;
		entry->height = 0x28;
		entry->u = 0.0f;
		entry->v = 0.0f;
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
		fillEntry->alpha = 0.0f;
		fillEntry++;
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
	const float alpha = 1.0f;
	k = static_cast<s32>(list->listEnd) - k;
	for (; k > 0; k--) {
		fillEntry->timer = 0;
		fillEntry->alpha = alpha;
		fillEntry++;
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
	if (m_cmdState->initialized == 0) {
		CmdInit();
	}

	CmdListEntry* entry;
	s32 finishedCount = 0;
	m_cmdState->transitionTimer = static_cast<s16>(m_cmdState->transitionTimer + 1);

	CmdListStorage* list = m_cmdList;
	const s32 entryCount = list->count;
	entry = list->entries;
	const s32 timer = static_cast<s32>(m_cmdState->transitionTimer);

	for (s32 i = 0; i < entryCount; i++) {
		if (entry->startFrame <= timer) {
			if ((entry->startFrame + entry->duration) <= timer) {
				finishedCount += 1;
				entry->alpha = 1.0f;
			} else {
				entry->timer++;
				f64 durationD = static_cast<double>(entry->duration);
				f64 timerD = static_cast<double>(entry->timer);
				entry->alpha = static_cast<float>((1.0 / durationD) * timerD);
			}
		}
		entry++;
	}

	int done = 0;
	CmdListStorage* const list2 = m_cmdList;
	if (list2->count == finishedCount) {
		float anim = 1.0f;
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
		actionHandled = CmdOpen2();
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
			entry->alpha = 1.0f;
			entry->scale = 1.0f;
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
	s32 hasItemHelp = false;
	s32 helpId;
	float rowU;
	float rowH;
	float t;
	float x;
	float y;
	float w;
	GXColor colors[4];

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	CCaravanWork* const caravan = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	const s32 animState = m_cmdState->animState;
	const s32 cmdMode = m_cmdState->mode;

	CmdListEntry* entry = m_cmdList->entries;
	for (s32 i = 0; i < m_cmdList->count; i++, entry++) {
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
					t = 8.0f + h;
				} else {
					t = 8.0f;
				}
				if ((animState == 1) && (i < caravan->m_numCmdListSlots) &&
				    (i == m_cmdState->selected[0])) {
					t = 72.0f;
					y -= 8.0f;
					h += 8.0f;
				}

				colors[0].r = 0xFF;
				colors[0].g = 0xFF;
				colors[0].b = 0xFF;
				colors[0].a = static_cast<u8>(255.0f * entry->alpha);
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);

				MenuPcs.DrawRect(
				    0, x, y, w, h, u, t, entry->scale, entry->scale, 0.0f);
			}
		}
	}

	CFont* nameFont = m_fonts[4];
	nameFont->SetMargin(1.0f);
	nameFont->SetShadow(0);
	nameFont->SetScale(0.9f);
	nameFont->DrawInit();

	CmdListEntry* nameEntry = m_cmdList->entries;
	for (s32 i = 0; i < caravan->m_numCmdListSlots; i++, nameEntry++) {
		if ((i >= 8) || (caravan->m_commandListExtra[i] == 0)) {
			nameFont->SetColor(
			    CColor(0xFF, 0xFF, 0xFF,
			        static_cast<u8>(255.0f *
			            static_cast<float>(cmdMode == 3 ? 1.0 : static_cast<double>(nameEntry->alpha))))
			        .color);

			const char* text;
			if (i < 2) {
				text = GetMenuStr(i + 9);
			} else {
				const int cmdId = caravan->m_commandListInventorySlotRef[i];
				if (cmdId >= 0) {
					const int skillId = caravan->m_inventoryItems[cmdId];
					char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
					text = flatText[skillId * 5 + 4];
					if ((m_cmdState->mode == 0) && (i == m_cmdState->selected[0])) {
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
			nameFont->SetPosY(y - 4.0f);
			nameFont->Draw(text);
		}
	}

	DrawInit();
	DrawUniteList();

	CmdListEntry* iconEntry = m_cmdList->entries;
	for (s32 i = 0; i < caravan->m_numCmdListSlots; i++, iconEntry++) {
		if ((i >= 2) && (caravan->m_commandListInventorySlotRef[i] >= 0)) {
			y = static_cast<float>(iconEntry->y - 2);
			x = static_cast<float>(iconEntry->x + iconEntry->width - 0x10);
			DrawSingleIcon(
			    caravan->m_inventoryItems[caravan->m_commandListInventorySlotRef[i]],
			    static_cast<s32>(static_cast<float>(iconEntry->x + iconEntry->width - 0x10)),
			    static_cast<s32>(y - 1.0f), iconEntry->alpha, 0, 1.0f);
		}
	}

	if (m_cmdState->prevMode != 0) {
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		CmdListEntry* row = &m_cmdList->entries[m_cmdList->count];
		const s16* letterBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const s32 itemCount = letterBuf[0];
		s32 specialRow = 0;
		for (s32 idx = m_cmdList->count; idx < m_cmdList->listEnd; idx++, row++) {
			const s32 tex = row->tex;
			if (tex >= 0) {
				x = static_cast<float>(row->x);
				y = static_cast<float>(row->y);
				w = static_cast<float>(row->width);
				rowH = static_cast<float>(row->height);
				rowU = row->u;
				t = row->v;

				if (idx == m_cmdList->count) {
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
					if (w > 0.0f) {
						MenuPcs.DrawRect(0, x, y, w, rowH, rowU, t, colors,
						    1.0f, 1.0f, 0.0f);
						x += w;
						rowU += w;
					}
					if ((w > 0.0f) && (w < static_cast<float>(row->width))) {
						colors[1].r = 0xFF;
						colors[1].g = 0xFF;
						colors[1].b = 0xFF;
						colors[1].a = 0;
						colors[3].r = 0xFF;
						colors[3].g = 0xFF;
						colors[3].b = 0xFF;
						colors[3].a = 0;
						w = static_cast<float>(
						    1.0 / static_cast<double>(row->duration));
						w *= static_cast<float>(row->width);
						MenuPcs.DrawRect(0, x, y, w, rowH, rowU, t, colors,
						    1.0f, 1.0f, 0.0f);
					}

					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				} else {
					float rowAlpha = row->alpha;
					s32 rowTex = tex;
					if (tex == 0x37) {
						s32 sel = specialRow + m_cmdState->scrollTop;
						if ((itemCount >= 8) && (sel >= itemCount)) {
							sel -= itemCount;
						}

						if (sel < 2) {
							const CCaravanWork* const caravan2 =
							    reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
							const s16* canBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
							const s16* canItems = canBuf + 1;
							u8 canUse;
							if ((sel < 0) || (sel >= canBuf[0])) {
								canUse = 0;
							} else if (sel == 0) {
								canUse = static_cast<u32>(
								    caravan2->m_commandListInventorySlotRef[m_cmdState->selected[0]] >= 0);
							} else if (sel == 1) {
								int combo[5][2];
								canUse = static_cast<u32>(
								    ChkUnite(m_cmdState->selected[0], combo) != 0);
							} else {
								canUse = static_cast<u32>(static_cast<u8>(EquipChk(static_cast<int>(canItems[sel - 2]))) == 0);
							}

							if (canUse == 0) {
								rowAlpha = 0.5 * row->alpha;
								rowTex = 0x34;
							}
						} else {
							s32 itemIdx = sel - 2;
							if ((itemCount >= 8) && (itemIdx >= itemCount)) {
								itemIdx -= itemCount;
							}

							int equippable = 1;
							if (itemIdx + 2 < itemCount) {
								equippable = EquipChk(static_cast<int>(letterBuf[itemIdx + 1]));
							}

							if (static_cast<u8>(equippable) != 0) {
								if (itemIdx + 2 < itemCount) {
									DrawEquipMark(static_cast<s32>(x - 12.0f),
									    static_cast<s32>(((rowH - 24.0f) * 0.5) + y),
									    row->alpha);
								}
								rowTex = 0x34;
								rowAlpha = 0.5 * row->alpha;
							}
						}

						if ((rowTex == 0x37) &&
						    (specialRow == m_cmdState->selected[1])) {
							t += rowH;
						}
						specialRow++;
					}

					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(rowTex));

					colors[0].r = 0xFF;
					colors[0].g = 0xFF;
					colors[0].b = 0xFF;
					colors[0].a = static_cast<u8>(255.0f * rowAlpha);
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);

					MenuPcs.DrawRect(0, x, y, w, rowH, rowU, t, row->scale,
					    row->scale, 0.0f);
				}
			}
		}
	}

	if (cmdMode == 1) {
		CFont* listFont = m_fonts[4];
		listFont->SetMargin(1.0f);
		listFont->SetShadow(0);
		listFont->SetScale(0.9f);
		listFont->DrawInit();

		const s16* letterBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const s32 itemCount = letterBuf[0];
		CmdListEntry* scan = &m_cmdList->entries[m_cmdList->count];
		for (s32 idx = m_cmdList->count; idx < m_cmdList->listEnd; idx++) {
			if (scan->tex == 0x37) {
				break;
			}
			scan++;
		}

		CmdListEntry* textRow = scan;
		for (s32 row = 0; row < 8; row++, textRow++) {
			if ((itemCount <= 8) && (row + m_cmdState->scrollTop >= itemCount)) {
				break;
			}

			s32 displayIdx =  (s32)(row + m_cmdState->scrollTop);
			if (displayIdx >= itemCount) {
				displayIdx -= itemCount;
			}

			const float alpha = textRow->alpha;
			listFont->SetColor(
			    CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)).color);

			const char* text;
			if (displayIdx < 2) {
				text = GetMenuStr(displayIdx + 0x0B);
			} else if (!(displayIdx >= itemCount)) {
				const s16 slot = letterBuf[displayIdx - 1];
				const s16 skillId = caravan->m_inventoryItems[slot];
				char** flatText = Game.m_cFlatDataArr[1].TableStrings(0);
				text = flatText[skillId * 5 + 4];

				s32 selDisp = m_cmdState->selected[1] + m_cmdState->scrollTop;
				if (selDisp >= itemCount) {
					selDisp -= itemCount;
				}
				if (displayIdx == selDisp) {
					helpId = skillId;
					hasItemHelp = true;
				}
			} else {
				continue;
			}

			listFont->GetWidth(text);
			x = static_cast<float>(textRow->x + 0x1C);
			y = static_cast<float>(textRow->y + 0x0B);
			listFont->SetPosX(static_cast<float>(textRow->x + 0x1C));
			listFont->SetPosY(y - 4.0f);
			listFont->Draw(text);
		}

		DrawInit();

		CmdListEntry* iconRow = scan;
		for (s32 row = 0; row < 8; row++, iconRow++) {
			if ((itemCount <= 8) && (row + m_cmdState->scrollTop >= itemCount)) {
				break;
			}

			s32 displayIdx = row + m_cmdState->scrollTop;
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
				    static_cast<s32>(y - 1.0f),
				    iconRow->alpha, 0, 1.0f);
			}
		}
	}

	if ((cmdMode == 1) && (m_cmdState->phase == 1)) {
		CmdListEntry* listPos = &m_cmdList->entries[m_cmdList->count];
		const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const float mark = CalcListPos(m_cmdState->scrollTop, letter[0], 1);
		if (mark > 0.0f) {
			DrawListPosMark(static_cast<float>(listPos->x), static_cast<float>(listPos->y), mark);
		}
	}

	if (cmdMode == 2) {
		CmdListEntry* panel = &m_cmdList->entries[m_cmdList->listEnd + 3];
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(panel->tex));

		colors[0].r = 0xFF;
		colors[0].g = 0xFF;
		colors[0].b = 0xFF;
		colors[0].a = static_cast<u8>(255.0f * panel->alpha);
		GXSetChanMatColor(GX_COLOR0A0, colors[0]);
		MenuPcs.DrawRect(
		    0, static_cast<float>(panel->x), static_cast<float>(panel->y),
		    static_cast<float>(panel->width), static_cast<float>(panel->height),
		    panel->u, panel->v, 1.0f, panel->scale, 0.0f);

		CFont* choiceFont = m_fonts[0];
		choiceFont->SetMargin(1.0f);
		choiceFont->SetShadow(1);
		choiceFont->SetScale(0.9f);
		choiceFont->DrawInit();
		choiceFont->SetTlut(7);
		choiceFont->SetColor(
		    CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * panel->alpha)).color);

		const s32 choices = (1.0 == static_cast<double>(panel->scale)) ? 2 : 3;
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
			    ((static_cast<float>(panel->height) * panel->scale) - 16.0) /
			    choices);
			y = ((pitch * static_cast<float>(choice)) + static_cast<float>(panel->y + 8)) +
			    ((pitch - 19.8) * 0.5);
			x = static_cast<float>(panel->x + 0x18);
			choiceFont->SetPosX(static_cast<float>(panel->x + 0x18));
			choiceFont->SetPosY(y - 4.0f);
			choiceFont->Draw(text);
		}
		DrawInit();
	}

	CmdListEntry* cursorEntry;
	s32 cursorOnUnite = false;
	if (((cmdMode == 0) && (animState == 1)) ||
	    ((cmdMode != 0) && (m_cmdState->phase == 1))) {

		if ((cmdMode == 0) || (cmdMode == 3)) {
			s32 index = m_cmdState->selected[cmdMode];
			if (!(caravan->m_commandListExtra[index] == 0)) {
				s32 uniteIdx;
				for (uniteIdx = 0; uniteIdx < s_unitePanelCount; uniteIdx++) {
					if (s_UniteTop[uniteIdx] == index) {
						break;
					}
				}
				cursorEntry = &m_cmdList->entries[m_cmdList->listEnd + uniteIdx];
				cursorOnUnite = true;
			} else {
				cursorEntry = &m_cmdList->entries[index];
			}
		} else if (cmdMode == 1) {
			CmdListStorage* const list = m_cmdList;
			for (s32 idx = list->count; idx < list->listEnd; idx++) {
				cursorEntry = &list->entries[idx];
				if (cursorEntry->tex == 0x37) {
					break;
				}
			}
			cursorEntry = cursorEntry + m_cmdState->selected[1];
		} else {
			CmdListEntry* panel = &m_cmdList->entries[m_cmdList->listEnd + 3];
			const s32 choices = (1.0 == static_cast<double>(panel->scale)) ? 2 : 3;
			const float pitch = static_cast<float>(
			    ((static_cast<float>(panel->height) * panel->scale) - 16.0) /
			    static_cast<double>(choices));
			x = static_cast<float>(panel->x - 0x14);
			y = ((pitch - 19.8) * 0.5) +
			    ((pitch * static_cast<float>(m_cmdState->selected[2])) + static_cast<float>(panel->y + 8));
		}

		if (cmdMode != 2) {
			if (!cursorOnUnite) {
				x = static_cast<float>(cursorEntry->x - 0x14);
				y = static_cast<float>(cursorEntry->y);
				if (m_cmdState->mode != 0) {
					y += 8.0f;
				}
			} else {
				y = (cursorEntry->height - 0x20) * 0.5 + cursorEntry->y;
				x = static_cast<float>(cursorEntry->x - 0x14);
			}
		}

		const s32 frame = static_cast<s32>(System.m_frameCounter) % 8;
		x += static_cast<float>(frame);
		DrawCursor(static_cast<s32>(x), static_cast<s32>(y), 1.0f);
	}

	const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	s32 idx = m_cmdState->selected[1] + m_cmdState->scrollTop;
	if (idx >= letter[0]) {
		idx -= letter[0];
	}

	CFont* helpFont = m_fonts[0];
	int helpAlpha = static_cast<int>(
	    255.0f * m_cmdList->entries[m_cmdList->count].alpha);
	if (!hasItemHelp) {
		helpId = -1;
	}

	const s16 mode = m_cmdState->mode;
	if (mode == 0) {
		if (helpId == -1) {
			if (caravan->m_commandListExtra[m_cmdState->selected[0]] == 0) {
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
		if (m_cmdState->selected[2] == 0) {
			helpId = 0x25B;
		} else {
			helpId = -1;
		}
	}
	if ((mode == 0) || (mode == 2)) {
		helpAlpha = static_cast<int>(255.0f * m_cmdList->entries[0].alpha);
	}

	float helpX = static_cast<float>(-(w * 0.5f - 320.0f));
	float helpY = 352.0f;
	DrawHelpMessage(
	    helpId, helpFont, static_cast<int>(helpX), static_cast<int>(helpY),
	    CColor(0xFF, 0xFF, 0xFF, helpAlpha).color, 10,
	    1.0f, 3.0f);
}

/*
 * --INFO--
 * PAL Address: 0x8014d274
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
	press = Pad.GetButtonDown(0);
	hold = Pad.GetButtonRepeat(0);

	if (hold == 0) {
		return 0;
	}

	s32 mode = GetCmdStateView(this)->mode;

	if (mode == 0) {
		const s32 cmdCount = caravanWork->m_numCmdListSlots;

		if ((hold & 8) != 0) {
			CmdState* row = GetCmdStateView(this);
			if (row->selected[mode] > 2) {
				row->selected[mode]--;
			} else {
				row->selected[mode] = static_cast<s16>(cmdCount - 1);
			}

			CmdState* row2 = GetCmdStateView(this);
			const int cursor = row2->selected[mode];
			if (caravanWork->m_commandListExtra[cursor] < 0) {
				const int m1 = cursor - 1;
				if (caravanWork->m_commandListExtra[m1] >= 0) {
					row2->selected[mode] = static_cast<s16>(m1);
				} else {
					const int m2 = cursor - 2;
					if (caravanWork->m_commandListExtra[m2] >= 0) {
						row2->selected[mode] = static_cast<s16>(m2);
					}
				}
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else {
			if ((hold & 4) != 0) {
				CmdState* row = GetCmdStateView(this);
				if (row->selected[mode] < cmdCount - 1) {
					row->selected[mode]++;
				} else {
					row->selected[mode] = 2;
				}

				CmdState* row2 = GetCmdStateView(this);
				const int cursor = row2->selected[mode];
				if (caravanWork->m_commandListExtra[cursor] < 0) {
					const int p1 = cursor + 1;
					if (caravanWork->m_commandListExtra[p1] >= 0) {
						row2->selected[mode] = static_cast<s16>(p1);
					} else {
						const int p2 = cursor + 2;
						if (caravanWork->m_commandListExtra[p2] >= 0) {
							row2->selected[mode] = static_cast<s16>(p2);
						}
					}
					CmdState* row3 = GetCmdStateView(this);
					if (row3->selected[mode] > cmdCount - 1) {
						row3->selected[mode] = 2;
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
				if (!(caravanWork->m_commandListExtra[GetCmdStateView(this)->selected[mode]] == 0)) {
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
			CmdState* row = sv1;
			if (!(row->selected[mode] == 0)) {
				row->selected[mode]--;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				if (itemCount <= 8) {
					row->selected[mode] = static_cast<s16>(itemCount - 1);
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
				if (((itemCount > 8) && (GetCmdStateView(this)->selected[mode] < 7)) ||
				    ((itemCount <= 8) &&
				     (GetCmdStateView(this)->selected[mode] < itemCount - 1))) {
					GetCmdStateView(this)->selected[mode]++;
				} else {
					if (itemCount <= 8) {
						GetCmdStateView(this)->selected[mode] = 0;
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
				               static_cast<int>(GetCmdStateView(this)->selected[mode]);
				if (selected >= itemCount) {
					selected -= itemCount;
				}

				CCaravanWork* const cw = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
				s16* const list2 = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
				const int itemCount2 = list2[0];
				s16* const items = list2 + 1;

				bool canUse;
				if ((selected < 0) || (selected >= itemCount2)) {
					canUse = false;
				} else if (selected == 0) {
					canUse = cw->m_commandListInventorySlotRef[GetCmdStateView(this)->selected[0]] >= 0;
				} else if (selected == 1) {
					canUse = (ChkUnite(GetCmdStateView(this)->selected[0], combo) != 0);
				} else {
					canUse = static_cast<u8>(EquipChk(static_cast<int>(items[selected - 2]))) == 0;
				}

				if (canUse) {
					if (selected == 0) {
						caravanWork->ChgCmdLst(GetCmdStateView(this)->selected[0], -1);
					} else if (selected != 1) {
						caravanWork->ChgCmdLst(GetCmdStateView(this)->selected[0], list[selected - 1]);
					}

					GetCmdStateView(this)->commandResult = 0;
					if (selected != 0) {
						int comboCount;
						comboCount = ChkUnite(GetCmdStateView(this)->selected[0], comboChoice);
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
	} else if (mode == 2) {
		CmdListStorage* cmdList = GetCmdListStorage(this);
		const int animSlot = cmdList->listEnd + 3;
		int maxPos;
		if (1.0 ==
		    static_cast<double>(cmdList->entries[animSlot].scale)) {
			maxPos = 2;
		} else {
			maxPos = 3;
		}

		if (!((hold & 8) == 0)) {
			CmdState* row = GetCmdStateView(this);
			if (!(row->selected[mode] == 0)) {
				row->selected[mode]--;
			} else {
				row->selected[mode] = static_cast<s16>(maxPos - 1);
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else {
			if ((hold & 4) != 0) {
				CmdState* row = GetCmdStateView(this);
				if (row->selected[mode] < maxPos - 1) {
					row->selected[mode]++;
				} else {
					row->selected[mode] = 0;
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
			const int selected = sv0->selected[0];
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

			CmdState* row = sv0;
			if (row->selected[mode] == prev) {
				row->selected[mode] = static_cast<s16>(next);
			} else {
				row->selected[mode] = static_cast<s16>(prev);
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
	const s32 sel = GetCmdStateView(this)->selected[0];
	CmdListEntry* selEntry = &GetCmdListStorage(this)->entries[sel];
	if (timer < 5) {
		selEntry->x = static_cast<s16>(selEntry->x - 0x13);
	}

	CmdListEntry* entry = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->count];
	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(GetCmdListStorage(this)->listEnd) - static_cast<s32>(GetCmdListStorage(this)->count);
	const float fVar1 = 0.0f;

	for (s32 i = 0; i < entryCount; i++) {
		if (timer >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= timer) {
				doneCount++;
				entry->alpha = 1.0f;
				entry->dx = fVar1;
				entry->dy = fVar1;
			} else {
				entry->timer++;
				const double step = 1.0 / static_cast<double>(entry->duration);
				entry->alpha = static_cast<float>(step * static_cast<double>(entry->timer));
				if ((entry->flags & 2) == 0) {
					const float t = static_cast<float>(
						(1.0 / static_cast<double>(entry->duration)) *
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
	const s32 sel = GetCmdStateView(this)->selected[0];
	CmdListEntry* selEntry = &GetCmdListStorage(this)->entries[sel];

	if (time > 7) {
		selEntry->x = static_cast<s16>(selEntry->x + 0x13);
	}

	s32 doneCount = 0;
	s32 count = static_cast<s32>(GetCmdListStorage(this)->count);
	s32 entryCount = static_cast<s32>(GetCmdListStorage(this)->listEnd) - count;
	CmdListEntry* entry = &GetCmdListStorage(this)->entries[count];

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
				    1.0 - ((1.0 / static_cast<f64>(entry->duration)) *
				           static_cast<f64>(entry->timer)));
				if ((entry->flags & 2) == 0) {
					const f32 t = static_cast<f32>(
					    1.0 - ((1.0 / static_cast<f64>(entry->duration)) *
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
		CmdListEntry* e = &GetCmdListStorage(this)->entries[GetCmdStateView(this)->selected[0]];
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
void CMenuPcs::GetCmdItem()
{
	s32 count;
	s16* list;
	const CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	s16* write = list;
	count = 0;
	s32 i = count;

	for (; i < CCaravanWork::kInventoryCapacity; i++) {
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
	for (s32 i = 0; i < 0x49; i++) {
		s32 arti = i + 0x9f;
		if (caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + i] == arti) {
			if (IsMagicArti(arti)) {
				count++;
				write2++;
				*write2 = static_cast<s16>(i + CCaravanWork::kPermanentArtifactStart);
			}
		}
	}

	write2 = list + count;
	for (s32 i = 0; i < CCaravanWork::kTemporaryArtifactCount; i++) {
		if (IsMagicArti(caravanWork->m_inventoryItems[CCaravanWork::kTemporaryArtifactStart + i])) {
			count++;
			write2++;
			*write2 = static_cast<s16>(CCaravanWork::kTemporaryArtifactStart + i);
		}
	}

	s16* out = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	*out = count + 2;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 248b
 * EN Address: 0x80171108
 * EN Size: 276b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::ChkCmdActive(int itemIndex)
{
	CmdState* const cmd = GetCmdStateView(this);
	cmd->commandResult = 0;

	const CCaravanWork* const caravan = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	const s16 selected = cmd->selected[0];
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
 * PAL Address: 0x8014c6bc
 * PAL Size: 1572b
 * EN Address: 0x8017121c
 * EN Size: 2192b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ChkUnite(int selected, int (*comboOut)[2])
{
	const CCaravanWork* const caravan = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);

	int itemKinds[10];
	int matches[5][2];
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
	const s32 selectedFlag = selectedState > 0 ? 1 : 0;

	if ((GetCmdStateView(this)->mode == 1) && (GetCmdStateView(this)->phase == 2)) {
		if (selectedState < 0) {
			selected--;
		}
		if (caravan->m_commandListExtra[selected] < 0) {
			selected--;
		}
	}

	memset(candidates, 0xff, sizeof(candidates));

	for (int slot = 2; slot < 8; slot++) {
		if (slot == selected) {
			if (caravan->m_commandListExtra[slot] == 0) {
				candidates[slot] = 0;
			} else {
				candidates[slot] = 0;
				candidates[++slot] = 0;
				if (caravan->m_commandListExtra[slot + 1] < 0) {
					candidates[++slot] = 0;
				}
			}
		} else {
			const s32 v = caravan->m_commandListExtra[slot];
			candidates[slot] = v != 0 ? -1 : 0;
		}
	}

	memset(itemKinds, 0xff, sizeof(itemKinds));

	for (int slot = 2; slot < 8; slot++) {
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
				itemKinds[slot] = 0x100;
			} else if (itemId == 0xe0) {
				itemKinds[slot] = 0x101;
			} else if (itemId == 0xe1) {
				itemKinds[slot] = 0x102;
			} else if (itemId == 0xe2) {
				itemKinds[slot] = 0x105;
			} else {
				itemKinds[slot] = 0x107;
			}
		} else if ((icon == 0) || (icon == 1) || (icon == 2) || (icon == 3)) {
			itemKinds[slot] = 999;
		} else if ((icon == 0x10) || (icon == 0x11)) {
			itemKinds[slot] = itemId;
		} else {
			itemKinds[slot] = -1;
		}
	}

	int matchCount;
	if (itemKinds[selected] <= 0) {
		return 0;
	}

	matchCount = 0;
	memset(matches, 0xff, sizeof(matches));

	if ((itemKinds[selected] == 999) && (selected > 2)) {
		int patIdx = 0;
		for (const UniteRecipe* pat = s_Unite; pat->command >= 0; pat++, patIdx++) {
			if (pat->food == 0) {
				continue;
			}
			const int len1 = pat->count;
			if ((len1 == 2) && (selectedFlag != 0)) {
				continue;
			}
			ok = 0;
			k = 0;
			for (; k < len1 - 1; k++) {
				const int slot = selected - (len1 - 1 - k);
				if (candidates[slot] != 0) {
					break;
				}
				if (pat->ingredients[k] == itemKinds[slot]) {
					ok++;
				}
			}
			if (ok == len1 - 1) {
				matches[matchCount][0] = patIdx;
				matches[matchCount][1] = selected - (len1 - 1);
				matchCount++;
			}
		}
	} else if (selectedFlag == 0) {
		const int baseLen = static_cast<int>(s_Unite[0].count);
		int start = selected - (baseLen - 1);
		for (int i = 0; i < baseLen; i++, start++) {
			ok = 0;
			k = 0;
			for (; k < baseLen; k++) {
				const int slot = i + (selected - ((baseLen - 1) - k));
				if (candidates[slot] != 0) {
					break;
				}
				if (s_Unite[0].ingredients[k] == itemKinds[slot]) {
					ok++;
				}
			}
			if (ok == baseLen) {
				matches[matchCount][0] = 0;
				matches[matchCount][1] = start;
				matchCount++;
			}
		}
	}

	int group = 1;
	for (const UniteRecipe* pat = s_Unite + 1; pat->command >= 0; pat++, group++) {
		if (((pat->food != 0) && (itemKinds[selected] == 999) && (selected > 2)) ||
		    ((pat->count == 2) && (selectedFlag != 0))) {
			continue;
		}

		const int len = pat->count;
		for (int start = 0; start < len; start++) {
			if ((start == 0) && (selectedFlag != 0)) {
				start++;
			}

			ok = 0;
			k = 0;
			for (; k < len; k++) {
				const int slot = start + (selected - ((len - 1) - k));
				if (candidates[slot] != 0) {
					break;
				}
				if (pat->ingredients[k] == itemKinds[slot]) {
					ok++;
				}
			}

			if (ok == len) {
				matches[matchCount][0] = group;
				matches[matchCount][1] = start + (selected - (len - 1));
				matchCount++;
			}
		}
	}

	int (*out)[2] = comboOut;
	for (int rank = 0; rank < 2; rank++) {
		for (int i = 0; i < matchCount; i++) {
			const int* m = matches[i];
			if (rank + 2 == s_Unite[m[0]].count) {
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
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: 0x80171AAC
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmdUnite(int selected, int comboIndex)
{
	int combo[5][2];
	const int comboCount = ChkUnite(selected, combo);
	if ((comboIndex < 0) || (comboIndex >= comboCount) || (combo[comboIndex][1] < 0)) {
		return;
	}

	const int recipe = combo[comboIndex][0];
	reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->UniteComList(
		combo[comboIndex][1], GetUniteRecipeCount(recipe), GetUniteRecipeCmd(recipe));
	GetCmdStateView(this)->selected[0] = static_cast<s16>(combo[comboIndex][1]);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 152b
 * EN Address: 0x80171B24
 * EN Size: 156b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmdDismantle(int selected)
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
	float drawH;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	CmdListEntry* unitePanels = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd];
	const s32 topX = GetCmdListStorage(this)->entries[0].x;
	s_unitePanelCount = 0;
	active = 0;

	for (i = 0; i < 8; i++) {
		if (i == GetCmdStateView(this)->selected[0]) {
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
		drawW = static_cast<float>(entry->width - 8);
		drawY = static_cast<float>(entry->y);
		const float rectU = static_cast<float>(entry->u);
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<u8>(255.0f * entry->alpha);
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

			if ((i <= GetCmdStateView(this)->selected[0]) && (GetCmdStateView(this)->selected[0] < i + groupSize)) {
				if ((GetCmdStateView(this)->phase == 3) && (i != GetCmdStateView(this)->selected[0])) {
					GetCmdStateView(this)->selected[0] = static_cast<s16>(i);
				}
				active = 1;
			}
		}

		CMenuPcs& menuPcsRef = MenuPcs;
		s32 barTex = 0x35;
		if (groupSize == 2) {
			barTex = 0x36;
		}
		menuPcsRef.SetTexture(static_cast<CMenuPcs::TEX>(barTex));
		MenuPcs.DrawRect(0,
			rectX,
			drawY - 8.0f,
			drawW,
			40.0f,
			rectU,
			active ? 40.0f : 0.0f,
			1.0f,
			1.0f,
			0.0f);
	}

	CFont* font = m_fonts[0];
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.9f);
	font->DrawInit();
	font->SetTlut(7);

	CmdListEntry* entry = GetCmdListStorage(this)->entries;
	for (i = 0; i < caravan->m_numCmdListSlots; i++, entry++) {
		if ((i < 8) && (caravan->m_commandListExtra[i] == 0)) {
			continue;
		}

		const float alpha = (GetCmdStateView(this)->mode == 3) ? 1.0f : entry->alpha;
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)).color);

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
			text = flatText[skillId * 5 + 4];
		}

		const float width = static_cast<float>(font->GetWidth(text));
		float x = static_cast<float>((static_cast<float>(entry->width) - width) * 0.5 +
		                             static_cast<double>(entry->x));
		if (topX != entry->x) {
			const float t = static_cast<float>(fabs(static_cast<double>(topX - entry->x)) * 0.015625);
			const float target = static_cast<float>(entry->x + entry->width - 0x18) - width;
			x = (target - x) * t + x;
		}

		drawY = static_cast<float>(entry->y + 3);
		font->SetPosX(x);
		font->SetPosY(drawY - 4.0f);
		font->Draw(text);
	}

	DrawInit();
	for (i = 0; i < 8; i++) {
		if (i == GetCmdStateView(this)->selected[0]) {
			active = 1;
		} else if (caravan->m_commandListExtra[i] >= 0) {
			active = 0;
		}

		if (i >= caravan->m_numCmdListSlots) {
			break;
		}

		const s16 slotType = caravan->m_commandListExtra[i];
		const int slotCheck = slotType;
		if (slotCheck == 0) {
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

			if ((i <= GetCmdStateView(this)->selected[0]) && (GetCmdStateView(this)->selected[0] < i + groupSize)) {
				active = 1;
			}
		}

		if (i != groupStart + groupSize - 1) {
			continue;
		}

		CmdListEntry* const endEntry = &GetCmdListStorage(this)->entries[i];
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x38));

		const s32 labelAnchor =
		    (groupStart == GetCmdStateView(this)->selected[0]) ? groupStart + 1 : groupStart;
		const float panelX =
		    static_cast<float>(topX - (GetCmdListStorage(this)->entries[labelAnchor].x - topX));
		drawW = 208.0f;
		drawH = 64.0f;
		const float panelTone = active ? 64.0f : 0.0f;
		CmdListEntry* const startEntry = &GetCmdListStorage(this)->entries[groupStart];
		drawY = static_cast<float>(
		    (static_cast<float>(endEntry->y + endEntry->height - startEntry->y) - 64.0f) *
		        0.5 +
		    static_cast<double>(startEntry->y));
		float panelAlpha;
		if (GetCmdStateView(this)->mode == 3) {
			panelAlpha = startEntry->alpha;
		} else {
			panelAlpha = static_cast<float>(
			    fabs(static_cast<double>(panelX - static_cast<float>(topX))) * 0.015625);
		}

		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<u8>(255.0f * panelAlpha);
		GXSetChanMatColor((_GXChannelID)4, color);

		unitePanels[s_unitePanelCount].x = static_cast<u16>(panelX);
		unitePanels[s_unitePanelCount].y = static_cast<s16>(drawY);
		unitePanels[s_unitePanelCount].width = static_cast<s16>(drawW);
		unitePanels[s_unitePanelCount].height = static_cast<s16>(drawH);
		unitePanels[s_unitePanelCount].u = 0.0f;
		unitePanels[s_unitePanelCount].v = panelTone;
		unitePanels[s_unitePanelCount].alpha = panelAlpha;
		s_UniteTop[s_unitePanelCount] = groupStart;
		s_unitePanelCount++;

		MenuPcs.DrawRect(0,
			panelX,
			drawY - 2.0f,
			208.0f,
			64.0f,
			0.0f,
			panelTone,
			1.0f,
			1.0f,
			0.0f);
	}

	font = m_fonts[0];
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(1.0f);
	font->DrawInit();
	font->SetTlut(6);

	for (i = 0; i < s_unitePanelCount; i++, unitePanels++) {
		const float alpha = (GetCmdStateView(this)->mode == 3) ? 1.0f : unitePanels->alpha;
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)).color);

		const int itemId = caravan->m_commandListExtra[s_UniteTop[i]];
		const char* text;
		if (itemId == 0x207) {
			text = GetSkillStr(0);
		} else if (itemId == 0x20B) {
			text = GetSkillStr(1);
		} else if (itemId == 0x20F) {
			text = GetSkillStr(2);
		} else if (itemId == 0x222) {
			text = GetSkillStr(3);
		} else if (itemId == 0x227) {
			text = GetSkillStr(4);
		} else {
			text = Game.m_cFlatDataArr[1].TableStrings(0)[itemId * 5 + 4];
		}
		const float width = static_cast<float>(font->GetWidth(text));
		drawY = static_cast<float>(
		    (static_cast<double>(unitePanels->height) - 19.8) * 0.5 +
		    static_cast<double>(unitePanels->y) - 2.0);
		font->SetPosX(static_cast<float>((static_cast<float>(unitePanels->width) - width) * 0.5 +
		                                 static_cast<double>(unitePanels->x)));
		font->SetPosY(drawY - 4.0f);
		font->Draw(text);
	}

	DrawInit();
	{
		CmdState* const helpStateView = GetCmdStateView(this);
		const s32 helpMode = helpStateView->mode;
		const s32 helpSelected = helpStateView->selected[0];
		if (helpMode == 0) {
		const s16 helpSlot = caravan->m_commandListExtra[helpSelected];
		if (helpSlot != 0) {
			int helpId =  (helpSlot + 0);
			const u8 helpAlpha =
			    static_cast<u8>(255.0f * GetCmdListStorage(this)->entries[0].alpha);
			if (helpSlot == 0x207 || helpSlot == 0x20B || helpSlot == 0x20F) {
				helpId += 2;
			}

			CFont* const helpFont = m_fonts[0];
			DrawHelpMessage(
				helpId, helpFont,
				static_cast<int>(-(drawW * 0.5f - 320.0f)),
				static_cast<int>(drawY),
				CColor(0xFF, 0xFF, 0xFF, helpAlpha).color, 10,
				1.0f, 3.0f);
		}
		}
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
	int finished;
	float targetX;

	if (s_unitePanelCount == 0) {
		return 1;
	}

	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	float baseX = static_cast<float>(GetCmdListEntries(this)[0].x);

	if (topIdx > 0) {
		for (int i = 0; i < 3; i++) {
			CmdListEntry* entry = &GetCmdListStorage(this)->entries[i + s_UniteTop[topIdx]];
			int idx = i + s_UniteTop[topIdx];
			if ((i != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
				break;
			}

			entry->x = static_cast<s16>(static_cast<double>(entry->x) + 12.8);
			if (fabs(static_cast<double>(static_cast<float>(entry->x) - baseX)) >
			    64.0) {
				entry->x = static_cast<s16>(64.0f + baseX);
				return 1;
			}
		}
	} else {
		finished = 0;
		targetX = 64.0f + baseX;
		s32* top = &s_UniteTop[finished];
		for (int i = 0; i < s_unitePanelCount; i++) {
			for (int j = 0; j < 3; j++) {
				CmdListEntry* entry = &GetCmdListStorage(this)->entries[j + *top];
				int idx = j + *top;
				if ((j != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
					break;
				}

				entry->x = static_cast<s16>(static_cast<double>(entry->x) + 12.8);
				if (fabs(static_cast<double>(static_cast<float>(entry->x) - baseX)) >
				    64.0) {
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

	const CCaravanWork* const caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	float baseX = static_cast<float>(GetCmdListEntries(this)[0].x);

	if (topIdx >= 0) {
		int finished = 0;
		for (int i = 0; i < 3; i++) {
			int idx = i + s_UniteTop[topIdx];
			CmdListEntry* entry = &GetCmdListStorage(this)->entries[idx];
			if ((i != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
				break;
			}

			entry->x = static_cast<s16>(static_cast<double>(entry->x) - 12.8);
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

				entry->x = static_cast<s16>(static_cast<double>(entry->x) - 12.8);
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

	m_cmdState->transitionTimer = static_cast<s16>(m_cmdState->transitionTimer + 1);

	const s32 selected = static_cast<s32>(m_cmdState->selected[0]);

	for (i = 0; i < 3; i++) {
		if ((i != 0) && (caravanWork->m_commandListExtra[selected + i] != -1)) {
			break;
		}
		m_cmdList->entries[selected + i].alpha = static_cast<f32>(
			-((0.2 * static_cast<f64>(m_cmdState->transitionTimer)) - 1.0)
		);
	}
	s32 chainCount = i;

	CmdListEntry* const animEntry = &m_cmdList->entries[m_cmdList->listEnd + 3];

	for (slot = 0; slot < 3; slot++) {
		if (selected == s_UniteTop[slot]) {
			break;
		}
	}

	CmdListEntry* const baseEntry = &m_cmdList->entries[m_cmdList->listEnd + slot];

	if (static_cast<s8>(m_cmdState->unitePanelInitialized) == 0) {
		const s32 endX = static_cast<s32>(static_cast<f64>(baseEntry->x + baseEntry->width) - 24.0);
		animEntry->x = static_cast<s16>(endX);

		if (chainCount == 2) {
			int combo[5][2];
			chainCount = ChkUnite(static_cast<int>(m_cmdState->selected[0]), combo);
		} else {
			chainCount = 0;
		}

		animEntry->scale = static_cast<f32>((chainCount != 0) ? 1.5 : 1.0);
		animEntry->width = 0xC0;
		animEntry->height = 0x40;
		animEntry->y = static_cast<s16>(((-((static_cast<f32>(animEntry->height) * animEntry->scale) -
		                                    static_cast<f32>(baseEntry->height)) *
		                                   0.5) +
		                                  static_cast<f64>(baseEntry->y)) -
		                                 3.0);
		animEntry->u = 0.0f;
		animEntry->v = 0.0f;
		animEntry->tex = 0x39;
		m_cmdState->unitePanelInitialized = 1;
	}

	animEntry->alpha = static_cast<f32>(0.2 * static_cast<f64>(m_cmdState->transitionTimer));
	u32 done = (static_cast<f64>(m_cmdState->transitionTimer) >= 5.0) ? 1 : 0;
	if (done != 0) {
		m_cmdState->selected[2] = 0;
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
		const s32 selected = GetCmdStateView(this)->selected[0];
		s32 i;
		for (i = 0; i < 3; i++) {
			if ((i != 0) && (caravanWork->m_commandListExtra[selected + i] != -1)) {
				break;
			}
			GetCmdList(this)->entries[selected + i].alpha =
				static_cast<float>(0.2 * static_cast<f64>(GetCmdStateView(this)->transitionTimer));
		}

		CmdListEntry* const animEntry = &GetCmdListStorage(this)->entries[GetCmdListStorage(this)->listEnd + 3];
		animEntry->alpha =
			static_cast<float>(-(0.2 * static_cast<f64>(GetCmdStateView(this)->transitionTimer) - 1.0));
		const s32 nextState = (1.0 == static_cast<f64>(animEntry->scale)) ? 2 : 3;

		done = (static_cast<f64>(GetCmdStateView(this)->transitionTimer) >= 5.0) ? 1 : 0;
		if ((done != 0) && (GetCmdStateView(this)->commandResult > 0)) {
			GetCmdStateView(this)->commandResult = 0;
			const s16 choice = GetCmdStateView(this)->selected[2];
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
		const s32 selected = GetCmdStateView(this)->selected[0];
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
		const s16 selected = GetCmdStateView(this)->selected[0];
		const s32 count = ChkUnite(static_cast<int>(selected), combo);
		if (count == 1) {
			done = 0;
			GetCmdStateView(this)->uniteState = 3;
		} else {
			done = 1;
			GetCmdStateView(this)->commandResult = 1;
		}
	} else if (state == 3) {
		const s16 selected = GetCmdStateView(this)->selected[0];
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
			const s32 sel = GetCmdStateView(this)->selected[0];
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
			GetCmdStateView(this)->selected[0] = static_cast<s16>(combo[0][1]);
			GetCmdStateView(this)->uniteState = 4;
		}
	} else if (state == 4) {
		done = static_cast<u32>(UniteOpenAnim(-1));
	}

	return done;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 392b
 * EN Address: 0x801735F8
 * EN Size: 428b
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned int CMenuPcs::CmdOpen2()
{
	unsigned int done;
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

	GetCmdStateView(this)->transitionTimer = static_cast<s16>(GetCmdStateView(this)->transitionTimer + 1);

	s32 selected = static_cast<s32>(GetCmdStateView(this)->selected[0]);
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
	for (i = 0; i < static_cast<s32>(GetCmdListStorage(this)->count); i++) {
		if ((i < prev) || (i > next)) {
			fadeEntry = &GetCmdListStorage(this)->entries[i];
			fadeEntry->alpha = static_cast<float>(
			    -((0.1 * static_cast<double>(static_cast<s32>(GetCmdStateView(this)->transitionTimer))) - 1.0));
			if (static_cast<double>(fadeEntry->alpha) < 0.5) {
				fadeEntry->alpha = 0.5f;
			}
		}
	}

	if (static_cast<double>(static_cast<s32>(GetCmdStateView(this)->transitionTimer)) >= 5.0) {
		done = 1;
	} else {
		done = 0;
	}
	if (done != 0) {
		GetCmdStateSelections(GetCmdStateView(this))[GetCmdStateView(this)->mode] = static_cast<s16>(prev);
	}
	return done;
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
	CCaravanWork* const caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	int combo[5][2];

	const s32 selected = static_cast<s32>(GetCmdStateView(this)->selected[0]);
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
		for (uniteIdx = 0; uniteIdx < s_unitePanelCount; uniteIdx++) {
			if (selected == s_UniteTop[uniteIdx]) {
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

			const s32 closeSel = GetCmdStateView(this)->selected[0];
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
			const int recipe = combo[comboIdx][0];
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->UniteComList(
			    comboSel[comboIdx * 2], GetUniteRecipeCount(recipe), GetUniteRecipeCmd(recipe));
			GetCmdStateView(this)->selected[0] = static_cast<s16>(comboSel[comboIdx * 2]);
			GetCmdStateView(this)->uniteState = 2;
		}
		return 0;
	} else if (GetCmdStateView(this)->uniteState == 2) {
		if (caravanWork->m_commandListExtra[selected] == 0) {
			ChkUnite(selected, combo);
			int* comboSel = &combo[0][1];

			s32 comboIdx = 0;
			if (comboSel[0] < comboSel[2]) {
				comboIdx = (modeSel == static_cast<u32>(comboSel[0])) ? 0 : 1;
			} else {
				comboIdx = (!(modeSel == static_cast<u32>(comboSel[2]))) ? 0 : 1;
			}

			const int recipe = combo[comboIdx][0];
			reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0])->UniteComList(
				comboSel[comboIdx * 2], GetUniteRecipeCount(recipe), GetUniteRecipeCmd(recipe));
			GetCmdStateView(this)->selected[0] = static_cast<s16>(comboSel[comboIdx * 2]);
		} else if (UniteOpenAnim(-1) != 0) {
			GetCmdStateView(this)->uniteState = 3;
		}
		return 0;
	} else if (GetCmdStateView(this)->uniteState == 3) {
		for (s32 i = 0; i < static_cast<s32>(GetCmdListStorage(this)->count); i++) {
			CmdListEntry* entry = &GetCmdListStorage(this)->entries[i];
			if (static_cast<f64>(entry->alpha) >= 1.0) {
				continue;
			}
			entry->alpha = static_cast<f32>((0.1 * static_cast<f64>(GetCmdStateView(this)->transitionTimer)) + 0.5);
			if (static_cast<f64>(entry->alpha) > 1.0) {
				entry->alpha = 1.0f;
			}
		}
		return (static_cast<f64>(GetCmdStateView(this)->transitionTimer) >= 5.0) ? 1 : 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8014a940
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
const char* CMenuPcs::GetSkillStr(int index)
{
	switch (Game.m_gameWork.m_languageId) {
	case 2:
		return s_SkillStr_ge[index];
	case 3:
		return s_SkillStr_it[index];
	case 4:
		return s_SkillStr_fr[index];
	case 5:
		return s_SkillStr_sp[index];
	case 1:
	default:
		return s_SkillStr_us[index];
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetFontItem()
{
	return;
}
