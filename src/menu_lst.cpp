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
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);

extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);

extern double DOUBLE_803333E8;
extern double DOUBLE_803333D8;
extern float FLOAT_803333D0;
extern float FLOAT_803333D4;
extern float FLOAT_803333E0;
extern float FLOAT_803333F4;
extern float FLOAT_803333F8;
extern float FLOAT_803333FC;
extern float FLOAT_80333400;
extern double DOUBLE_80333408;
extern double DOUBLE_80333410;
extern double DOUBLE_80333418;
extern double DOUBLE_80333420;
extern float FLOAT_803333F0;

STATIC_ASSERT(offsetof(CMenuPcs, listFont) == 0x108);
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
		entry = this->lstData->entries;
		i = 0;
		yPos = 0x18;
		do {
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
			i++;
			entry->duration = 4;
			entry++;
		} while (i < 9);
		this->lstData->count = initializedCount;
		this->lstState->initialized = 1;
	}

	completedItems = 0;
	this->lstState->frame = this->lstState->frame + 1;
	itemCount = (unsigned int)this->lstData->count;
	entry = this->lstData->entries;
	currentFrame = (int)this->lstState->frame;
	count = itemCount;
	if ((int)itemCount > 0) {
		do {
			if (entry->startFrame <= currentFrame) {
				if (currentFrame < entry->startFrame + entry->duration) {
					entry->timer = entry->timer + 1;
					entry->alpha = (float)((DOUBLE_80333410 / (double)entry->duration) * (double)entry->timer);
				} else {
					completedItems++;
					entry->alpha = FLOAT_803333F0;
				}
			}
			entry++;
			count--;
		} while (count != 0);
	}

	one = FLOAT_803333F0;
	if (this->lstData->count == completedItems) {
		entry = this->lstData->entries;
		if ((int)itemCount > 0) {
			count = itemCount >> 3;
			if (count != 0) {
				do {
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
					count--;
				} while (count != 0);
				itemCount &= 7;
				if (itemCount == 0) {
					return 1;
				}
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
	unsigned short press;
	unsigned short hold;
	unsigned int itemCount;
	unsigned int chunkCount;
	int entryBase;
	int i;
	int startFrame;
	int offset;

	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		unsigned char* padPtr = reinterpret_cast<unsigned char*>(&Pad);
		if ((__cntlzw((unsigned int)Pad._448_4_) & 0x20) == 0) {
			padPtr += 0x54;
		}
		press = *(unsigned short*)(padPtr + 8);
	}

	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		unsigned char* padPtr = reinterpret_cast<unsigned char*>(&Pad);
		if ((__cntlzw((unsigned int)Pad._448_4_) & 0x20) == 0) {
			padPtr += 0x54;
		}
		hold = *(unsigned short*)(padPtr + 0x14);
	}

	if (hold == 0) {
		blocked = false;
	} else {
		if ((hold & 0x48) != 0) {
			if (this->lstState->cursor == 0) {
				this->lstState->cursor = 8;
			} else {
				this->lstState->cursor = this->lstState->cursor - 1;
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

	entryBase = (int)this->lstData + 8;
	for (i = 0; (itemCount = (unsigned int)this->lstData->count), i < (int)itemCount; i++) {
		*(float*)(entryBase + 0x10) = one;
		*(float*)(entryBase + 0x14) = one;
		entryBase += 0x40;
	}

	startFrame = 0;
	offset = ((int)itemCount - 1) * 0x40;
	if (-1 < (int)(itemCount - 1)) {
		chunkCount = itemCount >> 3;
		if (chunkCount != 0) {
			do {
				int entryPtr = (int)this->lstData + offset + 8;
				*(int*)(entryPtr + 0x24) = startFrame;
				*(unsigned int*)(entryPtr + 0x28) = 4;
				entryPtr = (int)this->lstData + offset - 0x38;
				*(int*)(entryPtr + 0x24) = startFrame + 1;
				*(unsigned int*)(entryPtr + 0x28) = 4;
				entryPtr = (int)this->lstData + offset - 0x78;
				*(int*)(entryPtr + 0x24) = startFrame + 2;
				*(unsigned int*)(entryPtr + 0x28) = 4;
				entryPtr = (int)this->lstData + offset - 0xb8;
				*(int*)(entryPtr + 0x24) = startFrame + 3;
				*(unsigned int*)(entryPtr + 0x28) = 4;
				entryPtr = (int)this->lstData + offset - 0xf8;
				*(int*)(entryPtr + 0x24) = startFrame + 4;
				*(unsigned int*)(entryPtr + 0x28) = 4;
				entryPtr = (int)this->lstData + offset - 0x138;
				*(int*)(entryPtr + 0x24) = startFrame + 5;
				*(unsigned int*)(entryPtr + 0x28) = 4;
				entryPtr = (int)this->lstData + offset - 0x178;
				*(int*)(entryPtr + 0x24) = startFrame + 6;
				*(unsigned int*)(entryPtr + 0x28) = 4;
				entryPtr = offset - 0x1b8;
				offset -= 0x200;
				entryPtr = (int)this->lstData + entryPtr;
				*(int*)(entryPtr + 0x24) = startFrame + 7;
				startFrame += 8;
				*(unsigned int*)(entryPtr + 0x28) = 4;
				chunkCount--;
			} while (chunkCount != 0);

				itemCount &= 7;
				if (itemCount == 0) {
					this->lstState->frame = 0;
					return;
				}
			}

		do {
			int entryPtr = offset + 8;
			offset -= 0x40;
			entryPtr = (int)this->lstData + entryPtr;
			*(int*)(entryPtr + 0x24) = startFrame;
			startFrame++;
			*(unsigned int*)(entryPtr + 0x28) = 4;
			itemCount--;
		} while (itemCount != 0);
	}

	this->lstState->frame = 0;
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
	count = itemCount;
	if ((int)itemCount > 0) {
		do {
			if (entry->startFrame <= currentFrame) {
				if (currentFrame < entry->startFrame + entry->duration) {
					entry->timer = entry->timer + 1;
					entry->alpha =
						(float)-((DOUBLE_80333410 / (double)entry->duration) * (double)entry->timer - DOUBLE_80333410);
					if ((double)entry->alpha < DOUBLE_80333418) {
						entry->alpha = FLOAT_803333D0;
					}
				} else {
					completedItems++;
					entry->alpha = FLOAT_803333D0;
				}
			}
			entry++;
			count--;
		} while (count != 0);
	}
	zero = FLOAT_803333D0;
	if (this->lstData->count == completedItems) {
		entry = this->lstData->entries;
		if ((int)itemCount > 0) {
			count = itemCount >> 3;
			if (count != 0) {
				do {
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
					count--;
				} while (count != 0);
				itemCount &= 7;
				if (itemCount == 0) {
					return 1;
				}
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

	MenuLstState* state = this->lstState;
	MenuLstList* list = this->lstData;
	short menuMode = state->mode;
	MenuLstEntry* item = list->entries;

	for (int i = 0; i < list->count; i++) {
		int tex = item->tex;
		if (tex >= 0) {
			float x = (float)item->x;
			float y = (float)item->y;
			float w = (float)item->width;
			float h = (float)item->height;
			float alpha = item->alpha;
			float z = item->z;

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);
			GXColor color = {0xff, 0xff, 0xff, (unsigned char)(FLOAT_803333D4 * alpha)};
			GXSetChanMatColor(GX_COLOR0A0, color);

			float v = FLOAT_803333D0;
			if ((menuMode == 1) && (i == state->cursor)) {
				x = (float)(x + DOUBLE_803333D8);
				v += (float)((double)item->height);
			}

			DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, x, y, w, h, FLOAT_803333D0, v, z, z, FLOAT_803333D0);

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x5c);
			v = FLOAT_803333D0;
			if ((menuMode == 1) && (i == state->cursor)) {
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

	item = list->entries;
	for (int i = 0; i < list->count; i++) {
		CColor color(0xff, 0xff, 0xff, (unsigned char)(FLOAT_803333D4 * item->alpha));
		font->SetColor(color.color);

		const char* text = GetMenuStr__8CMenuPcsFi(this, i + 0x2e);
		font->GetWidth(text);

		float textX = (float)(item->x + 0x28);
		float textY = (float)(item->y + 3) - FLOAT_803333F4;
		if ((menuMode == 1) && (i == state->cursor)) {
			textX = (float)(textX + DOUBLE_803333D8);
		}

		font->SetPosX(textX);
		font->SetPosY(textY);
		font->Draw(text);

		item++;
	}

	DrawInit__8CMenuPcsFv(this);
	if (menuMode == 1) {
		MenuLstEntry* curItem = &list->entries[state->cursor];
		float cursorYOffset =
			(float)(((double)(float)(curItem->height - 0x20) * DOUBLE_803333E8) + (double)(float)curItem->height);
		int cursorY = (int)((float)curItem->y + cursorYOffset);
		int cursorX = (int)((float)curItem->x - 56.0f + (float)(System.m_frameCounter & 7));
		DrawCursor__8CMenuPcsFiif(this, cursorX, cursorY, FLOAT_803333F0);
	}

	DrawInit__8CMenuPcsFv(this);
	CColor helpColor(0xff, 0xff, 0xff, (unsigned char)(FLOAT_803333D4 * list->entries[0].alpha));
	DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(
		this,
		state->cursor + 0x25c,
		font,
		0,
		-(int)FLOAT_80333400,
		helpColor.color,
		0,
		FLOAT_803333F0,
		(float)-((FLOAT_803333E0 * (double)FLOAT_803333FC) - (double)FLOAT_803333F8));
}
