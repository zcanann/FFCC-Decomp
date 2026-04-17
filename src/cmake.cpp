#include "ffcc/cmake.h"
#include "ffcc/chara.h"
#include "ffcc/fontman.h"
#include "ffcc/p_game.h"
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
extern "C" float FLOAT_80333284;
extern "C" float FLOAT_80333288;
extern "C" float FLOAT_80333298;
extern "C" float FLOAT_8033327c;
extern "C" float FLOAT_8033324c;
extern "C" float FLOAT_803332d8;
extern "C" float FLOAT_803332e4;
extern "C" float FLOAT_803332f4;
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
extern "C" float FLOAT_803333a8;
extern "C" float FLOAT_803333ac;
extern "C" float FLOAT_803333b0;
extern "C" float FLOAT_803333c8;
extern "C" double DOUBLE_803332d0;
extern "C" double DOUBLE_80333270;
extern "C" double DOUBLE_80333268;
extern "C" double DOUBLE_80333298;
extern "C" double DOUBLE_803333a0;
extern "C" double DOUBLE_803333b8;
extern "C" double DOUBLE_803333c0;
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
extern "C" void DrawMcWin__8CMenuPcsFss(CMenuPcs*, short, short);
extern "C" void DrawMcWinMess__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" char s_dvd__smenu_subfont_fnt_801e3020[];
extern "C" char* PTR_s_world2_802159a4[];
extern "C" int DAT_802159c8;
extern "C" {
static const char s_cmake_cpp_801e3038[] = "cmake.cpp";
}

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

static inline void DrawCmakePreviewChara(CMenuPcs* menu)
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
        *reinterpret_cast<float*>(model + 0x9C) = FLOAT_80333258;
        Draw__Q29CCharaPcs7CHandleFi(reinterpret_cast<void*>(handle), 5);
        RestoreProjection__8CMenuPcsFv(menu);
    }

    DrawInit__8CMenuPcsFv(menu);
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    int state = MenuS32(this, 0x82C);

    if (*reinterpret_cast<unsigned char*>(state + 0x0B) == 0) {
        memset(self + 0x85C, 0, 0x16);
        *reinterpret_cast<unsigned char*>(state + 0x0B) = 1;
        *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
        *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) = 3;
    }

    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& openMode = *reinterpret_cast<short*>(state + 0x10);
    short& step = *reinterpret_cast<short*>(state + 0x16);

    switch (step) {
    case 0:
        if (openMode == 0 || openMode == 2) {
            if (frame < 10) {
                frame = frame + 1;
            } else {
                *reinterpret_cast<short*>(state + 0x26) = 0;
                *reinterpret_cast<short*>(state + 0x28) = 0;
                *reinterpret_cast<short*>(state + 0x2A) = 0;
                *reinterpret_cast<short*>(state + 0x2C) = 0;
            }
        }
        break;
    case 1:
        if (openMode == 0 || openMode == 2) {
            if (frame < 10) {
                frame = frame + 1;
            } else if (openMode == 2 && *reinterpret_cast<short*>(state + 0x1E) < 0) {
                ChgModel__8CMenuPcsFiiii(this, static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
            }
        } else {
            CmakeNameCtrl();
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
        } else if (openMode == 1) {
            CmakeSexCtrl();
        } else if (frame < 10) {
            frame = frame + 1;
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
        } else if (openMode == 1) {
            CmakeTribeCtrl();
        } else if (frame < 10) {
            frame = frame + 1;
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
        } else if (openMode == 1) {
            CmakeJobCtrl();
        } else if (frame < 10) {
            frame = frame + 1;
        }
        break;
    default:
        break;
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
    int state = MenuS32(this, 0x82C);
    short step = *reinterpret_cast<short*>(state + 0x16);
    float alpha = 1.0f;

    DrawDiaryBase(step, alpha);
    DrawCmakePageMark(alpha);

    switch (step) {
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
        CmakeResultDraw();
        break;
    }

    if (*reinterpret_cast<short*>(state + 0x2E) != 0) {
        short& mode = *reinterpret_cast<short*>(state + 0x10);
        short& resultDir = *reinterpret_cast<short*>(state + 0x1E);
        short& frame = *reinterpret_cast<short*>(state + 0x22);

        if (mode < 2) {
            mode = mode + 1;
        } else {
            if (step == 6) {
                *reinterpret_cast<short*>(state + 0x16) = *reinterpret_cast<short*>(state + 0x26) + 1;
                if (*reinterpret_cast<short*>(state + 0x16) == 0) {
                    mode = 2;
                } else {
                    mode = 0;
                }
            } else if (resultDir < 0) {
                if (step == 5) {
                    *reinterpret_cast<short*>(state + 0x16) = 6;
                } else if (step > 0) {
                    *reinterpret_cast<short*>(state + 0x16) = step - 1;
                }
                if (*reinterpret_cast<short*>(state + 0x16) == 0) {
                    mode = 2;
                } else {
                    mode = 0;
                }
            } else if (step != 5) {
                *reinterpret_cast<short*>(state + 0x16) = step + 1;
                if (*reinterpret_cast<short*>(state + 0x16) == 0) {
                    mode = 2;
                } else {
                    mode = 0;
                }
            } else {
                *reinterpret_cast<short*>(state + 0x16) = 0;
                mode = 2;
            }

            *reinterpret_cast<unsigned char*>(state + 0x0C) = 0;
            frame = 0;
            *reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) = 3;
        }

        *reinterpret_cast<short*>(state + 0x2E) = 0;
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
    (void)type;
    (void)frame;
    (void)alpha;
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
void CMenuPcs::DrawCmakeCrest(int tribe, int x, int y, float alpha)
{
    DrawCrystal(tribe, x + y, alpha);
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
    *reinterpret_cast<short*>(state + 0x16) = 1;
    *reinterpret_cast<short*>(state + 0x22) = 0;
    *reinterpret_cast<short*>(state + 0x1E) = 0;
    *reinterpret_cast<unsigned char*>(state + 0x0B) = 0;
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
void CMenuPcs::CmakeCtrl()
{
    int state = MenuS32(this, 0x82C);
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& step = *reinterpret_cast<short*>(state + 0x16);
    short& frame = *reinterpret_cast<short*>(state + 0x22);

    CalcSingCMake();

    if (mode == 0 && frame >= 10) {
        mode = 1;
        frame = 0;
    } else if (mode == 2 && frame >= 10) {
        mode = 0;
        frame = 0;
        if (step < 5) {
            step = step + 1;
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
void CMenuPcs::CmakeClose()
{
    int state = MenuS32(this, 0x82C);
    *reinterpret_cast<short*>(state + 0x10) = 2;
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
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& select = *reinterpret_cast<short*>(state + 0x26);
    short& row = *reinterpret_cast<short*>(state + 0x28);
    short& table = *reinterpret_cast<short*>(state + 0x2A);

    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);

    if (mode == 1) {
        if (frame < 30) {
            frame = frame + 1;
        } else if ((down & 0x200) != 0) {
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = -1;
        }
    } else if (mode == 0 && frame < 10) {
        frame = frame + 1;
    }

    if (mode != 1) {
        return;
    }

    if ((repeat & 0x4) != 0) {
        int maxRow = (select < 10) ? 4 : 5;
        row = (row < maxRow) ? static_cast<short>(row + 1) : 0;
    } else if ((repeat & 0x8) != 0) {
        int maxRow = (select < 10) ? 4 : 5;
        row = (row > 0) ? static_cast<short>(row - 1) : static_cast<short>(maxRow);
    }

    if ((repeat & 0x2) != 0 && row < 5) {
        select = (select < 0xB) ? static_cast<short>(select + 1) : 0;
    } else if ((repeat & 0x1) != 0 && row < 5) {
        select = (select > 0) ? static_cast<short>(select - 1) : 0xB;
    }

    if ((down & 0x20) != 0) {
        table = (table < 2) ? static_cast<short>(table + 1) : 0;
    } else if ((down & 0x40) != 0) {
        table = (table > 0) ? static_cast<short>(table - 1) : 2;
    }

    if ((down & 0x100) != 0) {
        char* name = reinterpret_cast<char*>(reinterpret_cast<unsigned char*>(this) + 0x85C);
        size_t len = strlen(name);
        if (row < 5) {
            if (len < 7) {
                int charIdx = (table * 5 + row + select) % 26;
                AddNameChara(static_cast<int>('A' + charIdx), static_cast<int>(len), 0, 0);
                name[len + 1] = '\0';
            }
        } else if (len > 0) {
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = 1;
        }
    } else if ((down & 0x200) != 0) {
        char* name = reinterpret_cast<char*>(reinterpret_cast<unsigned char*>(this) + 0x85C);
        size_t len = strlen(name);
        if (len > 0) {
            name[len - 1] = '\0';
        } else {
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = -1;
        }
    }

    if (select < 0) {
        select = 0;
    } else if (select > 0xB) {
        select = 0xB;
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
    DrawCmakeNameBase(1, 1.0f);
    DrawCmakeName(0, 0, reinterpret_cast<char*>(reinterpret_cast<unsigned char*>(this) + 0x85C), 1.0f);
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
        }

        if ((down & 0x100) != 0) {
            MenuS16(this, 0x860) = sel;
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = 1;
        } else if ((down & 0x200) != 0) {
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = -1;
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
    DrawCmakeWin(0.0f, 0.0f, 1.0f);
    DrawCmakePreviewChara(this);
    DrawCmakeTitle(2, 0.0f, alpha);

    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xFC);
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(0);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    unsigned char rgba[8];
    __ct__6CColorFUcUcUcUc(rgba, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    font->SetColor(*reinterpret_cast<GXColor*>(rgba));

    for (int i = 0; i < 2; ++i) {
        const char* txt = GetMenuStr__8CMenuPcsFi(this, 0x11 + i);
        float x = FLOAT_80333288 - static_cast<float>(font->GetWidth(txt)) * FLOAT_80333298;
        font->SetPosX(x);
        font->SetPosY(0x9C + i * 0x28 - FLOAT_803332f4);
        font->Draw(txt);
    }
    DrawInit__8CMenuPcsFv(this);

    if (*reinterpret_cast<short*>(MenuS32(this, 0x82C) + 0x10) == 1) {
        int sel = *reinterpret_cast<short*>(MenuS32(this, 0x82C) + 0x26);
        int frame = System.m_frameCounter & 7;
        DrawCursor__8CMenuPcsFiif(this, 0xA4 + frame, 0x9C + sel * 0x28, alpha);
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
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& tribe = *reinterpret_cast<short*>(state + 0x26);
    short& crest = *reinterpret_cast<short*>(state + 0x28);
    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);

    if (mode == 1) {
        if ((repeat & 0x4) != 0) {
            tribe = (tribe < 3) ? static_cast<short>(tribe + 1) : 0;
        } else if ((repeat & 0x8) != 0) {
            tribe = (tribe > 0) ? static_cast<short>(tribe - 1) : 3;
        }

        if ((repeat & 0x3) != 0) {
            crest = (crest < 3) ? static_cast<short>(crest + 1) : 0;
        }

        if ((down & 0x100) != 0) {
            MenuS16(this, 0x862) = tribe;
            ChgModel__8CMenuPcsFiiii(this, static_cast<int>(MenuS16(this, 0x86A)),
                static_cast<int>(MenuS16(this, 0x860)), static_cast<int>(tribe), static_cast<int>(MenuS16(this, 0x864)));
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = 1;
        } else if ((down & 0x200) != 0) {
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = -1;
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
    DrawCmakeCrest(MenuS16(this, 0x862), 0, 0, 1.0f);
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
    short& mode = *reinterpret_cast<short*>(state + 0x10);
    short& frame = *reinterpret_cast<short*>(state + 0x22);
    short& job = *reinterpret_cast<short*>(state + 0x26);
    unsigned short repeat = GetButtonRepeat__8CMenuPcsFi(this, 0);
    unsigned short down = GetButtonDown__8CMenuPcsFi(this, 0);

    if (mode == 1) {
        if ((repeat & 0x4) != 0) {
            job = (job < 7) ? static_cast<short>(job + 1) : 0;
        } else if ((repeat & 0x8) != 0) {
            job = (job > 0) ? static_cast<short>(job - 1) : 7;
        }

        if ((repeat & 0x3) != 0) {
            job = (job < 4) ? static_cast<short>(job + 4) : static_cast<short>(job - 4);
        }

        if ((down & 0x100) != 0) {
            MenuS16(this, 0x864) = job;
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = 1;
            SetSingMakeChara();
        } else if ((down & 0x200) != 0) {
            mode = 2;
            frame = 0;
            *reinterpret_cast<short*>(state + 0x1E) = -1;
            ChgModel__8CMenuPcsFiiii(this, static_cast<int>(MenuS16(this, 0x86A)), -1, -1, -1);
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
    float alpha = CalcCmakeFadeAlpha(this);
    DrawWMFrame0__8CMenuPcsFif(this, 1, FLOAT_80333258);
    DrawCmakeWin(0.0f, 0.0f, 1.0f);
    DrawCmakePreviewChara(this);
    DrawCmakeTitle(5, 0.0f, alpha);

    CFont* font = *reinterpret_cast<CFont**>(reinterpret_cast<unsigned char*>(this) + 0xFC);
    font->SetMargin(FLOAT_80333258);
    font->SetShadow(0);
    font->SetScale(FLOAT_80333258);
    font->DrawInit();

    int a = static_cast<int>(static_cast<double>(FLOAT_80333240) * alpha);
    unsigned char rgba[8];
    __ct__6CColorFUcUcUcUc(rgba, 0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a));
    font->SetColor(*reinterpret_cast<GXColor*>(rgba));

    for (int i = 0; i < 8; ++i) {
        const char* txt = GetJobStr__8CMenuPcsFi(this, i);
        float x = (i < 4) ? 272.0f : 424.0f;
        int row = (i < 4) ? i : (i - 4);
        font->SetPosX(x);
        font->SetPosY(0x70 + row * 0x28 - FLOAT_803332f4);
        font->Draw(txt);
    }

    if (*reinterpret_cast<short*>(MenuS32(this, 0x82C) + 0x10) == 1) {
        int sel = *reinterpret_cast<short*>(MenuS32(this, 0x82C) + 0x26);
        int cursorX = (sel < 4) ? 0x110 : 0x1A8;
        int cursorY = 0x70 + (sel & 3) * 0x28;
        DrawCursor__8CMenuPcsFiif(this, cursorX - 0x18 + (System.m_frameCounter & 7), cursorY, alpha);
    }

    DrawInit__8CMenuPcsFv(this);
    if ((*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) != 3)) {
        DrawMcWin__8CMenuPcsFss(this, -1, 0);
        if (*reinterpret_cast<short*>(MenuS32(this, 0x848) + 10) == 1) {
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

    DrawCmakeTitle(6, 0.0f, 1.0f);
    DrawCmakeCharaText(6, 1.0f);
    DrawCmakeCrest(MenuS16(this, 0x862), 0, 0, 1.0f);

    if (mode == 1) {
        DrawCmakeYesNo(*reinterpret_cast<short*>(state + 0x26) + 1, 1.0f);
    } else {
        DrawCmakeYesNo(0, 1.0f);
    }

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
    DrawCmakeTitle(7, 0.0f, 1.0f);
    DrawCmakeCharaText(7, 1.0f);
    DrawCmakeCrest(MenuS16(this, 0x862), 0, 0, 1.0f);
    DrawCmakeYesNo(0, 1.0f);
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
void CMenuPcs::CmakeVillageCtrl()
{
    calcVillageMenu();
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
    drawVillageMenu();
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
    (void)alpha;
    CalcSingleCMakeChara();
}
