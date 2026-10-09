#include "ffcc/ptrarray.h"
#include "ffcc/p_menu.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/menu.h"
#include "ffcc/mesmenu.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/pad.h"
#include "ffcc/ref.h"
#include "ffcc/ringmenu.h"

#include "ffcc/textureman.h"
#include "ffcc/fontman.h"

#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CMenuPcs MenuPcs ATTRIBUTE_ALIGN(32);

struct MenuGbaLinkPool
{
    char gbaDir[12];
    char gbaClient[16];
    char gbaObjData[12];
#ifdef VERSION_GCCJGC
    char gbaIcon[20];
#else
    char gbaIcon[12];
#endif
    char gameTitle[24];
};

static const MenuGbaLinkPool sMenuGbaLinkStrings = {
#ifdef VERSION_GCCJGC
    "dvd/gba/", "ffcc_cli.bin", "objdat.spt", "dvd/menu/icon.dat", "\xCC\xA7\xB2\xC5\xD9\xCC\xA7\xDD\xC0\xBC\xDE\xB0\xA5\xB8\xD8\xBD\xC0\xD9\xB8\xDB\xC6\xB8\xD9"
#else
    "dvd/gba/", "ffcc_cli.bin", "objdat.spt", "icon.dat", "FF Crystal Chronicles"
#endif
};

extern const char sCMenuPcsProcessName[] = "CMenuPcs";

struct MenuFontTlutPalette
{
    _GXColor shadow;
    _GXColor highlight;
};

STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuStageActive) == 0x859);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuInitialized) == 0x85A);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuTextureLoadIndex) == 0x85C);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuTextureLoadState) == 0x860);

static const char sMenuTexWinKazari[] = "win_kazari";
extern const char sMenuManagerClassName[] = "CManager";
extern const char sMenuProcessClassName[] = "CProcess";
#ifdef VERSION_GCCJGC
static const char sMenuTexturePathFmt[] = "dvd/menu/%s.tex";
#else
static const char sMenuTexturePathFmt[] = "dvd/%smenu/%s.tex";
#endif
extern "C" const char s_p_menu_cpp[] = "p_menu.cpp";
#ifdef VERSION_GCCJGC
static const char sMenuGc23FontPathFmt[] = "dvd/menu/gc23.fnt";
#else
static const char sMenuGc23FontPathFmt[] = "dvd/%smenu/gc23.fnt";
#endif
#ifdef VERSION_GCCJGC
static const char sMenuFontPathFmt[] = "dvd/menu/%s.fnt";
#else
static const char sMenuFontPathFmt[] = "dvd/%smenu/%s.fnt";
#endif
#ifdef VERSION_GCCJGC
static const char sMenuGc22FontPathFmt[] = "dvd/menu/gc22.fnt";
#else
static const char sMenuGc22FontPathFmt[] = "dvd/%smenu/gc22.fnt";
#endif
static const char sMenuCommonName[] = "common";
static const char sMenuWinName[] = "win";
static const char sMenuTexKasoru[] = "kasoru";
static const char sMenuTexPause[] = "pause";
static const char sMenuTexWin1_0[] = "win1_0";
static const char sMenuTexWin1_1[] = "win1_1";
static const char sMenuTexWin1_2[] = "win1_2";
static const char sMenuTexWin1_3[] = "win1_3";
static const char sMenuTexWin1_4[] = "win1_4";
static const char sMenuTexWin1_5[] = "win1_5";
static const char sMenuTexWin1_6[] = "win1_6";
static const char sMenuTexWin1_7[] = "win1_7";
static const char sMenuTexWin1_8[] = "win1_8";
static const char sMenuTexWin2_0[] = "win2_0";
static const char sMenuTexWin2_1[] = "win2_1";
static const char sMenuTexWin2_2[] = "win2_2";
static const char sMenuTexWin2_3[] = "win2_3";
static const char sMenuTexWin2_4[] = "win2_4";
static const char sMenuTexWin2_5[] = "win2_5";
static const char sMenuTexWin2_6[] = "win2_6";
static const char sMenuTexWin2_7[] = "win2_7";
static const char sMenuTexWin2_8[] = "win2_8";
#ifndef VERSION_GCCJGC
static const char sMenuTexButton[] = "button";
#endif
static const char sMenuRegionShibuya[] = "shibuya";
static const char sMenuRegionFace[] = "face";
static const char sMenuTexBattle[] = "battle";
static const char sMenuTexHeart[] = "heart";
static const char sMenuTexNavi[] = "navi";
static const char sMenuTexHp0[] = "hp0";
static const char sMenuTexHp1[] = "hp1";
static const char sMenuTexHp2[] = "hp2";
static const char sMenuTexSuna[] = "suna";
static const char sMenuTexGba[] = "gba";
static const char sMenuTexBattle2[] = "battle2";

CProcessCallbackTable CMenuPcs::m_table = {
    const_cast<char*>(sCMenuPcsProcessName),
    static_cast<CProcessCallback>(&CMenuPcs::create),
    static_cast<CProcessCallback>(&CMenuPcs::destroy),
    {
        {static_cast<CProcessCallback>(&CMenuPcs::calc), 0x1A, 0},
        {static_cast<CProcessCallback>(&CMenuPcs::draw), 0x49, 1},
        {reinterpret_cast<CProcessCallback>(&CMenuPcs::loadTextureAsync), 0x1A, 0x10},
        {static_cast<CProcessCallback>(&CMenuPcs::drawSingleMenu), 0x49, 0x11},
    },
};

enum
{
#ifdef VERSION_GCCJGC
    MenuCommonTextureCount = 21,
#else
    MenuCommonTextureCount = 22,
#endif
#ifdef VERSION_GCCJGC
    MenuFontAllocationLine = 0xF4,
    MenuTextureAllocationLine = 0x17C,
    MenuDrawDoneLine = 0x1AA,
    MenuMessageAllocationLine = 0x485,
    MenuRingAllocationLine = 0x48C,
#else
    MenuFontAllocationLine = 0xF8,
    MenuTextureAllocationLine = 0x182,
    MenuDrawDoneLine = 0x1B0,
    MenuMessageAllocationLine = 0x48B,
    MenuRingAllocationLine = 0x492,
#endif
    MenuBattleTextureStart = MenuCommonTextureCount,
    MenuFaceTexture = MenuBattleTextureStart + 2
};

static inline void ReleaseRefObject(void* object)
{
    CRef* ref = reinterpret_cast<CRef*>(object);
    if (ref->DecRef() == 0) {
        delete ref;
    }
}

static inline void ReleaseRefSlot(void** slot)
{
    if (*slot != nullptr) {
        ReleaseRefObject(*slot);
        *slot = nullptr;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80097760
 * PAL Size: 120b
 * EN Address: 0x800AA7C4
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMenuPcs::~CMenuPcs()
{
}

/*
 * --INFO--
 * PAL Address: 0x800974a8
 * PAL Size: 368b
 * EN Address: 0x80096E44
 * EN Size: 368b
 * JP Address: 0x800969B4
 * JP Size: 376b
 */
void CMenuPcs::Init()
{
    f32 one;

    m_menuStage = 0;
    m_stageF0 = 0;
    m_stageF4 = 0;
    memset(m_fonts, 0, sizeof(m_fonts));
    memset(m_textureSets, 0, sizeof(m_textureSets));
    memset(m_textures, 0, sizeof(m_textures));
    memset(reinterpret_cast<u8*>(this) + 0x04, 0, 0x1C);

    m_singleMenuStageActive = 0;
    m_menuResultCode = 0;
    m_cmakeVillageWork = 0;
    m_artiList = 0;
    m_battleStateFlag = 0;

    WmInit();
    BonusInit();

    m_optionIndex = 0;
    one = 0.0f;
    m_gameInitMode = 0;
    m_stereoMode = 0;
    m_bgmVolume = 6;
    m_seVolume = 6;
    m_leftHintTimer = 0;
    m_rightHintTimer = 0;
    m_optionMenuState = 0;
    m_optionOpenAnim = one;
    m_pad9D[0] = 0;
    m_optionAnimPhase = 0;
    m_optionRowAnim = one;
    m_optionColumnAnim = one;
    m_optionAnimCounter = 0;
    m_specialModeFlags[0] = 0;
    m_specialModeFlags[1] = 0;
    m_specialModeFlags[2] = 0;
    m_specialModeFlags[3] = 0;
    m_wmOptionTextureSet = 0;
    for (int workIndex = 0; workIndex < 11; workIndex++) {
        m_wmOptionTextures[workIndex] = 0;
    }

    m_shopMenu = 0;
    m_pad87C = 1;
    m_cmakeWorkActive = 0;
    m_cmakeWorkCardChannel = 0;
    m_pad88A = 0;
    m_pad884 = 0;
    m_pad880 = 0;
    m_cmakeWork = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800974a4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::Quit()
{
	return;
}

/*
 * --INFO--
 * PAL Address: 0x80097490
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&m_table + index);
}

/*
 * --INFO--
 * PAL Address: 0x80097240
 * PAL Size: 592b
 * EN Address: 0x80096BDC
 * EN Size: 592b
 * JP Address: 0x80096780
 * JP Size: 540b
 */
void CMenuPcs::create()
{
    char fontPath[0x80];
    static char* tName[] = { const_cast<char*>(sMenuCommonName), const_cast<char*>(sMenuWinName) };
    static CMenuPcs::CTmp tTmp[] = {
        { 0, const_cast<char*>(sMenuTexKasoru) },
        { 0, const_cast<char*>(sMenuTexPause) },
        { 1, const_cast<char*>(sMenuTexWin1_0) },
        { 1, const_cast<char*>(sMenuTexWin1_1) },
        { 1, const_cast<char*>(sMenuTexWin1_2) },
        { 1, const_cast<char*>(sMenuTexWin1_3) },
        { 1, const_cast<char*>(sMenuTexWin1_4) },
        { 1, const_cast<char*>(sMenuTexWin1_5) },
        { 1, const_cast<char*>(sMenuTexWin1_6) },
        { 1, const_cast<char*>(sMenuTexWin1_7) },
        { 1, const_cast<char*>(sMenuTexWin1_8) },
        { 1, const_cast<char*>(sMenuTexWin2_0) },
        { 1, const_cast<char*>(sMenuTexWin2_1) },
        { 1, const_cast<char*>(sMenuTexWin2_2) },
        { 1, const_cast<char*>(sMenuTexWin2_3) },
        { 1, const_cast<char*>(sMenuTexWin2_4) },
        { 1, const_cast<char*>(sMenuTexWin2_5) },
        { 1, const_cast<char*>(sMenuTexWin2_6) },
        { 1, const_cast<char*>(sMenuTexWin2_7) },
        { 1, const_cast<char*>(sMenuTexWin2_8) },
        { 1, const_cast<char*>(sMenuTexWinKazari) },
#ifndef VERSION_GCCJGC
        { 0, const_cast<char*>(sMenuTexButton) }
#endif
    };

#ifdef VERSION_GCCJGC
    unsigned long menuHeapSize = 0xE4000;
#else
    unsigned long menuHeapSize = 0xC4000;
#endif
    if (FontMan.m_font != 0) {
        menuHeapSize -= FontMan.GetInternal22Size();
    }

    m_menuStage = Memory.CreateStage(menuHeapSize, const_cast<char*>(sCMenuPcsProcessName), 0);
    m_mode = -1;

    memset(m_textureSets, 0, sizeof(m_textureSets));
    memset(m_textures, 0, sizeof(m_textures));

#ifdef VERSION_GCCJGC
    loadFont(0, const_cast<char*>(sMenuGc22FontPathFmt), 0, 0);
#else
    sprintf(fontPath, const_cast<char*>(sMenuGc22FontPathFmt), Game.GetLangString());
    loadFont(0, fontPath, 0, 0);
#endif

    loadTexture(tName, 0, 2, tTmp, 0, MenuCommonTextureCount, 0);

    changeMode(static_cast<CMenuPcs::MENUMODE>(0));
}

/*
 * --INFO--
 * PAL Address: 0x800970e0
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::destroy()
{
    changeMode(static_cast<CMenuPcs::MENUMODE>(-1));

    freeTexture(0, 2, 0, MenuCommonTextureCount);

    CFont* font = m_fonts[0];
    if (font != nullptr) {
        if (font->DecRef() == 0) {
            delete font;
        }
        m_fonts[0] = 0;
    }

    Memory.DestroyStage(m_menuStage);
    if (m_singleMenuStageActive != 0) {
        m_stageF0 = 0;
        m_singleMenuStageActive = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80096d98
 * PAL Size: 840b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma push
#pragma pool_data off
void CMenuPcs::loadFont(int type, char* path, int slot, int tlutMode)
{
    CMemory::CStage* stage = 0;

    switch (type) {
    case 0:
        stage = m_menuStage;
        break;
    case 2:
        stage = PartMng.m_pppEnvSt.m_stagePtr;
        break;
    case 1:
        stage = m_stageF0;
        break;
    }

    if ((slot == 0) && FontMan.IsInternal22()) {
        m_fonts[0] = FontMan.GetInternal22();
        m_fonts[0]->AddRef();
    } else {
        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        m_fonts[slot] = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), MenuFontAllocationLine) CFont;
        m_fonts[slot]->Create(File.m_readBuffer, stage);

        File.Close(fileHandle);
    }

    if (tlutMode < 2) {
        static u8 color[] = {
            0xFF, 0xF5, 0xF5, 0xF5, 0xF5, 0xF5, 0xF5, 0xF5, 0xBD, 0xA8, 0x92, 0x7B, 0x39, 0x22, 0x00, 0x00
        };
        static u8 alpha1[] = {
            0x00, 0x0A, 0x1E, 0x32, 0x46, 0x64, 0xD2, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
        };
        static u8 alpha2[] = {
            0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0A, 0x1E, 0x32, 0x46, 0x78, 0xB9, 0xDC, 0xFF
        };
        static MenuFontTlutPalette pal[] = {
            {{0x00, 0x00, 0x00, 0xFF}, {0x7C, 0x78, 0x86, 0xFF}},
            {{0x99, 0xB7, 0xE2, 0xFF}, {0x03, 0x0C, 0x44, 0xFF}},
            {{0xF7, 0x7F, 0x37, 0xFF}, {0x44, 0x19, 0x00, 0xFF}},
            {{0xE3, 0xB4, 0xEF, 0xFF}, {0x48, 0x01, 0x48, 0xFF}},
            {{0xB4, 0xE4, 0x84, 0xFF}, {0x00, 0x3B, 0x06, 0xFF}},
            {{0xA8, 0xFB, 0xFA, 0xFF}, {0x01, 0x2F, 0x5E, 0xFF}},
            {{0xF6, 0xFA, 0x92, 0xFF}, {0x39, 0x1A, 0x05, 0xFF}},
            {{0xFD, 0xF9, 0xEE, 0xFF}, {0x18, 0x0A, 0x00, 0xFF}},
            {{0x9E, 0x9B, 0x9B, 0xFF}, {0x3E, 0x30, 0x27, 0xFF}},
            {{0xFD, 0xBE, 0x7B, 0xFF}, {0x67, 0x2A, 0x00, 0xFF}},
            {{0xFE, 0xFE, 0xFE, 0xFF}, {0x20, 0x20, 0x20, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0xE1, 0xFA, 0xD7, 0xFF}, {0x2A, 0x3C, 0x13, 0xFF}},
            {{0xFC, 0xF8, 0xD1, 0xFF}, {0x3F, 0x39, 0x21, 0xFF}},
            {{0xFF, 0xFF, 0xFF, 0xFF}, {0x25, 0x1C, 0x14, 0xFF}},
            {{0xF5, 0xEF, 0xAC, 0xFF}, {0x65, 0x48, 0x08, 0xFF}},
            {{0x00, 0x00, 0x00, 0x20}, {0x00, 0x00, 0x00, 0x20}},
            {{0x70, 0x4E, 0x05, 0x20}, {0x00, 0x00, 0x00, 0x20}},
            {{0xFD, 0xDA, 0xC8, 0xFF}, {0x5C, 0x3F, 0x00, 0xFF}},
            {{0x83, 0xE8, 0xFA, 0xFF}, {0x5C, 0x3F, 0x00, 0xFF}},
            {{0xF7, 0xF3, 0xDA, 0xFF}, {0x39, 0x1A, 0x05, 0xFF}},
            {{0x8D, 0xFF, 0xFB, 0xFF}, {0x5C, 0x3F, 0x00, 0xFF}},
            {{0xF5, 0xDE, 0x3D, 0xFF}, {0x5C, 0x3F, 0x00, 0xFF}},
            {{0xF8, 0xEE, 0xC3, 0xFF}, {0x5C, 0x3F, 0x00, 0xFF}},
            {{0xCD, 0xCD, 0xCD, 0xFF}, {0x5C, 0x3F, 0x00, 0xFF}},
            {{0xF8, 0xAB, 0xAB, 0xFF}, {0x9B, 0x00, 0x00, 0xFF}},
            {{0xFF, 0xFF, 0xFF, 0xFF}, {0x5C, 0x3F, 0x00, 0xFF}},
            {{0x7C, 0x78, 0x86, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x99, 0xB7, 0xE2, 0xFF}, {0x03, 0x0C, 0x44, 0xFF}},
            {{0xF0, 0x65, 0x12, 0xFF}, {0x3D, 0x27, 0x1A, 0xFF}},
            {{0xF5, 0xF5, 0xF5, 0xFF}, {0x32, 0x05, 0x32, 0xFF}},
#ifdef VERSION_GCCJGC
            {{0xB4, 0xE4, 0x84, 0xFF}, {0x00, 0x3B, 0x06, 0xFF}},
            {{0xA8, 0xFB, 0xFA, 0xFF}, {0x01, 0x2F, 0x5E, 0xFF}},
#else
            {{0xB4, 0xD2, 0x84, 0xFF}, {0x00, 0x3B, 0x06, 0xFF}},
            {{0xA8, 0xFB, 0x00, 0xFF}, {0x01, 0x2F, 0x5E, 0xFF}},
#endif
#if defined(VERSION_GCCE01) || defined(VERSION_GCCJGC)
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
#else
            {{0xA8, 0xFB, 0xFA, 0xFF}, {0x01, 0x2F, 0x5E, 0xFF}},
#endif
            {{0xF5, 0xF5, 0xF5, 0xFF}, {0x05, 0x32, 0x25, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0xFE, 0xFE, 0xFE, 0xFF}, {0x20, 0x20, 0x20, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0xE1, 0xFA, 0xD7, 0xFF}, {0x2A, 0x3C, 0x13, 0xFF}},
            {{0xFC, 0xF8, 0xD1, 0xFF}, {0x3F, 0x39, 0x21, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}},
            {{0x00, 0x00, 0x00, 0xFF}, {0x00, 0x00, 0x00, 0xFF}}
        };

        for (int colorIndex = 0; colorIndex < 0x10; colorIndex++) {
            MenuFontTlutPalette* palette = &pal[tlutMode * 0x1C];

            for (int tlutIndex = 0; tlutIndex < 0x1C; tlutIndex++) {
                float blend = 0.0f;
                float blendInv = 0.0f;
                _GXColor tlutColor;
                tlutColor.r = static_cast<u8>(0xFF - color[colorIndex]);
                tlutColor.g = static_cast<u8>(0xFF - color[colorIndex]);
                tlutColor.b = static_cast<u8>(0xFF - color[colorIndex]);
                tlutColor.a = alpha1[colorIndex];

                if (colorIndex < 8) {
                    tlutColor.r = palette[tlutIndex].highlight.r;
                    tlutColor.g = palette[tlutIndex].highlight.g;
                    tlutColor.b = palette[tlutIndex].highlight.b;
                } else {
                    blend = 1.0f - static_cast<float>(colorIndex - 8) / 8.0f;
                    blendInv = 1.0f - blend;
                    tlutColor.r = static_cast<u8>(static_cast<float>(palette[tlutIndex].highlight.r) * blend +
                                                  static_cast<float>(palette[tlutIndex].shadow.r) * blendInv);
                    tlutColor.g = static_cast<u8>(static_cast<float>(palette[tlutIndex].highlight.g) * blend +
                                                  static_cast<float>(palette[tlutIndex].shadow.g) * blendInv);
                    tlutColor.b = static_cast<u8>(static_cast<float>(palette[tlutIndex].highlight.b) * blend +
                                                  static_cast<float>(palette[tlutIndex].shadow.b) * blendInv);
                }

                m_fonts[slot]->SetTlutColor(tlutIndex, colorIndex, tlutColor);

                tlutColor.a = alpha2[colorIndex];
                m_fonts[slot]->SetTlutColor(tlutIndex + 0x1C, colorIndex, tlutColor);
            }
        }

        m_fonts[slot]->FlushTlutColor();
    }
}

#pragma pop

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x80061B80
 * EN Size: 104b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CMemory::CStage* CMenuPcs::GetStage(int stageSelect)
{
    if (stageSelect == 3) {
        return MapMng.m_stage;
    }
    if ((Game.m_gameWork.m_menuStageMode != 0) && (stageSelect != 0)) {
        if (stageSelect == 1) {
            return m_stageF0;
        }
        return m_stageF4;
    }
    return m_menuStage;
}

/*
 * --INFO--
 * PAL Address: 0x80096b94
 * PAL Size: 516b
 * EN Address: 0x80096530
 * EN Size: 516b
 * JP Address: 0x800960E0
 * JP Size: 504b
 */
void CMenuPcs::loadTexture(char** paths, int textureSetStart, int textureSetCount, CMenuPcs::CTmp* tmp,
                           int textureStart, int textureCount, int stageSelect)
{
    char texPath[0x100];

    for (int i = 0; i < textureSetCount; i++) {
#ifdef VERSION_GCCJGC
        sprintf(texPath, const_cast<char*>(sMenuTexturePathFmt), paths[i]);
#else
        sprintf(texPath, const_cast<char*>(sMenuTexturePathFmt), Game.GetLangString(), paths[i]);
#endif

        CFile::CHandle* fileHandle = File.Open(texPath, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            CMemory::CStage* stage = (m_mode == 1) ? MapMng.m_stage : GetStage(stageSelect);

            m_textureSets[i + textureSetStart] =
                new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), MenuTextureAllocationLine) CTextureSet;

            m_textureSets[i + textureSetStart]->Create(File.m_readBuffer, stage, 0, 0, 0, 0);

            File.Close(fileHandle);
        }
    }

    for (int i = 0; i < textureCount; i++) {
        const unsigned long textureIndex = static_cast<unsigned long>(
            m_textureSets[tmp[i].m_textureSetIndex]->Find(tmp[i].m_textureName));
        CTexture* texture = m_textureSets[tmp[i].m_textureSetIndex]->GetTexture(textureIndex);
        texture->AddRef();
        m_textures[i + textureStart] = texture;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80096a9c
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::freeTexture(int textureSetStart, int textureSetCount, int textureStart, int textureCount)
{
    for (int i = 0; i < textureCount; i++) {
        CTexture* texture = m_textures[i + textureStart];
        if (texture != nullptr) {
            if (texture->DecRef() == 0) {
                delete texture;
            }
            m_textures[i + textureStart] = 0;
        }
    }

    for (int i = 0; i < textureSetCount; i++) {
        CTextureSet* textureSet = m_textureSets[i + textureSetStart];
        if (textureSet != nullptr) {
            if (textureSet->DecRef() == 0) {
                delete textureSet;
            }
            m_textureSets[i + textureSetStart] = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80096800
 * PAL Size: 668b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::changeMode(CMenuPcs::MENUMODE mode)
{
    int currentMode;
    int i;

    if (m_mode != static_cast<int>(mode)) {
        Graphic._WaitDrawDone(const_cast<char*>(s_p_menu_cpp), MenuDrawDoneLine);
        currentMode = m_mode;
        switch (currentMode) {
        case -1:
            break;
        case 0:
            ReleaseRefSlot(reinterpret_cast<void**>(&m_fonts[1]));
            freeTexture(2, 2, MenuBattleTextureStart, 10);

            for (i = 0; i < 4; i++) {
                ReleaseRefSlot(reinterpret_cast<void**>(&m_battleRingMenus[i]));
            }

            for (i = 0; i < 12; i++) {
                ReleaseRefSlot(reinterpret_cast<void**>(&m_battleMesMenus[i]));
            }

            destroySingleMenu();
            destroyVillageMenu();
            break;
        case 1:
            destroyWorld();
            break;
        case 2:
            destroyBonus();
            break;
        }

        m_mode = static_cast<int>(mode);
        currentMode = m_mode;
        switch (currentMode) {
        case -1:
            break;
        case 0:
            createBattle();
            createSingleMenu();
            break;
        case 1:
            createWorld();
            break;
        case 2:
            createBonus();
            break;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800966e8
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::calc()
{
    switch (m_mode) {
        case 0:
            calcBattle();
            break;
        case 1:
            CalcDiaryMenu();
            break;
        case 2:
            calcBonus();
            break;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009631c
 * PAL Size: 972b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::draw()
{
    DrawInit();

    switch (m_mode) {
    case 0:
        drawBattle();
        drawVillageMenu();
        break;
    case 1:
        drawWorld();
        break;
    case 2:
        drawBonus();
        break;
    }

    drawPause();
    DrawQuit();
}

/*
 * --INFO--
 * PAL Address: 0x80096148
 * PAL Size: 468b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawInit()
{
    Mtx modelMtx;
    Mtx44 orthoMtx;

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, 0);
    C_MTXOrtho(orthoMtx, 0.0f, 448.0f, 0.0f,
               640.0f, 0.0f, -100.0f);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);

    GXSetChanAmbColor(GX_COLOR0A0, CColor(0xFF, 0xFF, 0xFF, 0xFF).color);

    GXSetZCompLoc(GX_FALSE);
    GXSetCurrentMtx(0);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
}

/*
 * --INFO--
 * PAL Address: 0x80095f58
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetAttrFmt(CMenuPcs::FMT fmt)
{
    GXClearVtxDesc();
    switch ((int)fmt) {
    case 0:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        break;
    case 1:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        break;
    case 2:
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
        break;
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: 0x800A82EC
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawQuit()
{
	Mtx44 screenMtx;

	PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
	GXSetProjection(screenMtx, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * PAL Address: 0x80095EE4
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
u16 CMenuPcs::GetButtonDown(int port)
{
    return Pad.GetButtonDown(port);
}

/*
 * --INFO--
 * PAL Address: 0x80095E70
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
u16 CMenuPcs::GetButtonRepeat(int port)
{
    return Pad.GetButtonRepeat(port);
}

/*
 * --INFO--
 * PAL Address: 0x80095d44
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::onScriptChanging(char* script)
{

    switch (m_mode) {
    case 0:
        for (int i = 0; i < 4; i++) {
            CMenu* menu = m_battleRingMenus[i];
            menu->ScriptChanging(script);
        }

        for (int i = 0; i < 12; i++) {
            CMenu* menu = m_battleMesMenus[i];
            menu->ScriptChanging(script);
        }
        break;
    }

    memset(&m_battleHud, 0, sizeof(m_battleHud));
    ReleaseRefSlot(reinterpret_cast<void**>(&m_fonts[2]));
    ReleaseRefSlot(reinterpret_cast<void**>(&m_fonts[3]));
}

/*
 * --INFO--
 * PAL Address: 0x80095CE0
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::onMapChanging(int mapNo, int)
{
    if (((mapNo == 0x21) && (Game.m_currentMapId != 0x21)) ||
        ((mapNo != 0x21) && (Game.m_currentMapId == 0x21))) {
        changeMode(static_cast<CMenuPcs::MENUMODE>(-1));
    }
}

/*
 * --INFO--
 * PAL Address: 0x80095CA4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::onMapChanged(int, int, int)
{
    changeMode(static_cast<CMenuPcs::MENUMODE>((Game.m_currentMapId == 0x21) ? 1 : 0));
}

/*
 * --INFO--
 * PAL Address: 0x80095bd0
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetTexture(CMenuPcs::TEX tex)
{
    CTexture* texture;
    Mtx texMtx;

    if ((int)tex == -1) {
        texture = 0;
    } else {
        u32 width;
        u32 height;

        texture = m_textures[(int)tex];
        TextureMan.SetTexture(GX_TEXMAP0, texture);

        width = *(u32*)((u8*)texture + 0x64);
        height = *(u32*)((u8*)texture + 0x68);
        PSMTXScale(texMtx, 1.0f / (f32)width, 1.0f / (f32)height, 1.0f);
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    }

    TextureMan.SetTextureTev(texture);
}

/*
 * --INFO--
 * PAL Address: 0x800958fc
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawRect(unsigned long attr, float x, float y, float w, float h, float u, float v, float us, float vs, float angle)
{
    if (w <= 0.0f || h <= 0.0f) {
        return;
    }
    {
        float u1;
        float v1;
        float x0;
        float y0;
        float x1;
        float y1;
        float scaledW;
        float scaledH;
        float z = 0.0f;

        if ((attr & 8) != 0) {
            u1 = u + 0.5f;
            u = (u + w) - 0.5f;
        } else {
            u1 = (u + w) - 0.5f;
            u += 0.5f;
        }

        if ((attr & 4) != 0) {
            v1 = v + 0.5f;
            v = (v1 + h) - 0.5f;
        } else {
            v1 = (v + h) - 0.5f;
            v += 0.5f;
        }

        scaledW = w * us;
        scaledH = h * vs;

        x0 = ((attr & 1) != 0) ? x - scaledW * 0.5f : x;
        y0 = ((attr & 2) != 0) ? y - scaledH * 0.5f : y;

        x1 = x0 + scaledW;
        y1 = y0 + scaledH;

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        if (0.0f != angle) {
            float s = static_cast<float>(sin(angle));
            float c = static_cast<float>(cos(angle));
            x0 -= x;
            y0 -= y;
            x1 -= x;
            y1 -= y;

            GXPosition3f32(x + x0 * c - y0 * s, y + x0 * s + y0 * c, z);
            GXTexCoord2f32(u, v);

            GXPosition3f32(x + x1 * c - y0 * s, y + x1 * s + y0 * c, z);
            GXTexCoord2f32(u1, v);

            GXPosition3f32(x + x0 * c - y1 * s, y + x0 * s + y1 * c, z);
            GXTexCoord2f32(u, v1);

            GXPosition3f32(x + x1 * c - y1 * s, y + x1 * s + y1 * c, z);
            GXTexCoord2f32(u1, v1);
        } else {
            GXPosition3f32(x0, y0, z);
            GXTexCoord2f32(u, v);

            GXPosition3f32(x1, y0, z);
            GXTexCoord2f32(u1, v);

            GXPosition3f32(x0, y1, z);
            GXTexCoord2f32(u, v1);

            GXPosition3f32(x1, y1, z);
            GXTexCoord2f32(u1, v1);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800955dc
 * PAL Size: 800b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawRect(unsigned long attr, float x, float y, float w, float h, float u, float v, _GXColor* colors, float us, float vs, float angle)
{
    if (w <= 0.0f || h <= 0.0f) {
        return;
    }
    {
        float u1;
        float v1;
        float x0;
        float y0;
        float x1;
        float y1;
        float scaledW;
        float scaledH;
        float z = 0.0f;

        if ((attr & 8) != 0) {
            u1 = u + 0.5f;
            u = (u + w) - 0.5f;
        } else {
            u1 = (u + w) - 0.5f;
            u += 0.5f;
        }

        if ((attr & 4) != 0) {
            v1 = v + 0.5f;
            v = (v1 + h) - 0.5f;
        } else {
            v1 = (v + h) - 0.5f;
            v += 0.5f;
        }

        scaledW = w * us;
        scaledH = h * vs;

        x0 = ((attr & 1) != 0) ? x - scaledW * 0.5f : x;
        y0 = ((attr & 2) != 0) ? y - scaledH * 0.5f : y;

        x1 = x0 + scaledW;
        y1 = y0 + scaledH;

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        if (0.0f != angle) {
            float s = static_cast<float>(sin(angle));
            float c = static_cast<float>(cos(angle));
            x0 -= x;
            y0 -= y;
            x1 -= x;
            y1 -= y;

            GXPosition3f32(x + x0 * c - y0 * s, y + x0 * s + y0 * c, z);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[0]));
            GXTexCoord2f32(u, v);

            GXPosition3f32(x + x1 * c - y0 * s, y + x1 * s + y0 * c, z);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[1]));
            GXTexCoord2f32(u1, v);

            GXPosition3f32(x + x0 * c - y1 * s, y + x0 * s + y1 * c, z);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[2]));
            GXTexCoord2f32(u, v1);

            GXPosition3f32(x + x1 * c - y1 * s, y + x1 * s + y1 * c, z);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[3]));
            GXTexCoord2f32(u1, v1);
        } else {
            GXPosition3f32(x0, y0, z);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[0]));
            GXTexCoord2f32(u, v);

            GXPosition3f32(x1, y0, z);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[1]));
            GXTexCoord2f32(u1, v);

            GXPosition3f32(x0, y1, z);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[2]));
            GXTexCoord2f32(u, v1);

            GXPosition3f32(x1, y1, z);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[3]));
            GXTexCoord2f32(u1, v1);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 880b
 * EN Address: 0x800A8E3C
 * EN Size: 424b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::DrawBar(float x, float y, float width, CMenuPcs::TEX texBase, float height)
{
    float capW = 8.0f;

    if (width <= 0.0f) {
        return;
    }

    float midW = width - capW * 2.0f;
    midW = (midW < 0.0f) ? 0.0f : midW;

    SetTexture(texBase);
    DrawRect(0, x, y, capW, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    SetTexture(static_cast<TEX>(texBase + 1));
    DrawRect(0, x + capW, y, midW, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
    SetTexture(static_cast<TEX>(texBase + 2));
    DrawRect(0, (x + width) - capW, y, capW, height, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x80094bec
 * PAL Size: 2544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawWindow(float x, float y, float width, float height, CMenuPcs::TEX texBase, float corner)
{
	if (width <= 0.0f || height <= 0.0f) {
		return;
	}

	const float twoCorner = corner * 2.0f;
	float midW = (width - twoCorner < 0.0f) ? 0.0f : width - twoCorner;
	float midH = (height - twoCorner < 0.0f) ? 0.0f : height - twoCorner;
	float uOff = (twoCorner - width < 0.0f) ? 0.0f : twoCorner - width;
	uOff *= 0.5f;
	float vOff = (twoCorner - height < 0.0f) ? 0.0f : twoCorner - height;
	vOff *= 0.5f;
	const int tex = static_cast<int>(texBase);

	SetTexture(static_cast<CMenuPcs::TEX>(tex));
	const float cornerW = corner - uOff;
	const float cornerH = corner - vOff;
	DrawRect(0, x, y, cornerW, cornerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 1));
	DrawRect(0, x + corner, y, midW, cornerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 2));
	DrawRect(0, ((x + width) - corner) + uOff, y, cornerW, cornerH, uOff, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 3));
	DrawRect(0, x, y + corner, corner, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 4));
	DrawRect(0, x + corner, y + corner, midW, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 5));
	DrawRect(0, (x + width) - corner, y + corner, corner, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 6));
	DrawRect(0, x, ((y + height) - corner) + vOff, cornerW, cornerH, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 7));
	DrawRect(0, x + corner, ((y + height) - corner) + vOff, midW, cornerH, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 8));
	DrawRect(0, ((x + width) - corner) + uOff, ((y + height) - corner) + vOff, cornerW, cornerH, uOff, vOff, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x8009ba1c
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetColor(CColor& color)
{
    GXSetChanMatColor(GX_COLOR0A0, color.color);
}

/*
 * --INFO--
 * PAL Address: 0x80094aec
 * PAL Size: 208b
 * EN Address: 0x80094488
 * EN Size: 208b
 * JP Address: 0x80093FEC
 * JP Size: 192b
 */
void CMenuPcs::LoadExtraFont(int fontNo, char* fileName)
{
    char path[0x108];
    CFont* font = m_fonts[fontNo + 2];

    if (font != 0) {
        if (font->DecRef() == 0) {
            delete font;
        }
        m_fonts[fontNo + 2] = 0;
    }

#ifdef VERSION_GCCJGC
    sprintf(path, const_cast<char*>(sMenuFontPathFmt), fileName);
#else
    sprintf(path, const_cast<char*>(sMenuFontPathFmt), Game.GetLangString(), fileName);
#endif
    loadFont(2, path, fontNo + 2, -1);
}

/*
 * --INFO--
 * PAL Address: 0x8009497c
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::SetExtraFontTlut(int fontNo, _GXColor color)
{
    for (int i = 0; i < 0x10; i++) {
        _GXColor out = m_fonts[fontNo + 2]->GetDefaultTlutColor(i);

        if (i < 9) {
            out.r = color.r;
            out.g = color.g;
            out.b = color.b;
        } else {
            float blend = 1.0f - static_cast<float>(i - 9) / 7.0f;
            out.r = static_cast<u8>(-(static_cast<float>(0xF5 - color.r) * blend - 245.0f));
            out.g = static_cast<u8>(-(static_cast<float>(0xF5 - color.g) * blend - 245.0f));
            out.b = static_cast<u8>(-(static_cast<float>(0xF5 - color.b) * blend - 245.0f));
        }

        m_fonts[fontNo + 2]->SetDefaultTlutColor(i, out);
    }

    m_fonts[fontNo + 2]->FlushDefaultTlutColor();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 380b
 * EN Address: 0x800A97A8
 * EN Size: 240b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawPause()
{
    if (((CFlatEventFlags() & 0x10) == 0) || (System.m_scenegraphStepMode != 2)) {
        return;
    }

    SetTexture(static_cast<TEX>(1));
    CColor color(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * (0.5f * (1.0f + sinf(static_cast<int>(System.m_frameCounter) * 0.1f)))));
    SetColor(color);
    DrawRect(3, 320.0f, 224.0f, 120.0f, 56.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x8009460c
 * PAL Size: 880b
 * EN Address: 0x80093FA8
 * EN Size: 880b
 * JP Address: 0x80093B44
 * JP Size: 824b
 */
void CMenuPcs::createBattle()
{
    char fontPath[0x80];
    static char* tName[] = {
        const_cast<char*>(sMenuRegionShibuya), const_cast<char*>(sMenuRegionFace), 0, 0, 0, 0, 0, 0, 0
    };
    static CMenuPcs::CTmp tTmp[] = {
        { 2, const_cast<char*>(sMenuTexBattle) },
        { 2, const_cast<char*>(sMenuTexHeart) },
        { 3, const_cast<char*>(sMenuRegionFace) },
        { 2, const_cast<char*>(sMenuTexNavi) },
        { 2, const_cast<char*>(sMenuTexHp0) },
        { 2, const_cast<char*>(sMenuTexHp1) },
        { 2, const_cast<char*>(sMenuTexHp2) },
        { 2, const_cast<char*>(sMenuTexSuna) },
        { 2, const_cast<char*>(sMenuTexGba) },
        { 2, const_cast<char*>(sMenuTexBattle2) }
    };

    loadTexture(tName, 2, 2, tTmp, MenuBattleTextureStart, 10, 0);

    for (int i = 0; i < 12; i++) {
        CMesMenu* menu = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), MenuMessageAllocationLine) CMesMenu;
        m_battleMesMenus[i] = menu;
        m_battleMesMenus[i]->SetIndex(i);
        m_battleMesMenus[i]->Create();
    }

    for (int i = 0; i < 4; i++) {
        CRingMenu* menu = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), MenuRingAllocationLine) CRingMenu;
        m_battleRingMenus[i] = menu;
        m_battleRingMenus[i]->SetIndex(i);
        m_battleRingMenus[i]->Create();
    }

#ifdef VERSION_GCCJGC
    loadFont(0, const_cast<char*>(sMenuGc23FontPathFmt), 1, 1);
#else
    sprintf(fontPath, const_cast<char*>(sMenuGc23FontPathFmt), Game.GetLangString());
    loadFont(0, fontPath, 1, 1);
#endif

    for (int i = 0; i < 0x100; i++) {
        _GXColor color = GetTexture(static_cast<TEX>(MenuFaceTexture))->GetTlutColor(i);
        const int avg2 = (((int)color.r + (int)color.g + (int)color.b) / 3) * 2;
        color.r = static_cast<u8>(((int)color.r + avg2) / 3);
        color.g = static_cast<u8>(((int)color.g + avg2) / 3);
        color.b = static_cast<u8>(((int)color.b + avg2) / 3);

        const unsigned long tlutFmt = GetTexture(static_cast<TEX>(MenuFaceTexture))->m_format;
        int tlutOffset;
        if (tlutFmt == 9) {
            tlutOffset = 0x100;
        } else if (tlutFmt == 8) {
            tlutOffset = 0x10;
        } else {
            tlutOffset = 0;
        }

        CTexture::SetExternalTlutColor(m_externalFontTlut, tlutOffset, i, color);
    }

    GetTexture(static_cast<TEX>(MenuFaceTexture))->FlushExternalTlut(m_externalFontTlut);
    m_battleStateFlag = 0;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 480b
 * EN Address: 0x800A9B6C
 * EN Size: 252b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::destroyBattle()
{
    int i;

    for (i = 0; i < 10; i++) {
        ReleaseRefSlot(reinterpret_cast<void**>(m_textures + MenuBattleTextureStart + i));
    }

    for (i = 0; i < 2; i++) {
        ReleaseRefSlot(reinterpret_cast<void**>(m_textureSets + 2 + i));
    }

    for (i = 0; i < 4; i++) {
        ReleaseRefSlot(reinterpret_cast<void**>(&m_battleRingMenus[i]));
    }

    for (i = 0; i < 12; i++) {
        ReleaseRefSlot(reinterpret_cast<void**>(&m_battleMesMenus[i]));
    }

    destroySingleMenu();
    destroyVillageMenu();
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 216b
 * EN Address: 0x800A9C68
 * EN Size: 292b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMenuPcs::calcBattle()
{
    for (int i = 0; i < 4; i++) {
        m_battleRingMenus[i]->Calc();
    }

    for (int i = 0; i < 0xC; i++) {
        reinterpret_cast<CMenu*>(m_battleMesMenus[i])->Calc();
    }

    int value;
    int current;
    int limit;

    current = m_battleHud.m_gaugeValue;
    value = current - 1;
    limit = m_battleHud.m_gaugeTarget - current;
    limit = current + limit;
    m_battleHud.m_gaugeValue = (limit < value) ? value : ((++current < limit) ? current : limit);

    u32 counter = m_battleHud.m_fadeCounter - 1;
    m_battleHud.m_fadeCounter = counter & ~((int)counter >> 31);
    counter = m_battleHud.m_gaugeCounter - 1;
    m_battleHud.m_gaugeCounter = counter & ~((int)counter >> 31);

    calcVillageMenu();
}

/*
 * --INFO--
 * PAL Address: 0x80093ec4
 * PAL Size: 1864b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::drawBattle()
{
    if (m_battleHud.m_visible != 0) {
        const float frame = static_cast<float>(m_battleHud.m_fadeCounter);
        float fade = frame / 64.0f;
        if (m_battleHud.m_visible != 0) {
            fade = 1.0f - fade;
        }

        Mtx cameraMtx;
        Mtx44 viewMtx;
        Mtx44 screenMtx;
        Vec4d projected;
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        PSMTXCopy(cameraMtx, reinterpret_cast<MtxPtr>(viewMtx));
        viewMtx[3][2] = 0.0f;
        viewMtx[3][1] = 0.0f;
        viewMtx[3][0] = 0.0f;
        viewMtx[3][3] = 1.0f;
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        PSMTX44Concat(screenMtx, viewMtx, screenMtx);
        Math.MTX44MultVec4(screenMtx, reinterpret_cast<Vec*>(m_battleHud.m_worldPos), &projected);

        if (0.0f < projected.w) {
            float screenX = 320.0f + (320.0f * projected.x) / projected.w;
            float screenY = 224.0f - (224.0f * projected.y) / projected.w;
            const int totalWidth = static_cast<int>(static_cast<float>(m_battleHud.m_width) * fade);
            const int halfWidth = totalWidth / 2;

            const float markerX = (screenX < static_cast<float>(halfWidth))
                                      ? static_cast<float>(halfWidth)
                                      : ((static_cast<float>(0x280 - halfWidth) < screenX) ? static_cast<float>(0x280 - halfWidth) : screenX);

            const float markerY = (screenY < 16.0f)
                                      ? 16.0f
                                      : ((432.0f < screenY) ? 432.0f : screenY);

            const float left = markerX - static_cast<float>(halfWidth);
            const float bodyLeft = left + 8.0f;

            int fillWidth = ((totalWidth - 16) * m_battleHud.m_gaugeValue) / m_battleHud.m_gaugeMax;
            const CColor frameColor(0xFF, 0xFF, 0xFF, static_cast<u8>(255.0f * fade));
            GXSetChanMatColor(GX_COLOR0A0, frameColor.color);
#ifdef VERSION_GCCJGC
            MenuPcs.DrawBar(left, markerY, static_cast<float>(totalWidth), static_cast<CMenuPcs::TEX>(0x19), 8.0f);
#else
            MenuPcs.DrawBar(left, markerY, static_cast<float>(totalWidth), static_cast<CMenuPcs::TEX>(0x1A), 8.0f);
#endif

            const CColor fillTop(0xFF, (m_battleHud.m_gaugeCounter * 0xFF) / 16, (m_battleHud.m_gaugeCounter * 0xFF) / 16, static_cast<u8>(255.0f * fade));
            GXSetChanMatColor(GX_COLOR0A0, fillTop.color);
            TextureMan.SetTextureTev(0);
            DrawRect(0, bodyLeft, (markerY + 3.0f) - 1.0f, static_cast<float>(fillWidth), 4.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

            const CColor fillBottom(0xFF, ((m_battleHud.m_gaugeCounter * 0x7F) / 16) + 0x80, (m_battleHud.m_gaugeCounter * 0xFF) / 16, static_cast<u8>(255.0f * fade));
            GXSetChanMatColor(GX_COLOR0A0, fillBottom.color);
            DrawRect(0, bodyLeft, markerY + 3.0f, static_cast<float>(fillWidth), 2.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
    }

    for (int i = 0; i < 4; i++) {
        m_battleRingMenus[i]->Draw();
    }
    for (int i = 0; i < 12; i++) {
        reinterpret_cast<CMenu*>(m_battleMesMenus[i])->Draw();
    }
    for (int i = 0; i < 4; i++) {
        m_battleRingMenus[i]->DrawIcon();
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009ab8c
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ChgPlayModeFromScript(bool isScriptMode)
{
    const int mode = m_mode;

    if ((mode != 2) && (mode != 1)) {
        destroySingleMenu();
    }

    Game.m_gameWork.m_menuStageMode = static_cast<u8>(isScriptMode);
}

#pragma pool_data off
