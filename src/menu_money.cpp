#include "ffcc/menu_money.h"
#include "ffcc/fontman.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"

#include <string.h>

typedef unsigned char u8;

extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawSingWin__8CMenuPcsFs(CMenuPcs*, short);
extern "C" void DrawSingWinMess__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" int SingWinMessHeight__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);

extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);

extern float FLOAT_80332f60;
extern float FLOAT_80332f64;
extern float FLOAT_80332f68;
extern float FLOAT_80332f6c;
extern float FLOAT_80332f70;
extern float FLOAT_80332f74;
extern float FLOAT_80332f78;
extern float FLOAT_80332f7c;
extern float FLOAT_80332f80;
extern float FLOAT_80332f84;

namespace {
unsigned int DAT_8032eee0 = 0;
signed char s_place[16];

struct MenuMoneyMembers {
    unsigned char pad_0000[0x108];
    CFont* m_moneyFont;
    unsigned char pad_010C[0x720];
    short* m_moneyState;
    unsigned char pad_0830[0x18];
    short* m_singWindow;
    unsigned char pad_084C[0x4];
    short* m_moneyPanel;
};

STATIC_ASSERT(offsetof(MenuMoneyMembers, m_moneyFont) == 0x108);
STATIC_ASSERT(offsetof(MenuMoneyMembers, m_moneyState) == 0x82C);
STATIC_ASSERT(offsetof(MenuMoneyMembers, m_singWindow) == 0x848);
STATIC_ASSERT(offsetof(MenuMoneyMembers, m_moneyPanel) == 0x850);

static inline MenuMoneyMembers& GetMenuMoneyMembers(CMenuPcs* menu) {
    return *reinterpret_cast<MenuMoneyMembers*>(menu);
}

static inline short* GetMoneyState(CMenuPcs* menu) {
    return GetMenuMoneyMembers(menu).m_moneyState;
}

static inline short* GetMoneyPanel(CMenuPcs* menu) {
    return GetMenuMoneyMembers(menu).m_moneyPanel;
}

static inline short* GetSingWindow(CMenuPcs* menu) {
    return GetMenuMoneyMembers(menu).m_singWindow;
}

static inline CFont* GetMoneyFont(CMenuPcs* menu) {
    return GetMenuMoneyMembers(menu).m_moneyFont;
}

static inline int GetMoneyStateBase(CMenuPcs* menu) {
    return reinterpret_cast<int>(GetMoneyState(menu));
}

static inline int GetMoneyPanelBase(CMenuPcs* menu) {
    return reinterpret_cast<int>(GetMoneyPanel(menu));
}

static unsigned short GetPadHoldMask() {
    return *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(&Pad) + 0x20);
}

static void UpdateDigits(unsigned int value, signed char* outDigits) {
    int div = 10000000;
    bool started = false;

    for (int i = 0; i < 8; ++i) {
        if (!started && div <= static_cast<int>(value)) {
            started = true;
        }

        if (started || div <= static_cast<int>(value) || i > 6) {
            int digit = static_cast<int>(value) / div;
            if (digit > 9) {
                digit = 9;
            }
            outDigits[i] = static_cast<signed char>(digit);
            value -= digit * static_cast<unsigned int>(div);
        } else {
            outDigits[i] = -1;
        }

        div /= 10;
    }
}
} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MoneyInit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8015f688
 * PAL Size: 928b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::MoneyOpen()
{
	float fVar1;
	int iVar7;
	int iVar8;
	int iVar10;
	int iVar12;
	int iVar13;
	int iVar15;
	signed char* puVar9;
	short* psVar11;
	signed char* puVar14;

	if (*(char*)(GetMoneyStateBase(this) + 0xB) == '\0') {
		memset(GetMoneyPanel(this), 0, 0x1008);

		fVar1 = FLOAT_80332f70;
		iVar8 = GetMoneyPanelBase(this) + 8;
		iVar15 = 8;
		do {
			*(float *)(iVar8 + 0x14) = fVar1;
			*(float *)(iVar8 + 0x54) = fVar1;
			*(float *)(iVar8 + 0x94) = fVar1;
			*(float *)(iVar8 + 0xd4) = fVar1;
			*(float *)(iVar8 + 0x114) = fVar1;
			*(float *)(iVar8 + 0x154) = fVar1;
			*(float *)(iVar8 + 0x194) = fVar1;
			*(float *)(iVar8 + 0x1d4) = fVar1;
			iVar8 = iVar8 + 0x200;
			iVar15 = iVar15 + -1;
		} while (iVar15 != 0);

		iVar8 = GetMoneyPanelBase(this);
		*(int *)(iVar8 + 0x24) = 0x3b;
		*(short *)(iVar8 + 10) = 0x68;
		*(short *)(iVar8 + 0xc) = 0xf8;
		*(short *)(iVar8 + 0xe) = 0x88;
		*(short *)(iVar8 + 8) = static_cast<short>(-(static_cast<int>(*(short *)(iVar8 + 0xc)) / 2));
		*(float *)(iVar8 + 0x10) = FLOAT_80332f64;
		*(float *)(iVar8 + 0x14) = FLOAT_80332f64;
		*(float *)(iVar8 + 0x1c) = FLOAT_80332f70;
		*(int *)(iVar8 + 0x2c) = 0;
		*(int *)(iVar8 + 0x30) = 10;
		*GetMoneyPanel(this) = 1;

		DAT_8032eee0 = 0;
		puVar9 = s_place;
		iVar15 = 0;
		do {
			iVar8 = 10000000;
			if (iVar15 == 0) {
				iVar12 = *(int *)(Game.game.m_scriptFoodBase[0] + 0x200);
			} else {
				iVar12 = 0;
			}
			iVar13 = 0;
			iVar7 = 8;
			bool started = false;
			puVar14 = puVar9;
			do {
				if ((!started) && (iVar8 <= iVar12)) {
					started = true;
				}
				if (((started) || (iVar8 <= iVar12)) || (6 < iVar13)) {
					iVar10 = iVar12 / iVar8;
					if (9 < iVar10) {
						iVar10 = 9;
					}
					*puVar14 = static_cast<signed char>(iVar10);
					iVar12 = iVar12 - (iVar12 / iVar8) * iVar8;
				} else {
					*puVar14 = -1;
				}
				puVar14 = puVar14 + 1;
				iVar13 = iVar13 + 1;
				iVar8 /= 10;
				iVar7 = iVar7 + -1;
			} while (iVar7 != 0);
			iVar15 = iVar15 + 1;
			puVar9 = puVar9 + 8;
		} while (iVar15 < 2);

		*(short*)(GetMoneyStateBase(this) + 0x26) = 0;
		*(char*)(GetMoneyStateBase(this) + 0xB) = 1;
	}

	iVar15 = 0;
	*(short*)(GetMoneyStateBase(this) + 0x22) = *(short*)(GetMoneyStateBase(this) + 0x22) + 1;
	iVar12 = static_cast<int>(*GetMoneyPanel(this));
	psVar11 = GetMoneyPanel(this) + 4;
	iVar7 = static_cast<int>(*(short*)(GetMoneyStateBase(this) + 0x22));
	iVar8 = iVar12;
	if (0 < iVar12) {
		do {
			if (*(int *)(psVar11 + 0x12) <= iVar7) {
				if (iVar7 < *(int *)(psVar11 + 0x12) + *(int *)(psVar11 + 0x14)) {
					*(int *)(psVar11 + 0x10) = *(int *)(psVar11 + 0x10) + 1;
					fVar1 = static_cast<float>(*(int *)(psVar11 + 0x10)) / static_cast<float>(*(int *)(psVar11 + 0x14));
					*(float *)(psVar11 + 8) = fVar1;
					if ((*(unsigned int *)(psVar11 + 0x16) & 2) == 0) {
						*(float *)(psVar11 + 0x18) = (*(float *)(psVar11 + 0x1c) - static_cast<float>(*psVar11)) * fVar1;
						*(float *)(psVar11 + 0x1a) = (*(float *)(psVar11 + 0x1e) - static_cast<float>(psVar11[1])) * fVar1;
					}
				} else {
					iVar15 = iVar15 + 1;
					*(float *)(psVar11 + 8) = FLOAT_80332f70;
					*(float *)(psVar11 + 0x18) = FLOAT_80332f64;
					*(float *)(psVar11 + 0x1a) = FLOAT_80332f64;
				}
			}
			psVar11 = psVar11 + 0x20;
			iVar8 = iVar8 + -1;
		} while (iVar8 != 0);
	}

	return iVar12 == iVar15;
}

/*
 * --INFO--
 * PAL Address: 8015f588
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::MoneyCtrl()
{
	int iVar2 = 0;
	int iVar3;
	short sVar1;

	*reinterpret_cast<short*>(GetMoneyStateBase(this) + 0x32) = *reinterpret_cast<short*>(GetMoneyStateBase(this) + 0x30);
	iVar3 = GetMoneyStateBase(this);
	sVar1 = *reinterpret_cast<short*>(iVar3 + 0x30);
	if ((sVar1 == 0) || ((sVar1 != 0 && (*reinterpret_cast<short*>(iVar3 + 0x12) == 1)))) {
		iVar2 = MoneyCtrlCur();
	} else if ((sVar1 == 1) && (*reinterpret_cast<short*>(iVar3 + 0x12) == 0)) {
		if (*reinterpret_cast<short*>(reinterpret_cast<int>(GetSingWindow(this)) + 10) == 1) {
			iVar2 = 0;
			*reinterpret_cast<short*>(iVar3 + 0x12) = 1;
		}
	} else if (((sVar1 == 1) && (*reinterpret_cast<short*>(iVar3 + 0x12) == 2)) &&
		       (*reinterpret_cast<short*>(reinterpret_cast<int>(GetSingWindow(this)) + 10) == 3)) {
		iVar2 = 0;
		*reinterpret_cast<short*>(iVar3 + 0x12) = 0;
		*reinterpret_cast<short*>(GetMoneyStateBase(this) + 0x30) = 0;
		*reinterpret_cast<short*>(GetMoneyStateBase(this) + 0x22) = 0;
	}

	if (iVar2 != 0) {
		iVar2 = GetMoneyPanelBase(this);
		*reinterpret_cast<float*>(iVar2 + 0x18) = FLOAT_80332f70;
		*reinterpret_cast<int*>(iVar2 + 0x2c) = 0;
		*reinterpret_cast<int*>(iVar2 + 0x30) = 10;
		*reinterpret_cast<int*>(iVar2 + 0x28) = 0;
	}
}

/*
 * --INFO--
 * PAL Address: 8015f40c
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::MoneyClose()
{
	float fVar1;
	int iVar4;
	short* psVar5;
	int iVar6;
	int iVar7;
	int iVar8;

	iVar4 = 0;
	*(short*)(GetMoneyStateBase(this) + 0x22) = *(short*)(GetMoneyStateBase(this) + 0x22) + 1;
	iVar6 = (int)*GetMoneyPanel(this);
	psVar5 = GetMoneyPanel(this) + 4;
	iVar7 = (int)*(short*)(GetMoneyStateBase(this) + 0x22);
	iVar8 = iVar6;
	if (0 < iVar6) {
		do {
			fVar1 = FLOAT_80332f64;
			if (*(int *)(psVar5 + 0x12) <= iVar7) {
				if (iVar7 < *(int *)(psVar5 + 0x12) + *(int *)(psVar5 + 0x14)) {
					*(int *)(psVar5 + 0x10) = *(int *)(psVar5 + 0x10) + 1;
					*(float *)(psVar5 + 8) = FLOAT_80332f70 - (float)*(int *)(psVar5 + 0x10) / (float)*(int *)(psVar5 + 0x14);
					if ((*(unsigned int *)(psVar5 + 0x16) & 2) == 0) {
						fVar1 = FLOAT_80332f70 - (float)*(int *)(psVar5 + 0x10) / (float)*(int *)(psVar5 + 0x14);
						*(float *)(psVar5 + 0x18) = (*(float *)(psVar5 + 0x1c) - (float)*psVar5) * fVar1;
						*(float *)(psVar5 + 0x1a) = (*(float *)(psVar5 + 0x1e) - (float)psVar5[1]) * fVar1;
					}
				}
				else {
					iVar4 = iVar4 + 1;
					*(float *)(psVar5 + 8) = FLOAT_80332f64;
					*(float *)(psVar5 + 0x18) = fVar1;
					*(float *)(psVar5 + 0x1a) = fVar1;
				}
			}
			psVar5 = psVar5 + 0x20;
			iVar8 = iVar8 + -1;
		} while (iVar8 != 0);
	}
	(void)iVar6;
	(void)iVar4;
}

/*
 * --INFO--
 * PAL Address: 8015eda8
 * PAL Size: 1636b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::MoneyDraw()
{
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

    short* moneyState = GetMoneyState(this);
    short selectionState = *reinterpret_cast<short*>((u8*)moneyState + 0x10);
    short mode = *reinterpret_cast<short*>((u8*)moneyState + 0x30);
    short* panel = GetMoneyPanel(this);

    short* entry = panel + 4;
    int entryCount = panel[0];
    for (int i = 0; i < entryCount; i++, entry += 0x20) {
        int tex = *reinterpret_cast<int*>(entry + 0xE);
        if (tex >= 0) {
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
            float alpha = *reinterpret_cast<float*>(entry + 8);
            GXColor color = {0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332f60 * alpha)};
            GXSetChanMatColor(GX_COLOR0A0, color);
            DrawRect__8CMenuPcsFUlfffffffff(
                this, 0, (float)entry[0], (float)entry[1], (float)entry[2], (float)entry[3],
                *reinterpret_cast<float*>(entry + 4), *reinterpret_cast<float*>(entry + 6),
                *reinterpret_cast<float*>(entry + 10), *reinterpret_cast<float*>(entry + 10), 0.0f);
        }
    }

    short* drawBase = panel + 4;
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x5D);
    {
        float alpha = *reinterpret_cast<float*>(panel + 0xC);
        GXColor color = {0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332f60 * alpha)};
        GXSetChanMatColor(GX_COLOR0A0, color);
    }

    for (int row = 0; row < 2; row++) {
        float rowY = (float)(drawBase[1] + 0x18) + FLOAT_80332f68 * (float)row;
        float x = (float)(panel[4] + 0x20);
        for (int i = 0; i < 8; i++) {
            signed char digit = s_place[row * 8 + i];
            if (digit >= 0) {
                DrawRect__8CMenuPcsFUlfffffffff(
                    this, 0, x, rowY, FLOAT_80332f6c, FLOAT_80332f68,
                    FLOAT_80332f6c * (float)digit, FLOAT_80332f68 * (float)row,
                    FLOAT_80332f70, FLOAT_80332f70, 0.0f);
            }
            x += FLOAT_80332f74;
        }
    }

    short* firstEntry = panel + 4;
    if (mode == 0 && selectionState == 1) {
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x48);
        {
            float alpha = *reinterpret_cast<float*>(panel + 0xC);
            GXColor color = {0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332f60 * alpha)};
            GXSetChanMatColor(GX_COLOR0A0, color);
        }

        float cursorX = (float)(firstEntry[0] + (7 - *reinterpret_cast<short*>((u8*)moneyState + 0x26)) * 0x12 + 0x24);
        float cursorY = (float)(panel[5] + 0x5C);
        DrawRect__8CMenuPcsFUlfffffffff(
            this, 0, cursorX, cursorY, FLOAT_80332f78, FLOAT_80332f6c,
            FLOAT_80332f64, FLOAT_80332f64, FLOAT_80332f70, FLOAT_80332f70, 0.0f);
    }

    CFont* font = GetMoneyFont(this);
    SetMargin__5CFontFf(FLOAT_80332f70, font);
    SetShadow__5CFontFi(font, 0);
    SetScale__5CFontFf(FLOAT_80332f7c, font);
    DrawInit__5CFontFv(font);

    {
        float alpha = *reinterpret_cast<float*>(firstEntry + 8);
        GXColor color = {0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332f60 * alpha)};
        SetColor__5CFontF8_GXColor(font, &color);
    }

    const char* label = GetMenuStr__8CMenuPcsFi(this, 0x15);
    for (int i = 0; i < 2; i++) {
        float textX = (float)(firstEntry[0] + 0xB6);
        float textY = (FLOAT_80332f68 + (FLOAT_80332f68 * (float)i + (float)(firstEntry[1] + 0x18))) - FLOAT_80332f80;
        SetPosX__5CFontFf(textX, font);
        SetPosY__5CFontFf(textY - FLOAT_80332f84, font);
        Draw__5CFontFPc(font, label);
    }

    DrawInit__8CMenuPcsFv(this);
    if (mode == 1) {
        DrawSingWin__8CMenuPcsFs(this, -1);
        if (*reinterpret_cast<short*>((u8*)moneyState + 0x12) == 1) {
            DrawSingWinMess__8CMenuPcsFiii(this, 1, (int)*((char*)moneyState + 9), 0);
        }
    }

    if (mode != 0 && *reinterpret_cast<short*>((u8*)moneyState + 0x12) == 1) {
        short* singWindow = GetSingWindow(this);
        float cursorX = (float)singWindow[0];
        float cursorY = (float)(singWindow[1] + 0x20);
        cursorY += (float)(*reinterpret_cast<short*>((u8*)moneyState + 0x28) * SingWinMessHeight__8CMenuPcsFv(this));

        int frame = (int)System.m_frameCounter;
        int frameSign = frame >> 31;
        int anim = ((frameSign * 8) | ((frame * 0x20000000 + frameSign) >> 29)) - frameSign;
        DrawCursor__8CMenuPcsFiif(this, (int)(cursorX + (float)anim), (int)cursorY, FLOAT_80332f70);
    }
}

/*
 * --INFO--
 * PAL Address: 8015e37c
 * PAL Size: 2604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::MoneyCtrlCur()
{
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[0]);

	bool blocked = false;
	unsigned short press;
	unsigned short hold;
	if (Pad._452_4_ != 0 || Pad._448_4_ != -1) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		press = Pad._8_2_;
	}

	blocked = false;
	if (Pad._452_4_ != 0 || Pad._448_4_ != -1) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		hold = GetPadHoldMask();
	}

	if (hold == 0) {
		return 0;
	}

	int menuState = GetMoneyStateBase(this);
	short mode = *reinterpret_cast<short*>(menuState + 0x30);

	int maxDigits = 1;
	int maxGil = caravanWork->m_gil;
	while (maxDigits < 8 && maxGil >= 10) {
		maxGil /= 10;
		++maxDigits;
	}

	if (mode != 0) {
		short* selectedFlag = reinterpret_cast<short*>(menuState + mode * 2 + 0x26);
		if ((hold & 8) != 0) {
			*selectedFlag = (*selectedFlag == 0) ? 1 : static_cast<short>(*selectedFlag - 1);
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((hold & 4) != 0) {
			*selectedFlag = (*selectedFlag < 1) ? 1 : 0;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0xC) != 0) {
			return 0;
		}

		if ((press & 0x200) != 0) {
			*reinterpret_cast<short*>(reinterpret_cast<int>(GetSingWindow(this)) + 10) = 2;
			*reinterpret_cast<short*>(menuState + 0x12) += 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			return 0;
		}

		if ((press & 0x100) != 0) {
			if (*selectedFlag == 0) {
				caravanWork->FGPutGil(static_cast<int>(DAT_8032eee0));
				DAT_8032eee0 = 0;
				UpdateDigits(static_cast<unsigned int>(caravanWork->m_gil), s_place);
				UpdateDigits(0, s_place + 8);
			}
			*reinterpret_cast<short*>(reinterpret_cast<int>(GetSingWindow(this)) + 10) = 2;
			*reinterpret_cast<short*>(menuState + 0x12) += 1;
			Sound.PlaySe(2, 0x40, 0x7f, 0);
		}
		return 0;
	}

	short cursor = *reinterpret_cast<short*>(menuState + 0x26);
	unsigned int placeValue = 1;
	for (int i = 0; i < cursor; ++i) {
		placeValue *= 10;
	}

	if ((hold & 8) != 0) {
		if (caravanWork->m_gil == 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else {
			unsigned int maxValue = static_cast<unsigned int>(caravanWork->m_gil);
			unsigned int nextValue = DAT_8032eee0 + placeValue;
			DAT_8032eee0 = (nextValue < maxValue) ? nextValue : maxValue;
			UpdateDigits(DAT_8032eee0, s_place + 8);
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}
	} else if ((hold & 4) != 0) {
		if (DAT_8032eee0 == 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else {
			DAT_8032eee0 = (DAT_8032eee0 >= placeValue) ? (DAT_8032eee0 - placeValue) : 0;
			UpdateDigits(DAT_8032eee0, s_place + 8);
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}
	}

	if ((hold & 1) != 0) {
		if (cursor < maxDigits - 1) {
			*reinterpret_cast<short*>(menuState + 0x26) = cursor + 1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		}
	} else if ((hold & 2) != 0) {
		if (cursor == 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else {
			*reinterpret_cast<short*>(menuState + 0x26) = cursor - 1;
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}
	}

	if ((hold & 0xF) == 0) {
		if ((press & 0x20) != 0) {
			*reinterpret_cast<short*>(menuState + 0x1e) = 1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return 1;
		}
		if ((press & 0x40) != 0) {
			*reinterpret_cast<short*>(menuState + 0x1e) = -1;
			Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
			return -1;
		}
		if ((press & 0x200) != 0) {
			*reinterpret_cast<char*>(menuState + 0xd) = 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			return 0;
		}
		if ((press & 0x100) != 0) {
			if (DAT_8032eee0 < 1) {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			} else {
				*reinterpret_cast<char*>(menuState + 9) = 2;
				*reinterpret_cast<short*>(reinterpret_cast<int>(GetSingWindow(this)) + 10) = 0;
				*reinterpret_cast<short*>(menuState + 0x12) = 0;
				*reinterpret_cast<short*>(menuState + 0x30) = 1;
				Sound.PlaySe(2, 0x40, 0x7f, 0);
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MoneySetPlace(int)
{
	// TODO
}
