#include "ffcc/cmake.h"
#include "ffcc/p_game.h"

extern "C" void __dl__FPv(void*);
extern "C" void freeTexture__8CMenuPcsFiiii(CMenuPcs*, int, int, int, int);
extern "C" void CmakeVillageDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" void CallWorldParam__8CMenuPcsFiii(CMenuPcs*, int, int, int);

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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSingCMake()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSingleCMakeChara()
{
	// TODO
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
