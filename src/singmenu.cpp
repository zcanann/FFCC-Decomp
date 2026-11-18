#include "ffcc/itemobj.h"
#include "ffcc/ptrarray.h"
#include "ffcc/singmenu.h"
#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/fontman.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/joybus.h"
#include "ffcc/memory.h"
#include "ffcc/mesmenu.h"
#include "ffcc/p_chara.h"
#include "ffcc/pad.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/shopmenu.h"
#include "ffcc/sound.h"

static const float s_PCYpos[4] = {-11.14f, -7.1f, -11.55f, -11.14f};
static const float s_PCScl[4] = {0.87f, 0.78f, 0.78f, 0.87f};

#if defined(VERSION_GCCJGC)
#include "ffcc/singmenu_jp.inc"
#elif defined(VERSION_GCCE01)
#include "src/singmenu_str_data_us.inc"
#else
#include "src/singmenu_str_data.inc"
#endif

#ifdef VERSION_GCCJGC
extern "C"
#else
static
#endif
const u8 s_ItemIcon[0x1F5] = {
    0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x26, 0x26, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x26, 0x26, 0x26, 0x26, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02, 0x02,
    0x26, 0x26, 0x26, 0x26, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
    0x03, 0x26, 0x26, 0x26, 0x26, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05, 0x05,
    0x05, 0x05, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x06, 0x07, 0x07, 0x07, 0x07, 0x07,
    0x07, 0x07, 0x07, 0x07, 0x07, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x08, 0x0A,
    0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A,
    0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x0B,
    0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
    0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B, 0x0B,
    0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0B, 0x0B, 0x0B, 0x0C,
    0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C, 0x0D, 0x0D, 0x0D, 0x0D, 0x0F,
    0x0F, 0x0F, 0x0F, 0x0F, 0x0E, 0x0E, 0x0E, 0x0E, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
    0x10, 0x10, 0x10, 0x10, 0x26, 0x11, 0x11, 0x11, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x26, 0x26, 0x1C, 0x12, 0x12, 0x12, 0x12, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x26, 0x26, 0x26, 0x26,
    0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x26, 0x14, 0x15, 0x16,
    0x17, 0x18, 0x19, 0x1A, 0x1B, 0x25, 0x13, 0x13, 0x13, 0x26, 0x26, 0x26, 0x26, 0x23, 0x24, 0x26,
    0x26, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22,
    0x22, 0x22, 0x22, 0x22, 0x22,
};
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <math.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

typedef signed short s16;
typedef unsigned char u8;

STATIC_ASSERT(offsetof(CCaravanWork, m_tribeId) == 0x3E0);
STATIC_ASSERT(offsetof(CCaravanWork, m_genderFlag) == 0x3E2);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuStageActive) == 0x859);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuInitialized) == 0x85A);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuTextureLoadIndex) == 0x85C);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuTextureLoadState) == 0x860);

struct SingMenuStaticMessageInfo
{
    int lineCount;
    s16 textIds[8];
};

struct SingMenuSoloNameTable
{
    char* entries[9];
};

#if defined(VERSION_GCCJGC)
#define SINGMENU_LINE(line, usLine, jpLine) (jpLine)
#elif defined(VERSION_GCCE01)
#define SINGMENU_LINE(line, usLine, jpLine) (usLine)
#else
#define SINGMENU_LINE(line, usLine, jpLine) (line)
#endif

#ifdef VERSION_GCCJGC
#define SINGMENU_TEX_ID(id) ((id) - 1)
#else
#define SINGMENU_TEX_ID(id) (id)
#endif

extern "C" {
int s_DynamicMess[5];
}
static char s_DynamicMessStr[0x400];
SingMenuStaticMessageInfo s_SingMess[] = {
    {4, {14, 15, 16, 3, 0, 0, 0, 0}},
    {2, {15, 3, 0, 0, 0, 0, 0, 0}},
    {4, {30, 31, 32, 3, 0, 0, 0, 0}},
};

extern "C" SingMenuSoloNameTable PTR_s_solo2 = {
    {"solo2", 0, 0, 0, 0, 0, 0, 0, 0},
};

CMenuPcs::CTmp s_singleMenuTextureTable[] = {
    {4, "solo1"},
    {4, "solo4"},
    {4, "solo5"},
    {4, "solo8"},
    {4, "solo9"},
    {4, "solo30"},
    {4, "solo42"},
    {4, "solo47"},
    {4, "solo48"},
    {4, "solo49"},
    {4, "solo50"},
    {4, "solo51"},
    {4, "solo63"},
};

extern "C" SingMenuSoloNameTable PTR_s_solo1 = {
    {"solo1", "sololetter", 0, 0, 0, 0, 0, 0, 0},
};

extern "C" CMenuPcs::CTmp s_singleMenuModelTextureTable[] = {
    {5, "solo2"}, {5, "solo3"}, {5, "solo6"}, {5, "solo7"}, {5, "solo10"},
    {5, "solo11"}, {5, "solo12"}, {5, "solo13"}, {5, "solo14"}, {5, "solo15"},
    {5, "solo16"}, {5, "solo17"}, {5, "solo18"}, {5, "solo19"}, {5, "solo20"},
    {5, "solo21"}, {5, "solo22"}, {5, "solo24"}, {5, "solo25"}, {5, "solo26"},
    {5, "solo27"}, {5, "solo28"}, {5, "solo29"}, {5, "solo31"}, {5, "solo32"},
    {5, "solo33"}, {5, "solo34"}, {5, "solo35"}, {5, "solo36"}, {5, "solo37"},
    {5, "solo38"}, {5, "solo39"}, {5, "solo40"}, {5, "solo41"}, {5, "solo43"},
    {5, "solo44"}, {5, "solo45"}, {5, "solo46"}, {5, "solo52"}, {5, "solo53"},
    {5, "solo54"}, {5, "solo55"}, {5, "solo56"}, {5, "solo57"}, {5, "solo58"},
    {5, "solo59"}, {5, "solo60"}, {5, "solo61"}, {5, "solo62"}, {5, "solo64"},
    {6, "solo23"},
};

CFile::CHandle* gSingMenuAsyncFileHandle;
int gSingMenuAsyncLoadCompleted;
int gSingMenuHasScriptFoodBase;
int gSingMenuForcedSelection;
static float s_WinMessScl = 0.8999999761581421f;

#ifndef VERSION_GCCJGC
static inline const char* GetSingWinMessage(int staticText, const char* dynamicText, int useDynamic)
{
    if (useDynamic != 0) {
        return dynamicText;
    }

    int languageId = Game.m_gameWork.m_languageId;
    switch (languageId) {
    case 2:
        return (char*)s_MenuStr_ge[staticText];
    case 3:
        return (char*)s_MenuStr_it[staticText];
    case 4:
        return (char*)s_MenuStr_fr[staticText];
    case 5:
        return (char*)s_MenuStr_sp[staticText];
    case 1:
    default:
        return (char*)s_MenuStr_us[staticText];
    }
}
#endif

/*
 * --INFO--
 * PAL Address: 0x8014a7cc
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createSingleMenu()
{
    m_singleMenuPhase = 0;
    gSingMenuAsyncLoadCompleted = 0;
    if (Game.m_gameWork.m_menuStageMode == 0) {
        if (m_singleMenuStageActive != 0) {
            m_stageF0 = 0;

            CFont* font = m_fonts[4];
            if (font != 0) {
                font->Release();
                m_fonts[4] = 0;
            }

            m_singleMenuStageActive = 0;
            m_singleMenuInitialized = 0;
        }
    } else {
        if (m_singleMenuStageActive == 0) {
            m_stageF0 = CharaPcs.GetAnimStage();
            m_singleMenuStageActive = 1;
        }

        FFCC_ASSERT(m_fonts[4] == 0);
#ifdef VERSION_GCCJGC
        char* path = "dvd/menu/subfont.fnt";
#else
        char path[128];
        sprintf(path, "dvd/%smenu/subfont.fnt", Game.GetLangString());
#endif
        loadFont(1, path, 4, -1);

        m_singleMenuInitialized = 0;
        gSingMenuForcedSelection = -1;
        gSingMenuAsyncFileHandle = 0;

        if (Game.m_gameWork.m_menuStageMode != 0) {
            loadTexture(PTR_s_solo2.entries, 4, 1, s_singleMenuTextureTable, SINGMENU_TEX_ID(0x20), 0xD, 1);
            m_wm.m_worldObjData = 0;
            m_singleFadeState = 0;
            m_singMenuState = 0;
            m_menuWindowInfo = 0;
            m_shopMenu = 0;
        } else {
            FFCC_ASSERT(0);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8014A67C
 * PAL Size: 336b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroySingleMenu()
{
    if (gSingMenuAsyncFileHandle != 0) {
        File.Close(gSingMenuAsyncFileHandle);
        gSingMenuAsyncFileHandle = 0;
    }

    CFont* font = m_fonts[4];
    if (font != 0) {
        font->Release();
        m_fonts[4] = 0;
    }

    freeTexture(4, 1, SINGMENU_TEX_ID(0x20), 0xD);
    freeTexture(5, 2, SINGMENU_TEX_ID(0x2D), 0x33);

    m_stageF0 = 0;
    m_singleMenuInitialized = 0;
    m_singleMenuStageActive = 0;
    gSingMenuForcedSelection = -1;

    void* ptr = m_wm.m_worldObjData;
    if (ptr != 0) {
        delete[] static_cast<WmWorldObjInfo*>(ptr);
        m_wm.m_worldObjData = 0;
    }

    ptr = m_singleFadeState;
    if (ptr != 0) {
        delete static_cast<SingleFadeState*>(ptr);
        m_singleFadeState = 0;
    }

    ptr = m_singMenuState;
    if (ptr != 0) {
        delete static_cast<u8*>(ptr);
        m_singMenuState = 0;
    }

    ptr = m_menuWindowInfo;
    if (ptr != 0) {
        delete static_cast<MenuWindowInfo*>(ptr);
        m_menuWindowInfo = 0;
    }

    GXSetCopyClear(Graphic.m_defaultCopyClearColor, 0xFFFFFF);
}

/*
 * --INFO--
 * PAL Address: 0x8014a214
 * PAL Size: 1128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingMenuInit()
{
    Graphic._WaitDrawDone("singmenu.cpp", SINGMENU_LINE(0x5C2, 0x5BD, 0x563));
    Graphic.DestroyTempBuffer();

    m_stageF4 = Graphic.GetTempStage();
    memset(&m_singleMenuTextureLoadIndex, 0, 8);
    m_wm.m_handles[0] = 0;

    CCharaPcs::CHandle* handle = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, "singmenu.cpp", SINGMENU_LINE(0x5CD, 0x5C8, 0x56E)) CCharaPcs::CHandle;
    m_wm.m_handles[0] = handle;

    CCharaPcs::CHandle** handlePtr = &m_wm.m_handles[0];
    (*handlePtr)->Add();
    CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
    int modelNo = GetModelNo(
        static_cast<int>(caravanWork->m_tribeId),
        static_cast<int>(caravanWork->m_appearanceVariant),
        static_cast<int>(caravanWork->m_genderFlag));
    (*handlePtr)->LoadModel(0, static_cast<unsigned long>(modelNo), 0, 0, -1, 0, 0);
    (*handlePtr)->m_flags |= 0x300141;
    (*handlePtr)->LoadAnim("stand", 0, 1, 0, (static_cast<unsigned int>((*handlePtr)->m_charaNo) / 100) * 100, -1, 0);
    (*handlePtr)->SetAnim(0, -1, -1, -1, 0);

    m_wm.m_worldObjData = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, "singmenu.cpp", SINGMENU_LINE(0x5DD, 0x5D8, 0x57E)) WmWorldObjInfo[1];

    for (int i = 0; i < 1; i++) {
        m_wm.m_worldObjData[i].m_transform.Identity();
        m_wm.m_worldObjData[i].m_active = 0;
        m_wm.m_worldObjData[i].m_frameCounter = 0;
        m_wm.m_worldObjData[i].m_viewportX = 0;
        m_wm.m_worldObjData[i].m_viewportY = 0;
        m_wm.m_worldObjData[i].m_viewportWidth = 0x280;
        m_wm.m_worldObjData[i].m_viewportHeight = 0x1C0;
        m_wm.m_worldObjData[i].m_cameraPosition.x = 0.0f;
        m_wm.m_worldObjData[i].m_cameraPosition.y = 0.0f;
        m_wm.m_worldObjData[i].m_cameraPosition.z = 100.0f;
        m_wm.m_worldObjData[i].m_scissorX = 0;
        m_wm.m_worldObjData[i].m_scissorY = 0;
        m_wm.m_worldObjData[i].m_scissorWidth = 0x280;
        m_wm.m_worldObjData[i].m_scissorHeight = 0x1C0;
    }
    float left = 440.0f;
    float top = 88.0f;
    float width = 96.0f;
    left += 28.0f;
    double half = 0.5;
    float centerX = 4.0 + (width * half + left);
    float centerY = top;
    centerY += top * half;
    centerX -= 320.0;
    centerY -= 224.0;
    m_wm.m_worldObjData->m_viewportX = static_cast<s16>(centerX - 4.0);
    m_wm.m_worldObjData->m_viewportY = static_cast<s16>(centerY);
    m_wm.m_worldObjData->m_scissorX = static_cast<int>(12.0f + left);
    m_wm.m_worldObjData->m_scissorY = static_cast<int>(top - 8.0f);
    m_wm.m_worldObjData->m_scissorWidth = 0x48;
    m_wm.m_worldObjData->m_scissorHeight = 0x58;

    m_singleFadeState = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, "singmenu.cpp", SINGMENU_LINE(0x605, 0x600, 0x5A6)) SingleFadeState;
    memset(m_singleFadeState, 0, sizeof(SingleFadeState));

    m_singMenuState = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, "singmenu.cpp", SINGMENU_LINE(0x609, 0x604, 0x5AA)) SingMenuState;
    memset(m_singMenuState, 0, sizeof(SingMenuState));

    m_menuWindowInfo = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, "singmenu.cpp", SINGMENU_LINE(0x60D, 0x608, 0x5AE)) MenuWindowInfo;
    memset(m_menuWindowInfo, 0, sizeof(MenuWindowInfo));

    m_singleMenuPhase = 0;
    if (gSingMenuForcedSelection >= 0) {
        m_singleMenuMode = 8;
        gSingMenuForcedSelection = -1;
    }
    SetSingWinScl(0.9f);
    SingLifeInit(-1);
    m_singleMenuCtrlResetFlag = 1;
    m_singleMenuInitialized = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingMenuEnd()
{
    Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 0;
    Graphic._WaitDrawDone("singmenu.cpp", SINGMENU_LINE(0x62B, 0x626, 0x5CC));
    m_singleMenuInitialized = 0;

    if (gSingMenuAsyncFileHandle != 0) {
        File.Close(gSingMenuAsyncFileHandle);
        gSingMenuAsyncFileHandle = 0;
    }

    freeTexture(5, 2, SINGMENU_TEX_ID(0x2D), 0x33);

    if (m_wm.m_handles[0] != 0) {
        delete m_wm.m_handles[0];
        m_wm.m_handles[0] = 0;
    }

    if (m_wm.m_worldObjData != 0) {
        delete[] m_wm.m_worldObjData;
        m_wm.m_worldObjData = 0;
    }

    if (m_singMenuState != 0) {
        delete[] reinterpret_cast<u8*>(m_singMenuState);
        m_singMenuState = 0;
    }

    if (m_singleFadeState != 0) {
        delete m_singleFadeState;
        m_singleFadeState = 0;
    }

    if (m_menuWindowInfo != 0) {
        delete m_menuWindowInfo;
        m_menuWindowInfo = 0;
    }

    m_stageF4->heapWalker(-1, 0, 0xFFFFFFFF);
    Graphic.CreateTempBuffer();
    m_stageF4 = 0;
    m_singleMenuCtrlResetFlag = 0;
    Joybus.SetCtrlMode(0, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80149e5c
 * PAL Size: 952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calcSingleMenu()
{
    gSingMenuHasScriptFoodBase = static_cast<int>(Game.m_scriptFoodBase[0]->m_shopRequestState != 0);
    if (Game.m_gameWork.m_menuStageMode == 0) {
        if (m_singleMenuStageActive == 0) {
            return;
        }

        m_stageF0 = 0;
        m_singleMenuStageActive = 0;
        m_singleMenuInitialized = 0;
        return;
    }

    if (m_singleMenuStageActive == 0) {
        createSingleMenu();
    }
    if (Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag == 0) {
        return;
    }
    if (m_singleMenuInitialized == 0) {
        SingMenuInit();
    }

    if (Game.m_scriptFoodBase[0]->m_shopRequestState == 0) {
        gSingMenuAsyncLoadCompleted = loadTextureAsync(PTR_s_solo1.entries, 5, 2, s_singleMenuModelTextureTable, SINGMENU_TEX_ID(45), 0x33, 0);
    }
    if (m_singleFadeState->done != 0) {
        m_singleMenuPhase = m_singleMenuPhase + 1;
        m_singleFadeState->done = 0;
        m_singleFadeState->active = 0;
        m_singMenuState->initialized = 0;
        m_singMenuState->closeRequested = 0;
        m_singMenuState->stepState = 0;
        m_singMenuState->frame = 0;
    }

    char menuKind = Game.m_scriptFoodBase[0]->m_shopRequestState;
    if (menuKind == 1) {
        if (m_shopMenu == 0) {
            CreateShopMenu();
        } else {
            m_shopMenu->Calc();
        }
    } else if (menuKind == 2) {
        if (m_shopMenu == 0) {
            CreateSmithMenu();
        } else {
            m_shopMenu->Calc();
        }
    }

    if (gSingMenuHasScriptFoodBase == 0) {
        switch (m_singleMenuPhase) {
            case 0:
                SingleCalcFadeIn();
                break;
            case 1:
                SingleCalcCtrl();
                break;
            case 2:
                SingleCalcFadeOut();
                break;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80149534
 * PAL Size: 2344b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawSingleMenu()
{
    if ((Game.m_gameWork.m_menuStageMode != 0) &&
        (Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != 0)) {
        DrawInit();
        DrawFilter(0, 0, 0, 0xFF);
        Util.ClearZBufferRect(0.0f, 0.0f, 640.0f, 448.0f);
        DrawInit();

        char menuType = Game.m_scriptFoodBase[0]->m_shopRequestState;
        if (menuType == 1) {
            if (m_shopMenu != 0) {
                m_shopMenu->Draw();
            }
        } else if ((menuType == 2) && (m_shopMenu != 0)) {
            m_shopMenu->Draw();
        }

        if ((gSingMenuHasScriptFoodBase != 0) && (m_singleFadeState->done != 0)) {
            SingMenuEnd();
        }

        if (gSingMenuHasScriptFoodBase != 0) {
            return;
        }

        switch (m_singleMenuPhase) {
        case 0:
            SingleDrawFadeIn();
            break;
        case 1:
            SingleDrawCtrl();
            break;
        case 2:
            SingleDrawFadeOut();
            if (m_singleFadeState->done != 0) {
                SingMenuEnd();
            }
            break;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CMenuPcs::loadTextureAsync(char** names, int setStart, int setCount, CMenuPcs::CTmp* tmp, int texStart, int texCount, int)
{
    int loadIndex = m_singleMenuTextureLoadIndex;
    if (loadIndex >= setCount) {
        return 1;
    }

    if (m_singleMenuTextureLoadState == 0) {
        char path[256];
#ifdef VERSION_GCCJGC
        sprintf(path, "dvd/menu/%s.tex", names[loadIndex]);
#else
        sprintf(path, "dvd/%smenu/%s.tex", Game.GetLangString(), names[loadIndex]);
#endif
        gSingMenuAsyncFileHandle = File.Open(path, 0, CFile::PRI_LOW);
        File.ReadASync(gSingMenuAsyncFileHandle);
        m_singleMenuTextureLoadState = m_singleMenuTextureLoadState + 1;
    } else if (m_singleMenuTextureLoadState == 1) {
        if (!File.IsCompleted(gSingMenuAsyncFileHandle)) {
            return 0;
        }

        m_textureSets[loadIndex + setStart] = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, "singmenu.cpp", SINGMENU_LINE(0x748, 0x743, 0x6E8)) CTextureSet;

        void* buffer = File.m_readBuffer;
        m_textureSets[loadIndex + setStart]->Create(buffer, Game.m_gameWork.m_menuStageMode != 0 ? m_stageF4 : m_menuStage, 0, 0, 0, 0);
        File.Close(gSingMenuAsyncFileHandle);
        gSingMenuAsyncFileHandle = 0;
        m_singleMenuTextureLoadState = 0;
        m_singleMenuTextureLoadIndex = m_singleMenuTextureLoadIndex + 1;
    }

    if (m_singleMenuTextureLoadIndex < setCount) {
        return 0;
    }

    for (int i = 0; i < texCount; i++) {
        int texIdx = m_textureSets[tmp[i].m_textureSetIndex]->Find(tmp[i].m_textureName);
        CTexture* tex = m_textureSets[tmp[i].m_textureSetIndex]->GetTexture(static_cast<unsigned long>(texIdx));
        tex->AddRef();
        m_textures[i + texStart] = tex;
    }
    return 1;
}


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::SingCalcChara(float frameStep)
{
    if (m_wm.m_handles[0]->m_model->GetNowFrame() < m_wm.m_handles[0]->m_model->GetEndFrame()) {
        m_wm.m_handles[0]->m_model->AddFrame(frameStep);
    } else {
        m_wm.m_handles[0]->m_model->SetFrame(0.0f);
    }

    unsigned short modelScaleIndex = Game.m_scriptFoodBase[0]->m_tribeId;
    float modelScale = s_PCScl[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[0][3] = 0.0f;
    scaleMtx[1][3] = s_PCYpos[modelScaleIndex];
    scaleMtx[2][3] = 0.0f;

    m_wm.m_handles[0]->m_model->m_flags10CBits.m_flag10C_80 = 1;
    m_wm.m_handles[0]->m_model->SetMatrix(scaleMtx);
    m_wm.m_handles[0]->m_model->CalcMatrix();
    m_wm.m_handles[0]->m_model->CalcSkin();
}

/*
 * --INFO--
 * PAL Address: 0x8014935c
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingleBase(float alpha)
{
    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x20)));
    MenuPcs.DrawRect(0, 0.0f, 0.0f, 640.0f, 64.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 0.0f, 384.0f, 640.0f, 64.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x28)));
    int y;
    int sliceHeight = 32;
    y = 64;
    while (y < 384) {
        if ((384 - y) < sliceHeight) {
            sliceHeight = 384 - y;
        }

        MenuPcs.DrawRect(0, 0.0f, static_cast<float>(y), 640.0f, static_cast<float>(sliceHeight), 0.0f,
                                         0.0f, 1.0f, 1.0f, 0.0f);
        y += sliceHeight;
    }
}

enum {
#ifdef VERSION_GCCJGC
    kStatTexHeader = 0x25,
    kStatTexSlice = 0x28,
    kStatTexPortrait = 0x21,
    kStatTexEmblem = 0x29,
#else
    kStatTexHeader = 0x26,
    kStatTexSlice = 0x29,
    kStatTexPortrait = 0x22,
    kStatTexEmblem = 0x2A,
#endif
};

/*
 * --INFO--
 * PAL Address: 0x80148b98
 * PAL Size: 1988b
 * EN Address: 0x80147D08
 * EN Size: 1864b
 * JP Address: 0x801442BC
 * JP Size: 1712b
 */
void CMenuPcs::DrawSingleStat(float alpha)
{
    CFont* font;
    float y;
    int i;
    char* label;
#ifdef VERSION_GCCP01
    int languageId = Game.m_gameWork.m_languageId;
#endif

    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    float a255 = 255.0f * alpha;
    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(a255);
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kStatTexHeader));
    float x = 440.0f;
    MenuPcs.DrawRect(0, x, 0.0f, 152.0f, 40.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 440.0f, 408.0f, 152.0f, 40.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kStatTexSlice));
    float sliceY;
    float sliceHeight = 8.0f;
    for (sliceY = 40.0f; sliceY < 408.0f; sliceY += sliceHeight) {
        if ((408.0f - sliceY) < sliceHeight) {
            sliceHeight = 408.0f - sliceY;
        }
        MenuPcs.DrawRect(0, 440.0f, sliceY, 640.0f, sliceHeight,
                                         0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0 * (0.5 * alpha));
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kStatTexPortrait));

    int charaNo = Game.m_scriptFoodBase[0]->m_tribeId;
    float iconStep = 216.0f;
    int texU = static_cast<int>(static_cast<float>(charaNo & 1) * iconStep);
    int texV = static_cast<int>(static_cast<float>(charaNo / 2) * iconStep);
    x -= 32.0f;
    MenuPcs.DrawRect(0, x, 176.0f, iconStep, iconStep,
                                     static_cast<float>(texU), static_cast<float>(texV), 1.0f, 1.0f, 0.0f);

    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(a255);
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kStatTexEmblem));
    x = 440.0f;
    x += 28.0f;
    MenuPcs.DrawRect(0, x, 88.0f, 96.0f, 88.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    DrawInit();
    SetProjection(0);
    SetLight(1);
    m_wm.m_handles[0]->m_model->m_lightAlpha = alpha;
    m_wm.m_handles[0]->Draw(5);
    RestoreProjection();

    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(a255);
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(kStatTexEmblem));
    x = 440.0f;
    x += 28.0f;
    MenuPcs.DrawRect(0, x, 128.0f, 96.0f, 48.0f,
                                     0.0f, 88.0f, 1.0f, 1.0f, 0.0f);

    DrawInit();
    font = GetFont22();
    font->SetMargin(1.0f);
    font->SetShadow(1);
    font->SetScale(0.8999999761581421f);

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(a255)).color);
    font->DrawInit();

    char* charaName = reinterpret_cast<char*>(Game.m_scriptFoodBase[0]->m_name);
    float titleWidth = static_cast<float>(font->GetWidth(charaName));
    DrawShadowFont(font, charaName, 440.0f + static_cast<float>((152.0f - titleWidth) / 2.0), 56.0f, 0x17, 0x12);

    font->SetTlut(0x15);
    float statY0 = 184.0f;
    float statYStep = 36.0f;
    float statPosX0 = 592.0f;
    y = statY0;
    for (i = 0; i < 4; i++) {
        font->SetPosX(440.0f);
#ifdef VERSION_GCCJGC
        font->SetPosY(y);
#else
        font->SetPosY(y - 4.0f);
#endif

#ifdef VERSION_GCCJGC
        label = GetMenuStr(i + 5);
#else
        switch (Game.m_gameWork.m_languageId) {
            case 2:
                label = (char*)s_MenuStr_ge[i + 5];
                break;
            case 3:
                label = (char*)s_MenuStr_it[i + 5];
                break;
            case 4:
                label = (char*)s_MenuStr_fr[i + 5];
                break;
            case 5:
                label = (char*)s_MenuStr_sp[i + 5];
                break;
            case 1:
            default:
                label = (char*)s_MenuStr_us[i + 5];
                break;
        }
#endif

#ifdef VERSION_GCCP01
        if ((languageId == 2) && (i == 3)) {
            font->SetScaleX(0.7199999690055847f);
            font->SetScaleY(0.8999999761581421f);
        } else {
            font->SetScaleX(0.8999999761581421f);
        }
#endif
        font->Draw(label);

        font->SetFixed(1);
#ifdef VERSION_GCCP01
        if (languageId == 2) {
            font->SetMargin(-5.0f);
            font->SetScaleX(0.7199999690055847f);
            font->SetScaleY(0.8999999761581421f);
        } else {
            font->SetMargin(-3.0f);
            font->SetScale(0.8999999761581421f);
        }
#else
        font->SetMargin(-3.0f);
#endif

        int stat;
        if (i == 0) {
            stat = Game.m_scriptFoodBase[0]->m_strength;
        } else if (i == 1) {
            stat = Game.m_scriptFoodBase[0]->m_defense;
        } else if (i == 2) {
            stat = Game.m_scriptFoodBase[0]->m_magic;
        } else {
            stat = Game.m_scriptFoodBase[0]->m_progressValue;
        }

        char valueText[36];
        sprintf(valueText, "%d", stat);
        float valueW = static_cast<float>(font->GetWidth(valueText));
        font->SetPosX(statPosX0 - valueW);
        font->Draw(valueText);

        font->SetFixed(0);
        font->SetMargin(1.0f);
        y += statYStep;
    }

    font->SetFixed(0);
    font->SetMargin(1.0f);
    DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x801488f0
 * PAL Size: 680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingleHelpWim(float alpha)
{
    int posX;
    int posY;
    int width;
    int height;

    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x23)));
    posX = 32;
    posY = 312;
    width = 32;
    height = 32;
    MenuPcs.DrawRect(0, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    posX = 576;
    MenuPcs.DrawRect(8, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    posX = 32;
    posY = 384;
    MenuPcs.DrawRect(4, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    posX = 576;
    MenuPcs.DrawRect(0xC, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x27)));
    posX = 64;
    posY = 312;
    width = 512;
    MenuPcs.DrawRect(0, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    posY = 384;
    MenuPcs.DrawRect(4, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x24)));
    posX = 32;
    posY = 344;
    width = 32;
    height = 40;
    MenuPcs.DrawRect(0, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    posX = 576;
    MenuPcs.DrawRect(8, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x2B)));
    posX = 64;
    width = 512;
    MenuPcs.DrawRect(8, posX, posY, width, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleCrescent(float scaleX, float alpha)
{
    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x21)));
    MenuPcs.DrawRect(0,
                                    -(176.0f * scaleX - 208.0f), 24.0f,
                                    176.0f, 288.0f,
                                    0.0f, 0.0f,
                                    scaleX, 1.0f, 0.0f);
    MenuPcs.DrawRect(8,
                                    224.0f, 24.0f,
                                    176.0f, 288.0f,
                                    0.0f, 0.0f,
                                    scaleX, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x801484e4
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingleCalcFadeIn()
{
    if (m_singleFadeState->active == 0) {
        Sound.PlaySe(0xE, 0x40, 0x7F, 0);
        memset(m_singleFadeState, 0, sizeof(SingleFadeState));

        SingleFadeEntry* e;
        int idx = 0;
        e = &m_singleFadeState->entries[idx++];
        e->startFrame = 0;
        e->duration = 10;
        e = &m_singleFadeState->entries[idx++];
        e->startFrame = (m_singleMenuMode == 8) ? 0 : 10;
        e->duration = 10;
        e = &m_singleFadeState->entries[idx++];
        e->startFrame = (m_singleMenuMode == 8) ? 0 : 10;
        e->duration = 10;
        e = &m_singleFadeState->entries[idx++];
        e->startFrame = (m_singleMenuMode == 8) ? 0 : 10;
        e->duration = 10;

        m_singleFadeState->count = static_cast<s16>(idx);
        m_singleFadeState->done = 0;
        m_singleFadeState->active = 1;
    }

    int completed = 0;
    m_singMenuState->frame = m_singMenuState->frame + 1;

    int count = static_cast<int>(m_singleFadeState->count);
    SingleFadeEntry* entry = m_singleFadeState->entries;
    int frame = static_cast<int>(m_singMenuState->frame);
    for (int i = 0; i < count; i++) {
        if (entry->startFrame <= frame) {
            if (entry->startFrame + entry->duration <= frame) {
                completed = completed + 1;
                entry->alpha = 1.0f;
            } else {
                entry->elapsed = entry->elapsed + 1;
                entry->alpha = static_cast<float>((1.0 / (double)entry->duration) *
                                                  (double)entry->elapsed);
            }
        }
        entry = entry + 1;
    }

    SingCalcChara(1.0f);

    if (m_singleFadeState->count == completed) {
        m_singleFadeState->done = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawFadeIn()
{
    SingleFadeEntry* entry;
    int i;
    int count;

    count = m_singleFadeState->count;
    entry = m_singleFadeState->entries;
    for (i = 0; i < count; i++, entry++) {
        if ((i == 0) || (m_singleMenuMode != 8)) {
            if (i == 0) {
                DrawSingleBase(entry->alpha);
            } else if (i == 1) {
                DrawSingleCrescent(entry->alpha, 1.0f);
            } else if (i == 2) {
                DrawSingleStat(entry->alpha);
            } else {
                DrawSingleHelpWim(entry->alpha);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80148220
 * PAL Size: 708b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingleCalcFadeOut()
{
    if (m_singleFadeState->active == 0) {
        Sound.PlaySe(0xF, 0x40, 0x7F, 0);
        memset(m_singleFadeState, 0, sizeof(SingleFadeState));

        SingleFadeEntry* e;
        int idx = 0;
        e = &m_singleFadeState->entries[idx++];
        e->startFrame = (m_singleMenuMode == 8) ? 0 : 10;
        e->duration = 10;
        e = &m_singleFadeState->entries[idx++];
        e->startFrame = 0;
        e->duration = 10;
        e = &m_singleFadeState->entries[idx++];
        e->startFrame = 0;
        e->duration = 10;
        e = &m_singleFadeState->entries[idx++];
        e->startFrame = 0;
        e->duration = 10;

        m_singleFadeState->count = static_cast<s16>(idx);
        m_singleFadeState->done = 0;
        m_singleFadeState->active = 1;
    }

    int completed = 0;
    ++m_singMenuState->frame;

    int count = static_cast<int>(m_singleFadeState->count);
    SingleFadeEntry* entry = m_singleFadeState->entries;
    int frame = static_cast<int>(m_singMenuState->frame);
    for (int i = 0; i < count; i++) {
        if (entry->startFrame > frame) {
            entry->alpha = 1.0f;
        } else if (entry->startFrame + entry->duration <= frame) {
            completed = completed + 1;
            entry->alpha = 0.0f;
        } else {
            entry->elapsed = entry->elapsed + 1;
            entry->alpha =
                static_cast<float>(-((1.0 / static_cast<double>(entry->duration)) *
                                      static_cast<double>(entry->elapsed) - 1.0));
        }
        entry = entry + 1;
    }

    SingCalcChara(1.0f);

    if (m_singleFadeState->count == completed) {
        m_singleFadeState->done = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawFadeOut()
{
    SingleDrawFadeIn();
}

/*
 * --INFO--
 * PAL Address: 0x80147d50
 * PAL Size: 1232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingleCalcCtrl()
{
    if (gSingMenuAsyncLoadCompleted == 0) {
        return;
    }

    if ((m_singleMenuCtrlResetFlag != 0) && (m_singMenuState->stepState != 0)) {
        m_singleMenuCtrlResetFlag = 0;
    }

    int result = 0;
    SingCalcChara(1.0f);

    switch (m_singleMenuMode) {
    case 0: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = CmdOpen();
        } else if (proc == 1) {
            result = CmdCtrl();
        } else {
            result = CmdClose();
        }
        break;
    }
    case 1: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = ItemOpen();
        } else if (proc == 1) {
            result = ItemCtrl();
        } else {
            result = ItemClose();
        }
        if ((m_singleLifeTimer >= 0) && (++m_singleLifeTimer, m_singleLifeTimer >= 0x32)) {
            m_singleLifeTimer = -1;
        }
        break;
    }
    case 2: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = EquipOpen();
        } else if (proc == 1) {
            result = EquipCtrl();
        } else {
            result = EquipClose();
        }
        break;
    }
    case 3: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = ArtiOpen();
        } else if (proc == 1) {
            result = ArtiCtrl();
        } else {
            result = ArtiClose();
        }
        break;
    }
    case 4: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = TmpArtiOpen();
        } else if (proc == 1) {
            result = TmpArtiCtrl();
        } else {
            result = TmpArtiClose();
        }
        break;
    }
    case 5: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = MoneyOpen();
        } else if (proc == 1) {
            result = MoneyCtrl();
        } else {
            result = MoneyClose();
        }
        break;
    }
    case 6: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = FavoOpen();
        } else if (proc == 1) {
            result = FavoCtrl();
        } else {
            result = FavoClose();
        }
        break;
    }
    case 7: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = CompaOpen();
        } else if (proc == 1) {
            result = CompaCtrl();
        } else {
            result = CompaClose();
        }
        break;
    }
    case 8: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = LetterOpen();
        } else if (proc == 1) {
            result = LetterCtrl();
        } else {
            result = LetterClose();
        }
        break;
    }
    case 9: {
        s16 proc = m_singMenuState->stepState;
        if (proc == 0) {
            result = MLstOpen();
        } else if (proc == 1) {
            result = MLstCtrl();
        } else {
            result = MLstClose();
        }
        break;
    }
    }

    MenuPcs.m_battleMesMenus[0]->CalcHeart();
    m_singMenuState->result = result;

    if ((Pad.GetButtonDown(0) & 0x800) != 0) {
        m_singleFadeState->done = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x801478cc
 * PAL Size: 1156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingleDrawCtrl()
{
    DrawSingleBase(1.0f);

    if (m_singleMenuMode != 8) {
        DrawSingleCrescent(1.0f, 1.0f);
        DrawSingleStat(1.0f);
        DrawSingleHelpWim(1.0f);
    }

    if (gSingMenuAsyncLoadCompleted == 0) {
        return;
    }

    switch (m_singleMenuMode) {
    case 0:
        CmdDraw();
        break;
    case 1:
        ItemDraw();
        break;
    case 2:
        EquipDraw();
        break;
    case 3:
        ArtiDraw();
        break;
    case 4:
        TmpArtiDraw();
        break;
    case 5:
        MoneyDraw();
        break;
    case 6:
        FavoDraw();
        break;
    case 7:
        CompaDraw();
        break;
    case 8:
        LetterDraw();
        break;
    case 9:
        MLstDraw();
        break;
    }

    SingMenuState* state = m_singMenuState;
    if (state->result == 0) {
        return;
    }

    if (state->stepState < 2) {
        ++state->stepState;
        m_singMenuState->frame = 0;
        m_singMenuState->initialized = 0;
        m_singMenuState->result = 0;
        return;
    }

    s16 previousMode = 0;
    if (state->closeRequested != 0) {
        s16 mode = m_singleMenuMode;
        if (mode == 9) {
            m_singleFadeState->done = 1;
        } else {
            m_singleMenuMode = 9;
            previousMode = mode;
        }
    } else {
        if (m_singleMenuMode == 9) {
            m_singleMenuMode = state->selectedIndex;
        } else if ((m_singleMenuMode == 8) && (gSingMenuForcedSelection >= 0)) {
            m_singleMenuMode = static_cast<s16>(gSingMenuForcedSelection);
        } else if ((m_singleMenuMode != 8) && (gSingMenuForcedSelection >= 0)) {
            m_singleMenuMode = 8;
        } else {
            if (state->cursorMove > 0) {
                ++m_singleMenuMode;
                if (m_singleMenuMode > 8) {
                    m_singleMenuMode = 0;
                }
            } else {
                --m_singleMenuMode;
                if (m_singleMenuMode < 0) {
                    m_singleMenuMode = 8;
                }
            }
        }
    }

    memset(m_singMenuState, 0, sizeof(SingMenuState));
    m_singMenuState->selectedIndex = previousMode;
    s_WinMessScl = 0.8999999761581421f;
}

/*
 * --INFO--
 * PAL Address: 0x80147728
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingleIcon(int iconNo, int posX, int posY, float alpha, int rawIcon, float uvScale)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x25)));
    int icon;
    if (rawIcon != 0) {
        icon = iconNo;
    } else {
        icon = static_cast<int>(s_ItemIcon[iconNo]);
    }

    int row = icon / 8;
    int col = icon % 8;

    MenuPcs.DrawRect(0, static_cast<float>(posX), static_cast<float>(posY), 32.0f, 32.0f,
        static_cast<float>(col * 0x20), static_cast<float>(row * 0x20), uvScale, uvScale, 0.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawShadowFont(CFont* font, char* text, float x, float y, int tlut, int shadowTlut)
{
    font->SetTlut(shadowTlut);
    font->SetPosX(1.0f + x);
#ifdef VERSION_GCCJGC
    font->SetPosY(1.0f + y);
#else
    font->SetPosY((1.0f + y) - 4.0f);
#endif
    font->Draw(text);

    font->SetTlut(tlut);
    font->SetPosX(x);
#ifdef VERSION_GCCJGC
    font->SetPosY(y);
#else
    font->SetPosY(y - 4.0f);
#endif
    font->Draw(text);
}

/*
 * --INFO--
 * PAL Address: 0x801475BC
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawNoShadowFont(CFont* font, char* text, float x, float y, int tlut, int)
{
    font->SetTlut(tlut);
    font->SetPosX(x);
#ifdef VERSION_GCCJGC
    font->SetPosY(y);
#else
    font->SetPosY(y - 4.0f);
#endif
    font->Draw(text);
}

/*
 * --INFO--
 * PAL Address: 0x801474F0
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetItemType(int itemId, int useRawItemId)
{
    const CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
    itemId = useRawItemId != 0 ? itemId : static_cast<int>(caravanWork->m_inventoryItems[itemId]);
    int type;

    if (itemId <= 0) {
        type = 0;
    } else if (itemId <= 0x9E) {
        type = 1;
    } else if (itemId <= 0xFF) {
        type = 2;
    } else if (itemId <= 0x124) {
        type = 3;
    } else if (itemId == 0x125) {
        type = 4;
    } else if (itemId <= 0x129) {
        type = 5;
    } else if (itemId <= 0x17C) {
        type = 6;
    } else if (itemId <= 0x17C) {
        type = 6;
    } else if (itemId <= 0x188) {
        type = 7;
    } else if (itemId < 0x191) {
        type = 8;
    } else {
        type = 9;
    }
    return type;
}

/*
 * --INFO--
 * PAL Address: 0x8014744c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMenuPcs::CalcListPos(int listPos, int listSize, int mode)
{
    float span;

    if (mode != 0) {
        span = static_cast<float>(listSize - 1);
    } else {
        span = static_cast<float>(listSize - 8);
    }

    if ((span <= 0.0f) || (listSize <= 8)) {
        return (-1.0f);
    }

    span = static_cast<float>(listPos) / span;
    return 192.0f * span + 32.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawListPosMark(float x, float y, float z)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x2E)));
    MenuPcs.DrawRect(0, 10.0f + x, y + z, 8.0f, 8.0f, 128.0f,
        280.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x801471cc
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::EquipChk(int itemNo)
{
    CCaravanWork* w = Game.m_scriptFoodBase[0];
    int item;
    int slot;
    for (slot = 2; slot < 8; slot++) {
        if (slot >= w->m_numCmdListSlots) {
            break;
        }
        item = w->m_commandListInventorySlotRef[slot];
        if ((item >= 0) && (item == itemNo)) {
            return 1;
        }
    }

    item = w->m_equipment[0];
    if ((item >= 0) && (item == itemNo)) {
        return 1;
    }
    item = w->m_equipment[1];
    if ((item >= 0) && (item == itemNo)) {
        return 1;
    }
    item = w->m_equipment[2];
    if ((item >= 0) && (item == itemNo)) {
        return 1;
    }
    item = w->m_equipment[3];
    if ((item >= 0) && (item == itemNo)) {
        return 1;
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x801470b8
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawEquipMark(int x, int y, float alpha)
{
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(static_cast<int>(255.0f * alpha));
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x2C)));

    MenuPcs.DrawRect(0, static_cast<float>(x),
        static_cast<float>(y), 24.0f, 24.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f);
}

#ifdef VERSION_GCCP01
#define SINGWIN_OPEN_FRAMES 6
#else
#define SINGWIN_OPEN_FRAMES 8
#endif

/*
 * --INFO--
 * PAL Address: 0x80146adc
 * PAL Size: 1500b
 * EN Address: 0x80145C4C
 * EN Size: 1500b
 * JP Address: 0x8014220C
 * JP Size: 1488b
 */
void CMenuPcs::DrawSingWin(short mode)
{
    int i;

    float topScale;
    double innerW;
    if (mode >= 0 && m_menuWindowInfo->state != mode) {
        m_menuWindowInfo->state = mode;
    }

    if (m_menuWindowInfo->state == 3) {
        return;
    }

    float left = static_cast<float>(m_menuWindowInfo->x) + static_cast<float>(static_cast<double>(m_menuWindowInfo->width) / 2.0);
    float top = static_cast<float>(m_menuWindowInfo->y) + static_cast<float>(static_cast<double>(m_menuWindowInfo->height) / 2.0);
    float height;
    float width;

    if (m_menuWindowInfo->state != 1) {
        float leftScale = (left - m_menuWindowInfo->x - 32.0f) / SINGWIN_OPEN_FRAMES;
        leftScale *= m_menuWindowInfo->frame;
        topScale = (top - m_menuWindowInfo->y - 32.0f) / SINGWIN_OPEN_FRAMES;
        topScale *= m_menuWindowInfo->frame;
        width = static_cast<float>(2.0 * static_cast<double>(32.0f + leftScale));
        left = (left - 32.0f) - leftScale;
        height = static_cast<float>(2.0 * static_cast<double>(32.0f + topScale));
        top = (top - 32.0f) - topScale;
    } else {
        left = static_cast<float>(m_menuWindowInfo->x);
        top = static_cast<float>(m_menuWindowInfo->y);
        width = static_cast<float>(m_menuWindowInfo->width);
        height = static_cast<float>(m_menuWindowInfo->height);
    }

    int leftPx = static_cast<int>(static_cast<double>(left) - 0.5);
    int topPx = static_cast<int>(static_cast<double>(top) - 0.5);
    int widthPx = static_cast<int>(static_cast<double>(width) - 1.0);
    int heightPx = static_cast<int>(static_cast<double>(height) - 1.0);

    float x0 = static_cast<float>(leftPx);
    float y0 = static_cast<float>(topPx);
    float w = static_cast<float>(widthPx);
    float h = static_cast<float>(heightPx);

    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));
    float innerX;
    _GXColor white;
    white.r = 0xFF;
    white.g = 0xFF;
    white.b = 0xFF;
    white.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, white);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x3F)));
    float x1 = x0 + w - 32.0f;
    float y1 = y0 + h - 32.0f;
    double innerH;
    unsigned long uvFlag;
    for (i = 0; i < 4; i++) {
        uvFlag = 0;
        float x;
        if ((i & 1) != 0) {
            uvFlag |= 8;
            x = x1;
        } else {
            x = x0;
        }
        float y;
        if ((i & 2) != 0) {
            uvFlag |= 4;
            y = y1;
        } else {
            y = y0;
        }
        MenuPcs.DrawRect(uvFlag, x, y, 32.0f, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x41)));
    innerX = 32.0f + x0;
    innerW = static_cast<double>(w) - 64.0;
    float yy = y0;
    float innerWf = static_cast<float>(innerW);
    float innerHf;
    for (i = 0; i < 2; i++) {
        uvFlag = 0;
        if (i != 0) {
            yy = y1;
            uvFlag |= 4;
        }
        MenuPcs.DrawRect(uvFlag, innerX, yy, innerWf, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x40)));
    float innerY = 32.0f + y0;
    innerH = static_cast<double>(h) - 64.0;
    innerHf = static_cast<float>(innerH);
    float xx = x0;
    for (i = 0; i < 2; i++) {
        uvFlag = 0;
        if (i != 0) {
            xx = x1;
            uvFlag |= 8;
        }
        MenuPcs.DrawRect(uvFlag, xx, innerY, 32.0f, innerHf, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x42)));
    MenuPcs.DrawRect(uvFlag, innerX, innerY, static_cast<float>(innerW), static_cast<float>(innerH), 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuWindowInfo* win = m_menuWindowInfo;
    int state = win->state;
    if (state == 0) {
        win->frame = win->frame + 1;
        if (m_menuWindowInfo->frame >= SINGWIN_OPEN_FRAMES) {
            m_menuWindowInfo->frame = SINGWIN_OPEN_FRAMES;
            m_menuWindowInfo->state = 1;
        }
    } else if (state == 1) {
        if (win->frame != SINGWIN_OPEN_FRAMES) {
            win->frame = SINGWIN_OPEN_FRAMES;
        }
    } else if (state == 2) {
        win->frame = win->frame - 1;
        if (m_menuWindowInfo->frame <= 0) {
            m_menuWindowInfo->frame = 0;
            m_menuWindowInfo->state = 3;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x801466ec
 * PAL Size: 1008b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingWinMess(int messageNo, int activeMask, int useDynamic)
{
    const char* text;
    int i;
    int lineCount;
    int maxWidth;
    CFont* font;
    font = GetFont22();
    #ifdef VERSION_GCCJGC
    font->SetMargin(4.0f);
#else
    font->SetMargin(1.0f);
#endif
    font->SetShadow(1);
    font->SetScale(s_WinMessScl);
    font->DrawInit();

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);

    maxWidth = 0;
    if (useDynamic != 0) {
        lineCount = s_DynamicMess[0];
    } else {
        lineCount = s_SingMess[messageNo].lineCount;
    }
    for (i = 0; i < lineCount; i++) {
#ifdef VERSION_GCCJGC
        if (!useDynamic) {
            text = GetMenuStr(s_SingMess[messageNo].textIds[i]);
        } else {
            text = s_DynamicMessStr + i * 0x80;
        }
#else
        if (useDynamic == 0) {
            text = GetSingWinMessage(s_SingMess[messageNo].textIds[i], s_DynamicMessStr + i * 0x80, 0);
        } else {
            text = s_DynamicMessStr + i * 0x80;
        }
#endif
        int textWidth = font->GetWidth(text);
        if (textWidth > maxWidth) {
            maxWidth = textWidth;
        }
    }

    MenuWindowInfo* win = m_menuWindowInfo;
    float x = static_cast<float>(static_cast<double>(win->width - maxWidth) / 2.0
            + static_cast<double>(win->x));
    float y = static_cast<float>(win->y + 0x20);
    int lineHeight = static_cast<int>(22.0f * s_WinMessScl);
    if (22.0f * s_WinMessScl - static_cast<float>(lineHeight) > 0.0f) {
        lineHeight++;
    }
    int lineStep = lineHeight + 3;
    float yOffset = 4.0f;

    for (i = 0; i < lineCount; i++) {
        font->SetTlut((activeMask & (1 << i)) != 0 ? 7 : 8);

#ifdef VERSION_GCCJGC
        if (!useDynamic) {
            text = GetMenuStr(s_SingMess[messageNo].textIds[i]);
        } else {
            text = s_DynamicMessStr + i * 0x80;
        }
#else
        if (useDynamic == 0) {
            text = GetSingWinMessage(s_SingMess[messageNo].textIds[i], s_DynamicMessStr + i * 0x80, 0);
        } else {
            text = s_DynamicMessStr + i * 0x80;
        }
#endif
        if (static_cast<int>(strlen(text)) != 0) {
            char lineBuffer[128];
            strcpy(lineBuffer, text);
            font->SetPosX(x);
#ifdef VERSION_GCCJGC
            font->SetPosY(y);
#else
            font->SetPosY(y - yOffset);
#endif
            font->Draw(lineBuffer);
        }

        y += static_cast<float>(lineStep);
    }

    DrawInit();
}

/*
 * --INFO--
 * PAL Address: 0x801464cc
 * PAL Size: 544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetSingWinSize(int messageNo, short* outWidth, short* outHeight, int useDynamic)
{
    CFont* font;
    int i;
    int maxWidth;
    int lineCount;

    font = GetFont22();
    #ifdef VERSION_GCCJGC
    font->SetMargin(4.0f);
#else
    font->SetMargin(1.0f);
#endif
#ifdef VERSION_GCCJGC
    font->SetShadow(0);
#else
    font->SetShadow(1);
#endif
    font->SetScale(s_WinMessScl);

    maxWidth = 0;
    if (useDynamic != 0) {
        lineCount = s_DynamicMess[0];
    } else {
        lineCount = s_SingMess[messageNo].lineCount;
    }
    for (i = 0; i < lineCount; i++) {
        const char* text;
#ifdef VERSION_GCCJGC
        if (!useDynamic) {
            text = GetMenuStr(s_SingMess[messageNo].textIds[i]);
        } else {
            text = s_DynamicMessStr + i * 0x80;
        }
#else
        if (useDynamic == 0) {
            text = GetSingWinMessage(s_SingMess[messageNo].textIds[i], s_DynamicMessStr + i * 0x80, 0);
        } else {
            text = s_DynamicMessStr + i * 0x80;
        }
#endif
        int textWidth = font->GetWidth(text);
        if (textWidth > maxWidth) {
            maxWidth = textWidth;
        }
    }

    if (useDynamic != 0) {
        maxWidth += 0x16;
    } else {
        maxWidth -= 0x18;
    }

    int lineHeight = static_cast<int>(22.0f * s_WinMessScl);
    if (22.0f * s_WinMessScl - static_cast<float>(lineHeight) > 0.0f) {
        lineHeight++;
    }

    int widthLines = maxWidth / lineHeight;
    if (maxWidth - widthLines * lineHeight != 0) {
        widthLines++;
    }

#ifdef VERSION_GCCJGC
    widthLines += 3;
#else
    if (useDynamic == 0) {
        widthLines += 3;
    }
#endif

    *outWidth = static_cast<short>(widthLines * lineHeight + 0x40);
    *outHeight = static_cast<short>(lineCount * (lineHeight + 2) + 0x40);
}

/*
 * --INFO--
 * PAL Address: 0x80146490
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetSingWinInfo(int x, int y, int w, int h)
{
    m_menuWindowInfo->x = static_cast<s16>(x);
    m_menuWindowInfo->y = static_cast<s16>(y);
    m_menuWindowInfo->width = static_cast<s16>(w);
    m_menuWindowInfo->height = static_cast<s16>(h);
    m_menuWindowInfo->frame = 0;
    m_menuWindowInfo->state = 3;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingDynamicWinMessInfo(
    int lineCount,
    char* line0,
    char* line1,
    char* line2,
    char* line3,
    char* line4,
    char* line5,
    char* line6,
    char* line7)
{
    s_DynamicMess[0] = lineCount;

    if (line0 != 0) {
        strcpy(s_DynamicMessStr, line0);
    }
    if (line1 != 0) {
        strcpy(s_DynamicMessStr + 0x80, line1);
    }
    if (line2 != 0) {
        strcpy(s_DynamicMessStr + 0x100, line2);
    }
    if (line3 != 0) {
        strcpy(s_DynamicMessStr + 0x180, line3);
    }
    if (line4 != 0) {
        strcpy(s_DynamicMessStr + 0x200, line4);
    }
    if (line5 != 0) {
        strcpy(s_DynamicMessStr + 0x280, line5);
    }
    if (line6 != 0) {
        strcpy(s_DynamicMessStr + 0x300, line6);
    }
    if (line7 != 0) {
        strcpy(s_DynamicMessStr + 0x380, line7);
    }
}


/*
 * --INFO--
 * PAL Address: 0x80146364
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetSingWinScl(float scale)
{
    s_WinMessScl = scale;
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
inline float CMenuPcs::GetSingWinScl()
{
    return s_WinMessScl;
}

/*
 * --INFO--
 * PAL Address: 0x8014630c
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::SingWinMessHeight()
{
    float scaled = 22.0f * s_WinMessScl;
    int lineHeight = static_cast<int>(scaled);

    if (scaled - static_cast<float>(lineHeight) > 0.0f) {
        lineHeight += 1;
    }
    return lineHeight + 3;
}

/*
 * --INFO--
 * PAL Address: 0x8014624c
 * PAL Size: 192b
 * EN Address: 0x8016C45C
 * EN Size: 284b
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::ChkEquipPossible(int itemNo)
{
    unsigned int genderMask;
    CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];
    int flags = reinterpret_cast<const SItemFlatRow*>(Game.m_itemTable)[itemNo].m_equipFlags;
    int raceBits = flags & 0xF;
    int genderBits = flags & 0x30;
    unsigned int raceMask = 1 << (caravanWork->m_tribeId & 3);

    if (caravanWork->m_genderFlag != 0) {
        genderMask = 0x20;
    } else {
        genderMask = 0x10;
    }

    int result;
    if ((raceBits != 0) && (genderBits != 0)) {
        if (((raceBits & raceMask) != 0) && ((genderBits & genderMask) != 0)) {
            result = 1;
        } else {
            result = 0;
        }
    } else if (raceBits != 0) {
        result = (raceBits & raceMask) != 0;
    } else {
        result = (genderBits & genderMask) != 0;
    }
    return result != 0;
}

/*
 * --INFO--
 * PAL Address: 0x80146190
 * PAL Size: 188b
 * EN Address: 0x8016C578
 * EN Size: 348b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetEquipType(int itemNo)
{
    u16 flags = reinterpret_cast<const SItemFlatRow*>(Game.m_itemTable)[itemNo].m_equipFlags;
    int equipType;

    if (flags & 0x100) {
        equipType = 0;
    } else if (flags & 0x400) {
        equipType = 1;
    } else if (flags & 0xA00) {
        equipType = 2;
    } else if (flags & 0x3000) {
        equipType = 3;
    } else {
        // BUG (original): equipType is returned uninitialized on this path.
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf("%s(%d): item = %d m_equip = %08x\n", "singmenu.cpp", SINGMENU_LINE(0xD3D, 0xD38, 0xCAE), itemNo, flags);
        }
    }

    return equipType;
}

/*
 * --INFO--
 * PAL Address: 0x80145ff4
 * PAL Size: 412b
 * EN Address: 0x80145164
 * EN Size: 412b
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetSmithItem(int itemNo)
{
    CCaravanWork* caravanWork = Game.m_scriptFoodBase[0];

    GetItemType(itemNo, 1);
    u16 race = caravanWork->m_tribeId;
    int raceType = race & 3;
    SItemFlatRow* rec = &reinterpret_cast<SItemFlatRow*>(Game.m_itemTable)[itemNo];
    int smithItem = rec->m_smithResults[race & 3];
    if (smithItem > 0 && ChkEquipPossible(smithItem)) {
        return smithItem;
    }

    for (int i = 0; i < 4; i++) {
        if (raceType != i) {
            smithItem = rec->m_smithResults[i];
            if (smithItem > 0) {
                return smithItem;
            }
        }
    }
    return 0xFFFFFFFF;
}

/*
 * --INFO--
 * PAL Address: 0x80145f70
 * PAL Size: 132b
 * EN Address: 0x8016C820
 * EN Size: 232b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetRecipeMaterial(int itemNo, CMenuPcs::MaterialInfo* materialInfo)
{
    GetItemType(itemNo, 1);

    const SItemFlatRow* itemBase = &reinterpret_cast<SItemFlatRow*>(Game.m_itemTable)[itemNo];

    materialInfo->m_itemNo[0] = itemBase->m_smithMaterials[0];
    materialInfo->m_count[0] = itemBase->m_smithMaterialCounts[0];
    materialInfo->m_itemNo[1] = itemBase->m_smithMaterials[1];
    materialInfo->m_count[1] = itemBase->m_smithMaterialCounts[1];
    materialInfo->m_itemNo[2] = itemBase->m_smithMaterials[2];
    materialInfo->m_count[2] = itemBase->m_smithMaterialCounts[2];
}

/*
 * --INFO--
 * PAL Address: 0x80145c84
 * PAL Size: 748b
 * EN Address: 0x8016C908
 * EN Size: 400b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetRaceStr(int itemNo, char* outText)
{
#ifdef VERSION_GCCJGC
    unsigned short raceBits;
    int raceType;

    GetItemType(itemNo, 1);
    raceBits = reinterpret_cast<const SItemFlatRow*>(Game.m_itemTable)[itemNo].m_equipFlags;
    int raceLow = raceBits & 0xF;
    int genderMask = raceBits & 0x30;
    outText[0] = '\0';

    if (raceLow == 0xF) {
        strcpy(outText, GetMenuStr(19));
        return;
    }

    for (raceType = 0; raceType < 4; raceType++) {
        if ((raceLow & (1 << raceType)) != 0) {
            break;
        }
    }

    if (raceType < 4) {
        strcpy(outText, GetTribeStr(raceType));
    }

    if (raceLow != 0 && genderMask != 0) {
        strcpy(outText, "\x81\x40");
    }
    if (genderMask == 0) {
        return;
    }

    strcat(outText, GetMenuStr(((genderMask >> 5) & 1) + 17));
#else
    unsigned short raceBits;
    int raceType;

    GetItemType(itemNo, 1);
    raceBits = reinterpret_cast<const SItemFlatRow*>(Game.m_itemTable)[itemNo].m_equipFlags;
    int raceLow = raceBits & 0xF;
    int genderMask = raceBits & 0x30;
    outText[0] = '\0';

    if (raceLow == 0xF) {
        strcpy(outText, GetMenuStr(19));
        return;
    }

    for (raceType = 0; raceType < 4; raceType++) {
        if ((raceLow & (1 << raceType)) != 0) {
            break;
        }
    }

    if (raceType < 4) {
        strcpy(outText, GetTribeStr(raceType));
        if (static_cast<int>(Game.m_gameWork.m_languageId) == 2) {
            strcat(outText, "s");
        }
    }

    if (raceLow != 0 && genderMask != 0) {
        strcpy(outText, " ");
    }

    if (genderMask == 0) {
        return;
    }

    raceType = (genderMask >> 5) & 1;
    strcat(outText, GetMenuStr(raceType + 17));
#endif
}

/*
 * --INFO--
 * PAL Address: 0x801458ec
 * PAL Size: 920b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingBar(int x, int y, int value, float alpha)
{
    int barY;
    int tex;
    int barX;
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<unsigned char>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x53)));
    MenuPcs.DrawRect(0, static_cast<float>(x), static_cast<float>(y), 16.0f,
                                    24.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, static_cast<float>(x + 0x60), static_cast<float>(y), 16.0f,
                                    24.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(0x54)));
    MenuPcs.DrawRect(0, static_cast<float>(x + 0x10), static_cast<float>(y),
                                    80.0f, 24.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);

    if (value <= 0x28) {
        tex = SINGMENU_TEX_ID(0x59);
    } else if (value <= 0x3C) {
        tex = SINGMENU_TEX_ID(0x57);
    } else {
        tex = SINGMENU_TEX_ID(0x55);
    }

    int bars = value / 10;
    if (value % 10 != 0) {
        ++bars;
    }

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex));
    barX = x + 0x10;
    barY = y + 8;
    MenuPcs.DrawRect(0, static_cast<float>(barX), static_cast<float>(barY),
                                    4.0f, 8.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);
    barX += bars * 8 - 4;
    MenuPcs.DrawRect(8, static_cast<float>(barX), static_cast<float>(barY),
                                    4.0f, 8.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(tex + 1));
    MenuPcs.DrawRect(0, static_cast<float>(x + 0x14), static_cast<float>(barY),
                                    static_cast<float>(bars * 8 - 8), 8.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x801458e4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingSetLetterAttachflg(int flag)
{
    gSingMenuForcedSelection = flag;
}

/*
 * --INFO--
 * PAL Address: 0x801458dc
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::SingGetLetterAttachflg()
{
    return gSingMenuForcedSelection;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::CalcSingLife()
{
    if (m_singleLifeTimer >= 0) {
        m_singleLifeTimer++;
        if (m_singleLifeTimer > 0x31) {
            m_singleLifeTimer = -1;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80145738
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingLife()
{
    int lifeTimer = m_singleLifeTimer;
    float xBase = 366.0f;
    float y = (-32.0f);
    const CCaravanWork* const caravanWork = Game.m_scriptFoodBase[0];
    if (lifeTimer < 0) {
        return;
    }

    if (lifeTimer < 10) {
        y += 64.0f * sinf(0.01745329238474369f * (9.0f * static_cast<float>((lifeTimer < 0) ? 0 : ((lifeTimer > 10) ? 10 : lifeTimer))));
    } else if (lifeTimer < 0x28) {
        y = 32.0f;
    } else {
        int t = 10 - (lifeTimer - 0x28);
        y += 64.0f * sinf(0.01745329238474369f * (9.0f * static_cast<float>((t < 0) ? 0 : ((t > 10) ? 10 : t))));
    }

    int halfHearts = static_cast<unsigned int>(caravanWork->m_maxHp) >> 1;
    xBase += static_cast<float>(((8 - halfHearts) * 0x18) / 2);
    MenuPcs.m_battleMesMenus[0]->DrawHeart(xBase, y - 8.0f, 1.0f, 1.0f);
}

/*
 * --INFO--
 * PAL Address: 0x80145710
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SingLifeInit(int timer)
{
    if ((m_singleLifeTimer > 0) && (timer == 0)) {
        m_singleLifeTimer = 10;
        return;
    }
    m_singleLifeTimer = timer;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::SingLifeResetWait()
{
    SingLifeInit(0);
}

#ifndef VERSION_GCCJGC
/*
 * --INFO--
 * PAL Address: 0x80145674
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetTribeStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 2:
            return (char*)s_TribeStr_ge[index];
        case 3:
            return (char*)s_TribeStr_it[index];
        case 4:
            return (char*)s_TribeStr_fr[index];
        case 5:
            return (char*)s_TribeStr_sp[index];
        case 1:
        default:
            return (char*)s_TribeStr_us[index];
    }
}

char* CMenuPcs::GetJobStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 2:
            return (char*)s_JobStr_ge[index];
        case 3:
            return (char*)s_JobStr_it[index];
        case 4:
            return (char*)s_JobStr_fr[index];
        case 5:
            return (char*)s_JobStr_sp[index];
        case 1:
        default:
            return (char*)s_JobStr_us[index];
    }
}

char* CMenuPcs::GetHairStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 2:
            return (char*)s_HairStr_ge[index];
        case 3:
            return (char*)s_HairStr_it[index];
        case 4:
            return (char*)s_HairStr_fr[index];
        case 5:
            return (char*)s_HairStr_sp[index];
        case 1:
        default:
            return (char*)s_HairStr_us[index];
    }
}

char* CMenuPcs::GetMenuStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 2:
            return (char*)s_MenuStr_ge[index];
        case 3:
            return (char*)s_MenuStr_it[index];
        case 4:
            return (char*)s_MenuStr_fr[index];
        case 5:
            return (char*)s_MenuStr_sp[index];
        case 1:
        default:
            return (char*)s_MenuStr_us[index];
    }
}

char* CMenuPcs::GetAttrStr(int index)
{
    switch (Game.m_gameWork.m_languageId) {
        case 2:
            return (char*)s_AttrStr_ge[index];
        case 3:
            return (char*)s_AttrStr_it[index];
        case 4:
            return (char*)s_AttrStr_fr[index];
        case 5:
            return (char*)s_AttrStr_sp[index];
        case 1:
        default:
            return (char*)s_AttrStr_us[index];
    }
}

/*
 * --INFO--
 * PAL Address: 0x801453f4
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetItemIcon(int index)
{
    return s_ItemIcon[index];
}
#endif
