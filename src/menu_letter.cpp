#include "ffcc/menu_letter.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/mes.h"
#include "ffcc/linkage.h"

#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdlib.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>


typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" const float FLOAT_80333088 = 592.0f;
extern "C" const float FLOAT_8033308c = 160.0f;
extern "C" const double DOUBLE_80333090 = 0.7;
extern "C" const double DOUBLE_80333098 = 0.03;
extern "C" const float FLOAT_803330a0 = 255.0f;
extern "C" const double DOUBLE_803330a8 = 0.5;
extern "C" const double DOUBLE_803330b0 = 0.05;
extern "C" const float FLOAT_803330b8 = 48.0f;
extern "C" const float FLOAT_803330bc = 0.0f;
extern "C" const float FLOAT_803330c0 = 112.0f;
extern "C" const double DOUBLE_803330c8 = 4503601774854144.0;
extern "C" const float FLOAT_803330d0 = 480.0f;
extern "C" const float FLOAT_803330d4 = 288.0f;
extern "C" const double DOUBLE_803330d8 = 64.0;
extern "C" const float FLOAT_803330e0 = 72.0f;
extern "C" const double DOUBLE_803330e8 = 1.0;
extern "C" const float FLOAT_803330f0 = 336.0f;
extern "C" const float FLOAT_803330f4 = 32.0f;
extern "C" const float FLOAT_803330f8 = 1.0f;
extern "C" const double DOUBLE_80333100 = 8.0;
extern "C" const float FLOAT_80333108 = 16.0f;
extern "C" const float FLOAT_8033310c = 24.0f;
extern "C" const float FLOAT_80333110 = 8.0f;
extern "C" const double DOUBLE_80333118 = 24.0;
extern "C" const double DOUBLE_80333120 = 32.0;
extern "C" const float FLOAT_80333128 = 56.0f;
extern "C" const float FLOAT_8033312c = 88.0f;
extern "C" const float FLOAT_80333130 = 184.0f;
extern "C" const float FLOAT_80333134 = 152.0f;
extern "C" const float FLOAT_80333138 = 144.0f;
extern "C" const float FLOAT_8033313c = 3.0f;
extern "C" const float FLOAT_80333140 = 1.2000000476837158f;
extern "C" const float FLOAT_80333144 = 136.0f;
extern "C" const float FLOAT_80333148 = 4.0f;
extern "C" const float FLOAT_8033314c = 472.0f;
extern "C" const float FLOAT_80333150 = 296.0f;
extern "C" const float FLOAT_80333154 = 2.0f;
extern "C" const float FLOAT_80333158 = 640.0f;
extern "C" const float FLOAT_8033315c = 40.0f;
extern "C" const float FLOAT_80333160 = 64.0f;
extern "C" const float FLOAT_80333164 = 352.0f;
extern "C" const float FLOAT_80333168 = 536.0f;

static const char s_fmt_pcts_pcts[] = "%s%s";
static const char s_fmt_pcts_pcts_pcts[] = "%s%s%s";
static const char s_fmt_pcts_sp_pcts_dot[] = "%s %s.";
static const char s_fmt_pcts_sp_pcts_pcts[] = "%s %s%s";
#ifdef VERSION_GCCE01
static const char s_fmt_pcts_sp[] = "%s ";
#endif
static const char s_fmt_pctd_sp_pcts[] = "%d %s";
#ifdef VERSION_GCCJGC
static const char s_fmt_pctd[] = "%d";
static const char s_fmt_two_spaces[] = "　";
#else
static const char s_fmt_two_spaces[] = "  ";
#endif
static const char s_fmt_pctd_sp_pcts_pcts[] = "%d %s%s";
static const char s_fmt_pcts_pcts_q[] = "%s%s?";

static short s_SelLetter = 0;
static unsigned char s_OpenClose = 0;
static signed char s_ReplyMax = 0;
static signed char s_ReplyPos = 0;
static signed char s_Attach = 0;
static signed char s_AttachItemIdx = 0;
static int s_AttachItem = 0;
static int s_AttachMode = 0;
static int s_BackUpCur[2];
static int s_BackUpTopPos = 0;
static char s_ReplyStr[0x80];

extern "C" const char s_menu_letter_cpp[] = "menu_letter.cpp";
namespace {
const char s_letterItemInfoFmt[] = "%s%s%s%s";
}  // namespace
static const char s_pctspctspctspcts[] = "%s%s%s%s?";
static const char s_pctspctd_pcts_801DEE20[] = "%s%d %s?";

namespace {
STATIC_ASSERT(offsetof(SingleFadeEntry, x) == 0x00);
STATIC_ASSERT(offsetof(SingleFadeEntry, y) == 0x02);
STATIC_ASSERT(offsetof(SingleFadeEntry, width) == 0x04);
STATIC_ASSERT(offsetof(SingleFadeEntry, height) == 0x06);
STATIC_ASSERT(offsetof(SingleFadeEntry, u) == 0x08);
STATIC_ASSERT(offsetof(SingleFadeEntry, v) == 0x0C);
STATIC_ASSERT(offsetof(SingleFadeEntry, alpha) == 0x10);
STATIC_ASSERT(offsetof(SingleFadeEntry, uvScale) == 0x14);
STATIC_ASSERT(offsetof(SingleFadeEntry, unk18) == 0x18);
STATIC_ASSERT(offsetof(SingleFadeEntry, tex) == 0x1C);
STATIC_ASSERT(offsetof(SingleFadeEntry, elapsed) == 0x20);
STATIC_ASSERT(offsetof(SingleFadeEntry, startFrame) == 0x24);
STATIC_ASSERT(offsetof(SingleFadeEntry, duration) == 0x28);
STATIC_ASSERT(offsetof(SingleFadeEntry, flags) == 0x2C);
STATIC_ASSERT(offsetof(SingleFadeEntry, dx) == 0x30);
STATIC_ASSERT(offsetof(SingleFadeEntry, dy) == 0x34);
STATIC_ASSERT(offsetof(SingleFadeEntry, targetX) == 0x38);
STATIC_ASSERT(offsetof(SingleFadeEntry, targetY) == 0x3C);
STATIC_ASSERT(offsetof(SingleFadeState, entries) == 8);
STATIC_ASSERT(offsetof(CCaravanWork, m_letters) == 0x3EC);

enum {
	kLetterTextScratchSize = 0x400,
};

enum {
#ifdef VERSION_GCCJGC
	kLetterTexBase = 0x3B,
#else
	kLetterTexBase = 0x3C,
#endif
};

static inline CCaravanWork* GetLetterCaravanWork()
{
	return Game.m_scriptFoodBase[0];
}

static inline CMemory::CStage* GetLetterMenuStage(CMenuPcs* menu)
{
	(void)menu;
	if (Game.m_gameWork.m_menuStageMode != 0) {
		return MenuPcs.m_stageF4;
	}
	return MenuPcs.m_menuStage;
}
} // namespace

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 244b
 * EN Address: 0x801867F4
 * EN Size: 268b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::LetterInit()
{
	memset(m_singleFadeState, 0, sizeof(*m_singleFadeState));
	SingleFadeEntry* entry = m_singleFadeState->entries;
	for (int i = 0; i < 64; ++i, ++entry) {
		entry->uvScale = FLOAT_803330f8;
	}

	int index = 0;
	entry = &m_singleFadeState->entries[index++];
	entry->tex = 0;
	entry->startFrame = 0;
	entry->duration = 10;
	entry = &m_singleFadeState->entries[index++];
	entry->tex = 0;
	entry->startFrame = m_singleMenuCtrlResetFlag ? 0 : 10;
	entry->duration = 10;
	m_singleFadeState->count = index;
	m_letterMenuState->frame = 0;
	m_letterMenuState->initialized = 1;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 224b
 * EN Address: 0x80186900
 * EN Size: 216b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::LetterInit0()
{
	int index = 0;
	SingleFadeEntry* entry = &m_singleFadeState->entries[index++];
	entry->startFrame = 0;
	entry->duration = 10;
	entry = &m_singleFadeState->entries[index++];
	entry->startFrame = 0;
	entry->duration = 10;

	int count = m_singleFadeState->count;
	entry = m_singleFadeState->entries;
	for (int i = 0; i < count; ++i, ++entry) {
		entry->elapsed = 0;
		entry->alpha = FLOAT_803330f8;
	}
	m_letterMenuState->frame = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 216b
 * EN Address: 0x80186B9C
 * EN Size: 200b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::LetterInit2()
{
	int index = 0;
	SingleFadeEntry* entry = &m_singleFadeState->entries[index++];
	entry->tex = 0;
	entry->startFrame = 10;
	entry->duration = 10;
	entry = &m_singleFadeState->entries[index++];
	entry->tex = 0;
	entry->startFrame = 0;
	entry->duration = 10;

	int count = m_singleFadeState->count;
	entry = m_singleFadeState->entries;
	for (int i = 0; i < count; ++i, ++entry) {
		entry->elapsed = 0;
		entry->alpha = FLOAT_803330f8;
	}
	m_letterMenuState->frame = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 176b
 * EN Address: 0x80186C64
 * EN Size: 184b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::LetterInit3()
{
	memset(m_singleFadeState, 0, sizeof(*m_singleFadeState));
	SingleFadeEntry* entry = m_singleFadeState->entries;
	for (int i = 0; i < 64; ++i, ++entry) {
		entry->uvScale = FLOAT_803330f8;
	}

	int index = 0;
	entry = &m_singleFadeState->entries[index++];
	entry->tex = 0;
	entry->startFrame = 0;
	entry->duration = 10;
	m_singleFadeState->count = index;
	m_letterMenuState->frame = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 204b
 * EN Address: 0x80186D1C
 * EN Size: 180b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::LetterInit4()
{
	int index = 0;
	SingleFadeEntry* entry = &m_singleFadeState->entries[index++];
	entry->tex = 0;
	entry->startFrame = 0;
	entry->duration = 10;
	m_singleFadeState->count = index;

	int count = m_singleFadeState->count;
	entry = m_singleFadeState->entries;
	for (int i = 0; i < count; ++i, ++entry) {
		entry->elapsed = 0;
		entry->alpha = FLOAT_803330f8;
	}
	m_letterMenuState->frame = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 384b
 * EN Address: 0x80187678
 * EN Size: 536b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterLstOpen()
{
	SingleFadeEntry* panel;
	int done;
	int count;
	int frame;

	done = 0;
	m_letterMenuState->frame = m_letterMenuState->frame + 1;
	count = static_cast<int>(m_singleFadeState->count);
	panel = m_singleFadeState->entries;
	frame = static_cast<int>(m_letterMenuState->frame);
	for (int i = 0; i < count; ++i) {
		{
			float progress = FLOAT_803330bc;
			if (frame >= panel->startFrame) {
				if (panel->startFrame + panel->duration <= frame) {
					done = done + 1;
					panel->alpha = FLOAT_803330f8;
					panel->dx = progress;
					panel->dy = progress;
				} else {
					panel->elapsed = panel->elapsed + 1;
					panel->alpha = (1.0 / (float)panel->duration) * (float)panel->elapsed;
					if ((panel->flags & 2) == 0) {
						progress = (1.0 / (float)panel->duration) * (float)panel->elapsed;
						float dx = panel->targetX - static_cast<float>(panel->x);
						float dy = panel->targetY - static_cast<float>(panel->y);
						panel->dx = dx * progress;
						panel->dy = dy * progress;
					}
				}
			}
		}
		panel++;
	}
	int finished = 0;
	if (count == done) {
		finished = 1;
	}
	return finished;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 380b
 * EN Address: 0x80187890
 * EN Size: 552b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterLstClose()
{
	LetterMenuState* state = m_letterMenuState;
	state->frame = state->frame + 1;

	SingleFadeEntry* entry = m_singleFadeState->entries;
	int finished = 0;
	int panelCount = static_cast<int>(m_singleFadeState->count);
	int frame = static_cast<int>(m_letterMenuState->frame);

	for (int i = 0; i < panelCount; ++i, ++entry) {
		float f = FLOAT_803330bc;
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				++finished;
				entry->alpha = FLOAT_803330bc;
				entry->dx = f;
				entry->dy = f;
			} else {
				entry->elapsed = entry->elapsed + 1;
				entry->alpha = 1.0 - (1.0 / (float)entry->duration) * (float)entry->elapsed;
				if ((entry->flags & 2) == 0) {
					f = 1.0 - (1.0 / (float)entry->duration) * (float)entry->elapsed;
					float dx = entry->targetX - static_cast<float>(entry->x);
					float dy = entry->targetY - static_cast<float>(entry->y);
					entry->dx = dx * f;
					entry->dy = dy * f;
				}
			}
		}
	}

	int allFinished = 0;
	if (panelCount == finished) {
		allFinished = 1;
	}
	return allFinished;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 436b
 * EN Address: 0x80187AB8
 * EN Size: 124b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterMessOpen()
{
	CCaravanWork* caravanWork = GetLetterCaravanWork();
	if (!caravanWork->m_letters[s_SelLetter].m_bits.m_opened) {
		caravanWork->m_letters[s_SelLetter].m_bits.m_opened = 1;
	}
	return LetterLstOpen();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 380b
 * EN Address: 0x80187B34
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterMessClose()
{
	return LetterLstClose();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 636b
 * EN Address: 0x80187B5C
 * EN Size: 544b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterItemWinOpen()
{
#ifndef VERSION_GCCJGC
	int lang = Game.m_gameWork.m_languageId;
#endif
	CCaravanWork* caravanWork = GetLetterCaravanWork();
	if (m_letterMenuState->dialogInitialized == '\0') {
		char info[0x80];
		char left[0x10];
		char right[0x10];
		s16 winW;
		s16 winH;
#ifdef VERSION_GCCJGC
		if (caravanWork->m_letters[s_SelLetter].m_bits.m_attachmentIsGil) {
			sprintf(info, s_fmt_pctd, caravanWork->m_letters[s_SelLetter].m_bits.m_attachValue * 100);
			strcat(info, GetMenuStr(0x15));
		} else {
			strcpy(info, Game.GetShortItemName(caravanWork->m_letters[s_SelLetter].m_bits.m_attachValue));
		}
		strcat(info, GetMenuStr(0x22));
#else
		if (caravanWork->m_letters[s_SelLetter].m_bits.m_attachmentIsGil) {
			int gil = caravanWork->m_letters[s_SelLetter].m_bits.m_attachValue * 100;
			if (lang == 2) {
				sprintf(info, s_fmt_pctd_sp_pcts_pcts,
				        gil,
				        GetMenuStr(4),
				        GetMenuStr(0x22));
			} else {
				sprintf(info, s_pctspctd_pcts_801DEE20,
				        GetMenuStr(0x22),
				        gil,
				        GetMenuStr(4));
			}
		} else {
			int value = caravanWork->m_letters[s_SelLetter].m_bits.m_attachValue;
			if (lang == 2) {
				sprintf(info, s_letterItemInfoFmt,
				        GetMenuStr(0x23),
				        Game.GetShortItemName(value),
				        GetMenuStr(0x24),
				        GetMenuStr(0x22));
			} else {
				sprintf(info, s_fmt_pcts_pcts_q, GetMenuStr(0x22), Game.GetShortItemName(value));
			}
		}
#endif
		strcpy(left, s_fmt_two_spaces);
		strcat(left, GetMenuStr(1));
		strcpy(right, s_fmt_two_spaces);
		strcat(right, GetMenuStr(2));
		SetSingDynamicWinMessInfo(3, info, left, right, 0, 0, 0, 0, 0);
		GetSingWinSize(0, &winW, &winH, 1);
		SetMcWinInfo(static_cast<int>(winW), static_cast<int>(winH));
		m_menuWindowInfo->state = 0;
		m_letterMenuState->choiceCursor = 0;
		m_letterMenuState->dialogInitialized = 1;
	}
	int done = 0;
	if (m_menuWindowInfo->state == 1) {
		done = 1;
	}
	return done;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 160b
 * EN Address: 0x80188110
 * EN Size: 184b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterAttachWinOpen()
{
	if (m_letterMenuState->dialogInitialized == '\0') {
		s16 winW;
		s16 winH;
		GetSingWinSize(2, &winW, &winH, 0);
		SetMcWinInfo(static_cast<int>(winW), static_cast<int>(winH));
		m_menuWindowInfo->state = 0;
		m_letterMenuState->choiceCursor = 0;
		m_letterMenuState->messageMask = -1;
		m_letterMenuState->dialogInitialized = 1;
	}
	int done = 0;
	if (m_menuWindowInfo->state == 1) {
		done = 1;
	}
	return done;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: 0x80187D7C
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterItemWinClose()
{
	int done = 0;
	if (m_menuWindowInfo->state == 3) {
		m_letterMenuState->dialogInitialized = 0;
		done = 1;
	}
	return done;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: 0x801880D4
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterReplyWinClose()
{
	int done = 0;
	if (m_menuWindowInfo->state == 3) {
		m_letterMenuState->dialogInitialized = 0;
		done = 1;
	}
	return done;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: 0x801881C8
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterAttachWinClose()
{
	int done = 0;
	if (m_menuWindowInfo->state == 3) {
		m_letterMenuState->dialogInitialized = 0;
		done = 1;
	}
	return done;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 44b
 * EN Address: 0x8018856C
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::LetterConfirmClose()
{
	int done = 0;
	if (m_menuWindowInfo->state == 3) {
		m_letterMenuState->dialogInitialized = 0;
		done = 1;
	}
	return done;
}

/*
 * --INFO--
 * PAL Address: 0x8016394C
 * PAL Size: 64b
 * EN Address: 0x801629BC
 * EN Size: 64b
 * JP Address: 0x8015E4DC
 * JP Size: 64b
 */
void CMenuPcs::LetterSetAttachItem(unsigned int itemIndex, int flag)
{
	CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];

	if (s_Attach == 0) {
		s_AttachItemIdx = static_cast<signed char>(itemIndex);
		s_AttachItem = caravanWork->m_inventoryItems[itemIndex];
	} else {
		s_AttachItem = itemIndex;
	}
	s_AttachMode = flag;
}

/*
 * --INFO--
 * PAL Address: 0x8016398C
 * PAL Size: 1616b
 * EN Address: 0x801629FC
 * EN Size: 1616b
 * JP Address: 0x8015E51C
 * JP Size: 1616b
 */
void CMenuPcs::LetterLstBaseDraw(float openRatio)
{
	unsigned long flip;
	int i;
	float xw;
	float yh;
	float x0;
	float y0;
	float h;
	float x1;
	float w;
	float y1;

	if (openRatio <= FLOAT_803330bc) {
		return;
	}

	float grow = FLOAT_803330d0 * openRatio;
	float left = FLOAT_803330d4 - static_cast<float>(grow / 2.0);
	float top = FLOAT_803330e0;
	float width = DOUBLE_803330d8 + grow;
	float height = FLOAT_803330f0;
	int leftPx = static_cast<int>(static_cast<double>(left) - 0.5);
	int topPx = static_cast<int>(static_cast<double>(top) - 0.5);
	int widthPx = static_cast<int>(static_cast<double>(width) - 1.0);
	int heightPx = static_cast<int>(static_cast<double>(height) - 1.0);
	x0 = static_cast<float>(leftPx);
	y0 = static_cast<float>(topPx);
	w = static_cast<float>(widthPx);
	h = static_cast<float>(heightPx);

	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
	GXColor white;
	white.r = 0xFF;
	white.g = 0xFF;
	white.b = 0xFF;
	white.a = 0xFF;
	GXSetChanMatColor(GX_COLOR0A0, white);

	xw = x0 + w;
	yh = y0 + h;
	x1 = xw - FLOAT_803330f4;
	y1 = yh - FLOAT_803330f4;

	for (i = 0; i < 4; ++i) {
		int tex;
		flip = 0;
		if (i == 0) {
			tex = kLetterTexBase;
		} else if (i == 1) {
			tex = kLetterTexBase;
		} else if (i == 2) {
			tex = kLetterTexBase + 0xF;
		} else {
			tex = kLetterTexBase + 0x11;
		}

		float x;
		float y;
		if ((i & 1) != 0) {
			x = x1;
			if (i == 1) {
				flip |= 8;
			}
		} else {
			x = x0;
		}
		if ((i & 2) != 0) {
			y = y1;
		} else {
			y = y0;
		}

		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
		MenuPcs.DrawRect(
		    flip, x, y, FLOAT_803330f4, FLOAT_803330f4,
		    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, FLOAT_803330bc);
	}

	float innerX = FLOAT_803330f4 + x0;
	double innerW = w - DOUBLE_803330d8;
	float innerWf = static_cast<float>(innerW);
	float y = y0;
	for (i = 0; i < 2; ++i) {
		int tex = kLetterTexBase + 0xD;
		if (i != 0) {
			tex = kLetterTexBase + 0x10;
		}
		if (i != 0) {
			y = y1;
		}
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
		MenuPcs.DrawRect(
		    0, innerX, y, innerWf, FLOAT_803330f4,
		    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, FLOAT_803330bc);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kLetterTexBase + 0xE));
	float innerY = FLOAT_803330f4 + y0;
	double innerH = h - DOUBLE_803330d8;
	float x = x0;
	float innerHf = static_cast<float>(innerH);
	for (i = 0; i < 2; ++i) {
		flip = 0;
		if (i != 0) {
			flip |= 8;
			x = x1;
		}
		MenuPcs.DrawRect(
		    flip, x, innerY, FLOAT_803330f4, innerHf,
		    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, FLOAT_803330bc);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kLetterTexBase + 0x12));
	MenuPcs.DrawRect(
	    flip, innerX, innerY, static_cast<float>(innerW), static_cast<float>(innerH),
	    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, FLOAT_803330bc);

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kLetterTexBase + 0x13));
	float decoX = xw - FLOAT_80333108;
	double decoY0 = y0 - DOUBLE_80333100;
	double decoX1 = DOUBLE_80333100 + decoX;
	double decoY1 = DOUBLE_80333100 + (yh - FLOAT_8033310c);
	for (i = 0; i < 4; ++i) {
		flip = 0;
		float dx;
		float dy;
		if ((i & 1) != 0) {
			dx = static_cast<float>(decoX1);
		} else {
			dx = x0 - FLOAT_80333110;
		}
		if ((i & 2) != 0) {
			dy = static_cast<float>(decoY1);
			flip |= 4;
		} else {
			dy = static_cast<float>(decoY0);
		}
		MenuPcs.DrawRect(
		    flip, dx, dy, FLOAT_80333108, FLOAT_8033310c,
		    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, FLOAT_803330bc);
	}

	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kLetterTexBase + 0x14));
	float barX = x0 - FLOAT_80333110;
	float barX1 = FLOAT_80333110 + decoX;
	float barY0 = static_cast<float>((DOUBLE_80333118 + y0) - DOUBLE_80333100);
	float barY1 = barY0 + static_cast<float>(h - DOUBLE_80333120);
	for (i = 0; i < 2; ++i) {
		if (i != 0) {
			barX = barX1;
		}
		float by = barY0;
		while (by < barY1) {
			float seg = barY1 - by;
			if (seg >= DOUBLE_80333118) {
				seg = FLOAT_8033310c;
			}
			MenuPcs.DrawRect(
			    0, barX, by, FLOAT_80333108, seg,
			    FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, FLOAT_803330bc);
			by = by + seg;
		}
	}

	if (!(openRatio < DOUBLE_803330e8)) {
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kLetterTexBase + 0x1));
		MenuPcs.DrawRect(
		    0, x0 - FLOAT_803330f4, y0 - FLOAT_80333108,
		    FLOAT_80333128, FLOAT_8033312c, FLOAT_80333130, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, FLOAT_803330bc);
		MenuPcs.DrawRect(
		    0, xw - FLOAT_80333134, yh - FLOAT_803330c0,
		    FLOAT_80333130, FLOAT_80333138, FLOAT_803330bc, FLOAT_803330bc, FLOAT_803330f8, FLOAT_803330f8, FLOAT_803330bc);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80163FDC
 * PAL Size: 3844b
 * EN Address: 0x8016304C
 * EN Size: 3844b
 * JP Address: 0x8015EB6C
 * JP Size: 3900b
 */
int CMenuPcs::LetterCtrlCur()
{
	int press = static_cast<s16>(Pad.GetButtonDown(0));
	int hold = static_cast<s16>(Pad.GetButtonRepeat(0));

	if (hold == 0) {
		return 0;
	}

	CCaravanWork* const caravanWork = GetLetterCaravanWork();
	int menuMode = m_letterMenuState->mode;
	if (menuMode == 0) {
		int letterCount = caravanWork->m_letterCount;
		if ((letterCount == 0) && ((hold & 0xC) != 0)) {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
			return 0;
		}

		if ((hold & 8) != 0) {
			int cur = m_letterMenuState->listCursor;
			if (cur != 0) {
				m_letterMenuState->listCursor = cur - 1;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				int top = m_letterMenuState->topIndex;
				if (top != 0) {
					m_letterMenuState->topIndex = top - 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				}
			}
		} else if ((hold & 4) != 0) {
			int cursor = static_cast<int>(m_letterMenuState->listCursor);
			if ((cursor < 8) && (cursor < letterCount - 1)) {
				m_letterMenuState->listCursor = m_letterMenuState->listCursor + 1;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else if (m_letterMenuState->topIndex + cursor < letterCount - 1) {
				m_letterMenuState->topIndex = m_letterMenuState->topIndex + 1;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x20) != 0) {
				m_letterMenuState->cursorMove = 1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x40) != 0) {
				m_letterMenuState->cursorMove = -1;
				Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
				return 1;
			}
			if ((press & 0x100) != 0) {
				if (letterCount == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					m_letterMenuState->step = m_letterMenuState->step + 1;
					s_SelLetter = m_letterMenuState->topIndex + m_letterMenuState->listCursor;
					CMes::m_tempVar[0] = caravanWork->m_letters[s_SelLetter].m_half.m_tempVars[0];
					CMes::m_tempVar[1] = caravanWork->m_letters[s_SelLetter].m_half.m_tempVars[1];
					CMes::m_tempVar[2] = caravanWork->m_letters[s_SelLetter].m_half.m_tempVars[2];
					CMes::m_tempVar[3] = caravanWork->m_letters[s_SelLetter].m_half.m_tempVars[3];

					LetterInit2();
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			} else if ((press & 0x200) != 0) {
				m_letterMenuState->closeRequested = 1;
				Sound.PlaySe(3, 0x40, 0x7F, 0);
				return 1;
			}
		}
	} else if (menuMode == 1) {
		if ((press & 0x100) != 0) {
			if ((caravanWork->m_letters[s_SelLetter].m_bits.m_attachValue != 0) &&
			    !caravanWork->m_letters[s_SelLetter].m_bits.m_attachmentClaimed) {
				m_letterMenuState->action = 1;
				m_letterMenuState->messageMask = 5;
				int value = caravanWork->m_letters[s_SelLetter].m_bits.m_attachValue;
				if (caravanWork->m_letters[s_SelLetter].m_bits.m_attachmentIsGil) {
					if (caravanWork->CanAddGil(value * 100) != 0) {
						m_letterMenuState->messageMask |= 2;
					}
				} else {
					if (caravanWork->m_inventoryItemCount + 1 <= 0x40) {
						m_letterMenuState->messageMask |= 2;
					}
				}
				m_letterMenuState->step = m_letterMenuState->step + 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else if ((CFlat.CanReplyLetter() != 0) &&
			    caravanWork->m_letters[s_SelLetter].m_bits.m_hasReply &&
			    !caravanWork->m_letters[s_SelLetter].m_bits.m_replySent) {
				m_letterMenuState->action = 2;
				m_letterMenuState->step = m_letterMenuState->step + 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
#ifdef VERSION_GCCJGC
		}
		if ((press & 0x200) != 0) {
#else
		} else if ((press & 0x200) != 0) {
#endif
			m_letterMenuState->action = -1;
			m_letterMenuState->step = m_letterMenuState->step + 1;
			LetterInit0();
			Sound.PlaySe(3, 0x40, 0x7F, 0);
		}
	} else if (menuMode == 2) {
		if ((hold & 0xC) != 0) {
			m_letterMenuState->choiceCursor ^= 1;
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}
		if ((hold & 0xC) == 0) {
			if ((press & 0x100) != 0) {
			s16 sel = m_letterMenuState->choiceCursor;
			if ((static_cast<int>(m_letterMenuState->messageMask) & (1 << (sel + 1))) != 0) {
				if (sel == 0) {
					int value = caravanWork->m_letters[s_SelLetter].m_bits.m_attachValue;
					if (caravanWork->m_letters[s_SelLetter].m_bits.m_attachmentIsGil) {
						caravanWork->AddGil(value * 100);
					} else {
						caravanWork->AddItem(value, 0);
					}
					caravanWork->m_letters[s_SelLetter].SetAttachmentClaimed();
				}

				if ((CFlat.CanReplyLetter() != 0) &&
				    caravanWork->m_letters[s_SelLetter].m_bits.m_hasReply &&
				    !caravanWork->m_letters[s_SelLetter].m_bits.m_replySent) {
					m_letterMenuState->action = 1;
				} else {
					m_letterMenuState->action = -1;
				}
				m_letterMenuState->step = m_letterMenuState->step + 1;
				m_menuWindowInfo->state = 2;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		} else if ((press & 0x200) != 0) {
			if ((CFlat.CanReplyLetter() != 0) &&
			    caravanWork->m_letters[s_SelLetter].m_bits.m_hasReply &&
			    !caravanWork->m_letters[s_SelLetter].m_bits.m_replySent) {
				m_letterMenuState->action = 1;
			} else {
				m_letterMenuState->action = -1;
			}
			m_letterMenuState->step = m_letterMenuState->step + 1;
			m_menuWindowInfo->state = 2;
			Sound.PlaySe(3, 0x40, 0x7F, 0);
			}
		}
	} else if (menuMode == 3) {
		int maxReply = static_cast<int>(s_ReplyMax);
		if ((hold & 8) != 0) {
			int cur = m_letterMenuState->choiceCursor;
			if (cur != 0) {
				m_letterMenuState->choiceCursor = cur - 1;
			} else {
				m_letterMenuState->choiceCursor = maxReply - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else if ((hold & 4) != 0) {
			int cur = m_letterMenuState->choiceCursor;
			if (cur < maxReply - 1) {
				m_letterMenuState->choiceCursor = cur + 1;
			} else {
				m_letterMenuState->choiceCursor = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x100) != 0) {
				int curReply = m_letterMenuState->choiceCursor;
			if (curReply >= maxReply - 1) {
				m_letterMenuState->action = -1;
			} else {
				s_ReplyPos = static_cast<u8>(curReply);
#ifdef VERSION_GCCJGC
			char* srcText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x5C0) char[kLetterTextScratchSize];
			char* workText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x5C2) char[kLetterTextScratchSize];
#else
			char* srcText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x65E) char[kLetterTextScratchSize];
			char* workText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x660) char[kLetterTextScratchSize];
#endif
			memset(srcText, 0, kLetterTextScratchSize);
			memset(workText, 0, kLetterTextScratchSize);

			CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
			s16 msgIndex = letter->HeaderWord();
			strcpy(srcText, Game.GetLetterReply((msgIndex & 0x7FC) >> 2));
#ifdef VERSION_GCCJGC
			CMes::MakeAgbString(workText, srcText);
#else
			CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);
#endif

			int i = 0;
			char* line = workText;
			do {
					char* newline = strchr(line, '\n');
					if (newline != 0) {
						*newline = '\0';
					}
					if (i == s_ReplyPos) {
						strcpy(s_ReplyStr, line);
					}
					if (newline == 0) {
						break;
					}
					++i;
					line = newline + 1;
			} while (i < 7);

			delete[] srcText;
			delete[] workText;
				m_letterMenuState->action = 1;
			}

			m_letterMenuState->step = m_letterMenuState->step + 1;
			m_menuWindowInfo->state = 2;
			Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else if ((press & 0x200) != 0) {
				m_letterMenuState->action = -1;
				m_letterMenuState->step = m_letterMenuState->step + 1;
				m_menuWindowInfo->state = 2;
				Sound.PlaySe(3, 0x40, 0x7F, 0);
			}
		}
	} else if (menuMode == 4) {
		if ((hold & 8) != 0) {
			int cur = m_letterMenuState->choiceCursor;
			if (cur != 0) {
				m_letterMenuState->choiceCursor = cur - 1;
			} else {
				m_letterMenuState->choiceCursor = 3;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else if ((hold & 4) != 0) {
			int cur = m_letterMenuState->choiceCursor;
			if (cur < 3) {
				m_letterMenuState->choiceCursor = cur + 1;
			} else {
				m_letterMenuState->choiceCursor = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x100) != 0) {
				int choice = m_letterMenuState->choiceCursor;
				if (choice >= 3) {
					s_Attach = 2;
					m_letterMenuState->action = -1;
				} else {
					s_Attach = static_cast<signed char>(choice);
					m_letterMenuState->action = 1;
				}
				m_letterMenuState->step = m_letterMenuState->step + 1;
				s_AttachMode = 0;
				s_AttachItem = 0;
				m_menuWindowInfo->state = 2;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else if ((press & 0x200) != 0) {
				m_letterMenuState->action = -1;
				m_letterMenuState->step = m_letterMenuState->step + 1;
				m_menuWindowInfo->state = 2;
				Sound.PlaySe(3, 0x40, 0x7F, 0);
			}
		}
	} else if (menuMode == 5) {
		if ((hold & 0xC) != 0) {
			m_letterMenuState->choiceCursor ^= 1;
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}
		if ((hold & 0xC) == 0) {
			if ((press & 0x100) != 0) {
				if (m_letterMenuState->choiceCursor == 0) {
					int gilValue = 0;
					int itemValue = 0;
					if (s_Attach == 0) {
						itemValue = s_AttachItem;
					} else if (s_Attach == 1) {
						gilValue = s_AttachItem;
					}
					caravanWork->FGLetterReply(
					    static_cast<int>(s_SelLetter),
					    static_cast<int>(s_ReplyPos),
					    itemValue,
					    gilValue);
					if (s_Attach == 0) {
						caravanWork->DeleteItemIdx(static_cast<int>(s_AttachItemIdx), 0);
					} else {
						caravanWork->AddGil(-gilValue);
					}
					m_letterMenuState->action = 1;
				} else {
					m_letterMenuState->action = -1;
				}

				m_letterMenuState->step = m_letterMenuState->step + 1;
				m_menuWindowInfo->state = 2;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			} else if ((press & 0x200) != 0) {
				m_letterMenuState->action = -1;
				m_letterMenuState->step = m_letterMenuState->step + 1;
				m_menuWindowInfo->state = 2;
				Sound.PlaySe(3, 0x40, 0x7F, 0);
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80164EE0
 * PAL Size: 1652b
 * EN Address: 0x80163F50
 * EN Size: 1652b
 * JP Address: 0x8015FAA8
 * JP Size: 1640b
 */
void CMenuPcs::LetterMessDraw()
{
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	CCaravanWork* const caravanWork = GetLetterCaravanWork();
	s16 mode = m_letterMenuState->previousMode;
	float x1, x0;
	float y0, y1;
	float u, v;
	GXColor colors[4];

	SingleFadeEntry* panel = m_singleFadeState->entries;
	for (int i = 0; i < m_singleFadeState->count; ++i, ++panel) {
		int tex = panel->tex;
		if (tex < 0) {
			continue;
		}

		x0 = static_cast<float>(panel->x);
		y0 = static_cast<float>(panel->y);
		x1 = static_cast<float>(panel->width);
		y1 = static_cast<float>(panel->height);
		u = panel->u;
		v = panel->v;
		colors[0].r = 0xFF;
		colors[0].g = 0xFF;
		colors[0].b = 0xFF;
		colors[0].a = static_cast<u8>(FLOAT_803330a0 * panel->alpha);
		GXSetChanMatColor(GX_COLOR0A0, colors[0]);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(panel->tex));
		MenuPcs.DrawRect(
		    0, x0, y0, x1,
		    y1, u, v,
		    panel->uvScale, panel->uvScale, 0.0f);
	}

	SingleFadeState* animState = m_singleFadeState;
	CFont* font = m_fonts[0];
	font->SetShadow(0);
	font->SetMargin(FLOAT_8033313c);
	font->SetScale(FLOAT_80333140);
	font->DrawInit();
	font->SetTlut(0x1C);

	font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_803330a0 * animState->entries[0].alpha)).color);

	CMemory::CStage* stage = GetLetterMenuStage(this);
	char* srcText = new (stage, const_cast<char*>(s_menu_letter_cpp), 0x535) char[kLetterTextScratchSize];
	char* workText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x537) char[kLetterTextScratchSize];

	memset(srcText, 0, kLetterTextScratchSize);
	memset(workText, 0, kLetterTextScratchSize);

	CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
	u16 msgIndex = letter->HeaderWord();
	strcpy(srcText, Game.GetLetter((msgIndex & 0x7FC) >> 2));
#ifdef VERSION_GCCJGC
	CMes::MakeAgbString(workText, srcText);
#else
	CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);
#endif
	int y = 0x58;

	int i = 0;
	char* curLine = workText;
	for (; i < 7; ++i) {
		char* newline = strchr(curLine, '\n');
		y0 = static_cast<float>(y);
		if (newline != 0) {
			*newline = '\0';
		}

		if (strlen(curLine) != 0) {
			font->SetPosX(FLOAT_80333144);
			font->SetPosY(y0 - FLOAT_80333148);
			font->Draw(curLine);
		}

		if (newline == 0) {
			break;
		}

		curLine = newline + 1;
		y += 0x20;
	}

	delete[] srcText;
	delete[] workText;

	DrawInit();

	if (caravanWork->m_letters[s_SelLetter].m_bits.m_attachValue != 0) {
		x0 = FLOAT_8033314c;
		y0 = FLOAT_80333150;
		int iconX = static_cast<int>(x0);
		int iconY = static_cast<int>(y0);
		int icon = 0x26 +
		           (caravanWork->m_letters[s_SelLetter].m_bits.m_attachmentClaimed ? 1 : 0);
		DrawSingleIcon(
		    icon, iconX, iconY,
		    animState->entries[0].alpha, 1, FLOAT_80333154);
	}

	if (mode <= 1) {
		return;
	}

	DrawSingWin(-1);
	if ((m_letterMenuState->step == 1) &&
	    (m_menuWindowInfo->state == 1)) {
		int msgType = static_cast<int>(m_letterMenuState->messageMask);
		if (mode == 4) {
			DrawSingWinMess(2, msgType, 0);
		} else {
			DrawSingWinMess(0, msgType, 1);
		}

		if ((mode == 2) || (mode == 5)) {
			x0 = static_cast<float>(m_menuWindowInfo->x + 0x14);
			int itemSel = m_letterMenuState->choiceCursor;
			if (mode == 2) {
				itemSel += 1;
			} else {
				itemSel += s_Attach == 2 ? 3 : 4;
			}
			itemSel *= SingWinMessHeight();
			y0 = static_cast<float>(m_menuWindowInfo->y + (itemSel + 0x20));
		} else if ((mode == 3) || (mode == 4)) {
			x0 = static_cast<float>(m_menuWindowInfo->x - 8);
			if (mode == 4) {
				x0 += FLOAT_80333110;
			}
			int itemSel = m_letterMenuState->choiceCursor;
			itemSel *= SingWinMessHeight();
			y0 = static_cast<float>(m_menuWindowInfo->y + (itemSel + 0x20));
		}

		int frameAnim = static_cast<int>(System.m_frameCounter) % 8;
		x0 += static_cast<float>(frameAnim);
		DrawCursor(static_cast<int>(x0), static_cast<int>(y0), FLOAT_803330f8);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80165554
 * PAL Size: 1528b
 * EN Address: 0x801645C4
 * EN Size: 1528b
 * JP Address: 0x80160110
 * JP Size: 1528b
 */
void CMenuPcs::LetterListDraw()
{
	SingleFadeEntry* panels = m_singleFadeState->entries;

	if ((static_cast<char>(s_OpenClose) != 0) && (static_cast<char>(m_singleMenuCtrlResetFlag) == '\0')) {
		DrawSingleCrescent(FLOAT_803330f8,
			static_cast<float>(DOUBLE_803330e8 - static_cast<double>(panels[0].alpha)));
		DrawSingleStat(
			static_cast<float>(DOUBLE_803330e8 - static_cast<double>(panels[0].alpha)));
		DrawSingleHelpWim(
			static_cast<float>(DOUBLE_803330e8 - static_cast<double>(panels[0].alpha)));
	}

	if (m_singleFadeState->count == 1) {
		return;
	}

	LetterLstBaseDraw(panels[1].alpha);

	CFont* font = m_fonts[0];
	font->SetMargin(FLOAT_803330f8);
	font->SetShadow(1);
	font->SetScale(FLOAT_803330f8);
	font->DrawInit();

	font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(FLOAT_803330a0 * panels[1].alpha)).color);

	char* menuTitle = GetMenuStr(0x1D);
	float titleX = static_cast<float>((FLOAT_80333158 - font->GetWidth(menuTitle)) / 2.0);
	DrawShadowFont(font, menuTitle, titleX, FLOAT_8033315c, 0x18, 0x12);

	if (static_cast<double>(panels[1].alpha) < DOUBLE_803330e8) {
		return;
	}

	font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);

	CCaravanWork* caravanWork = GetLetterCaravanWork();

	unsigned int y = 0x60;
	const int topRow = static_cast<int>(m_letterMenuState->topIndex);
	int letterIndex;
	float yf;
	for (int row = 0; row < 9 && (letterIndex = topRow + row) < caravanWork->m_letterCount; ++row) {
		CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[letterIndex];
		yf = static_cast<float>(y);

		int tlut;
		if (!letter->IsOpened()) {
			tlut = 9;
		} else if (letter->IsReplySent()) {
			tlut = 8;
		} else {
			tlut = 0;
		}

		font->SetTlut(tlut);

		const char* subject = Game.GetLetterSubject((letter->HeaderWord() & 0x7FC) >> 2);
		font->SetPosX(FLOAT_80333160);
		font->SetPosY(yf - FLOAT_80333148);
		font->Draw(subject);

		const char* npcName = Game.m_cFlatDataArr[1].TableStrings(2)[(letter->Word0() >> 9) & 0x1FF];
		font->SetPosX(FLOAT_80333164);
		font->SetPosY(static_cast<float>(y) - FLOAT_80333148);
		font->Draw(npcName);

		y += 0x20;
	}

	DrawInit();

	s16 topVal = m_letterMenuState->topIndex;
	int pageMark = 0;
	if (topVal != 0) {
		pageMark |= 1;
	}
	if (topVal + 9 < caravanWork->m_letterCount) {
		pageMark = pageMark | 2;
	}

	if (pageMark != 0) {
		const int frame = static_cast<int>(System.m_frameCounter);
		const int phase = (frame % 0x14) - 10;
		const int absPhase = abs(phase);
		const float markScale =
		    static_cast<float>(DOUBLE_80333098 * static_cast<double>(absPhase) + DOUBLE_80333090);

		float markY = FLOAT_8033308c;
		float markX = FLOAT_80333088;

		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

		const int alpha = static_cast<int>(
		    FLOAT_803330a0 * static_cast<float>(DOUBLE_803330b0 * static_cast<double>(absPhase) + DOUBLE_803330a8));
		GXColor markColor;
		markColor.r = 0xFF;
		markColor.g = 0xFF;
		markColor.b = 0xFF;
		markColor.a = static_cast<u8>(alpha);
		GXSetChanMatColor(GX_COLOR0A0, markColor);
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kLetterTexBase + 0x7));

		const float iconSize = FLOAT_803330b8;
		const double iconOffset = (iconSize - iconSize * markScale) / 2.0;
		markX += iconOffset;
		markY += iconOffset;

		if ((pageMark & 1) != 0) {
			MenuPcs.DrawRect(
			    4, markX, markY, FLOAT_803330b8,
			    FLOAT_803330b8, FLOAT_803330bc, FLOAT_803330bc, markScale,
			    markScale, 0.0f);
		}

		markY += FLOAT_803330c0;
		if ((pageMark & 2) != 0) {
			MenuPcs.DrawRect(
			    0, markX, markY,
			    FLOAT_803330b8, FLOAT_803330b8, FLOAT_803330bc, FLOAT_803330bc,
			    markScale, markScale, 0.0f);
		}
	}

	int iconY = 0x5B;
	float iconXf = FLOAT_80333168;
	const int iconX = static_cast<int>(iconXf);
	const int iconTopRow = static_cast<int>(m_letterMenuState->topIndex);
	int iconLetterIndex;
	for (int row = 0; row < 9 && (iconLetterIndex = iconTopRow + row) < caravanWork->m_letterCount; ++row) {
		if (caravanWork->m_letters[iconLetterIndex].AttachmentValue() != 0) {
			const int icon = 0x26 + (caravanWork->m_letters[iconLetterIndex].IsAttachmentClaimed() ? 1 : 0);
			DrawSingleIcon(icon, iconX, static_cast<int>(static_cast<float>(iconY)), FLOAT_803330f8, 1, FLOAT_803330f8);
		}
		iconY += 0x20;
	}

	const int cursorX = static_cast<int>(FLOAT_803330f4 + static_cast<float>(static_cast<int>(System.m_frameCounter) % 8));
	const int cursorY = static_cast<int>(static_cast<float>(m_letterMenuState->listCursor * 0x20 + 0x60));
	DrawCursor(cursorX, cursorY, FLOAT_803330f8);
}

/*
 * --INFO--
 * PAL Address: 0x80165B4C
 * PAL Size: 56b
 * EN Address: 0x80164BBC
 * EN Size: 56b
 * JP Address: 0x80160708
 * JP Size: 56b
 */
void CMenuPcs::LetterDraw()
{
	if (m_letterMenuState->mode == 0) {
		LetterListDraw();
	} else {
		LetterMessDraw();
	}
}

/*
 * --INFO--
 * PAL Address: 0x80165B84
 * PAL Size: 1552b
 * EN Address: 0x80164BF4
 * EN Size: 1420b
 * JP Address: 0x80160740
 * JP Size: 720b
 */
int CMenuPcs::LetterConfirmOpen()
{
	CCaravanWork* caravanWork = GetLetterCaravanWork();
#ifndef VERSION_GCCJGC
	int languageId = Game.m_gameWork.m_languageId;
#endif

	if (m_letterMenuState->dialogInitialized == '\0') {
		char lines[8][0x80];
		memset(lines, 0, sizeof(lines));
#ifdef VERSION_GCCJGC
		int lineCount = 0;
		strcpy(lines[lineCount], Game.GetNPCName(caravanWork->m_letters[s_SelLetter].SenderId()));
		strcat(lines[lineCount], GetMenuStr(0x26));
		lineCount++;

		strcpy(lines[lineCount], GetMenuStr(0x23));
		strcat(lines[lineCount], s_ReplyStr);
		strcat(lines[lineCount], GetMenuStr(0x24));
		strcat(lines[lineCount], GetMenuStr(0x27));
		lineCount++;

		if (s_Attach == 0) {
			strcpy(lines[lineCount], Game.GetShortItemName(s_AttachItem));
		} else if (s_Attach == 1) {
			sprintf(lines[lineCount], s_fmt_pctd, s_AttachItem);
			strcat(lines[lineCount], GetMenuStr(4));
		}
		if (s_Attach != 2) {
			strcat(lines[lineCount], GetMenuStr(0x28));
			lineCount++;
		}
#else
		int lineCount = 0;
		switch (languageId) {
		case 2: {
			const char* title = Game.GetNPCName(caravanWork->m_letters[s_SelLetter].SenderId());
			sprintf(lines[lineCount], s_fmt_pcts_pcts, title, GetMenuStr(0x26));
			break;
		}
#ifdef VERSION_GCCE01
		case 3:
#endif
		case 4: {
			const char* title = Game.GetNPCName(caravanWork->m_letters[s_SelLetter].SenderId());
			sprintf(lines[lineCount], s_fmt_pcts_pcts_pcts, GetMenuStr(0x26), title, GetMenuStr(0x25));
			break;
		}
#ifndef VERSION_GCCE01
		case 3: {
			const char* title = Game.GetNPCName(caravanWork->m_letters[s_SelLetter].SenderId());
			sprintf(lines[lineCount], s_fmt_pcts_pcts, GetMenuStr(0x26), title);
			break;
		}
#endif
		case 5: {
			const char* title = Game.GetNPCName(caravanWork->m_letters[s_SelLetter].SenderId());
			sprintf(lines[lineCount], s_fmt_pcts_sp_pcts_dot, GetMenuStr(0x26), title);
			break;
		}
		case 1:
		default: {
			const char* title = Game.GetNPCName(caravanWork->m_letters[s_SelLetter].SenderId());
			sprintf(lines[lineCount], s_fmt_pcts_sp_pcts_pcts, GetMenuStr(0x25), title, GetMenuStr(0x26));
			break;
		}
		}
		lineCount++;

		switch (languageId) {
		case 2:
			sprintf(lines[lineCount], s_letterItemInfoFmt,
			        GetMenuStr(0x23),
			        s_ReplyStr,
			        GetMenuStr(0x24),
			        GetMenuStr(0x27));
			break;
		case 3:
			sprintf(lines[lineCount], s_pctspctspctspcts,
			        GetMenuStr(0x25),
			        GetMenuStr(0x23),
			        s_ReplyStr,
			        GetMenuStr(0x24));
			break;
		case 1:
		case 4:
		default:
			sprintf(lines[lineCount], s_fmt_pcts_pcts_pcts, GetMenuStr(0x23), s_ReplyStr, GetMenuStr(0x24));
			break;
		}
		lineCount++;

		if (s_Attach != 2) {
			switch (languageId) {
			case 2:
				if (s_Attach == 0) {
#ifdef VERSION_GCCE01
					sprintf(lines[lineCount], s_fmt_pcts_sp, Game.GetShortItemName(s_AttachItem));
#else
					const char* attachName = Game.GetShortItemName(s_AttachItem);
					sprintf(lines[lineCount], s_fmt_pcts_pcts_pcts, GetMenuStr(0x23),
					        attachName,
					        GetMenuStr(0x24));
#endif
				} else if (s_Attach == 1) {
					sprintf(lines[lineCount], s_fmt_pctd_sp_pcts, s_AttachItem, GetMenuStr(4));
				}
				strcat(lines[lineCount], GetMenuStr(0x28));
				break;
			case 1:
			case 3:
			default:
				strcpy(lines[lineCount], GetMenuStr(0x28));
				if (s_Attach == 0) {
					strcat(lines[lineCount], Game.GetShortItemName(s_AttachItem));
				} else if (s_Attach == 1) {
					int offs = strlen(lines[lineCount]);
					sprintf(lines[lineCount] + offs, s_fmt_pctd_sp_pcts, s_AttachItem, GetMenuStr(4));
				}
				break;
			}
			lineCount++;
		}
#endif

		strcat(lines[lineCount], GetMenuStr(0x21));
		strcpy(lines[lineCount + 1], s_fmt_two_spaces);
		strcat(lines[lineCount + 1], GetMenuStr(1));
		strcpy(lines[lineCount + 2], s_fmt_two_spaces);
		strcat(lines[lineCount + 2], GetMenuStr(2));

		SetSingDynamicWinMessInfo(lineCount + 3, lines[0], lines[1], lines[2], lines[3], lines[4], lines[5], lines[6], lines[7]);

		s16 winW;
		s16 winH;
		GetSingWinSize(0, &winW, &winH, 1);
		SetMcWinInfo(winW, winH);
		m_menuWindowInfo->state = 0;
		m_letterMenuState->choiceCursor = 0;
		m_letterMenuState->messageMask = -1;
		m_letterMenuState->dialogInitialized = 1;
	}

	int opened = 0;
	if (m_menuWindowInfo->state == 1) {
		opened = 1;
	}
	return opened;
}

/*
 * --INFO--
 * PAL Address: 0x80166194
 * PAL Size: 764b
 * EN Address: 0x80165180
 * EN Size: 764b
 * JP Address: 0x80160A10
 * JP Size: 680b
 */
int CMenuPcs::LetterReplyWinOpen()
{
	CCaravanWork* caravanWork = GetLetterCaravanWork();
	char* srcText;
	char* workText;
#ifndef VERSION_GCCJGC
	int languageId = Game.m_gameWork.m_languageId;
#endif
	if (m_letterMenuState->dialogInitialized == '\0') {
		char lines[8][0x80];
		memset(lines, 0, sizeof(lines));

#ifdef VERSION_GCCJGC
		srcText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x30B) char[kLetterTextScratchSize];
		workText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x30D) char[kLetterTextScratchSize];
#else
		srcText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x323) char[kLetterTextScratchSize];
		workText = new (GetLetterMenuStage(this), const_cast<char*>(s_menu_letter_cpp), 0x325) char[kLetterTextScratchSize];
#endif

		memset(srcText, 0, kLetterTextScratchSize);
		memset(workText, 0, kLetterTextScratchSize);

		CCaravanWork::CLetterWork* letter = &caravanWork->m_letters[s_SelLetter];
		unsigned short msgIndex = letter->HeaderWord();
		strcpy(srcText, Game.GetLetterReply((msgIndex & 0x7FC) >> 2));
#ifdef VERSION_GCCJGC
		CMes::MakeAgbString(workText, srcText);
#else
		CMes::MakeAgbString(workText, srcText, caravanWork->m_genderFlag, 0);
#endif

		s_ReplyMax = 0;
		char* curLine = workText;
		int i = 0;
		do {
			char* newline = strchr(curLine, '\n');
			if (newline != 0) {
				*newline = '\0';
			}

#ifdef VERSION_GCCJGC
			strcpy(lines[i], GetMenuStr(0x23));
			strcat(lines[i], curLine);
			strcat(lines[i], GetMenuStr(0x24));
			strcat(lines[i], GetMenuStr(0x25));
#else
			if (languageId == 2) {
				sprintf(lines[i], "%s%s%s", GetMenuStr(0x23), curLine, GetMenuStr(0x24));
			} else {
				sprintf(lines[i], "%s%s%s", GetMenuStr(0x23), curLine, GetMenuStr(0x24));
			}
#endif

			s_ReplyMax = static_cast<unsigned char>(s_ReplyMax + 1);
			if (newline == 0) {
				break;
			}
			++i;
			curLine = newline + 1;
		} while (i < 7);

		delete[] srcText;
		delete[] workText;

		const char* closeText = GetMenuStr(3);
		int lineIndex = static_cast<signed char>(s_ReplyMax++);
		strcat(lines[lineIndex], closeText);

		SetSingDynamicWinMessInfo(s_ReplyMax,
			lines[0],
			lines[1],
			lines[2],
			lines[3],
			lines[4],
			lines[5],
			lines[6],
			lines[7]);

		s16 winW;
		s16 winH;
		GetSingWinSize(0, &winW, &winH, 1);
		SetMcWinInfo(winW, winH);
		m_menuWindowInfo->state = 0;
		m_letterMenuState->messageMask = -1;
		m_letterMenuState->dialogInitialized = 1;
	}
	int opened = 0;
	if (m_menuWindowInfo->state == 1) {
		opened = 1;
	}
	return opened;
}

/*
 * --INFO--
 * PAL Address: 0x80166490
 * PAL Size: 488b
 * EN Address: 0x8016547C
 * EN Size: 488b
 * JP Address: 0x80160CB8
 * JP Size: 512b
 */
int CMenuPcs::LetterClose()
{
	s_OpenClose = 1;
	int allFinished = LetterLstClose();
	if (allFinished && SingGetLetterAttachflg() >= 0) {
		LetterMenuState* state2 = m_letterMenuState;
		s_BackUpCur[0] = state2->listCursor;
		s_BackUpCur[1] = state2->choiceCursor;
		s_BackUpTopPos = s_SelLetter - s_BackUpCur[0];
	}

	return allFinished;
}

/*
 * --INFO--
 * PAL Address: 0x80166678
 * PAL Size: 4556b
 * EN Address: 0x80165664
 * EN Size: 4556b
 * JP Address: 0x80160EB8
 * JP Size: 4564b
 */
int CMenuPcs::LetterCtrl()
{
	int done;
	int ret = 0;
	m_letterMenuState->previousMode = m_letterMenuState->mode;
	done = s_OpenClose = 0;

	LetterMenuState* state = m_letterMenuState;
	s16 phase = state->step;
	if (phase == 0) {
		s16 mode = state->mode;
		if (mode == 0) {
			int listOpenFinished = LetterLstOpen();
			if (listOpenFinished) {
				m_letterMenuState->topIndex = s_SelLetter - m_letterMenuState->listCursor;
				m_letterMenuState->step = 1;
			}
		} else if (mode == 1) {
			int messOpenFinished = LetterMessOpen();
			if (messOpenFinished) {
				if (SingGetLetterAttachflg() >= 0) {
					if (s_AttachMode > 0) {
						m_letterMenuState->mode = 5;
					} else {
						s_Attach = 2;
						m_letterMenuState->mode = 3;
						m_letterMenuState->choiceCursor = static_cast<s16>(s_ReplyPos);
					}
					m_letterMenuState->step = 0;
					m_letterMenuState->dialogInitialized = 0;
					SingSetLetterAttachflg(-1);
				} else {
					m_letterMenuState->step = 1;
				}
			}
		} else if (mode == 2) {
			done = LetterItemWinOpen();
			if (done != 0) {
				m_letterMenuState->step = 1;
			}
		} else if (mode == 3) {
			if (LetterReplyWinOpen()) {
				m_letterMenuState->step = 1;
			}
		} else if (mode == 4) {
			done = LetterAttachWinOpen();
			if (done != 0) {
				m_letterMenuState->step = 1;
			}
		} else if (mode == 5) {
			if (LetterConfirmOpen()) {
				m_letterMenuState->step = 1;
			}
		}
	} else if (phase == 1) {
		ret = LetterCtrlCur();
	} else if (phase == 2) {
		s16 mode = state->mode;
		if (mode == 0) {
			int uniteFinished = LetterLstClose();
			if (uniteFinished) {
				LetterInit1();
				m_letterMenuState->mode = 1;
				m_letterMenuState->step = 0;
			}
		} else if (mode == 1) {
			signed char action = state->action;
			if (action > 0) {
				if (action == 1) {
					state->mode = 2;
				} else if (action == 2) {
					state->choiceCursor = static_cast<u16>(done);
					m_letterMenuState->mode = 3;
				}
				m_letterMenuState->step = 0;
				m_letterMenuState->action = 0;
				m_letterMenuState->dialogInitialized = 0;
			} else {
				int replyFinished = LetterMessClose();
				if (replyFinished) {
					if (s_Attach != 2) {
						ret = 1;
					} else {
						LetterInit();
					}
					m_letterMenuState->step = 0;
					m_letterMenuState->mode = 0;
				}
			}
			m_letterMenuState->action = 0;
		} else if (mode == 2) {
			done = LetterItemWinClose();
			if (done != 0) {
				LetterMenuState* st = m_letterMenuState;
				if (st->action > 0) {
					st->mode = 3;
				} else {
					st->mode = 1;
				}
				m_letterMenuState->action = 0;
				m_letterMenuState->step = 0;
				m_letterMenuState->dialogInitialized = 0;
				m_letterMenuState->choiceCursor = 0;
			}
		} else if (mode == 3) {
			done = LetterReplyWinClose();
			if (done != 0) {
				LetterMenuState* st = m_letterMenuState;
				if (st->action < 1) {
					st->mode = 1;
					m_letterMenuState->step = 1;
				} else {
					st->mode = 4;
					m_letterMenuState->step = 0;
				}
				m_letterMenuState->dialogInitialized = 0;
			}
		} else if (mode == 4) {
			done = LetterAttachWinClose();
			if (done != 0) {
				LetterMenuState* st = m_letterMenuState;
				if (st->action < 1) {
					st->mode = 3;
					m_letterMenuState->step = 0;
					m_letterMenuState->dialogInitialized = 0;
					m_letterMenuState->choiceCursor = static_cast<s16>(s_ReplyPos);
				} else {
					if (s_Attach != 2) {
						if (s_Attach == 0) {
							SingSetLetterAttachflg(1);
						} else {
							SingSetLetterAttachflg(5);
						}
						m_letterMenuState->mode = 1;
						m_letterMenuState->step = 2;
						m_letterMenuState->action = -1;
						LetterInit0();
					} else {
						st->mode = 5;
						m_letterMenuState->step = 0;
					}
					m_letterMenuState->dialogInitialized = 0;
				}
			}
		} else if (mode == 5) {
			done = LetterConfirmClose();
			if (done != 0) {
				LetterMenuState* st = m_letterMenuState;
				if (st->action < 1) {
					st->mode = 3;
					m_letterMenuState->step = 0;
					m_letterMenuState->dialogInitialized = 0;
					m_letterMenuState->choiceCursor = static_cast<s16>(s_ReplyPos);
				} else {
					s_Attach = 2;
					m_letterMenuState->mode = 1;
					m_letterMenuState->step = 2;
					m_letterMenuState->action = -1;
					LetterInit0();
					m_letterMenuState->dialogInitialized = 0;
				}
			}
		}
	}

	if (ret != 0) {
		if (s_Attach != 2) {
			LetterInit4();
		} else {
			LetterInit2();
		}
	}
	return ret;
}

/*
 * --INFO--
 * PAL Address: 0x80167844
 * PAL Size: 1016b
 * EN Address: 0x80166830
 * EN Size: 1016b
 * JP Address: 0x8016208C
 * JP Size: 1084b
 */
int CMenuPcs::LetterOpen()
{
	int attachMode;

	s_OpenClose = 1;
	if (m_letterMenuState->initialized == '\0') {
		LetterInit();
		attachMode = SingGetLetterAttachflg();
		if (attachMode >= 0) {
			LetterInit3();
			m_letterMenuState->listCursor = static_cast<s16>(s_BackUpCur[0]);
			m_letterMenuState->choiceCursor = static_cast<s16>(s_BackUpCur[1]);
			m_letterMenuState->topIndex = static_cast<s16>(s_BackUpTopPos);
			s_SelLetter = static_cast<s16>(s_BackUpCur[0] + s_BackUpTopPos);
		} else {
			m_letterMenuState->listCursor = 0;
			m_letterMenuState->choiceCursor = 0;
			m_letterMenuState->topIndex = 0;
			s_AttachItem = 0;
			s_AttachMode = 0;
			s_Attach = 2;
			s_SelLetter = 0;
		}
		s_BackUpCur[0] = 0;
		s_BackUpCur[1] = 0;
		s_BackUpTopPos = 0;
		SetSingWinScl(FLOAT_803330f8);
	}
	int allFinished = LetterLstOpen();
	if (allFinished) {
		attachMode = SingGetLetterAttachflg();
		if (attachMode >= 0) {
			m_letterMenuState->step = 0;
			m_letterMenuState->mode = 1;
			LetterInit1();
		} else {
			m_letterMenuState->step = 1;
		}
	}
	return allFinished;
}

/*
 * --INFO--
 * PAL Address: 0x80167C3C
 * PAL Size: 408b
 * EN Address: 0x80166C28
 * EN Size: 408b
 * JP Address: 0x801624C8
 * JP Size: 456b
 */
void CMenuPcs::LetterInit1()
{
	float uvOrigin;

	memset(m_singleFadeState, 0, sizeof(*m_singleFadeState));
	SingleFadeEntry* entry = m_singleFadeState->entries;
	for (int i = 0; i < 64; ++i, ++entry) {
		entry->uvScale = FLOAT_803330f8;
	}

	SingleFadeEntry* p;
	int n = 0;
	p = &m_singleFadeState->entries[n++];
	p->tex = kLetterTexBase + 0x23;
	p->width = 0x238;
	p->height = 0x178;
	double scale = DOUBLE_803330a8;
	p->x = static_cast<s16>((0x280 - p->width) * scale);
	p->y = static_cast<s16>((0x1C0 - p->height) * scale);
	uvOrigin = FLOAT_803330bc;
	p->u = uvOrigin;
	p->v = uvOrigin;
	p->startFrame = 0;
	p->duration = 10;

	p = &m_singleFadeState->entries[n++];
	p->tex = kLetterTexBase + 0x2;
	p->width = 0xA8;
	p->height = 0x60;
	p->x = 0x20;
	p->y = static_cast<s16>(0x1A0 - p->height);
	p->u = uvOrigin;
	p->v = uvOrigin;
	p->startFrame = 0;
	p->duration = 10;

	m_singleFadeState->count = static_cast<s16>(n);
	m_letterMenuState->frame = 0;
	m_letterMenuState->initialized = 1;
}
