#include "ffcc/math.h"
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
    ref->Release();
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

#ifdef VERSION_GCCJGC
#include "ffcc/cmake_jp.inc"
static const char s_cmakeSubfontPath[] = "dvd/menu/subfont.fnt";
static const char s_cmake_cpp[] = "cmake.cpp";
#define CMAKE_SOURCE_NAME s_cmake_cpp
#else
#define CMAKE_SOURCE_NAME "cmake.cpp"
static const char* s_NameEntryStr[] = {
    "ABCDEFGHIJKL",
    "MNOPQRSTUVWX",
    "YZ \xC0\xC1\xC2\xC4\x8C\xC7\xC8\xC9\xCA",
    "\xCB\xCC\xCD\xCE\xCF\xD1\xD2\xD3\xD4\xD6\xD9\xDA",
    "\xDB\xDC\xDF         ",
    "abcdefghijkl",
    "mnopqrstuvwx",
    "yz \xE0\xE1\xE2\xE4\x9C\xE7\xE8\xE9\xEA",
    "\xEB\xEC\xED\xEE\xEF\xF1\xF2\xF3\xF4\xF6\xF9\xFA",
    "\xFB\xFC\xDF         ",
    "0123456789-#",
    "!\xA1?\xBF%&\xB0\x22'()@",
    "*,./:;<=>[]_",
    "|\xAB\xBB\x82\x84       ",
    "            "
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
#ifndef VERSION_GCCJGC
static const char s_world51[] = "world51";
#endif

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

static inline void LoadCmakeVillageName()
{
    strcpy(s_CmakeInfo.m_name, Game.m_gameWork.m_townName);
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
        state = character = 0;
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
inline void GetChara(char* text, int index, char* dst)
{
    dst[0] = '\0';
    int length = strlen(text);
    if (length != 0) {
        int position;
        int character;
        character = 0;
        position = 0;
        for (; length > 0; --length, ++position) {
            if (character == index) {
                dst[0] = text[position];
                dst[1] = '\0';
                break;
            }
            ++character;
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
#ifdef VERSION_GCCJGC
static inline int GetCharaType(char* text, int index)
{
    int length = strlen(text);
    if (length == 0) {
        return -1;
    }
    int position;
    int state;
    int character;
    state = character = 0;
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
            return state != 0;
        }
        if (state != 1) {
            ++character;
        }
    }
    return -1;
}
#else
inline int GetCharaType(char* text, int index)
{
    int length = strlen(text);
    if (length == 0) {
        return -1;
    }
    return 0;
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
    int position;
    int state;
    int character;
    state = character = 0;
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
        if (state != 1) {
            ++character;
        }
    }
    return character;
}
#else
inline int GetCharaCnt(char* text)
{
    int length = strlen(text);
    if (length != 0) {
        return length;
    }
    return 0;
}
#endif

/*
 * --INFO--
 * PAL Address: 0x80173BA4
 * PAL Size: 2984b
 * EN Address: 0x80172B20
 * EN Size: 2984b
 * JP Address: 0x8016E69C
 * JP Size: 2984b
 */
void CMenuPcs::CalcSingCMake()
{
    short down;
    short repeat;
    int result;

    if (m_cmakeState->m_initialized == 0) {
        InitFrame0Info();
        memset(&s_CmakeInfo, 0, sizeof(s_CmakeInfo));
        m_cmakeState->m_initialized = 1;
        m_cmakeState->m_selectionInitialized = 0;
        s_OldMenu = -1;
        m_menuWindowInfo->state = 3;
    }

    switch (m_cmakeState->m_step) {
    case 0:
        if (m_cmakeState->m_mode == 0) {
            CalcWMFrame0(m_cmakeState->m_frame - 10);
            int done;
            if (m_cmakeState->m_frame >= 10) {
                m_cmakeState->m_select = 0;
                m_cmakeState->m_row = 0;
                m_cmakeState->m_table = 0;
                m_cmakeState->m_subSelect = 0;
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        } else if (m_cmakeState->m_mode == 1) {
            result = 0;
        } else {
            CalcWMFrame0(-m_cmakeState->m_frame);
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    case 1:
        if (m_cmakeState->m_mode == 0) {
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        } else if (m_cmakeState->m_mode == 1) {
            result = CmakeNameCtrl();
        } else {
            int done;
            if (m_cmakeState->m_frame >= 10) {
                if (m_cmakeState->m_resultDir < 0) {
                    ChgModel(static_cast<int>(m_singleCmakeSlot), -1, -1, -1);
                }
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    case 2: {
        if (m_cmakeState->m_mode == 0) {
            if (m_cmakeState->m_selectionInitialized == 0) {
                m_cmakeState->m_select = 0;
                m_cmakeState->m_selectionInitialized = 1;
            }
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        } else if (m_cmakeState->m_mode == 1) {
            down = Pad.GetButtonDown(0);
            repeat = Pad.GetButtonRepeat(0);

            int done;
            if (repeat == 0) {
                done = 0;
            } else {
                if ((repeat & 0xC) != 0) {
                    m_cmakeState->m_select ^= 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
                if ((repeat & 0xC) == 0) {
                    if ((down & 0x100) != 0) {
                        s_CmakeInfo.m_gender = static_cast<signed char>(m_cmakeState->m_select);
                        m_cmakeState->m_resultDir = 1;
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        done = 1;
                        goto case2_out;
                    }
                    if ((down & 0x200) != 0) {
                        m_cmakeState->m_resultDir = -1;
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
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    }
    case 3:
        if (m_cmakeState->m_mode == 0) {
            if (m_cmakeState->m_selectionInitialized == 0) {
                m_cmakeState->m_select = 0;
                m_cmakeState->m_row = 0;
                m_cmakeState->m_fieldSelect = 0;
                m_cmakeState->m_selectionInitialized = 1;
            }
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        } else if (m_cmakeState->m_mode == 1) {
            result = CmakeTribeCtrl();
        } else {
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    case 4:
        if (m_cmakeState->m_mode == 0) {
            if (m_cmakeState->m_selectionInitialized == 0) {
                m_cmakeState->m_select = 0;
                m_cmakeState->m_selectionInitialized = 1;
            }
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        } else if (m_cmakeState->m_mode == 1) {
            result = CmakeJobCtrl();
        } else {
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        }
        break;
    case 5: {
        if (m_cmakeState->m_mode == 0) {
            if (m_cmakeState->m_selectionInitialized == 0) {
                m_cmakeState->m_select = 0;
                m_cmakeState->m_selectionInitialized = 1;
            }
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        } else if (m_cmakeState->m_mode == 1) {
            down = Pad.GetButtonDown(0);
            repeat = Pad.GetButtonRepeat(0);

            int done;
            if (repeat == 0) {
                done = 0;
            } else {
                if ((repeat & 3) != 0) {
                    m_cmakeState->m_select ^= 1;
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }
                if ((repeat & 3) == 0) {
                    if ((down & 0x100) != 0) {
                        if (m_cmakeState->m_select == 0) {
                            m_cmakeState->m_resultDir = 1;
                            m_wmCharaAnimState[m_singleCmakeSlot].m_nextAnimIndex = 3;

                            CCaravanWork* caravanWork;
                            int slot = static_cast<int>(m_singleCmakeSlot);
                            int modelNo = GetModelNo(static_cast<int>(s_CmakeInfo.m_tribe), static_cast<int>(s_CmakeInfo.m_hair),
                                static_cast<int>(s_CmakeInfo.m_gender));
                            m_wm.m_charaModelData[slot].m_modelNo = modelNo;

                            caravanWork = &Game.m_caravanWorkArr[slot];
                            m_wm.m_charaSelectData->m_confirmed = 1;
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
                                m_cmakeState->m_stepTimer = animWait;
                            }
                        } else {
                            m_cmakeState->m_resultDir = -1;
                        }
                        Sound.PlaySe(0x33, 0x40, 0x7F, 0);
                        done = 1;
                        goto case5_out;
                    }
                    if ((down & 0x200) != 0) {
                        m_cmakeState->m_resultDir = -1;
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
            if (static_cast<int>(m_cmakeState->m_stepTimer) != 0) {
                m_cmakeState->m_stepTimer =
                    static_cast<short>(m_cmakeState->m_stepTimer - 1);
                done = 0;
            } else {
                if (m_cmakeState->m_frame >= 10) {
                    done = 1;
                } else {
                    m_cmakeState->m_frame++;
                    done = 0;
                }
            }
            result = done;
        }
        break;
    }
    case 6: {
        if (m_cmakeState->m_mode == 0) {
            if (m_cmakeState->m_selectionInitialized == 0) {
                m_cmakeState->m_select = 0;
                m_cmakeState->m_selectionInitialized = 1;
            }
            int done;
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
                done = 0;
            }
            result = done;
        } else if (m_cmakeState->m_mode == 1) {
            down = Pad.GetButtonDown(0);
            repeat = Pad.GetButtonRepeat(0);

            int done;
            if (repeat == 0) {
                done = 0;
            } else {
                if ((repeat & 0x8) != 0) {
                    if (static_cast<int>(m_cmakeState->m_select) != 0) {
                        m_cmakeState->m_select =
                            static_cast<short>(m_cmakeState->m_select - 1);
                    } else {
                        m_cmakeState->m_select = 3;
                    }
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                } else if ((repeat & 0x4) != 0) {
                    if (m_cmakeState->m_select < 3) {
                        m_cmakeState->m_select =
                            static_cast<short>(m_cmakeState->m_select + 1);
                    } else {
                        m_cmakeState->m_select = 0;
                    }
                    Sound.PlaySe(1, 0x40, 0x7F, 0);
                }

                if ((repeat & 0xC) == 0) {
                    if ((down & 0x100) != 0) {
                        if (m_cmakeState->m_select < 3) {
                            ChgModel(static_cast<int>(m_singleCmakeSlot), -1, -1, -1);
                        }
                        m_cmakeState->m_resultDir = 1;
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
            if (m_cmakeState->m_frame >= 10) {
                done = 1;
            } else {
                m_cmakeState->m_frame++;
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
    m_cmakeState->m_resultFlag = static_cast<short>(result);
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

    switch (m_cmakeState->m_step) {
    case 0:
        CmakeDraw();
        if (m_cmakeState->m_resultFlag != 0 && m_cmakeState->m_mode == 0) {
            m_cmakeState->m_step = m_cmakeState->m_step + 1;
            m_cmakeState->m_frame = 0;
            m_cmakeState->m_resultFlag = 0;
            m_cmakeState->m_selectionInitialized = 0;
        } else if (m_cmakeState->m_resultFlag != 0 && m_cmakeState->m_mode == 2) {
            m_singleCmakeSlot = 999;
            m_cmakeState->m_resultValue = -1;
        }
        break;
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

    if (m_cmakeState->m_resultFlag == 0) {
        return;
    }

    if (m_cmakeState->m_mode < 2) {
        m_cmakeState->m_mode++;
        goto resetFrame;
    }

    s_OldMenu = static_cast<int>(m_cmakeState->m_step);

    if (m_cmakeState->m_step == 6) {
        m_cmakeState->m_step = static_cast<short>(m_cmakeState->m_select + 1);
    } else if (m_cmakeState->m_resultDir < 0) {
        if (m_cmakeState->m_step != 0) {
            if (m_cmakeState->m_step != 5) {
                m_cmakeState->m_step = static_cast<short>(m_cmakeState->m_step - 1);
            } else {
                m_cmakeState->m_step = static_cast<short>(m_cmakeState->m_step + 1);
            }
        }
    } else if (m_cmakeState->m_step != 5) {
        m_cmakeState->m_step = static_cast<short>(m_cmakeState->m_step + 1);
    } else {
        m_cmakeState->m_step = 0;
        m_cmakeState->m_mode = 2;
        goto initSelection;
    }

    if (m_cmakeState->m_step == 0) {
        m_cmakeState->m_mode = 2;
    } else {
        m_cmakeState->m_mode = 0;
    }

initSelection:
    m_cmakeState->m_selectionInitialized = 0;
resetFrame:
    m_cmakeState->m_frame = 0;
    m_menuWindowInfo->state = 3;
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD28 : CMAKE_TEX_WORLD28));
    MenuPcs.DrawRect(
        0, 214.0f, 32.0f, 112.0f, 56.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 474.0f, 32.0f, 112.0f, 56.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD45 : CMAKE_TEX_WORLD45));

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

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_CRYSTAL : CMAKE_TEX_CRYSTAL));
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
    float w;
    float y;
    float h;
    float v;

    if (page == 0) {
        w = 328.0f;
        y = 288.0f;
        h = 56.0f;
        v = 368.0f;
    } else {
        w = 280.0f;
        y = 268.0f;
        h = 64.0f;
        v = 304.0f;
    }

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(400.0 - w / 2.0)), y, w, h,
        0.0f, v, 1.0f, 1.0f, 0.0f);
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
    SetCmakeBlendMatColor(alpha);
#ifdef VERSION_GCCJGC
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 184.0f, 216.0f, 40.0f, 40.0f,
        256.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    double crestRightX = 576.0;
    int rightX = static_cast<int>(crestRightX);
    MenuPcs.DrawRect(
        0, static_cast<float>(rightX), 216.0f, 40.0f, 40.0f,
        256.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD29 : CMAKE_TEX_WORLD29));
    MenuPcs.DrawRect(
        0, 192.0f, 224.0f, 24.0f, 24.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        0, static_cast<float>(rightX + 8), 224.0f, 24.0f, 24.0f,
        24.0f, 0.0f, 1.0f, 1.0f, 0.0f);
#else
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? 0x68 : 0x41));
    MenuPcs.DrawRect(
        0, 184.0f, 216.0f, 48.0f, 48.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    double crestRightX = 568.0;
    MenuPcs.DrawRect(
        0, static_cast<float>(static_cast<int>(crestRightX)), 216.0f, 48.0f, 48.0f,
        48.0f, 0.0f, 1.0f, 1.0f, 0.0f);
#endif
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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 480.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(
        8, 552.0f, 368.0f, 48.0f, 32.0f,
        296.0f, 264.0f, 1.0f, 1.0f, 0.0f);

    if (yesNoSel != 0) {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD44 : CMAKE_TEX_WORLD44));
        MenuPcs.DrawRect(
            0, 516.0f, 360.0f, 48.0f, 48.0f,
            128.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    CFont* font = GetFont22();
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
inline void CMenuPcs::DrawCmakeBallCursor(int x, int y, float alpha)
{
    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD44 : CMAKE_TEX_WORLD44));
    MenuPcs.DrawRect(
        0, static_cast<float>(x), static_cast<float>(y), 48.0f, 48.0f,
        128.0f, 0.0f, 1.0f, 1.0f, 0.0f);
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
inline void CMenuPcs::DrawCmakeCharaText(int table, float alpha)
{
    CFont* font;
    if (m_menuResultCode != 0) {
        font = GetFontItem();
    } else {
        font = GetFont23();
    }
    font->SetShadow(0);
    font->SetScale(1.0f);
    font->DrawInit();
    font->SetFixed(1);
    font->SetMargin(4.9f);
    SetCmakeFontColor(font, alpha);

    int y;
    int i;
    int tableBase = table * 5;
    const char* rowText;
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

    font->SetFixed(0);
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

    CFont* font = GetFont22();
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
        char* name = s_CmakeInfo.m_name;
        int count = GetCharaCnt(name);
        if (count == 0) {
            return -1;
        }
        int length = strlen(s_CmakeInfo.m_name);
        if (GetCharaType(name, count - 1) == 0) {
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
            if (strcmp(picked, "\x81\x4A") != 0 && strcmp(picked, "\x81\x4B") != 0) {
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
        if (type != 0 && strcmp(picked, "\x81\x4A") == 0) {
            int group;
            int pos;
            char* last = &s_CmakeInfo.m_name[strlen(s_CmakeInfo.m_name) - 2];
            for (group = 0; group < 2; ++group) {
                text = const_cast<char*>(s_NameEntryVoiced[group]);
                int length = strlen(text);
                for (pos = 0; pos < length; pos += 2, text += 2) {
                    if (memcmp(text, last, 2) == 0) {
                        ++last[1];
                        return 0;
                    }
                }
            }
            if (memcmp(last, "\x83\x45", 2) == 0) {
                strcpy(last, "\x83\x94");
            } else {
                if (count >= 7) {
                    return -1;
                }
                strcat(s_CmakeInfo.m_name, picked);
            }
            return 0;
        } else if (type != 0 && strcmp(picked, "\x81\x4B") == 0) {
            char* last = &s_CmakeInfo.m_name[strlen(s_CmakeInfo.m_name) - 2];
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
inline int CMenuPcs::AddNameChara(int add, int column, int row, int table)
{
    if (add == 0) {
        char* name = s_CmakeInfo.m_name;
        int count = GetCharaCnt(name);
        if (count == 0) {
            return -1;
        }
        int length = strlen(s_CmakeInfo.m_name);
        if (GetCharaType(name, count - 1) == 0) {
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
            return -1;
        }
        GetChara(text, column, picked);
        if (count == 0) {
            strcat(s_CmakeInfo.m_name, picked);
            return 0;
        }
        int type = GetCharaType(text, count - 1);
        if (type == 0 && count >= 7) {
            return -1;
        }
        strcat(s_CmakeInfo.m_name, picked);
    }
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

    CFont* font;
    float yesW;
    int yesX;
    float noW;
    int noX;
    const char* text;

    font = GetFont22();
    font->SetMargin(1.0f);
    font->SetShadow(1);
    font->SetScale(1.0f);
    font->DrawInit();
    font->SetTlut(7);

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(alpha255)).color);

    text = GetMenuStr(1);
#ifdef VERSION_GCCJGC
    font->GetWidth(text);
    yesX = 460;
    font->SetPosX(static_cast<float>(yesX));
    font->SetPosY(373.0f);
#else
    yesW = static_cast<float>(font->GetWidth(text));
    yesX = 0x1D0;
    yesX += (48.0f - yesW) / 2.0f;
    font->SetPosX(static_cast<float>(yesX));
    font->SetPosY(369.0f);
#endif
    font->Draw(text);

    text = GetMenuStr(2);
#ifdef VERSION_GCCJGC
    font->GetWidth(text);
    noX = 532;
    font->SetPosX(static_cast<float>(noX));
    font->SetPosY(373.0f);
#else
    noW = static_cast<float>(font->GetWidth(text));
    noX = 0x218;
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
 * PAL Address: UNUSED
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeOpen()
{
    CalcWMFrame0(m_cmakeState->m_frame - 10);
    if (m_cmakeState->m_frame >= 10) {
        m_cmakeState->m_select = 0;
        m_cmakeState->m_row = 0;
        m_cmakeState->m_table = 0;
        m_cmakeState->m_subSelect = 0;
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeCtrl()
{
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeClose()
{
    CalcWMFrame0(-m_cmakeState->m_frame);
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 612b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::CmakeDraw()
{
    CmakeMenuState* state = m_cmakeState;
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
    DrawWMFrame0(1, alpha);

    DrawCmakeWin(0.0f, 0.0f, alpha);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeNameOpen()
{
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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

    down = Pad.GetButtonDown(0);
    repeat = Pad.GetButtonRepeat(0);

    if (repeat == 0) {
        return 0;
    }

    if (m_menuWindowInfo->state != 3) {
        if (m_menuWindowInfo->state == 1 && (down & 0x300) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            m_menuWindowInfo->state = 2;
        }
        return 0;
    }
    {
        if ((repeat & 0x8) != 0) {
            if (static_cast<int>(m_cmakeState->m_row) != 0) {
                m_cmakeState->m_row -= 1;
            } else if (m_cmakeState->m_select >= 10) {
                m_cmakeState->m_row = 5;
            } else {
                m_cmakeState->m_row = 4;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            if (m_cmakeState->m_row < (m_cmakeState->m_select >= 10 ? 5 : 4)) {
                m_cmakeState->m_row += 1;
            } else {
                m_cmakeState->m_row = 0;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0x1) != 0) {
            if (m_cmakeState->m_row >= 5) {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else {
                CmakeMenuState* state = m_cmakeState;
                if (static_cast<int>(state->m_select) != 0) {
                    state->m_select -= 1;
                } else {
                    state->m_select = 0xB;
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        } else if ((repeat & 0x2) != 0) {
            if (m_cmakeState->m_row >= 5) {
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else {
                CmakeMenuState* state = m_cmakeState;
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
                m_cmakeState->m_table -= 1;
                if (m_cmakeState->m_table < 0) {
                    m_cmakeState->m_table = CMAKE_NAME_PAGE_COUNT - 1;
                }
                Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
            } else if ((down & 0x20) != 0) {
                m_cmakeState->m_table += 1;
                if (m_cmakeState->m_table > CMAKE_NAME_PAGE_COUNT - 1) {
                    m_cmakeState->m_table = 0;
                }
                Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
            } else if ((down & 0x1000) != 0) {
                m_cmakeState->m_select = 0xB;
                m_cmakeState->m_row = 5;
                Sound.PlaySe(2, 0x40, 0x7F, 0);
            } else if ((down & 0x100) != 0) {
                if (m_cmakeState->m_row >= 5) {
                    if (GetCharaCnt(s_CmakeInfo.m_name) == 0) {
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

                    int i;
                    int found = 0;
                    for (i = 0; i < 8; i++) {
                        if (i != m_singleCmakeSlot && Game.m_caravanWorkArr[i].m_shopState != 0 &&
#ifndef VERSION_GCCJGC
                            Game.m_caravanWorkArr[i].m_caravanLocalFlags != 1 &&
#endif
                            strcmp(s_CmakeInfo.m_name, reinterpret_cast<char*>(Game.m_caravanWorkArr[i].m_name)) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (found == 0) {
                        for (i = 0; i < 0x100; i++) {
                            if (strcmp(Game.m_cFlatDataArr[1].TableStrings(2)[i], s_CmakeInfo.m_name) == 0) {
                                found = 1;
                                break;
                            }
                        }
                    }
                    if (found != 0) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                        short winX;
                        short winY;
                        GetWinSize(0x14, &winX, &winY, 0);
                        SetMcWinInfo((int)winX, (int)winY);
                        m_menuWindowInfo->state = 0;
                    } else {
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                        m_cmakeState->m_resultDir = 1;
                        return 1;
                    }
                } else {
                    int ret = AddNameChara(1, m_cmakeState->m_select, m_cmakeState->m_row, m_cmakeState->m_table);
                    if (ret != 0) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    } else {
                        if (GetCharaCnt(s_CmakeInfo.m_name) >= 7) {
                            m_cmakeState->m_select = 0xB;
                            m_cmakeState->m_row = 5;
                        }
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                    }
                }
            } else if ((down & 0x200) != 0) {
                if (GetCharaCnt(s_CmakeInfo.m_name) != 0) {
                    int bsRet = AddNameChara(0, m_cmakeState->m_select, m_cmakeState->m_row, m_cmakeState->m_table);
                    if (bsRet != 0) {
                        Sound.PlaySe(4, 0x40, 0x7F, 0);
                    } else {
                        Sound.PlaySe(3, 0x40, 0x7F, 0);
                    }
                } else {
                    Sound.PlaySe(0x34, 0x40, 0x7F, 0);
                    ChgModel(static_cast<int>(m_singleCmakeSlot), -1, -1, -1);
                    m_cmakeState->m_resultDir = -1;
                    return -1;
                }
            }
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeNameClose()
{
    if (m_cmakeState->m_frame >= 10) {
        if (m_cmakeState->m_resultDir < 0) {
            ChgModel(static_cast<int>(m_singleCmakeSlot), -1, -1, -1);
        }
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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
    CmakeMenuState* state = m_cmakeState;
    int frame = static_cast<int>(state->m_frame) - 1;
    float alpha;
    int x;
    int y;
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
    DrawCmakeWin(0.0f, 0.0f, 1.0f);

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 192.0f, 56.0f, 416.0f, 264.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    if ((s_OldMenu == 2) && (m_cmakeState->m_mode == 0)) {
        DrawSingleCMakeChara(1.0f);
        DrawCmakeTitle(1, alpha, 1.0f);
    } else if ((m_cmakeState->m_mode != 2) ||
               (m_cmakeState->m_mode == 2 && m_cmakeState->m_resultDir == -1)) {
        DrawSingleCMakeChara(alpha);
        DrawCmakeTitle(1, 1.0f, alpha);
    } else {
        DrawSingleCMakeChara(1.0f);
        DrawCmakeTitle(1, alpha, 1.0f);
    }

    DrawCmakeNameBase(1, alpha);
    DrawCmakePageMark(alpha);

    if ((m_cmakeState->m_mode == 1) && (m_cmakeState->m_row < 5)) {
        x = 0xE5;
        y = 0x63;
        x += 26.9f * static_cast<float>(m_cmakeState->m_select);
        y += m_cmakeState->m_row * 0x20;
        DrawCmakeBallCursor(x, y, 1.0f);
    }

    DrawCmakeCharaText(m_cmakeState->m_table, alpha);

    if ((m_cmakeState->m_mode == 1) && (m_cmakeState->m_row < 5)) {
        x = 0xC8;
        y = 0x70;
        x += 26.9f * static_cast<float>(m_cmakeState->m_select);
        y += m_cmakeState->m_row * 0x20;
        x += static_cast<int>(System.m_frameCounter) % 8;
        DrawCursor(x, y, 1.0f);
    }

    int nameCursor = (m_cmakeState->m_mode == 1) ? 1 : 0;
    if (m_cmakeState->m_row >= 5) {
        nameCursor = 0;
    }
    if (GetCharaCnt(s_CmakeInfo.m_name) >= 7) {
        nameCursor = 0;
    }
    DrawCmakeName(0, nameCursor, s_CmakeInfo.m_name, alpha);
    DrawCmakeDecision((m_cmakeState->m_row >= 5) ? 1 : 0, alpha);

    if (m_menuWindowInfo->state != 3) {
        DrawMcWin(-1, 0);
        if (m_menuWindowInfo->state == 1) {
            DrawMcWinMess(0x14, 0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeSexOpen()
{
    if (m_cmakeState->m_selectionInitialized == 0) {
        m_cmakeState->m_select = 0;
        m_cmakeState->m_selectionInitialized = 1;
    }
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeSexCtrl()
{
    short down = Pad.GetButtonDown(0);
    short repeat = Pad.GetButtonRepeat(0);

    if (repeat == 0) {
        return 0;
    }

    if ((repeat & 0xC) != 0) {
        m_cmakeState->m_select ^= 1;
        Sound.PlaySe(1, 0x40, 0x7F, 0);
    }
    if ((repeat & 0xC) == 0) {
        if ((down & 0x100) != 0) {
            s_CmakeInfo.m_gender = static_cast<signed char>(m_cmakeState->m_select);
            m_cmakeState->m_resultDir = 1;
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            return 1;
        }
        if ((down & 0x200) != 0) {
            m_cmakeState->m_resultDir = -1;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            return 1;
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeSexClose()
{
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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
    CmakeMenuState* state = m_cmakeState;
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

    DrawCmakeWin(0.0f, 0.0f, 1.0f);

    DrawSingleCMakeChara(1.0f);

    SetCmakeBlendMatColor(alpha);
    a255 = 255.0f * alpha;
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    float sexW = 256.0f;
    float sexH = 162.4615478515625f;
    MenuPcs.DrawRect(
        0,
        static_cast<float>(static_cast<int>(-(sexW / 2.0 - 400.0))),
        static_cast<float>(static_cast<int>(-(sexH / 2.0 - 188.0))),
        416.0f, 264.0f,
        0.0f, 0.0f, 0.6153846383094788f, 0.6153846383094788f, 0.0f);
    DrawCmakeTitle(2, alpha, 1.0f);

    CFont* font = GetFont23();
    font->SetMargin(1.0f);
#ifdef VERSION_GCCP01
    font->SetShadow(0);
#else
    font->SetShadow(1);
#endif
    font->SetScale(1.0f);
    font->DrawInit();

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a255)).color);

#ifdef VERSION_GCCP01
    float labelWidth = 0.0f;
#else
    float labelWidth;
#endif
    int y;
    int i;
    for (i = 0, y = 0x9C; i < 2; ++i, y += 0x28) {
        const char* txt = GetMenuStr(0x11 + i);
        float width = static_cast<float>(font->GetWidth(txt));
#ifdef VERSION_GCCP01
        if (labelWidth < width) {
            labelWidth = width;
        }
#else
        labelWidth = width;
#endif
        float x = static_cast<float>(-(width / 2.0 - 400.0));
        font->SetPosX(x);
#ifdef VERSION_GCCJGC
        font->SetPosY(static_cast<float>(y));
#else
        font->SetPosY(static_cast<float>(y) - 4.0f);
#endif
        font->Draw(txt);
    }
    DrawInit();

    if (m_cmakeState->m_mode == 1) {
        int sel = m_cmakeState->m_select;
        float cx = 400.0 - labelWidth / 2.0;
        float cy = 156.0f;
        cy += static_cast<float>(sel * 0x28);
        cx += static_cast<float>(static_cast<int>(System.m_frameCounter) % 8);
        DrawCursor(static_cast<int>(cx - labelWidth / 2.0), static_cast<int>(cy), 1.0f);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeTribeOpen()
{
    if (m_cmakeState->m_selectionInitialized == 0) {
        m_cmakeState->m_select = 0;
        m_cmakeState->m_row = 0;
        m_cmakeState->m_fieldSelect = 0;
        m_cmakeState->m_selectionInitialized = 1;
    }
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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

    if (m_menuWindowInfo->state != 3) {
        if (m_menuWindowInfo->state == 1 && (down & 0x300) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            m_menuWindowInfo->state = 2;
        }
        return 0;
    } else {
        int fieldSelect = m_cmakeState->m_fieldSelect;
        int tribeCount = (fieldSelect != 0) ? 4 : 4;

        if ((repeat & 0x8) != 0) {
            short* values = &m_cmakeState->m_select;
            int idx = fieldSelect;
            if (static_cast<int>(values[idx]) != 0) {
                values[idx] = static_cast<short>(values[idx] - 1);
            } else {
                values[idx] = static_cast<short>(tribeCount - 1);
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            short* values = &m_cmakeState->m_select;
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
                    m_cmakeState->m_fieldSelect = static_cast<short>(m_cmakeState->m_fieldSelect + 1);
                } else {
                    int slot;
                    for (slot = 0; slot < 8; ++slot) {
                        if ((Game.m_caravanWorkArr[slot].m_shopState != 0) &&
#ifndef VERSION_GCCJGC
                            (Game.m_caravanWorkArr[slot].m_caravanLocalFlags != 1) &&
#endif
                            (Game.m_caravanWorkArr[slot].m_tribeId == m_cmakeState->m_select) &&
                            (Game.m_caravanWorkArr[slot].m_appearanceVariant == m_cmakeState->m_row) &&
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
                        m_menuWindowInfo->state = 0;
                        return 0;
                    } else {
                        s_CmakeInfo.m_tribe = static_cast<signed char>(m_cmakeState->m_select);
                        s_CmakeInfo.m_hair = static_cast<signed char>(m_cmakeState->m_row);
                        ChgModel(static_cast<int>(m_singleCmakeSlot),
                                 static_cast<int>(s_CmakeInfo.m_tribe),
                                 static_cast<int>(s_CmakeInfo.m_hair),
                                 static_cast<int>(s_CmakeInfo.m_gender));
                        m_cmakeState->m_resultDir = 1;
                        return 1;
                    }
                }
            } else if ((down & 0x200) != 0) {
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                if (fieldSelect == 0) {
                    m_cmakeState->m_resultDir = -1;
                    return 1;
                }

                m_cmakeState->m_fieldSelect = static_cast<short>(m_cmakeState->m_fieldSelect - 1);
            }
        }

        return 0;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeTribeClose()
{
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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
    CmakeMenuState* state = m_cmakeState;
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

    DrawCmakeWin(0.0f, 0.0f, 1.0f);

    DrawSingleCMakeChara(1.0f);

    SetCmakeBlendMatColor(alpha);
    a255 = 255.0f * alpha;
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
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
        int tribe = m_cmakeState->m_select;
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD40));
        MenuPcs.DrawRect(
            0,
            351.0f, 96.0f, 184.0f, 184.0f,
            static_cast<float>((tribe & 1) * 0xB8),
            static_cast<float>((tribe / 2) * 0xB8),
            1.0f, 1.0f, 0.0f);
    }

    int i;
    CFont* font;
    int y;
    int hairBase;
    const char* txt;
    font = GetFont23();
    font->SetMargin(1.0f);
    font->SetShadow(0);
    font->SetScale(1.0f);
    font->DrawInit();
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a255)).color);

    y = 0x88;
    for (i = 0; i < 4; i++, y += 0x1C) {
        txt = GetTribeStr(i);
        font->SetPosX(264.0f);
#ifdef VERSION_GCCJGC
        font->SetPosY(static_cast<float>(y));
#else
        font->SetPosY(static_cast<float>(y) - 4.0f);
#endif
        font->Draw(txt);
    }

    font = GetFont22();
    font->SetMargin(1.0f);
    font->SetShadow(1);
    font->SetScale(1.0f);
    font->DrawInit();
    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(a255)).color);
    font->SetTlut(6);

    hairBase = m_cmakeState->m_select * 8;
    if (s_CmakeInfo.m_gender != 0) {
        hairBase += 4;
    }

    for (i = 0, y = 0x88; i < 4; i++, y += 0x1C) {
        txt = GetHairStr(hairBase + i);
#ifdef VERSION_GCCJGC
        font->SetPosX(424.0f);
        font->SetPosY(static_cast<float>(y));
#else
        font->SetPosX(384.0f);
        font->SetPosY(static_cast<float>(y) - 4.0f);
#endif
        font->Draw(txt);
    }

    DrawInit();

    if (m_cmakeState->m_mode == 1) {
        float tribeX = 228.0f;
        float cursorY = static_cast<float>(0x88 + m_cmakeState->m_select * 0x1C);

        if (m_cmakeState->m_fieldSelect == 0) {
            tribeX += static_cast<float>(static_cast<int>(System.m_frameCounter) % 8);
            DrawCursor(static_cast<int>(tribeX), static_cast<int>(cursorY), alpha);
        } else {
            if ((System.m_frameCounter & 1) != 0) {
                DrawCursor(static_cast<int>(tribeX), static_cast<int>(cursorY), alpha);
            }

#ifdef VERSION_GCCJGC
            float hairX = 388.0f;
#else
            float hairX = 348.0f;
#endif
            hairX += static_cast<float>(static_cast<int>(System.m_frameCounter) % 8);
            DrawCursor(
                static_cast<int>(hairX),
                static_cast<int>(static_cast<float>(0x88 + m_cmakeState->m_row * 0x1C)), alpha);
        }
    }

    if (m_menuWindowInfo->state != 3) {
        DrawMcWin(-1, 0);
        if (m_menuWindowInfo->state == 1) {
            DrawMcWinMess(0x15, 0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeJobOpen()
{
    if (m_cmakeState->m_selectionInitialized == 0) {
        m_cmakeState->m_select = 0;
        m_cmakeState->m_selectionInitialized = 1;
    }
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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

    if (m_menuWindowInfo->state != 3) {
        if (m_menuWindowInfo->state == 1 && (down & 0x300) != 0) {
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            m_menuWindowInfo->state = 2;
        }
        return 0;
    } else {
        if ((repeat & 0x8) != 0) {
            if ((m_cmakeState->m_select % 4) != 0) {
                m_cmakeState->m_select -= 1;
            } else {
                m_cmakeState->m_select += 3;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else if ((repeat & 0x4) != 0) {
            if ((m_cmakeState->m_select % 4) < 3) {
                m_cmakeState->m_select += 1;
            } else {
                m_cmakeState->m_select -= 3;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0x3) != 0) {
            if (m_cmakeState->m_select <= 3) {
                m_cmakeState->m_select += 4;
            } else {
                m_cmakeState->m_select -= 4;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((repeat & 0xF) == 0) {
            if ((down & 0x100) != 0) {
                int slot;
                for (slot = 0; slot < 8; ++slot) {
                    if (slot != m_singleCmakeSlot &&
                        Game.m_caravanWorkArr[slot].m_shopState != 0 &&
#ifndef VERSION_GCCJGC
                        Game.m_caravanWorkArr[slot].m_caravanLocalFlags != 1 &&
#endif
                        Game.m_caravanWorkArr[slot].m_jobType == m_cmakeState->m_select) {
                        break;
                    }
                }

                if (slot < 8) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                    short winX;
                    short winY;
                    GetWinSize(0x16, &winX, &winY, 0);
                    SetMcWinInfo((int)winX, (int)winY);
                    m_menuWindowInfo->state = 0;
                    return 0;
                } else {
                    s_CmakeInfo.m_job = static_cast<signed char>(m_cmakeState->m_select);
                    m_cmakeState->m_resultDir = 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                    return 1;
                }
            } else if ((down & 0x200) != 0) {
                ChgModel(static_cast<int>(m_singleCmakeSlot), -1, -1, -1);
                m_cmakeState->m_resultDir = -1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                return 1;
            }
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeJobClose()
{
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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
    CmakeMenuState* state = m_cmakeState;
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

    DrawCmakeWin(0.0f, 0.0f, 1.0f);

    DrawSingleCMakeChara(1.0f);

    SetCmakeBlendMatColor(alpha);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0,
        192.0f, 56.0f, 416.0f, 264.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    DrawCmakeTitle(5, alpha, 1.0f);

    CFont* font = GetFont23();
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

    if (m_cmakeState->m_mode == 1) {
        int sel = m_cmakeState->m_select;
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

    if (m_menuWindowInfo->state != 3) {
        DrawMcWin(-1, 0);
        if (m_menuWindowInfo->state == 1) {
            DrawMcWinMess(0x16, 0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeResultOpen()
{
    if (m_cmakeState->m_selectionInitialized == 0) {
        m_cmakeState->m_select = 0;
        m_cmakeState->m_selectionInitialized = 1;
    }
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 820b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeResultCtrl()
{
    short down = Pad.GetButtonDown(0);
    short repeat = Pad.GetButtonRepeat(0);

    if (repeat == 0) {
        return 0;
    }

    if ((repeat & 3) != 0) {
        m_cmakeState->m_select ^= 1;
        Sound.PlaySe(1, 0x40, 0x7F, 0);
    }
    if ((repeat & 3) == 0) {
        if ((down & 0x100) != 0) {
            if (m_cmakeState->m_select == 0) {
                m_cmakeState->m_resultDir = 1;
                m_wmCharaAnimState[m_singleCmakeSlot].m_nextAnimIndex = 3;
                SetSingMakeChara();
                {
                    short animWait = static_cast<short>(static_cast<int>(GetMaxAnimWait()));
                    m_cmakeState->m_stepTimer = animWait;
                }
            } else {
                m_cmakeState->m_resultDir = -1;
            }
            Sound.PlaySe(0x33, 0x40, 0x7F, 0);
            return 1;
        }
        if ((down & 0x200) != 0) {
            m_cmakeState->m_resultDir = -1;
            Sound.PlaySe(3, 0x40, 0x7F, 0);
            return 1;
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeResultClose()
{
    if (static_cast<int>(m_cmakeState->m_stepTimer) != 0) {
        m_cmakeState->m_stepTimer =
            static_cast<short>(m_cmakeState->m_stepTimer - 1);
        return 0;
    }
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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
    CmakeMenuState* state = m_cmakeState;
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

    DrawCmakeWin(0.0f, 0.0f, 1.0f);

    DrawSingleCMakeChara(1.0f);

    if ((m_cmakeState->m_mode == 2) && (m_cmakeState->m_resultDir < 0)) {
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    } else {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    if ((m_cmakeState->m_mode == 2) && (m_cmakeState->m_resultDir > 0)) {
        DrawCmakeTitle(6, 1.0f, alpha);
    } else {
        DrawCmakeTitle(6, alpha, 1.0f);
    }

    if ((m_cmakeState->m_mode == 2) && (m_cmakeState->m_resultDir < 0)) {
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
    if (m_cmakeState->m_mode == 1) {
        yesNoSel = m_cmakeState->m_select + 1;
    } else {
        yesNoSel = 0;
    }
    DrawCmakeYesNo(yesNoSel, alpha);

    if ((m_cmakeState->m_mode == 2) && (m_cmakeState->m_resultDir < 0)) {
        alpha = 1.0f;
    }

    CFont* labelFont = GetFont23();
    labelFont->SetMargin(1.0f);
    labelFont->SetShadow(0);
    labelFont->SetScale(1.0f);
    labelFont->DrawInit();

    labelFont->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).color);

#ifndef VERSION_GCCJGC
    char tribeWithComma[0x10];
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

    CFont* valueFont = GetFont22();
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
            strcpy(tribeWithComma, GetTribeStr(static_cast<int>(s_CmakeInfo.m_tribe)));
            strcat(tribeWithComma, ",");
            value = tribeWithComma;
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
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeResultOpen1()
{
    if (m_cmakeState->m_selectionInitialized == 0) {
        m_cmakeState->m_select = 0;
        m_cmakeState->m_selectionInitialized = 1;
    }
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 572b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeResultCtrl1()
{
    short down = Pad.GetButtonDown(0);
    short repeat = Pad.GetButtonRepeat(0);

    if (repeat == 0) {
        return 0;
    }

    if ((repeat & 0x8) != 0) {
        if (static_cast<int>(m_cmakeState->m_select) != 0) {
            m_cmakeState->m_select =
                static_cast<short>(m_cmakeState->m_select - 1);
        } else {
            m_cmakeState->m_select = 3;
        }
        Sound.PlaySe(1, 0x40, 0x7F, 0);
    } else if ((repeat & 0x4) != 0) {
        if (m_cmakeState->m_select < 3) {
            m_cmakeState->m_select =
                static_cast<short>(m_cmakeState->m_select + 1);
        } else {
            m_cmakeState->m_select = 0;
        }
        Sound.PlaySe(1, 0x40, 0x7F, 0);
    }

    if ((repeat & 0xC) == 0) {
        if ((down & 0x100) != 0) {
            if (m_cmakeState->m_select < 3) {
                ChgModel(static_cast<int>(m_singleCmakeSlot), -1, -1, -1);
            }
            m_cmakeState->m_resultDir = 1;
            Sound.PlaySe(2, 0x40, 0x7F, 0);
            return 1;
        }
        if ((down & 0x200) != 0) {
            Sound.PlaySe(4, 0x40, 0x7F, 0);
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline int CMenuPcs::CmakeResultClose1()
{
    if (m_cmakeState->m_frame >= 10) {
        return 1;
    }
    m_cmakeState->m_frame++;
    return 0;
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
    CmakeMenuState* state = m_cmakeState;
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
    float popupAlpha = (m_cmakeState->m_mode == 0) ? 1.0f : alpha;

    DrawWMFrame0(1, 1.0f);

    DrawCmakeWin(0.0f, 0.0f, 1.0f);

    DrawSingleCMakeChara(1.0f);

    if (m_cmakeState->m_mode == 0) {
        SetCmakeBlendMatColor(1.0f);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    } else {
        SetCmakeBlendMatColor(alpha);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
        MenuPcs.DrawRect(
            0, 192.0f, 56.0f, 416.0f, 264.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }
    DrawCmakeTitle(7, alpha, 1.0f);

    if (m_cmakeState->m_mode == 0) {
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

    CFont* labelFont = GetFont23();
    labelFont->SetMargin(1.0f);
    labelFont->SetShadow(0);
    labelFont->SetScale(1.0f);
    labelFont->DrawInit();

    labelFont->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<unsigned char>(255.0f * alpha)).color);

#ifndef VERSION_GCCJGC
    char tribeWithComma[0x10];
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

    CFont* valueFont = GetFont22();
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
            strcpy(tribeWithComma, txt);
            strcat(tribeWithComma, ",");
            txt = tribeWithComma;
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

    if (m_cmakeState->m_mode == 1) {
        float cursorX = 196.0f;
        cursorX += static_cast<float>(static_cast<int>(System.m_frameCounter) % 8);
        DrawCursor(static_cast<int>(cursorX), static_cast<int>(static_cast<float>(0x70 + m_cmakeState->m_select * 0x28)), alpha);
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
    CmakeMenuState* villageWork = static_cast<CmakeMenuState*>(m_cmakeVillageWork);
    short& select = villageWork->m_select;
    short& row = villageWork->m_row;
    short& table = villageWork->m_table;
    short repeat;
    short down;

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
            short curRow = row;
            if (curRow >= 5) {
            if (GetCharaCnt(s_CmakeInfo.m_name) == 0) {
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
            int ret = AddNameChara(1, select, curRow, table);
            if (ret != 0) {
                Sound.PlaySe(4, 0x40, 0x7f, 0);
            } else {
                if (GetCharaCnt(s_CmakeInfo.m_name) >= 7) {
                    select = 0xB;
                    row = 5;
                }
                Sound.PlaySe(2, 0x40, 0x7f, 0);
            }
            }
        } else if ((down & 0x200) != 0) {
            if (GetCharaCnt(s_CmakeInfo.m_name) != 0) {
                int bsRet = AddNameChara(0, select, row, table);
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
 * PAL Address: UNUSED
 * PAL Size: 40b
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
    CmakeMenuState* villageWork = static_cast<CmakeMenuState*>(m_cmakeVillageWork);
    int frame = static_cast<int>(villageWork->m_frame) - 1;
    float alpha;
    int x;
    int y;

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
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>((m_menuResultCode != 0) ? CMAKE_TEX_VILLAGE_WORLD27 : CMAKE_TEX_WORLD27));
    MenuPcs.DrawRect(
        0, 192.0f, 56.0f, 416.0f, 264.0f,
        0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    DrawCmakeTitle(0, 1.0f, alpha);
    DrawCmakeNameBase(0, alpha);
    DrawCmakePageMark(alpha);

    if (villageWork->m_mode == 1 && villageWork->m_row < 5) {
        x = 0xE5;
        y = 0x63;
        x += 26.9f * static_cast<float>(villageWork->m_select);
        y += villageWork->m_row * 0x20;
        DrawCmakeBallCursor(x, y, 1.0f);
    }

    DrawCmakeCharaText(villageWork->m_table, alpha);

    if (villageWork->m_mode == 1 && villageWork->m_row < 5) {
        x = 0xC8;
        y = 0x70;
        x += 26.9f * static_cast<float>(villageWork->m_select);
        y += villageWork->m_row * 0x20;
        x += static_cast<int>(System.m_frameCounter) % 8;
        DrawCursor(x, y, 1.0f);
    }

    int nameCursor = (villageWork->m_mode == 1) ? 1 : 0;
    if (villageWork->m_row >= 5) {
        nameCursor = 0;
    }
    if (GetCharaCnt(s_CmakeInfo.m_name) >= 7) {
        nameCursor = 0;
    }
    DrawCmakeName(1, nameCursor, s_CmakeInfo.m_name, alpha);
    DrawCmakeDecision((villageWork->m_row >= 5) ? 1 : 0, alpha);
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
inline void CMenuPcs::SetSingMakeChara()
{
    CCaravanWork* caravanWork;
    int slot = static_cast<int>(m_singleCmakeSlot);
    int modelNo = GetModelNo(static_cast<int>(s_CmakeInfo.m_tribe), static_cast<int>(s_CmakeInfo.m_hair),
        static_cast<int>(s_CmakeInfo.m_gender));
    m_wm.m_charaModelData[slot].m_modelNo = modelNo;

    caravanWork = &Game.m_caravanWorkArr[slot];
    m_wm.m_charaSelectData->m_confirmed = 1;
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
    if (m_menuResultCode == 0) {
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
    if (m_menuResultCode != 0) {
        if (Game.m_gameWork.m_menuStageMode == 0) {
            CFont*& font = m_fonts[CMAKE_FONT_VILLAGE];
            if (font != 0) {
                ReleaseRefObject(font);
                font = 0;
            }
        }

        freeTexture(8, 1, CMAKE_TEX_VILLAGE_CRYSTAL, CMAKE_VILLAGE_TEXTURE_COUNT);

        void*& villageWork = m_cmakeVillageWork;
        if (villageWork != nullptr) {
            operator delete(villageWork);
            villageWork = nullptr;
        }

        m_menuResultCode = 0;
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
    if (MenuU8(this, 0x16) != 0 && m_menuResultCode == 0) {
        if (m_menuResultCode == 0 && MenuU8(this, 0x16) != 0) {
            if (Game.m_gameWork.m_menuStageMode == 0) {
#ifdef VERSION_GCCJGC
                loadFont(2, const_cast<char*>(s_cmakeSubfontPath), 4, -1);
#else
                char path[128];
                sprintf(path, "dvd/%smenu/subfont.fnt", Game.GetLangString());
                loadFont(2, path, 4, -1);
#endif
            }

            loadTexture(PTR_s_world2, 8, 1, s_cmakeWorldTextureTable, CMAKE_TEX_VILLAGE_CRYSTAL, CMAKE_VILLAGE_TEXTURE_COUNT, 3);

            CMemory::CStage* stage = MenuPcs.m_menuStage;
            void*& villageWork = m_cmakeVillageWork;
#ifdef VERSION_GCCJGC
            const int allocationLine = 0xC17;
#elif defined(VERSION_GCCE01)
            const int allocationLine = 0xCB1;
#else
            const int allocationLine = 0xCB3;
#endif
            villageWork = operator new(0x48, stage, const_cast<char*>(CMAKE_SOURCE_NAME), allocationLine);
            memset(villageWork, 0, 0x48);
            LoadCmakeVillageName();
            m_menuResultCode = 1;
        }
    }

    short active = m_menuResultCode;
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
                void*& villageWork = m_cmakeVillageWork;
                if (villageWork != nullptr) {
                    operator delete(villageWork);
                    villageWork = nullptr;
                }
                m_menuResultCode = 0;
            }
        } else {
            CmakeMenuState* villageWork = static_cast<CmakeMenuState*>(m_cmakeVillageWork);
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
    if (m_menuResultCode != 0) {
        CmakeMenuState* villageWork = static_cast<CmakeMenuState*>(m_cmakeVillageWork);
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
    int slot = static_cast<int>(m_singleCmakeSlot);
    WmWorldObjInfo* modelWork = m_wm.m_worldObjData + slot + 0x20;

    if (GetCmakeCharaHandle(this, slot)->m_model == nullptr ||
        GetCmakeCharaHandle(this, slot)->m_model->m_texSet == nullptr) {
        modelWork->m_active = 0;
        return;
    }

    WmCharaModelInfo* animWork = m_wm.m_charaModelData + slot;
    if (animWork->m_modelChanged == 1) {
        modelWork->m_transform.m_rotation.y = 0.2617994f;
        SetAnim(m_singleCmakeSlot);
        animWork->m_modelChanged = 0;
    }

    modelWork->m_active = 1;
    if (GetCmakeCharaHandle(this, slot)->m_charaKind != 3) {
        Mtx scaleMtx;
        Mtx rotXMtx;

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
        Math.MTXRotRadApply(rotXMtx, rotXMtx, 'y', modelWork->m_transform.m_rotation.y);
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
 * PAL Address: UNUSED
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawSingleCMakeChara(float alpha)
{
    WmWorldObjInfo* worldObjects = m_wm.m_worldObjData;
    int handleIndex = static_cast<int>(m_singleCmakeSlot) + 0x20;
    if (worldObjects[handleIndex].m_active == 0) {
        return;
    }

    WmWorldObjInfo& viewport = worldObjects[22];
    viewport.m_viewportX = -220;
    viewport.m_viewportY = 4;
    DrawInit();

    if (m_wm.m_handles[handleIndex]->m_charaKind != 3) {
        SetProjection(0x16);
        SetLight(2);
        m_wm.m_handles[handleIndex]->m_model->m_lightAlpha = alpha;
        m_wm.m_handles[handleIndex]->Draw(5);
        RestoreProjection();
    } else {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(CMAKE_TEX_WORLD46));
        MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
        GXColor col;
        col.r = 0xFF;
        col.g = 0xFF;
        col.b = 0xFF;
        col.a = static_cast<unsigned char>(255.0f * alpha);
        GXSetChanMatColor(GX_COLOR0A0, col);
        MenuPcs.DrawRect(
            0,
            33.0f, 132.0f, 128.0f, 104.0f,
            0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    DrawInit();
}
