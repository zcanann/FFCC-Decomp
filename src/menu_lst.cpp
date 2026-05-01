#include "ffcc/menu_lst.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/linkage.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

extern "C" int __cntlzw(unsigned int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" void DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(CMenuPcs*, int, CFont*, int, int, GXColor, int, float, float);
extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" float GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);

extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);

extern const float FLOAT_803333D0;
extern const float FLOAT_803333D4;
extern const double DOUBLE_803333D8;
extern const float FLOAT_803333E0;
extern const double DOUBLE_803333E8;
extern const float FLOAT_803333F0;
extern const float FLOAT_803333F4;
extern const float FLOAT_803333F8;
extern const float FLOAT_803333FC;
extern const float FLOAT_80333400;
extern const float FLOAT_80333404;
extern const double DOUBLE_80333408;
extern const double DOUBLE_80333410;
extern const double DOUBLE_80333418;
extern const double DOUBLE_80333420;

extern "C" const float FLOAT_80333614 = 196.0f;
extern "C" const float FLOAT_80333618 = 168.0f;
extern "C" const float FLOAT_8033361C = 24.0f;
extern "C" const float FLOAT_80333620 = 20.0f;
extern "C" const float FLOAT_80333624 = 16.0f;
extern "C" const float FLOAT_80333628 = 564.0f;
extern "C" const float FLOAT_8033362C = 0.07692308f;
extern "C" const float FLOAT_80333630 = 6.923077f;
extern "C" const float FLOAT_80333634 = 4.0f;
extern "C" const unsigned int DOUBLE_80333638[2] = {0x43300000, 0x00000000};
extern "C" const unsigned int DOUBLE_80333640[2] = {0x43300000, 0x80000000};
extern "C" const float kOptionOpenAnimStep = 0.04f;
extern "C" const float kOptionColumnAnimStep = 0.2f;
extern "C" const float kOptionVolumeScale = 10.583333f;
extern "C" const float FLOAT_80333654 = 25.0f;
extern "C" const char DAT_80333658[4] = "";
extern "C" const char DAT_8033365c[] = "%s";
extern "C" const char DAT_80333660[] = "+1";
extern "C" const char DAT_80333664[] = "%c%d";
extern "C" const char DAT_8033366c[] = " ";
extern "C" const char DAT_80333670[] = " %d";

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
	_GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(&MenuPcs, 0);

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

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);
			GXColor color;
			color.r = 0xff;
			color.g = 0xff;
			color.b = 0xff;
			color.a = (unsigned char)(FLOAT_803333D4 * alpha);
			GXSetChanMatColor(GX_COLOR0A0, color);

			float v = FLOAT_803333D0;
			if ((menuMode == 1) && (i == this->lstState->cursor)) {
				x = (float)(x + DOUBLE_803333D8);
				v += (float)((double)item->height);
			}

			DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, x, y, w, h, FLOAT_803333D0, v, z, z, FLOAT_803333D0);

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x5c);
			v = FLOAT_803333D0;
			if ((menuMode == 1) && (i == this->lstState->cursor)) {
				v += (float)((double)item->height);
			}
			DrawRect__8CMenuPcsFUlfffffffff(
				&MenuPcs,
				0,
				(float)-(FLOAT_803333E0 * DOUBLE_803333E8 - x),
				y - FLOAT_803333F4,
				FLOAT_803333E0,
				FLOAT_803333E0,
				FLOAT_803333D0,
				v,
				z,
				z,
				FLOAT_803333D0);
		}
		item++;
	}

	CFont* font = this->listFont;
	font->SetMargin(FLOAT_803333F0);
	font->SetShadow(0);
	font->SetScale(FLOAT_803333F0);
	font->DrawInit();

	item = this->lstData->entries;
	for (int i = 0; i < this->lstData->count; i++) {
		CColor color(0xff, 0xff, 0xff, (unsigned char)(FLOAT_803333D4 * item->alpha));
		font->SetColor(color.color);

		const char* text = GetMenuStr__8CMenuPcsFi(this, i + 0x2e);
		font->GetWidth(text);

		float textX = (float)(item->x + 0x28);
		float textY = ((float)item->y + FLOAT_80333404) - FLOAT_803333F4;
		if ((menuMode == 1) && (i == this->lstState->cursor)) {
			textX = (float)(textX + DOUBLE_803333D8);
		}

		font->SetPosX(textX);
		font->SetPosY(textY);
		font->Draw(text);

		item++;
	}

	DrawInit__8CMenuPcsFv(this);
	if (menuMode == 1) {
		MenuLstEntry* curItem = &this->lstData->entries[this->lstState->cursor];
		float cursorYOffset = (float)((double)(float)(curItem->height - 0x20) * DOUBLE_803333E8);
		int cursorY = (int)((float)curItem->y + cursorYOffset);
		int cursorX = (int)((float)(curItem->x - 0x38) + (float)(System.m_frameCounter % 8));
		DrawCursor__8CMenuPcsFiif(this, cursorX, cursorY, FLOAT_803333F0);
	}

	DrawInit__8CMenuPcsFv(this);
	CColor helpColor(0xff, 0xff, 0xff, (unsigned char)(FLOAT_803333D4 * this->lstData->entries[0].alpha));
	DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(
		this,
		this->lstState->cursor + 0x25c,
		this->helpFont,
		(int)-((FLOAT_803333E0 * (double)FLOAT_803333FC) - (double)FLOAT_803333F8),
		(int)FLOAT_80333400,
		helpColor.color,
		0x0a,
		FLOAT_803333F0,
		FLOAT_80333404);
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
	int completedItems;
	MenuLstEntry* entry;
	unsigned int itemCount;
	int currentFrame;
	unsigned int count;

	completedItems = 0;
	this->lstState->frame = this->lstState->frame + 1;
	itemCount = (unsigned int)this->lstData->count;
	entry = this->lstData->entries;
	currentFrame = (int)this->lstState->frame;
	if ((int)itemCount > 0) {
		for (unsigned int i = itemCount; i != 0; i--) {
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
	}
	zero = FLOAT_803333D0;
	if (this->lstData->count == completedItems) {
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
			if (itemCount == 0) {
				return 1;
			}

			do {
				entry->startFrame = 0;
				entry->duration = 1;
				entry->alpha = zero;
				entry++;
				itemCount--;
			} while (itemCount != 0);
		}
		return 1;
	}

	return 0;
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
void CMenuPcs::MLstCtrl()
{
	bool blocked;
	float one;
	unsigned int press;
	unsigned int hold;
	unsigned int itemCount;
	unsigned int chunkCount;
	int i;
	int startFrame;
	int duration;
	int padLock;

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
		blocked = false;
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
				blocked = true;
			} else if ((press & 0x200) != 0) {
				this->lstState->closeRequested = (char)0xFF;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
				blocked = true;
			} else {
				blocked = false;
			}
		} else {
			blocked = false;
		}
	}

	one = FLOAT_803333F0;
	if (!blocked) {
		return;
	}

	MenuLstEntry* entry = this->lstData->entries;
	for (i = 0; (itemCount = (unsigned int)this->lstData->count), i < (int)itemCount; i++) {
		entry->alpha = one;
		entry->z = one;
		entry++;
	}

	startFrame = 0;
	duration = 4;
	for (int idx = this->lstData->count - 1; idx >= 0; idx--) {
		this->lstData->entries[idx].startFrame = startFrame++;
		this->lstData->entries[idx].duration = duration;
	}

	this->lstState->frame = 0;
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
		one = FLOAT_803333F0;
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

		zero = FLOAT_803333D0;
		initializedCount = 0;
		yPos = 0x18;
		for (int i = 0; i < 9; i++) {
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
	if ((int)itemCount > 0) {
		for (unsigned int i = itemCount; i != 0; i--) {
			if (entry->startFrame <= currentFrame) {
				if (entry->startFrame + entry->duration <= currentFrame) {
					completedItems++;
					entry->alpha = FLOAT_803333F0;
				} else {
					entry->timer = entry->timer + 1;
					double ratio = DOUBLE_80333410 / (double)entry->duration;
					entry->alpha = (float)(ratio * (double)entry->timer);
				}
			}
			entry++;
		}
	}

	one = FLOAT_803333F0;
	if (this->lstData->count == completedItems) {
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
			if (itemCount == 0) {
				return 1;
			}

			do {
				entry->startFrame = 0;
				entry->duration = 1;
				entry->alpha = one;
				entry++;
				itemCount--;
			} while (itemCount != 0);
		}
		return 1;
	}
	return 0;
}
