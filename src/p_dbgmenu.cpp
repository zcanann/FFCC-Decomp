#include "ffcc/p_dbgmenu.h"
#include "ffcc/graphic.h"
#include "ffcc/pad.h"
#include "ffcc/system.h"
#include <dolphin/gx.h>
#include <string.h>

extern unsigned char CFlat[];
extern unsigned char DAT_8032e698;
extern unsigned char DAT_8032ecd8;
extern unsigned char CharaPcs[];
extern unsigned char PartMng[];
extern unsigned char PartPcs[];
extern unsigned char Sound[];
extern char s_Debug_80331c90[];
extern u32 PTR_DAT_80212524;

extern "C" int __cntlzw(unsigned int);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, int, int, int, int, void*, void*);
extern "C" void CheckDriver__6CSoundFi(void*, int);
extern "C" void pppDumpMngSt__8CPartMngFv(void*);
extern "C" void DumpLoad__9CCharaPcsFv(void*);

/*
 * --INFO--
 * PAL Address: 0x8012d288
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_dbgmenu_cpp()
{
	// Static initialization function for debug menu system
	// Initialize MiniGamePcs structure
	// memset calls for initialization
	memset((void*)0x80306710, 0, 0x34);
	memset((void*)0x80306744, 0, 0x20);
	
	// Initialize debug menu array with constructor calls
	// __construct_array call for CDM objects
	
	// Set up vtable pointers and function pointers
	// These appear to be vtable entries for CDbgMenuPcs
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CDbgMenuPcs::CDbgMenuPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::Init()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::selectNext()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::selectPrev()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::calc()
{
	unsigned short padInput;
	unsigned int flags;
	int menuPtr;
	int cursorPtr;
	int stackData[3];

	if (*(int*)((char*)this + 0x58) == 0) {
		return;
	}

	if (Pad._452_4_ == 0) {
		padInput = *(unsigned short*)((unsigned char*)&Pad._8_2_ +
		                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) *
		                               0x54));
	} else {
		padInput = 0;
	}

	if ((padInput & 0x100) != 0) {
		switch (*(int*)(*(int*)((char*)this + 0x2a5c) + 0x38)) {
		case 100:
			*(unsigned int*)(CFlat + 0x12A4) = ~*(unsigned int*)(CFlat + 0x12A4);
			break;
		case 0x65:
			stackData[0] = 0;
			stackData[2] = 0;
			flags = (unsigned int)__cntlzw((int)((signed char)CFlat[0x12E4] >> 7));
			flags = ((int)(char)(flags >> 5) & 1U) << 7 | ((unsigned char)CFlat[0x12E4] & 0x7F);
			CFlat[0x12E4] = (unsigned char)flags;
			stackData[1] = (int)(flags << 0x18) >> 0x1f;
			SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
			    CFlat, 0, 1, 9, 3, stackData, 0);
			break;
		case 0x66:
			flags = (unsigned int)__cntlzw((int)(char)((int)((unsigned int)(unsigned char)CFlat[0x12E4] << 0x1d) >> 0x1f));
			CFlat[0x12E4] = (unsigned char)((((int)(char)(flags >> 5) << 2) & 4) | (CFlat[0x12E4] & 0xFB));
			break;
		case 0x67:
			*(unsigned int*)((char*)this + 4) ^= 1;
			break;
		case 0x68:
			*(unsigned int*)((char*)this + 4) ^= 2;
			break;
		case 0x69:
			*(unsigned int*)((char*)this + 4) ^= 4;
			break;
		case 0x6A:
			*(unsigned int*)((char*)this + 4) ^= 8;
			break;
		case 0x6B:
			*(unsigned int*)((char*)this + 4) ^= 0x10;
			break;
		case 0x6C:
			*(unsigned int*)((char*)this + 4) ^= 0x20;
			break;
		case 0x6D:
			*(unsigned int*)((char*)this + 4) ^= 0x40;
			break;
		case 0x6E:
			*(unsigned int*)((char*)this + 4) ^= 0x80;
			break;
		case 0x6F:
			*(unsigned int*)((char*)this + 4) ^= 0x100;
			break;
		case 0x70:
			*(unsigned int*)((char*)this + 4) ^= 0x200;
			break;
		case 0x71:
			*(unsigned int*)((char*)this + 4) ^= 0x400;
			break;
		case 0x72:
			*(unsigned int*)((char*)this + 4) ^= 0x800;
			flags = (unsigned int)__cntlzw(*(unsigned int*)((char*)this + 4) & 0x800);
			PartPcs[0x34] = (unsigned char)(flags >> 5);
			break;
		case 0x73:
			*(unsigned int*)((char*)this + 4) ^= 0x1000;
			break;
		case 0x74:
			CheckDriver__6CSoundFi(Sound, 1);
			break;
		case 0x75:
			DAT_8032ecd8 = 1 - DAT_8032ecd8;
			break;
		case 0x76:
			DAT_8032e698 = 1 - DAT_8032e698;
			pppDumpMngSt__8CPartMngFv(PartMng);
			break;
		case 0x77:
			DumpLoad__9CCharaPcsFv(CharaPcs);
			break;
		case 0x78:
			*(unsigned int*)((char*)this + 4) ^= 0x2000;
			break;
		case 0x79:
			*(unsigned int*)((char*)this + 4) ^= 0x4000;
			break;
		case 0x7A:
			*(unsigned int*)((char*)this + 4) ^= 0x8000;
			break;
		}
	}

	if (Pad._452_4_ == 0) {
		padInput = *(unsigned short*)((unsigned char*)&Pad._8_2_ +
		                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) *
		                               0x54));
	} else {
		padInput = 0;
	}
	if ((padInput & 4) != 0) {
		menuPtr = *(int*)((char*)this + 0x2a5c);
		*(unsigned char*)(menuPtr + 0x34) &= 0xBF;
		do {
			*(int*)((char*)this + 0x2a5c) = *(int*)(*(int*)((char*)this + 0x2a5c) + 0x48);
			cursorPtr = *(int*)((char*)this + 0x2a5c);
			if ((*(unsigned int*)(cursorPtr + 4) & 1) != 0) {
				break;
			}
		} while (menuPtr != cursorPtr);
		*(unsigned char*)(cursorPtr + 0x34) = (*(unsigned char*)(cursorPtr + 0x34) & 0xBF) | 0x40;
	}

	if (Pad._452_4_ == 0) {
		padInput = *(unsigned short*)((unsigned char*)&Pad._8_2_ +
		                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) *
		                               0x54));
	} else {
		padInput = 0;
	}
	if ((padInput & 8) != 0) {
		menuPtr = *(int*)((char*)this + 0x2a5c);
		*(unsigned char*)(menuPtr + 0x34) &= 0xBF;
		do {
			*(int*)((char*)this + 0x2a5c) = *(int*)(*(int*)((char*)this + 0x2a5c) + 0x44);
			cursorPtr = *(int*)((char*)this + 0x2a5c);
			if ((*(unsigned int*)(cursorPtr + 4) & 1) != 0) {
				break;
			}
		} while (menuPtr != cursorPtr);
		*(unsigned char*)(cursorPtr + 0x34) = (*(unsigned char*)(cursorPtr + 0x34) & 0xBF) | 0x40;
	}

	if (*(int*)((char*)this + 0x58) != 0) {
		calcMenu(*(CDM**)((char*)this + 0x58));
	}

	if (Pad._452_4_ == 0) {
		padInput = *(unsigned short*)((unsigned char*)&Pad._8_2_ +
		                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) *
		                               0x54));
	} else {
		padInput = 0;
	}
	if ((padInput & 0x200) != 0) {
		memset((char*)this + 0x5C, 0, 0x2A00);
		*(int*)((char*)this + 0x58) = 0;
		*(int*)((char*)this + 0x2A60) = 0;
		*(int*)((char*)this + 0x2A5C) = 0;
	}

	Pad._452_4_ = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::draw()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8012cac0
 * PAL Size: 592b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::calcMenu(CDbgMenuPcs::CDM* menu)
{
	CDM* head = menu;
	do {
		*(CDM**)((char*)this + 0x2A5C) = menu;
		switch (*(int*)((char*)menu + 0x38)) {
		case 100:
			*(u32*)((char*)menu + 0x30) = *(u32*)(CFlat + 0x12A4) != 0;
			break;
		case 0x65:
			*(u32*)((char*)menu + 0x30) = *(signed char*)(CFlat + 0x12E4) < 0;
			break;
		case 0x66:
			*(u32*)((char*)menu + 0x30) = ((*(u8*)(CFlat + 0x12E4) >> 3) & 1) != 0;
			break;
		case 0x67:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 0) & 1;
			break;
		case 0x68:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 1) & 1;
			break;
		case 0x69:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 2) & 1;
			break;
		case 0x6A:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 3) & 1;
			break;
		case 0x6B:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 4) & 1;
			break;
		case 0x6C:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 5) & 1;
			break;
		case 0x6D:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 6) & 1;
			break;
		case 0x6E:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 7) & 1;
			break;
		case 0x6F:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 8) & 1;
			break;
		case 0x70:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 9) & 1;
			break;
		case 0x71:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 10) & 1;
			break;
		case 0x72:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 11) & 1;
			break;
		case 0x73:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 12) & 1;
			break;
		case 0x75:
			*(u32*)((char*)menu + 0x30) = DAT_8032ecd8 != 0;
			break;
		case 0x76:
			*(u32*)((char*)menu + 0x30) = DAT_8032e698 != 0;
			break;
		case 0x78:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 13) & 1;
			break;
		case 0x79:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 14) & 1;
			break;
		case 0x7A:
			*(u32*)((char*)menu + 0x30) = (*(u32*)((char*)this + 4) >> 15) & 1;
			break;
		}

		*(int*)((char*)menu + 0x3C) = *(int*)((char*)*(CDM**)((char*)menu + 0x4C) + 0x10) + *(int*)((char*)menu + 0x10);
		*(int*)((char*)menu + 0x40) = *(int*)((char*)*(CDM**)((char*)menu + 0x4C) + 0x14) + *(int*)((char*)menu + 0x14);

		if (*(CDM**)((char*)menu + 0x50) != 0) {
			calcMenu(*(CDM**)((char*)menu + 0x50));
		}

		menu = *(CDM**)((char*)menu + 0x48);
	} while (menu != head);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::drawMenu(CDbgMenuPcs::CDM*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::changeVtxFmt(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8012c274
 * PAL Size: 1336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::drawWindow(int x, int y, int width, int height, int flags, char* text)
{
	// Set up GX vertex format if not already done
	if (*(int*)((char*)this + 0x2a68) != 1) {
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
		GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
		GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
		GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		*(int*)((char*)this + 0x2a68) = 1;
	}

	// Draw window border if flag is not set
	if ((flags & 1) == 0) {
		GXBegin(GX_QUADS, GX_VTXFMT1, 4);
		// Window border quad rendering
		for (int i = 0; i < 4; i++) {
			float xPos = (float)(x + (width & (i & 1 ? -1 : 0)));
			float yPos = (float)(y + (height & (i > 1 ? -1 : 0)));
			GXPosition3f32(xPos, yPos, 0.0f);
			GXColor1u32(0x808080ff); // Gray border color
		}
	}

	// Draw window triangles
	GXBegin(GX_TRIANGLES, GX_VTXFMT1, 3);
	int colorOffset = (flags >> 1 & 1) * 4;
	GXPosition3f32((float)(x + width), (float)y, 0.0f);
	GXColor1u32(0x404040ff); // Dark color
	GXPosition3f32((float)x, (float)y, 0.0f);
	GXColor1u32(0x404040ff);
	GXPosition3f32((float)x, (float)(y + height), 0.0f);
	GXColor1u32(0x404040ff);

	GXBegin(GX_TRIANGLES, GX_VTXFMT1, 3);
	GXPosition3f32((float)(x + width), (float)y, 0.0f);
	GXColor1u32(0x808080ff); // Light color
	GXPosition3f32((float)(x + width), (float)(y + height), 0.0f);
	GXColor1u32(0x808080ff);
	GXPosition3f32((float)x, (float)(y + height), 0.0f);
	GXColor1u32(0x808080ff);

	// Draw selection highlight if flag is set
	char selectionFlag = *(char*)(*(int*)((char*)this + 0x2a5c) + 0x34);
	if (selectionFlag < 0) {
		unsigned char alpha = 0xc0;
		if ((System.m_frameCounter >> 2 & 1) != 0) {
			alpha = 0xff;
		}
		u32 highlightColor = (alpha << 24) | (alpha << 16) | (alpha << 8) | 0xff;

		GXBegin(GX_QUADS, GX_VTXFMT1, 5);
		// Highlight border
		GXPosition3f32((float)(x + width + 1), (float)(y - 1), 0.0f);
		GXColor1u32(highlightColor);
		GXPosition3f32((float)(x - 1), (float)(y - 1), 0.0f);
		GXColor1u32(highlightColor);
		GXPosition3f32((float)(x - 1), (float)(y + height + 1), 0.0f);
		GXColor1u32(highlightColor);
		GXPosition3f32((float)(x + width + 1), (float)(y + height + 1), 0.0f);
		GXColor1u32(highlightColor);
		GXPosition3f32((float)(x + width + 1), (float)(y - 1), 0.0f);
		GXColor1u32(highlightColor);
	}

	// Draw text if provided
	if (text != nullptr) {
		drawFont(5, x + 8, y - 6, text);
	}
}

/*
 * --INFO--
 * PAL Address: 0x8012bd4c
 * PAL Size: 1320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::drawFont(int flags, int x, int y, char* text)
{
	// Reset GX state if needed
	if (*(int*)((char*)this + 0x2a68) != 0) {
		GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
		*(int*)((char*)this + 0x2a68) = 0;
	}

	// Draw drop shadow if flag is set
	if ((flags & 4) != 0) {
		changeVtxFmt(0);
		GXColor shadowColor = {0, 0, 0, 255};
		GXSetChanMatColor(GX_COLOR0A0, shadowColor);

		int fontSize = 10;
		if ((flags & 1) != 0) {
			fontSize = 8;
		}

		short shadowX = x - 1;
		short shadowY = y;
		if ((flags & 8) != 0) {
			// Center text
			int textLen = strlen(text);
			shadowX = x - (short)((fontSize * textLen) >> 1);
			shadowY = y - (short)(fontSize >> 1);
		}

		// Draw shadow in 4 directions
		Graphic.DrawDebugStringDirect(shadowX, shadowY, text, fontSize);
		Graphic.DrawDebugStringDirect(x, shadowY + 1, text, fontSize);
		Graphic.DrawDebugStringDirect(x + 1, shadowY, text, fontSize);
		Graphic.DrawDebugStringDirect(x, shadowY - 1, text, fontSize);
	}

	// Draw main text
	GXColor mainColor = {255, 255, 255, 255}; // Default white
	if ((flags & 2) != 0) {
		mainColor.r = mainColor.g = mainColor.b = 0; // Black text
	}
	GXSetChanMatColor(GX_COLOR0A0, mainColor);

	int fontSize = 10;
	if ((flags & 1) != 0) {
		fontSize = 8;
	}

	short finalX = x;
	short finalY = y;
	if ((flags & 8) != 0) {
		// Center text
		int textLen = strlen(text);
		finalX = x - (short)((fontSize * textLen) >> 1);
		finalY = y - (short)(fontSize >> 1);
	}

	Graphic.DrawDebugStringDirect(finalX, finalY, text, fontSize);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::searchFreeCDM()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8012bb0c
 * PAL Size: 576b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CDbgMenuPcs::searchID(int id, CDbgMenuPcs::CDM& root)
{
	int* next;
	CDM* result;
	CDM* node = &root;
	do {
		if (*(int*)((char*)node + 0x38) == id) {
			return (int)node;
		}
		CDM* first = *(CDM**)((char*)node + 0x50);
		CDM* cur1 = first;
		if (first != 0) {
			do {
				result = cur1;
				if (*(int*)((char*)cur1 + 0x38) == id) {
					goto level1_done;
				}
				CDM* first2 = *(CDM**)((char*)cur1 + 0x50);
				CDM* cur2 = first2;
				if (first2 != 0) {
					do {
						result = cur2;
						if (*(int*)((char*)cur2 + 0x38) == id) {
							goto level2_done;
						}
						CDM* first3 = *(CDM**)((char*)cur2 + 0x50);
						CDM* cur3 = first3;
						if (first3 != 0) {
							do {
								result = cur3;
								if (*(int*)((char*)cur3 + 0x38) == id) {
									goto level3_done;
								}
								CDM* first4 = *(CDM**)((char*)cur3 + 0x50);
								CDM* cur4 = first4;
								if (first4 != 0) {
									do {
										result = cur4;
										if (*(int*)((char*)cur4 + 0x38) == id) {
											goto level4_done;
										}
										CDM* first5 = *(CDM**)((char*)cur4 + 0x50);
										CDM* cur5 = first5;
										if (first5 != 0) {
											do {
												result = cur5;
												if (*(int*)((char*)cur5 + 0x38) == id) {
													goto level5_done;
												}
												CDM* first6 = *(CDM**)((char*)cur5 + 0x50);
												CDM* cur6 = first6;
												if (first6 != 0) {
													do {
														result = cur6;
														if (*(int*)((char*)cur6 + 0x38) == id) {
															goto level6_done;
														}
														CDM* first7 = *(CDM**)((char*)cur6 + 0x50);
														CDM* cur7 = first7;
														if (first7 != 0) {
															do {
																result = cur7;
																if ((*(int*)((char*)cur7 + 0x38) == id) ||
																	((*(CDM**)((char*)cur7 + 0x50) != 0 &&
																	  (result = (CDM*)searchID(
																		  id, **(CDM**)((char*)cur7 + 0x50)),
																	   result != 0)))) {
																	goto level7_done;
																}
																next = (int*)((char*)cur7 + 0x48);
																cur7 = (CDM*)*next;
															} while ((CDM*)*next != first7);
															result = 0;
level7_done:
															if (result != 0) {
																goto level6_done;
															}
														}
														next = (int*)((char*)cur6 + 0x48);
														cur6 = (CDM*)*next;
													} while ((CDM*)*next != first6);
													result = 0;
level6_done:
													if (result != 0) {
														goto level5_done;
													}
												}
												next = (int*)((char*)cur5 + 0x48);
												cur5 = (CDM*)*next;
											} while ((CDM*)*next != first5);
											result = 0;
level5_done:
											if (result != 0) {
												goto level4_done;
											}
										}
										next = (int*)((char*)cur4 + 0x48);
										cur4 = (CDM*)*next;
									} while ((CDM*)*next != first4);
									result = 0;
level4_done:
									if (result != 0) {
										goto level3_done;
									}
								}
								next = (int*)((char*)cur3 + 0x48);
								cur3 = (CDM*)*next;
							} while ((CDM*)*next != first3);
							result = 0;
level3_done:
							if (result != 0) {
								goto level2_done;
							}
						}
						next = (int*)((char*)cur2 + 0x48);
						cur2 = (CDM*)*next;
					} while ((CDM*)*next != first2);
					result = 0;
level2_done:
					if (result != 0) {
						goto level1_done;
					}
				}
				next = (int*)((char*)cur1 + 0x48);
				cur1 = (CDM*)*next;
			} while ((CDM*)*next != first);
			result = 0;
level1_done:
			if (result != 0) {
				return (int)result;
			}
		}
		node = *(CDM**)((char*)node + 0x48);
		if (node == &root) {
			return 0;
		}
	} while (1);
}

/*
 * --INFO--
 * PAL Address: 0x8012b8c0
 * PAL Size: 588b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::Add()
{
	if (*(int*)((char*)this + 0x58) != 0) {
		return;
	}

	u32 rootParam[13];
	u32 nodeParam[13];
	u32 actionParam[13];
	u32* menuDefs = &PTR_DAT_80212524;

	memset(rootParam, 0, sizeof(rootParam));
	memset(nodeParam, 0, sizeof(nodeParam));

	rootParam[0] = 0;
	rootParam[1] = 0;
	rootParam[2] = 0;
	rootParam[3] = 0;
	rootParam[4] = 100;
	rootParam[5] = 0x32;
	rootParam[6] = 0xDC;
	rootParam[7] = 0x180;
	rootParam[8] = 0;
	rootParam[9] = (u32)s_Debug_80331c90;
	rootParam[10] = 0;
	rootParam[11] = 0;
	rootParam[12] = 0;
	Add(0, 10, *(CDMParam*)rootParam);

	int y = 10;
	for (int i = 0; i < 0x17; i++) {
		memset(nodeParam, 0, sizeof(nodeParam));
		nodeParam[0] = 1;
		nodeParam[1] = 0;
		nodeParam[2] = 0;
		nodeParam[3] = 0;
		nodeParam[4] = 10;
		nodeParam[5] = y;
		nodeParam[6] = 0;
		nodeParam[7] = 0;
		nodeParam[8] = 0;
		nodeParam[9] = menuDefs[0];
		nodeParam[10] = 0;
		nodeParam[11] = 0;
		nodeParam[12] = 0;
		Add(10, 1, *(CDMParam*)nodeParam);

		memset(actionParam, 0, sizeof(actionParam));
		actionParam[0] = menuDefs[2];
		actionParam[1] = menuDefs[3];
		actionParam[2] = 0;
		actionParam[3] = 0;
		actionParam[4] = 0xB4;
		actionParam[5] = y;
		actionParam[6] = 0;
		actionParam[7] = 0;
		actionParam[8] = 0;
		actionParam[9] = 0;
		actionParam[10] = 0;
		actionParam[11] = 0;
		actionParam[12] = 0;
		Add(10, menuDefs[1], *(CDMParam*)actionParam);

		menuDefs += 4;
		y += 0x10;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::CDMParam::operator= (const CDbgMenuPcs::CDMParam&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8012b710
 * PAL Size: 432b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::Add(int parentID, int id, CDbgMenuPcs::CDMParam& param)
{
	int parent = searchID(parentID, *(CDM*)((char*)this + 8));
	int freeIdx = 0;
	int remaining = 0x80;
	int cur = (int)this;
	u32* menu;
	do {
		if ((s8)*(u8*)(cur + 0x90) >= 0) {
			menu = (u32*)((char*)this + freeIdx * 0x54 + 0x5C);
			goto found_slot;
		}
		cur += 0x54;
		freeIdx++;
		remaining--;
	} while (remaining != 0);
	menu = 0;

found_slot:
	memset(menu + 0xD, 0, 0x20);
	*(u8*)(menu + 0xD) = (*(u8*)(menu + 0xD) & 0x7F) | 0x80;

	u32* src = (u32*)&param;
	menu[0] = src[0];
	menu[1] = src[1];
	menu[2] = src[2];
	menu[3] = src[3];
	menu[4] = src[4];
	menu[5] = src[5];
	menu[6] = src[6];
	menu[7] = src[7];
	menu[8] = src[8];
	menu[9] = src[9];
	menu[10] = src[10];
	menu[11] = src[11];
	menu[12] = src[12];

	menu[0x13] = parent;
	menu[0x11] = (u32)menu;
	menu[0x12] = (u32)menu;
	menu[0x0E] = id;

	int child = *(int*)(parent + 0x50);
	if (child == 0) {
		*(u32**)(parent + 0x50) = menu;
		if ((menu[1] & 1) != 0) {
			*(u8*)(menu + 0xD) = (*(u8*)(menu + 0xD) & 0xBF) | 0x40;
			*(u32**)((char*)this + 0x2A64) = menu;
		}
		if ((menu[1] & 2) != 0) {
			*(u32**)((char*)this + 0x2A60) = menu;
		}
	} else {
		bool found = false;
		do {
			if (!found && ((*(u32*)(child + 4) & 1) != 0)) {
				found = true;
				*(u8*)(child + 0x34) = (*(u8*)(child + 0x34) & 0xBF) | 0x40;
				*(int*)((char*)this + 0x2A64) = child;
			}
			child = *(int*)(child + 0x48);
		} while (child != *(int*)(parent + 0x50));

		*(u32**)(*(int*)(child + 0x44) + 0x48) = menu;
		menu[0x11] = *(u32*)(child + 0x44);
		*(u32**)(child + 0x44) = menu;
		menu[0x12] = child;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::Delete(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CDbgMenuPcs::CDMParam::CDMParam()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CDbgMenuPcs::CDMParam::CDMParam(int, int, int, int, int, int, void*, void (*) (CDbgMenuPcs::CDM&, void*), void (*) (CDbgMenuPcs::CDM&, void*))
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::CDMParam::Clear()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CDbgMenuPcs::CDM::CDM()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::CDM::Clear()
{
	// TODO
}
