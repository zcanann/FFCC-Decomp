#include "ffcc/menu_lst.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

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
void CMenuPcs::MLstOpen()
{
	// Initialize menu list data if not already initialized
	if (*(char*)((char*)this + 0x82c + 0xb) == 0) {
		// Clear menu list data structure
		memset(*(void**)((char*)this + 0x850), 0, 0x1008);
		
		// Initialize 9 menu items with default properties
		float defaultAlpha = 1.0f;
		short yPos = 0x18;
		int itemIndex = 0;
		
		for (int i = 0; i < 9; i++) {
			short* itemPtr = (short*)(*(int*)((char*)this + 0x850) + i * 0x40 + 8);
			
			// Set item properties
			*(int*)(itemPtr + 0x16) = 2;      // Some flag/type
			*(int*)(itemPtr + 0xe) = 0x5b;    // Texture ID
			itemPtr[2] = 0xe0;                // Width
			itemPtr[3] = 0x28;                // Height
			
			// Calculate X position (centered)
			*itemPtr = (short)(int)-(((double)(itemPtr[2] ^ 0x80000000) - 4503599627370496.0) * 0.5 - 320.0);
			itemPtr[1] = yPos;                // Y position
			yPos += 0x20;                     // Move down for next item
			
			*(float*)(itemPtr + 4) = 1.0f;    // Scale/alpha values
			*(float*)(itemPtr + 6) = 1.0f;
			*(int*)(itemPtr + 0x12) = itemIndex;    // Animation start frame
			*(int*)(itemPtr + 0x14) = 4;            // Animation duration
			
			itemIndex++;
		}
		
		// Set item count
		**(short**)((char*)this + 0x850) = 9;
		
		// Mark as initialized
		*(char*)((char*)this + 0x82c + 0xb) = 1;
	}
	
	// Handle fade-in animation
	int completedItems = 0;
	*(short*)((char*)this + 0x82c + 0x22) += 1; // Increment animation frame
	int currentFrame = *(short*)((char*)this + 0x82c + 0x22);
	
	int itemCount = **(short**)((char*)this + 0x850);
	short* itemPtr = *(short**)((char*)this + 0x850) + 4;
	
	// Update each item's fade-in animation
	for (int i = 0; i < itemCount; i++) {
		int startFrame = *(int*)(itemPtr + 0x12);
		int duration = *(int*)(itemPtr + 0x14);
		
		if (startFrame <= currentFrame) {
			if (currentFrame < startFrame + duration) {
				// Animate fade-in
				*(int*)(itemPtr + 0x10) += 1;
				float progress = (float)(*(int*)(itemPtr + 0x10)) / (float)duration;
				*(float*)(itemPtr + 8) = progress;
			} else {
				// Animation complete
				completedItems++;
				*(float*)(itemPtr + 8) = 1.0f;
			}
		}
		
		itemPtr += 0x20;
	}
	
	// Check if all animations are complete
	if (itemCount == completedItems) {
		// Reset all animation states
		itemPtr = *(short**)((char*)this + 0x850) + 4;
		for (int i = 0; i < itemCount; i++) {
			*(short*)(itemPtr + 0x12) = 0;  // Reset start frame
			*(short*)(itemPtr + 0x13) = 0;
			*(short*)(itemPtr + 0x14) = 0;  // Reset duration
			*(short*)(itemPtr + 0x15) = 1;
			*(float*)(itemPtr + 8) = 1.0f;  // Full alpha
			itemPtr += 0x20;
		}
		// Animation complete - no return needed for void function
	}
	
	// Still animating - no return needed for void function
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
	bool resetAnim;
	unsigned short press;
	unsigned short hold;
	unsigned int itemCount;
	int i;
	int item;
	int startFrame;
	int offset;
	unsigned int chunkCount;
	int menuState;

	blocked = false;
	if (Pad._452_4_ != 0 || Pad._448_4_ != -1) {
		blocked = true;
	}
	if (blocked) {
		press = 0;
	} else {
		press = Pad._8_2_;
	}

	blocked = false;
	if (Pad._452_4_ != 0 || Pad._448_4_ != -1) {
		blocked = true;
	}
	if (blocked) {
		hold = 0;
	} else {
		hold = *reinterpret_cast<unsigned short*>(reinterpret_cast<char*>(&Pad) + 0x20);
	}

	if (hold == 0) {
		resetAnim = false;
	} else {
		menuState = *(int*)((char*)this + 0x82c);
		if ((hold & 0x48) == 0) {
			if ((hold & 0x24) != 0) {
				if (*(short*)(menuState + 0x26) < 8) {
					*(short*)(menuState + 0x26) = *(short*)(menuState + 0x26) + 1;
				} else {
					*(short*)(menuState + 0x26) = 0;
				}
				Sound.PlaySe(1, 0x40, 0x7f, 0);
			}
		} else {
			if (*(short*)(menuState + 0x26) == 0) {
				*(short*)(menuState + 0x26) = 8;
			} else {
				*(short*)(menuState + 0x26) = *(short*)(menuState + 0x26) - 1;
			}
			Sound.PlaySe(1, 0x40, 0x7f, 0);
		}

		if ((hold & 0x6c) == 0) {
			if ((press & 0x100) == 0) {
				if ((press & 0x200) == 0) {
					resetAnim = false;
				} else {
					*(char*)(*(int*)((char*)this + 0x82c) + 0xd) = (char)0xff;
					Sound.PlaySe(3, 0x40, 0x7f, 0);
					resetAnim = true;
				}
			} else {
				Sound.PlaySe(2, 0x40, 0x7f, 0);
				resetAnim = true;
			}
		} else {
			resetAnim = false;
		}
	}

	if (!resetAnim) {
		return;
	}

	item = *(int*)((char*)this + 0x850) + 8;
	for (i = 0; (itemCount = (unsigned int)**(short**)((char*)this + 0x850)), i < (int)itemCount; i++) {
		*(float*)(item + 0x10) = 1.0f;
		*(float*)(item + 0x14) = 1.0f;
		item += 0x40;
	}

	startFrame = 0;
	offset = ((int)itemCount - 1) * 0x40;
	if (-1 < (int)(itemCount - 1)) {
		chunkCount = itemCount >> 3;
		if (chunkCount != 0) {
			do {
				item = *(int*)((char*)this + 0x850) + offset + 8;
				*(int*)(item + 0x24) = startFrame;
				*(int*)(item + 0x28) = 4;
				item = *(int*)((char*)this + 0x850) + offset - 0x38;
				*(int*)(item + 0x24) = startFrame + 1;
				*(int*)(item + 0x28) = 4;
				item = *(int*)((char*)this + 0x850) + offset - 0x78;
				*(int*)(item + 0x24) = startFrame + 2;
				*(int*)(item + 0x28) = 4;
				item = *(int*)((char*)this + 0x850) + offset - 0xb8;
				*(int*)(item + 0x24) = startFrame + 3;
				*(int*)(item + 0x28) = 4;
				item = *(int*)((char*)this + 0x850) + offset - 0xf8;
				*(int*)(item + 0x24) = startFrame + 4;
				*(int*)(item + 0x28) = 4;
				item = *(int*)((char*)this + 0x850) + offset - 0x138;
				*(int*)(item + 0x24) = startFrame + 5;
				*(int*)(item + 0x28) = 4;
				item = *(int*)((char*)this + 0x850) + offset - 0x178;
				*(int*)(item + 0x24) = startFrame + 6;
				*(int*)(item + 0x28) = 4;
				item = *(int*)((char*)this + 0x850) + offset - 0x1b8;
				offset -= 0x200;
				*(int*)(item + 0x24) = startFrame + 7;
				startFrame += 8;
				*(int*)(item + 0x28) = 4;
				chunkCount--;
			} while (chunkCount != 0);

			itemCount &= 7;
			if (itemCount == 0) {
				*(short*)(*(int*)((char*)this + 0x82c) + 0x22) = 0;
				return;
			}
		}

		do {
			item = *(int*)((char*)this + 0x850) + offset + 8;
			offset -= 0x40;
			*(int*)(item + 0x24) = startFrame;
			startFrame++;
			*(int*)(item + 0x28) = 4;
			itemCount--;
		} while (itemCount != 0);
	}

	*(short*)(*(int*)((char*)this + 0x82c) + 0x22) = 0;
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
	int completedItems = 0;
	
	// Increment animation frame counter
	*(short*)((char*)this + 0x82c + 0x22) += 1;
	int currentFrame = *(short*)((char*)this + 0x82c + 0x22);
	
	int itemCount = **(short**)((char*)this + 0x850);
	short* itemPtr = *(short**)((char*)this + 0x850) + 4;
	
	// Update each item's fade-out animation
	for (int i = 0; i < itemCount; i++) {
		int startFrame = *(int*)(itemPtr + 0x12);
		int duration = *(int*)(itemPtr + 0x14);
		
		if (startFrame <= currentFrame) {
			if (currentFrame < startFrame + duration) {
				// Animate fade-out
				*(int*)(itemPtr + 0x10) += 1;
				int progress = *(int*)(itemPtr + 0x10);
				
				// Calculate fade-out alpha (1.0 - progress/duration)
				float alpha = 1.0f - (float)progress / (float)duration;
				if (alpha < 0.0f) {
					alpha = 0.0f;
				}
				*(float*)(itemPtr + 8) = alpha;
			} else {
				// Animation complete
				completedItems++;
				*(float*)(itemPtr + 8) = 0.0f;
			}
		}
		
		itemPtr += 0x20;
	}
	
	// Check if all animations are complete
	if (itemCount == completedItems) {
		// Reset all animation states
		itemPtr = *(short**)((char*)this + 0x850) + 4;
		for (int i = 0; i < itemCount; i++) {
			*(short*)(itemPtr + 0x12) = 0;  // Reset start frame
			*(short*)(itemPtr + 0x13) = 0;
			*(short*)(itemPtr + 0x14) = 0;  // Reset duration
			*(short*)(itemPtr + 0x15) = 1;
			*(float*)(itemPtr + 8) = 0.0f;  // Zero alpha
			itemPtr += 0x20;
		}
		return 1;  // Close animation complete
	}
	
	return 0;  // Still animating
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
	SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

	int menuState = *(int*)((char*)this + 0x82c);
	int listBase = *(int*)((char*)this + 0x850);
	short menuMode = *(short*)(menuState + 0x10);
	short cursor = *(short*)(menuState + 0x26);
	short* item = (short*)(listBase + 8);
	int itemCount = **(short**)((char*)this + 0x850);

	for (int i = 0; i < itemCount; i++) {
		int tex = *(int*)(item + 0xe);
		if (tex >= 0) {
			float x = (float)item[0];
			float y = (float)item[1];
			float w = (float)item[2];
			float h = (float)item[3];
			float alpha = *(float*)(item + 8);

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
			GXColor color = {0xff, 0xff, 0xff, (unsigned char)(255.0f * alpha)};
			GXSetChanMatColor(GX_COLOR0A0, color);

			float v = 0.0f;
			if ((menuMode == 1) && (i == cursor)) {
				x += 6.0f;
				v += h;
			}

			DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, y, w, h, 0.0f, v, *(float*)(item + 10), *(float*)(item + 10), 0.0f);

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x5c);
			v = 0.0f;
			if ((menuMode == 1) && (i == cursor)) {
				v += h;
			}
			DrawRect__8CMenuPcsFUlfffffffff(this, 0, -((48.0f * 1.5f) - (float)item[0]), (float)item[1] - 6.0f, 48.0f, 48.0f, 0.0f, v, *(float*)(item + 10), *(float*)(item + 10), 0.0f);
		}
		item += 0x20;
	}

	CFont* font = *(CFont**)((char*)this + 0x108);
	SetMargin__5CFontFf(1.0f, font);
	SetShadow__5CFontFi(font, 0);
	SetScale__5CFontFf(1.0f, font);
	DrawInit__5CFontFv(font);

	item = (short*)(listBase + 8);
	for (int i = 0; i < itemCount; i++) {
		GXColor color = {0xff, 0xff, 0xff, (unsigned char)(255.0f * *(float*)(item + 8))};
		SetColor__5CFontF8_GXColor(font, &color);

		const char* text = GetMenuStr__8CMenuPcsFi(this, i + 0x2e);
		GetWidth__5CFontFPc(font, text);

		float textX = (float)(item[0] + 0x28);
		float textY = (float)(item[1] + 3);
		if ((menuMode == 1) && (i == cursor)) {
			textX += 6.0f;
		}

		SetPosX__5CFontFf(textX, font);
		SetPosY__5CFontFf(textY, font);
		Draw__5CFontFPc(font, text);

		item += 0x20;
	}

	DrawInit__8CMenuPcsFv(this);
	if (menuMode == 1) {
		short* curItem = (short*)(listBase + cursor * 0x40 + 8);
		int cursorY = (int)((float)curItem[1] + (((float)curItem[3] - 32.0f) * 1.5f));
		int cursorX = (int)((float)curItem[0] - 56.0f + (float)(System.m_frameCounter & 7));
		DrawCursor__8CMenuPcsFiif(this, cursorX, cursorY, 1.0f);
	}

	DrawInit__8CMenuPcsFv(this);
	GXColor helpColor = {0xff, 0xff, 0xff, (unsigned char)(255.0f * *(float*)(listBase + 0x18))};
	DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(this, cursor + 0x25c, font, 0, -20, helpColor, 0, 1.0f, 0.0f);
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
