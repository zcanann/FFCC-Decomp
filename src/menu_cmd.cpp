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

static s32 s_ucnt;
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

#ifdef VERSION_GCCJGC
static char* s_SkillStr_jp[] = {
    "ファイア剣",
    "ブリザド剣",
    "サンダー剣",
    "ホーリー剣",
    "グラビデ剣",
};

#else
static char* s_SkillStr_us[] = {
    "Flamestrike",
    "Icestrike",
    "Thunderstrike",
    "",
    "",
};

static char* s_SkillStr_ge[] = {
#ifdef VERSION_GCCE01
    "Feuer-Klinge",
    "Eis-Klinge",
    "Blitz-Klinge",
#else
    "Feuer-Hieb",
    "Eis-Hieb",
    "Blitz-Hieb",
#endif
    "",
    "",
};

static char* s_SkillStr_it[] = {
    "Colpo Fire",
    "Colpo Blizzard",
    "Colpo Thunder",
    "",
    "",
};

static char* s_SkillStr_fr[] = {
    "Pyro-Frappe",
    "Cryo-Frappe",
    "Rh\351o-Frappe",
    "",
    "",
};

static char* s_SkillStr_sp[] = {
    "Efecto Fuego",
    "Efecto Hielo",
    "Efecto Electro",
    "",
    "",
};
#endif
namespace {

#ifdef VERSION_GCCJGC
enum {
    kCmdSlotTexture = 0x2C,
    kCmdPanelTexture = 0x2D,
    kCmdTabTexture = 0x45,
    kCmdDisabledRowTexture = 0x33,
    kCmdUniteListTexture = 0x34,
    kCmdUniteListPairTexture = 0x35,
    kCmdRowTexture = 0x36,
    kCmdUniteRowTexture = 0x37,
    kCmdUnitePanelTexture = 0x38
};
#else
enum {
    kCmdSlotTexture = 0x2D,
    kCmdPanelTexture = 0x2E,
    kCmdTabTexture = 0x46,
    kCmdDisabledRowTexture = 0x34,
    kCmdUniteListTexture = 0x35,
    kCmdUniteListPairTexture = 0x36,
    kCmdRowTexture = 0x37,
    kCmdUniteRowTexture = 0x38,
    kCmdUnitePanelTexture = 0x39
};
#endif

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

const int kIconClavatWeapon = 0;
const int kIconLiltyWeapon = 1;
const int kIconYukeWeapon = 2;
const int kIconSelkieWeapon = 3;

} // namespace

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
	const CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
	memset(m_cmdList, 0, sizeof(*m_cmdList));

	CmdListEntry* entry = m_cmdList->entries;
	for (s32 i = 0; i < 64; i++, entry++) {
		entry->scale = 1.0f;
	}

	entry = m_cmdList->entries;
	float texU = 0.0f;
	float texV = 8.0f;
	for (s32 slot = 0; slot < 8; slot++) {
		if (slot < caravanWork->m_numCmdListSlots) {
			entry->tex = kCmdSlotTexture;
		} else {
			entry->tex = 0xFFFFFFFF;
		}

		entry->width = 200;
		entry->height = 0x20;
		entry->x = 0x74;
		entry->y = static_cast<s16>(slot * entry->height + 0x28);
		entry->u = texU;
		entry->v = texV;

		if ((2 <= slot) && (caravanWork->m_commandListInventorySlotRef[slot] < 0)) {
			entry->v += static_cast<float>(entry->height);
		}

		entry->startFrame = slot;
		entry->duration = 3;
		entry++;
	}

	m_cmdList->count = 8;
	CmdInit1();
	GetCmdItem();
	m_cmdState->selected[0] = 2;
	m_cmdState->initialized = 1;
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
	s32 i;
	s32 idx;
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
	CmdListEntry* entry = m_cmdList->entries;
	for (i = 0; i < static_cast<s32>(m_cmdList->count); i++, entry++) {
		entry->alpha = 1.0f;
		entry->scale = 1.0f;
	}

	for (i = static_cast<s32>(caravanWork->m_numCmdListSlots) - 1, idx = 0; i >= 0; i--, idx++) {
		entry = &m_cmdList->entries[i];
		entry->startFrame = idx;
		entry->duration = 3;
	}

	m_cmdState->commandResult = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8014ff0c
 * PAL Size: 816b
 * EN Address: 0x8014F000
 * EN Size: 816b
 * JP Address: 0x8014B168
 * JP Size: 804b
 */
void CMenuPcs::CmdInit1()
{
	CmdListEntry* entry;
	s32 idx = static_cast<s32>(m_cmdList->count);

	entry = &m_cmdList->entries[idx++];
	entry->tex = kCmdPanelTexture;
	entry->x = 0xb8;
	entry->y = 0x28;
	entry->width = 0x78;
	entry->height = 0x108;
	entry->u = 128.0f;
	entry->v = 8.0f;
	entry->scale = 1.0f;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &m_cmdList->entries[idx++];
#ifdef VERSION_GCCJGC
	entry->tex = kCmdTabTexture;
#else
	entry->tex = (m_cmdLayoutFlag == 0) ? kCmdTabTexture : 0x2f;
#endif
	entry->x = 0xa0;
	entry->y = 0xe;
	entry->width = 0x30;
	entry->height = 0x30;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->scale = 1.0f;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &m_cmdList->entries[idx++];
#ifdef VERSION_GCCJGC
	entry->tex = kCmdTabTexture;
#else
	entry->tex = (m_cmdLayoutFlag == 0) ? kCmdTabTexture : 0x2f;
#endif
	entry->width = 0x30;
	entry->height = 0x30;
	entry->x = 0xa5;
	entry->y = static_cast<s16>(0x150 - entry->height);
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->scale = 0.75f;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &m_cmdList->entries[idx++];
	entry->flags = 2;
	entry->tex = kCmdPanelTexture;
	entry->x = 0xa0;
	entry->y = 8;
	entry->width = 0x48;
	entry->height = 0x140;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->startFrame = 0;
	entry->duration = 5;

	CmdListEntry* basePanel = &m_cmdList->entries[m_cmdList->count];
	for (s32 i = 0; i < 8; i++) {
		entry = &m_cmdList->entries[idx++];
		entry->flags = 2;
		entry->tex = kCmdRowTexture;
		entry->x = static_cast<s16>(basePanel->x + 0x24);
		entry->y = static_cast<s16>(basePanel->y + i * 0x20);
		entry->width = 200;
		entry->height = 0x28;
		entry->u = 0.0f;
		entry->v = 0.0f;
		entry->startFrame = 7;
		entry->duration = 5;
	}

	m_cmdList->listEnd = static_cast<s16>(idx);

	CmdListEntry* fillEntry = &m_cmdList->entries[m_cmdList->count];
	for (s32 k = m_cmdList->listEnd - m_cmdList->count; k > 0; k--) {
		fillEntry->timer = 0;
		fillEntry->alpha = 0.0f;
		fillEntry++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8014fc50
 * PAL Size: 700b
 * EN Address: 0x8014ED44
 * EN Size: 700b
 * JP Address: 0x8014AED4
 * JP Size: 660b
 */
void CMenuPcs::CmdInit2()
{
	s32 i = m_cmdList->count;
	CmdListEntry* entry;

	entry = &m_cmdList->entries[i++];
	entry->tex = kCmdPanelTexture;
	entry->startFrame = 2;
	entry->duration = 5;

	entry = &m_cmdList->entries[i++];
#ifdef VERSION_GCCJGC
	entry->tex = kCmdTabTexture;
#else
	entry->tex = (m_cmdLayoutFlag == 0) ? kCmdTabTexture : 0x2f;
#endif
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_cmdList->entries[i++];
#ifdef VERSION_GCCJGC
	entry->tex = kCmdTabTexture;
#else
	entry->tex = (m_cmdLayoutFlag == 0) ? kCmdTabTexture : 0x2f;
#endif
	entry->startFrame = 7;
	entry->duration = 5;

	entry = &m_cmdList->entries[i++];
	entry->flags = 2;
	entry->tex = kCmdPanelTexture;
	entry->startFrame = 7;
	entry->duration = 5;

	for (s32 j = 0; j < 8; j++) {
		entry = &m_cmdList->entries[i++];
		entry->flags = 2;
		entry->tex = kCmdRowTexture;
		entry->startFrame = 0;
		entry->duration = 5;
	}

	m_cmdList->listEnd = static_cast<s16>(i);

	entry = &m_cmdList->entries[m_cmdList->count];
	for (i = m_cmdList->listEnd - m_cmdList->count; i > 0; i--) {
		entry->timer = 0;
		entry->alpha = 1.0f;
		entry++;
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
int CMenuPcs::CmdOpen()
{
	if (m_cmdState->initialized == 0) {
		CmdInit();
	}

	CmdListEntry* entry;
	s32 i;
	s32 finishedCount = 0;
	m_cmdState->transitionTimer = static_cast<s16>(m_cmdState->transitionTimer + 1);

	const s32 entryCount = m_cmdList->count;
	entry = m_cmdList->entries;
	const s32 timer = static_cast<s32>(m_cmdState->transitionTimer);

	for (i = 0; i < entryCount; i++) {
		if (entry->startFrame <= timer) {
			if ((entry->startFrame + entry->duration) <= timer) {
				finishedCount += 1;
				entry->alpha = 1.0f;
			} else {
				entry->timer++;
				entry->alpha = static_cast<float>((1.0 / static_cast<double>(entry->duration)) * static_cast<double>(entry->timer));
			}
		}
		entry++;
	}

	int done = 0;
	CmdListStorage* const list2 = m_cmdList;
	if (list2->count == finishedCount) {
		entry = list2->entries;
		for (i = 0; i < entryCount; i++, entry++) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = 1.0f;
		}
		done = 1;
	}

	if (done) {
		done = UniteOpenAnim(-1);
	}
	return done;
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
	Game.m_scriptFoodBase[0]->CalcStatus();

	m_cmdState->prevMode = m_cmdState->mode;

	s32 actionHandled = 0;
	s32 mode = m_cmdState->mode;

	if ((mode == 0) || ((mode != 0) && (m_cmdState->phase == 1))) {
		actionHandled = CmdCtrlCur();
	} else if ((mode == 1) && (m_cmdState->phase == 0)) {
		actionHandled = CmdOpen0();
		if (actionHandled != 0) {
			actionHandled = 0;
			m_cmdState->phase = static_cast<s16>(m_cmdState->phase + 1);
		}
	} else if ((mode == 1) && (m_cmdState->phase == 2)) {
		actionHandled = CmdClose0();
		if (actionHandled != 0) {
			if (m_cmdState->commandResult != 0) {
				m_cmdState->phase = 0;
				m_cmdState->mode = 3;
				m_cmdState->transitionTimer = 0;
				m_cmdState->commandResult = 0;
				CmdInit1();
			} else {
				m_cmdState->phase = static_cast<s16>(m_cmdState->phase + 1);
			}
			actionHandled = 0;
		}
	} else if ((mode == 1) && (m_cmdState->phase == 3)) {
		actionHandled = UniteOpenAnim(-1);
		if (actionHandled != 0) {
			m_cmdState->phase = 0;
			m_cmdState->mode = 0;
			m_cmdState->transitionTimer = 0;
			CmdInit1();
			actionHandled = 0;
		}
	} else if ((mode == 2) && (m_cmdState->phase == 0)) {
		actionHandled = CmdOpen1();
		if (actionHandled != 0) {
			actionHandled = 0;
			m_cmdState->phase = static_cast<s16>(m_cmdState->phase + 1);
		}
	} else if ((mode == 2) && (m_cmdState->phase == 2)) {
		actionHandled = CmdClose1();
		if (actionHandled != 0) {
			if (m_cmdState->commandResult != 0) {
				m_cmdState->uniteState = 0;
				m_cmdState->mode = 3;
			} else {
				m_cmdState->mode = 0;
			}
			actionHandled = 0;
			m_cmdState->phase = 0;
			m_cmdState->transitionTimer = 0;
		}
	} else if ((mode == 3) && (m_cmdState->phase == 0)) {
		actionHandled = CmdOpen2();
		if (actionHandled != 0) {
			actionHandled = 0;
			m_cmdState->phase = static_cast<s16>(m_cmdState->phase + 1);
		}
	} else if ((mode == 3) && (m_cmdState->phase == 2)) {
		actionHandled = CmdClose2();
		if (actionHandled != 0) {
			actionHandled = 0;
			m_cmdState->phase = 0;
			m_cmdState->mode = 0;
			m_cmdState->transitionTimer = 0;
			m_cmdState->commandResult = 0;
		}
	}

	if (actionHandled != 0) {
		CmdInit0();
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
	s32 ret;

	if (m_cmdState->commandResult == 0) {
		ret = UniteCloseAnim(-1);
		if (ret != 0) {
			m_cmdState->transitionTimer = 0;
			m_cmdState->commandResult = 1;
		}
		return 0;
	}

	CmdListEntry* entry;
	s32 doneCount = 0;
	m_cmdState->transitionTimer = m_cmdState->transitionTimer + 1;

	const s32 entryCount = static_cast<s32>(m_cmdList->count);
	entry = m_cmdList->entries;
	s32 closeTimer = static_cast<s32>(m_cmdState->transitionTimer);

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

	ret = 0;
	CmdListStorage* const list = m_cmdList;
	if (list->count == doneCount) {
		CmdListEntry* p = list->entries;
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
 * EN Address: 0x8014CE7C
 * EN Size: 5472b
 * JP Address: 0x80149004
 * JP Size: 5412b
 */
void CMenuPcs::CmdDraw()
{
	float h;
	s32 itemCount;
	s32 idx;
	s32 sel;
	s32 row;
	s32 choice;
	s16 mode;
	s32 hasItemHelp = false;
	s32 helpId;
	float rowU;
	float t;
	float x;
	float y;
	float w;
	GXColor colors[4];
	CmdListEntry* entry;
	s32 choices;
	s32 i;

	AlphaNormal();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	CCaravanWork* const caravan = Game.m_scriptFoodBase[0];
	const s32 animState = m_cmdState->animState;
	const s32 cmdMode = m_cmdState->mode;

	entry = m_cmdList->entries;
	for (i = 0; i < m_cmdList->count; i++, entry++) {
		const s32 tex = entry->tex;
		if (tex >= 0) {
			x = static_cast<float>(entry->x);
			y = static_cast<float>(entry->y);
			w = static_cast<float>(entry->width);
			h = static_cast<float>(entry->height);
			rowU = entry->u;

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
				    0, x, y, w, h, rowU, t, entry->scale, entry->scale, 0.0f);
			}
		}
	}

	CFont* nameFont = GetFontItem();
	nameFont->SetMargin(1.0f);
	nameFont->SetShadow(0);
	nameFont->SetScale(0.9f);
	nameFont->DrawInit();

	entry = m_cmdList->entries;
	for (i = 0; i < caravan->m_numCmdListSlots; i++, entry++) {
		if ((i >= 8) || (caravan->m_commandListExtra[i] == 0)) {
			nameFont->SetColor(
			    CColor(0xFF, 0xFF, 0xFF,
			        static_cast<u8>(255.0f *
			            static_cast<float>(cmdMode == 3 ? 1.0 : static_cast<double>(entry->alpha))))
			        .color);

			char* text;
			if (i < 2) {
				text = GetMenuStr(i + 9);
			} else {
				const int cmdId = caravan->m_commandListInventorySlotRef[i];
				if (cmdId >= 0) {
					const int skillId = caravan->m_inventoryItems[cmdId];
					text = Game.GetShortItemName(skillId);
					if ((m_cmdState->mode == 0) && (i == m_cmdState->selected[0])) {
						helpId = skillId;
						hasItemHelp = true;
					}
				} else {
					continue;
				}
			}

			const float textW = static_cast<float>(nameFont->GetWidth(text));
			x = static_cast<double>(entry->x) + ((static_cast<float>(entry->width) - textW) / 2.0);
			y = static_cast<float>(entry->y + 3);
			nameFont->SetPosX(x);
#ifdef VERSION_GCCJGC
			nameFont->SetPosY(y);
#else
			nameFont->SetPosY(y - 4.0f);
#endif
			nameFont->Draw(text);
		}
	}

	DrawInit();
	DrawUniteList();

	entry = m_cmdList->entries;
	for (i = 0; i < caravan->m_numCmdListSlots; i++, entry++) {
		if (i >= 2) {
			const s32 ref = caravan->m_commandListInventorySlotRef[i];
			if (ref < 0) {
				continue;
			}
			x = static_cast<float>(entry->x + entry->width - 0x10);
			y = static_cast<float>(entry->y - 2);
			DrawSingleIcon(
			    caravan->m_inventoryItems[ref],
			    static_cast<s32>(static_cast<float>(entry->x + entry->width - 0x10)),
			    static_cast<s32>(y - 1.0f), entry->alpha, 0, 1.0f);
		}
	}

	if (m_cmdState->prevMode != 0) {
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		s32 specialRow = 0;
		entry = &m_cmdList->entries[m_cmdList->count];
		const s16* letterBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		itemCount = letterBuf[0];
		for (idx = m_cmdList->count; idx < m_cmdList->listEnd; idx++, entry++) {
			if (entry->tex >= 0) {
				x = static_cast<float>(entry->x);
				y = static_cast<float>(entry->y);
				w = static_cast<float>(entry->width);
				h = static_cast<float>(entry->height);
				rowU = entry->u;
				t = entry->v;

				if (idx == m_cmdList->count) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(entry->tex));

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

					w = entry->alpha * w;
					if (w > 0.0f) {
						MenuPcs.DrawRect(0, x, y, w, h, rowU, t, colors,
						    1.0f, 1.0f, 0.0f);
						x += w;
						rowU += w;
					}
					if ((w > 0.0f) && (w < static_cast<float>(entry->width))) {
						colors[1].r = 0xFF;
						colors[1].g = 0xFF;
						colors[1].b = 0xFF;
						colors[1].a = 0;
						colors[3].r = 0xFF;
						colors[3].g = 0xFF;
						colors[3].b = 0xFF;
						colors[3].a = 0;
						w = static_cast<float>(
						    1.0 / static_cast<double>(entry->duration));
						w *= static_cast<float>(entry->width);
						MenuPcs.DrawRect(0, x, y, w, h, rowU, t, colors,
						    1.0f, 1.0f, 0.0f);
					}

					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				} else {
					float rowAlpha = entry->alpha;
					s32 rowTex = entry->tex;
					if (rowTex == kCmdRowTexture) {
						sel = specialRow + m_cmdState->scrollTop;
						if ((itemCount >= 8) && (sel >= itemCount)) {
							sel -= itemCount;
						}

						if (sel < 2) {
							if (!ChkCmdActive(sel)) {
								rowAlpha = 0.5 * entry->alpha;
								rowTex = kCmdDisabledRowTexture;
							}
						} else {
							sel = specialRow + m_cmdState->scrollTop - 2;
							if ((itemCount >= 8) && (sel >= itemCount)) {
								sel -= itemCount;
							}

							if ((sel + 2 >= itemCount) || EquipChk(static_cast<int>(letterBuf[sel + 1]))) {
								if (sel + 2 < itemCount) {
									DrawEquipMark(static_cast<s32>(x - 12.0f),
									    static_cast<s32>(((h - 24.0f) / 2.0) + y),
									    entry->alpha);
								}
								rowTex = kCmdDisabledRowTexture;
								rowAlpha = 0.5 * entry->alpha;
							}
						}

						if ((rowTex == kCmdRowTexture) &&
						    (specialRow == m_cmdState->selected[1])) {
							t += h;
						}
						specialRow++;
					}

					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(rowTex));

					colors[0].r = 0xFF;
					colors[0].g = 0xFF;
					colors[0].b = 0xFF;
					colors[0].a = static_cast<u8>(255.0f * rowAlpha);
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);

					MenuPcs.DrawRect(0, x, y, w, h, rowU, t, entry->scale,
					    entry->scale, 0.0f);
				}
			}
		}
	}

	if (cmdMode == 1) {
		CFont* listFont = GetFontItem();
		listFont->SetMargin(1.0f);
		listFont->SetShadow(0);
		listFont->SetScale(0.9f);
		listFont->DrawInit();

		const s16* letterBuf = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		itemCount = letterBuf[0];
		for (idx = m_cmdList->count; idx < m_cmdList->listEnd; idx++) {
			entry = &m_cmdList->entries[idx];
			if (entry->tex == kCmdRowTexture) {
				break;
			}
		}

		CmdListEntry* rowEntry = entry;
		for (row = 0; row < 8; row++, rowEntry++) {
			if ((itemCount <= 8) && (row + m_cmdState->scrollTop >= itemCount)) {
				break;
			}

			s32 displayIdx =  (s32)(row + m_cmdState->scrollTop);
			if (displayIdx >= itemCount) {
				displayIdx -= itemCount;
			}

			const float alpha = entry->alpha;
			listFont->SetColor(
			    CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)));

			char* text;
			if (displayIdx < 2) {
				text = GetMenuStr(displayIdx + 0x0B);
			} else if (!(displayIdx >= itemCount)) {
				const s16 slot = letterBuf[displayIdx - 1];
				const int skillId = caravan->m_inventoryItems[slot];
				text = Game.GetShortItemName(skillId);

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
			x = static_cast<float>(rowEntry->x + 0x1C);
			y = static_cast<float>(rowEntry->y + 0x0B);
			listFont->SetPosX(static_cast<float>(rowEntry->x + 0x1C));
#ifdef VERSION_GCCJGC
			listFont->SetPosY(y);
#else
			listFont->SetPosY(y - 4.0f);
#endif
			listFont->Draw(text);
		}

		DrawInit();

		for (row = 0, rowEntry = entry; row < 8; row++, rowEntry++) {
			if ((itemCount <= 8) && (row + m_cmdState->scrollTop >= itemCount)) {
				break;
			}

			s32 displayIdx = row + m_cmdState->scrollTop;
			if (displayIdx >= itemCount) {
				displayIdx -= itemCount;
			}

			if (displayIdx >= 2) {
				const s16 slot = letterBuf[displayIdx - 1];
				x = static_cast<float>(rowEntry->x + rowEntry->width - 0x10);
				y = static_cast<float>(rowEntry->y + 6);
				DrawSingleIcon(
				    caravan->m_inventoryItems[slot],
				    static_cast<s32>(static_cast<float>(rowEntry->x + rowEntry->width - 0x10)),
				    static_cast<s32>(y - 1.0f),
				    entry->alpha, 0, 1.0f);
			}
		}
	}

	if ((cmdMode == 1) && (m_cmdState->phase == 1)) {
		entry = &m_cmdList->entries[m_cmdList->count];
		const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		const float mark = CalcListPos(m_cmdState->scrollTop, letter[0], 1);
		if (mark > 0.0f) {
			DrawListPosMark(static_cast<float>(entry->x), static_cast<float>(entry->y), mark);
		}
	}

	if (cmdMode == 2) {
		entry = &m_cmdList->entries[m_cmdList->listEnd + 3];
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(entry->tex));

		colors[0].r = 0xFF;
		colors[0].g = 0xFF;
		colors[0].b = 0xFF;
		colors[0].a = static_cast<u8>(255.0f * entry->alpha);
		GXSetChanMatColor(GX_COLOR0A0, colors[0]);
		MenuPcs.DrawRect(
		    0, static_cast<float>(entry->x), static_cast<float>(entry->y),
		    static_cast<float>(entry->width), static_cast<float>(entry->height),
		    entry->u, entry->v, 1.0f, entry->scale, 0.0f);

		CFont* choiceFont = GetFont22();
		choiceFont->SetMargin(1.0f);
		choiceFont->SetShadow(1);
		choiceFont->SetScale(0.9f);
		choiceFont->DrawInit();
		choiceFont->SetTlut(7);
		choiceFont->SetColor(
		    CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * entry->alpha)));

		choices = (1.0 == static_cast<double>(entry->scale)) ? 2 : 3;
		for (choice = 0; choice < choices; choice++) {
			char* text;
			if (choice == 0) {
				text = GetMenuStr(0x0D);
			} else if ((choice == 1) && (choices == 3)) {
				text = GetMenuStr(0x0C);
			} else {
				text = GetMenuStr(0x37);
			}
			choiceFont->GetWidth(text);
			x = static_cast<float>(entry->x + 0x18);
			const float pitch = static_cast<float>(
			    ((static_cast<float>(entry->height) * entry->scale) - 16.0) /
			    choices);
			y = ((pitch * static_cast<float>(choice)) + static_cast<float>(entry->y + 8)) +
			    ((pitch - 19.8) / 2.0);
			choiceFont->SetPosX(x);
#ifdef VERSION_GCCJGC
			choiceFont->SetPosY(y);
#else
			choiceFont->SetPosY(y - 4.0f);
#endif
			choiceFont->Draw(text);
		}
		DrawInit();
	}

	s32 cursorOnUnite = false;
	if (((cmdMode == 0) && (animState == 1)) ||
	    ((cmdMode != 0) && (m_cmdState->phase == 1))) {

		if ((cmdMode == 0) || (cmdMode == 3)) {
			s32 index = m_cmdState->selected[cmdMode];
			if (!(caravan->m_commandListExtra[index] == 0)) {
				s32 uniteIdx;
				for (uniteIdx = 0; uniteIdx < s_ucnt; uniteIdx++) {
					if (s_UniteTop[uniteIdx] == index) {
						break;
					}
				}
				entry = &m_cmdList->entries[m_cmdList->listEnd + uniteIdx];
				cursorOnUnite = true;
			} else {
				entry = &m_cmdList->entries[index];
			}
		} else if (cmdMode == 1) {
			for (idx = m_cmdList->count; idx < m_cmdList->listEnd; idx++) {
				entry = &m_cmdList->entries[idx];
				if (entry->tex == kCmdRowTexture) {
					break;
				}
			}
			entry = entry + m_cmdState->selected[1];
		} else {
			entry = &m_cmdList->entries[m_cmdList->listEnd + 3];
			choices = (1.0 == static_cast<double>(entry->scale)) ? 2 : 3;
			const float pitch = static_cast<float>(
			    ((static_cast<float>(entry->height) * entry->scale) - 16.0) /
			    static_cast<double>(choices));
			x = static_cast<float>(entry->x - 0x14);
			y = ((pitch - 19.8) / 2.0) +
			    ((pitch * static_cast<float>(m_cmdState->selected[2])) + static_cast<float>(entry->y + 8));
		}

		if (cmdMode != 2) {
			if (!cursorOnUnite) {
				x = static_cast<float>(entry->x - 0x14);
				y = static_cast<float>(entry->y);
				if (m_cmdState->mode != 0) {
					y += 8.0f;
				}
			} else {
				x = static_cast<float>(entry->x - 0x14);
				y = (entry->height - 0x20) / 2.0 + entry->y;
			}
		}

		const s32 frame = static_cast<s32>(System.GetCounter()) % 8;
		x += static_cast<float>(frame);
		DrawCursor(static_cast<s32>(x), static_cast<s32>(y), 1.0f);
	}

	const s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	s32 helpIdx = m_cmdState->selected[1] + m_cmdState->scrollTop;
	if (helpIdx >= letter[0]) {
		helpIdx -= letter[0];
	}

	CFont* helpFont = GetFont22();
	entry = &m_cmdList->entries[m_cmdList->count];
	int helpAlpha = static_cast<int>(255.0f * entry->alpha);
	if (!hasItemHelp) {
		helpId = -1;
	}

	mode = m_cmdState->mode;
	if (mode == 0) {
		if (helpId == -1) {
			if (caravan->m_commandListExtra[m_cmdState->selected[0]] == 0) {
				helpId = 0x266;
			}
		}
	}
	if (mode == 1) {
		if (helpIdx < 2) {
			helpId = helpIdx + 0x259;
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

	float helpX = static_cast<float>(-(w / 2.0f - 320.0f));
	float helpY = 352.0f;
	DrawHelpMessage(
	    helpId, helpFont, static_cast<int>(helpX), static_cast<int>(helpY),
	    CColor(0xFF, 0xFF, 0xFF, helpAlpha), 10,
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
	int cursor;
	CCaravanWork* caravanWork;
	short hold;
	short press;
	s32 cmdCount;
	s32 mode;
	s16* list;
	list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	caravanWork = Game.m_scriptFoodBase[0];
	press = Pad.GetButtonDown(0);
	hold = Pad.GetButtonRepeat(0);

	if (hold == 0) {
		return 0;
	}

	mode = m_cmdState->mode;

	if (mode == 0) {
		cmdCount = caravanWork->m_numCmdListSlots;

		if ((hold & 8) != 0) {
			CmdState* row = m_cmdState;
			if (row->selected[mode] > 2) {
				row->selected[mode]--;
			} else {
				row->selected[mode] = static_cast<s16>(cmdCount - 1);
			}

			CmdState* row2 = m_cmdState;
			cursor = row2->selected[mode];
			if (caravanWork->m_commandListExtra[cursor] < 0) {
				for (int k = 1; k < 3; k++) {
					if (caravanWork->m_commandListExtra[cursor - k] >= 0) {
						row2->selected[mode] = static_cast<s16>(cursor - k);
						break;
					}
				}
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else {
			if ((hold & 4) != 0) {
				CmdState* row = m_cmdState;
				if (row->selected[mode] < cmdCount - 1) {
					row->selected[mode]++;
				} else {
					row->selected[mode] = 2;
				}

				CmdState* row2 = m_cmdState;
				cursor = row2->selected[mode];
				if (caravanWork->m_commandListExtra[cursor] < 0) {
					for (int k = 1; k < 3; k++) {
						if (caravanWork->m_commandListExtra[cursor + k] >= 0) {
							row2->selected[mode] = static_cast<s16>(cursor + k);
							break;
						}
					}
					CmdState* row3 = m_cmdState;
					if (row3->selected[mode] > cmdCount - 1) {
						row3->selected[mode] = 2;
					}
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x20) != 0) {
				m_cmdState->action = 1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x40) != 0) {
				m_cmdState->action = -1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x100) != 0) {
				if (!(caravanWork->m_commandListExtra[m_cmdState->selected[mode]] == 0)) {
					m_cmdState->unitePanelInitialized = 0;
					m_cmdState->mode = 2;
				} else {
					m_cmdState->mode = 1;
				}
				m_cmdState->phase = 0;
				m_cmdState->transitionTimer = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else {
				if ((press & 0x200) != 0) {
					m_cmdState->uniteOpenFlag = 1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
					return 1;
				}
			}
		}
	} else if (mode == 1) {
		int itemCount = static_cast<int>(reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0))[0]);

		if (!((hold & 8) == 0)) {
			CmdState* sv1 = m_cmdState;
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
				if (((itemCount > 8) && (m_cmdState->selected[mode] < 7)) ||
				    ((itemCount <= 8) &&
				     (m_cmdState->selected[mode] < itemCount - 1))) {
					m_cmdState->selected[mode]++;
				} else {
					if (itemCount <= 8) {
						m_cmdState->selected[mode] = 0;
					} else if (m_cmdState->scrollTop < itemCount - 1) {
						m_cmdState->scrollTop = m_cmdState->scrollTop + 1;
					} else {
						m_cmdState->scrollTop = 0;
					}
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if (!((press & 0x100) == 0)) {
				int comboChoice[5][2];
				int selected = static_cast<int>(m_cmdState->scrollTop) +
				               static_cast<int>(m_cmdState->selected[mode]);
				if (selected >= itemCount) {
					selected -= itemCount;
				}

				if (ChkCmdActive(selected)) {
					if (selected == 0) {
						caravanWork->ChgCmdLst(m_cmdState->selected[0], -1);
					} else if (selected != 1) {
						caravanWork->ChgCmdLst(m_cmdState->selected[0], list[selected - 1]);
					}

					m_cmdState->commandResult = 0;
					if (selected != 0) {
						int comboCount;
						comboCount = ChkUnite(m_cmdState->selected[0], comboChoice);
						if (comboCount == 1) {
							CmdUnite(comboChoice[0][0], comboChoice[0][1]);
						} else if (comboCount > 1) {
							if (!(s_Unite[comboChoice[1][0]].count == 2)) {
								CmdUnite(comboChoice[0][0], comboChoice[0][1]);
							} else {
								m_cmdState->commandResult = 1;
							}
						}
					}

					m_cmdState->phase++;
					m_cmdState->transitionTimer = 0;
					CmdInit2();
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				} else {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				}
			} else {
				if ((press & 0x200) != 0) {
					m_cmdState->phase++;
					m_cmdState->transitionTimer = 0;
					m_cmdState->commandResult = 0;
					CmdInit2();
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			}
		}
	} else if (mode == 2) {
		CmdListStorage* cmdList = m_cmdList;
		CmdListEntry* panel = &cmdList->entries[cmdList->listEnd + 3];
		int maxPos;
		if (1.0 == static_cast<double>(panel->scale)) {
			maxPos = 2;
		} else {
			maxPos = 3;
		}

		if (!((hold & 8) == 0)) {
			CmdState* row = m_cmdState;
			if (!(row->selected[mode] == 0)) {
				row->selected[mode]--;
			} else {
				row->selected[mode] = static_cast<s16>(maxPos - 1);
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else {
			if ((hold & 4) != 0) {
				CmdState* row = m_cmdState;
				if (row->selected[mode] < maxPos - 1) {
					row->selected[mode]++;
				} else {
					row->selected[mode] = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			m_cmdState->uniteState = 0;
			if (!((press & 0x100) == 0)) {
				m_cmdState->phase++;
				m_cmdState->transitionTimer = 0;
				m_cmdState->commandResult = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else {
				if ((press & 0x200) != 0) {
					m_cmdState->phase++;
					m_cmdState->transitionTimer = 0;
					m_cmdState->commandResult = -1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
				}
			}
		}
	} else {
		if ((hold & 0xC) != 0) {
			int cmdCount;
			CmdState* const sv0 = m_cmdState;
			const int selected = sv0->selected[0];
			int prev = selected - 1;
			while (prev > 2) {
				if (caravanWork->m_commandListExtra[prev] >= 0) {
					break;
				}
				prev--;
			}

			cmdCount = caravanWork->m_numCmdListSlots;
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
			m_cmdState->commandResult = 0;
			m_cmdState->uniteState = 0;
			if (!((press & 0x100) == 0)) {
				m_cmdState->phase++;
				m_cmdState->transitionTimer = 0;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else {
				if ((press & 0x200) != 0) {
					m_cmdState->commandResult = -1;
					m_cmdState->phase++;
					m_cmdState->transitionTimer = 0;
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
	m_cmdState->transitionTimer++;
	const s32 timer = static_cast<s32>(m_cmdState->transitionTimer);
	const s32 sel = m_cmdState->selected[0];
	CmdListEntry* selEntry = &m_cmdList->entries[sel];
	if (timer < 5) {
		selEntry->x = static_cast<s16>(selEntry->x - 0x13);
	}

	CmdListEntry* entry = &m_cmdList->entries[m_cmdList->count];
	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(m_cmdList->listEnd) - static_cast<s32>(m_cmdList->count);

	for (s32 i = 0; i < entryCount; i++) {
		if (timer >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= timer) {
				doneCount++;
				entry->alpha = 1.0f;
				entry->dx = 0.0f;
				entry->dy = 0.0f;
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
	m_cmdState->transitionTimer++;
	const s32 timer = static_cast<s32>(m_cmdState->transitionTimer);
	const s32 sel = m_cmdState->selected[0];
	CmdListEntry* selEntry = &m_cmdList->entries[sel];
	if (timer > 7) {
		selEntry->x = static_cast<s16>(selEntry->x + 0x13);
	}

	CmdListEntry* entry = &m_cmdList->entries[m_cmdList->count];
	s32 doneCount = 0;
	s32 entryCount = static_cast<s32>(m_cmdList->listEnd) - static_cast<s32>(m_cmdList->count);

	for (s32 i = 0; i < entryCount; i++) {
		if (timer >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= timer) {
				doneCount++;
				entry->alpha = 0.0f;
				entry->dx = 0.0f;
				entry->dy = 0.0f;
			} else {
				entry->timer++;
				const double step = 1.0 / static_cast<double>(entry->duration);
				entry->alpha = static_cast<float>(1.0 - step * static_cast<double>(entry->timer));
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
		selEntry = &m_cmdList->entries[m_cmdState->selected[0]];
		selEntry->x = m_cmdList->entries[0].x;
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
	s32 i;
	s16* list;
	CCaravanWork* caravanWork;

	caravanWork = Game.m_scriptFoodBase[0];
	list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	for (i = count = 0; i < CCaravanWork::kInventoryCapacity; i++) {
		s32 itemType = GetItemType(i, 0);
		if ((itemType != 0) && (itemType != 5) && (itemType != 6) && (itemType != 8) && (itemType != 9)) {
			if (itemType == 1) {
				const s32 tribe = caravanWork->m_tribeId & 3;
				const s32 icon = GetItemIcon(caravanWork->m_inventoryItems[i]);
				if (icon != tribe) {
					continue;
				}
			}
			count++;
			list[count] = static_cast<s16>(i);
		}
	}

	for (i = 0; i < 0x49; i++) {
		s32 arti = i + 0x9f;
		if (caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + i] == arti) {
			if (IsMagicArti(arti)) {
				count++;
				list[count] = static_cast<s16>(i + CCaravanWork::kPermanentArtifactStart);
			}
		}
	}

	for (i = 0; i < CCaravanWork::kTemporaryArtifactCount; i++) {
		s16 item = caravanWork->m_inventoryItems[CCaravanWork::kTemporaryArtifactStart + i];
		if (IsMagicArti(item)) {
			count++;
			list[count] = static_cast<s16>(CCaravanWork::kTemporaryArtifactStart + i);
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
inline int CMenuPcs::ChkCmdActive(int itemIndex)
{
	const CCaravanWork* const caravan = Game.m_scriptFoodBase[0];
	const s16* list = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	const s16* items = list + 1;
	const s32 count = list[0];
	bool canUse;
	if ((itemIndex < 0) || (itemIndex >= count)) {
		canUse = false;
	} else if (itemIndex == 0) {
		canUse = caravan->m_commandListInventorySlotRef[m_cmdState->selected[0]] >= 0;
	} else if (itemIndex == 1) {
		int combo[5][2];
		canUse = ChkUnite(m_cmdState->selected[0], combo) != 0;
	} else {
		canUse = !EquipChk(static_cast<int>(items[itemIndex - 2]));
	}
	return canUse;
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
	int j;
	int slot;
	int matchCount;
	const CCaravanWork* const caravan = Game.m_scriptFoodBase[0];
	int itemKinds[10];
	int matches[5][2];
	int candidates[10];
	int k;
	int ok;
	int i;
	int len;

	if (comboOut != nullptr) {
		for (i = 0; i < 5; i++) {
			comboOut[i][0] = -1;
			comboOut[i][1] = -1;
		}
	}

	const s16 selectedState = caravan->m_commandListExtra[selected];
	const s32 selectedFlag = selectedState > 0 ? 1 : 0;

	if ((m_cmdState->mode == 1) && (m_cmdState->phase == 2)) {
		if (selectedState < 0) {
			selected--;
		}
		if (caravan->m_commandListExtra[selected] < 0) {
			selected--;
		}
	}

	memset(candidates, 0xff, sizeof(candidates));

	for (slot = 2; slot < 8; slot++) {
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

	for (slot = 2; slot < 8; slot++) {
		if (caravan->m_numCmdListSlots <= slot) {
			break;
		}
		j = caravan->m_commandListInventorySlotRef[slot];
		if (j < 0) {
			continue;
		}

		i = caravan->m_inventoryItems[j];
		const int icon = GetItemIcon(i);

		if (IsMagicArti(i)) {
			if (i == 0xdf) {
				itemKinds[slot] = 0x100;
			} else if (i == 0xe0) {
				itemKinds[slot] = 0x101;
			} else if (i == 0xe1) {
				itemKinds[slot] = 0x102;
			} else if (i == 0xe2) {
				itemKinds[slot] = 0x105;
			} else {
				itemKinds[slot] = 0x107;
			}
		} else if ((icon == kIconClavatWeapon) || (icon == kIconLiltyWeapon) || (icon == kIconYukeWeapon) || (icon == kIconSelkieWeapon)) {
			itemKinds[slot] = 999;
		} else if ((icon == 0x10) || (icon == 0x11)) {
			itemKinds[slot] = i;
		} else {
			itemKinds[slot] = -1;
		}
	}

	if (itemKinds[selected] <= 0) {
		return 0;
	}

	matchCount = 0;
	memset(matches, 0xff, sizeof(matches));

	if ((itemKinds[selected] == 999) && (selected > 2)) {
		for (int patIdx = 0; s_Unite[patIdx].command >= 0; patIdx++) {
			const UniteRecipe* pat = &s_Unite[patIdx];
			if (pat->food == 0) {
				continue;
			}
			len = pat->count;
			if ((len == 2) && (selectedFlag != 0)) {
				continue;
			}
			k = ok = 0;
			for (; k < len - 1; k++) {
				slot = selected - (len - 1 - k);
				if (candidates[slot] != 0) {
					break;
				}
				if (pat->ingredients[k] == itemKinds[slot]) {
					ok++;
				}
			}
			if (ok == len - 1) {
				matches[matchCount][0] = patIdx;
				matches[matchCount++][1] = selected - (len - 1);
			}
		}
	} else if (selectedFlag == 0) {
		len = static_cast<int>(s_Unite[0].count);
		i = selected - (len - 1);
		for (j = 0; j < len; j++, i++) {
			k = ok = 0;
			for (; k < len; k++) {
				slot = j + (selected - ((len - 1) - k));
				if (candidates[slot] != 0) {
					break;
				}
				if (s_Unite[0].ingredients[k] == itemKinds[slot]) {
					ok++;
				}
			}
			if (ok == len) {
				matches[matchCount][0] = 0;
				matches[matchCount++][1] = i;
			}
		}
	}

	for (int group = 1; s_Unite[group].command >= 0; group++) {
		const UniteRecipe* pat = &s_Unite[group];
		if (((pat->food != 0) && (itemKinds[selected] == 999) && (selected > 2)) ||
		    ((pat->count == 2) && (selectedFlag != 0))) {
			continue;
		}

		len = pat->count;
		for (i = 0; i < len; i++) {
			if ((i == 0) && (selectedFlag != 0)) {
				i++;
			}

			k = ok = 0;
			for (; k < len; k++) {
				slot = i + (selected - ((len - 1) - k));
				if (candidates[slot] != 0) {
					break;
				}
				if (pat->ingredients[k] == itemKinds[slot]) {
					ok++;
				}
			}

			if (ok == len) {
				matches[matchCount][0] = group;
				matches[matchCount++][1] = i + (selected - (len - 1));
			}
		}
	}

	int n = 0;
	for (int rank = 0; rank < 2; rank++) {
		for (i = 0; i < matchCount; i++) {
			if (rank + 2 == s_Unite[matches[i][0]].count) {
				comboOut[n][0] = matches[i][0];
				comboOut[n][1] = matches[i][1];
				n++;
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
inline void CMenuPcs::CmdUnite(int recipe, int start)
{
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
	caravanWork->UniteComList(start, s_Unite[recipe].count, s_Unite[recipe].command);
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
	CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
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
	char* text;
	float panelAlpha;
	CFont* helpFont;
	float panelX;
	GXColor color;
	s32 i;
	s32 active;
	s32 groupSize;
	s32 groupStart;
	float drawY;
	float drawW;
	float drawH;
	const CCaravanWork* const caravan = Game.m_scriptFoodBase[0];

	AlphaNormal();
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	CmdListEntry* unitePanels = &m_cmdList->entries[m_cmdList->listEnd];
	const s32 topX = m_cmdList->entries[0].x;
	s_ucnt = 0;
	active = 0;

	for (i = 0; i < 8; i++) {
		if (i == m_cmdState->selected[0]) {
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

		CmdListEntry* const entry = &m_cmdList->entries[i];
		const float rectX = static_cast<float>(entry->x + 4);
		drawY = static_cast<float>(entry->y);
		drawW = static_cast<float>(entry->width - 8);
		const float rectU = static_cast<float>(entry->u);
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

			if ((i <= m_cmdState->selected[0]) && (m_cmdState->selected[0] < i + groupSize)) {
				if ((m_cmdState->phase == 3) && (i != m_cmdState->selected[0])) {
					m_cmdState->selected[0] = static_cast<s16>(i);
				}
				active = 1;
			}
		}

		MenuPcs.SetTexture((groupSize == 2) ? static_cast<CMenuPcs::TEX>(kCmdUniteListPairTexture) : static_cast<CMenuPcs::TEX>(kCmdUniteListTexture));
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

	CFont* font = GetFont22();
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(0.9f);
	font->DrawInit();
	font->SetTlut(7);

	CmdListEntry* entry = m_cmdList->entries;
	for (i = 0; i < caravan->m_numCmdListSlots; i++, entry++) {
		if ((i < 8) && (caravan->m_commandListExtra[i] == 0)) {
			continue;
		}

		const float alpha = (m_cmdState->mode == 3) ? 1.0f : entry->alpha;
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)));

		if (i < 2) {
			text = GetMenuStr(i + 9);
		} else {
			const s32 itemIdx = caravan->m_commandListInventorySlotRef[i];
			if (itemIdx < 0) {
				continue;
			}
			const s32 skillId = caravan->m_inventoryItems[itemIdx];
			text = Game.GetShortItemName(skillId);
		}

		const float width = static_cast<float>(font->GetWidth(text));
		float x = static_cast<float>((static_cast<float>(entry->width) - width) / 2.0 +
		                             static_cast<double>(entry->x));
		if (topX != entry->x) {
			const float target = static_cast<float>(entry->x + entry->width - 0x18) - width;
			x = (target - x) * static_cast<float>(__fabs(static_cast<double>(topX - entry->x)) / 64.0) + x;
		}

		drawY = static_cast<float>(entry->y + 3);
		font->SetPosX(x);
#ifdef VERSION_GCCJGC
		font->SetPosY(drawY);
#else
		font->SetPosY(drawY - 4.0f);
#endif
		font->Draw(text);
	}

	DrawInit();
	for (i = 0; i < 8; i++) {
		if (i == m_cmdState->selected[0]) {
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

			if ((i <= m_cmdState->selected[0]) && (m_cmdState->selected[0] < i + groupSize)) {
				active = 1;
			}
		}

		if (i != groupStart + groupSize - 1) {
			continue;
		}

		CmdListEntry* const endEntry = &m_cmdList->entries[i];
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kCmdUniteRowTexture));

		const s32 labelAnchor =
		    (groupStart == m_cmdState->selected[0]) ? groupStart + 1 : groupStart;
		panelX =
		    static_cast<float>(topX - (m_cmdList->entries[labelAnchor].x - topX));
		drawW = 208.0f;
		drawH = 64.0f;
		const float panelTone = active ? 64.0f : 0.0f;
		CmdListEntry* const startEntry = &m_cmdList->entries[groupStart];
		drawY = static_cast<float>(
		    (static_cast<float>(endEntry->y + endEntry->height - startEntry->y) - 64.0f) /
		        2.0 +
		    static_cast<double>(startEntry->y));

		if (m_cmdState->mode == 3) {
			panelAlpha = startEntry->alpha;
		} else {
			panelAlpha = static_cast<float>(
			    __fabs(static_cast<double>(panelX - static_cast<float>(topX))) / 64.0);
		}

		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = static_cast<u8>(255.0f * panelAlpha);
		GXSetChanMatColor((_GXChannelID)4, color);

		unitePanels[s_ucnt].x = panelX;
		unitePanels[s_ucnt].y = static_cast<s16>(drawY);
		unitePanels[s_ucnt].width = static_cast<s16>(drawW);
		unitePanels[s_ucnt].height = static_cast<s16>(drawH);
		unitePanels[s_ucnt].u = 0.0f;
		unitePanels[s_ucnt].v = panelTone;
		unitePanels[s_ucnt].alpha = panelAlpha;
		s_UniteTop[s_ucnt] = groupStart;
		s_ucnt++;

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

	font = GetFont22();
	font->SetMargin(1.0f);
	font->SetShadow(1);
	font->SetScale(1.0f);
	font->DrawInit();
	font->SetTlut(6);

	for (i = 0; i < s_ucnt; i++, unitePanels++) {
		const float alpha = (m_cmdState->mode == 3) ? 1.0f : unitePanels->alpha;
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * alpha)));

		const int itemId = caravan->m_commandListExtra[s_UniteTop[i]];
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
			text = Game.GetShortItemName(itemId);
		}
		const float width = static_cast<float>(font->GetWidth(text));
		drawY = static_cast<float>(
		    (static_cast<double>(unitePanels->height) - 19.8) / 2.0 +
		    static_cast<double>(unitePanels->y) - 2.0);
		font->SetPosX(static_cast<float>((static_cast<float>(unitePanels->width) - width) / 2.0 +
		                                 static_cast<double>(unitePanels->x)));
#ifdef VERSION_GCCJGC
		font->SetPosY(drawY);
#else
		font->SetPosY(drawY - 4.0f);
#endif
		font->Draw(text);
	}

	DrawInit();
	{
		CmdState* const helpStateView = m_cmdState;
		const s32 helpMode = helpStateView->mode;
		const s32 helpSelected = helpStateView->selected[0];
		if (helpMode == 0) {
		const s16 helpSlot = caravan->m_commandListExtra[helpSelected];
		if (helpSlot != 0) {
			int helpId = helpSlot;
			const u8 helpAlpha =
			    static_cast<u8>(255.0f * m_cmdList->entries[0].alpha);
#ifndef VERSION_GCCJGC
			if (helpSlot == 0x207 || helpSlot == 0x20B || helpSlot == 0x20F) {
				helpId += 2;
			}
#endif

			helpFont = GetFont22();
			DrawHelpMessage(
				helpId, helpFont,
				static_cast<int>(-(drawW / 2.0f - 320.0f)),
				static_cast<int>(drawY),
				CColor(0xFF, 0xFF, 0xFF, helpAlpha), 10,
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
	CmdListEntry* entry;
	int i;
	int j;
	int idx;
	int finished;

	if (s_ucnt == 0) {
		return 1;
	}

	const CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
	float baseX = static_cast<float>(m_cmdList->entries[0].x);

	if (topIdx > 0) {
		for (i = 0; i < 3; i++) {
			idx = i + s_UniteTop[topIdx];
			entry = &m_cmdList->entries[idx];
			if ((i != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
				break;
			}

			entry->x += 12.8;
			if (__fabs(static_cast<double>(static_cast<float>(entry->x) - baseX)) >
			    64.0) {
				entry->x = static_cast<s16>(64.0f + baseX);
				return 1;
			}
		}
	} else {
		for (i = finished = 0; i < s_ucnt; i++) {
			for (j = 0; j < 3; j++) {
				idx = j + s_UniteTop[i];
				entry = &m_cmdList->entries[idx];
				if ((j != 0) && (caravanWork->m_commandListExtra[idx] != -1)) {
					break;
				}

				entry->x += 12.8;
				if (__fabs(static_cast<double>(static_cast<float>(entry->x) - baseX)) >
				    64.0) {
					entry->x = static_cast<s16>(64.0f + baseX);
					if (j == 0) {
						finished++;
					}
				}
			}
		}
		if (finished == s_ucnt) {
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
	if (s_ucnt == 0) {
		return 1;
	}

	const CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
	float baseX = static_cast<float>(m_cmdList->entries[0].x);

	if (topIdx >= 0) {
		CmdListEntry* entry;
		int i;
		int idx;
		int finished;
		finished = 0;
		for (i = 0; i < 3; i++) {
			idx = i + s_UniteTop[topIdx];
			entry = &m_cmdList->entries[idx];
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
		int i;
		int idx;
		CmdListEntry* entry;
		int j;
		int finished;
		for (i = finished = 0; i < s_ucnt; i++) {
			for (j = 0; j < 3; j++) {
				idx = j + s_UniteTop[i];
				entry = &m_cmdList->entries[idx];
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
		}
		if (finished == s_ucnt) {
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
	const CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
	s32 i;
	s32 slot;

	m_cmdState->transitionTimer++;

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
		animEntry->y = static_cast<s16>(((static_cast<f32>(baseEntry->height) -
		                                   static_cast<f32>(animEntry->height) * animEntry->scale) /
		                                      2.0 +
		                                  static_cast<f64>(baseEntry->y)) -
		                                 3.0);
		animEntry->u = 0.0f;
		animEntry->v = 0.0f;
		animEntry->tex = kCmdUnitePanelTexture;
		m_cmdState->unitePanelInitialized = 1;
	}

	animEntry->alpha = static_cast<f32>(0.2 * static_cast<f64>(m_cmdState->transitionTimer));
	int done = (static_cast<f64>(m_cmdState->transitionTimer) >= 5.0) ? 1 : 0;
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
	s32 i;
	s32 selected;
	CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];

	m_cmdState->transitionTimer++;
	s16 state = m_cmdState->uniteState;
	s32 done;
	int combo[5][2];

	if (state == 0) {
		selected = m_cmdState->selected[0];
		for (i = 0; i < 3; i++) {
			if ((i != 0) && (caravanWork->m_commandListExtra[selected + i] != -1)) {
				break;
			}
			m_cmdList->entries[selected + i].alpha =
				static_cast<float>(0.2 * static_cast<f64>(m_cmdState->transitionTimer));
		}

		CmdListEntry* const animEntry = &m_cmdList->entries[m_cmdList->listEnd + 3];
		animEntry->alpha =
			static_cast<float>(-(0.2 * static_cast<f64>(m_cmdState->transitionTimer) - 1.0));
		int nextState = (1.0 == static_cast<f64>(animEntry->scale)) ? 2 : 3;

		done = (static_cast<f64>(m_cmdState->transitionTimer) >= 5.0) ? 1 : 0;
		if ((done != 0) && (m_cmdState->commandResult > 0)) {
			m_cmdState->commandResult = 0;
			s16 choice = m_cmdState->selected[2];
			if (choice == 0) {
				m_cmdState->uniteState = 1;
				done = 0;
			} else if ((nextState == 3) && (choice == 1)) {
				m_cmdState->uniteState = 2;
				done = 0;
			}
		}
		if (done != 0) {
			m_cmdState->commandResult = 0;
		}
	} else if (state == 1) {
		selected = m_cmdState->selected[0];
		s32 uniteIdx = 0;
		s32 topCount = s_ucnt;
		for (; uniteIdx < topCount; uniteIdx++) {
			if (s_UniteTop[uniteIdx] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx));
		if (done != 0) {
			CCaravanWork* const cw = Game.m_scriptFoodBase[0];
			s32 ununiteCount;
			for (ununiteCount = 0; ununiteCount < 3; ununiteCount++) {
				if ((ununiteCount != 0) && (cw->m_commandListExtra[selected + ununiteCount] != -1)) {
					break;
				}
			}
			cw->UnuniteComList(selected, ununiteCount);
		}
	} else if (state == 2) {
		selected = m_cmdState->selected[0];
		const s32 count = ChkUnite(static_cast<int>(selected), combo);
		if (count == 1) {
			done = 0;
			m_cmdState->uniteState = 3;
		} else {
			done = 1;
			m_cmdState->commandResult = 1;
		}
	} else if (state == 3) {
		selected = m_cmdState->selected[0];
		s32 uniteIdx = 0;
		s32 topCount = s_ucnt;
		for (; uniteIdx < topCount; uniteIdx++) {
			if (s_UniteTop[uniteIdx] == selected) {
				break;
			}
		}

		done = static_cast<u32>(UniteCloseAnim(uniteIdx));
		if (done != 0) {
			ChkUnite(static_cast<int>(selected), combo);

			CCaravanWork* const cw = Game.m_scriptFoodBase[0];
			const s32 sel = m_cmdState->selected[0];
			s32 ununiteCount;
			for (ununiteCount = 0; ununiteCount < 3; ununiteCount++) {
				if ((ununiteCount != 0) && (cw->m_commandListExtra[sel + ununiteCount] != -1)) {
					break;
				}
			}

			cw->UnuniteComList(sel, ununiteCount);
			CmdUnite(combo[0][0], combo[0][1]);

			done = 0;
			m_cmdState->selected[0] = static_cast<s16>(combo[0][1]);
			m_cmdState->uniteState = 4;
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
	int done;
	s32 selected;
	s32 limit;
	CCaravanWork* caravanWork;
	s32 prev;
	s32 next;

	caravanWork = Game.m_scriptFoodBase[0];

	m_cmdState->transitionTimer++;

	selected = static_cast<s32>(m_cmdState->selected[0]);
	for (prev = selected - 1; prev > 2; prev--) {
		if (caravanWork->m_commandListExtra[prev] >= 0) {
			break;
		}
	}

	limit = static_cast<s32>(caravanWork->m_numCmdListSlots);
	for (next = selected + 1; next < limit; next++) {
		if (caravanWork->m_commandListExtra[next] >= 0) {
			break;
		}
	}

	CmdListEntry* fadeEntry;
	s32 i;
	for (i = 0; i < static_cast<s32>(m_cmdList->count); i++, fadeEntry++) {
		if ((i < prev) || (i > next)) {
			fadeEntry = &m_cmdList->entries[i];
			fadeEntry->alpha = static_cast<float>(
			    -((0.1 * static_cast<double>(static_cast<s32>(m_cmdState->transitionTimer))) - 1.0));
			if (static_cast<double>(fadeEntry->alpha) < 0.5) {
				fadeEntry->alpha = 0.5f;
			}
		}
	}

	if (static_cast<double>(static_cast<s32>(m_cmdState->transitionTimer)) >= 5.0) {
		done = 1;
	} else {
		done = 0;
	}
	if (done != 0) {
		m_cmdState->selected[m_cmdState->mode] = static_cast<s16>(prev);
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
	CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
	int combo[5][2];
	s32 i;

	const s32 selected = static_cast<s32>(m_cmdState->selected[0]);
	const u32 modeSel = static_cast<s32>(m_cmdState->selected[m_cmdState->mode]);

	m_cmdState->transitionTimer++;

	if (m_cmdState->uniteState == 0) {
		m_cmdState->transitionTimer = 0;
		if (m_cmdState->commandResult < 0) {
			m_cmdState->uniteState = 3;
		} else if (caravanWork->m_commandListExtra[selected] != 0) {
			m_cmdState->uniteState = 1;
		} else {
			m_cmdState->uniteState = 2;
		}
		return 0;
	} else if (m_cmdState->uniteState == 1) {
		for (i = 0; i < s_ucnt; i++) {
			if (selected == s_UniteTop[i]) {
				break;
			}
		}

		if (UniteCloseAnim(i) != 0) {
			ChkUnite(selected, combo);
			int* comboSel = &combo[0][1];

			s32 comboIdx = 0;
			if (comboSel[0] < comboSel[2]) {
				comboIdx = (modeSel == static_cast<u32>(comboSel[0])) ? 0 : 1;
			} else {
				comboIdx = (modeSel == static_cast<u32>(comboSel[2])) ? 1 : 0;
			}

			const s32 closeSel = m_cmdState->selected[0];
			for (i = 0; i < 3; i++) {
				if ((i != 0) &&
				    (Game.m_scriptFoodBase[0]
				         ->m_commandListExtra[closeSel + i] != -1)) {
					break;
				}
			}

			Game.m_scriptFoodBase[0]
			    ->UnuniteComList(closeSel, i);
			CmdUnite(combo[comboIdx][0], comboSel[comboIdx * 2]);
			m_cmdState->selected[0] = static_cast<s16>(comboSel[comboIdx * 2]);
			m_cmdState->uniteState = 2;
		}
		return 0;
	} else if (m_cmdState->uniteState == 2) {
		if (caravanWork->m_commandListExtra[selected] == 0) {
			ChkUnite(selected, combo);
			int* comboSel = &combo[0][1];

			s32 comboIdx = 0;
			if (comboSel[0] < comboSel[2]) {
				comboIdx = (modeSel == static_cast<u32>(comboSel[0])) ? 0 : 1;
			} else {
				comboIdx = (!(modeSel == static_cast<u32>(comboSel[2]))) ? 0 : 1;
			}

			CmdUnite(combo[comboIdx][0], comboSel[comboIdx * 2]);
			m_cmdState->selected[0] = static_cast<s16>(comboSel[comboIdx * 2]);
		} else if (UniteOpenAnim(-1) != 0) {
			m_cmdState->uniteState = 3;
		}
		return 0;
	} else if (m_cmdState->uniteState == 3) {
		for (i = 0; i < static_cast<s32>(m_cmdList->count); i++) {
			CmdListEntry* entry = &m_cmdList->entries[i];
			if (static_cast<f64>(entry->alpha) >= 1.0) {
				continue;
			}
			entry->alpha = static_cast<f32>((0.1 * static_cast<f64>(m_cmdState->transitionTimer)) + 0.5);
			if (static_cast<f64>(entry->alpha) > 1.0) {
				entry->alpha = 1.0f;
			}
		}
		return (static_cast<f64>(m_cmdState->transitionTimer) >= 5.0) ? 1 : 0;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8014a940
 * PAL Size: 156b
 * EN Address: 0x80149A34
 * EN Size: 156b
 * JP Address: UNUSED
 * JP Size: TODO
 */
char* CMenuPcs::GetSkillStr(int index)
{
#ifdef VERSION_GCCJGC
	return s_SkillStr_jp[index];
#else
	switch (Game.m_gameWork.GetLanguage()) {
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
#endif
}
