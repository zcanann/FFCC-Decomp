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

extern "C" {
const u8 gSingMenuItemIconByType[0x1F5] = {
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
}
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

static inline CCaravanWork* SingleCaravanWork()
{
    return Game.m_scriptFoodBase[0];
}

struct SingMenuStaticMessageInfo
{
    int lineCount;
    s16 textIds[8];
};

struct SingMenuTextureRef
{
    int textureSetIndex;
    char* textureName;
};

struct SingMenuSoloNameTable
{
    char* entries[9];
};

extern char s_singmenu_cpp[];

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

static inline CMenuPcs::TEX SingMenuTex(int id)
{
    return static_cast<CMenuPcs::TEX>(SINGMENU_TEX_ID(id));
}

extern "C" char s_singMenuTexturePathFmt[];
extern "C" char s_singMenuSubfontPathFmt[];

extern "C" {
extern char s_pcts_pctd_item_pctd_m_equip_pct08x_801DE8B0[];
}
#ifndef VERSION_GCCJGC
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
#endif

extern "C" {
extern int s_DynamicMess[5];
}
extern char s_DynamicMessStr[0x400];
extern "C" SingMenuStaticMessageInfo s_singleMenuStaticMessages[];

extern "C" SingMenuStaticMessageInfo s_singleMenuStaticMessages[] = {
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

extern "C" SingMenuTextureRef s_singleMenuModelTextureTable[] = {
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
extern "C" SingMenuTextureRef s_singleMenuModelTextureTable[];
float FLOAT_8032ea78 = 0.8999999761581421f;

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
        if (font->DecRef() == 0) {
            delete font;
        }
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
    Graphic._WaitDrawDone(s_singmenu_cpp, SINGMENU_LINE(0x5C2, 0x5BD, 0x563));
    Graphic.DestroyTempBuffer();

    m_stageF4 = Graphic.GetTempStage();
    memset(&m_singleMenuTextureLoadIndex, 0, 8);
    m_wm.m_handles[0] = 0;

    CCharaPcs::CHandle* handle = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, SINGMENU_LINE(0x5CD, 0x5C8, 0x56E)) CCharaPcs::CHandle;
    m_wm.m_handles[0] = handle;

    CCharaPcs::CHandle** handlePtr = &m_wm.m_handles[0];
    (*handlePtr)->Add();
    CCaravanWork* caravanWork = SingleCaravanWork();
    int modelNo = GetModelNo(
        static_cast<int>(caravanWork->m_tribeId),
        static_cast<int>(caravanWork->m_appearanceVariant),
        static_cast<int>(caravanWork->m_genderFlag));
    (*handlePtr)->LoadModel(0, static_cast<unsigned long>(modelNo), 0, 0, -1, 0, 0);
    (*handlePtr)->m_flags |= 0x300141;
    (*handlePtr)->LoadAnim("stand", 0, 1, 0, (static_cast<unsigned int>((*handlePtr)->m_charaNo) / 100) * 100, -1, 0);
    (*handlePtr)->SetAnim(0, -1, -1, -1, 0);

    m_wm.m_worldObjData = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, SINGMENU_LINE(0x5DD, 0x5D8, 0x57E)) WmWorldObjInfo[1];

    float left = 440.0f;
    float top = 88.0f;
    float width = 96.0f;
    left += 28.0f;
    int scissorX = static_cast<int>(12.0f + left);
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
    double half = 0.5;
    float centerX = 4.0 + (width * half + left);
    float centerY = top * half + top;
    centerX -= 320.0;
    centerY -= 224.0;
    m_wm.m_worldObjData->m_viewportX = static_cast<s16>(centerX - 4.0);
    m_wm.m_worldObjData->m_viewportY = static_cast<s16>(static_cast<int>(centerY));
    m_wm.m_worldObjData->m_scissorX = scissorX;
    m_wm.m_worldObjData->m_scissorY = static_cast<int>(top - 8.0f);
    m_wm.m_worldObjData->m_scissorWidth = 0x48;
    m_wm.m_worldObjData->m_scissorHeight = 0x58;

    m_singleFadeState = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, SINGMENU_LINE(0x605, 0x600, 0x5A6)) SingleFadeState;
    memset(m_singleFadeState, 0, sizeof(SingleFadeState));

    m_singMenuState = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, SINGMENU_LINE(0x609, 0x604, 0x5AA)) SingMenuState;
    memset(m_singMenuState, 0, sizeof(SingMenuState));

    m_menuWindowInfo = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, SINGMENU_LINE(0x60D, 0x608, 0x5AE)) MenuWindowInfo;
    memset(m_menuWindowInfo, 0, sizeof(MenuWindowInfo));

    m_singleMenuPhase = 0;
    if (gSingMenuForcedSelection >= 0) {
        m_singleMenuMode = 8;
        gSingMenuForcedSelection = -1;
    }
    FLOAT_8032ea78 = 0.8999999761581421f;
    m_singleLifeTimer = -1;
    m_singleMenuCtrlResetFlag = 1;
    m_singleMenuInitialized = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::SingMenuEnd()
{
    Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 0;
    gSingMenuHasScriptFoodBase = 0;
    gSingMenuAsyncLoadCompleted = 0;
    destroySingleMenu();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline void CMenuPcs::calcSingleMenu()
{
    loadTextureAsync(0, 0, 0, 0, 0, 0, 0);
}

static inline int LoadSingMenuTextureStep(CMenuPcs* menu)
{
    int loadIndex = menu->m_singleMenuTextureLoadIndex;
    if (loadIndex >= 2) {
        return 1;
    }

    if (menu->m_singleMenuTextureLoadState == 0) {
        char path[256];
#ifdef VERSION_GCCJGC
        sprintf(path, s_singMenuTexturePathFmt, PTR_s_solo1.entries[loadIndex]);
#else
        sprintf(path, s_singMenuTexturePathFmt, Game.GetLangString(), PTR_s_solo1.entries[loadIndex]);
#endif
        gSingMenuAsyncFileHandle = File.Open(path, 0, CFile::PRI_LOW);
        File.ReadASync(gSingMenuAsyncFileHandle);
        menu->m_singleMenuTextureLoadState = menu->m_singleMenuTextureLoadState + 1;
    } else if (menu->m_singleMenuTextureLoadState == 1) {
        if (!File.IsCompleted(gSingMenuAsyncFileHandle)) {
            return 0;
        }

        menu->m_textureSets[loadIndex + 5] = new (Game.m_gameWork.m_menuStageMode != 0 ? MenuPcs.m_stageF4 : MenuPcs.m_menuStage, s_singmenu_cpp, SINGMENU_LINE(0x748, 0x743, 0x6E8)) CTextureSet;

        void* buffer = File.m_readBuffer;
        menu->m_textureSets[loadIndex + 5]->Create(buffer, Game.m_gameWork.m_menuStageMode != 0 ? menu->m_stageF4 : menu->m_menuStage, 0, 0, 0, 0);
        File.Close(gSingMenuAsyncFileHandle);
        gSingMenuAsyncFileHandle = 0;
        menu->m_singleMenuTextureLoadState = 0;
        menu->m_singleMenuTextureLoadIndex = menu->m_singleMenuTextureLoadIndex + 1;
    }

    if (menu->m_singleMenuTextureLoadIndex < 2) {
        return 0;
    }

    for (int i = 0; i < 0x33; i++) {
        int texIdx = menu->m_textureSets[s_singleMenuModelTextureTable[i].textureSetIndex]->Find(s_singleMenuModelTextureTable[i].textureName);
        CTexture* tex = menu->m_textureSets[s_singleMenuModelTextureTable[i].textureSetIndex]->GetTexture(static_cast<unsigned long>(texIdx));
        tex->AddRef();
        menu->m_textures[SINGMENU_TEX_ID(i + 45)] = tex;
    }
    return 1;
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
void CMenuPcs::loadTextureAsync(char **, int, int, CMenuPcs::CTmp*, int, int, int)
{
    gSingMenuHasScriptFoodBase = static_cast<int>(SingleCaravanWork()->m_shopRequestState != 0);
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

    if (SingleCaravanWork()->m_shopRequestState == 0) {
        gSingMenuAsyncLoadCompleted = LoadSingMenuTextureStep(this);
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

    char menuKind = SingleCaravanWork()->m_shopRequestState;
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
                if (font->DecRef() == 0) {
                    delete font;
                }
                m_fonts[4] = 0;
            }

            m_singleMenuStageActive = 0;
            m_singleMenuInitialized = 0;
        }
    } else {
        if (m_singleMenuStageActive == 0) {
            m_stageF0 = CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_ANIM];
            m_singleMenuStageActive = 1;
        }

#ifdef VERSION_GCCJGC
        loadFont(1, s_singMenuSubfontPathFmt, 4, -1);
#else
        char path[128];
        sprintf(path, s_singMenuSubfontPathFmt, Game.GetLangString());
        loadFont(1, path, 4, -1);
#endif

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
        }
    }
}

static inline void DrawSingleBack(CMenuPcs* menu, float alpha)
{
    menu->DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(SingMenuTex(0x20));
    MenuPcs.DrawRect(0, 0.0f, 0.0f, 640.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 0.0f, 384.0f, 640.0f, 64.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(SingMenuTex(0x28));
    int y;
    int step = 0x20;
    for (y = 0x40; y < 0x180; y += step) {
        if ((0x180 - y) < step) {
            step = 0x180 - y;
        }
        MenuPcs.DrawRect(0, 0.0f, static_cast<float>(y), 640.0f, static_cast<float>(step),
                         0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }
}

static inline void DrawSingleFrame(CMenuPcs* menu, float alpha)
{
    menu->DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, color);
    MenuPcs.SetTexture(SingMenuTex(0x21));
    MenuPcs.DrawRect(0, -(176.0f * alpha - 208.0f), 24.0f, 176.0f, 288.0f, 0.0f, 0.0f, alpha, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, 224.0f, 24.0f, 176.0f, 288.0f, 0.0f, 0.0f, alpha, 1.0f, 0.0f);
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
        gUtil.ClearZBufferRect(0.0f, 0.0f, 640.0f, 448.0f);
        DrawInit();

        char menuType = SingleCaravanWork()->m_shopRequestState;
        if (menuType == 1) {
            if (m_shopMenu != 0) {
                m_shopMenu->Draw();
            }
        } else if ((menuType == 2) && (m_shopMenu != 0)) {
            m_shopMenu->Draw();
        }

        if ((gSingMenuHasScriptFoodBase != 0) && (m_singleFadeState->done != 0)) {
            Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 0;
            Graphic._WaitDrawDone(s_singmenu_cpp, SINGMENU_LINE(0x62B, 0x626, 0x5CC));
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

        if (gSingMenuHasScriptFoodBase != 0) {
            return;
        }

        s16 mode = m_singleMenuPhase;
        switch (mode) {
        case 0:
        {
            SingleFadeState* fadeState = m_singleFadeState;
            int count = fadeState->count;
            int i = 0;
            SingleFadeEntry* entry = fadeState->entries;
            for (; i < count; i++, entry++) {
                if ((i == 0) || (m_singleMenuMode != 8)) {
                    if (i == 0) {
                        DrawSingleBack(this, entry->alpha);
                    } else if (i == 1) {
                        DrawSingleFrame(this, entry->alpha);
                    } else if (i == 2) {
                        DrawSingleStat(entry->alpha);
                    } else {
                        DrawSingleHelpWim(entry->alpha);
                    }
                }
            }
            return;
        }
        case 1:
            SingleDrawCtrl();
            return;
        case 2:
        {
            SingleFadeState* fadeState = m_singleFadeState;
            int count = fadeState->count;
            int i = 0;
            SingleFadeEntry* entry = fadeState->entries;
            for (; i < count; i++, entry++) {
                if ((i == 0) || (m_singleMenuMode != 8)) {
                    if (i == 0) {
                        DrawSingleBack(this, entry->alpha);
                    } else if (i == 1) {
                        DrawSingleFrame(this, entry->alpha);
                    } else if (i == 2) {
                        DrawSingleStat(entry->alpha);
                    } else {
                        DrawSingleHelpWim(entry->alpha);
                    }
                }
            }

            if (m_singleFadeState->done != 0) {
                Game.m_gameWork.m_singleShopOrSmithMenuActiveFlag = 0;
                Graphic._WaitDrawDone(s_singmenu_cpp, SINGMENU_LINE(0x62B, 0x626, 0x5CC));
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
            return;
        }
        }
    }
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

    unsigned short modelScaleIndex = SingleCaravanWork()->m_tribeId;
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

    MenuPcs.SetTexture(SingMenuTex(0x20));
    MenuPcs.DrawRect(0, 0.0f, 0.0f, 640.0f, 64.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 0.0f, 384.0f, 640.0f, 64.0f,
                                     0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(SingMenuTex(0x28));
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
    float sliceY = 40.0f;
    float sliceHeight = 8.0f;
    for (; sliceY < 408.0f; sliceY += sliceHeight) {
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

    int charaNo = SingleCaravanWork()->m_tribeId;
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
    font = m_fonts[0];
    font->SetMargin(1.0f);
    font->SetShadow(1);
    font->SetScale(0.8999999761581421f);

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, static_cast<u8>(a255)).color);
    font->DrawInit();

    char* charaName = reinterpret_cast<char*>(SingleCaravanWork()->m_name);
    float titleWidth = static_cast<float>(font->GetWidth(charaName));
    font->SetTlut(0x12);
    float titleX = 152.0f - titleWidth;
    titleX = 440.0f + static_cast<float>(0.5 * titleX);
    font->SetPosX(1.0f + titleX);
#ifdef VERSION_GCCJGC
    font->SetPosY(57.0f);
#else
    font->SetPosY(53.0f);
#endif
    font->Draw(charaName);

    font->SetTlut(0x17);
    font->SetPosX(titleX);
#ifdef VERSION_GCCJGC
    font->SetPosY(56.0f);
#else
    font->SetPosY(52.0f);
#endif
    font->Draw(charaName);

    font->SetTlut(0x15);
    float statY0 = 184.0f;
    float statYStep = 36.0f;
    float statPosX0 = 592.0f;
    float y = statY0;
    for (int i = 0; i < 4; i++) {
        font->SetPosX(440.0f);
#ifdef VERSION_GCCJGC
        font->SetPosY(y);
#else
        font->SetPosY(y - 4.0f);
#endif

        char* label;
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

        font->renderFlags.fixedWidth = 1;
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
            stat = SingleCaravanWork()->m_strength;
        } else if (i == 1) {
            stat = SingleCaravanWork()->m_defense;
        } else if (i == 2) {
            stat = SingleCaravanWork()->m_magic;
        } else {
            stat = SingleCaravanWork()->m_progressValue;
        }

        char valueText[36];
        sprintf(valueText, "%d", stat);
        float valueW = static_cast<float>(font->GetWidth(valueText));
        font->SetPosX(statPosX0 - valueW);
        font->Draw(valueText);

        font->renderFlags.fixedWidth = 0;
        font->SetMargin(1.0f);
        y += statYStep;
    }

    font->renderFlags.fixedWidth = 0;
    font->SetMargin(1.0f);
    DrawInit();
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

    MenuPcs.SetTexture(SingMenuTex(0x21));
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
inline void CMenuPcs::SingleDrawFadeIn()
{
    SingleFadeState* fadeState = m_singleFadeState;
    if (fadeState == 0) {
        return;
    }

    DrawSingleBase(fadeState->entries[0].alpha);
    if (m_singleMenuMode == 8) {
        return;
    }

    DrawSingleCrescent(fadeState->entries[1].alpha, fadeState->entries[1].alpha);
    DrawSingleStat(fadeState->entries[2].alpha);
    DrawSingleHelpWim(fadeState->entries[3].alpha);
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
inline void CMenuPcs::SingleDrawFadeOut()
{
    SingleFadeState* fadeState = m_singleFadeState;
    if (fadeState == 0) {
        return;
    }

    DrawSingleBase(fadeState->entries[0].alpha);
    if (m_singleMenuMode == 8) {
        return;
    }

    DrawSingleCrescent(fadeState->entries[1].alpha, fadeState->entries[1].alpha);
    DrawSingleStat(fadeState->entries[2].alpha);
    DrawSingleHelpWim(fadeState->entries[3].alpha);
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
    DrawSingleBack(this, 1.0f);

    if (m_singleMenuMode != 8) {
        DrawSingleFrame(this, 1.0f);
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
    FLOAT_8032ea78 = 0.8999999761581421f;
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
    DrawInit();
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    int alphaInt = static_cast<int>(255.0f * alpha);
    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<u8>(alphaInt);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(SingMenuTex(0x23));
    MenuPcs.DrawRect(0, 32.0f, 312.0f, 32.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, 576.0f, 312.0f, 32.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 32.0f, 384.0f, 32.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(0xC, 576.0f, 384.0f, 32.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(SingMenuTex(0x27));
    MenuPcs.DrawRect(0, 64.0f, 312.0f, 512.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(4, 64.0f, 384.0f, 512.0f, 32.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(SingMenuTex(0x24));
    MenuPcs.DrawRect(0, 32.0f, 344.0f, 32.0f, 40.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, 576.0f, 344.0f, 32.0f, 40.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(SingMenuTex(0x2B));
    MenuPcs.DrawRect(8, 64.0f, 344.0f, 512.0f, 40.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f, 0.0f);
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

    MenuPcs.SetTexture(SingMenuTex(0x25));
    int icon;
    if (rawIcon != 0) {
        icon = iconNo;
    } else {
        icon = static_cast<int>(gSingMenuItemIconByType[iconNo]);
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

    MenuPcs.SetTexture(SingMenuTex(0x2E));
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
    CCaravanWork* w = SingleCaravanWork();
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
    MenuPcs.SetTexture(SingMenuTex(0x2C));

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

    if (mode >= 0 && m_menuWindowInfo->state != mode) {
        m_menuWindowInfo->state = mode;
    }

    if (m_menuWindowInfo->state == 3) {
        return;
    }

    float left = static_cast<float>(m_menuWindowInfo->x) + static_cast<float>(static_cast<double>(m_menuWindowInfo->width) / 2.0);
    float top = static_cast<float>(m_menuWindowInfo->y) + static_cast<float>(static_cast<double>(m_menuWindowInfo->height) / 2.0);
    float width;
    float height;

    if (m_menuWindowInfo->state != 1) {
        float leftScale = (left - m_menuWindowInfo->x - 32.0f) / SINGWIN_OPEN_FRAMES;
        leftScale *= m_menuWindowInfo->frame;
        float topScale = (top - m_menuWindowInfo->y - 32.0f) / SINGWIN_OPEN_FRAMES;
        topScale *= m_menuWindowInfo->frame;
        left = (left - 32.0f) - leftScale;
        width = static_cast<float>(2.0 * static_cast<double>(32.0f + leftScale));
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
    _GXColor white;
    white.r = 0xFF;
    white.g = 0xFF;
    white.b = 0xFF;
    white.a = 0xFF;
    GXSetChanMatColor(GX_COLOR0A0, white);
    MenuPcs.SetTexture(SingMenuTex(0x3F));
    float x1 = x0 + w - 32.0f;
    float y1 = y0 + h - 32.0f;
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

    MenuPcs.SetTexture(SingMenuTex(0x41));
    double innerW = static_cast<double>(w) - 64.0;
    float innerX = 32.0f + x0;
    float yy = y0;
    float innerWf = static_cast<float>(innerW);
    for (i = 0; i < 2; i++) {
        uvFlag = 0;
        if (i != 0) {
            yy = y1;
            uvFlag |= 4;
        }
        MenuPcs.DrawRect(uvFlag, innerX, yy, innerWf, 32.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    MenuPcs.SetTexture(SingMenuTex(0x40));
    double innerH = static_cast<double>(h) - 64.0;
    float innerY = 32.0f + y0;
    float xx = x0;
    float innerHf = static_cast<float>(innerH);
    for (i = 0; i < 2; i++) {
        uvFlag = 0;
        if (i != 0) {
            xx = x1;
            uvFlag |= 8;
        }
        MenuPcs.DrawRect(uvFlag, xx, innerY, 32.0f, innerHf, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    }

    MenuPcs.SetTexture(SingMenuTex(0x42));
    MenuPcs.DrawRect(uvFlag, innerX, innerY, static_cast<float>(innerW), static_cast<float>(innerH), 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    MenuWindowInfo* win = m_menuWindowInfo;
    s16 state = win->state;
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
    font = m_fonts[0];
    #ifdef VERSION_GCCJGC
    font->SetMargin(4.0f);
#else
    font->SetMargin(1.0f);
#endif
    font->SetShadow(1);
    font->SetScale(FLOAT_8032ea78);
    font->DrawInit();

    font->SetColor(CColor(0xFF, 0xFF, 0xFF, 0xFF).color);

    maxWidth = 0;
    if (useDynamic != 0) {
        lineCount = s_DynamicMess[0];
    } else {
        lineCount = s_singleMenuStaticMessages[messageNo].lineCount;
    }
    for (i = 0; i < lineCount; i++) {
#ifdef VERSION_GCCJGC
        if (useDynamic != 0) {
            text = s_DynamicMessStr + i * 0x80;
        } else {
            text = GetMenuStr(s_singleMenuStaticMessages[messageNo].textIds[i]);
        }
#else
        if (useDynamic == 0) {
            text = GetSingWinMessage(s_singleMenuStaticMessages[messageNo].textIds[i], s_DynamicMessStr + i * 0x80, 0);
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
    int lineHeight = static_cast<int>(22.0f * FLOAT_8032ea78);
    if (22.0f * FLOAT_8032ea78 - static_cast<float>(lineHeight) > 0.0f) {
        lineHeight++;
    }
    int lineStep = lineHeight + 3;
    float yOffset = 4.0f;

    for (i = 0; i < lineCount; i++) {
        font->SetTlut((activeMask & (1 << i)) != 0 ? 7 : 8);

#ifdef VERSION_GCCJGC
        if (useDynamic != 0) {
            text = s_DynamicMessStr + i * 0x80;
        } else {
            text = GetMenuStr(s_singleMenuStaticMessages[messageNo].textIds[i]);
        }
#else
        if (useDynamic == 0) {
            text = GetSingWinMessage(s_singleMenuStaticMessages[messageNo].textIds[i], s_DynamicMessStr + i * 0x80, 0);
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

    font = m_fonts[0];
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
    font->SetScale(FLOAT_8032ea78);

    maxWidth = 0;
    if (useDynamic != 0) {
        lineCount = s_DynamicMess[0];
    } else {
        lineCount = s_singleMenuStaticMessages[messageNo].lineCount;
    }
    for (i = 0; i < lineCount; i++) {
        const char* text;
#ifdef VERSION_GCCJGC
        if (useDynamic != 0) {
            text = s_DynamicMessStr + i * 0x80;
        } else {
            text = GetMenuStr(s_singleMenuStaticMessages[messageNo].textIds[i]);
        }
#else
        if (useDynamic == 0) {
            text = GetSingWinMessage(s_singleMenuStaticMessages[messageNo].textIds[i], s_DynamicMessStr + i * 0x80, 0);
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

    int lineHeight = static_cast<int>(22.0f * FLOAT_8032ea78);
    if (22.0f * FLOAT_8032ea78 - static_cast<float>(lineHeight) > 0.0f) {
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

extern "C" {
int s_DynamicMess[5];
}
char s_DynamicMessStr[0x400];

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
    FLOAT_8032ea78 = scale;
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
    return FLOAT_8032ea78;
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
    float scaled = 22.0f * FLOAT_8032ea78;
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
    CCaravanWork* caravanWork = SingleCaravanWork();
    int flags = reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2])[itemNo].m_equipFlags;
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
    u16 flags = reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2])[itemNo].m_equipFlags;
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
            System.Printf(s_pcts_pctd_item_pctd_m_equip_pct08x_801DE8B0, s_singmenu_cpp, SINGMENU_LINE(0xD3D, 0xD38, 0xCAE), itemNo, flags);
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
    SItemFlatRow* rec = &reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2])[itemNo];
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

    const SItemFlatRow* itemBase = &reinterpret_cast<SItemFlatRow*>(Game.unkCFlatData0[2])[itemNo];

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
    raceBits = reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2])[itemNo].m_equipFlags;
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
        strcpy(outText, " ");
    }
    if (genderMask == 0) {
        return;
    }

    strcat(outText, GetMenuStr(((genderMask >> 5) & 1) + 17));
#else
    unsigned short raceBits;
    int raceType;
    char* text;
    char* suffix;

    GetItemType(itemNo, 1);
    raceBits = reinterpret_cast<const SItemFlatRow*>(Game.unkCFlatData0[2])[itemNo].m_equipFlags;
    int raceLow = raceBits & 0xF;
    int genderMask = raceBits & 0x30;
    outText[0] = '\0';

    if (raceLow == 0xF) {
        switch (Game.m_gameWork.m_languageId) {
        case 2:
            text = (char*)s_MenuStr_ge[19];
            break;
        case 3:
            text = (char*)s_MenuStr_it[19];
            break;
        case 4:
            text = (char*)s_MenuStr_fr[19];
            break;
        case 5:
            text = (char*)s_MenuStr_sp[19];
            break;
        case 1:
        default:
            text = (char*)s_MenuStr_us[19];
            break;
        }
        strcpy(outText, text);
        return;
    }

    for (raceType = 0; raceType < 4; raceType++) {
        if ((raceLow & (1 << raceType)) != 0) {
            break;
        }
    }

    if (raceType < 4) {
        switch (Game.m_gameWork.m_languageId) {
        case 2:
            text = (char*)s_TribeStr_ge[raceType];
            break;
        case 3:
            text = (char*)s_TribeStr_it[raceType];
            break;
        case 4:
            text = (char*)s_TribeStr_fr[raceType];
            break;
        case 5:
            text = (char*)s_TribeStr_sp[raceType];
            break;
        case 1:
        default:
            text = (char*)s_TribeStr_us[raceType];
            break;
        }

        strcpy(outText, text);
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
    switch (Game.m_gameWork.m_languageId) {
    case 2:
        suffix = (char*)s_MenuStr_ge[raceType + 17];
        break;
    case 3:
        suffix = (char*)s_MenuStr_it[raceType + 17];
        break;
    case 4:
        suffix = (char*)s_MenuStr_fr[raceType + 17];
        break;
    case 5:
        suffix = (char*)s_MenuStr_sp[raceType + 17];
        break;
    case 1:
    default:
        suffix = (char*)s_MenuStr_us[raceType + 17];
        break;
    }
    strcat(outText, suffix);
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
    int tex;
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    _GXColor color;
    color.r = 0xFF;
    color.g = 0xFF;
    color.b = 0xFF;
    color.a = static_cast<unsigned char>(255.0f * alpha);
    GXSetChanMatColor(GX_COLOR0A0, color);

    MenuPcs.SetTexture(SingMenuTex(0x53));
    MenuPcs.DrawRect(0, static_cast<float>(x), static_cast<float>(y), 16.0f,
                                    24.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);
    MenuPcs.DrawRect(8, static_cast<float>(x + 0x60), static_cast<float>(y), 16.0f,
                                    24.0f, 0.0f, 0.0f,
                                    1.0f, 1.0f, 0.0f);

    MenuPcs.SetTexture(SingMenuTex(0x54));
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
    int barX = x + 0x10;
    int barY = y + 8;
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
    int* lifeTimer = &m_singleLifeTimer;
    if (*lifeTimer >= 0) {
        ++(*lifeTimer);
        if (*lifeTimer > 0x31) {
            *lifeTimer = -1;
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
    const CCaravanWork* const caravanWork = SingleCaravanWork();
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

/*
 * --INFO--
 * PAL Address: 0x80145674
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
/*
 * --INFO--
 * PAL Address: 0x801453f4
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#ifndef VERSION_GCCJGC
int CMenuPcs::GetItemIcon(int index)
{
    return gSingMenuItemIconByType[index];
}
#endif

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
    const CCaravanWork* caravanWork = SingleCaravanWork();
    itemId = useRawItemId != 0 ? itemId : static_cast<int>(caravanWork->m_inventoryItems[itemId]);

    if (itemId <= 0) {
        return 0;
    }
    if (itemId <= 0x9E) {
        return 1;
    }
    if (itemId <= 0xFF) {
        return 2;
    }
    if (itemId <= 0x124) {
        return 3;
    }
    if (itemId == 0x125) {
        return 4;
    }
    if (itemId <= 0x129) {
        return 5;
    }
    if (itemId <= 0x17C) {
        return 6;
    }
    if (itemId <= 0x17C) {
        return 6;
    }
    if (itemId <= 0x188) {
        return 7;
    }
    if (itemId < 0x191) {
        return 8;
    }
    if (itemId >= 0x191) {
        return 9;
    }
    return 9;
}
