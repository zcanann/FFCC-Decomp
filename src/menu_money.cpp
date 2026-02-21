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
	if (*(char *)(*(int *)((char*)this + 0x82c) + 0xb) == '\0') {
		memset(*(void**)((char*)this + 0x850), 0, 0x1008);

		float fVar1 = 1.0f;
		int iVar8 = *(int *)((char*)this + 0x850) + 8;
		int iVar15 = 8;
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

		int iVar8_2 = *(int *)((char*)this + 0x850);
		*(int *)(iVar8_2 + 0x24) = 0x3b;
		*(short *)(iVar8_2 + 10) = 0x68;
		*(short *)(iVar8_2 + 0xc) = 0xf8;
		*(short *)(iVar8_2 + 0xe) = 0x88;

		*(short *)(iVar8_2 + 8) = static_cast<short>(-(static_cast<int>(*(short *)(iVar8_2 + 0xc)) / 2));
		*(float *)(iVar8_2 + 0x10) = 0.0f;
		*(float *)(iVar8_2 + 0x14) = 0.0f;
		*(float *)(iVar8_2 + 0x1c) = 1.0f;
		*(int *)(iVar8_2 + 0x2c) = 0;
		*(int *)(iVar8_2 + 0x30) = 10;
		**(short**)((char*)this + 0x850) = 1;

		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.game.m_scriptFoodBase[0]);
		DAT_8032eee0 = 0;
		signed char* digits = s_place;
		for (int group = 0; group < 2; ++group) {
			int currentValue = (group == 0) ? caravanWork->m_gil : 0;
			int div = 10000000;
			bool started = false;

			for (int i = 0; i < 8; ++i) {
				if (!started && div <= currentValue) {
					started = true;
				}

				if (started || div <= currentValue || i > 6) {
					int digit = currentValue / div;
					if (digit > 9) {
						digit = 9;
					}
					digits[i] = static_cast<signed char>(digit);
					currentValue -= (currentValue / div) * div;
				} else {
					digits[i] = -1;
				}

				div /= 10;
			}

			digits += 8;
		}

		*(short *)(*(int *)((char*)this + 0x82c) + 0x26) = 0;
		*(char *)(*(int *)((char*)this + 0x82c) + 0xb) = 1;
	}

	int doneCount = 0;
	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);

	*reinterpret_cast<short*>(menuState + 0x22) = static_cast<short>(*reinterpret_cast<short*>(menuState + 0x22) + 1);
	int entryCount = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
	short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	int time = static_cast<int>(*reinterpret_cast<short*>(menuState + 0x22));

	for (int i = 0; i < entryCount; ++i) {
		if (*reinterpret_cast<int*>(entry + 0x12) <= time) {
			int duration = *reinterpret_cast<int*>(entry + 0x14);
			if (time < *reinterpret_cast<int*>(entry + 0x12) + duration) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				float t = static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(duration);
				*reinterpret_cast<float*>(entry + 8) = t;
				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					*reinterpret_cast<float*>(entry + 0x18) =
						(*reinterpret_cast<float*>(entry + 0x1c) - static_cast<float>(*entry)) * t;
					*reinterpret_cast<float*>(entry + 0x1a) =
						(*reinterpret_cast<float*>(entry + 0x1e) - static_cast<float>(entry[1])) * t;
				}
			} else {
				doneCount += 1;
				*reinterpret_cast<float*>(entry + 8) = 1.0f;
				*reinterpret_cast<float*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x1a) = 0.0f;
			}
		}
		entry += 0x20;
	}

	return entryCount == doneCount;
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
	int iVar3 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
	short sVar1;

	*reinterpret_cast<short*>(iVar3 + 0x32) = *reinterpret_cast<short*>(iVar3 + 0x30);
	sVar1 = *reinterpret_cast<short*>(iVar3 + 0x30);
	if ((sVar1 == 0) || ((sVar1 != 0 && (*reinterpret_cast<short*>(iVar3 + 0x12) == 1)))) {
		iVar2 = MoneyCtrlCur();
	} else if ((sVar1 == 1) && (*reinterpret_cast<short*>(iVar3 + 0x12) == 0)) {
		if (*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 10) == 1) {
			iVar2 = 0;
			*reinterpret_cast<short*>(iVar3 + 0x12) = 1;
		}
	} else if (((sVar1 == 1) && (*reinterpret_cast<short*>(iVar3 + 0x12) == 2)) &&
		       (*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 10) == 3)) {
		iVar2 = 0;
		*reinterpret_cast<short*>(iVar3 + 0x12) = 0;
		*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x30) = 0;
		*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c) + 0x22) = 0;
	}

	if (iVar2 != 0) {
		iVar2 = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x850);
		*reinterpret_cast<float*>(iVar2 + 0x18) = 1.0f;
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
	int doneCount = 0;
	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);

	*reinterpret_cast<short*>(menuState + 0x22) = static_cast<short>(*reinterpret_cast<short*>(menuState + 0x22) + 1);
	int entryCount = static_cast<int>(**reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850));
	short* entry = *reinterpret_cast<short**>(reinterpret_cast<char*>(this) + 0x850) + 4;
	int time = static_cast<int>(*reinterpret_cast<short*>(menuState + 0x22));
	for (int i = 0; i < entryCount; ++i) {
		if (*reinterpret_cast<int*>(entry + 0x12) <= time) {
			int duration = *reinterpret_cast<int*>(entry + 0x14);
			if (time < *reinterpret_cast<int*>(entry + 0x12) + duration) {
				*reinterpret_cast<int*>(entry + 0x10) = *reinterpret_cast<int*>(entry + 0x10) + 1;
				float t = static_cast<float>(*reinterpret_cast<int*>(entry + 0x10)) / static_cast<float>(duration);
				*reinterpret_cast<float*>(entry + 8) = 1.0f - t;
				if ((*reinterpret_cast<unsigned int*>(entry + 0x16) & 2) == 0) {
					float delta = 1.0f - t;
					*reinterpret_cast<float*>(entry + 0x18) = (*reinterpret_cast<float*>(entry + 0x1c) - static_cast<float>(*entry)) * delta;
					*reinterpret_cast<float*>(entry + 0x1a) = (*reinterpret_cast<float*>(entry + 0x1e) - static_cast<float>(entry[1])) * delta;
				}
			} else {
				doneCount += 1;
				*reinterpret_cast<float*>(entry + 8) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x18) = 0.0f;
				*reinterpret_cast<float*>(entry + 0x1a) = 0.0f;
			}
		}
		entry += 0x20;
	}

	(void)doneCount;
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

    short* moneyState = reinterpret_cast<short*>(*(int*)((u8*)this + 0x82c));
    short selectionState = *reinterpret_cast<short*>((u8*)moneyState + 0x10);
    short mode = *reinterpret_cast<short*>((u8*)moneyState + 0x30);
    short* panel = reinterpret_cast<short*>(*(int*)((u8*)this + 0x850));

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

    CFont* font = *(CFont**)((u8*)this + 0x108);
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
        short* singWindow = *reinterpret_cast<short**>((u8*)this + 0x848);
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

	unsigned short press = 0;
	unsigned short hold = 0;
	if (Pad._452_4_ == 0 && Pad._448_4_ == -1) {
		press = Pad._8_2_;
		hold = GetPadHoldMask();
	}

	if (hold == 0) {
		return 0;
	}

	int menuState = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x82c);
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
			*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 10) = 2;
			*reinterpret_cast<short*>(menuState + 0x12) += 1;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			return 0;
		}

		if ((press & 0x100) != 0) {
			if (*selectedFlag == 0) {
				caravanWork->FGPutGil(static_cast<int>(DAT_8032eee0));
				DAT_8032eee0 = 0;
				{
					bool started = false;
					int value = caravanWork->m_gil;
					int div = 10000000;
					for (int i = 0; i < 8; ++i) {
						if (!started && div <= value) {
							started = true;
						}
						if (started || div <= value || i > 6) {
							int digit = value / div;
							if (digit > 9) {
								digit = 9;
							}
							s_place[i] = static_cast<signed char>(digit);
							value -= (value / div) * div;
						} else {
							s_place[i] = -1;
						}
						div /= 10;
					}
				}
				{
					bool started = false;
					int value = 0;
					int div = 10000000;
					for (int i = 0; i < 8; ++i) {
						if (!started && div <= value) {
							started = true;
						}
						if (started || div <= value || i > 6) {
							int digit = value / div;
							if (digit > 9) {
								digit = 9;
							}
							s_place[i + 8] = static_cast<signed char>(digit);
							value -= (value / div) * div;
						} else {
							s_place[i + 8] = -1;
						}
						div /= 10;
					}
				}
			}
			*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 10) = 2;
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
			{
				bool started = false;
				unsigned int value = DAT_8032eee0;
				int div = 10000000;
				for (int i = 0; i < 8; ++i) {
					if (!started && div <= static_cast<int>(value)) {
						started = true;
					}
					if (started || div <= static_cast<int>(value) || i > 6) {
						int digit = static_cast<int>(value) / div;
						if (digit > 9) {
							digit = 9;
						}
						s_place[i + 8] = static_cast<signed char>(digit);
						value -= static_cast<unsigned int>((static_cast<int>(value) / div) * div);
					} else {
						s_place[i + 8] = -1;
					}
					div /= 10;
				}
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}
	} else if ((hold & 4) != 0) {
		if (DAT_8032eee0 == 0) {
			Sound.PlaySe(4, 0x40, 0x7f, 0);
		} else {
			DAT_8032eee0 = (DAT_8032eee0 >= placeValue) ? (DAT_8032eee0 - placeValue) : 0;
			{
				bool started = false;
				unsigned int value = DAT_8032eee0;
				int div = 10000000;
				for (int i = 0; i < 8; ++i) {
					if (!started && div <= static_cast<int>(value)) {
						started = true;
					}
					if (started || div <= static_cast<int>(value) || i > 6) {
						int digit = static_cast<int>(value) / div;
						if (digit > 9) {
							digit = 9;
						}
						s_place[i + 8] = static_cast<signed char>(digit);
						value -= static_cast<unsigned int>((static_cast<int>(value) / div) * div);
					} else {
						s_place[i + 8] = -1;
					}
					div /= 10;
				}
			}
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
				*reinterpret_cast<short*>(*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x848) + 10) = 0;
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
