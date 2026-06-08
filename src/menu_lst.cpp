#include "ffcc/menu_lst.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

static const float kMLstZero = 0.0f;
static const float kMLstColorMax = 255.0f;
static const double kMLstSelectedOffsetX = 20.0;
static const float kMLstRowHeight = 40.0f;
static const double kMLstHalfDouble = 0.5;
static const float kMLstOne = 1.0f;
static const float kMLstTextYOffset = 4.0f;
static const float kMLstHelpCenterX = 320.0f;
static const float kMLstHalf = 0.5f;
static const float kMLstHelpY = 352.0f;
static const float kMLstHelpScale = 3.0f;
static const double kMLstIntToDoubleBias = 4503601774854144.0;
static const double kMLstOneDouble = 1.0;
static const double kMLstZeroDouble = 0.0;
static const double kMLstWindowCenterX = 216.0;

STATIC_ASSERT(offsetof(CMenuPcs, m_fonts) == 0xF8);
STATIC_ASSERT(offsetof(CMenuPcs, m_menuLstState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_menuLstList) == 0x850);
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

	short menuMode = this->m_menuLstState->mode;
	MenuLstEntry* item = this->m_menuLstList->entries;
	float rowHeight = kMLstRowHeight;

	for (int i = 0; i < this->m_menuLstList->count; i++) {
		int tex = item->tex;
		if (tex >= 0) {
			float x = (float)item->x;
			float zero = kMLstZero;
			float v = zero;
			float y = (float)item->y;
			float w = (float)item->width;
			float h = (float)item->height;
			float alpha = item->alpha;

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
			GXColor color;
			color.r = 0xff;
			color.g = 0xff;
			color.b = 0xff;
			color.a = (unsigned char)(255.0f * alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);

			if ((menuMode == 1) && (i == this->m_menuLstState->cursor)) {
				x = (float)(x + 20.0);
				v += (float)item->height;
			}

			MenuPcs.DrawRect(0, x, y, w, h, zero, v, item->z, item->z, zero);

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x5c));
			float iconX = (float)((double)item->x - kMLstRowHeight * kMLstHalfDouble);
			float iconY = (float)(item->y - 6);
			v = zero;
			if ((menuMode == 1) && (i == this->m_menuLstState->cursor)) {
				v += (float)item->height;
			}
			MenuPcs.DrawRect(
				0,
				iconX,
				iconY,
				rowHeight,
				rowHeight,
				zero,
				v,
				item->z,
				item->z,
				zero);
		}
		item++;
	}

	CFont* font = this->m_fonts[4];
	font->SetMargin(kMLstOne);
	font->SetShadow(0);
	font->SetScale(kMLstOne);
	font->DrawInit();

	item = this->m_menuLstList->entries;
	for (int i = 0; i < this->m_menuLstList->count; i++) {
		font->SetColor(CColor(0xff, 0xff, 0xff, (unsigned char)(255.0f * item->alpha)).color);

		const char* text = GetMenuStr(i + 0x2e);
		font->GetWidth(text);

		float textX = (float)(item->x + 0x28);
		float textY = (float)(item->y + 3);
		if ((menuMode == 1) && (i == this->m_menuLstState->cursor)) {
			textX = (float)(textX + 20.0);
		}

		font->SetPosX(textX);
		font->SetPosY(textY - 4.0f);
		font->Draw(text);

		item++;
	}

	DrawInit();
	if (menuMode == 1) {
		MenuLstEntry* curItem = &this->m_menuLstList->entries[this->m_menuLstState->cursor];
		float cursorYF = (float)((double)(curItem->height - 0x20) * kMLstHalfDouble + (double)curItem->y);
		int cursorY = (int)cursorYF;
		int cursorX = (int)((float)(curItem->x - 0x38) + (float)((int)System.m_frameCounter % 8));
		DrawCursor(cursorX, cursorY, kMLstOne);
	}

	DrawInit();
	int helpMessageId = this->m_menuLstState->cursor + 0x25c;
	CFont* helpFont = this->m_fonts[0];
	float helpX = (float)-(rowHeight * kMLstHalf - kMLstHelpCenterX);
	float helpY = kMLstHelpY;
	DrawHelpMessage(
		helpMessageId,
		helpFont,
		(int)helpX,
		(int)helpY,
		CColor(0xff, 0xff, 0xff, (signed char)(255.0f * this->m_menuLstList->entries[0].alpha)).color,
		0x0a,
		kMLstOne,
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
	int itemCount;
	int currentFrame;
	int count;
	int result;

	completedItems = 0;
	this->m_menuLstState->frame = this->m_menuLstState->frame + 1;
	itemCount = this->m_menuLstList->count;
	entry = this->m_menuLstList->entries;
	currentFrame = (int)this->m_menuLstState->frame;
	for (int remaining = itemCount; remaining > 0; remaining--) {
		if (entry->startFrame <= currentFrame) {
			if (entry->startFrame + entry->duration <= currentFrame) {
				completedItems++;
				entry->alpha = kMLstZero;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = kMLstOneDouble / (double)entry->duration;
				entry->alpha = (float)(kMLstOneDouble - ratio * (double)entry->timer);
				if ((double)entry->alpha < kMLstZeroDouble) {
					entry->alpha = kMLstZero;
				}
			}
		}
		entry++;
	}
	result = 0;
	if (this->m_menuLstList->count == completedItems) {
		zero = kMLstZero;
		entry = this->m_menuLstList->entries;
		for (count = itemCount; count > 0; count--) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = zero;
			entry++;
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
	unsigned int rawPress;
	unsigned int rawHold;
	short press;
	short hold;
	unsigned int itemCount;
	unsigned int chunkCount;
	int i;
	int startFrame;
	int duration;
	int padLock;
	int result;

	blocked = false;
	padLock = Pad.m_debugPadLock;
	if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		rawPress = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		rawPress = Pad.GetPadInputs()[padIndex].buttonDown[0];
	}
	press = rawPress & 0xffff;

	blocked = false;
	if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
		blocked = true;
	}
	if (blocked) {
		rawHold = 0;
	} else {
		int padIndex = 0;
		padIndex &= ~-((__cntlzw((unsigned int)Pad.m_debugPadPort) & 0x20) >> 5);
		rawHold = Pad.GetPadInputs()[padIndex].repeatButton;
	}
	hold = rawHold & 0xffff;

	if (hold == 0) {
		result = 0;
	} else {
		if ((hold & 0x48) != 0) {
			int cursor = this->m_menuLstState->cursor;
			if (cursor != 0) {
				this->m_menuLstState->cursor = cursor - 1;
			} else {
				this->m_menuLstState->cursor = 8;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		} else if ((hold & 0x24) != 0) {
			int cursor = this->m_menuLstState->cursor;
			if (cursor < 8) {
				this->m_menuLstState->cursor = cursor + 1;
			} else {
				this->m_menuLstState->cursor = 0;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0x6c) == 0) {
			if ((press & 0x100) != 0) {
				Sound.PlaySe(2, 0x40, 0x7f, 0);
				result = 1;
			} else if ((press & 0x200) != 0) {
				this->m_menuLstState->closeRequested = (char)0xFF;
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
		one = kMLstOne;
		MenuLstEntry* entry = this->m_menuLstList->entries;
		for (i = 0; (itemCount = (unsigned int)this->m_menuLstList->count), i < (int)itemCount; i++) {
			entry->alpha = one;
			entry->z = one;
			entry++;
		}

		startFrame = 0;
		duration = 4;
		for (int idx = this->m_menuLstList->count - 1; idx >= 0; idx--) {
			MenuLstEntry* closeEntry = &this->m_menuLstList->entries[idx];
			closeEntry->startFrame = startFrame++;
			closeEntry->duration = duration;
		}

		this->m_menuLstState->frame = 0;
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
	int itemCount;
	int currentFrame;
	int count;

	if (this->m_menuLstState->initialized == '\0') {
		int i;
		short initializedCount;
		short yPos;
		double itemCenter;
		double xOrigin;
		float zero;

		memset(this->m_menuLstList, 0, sizeof(MenuLstList));
		one = kMLstOne;
		entry = this->m_menuLstList->entries;
		for (i = 0; i < 64; i++, entry++) {
			entry->z = one;
		}

		xOrigin = kMLstWindowCenterX;
		itemCenter = kMLstHalfDouble;
		zero = kMLstZero;
		initializedCount = 0;
		yPos = 0x18;
		for (i = 0; i < 9; i++) {
			entry = &this->m_menuLstList->entries[i];
			entry->unk_2C = 2;
			initializedCount++;
			entry->tex = 0x5B;
			entry->width = 0xE0;
			entry->height = 0x28;
			entry->x = (short)(int)-(((double)entry->width * itemCenter) - xOrigin);
			entry->y = yPos;
			yPos += 0x20;
			entry->s = zero;
			entry->t = zero;
			entry->startFrame = i;
			entry->duration = 4;
		}
		this->m_menuLstList->count = initializedCount;
		this->m_menuLstState->initialized = 1;
	}

	completedItems = 0;
	this->m_menuLstState->frame = this->m_menuLstState->frame + 1;
	itemCount = this->m_menuLstList->count;
	entry = this->m_menuLstList->entries;
	currentFrame = (int)this->m_menuLstState->frame;
	for (int remaining = itemCount; remaining > 0; remaining--) {
		if (entry->startFrame <= currentFrame) {
			if (entry->startFrame + entry->duration <= currentFrame) {
				completedItems++;
				entry->alpha = kMLstOne;
			} else {
				entry->timer = entry->timer + 1;
				double ratio = kMLstOneDouble / (double)entry->duration;
				entry->alpha = (float)(ratio * (double)entry->timer);
			}
		}
		entry++;
	}

	int result = 0;
	if (this->m_menuLstList->count == completedItems) {
		one = kMLstOne;
		entry = this->m_menuLstList->entries;
		for (count = itemCount; count > 0; count--) {
			entry->startFrame = 0;
			entry->duration = 1;
			entry->alpha = one;
			entry++;
		}
		result = 1;
	}
	return result;
}
