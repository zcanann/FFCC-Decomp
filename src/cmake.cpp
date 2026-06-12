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

extern "C" char* strcat(char*, const char*);

extern "C" int gCmakePreviousStep;
extern "C" char s_menuSubfontPathFmt[];
static const char s_cmake_cpp[] = "cmake.cpp";

struct CmakeInfo {
    char m_name[0x12];
    signed char m_gender;
    signed char m_tribe;
    signed char m_hair;
    signed char m_job;
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

struct CFontRenderFlagBits
{
    signed char shadow : 1;
    signed char zCompare : 1;
    signed char zUpdate : 1;
    signed char fixedWidth : 1;
    signed char snapPosition : 1;
    signed char pad : 3;
};

static inline CFontRenderFlagBits& GetRenderFlagBits(unsigned char& flags)
{
    return reinterpret_cast<CFontRenderFlagBits&>(flags);
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

static unsigned short GetCmakePadDown()
{
    unsigned char noPad = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
    int held;
    if (noPad) {
        held = 0;
    } else {
        int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
        held = Pad.GetPadInputs()[padIndex].buttonDown[0];
    }
    return static_cast<unsigned short>(held);
}

static unsigned short GetCmakePadRepeat()
{
    unsigned char noPad = (Pad.m_debugPadLock != 0) || (Pad.m_debugPadPort != -1);
    int held;
    if (noPad) {
        held = 0;
    } else {
        int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
        held = Pad.GetPadInputs()[padIndex].repeatButton;
    }
    return static_cast<unsigned short>(held);
}

static inline void DrawCmakePreviewCharaAlpha(CMenuPcs* menu, float alpha)
{
    int handleIndex = static_cast<int>(CmakeSlot(menu)) + 0x20;
    int modelBlock = MenuS32(menu, 0x814);
    if (*reinterpret_cast<int*>(modelBlock + handleIndex * 0x50) == 0) {
        return;
    }

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
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x32));
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
    int handleIndex = static_cast<int>(CmakeSlot(menu)) + 0x20;
    int modelBlock = MenuS32(menu, 0x814);
    if (*reinterpret_cast<int*>(modelBlock + handleIndex * 0x50) == 0) {
        return;
    }

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
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x32));
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(menu) != 0) ? 0x61 : 0x3A));
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
    {8, (char*)s_world51},
};

static CmakeInfo s_CmakeInfo;
static char s_CmakeVillageName[0x11];

static inline char* GetCmakeNameBuffer()
{
    return s_CmakeInfo.m_name;
}

static void LoadCmakeVillageName()
{
    strcpy(s_CmakeInfo.m_name, Game.m_gameWork.m_townName);
}

static void StoreCmakeVillageName()
{
    memset(Game.m_gameWork.m_townName, 0, 17);
    strcpy(Game.m_gameWork.m_townName, s_CmakeInfo.m_name);
}

static bool IsCmakeNameBlank(const char* name)
{
    if (name[0] == '\0') {
        return true;
    }

    for (const char* it = name; *it != '\0'; ++it) {
        if (*it != ' ') {
            return false;
        }
    }

    return true;
}

static int IsDuplicateCmakeName(CMenuPcs* menu, const char* name)
{
    const char* nm = name;
    int slot = 0;
    int found = false;
    unsigned char* base = reinterpret_cast<unsigned char*>(&Game);
    for (; slot < 8; ++slot) {
        if (slot == CmakeSlot(menu)) {
            continue;
        }
        if (*reinterpret_cast<int*>(base + slot * 0xC30 + 0x1794) == 0) {
            continue;
        }
        if (*(base + slot * 0xC30 + 0x1F96) == 1) {
            continue;
        }
        if (strcmp(nm, reinterpret_cast<char*>(base + slot * 0xC30 + 0x17BA)) == 0) {
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
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void CMenuPcs::DrawSingleCMakeChara(float alpha)
{
    CalcSingleCMakeChara();
    if (alpha <= 0.0f) {
        return;
    }

    DrawCmakePreviewCharaAlpha(this, alpha);
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016cd3c
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CalcSingleCMakeChara()
{
    int slot = static_cast<int>(CmakeSlot(this));
    unsigned char* modelWork = reinterpret_cast<unsigned char*>(MenuS32(this, 0x814) + slot * 0x50 + 0xA00);

    if (GetCmakeCharaHandle(this, slot)->m_model == nullptr ||
        *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(GetCmakeCharaHandle(this, slot)->m_model) + 0xB0) == 0) {
        *reinterpret_cast<int*>(modelWork + 0x00) = 0;
        return;
    }

    unsigned char* animWork = reinterpret_cast<unsigned char*>(MenuS32(this, 0x824) + slot * 0x34);
    if (animWork[0x0C] == 1) {
        *reinterpret_cast<float*>(modelWork + 0x2C) = 0.2617994f;
        SetAnim(CmakeSlot(this));
        animWork[0x0C] = 0;
    }

    *reinterpret_cast<int*>(modelWork + 0x00) = 1;
    if (GetCmakeCharaHandle(this, slot)->m_charaKind != 3) {
        Mtx scaleMtx;
        Mtx rotXMtx;
        Mtx rotYMtx;
        float posY = -6.0f;
        float posXZ = 0.0f;
        float scale = 0.83f;

        *reinterpret_cast<float*>(modelWork + 0x1C) = posXZ;
        *reinterpret_cast<float*>(modelWork + 0x20) = posY;
        *reinterpret_cast<float*>(modelWork + 0x24) = posXZ;
        *reinterpret_cast<float*>(modelWork + 0x34) = scale;
        *reinterpret_cast<float*>(modelWork + 0x38) = scale;
        *reinterpret_cast<float*>(modelWork + 0x3C) = scale;

        PSMTXScale(scaleMtx,
            *reinterpret_cast<float*>(modelWork + 0x34),
            *reinterpret_cast<float*>(modelWork + 0x38),
            *reinterpret_cast<float*>(modelWork + 0x3C));
        PSMTXRotRad(rotXMtx, 'x', *reinterpret_cast<float*>(modelWork + 0x28));
        PSMTXRotRad(rotYMtx, 'y', *reinterpret_cast<float*>(modelWork + 0x2C));
        PSMTXConcat(rotXMtx, rotYMtx, rotXMtx);
        rotXMtx[0][3] = *reinterpret_cast<float*>(modelWork + 0x1C);
        rotXMtx[1][3] = *reinterpret_cast<float*>(modelWork + 0x20);
        rotXMtx[2][3] = *reinterpret_cast<float*>(modelWork + 0x24);
        PSMTXConcat(rotXMtx, scaleMtx, scaleMtx);
        GetCmakeCharaHandle(this, slot)->m_model->SetMatrix(scaleMtx);
        GetCmakeCharaHandle(this, slot)->m_model->CalcMatrix();
        GetCmakeCharaHandle(this, slot)->m_model->CalcSkin();
        PCAnimCtrl();
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
 * PAL Address: 0x8016cf58
 * PAL Size: 580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calcVillageMenu()
{
    if (MenuU8(this, 0x16) != 0 && CmakeResult(this) == 0) {
        if (CmakeResult(this) == 0 && MenuU8(this, 0x16) != 0) {
            if (Game.m_gameWork.m_menuStageMode == 0) {
                char path[128];
                const char* language = Game.GetLangString();
                sprintf(path, s_menuSubfontPathFmt, language);
                loadFont(2, path, 4, -1);
            }

            loadTexture(PTR_s_world2, 8, 1, s_cmakeWorldTextureTable, 0x60, 9, 3);

            CMemory::CStage* stage = MenuPcs.m_menuStage;
            void*& villageWork = CmakeVillageWork(this);
            villageWork = operator new(0x48, stage, const_cast<char*>(s_cmake_cpp), 0xCB3);
            memset(villageWork, 0, 0x48);
            LoadCmakeVillageName();
            CmakeResult(this) = 1;
        }
    }

    short active = CmakeResult(this);
    if (active != 0) {
        if (MenuU8(this, 0x16) == 0) {
            if (active != 0) {
              if (active != 0) {
                if (Game.m_gameWork.m_menuStageMode == 0) {
                    CFont*& font = m_fonts[CMAKE_FONT_VILLAGE];
                    if (font != 0) {
                        ReleaseRefObject(font);
                        font = 0;
                    }
                }

                freeTexture(8, 1, 0x60, 9);
                void*& villageWork = CmakeVillageWork(this);
                if (villageWork != nullptr) {
                    operator delete(villageWork);
                    villageWork = nullptr;
                }
                CmakeResult(this) = 0;
              }
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
 * PAL Address: 0x8016d19c
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

        freeTexture(8, 1, 0x60, 9);

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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void CMenuPcs::SetSingMakeChara()
{
    int slot = static_cast<int>(CmakeSlot(this));
    ChgModel(slot, MenuS16(this, 0x860), MenuS16(this, 0x862), MenuS16(this, 0x864));
    SetAnim(slot);
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016d25c
 * PAL Size: 1764b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, 192.0f, 56.0f, 416.0f, 264.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    DrawCmakeTitle(0, 1.0f, alpha);

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
    float panelW = 328.0f;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(-(panelW / 2.0 - 400.0))), 288.0f, panelW, 56.0f,
        0.0f, 368.0f, 1.0f, 1.0f, 0.0f);

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x68 : 0x41));
    MenuPcs.DrawRect(
        0, 184.0f, 216.0f, 48.0f, 48.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    double crestRightX = 568.0;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(crestRightX)), 216.0f, 48.0f, 48.0f,
        48.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    if (villageWork->m_mode == 1 && villageWork->m_row < 5) {
        short sel = villageWork->m_select;
        int cursorBase = (villageWork->m_row < 5) ? 0xE5 : 0xE5;
        int cursorY = villageWork->m_row * 0x20 + 0x63;
        int cursorX = static_cast<int>(
            26.9f * static_cast<float>(sel) + static_cast<float>(cursorBase));
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 100 : 0x3D));
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
    GetRenderFlagBits(font->renderFlags).fixedWidth = 1;
    font->SetMargin(4.9f);
    SetCmakeFontColor(font, alpha);

    const char* rowText;
    int tableBase = table * 5;
    int i;
    int y;
    for (i = 0, y = 0x6C; i < 5; i++, y += 0x20) {
        rowText = s_NameEntryStr[tableBase + i];
        font->SetPosX(240.0f);
        font->SetPosY(static_cast<float>(y));
        font->Draw(rowText);
    }

    GetRenderFlagBits(font->renderFlags).fixedWidth = 0;

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
    unsigned int nameLen = strlen(s_CmakeInfo.m_name);
    if (7 <= static_cast<int>(nameLen & (static_cast<int>(-nameLen | nameLen) >> 31))) {
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeVillageClose()
{
    MenuU8(this, 0x16) = 0;
    destroyVillageMenu();
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016d940
 * PAL Size: 1940b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned short CMenuPcs::CmakeVillageCtrl()
{
    CmakeMenuState* villageWork = CmakeVillageState(this);
    short& select = villageWork->m_select;
    short& row = villageWork->m_row;
    short& table = villageWork->m_table;
    short repeat;
    short down;
    char picked[8];

    bool padBusy = false;
    int padLock = Pad.m_debugPadLock;
    if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
        padBusy = true;
    }
    {
        int held;
        if (padBusy) {
            held = 0;
        } else {
            int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
            held = Pad.GetPadInputs()[padIndex].buttonDown[0];
        }
        down = static_cast<short>(static_cast<unsigned short>(held));
    }

    padBusy = false;
    if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
        padBusy = true;
    }
    {
        int held;
        if (padBusy) {
            held = 0;
        } else {
            int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
            held = Pad.GetPadInputs()[padIndex].repeatButton;
        }
        repeat = static_cast<short>(static_cast<unsigned short>(held));
    }

    if (repeat == 0) {
        return 0;
    }

    if ((repeat & 0x8) != 0) {
        if (villageWork->m_row != 0) {
            row = static_cast<short>(row - 1);
        } else if (select >= 10) {
            row = 5;
        } else {
            row = 4;
        }
        Sound.PlaySe(1, 0x40, 0x7f, 0);
    } else if ((repeat & 0x4) != 0) {
        if (row < (select >= 10 ? 5 : 4)) {
            row = static_cast<short>(row + 1);
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
                select = static_cast<short>(select - 1);
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
                select = static_cast<short>(select + 1);
            } else {
                select = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7f, 0);
        }
    }

    if ((repeat & 0xF) == 0) {
        if ((down & 0x40) != 0) {
            table = static_cast<short>(table - 1);
            if (table < 0) {
                table = 2;
            }
            Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
        } else if ((down & 0x20) != 0) {
            table = static_cast<short>(table + 1);
            if (table > 2) {
                table = 0;
            }
            Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
        } else if ((down & 0x1000) != 0) {
            select = 0xB;
            row = 5;
            Sound.PlaySe(2, 0x40, 0x7f, 0);
        } else if ((down & 0x100) != 0) {
            short curTable;
            short curSelect;
            short curRow = row;
            if (curRow >= 5) {
            unsigned int emptyLen = strlen(s_CmakeInfo.m_name);
            if ((emptyLen & (static_cast<int>(-emptyLen | emptyLen) >> 31)) == 0) {
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

            StoreCmakeVillageName();
            Sound.PlaySe(2, 0x40, 0x7f, 0);
            villageWork->m_resultDir = 1;
            return 1;
        } else {
            curSelect = select;
            curTable = table;
            memset(picked, 0, 3);
            picked[0] = '\0';
            const char* rowText = s_NameEntryStr[curRow + curTable * 5];
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
            if (ret != 0) {
                Sound.PlaySe(4, 0x40, 0x7f, 0);
            } else {
                unsigned int finalLen = strlen(s_CmakeInfo.m_name);
                if (static_cast<int>(finalLen & (static_cast<int>(-finalLen | finalLen) >> 31)) >= 7) {
                    select = 0xB;
                    row = 5;
                }
                Sound.PlaySe(2, 0x40, 0x7f, 0);
            }
            }
        } else if ((down & 0x200) != 0) {
            unsigned int bsLen0 = strlen(s_CmakeInfo.m_name);
            if ((bsLen0 & (static_cast<int>(-bsLen0 | bsLen0) >> 31)) != 0) {
                const char* name = s_CmakeInfo.m_name;
                int bsRet;
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeVillageOpen()
{
    MenuU8(this, 0x16) = 1;
    createVillageMenu();
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016e0d4
 * PAL Size: 2468b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
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
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    } else {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
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
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x31));
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

    CColor color(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha));
    labelFont->SetColor(color.color);

    float labelWidths[4];
    for (int i = 0; i < 4; i++) {
        const char* txt = GetMenuStr(0x2A + i);

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
    CColor valueColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha));
    valueFont->SetColor(valueColor.color);
    valueFont->SetTlut(6);

    char tribeWithSlash[0x10];
    for (int i = 0; i < 4; i++) {
        const char* txt = "";

        if (i == 0) {
            txt = s_CmakeInfo.m_name;
        } else if (i == 1) {
            txt = GetMenuStr(s_CmakeInfo.m_gender + 0x11);
        } else if (i == 2) {
            txt = GetTribeStr(s_CmakeInfo.m_tribe);
            strcpy(tribeWithSlash, txt);
            strcat(tribeWithSlash, "/");
            txt = tribeWithSlash;
        } else {
            txt = GetJobStr(s_CmakeInfo.m_job);
        }

        float x = 8.0f + labelWidths[i];
        float y = static_cast<float>(0x70 + i * 0x28);
        float valueWidth = static_cast<float>(valueFont->GetWidth(txt));
        valueFont->SetPosX(x);
        valueFont->SetPosY(y - 4.0f);
        valueFont->Draw(txt);

        if (i == 2) {
            int hairIndex = s_CmakeInfo.m_tribe * 8;
            if (s_CmakeInfo.m_gender != 0) {
                hairIndex += 4;
            }

            const char* hairTxt = GetHairStr(hairIndex + s_CmakeInfo.m_hair);

            valueFont->SetPosX(16.0f + (x + valueWidth));
            valueFont->SetPosY(y - 4.0f);
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
void CMenuPcs::CmakeResultClose1()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeResultCtrl1()
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeResultOpen1()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016ea78
 * PAL Size: 2688b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
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
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    } else {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
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
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x31));
        MenuPcs.DrawRect(
            0,
            351.0f, 96.0f, 184.0f, 184.0f,
            static_cast<float>((tribe & 1) * 0xB8),
            static_cast<float>((tribe / 2) * 0xB8),
            1.0f, 1.0f, 0.0f);
    } else {
        int tribe = static_cast<int>(s_CmakeInfo.m_tribe);
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x31));
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

    CColor color(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha));
    labelFont->SetColor(color.color);

    float labelWidths[4];
    int labelY = 0x70;
    for (int i = 0; i < 4; i++) {
        const char* label = GetMenuStr(i + 0x2A);

        labelWidths[i] = 232.0f + labelFont->GetWidth(label);
        labelFont->SetPosX(232.0f);
        labelFont->SetPosY(static_cast<float>(labelY) - 4.0f);
        labelFont->Draw(label);
        labelY += 0x28;
    }

    CFont* valueFont = m_fonts[CMAKE_FONT_VALUE];
    valueFont->SetMargin(1.0f);
    valueFont->SetShadow(1);
    valueFont->SetScale(1.0f);
    valueFont->DrawInit();
    CColor valueColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha));
    valueFont->SetColor(valueColor.color);
    valueFont->SetTlut(6);

    char tribeWithSlash[0x10];
    for (int i = 0; i < 4; i++) {
        const char* value = "";
        if (i == 0) {
            value = s_CmakeInfo.m_name;
        } else if (i == 1) {
            value = GetMenuStr(static_cast<int>(s_CmakeInfo.m_gender) + 0x11);
        } else if (i == 2) {
            strcpy(tribeWithSlash, GetTribeStr(static_cast<int>(s_CmakeInfo.m_tribe)));
            strcat(tribeWithSlash, "/");
            value = tribeWithSlash;
        } else {
            value = GetJobStr(static_cast<int>(s_CmakeInfo.m_job));
        }

        float x = 8.0f + labelWidths[i];
        float y = static_cast<float>(0x70 + i * 0x28);
        float valueWidth = valueFont->GetWidth(value);
        valueFont->SetPosX(x);
        valueFont->SetPosY(y - 4.0f);
        valueFont->Draw(value);

        if (i == 2) {
            int hairIndex = static_cast<int>(s_CmakeInfo.m_tribe) * 8;
            if (s_CmakeInfo.m_gender != 0) {
                hairIndex += 4;
            }

            const char* hair = GetHairStr(hairIndex + static_cast<int>(s_CmakeInfo.m_hair));

            valueFont->SetPosX(16.0f + (x + valueWidth));
            valueFont->SetPosY(y - 4.0f);
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeResultClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeResultCtrl()
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeResultOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 5;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016f4f8
 * PAL Size: 1600b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
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

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor panelColor;
    panelColor.r = 0xFF;
    panelColor.g = 0xFF;
    panelColor.b = 0xFF;
    panelColor.a = static_cast<unsigned char>(static_cast<int>(255.0f * alpha));
    GXSetChanMatColor(GX_COLOR0A0, panelColor);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
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

    SetCmakeFontColor(font, alpha);

    for (int i = 0; i < 8; ++i) {
        const char* txt = GetJobStr(i);
        int x = (i < 4) ? 0x110 : 0x1A8;
        int row = i % 4;
        font->SetPosX(x);
        font->SetPosY(static_cast<float>(0x70 + row * 0x28) - 4.0f);
        font->Draw(txt);
    }

    if (CmakeState(this)->m_mode == 1) {
        int sel = CmakeState(this)->m_select;
        int cursorX = (sel < 4) ? 0x110 : 0x1A8;
        int cursorFrame = static_cast<int>(System.m_frameCounter) % 8;
        DrawCursor(static_cast<int>((static_cast<float>(cursorX) - 36.0f) + static_cast<float>(cursorFrame)),
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeJobClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016fb38
 * PAL Size: 1156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CmakeJobCtrl()
{
    short repeat;
    short down;

    bool padBusy = false;
    int padLock = Pad.m_debugPadLock;
    if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
        padBusy = true;
    }
    {
        int held;
        if (padBusy) {
            held = 0;
        } else {
            int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
            held = Pad.GetPadInputs()[padIndex].buttonDown[0];
        }
        down = static_cast<short>(static_cast<unsigned short>(held));
    }

    padBusy = false;
    if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
        padBusy = true;
    }
    {
        int held;
        if (padBusy) {
            held = 0;
        } else {
            int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
            held = Pad.GetPadInputs()[padIndex].repeatButton;
        }
        repeat = static_cast<short>(static_cast<unsigned short>(held));
    }

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
                CmakeState(this)->m_select = static_cast<short>(CmakeState(this)->m_select - 1);
            } else {
                CmakeState(this)->m_select = static_cast<short>(CmakeState(this)->m_select + 3);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            if ((CmakeState(this)->m_select % 4) < 3) {
                CmakeState(this)->m_select = static_cast<short>(CmakeState(this)->m_select + 1);
            } else {
                CmakeState(this)->m_select = static_cast<short>(CmakeState(this)->m_select - 3);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0x3) != 0) {
            if (CmakeState(this)->m_select <= 3) {
                CmakeState(this)->m_select = static_cast<short>(CmakeState(this)->m_select + 4);
            } else {
                CmakeState(this)->m_select = static_cast<short>(CmakeState(this)->m_select - 4);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0xF) == 0) {
            if ((down & 0x100) != 0) {
                unsigned char* group = reinterpret_cast<unsigned char*>(&Game);
                int slot = 0;
                for (int groupCount = 2; groupCount != 0; groupCount--) {
                    for (int inner = 0; inner < 4; ++inner) {
                        if ((slot != static_cast<int>(CmakeSlot(this))) &&
                            (*reinterpret_cast<int*>(group + 0x1794) != 0) &&
                            (*(group + 0x1F96) != 1) &&
                            (*reinterpret_cast<int*>(group + 0x179C) == static_cast<int>(CmakeState(this)->m_select))) {
                            goto found;
                        }
                        group += 0xC30;
                        ++slot;
                    }
                }
            found:

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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeJobOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 4;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8016ffbc
 * PAL Size: 2292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8,
        608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
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
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x31));
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

    for (int i = 0; i < 4; i++) {
        const char* txt = GetTribeStr(i);
        tribeFont->SetPosX(264.0f);
        tribeFont->SetPosY(0x88 + i * 0x1C - 4.0f);
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

    for (int i = 0; i < 4; i++) {
        const char* txt = GetHairStr(hairBase + i);
        hairFont->SetPosX(384.0f);
        hairFont->SetPosY(0x88 + i * 0x1C - 4.0f);
        hairFont->Draw(txt);
    }

    DrawInit();

    if (CmakeState(this)->m_mode == 1) {
        float tribeX = 228.0f;
        float cursorY = static_cast<float>(0x88 + CmakeState(this)->m_select * 0x1C);

        if (CmakeState(this)->m_fieldSelect == 0) {
            DrawCursor(
                static_cast<int>(tribeX + static_cast<float>(static_cast<int>(System.m_frameCounter) % 8)),
                static_cast<int>(cursorY), alpha);
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeTribeClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x801708b0
 * PAL Size: 1080b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CmakeTribeCtrl()
{
    short repeat;
    short down;

    bool padBusy = false;
    int padLock = Pad.m_debugPadLock;
    if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
        padBusy = true;
    }
    {
        int held;
        if (padBusy) {
            held = 0;
        } else {
            int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
            held = Pad.GetPadInputs()[padIndex].buttonDown[0];
        }
        down = static_cast<short>(static_cast<unsigned short>(held));
    }

    padBusy = false;
    if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
        padBusy = true;
    }
    {
        int held;
        if (padBusy) {
            held = 0;
        } else {
            int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
            held = Pad.GetPadInputs()[padIndex].repeatButton;
        }
        repeat = static_cast<short>(static_cast<unsigned short>(held));
    }

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
                    unsigned char* base = reinterpret_cast<unsigned char*>(&Game);
                    int slot;
                    for (slot = 0; slot < 8; ++slot) {
                        if ((*reinterpret_cast<int*>(base + slot * 0xC30 + 0x1794) != 0) &&
                            (*(base + slot * 0xC30 + 0x1F96) != 1) &&
                            (*reinterpret_cast<unsigned short*>(base + slot * 0xC30 + 0x17D0) == CmakeState(this)->m_select) &&
                            (*reinterpret_cast<unsigned short*>(base + slot * 0xC30 + 0x17D4) == CmakeState(this)->m_row) &&
                            (*reinterpret_cast<unsigned short*>(base + slot * 0xC30 + 0x17D2) == s_CmakeInfo.m_gender)) {
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeTribeOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 3;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x80170ce8
 * PAL Size: 1624b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0, 0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
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

    float maxWidth = 0.0f;
    int y;
    int i;
    for (i = 0, y = 0x9C; i < 2; ++i) {
        const char* txt = GetMenuStr(0x11 + i);
        float width = static_cast<float>(font->GetWidth(txt));
        if (maxWidth < width) {
            maxWidth = width;
        }
        float x = static_cast<float>(-(width / 2.0 - 400.0));
        font->SetPosX(x);
        font->SetPosY(static_cast<float>(y) - 4.0f);
        font->Draw(txt);
        y += 0x28;
    }
    DrawInit();

    if (CmakeState(this)->m_mode == 1) {
        int sel = CmakeState(this)->m_select;
        int wobble = static_cast<int>(System.m_frameCounter) % 8;
        int cursorX = static_cast<int>(
            static_cast<double>(static_cast<float>(400.0 - maxWidth / 2.0) +
                                static_cast<float>(wobble)) -
            maxWidth / 2.0);
        int cursorY = static_cast<int>(156.0f + static_cast<float>(sel * 0x28));
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeSexClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeSexCtrl()
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeSexOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 2;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x80171340
 * PAL Size: 3168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0, 0.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 608.0f, 24.0f, 32.0f, 336.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, 192.0f, 56.0f, 416.0f, 264.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    if ((gCmakePreviousStep == 2) && (CmakeState(this)->m_mode == 0)) {
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
    float titleW = 280.0f;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(-(titleW / 2.0 - 400.0))), 268.0f, titleW, 64.0f,
        0.0f, 304.0f, 1.0f, 1.0f, 0.0f);

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x68 : 0x41));
    MenuPcs.DrawRect(
        0, 184.0f, 216.0f, 48.0f, 48.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    double crestRightX = 568.0;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(crestRightX)), 216.0f, 48.0f, 48.0f,
        48.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    if ((CmakeState(this)->m_mode == 1) && (CmakeState(this)->m_row < 5)) {
        short sel = CmakeState(this)->m_select;
        int cursorBase = (CmakeState(this)->m_row < 5) ? 0xE5 : 0xE5;
        int cursorY = CmakeState(this)->m_row * 0x20 + 0x63;
        int cellX = static_cast<int>(
            26.9f * static_cast<float>(sel) + static_cast<float>(cursorBase));
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x64 : 0x3D));
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
    GetRenderFlagBits(font->renderFlags).fixedWidth = 1;
    font->SetMargin(4.9f);
    SetCmakeFontColor(font, alpha);

    int tableBase = table * 5;
    for (i = 0; i < 5; i++) {
        const char* rowText = s_NameEntryStr[tableBase + i];
        font->SetPosX(240.0f);
        font->SetPosY(static_cast<float>(0x6C + i * 0x20));
        font->Draw(rowText);
    }

    GetRenderFlagBits(font->renderFlags).fixedWidth = 0;
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
    unsigned int nameLen = strlen(s_CmakeInfo.m_name);
    if (static_cast<int>(nameLen & (static_cast<int>(-nameLen | nameLen) >> 31)) >= 7) {
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeNameClose()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_mode = 2;
    cmakeState->m_frame = 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x80171fa0
 * PAL Size: 2332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::CmakeNameCtrl()
{
    short repeat;
    short down;

    bool padBusy = false;
    int padLock = Pad.m_debugPadLock;
    if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
        padBusy = true;
    }
    {
        int held;
        if (padBusy) {
            held = 0;
        } else {
            int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
            held = Pad.GetPadInputs()[padIndex].buttonDown[0];
        }
        down = static_cast<short>(static_cast<unsigned short>(held));
    }

    padBusy = false;
    if ((padLock != 0) || (Pad.m_debugPadPort != -1)) {
        padBusy = true;
    }
    {
        int held;
        if (padBusy) {
            held = 0;
        } else {
            int padIndex = (Pad.m_debugPadPort == 0) ? 0 : 0;
            held = Pad.GetPadInputs()[padIndex].repeatButton;
        }
        repeat = static_cast<short>(static_cast<unsigned short>(held));
    }

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
                CmakeState(this)->m_row = static_cast<short>(CmakeState(this)->m_row - 1);
            } else if (CmakeState(this)->m_select >= 10) {
                CmakeState(this)->m_row = 5;
            } else {
                CmakeState(this)->m_row = 4;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            short sel = CmakeState(this)->m_select;
            if (CmakeState(this)->m_row < (sel >= 10 ? 5 : 4)) {
                CmakeState(this)->m_row = static_cast<short>(CmakeState(this)->m_row + 1);
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
                    state->m_select = static_cast<short>(state->m_select - 1);
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
                    state->m_select = static_cast<short>(state->m_select + 1);
                } else {
                    state->m_select = 0;
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        }

        if ((repeat & 0xF) == 0) {
            if ((down & 0x40) != 0) {
                CmakeState(this)->m_table = static_cast<short>(CmakeState(this)->m_table - 1);
                if (CmakeState(this)->m_table < 0) {
                    CmakeState(this)->m_table = 2;
                }
                Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
            } else if ((down & 0x20) != 0) {
                CmakeState(this)->m_table = static_cast<short>(CmakeState(this)->m_table + 1);
                if (CmakeState(this)->m_table > 2) {
                    CmakeState(this)->m_table = 0;
                }
                Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
            } else if ((down & 0x1000) != 0) {
                CmakeState(this)->m_select = 0xB;
                CmakeState(this)->m_row = 5;
                Sound.PlaySe(2, 0x40, 0x7F, 0);
            } else if ((down & 0x100) != 0) {
                short curTable;
                short curSelect;
                short curRow = CmakeState(this)->m_row;
                if (curRow >= 5) {
                    int emptyLen = strlen(s_CmakeInfo.m_name);
                    if ((emptyLen & ((-emptyLen | emptyLen) >> 31)) == 0) {
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
                    curTable = CmakeState(this)->m_table;
                    curSelect = CmakeState(this)->m_select;
                    char picked[12];
                    memset(picked, 0, 3);
                    picked[0] = '\0';
                    const char* rowText = s_NameEntryStr[curRow + curTable * 5];
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
                    if (ret != 0) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    } else {
                        unsigned int finalLen = strlen(s_CmakeInfo.m_name);
                        if (static_cast<int>(finalLen & (static_cast<int>(-finalLen | finalLen) >> 31)) >= 7) {
                            CmakeState(this)->m_select = 0xB;
                            CmakeState(this)->m_row = 5;
                        }
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                    }
                    return 0;
                }
            } else if ((down & 0x200) != 0) {
                unsigned int bsLen0 = strlen(s_CmakeInfo.m_name);
                if ((bsLen0 & (static_cast<int>(-bsLen0 | bsLen0) >> 31)) != 0) {
                    const char* name = s_CmakeInfo.m_name;
                    int bsRet;
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeNameOpen()
{
    CmakeMenuState* cmakeState = CmakeState(this);
    cmakeState->m_step = 1;
    cmakeState->m_mode = 0;
    cmakeState->m_frame = 0;
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeDraw()
{
    DrawSingCMake();
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeClose()
{
    CmakeMenuState* state = CmakeState(this);
    state->m_step = 0;
    state->m_mode = 2;
    state->m_frame = 0;
    state->m_resultDir = -1;
    state->m_resultFlag = 0;
    state->m_selectionInitialized = 0;
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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeCtrl()
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

    gCmakePreviousStep = static_cast<int>(step);

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
#ifndef VERSION_GCCP01
void CMenuPcs::CmakeOpen()
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
#endif

/*
 * --INFO--
 * PAL Address: 0x801728bc
 * PAL Size: 864b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_propagation off
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3A));
    MenuPcs.DrawRect(
        0, 432.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 568.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);

    if (yesNoSel != 0) {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3D));
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

    const char* noStr;
    const char* yesStr = GetMenuStr(1);
    float yesW = static_cast<float>(font->GetWidth(yesStr));
    int yesX = 0x1D0;
    yesX = static_cast<int>(
        (48.0f - yesW) / 2.0f + static_cast<float>(yesX));
    font->SetPosX(static_cast<float>(yesX));
    font->SetPosY(369.0f);
    font->Draw(yesStr);

    noStr = GetMenuStr(2);
    float noW = static_cast<float>(font->GetWidth(noStr));
    int noX = 0x218;
    noX = static_cast<int>(
        (48.0f - noW) / 2.0f + static_cast<float>(noX));
    font->SetPosX(static_cast<float>(noX));
    font->SetPosY(369.0f);
    font->Draw(noStr);

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
#pragma opt_propagation on

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::AddNameChara(int c, int slot, int, int)
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
}

/*
 * --INFO--
 * PAL Address: 0x80172c1c
 * PAL Size: 732b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCmakeName(int x, int y, char* text, float alpha)
{
    float textW;

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);

    float nameW = 161.0f;
    int nameX = static_cast<int>(-(nameW / 2.0 - 400.0));

    int baseY = 300;
    if (x != 0) {
        baseY = 0x130;
    }

    CFont* font = m_fonts[CMAKE_FONT_VALUE];
    font->SetShadow(1);
    font->SetScale(1.0f);
    font->DrawInit();
    GetRenderFlagBits(font->renderFlags).fixedWidth = 1;
    font->SetMargin(1.0f);

    alpha = 255.0f * alpha;
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha)).color);
    font->SetTlut(6);

    textW = font->GetWidth(text);
    font->SetPosX(static_cast<float>(nameX));
    font->SetPosY(static_cast<float>(baseY - 4));
    font->Draw(text);
    GetRenderFlagBits(font->renderFlags).fixedWidth = 0;
    DrawInit();

    if (y != 0) {
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

        GXColor drawColor;
        drawColor.r = 0xFF;
        drawColor.g = 0xFF;
        drawColor.b = 0xFF;
        drawColor.a = static_cast<unsigned char>(alpha);
        GXSetChanMatColor(GX_COLOR0A0, drawColor);

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x60 : 0x39));

        int cursorX = static_cast<int>(static_cast<float>(nameX) + textW);
        MenuPcs.DrawRect(
            0,
            static_cast<float>(cursorX),
            static_cast<float>(baseY - 0x10),
            32.0f, 48.0f,
            static_cast<float>(((static_cast<int>(System.m_frameCounter) >> 1) % 8) << 5), 0.0f,
            1.0f, 1.0f, 0.0f);
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
void CMenuPcs::DrawCmakeCrest(int tribe, int x, int y, float alpha)
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x31));
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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCmakeCharaText(int page, float alpha)
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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCmakeBallCursor(int kind, int frame, float alpha)
{
    DrawCrystal(kind, frame, alpha);
}

/*
 * --INFO--
 * PAL Address: 0x80172ef8
 * PAL Size: 864b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, 480.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 552.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);

    if (yesNoSel != 0) {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x64 : 0x3D));
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
    font->SetPosY(static_cast<float>(cursorY - 4));
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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCmakePageMark(float alpha)
{
    DrawCrystal(0, 0, alpha);
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
void CMenuPcs::DrawCmakeNameBase(int page, float alpha)
{
    DrawCmakeWin(0.0f, 0.0f, alpha);
    DrawCmakeTitle(page, 0.0f, alpha);
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
void CMenuPcs::DrawCrystal(int type, int frame, float alpha)
{
    int index = type + frame;
    if (index < 0) {
        index = 0;
    }

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(255.0f * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col;
    col.r = 0xFF;
    col.g = 0xFF;
    col.b = 0xFF;
    col.a = static_cast<unsigned char>(a);
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x31));
    MenuPcs.DrawRect(
        0, 351.0f, 96.0f, 368.0f, 368.0f,
        static_cast<float>((index & 1) * 0xB8), static_cast<float>((index / 2) * 0xB8),
        1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x80173258
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma opt_propagation off
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x62 : 0x3B));
    MenuPcs.DrawRect(
        0, 214.0f, 32.0f, 112.0f, 56.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 474.0f, 32.0f, 112.0f, 56.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x61 : 0x3A));
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((CmakeResult(this) != 0) ? 0x65 : 0x3E));

    baseX = static_cast<int>(baseX + 20.0);
    offsU = static_cast<int>(static_cast<double>(offsU) + 8.0);
    MenuPcs.DrawRect(
        0, static_cast<float>(baseX), static_cast<float>(offsU), 208.0f, 24.0f,
        0.0f, static_cast<float>(page * 0x18), 1.0f, 1.0f, 0.0f);
}
#pragma opt_propagation on

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCmakeWin(float x, float y, float alpha)
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((x == 0.0f) ? 0x3F : 0x35));
    MenuPcs.DrawRect(
        0, 0.0f, 24.0f, 32.0f, static_cast<float>(frameH),
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 608.0f, 24.0f, 32.0f, static_cast<float>(frameH),
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((x == 0.0f) ? 0x40 : 0x36));
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
 * PAL Address: 0x8017352c
 * PAL Size: 616b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
    CMenuPcs::TEX baseTex = static_cast<CMenuPcs::TEX>(0x3F);
    if (widePage) {
        baseTex = static_cast<CMenuPcs::TEX>(0x35);
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(widePage ? 0x36 : 0x40));
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
 * PAL Address: 0x80173794
 * PAL Size: 1040b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingCMake()
{

    switch (CmakeState(this)->m_step) {
    case 0: {
        float alpha = CalcCmakeFadeAlpha(this);
        DrawWMFrame0(1, alpha);

        SetCmakeBlendMatColor(alpha);

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
        MenuPcs.DrawRect(
            0,
            0.0f, 24.0f, 32.0f, 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        MenuPcs.DrawRect(
            8,
            608.0f, 24.0f, 32.0f, 336.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
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

    gCmakePreviousStep = static_cast<int>(CmakeState(this)->m_step);

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
        gCmakePreviousStep = -1;
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
            down = GetCmakePadDown();
            repeat = GetCmakePadRepeat();

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
            down = GetCmakePadDown();
            repeat = GetCmakePadRepeat();

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
                            *reinterpret_cast<int*>(MenuS32(this, 0x844) + CmakeSlot(this) * 0x14 + 4) = 3;

                            CCaravanWork* caravanWork;
                            int slot = static_cast<int>(CmakeSlot(this));
                            int modelNo = GetModelNo(static_cast<int>(s_CmakeInfo.m_tribe), static_cast<int>(s_CmakeInfo.m_hair),
                                static_cast<int>(s_CmakeInfo.m_gender));
                            *reinterpret_cast<int*>(MenuS32(this, 0x824) + slot * 0x34 + 8) = modelNo;

                            caravanWork = &Game.m_caravanWorkArr[slot];
                            *reinterpret_cast<unsigned char*>(MenuS32(this, 0x828) + 10) = 1;
                            caravanWork->LoadInit();
                            caravanWork->m_shopState = 1;
                            caravanWork->unk_0x3a8 = 0x101;
                            caravanWork->unk_0x3ac = static_cast<int>(s_CmakeInfo.m_job);
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
            down = GetCmakePadDown();
            repeat = GetCmakePadRepeat();

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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCP01
void GetCharaCnt(char* dst)
{
    if (dst != nullptr) {
        dst[0] = '\0';
    }
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
#ifndef VERSION_GCCP01
void GetCharaType(char* dst, int type)
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
#ifndef VERSION_GCCP01
void GetChara(char* dst, int index, char* table)
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
