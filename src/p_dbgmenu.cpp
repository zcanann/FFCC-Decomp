#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/gxfunc.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/pad.h"
#include "ffcc/p_chara.h"
#include "ffcc/p_minigame.h"
#include "ffcc/p_map.h"
#include "ffcc/partMng.h"
#include "ffcc/p_tina.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/cflat_runtime2.h"
#include <dolphin/gx.h>
#include <string.h>

CDbgMenuPcs DbgMenuPcs;

struct DbgMenuDef {
    const char* text;
    u32 id;
    u32 actionType;
    u32 actionFlags;
};

inline CDbgMenuPcs::CDbgMenuPcs()
{
}

CProcessCallbackTable CDbgMenuPcs::m_table = {
    "CDbgMenuPcs",
    static_cast<CProcessCallback>(&CDbgMenuPcs::create),
    static_cast<CProcessCallback>(&CDbgMenuPcs::destroy),
    {
        {static_cast<CProcessCallback>(&CDbgMenuPcs::calc), 0x11, 0},
        {static_cast<CProcessCallback>(&CDbgMenuPcs::draw), 0x4A, 1},
    },
};

static DbgMenuDef tWork[] = {
    { "MENU", 100, 2, 1 },      { "SHOUKI", 101, 2, 1 },
    { "MARK", 102, 2, 1 },      { "BAR", 103, 2, 1 },
    { "SPEED", 104, 2, 1 },     { "MUTEKI", 105, 2, 1 },
    { "FOLLOW", 106, 2, 1 },    { "DISPPRINT", 107, 2, 1 },
    { "COMBO", 108, 2, 1 },     { "PAUSE", 109, 2, 1 },
    { "BATTLE", 110, 2, 1 },    { "ANALOG", 111, 2, 1 },
    { "COLCHECK", 112, 2, 1 },  { "A*", 113, 2, 1 },
    { "PARTICLE", 114, 2, 1 },  { "PRINTF", 115, 2, 1 },
    { "SOUND INFO", 116, 3, 1 }, { "SHADOW", 117, 2, 1 },
    { "PART HEAP", 118, 2, 1 },  { "CHARA INFO", 119, 3, 1 },
    { "ITEM WEAPON", 120, 2, 1 }, { "SMITH MASTER", 121, 2, 1 },
    { "CHARA", 122, 2, 1 },
};

inline CDbgMenuPcs::CDM* CDbgMenuPcs::searchFreeCDM()
{
	for (int i = 0; i < 0x80; i++) {
		if (m_menuPool[i].m_statusBits.m_used == 0) {
			return &m_menuPool[i];
		}
	}

	return 0;
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
	return reinterpret_cast<int>(&m_table + index);
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
 * PAL Address: 0x8012cd88
 * PAL Size: 1144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CDbgMenuPcs::calc()
{
	unsigned short padInput;
	unsigned int flags;
	unsigned int padOffset;
	int menuPtr;
	int cursorPtr;
	CFlatRuntime::CStack stackData[3];

	if (m_rootMenuNode.m_firstChild == 0) {
		return;
	}

	if (Pad.m_debugPadLock != 0) {
		padInput = 0;
	} else {
		padOffset = (Pad.m_debugPadPort == 4) ? 0 : 4U;
		padInput = Pad.GetPadInputs()[padOffset].buttonDown[0];
	}

	if ((padInput & 0x100) != 0) {
		switch (m_selectedMenu->m_id) {
		case 100:
			CFlatEventMask() = ~CFlatEventMask();
			break;
		case 0x65:
			stackData[0].m_word = 0;
			stackData[2].m_word = 0;
			flags = (unsigned int)__cntlzw((int)(s8)((s32)(((u32)CFlatGameFlags() << 0x18) & 0xC0000000) >> 0x1f));
			unsigned char gameFlags = ((int)(char)(flags >> 5) & 1U) << 7 | (CFlatGameFlags() & ~CFlatGameFlag_Shouki);
			CFlatGameFlags() = gameFlags;
			stackData[1].m_word = (s32)(((u32)gameFlags << 0x18) & 0xC0000000) >> 0x1f;
			gCFlatRuntime().SystemCall(0, 1, 9, 3, stackData, 0);
			break;
		case 0x66:
			flags = (unsigned int)__cntlzw((int)(s8)((s32)(((u32)(u8)CFlatGameFlags() << 0x1d) & 0xC0000000) >> 0x1f));
			CFlatGameFlags() = (unsigned char)((((int)(char)(flags >> 5) << 2) & CFlatGameFlag_Mark) |
			                                   (CFlatGameFlags() & ~CFlatGameFlag_Mark));
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
			PartPcs.m_usbStreamState.m_disableShokiDraw = (unsigned char)(flags >> 5);
			break;
		case 0x73:
			m_dbgFlags ^= 0x1000;
			break;
		case 0x74:
			Sound.CheckDriver(1);
			break;
		case 0x75:
			g_IsDbgDrawShadowPos = 1 - g_IsDbgDrawShadowPos;
			break;
		case 0x76:
			g_IsDrawHeapSize = 1 - g_IsDrawHeapSize;
			PartMng.pppDumpMngSt();
			break;
		case 0x77:
			CharaPcs.DumpLoad();
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

	if (Pad.m_debugPadLock != 0) {
		padInput = 0;
	} else {
		padOffset = (Pad.m_debugPadPort == 4) ? 0 : 4U;
		padInput = Pad.GetPadInputs()[padOffset].buttonDown[0];
	}
	if ((padInput & 4) != 0) {
		CDM* start = m_selectedMenu;
		m_selectedMenu->m_statusBits.m_selected = 0;
		do {
			m_selectedMenu = m_selectedMenu->m_next;
			if ((m_selectedMenu->m_flags & 1) != 0) {
				break;
			}
		} while (start != m_selectedMenu);
		m_selectedMenu->m_statusBits.m_selected = 1;
	}

	if (Pad.m_debugPadLock != 0) {
		padInput = 0;
	} else {
		padOffset = (Pad.m_debugPadPort == 4) ? 0 : 4U;
		padInput = Pad.GetPadInputs()[padOffset].buttonDown[0];
	}
	if ((padInput & 8) != 0) {
		CDM* start = m_selectedMenu;
		m_selectedMenu->m_statusBits.m_selected = 0;
		do {
			m_selectedMenu = m_selectedMenu->m_prev;
			if ((m_selectedMenu->m_flags & 1) != 0) {
				break;
			}
		} while (start != m_selectedMenu);
		m_selectedMenu->m_statusBits.m_selected = 1;
	}

	if (m_rootMenuNode.m_firstChild != 0) {
		calcMenu(m_rootMenuNode.m_firstChild);
	}

	if (Pad.m_debugPadLock != 0) {
		padInput = 0;
	} else {
		padOffset = (Pad.m_debugPadPort == 4) ? 0 : 4U;
		padInput = Pad.GetPadInputs()[padOffset].buttonDown[0];
	}
	if ((padInput & 0x200) != 0) {
		memset(m_menuPool, 0, sizeof(m_menuPool));
		m_rootMenuNode.m_firstChild = 0;
		m_defaultMenu = 0;
		m_selectedMenu = 0;
	}

	Pad.m_debugPadLock = 1;
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
			menu->m_state = CFlatEventMask() != 0;
			break;
		case 0x65:
			menu->m_state = (s8)((s32)(((u32)(u8)CFlatGameFlags() << 0x18) & 0xC0000000) >> 0x1F) != 0;
			break;
		case 0x66:
			menu->m_state = (s8)((s32)(((u32)(u8)CFlatGameFlags() << 0x1C) & 0xC0000000) >> 0x1F) != 0;
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
			menu->m_state = g_IsDbgDrawShadowPos != 0;
			break;
		case 0x76:
			menu->m_state = g_IsDrawHeapSize != 0;
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
 * Address:	TODO
 * Size:	TODO
 */

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
	CDM* head = menu;

	do {
		m_currentMenu = menu;
		GXSetViewport((f32)menu->m_drawX, (f32)menu->m_drawY, 640.0f, 448.0f, 0.0f, 1.0f);

		switch (menu->m_type) {
		case 0:
			drawWindow(menu->m_y, 0, 0, menu->m_unk18, menu->m_unk1C, menu->m_text);
			break;
		case 1:
			drawFont(menu->m_y, 0, 0, menu->m_text);
			break;
		case 2: {
			drawWindow((menu->m_state != 0) ? 2 : 0, 1, 1, 0x1E, 0xE, 0);

			const char* stateText = menu->m_state == 1 ? "ON" : (menu->m_state == 0 ? "OFF" : "?");
			drawFont(9, 0x10, 8, const_cast<char*>(stateText));
			break;
		}
		case 3:
			drawWindow((menu->m_state != 0) ? 2 : 0, 1, 1, 0x1E, 0xE, 0);
			break;
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
        switch (vtxFmt) {
        case 0:
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP,
                          GX_AF_SPOT);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
            _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
            break;

        case 1:
            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetVtxAttrFmt(GX_VTXFMT1, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
            GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
            _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
            _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
            break;
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
	static GXColor l[2] = {{0xFF, 0xFF, 0xFF, 0x80}, {0, 0, 0, 0x80}};
	static u32 c[4] = {0x0000FFC0, 0x4040FFC0, 0x4040FFC0, 0x8080FFC0};
	changeVtxFmt(1);
	float z = 0.0f;

	if ((flags & 1) == 0) {
		GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT1, 4);

		for (int vertexIndex = 0; vertexIndex < 4; vertexIndex++) {
			GXPosition3f32((float)(x + ((vertexIndex & 1) ? width : 0)),
			              (float)(y + ((vertexIndex & 2) ? height : 0)), z);
			GXColor1u32(c[vertexIndex]);
		}
	}

	int fillColorIndex = (flags >> 1) & 1;

	GXBegin(GX_LINESTRIP, GX_VTXFMT1, 3);
	int right = x + width;
	int bottom = y + height;
	GXPosition3f32((float)right, (float)y, z);
	GXColor1u32(*reinterpret_cast<u32*>(&l[fillColorIndex]));
	GXPosition3f32((float)x, (float)y, z);
	GXColor1u32(*reinterpret_cast<u32*>(&l[fillColorIndex]));
	GXPosition3f32((float)x, (float)bottom, z);
	GXColor1u32(*reinterpret_cast<u32*>(&l[fillColorIndex]));

	GXBegin(GX_LINESTRIP, GX_VTXFMT1, 3);
	GXPosition3f32((float)right, (float)y, z);
	GXColor1u32(*reinterpret_cast<u32*>(&l[1 - fillColorIndex]));
	GXPosition3f32((float)right, (float)bottom, z);
	GXColor1u32(*reinterpret_cast<u32*>(&l[1 - fillColorIndex]));
	GXPosition3f32((float)x, (float)bottom, z);
	GXColor1u32(*reinterpret_cast<u32*>(&l[1 - fillColorIndex]));

	if (m_currentMenu->m_statusBits.m_selected != 0) {
		u8 alpha = 0xC0;

		if ((System.GetCounter() >> 2 & 1) != 0) {
			alpha = 0xFF;
		}

		GXColor highlightColor = {0, 0, 0, 0x80};
		highlightColor.r = alpha;
		highlightColor.g = alpha;
		highlightColor.b = alpha;

		GXBegin(GX_LINESTRIP, GX_VTXFMT1, 5);
		int left = x - 1;
		int top = y - 1;
		int rightEdge = right + 1;
		int bottomEdge = bottom + 1;
		GXPosition3f32((float)rightEdge, (float)top, z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
		GXPosition3f32((float)left, (float)top, z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
		GXPosition3f32((float)left, (float)bottomEdge, z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
		GXPosition3f32((float)rightEdge, (float)bottomEdge, z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
		GXPosition3f32((float)rightEdge, (float)top, z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
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
	changeVtxFmt(0);

	GXColor mainColor = {0xFF, 0xFF, 0xFF, 0xFF};
	if ((flags & 2) != 0) {
		mainColor.b = 0;
		mainColor.g = 0;
		mainColor.r = 0;
	}

	if ((flags & 4) != 0) {
		drawFont((flags & ~4) | 2, x - 1, y, text);
		drawFont((flags & ~4) | 2, x, y + 1, text);
		drawFont((flags & ~4) | 2, x + 1, y, text);
		drawFont((flags & ~4) | 2, x, y - 1, text);
	}

	GXSetChanMatColor(GX_COLOR0A0, mainColor);

	int fontSize = (flags & 1) ? 8 : 10;
	if ((flags & 8) != 0) {
		int textLen = strlen(text);
		x -= (u32)(fontSize * textLen) >> 1;
		y -= fontSize / 2;
	}
	Graphic.DrawDebugStringDirect(x, y, text, fontSize);
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
    param = rootParam;
    param.m_text = "Debug";
    Add(0, 10, param);

    y = 10;
    for (int index = 0; index < static_cast<int>(sizeof(tWork) / sizeof(tWork[0])); index++) {
        DbgMenuDef* menuDefs = &tWork[index];
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
        param = nodeParam;
        param.m_text = const_cast<char*>(menuDefs->text);
        Add(10, 1, param);

        u32 actionType;
        u32 actionFlags = menuDefs->actionFlags;
        actionType = menuDefs->actionType;

        memset(&actionParam, 0, sizeof(actionParam));
        actionParam.m_type = (int)actionType;
        actionParam.m_flags = actionFlags;
        actionParam.m_width = 0xB4;
        actionParam.m_height = y;
        actionParam.m_unk18 = 0;
        actionParam.m_unk1C = 0;
        actionParam.m_unk20 = 0;
        actionParam.m_unk28 = 0;
        actionParam.m_unk2C = 0;

        param = actionParam;
        Add(10, (int)menuDefs->id, param);

        y += 0x10;
    }
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
	CDM* menu = searchFreeCDM();

	memset(&menu->m_status, 0, sizeof(CDM) - sizeof(CDMParam));
	menu->m_statusBits.m_used = 1;

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

	if (parentMenu->m_firstChild != 0) {
		CDM* child = parentMenu->m_firstChild;
		int found = 0;
		do {
			if (found == 0 && ((child->m_flags & 1) != 0)) {
				found = 1;
				child->m_statusBits.m_selected = 1;
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
			menu->m_statusBits.m_selected = 1;
			m_selectedMenu = menu;
		}
		if ((menu->m_flags & 2) != 0) {
			m_defaultMenu = menu;
		}
	}
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
inline CDbgMenuPcs::CDM::CDM()
{
	memset(this, 0, sizeof(CDMParam));
	memset(&m_status, 0, sizeof(*this) - sizeof(CDMParam));
}

#pragma pool_data off
