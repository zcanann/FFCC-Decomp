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

#ifdef VERSION_GCCJGC
enum {
    kMoneyDigitsTexture = 0x5C,
    kMoneyCursorTexture = 0x47,
    kMoneyPanelTexture = 0x3A
};
#else
enum {
    kMoneyDigitsTexture = 0x5D,
    kMoneyCursorTexture = 0x48,
    kMoneyPanelTexture = 0x3B
};
#endif

typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

static unsigned int s_Money = 0;
static signed char s_place[2][8];

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
	int digitIndex;
	int digitPlace = 1;
	int gil;
	int started;
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];

	for (digitIndex = 0; digitIndex < 7; digitIndex++) {
		digitPlace *= 10;
	}
	if (row != 0) {
		gil = s_Money;
	} else {
		gil = caravanWork->m_gil;
	}
	digitIndex = started = 0;

	while (digitIndex < 8) {
		if ((!started) && (gil >= digitPlace)) {
			started = 1;
		}
		if (((!started) && (gil < digitPlace)) && (digitIndex < 7)) {
			s_place[row][digitIndex] = -1;
		} else {
			int digit = gil / digitPlace;
			if (9 < digit) {
				digit = 9;
			}
			s_place[row][digitIndex] = digit;
			gil = gil % digitPlace;
		}
		digitIndex++;
		digitPlace /= 10;
	}
}

STATIC_ASSERT(offsetof(CMenuPcs, m_fonts) == 0xF8);
STATIC_ASSERT(offsetof(CMenuPcs, m_moneyState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_menuWindowInfo) == 0x848);
STATIC_ASSERT(offsetof(CMenuPcs, m_moneyPanel) == 0x850);
STATIC_ASSERT(offsetof(MoneyMenuState, messageMask) == 0x9);
STATIC_ASSERT(offsetof(MoneyMenuState, initialized) == 0xB);
STATIC_ASSERT(offsetof(MoneyMenuState, closeRequested) == 0xD);
STATIC_ASSERT(offsetof(MoneyMenuState, listState) == 0x10);
STATIC_ASSERT(offsetof(MoneyMenuState, optionState) == 0x12);
STATIC_ASSERT(offsetof(MoneyMenuState, moveDirection) == 0x1E);
STATIC_ASSERT(offsetof(MoneyMenuState, frame) == 0x22);
STATIC_ASSERT(offsetof(MoneyMenuState, selections) == 0x26);
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
 * EN Address: 0x8015D3F8
 * EN Size: 2604b
 * JP Address: 0x80158D78
 * JP Size: 2608b
 */
int CMenuPcs::MoneyCtrlCur()
{
	s16 hold;
	s16 press;

	press = Pad.GetButtonDown(0);
	hold = Pad.GetButtonRepeat(0);

	if (hold == 0) {
		return 0;
	}

	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
	int maxDigits = 1;
	int mode = this->m_moneyState->mode;
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
		s16* sel = &this->m_moneyState->selections[mode];
		int cursor = *sel;
		unsigned int placeValue = 1;
		while (0 < cursor) {
			placeValue *= 10;
			cursor--;
		}

		if ((hold & 8) != 0) {
			if (caravanWork->m_gil == 0) {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			} else {
				int gil = s_Money + placeValue;
				gil = (gil <= caravanWork->m_gil) ? gil : 0;
				s_Money = gil;
				Sound.PlaySe(1, 0x40, 0x7F, 0);

				MoneySetPlace(1);
			}
		} else {
			if ((hold & 4) != 0) {
				int gil = caravanWork->m_gil;
				if (gil == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (0 <= (int)s_Money - (int)placeValue) {
						gil = s_Money - placeValue;
					}
					s_Money = gil;
					MoneySetPlace(1);
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				}
			}
		}

		if ((hold & 1) != 0) {
			if (this->m_moneyState->selections[mode] < maxDigits - 1) {
				this->m_moneyState->selections[mode] = this->m_moneyState->selections[mode] + 1;
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			}
		} else {
			if ((hold & 2) != 0) {
				int selection = this->m_moneyState->selections[mode];
				if (selection != 0) {
					this->m_moneyState->selections[mode] = selection - 1;
					Sound.PlaySe(1, 0x40, 0x7F, 0);
				} else {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				}
			}
		}

		if ((hold & 0xF) == 0) {
			if ((press & 0x20) != 0) {
				if (attachFlag < 0) {
					this->m_moneyState->moveDirection = 1;
					Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
					return 1;
				}
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			} else if ((press & 0x40) != 0) {
				if (attachFlag < 0) {
					this->m_moneyState->moveDirection = -1;
					Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
					return 1;
				}
				Sound.PlaySe(4, 0x40, 0x7F, 0);
			} else if ((press & 0x100) != 0) {
				if ((int)s_Money <= 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (attachFlag >= 0) {
						LetterSetAttachItem(s_Money, 1);
						Sound.PlaySe(2, 0x40, 0x7F, 0);
						return 1;
					}
					s16 winW;
					s16 winH;
					this->m_moneyState->messageMask = 2;
					if (caravanWork->CanPlayerPutItem() != 0) {
						this->m_moneyState->messageMask = this->m_moneyState->messageMask | 1;
					}
					GetSingWinSize(1, &winW, &winH, 0);
					SetSingWinInfo(0xF0, 0xD0, winW, winH);
					this->m_menuWindowInfo->state = 0;
					this->m_moneyState->optionState = 0;
					this->m_moneyState->mode = 1;
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			} else if ((press & 0x200) != 0) {
				if (attachFlag >= 0) {
					LetterSetAttachItem(0, 0xFFFFFFFF);
					Sound.PlaySe(3, 0x40, 0x7F, 0);
					return 1;
				}
				this->m_moneyState->closeRequested = 1;
				Sound.PlaySe(3, 0x40, 0x7F, 0);
				return 1;
			}
		}
	} else {
		if ((hold & 8) != 0) {
			if ((int)this->m_moneyState->selections[mode] != 0) {
				this->m_moneyState->selections[mode] = this->m_moneyState->selections[mode] - 1;
			} else {
				this->m_moneyState->selections[mode] = 1;
			}
			Sound.PlaySe(1, 0x40, 0x7F, 0);
		} else {
			if ((hold & 4) != 0) {
				if ((int)this->m_moneyState->selections[mode] < 1) {
					this->m_moneyState->selections[mode] = this->m_moneyState->selections[mode] + 1;
				} else {
					this->m_moneyState->selections[mode] = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7F, 0);
			}
		}

		if ((hold & 0xC) == 0) {
			if ((press & 0x100) != 0) {
				int sel = this->m_moneyState->selections[mode];
				if (((int)this->m_moneyState->messageMask & (1 << sel)) == 0) {
					Sound.PlaySe(4, 0x40, 0x7F, 0);
				} else {
					if (sel == 0) {
						caravanWork->FGPutGil(static_cast<int>(s_Money));
						s_Money = 0;
						MoneySetPlace(0);
						MoneySetPlace(1);
					}
					this->m_menuWindowInfo->state = 2;
					this->m_moneyState->optionState = this->m_moneyState->optionState + 1;
					Sound.PlaySe(2, 0x40, 0x7F, 0);
				}
			} else if ((press & 0x200) != 0) {
				this->m_menuWindowInfo->state = 2;
				this->m_moneyState->optionState = this->m_moneyState->optionState + 1;
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
 * EN Address: 0x8015DE24
 * EN Size: 1636b
 * JP Address: 0x801597A8
 * JP Size: 1632b
 */
void CMenuPcs::MoneyDraw()
{
	int i;
	int j;
	CFont* font;
	float x;
	int mode;
	float y;
	const char* label;
	int selectionState;
	GXColor colors[4];
	float w;
	float h;
	MoneyMenuAnim* entry;
	float u;
	float v;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	selectionState = this->m_moneyState->listState;
	entry = this->m_moneyPanel->anims;
	mode = this->m_moneyState->mode;

	for (i = 0; i < this->m_moneyPanel->count; i++, entry++) {
		int tex = entry->tex;
		if (tex < 0) {
			continue;
		}

		x = (float)entry->x;
		y = (float)entry->y;
		w = (float)entry->w;
		h = (float)entry->h;
		u = entry->u;
		v = entry->v;
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
		colors[0].r = 0xFF;
		colors[0].g = 0xFF;
		colors[0].b = 0xFF;
		colors[0].a = (u8)(255.0f * entry->alpha);
		GXSetChanMatColor(GX_COLOR0A0, colors[0]);
		float uvScale = entry->uvScale;
		MenuPcs.DrawRect(0, x, y, w, h, u, v, uvScale, uvScale, 0.0f);
	}

	entry = this->m_moneyPanel->anims;
	MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMoneyDigitsTexture));
	colors[0].r = 0xFF;
	colors[0].g = 0xFF;
	colors[0].b = 0xFF;
	colors[0].a = (u8)(255.0f * entry->alpha);
	GXSetChanMatColor(GX_COLOR0A0, colors[0]);

	for (i = 0; i < 2; i++) {
		x = (float)(entry->x + 0x20);
		y = (float)(entry->y + 0x18) + 32.0f * (float)i;
		for (j = 0; j < 8; j++) {
			signed char digit = s_place[i][j];
			if (digit >= 0) {
				MenuPcs.DrawRect(0, x, y, 24.0f, 32.0f,
				                 24.0f * (float)digit, 32.0f * (float)i,
				                 1.0f, 1.0f, 0.0f);
			}
			x += 18.0f;
		}
	}

	if ((mode == 0) && (selectionState == 1)) {
		MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMoneyCursorTexture));
		colors[0].r = 0xFF;
		colors[0].g = 0xFF;
		colors[0].b = 0xFF;
		colors[0].a = (u8)(255.0f * entry->alpha);
		GXSetChanMatColor(GX_COLOR0A0, colors[0]);

		entry = this->m_moneyPanel->anims;
		MenuPcs.DrawRect(0, (float)(entry->x + ((7 - this->m_moneyState->selections[0]) * 0x12 + 0x24)),
		                 (float)(entry->y + 0x5C), 16.0f, 24.0f,
		                 0.0f, 0.0f, 1.0f,
		                 1.0f, 0.0f);
	}

	font = GetFontItem();
	font->SetMargin(1.0f);
	font->SetShadow(0);
	font->SetScale(0.9f);
	font->DrawInit();

	font->SetColor(CColor(0xFF, 0xFF, 0xFF, (u8)(255.0f * entry->alpha)).color);

	label = GetMenuStr(0x15);
	for (i = 0; i < 2; i++) {
		y = (32.0f + ((float)(entry->y + 0x18) + 32.0f * (float)i)) - 19.8f;
		font->SetPosX((float)(entry->x + 0xB6));
		font->SetPosY(y - 4.0f);
		font->Draw(label);
	}

	DrawInit();
	if (mode == 1) {
		DrawSingWin(-1);
		if (this->m_moneyState->optionState == 1) {
			DrawSingWinMess(1, (int)this->m_moneyState->messageMask, 0);
		}
	}

	if ((mode != 0) && (this->m_moneyState->optionState == 1)) {
		MenuWindowInfo* window = this->m_menuWindowInfo;
		y = (float)(window->y + 0x20);
		x = (float)window->x;
		y += (float)(this->m_moneyState->selections[1] * SingWinMessHeight());
		x += (float)((int)System.m_frameCounter % 8);
		DrawCursor((int)x, (int)y, 1.0f);
	}
}

/*
 * --INFO--
 * PAL Address: 8015f40c
 * PAL Size: 380b
 * EN Address: 0x8015E488
 * EN Size: 380b
 * JP Address: 0x80159E08
 * JP Size: 396b
 */
int CMenuPcs::MoneyClose()
{
	this->m_moneyState->frame++;

	MoneyMenuAnimList* panel = this->m_moneyPanel;
	MoneyMenuAnim* anim = panel->anims;
	int finished = 0;
	int count = panel->count;
	int frame = this->m_moneyState->frame;

	for (int i = 0; i < count; i++, anim++) {
		if (frame < anim->startFrame) {
			continue;
		}

		if (anim->startFrame + anim->duration <= frame) {
			float zero = 0.0f;
			finished++;
			anim->alpha = zero;
			anim->dx = zero;
			anim->dy = zero;
		} else {
			anim->frame++;
			double one = 1.0;
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

	int result = 0;
	if (count == finished) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 8015f588
 * PAL Size: 256b
 * EN Address: 0x8015E604
 * EN Size: 256b
 * JP Address: 0x80159F94
 * JP Size: 256b
 */
int CMenuPcs::MoneyCtrl()
{
	int result;
	MoneyMenuState* state;
	int mode;

	result = 0;
	this->m_moneyState->prevMode = this->m_moneyState->mode;
	state = this->m_moneyState;
	mode = state->mode;
	if ((mode == 0) || ((mode != 0) && (state->optionState == 1))) {
		result = MoneyCtrlCur();
	} else if ((mode == 1) && ((int)state->optionState == 0)) {
		if (this->m_menuWindowInfo->state == 1) {
			result = 0;
			state->optionState = state->optionState + 1;
		}
	} else if (((mode == 1) && (state->optionState == 2)) && (this->m_menuWindowInfo->state == 3)) {
		result = 0;
		state->optionState = 0;
		this->m_moneyState->mode = 0;
		this->m_moneyState->frame = 0;
	}

	if (result != 0) {
		MoneyMenuAnim* anim = this->m_moneyPanel->anims;
		anim->alpha = 1.0f;
		anim->startFrame = 0;
		anim->duration = 10;
		anim->frame = 0;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::MoneyInit()
{
	int i;
	MoneyMenuAnim* anim;

	memset(this->m_moneyPanel, 0, sizeof(*this->m_moneyPanel));

	anim = this->m_moneyPanel->anims;
	for (i = 0; i < 64; i++, anim++) {
		anim->uvScale = 1.0f;
	}

	i = 0;
	anim = &this->m_moneyPanel->anims[i++];
	anim->tex = kMoneyPanelTexture;
	anim->y = 0x68;
	anim->w = 0xf8;
	anim->h = 0x88;
	anim->x = 216.0 - anim->w / 2.0;
	anim->u = 0.0f;
	anim->v = 0.0f;
	anim->uvScale = 1.0f;
	anim->startFrame = 0;
	anim->duration = 10;
	this->m_moneyPanel->count = i;

	s_Money = 0;
	for (i = 0; i < 2; i++) {
		MoneySetPlace(i);
	}

	this->m_moneyState->selections[0] = 0;
	this->m_moneyState->initialized = 1;
}

/*
 * --INFO--
 * PAL Address: 8015f688
 * PAL Size: 928b
 * EN Address: 0x8015E704
 * EN Size: 928b
 * JP Address: 0x8015A094
 * JP Size: 972b
 */
int CMenuPcs::MoneyOpen()
{
	int i;
	MoneyMenuAnim* anim;

	if (this->m_moneyState->initialized == '\0') {
		MoneyInit();
	}

	this->m_moneyState->frame++;

	MoneyMenuAnimList* panel = this->m_moneyPanel;
	anim = panel->anims;
	int finished = 0;
	int count = panel->count;
	int frame = this->m_moneyState->frame;

	for (i = 0; i < count; i++, anim++) {
		if (frame >= anim->startFrame) {
			if (anim->startFrame + anim->duration <= frame) {
				finished++;
				anim->alpha = 1.0f;
				anim->dx = 0.0f;
				anim->dy = 0.0f;
			} else {
				anim->frame++;
				anim->alpha = (1.0 / anim->duration) * anim->frame;
				if ((anim->flags & 2) == 0) {
					float ratio = (1.0 / anim->duration) * anim->frame;
					float dx = anim->targetX - (float)anim->x;
					float dy = anim->targetY - (float)anim->y;
					anim->dx = dx * ratio;
					anim->dy = dy * ratio;
				}
			}
		}
	}

	int opened = 0;
	if (count == finished) {
		opened = 1;
	}
	return opened;
}
