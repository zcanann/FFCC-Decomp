#include "ffcc/menu_favo.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/sound.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

typedef signed short s16;

unsigned char s_rank[0x20];

extern "C" const float FLOAT_80333040 = 0.0f;
extern "C" const float FLOAT_80333044 = 32.0f;
extern "C" const float FLOAT_80333048 = 1.0f;
extern "C" const double DOUBLE_80333050 = 1.0;
extern "C" const float FLOAT_80333058 = 255.0f;
extern "C" const float FLOAT_8033305C = 24.0f;
extern "C" const double DOUBLE_80333060 = 0.5;
extern "C" const char s_FavoRankFormat_80333068[] = "%d";
extern "C" const float FLOAT_8033306C = 4.0f;
extern "C" const float FLOAT_80333070 = 0.9f;

struct FavoFlatTableEntry
{
	int count;
	const char** strings;
	char* stringBuf;
};

struct FavoFlatData
{
	char pad0[0x6C];
	FavoFlatTableEntry table[8];
};

STATIC_ASSERT(sizeof(FavoEntry) == 0x40);
STATIC_ASSERT(sizeof(FavoListStorage) == 0x1008);

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

	FavoEntry* entry = favoList->entries;
	int count = favoList->count;
	for (int i = 0; i < count; i++) {
		int tex = entry->tex;
		if (tex >= 0) {
			float x = static_cast<float>(entry->x);
			float y = static_cast<float>(entry->y);
			float w = static_cast<float>(entry->w);
			float h = static_cast<float>(entry->h);
			float u = entry->u;
			float v = entry->v;
			float alpha = entry->alpha;
			float uvScale = entry->uvScale;

			if (i < 3) {
				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

				GXColor colors[4];
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

				float fillW = alpha * w;
				if (fillW > FLOAT_80333040) {
					if (tex == 0x32) {
						float yStep = y;
						float end = y + h;
						while (yStep < end) {
							float tileH = end - yStep;
							if (tileH > FLOAT_80333044) {
								tileH = FLOAT_80333044;
							}
							MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, yStep, fillW, tileH, u,
							                 v, colors, uvScale, FLOAT_80333048, FLOAT_80333040);
							yStep += FLOAT_80333044;
						}
					} else {
						MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, y, fillW, h, u, v, colors,
						                 uvScale, FLOAT_80333048, FLOAT_80333040);
					}

					u += fillW;
					x += fillW * uvScale;
				}

				if (fillW > FLOAT_80333040 && fillW < w) {
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0;
					float remainW = (static_cast<float>(DOUBLE_80333050) / static_cast<float>(entry->duration)) * w;
					if (tex == 0x32) {
						float yStep = y;
						float end = y + h;
						while (yStep < end) {
							float tileH = end - yStep;
							if (tileH > FLOAT_80333044) {
								tileH = FLOAT_80333044;
							}
							MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, yStep, remainW, tileH,
							                 u, v, colors, uvScale, FLOAT_80333048, FLOAT_80333040);
							yStep += FLOAT_80333044;
						}
					} else {
						MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, y, remainW, h, u, v,
						                 colors, uvScale, FLOAT_80333048, FLOAT_80333040);
					}
				}

				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			} else {
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
				GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = static_cast<unsigned char>(alpha * FLOAT_80333058);
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, FLOAT_80333040);
			}
		}

		entry++;
	}

	FavoEntry* rankEntry = favoList->entries;
	int remaining = count;
	while (0 < remaining) {
		if (rankEntry->tex == 0x37) {
			break;
		}
		rankEntry++;
		remaining--;
	}

	unsigned char* rank = s_rank;
	FavoEntry* drawEntry = rankEntry;
	for (int i = 0; i < 8; i++) {
		int barX = drawEntry->x + drawEntry->w + 0x18;
		int barY = static_cast<int>((static_cast<float>(drawEntry->h) - FLOAT_8033305C) * static_cast<float>(DOUBLE_80333060) +
		                            static_cast<float>(drawEntry->y));
		DrawSingBar(barX, barY, *reinterpret_cast<short*>(rank + 2), drawEntry->alpha);
		rank += 4;
		drawEntry++;
	}

	rank = s_rank;
	drawEntry = rankEntry;
	for (int i = 0; i < 8; i++) {
		int iconX = drawEntry->x + drawEntry->w - 0x10;
		int iconY = static_cast<int>((static_cast<float>(drawEntry->h) - FLOAT_80333044) * static_cast<float>(DOUBLE_80333060) +
		                             static_cast<float>(drawEntry->y));
		DrawSingleIcon(static_cast<char>(rank[1]) + 0x14, iconX, iconY, drawEntry->alpha, 1, FLOAT_80333048);
		rank += 4;
		drawEntry++;
	}

	CFont* rankFont = font22;
	rankFont->SetShadow(1);
	rankFont->SetScale(FLOAT_80333048);
	rankFont->DrawInit();

	char textBuf[0x10];
	memset(textBuf, 0, sizeof(textBuf));
	rank = s_rank;
	drawEntry = rankEntry;
	for (int i = 0; i < 8; i++) {
		rankFont->SetTlut(6);
		rankFont->SetColor(
		    CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(FLOAT_80333058 * drawEntry->alpha)).color);
		rankFont->SetMargin(FLOAT_80333048);
		sprintf(textBuf, s_FavoRankFormat_80333068, static_cast<int>(*rank));
		rankFont->SetPosX(static_cast<float>(drawEntry->x - 0xC));
		rankFont->SetPosY(static_cast<float>(drawEntry->y) - FLOAT_8033306C);
		rankFont->Draw(textBuf);
		rankFont->SetShadow(0);
		rank += 4;
		drawEntry++;
	}

	CFont* nameFont = font16;
	nameFont->SetShadow(0);
	nameFont->SetScale(FLOAT_80333070);
	nameFont->SetMargin(FLOAT_80333048);
	nameFont->DrawInit();
	memset(textBuf, 0, sizeof(textBuf));

	const FavoFlatData* flatData = reinterpret_cast<const FavoFlatData*>(&Game.m_cFlatDataArr[1]);
	rank = s_rank;
	drawEntry = rankEntry;
	for (int i = 0; i < 8; i++) {
		nameFont->SetColor(
		    CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(FLOAT_80333058 * drawEntry->alpha)).color);
		const char* name = flatData->table[0].strings[(static_cast<char>(rank[1]) + 0x17D) * 5 + 4];
		nameFont->SetPosX(static_cast<float>(drawEntry->x + 0x1C));
		nameFont->SetPosY(static_cast<float>(drawEntry->y) - FLOAT_8033306C);
		nameFont->Draw(const_cast<char*>(name));
		rank += 4;
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
	this->singMenuState->frame = this->singMenuState->frame + 1;
	count = this->favoList->count;
	entry = this->favoList->entries;
	frame = this->singMenuState->frame;
	for (int i = 0; i < count; i++) {
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				finishedCount = finishedCount + 1;
				entry->alpha = FLOAT_80333040;
				entry->dx = FLOAT_80333040;
				entry->dy = FLOAT_80333040;
			} else {
				entry->step = entry->step + 1;
				entry->alpha =
				    (float)(DOUBLE_80333050 - (DOUBLE_80333050 / (double)entry->duration) * (double)entry->step);
				if ((entry->flags & 2) == 0) {
					float step =
					    (float)(DOUBLE_80333050 - (DOUBLE_80333050 / (double)entry->duration) * (double)entry->step);
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

	if (Pad._452_4_ == 0) {
		if (Pad._448_4_ != -1) {
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
		int mask = -((__cntlzw((unsigned int)Pad._448_4_) >> 5) & 1);
		port &= ~mask;
		rawPress = *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(&Pad) + port * 0x54 + 8);
	}
	press = rawPress & 0xffff;

	if (press == 0) {
		doReset = 0;
	} else if ((press & 0x20) != 0) {
		singMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x40) != 0) {
		singMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else {
		if ((press & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
			goto noReset;
		} else if ((press & 0x200) != 0) {
			singMenuState->closeRequested = 1;
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

	if (this->singMenuState->initialized == '\0') {
		FavoInit();
	}

	finishedCount = 0;
	this->singMenuState->frame = this->singMenuState->frame + 1;
	count = this->favoList->count;
	entry = this->favoList->entries;
	frame = this->singMenuState->frame;
	for (int i = 0; i < count; i++) {
		if (frame >= entry->startFrame) {
			if (entry->startFrame + entry->duration <= frame) {
				finishedCount = finishedCount + 1;
				entry->alpha = FLOAT_80333048;
				entry->dx = FLOAT_80333040;
				entry->dy = FLOAT_80333040;
			} else {
				entry->step = entry->step + 1;
				entry->alpha = (float)((DOUBLE_80333050 / (double)entry->duration) * (double)entry->step);
				if ((entry->flags & 2) == 0) {
					float step = (float)((DOUBLE_80333050 / (double)entry->duration) * (double)entry->step);
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
	unsigned int count;
	unsigned int blockCount;
	FavoEntry* entry;
	int list;

	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x2C) = 2;
	*reinterpret_cast<int*>(list + 0x30) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x6C) = 2;
	*reinterpret_cast<int*>(list + 0x70) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0xAC) = 2;
	*reinterpret_cast<int*>(list + 0xB0) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0xEC) = 7;
	*reinterpret_cast<int*>(list + 0xF0) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x12C) = 7;
	*reinterpret_cast<int*>(list + 0x130) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x174) = 2;
	*reinterpret_cast<int*>(list + 0x16C) = 7;
	*reinterpret_cast<int*>(list + 0x170) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x1B4) = 2;
	*reinterpret_cast<int*>(list + 0x1AC) = 0;
	*reinterpret_cast<int*>(list + 0x1B0) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x1F4) = 2;
	*reinterpret_cast<int*>(list + 0x1EC) = 0;
	*reinterpret_cast<int*>(list + 0x1F0) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x234) = 2;
	*reinterpret_cast<int*>(list + 0x22C) = 0;
	*reinterpret_cast<int*>(list + 0x230) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x274) = 2;
	alpha = FLOAT_80333048;
	*reinterpret_cast<int*>(list + 0x26C) = 0;
	*reinterpret_cast<int*>(list + 0x270) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x2B4) = 2;
	*reinterpret_cast<int*>(list + 0x2AC) = 0;
	*reinterpret_cast<int*>(list + 0x2B0) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x2F4) = 2;
	*reinterpret_cast<int*>(list + 0x2EC) = 0;
	*reinterpret_cast<int*>(list + 0x2F0) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x334) = 2;
	*reinterpret_cast<int*>(list + 0x32C) = 0;
	*reinterpret_cast<int*>(list + 0x330) = 5;
	list = reinterpret_cast<int>(favoList);
	*reinterpret_cast<int*>(list + 0x374) = 2;
	*reinterpret_cast<int*>(list + 0x36C) = 0;
	*reinterpret_cast<int*>(list + 0x370) = 5;

	count = (unsigned int)favoList->count;
	entry = favoList->entries;
	if (0 < (int)count) {
		blockCount = count >> 3;
		if (blockCount != 0) {
			do {
				entry[0].step = 0;
				entry[0].alpha = alpha;
				entry[1].step = 0;
				entry[1].alpha = alpha;
				entry[2].step = 0;
				entry[2].alpha = alpha;
				entry[3].step = 0;
				entry[3].alpha = alpha;
				entry[4].step = 0;
				entry[4].alpha = alpha;
				entry[5].step = 0;
				entry[5].alpha = alpha;
				entry[6].step = 0;
				entry[6].alpha = alpha;
				entry[7].step = 0;
				entry[7].alpha = alpha;
				entry += 8;
				blockCount = blockCount - 1;
			} while (blockCount != 0);
			count = count & 7;
			if (count == 0) {
				return;
			}
		}
		do {
			entry->step = 0;
			entry->alpha = alpha;
			entry++;
			count = count - 1;
		} while (count != 0);
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
	unsigned char uVar1;
	unsigned char uVar2;
	unsigned int uVar3;
	float fVar4;
	float fVar5;
	float fVar7;
	int iVar8;
	short sVar9;
	short sVar10;
	short sVar11;
	unsigned char* puVar12;
	unsigned char* puVar13;
	int iVar16;
	int iVar17;

	uVar3 = Game.m_scriptFoodBase[0];
	memset(favoList, 0, sizeof(*favoList));
	FavoEntry* entry = favoList->entries;
	iVar16 = 8;
	do {
		entry[0].uvScale = FLOAT_80333048;
		entry[1].uvScale = FLOAT_80333048;
		entry[2].uvScale = FLOAT_80333048;
		entry[3].uvScale = FLOAT_80333048;
		entry[4].uvScale = FLOAT_80333048;
		entry[5].uvScale = FLOAT_80333048;
		entry[6].uvScale = FLOAT_80333048;
		entry[7].uvScale = FLOAT_80333048;
		entry += 8;
		iVar16 = iVar16 - 1;
	} while (iVar16 != 0);

	FavoEntry* setupEntry = &favoList->entries[0];
	setupEntry->tex = 0x33;
	setupEntry->drawFlags = 4;
	setupEntry->x = 0x30;
	setupEntry->y = 0x28;
	setupEntry->w = 0x158;
	setupEntry->h = 0x20;
	fVar4 = FLOAT_80333040;
	fVar5 = 384.0f;
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->uvScale = fVar5 / (float)setupEntry->w;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	setupEntry = &favoList->entries[1];
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

	setupEntry = &favoList->entries[2];
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
	fVar7 = 0.75f;
	sVar11 = 6;
	setupEntry = &favoList->entries[3];
	setupEntry->tex = 0x45;
	setupEntry->x = 0x18;
	setupEntry->y = 0xe;
	setupEntry->w = 0x30;
	setupEntry->h = 0x30;
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->uvScale = FLOAT_80333048;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	setupEntry = &favoList->entries[4];
	setupEntry->tex = 0x45;
	setupEntry->x = 0x1d;
	setupEntry->w = 0x30;
	setupEntry->h = 0x30;
	setupEntry->y = static_cast<short>(0x150 - setupEntry->h);
	setupEntry->u = fVar4;
	setupEntry->v = fVar4;
	setupEntry->uvScale = fVar7;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	setupEntry = &favoList->entries[5];
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

	FavoEntry* firstEntry = favoList->entries;
	setupEntry = &favoList->entries[6];
	iVar17 = 4;
	do {
		setupEntry->flags = 2;
		setupEntry->tex = 0x37;
		sVar11 = sVar11 + 2;
		setupEntry->x = firstEntry->x + 0x28;
		sVar10 = sVar9 + 0x20;
		setupEntry->y = firstEntry->y + sVar9;
		setupEntry->w = 200;
		setupEntry->h = 0x28;
		setupEntry->u = fVar4;
		setupEntry->v = fVar4;
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;
		setupEntry++;

		setupEntry->flags = 2;
		setupEntry->tex = 0x37;
		setupEntry->x = firstEntry->x + 0x28;
		sVar9 = sVar9 + 0x40;
		setupEntry->y = firstEntry->y + sVar10;
		setupEntry->w = 200;
		setupEntry->h = 0x28;
		setupEntry->u = fVar4;
		setupEntry->v = fVar4;
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;
		setupEntry++;
		iVar17 = iVar17 - 1;
	} while (iVar17 != 0);

	favoList->count = sVar11;

	memset(s_rank, 0, sizeof(s_rank));
	iVar8 = 0;
	puVar13 = s_rank;
	s_rank[1] = 0;
	*(short*)&s_rank[2] = *(short*)(uVar3 + 0x3b8);
	s_rank[5] = 1;
	*(short*)&s_rank[6] = *(short*)(uVar3 + 0x3ba);
	s_rank[9] = 2;
	*(short*)&s_rank[10] = *(short*)(uVar3 + 0x3bc);
	s_rank[0xd] = 3;
	*(short*)&s_rank[14] = *(short*)(uVar3 + 0x3be);
	s_rank[0x11] = 4;
	*(short*)&s_rank[18] = *(short*)(uVar3 + 0x3c0);
	s_rank[0x15] = 5;
	*(short*)&s_rank[22] = *(short*)(uVar3 + 0x3c2);
	s_rank[0x19] = 6;
	*(short*)&s_rank[26] = *(short*)(uVar3 + 0x3c4);
	s_rank[0x1d] = 7;
	*(short*)&s_rank[30] = *(short*)(uVar3 + 0x3c6);

	do {
		iVar17 = iVar8 + 1;
		iVar16 = 8 - iVar17;
		puVar12 = s_rank + iVar17 * 4;
		if (iVar17 < 8) {
			do {
				sVar9 = *(short*)(puVar13 + 2);
				if (sVar9 < *(short*)(puVar12 + 2)) {
					uVar1 = *puVar13;
					uVar2 = puVar13[1];
					*puVar13 = *puVar12;
					puVar13[1] = puVar12[1];
					*(short*)(puVar13 + 2) = *(short*)(puVar12 + 2);
					*puVar12 = uVar1;
					puVar12[1] = uVar2;
					*(short*)(puVar12 + 2) = sVar9;
				}
				puVar12 = puVar12 + 4;
				iVar16 = iVar16 - 1;
			} while (iVar16 != 0);
		}
		iVar8 = iVar8 + 1;
		puVar13 = puVar13 + 4;
	} while (iVar8 < 8);

	iVar8 = 0;
	iVar17 = 0;
	iVar16 = 8;
	puVar13 = s_rank;
	do {
		if ((iVar17 != 0) && (*(short*)(puVar13 - 2) != *(short*)(puVar13 + 2))) {
			iVar8 = iVar17;
		}
		iVar17 = iVar17 + 1;
		*puVar13 = (char)iVar8 + 1;
		puVar13 = puVar13 + 4;
		iVar16 = iVar16 - 1;
	} while (iVar16 != 0);

	singMenuState->selectedIndex = 0;
	singMenuState->initialized = 1;
}
