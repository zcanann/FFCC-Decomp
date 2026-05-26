#include "ffcc/menu_lst.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

extern const float FLOAT_803333D0;
extern const double DOUBLE_803333E8;
extern const float FLOAT_803333F0;
extern const double DOUBLE_80333410;
extern const double DOUBLE_80333418;
extern const double DOUBLE_80333420;

STATIC_ASSERT(offsetof(CMenuPcs, listFont) == 0x108);
STATIC_ASSERT(offsetof(CMenuPcs, helpFont) == 0xF8);
STATIC_ASSERT(offsetof(CMenuPcs, lstState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, lstData) == 0x850);
STATIC_ASSERT(offsetof(MenuLstEntry, tex) == 0x1C);
STATIC_ASSERT(offsetof(MenuLstEntry, timer) == 0x20);
STATIC_ASSERT(offsetof(MenuLstEntry, startFrame) == 0x24);
STATIC_ASSERT(offsetof(MenuLstEntry, duration) == 0x28);
STATIC_ASSERT(offsetof(MenuLstEntry, unk_2C) == 0x2C);
STATIC_ASSERT(sizeof(MenuLstEntry) == 0x40);
STATIC_ASSERT(sizeof(MenuLstList) == 0x1008);
STATIC_ASSERT(offsetof(MenuLstState, initialized) == 0xB);
STATIC_ASSERT(offsetof(MenuLstState, closeRequested) == 0xD);
STATIC_ASSERT(offsetof(MenuLstState, mode) == 0x10);
STATIC_ASSERT(offsetof(MenuLstState, frame) == 0x22);
STATIC_ASSERT(offsetof(MenuLstState, cursor) == 0x26);

/*
 * --INFO--
 * PAL Address: 0x8017474c
 * PAL Size: 1436b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::MLstDraw()
{
	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	short menuMode = this->lstState->mode;
	MenuLstEntry* item = this->lstData->entries;

	for (int i = 0; i < this->lstData->count; i++) {
		int tex = item->tex;
		if (tex >= 0) {
			float x = (float)item->x;
			float y = (float)item->y;
			float w = (float)item->width;
			float h = (float)item->height;
			float alpha = item->alpha;
			float z = item->z;

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
			GXColor color;
			color.r = 0xff;
			color.g = 0xff;
			color.b = 0xff;
			color.a = (unsigned char)(255.0f * alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);

			float v = 0.0f;
			if ((menuMode == 1) && (i == this->lstState->cursor)) {
				x = (float)(x + 20.0);
				v += (float)((double)item->height);
			}

			MenuPcs.DrawRect(0, x, y, w, h, 0.0f, v, z, z, 0.0f);

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x5c));
			float iconX = (float)item->x;
			float iconY = (float)(item->y - 6);
			v = 0.0f;
			if ((menuMode == 1) && (i == this->lstState->cursor)) {
				v += (float)((double)item->height);
			}
			MenuPcs.DrawRect(
				0,
				iconX - 20.0f,
				iconY,
				40.0f,
				40.0f,
				0.0f,
				v,
				z,
				z,
				0.0f);
		}
		item++;
	}

	CFont* font = this->listFont;
	font->SetMargin(1.0f);
	font->SetShadow(0);
	font->SetScale(1.0f);
	font->DrawInit();

	item = this->lstData->entries;
	for (int i = 0; i < this->lstData->count; i++) {
		CColor color(0xff, 0xff, 0xff, (unsigned char)(255.0f * item->alpha));
		font->SetColor(color.color);

		const char* text = GetMenuStr(i + 0x2e);
		font->GetWidth(text);

		float textX = (float)(item->x + 0x28);
		float textY = (float)(item->y + 3);
		if ((menuMode == 1) && (i == this->lstState->cursor)) {
			textX = (float)(textX + 20.0);
		}

		font->SetPosX(textX);
		font->SetPosY(textY - 4.0f);
		font->Draw(text);

		item++;
	}

	DrawInit();
	if (menuMode == 1) {
		MenuLstEntry* curItem = &this->lstData->entries[this->lstState->cursor];
		float cursorYOffset = (float)((double)(float)(curItem->height - 0x20) * 0.5);
		int cursorY = (int)((float)curItem->y + cursorYOffset);
		int cursorX = (int)((float)(curItem->x - 0x38) + (float)(System.m_frameCounter % 8));
		DrawCursor(cursorX, cursorY, 1.0f);
	}

	DrawInit();
	int helpMessageId = this->lstState->cursor + 0x25c;
	CFont* helpFont = this->helpFont;
	CColor helpColor(0xff, 0xff, 0xff, (unsigned char)(255.0f * this->lstData->entries[0].alpha));
	float helpX = (float)-((40.0f * (double)0.5f) - (double)320.0f);
	float helpY = 352.0f;
	DrawHelpMessage(
		helpMessageId,
		helpFont,
		(int)helpX,
		(int)helpY,
		helpColor.color,
		0x0a,
		1.0f,
		3.0f);
}

/*
 * --INFO--
 * PAL Address: 0x80174ce8
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
int CMenuPcs::MLstClose()
{
	float zero;
	MenuLstEntry* entry;
	int completedItems;
	unsigned int itemCount;
	int currentFrame;
	unsigned int count;
	int result;

	completedItems = 0;
	this->lstState->frame = this->lstState->frame + 1;
	itemCount = (unsigned int)this->lstData->count;
	entry = this->lstData->entries;
	currentFrame = (int)this->lstState->frame;
	for (int remaining = itemCount; remaining > 0; remaining--) {
		if (entry->startFrame <= currentFrame) {
			if (entry->startFrame + entry->duration <= currentFrame) {
				completedItems++;
				entry->alpha = FLOAT_803333D0;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = DOUBLE_80333410 / (double)entry->duration;
				entry->alpha = (float)(DOUBLE_80333410 - ratio * (double)entry->timer);
				if ((double)entry->alpha < DOUBLE_80333418) {
					entry->alpha = FLOAT_803333D0;
				}
			}
		}
		entry++;
	}
	result = 0;
	if (this->lstData->count == completedItems) {
		zero = FLOAT_803333D0;
		entry = this->lstData->entries;
		if ((int)itemCount > 0) {
			count = itemCount >> 3;
			for (; count != 0; count--) {
				entry[0].startFrame = 0;
				entry[0].duration = 1;
				entry[0].alpha = zero;
				entry[1].startFrame = 0;
				entry[1].duration = 1;
				entry[1].alpha = zero;
				entry[2].startFrame = 0;
				entry[2].duration = 1;
				entry[2].alpha = zero;
				entry[3].startFrame = 0;
				entry[3].duration = 1;
				entry[3].alpha = zero;
				entry[4].startFrame = 0;
				entry[4].duration = 1;
				entry[4].alpha = zero;
				entry[5].startFrame = 0;
				entry[5].duration = 1;
				entry[5].alpha = zero;
				entry[6].startFrame = 0;
				entry[6].duration = 1;
				entry[6].alpha = zero;
				entry[7].startFrame = 0;
				entry[7].duration = 1;
				entry[7].alpha = zero;
				entry += 8;
			}
			itemCount &= 7;
			if (itemCount != 0) {
				do {
					entry->startFrame = 0;
					entry->duration = 1;
					entry->alpha = zero;
					entry++;
					itemCount--;
				} while (itemCount != 0);
			}
		}
		result = 1;
	}

	return result;
}

/*
 * --INFO--
 * PAL Address: 0x80174e94
 * PAL Size: 892b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::MLstCtrl()
{
	bool blocked;
	float one;
	unsigned int press;
	u16 hold;
	unsigned int itemCount;
	unsigned int chunkCount;
	int i;
	int startFrame;
	int duration;
	int padLock;
	int result;

	blocked = false;
	padLock = Pad._452_4_;
	if ((padLock != 0) || (Pad._448_4_ != -1)) {
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
	if ((padLock != 0) || (Pad._448_4_ != -1)) {
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
		result = 0;
	} else {
		if ((hold & 0x48) != 0) {
			if (this->lstState->cursor != 0) {
				this->lstState->cursor = this->lstState->cursor - 1;
			} else {
				this->lstState->cursor = 8;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((hold & 0x24) != 0) {
			if (this->lstState->cursor < 8) {
				this->lstState->cursor = this->lstState->cursor + 1;
			} else {
				this->lstState->cursor = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0x6c) == 0) {
			if ((press & 0x100) != 0) {
				Sound.PlaySe(2, 0x40, 0x7f, 0);
				result = 1;
			} else if ((press & 0x200) != 0) {
				this->lstState->closeRequested = (char)0xFF;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
				result = 1;
			} else {
				result = 0;
			}
		} else {
			result = 0;
		}
	}

	if (result != 0) {
		one = 1.0f;
		MenuLstEntry* entry = this->lstData->entries;
		for (i = 0; (itemCount = (unsigned int)this->lstData->count), i < (int)itemCount; i++) {
			entry->alpha = one;
			entry->z = one;
			entry++;
		}

		startFrame = 0;
		duration = 4;
		for (int idx = this->lstData->count - 1; idx >= 0; idx--) {
			MenuLstEntry* closeEntry = &this->lstData->entries[idx];
			closeEntry->startFrame = startFrame++;
			closeEntry->duration = duration;
		}

		this->lstState->frame = 0;
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: 0x80175210
 * PAL Size: 720b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO  
 * JP Size: TODO
 */
int CMenuPcs::MLstOpen()
{
	float one;
	float zero;
	int completedItems;
	MenuLstEntry* entry;
	unsigned int itemCount;
	int currentFrame;
	unsigned int count;

	if (this->lstState->initialized == '\0') {
		int i;
		short initializedCount;
		short yPos;

		memset(this->lstData, 0, sizeof(MenuLstList));
		one = 1.0f;
		entry = this->lstData->entries;
		i = 8;
		do {
			entry[0].z = one;
			entry[1].z = one;
			entry[2].z = one;
			entry[3].z = one;
			entry[4].z = one;
			entry[5].z = one;
			entry[6].z = one;
			entry[7].z = one;
			entry += 8;
			i--;
		} while (i != 0);

		zero = 0.0f;
		initializedCount = 0;
		yPos = 0x18;
		for (i = 0; i < 9; i++) {
			entry = &this->lstData->entries[i];
			entry->unk_2C = 2;
			initializedCount++;
			entry->tex = 0x5B;
			entry->width = 0xE0;
			entry->height = 0x28;
			entry->x = (short)(int)-(((double)entry->width * DOUBLE_803333E8) - DOUBLE_80333420);
			entry->y = yPos;
			yPos += 0x20;
			entry->s = zero;
			entry->t = zero;
			entry->startFrame = i;
			entry->duration = 4;
		}
		this->lstData->count = initializedCount;
		this->lstState->initialized = 1;
	}

	completedItems = 0;
	this->lstState->frame = this->lstState->frame + 1;
	itemCount = (unsigned int)this->lstData->count;
	entry = this->lstData->entries;
	currentFrame = (int)this->lstState->frame;
	for (int remaining = itemCount; remaining > 0; remaining--) {
		if (entry->startFrame <= currentFrame) {
			if (entry->startFrame + entry->duration <= currentFrame) {
				completedItems++;
				entry->alpha = 1.0f;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = DOUBLE_80333410 / (double)entry->duration;
				entry->alpha = (float)(ratio * (double)entry->timer);
			}
		}
		entry++;
	}

	int result = 0;
	if (this->lstData->count == completedItems) {
		one = 1.0f;
		entry = this->lstData->entries;
		if ((int)itemCount > 0) {
			count = itemCount >> 3;
			for (; count != 0; count--) {
				entry[0].startFrame = 0;
				entry[0].duration = 1;
				entry[0].alpha = one;
				entry[1].startFrame = 0;
				entry[1].duration = 1;
				entry[1].alpha = one;
				entry[2].startFrame = 0;
				entry[2].duration = 1;
				entry[2].alpha = one;
				entry[3].startFrame = 0;
				entry[3].duration = 1;
				entry[3].alpha = one;
				entry[4].startFrame = 0;
				entry[4].duration = 1;
				entry[4].alpha = one;
				entry[5].startFrame = 0;
				entry[5].duration = 1;
				entry[5].alpha = one;
				entry[6].startFrame = 0;
				entry[6].duration = 1;
				entry[6].alpha = one;
				entry[7].startFrame = 0;
				entry[7].duration = 1;
				entry[7].alpha = one;
				entry += 8;
			}
			itemCount &= 7;
			if (itemCount != 0) {
				do {
					entry->startFrame = 0;
					entry->duration = 1;
					entry->alpha = one;
					entry++;
					itemCount--;
				} while (itemCount != 0);
			}
		}
		result = 1;
	}
	return result;
}
