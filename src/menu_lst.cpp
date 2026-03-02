#include "ffcc/menu_lst.h"
#include "ffcc/color.h"
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
extern CMenuPcs MenuPcs;

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
	int completedItems;
	unsigned int itemCount;
	short* itemPtr;

	if (*(char*)((char*)this + 0x82c + 0xb) == 0) {
		int offset;
		int i;
		short yPos;
		short initializedCount;

		memset(*(void**)((char*)this + 0x850), 0, 0x1008);

		offset = *(int*)((char*)this + 0x850) + 8;
		i = 8;
		do {
			*(float*)(offset + 0x14) = 1.0f;
			*(float*)(offset + 0x54) = 1.0f;
			*(float*)(offset + 0x94) = 1.0f;
			*(float*)(offset + 0xd4) = 1.0f;
			*(float*)(offset + 0x114) = 1.0f;
			*(float*)(offset + 0x154) = 1.0f;
			*(float*)(offset + 0x194) = 1.0f;
			*(float*)(offset + 0x1d4) = 1.0f;
			offset += 0x200;
			i--;
		} while (i != 0);

		initializedCount = 0;
		offset = 0;
		i = 0;
		yPos = 0x18;
		do {
			short* entry = (short*)(*(int*)((char*)this + 0x850) + offset + 8);

			*(int*)(entry + 0x16) = 2;
			initializedCount++;
			*(int*)(entry + 0xe) = 0x5b;
			offset += 0x40;
			entry[2] = 0xe0;
			entry[3] = 0x28;
			*entry = (short)(int)(320.0 - ((double)entry[2] * 0.5));
			entry[1] = yPos;
			yPos += 0x20;
			*(float*)(entry + 4) = 1.0f;
			*(float*)(entry + 6) = 1.0f;
			*(int*)(entry + 0x12) = i;
			i++;
			*(int*)(entry + 0x14) = 4;
		} while (i < 9);

		**(short**)((char*)this + 0x850) = initializedCount;
		*(char*)((char*)this + 0x82c + 0xb) = 1;
	}

	completedItems = 0;
	*(short*)((char*)this + 0x82c + 0x22) = *(short*)((char*)this + 0x82c + 0x22) + 1;
	itemCount = (unsigned int)**(short**)((char*)this + 0x850);
	itemPtr = *(short**)((char*)this + 0x850) + 4;
	if ((int)itemCount > 0) {
		unsigned int i = itemCount;
		int currentFrame = (int)*(short*)(*(int*)((char*)this + 0x82c) + 0x22);
		do {
			if (*(int*)(itemPtr + 0x12) <= currentFrame) {
				if (currentFrame < *(int*)(itemPtr + 0x12) + *(int*)(itemPtr + 0x14)) {
					*(int*)(itemPtr + 0x10) = *(int*)(itemPtr + 0x10) + 1;
					*(float*)(itemPtr + 8) = (float)*(int*)(itemPtr + 0x10) / (float)*(int*)(itemPtr + 0x14);
				} else {
					completedItems++;
					*(float*)(itemPtr + 8) = 1.0f;
				}
			}
			itemPtr += 0x20;
			i--;
		} while (i != 0);
	}

	if (**(short**)((char*)this + 0x850) == completedItems) {
		itemPtr = *(short**)((char*)this + 0x850) + 4;
		if ((int)itemCount > 0) {
			unsigned int blocks = itemCount >> 3;
			if (blocks != 0) {
				do {
					itemPtr[0x12] = 0;
					itemPtr[0x13] = 0;
					itemPtr[0x14] = 0;
					itemPtr[0x15] = 1;
					*(float*)(itemPtr + 8) = 1.0f;
					itemPtr[0x32] = 0;
					itemPtr[0x33] = 0;
					itemPtr[0x34] = 0;
					itemPtr[0x35] = 1;
					*(float*)(itemPtr + 0x28) = 1.0f;
					itemPtr[0x52] = 0;
					itemPtr[0x53] = 0;
					itemPtr[0x54] = 0;
					itemPtr[0x55] = 1;
					*(float*)(itemPtr + 0x48) = 1.0f;
					itemPtr[0x72] = 0;
					itemPtr[0x73] = 0;
					itemPtr[0x74] = 0;
					itemPtr[0x75] = 1;
					*(float*)(itemPtr + 0x68) = 1.0f;
					itemPtr[0x92] = 0;
					itemPtr[0x93] = 0;
					itemPtr[0x94] = 0;
					itemPtr[0x95] = 1;
					*(float*)(itemPtr + 0x88) = 1.0f;
					itemPtr[0xb2] = 0;
					itemPtr[0xb3] = 0;
					itemPtr[0xb4] = 0;
					itemPtr[0xb5] = 1;
					*(float*)(itemPtr + 0xa8) = 1.0f;
					itemPtr[0xd2] = 0;
					itemPtr[0xd3] = 0;
					itemPtr[0xd4] = 0;
					itemPtr[0xd5] = 1;
					*(float*)(itemPtr + 0xc8) = 1.0f;
					itemPtr[0xf2] = 0;
					itemPtr[0xf3] = 0;
					itemPtr[0xf4] = 0;
					itemPtr[0xf5] = 1;
					*(float*)(itemPtr + 0xe8) = 1.0f;
					itemPtr += 0x100;
					blocks--;
				} while (blocks != 0);

				itemCount &= 7;
				if (itemCount == 0) {
					return 1;
				}
			}

			do {
				itemPtr[0x12] = 0;
				itemPtr[0x13] = 0;
				itemPtr[0x14] = 0;
				itemPtr[0x15] = 1;
				*(float*)(itemPtr + 8) = 1.0f;
				itemPtr += 0x20;
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
void CMenuPcs::MLstClose()
{
	float fVar1;
	short* psVar4;
	int iVar5;
	unsigned int uVar6;
	int iVar7;
	unsigned int uVar8;

	iVar5 = 0;
	*(short*)(*(int*)((char*)this + 0x82c) + 0x22) = *(short*)(*(int*)((char*)this + 0x82c) + 0x22) + 1;
	uVar6 = (unsigned int)**(short**)((char*)this + 0x850);
	psVar4 = *(short**)((char*)this + 0x850) + 4;
	iVar7 = (int)*(short*)(*(int*)((char*)this + 0x82c) + 0x22);
	uVar8 = uVar6;
	if (0 < (int)uVar6) {
		do {
			if (*(int*)(psVar4 + 0x12) <= iVar7) {
				if (iVar7 < *(int*)(psVar4 + 0x12) + *(int*)(psVar4 + 0x14)) {
					*(int*)(psVar4 + 0x10) = *(int*)(psVar4 + 0x10) + 1;
					*(float*)(psVar4 + 8) = (float)(1.0 - ((1.0 / (double)*(int*)(psVar4 + 0x14)) * (double)*(int*)(psVar4 + 0x10)));
					if (*(float*)(psVar4 + 8) < 0.0f) {
						*(float*)(psVar4 + 8) = 0.0f;
					}
				} else {
					iVar5 = iVar5 + 1;
					*(float*)(psVar4 + 8) = 0.0f;
				}
			}
			psVar4 = psVar4 + 0x20;
			uVar8 = uVar8 - 1;
		} while (uVar8 != 0);
	}
	fVar1 = 0.0f;
	if (**(short**)((char*)this + 0x850) == iVar5) {
		psVar4 = *(short**)((char*)this + 0x850) + 4;
		if (0 < (int)uVar6) {
			uVar8 = uVar6 >> 3;
			if (uVar8 != 0) {
				do {
					*(int*)(psVar4 + 0x12) = 0;
					*(int*)(psVar4 + 0x14) = 0;
					*(int*)(psVar4 + 0x16) = 1;
					*(float*)(psVar4 + 8) = fVar1;
					*(int*)(psVar4 + 0x32) = 0;
					*(int*)(psVar4 + 0x34) = 0;
					*(int*)(psVar4 + 0x36) = 1;
					*(float*)(psVar4 + 0x28) = fVar1;
					*(int*)(psVar4 + 0x52) = 0;
					*(int*)(psVar4 + 0x54) = 0;
					*(int*)(psVar4 + 0x56) = 1;
					*(float*)(psVar4 + 0x48) = fVar1;
					*(int*)(psVar4 + 0x72) = 0;
					*(int*)(psVar4 + 0x74) = 0;
					*(int*)(psVar4 + 0x76) = 1;
					*(float*)(psVar4 + 0x68) = fVar1;
					*(int*)(psVar4 + 0x92) = 0;
					*(int*)(psVar4 + 0x94) = 0;
					*(int*)(psVar4 + 0x96) = 1;
					*(float*)(psVar4 + 0x88) = fVar1;
					*(int*)(psVar4 + 0xb2) = 0;
					*(int*)(psVar4 + 0xb4) = 0;
					*(int*)(psVar4 + 0xb6) = 1;
					*(float*)(psVar4 + 0xa8) = fVar1;
					*(int*)(psVar4 + 0xd2) = 0;
					*(int*)(psVar4 + 0xd4) = 0;
					*(int*)(psVar4 + 0xd6) = 1;
					*(float*)(psVar4 + 200) = fVar1;
					*(int*)(psVar4 + 0xf2) = 0;
					*(int*)(psVar4 + 0xf4) = 0;
					*(int*)(psVar4 + 0xf6) = 1;
					*(float*)(psVar4 + 0xe8) = fVar1;
					psVar4 = psVar4 + 0x100;
					uVar8 = uVar8 - 1;
				} while (uVar8 != 0);
				uVar6 = uVar6 & 7;
				if (uVar6 == 0) {
					return;
				}
			}
			do {
				*(int*)(psVar4 + 0x12) = 0;
				*(int*)(psVar4 + 0x14) = 0;
				*(int*)(psVar4 + 0x16) = 1;
				*(float*)(psVar4 + 8) = fVar1;
				psVar4 = psVar4 + 0x20;
				uVar6 = uVar6 - 1;
			} while (uVar6 != 0);
		}
		return;
	}
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

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, tex);
			GXColor color = {0xff, 0xff, 0xff, (unsigned char)(int)(255.0f * alpha)};
			GXSetChanMatColor(GX_COLOR0A0, color);

			float v = 0.0f;
			if ((menuMode == 1) && (i == cursor)) {
				x += 6.0f;
				v += h;
			}

			DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, x, y, w, h, 0.0f, v, *(float*)(item + 10), *(float*)(item + 10), 0.0f);

			SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(&MenuPcs, 0x5c);
			v = 0.0f;
			if ((menuMode == 1) && (i == cursor)) {
				v += h;
			}
			DrawRect__8CMenuPcsFUlfffffffff(&MenuPcs, 0, -((48.0f * 1.5f) - (float)item[0]), (float)item[1] - 6.0f, 48.0f, 48.0f, 0.0f, v, *(float*)(item + 10), *(float*)(item + 10), 0.0f);
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
		CColor color(0xff, 0xff, 0xff, (unsigned char)(int)(255.0f * *(float*)(item + 8)));
		SetColor__5CFontF8_GXColor(font, &color.color);

		const char* text = GetMenuStr__8CMenuPcsFi(&MenuPcs, i + 0x2e);
		GetWidth__5CFontFPc(font, text);

		float textX = (float)(item[0] + 0x28);
		float textY = (float)(item[1] + 3);
		if ((menuMode == 1) && (i == cursor)) {
			textX += 6.0f;
		}

		SetPosX__5CFontFf(textX, font);
		SetPosY__5CFontFf(textY - 1.0f, font);
		Draw__5CFontFPc(font, text);

		item += 0x20;
	}

	DrawInit__8CMenuPcsFv(&MenuPcs);
	if (menuMode == 1) {
		short* curItem = (short*)(listBase + cursor * 0x40 + 8);
		int frame = (int)System.m_frameCounter;
		int frameSign = frame >> 31;
		int anim = ((frameSign * 8) | ((frame * 0x20000000 + frameSign) >> 29)) - frameSign;
		int cursorY = (int)((float)curItem[1] + (((float)curItem[3] - 32.0f) * 1.5f));
		int cursorX = (int)((float)curItem[0] - 56.0f + (float)anim);
		DrawCursor__8CMenuPcsFiif(&MenuPcs, cursorX, cursorY, 1.0f);
	}

	DrawInit__8CMenuPcsFv(&MenuPcs);
	CColor helpColor(0xff, 0xff, 0xff, (unsigned char)(int)(255.0f * *(float*)(listBase + 0x18)));
	DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(&MenuPcs, cursor + 0x25c, font, 0, -20, helpColor.color, 0, 1.0f, 0.0f);
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
