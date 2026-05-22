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

extern "C" const float FLOAT_80332FF8;
extern "C" const float FLOAT_80332FFC;
extern "C" const float FLOAT_80333000;
extern "C" const double DOUBLE_80333008;
extern "C" const float FLOAT_80333010;
extern "C" const float FLOAT_80333014;
extern "C" const float FLOAT_80333018;
extern "C" const float FLOAT_8033301C;
extern "C" const float FLOAT_80333020;
extern "C" const float FLOAT_80333024;
extern "C" const float FLOAT_80333028;
extern "C" const float FLOAT_80333038;
extern "C" const float FLOAT_8033303C;

extern "C" const char s_pcts_pctd_family_cnt_error_pctd_801DEDC8[] = "%s(%d):family cnt error!!(%d)\n";
extern "C" const char s_menu_compa_cpp_801DEDE8[] = "menu_compa.cpp";

extern "C" const char s_MenuOptionMonoUpper_803334A8[] = "MONO";
extern "C" const char s_MenuOptionNormalIt_803334B0[] = "Normal";
extern "C" const char s_MenuOptionForza_803334B8[] = "Forza";
extern "C" const char s_MenuOptionDifesa_803334C0[] = "Difesa";
extern "C" const char s_MenuOptionSonoro_803334C8[] = "Sonoro";
extern "C" const char s_MenuOptionMusica_803334D0[] = "Musica";
extern "C" const char s_MenuOptionMonoIt_803334D8[] = "Mono";
extern "C" const char s_MenuOptionContr_803334E0[] = "Contr.";
extern "C" const char s_MenuOptionNorm_803334E8[] = "Norm.";

struct CompaFlatTableEntry
{
	int count;
	const char** strings;
	char* stringBuf;
};

struct CompaFlatData
{
	char pad0[0x6C];
	CompaFlatTableEntry table[8];
};

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

	unsigned int scriptFood = Game.m_scriptFoodBase[0];
	CompaOpenAnimList* compaList = this->compaList;
	CompaOpenAnim* entry = compaList->entries;
	int count = compaList->count;
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
				if (fillW > FLOAT_80332FF8) {
					if (tex == 0x51) {
						int yStep = static_cast<int>(y);
						float end = y + h;
						while (static_cast<float>(yStep) < end) {
							int tileH = static_cast<int>(end - static_cast<float>(yStep));
							if (static_cast<float>(tileH) > FLOAT_80332FFC) {
								tileH = 0x18;
							}
							MenuPcs.DrawRect(
								static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
								fillW, static_cast<float>(tileH), u, v,
								colors, uvScale, FLOAT_80333000, FLOAT_80332FF8);
							yStep += 0x18;
						}
					} else {
						MenuPcs.DrawRect(
							static_cast<unsigned long>(entry->drawFlags), x, y, fillW, h, u, v,
							colors, uvScale, FLOAT_80333000, FLOAT_80332FF8);
					}

					u += fillW;
					x += fillW * uvScale;
				}

				if (fillW > FLOAT_80332FF8 && fillW < w) {
					GXColor fadeColors[4];
					fadeColors[0].r = 0xFF;
					fadeColors[0].g = 0xFF;
					fadeColors[0].b = 0xFF;
					fadeColors[0].a = 0;
					fadeColors[1].r = 0xFF;
					fadeColors[1].g = 0xFF;
					fadeColors[1].b = 0xFF;
					fadeColors[1].a = 0;
					fadeColors[2].r = 0xFF;
					fadeColors[2].g = 0xFF;
					fadeColors[2].b = 0xFF;
					fadeColors[2].a = 0;
					fadeColors[3].r = 0xFF;
					fadeColors[3].g = 0xFF;
					fadeColors[3].b = 0xFF;
					fadeColors[3].a = 0;
					float remainW = (static_cast<float>(DOUBLE_80333008) / static_cast<float>(entry->duration)) * w;
					if (tex == 0x51) {
						int yStep = static_cast<int>(y);
						float end = y + h;
						while (static_cast<float>(yStep) < end) {
							int tileH = static_cast<int>(end - static_cast<float>(yStep));
							if (static_cast<float>(tileH) > FLOAT_80332FFC) {
								tileH = 0x18;
							}
							MenuPcs.DrawRect(
								static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
								remainW, static_cast<float>(tileH), u, v,
								fadeColors, uvScale, FLOAT_80333000, FLOAT_80332FF8);
							yStep += 0x18;
						}
					} else {
						MenuPcs.DrawRect(
							static_cast<unsigned long>(entry->drawFlags), x, y, remainW, h, u, v,
							fadeColors, uvScale, FLOAT_80333000, FLOAT_80332FF8);
					}
				}

				MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
			} else {
				MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
				GXColor color;
				color.r = 0xFF;
				color.g = 0xFF;
				color.b = 0xFF;
				color.a = static_cast<unsigned char>(alpha * FLOAT_80333010);
				GXSetChanMatColor(GX_COLOR0A0, color);
				MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, FLOAT_80332FF8);
			}
		}

		entry++;
	}

	float globalAlpha = compaList->entries[0].alpha;

	GXColor color;
	color.r = 0xFF;
	color.g = 0xFF;
	color.b = 0xFF;
	color.a = static_cast<unsigned char>(globalAlpha * FLOAT_80333010);
	GXSetChanMatColor(GX_COLOR0A0, color);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3A));

	int familyCount = 2;
	for (int i = 2; i < 7; i++) {
		if (*reinterpret_cast<short*>(scriptFood + 0x9CA + i * 2) > 0) {
			familyCount++;
		}
	}
	if (familyCount > 4 && System.m_execParam >= 1) {
		System.Printf(const_cast<char*>(s_pcts_pctd_family_cnt_error_pctd_801DEDC8), s_menu_compa_cpp_801DEDE8, 0x1BF,
		              familyCount);
	}
	if (familyCount > 4) {
		familyCount = 4;
	}

	for (int i = 0; i < familyCount; i++) {
		MenuPcs.DrawRect(
			0,
			static_cast<float>(compaList->entries[0].x + 0x10),
			static_cast<float>(compaList->entries[0].y + 0x40 + i * 0x28),
			FLOAT_80333014, FLOAT_80333018, FLOAT_80332FF8, FLOAT_80332FF8, FLOAT_80333000,
			FLOAT_80333000, FLOAT_80332FF8);
	}

	int memberIndex = 0;
	int shown = 0;
	for (int i = 0; i < 8 && shown < familyCount; i++) {
		int drawIndex = memberIndex;
		if (memberIndex > 1) {
			while (drawIndex < 8 && *reinterpret_cast<short*>(scriptFood + 0x9CA + drawIndex * 2) == 0) {
				drawIndex++;
			}
			if (drawIndex > 7) {
				break;
			}
		}

		const u8* compatibility = reinterpret_cast<const u8*>(&Game) + *reinterpret_cast<int*>(scriptFood + 8) * 0x208 + drawIndex + 0xA9;
		u8 food = *compatibility;
		if (food == 0 && System.m_execParam >= 1) {
			System.Printf(const_cast<char*>(s_pcts_pctd_family_cnt_error_pctd_801DEDC8), s_menu_compa_cpp_801DEDE8, 0x1E0,
			              shown);
		}
		int icon = 0x1D;
		if (food < 0x15) {
			icon = 0x21;
		} else if (food < 0x29) {
			icon = 0x20;
		} else if (food < 0x3D) {
			icon = 0x1F;
		} else if (food < 0x51) {
			icon = 0x1E;
		}

		DrawSingleIcon(
			icon,
			static_cast<int>(compaList->entries[0].x + 0x128),
			static_cast<int>(compaList->entries[0].y + 0x40 + shown * 0x28),
			globalAlpha, 1, FLOAT_80333000);

		shown++;
		memberIndex = drawIndex + 1;
	}

	CFont* font = listFont;
	font->SetMargin(FLOAT_80333000);
	font->SetShadow(0);
	font->SetScaleX(FLOAT_8033301C);
	font->SetScaleY(FLOAT_80333000);
	font->DrawInit();

	GXColor textColor = CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(FLOAT_80333010 * globalAlpha)).color;
	font->SetColor(textColor);

	const CompaFlatData* flatData = reinterpret_cast<const CompaFlatData*>(&Game.m_cFlatDataArr[1]);
	memberIndex = 0;
	shown = 0;
	for (int i = 0; i < 8 && shown < familyCount; i++) {
		int drawIndex = memberIndex;
		if (memberIndex > 1) {
			while (drawIndex < 8 && *reinterpret_cast<short*>(scriptFood + 0x9CA + drawIndex * 2) <= 0) {
				drawIndex++;
			}
			if (drawIndex > 7) {
				break;
			}
		}

		const char* name = GetMenuStr(drawIndex + 0x16);
		float y = static_cast<float>(compaList->entries[0].y + 0x45 + shown * 0x28) - FLOAT_80333020;
		font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x18));
		font->SetPosY(y);
		font->Draw(name);

		short food = *reinterpret_cast<short*>(scriptFood + 0x9CA + drawIndex * 2);
		const char* value = flatData->table[2].strings[food];
		font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x90));
		font->SetPosY(y);
		font->Draw(value);

		shown++;
		memberIndex = drawIndex + 1;
	}

	font = listFont;
	font->SetMargin(FLOAT_80333000);
	font->SetShadow(0);
	font->SetScale(FLOAT_80333024);
	font->DrawInit();
	font->SetColor(textColor);

	const char* job = GetJobStr(*reinterpret_cast<int*>(scriptFood + 0x3AC));
	font->GetWidth(job);
	font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x18));
	font->SetPosY(static_cast<float>(compaList->entries[0].y + 0x20) - FLOAT_80333020 - FLOAT_80333028);
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
    this->compaMenuState->frame = this->compaMenuState->frame + 1;
    count = this->compaList->count;
    entry = this->compaList->entries;
    frame = this->compaMenuState->frame;
    for (int i = 0; i < count; i++) {
        if (frame >= entry->startFrame) {
            if (entry->startFrame + entry->duration <= frame) {
                finishedCount = finishedCount + 1;
                entry->alpha = FLOAT_80332FF8;
                entry->dx = FLOAT_80332FF8;
                entry->dy = FLOAT_80332FF8;
            } else {
                entry->frame = entry->frame + 1;
                entry->alpha =
                    (float)(DOUBLE_80333008 - (DOUBLE_80333008 / (double)entry->duration) * (double)entry->frame);
                if ((entry->flags & 2) == 0) {
                    float step =
                        (float)(DOUBLE_80333008 - (DOUBLE_80333008 / (double)entry->duration) * (double)entry->frame);
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
	int padState = Pad._452_4_;
	unsigned int rawPress;
	unsigned int rawHold;
	short press;
	short hold;
	int doReset = 0;

	if (padState == 0) {
		if (Pad._448_4_ != -1) {
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
		int mask = -((__cntlzw((unsigned int)Pad._448_4_) >> 5) & 1);
		port &= ~mask;
		rawPress = *reinterpret_cast<unsigned short*>(reinterpret_cast<u8*>(&Pad) + port * 0x54 + 8);
	}
	press = rawPress & 0xffff;

	activeInput = false;
	if (padState == 0) {
		if (Pad._448_4_ != -1) {
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
		int mask = -((__cntlzw((unsigned int)Pad._448_4_) >> 5) & 1);
		port &= ~mask;
		rawHold = *reinterpret_cast<unsigned short*>(reinterpret_cast<u8*>(&Pad) + port * 0x54 + 0x14);
	}
	hold = rawHold & 0xffff;

	if (hold == 0) {
		doReset = 0;
	} else if ((press & 0x20) != 0) {
		this->compaMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x40) != 0) {
		this->compaMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = 1;
	} else if ((press & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
		doReset = 0;
	} else if ((press & 0x200) != 0) {
		this->compaMenuState->closeRequested = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		doReset = 1;
	} else {
		doReset = 0;
	}

	if (doReset != 0) {
		CompaOpenAnimList* compaList = this->compaList;
		int entryIndex = 0;
		CompaOpenAnim* setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 2;
		setupEntry->duration = 5;
		compaList = this->compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 2;
		setupEntry->duration = 5;
		compaList = this->compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 2;
		setupEntry->duration = 5;
		compaList = this->compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;
		compaList = this->compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;
		compaList = this->compaList;
		setupEntry = &compaList->entries[entryIndex++];
		setupEntry->flags = 2;
		setupEntry->startFrame = 7;
		setupEntry->duration = 5;

		unsigned int entryCount = compaList->count;
		CompaOpenAnim* entry = compaList->entries;
		while (entryCount != 0) {
			entry->frame = 0;
			entry->alpha = FLOAT_80333000;
			entry++;
			entryCount--;
		}
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

    if (this->compaMenuState->initialized == '\0') {
        CompaInit();
    }

    finishedCount = 0;
    this->compaMenuState->frame = this->compaMenuState->frame + 1;
    count = this->compaList->count;
    entry = this->compaList->entries;
    frame = this->compaMenuState->frame;
    for (int i = 0; i < count; i++) {
        if (frame >= entry->startFrame) {
            if (entry->startFrame + entry->duration <= frame) {
                finishedCount = finishedCount + 1;
                entry->alpha = FLOAT_80333000;
                entry->dx = FLOAT_80332FF8;
                entry->dy = FLOAT_80332FF8;
            } else {
                entry->frame = entry->frame + 1;
                entry->alpha = (float)((DOUBLE_80333008 / (double)entry->duration) * (double)entry->frame);
                if ((entry->flags & 2) == 0) {
                    float step = (float)((DOUBLE_80333008 / (double)entry->duration) * (double)entry->frame);
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
	memset(this->compaList, 0, 0x1008);

	CompaOpenAnim* entry = this->compaList->entries;
	int count = 8;
	do {
		entry[0].uvScale = FLOAT_80333000;
		entry[1].uvScale = FLOAT_80333000;
		entry[2].uvScale = FLOAT_80333000;
		entry[3].uvScale = FLOAT_80333000;
		entry[4].uvScale = FLOAT_80333000;
		entry[5].uvScale = FLOAT_80333000;
		entry[6].uvScale = FLOAT_80333000;
		entry[7].uvScale = FLOAT_80333000;
		entry += 8;
	} while (--count != 0);

	CompaOpenAnimList* compaList = this->compaList;
	int entryIndex = 0;
	CompaOpenAnim* setupEntry = &compaList->entries[entryIndex++];
	setupEntry->tex = 0x52;
	setupEntry->drawFlags = 4;
	setupEntry->x = 0x28;
	setupEntry->y = 0x30;
	setupEntry->w = 0x198;
	setupEntry->h = 0x18;
	setupEntry->u = FLOAT_80332FF8;
	setupEntry->v = FLOAT_80332FF8;
	setupEntry->uvScale = FLOAT_80333000;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	compaList = this->compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->tex = 0x51;
	setupEntry->x = 0x28;
	setupEntry->y = 0x48;
	setupEntry->w = 0x198;
	setupEntry->h = 200;
	setupEntry->u = FLOAT_80332FF8;
	setupEntry->v = FLOAT_80332FF8;
	setupEntry->uvScale = FLOAT_80333000;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	compaList = this->compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->tex = 0x52;
	setupEntry->x = 0x28;
	setupEntry->y = 0x110;
	setupEntry->w = 0x198;
	setupEntry->h = 0x18;
	setupEntry->u = FLOAT_80332FF8;
	setupEntry->v = FLOAT_80332FF8;
	setupEntry->uvScale = FLOAT_80333000;
	setupEntry->startFrame = 5;
	setupEntry->duration = 5;

	compaList = this->compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->tex = 0x5e;
	setupEntry->x = 0x10;
	setupEntry->y = 0xe;
	setupEntry->w = 0x30;
	setupEntry->h = 0x30;
	setupEntry->u = FLOAT_80332FF8;
	setupEntry->v = FLOAT_80332FF8;
	setupEntry->uvScale = FLOAT_80333000;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	compaList = this->compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->tex = 0x5e;
	setupEntry->x = 0x15;
	setupEntry->w = 0x30;
	setupEntry->h = 0x30;
	setupEntry->y = static_cast<short>(0x150 - setupEntry->h);
	setupEntry->u = FLOAT_80332FF8;
	setupEntry->v = FLOAT_80332FF8;
	setupEntry->uvScale = FLOAT_80333038;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	compaList = this->compaList;
	setupEntry = &compaList->entries[entryIndex++];
	setupEntry->flags = 2;
	setupEntry->drawFlags = 0x2e;
	setupEntry->x = 0x10;
	setupEntry->y = 8;
	setupEntry->w = 0x30;
	setupEntry->h = 0x140;
	setupEntry->u = FLOAT_8033303C;
	setupEntry->v = FLOAT_80332FF8;
	setupEntry->startFrame = 0;
	setupEntry->duration = 5;

	this->compaList->count = 6;
	this->compaMenuState->selectedIndex = 0;
	this->compaMenuState->initialized = 1;
}
