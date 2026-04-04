#include "ffcc/p_dbgmenu.h"
#include "ffcc/gxfunc.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/pad.h"
#include "ffcc/p_chara.h"
#include "ffcc/p_minigame.h"
#include "ffcc/partMng.h"
#include "ffcc/p_tina.h"
#include "ffcc/system.h"
#include <dolphin/gx.h>
#include <string.h>

CDbgMenuPcs DbgMenuPcs;

extern unsigned char DAT_8032e698;
extern unsigned char DAT_8032ecd8;
extern u32 gDbgMenuWindowBorderColors[4];
extern u32 gDbgMenuWindowFillColors[2];

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
	return reinterpret_cast<int>(m_table__11CDbgMenuPcs + index * 0x15C);
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
			reinterpret_cast<unsigned char*>(&PartPcs)[0x34] = (unsigned char)(flags >> 5);
			break;
		case 0x73:
			m_dbgFlags ^= 0x1000;
			break;
		case 0x74:
			CheckDriver__6CSoundFi(&Sound, 1);
			break;
		case 0x75:
			DAT_8032ecd8 = 1 - DAT_8032ecd8;
			break;
		case 0x76:
			DAT_8032e698 = 1 - DAT_8032e698;
			pppDumpMngSt__8CPartMngFv(&PartMng);
			break;
		case 0x77:
			DumpLoad__9CCharaPcsFv(&CharaPcs);
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
void CDbgMenuPcs::drawWindow(int flags, int x, int y, int width, int height, char* text)
{
	if (m_currentVtxFmt != 1) {
		GXClearVtxDesc();
		GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
		GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
		GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
		GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
		GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
		_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
		_GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
		m_currentVtxFmt = 1;
	}

	if ((flags & 1) == 0) {
		const u32* borderColors = gDbgMenuWindowBorderColors;
		u32 vertexIndex = 0;

		GXBegin(GX_QUADS, GX_VTXFMT1, 4);

		for (int i = 0; i < 2; i++) {
			u32 row = vertexIndex >> 1;
			u32 nextVertexIndex = vertexIndex + 1;
			vertexIndex += 2;

			GXPosition3f32((float)x, (float)(y + (height & -(row & 1))), 0.0f);
			GXColor1u32(borderColors[0]);

			GXPosition3f32((float)(x + (width & -(nextVertexIndex & 1))),
			               (float)(y + (height & -((nextVertexIndex >> 1) & 1))),
			               0.0f);
			GXColor1u32(borderColors[1]);

			borderColors += 2;
		}
	}

	u32 fillColorIndex = (flags >> 1) & 1;

	GXBegin(GX_TRIANGLES, GX_VTXFMT1, 3);
	GXPosition3f32((float)(x + width), (float)y, 0.0f);
	GXColor1u32(gDbgMenuWindowFillColors[fillColorIndex]);
	GXPosition3f32((float)x, (float)y, 0.0f);
	GXColor1u32(gDbgMenuWindowFillColors[fillColorIndex]);
	GXPosition3f32((float)x, (float)(y + height), 0.0f);
	GXColor1u32(gDbgMenuWindowFillColors[fillColorIndex]);

	GXBegin(GX_TRIANGLES, GX_VTXFMT1, 3);
	GXPosition3f32((float)(x + width), (float)y, 0.0f);
	GXColor1u32(gDbgMenuWindowFillColors[1 - fillColorIndex]);
	GXPosition3f32((float)(x + width), (float)(y + height), 0.0f);
	GXColor1u32(gDbgMenuWindowFillColors[1 - fillColorIndex]);
	GXPosition3f32((float)x, (float)(y + height), 0.0f);
	GXColor1u32(gDbgMenuWindowFillColors[1 - fillColorIndex]);

	if ((s8)m_currentMenu->m_status < 0) {
		u8 alpha = 0xC0;

		if ((System.m_frameCounter >> 2 & 1) != 0) {
			alpha = 0xFF;
		}

		u32 highlightColor = (alpha << 24) | (alpha << 16) | (alpha << 8) | 0xFF;

		GXBegin(GX_QUADS, GX_VTXFMT1, 5);
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

	if (text != NULL) {
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
	if (m_currentVtxFmt != 0) {
		GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPEC);
		_GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
		_GXSetTevOp(GX_TEVSTAGE0, GX_REPLACE);
		m_currentVtxFmt = 0;
	}

	u32 mainColor = 0xFFFFFFFF;
	if ((flags & 2) != 0) {
		mainColor = 0x000000FF;
	}

	if ((flags & 4) != 0) {
		u32 smallFont = flags & 1;
		u32 centered = flags & 8;
		u32 shadowColor = 0x000000FF;
		int fontSize;
		short drawX = (short)(x - 1);
		short drawY = (short)y;

		changeVtxFmt(0);
		GXSetChanMatColor(GX_COLOR0A0, *reinterpret_cast<GXColor*>(&shadowColor));
		fontSize = 10;
		if (smallFont != 0) {
			fontSize = 8;
		}
		if (centered != 0) {
			int textLen = strlen(text);
			drawX = (short)(drawX - (short)((u32)(fontSize * textLen) >> 1));
			drawY = (short)(y - (short)(fontSize >> 1));
		}
		Graphic.DrawDebugStringDirect(drawX, drawY, text, (short)fontSize);

		drawY = (short)(y + 1);
		changeVtxFmt(0);
		GXSetChanMatColor(GX_COLOR0A0, *reinterpret_cast<GXColor*>(&shadowColor));
		fontSize = 10;
		if (smallFont != 0) {
			fontSize = 8;
		}
		drawX = (short)x;
		if (centered != 0) {
			int textLen = strlen(text);
			drawX = (short)(x - (short)((u32)(fontSize * textLen) >> 1));
			drawY = (short)(drawY - (short)(fontSize >> 1));
		}
		Graphic.DrawDebugStringDirect(drawX, drawY, text, (short)fontSize);

		drawX = (short)(x + 1);
		changeVtxFmt(0);
		GXSetChanMatColor(GX_COLOR0A0, *reinterpret_cast<GXColor*>(&shadowColor));
		fontSize = 10;
		if (smallFont != 0) {
			fontSize = 8;
		}
		drawY = (short)y;
		if (centered != 0) {
			int textLen = strlen(text);
			drawX = (short)(drawX - (short)((u32)(fontSize * textLen) >> 1));
			drawY = (short)(y - (short)(fontSize >> 1));
		}
		Graphic.DrawDebugStringDirect(drawX, drawY, text, (short)fontSize);

		drawY = (short)(y - 1);
		changeVtxFmt(0);
		GXSetChanMatColor(GX_COLOR0A0, *reinterpret_cast<GXColor*>(&shadowColor));
		fontSize = 10;
		if (smallFont != 0) {
			fontSize = 8;
		}
		drawX = (short)x;
		if (centered != 0) {
			int textLen = strlen(text);
			drawX = (short)(x - (short)((u32)(fontSize * textLen) >> 1));
			drawY = (short)(drawY - (short)(fontSize >> 1));
		}
		Graphic.DrawDebugStringDirect(drawX, drawY, text, (short)fontSize);
	}

	GXSetChanMatColor(GX_COLOR0A0, *reinterpret_cast<GXColor*>(&mainColor));

	int fontSize = 10;
	if ((flags & 1) != 0) {
		fontSize = 8;
	}
	if ((flags & 8) != 0) {
		int textLen = strlen(text);
		x = (short)(x - (short)((u32)(fontSize * textLen) >> 1));
		y = (short)(y - (short)(fontSize >> 1));
	}
	Graphic.DrawDebugStringDirect((short)x, (short)y, text, (short)fontSize);
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
			CDM* found = reinterpret_cast<CDM*>(searchID(id, *node->m_firstChild));
			if (found != 0) {
				return reinterpret_cast<int>(found);
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
    CDMParam param;
    CDMParam rootParam;
    CDMParam nodeParam;
    CDMParam actionParam;
    DbgMenuDef* menuDefs;
    int index;
    int y;

    if (m_rootMenuNode.m_firstChild != 0) {
        return;
    }

    memset(&param, 0, sizeof(param));
    memset(&rootParam, 0, sizeof(rootParam));
    rootParam.m_type = 0;
    rootParam.m_flags = 0;
    rootParam.m_width = 100;
    rootParam.m_height = 0x32;
    rootParam.m_unk18 = 0xDC;
    rootParam.m_unk1C = 0x180;
    rootParam.m_unk20 = 0;
    rootParam.m_unk28 = 0;
    rootParam.m_unk2C = 0;
    rootParam.m_unk30 = 0;
    rootParam.m_text = s_Debug_80331c90;

    param.m_type = rootParam.m_type;
    param.m_flags = rootParam.m_flags;
    param.m_x = rootParam.m_x;
    param.m_y = rootParam.m_y;
    param.m_width = rootParam.m_width;
    param.m_height = rootParam.m_height;
    param.m_unk18 = rootParam.m_unk18;
    param.m_unk1C = rootParam.m_unk1C;
    param.m_unk20 = rootParam.m_unk20;
    param.m_text = rootParam.m_text;
    param.m_unk28 = rootParam.m_unk28;
    param.m_unk2C = rootParam.m_unk2C;
    param.m_unk30 = rootParam.m_unk30;
    Add(0, 10, param);

    y = 10;
    menuDefs = PTR_DAT_80212524;
    index = 0;
    do {
        memset(&nodeParam, 0, sizeof(nodeParam));
        nodeParam.m_type = 1;
        nodeParam.m_flags = 0;
        nodeParam.m_width = 10;
        nodeParam.m_height = y;
        nodeParam.m_unk18 = 0;
        nodeParam.m_unk1C = 0;
        nodeParam.m_unk20 = 0;
        nodeParam.m_unk28 = 0;
        nodeParam.m_unk2C = 0;
        nodeParam.m_unk30 = 0;
        nodeParam.m_text = const_cast<char*>(menuDefs->text);

        param.m_type = nodeParam.m_type;
        param.m_flags = nodeParam.m_flags;
        param.m_x = nodeParam.m_x;
        param.m_y = nodeParam.m_y;
        param.m_width = nodeParam.m_width;
        param.m_height = nodeParam.m_height;
        param.m_unk18 = nodeParam.m_unk18;
        param.m_unk1C = nodeParam.m_unk1C;
        param.m_unk20 = nodeParam.m_unk20;
        param.m_text = nodeParam.m_text;
        param.m_unk28 = nodeParam.m_unk28;
        param.m_unk2C = nodeParam.m_unk2C;
        param.m_unk30 = nodeParam.m_unk30;
        Add(10, 1, param);

        memset(&actionParam, 0, sizeof(actionParam));
        actionParam.m_type = (int)menuDefs->actionType;
        actionParam.m_flags = menuDefs->actionFlags;
        actionParam.m_width = 0xB4;
        actionParam.m_height = y;
        actionParam.m_unk18 = 0;
        actionParam.m_unk1C = 0;
        actionParam.m_unk20 = 0;
        actionParam.m_unk28 = 0;
        actionParam.m_unk2C = 0;
        actionParam.m_unk30 = 0;

        param.m_type = actionParam.m_type;
        param.m_flags = actionParam.m_flags;
        param.m_x = actionParam.m_x;
        param.m_y = actionParam.m_y;
        param.m_width = actionParam.m_width;
        param.m_height = actionParam.m_height;
        param.m_unk18 = actionParam.m_unk18;
        param.m_unk1C = actionParam.m_unk1C;
        param.m_unk20 = actionParam.m_unk20;
        param.m_text = actionParam.m_text;
        param.m_unk28 = actionParam.m_unk28;
        param.m_unk2C = actionParam.m_unk2C;
        param.m_unk30 = actionParam.m_unk30;
        Add(10, (int)menuDefs->id, param);

        index++;
        menuDefs++;
        y += 0x10;
    } while (index < 0x17);
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
	CDM* parentMenu = reinterpret_cast<CDM*>(searchID(parentID, m_rootMenuNode));
	CDM* menu = 0;
	for (int i = 0; i < 0x80; i++) {
		if ((s8)m_menuPool[i].m_status >= 0) {
			menu = &m_menuPool[i];
			break;
		}
	}

	memset(&menu->m_status, 0, 0x20);
	menu->m_status = (menu->m_status & 0x7F) | 0x80;

	menu->m_type = param.m_type;
	menu->m_flags = param.m_flags;
	menu->m_x = param.m_x;
	menu->m_y = param.m_y;
	menu->m_width = param.m_width;
	menu->m_height = param.m_height;
	menu->m_unk18 = param.m_unk18;
	menu->m_unk1C = param.m_unk1C;
	menu->m_unk20 = param.m_unk20;
	menu->m_text = param.m_text;
	menu->m_unk28 = param.m_unk28;
	menu->m_unk2C = param.m_unk2C;
	menu->m_state = static_cast<s32>(param.m_unk30);

	menu->m_parent = parentMenu;
	menu->m_prev = menu;
	menu->m_next = menu;
	menu->m_id = id;

	CDM* child = parentMenu->m_firstChild;
	if (child != 0) {
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
	} else {
		parentMenu->m_firstChild = menu;
		if ((menu->m_flags & 1) != 0) {
			menu->m_status = (menu->m_status & 0xBF) | 0x40;
			m_selectedMenu = menu;
		}
		if ((menu->m_flags & 2) != 0) {
			m_defaultMenu = menu;
		}
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
 * PAL Address: 0x8012d3b4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CDbgMenuPcs::CDM::CDM()
{
	memset(this, 0, 0x34);
	memset(reinterpret_cast<unsigned char*>(this) + 0x34, 0, 0x20);
}
