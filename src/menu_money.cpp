#include "ffcc/menu_money.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"

#include <string.h>

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
	// Set blend mode for rendering
	// _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	// SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);
	
	short sVar1 = *(short *)(*(int *)((char*)this + 0x82c) + 0x10);
	short sVar2 = *(short *)(*(int *)((char*)this + 0x82c) + 0x30);
	short *psVar6 = (short *)(*(int *)((char*)this + 0x850) + 8);
	
	// Draw UI elements
	for (int iVar7 = 0; iVar7 < **(short**)((char*)this + 0x850); iVar7++) {
		if (-1 < *(int *)(psVar6 + 0xe)) {
			// SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, *(int *)(psVar6 + 0xe));
			
			// Calculate positions and render rectangle
			float dVar14 = (float)*psVar6;
			float dVar13 = (float)psVar6[1];
			float dVar15 = (float)psVar6[2];
			float dVar16 = (float)psVar6[3];
			float dVar11 = *(float *)(psVar6 + 4);
			float dVar12 = *(float *)(psVar6 + 6);
			
			// Set material color
			int local_cc = 0xffffffff;
			// GXSetChanMatColor(4, &local_cc);
			
			// DrawRect__8CMenuPcsFUlfffffffff(
			//	dVar14, dVar13, dVar15, dVar16, dVar11, dVar12, 
			//	(float)*(float *)(psVar6 + 10), (float)*(float *)(psVar6 + 10), 
			//	&MenuPcs, 0);
		}
		psVar6 = psVar6 + 0x20;
	}
	
	// Draw money digits
	// SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x5d);
	
	// Draw cursor if in selection mode
	if ((sVar2 == 0) && (sVar1 == 1)) {
		// SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x48);
		
		// Draw cursor rectangle
		short *psVar6_cursor = (short *)(*(int *)((char*)this + 0x850) + 8);
		float cursorX = (float)*psVar6_cursor + (7 - *(short *)(*(int *)((char*)this + 0x82c) + 0x26)) * 18 + 36;
		float cursorY = (float)*(short *)(*(int *)((char*)this + 0x850) + 10) + 92;
		
		// DrawRect__8CMenuPcsFUlfffffffff(
		//	cursorX, cursorY, 24.0f, 18.0f, 0.0f, 0.0f, 1.0f, 1.0f, &MenuPcs, 0);
	}
	
	// Draw text elements
	void *font = *(void **)((char*)this + 0x108);
	// SetMargin__5CFontFf(1.0f, font);
	// SetShadow__5CFontFi(font, 0);
	// SetScale__5CFontFf(1.0f, font);
	// DrawInit__5CFontFv(font);
	
	int local_dc = 0xffffffff;
	// SetColor__5CFontF8_GXColor(font, &local_dc);
	
	void *uVar3 = 0; // GetMenuStr__8CMenuPcsFi(this, 0x15);
	// SetPosX__5CFontFf(100.0f, font);
	// SetPosY__5CFontFf(50.0f, font);
	// Draw__5CFontFPc(font, uVar3);
	
	// DrawInit__8CMenuPcsFv(this);
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
