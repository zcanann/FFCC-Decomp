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

namespace {

struct MenuLstState {
	unsigned char pad_0000[0xB];
	char initialized;
	char pad_000C;
	char closeRequested;
	unsigned char pad_000E[2];
	short mode;
	unsigned char pad_0012[0x10];
	short frame;
	unsigned char pad_0024[2];
	short cursor;
};

struct MenuLstEntry {
	short x;
	short y;
	short width;
	short height;
	float s;
	float t;
	float alpha;
	float z;
	int unk_18;
	int tex;
	int timer;
	int startFrame;
	int duration;
	int unk_2C;
	unsigned char pad_0030[0x10];
};

struct MenuLstList {
	short count;
	unsigned short pad_0002;
	unsigned int pad_0004;
	MenuLstEntry entries[64];
};

struct MenuLstMembers {
	unsigned char pad_0000[0x108];
	CFont* m_font;
	unsigned char pad_010C[0x720];
	MenuLstState* m_lstState;
	unsigned char pad_0830[0x20];
	MenuLstList* m_lstData;
};

STATIC_ASSERT(offsetof(MenuLstMembers, m_font) == 0x108);
STATIC_ASSERT(offsetof(MenuLstMembers, m_lstState) == 0x82C);
STATIC_ASSERT(offsetof(MenuLstMembers, m_lstData) == 0x850);
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

static inline MenuLstMembers& GetMenuLstMembers(CMenuPcs* menu)
{
	return *reinterpret_cast<MenuLstMembers*>(menu);
}

static inline MenuLstState* GetMenuLstStateStruct(CMenuPcs* menu)
{
	return GetMenuLstMembers(menu).m_lstState;
}

static inline MenuLstList* GetMenuLstListStruct(CMenuPcs* menu)
{
	return GetMenuLstMembers(menu).m_lstData;
}

static inline unsigned char* GetMenuLstPadPtr()
{
	unsigned char* padPtr = reinterpret_cast<unsigned char*>(&Pad);
	if ((__cntlzw((unsigned int)Pad._448_4_) & 0x20) == 0) {
		padPtr += 0x54;
	}
	return padPtr;
}

} // namespace

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MLstInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MLstInit1()
{
	// TODO
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
	int completedItems;
	MenuLstEntry* entry;
	unsigned int itemCount;
	int currentFrame;
	unsigned int count;

	if (GetMenuLstStateStruct(this)->initialized == '\0') {
		int i;
		short initializedCount;
		short yPos;

		memset(GetMenuLstListStruct(this), 0, sizeof(MenuLstList));
		one = 1.0f;
		entry = GetMenuLstListStruct(this)->entries;
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

		initializedCount = 0;
		entry = GetMenuLstListStruct(this)->entries;
		i = 0;
		yPos = 0x18;
		do {
			entry->unk_2C = 2;
			initializedCount++;
			entry->tex = 0x5B;
			entry->width = 0xE0;
			entry->height = 0x28;
			entry->x = (short)(int)(320.0 - ((double)entry->width * 0.5));
			entry->y = yPos;
			yPos += 0x20;
			entry->s = one;
			entry->t = one;
			entry->startFrame = i;
			i++;
			entry->duration = 4;
			entry++;
		} while (i < 9);
		GetMenuLstListStruct(this)->count = initializedCount;
		GetMenuLstStateStruct(this)->initialized = 1;
	}

	completedItems = 0;
	GetMenuLstStateStruct(this)->frame = GetMenuLstStateStruct(this)->frame + 1;
	itemCount = (unsigned int)GetMenuLstListStruct(this)->count;
	entry = GetMenuLstListStruct(this)->entries;
	currentFrame = (int)GetMenuLstStateStruct(this)->frame;
	count = itemCount;
	if ((int)itemCount > 0) {
		do {
			if (entry->startFrame <= currentFrame) {
				if (currentFrame < entry->startFrame + entry->duration) {
					entry->timer = entry->timer + 1;
					entry->alpha = (float)((1.0 / (double)entry->duration) * (double)entry->timer);
				} else {
					completedItems++;
					entry->alpha = 1.0f;
				}
			}
			entry++;
			count--;
		} while (count != 0);
	}

	one = 1.0f;
	if (GetMenuLstListStruct(this)->count == completedItems) {
		entry = GetMenuLstListStruct(this)->entries;
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
	int i;
	int item;
	int startFrame;
	int offset;
	unsigned int chunkCount;
	MenuLstState* state;
	MenuLstList* list;

	state = GetMenuLstStateStruct(this);
	list = GetMenuLstListStruct(this);
	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		press = *(unsigned short*)(GetMenuLstPadPtr() + 8);
	}

	blocked = false;
	if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		hold = *(unsigned short*)(GetMenuLstPadPtr() + 0x14);
	}

	if (hold == 0) {
		blocked = false;
	} else {
		if ((hold & 0x48) == 0) {
			if ((hold & 0x24) != 0) {
				if (state->cursor < 8) {
					state->cursor = state->cursor + 1;
				} else {
					state->cursor = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		} else {
			if (state->cursor == 0) {
				state->cursor = 8;
			} else {
				state->cursor = state->cursor - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0x6c) == 0) {
			if ((press & 0x100) != 0) {
				Sound.PlaySe(2, 0x40, 0x7f, 0);
				blocked = true;
			} else if ((press & 0x200) != 0) {
				state->closeRequested = 0xFF;
				Sound.PlaySe(3, 0x40, 0x7f, 0);
				blocked = true;
			} else {
				blocked = false;
			}
		} else {
			blocked = false;
		}
	}

	one = 1.0f;
	if (!blocked) {
		return;
	}

	item = reinterpret_cast<int>(list) + 8;
	for (i = 0; (itemCount = (unsigned int)list->count), i < (int)itemCount; i++) {
		*(float*)(item + 0x10) = one;
		*(float*)(item + 0x14) = one;
		item += 0x40;
	}

	startFrame = 0;
	offset = ((int)itemCount - 1) * 0x40;
	if (-1 < (int)(itemCount - 1)) {
		chunkCount = itemCount >> 3;
		if (chunkCount != 0) {
			do {
				item = reinterpret_cast<int>(list) + offset + 8;
				*(int*)(item + 0x24) = startFrame;
				*(int*)(item + 0x28) = 4;
				item = reinterpret_cast<int>(list) + offset - 0x38;
				*(int*)(item + 0x24) = startFrame + 1;
				*(int*)(item + 0x28) = 4;
				item = reinterpret_cast<int>(list) + offset - 0x78;
				*(int*)(item + 0x24) = startFrame + 2;
				*(int*)(item + 0x28) = 4;
				item = reinterpret_cast<int>(list) + offset - 0xB8;
				*(int*)(item + 0x24) = startFrame + 3;
				*(int*)(item + 0x28) = 4;
				item = reinterpret_cast<int>(list) + offset - 0xF8;
				*(int*)(item + 0x24) = startFrame + 4;
				*(int*)(item + 0x28) = 4;
				item = reinterpret_cast<int>(list) + offset - 0x138;
				*(int*)(item + 0x24) = startFrame + 5;
				*(int*)(item + 0x28) = 4;
				item = reinterpret_cast<int>(list) + offset - 0x178;
				*(int*)(item + 0x24) = startFrame + 6;
				*(int*)(item + 0x28) = 4;
				item = reinterpret_cast<int>(list) + offset - 0x1B8;
				offset -= 0x200;
				*(int*)(item + 0x24) = startFrame + 7;
				startFrame += 8;
				*(int*)(item + 0x28) = 4;
				chunkCount--;
			} while (chunkCount != 0);

			itemCount &= 7;
			if (itemCount == 0) {
				state->frame = 0;
				return;
			}
		}

		do {
			item = reinterpret_cast<int>(list) + offset + 8;
			offset -= 0x40;
			*(int*)(item + 0x24) = startFrame;
			startFrame++;
			*(int*)(item + 0x28) = 4;
			itemCount--;
		} while (itemCount != 0);
	}

	state->frame = 0;
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
	GetMenuLstStateStruct(this)->frame = GetMenuLstStateStruct(this)->frame + 1;
	itemCount = (unsigned int)GetMenuLstListStruct(this)->count;
	entry = GetMenuLstListStruct(this)->entries;
	currentFrame = (int)GetMenuLstStateStruct(this)->frame;
	count = itemCount;
	if ((int)itemCount > 0) {
		do {
			if (entry->startFrame <= currentFrame) {
				if (currentFrame < entry->startFrame + entry->duration) {
					entry->timer = entry->timer + 1;
					entry->alpha = (float)-((1.0 / (double)entry->duration) * (double)entry->timer - 1.0);
					if ((double)entry->alpha < 0.0) {
						entry->alpha = 0.0f;
					}
				} else {
					completedItems++;
					entry->alpha = 0.0f;
				}
			}
			entry++;
			count--;
		} while (count != 0);
	}
	zero = 0.0f;
	if (GetMenuLstListStruct(this)->count == completedItems) {
		entry = GetMenuLstListStruct(this)->entries;
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

	MenuLstState* state = GetMenuLstStateStruct(this);
	MenuLstList* list = GetMenuLstListStruct(this);
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

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);
			GXColor color = {0xff, 0xff, 0xff, (unsigned char)(255.0f * alpha)};
			GXSetChanMatColor(GX_COLOR0A0, color);

			float v = 0.0f;
			if ((menuMode == 1) && (i == state->cursor)) {
				x += 6.0f;
				v += h;
			}

			DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, x, y, w, h, 0.0f, v, item->z, item->z, 0.0f);

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x5c);
			v = 0.0f;
			if ((menuMode == 1) && (i == state->cursor)) {
				v += h;
			}
			DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, -((48.0f * 1.5f) - (float)item->x), (float)item->y - 6.0f, 48.0f, 48.0f, 0.0f, v, item->z, item->z, 0.0f);
		}
		item++;
	}

	CFont* font = GetMenuLstMembers(this).m_font;
	SetMargin__5CFontFf(1.0f, font);
	SetShadow__5CFontFi(font, 0);
	SetScale__5CFontFf(1.0f, font);
	DrawInit__5CFontFv(font);

	item = list->entries;
	for (int i = 0; i < list->count; i++) {
		CColor color(0xff, 0xff, 0xff, (unsigned char)(255.0f * item->alpha));
		SetColor__5CFontF8_GXColor(font, &color.color);

		const char* text = GetMenuStr__8CMenuPcsFi(this, i + 0x2e);
		GetWidth__5CFontFPc(font, text);

		float textX = (float)(item->x + 0x28);
		float textY = (float)(item->y - 3);
		if ((menuMode == 1) && (i == state->cursor)) {
			textX += 6.0f;
		}

		SetPosX__5CFontFf(textX, font);
		SetPosY__5CFontFf(textY, font);
		Draw__5CFontFPc(font, text);

		item++;
	}

	DrawInit__8CMenuPcsFv(this);
	if (menuMode == 1) {
		MenuLstEntry* curItem = &list->entries[state->cursor];
		int cursorY = (int)((float)curItem->y + (((float)curItem->height - 32.0f) * 1.5f));
		int cursorX = (int)((float)curItem->x - 56.0f + (float)(System.m_frameCounter & 7));
		DrawCursor__8CMenuPcsFiif(this, cursorX, cursorY, 1.0f);
	}

	DrawInit__8CMenuPcsFv(this);
	CColor helpColor(0xff, 0xff, 0xff, (unsigned char)(255.0f * list->entries[0].alpha));
	DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(this, state->cursor + 0x25c, font, 0, -20, helpColor.color, 0, 1.0f, 0.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::MLstCtrlCur()
{
	// TODO
}
