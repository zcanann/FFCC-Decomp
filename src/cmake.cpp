#include "ffcc/cmake.h"
#include "ffcc/chara.h"
#include "ffcc/p_game.h"
#include <dolphin/mtx.h>
#include <string.h>

extern "C" void __dl__FPv(void*);
extern "C" void freeTexture__8CMenuPcsFiiii(CMenuPcs*, int, int, int, int);
extern "C" void CmakeVillageDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" void CallWorldParam__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void ChgModel__8CMenuPcsFiiii(CMenuPcs*, int, int, int, int);
extern "C" void SetAnim__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void PCAnimCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" void SetMatrix__Q26CChara6CModelFPA4_f(CChara::CModel*, Mtx);
extern "C" void CalcMatrix__Q26CChara6CModelFv(CChara::CModel*);
extern "C" void CalcSkin__Q26CChara6CModelFv(CChara::CModel*);
extern "C" float FLOAT_80333254;
extern "C" float FLOAT_8033325c;
extern "C" float FLOAT_80333260;
extern "C" float FLOAT_80333264;

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
 * Address:	TODO
 * Size:	TODO
 */
void GetChara(char*, int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GetCharaType(char*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GetCharaCnt(char*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingCMake()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawDiaryBase(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeWin(float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeTitle(int, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCrystal(int, int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeNameBase(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakePageMark(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeDecision(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeBallCursor(int, int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeCharaText(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeCrest(int, int, int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeName(int, int, char*, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::AddNameChara(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawCmakeYesNo(int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeNameOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeNameCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeNameClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeNameDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeSexOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeSexCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeSexClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeSexDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeTribeOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeTribeCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeTribeClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeTribeDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeJobOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeJobCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeJobClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeJobDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeResultOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeResultCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeResultClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeResultDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeResultOpen1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeResultCtrl1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeResultClose1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeResultDraw1()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeVillageOpen()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeVillageCtrl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeVillageClose()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CmakeVillageDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingMakeChara()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::createVillageMenu()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcVillageMenu()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleCMakeChara(float)
{
	// TODO
}
