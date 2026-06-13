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

extern const float kEquipZero = 0.0f;
extern const double kEquipOneDouble = 1.0;
extern const double kEquipWindowCenterX = 216.0;
extern const double kEquipHalfDouble = 0.5;
extern const double kEquipIntToDoubleBias = 4503601774854144.0;
extern const float kEquipOne = 1.0f;
extern const float kEquipColorMax = 255.0f;
extern const float kEquipListFontScale = 0.9f;
extern const float kEquipTextYOffset = 4.0f;
extern const float kEquipMarkXOffset = 12.0f;
extern const float kEquipMarkHeight = 24.0f;
extern const float kEquipHelpCenterX = 320.0f;
extern const float kEquipHalf = 0.5f;
extern const float kEquipHelpY = 352.0f;
extern const float kEquipHelpScale = 3.0f;
extern const double kEquipZeroDouble = 0.0;
extern const float kEquipInitU = 128.0f;
extern const float kEquipInitV = 8.0f;
extern const float kEquipSmallScale = 0.75f;

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
STATIC_ASSERT(offsetof(EquipMenuState, selected) == 0x26);
STATIC_ASSERT(offsetof(EquipMenuState, selected[1]) == 0x28);
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
	return state->selected[mode];
}

static inline s16& GetEquipCurSelected(EquipMenuState* state)
{
	return state->selected[state->mode];
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
	int equipIndex = GetEquipMenuState(this)->selected[0];

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

	if (((active & 0xff) != 0) && (equipIndex != GetEquipType(item))) {
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
	int selOff = (int)GetEquipMenuState(this)->selected[0] * 0x40 + 8;
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
					fVar1 = (float)-((dVar2 / (double)item->duration) * (double)item->step - dVar2);
					float dx = item->targetX - (float)item->x;
					float dy = item->targetY - (float)item->y;
					item->dx = dx * fVar1;
					item->dy = dy * fVar1;
				}
			}
		}
		item++;
	}

	int result = 0;
	if (itemCount == doneCount) {
		EquipOpenAnim* selected = &GetEquipListStorage(this)->entries[GetEquipMenuState(this)->selected[0]];
		selected->x = (s16)(int)(kEquipWindowCenterX - (double)selected->w * kEquipHalfDouble);
		result = 1;
	}

	return result;
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
	EquipOpenAnim* selected = &GetEquipListStorage(this)->entries[GetEquipMenuState(this)->selected[0]];

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
					fVar1 = (float)((dVar2 / (double)item->duration) * (double)item->step);
					float dx = item->targetX - (float)item->x;
					float dy = item->targetY - (float)item->y;
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
	int press;
	int hold;
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

	int padLock = Pad.m_debugPadLock;
	if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	unsigned int rawPress;
	if (blocked) {
		rawPress = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		rawPress = Pad.GetPadInputs()[padIndex].buttonDown[0];
	}
	press = (s16)(u16)rawPress;

	blocked = false;
	if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	unsigned int rawHold;
	if (blocked) {
		rawHold = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		rawHold = Pad.GetPadInputs()[padIndex].repeatButton;
	}
	hold = (s16)(u16)rawHold;

	if (hold == 0) {
		return 0;
	}

	int mode = static_cast<int>(GetEquipMenuState(this)->mode);

	if (mode == 0) {
		if ((hold & 8) != 0) {
			int sel = GetEquipMenuState(this)->selected[mode];
			if (sel != 0) {
				GetEquipMenuState(this)->selected[mode] = sel - 1;
			} else {
				GetEquipMenuState(this)->selected[mode] = 3;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((hold & 4) != 0) {
			if (GetEquipMenuState(this)->selected[mode] < 3) {
				GetEquipMenuState(this)->selected[mode] = GetEquipMenuState(this)->selected[mode] + 1;
			} else {
				GetEquipMenuState(this)->selected[mode] = 0;
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
		int letterCount = letterBuffer[0];

		if ((hold & 8) != 0) {
			int sel = GetEquipMenuState(this)->selected[mode];
			if (sel != 0) {
				GetEquipMenuState(this)->selected[mode] = sel - 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else {
				int scroll = GetEquipMenuState(this)->scroll;
				if (scroll != 0) {
					GetEquipMenuState(this)->scroll = scroll - 1;
					Sound.PlaySe(1, 0x40, 0x7f, 0);
				} else {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				}
			}
		} else if ((hold & 4) != 0) {
			s16 selected = GetEquipMenuState(this)->selected[mode];

			if (selected < 7) {
				GetEquipMenuState(this)->selected[mode] = selected + 1;
			} else if (static_cast<int>(GetEquipMenuState(this)->scroll) + static_cast<int>(selected) < letterCount - 1) {
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
				            static_cast<int>(GetEquipMenuState(this)->selected[mode]);
				s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
				unsigned int valid = ChkEquipActive(index);

				if (((valid & 0xff) == 0) || ((index != 0) && ((EquipChk((int)entries[index]) & 0xff) != 0))) {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				} else {
					caravanWork->ChgEquipPos(GetEquipMenuState(this)->selected[0],
					                         (index != 0) ? entries[index] : -1);
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
#pragma opt_lifetimes off
void CMenuPcs::EquipDraw()
{
	int helpItem;
	int helpFound = 0;
	float w;
	float h;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int mode = static_cast<int>(GetEquipMenuState(this)->mode);
	unsigned int listState = static_cast<int>(GetEquipMenuState(this)->listState);
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	EquipOpenAnim* item = GetEquipListStorage(this)->entries;

	for (int i = 0; i < GetEquipListStorage(this)->count; i++) {
		int tex = item->tex;
		if (tex >= 0) {
			float x = (float)item->x;
			float y = (float)item->y;
			w = (float)item->w;
			h = (float)item->h;
			float u = item->u;
			float v = item->v;

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

			if ((listState == 1) && (i == static_cast<int>(GetEquipMenuState(this)->selected[0]))) {
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
			int iconY = (int)((float)(item->y + 6) - kEquipOne);
			int iconX = (int)(float)(item->x + item->w - 0x10);
			DrawSingleIcon(caravanWork->m_inventoryItems[caravanWork->m_equipment[i]], iconX, iconY,
			               item->alpha, 0, kEquipOne);
		}
		item++;
	}

	CFont* font = GetEquipFont(this);
	font->SetMargin(kEquipOne);
	font->SetShadow(0);
	font->SetScale(kEquipListFontScale);
	font->DrawInit();

	item = GetEquipListStorage(this)->entries;
	for (unsigned int i = 0; i < 4; i++) {
		if (caravanWork->m_equipment[i] >= 0) {
			CColor color(0xff, 0xff, 0xff, (u8)(kEquipColorMax * item->alpha));
			font->SetColor(color.color);
			int itemIdx = caravanWork->m_inventoryItems[caravanWork->m_equipment[i]];
			char* str = Game.m_cFlatDataArr[1].TableStrings(0)[itemIdx * 5 + 4];
			if ((GetEquipMenuState(this)->mode == 0) && (i == static_cast<int>(GetEquipMenuState(this)->selected[0]))) {
				helpItem = itemIdx;
				helpFound = 1;
			}
			float width = font->GetWidth(str);
			float textY = (float)(item->y + 0xb);
			font->SetPosX((float)((((float)item->w - width) * kEquipHalfDouble) + (double)item->x));
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
				float u = listItem->u;
				float y = (float)listItem->y;
				float v = listItem->v;
				w = (float)listItem->w;
				h = (float)listItem->h;

				if (i == GetEquipListStorage(this)->count) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(listItem->tex));
					GXColor colors[4];
					colors[0].r = 0xff;
					colors[0].g = 0xff;
					colors[0].b = 0xff;
					colors[0].a = 0xff;
					colors[1].r = 0xff;
					colors[1].g = 0xff;
					colors[1].b = 0xff;
					colors[1].a = 0xff;
					colors[2].r = 0xff;
					colors[2].g = 0xff;
					colors[2].b = 0xff;
					colors[2].a = 0xff;
					colors[3].r = 0xff;
					colors[3].g = 0xff;
					colors[3].b = 0xff;
					colors[3].a = 0xff;
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);
					w = listItem->alpha * w;
					if (w > kEquipZero) {
						MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, kEquipOne, kEquipOne, kEquipZero);
						x = x + w;
						u = u + w;
					}
					if ((w > kEquipZero) && (w < (float)listItem->w)) {
						colors[1].r = 0xff;
						colors[1].g = 0xff;
						colors[1].b = 0xff;
						colors[1].a = 0;
						colors[3].r = 0xff;
						colors[3].g = 0xff;
						colors[3].b = 0xff;
						colors[3].a = 0;
						w = (float)(kEquipOneDouble / (double)listItem->duration) * (float)listItem->w;
						MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, kEquipOne, kEquipOne, kEquipZero);
					}
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				} else {
					float alpha = listItem->alpha;
					if (tex == 0x37) {
						int idx = drawIndex + GetEquipMenuState(this)->scroll;
						if ((idx < 1) || (idx >= letterCount)) {
							if ((idx >= letterCount) || (ChkEquipActive(idx) == 0)) {
								tex = 0x34;
								alpha = (float)(kEquipHalfDouble * (double)listItem->alpha);
							}
						} else {
							unsigned int chk = idx - 1;
							int equipped = EquipChk((int)letter[chk + 1]);
							if (((chk + 1) >= letterCount) || ((equipped & 0xff) != 0) || ((ChkEquipActive(chk + 1) & 0xff) == 0)) {
								if ((equipped & 0xff) != 0) {
									int markX = (int)(x - kEquipMarkXOffset);
									int markY = (int)((double)(h - kEquipMarkHeight) * kEquipHalfDouble + (double)y);
									DrawEquipMark(markX, markY, listItem->alpha);
								}
								tex = 0x34;
								alpha = (float)(kEquipHalfDouble * (double)listItem->alpha);
							}
						}
						if ((tex == 0x37) && (drawIndex == GetEquipMenuState(this)->selected[1])) {
							v += h;
						}
						drawIndex++;
					}

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
		int letterCount = letter[0];
		EquipOpenAnimList* list = GetEquipListStorage(this);
		EquipOpenAnim* listStart;
		for (int i = list->count; i < list->listEnd; i++) {
			listStart = &list->entries[i];
			if (listStart->tex == 0x37) {
				break;
			}
		}

		float colorMax = kEquipColorMax;
		EquipOpenAnim* textItem = listStart;
		int idx;
		for (int i = 0; (i < 8) && ((idx = i + GetEquipMenuState(this)->scroll) < letterCount); i++) {
			CColor color(0xff, 0xff, 0xff, (u8)(colorMax * listStart->alpha));
			font->SetColor(color.color);

			char* str;
			if (idx == 0) {
				str = GetMenuStr(0xb);
			} else {
				if (idx >= letterCount) {
					continue;
				}
				int entry = letter[idx];
				if (entry < 0) {
					continue;
				}
				int itemIdx = caravanWork->m_inventoryItems[entry];
				str = Game.m_cFlatDataArr[1].TableStrings(0)[itemIdx * 5 + 4];
				if (idx == static_cast<int>(GetEquipMenuState(this)->selected[1]) + static_cast<int>(GetEquipMenuState(this)->scroll)) {
					helpItem = itemIdx;
					helpFound = 1;
				}
			}

			font->GetWidth(str);
			float textY = (float)(textItem->y + 0xb);
			font->SetPosX((float)(textItem->x + 0x1c));
			font->SetPosY(textY - kEquipTextYOffset);
			font->Draw(str);
			textItem++;
		}

		DrawInit();

		EquipOpenAnim* iconItem = listStart;
		for (int i = 0; (i < 8) && ((idx = i + GetEquipMenuState(this)->scroll) < letterCount); i++) {
			if (idx >= 1) {
				int entry = letter[idx];
				if (entry >= 0) {
					int iconY = (int)((float)(iconItem->y + 6) - kEquipOne);
					int iconX = (int)(float)(iconItem->x + iconItem->w - 0x10);
					DrawSingleIcon(caravanWork->m_inventoryItems[entry], iconX, iconY,
					               listStart->alpha, 0, kEquipOne);
				}
			}
			iconItem++;
		}
	}

	if ((mode == 1) && (GetEquipMenuState(this)->step == 1)) {
		EquipOpenAnim* listStart = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		float pos = CalcListPos(static_cast<int>(GetEquipMenuState(this)->scroll), static_cast<int>(letter[0]), 0);
		if (pos > kEquipZero) {
			DrawListPosMark((float)listStart->x, (float)listStart->y, pos);
		}
	}

	if (((mode == 0) && (listState == 1)) || ((mode != 0) && (GetEquipMenuState(this)->step == 1))) {
		float cx;
		float cy;
		if (mode == 0) {
			EquipOpenAnim* cursorItem = &GetEquipListStorage(this)->entries[GetEquipMenuState(this)->selected[0]];
			cy = (float)((double)(cursorItem->h - 0x20) * kEquipHalfDouble + (double)cursorItem->y);
			cx = (float)(cursorItem->x - 0x14);
		} else {
			EquipOpenAnimList* list = GetEquipListStorage(this);
			EquipOpenAnim* found;
			for (int i = list->count; i < list->listEnd; i++) {
				found = &list->entries[i];
				if (found->tex == 0x37) {
					break;
				}
			}
			EquipOpenAnim* cursorItem = &found[GetEquipMenuState(this)->selected[1]];
			cy = (float)((double)(cursorItem->h - 0x20) * kEquipHalfDouble + (double)cursorItem->y);
			cx = (float)(cursorItem->x - 0x14);
		}
		int cursorY = (int)cy;
		int cursorX = (int)(cx + (float)((int)System.m_frameCounter % 8));
		DrawCursor(cursorX, cursorY, kEquipOne);
	}

	EquipMenuState* state = GetEquipMenuState(this);
	s16 endMode = state->mode;
	unsigned int listIndex = static_cast<int>((&state->selected[0])[endMode]) + static_cast<int>(state->scroll);
	int helpEntryIndex;
	if (endMode == 1) {
		helpEntryIndex = GetEquipListStorage(this)->count;
	} else {
		helpEntryIndex = 0;
	}
	int helpAlpha = (int)(kEquipColorMax * GetEquipListStorage(this)->entries[helpEntryIndex].alpha);
	CFont* helpFont = m_fonts[0];
	if (!helpFound) {
		helpItem = -1;
	}
	if ((listIndex < 1) && (endMode == 1)) {
		helpItem = -1;
	}
	if (((endMode == 0) && (state->emptySlotHelpState == 0)) && (helpItem == -1)) {
		helpItem = 0x267;
	}

	CColor helpColor(0xff, 0xff, 0xff, (u8)helpAlpha);
	int helpX = (int)(kEquipHelpCenterX - w * kEquipHalf);
	float helpYf = kEquipHelpY;
	unsigned int helpY = (int)helpYf;
	DrawHelpMessage(helpItem, helpFont, helpX, helpY, helpColor.color, 10,
	                kEquipOne, kEquipHelpScale);
	if (GetEquipMenuState(this)->mode == 1) {
		int listHelpAlpha = (int)(kEquipColorMax * GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count].alpha);
		if (listIndex < 1) {
			CColor listHelpColor(0xff, 0xff, 0xff, (u8)listHelpAlpha);
			DrawHelpMessage(0x265, helpFont, helpX, helpY, listHelpColor.color, 10,
			                kEquipOne, kEquipHelpScale);
		}
	}
}
#pragma opt_lifetimes reset

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
		for (int k = itemCount; k > 0; k--) {
			item->startFrame = 0;
			item->duration = 1;
			item->alpha = fVar1;
			item++;
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
int CMenuPcs::EquipCtrl()
{
	GetEquipMenuState(this)->prevMode = GetEquipMenuState(this)->mode;
	int mode = GetEquipMenuState(this)->mode;
	int state = 0;
	if ((mode == 0) || ((mode != 0) && (GetEquipMenuState(this)->step == 1))) {
		state = EquipCtrlCur();
	} else if ((mode == 1) && (GetEquipMenuState(this)->step == 0)) {
		state = EquipOpen0();
		if (state != 0) {
			state = 0;
			GetEquipMenuState(this)->step = GetEquipMenuState(this)->step + 1;
		}
	} else if ((mode == 1) && ((GetEquipMenuState(this)->step == 2) && ((state = EquipClose0()) != 0))) {
		GetEquipMenuState(this)->step = 0;
		GetEquipMenuState(this)->mode = 0;
		GetEquipMenuState(this)->frame = 0;
		CmdInit1();
		state = 0;
	}

	if (state) {
		float one = kEquipOne;
		CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);

		EquipOpenAnim* entry = GetEquipListStorage(this)->entries;
		for (int i = 0; i < GetEquipListStorage(this)->count; i++) {
			entry->alpha = one;
			entry->scale = one;
			entry++;
		}

		int idx = 0;
		for (int k = caravanWork->m_numCmdListSlots - 1; k >= 0; k--) {
			EquipOpenAnim* e = &GetEquipListStorage(this)->entries[k];
			e->startFrame = idx;
			idx++;
			e->duration = 3;
		}
	}
	return state;
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
	int iCount;
	EquipOpenAnim* entry;
	double dVar20;

	if ((signed char)GetEquipMenuState(this)->initialized == 0) {
		memset(GetEquipListStorage(this), 0, sizeof(EquipOpenAnimList));
		fVar5 = kEquipOne;
		entry = GetEquipListStorage(this)->entries;
		for (iVar11 = 64; iVar11 != 0; iVar11--) {
			entry->scale = fVar5;
			entry++;
		}

		dVar4 = kEquipIntToDoubleBias;
		dVar3 = kEquipHalfDouble;
		dVar2 = kEquipWindowCenterX;
		fVar1 = kEquipZero;
		iVar6 = 0;
		entry = GetEquipListStorage(this)->entries;
		for (iVar11 = 4; iVar11 != 0; iVar11--) {
			entry->tex = 0x34;
			entry->w = 200;
			entry->h = 0x28;
			entry->x = (s16)(int)-((double)entry->w * dVar3 - dVar2);
			entry->y = iVar6 * (entry->h - 8) + 0x60;
			entry->u = fVar1;
			entry->v = fVar1;
			entry->startFrame = iVar6;
			iVar6++;
			entry->duration = 3;
			entry++;
		}

		GetEquipListStorage(this)->count = 4;
		EquipInit1();
		puVar9 = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		sVar10 = 0;
		iVar6 = 0;
		int letterMax = 0x40;
		while (iVar6 < letterMax) {
			iVar11 = GetItemType(iVar6, 0);
			if (iVar11 == 1) {
				puVar9++;
				*puVar9 = (s16)iVar6;
				sVar10++;
			}
			iVar6++;
		}

		psVar7 = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		*psVar7 = sVar10 + 1;
		GetEquipMenuState(this)->selected[0] = 0;
		GetEquipMenuState(this)->initialized = 1;
	}

	iVar6 = 0;
	GetEquipMenuState(this)->frame = GetEquipMenuState(this)->frame + 1;
	iCount = GetEquipListStorage(this)->count;
	entry = GetEquipListStorage(this)->entries;
	int frameNow = static_cast<int>(GetEquipMenuState(this)->frame);
	for (int i = 0; i < iCount; i++) {
		if (entry->startFrame <= frameNow) {
			if (entry->startFrame + entry->duration <= frameNow) {
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
		for (iVar11 = iCount; iVar11 > 0; iVar11--) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = fVar5;
			entry++;
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
#pragma opt_dead_assignments off
void CMenuPcs::EquipInit1()
{
	int i = (int)GetEquipListStorage(this)->count;

	EquipOpenAnim* e = &GetEquipListStorage(this)->entries[i++];
	e->tex = 0x2e;
	e->x = 0xb8;
	e->y = 0x28;
	e->w = 0x78;
	e->h = 0x108;
	e->u = kEquipInitU;
	e->v = kEquipInitV;
	e->scale = kEquipOne;
	e->startFrame = 5;
	e->duration = 5;

	e = &GetEquipListStorage(this)->entries[i++];
	e->tex = 0x2f;
	e->x = 0xa0;
	e->y = 0xe;
	e->w = 0x30;
	e->h = 0x30;
	e->u = kEquipZero;
	e->v = kEquipZero;
	e->scale = kEquipOne;
	e->startFrame = 0;
	e->duration = 5;

	e = &GetEquipListStorage(this)->entries[i++];
	e->tex = 0x2f;
	e->w = 0x30;
	e->h = 0x30;
	e->x = 0xa5;
	e->y = 0x150 - e->h;
	e->u = kEquipZero;
	e->v = kEquipZero;
	e->scale = kEquipSmallScale;
	e->startFrame = 0;
	e->duration = 5;

	e = &GetEquipListStorage(this)->entries[i++];
	e->flags = 2;
	e->tex = 0x2e;
	e->x = 0xa0;
	e->y = 8;
	e->w = 0x48;
	e->h = 0x140;
	e->u = kEquipZero;
	e->v = kEquipZero;
	e->startFrame = 0;
	e->duration = 5;

	int yOff = 0;
	EquipOpenAnim* anchor = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
	for (int n = 0; n < 8; n++) {
		e = &GetEquipListStorage(this)->entries[i];
		e->flags = 2;
		e->tex = 0x37;
		e->x = anchor->x + 0x24;
		e->y = anchor->y + yOff;
		yOff += 0x20;
		e->w = 200;
		e->h = 0x28;
		e->u = kEquipZero;
		e->v = kEquipZero;
		e->startFrame = 7;
		e->duration = 5;
		i++;
	}

	GetEquipListStorage(this)->listEnd = i;
	float fVar2 = kEquipZero;
	int n = (int)GetEquipListStorage(this)->listEnd - (int)GetEquipListStorage(this)->count;
	EquipOpenAnim* psVar10 = &GetEquipListStorage(this)->entries[GetEquipListStorage(this)->count];
	for (int k = n; k > 0; k--) {
		psVar10->step = 0;
		psVar10->alpha = fVar2;
		psVar10++;
	}
}
#pragma opt_dead_assignments reset
