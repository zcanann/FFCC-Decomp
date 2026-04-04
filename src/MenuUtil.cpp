#include "ffcc/MenuUtil.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include <string.h>
#include "ffcc/fontman.h"
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" void pppDeletePart__8CPartMngFi(void*, int);
extern "C" short BindEffect__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" unsigned int GetSoundMode__9CRedSoundFv(void*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
extern "C" void __dla__FPv(void*);
extern "C" char* strcat(char*, const char*);
extern "C" void MakeAgbString__4CMesFPcPcii(char*, char*, int, int);
extern "C" int drawTagString__4CMesFP5CFontPciii(CFont*, int, int, int, int);
extern "C" const char* GetSkillStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* GetAttrStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" char ChkEquipActive__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void MakeArtItemName__5CGameFPcii(void*, char*, int, int);
extern "C" char s_MenuUtil_cpp_801e37fc[];
extern u32 DAT_801e36d0;
extern u32 DAT_801e36d4;
extern u32 DAT_801e36d8;
extern u32 DAT_801e36dc;
extern float FLOAT_80333654;
extern float FLOAT_80333620;
extern float FLOAT_8033357c;
extern float FLOAT_803335a0;
extern char DAT_80333658[];
extern char DAT_8033365c[];
extern char DAT_80333660[];
extern char DAT_80333664[];
extern char DAT_8033366c[];
extern char DAT_80333670[];
extern char DAT_80333674[];
extern char DAT_8033367c[];
extern char* PTR_s_Strength__80215a48[];
extern char* PTR_s_Defence__80215a4c[];

// Constants defined externally, placed in .sdata2 by the linker.
extern const float kMenuCenteringHalfWidth;
extern const float kOptionAnimMin;
extern const float kOptionAnimMax;
extern const float kMenuCenteringOffset;
extern const float kOptionRowAnimStep;
extern const float kOptionOpenAnimStep;
extern const float kOptionColumnAnimStep;
extern const float kOptionVolumeScale;

namespace {
struct MenuUtilFlatTableEntry {
	int count;
	const char** index;
	char* buffer;
};

struct MenuUtilFlatData {
	char pad[0x6C];
	MenuUtilFlatTableEntry table[8];
};

static inline int* GetMenuHelpMsgTable()
{
	return reinterpret_cast<int*>(reinterpret_cast<MenuUtilFlatData*>(&Game.m_cFlatDataArr[1])->table[6].index);
}
}

static unsigned short GetMenuPress()
{
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		return 0;
	}

	__cntlzw(static_cast<unsigned int>(Pad._448_4_));
	return static_cast<unsigned short>(Pad._8_2_);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcHelpLine(int, int&, int&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetLongHelpString(CFont*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos2(char* text, float scale, float margin)
{
	CFont* font = menuFont;
	float width;

	font->SetShadow(1);
	font->SetMargin(margin);
	font->SetScaleX(scale);
	font->SetScaleY(kOptionAnimMax);
	width = font->GetWidth(text);
	return kMenuCenteringOffset - width * kMenuCenteringHalfWidth;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos(char* text, CFont* font)
{
    float width = font->GetWidth(text);
    return -(width * kMenuCenteringHalfWidth - kMenuCenteringOffset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawFont(int posX, int posY, _GXColor color, int tlut, char* text, float scale, float margin)
{
	CFont* font = menuFont;

	font->SetMargin(margin);
	font->SetShadow(1);
	font->SetScale(scale);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetPosX((float)posX);
	font->SetPosY((float)posY);
	font->Draw(text);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetFontWidth(char*, float, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8017ac40
 * PAL Size: 272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawFont2(int posX, int posY, _GXColor color, int tlut, char* text, float scaleX, float scaleY, float margin)
{
	CFont* font = menuFont;

	font->SetMargin(margin);
	font->SetShadow(1);
	font->SetScaleX(scaleX);
	font->SetScaleY(scaleY);
	font->DrawInit();
	font->SetTlut(tlut);
	font->SetColor(color);
	font->SetPosX((float)posX);
	font->SetPosY((float)posY);
	font->Draw(text);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawHelpMessageUS(int msgNo, CFont* font, int, int, _GXColor color, int tlut, float margin, float scale)
{
    u32 lineBaseY[4];
    lineBaseY[0] = DAT_801e36d0;
    lineBaseY[1] = DAT_801e36d4;
    lineBaseY[2] = DAT_801e36d8;
    lineBaseY[3] = DAT_801e36dc;

    int languageIndex = Game.m_gameWork.m_languageId - 1;
    int lineCount = 3;
    int firstLine = 500;
    int maxWidth = -1;
    int drawPrefix = 1;
    float lineStep = FLOAT_80333654;
    const char* suffix = DAT_80333658;
    char itemName[260];
    char scratch[0x200];
    itemName[0] = '\0';

    font->SetMargin(margin);
    font->SetShadow(1);
    font->SetScale(scale);
    font->DrawInit();
    font->SetTlut(tlut);
    font->SetColor(color);
    font->SetScale(kOptionAnimMax);

    if ((0 <= msgNo) && (msgNo < 0x269)) {
        firstLine = msgNo * 3 + 0x1F5;
    }

    for (int i = 0; i < 3; i++) {
        int msgId = GetMenuHelpMsgTable()[firstLine + i];
        memset(scratch, 0, sizeof(scratch));
        MakeAgbString__4CMesFPcPcii(scratch, reinterpret_cast<char*>(msgId), 0, 1);
        if (strlen(scratch) != 0) {
            int width = drawTagString__4CMesFP5CFontPciii(font, msgId, 0, 0, 0);
            if (maxWidth < width) {
                maxWidth = width;
            }
        }
    }

    if ((msgNo < 0x259) || (0x268 < msgNo)) {
        if (msgNo == 0x209) {
            suffix = GetSkillStr__8CMenuPcsFi(this, 0);
            itemName[0] = '\0';
        } else if (msgNo == 0x20D) {
            suffix = GetSkillStr__8CMenuPcsFi(this, 1);
            itemName[0] = '\0';
        } else if (msgNo == 0x211) {
            suffix = GetSkillStr__8CMenuPcsFi(this, 2);
            itemName[0] = '\0';
        } else {
            MakeArtItemName__5CGameFPcii(&Game, itemName, msgNo, 1);
            if ((itemName[0] != '\0') && (strlen(itemName) != 0) &&
                (itemName[0] >= 'a') && (itemName[0] <= 'z')) {
                itemName[0] = static_cast<char>(itemName[0] - ('a' - 'A'));
            }
        }
        lineStep = FLOAT_80333620;
    } else {
        drawPrefix = 0;
    }

    int rangeKind = 0;
    if ((1 <= msgNo) && (msgNo <= 0x44)) {
        rangeKind = 1;
    } else if ((0x45 <= msgNo) && (msgNo <= 0x7E)) {
        rangeKind = 0x45;
    } else if ((0x7F <= msgNo) && (msgNo <= 0x9E)) {
        rangeKind = 0x7F;
    }

    if (rangeKind == 0) {
        for (int i = 0; i < 3; i++) {
            int msgId = GetMenuHelpMsgTable()[firstLine + i];
            memset(scratch, 0, sizeof(scratch));
            MakeAgbString__4CMesFPcPcii(scratch, reinterpret_cast<char*>(msgId), 0, 1);
            if (strlen(scratch) == 0) {
                lineCount--;
                if (firstLine == firstLine + i) {
                    firstLine++;
                }
            }
        }

        u32 y = lineBaseY[lineCount + drawPrefix - 1];
        if (drawPrefix != 0) {
            font->SetPosX(FLOAT_8033357c);
            font->SetPosY(static_cast<float>(y));
            font->Draw(itemName);
            font->Draw(suffix);
            y = static_cast<u32>(static_cast<float>(y) + lineStep);
        }

        for (int i = 0; i < lineCount; i++) {
            int x = 0x140 - maxWidth / 2;
            int msgId = GetMenuHelpMsgTable()[firstLine + i];
            font->SetPosX(static_cast<float>(x));
            font->SetPosY(static_cast<float>(y));
            drawTagString__4CMesFP5CFontPciii(font, msgId, 1, 0, 0);
            y = static_cast<u32>(static_cast<float>(y) + lineStep);
        }
        return;
    }

    u32 y = lineBaseY[drawPrefix + 2];
    if (drawPrefix != 0) {
        font->SetPosX(FLOAT_8033357c);
        font->SetPosY(static_cast<float>(y));
        font->Draw(itemName);
        font->Draw(suffix);
        y = static_cast<u32>(static_cast<float>(y) + lineStep);
    }

    for (int i = 0; i < 3; i++) {
        int x = 0x140 - maxWidth / 2;
        int msgId = GetMenuHelpMsgTable()[firstLine + i];
        font->SetPosX(static_cast<float>(x));
        font->SetPosY(static_cast<float>(y));
        drawTagString__4CMesFP5CFontPciii(font, msgId, 1, 0, 0);
        y = static_cast<u32>(static_cast<float>(y) + lineStep);
    }

    int itemBase = Game.unkCFlatData0[2] + msgNo * 0x48;
    u16 flags = *reinterpret_cast<u16*>(itemBase + 4);
    const char* bonusLabel = DAT_80333658;
    if ((flags & 0x100) != 0) {
        bonusLabel = PTR_s_Strength__80215a48[languageIndex];
    } else if ((flags & 0xE00) != 0) {
        bonusLabel = PTR_s_Defence__80215a4c[languageIndex];
    }

    font->SetPosX(FLOAT_8033357c);
    font->SetPosY(static_cast<float>(y));

    if ((flags & 0x1000) == 0) {
        strcpy(scratch, bonusLabel);
        strcat(scratch, DAT_8033366c);
        font->Draw(scratch);

        float x = FLOAT_8033357c + font->GetWidth(scratch) + FLOAT_803335a0;
        font->SetTlut(1);
        font->SetPosX(x);
        sprintf(scratch, DAT_80333670, *reinterpret_cast<u16*>(itemBase + 6));
        font->Draw(scratch);

        float markerX = FLOAT_8033357c + font->GetWidth(DAT_8033366c);
        font->SetPosX(markerX);
        u16 attr = *reinterpret_cast<u16*>(itemBase + 8);
        if ((attr != 0) && (attr < 0x14)) {
            font->SetTlut(4);
            strcpy(scratch, GetAttrStr__8CMenuPcsFi(this, attr));
            font->Draw(scratch);
            font->SetTlut(9);
            if (attr < 9) {
                sprintf(scratch, DAT_8033367c, DAT_80333660);
                font->Draw(scratch);
            }
        }
    } else {
        u16 attr = *reinterpret_cast<u16*>(itemBase + 8);
        if ((attr != 0) && (attr < 0x14)) {
            font->SetTlut(4);
            strcpy(scratch, GetAttrStr__8CMenuPcsFi(this, attr));
            font->Draw(scratch);
            float x = FLOAT_8033357c + font->GetWidth(scratch) + FLOAT_803335a0;
            font->SetPosX(x);
            font->SetTlut(9);
            if (attr < 9) {
                sprintf(scratch, DAT_8033365c, DAT_80333660);
            } else if ((attr == 0xB) || (attr == 0x11) || (attr == 0x12)) {
                sprintf(scratch, DAT_80333664, 0x2B, *reinterpret_cast<u16*>(itemBase + 6));
            } else if (((9 <= attr) && (attr <= 0xA)) || (attr == 0xC)) {
                sprintf(scratch, DAT_80333664, 0x2D, *reinterpret_cast<u16*>(itemBase + 6));
                font->SetTlut(3);
            } else {
                return;
            }
            font->Draw(scratch);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma dont_inline on
void CMenuPcs::DrawHelpMessage(int msgNo, CFont* font, int posX, int posY, _GXColor color, int tlut, float margin, float scaleY)
{
	if (msgNo >= 0) {
		DrawHelpMessageUS(msgNo, font, posX, posY, color, tlut, margin, scaleY);
	}
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::IsItemEquip(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80179e9c
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetCrystalCageAttr()
{
	struct CrystalState {
		unsigned char _pad0[0x80];
		unsigned char m_effectTimer;
		unsigned char _pad1[3];
		int m_crystalElem;
		short m_crystalPart;
		short m_crystalAttr;
	};

	CrystalState* state = reinterpret_cast<CrystalState*>(this);

	if (state->m_crystalPart != -1) {
		pppDeletePart__8CPartMngFi(&PartMng, state->m_crystalPart);
	}

	unsigned int chaliceElement = Game.m_gameWork.m_chaliceElement;
	if ((chaliceElement & 1U) != 0) {
		state->m_crystalAttr = 0xE;
		state->m_crystalElem = 1;
	} else if ((chaliceElement & 2U) != 0) {
		state->m_crystalAttr = 0xF;
		state->m_crystalElem = 2;
	} else if ((chaliceElement & 4U) != 0) {
		state->m_crystalAttr = 0x10;
		state->m_crystalElem = 4;
	} else if ((chaliceElement & 8U) != 0) {
		state->m_crystalAttr = 0x11;
		state->m_crystalElem = 8;
	} else if ((chaliceElement & 0x10U) != 0) {
		state->m_crystalAttr = 0x12;
		state->m_crystalElem = 0x10;
	}

	state->m_crystalPart = BindEffect(5, state->m_crystalAttr, -1);
	state->m_effectTimer = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80179e28
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetManaWaterEffect()
{
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
	int partNo = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x840) + 0x19B8);

	if (partNo != -1) {
		pppDeletePart__8CPartMngFi(&PartMng, partNo);
	}

	BindEffect__8CMenuPcsFiii(this, 5, Game.m_gameWork.m_timerA + 0x13, -1);
	*reinterpret_cast<int*>(self + 0x70) = Game.m_gameWork.m_timerA;
}

/*
 * --INFO--
 * PAL Address: 0x80179d28
 * PAL Size: 256b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetOptionData()
{
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
	signed char& gameInitMode = *reinterpret_cast<signed char*>(self + 0x8F);
	signed char& stereoMode = *reinterpret_cast<signed char*>(self + 0x90);
	signed char& bgmVolume = *reinterpret_cast<signed char*>(self + 0x91);
	signed char& seVolume = *reinterpret_cast<signed char*>(self + 0x92);
	signed char* const specialModeFlags = reinterpret_cast<signed char*>(self + 0xB5);

	gameInitMode =
	    static_cast<signed char>(static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(Game.m_gameWork.m_gameInitFlag))) >> 5);

	unsigned int soundMode = GetSoundMode__9CRedSoundFv(reinterpret_cast<unsigned char*>(&Sound) + 8);
	unsigned int soundModeClz = static_cast<unsigned int>(__cntlzw(soundMode));
	stereoMode = static_cast<signed char>(static_cast<unsigned int>(__cntlzw(soundModeClz >> 5)) >> 5);

	int value = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Sound) + 0x22B0);
	value = value / 10 + (value >> 31);
	bgmVolume = static_cast<signed char>(value - (value >> 31));

	value = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Sound) + 0x22B4);
	value = value / 10 + (value >> 31);
	seVolume = static_cast<signed char>(value - (value >> 31));

	unsigned int flag = Game.m_gameWork.m_spModeFlags[0];
	specialModeFlags[0] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.m_gameWork.m_spModeFlags[1];
	specialModeFlags[1] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.m_gameWork.m_spModeFlags[2];
	specialModeFlags[2] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.m_gameWork.m_spModeFlags[3];
	specialModeFlags[3] = static_cast<signed char>((-flag | flag) >> 31);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::InitOptionMenuParam()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80179328
 * PAL Size: 2560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcOptionMenu()
{
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
	bool optionChanged = false;

	const float minValue = kOptionAnimMin;
	const float maxValue = kOptionAnimMax;
	const float animStep = kOptionRowAnimStep;
	const float animStep2 = kOptionColumnAnimStep;
	const unsigned short press = GetMenuPress();

	signed char& menuState = *reinterpret_cast<signed char*>(self + 0x9C);
	float& openAnim = *reinterpret_cast<float*>(self + 0x98);
	float& rowAnim = *reinterpret_cast<float*>(self + 0xA0);
	float& colAnim = *reinterpret_cast<float*>(self + 0xA8);
	signed char& animPhase = *reinterpret_cast<signed char*>(self + 0xA4);
	signed char& animCounter = *reinterpret_cast<signed char*>(self + 0xAC);
	signed char& optionIndex = *reinterpret_cast<signed char*>(self + 0x8E);
	signed char& gameInitMode = *reinterpret_cast<signed char*>(self + 0x8F);
	signed char& stereoMode = *reinterpret_cast<signed char*>(self + 0x90);
	signed char& bgmVolume = *reinterpret_cast<signed char*>(self + 0x91);
	signed char& seVolume = *reinterpret_cast<signed char*>(self + 0x92);
	signed char& leftHintTimer = *reinterpret_cast<signed char*>(self + 0x93);
	signed char& rightHintTimer = *reinterpret_cast<signed char*>(self + 0x94);
	int& specialModeEdit = *reinterpret_cast<int*>(self + 0xB0);
	signed char& specialModeCursor = *reinterpret_cast<signed char*>(self + 0xB4);
	signed char* const specialModeFlags = reinterpret_cast<signed char*>(self + 0xB5);

	if (menuState == 0) {
		openAnim += kOptionOpenAnimStep;
		if (openAnim < maxValue) {
			return;
		}

		menuState = 1;
		openAnim = maxValue;
		return;
	}

	if (menuState == 2) {
		openAnim -= kOptionOpenAnimStep;
		rowAnim -= animStep;
		colAnim -= animStep2;

		if (rowAnim <= minValue) {
			rowAnim = minValue;
		}
		if (colAnim <= minValue) {
			colAnim = minValue;
		}
		if (static_cast<int>(openAnim / kOptionOpenAnimStep) == 5) {
			Sound.PlaySe(0x32, 0x40, 0x7F, 0);
		}
		if (openAnim > minValue) {
			return;
		}

		*reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(self + 0x82C) + 0x20) = 1;
		optionIndex = 0;
		menuState = 0;
		openAnim = minValue;
		rowAnim = minValue;
		colAnim = minValue;
		animCounter = 0;
		animPhase = 0;
		return;
	}

	if (menuState == 3) {
		return;
	}

	if (animPhase == 0) {
		rowAnim += animStep;
		animCounter++;
		if (rowAnim >= maxValue) {
			animPhase = 1;
			rowAnim = maxValue;
		}
	} else if (animPhase == 1) {
		colAnim += animStep2;
		if (colAnim >= maxValue) {
			animPhase = 2;
			colAnim = maxValue;
		}
	}

	if (leftHintTimer > 0) {
		leftHintTimer--;
	}
	if (rightHintTimer > 0) {
		rightHintTimer--;
	}

	if ((specialModeEdit == 0) && ((press & 8) != 0)) {
		leftHintTimer = 0;
		rightHintTimer = 0;
		optionIndex--;
		if (optionIndex < 0) {
			optionIndex = 4;
		}
		rowAnim = minValue;
		colAnim = minValue;
		animCounter = 0;
		animPhase = 0;
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	} else if ((specialModeEdit == 0) && ((press & 4) != 0)) {
		leftHintTimer = 0;
		rightHintTimer = 0;
		optionIndex++;
		if (optionIndex > 4) {
			optionIndex = 0;
		}
		rowAnim = minValue;
		colAnim = minValue;
		animCounter = 0;
		animPhase = 0;
		Sound.PlaySe(1, 0x40, 0x7F, 0);
	}

	if (specialModeEdit == 0) {
		const unsigned short press2 = GetMenuPress();
		if ((press2 & 0x200) != 0) {
			menuState = 2;
			Sound.PlaySe(3, 0x40, 0x7F, 0);
			return;
		}
	}

	if ((animPhase == 0) || (animPhase == 1)) {
		return;
	}

	if ((press & 1) != 0) {
		if (optionIndex == 2) {
			leftHintTimer = 3;
			rightHintTimer = 0;
			bgmVolume--;
			if (bgmVolume < 0) {
				bgmVolume = 0;
			}
		} else if (optionIndex < 2) {
			if (optionIndex == 0) {
				gameInitMode--;
				if (gameInitMode < 0) {
					gameInitMode = 1;
				}
			} else if (optionIndex == 1) {
				stereoMode--;
				if (stereoMode < 0) {
					stereoMode = 1;
				}
			}
		} else if (optionIndex == 4) {
			if (specialModeEdit != 0) {
				specialModeFlags[static_cast<signed char>(specialModeCursor)]--;
				if (specialModeFlags[static_cast<signed char>(specialModeCursor)] < 0) {
					specialModeFlags[static_cast<signed char>(specialModeCursor)] = 1;
				}
			}
		} else if (optionIndex == 3) {
			leftHintTimer = 3;
			rightHintTimer = 0;
			seVolume--;
			if (seVolume < 0) {
				seVolume = 0;
			}
		}

		Sound.PlaySe(1, 0x40, 0x7F, 0);
		optionChanged = true;
	} else if ((press & 2) != 0) {
		if (optionIndex == 2) {
			rightHintTimer = 3;
			leftHintTimer = 0;
			bgmVolume++;
			if (bgmVolume > 0xC) {
				bgmVolume = 0xC;
			}
		} else if (optionIndex < 2) {
			if (optionIndex == 0) {
				gameInitMode++;
				if (gameInitMode > 1) {
					gameInitMode = 0;
				}
			} else if (optionIndex == 1) {
				stereoMode++;
				if (stereoMode > 1) {
					stereoMode = 0;
				}
			}
		} else if (optionIndex == 4) {
			if (specialModeEdit != 0) {
				specialModeFlags[static_cast<signed char>(specialModeCursor)]++;
				if (specialModeFlags[static_cast<signed char>(specialModeCursor)] > 1) {
					specialModeFlags[static_cast<signed char>(specialModeCursor)] = 0;
				}
			}
		} else if (optionIndex == 3) {
			rightHintTimer = 3;
			leftHintTimer = 0;
			seVolume++;
			if (seVolume > 0xC) {
				seVolume = 0xC;
			}
		}

		Sound.PlaySe(1, 0x40, 0x7F, 0);
		optionChanged = true;
	}

	if (optionIndex == 4) {
		const unsigned short press3 = GetMenuPress();
		if ((press3 & 0x100) != 0) {
			if (specialModeEdit == 0) {
				specialModeCursor = 0;
				specialModeEdit = 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
			}
		} else if (specialModeEdit != 0) {
			const unsigned short press4 = GetMenuPress();
			if ((press4 & 0x200) != 0) {
				specialModeCursor = 0;
				specialModeEdit = 0;
				Sound.PlaySe(3, 0x40, 0x7F, 0);

				Game.m_gameWork.m_spModeFlags[0] = static_cast<unsigned char>(specialModeFlags[0]);
				Game.m_gameWork.m_spModeFlags[1] = static_cast<unsigned char>(specialModeFlags[1]);
				Game.m_gameWork.m_spModeFlags[2] = static_cast<unsigned char>(specialModeFlags[2]);
				Game.m_gameWork.m_spModeFlags[3] = static_cast<unsigned char>(specialModeFlags[3]);
			} else if ((press & 8) != 0) {
				specialModeCursor--;
				if (specialModeCursor < 0) {
					specialModeCursor = 3;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else if ((press & 4) != 0) {
				specialModeCursor++;
				if (specialModeCursor > 3) {
					specialModeCursor = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}
	}

	if (optionChanged) {
		Game.m_gameWork.m_gameInitFlag = static_cast<unsigned char>(gameInitMode == 0);
		Sound.SetStereo(stereoMode == 0);
		Sound.SetSeMasterVolume(static_cast<int>(kOptionVolumeScale * static_cast<float>(seVolume)));
		Sound.SetBgmMasterVolume(static_cast<int>(kOptionVolumeScale * static_cast<float>(bgmVolume)));
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawOptionMenu()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8017683c
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::BindMcObj(int slotNo)
{
	unsigned char* const self = reinterpret_cast<unsigned char*>(this);
	int slot = 0;

	do {
		if (slotNo == slot) {
			int* obj = reinterpret_cast<int*>(
				*reinterpret_cast<unsigned char**>(self + 0x840) + (slot + 0x11) * 0x524);

			if (obj[1] >= 0) {
				pppDeletePart__8CPartMngFi(&PartMng, obj[1]);
				obj[1] = -1;
				obj[2] = -1;
				obj[0] = -1;
			}

			if (obj[0x525] >= 0) {
				pppDeletePart__8CPartMngFi(&PartMng, obj[0x525]);
				obj[0x525] = -1;
				obj[0x526] = -1;
				obj[0x524] = -1;
			}
		}

		slot++;
	} while (slot < 4);

	slot = 0;
	int entryOffset = 0;
	do {
		if (slotNo == slot) {
			unsigned char* entry = *reinterpret_cast<unsigned char**>(self + 0x838) + entryOffset;
			int iconType = *reinterpret_cast<int*>(entry + 0xC);

			if (iconType != 0) {
				BindEffect__8CMenuPcsFiii(this, slot + 0x11, iconType + 0x16, -1);
			}

			unsigned int flags = *reinterpret_cast<unsigned int*>(entry + 0x28);
			int markType = iconType;

			if ((flags & 1) != 0) {
				markType = 0;
			} else if ((flags & 2) != 0) {
				markType = 1;
			} else if ((flags & 4) != 0) {
				markType = 2;
			} else if ((flags & 8) != 0) {
				markType = 3;
			} else if ((flags & 0x10) != 0) {
				markType = 4;
			}

			BindEffect__8CMenuPcsFiii(this, slot + 0x11, markType + 0x1A, -1);
		}

		slot++;
		entryOffset += 0x48;
	} while (slot < 4);
}
