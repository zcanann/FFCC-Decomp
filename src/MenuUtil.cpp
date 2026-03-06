#include "ffcc/MenuUtil.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"

extern "C" float GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScaleX__5CFontFf(float, CFont*);
extern "C" void SetScaleY__5CFontFf(float, CFont*);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetTlut__5CFontFi(CFont*, int);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, _GXColor*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);
extern "C" void pppDeletePart__8CPartMngFi(void*, int);
extern "C" short BindEffect__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" unsigned int GetSoundMode__9CRedSoundFv(void*);
extern unsigned char PartMng[];

extern float kMenuCenteringHalfWidth;
extern float kOptionAnimMin;
extern float kOptionAnimMax;
extern float kMenuCenteringOffset;
extern float kOptionRowAnimStep;
extern double lbl_80333640;
extern float kOptionOpenAnimStep;
extern float kOptionColumnAnimStep;
extern float kOptionVolumeScale;

extern "C" int __cntlzw(unsigned int);

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
float CMenuPcs::CalcCenteringPos2(char* text, float margin, float scale)
{
	CFont* font = menuFont;

	SetShadow__5CFontFi(font, 1);
	SetMargin__5CFontFf(margin, font);
	SetScaleX__5CFontFf(scale, font);
	SetScaleY__5CFontFf(kOptionAnimMax, font);
	return -(GetWidth__5CFontFPc(font, text) * kMenuCenteringHalfWidth - kMenuCenteringOffset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CMenuPcs::CalcCenteringPos(char* text, CFont* font)
{
    float width = GetWidth__5CFontFPc(font, text);
    return -(width * kMenuCenteringHalfWidth - kMenuCenteringOffset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawFont(int posX, int posY, _GXColor color, int tlut, char* text, float margin, float scale)
{
	CFont* font = menuFont;

	SetMargin__5CFontFf(margin, font);
	SetShadow__5CFontFi(font, 1);
	SetScale__5CFontFf(scale, font);
	DrawInit__5CFontFv(font);
	SetTlut__5CFontFi(font, tlut);
	SetColor__5CFontF8_GXColor(font, &color);
	SetPosX__5CFontFf((float)posX, font);
	SetPosY__5CFontFf((float)posY, font);
	Draw__5CFontFPc(font, text);
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
void CMenuPcs::DrawFont2(int posX, int posY, _GXColor color, int tlut, char* text, float margin, float scaleX, float scaleY)
{
	CFont* font = menuFont;

	SetMargin__5CFontFf(margin, font);
	SetShadow__5CFontFi(font, 1);
	SetScaleX__5CFontFf(scaleX, font);
	SetScaleY__5CFontFf(scaleY, font);
	DrawInit__5CFontFv(font);
	SetTlut__5CFontFi(font, tlut);
	SetColor__5CFontF8_GXColor(font, &color);
	SetPosX__5CFontFf((float)posX, font);
	SetPosY__5CFontFf((float)posY, font);
	Draw__5CFontFPc(font, text);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawHelpMessageUS(int, CFont*, int, int, _GXColor, int, float, float)
{
	// TODO
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
		int m_effectTimer;
		int m_crystalElem;
		short m_crystalPart;
		short m_crystalAttr;
	};

	CrystalState* state = reinterpret_cast<CrystalState*>(this);

	if (state->m_crystalPart != -1) {
		pppDeletePart__8CPartMngFi(PartMng, state->m_crystalPart);
	}

	unsigned int chaliceElement = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&Game) + 0x10CC);
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

	state->m_crystalPart = BindEffect__8CMenuPcsFiii(this, 5, state->m_crystalAttr, -1);
	*reinterpret_cast<volatile int*>(&state->m_effectTimer) = 0;
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
		pppDeletePart__8CPartMngFi(PartMng, partNo);
	}

	BindEffect__8CMenuPcsFiii(this, 5, Game.game.m_gameWork.m_timerA + 0x13, -1);
	*reinterpret_cast<int*>(self + 0x70) = Game.game.m_gameWork.m_timerA;
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
	    static_cast<signed char>(static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(Game.game.m_gameWork.m_gameInitFlag))) >> 5);

	unsigned int soundMode = GetSoundMode__9CRedSoundFv(reinterpret_cast<unsigned char*>(&Sound) + 8);
	unsigned int soundModeClz = static_cast<unsigned int>(__cntlzw(soundMode));
	stereoMode = static_cast<signed char>(static_cast<unsigned int>(__cntlzw(soundModeClz >> 5)) >> 5);

	int value = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Sound) + 0x22B0);
	value = value / 10 + (value >> 31);
	bgmVolume = static_cast<signed char>(value - (value >> 31));

	value = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(&Sound) + 0x22B4);
	value = value / 10 + (value >> 31);
	seVolume = static_cast<signed char>(value - (value >> 31));

	unsigned int flag = Game.game.m_gameWork.m_spModeFlags[0];
	specialModeFlags[0] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.game.m_gameWork.m_spModeFlags[1];
	specialModeFlags[1] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.game.m_gameWork.m_spModeFlags[2];
	specialModeFlags[2] = static_cast<signed char>((-flag | flag) >> 31);
	flag = Game.game.m_gameWork.m_spModeFlags[3];
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

				Game.game.m_gameWork.m_spModeFlags[0] = static_cast<unsigned char>(specialModeFlags[0]);
				Game.game.m_gameWork.m_spModeFlags[1] = static_cast<unsigned char>(specialModeFlags[1]);
				Game.game.m_gameWork.m_spModeFlags[2] = static_cast<unsigned char>(specialModeFlags[2]);
				Game.game.m_gameWork.m_spModeFlags[3] = static_cast<unsigned char>(specialModeFlags[3]);
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
		Game.game.m_gameWork.m_gameInitFlag = static_cast<unsigned char>(gameInitMode == 0);
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
				pppDeletePart__8CPartMngFi(PartMng, obj[1]);
				obj[1] = -1;
				obj[2] = -1;
				obj[0] = -1;
			}

			if (obj[0x525] >= 0) {
				pppDeletePart__8CPartMngFi(PartMng, obj[0x525]);
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
