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

extern "C" float FLOAT_80333254;
extern "C" float FLOAT_8033325c;
extern "C" float FLOAT_80333260;
extern "C" float FLOAT_80333264;
extern "C" float FLOAT_80333240;
extern "C" float FLOAT_80333244;
extern "C" float FLOAT_80333248;
extern "C" float FLOAT_80333250;
extern "C" float FLOAT_80333258;
extern "C" float FLOAT_803332dc;
extern "C" float FLOAT_803332b0;
extern "C" float FLOAT_80333364;
extern "C" float FLOAT_803332a4;
extern "C" float FLOAT_80333280;
extern "C" float FLOAT_80333284;
extern "C" float FLOAT_80333288;
extern "C" float FLOAT_80333290;
extern "C" float FLOAT_80333298;
extern "C" float FLOAT_803332a0;
extern "C" float FLOAT_80333278;
extern "C" float FLOAT_8033327c;
extern "C" float FLOAT_8033324c;
extern "C" float FLOAT_803332a8;
extern "C" float FLOAT_803332ac;
extern "C" float FLOAT_803332d8;
extern "C" float FLOAT_803332e8;
extern "C" float FLOAT_803332ec;
extern "C" float FLOAT_803332e0;
extern "C" float FLOAT_803332e4;
extern "C" float FLOAT_803332f0;
extern "C" float FLOAT_803332f4;
extern "C" float FLOAT_803332fc;
extern "C" float FLOAT_80333348;
extern "C" float FLOAT_80333350;
extern "C" float FLOAT_80333354;
extern "C" float FLOAT_80333358;
extern "C" float FLOAT_8033335c;
extern "C" float FLOAT_80333360;
extern "C" float FLOAT_8033334c;
extern "C" float FLOAT_80333368;
extern "C" float FLOAT_8033336c;
extern "C" float FLOAT_80333370;
extern "C" float FLOAT_80333380;
extern "C" float FLOAT_80333390;
extern "C" float FLOAT_80333394;
extern "C" float FLOAT_80333398;
extern "C" float FLOAT_80333300;
extern "C" float FLOAT_80333308;
extern "C" float FLOAT_80333318;
extern "C" float FLOAT_8033331c;
extern "C" float FLOAT_80333320;
extern "C" float FLOAT_80333324;
extern "C" float FLOAT_80333334;
static const float FLOAT_803333a8 = 40.0f;
static const float FLOAT_803333ac = 278.0f;
static const float FLOAT_803333b0 = 248.0f;
static const float FLOAT_803333c8 = 208.0f;
extern "C" float FLOAT_80333304;
extern "C" float FLOAT_803332c0;
extern "C" float FLOAT_803332c4;
extern "C" float FLOAT_803332c8;
extern "C" double DOUBLE_803332d0;
extern "C" double DOUBLE_80333270;
extern "C" double DOUBLE_80333268;
extern "C" double DOUBLE_80333288;
extern "C" double DOUBLE_80333298;
extern "C" double DOUBLE_80333378;
extern "C" double DOUBLE_80333388;
extern "C" double DOUBLE_803333a0;
static const double DOUBLE_803333b8 = 20.0;
static const double DOUBLE_803333c0 = 8.0;
extern "C" int gCmakePreviousStep;
extern "C" char s_menuSubfontPathFmt[];
extern "C" {
extern "C" const char s_cmake_cpp[] = "cmake.cpp";
}

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

struct CmakeMenuFields {
    unsigned char m_pad000[0xEC];
    CMemory::CStage* m_menuStage;
    CMemory::CStage* m_stageF0;
    CMemory::CStage* m_stageF4;
    CFont* m_fonts[5];
    unsigned char m_pad10C[0x830 - 0x10C];
    void* m_villageWork;
};
STATIC_ASSERT(sizeof(CmakeMenuFields) == 0x834);

static inline CmakeMenuFields& CmakeFields(CMenuPcs* menu)
{
    return *reinterpret_cast<CmakeMenuFields*>(menu);
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
    return reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(menu) + 0x7F4)[slot];
}

static inline void ReleaseRefObject(void* object)
{
    int* raw = reinterpret_cast<int*>(object);
    int refCount = raw[1] - 1;
    raw[1] = refCount;
    if (refCount == 0) {
        delete reinterpret_cast<CRef*>(object);
    }
}

static inline float CalcCmakeFadeAlpha(CMenuPcs* menu)
{
    int state = MenuS32(menu, 0x82C);
    int frame = static_cast<int>(*reinterpret_cast<short*>(state + 0x22)) - 1;
    if (frame < 0) {
        frame = 0;
    }

    short mode = *reinterpret_cast<short*>(state + 0x10);
    if (mode == 0) {
        return static_cast<float>(DOUBLE_80333268 * static_cast<double>(frame));
    }
    if (mode == 1) {
        return FLOAT_80333258;
    }
    return static_cast<float>(DOUBLE_80333270 - DOUBLE_80333268 * static_cast<double>(frame));
}

static inline void DrawCmakePreviewCharaAlpha(CMenuPcs* menu, float alpha)
{
    int slot = static_cast<int>(MenuS16(menu, 0x86A));
    int modelBlock = MenuS32(menu, 0x814);
    if (*reinterpret_cast<int*>(modelBlock + (slot + 0x20) * 0x50) == 0) {
        return;
    }

    *reinterpret_cast<unsigned short*>(modelBlock + 0x6E8) = 0xFF24;
    *reinterpret_cast<unsigned short*>(modelBlock + 0x6EA) = 4;
    menu->DrawInit();

    CCharaPcs::CHandle* handle = GetCmakeCharaHandle(menu, slot);
    if (handle->m_charaKind == 3) {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x32));
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        GXColor col = {0xFF, 0xFF, 0xFF, 0xFF};
        GXSetChanMatColor(GX_COLOR0A0, col);
        MenuPcs.DrawRect(
            0,
            FLOAT_80333244, FLOAT_80333248, FLOAT_8033324c, FLOAT_80333250,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    } else {
        menu->SetProjection(0x16);
        menu->SetLight(2);
        *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0x9C) = alpha;
        handle->Draw(5);
        menu->RestoreProjection();
    }

    menu->DrawInit();
}

static inline void DrawCmakePreviewChara(CMenuPcs* menu)
{
    DrawCmakePreviewCharaAlpha(menu, FLOAT_80333258);
}

static inline void DrawCmakeSelectionBackdrop(CMenuPcs* menu)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor col = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, col);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        0.0f, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8,
        FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
    for (int x = 0x20; x < 0x260; x += 0x20) {
        int span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }

        MenuPcs.DrawRect(
            0,
            (float)x, FLOAT_803332d8, (float)span, FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    }

    menu->DrawInit();
}

static inline void DrawCmakePopupPanel(CMenuPcs* menu, float alpha, float x, float y, float w, float h, float scaleX, float scaleY)
{
    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(menu, 0x86C) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, x, y, w, h,
        FLOAT_80333254, FLOAT_80333254, scaleX, scaleY, 0.0f);
}

static inline void DrawCmakeMcOverlay(CMenuPcs* menu, int messageId)
{
    int mcState = *reinterpret_cast<short*>(MenuS32(menu, 0x848) + 10);

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
    if (MenuS16(menu, 0x86C) == 0) {
        return CmakeFields(menu).m_fonts[CMAKE_FONT_LABEL];
    }
    return CmakeFields(menu).m_fonts[CMAKE_FONT_VILLAGE];
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
extern "C" char lbl_803331F0[];
extern "C" char lbl_803331F8[];
extern "C" char lbl_80333200[];
extern "C" char lbl_80333208[];
extern "C" char lbl_80333210[];
extern "C" char lbl_80333218[];
extern "C" char lbl_80333220[];
extern "C" char lbl_80333228[];
extern "C" char lbl_80333230[];
extern "C" char lbl_80333238[];

extern "C" const char* s_NameEntryStr[] = {
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

extern "C" char* PTR_s_world2[] = {
    lbl_803331F0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
};
extern "C" CMenuPcs::CTmp s_cmakeWorldTextureTable[] = {
    {8, lbl_803331F8},
    {8, lbl_80333200},
    {8, lbl_80333208},
    {8, lbl_80333210},
    {8, lbl_80333218},
    {8, lbl_80333220},
    {8, lbl_80333228},
    {8, lbl_80333230},
    {8, lbl_80333238},
};

static CmakeInfo s_CmakeInfo;
static char s_CmakeVillageName[0x10];

struct CmakeFlatTableEntry {
    int count;
    char** strings;
    char* stringBuf;
};

struct CmakeFlatDataOverlay {
    int dataCount;
    unsigned char data[0x64];
    int tableCount;
    CmakeFlatTableEntry table[8];
};

static inline char* GetCmakeNameBuffer()
{
    return s_CmakeInfo.m_name;
}

static void LoadCmakeVillageName()
{
    memset(s_CmakeInfo.m_name, 0, sizeof(s_CmakeInfo.m_name));
    strcpy(s_CmakeInfo.m_name, s_CmakeVillageName);
}

static void StoreCmakeVillageName()
{
    memset(s_CmakeVillageName, 0, sizeof(s_CmakeVillageName));
    strcpy(s_CmakeVillageName, s_CmakeInfo.m_name);
}

static bool IsCmakeNameBlank(const char* name)
{
    if (name == nullptr || name[0] == '\0') {
        return true;
    }

    for (const char* it = name; *it != '\0'; ++it) {
        if (*it != ' ') {
            return false;
        }
    }

    return true;
}

static bool IsDuplicateCmakeName(CMenuPcs* menu, const char* name)
{
    if (name == nullptr || name[0] == '\0') {
        return false;
    }

    int activeSlot = static_cast<int>(MenuS16(menu, 0x86A));
    for (int slot = 0; slot < 8; ++slot) {
        if (slot == activeSlot) {
            continue;
        }

        unsigned char* entry = GetCmakeRosterEntry(menu, slot);
        if (*reinterpret_cast<int*>(entry + 0x1794) == 0) {
            continue;
        }
        if (*(entry + 0x1F96) == 1) {
            continue;
        }
        if (strcmp(name, reinterpret_cast<char*>(entry + 0x17BA)) == 0) {
            return true;
        }
    }

    CmakeFlatDataOverlay* textData = reinterpret_cast<CmakeFlatDataOverlay*>(&Game.m_cFlatDataArr[1]);
    char** nameTable = textData->table[2].strings;
    int nameCount = textData->table[2].count;
    for (int i = 0; i < nameCount; ++i) {
        if (nameTable[i] != nullptr && strcmp(nameTable[i], name) == 0) {
            return true;
        }
    }

    return false;
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

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void GetCharaType(char* dst, int type)
{
    if (dst == nullptr) {
        return;
    }

    dst[0] = static_cast<char>(type);
    dst[1] = '\0';
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
void GetCharaCnt(char* dst)
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
    int state = MenuS32(this, 0x82C);

    if (*reinterpret_cast<unsigned char*>(state + 0x0B) == 0) {
        InitFrame0Info();
        memset(&s_CmakeInfo, 0, sizeof(s_CmakeInfo));
        *reinterpret_cast<unsigned char*>(state + 0x0B) = 1;
        *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
        gCmakePreviousStep = -1;
        *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) = 3;
    }

    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& openMode = *reinterpret_cast<short*>(state + 0x10);
    short& step = *reinterpret_cast<short*>(state + 0x16);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& resultFlag = *reinterpret_cast<short*>(state + 0x2E);
    unsigned short result = 0;

    switch (step) {
    case 0:
        if (openMode == 0) {
            CalcWMFrame0(frame - 10);
            if (frame < 10) {
                frame = frame + 1;
            } else {
                *reinterpret_cast<short*>(state + 0x26) = 0;
                *reinterpret_cast<short*>(state + 0x28) = 0;
                *reinterpret_cast<short*>(state + 0x2A) = 0;
                *reinterpret_cast<short*>(state + 0x2C) = 0;
            }
            result = (frame >= 10) ? 1 : 0;
        } else if (openMode == 1) {
            result = 0;
        } else {
            CalcWMFrame0(-frame);
            if (frame < 10) {
                frame = frame + 1;
            }
            result = (frame >= 10) ? 1 : 0;
        }
        break;
    case 1:
        if (openMode == 0) {
            if (frame < 10) {
                frame = frame + 1;
            }
            result = (frame >= 10) ? 1 : 0;
        } else if (openMode == 1) {
            result = static_cast<unsigned short>(CmakeNameCtrl());
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            if (resultDir < 0) {
                ChgModel(static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
            }
            result = 1;
        }
        break;
    case 2: {
        if (openMode == 0) {
            if (*reinterpret_cast<unsigned char*>(state + 0x0C) == 0) {
                *reinterpret_cast<short*>(state + 0x26) = 0;
                *reinterpret_cast<unsigned char*>(state + 0x0C) = 1;
            }
            if (frame < 10) {
                frame = frame + 1;
            }
            result = (frame >= 10) ? 1 : 0;
        } else if (openMode == 1) {
            unsigned short down;
            unsigned short repeat;

            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                down = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                down = static_cast<unsigned short>(Pad.GetPadInputs()[0].buttonDown[0]);
            }

            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                repeat = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                repeat = Pad.GetPadInputs()[0].repeatButton;
            }

            if (repeat == 0) {
                result = 0;
            } else {
                if ((repeat & 0xC) != 0) {
                    *reinterpret_cast<unsigned short*>(state + 0x26) =
                        *reinterpret_cast<unsigned short*>(state + 0x26) ^ 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
                if ((repeat & 0xC) == 0) {
                    if ((down & 0x100) != 0) {
                        s_CmakeInfo.m_gender = static_cast<signed char>(*reinterpret_cast<short*>(state + 0x26));
                        resultDir = 1;
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        result = 1;
                        break;
                    }
                    if ((down & 0x200) != 0) {
                        resultDir = -1;
                        Sound.PlaySe(3, 0x40, 0x7F, 0);
                        result = 1;
                        break;
                    }
                }
                result = 0;
            }
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            result = 1;
        }
        break;
    }
    case 3:
        if (openMode == 0) {
            if (*reinterpret_cast<unsigned char*>(state + 0x0C) == 0) {
                *reinterpret_cast<short*>(state + 0x26) = 0;
                *reinterpret_cast<short*>(state + 0x28) = 0;
                *reinterpret_cast<short*>(state + 0x30) = 0;
                *reinterpret_cast<unsigned char*>(state + 0x0C) = 1;
            }
            if (frame < 10) {
                frame = frame + 1;
            }
            result = (frame >= 10) ? 1 : 0;
        } else if (openMode == 1) {
            result = CmakeTribeCtrl();
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            result = 1;
        }
        break;
    case 4:
        if (openMode == 0) {
            if (*reinterpret_cast<unsigned char*>(state + 0x0C) == 0) {
                *reinterpret_cast<short*>(state + 0x26) = 0;
                *reinterpret_cast<unsigned char*>(state + 0x0C) = 1;
            }
            if (frame < 10) {
                frame = frame + 1;
            }
            result = (frame >= 10) ? 1 : 0;
        } else if (openMode == 1) {
            result = CmakeJobCtrl();
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            result = 1;
        }
        break;
    case 5: {
        if (openMode == 0) {
            if (*reinterpret_cast<unsigned char*>(state + 0x0C) == 0) {
                *reinterpret_cast<short*>(state + 0x26) = 0;
                *reinterpret_cast<unsigned char*>(state + 0x0C) = 1;
            }
            if (frame < 10) {
                frame = frame + 1;
            }
            result = (frame >= 10) ? 1 : 0;
        } else if (openMode == 1) {
            unsigned short down;
            unsigned short repeat;

            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                down = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                down = static_cast<unsigned short>(Pad.GetPadInputs()[0].buttonDown[0]);
            }

            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                repeat = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                repeat = Pad.GetPadInputs()[0].repeatButton;
            }

            if (repeat == 0) {
                result = 0;
            } else {
                if ((repeat & 3) != 0) {
                    *reinterpret_cast<unsigned short*>(state + 0x26) =
                        *reinterpret_cast<unsigned short*>(state + 0x26) ^ 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
                if ((repeat & 3) == 0) {
                    if ((down & 0x100) != 0) {
                        if (*reinterpret_cast<short*>(state + 0x26) == 0) {
                            resultDir = 1;
                            *reinterpret_cast<int*>(MenuS32(this, 0x844) + MenuS16(this, 0x86A) * 0x14 + 4) = 3;

                            int slot = static_cast<int>(MenuS16(this, 0x86A));
                            int modelNo = GetModelNo(static_cast<int>(s_CmakeInfo.m_tribe), static_cast<int>(s_CmakeInfo.m_hair),
                                static_cast<int>(s_CmakeInfo.m_gender));
                            *reinterpret_cast<int*>(MenuS32(this, 0x824) + slot * 0x34 + 8) = modelNo;

                            CCaravanWork* caravanWork = &Game.m_caravanWorkArr[slot];
                            *reinterpret_cast<unsigned char*>(MenuS32(this, 0x828) + 10) = 1;
                            caravanWork->LoadInit();
                            caravanWork->m_shopState = 1;
                            caravanWork->unk_0x3a8 = 0x101;
                            caravanWork->unk_0x3ac = static_cast<int>(s_CmakeInfo.m_job);
                            memset(caravanWork->unk_0x3ca_0x3dd, 0, 0x11);
                            strcpy(reinterpret_cast<char*>(caravanWork->unk_0x3ca_0x3dd), s_CmakeInfo.m_name);
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
                            *reinterpret_cast<short*>(state + 0x18) =
                                static_cast<short>(static_cast<int>(GetMaxAnimWait()));
                        } else {
                            resultDir = -1;
                        }
                        Sound.PlaySe(0x33, 0x40, 0x7F, 0);
                        result = 1;
                        break;
                    }
                    if ((down & 0x200) != 0) {
                        resultDir = -1;
                        Sound.PlaySe(3, 0x40, 0x7F, 0);
                        result = 1;
                        break;
                    }
                }
                result = 0;
            }
        } else {
            if (*reinterpret_cast<short*>(state + 0x18) == 0) {
                if (frame < 10) {
                    frame = frame + 1;
                } else {
                    result = 1;
                }
            } else {
                *reinterpret_cast<short*>(state + 0x18) =
                    static_cast<short>(*reinterpret_cast<short*>(state + 0x18) - 1);
            }
        }
        break;
    }
    case 6: {
        if (openMode == 0) {
            if (*reinterpret_cast<unsigned char*>(state + 0x0C) == 0) {
                *reinterpret_cast<short*>(state + 0x26) = 0;
                *reinterpret_cast<unsigned char*>(state + 0x0C) = 1;
            }
            if (frame < 10) {
                frame = frame + 1;
            }
            result = (frame >= 10) ? 1 : 0;
        } else if (openMode == 1) {
            unsigned short down;
            unsigned short repeat;

            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                down = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                down = static_cast<unsigned short>(Pad.GetPadInputs()[0].buttonDown[0]);
            }

            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                repeat = 0;
            } else {
                __cntlzw(static_cast<unsigned int>(Pad._448_4_));
                repeat = Pad.GetPadInputs()[0].repeatButton;
            }

            if (repeat == 0) {
                result = 0;
            } else {
                if ((repeat & 0x8) != 0) {
                    if (*reinterpret_cast<short*>(state + 0x26) == 0) {
                        *reinterpret_cast<short*>(state + 0x26) = 3;
                    } else {
                        *reinterpret_cast<short*>(state + 0x26) =
                            static_cast<short>(*reinterpret_cast<short*>(state + 0x26) - 1);
                    }
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else if ((repeat & 0x4) != 0) {
                    if (*reinterpret_cast<short*>(state + 0x26) < 3) {
                        *reinterpret_cast<short*>(state + 0x26) =
                            static_cast<short>(*reinterpret_cast<short*>(state + 0x26) + 1);
                    } else {
                        *reinterpret_cast<short*>(state + 0x26) = 0;
                    }
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }

                if ((repeat & 0xC) == 0) {
                    if ((down & 0x100) != 0) {
                        if (*reinterpret_cast<short*>(state + 0x26) < 3) {
                            ChgModel(static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
                        }
                        resultDir = 1;
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        result = 1;
                        break;
                    }
                    if ((down & 0x200) != 0) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    }
                }
                result = 0;
            }
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            result = 1;
        }
        break;
    }
    default:
        break;
    }

    CalcSingleCMakeChara();
    resultFlag = static_cast<short>(result);
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
    int state = MenuS32(this, 0x82C);
    short step = *reinterpret_cast<short*>(state + 0x16);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& resultFlag = *reinterpret_cast<short*>(state + 0x2E);
    short& frame = *reinterpret_cast<short*>(state + 0x22);

    switch (step) {
    case 0: {
        float alpha = CalcCmakeFadeAlpha(this);
        DrawWMFrame0(1, alpha);

        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

        int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * static_cast<double>(alpha));
        GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
        GXSetChanMatColor(GX_COLOR0A0, col);

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
        MenuPcs.DrawRect(
            0,
            FLOAT_80333254, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        MenuPcs.DrawRect(
            8,
            FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
        for (int x = 0x20; x < 0x260;) {
            int span = 0x20;
            if ((0x260 - x) < span) {
                span = 0x260 - x;
            }

            MenuPcs.DrawRect(
                0,
                static_cast<float>(x), FLOAT_803332d8, static_cast<float>(span), FLOAT_803332e0,
                FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
            x += span;
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

    if (resultFlag == 0) {
        return;
    }

    if (mode < 2) {
        mode = static_cast<short>(mode + 1);
        frame = 0;
        *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) = 3;
        return;
    }

    gCmakePreviousStep = static_cast<int>(step);

    if (step == 6) {
        step = static_cast<short>(*reinterpret_cast<short*>(state + 0x26) + 1);
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

    *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
    frame = 0;
    *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) = 3;
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

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    const bool widePage = (page == 0);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(widePage ? 0x35 : 0x3F));

    int frameH = widePage ? 0x180 : 0x150;
    MenuPcs.DrawRect(
        0, FLOAT_80333254, FLOAT_803332dc, FLOAT_803332dc, static_cast<float>(frameH),
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8, FLOAT_803332e4, FLOAT_803332dc, FLOAT_803332dc, static_cast<float>(frameH),
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(widePage ? 0x36 : 0x40));
    for (int x = 0x20; x < 0x260;) {
        int span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }

        MenuPcs.DrawRect(
            0, static_cast<float>(x), FLOAT_803332dc, static_cast<float>(span), static_cast<float>(frameH),
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        x += span;
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
void CMenuPcs::DrawCmakeWin(float x, float y, float alpha)
{
    (void)y;

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    int frameH = (x == 0.0f) ? 0x150 : 0x180;
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((x == 0.0f) ? 0x3F : 0x35));
    MenuPcs.DrawRect(
        0, FLOAT_80333254, 24.0f, FLOAT_803332dc, static_cast<float>(frameH),
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8, FLOAT_803332e4, 24.0f, FLOAT_803332dc, static_cast<float>(frameH),
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((x == 0.0f) ? 0x40 : 0x36));
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        MenuPcs.DrawRect(
            0, static_cast<float>(tileX), 24.0f, static_cast<float>(tileW), static_cast<float>(frameH),
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        tileX += tileW;
    }
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
void CMenuPcs::DrawCmakeTitle(int page, float x, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x62 : 0x3B));
    MenuPcs.DrawRect(
        0, FLOAT_80333390, FLOAT_803332dc, FLOAT_80333394, FLOAT_8033327c,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8, FLOAT_80333398, FLOAT_803332dc, FLOAT_80333394, FLOAT_8033327c,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    unsigned int offsU = static_cast<unsigned int>(
        -(static_cast<double>(FLOAT_803333a8 * x - FLOAT_803333a8) * DOUBLE_80333298) + DOUBLE_803333a0);
    float offs = static_cast<float>(offsU);
    MenuPcs.DrawRect(
        0, FLOAT_803333ac, offs, FLOAT_803333b0, FLOAT_803333a8,
        FLOAT_80333254, FLOAT_80333284, FLOAT_80333258, alpha, 0.0f);

    if (x >= static_cast<float>(DOUBLE_80333270)) {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x65 : 0x3E));

        float titleX = static_cast<float>(offsU + static_cast<unsigned int>(DOUBLE_803333b8));
        float titleY = static_cast<float>(offsU + static_cast<unsigned int>(DOUBLE_803333c0));
        MenuPcs.DrawRect(
            0, titleX, titleY, FLOAT_803333c8, FLOAT_803332d8,
            FLOAT_80333254, static_cast<float>(page * 0x18), FLOAT_80333258, FLOAT_80333258, 0.0f);
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
void CMenuPcs::DrawCrystal(int type, int frame, float alpha)
{
    int index = type + frame;
    if (index < 0) {
        index = 0;
    }

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x31));
    MenuPcs.DrawRect(
        0, FLOAT_803332e8, FLOAT_803332ec, FLOAT_803332a4, FLOAT_803332a4,
        static_cast<float>((index & 1) * 0xB8), static_cast<float>((index / 2) * 0xB8),
        FLOAT_80333258, FLOAT_80333258, 0.0f);
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
void CMenuPcs::DrawCmakePageMark(float alpha)
{
    DrawCrystal(0, 0, alpha);
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

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, FLOAT_80333368, FLOAT_803332a4, FLOAT_803332b0, FLOAT_803332dc,
        FLOAT_8033334c, FLOAT_80333284, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8, FLOAT_8033336c, FLOAT_803332a4, FLOAT_803332b0, FLOAT_803332dc,
        FLOAT_8033334c, FLOAT_80333284, FLOAT_80333258, FLOAT_80333258, 0.0f);

    if (yesNoSel != 0) {
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        GXSetChanMatColor(GX_COLOR0A0, col);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x64 : 0x3D));
        MenuPcs.DrawRect(
            0, FLOAT_80333370, FLOAT_80333358, FLOAT_803332b0, FLOAT_803332b0,
            FLOAT_8033324c, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    }

    CFont* font = CmakeFields(this).m_fonts[CMAKE_FONT_VALUE];
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(1);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();
    font->SetTlut(7);

    CColor rgba(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    font->SetColor(rgba);

    const char* txt = GetMenuStr(0x29);
    float w = static_cast<float>(font->GetWidth(txt));
    unsigned int tx = static_cast<unsigned int>(
        static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_80333380) - static_cast<double>(w))) *
            DOUBLE_80333298 +
        DOUBLE_80333378);
    int cursorY = static_cast<int>(DOUBLE_80333388);
    font->SetPosX(static_cast<float>(static_cast<int>(tx)));
    font->SetPosY(static_cast<float>(cursorY - 4));
    font->Draw(txt);
    DrawInit();

    if (yesNoSel != 0) {
        int frame = System.m_frameCounter & 7;
        DrawCursor(static_cast<int>(tx) - 0x20 + frame, cursorY, alpha);
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
void CMenuPcs::DrawCmakeBallCursor(int kind, int frame, float alpha)
{
    DrawCrystal(kind, frame, alpha);
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

    CFont* labelFont = CmakeFields(this).m_fonts[CMAKE_FONT_LABEL];
    labelFont->SetMargin(FLOAT_80333258);
    labelFont->SetShadow(0);
    labelFont->SetScale(FLOAT_80333258);
    labelFont->DrawInit();

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    CColor rgba(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    labelFont->SetColor(rgba);

    float labelWidths[4];
    for (int i = 0; i < 4; i++) {
        const char* txt = GetMenuStr(0x2A + i);
        if (txt == 0) {
            txt = "";
        }

        labelWidths[i] = FLOAT_803332f0 + static_cast<float>(labelFont->GetWidth(txt));
        labelFont->SetPosX(FLOAT_803332f0);
        labelFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
        labelFont->Draw(txt);
    }

    CFont* valueFont = CmakeFields(this).m_fonts[CMAKE_FONT_VALUE];
    valueFont->SetMargin(FLOAT_80333258);
    valueFont->SetShadow(1);
    valueFont->SetScale(FLOAT_80333258);
    valueFont->DrawInit();
    valueFont->SetColor(rgba);
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
            strcat(tribeWithSep, "/", sizeof(tribeWithSep));
            txt = tribeWithSep;
            break;
        default:
            txt = GetJobStr(s_CmakeInfo.m_job);
            break;
        }

        if (txt == 0) {
            txt = "";
        }

        valueFont->SetPosX(FLOAT_803332fc + labelWidths[i]);
        valueFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
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
                FLOAT_80333300 + (FLOAT_803332fc + labelWidths[i] + static_cast<float>(valueFont->GetWidth(tribeWithSep))));
            valueFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
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
void CMenuPcs::DrawCmakeCrest(int tribe, int x, int y, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x31));
    MenuPcs.DrawRect(
        0,
        FLOAT_803332e8 + static_cast<float>(x),
        FLOAT_803332ec + static_cast<float>(y),
        FLOAT_803332a8, FLOAT_803332a8,
        static_cast<float>((tribe & 1) * 0xB8),
        static_cast<float>((tribe / 2) * 0xB8),
        FLOAT_80333258, FLOAT_80333258, 0.0f);
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
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);

    int baseY = 300;
    unsigned int nameX = static_cast<unsigned int>(
        -((static_cast<double>(FLOAT_80333364) * DOUBLE_80333298) - DOUBLE_80333288));

    if (x != 0) {
        baseY = 0x130;
    }

    CFont* font = CmakeFields(this).m_fonts[CMAKE_FONT_VALUE];
    font->SetShadow(1);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();
    font->renderFlags = (font->renderFlags & 0xEF) | 0x10;
    font->SetMargin(FLOAT_80333258);

    CColor rgba(
        0xFF, 0xFF, 0xFF,
        static_cast<unsigned char>(static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha)));
    font->SetColor(rgba);
    font->SetTlut(6);

    float textW = static_cast<float>(font->GetWidth(text));
    font->SetPosX(static_cast<float>(static_cast<int>(nameX)));
    font->SetPosY(static_cast<float>(baseY - 4));
    font->Draw(text);
    font->renderFlags &= 0xEF;
    DrawInit();

    if (y != 0) {
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

        int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
        GXColor drawColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
        GXSetChanMatColor(GX_COLOR0A0, drawColor);

        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x60 : 0x39));

        int cursorX = static_cast<int>(static_cast<float>(static_cast<int>(nameX)) + textW);
        MenuPcs.DrawRect(
            0,
            static_cast<float>(cursorX),
            static_cast<float>(baseY - 0x10),
            FLOAT_803332dc, FLOAT_803332b0,
            static_cast<float>((System.m_frameCounter & 7) << 5), FLOAT_80333254,
            FLOAT_80333258, FLOAT_80333258, 0.0f);
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
 * PAL Address: 0x801728bc
 * PAL Size: 864b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawCmakeYesNo(int yesNoSel, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3A));
    MenuPcs.DrawRect(
        0, FLOAT_80333348, FLOAT_803332a4, FLOAT_803332b0, FLOAT_803332dc,
        FLOAT_8033334c, FLOAT_80333284, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8, FLOAT_80333350, FLOAT_803332a4, FLOAT_803332b0, FLOAT_803332dc,
        FLOAT_8033334c, FLOAT_80333284, FLOAT_80333258, FLOAT_80333258, 0.0f);

    if (yesNoSel != 0) {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3D));
        MenuPcs.DrawRect(
            0, FLOAT_80333354, FLOAT_80333358, FLOAT_8033324c, FLOAT_803332b0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    }

    CFont* font = CmakeFields(this).m_fonts[CMAKE_FONT_VALUE];
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(1);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();
    font->SetTlut(7);

    GXColor rgba = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    font->SetColor(rgba);

    const char* yesStr = GetMenuStr(1);
    float yesW = static_cast<float>(font->GetWidth(yesStr));
    unsigned int yesX = static_cast<unsigned int>(
        (static_cast<float>(static_cast<double>(FLOAT_803332b0) - static_cast<double>(yesW)) * FLOAT_8033335c) +
        0x1D0);
    font->SetPosX(static_cast<float>(static_cast<int>(yesX)));
    font->SetPosY(FLOAT_80333360);
    font->Draw(yesStr);

    const char* noStr = GetMenuStr(2);
    float noW = static_cast<float>(font->GetWidth(noStr));
    unsigned int noX = static_cast<unsigned int>(
        (static_cast<float>(static_cast<double>(FLOAT_803332b0) - static_cast<double>(noW)) * FLOAT_8033335c) +
        0x218);
    font->SetPosX(static_cast<float>(static_cast<int>(noX)));
    font->SetPosY(FLOAT_80333360);
    font->Draw(noStr);

    DrawInit();
    if (yesNoSel != 0) {
        unsigned int cursorBase = noX;
        if (yesNoSel == 1) {
            cursorBase = yesX;
        }
        int frame = System.m_frameCounter & 7;
        DrawCursor(static_cast<int>(cursorBase) - 0x24 + frame, 0x175, alpha);
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
void CMenuPcs::CmakeOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x16) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
    *reinterpret_cast<short*>(state + 0x1E) = 0;
    *reinterpret_cast<unsigned char*>(state + 0x0B) = 0;
    *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
    *reinterpret_cast<short*>(state + 0x2E) = 0;
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
void CMenuPcs::CmakeCtrl()
{
    int state = MenuS32(this, 0x82C);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& step = *reinterpret_cast<short*>(state + 0x16);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& resultFlag = *reinterpret_cast<short*>(state + 0x2E);

    CalcSingCMake();

    if (resultFlag == 0) {
        return;
    }

    if (step == 0) {
        if (mode == 0) {
            step = 1;
            frame = 0;
            resultFlag = 0;
            *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
            *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) = 3;
        } else if (mode == 2) {
            MenuS16(this, 0x86A) = 999;
            *reinterpret_cast<short*>(state + 0x20) = -1;
            resultFlag = 0;
        }
        return;
    }

    if (mode < 2) {
        mode = static_cast<short>(mode + 1);
        frame = 0;
        resultFlag = 0;
        *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) = 3;
        return;
    }

    gCmakePreviousStep = static_cast<int>(step);

    if (step == 6) {
        step = static_cast<short>(*reinterpret_cast<short*>(state + 0x26) + 1);
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

    *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
    frame = 0;
    resultFlag = 0;
    *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) = 3;
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
void CMenuPcs::CmakeClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 0;
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
    *reinterpret_cast<short*>(state + 0x1E) = -1;
    *reinterpret_cast<short*>(state + 0x2E) = 0;
    *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
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
void CMenuPcs::CmakeDraw()
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
void CMenuPcs::CmakeNameOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 1;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    int state = MenuS32(this, 0x82C);
    int mcWork = MenuS32(this, 0x848);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& select = *reinterpret_cast<short*>(state + 0x26);
    short& row = *reinterpret_cast<short*>(state + 0x28);
    short& table = *reinterpret_cast<short*>(state + 0x2A);
    unsigned short down;
    unsigned short repeat;
    short& mcState = *reinterpret_cast<short*>(mcWork + 10);
    char* name = GetCmakeNameBuffer();

    bool padBusy = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        padBusy = true;
    }
    if (padBusy) {
        down = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        down = static_cast<unsigned short>(Pad.GetPadInputs()[0].buttonDown[0]);
    }

    padBusy = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        padBusy = true;
    }
    if (padBusy) {
        repeat = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        repeat = Pad.GetPadInputs()[0].repeatButton;
    }

    if (repeat == 0) {
        return 0;
    }

    if (mcState == 3) {
        int maxRow = (static_cast<int>(select) >> 31) + (static_cast<unsigned int>(select) > 9) + 4;
        if ((repeat & 0x8) != 0) {
            row = (row > 0) ? static_cast<short>(row - 1) : static_cast<short>(maxRow);
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            row = (row < maxRow) ? static_cast<short>(row + 1) : 0;
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0x1) != 0) {
            if (row < 5) {
                select = (select > 0) ? static_cast<short>(select - 1) : 0xB;
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            }
        } else if ((repeat & 0x2) != 0) {
            if (row < 5) {
                select = (select < 0xB) ? static_cast<short>(select + 1) : 0;
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            } else {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            }
        }

        if ((repeat & 0xF) == 0) {
            if ((down & 0x40) != 0) {
                if (table > 0) {
                    table = static_cast<short>(table - 1);
                } else {
                    table = 2;
                }
                Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
            } else if ((down & 0x20) != 0) {
                if (table < 2) {
                    table = static_cast<short>(table + 1);
                } else {
                    table = 0;
                }
                Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
            } else if ((down & 0x1000) != 0) {
                select = 0xB;
                row = 5;
                Sound.PlaySe(2, 0x40, 0x7F, 0);
                return 0;
            } else if ((down & 0x100) != 0) {
                size_t len = strlen(name);
                if (row < 5) {
                    if (len >= 7) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                        return 0;
                    }

                    const char* rowText = s_NameEntryStr[table * 5 + row];
                    size_t rowLen = strlen(rowText);
                    if (select < 0 || static_cast<size_t>(select) >= rowLen || rowText[select] == '\0') {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                        return 0;
                    }

                    char picked[12];
                    memset(picked, 0, 3);
                    picked[0] = rowText[select];
                    picked[1] = '\0';
                    strcat(name, picked, 0x12);
                    if (strlen(name) > 6) {
                        select = 0xB;
                        row = 5;
                    }
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                    return 0;
                }

                if (IsCmakeNameBlank(name)) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                    return 0;
                }

                if (IsDuplicateCmakeName(this, name)) {
                    short winX = 0;
                    short winY = 0;
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                    GetWinSize(0x14, &winX, &winY, 0);
                    SetMcWinInfo((int)winX, (int)winY);
                    mcState = 0;
                    return 0;
                }

                resultDir = 1;
                Sound.PlaySe(2, 0x40, 0x7F, 0);
                return 1;
            } else if ((down & 0x200) != 0) {
                size_t len = strlen(name);
                if (len == 0) {
                    resultDir = -1;
                    ChgModel(static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
                    Sound.PlaySe(0x34, 0x40, 0x7F, 0);
                    return -1;
                } else {
                    name[strlen(name) - 1] = '\0';
                    Sound.PlaySe(3, 0x40, 0x7F, 0);
                }
                return 0;
            }
        }
    } else if (mcState == 1 && (down & 0x300) != 0) {
        Sound.PlaySe(2, 0x40, 0x7F, 0);
        mcState = 2;
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
void CMenuPcs::CmakeNameClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    int state = MenuS32(this, 0x82C);
    short mode = *reinterpret_cast<short*>(state + 0x10);
    short resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short select = *reinterpret_cast<short*>(state + 0x26);
    short row = *reinterpret_cast<short*>(state + 0x28);
    short table = *reinterpret_cast<short*>(state + 0x2A);
    char* name = GetCmakeNameBuffer();
    float alpha = CalcCmakeFadeAlpha(this);
    float previewAlpha = alpha;
    float titleX = FLOAT_80333258;
    float titleAlpha = alpha;
    if (((gCmakePreviousStep == 2) && (mode == 0)) || ((mode == 2) && (resultDir > 0))) {
        previewAlpha = FLOAT_80333258;
    }
    if ((mode == 2) && (resultDir > 0)) {
        titleX = alpha;
        titleAlpha = FLOAT_80333258;
    }

    if (table < 0) {
        table = 0;
    } else if (table > 2) {
        table = 2;
    }
    if (select < 0) {
        select = 0;
    } else if (select > 0xB) {
        select = 0xB;
    }

    DrawWMFrame0(1, FLOAT_80333258);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor backdropColor = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, backdropColor);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0, FLOAT_80333254, 24.0f, FLOAT_803332dc, 336.0f,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8, FLOAT_803332e4, 24.0f, FLOAT_803332dc, 336.0f,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        MenuPcs.DrawRect(
            0, static_cast<float>(tileX), 24.0f, static_cast<float>(tileW), 336.0f,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        tileX += tileW;
    }

    int slot = static_cast<int>(MenuS16(this, 0x86A));
    int modelBlock = MenuS32(this, 0x814);
    if (*reinterpret_cast<int*>(modelBlock + (slot + 0x20) * 0x50) != 0) {
        *reinterpret_cast<unsigned short*>(modelBlock + 0x6E8) = 0xFF24;
        *reinterpret_cast<unsigned short*>(modelBlock + 0x6EA) = 4;
        DrawInit();

        CCharaPcs::CHandle* handle = GetCmakeCharaHandle(this, slot);
        if (handle->m_charaKind == 3) {
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x32));
            MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
            int previewA = static_cast<int>(static_cast<double>(FLOAT_80333240) * previewAlpha);
            GXColor previewColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(previewA)};
            GXSetChanMatColor(GX_COLOR0A0, previewColor);
            MenuPcs.DrawRect(
                0,
                FLOAT_80333244, FLOAT_80333248, FLOAT_8033324c, FLOAT_80333250,
                FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        } else {
            SetProjection(0x16);
            SetLight(2);
            *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0x9C) = previewAlpha;
            handle->Draw(5);
            RestoreProjection();
        }

        DrawInit();
    }

    DrawCmakeTitle(1, titleX, titleAlpha);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, 120.0f, 124.0f, 320.0f, 132.0f,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x68 : 0x41));
    MenuPcs.DrawRect(
        0, 168.0f, 172.0f, FLOAT_803332b0, FLOAT_803332b0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        0, 232.0f, 172.0f, FLOAT_803332b0, FLOAT_803332b0,
        FLOAT_803332b0, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    for (int i = 0; i < 3; i++) {
        float markAlpha = (i == table) ? alpha : alpha * 0.5f;
        DrawCmakeBallCursor(i == table ? 1 : 0, (System.m_frameCounter + i) & 7, markAlpha);
    }

    CFont* font = GetCmakeKeyboardFont(this);
    font->SetShadow(0);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    font->SetMargin(FLOAT_803332c4);
    font->SetColor(col);

    for (int i = 0; i < 5; i++) {
        const char* rowText = s_NameEntryStr[table * 5 + i];
        font->SetPosX(FLOAT_803332c8);
        font->SetPosY((108.0f + i * 32.0f) - FLOAT_803332f4);
        font->Draw(rowText);
    }

    reinterpret_cast<unsigned char*>(font)[0x24] &= 0xEF;
    DrawInit();

    if (mode == 1 && row < 5) {
        int cursorX = static_cast<int>(FLOAT_803332c8 + FLOAT_803332c0 * static_cast<float>(select));
        int cursorY = 112 + row * 32;
        DrawCursor(cursorX + (System.m_frameCounter & 7), cursorY, FLOAT_80333258);
    }

    int showNameCursor = ((mode == 1) && (row < 5) && (strlen(name) <= 6)) ? 1 : 0;
    DrawCmakeName(0, showNameCursor, name, alpha);
    DrawCmakeDecision((row > 4) ? 1 : 0, alpha);

    if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) != 3) {
        DrawMcWin(-1, 0);
        if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) == 1) {
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
void CMenuPcs::CmakeSexOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 2;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    int state = MenuS32(this, 0x82C);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& sel = *reinterpret_cast<short*>(state + 0x26);
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
            *reinterpret_cast<short*>(state + 0x1E) = 1;
            Sound.PlaySe(2, 0x40, 0x7F, 0);
        } else if (((repeat & 0x3) == 0) && ((down & 0x200) != 0)) {
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = -1;
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
void CMenuPcs::CmakeSexClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    float alpha = CalcCmakeFadeAlpha(this);
    DrawWMFrame0(1, FLOAT_80333258);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
    GXColor backdropColor = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, backdropColor);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0, FLOAT_80333254, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8, FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
    for (int x = 0x20; x < 0x260;) {
        int span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }
        MenuPcs.DrawRect(
            0, static_cast<float>(x), FLOAT_803332d8, static_cast<float>(span), FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        x += span;
    }

    DrawCmakePreviewChara(this);

    int panelAlpha = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor panelColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(panelAlpha)};
    GXSetChanMatColor(GX_COLOR0A0, panelColor);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
        FLOAT_80333254, FLOAT_80333254, 0.85f, 0.85f, 0.0f);
    DrawCmakeTitle(2, FLOAT_80333258, alpha);

    CFont* font = CmakeFields(this).m_fonts[CMAKE_FONT_LABEL];
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(0);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    CColor rgba(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    font->SetColor(rgba);

    float maxWidth = FLOAT_80333254;
    for (int i = 0; i < 2; ++i) {
        const char* txt = GetMenuStr(0x11 + i);
        float width = static_cast<float>(font->GetWidth(txt));
        if (maxWidth < width) {
            maxWidth = width;
        }
        float x = static_cast<float>(-(static_cast<double>(width) * DOUBLE_80333298 - DOUBLE_80333288));
        font->SetPosX(x);
        font->SetPosY(0x9C + i * 0x28 - FLOAT_803332f4);
        font->Draw(txt);
    }
    DrawInit();

    if (*reinterpret_cast<short*>(MenuS32(this, 0x82C) + 0x10) == 1) {
        int sel = *reinterpret_cast<short*>(MenuS32(this, 0x82C) + 0x26);
        int frame = System.m_frameCounter & 7;
        int cursorX = static_cast<int>(
            static_cast<double>(static_cast<float>(DOUBLE_80333288 - static_cast<double>(maxWidth) * DOUBLE_80333298) +
                                static_cast<float>(frame)) -
            static_cast<double>(maxWidth) * DOUBLE_80333298);
        int cursorY = static_cast<int>(FLOAT_80333334 + static_cast<float>(sel * 0x28));
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
void CMenuPcs::CmakeTribeOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 3;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
unsigned short CMenuPcs::CmakeTribeCtrl()
{
    int state = MenuS32(this, 0x82C);
    int mcWork = MenuS32(this, 0x848);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& tribe = *reinterpret_cast<short*>(state + 0x26);
    short& crest = *reinterpret_cast<short*>(state + 0x28);
    short selectField = *reinterpret_cast<short*>(state + 0x30);
    short& mcState = *reinterpret_cast<short*>(mcWork + 10);
    unsigned short down;
    unsigned short repeat;

    bool padBusy = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        padBusy = true;
    }
    if (padBusy) {
        down = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        down = static_cast<unsigned short>(Pad.GetPadInputs()[0].buttonDown[0]);
    }

    padBusy = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        padBusy = true;
    }
    if (padBusy) {
        repeat = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        repeat = Pad.GetPadInputs()[0].repeatButton;
    }

    if (repeat == 0) {
        return 0;
    }

    if (mcState == 3) {
        short& currentValue = *reinterpret_cast<short*>(state + 0x26 + selectField * 2);

        if ((repeat & 0x8) != 0) {
            if (currentValue == 0) {
                currentValue = 3;
            } else {
                currentValue = static_cast<short>(currentValue - 1);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            if (currentValue < 3) {
                currentValue = static_cast<short>(currentValue + 1);
            } else {
                currentValue = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0xC) != 0) {
            return 0;
        }

        if ((down & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            if (selectField == 0) {
                resultDir = -1;
                return 1;
            }

            *reinterpret_cast<short*>(state + 0x30) = static_cast<short>(selectField - 1);
            return 0;
        }

        if ((down & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            if (selectField == 0) {
                *reinterpret_cast<short*>(state + 0x30) = static_cast<short>(selectField + 1);
                return 0;
            }

            int duplicateSlot = 8;
            unsigned char* entry = reinterpret_cast<unsigned char*>(&Game);
            for (int slot = 0; slot < 8; slot += 2, entry += 0x1860) {
                if (((*reinterpret_cast<int*>(entry + 0x1794) != 0) &&
                     (*(entry + 0x1F96) != 1) &&
                     (*reinterpret_cast<unsigned short*>(entry + 0x17D0) == tribe) &&
                     (*reinterpret_cast<unsigned short*>(entry + 0x17D4) == crest) &&
                     (duplicateSlot = slot,
                      *reinterpret_cast<unsigned short*>(entry + 0x17D2) == s_CmakeInfo.m_gender)) ||
                    ((*reinterpret_cast<int*>(entry + 0x23C4) != 0) &&
                     (*(entry + 0x2BC6) != 1) &&
                     (*reinterpret_cast<unsigned short*>(entry + 0x2400) == tribe) &&
                     (*reinterpret_cast<unsigned short*>(entry + 0x2404) == crest) &&
                     (duplicateSlot = slot + 1,
                      *reinterpret_cast<unsigned short*>(entry + 0x2402) == s_CmakeInfo.m_gender))) {
                    break;
                }
                duplicateSlot = slot + 2;
            }

            if (duplicateSlot > 7) {
                s_CmakeInfo.m_tribe = static_cast<signed char>(tribe);
                s_CmakeInfo.m_hair = static_cast<signed char>(crest);
                ChgModel(static_cast<int>(MenuS16(this, 0x86A)),
                         static_cast<int>(s_CmakeInfo.m_tribe),
                         static_cast<int>(s_CmakeInfo.m_hair),
                         static_cast<int>(s_CmakeInfo.m_gender));
                resultDir = 1;
                return 1;
            }

            Sound.PlaySe(4, 0x40, 0x7F, 0);
            short winX = 0;
            short winY = 0;
            GetWinSize(0x15, &winX, &winY, 0);
            SetMcWinInfo(static_cast<int>(winX), static_cast<int>(winY));
            mcState = 0;
        }

        return 0;
    }

    if (mcState == 1 && (down & 0x300) != 0) {
        Sound.PlaySe(2, 0x40, 0x7F, 0);
        mcState = 2;
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
void CMenuPcs::CmakeTribeClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    float alpha = CalcCmakeFadeAlpha(this);
    int state = MenuS32(this, 0x82C);

    DrawWMFrame0(1, FLOAT_80333258);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor backdropColor = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, backdropColor);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        FLOAT_80333254, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8,
        FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        MenuPcs.DrawRect(
            0,
            static_cast<float>(tileX), FLOAT_803332d8, static_cast<float>(tileW), FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        tileX += tileW;
    }

    DrawCmakePreviewChara(this);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, FLOAT_80333278, FLOAT_8033327c, FLOAT_803332a4, FLOAT_80333284,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333318, 0.0f);

    DrawCmakeTitle(3, FLOAT_80333258, alpha);
    DrawCmakeCrest(MenuS16(this, 0x862), 0, 0, alpha);

    CFont* tribeFont = CmakeFields(this).m_fonts[CMAKE_FONT_LABEL];
    tribeFont->SetMargin(FLOAT_80333258);
    tribeFont->SetShadow(0);
    tribeFont->SetScale(FLOAT_80333258);
    tribeFont->DrawInit();
    CColor tribeRgba(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    tribeFont->SetColor(tribeRgba);

    for (int i = 0; i < 4; i++) {
        const char* txt = GetTribeStr(i);
        tribeFont->SetPosX(FLOAT_80333284);
        tribeFont->SetPosY(0x88 + i * 0x1C - FLOAT_803332f4);
        tribeFont->Draw(txt);
    }

    CFont* hairFont = CmakeFields(this).m_fonts[CMAKE_FONT_VALUE];
    hairFont->SetMargin(FLOAT_80333258);
    hairFont->SetShadow(1);
    hairFont->SetScale(FLOAT_80333258);
    hairFont->DrawInit();
    hairFont->SetColor(tribeRgba);
    hairFont->SetTlut(6);

    int hairBase = MenuS16(this, 0x862) * 8;
    if (s_CmakeInfo.m_gender != 0) {
        hairBase += 4;
    }

    for (int i = 0; i < 4; i++) {
        const char* txt = GetHairStr(hairBase + i);
        hairFont->SetPosX(FLOAT_8033331c);
        hairFont->SetPosY(0x88 + i * 0x1C - FLOAT_803332f4);
        hairFont->Draw(txt);
    }

    DrawInit();

    if (*reinterpret_cast<short*>(state + 0x10) == 1) {
        int select = *reinterpret_cast<short*>(state + 0x26);
        int frame = System.m_frameCounter & 7;
        int tribeCursorY = 0x88 + select * 0x1C;

        if (*reinterpret_cast<short*>(state + 0x30) == 0) {
            DrawCursor(static_cast<int>(FLOAT_80333320 + static_cast<float>(frame)), tribeCursorY, alpha);
        } else {
            if ((System.m_frameCounter & 1) != 0) {
                DrawCursor(static_cast<int>(FLOAT_80333320), tribeCursorY, alpha);
            }

            int hairCursorY = 0x88 + *reinterpret_cast<short*>(state + 0x28) * 0x1C;
            DrawCursor(static_cast<int>(FLOAT_80333324 + static_cast<float>(frame)), hairCursorY, alpha);
        }
    }

    if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) != 3) {
        DrawMcWin(-1, 0);
        if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) == 1) {
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
void CMenuPcs::CmakeJobOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 4;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
unsigned short CMenuPcs::CmakeJobCtrl()
{
    int state = MenuS32(this, 0x82C);
    int mcWork = MenuS32(this, 0x848);
    short& job = *reinterpret_cast<short*>(state + 0x26);
    unsigned short down;
    unsigned short repeat;
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& mcState = *reinterpret_cast<short*>(mcWork + 10);

    bool padBusy = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        padBusy = true;
    }
    if (padBusy) {
        down = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        down = static_cast<unsigned short>(Pad.GetPadInputs()[0].buttonDown[0]);
    }

    padBusy = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        padBusy = true;
    }
    if (padBusy) {
        repeat = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        repeat = Pad.GetPadInputs()[0].repeatButton;
    }

    if (repeat == 0) {
        return 0;
    }

    if (mcState == 3) {
        if ((repeat & 0x8) != 0) {
            if ((job % 4) == 0) {
                job = static_cast<short>(job + 3);
            } else {
                job = static_cast<short>(job - 1);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            if ((job % 4) < 3) {
                job = static_cast<short>(job + 1);
            } else {
                job = static_cast<short>(job - 3);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0x3) != 0) {
            if (job < 4) {
                job = static_cast<short>(job + 4);
            } else {
                job = static_cast<short>(job - 4);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0xF) == 0) {
            if ((down & 0x100) != 0) {
                int duplicateSlot = 8;
                unsigned char* group = reinterpret_cast<unsigned char*>(&Game);
                int slot = 0;
                for (int groupCount = 2; groupCount != 0; groupCount--) {
                    if (((slot != static_cast<int>(MenuS16(this, 0x86A))) &&
                         (*reinterpret_cast<int*>(group + 0x1794) != 0) &&
                         (*(group + 0x1F96) != 1) &&
                         (duplicateSlot = slot,
                          *reinterpret_cast<int*>(group + 0x179C) == static_cast<int>(job))) ||
                        (((slot + 1) != static_cast<int>(MenuS16(this, 0x86A))) &&
                         (*reinterpret_cast<int*>(group + 0x23C4) != 0) &&
                         (*(group + 0x2BC6) != 1) &&
                         (duplicateSlot = slot + 1,
                          *reinterpret_cast<int*>(group + 0x23CC) == static_cast<int>(job))) ||
                        (((slot + 2) != static_cast<int>(MenuS16(this, 0x86A))) &&
                         (*reinterpret_cast<int*>(group + 0x2FF4) != 0) &&
                         (*(group + 0x37F6) != 1) &&
                         (duplicateSlot = slot + 2,
                          *reinterpret_cast<int*>(group + 0x2FFC) == static_cast<int>(job))) ||
                        (((slot + 3) != static_cast<int>(MenuS16(this, 0x86A))) &&
                         (*reinterpret_cast<int*>(group + 0x3C24) != 0) &&
                         (*(group + 0x4426) != 1) &&
                         (duplicateSlot = slot + 3,
                          *reinterpret_cast<int*>(group + 0x3C2C) == static_cast<int>(job)))) {
                        break;
                    }

                    group += 0x30C0;
                    slot += 4;
                    duplicateSlot = slot;
                }

                if (duplicateSlot > 7) {
                    s_CmakeInfo.m_job = static_cast<signed char>(job);
                    resultDir = 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                    return 1;
                } else {
                    short winX = 0;
                    short winY = 0;
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                    GetWinSize(0x16, &winX, &winY, 0);
                    SetMcWinInfo((int)winX, (int)winY);
                    mcState = 0;
                    return 0;
                }
            } else if ((down & 0x200) != 0) {
                ChgModel(static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
                resultDir = -1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                return 1;
            }
        }
    } else if (mcState == 1 && (down & 0x300) != 0) {
        Sound.PlaySe(2, 0x40, 0x7F, 0);
        mcState = 2;
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
void CMenuPcs::CmakeJobClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    int state = MenuS32(this, 0x82C);
    short mode = *reinterpret_cast<short*>(state + 0x10);
    float alpha = CalcCmakeFadeAlpha(this);

    DrawWMFrame0(1, FLOAT_80333258);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor backdropColor = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, backdropColor);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        0.0f, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8,
        FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
    for (int x = 0x20; x < 0x260;) {
        int span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }

        MenuPcs.DrawRect(
            0,
            static_cast<float>(x), FLOAT_803332d8, static_cast<float>(span), FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        x += span;
    }

    DrawCmakePreviewChara(this);

    int panelAlpha = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor panelColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(panelAlpha)};
    GXSetChanMatColor(GX_COLOR0A0, panelColor);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0,
        FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    DrawCmakeTitle(5, FLOAT_80333258, alpha);

    CFont* font = CmakeFields(this).m_fonts[CMAKE_FONT_LABEL];
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(0);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();

    CColor textColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(panelAlpha));
    font->SetColor(textColor);

    for (int i = 0; i < 8; ++i) {
        const char* txt = GetJobStr(i);
        int x = (i < 4) ? 0x110 : 0x1A8;
        int row = i % 4;
        font->SetPosX(x);
        font->SetPosY(static_cast<float>(0x70 + row * 0x28) - FLOAT_803332f4);
        font->Draw(txt);
    }

    if (*reinterpret_cast<short*>(state + 0x10) == 1) {
        int sel = *reinterpret_cast<short*>(state + 0x26);
        int cursorX = (sel < 4) ? 0x110 : 0x1A8;
        int cursorY = 0x70 + ((sel < 4) ? sel : (sel - 4)) * 0x28;
        int cursorFrame = System.m_frameCounter & 7;
        DrawCursor(static_cast<int>((static_cast<float>(cursorX) - FLOAT_80333308) + static_cast<float>(cursorFrame)),
            cursorY, alpha);
    }

    if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) != 3) {
        DrawMcWin(-1, 0);
        if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) == 1) {
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
void CMenuPcs::CmakeResultOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 5;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    int state = MenuS32(this, 0x82C);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& sel = *reinterpret_cast<short*>(state + 0x26);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
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
void CMenuPcs::CmakeResultClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    int state = MenuS32(this, 0x82C);
    short mode = *reinterpret_cast<short*>(state + 0x10);
    short resultDir = *reinterpret_cast<short*>(state + 0x1E);
    float alpha = CalcCmakeFadeAlpha(this);

    DrawWMFrame0(1, FLOAT_80333258);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor backdropColor = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, backdropColor);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        FLOAT_80333254, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8,
        FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        MenuPcs.DrawRect(
            0,
            static_cast<float>(tileX), FLOAT_803332d8, static_cast<float>(tileW), FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        tileX += tileW;
    }

    int slot = static_cast<int>(MenuS16(this, 0x86A));
    int modelBlock = MenuS32(this, 0x814);
    if (*reinterpret_cast<int*>(modelBlock + (slot + 0x20) * 0x50) != 0) {
        *reinterpret_cast<unsigned short*>(modelBlock + 0x6E8) = 0xFF24;
        *reinterpret_cast<unsigned short*>(modelBlock + 0x6EA) = 4;
        DrawInit();

        CCharaPcs::CHandle* handle = GetCmakeCharaHandle(this, slot);
        if (handle->m_charaKind == 3) {
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x32));
            MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
            GXColor charaColor = {0xFF, 0xFF, 0xFF, 0xFF};
            GXSetChanMatColor(GX_COLOR0A0, charaColor);
            MenuPcs.DrawRect(
                0,
                FLOAT_80333244, FLOAT_80333248, FLOAT_8033324c, FLOAT_80333250,
                FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        } else {
            SetProjection(0x16);
            SetLight(2);
            *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(handle->m_model) + 0x9C) = FLOAT_80333258;
            handle->Draw(5);
            RestoreProjection();
        }

        DrawInit();
    }

    float panelAlphaValue = alpha;
    if ((mode == 2) && (resultDir < 0)) {
        panelAlphaValue = FLOAT_80333258;
    }
    int panelAlpha = static_cast<int>(static_cast<double>(FLOAT_80333240) * panelAlphaValue);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor panelColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(panelAlpha)};
    GXSetChanMatColor(GX_COLOR0A0, panelColor);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    if ((mode == 2) && (resultDir > 0)) {
        DrawCmakeTitle(6, FLOAT_80333258, alpha);
    } else {
        DrawCmakeTitle(6, alpha, FLOAT_80333258);
    }

    float textAlpha = alpha;
    if ((*reinterpret_cast<short*>(state + 0x10) == 2) && (*reinterpret_cast<short*>(state + 0x1E) < 0)) {
        textAlpha = FLOAT_80333258;
    }

    DrawCmakeCrest(static_cast<int>(s_CmakeInfo.m_tribe), 0, 0, textAlpha);

    if (*reinterpret_cast<short*>(state + 0x10) == 1) {
        DrawCmakeYesNo(*reinterpret_cast<short*>(state + 0x26) + 1, alpha);
    } else {
        DrawCmakeYesNo(0, alpha);
    }

    CFont* labelFont = CmakeFields(this).m_fonts[CMAKE_FONT_LABEL];
    labelFont->SetMargin(FLOAT_80333258);
    labelFont->SetShadow(0);
    labelFont->SetScale(FLOAT_80333258);
    labelFont->DrawInit();

    int textColor = static_cast<int>(static_cast<double>(FLOAT_80333240) * textAlpha);
    CColor color(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textColor));
    labelFont->SetColor(color);

    float labelWidths[4];
    for (int i = 0; i < 4; i++) {
        const char* label = GetMenuStr(i + 0x2A);

        labelWidths[i] = FLOAT_803332f0 + labelFont->GetWidth(label);
        labelFont->SetPosX(FLOAT_803332f0);
        labelFont->SetPosY(static_cast<float>(0x70 + i * 0x28) - FLOAT_803332f4);
        labelFont->Draw(label);
    }

    CFont* valueFont = CmakeFields(this).m_fonts[CMAKE_FONT_VALUE];
    valueFont->SetMargin(FLOAT_80333258);
    valueFont->SetShadow(1);
    valueFont->SetScale(FLOAT_80333258);
    valueFont->DrawInit();
    valueFont->SetColor(color);
    valueFont->SetTlut(6);

    char tribeWithSlash[0x40];
    for (int i = 0; i < 4; i++) {
        const char* value = "";
        if (i == 0) {
            value = s_CmakeInfo.m_name;
        } else if (i == 1) {
            value = GetMenuStr(static_cast<int>(s_CmakeInfo.m_gender) + 0x11);
        } else if (i == 2) {
            value = GetTribeStr(static_cast<int>(s_CmakeInfo.m_tribe));

            strcpy(tribeWithSlash, value);
            strcat(tribeWithSlash, "/", sizeof(tribeWithSlash));
            value = tribeWithSlash;
        } else {
            value = GetJobStr(static_cast<int>(s_CmakeInfo.m_job));
        }

        float x = FLOAT_803332fc + labelWidths[i];
        float y = static_cast<float>(0x70 + i * 0x28) - FLOAT_803332f4;
        float valueWidth = valueFont->GetWidth(value);
        valueFont->SetPosX(x);
        valueFont->SetPosY(y);
        valueFont->Draw(value);

        if (i == 2) {
            int hairIndex = static_cast<int>(s_CmakeInfo.m_tribe) * 8;
            if (s_CmakeInfo.m_gender != 0) {
                hairIndex += 4;
            }

            const char* hair = GetHairStr(hairIndex + static_cast<int>(s_CmakeInfo.m_hair));

            valueFont->SetPosX(FLOAT_80333300 + x + valueWidth);
            valueFont->SetPosY(y);
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
void CMenuPcs::CmakeResultOpen1()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    int state = MenuS32(this, 0x82C);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
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
void CMenuPcs::CmakeResultClose1()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
    int state = MenuS32(this, 0x82C);
    short mode = *reinterpret_cast<short*>(state + 0x10);
    float alpha = CalcCmakeFadeAlpha(this);
    float popupAlpha = (mode == 0) ? FLOAT_80333258 : alpha;
    float textAlpha = (mode == 0) ? FLOAT_80333258 : alpha;

    DrawWMFrame0(1, FLOAT_80333258);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    GXColor backdropColor = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, backdropColor);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x3F));
    MenuPcs.DrawRect(
        0,
        FLOAT_80333254, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        8,
        FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x40));
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        MenuPcs.DrawRect(
            0,
            static_cast<float>(tileX), FLOAT_803332d8, static_cast<float>(tileW), FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        tileX += tileW;
    }

    DrawCmakePreviewChara(this);

    DrawCmakePopupPanel(this, popupAlpha, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
        FLOAT_80333258, FLOAT_80333258);
    DrawCmakeTitle(7, FLOAT_80333258, alpha);
    DrawCmakeCrest(static_cast<int>(s_CmakeInfo.m_tribe), 0, 0, textAlpha);

    CFont* labelFont = CmakeFields(this).m_fonts[CMAKE_FONT_LABEL];
    labelFont->SetMargin(FLOAT_80333258);
    labelFont->SetShadow(0);
    labelFont->SetScale(FLOAT_80333258);
    labelFont->DrawInit();

    int textColor = static_cast<int>(static_cast<double>(FLOAT_80333240) * textAlpha);
    GXColor color = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textColor)};
    labelFont->SetColor(color);

    float labelWidths[4];
    for (int i = 0; i < 4; i++) {
        const char* txt = GetMenuStr(0x2A + i);
        if (txt == 0) {
            txt = "";
        }

        labelWidths[i] = FLOAT_803332f0 + static_cast<float>(labelFont->GetWidth(txt));
        labelFont->SetPosX(FLOAT_803332f0);
        labelFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
        labelFont->Draw(txt);
    }

    CFont* valueFont = CmakeFields(this).m_fonts[CMAKE_FONT_VALUE];
    valueFont->SetMargin(FLOAT_80333258);
    valueFont->SetShadow(1);
    valueFont->SetScale(FLOAT_80333258);
    valueFont->DrawInit();
    valueFont->SetColor(color);
    valueFont->SetTlut(6);

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
            break;
        default:
            txt = GetJobStr(s_CmakeInfo.m_job);
            break;
        }

        valueFont->SetPosX(FLOAT_803332fc + labelWidths[i]);
        valueFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
        valueFont->Draw(txt);

        if (i == 2) {
            int hairIndex = s_CmakeInfo.m_tribe * 8;
            if (s_CmakeInfo.m_gender != 0) {
                hairIndex += 4;
            }

            const char* hairTxt = GetHairStr(hairIndex + s_CmakeInfo.m_hair);

            valueFont->SetPosX(
                FLOAT_80333300 +
                (FLOAT_803332fc + labelWidths[i] + static_cast<float>(valueFont->GetWidth(txt))));
            valueFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
            valueFont->Draw(hairTxt);
        }
    }

    DrawInit();

    if (*reinterpret_cast<short*>(state + 0x10) == 1) {
        int cursorX = static_cast<int>(FLOAT_80333304 + static_cast<float>(System.m_frameCounter & 7));
        int cursorY = 0x70 + *reinterpret_cast<short*>(state + 0x26) * 0x28;
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
 * PAL Address: 0x8016d940
 * PAL Size: 1940b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned short CMenuPcs::CmakeVillageCtrl()
{
    unsigned char* villageWork = static_cast<unsigned char*>(CmakeFields(this).m_villageWork);
    short& select = *reinterpret_cast<short*>(villageWork + 0x26);
    short& row = *reinterpret_cast<short*>(villageWork + 0x28);
    short& table = *reinterpret_cast<short*>(villageWork + 0x2A);
    unsigned short down;
    unsigned short repeat;
    char picked[8];
    int len = strlen(s_CmakeInfo.m_name);

    bool padBusy = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        padBusy = true;
    }
    if (padBusy) {
        down = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        down = static_cast<unsigned short>(Pad.GetPadInputs()[0].buttonDown[0]);
    }

    padBusy = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        padBusy = true;
    }
    if (padBusy) {
        repeat = 0;
    } else {
        __cntlzw(static_cast<unsigned int>(Pad._448_4_));
        repeat = Pad.GetPadInputs()[0].repeatButton;
    }

    if (repeat == 0) {
        return 0;
    }

    int maxRow = (select < 10) ? 4 : 5;
    if ((repeat & 0x4) != 0) {
        row = (row < maxRow) ? static_cast<short>(row + 1) : 0;
        Sound.PlaySe(1, 0x40, 0x7f, 0);
    } else if ((repeat & 0x8) != 0) {
        row = (row > 0) ? static_cast<short>(row - 1) : static_cast<short>(maxRow);
        Sound.PlaySe(1, 0x40, 0x7f, 0);
    }

    if ((repeat & 0x1) != 0) {
        if (row < 5) {
            if (select > 0) {
                select = static_cast<short>(select - 1);
            } else {
                select = 0xB;
            }
            Sound.PlaySe(1, 0x40, 0x7f, 0);
        } else {
            Sound.PlaySe(4, 0x40, 0x7f, 0);
        }
    } else if ((repeat & 0x2) != 0) {
        if (row < 5) {
            if (select < 0xB) {
                select = static_cast<short>(select + 1);
            } else {
                select = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7f, 0);
        } else {
            Sound.PlaySe(4, 0x40, 0x7f, 0);
        }
    }

    if ((repeat & 0xF) != 0) {
        return 0;
    }

    if ((down & 0x40) != 0) {
        if (table > 0) {
            table = static_cast<short>(table - 1);
        } else {
            table = 2;
        }
        Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
    } else if ((down & 0x20) != 0) {
        if (table < 2) {
            table = static_cast<short>(table + 1);
        } else {
            table = 0;
        }
        Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
    }

    if ((down & 0x1000) != 0) {
        select = 0xB;
        row = 5;
        Sound.PlaySe(2, 0x40, 0x7f, 0);
        return 0;
    }

    if ((down & 0x200) != 0) {
        if (len == 0) {
            Sound.PlaySe(4, 0x40, 0x7f, 0);
        } else {
            s_CmakeInfo.m_name[len - 1] = '\0';
            Sound.PlaySe(3, 0x40, 0x7f, 0);
        }
        return 0;
    }

    if ((down & 0x100) == 0) {
        return 0;
    }

    if (row > 4) {
        bool blankName = true;
        for (const char* it = s_CmakeInfo.m_name; *it != '\0'; ++it) {
            if (*it != ' ') {
                blankName = false;
                break;
            }
        }

        if (blankName) {
            Sound.PlaySe(4, 0x40, 0x7f, 0);
            return 0;
        }

        StoreCmakeVillageName();
        Sound.PlaySe(2, 0x40, 0x7f, 0);
        *reinterpret_cast<short*>(villageWork + 0x1E) = 1;
        return 1;
    }

    if (len >= 7) {
        Sound.PlaySe(4, 0x40, 0x7f, 0);
        return 0;
    }

    const char* rowText = s_NameEntryStr[table * 5 + row];
    int rowLen = strlen(rowText);
    if (select < 0 || select >= rowLen) {
        Sound.PlaySe(4, 0x40, 0x7f, 0);
        return 0;
    }

    memset(picked, 0, 3);
    picked[0] = '\0';
    picked[0] = rowText[select];
    picked[1] = '\0';
    if (picked[0] == '\0') {
        Sound.PlaySe(4, 0x40, 0x7f, 0);
        return 0;
    }

    strcat(s_CmakeInfo.m_name, picked, 0x11);
    if (strlen(s_CmakeInfo.m_name) > 6) {
        select = 0xB;
        row = 5;
    }

    Sound.PlaySe(2, 0x40, 0x7f, 0);
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
void CMenuPcs::CmakeVillageClose()
{
    MenuU8(this, 0x16) = 0;
    destroyVillageMenu();
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
    unsigned char* villageWork = static_cast<unsigned char*>(CmakeFields(this).m_villageWork);
    short mode = *reinterpret_cast<short*>(villageWork + 0x10);
    int frame = static_cast<int>(*reinterpret_cast<short*>(villageWork + 0x22)) - 1;
    float alpha;

    if (frame < 0) {
        frame = 0;
    }

    if (mode == 0) {
        alpha = static_cast<float>(DOUBLE_80333268 * static_cast<double>(frame));
    } else if (mode == 1) {
        alpha = FLOAT_80333258;
    } else {
        alpha = static_cast<float>(DOUBLE_80333270 - DOUBLE_80333268 * static_cast<double>(frame));
    }

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    MenuPcs.DrawRect(
        0, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    DrawCmakeTitle(0, FLOAT_80333258, alpha);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A));
    float panelX = -(FLOAT_80333290 * static_cast<float>(DOUBLE_80333298) - static_cast<float>(DOUBLE_80333288));
    MenuPcs.DrawRect(
        0, panelX, FLOAT_803332a0, FLOAT_80333290, FLOAT_8033327c,
        FLOAT_80333254, FLOAT_803332a4, FLOAT_80333258, FLOAT_80333258, 0.0f);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
    GXSetChanMatColor(GX_COLOR0A0, col);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 0x68 : 0x41));
    MenuPcs.DrawRect(
        0, FLOAT_803332a8, FLOAT_803332ac, FLOAT_803332b0, FLOAT_803332b0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    MenuPcs.DrawRect(
        0, static_cast<float>(DOUBLE_803333b8), FLOAT_803332ac, FLOAT_803332b0, FLOAT_803332b0,
        FLOAT_803332b0, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    if (mode == 1 && *reinterpret_cast<short*>(villageWork + 0x28) < 5) {
        short row = *reinterpret_cast<short*>(villageWork + 0x28);
        unsigned int cursorX = static_cast<unsigned int>(
            FLOAT_803332c0 * static_cast<float>(*reinterpret_cast<short*>(villageWork + 0x26)) + 0xE5);
        GXColor cursorColor = {0xFF, 0xFF, 0xFF, 0xFF};
        GXSetChanMatColor(GX_COLOR0A0, cursorColor);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((MenuS16(this, 0x86C) != 0) ? 100 : 0x3D));
        MenuPcs.DrawRect(
            0,
            static_cast<float>(static_cast<int>(cursorX)), 99.0f + row * 32.0f, FLOAT_803332b0, FLOAT_803332b0,
            FLOAT_8033324c, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    }

    CFont* font = GetCmakeKeyboardFont(this);
    font->SetShadow(0);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();
    reinterpret_cast<unsigned char*>(font)[0x24] = (reinterpret_cast<unsigned char*>(font)[0x24] & 0xEF) | 0x10;
    font->SetMargin(FLOAT_803332c4);
    font->SetColor(col);

    for (int i = 0; i < 5; i++) {
        const char* rowText = s_NameEntryStr[*reinterpret_cast<short*>(villageWork + 0x2A) * 5 + i];
        font->SetPosX(FLOAT_803332c8);
        font->SetPosY(static_cast<float>(0x6C + i * 0x20));
        font->Draw(rowText);
    }

    reinterpret_cast<unsigned char*>(font)[0x24] &= 0xEF;

    DrawInit();
    if (mode == 1 && *reinterpret_cast<short*>(villageWork + 0x28) < 5) {
        int wobble = System.m_frameCounter & 7;
        DrawCursor(
            static_cast<int>(FLOAT_803332c8 + *reinterpret_cast<short*>(villageWork + 0x26) * FLOAT_803332c0) + wobble,
            *reinterpret_cast<short*>(villageWork + 0x28) * 0x20 + 0x70, FLOAT_80333258);
    }

    int showNameCursor = __cntlzw(static_cast<unsigned int>(1 - *reinterpret_cast<short*>(villageWork + 0x10))) >> 5;
    if (*reinterpret_cast<short*>(villageWork + 0x28) > 4) {
        showNameCursor = 0;
    }
    if (strlen(s_CmakeInfo.m_name) > 6) {
        showNameCursor = 0;
    }
    DrawCmakeName(1, showNameCursor, s_CmakeInfo.m_name, alpha);
    DrawCmakeDecision((static_cast<int>(*reinterpret_cast<short*>(villageWork + 0x28)) >> 31) +
        (static_cast<unsigned int>(static_cast<int>(*reinterpret_cast<short*>(villageWork + 0x28))) > 4), alpha);
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
void CMenuPcs::SetSingMakeChara()
{
    int slot = static_cast<int>(MenuS16(this, 0x86A));
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
void CMenuPcs::createVillageMenu()
{
    if (MenuS16(this, 0x86C) == 0) {
        MenuU8(this, 0x16) = 1;
        calcVillageMenu();
    }
}
#endif

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
    if (MenuS16(this, 0x86C) != 0) {
        if (Game.m_gameWork.m_menuStageMode == 0) {
            CFont*& font = CmakeFields(this).m_fonts[CMAKE_FONT_VILLAGE];
            if (font != 0) {
                ReleaseRefObject(font);
                font = 0;
            }
        }

        freeTexture(8, 1, 0x60, 9);

        void*& villageWork = CmakeFields(this).m_villageWork;
        if (villageWork != nullptr) {
            operator delete(villageWork);
            villageWork = nullptr;
        }

        MenuS16(this, 0x86C) = 0;
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
    if (MenuU8(this, 0x16) != 0) {
        if (MenuS16(this, 0x86C) == 0 && MenuU8(this, 0x16) != 0) {
            if (Game.m_gameWork.m_menuStageMode == 0) {
                char path[128];
                const char* language = Game.GetLangString();
                sprintf(path, s_menuSubfontPathFmt, language);
                loadFont(2, path, 4, -1);
            }

            loadTexture(PTR_s_world2, 8, 1, s_cmakeWorldTextureTable, 0x60, 9, 3);

            CMemory::CStage* stage = CmakeFields(this).m_menuStage;
            void*& villageWork = CmakeFields(this).m_villageWork;
            villageWork = operator new(0x48, stage, const_cast<char*>(s_cmake_cpp), 0xCB3);
            memset(villageWork, 0, 0x48);
            LoadCmakeVillageName();
            MenuS16(this, 0x86C) = 1;
        }
    }

    short active = MenuS16(this, 0x86C);
    if (active != 0) {
        if (MenuU8(this, 0x16) == 0) {
            if (active != 0) {
                if (Game.m_gameWork.m_menuStageMode == 0) {
                    CFont*& font = CmakeFields(this).m_fonts[CMAKE_FONT_VILLAGE];
                    if (font != 0) {
                        ReleaseRefObject(font);
                        font = 0;
                    }
                }

                freeTexture(8, 1, 0x60, 9);
                void*& villageWork = CmakeFields(this).m_villageWork;
                if (villageWork != nullptr) {
                    operator delete(villageWork);
                    villageWork = nullptr;
                }
                MenuS16(this, 0x86C) = 0;
            }
        } else {
            unsigned char* villageWork = static_cast<unsigned char*>(CmakeFields(this).m_villageWork);
            unsigned short result = 0;
            short& mode = *reinterpret_cast<short*>(villageWork + 0x10);
            short& frame = *reinterpret_cast<short*>(villageWork + 0x22);

            if (mode == 0) {
                if (frame < 10) {
                    frame = frame + 1;
                    result = 0;
                } else {
                    result = 1;
                }
            } else if (mode == 1) {
                result = CmakeVillageCtrl();
            } else if (frame < 10) {
                frame = frame + 1;
                result = 0;
            } else {
                result = 1;
            }

            *reinterpret_cast<unsigned short*>(villageWork + 0x2E) = result;
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
    if (MenuS16(this, 0x86C) != 0) {
        unsigned char* villageWork = static_cast<unsigned char*>(CmakeFields(this).m_villageWork);
        CmakeVillageDraw();
        if (*reinterpret_cast<short*>(villageWork + 0x2E) != 0) {
            short& mode = *reinterpret_cast<short*>(villageWork + 0x10);
            if (mode < 2) {
                mode = mode + 1;
            } else {
                MenuU8(this, 0x16) = 0;
                CallWorldParam(10, 0, 0);
            }
            *reinterpret_cast<short*>(villageWork + 0x22) = 0;
        }
    }
}

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
    int slot = static_cast<int>(MenuS16(this, 0x86A));
    CCharaPcs::CHandle* handle = GetCmakeCharaHandle(this, slot);
    CChara::CModel* model = handle->m_model;
    unsigned char* modelWork = reinterpret_cast<unsigned char*>(MenuS32(this, 0x814) + slot * 0x50 + 0xA00);

    if (model == nullptr || *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(model) + 0xB0) == 0) {
        *reinterpret_cast<int*>(modelWork + 0x00) = 0;
        return;
    }

    unsigned char* animWork = reinterpret_cast<unsigned char*>(MenuS32(this, 0x824) + slot * 0x34);
    if (animWork[0x0C] == 1) {
        *reinterpret_cast<float*>(modelWork + 0x2C) = FLOAT_8033325c;
        SetAnim(slot);
        animWork[0x0C] = 0;
    }

    *reinterpret_cast<int*>(modelWork + 0x00) = 1;
    if (handle->m_charaKind != 3) {
        Mtx scaleMtx;
        Mtx rotXMtx;
        Mtx rotYMtx;

        *reinterpret_cast<float*>(modelWork + 0x1C) = FLOAT_80333254;
        *reinterpret_cast<float*>(modelWork + 0x20) = FLOAT_80333260;
        *reinterpret_cast<float*>(modelWork + 0x24) = FLOAT_80333254;
        *reinterpret_cast<float*>(modelWork + 0x34) = FLOAT_80333264;
        *reinterpret_cast<float*>(modelWork + 0x38) = FLOAT_80333264;
        *reinterpret_cast<float*>(modelWork + 0x3C) = FLOAT_80333264;

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
        model->SetMatrix(scaleMtx);
        model->CalcMatrix();
        model->CalcSkin();
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
