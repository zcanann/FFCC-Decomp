#include "ffcc/menu_favo.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/sound.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

#ifdef VERSION_GCCJGC
enum {
    kFavoWindowTexture = 0x31,
    kFavoBorderTexture = 0x32,
    kFavoIconTexture = 0x44,
    kFavoPanelTexture = 0x2D,
    kFavoRowTexture = 0x36
};
#else
enum {
    kFavoWindowTexture = 0x32,
    kFavoBorderTexture = 0x33,
    kFavoIconTexture = 0x45,
    kFavoPanelTexture = 0x2E,
    kFavoRowTexture = 0x37
};
#endif

static FoodRank s_rank[8];

STATIC_ASSERT(sizeof(FavoEntry) == 0x40);
STATIC_ASSERT(sizeof(FavoListStorage) == 0x1008);
STATIC_ASSERT(sizeof(FoodRank) == 4);
STATIC_ASSERT(sizeof(s_rank) == 0x20);

/*
 * --INFO--
 * PAL Address: 0x80162360
 * PAL Size: 2488b
 * EN Address: 0x801613D0
 * EN Size: 2488b
 * JP Address: 0x8015CE6C
 * JP Size: 2456b
 */
void CMenuPcs::FavoDraw()
{
	CFont* font;
	int i;
	FavoEntry* entry;
	float x;
	float y;
	float w;
	float h;
	float u;
	float v;
	GXColor colors[4];
	char textBuf[0x10];
	int yStep;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	entry = m_favoList->entries;
	for (i = 0; i < m_favoList->count; i++, entry++) {
		if (entry->tex >= 0) {
			x = static_cast<float>(entry->x);
			y = static_cast<float>(entry->y);
			w = static_cast<float>(entry->w);
			h = static_cast<float>(entry->h);
			u = entry->u;
			v = entry->v;

			if (i < 3) {
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
					if (entry->tex == kFavoWindowTexture) {
						for (yStep = static_cast<int>(y); static_cast<float>(yStep) < y + h; yStep += 0x20) {
							int tileH;
							if (y + h - static_cast<float>(yStep) >= 32.0f) {
								tileH = 0x20;
							} else {
								tileH = static_cast<int>(y + h - static_cast<float>(yStep));
							}
							MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
							                 w, static_cast<float>(tileH), u, v, colors, entry->uvScale, 1.0f, 0.0f);
						}
					} else {
						MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, y, w, h, u, v, colors,
						                 entry->uvScale, 1.0f, 0.0f);
					}

					u += w;
					x += w * entry->uvScale;
				}

				if (w > 0.0f && w < static_cast<float>(entry->w)) {
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0;
					w = 1.0 / entry->duration;
					w = w * entry->w;
					if (entry->tex == kFavoWindowTexture) {
						for (yStep = static_cast<int>(y); static_cast<float>(yStep) < y + h; yStep += 0x20) {
							int tileH;
							if (y + h - static_cast<float>(yStep) >= 32.0f) {
								tileH = 0x20;
							} else {
								tileH = static_cast<int>(y + h - static_cast<float>(yStep));
							}
							MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
							                 w, static_cast<float>(tileH), u, v, colors, entry->uvScale, 1.0f, 0.0f);
						}
					} else {
						MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, y, w, h, u, v, colors,
						                 entry->uvScale, 1.0f, 0.0f);
					}
				}

				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			} else {
				float entryAlpha = entry->alpha;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(entry->tex));
				colors[0].r = 0xFF;
				colors[0].g = 0xFF;
				colors[0].b = 0xFF;
				colors[0].a = static_cast<unsigned char>(255.0f * entryAlpha);
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);
				MenuPcs.DrawRect(0, x, y, w, h, u, v, entry->uvScale, entry->uvScale, 0.0f);
			}
		}
	}

	for (i = 0; i < m_favoList->count; i++) {
		entry = &m_favoList->entries[i];
		if (entry->tex == kFavoRowTexture) {
			break;
		}
	}

	for (i = 0; i < 8; i++) {
		x = entry[i].x + entry[i].w + 0x18;
		y = entry[i].y;
		y += (entry[i].h - 24.0f) / 2.0;
		DrawSingBar(x, y, s_rank[i].score, entry[i].alpha);
	}

	for (i = 0; i < 8; i++) {
		x = entry[i].x + entry[i].w - 0x10;
		y = entry[i].y;
		y += (entry[i].h - 32.0f) / 2.0;
		DrawSingleIcon(static_cast<char>(s_rank[i].foodId) + 0x14, x, y, entry[i].alpha, 1, 1.0f);
	}

	font = GetFont22();
	font->SetShadow(1);
	font->SetScale(1.0f);
	font->DrawInit();

	memset(textBuf, 0, sizeof(textBuf));
	for (i = 0; i < 8; i++) {
		font->SetTlut(6);
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * entry[i].alpha)).color);
		x = static_cast<float>(entry[i].x - 0xC);
		y = static_cast<float>(entry[i].y + 0xA);
		font->SetFixed(1);
		font->SetMargin(1.0f);
		sprintf(textBuf, "%d", static_cast<int>(s_rank[i].place));
		font->SetPosX(x);
#ifdef VERSION_GCCJGC
		font->SetPosY(y);
#else
		font->SetPosY(y - 4.0f);
#endif
		font->Draw(textBuf);
		font->SetShadow(0);
	}

	font = GetFontItem();
	font->SetShadow(0);
	font->SetScale(0.9f);
	font->SetMargin(1.0f);
	font->DrawInit();
	memset(textBuf, 0, sizeof(textBuf));

	for (i = 0; i < 8; i++) {
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * entry[i].alpha)).color);
		char* name = Game.GetShortItemName(static_cast<char>(s_rank[i].foodId) + 0x17D);
		y = static_cast<float>(entry[i].y + 0xB);
		x = static_cast<float>(entry[i].x + 0x1C);
		font->SetPosX(x);
#ifdef VERSION_GCCJGC
		font->SetPosY(y);
#else
		font->SetPosY(y - 4.0f);
#endif
		font->Draw(name);
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x80162d18
 * PAL Size: 380b
 * EN Address: 0x80161D88
 * EN Size: 380b
 * JP Address: 0x8015D804
 * JP Size: 396b
 */
int CMenuPcs::FavoClose()
{
	FavoEntry* entry;
	int finishedCount;
	int count;
	int frame;

	finishedCount = 0;
	m_singMenuState->frame++;
	count = m_favoList->count;
	entry = m_favoList->entries;
	frame = m_singMenuState->frame;
	for (int i = 0; i < count; i++) {
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				finishedCount++;
				entry->alpha = 0.0f;
				entry->dx = 0.0f;
				entry->dy = 0.0f;
			} else {
				entry->step++;
				entry->alpha =
				    (float)(1.0 - (1.0 / (double)entry->duration) * (double)entry->step);
				if ((entry->flags & 2) == 0) {
					float step =
					    (float)(1.0 - (1.0 / (double)entry->duration) * (double)entry->step);
					float dx = entry->targetX - (float)entry->x;
					float dy = entry->targetY - (float)entry->y;
					entry->dx = dx * step;
					entry->dy = dy * step;
				}
			}
		}
		entry++;
	}

	int result = 0;
	if (count == finishedCount) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 360b
 * EN Address: 0x801866AC
 * EN Size: 328b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::FavoCtrlCur()
{
	short press = Pad.GetButtonDown(0);

	if (press == 0) {
		return 0;
	} else if ((press & 0x20) != 0) {
		m_singMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		return 1;
	} else if ((press & 0x40) != 0) {
		m_singMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		return 1;
	} else if ((press & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
	} else if ((press & 0x200) != 0) {
		m_singMenuState->closeRequested = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80162E94
 * PAL Size: 400b
 * EN Address: 0x80161F04
 * EN Size: 400b
 * JP Address: 0x8015D990
 * JP Size: 400b
 */
int CMenuPcs::FavoCtrl()
{
	int doReset = FavoCtrlCur();
	if (doReset) {
		FavoInit0();
	}
	return doReset;
}

/*
 * --INFO--
 * PAL Address: 0x80163024
 * PAL Size: 432b
 * EN Address: 0x80162094
 * EN Size: 432b
 * JP Address: 0x8015DB20
 * JP Size: 444b
 */
int CMenuPcs::FavoOpen()
{
	FavoEntry* entry;
	int finishedCount;
	int count;
	int frame;

	if (m_singMenuState->initialized == '\0') {
		FavoInit();
	}

	finishedCount = 0;
	m_singMenuState->frame++;
	count = m_favoList->count;
	entry = m_favoList->entries;
	frame = m_singMenuState->frame;
	for (int i = 0; i < count; i++) {
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				finishedCount++;
				entry->alpha = 1.0f;
				entry->dx = 0.0f;
				entry->dy = 0.0f;
			} else {
				entry->step++;
				entry->alpha = (float)((1.0 / (double)entry->duration) * (double)entry->step);
				if ((entry->flags & 2) == 0) {
					float step = (float)((1.0 / (double)entry->duration) * (double)entry->step);
					float dx = entry->targetX - (float)entry->x;
					float dy = entry->targetY - (float)entry->y;
					entry->dx = dx * step;
					entry->dy = dy * step;
				}
			}
		}
		entry++;
	}

	int result = 0;
	if (count == finishedCount) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 801631d4
 * PAL Size: 616b
 * EN Address: 0x80162244
 * EN Size: 616b
 * JP Address: 0x8015DCDC
 * JP Size: 648b
 */
void CMenuPcs::FavoInit0()
{
	float alpha;
	FavoEntry* entry;
	FavoListStorage* list;
	int entryIndex;

	list = m_favoList;
	entryIndex = 0;
	entry = &list->entries[entryIndex++];
	entry->startFrame = 2;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->startFrame = 2;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->startFrame = 2;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	alpha = 1.0f;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;

	list = m_favoList;
	entry = list->entries;
	for (entryIndex = list->count; entryIndex > 0; entryIndex--) {
		entry->step = 0;
		entry->alpha = alpha;
		entry++;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8016343c
 * PAL Size: 1296b
 * EN Address: 0x801624AC
 * EN Size: 1296b
 * JP Address: 0x8015DF64
 * JP Size: 1400b
 */
void CMenuPcs::FavoInit()
{
	int i;
	int idx;
	FavoEntry* entry;
	int index;
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];

	memset(m_favoList, 0, sizeof(*m_favoList));
	entry = m_favoList->entries;
	for (i = 0; i < 64; i++, entry++) {
		entry->uvScale = 1.0f;
	}

	index = 0;
	entry = &m_favoList->entries[index++];
	entry->tex = kFavoBorderTexture;
	entry->drawFlags = 4;
	entry->x = 0x30;
	entry->y = 0x28;
	entry->w = 0x158;
	entry->h = 0x20;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = 384.0f / entry->w;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->tex = kFavoWindowTexture;
	entry->x = 0x30;
	entry->y = 0x48;
	entry->w = 0x158;
	entry->h = 200;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = 384.0f / entry->w;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->tex = kFavoBorderTexture;
	entry->x = 0x30;
	entry->y = 0x110;
	entry->w = 0x158;
	entry->h = 0x20;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = 384.0f / entry->w;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->tex = kFavoIconTexture;
	entry->x = 0x18;
	entry->y = 0xe;
	entry->w = 0x30;
	entry->h = 0x30;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = 1.0f;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->tex = kFavoIconTexture;
	entry->x = 0x1d;
	entry->w = 0x30;
	entry->h = 0x30;
	entry->y = 0x150 - entry->h;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = 0.75f;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->flags = 2;
	entry->tex = kFavoPanelTexture;
	entry->x = 0x18;
	entry->y = 8;
	entry->w = 0x48;
	entry->h = 0x140;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->startFrame = 0;
	entry->duration = 5;

	FavoEntry* firstEntry = m_favoList->entries;
	for (idx = 0; idx < 8; idx++) {
		entry = &m_favoList->entries[index++];
		entry->flags = 2;
		entry->tex = kFavoRowTexture;
		entry->x = firstEntry->x + 0x28;
		entry->y = firstEntry->y + idx * 0x20;
		entry->w = 200;
		entry->h = 0x28;
		entry->u = 0.0f;
		entry->v = 0.0f;
		entry->startFrame = 7;
		entry->duration = 5;
	}

	m_favoList->count = index;

	memset(s_rank, 0, sizeof(s_rank));
	for (i = 0; i < 8; i++) {
		s_rank[i].foodId = i;
		s_rank[i].score = caravanWork->m_letterMeta[i];
	}

	for (i = 0; i < 8; i++) {
		for (idx = i + 1; idx < 8; idx++) {
			if (s_rank[i].score < s_rank[idx].score) {
				FoodRank tmp;
				tmp = s_rank[i];
				s_rank[i] = s_rank[idx];
				s_rank[idx] = tmp;
			}
		}
	}

	int place;
	for (i = place = 0; i < 8; i++) {
		if ((i != 0) && (s_rank[i - 1].score != s_rank[i].score)) {
			place = i;
		}
		s_rank[i].place = place + 1;
	}

	m_singMenuState->selectedIndex = 0;
	m_singMenuState->initialized = 1;
}
