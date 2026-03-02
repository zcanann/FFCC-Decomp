#include "ffcc/cmake.h"
#include "ffcc/chara.h"
#include "ffcc/p_game.h"
#include <dolphin/mtx.h>
#include <string.h>

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
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void loadFont__8CMenuPcsFiPcii(CMenuPcs*, int, char*, int, int);
extern "C" void loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(CMenuPcs*, char**, int, int, void*, int, int, int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, void*, char*, int);
extern "C" char s_dvd__smenu_subfont_fnt_801e3020[];
extern "C" char* PTR_s_world2_802159a4[];
extern "C" int DAT_802159c8;
extern "C" char s_cmake_cpp_801e3038[];

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
    (void)x;
    (void)y;
    (void)alpha;
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
    (void)page;
    (void)x;
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
    DrawCmakeYesNo(yesNoSel, alpha);
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
    (void)x;
    (void)y;
    (void)text;
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
    DrawCmakeBallCursor(yesNoSel, 0, alpha);
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
    DrawCmakeCharaText(2, 1.0f);
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
    DrawCmakeCharaText(4, 1.0f);
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
        if (Game.game.m_gameWork.m_menuStageMode == 0) {
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
        if (Game.game.m_gameWork.m_menuStageMode == 0) {
            char path[128];
            char* language = GetLangString__5CGameFv(&Game.game);
            sprintf(path, s_dvd__smenu_subfont_fnt_801e3020, language);
            loadFont__8CMenuPcsFiPcii(this, 2, path, 4, -1);
        }

        loadTexture__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(
            this, PTR_s_world2_802159a4, 8, 1, &DAT_802159c8, 0x60, 9, 3);

        void* stage = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0xEC);
        int& villageWork = MenuS32(this, 0x830);
        villageWork = reinterpret_cast<int>(__nw__FUlPQ27CMemory6CStagePci(0x48, stage, s_cmake_cpp_801e3038, 0xCB3));
        memset(reinterpret_cast<void*>(villageWork), 0, 0x48);
        MenuS16(this, 0x86C) = 1;
    }

    short active = MenuS16(this, 0x86C);
    if (active == 0) {
        return;
    }

    if (MenuU8(this, 0x16) == 0) {
        if (Game.game.m_gameWork.m_menuStageMode == 0) {
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
