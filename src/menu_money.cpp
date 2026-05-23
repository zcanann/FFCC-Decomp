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

static const float LOCAL_FLOAT_80332f60 = 255.0f;
extern const float FLOAT_80332f64;
static const float LOCAL_FLOAT_80332f64 = 0.0f;
static const float LOCAL_FLOAT_80332f68 = 32.0f;
static const float LOCAL_FLOAT_80332f6c = 24.0f;
extern const float FLOAT_80332f70;
static const float LOCAL_FLOAT_80332f70 = 1.0f;
static const float LOCAL_FLOAT_80332f74 = 18.0f;
static const float LOCAL_FLOAT_80332f78 = 16.0f;
static const float LOCAL_FLOAT_80332f7c = 0.9f;
extern const float FLOAT_80332f80;
extern const float FLOAT_80332f84;
extern const double DOUBLE_80332F90;
extern const double DOUBLE_80332F98;
extern const double DOUBLE_80332FA0;

unsigned int s_Money = 0;
signed char s_place[16];

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
		int padIndex = blocked;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		press = *(u16*)((u8*)&Pad + padIndex * 0x54 + 8);
	}

	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		int padIndex = blocked;
		padIndex &= ~-((__cntlzw((unsigned int)Pad._448_4_) & 0x20) >> 5);
		hold = *(u16*)((u8*)&Pad + padIndex * 0x54 + 0x14);
	}

	if (hold == 0) {
		return 0;
	}

	int caravanWork = Game.m_scriptFoodBase[0];
	int menuState = (int)this->moneyState;
	int mode = (int)*(s16*)(menuState + 0x30);
	int maxDigits = 1;
	int maxGil = *(int*)(caravanWork + 0x200);
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
		int cursor = *(s16*)(menuState + 0x26);
		unsigned int placeValue = 1;
		for (int i = 0; i < cursor; i++) {
			placeValue *= 10;
		}

		if ((hold & 8) == 0) {
			if ((hold & 4) != 0) {
				unsigned int gil = *(unsigned int*)(caravanWork + 0x200);
				if (gil == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (-1 < (int)(s_Money - placeValue)) {
						gil = s_Money - placeValue;
					}
					int iVar9 = 0;
					int iVar8 = 10000000;
					signed char* puVar10 = s_place + 8;
					int iVar11 = 8;
					bool started = false;
					s_Money = gil;
					do {
						if ((!started) && (iVar8 <= (int)gil)) {
							started = true;
						}
						if (((started) || (iVar8 <= (int)gil)) || (6 < iVar9)) {
							int digit = (int)gil / iVar8;
							if (9 < digit) {
								digit = 9;
							}
							*puVar10 = static_cast<signed char>(digit);
							gil = gil - ((int)gil / iVar8) * iVar8;
						} else {
							*puVar10 = -1;
						}
						puVar10 = puVar10 + 1;
						iVar9 = iVar9 + 1;
						iVar8 /= 10;
						iVar11 = iVar11 + -1;
					} while (iVar11 != 0);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
		} else if (*(int*)(caravanWork + 0x200) == 0) {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
		} else {
			unsigned int gil = s_Money + placeValue;
			if ((unsigned int)*(int*)(caravanWork + 0x200) < gil) {
				gil = *(int*)(caravanWork + 0x200);
			}
			int iVar9 = 0;
			int iVar8 = 10000000;
			signed char* puVar10 = s_place + 8;
			int iVar11 = 8;
			bool started = false;
			s_Money = gil;
			do {
				if ((!started) && (iVar8 <= (int)gil)) {
					started = true;
				}
				if (((started) || (iVar8 <= (int)gil)) || (6 < iVar9)) {
					int digit = (int)gil / iVar8;
					if (9 < digit) {
						digit = 9;
					}
					*puVar10 = static_cast<signed char>(digit);
					gil = gil - ((int)gil / iVar8) * iVar8;
				} else {
					*puVar10 = -1;
				}
				puVar10 = puVar10 + 1;
				iVar9 = iVar9 + 1;
				iVar8 /= 10;
				iVar11 = iVar11 + -1;
			} while (iVar11 != 0);
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		}

		if ((hold & 1) == 0) {
			if ((hold & 2) != 0) {
				if (*(s16*)(menuState + 0x26) == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					*(s16*)(menuState + 0x26) = *(s16*)(menuState + 0x26) - 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
		} else if (*(s16*)(menuState + 0x26) < maxDigits - 1) {
			*(s16*)(menuState + 0x26) = *(s16*)(menuState + 0x26) + 1;
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else {
			Sound.PlaySe(4, 0x40, 0x7F, 0);
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
			} else if ((press & 0x200) != 0) {
				if (attachFlag < 0) {
					*(u8*)(menuState + 0xD) = 1;
					Sound.PlaySe(3, 0x40, 0x7F, 0);
					return 1;
				}
				LetterSetAttachItem(0, 0xFFFFFFFF);
				Sound.PlaySe(3, 0x40, 0x7F, 0);
				return 1;
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
					if (reinterpret_cast<CCaravanWork*>(caravanWork)->CanPlayerPutItem() != 0) {
						this->moneyState->messageMask = this->moneyState->messageMask | 1;
					}
					GetSingWinSize(1, &winW, &winH, 0);
					SetSingWinInfo(0xF0, 0xD0, winW, winH);
					this->singWindowInfo[5] = 0;
					*(s16*)(menuState + 0x12) = 0;
					*(s16*)(menuState + 0x30) = 1;
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			}
		}
	} else {
		int optBase = menuState + mode * 2;

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
					return 0;
				}
				if (*(s16*)(optBase + 0x26) == 0) {
					reinterpret_cast<CCaravanWork*>(caravanWork)->FGPutGil(static_cast<int>(s_Money));
					s_Money = 0;
					int iVar8 = *(int*)(Game.m_scriptFoodBase[0] + 0x200);
					int iVar9 = 0;
					int iVar11 = 10000000;
					bool started = false;
					signed char* puVar10 = s_place;
					int count = 8;
					do {
						if ((!started) && (iVar11 <= iVar8)) {
							started = true;
						}
						if (((started) || (iVar11 <= iVar8)) || (6 < iVar9)) {
							int digit = iVar8 / iVar11;
							if (9 < digit) {
								digit = 9;
							}
							*puVar10 = static_cast<signed char>(digit);
							iVar8 = iVar8 - (iVar8 / iVar11) * iVar11;
						} else {
							*puVar10 = -1;
						}
						puVar10 = puVar10 + 1;
						iVar9 = iVar9 + 1;
						iVar11 /= 10;
						count = count + -1;
					} while (count != 0);

					iVar8 = 0;
					iVar9 = 0;
					iVar11 = 10000000;
					started = false;
					puVar10 = s_place + 8;
					count = 8;
					do {
						if ((!started) && (iVar11 <= iVar8)) {
							started = true;
						}
						if (((started) || (iVar11 <= iVar8)) || (6 < iVar9)) {
							int digit = iVar8 / iVar11;
							if (9 < digit) {
								digit = 9;
							}
							*puVar10 = static_cast<signed char>(digit);
							iVar8 = iVar8 - (iVar8 / iVar11) * iVar11;
						} else {
							*puVar10 = -1;
						}
						puVar10 = puVar10 + 1;
						iVar9 = iVar9 + 1;
						iVar11 /= 10;
						count = count + -1;
					} while (count != 0);
				}
				this->singWindowInfo[5] = 2;
				*(s16*)(menuState + 0x12) = *(s16*)(menuState + 0x12) + 1;
				Sound.PlaySe(2, 0x40, 0x7F, 0);
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
		color.a = (u8)(LOCAL_FLOAT_80332f60 * entry->alpha);
		GXSetChanMatColor(GX_COLOR0A0, color);
		float uvScale = entry->uvScale;
		MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, LOCAL_FLOAT_80332f64);
	}

	s16* drawBase = reinterpret_cast<s16*>(this->moneyPanel->anims);
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x5D));
	{
		GXColor color;
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = (u8)(LOCAL_FLOAT_80332f60 * *(float*)(drawBase + 8));
		GXSetChanMatColor(GX_COLOR0A0, color);
	}

	for (int i = 0; i < 2; i++) {
		float y = (float)(drawBase[1] + 0x18) + LOCAL_FLOAT_80332f68 * (float)i;
		float x = (float)(drawBase[0] + 0x20);
		for (int j = 0; j < 8; j++) {
			signed char digit = s_place[i * 8 + j];
			if (digit >= 0) {
				MenuPcs.DrawRect(0, x, y, LOCAL_FLOAT_80332f6c, LOCAL_FLOAT_80332f68,
				                 LOCAL_FLOAT_80332f6c * (float)digit, LOCAL_FLOAT_80332f68 * (float)i,
				                 LOCAL_FLOAT_80332f70, LOCAL_FLOAT_80332f70, LOCAL_FLOAT_80332f64);
			}
			x += LOCAL_FLOAT_80332f74;
		}
	}

	if ((mode == 0) && (selectionState == 1)) {
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x48));
		{
			GXColor color;
			color.r = 0xFF;
			color.g = 0xFF;
			color.b = 0xFF;
			color.a = (u8)(LOCAL_FLOAT_80332f60 * *(float*)(drawBase + 8));
			GXSetChanMatColor(GX_COLOR0A0, color);
		}

		MenuPcs.DrawRect(0, (float)(drawBase[0] + (7 - this->moneyState->selectedIndex) * 0x12 + 0x24),
		                 (float)(drawBase[1] + 0x5C), LOCAL_FLOAT_80332f78, LOCAL_FLOAT_80332f6c,
		                 LOCAL_FLOAT_80332f64, LOCAL_FLOAT_80332f64, LOCAL_FLOAT_80332f70,
		                 LOCAL_FLOAT_80332f70, LOCAL_FLOAT_80332f64);
	}

	CFont* font = this->moneyFont;
	font->SetMargin(LOCAL_FLOAT_80332f70);
	font->SetShadow(0);
	font->SetScale(LOCAL_FLOAT_80332f7c);
	font->DrawInit();

	{
		CColor color(0xFF, 0xFF, 0xFF, (u8)(LOCAL_FLOAT_80332f60 * *(float*)(drawBase + 8)));
		font->SetColor(color.color);
	}

	const char* label = GetMenuStr(0x15);
	for (int i = 0; i < 2; i++) {
		font->SetPosX((float)(drawBase[0] + 0xB6));
		font->SetPosY((LOCAL_FLOAT_80332f68 + ((float)(drawBase[1] + 0x18) + LOCAL_FLOAT_80332f68 * (float)i)) -
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

		int frame = (int)System.m_frameCounter;
		int frameSign = frame >> 31;
		int anim = ((frameSign * 8) | ((frame * 0x20000000 + frameSign) >> 29)) - frameSign;
		DrawCursor((int)((float)singWindow[0] + (float)anim), (int)cursorY, LOCAL_FLOAT_80332f70);
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
			float zero = FLOAT_80332f64;
			finished++;
			anim->alpha = zero;
			anim->dx = zero;
			anim->dy = zero;
		} else {
			anim->frame++;
			double one = DOUBLE_80332F90;
			anim->alpha =
				(float)-((DOUBLE_80332F90 / (double)anim->duration) * (double)anim->frame - DOUBLE_80332F90);
			if ((anim->flags & 2) == 0) {
				float ratio = (float)-((one / (double)anim->duration) * (double)anim->frame - one);
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
		anim->alpha = FLOAT_80332f70;
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
		memset(this->moneyPanel, 0, 0x1008);

		float fVar1 = FLOAT_80332f70;
		int iVar8 = (int)this->moneyPanel + 8;
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

		MoneyMenuAnim* firstAnim = &this->moneyPanel->anims[0];
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

		unsigned int scriptFood = Game.m_scriptFoodBase[0];
		s_Money = 0;
		signed char* puVar9 = s_place;
		iVar15 = 0;
		do {
			iVar8 = 10000000;
			int iVar12;
			if (iVar15 == 0) {
				iVar12 = *(int *)(scriptFood + 0x200);
			} else {
				iVar12 = 0;
			}
			int iVar13 = 0;
			int iVar7 = 8;
			int started = 0;
			signed char* puVar14 = puVar9;
			do {
				if ((!started) && (iVar12 >= iVar8)) {
					started = 1;
				}
				if (((started) || (iVar12 >= iVar8)) || (6 < iVar13)) {
					int iVar10 = iVar12 / iVar8;
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
				anim->alpha = (float)((DOUBLE_80332F90 / (double)anim->duration) * (double)anim->frame);
				if ((anim->flags & 2) == 0) {
					float ratio = (float)((one / (double)anim->duration) * (double)anim->frame);
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
