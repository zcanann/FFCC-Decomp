#include "ffcc/p_dbgmenu.h"
#include "ffcc/graphic.h"
#include "ffcc/system.h"
#include <dolphin/gx.h>
#include <string.h>

extern unsigned char CFlat[];
extern unsigned char DAT_8032e698;
extern unsigned char DAT_8032ecd8;

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
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::searchID(int, CDbgMenuPcs::CDM&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::Add()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::Add(int, int, CDbgMenuPcs::CDMParam&)
{
	// TODO
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
