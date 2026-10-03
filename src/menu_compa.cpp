#include "ffcc/menu_compa.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

typedef unsigned char u8;

static const float kCompaZero = 0.0f;
static const float kCompaTileHeight = 24.0f;
static const float kCompaOne = 1.0f;
static const float kCompaColorMax = 255.0f;
static const float kCompaFoodIconWidth = 328.0f;
static const float kCompaFoodIconHeight = 40.0f;
static const float kCompaNameFontScaleX = 0.8f;
static const float kCompaTextYOffset = 4.0f;
static const float kCompaJobFontScale = 1.2f;
static const float kCompaJobYOffset = 2.0f;
static const float kCompaFoodIconUvScale = 0.75f;
static const float kCompaFrameU = 72.0f;

static const char sCompaFamilyCountErrorFmt[] = "%s(%d):family cnt error!!(%d)\n";
static const char s_menu_compa_cpp[] = "menu_compa.cpp";

STATIC_ASSERT(sizeof(CompaOpenAnimList) == 0x1008);

static inline void CompaDrawWindow(CompaOpenAnim* entry, float x, float y, float w, float h, float u, float v, GXColor* colors)
{
	if (entry->tex == 0x51) {
		int yStep = static_cast<int>(y);
		float end = y + h;
		while (static_cast<float>(yStep) < end) {
			int tileH;
			if (end - static_cast<float>(yStep) >= kCompaTileHeight) {
				tileH = 0x18;
			} else {
				tileH = static_cast<int>(end - static_cast<float>(yStep));
			}
			MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
			                 w, static_cast<float>(tileH), u, v, colors, kCompaOne, kCompaOne, kCompaZero);
			yStep += 0x18;
		}
	} else {
		MenuPcs.DrawRect(static_cast<unsigned long>(entry->drawFlags), x, y, w, h, u, v, colors,
		                 kCompaOne, kCompaOne, kCompaZero);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80160edc
 * PAL Size: 3024b
 * EN Address: 0x80183DF4
 * EN Size: 3816b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaDraw()
{
	CCaravanWork* caravanWork;
	GXColor colors[4];
	CompaOpenAnimList* compaList;
	CFont* font;
	int familyCount;
	float fillW;
	int tex;
	float x;
	float y;
	float w;
	float h;
	float u;
	float v;
	float alpha;
	int drawIndex;
	int shown;
	int i;
	float iconX;
	float iconY;
	int scan;
	const u8* foodPtr;
	CompaOpenAnim* entry;
	int icon;
	const char* name;
	const char* value;
	const char* job;
	float jobY;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	caravanWork = Game.m_scriptFoodBase[0];
	entry = this->m_compaList->entries;
	for (i = 0; i < this->m_compaList->count; i++, entry++) {
		tex = entry->tex;
		if (tex >= 0) {
			x = static_cast<float>(entry->x);
			y = static_cast<float>(entry->y);
			w = static_cast<float>(entry->w);
			h = static_cast<float>(entry->h);
			u = entry->u;
			v = entry->v;

			if (i < 3) {
				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(entry->tex));

				for (int j = 0; j < 4; j++) {
					colors[j].r = 0xFF;
					colors[j].g = 0xFF;
					colors[j].b = 0xFF;
					colors[j].a = 0xFF;
				}
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);

				fillW = entry->alpha * w;
				if (fillW > kCompaZero) {
					CompaDrawWindow(entry, x, y, fillW, h, u, v, colors);

					u += fillW;
					x += fillW * entry->uvScale;
				}

				if (fillW > kCompaZero && fillW < static_cast<float>(entry->w)) {
					colors[1].r = 0xFF;
					colors[1].g = 0xFF;
					colors[1].b = 0xFF;
					colors[1].a = 0;
					colors[3].r = 0xFF;
					colors[3].g = 0xFF;
					colors[3].b = 0xFF;
					colors[3].a = 0;
					fillW = 1.0 / entry->duration;
					fillW = fillW * entry->w;
					CompaDrawWindow(entry, x, y, fillW, h, u, v, colors);
				}

				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			} else {
				alpha = entry->alpha;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
				colors[0].r = 0xFF;
				colors[0].g = 0xFF;
				colors[0].b = 0xFF;
				colors[0].a = static_cast<unsigned char>(alpha * kCompaColorMax);
				GXSetChanMatColor(GX_COLOR0A0, colors[0]);
				MenuPcs.DrawRect(0, x, y, w, h, u, v, entry->uvScale, entry->uvScale, kCompaZero);
			}
		}
	}

	colors[0].r = 0xFF;
	colors[0].g = 0xFF;
	colors[0].b = 0xFF;
	colors[0].a = static_cast<unsigned char>(this->m_compaList->entries[0].alpha * kCompaColorMax);
	GXSetChanMatColor(GX_COLOR0A0, colors[0]);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3A));

	compaList = this->m_compaList;
	for (i = familyCount = 2; i < 7; i++) {
		if (caravanWork->m_evtWordArr[19 + i] > 0) {
			familyCount++;
		}
	}
	if (familyCount > 4 && static_cast<unsigned int>(System.m_execParam) >= 1) {
		System.Printf(const_cast<char*>(sCompaFamilyCountErrorFmt), s_menu_compa_cpp, 0x1BF,
		              familyCount);
	}
	if (familyCount > 4) {
		familyCount = 4;
	}

	for (i = 0; i < familyCount; i++) {
		y = static_cast<float>(compaList->entries[0].y + 0x40);
		y += static_cast<float>(i * 0x28);
		MenuPcs.DrawRect(
			0,
			static_cast<float>(compaList->entries[0].x + 0x10),
			y,
			kCompaFoodIconWidth, kCompaFoodIconHeight, kCompaZero, kCompaZero, kCompaOne,
			kCompaOne, kCompaZero);
	}

	drawIndex = 0;
	shown = 0;
	for (i = shown; i < 8 && shown < familyCount; i++) {
		iconX = static_cast<float>(compaList->entries[0].x + 0x128);
		iconY = static_cast<float>(compaList->entries[0].y + 0x40);
		iconY += static_cast<float>(shown * 0x28);

		if (i >= 2) {
			scan = drawIndex;
			for (; scan < 7; scan++) {
				if (caravanWork->m_evtWordArr[19 + scan] != 0) {
					drawIndex = scan;
					break;
				}
			}
			if (scan >= 8) {
				break;
			}
		} else {
			drawIndex = i;
		}

		foodPtr = &Game.m_gameWork.m_linkTable[caravanWork->m_saveSlot][0][caravanWork->m_saveSlot][1 + drawIndex];
		if (*foodPtr == 0 && static_cast<unsigned int>(System.m_execParam) >= 1) {
			System.Printf(const_cast<char*>(sCompaFamilyCountErrorFmt), s_menu_compa_cpp, 0x1E0,
			              shown);
		}
		unsigned int food = *foodPtr;
		if (food <= 0x14) {
			icon = 0x21;
		} else if (food <= 0x28) {
			icon = 0x20;
		} else if (food <= 0x3C) {
			icon = 0x1F;
		} else if (food <= 0x50) {
			icon = 0x1E;
		} else {
			icon = 0x1D;
		}

		DrawSingleIcon(
			icon,
			static_cast<int>(iconX),
			static_cast<int>(iconY),
			compaList->entries[0].alpha, 1, kCompaOne);

		shown++;
		drawIndex++;
	}

	font = m_fonts[4];
	compaList = this->m_compaList;
	font->SetMargin(kCompaOne);
	font->SetShadow(0);
	font->SetScaleX(kCompaNameFontScaleX);
	font->SetScaleY(kCompaOne);
	font->DrawInit();

	font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(kCompaColorMax * compaList->entries[0].alpha)).color);

	caravanWork = Game.m_scriptFoodBase[0];
	drawIndex = 0;
	shown = 0;
	for (i = shown; i < 8 && shown < familyCount; i++) {
		if (i >= 2) {
			scan = drawIndex;
			for (; scan < 7; scan++) {
				if (caravanWork->m_evtWordArr[19 + scan] > 0) {
					drawIndex = scan;
					break;
				}
			}
			if (scan >= 8) {
				break;
			}
		} else {
			drawIndex = i;
		}

		name = GetMenuStr(drawIndex + 0x16);
		x = static_cast<float>(compaList->entries[0].x + 0x18);
		y = static_cast<float>(compaList->entries[0].y + 0x45);
		y += static_cast<float>(shown * 0x28);
		font->SetPosX(x);
		font->SetPosY(y - kCompaTextYOffset);
		font->Draw(name);

		short food = caravanWork->m_evtWordArr[19 + drawIndex];
		value = Game.m_cFlatDataArr[1].TableStrings(2)[food];
		font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x90));
		font->SetPosY(y - kCompaTextYOffset);
		font->Draw(value);

		shown++;
		drawIndex++;
	}

	font = m_fonts[4];
	font->SetMargin(kCompaOne);
	font->SetShadow(0);
	font->SetScale(kCompaJobFontScale);
	font->DrawInit();
	compaList = this->m_compaList;
	font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(kCompaColorMax * compaList->entries[0].alpha)).color);

	job = GetJobStr(caravanWork->m_jobType);
	font->GetWidth(job);
	jobY = static_cast<float>(compaList->entries[0].y + 0x20);
	font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x18));
	font->SetPosY(jobY - kCompaTextYOffset - kCompaJobYOffset);
	font->Draw(job);

	DrawInit();
}
/*
 * --INFO--
 * PAL Address: 80161aac
 * PAL Size: 380b
 * EN Address: 0x80183BCC
 * EN Size: 552b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CompaClose()
{
    CompaOpenAnim* entry;
    int finishedCount;
    int count;
    int frame;

    finishedCount = 0;
    this->m_compaMenuState->frame = this->m_compaMenuState->frame + 1;
    count = this->m_compaList->count;
    entry = this->m_compaList->entries;
    frame = this->m_compaMenuState->frame;
    for (int i = 0; i < count; i++) {
        if (frame >= entry->startFrame) {
            if (entry->startFrame + entry->duration <= frame) {
                finishedCount = finishedCount + 1;
                entry->alpha = kCompaZero;
                entry->dx = kCompaZero;
                entry->dy = kCompaZero;
            } else {
                entry->frame = entry->frame + 1;
                entry->alpha =
                    (float)(1.0 - (1.0 / (double)entry->duration) * (double)entry->frame);
                if ((entry->flags & 2) == 0) {
                    float step =
                        (float)(1.0 - (1.0 / (double)entry->duration) * (double)entry->frame);
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
 * PAL Size: 328b
 * EN Address: 0x801837E0
 * EN Size: 356b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CompaInit0()
{
	int entryIndex = 0;
	CompaOpenAnim* setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->startFrame = 2;
	setupEntry->duration = 5;
	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->startFrame = 2;
	setupEntry->duration = 5;
	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->startFrame = 2;
	setupEntry->duration = 5;
	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->startFrame = 7;
	setupEntry->duration = 5;
	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->startFrame = 7;
	setupEntry->duration = 5;
	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->flags = 2;
	setupEntry->startFrame = 7;
	setupEntry->duration = 5;

	int entryCount = m_compaList->count;
	CompaOpenAnim* entry = m_compaList->entries;
	while (entryCount > 0) {
		entry->frame = 0;
		entry->alpha = kCompaOne;
		entry++;
		entryCount--;
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 464b
 * EN Address: 0x80184CDC
 * EN Size: 356b
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CompaCtrlCur()
{
	short press = Pad.GetButtonDown(0);
	short hold = Pad.GetButtonRepeat(0);

	if (hold == 0) {
		return 0;
	} else if ((press & 0x20) != 0) {
		m_compaMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		return 1;
	} else if ((press & 0x40) != 0) {
		m_compaMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		return 1;
	} else if ((press & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
	} else if ((press & 0x200) != 0) {
		m_compaMenuState->closeRequested = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		return 1;
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80161C28
 * PAL Size: 800b
 * EN Address: 0x80183B7C
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CompaCtrl()
{
	int result = CompaCtrlCur();
	if (result) {
		CompaInit0();
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 80161f48
 * PAL Size: 432b
 * EN Address: 0x80183944
 * EN Size: 568b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CompaOpen()
{
    CompaOpenAnim* entry;
    int finishedCount;
    int count;
    int frame;

    if (this->m_compaMenuState->initialized == '\0') {
        CompaInit();
    }

    finishedCount = 0;
    this->m_compaMenuState->frame = this->m_compaMenuState->frame + 1;
    count = this->m_compaList->count;
    entry = this->m_compaList->entries;
    frame = this->m_compaMenuState->frame;
    for (int i = 0; i < count; i++) {
        if (frame >= entry->startFrame) {
            if (entry->startFrame + entry->duration <= frame) {
                finishedCount = finishedCount + 1;
                entry->alpha = kCompaOne;
                entry->dx = kCompaZero;
                entry->dy = kCompaZero;
            } else {
                entry->frame = entry->frame + 1;
                entry->alpha = (float)((1.0 / (double)entry->duration) * (double)entry->frame);
                if ((entry->flags & 2) == 0) {
                    float step = (float)((1.0 / (double)entry->duration) * (double)entry->frame);
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
 * PAL Address: 801620f8
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaInit()
{
	CompaOpenAnim* setupEntry;
	int entryIndex;

	memset(this->m_compaList, 0, sizeof(*this->m_compaList));

	CompaOpenAnim* entry = this->m_compaList->entries;
	float one = kCompaOne;
	for (int count = 64; count != 0; count--) {
		entry->uvScale = one;
		entry++;
	}

	entryIndex = 0;
	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->tex = 0x52;
	setupEntry->drawFlags = 4;
	setupEntry->x = 0x28;
	setupEntry->y = 0x30;
	setupEntry->w = 0x198;
	setupEntry->h = 0x18;
	setupEntry->u = kCompaZero;
	setupEntry->v = kCompaZero;
	setupEntry->uvScale = kCompaOne;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->tex = 0x51;
	setupEntry->x = 0x28;
	setupEntry->y = 0x48;
	setupEntry->w = 0x198;
	setupEntry->h = 200;
	setupEntry->u = kCompaZero;
	setupEntry->v = kCompaZero;
	setupEntry->uvScale = kCompaOne;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->tex = 0x52;
	setupEntry->x = 0x28;
	setupEntry->y = 0x110;
	setupEntry->w = 0x198;
	setupEntry->h = 0x18;
	setupEntry->u = kCompaZero;
	setupEntry->v = kCompaZero;
	setupEntry->uvScale = kCompaOne;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->tex = 0x5e;
	setupEntry->x = 0x10;
	setupEntry->y = 0xe;
	setupEntry->w = 0x30;
	setupEntry->h = 0x30;
	setupEntry->u = kCompaZero;
	setupEntry->v = kCompaZero;
	setupEntry->uvScale = kCompaOne;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->tex = 0x5e;
	setupEntry->x = 0x15;
	setupEntry->w = 0x30;
	setupEntry->h = 0x30;
	setupEntry->y = static_cast<short>(0x150 - setupEntry->h);
	setupEntry->u = kCompaZero;
	setupEntry->v = kCompaZero;
	setupEntry->uvScale = kCompaFoodIconUvScale;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	setupEntry = &m_compaList->entries[entryIndex++];
	setupEntry->flags = 2;
	setupEntry->tex = 0x2e;
	setupEntry->x = 0x10;
	setupEntry->y = 8;
	setupEntry->w = 0x30;
	setupEntry->h = 0x140;
	setupEntry->u = kCompaFrameU;
	setupEntry->v = kCompaZero;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	this->m_compaList->count = entryIndex;
	this->m_compaMenuState->selectedIndex = 0;
	this->m_compaMenuState->initialized = 1;
}
