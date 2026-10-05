#include "ffcc/menu_arti.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

#ifdef VERSION_GCCJGC
enum {
    kArtiPanelTexture = 0x2D,
    kArtiIconTexture = 0x43,
    kArtiRowTexture = 0x36,
    kArtiEmptyRowTexture = 0x33
};
#else
enum {
    kArtiPanelTexture = 0x2E,
    kArtiIconTexture = 0x44,
    kArtiRowTexture = 0x37,
    kArtiEmptyRowTexture = 0x34
};
#endif

typedef unsigned char u8;

static const float kArtiZero = 0.0f;
static const float kArtiOne = 1.0f;
static const double kArtiOneDouble = 1.0;
static const double kArtiHalfDouble = 0.5;
static const float kArtiColorMax = 255.0f;
static const float kArtiListFontScale = 0.9f;
static const float kArtiTextYOffset = 4.0f;
static const float kArtiHelpY = 352.0f;
static const float kArtiHelpScale = 3.0f;
static const float kArtiHelpCenterX = 320.0f;
static const float kArtiInitX = 128.0f;
static const float kArtiInitYOffset = 8.0f;
static const float kArtiInitScale = 0.75f;

namespace {
STATIC_ASSERT(offsetof(CMenuPcs, m_artiState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_artiList) == 0x850);
STATIC_ASSERT(offsetof(ArtiState, initialized) == 0xB);
STATIC_ASSERT(offsetof(ArtiState, closeRequested) == 0xD);
STATIC_ASSERT(offsetof(ArtiState, state) == 0x10);
STATIC_ASSERT(offsetof(ArtiState, moveDirection) == 0x1E);
STATIC_ASSERT(offsetof(ArtiState, optionCloseReady) == 0x20);
STATIC_ASSERT(offsetof(ArtiState, frame) == 0x22);
STATIC_ASSERT(offsetof(ArtiState, selections) == 0x26);
STATIC_ASSERT(offsetof(ArtiState, currentSelection) == 0x30);
STATIC_ASSERT(offsetof(ArtiState, prevSelection) == 0x32);
STATIC_ASSERT(offsetof(ArtiState, scrollOffset) == 0x34);
STATIC_ASSERT(offsetof(ArtiOpenAnim, alpha) == 0x10);
STATIC_ASSERT(offsetof(ArtiOpenAnim, scale) == 0x14);
STATIC_ASSERT(offsetof(ArtiOpenAnim, unk) == 0x18);
STATIC_ASSERT(offsetof(ArtiOpenAnim, tex) == 0x1C);
STATIC_ASSERT(offsetof(ArtiOpenAnim, step) == 0x20);
STATIC_ASSERT(offsetof(ArtiOpenAnim, startFrame) == 0x24);
STATIC_ASSERT(offsetof(ArtiOpenAnim, duration) == 0x28);
STATIC_ASSERT(offsetof(ArtiOpenAnim, flags) == 0x2C);
STATIC_ASSERT(offsetof(ArtiOpenAnim, dx) == 0x30);
STATIC_ASSERT(offsetof(ArtiOpenAnim, dy) == 0x34);
STATIC_ASSERT(offsetof(ArtiOpenAnim, targetX) == 0x38);
STATIC_ASSERT(offsetof(ArtiOpenAnim, targetY) == 0x3C);
STATIC_ASSERT(sizeof(ArtiOpenAnim) == 0x40);
STATIC_ASSERT(offsetof(ArtiOpenAnimList, entries) == 8);
STATIC_ASSERT(sizeof(ArtiOpenAnimList) == 0x1008);
} // namespace

/*
 * --INFO--
 * PAL Address: 0x8015fa28
 * PAL Size: 812b
 * EN Address: 0x8015EAA4
 * EN Size: 812b
 * JP Address: 0x8015A460
 * JP Size: 812b
 */
int CMenuPcs::ArtiCtrlCur()
{
	int selectedRow;
	int selection;
	short hold;
	short press;

	press = Pad.GetButtonDown(0);
	hold = Pad.GetButtonRepeat(0);

	if (hold == 0) {
		return 0;
	}

	selection = m_artiState->currentSelection;
	if ((hold & 8) != 0) {
		selectedRow = m_artiState->selections[selection];
		if (selectedRow != 0) {
			m_artiState->selections[selection] = selectedRow - 1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else {
			int scrollOffset = m_artiState->scrollOffset;
			if (scrollOffset != 0) {
				m_artiState->scrollOffset = scrollOffset - 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			}
		}
	} else if ((hold & 4) != 0) {
		selectedRow = m_artiState->selections[selection];
		if (selectedRow < 7) {
			m_artiState->selections[selection] = selectedRow + 1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else {
			if (m_artiState->scrollOffset + selectedRow < 0x48) {
				m_artiState->scrollOffset = m_artiState->scrollOffset + 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			}
		}
	}

	if ((hold & 0xc) == 0) {
		if ((press & 0x20) != 0) {
			m_artiState->moveDirection = 1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((press & 0x40) != 0) {
			m_artiState->moveDirection = -1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((press & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else if ((press & 0x200) != 0) {
			m_artiState->closeRequested = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			return 1;
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8015fd54
 * PAL Size: 2308b
 * EN Address: 0x8015EDD0
 * EN Size: 2308b
 * JP Address: 0x8015A78C
 * JP Size: 2284b
 */
void CMenuPcs::ArtiDraw()
{
	short artiState;
	ArtiOpenAnim* entry;
	const CCaravanWork* caravanWork;
	int selectedArtifactId;
	int hasSelectedArtifact;
	CFont* listFont;
	char* text;
	int i;
	int drawIndex;
	CFont* helpFont;

	hasSelectedArtifact = 0;
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	caravanWork = Game.m_scriptFoodBase[0];
	artiState = m_artiState->state;
	entry = m_artiList->entries;
	drawIndex = 0;
	float x;
	float y;
	float w;
	float h;
	float u;
	float v;
	GXColor colors[4];

	for (i = 0; i < m_artiList->count; i++, entry++) {
		int tex = entry->tex;
		if (tex >= 0) {
			x = (float)entry->x;
			y = (float)entry->y;
			w = (float)entry->w;
			h = (float)entry->h;
			u = entry->u;
			v = entry->v;

			if (i == 0) {
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
				if (w > kArtiZero) {
					MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, kArtiOne, kArtiOne, kArtiZero);
					x += w;
					u += w;
				}

				if (w > kArtiZero && w < (float)entry->w) {
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0;
					w = (float)(kArtiOneDouble / (double)entry->duration);
					w = w * entry->w;
					MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, kArtiOne, kArtiOne, kArtiZero);
				}

				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			} else {
				float animAlpha = entry->alpha;
				int texId = tex;
				float itemAlpha = animAlpha;
				if (tex == kArtiRowTexture) {
					int itemCount = caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + (drawIndex + m_artiState->scrollOffset)];
					if (itemCount > 0) {
					} else {
						texId = kArtiEmptyRowTexture;
						double half = kArtiHalfDouble;
						itemAlpha = (float)(half * (double)animAlpha);
					}

					if (texId == kArtiRowTexture && drawIndex == m_artiState->selections[0]) {
						v += h;
					}
					drawIndex++;
				}

				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(texId));
				colors[0].r = 0xFF;
				colors[0].g = 0xFF;
				colors[0].b = 0xFF;
				float colorMax = kArtiColorMax;
				colors[0].a = (u8)(colorMax * itemAlpha);
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);
				float uvScale = entry->scale;
				MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, kArtiZero);
			}
		}
	}

	listFont = GetFontItem();
	listFont->SetMargin(kArtiOne);
	listFont->SetShadow(0);
	listFont->SetScale(kArtiListFontScale);
	listFont->DrawInit();

	for (i = 0; i < m_artiList->count; i++) {
		entry = &m_artiList->entries[i];
		if (entry->tex == kArtiRowTexture) {
			break;
		}
	}

	for (i = 0; i < 8; i++) {
		float colorMax = kArtiColorMax;
		u8 alpha = (u8)(colorMax * entry->alpha);
		int menuIndex = i + m_artiState->scrollOffset;
		listFont->SetColor(CColor(0xFF, 0xFF, 0xFF, alpha).color);

		if (caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + menuIndex] <= 0) {
			text = GetMenuStr(0x14);
		} else {
			short itemCount = caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + menuIndex];
			text = Game.GetShortItemName(itemCount);
			if (menuIndex == (int)m_artiState->selections[0] + (int)m_artiState->scrollOffset) {
				selectedArtifactId = itemCount;
				hasSelectedArtifact = 1;
			}
		}

		listFont->GetWidth(text);
		x = (float)(entry[i].x + 0x1c);
		y = (float)(entry[i].y + 0xb);
		listFont->SetPosX(x);
		listFont->SetPosY(y - kArtiTextYOffset);
		listFont->Draw(text);
	}

	DrawInit();

	for (i = 0; i < 8; i++) {
		if (caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + (i + m_artiState->scrollOffset)] > 0) {
			int iconY = (int)((float)(entry[i].y + 6) - kArtiOne);
			int iconX = (int)((float)(entry[i].x + entry[i].w - 0x10));
			DrawSingleIcon(caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + (i + m_artiState->scrollOffset)],
			               iconX, iconY, entry->alpha, 0, kArtiOne);
		}
	}

	if (artiState == 1) {
		entry = m_artiList->entries;
		float mark = static_cast<float>(CalcListPos(m_artiState->scrollOffset, 0x49, 0));
		if (mark > kArtiZero) {
			DrawListPosMark((float)entry->x, (float)entry->y, mark);
		}
	}

	if (artiState == 1) {
		for (i = 0; i < m_artiList->count; i++) {
			entry = &m_artiList->entries[i];
			if (m_artiList->entries[i].tex == kArtiRowTexture) {
				break;
			}
		}

		entry += m_artiState->selections[0];
		x = (float)(entry->x - 0x14);
		y = (float)((entry->h - 0x20) / 2.0 + entry->y);
		x += (float)((int)System.m_frameCounter % 8);
		DrawCursor((int)x, (int)y, kArtiOne);
	}

	helpFont = GetFont22();
	s8 helpAlpha = (s8)(kArtiColorMax * m_artiList->entries[0].alpha);
	if (!hasSelectedArtifact) {
		selectedArtifactId = -1;
	}

	if (selectedArtifactId == -1) {
		text = GetMenuStr(0x14);
		float helpY = kArtiHelpY;
		DrawFont((int)CalcCenteringPos(text, helpFont), (int)helpY,
		         CColor(0xFF, 0xFF, 0xFF, helpAlpha).color, 10, text, kArtiOne, kArtiHelpScale);
	} else {
		float helpY = kArtiHelpY;
		DrawHelpMessage(selectedArtifactId, helpFont, (int)(kArtiHelpCenterX - w / 2),
		                (int)helpY, CColor(0xFF, 0xFF, 0xFF, helpAlpha).color, 10, kArtiOne,
		                kArtiHelpScale);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160658
 * PAL Size: 380b
 * EN Address: 0x8015F6D4
 * EN Size: 380b
 * JP Address: 0x8015B078
 * JP Size: 396b
 */
int CMenuPcs::ArtiClose()
{
	ArtiOpenAnim* anim;
	int count;
	int frame;
	int finished;

	m_artiState->frame++;
	finished = 0;

	count = m_artiList->count;
	anim = m_artiList->entries;
	frame = m_artiState->frame;

	for (int i = 0; i < count; i++, anim++) {
		if (frame >= anim->startFrame) {
			if (anim->startFrame + anim->duration <= frame) {
				float zeroF = kArtiZero;
				finished++;
				anim->alpha = zeroF;
				anim->dx = zeroF;
				anim->dy = zeroF;
			} else {
				anim->step++;
				anim->alpha = 1.0 - (1.0 / anim->duration) * anim->step;
				if ((anim->flags & 2) == 0) {
					float ratio = 1.0 - (1.0 / anim->duration) * anim->step;
					float dx = anim->targetX - (float)anim->x;
					float dy = anim->targetY - (float)anim->y;
					anim->dx = dx * ratio;
					anim->dy = dy * ratio;
				}
			}
		}
	}

	int result = 0;
	if (count == finished) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x801607d4
 * PAL Size: 84b
 * EN Address: 0x8015F850
 * EN Size: 84b
 * JP Address: 0x8015B204
 * JP Size: 84b
 */
int CMenuPcs::ArtiCtrl()
{
	ArtiState* state = m_artiState;
	int result;

	state->prevSelection = state->currentSelection;
	result = ArtiCtrlCur();
	if (result != 0) {
		ArtiInit1();
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x80160828
 * PAL Size: 432b
 * EN Address: 0x8015F8A4
 * EN Size: 432b
 * JP Address: 0x8015B258
 * JP Size: 444b
 */
int CMenuPcs::ArtiOpen()
{
	ArtiOpenAnim* entry;
	int finished;
	int count;
	int frame;

	if (m_artiState->initialized == '\0') {
		ArtiInit();
	}

	m_artiState->frame = m_artiState->frame + 1;
	finished = 0;
	entry = m_artiList->entries;
	count = m_artiList->count;
	frame = (int)m_artiState->frame;

	for (int i = 0; i < count; i++, entry++) {
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				float zero = kArtiZero;
				finished++;
				entry->alpha = kArtiOne;
				entry->dx = zero;
				entry->dy = zero;
			} else {
				entry->step++;
				entry->alpha = (1.0 / entry->duration) * entry->step;
				if ((entry->flags & 2) == 0) {
					float ratio = (1.0 / entry->duration) * entry->step;
					float dx = entry->targetX - (float)entry->x;
					float dy = entry->targetY - (float)entry->y;
					entry->dx = dx * ratio;
					entry->dy = dy * ratio;
				}
			}
		}
	}

	int result = 0;
	if (count == finished) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x801609d8
 * PAL Size: 604b
 * EN Address: 0x8015FA54
 * EN Size: 604b
 * JP Address: 0x8015B414
 * JP Size: 636b
 */
void CMenuPcs::ArtiInit1()
{
	float alpha;
	int index;
	ArtiOpenAnim* entry;

	index = 0;
	entry = &m_artiList->entries[index++];
	entry->tex = kArtiPanelTexture;
	entry->startFrame = 2;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->tex = kArtiIconTexture;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->tex = kArtiIconTexture;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiPanelTexture;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiRowTexture;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiRowTexture;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiRowTexture;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiRowTexture;
	alpha = kArtiOne;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiRowTexture;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiRowTexture;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiRowTexture;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index];
	entry->flags = 2;
	entry->tex = kArtiRowTexture;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = m_artiList->entries;
	for (index = m_artiList->count; index > 0; index--) {
		entry->step = 0;
		entry->alpha = alpha;
		entry++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160c34
 * PAL Size: 680b
 * EN Address: 0x8015FCB0
 * EN Size: 680b
 * JP Address: 0x8015B690
 * JP Size: 748b
 */
void CMenuPcs::ArtiInit()
{
	int index;
	ArtiOpenAnim* entry;

	memset(m_artiList, 0, sizeof(*m_artiList));
	{
		float one = kArtiOne;
		ArtiOpenAnim* p = m_artiList->entries;
		for (int i = 0; i < 64; i++, p++) {
			p->scale = one;
		}
	}

	index = 0;
	entry = &m_artiList->entries[index++];
	entry->tex = kArtiPanelTexture;
	entry->x = 0x68;
	entry->y = 0x28;
	entry->w = 0x78;
	entry->h = 0x108;
	float titleAlpha = kArtiInitX;
	float titleScale = kArtiInitYOffset;
	float one = kArtiOne;
	float zero = kArtiZero;
	entry->u = titleAlpha;
	entry->v = titleScale;
	entry->scale = one;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &m_artiList->entries[index++];
	entry->tex = kArtiIconTexture;
	entry->x = 0x50;
	entry->y = 0xe;
	entry->w = 0x30;
	entry->h = 0x30;
	entry->u = zero;
	entry->v = zero;
	entry->scale = one;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &m_artiList->entries[index++];
	entry->tex = kArtiIconTexture;
	entry->x = 0x55;
	entry->w = 0x30;
	entry->h = 0x30;
	entry->y = 0x150 - entry->h;
	float rightScale = kArtiInitScale;
	entry->u = zero;
	entry->v = zero;
	entry->scale = rightScale;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = kArtiPanelTexture;
	entry->x = 0x50;
	entry->y = 8;
	entry->w = 0x48;
	entry->h = 0x140;
	entry->u = zero;
	entry->v = zero;
	entry->startFrame = 0;
	entry->duration = 5;

	ArtiOpenAnim* entry0 = m_artiList->entries;
	for (int loopCount = 0; loopCount < 8; loopCount++) {
		entry = &m_artiList->entries[index++];
		entry->flags = 2;
		entry->tex = kArtiRowTexture;
		entry->x = entry0->x + 0x24;
		entry->y = entry0->y + loopCount * 0x20;
		entry->w = 200;
		entry->h = 0x28;
		entry->u = zero;
		entry->v = zero;
		entry->startFrame = 7;
		entry->duration = 5;
	}

	m_artiList->count = index;
	m_artiState->selections[0] = 0;
	m_artiState->initialized = 1;
}
