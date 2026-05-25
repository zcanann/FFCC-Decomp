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
#include "ffcc/ptrarray.h"
#include "ffcc/ref.h"
#include "ffcc/ringmenu.h"
extern "C" {
extern const f32 FLOAT_80330804;
extern const f32 kMenuInitOne;
extern const f32 kMenuOrthoBottom;
extern const f32 kMenuOrthoRight;
extern const f32 kMenuOrthoFar;
extern const f32 FLOAT_80330808;
extern const f32 FLOAT_80330810;
extern const f32 FLOAT_80330814;
extern const f32 FLOAT_80330818;
extern const f32 FLOAT_8033081C;
extern const f32 FLOAT_80330820;
extern const f32 FLOAT_80330824;
extern const f32 FLOAT_80330828;
extern const f32 FLOAT_8033082C;
extern const f32 FLOAT_80330830;
extern const f32 FLOAT_80330848;
extern const f32 FLOAT_8033084C;
extern const f32 FLOAT_80330850;
extern const f32 FLOAT_80330854;
extern const f32 FLOAT_80330858;
extern const f32 FLOAT_8033085C;
extern const f32 FLOAT_8033086C;
}
#include "ffcc/textureman.h"
#include "ffcc/fontman.h"

#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CMenuPcs MenuPcs ATTRIBUTE_ALIGN(32);
static const char kMenuPcsStageName[] = "CMenuPcs";
extern "C" const char s_p_menu_cpp[];

struct Vec4d
{
    float x;
    float y;
    float z;
    float w;
};

struct MenuFontTlutPalette
{
    _GXColor shadow;
    _GXColor highlight;
};
static const char s_win_kazari_801D9D48[] = "win_kazari";
static const char s_dvd__smenu__s_tex_801d9d6c[] = "dvd/%smenu/%s.tex";
static const char s_dvd__smenu_gc23_fnt_801d9d8c[] = "dvd/%smenu/gc23.fnt";
static const char s_dvd__smenu__s_fnt_801d9da0[] = "dvd/%smenu/%s.fnt";
static const char s_dvd__smenu_gc22_fnt_801d9db4[] = "dvd/%smenu/gc22.fnt";
static const char s_MenuTexKasoru_80330714[] = "kasoru";
static const char s_MenuTexPause_8033071C[] = "pause";
static const char s_MenuTexWin1_0_80330724[] = "win1_0";
static const char s_MenuTexWin1_1_8033072C[] = "win1_1";
static const char s_MenuTexWin1_2_80330734[] = "win1_2";
static const char s_MenuTexWin1_3_8033073C[] = "win1_3";
static const char s_MenuTexWin1_4_80330744[] = "win1_4";
static const char s_MenuTexWin1_5_8033074C[] = "win1_5";
static const char s_MenuTexWin1_6_80330754[] = "win1_6";
static const char s_MenuTexWin1_7_8033075C[] = "win1_7";
static const char s_MenuTexWin1_8_80330764[] = "win1_8";
static const char s_MenuTexWin2_0_8033076C[] = "win2_0";
static const char s_MenuTexWin2_1_80330774[] = "win2_1";
static const char s_MenuTexWin2_2_8033077C[] = "win2_2";
static const char s_MenuTexWin2_3_80330784[] = "win2_3";
static const char s_MenuTexWin2_4_8033078C[] = "win2_4";
static const char s_MenuTexWin2_5_80330794[] = "win2_5";
static const char s_MenuTexWin2_6_8033079C[] = "win2_6";
static const char s_MenuTexWin2_7_803307A4[] = "win2_7";
static const char s_MenuTexWin2_8_803307AC[] = "win2_8";
static const char s_MenuTexButton_803307B4[] = "button";
static const char s_MenuRegionShibuya_803307BC[] = "shibuya";
static const char s_MenuRegionFace_803307C4[] = "face";
static const char s_MenuTexBattle_803307CC[] = "battle";
static const char s_MenuTexHeart_803307D4[] = "heart";
static const char s_MenuTexNavi_803307DC[] = "navi";
static const char s_MenuTexHp0_803307E4[] = "hp0";
static const char s_MenuTexHp1_803307E8[] = "hp1";
static const char s_MenuTexHp2_803307EC[] = "hp2";
static const char s_MenuTexSuna_803307F0[] = "suna";
static const char s_MenuTexGba_803307F8[] = "gba";
static const char s_MenuTexBattle2_803307FC[] = "battle2";

extern "C" const f32 FLOAT_80330804 = 0.015625f;
extern "C" const f32 FLOAT_80330808 = 1.0f;
extern "C" const f32 kMenuInitOne = 0.0f;
extern "C" const f32 FLOAT_80330810 = 320.0f;
extern "C" const f32 FLOAT_80330814 = 224.0f;
extern "C" const f32 FLOAT_80330818 = 16.0f;
extern "C" const f32 FLOAT_8033081C = 432.0f;
extern "C" const f32 FLOAT_80330820 = 8.0f;
extern "C" const f32 FLOAT_80330824 = 255.0f;
extern "C" const f32 FLOAT_80330828 = 3.0f;
extern "C" const f32 FLOAT_8033082C = 4.0f;
extern "C" const f32 FLOAT_80330830 = 2.0f;
extern "C" const double DOUBLE_80330838 = 4503601774854144.0;
extern "C" const double DOUBLE_80330840 = 4503599627370496.0;
extern "C" const f32 FLOAT_80330848 = 0.1f;
extern "C" const f32 FLOAT_8033084C = 0.5f;
extern "C" const f32 FLOAT_80330850 = 120.0f;
extern "C" const f32 FLOAT_80330854 = 56.0f;
extern "C" const f32 FLOAT_80330858 = 7.0f;
extern "C" const f32 FLOAT_8033085C = 245.0f;
extern "C" const f32 kMenuOrthoBottom = 448.0f;
extern "C" const f32 kMenuOrthoRight = 640.0f;
extern "C" const f32 kMenuOrthoFar = -100.0f;
extern "C" const f32 FLOAT_8033086C = 0.125f;

extern const char __RTTI__8CManager_8032E7A8[];
extern const char __RTTI__8CProcess_8032E7B0[];

static unsigned int m_table_desc0__8CMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__8CMenuPcsFv)};
static unsigned int m_table_desc1__8CMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__8CMenuPcsFv)};
static unsigned int m_table_desc2__8CMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__8CMenuPcsFv)};
static unsigned int m_table_desc3__8CMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__8CMenuPcsFv)};
static unsigned int m_table_desc4__8CMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii)};
static unsigned int m_table_desc5__8CMenuPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawSingleMenu__8CMenuPcsFv)};

unsigned int CMenuPcs::m_table[0x57] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(kMenuPcsStageName)),
    m_table_desc0__8CMenuPcs[0], m_table_desc0__8CMenuPcs[1], m_table_desc0__8CMenuPcs[2],
    m_table_desc1__8CMenuPcs[0], m_table_desc1__8CMenuPcs[1], m_table_desc1__8CMenuPcs[2],
    m_table_desc2__8CMenuPcs[0], m_table_desc2__8CMenuPcs[1], m_table_desc2__8CMenuPcs[2],
    0x1A, 0,
    m_table_desc3__8CMenuPcs[0], m_table_desc3__8CMenuPcs[1], m_table_desc3__8CMenuPcs[2],
    0x49, 0x1,
    m_table_desc4__8CMenuPcs[0], m_table_desc4__8CMenuPcs[1], m_table_desc4__8CMenuPcs[2],
    0x1A, 0x10,
    m_table_desc5__8CMenuPcs[0], m_table_desc5__8CMenuPcs[1], m_table_desc5__8CMenuPcs[2],
    0x49, 0x11
};

extern const char* sMenuTextureRegionNameTable[];
extern int sMenuTextureInfoTable[];

static inline void ReleaseRefObject(void* object)
{
    if (object == nullptr) {
        return;
    }

    u32* raw = reinterpret_cast<u32*>(object);
    int refCount = static_cast<int>(raw[1]) - 1;
    raw[1] = static_cast<u32>(refCount);
    if (refCount == 0) {
        delete reinterpret_cast<CRef*>(object);
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
    u8* self = reinterpret_cast<u8*>(this);

    if (self + 0x20 != nullptr) {
        *reinterpret_cast<u32*>(self + 0x20) = 0;
        *reinterpret_cast<u32*>(self + 0x24) = 0;
        *reinterpret_cast<u32*>(self + 0x2C) = 0;
        *reinterpret_cast<u32*>(self + 0x34) = 0;
        *reinterpret_cast<u32*>(self + 0x3C) = 0;
        *reinterpret_cast<u32*>(self + 0x38) = 0;
        *reinterpret_cast<u32*>(self + 0x28) = 0;
        *reinterpret_cast<u32*>(self + 0x30) = 0;
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
    u8* self = reinterpret_cast<u8*>(this);
    f32 one;
    int i;
    int* cardChannel;

    m_menuStage = 0;
    m_stageF0 = 0;
    m_stageF4 = 0;
    memset(m_fonts, 0, sizeof(m_fonts));
    memset(m_textureSets, 0, sizeof(m_textureSets));
    memset(m_textures, 0, sizeof(m_textures));
    memset(self + 0x04, 0, 0x1C);

    self[0x859] = 0;
    *reinterpret_cast<u16*>(self + 0x86C) = 0;
    *reinterpret_cast<u32*>(self + 0x830) = 0;
    *reinterpret_cast<u32*>(self + 0x850) = 0;
    *reinterpret_cast<u16*>(self + 0x864) = 0;

    WmInit();
    BonusInit();

    self[0x8E] = 0;
    one = LoadFloat(kMenuInitOne);
    i = 1;
    cardChannel = reinterpret_cast<int*>(self + 0x838);
    self[0x8F] = 0;
    self[0x90] = 0;
    self[0x91] = 6;
    self[0x92] = 6;
    self[0x93] = 0;
    self[0x94] = 0;
    self[0x9C] = 0;
    *reinterpret_cast<f32*>(self + 0x98) = one;
    self[0x9D] = 0;
    self[0xA4] = 0;
    *reinterpret_cast<f32*>(self + 0xA0) = one;
    *reinterpret_cast<f32*>(self + 0xA8) = one;
    self[0xAC] = 0;
    self[0xB5] = 0;
    self[0xB6] = 0;
    self[0xB7] = 0;
    self[0xB8] = 0;
    *reinterpret_cast<u32*>(self + 0xBC) = 0;
    *reinterpret_cast<u32*>(self + 0xC0) = 0;
    *reinterpret_cast<u32*>(self + 0xC4) = 0;
    *reinterpret_cast<u32*>(self + 0xC8) = 0;
    *reinterpret_cast<u32*>(self + 0xCC) = 0;
    *reinterpret_cast<u32*>(self + 0xD0) = 0;
    *reinterpret_cast<u32*>(self + 0xD4) = 0;
    *reinterpret_cast<u32*>(self + 0xD8) = 0;
    *reinterpret_cast<u32*>(self + 0xDC) = 0;
    *reinterpret_cast<u32*>(self + 0xE0) = 0;
    *reinterpret_cast<u32*>(self + 0xE4) = 0;

    do {
        cardChannel[0x30] = 0;
        cardChannel = cardChannel + 1;
        i = i + -1;
    } while (i != 0);

    *reinterpret_cast<void**>(self + 0x878) = nullptr;
    self[0x87C] = 1;
    self[0x888] = 0;
    self[0x889] = 0;
    self[0x88A] = 0;
    *reinterpret_cast<u32*>(self + 0x884) = 0;
    *reinterpret_cast<u32*>(self + 0x880) = 0;
    *reinterpret_cast<u32*>(self + 0x88C) = 0;
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
    return reinterpret_cast<int>(m_table + index * 0x57);
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
        0, reinterpret_cast<int>(const_cast<char*>(s_MenuTexKasoru_80330714)),
        0, reinterpret_cast<int>(const_cast<char*>(s_MenuTexPause_8033071C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_0_80330724)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_1_8033072C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_2_80330734)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_3_8033073C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_4_80330744)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_5_8033074C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_6_80330754)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_7_8033075C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin1_8_80330764)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_0_8033076C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_1_80330774)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_2_8033077C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_3_80330784)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_4_8033078C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_5_80330794)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_6_8033079C)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_7_803307A4)),
        1, reinterpret_cast<int>(const_cast<char*>(s_MenuTexWin2_8_803307AC)),
        1, reinterpret_cast<int>(const_cast<char*>(s_win_kazari_801D9D48)),
        0, reinterpret_cast<int>(const_cast<char*>(s_MenuTexButton_803307B4))
    };
    u8* self = reinterpret_cast<u8*>(this);

    unsigned long menuHeapSize = 0xC4000;
    if (FontMan.m_font != 0) {
        menuHeapSize -= FontMan.GetInternal22Size();
    }

    m_menuStage = Memory.CreateStage(menuHeapSize, const_cast<char*>(kMenuPcsStageName), 0);
    *reinterpret_cast<int*>(self + 0x740) = -1;

    memset(m_textureSets, 0, sizeof(m_textureSets));
    memset(m_textures, 0, sizeof(m_textures));

    sprintf(fontPath, const_cast<char*>(s_dvd__smenu_gc22_fnt_801d9db4), Game.GetLangString());
    loadFont(0, fontPath, 0, 0);

    CMenuPcs* textureSetSlot = this;
    for (int i = 0; i < 2; i++) {
        sprintf(texPath, const_cast<char*>(s_dvd__smenu__s_tex_801d9d6c), Game.GetLangString(), sMenuTextureRegionNameTable[i]);

        CFile::CHandle* fileHandle = File.Open(texPath, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            void* stage = *reinterpret_cast<int*>(self + 0x740) == 1 ? MapMng.m_stage
                                                                     : m_menuStage;

            CTextureSet* textureSet = new (m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x182) CTextureSet;
            *reinterpret_cast<CTextureSet**>(reinterpret_cast<u8*>(textureSetSlot) + 0x14C) = textureSet;
            (*reinterpret_cast<CTextureSet**>(reinterpret_cast<u8*>(textureSetSlot) + 0x14C))
                ->Create(File.m_readBuffer, reinterpret_cast<CMemory::CStage*>(stage), 0, 0, 0, 0);

            File.Close(fileHandle);
        }

        textureSetSlot = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(textureSetSlot) + 4);
    }

    int* textureInfo = tTmp;
    CMenuPcs* textureSlot = this;
    for (int i = 0; i < 0x16; i++) {
        CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(self + 0x14C + textureInfo[0] * 4);
        const unsigned long textureIndex = static_cast<unsigned long>(textureSet->Find(reinterpret_cast<char*>(textureInfo[1])));
        CTexture* texture = (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(textureSet) + 8))[textureIndex];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) + 1;
        *reinterpret_cast<CTexture**>(reinterpret_cast<u8*>(textureSlot) + 0x18C) = texture;
        textureInfo += 2;
        textureSlot = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(textureSlot) + 4);
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
    CMenuPcs* textureCursor = this;
    int i = 0;
    do {
        int** slot = reinterpret_cast<int**>(reinterpret_cast<u8*>(textureCursor) + 0x18C);
        int* refObject = *slot;
        if (refObject != nullptr) {
            int refCount = refObject[1] - 1;
            refObject[1] = refCount;
            if ((refCount == 0) && (refObject != nullptr)) {
                reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
            }
            *slot = 0;
        }
        i++;
        textureCursor = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(textureCursor) + 4);
    } while (i < 0x16);

    textureCursor = this;
    i = 0;
    do {
        int** slot = reinterpret_cast<int**>(reinterpret_cast<u8*>(textureCursor) + 0x14C);
        int* refObject = *slot;
        if (refObject != nullptr) {
            int refCount = refObject[1] - 1;
            refObject[1] = refCount;
            if ((refCount == 0) && (refObject != nullptr)) {
                reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
            }
            *slot = 0;
        }
        i++;
        textureCursor = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(textureCursor) + 4);
    } while (i < 2);

    int* refObject = reinterpret_cast<int*>(m_fonts[0]);
    if (refObject != nullptr) {
        int refCount = refObject[1] - 1;
        refObject[1] = refCount;
        if ((refCount == 0) && (refObject != nullptr)) {
            reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
        }
        m_fonts[0] = 0;
    }

    Memory.DestroyStage(m_menuStage);
    if (*reinterpret_cast<s8*>(self + 0x859) != 0) {
        m_stageF0 = 0;
        *(self + 0x859) = 0;
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
                    blend = LoadFloat(FLOAT_80330808) - static_cast<float>(colorIndex - 8) * LoadFloat(FLOAT_8033086C);
                    blendInv = LoadFloat(FLOAT_80330808) - blend;
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
    s_MenuRegionShibuya_803307BC, s_MenuRegionFace_803307C4, 0, 0, 0, 0, 0, 0, 0
};

int sMenuTextureInfoTable[] = {
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexBattle_803307CC)),
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexHeart_803307D4)),
    3, reinterpret_cast<int>(const_cast<char*>(s_MenuRegionFace_803307C4)),
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexNavi_803307DC)),
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexHp0_803307E4)),
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexHp1_803307E8)),
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexHp2_803307EC)),
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexSuna_803307F0)),
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexGba_803307F8)),
    2, reinterpret_cast<int>(const_cast<char*>(s_MenuTexBattle2_803307FC))
};

unsigned int s_CMenuPcsTablePad0[3] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E7A8)), 0, 0};
unsigned int s_CMenuPcsTablePad1[5] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CManager_8032E7A8)),
    0,
    reinterpret_cast<unsigned int>(const_cast<char*>(__RTTI__8CProcess_8032E7B0)),
    0,
    0,
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
        sprintf(texPath, const_cast<char*>(s_dvd__smenu__s_tex_801d9d6c), Game.GetLangString(), *paths);

        CFile::CHandle* fileHandle = File.Open(texPath, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            CMemory::CStage* stage;
            if (*reinterpret_cast<int*>(self + 0x740) == 1) {
                stage = MapMng.m_stage;
            } else if (stageSelect == 3) {
                stage = MapMng.m_stage;
            } else {
                if ((Game.m_gameWork.m_menuStageMode == 0) || (stageSelect == 0)) {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
                } else if (stageSelect == 1) {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF0);
                } else {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
                }
            }

            *reinterpret_cast<CTextureSet**>(self + 0x14C + (textureSetStart + i) * 4) =
                new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x182) CTextureSet;

            (*reinterpret_cast<CTextureSet**>(self + 0x14C + (textureSetStart + i) * 4))
                ->Create(File.m_readBuffer, stage, 0, 0, 0, 0);

            File.Close(fileHandle);
        }

        paths++;
    }

    for (int i = 0; i < textureCount; i++) {
        const unsigned long textureIndex =
            static_cast<unsigned long>((*reinterpret_cast<CTextureSet**>(self + 0x14C + tmp->m_textureSetIndex * 4))
                                           ->Find(tmp->m_textureName));
        CTexture* texture =
            (*reinterpret_cast<CPtrArray<CTexture*>*>(
                reinterpret_cast<u8*>(*reinterpret_cast<CTextureSet**>(self + 0x14C + tmp->m_textureSetIndex * 4)) + 8))[textureIndex];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) + 1;
        *reinterpret_cast<CTexture**>(self + 0x18C + (textureStart + i) * 4) = texture;
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
    u8* self = reinterpret_cast<u8*>(this);

    for (int i = 0; i < textureCount; i++) {
        int offset = (i + textureStart) * 4;
        int* refObject = *reinterpret_cast<int**>(self + 0x18C + offset);
        if (refObject != nullptr) {
            int refCount = refObject[1] - 1;
            refObject[1] = refCount;
            if (refCount == 0) {
                delete reinterpret_cast<CRef*>(refObject);
            }
            *reinterpret_cast<void**>(self + 0x18C + offset) = nullptr;
        }
    }

    for (int i = 0; i < textureSetCount; i++) {
        int offset = (i + textureSetStart) * 4;
        int* refObject = *reinterpret_cast<int**>(self + 0x14C + offset);
        if (refObject != nullptr) {
            int refCount = refObject[1] - 1;
            refObject[1] = refCount;
            if (refCount == 0) {
                delete reinterpret_cast<CRef*>(refObject);
            }
            *reinterpret_cast<void**>(self + 0x14C + offset) = nullptr;
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
    int refCount;
    int* refObject;
    int i;
    CMenuPcs* slotMenu;

    if (*reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x740) != static_cast<int>(mode)) {
        Graphic._WaitDrawDone(const_cast<char*>(s_p_menu_cpp), 0x1B0);
        currentMode = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x740);
        if (currentMode != 1) {
            if (currentMode < 1) {
                if ((currentMode != -1) && (-2 < currentMode)) {
                    refObject = *reinterpret_cast<int**>(reinterpret_cast<u8*>(this) + 0xFC);
                    if (refObject != nullptr) {
                        refCount = refObject[1] - 1;
                        refObject[1] = refCount;
                        if ((refCount == 0) && (refObject != nullptr)) {
                            reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
                        }
                        *reinterpret_cast<void**>(reinterpret_cast<u8*>(this) + 0xFC) = nullptr;
                    }

                    i = 0;
                    slotMenu = this;
                    do {
                        refObject = *reinterpret_cast<int**>(reinterpret_cast<u8*>(slotMenu) + 0x1E4);
                        if (refObject != nullptr) {
                            refCount = refObject[1] - 1;
                            refObject[1] = refCount;
                            if ((refCount == 0) && (refObject != nullptr)) {
                                reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
                            }
                            *reinterpret_cast<void**>(reinterpret_cast<u8*>(slotMenu) + 0x1E4) = nullptr;
                        }
                        i++;
                        slotMenu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(slotMenu) + 4);
                    } while (i < 10);

                    i = 0;
                    slotMenu = this;
                    do {
                        refObject = *reinterpret_cast<int**>(reinterpret_cast<u8*>(slotMenu) + 0x154);
                        if (refObject != nullptr) {
                            refCount = refObject[1] - 1;
                            refObject[1] = refCount;
                            if ((refCount == 0) && (refObject != nullptr)) {
                                reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
                            }
                            *reinterpret_cast<void**>(reinterpret_cast<u8*>(slotMenu) + 0x154) = nullptr;
                        }
                        i++;
                        slotMenu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(slotMenu) + 4);
                    } while (i < 2);

                    i = 0;
                    slotMenu = this;
                    do {
                        refObject = *reinterpret_cast<int**>(reinterpret_cast<u8*>(slotMenu) + 0x13C);
                        if (refObject != nullptr) {
                            refCount = refObject[1] - 1;
                            refObject[1] = refCount;
                            if ((refCount == 0) && (refObject != nullptr)) {
                                reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
                            }
                            *reinterpret_cast<void**>(reinterpret_cast<u8*>(slotMenu) + 0x13C) = nullptr;
                        }
                        i++;
                        slotMenu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(slotMenu) + 4);
                    } while (i < 4);

                    i = 0;
                    slotMenu = this;
                    do {
                        refObject = *reinterpret_cast<int**>(reinterpret_cast<u8*>(slotMenu) + 0x10C);
                        if (refObject != nullptr) {
                            refCount = refObject[1] - 1;
                            refObject[1] = refCount;
                            if ((refCount == 0) && (refObject != nullptr)) {
                                reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
                            }
                            *reinterpret_cast<void**>(reinterpret_cast<u8*>(slotMenu) + 0x10C) = nullptr;
                        }
                        i++;
                        slotMenu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(slotMenu) + 4);
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

        *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x740) = static_cast<int>(mode);
        currentMode = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x740);
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
    int mode = *reinterpret_cast<int*>(self + 0x740);

    if (mode != 1) {
        if (mode >= 1) {
            if (mode < 3) {
                calcBonus();
            }
            return;
        }

        if (mode >= 0) {
            int i = 0;
            CMenuPcs* menu = this;
            do {
                (*reinterpret_cast<CMenu**>(reinterpret_cast<u8*>(menu) + 0x13c))->Calc();
                i++;
                menu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(menu) + 4);
            } while (i < 4);

            i = 0;
            menu = this;
            do {
                (*reinterpret_cast<CMenu**>(reinterpret_cast<u8*>(menu) + 0x10c))->Calc();
                i++;
                menu = reinterpret_cast<CMenuPcs*>(reinterpret_cast<u8*>(menu) + 4);
            } while (i < 0xc);

            int limit = *reinterpret_cast<int*>(self + 0x68);
            int current = *reinterpret_cast<int*>(self + 0x6c);
            int value = current - 1;
            if (value <= limit) {
                int alt = current + 1;
                value = limit;
                if (alt < limit) {
                    value = alt;
                }
            }
            *reinterpret_cast<int*>(self + 0x6c) = value;

            u32 counter = *reinterpret_cast<u32*>(self + 0x58) - 1;
            *reinterpret_cast<u32*>(self + 0x58) = counter & ~((int)counter >> 31);
            counter = *reinterpret_cast<u32*>(self + 0x5c) - 1;
            *reinterpret_cast<u32*>(self + 0x5c) = counter & ~((int)counter >> 31);

            calcVillageMenu();
        }
        return;
    }

    CalcDiaryMenu();
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
    Mtx modelMtx;
    Mtx texMtx;
    Mtx44 orthoMtx;
    Mtx44 screenMtx;

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
        int mode = *reinterpret_cast<int*>(reinterpret_cast<u8*>(this) + 0x740);

        if (mode == 1) {
            drawWorld();
        } else if (mode < 1) {
            if (mode >= 0) {
                drawBattle();
                drawVillageMenu();
            }
        } else if (mode < 3) {
            drawBonus();
        }
    }

    if (((CFlatEventFlags() & 0x10) != 0) && (System.m_scenegraphStepMode == 2)) {
        CTexture* texture = *reinterpret_cast<CTexture**>(reinterpret_cast<u8*>(this) + 0x190);
        TextureMan.SetTexture(GX_TEXMAP0, texture);

        float width = static_cast<float>(*reinterpret_cast<u32*>(reinterpret_cast<u8*>(texture) + 0x64));
        float height = static_cast<float>(*reinterpret_cast<u32*>(reinterpret_cast<u8*>(texture) + 0x68));
        PSMTXScale(texMtx, LoadFloat(FLOAT_80330808) / width, LoadFloat(FLOAT_80330808) / height,
                   LoadFloat(FLOAT_80330808));
        GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);

        TextureMan.SetTextureTev(texture);

        {
            int alpha = static_cast<int>(127.5f * (1.0f + sinf(System.m_frameCounter * FLOAT_80330848)));
            CColor color(0xFF, 0xFF, 0xFF, static_cast<u8>(alpha));
            GXSetChanMatColor(GX_COLOR0A0, color.color);
            DrawRect(3, LoadFloat(FLOAT_80330810), LoadFloat(FLOAT_80330814), LoadFloat(FLOAT_80330850),
                     LoadFloat(FLOAT_80330854), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne),
                     LoadFloat(FLOAT_80330808), LoadFloat(FLOAT_80330808), LoadFloat(kMenuInitOne));
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

    if (Pad._452_4_ == 0) {
        if (port != 0) {
            goto input_check_done;
        }
        if (Pad._448_4_ == -1) {
            goto input_check_done;
        }
    }
    noInput = true;

input_check_done:
    if (noInput) {
        result = 0;
    } else {
        u32 clamped = (Pad._448_4_ == port) ? 0 : port;
        result = *(u16*)((u8*)&Pad + 0x8 + clamped * 0x54);
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

    if (Pad._452_4_ == 0) {
        if (port != 0) {
            goto repeat_check_done;
        }
        if (Pad._448_4_ == -1) {
            goto repeat_check_done;
        }
    }
    noInput = true;

repeat_check_done:
    if (noInput) {
        result = 0;
    } else {
        u32 clamped = (Pad._448_4_ == port) ? 0 : port;
        result = *(u16*)((u8*)&Pad + 0x14 + clamped * 0x54);
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
    int* refObject;
    int refCount;

    if (*reinterpret_cast<int*>(self + 0x740) == 0) {
        for (int i = 0; i < 4; i++) {
            CMenu* menu = *reinterpret_cast<CMenu**>(self + 0x13C + i * 4);
            menu->ScriptChanging(script);
        }

        for (int i = 0; i < 12; i++) {
            CMenu* menu = *reinterpret_cast<CMenu**>(self + 0x10C + i * 4);
            menu->ScriptChanging(script);
        }
    }

    memset(self + 0x48, 0, 0x28);
    refObject = *reinterpret_cast<int**>(self + 0x100);
    if (refObject != nullptr) {
        refCount = refObject[1] - 1;
        refObject[1] = refCount;
        if ((refCount == 0) && (refObject != nullptr)) {
            reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
        }
        *reinterpret_cast<void**>(self + 0x100) = nullptr;
    }

    refObject = *reinterpret_cast<int**>(self + 0x104);
    if (refObject != nullptr) {
        refCount = refObject[1] - 1;
        refObject[1] = refCount;
        if ((refCount == 0) && (refObject != nullptr)) {
            reinterpret_cast<void (**)(void*, int)>(refObject[0])[2](refObject, 1);
        }
        *reinterpret_cast<void**>(self + 0x104) = nullptr;
    }
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
        PSMTXScale(texMtx, LoadFloat(FLOAT_80330808) / (f32)width, LoadFloat(FLOAT_80330808) / (f32)height,
                   LoadFloat(FLOAT_80330808));
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
            u1 = u + LoadFloat(FLOAT_8033084C);
            u0 = (u + w) - LoadFloat(FLOAT_8033084C);
        } else {
            u0 = u + LoadFloat(FLOAT_8033084C);
            u1 = (u + w) - LoadFloat(FLOAT_8033084C);
        }

        if ((attr & 4) != 0) {
            v1 = v + LoadFloat(FLOAT_8033084C);
            v0 = (v1 + h) - LoadFloat(FLOAT_8033084C);
        } else {
            v0 = v + LoadFloat(FLOAT_8033084C);
            v1 = (v + h) - LoadFloat(FLOAT_8033084C);
        }

        scaledW = w * us;
        scaledH = h * vs;

        x0 = x;
        if ((attr & 1) != 0) {
            x0 = -(scaledW * LoadFloat(FLOAT_8033084C) - x);
        }

        y0 = y;
        if ((attr & 2) != 0) {
            y0 = -(scaledH * LoadFloat(FLOAT_8033084C) - y);
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
            u1 = u + LoadFloat(FLOAT_8033084C);
            u0 = (u + w) - LoadFloat(FLOAT_8033084C);
        } else {
            u0 = u + LoadFloat(FLOAT_8033084C);
            u1 = (u + w) - LoadFloat(FLOAT_8033084C);
        }

        if ((attr & 4) != 0) {
            v1 = v + LoadFloat(FLOAT_8033084C);
            v0 = (v1 + h) - LoadFloat(FLOAT_8033084C);
        } else {
            v0 = v + LoadFloat(FLOAT_8033084C);
            v1 = (v + h) - LoadFloat(FLOAT_8033084C);
        }

        scaledW = w * us;
        scaledH = h * vs;

        x0 = x;
        if ((attr & 1) != 0) {
            x0 = -(scaledW * LoadFloat(FLOAT_8033084C) - x);
        }

        y0 = y;
        if ((attr & 2) != 0) {
            y0 = -(scaledH * LoadFloat(FLOAT_8033084C) - y);
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
    u8* fontSlot = reinterpret_cast<u8*>(this) + fontNo * 4;
    CFont* font = *reinterpret_cast<CFont**>(fontSlot + 0x100);

    if (font != 0) {
        u32* raw = reinterpret_cast<u32*>(font);
        if (--raw[1] == 0) {
            delete reinterpret_cast<CRef*>(font);
        }
        *reinterpret_cast<u32*>(fontSlot + 0x100) = 0;
    }

    sprintf(path, const_cast<char*>(s_dvd__smenu__s_fnt_801d9da0), Game.GetLangString(), fileName);
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
    u8* fontSlot = reinterpret_cast<u8*>(this) + 0x100 + fontNo * 4;

    for (int i = 0; i < 0x10; i++) {
        CTexture* texture =
            *reinterpret_cast<CTexture**>(*reinterpret_cast<u32*>(fontSlot) + 0x34);
        _GXColor out = texture->GetTlutColor(i);

        if (i < 9) {
            out.r = color.r;
            out.g = color.g;
            out.b = color.b;
        } else {
            float blend = FLOAT_80330808 - static_cast<float>(i - 9) / FLOAT_80330858;
            out.r = static_cast<u8>(-(static_cast<float>(0xF5 - color.r) * blend - FLOAT_8033085C));
            out.g = static_cast<u8>(-(static_cast<float>(0xF5 - color.g) * blend - FLOAT_8033085C));
            out.b = static_cast<u8>(-(static_cast<float>(0xF5 - color.b) * blend - FLOAT_8033085C));
        }

        texture->SetTlutColor(i, out);
    }

    (*reinterpret_cast<CTexture**>(*reinterpret_cast<u32*>(fontSlot) + 0x34))->FlushTlut();
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

    int alpha = static_cast<int>(127.5f * (1.0f + sinf(System.m_frameCounter * FLOAT_80330848)));
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
        sprintf(path, const_cast<char*>(s_dvd__smenu__s_tex_801d9d6c), language, sMenuTextureRegionNameTable[i]);

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
        CTexture* texture =
            (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(m_textureSets[textureInfo[0]]) + 8))[textureIndex];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) + 1;
        m_textures[i + 0x16] = texture;
        textureInfo += 2;
    }

    for (int i = 0; i < 12; i++) {
        CMesMenu* menu = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x48B) CMesMenu;
        m_battleMesMenus[i] = menu;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(m_battleMesMenus[i]) + 0x18) = i;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(m_battleMesMenus[i]) + 0x1C) = i;
        m_battleMesMenus[i]->Create();
    }

    for (int i = 0; i < 4; i++) {
        CRingMenu* menu = new (MenuPcs.m_menuStage, const_cast<char*>(s_p_menu_cpp), 0x492) CRingMenu;
        m_battleRingMenus[i] = menu;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(m_battleRingMenus[i]) + 8) = i;
        m_battleRingMenus[i]->Create();
    }

    sprintf(fontPath, const_cast<char*>(s_dvd__smenu_gc23_fnt_801d9d8c), Game.GetLangString());
    loadFont(0, fontPath, 1, 1);

    for (int i = 0; i < 0x100; i++) {
        _GXColor color = m_textures[0x18]->GetTlutColor(i);
        const int avg2 = (((int)color.r + (int)color.g + (int)color.b) / 3) * 2;
        color.r = static_cast<u8>(((int)color.r + avg2) / 3);
        color.g = static_cast<u8>(((int)color.g + avg2) / 3);
        color.b = static_cast<u8>(((int)color.b + avg2) / 3);

        const unsigned long tlutFmt = *reinterpret_cast<unsigned long*>(reinterpret_cast<u8*>(m_textures[0x18]) + 0x60);
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
    u8* self = reinterpret_cast<u8*>(this);
    void** slot = reinterpret_cast<void**>(self + 0x1E4);
    for (int i = 0; i < 10; i++, slot++) {
        ReleaseRefObject(*slot);
        *slot = nullptr;
    }

    slot = reinterpret_cast<void**>(self + 0x154);
    for (int i = 0; i < 2; i++, slot++) {
        ReleaseRefObject(*slot);
        *slot = nullptr;
    }

    slot = reinterpret_cast<void**>(self + 0x13C);
    for (int i = 0; i < 4; i++, slot++) {
        ReleaseRefObject(*slot);
        *slot = nullptr;
    }

    slot = reinterpret_cast<void**>(self + 0x10C);
    for (int i = 0; i < 12; i++, slot++) {
        ReleaseRefObject(*slot);
        *slot = nullptr;
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
        float fade = frame * LoadFloat(FLOAT_80330804);
        if (m_battleHud.m_visible != 0) {
            fade = LoadFloat(FLOAT_80330808) - fade;
        }

        Mtx cameraMtx;
        Mtx44 viewMtx;
        Mtx44 screenMtx;
        Vec4d projected;
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
        PSMTXCopy(cameraMtx, reinterpret_cast<MtxPtr>(viewMtx));
        viewMtx[3][0] = LoadFloat(kMenuInitOne);
        viewMtx[3][1] = LoadFloat(kMenuInitOne);
        viewMtx[3][2] = LoadFloat(kMenuInitOne);
        viewMtx[3][3] = LoadFloat(FLOAT_80330808);
        PSMTX44Copy(CameraPcs.m_screenMatrix, screenMtx);
        PSMTX44Concat(screenMtx, viewMtx, screenMtx);
        Math.MTX44MultVec4(screenMtx, reinterpret_cast<Vec*>(m_battleHud.m_worldPos), &projected);

        if (LoadFloat(kMenuInitOne) < projected.w) {
            const int totalWidth = static_cast<int>(static_cast<float>(m_battleHud.m_width) * fade);
            const int halfWidth = totalWidth / 2;
            float screenX = LoadFloat(FLOAT_80330810) + (LoadFloat(FLOAT_80330810) * projected.x) / projected.w;
            float screenY = LoadFloat(FLOAT_80330814) - (LoadFloat(FLOAT_80330814) * projected.y) / projected.w;

            if (screenX < static_cast<float>(halfWidth)) {
                screenX = static_cast<float>(halfWidth);
            } else {
                const float right = static_cast<float>(0x280 - halfWidth);
                if (screenX > right) {
                    screenX = right;
                }
            }

            if (screenY < LoadFloat(FLOAT_80330818)) {
                screenY = LoadFloat(FLOAT_80330818);
            } else if (screenY > LoadFloat(FLOAT_8033081C)) {
                screenY = LoadFloat(FLOAT_8033081C);
            }

            int fillWidth = ((totalWidth - 16) * m_battleHud.m_gaugeValue) / m_battleHud.m_gaugeMax;

            const float left = screenX - static_cast<float>(halfWidth);
            const float bodyLeft = left + LoadFloat(FLOAT_80330820);
            const float alphaF = LoadFloat(FLOAT_80330824) * fade;
            const CColor frameColor(0xFF, 0xFF, 0xFF, static_cast<u8>(alphaF));
            GXSetChanMatColor(GX_COLOR0A0, frameColor.color);

            if (LoadFloat(kMenuInitOne) < static_cast<float>(totalWidth)) {
                float bodyWidth = static_cast<float>(totalWidth) - LoadFloat(FLOAT_80330818);
                if (bodyWidth < LoadFloat(kMenuInitOne)) {
                    bodyWidth = LoadFloat(kMenuInitOne);
                }

                CTexture* tex = MenuPcs.m_textures[0xDD];
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                u32 width = tex->m_width;
                u32 height = tex->m_height;
                Mtx texMtx0;
                PSMTXScale(texMtx0, LoadFloat(FLOAT_80330808) / static_cast<float>(width), LoadFloat(FLOAT_80330808) / static_cast<float>(height), LoadFloat(FLOAT_80330808));
                GXLoadTexMtxImm(texMtx0, GX_TEXMTX0, GX_MTX2x4);
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                TextureMan.SetTextureTev(tex);
                MenuPcs.DrawRect(0, left, screenY, LoadFloat(FLOAT_80330820), LoadFloat(FLOAT_80330820), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(FLOAT_80330808), LoadFloat(FLOAT_80330808), LoadFloat(kMenuInitOne));

                tex = MenuPcs.m_textures[0xDE];
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                width = tex->m_width;
                height = tex->m_height;
                Mtx texMtx1;
                PSMTXScale(texMtx1, LoadFloat(FLOAT_80330808) / static_cast<float>(width), LoadFloat(FLOAT_80330808) / static_cast<float>(height), LoadFloat(FLOAT_80330808));
                GXLoadTexMtxImm(texMtx1, GX_TEXMTX0, GX_MTX2x4);
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                TextureMan.SetTextureTev(tex);
                MenuPcs.DrawRect(0, bodyLeft, screenY, bodyWidth, LoadFloat(FLOAT_80330820), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(FLOAT_80330808), LoadFloat(FLOAT_80330808), LoadFloat(kMenuInitOne));

                tex = MenuPcs.m_textures[0xDF];
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                width = tex->m_width;
                height = tex->m_height;
                Mtx texMtx2;
                PSMTXScale(texMtx2, LoadFloat(FLOAT_80330808) / static_cast<float>(width), LoadFloat(FLOAT_80330808) / static_cast<float>(height), LoadFloat(FLOAT_80330808));
                GXLoadTexMtxImm(texMtx2, GX_TEXMTX0, GX_MTX2x4);
                GXSetNumTexGens(1);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                TextureMan.SetTextureTev(tex);
                MenuPcs.DrawRect(0, (left + static_cast<float>(totalWidth)) - LoadFloat(FLOAT_80330820), screenY, LoadFloat(FLOAT_80330820), LoadFloat(FLOAT_80330820), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(FLOAT_80330808), LoadFloat(FLOAT_80330808), LoadFloat(kMenuInitOne));
            }

            const u8 gauge = static_cast<u8>((m_battleHud.m_gaugeCounter * 0xFF) / 16);
            const CColor fillTop(0xFF, gauge, gauge, static_cast<u8>(alphaF));
            GXSetChanMatColor(GX_COLOR0A0, fillTop.color);
            TextureMan.SetTextureTev(0);
            DrawRect(0, bodyLeft, (screenY + LoadFloat(FLOAT_80330828)) - LoadFloat(FLOAT_80330808), static_cast<float>(fillWidth), LoadFloat(FLOAT_8033082C), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(FLOAT_80330808), LoadFloat(FLOAT_80330808), LoadFloat(kMenuInitOne));

            const u8 gaugeTop = static_cast<u8>(((m_battleHud.m_gaugeCounter * 0x7F) / 16) + 0x80);
            const CColor fillBottom(0xFF, gaugeTop, gauge, static_cast<u8>(alphaF));
            GXSetChanMatColor(GX_COLOR0A0, fillBottom.color);
            DrawRect(0, bodyLeft, screenY + LoadFloat(FLOAT_80330828), static_cast<float>(fillWidth), LoadFloat(FLOAT_80330830), LoadFloat(kMenuInitOne), LoadFloat(kMenuInitOne), LoadFloat(FLOAT_80330808), LoadFloat(FLOAT_80330808), LoadFloat(kMenuInitOne));
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
    const int mode = *reinterpret_cast<int*>(self + 0x740);

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
