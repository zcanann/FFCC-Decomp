#include "ffcc/menu_money.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gobjwork.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"

#include <string.h>

typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

extern "C" const float FLOAT_80332f60 = 255.0f;
extern "C" const float FLOAT_80332f64 = 0.0f;
extern "C" const float FLOAT_80332f68 = 32.0f;
extern "C" const float FLOAT_80332f6c = 24.0f;
extern "C" const float FLOAT_80332f70 = 1.0f;
extern "C" const float FLOAT_80332f74 = 18.0f;
extern "C" const float FLOAT_80332f78 = 16.0f;
extern "C" const float FLOAT_80332f7c = 0.9f;
extern "C" const float FLOAT_80332f80 = 19.8f;
extern "C" const float FLOAT_80332f84 = 4.0f;
extern "C" const double DOUBLE_80332F90 = 1.0;
extern "C" const double DOUBLE_80332F98 = 216.0;
extern "C" const double DOUBLE_80332FA0 = 0.5;
unsigned int s_Money = 0;
signed char s_place[16];

static inline float LoadFloat(const float& value)
{
	return value;
}

static inline double LoadDouble(const double& value)
{
	return value;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::MoneySetPlace(int row)
{
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	int gil;
	if (row == 0) {
		gil = caravanWork->m_gil;
	} else {
		gil = s_Money;
	}

	signed char* place = s_place + row * 8;
	int digitPlace = 10000000;
	int digitIndex = 0;
	int digitCount = 8;
	bool started = false;

	do {
		if ((!started) && (digitPlace <= gil)) {
			started = true;
		}
		if (((started) || (digitPlace <= gil)) || (digitIndex == 7)) {
			int digit = gil / digitPlace;
			if (9 < digit) {
				digit = 9;
			}
			*place = static_cast<signed char>(digit);
			gil = gil - (gil / digitPlace) * digitPlace;
		} else {
			*place = -1;
		}
		place++;
		digitIndex++;
		digitPlace /= 10;
		digitCount--;
	} while (digitCount != 0);
}

STATIC_ASSERT(offsetof(CMenuPcs, moneyFont) == 0x108);
STATIC_ASSERT(offsetof(CMenuPcs, moneyState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, singWindowInfo) == 0x848);
STATIC_ASSERT(offsetof(CMenuPcs, moneyPanel) == 0x850);
STATIC_ASSERT(offsetof(MoneyMenuState, messageMask) == 0x9);
STATIC_ASSERT(offsetof(MoneyMenuState, initialized) == 0xB);
STATIC_ASSERT(offsetof(MoneyMenuState, closeRequested) == 0xD);
STATIC_ASSERT(offsetof(MoneyMenuState, listState) == 0x10);
STATIC_ASSERT(offsetof(MoneyMenuState, optionState) == 0x12);
STATIC_ASSERT(offsetof(MoneyMenuState, moveDirection) == 0x1E);
STATIC_ASSERT(offsetof(MoneyMenuState, frame) == 0x22);
STATIC_ASSERT(offsetof(MoneyMenuState, selectedIndex) == 0x26);
STATIC_ASSERT(offsetof(MoneyMenuState, subMenuIndex) == 0x28);
STATIC_ASSERT(offsetof(MoneyMenuState, mode) == 0x30);
STATIC_ASSERT(offsetof(MoneyMenuState, prevMode) == 0x32);
STATIC_ASSERT(offsetof(MoneyMenuAnim, u) == 0x8);
STATIC_ASSERT(offsetof(MoneyMenuAnim, v) == 0xC);
STATIC_ASSERT(offsetof(MoneyMenuAnim, alpha) == 0x10);
STATIC_ASSERT(offsetof(MoneyMenuAnim, uvScale) == 0x14);
STATIC_ASSERT(offsetof(MoneyMenuAnim, unk18) == 0x18);
STATIC_ASSERT(offsetof(MoneyMenuAnim, tex) == 0x1C);
STATIC_ASSERT(offsetof(MoneyMenuAnim, frame) == 0x20);
STATIC_ASSERT(offsetof(MoneyMenuAnim, startFrame) == 0x24);
STATIC_ASSERT(offsetof(MoneyMenuAnim, duration) == 0x28);
STATIC_ASSERT(offsetof(MoneyMenuAnim, flags) == 0x2C);
STATIC_ASSERT(offsetof(MoneyMenuAnim, dx) == 0x30);
STATIC_ASSERT(offsetof(MoneyMenuAnim, dy) == 0x34);
STATIC_ASSERT(offsetof(MoneyMenuAnim, targetX) == 0x38);
STATIC_ASSERT(offsetof(MoneyMenuAnim, targetY) == 0x3C);
STATIC_ASSERT(sizeof(MoneyMenuAnim) == 0x40);
STATIC_ASSERT(sizeof(MoneyMenuAnimList) == 0x1008);

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
	bool blocked;
	unsigned int press;
	unsigned int hold;

	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		press = Pad.GetPadInputs()[padIndex].buttonDown[0];
	}

	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		hold = Pad.GetPadInputs()[padIndex].repeatButton;
	}

	if (hold == 0) {
		return 0;
	}

	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	int menuState = (int)this->moneyState;
	int mode = (int)*(s16*)(menuState + 0x30);
	int optBase = menuState + mode * 2;
	int maxDigits = 1;
	int maxGil = caravanWork->m_gil;
	int digitPlace = 10;

	while (maxDigits < 8) {
		if (0 < maxGil / digitPlace) {
			digitPlace *= 10;
			maxDigits++;
		} else {
			break;
		}
	}
	int attachFlag = SingGetLetterAttachflg();

	if (mode == 0) {
		unsigned int cursor = *(s16*)(optBase + 0x26);
		unsigned int placeValue = 1;
		while (cursor != 0) {
			placeValue *= 10;
			cursor--;
		}

		if ((hold & 8) != 0) {
			if (caravanWork->m_gil == 0) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			} else {
				unsigned int gil = s_Money + placeValue;
				if ((unsigned int)caravanWork->m_gil < gil) {
					gil = 0;
				}
				s_Money = gil;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
				gil = s_Money;

				MoneySetPlace(1);
			}
		} else {
			if ((hold & 4) != 0) {
				unsigned int gil = caravanWork->m_gil;
				if (gil == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (-1 < (int)(s_Money - placeValue)) {
						gil = s_Money - placeValue;
					}
					s_Money = gil;
					MoneySetPlace(1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
		}

		if ((hold & 1) != 0) {
			if (*(s16*)(optBase + 0x26) < maxDigits - 1) {
				*(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) + 1;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		} else {
			if ((hold & 2) != 0) {
				if (*(s16*)(optBase + 0x26) == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					*(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) - 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
		}

		if ((hold & 0xF) == 0) {
			if ((press & 0x20) != 0) {
				if (attachFlag < 0) {
					*(s16*)(menuState + 0x1E) = 1;
					Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
					return 1;
				}
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			} else if ((press & 0x40) != 0) {
				if (attachFlag < 0) {
					*(s16*)(menuState + 0x1E) = -1;
					Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
					return 1;
				}
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			} else if ((press & 0x100) != 0) {
				if (s_Money < 1) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (-1 < attachFlag) {
						LetterSetAttachItem(s_Money, 1);
						Sound.PlaySe(2, 0x40, 0x7F, 0);
						return 1;
					}
					s16 winW;
					s16 winH;
					this->moneyState->messageMask = 2;
					if (caravanWork->CanPlayerPutItem() != 0) {
						this->moneyState->messageMask = this->moneyState->messageMask | 1;
					}
					GetSingWinSize(1, &winW, &winH, 0);
					SetSingWinInfo(0xF0, 0xD0, winW, winH);
					this->singWindowInfo[5] = 0;
					*(s16*)(menuState + 0x12) = 0;
					*(s16*)(menuState + 0x30) = 1;
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			} else if ((press & 0x200) != 0) {
				if (attachFlag < 0) {
					*(u8*)(menuState + 0xD) = 1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
					return 1;
				}
				LetterSetAttachItem(0, 0xFFFFFFFF);
				Sound.PlaySe(3, 0x40, 0x7F, 0);
				return 1;
			}
		}
	} else {
		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				if (*(s16*)(optBase + 0x26) < 1) {
					*(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) + 1;
				} else {
					*(s16*)(optBase + 0x26) = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		} else {
			if (*(s16*)(optBase + 0x26) == 0) {
				*(s16*)(optBase + 0x26) = 1;
			} else {
				*(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x100) != 0) {
				if (((int)this->moneyState->messageMask & (1 << *(s16*)(optBase + 0x26))) == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (*(s16*)(optBase + 0x26) == 0) {
						caravanWork->FGPutGil(static_cast<int>(s_Money));
						s_Money = 0;
						MoneySetPlace(0);
						MoneySetPlace(1);
					}
					this->singWindowInfo[5] = 2;
					*(s16*)(menuState + 0x12) = *(s16*)(menuState + 0x12) + 1;
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			} else if ((press & 0x200) != 0) {
				this->singWindowInfo[5] = 2;
				*(s16*)(menuState + 0x12) = *(s16*)(menuState + 0x12) + 1;
				Sound.PlaySe(3, 0x40, 0x7F, 0);
			}
		}
	}

	return 0;
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
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	s16 selectionState = this->moneyState->listState;
	s16 mode = this->moneyState->mode;
	MoneyMenuAnim* entry = this->moneyPanel->anims;

	for (int i = 0; i < this->moneyPanel->count; i++, entry++) {
		int tex = entry->tex;
		if (tex < 0) {
			continue;
		}

		float x = (float)entry->x;
		float y = (float)entry->y;
		float w = (float)entry->w;
		float h = (float)entry->h;
		float u = entry->u;
		float v = entry->v;
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = (u8)(FLOAT_80332f60 * entry->alpha);
		GXSetChanMatColor(GX_COLOR0A0, color);
		float uvScale = entry->uvScale;
		MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, FLOAT_80332f64);
	}

	MoneyMenuAnim* drawBase = this->moneyPanel->anims;
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x5D));
	{
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = (u8)(FLOAT_80332f60 * drawBase->alpha);
		GXSetChanMatColor(GX_COLOR0A0, color);
	}

	for (int i = 0; i < 2; i++) {
		float y = (float)(drawBase->y + 0x18) + FLOAT_80332f68 * (float)i;
		float x = (float)(drawBase->x + 0x20);
		for (int j = 0; j < 8; j++) {
			signed char digit = s_place[i * 8 + j];
			if (digit >= 0) {
				MenuPcs.DrawRect(0, x, y, FLOAT_80332f6c, FLOAT_80332f68,
				                 FLOAT_80332f6c * (float)digit, FLOAT_80332f68 * (float)i,
				                 FLOAT_80332f70, FLOAT_80332f70, FLOAT_80332f64);
			}
			x += FLOAT_80332f74;
		}
	}

	if ((mode == 0) && (selectionState == 1)) {
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x48));
		{
			GXColor color;
			color.r = 0xFF;
			color.g = 0xFF;
			color.b = 0xFF;
			color.a = (u8)(FLOAT_80332f60 * drawBase->alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);
		}

		MenuPcs.DrawRect(0, (float)(drawBase->x + (7 - this->moneyState->selectedIndex) * 0x12 + 0x24),
		                 (float)(drawBase->y + 0x5C), FLOAT_80332f78, FLOAT_80332f6c,
		                 FLOAT_80332f64, FLOAT_80332f64, FLOAT_80332f70,
		                 FLOAT_80332f70, FLOAT_80332f64);
	}

	CFont* font = this->moneyFont;
	font->SetMargin(FLOAT_80332f70);
	font->SetShadow(0);
	font->SetScale(FLOAT_80332f7c);
	font->DrawInit();

	{
		CColor color(0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332f60 * drawBase->alpha));
		font->SetColor(color.color);
	}

	const char* label = GetMenuStr(0x15);
	for (int i = 0; i < 2; i++) {
		font->SetPosX((float)(drawBase->x + 0xB6));
		font->SetPosY((FLOAT_80332f68 + ((float)(drawBase->y + 0x18) + FLOAT_80332f68 * (float)i)) -
		              FLOAT_80332f80 - FLOAT_80332f84);
		font->Draw(label);
	}

	DrawInit();
	if (mode == 1) {
		DrawSingWin(-1);
		if (this->moneyState->optionState == 1) {
			DrawSingWinMess(1, (int)this->moneyState->messageMask, 0);
		}
	}

	if ((mode != 0) && (this->moneyState->optionState == 1)) {
		s16* singWindow = this->singWindowInfo;
		float cursorY = (float)(singWindow[1] + 0x20);
		cursorY += (float)(this->moneyState->subMenuIndex * SingWinMessHeight());

		int anim = (int)System.m_frameCounter % 8;
		DrawCursor((int)((float)singWindow[0] + (float)anim), (int)cursorY, FLOAT_80332f70);
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
bool CMenuPcs::MoneyClose()
{
	this->moneyState->frame++;

	MoneyMenuAnimList* panel = this->moneyPanel;
	MoneyMenuAnim* anim = panel->anims;
	int finished = 0;
	int count = panel->count;
	int frame = this->moneyState->frame;

	for (int i = 0; i < count; i++, anim++) {
		if (frame < anim->startFrame) {
			continue;
		}

		if (anim->startFrame + anim->duration <= frame) {
			float zero = LoadFloat(FLOAT_80332f64);
			finished++;
			anim->alpha = zero;
			anim->dx = zero;
			anim->dy = zero;
		} else {
			anim->frame++;
			double one = LoadDouble(DOUBLE_80332F90);
			double duration = (double)anim->duration;
			double animFrame = (double)anim->frame;
			double rate = one / duration;
			anim->alpha = (float)(one - rate * animFrame);
			if ((anim->flags & 2) == 0) {
				duration = (double)anim->duration;
				animFrame = (double)anim->frame;
				rate = one / duration;
				float ratio = (float)(one - rate * animFrame);
				float dx = anim->targetX - (float)anim->x;
				float dy = anim->targetY - (float)anim->y;
				anim->dx = dx * ratio;
				anim->dy = dy * ratio;
			}
		}
	}

	bool result = false;
	if (count == finished) {
		result = true;
	}
	return result;
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
int CMenuPcs::MoneyCtrl()
{
	int result;
	MoneyMenuState* state;
	int mode;

	result = 0;
	this->moneyState->prevMode = this->moneyState->mode;
	state = this->moneyState;
	mode = state->mode;
	if ((mode == 0) || ((mode != 0) && (state->optionState == 1))) {
		result = MoneyCtrlCur();
	} else if ((mode == 1) && ((int)state->optionState == 0)) {
		if (this->singWindowInfo[5] == 1) {
			result = 0;
			state->optionState = state->optionState + 1;
		}
	} else if (((mode == 1) && (state->optionState == 2)) && (this->singWindowInfo[5] == 3)) {
		result = 0;
		state->optionState = 0;
		this->moneyState->mode = 0;
		this->moneyState->frame = 0;
	}

	if (result != 0) {
		MoneyMenuAnim* anim = this->moneyPanel->anims;
		anim->alpha = LoadFloat(FLOAT_80332f70);
		anim->startFrame = 0;
		anim->duration = 10;
		anim->frame = 0;
	}

	return result;
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
	if (this->moneyState->initialized == '\0') {
		memset(this->moneyPanel, 0, sizeof(*this->moneyPanel));

		float one = FLOAT_80332f70;
		MoneyMenuAnim* initAnim = this->moneyPanel->anims;
		int initCount = 8;
		do {
			initAnim[0].uvScale = one;
			initAnim[1].uvScale = one;
			initAnim[2].uvScale = one;
			initAnim[3].uvScale = one;
			initAnim[4].uvScale = one;
			initAnim[5].uvScale = one;
			initAnim[6].uvScale = one;
			initAnim[7].uvScale = one;
			initAnim += 8;
		} while (--initCount != 0);

		int entryIndex = 0;
		MoneyMenuAnim* firstAnim = &this->moneyPanel->anims[entryIndex++];
		firstAnim->tex = 0x3b;
		firstAnim->y = 0x68;
		firstAnim->w = 0xf8;
		firstAnim->h = 0x88;
		firstAnim->x =
			static_cast<short>(static_cast<int>(DOUBLE_80332F98 - (double)firstAnim->w * DOUBLE_80332FA0));
		firstAnim->u = FLOAT_80332f64;
		firstAnim->v = FLOAT_80332f64;
		firstAnim->uvScale = FLOAT_80332f70;
		firstAnim->flags = 0;
		firstAnim->duration = 10;
		this->moneyPanel->count = 1;

		s_Money = 0;
		int row = 0;
		do {
			MoneySetPlace(row);
			row = row + 1;
		} while (row < 2);

		this->moneyState->selectedIndex = 0;
		this->moneyState->initialized = 1;
	}

	this->moneyState->frame++;

	MoneyMenuAnimList* panel = this->moneyPanel;
	MoneyMenuAnim* anim = panel->anims;
	int finished = 0;
	int count = panel->count;
	int frame = this->moneyState->frame;

	for (int i = 0; i < count; i++, anim++) {
		if (frame >= anim->startFrame) {
			if (anim->startFrame + anim->duration <= frame) {
				finished++;
				anim->alpha = FLOAT_80332f70;
				anim->dx = FLOAT_80332f64;
				anim->dy = FLOAT_80332f64;
			} else {
				anim->frame++;
				double one = DOUBLE_80332F90;
				double duration = (double)anim->duration;
				double animFrame = (double)anim->frame;
				double rate = DOUBLE_80332F90 / duration;
				anim->alpha = (float)(rate * animFrame);
				if ((anim->flags & 2) == 0) {
					duration = (double)anim->duration;
					animFrame = (double)anim->frame;
					rate = one / duration;
					float ratio = (float)(rate * animFrame);
					float dx = anim->targetX - (float)anim->x;
					float dy = anim->targetY - (float)anim->y;
					anim->dx = dx * ratio;
					anim->dy = dy * ratio;
				}
			}
		}
	}

	bool opened = false;
	if (count == finished) {
		opened = true;
	}
	return opened;
}
