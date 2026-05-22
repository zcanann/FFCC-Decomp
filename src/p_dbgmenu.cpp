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
extern unsigned char g_map_draw_prof;

extern "C" void create__11CDbgMenuPcsFv(CDbgMenuPcs*);
extern "C" void destroy__11CDbgMenuPcsFv(CDbgMenuPcs*);
extern "C" void calc__11CDbgMenuPcsFv(CDbgMenuPcs*);
extern "C" void draw__11CDbgMenuPcsFv(CDbgMenuPcs*);
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

extern const char s_CDbgMenuPcs_801DD428[] = "CDbgMenuPcs";
extern const char s_DbgMenuMenu_80331C18[] = "MENU";
extern const char s_DbgMenuShouki_80331C20[] = "SHOUKI";
extern const char s_DbgMenuMark_80331C28[] = "MARK";
extern const char s_DbgMenuBar_80331C30[] = "BAR";
extern const char s_DbgMenuSpeed_80331C34[] = "SPEED";
extern const char s_DbgMenuMuteki_80331C3C[] = "MUTEKI";
extern const char s_DbgMenuFollow_80331C44[] = "FOLLOW";
extern const char s_DISPPRINT_801DD434[] = "DISPPRINT";
extern const char s_DbgMenuCombo_80331C4C[] = "COMBO";
extern const char s_DbgMenuPause_80331C54[] = "PAUSE";
extern const char s_DbgMenuBattle_80331C5C[] = "BATTLE";
extern const char s_DbgMenuAnalog_80331C64[] = "ANALOG";
extern const char s_COLCHECK_801DD440[] = "COLCHECK";
extern const char s_DbgMenuAsterisk_80331C6C[] = "A*";
extern const char s_PARTICLE_801DD44C[] = "PARTICLE";
extern const char s_DbgMenuPrintf_80331C70[] = "PRINTF";
extern const char s_SOUND_INFO_801DD458[] = "SOUND INFO";
extern const char s_DbgMenuShadow_80331C78[] = "SHADOW";
extern const char s_PART_HEAP_801DD464[] = "PART HEAP";
extern const char s_CHARA_INFO_801DD470[] = "CHARA INFO";
extern const char s_ITEM_WEAPON_801DD47C[] = "ITEM WEAPON";
extern const char s_SMITH_MASTER_801DD488[] = "SMITH MASTER";
extern const char s_DbgMenuChara_80331C80[] = "CHARA";
extern const u32 DAT_80331C88 = 0x00000080;
extern const u32 DAT_80331C8C = 0xFFFFFFFF;
extern const char s_Debug_80331c90[] = "Debug";
extern const float FLOAT_80331C98 = 0.0f;
extern const double DOUBLE_80331CA0 = 4503601774854144.0;
extern const float FLOAT_80331CA8 = 640.0f;
extern const float FLOAT_80331CAC = 448.0f;
extern const float FLOAT_80331CB0 = 1.0f;
extern const char s_DbgMenuOn_80331CB4[] = "ON";
extern const char s_DbgMenuOff_80331CB8[] = "OFF";
extern const char s_DbgMenuUnknown_80331CBC[] = "?";

u32 m_table_desc0__11CDbgMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(create__11CDbgMenuPcsFv)};
u32 m_table_desc1__11CDbgMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(destroy__11CDbgMenuPcsFv)};
u32 m_table_desc2__11CDbgMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(calc__11CDbgMenuPcsFv)};
u32 m_table_desc3__11CDbgMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(draw__11CDbgMenuPcsFv)};
u32 m_table__11CDbgMenuPcs[0x15C / sizeof(u32)] = {
    reinterpret_cast<u32>(const_cast<char*>(s_CDbgMenuPcs_801DD428)), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x11, 0, 0, 0, 0, 0x4A, 1
};

DbgMenuDef tWork[] = {
    { s_DbgMenuMenu_80331C18, 100, 2, 1 },   { s_DbgMenuShouki_80331C20, 101, 2, 1 },
    { s_DbgMenuMark_80331C28, 102, 2, 1 },   { s_DbgMenuBar_80331C30, 103, 2, 1 },
    { s_DbgMenuSpeed_80331C34, 104, 2, 1 },  { s_DbgMenuMuteki_80331C3C, 105, 2, 1 },
    { s_DbgMenuFollow_80331C44, 106, 2, 1 }, { s_DISPPRINT_801DD434, 107, 2, 1 },
    { s_DbgMenuCombo_80331C4C, 108, 2, 1 },  { s_DbgMenuPause_80331C54, 109, 2, 1 },
    { s_DbgMenuBattle_80331C5C, 110, 2, 1 }, { s_DbgMenuAnalog_80331C64, 111, 2, 1 },
    { s_COLCHECK_801DD440, 112, 2, 1 },      { s_DbgMenuAsterisk_80331C6C, 113, 2, 1 },
    { s_PARTICLE_801DD44C, 114, 2, 1 },      { s_DbgMenuPrintf_80331C70, 115, 2, 1 },
    { s_SOUND_INFO_801DD458, 116, 3, 1 },    { s_DbgMenuShadow_80331C78, 117, 2, 1 },
    { s_PART_HEAP_801DD464, 118, 2, 1 },     { s_CHARA_INFO_801DD470, 119, 3, 1 },
    { s_ITEM_WEAPON_801DD47C, 120, 2, 1 },   { s_SMITH_MASTER_801DD488, 121, 2, 1 },
    { s_DbgMenuChara_80331C80, 122, 2, 1 },
};
u32 gDbgMenuWindowBorderColors[4] = {0x0000FFC0, 0x4040FFC0, 0x4040FFC0, 0x8080FFC0};
GXColor gDbgMenuWindowFillColors[2] = {{0xFF, 0xFF, 0xFF, 0x80}, {0, 0, 0, 0x80}};

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
	return reinterpret_cast<int>(reinterpret_cast<char*>(m_table__11CDbgMenuPcs) + index * 0x15C);
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

inline CDbgMenuPcs::CDbgMenuPcs()
{
    m_table__11CDbgMenuPcs[1] = m_table_desc0__11CDbgMenuPcs[0];
    m_table__11CDbgMenuPcs[2] = m_table_desc0__11CDbgMenuPcs[1];
    m_table__11CDbgMenuPcs[3] = m_table_desc0__11CDbgMenuPcs[2];
    m_table__11CDbgMenuPcs[4] = m_table_desc1__11CDbgMenuPcs[0];
    m_table__11CDbgMenuPcs[5] = m_table_desc1__11CDbgMenuPcs[1];
    m_table__11CDbgMenuPcs[6] = m_table_desc1__11CDbgMenuPcs[2];
    m_table__11CDbgMenuPcs[7] = m_table_desc2__11CDbgMenuPcs[0];
    m_table__11CDbgMenuPcs[8] = m_table_desc2__11CDbgMenuPcs[1];
    m_table__11CDbgMenuPcs[9] = m_table_desc2__11CDbgMenuPcs[2];
    m_table__11CDbgMenuPcs[12] = m_table_desc3__11CDbgMenuPcs[0];
    m_table__11CDbgMenuPcs[13] = m_table_desc3__11CDbgMenuPcs[1];
    m_table__11CDbgMenuPcs[14] = m_table_desc3__11CDbgMenuPcs[2];
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
	unsigned int padOffset;
	int menuPtr;
	int cursorPtr;
	int stackData[3];

	if (m_rootMenuNode.m_firstChild == 0) {
		return;
	}

	if (Pad._452_4_ != 0) {
		padInput = 0;
	} else {
		padOffset = 4U;
		padOffset &= ~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f);
		padInput = Pad.GetPadInputs()[padOffset].buttonDown[0];
	}

	if ((padInput & 0x100) != 0) {
		switch (m_selectedMenu->m_id) {
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
			PartPcs.m_usbStreamData.m_disableShokiDraw = (unsigned char)(flags >> 5);
			break;
		case 0x73:
			m_dbgFlags ^= 0x1000;
			break;
		case 0x74:
			CheckDriver__6CSoundFi(&Sound, 1);
			break;
		case 0x75:
			g_map_draw_prof = 1 - g_map_draw_prof;
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

	if (Pad._452_4_ != 0) {
		padInput = 0;
	} else {
		padOffset = 4U;
		padOffset &= ~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f);
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
		} while (m_selectedMenu != start);
		m_selectedMenu->m_statusBits.m_selected = 1;
	}

	if (Pad._452_4_ != 0) {
		padInput = 0;
	} else {
		padOffset = 4U;
		padOffset &= ~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f);
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
		} while (m_selectedMenu != start);
		m_selectedMenu->m_statusBits.m_selected = 1;
	}

	if (m_rootMenuNode.m_firstChild != 0) {
		calcMenu(m_rootMenuNode.m_firstChild);
	}

	if (Pad._452_4_ != 0) {
		padInput = 0;
	} else {
		padOffset = 4U;
		padOffset &= ~((int)~(Pad._448_4_ - 4 | 4 - Pad._448_4_) >> 0x1f);
		padInput = Pad.GetPadInputs()[padOffset].buttonDown[0];
	}
	if ((padInput & 0x200) != 0) {
		memset(m_menuPool, 0, sizeof(m_menuPool));
		m_rootMenuNode.m_firstChild = 0;
		m_defaultMenu = 0;
		m_selectedMenu = 0;
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
			menu->m_state = (s8)((s32)(((u32)(u8)CFlat[0x12E4] << 0x18) & 0xC0000000) >> 0x1F) != 0;
			break;
		case 0x66:
			menu->m_state = (s8)((s32)(((u32)(u8)CFlat[0x12E4] << 0x1C) & 0xC0000000) >> 0x1F) != 0;
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
			menu->m_state = g_map_draw_prof != 0;
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
	CDM* current = menu;
	CDM* head = menu;

	do {
		m_currentMenu = current;
		GXSetViewport((f32)current->m_drawX, (f32)current->m_drawY, FLOAT_80331CA8, FLOAT_80331CAC, FLOAT_80331C98,
		              FLOAT_80331CB0);

		int type = current->m_type;
		if (type != 2) {
			if (type < 2) {
				if (type < 0) {
				} else if (type == 0) {
					drawWindow(current->m_y, 0, 0, current->m_unk18, current->m_unk1C, current->m_text);
				} else {
					drawFont(current->m_y, 0, 0, current->m_text);
				}
			} else if (type < 4) {
				drawWindow((current->m_state != 0) ? 2 : 0, 1, 1, 0x1E, 0xE, 0);
			}
		} else {
			drawWindow((current->m_state != 0) ? 2 : 0, 1, 1, 0x1E, 0xE, 0);

			const char* stateText;
			if (current->m_state == 1) {
				stateText = s_DbgMenuOn_80331CB4;
			} else {
				stateText = s_DbgMenuUnknown_80331CBC;
				if (current->m_state == 0) {
					stateText = s_DbgMenuOff_80331CB8;
				}
			}

			drawFont(9, 0x10, 8, const_cast<char*>(stateText));
		}

		current = current->m_next;
	} while (current != head);

	current = head;
	do {
		if (current->m_firstChild != 0) {
			drawMenu(current->m_firstChild);
		}
		current = current->m_next;
	} while (current != head);
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
	changeVtxFmt(1);
	float z = FLOAT_80331C98;

	if ((flags & 1) == 0) {
		GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT1, 4);

		const u32* borderColors = gDbgMenuWindowBorderColors;
		u32 vertexIndex = 0;
		int count = 2;

		while (count != 0) {
			u32 col = vertexIndex & 1;
			u32 row = vertexIndex >> 1;
			u32 nextVertexIndex = vertexIndex + 1;

			GXPosition3f32((float)(x + (width & -static_cast<int>(col))),
			               (float)(y + (height & -static_cast<int>(row & 1))),
			               z);
			GXColor1u32(borderColors[0]);

			vertexIndex = nextVertexIndex;
			GXPosition3f32((float)(x + (width & -(nextVertexIndex & 1))),
			               (float)(y + (height & -((nextVertexIndex >> 1) & 1))),
			               z);
			GXColor1u32(borderColors[1]);

			vertexIndex = nextVertexIndex + 1;
			borderColors += 2;
			count--;
		}
	}

	int fillColorIndex = (flags >> 1) & 1;

	GXBegin(GX_LINESTRIP, GX_VTXFMT1, 3);
	GXPosition3f32((float)(x + width), (float)y, z);
	GXColor1u32(*reinterpret_cast<u32*>(&gDbgMenuWindowFillColors[fillColorIndex]));
	GXPosition3f32((float)x, (float)y, z);
	GXColor1u32(*reinterpret_cast<u32*>(&gDbgMenuWindowFillColors[fillColorIndex]));
	GXPosition3f32((float)x, (float)(y + height), z);
	GXColor1u32(*reinterpret_cast<u32*>(&gDbgMenuWindowFillColors[fillColorIndex]));

	GXBegin(GX_LINESTRIP, GX_VTXFMT1, 3);
	GXPosition3f32((float)(x + width), (float)y, z);
	GXColor1u32(*reinterpret_cast<u32*>(&gDbgMenuWindowFillColors[1 - fillColorIndex]));
	GXPosition3f32((float)(x + width), (float)(y + height), z);
	GXColor1u32(*reinterpret_cast<u32*>(&gDbgMenuWindowFillColors[1 - fillColorIndex]));
	GXPosition3f32((float)x, (float)(y + height), z);
	GXColor1u32(*reinterpret_cast<u32*>(&gDbgMenuWindowFillColors[1 - fillColorIndex]));

	s8 selected = static_cast<s32>((static_cast<u32>(m_currentMenu->m_status) << 25) & 0xC0000000) >> 31;
	if (selected != 0) {
		u8 alpha = 0xC0;

		if ((System.m_frameCounter >> 2 & 1) != 0) {
			alpha = 0xFF;
		}

		GXColor highlightColor = {0, 0, 0, static_cast<u8>(DAT_80331C88)};
		highlightColor.r = alpha;
		highlightColor.g = alpha;
		highlightColor.b = alpha;

		GXBegin(GX_LINESTRIP, GX_VTXFMT1, 5);
		GXPosition3f32((float)(x + width + 1), (float)(y - 1), z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
		GXPosition3f32((float)(x - 1), (float)(y - 1), z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
		GXPosition3f32((float)(x - 1), (float)(y + height + 1), z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
		GXPosition3f32((float)(x + width + 1), (float)(y + height + 1), z);
		GXColor1u32(*reinterpret_cast<u32*>(&highlightColor));
		GXPosition3f32((float)(x + width + 1), (float)(y - 1), z);
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

	GXColor mainColor = *reinterpret_cast<const GXColor*>(&DAT_80331C8C);
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

	int fontSize = 10;
	if ((flags & 1) != 0) {
		fontSize = 8;
	}
	if ((flags & 8) != 0) {
		int textLen = strlen(text);
		x -= (u32)(fontSize * textLen) >> 1;
		y -= fontSize / 2;
	}
	Graphic.DrawDebugStringDirect(x, y, text, fontSize);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CDbgMenuPcs::CDM* CDbgMenuPcs::searchFreeCDM()
{
	for (int i = 0; i < 0x80; i++) {
		s8 used = static_cast<s32>((static_cast<u32>(m_menuPool[i].m_status) << 24) & 0xC0000000) >> 31;
		if (used == 0) {
			return &m_menuPool[i];
		}
	}

	return 0;
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
    int y;
    int index;

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
    param.m_text = const_cast<char*>(s_Debug_80331c90);
    Add(0, 10, param);

    y = 10;
    menuDefs = tWork;
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

        index++;
        y += 0x10;
        menuDefs++;
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
	CDM* menu = searchFreeCDM();

	memset(&menu->m_status, 0, 0x20);
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
CDbgMenuPcs::CDM::CDM()
{
	memset(this, 0, 0x34);
	memset(reinterpret_cast<unsigned char*>(this) + 0x34, 0, 0x20);
}
