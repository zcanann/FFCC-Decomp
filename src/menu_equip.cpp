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
bool CMenuPcs::ChkEquipActive(int index)
{
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
	s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	int entryCount = entries[0];
	s16* itemEntries = entries + 1;
	int equipIndex = m_equipState->selected[0];

	if ((index < 0) || (index >= entryCount)) {
		return 0;
	}

	bool active;
	if (index == 0) {
		if (equipIndex < 3) {
			active = false;
		} else {
			active = caravanWork->m_equipment[equipIndex] >= 0;
		}
	} else {
		int item = caravanWork->m_inventoryItems[itemEntries[index - 1]];
		active = ChkEquipPossible(item);

		if (active && (GetEquipType(item) != equipIndex)) {
			active = false;
		}
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
	float moveT;
	double one;
	int doneCount;
	int timer;
	int itemCount;

	m_equipState->frame = m_equipState->frame + 1;
	timer = static_cast<int>(m_equipState->frame);
	EquipOpenAnim* selectedItem = &m_equipList->entries[m_equipState->selected[0]];
	if (7 < timer) {
		selectedItem->x = selectedItem->x + 0x13;
	}

	EquipOpenAnimList* list = m_equipList;
	doneCount = 0;
	itemCount = (int)list->listEnd - (int)list->count;
	EquipOpenAnim* item = &list->entries[list->count];
	for (int i = 0; i < itemCount; i++) {
		moveT = 0.0f;
		if (timer >= item->startFrame) {
			if (item->startFrame + item->duration <= timer) {
				doneCount = doneCount + 1;
				item->alpha = 0.0f;
				item->dx = 0.0f;
				item->dy = 0.0f;
			} else {
				item->step = item->step + 1;
				one = 1.0;
				double recip = 1.0 / (double)item->duration;
				item->alpha = (float)-(recip * (double)item->step - 1.0);
				if ((item->flags & 2) == 0) {
					moveT = (float)-((one / (double)item->duration) * (double)item->step - one);
					float dx = item->targetX - (float)item->x;
					float dy = item->targetY - (float)item->y;
					item->dx = dx * moveT;
					item->dy = dy * moveT;
				}
			}
		}
		item++;
	}

	int result = 0;
	if (itemCount == doneCount) {
		EquipOpenAnim* selected = &m_equipList->entries[m_equipState->selected[0]];
		selected->x = (s16)(int)(216.0 - (double)selected->w * 0.5);
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
	float moveT;
	double one;
	int timer;
	int doneCount;
	int itemCount;

	m_equipState->frame = m_equipState->frame + 1;
	timer = static_cast<int>(m_equipState->frame);
	EquipOpenAnim* selected = &m_equipList->entries[m_equipState->selected[0]];

	if (timer < 5) {
		selected->x = selected->x - 0x13;
	}

	doneCount = 0;
	EquipOpenAnim* item = &m_equipList->entries[m_equipList->count];
	itemCount = (int)m_equipList->listEnd - (int)m_equipList->count;

	for (int i = 0; i < itemCount; i++) {
		moveT = 0.0f;
		if (timer >= item->startFrame) {
			if (item->startFrame + item->duration <= timer) {
				doneCount = doneCount + 1;
				item->alpha = 1.0f;
				item->dx = 0.0f;
				item->dy = 0.0f;
			} else {
				item->step = item->step + 1;
				one = 1.0;
				double recip = 1.0 / (double)item->duration;
				item->alpha = (float)(recip * (double)item->step);
				if ((item->flags & 2) == 0) {
					moveT = (float)((one / (double)item->duration) * (double)item->step);
					float dx = item->targetX - (float)item->x;
					float dy = item->targetY - (float)item->y;
					item->dx = dx * moveT;
					item->dy = dy * moveT;
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
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
	int press = static_cast<s16>(Pad.GetButtonDown(0));
	int hold = static_cast<s16>(Pad.GetButtonRepeat(0));

	if (hold == 0) {
		return 0;
	}

	int mode = static_cast<int>(m_equipState->mode);

	if (mode == 0) {
		if ((hold & 8) != 0) {
			int sel = m_equipState->selected[mode];
			if (sel != 0) {
				m_equipState->selected[mode] = sel - 1;
			} else {
				m_equipState->selected[mode] = 3;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((hold & 4) != 0) {
			if (m_equipState->selected[mode] < 3) {
				m_equipState->selected[mode] = m_equipState->selected[mode] + 1;
			} else {
				m_equipState->selected[mode] = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0xc) == 0) {
			if ((press & 0x20) != 0) {
				m_equipState->cursorMove = 1;
				Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
				return 1;
			}

			if ((press & 0x40) != 0) {
				m_equipState->cursorMove = -1;
				Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
				return 1;
			}

			if ((press & 0x100) != 0) {
				if (caravanWork->CanPlayerPutItem() == 0) {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				} else {
					m_equipState->mode = 1;
					m_equipState->step = 0;
					m_equipState->frame = 0;
					Sound.PlaySe(2, 0x40, 0x7f, 0);
				}
			} else if ((press & 0x200) != 0) {
				m_equipState->closeRequested = 1;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
				return 1;
			}
		}
	} else {
		s16* letterBuffer = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int letterCount = letterBuffer[0];

		if ((hold & 8) != 0) {
			int sel = m_equipState->selected[mode];
			if (sel != 0) {
				m_equipState->selected[mode] = sel - 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else {
				int scroll = m_equipState->scroll;
				if (scroll != 0) {
					m_equipState->scroll = scroll - 1;
					Sound.PlaySe(1, 0x40, 0x7f, 0);
				} else {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				}
			}
		} else if ((hold & 4) != 0) {
			s16 selected = m_equipState->selected[mode];

			if (selected < 7) {
				m_equipState->selected[mode] = selected + 1;
			} else if (static_cast<int>(m_equipState->scroll) + static_cast<int>(selected) < letterCount - 1) {
				m_equipState->scroll = m_equipState->scroll + 1;
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			} else {
				Sound.PlaySe(4, 0x40, 0x7f, 0);
			}

			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0xc) == 0) {
			if ((press & 0x100) != 0) {
				int index = static_cast<int>(m_equipState->scroll) +
				            static_cast<int>(m_equipState->selected[mode]);
				s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
				bool valid = ChkEquipActive(index);

				if (!valid || ((index != 0) && EquipChk((int)entries[index]))) {
					Sound.PlaySe(4, 0x40, 0x7f, 0);
				} else {
					caravanWork->ChgEquipPos(m_equipState->selected[0],
					                         (index != 0) ? entries[index] : -1);
					caravanWork->CalcStatus();
					m_equipState->step = m_equipState->step + 1;
					m_equipState->frame = 0;
					CmdInit2();
					Sound.PlaySe(2, 0x40, 0x7f, 0);
				}
			} else if ((press & 0x200) != 0) {
				m_equipState->step = m_equipState->step + 1;
				m_equipState->frame = 0;
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
	int helpItem;
	int helpFound = 0;
	float w;
	float h;

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	int mode = static_cast<int>(m_equipState->mode);
	unsigned int listState = static_cast<int>(m_equipState->listState);
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
	EquipOpenAnim* item = m_equipList->entries;

	for (int i = 0; i < m_equipList->count; i++) {
		int tex = item->tex;
		if (tex >= 0) {
			float x = (float)item->x;
			float y = (float)item->y;
			w = (float)item->w;
			h = (float)item->h;
			float u = item->u;
			float v = item->v;

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

			if ((listState == 1) && (i == static_cast<int>(m_equipState->selected[0]))) {
				v = v + h;
			}

			GXColor color;
			color.r = 0xff;
			color.g = 0xff;
			color.b = 0xff;
			color.a = (u8)(int)(255.0f * item->alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);

			float scale = item->scale;
			MenuPcs.DrawRect(0, x, y, w, h, u, v, scale, scale, 0.0f);
		}
		item++;
	}

	item = m_equipList->entries;
	for (int i = 0; i < 4; i++) {
		if (caravanWork->m_equipment[i] >= 0) {
			int iconY = (int)((float)(item->y + 6) - 1.0f);
			int iconX = (int)(float)(item->x + item->w - 0x10);
			DrawSingleIcon(caravanWork->m_inventoryItems[caravanWork->m_equipment[i]], iconX, iconY,
			               item->alpha, 0, 1.0f);
		}
		item++;
	}

	CFont* font = m_fonts[4];
	font->SetMargin(1.0f);
	font->SetShadow(0);
	font->SetScale(0.9f);
	font->DrawInit();

	item = m_equipList->entries;
	for (unsigned int i = 0; i < 4; i++) {
		if (caravanWork->m_equipment[i] >= 0) {
			CColor color(0xff, 0xff, 0xff, (u8)(255.0f * item->alpha));
			font->SetColor(color.color);
			int itemIdx = caravanWork->m_inventoryItems[caravanWork->m_equipment[i]];
			char* str = Game.m_cFlatDataArr[1].TableStrings(0)[itemIdx * 5 + 4];
			if ((m_equipState->mode == 0) && (i == static_cast<int>(m_equipState->selected[0]))) {
				helpItem = itemIdx;
				helpFound = 1;
			}
			float width = font->GetWidth(str);
			float textY = (float)(item->y + 0xb);
			font->SetPosX((float)((((float)item->w - width) * 0.5) + (double)item->x));
			font->SetPosY(textY - 4.0f);
			font->Draw(str);
		}
		item++;
	}
	DrawInit();

	if (m_equipState->prevMode != 0) {
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		int drawIndex = 0;
		EquipOpenAnim* listItem = &m_equipList->entries[m_equipList->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int letterCount = letter[0];

		for (int i = m_equipList->count; i < m_equipList->listEnd; i++) {
			int tex = listItem->tex;
			if (tex >= 0) {
				float x = (float)listItem->x;
				float u = listItem->u;
				float y = (float)listItem->y;
				float v = listItem->v;
				w = (float)listItem->w;
				h = (float)listItem->h;

				if (i == m_equipList->count) {
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
					if (w > 0.0f) {
						MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, 1.0f, 1.0f, 0.0f);
						x = x + w;
						u = u + w;
					}
					if ((w > 0.0f) && (w < (float)listItem->w)) {
						colors[1].r = 0xff;
						colors[1].g = 0xff;
						colors[1].b = 0xff;
						colors[1].a = 0;
						colors[3].r = 0xff;
						colors[3].g = 0xff;
						colors[3].b = 0xff;
						colors[3].a = 0;
						w = (float)(1.0 / (double)listItem->duration) * (float)listItem->w;
						MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, 1.0f, 1.0f, 0.0f);
					}
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				} else {
					float alpha = listItem->alpha;
					if (tex == 0x37) {
						int idx = drawIndex + m_equipState->scroll;
						if ((idx < 1) || (idx >= letterCount)) {
							if ((idx >= letterCount) || !ChkEquipActive(idx)) {
								tex = 0x34;
								alpha = (float)(0.5 * (double)listItem->alpha);
							}
						} else {
							unsigned int chk = idx - 1;
							bool equipped = EquipChk((int)letter[chk + 1]);
							if (((chk + 1) >= letterCount) || equipped || !ChkEquipActive(chk + 1)) {
								if (equipped) {
									int markX = (int)(x - 12.0f);
									int markY = (int)((double)(h - 24.0f) * 0.5 + (double)y);
									DrawEquipMark(markX, markY, listItem->alpha);
								}
								tex = 0x34;
								alpha = (float)(0.5 * (double)listItem->alpha);
							}
						}
						if ((tex == 0x37) && (drawIndex == m_equipState->selected[1])) {
							v += h;
						}
						drawIndex++;
					}

					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
					GXColor color;
					color.r = 0xff;
					color.g = 0xff;
					color.b = 0xff;
					color.a = (u8)(int)(255.0f * alpha);
					GXSetChanMatColor(GX_COLOR0A0, color);
					float scale = listItem->scale;
					MenuPcs.DrawRect(0, x, y, w, h, u, v, scale, scale, 0.0f);
				}
			}
			listItem++;
		}
	}

	if (mode == 1) {
		font = m_fonts[4];
		font->SetMargin(1.0f);
		font->SetShadow(0);
		font->SetScale(0.9f);
		font->DrawInit();

		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int letterCount = letter[0];
		EquipOpenAnimList* list = m_equipList;
		EquipOpenAnim* listStart;
		for (int i = list->count; i < list->listEnd; i++) {
			listStart = &list->entries[i];
			if (listStart->tex == 0x37) {
				break;
			}
		}

		float colorMax = 255.0f;
		EquipOpenAnim* textItem = listStart;
		int idx;
		for (int i = 0; (i < 8) && ((idx = i + m_equipState->scroll) < letterCount); i++) {
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
				if (idx == static_cast<int>(m_equipState->selected[1]) + static_cast<int>(m_equipState->scroll)) {
					helpItem = itemIdx;
					helpFound = 1;
				}
			}

			font->GetWidth(str);
			float textY = (float)(textItem->y + 0xb);
			font->SetPosX((float)(textItem->x + 0x1c));
			font->SetPosY(textY - 4.0f);
			font->Draw(str);
			textItem++;
		}

		DrawInit();

		EquipOpenAnim* iconItem = listStart;
		for (int i = 0; (i < 8) && ((idx = i + m_equipState->scroll) < letterCount); i++) {
			if (idx >= 1) {
				int entry = letter[idx];
				if (entry >= 0) {
					int iconY = (int)((float)(iconItem->y + 6) - 1.0f);
					int iconX = (int)(float)(iconItem->x + iconItem->w - 0x10);
					DrawSingleIcon(caravanWork->m_inventoryItems[entry], iconX, iconY,
					               listStart->alpha, 0, 1.0f);
				}
			}
			iconItem++;
		}
	}

	if ((mode == 1) && (m_equipState->step == 1)) {
		EquipOpenAnim* listStart = &m_equipList->entries[m_equipList->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		float pos = CalcListPos(static_cast<int>(m_equipState->scroll), static_cast<int>(letter[0]), 0);
		if (pos > 0.0f) {
			DrawListPosMark((float)listStart->x, (float)listStart->y, pos);
		}
	}

	if (((mode == 0) && (listState == 1)) || ((mode != 0) && (m_equipState->step == 1))) {
		float cx;
		float cy;
		if (mode == 0) {
			EquipOpenAnim* cursorItem = &m_equipList->entries[m_equipState->selected[0]];
			cy = (float)((double)(cursorItem->h - 0x20) * 0.5 + (double)cursorItem->y);
			cx = (float)(cursorItem->x - 0x14);
		} else {
			EquipOpenAnimList* list = m_equipList;
			EquipOpenAnim* found;
			for (int i = list->count; i < list->listEnd; i++) {
				found = &list->entries[i];
				if (found->tex == 0x37) {
					break;
				}
			}
			EquipOpenAnim* cursorItem = &found[m_equipState->selected[1]];
			cy = (float)((double)(cursorItem->h - 0x20) * 0.5 + (double)cursorItem->y);
			cx = (float)(cursorItem->x - 0x14);
		}
		int cursorY = (int)cy;
		int cursorX = (int)(cx + (float)((int)System.m_frameCounter % 8));
		DrawCursor(cursorX, cursorY, 1.0f);
	}

	EquipMenuState* state = m_equipState;
	s16 endMode = state->mode;
	unsigned int listIndex = static_cast<int>(state->selected[endMode]) + static_cast<int>(state->scroll);
	int helpEntryIndex;
	if (endMode == 1) {
		helpEntryIndex = m_equipList->count;
	} else {
		helpEntryIndex = 0;
	}
	int helpAlpha = (int)(255.0f * m_equipList->entries[helpEntryIndex].alpha);
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
	int helpX = (int)(320.0f - w * 0.5f);
	float helpYf = 352.0f;
	unsigned int helpY = (int)helpYf;
	DrawHelpMessage(helpItem, helpFont, helpX, helpY, helpColor.color, 10,
	                1.0f, 3.0f);
	if (m_equipState->mode == 1) {
		int listHelpAlpha = (int)(255.0f * m_equipList->entries[m_equipList->count].alpha);
		if (listIndex < 1) {
			CColor listHelpColor(0xff, 0xff, 0xff, (u8)listHelpAlpha);
			DrawHelpMessage(0x265, helpFont, helpX, helpY, listHelpColor.color, 10,
			                1.0f, 3.0f);
		}
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

	m_equipState->frame = m_equipState->frame + 1;
	int timer = static_cast<int>(m_equipState->frame);
	int itemCount = static_cast<int>(m_equipList->count);
	EquipOpenAnim* item = m_equipList->entries;

	for (int i = 0; i < itemCount; i++) {
		if (item->startFrame <= timer) {
			if (item->startFrame + item->duration <= timer) {
				doneCount++;
				item->alpha = 0.0f;
			} else {
				item->step = item->step + 1;
				double recip = 1.0 / static_cast<double>(item->duration);
				item->alpha = (float)-(recip * static_cast<double>(item->step) - 1.0);
				if ((double)item->alpha < 0.0) {
					item->alpha = 0.0f;
				}
			}
		}
		item++;
	}

	float zeroAlpha = 0.0f;
	int result = 0;
	if (m_equipList->count == doneCount) {
		item = m_equipList->entries;
		for (int k = itemCount; k > 0; k--) {
			item->startFrame = 0;
			item->duration = 1;
			item->alpha = zeroAlpha;
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
	m_equipState->prevMode = m_equipState->mode;
	int mode = m_equipState->mode;
	int state = 0;
	if ((mode == 0) || ((mode != 0) && (m_equipState->step == 1))) {
		state = EquipCtrlCur();
	} else if ((mode == 1) && (m_equipState->step == 0)) {
		state = EquipOpen0();
		if (state != 0) {
			state = 0;
			m_equipState->step = m_equipState->step + 1;
		}
	} else if ((mode == 1) && ((m_equipState->step == 2) && ((state = EquipClose0()) != 0))) {
		m_equipState->step = 0;
		m_equipState->mode = 0;
		m_equipState->frame = 0;
		CmdInit1();
		state = 0;
	}

	if (state) {
		float one = 1.0f;
		CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];

		EquipOpenAnim* entry = m_equipList->entries;
		for (int i = 0; i < m_equipList->count; i++) {
			entry->alpha = one;
			entry->scale = one;
			entry++;
		}

		int idx = 0;
		for (int k = caravanWork->m_numCmdListSlots - 1; k >= 0; k--) {
			EquipOpenAnim* e = &m_equipList->entries[k];
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
	float zeroUV;
	double centerX;
	double half;
	float one;
	int doneCount;
	s16* letterBuffer;
	s16* entryCursor;
	s16 entryCount;
	int itemCount;
	EquipOpenAnim* entry;
	double duration;

	if ((signed char)m_equipState->initialized == 0) {
		memset(m_equipList, 0, sizeof(EquipOpenAnimList));
		one = 1.0f;
		entry = m_equipList->entries;
		for (int k = 64; k != 0; k--) {
			entry->scale = one;
			entry++;
		}

		half = 0.5;
		centerX = 216.0;
		zeroUV = 0.0f;
		int idx = 0;
		entry = m_equipList->entries;
		for (int k = 4; k != 0; k--) {
			entry->tex = 0x34;
			entry->w = 200;
			entry->h = 0x28;
			entry->x = (s16)(int)-((double)entry->w * half - centerX);
			entry->y = idx * (entry->h - 8) + 0x60;
			entry->u = zeroUV;
			entry->v = zeroUV;
			entry->startFrame = idx;
			idx++;
			entry->duration = 3;
			entry++;
		}

		m_equipList->count = 4;
		EquipInit1();
		entryCursor = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		idx = 0;
		entryCount = 0;
		int letterMax = 0x40;
		while (idx < letterMax) {
			int itemType = GetItemType(idx, 0);
			if (itemType == 1) {
				entryCursor++;
				*entryCursor = (s16)idx;
				entryCount++;
			}
			idx++;
		}

		letterBuffer = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		*letterBuffer = entryCount + 1;
		m_equipState->selected[0] = 0;
		m_equipState->initialized = 1;
	}

	doneCount = 0;
	m_equipState->frame = m_equipState->frame + 1;
	itemCount = m_equipList->count;
	entry = m_equipList->entries;
	int frameNow = static_cast<int>(m_equipState->frame);
	for (int i = 0; i < itemCount; i++) {
		if (entry->startFrame <= frameNow) {
			if (entry->startFrame + entry->duration <= frameNow) {
				doneCount++;
				entry->alpha = 1.0f;
			} else {
				entry->step = entry->step + 1;
				duration = (double)entry->duration;
				entry->alpha = (float)((1.0 / duration) * (double)entry->step);
			}
		}
		entry++;
	}

	one = 1.0f;
	int result = 0;
	if (m_equipList->count == doneCount) {
		entry = m_equipList->entries;
		for (int k = itemCount; k > 0; k--) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = one;
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
void CMenuPcs::EquipInit1()
{
	int i = (int)m_equipList->count;

	EquipOpenAnim* e = &m_equipList->entries[i++];
	e->tex = 0x2e;
	e->x = 0xb8;
	e->y = 0x28;
	e->w = 0x78;
	e->h = 0x108;
	e->u = 128.0f;
	e->v = 8.0f;
	e->scale = 1.0f;
	e->startFrame = 5;
	e->duration = 5;

	e = &m_equipList->entries[i++];
	e->tex = 0x2f;
	e->x = 0xa0;
	e->y = 0xe;
	e->w = 0x30;
	e->h = 0x30;
	e->u = 0.0f;
	e->v = 0.0f;
	e->scale = 1.0f;
	e->startFrame = 0;
	e->duration = 5;

	e = &m_equipList->entries[i++];
	e->tex = 0x2f;
	e->w = 0x30;
	e->h = 0x30;
	e->x = 0xa5;
	e->y = 0x150 - e->h;
	e->u = 0.0f;
	e->v = 0.0f;
	e->scale = 0.75f;
	e->startFrame = 0;
	e->duration = 5;

	e = &m_equipList->entries[i++];
	e->flags = 2;
	e->tex = 0x2e;
	e->x = 0xa0;
	e->y = 8;
	e->w = 0x48;
	e->h = 0x140;
	e->u = 0.0f;
	e->v = 0.0f;
	e->startFrame = 0;
	e->duration = 5;

	int yOff = 0;
	EquipOpenAnim* anchor = &m_equipList->entries[m_equipList->count];
	for (int n = 0; n < 8; n++) {
		e = &m_equipList->entries[i];
		e->flags = 2;
		e->tex = 0x37;
		e->x = anchor->x + 0x24;
		e->y = anchor->y + yOff;
		yOff += 0x20;
		e->w = 200;
		e->h = 0x28;
		e->u = 0.0f;
		e->v = 0.0f;
		e->startFrame = 7;
		e->duration = 5;
		i++;
	}

	m_equipList->listEnd = i;
	float zeroAlpha = 0.0f;
	int n = (int)m_equipList->listEnd - (int)m_equipList->count;
	EquipOpenAnim* listEntry = &m_equipList->entries[m_equipList->count];
	for (int k = n; k > 0; k--) {
		listEntry->step = 0;
		listEntry->alpha = zeroAlpha;
		listEntry++;
	}
}
