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
static const double kCompaOneDouble = 1.0;
static const float kCompaColorMax = 255.0f;
static const float kCompaFoodIconWidth = 328.0f;
static const float kCompaFoodIconHeight = 40.0f;
static const float kCompaNameFontScaleX = 0.8f;
static const float kCompaTextYOffset = 4.0f;
static const float kCompaJobFontScale = 1.2f;
static const float kCompaJobYOffset = 2.0f;
static const double kCompaIntToDoubleBias = 4503601774854144.0;
extern "C" const float kCompaFoodIconUvScale;
extern "C" const float kCompaFrameU;

static const char sCompaFamilyCountErrorFmt[] = "%s(%d):family cnt error!!(%d)\n";
static const char s_menu_compa_cpp[] = "menu_compa.cpp";

STATIC_ASSERT(sizeof(CompaOpenAnimList) == 0x1008);

static inline double LoadDouble(double value)
{
	return value;
}

static inline float LoadFloat(float value)
{
	return value;
}

static inline float LoadFloatRef(const float& value)
{
	return value;
}

/*
 * --INFO--
 * PAL Address: 0x80160edc
 * PAL Size: 3024b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaDraw()
{
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	const CCaravanWork* caravanWork = reinterpret_cast<const CCaravanWork*>(Game.m_scriptFoodBase[0]);
	CompaOpenAnim* entry = this->m_compaList->entries;
	for (int i = 0; i < this->m_compaList->count; i++) {
		int tex = entry->tex;
		if (tex >= 0) {
			float x = static_cast<float>(entry->x);
			float y = static_cast<float>(entry->y);
			float w = static_cast<float>(entry->w);
			float h = static_cast<float>(entry->h);
			float u = entry->u;
			float v = entry->v;

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

				float fillW = entry->alpha * w;
				if (fillW > kCompaZero) {
					if (entry->tex == 0x51) {
						int yStep = static_cast<int>(y);
						float end = y + h;
						while (static_cast<float>(yStep) < end) {
							int tileH = static_cast<unsigned int>(end - static_cast<float>(yStep));
							if (static_cast<float>(tileH) > kCompaTileHeight) {
								tileH = 0x18;
							}
							MenuPcs.DrawRect(
								static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
								fillW, static_cast<float>(tileH), u, v,
								colors, kCompaOne, kCompaOne, kCompaZero);
							yStep += 0x18;
						}
					} else {
						MenuPcs.DrawRect(
							static_cast<unsigned long>(entry->drawFlags), x, y, fillW, h, u, v,
							colors, kCompaOne, kCompaOne, kCompaZero);
					}

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
					float remainW = static_cast<float>((LoadDouble(kCompaOneDouble) / (double)entry->duration) * (double)static_cast<float>(entry->w));
					if (entry->tex == 0x51) {
						int yStep = static_cast<int>(y);
						float end = y + h;
						while (static_cast<float>(yStep) < end) {
							float diff = end - static_cast<float>(yStep);
							int tileH = (diff >= kCompaTileHeight) ? 0x18 : static_cast<unsigned int>(diff);
							MenuPcs.DrawRect(
								static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
								remainW, static_cast<float>(tileH), u, v,
								colors, kCompaOne, kCompaOne, kCompaZero);
							yStep += 0x18;
						}
					} else {
						MenuPcs.DrawRect(
							static_cast<unsigned long>(entry->drawFlags), x, y, remainW, h, u, v,
							colors, kCompaOne, kCompaOne, kCompaZero);
					}
				}

				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			} else {
				float alpha = entry->alpha;
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
				GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = static_cast<unsigned char>(alpha * kCompaColorMax);
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.DrawRect(0, x, y, w, h, u, v, entry->uvScale, entry->uvScale, kCompaZero);
			}
		}

		entry++;
	}

	CompaOpenAnimList* compaList = this->m_compaList;
	float globalAlpha = compaList->entries[0].alpha;

	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<signed char>(globalAlpha * kCompaColorMax);
	GXSetChanMatColor(GX_COLOR0A0, color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3A));

	int familyCount = 2;
	for (int i = 2; i < 7; i++) {
		if (caravanWork->m_evtWordArr[19 + i] > 0) {
			familyCount++;
		}
	}
	if (familyCount > 4 && System.m_execParam >= 1) {
		System.Printf(const_cast<char*>(sCompaFamilyCountErrorFmt), s_menu_compa_cpp, 0x1BF,
		              familyCount);
	}
	if (familyCount > 4) {
		familyCount = 4;
	}

	for (unsigned int i = 0; i < familyCount; i++) {
		MenuPcs.DrawRect(
			0,
			static_cast<float>(compaList->entries[0].x + 0x10),
			static_cast<float>(compaList->entries[0].y + 0x40 + i * 0x28),
			kCompaFoodIconWidth, kCompaFoodIconHeight, kCompaZero, kCompaZero, kCompaOne,
			kCompaOne, kCompaZero);
	}

	int memberIndex = 0;
	unsigned int shown = 0;
	for (int i = 0; i < 8 && shown < familyCount; i++) {
		int drawIndex = memberIndex;
		if (memberIndex > 1) {
			for (; drawIndex < 7; drawIndex++) {
				if (caravanWork->m_evtWordArr[19 + drawIndex] != 0) {
					break;
				}
			}
			if (drawIndex > 7) {
				break;
			}
		}

		const u8* foodPtr = &Game.m_gameWork.m_linkTable[caravanWork->m_saveSlot][0][caravanWork->m_saveSlot][drawIndex + 1];
		if (*foodPtr == 0 && System.m_execParam >= 1) {
			System.Printf(const_cast<char*>(sCompaFamilyCountErrorFmt), s_menu_compa_cpp, 0x1E0,
			              shown);
		}
		u8 food = *foodPtr;
		int icon = 0x1D;
		if (food <= 0x14) {
			icon = 0x21;
		} else if (food <= 0x28) {
			icon = 0x20;
		} else if (food <= 0x3C) {
			icon = 0x1F;
		} else if (food <= 0x50) {
			icon = 0x1E;
		}

		DrawSingleIcon(
			icon,
			static_cast<int>(compaList->entries[0].x + 0x128),
			static_cast<int>(compaList->entries[0].y + 0x40 + shown * 0x28),
			globalAlpha, 1, kCompaOne);

		shown++;
		memberIndex = drawIndex + 1;
	}

	CFont* font = m_fonts[4];
	font->SetMargin(kCompaOne);
	font->SetShadow(0);
	font->SetScaleX(kCompaNameFontScaleX);
	font->SetScaleY(kCompaOne);
	font->DrawInit();

	GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<signed char>(kCompaColorMax * globalAlpha)).color;
	font->SetColor(textColor);

	memberIndex = 0;
	shown = 0;
	for (int i = 0; i < 8 && shown < familyCount; i++) {
		int drawIndex = memberIndex;
		if (memberIndex > 1) {
			for (; drawIndex < 7; drawIndex++) {
				if (caravanWork->m_evtWordArr[19 + drawIndex] > 0) {
					break;
				}
			}
			if (drawIndex > 7) {
				break;
			}
		}

		const char* name = GetMenuStr(drawIndex + 0x16);
		float y = static_cast<float>(compaList->entries[0].y + 0x45 + shown * 0x28) - kCompaTextYOffset;
		font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x18));
		font->SetPosY(y);
		font->Draw(name);

		short food = caravanWork->m_evtWordArr[19 + drawIndex];
		const char* value = Game.m_cFlatDataArr[1].TableStrings(2)[food];
		font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x90));
		font->SetPosY(y);
		font->Draw(value);

		shown++;
		memberIndex = drawIndex + 1;
	}

	font = m_fonts[4];
	font->SetMargin(kCompaOne);
	font->SetShadow(0);
	font->SetScale(kCompaJobFontScale);
	font->DrawInit();
	font->SetColor(textColor);

	const char* job = GetJobStr(caravanWork->unk_0x3ac);
	font->GetWidth(job);
	font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x18));
	font->SetPosY(static_cast<float>(compaList->entries[0].y + 0x20) - kCompaTextYOffset - kCompaJobYOffset);
	font->Draw(job);

	DrawInit();
}
/*
 * --INFO--
 * PAL Address: 80161aac
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::CompaClose()
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
                entry->alpha = LoadFloat(kCompaZero);
                entry->dx = LoadFloat(kCompaZero);
                entry->dy = LoadFloat(kCompaZero);
            } else {
                entry->frame = entry->frame + 1;
                entry->alpha =
                    (float)(LoadDouble(kCompaOneDouble) - (LoadDouble(kCompaOneDouble) / (double)entry->duration) * (double)entry->frame);
                if ((entry->flags & 2) == 0) {
                    float step =
                        (float)(LoadDouble(kCompaOneDouble) - (LoadDouble(kCompaOneDouble) / (double)entry->duration) * (double)entry->frame);
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
 * PAL Address: 80161c28
 * PAL Size: 800b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaCtrl()
{
	bool activeInput = false;
	int padState = Pad.m_debugPadLock;
	unsigned int rawPress;
	unsigned int rawHold;
	short press;
	short hold;
	int doReset;

	if (padState == 0) {
		if (Pad.m_debugPadPort != -1) {
			goto activePress;
		}
	} else {
activePress:
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

	activeInput = false;
	if (padState == 0) {
		if (Pad.m_debugPadPort != -1) {
			goto activeHold;
		}
	} else {
activeHold:
		activeInput = true;
	}

	if (activeInput) {
		rawHold = 0;
	} else {
		unsigned int port = 0;
		int mask = -((__cntlzw((unsigned int)Pad.m_debugPadPort) >> 5) & 1);
		port &= ~mask;
		rawHold = Pad.GetPadInputs()[port].repeatButton;
	}
	hold = rawHold & 0xffff;

	if (hold == 0) {
		doReset = 0;
	} else if ((press & 0x20) != 0) {
		this->m_compaMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x40) != 0) {
		this->m_compaMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else {
		if ((press & 0x100) != 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
			goto noReset;
		} else if ((press & 0x200) != 0) {
			this->m_compaMenuState->closeRequested = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			doReset = 1;
		} else {
noReset:
			doReset = 0;
		}
	}

	if (doReset != 0) {
		CompaOpenAnimList* compaList = this->m_compaList;
		int entryIndex = 0;
		CompaOpenAnim* setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 2;
		setupEntry->duration = 5;
		compaList = this->m_compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 2;
		setupEntry->duration = 5;
		compaList = this->m_compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 2;
		setupEntry->duration = 5;
		compaList = this->m_compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;
		compaList = this->m_compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;
		compaList = this->m_compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->flags = 2;
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;

		CompaOpenAnim* entry = this->m_compaList->entries;
		for (int entryCount = this->m_compaList->count; entryCount > 0; entryCount--) {
			entry->frame = 0;
			entry->alpha = LoadFloat(kCompaOne);
			entry++;
		}
	}
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CompaInit0()
{
	CompaOpenAnimList* compaList = this->m_compaList;
	int entryIndex = 0;
	CompaOpenAnim* setupEntry = &compaList->entries[entryIndex++];
	setupEntry->startFrame = 2;
	setupEntry->duration = 5;
	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->startFrame = 2;
	setupEntry->duration = 5;
	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->startFrame = 2;
	setupEntry->duration = 5;
	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->startFrame = 7;
	setupEntry->duration = 5;
	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->startFrame = 7;
	setupEntry->duration = 5;
	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->flags = 2;
	setupEntry->startFrame = 7;
	setupEntry->duration = 5;

	unsigned int entryCount = compaList->count;
	CompaOpenAnim* entry = compaList->entries;
	while (entryCount != 0) {
		entry->frame = 0;
		entry->alpha = LoadFloat(kCompaOne);
		entry++;
		entryCount--;
	}
}

/*
 * --INFO--
 * PAL Address: 80161f48
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::CompaOpen()
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
                entry->alpha = LoadFloat(kCompaOne);
                entry->dx = LoadFloat(kCompaZero);
                entry->dy = LoadFloat(kCompaZero);
            } else {
                entry->frame = entry->frame + 1;
                entry->alpha = (float)((LoadDouble(kCompaOneDouble) / (double)entry->duration) * (double)entry->frame);
                if ((entry->flags & 2) == 0) {
                    float step = (float)((LoadDouble(kCompaOneDouble) / (double)entry->duration) * (double)entry->frame);
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
 * PAL Address: 801620f8
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CompaInit()
{
	memset(this->m_compaList, 0, sizeof(*this->m_compaList));

	CompaOpenAnim* entry = this->m_compaList->entries;
	float one = LoadFloatRef(kCompaOne);
	int count = 8;
	do {
		entry[0].uvScale = one;
		entry[1].uvScale = one;
		entry[2].uvScale = one;
		entry[3].uvScale = one;
		entry[4].uvScale = one;
		entry[5].uvScale = one;
		entry[6].uvScale = one;
		entry[7].uvScale = one;
		entry += 8;
	} while (--count != 0);

	CompaOpenAnimList* compaList = this->m_compaList;
	int entryIndex = 0;
	CompaOpenAnim* setupEntry = &compaList->entries[entryIndex++];
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

	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
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

	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
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

	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
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

	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
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

	compaList = this->m_compaList;
	setupEntry = &compaList->entries[entryIndex++];
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

	this->m_compaList->count = 6;
	this->m_compaMenuState->selectedIndex = 0;
	this->m_compaMenuState->initialized = 1;
}
