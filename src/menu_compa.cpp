#include "ffcc/menu_compa.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

typedef unsigned char u8;

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void Printf__7CSystemFPce(CSystem*, const char*, ...);
extern CMenuPcs MenuPcs;

extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* GetJobStr__8CMenuPcsFi(CMenuPcs*, int);

const float FLOAT_80332FF8 = 0.0f;
const float FLOAT_80332FFC = 24.0f;
const float FLOAT_80333000 = 1.0f;
const double DOUBLE_80333008 = 1.0;
const float FLOAT_80333010 = 255.0f;
const float FLOAT_80333014 = 328.0f;
const float FLOAT_80333018 = 40.0f;
const float FLOAT_8033301C = 0.8f;
const float FLOAT_80333020 = 4.0f;
const float FLOAT_80333024 = 1.2f;
const float FLOAT_80333028 = 2.0f;
const double DOUBLE_80333030 = 4503601774854144.0;
const float FLOAT_80333038 = 0.75f;
const float FLOAT_8033303C = 72.0f;

extern "C" const char s_pcts_pctd_family_cnt_error_pctd_801DEDC8[] = "%s(%d):family cnt error!!(%d)\n";
extern "C" const char s_menu_compa_cpp_801DEDE8[] = "menu_compa.cpp";

extern "C" const char lbl_803334A8[] = "MONO";
extern "C" const char lbl_803334B0[] = "Normal";
extern "C" const char lbl_803334B8[] = "Forza";
extern "C" const char lbl_803334C0[] = "Difesa";
extern "C" const char lbl_803334C8[] = "Sonoro";
extern "C" const char lbl_803334D0[] = "Musica";
extern "C" const char lbl_803334D8[] = "Mono";
extern "C" const char lbl_803334E0[] = "Contr.";
extern "C" const char lbl_803334E8[] = "Norm.";

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
	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);

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
				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 1);
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);

				GXColor colors[4];
				reinterpret_cast<unsigned int*>(colors)[0] = 0xFFFFFFFF;
				reinterpret_cast<unsigned int*>(colors)[1] = 0xFFFFFFFF;
				reinterpret_cast<unsigned int*>(colors)[2] = 0xFFFFFFFF;
				reinterpret_cast<unsigned int*>(colors)[3] = 0xFFFFFFFF;
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
							DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
								&MenuPcs, static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
								fillW, static_cast<float>(tileH), u, v,
								colors, uvScale, FLOAT_80333000, FLOAT_80332FF8);
							yStep += 0x18;
						}
					} else {
						DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
							&MenuPcs, static_cast<unsigned long>(entry->drawFlags), x, y, fillW, h, u, v,
							colors, uvScale, FLOAT_80333000, FLOAT_80332FF8);
					}

					u += fillW;
					x += fillW * uvScale;
				}

				if (fillW > FLOAT_80332FF8 && fillW < w) {
					GXColor fadeColors[4];
					reinterpret_cast<unsigned int*>(fadeColors)[0] = 0xFFFFFF00;
					reinterpret_cast<unsigned int*>(fadeColors)[1] = 0xFFFFFF00;
					reinterpret_cast<unsigned int*>(fadeColors)[2] = 0xFFFFFF00;
					reinterpret_cast<unsigned int*>(fadeColors)[3] = 0xFFFFFF00;
					float remainW = (static_cast<float>(DOUBLE_80333008) / static_cast<float>(entry->duration)) * w;
					if (tex == 0x51) {
						int yStep = static_cast<int>(y);
						float end = y + h;
						while (static_cast<float>(yStep) < end) {
							int tileH = static_cast<int>(end - static_cast<float>(yStep));
							if (static_cast<float>(tileH) > FLOAT_80332FFC) {
								tileH = 0x18;
							}
							DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
								&MenuPcs, static_cast<unsigned long>(entry->drawFlags), x, static_cast<float>(yStep),
								remainW, static_cast<float>(tileH), u, v,
								fadeColors, uvScale, FLOAT_80333000, FLOAT_80332FF8);
							yStep += 0x18;
						}
					} else {
						DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
							&MenuPcs, static_cast<unsigned long>(entry->drawFlags), x, y, remainW, h, u, v,
							fadeColors, uvScale, FLOAT_80333000, FLOAT_80332FF8);
					}
				}

				SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);
			} else {
				SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);
				GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha * FLOAT_80333010)};
				GXSetChanMatColor(GX_COLOR0A0, color);
				DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, x, y, w, h, u, v, uvScale, uvScale, FLOAT_80332FF8);
			}
		}

		entry++;
	}

	float globalAlpha = compaList->entries[0].alpha;

	GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(globalAlpha * FLOAT_80333010)};
	GXSetChanMatColor(GX_COLOR0A0, color);
	SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x3A);

	int familyCount = 2;
	for (int i = 2; i < 7; i++) {
		if (*reinterpret_cast<short*>(scriptFood + 0x9CA + i * 2) > 0) {
			familyCount++;
		}
	}
	if (familyCount > 4 && System.m_execParam >= 1) {
		Printf__7CSystemFPce(&System, s_pcts_pctd_family_cnt_error_pctd_801DEDC8, s_menu_compa_cpp_801DEDE8, 0x1BF, familyCount);
	}
	if (familyCount > 4) {
		familyCount = 4;
	}

	for (int i = 0; i < familyCount; i++) {
		DrawRect__8CMenuPcsFUlfffffffff(
			&MenuPcs, 0,
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
			Printf__7CSystemFPce(&System, s_pcts_pctd_family_cnt_error_pctd_801DEDC8, s_menu_compa_cpp_801DEDE8, 0x1E0, shown);
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

		DrawSingleIcon__8CMenuPcsFiiifif(
			this, icon,
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

		const char* name = GetMenuStr__8CMenuPcsFi(this, drawIndex + 0x16);
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

	const char* job = GetJobStr__8CMenuPcsFi(this, *reinterpret_cast<int*>(scriptFood + 0x3AC));
	font->GetWidth(job);
	font->SetPosX(static_cast<float>(compaList->entries[0].x + 0x18));
	font->SetPosY(static_cast<float>(compaList->entries[0].y + 0x20) - FLOAT_80333020 - FLOAT_80333028);
	font->Draw(job);

	DrawInit__8CMenuPcsFv(this);
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
    int finishedCount;
    int count;
    int frame;
    CompaOpenAnim* entry;

    finishedCount = 0;
    this->compaMenuState->frame = this->compaMenuState->frame + 1;
    count = this->compaList->count;
    entry = this->compaList->entries;
    frame = this->compaMenuState->frame;
    for (int i = 0; i < count; i++) {
        float step = FLOAT_80332FF8;
        if (frame >= entry->startFrame) {
            if (entry->startFrame + entry->duration <= frame) {
                finishedCount = finishedCount + 1;
                entry->alpha = FLOAT_80332FF8;
                entry->dx = step;
                entry->dy = step;
            } else {
                entry->frame = entry->frame + 1;
                entry->alpha =
                    (float)-((DOUBLE_80333008 / (double)entry->duration) * (double)entry->frame - DOUBLE_80333008);
                if ((entry->flags & 2) == 0) {
                    step =
                        (float)-((DOUBLE_80333008 / (double)entry->duration) * (double)entry->frame - DOUBLE_80333008);
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
	short press;
	short hold;
	int doReset = 0;

	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		press = 0;
	} else {
		int padIndex = activeInput;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		press = *reinterpret_cast<unsigned short*>(reinterpret_cast<u8*>(&Pad) + padIndex * 0x54 + 8);
	}

	activeInput = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		activeInput = true;
	}

	if (activeInput) {
		hold = 0;
	} else {
		int padIndex = activeInput;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		hold = *reinterpret_cast<unsigned short*>(reinterpret_cast<u8*>(&Pad) + padIndex * 0x54 + 0x14);
	}

	if (hold == 0) {
		doReset = false;
	} else if ((press & 0x20) != 0) {
		this->compaMenuState->cursorMove = 1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = true;
	} else if ((press & 0x40) != 0) {
		this->compaMenuState->cursorMove = -1;
		Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
		doReset = true;
	} else if ((press & 0x100) != 0) {
		Sound.PlaySe(4, 0x40, 0x7f, 0);
		doReset = false;
	} else if ((press & 0x200) != 0) {
		this->compaMenuState->closeRequested = 1;
		Sound.PlaySe(3, 0x40, 0x7f, 0);
		doReset = true;
	} else {
		doReset = false;
	}

	if (doReset) {
		CompaOpenAnim* entries = this->compaList->entries;
		entries[0].startFrame = 2;
		entries[0].duration = 5;
		entries[1].startFrame = 2;
		entries[1].duration = 5;
		entries[2].startFrame = 2;
		entries[2].duration = 5;
		entries[3].startFrame = 7;
		entries[3].duration = 5;
		entries[4].startFrame = 7;
		entries[4].duration = 5;
		entries[5].flags = 2;
		entries[5].startFrame = 7;
		entries[5].duration = 5;

		unsigned int entryCount = this->compaList->count;
		CompaOpenAnim* entry = entries;
		while (entryCount != 0) {
			entry->frame = 0;
			entry->alpha = 1.0f;
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
    int finishedCount;
    int count;
    int frame;
    CompaOpenAnim* entry;

    if (this->compaMenuState->initialized == '\0') {
        CompaInit();
    }

    finishedCount = 0;
    this->compaMenuState->frame = this->compaMenuState->frame + 1;
    count = this->compaList->count;
    entry = this->compaList->entries;
    frame = this->compaMenuState->frame;
    for (int i = 0; i < count; i++) {
        float step = FLOAT_80332FF8;
        if (frame >= entry->startFrame) {
            if (entry->startFrame + entry->duration <= frame) {
                finishedCount = finishedCount + 1;
                entry->alpha = FLOAT_80333000;
                entry->dx = step;
                entry->dy = step;
            } else {
                entry->frame = entry->frame + 1;
                entry->alpha = (float)((DOUBLE_80333008 / (double)entry->duration) * (double)entry->frame);
                if ((entry->flags & 2) == 0) {
                    step = (float)((DOUBLE_80333008 / (double)entry->duration) * (double)entry->frame);
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
	CompaOpenAnim* setupEntry = &compaList->entries[0];
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
	setupEntry = &compaList->entries[1];
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
	setupEntry = &compaList->entries[2];
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
	setupEntry = &compaList->entries[3];
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
	setupEntry = &compaList->entries[4];
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
	setupEntry = &compaList->entries[5];
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
