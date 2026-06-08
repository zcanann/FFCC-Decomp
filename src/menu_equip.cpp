#include "ffcc/menu_equip.h"
#include "ffcc/joybus.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/gobjwork.h"
#include "ffcc/gxfunc.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/color.h"
#include <string.h>
#include "ffcc/fontman.h"

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

#define kEquipZero 0.0f
#define kEquipOneDouble 1.0
#define kEquipWindowCenterX 216.0
#define kEquipHalfDouble 0.5
#define kEquipIntToDoubleBias 4503601774854144.0
#define kEquipOne 1.0f
#define kEquipColorMax 255.0f
#define kEquipListFontScale 0.9f
#define kEquipTextYOffset 4.0f
#define kEquipMarkXOffset 12.0f
#define kEquipMarkHeight 24.0f
#define kEquipHelpCenterX 320.0f
#define kEquipHalf 0.5f
#define kEquipHelpY 352.0f
#define kEquipHelpScale 3.0f
#define kEquipZeroDouble 0.0
#define kEquipInitU 128.0f
#define kEquipInitV 8.0f
#define kEquipSmallScale 0.75f

namespace {
STATIC_ASSERT(offsetof(CMenuPcs, m_fonts[4]) == 0x108);
STATIC_ASSERT(offsetof(CMenuPcs, m_equipState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_equipList) == 0x850);
STATIC_ASSERT(offsetof(EquipMenuState, initialized) == 0x0B);
STATIC_ASSERT(offsetof(EquipMenuState, closeRequested) == 0x0D);
STATIC_ASSERT(offsetof(EquipMenuState, listState) == 0x10);
STATIC_ASSERT(offsetof(EquipMenuState, step) == 0x12);
STATIC_ASSERT(offsetof(EquipMenuState, cursorMove) == 0x1E);
STATIC_ASSERT(offsetof(EquipMenuState, frame) == 0x22);
STATIC_ASSERT(offsetof(EquipMenuState, selectedIndex) == 0x26);
STATIC_ASSERT(offsetof(EquipMenuState, subSelectedIndex) == 0x28);
STATIC_ASSERT(offsetof(EquipMenuState, emptySlotHelpState) == 0x2C);
STATIC_ASSERT(offsetof(EquipMenuState, mode) == 0x30);
STATIC_ASSERT(offsetof(EquipMenuState, prevMode) == 0x32);
STATIC_ASSERT(offsetof(EquipMenuState, scroll) == 0x34);
STATIC_ASSERT(offsetof(EquipOpenAnimList, entries) == 8);
STATIC_ASSERT(sizeof(EquipOpenAnimList) == 0x1008);

static inline s16* GetEquipState(CMenuPcs* menu)
{
	return reinterpret_cast<s16*>(menu->m_equipState);
}

static inline EquipMenuState* GetEquipMenuState(CMenuPcs* menu)
{
	return menu->m_equipState;
}

static inline s16& GetEquipModeSelected(EquipMenuState* state, int mode)
{
	return (&state->selectedIndex)[mode];
}

static inline s16& GetEquipCurSelected(EquipMenuState* state)
{
	return (&state->selectedIndex)[state->mode];
}

static inline EquipOpenAnimList* GetEquipListStorage(CMenuPcs* menu)
{
	return menu->m_equipList;
}

static inline int GetEquipStateBase(CMenuPcs* menu)
{
	return reinterpret_cast<int>(GetEquipState(menu));
}

static inline CFont* GetEquipFont(CMenuPcs* menu)
{
	return menu->m_fonts[4];
}

static inline float EquipIntToFloat(int value)
{
	return (float)value;
}
} // namespace

/*
 * --INFO--
 * PAL Address: 0x8015b158
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ChkEquipActive(int index)
{
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	int entryCount = entries[0];
	s16* itemEntries = entries + 1;
	int equipIndex = GetEquipMenuState(this)->selectedIndex;

	if ((index < 0) || (index >= entryCount)) {
		return 0;
	}

	if (index == 0) {
		if (equipIndex < 3) {
			return 0;
		}

		return (unsigned int)(int)caravanWork->m_equipment[equipIndex] >> 0x1f ^ 1;
	}

	int item = caravanWork->m_inventoryItems[itemEntries[index - 1]];
	unsigned int active = ChkEquipPossible(item);

	if (((active & 0xff) != 0) && (GetEquipType(item) != equipIndex)) {
		active = 0;
	}

	return active;
}

/*
 * --INFO--
 * PAL Address: 0x8015b264
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::EquipClose0()
{
	float fVar1;
	double dVar2;
	int doneCount;
	int timer;
	int itemCount;

	GetEquipMenuState(this)->frame = GetEquipMenuState(this)->frame + 1;
	timer = static_cast<int>(GetEquipMenuState(this)->frame);
	int listBase = *(int*)&this->m_equipList;
	int selOff = (int)GetEquipMenuState(this)->selectedIndex * 0x40 + 8;
	if (7 < timer) {
		*(short*)(listBase + selOff) = *(short*)(listBase + selOff) + 0x13;
	}

	short* base = (short*)*(int*)&this->m_equipList;
	doneCount = 0;
	itemCount = (int)base[1] - (int)base[0];
	EquipOpenAnim* item = (EquipOpenAnim*)(base + base[0] * 0x20 + 4);
	for (int i = 0; i < itemCount; i++) {
		fVar1 = kEquipZero;
		if (timer >= item->startFrame) {
			if (item->startFrame + item->duration <= timer) {
				doneCount = doneCount + 1;
				item->alpha = kEquipZero;
				item->dx = kEquipZero;
				item->dy = kEquipZero;
			} else {
				item->step = item->step + 1;
				dVar2 = kEquipOneDouble;
				double recip = kEquipOneDouble / (double)item->duration;
				item->alpha = (float)-(recip * (double)item->step - kEquipOneDouble);
				if ((item->flags & 2) == 0) {
					float dx = item->targetX - (float)item->x;
					float dy = item->targetY - (float)item->y;
					fVar1 = (float)-((dVar2 / (double)item->duration) * (double)item->step - dVar2);
					item->dx = dx * fVar1;
					item->dy = dy * fVar1;
				}
			}
		}
		item++;
	}

	int result = 0;
	if (itemCount == doneCount) {
		EquipOpenAnim* selected = &GetEquipListStorage(this)->entries[GetEquipMenuState(this)->selectedIndex];
		selected->x = (s16)(int)-(((double)selected->w - kEquipIntToDoubleBias) * kEquipHalfDouble - kEquipWindowCenterX);
		result = 1;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015b618
 * PAL Size: 1592b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::EquipCtrlCur()
{
	bool blocked = false;
	unsigned int press;
	unsigned int hold;
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

	int padLock = Pad.m_debugPadLock;
	if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		press = Pad.GetPadInputs()[padIndex].buttonDown[0];
	}

	blocked = false;
	if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		hold = Pad.GetPadInputs()[padIndex].repeatButton;
	}

	if (hold == 0) {
		return 0;
	}

	int mode = static_cast<int>(GetEquipMenuState(this)->mode);

	if (mode == 0) {
		if ((hold & 8) != 0) {
			if (GetEquipCurSelected(GetEquipMenuState(this)) != 0) {
				GetEquipCurSelected(GetEquipMenuState(this)) =
				    GetEquipCurSelected(GetEquipMenuState(this)) - 1;
			} else {
				GetEquipCurSelected(GetEquipMenuState(this)) = 3;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((hold & 4) != 0) {
			if (GetEquipCurSelected(GetEquipMenuState(this)) < 3) {
				GetEquipCurSelected(GetEquipMenuState(this)) =
				    GetEquipCurSelected(GetEquipMenuState(this)) + 1;
			} else {
				GetEquipCurSelected(GetEquipMenuState(this)) = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0xc) == 0) {
			if ((press & 0x20) != 0) {
				GetEquipMenuState(this)->cursorMove = 1;
				Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
				return 1;
			}

			if ((press & 0x40) != 0) {
				GetEquipMenuState(this)->cursorMove = -1;
				Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
				return 1;
			}

			if ((press & 0x100) != 0) {
				if (caravanWork->CanPlayerPutItem() == 0) {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				} else {
					GetEquipMenuState(this)->mode = 1;
					GetEquipMenuState(this)->step = 0;
					GetEquipMenuState(this)->frame = 0;
					Sound.PlaySe(2, 0x40, 0x7f, 0);
				}
			} else if ((press & 0x200) != 0) {
				GetEquipMenuState(this)->closeRequested = 1;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
				return 1;
			}
		}
	} else {
		s16* letterBuffer = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));

		if ((hold & 8) != 0) {
			if (GetEquipCurSelected(GetEquipMenuState(this)) != 0) {
				GetEquipCurSelected(GetEquipMenuState(this)) =
				    GetEquipCurSelected(GetEquipMenuState(this)) - 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else if (GetEquipMenuState(this)->scroll == 0) {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			} else {
				GetEquipMenuState(this)->scroll = GetEquipMenuState(this)->scroll - 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		} else if ((hold & 4) != 0) {
			s16 selected = GetEquipCurSelected(GetEquipMenuState(this));

			if (selected < 7) {
				GetEquipCurSelected(GetEquipMenuState(this)) = selected + 1;
			} else if (static_cast<int>(GetEquipMenuState(this)->scroll) + static_cast<int>(selected) < letterBuffer[0] - 1) {
				GetEquipMenuState(this)->scroll = GetEquipMenuState(this)->scroll + 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			}

			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0xc) == 0) {
			if ((press & 0x100) != 0) {
				int index = static_cast<int>(GetEquipMenuState(this)->scroll) +
				            static_cast<int>(GetEquipCurSelected(GetEquipMenuState(this)));
				s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
				int equipIndex = static_cast<int>(GetEquipMenuState(this)->selectedIndex);
				unsigned int valid = ChkEquipActive(index);

				if (((valid & 0xff) == 0) || ((index != 0) && (EquipChk(entries[index]) != 0))) {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				} else {
					int item;
					if (index == 0) {
						item = -1;
					} else {
						item = entries[index];
					}
					caravanWork->ChgEquipPos(equipIndex, item);
					caravanWork->CalcStatus();
					GetEquipMenuState(this)->step = GetEquipMenuState(this)->step + 1;
					GetEquipMenuState(this)->frame = 0;
					CmdInit2();
					Sound.PlaySe(2, 0x40, 0x7f, 0);
				}
			} else if ((press & 0x200) != 0) {
				GetEquipMenuState(this)->step = GetEquipMenuState(this)->step + 1;
				GetEquipMenuState(this)->frame = 0;
				CmdInit2();
				Sound.PlaySe(3, 0x40, 0x7f, 0);
			}
		}
	}

	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8015bc50
 * PAL Size: 4280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::EquipDraw()
{
	unsigned int helpItem = -1;
	bool helpFound = false;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	unsigned int mode = static_cast<int>(GetEquipMenuState(this)->mode);
	int listState = static_cast<int>(GetEquipMenuState(this)->listState);
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	EquipOpenAnim* item = GetEquipListStorage(this)->entries;

	for (int i = 0; i < GetEquipListStorage(this)->count; i++) {
		int tex = item->tex;
		if (tex >= 0) {
			float x = (float)item->x;
			float y = (float)item->y;
			float w = (float)item->w;
			float h = (float)item->h;
			float u = item->u;
			float v = item->v;

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

			if ((listState == 1) && (i == static_cast<int>(GetEquipMenuState(this)->selectedIndex))) {
				v = v + h;
			}

			GXColor color;
			color.r = 0xff;
			color.g = 0xff;
			color.b = 0xff;
			color.a = (u8)(int)(kEquipColorMax * item->alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);

			float scale = item->scale;
			MenuPcs.DrawRect(0, x, y, w, h, u, v, scale, scale, kEquipZero);
		}
		item++;
	}

	item = GetEquipListStorage(this)->entries;
	for (int i = 0; i < 4; i++) {
		if (caravanWork->m_equipment[i] >= 0) {
			int iconX = (int)EquipIntToFloat(item->x + item->w - 0x10);
			int iconY = (int)(EquipIntToFloat(item->y + 6) - kEquipOne);
			int itemIdx = caravanWork->m_inventoryItems[caravanWork->m_equipment[i]];
			DrawSingleIcon(itemIdx, iconX, iconY, item->alpha, 0, kEquipOne);
		}
		item++;
	}

	CFont* font = GetEquipFont(this);
	font->SetMargin(kEquipOne);
	font->SetShadow(0);
	font->SetScale(kEquipListFontScale);
	font->DrawInit();

	item = GetEquipListStorage(this)->entries;
	for (int i = 0; i < 4; i++) {
		if (caravanWork->m_equipment[i] >= 0) {
			CColor color(0xff, 0xff, 0xff, (u8)(int)(kEquipColorMax * item->alpha));
			font->SetColor(color.color);
			int itemIdx = caravanWork->m_inventoryItems[caravanWork->m_equipment[i]];
			const char* str = GetAttrStr(itemIdx);
			if ((mode == 0) && (i == static_cast<int>(GetEquipMenuState(this)->selectedIndex))) {
				helpFound = true;
				helpItem = itemIdx;
			}
			float width = font->GetWidth(str);
			float textX = (float)((((float)item->w - width) * kEquipHalfDouble) + (float)item->x);
			float textY = (float)(item->y + 0xb);
			font->SetPosX(textX);
			font->SetPosY(textY - kEquipTextYOffset);
			font->Draw(str);
		}
		item++;
	}
	DrawInit();

	if (GetEquipMenuState(this)->prevMode != 0) {
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		int drawIndex = 0;
		EquipOpenAnim* listItem = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int letterCount = letter[0];

		for (int i = GetEquipListStorage(this)->count; i < GetEquipListStorage(this)->listEnd; i++) {
			int tex = listItem->tex;
			if (tex >= 0) {
				float x = (float)listItem->x;
				float y = (float)listItem->y;
				float w = (float)listItem->w;
				float h = (float)listItem->h;
				float u = listItem->u;
				float v = listItem->v;
				float alpha = listItem->alpha;

				if (i == GetEquipListStorage(this)->count) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
					GXColor colors[4];
					colors[0].r = 0xff;
					colors[0].g = 0xff;
					colors[0].b = 0xff;
					colors[0].a = 0xff;
					colors[1] = colors[0];
					colors[2] = colors[0];
					colors[3] = colors[0];
					GXColor color;
					color.r = 0xff;
					color.g = 0xff;
					color.b = 0xff;
					color.a = 0xff;
					GXSetChanMatColor(GX_COLOR0A0, color);
					w = listItem->alpha * w;
					float fillWidth = w;
					if (fillWidth > kEquipZero) {
						MenuPcs.DrawRect(0, x, y, fillWidth, h, u, v, colors, kEquipOne, kEquipOne, kEquipZero);
						x = x + fillWidth;
						u = u + fillWidth;
					}
					if ((fillWidth > kEquipZero) && (fillWidth < (float)listItem->w)) {
						colors[1].a = 0;
						colors[3].a = 0;
						float fadeWidth =
						    (float)(kEquipOneDouble / (double)listItem->duration) * (float)listItem->w;
						MenuPcs.DrawRect(0, x, y, fadeWidth, h, u, v, colors, kEquipOne, kEquipOne, kEquipZero);
					}
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				} else if (tex == 0x37) {
					int idx = drawIndex + GetEquipMenuState(this)->scroll;
					if ((idx < 1) || (idx >= letterCount)) {
						if ((idx >= letterCount) || (ChkEquipActive(idx) == 0)) {
							tex = 0x34;
							alpha = (float)(kEquipHalfDouble * (double)alpha);
						}
					} else {
						int equipped = EquipChk((int)letter[idx]);
						if ((equipped == 0) && (ChkEquipActive(idx) == 0)) {
							tex = 0x34;
							alpha = (float)(kEquipHalfDouble * (double)alpha);
						}
						if (equipped != 0) {
							int markX = (int)(x - kEquipMarkXOffset);
							int markY = (int)(((double)h - (double)kEquipMarkHeight) * kEquipHalfDouble + (double)y);
							DrawEquipMark(markX, markY, listItem->alpha);
						}
					}
					if ((tex == 0x37) && (drawIndex == GetEquipMenuState(this)->subSelectedIndex)) {
						v += h;
					}
					drawIndex++;
				}

				if (i != GetEquipListStorage(this)->count) {
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
					GXColor color;
					color.r = 0xff;
					color.g = 0xff;
					color.b = 0xff;
					color.a = (u8)(int)(kEquipColorMax * alpha);
					GXSetChanMatColor(GX_COLOR0A0, color);
					float scale = listItem->scale;
					MenuPcs.DrawRect(0, x, y, w, h, u, v, scale, scale, kEquipZero);
				}
			}
			listItem++;
		}
	}

	if (mode == 1) {
		font = GetEquipFont(this);
		font->SetMargin(kEquipOne);
		font->SetShadow(0);
		font->SetScale(kEquipListFontScale);
		font->DrawInit();

		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		EquipOpenAnim* listStart = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
		for (int i = GetEquipListStorage(this)->count; i < GetEquipListStorage(this)->listEnd; i++) {
			if (listStart->tex == 0x37) {
				break;
			}
			listStart++;
		}

		EquipOpenAnim* textItem = listStart;
		for (int i = 0; (i < 8) && (i + GetEquipMenuState(this)->scroll < letter[0]); i++) {
			int idx = i + GetEquipMenuState(this)->scroll;
			CColor color(0xff, 0xff, 0xff, (u8)(kEquipColorMax * listStart->alpha));
			font->SetColor(color.color);

			const char* str = 0;
			if (idx == 0) {
				str = GetMenuStr(0xb);
			} else if (letter[idx] >= 0) {
				int itemIdx = caravanWork->m_inventoryItems[letter[idx]];
				str = GetAttrStr(itemIdx);
				if (idx == static_cast<int>(GetEquipMenuState(this)->subSelectedIndex) + static_cast<int>(GetEquipMenuState(this)->scroll)) {
					helpItem = itemIdx;
				}
			}

			if (str != NULL) {
				font->GetWidth(str);
				font->SetPosX(EquipIntToFloat(textItem->x + 0x1c));
				font->SetPosY(EquipIntToFloat(textItem->y + 0xb) - kEquipTextYOffset);
				font->Draw(str);
			}
			textItem++;
		}

		DrawInit();

		EquipOpenAnim* iconItem = listStart;
		for (int i = 0; (i < 8) && (i + GetEquipMenuState(this)->scroll < letter[0]); i++) {
			int idx = i + GetEquipMenuState(this)->scroll;
			if ((idx > 0) && (letter[idx] >= 0)) {
				int iconX = (int)EquipIntToFloat(iconItem->x + iconItem->w - 0x10);
				int iconY = (int)(EquipIntToFloat(iconItem->y + 6) - kEquipOne);
				int itemIdx = caravanWork->m_inventoryItems[letter[idx]];
				DrawSingleIcon(itemIdx, iconX, iconY, listStart->alpha, 0, kEquipOne);
			}
			iconItem++;
		}
	}

	if ((mode == 1) && (GetEquipMenuState(this)->step == 1)) {
		EquipOpenAnim* listStart = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		double pos = CalcListPos(static_cast<int>(GetEquipMenuState(this)->scroll), static_cast<int>(letter[0]), 0);
		if (pos > (double)kEquipZero) {
			DrawListPosMark(static_cast<float>(listStart->x), static_cast<float>(listStart->y), static_cast<float>(pos));
		}
	}

	if (((mode == 0) && (GetEquipMenuState(this)->listState == 1)) || ((mode != 0) && (GetEquipMenuState(this)->step == 1))) {
		EquipOpenAnim* cursorItem;
		if (mode == 0) {
			cursorItem = &GetEquipListStorage(this)->entries[GetEquipMenuState(this)->selectedIndex];
		} else {
			EquipOpenAnim* listBase = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
			cursorItem = &listBase[GetEquipMenuState(this)->subSelectedIndex];
		}
		int cursorX = (int)((double)cursorItem->y + ((double)(cursorItem->h - 0x20) * kEquipHalfDouble));
		int frame = (int)System.m_frameCounter;
		int cursorY = (cursorItem->x - 0x14) + (frame & 7);
		DrawCursor(cursorY, cursorX, kEquipOne);
	}

	if ((mode == 1) && (GetEquipMenuState(this)->step == 1)) {
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int idx = GetEquipMenuState(this)->subSelectedIndex + GetEquipMenuState(this)->scroll;
		if ((idx > 0) && (idx < letter[0]) && (letter[idx] >= 0)) {
			if (EquipChk((int)letter[idx]) != 0) {
				EquipOpenAnim* listBase = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
				EquipOpenAnim* markItem = &listBase[GetEquipMenuState(this)->subSelectedIndex];
				int markX = (int)((double)markItem->x - (double)kEquipMarkXOffset);
				int markY = (int)(((double)markItem->h - (double)kEquipMarkHeight) * kEquipHalfDouble + (double)markItem->y);
				DrawEquipMark(markX, markY, markItem->alpha);
			}
		}
	}

	int listIndex = static_cast<int>(GetEquipModeSelected(GetEquipMenuState(this), mode)) + static_cast<int>(GetEquipMenuState(this)->scroll);
	int helpEntryIndex = (mode == 1) ? GetEquipListStorage(this)->count : 0;
	float helpAlpha = GetEquipListStorage(this)->entries[helpEntryIndex].alpha;
	if (!helpFound) {
		helpItem = -1;
	}
	if ((listIndex < 1) && (mode == 1)) {
		helpItem = -1;
	}
	if (((mode == 0) && (GetEquipMenuState(this)->emptySlotHelpState == 0)) && (helpItem == -1)) {
		helpItem = 0x267;
	}

	CColor helpColor(0xff, 0xff, 0xff, static_cast<u8>(kEquipColorMax * helpAlpha));
	int helpX = (int)kEquipHelpCenterX;
	int helpY = (int)kEquipHelpY;
	DrawHelpMessage(helpItem, m_fonts[0], helpX, helpY, helpColor.color, 10,
	                kEquipOne, kEquipHelpScale);
	if ((mode == 1) && (listIndex < 1)) {
		float listHelpAlpha = GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count].alpha;
		CColor listHelpColor(0xff, 0xff, 0xff, static_cast<s8>(kEquipColorMax * listHelpAlpha));
		DrawHelpMessage(0x265, m_fonts[0], helpX, helpY, listHelpColor.color, 10,
		                kEquipOne, kEquipHelpScale);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015cd08
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::EquipClose()
{
	int doneCount = 0;

	GetEquipMenuState(this)->frame = GetEquipMenuState(this)->frame + 1;
	int timer = static_cast<int>(GetEquipMenuState(this)->frame);
	int itemCount = static_cast<int>(GetEquipListStorage(this)->count);
	EquipOpenAnim* item = GetEquipListStorage(this)->entries;

	for (int i = 0; i < itemCount; i++) {
		if (item->startFrame <= timer) {
			if (item->startFrame + item->duration <= timer) {
				doneCount++;
				item->alpha = kEquipZero;
			} else {
				item->step = item->step + 1;
				double recip = kEquipOneDouble / static_cast<double>(item->duration);
				item->alpha = (float)-(recip * static_cast<double>(item->step) - kEquipOneDouble);
				if ((double)item->alpha < kEquipZeroDouble) {
					item->alpha = kEquipZero;
				}
			}
		}
		item++;
	}

	float fVar1 = kEquipZero;
	int result = 0;
	if (**(short**)&this->m_equipList == doneCount) {
		item = GetEquipListStorage(this)->entries;
		unsigned int n = (unsigned int)itemCount;
		if (0 < (int)n) {
			unsigned int blocks = n >> 3;
			if (blocks != 0) {
				do {
					item[0].startFrame = 0;
					item[0].duration = 1;
					item[0].alpha = fVar1;
					item[1].startFrame = 0;
					item[1].duration = 1;
					item[1].alpha = fVar1;
					item[2].startFrame = 0;
					item[2].duration = 1;
					item[2].alpha = fVar1;
					item[3].startFrame = 0;
					item[3].duration = 1;
					item[3].alpha = fVar1;
					item[4].startFrame = 0;
					item[4].duration = 1;
					item[4].alpha = fVar1;
					item[5].startFrame = 0;
					item[5].duration = 1;
					item[5].alpha = fVar1;
					item[6].startFrame = 0;
					item[6].duration = 1;
					item[6].alpha = fVar1;
					item[7].startFrame = 0;
					item[7].duration = 1;
					item[7].alpha = fVar1;
					item += 8;
					blocks = blocks - 1;
				} while (blocks != 0);
				n = n & 7;
				if (n == 0) {
					return 1;
				}
			}
			do {
				item->startFrame = 0;
				item->duration = 1;
				item->alpha = fVar1;
				item++;
				n = n - 1;
			} while (n != 0);
		}
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015ceb4
 * PAL Size: 596b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::EquipCtrl()
{
	int state;
	int index;
	int itemCount;
	unsigned int blockCount;

	EquipMenuState* es = this->m_equipState;
	es->prevMode = es->mode;
	es = this->m_equipState;
	int mode = es->mode;
	state = 0;
	if ((mode == 0) || ((mode != 0) && (es->step == 1))) {
		state = EquipCtrlCur();
	} else if ((mode == 1) && (es->step == 0)) {
		state = EquipOpen0();
		if (state != 0) {
			state = 0;
			this->m_equipState->step = this->m_equipState->step + 1;
		}
	} else if ((mode == 1) && ((es->step == 2) && (state = EquipClose0(), state != 0))) {
		this->m_equipState->step = 0;
		this->m_equipState->mode = 0;
		this->m_equipState->frame = 0;
		CmdInit1();
		state = 0;
	}

	if (state) {
		float fVar2 = kEquipOne;
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

		EquipOpenAnim* entry = this->m_equipList->entries;
		for (index = 0; index < this->m_equipList->count; index = index + 1) {
			entry->alpha = fVar2;
			entry->scale = fVar2;
			entry++;
		}

		unsigned int slotCount = (unsigned int)caravanWork->m_numCmdListSlots;
		index = 0;
		int byteOff = (slotCount - 1) * 0x40;
		if (-1 < (int)(slotCount - 1)) {
			blockCount = slotCount >> 3;
			if (blockCount != 0) {
				do {
					int p;
					p = *(int*)&this->m_equipList + byteOff;
					*(int*)(p + 0x2c) = index++;
					*(int*)(p + 0x30) = 3;
					p = *(int*)&this->m_equipList + byteOff;
					*(int*)(p + -0x14) = index++;
					*(int*)(p + -0x10) = 3;
					p = *(int*)&this->m_equipList + byteOff;
					*(int*)(p + -0x54) = index++;
					*(int*)(p + -0x50) = 3;
					p = *(int*)&this->m_equipList + byteOff;
					*(int*)(p + -0x94) = index++;
					*(int*)(p + -0x90) = 3;
					p = *(int*)&this->m_equipList + byteOff;
					*(int*)(p + -0xd4) = index++;
					*(int*)(p + -0xd0) = 3;
					p = *(int*)&this->m_equipList + byteOff;
					*(int*)(p + -0x114) = index++;
					*(int*)(p + -0x110) = 3;
					p = *(int*)&this->m_equipList + byteOff;
					*(int*)(p + -0x154) = index++;
					*(int*)(p + -0x150) = 3;
					p = *(int*)&this->m_equipList + byteOff;
					byteOff = byteOff + -0x200;
					*(int*)(p + -0x194) = index++;
					*(int*)(p + -0x190) = 3;
					blockCount = blockCount - 1;
				} while (blockCount != 0);
				slotCount = slotCount & 7;
				if (slotCount == 0) {
					return;
				}
			}
			do {
				int p2 = byteOff + 8;
				byteOff = byteOff + -0x40;
				p2 = *(unsigned int*)&this->m_equipList + p2;
				*(int*)(p2 + 0x24) = index;
				index = index + 1;
				*(int*)(p2 + 0x28) = 3;
				slotCount = slotCount - 1;
			} while (slotCount != 0);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015b468
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::EquipOpen0()
{
	float fVar1;
	double dVar2;
	int timer;
	int doneCount;
	int itemCount;

	GetEquipMenuState(this)->frame = GetEquipMenuState(this)->frame + 1;
	timer = static_cast<int>(GetEquipMenuState(this)->frame);
	EquipOpenAnim* selected = &GetEquipListStorage(this)->entries[GetEquipMenuState(this)->selectedIndex];

	if (timer < 5) {
		selected->x = selected->x - 0x13;
	}

	doneCount = 0;
	EquipOpenAnim* item = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
	itemCount = (int)GetEquipListStorage(this)->listEnd - (int)GetEquipListStorage(this)->count;

	for (int i = 0; i < itemCount; i++) {
		fVar1 = kEquipZero;
		if (timer >= item->startFrame) {
			if (item->startFrame + item->duration <= timer) {
				doneCount = doneCount + 1;
				item->alpha = kEquipOne;
				item->dx = kEquipZero;
				item->dy = kEquipZero;
			} else {
				item->step = item->step + 1;
				dVar2 = kEquipOneDouble;
				double recip = kEquipOneDouble / (double)item->duration;
				item->alpha = (float)(recip * (double)item->step);
				if ((item->flags & 2) == 0) {
					float dx = item->targetX - (float)item->x;
					float dy = item->targetY - (float)item->y;
					fVar1 = (float)((dVar2 / (double)item->duration) * (double)item->step);
					item->dx = dx * fVar1;
					item->dy = dy * fVar1;
				}
			}
		}
		item++;
	}

	int result = 0;
	if (itemCount == doneCount) {
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015d108
 * PAL Size: 948b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::EquipOpen()
{
	float fVar1;
	double dVar2;
	double dVar3;
	double dVar4;
	float fVar5;
	int iVar6;
	s16* psVar7;
	u32 uVar8;
	s16* puVar9;
	s16 sVar10;
	int iVar11;
	u32 uVar12;
	double dVar20;

	if ((signed char)GetEquipMenuState(this)->initialized == 0) {
		memset(GetEquipListStorage(this), 0, sizeof(EquipOpenAnimList));
		fVar5 = kEquipOne;
		EquipOpenAnim* entry = GetEquipListStorage(this)->entries;
		iVar11 = 8;
		do {
			entry[0].scale = fVar5;
			entry[1].scale = fVar5;
			entry[2].scale = fVar5;
			entry[3].scale = fVar5;
			entry[4].scale = fVar5;
			entry[5].scale = fVar5;
			entry[6].scale = fVar5;
			entry[7].scale = fVar5;
			dVar4 = kEquipIntToDoubleBias;
			dVar3 = kEquipHalfDouble;
			dVar2 = kEquipWindowCenterX;
			fVar1 = kEquipZero;
			entry += 8;
			iVar11--;
		} while (iVar11 != 0);

		iVar6 = 0;
		entry = GetEquipListStorage(this)->entries;
		iVar11 = 2;
		do {
			entry[0].tex = 0x34;
			entry[0].w = 200;
			entry[0].h = 0x28;
			entry[0].x = (s16)(int)-(((double)entry[0].w - dVar4) * dVar3 - dVar2);
			entry[0].y = (s16)iVar6 * (entry[0].h - 8) + 0x60;
			entry[0].u = fVar1;
			entry[0].v = fVar1;
			entry[0].startFrame = iVar6;
			entry[0].duration = 3;

			entry[1].tex = 0x34;
			entry[1].w = 200;
			entry[1].h = 0x28;
			entry[1].x = (s16)(int)-(((double)entry[1].w - dVar4) * dVar3 - dVar2);
			entry[1].y = (s16)(iVar6 + 1) * (entry[1].h - 8) + 0x60;
			entry[1].u = fVar1;
			entry[1].v = fVar1;
			entry[1].startFrame = iVar6 + 1;
			iVar6 += 2;
			entry[1].duration = 3;
			entry += 2;
			iVar11--;
		} while (iVar11 != 0);

		GetEquipListStorage(this)->count = 4;
		EquipInit1();
		puVar9 = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		sVar10 = 0;
		for (iVar6 = 0; iVar6 < 0x40; iVar6++) {
			iVar11 = GetItemType(iVar6, 0);
			if (iVar11 == 1) {
				puVar9++;
				*puVar9 = (s16)iVar6;
				sVar10++;
			}
		}

		psVar7 = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		*psVar7 = sVar10 + 1;
		GetEquipMenuState(this)->selectedIndex = 0;
		GetEquipMenuState(this)->initialized = 1;
	}

	iVar6 = 0;
	GetEquipMenuState(this)->frame = GetEquipMenuState(this)->frame + 1;
	uVar8 = (u32)GetEquipListStorage(this)->count;
	EquipOpenAnim* entry = GetEquipListStorage(this)->entries;
	iVar11 = static_cast<int>(GetEquipMenuState(this)->frame);
	for (int i = 0; i < (int)uVar8; i++) {
		if (entry->startFrame <= iVar11) {
			if (entry->startFrame + entry->duration <= iVar11) {
				iVar6++;
				entry->alpha = kEquipOne;
			} else {
				entry->step = entry->step + 1;
				dVar20 = (double)entry->duration;
				entry->alpha = (float)((kEquipOneDouble / dVar20) * (double)entry->step);
			}
		}
		entry++;
	}

	fVar5 = kEquipOne;
	int result = 0;
	if (GetEquipListStorage(this)->count == iVar6) {
		entry = GetEquipListStorage(this)->entries;
		if (0 < (int)uVar8) {
			uVar12 = uVar8 >> 3;
			if (uVar12 != 0) {
				do {
					entry[0].startFrame = 0;
					entry[0].duration = 1;
					entry[0].alpha = fVar5;
					entry[1].startFrame = 0;
					entry[1].duration = 1;
					entry[1].alpha = fVar5;
					entry[2].startFrame = 0;
					entry[2].duration = 1;
					entry[2].alpha = fVar5;
					entry[3].startFrame = 0;
					entry[3].duration = 1;
					entry[3].alpha = fVar5;
					entry[4].startFrame = 0;
					entry[4].duration = 1;
					entry[4].alpha = fVar5;
					entry[5].startFrame = 0;
					entry[5].duration = 1;
					entry[5].alpha = fVar5;
					entry[6].startFrame = 0;
					entry[6].duration = 1;
					entry[6].alpha = fVar5;
					entry[7].startFrame = 0;
					entry[7].duration = 1;
					entry[7].alpha = fVar5;
					entry += 8;
					uVar12--;
				} while (uVar12 != 0);
				uVar8 &= 7;
				if (uVar8 == 0) {
					return 1;
				}
			}

			do {
				entry->startFrame = 0;
				entry->duration = 1;
				entry->alpha = fVar5;
				entry++;
				uVar8--;
			} while (uVar8 != 0);
		}
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015d4bc
 * PAL Size: 732b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::EquipInit1()
{
	int iVar11;
	float fVar2;
	float fVar3;
	float fVar4;
	float fVar5;
	unsigned int uVar6;
	int iVar8;
	int iVar9;
	EquipOpenAnim* psVar10;
	EquipOpenAnim* puVar12;
	EquipOpenAnim* psVar13;
	unsigned int uVar15;

	fVar5 = kEquipInitV;
	fVar4 = kEquipInitU;
	fVar3 = kEquipOne;
	fVar2 = kEquipZero;
	iVar11 = 0;
	iVar8 = (int)GetEquipListStorage(this)->count;
	psVar10 = &GetEquipListStorage(this)->entries[iVar8];
	psVar10->tex = 0x2e;
	psVar10->x = 0xb8;
	psVar10->y = 0x28;
	iVar9 = iVar8 + 4;
	psVar10->w = 0x78;
	psVar10->h = 0x108;
	psVar10->u = fVar4;
	fVar4 = kEquipSmallScale;
	psVar10->v = fVar5;
	psVar10->scale = fVar3;
	psVar10->startFrame = 5;
	psVar10->duration = 5;

	puVar12 = &GetEquipListStorage(this)->entries[iVar8 + 1];
	puVar12->tex = 0x2f;
	puVar12->x = 0xa0;
	puVar12->y = 0xe;
	puVar12->w = 0x30;
	puVar12->h = 0x30;
	puVar12->u = fVar2;
	puVar12->v = fVar2;
	puVar12->scale = fVar3;
	puVar12->startFrame = 0;
	puVar12->duration = 5;

	puVar12 = &GetEquipListStorage(this)->entries[iVar8 + 2];
	puVar12->tex = 0x2f;
	puVar12->w = 0x30;
	puVar12->h = 0x30;
	puVar12->x = 0xa5;
	puVar12->y = 0x150 - puVar12->h;
	puVar12->u = fVar2;
	puVar12->v = fVar2;
	puVar12->scale = fVar4;
	puVar12->startFrame = 0;
	puVar12->duration = 5;

	puVar12 = &GetEquipListStorage(this)->entries[iVar8 + 3];
	puVar12->flags = 2;
	puVar12->tex = 0x2e;
	puVar12->x = 0xa0;
	puVar12->y = 8;
	puVar12->w = 0x48;
	puVar12->h = 0x140;
	puVar12->u = fVar2;
	puVar12->v = fVar2;
	puVar12->startFrame = 0;
	puVar12->duration = 5;

	psVar10 = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
	for (iVar8 = 0; iVar8 < 4; iVar8++) {
		psVar13 = &GetEquipListStorage(this)->entries[iVar9];
		psVar13[0].flags = 2;
		psVar13[0].tex = 0x37;
		iVar9 = iVar9 + 2;
		psVar13[0].x = psVar10->x + 0x24;
		psVar13[0].y = psVar10->y + iVar11;
		iVar11 = iVar11 + 0x20;
		psVar13[0].w = 200;
		psVar13[0].h = 0x28;
		psVar13[0].u = fVar2;
		psVar13[0].v = fVar2;
		psVar13[0].startFrame = 7;
		psVar13[0].duration = 5;

		psVar13[1].flags = 2;
		psVar13[1].tex = 0x37;
		psVar13[1].x = psVar10->x + 0x24;
		psVar13[1].y = psVar10->y + iVar11;
		iVar11 = iVar11 + 0x20;
		psVar13[1].w = 200;
		psVar13[1].h = 0x28;
		psVar13[1].u = fVar2;
		psVar13[1].v = fVar2;
		psVar13[1].startFrame = 7;
		fVar3 = kEquipZero;
		psVar13[1].duration = 5;
	}

	GetEquipListStorage(this)->listEnd = (short)iVar9;
	uVar6 = (unsigned int)((int)GetEquipListStorage(this)->listEnd - (int)GetEquipListStorage(this)->count);
	psVar10 = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
	fVar2 = kEquipZero;
	if (0 < (int)uVar6) {
		uVar15 = uVar6 >> 3;
		if (uVar15 != 0) {
			do {
				psVar10[0].step = 0;
				psVar10[0].alpha = fVar2;
				psVar10[1].step = 0;
				psVar10[1].alpha = fVar2;
				psVar10[2].step = 0;
				psVar10[2].alpha = fVar2;
				psVar10[3].step = 0;
				psVar10[3].alpha = fVar2;
				psVar10[4].step = 0;
				psVar10[4].alpha = fVar2;
				psVar10[5].step = 0;
				psVar10[5].alpha = fVar2;
				psVar10[6].step = 0;
				psVar10[6].alpha = fVar2;
				psVar10[7].step = 0;
				psVar10[7].alpha = fVar2;
				psVar10 += 8;
				uVar15 = uVar15 - 1;
			} while (uVar15 != 0);
			uVar6 = uVar6 & 7;
			if (uVar6 == 0) {
				return;
			}
		}
		do {
			psVar10->step = 0;
			psVar10->alpha = fVar2;
			psVar10++;
			uVar6 = uVar6 - 1;
		} while (uVar6 != 0);
	}
}
