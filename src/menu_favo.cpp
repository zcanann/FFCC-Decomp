#include "ffcc/menu_favo.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/sound.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

static FoodRank s_rank[8];

static const float kFavoWideTextureWidth = 384.0f;
static const float kFavoIconUvScale = 0.75f;

STATIC_ASSERT(sizeof(FavoEntry) == 0x40);
STATIC_ASSERT(sizeof(FavoListStorage) == 0x1008);
STATIC_ASSERT(sizeof(FoodRank) == 4);
STATIC_ASSERT(sizeof(s_rank) == 0x20);

static inline void FavoDrawWindow(FavoEntry* entry, float x, float y, float w, float h, float u, float v, GXColor* colors)
{
	if (entry->tex == 0x32) {
		int yStep = static_cast<int>(y);
		float end = y + h;
		while (static_cast<float>(yStep) < end) {
			int tileH;
			if (end - static_cast<float>(yStep) >= 32.0f) {
				tileH = 0x20;
			} else {
				tileH = static_cast<int>(end - static_cast<float>(yStep));
			}
			MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
			                 w, static_cast<float>(tileH), u, v, colors, entry->uvScale, 1.0f, 0.0f);
			yStep += 0x20;
		}
	} else {
		MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, y, w, h, u, v, colors,
		                 entry->uvScale, 1.0f, 0.0f);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80162360
 * PAL Size: 2488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::FavoDraw()
{
	FavoEntry* entry;
	CFont* font;
	int i;
	float x;
	float y;
	float w;
	float h;
	float u;
	float v;
	GXColor colors[4];
	char textBuf[0x10];

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
					FavoDrawWindow(entry, x, y, w, h, u, v, colors);

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
					FavoDrawWindow(entry, x, y, w, h, u, v, colors);
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
		if (entry->tex == 0x37) {
			break;
		}
	}

	for (i = 0; i < 8; i++) {
		int barX = static_cast<int>(static_cast<float>(entry[i].x + entry[i].w + 0x18));
		float barHalfH = static_cast<float>(entry[i].h) - 24.0f;
		float barYf = static_cast<float>(entry[i].y);
		int barY = static_cast<int>(static_cast<float>(barHalfH / 2.0 + barYf));
		DrawSingBar(barX, barY, s_rank[i].score, entry[i].alpha);
	}

	for (i = 0; i < 8; i++) {
		int iconX = static_cast<int>(static_cast<float>(entry[i].x + entry[i].w - 0x10));
		float iconHalfH = static_cast<float>(entry[i].h) - 32.0f;
		float iconYf = static_cast<float>(entry[i].y);
		int iconY = static_cast<int>(static_cast<float>(iconHalfH / 2.0 + iconYf));
		DrawSingleIcon(static_cast<char>(s_rank[i].foodId) + 0x14, iconX, iconY, entry[i].alpha, 1, 1.0f);
	}

	font = m_fonts[0];
	font->SetShadow(1);
	font->SetScale(1.0f);
	font->DrawInit();

	memset(textBuf, 0, sizeof(textBuf));
	for (i = 0; i < 8; i++) {
		font->SetTlut(6);
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * entry[i].alpha)).color);
		x = static_cast<float>(entry[i].x - 0xC);
		y = static_cast<float>(entry[i].y + 0xA);
		font->renderFlags.fixedWidth = 1;
		font->SetMargin(1.0f);
		sprintf(textBuf, "%d", static_cast<int>(s_rank[i].place));
		font->SetPosX(x);
		font->SetPosY(y - 4.0f);
		font->Draw(textBuf);
		font->SetShadow(0);
	}

	font = m_fonts[4];
	font->SetShadow(0);
	font->SetScale(0.9f);
	font->SetMargin(1.0f);
	font->DrawInit();
	memset(textBuf, 0, sizeof(textBuf));

	for (i = 0; i < 8; i++) {
		font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * entry->alpha)).color);
		const char* name = Game.m_cFlatDataArr[1].TableStrings(0)[(static_cast<char>(s_rank[i].foodId) + 0x17D) * 5 + 4];
		y = static_cast<float>(entry->y + 0xB);
		x = static_cast<float>(entry->x + 0x1C);
		font->SetPosX(x);
		font->SetPosY(y - 4.0f);
		font->Draw(const_cast<char*>(name));
		entry++;
	}

	DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x80162d18
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * EN Address: 0x8018580C
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
	entry->tex = 0x33;
	entry->drawFlags = 4;
	entry->x = 0x30;
	entry->y = 0x28;
	entry->w = 0x158;
	entry->h = 0x20;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = kFavoWideTextureWidth / entry->w;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->tex = 0x32;
	entry->x = 0x30;
	entry->y = 0x48;
	entry->w = 0x158;
	entry->h = 200;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = kFavoWideTextureWidth / entry->w;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->tex = 0x33;
	entry->x = 0x30;
	entry->y = 0x110;
	entry->w = 0x158;
	entry->h = 0x20;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = kFavoWideTextureWidth / entry->w;
	entry->startFrame = 5;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->tex = 0x45;
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
	entry->tex = 0x45;
	entry->x = 0x1d;
	entry->w = 0x30;
	entry->h = 0x30;
	entry->y = 0x150 - entry->h;
	entry->u = 0.0f;
	entry->v = 0.0f;
	entry->uvScale = kFavoIconUvScale;
	entry->startFrame = 0;
	entry->duration = 5;

	entry = &m_favoList->entries[index++];
	entry->flags = 2;
	entry->tex = 0x2e;
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
		entry->tex = 0x37;
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
				signed char place = s_rank[i].place;
				unsigned char foodId = s_rank[i].foodId;
				short score = s_rank[i].score;

				s_rank[i].place = s_rank[idx].place;
				s_rank[i].foodId = s_rank[idx].foodId;
				s_rank[i].score = s_rank[idx].score;

				s_rank[idx].place = place;
				s_rank[idx].foodId = foodId;
				s_rank[idx].score = score;
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
