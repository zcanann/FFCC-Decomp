#include "ffcc/menu_item.h"
#include "ffcc/fontman.h"
#include "ffcc/pad.h"
#include "ffcc/p_game.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include <string.h>

typedef signed short s16;
typedef unsigned char u8;
typedef unsigned short u16;

extern "C" int SingGetLetterAttachflg__8CMenuPcsFv(CMenuPcs*);
extern "C" void LetterSetAttachItem__8CMenuPcsFUii(CMenuPcs*, unsigned int, unsigned int);
extern "C" int EquipChk__8CMenuPcsFi(CMenuPcs*, int);
extern "C" int GetItemType__8CMenuPcsFii(CMenuPcs*, int, int);
extern "C" int CanPlayerUseItem__12CCaravanWorkFv(void*);
extern "C" int CanPlayerPutItem__12CCaravanWorkFv(void*);
extern "C" void GetSingWinSize__8CMenuPcsFiPsPsi(CMenuPcs*, int, s16*, s16*, int);
extern "C" void SetSingWinInfo__8CMenuPcsFiiii(CMenuPcs*, int, int, int, int);
extern "C" void FGUseItem__12CCaravanWorkFii(void*, int, int);
extern "C" void SingLifeInit__8CMenuPcsFi(CMenuPcs*, int);
extern "C" void CalcStatus__12CCaravanWorkFv(void*);
extern "C" void FGPutItem__12CCaravanWorkFii(void*, int, int);
extern "C" void DeleteItemIdx__12CCaravanWorkFii(void*, int, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(CMenuPcs*, int);
extern "C" void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(CMenuPcs*, int);
extern "C" void DrawRect__8CMenuPcsFUlfffffffff(CMenuPcs*, unsigned long, float, float, float, float, float, float, float, float, float);
extern "C" void DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(CMenuPcs*, unsigned long, float, float, float, float, float, float, GXColor*, float, float, float);
extern "C" void DrawSingleIcon__8CMenuPcsFiiifif(CMenuPcs*, int, int, int, float, int, float);
extern "C" float CalcListPos__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" void DrawListPosMark__8CMenuPcsFfff(CMenuPcs*, float, float, float);
extern "C" void DrawSingWin__8CMenuPcsFs(CMenuPcs*, short);
extern "C" void DrawSingWinMess__8CMenuPcsFiii(CMenuPcs*, int, int, int);
extern "C" int SingWinMessHeight__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawCursor__8CMenuPcsFiif(CMenuPcs*, int, int, float);
extern "C" void DrawInit__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawSingLife__8CMenuPcsFv(CMenuPcs*);
extern "C" void DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(CMenuPcs*, int, CFont*, int, int, GXColor, int, float, float);
extern "C" void DrawEquipMark__8CMenuPcsFiif(CMenuPcs*, int, int, float);

extern "C" void SetMargin__5CFontFf(float, CFont*);
extern "C" void SetShadow__5CFontFi(CFont*, int);
extern "C" void SetScale__5CFontFf(float, CFont*);
extern "C" void DrawInit__5CFontFv(CFont*);
extern "C" void SetColor__5CFontF8_GXColor(CFont*, GXColor*);
extern "C" int GetWidth__5CFontFPc(CFont*, const char*);
extern "C" void SetPosX__5CFontFf(float, CFont*);
extern "C" void SetPosY__5CFontFf(float, CFont*);
extern "C" void Draw__5CFontFPc(CFont*, const char*);

extern double DOUBLE_80332ea0;
extern float FLOAT_80332e60;
extern float FLOAT_80332e64;
extern double DOUBLE_80332e68;
extern float FLOAT_80332e70;
extern float FLOAT_80332e74;
extern double DOUBLE_80332e78;
extern float FLOAT_80332e80;
extern float FLOAT_80332e84;
extern float FLOAT_80332e88;
extern float FLOAT_80332e8c;
extern float FLOAT_80332e90;
extern float FLOAT_80332e94;

struct MenuItemOpenAnim {
    s16 x;
    s16 y;
    s16 w;
    s16 h;
    float alpha;
    float scale;
    int frame;
    int duration;
    unsigned int flags;
    float progress;
    float dx;
    float dy;
    float targetX;
    float targetY;
};

struct ItemFlatTableEntry {
    int count;
    const char** index;
    char* buffer;
};

struct ItemFlatData {
    char pad[0x6C];
    ItemFlatTableEntry table[8];
};

/*
 * --INFO--
 * PAL Address: 0x8015aeb0
 * PAL Size: 680b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemInit()
{
    float fVar2;
    float fVar3;
    float fVar4;
    int iVar5;
    s16 sVar6;
    s16 sVar7;
    s16* psVar8;
    int iVar9;
    int iVar10;
    int iVar11;

    memset(*(void**)((u8*)this + 0x850), 0, 0x1008);
    fVar2 = FLOAT_80332e64;
    iVar5 = *(int*)((u8*)this + 0x850) + 8;
    iVar10 = 8;
    do {
        *(float*)(iVar5 + 0x14) = fVar2;
        *(float*)(iVar5 + 0x54) = fVar2;
        *(float*)(iVar5 + 0x94) = fVar2;
        *(float*)(iVar5 + 0xD4) = fVar2;
        *(float*)(iVar5 + 0x114) = fVar2;
        *(float*)(iVar5 + 0x154) = fVar2;
        *(float*)(iVar5 + 0x194) = fVar2;
        *(float*)(iVar5 + 0x1D4) = fVar2;
        iVar5 += 0x200;
        iVar10 -= 1;
    } while (iVar10 != 0);
    iVar5 = *(int*)((u8*)this + 0x850);
    *(int*)(iVar5 + 0x24) = 0x2E;
    *(s16*)(iVar5 + 8) = 0x68;
    *(s16*)(iVar5 + 0xA) = 0x28;
    *(s16*)(iVar5 + 0xC) = 0x78;
    fVar2 = FLOAT_80332e60;
    *(s16*)(iVar5 + 0xE) = 0x108;
    fVar4 = FLOAT_80332e60;
    *(float*)(iVar5 + 0x10) = fVar2;
    fVar3 = FLOAT_80332e64;
    *(float*)(iVar5 + 0x14) = fVar4;
    fVar2 = FLOAT_80332e60;
    sVar6 = 0;
    *(float*)(iVar5 + 0x1C) = fVar3;
    fVar4 = FLOAT_80332e64;
    sVar7 = 4;
    *(int*)(iVar5 + 0x2C) = 5;
    *(int*)(iVar5 + 0x30) = 5;
    iVar5 = 0x100;
    iVar10 = *(int*)((u8*)this + 0x850);
    *(int*)(iVar10 + 0x64) = 0x47;
    *(s16*)(iVar10 + 0x48) = 0x50;
    *(s16*)(iVar10 + 0x4A) = 0xE;
    *(s16*)(iVar10 + 0x4C) = 0x30;
    *(s16*)(iVar10 + 0x4E) = 0x30;
    *(float*)(iVar10 + 0x50) = fVar2;
    *(float*)(iVar10 + 0x54) = fVar2;
    *(float*)(iVar10 + 0x5C) = fVar3;
    *(int*)(iVar10 + 0x6C) = 0;
    *(int*)(iVar10 + 0x70) = 5;
    iVar10 = *(int*)((u8*)this + 0x850);
    *(int*)(iVar10 + 0xA4) = 0x47;
    *(s16*)(iVar10 + 0x88) = 0x55;
    *(s16*)(iVar10 + 0x8C) = 0x30;
    *(s16*)(iVar10 + 0x8E) = 0x30;
    *(s16*)(iVar10 + 0x8A) = (s16)(0x150 - *(s16*)(iVar10 + 0x8E));
    *(float*)(iVar10 + 0x90) = fVar2;
    *(float*)(iVar10 + 0x94) = fVar2;
    *(float*)(iVar10 + 0x9C) = fVar4;
    *(int*)(iVar10 + 0xAC) = 0;
    *(int*)(iVar10 + 0xB0) = 5;
    iVar10 = *(int*)((u8*)this + 0x850);
    *(int*)(iVar10 + 0xF4) = 2;
    *(int*)(iVar10 + 0xE4) = 0x2E;
    *(s16*)(iVar10 + 0xC8) = 0x50;
    *(s16*)(iVar10 + 0xCA) = 8;
    *(s16*)(iVar10 + 0xCC) = 0x48;
    *(s16*)(iVar10 + 0xCE) = 0x140;
    *(float*)(iVar10 + 0xD0) = fVar2;
    *(float*)(iVar10 + 0xD4) = fVar2;
    *(int*)(iVar10 + 0xEC) = 0;
    *(int*)(iVar10 + 0xF0) = 5;
    iVar10 = *(int*)((u8*)this + 0x850);
    iVar11 = 4;
    do {
        psVar8 = (s16*)(*(int*)((u8*)this + 0x850) + iVar5 + 8);
        psVar8[0x16] = 0;
        psVar8[0x17] = 2;
        psVar8[0xE] = 0;
        psVar8[0xF] = 0x37;
        sVar7 = sVar7 + 2;
        *psVar8 = *(s16*)(iVar10 + 8) + 0x24;
        s16 sVar1 = sVar6 + 0x20;
        psVar8[1] = *(s16*)(iVar10 + 0xA) + sVar6;
        psVar8[2] = 200;
        psVar8[3] = 0x28;
        *(float*)(psVar8 + 4) = fVar2;
        *(float*)(psVar8 + 6) = fVar2;
        psVar8[0x12] = 0;
        psVar8[0x13] = 7;
        psVar8[0x14] = 0;
        psVar8[0x15] = 5;
        iVar9 = iVar5 + 0x48;
        iVar5 += 0x80;
        psVar8 = (s16*)(*(int*)((u8*)this + 0x850) + iVar9);
        psVar8[0x16] = 0;
        psVar8[0x17] = 2;
        psVar8[0xE] = 0;
        psVar8[0xF] = 0x37;
        *psVar8 = *(s16*)(iVar10 + 8) + 0x24;
        sVar6 = sVar6 + 0x40;
        psVar8[1] = *(s16*)(iVar10 + 0xA) + sVar1;
        psVar8[2] = 200;
        psVar8[3] = 0x28;
        *(float*)(psVar8 + 4) = fVar2;
        *(float*)(psVar8 + 6) = fVar2;
        psVar8[0x12] = 0;
        psVar8[0x13] = 7;
        psVar8[0x14] = 0;
        psVar8[0x15] = 5;
        iVar11 -= 1;
    } while (iVar11 != 0);
    **(s16**)((u8*)this + 0x850) = sVar7;
    *(s16*)(*(int*)((u8*)this + 0x82C) + 0x26) = 0;
    *(u8*)(*(int*)((u8*)this + 0x82C) + 0xB) = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8015ac54
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemInit1()
{
    s16* itemList = *(s16**)((u8*)this + 0x850);
    u8* itemListBytes = (u8*)itemList;

    *(int*)(itemListBytes + 0x24) = 0x2E;
    *(int*)(itemListBytes + 0x2C) = 2;
    *(int*)(itemListBytes + 0x30) = 5;

    *(int*)(itemListBytes + 0x64) = 0x47;
    *(int*)(itemListBytes + 0x6C) = 7;
    *(int*)(itemListBytes + 0x70) = 5;

    *(int*)(itemListBytes + 0xA4) = 0x47;
    *(int*)(itemListBytes + 0xAC) = 7;
    *(int*)(itemListBytes + 0xB0) = 5;

    *(int*)(itemListBytes + 0xF4) = 2;
    *(int*)(itemListBytes + 0xE4) = 0x2E;
    *(int*)(itemListBytes + 0xEC) = 7;
    *(int*)(itemListBytes + 0xF0) = 5;

    *(int*)(itemListBytes + 0x134) = 2;
    *(int*)(itemListBytes + 0x124) = 0x37;
    *(int*)(itemListBytes + 0x12C) = 0;
    *(int*)(itemListBytes + 0x130) = 5;

    *(int*)(itemListBytes + 0x174) = 2;
    *(int*)(itemListBytes + 0x164) = 0x37;
    *(int*)(itemListBytes + 0x16C) = 0;
    *(int*)(itemListBytes + 0x170) = 5;

    *(int*)(itemListBytes + 0x1B4) = 2;
    *(int*)(itemListBytes + 0x1A4) = 0x37;
    *(int*)(itemListBytes + 0x1AC) = 0;
    *(int*)(itemListBytes + 0x1B0) = 5;

    *(int*)(itemListBytes + 0x1F4) = 2;
    *(int*)(itemListBytes + 0x1E4) = 0x37;
    *(int*)(itemListBytes + 0x1EC) = 0;
    *(int*)(itemListBytes + 0x1F0) = 5;

    *(int*)(itemListBytes + 0x234) = 2;
    *(int*)(itemListBytes + 0x224) = 0x37;
    *(int*)(itemListBytes + 0x22C) = 0;
    *(int*)(itemListBytes + 0x230) = 5;

    *(int*)(itemListBytes + 0x274) = 2;
    *(int*)(itemListBytes + 0x264) = 0x37;
    *(int*)(itemListBytes + 0x26C) = 0;
    *(int*)(itemListBytes + 0x270) = 5;

    *(int*)(itemListBytes + 0x2B4) = 2;
    *(int*)(itemListBytes + 0x2A4) = 0x37;
    *(int*)(itemListBytes + 0x2AC) = 0;
    *(int*)(itemListBytes + 0x2B0) = 5;

    *(int*)(itemListBytes + 0x2F4) = 2;
    *(int*)(itemListBytes + 0x2E4) = 0x37;
    *(int*)(itemListBytes + 0x2EC) = 0;
    *(int*)(itemListBytes + 0x2F0) = 5;

    unsigned int count = (unsigned int)itemList[0];
    s16* entry = itemList + 4;
    if ((int)count <= 0) {
        return;
    }

    const float scale = 1.0f;
    unsigned int blocks = count >> 3;
    if (blocks != 0) {
        do {
            entry[0x10] = 0;
            entry[0x11] = 0;
            *(float*)(entry + 8) = scale;
            entry[0x30] = 0;
            entry[0x31] = 0;
            *(float*)(entry + 0x28) = scale;
            entry[0x50] = 0;
            entry[0x51] = 0;
            *(float*)(entry + 0x48) = scale;
            entry[0x70] = 0;
            entry[0x71] = 0;
            *(float*)(entry + 0x68) = scale;
            entry[0x90] = 0;
            entry[0x91] = 0;
            *(float*)(entry + 0x88) = scale;
            entry[0xB0] = 0;
            entry[0xB1] = 0;
            *(float*)(entry + 0xA8) = scale;
            entry[0xD0] = 0;
            entry[0xD1] = 0;
            *(float*)(entry + 0xC8) = scale;
            entry[0xF0] = 0;
            entry[0xF1] = 0;
            *(float*)(entry + 0xE8) = scale;
            entry += 0x100;
            blocks--;
        } while (blocks != 0);

        count &= 7;
        if (count == 0) {
            return;
        }
    }

    do {
        entry[0x10] = 0;
        entry[0x11] = 0;
        *(float*)(entry + 8) = scale;
        entry += 0x20;
        count--;
    } while (count != 0);
}

/*
 * --INFO--
 * PAL Address: 0x8015aa98
 * PAL Size: 444b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::ItemOpen()
{
    s16* itemState = *reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x82C);
    s16* itemList = *reinterpret_cast<s16**>(reinterpret_cast<u8*>(this) + 0x850);
    int finished = 0;
    int count = itemList[0];
    MenuItemOpenAnim* anim = reinterpret_cast<MenuItemOpenAnim*>(reinterpret_cast<u8*>(itemList) + 8);

    if (*reinterpret_cast<u8*>(itemState + 5) == 0) {
        SingLifeInit(-1);
        ItemInit();
    }

    itemState[0x11]++;

    for (int i = 0; i < count; i++, anim++) {
        if (anim->frame <= itemState[0x11]) {
            if (itemState[0x11] < anim->frame + anim->duration) {
                anim->frame++;
                anim->progress = (float)anim->frame / (float)anim->duration;
                if ((anim->flags & 2) == 0) {
                    float t = (float)anim->frame / (float)anim->duration;
                    anim->dx = (anim->targetX - (float)anim->x) * t;
                    anim->dy = (anim->targetY - (float)anim->y) * t;
                }
            } else {
                finished++;
                anim->progress = 1.0f;
                anim->dx = 0.0f;
                anim->dy = 0.0f;
            }
        }
    }

    return count == finished;
}

/*
 * --INFO--
 * PAL Address: 0x8015a994
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ItemCtrl()
{
    s16* itemState = *(s16**)((u8*)this + 0x82C);
    s16* selectState = *(s16**)((u8*)this + 0x848);
    int result = 0;

    itemState[0x19] = itemState[0x18];

    if ((itemState[0x18] == 0) || ((itemState[0x18] != 0) && (itemState[0x9] == 1))) {
        result = ItemCtrlCur();
    } else if ((itemState[0x18] == 1) && (itemState[0x9] == 0)) {
        if (selectState[5] == 1) {
            result = 0;
            itemState[0x9] = 1;
        }
    } else if ((itemState[0x18] == 1) && (itemState[0x9] == 2) && (selectState[5] == 3)) {
        result = 0;
        itemState[0x9] = 0;
        itemState[0x18] = 0;
        itemState[0x11] = 0;
    }

    if (result != 0) {
        SingLifeInit(-1);
        ItemInit1();
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x8015a818
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
bool CMenuPcs::ItemClose()
{
    s16* itemState = *(s16**)((u8*)this + 0x82C);
    s16* itemList = *(s16**)((u8*)this + 0x850);
    int finished = 0;
    int count = itemList[0];
    MenuItemOpenAnim* anim = (MenuItemOpenAnim*)((u8*)itemList + 8);

    itemState[0x11]++;

    for (int i = 0; i < count; i++, anim++) {
        if (anim->frame <= itemState[0x11]) {
            if (itemState[0x11] < anim->frame + anim->duration) {
                anim->frame++;
                anim->progress = 1.0f - ((float)anim->frame / (float)anim->duration);
                if ((anim->flags & 2) == 0) {
                    float t = 1.0f - ((float)anim->frame / (float)anim->duration);
                    anim->dx = (anim->targetX - (float)anim->x) * t;
                    anim->dy = (anim->targetY - (float)anim->y) * t;
                }
            } else {
                finished++;
                anim->progress = 0.0f;
                anim->dx = 0.0f;
                anim->dy = 0.0f;
            }
        }
    }

    return count == finished;
}

/*
 * --INFO--
 * PAL Address: 0x80159df4
 * PAL Size: 2596b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMenuPcs::ItemDraw()
{
    bool hasSelectedItem = false;
    int selectedItemId = -1;

    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);

    int caravanWork = Game.game.m_scriptFoodBase[0];
    s16* itemState = *(s16**)((u8*)this + 0x82C);
    s16* itemList = *(s16**)((u8*)this + 0x850);
    s16 listState = itemState[8];
    s16 mode = itemState[0x18];
    int letterAttachFlg = SingGetLetterAttachflg__8CMenuPcsFv(this);
    int drawIndex = 0;
    int count = itemList[0];
    s16* entry = (s16*)((u8*)itemList + 8);

    for (int i = 0; i < count; i++, entry += 0x20) {
        int tex = *(int*)(entry + 0xE);
        if (tex < 0) {
            continue;
        }

        float x = (float)entry[0];
        float y = (float)entry[1];
        float w = (float)entry[2];
        float h = (float)entry[3];
        float u = *(float*)(entry + 4);
        float v = *(float*)(entry + 6);
        float alpha = *(float*)(entry + 8);
        float uvScale = *(float*)(entry + 10);

        if (i == 0) {
            SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 1);
            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);

            GXColor barColors[4] = {
                {0xFF, 0xFF, 0xFF, 0xFF},
                {0xFF, 0xFF, 0xFF, 0xFF},
                {0xFF, 0xFF, 0xFF, 0xFF},
                {0xFF, 0xFF, 0xFF, 0xFF},
            };

            GXSetChanMatColor(GX_COLOR0A0, barColors[0]);
            float fillW = alpha * w;
            if (fillW > FLOAT_80332e60) {
                DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
                    this, 0, x, y, fillW, h, u, v, barColors, FLOAT_80332e64, FLOAT_80332e64, 0.0f);
                x += fillW;
                u += fillW;
            }

            if (fillW > FLOAT_80332e60 && fillW < w) {
                GXColor fadeColors[4] = {
                    {0xFF, 0xFF, 0xFF, 0x00},
                    {0xFF, 0xFF, 0xFF, 0x00},
                    {0xFF, 0xFF, 0xFF, 0x00},
                    {0xFF, 0xFF, 0xFF, 0x00},
                };

                float remainW = (float)((double)(DOUBLE_80332e68 / (double)*(int*)(entry + 0x14)) * (double)w);
                DrawRect__8CMenuPcsFUlffffffP8_GXColorfff(
                    this, 0, x, y, remainW, h, u, v, fadeColors, FLOAT_80332e64, FLOAT_80332e64, 0.0f);
            }

            SetAttrFmt__8CMenuPcsFQ28CMenuPcs3FMT(this, 0);
        } else {
            float itemAlpha = alpha;
            if (tex == 0x37) {
                int menuIndex = drawIndex + itemState[0x1A];
                if (menuIndex > 0x3F) {
                    menuIndex -= 0x40;
                }

                s16 itemId = *(s16*)(caravanWork + menuIndex * 2 + 0xB6);
                if ((itemId < 1) || (EquipChk__8CMenuPcsFi(this, menuIndex) != 0) ||
                    ((letterAttachFlg >= 0) && (itemId < 0x125))) {
                    if (EquipChk__8CMenuPcsFi(this, menuIndex) != 0) {
                        int markX = (int)(x - FLOAT_80332e70);
                        int markY = (int)((float)((h - FLOAT_80332e74) * (float)DOUBLE_80332e78) + y);
                        DrawEquipMark__8CMenuPcsFiif(this, markX, markY, alpha);
                    }
                    tex = 0x34;
                    itemAlpha = (float)((double)DOUBLE_80332e78 * (double)alpha);
                }

                if (tex == 0x37 && drawIndex == itemState[0x13]) {
                    v += h;
                }
                drawIndex++;
            }

            SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(this, tex);
            GXColor color = {0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332e80 * itemAlpha)};
            GXSetChanMatColor(GX_COLOR0A0, color);
            DrawRect__8CMenuPcsFUlfffffffff(this, 0, x, y, w, h, u, v, uvScale, uvScale, 0.0f);
        }
    }

    CFont* listFont = *(CFont**)((u8*)this + 0x108);
    SetMargin__5CFontFf(FLOAT_80332e64, listFont);
    SetShadow__5CFontFi(listFont, 0);
    SetScale__5CFontFf(FLOAT_80332e84, listFont);
    DrawInit__5CFontFv(listFont);

    s16* listStart = (s16*)((u8*)itemList + 8);
    int listCount = itemList[0];
    for (int i = 0; i < listCount; i++, listStart += 0x20) {
        if (*(int*)(listStart + 0xE) == 0x37) {
            break;
        }
    }

    const ItemFlatData* flatData = reinterpret_cast<const ItemFlatData*>(&Game.game.m_cFlatDataArr[1]);
    s16* textEntry = listStart;
    for (int i = 0; i < 8; i++, textEntry += 0x20) {
        int menuIndex = i + itemState[0x1A];
        if (menuIndex > 0x3F) {
            menuIndex -= 0x40;
        }

        GXColor textColor = {0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332e80 * *(float*)(listStart + 8))};
        SetColor__5CFontF8_GXColor(listFont, &textColor);

        s16 itemId = *(s16*)(caravanWork + menuIndex * 2 + 0xB6);
        if (itemId > 0) {
            const char* text = flatData->table[0].index[itemId * 5 + 4];
            int selectedIndex = itemState[0x13] + itemState[0x1A];
            if (selectedIndex > 0x3F) {
                selectedIndex -= 0x40;
            }
            if (menuIndex == selectedIndex) {
                hasSelectedItem = true;
                selectedItemId = itemId;
            }

            GetWidth__5CFontFPc(listFont, text);
            SetPosX__5CFontFf((float)(textEntry[0] + 0x1C), listFont);
            SetPosY__5CFontFf((float)(textEntry[1] + 0xB) - FLOAT_80332e88, listFont);
            Draw__5CFontFPc(listFont, text);
        }
    }

    DrawInit__8CMenuPcsFv(this);

    s16* iconEntry = listStart;
    for (int i = 0; i < 8; i++, iconEntry += 0x20) {
        int menuIndex = i + itemState[0x1A];
        if (menuIndex > 0x3F) {
            menuIndex -= 0x40;
        }

        s16 itemId = *(s16*)(caravanWork + menuIndex * 2 + 0xB6);
        if (itemId > 0) {
            int iconY = (int)((float)iconEntry[1] + 6.0f - FLOAT_80332e64);
            int iconX = (int)(float)(iconEntry[0] + iconEntry[2] - 0x10);
            DrawSingleIcon__8CMenuPcsFiiifif(this, itemId, iconX, iconY, *(float*)(listStart + 8), 0, 0.0f);
        }
    }

    if (listState == 1) {
        float mark = CalcListPos__8CMenuPcsFiii(this, itemState[0x1A], 0x40, 1);
        if (mark > FLOAT_80332e60) {
            DrawListPosMark__8CMenuPcsFfff(this, (float)itemList[4], (float)itemList[5], mark);
        }
    }

    if (mode == 1) {
        DrawSingWin__8CMenuPcsFs(this, -1);
        if (itemState[9] == 1) {
            DrawSingWinMess__8CMenuPcsFiii(this, 0, (int)*((char*)itemState + 9), 0);
        }
    }

    s16* cursorEntry = listStart;
    if ((mode == 0 && listState == 1) || (mode != 0 && itemState[9] == 1)) {
        float cursorX;
        float cursorY;

        if (mode == 0) {
            cursorEntry += itemState[0x13] * 0x20;
            cursorX = (float)(cursorEntry[0] - 0x14);
            cursorY = (float)((float)(cursorEntry[3] - 0x20) * (float)DOUBLE_80332e78 + (float)cursorEntry[1]);
        } else {
            s16* singWindow = *(s16**)((u8*)this + 0x848);
            cursorX = (float)singWindow[0];
            cursorY = (float)(singWindow[1] + 0x20);
            cursorY += (float)(itemState[0x14] * SingWinMessHeight__8CMenuPcsFv(this));
        }

        int cursorAnim = (int)System.m_frameCounter & 7;
        DrawCursor__8CMenuPcsFiif(this, (int)(cursorX + (float)cursorAnim), (int)cursorY, FLOAT_80332e64);
    }

    DrawInit__8CMenuPcsFv(this);
    DrawSingLife__8CMenuPcsFv(this);

    if (!hasSelectedItem) {
        selectedItemId = -1;
    }

    CFont* helpFont = *(CFont**)((u8*)this + 0xF8);
    GXColor helpColor = {0xFF, 0xFF, 0xFF, (u8)(FLOAT_80332e80 * *(float*)(cursorEntry + 8))};
    DrawHelpMessage__8CMenuPcsFiP5CFontii8_GXColoriff(
        this,
        selectedItemId,
        helpFont,
        0,
        (int)-FLOAT_80332e94,
        helpColor,
        0,
        FLOAT_80332e64,
        (float)-((double)(DOUBLE_80332e78 * (double)FLOAT_80332e90) - (double)FLOAT_80332e8c));
}

/*
 * --INFO--
 * PAL Address: 0x80159654
 * PAL Size: 1952b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMenuPcs::ItemCtrlCur()
{
    bool blocked = false;
    u16 press;
    u16 hold;
    int caravanWork = Game.game.m_scriptFoodBase[0];

    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        blocked = true;
    }
    if (blocked) {
        press = 0;
    } else {
        press = Pad._8_2_;
    }

    blocked = false;
    if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
        blocked = true;
    }
    if (blocked) {
        hold = 0;
    } else {
        hold = *(u16*)((u8*)&Pad + 0x20);
    }

    if (hold == 0) {
        return 0;
    }

    int menuState = *(int*)((u8*)this + 0x82C);
    s16 letterAttachFlg = SingGetLetterAttachflg__8CMenuPcsFv(this);
    int mode = (int)*(s16*)(menuState + 0x30);

    if (mode == 0) {
        if ((hold & 8) == 0) {
            if ((hold & 4) != 0) {
                if (*(s16*)(menuState + 0x26) < 7) {
                    *(s16*)(menuState + 0x26) = *(s16*)(menuState + 0x26) + 1;
                } else {
                    s16 scroll = *(s16*)(menuState + 0x34);
                    if (scroll > 0x3E) {
                        *(s16*)(menuState + 0x34) = 0;
                    } else {
                        *(s16*)(menuState + 0x34) = scroll + 1;
                    }
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        } else if (*(s16*)(menuState + 0x26) == 0) {
            if (*(s16*)(menuState + 0x34) == 0) {
                *(s16*)(menuState + 0x34) = 0x3F;
            } else {
                *(s16*)(menuState + 0x34) = *(s16*)(menuState + 0x34) - 1;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        } else {
            *(s16*)(menuState + 0x26) = *(s16*)(menuState + 0x26) - 1;
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x20) != 0) {
                if (letterAttachFlg < 0) {
                    *(s16*)(menuState + 0x1E) = 1;
                    Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
                    return 1;
                }
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if ((press & 0x40) != 0) {
                if (letterAttachFlg < 0) {
                    *(s16*)(menuState + 0x1E) = -1;
                    Sound.PlaySe(0x5A, 0x40, 0x7F, 0);
                    return 1;
                }
                Sound.PlaySe(4, 0x40, 0x7F, 0);
            } else if ((press & 0x100) != 0) {
                int idx = (int)*(s16*)(menuState + 0x34) + (int)*(s16*)(menuState + 0x26);
                if (idx > 0x3F) {
                    idx -= 0x40;
                }

                int itemEntry = caravanWork + idx * 2;
                s16 itemId = *(s16*)(itemEntry + 0xB6);

                if ((itemId < 1) || (EquipChk__8CMenuPcsFi(this, idx) != 0) ||
                    ((letterAttachFlg >= 0) && (itemId < 0x125))) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else if (letterAttachFlg >= 0) {
                    LetterSetAttachItem__8CMenuPcsFUii(this, (unsigned int)idx, 1);
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                    return 1;
                } else {
                    *(u8*)(menuState + 9) = 0xC;
                    int itemType = GetItemType__8CMenuPcsFii(this, idx, 0);

                    if ((itemType == 7) && (CanPlayerUseItem__12CCaravanWorkFv((void*)caravanWork) != 0)) {
                        *(u8*)(menuState + 9) = *(u8*)(menuState + 9) | 1;
                    }
                    if ((itemType != 1) && (CanPlayerPutItem__12CCaravanWorkFv((void*)caravanWork) != 0)) {
                        *(u8*)(menuState + 9) = *(u8*)(menuState + 9) | 2;
                    }

                    s16 winW;
                    s16 winH;
                    GetSingWinSize__8CMenuPcsFiPsPsi(this, 0, &winW, &winH, 0);
                    SetSingWinInfo__8CMenuPcsFiiii(this, 0xF0, 0xA0, winW, winH);

                    *(s16*)(*(int*)((u8*)this + 0x848) + 10) = 0;
                    *(s16*)(menuState + 0x12) = 0;
                    *(s16*)(menuState + 0x30) = 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                }
            } else if ((press & 0x200) != 0) {
                if (letterAttachFlg >= 0) {
                    LetterSetAttachItem__8CMenuPcsFUii(this, 0, 0xFFFFFFFF);
                    Sound.PlaySe(3, 0x40, 0x7F, 0);
                    return 1;
                }
                *(u8*)(menuState + 0xD) = 1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
                return 1;
            }
        }
    } else {
        int optBase = menuState + mode * 2;

        if ((hold & 8) == 0) {
            if ((hold & 4) != 0) {
                if (*(s16*)(optBase + 0x26) < 3) {
                    *(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) + 1;
                } else {
                    *(s16*)(optBase + 0x26) = 0;
                }
                Sound.PlaySe(1, 0x40, 0x7F, 0);
            }
        } else {
            if (*(s16*)(optBase + 0x26) == 0) {
                *(s16*)(optBase + 0x26) = 3;
            } else {
                *(s16*)(optBase + 0x26) = *(s16*)(optBase + 0x26) - 1;
            }
            Sound.PlaySe(1, 0x40, 0x7F, 0);
        }

        if ((hold & 0xC) == 0) {
            if ((press & 0x100) != 0) {
                int option = (int)*(s16*)(optBase + 0x26);
                if (((int)*(char*)(menuState + 9) & (1 << option)) == 0) {
                    Sound.PlaySe(4, 0x40, 0x7F, 0);
                } else {
                    int idx = (int)*(s16*)(menuState + 0x34) + (int)*(s16*)(menuState + 0x26);
                    if (idx > 0x3F) {
                        idx -= 0x40;
                    }

                    if (option == 0) {
                        FGUseItem__12CCaravanWorkFii((void*)caravanWork, idx, 0);
                        SingLifeInit__8CMenuPcsFi(this, 0);
                        CalcStatus__12CCaravanWorkFv((void*)caravanWork);
                    } else if (option == 1) {
                        FGPutItem__12CCaravanWorkFii((void*)caravanWork, idx, 0);
                    } else if (option == 2) {
                        DeleteItemIdx__12CCaravanWorkFii((void*)caravanWork, idx, 0);
                    }

                    *(s16*)(*(int*)((u8*)this + 0x848) + 10) = 2;
                    *(s16*)(menuState + 0x12) = *(s16*)(menuState + 0x12) + 1;
                    Sound.PlaySe(2, 0x40, 0x7F, 0);
                }
            } else if ((press & 0x200) != 0) {
                *(s16*)(*(int*)((u8*)this + 0x848) + 10) = 2;
                *(s16*)(menuState + 0x12) = *(s16*)(menuState + 0x12) + 1;
                Sound.PlaySe(3, 0x40, 0x7F, 0);
            }
        }
    }

    return 0;
}
