#include "ffcc/cmake.h"
#include "ffcc/chara.h"
#include "ffcc/fontman.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/linkage.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" void __dl__FPv(void*);
extern "C" void freeTexture__8CMenuPcsFiiii(CMenuPcs*, int, int, int, int);
extern "C" void CmakeVillageDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned short CmakeVillageCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" void CallWorldParam__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void ChgModel__8CMenuPcsFiiii(CMenuPcs*, int, int, int, int);
extern "C" void SetAnim__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void PCAnimCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" void InitFrame0Info__8CMenuPcsFv(CMenuPcs*);
extern "C" void CalcWMFrame0__8CMenuPcsFi(CMenuPcs*, int);
extern "C" unsigned short GetButtonRepeat__8CMenuPcsFi(CMenuPcs*, int);
extern "C" unsigned short GetButtonDown__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void SetMatrix__Q26CChara6CModelFPA4_f(CChara::CModel*, Mtx);
extern "C" void CalcMatrix__Q26CChara6CModelFv(CChara::CModel*);
extern "C" void CalcSkin__Q26CChara6CModelFv(CChara::CModel*);
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
extern "C" float FLOAT_80333318;
extern "C" float FLOAT_8033331c;
extern "C" float FLOAT_80333320;
extern "C" float FLOAT_80333324;
extern "C" float FLOAT_803333a8;
extern "C" float FLOAT_803333ac;
extern "C" float FLOAT_803333b0;
extern "C" float FLOAT_803333c8;
extern "C" float FLOAT_80333304;
extern "C" float FLOAT_803332c0;
extern "C" float FLOAT_803332c4;
extern "C" float FLOAT_803332c8;
extern "C" double DOUBLE_803332d0;
extern "C" double DOUBLE_80333270;
extern "C" double DOUBLE_80333268;
extern "C" double DOUBLE_80333288;
extern "C" double DOUBLE_80333298;
extern "C" double DOUBLE_803333a0;
extern "C" double DOUBLE_803333b8;
extern "C" double DOUBLE_803333c0;
extern "C" int DAT_8032ef10;
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void loadFont__8CMenuPcsFiPcii(CMenuPcs*, int, char*, int, int);
extern "C" void loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(CMenuPcs*, char**, int, int, void*, int, int, int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(void*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(void*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(void*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawInit__8CMenuPcsFv(void*);
extern "C" void* __ct__6CColorFUcUcUcUc(void*, unsigned char, unsigned char, unsigned char, unsigned char);
extern "C" const char* GetMenuStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" void DrawWMFrame0__8CMenuPcsFif(CMenuPcs*, int, float);
extern "C" void SetProjection__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void SetLight__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void RestoreProjection__8CMenuPcsFv(CMenuPcs*);
extern "C" void Draw__Q29CCharaPcs7CHandleFi(void*, int);
extern "C" const char* GetJobStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* GetTribeStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" const char* GetHairStr__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void DrawMcWin__8CMenuPcsFss(CMenuPcs*, short, short);
extern "C" void DrawMcWinMess__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" void GetWinSize__8CMenuPcsFiPsPsi(CMenuPcs*, int, short*, short*, int);
extern "C" void SetMcWinInfo__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" char s_dvd__smenu_subfont_fnt_801e3020[];
extern "C" char* PTR_s_world2_802159a4[];
extern "C" int DAT_802159c8;
extern "C" {
static const char s_cmake_cpp_801e3038[] = "cmake.cpp";
}

struct CmakeInfo {
    char m_name[0x12];
    signed char m_gender;
    signed char m_tribe;
    signed char m_hair;
    signed char m_job;
};

static CmakeInfo s_CmakeInfo;
static char s_CmakeVillageName[0x12];

static inline void* MenuPcsVoid()
{
    return &MenuPcs;
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

static inline void ReleaseRefObject(void* object)
{
    if (object == nullptr) {
        return;
    }

    int* raw = reinterpret_cast<int*>(object);
    int refCount = raw[1] - 1;
    raw[1] = refCount;
    if (refCount == 0) {
        reinterpret_cast<void (*)(void*, int)>(*reinterpret_cast<int*>(raw[0] + 8))(object, 1);
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
    DrawInit__8CMenuPcsFv(menu);

    int handle = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(menu) + 0x7F4 + slot * 4);
    if (*reinterpret_cast<int*>(handle) == 3) {
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x32);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);
        GXColor col = {0xFF, 0xFF, 0xFF, 0xFF};
        GXSetChanMatColor(GX_COLOR0A0, col);
        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0,
            FLOAT_80333244, FLOAT_80333248, FLOAT_8033324c, FLOAT_80333250,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    } else {
        SetProjection__8CMenuPcsFi(menu, 0x16);
        SetLight__8CMenuPcsFi(menu, 2);
        int model = *reinterpret_cast<int*>(handle + 0x168);
        *reinterpret_cast<float*>(model + 0x9C) = alpha;
        Draw__Q29CCharaPcs7CHandleFi(reinterpret_cast<void*>(handle), 5);
        RestoreProjection__8CMenuPcsFv(menu);
    }

    DrawInit__8CMenuPcsFv(menu);
}

static inline void DrawCmakePreviewChara(CMenuPcs* menu)
{
    DrawCmakePreviewCharaAlpha(menu, FLOAT_80333258);
}

static inline void DrawCmakeSelectionBackdrop(CMenuPcs* menu)
{
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    GXColor col = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, col);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x3F);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0,
        0.0f, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 8,
        FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x40);
    for (int x = 0x20; x < 0x260; x += 0x20) {
        int span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }

        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0,
            (float)x, FLOAT_803332d8, (float)span, FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    }

    DrawInit__8CMenuPcsFv(menu);
}

static inline void DrawCmakePopupPanel(CMenuPcs* menu, float alpha, float x, float y, float w, float h, float scaleX, float scaleY)
{
    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(menu, 0x86C) != 0) ? 0x61 : 0x3A);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, x, y, w, h,
        FLOAT_80333254, FLOAT_80333254, scaleX, scaleY, 0.0f);
}

static inline void DrawCmakeMcOverlay(CMenuPcs* menu, int messageId)
{
    int mcState = *reinterpret_cast<short*>(MenuS32(menu, 0x848) + 10);

    DrawInit__8CMenuPcsFv(menu);
    if (mcState == 3) {
        return;
    }

    DrawMcWin__8CMenuPcsFss(menu, -1, 0);
    if (mcState == 1) {
        DrawMcWinMess__8CMenuPcsFii(menu, messageId, 0);
    }
}

static inline unsigned char* GetCmakeRosterEntry(CMenuPcs* menu, int slot)
{
    return reinterpret_cast<unsigned char*>(MenuS32(menu, 0x814) + 0x7930 + slot * 0xC30);
}

static int FindDuplicateCmakeJob(CMenuPcs* menu, int selectedJob)
{
    int activeSlot = static_cast<int>(MenuS16(menu, 0x86A));

    for (int slot = 0; slot < 8; slot++) {
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
        if ((*reinterpret_cast<int*>(entry + 0x179C) & 0xFF) == selectedJob) {
            return slot;
        }
    }

    return -1;
}

static bool IsDuplicateCmakeTribeHair(CMenuPcs* menu, int tribe, int hair, int sex)
{
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
        if (*reinterpret_cast<unsigned short*>(entry + 0x17D0) != tribe) {
            continue;
        }
        if (*reinterpret_cast<unsigned short*>(entry + 0x17D4) != hair) {
            continue;
        }
        if (*reinterpret_cast<unsigned short*>(entry + 0x17D2) != sex) {
            continue;
        }

        return true;
    }

    return false;
}

static inline CFont* GetCmakeKeyboardFont(CMenuPcs* menu)
{
    if (MenuS16(menu, 0x86C) == 0) {
        return *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(menu) + 0xFC);
    }
    return *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(menu) + 0x108);
}

static const char* const s_cmakeNameRows[] = {
    "ABCDEFGHIJKL",
    "MNOPQRSTUVWX",
    "YZ.-'      ",
    "0123456789!?",
    " /+*=_:;(), ",
    "abcdefghijkl",
    "mnopqrstuvwx",
    "yz.-'      ",
    "0123456789!?",
    " /+*=_:;(), ",
    "ABCDEFGHIJKL",
    "MNOPQRSTUVWX",
    "YZ!?-+*/=<>",
    "0123456789@#",
    " .,:;'\"()[] "
};

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
        InitFrame0Info__8CMenuPcsFv(this);
        memset(&s_CmakeInfo, 0, sizeof(s_CmakeInfo));
        *reinterpret_cast<unsigned char*>(state + 0x0B) = 1;
        *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
        DAT_8032ef10 = -1;
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
            CalcWMFrame0__8CMenuPcsFi(this, frame - 10);
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
            CalcWMFrame0__8CMenuPcsFi(this, -frame);
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
            resultFlag = 0;
            CmakeNameCtrl();
            result = static_cast<unsigned short>(resultFlag);
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            if (resultDir < 0) {
                ChgModel__8CMenuPcsFiiii(this, static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
            }
            result = 1;
        }
        break;
    case 2:
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
            resultFlag = 0;
            CmakeSexCtrl();
            if (resultFlag != 0 || (*reinterpret_cast<short*>(state + 0x10) == 2 && frame == 0)) {
                result = 1;
            }
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            result = 1;
        }
        break;
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
            resultFlag = 0;
            CmakeTribeCtrl();
            result = static_cast<unsigned short>(resultFlag);
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
            resultFlag = 0;
            CmakeJobCtrl();
            result = static_cast<unsigned short>(resultFlag);
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            result = 1;
        }
        break;
    case 5:
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
            resultFlag = 0;
            CmakeResultCtrl();
            if (resultFlag != 0 || (*reinterpret_cast<short*>(state + 0x10) == 2 && frame == 0)) {
                result = 1;
            }
        } else if (*reinterpret_cast<short*>(state + 0x18) != 0) {
            *reinterpret_cast<short*>(state + 0x18) = *reinterpret_cast<short*>(state + 0x18) - 1;
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            result = 1;
        }
        break;
    case 6:
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
            resultFlag = 0;
            CmakeResultCtrl1();
            if (resultFlag != 0 || (*reinterpret_cast<short*>(state + 0x10) == 2 && frame == 0)) {
                result = 1;
            }
        } else if (frame < 10) {
            frame = frame + 1;
        } else {
            result = 1;
        }
        break;
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
    short& resultFlag = *reinterpret_cast<short*>(state + 0x2E);
    short& frame = *reinterpret_cast<short*>(state + 0x22);

    switch (step) {
    case 0: {
        float alpha = CalcCmakeFadeAlpha(this);
        DrawWMFrame0__8CMenuPcsFif(this, 1, alpha);

        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

        int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * static_cast<double>(alpha));
        if (a < 0) {
            a = 0;
        } else if (a > 0xFF) {
            a = 0xFF;
        }
        GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
        GXSetChanMatColor(GX_COLOR0A0, col);

        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x3F);
        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0,
            FLOAT_80333254, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 8,
            FLOAT_803332e4, FLOAT_803332d8, FLOAT_803332dc, FLOAT_803332e0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x40);
        for (int x = 0x20; x < 0x260;) {
            int span = 0x20;
            if ((0x260 - x) < span) {
                span = 0x260 - x;
            }

            DrawRect__8CMenuPcsFUlfffffffff(
                MenuPcsVoid(), 0,
                static_cast<float>(x), FLOAT_803332d8, static_cast<float>(span), FLOAT_803332e0,
                FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
            x += span;
        }

        break;
    }
    case 1:
        DrawDiaryBase(step, FLOAT_80333258);
        DrawCmakePageMark(FLOAT_80333258);
        CmakeNameDraw();
        break;
    case 2:
        DrawDiaryBase(step, FLOAT_80333258);
        DrawCmakePageMark(FLOAT_80333258);
        CmakeSexDraw();
        break;
    case 3:
        DrawDiaryBase(step, FLOAT_80333258);
        DrawCmakePageMark(FLOAT_80333258);
        CmakeTribeDraw();
        break;
    case 4:
        DrawDiaryBase(step, FLOAT_80333258);
        DrawCmakePageMark(FLOAT_80333258);
        CmakeJobDraw();
        break;
    case 5:
        DrawDiaryBase(step, FLOAT_80333258);
        DrawCmakePageMark(FLOAT_80333258);
        CmakeResultDraw();
        break;
    case 6:
        DrawDiaryBase(step, FLOAT_80333258);
        DrawCmakePageMark(FLOAT_80333258);
        CmakeResultDraw1();
        break;
    default:
        break;
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
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    const bool widePage = (page == 0);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), widePage ? 0x35 : 0x3F);

    int frameH = widePage ? 0x180 : 0x150;
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_80333254, FLOAT_803332dc, FLOAT_803332dc, static_cast<float>(frameH),
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 8, FLOAT_803332e4, FLOAT_803332dc, FLOAT_803332dc, static_cast<float>(frameH),
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), widePage ? 0x36 : 0x40);
    for (int x = 0x20; x < 0x260;) {
        int span = 0x20;
        if ((0x260 - x) < span) {
            span = 0x260 - x;
        }

        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0, static_cast<float>(x), FLOAT_803332dc, static_cast<float>(span), static_cast<float>(frameH),
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

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    int frameH = (x == 0.0f) ? 0x150 : 0x180;
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (x == 0.0f) ? 0x3F : 0x35);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_80333254, 24.0f, FLOAT_803332dc, static_cast<float>(frameH),
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 8, FLOAT_803332e4, 24.0f, FLOAT_803332dc, static_cast<float>(frameH),
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (x == 0.0f) ? 0x40 : 0x36);
    for (int tileX = 0x20; tileX < 0x260; ) {
        int tileW = 0x20;
        if (0x260 - tileX < 0x20) {
            tileW = 0x260 - tileX;
        }

        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0, static_cast<float>(tileX), 24.0f, static_cast<float>(tileW), static_cast<float>(frameH),
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
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x62 : 0x3B);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_80333390, FLOAT_803332dc, FLOAT_80333394, FLOAT_8033327c,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 8, FLOAT_80333398, FLOAT_803332dc, FLOAT_80333394, FLOAT_8033327c,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A);
    unsigned int offsU = static_cast<unsigned int>(
        -(static_cast<double>(FLOAT_803333a8 * x - FLOAT_803333a8) * DOUBLE_80333298) + DOUBLE_803333a0);
    float offs = static_cast<float>(offsU);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_803333ac, offs, FLOAT_803333b0, FLOAT_803333a8,
        FLOAT_80333254, FLOAT_80333284, FLOAT_80333258, alpha, 0.0f);

    if (x >= static_cast<float>(DOUBLE_80333270)) {
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x65 : 0x3E);

        float titleX = static_cast<float>(offsU + static_cast<unsigned int>(DOUBLE_803333b8));
        float titleY = static_cast<float>(offsU + static_cast<unsigned int>(DOUBLE_803333c0));
        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0, titleX, titleY, FLOAT_803333c8, FLOAT_803332d8,
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

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x31);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_803332e8, FLOAT_803332ec, FLOAT_803332a4, FLOAT_803332a4,
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
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_80333368, FLOAT_803332a4, FLOAT_803332b0, FLOAT_803332dc,
        FLOAT_8033334c, FLOAT_80333284, FLOAT_80333258, FLOAT_80333258, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 8, FLOAT_8033336c, FLOAT_803332a4, FLOAT_803332b0, FLOAT_803332dc,
        FLOAT_8033334c, FLOAT_80333284, FLOAT_80333258, FLOAT_80333258, 0.0f);

    if (yesNoSel != 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);
        GXSetChanMatColor(GX_COLOR0A0, col);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x64 : 0x3D);
        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0, FLOAT_80333370, FLOAT_80333358, FLOAT_803332b0, FLOAT_803332b0,
            FLOAT_8033324c, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    }

    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xF8);
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(1);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();
    font->SetTlut(7);

    unsigned char rgba[8];
    __ct__6CColorFUcUcUcUc(rgba, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    font->SetColor(*reinterpret_cast<GXColor*>(rgba));

    const char* txt = GetMenuStr__8CMenuPcsFi(this, 0x29);
    float w = static_cast<float>(font->GetWidth(txt));
    float tx = (FLOAT_80333380 - w) * 0.5f + 0x178;
    font->SetPosX(tx);
    font->SetPosY(0x184);
    font->Draw(txt);
    DrawInit__8CMenuPcsFv(this);

    if (yesNoSel != 0) {
        int frame = System.m_frameCounter & 7;
        DrawCursor__8CMenuPcsFiif(this, static_cast<int>(tx) - 0x20 + frame, 0x188, alpha);
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

    CFont* labelFont = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xFC);
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

    unsigned char rgba[8];
    __ct__6CColorFUcUcUcUc(rgba, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    labelFont->SetColor(*reinterpret_cast<GXColor*>(rgba));

    float labelWidths[4];
    for (int i = 0; i < 4; i++) {
        const char* txt = GetMenuStr__8CMenuPcsFi(this, 0x2A + i);
        if (txt == 0) {
            txt = "";
        }

        labelWidths[i] = FLOAT_803332f0 + static_cast<float>(labelFont->GetWidth(txt));
        labelFont->SetPosX(FLOAT_803332f0);
        labelFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
        labelFont->Draw(txt);
    }

    CFont* valueFont = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xF8);
    valueFont->SetMargin(FLOAT_80333258);
    valueFont->SetShadow(1);
    valueFont->SetScale(FLOAT_80333258);
    valueFont->DrawInit();
    valueFont->SetColor(*reinterpret_cast<GXColor*>(rgba));
    valueFont->SetTlut(6);

    for (int i = 0; i < 4; i++) {
        const char* txt = "";

        switch (i) {
        case 0:
            txt = s_CmakeInfo.m_name;
            break;
        case 1:
            txt = GetMenuStr__8CMenuPcsFi(this, s_CmakeInfo.m_gender + 0x11);
            break;
        case 2:
            txt = GetTribeStr__8CMenuPcsFi(this, s_CmakeInfo.m_tribe);
            break;
        default:
            txt = GetJobStr__8CMenuPcsFi(this, s_CmakeInfo.m_job);
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

            const char* hairTxt = GetHairStr__8CMenuPcsFi(this, hairIndex + s_CmakeInfo.m_hair);
            if (hairTxt == 0) {
                hairTxt = "";
            }

            valueFont->SetPosX(
                FLOAT_80333300 + (FLOAT_803332fc + labelWidths[i] + static_cast<float>(valueFont->GetWidth(tribeWithSep))));
            valueFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
            valueFont->Draw(hairTxt);
        }
    }

    DrawInit__8CMenuPcsFv(this);
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
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x31);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0,
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
    int baseY = 300;
    unsigned int nameX = static_cast<unsigned int>(
        -((static_cast<double>(FLOAT_80333364) * 0.5) - 0x80000000) + 0x43300000);

    if (x != 0) {
        baseY = 0x130;
    }

    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xF8);
    font->SetShadow(1);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();
    font->SetMargin(FLOAT_80333258);

    unsigned char rgba[8];
    __ct__6CColorFUcUcUcUc(rgba, 0xFF, 0xFF, 0xFF,
        static_cast<unsigned char>(static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha)));
    font->SetColor(*reinterpret_cast<GXColor*>(rgba));
    font->SetTlut(6);

    float textW = static_cast<float>(font->GetWidth(text));
    font->SetPosX(static_cast<float>(static_cast<int>(nameX)));
    font->SetPosY(static_cast<float>(baseY - 4));
    font->Draw(text);
    DrawInit__8CMenuPcsFv(this);

    if (y != 0) {
        _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

        int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
        GXColor drawColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
        GXSetChanMatColor(GX_COLOR0A0, drawColor);

        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x60 : 0x39);

        int cursorX = static_cast<int>(static_cast<float>(static_cast<int>(nameX)) + textW);
        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0,
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
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x3A);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_80333348, FLOAT_803332a4, FLOAT_803332b0, FLOAT_803332dc,
        FLOAT_8033334c, FLOAT_80333284, FLOAT_80333258, FLOAT_80333258, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 8, FLOAT_80333350, FLOAT_803332a4, FLOAT_803332b0, FLOAT_803332dc,
        FLOAT_8033334c, FLOAT_80333284, FLOAT_80333258, FLOAT_80333258, 0.0f);

    if (yesNoSel != 0) {
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), 0x3D);
        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0, FLOAT_80333354, FLOAT_80333358, FLOAT_8033324c, FLOAT_803332b0,
            FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    }

    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xF8);
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(1);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();
    font->SetTlut(7);

    unsigned char rgba[8];
    __ct__6CColorFUcUcUcUc(rgba, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    font->SetColor(*reinterpret_cast<GXColor*>(rgba));

    const char* yesStr = GetMenuStr__8CMenuPcsFi(this, 1);
    float yesW = static_cast<float>(font->GetWidth(yesStr));
    float yesX = (FLOAT_803332b0 - yesW) * FLOAT_8033335c + 0x1D0;
    font->SetPosX(yesX);
    font->SetPosY(FLOAT_80333360);
    font->Draw(yesStr);

    const char* noStr = GetMenuStr__8CMenuPcsFi(this, 2);
    float noW = static_cast<float>(font->GetWidth(noStr));
    float noX = (FLOAT_803332b0 - noW) * FLOAT_8033335c + 0x218;
    font->SetPosX(noX);
    font->SetPosY(FLOAT_80333360);
    font->Draw(noStr);

    DrawInit__8CMenuPcsFv(this);
    if (yesNoSel != 0) {
        float cursorBase = (yesNoSel == 1) ? yesX : noX;
        int frame = System.m_frameCounter & 7;
        DrawCursor__8CMenuPcsFiif(this, static_cast<int>(cursorBase) - 0x24 + frame, 0x175, alpha);
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

    DAT_8032ef10 = static_cast<int>(step);

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

/*
 * --INFO--
 * PAL Address: 0x80171fa0
 * PAL Size: 2332b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmakeNameCtrl()
{
    int state = MenuS32(this, 0x82C);
    int mcWork = MenuS32(this, 0x848);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& resultFlag = *reinterpret_cast<short*>(state + 0x2E);
    short& select = *reinterpret_cast<short*>(state + 0x26);
    short& row = *reinterpret_cast<short*>(state + 0x28);
    short& table = *reinterpret_cast<short*>(state + 0x2A);
    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);
    short& mcState = *reinterpret_cast<short*>(mcWork + 10);
    char* name = GetCmakeNameBuffer();

    if (mode != 1) {
        return;
    }

    if (repeat == 0 && down == 0) {
        return;
    }

    if (mcState == 3) {
        int maxRow = (select < 10) ? 4 : 5;
        if ((repeat & 0x4) != 0) {
            row = (row < maxRow) ? static_cast<short>(row + 1) : 0;
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x8) != 0) {
            row = (row > 0) ? static_cast<short>(row - 1) : static_cast<short>(maxRow);
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

        if ((down & 0x40) != 0) {
            table = (table > 0) ? static_cast<short>(table - 1) : 2;
            Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
        } else if ((down & 0x20) != 0) {
            table = (table < 2) ? static_cast<short>(table + 1) : 0;
            Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
        }

        if ((down & 0x1000) != 0) {
            select = 0xB;
            row = 5;
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            return;
        }

        if ((down & 0x200) != 0) {
            size_t len = strlen(name);
            if (len == 0) {
                resultDir = -1;
                resultFlag = 1;
                mode = 2;
                frame = 0;
                ChgModel__8CMenuPcsFiiii(this, static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
                Sound.PlaySe(0x34, 0x40, 0x7F, 0);
            } else {
                name[len - 1] = '\0';
                Sound.PlaySe(3, 0x40, 0x7F, 0);
            }
            return;
        }

        if ((down & 0x100) != 0) {
            size_t len = strlen(name);
            if (row < 5) {
                if (len >= 7) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                    return;
                }

                const char* rowText = s_cmakeNameRows[table * 5 + row];
                size_t rowLen = strlen(rowText);
                if (select < 0 || static_cast<size_t>(select) >= rowLen || rowText[select] == '\0') {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                    return;
                }

                name[len] = rowText[select];
                name[len + 1] = '\0';
                if (strlen(name) > 6) {
                    select = 0xB;
                    row = 5;
                }
                Sound.PlaySe(2, 0x40, 0x7F, 0);
                return;
            }

            if (IsCmakeNameBlank(name)) {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
                return;
            }

            if (IsDuplicateCmakeName(this, name)) {
                short winX = 0;
                short winY = 0;
                Sound.PlaySe(4, 0x40, 0x7F, 0);
                GetWinSize__8CMenuPcsFiPsPsi(this, 0x14, &winX, &winY, 0);
                SetMcWinInfo__8CMenuPcsFii(this, (int)winX, (int)winY);
                mcState = 0;
                return;
            }

            resultDir = 1;
            resultFlag = 1;
            mode = 2;
            frame = 0;
            Sound.PlaySe(2, 0x40, 0x7F, 0);
        }
    } else if (mcState == 1 && (down & 0x300) != 0) {
        Sound.PlaySe(2, 0x40, 0x7F, 0);
        mcState = 2;
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
void CMenuPcs::CmakeNameClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
}

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
    float previewAlpha = ((mode == 2) && (resultDir < 0)) ? FLOAT_80333258 : alpha;
    float titleX = ((mode == 2) && (resultDir > 0)) ? FLOAT_80333258 : 0.0f;

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

    DrawWMFrame0__8CMenuPcsFif(this, 1, FLOAT_80333258);
    DrawCmakeWin(0.0f, 0.0f, FLOAT_80333258);
    DrawCmakePreviewCharaAlpha(this, previewAlpha);
    DrawCmakeTitle(1, titleX, alpha);

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, 120.0f, 124.0f, 320.0f, 132.0f,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x68 : 0x41);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, 168.0f, 172.0f, FLOAT_803332b0, FLOAT_803332b0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, 232.0f, 172.0f, FLOAT_803332b0, FLOAT_803332b0,
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
        const char* rowText = s_cmakeNameRows[table * 5 + i];
        font->SetPosX(FLOAT_803332c8);
        font->SetPosY((108.0f + i * 32.0f) - FLOAT_803332f4);
        font->Draw(rowText);
    }

    reinterpret_cast<unsigned char*>(font)[0x24] &= 0xEF;
    DrawInit__8CMenuPcsFv(this);

    if (mode == 1 && row < 5) {
        int cursorX = static_cast<int>(FLOAT_803332c8 + FLOAT_803332c0 * static_cast<float>(select));
        int cursorY = 112 + row * 32;
        DrawCursor__8CMenuPcsFiif(this, cursorX + (System.m_frameCounter & 7), cursorY, FLOAT_80333258);
    }

    int showNameCursor = ((mode == 1) && (row < 5) && (strlen(name) <= 6)) ? 1 : 0;
    DrawCmakeName(0, showNameCursor, name, alpha);
    DrawCmakeDecision((row > 4) ? 1 : 0, alpha);

    if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) != 3) {
        DrawMcWin__8CMenuPcsFss(this, -1, 0);
        if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) == 1) {
            DrawMcWinMess__8CMenuPcsFii(this, 0x14, 0);
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
void CMenuPcs::CmakeSexOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 2;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
void CMenuPcs::CmakeSexCtrl()
{
    int state = MenuS32(this, 0x82C);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& sel = *reinterpret_cast<short*>(state + 0x26);
    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);

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

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmakeSexClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
}

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
    DrawWMFrame0__8CMenuPcsFif(this, 1, FLOAT_80333258);
    DrawCmakeSelectionBackdrop(this);
    DrawCmakePreviewCharaAlpha(this, FLOAT_80333258);
    DrawCmakePopupPanel(this, alpha, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284, 0.85f, 0.85f);
    DrawCmakeTitle(2, FLOAT_80333258, alpha);

    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xFC);
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(0);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    unsigned char rgba[8];
    __ct__6CColorFUcUcUcUc(rgba, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    font->SetColor(*reinterpret_cast<GXColor*>(rgba));

    float maxWidth = 0.0f;
    for (int i = 0; i < 2; ++i) {
        const char* txt = GetMenuStr__8CMenuPcsFi(this, 0x11 + i);
        float width = static_cast<float>(font->GetWidth(txt));
        if (maxWidth < width) {
            maxWidth = width;
        }
        float x = FLOAT_80333288 - width * FLOAT_80333298;
        font->SetPosX(x);
        font->SetPosY(0x9C + i * 0x28 - FLOAT_803332f4);
        font->Draw(txt);
    }
    DrawInit__8CMenuPcsFv(this);

    if (*reinterpret_cast<short*>(MenuS32(this, 0x82C) + 0x10) == 1) {
        int sel = *reinterpret_cast<short*>(MenuS32(this, 0x82C) + 0x26);
        int frame = System.m_frameCounter & 7;
        int cursorX = static_cast<int>(FLOAT_80333288 - maxWidth * (FLOAT_80333298 + FLOAT_80333298)) + frame;
        int cursorY = 0xA4 + sel * 0x28;
        DrawCursor__8CMenuPcsFiif(this, cursorX, cursorY, alpha);
    }

    DrawCmakeMcOverlay(this, 0x15);
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
void CMenuPcs::CmakeTribeOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 3;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x801708b0
 * PAL Size: 1080b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmakeTribeCtrl()
{
    int state = MenuS32(this, 0x82C);
    int mcWork = MenuS32(this, 0x848);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& resultFlag = *reinterpret_cast<short*>(state + 0x2E);
    short& tribe = *reinterpret_cast<short*>(state + 0x26);
    short& crest = *reinterpret_cast<short*>(state + 0x28);
    short& selectField = *reinterpret_cast<short*>(state + 0x30);
    short& mcState = *reinterpret_cast<short*>(mcWork + 10);
    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);

    if (repeat == 0 && down == 0) {
        return;
    }

    if (mcState == 3) {
        short& currentValue = *reinterpret_cast<short*>(state + 0x26 + selectField * 2);

        if ((repeat & 0x8) != 0) {
            currentValue = (currentValue == 0) ? 3 : static_cast<short>(currentValue - 1);
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            currentValue = (currentValue < 3) ? static_cast<short>(currentValue + 1) : 0;
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0xC) != 0) {
            return;
        }

        if ((down & 0x200) != 0) {
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            if (selectField == 0) {
                resultDir = -1;
                resultFlag = 1;
                return;
            }

            selectField = static_cast<short>(selectField - 1);
            return;
        }

        if ((down & 0x100) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            if (selectField == 0) {
                selectField = static_cast<short>(selectField + 1);
                return;
            }

            if (!IsDuplicateCmakeTribeHair(this, tribe, crest, s_CmakeInfo.m_gender)) {
                s_CmakeInfo.m_tribe = static_cast<signed char>(tribe);
                s_CmakeInfo.m_hair = static_cast<signed char>(crest);
                ChgModel__8CMenuPcsFiiii(this,
                    static_cast<int>(MenuS16(this, 0x86A)),
                    static_cast<int>(s_CmakeInfo.m_tribe),
                    static_cast<int>(s_CmakeInfo.m_hair),
                    static_cast<int>(s_CmakeInfo.m_gender));
                resultDir = 1;
                resultFlag = 1;
                return;
            }

            Sound.PlaySe(4, 0x40, 0x7F, 0);
            short winX = 0;
            short winY = 0;
            GetWinSize__8CMenuPcsFiPsPsi(this, 0x15, &winX, &winY, 0);
            SetMcWinInfo__8CMenuPcsFii(this, static_cast<int>(winX), static_cast<int>(winY));
            mcState = 0;
        }

        return;
    }

    if (mcState == 1 && (down & 0x300) != 0) {
        Sound.PlaySe(2, 0x40, 0x7F, 0);
        mcState = 2;
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
void CMenuPcs::CmakeTribeClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
}

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

    DrawWMFrame0__8CMenuPcsFif(this, 1, FLOAT_80333258);
    DrawCmakeWin(0.0f, 0.0f, 1.0f);
    DrawCmakePreviewChara(this);

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_80333278, FLOAT_8033327c, FLOAT_803332a4, FLOAT_80333284,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333318, 0.0f);

    DrawCmakeTitle(3, FLOAT_80333258, alpha);
    DrawCmakeCrest(MenuS16(this, 0x862), 0, 0, alpha);

    CFont* tribeFont = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xFC);
    tribeFont->SetMargin(FLOAT_80333258);
    tribeFont->SetShadow(0);
    tribeFont->SetScale(FLOAT_80333258);
    tribeFont->DrawInit();
    unsigned char tribeRgba[8];
    __ct__6CColorFUcUcUcUc(tribeRgba, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    tribeFont->SetColor(*reinterpret_cast<GXColor*>(tribeRgba));

    for (int i = 0; i < 4; i++) {
        const char* txt = GetTribeStr__8CMenuPcsFi(this, i);
        if (txt == 0) {
            txt = "";
        }
        tribeFont->SetPosX(FLOAT_80333284);
        tribeFont->SetPosY(0x88 + i * 0x1C - FLOAT_803332f4);
        tribeFont->Draw(txt);
    }

    CFont* hairFont = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xF8);
    hairFont->SetMargin(FLOAT_80333258);
    hairFont->SetShadow(1);
    hairFont->SetScale(FLOAT_80333258);
    hairFont->DrawInit();
    hairFont->SetColor(*reinterpret_cast<GXColor*>(tribeRgba));
    hairFont->SetTlut(6);

    int hairBase = MenuS16(this, 0x862) * 8;
    if (s_CmakeInfo.m_gender != 0) {
        hairBase += 4;
    }

    for (int i = 0; i < 4; i++) {
        const char* txt = GetHairStr__8CMenuPcsFi(this, hairBase + i);
        if (txt == 0) {
            txt = "";
        }
        hairFont->SetPosX(FLOAT_8033331c);
        hairFont->SetPosY(0x88 + i * 0x1C - FLOAT_803332f4);
        hairFont->Draw(txt);
    }

    DrawInit__8CMenuPcsFv(this);

    if (*reinterpret_cast<short*>(state + 0x10) == 1) {
        int select = *reinterpret_cast<short*>(state + 0x26);
        int frame = System.m_frameCounter & 7;
        int tribeCursorY = 0x88 + select * 0x1C;

        if (*reinterpret_cast<short*>(state + 0x30) == 0) {
            DrawCursor__8CMenuPcsFiif(this, static_cast<int>(FLOAT_80333320) + frame, tribeCursorY, alpha);
        } else {
            if ((System.m_frameCounter & 1) != 0) {
                DrawCursor__8CMenuPcsFiif(this, static_cast<int>(FLOAT_80333320), tribeCursorY, alpha);
            }

            int hairCursorY = 0x88 + *reinterpret_cast<short*>(state + 0x28) * 0x1C;
            DrawCursor__8CMenuPcsFiif(
                this, static_cast<int>(FLOAT_80333324) + frame, hairCursorY, alpha);
        }
    }

    if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) != 3) {
        DrawMcWin__8CMenuPcsFss(this, -1, 0);
        if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) == 1) {
            DrawMcWinMess__8CMenuPcsFii(this, 0x15, 0);
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
void CMenuPcs::CmakeJobOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 4;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8016fb38
 * PAL Size: 1156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::CmakeJobCtrl()
{
    int state = MenuS32(this, 0x82C);
    int mcWork = MenuS32(this, 0x848);
    short& job = *reinterpret_cast<short*>(state + 0x26);
    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& resultFlag = *reinterpret_cast<short*>(state + 0x2E);
    short& mcState = *reinterpret_cast<short*>(mcWork + 10);

    if (repeat == 0 && down == 0) {
        return;
    }

    if (mcState == 3) {
        if ((repeat & 0x8) != 0) {
            job = (job < 3) ? static_cast<short>(job + 3) : static_cast<short>(job - 1);
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            job = (((job & 3) < 3)) ? static_cast<short>(job + 1) : static_cast<short>(job - 3);
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0x3) != 0) {
            job = (job < 4) ? static_cast<short>(job + 4) : static_cast<short>(job - 4);
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((down & 0x100) != 0) {
            if (FindDuplicateCmakeJob(this, static_cast<int>(job)) < 0) {
                s_CmakeInfo.m_job = static_cast<signed char>(job);
                MenuS16(this, 0x864) = job;
                SetSingMakeChara();
                resultDir = 1;
                resultFlag = 1;
                Sound.PlaySe(2, 0x40, 0x7F, 0);
            } else {
                short winX = 0;
                short winY = 0;
                Sound.PlaySe(4, 0x40, 0x7F, 0);
                GetWinSize__8CMenuPcsFiPsPsi(this, 0x16, &winX, &winY, 0);
                SetMcWinInfo__8CMenuPcsFii(this, (int)winX, (int)winY);
                mcState = 0;
            }
        } else if ((down & 0x200) != 0) {
            resultDir = -1;
            resultFlag = 1;
            ChgModel__8CMenuPcsFiiii(this, static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
            Sound.PlaySe(3, 0x40, 0x7F, 0);
        }
    } else if (mcState == 1 && (down & 0x300) != 0) {
        Sound.PlaySe(2, 0x40, 0x7F, 0);
        mcState = 2;
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
void CMenuPcs::CmakeJobClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
}

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
    int frame = static_cast<int>(*reinterpret_cast<short*>(state + 0x22)) - 1;
    if (frame < 0) {
        frame = 0;
    }

    short mode = *reinterpret_cast<short*>(state + 0x10);
    float alpha = FLOAT_80333258;
    if (mode == 0) {
        alpha = static_cast<float>(DOUBLE_80333268 * static_cast<double>(frame));
    } else if (mode == 2) {
        alpha = static_cast<float>(DOUBLE_80333270 - DOUBLE_80333268 * static_cast<double>(frame));
    }

    DrawWMFrame0__8CMenuPcsFif(this, 1, FLOAT_80333258);
    DrawCmakeSelectionBackdrop(this);
    DrawCmakePreviewCharaAlpha(this, FLOAT_80333258);

    int panelAlpha = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (panelAlpha < 0) {
        panelAlpha = 0;
    } else if (panelAlpha > 0xFF) {
        panelAlpha = 0xFF;
    }

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    GXColor panelColor = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(panelAlpha)};
    GXSetChanMatColor(GX_COLOR0A0, panelColor);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0,
        FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    DrawCmakeTitle(5, FLOAT_80333258, alpha);

    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xFC);
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(0);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();

    GXColor textColor;
    __ct__6CColorFUcUcUcUc(&textColor, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(panelAlpha));
    font->SetColor(textColor);

    for (int i = 0; i < 8; ++i) {
        const char* txt = GetJobStr__8CMenuPcsFi(this, i);
        int x = (i < 4) ? 0x110 : 0x1A8;
        int row = (i < 4) ? i : (i - 4);
        font->SetPosX(x);
        font->SetPosY(static_cast<float>(0x70 + row * 0x28) - FLOAT_803332f4);
        font->Draw(txt);
    }

    if (mode == 1) {
        int sel = *reinterpret_cast<short*>(state + 0x26);
        int cursorX = (sel < 4) ? 0x110 : 0x1A8;
        int cursorY = 0x70 + ((sel < 4) ? sel : (sel - 4)) * 0x28;
        int cursorFrame = System.m_frameCounter & 7;
        DrawCursor__8CMenuPcsFiif(this, cursorX - 0x18 + cursorFrame, cursorY, alpha);
    }

    short mcState = *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10);
    if (mcState != 3) {
        DrawMcWin__8CMenuPcsFss(this, -1, 0);
        if (mcState == 1) {
            DrawMcWinMess__8CMenuPcsFii(this, 0x16, 0);
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
void CMenuPcs::CmakeResultOpen()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x16) = 5;
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
void CMenuPcs::CmakeResultCtrl()
{
    int state = MenuS32(this, 0x82C);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& sel = *reinterpret_cast<short*>(state + 0x26);
    short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);

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
void CMenuPcs::CmakeResultClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
}

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

    DrawWMFrame0__8CMenuPcsFif(this, 1, FLOAT_80333258);
    DrawCmakeSelectionBackdrop(this);
    DrawCmakePreviewChara(this);

    if ((mode == 2) && (resultDir < 0)) {
        DrawCmakePopupPanel(this, FLOAT_80333258, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
            FLOAT_80333258, FLOAT_80333258);
    } else {
        DrawCmakePopupPanel(this, alpha, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
            FLOAT_80333258, FLOAT_80333258);
    }

    if ((mode == 2) && (resultDir > 0)) {
        DrawCmakeTitle(6, FLOAT_80333258, alpha);
    } else {
        DrawCmakeTitle(6, alpha, FLOAT_80333258);
    }

    float textAlpha = alpha;
    if ((mode == 2) && (resultDir < 0)) {
        textAlpha = FLOAT_80333258;
    }

    DrawCmakeCrest(static_cast<int>(s_CmakeInfo.m_tribe), 0, 0, textAlpha);

    if (mode == 1) {
        DrawCmakeYesNo(*reinterpret_cast<short*>(state + 0x26) + 1, alpha);
    } else {
        DrawCmakeYesNo(0, alpha);
    }

    CFont* labelFont = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xFC);
    labelFont->SetMargin(FLOAT_80333258);
    labelFont->SetShadow(0);
    labelFont->SetScale(FLOAT_80333258);
    labelFont->DrawInit();

    int textColor = static_cast<int>(static_cast<double>(FLOAT_80333240) * textAlpha);
    if (textColor < 0) {
        textColor = 0;
    } else if (textColor > 0xFF) {
        textColor = 0xFF;
    }

    GXColor color;
    __ct__6CColorFUcUcUcUc(&color, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textColor));
    labelFont->SetColor(color);

    float labelWidths[4];
    for (int i = 0; i < 4; i++) {
        const char* label = GetMenuStr__8CMenuPcsFi(this, i + 0x2A);
        if (label == 0) {
            label = "";
        }

        labelWidths[i] = FLOAT_803332f0 + labelFont->GetWidth(label);
        labelFont->SetPosX(FLOAT_803332f0);
        labelFont->SetPosY(static_cast<float>(0x70 + i * 0x28) - FLOAT_803332f4);
        labelFont->Draw(label);
    }

    CFont* valueFont = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xF8);
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
            value = GetMenuStr__8CMenuPcsFi(this, static_cast<int>(s_CmakeInfo.m_gender) + 0x11);
        } else if (i == 2) {
            value = GetTribeStr__8CMenuPcsFi(this, static_cast<int>(s_CmakeInfo.m_tribe));
            if (value == 0) {
                value = "";
            }

            strcpy(tribeWithSlash, value);
            size_t tribeLen = strlen(tribeWithSlash);
            if (tribeLen + 1 < sizeof(tribeWithSlash)) {
                tribeWithSlash[tribeLen] = '/';
                tribeWithSlash[tribeLen + 1] = '\0';
            }
            value = tribeWithSlash;
        } else {
            value = GetJobStr__8CMenuPcsFi(this, static_cast<int>(s_CmakeInfo.m_job));
        }

        if (value == 0) {
            value = "";
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

            const char* hair = GetHairStr__8CMenuPcsFi(this, hairIndex + static_cast<int>(s_CmakeInfo.m_hair));
            if (hair == 0) {
                hair = "";
            }

            valueFont->SetPosX(FLOAT_80333300 + x + valueWidth);
            valueFont->SetPosY(y);
            valueFont->Draw(hair);
        }
    }

    DrawInit__8CMenuPcsFv(this);

    if (mode == 2 && resultDir < 0) {
        DrawCmakeDecision(-1, 1.0f);
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
void CMenuPcs::CmakeResultOpen1()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 0;
    *reinterpret_cast<short*>(state + 0x22) = 0;
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
void CMenuPcs::CmakeResultCtrl1()
{
    int state = MenuS32(this, 0x82C);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);

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
void CMenuPcs::CmakeResultClose1()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
    *reinterpret_cast<short*>(state + 0x22) = 0;
}

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

    DrawWMFrame0__8CMenuPcsFif(this, 1, FLOAT_80333258);
    DrawCmakeSelectionBackdrop(this);
    DrawCmakePreviewChara(this);
    DrawCmakePopupPanel(this, popupAlpha, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
        FLOAT_80333258, FLOAT_80333258);
    DrawCmakeTitle(7, FLOAT_80333258, alpha);
    DrawCmakeCrest(MenuS16(this, 0x862), 0, 0, textAlpha);

    CFont* labelFont = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xFC);
    labelFont->SetMargin(FLOAT_80333258);
    labelFont->SetShadow(0);
    labelFont->SetScale(FLOAT_80333258);
    labelFont->DrawInit();

    int textColor = static_cast<int>(static_cast<double>(FLOAT_80333240) * textAlpha);
    if (textColor < 0) {
        textColor = 0;
    } else if (textColor > 0xFF) {
        textColor = 0xFF;
    }

    GXColor color;
    __ct__6CColorFUcUcUcUc(&color, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(textColor));
    labelFont->SetColor(color);

    float labelWidths[4];
    for (int i = 0; i < 4; i++) {
        const char* txt = GetMenuStr__8CMenuPcsFi(this, 0x2A + i);
        if (txt == 0) {
            txt = "";
        }

        labelWidths[i] = FLOAT_803332f0 + static_cast<float>(labelFont->GetWidth(txt));
        labelFont->SetPosX(FLOAT_803332f0);
        labelFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
        labelFont->Draw(txt);
    }

    CFont* valueFont = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xF8);
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
            txt = GetMenuStr__8CMenuPcsFi(this, s_CmakeInfo.m_gender + 0x11);
            break;
        case 2:
            txt = GetTribeStr__8CMenuPcsFi(this, s_CmakeInfo.m_tribe);
            break;
        default:
            txt = GetJobStr__8CMenuPcsFi(this, s_CmakeInfo.m_job);
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
            tribeWithSep[tribeLen] = '/';
            tribeWithSep[tribeLen + 1] = '\0';

            const char* hairTxt = GetHairStr__8CMenuPcsFi(this, hairIndex + s_CmakeInfo.m_hair);
            if (hairTxt == 0) {
                hairTxt = "";
            }

            valueFont->SetPosX(
                FLOAT_80333300 +
                (FLOAT_803332fc + labelWidths[i] + static_cast<float>(valueFont->GetWidth(tribeWithSep))));
            valueFont->SetPosY(0x70 + i * 0x28 - FLOAT_803332f4);
            valueFont->Draw(hairTxt);
        }
    }

    DrawInit__8CMenuPcsFv(this);

    if (mode == 1) {
        int cursorX = static_cast<int>(FLOAT_80333304) + (System.m_frameCounter & 7);
        int cursorY = 0x70 + *reinterpret_cast<short*>(state + 0x26) * 0x28;
        DrawCursor__8CMenuPcsFiif(this, cursorX, cursorY, alpha);
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
void CMenuPcs::CmakeVillageOpen()
{
    MenuU8(this, 0x16) = 1;
    createVillageMenu();
}

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
    int villageWork = MenuS32(this, 0x830);
    short& select = *reinterpret_cast<short*>(villageWork + 0x26);
    short& row = *reinterpret_cast<short*>(villageWork + 0x28);
    short& table = *reinterpret_cast<short*>(villageWork + 0x2A);
    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);
    char picked[2] = {'\0', '\0'};
    size_t len = strlen(s_CmakeInfo.m_name);

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
            select = (select > 0) ? static_cast<short>(select - 1) : 0xB;
            Sound.PlaySe(1, 0x40, 0x7f, 0);
        } else {
            Sound.PlaySe(4, 0x40, 0x7f, 0);
        }
    } else if ((repeat & 0x2) != 0) {
        if (row < 5) {
            select = (select < 0xB) ? static_cast<short>(select + 1) : 0;
            Sound.PlaySe(1, 0x40, 0x7f, 0);
        } else {
            Sound.PlaySe(4, 0x40, 0x7f, 0);
        }
    }

    if ((down & 0x40) != 0) {
        table = (table > 0) ? static_cast<short>(table - 1) : 2;
        Sound.PlaySe(0x5a, 0x40, 0x7f, 0);
    } else if ((down & 0x20) != 0) {
        table = (table < 2) ? static_cast<short>(table + 1) : 0;
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
        if (IsCmakeNameBlank(s_CmakeInfo.m_name)) {
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

    const char* rowText = s_cmakeNameRows[table * 5 + row];
    size_t rowLen = strlen(rowText);
    if (select < 0 || static_cast<size_t>(select) >= rowLen) {
        Sound.PlaySe(4, 0x40, 0x7f, 0);
        return 0;
    }

    picked[0] = rowText[select];
    if (picked[0] == '\0') {
        Sound.PlaySe(4, 0x40, 0x7f, 0);
        return 0;
    }

    s_CmakeInfo.m_name[len] = picked[0];
    s_CmakeInfo.m_name[len + 1] = '\0';
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
void CMenuPcs::CmakeVillageClose()
{
    MenuU8(this, 0x16) = 0;
    destroyVillageMenu();
}

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
    int villageWork = MenuS32(this, 0x830);
    short mode = *reinterpret_cast<short*>(villageWork + 0x10);
    int frame = static_cast<int>(*reinterpret_cast<short*>(villageWork + 0x22)) - 1;
    short select = *reinterpret_cast<short*>(villageWork + 0x26);
    short row = *reinterpret_cast<short*>(villageWork + 0x28);
    short table = *reinterpret_cast<short*>(villageWork + 0x2A);
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

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    if (a < 0) {
        a = 0;
    } else if (a > 0xFF) {
        a = 0xFF;
    }

    GXColor col = {0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a)};
    GXSetChanMatColor(GX_COLOR0A0, col);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_80333278, FLOAT_8033327c, FLOAT_80333280, FLOAT_80333284,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    DrawCmakeTitle(0, FLOAT_80333258, alpha);

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);
    GXSetChanMatColor(GX_COLOR0A0, col);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x61 : 0x3A);
    float panelX = -(FLOAT_80333290 * static_cast<float>(DOUBLE_80333298) - static_cast<float>(DOUBLE_80333288));
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, panelX, FLOAT_803332a0, FLOAT_80333290, FLOAT_8033327c,
        FLOAT_80333254, FLOAT_803332a4, FLOAT_80333258, FLOAT_80333258, 0.0f);

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(MenuPcsVoid(), 0);
    GXSetChanMatColor(GX_COLOR0A0, col);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 0x68 : 0x41);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, FLOAT_803332a8, FLOAT_803332ac, FLOAT_803332b0, FLOAT_803332b0,
        FLOAT_80333254, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(
        MenuPcsVoid(), 0, static_cast<float>(DOUBLE_803333b8), FLOAT_803332ac, FLOAT_803332b0, FLOAT_803332b0,
        FLOAT_803332b0, FLOAT_80333254, FLOAT_80333258, FLOAT_80333258, 0.0f);

    if (mode == 1 && row < 5) {
        GXColor cursorColor = {0xFF, 0xFF, 0xFF, 0xFF};
        GXSetChanMatColor(GX_COLOR0A0, cursorColor);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcsVoid(), (MenuS16(this, 0x86C) != 0) ? 100 : 0x3D);
        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcsVoid(), 0,
            0xE5 + select * 20.0f, 99.0f + row * 32.0f, FLOAT_803332b0, FLOAT_803332b0,
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
        const char* rowText = s_cmakeNameRows[table * 5 + i];
        font->SetPosX(FLOAT_803332c8);
        font->SetPosY(static_cast<float>(0x6C + i * 0x20));
        font->Draw(rowText);
    }

    reinterpret_cast<unsigned char*>(font)[0x24] &= 0xEF;

    DrawInit__8CMenuPcsFv(this);
    if (mode == 1 && row < 5) {
        int wobble = System.m_frameCounter & 7;
        DrawCursor__8CMenuPcsFiif(this,
            static_cast<int>(FLOAT_803332c8 + select * FLOAT_803332c0) + wobble,
            row * 0x20 + 0x70, FLOAT_80333258);
    }

    int showNameCursor = (mode == 1 && row < 5 && strlen(s_CmakeInfo.m_name) <= 6) ? 1 : 0;
    DrawCmakeName(1, showNameCursor, s_CmakeInfo.m_name, alpha);
    DrawCmakeDecision((row > 4) ? 1 : 0, alpha);
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
void CMenuPcs::SetSingMakeChara()
{
    int slot = static_cast<int>(MenuS16(this, 0x86A));
    ChgModel__8CMenuPcsFiiii(this, slot, MenuS16(this, 0x860), MenuS16(this, 0x862), MenuS16(this, 0x864));
    SetAnim__8CMenuPcsFi(this, slot);
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
            void*& font = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x108);
            ReleaseRefObject(font);
            font = nullptr;
        }

        freeTexture__8CMenuPcsFiiii(this, 8, 1, 0x60, 9);

        int& villageWork = MenuS32(this, 0x830);
        if (villageWork != 0) {
            __dl__FPv(reinterpret_cast<void*>(villageWork));
            villageWork = 0;
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
    if (MenuU8(this, 0x16) != 0 && MenuS16(this, 0x86C) == 0) {
        if (Game.m_gameWork.m_menuStageMode == 0) {
            char path[128];
            char* language = GetLangString__5CGameFv(&Game);
            sprintf(path, s_dvd__smenu_subfont_fnt_801e3020, language);
            loadFont__8CMenuPcsFiPcii(this, 2, path, 4, -1);
        }

        loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(
            this, PTR_s_world2_802159a4, 8, 1, &DAT_802159c8, 0x60, 9, 3);

        void* stage = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0xEC);
        int& villageWork = MenuS32(this, 0x830);
        villageWork =
            reinterpret_cast<int>(__nw__FUlPQ27CMemory6CStagePci(0x48, stage, const_cast<char*>(s_cmake_cpp_801e3038), 0xCB3));
        memset(reinterpret_cast<void*>(villageWork), 0, 0x48);
        LoadCmakeVillageName();
        MenuS16(this, 0x86C) = 1;
    }

    short active = MenuS16(this, 0x86C);
    if (active == 0) {
        return;
    }

    if (MenuU8(this, 0x16) == 0) {
        if (Game.m_gameWork.m_menuStageMode == 0) {
            void*& font = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x108);
            ReleaseRefObject(font);
            font = nullptr;
        }

        freeTexture__8CMenuPcsFiiii(this, 8, 1, 0x60, 9);
        int& villageWork = MenuS32(this, 0x830);
        if (villageWork != 0) {
            __dl__FPv(reinterpret_cast<void*>(villageWork));
            villageWork = 0;
        }
        MenuS16(this, 0x86C) = 0;
        return;
    }

    int villageWork = MenuS32(this, 0x830);
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
        result = CmakeVillageCtrl__8CMenuPcsFv(this);
    } else if (frame < 10) {
        frame = frame + 1;
        result = 0;
    } else {
        result = 1;
    }

    *reinterpret_cast<unsigned short*>(villageWork + 0x2E) = result;
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
        int villageWork = MenuS32(this, 0x830);
        CmakeVillageDraw__8CMenuPcsFv(this);
        if (*reinterpret_cast<short*>(villageWork + 0x2E) != 0) {
            short& mode = *reinterpret_cast<short*>(villageWork + 0x10);
            if (mode < 2) {
                mode = mode + 1;
            } else {
                MenuU8(this, 0x16) = 0;
                CallWorldParam__8CMenuPcsFiii(this, 10, 0, 0);
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
    int handle = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x7F4 + slot * 4);
    CChara::CModel* model = *reinterpret_cast<CChara::CModel**>(reinterpret_cast<unsigned char*>(handle) + 0x168);
    unsigned char* modelWork = reinterpret_cast<unsigned char*>(MenuS32(this, 0x814) + slot * 0x50 + 0xA00);

    if (model == nullptr || *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(model) + 0xB0) == 0) {
        *reinterpret_cast<int*>(modelWork + 0x00) = 0;
        return;
    }

    unsigned char* animWork = reinterpret_cast<unsigned char*>(MenuS32(this, 0x824) + slot * 0x34);
    if (animWork[0x0C] == 1) {
        *reinterpret_cast<float*>(modelWork + 0x2C) = FLOAT_8033325c;
        SetAnim__8CMenuPcsFi(this, slot);
        animWork[0x0C] = 0;
    }

    *reinterpret_cast<int*>(modelWork + 0x00) = 1;
    if (**reinterpret_cast<int**>(reinterpret_cast<unsigned char*>(this) + 0x7F4 + slot * 4) != 3) {
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
        SetMatrix__Q26CChara6CModelFPA4_f(model, scaleMtx);
        CalcMatrix__Q26CChara6CModelFv(model);
        CalcSkin__Q26CChara6CModelFv(model);
        PCAnimCtrl__8CMenuPcsFv(this);
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
void CMenuPcs::DrawSingleCMakeChara(float alpha)
{
    CalcSingleCMakeChara();
    if (alpha <= 0.0f) {
        return;
    }

    DrawCmakePreviewCharaAlpha(this, alpha);
}
