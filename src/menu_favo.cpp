#include "ffcc/menu_favo.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/sound.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

#pragma readonly_strings on

typedef signed short s16;

static FoodRank s_rank[8];

extern "C" const float kCompaFoodIconUvScale = 0.75f;
extern "C" const float kCompaFrameU = 72.0f;
extern "C" const float kFavoWideTextureWidth;
extern "C" const float kFavoIconUvScale;

STATIC_ASSERT(sizeof(FavoEntry) == 0x40);
STATIC_ASSERT(sizeof(FavoListStorage) == 0x1008);
STATIC_ASSERT(sizeof(FoodRank) == 4);
STATIC_ASSERT(sizeof(s_rank) == 0x20);

static inline float LoadFloat(const float& value)
{
	return value;
}

static inline double LoadDouble(const double& value)
{
	return value;
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
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	FavoEntry* entry = m_favoList->entries;
	for (int i = 0; i < m_favoList->count; i++) {
		if (entry->tex >= 0) {
			float x = static_cast<float>(entry->x);
			float y = static_cast<float>(entry->y);
			float w = static_cast<float>(entry->w);
			float h = static_cast<float>(entry->h);
			float u = entry->u;
			float v = entry->v;

			GXColor colors[4];
			if (static_cast<int>(i) < 3) {
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

				float fillW = entry->alpha * w;
				if (fillW > 0.0f) {
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
							                 fillW, static_cast<float>(tileH), u, v, colors, entry->uvScale,
							                 1.0f, 0.0f);
							yStep += 0x20;
						}
					} else {
						MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, y, fillW, h, u, v, colors,
						                 entry->uvScale, 1.0f, 0.0f);
					}

					u += fillW;
					x += fillW * entry->uvScale;
				}

				if (fillW > 0.0f && fillW < static_cast<float>(entry->w)) {
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0;
					float remainW =
					    static_cast<float>(1.0 / static_cast<double>(entry->duration)) * static_cast<float>(entry->w);
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
							                 remainW, static_cast<float>(tileH), u, v, colors, entry->uvScale,
							                 1.0f, 0.0f);
							yStep += 0x20;
						}
					} else {
						MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, y, remainW, h, u, v,
						                 colors, entry->uvScale, 1.0f, 0.0f);
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

		entry++;
	}

	int count = m_favoList->count;
	for (int k = 0; k < count; k++) {
		entry = &m_favoList->entries[k];
		if (entry->tex == 0x37) {
			break;
		}
	}

	FoodRank* rankBase = s_rank;
	FavoEntry* drawEntry = entry;
	FoodRank* rank = rankBase;
	for (int i = 0; i < 8; i++) {
		int barX = static_cast<int>(static_cast<float>(drawEntry->x + drawEntry->w + 0x18));
		float barHalfH = static_cast<float>(drawEntry->h) - 24.0f;
		float barYf = static_cast<float>(drawEntry->y);
		int barY = static_cast<int>(static_cast<float>(barHalfH / 2.0 + barYf));
		DrawSingBar(barX, barY, rank->score, drawEntry->alpha);
		rank++;
		drawEntry++;
	}

	rank = rankBase;
	drawEntry = entry;
	for (int i = 0; i < 8; i++) {
		int iconX = static_cast<int>(static_cast<float>(drawEntry->x + drawEntry->w - 0x10));
		float iconHalfH = static_cast<float>(drawEntry->h) - 32.0f;
		float iconYf = static_cast<float>(drawEntry->y);
		int iconY = static_cast<int>(iconHalfH / 2.0 + iconYf);
		DrawSingleIcon(static_cast<char>(rank->foodId) + 0x14, iconX, iconY, drawEntry->alpha, 1, 1.0f);
		rank++;
		drawEntry++;
	}

	CFont* rankFont = m_fonts[0];
	rankFont->SetShadow(1);
	rankFont->SetScale(1.0f);
	rankFont->DrawInit();

	char textBuf[0x10];
	memset(textBuf, 0, sizeof(textBuf));
	rank = rankBase;
	drawEntry = entry;
	for (int i = 0; i < 8; i++) {
		rankFont->SetTlut(6);
		rankFont->SetColor(
		    CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * drawEntry->alpha)).color);
		float posX = static_cast<float>(drawEntry->x - 0xC);
		float posY = static_cast<float>(drawEntry->y + 0xA);
		rankFont->renderFlags = (rankFont->renderFlags & 0xEF) | 0x10;
		rankFont->SetMargin(1.0f);
		sprintf(textBuf, "%d", static_cast<int>(rank->place));
		rankFont->SetPosX(posX);
		rankFont->SetPosY(posY - 4.0f);
		rankFont->Draw(textBuf);
		rankFont->SetShadow(0);
		rank++;
		drawEntry++;
	}

	CFont* nameFont = m_fonts[4];
	nameFont->SetShadow(0);
	nameFont->SetScale(0.9f);
	nameFont->SetMargin(1.0f);
	nameFont->DrawInit();
	memset(textBuf, 0, sizeof(textBuf));

	rank = rankBase;
	drawEntry = entry;
	for (int i = 0; i < 8; i++) {
		nameFont->SetColor(
		    CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * drawEntry->alpha)).color);
		float posY = static_cast<float>(drawEntry->y + 0xB);
		float posX = static_cast<float>(drawEntry->x + 0x1C);
		const char* name = Game.m_cFlatDataArr[1].TableStrings(0)[(static_cast<char>(rank->foodId) + 0x17D) * 5 + 4];
		nameFont->SetPosX(posX);
		nameFont->SetPosY(posY - 4.0f);
		nameFont->Draw(const_cast<char*>(name));
		rank++;
		drawEntry++;
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
bool CMenuPcs::FavoClose()
{
	FavoEntry* entry;
	int finishedCount;
	int count;
	int frame;

	finishedCount = 0;
	this->m_singMenuState->frame = this->m_singMenuState->frame + 1;
	count = this->m_favoList->count;
	entry = this->m_favoList->entries;
	frame = this->m_singMenuState->frame;
	for (int i = 0; i < count; i++) {
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				finishedCount = finishedCount + 1;
				entry->alpha = 0.0f;
				entry->dx = 0.0f;
				entry->dy = 0.0f;
			} else {
				entry->step = entry->step + 1;
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

	bool result = false;
	if (count == finishedCount) {
		result = true;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x80162e94
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMenuPcs::FavoCtrl()
{
	bool activeInput = false;
	unsigned int rawPress;
	short press;
	int doReset;

	if (Pad.m_debugPadLock == 0) {
		if (Pad.m_debugPadPort != -1) {
			goto active;
		}
	} else {
active:
		activeInput = true;
	}

	if (activeInput) {
		rawPress = 0;
	} else {
		unsigned int port = 0;
		int mask = -((__cntlzw((unsigned int)Pad.m_debugPadPort) >> 5) & 1);
		port &= ~mask;
		rawPress = Pad.GetPadInputs()[port].buttonDown[0];
	}
	press = rawPress & 0xffff;

	if (press == 0) {
		doReset = 0;
	} else if ((press & 0x20) != 0) {
		m_singMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x40) != 0) {
		m_singMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else {
		if ((press & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
			goto noReset;
		} else if ((press & 0x200) != 0) {
			m_singMenuState->closeRequested = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			doReset = 1;
		} else {
noReset:
			doReset = 0;
		}
	}

	if (doReset != 0) {
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
bool CMenuPcs::FavoOpen()
{
	FavoEntry* entry;
	int finishedCount;
	int count;
	int frame;

	if (this->m_singMenuState->initialized == '\0') {
		FavoInit();
	}

	finishedCount = 0;
	this->m_singMenuState->frame = this->m_singMenuState->frame + 1;
	count = this->m_favoList->count;
	entry = this->m_favoList->entries;
	frame = this->m_singMenuState->frame;
	for (int i = 0; i < count; i++) {
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				finishedCount = finishedCount + 1;
				entry->alpha = 1.0f;
				entry->dx = 0.0f;
				entry->dy = 0.0f;
			} else {
				entry->step = entry->step + 1;
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

	bool result = false;
	if (count == finishedCount) {
		result = true;
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

	list = this->m_favoList;
	entryIndex = 0;
	entry = &list->entries[entryIndex++];
	entry->startFrame = 2;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->startFrame = 2;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->startFrame = 2;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 7;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	alpha = 1.0f;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;
	entry = &this->m_favoList->entries[entryIndex++];
	entry->flags = 2;
	entry->startFrame = 0;
	entry->duration = 5;

	list = this->m_favoList;
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
	float fVar4;
	float fVar5;
	int sVar9;
	int sVar10;
	int sVar11;
	int iVar16;
	int iVar17;

	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	memset(m_favoList, 0, sizeof(*m_favoList));
	FavoEntry* entry = m_favoList->entries;
	for (iVar16 = 64; iVar16 > 0; iVar16--) {
		entry->uvScale = 1.0f;
		entry++;
	}

	FavoListStorage* list = this->m_favoList;
	int entryIndex = 0;
	FavoEntry* setupEntry = &list->entries[entryIndex++];
	setupEntry->tex = 0x33;
	setupEntry->drawFlags = 4;
	setupEntry->x = 0x30;
	setupEntry->y = 0x28;
	setupEntry->w = 0x158;
	setupEntry->h = 0x20;
	fVar4 = 0.0f;
	fVar5 = kFavoWideTextureWidth;
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->uvScale = fVar5 / (float)setupEntry->w;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	list = this->m_favoList;
	setupEntry = &list->entries[entryIndex++];
	setupEntry->tex = 0x32;
	setupEntry->x = 0x30;
	setupEntry->y = 0x48;
	setupEntry->w = 0x158;
	setupEntry->h = 200;
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->uvScale = fVar5 / (float)setupEntry->w;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	list = this->m_favoList;
	setupEntry = &list->entries[entryIndex++];
	setupEntry->tex = 0x33;
	setupEntry->x = 0x30;
	setupEntry->y = 0x110;
	setupEntry->w = 0x158;
	setupEntry->h = 0x20;
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->uvScale = fVar5 / (float)setupEntry->w;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	sVar9 = 0;
	sVar11 = 6;
	list = this->m_favoList;
	setupEntry = &list->entries[entryIndex++];
	setupEntry->tex = 0x45;
	setupEntry->x = 0x18;
	setupEntry->y = 0xe;
	setupEntry->w = 0x30;
	setupEntry->h = 0x30;
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->uvScale = 1.0f;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	list = this->m_favoList;
	setupEntry = &list->entries[entryIndex++];
	setupEntry->tex = 0x45;
	setupEntry->x = 0x1d;
	setupEntry->w = 0x30;
	setupEntry->h = 0x30;
	setupEntry->y = static_cast<short>(0x150 - setupEntry->h);
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->uvScale = kFavoIconUvScale;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	list = this->m_favoList;
	setupEntry = &list->entries[entryIndex++];
	setupEntry->flags = 2;
	setupEntry->tex = 0x2e;
	setupEntry->x = 0x18;
	setupEntry->y = 8;
	setupEntry->w = 0x48;
	setupEntry->h = 0x140;
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	FavoEntry* firstEntry = &this->m_favoList->entries[0];
	int byteOff = 0x180;
	for (iVar17 = 8; iVar17 > 0; iVar17--) {
		setupEntry = reinterpret_cast<FavoEntry*>(reinterpret_cast<char*>(this->m_favoList->entries) + byteOff);
		byteOff = byteOff + 0x40;
		setupEntry->flags = 2;
		setupEntry->tex = 0x37;
		sVar11 = sVar11 + 1;
		setupEntry->x = firstEntry->x + 0x28;
		setupEntry->y = firstEntry->y + sVar9;
		sVar9 = sVar9 + 0x20;
		setupEntry->w = 200;
		setupEntry->h = 0x28;
		setupEntry->u = fVar4;
		setupEntry->v = fVar4;
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;
	}

	m_favoList->count = sVar11;

	memset(s_rank, 0, sizeof(s_rank));
	FoodRank* ranks = s_rank;
	for (int foodId = 0; foodId < 8; foodId++) {
		ranks[foodId].foodId = foodId;
		ranks[foodId].score = caravanWork->m_letterMeta[foodId];
	}

	int rankIndex = 0;
	FoodRank* rank = ranks;
	do {
		iVar17 = rankIndex + 1;
		FoodRank* compareRank = ranks + iVar17;
		for (iVar16 = iVar17; iVar16 < 8; iVar16++) {
			if (rank->score < compareRank->score) {
				signed char place = rank->place;
				signed char foodId = rank->foodId;
				short score = rank->score;

				rank->place = compareRank->place;
				rank->foodId = compareRank->foodId;
				rank->score = compareRank->score;

				compareRank->place = place;
				compareRank->foodId = foodId;
				compareRank->score = score;
			}
			compareRank++;
		}
		rankIndex++;
		rank++;
	} while (rankIndex < 8);

	int place = 0;
	iVar17 = 0;
	rank = ranks;
	do {
		if ((iVar17 != 0) && (rank[-1].score != rank->score)) {
			place = iVar17;
		}
		rank->place = place + 1;
		rank++;
		iVar17++;
	} while (iVar17 < 8);

	m_singMenuState->selectedIndex = 0;
	m_singMenuState->initialized = 1;
}
