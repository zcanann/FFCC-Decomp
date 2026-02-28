#include "ffcc/singmenu.h"
#include "ffcc/chara.h"
#include "ffcc/file.h"
#include "ffcc/graphic.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/ptrarray.h"
#include "ffcc/sound.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include <dolphin/gx.h>
#include <dolphin/mtx.h>
#include <string.h>

typedef signed short s16;
typedef unsigned char u8;

extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawFilter__8CMenuPcsFUcUcUcUc(CMenuPcs*, u8, u8, u8, u8);
extern "C" void Draw__9CShopMenuFv(void*);
extern "C" void Calc__9CShopMenuFv(void*);
extern "C" void SingleDrawCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" void SetFrame__Q26CChara6CModelFf(float, CChara::CModel*);
extern "C" void AddFrame__Q26CChara6CModelFf(float, CChara::CModel*);
extern "C" void SetMatrix__Q26CChara6CModelFPA4_f(CChara::CModel*, Mtx);
extern "C" void CalcMatrix__Q26CChara6CModelFv(CChara::CModel*);
extern "C" void CalcSkin__Q26CChara6CModelFv(CChara::CModel*);
extern "C" void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
extern "C" void DestroyTempBuffer__8CGraphicFv(CGraphic*);
extern "C" int GetModelNo__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void* __nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nw__11CTextureSetFUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" CCharaPcs::CHandle* __ct__Q29CCharaPcs7CHandleFv(CCharaPcs::CHandle*);
extern "C" CTextureSet* __ct__11CTextureSetFv(CTextureSet*);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(CTextureSet*, void*, CMemory::CStage*, int, void*, int, int);
extern "C" int Find__11CTextureSetFPc(CTextureSet*, char*);
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void* Open__5CFileFPcUlQ25CFile3PRI(void*, char*, unsigned long, int);
extern "C" void ReadASync__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" int IsCompleted__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" void Close__5CFileFPQ25CFile7CHandle(void*, void*);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void createSingleMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void SingMenuInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void CreateShopMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" void CreateSmithMenu__8CMenuPcsFv(CMenuPcs*);
extern "C" char* s_stand_80332a24;
extern "C" char* s_singmenu_cpp_801de8d4;
extern "C" char* s_dvd__smenu__s_tex_801de8e4;
extern "C" char* PTR_s_solo1_80214b18[];
extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" char* PTR_s_Tutti_802143ec;
extern "C" char* PTR_s_Alle_Rassen_8021430c;
extern "C" char* PTR_s_Todos_802145ac;
extern "C" char* PTR_DAT_802144cc;
extern "C" char* PTR_DAT_8021422c;
extern "C" char* PTR_s_Clavat_80214110[];
extern "C" char* PTR_s_Clavat_802140f0[];
extern "C" char* PTR_s_Clavat_80214100[];
extern "C" char* PTR_s_Clavate_80214130[];
extern "C" char* PTR_s_Clavat_80214120[];
extern "C" char* PTR_s_Maschio_802143e4[];
extern "C" char* PTR_DAT_80214304[];
extern "C" char* PTR_s_Hombre_802145a4[];
extern "C" char* PTR_s_Masculin_802144c4[];
extern "C" char* PTR_DAT_80214224[];
extern "C" char DAT_80332958[];
extern "C" char DAT_8033295c[];
extern "C" u8 lbl_801DE6AC[];
extern "C" char* lbl_80214140[];
extern "C" char* lbl_80214160[];
extern "C" char* lbl_80214180[];
extern "C" char* lbl_802141A0[];
extern "C" char* lbl_802141C0[];
extern "C" char* lbl_802141E0[];
extern "C" char* lbl_802142C0[];
extern "C" char* lbl_802143A0[];
extern "C" char* lbl_80214480[];
extern "C" char* lbl_80214560[];
extern "C" char* lbl_80214640[];
extern "C" char* lbl_802146C0[];
extern "C" char* lbl_80214740[];
extern "C" char* lbl_802147C0[];
extern "C" char* lbl_80214840[];
extern "C" char* lbl_802148C0[];
extern "C" char* lbl_80214910[];
extern "C" char* lbl_80214960[];
extern "C" char* lbl_802149B0[];
extern "C" char* lbl_80214A00[];

extern "C" unsigned int CmdOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CmdClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void CmdDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ItemOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ItemCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ItemClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void ItemDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int EquipOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int EquipCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int EquipClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void EquipDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ArtiOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ArtiCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int ArtiClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void ArtiDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int TmpArtiOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int TmpArtiCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int TmpArtiClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void TmpArtiDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MoneyOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MoneyCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MoneyClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void MoneyDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int FavoOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int FavoCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int FavoClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void FavoDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CompaOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CompaCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int CompaClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void CompaDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int LetterOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int LetterCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int LetterClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void LetterDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MLstOpen__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MLstCtrl__8CMenuPcsFv(CMenuPcs*);
extern "C" unsigned int MLstClose__8CMenuPcsFv(CMenuPcs*);
extern "C" void MLstDraw__8CMenuPcsFv(CMenuPcs*);
extern "C" void CalcHeart__8CMesMenuFv(void*);

extern float FLOAT_8033292c;
extern float FLOAT_80332928;
extern float FLOAT_80332934;
extern float FLOAT_80332940;
extern float FLOAT_80332948;
extern float FLOAT_8033294c;
extern float FLOAT_80332950;
extern float FLOAT_80332970;
extern float FLOAT_803329a4;
extern float FLOAT_803329a8;
extern float FLOAT_803329ac;
extern float FLOAT_803329b0;
extern float FLOAT_803329b4;
extern float FLOAT_803329bc;
extern float FLOAT_803329b8;
extern CUtil DAT_8032ec70;
extern int DAT_8032eeb8;
extern int DAT_8032eebc;
extern int DAT_8032eec0;
extern int DAT_8032eec4;
extern int DAT_80214b3c[];
extern float DAT_801dd708[];
extern float DAT_801dd6f8[];
extern float FLOAT_8032ea78;
extern float FLOAT_803329d0;
extern float FLOAT_803329d4;
extern float FLOAT_803329d8;
extern float FLOAT_803329dc;
extern float FLOAT_803329e8;
extern float FLOAT_803329ec;
extern float FLOAT_803329f0;
extern float FLOAT_803329f4;
extern float FLOAT_803329f8;
extern float FLOAT_803329fc;
extern float FLOAT_80332a00;
extern float FLOAT_80332a04;
extern float FLOAT_80332a08;
extern float FLOAT_80332a0c;
extern float FLOAT_80332a10;
extern float FLOAT_80332a18;
extern float FLOAT_80332a1c;
extern float FLOAT_80332a2c;
extern float FLOAT_80332a48;
extern double DOUBLE_80332938;
extern double DOUBLE_80332968;
extern double DOUBLE_80332978;
extern double DOUBLE_80332980;
extern double DOUBLE_80332988;
extern double DOUBLE_80332a30;
extern double DOUBLE_80332a38;
extern double DOUBLE_80332a40;

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::createSingleMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::destroySingleMenu()
{
	// TODO
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
    u8* self = reinterpret_cast<u8*>(this);

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_singmenu_cpp_801de8d4, 0x5C2);
    DestroyTempBuffer__8CGraphicFv(&Graphic);

    *reinterpret_cast<void**>(self + 0xF4) = *reinterpret_cast<void**>(reinterpret_cast<u8*>(&Graphic) + 8);
    memset(self + 0x85C, 0, 8);
    *reinterpret_cast<void**>(self + 0x774) = 0;

    CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }

    CCharaPcs::CHandle* handle =
        static_cast<CCharaPcs::CHandle*>(__nw__Q29CCharaPcs7CHandleFUlPQ27CMemory6CStagePci(
            0x194, stage, s_singmenu_cpp_801de8d4, 0x5CD));
    if (handle != 0) {
        handle = __ct__Q29CCharaPcs7CHandleFv(handle);
    }
    *reinterpret_cast<CCharaPcs::CHandle**>(self + 0x774) = handle;

    handle->Add();
    int modelNo = GetModelNo__8CMenuPcsFiii(
        this,
        static_cast<int>(*reinterpret_cast<u16*>(Game.game.m_scriptFoodBase[0] + 0x3E0)),
        static_cast<int>(*reinterpret_cast<u16*>(Game.game.m_scriptFoodBase[0] + 0x3E4)),
        static_cast<int>(*reinterpret_cast<u16*>(Game.game.m_scriptFoodBase[0] + 0x3E2)));
    handle->LoadModel(0, static_cast<unsigned long>(modelNo), 0, 0, -1, 0, 0);
    handle->m_flags |= 0x300141;
    handle->LoadAnim(s_stand_80332a24, 0, 1, 0, (handle->m_charaNo / 100) * 100, -1, 0);
    handle->SetAnim(0, -1, -1, -1, 0);

    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }
    *reinterpret_cast<void**>(self + 0x814) = __nwa__FUlPQ27CMemory6CStagePci(0x50, stage, s_singmenu_cpp_801de8d4, 0x5DD);

    int state = *reinterpret_cast<int*>(self + 0x814);
    *reinterpret_cast<float*>(state + 0x24) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x20) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x1C) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x30) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x2C) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x28) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x3C) = FLOAT_80332934;
    *reinterpret_cast<float*>(state + 0x38) = FLOAT_80332934;
    *reinterpret_cast<float*>(state + 0x34) = FLOAT_80332934;
    *reinterpret_cast<int*>(state + 0) = 0;
    *reinterpret_cast<int*>(state + 4) = 0;
    *reinterpret_cast<s16*>(state + 8) = 0;
    *reinterpret_cast<s16*>(state + 10) = 0;
    *reinterpret_cast<s16*>(state + 12) = 0x280;
    *reinterpret_cast<s16*>(state + 14) = 0x1C0;
    *reinterpret_cast<float*>(state + 0x10) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x14) = FLOAT_8033294c;
    *reinterpret_cast<float*>(state + 0x18) = FLOAT_80332a2c;
    *reinterpret_cast<int*>(state + 0x40) = 0;
    *reinterpret_cast<int*>(state + 0x44) = 0;
    *reinterpret_cast<int*>(state + 0x48) = 0x280;
    *reinterpret_cast<int*>(state + 0x4C) = 0x1C0;
    *reinterpret_cast<s16*>(state + 8) = static_cast<s16>(static_cast<int>(
        static_cast<double>(static_cast<float>(DOUBLE_80332a30 + static_cast<double>(FLOAT_803329f4) * DOUBLE_80332968
                + static_cast<double>(FLOAT_803329d4 + FLOAT_803329ec)) - DOUBLE_80332a38) - DOUBLE_80332a30));
    *reinterpret_cast<s16*>(state + 10) = static_cast<s16>(static_cast<int>(
        static_cast<double>(static_cast<float>(static_cast<double>(FLOAT_803329f0) * DOUBLE_80332968
                + static_cast<double>(FLOAT_803329f0))) - DOUBLE_80332a40));
    *reinterpret_cast<int*>(state + 0x40) = static_cast<int>(static_cast<double>(FLOAT_80332a48)
                + static_cast<double>(FLOAT_803329d4 + FLOAT_803329ec));
    *reinterpret_cast<int*>(state + 0x44) = static_cast<int>(FLOAT_80332950);
    *reinterpret_cast<int*>(state + 0x48) = 0x48;
    *reinterpret_cast<int*>(state + 0x4C) = 0x58;

    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }
    *reinterpret_cast<void**>(self + 0x850) = __nw__FUlPQ27CMemory6CStagePci(0x1008, stage, s_singmenu_cpp_801de8d4, 0x605);
    memset(*reinterpret_cast<void**>(self + 0x850), 0, 0x1008);

    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }
    *reinterpret_cast<void**>(self + 0x82C) = __nw__FUlPQ27CMemory6CStagePci(0x48, stage, s_singmenu_cpp_801de8d4, 0x609);
    memset(*reinterpret_cast<void**>(self + 0x82C), 0, 0x48);

    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
    if (Game.game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
    }
    *reinterpret_cast<void**>(self + 0x848) = __nw__FUlPQ27CMemory6CStagePci(0xC, stage, s_singmenu_cpp_801de8d4, 0x60D);
    memset(*reinterpret_cast<void**>(self + 0x848), 0, 0xC);

    *reinterpret_cast<s16*>(self + 0x866) = 0;
    if (DAT_8032eec4 >= 0) {
        *reinterpret_cast<s16*>(self + 0x864) = 8;
        DAT_8032eec4 = -1;
    }
    FLOAT_8032ea78 = FLOAT_803329b8;
    *reinterpret_cast<int*>(self + 0x874) = -1;
    *(self + 0x872) = 1;
    *(self + 0x85A) = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingMenuEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::calcSingleMenu()
{
	// TODO
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
    u8* self = reinterpret_cast<u8*>(this);

    if ((Game.game.m_gameWork.m_menuStageMode != 0) &&
        (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag != 0)) {
        DrawInit__8CMenuPcsFv(this);
        DrawFilter__8CMenuPcsFUcUcUcUc(this, 0, 0, 0, 0xFF);
        DAT_8032ec70.ClearZBufferRect(FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_803329a4);
        DrawInit__8CMenuPcsFv(this);

        unsigned int scriptFoodBase = Game.game.m_scriptFoodBase[0];
        if (scriptFoodBase != 0) {
            u8 menuType = *reinterpret_cast<u8*>(scriptFoodBase + 0xBE0);
            void* shopMenu = *reinterpret_cast<void**>(self + 0x868);
            if (((menuType == 1) || (menuType == 2)) && (shopMenu != 0)) {
                Draw__9CShopMenuFv(shopMenu);
            }
        }

        s16 mode = *reinterpret_cast<s16*>(self + 0x866);
        if (mode == 1) {
            SingleDrawCtrl__8CMenuPcsFv(this);
            return;
        }

        if ((mode == 0) || (mode == 2)) {
            s16* menuData = *reinterpret_cast<s16**>(self + 0x850);
            if (menuData == 0) {
                return;
            }

            s16 count = menuData[0];
            s16* entry = menuData + 4;

            for (s16 i = 0; i < count; i++) {
                if ((i == 0) || (*reinterpret_cast<s16*>(self + 0x864) != 8)) {
                    float alpha = *reinterpret_cast<float*>(entry + 8);

                    if (i == 0) {
                        DrawInit__8CMenuPcsFv(this);
                        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
                        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
                        u8 a = static_cast<u8>(FLOAT_80332940 * alpha);
                        _GXColor color = {0xFF, 0xFF, 0xFF, a};
                        GXSetChanMatColor(GX_COLOR0A0, color);

                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x20);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_80332928,
                                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_8033294c, FLOAT_803329a8, FLOAT_803329a4, FLOAT_80332928,
                                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x28);
                        unsigned int step = 0x20;
                        for (unsigned int y = 0x40; y < 0x180; y += step) {
                            if ((0x180 - y) < step) {
                                step = 0x180 - y;
                            }
                            DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, static_cast<float>(y), FLOAT_803329a4,
                                                             static_cast<float>(step), FLOAT_8033294c, FLOAT_8033294c,
                                                             FLOAT_80332934, FLOAT_80332934, 0.0f);
                        }
                    } else if (i == 1) {
                        DrawInit__8CMenuPcsFv(this);
                        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
                        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
                        _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
                        GXSetChanMatColor(GX_COLOR0A0, white);
                        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x21);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 0, -(FLOAT_803329ac * alpha - FLOAT_803329bc), FLOAT_80332948,
                                                         FLOAT_803329ac, FLOAT_803329b0, FLOAT_8033294c, FLOAT_8033294c,
                                                         alpha, FLOAT_80332934, 0.0f);
                        DrawRect__8CMenuPcsFUlfffffffff(this, 8, FLOAT_803329b4, FLOAT_80332948, FLOAT_803329ac, FLOAT_803329b0,
                                                         FLOAT_8033294c, FLOAT_8033294c, alpha, FLOAT_80332934, 0.0f);
                    } else if (i == 2) {
                        DrawSingleStat(alpha);
                    } else {
                        DrawSingleHelpWim(alpha);
                    }
                }
                entry += 0x20;
            }
        }
    }
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
    u8* self = reinterpret_cast<u8*>(this);

    DAT_8032eec0 = static_cast<int>(*reinterpret_cast<char*>(Game.game.m_scriptFoodBase[0] + 0xBE0) != 0);
    if (Game.game.m_gameWork.m_menuStageMode == 0) {
        if (self[0x859] == 0) {
            return;
        }

        *reinterpret_cast<int*>(self + 0xF0) = 0;
        self[0x859] = 0;
        self[0x85A] = 0;
        return;
    }

    if (self[0x859] == 0) {
        createSingleMenu__8CMenuPcsFv(this);
    }
    if (Game.game.m_gameWork.m_singleShopOrSmithMenuActiveFlag == 0) {
        return;
    }
    if (self[0x85A] == 0) {
        SingMenuInit__8CMenuPcsFv(this);
    }

    if (*reinterpret_cast<char*>(Game.game.m_scriptFoodBase[0] + 0xBE0) == 0) {
        int loadIndex = *reinterpret_cast<int*>(self + 0x85C);
        if (loadIndex < 2) {
            if (*reinterpret_cast<int*>(self + 0x860) == 0) {
                char path[260];
                char* language = GetLangString__5CGameFv(&Game.game);
                sprintf(path, s_dvd__smenu__s_tex_801de8e4, language, PTR_s_solo1_80214b18[loadIndex]);
                DAT_8032eeb8 = reinterpret_cast<int>(Open__5CFileFPcUlQ25CFile3PRI(&File, path, 0, 0));
                ReadASync__5CFileFPQ25CFile7CHandle(&File, reinterpret_cast<void*>(DAT_8032eeb8));
                *reinterpret_cast<int*>(self + 0x860) = *reinterpret_cast<int*>(self + 0x860) + 1;
            } else if (*reinterpret_cast<int*>(self + 0x860) == 1) {
                if (IsCompleted__5CFileFPQ25CFile7CHandle(&File, reinterpret_cast<void*>(DAT_8032eeb8)) == 0) {
                    DAT_8032eebc = 0;
                    goto post_texture_load;
                }

                CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
                if (Game.game.m_gameWork.m_menuStageMode != 0) {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
                }

                CTextureSet* textureSet = static_cast<CTextureSet*>(
                    __nw__11CTextureSetFUlPQ27CMemory6CStagePci(0x24, stage, s_singmenu_cpp_801de8d4, 0x748));
                if (textureSet != 0) {
                    textureSet = __ct__11CTextureSetFv(textureSet);
                }
                *reinterpret_cast<CTextureSet**>(self + 0x160 + loadIndex * 4) = textureSet;

                stage = *reinterpret_cast<CMemory::CStage**>(self + 0xEC);
                if (Game.game.m_gameWork.m_menuStageMode != 0) {
                    stage = *reinterpret_cast<CMemory::CStage**>(self + 0xF4);
                }

                Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(textureSet, File.m_readBuffer, stage, 0, 0, 0, 0);
                Close__5CFileFPQ25CFile7CHandle(&File, reinterpret_cast<void*>(DAT_8032eeb8));
                DAT_8032eeb8 = 0;
                *reinterpret_cast<int*>(self + 0x860) = 0;
                *reinterpret_cast<int*>(self + 0x85C) = *reinterpret_cast<int*>(self + 0x85C) + 1;
            }

            if (*reinterpret_cast<int*>(self + 0x85C) < 2) {
                DAT_8032eebc = 0;
            } else {
                int* mapping = DAT_80214b3c;
                for (int i = 0; i < 0x33; i++) {
                    CTextureSet* set = *reinterpret_cast<CTextureSet**>(self + 0x14C + mapping[0] * 4);
                    int texIdx = Find__11CTextureSetFPc(set, reinterpret_cast<char*>(mapping[1]));
                    CTexture* tex = (*reinterpret_cast<CPtrArray<CTexture*>*>(reinterpret_cast<u8*>(set) + 8))[static_cast<unsigned long>(texIdx)];
                    *reinterpret_cast<CTexture**>(reinterpret_cast<u8*>(this) + 0x240 + i * 4) = tex;
                    *reinterpret_cast<int*>(reinterpret_cast<u8*>(tex) + 4) = *reinterpret_cast<int*>(reinterpret_cast<u8*>(tex) + 4) + 1;
                    mapping += 2;
                }
                DAT_8032eebc = 1;
            }
        } else {
            DAT_8032eebc = 1;
        }
    }

post_texture_load:
    if (*reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 6) != 0) {
        *reinterpret_cast<s16*>(self + 0x866) = *reinterpret_cast<s16*>(self + 0x866) + 1;
        *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 6) = 0;
        *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 4) = 0;
        *(reinterpret_cast<u8*>(*reinterpret_cast<int*>(self + 0x82C)) + 0xB) = 0;
        *(reinterpret_cast<u8*>(*reinterpret_cast<int*>(self + 0x82C)) + 0xD) = 0;
        *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x82C) + 0x10) = 0;
        *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x82C) + 0x22) = 0;
    }

    char menuKind = *reinterpret_cast<char*>(Game.game.m_scriptFoodBase[0] + 0xBE0);
    if (menuKind == 1) {
        if (*reinterpret_cast<void**>(self + 0x868) == 0) {
            CreateShopMenu__8CMenuPcsFv(this);
        } else {
            Calc__9CShopMenuFv(*reinterpret_cast<void**>(self + 0x868));
        }
    } else if (menuKind == 2) {
        if (*reinterpret_cast<void**>(self + 0x868) == 0) {
            CreateSmithMenu__8CMenuPcsFv(this);
        } else {
            Calc__9CShopMenuFv(*reinterpret_cast<void**>(self + 0x868));
        }
    }

    if (DAT_8032eec0 == 0) {
        s16 state = *reinterpret_cast<s16*>(self + 0x866);
        if (state == 1) {
            SingleCalcCtrl();
        } else if (state < 1) {
            if (state >= 0) {
                SingleCalcFadeIn();
            }
        } else if (state < 3) {
            SingleCalcFadeOut();
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingCalcChara(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleBase(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleStat(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleHelpWim(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleCrescent(float, float)
{
	// TODO
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
    u8* self = reinterpret_cast<u8*>(this);
    int fadeState = *reinterpret_cast<int*>(self + 0x850);

    if (*reinterpret_cast<s16*>(fadeState + 4) == 0) {
        Sound.PlaySe(0xE, 0x40, 0x7F, 0);
        memset(reinterpret_cast<void*>(fadeState), 0, 0x1008);

        *reinterpret_cast<int*>(fadeState + 0x2C) = 0;
        *reinterpret_cast<int*>(fadeState + 0x30) = 10;

        int phase = (*reinterpret_cast<s16*>(self + 0x864) == 8) ? 10 : 0;
        *reinterpret_cast<int*>(fadeState + 0x6C) = phase;
        *reinterpret_cast<int*>(fadeState + 0x70) = 10;
        *reinterpret_cast<int*>(fadeState + 0xAC) = phase;
        *reinterpret_cast<int*>(fadeState + 0xB0) = 10;
        *reinterpret_cast<int*>(fadeState + 0xEC) = phase;
        *reinterpret_cast<int*>(fadeState + 0xF0) = 10;

        *reinterpret_cast<s16*>(fadeState + 0) = 4;
        *reinterpret_cast<s16*>(fadeState + 4) = 1;
        *reinterpret_cast<s16*>(fadeState + 6) = 0;
    }

    int completed = 0;
    int ctrlState = *reinterpret_cast<int*>(self + 0x82C);
    ++(*reinterpret_cast<s16*>(ctrlState + 0x22));

    s16 totalEntries = *reinterpret_cast<s16*>(fadeState + 0);
    int frame = static_cast<int>(*reinterpret_cast<s16*>(ctrlState + 0x22));
    u8* entry = reinterpret_cast<u8*>(fadeState + 8);
    for (s16 i = 0; i < totalEntries; i++) {
        int start = *reinterpret_cast<int*>(entry + 0x24);
        int duration = *reinterpret_cast<int*>(entry + 0x28);
        if (start <= frame) {
            if (frame < start + duration) {
                int elapsed = ++(*reinterpret_cast<int*>(entry + 0x20));
                *reinterpret_cast<float*>(entry + 0x10) =
                    static_cast<float>((DOUBLE_80332980 / static_cast<double>(duration)) * static_cast<double>(elapsed));
            } else {
                completed++;
                *reinterpret_cast<float*>(entry + 0x10) = FLOAT_80332934;
            }
        }
        entry += 0x40;
    }

    CChara::CModel* model = *reinterpret_cast<CChara::CModel**>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    if (*reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x10) <=
        *reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x08)) {
        SetFrame__Q26CChara6CModelFf(FLOAT_8033294c, model);
    } else {
        AddFrame__Q26CChara6CModelFf(FLOAT_80332934, model);
    }

    unsigned short modelScaleIndex = *reinterpret_cast<unsigned short*>(Game.game.m_scriptFoodBase[0] + 0x3E0);
    float modelScale = DAT_801dd708[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = DAT_801dd6f8[modelScaleIndex];
    scaleMtx[0][3] = FLOAT_8033294c;
    scaleMtx[2][3] = FLOAT_8033294c;

    int modelPtr = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    *reinterpret_cast<u8*>(modelPtr + 0x10C) = (*reinterpret_cast<u8*>(modelPtr + 0x10C) & 0x7F) | 0x80;
    SetMatrix__Q26CChara6CModelFPA4_f(model, scaleMtx);
    CalcMatrix__Q26CChara6CModelFv(model);
    CalcSkin__Q26CChara6CModelFv(model);

    if (totalEntries == completed) {
        *reinterpret_cast<s16*>(fadeState + 6) = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawFadeIn()
{
	// TODO
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
    u8* self = reinterpret_cast<u8*>(this);
    int fadeState = *reinterpret_cast<int*>(self + 0x850);

    if (*reinterpret_cast<s16*>(fadeState + 4) == 0) {
        Sound.PlaySe(0xF, 0x40, 0x7F, 0);
        memset(reinterpret_cast<void*>(fadeState), 0, 0x1008);

        *reinterpret_cast<int*>(fadeState + 0x2C) =
            (*reinterpret_cast<s16*>(self + 0x864) == 8) ? 10 : 0;
        *reinterpret_cast<int*>(fadeState + 0x30) = 10;

        *reinterpret_cast<int*>(fadeState + 0x6C) = 0;
        *reinterpret_cast<int*>(fadeState + 0x70) = 10;
        *reinterpret_cast<int*>(fadeState + 0xAC) = 0;
        *reinterpret_cast<int*>(fadeState + 0xB0) = 10;
        *reinterpret_cast<int*>(fadeState + 0xEC) = 0;
        *reinterpret_cast<int*>(fadeState + 0xF0) = 10;

        *reinterpret_cast<s16*>(fadeState + 0) = 4;
        *reinterpret_cast<s16*>(fadeState + 6) = 0;
        *reinterpret_cast<s16*>(fadeState + 4) = 1;
    }

    int completed = 0;
    int ctrlState = *reinterpret_cast<int*>(self + 0x82C);
    ++(*reinterpret_cast<s16*>(ctrlState + 0x22));

    int totalEntries = static_cast<int>(*reinterpret_cast<s16*>(fadeState + 0));
    s16* entry = reinterpret_cast<s16*>(fadeState + 8);
    int frame = static_cast<int>(*reinterpret_cast<s16*>(ctrlState + 0x22));
    for (int i = 0; i < totalEntries; i++) {
        int start = *reinterpret_cast<int*>(entry + 0x12);
        if (frame < start) {
            *reinterpret_cast<float*>(entry + 8) = FLOAT_80332934;
        } else {
            int duration = *reinterpret_cast<int*>(entry + 0x14);
            if (frame < start + duration) {
                int elapsed = ++(*reinterpret_cast<int*>(entry + 0x10));
                *reinterpret_cast<float*>(entry + 8) =
                    static_cast<float>(-((DOUBLE_80332980 / static_cast<double>(duration)) *
                                          static_cast<double>(elapsed) - DOUBLE_80332980));
            } else {
                completed++;
                *reinterpret_cast<float*>(entry + 8) = FLOAT_8033294c;
            }
        }
        entry += 0x20;
    }

    CChara::CModel* model = *reinterpret_cast<CChara::CModel**>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    if (*reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x10) <=
        *reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x08)) {
        SetFrame__Q26CChara6CModelFf(FLOAT_8033294c, model);
    } else {
        AddFrame__Q26CChara6CModelFf(FLOAT_80332934, model);
    }

    unsigned short modelScaleIndex = *reinterpret_cast<unsigned short*>(Game.game.m_scriptFoodBase[0] + 0x3E0);
    float modelScale = DAT_801dd708[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = DAT_801dd6f8[modelScaleIndex];
    scaleMtx[0][3] = FLOAT_8033294c;
    scaleMtx[2][3] = FLOAT_8033294c;

    int modelPtr = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    *reinterpret_cast<u8*>(modelPtr + 0x10C) = (*reinterpret_cast<u8*>(modelPtr + 0x10C) & 0x7F) | 0x80;
    SetMatrix__Q26CChara6CModelFPA4_f(model, scaleMtx);
    CalcMatrix__Q26CChara6CModelFv(model);
    CalcSkin__Q26CChara6CModelFv(model);

    if (totalEntries == completed) {
        *reinterpret_cast<s16*>(fadeState + 6) = 1;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingleDrawFadeOut()
{
	// TODO
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
    u8* self = reinterpret_cast<u8*>(this);

    if (DAT_8032eebc == 0) {
        return;
    }

    int statePtr = *reinterpret_cast<int*>(self + 0x82C);
    if ((self[0x872] != 0) && (*reinterpret_cast<s16*>(statePtr + 0x10) != 0)) {
        self[0x872] = 0;
    }

    unsigned short result = 0;
    CChara::CModel* model = *reinterpret_cast<CChara::CModel**>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    if (*reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x10) <=
        *reinterpret_cast<float*>(reinterpret_cast<u8*>(model) + 0x08)) {
        SetFrame__Q26CChara6CModelFf(FLOAT_8033294c, model);
    } else {
        AddFrame__Q26CChara6CModelFf(FLOAT_80332934, model);
    }

    unsigned short modelScaleIndex = *reinterpret_cast<unsigned short*>(Game.game.m_scriptFoodBase[0] + 0x3E0);
    float modelScale = DAT_801dd708[modelScaleIndex];
    Mtx scaleMtx;
    PSMTXScale(scaleMtx, modelScale, modelScale, modelScale);
    scaleMtx[1][3] = DAT_801dd6f8[modelScaleIndex];
    scaleMtx[0][3] = FLOAT_8033294c;
    scaleMtx[2][3] = FLOAT_8033294c;

    int modelPtr = *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x774) + 0x168);
    *reinterpret_cast<u8*>(modelPtr + 0x10C) = (*reinterpret_cast<u8*>(modelPtr + 0x10C) & 0x7F) | 0x80;
    SetMatrix__Q26CChara6CModelFPA4_f(model, scaleMtx);
    CalcMatrix__Q26CChara6CModelFv(model);
    CalcSkin__Q26CChara6CModelFv(model);

    s16 mode = *reinterpret_cast<s16*>(self + 0x864);
    s16 proc = *reinterpret_cast<s16*>(statePtr + 0x10);
    switch (mode) {
    case 0:
        result = (proc == 0) ? CmdOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? CmdCtrl__8CMenuPcsFv(this) : CmdClose__8CMenuPcsFv(this));
        break;
    case 1:
        result = (proc == 0) ? ItemOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? ItemCtrl__8CMenuPcsFv(this) : ItemClose__8CMenuPcsFv(this));
        if (*reinterpret_cast<int*>(self + 0x874) >= 0) {
            ++(*reinterpret_cast<int*>(self + 0x874));
            if (*reinterpret_cast<int*>(self + 0x874) > 0x31) {
                *reinterpret_cast<int*>(self + 0x874) = -1;
            }
        }
        break;
    case 2:
        result = (proc == 0) ? EquipOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? EquipCtrl__8CMenuPcsFv(this) : EquipClose__8CMenuPcsFv(this));
        break;
    case 3:
        result = (proc == 0) ? ArtiOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? ArtiCtrl__8CMenuPcsFv(this) : ArtiClose__8CMenuPcsFv(this));
        break;
    case 4:
        result = (proc == 0) ? TmpArtiOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? TmpArtiCtrl__8CMenuPcsFv(this) : TmpArtiClose__8CMenuPcsFv(this));
        break;
    case 5:
        result = (proc == 0) ? MoneyOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? MoneyCtrl__8CMenuPcsFv(this) : MoneyClose__8CMenuPcsFv(this));
        break;
    case 6:
        result = (proc == 0) ? FavoOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? FavoCtrl__8CMenuPcsFv(this) : FavoClose__8CMenuPcsFv(this));
        break;
    case 7:
        result = (proc == 0) ? CompaOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? CompaCtrl__8CMenuPcsFv(this) : CompaClose__8CMenuPcsFv(this));
        break;
    case 8:
        result = (proc == 0) ? LetterOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? LetterCtrl__8CMenuPcsFv(this) : LetterClose__8CMenuPcsFv(this));
        break;
    case 9:
        result = (proc == 0) ? MLstOpen__8CMenuPcsFv(this)
                             : ((proc == 1) ? MLstCtrl__8CMenuPcsFv(this) : MLstClose__8CMenuPcsFv(this));
        break;
    }

    CalcHeart__8CMesMenuFv(*reinterpret_cast<void**>(self + 0x268));
    *reinterpret_cast<unsigned short*>(statePtr + 0x2E) = result;

    bool hasInput = (Pad._452_4_ != 0) || (Pad._448_4_ != -1);
    unsigned short press;
    if (hasInput) {
        press = 0;
    } else {
        __cntlzw((unsigned int)Pad._448_4_);
        press = Pad._8_2_;
    }

    if ((press & 0x800) != 0) {
        *reinterpret_cast<unsigned short*>(*reinterpret_cast<int*>(self + 0x850) + 6) = 1;
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
    u8* self = reinterpret_cast<u8*>(this);

    DrawInit__8CMenuPcsFv(this);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, white);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x20);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, FLOAT_8033294c, FLOAT_803329a4, FLOAT_80332928,
                                     FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 4, FLOAT_8033294c, FLOAT_803329a8, FLOAT_803329a4, FLOAT_80332928,
                                     FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x28);
    unsigned int step = 0x20;
    for (unsigned int y = 0x40; y < 0x180; y += step) {
        if ((0x180 - y) < step) {
            step = 0x180 - y;
        }

        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033294c, static_cast<float>(y), FLOAT_803329a4,
                                         static_cast<float>(step), FLOAT_8033294c, FLOAT_8033294c,
                                         FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    if (*reinterpret_cast<s16*>(self + 0x864) != 8) {
        DrawInit__8CMenuPcsFv(this);
        GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
        SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
        GXSetChanMatColor(GX_COLOR0A0, white);
        SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x21);
        DrawRect__8CMenuPcsFUlfffffffff(this, 0, FLOAT_8033292c, FLOAT_80332948, FLOAT_803329ac, FLOAT_803329b0,
                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
        DrawRect__8CMenuPcsFUlfffffffff(this, 8, FLOAT_803329b4, FLOAT_80332948, FLOAT_803329ac, FLOAT_803329b0,
                                         FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
        DrawSingleStat(FLOAT_80332934);
        DrawSingleHelpWim(FLOAT_80332934);
    }

    if (DAT_8032eebc == 0) {
        return;
    }

    switch (*reinterpret_cast<s16*>(self + 0x864)) {
    case 0:
        CmdDraw__8CMenuPcsFv(this);
        break;
    case 1:
        ItemDraw__8CMenuPcsFv(this);
        break;
    case 2:
        EquipDraw__8CMenuPcsFv(this);
        break;
    case 3:
        ArtiDraw__8CMenuPcsFv(this);
        break;
    case 4:
        TmpArtiDraw__8CMenuPcsFv(this);
        break;
    case 5:
        MoneyDraw__8CMenuPcsFv(this);
        break;
    case 6:
        FavoDraw__8CMenuPcsFv(this);
        break;
    case 7:
        CompaDraw__8CMenuPcsFv(this);
        break;
    case 8:
        LetterDraw__8CMenuPcsFv(this);
        break;
    case 9:
        MLstDraw__8CMenuPcsFv(this);
        break;
    }

    int statePtr = *reinterpret_cast<int*>(self + 0x82C);
    if (*reinterpret_cast<s16*>(statePtr + 0x2E) == 0) {
        return;
    }

    if (*reinterpret_cast<s16*>(statePtr + 0x10) < 2) {
        ++(*reinterpret_cast<s16*>(statePtr + 0x10));
        *reinterpret_cast<s16*>(statePtr + 0x22) = 0;
        *reinterpret_cast<u8*>(statePtr + 0xB) = 0;
        *reinterpret_cast<s16*>(statePtr + 0x2E) = 0;
        return;
    }

    s16 previousMode = 0;
    if (*reinterpret_cast<u8*>(statePtr + 0xD) == 0) {
        s16 mode = *reinterpret_cast<s16*>(self + 0x864);
        if (mode == 9) {
            *reinterpret_cast<s16*>(self + 0x864) = *reinterpret_cast<s16*>(statePtr + 0x26);
        } else if ((mode == 8) && (DAT_8032eec4 >= 0)) {
            *reinterpret_cast<s16*>(self + 0x864) = static_cast<s16>(DAT_8032eec4);
        } else if ((mode == 8) || (DAT_8032eec4 < 0)) {
            if (*reinterpret_cast<s16*>(statePtr + 0x1E) < 1) {
                --(*reinterpret_cast<s16*>(self + 0x864));
                if (*reinterpret_cast<s16*>(self + 0x864) < 0) {
                    *reinterpret_cast<s16*>(self + 0x864) = 8;
                }
            } else {
                ++(*reinterpret_cast<s16*>(self + 0x864));
                if (*reinterpret_cast<s16*>(self + 0x864) > 8) {
                    *reinterpret_cast<s16*>(self + 0x864) = 0;
                }
            }
        } else {
            *reinterpret_cast<s16*>(self + 0x864) = 8;
        }
    } else {
        s16 mode = *reinterpret_cast<s16*>(self + 0x864);
        if (mode == 9) {
            *reinterpret_cast<s16*>(*reinterpret_cast<int*>(self + 0x850) + 6) = 1;
        } else {
            *reinterpret_cast<s16*>(self + 0x864) = 9;
            previousMode = mode;
        }
    }

    memset(reinterpret_cast<void*>(statePtr), 0, 0x48);
    FLOAT_8032ea78 = FLOAT_803329b8;
    *reinterpret_cast<s16*>(statePtr + 0x26) = previousMode;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingleIcon(int, int, int, float, int, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawShadowFont(CFont*, char*, float, float, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawNoShadowFont(CFont*, char*, float, float, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetItemType(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcListPos(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawListPosMark(float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::EquipChk(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawEquipMark(int, int, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80146adc
 * PAL Size: 1500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::DrawSingWin(short mode)
{
    u8* self = reinterpret_cast<u8*>(this);
    s16* win = *reinterpret_cast<s16**>(self + 0x848);

    if (mode >= 0 && win[5] != mode) {
        win[5] = mode;
    }

    if (win[5] == 3) {
        return;
    }

    float left = static_cast<float>(win[0]) + static_cast<float>(win[2]) * 0.5f;
    float top = static_cast<float>(win[1]) + static_cast<float>(win[3]) * 0.5f;
    float width;
    float height;

    if (win[5] == 1) {
        left = static_cast<float>(win[0]);
        top = static_cast<float>(win[1]);
        width = static_cast<float>(win[2]);
        height = static_cast<float>(win[3]);
    } else {
        float leftScale = (((left - static_cast<float>(win[0])) - FLOAT_8033292c) / FLOAT_80332970) * static_cast<float>(win[4]);
        float topScale = (((top - static_cast<float>(win[1])) - FLOAT_8033292c) / FLOAT_80332970) * static_cast<float>(win[4]);
        left = (left - FLOAT_8033292c) - leftScale;
        width = static_cast<float>(DOUBLE_80332978 * static_cast<double>(FLOAT_8033292c + leftScale));
        height = static_cast<float>(DOUBLE_80332978 * static_cast<double>(FLOAT_8033292c + topScale));
        top = (top - FLOAT_8033292c) - topScale;
    }

    int leftPx = static_cast<int>(static_cast<double>(left) - DOUBLE_80332968);
    int topPx = static_cast<int>(static_cast<double>(top) - DOUBLE_80332968);
    int widthPx = static_cast<int>(static_cast<double>(width) - DOUBLE_80332980);
    int heightPx = static_cast<int>(static_cast<double>(height) - DOUBLE_80332980);

    float x0 = static_cast<float>(leftPx);
    float y0 = static_cast<float>(topPx);
    float w = static_cast<float>(widthPx);
    float h = static_cast<float>(heightPx);
    float x1 = x0 + w - FLOAT_8033292c;
    float y1 = y0 + h - FLOAT_8033292c;

    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, white);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x3F);
    for (unsigned long i = 0; i < 4; i++) {
        unsigned long uvFlag = 0;
        float x = x0;
        float y = y0;
        if ((i & 1) != 0) {
            uvFlag = 8;
            x = x1;
        }
        if ((i & 2) != 0) {
            uvFlag |= 4;
            y = y1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, x, y, FLOAT_8033292c, FLOAT_8033292c, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x41);
    float innerW = w - static_cast<float>(DOUBLE_80332988);
    float innerX = FLOAT_8033292c + x0;
    for (int i = 0; i < 2; i++) {
        unsigned long uvFlag = 0;
        float y = y0;
        if (i != 0) {
            uvFlag = 4;
            y = y1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, innerX, y, innerW, FLOAT_8033292c, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x40);
    float innerH = h - static_cast<float>(DOUBLE_80332988);
    float innerY = FLOAT_8033292c + y0;
    for (int i = 0; i < 2; i++) {
        unsigned long uvFlag = 0;
        float x = x0;
        if (i != 0) {
            uvFlag = 8;
            x = x1;
        }
        DrawRect__8CMenuPcsFUlfffffffff(this, uvFlag, x, innerY, FLOAT_8033292c, innerH, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x42);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, innerX, innerY, innerW, innerH, FLOAT_8033294c, FLOAT_8033294c, FLOAT_80332934, FLOAT_80332934, 0.0f);

    int winStatePtr = *reinterpret_cast<int*>(self + 0x848);
    s16 state = *reinterpret_cast<s16*>(winStatePtr + 10);
    if (state == 0) {
        *reinterpret_cast<s16*>(winStatePtr + 8) = *reinterpret_cast<s16*>(winStatePtr + 8) + 1;
        if (*reinterpret_cast<s16*>(winStatePtr + 8) > 5) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 6;
            *reinterpret_cast<s16*>(winStatePtr + 10) = 1;
        }
    } else if (state == 1) {
        if (*reinterpret_cast<s16*>(winStatePtr + 8) != 6) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 6;
        }
    } else if (state == 2) {
        *reinterpret_cast<s16*>(winStatePtr + 8) = *reinterpret_cast<s16*>(winStatePtr + 8) - 1;
        if (*reinterpret_cast<s16*>(winStatePtr + 8) < 1) {
            *reinterpret_cast<s16*>(winStatePtr + 8) = 0;
            *reinterpret_cast<s16*>(winStatePtr + 10) = 3;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingWinMess(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetSingWinSize(int, short*, short*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingWinInfo(int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingDynamicWinMessInfo(int, char*, char*, char*, char*, char*, char*, char*, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SetSingWinScl(float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetSingWinScl()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingWinMessHeight()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::ChkEquipPossible(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetEquipType(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetSmithItem(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::GetRecipeMaterial(int, CMenuPcs::MaterialInfo*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80145c84
 * PAL Size: 748b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::GetRaceStr(int itemNo, char* outText)
{
    unsigned short raceBits;
    unsigned int raceType;
    char* text;
    char* suffix;
    unsigned char languageId;

    GetItemType__8CMenuPcsFii(this, itemNo, 1);
    raceBits = *reinterpret_cast<unsigned short*>(Game.game.unkCFlatData0[2] + itemNo * 0x48 + 4);
    outText[0] = '\0';

    languageId = static_cast<unsigned char>(Game.game.m_gameWork.m_languageId);
    if ((raceBits & 0xF) == 0xF) {
        text = PTR_s_Tutti_802143ec;
        if (languageId != 3) {
            if (languageId < 3) {
                if (languageId != 1 && languageId != 0) {
                    text = PTR_s_Alle_Rassen_8021430c;
                }
            } else {
                text = PTR_s_Todos_802145ac;
                if (languageId != 5 && languageId >= 5) {
                    text = PTR_DAT_8021422c;
                } else if (languageId < 5) {
                    text = PTR_DAT_802144cc;
                }
            }
        }
        strcpy(outText, text);
        return;
    }

    raceType = 0;
    if ((raceBits & 1) == 0) {
        raceType = 1;
        if ((raceBits & 2) == 0) {
            raceType = 2;
            if ((raceBits & 4) == 0) {
                raceType = 3;
                if ((raceBits & 8) == 0) {
                    raceType = 4;
                }
            }
        }
    }

    if (raceType < 4) {
        if (languageId == 3) {
            text = PTR_s_Clavat_80214110[raceType];
        } else if (languageId < 3) {
            if (languageId == 1 || languageId == 0) {
                text = PTR_s_Clavat_802140f0[raceType];
            } else {
                text = PTR_s_Clavat_80214100[raceType];
            }
        } else if (languageId == 5) {
            text = PTR_s_Clavate_80214130[raceType];
        } else if (languageId < 5) {
            text = PTR_s_Clavat_80214120[raceType];
        } else {
            text = PTR_s_Clavat_802140f0[raceType];
        }

        strcpy(outText, text);
        if (languageId == 2) {
            strcat(outText, DAT_80332958, 0x80);
        }
    }

    if ((raceBits & 0xF) != 0 && (raceBits & 0x30) != 0) {
        strcpy(outText, DAT_8033295c);
    }
    if ((raceBits & 0x30) == 0) {
        return;
    }

    suffix = 0;
    raceType = (raceBits & 0x30) >> 5;
    if (languageId == 3) {
        suffix = PTR_s_Maschio_802143e4[raceType];
    } else if (languageId < 3) {
        if (languageId != 1 && languageId != 0) {
            suffix = PTR_DAT_80214304[raceType];
        }
    } else if (languageId == 5) {
        suffix = PTR_s_Hombre_802145a4[raceType];
    } else if (languageId < 5) {
        suffix = PTR_s_Masculin_802144c4[raceType];
    }

    if (suffix == 0) {
        suffix = PTR_DAT_80214224[raceType];
    }
    strcat(outText, suffix, 0x80);
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
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_SET);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

    unsigned char alphaU8 = static_cast<unsigned char>(FLOAT_80332940 * alpha);
    _GXColor color = {0xFF, 0xFF, 0xFF, alphaU8};
    GXSetChanMatColor(GX_COLOR0A0, color);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x53);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, static_cast<float>(x), static_cast<float>(y), 16.0f,
                                    FLOAT_80332948, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 8, static_cast<float>(x + 0x60), static_cast<float>(y), 16.0f,
                                    FLOAT_80332948, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, 0x54);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, static_cast<float>(x + 0x10), static_cast<float>(y),
                                    FLOAT_80332950, FLOAT_80332948, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);

    int tex = 0x55;
    if (value < 0x29) {
        tex = 0x59;
    } else if (value < 0x3D) {
        tex = 0x57;
    }

    int bars = value / 10 + (value >> 31);
    bars -= bars >> 31;
    if (value != bars * 10) {
        ++bars;
    }

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
    int barY = y + 8;
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, static_cast<float>(x + 0x10), static_cast<float>(barY),
                                    4.0f, 8.0f, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);
    DrawRect__8CMenuPcsFUlfffffffff(this, 8, static_cast<float>(x + 0x10 + bars * 8 - 4), static_cast<float>(barY),
                                    4.0f, 8.0f, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);

    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex + 1);
    DrawRect__8CMenuPcsFUlfffffffff(this, 0, static_cast<float>(x + 0x14), static_cast<float>(barY),
                                    static_cast<float>(bars * 8 - 8), 8.0f, FLOAT_8033294c, FLOAT_8033294c,
                                    FLOAT_80332934, FLOAT_80332934, 0.0f);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingSetLetterAttachflg(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingGetLetterAttachflg()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::CalcSingLife()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::DrawSingLife()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingLifeInit(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMenuPcs::SingLifeResetWait()
{
	// TODO
}

static inline char* GetLanguageTableString(int index, char** englishTable, char** germanTable, char** italianTable,
                                           char** frenchTable, char** spanishTable)
{
    u8 languageId = Game.game.m_gameWork.m_languageId;
    if (languageId == 3) {
        return italianTable[index];
    }
    if (languageId < 3) {
        if ((languageId != 1) && (languageId != 0)) {
            return germanTable[index];
        }
    } else {
        if (languageId == 5) {
            return spanishTable[index];
        }
        if (languageId < 5) {
            return frenchTable[index];
        }
    }
    return englishTable[index];
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
char* CMenuPcs::GetTribeStr(int index)
{
    return GetLanguageTableString(index, PTR_s_Clavat_802140f0, PTR_s_Clavat_80214100, PTR_s_Clavat_80214110,
                                  PTR_s_Clavat_80214120, PTR_s_Clavate_80214130);
}

/*
 * --INFO--
 * PAL Address: 0x801455d8
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetJobStr(int index)
{
    return GetLanguageTableString(index, lbl_80214140, lbl_80214160, lbl_80214180, lbl_802141A0, lbl_802141C0);
}

/*
 * --INFO--
 * PAL Address: 0x8014553c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetHairStr(int index)
{
    return GetLanguageTableString(index, lbl_80214640, lbl_802146C0, lbl_80214740, lbl_802147C0, lbl_80214840);
}

/*
 * --INFO--
 * PAL Address: 0x801454a0
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetMenuStr(int index)
{
    return GetLanguageTableString(index, lbl_802141E0, lbl_802142C0, lbl_802143A0, lbl_80214480, lbl_80214560);
}

/*
 * --INFO--
 * PAL Address: 0x80145404
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char* CMenuPcs::GetAttrStr(int index)
{
    return GetLanguageTableString(index, lbl_802148C0, lbl_80214910, lbl_80214960, lbl_802149B0, lbl_80214A00);
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
u8 CMenuPcs::GetItemIcon(int index)
{
    return lbl_801DE6AC[index];
}
