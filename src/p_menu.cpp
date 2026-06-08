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
extern "C" {
extern const f32 kMenuFadeStep;
extern const f32 kMenuInitOne;
extern const f32 kMenuOrthoBottom;
extern const f32 kMenuOrthoRight;
extern const f32 kMenuOrthoFar;
extern const f32 kMenuOne;
extern const f32 kMenuScreenCenterX;
extern const f32 kMenuScreenCenterY;
extern const f32 kMenuMarkerMinY;
extern const f32 kMenuMarkerMaxY;
extern const f32 kMenuMarkerCapSize;
extern const f32 kMenuAlphaMax;
extern const f32 kMenuMarkerFillYOffset;
extern const f32 kMenuMarkerFillTopHeight;
extern const f32 kMenuMarkerFillBottomHeight;
extern const double kMenuUnsignedIntToDoubleBias;
extern const double kMenuSignedIntToDoubleBias;
extern const f32 kMenuPulseStep;
extern const f32 kMenuHalf;
extern const f32 kMenuInitRectWidth;
extern const f32 kMenuInitRectHeight;
extern const f32 kMenuColorBlendSpan;
extern const f32 kMenuColorBlendTarget;
extern const f32 kMenuPaletteBlendStep;
}
#include "ffcc/textureman.h"
#include "ffcc/fontman.h"

#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CMenuPcs MenuPcs ATTRIBUTE_ALIGN(32);
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
static const char sMenuTexturePathFmt[] = "dvd/%smenu/%s.tex";
extern "C" const char s_p_menu_cpp[] = "p_menu.cpp";
static const char sMenuGc23FontPathFmt[] = "dvd/%smenu/gc23.fnt";
static const char sMenuFontPathFmt[] = "dvd/%smenu/%s.fnt";
static const char sMenuGc22FontPathFmt[] = "dvd/%smenu/gc22.fnt";
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
static const char sMenuTexButton[] = "button";
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

extern "C" const f32 kMenuFadeStep = 0.015625f;
extern "C" const f32 kMenuOne = 1.0f;
extern "C" const f32 kMenuInitOne = 0.0f;
extern "C" const f32 kMenuScreenCenterX = 320.0f;
extern "C" const f32 kMenuScreenCenterY = 224.0f;
extern "C" const f32 kMenuMarkerMinY = 16.0f;
extern "C" const f32 kMenuMarkerMaxY = 432.0f;
extern "C" const f32 kMenuMarkerCapSize = 8.0f;
extern "C" const f32 kMenuAlphaMax = 255.0f;
extern "C" const f32 kMenuMarkerFillYOffset = 3.0f;
extern "C" const f32 kMenuMarkerFillTopHeight = 4.0f;
extern "C" const f32 kMenuMarkerFillBottomHeight = 2.0f;
extern "C" const double kMenuUnsignedIntToDoubleBias = 4503601774854144.0;
extern "C" const double kMenuSignedIntToDoubleBias = 4503599627370496.0;
extern "C" const f32 kMenuPulseStep = 0.1f;
extern "C" const f32 kMenuHalf = 0.5f;
extern "C" const f32 kMenuInitRectWidth = 120.0f;
extern "C" const f32 kMenuInitRectHeight = 56.0f;
extern "C" const f32 kMenuColorBlendSpan = 7.0f;
extern "C" const f32 kMenuColorBlendTarget = 245.0f;
extern "C" const f32 kMenuOrthoBottom = 448.0f;
extern "C" const f32 kMenuOrthoRight = 640.0f;
extern "C" const f32 kMenuOrthoFar = -100.0f;
extern "C" const f32 kMenuPaletteBlendStep = 0.125f;

extern "C" {
void create__8CMenuPcsFv(CMenuPcs*);
void destroy__8CMenuPcsFv(CMenuPcs*);
void calc__8CMenuPcsFv(CMenuPcs*);
void draw__8CMenuPcsFv(CMenuPcs*);
void loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(
    CMenuPcs*, char**, int, int, CMenuPcs::CTmp*, int, int, int);
void drawSingleMenu__8CMenuPcsFv(CMenuPcs*);
}

static CProcessTableCallback s_menuTableDescCreate = {0, 0xFFFFFFFF,
                                                       reinterpret_cast<unsigned int>(create__8CMenuPcsFv)};
static CProcessTableCallback s_menuTableDescDestroy = {0, 0xFFFFFFFF,
                                                        reinterpret_cast<unsigned int>(destroy__8CMenuPcsFv)};
static CProcessTableCallback s_menuTableDescCalc = {0, 0xFFFFFFFF,
                                                     reinterpret_cast<unsigned int>(calc__8CMenuPcsFv)};
static CProcessTableCallback s_menuTableDescDraw = {0, 0xFFFFFFFF,
                                                     reinterpret_cast<unsigned int>(draw__8CMenuPcsFv)};
static CProcessTableCallback s_menuTableDescLoadTextureAsync = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii)};
static CProcessTableCallback s_menuTableDescDrawSingleMenu = {0, 0xFFFFFFFF,
                                                              reinterpret_cast<unsigned int>(drawSingleMenu__8CMenuPcsFv)};

CProcessTable CMenuPcs::m_table = {
    const_cast<char*>(sCMenuPcsProcessName),
    {
        s_menuTableDescCreate.m_thisOffset, s_menuTableDescCreate.m_virtualOffset, s_menuTableDescCreate.m_function,
        s_menuTableDescDestroy.m_thisOffset, s_menuTableDescDestroy.m_virtualOffset, s_menuTableDescDestroy.m_function,
        s_menuTableDescCalc.m_thisOffset, s_menuTableDescCalc.m_virtualOffset, s_menuTableDescCalc.m_function,
        0x1A, 0,
        s_menuTableDescDraw.m_thisOffset, s_menuTableDescDraw.m_virtualOffset, s_menuTableDescDraw.m_function,
        0x49, 0x1,
        s_menuTableDescLoadTextureAsync.m_thisOffset, s_menuTableDescLoadTextureAsync.m_virtualOffset,
        s_menuTableDescLoadTextureAsync.m_function,
        0x1A, 0x10,
        s_menuTableDescDrawSingleMenu.m_thisOffset, s_menuTableDescDrawSingleMenu.m_virtualOffset,
        s_menuTableDescDrawSingleMenu.m_function,
        0x49, 0x11,
    },
};

extern const char sYmTracerCommonName[];
extern const char s_pppParHitSphWin[];
const char* sMenuCommonTextureNames[] = {
    sYmTracerCommonName, s_pppParHitSphWin,
};

extern const char* sMenuTextureRegionNameTable[];
extern int sMenuTextureInfoTable[];

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

static inline float LoadFloat(const float& value)
{
    return value;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMenuPcs::~CMenuPcs()
{
    if (&m_mcCtrl != nullptr) {
        m_mcCtrl.m_previousState = 0;
        m_mcCtrl.m_state = 0;
        m_mcCtrl.m_lastResult = 0;
        m_mcCtrl.m_iteration = 0;
        m_mcCtrl.m_userBuffer = 0;
        m_mcCtrl.m_createFlag = 0;
        m_mcCtrl.m_cardChannel = 0;
        m_mcCtrl.m_saveIndex = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800974a8
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
    one = LoadFloat(kMenuInitOne);
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
    m_specialModeWorkHead = 0;
    for (int workIndex = 0; workIndex < 11; workIndex++) {
        m_specialModeWork[workIndex] = 0;
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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::create()
{
    char fontPath[0x80];
    char texPath[0x100];
    static int tTmp[] = {
        0, reinterpret_cast<int>(const_cast<char*>(sMenuTexKasoru)),
        0, reinterpret_cast<int>(const_cast<char*>(sMenuTexPause)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_0)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_1)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_2)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_3)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_4)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_5)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_6)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_7)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin1_8)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_0)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_1)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_2)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_3)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_4)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_5)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_6)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_7)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWin2_8)),
        1, reinterpret_cast<int>(const_cast<char*>(sMenuTexWinKazari)),
        0, reinterpret_cast<int>(const_cast<char*>(sMenuTexButton))
    };
    u8* self = reinterpret_cast<u8*>(this);

    unsigned long menuHeapSize = 0xC4000;
    if (FontMan.m_font != 0) {
        menuHeapSize -= FontMan.GetInternal22Size();
    }

    m_menuStage = Memory.CreateStage(menuHeapSize, const_cast<char*>(sCMenuPcsProcessName), 0);
    m_mode = -1;

    memset(m_textureSets, 0, sizeof(m_textureSets));
    memset(m_textures, 0, sizeof(m_textures));

    sprintf(fontPath, const_cast<char*>(sMenuGc22FontPathFmt), Game.GetLangString());
    loadFont(0, fontPath, 0, 0);

    for (int i = 0; i < 2; i++) {
        sprintf(texPath, const_cast<char*>(sMenuTexturePathFmt), Game.GetLangString(), sMenuCommonTextureNames[i]);

        CFile::CHandle* fileHandle = File.Open(texPath, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            void* stage = m_mode == 1 ? MapMng.m_stage : m_menuStage;

            CTextureSet* textureSet = new (m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x182) CTextureSet;
            m_textureSets[i] = textureSet;
            m_textureSets[i]->Create(File.m_readBuffer, reinterpret_cast<CMemory::CStage*>(stage), 0, 0, 0, 0);

            File.Close(fileHandle);
        }
    }

    int* textureInfo = tTmp;
    for (int i = 0; i < 0x16; i++) {
        CTextureSet* textureSet = m_textureSets[textureInfo[0]];
        const unsigned long textureIndex = static_cast<unsigned long>(textureSet->Find(reinterpret_cast<char*>(textureInfo[1])));
        CTexture* texture = textureSet->GetTexture(textureIndex);
        texture->AddRef();
        m_textures[i] = texture;
        textureInfo += 2;
    }

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
    u8* self = reinterpret_cast<u8*>(this);

    int i = 0;
    CTexture** textureSlot = m_textures;
    do {
        ReleaseRefSlot(reinterpret_cast<void**>(textureSlot));
        textureSlot++;
        i++;
    } while (i < 0x16);

    i = 0;
    CTextureSet** textureSetSlot = m_textureSets;
    do {
        ReleaseRefSlot(reinterpret_cast<void**>(textureSetSlot));
        textureSetSlot++;
        i++;
    } while (i < 2);

    if (m_fonts[0] != nullptr) {
        if (m_fonts[0]->DecRef() == 0) {
            delete m_fonts[0];
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
void CMenuPcs::loadFont(int type, char* path, int slot, int tlutMode)
{
    CMemory::CStage* stage = 0;

    if (type != 1) {
        if (type < 1) {
            if (type >= 0) {
                stage = m_menuStage;
            }
        } else if (type < 3) {
            stage = PartMng.m_pppEnvSt.m_stagePtr;
        }
    } else {
        stage = m_stageF0;
    }

    if ((slot == 0) && FontMan.m_font) {
        m_fonts[0] = FontMan.m_font;
        reinterpret_cast<u32*>(m_fonts[0])[1] = reinterpret_cast<u32*>(m_fonts[0])[1] + 1;
    } else {
        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        m_fonts[slot] = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), 0xF8) CFont;
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
            {{0xB4, 0xD2, 0x84, 0xFF}, {0x00, 0x3B, 0x06, 0xFF}},
            {{0xA8, 0xFB, 0x00, 0xFF}, {0x01, 0x2F, 0x5E, 0xFF}},
            {{0xA8, 0xFB, 0xFA, 0xFF}, {0x01, 0x2F, 0x5E, 0xFF}},
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
        MenuFontTlutPalette* palette = &pal[tlutMode * 0x1C];

        for (int colorIndex = 0; colorIndex < 0x10; colorIndex++) {
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
                    blend = LoadFloat(kMenuOne) - static_cast<float>(colorIndex - 8) * LoadFloat(kMenuPaletteBlendStep);
                    blendInv = LoadFloat(kMenuOne) - blend;
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

const char* sMenuTextureRegionNameTable[] = {
    sMenuRegionShibuya, sMenuRegionFace, 0, 0, 0, 0, 0, 0, 0
};

int sMenuTextureInfoTable[] = {
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexBattle)),
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexHeart)),
    3, reinterpret_cast<int>(const_cast<char*>(sMenuRegionFace)),
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexNavi)),
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexHp0)),
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexHp1)),
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexHp2)),
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexSuna)),
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexGba)),
    2, reinterpret_cast<int>(const_cast<char*>(sMenuTexBattle2))
};

/*
 * --INFO--
 * PAL Address: 0x80096b94
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::loadTexture(char** paths, int textureSetStart, int textureSetCount, CMenuPcs::CTmp* tmp,
                           int textureStart, int textureCount, int stageSelect)
{
    char texPath[0x104];
    u8* self = reinterpret_cast<u8*>(this);

    for (int i = 0; i < textureSetCount; i++) {
        sprintf(texPath, const_cast<char*>(sMenuTexturePathFmt), Game.GetLangString(), *paths);

        CFile::CHandle* fileHandle = File.Open(texPath, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            CMemory::CStage* stage;
            if (m_mode == 1) {
                stage = MapMng.m_stage;
            } else if (stageSelect == 3) {
                stage = MapMng.m_stage;
            } else {
                if ((Game.m_gameWork.m_menuStageMode == 0) || (stageSelect == 0)) {
                    stage = m_menuStage;
                } else if (stageSelect == 1) {
                    stage = m_stageF0;
                } else {
                    stage = m_stageF4;
                }
            }

            m_textureSets[textureSetStart + i] =
                new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x182) CTextureSet;

            m_textureSets[textureSetStart + i]->Create(File.m_readBuffer, stage, 0, 0, 0, 0);

            File.Close(fileHandle);
        }

        paths++;
    }

    for (int i = 0; i < textureCount; i++) {
        const unsigned long textureIndex =
            static_cast<unsigned long>(m_textureSets[tmp->m_textureSetIndex]->Find(tmp->m_textureName));
        CTexture* texture = m_textureSets[tmp->m_textureSetIndex]->GetTexture(textureIndex);
        texture->AddRef();
        m_textures[textureStart + i] = texture;
        tmp++;
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
    CMenuPcs* menu;

    if (m_mode != static_cast<int>(mode)) {
        Graphic._WaitDrawDone(const_cast<char*>(s_p_menu_cpp), 0x1B0);
        currentMode = m_mode;
        if (currentMode != 1) {
            if (currentMode < 1) {
                if ((currentMode != -1) && (-2 < currentMode)) {
                    ReleaseRefSlot(reinterpret_cast<void**>(&m_fonts[1]));

                    i = 0;
                    menu = this;
                    do {
                        ReleaseRefSlot(reinterpret_cast<void**>(&menu->m_textures[0x16]));
                        i++;
                        menu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(menu) + 4);
                    } while (i < 10);

                    i = 0;
                    menu = this;
                    do {
                        ReleaseRefSlot(reinterpret_cast<void**>(&menu->m_textureSets[2]));
                        i++;
                        menu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(menu) + 4);
                    } while (i < 2);

                    i = 0;
                    menu = this;
                    do {
                        ReleaseRefSlot(reinterpret_cast<void**>(&menu->m_battleRingMenus[0]));
                        i++;
                        menu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(menu) + 4);
                    } while (i < 4);

                    i = 0;
                    menu = this;
                    do {
                        ReleaseRefSlot(reinterpret_cast<void**>(&menu->m_battleMesMenus[0]));
                        i++;
                        menu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(menu) + 4);
                    } while (i < 12);

                    destroySingleMenu();
                    destroyVillageMenu();
                }
            } else if (currentMode < 3) {
                destroyBonus();
            }
        } else {
            destroyWorld();
        }

        m_mode = static_cast<int>(mode);
        currentMode = m_mode;
        if (currentMode != 1) {
            if (currentMode < 1) {
                if ((currentMode != -1) && (-2 < currentMode)) {
                    createBattle();
                    createSingleMenu();
                }
            } else if (currentMode < 3) {
                createBonus();
            }
        } else {
            createWorld();
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
    u8* self = reinterpret_cast<u8*>(this);
    switch (m_mode) {
        case 0:
        {
            int i = 0;
            CMenuPcs* menu = this;
            do {
                menu->m_battleRingMenus[0]->Calc();
                i++;
                menu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(menu) + 4);
            } while (i < 4);

            i = 0;
            menu = this;
            do {
                menu->m_battleMesMenus[0]->Calc();
                i++;
                menu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(menu) + 4);
            } while (i < 0xc);

            int current = m_battleHud.m_gaugeValue;
            int value = current - 1;
            int limit = current + (m_battleHud.m_gaugeTarget - current);
            if (limit >= value) {
                current++;
                if (current < limit) {
                    limit = current;
                }
                value = limit;
            }
            m_battleHud.m_gaugeValue = value;

            u32 counter = m_battleHud.m_fadeCounter - 1;
            m_battleHud.m_fadeCounter = counter & ~((int)counter >> 31);
            counter = m_battleHud.m_gaugeCounter - 1;
            m_battleHud.m_gaugeCounter = counter & ~((int)counter >> 31);

            calcVillageMenu();
            break;
        }
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
    Mtx44 orthoMtx;
    Mtx modelMtx;
    Mtx44 screenMtx;
    Mtx texMtx;

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, 0);
    C_MTXOrtho(orthoMtx, LoadFloat(kMenuInitOne), LoadFloat(kMenuOrthoBottom), LoadFloat(kMenuInitOne),
               LoadFloat(kMenuOrthoRight), LoadFloat(kMenuInitOne), LoadFloat(kMenuOrthoFar));
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    {
        CColor white(0xFF, 0xFF, 0xFF, 0xFF);
        GXSetChanAmbColor(GX_COLOR0A0, white.color);
    }
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

    {
        int mode = m_mode;

        if (mode != 1) {
            if (mode < 1) {
                if (mode >= 0) {
                    drawBattle();
                    drawVillageMenu();
                }
            } else if (mode < 3) {
                drawBonus();
            }
        } else {
            drawWorld();
        }
    }

    if (((CFlatEventFlags() & 0x10) != 0) && (System.m_scenegraphStepMode == 2)) {
        CTexture* texture = m_textures[1];
        TextureMan.SetTexture(GX_TEXMAP0, texture);

        float width = static_cast<float>(texture->m_width);
        float height = static_cast<float>(texture->m_height);
        PSMTXScale(texMtx, LoadFloat(kMenuOne) / width, LoadFloat(kMenuOne) / height,
                   LoadFloat(kMenuOne));
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);

        TextureMan.SetTextureTev(texture);

        {
            int alpha = static_cast<int>(LoadFloat(kMenuAlphaMax) * (LoadFloat(kMenuHalf) * (LoadFloat(kMenuOne) + sinf(System.m_frameCounter * LoadFloat(kMenuPulseStep)))));
            CColor color(0xFF, 0xFF, 0xFF, static_cast<u8>(alpha));
            GXSetChanMatColor(GX_COLOR0A0, color.color);
            DrawRect(3, LoadFloat(kMenuScreenCenterX), LoadFloat(kMenuScreenCenterY), LoadFloat(kMenuInitRectWidth),
                     LoadFloat(kMenuInitRectHeight), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne),
                     LoadFloat(kMenuOne), LoadFloat(kMenuOne), LoadFloat(kMenuInitOne));
        }
    }

    PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
    GXSetProjection(screenMtx, GX_PERSPECTIVE);
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
    C_MTXOrtho(orthoMtx, LoadFloat(kMenuInitOne), LoadFloat(kMenuOrthoBottom), LoadFloat(kMenuInitOne),
               LoadFloat(kMenuOrthoRight), LoadFloat(kMenuInitOne), LoadFloat(kMenuOrthoFar));
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawQuit()
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
    bool noInput = false;
    u32 result;

    if (Pad.m_debugPadLock == 0) {
        if (port != 0) {
            goto input_check_done;
        }
        if (Pad.m_debugPadPort == -1) {
            goto input_check_done;
        }
    }
    noInput = true;

input_check_done:
    if (noInput) {
        result = 0;
    } else {
        u32 clamped = (Pad.m_debugPadPort == port) ? 0 : port;
        result = Pad.GetPadInputs()[clamped].buttonDown[0];
    }

    return result;
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
    bool noInput = false;
    u32 result;

    if (Pad.m_debugPadLock == 0) {
        if (port != 0) {
            goto repeat_check_done;
        }
        if (Pad.m_debugPadPort == -1) {
            goto repeat_check_done;
        }
    }
    noInput = true;

repeat_check_done:
    if (noInput) {
        result = 0;
    } else {
        u32 clamped = (Pad.m_debugPadPort == port) ? 0 : port;
        result = Pad.GetPadInputs()[clamped].repeatButton;
    }

    return result;
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
    u8* self = reinterpret_cast<u8*>(this);

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
    CGame* game = &Game;

    changeMode(static_cast<CMenuPcs::MENUMODE>((u32)__cntlzw((u32)(0x21 - game->m_currentMapId)) >> 5));
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
        PSMTXScale(texMtx, LoadFloat(kMenuOne) / (f32)width, LoadFloat(kMenuOne) / (f32)height,
                   LoadFloat(kMenuOne));
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
    if (w <= LoadFloat(kMenuInitOne)) {
        return;
    }
    if (h <= LoadFloat(kMenuInitOne)) {
        return;
    }
    {
        float u0;
        float u1;
        float v0;
        float v1;
        float x0;
        float y0;
        float x1;
        float y1;
        float scaledW;
        float scaledH;

        if ((attr & 8) != 0) {
            u1 = u + LoadFloat(kMenuHalf);
            u0 = (u + w) - LoadFloat(kMenuHalf);
        } else {
            u0 = u + LoadFloat(kMenuHalf);
            u1 = (u + w) - LoadFloat(kMenuHalf);
        }

        if ((attr & 4) != 0) {
            v1 = v + LoadFloat(kMenuHalf);
            v0 = (v1 + h) - LoadFloat(kMenuHalf);
        } else {
            v0 = v + LoadFloat(kMenuHalf);
            v1 = (v + h) - LoadFloat(kMenuHalf);
        }

        scaledW = w * us;
        scaledH = h * vs;

        x0 = x;
        if ((attr & 1) != 0) {
            x0 = -(scaledW * LoadFloat(kMenuHalf) - x);
        }

        y0 = y;
        if ((attr & 2) != 0) {
            y0 = -(scaledH * LoadFloat(kMenuHalf) - y);
        }

        x1 = x0 + scaledW;
        y1 = y0 + scaledH;

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        if (LoadFloat(kMenuInitOne) != angle) {
            float s = static_cast<float>(sin(angle));
            float c = static_cast<float>(cos(angle));
            float xtl = ((x0 - x) * c) + x;
            float ytl = ((x0 - x) * s) + y;
            float tx0 = (y0 - y) * s;
            float ty0 = (y0 - y) * c;
            float xtr = ((x1 - x) * c) + x;
            float ytr = ((x1 - x) * s) + y;
            float tx1 = (y1 - y) * s;
            float ty1 = (y1 - y) * c;

            GXPosition3f32(xtl - tx0, ytl + ty0, LoadFloat(kMenuInitOne));
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(xtr - tx0, ytr + ty0, LoadFloat(kMenuInitOne));
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(xtl - tx1, ytl + ty1, LoadFloat(kMenuInitOne));
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(xtr - tx1, ytr + ty1, LoadFloat(kMenuInitOne));
            GXTexCoord2f32(u1, v1);
        } else {
            GXPosition3f32(x0, y0, LoadFloat(kMenuInitOne));
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(x1, y0, LoadFloat(kMenuInitOne));
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(x0, y1, LoadFloat(kMenuInitOne));
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(x1, y1, LoadFloat(kMenuInitOne));
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
    if (w <= LoadFloat(kMenuInitOne)) {
        return;
    }
    if (h <= LoadFloat(kMenuInitOne)) {
        return;
    }
    {
        float u0;
        float u1;
        float v0;
        float v1;
        float x0;
        float y0;
        float x1;
        float y1;
        float scaledW;
        float scaledH;

        if ((attr & 8) != 0) {
            u1 = u + LoadFloat(kMenuHalf);
            u0 = (u + w) - LoadFloat(kMenuHalf);
        } else {
            u0 = u + LoadFloat(kMenuHalf);
            u1 = (u + w) - LoadFloat(kMenuHalf);
        }

        if ((attr & 4) != 0) {
            v1 = v + LoadFloat(kMenuHalf);
            v0 = (v1 + h) - LoadFloat(kMenuHalf);
        } else {
            v0 = v + LoadFloat(kMenuHalf);
            v1 = (v + h) - LoadFloat(kMenuHalf);
        }

        scaledW = w * us;
        scaledH = h * vs;

        x0 = x;
        if ((attr & 1) != 0) {
            x0 = -(scaledW * LoadFloat(kMenuHalf) - x);
        }

        y0 = y;
        if ((attr & 2) != 0) {
            y0 = -(scaledH * LoadFloat(kMenuHalf) - y);
        }

        x1 = x0 + scaledW;
        y1 = y0 + scaledH;

        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        if (LoadFloat(kMenuInitOne) != angle) {
            float s = static_cast<float>(sin(angle));
            float c = static_cast<float>(cos(angle));
            float xtl = ((x0 - x) * c) + x;
            float ytl = ((x0 - x) * s) + y;
            float tx0 = (y0 - y) * s;
            float ty0 = (y0 - y) * c;
            float xtr = ((x1 - x) * c) + x;
            float ytr = ((x1 - x) * s) + y;
            float tx1 = (y1 - y) * s;
            float ty1 = (y1 - y) * c;

            GXPosition3f32(xtl - tx0, ytl + ty0, LoadFloat(kMenuInitOne));
            GXColor1u32(*reinterpret_cast<u32*>(&colors[0]));
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(xtr - tx0, ytr + ty0, LoadFloat(kMenuInitOne));
            GXColor1u32(*reinterpret_cast<u32*>(&colors[1]));
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(xtl - tx1, ytl + ty1, LoadFloat(kMenuInitOne));
            GXColor1u32(*reinterpret_cast<u32*>(&colors[2]));
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(xtr - tx1, ytr + ty1, LoadFloat(kMenuInitOne));
            GXColor1u32(*reinterpret_cast<u32*>(&colors[3]));
            GXTexCoord2f32(u1, v1);
        } else {
            GXPosition3f32(x0, y0, LoadFloat(kMenuInitOne));
            GXColor1u32(*reinterpret_cast<u32*>(&colors[0]));
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(x1, y0, LoadFloat(kMenuInitOne));
            GXColor1u32(*reinterpret_cast<u32*>(&colors[1]));
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(x0, y1, LoadFloat(kMenuInitOne));
            GXColor1u32(*reinterpret_cast<u32*>(&colors[2]));
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(x1, y1, LoadFloat(kMenuInitOne));
            GXColor1u32(*reinterpret_cast<u32*>(&colors[3]));
            GXTexCoord2f32(u1, v1);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawBar(float x, float y, float width, CMenuPcs::TEX texBase, float alpha)
{
    if (width <= 0.0f) {
        return;
    }

    const float capW = 8.0f;
    const float barH = 8.0f;
    float midW = width - (capW * 2.0f);
    if (midW < 0.0f) {
        midW = 0.0f;
    }

    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt(FMT(0));

    const u8 alphaU8 = static_cast<u8>(255.0f * alpha);
    const CColor color(0xFF, 0xFF, 0xFF, alphaU8);
    GXSetChanMatColor(GX_COLOR0A0, color.color);

    const int tex = static_cast<int>(texBase);
    SetTexture(static_cast<TEX>(tex));
    DrawRect(0, x, y, capW, barH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    SetTexture(static_cast<TEX>(tex + 1));
    DrawRect(0, x + capW, y, midW, barH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

    SetTexture(static_cast<TEX>(tex + 2));
    DrawRect(8, x + width - capW, y, capW, barH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
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
	float midW = width - twoCorner;
	float midH = height - twoCorner;
	float overW;
	float overH;
	float uOff;
	float vOff;
	const int tex = static_cast<int>(texBase);
	const float xL = x;
	const float yT = y;

	if (midW < 0.0f) {
		midW = 0.0f;
	}
	if (midH < 0.0f) {
		midH = 0.0f;
	}

	overW = twoCorner - width;
	if (overW < 0.0f) {
		overW = 0.0f;
	}

	overH = twoCorner - height;
	if (overH < 0.0f) {
		overH = 0.0f;
	}
	uOff = overW * 0.5f;
	vOff = overH * 0.5f;

	const float cornerW = corner - uOff;
	const float cornerH = corner - vOff;

	SetTexture(static_cast<CMenuPcs::TEX>(tex));
	DrawRect(0, xL, yT, cornerW, cornerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 1));
	DrawRect(0, x + corner, yT, midW, cornerH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 2));
	DrawRect(0, ((x + width) - corner) + uOff, yT, cornerW, cornerH, uOff, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 3));
	DrawRect(0, xL, y + corner, corner, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 4));
	DrawRect(0, x + corner, y + corner, midW, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 5));
	DrawRect(0, (x + width) - corner, y + corner, corner, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 6));
	DrawRect(0, xL, ((y + height) - corner) + vOff, cornerW, cornerH, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

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
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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

    sprintf(path, const_cast<char*>(sMenuFontPathFmt), Game.GetLangString(), fileName);
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
        _GXColor tlutColor = m_fonts[fontNo + 2]->texturePtr->GetTlutColor(i);
        _GXColor out = tlutColor;

        if (i < 9) {
            out.r = color.r;
            out.g = color.g;
            out.b = color.b;
        } else {
            float blend = kMenuOne - static_cast<float>(i - 9) / kMenuColorBlendSpan;
            out.r = static_cast<u8>(-(static_cast<float>(0xF5 - color.r) * blend - kMenuColorBlendTarget));
            out.g = static_cast<u8>(-(static_cast<float>(0xF5 - color.g) * blend - kMenuColorBlendTarget));
            out.b = static_cast<u8>(-(static_cast<float>(0xF5 - color.b) * blend - kMenuColorBlendTarget));
        }

        CTexture* texture = m_fonts[fontNo + 2]->texturePtr;
        texture->SetTlutColor(i, out);
    }

    m_fonts[fontNo + 2]->texturePtr->FlushTlut();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::drawPause()
{
    if (((CFlatEventFlags() & 0x10) == 0) || (System.m_scenegraphStepMode != 2)) {
        return;
    }

    CTexture* texture = m_textures[1];
    TextureMan.SetTexture(GX_TEXMAP0, texture);

    if (texture != nullptr) {
        Mtx texMtx;
        float width = static_cast<float>(texture->m_width);
        float height = static_cast<float>(texture->m_height);
        PSMTXScale(texMtx, 1.0f / width, 1.0f / height, 1.0f);
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    }

    TextureMan.SetTextureTev(texture);

    int alpha = static_cast<int>(127.5f * (1.0f + sinf(System.m_frameCounter * kMenuPulseStep)));
    CColor color(0xFF, 0xFF, 0xFF, static_cast<u8>(alpha));
    GXSetChanMatColor(GX_COLOR0A0, color.color);
    DrawRect(3, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
}

/*
 * --INFO--
 * PAL Address: 0x8009460c
 * PAL Size: 880b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::createBattle()
{
    char path[0x104];
    char fontPath[0x80];

    for (int i = 0; i < 2; i++) {
        const char* language = Game.GetLangString();
        sprintf(path, const_cast<char*>(sMenuTexturePathFmt), language, sMenuTextureRegionNameTable[i]);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            void* stage = m_mode == 1 ? MapMng.m_stage : m_menuStage;

            CTextureSet* textureSet = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x182) CTextureSet;
            m_textureSets[i + 2] = textureSet;
            m_textureSets[i + 2]->Create(File.m_readBuffer, reinterpret_cast<CMemory::CStage*>(stage), 0, 0, 0, 0);

            File.Close(fileHandle);
        }
    }

    int* textureInfo = sMenuTextureInfoTable;
    for (int i = 0; i < 10; i++) {
        const unsigned long textureIndex =
            static_cast<unsigned long>(m_textureSets[textureInfo[0]]->Find(reinterpret_cast<char*>(textureInfo[1])));
        CTexture* texture = m_textureSets[textureInfo[0]]->GetTexture(textureIndex);
        texture->AddRef();
        m_textures[i + 0x16] = texture;
        textureInfo += 2;
    }

    for (int i = 0; i < 12; i++) {
        CMesMenu* menu = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x48B) CMesMenu;
        m_battleMesMenus[i] = menu;
        m_battleMesMenus[i]->SetBattleIndex(i);
        m_battleMesMenus[i]->Create();
    }

    for (int i = 0; i < 4; i++) {
        CRingMenu* menu = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x492) CRingMenu;
        m_battleRingMenus[i] = menu;
        m_battleRingMenus[i]->m_menuIndex = i;
        m_battleRingMenus[i]->Create();
    }

    sprintf(fontPath, const_cast<char*>(sMenuGc23FontPathFmt), Game.GetLangString());
    loadFont(0, fontPath, 1, 1);

    for (int i = 0; i < 0x100; i++) {
        _GXColor color = m_textures[0x18]->GetTlutColor(i);
        const int avg2 = (((int)color.r + (int)color.g + (int)color.b) / 3) * 2;
        color.r = static_cast<u8>(((int)color.r + avg2) / 3);
        color.g = static_cast<u8>(((int)color.g + avg2) / 3);
        color.b = static_cast<u8>(((int)color.b + avg2) / 3);

        const unsigned long tlutFmt = m_textures[0x18]->m_format;
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

    m_textures[0x18]->FlushExternalTlut(m_externalFontTlut);
    m_battleStateFlag = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::destroyBattle()
{
    void** slot = reinterpret_cast<void**>(&m_textures[0x16]);
    for (int i = 0; i < 10; i++, slot++) {
        ReleaseRefSlot(slot);
    }

    slot = reinterpret_cast<void**>(&m_textureSets[2]);
    for (int i = 0; i < 2; i++, slot++) {
        ReleaseRefSlot(slot);
    }

    slot = reinterpret_cast<void**>(m_battleRingMenus);
    for (int i = 0; i < 4; i++, slot++) {
        ReleaseRefSlot(slot);
    }

    slot = reinterpret_cast<void**>(m_battleMesMenus);
    for (int i = 0; i < 12; i++, slot++) {
        ReleaseRefSlot(slot);
    }

    destroySingleMenu();
    destroyVillageMenu();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcBattle()
{
    for (int i = 0; i < 4; i++) {
        m_battleRingMenus[i]->Calc();
    }

    for (int i = 0; i < 0xC; i++) {
        reinterpret_cast<CMenu*>(m_battleMesMenus[i])->Calc();
    }

    int limit = m_battleHud.m_gaugeTarget;
    int value = m_battleHud.m_gaugeValue - 1;
    if (value <= limit) {
        int alt = m_battleHud.m_gaugeValue + 1;
        value = limit;
        if (alt < limit) {
            value = alt;
        }
    }
    m_battleHud.m_gaugeValue = value;

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
        float fade = frame * LoadFloat(kMenuFadeStep);
        if (m_battleHud.m_visible != 0) {
            fade = LoadFloat(kMenuOne) - fade;
        }

        Mtx cameraMtx;
        Mtx44 viewMtx;
        Mtx44 screenMtx;
        Vec4d projected;
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        PSMTXCopy(cameraMtx, reinterpret_cast<MtxPtr>(viewMtx));
        viewMtx[3][2] = LoadFloat(kMenuInitOne);
        viewMtx[3][1] = LoadFloat(kMenuInitOne);
        viewMtx[3][0] = LoadFloat(kMenuInitOne);
        viewMtx[3][3] = LoadFloat(kMenuOne);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        PSMTX44Concat(screenMtx, viewMtx, screenMtx);
        Math.MTX44MultVec4(screenMtx, reinterpret_cast<Vec*>(m_battleHud.m_worldPos), &projected);

        if (LoadFloat(kMenuInitOne) < projected.w) {
            const int totalWidth = static_cast<int>(static_cast<float>(m_battleHud.m_width) * fade);
            const int halfWidth = totalWidth / 2;
            float screenX = LoadFloat(kMenuScreenCenterX) + (LoadFloat(kMenuScreenCenterX) * projected.x) / projected.w;
            float screenY = LoadFloat(kMenuScreenCenterY) - (LoadFloat(kMenuScreenCenterY) * projected.y) / projected.w;

            if (screenX < static_cast<float>(halfWidth)) {
                screenX = static_cast<float>(halfWidth);
            } else if (screenX > static_cast<float>(0x280 - halfWidth)) {
                screenX = static_cast<float>(0x280 - halfWidth);
            }

            if (screenY < LoadFloat(kMenuMarkerMinY)) {
                screenY = LoadFloat(kMenuMarkerMinY);
            } else if (screenY > LoadFloat(kMenuMarkerMaxY)) {
                screenY = LoadFloat(kMenuMarkerMaxY);
            }

            int fillWidth = ((totalWidth - 16) * m_battleHud.m_gaugeValue) / m_battleHud.m_gaugeMax;

            const float left = screenX - static_cast<float>(halfWidth);
            const float bodyLeft = left + LoadFloat(kMenuMarkerCapSize);
            const float alphaF = LoadFloat(kMenuAlphaMax) * fade;
            const CColor frameColor(0xFF, 0xFF, 0xFF, static_cast<u8>(alphaF));
            GXSetChanMatColor(GX_COLOR0A0, frameColor.color);

            if (LoadFloat(kMenuInitOne) < static_cast<float>(totalWidth)) {
                float bodyWidth = static_cast<float>(totalWidth) - LoadFloat(kMenuMarkerMinY);
                if (bodyWidth < LoadFloat(kMenuInitOne)) {
                    bodyWidth = LoadFloat(kMenuInitOne);
                }

                CTexture* tex = MenuPcs.m_textures[0xDD];
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                u32 width = tex->m_width;
                u32 height = tex->m_height;
                Mtx texMtx0;
                PSMTXScale(texMtx0, LoadFloat(kMenuOne) / static_cast<float>(width), LoadFloat(kMenuOne) / static_cast<float>(height), LoadFloat(kMenuOne));
                GXLoadTexMtxImm(texMtx0, GX_TEXMTX0, GX_MTX2x4);
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                TextureMan.SetTextureTev(tex);
                MenuPcs.DrawRect(0, left, screenY, LoadFloat(kMenuMarkerCapSize), LoadFloat(kMenuMarkerCapSize), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(kMenuOne), LoadFloat(kMenuOne), LoadFloat(kMenuInitOne));

                tex = MenuPcs.m_textures[0xDE];
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                width = tex->m_width;
                height = tex->m_height;
                Mtx texMtx1;
                PSMTXScale(texMtx1, LoadFloat(kMenuOne) / static_cast<float>(width), LoadFloat(kMenuOne) / static_cast<float>(height), LoadFloat(kMenuOne));
                GXLoadTexMtxImm(texMtx1, GX_TEXMTX0, GX_MTX2x4);
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                TextureMan.SetTextureTev(tex);
                MenuPcs.DrawRect(0, bodyLeft, screenY, bodyWidth, LoadFloat(kMenuMarkerCapSize), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(kMenuOne), LoadFloat(kMenuOne), LoadFloat(kMenuInitOne));

                tex = MenuPcs.m_textures[0xDF];
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                width = tex->m_width;
                height = tex->m_height;
                Mtx texMtx2;
                PSMTXScale(texMtx2, LoadFloat(kMenuOne) / static_cast<float>(width), LoadFloat(kMenuOne) / static_cast<float>(height), LoadFloat(kMenuOne));
                GXLoadTexMtxImm(texMtx2, GX_TEXMTX0, GX_MTX2x4);
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                TextureMan.SetTextureTev(tex);
                MenuPcs.DrawRect(0, (left + static_cast<float>(totalWidth)) - LoadFloat(kMenuMarkerCapSize), screenY, LoadFloat(kMenuMarkerCapSize), LoadFloat(kMenuMarkerCapSize), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(kMenuOne), LoadFloat(kMenuOne), LoadFloat(kMenuInitOne));
            }

            const int gauge = (m_battleHud.m_gaugeCounter * 0xFF) / 16;
            const CColor fillTop(0xFF, gauge, gauge, static_cast<u8>(alphaF));
            GXSetChanMatColor(GX_COLOR0A0, fillTop.color);
            TextureMan.SetTextureTev(0);
            DrawRect(0, bodyLeft, (screenY + LoadFloat(kMenuMarkerFillYOffset)) - LoadFloat(kMenuOne), static_cast<float>(fillWidth), LoadFloat(kMenuMarkerFillTopHeight), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(kMenuOne), LoadFloat(kMenuOne), LoadFloat(kMenuInitOne));

            const int gaugeTop = ((m_battleHud.m_gaugeCounter * 0x7F) / 16) + 0x80;
            const CColor fillBottom(0xFF, gaugeTop, gauge, static_cast<u8>(alphaF));
            GXSetChanMatColor(GX_COLOR0A0, fillBottom.color);
            DrawRect(0, bodyLeft, screenY + LoadFloat(kMenuMarkerFillYOffset), static_cast<float>(fillWidth), LoadFloat(kMenuMarkerFillBottomHeight), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(kMenuOne), LoadFloat(kMenuOne), LoadFloat(kMenuInitOne));
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
    u8* self = reinterpret_cast<u8*>(this);
    const int mode = m_mode;

    if ((mode != 2) && (mode != 1)) {
        destroySingleMenu();
    }

    Game.m_gameWork.m_menuStageMode = static_cast<u8>(isScriptMode);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexture* CMenuPcs::GetTexture(CMenuPcs::TEX tex)
{
    return m_textures[static_cast<int>(tex)];
}
