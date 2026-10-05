#include "ffcc/cmake.h"
#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/pad.h"
#include "ffcc/p_chara.h"
#include "ffcc/memory.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/linkage.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

static int s_OldMenu;
extern "C" char s_menuSubfontPathFmt[];
#ifndef VERSION_GCCJGC
static const char s_cmake_cpp[] = "cmake.cpp";
#endif

struct CmakeInfo {
    char m_name[0x12];
    signed char m_gender;
    signed char m_tribe;
    signed char m_hair;
    signed char m_job;
};

enum CmakeTexture {
#ifdef VERSION_GCCJGC
    CMAKE_TEX_WORLD40 = 0x30,
    CMAKE_TEX_WORLD46 = 0x31,
    CMAKE_TEX_DIARY1 = 0x33,
    CMAKE_TEX_DIARY2 = 0x34,
    CMAKE_TEX_CRYSTAL = 0x37,
    CMAKE_TEX_WORLD27 = 0x38,
    CMAKE_TEX_WORLD28 = 0x39,
    CMAKE_TEX_WORLD29 = 0x3A,
    CMAKE_TEX_WORLD44 = 0x3B,
    CMAKE_TEX_WORLD45 = 0x3C,
    CMAKE_TEX_WORLD48 = 0x3D,
    CMAKE_TEX_WORLD49 = 0x3E,
    CMAKE_TEX_VILLAGE_CRYSTAL = 0x5F,
    CMAKE_TEX_VILLAGE_WORLD27 = 0x60,
    CMAKE_TEX_VILLAGE_WORLD28 = 0x61,
    CMAKE_TEX_VILLAGE_WORLD29 = 0x62,
    CMAKE_TEX_VILLAGE_WORLD44 = 0x63,
    CMAKE_TEX_VILLAGE_WORLD45 = 0x64,
    CMAKE_VILLAGE_TEXTURE_COUNT = 8,
#else
    CMAKE_TEX_WORLD40 = 0x31,
    CMAKE_TEX_WORLD46 = 0x32,
    CMAKE_TEX_DIARY1 = 0x35,
    CMAKE_TEX_DIARY2 = 0x36,
    CMAKE_TEX_CRYSTAL = 0x39,
    CMAKE_TEX_WORLD27 = 0x3A,
    CMAKE_TEX_WORLD28 = 0x3B,
    CMAKE_TEX_WORLD29 = 0x3C,
    CMAKE_TEX_WORLD44 = 0x3D,
    CMAKE_TEX_WORLD45 = 0x3E,
    CMAKE_TEX_WORLD48 = 0x3F,
    CMAKE_TEX_WORLD49 = 0x40,
    CMAKE_TEX_VILLAGE_CRYSTAL = 0x60,
    CMAKE_TEX_VILLAGE_WORLD27 = 0x61,
    CMAKE_TEX_VILLAGE_WORLD28 = 0x62,
    CMAKE_TEX_VILLAGE_WORLD29 = 0x63,
    CMAKE_TEX_VILLAGE_WORLD44 = 0x64,
    CMAKE_TEX_VILLAGE_WORLD45 = 0x65,
    CMAKE_VILLAGE_TEXTURE_COUNT = 9,
#endif
};

enum CmakeFontSlot {
    CMAKE_FONT_VALUE = 0,
    CMAKE_FONT_LABEL = 1,
    CMAKE_FONT_VILLAGE = 4,
};

struct CmakeMenuState {
    unsigned char m_pad00[0x0B];
    char m_initialized;
    char m_selectionInitialized;
    unsigned char m_pad0D[0x10 - 0x0D];
    short m_mode;
    unsigned char m_pad12[0x16 - 0x12];
    short m_step;
    short m_stepTimer;
    unsigned char m_pad1A[0x1E - 0x1A];
    short m_resultDir;
    short m_resultValue;
    short m_frame;
    unsigned char m_pad24[0x26 - 0x24];
    short m_select;
    short m_row;
    short m_table;
    short m_subSelect;
    short m_resultFlag;
    short m_fieldSelect;
};
STATIC_ASSERT(offsetof(CmakeMenuState, m_initialized) == 0x0B);
STATIC_ASSERT(offsetof(CmakeMenuState, m_selectionInitialized) == 0x0C);
STATIC_ASSERT(offsetof(CmakeMenuState, m_mode) == 0x10);
STATIC_ASSERT(offsetof(CmakeMenuState, m_step) == 0x16);
STATIC_ASSERT(offsetof(CmakeMenuState, m_stepTimer) == 0x18);
STATIC_ASSERT(offsetof(CmakeMenuState, m_resultDir) == 0x1E);
STATIC_ASSERT(offsetof(CmakeMenuState, m_resultValue) == 0x20);
STATIC_ASSERT(offsetof(CmakeMenuState, m_frame) == 0x22);
STATIC_ASSERT(offsetof(CmakeMenuState, m_select) == 0x26);
STATIC_ASSERT(offsetof(CmakeMenuState, m_row) == 0x28);
STATIC_ASSERT(offsetof(CmakeMenuState, m_table) == 0x2A);
STATIC_ASSERT(offsetof(CmakeMenuState, m_subSelect) == 0x2C);
STATIC_ASSERT(offsetof(CmakeMenuState, m_resultFlag) == 0x2E);
STATIC_ASSERT(offsetof(CmakeMenuState, m_fieldSelect) == 0x30);

static inline void*& CmakeVillageWork(CMenuPcs* menu)
{
    return menu->m_cmakeVillageWork;
}

static inline CmakeMenuState* CmakeState(CMenuPcs* menu)
{
    return menu->m_cmakeState;
}

static inline CmakeMenuState* CmakeVillageState(CMenuPcs* menu)
{
    return static_cast<CmakeMenuState*>(CmakeVillageWork(menu));
}

static inline short& CmakeSlot(CMenuPcs* menu)
{
    return menu->m_singleCmakeSlot;
}

static inline short& CmakeResult(CMenuPcs* menu)
{
    return menu->m_menuResultCode;
}

static inline MenuWindowInfo* CmakeWindowInfo(CMenuPcs* menu)
{
    return menu->m_menuWindowInfo;
}

static inline short& CmakeMcState(CMenuPcs* menu)
{
    return CmakeWindowInfo(menu)->state;
}

static inline short& CmakeStateSelectField(CmakeMenuState* state, int index)
{
    return (&state->m_select)[index];
}

static inline unsigned char* MenuPcsRaw()
{
    return reinterpret_cast<unsigned char*>(&MenuPcs);
}

static inline short& MenuS16(CMenuPcs* menu, int offset)
{
    return *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(menu) + offset);
}

static inline int& MenuS32(CMenuPcs* menu, int offset)
{
    return *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(menu) + offset);
}

static inline unsigned char& MenuU8(CMenuPcs* menu, int offset)
{
    return *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(menu) + offset);
}

static inline CCharaPcs::CHandle* GetCmakeCharaHandle(CMenuPcs* menu, int slot)
{
    int index = slot + 0x20;
    return menu->m_wm.m_handles[index];
}

static inline void ReleaseRefObject(void* object)
{
    CRef* ref = reinterpret_cast<CRef*>(object);
    if (ref->DecRef() == 0) {
        delete ref;
    }
}

static inline float CalcCmakeFadeAlpha(CMenuPcs* menu)
{
    CmakeMenuState* state = CmakeState(menu);
    int frame = static_cast<int>(state->m_frame) - 1;
    if (frame < 0) {
        frame = 0;
    }

    if (state->m_mode == 0) {
        return static_cast<float>(0.1 * static_cast<double>(frame));
    }
    if (state->m_mode == 1) {
        return 1.0f;
    }
    return static_cast<float>(1.0 - 0.1 * static_cast<double>(frame));
}

static inline void DrawCmakePreviewCharaAlpha(CMenuPcs* menu, float alpha)
{
    int modelBlock = MenuS32(menu, 0x814);
    if (*reinterpret_cast<int*>(modelBlock + (static_cast<int>(CmakeSlot(menu)) + 0x20) * 0x50) == 0) {
        return;
    }
    int handleIndex = static_cast<int>(CmakeSlot(menu)) + 0x20;

    *reinterpret_cast<short*>(modelBlock + 0x6E8) = 0xFF24;
    *reinterpret_cast<unsigned short*>(modelBlock + 0x6EA) = 4;
    menu->DrawInit();

    if (menu->m_wm.m_handles[handleIndex]->m_charaKind != 3) {
        menu->SetProjection(0x16);
        menu->SetLight(2);
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(menu->m_wm.m_handles[handleIndex]->m_model) + 0x9C) = alpha;
        menu->m_wm.m_handles[handleIndex]->Draw(5);
        menu->RestoreProjection();
    } else {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD46));
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        GXColor col;
        col.r = 0xFF;
        col.g = 0xFF;
        col.b = 0xFF;
        col.a = 0xFF;
        GXSetChanMatColor(GX_COLOR0A0, col);
        MenuPcs.DrawRect(
            0,
            33.0f, 132.0f, 128.0f, 104.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    menu->DrawInit();
}

static inline void DrawCmakePreviewChara(CMenuPcs* menu)
{
    DrawCmakePreviewCharaAlpha(menu, 1.0f);
}

static inline void DrawNamePreviewChara(CMenuPcs* menu, float modelAlpha, int gxAlpha)
{
    int modelBlock = MenuS32(menu, 0x814);
    if (*reinterpret_cast<int*>(modelBlock + (static_cast<int>(CmakeSlot(menu)) + 0x20) * 0x50) == 0) {
        return;
    }
    int handleIndex = static_cast<int>(CmakeSlot(menu)) + 0x20;

    *reinterpret_cast<short*>(modelBlock + 0x6E8) = 0xFF24;
    *reinterpret_cast<unsigned short*>(modelBlock + 0x6EA) = 4;
    menu->DrawInit();

    if (menu->m_wm.m_handles[handleIndex]->m_charaKind != 3) {
        menu->SetProjection(0x16);
        menu->SetLight(2);
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(menu->m_wm.m_handles[handleIndex]->m_model) + 0x9C) = modelAlpha;
        menu->m_wm.m_handles[handleIndex]->Draw(5);
        menu->RestoreProjection();
    } else {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD46));
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        GXColor col;
        col.r = 0xFF;
        col.g = 0xFF;
        col.b = 0xFF;
        col.a = static_cast<unsigned char>(gxAlpha);
        GXSetChanMatColor(GX_COLOR0A0, col);
        MenuPcs.DrawRect(
            0,
            33.0f, 132.0f, 128.0f, 104.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    menu->DrawInit();
}

static inline void SetCmakeBlendMatColor(float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, col);
}

static inline void SetCmakeFontColor(CFont* font, float alpha)
{
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).color);
}

static inline void DrawCmakeSelectionBackdrop(CMenuPcs* menu)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, col);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD49));
    for (int x = 0x20; x < 0x260; x += 0x20) {
        int span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }

        MenuPcs.DrawRect(
            0,
            (float)x, 24.0f, (float)span, 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    menu->DrawInit();
}

static inline void DrawCmakePopupPanel(CMenuPcs* menu, float alpha, float x, float y, float w, float h, float scaleX, float scaleY)
{
    int a = static_cast<int>(255.0f * alpha);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(a);
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(menu) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, x, y, w, h,
        0.0f, 0.0f, scaleX, scaleY, 0.0f);
}

static inline void DrawCmakeMcOverlay(CMenuPcs* menu, int messageId)
{
    int mcState = CmakeMcState(menu);

    menu->DrawInit();
    if (mcState == 3) {
        return;
    }

    menu->DrawMcWin(-1, 0);
    if (mcState == 1) {
        menu->DrawMcWinMess(messageId, 0);
    }
}

static inline unsigned char* GetCmakeRosterEntry(CMenuPcs* menu, int slot)
{
    return reinterpret_cast<unsigned char*>(MenuS32(menu, 0x814) + 0x7930 + slot * 0xC30);
}

static inline CFont* GetCmakeKeyboardFont(CMenuPcs* menu)
{
    if (CmakeResult(menu) != 0) {
        return menu->m_fonts[CMAKE_FONT_VILLAGE];
    }
    return menu->m_fonts[CMAKE_FONT_LABEL];
}

#ifdef VERSION_GCCJGC
#include "ffcc/cmake_jp.inc"
static const char s_cmakeSubfontPath[] = "dvd/menu/subfont.fnt";
static const char s_cmake_cpp[] = "cmake.cpp";
#else
extern "C" const char s_ABCDEFGHIJKL_801E2F30[];
extern "C" const char s_MNOPQRSTUVWX_801E2F40[];
extern "C" const char lbl_801E2F50[];
extern "C" const char lbl_801E2F60[];
extern "C" const char lbl_801E2F70[];
extern "C" const char s_abcdefghijkl_801E2F80[];
extern "C" const char s_mnopqrstuvwx_801E2F90[];
extern "C" const char lbl_801E2FA0[];
extern "C" const char lbl_801E2FB0[];
extern "C" const char lbl_801E2FC0[];
extern "C" const char s_str_0123456789_801E2FD0[];
extern "C" const char lbl_801E2FE0[];
extern "C" const char lbl_801E2FF0[];
extern "C" const char lbl_801E3000[];
extern "C" const char lbl_801E3010[];

static const char* s_NameEntryStr[] = {
    s_ABCDEFGHIJKL_801E2F30,
    s_MNOPQRSTUVWX_801E2F40,
    lbl_801E2F50,
    lbl_801E2F60,
    lbl_801E2F70,
    s_abcdefghijkl_801E2F80,
    s_mnopqrstuvwx_801E2F90,
    lbl_801E2FA0,
    lbl_801E2FB0,
    lbl_801E2FC0,
    s_str_0123456789_801E2FD0,
    lbl_801E2FE0,
    lbl_801E2FF0,
    lbl_801E3000,
    lbl_801E3010
};

#endif

enum { CMAKE_NAME_PAGE_COUNT = sizeof(s_NameEntryStr) / sizeof(s_NameEntryStr[0]) / 5 };

static const char s_world2[] = "world2";
static const char s_crystal[] = "crystal";
static const char s_world27[] = "world27";
static const char s_world28[] = "world28";
static const char s_world29[] = "world29";
static const char s_world44[] = "world44";
static const char s_world45[] = "world45";
static const char s_world48[] = "world48";
static const char s_world49[] = "world49";
static const char s_world51[] = "world51";

char* PTR_s_world2[] = {
    (char*)s_world2,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
CMenuPcs::CTmp s_cmakeWorldTextureTable[] = {
    {8, (char*)s_crystal},
    {8, (char*)s_world27},
    {8, (char*)s_world28},
    {8, (char*)s_world29},
    {8, (char*)s_world44},
    {8, (char*)s_world45},
    {8, (char*)s_world48},
    {8, (char*)s_world49},
#ifndef VERSION_GCCJGC
    {8, (char*)s_world51},
#endif
};

static CmakeInfo s_CmakeInfo;
static char s_CmakeVillageName[0x11];

static inline char* GetCmakeNameBuffer()
{
    return s_CmakeInfo.m_name;
}

static inline void LoadCmakeVillageName()
{
    strcpy(s_CmakeInfo.m_name, Game.m_gameWork.m_townName);
}

static inline void StoreCmakeVillageName()
{
    memset(Game.m_gameWork.m_townName, 0, 17);
    strcpy(Game.m_gameWork.m_townName, s_CmakeInfo.m_name);
}

static inline int IsDuplicateCmakeName(CMenuPcs* menu, const char* name)
{
    const char* nm = name;
    int slot = 0;
    int found = false;
    for (; slot < 8; ++slot) {
        if (slot == CmakeSlot(menu)) {
            continue;
        }
        if (Game.m_caravanWorkArr[slot].m_shopState == 0) {
            continue;
        }
#ifndef VERSION_GCCJGC
        if (Game.m_caravanWorkArr[slot].m_caravanLocalFlags == 1) {
            continue;
        }
#endif
        if (strcmp(nm, reinterpret_cast<char*>(Game.m_caravanWorkArr[slot].m_name)) == 0) {
            found = true;
            break;
        }
    }

    if (!found) {
        for (int i = 0; i < 0x100; ++i) {
            if (strcmp(Game.m_cFlatDataArr[1].TableStrings(2)[i], name) == 0) {
                found = true;
                break;
            }
        }
    }

    return found;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: 0x8016F244
 * JP Size: 320b
 */
#ifdef VERSION_GCCJGC
static void GetChara(char* text, int index, char* dst)
{
    dst[0] = '\0';
    int length = strlen(text);
    if (length != 0) {
        int position;
        int state;
        int character;
        character = 0;
        state = 0;
        position = 0;
        for (; length > 0; --length, ++position) {
            if ((state == 0 || state == 2) &&
                ((static_cast<unsigned char>(text[position]) >= 0x81 && static_cast<unsigned char>(text[position]) <= 0x9F) || (static_cast<unsigned char>(text[position]) >= 0xE0 && static_cast<unsigned char>(text[position]) <= 0xFC))) {
                state = 1;
            } else if (state == 1 && static_cast<unsigned char>(text[position]) != 0x7F && static_cast<unsigned char>(text[position]) >= 0x40 && static_cast<unsigned char>(text[position]) <= 0xFC) {
                state = 2;
            } else {
                state = 0;
            }
            if (character == index) {
                if (state == 0) {
                    dst[0] = text[position];
                    dst[1] = '\0';
                } else {
                    dst[0] = text[position];
                    dst[1] = text[position + 1];
                    dst[2] = '\0';
                }
                break;
            }
            if (state != 1) {
                ++character;
            }
        }
    }
}
#else
inline void GetChara(char* dst, int index, char* table)
{
    if (dst == nullptr) {
        return;
    }

    dst[0] = '\0';
    if (table == nullptr || index < 0) {
        return;
    }

    const int stride = 0x20;
    memcpy(dst, table + index * stride, stride);
    dst[stride - 1] = '\0';
}

#endif

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifdef VERSION_GCCJGC
static inline int GetCharaType(char* text, int index)
{
    int length = strlen(text);
    if (length == 0) {
        return -1;
    }
    int character = 0;
    int state = 0;
    for (int position = 0; length > 0; --length, ++position) {
        if ((state == 0 || state == 2) &&
            ((static_cast<unsigned char>(text[position]) >= 0x81 && static_cast<unsigned char>(text[position]) <= 0x9F) || (static_cast<unsigned char>(text[position]) >= 0xE0 && static_cast<unsigned char>(text[position]) <= 0xFC))) {
            state = 1;
        } else if (state == 1 && static_cast<unsigned char>(text[position]) != 0x7F && static_cast<unsigned char>(text[position]) >= 0x40 && static_cast<unsigned char>(text[position]) <= 0xFC) {
            state = 2;
        } else {
            state = 0;
        }
        if (character == index) {
            return state != 0;
        }
        if (state != 1) {
            ++character;
        }
    }
    return -1;
}
#else
inline void GetCharaType(char* dst, int type)
{
    if (dst == nullptr) {
        return;
    }

    dst[0] = static_cast<char>(type);
    dst[1] = '\0';
}

#endif

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifdef VERSION_GCCJGC
static inline int GetCharaCnt(char* text)
{
    int length = strlen(text);
    if (length == 0) {
        return 0;
    }
    int character = 0;
    int state = 0;
    for (int position = 0; length > 0; --length, ++position) {
        if ((state == 0 || state == 2) &&
            ((static_cast<unsigned char>(text[position]) >= 0x81 && static_cast<unsigned char>(text[position]) <= 0x9F) || (static_cast<unsigned char>(text[position]) >= 0xE0 && static_cast<unsigned char>(text[position]) <= 0xFC))) {
            state = 1;
        } else if (state == 1 && static_cast<unsigned char>(text[position]) != 0x7F && static_cast<unsigned char>(text[position]) >= 0x40 && static_cast<unsigned char>(text[position]) <= 0xFC) {
            state = 2;
        } else {
            state = 0;
        }
        if (state != 1) {
            ++character;
        }
    }
    return character;
}
#else
inline void GetCharaCnt(char* dst)
{
    if (dst != nullptr) {
        dst[0] = '\0';
    }
}

#endif

/*
 * --INFO--
 * PAL Address: 0x80173ba4
 * PAL Size: 2984b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSingCMake()
{
    short down;
    short repeat;
    int result;

    if (CmakeState(this)->m_initialized == 0) {
        InitFrame0Info();
        memset(&s_CmakeInfo, 0, sizeof(s_CmakeInfo));
        CmakeState(this)->m_initialized = 1;
        CmakeState(this)->m_selectionInitialized = 0;
        s_OldMenu = -1;
        CmakeMcState(this) = 3;
    }

    switch (CmakeState(this)->m_step) {
    case 0:
        if (CmakeState(this)->m_mode == 0) {
            CalcWMFrame0(CmakeState(this)->m_frame - 10);
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                CmakeState(this)->m_select = 0;
                CmakeState(this)->m_row = 0;
                CmakeState(this)->m_table = 0;
                CmakeState(this)->m_subSelect = 0;
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        } else if (CmakeState(this)->m_mode == 1) {
            result = 0;
        } else {
            CalcWMFrame0(-CmakeState(this)->m_frame);
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    case 1:
        if (CmakeState(this)->m_mode == 0) {
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        } else if (CmakeState(this)->m_mode == 1) {
            result = CmakeNameCtrl();
        } else {
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                if (CmakeState(this)->m_resultDir < 0) {
                    ChgModel(static_cast<int>(CmakeSlot(this)), -1, -1, -1);
                }
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    case 2: {
        if (CmakeState(this)->m_mode == 0) {
            if (CmakeState(this)->m_selectionInitialized == 0) {
                CmakeState(this)->m_select = 0;
                CmakeState(this)->m_selectionInitialized = 1;
            }
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        } else if (CmakeState(this)->m_mode == 1) {
            down = Pad.GetButtonDown(0);
            repeat = Pad.GetButtonRepeat(0);

            int done;
            if (repeat == 0) {
                done = 0;
            } else {
                if ((repeat & 0xC) != 0) {
                    CmakeState(this)->m_select ^= 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
                if ((repeat & 0xC) == 0) {
                    if ((down & 0x100) != 0) {
                        s_CmakeInfo.m_gender = static_cast<signed char>(CmakeState(this)->m_select);
                        CmakeState(this)->m_resultDir = 1;
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        done = 1;
                        goto case2_out;
                    }
                    if ((down & 0x200) != 0) {
                        CmakeState(this)->m_resultDir = -1;
                        Sound.PlaySe(3, 0x40, 0x7F, 0);
                        done = 1;
                        goto case2_out;
                    }
                }
                done = 0;
            }
        case2_out:
            result = done;
        } else {
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    }
    case 3:
        if (CmakeState(this)->m_mode == 0) {
            if (CmakeState(this)->m_selectionInitialized == 0) {
                CmakeState(this)->m_select = 0;
                CmakeState(this)->m_row = 0;
                CmakeState(this)->m_fieldSelect = 0;
                CmakeState(this)->m_selectionInitialized = 1;
            }
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        } else if (CmakeState(this)->m_mode == 1) {
            result = CmakeTribeCtrl();
        } else {
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    case 4:
        if (CmakeState(this)->m_mode == 0) {
            if (CmakeState(this)->m_selectionInitialized == 0) {
                CmakeState(this)->m_select = 0;
                CmakeState(this)->m_selectionInitialized = 1;
            }
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        } else if (CmakeState(this)->m_mode == 1) {
            result = CmakeJobCtrl();
        } else {
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    case 5: {
        if (CmakeState(this)->m_mode == 0) {
            if (CmakeState(this)->m_selectionInitialized == 0) {
                CmakeState(this)->m_select = 0;
                CmakeState(this)->m_selectionInitialized = 1;
            }
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        } else if (CmakeState(this)->m_mode == 1) {
            down = Pad.GetButtonDown(0);
            repeat = Pad.GetButtonRepeat(0);

            int done;
            if (repeat == 0) {
                done = 0;
            } else {
                if ((repeat & 3) != 0) {
                    CmakeState(this)->m_select ^= 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
                if ((repeat & 3) == 0) {
                    if ((down & 0x100) != 0) {
                        if (CmakeState(this)->m_select == 0) {
                            CmakeState(this)->m_resultDir = 1;
                            int chgWork = CmakeSlot(this) * 0x14;
                            chgWork += MenuS32(this, 0x844);
                            *reinterpret_cast<int*>(chgWork + 4) = 3;

                            CCaravanWork* caravanWork;
                            int slot = static_cast<int>(CmakeSlot(this));
                            int modelNo = GetModelNo(static_cast<int>(s_CmakeInfo.m_tribe), static_cast<int>(s_CmakeInfo.m_hair),
                                static_cast<int>(s_CmakeInfo.m_gender));
                            int animWork = slot * 0x34;
                            animWork += MenuS32(this, 0x824);
                            *reinterpret_cast<int*>(animWork + 8) = modelNo;

                            caravanWork = &Game.m_caravanWorkArr[slot];
                            *reinterpret_cast<unsigned char*>(MenuS32(this, 0x828) + 10) = 1;
                            caravanWork->LoadInit();
                            caravanWork->m_shopState = 1;
                            caravanWork->unk_0x3a8 = 0x101;
                            caravanWork->m_jobType = static_cast<int>(s_CmakeInfo.m_job);
                            memset(caravanWork->m_name, 0, 0x11);
                            strcpy(reinterpret_cast<char*>(caravanWork->m_name), s_CmakeInfo.m_name);
                            caravanWork->m_tribeId = static_cast<unsigned short>(s_CmakeInfo.m_tribe);
                            caravanWork->m_appearanceVariant = static_cast<unsigned short>(s_CmakeInfo.m_hair);
                            caravanWork->m_genderFlag = static_cast<unsigned short>(s_CmakeInfo.m_gender);
                            caravanWork->m_id = static_cast<unsigned short>(modelNo);
                            int baseDataIndex =
                                static_cast<int>(caravanWork->m_genderFlag) +
                                static_cast<int>(caravanWork->m_tribeId) * 2;
                            caravanWork->Init(
                                baseDataIndex,
                                reinterpret_cast<CRomWork*>(Game.unkCFlatData0[0] + baseDataIndex * 0x1D0),
                                static_cast<int>(caravanWork->m_appearanceVariant));
                            caravanWork->LoadFinished();
                            CallWorldParam(0, slot, 0);
                            {
                                short animWait = static_cast<short>(static_cast<int>(GetMaxAnimWait()));
                                CmakeState(this)->m_stepTimer = animWait;
                            }
                        } else {
                            CmakeState(this)->m_resultDir = -1;
                        }
                        Sound.PlaySe(0x33, 0x40, 0x7F, 0);
                        done = 1;
                        goto case5_out;
                    }
                    if ((down & 0x200) != 0) {
                        CmakeState(this)->m_resultDir = -1;
                        Sound.PlaySe(3, 0x40, 0x7F, 0);
                        done = 1;
                        goto case5_out;
                    }
                }
                done = 0;
            }
        case5_out:
            result = done;
        } else {
            int done;
            if (static_cast<int>(CmakeState(this)->m_stepTimer) != 0) {
                CmakeState(this)->m_stepTimer =
                    static_cast<short>(CmakeState(this)->m_stepTimer - 1);
                done = 0;
            } else {
                if (CmakeState(this)->m_frame >= 10) {
                    done = 1;
                } else {
                    CmakeState(this)->m_frame++;
                    done = 0;
                }
            }
            result = done;
        }
        break;
    }
    case 6: {
        if (CmakeState(this)->m_mode == 0) {
            if (CmakeState(this)->m_selectionInitialized == 0) {
                CmakeState(this)->m_select = 0;
                CmakeState(this)->m_selectionInitialized = 1;
            }
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        } else if (CmakeState(this)->m_mode == 1) {
            down = Pad.GetButtonDown(0);
            repeat = Pad.GetButtonRepeat(0);

            int done;
            if (repeat == 0) {
                done = 0;
            } else {
                if ((repeat & 0x8) != 0) {
                    if (static_cast<int>(CmakeState(this)->m_select) != 0) {
                        CmakeState(this)->m_select =
                            static_cast<short>(CmakeState(this)->m_select - 1);
                    } else {
                        CmakeState(this)->m_select = 3;
                    }
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else if ((repeat & 0x4) != 0) {
                    if (CmakeState(this)->m_select < 3) {
                        CmakeState(this)->m_select =
                            static_cast<short>(CmakeState(this)->m_select + 1);
                    } else {
                        CmakeState(this)->m_select = 0;
                    }
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }

                if ((repeat & 0xC) == 0) {
                    if ((down & 0x100) != 0) {
                        if (CmakeState(this)->m_select < 3) {
                            ChgModel(static_cast<int>(CmakeSlot(this)), -1, -1, -1);
                        }
                        CmakeState(this)->m_resultDir = 1;
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        done = 1;
                        goto case6_out;
                    }
                    if ((down & 0x200) != 0) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    }
                }
                done = 0;
            }
        case6_out:
            result = done;
        } else {
            int done;
            if (CmakeState(this)->m_frame >= 10) {
                done = 1;
            } else {
                CmakeState(this)->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    }
    default:
        break;
    }

    CalcSingleCMakeChara();
    CmakeState(this)->m_resultFlag = static_cast<short>(result);
}

/*
 * --INFO--
 * PAL Address: 0x80173794
 * PAL Size: 1040b
 * EN Address: 0x80172710
 * EN Size: 1040b
 * JP Address: 0x8016E294
 * JP Size: 1032b
 */
void CMenuPcs::DrawSingCMake()
{

    switch (CmakeState(this)->m_step) {
    case 0: {
        float alpha = CalcCmakeFadeAlpha(this);
        DrawWMFrame0(1, alpha);

        SetCmakeBlendMatColor(alpha);

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48));
        MenuPcs.DrawRect(
            0,
            0.0f, 24.0f, 32.0f, 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        MenuPcs.DrawRect(
            8,
            608.0f, 24.0f, 32.0f, 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD49));
        {
            int span;
            for (int x = 0x20; x < 0x260; x += span) {
                span = 0x20;
                if ((0x260 - x) < span) {
                    span = 0x260 - x;
                }

                MenuPcs.DrawRect(
                    0,
                    static_cast<float>(x), 24.0f, static_cast<float>(span), 336.0f,
                    0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
            }
        }

        if (CmakeState(this)->m_resultFlag != 0 && CmakeState(this)->m_mode == 0) {
            CmakeState(this)->m_step = CmakeState(this)->m_step + 1;
            CmakeState(this)->m_frame = 0;
            CmakeState(this)->m_resultFlag = 0;
            CmakeState(this)->m_selectionInitialized = 0;
        } else if (CmakeState(this)->m_resultFlag != 0 && CmakeState(this)->m_mode == 2) {
            m_singleCmakeSlot = 999;
            CmakeState(this)->m_resultValue = -1;
        }

        break;
    }
    case 1:
        CmakeNameDraw();
        break;
    case 2:
        CmakeSexDraw();
        break;
    case 3:
        CmakeTribeDraw();
        break;
    case 4:
        CmakeJobDraw();
        break;
    case 5:
        CmakeResultDraw();
        break;
    case 6:
        CmakeResultDraw1();
        break;
    default:
        break;
    }

    if (CmakeState(this)->m_resultFlag == 0) {
        return;
    }

    if (CmakeState(this)->m_mode < 2) {
        CmakeState(this)->m_mode = static_cast<short>(CmakeState(this)->m_mode + 1);
        goto resetFrame;
    }

    s_OldMenu = static_cast<int>(CmakeState(this)->m_step);

    if (CmakeState(this)->m_step == 6) {
        CmakeState(this)->m_step = static_cast<short>(CmakeState(this)->m_select + 1);
    } else if (CmakeState(this)->m_resultDir < 0) {
        if (CmakeState(this)->m_step != 0) {
            if (CmakeState(this)->m_step != 5) {
                CmakeState(this)->m_step = static_cast<short>(CmakeState(this)->m_step - 1);
            } else {
                CmakeState(this)->m_step = static_cast<short>(CmakeState(this)->m_step + 1);
            }
        }
    } else if (CmakeState(this)->m_step != 5) {
        CmakeState(this)->m_step = static_cast<short>(CmakeState(this)->m_step + 1);
    } else {
        CmakeState(this)->m_step = 0;
        CmakeState(this)->m_mode = 2;
        goto initSelection;
    }

    if (CmakeState(this)->m_step == 0) {
        CmakeState(this)->m_mode = 2;
    } else {
        CmakeState(this)->m_mode = 0;
    }

initSelection:
    CmakeState(this)->m_selectionInitialized = 0;
resetFrame:
    CmakeState(this)->m_frame = 0;
    CmakeMcState(this) = 3;
}

/*
 * --INFO--
 * PAL Address: 0x8017352C
 * PAL Size: 616b
 * EN Address: 0x801724A8
 * EN Size: 616b
 * JP Address: 0x8016E034
 * JP Size: 608b
 */
void CMenuPcs::DrawDiaryBase(int page, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(255.0f * alpha);
    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(a);
    GXSetChanMatColor(GX_COLOR0A0, col);

    const bool widePage = (page == 0);
    CMenuPcs::TEX baseTex = static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48);
    if (widePage) {
        baseTex = static_cast<CMenuPcs::TEX>(CMAKE_TEX_DIARY1);
    }
    MenuPcs.SetTexture(baseTex);

    int y0 = widePage ? 24 : 24;
    int frameH = widePage ? 0x180 : 0x150;
    MenuPcs.DrawRect(
        0, 0.0f, static_cast<float>(y0), 32.0f, static_cast<float>(frameH),
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 608.0f, static_cast<float>(y0), 32.0f, static_cast<float>(frameH),
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(widePage ? CMAKE_TEX_DIARY2 : CMAKE_TEX_WORLD49));
    int span;
    for (int x = 0x20; x < 0x260;) {
        span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }

        MenuPcs.DrawRect(
            0, static_cast<float>(x), static_cast<float>(y0), static_cast<float>(span), static_cast<float>(frameH),
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        x += span;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawCmakeWin(float x, float y, float alpha)
{
    (void)y;

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(255.0f * alpha);
    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(a);
    GXSetChanMatColor(GX_COLOR0A0, col);

    int frameH = (x == 0.0f) ? 0x150 : 0x180;
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((x == 0.0f) ? CMAKE_TEX_WORLD48 : CMAKE_TEX_DIARY1));
    MenuPcs.DrawRect(
        0, 0.0f, 24.0f, 32.0f, static_cast<float>(frameH),
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 608.0f, 24.0f, 32.0f, static_cast<float>(frameH),
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((x == 0.0f) ? CMAKE_TEX_WORLD49 : CMAKE_TEX_DIARY2));
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        MenuPcs.DrawRect(
            0, static_cast<float>(tileX), 24.0f, static_cast<float>(tileW), static_cast<float>(frameH),
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        tileX += tileW;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80173258
 * PAL Size: 724b
 * EN Address: 0x801721D4
 * EN Size: 724b
 * JP Address: 0x8016DD48
 * JP Size: 748b
 */
void CMenuPcs::DrawCmakeTitle(int page, float x, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(255.0f * alpha);
    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(a);
    GXSetChanMatColor(GX_COLOR0A0, col);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD28 : CMAKE_TEX_WORLD28));
    MenuPcs.DrawRect(
        0, 214.0f, 32.0f, 112.0f, 56.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 474.0f, 32.0f, 112.0f, 56.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    int baseX = 0x116;
    double offsCalc = static_cast<double>(40.0f - 40.0f * x) / 2.0 + 32.0;
    int offsU = static_cast<int>(offsCalc);
    float offs = static_cast<float>(static_cast<int>(offsCalc));
    MenuPcs.DrawRect(
        0, 278.0f, offs, 248.0f, 40.0f,
        0.0f, 264.0f, 1.0f, x, 0.0f);

    if (x < 1.0) {
        return;
    }

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD45 : CMAKE_TEX_WORLD45));

    baseX += 20.0;
    offsU += 8.0;
    MenuPcs.DrawRect(
        0, static_cast<float>(baseX), static_cast<float>(offsU), 208.0f, 24.0f,
        0.0f, static_cast<float>(page * 0x18), 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawCrystal(int x, int y, float alpha)
{
    AlphaNormal();
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<unsigned char>(alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_CRYSTAL : CMAKE_TEX_CRYSTAL));
    MenuPcs.DrawRect(
        0,
        static_cast<float>(x),
        static_cast<float>(y),
        32.0f, 48.0f,
        static_cast<float>(((static_cast<int>(System.m_frameCounter) >> 1) % 8) << 5), 0.0f,
        1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 424b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawCmakeNameBase(int page, float alpha)
{
    DrawCmakeWin(0.0f, 0.0f, alpha);
    DrawCmakeTitle(page, 0.0f, alpha);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawCmakePageMark(float alpha)
{
    (void)alpha;
}

/*
 * --INFO--
 * PAL Address: 0x80172EF8
 * PAL Size: 864b
 * EN Address: 0x80171E74
 * EN Size: 864b
 * JP Address: 0x8016D9F0
 * JP Size: 856b
 */
void CMenuPcs::DrawCmakeDecision(int yesNoSel, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    float alpha255 = 255.0f * alpha;
    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(alpha255);
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 480.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 552.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);

    if (yesNoSel != 0) {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD44 : CMAKE_TEX_WORLD44));
        MenuPcs.DrawRect(
            0, 516.0f, 360.0f, 48.0f, 48.0f,
            128.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    CFont* font = m_fonts[CMAKE_FONT_VALUE];
    font->SetMargin(1.0f);
    font->SetShadow(1);
    font->SetScale(1.0f);
    font->DrawInit();
    font->SetTlut(7);

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha255)).color);

    int tx;
    int cursorY;
    const char* txt = GetMenuStr(0x29);
    float w = static_cast<float>(font->GetWidth(txt));
    double cursorYBase = 373.0;
    tx = static_cast<int>((120.0f - w) / 2.0 + 480.0);
    cursorY = static_cast<int>(cursorYBase);
    font->SetPosX(static_cast<float>(static_cast<int>((120.0f - w) / 2.0 + 480.0)));
#ifdef VERSION_GCCJGC
    font->SetPosY(static_cast<float>(cursorY));
#else
    font->SetPosY(static_cast<float>(cursorY - 4));
#endif
    font->Draw(txt);
    DrawInit();

    if (yesNoSel != 0) {
        tx -= 0x20;
        tx += static_cast<int>(System.m_frameCounter) % 8;
        DrawCursor(tx, cursorY, alpha);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawCmakeBallCursor(int kind, int frame, float alpha)
{
    (void)kind;
    (void)frame;
    (void)alpha;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 340b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawCmakeCharaText(int page, float alpha)
{
    (void)page;

    CFont* labelFont = m_fonts[CMAKE_FONT_LABEL];
    labelFont->SetMargin(1.0f);
    labelFont->SetShadow(0);
    labelFont->SetScale(1.0f);
    labelFont->DrawInit();

    int a = static_cast<int>(255.0f * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    CColor rgba(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    labelFont->SetColor(rgba.color);

    float labelWidths[4];
    for (int i = 0; i < 4; i++) {
        const char* txt = GetMenuStr(0x2A + i);
        if (txt == 0) {
            txt = "";
        }

        labelWidths[i] = 232.0f + static_cast<float>(labelFont->GetWidth(txt));
        labelFont->SetPosX(232.0f);
        labelFont->SetPosY(0x70 + i * 0x28 - 4.0f);
        labelFont->Draw(txt);
    }

    CFont* valueFont = m_fonts[CMAKE_FONT_VALUE];
    valueFont->SetMargin(1.0f);
    valueFont->SetShadow(1);
    valueFont->SetScale(1.0f);
    valueFont->DrawInit();
    valueFont->SetColor(rgba.color);
    valueFont->SetTlut(6);

    char tribeWithSep[0x40];
    for (int i = 0; i < 4; i++) {
        const char* txt = "";

        switch (i) {
        case 0:
            txt = s_CmakeInfo.m_name;
            break;
        case 1:
            txt = GetMenuStr(s_CmakeInfo.m_gender + 0x11);
            break;
        case 2:
            txt = GetTribeStr(s_CmakeInfo.m_tribe);
            strcpy(tribeWithSep, txt);
            strcat(tribeWithSep, "/");
            txt = tribeWithSep;
            break;
        default:
            txt = GetJobStr(s_CmakeInfo.m_job);
            break;
        }

        if (txt == 0) {
            txt = "";
        }

        valueFont->SetPosX(8.0f + labelWidths[i]);
        valueFont->SetPosY(0x70 + i * 0x28 - 4.0f);
        valueFont->Draw(txt);

        if (i == 2) {
            int hairIndex = s_CmakeInfo.m_tribe * 8;
            if (s_CmakeInfo.m_gender != 0) {
                hairIndex += 4;
            }

            char tribeWithSep[0x40];
            strcpy(tribeWithSep, txt);
            size_t tribeLen = strlen(tribeWithSep);
            if (tribeLen + 1 < sizeof(tribeWithSep)) {
                tribeWithSep[tribeLen] = '/';
                tribeWithSep[tribeLen + 1] = '\0';
            }

            const char* hairTxt = GetHairStr(hairIndex + s_CmakeInfo.m_hair);
            if (hairTxt == 0) {
                hairTxt = "";
            }

            valueFont->SetPosX(
                16.0f + (8.0f + labelWidths[i] + static_cast<float>(valueFont->GetWidth(tribeWithSep))));
            valueFont->SetPosY(0x70 + i * 0x28 - 4.0f);
            valueFont->Draw(hairTxt);
        }
    }

    DrawInit();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 348b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawCmakeCrest(int tribe, int x, int y, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(255.0f * alpha);
    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(a);
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD40));
    MenuPcs.DrawRect(
        0,
        351.0f + static_cast<float>(x),
        96.0f + static_cast<float>(y),
        184.0f, 184.0f,
        static_cast<float>((tribe & 1) * 0xB8),
        static_cast<float>((tribe / 2) * 0xB8),
        1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x80172C1C
 * PAL Size: 732b
 * EN Address: 0x80171B98
 * EN Size: 732b
 * JP Address: 0x8016D714
 * JP Size: 732b
 */
void CMenuPcs::DrawCmakeName(int x, int y, char* text, float alpha)
{
    float textW;

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);

    float nameW = 161.0f;
    int nameX = static_cast<int>(-(nameW / 2.0 - 400.0));

    int baseY = (x != 0) ? 0x130 : 300;

    CFont* font = m_fonts[CMAKE_FONT_VALUE];
    font->SetShadow(1);
    font->SetScale(1.0f);
    font->DrawInit();
    font->renderFlags.fixedWidth = 1;
    font->SetMargin(1.0f);

    alpha = 255.0f * alpha;
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha)).color);
    font->SetTlut(6);

    textW = font->GetWidth(text);
    font->SetPosX(static_cast<float>(nameX));
#ifdef VERSION_GCCJGC
    font->SetPosY(static_cast<float>(baseY));
#else
    font->SetPosY(static_cast<float>(baseY - 4));
#endif
    font->Draw(text);
    font->renderFlags.fixedWidth = 0;
    DrawInit();

    if (y != 0) {
        DrawCrystal(static_cast<int>(static_cast<float>(nameX) + textW), baseY - 0x10, alpha);
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: 0x8016D0E0
 * JP Size: 1588b
 */
#ifdef VERSION_GCCJGC
int CMenuPcs::AddNameChara(int add, int column, int row, int table)
{
    if (add == 0) {
        int count = GetCharaCnt(s_CmakeInfo.m_name);
        if (count == 0) {
            return -1;
        }
        int length = strlen(s_CmakeInfo.m_name);
        if (GetCharaType(s_CmakeInfo.m_name, count - 1) == 0) {
            s_CmakeInfo.m_name[length - 1] = '\0';
        } else {
            s_CmakeInfo.m_name[length - 2] = '\0';
        }
    } else {
        char picked[3];
        memset(picked, 0, 3);
        char* text = const_cast<char*>(s_NameEntryStr[row + table * 5]);
        GetChara(text, column, picked);
        int count = GetCharaCnt(s_CmakeInfo.m_name);
        if (count >= 7) {
            if (strcmp(picked, s_nameDakutenMark) != 0 && strcmp(picked, s_nameHandakutenMark) != 0) {
                return -1;
            }
        } else {
            GetChara(text, column, picked);
            if (count == 0) {
                strcat(s_CmakeInfo.m_name, picked);
                return 0;
            }
        }
        int type = GetCharaType(text, count - 1);
        if (type == 0 && count >= 7) {
            return -1;
        }
        if (type != 0 && strcmp(picked, s_nameDakutenMark) == 0) {
            char* last = s_CmakeInfo.m_name + strlen(s_CmakeInfo.m_name) - 2;
            for (int group = 0; group < 2; ++group) {
                const char* characters = s_NameEntryVoiced[group];
                int length = strlen(characters);
                for (int pos = 0; pos < length; pos += 2, characters += 2) {
                    if (memcmp(characters, last, 2) == 0) {
                        ++last[1];
                        return 0;
                    }
                }
            }
            if (memcmp(last, s_nameKatakanaU, 2) == 0) {
                strcpy(last, s_nameKatakanaVu);
            } else {
                if (count >= 7) {
                    return -1;
                }
                strcat(s_CmakeInfo.m_name, picked);
            }
            return 0;
        } else if (type != 0 && strcmp(picked, s_nameHandakutenMark) == 0) {
            char* last = s_CmakeInfo.m_name + strlen(s_CmakeInfo.m_name) - 2;
            int length = strlen(s_NameEntryVoiced[1]);
            const char* characters = s_NameEntryVoiced[1];
            for (int pos = 0; pos < length; pos += 2, characters += 2) {
                if (memcmp(characters, last, 2) == 0) {
                    last[1] += 2;
                    return 0;
                }
            }
            if (count >= 7) {
                return -1;
            }
            strcat(s_CmakeInfo.m_name, picked);
        } else {
            strcat(s_CmakeInfo.m_name, picked);
        }
    }
    return 0;
}
#else
inline int CMenuPcs::AddNameChara(int c, int slot, int, int)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    int index = slot;
    if (index < 0) {
        index = 0;
    }
    if (index > 0x14) {
        index = 0x14;
    }
    self[0x85C + index] = static_cast<unsigned char>(c);
    return 0;
}

#endif

/*
 * --INFO--
 * PAL Address: 0x801728bc
 * PAL Size: 864b
 * EN Address: 0x80171838
 * EN Size: 864b
 * JP Address: 0x8016CE08
 * JP Size: 728b
 */
void CMenuPcs::DrawCmakeYesNo(int yesNoSel, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    float alpha255 = 255.0f * alpha;
    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(alpha255);
    GXSetChanMatColor(GX_COLOR0A0, col);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 432.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 568.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);

    if (yesNoSel != 0) {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD44));
        MenuPcs.DrawRect(
            0, 464.0f, 360.0f, 128.0f, 48.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    CFont* font = m_fonts[CMAKE_FONT_VALUE];
    font->SetMargin(1.0f);
    font->SetShadow(1);
    font->SetScale(1.0f);
    font->DrawInit();
    font->SetTlut(7);

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha255)).color);

    const char* text = GetMenuStr(1);
#ifdef VERSION_GCCJGC
    font->GetWidth(text);
    int yesX = 460;
    font->SetPosX(static_cast<float>(yesX));
    font->SetPosY(373.0f);
#else
    float yesW = static_cast<float>(font->GetWidth(text));
    int yesX = 0x1D0;
    yesX += (48.0f - yesW) / 2.0f;
    font->SetPosX(static_cast<float>(yesX));
    font->SetPosY(369.0f);
#endif
    font->Draw(text);

    text = GetMenuStr(2);
#ifdef VERSION_GCCJGC
    font->GetWidth(text);
    int noX = 532;
    font->SetPosX(static_cast<float>(noX));
    font->SetPosY(373.0f);
#else
    float noW = static_cast<float>(font->GetWidth(text));
    int noX = 0x218;
    noX += (48.0f - noW) / 2.0f;
    font->SetPosX(static_cast<float>(noX));
    font->SetPosY(369.0f);
#endif
    font->Draw(text);

    DrawInit();
    if (yesNoSel != 0) {
        int cursorBase = noX;
        if (yesNoSel == 1) {
            cursorBase = yesX;
        }
        cursorBase -= 0x24;
        cursorBase += static_cast<int>(System.m_frameCounter) % 8;
        DrawCursor(cursorBase, 0x175, alpha);
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeOpen()
{
    CmakeMenuState* state = CmakeState(this);
    state->m_mode = 0;
    state->m_step = 0;
    state->m_frame = 0;
    state->m_resultDir = 0;
    state->m_initialized = 0;
    state->m_selectionInitialized = 0;
    state->m_resultFlag = 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeCtrl()
{
    CmakeMenuState* state = CmakeState(this);
    short& mode = state->m_mode;
    short& step = state->m_step;
    short& frame = state->m_frame;
    short& resultDir = state->m_resultDir;
    short& resultFlag = state->m_resultFlag;

    CalcSingCMake();

    if (resultFlag == 0) {
        return;
    }

    if (step == 0) {
        if (mode == 0) {
            step = 1;
            frame = 0;
            resultFlag = 0;
            state->m_selectionInitialized = 0;
            CmakeMcState(this) = 3;
        } else if (mode == 2) {
            CmakeSlot(this) = 999;
            state->m_resultValue = -1;
            resultFlag = 0;
        }
        return;
    }

    if (mode < 2) {
        mode = static_cast<short>(mode + 1);
        frame = 0;
        resultFlag = 0;
        CmakeMcState(this) = 3;
        return;
    }

    s_OldMenu = static_cast<int>(step);

    if (step == 6) {
        step = static_cast<short>(state->m_select + 1);
        mode = (step == 0) ? 2 : 0;
    } else if (resultDir < 0) {
        if (step == 5) {
            step = 6;
        } else {
            step = static_cast<short>(step - 1);
        }
        mode = (step == 0) ? 2 : 0;
    } else if (step != 5) {
        step = static_cast<short>(step + 1);
        mode = (step == 0) ? 2 : 0;
    } else {
        step = 0;
        mode = 2;
    }

    state->m_selectionInitialized = 0;
    frame = 0;
    resultFlag = 0;
    CmakeMcState(this) = 3;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeClose()
{
    CmakeMenuState* state = CmakeState(this);
    state->m_step = 0;
    state->m_mode = 2;
    state->m_frame = 0;
    state->m_resultDir = -1;
    state->m_resultFlag = 0;
    state->m_selectionInitialized = 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeDraw()
{
    DrawSingCMake();
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeNameOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 1;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80171FA0
 * PAL Size: 2332b
 * EN Address: 0x80170F1C
 * EN Size: 2332b
 * JP Address: 0x8016C4B0
 * JP Size: 2392b
 */
int CMenuPcs::CmakeNameCtrl()
{
    short repeat;
    short down;
#ifndef VERSION_GCCJGC
    const char* name;
#endif

    down = Pad.GetButtonDown(0);
    repeat = Pad.GetButtonRepeat(0);

    if (repeat == 0) {
        return 0;
    }

    if (CmakeMcState(this) != 3) {
        if (CmakeMcState(this) == 1 && (down & 0x300) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            CmakeMcState(this) = 2;
        }
        return 0;
    }
    {
        if ((repeat & 0x8) != 0) {
            if (static_cast<int>(CmakeState(this)->m_row) != 0) {
                CmakeState(this)->m_row -= 1;
            } else if (CmakeState(this)->m_select >= 10) {
                CmakeState(this)->m_row = 5;
            } else {
                CmakeState(this)->m_row = 4;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            if (CmakeState(this)->m_row < (CmakeState(this)->m_select >= 10 ? 5 : 4)) {
                CmakeState(this)->m_row += 1;
            } else {
                CmakeState(this)->m_row = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0x1) != 0) {
            if (CmakeState(this)->m_row >= 5) {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else {
                CmakeMenuState* state = CmakeState(this);
                if (static_cast<int>(state->m_select) != 0) {
                    state->m_select -= 1;
                } else {
                    state->m_select = 0xB;
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        } else if ((repeat & 0x2) != 0) {
            if (CmakeState(this)->m_row >= 5) {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else {
                CmakeMenuState* state = CmakeState(this);
                if (state->m_select < 0xB) {
                    state->m_select += 1;
                } else {
                    state->m_select = 0;
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        }

        if ((repeat & 0xF) == 0) {
            if ((down & 0x40) != 0) {
                CmakeState(this)->m_table -= 1;
                if (CmakeState(this)->m_table < 0) {
                    CmakeState(this)->m_table = CMAKE_NAME_PAGE_COUNT - 1;
                }
                Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
            } else if ((down & 0x20) != 0) {
                CmakeState(this)->m_table += 1;
                if (CmakeState(this)->m_table > CMAKE_NAME_PAGE_COUNT - 1) {
                    CmakeState(this)->m_table = 0;
                }
                Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
            } else if ((down & 0x1000) != 0) {
                CmakeState(this)->m_select = 0xB;
                CmakeState(this)->m_row = 5;
                Sound.PlaySe(2, 0x40, 0x7F, 0);
            } else if ((down & 0x100) != 0) {
#ifndef VERSION_GCCJGC
                short curTable;
                short curSelect;
                const char* rowText;
#endif
                short curRow = CmakeState(this)->m_row;
                if (curRow >= 5) {
#ifdef VERSION_GCCJGC
                    if (GetCharaCnt(s_CmakeInfo.m_name) == 0) {
#else
                    int emptyLen = strlen(s_CmakeInfo.m_name);
                    if ((emptyLen & ((-emptyLen | emptyLen) >> 31)) == 0) {
#endif
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                        return 0;
                    }

                    int nameLen = strlen(s_CmakeInfo.m_name);
                    int spaceCount = 0;
                    for (; spaceCount < nameLen; spaceCount++) {
                        if (s_CmakeInfo.m_name[spaceCount] != ' ') {
                            break;
                        }
                    }
                    if (spaceCount == nameLen) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                        return 0;
                    }

                    if (IsDuplicateCmakeName(this, s_CmakeInfo.m_name)) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                        short winX;
                        short winY;
                        GetWinSize(0x14, &winX, &winY, 0);
                        SetMcWinInfo((int)winX, (int)winY);
                        CmakeMcState(this) = 0;
                    } else {
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        CmakeState(this)->m_resultDir = 1;
                        return 1;
                    }
                } else {
#ifdef VERSION_GCCJGC
                    int ret = AddNameChara(1, CmakeState(this)->m_select, curRow, CmakeState(this)->m_table);
#else
                    curTable = CmakeState(this)->m_table;
                    curSelect = CmakeState(this)->m_select;
                    char picked[12];
                    memset(picked, 0, 3);
                    rowText = s_NameEntryStr[curRow + curTable * 5];
                    picked[0] = '\0';
                    int rowLen = strlen(rowText);
                    if (rowLen != 0) {
                        int i = 0;
                        int j = i;
                        for (; 0 < rowLen; rowLen = rowLen - 1) {
                            if (i == curSelect) {
                                picked[0] = rowText[j];
                                picked[1] = '\0';
                                break;
                            }
                            i = i + 1;
                            j = j + 1;
                        }
                    }
                    unsigned int rawLen = strlen(s_CmakeInfo.m_name);
                    int nameLen = rawLen & (static_cast<int>(-rawLen | rawLen) >> 31);
                    int ret;
                    if (nameLen >= 7) {
                        ret = -1;
                    } else {
                        picked[0] = '\0';
                        rowLen = strlen(rowText);
                        if (rowLen != 0) {
                            int i = 0;
                            int j = i;
                            for (; 0 < rowLen; rowLen = rowLen - 1) {
                                if (i == curSelect) {
                                    picked[0] = rowText[j];
                                    picked[1] = '\0';
                                    break;
                                }
                                i = i + 1;
                                j = j + 1;
                            }
                        }
                        if (nameLen == 0) {
                            strcat(s_CmakeInfo.m_name, picked);
                            ret = 0;
                        } else if (-((__cntlzw(strlen(rowText)) & 0x20) >> 5) == 0 && nameLen >= 7) {
                            ret = -1;
                        } else {
                            strcat(s_CmakeInfo.m_name, picked);
                            ret = 0;
                        }
                    }
#endif
                    if (ret != 0) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    } else {
#ifdef VERSION_GCCJGC
                        if (GetCharaCnt(s_CmakeInfo.m_name) >= 7) {
#else
                        unsigned int finalLen = strlen(s_CmakeInfo.m_name);
                        if (static_cast<int>(finalLen & (static_cast<int>(-finalLen | finalLen) >> 31)) >= 7) {
#endif
                            CmakeState(this)->m_select = 0xB;
                            CmakeState(this)->m_row = 5;
                        }
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                    }
                }
            } else if ((down & 0x200) != 0) {
#ifdef VERSION_GCCJGC
                if (GetCharaCnt(s_CmakeInfo.m_name) != 0) {
                    int bsRet = AddNameChara(0, CmakeState(this)->m_select, CmakeState(this)->m_row, CmakeState(this)->m_table);
#else
                unsigned int bsLen0 = strlen(s_CmakeInfo.m_name);
                if ((bsLen0 & (static_cast<int>(-bsLen0 | bsLen0) >> 31)) != 0) {
                    int bsRet;
                    name = s_CmakeInfo.m_name;
                    unsigned int bsLen1 = strlen(name);
                    if ((bsLen1 & (static_cast<int>(-bsLen1 | bsLen1) >> 31)) == 0) {
                        bsRet = -1;
                    } else {
                        int bsPos = strlen(s_CmakeInfo.m_name);
                        if (-((__cntlzw(strlen(name)) & 0x20) >> 5) == 0) {
                            s_CmakeInfo.m_name[bsPos - 1] = '\0';
                        } else {
                            s_CmakeInfo.m_name[bsPos - 2] = '\0';
                        }
                        bsRet = 0;
                    }
#endif
                    if (bsRet != 0) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    } else {
                        Sound.PlaySe(3, 0x40, 0x7F, 0);
                    }
                } else {
                    Sound.PlaySe(0x34, 0x40, 0x7F, 0);
                    ChgModel(static_cast<int>(CmakeSlot(this)), -1, -1, -1);
                    CmakeState(this)->m_resultDir = -1;
                    return -1;
                }
            }
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeNameClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80171340
 * PAL Size: 3168b
 * EN Address: 0x801702BC
 * EN Size: 3168b
 * JP Address: 0x8016B6E8
 * JP Size: 3528b
 */
void CMenuPcs::CmakeNameDraw()
{
    CmakeMenuState* state = CmakeState(this);
    int frame = static_cast<int>(state->m_frame) - 1;
    float a255;
    float alpha;
    if (frame < 0) {
        frame = 0;
    }

    if (state->m_mode == 0) {
        alpha = static_cast<float>(0.1 * static_cast<double>(frame));
    } else if (state->m_mode == 1) {
        alpha = 1.0f;
    } else {
        alpha = static_cast<float>(-(0.1 * static_cast<double>(frame) - 1.0));
    }

    DrawWMFrame0(1, 1.0f);
    SetCmakeBlendMatColor(1.0f);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48));
    MenuPcs.DrawRect(
        0, 0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD49));
    for (int x = 0x20; x < 0x260;) {
        int span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }
        MenuPcs.DrawRect(
            0, static_cast<float>(x), 24.0f, static_cast<float>(span), 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        x += span;
    }

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 192.0f, 56.0f, 416.0f, 264.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    if ((s_OldMenu == 2) && (CmakeState(this)->m_mode == 0)) {
        DrawNamePreviewChara(this, 1.0f, 0xFF);
        DrawCmakeTitle(1, alpha, 1.0f);
    } else if ((CmakeState(this)->m_mode != 2) ||
               (CmakeState(this)->m_mode == 2 && CmakeState(this)->m_resultDir == -1)) {
        DrawNamePreviewChara(this, alpha, static_cast<int>(255.0f * alpha));
        DrawCmakeTitle(1, 1.0f, alpha);
    } else {
        DrawNamePreviewChara(this, 1.0f, 0xFF);
        DrawCmakeTitle(1, alpha, 1.0f);
    }

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    float titleW = 280.0f;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(-(titleW / 2.0 - 400.0))), 268.0f, titleW, 64.0f,
        0.0f, 304.0f, 1.0f, 1.0f, 0.0f);

    SetCmakeBlendMatColor(alpha);
#ifdef VERSION_GCCJGC
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 184.0f, 216.0f, 40.0f, 40.0f,
        256.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    double crestRightX = 576.0;
    int rightX = static_cast<int>(crestRightX);
    MenuPcs.DrawRect(
        0, static_cast<float>(rightX), 216.0f, 40.0f, 40.0f,
        256.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD29 : CMAKE_TEX_WORLD29));
    MenuPcs.DrawRect(
        0, 192.0f, 224.0f, 24.0f, 24.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        0, static_cast<float>(rightX + 8), 224.0f, 24.0f, 24.0f,
        24.0f, 0.0f, 1.0f, 1.0f, 0.0f);
#else
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x68 : 0x41));
    MenuPcs.DrawRect(
        0, 184.0f, 216.0f, 48.0f, 48.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    double crestRightX = 568.0;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(crestRightX)), 216.0f, 48.0f, 48.0f,
        48.0f, 0.0f, 1.0f, 1.0f, 0.0f);
#endif

    if ((CmakeState(this)->m_mode == 1) && (CmakeState(this)->m_row < 5)) {
        short sel = CmakeState(this)->m_select;
        int cellX = (CmakeState(this)->m_row < 5) ? 0xE5 : 0xE5;
        int cursorY = CmakeState(this)->m_row * 0x20 + 0x63;
        cellX = static_cast<int>(
            26.9f * static_cast<float>(sel) + static_cast<float>(cellX));
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD44 : CMAKE_TEX_WORLD44));
        MenuPcs.DrawRect(
            0, static_cast<float>(cellX), static_cast<float>(cursorY), 48.0f, 48.0f,
            128.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    short table = CmakeState(this)->m_table;
    int i;
    CFont* font = GetCmakeKeyboardFont(this);
    font->SetShadow(0);
    font->SetScale(1.0f);
    font->DrawInit();
    font->renderFlags.fixedWidth = 1;
    font->SetMargin(4.9f);
    SetCmakeFontColor(font, alpha);

    int tableBase = table * 5;
    for (i = 0; i < 5; i++) {
        const char* rowText = s_NameEntryStr[tableBase + i];
        font->SetPosX(240.0f);
#ifdef VERSION_GCCJGC
        font->SetPosY(static_cast<float>(0x70 + i * 0x20));
#else
        font->SetPosY(static_cast<float>(0x6C + i * 0x20));
#endif
        font->Draw(rowText);
    }

    font->renderFlags.fixedWidth = 0;
    DrawInit();

    if ((CmakeState(this)->m_mode == 1) && (CmakeState(this)->m_row < 5)) {
        int cursorLeft = (CmakeState(this)->m_select == 0) ? 0xC8 : 0xC8;
        cursorLeft = static_cast<int>(26.9f * static_cast<float>(CmakeState(this)->m_select) +
            static_cast<float>(cursorLeft));
        cursorLeft += static_cast<int>(System.m_frameCounter) % 8;
        DrawCursor(cursorLeft, CmakeState(this)->m_row * 0x20 + 0x70, 1.0f);
    }

    int nameCursor = static_cast<int>(
        static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(1 - CmakeState(this)->m_mode))) >> 5);
    if (CmakeState(this)->m_row >= 5) {
        nameCursor = 0;
    }
#ifdef VERSION_GCCJGC
    if (GetCharaCnt(s_CmakeInfo.m_name) >= 7) {
#else
    unsigned int nameLen = strlen(s_CmakeInfo.m_name);
    if (static_cast<int>(nameLen & (static_cast<int>(-nameLen | nameLen) >> 31)) >= 7) {
#endif
        nameCursor = 0;
    }
    DrawCmakeName(0, nameCursor, s_CmakeInfo.m_name, alpha);
    DrawCmakeDecision((CmakeState(this)->m_row >= 5) ? 1 : 0, alpha);

    if (CmakeMcState(this) != 3) {
        DrawMcWin(-1, 0);
        if (CmakeMcState(this) == 1) {
            DrawMcWinMess(0x14, 0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeSexOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 2;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeSexCtrl()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    short& mode = cmakeState->m_mode;
    short& frame = cmakeState->m_frame;
    short& sel = cmakeState->m_select;
    unsigned short repeat = GetButtonRepeat(0);
    unsigned short down = GetButtonDown(0);

    if (mode == 1) {
        if ((repeat & 0x3) != 0) {
            sel = (sel == 0) ? 1 : 0;
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if (((repeat & 0x3) == 0) && ((down & 0x100) != 0)) {
            s_CmakeInfo.m_gender = static_cast<signed char>(sel);
            MenuS16(this, 0x860) = sel;
            mode = 2;
            frame = 0;
            cmakeState->m_resultDir = 1;
            Sound.PlaySe(2, 0x40, 0x7F, 0);
        } else if (((repeat & 0x3) == 0) && ((down & 0x200) != 0)) {
            mode = 2;
            frame = 0;
            cmakeState->m_resultDir = -1;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
        } else if (frame < 30) {
            frame = frame + 1;
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeSexClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80170CE8
 * PAL Size: 1624b
 * EN Address: 0x8016FC70
 * EN Size: 1612b
 * JP Address: 0x8016B0C8
 * JP Size: 1568b
 */
void CMenuPcs::CmakeSexDraw()
{
    CmakeMenuState* state = CmakeState(this);
    int frame = static_cast<int>(state->m_frame) - 1;
    float a255;
    float alpha;
    if (frame < 0) {
        frame = 0;
    }

    if (state->m_mode == 0) {
        alpha = static_cast<float>(0.1 * static_cast<double>(frame));
    } else if (state->m_mode == 1) {
        alpha = 1.0f;
    } else {
        alpha = static_cast<float>(-(0.1 * static_cast<double>(frame) - 1.0));
    }
    DrawWMFrame0(1, 1.0f);

    SetCmakeBlendMatColor(1.0f);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48));
    MenuPcs.DrawRect(
        0, 0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD49));
    int span;
    for (int x = 0x20; x < 0x260;) {
        span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }
        MenuPcs.DrawRect(
            0, static_cast<float>(x), 24.0f, static_cast<float>(span), 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        x += span;
    }

    DrawCmakePreviewCharaAlpha(this, 1.0f);

    SetCmakeBlendMatColor(alpha);
    a255 = 255.0f * alpha;
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    float sexW = 256.0f;
    float sexH = 162.4615478515625f;
    MenuPcs.DrawRect(
        0,
        static_cast<float>(static_cast<int>(-(sexW / 2.0 - 400.0))),
        static_cast<float>(static_cast<int>(-(sexH / 2.0 - 188.0))),
        416.0f, 264.0f,
        0.0f, 0.0f, 0.6153846383094788f, 0.6153846383094788f, 0.0f);
    DrawCmakeTitle(2, alpha, 1.0f);

    CFont* font = m_fonts[CMAKE_FONT_LABEL];
    font->SetMargin(1.0f);
    font->SetShadow(0);
    font->SetScale(1.0f);
    font->DrawInit();

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a255)).color);

#ifdef VERSION_GCCJGC
    float labelWidth;
#else
    float labelWidth = 0.0f;
#endif
    int y;
    int i;
    for (i = 0, y = 0x9C; i < 2; ++i) {
        const char* txt = GetMenuStr(0x11 + i);
        float width = static_cast<float>(font->GetWidth(txt));
#ifdef VERSION_GCCJGC
        labelWidth = width;
#else
        if (labelWidth < width) {
            labelWidth = width;
        }
#endif
        float x = static_cast<float>(-(width / 2.0 - 400.0));
        font->SetPosX(x);
#ifdef VERSION_GCCJGC
        font->SetPosY(static_cast<float>(y));
#else
        font->SetPosY(static_cast<float>(y) - 4.0f);
#endif
        font->Draw(txt);
        y += 0x28;
    }
    DrawInit();

    if (CmakeState(this)->m_mode == 1) {
        int sel = CmakeState(this)->m_select;
        int wobble = static_cast<int>(System.m_frameCounter) % 8;
        int cursorX = static_cast<int>(
            static_cast<double>(static_cast<float>(400.0 - labelWidth / 2.0) +
                                static_cast<float>(wobble)) -
            labelWidth / 2.0);
        float cy = 156.0f;
        cy += static_cast<float>(sel * 0x28);
        int cursorY = static_cast<int>(cy);
        DrawCursor(cursorX, cursorY, 1.0f);
    }

}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeTribeOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 3;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801708B0
 * PAL Size: 1080b
 * EN Address: 0x8016F838
 * EN Size: 1080b
 * JP Address: 0x8016AC20
 * JP Size: 1192b
 */
int CMenuPcs::CmakeTribeCtrl()
{
    short repeat;
    short down;

    down = Pad.GetButtonDown(0);
    repeat = Pad.GetButtonRepeat(0);

    if (repeat == 0) {
        return 0;
    }

    if (CmakeMcState(this) != 3) {
        if (CmakeMcState(this) == 1 && (down & 0x300) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            CmakeMcState(this) = 2;
        }
        return 0;
    } else {
        int fieldSelect = CmakeState(this)->m_fieldSelect;
        int tribeCount = (fieldSelect != 0) ? 4 : 4;

        if ((repeat & 0x8) != 0) {
            short* values = &CmakeState(this)->m_select;
            int idx = fieldSelect;
            if (static_cast<int>(values[idx]) != 0) {
                values[idx] = static_cast<short>(values[idx] - 1);
            } else {
                values[idx] = static_cast<short>(tribeCount - 1);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            short* values = &CmakeState(this)->m_select;
            int idx = fieldSelect;
            if (values[idx] < tribeCount - 1) {
                values[idx] = static_cast<short>(values[idx] + 1);
            } else {
                values[idx] = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0xC) == 0) {
            if ((down & 0x100) != 0) {
                Sound.PlaySe(2, 0x40, 0x7F, 0);
                if (fieldSelect == 0) {
                    CmakeState(this)->m_fieldSelect = static_cast<short>(CmakeState(this)->m_fieldSelect + 1);
                } else {
                    int slot;
                    for (slot = 0; slot < 8; ++slot) {
                        if ((Game.m_caravanWorkArr[slot].m_shopState != 0) &&
#ifndef VERSION_GCCJGC
                            (Game.m_caravanWorkArr[slot].m_caravanLocalFlags != 1) &&
#endif
                            (Game.m_caravanWorkArr[slot].m_tribeId == CmakeState(this)->m_select) &&
                            (Game.m_caravanWorkArr[slot].m_appearanceVariant == CmakeState(this)->m_row) &&
                            (Game.m_caravanWorkArr[slot].m_genderFlag == s_CmakeInfo.m_gender)) {
                            break;
                        }
                    }

                    if (slot < 8) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                        short winX;
                        short winY;
                        GetWinSize(0x15, &winX, &winY, 0);
                        SetMcWinInfo(static_cast<int>(winX), static_cast<int>(winY));
                        CmakeMcState(this) = 0;
                        return 0;
                    } else {
                        s_CmakeInfo.m_tribe = static_cast<signed char>(CmakeState(this)->m_select);
                        s_CmakeInfo.m_hair = static_cast<signed char>(CmakeState(this)->m_row);
                        ChgModel(static_cast<int>(CmakeSlot(this)),
                                 static_cast<int>(s_CmakeInfo.m_tribe),
                                 static_cast<int>(s_CmakeInfo.m_hair),
                                 static_cast<int>(s_CmakeInfo.m_gender));
                        CmakeState(this)->m_resultDir = 1;
                        return 1;
                    }
                }
            } else if ((down & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                if (fieldSelect == 0) {
                    CmakeState(this)->m_resultDir = -1;
                    return 1;
                }

                CmakeState(this)->m_fieldSelect = static_cast<short>(CmakeState(this)->m_fieldSelect - 1);
            }
        }

        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeTribeClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8016FFBC
 * PAL Size: 2292b
 * EN Address: 0x8016EF44
 * EN Size: 2292b
 * JP Address: 0x8016A348
 * JP Size: 2264b
 */
void CMenuPcs::CmakeTribeDraw()
{
    CmakeMenuState* state = CmakeState(this);
    int frame = static_cast<int>(state->m_frame) - 1;
    float a255;
    float alpha;
    if (frame < 0) {
        frame = 0;
    }

    if (state->m_mode == 0) {
        alpha = static_cast<float>(0.1 * static_cast<double>(frame));
    } else if (state->m_mode == 1) {
        alpha = 1.0f;
    } else {
        alpha = static_cast<float>(-(0.1 * static_cast<double>(frame) - 1.0));
    }

    DrawWMFrame0(1, 1.0f);

    SetCmakeBlendMatColor(1.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD49));
    {
        int tileW;
        for (int tileX = 0x20; tileX < 0x260; tileX += tileW) {
            tileW = 0x20;
            if (0x260 - tileX < 0x20) {
                tileW = 0x260 - tileX;
            }

            MenuPcs.DrawRect(
                0,
                static_cast<float>(tileX), 24.0f, static_cast<float>(tileW), 336.0f,
                0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
    }

    DrawCmakePreviewCharaAlpha(this, 1.0f);

    SetCmakeBlendMatColor(alpha);
    a255 = 255.0f * alpha;
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    float boxW = 416.0f;
    float boxH = 240.0f;
    MenuPcs.DrawRect(
        0,
        static_cast<float>(static_cast<int>(-(boxW / 2.0 - 400.0))),
        static_cast<float>(static_cast<int>(-(boxH / 2.0 - 188.0))),
        boxW, 264.0f,
        0.0f, 0.0f, 1.0f, 0.90909094f, 0.0f);

    DrawCmakeTitle(3, alpha, 1.0f);
    {
        int tribe = CmakeState(this)->m_select;
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD40));
        MenuPcs.DrawRect(
            0,
            351.0f, 96.0f, 184.0f, 184.0f,
            static_cast<float>((tribe & 1) * 0xB8),
            static_cast<float>((tribe / 2) * 0xB8),
            1.0f, 1.0f, 0.0f);
    }

    CFont* tribeFont = m_fonts[CMAKE_FONT_LABEL];
    tribeFont->SetMargin(1.0f);
    tribeFont->SetShadow(0);
    tribeFont->SetScale(1.0f);
    tribeFont->DrawInit();
    tribeFont->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a255)).color);

    const char* txt;
    int y;
    int i;
    for (i = 0, y = 0x88; i < 4; i++, y += 0x1C) {
        txt = GetTribeStr(i);
        tribeFont->SetPosX(264.0f);
#ifdef VERSION_GCCJGC
        tribeFont->SetPosY(static_cast<float>(y));
#else
        tribeFont->SetPosY(static_cast<float>(y) - 4.0f);
#endif
        tribeFont->Draw(txt);
    }

    CFont* hairFont = m_fonts[CMAKE_FONT_VALUE];
    hairFont->SetMargin(1.0f);
    hairFont->SetShadow(1);
    hairFont->SetScale(1.0f);
    hairFont->DrawInit();
    hairFont->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a255)).color);
    hairFont->SetTlut(6);

    int hairBase = CmakeState(this)->m_select * 8;
    if (s_CmakeInfo.m_gender != 0) {
        hairBase += 4;
    }

    for (i = 0, y = 0x88; i < 4; i++, y += 0x1C) {
        const char* txt = GetHairStr(hairBase + i);
        hairFont->SetPosX(384.0f);
#ifdef VERSION_GCCJGC
        hairFont->SetPosY(static_cast<float>(y));
#else
        hairFont->SetPosY(static_cast<float>(y) - 4.0f);
#endif
        hairFont->Draw(txt);
    }

    DrawInit();

    if (CmakeState(this)->m_mode == 1) {
        float tribeX = 228.0f;
        float cursorY = static_cast<float>(0x88 + CmakeState(this)->m_select * 0x1C);

        if (CmakeState(this)->m_fieldSelect == 0) {
            tribeX += static_cast<float>(static_cast<int>(System.m_frameCounter) % 8);
            DrawCursor(static_cast<int>(tribeX), static_cast<int>(cursorY), alpha);
        } else {
            if ((System.m_frameCounter & 1) != 0) {
                DrawCursor(static_cast<int>(tribeX), static_cast<int>(cursorY), alpha);
            }

            float hairX = 348.0f;
            DrawCursor(
                static_cast<int>(hairX + static_cast<float>(static_cast<int>(System.m_frameCounter) % 8)),
                static_cast<int>(static_cast<float>(0x88 + CmakeState(this)->m_row * 0x1C)), alpha);
        }
    }

    if (CmakeMcState(this) != 3) {
        DrawMcWin(-1, 0);
        if (CmakeMcState(this) == 1) {
            DrawMcWinMess(0x15, 0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeJobOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 4;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8016FB38
 * PAL Size: 1156b
 * EN Address: 0x8016EAC0
 * EN Size: 1156b
 * JP Address: 0x80169EF4
 * JP Size: 1108b
 */
int CMenuPcs::CmakeJobCtrl()
{
    short repeat;
    short down;

    down = Pad.GetButtonDown(0);
    repeat = Pad.GetButtonRepeat(0);

    if (repeat == 0) {
        return 0;
    }

    if (CmakeMcState(this) != 3) {
        if (CmakeMcState(this) == 1 && (down & 0x300) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            CmakeMcState(this) = 2;
        }
        return 0;
    } else {
        if ((repeat & 0x8) != 0) {
            if ((CmakeState(this)->m_select % 4) != 0) {
                CmakeState(this)->m_select -= 1;
            } else {
                CmakeState(this)->m_select += 3;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            if ((CmakeState(this)->m_select % 4) < 3) {
                CmakeState(this)->m_select += 1;
            } else {
                CmakeState(this)->m_select -= 3;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0x3) != 0) {
            if (CmakeState(this)->m_select <= 3) {
                CmakeState(this)->m_select += 4;
            } else {
                CmakeState(this)->m_select -= 4;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0xF) == 0) {
            if ((down & 0x100) != 0) {
                int slot;
                for (slot = 0; slot < 8; ++slot) {
                    if (slot != CmakeSlot(this) &&
                        Game.m_caravanWorkArr[slot].m_shopState != 0 &&
#ifndef VERSION_GCCJGC
                        Game.m_caravanWorkArr[slot].m_caravanLocalFlags != 1 &&
#endif
                        Game.m_caravanWorkArr[slot].m_jobType == CmakeState(this)->m_select) {
                        break;
                    }
                }

                if (slot < 8) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                    short winX;
                    short winY;
                    GetWinSize(0x16, &winX, &winY, 0);
                    SetMcWinInfo((int)winX, (int)winY);
                    CmakeMcState(this) = 0;
                    return 0;
                } else {
                    s_CmakeInfo.m_job = static_cast<signed char>(CmakeState(this)->m_select);
                    CmakeState(this)->m_resultDir = 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                    return 1;
                }
            } else if ((down & 0x200) != 0) {
                ChgModel(static_cast<int>(CmakeSlot(this)), -1, -1, -1);
                CmakeState(this)->m_resultDir = -1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                return 1;
            }
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeJobClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8016F4F8
 * PAL Size: 1600b
 * EN Address: 0x8016E480
 * EN Size: 1600b
 * JP Address: 0x801698B8
 * JP Size: 1596b
 */
void CMenuPcs::CmakeJobDraw()
{
    CmakeMenuState* state = CmakeState(this);
    int frame = static_cast<int>(state->m_frame) - 1;
    float alpha;
    if (frame < 0) {
        frame = 0;
    }

    if (state->m_mode == 0) {
        alpha = static_cast<float>(0.1 * static_cast<double>(frame));
    } else if (state->m_mode == 1) {
        alpha = 1.0f;
    } else {
        alpha = static_cast<float>(-(0.1 * static_cast<double>(frame) - 1.0));
    }

    DrawWMFrame0(1, 1.0f);

    SetCmakeBlendMatColor(1.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD49));
    {
        int span;
        for (int x = 0x20; x < 0x260; x += span) {
            span = 0x20;
            if ((0x260 - x) < span) {
                span = 0x260 - x;
            }

            MenuPcs.DrawRect(
                0,
                static_cast<float>(x), 24.0f, static_cast<float>(span), 336.0f,
                0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
    }

    DrawCmakePreviewCharaAlpha(this, 1.0f);

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0,
        192.0f, 56.0f, 416.0f, 264.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    DrawCmakeTitle(5, alpha, 1.0f);

    CFont* font = m_fonts[CMAKE_FONT_LABEL];
    font->SetMargin(1.0f);
    font->SetShadow(0);
    font->SetScale(1.0f);
    font->DrawInit();

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).color);

    for (int i = 0; i < 8; ++i) {
        const char* txt = GetJobStr(i);
        int x = (i < 4) ? 0x110 : 0x1A8;
        int row = i % 4;
        font->SetPosX(x);
#ifdef VERSION_GCCJGC
        font->SetPosY(static_cast<float>(0x70 + row * 0x28));
#else
        font->SetPosY(static_cast<float>(0x70 + row * 0x28) - 4.0f);
#endif
        font->Draw(txt);
    }

    if (CmakeState(this)->m_mode == 1) {
        int sel = CmakeState(this)->m_select;
        int cursorX = 0x1A8;
        if (sel < 4) {
            cursorX = 0x110;
        }
        float jx = static_cast<float>(cursorX);
        jx -= 36.0f;
        jx += static_cast<float>(static_cast<int>(System.m_frameCounter) % 8);
        DrawCursor(static_cast<int>(jx),
            static_cast<int>(static_cast<float>(sel % 4 * 0x28 + 0x70)), alpha);
    }

    if (CmakeMcState(this) != 3) {
        DrawMcWin(-1, 0);
        if (CmakeMcState(this) == 1) {
            DrawMcWinMess(0x16, 0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeResultOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 5;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeResultCtrl()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    short& mode = cmakeState->m_mode;
    short& sel = cmakeState->m_select;
    short& resultDir = cmakeState->m_resultDir;
    short& frame = cmakeState->m_frame;
    unsigned short repeat = GetButtonRepeat(0);
    unsigned short down = GetButtonDown(0);

    if (mode != 1) {
        if (frame < 10) {
            frame = frame + 1;
        }
        return;
    }

    if ((repeat & 0x3) != 0) {
        sel = (sel == 0) ? 1 : 0;
    }

    if ((down & 0x100) != 0) {
        mode = 2;
        frame = 0;
        resultDir = (sel == 0) ? 1 : -1;
    } else if ((down & 0x200) != 0) {
        mode = 2;
        frame = 0;
        resultDir = -1;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeResultClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8016EA78
 * PAL Size: 2688b
 * EN Address: 0x8016DA00
 * EN Size: 2688b
 * JP Address: 0x80168EB0
 * JP Size: 2568b
 */
void CMenuPcs::CmakeResultDraw()
{
    CmakeMenuState* state = CmakeState(this);
    int frame = static_cast<int>(state->m_frame) - 1;
    float alpha;
    if (frame < 0) {
        frame = 0;
    }

    if (state->m_mode == 0) {
        alpha = static_cast<float>(0.1 * static_cast<double>(frame));
    } else if (state->m_mode == 1) {
        alpha = 1.0f;
    } else {
        alpha = static_cast<float>(-(0.1 * static_cast<double>(frame) - 1.0));
    }

    DrawWMFrame0(1, 1.0f);

    SetCmakeBlendMatColor(1.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD49));
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        MenuPcs.DrawRect(
            0,
            static_cast<float>(tileX), 24.0f, static_cast<float>(tileW), 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        tileX += tileW;
    }

    DrawCmakePreviewCharaAlpha(this, 1.0f);

    if ((CmakeState(this)->m_mode == 2) && (CmakeState(this)->m_resultDir < 0)) {
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    } else {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    if ((CmakeState(this)->m_mode == 2) && (CmakeState(this)->m_resultDir > 0)) {
        DrawCmakeTitle(6, 1.0f, alpha);
    } else {
        DrawCmakeTitle(6, alpha, 1.0f);
    }

    if ((CmakeState(this)->m_mode == 2) && (CmakeState(this)->m_resultDir < 0)) {
        int tribe = static_cast<int>(s_CmakeInfo.m_tribe);
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD40));
        MenuPcs.DrawRect(
            0,
            351.0f, 96.0f, 184.0f, 184.0f,
            static_cast<float>((tribe & 1) * 0xB8),
            static_cast<float>((tribe / 2) * 0xB8),
            1.0f, 1.0f, 0.0f);
    } else {
        int tribe = static_cast<int>(s_CmakeInfo.m_tribe);
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD40));
        MenuPcs.DrawRect(
            0,
            351.0f, 96.0f, 184.0f, 184.0f,
            static_cast<float>((tribe & 1) * 0xB8),
            static_cast<float>((tribe / 2) * 0xB8),
            1.0f, 1.0f, 0.0f);
    }

    int yesNoSel;
    if (CmakeState(this)->m_mode == 1) {
        yesNoSel = CmakeState(this)->m_select + 1;
    } else {
        yesNoSel = 0;
    }
    DrawCmakeYesNo(yesNoSel, alpha);

    if ((CmakeState(this)->m_mode == 2) && (CmakeState(this)->m_resultDir < 0)) {
        alpha = 1.0f;
    }

    CFont* labelFont = m_fonts[CMAKE_FONT_LABEL];
    labelFont->SetMargin(1.0f);
    labelFont->SetShadow(0);
    labelFont->SetScale(1.0f);
    labelFont->DrawInit();

    labelFont->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).color);

#ifndef VERSION_GCCJGC
    char tribeWithSlash[0x10];
#endif
#ifndef VERSION_GCCJGC
    float labelWidths[4];
#endif
    int labelY = 0x70;
    for (int i = 0; i < 4; i++) {
        const char* label = GetMenuStr(i + 0x2A);

#ifndef VERSION_GCCJGC
        labelWidths[i] = 232.0f + labelFont->GetWidth(label);
#endif
        labelFont->SetPosX(232.0f);
#ifdef VERSION_GCCJGC
        labelFont->SetPosY(static_cast<float>(labelY));
#else
        labelFont->SetPosY(static_cast<float>(labelY) - 4.0f);
#endif
        labelFont->Draw(label);
        labelY += 0x28;
    }

    CFont* valueFont = m_fonts[CMAKE_FONT_VALUE];
    valueFont->SetMargin(1.0f);
    valueFont->SetShadow(1);
    valueFont->SetScale(1.0f);
    valueFont->DrawInit();
    valueFont->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).color);
    valueFont->SetTlut(6);

    for (int i = 0; i < 4; i++) {
        const char* value = "";
        if (i == 0) {
            value = s_CmakeInfo.m_name;
        } else if (i == 1) {
            value = GetMenuStr(static_cast<int>(s_CmakeInfo.m_gender) + 0x11);
        } else if (i == 2) {
#ifdef VERSION_GCCJGC
            value = GetTribeStr(static_cast<int>(s_CmakeInfo.m_tribe));
#else
            strcpy(tribeWithSlash, GetTribeStr(static_cast<int>(s_CmakeInfo.m_tribe)));
            strcat(tribeWithSlash, "/");
            value = tribeWithSlash;
#endif
        } else {
            value = GetJobStr(static_cast<int>(s_CmakeInfo.m_job));
        }

#ifdef VERSION_GCCJGC
        float x = 336.0f;
#else
        float x = 8.0f + labelWidths[i];
#endif
        float y = static_cast<float>(0x70 + i * 0x28);
        float valueWidth = valueFont->GetWidth(value);
        valueFont->SetPosX(x);
#ifdef VERSION_GCCJGC
        valueFont->SetPosY(y);
#else
        valueFont->SetPosY(y - 4.0f);
#endif
        valueFont->Draw(value);

        if (i == 2) {
            int hairIndex = static_cast<int>(s_CmakeInfo.m_tribe) * 8;
            if (s_CmakeInfo.m_gender != 0) {
                hairIndex += 4;
            }

            const char* hair = GetHairStr(hairIndex + static_cast<int>(s_CmakeInfo.m_hair));

            valueFont->SetPosX(16.0f + (x + valueWidth));
#ifdef VERSION_GCCJGC
            valueFont->SetPosY(y);
#else
            valueFont->SetPosY(y - 4.0f);
#endif
            valueFont->Draw(hair);
        }
    }

    DrawInit();

}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeResultOpen1()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeResultCtrl1()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    short& mode = cmakeState->m_mode;
    short& frame = cmakeState->m_frame;
    unsigned short down = GetButtonDown(0);

    if (frame < 10) {
        frame = frame + 1;
        return;
    }

    if ((down & 0x300) != 0) {
        mode = 2;
        frame = 0;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeResultClose1()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8016E0D4
 * PAL Size: 2468b
 * EN Address: 0x8016D05C
 * EN Size: 2468b
 * JP Address: 0x80168584
 * JP Size: 2348b
 */
void CMenuPcs::CmakeResultDraw1()
{
    CmakeMenuState* state = CmakeState(this);
    int frame = static_cast<int>(state->m_frame) - 1;
    float alpha;
    if (frame < 0) {
        frame = 0;
    }

    if (state->m_mode == 0) {
        alpha = static_cast<float>(0.1 * static_cast<double>(frame));
    } else if (state->m_mode == 1) {
        alpha = 1.0f;
    } else {
        alpha = static_cast<float>(-(0.1 * static_cast<double>(frame) - 1.0));
    }
    float popupAlpha = (CmakeState(this)->m_mode == 0) ? 1.0f : alpha;

    DrawWMFrame0(1, 1.0f);

    SetCmakeBlendMatColor(1.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD48));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD49));
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        MenuPcs.DrawRect(
            0,
            static_cast<float>(tileX), 24.0f, static_cast<float>(tileW), 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        tileX += tileW;
    }

    DrawCmakePreviewCharaAlpha(this, 1.0f);

    if (CmakeState(this)->m_mode == 0) {
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    } else {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }
    DrawCmakeTitle(7, alpha, 1.0f);

    if (CmakeState(this)->m_mode == 0) {
        alpha = 1.0f;
    }
    {
        int tribe = static_cast<int>(s_CmakeInfo.m_tribe);
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD40));
        MenuPcs.DrawRect(
            0,
            351.0f, 96.0f, 184.0f, 184.0f,
            static_cast<float>((tribe & 1) * 0xB8),
            static_cast<float>((tribe / 2) * 0xB8),
            1.0f, 1.0f, 0.0f);
    }

    CFont* labelFont = m_fonts[CMAKE_FONT_LABEL];
    labelFont->SetMargin(1.0f);
    labelFont->SetShadow(0);
    labelFont->SetScale(1.0f);
    labelFont->DrawInit();

    labelFont->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).color);

#ifndef VERSION_GCCJGC
    char tribeWithSlash[0x10];
#endif
#ifndef VERSION_GCCJGC
    float labelWidths[4];
#endif
    for (int i = 0; i < 4; i++) {
        const char* txt = GetMenuStr(0x2A + i);

#ifndef VERSION_GCCJGC
        labelWidths[i] = 232.0f + static_cast<float>(labelFont->GetWidth(txt));
#endif
        labelFont->SetPosX(232.0f);
#ifdef VERSION_GCCJGC
        labelFont->SetPosY(0x70 + i * 0x28);
#else
        labelFont->SetPosY(0x70 + i * 0x28 - 4.0f);
#endif
        labelFont->Draw(txt);
    }

    CFont* valueFont = m_fonts[CMAKE_FONT_VALUE];
    valueFont->SetMargin(1.0f);
    valueFont->SetShadow(1);
    valueFont->SetScale(1.0f);
    valueFont->DrawInit();
    valueFont->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).color);
    valueFont->SetTlut(6);

    for (int i = 0; i < 4; i++) {
        const char* txt = "";

        if (i == 0) {
            txt = s_CmakeInfo.m_name;
        } else if (i == 1) {
            txt = GetMenuStr(s_CmakeInfo.m_gender + 0x11);
        } else if (i == 2) {
            txt = GetTribeStr(s_CmakeInfo.m_tribe);
#ifndef VERSION_GCCJGC
            strcpy(tribeWithSlash, txt);
            strcat(tribeWithSlash, "/");
            txt = tribeWithSlash;
#endif
        } else {
            txt = GetJobStr(s_CmakeInfo.m_job);
        }

#ifdef VERSION_GCCJGC
        float x = 336.0f;
#else
        float x = 8.0f + labelWidths[i];
#endif
        float y = static_cast<float>(0x70 + i * 0x28);
        float valueWidth = static_cast<float>(valueFont->GetWidth(txt));
        valueFont->SetPosX(x);
#ifdef VERSION_GCCJGC
        valueFont->SetPosY(y);
#else
        valueFont->SetPosY(y - 4.0f);
#endif
        valueFont->Draw(txt);

        if (i == 2) {
            int hairIndex = s_CmakeInfo.m_tribe * 8;
            if (s_CmakeInfo.m_gender != 0) {
                hairIndex += 4;
            }

            const char* hairTxt = GetHairStr(hairIndex + s_CmakeInfo.m_hair);

            valueFont->SetPosX(16.0f + (x + valueWidth));
#ifdef VERSION_GCCJGC
            valueFont->SetPosY(y);
#else
            valueFont->SetPosY(y - 4.0f);
#endif
            valueFont->Draw(hairTxt);
        }
    }

    DrawInit();

    if (CmakeState(this)->m_mode == 1) {
        int cursorX = static_cast<int>(196.0f + static_cast<float>(static_cast<int>(System.m_frameCounter) % 8));
        int cursorY = static_cast<int>(static_cast<float>(0x70 + CmakeState(this)->m_select * 0x28));
        DrawCursor(cursorX, cursorY, alpha);
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeVillageOpen()
{
    MenuU8(this, 0x16) = 1;
    createVillageMenu();
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016D940
 * PAL Size: 1940b
 * EN Address: 0x8016C8C8
 * EN Size: 1940b
 * JP Address: 0x80167DA8
 * JP Size: 2012b
 */
unsigned short CMenuPcs::CmakeVillageCtrl()
{
    CmakeMenuState* villageWork = CmakeVillageState(this);
    short& select = villageWork->m_select;
    short& row = villageWork->m_row;
    short& table = villageWork->m_table;
    short repeat;
    short down;
#ifndef VERSION_GCCJGC
    const char* name;
    char picked[8];
#endif

    down = Pad.GetButtonDown(0);
    repeat = Pad.GetButtonRepeat(0);

    if (repeat == 0) {
        return 0;
    }

    if ((repeat & 0x8) != 0) {
        if (villageWork->m_row != 0) {
            row -= 1;
        } else if (select >= 10) {
            row = 5;
        } else {
            row = 4;
        }
        Sound.PlaySe(1, 0x40, 0x7f, 0);
    } else if ((repeat & 0x4) != 0) {
        if (row < (select >= 10 ? 5 : 4)) {
            row += 1;
        } else {
            row = 0;
        }
        Sound.PlaySe(1, 0x40, 0x7f, 0);
    }

    if ((repeat & 0x1) != 0) {
        if (row >= 5) {
            Sound.PlaySe(4, 0x40, 0x7f, 0);
        } else {
            if (villageWork->m_select != 0) {
                select -= 1;
            } else {
                select = 0xB;
            }
            Sound.PlaySe(1, 0x40, 0x7f, 0);
        }
    } else if ((repeat & 0x2) != 0) {
        if (row >= 5) {
            Sound.PlaySe(4, 0x40, 0x7f, 0);
        } else {
            if (select < 0xB) {
                select += 1;
            } else {
                select = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7f, 0);
        }
    }

    if ((repeat & 0xF) == 0) {
        if ((down & 0x40) != 0) {
            table -= 1;
            if (table < 0) {
                table = CMAKE_NAME_PAGE_COUNT - 1;
            }
            Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
        } else if ((down & 0x20) != 0) {
            table += 1;
            if (table > CMAKE_NAME_PAGE_COUNT - 1) {
                table = 0;
            }
            Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
        } else if ((down & 0x1000) != 0) {
            select = 0xB;
            row = 5;
            Sound.PlaySe(2, 0x40, 0x7f, 0);
        } else if ((down & 0x100) != 0) {
#ifndef VERSION_GCCJGC
            short curTable;
            short curSelect;
            const char* rowText;
#endif
            short curRow = row;
            if (curRow >= 5) {
#ifdef VERSION_GCCJGC
            if (GetCharaCnt(s_CmakeInfo.m_name) == 0) {
#else
            unsigned int emptyLen = strlen(s_CmakeInfo.m_name);
            if ((emptyLen & (static_cast<int>(-emptyLen | emptyLen) >> 31)) == 0) {
#endif
                Sound.PlaySe(4, 0x40, 0x7f, 0);
                return 0;
            }

            int nameLen = strlen(s_CmakeInfo.m_name);
            int spaceCount = 0;
            for (; spaceCount < nameLen; spaceCount++) {
                if (s_CmakeInfo.m_name[spaceCount] != ' ') {
                    break;
                }
            }
            if (spaceCount == nameLen) {
                Sound.PlaySe(4, 0x40, 0x7f, 0);
                return 0;
            }

            char* townName = Game.m_gameWork.m_townName;
            memset(townName, 0, 17);
            strcpy(townName, s_CmakeInfo.m_name);
            Sound.PlaySe(2, 0x40, 0x7f, 0);
            villageWork->m_resultDir = 1;
            return 1;
        } else {
#ifdef VERSION_GCCJGC
            int ret = AddNameChara(1, select, curRow, table);
#else
            curTable = table;
            curSelect = select;
            memset(picked, 0, 3);
            rowText = s_NameEntryStr[curRow + curTable * 5];
            picked[0] = '\0';
            int rowLen = strlen(rowText);
            if (rowLen != 0) {
                int i = 0;
                int j = 0;
                for (; 0 < rowLen; rowLen = rowLen - 1) {
                    if (i == curSelect) {
                        picked[0] = rowText[j];
                        picked[1] = '\0';
                        break;
                    }
                    i = i + 1;
                    j = j + 1;
                }
            }
            unsigned int rawLen = strlen(s_CmakeInfo.m_name);
            int nameLen = rawLen & (static_cast<int>(-rawLen | rawLen) >> 31);
            int ret;
            if (nameLen >= 7) {
                ret = -1;
            } else {
                picked[0] = '\0';
                rowLen = strlen(rowText);
                if (rowLen != 0) {
                    int i = 0;
                    int j = 0;
                    for (; 0 < rowLen; rowLen = rowLen - 1) {
                        if (i == curSelect) {
                            picked[0] = rowText[j];
                            picked[1] = '\0';
                            break;
                        }
                        i = i + 1;
                        j = j + 1;
                    }
                }
                if (nameLen == 0) {
                    strcat(s_CmakeInfo.m_name, picked);
                    ret = 0;
                } else if (-((__cntlzw(strlen(rowText)) & 0x20) >> 5) == 0 && nameLen >= 7) {
                    ret = -1;
                } else {
                    strcat(s_CmakeInfo.m_name, picked);
                    ret = 0;
                }
            }
#endif
            if (ret != 0) {
                Sound.PlaySe(4, 0x40, 0x7f, 0);
            } else {
#ifdef VERSION_GCCJGC
                if (GetCharaCnt(s_CmakeInfo.m_name) >= 7) {
#else
                unsigned int finalLen = strlen(s_CmakeInfo.m_name);
                if (static_cast<int>(finalLen & (static_cast<int>(-finalLen | finalLen) >> 31)) >= 7) {
#endif
                    select = 0xB;
                    row = 5;
                }
                Sound.PlaySe(2, 0x40, 0x7f, 0);
            }
            }
        } else if ((down & 0x200) != 0) {
#ifdef VERSION_GCCJGC
            if (GetCharaCnt(s_CmakeInfo.m_name) != 0) {
                int bsRet = AddNameChara(0, select, row, table);
#else
            unsigned int bsLen0 = strlen(s_CmakeInfo.m_name);
            if ((bsLen0 & (static_cast<int>(-bsLen0 | bsLen0) >> 31)) != 0) {
                int bsRet;
                name = s_CmakeInfo.m_name;
                unsigned int bsLen1 = strlen(name);
                if ((bsLen1 & (static_cast<int>(-bsLen1 | bsLen1) >> 31)) == 0) {
                    bsRet = -1;
                } else {
                    int bsPos = strlen(s_CmakeInfo.m_name);
                    if (-((__cntlzw(strlen(name)) & 0x20) >> 5) == 0) {
                        s_CmakeInfo.m_name[bsPos - 1] = '\0';
                    } else {
                        s_CmakeInfo.m_name[bsPos - 2] = '\0';
                    }
                    bsRet = 0;
                }
#endif
                if (bsRet != 0) {
                    Sound.PlaySe(4, 0x40, 0x7f, 0);
                } else {
                    Sound.PlaySe(3, 0x40, 0x7f, 0);
                }
            } else {
                Sound.PlaySe(4, 0x40, 0x7f, 0);
            }
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeVillageClose()
{
    MenuU8(this, 0x16) = 0;
    destroyVillageMenu();
}

/*
 * --INFO--
 * PAL Address: 0x8016D25C
 * PAL Size: 1764b
 * EN Address: 0x8016C1E4
 * EN Size: 1764b
 * JP Address: 0x80167560
 * JP Size: 2120b
 */
void CMenuPcs::CmakeVillageDraw()
{
    CmakeMenuState* villageWork = CmakeVillageState(this);
    int frame = static_cast<int>(villageWork->m_frame) - 1;
    float alpha;

    if (frame < 0) {
        frame = 0;
    }

    if (villageWork->m_mode == 0) {
        alpha = static_cast<float>(0.1 * static_cast<double>(frame));
    } else if (villageWork->m_mode == 1) {
        alpha = 1.0f;
    } else {
        alpha = static_cast<float>(-(0.1 * static_cast<double>(frame) - 1.0));
    }

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 192.0f, 56.0f, 416.0f, 264.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    DrawCmakeTitle(0, 1.0f, alpha);

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    float panelW = 328.0f;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(-(panelW / 2.0 - 400.0))), 288.0f, panelW, 56.0f,
        0.0f, 368.0f, 1.0f, 1.0f, 0.0f);

    SetCmakeBlendMatColor(alpha);
#ifdef VERSION_GCCJGC
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 184.0f, 216.0f, 40.0f, 40.0f,
        256.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    double crestRightX = 576.0;
    int rightX = static_cast<int>(crestRightX);
    MenuPcs.DrawRect(
        0, static_cast<float>(rightX), 216.0f, 40.0f, 40.0f,
        256.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD29 : CMAKE_TEX_WORLD29));
    MenuPcs.DrawRect(
        0, 192.0f, 224.0f, 24.0f, 24.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        0, static_cast<float>(rightX + 8), 224.0f, 24.0f, 24.0f,
        24.0f, 0.0f, 1.0f, 1.0f, 0.0f);
#else
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x68 : 0x41));
    MenuPcs.DrawRect(
        0, 184.0f, 216.0f, 48.0f, 48.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    double crestRightX = 568.0;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(crestRightX)), 216.0f, 48.0f, 48.0f,
        48.0f, 0.0f, 1.0f, 1.0f, 0.0f);
#endif

    if (villageWork->m_mode == 1 && villageWork->m_row < 5) {
        short sel = villageWork->m_select;
        int cursorX = (villageWork->m_row < 5) ? 0xE5 : 0xE5;
        int cursorY = villageWork->m_row * 0x20 + 0x63;
        cursorX = static_cast<int>(
            26.9f * static_cast<float>(sel) + static_cast<float>(cursorX));
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? CMAKE_TEX_VILLAGE_WORLD44 : CMAKE_TEX_WORLD44));
        MenuPcs.DrawRect(
            0,
            static_cast<float>(cursorX), static_cast<float>(cursorY), 48.0f, 48.0f,
            128.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    short table = villageWork->m_table;
    CFont* font = GetCmakeKeyboardFont(this);
    font->SetShadow(0);
    font->SetScale(1.0f);
    font->DrawInit();
    font->renderFlags.fixedWidth = 1;
    font->SetMargin(4.9f);
    SetCmakeFontColor(font, alpha);

    const char* rowText;
    int tableBase = table * 5;
    int i;
    int y;
#ifdef VERSION_GCCJGC
    for (i = 0, y = 0x70; i < 5; i++, y += 0x20) {
#else
    for (i = 0, y = 0x6C; i < 5; i++, y += 0x20) {
#endif
        rowText = s_NameEntryStr[tableBase + i];
        font->SetPosX(240.0f);
        font->SetPosY(static_cast<float>(y));
        font->Draw(rowText);
    }

    font->renderFlags.fixedWidth = 0;

    DrawInit();
    if (villageWork->m_mode == 1 && villageWork->m_row < 5) {
        int cursorLeft = (villageWork->m_select == 0) ? 0xC8 : 0xC8;
        cursorLeft = static_cast<int>(26.9f * static_cast<float>(villageWork->m_select) +
            static_cast<float>(cursorLeft));
        cursorLeft += static_cast<int>(System.m_frameCounter) % 8;
        DrawCursor(cursorLeft, villageWork->m_row * 0x20 + 0x70, 1.0f);
    }

    int showNameCursor = static_cast<int>(
        static_cast<unsigned int>(__cntlzw(static_cast<unsigned int>(1 - villageWork->m_mode))) >> 5);
    if (villageWork->m_row >= 5) {
        showNameCursor = 0;
    }
#ifdef VERSION_GCCJGC
    if (GetCharaCnt(s_CmakeInfo.m_name) >= 7) {
#else
    unsigned int nameLen = strlen(s_CmakeInfo.m_name);
    if (7 <= static_cast<int>(nameLen & (static_cast<int>(-nameLen | nameLen) >> 31))) {
#endif
        showNameCursor = 0;
    }
    DrawCmakeName(1, showNameCursor, s_CmakeInfo.m_name, alpha);
    DrawCmakeDecision((villageWork->m_row >= 5) ? 1 : 0, alpha);
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::SetSingMakeChara()
{
    int slot = static_cast<int>(CmakeSlot(this));
    ChgModel(slot, MenuS16(this, 0x860), MenuS16(this, 0x862), MenuS16(this, 0x864));
    SetAnim(slot);
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void CMenuPcs::createVillageMenu()
{
    if (CmakeResult(this) == 0) {
        MenuU8(this, 0x16) = 1;
        calcVillageMenu();
    }
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016D19C
 * PAL Size: 192b
 * EN Address: 0x8016C124
 * EN Size: 192b
 * JP Address: 0x801674A0
 * JP Size: 192b
 */
void CMenuPcs::destroyVillageMenu()
{
    if (CmakeResult(this) != 0) {
        if (Game.m_gameWork.m_menuStageMode == 0) {
            CFont*& font = m_fonts[CMAKE_FONT_VILLAGE];
            if (font != 0) {
                ReleaseRefObject(font);
                font = 0;
            }
        }

        freeTexture(8, 1, CMAKE_TEX_VILLAGE_CRYSTAL, CMAKE_VILLAGE_TEXTURE_COUNT);

        void*& villageWork = CmakeVillageWork(this);
        if (villageWork != nullptr) {
            operator delete(villageWork);
            villageWork = nullptr;
        }

        CmakeResult(this) = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8016CF58
 * PAL Size: 580b
 * EN Address: 0x8016BEE0
 * EN Size: 580b
 * JP Address: 0x80167278
 * JP Size: 552b
 */
void CMenuPcs::calcVillageMenu()
{
    if (MenuU8(this, 0x16) != 0 && CmakeResult(this) == 0) {
        if (CmakeResult(this) == 0 && MenuU8(this, 0x16) != 0) {
            if (Game.m_gameWork.m_menuStageMode == 0) {
#ifdef VERSION_GCCJGC
                loadFont(2, const_cast<char*>(s_cmakeSubfontPath), 4, -1);
#else
                char path[128];
                sprintf(path, s_menuSubfontPathFmt, Game.GetLangString());
                loadFont(2, path, 4, -1);
#endif
            }

            loadTexture(PTR_s_world2, 8, 1, s_cmakeWorldTextureTable, CMAKE_TEX_VILLAGE_CRYSTAL, CMAKE_VILLAGE_TEXTURE_COUNT, 3);

            CMemory::CStage* stage = MenuPcs.m_menuStage;
            void*& villageWork = CmakeVillageWork(this);
#ifdef VERSION_GCCJGC
            const int allocationLine = 0xC17;
#elif defined(VERSION_GCCE01)
            const int allocationLine = 0xCB1;
#else
            const int allocationLine = 0xCB3;
#endif
            villageWork = operator new(0x48, stage, const_cast<char*>(s_cmake_cpp), allocationLine);
            memset(villageWork, 0, 0x48);
            LoadCmakeVillageName();
            CmakeResult(this) = 1;
        }
    }

    short active = CmakeResult(this);
    if (active != 0) {
        if (MenuU8(this, 0x16) == 0 && active != 0) {
            if (active != 0) {
                if (Game.m_gameWork.m_menuStageMode == 0) {
                    CFont*& font = m_fonts[CMAKE_FONT_VILLAGE];
                    if (font != 0) {
                        ReleaseRefObject(font);
                        font = 0;
                    }
                }

                freeTexture(8, 1, CMAKE_TEX_VILLAGE_CRYSTAL, CMAKE_VILLAGE_TEXTURE_COUNT);
                void*& villageWork = CmakeVillageWork(this);
                if (villageWork != nullptr) {
                    operator delete(villageWork);
                    villageWork = nullptr;
                }
                CmakeResult(this) = 0;
            }
        } else {
            CmakeMenuState* villageWork = CmakeVillageState(this);
            unsigned short result = 0;
            short& mode = villageWork->m_mode;
            short& frame = villageWork->m_frame;

            if (mode == 0) {
                if (frame >= 10) {
                    result = 1;
                } else {
                    frame = frame + 1;
                    result = 0;
                }
            } else if (mode == 1) {
                result = CmakeVillageCtrl();
            } else if (frame >= 10) {
                result = 1;
            } else {
                frame = frame + 1;
                result = 0;
            }

            villageWork->m_resultFlag = static_cast<short>(result);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8016cecc
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawVillageMenu()
{
    if (CmakeResult(this) != 0) {
        CmakeMenuState* villageWork = CmakeVillageState(this);
        CmakeVillageDraw();
        if (villageWork->m_resultFlag != 0) {
            short& mode = villageWork->m_mode;
            if (mode < 2) {
                mode = mode + 1;
            } else {
                MenuU8(this, 0x16) = 0;
                CallWorldParam(10, 0, 0);
            }
            villageWork->m_frame = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8016cd3c
 * PAL Size: 400b
 * EN Address: 0x8016BCC4
 * EN Size: 400b
 * JP Address: 0x80167050
 * JP Size: 412b
 */
void CMenuPcs::CalcSingleCMakeChara()
{
    int slot = static_cast<int>(CmakeSlot(this));
    WmWorldObjInfo* modelWork = m_wm.m_worldObjData + slot + 0x20;

    if (GetCmakeCharaHandle(this, slot)->m_model == nullptr ||
        GetCmakeCharaHandle(this, slot)->m_model->m_texSet == nullptr) {
        modelWork->m_active = 0;
        return;
    }

    WmCharaModelInfo* animWork = m_wm.m_charaModelData + slot;
    if (animWork->m_modelChanged == 1) {
        modelWork->m_transform.m_rotation.y = 0.2617994f;
        SetAnim(CmakeSlot(this));
        animWork->m_modelChanged = 0;
    }

    modelWork->m_active = 1;
    if (GetCmakeCharaHandle(this, slot)->m_charaKind != 3) {
        Mtx scaleMtx;
        Mtx rotXMtx;
        Mtx rotYMtx;

        modelWork->m_transform.m_position.x = 0.0f;
        modelWork->m_transform.m_position.y = -6.0f;
        modelWork->m_transform.m_position.z = 0.0f;
        modelWork->m_transform.m_scale.x = 0.83f;
        modelWork->m_transform.m_scale.y = 0.83f;
        modelWork->m_transform.m_scale.z = 0.83f;

        PSMTXScale(scaleMtx,
            modelWork->m_transform.m_scale.x,
            modelWork->m_transform.m_scale.y,
            modelWork->m_transform.m_scale.z);
        PSMTXRotRad(rotXMtx, 'x', modelWork->m_transform.m_rotation.x);
        PSMTXRotRad(rotYMtx, 'y', modelWork->m_transform.m_rotation.y);
        PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
        rotXMtx[0][3] = modelWork->m_transform.m_position.x;
        rotXMtx[1][3] = modelWork->m_transform.m_position.y;
        rotXMtx[2][3] = modelWork->m_transform.m_position.z;
        PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);
        GetCmakeCharaHandle(this, slot)->m_model->SetMatrix(scaleMtx);
        GetCmakeCharaHandle(this, slot)->m_model->CalcMatrix();
        GetCmakeCharaHandle(this, slot)->m_model->CalcSkin();
        PCAnimCtrl();
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawSingleCMakeChara(float alpha)
{
    CalcSingleCMakeChara();
    if (alpha <= 0.0f) {
        return;
    }

    DrawCmakePreviewCharaAlpha(this, alpha);
}
