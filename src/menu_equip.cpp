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

enum {
#ifdef VERSION_GCCJGC
    EQUIP_TEX_FRAME = 0x2D,
    EQUIP_TEX_TAB = 0x2E,
    EQUIP_TEX_PLATE = 0x33,
    EQUIP_TEX_LIST = 0x36,
#else
    EQUIP_TEX_FRAME = 0x2E,
    EQUIP_TEX_TAB = 0x2F,
    EQUIP_TEX_PLATE = 0x34,
    EQUIP_TEX_LIST = 0x37,
#endif
};

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
 * EN Address: 0x8015A1D4
 * EN Size: 268b
 * JP Address: 0x80155A1C
 * JP Size: 268b
 */
bool CMenuPcs::ChkEquipActive(int index)
{
	int item;
	int equipIndex;
	bool active;
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
	s16* entries = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
	int entryCount = entries[0];
	s16* itemEntries = entries + 1;
	equipIndex = m_equipState->selected[0];

	if ((index < 0) || (index >= entryCount)) {
		return 0;
	}

	if (index == 0) {
		if (equipIndex < 3) {
			active = false;
		} else {
			active = caravanWork->m_equipment[equipIndex] >= 0;
		}
	} else {
		item = caravanWork->m_inventoryItems[*(itemEntries + index - 1)];
		active = ChkEquipPossible(item);

		if (active) {
			int itemType = GetEquipType(item);
			if (itemType != equipIndex) {
				active = false;
			}
		}
	}

	return active;
}

/*
 * --INFO--
 * PAL Address: 0x8015b264
 * PAL Size: 516b
 * EN Address: 0x8015A2E0
 * EN Size: 516b
 * JP Address: 0x80155B28
 * JP Size: 532b
 */
int CMenuPcs::EquipClose0()
{
	float moveT;
	EquipOpenAnim* item;
	int timer;
	int itemCount;
	int doneCount;

	m_equipState->frame = m_equipState->frame + 1;
	timer = static_cast<int>(m_equipState->frame);
	EquipOpenAnim* selectedItem = &m_equipList->entries[m_equipState->selected[0]];
	if (7 < timer) {
		selectedItem->x = selectedItem->x + 0x13;
	}

	doneCount = 0;
	item = &m_equipList->entries[m_equipList->count];
	itemCount = (int)m_equipList->listEnd - (int)m_equipList->count;
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
				double recip = 1.0 / (double)item->duration;
				item->alpha = (float)-(recip * (double)item->step - 1.0);
				if ((item->flags & 2) == 0) {
					recip = 1.0 / (double)item->duration;
					moveT = (float)-(recip * (double)item->step - 1.0);
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
		selected->x = (s16)(216.0 - selected->w / 2.0);
		result = 1;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015b468
 * PAL Size: 432b
 * EN Address: 0x8015A4E4
 * EN Size: 432b
 * JP Address: 0x80155D3C
 * JP Size: 444b
 */
int CMenuPcs::EquipOpen0()
{
	EquipOpenAnim* item;
	float moveT;
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
	item = &m_equipList->entries[m_equipList->count];
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
				double recip = 1.0 / (double)item->duration;
				item->alpha = (float)(recip * (double)item->step);
				if ((item->flags & 2) == 0) {
					recip = 1.0 / (double)item->duration;
					moveT = (float)(recip * (double)item->step);
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
 * EN Address: 0x8015A694
 * EN Size: 1592b
 * JP Address: 0x80155EF8
 * JP Size: 1592b
 */
int CMenuPcs::EquipCtrlCur()
{
	CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
	s16 hold;
	s16 press = Pad.GetButtonDown(0);
	hold = Pad.GetButtonRepeat(0);

	if (hold == 0) {
		return 0;
	}

	int mode = static_cast<int>(m_equipState->mode);

	if (mode == 0) {
		if ((hold & 8) != 0) {
			if (m_equipState->selected[mode] != 0) {
				m_equipState->selected[mode]--;
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
			EquipMenuState* state = m_equipState;
			if (state->selected[mode] < 7) {
				state->selected[mode]++;
			} else if (state->scroll + state->selected[mode] < letterCount - 1) {
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
 * EN Address: 0x8015ACCC
 * EN Size: 4280b
 * JP Address: 0x80156530
 * JP Size: 4260b
 */
void CMenuPcs::EquipDraw()
{
	float textY;
	int helpItem;
	int helpFound = 0;
	int mode;
	int listState;
	CCaravanWork* caravanWork;
	EquipOpenAnim* item;
	float x;
	float y;
	float w;
	float h;
	float u;
	float v;
	GXColor colors[4];

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	mode = static_cast<int>(m_equipState->mode);
	listState = static_cast<int>(m_equipState->listState);
	caravanWork = Game.m_scriptFoodBase[0];
	item = m_equipList->entries;

	for (int i = 0; i < m_equipList->count; i++, item++) {
		int tex = item->tex;
		if (tex >= 0) {
			x = (float)item->x;
			y = (float)item->y;
			w = (float)item->w;
			h = (float)item->h;
			u = item->u;
			v = item->v;

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));

			if ((listState == 1) && (i == static_cast<int>(m_equipState->selected[0]))) {
				v = v + h;
			}

			colors[0].r = 0xff;
			colors[0].g = 0xff;
			colors[0].b = 0xff;
			colors[0].a = (u8)(int)(255.0f * item->alpha);
			GXSetChanMatColor(GX_COLOR0A0, colors[0]);

			float scale = item->scale;
			MenuPcs.DrawRect(0, x, y, w, h, u, v, scale, scale, 0.0f);
		}
	}

	item = m_equipList->entries;
	for (int i = 0; i < 4; i++, item++) {
		if (caravanWork->m_equipment[i] >= 0) {
			int iconY = (int)((float)(item->y + 6) - 1.0f);
			int iconX = (int)(float)(item->x + item->w - 0x10);
			DrawSingleIcon(caravanWork->m_inventoryItems[caravanWork->m_equipment[i]], iconX, iconY,
			               item->alpha, 0, 1.0f);
		}
	}

	CFont* font = GetFontItem();
	font->SetMargin(1.0f);
	font->SetShadow(0);
	font->SetScale(0.9f);
	font->DrawInit();

	item = m_equipList->entries;
	for (int i = 0; i < 4; i++, item++) {
		if (caravanWork->m_equipment[i] >= 0) {
			font->SetColor(CColor(0xff, 0xff, 0xff, (u8)(255.0f * item->alpha)).color);
			int itemIdx = caravanWork->m_inventoryItems[caravanWork->m_equipment[i]];
			char* str = Game.GetShortItemName(itemIdx);
			if ((m_equipState->mode == 0) && (i == static_cast<int>(m_equipState->selected[0]))) {
				helpFound = 1;
				helpItem = itemIdx;
			}
			float width = font->GetWidth(str);
			textY = (float)(item->y + 0xb);
			font->SetPosX((float)((((float)item->w - width) / 2.0) + (double)item->x));
#ifdef VERSION_GCCJGC
			font->SetPosY(textY);
#else
			font->SetPosY(textY - 4.0f);
#endif
			font->Draw(str);
		}
	}
	DrawInit();

	if (m_equipState->prevMode != 0) {
		MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
		int drawIndex = 0;
		item = &m_equipList->entries[m_equipList->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int letterCount = letter[0];

		for (int i = m_equipList->count; i < m_equipList->listEnd; i++) {
			int tex = item->tex;
			if (tex >= 0) {
				x = (float)item->x;
				u = item->u;
				y = (float)item->y;
				v = item->v;
				w = (float)item->w;
				h = (float)item->h;

				if (i == m_equipList->count) {
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(1));
					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(item->tex));
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
					w = item->alpha * w;
					if (w > 0.0f) {
						MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, 1.0f, 1.0f, 0.0f);
						x = x + w;
						u = u + w;
					}
					if ((w > 0.0f) && (w < (float)item->w)) {
						colors[1].r = 0xff;
						colors[1].g = 0xff;
						colors[1].b = 0xff;
						colors[1].a = 0;
						colors[3].r = 0xff;
						colors[3].g = 0xff;
						colors[3].b = 0xff;
						colors[3].a = 0;
						w = (float)(1.0 / (double)item->duration);
						w = w * item->w;
						MenuPcs.DrawRect(0, x, y, w, h, u, v, colors, 1.0f, 1.0f, 0.0f);
					}
					MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
				} else {
					float alpha = item->alpha;
					int texId = tex;
					if (tex == EQUIP_TEX_LIST) {
						int idx = drawIndex + m_equipState->scroll;
						if ((idx < 1) || (idx >= letterCount)) {
							if ((idx >= letterCount) || !ChkEquipActive(idx)) {
								texId = EQUIP_TEX_PLATE;
								alpha = (float)(0.5 * (double)item->alpha);
							}
						} else {
							int chk = idx - 1;
							bool equipped = EquipChk((int)letter[chk + 1]);
							if (((chk + 1) >= letterCount) || equipped || !ChkEquipActive(chk + 1)) {
								if (equipped) {
									int markX = (int)(x - 12.0f);
									int markY = (int)((double)(h - 24.0f) / 2.0 + (double)y);
									DrawEquipMark(markX, markY, item->alpha);
								}
								texId = EQUIP_TEX_PLATE;
								alpha = (float)(0.5 * (double)item->alpha);
							}
						}
						if ((texId == EQUIP_TEX_LIST) && (drawIndex == m_equipState->selected[1])) {
							v += h;
						}
						drawIndex++;
					}

					MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(texId));
					colors[0].r = 0xff;
					colors[0].g = 0xff;
					colors[0].b = 0xff;
					colors[0].a = (u8)(int)(255.0f * alpha);
					GXSetChanMatColor(GX_COLOR0A0, colors[0]);
					float scale = item->scale;
					MenuPcs.DrawRect(0, x, y, w, h, u, v, scale, scale, 0.0f);
				}
			}
			item++;
		}
	}

	if (mode == 1) {
		font = GetFontItem();
		font->SetMargin(1.0f);
		font->SetShadow(0);
		font->SetScale(0.9f);
		font->DrawInit();

		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		int letterCount = letter[0];
		for (int i = m_equipList->count; i < m_equipList->listEnd; i++) {
			item = &m_equipList->entries[i];
			if (item->tex == EQUIP_TEX_LIST) {
				break;
			}
		}

		EquipOpenAnim* textItem = item;
		int idx;
		for (int i = 0; (i < 8) && ((idx = i + m_equipState->scroll) < letterCount); textItem++, i++) {
			font->SetColor(CColor(0xff, 0xff, 0xff, (u8)(255.0f * item->alpha)).color);

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
				str = Game.GetShortItemName(itemIdx);
				if (idx == static_cast<int>(m_equipState->selected[1]) + static_cast<int>(m_equipState->scroll)) {
					helpItem = itemIdx;
					helpFound = 1;
				}
			}

			font->GetWidth(str);
			textY = (float)(textItem->y + 0xb);
			font->SetPosX((float)(textItem->x + 0x1c));
#ifdef VERSION_GCCJGC
			font->SetPosY(textY);
#else
			font->SetPosY(textY - 4.0f);
#endif
			font->Draw(str);
		}

		DrawInit();

		EquipOpenAnim* iconItem = item;
		for (int i = 0; (i < 8) && ((idx = i + m_equipState->scroll) < letterCount); iconItem++, i++) {
			if (idx >= 1) {
				int entry = letter[idx];
				if (entry >= 0) {
					int iconY = (int)((float)(iconItem->y + 6) - 1.0f);
					int iconX = (int)(float)(iconItem->x + iconItem->w - 0x10);
					DrawSingleIcon(caravanWork->m_inventoryItems[entry], iconX, iconY,
					               item->alpha, 0, 1.0f);
				}
			}
		}
	}

	if ((mode == 1) && (m_equipState->step == 1)) {
		item = &m_equipList->entries[m_equipList->count];
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		float pos = CalcListPos(static_cast<int>(m_equipState->scroll), static_cast<int>(letter[0]), 0);
		if (pos > 0.0f) {
			DrawListPosMark((float)item->x, (float)item->y, pos);
		}
	}

	if (((mode == 0) && (listState == 1)) || ((mode != 0) && (m_equipState->step == 1))) {
		float cx;
		float cy;
		if (mode == 0) {
			EquipOpenAnim* cursorItem = &m_equipList->entries[m_equipState->selected[0]];
			cx = (float)(cursorItem->x - 0x14);
			cy = (float)((cursorItem->h - 0x20) / 2.0 + cursorItem->y);
		} else {
			for (int i = m_equipList->count; i < m_equipList->listEnd; i++) {
				item = &m_equipList->entries[i];
				if (m_equipList->entries[i].tex == EQUIP_TEX_LIST) {
					break;
				}
			}
			item += m_equipState->selected[1];
			cx = (float)(item->x - 0x14);
			cy = (float)((item->h - 0x20) / 2.0 + item->y);
		}
		cx += (float)((int)System.GetCounter() % 8);
		DrawCursor((int)cx, (int)cy, 1.0f);
	}

	EquipMenuState* state = m_equipState;
	s16 endMode = state->mode;
	int listIndex = static_cast<int>(state->selected[endMode]) + static_cast<int>(state->scroll);
	int helpEntryIndex;
	if (endMode == 1) {
		helpEntryIndex = m_equipList->count;
	} else {
		helpEntryIndex = 0;
	}
	CFont* helpFont = m_fonts[0];
	item = &m_equipList->entries[helpEntryIndex];
	int helpAlpha = (int)(255.0f * item->alpha);
	if (!helpFound) {
		helpItem = -1;
	}
	if ((listIndex < 1) && (endMode == 1)) {
		helpItem = -1;
	}
	if (((endMode == 0) && (state->emptySlotHelpState == 0)) && (helpItem == -1)) {
		helpItem = 0x267;
	}

	float helpY = 352.0f;
	DrawHelpMessage(helpItem, helpFont, (int)(320.0f - w / 2), (int)helpY, CColor(0xff, 0xff, 0xff, (u8)helpAlpha).color, 10,
	                1.0f, 3.0f);
	if (m_equipState->mode == 1) {
		item = &m_equipList->entries[m_equipList->count];
		int listHelpAlpha = (int)(255.0f * item->alpha);
		if (listIndex < 1) {
			DrawHelpMessage(0x265, helpFont, (int)(320.0f - w / 2), (int)helpY, CColor(0xff, 0xff, 0xff, (u8)listHelpAlpha).color, 10,
			                1.0f, 3.0f);
		}
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015cd08
 * PAL Size: 428b
 * EN Address: 0x8015BD84
 * EN Size: 428b
 * JP Address: 0x801575D4
 * JP Size: 460b
 */
int CMenuPcs::EquipClose()
{
	EquipOpenAnim* item;
	int doneCount = 0;
	int i;

	m_equipState->frame = m_equipState->frame + 1;
	int itemCount = static_cast<int>(m_equipList->count);
	int timer = static_cast<int>(m_equipState->frame);
	item = m_equipList->entries;

	for (i = 0; i < itemCount; i++) {
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

	int result = 0;
	if (m_equipList->count == doneCount) {
		item = m_equipList->entries;
		for (i = 0; i < itemCount; i++, item++) {
			item->startFrame = 0;
			item->duration = 1;
			item->alpha = 0.0f;
		}
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 356b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::EquipInit0()
{
	int i;
	EquipOpenAnim* entry;
	int idx;
	int itemCount;
	CCaravanWork* caravanWork;

	caravanWork = Game.m_scriptFoodBase[0];
	entry = m_equipList->entries;
	for (i = 0; i < m_equipList->count; i++) {
		entry->alpha = 1.0f;
		entry->scale = 1.0f;
		entry++;
	}

	itemCount = caravanWork->m_numCmdListSlots;
	idx = 0;
	for (int k = itemCount - 1; k >= 0; k--) {
		entry = &m_equipList->entries[k];
		entry->startFrame = idx++;
		entry->duration = 3;
	}
}

/*
 * --INFO--
 * PAL Address: 0x8015ceb4
 * PAL Size: 596b
 * EN Address: 0x8015BF30
 * EN Size: 596b
 * JP Address: 0x801577A0
 * JP Size: 600b
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
		EquipInit0();
	}
	return state;
}


/*
 * --INFO--
 * PAL Address: 0x8015d108
 * PAL Size: 948b
 * EN Address: 0x8015C184
 * EN Size: 948b
 * JP Address: 0x801579F8
 * JP Size: 1032b
 */
int CMenuPcs::EquipOpen()
{
	int doneCount;
	s16* letterBuffer;
	int itemCount;
	EquipOpenAnim* entry;
	double duration;

	if ((signed char)m_equipState->initialized == 0) {
		memset(m_equipList, 0, sizeof(EquipOpenAnimList));
		entry = m_equipList->entries;
		for (int i = 0; i < 64; i++, entry++) {
			entry->scale = 1.0f;
		}

		entry = m_equipList->entries;
		for (int i = 0; i < 4; i++, entry++) {
			entry->tex = EQUIP_TEX_PLATE;
			entry->w = 200;
			entry->h = 0x28;
			entry->x = (s16)(216.0 - entry->w / 2.0);
			entry->y = i * (entry->h - 8) + 0x60;
			entry->u = 0.0f;
			entry->v = 0.0f;
			entry->startFrame = i;
			entry->duration = 3;
		}

		m_equipList->count = 4;
		EquipInit1();
		s16 entryCount;
		int i;
		s16* letter = reinterpret_cast<s16*>(Joybus.GetLetterBuffer(0));
		s16* entryCursor = letter;
		for (i = entryCount = 0; i < 0x40; i++) {
			if (GetItemType(i, 0) == 1) {
				entryCursor++;
				*entryCursor = (s16)i;
				entryCount++;
			}
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

	int result = 0;
	if (m_equipList->count == doneCount) {
		entry = m_equipList->entries;
		for (int i = 0; i < itemCount; i++, entry++) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = 1.0f;
		}
		result = 1;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015d4bc
 * PAL Size: 732b
 * EN Address: 0x8015C538
 * EN Size: 732b
 * JP Address: 0x80157E00
 * JP Size: 804b
 */
void CMenuPcs::EquipInit1()
{
	int n;
	EquipOpenAnim* listEntry;
	int k;

	int i = (int)m_equipList->count;

	EquipOpenAnim* e = &m_equipList->entries[i++];
	e->tex = EQUIP_TEX_FRAME;
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
	e->tex = EQUIP_TEX_TAB;
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
	e->tex = EQUIP_TEX_TAB;
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
	e->tex = EQUIP_TEX_FRAME;
	e->x = 0xa0;
	e->y = 8;
	e->w = 0x48;
	e->h = 0x140;
	e->u = 0.0f;
	e->v = 0.0f;
	e->startFrame = 0;
	e->duration = 5;

	EquipOpenAnim* anchor = &m_equipList->entries[m_equipList->count];
	for (n = 0; n < 8; n++) {
		e = &m_equipList->entries[i++];
		e->flags = 2;
		e->tex = EQUIP_TEX_LIST;
		e->x = anchor->x + 0x24;
		e->y = anchor->y + n * 0x20;
		e->w = 200;
		e->h = 0x28;
		e->u = 0.0f;
		e->v = 0.0f;
		e->startFrame = 7;
		e->duration = 5;
	}

	m_equipList->listEnd = i;
	n = (int)m_equipList->listEnd - (int)m_equipList->count;
	listEntry = &m_equipList->entries[m_equipList->count];
	for (k = n; k > 0; k--) {
		listEntry->step = 0;
		listEntry->alpha = 0.0f;
		listEntry++;
	}
}
