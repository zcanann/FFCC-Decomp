#include "ffcc/menu_lst.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

#ifdef VERSION_GCCJGC
enum {
    kMLstCursorTexture = 0x5B,
    kMLstRowTexture = 0x5A
};
#else
enum {
    kMLstCursorTexture = 0x5C,
    kMLstRowTexture = 0x5B
};
#endif

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
 * EN Address: 0x801736C8
 * EN Size: 1436b
 * JP Address: 0x8016F384
 * JP Size: 1436b
 */
void CMenuPcs::MLstDraw()
{
	CFont* font;
	short menuMode;
	int i;
	MenuLstEntry* item;
	float y;
	float h;
	float w;
	float x;
	float v;
	GXColor colors[4];

	_GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
	MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

	menuMode = this->m_menuLstState->mode;
	item = this->m_menuLstList->entries;

	for (i = 0; i < this->m_menuLstList->count; i++, item++) {
		int tex = item->tex;
		if (tex >= 0) {
			x = (float)item->x;
			float zero = kMLstZero;
			v = zero;
			y = (float)item->y;
			w = (float)item->width;
			h = (float)item->height;
			float alpha = item->alpha;

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
			colors[0].r = 0xff;
			colors[0].g = 0xff;
			colors[0].b = 0xff;
			colors[0].a = (unsigned char)(kMLstColorMax * alpha);
			GXSetChanMatColor(GX_COLOR0A0, colors[0]);

			if ((menuMode == 1) && (i == this->m_menuLstState->cursor)) {
				x += kMLstSelectedOffsetX;
				v += (float)item->height;
			}

			MenuPcs.DrawRect(0, x, y, w, h, zero, v, item->z, item->z, zero);

			MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kMLstCursorTexture));
			w = kMLstRowHeight;
			float iconX = item->x - w / 2.0;
			float iconY = (float)(item->y - 6);
			v = zero;
			if ((menuMode == 1) && (i == this->m_menuLstState->cursor)) {
				v += (float)item->height;
			}
			MenuPcs.DrawRect(0, iconX, iconY, w, w, zero, v, item->z, item->z, zero);
		}
	}

	font = GetFontItem();
	font->SetMargin(kMLstOne);
	font->SetShadow(0);
	font->SetScale(kMLstOne);
	font->DrawInit();

	item = this->m_menuLstList->entries;
	for (i = 0; i < this->m_menuLstList->count; i++, item++) {
		font->SetColor(CColor(0xff, 0xff, 0xff, (unsigned char)(kMLstColorMax * item->alpha)).color);

		const char* text = GetMenuStr(i + 0x2e);
		font->GetWidth(text);

		float textX = (float)(item->x + 0x28);
		float textY = (float)(item->y + 3);
		if ((menuMode == 1) && (i == this->m_menuLstState->cursor)) {
			textX += kMLstSelectedOffsetX;
		}

		font->SetPosX(textX);
#ifdef VERSION_GCCJGC
		font->SetPosY(textY);
#else
		font->SetPosY(textY - kMLstTextYOffset);
#endif
		font->Draw(text);
	}

	DrawInit();
	if (menuMode == 1) {
		MenuLstEntry* curItem = &this->m_menuLstList->entries[this->m_menuLstState->cursor];
		float cursorYF = (curItem->height - 0x20) / 2.0 + curItem->y;
		int cursorY = (int)cursorYF;
		int cursorX = (int)((float)(curItem->x - 0x38) + (float)((int)System.m_frameCounter % 8));
		DrawCursor(cursorX, cursorY, kMLstOne);
	}

	DrawInit();
	int helpMessageId = this->m_menuLstState->cursor + 0x25c;
	CFont* helpFont = this->m_fonts[0];
	float helpX = kMLstHelpCenterX - w / 2;
	float helpY = kMLstHelpY;
	DrawHelpMessage(
		helpMessageId,
		helpFont,
		(int)helpX,
		(int)helpY,
		CColor(0xff, 0xff, 0xff, (signed char)(kMLstColorMax * this->m_menuLstList->entries[0].alpha)).color,
		0x0a,
		kMLstOne,
		kMLstHelpScale);
}

/*
 * --INFO--
 * PAL Address: 0x80174ce8
 * PAL Size: 428b
 * EN Address: 0x80173C64
 * EN Size: 428b
 * JP Address: 0x8016F920
 * JP Size: 460b
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
 * PAL Address: UNUSED
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::MLstInit1()
{
	float one;
	int i;
	MenuLstEntry* entry;
	int startFrame;
	int duration;

	one = kMLstOne;
	entry = this->m_menuLstList->entries;
	for (i = 0; i < this->m_menuLstList->count; i++) {
		entry->alpha = one;
		entry->z = one;
		entry++;
	}

	startFrame = 0;
	duration = 4;
	for (int idx = this->m_menuLstList->count - 1; idx >= 0; idx--) {
		entry = &this->m_menuLstList->entries[idx];
		entry->startFrame = startFrame++;
		entry->duration = duration;
	}

	this->m_menuLstState->frame = 0;
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
inline int CMenuPcs::MLstCtrlCur()
{
	short press;
	short hold;

	press = Pad.GetButtonDown(0);
	hold = Pad.GetButtonRepeat(0);

	if (hold == 0) {
		return 0;
	}

	if ((hold & 0x48) != 0) {
		MenuLstState* st = this->m_menuLstState;
		if (st->cursor != 0) {
			st->cursor--;
		} else {
			st->cursor = 8;
		}
		Sound.PlaySe(1, 0x40, 0x7f, 0);
	} else if ((hold & 0x24) != 0) {
		MenuLstState* st = this->m_menuLstState;
		if (st->cursor < 8) {
			st->cursor++;
		} else {
			st->cursor = 0;
		}
		Sound.PlaySe(1, 0x40, 0x7f, 0);
	}

	if ((hold & 0x6c) == 0) {
		if ((press & 0x100) != 0) {
			Sound.PlaySe(2, 0x40, 0x7f, 0);
			return 1;
		}
		if ((press & 0x200) != 0) {
			this->m_menuLstState->closeRequested = (char)0xFF;
			Sound.PlaySe(3, 0x40, 0x7f, 0);
			return 1;
		}
	}
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80174e94
 * PAL Size: 892b
 * EN Address: 0x80173E10
 * EN Size: 892b
 * JP Address: 0x8016FAEC
 * JP Size: 896b
 */
int CMenuPcs::MLstCtrl()
{
	int result = MLstCtrlCur();

	if (result != 0) {
		MLstInit1();
	}
	return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::MLstInit()
{
	int i;
	short yPos;
	int initializedCount;
	double itemCenter;
	double xOrigin;
	float zero;
	float one;
	MenuLstEntry* entry;

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
		entry = &this->m_menuLstList->entries[initializedCount++];
		entry->unk_2C = 2;
		entry->tex = kMLstRowTexture;
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

/*
 * --INFO--
 * PAL Address: 0x80175210
 * PAL Size: 720b
 * EN Address: 0x8017418C
 * EN Size: 720b
 * JP Address: 0x8016FE6C
 * JP Size: 784b
 */
int CMenuPcs::MLstOpen()
{
	float one;
	MenuLstEntry* entry;
	int completedItems;
	int itemCount;
	int currentFrame;
	int count;

	if (this->m_menuLstState->initialized == '\0') {
		MLstInit();
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
