#include "ffcc/p_dbgmenu.h"
#include "ffcc/gxfunc.h"
#include "ffcc/graphic.h"
#include "ffcc/pad.h"
#include "ffcc/p_minigame.h"
#include "ffcc/system.h"
#include <dolphin/gx.h>
#include <string.h>

CDbgMenuPcs DbgMenuPcs;
class CPartMng;
extern CPartMng PartMng;

extern unsigned char CFlat[];
extern unsigned char DAT_8032e698;
extern unsigned char DAT_8032ecd8;
extern unsigned char CharaPcs[];
extern unsigned char PartPcs[];
extern unsigned char Sound[];
extern u32 PTR_PTR_s_CDbgMenuPcs_802126c4;
extern u32 DAT_80212398;
extern u32 DAT_8021239c;
extern u32 PTR_create__11CDbgMenuPcsFv_802123a0;
extern u32 DAT_802123a4;
extern u32 DAT_802123a8;
extern u32 PTR_destroy__11CDbgMenuPcsFv_802123ac;
extern u32 DAT_802123b0;
extern u32 DAT_802123b4;
extern u32 PTR_calc__11CDbgMenuPcsFv_802123b8;
extern u32 DAT_802123bc;
extern u32 DAT_802123c0;
extern u32 PTR_draw__11CDbgMenuPcsFv_802123c4;
extern u32 DAT_802123cc;
extern u32 DAT_802123d0;
extern u32 DAT_802123d4;
extern u32 DAT_802123d8;
extern u32 DAT_802123dc;
extern u32 DAT_802123e0;
extern u32 DAT_802123e4;
extern u32 DAT_802123e8;
extern u32 DAT_802123ec;
extern u32 DAT_802123f8;
extern u32 DAT_802123fc;
extern u32 DAT_80212400;

extern "C" int __cntlzw(unsigned int);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void __ct__Q211CDbgMenuPcs3CDMFv(void*);
extern "C" void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void*, int, int, int, int, void*, void*);
extern "C" void CheckDriver__6CSoundFi(void*, int);
extern "C" void pppDumpMngSt__8CPartMngFv(void*);
extern "C" void DumpLoad__9CCharaPcsFv(void*);

struct DbgMenuDef {
    const char* text;
    u32 id;
    u32 actionType;
    u32 actionFlags;
};

char s_Debug_80331c90[] = "Debug";

DbgMenuDef PTR_DAT_80212524[] = {
    { "MENU", 100, 2, 1 }, { "SHOUKI", 101, 2, 1 },      { "MARK", 102, 2, 1 },       { "BAR", 103, 2, 1 },
    { "SPEED", 104, 2, 1 }, { "MUTEKI", 105, 2, 1 },      { "FOLLOW", 106, 2, 1 },     { "DISPPRINT", 107, 2, 1 },
    { "COMBO", 108, 2, 1 }, { "PAUSE", 109, 2, 1 },       { "BATTLE", 110, 2, 1 },     { "ANALOG", 111, 2, 1 },
    { "COLCHECK", 112, 2, 1 }, { "A*", 113, 2, 1 },       { "PARTICLE", 114, 2, 1 },   { "PRINTF", 115, 2, 1 },
    { "SOUND_INFO", 116, 3, 1 }, { "SHADOW", 117, 2, 1 }, { "PART_HEAP", 118, 2, 1 },  { "CHARA_INFO", 119, 3, 1 },
    { "ITEM_WEAPON", 120, 2, 1 }, { "SMITH_MASTER", 121, 2, 1 }, { "CHARA", 122, 2, 1 },
};

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
	*(u32*)((u8*)&MiniGamePcs + 0x6480) = (u32)&PTR_PTR_s_CDbgMenuPcs_802126c4;
	memset((u8*)&DbgMenuPcs, 0, 0x34);
	memset((u8*)&DbgMenuPcs + 0x34, 0, 0x20);
	__construct_array((u8*)&DbgMenuPcs + 0x54, __ct__Q211CDbgMenuPcs3CDMFv, 0, 0x54, 0x80);

	DAT_802123cc = DAT_80212398;
	DAT_802123d0 = DAT_8021239c;
	DAT_802123d4 = PTR_create__11CDbgMenuPcsFv_802123a0;
	DAT_802123d8 = DAT_802123a4;
	DAT_802123dc = DAT_802123a8;
	DAT_802123e0 = PTR_destroy__11CDbgMenuPcsFv_802123ac;
	DAT_802123e4 = DAT_802123b0;
	DAT_802123e8 = DAT_802123b4;
	DAT_802123ec = PTR_calc__11CDbgMenuPcsFv_802123b8;
	DAT_802123f8 = DAT_802123bc;
	DAT_802123fc = DAT_802123c0;
	DAT_80212400 = PTR_draw__11CDbgMenuPcsFv_802123c4;
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
 * PAL Address: 0x8012d260
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::Init()
{
	m_rootMenuNode.m_id = 0;
	m_rootMenuNode.m_unk18 = 0x280;
	m_rootMenuNode.m_unk1C = 0x1C0;
	m_dbgFlags = 0x8940;
}

/*
 * --INFO--
 * PAL Address: 0x8012d25c
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::Quit()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x8012d248
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CDbgMenuPcs::GetTable(unsigned long index)
{
	return index * 0x15C + -0x7FDEDC38;
}

/*
 * --INFO--
 * PAL Address: 0x8012d204
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::create()
{
	memset(m_menuPool, 0, sizeof(m_menuPool));
	m_defaultMenu = 0;
	m_selectedMenu = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8012d200
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::destroy()
{
	return;
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

	if (m_rootMenuNode.m_firstChild == 0) {
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
		switch (m_currentMenu->m_id) {
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
			m_dbgFlags ^= 1;
			break;
		case 0x68:
			m_dbgFlags ^= 2;
			break;
		case 0x69:
			m_dbgFlags ^= 4;
			break;
		case 0x6A:
			m_dbgFlags ^= 8;
			break;
		case 0x6B:
			m_dbgFlags ^= 0x10;
			break;
		case 0x6C:
			m_dbgFlags ^= 0x20;
			break;
		case 0x6D:
			m_dbgFlags ^= 0x40;
			break;
		case 0x6E:
			m_dbgFlags ^= 0x80;
			break;
		case 0x6F:
			m_dbgFlags ^= 0x100;
			break;
		case 0x70:
			m_dbgFlags ^= 0x200;
			break;
		case 0x71:
			m_dbgFlags ^= 0x400;
			break;
		case 0x72:
			m_dbgFlags ^= 0x800;
			flags = (unsigned int)__cntlzw(m_dbgFlags & 0x800);
			PartPcs[0x34] = (unsigned char)(flags >> 5);
			break;
		case 0x73:
			m_dbgFlags ^= 0x1000;
			break;
		case 0x74:
			CheckDriver__6CSoundFi(Sound, 1);
			break;
		case 0x75:
			DAT_8032ecd8 = 1 - DAT_8032ecd8;
			break;
		case 0x76:
			DAT_8032e698 = 1 - DAT_8032e698;
			pppDumpMngSt__8CPartMngFv(&PartMng);
			break;
		case 0x77:
			DumpLoad__9CCharaPcsFv(CharaPcs);
			break;
		case 0x78:
			m_dbgFlags ^= 0x2000;
			break;
		case 0x79:
			m_dbgFlags ^= 0x4000;
			break;
		case 0x7A:
			m_dbgFlags ^= 0x8000;
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
		menuPtr = (int)m_currentMenu;
		m_currentMenu->m_status &= 0xBF;
		do {
			m_currentMenu = m_currentMenu->m_next;
			cursorPtr = (int)m_currentMenu;
			if ((*(unsigned int*)(cursorPtr + 4) & 1) != 0) {
				break;
			}
		} while (menuPtr != cursorPtr);
		m_currentMenu->m_status = (m_currentMenu->m_status & 0xBF) | 0x40;
	}

	if (Pad._452_4_ == 0) {
		padInput = *(unsigned short*)((unsigned char*)&Pad._8_2_ +
		                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) *
		                               0x54));
	} else {
		padInput = 0;
	}
	if ((padInput & 8) != 0) {
		menuPtr = (int)m_currentMenu;
		m_currentMenu->m_status &= 0xBF;
		do {
			m_currentMenu = m_currentMenu->m_prev;
			cursorPtr = (int)m_currentMenu;
			if ((*(unsigned int*)(cursorPtr + 4) & 1) != 0) {
				break;
			}
		} while (menuPtr != cursorPtr);
		m_currentMenu->m_status = (m_currentMenu->m_status & 0xBF) | 0x40;
	}

	if (m_rootMenuNode.m_firstChild != 0) {
		calcMenu(m_rootMenuNode.m_firstChild);
	}

	if (Pad._452_4_ == 0) {
		padInput = *(unsigned short*)((unsigned char*)&Pad._8_2_ +
		                              ((~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f) & 4U) *
		                               0x54));
	} else {
		padInput = 0;
	}
	if ((padInput & 0x200) != 0) {
		memset(m_menuPool, 0, sizeof(m_menuPool));
		m_rootMenuNode.m_firstChild = 0;
		m_defaultMenu = 0;
		m_currentMenu = 0;
	}

	Pad._452_4_ = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8012cd10
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::draw()
{
	m_currentVtxFmt = -1;
	Graphic.InitDebugString();
	_GXSetBlendMode((_GXBlendMode)1, (_GXBlendFactor)4, (_GXBlendFactor)5, (_GXLogicOp)1);
	GXSetNumChans(1);
	if (m_rootMenuNode.m_firstChild != 0) {
		drawMenu(m_rootMenuNode.m_firstChild);
	}
	Graphic.SetViewport();
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
		m_currentMenu = menu;
		switch (menu->m_id) {
		case 100:
			menu->m_state = *(u32*)(CFlat + 0x12A4) != 0;
			break;
		case 0x65:
			menu->m_state = *(signed char*)(CFlat + 0x12E4) < 0;
			break;
		case 0x66:
			menu->m_state = ((*(u8*)(CFlat + 0x12E4) >> 3) & 1) != 0;
			break;
		case 0x67:
			menu->m_state = (m_dbgFlags >> 0) & 1;
			break;
		case 0x68:
			menu->m_state = (m_dbgFlags >> 1) & 1;
			break;
		case 0x69:
			menu->m_state = (m_dbgFlags >> 2) & 1;
			break;
		case 0x6A:
			menu->m_state = (m_dbgFlags >> 3) & 1;
			break;
		case 0x6B:
			menu->m_state = (m_dbgFlags >> 4) & 1;
			break;
		case 0x6C:
			menu->m_state = (m_dbgFlags >> 5) & 1;
			break;
		case 0x6D:
			menu->m_state = (m_dbgFlags >> 6) & 1;
			break;
		case 0x6E:
			menu->m_state = (m_dbgFlags >> 7) & 1;
			break;
		case 0x6F:
			menu->m_state = (m_dbgFlags >> 8) & 1;
			break;
		case 0x70:
			menu->m_state = (m_dbgFlags >> 9) & 1;
			break;
		case 0x71:
			menu->m_state = (m_dbgFlags >> 10) & 1;
			break;
		case 0x72:
			menu->m_state = (m_dbgFlags >> 11) & 1;
			break;
		case 0x73:
			menu->m_state = (m_dbgFlags >> 12) & 1;
			break;
		case 0x75:
			menu->m_state = DAT_8032ecd8 != 0;
			break;
		case 0x76:
			menu->m_state = DAT_8032e698 != 0;
			break;
		case 0x78:
			menu->m_state = (m_dbgFlags >> 13) & 1;
			break;
		case 0x79:
			menu->m_state = (m_dbgFlags >> 14) & 1;
			break;
		case 0x7A:
			menu->m_state = (m_dbgFlags >> 15) & 1;
			break;
		}

		menu->m_drawX = menu->m_parent->m_width + menu->m_width;
		menu->m_drawY = menu->m_parent->m_height + menu->m_height;

		if (menu->m_firstChild != 0) {
			calcMenu(menu->m_firstChild);
		}

		menu = menu->m_next;
	} while (menu != head);
}

/*
 * --INFO--
 * PAL Address: 0x8012c8d8
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::drawMenu(CDbgMenuPcs::CDM* menu)
{
	static char sStateOn[] = "ON";
	static char sStateOff[] = "OFF";
	static char sStateUnknown[] = "?";
	CDM* head = menu;
	do {
		m_currentMenu = menu;
		GXSetViewport((f32)menu->m_drawX, (f32)menu->m_drawY, 640.0f, 480.0f, 0.0f, 1.0f);

		s32 type = menu->m_type;
		if (type == 2) {
			s32 state = menu->m_state;
			drawWindow(((-state | state) >> 0x1F) & 2, 1, 1, 0x1E, 0xE, 0);
			char* stateText = sStateUnknown;
			if (state == 1) {
				stateText = sStateOn;
			} else if (state == 0) {
				stateText = sStateOff;
			}
			drawFont(9, 0x10, 8, stateText);
		} else if (type < 2) {
			if (type == 0) {
				drawWindow(menu->m_y, 0, 0, menu->m_unk18, menu->m_unk1C, menu->m_text);
			} else if (type == 1) {
				drawFont(menu->m_y, 0, 0, menu->m_text);
			}
		} else if (type < 4) {
			s32 state = menu->m_state;
			drawWindow(((-state | state) >> 0x1F) & 2, 1, 1, 0x1E, 0xE, 0);
		}

		menu = menu->m_next;
	} while (menu != head);

	menu = head;
	do {
		if (menu->m_firstChild != 0) {
			drawMenu(menu->m_firstChild);
		}
		menu = menu->m_next;
	} while (menu != head);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CDbgMenuPcs::changeVtxFmt(int vtxFmt)
{
    if (m_currentVtxFmt != vtxFmt) {
        if (vtxFmt == 1) {
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
        } else if (vtxFmt == 0) {
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            _GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
        }

        m_currentVtxFmt = vtxFmt;
    }
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
	if (m_currentVtxFmt != 1) {
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
		GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
		GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
		GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
		GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		m_currentVtxFmt = 1;
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
	char selectionFlag = (char)m_currentMenu->m_status;
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
	if (m_currentVtxFmt != 0) {
		GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
		GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
		m_currentVtxFmt = 0;
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
	CDM* node = &root;
	do {
		if (node->m_id == id) {
			return (int)node;
		}
		if (node->m_firstChild != 0) {
			const int found = searchID(id, *node->m_firstChild);
			if (found != 0) {
				return found;
			}
		}
		node = node->m_next;
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
	if (m_rootMenuNode.m_firstChild != 0) {
		return;
	}

	u32 rootParam[13];
	u32 nodeParam[13];
	u32 actionParam[13];
	u32* menuDefs = (u32*)PTR_DAT_80212524;

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
	int parent = searchID(parentID, m_rootMenuNode);
	int freeIdx = 0;
	int remaining = 0x80;
	int cur = (int)this;
	CDM* menu;
	do {
		if ((s8)*(u8*)(cur + 0x90) >= 0) {
			menu = &m_menuPool[freeIdx];
			goto found_slot;
		}
		cur += 0x54;
		freeIdx++;
		remaining--;
	} while (remaining != 0);
	menu = 0;

found_slot:
	memset(&menu->m_status, 0, 0x20);
	menu->m_status = (menu->m_status & 0x7F) | 0x80;

	memcpy(menu, &param, sizeof(CDMParam));

	CDM* parentMenu = (CDM*)parent;
	menu->m_parent = parentMenu;
	menu->m_prev = menu;
	menu->m_next = menu;
	menu->m_id = id;

	CDM* child = parentMenu->m_firstChild;
	if (child == 0) {
		parentMenu->m_firstChild = menu;
		if ((menu->m_flags & 1) != 0) {
			menu->m_status = (menu->m_status & 0xBF) | 0x40;
			m_selectedMenu = menu;
		}
		if ((menu->m_flags & 2) != 0) {
			m_defaultMenu = menu;
		}
	} else {
		bool found = false;
		do {
			if (!found && ((child->m_flags & 1) != 0)) {
				found = true;
				child->m_status = (child->m_status & 0xBF) | 0x40;
				m_selectedMenu = child;
			}
			child = child->m_next;
		} while (child != parentMenu->m_firstChild);

		child->m_prev->m_next = menu;
		menu->m_prev = child->m_prev;
		child->m_prev = menu;
		menu->m_next = child;
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
 * PAL Address: 0x8012d3b4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CDbgMenuPcs::CDM::CDM()
{
	memset(this, 0, sizeof(CDM));
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

