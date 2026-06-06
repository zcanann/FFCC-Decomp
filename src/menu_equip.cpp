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

static const float FLOAT_80332eb8 = 0.0f;
static const double DOUBLE_80332ec0 = 1.0;
static const double DOUBLE_80332ec8 = 216.0;
static const double DOUBLE_80332ed0 = 0.5;
static const double DOUBLE_80332ed8 = 4503601774854144.0;
static const float FLOAT_80332ee0 = 1.0f;
static const float FLOAT_80332ee4 = 255.0f;
static const float FLOAT_80332ee8 = 0.9f;
static const float FLOAT_80332eec = 4.0f;
static const float FLOAT_80332ef0 = 12.0f;
static const float FLOAT_80332ef4 = 24.0f;
static const float FLOAT_80332ef8 = 320.0f;
static const float FLOAT_80332efc = 0.5f;
static const float FLOAT_80332f00 = 352.0f;
static const float FLOAT_80332F04 = 3.0f;
static const double DOUBLE_80332F08 = 0.0;
static const float FLOAT_80332f10 = 128.0f;
static const float FLOAT_80332f14 = 8.0f;
static const float FLOAT_80332f18 = 0.75f;

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
bool CMenuPcs::EquipClose0()
{
	float fVar1;
	double dVar2;
	int doneCount;
	int timer;
	int itemCount;

	EquipMenuState* menuState = GetEquipMenuState(this);
	menuState->frame = menuState->frame + 1;
	timer = static_cast<int>(menuState->frame);
	EquipOpenAnimList* list = GetEquipListStorage(this);
	EquipOpenAnim* selected = &list->entries[menuState->selectedIndex];
	if (7 < timer) {
		selected->x = selected->x + 0x13;
	}

	doneCount = 0;
	itemCount = (int)list->listEnd - (int)list->count;
	EquipOpenAnim* item = &list->entries[list->count];
	for (int i = 0; i < itemCount; i++) {
		fVar1 = FLOAT_80332eb8;
		if (timer >= item->startFrame) {
			if (item->startFrame + item->duration <= timer) {
				doneCount = doneCount + 1;
				item->alpha = FLOAT_80332eb8;
				item->dx = FLOAT_80332eb8;
				item->dy = FLOAT_80332eb8;
			} else {
				item->step = item->step + 1;
				dVar2 = DOUBLE_80332ec0;
				item->alpha =
				    (float)-((DOUBLE_80332ec0 / (double)item->duration) * (double)item->step - DOUBLE_80332ec0);
				if ((item->flags & 2) == 0) {
					fVar1 = (float)-((dVar2 / (double)item->duration) * (double)item->step - dVar2);
					item->dx = (item->targetX - (float)(double)item->x) * fVar1;
					item->dy = (item->targetY - (float)(double)item->y) * fVar1;
				}
			}
		}
		item++;
	}

	if (itemCount == doneCount) {
		selected->x = (s16)(int)-(((double)selected->w - DOUBLE_80332ed8) * DOUBLE_80332ed0 - DOUBLE_80332ec8);
		return true;
	}

	return false;
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
bool CMenuPcs::EquipOpen0()
{
	float fVar1;
	double dVar2;
	int timer;
	int doneCount;
	int itemCount;

	EquipMenuState* menuState = GetEquipMenuState(this);
	menuState->frame = menuState->frame + 1;
	timer = static_cast<int>(menuState->frame);
	EquipOpenAnimList* list = GetEquipListStorage(this);
	EquipOpenAnim* selected = &list->entries[menuState->selectedIndex];

	if (timer < 5) {
		selected->x = selected->x - 0x13;
	}

	doneCount = 0;
	itemCount = (int)list->listEnd - (int)list->count;
	EquipOpenAnim* item = &list->entries[list->count];

	for (int i = 0; i < itemCount; i++) {
		fVar1 = FLOAT_80332eb8;
		if (timer >= item->startFrame) {
			if (item->startFrame + item->duration <= timer) {
				doneCount = doneCount + 1;
				item->alpha = FLOAT_80332ee0;
				item->dx = FLOAT_80332eb8;
				item->dy = FLOAT_80332eb8;
			} else {
				item->step = item->step + 1;
				dVar2 = DOUBLE_80332ec0;
				item->alpha = (float)((DOUBLE_80332ec0 / (double)item->duration) * (double)item->step);
				if ((item->flags & 2) == 0) {
					fVar1 = (float)((dVar2 / (double)item->duration) * (double)item->step);
					item->dx = (item->targetX - (float)(double)item->x) * fVar1;
					item->dy = (item->targetY - (float)(double)item->y) * fVar1;
				}
			}
		}
		item++;
	}

	return itemCount == doneCount;
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

	if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
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
	if ((Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1)) {
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

	EquipMenuState* menuState = GetEquipMenuState(this);
	int mode = static_cast<int>(menuState->mode);

	if (mode == 0) {
		if ((hold & 8) != 0) {
			if (menuState->selectedIndex == 0) {
				menuState->selectedIndex = 3;
			} else {
				menuState->selectedIndex = menuState->selectedIndex - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((hold & 4) != 0) {
			if (menuState->selectedIndex < 3) {
				menuState->selectedIndex = menuState->selectedIndex + 1;
			} else {
				menuState->selectedIndex = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0xc) == 0) {
			if ((press & 0x20) != 0) {
				menuState->cursorMove = 1;
				Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
				return 1;
			}

			if ((press & 0x40) != 0) {
				menuState->cursorMove = -1;
				Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
				return 1;
			}

			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					menuState->closeRequested = 1;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
					return 1;
				}
			} else if (caravanWork->CanPlayerPutItem() == 0) {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			} else {
				menuState->mode = 1;
				menuState->step = 0;
				menuState->frame = 0;
				Sound.PlaySe(2, 0x40, 0x7f, 0);
			}
		}
	} else {
		s16* letterBuffer = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));

		if ((hold & 8) != 0) {
			s16& modeSelected = GetEquipModeSelected(menuState, mode);
			s16 selected = modeSelected;

			if (selected == 0) {
				if (menuState->scroll == 0) {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				} else {
					menuState->scroll = menuState->scroll - 1;
					Sound.PlaySe(1, 0x40, 0x7f, 0);
				}
			} else {
				modeSelected = selected - 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		} else if ((hold & 4) != 0) {
			s16& modeSelected = GetEquipModeSelected(menuState, mode);
			s16 selected = modeSelected;

			if (selected < 7) {
				modeSelected = selected + 1;
			} else if (static_cast<int>(menuState->scroll) + static_cast<int>(selected) < letterBuffer[0] - 1) {
				menuState->scroll = menuState->scroll + 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			}

			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0xc) == 0) {
			if ((press & 0x100) == 0) {
				if ((press & 0x200) != 0) {
					menuState->step = menuState->step + 1;
					menuState->frame = 0;
					CmdInit2();
					Sound.PlaySe(3, 0x40, 0x7f, 0);
				}
			} else {
				int index = static_cast<int>(menuState->scroll) +
				            static_cast<int>(GetEquipModeSelected(menuState, mode));
				s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
				int equipIndex = static_cast<int>(menuState->selectedIndex);
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
					menuState->step = menuState->step + 1;
					menuState->frame = 0;
					CmdInit2();
					Sound.PlaySe(2, 0x40, 0x7f, 0);
				}
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
	EquipMenuState* menuState = GetEquipMenuState(this);
	int mode = static_cast<int>(menuState->mode);
	int listState = static_cast<int>(menuState->listState);
	CCaravanWork* caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	EquipOpenAnimList* menuData = GetEquipListStorage(this);
	EquipOpenAnim* item = menuData->entries;
	int helpItem = -1;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	for (int i = 0; i < menuData->count; i++) {
		if (item->tex >= 0) {
			double x = (double)(float)((double)item->x - DOUBLE_80332ed8);
			double y = (double)item->u;
			double w = (double)(float)((double)item->w - DOUBLE_80332ed8);
			double h = (double)(float)((double)item->h - DOUBLE_80332ed8);
			double sx = (double)item->v;
			int tex = item->tex;

			if ((listState == 1) && (i == static_cast<int>(menuState->selectedIndex))) {
				sx = sx + h;
			}

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
			GXColor color;
			color.r = 0xff;
			color.g = 0xff;
			color.b = 0xff;
			color.a = (u8)(FLOAT_80332ee4 * item->alpha);
			GXSetChanMatColor((GXChannelID)4, color);
			MenuPcs.DrawRect(
			    0, static_cast<float>(x), static_cast<float>((double)(float)((double)item->y - DOUBLE_80332ed8)),
			    static_cast<float>(w), static_cast<float>(h), static_cast<float>(y), static_cast<float>(sx),
			    item->scale, item->scale, 0.0f);
		}
		item++;
	}

	item = menuData->entries;
	for (int i = 0; i < 4; i++) {
		if (caravanWork->m_equipment[i] >= 0) {
			int iconY = (int)((float)(item->y + 6) - FLOAT_80332ee0);
			int iconX = item->x + item->w - 0x10;
			int itemIdx = caravanWork->m_inventoryItems[caravanWork->m_equipment[i]];
			DrawSingleIcon(itemIdx, iconX, iconY, item->alpha, 0, FLOAT_80332ee0);
		}
		item++;
	}

	CFont* font = GetEquipFont(this);
	font->SetMargin(FLOAT_80332ee0);
	font->SetShadow(0);
	font->SetScale(FLOAT_80332ee8);
	font->DrawInit();

	item = menuData->entries;
	for (int i = 0; i < 4; i++) {
		if (caravanWork->m_equipment[i] >= 0) {
			u8 alpha = (u8)(FLOAT_80332ee4 * item->alpha);
			CColor color(0xff, 0xff, 0xff, alpha);
			font->SetColor(color.color);
			int itemIdx = caravanWork->m_inventoryItems[caravanWork->m_equipment[i]];
			const char* str = GetAttrStr(itemIdx);
			if ((mode == 0) && (i == static_cast<int>(menuState->selectedIndex))) {
				helpItem = itemIdx;
			}
			double textX = (double)item->x + ((double)item->w - (double)font->GetWidth(str)) * DOUBLE_80332ed0;
			double textY = (double)(item->y + 0xb);
			font->SetPosX((float)textX);
			font->SetPosY((float)(textY - (double)FLOAT_80332eec));
			font->Draw(str);
		}
		item++;
	}
	DrawInit();

	if (menuState->prevMode != 0) {
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		int drawIndex = 0;
		EquipOpenAnim* listItem = &menuData->entries[menuData->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int letterCount = letter[0];

		for (int i = menuData->count; i < menuData->listEnd; i++) {
			int tex = listItem->tex;
			if (tex >= 0) {
				double x = (double)(float)((double)listItem->x - DOUBLE_80332ed8);
				double y = (double)(float)((double)listItem->y - DOUBLE_80332ed8);
				double w = (double)(float)((double)listItem->w - DOUBLE_80332ed8);
				double h = (double)(float)((double)listItem->h - DOUBLE_80332ed8);
				double u = (double)listItem->u;
				double v = (double)listItem->v;
				double alpha = (double)listItem->alpha;

				if (i == menuData->count) {
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
					GXSetChanMatColor((GXChannelID)4, color);
					double fillWidth = (double)(float)(alpha * w);
					if ((double)FLOAT_80332eb8 < fillWidth) {
						MenuPcs.DrawRect(
						    0, static_cast<float>(x), static_cast<float>(y), static_cast<float>(fillWidth),
						    static_cast<float>(h), static_cast<float>(u), static_cast<float>(v), colors,
						    FLOAT_80332ee0, FLOAT_80332ee0, 0.0f);
						x = (double)(float)(x + fillWidth);
						u = (double)(float)(u + fillWidth);
					}
					if (((double)FLOAT_80332eb8 < fillWidth) && (fillWidth < w)) {
						colors[1].a = 0;
						colors[3].a = 0;
						double fadeWidth =
						    (double)((float)(DOUBLE_80332ec0 / (double)listItem->duration) * (float)listItem->w);
						MenuPcs.DrawRect(
						    0, static_cast<float>(x), static_cast<float>(y), static_cast<float>(fadeWidth),
						    static_cast<float>(h), static_cast<float>(u), static_cast<float>(v), colors,
						    FLOAT_80332ee0, FLOAT_80332ee0, 0.0f);
					}
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				} else if (tex == 0x37) {
					int idx = drawIndex + menuState->scroll;
					if ((idx < 1) || (letterCount <= idx)) {
						if ((idx >= letterCount) || (ChkEquipActive(idx) == 0)) {
							tex = 0x34;
							alpha = DOUBLE_80332ed0 * alpha;
						}
					} else {
						int equipped = EquipChk((int)letter[idx]);
						if ((equipped == 0) && (ChkEquipActive(idx) == 0)) {
							tex = 0x34;
							alpha = DOUBLE_80332ed0 * alpha;
						}
						if (equipped != 0) {
							int markX = (int)(x - (double)FLOAT_80332ef0);
							int markY = (int)((h - (double)FLOAT_80332ef4) * DOUBLE_80332ed0 + y);
							DrawEquipMark(markX, markY, listItem->alpha);
						}
					}
					if ((tex == 0x37) && (drawIndex == menuState->subSelectedIndex)) {
						v += h;
					}
					drawIndex++;
				}

				if (i != menuData->count) {
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
					GXColor color;
					color.r = 0xff;
					color.g = 0xff;
					color.b = 0xff;
					color.a = (u8)((double)FLOAT_80332ee4 * alpha);
					GXSetChanMatColor((GXChannelID)4, color);
					MenuPcs.DrawRect(
					    0, static_cast<float>(x), static_cast<float>(y), static_cast<float>(w), static_cast<float>(h),
					    static_cast<float>(u), static_cast<float>(v), listItem->scale, listItem->scale, 0.0f);
				}
			}
			listItem++;
		}
	}

	if (mode == 1) {
		font = GetEquipFont(this);
		font->SetMargin(FLOAT_80332ee0);
		font->SetShadow(0);
		font->SetScale(FLOAT_80332ee8);
		font->DrawInit();

		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		EquipOpenAnim* listStart = &menuData->entries[menuData->count];
		for (int i = menuData->count; i < menuData->listEnd; i++) {
			if (listStart->tex == 0x37) {
				break;
			}
			listStart++;
		}

		EquipOpenAnim* textItem = listStart;
		for (int i = 0; (i < 8) && (i + menuState->scroll < letter[0]); i++) {
			int idx = i + menuState->scroll;
			CColor color(0xff, 0xff, 0xff, (u8)(FLOAT_80332ee4 * listStart->alpha));
			font->SetColor(color.color);

			const char* str = 0;
			if (idx == 0) {
				str = GetMenuStr(0xb);
			} else if (letter[idx] >= 0) {
				int itemIdx = caravanWork->m_inventoryItems[letter[idx]];
				str = GetAttrStr(itemIdx);
				if (idx == static_cast<int>(menuState->subSelectedIndex) + static_cast<int>(menuState->scroll)) {
					helpItem = itemIdx;
				}
			}

			if (str != NULL) {
				font->GetWidth(str);
				font->SetPosX((float)(textItem->x + 0x1c));
				font->SetPosY((float)(textItem->y + 0xb) - FLOAT_80332eec);
				font->Draw(str);
			}
			textItem++;
		}

		DrawInit();

		EquipOpenAnim* iconItem = listStart;
		for (int i = 0; (i < 8) && (i + menuState->scroll < letter[0]); i++) {
			int idx = i + menuState->scroll;
			if ((idx > 0) && (letter[idx] >= 0)) {
				int iconY = (int)((float)(iconItem->y + 6) - FLOAT_80332ee0);
				int iconX = (int)(float)(iconItem->x + iconItem->w - 0x10);
				int itemIdx = caravanWork->m_inventoryItems[letter[idx]];
				DrawSingleIcon(itemIdx, iconX, iconY, listStart->alpha, 0, FLOAT_80332ee0);
			}
			iconItem++;
		}
	}

	if ((mode == 1) && (menuState->step == 1)) {
		EquipOpenAnim* listStart = &menuData->entries[menuData->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		double pos = CalcListPos(static_cast<int>(menuState->scroll), static_cast<int>(letter[0]), 0);
		if (pos > (double)FLOAT_80332eb8) {
			DrawListPosMark(static_cast<float>(listStart->x), static_cast<float>(listStart->y), static_cast<float>(pos));
		}
	}

	if (((mode == 0) && (menuState->listState == 1)) || ((mode != 0) && (menuState->step == 1))) {
		EquipOpenAnim* cursorItem;
		if (mode == 0) {
			cursorItem = &menuData->entries[menuState->selectedIndex];
		} else {
			EquipOpenAnim* listBase = &menuData->entries[menuData->count];
			cursorItem = &listBase[menuState->subSelectedIndex];
		}
		int cursorX = (int)((double)cursorItem->y + ((double)(cursorItem->h - 0x20) * DOUBLE_80332ed0));
		int frame = (int)System.m_frameCounter;
		int cursorY = (cursorItem->x - 0x14) + (frame & 7);
		DrawCursor(cursorY, cursorX, FLOAT_80332ee0);
	}

	if ((mode == 1) && (menuState->step == 1)) {
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int idx = menuState->subSelectedIndex + menuState->scroll;
		if ((idx > 0) && (idx < letter[0]) && (letter[idx] >= 0)) {
			if (EquipChk((int)letter[idx]) != 0) {
				EquipOpenAnim* listBase = &menuData->entries[menuData->count];
				EquipOpenAnim* markItem = &listBase[menuState->subSelectedIndex];
				int markX = (int)((double)markItem->x - (double)FLOAT_80332ef0);
				int markY = (int)(((double)markItem->h - (double)FLOAT_80332ef4) * DOUBLE_80332ed0 + (double)markItem->y);
				DrawEquipMark(markX, markY, markItem->alpha);
			}
		}
	}

	int listIndex = static_cast<int>(GetEquipModeSelected(menuState, mode)) + static_cast<int>(menuState->scroll);
	if ((mode == 1) && (listIndex < 1)) {
		helpItem = -1;
	}
	if (((mode == 0) && (menuState->emptySlotHelpState == 0)) && (helpItem < 0)) {
		helpItem = 0x267;
	}

	int helpEntryIndex = (mode == 1) ? menuData->count : 0;
	CColor helpColor(0xff, 0xff, 0xff,
	                 static_cast<u8>(FLOAT_80332ee4 * menuData->entries[helpEntryIndex].alpha));
	DrawHelpMessage(helpItem, m_fonts[0], 0, static_cast<int>(FLOAT_80332f00), helpColor.color, 10,
	                FLOAT_80332ee0, FLOAT_80332f18);
	if ((mode == 1) && (listIndex < 1)) {
		CColor listHelpColor(
		    0xff, 0xff, 0xff, static_cast<u8>(FLOAT_80332ee4 * menuData->entries[menuData->count].alpha));
		DrawHelpMessage(0x265, m_fonts[0], 0, static_cast<int>(FLOAT_80332f00), listHelpColor.color, 10,
		                FLOAT_80332ee0, FLOAT_80332f18);
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
	EquipMenuState* menuState = GetEquipMenuState(this);
	EquipOpenAnimList* menuData = GetEquipListStorage(this);
	int doneCount = 0;

	menuState->frame = menuState->frame + 1;
	int timer = static_cast<int>(menuState->frame);
	int itemCount = static_cast<int>(menuData->count);
	EquipOpenAnim* item = menuData->entries;

	for (int i = 0; i < itemCount; i++) {
		if (item->startFrame <= timer) {
			if (item->startFrame + item->duration <= timer) {
				doneCount++;
				item->alpha = FLOAT_80332eb8;
			} else {
				item->step = item->step + 1;
				item->alpha = (float)-((DOUBLE_80332ec0 / static_cast<double>(item->duration)) *
				                           static_cast<double>(item->step) -
				                       DOUBLE_80332ec0);
				if ((double)item->alpha < DOUBLE_80332F08) {
					item->alpha = FLOAT_80332eb8;
				}
			}
		}
		item++;
	}

	if (itemCount == doneCount) {
		item = menuData->entries;
		for (int i = 0; i < itemCount; i++) {
			item->startFrame = 0;
			item->duration = 1;
			item->alpha = FLOAT_80332eb8;
			item++;
		}
		return 1;
	}
	return 0;
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
	int mode;
	CCaravanWork* caravanWork;
	float scale;
	int state;
	EquipMenuState* menuState;
	int index;
	u32 equipCount;

	state = 0;
	menuState = GetEquipMenuState(this);
	menuState->prevMode = menuState->mode;
	mode = static_cast<int>(menuState->mode);
	if ((mode == 0) || ((mode != 0) && (menuState->step == 1))) {
		state = EquipCtrlCur();
	} else if ((mode == 1) && (menuState->step == 0)) {
		state = EquipOpen0();
		if (state != 0) {
			state = 0;
			menuState->step = menuState->step + 1;
		}
	} else if ((mode == 1) && ((menuState->step == 2) && (state = EquipClose0(), state != 0))) {
		menuState->step = 0;
		menuState->mode = 0;
		menuState->frame = 0;
		CmdInit1();
		state = 0;
	}

	scale = FLOAT_80332ee0;
	caravanWork = reinterpret_cast<CCaravanWork*>(Game.m_scriptFoodBase[0]);
	if (state != 0) {
		EquipOpenAnimList* list = GetEquipListStorage(this);
		EquipOpenAnim* entry = list->entries;
		for (index = 0; index < list->count; index++) {
			entry->alpha = scale;
			entry->scale = scale;
			entry++;
		}

		equipCount = static_cast<u32>(caravanWork->m_numCmdListSlots);
		index = 0;
		if (static_cast<int>(equipCount - 1) >= 0) {
			entry = &list->entries[equipCount - 1];
			do {
				entry->startFrame = index;
				entry->duration = 3;
				index = index + 1;
				entry--;
				equipCount = equipCount - 1;
			} while (equipCount != 0);
		}
	}
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

	EquipMenuState* menuState = GetEquipMenuState(this);
	if (menuState->initialized == '\0') {
		EquipOpenAnimList* list = GetEquipListStorage(this);
		memset(list, 0, sizeof(*list));
		fVar5 = FLOAT_80332ee0;
		EquipOpenAnim* entry = list->entries;
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
			dVar4 = DOUBLE_80332ed8;
			dVar3 = DOUBLE_80332ed0;
			dVar2 = DOUBLE_80332ec8;
			fVar1 = FLOAT_80332eb8;
			entry += 8;
			iVar11--;
		} while (iVar11 != 0);

		iVar6 = 0;
		entry = list->entries;
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

		list->count = 4;
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
		menuState->selectedIndex = 0;
		menuState->initialized = 1;
	}

	iVar6 = 0;
	menuState->frame = menuState->frame + 1;
	EquipOpenAnimList* list = GetEquipListStorage(this);
	uVar8 = (u32)list->count;
	EquipOpenAnim* entry = list->entries;
	iVar11 = static_cast<int>(menuState->frame);
	for (int i = 0; i < (int)uVar8; i++) {
		if (entry->startFrame <= iVar11) {
			if (entry->startFrame + entry->duration <= iVar11) {
				iVar6++;
				entry->alpha = FLOAT_80332ee0;
			} else {
				entry->step = entry->step + 1;
				dVar20 = (double)entry->duration;
				entry->alpha = (float)((DOUBLE_80332ec0 / dVar20) * (double)entry->step);
			}
		}
		entry++;
	}

	fVar5 = FLOAT_80332ee0;
	if (list->count == iVar6) {
		entry = list->entries;
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
		return 1;
	}
	return 0;
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
	short sVar1;
	float fVar2;
	float fVar3;
	float fVar4;
	float fVar5;
	unsigned int uVar6;
	short sVar7;
	int iVar8;
	int iVar9;
	EquipOpenAnim* psVar10;
	EquipOpenAnim* puVar12;
	EquipOpenAnim* psVar13;
	unsigned int uVar15;

	fVar5 = FLOAT_80332f14;
	fVar4 = FLOAT_80332f10;
	fVar3 = FLOAT_80332ee0;
	fVar2 = FLOAT_80332eb8;
	EquipOpenAnimList* list = GetEquipListStorage(this);
	sVar7 = 0;
	iVar8 = (int)list->count;
	psVar10 = &list->entries[iVar8];
	psVar10->tex = 0x2e;
	psVar10->x = 0xb8;
	psVar10->y = 0x28;
	iVar9 = iVar8 + 4;
	psVar10->w = 0x78;
	psVar10->h = 0x108;
	psVar10->u = fVar4;
	fVar4 = FLOAT_80332f18;
	psVar10->v = fVar5;
	psVar10->scale = fVar3;
	psVar10->startFrame = 5;
	psVar10->duration = 5;

	puVar12 = &list->entries[iVar8 + 1];
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

	puVar12 = &list->entries[iVar8 + 2];
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

	puVar12 = &list->entries[iVar8 + 3];
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

	psVar10 = &list->entries[list->count];
	iVar8 = 4;
	do {
		psVar13 = &list->entries[iVar9];
		psVar13[0].flags = 2;
		psVar13[0].tex = 0x37;
		iVar9 = iVar9 + 2;
		psVar13[0].x = psVar10->x + 0x24;
		sVar1 = sVar7 + 0x20;
		psVar13[0].y = psVar10->y + sVar7;
		psVar13[0].w = 200;
		psVar13[0].h = 0x28;
		psVar13[0].u = fVar2;
		psVar13[0].v = fVar2;
		psVar13[0].startFrame = 7;
		psVar13[0].duration = 5;

		psVar13[1].flags = 2;
		psVar13[1].tex = 0x37;
		psVar13[1].x = psVar10->x + 0x24;
		sVar7 = sVar7 + 0x40;
		psVar13[1].y = psVar10->y + sVar1;
		psVar13[1].w = 200;
		psVar13[1].h = 0x28;
		psVar13[1].u = fVar2;
		psVar13[1].v = fVar2;
		psVar13[1].startFrame = 7;
		fVar3 = FLOAT_80332eb8;
		psVar13[1].duration = 5;
		iVar8 = iVar8 - 1;
	} while (iVar8 != 0);

	list->listEnd = (short)iVar9;
	uVar6 = (unsigned int)((int)list->listEnd - (int)list->count);
	psVar10 = &list->entries[list->count];
	if (0 < (int)uVar6) {
		uVar15 = uVar6 >> 3;
		if (uVar15 != 0) {
			do {
				psVar10[0].step = 0;
				psVar10[0].alpha = fVar3;
				psVar10[1].step = 0;
				psVar10[1].alpha = fVar3;
				psVar10[2].step = 0;
				psVar10[2].alpha = fVar3;
				psVar10[3].step = 0;
				psVar10[3].alpha = fVar3;
				psVar10[4].step = 0;
				psVar10[4].alpha = fVar3;
				psVar10[5].step = 0;
				psVar10[5].alpha = fVar3;
				psVar10[6].step = 0;
				psVar10[6].alpha = fVar3;
				psVar10[7].step = 0;
				psVar10[7].alpha = fVar3;
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
			psVar10->alpha = fVar3;
			psVar10++;
			uVar6 = uVar6 - 1;
		} while (uVar6 != 0);
	}
}
