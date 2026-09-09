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
static const float kArtiHalf = 0.5f;
static const float kArtiInitX = 128.0f;
static const float kArtiInitYOffset = 8.0f;
static const float kArtiInitScale = 0.75f;

extern "C" {
extern const char s_MenuOptionMusic[];
extern const char s_MenuOptionOn[];
extern const char s_MenuOptionOff[];
extern const char s_MenuOptionStereo[];
extern const char s_MenuOptionMin[];
extern const char s_MenuOptionMax[];
extern const char s_MenuOptionStrengthDe[];
extern const char s_MenuOptionDefenceDe[];
extern const char s_MenuOptionMusicDe[];
extern const char s_MenuOptionOnDe[];
extern const char s_MenuOptionOffDe[];
extern const char s_MenuOptionStereoDe[];
}

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
 * EN Address: 0x80183198
 * EN Size: 800b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ArtiCtrlCur()
{
	int selectedRow;
	int selection;
	short press = Pad.GetButtonDown(0);
	short hold = Pad.GetButtonRepeat(0);

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
			int scrollOffset = m_artiState->scrollOffset;
			if (scrollOffset + selectedRow < 0x48) {
				m_artiState->scrollOffset = scrollOffset + 1;
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
 * EN Address: 0x80182684
 * EN Size: 2836b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiDraw()
{
	int hasSelectedArtifact = 0;
	int selectedArtifactId;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	short artiState = m_artiState->state;
	ArtiOpenAnim* entry = m_artiList->entries;
	const CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
	int drawIndex = 0;
	float x;
	float y;
	float w;
	float h;
	float u;
	float v;
	GXColor colors[4];

	for (int i = 0; i < m_artiList->count; i++) {
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
				if (tex == 0x37) {
					int itemCount = caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + (drawIndex + m_artiState->scrollOffset)];
					if (itemCount > 0) {
					} else {
						texId = 0x34;
						double half = kArtiHalfDouble;
						itemAlpha = (float)(half * (double)animAlpha);
					}

					if (texId == 0x37 && drawIndex == m_artiState->selections[0]) {
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
		entry++;
	}

	CFont* listFont = m_fonts[4];
	listFont->SetMargin(kArtiOne);
	listFont->SetShadow(0);
	listFont->SetScale(kArtiListFontScale);
	listFont->DrawInit();

	ArtiOpenAnimList* list = m_artiList;
	for (int li = 0; li < list->count; li++) {
		entry = &list->entries[li];
		if (entry->tex == 0x37) {
			break;
		}
	}

	ArtiOpenAnim* textEntry = entry;
	for (int i = 0; i < 8; i++) {
		float colorMax = kArtiColorMax;
		u8 alpha = (u8)(colorMax * textEntry->alpha);
		int menuIndex = i + m_artiState->scrollOffset;
		listFont->SetColor(CColor(0xFF, 0xFF, 0xFF, alpha).color);

		short itemCount = caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + menuIndex];
		const char* text;
		if (itemCount <= 0) {
			text = GetMenuStr(0x14);
		} else {
			text = Game.m_cFlatDataArr[1].TableStrings(0)[itemCount * 5 + 4];
			if (menuIndex == (int)m_artiState->selections[0] + (int)m_artiState->scrollOffset) {
				selectedArtifactId = itemCount;
				hasSelectedArtifact = 1;
			}
		}

		listFont->GetWidth(text);
		float posX = (float)(textEntry->x + 0x1c);
		float posY = (float)(textEntry->y + 0xb);
		listFont->SetPosX(posX);
		listFont->SetPosY(posY - kArtiTextYOffset);
		listFont->Draw(text);
		textEntry++;
	}

	DrawInit();

	ArtiOpenAnim* iconEntry = entry;
	for (int i = 0; i < 8; i++) {
		short itemCount = caravanWork->m_inventoryItems[CCaravanWork::kPermanentArtifactStart + (i + m_artiState->scrollOffset)];
		if (itemCount > 0) {
			int iconY = (int)((float)(iconEntry->y + 6) - kArtiOne);
			int iconX = (int)((float)(iconEntry->x + iconEntry->w - 0x10));
			DrawSingleIcon(itemCount, iconX, iconY, entry->alpha, 0, kArtiZero);
		}
		iconEntry++;
	}

	if (artiState == 1) {
		entry = m_artiList->entries;
		float mark = static_cast<float>(CalcListPos(m_artiState->scrollOffset, 0x49, 0));
		if (mark > kArtiZero) {
			DrawListPosMark((float)entry->x, (float)entry->y, mark);
		}
	}

	if (artiState == 1) {
		ArtiOpenAnimList* cursorList = m_artiList;
		for (int i = 0; i < cursorList->count; i++) {
			entry = &cursorList->entries[i];
			if (cursorList->entries[i].tex == 0x37) {
				break;
			}
		}

		entry += m_artiState->selections[0];
		int cursorY = (int)(float)((double)(entry->h - 0x20) * kArtiHalfDouble + (double)entry->y);
		int cursorX = (int)((float)(entry->x - 0x14) + (float)((int)System.m_frameCounter % 8));
		DrawCursor(cursorX, cursorY, kArtiOne);
	}

	CFont* helpFont = m_fonts[0];
	s8 helpAlpha = (s8)(kArtiColorMax * m_artiList->entries[0].alpha);
	if (!hasSelectedArtifact) {
		selectedArtifactId = -1;
	}

	if (selectedArtifactId == -1) {
		const char* text = GetMenuStr(0x14);
		GXColor colorVal = CColor(0xFF, 0xFF, 0xFF, helpAlpha).color;
		int x = (int)CalcCenteringPos(const_cast<char*>(text), helpFont);
		float helpY = kArtiHelpY;
		DrawFont(x, (int)helpY, colorVal, 10, const_cast<char*>(text), kArtiOne,
		         kArtiHelpScale);
	} else {
		GXColor colorVal = CColor(0xFF, 0xFF, 0xFF, helpAlpha).color;
		int x = (int)(kArtiHelpCenterX - w * kArtiHalf);
		float helpY = kArtiHelpY;
		DrawHelpMessage(selectedArtifactId, helpFont, x, (int)helpY, colorVal, 10,
		                kArtiOne, kArtiHelpScale);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160658
 * PAL Size: 380b
 * EN Address: 0x8018245C
 * EN Size: 552b
 * JP Address: TODO
 * JP Size: TODO
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
				double oneD = kArtiOneDouble;
				anim->alpha = (float)-((oneD / (double)anim->duration) * (double)anim->step - oneD);
				if ((anim->flags & 2) == 0) {
					float ratio = (float)-((oneD / (double)anim->duration) * (double)anim->step - oneD);
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
 * EN Address: 0x801823FC
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
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
 * EN Address: 0x801821C4
 * EN Size: 568b
 * JP Address: TODO
 * JP Size: TODO
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
				double one = kArtiOneDouble;
				entry->alpha = (float)((one / (double)entry->duration) * (double)entry->step);
				if ((entry->flags & 2) == 0) {
					float ratio = (float)((one / (double)entry->duration) * (double)entry->step);
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
 * EN Address: 0x80182028
 * EN Size: 412b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ArtiInit1()
{
	float alpha;
	int index;
	ArtiOpenAnim* entry;
	ArtiOpenAnimList* list;

	index = 0;
	entry = &m_artiList->entries[index++];
	entry->tex = 0x2e;
	entry->startFrame = 2;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->tex = 0x44;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->tex = 0x44;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x2e;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x37;
	alpha = kArtiOne;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_artiList->entries[index];
	entry->flags = 2;
	entry->tex = 0x37;
	entry->startFrame = 0;
	entry->duration = 5;
	list = m_artiList;
	ArtiOpenAnim* p = list->entries;
	for (index = list->count; index > 0; index--, p++) {
		p->step = 0;
		p->alpha = alpha;
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160c34
 * PAL Size: 680b
 * EN Address: 0x80181D40
 * EN Size: 744b
 * JP Address: TODO
 * JP Size: TODO
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
	entry->tex = 0x2e;
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
	entry->tex = 0x44;
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
	entry->tex = 0x44;
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
	entry->tex = 0x2e;
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
		entry->tex = 0x37;
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
