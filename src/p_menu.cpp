#include "ffcc/p_menu.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/menu.h"
#include "ffcc/mesmenu.h"
#include "ffcc/partMng.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/pad.h"
#include "ffcc/ptrarray.h"
#include "ffcc/ringmenu.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/textureman.h"
#include "ffcc/fontman.h"

#include <dolphin/mtx.h>
#include <math.h>
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CMenuPcs MenuPcs;
u8 gMenuProcessTable[0x15C];
static const char kMenuPcsStageName[] = "CMenuPcs";
static const char kPMenuSourceFile[] = "p_menu.cpp";

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

u8 ARRAY_802ea1a0[0x20];
extern void* __vt__8CManager;
extern "C" void* __vt__8CMenuPcs[];
extern int DAT_8020ef9c[];
extern u8 sMenuFontShadeTable[];
extern u8 sMenuFontPrimaryAlphaTable[];
extern u8 sMenuFontSecondaryAlphaTable[];
extern MenuFontTlutPalette sMenuFontTlutPaletteTable[];
extern char s_dvd__smenu__s_tex_801d9d6c[];
extern char s_dvd__smenu__s_fnt_801d9da0[];
extern char s_dvd__smenu_gc22_fnt_801d9db4[];
extern char s_dvd__smenu_gc23_fnt_801d9d8c[];

extern "C" void* __register_global_object(void* object, void* destructor, void* registration);
extern "C" void __dt__8CMenuPcsFv(void*);
extern "C" unsigned long GetInternal22Size__8CFontManFv(void*);
extern "C" void Calc__5CMenuFv(CMenu*);
extern "C" void CalcDiaryMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void calcBonus__8CMenuPcsFv(CMenuPcs*);
extern "C" void calcVillageMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void WmInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void BonusInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void drawBonus__8CMenuPcsFv(CMenuPcs*);
extern "C" void drawVillageMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void createBonus__8CMenuPcsFv(CMenuPcs*);
extern "C" void destroyBonus__8CMenuPcsFv(CMenuPcs*);
extern "C" void createSingleMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void destroySingleMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void destroyVillageMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void _WaitDrawDone__8CGraphicFPci(void*, const char*, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, unsigned char, int, int, unsigned char);

static inline void ReleaseRefObject(void* object)
{
    if (object == nullptr) {
        return;
    }

    u32* raw = reinterpret_cast<u32*>(object);
    int refCount = static_cast<int>(raw[1]);
    raw[1] = static_cast<u32>(refCount - 1);
    if (refCount - 1 == 0) {
        reinterpret_cast<void (*)(void*, int)>(*reinterpret_cast<u32*>(raw[0] + 8))(object, 1);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMenuPcs::~CMenuPcs()
{
    u8* self = reinterpret_cast<u8*>(this);

    *reinterpret_cast<u32*>(self) = reinterpret_cast<u32>(__vt__8CMenuPcs);

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
 * PAL Address: 0x800977d8
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_menu_cpp(void)
{
    u8* self = reinterpret_cast<u8*>(&MenuPcs);
    *reinterpret_cast<void**>(self) = &__vt__8CManager;
    *reinterpret_cast<void**>(self) = &__vt__8CProcess;
    *reinterpret_cast<void**>(self) = __vt__8CMenuPcs;

    u32* mcCtrl = reinterpret_cast<u32*>(self + 0x20);
    mcCtrl[0] = 0;
    mcCtrl[1] = 0;
    mcCtrl[2] = 0;
    mcCtrl[3] = 0;
    mcCtrl[4] = 0;
    mcCtrl[5] = 0;
    mcCtrl[6] = 0;
    mcCtrl[7] = 0;

    __register_global_object(&MenuPcs, reinterpret_cast<void*>(__dt__8CMenuPcsFv), ARRAY_802ea1a0);

    unsigned int* table = reinterpret_cast<unsigned int*>(gMenuProcessTable);
    table[1] = m_table_desc0__8CMenuPcs[0];
    table[2] = m_table_desc0__8CMenuPcs[1];
    table[3] = m_table_desc0__8CMenuPcs[2];
    table[4] = m_table_desc1__8CMenuPcs[0];
    table[5] = m_table_desc1__8CMenuPcs[1];
    table[6] = m_table_desc1__8CMenuPcs[2];
    table[7] = m_table_desc2__8CMenuPcs[0];
    table[8] = m_table_desc2__8CMenuPcs[1];
    table[9] = m_table_desc2__8CMenuPcs[2];
    table[12] = m_table_desc3__8CMenuPcs[0];
    table[13] = m_table_desc3__8CMenuPcs[1];
    table[14] = m_table_desc3__8CMenuPcs[2];
    table[17] = m_table_desc4__8CMenuPcs[0];
    table[18] = m_table_desc4__8CMenuPcs[1];
    table[19] = m_table_desc4__8CMenuPcs[2];
    table[22] = m_table_desc5__8CMenuPcs[0];
    table[23] = m_table_desc5__8CMenuPcs[1];
    table[24] = m_table_desc5__8CMenuPcs[2];
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

    *reinterpret_cast<void**>(self + 0xEC) = nullptr;
    *reinterpret_cast<void**>(self + 0xF0) = nullptr;
    *reinterpret_cast<void**>(self + 0xF4) = nullptr;
    memset(self + 0xF8, 0, 0x14);
    memset(self + 0x14C, 0, 0x40);
    memset(self + 0x18C, 0, 0x1A4);
    memset(self + 0x04, 0, 0x1C);

    self[0x859] = 0;
    *reinterpret_cast<u16*>(self + 0x86C) = 0;
    *reinterpret_cast<u32*>(self + 0x830) = 0;
    *reinterpret_cast<u32*>(self + 0x850) = 0;
    *reinterpret_cast<u16*>(self + 0x864) = 0;

    WmInit__8CMenuPcsFv(this);
    BonusInit__8CMenuPcsFv(this);

    self[0x8E] = 0;
    one = kMenuInitOne;
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
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::Quit()
{
	// TODO
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
    unsigned char* table = gMenuProcessTable;
    unsigned long offset = index * 0x15c;
    return (int)(table + offset);
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
    int* textureInfo = DAT_8020ef9c;
    u8* self = reinterpret_cast<u8*>(this);

    unsigned long menuHeapSize = 0xC4000;
    if (FontMan.m_font != 0) {
        menuHeapSize -= GetInternal22Size__8CFontManFv(&FontMan);
    }

    *reinterpret_cast<CMemory::CStage**>(self + 0xEC) =
        Memory.CreateStage(menuHeapSize, const_cast<char*>(kMenuPcsStageName), 0);
    *reinterpret_cast<int*>(self + 0x740) = -1;

    memset(self + 0x14C, 0, 0x40);
    memset(self + 0x18C, 0, 0x1A4);

    sprintf(fontPath, s_dvd__smenu_gc22_fnt_801d9db4, Game.GetLangString());
    loadFont(0, fontPath, 0, 0);

    for (int i = 0; i < 2; i++) {
        sprintf(texPath, s_dvd__smenu__s_tex_801d9d6c, Game.GetLangString(), sMenuTextureRegionNameTable[i]);

        CFile::CHandle* fileHandle = File.Open(texPath, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            void* stage = *reinterpret_cast<int*>(self + 0x740) == 1 ? *reinterpret_cast<void**>(&MapMng)
                                                                     : *reinterpret_cast<void**>(self + 0xEC);

            CTextureSet* textureSet = new (Game.m_mainStage, const_cast<char*>(kPMenuSourceFile), 0x182) CTextureSet;
            *reinterpret_cast<CTextureSet**>(self + 0x14C + i * 4) = textureSet;
            if (textureSet != 0) {
                textureSet->Create(File.m_readBuffer, reinterpret_cast<CMemory::CStage*>(stage), 0, 0, 0, 0);
            }

            File.Close(fileHandle);
        }
    }

    for (int i = 0; i < 0x16; i++) {
        CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(self + 0x14C + textureInfo[0] * 4);
        const unsigned long textureIndex = static_cast<unsigned long>(textureSet->Find(reinterpret_cast<char*>(textureInfo[1])));
        CTexture* texture = (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(textureSet) + 8))[textureIndex];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) + 1;
        *reinterpret_cast<CTexture**>(self + 0x18C + i * 4) = texture;
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
    for (int i = 0; i < 0x16; i++) {
        u8* slot = self + 0x18c + i * 4;
        ReleaseRefObject(*reinterpret_cast<void**>(slot));
        *reinterpret_cast<void**>(slot) = nullptr;
    }

    for (int i = 0; i < 2; i++) {
        u8* slot = self + 0x14c + i * 4;
        ReleaseRefObject(*reinterpret_cast<void**>(slot));
        *reinterpret_cast<void**>(slot) = nullptr;
    }

    ReleaseRefObject(*reinterpret_cast<void**>(self + 0xf8));
    *reinterpret_cast<void**>(self + 0xf8) = nullptr;

    Memory.DestroyStage(*reinterpret_cast<CMemory::CStage**>(self + 0xec));
    if (*(self + 0x859) != 0) {
        *reinterpret_cast<void**>(self + 0xf0) = nullptr;
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
    u8* self = reinterpret_cast<u8*>(this);
    CMemory::CStage* menuStage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    CFont** fontSlot = reinterpret_cast<CFont**>(self + 0xF8 + slot * 4);

    if (type == 1) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF0);
    } else if (type < 1) {
        if (type >= 0) {
            stage = menuStage;
        }
    } else if (type < 3) {
        stage = pppEnvStPtr->m_stagePtr;
    }

    if ((slot == 0) && (FontMan.m_font != 0)) {
        *fontSlot = FontMan.m_font;
        reinterpret_cast<u32*>(*fontSlot)[1] = reinterpret_cast<u32*>(*fontSlot)[1] + 1;
    } else {
        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        CFont* font = new (menuStage, const_cast<char*>(kPMenuSourceFile), 0xF8) CFont;
        *fontSlot = font;
        font->Create(File.m_readBuffer, stage);

        File.Close(fileHandle);
    }

    if (tlutMode < 2) {
        CFont* font = *fontSlot;
        MenuFontTlutPalette* palette = &sMenuFontTlutPaletteTable[tlutMode * 0x1C];

        for (int colorIndex = 0; colorIndex < 0x10; colorIndex++) {
            for (int tlutIndex = 0; tlutIndex < 0x1C; tlutIndex++) {
                _GXColor color = {
                    static_cast<u8>(0xFF - sMenuFontShadeTable[colorIndex]),
                    static_cast<u8>(0xFF - sMenuFontShadeTable[colorIndex]),
                    static_cast<u8>(0xFF - sMenuFontShadeTable[colorIndex]),
                    sMenuFontPrimaryAlphaTable[colorIndex],
                };

                if (colorIndex < 8) {
                    color.r = palette[tlutIndex].highlight.r;
                    color.g = palette[tlutIndex].highlight.g;
                    color.b = palette[tlutIndex].highlight.b;
                } else {
                    float blend = 1.0f - static_cast<float>(colorIndex - 8) * 0.125f;
                    float blendInv = 1.0f - blend;

                    color.r = static_cast<u8>(static_cast<float>(palette[tlutIndex].shadow.r) * blendInv +
                                              static_cast<float>(palette[tlutIndex].highlight.r) * blend);
                    color.g = static_cast<u8>(static_cast<float>(palette[tlutIndex].shadow.g) * blendInv +
                                              static_cast<float>(palette[tlutIndex].highlight.g) * blend);
                    color.b = static_cast<u8>(static_cast<float>(palette[tlutIndex].shadow.b) * blendInv +
                                              static_cast<float>(palette[tlutIndex].highlight.b) * blend);
                }

                font->SetTlutColor(tlutIndex, colorIndex, color);

                color.a = sMenuFontSecondaryAlphaTable[colorIndex];
                font->SetTlutColor(tlutIndex + 0x1C, colorIndex, color);
            }
        }

        font->FlushTlutColor();
    }
}

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
    char texPath[0x10C];
    int* tmpInfo = reinterpret_cast<int*>(tmp);
    u8* self = reinterpret_cast<u8*>(this);

    for (int i = 0; i < textureSetCount; i++) {
        sprintf(texPath, s_dvd__smenu__s_tex_801d9d6c, Game.GetLangString(), *paths);

        CFile::CHandle* fileHandle = File.Open(texPath, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            CMemory::CStage* stage = reinterpret_cast<CMemory::CStage*>(&MapMng);
            if ((*reinterpret_cast<int*>(self + 0x740) != 1) && (stageSelect != 3)) {
                if ((Game.m_gameWork.m_menuStageMode == 0) || (stageSelect == 0)) {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
                } else if (stageSelect == 1) {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF0);
                } else {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
                }
            }

            CTextureSet* textureSet = new (Game.m_mainStage, const_cast<char*>(kPMenuSourceFile), 0x182) CTextureSet;
            *reinterpret_cast<CTextureSet**>(self + 0x14C + (textureSetStart + i) * 4) = textureSet;

            if (textureSet != 0) {
                textureSet->Create(File.m_readBuffer, stage, 0, 0, 0, 0);
            }

            File.Close(fileHandle);
        }

        paths++;
    }

    for (int i = 0; i < textureCount; i++) {
        CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(self + 0x14C + tmpInfo[0] * 4);
        const unsigned long textureIndex = static_cast<unsigned long>(textureSet->Find(reinterpret_cast<char*>(tmpInfo[1])));
        CTexture* texture = (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(textureSet) + 8))[textureIndex];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) + 1;
        *reinterpret_cast<CTexture**>(self + 0x18C + (textureStart + i) * 4) = texture;
        tmpInfo += 2;
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
        void** slot = reinterpret_cast<void**>(self + 0x18C + (textureStart + i) * 4);
        ReleaseRefObject(*slot);
        *slot = nullptr;
    }

    for (int i = 0; i < textureSetCount; i++) {
        void** slot = reinterpret_cast<void**>(self + 0x14C + (textureSetStart + i) * 4);
        ReleaseRefObject(*slot);
        *slot = nullptr;
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
    u8* self = reinterpret_cast<u8*>(this);
    int currentMode = *reinterpret_cast<int*>(self + 0x740);

    if (currentMode == static_cast<int>(mode)) {
        return;
    }

    _WaitDrawDone__8CGraphicFPci(&Graphic, const_cast<char*>(kPMenuSourceFile), 0x1B0);

    if (currentMode == 1) {
        destroyWorld();
    } else if (currentMode < 1) {
        if (currentMode != -1 && currentMode > -2) {
            ReleaseRefObject(*reinterpret_cast<void**>(self + 0xFC));
            *reinterpret_cast<void**>(self + 0xFC) = nullptr;

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

            destroySingleMenu__8CMenuPcsFv(this);
            destroyVillageMenu__8CMenuPcsFv(this);
        }
    } else if (currentMode < 3) {
        destroyBonus__8CMenuPcsFv(this);
    }

    *reinterpret_cast<int*>(self + 0x740) = static_cast<int>(mode);
    currentMode = *reinterpret_cast<int*>(self + 0x740);

    if (currentMode == 1) {
        createWorld();
    } else if (currentMode < 1) {
        if (currentMode != -1 && currentMode > -2) {
            createBattle();
            createSingleMenu__8CMenuPcsFv(this);
        }
    } else if (currentMode < 3) {
        createBonus__8CMenuPcsFv(this);
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

    if (mode == 1) {
        CalcDiaryMenu__8CMenuPcsFv(this);
    } else if (mode < 1) {
        if (mode >= 0) {
            for (int i = 0; i < 4; i++) {
                Calc__5CMenuFv(*reinterpret_cast<CMenu**>(self + 0x13c + i * 4));
            }

            for (int i = 0; i < 0xc; i++) {
                Calc__5CMenuFv(*reinterpret_cast<CMenu**>(self + 0x10c + i * 4));
            }

            int limit = *reinterpret_cast<int*>(self + 0x68);
            int value = *reinterpret_cast<int*>(self + 0x6c) - 1;
            if (value <= limit) {
                int alt = *reinterpret_cast<int*>(self + 0x6c) + 1;
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

            calcVillageMenu__8CMenuPcsFv(this);
        }
    } else if (mode < 3) {
        calcBonus__8CMenuPcsFv(this);
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
    Mtx modelMtx;
    Mtx texMtx;
    Mtx44 orthoMtx;
    Mtx44 screenMtx;

    PSMTXIdentity(modelMtx);
    GXLoadPosMtxImm(modelMtx, 0);
    C_MTXOrtho(orthoMtx, kMenuInitOne, kMenuOrthoBottom, kMenuInitOne, kMenuOrthoRight, kMenuInitOne, kMenuOrthoFar);
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
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
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
                drawVillageMenu__8CMenuPcsFv(this);
            }
        } else if (mode < 3) {
            drawBonus__8CMenuPcsFv(this);
        }
    }

    if (((*reinterpret_cast<unsigned int*>(CFlat + 0x12A0) & 0x10) != 0) && (System.m_scenegraphStepMode == 2)) {
        CTexture* texture = *reinterpret_cast<CTexture**>(reinterpret_cast<u8*>(this) + 0x190);
        TextureMan.SetTexture(GX_TEXMAP0, texture);

        if (texture != nullptr) {
            float width = static_cast<float>(*reinterpret_cast<u32*>(reinterpret_cast<u8*>(texture) + 0x64));
            float height = static_cast<float>(*reinterpret_cast<u32*>(reinterpret_cast<u8*>(texture) + 0x68));
            PSMTXScale(texMtx, 1.0f / width, 1.0f / height, 1.0f);
            GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
            GXSetNumTexGens(1);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
        }

        TextureMan.SetTextureTev(texture);

        {
            int alpha = static_cast<int>(127.5f * (1.0f + sinf(System.m_frameCounter * 0.1f)));
            CColor color(0xFF, 0xFF, 0xFF, static_cast<u8>(alpha));
            GXSetChanMatColor(GX_COLOR0A0, color.color);
            DrawRect(3, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
    }

    PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x48), screenMtx);
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
    C_MTXOrtho(orthoMtx, kMenuInitOne, kMenuOrthoBottom, kMenuInitOne, kMenuOrthoRight, kMenuInitOne, kMenuOrthoFar);
    GXSetProjection(orthoMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);

    GXSetChanAmbColor(GX_COLOR0A0, CColor(0xFF, 0xFF, 0xFF, 0xFF).color);

    GXSetZCompLoc(GX_FALSE);
    GXSetCurrentMtx(0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
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
    if ((int)fmt == 1) {
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    } else if ((int)fmt < 1) {
        if ((int)fmt >= 0) {
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
            GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
            GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        }
    } else if ((int)fmt < 3) {
        GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawQuit()
{
	// TODO
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
        return 0;
    }

    u32 clamped = (u32)port & ~((int)~(Pad._448_4_ - port | port - Pad._448_4_) >> 0x1f);
    return *(u16*)((u8*)&Pad + 0x8 + clamped * 0x54);
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
        return 0;
    }

    u32 clamped = (u32)port & ~((int)~(Pad._448_4_ - port | port - Pad._448_4_) >> 0x1f);
    return *(u16*)((u8*)&Pad + 0x14 + clamped * 0x54);
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
        refCount = refObject[1];
        refObject[1] = refCount - 1;
        if ((refCount - 1 == 0) && (refObject != nullptr)) {
            reinterpret_cast<void (*)(void*, int)>(*reinterpret_cast<u32*>(refObject[0] + 8))(refObject, 1);
        }
        *reinterpret_cast<void**>(self + 0x100) = nullptr;
    }

    refObject = *reinterpret_cast<int**>(self + 0x104);
    if (refObject != nullptr) {
        refCount = refObject[1];
        refObject[1] = refCount - 1;
        if ((refCount - 1 == 0) && (refObject != nullptr)) {
            reinterpret_cast<void (*)(void*, int)>(*reinterpret_cast<u32*>(refObject[0] + 8))(refObject, 1);
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
        CTexture** textures = (CTexture**)((u8*)this + 0x18C);
        u32 width;
        u32 height;

        texture = textures[(int)tex];
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
    if ((0.0f < w) && (0.0f < h)) {
        float u0;
        float u1;
        float v0;
        float v1;
        float x0;
        float y0;
        float x1;
        float y1;

        if ((attr & 8) == 0) {
            u0 = u + 0.5f;
            u1 = (u + w) - 0.5f;
        } else {
            u1 = u + 0.5f;
            u0 = (u + w) - 0.5f;
        }

        if ((attr & 4) == 0) {
            v0 = v + 0.5f;
            v1 = (v + h) - 0.5f;
        } else {
            v1 = v + 0.5f;
            v0 = (v1 + h) - 0.5f;
        }

        x0 = x;
        if ((attr & 1) != 0) {
            x0 = -((w * us) * 0.5f - x);
        }

        y0 = y;
        if ((attr & 2) != 0) {
            y0 = -((h * vs) * 0.5f - y);
        }

        x1 = x0 + (w * us);
        y1 = y0 + (h * vs);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        if (0.0f != angle) {
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

            GXPosition3f32(xtl - tx0, ytl + ty0, 0.0f);
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(xtr - tx0, ytr + ty0, 0.0f);
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(xtl - tx1, ytl + ty1, 0.0f);
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(xtr - tx1, ytr + ty1, 0.0f);
            GXTexCoord2f32(u1, v1);
        } else {
            GXPosition3f32(x0, y0, 0.0f);
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(x1, y0, 0.0f);
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(x0, y1, 0.0f);
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(x1, y1, 0.0f);
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
    if ((0.0f < w) && (0.0f < h)) {
        float u0;
        float u1;
        float v0;
        float v1;
        float x0;
        float y0;
        float x1;
        float y1;

        if ((attr & 8) == 0) {
            u0 = u + 0.5f;
            u1 = (u + w) - 0.5f;
        } else {
            u1 = u + 0.5f;
            u0 = (u + w) - 0.5f;
        }

        if ((attr & 4) == 0) {
            v0 = v + 0.5f;
            v1 = (v + h) - 0.5f;
        } else {
            v1 = v + 0.5f;
            v0 = (v1 + h) - 0.5f;
        }

        x0 = x;
        if ((attr & 1) != 0) {
            x0 = -((w * us) * 0.5f - x);
        }

        y0 = y;
        if ((attr & 2) != 0) {
            y0 = -((h * vs) * 0.5f - y);
        }

        x1 = x0 + (w * us);
        y1 = y0 + (h * vs);

        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        if (0.0f != angle) {
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

            GXPosition3f32(xtl - tx0, ytl + ty0, 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[0]));
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(xtr - tx0, ytr + ty0, 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[1]));
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(xtl - tx1, ytl + ty1, 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[2]));
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(xtr - tx1, ytr + ty1, 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[3]));
            GXTexCoord2f32(u1, v1);
        } else {
            GXPosition3f32(x, y, 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[0]));
            GXTexCoord2f32(u0, v0);

            GXPosition3f32(x1, y, 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[1]));
            GXTexCoord2f32(u1, v0);

            GXPosition3f32(x, y1, 0.0f);
            GXColor1u32(*reinterpret_cast<u32*>(&colors[2]));
            GXTexCoord2f32(u0, v1);

            GXPosition3f32(x1, y1, 0.0f);
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
void CMenuPcs::DrawBar(float, float, float, CMenuPcs::TEX, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawWindow(float x, float y, float width, float height, CMenuPcs::TEX texBase, float corner)
{
	if (width <= 0.0f || height <= 0.0f) {
		return;
	}

	const float twoCorner = corner * 2.0f;
	float midW = width - twoCorner;
	float midH = height - twoCorner;
	float overW = twoCorner - width;
	float overH = twoCorner - height;
	float uOff = 0.0f;
	float vOff = 0.0f;
	const int tex = static_cast<int>(texBase);
	const float xL = x;
	const float yT = y;
	const float xM = x + corner;
	const float yM = y + corner;
	const float xR = (x + width) - corner;
	const float yB = (y + height) - corner;

	if (midW < 0.0f) {
		midW = 0.0f;
	}
	if (midH < 0.0f) {
		midH = 0.0f;
	}
	if (overW < 0.0f) {
		overW = 0.0f;
	}
	if (overH < 0.0f) {
		overH = 0.0f;
	}
	if (corner > 0.0f) {
		uOff = overW / twoCorner;
		vOff = overH / twoCorner;
	}

	SetTexture(static_cast<CMenuPcs::TEX>(tex));
	DrawRect(0, xL, yT, corner, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 1));
	DrawRect(0, xM, yT, midW, corner, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 2));
	DrawRect(0, xR, yT, corner, corner, uOff, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 3));
	DrawRect(0, xL, yM, corner, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 4));
	DrawRect(0, xM, yM, midW, midH, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 5));
	DrawRect(0, xR, yM, corner, midH, uOff, 0.0f, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 6));
	DrawRect(0, xL, yB, corner, corner, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 7));
	DrawRect(0, xM, yB, midW, corner, 0.0f, vOff, 1.0f, 1.0f, 0.0f);

	SetTexture(static_cast<CMenuPcs::TEX>(tex + 8));
	DrawRect(0, xR, yB, corner, corner, uOff, vOff, 1.0f, 1.0f, 0.0f);
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
    char* language;
    u8* self = reinterpret_cast<u8*>(this);
    CFont** fontSlot = reinterpret_cast<CFont**>(self + 0x100 + fontNo * 4);
    CFont* font = *fontSlot;
    if (font != 0) {
        u32* raw = reinterpret_cast<u32*>(font);
        int refCount = static_cast<int>(raw[1]);
        raw[1] = static_cast<u32>(refCount - 1);
        if (refCount - 1 == 0) {
            reinterpret_cast<void (*)(void*, int)>(*reinterpret_cast<u32*>(raw[0] + 8))(font, 1);
        }
        *fontSlot = 0;
    }

    language = GetLangString__5CGameFv(&Game);
    sprintf(path, s_dvd__smenu__s_fnt_801d9da0, language, fileName);
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
    u8* self = reinterpret_cast<u8*>(this);
    int slotOffset = fontNo * 4;

    for (int i = 0; i < 0x10; i++) {
        CTexture* texture = *reinterpret_cast<CTexture**>(*reinterpret_cast<u32*>(self + 0x100 + slotOffset) + 0x34);
        _GXColor out = texture->GetTlutColor(i);
        if (i < 9) {
            out.r = color.r;
            out.g = color.g;
            out.b = color.b;
        } else {
            float blend = 1.0f - static_cast<float>(i - 9) / 10.0f;
            out.r = static_cast<u8>(245.0f - (245.0f - static_cast<float>(color.r)) * blend);
            out.g = static_cast<u8>(245.0f - (245.0f - static_cast<float>(color.g)) * blend);
            out.b = static_cast<u8>(245.0f - (245.0f - static_cast<float>(color.b)) * blend);
        }
        texture->SetTlutColor(i, out);
    }

    (*reinterpret_cast<CTexture**>(*reinterpret_cast<u32*>(self + 0x100 + slotOffset) + 0x34))->FlushTlut();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::drawPause()
{
	// TODO
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
    int* textureInfo = sMenuTextureInfoTable;
    u8* self = reinterpret_cast<u8*>(this);

    for (int i = 0; i < 2; i++) {
        const char* language = Game.GetLangString();
        sprintf(path, s_dvd__smenu__s_tex_801d9d6c, language, sMenuTextureRegionNameTable[i]);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            void* stage = *reinterpret_cast<int*>(self + 0x740) == 1 ? *reinterpret_cast<void**>(&MapMng)
                                                                     : *reinterpret_cast<void**>(self + 0xEC);

            CTextureSet* textureSet = new (Game.m_mainStage, const_cast<char*>(kPMenuSourceFile), 0x182) CTextureSet;
            *reinterpret_cast<CTextureSet**>(self + 0x14C + i * 4) = textureSet;
            if (textureSet != 0) {
                textureSet->Create(File.m_readBuffer, reinterpret_cast<CMemory::CStage*>(stage), 0, 0, 0, 0);
            }

            File.Close(fileHandle);
        }
    }

    for (int i = 0; i < 10; i++) {
        CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(self + 0x14C + textureInfo[0] * 4);
        const unsigned long textureIndex = static_cast<unsigned long>(textureSet->Find(reinterpret_cast<char*>(textureInfo[1])));
        CTexture* texture = (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(textureSet) + 8))[textureIndex];
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) =
            *reinterpret_cast<int*>(reinterpret_cast<u8*>(texture) + 4) + 1;
        *reinterpret_cast<CTexture**>(self + 0x1E4 + i * 4) = texture;
        textureInfo += 2;
    }

    for (int i = 0; i < 12; i++) {
        CMesMenu* menu = new (Game.m_mainStage, const_cast<char*>(kPMenuSourceFile), 0x48B) CMesMenu;
        *reinterpret_cast<CMesMenu**>(self + 0x10C + i * 4) = menu;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(menu) + 0x18) = i;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(menu) + 0x1C) = i;
        menu->Create();
    }

    for (int i = 0; i < 4; i++) {
        CRingMenu* menu = new (Game.m_mainStage, const_cast<char*>(kPMenuSourceFile), 0x492) CRingMenu;
        *reinterpret_cast<CRingMenu**>(self + 0x13C + i * 4) = menu;
        *reinterpret_cast<int*>(reinterpret_cast<u8*>(menu) + 8) = i;
        menu->Create();
    }

    sprintf(fontPath, s_dvd__smenu_gc23_fnt_801d9d8c, Game.GetLangString());
    loadFont(0, fontPath, 1, 1);

    CTexture* fontTexture = *reinterpret_cast<CTexture**>(self + 0x1EC);
    for (int i = 0; i < 0x100; i++) {
        _GXColor color = fontTexture->GetTlutColor(i);
        const int avg2 = (((int)color.r + (int)color.g + (int)color.b) / 3) * 2;
        _GXColor outColor;
        outColor.r = static_cast<u8>(((int)color.r + avg2) / 3);
        outColor.g = static_cast<u8>(((int)color.g + avg2) / 3);
        outColor.b = static_cast<u8>(((int)color.b + avg2) / 3);
        outColor.a = color.a;

        const int tlutFmt = *reinterpret_cast<int*>(reinterpret_cast<u8*>(fontTexture) + 0x60);
        int tlutOffset = 0;
        if (tlutFmt == 9) {
            tlutOffset = 0x100;
        } else if (tlutFmt == 8) {
            tlutOffset = 0x10;
        }

        fontTexture->SetExternalTlutColor(self + 0x340, tlutOffset, i, outColor);
    }

    fontTexture->FlushExternalTlut(self + 0x340);
    *reinterpret_cast<u16*>(self + 0x864) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::destroyBattle()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcBattle()
{
	// TODO
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
    u8* self = reinterpret_cast<u8*>(this);

    if (*reinterpret_cast<s32*>(self + 0x48) != 0) {
        const float frame = static_cast<float>(*reinterpret_cast<s32*>(self + 0x58));
        float fade = 1.0f - (frame * 0.05f);
        if (fade < 0.0f) {
            fade = 0.0f;
        }

        Mtx44 screenMtx;
        Vec4d projected;
        PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<u8*>(&CameraPcs) + 0x48), screenMtx);
        Math.MTX44MultVec4(screenMtx, reinterpret_cast<Vec*>(self + 0x4C), &projected);

        if (projected.w > 0.0f) {
            const int totalWidth = static_cast<int>(static_cast<float>(*reinterpret_cast<s32*>(self + 0x60)) * fade);
            const int halfWidth = totalWidth / 2;
            float screenX = 320.0f + (320.0f * projected.x) / projected.w;
            float screenY = 240.0f - (240.0f * projected.y) / projected.w;

            if (screenX < static_cast<float>(halfWidth)) {
                screenX = static_cast<float>(halfWidth);
            } else {
                const float right = 640.0f - static_cast<float>(halfWidth);
                if (screenX > right) {
                    screenX = right;
                }
            }

            if (screenY < 32.0f) {
                screenY = 32.0f;
            } else if (screenY > 448.0f) {
                screenY = 448.0f;
            }

            int fillWidth = 0;
            if (*reinterpret_cast<s32*>(self + 0x64) != 0) {
                fillWidth = ((totalWidth - 16) * *reinterpret_cast<s32*>(self + 0x6C)) /
                            *reinterpret_cast<s32*>(self + 0x64);
            }

            const float left = screenX - static_cast<float>(halfWidth);
            const float bodyLeft = left + 8.0f;
            const float alphaF = 80.0f * fade;
            const u8 alpha = static_cast<u8>(alphaF < 0.0f ? 0.0f : (alphaF > 255.0f ? 255.0f : alphaF));
            const CColor frameColor(0xFF, 0xFF, 0xFF, alpha);
            GXSetChanMatColor(GX_COLOR0A0, frameColor.color);

            if (totalWidth > 0) {
                CTexture* tex = *reinterpret_cast<CTexture**>(self + 0x500);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, left, screenY, 8.0f, 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

                tex = *reinterpret_cast<CTexture**>(self + 0x504);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, bodyLeft, screenY, static_cast<float>(totalWidth - 16), 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

                tex = *reinterpret_cast<CTexture**>(self + 0x508);
                TextureMan.SetTexture(GX_TEXMAP0, tex);
                if (tex != 0) {
                    Mtx texMtx;
                    const u32 width = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x64);
                    const u32 height = *reinterpret_cast<u32*>(reinterpret_cast<u8*>(tex) + 0x68);
                    PSMTXScale(texMtx, 1.0f / static_cast<float>(width), 1.0f / static_cast<float>(height), 1.0f);
                    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
                    GXSetNumTexGens(1);
                    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                }
                TextureMan.SetTextureTev(tex);
                DrawRect(0, (left + static_cast<float>(totalWidth)) - 8.0f, screenY, 8.0f, 8.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
            }

            const u8 gauge = static_cast<u8>((*reinterpret_cast<s32*>(self + 0x5C) * 0xFF) >> 4);
            const CColor fillTop(0xFF, gauge, gauge, alpha);
            GXSetChanMatColor(GX_COLOR0A0, fillTop.color);
            TextureMan.SetTextureTev(0);
            DrawRect(0, bodyLeft, screenY + 1.0f, static_cast<float>(fillWidth), 3.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);

            const u8 gaugeTop = static_cast<u8>(((*reinterpret_cast<s32*>(self + 0x5C) * 0x7F) >> 4) + 0x80);
            const CColor fillBottom(0xFF, gaugeTop, gauge, alpha);
            GXSetChanMatColor(GX_COLOR0A0, fillBottom.color);
            DrawRect(0, bodyLeft, screenY + 4.0f, static_cast<float>(fillWidth), 3.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f);
        }
    }

    for (int i = 0; i < 4; i++) {
        CMenu* menu = *reinterpret_cast<CMenu**>(self + 0x13C + i * 4);
        if (menu != 0) {
            menu->Draw();
        }
    }
    for (int i = 0; i < 12; i++) {
        CMenu* menu = *reinterpret_cast<CMenu**>(self + 0x10C + i * 4);
        if (menu != 0) {
            menu->Draw();
        }
    }
    for (int i = 0; i < 4; i++) {
        CRingMenu* menu = *reinterpret_cast<CRingMenu**>(self + 0x13C + i * 4);
        if (menu != 0) {
            menu->DrawIcon();
        }
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
        destroySingleMenu__8CMenuPcsFv(this);
    }

    Game.m_gameWork.m_menuStageMode = static_cast<u8>(isScriptMode);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetTexture(CMenuPcs::TEX)
{
	// TODO
}
