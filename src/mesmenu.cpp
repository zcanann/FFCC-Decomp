#include "ffcc/mesmenu.h"
#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/fontman.h"
#include "ffcc/game.h"
#include "ffcc/linkage.h"
#include "ffcc/menu.h"
#include "ffcc/p_menu.h"
#include "ffcc/pad.h"
#include "ffcc/ringmenu.h"
#include "ffcc/sound.h"
#include "ffcc/system.h"
#include "ffcc/cflat_runtime2.h"

#include <math.h>
#include <string.h>

extern "C" {
void Create__5CMenuFv(void* menu);
void Destroy__5CMenuFv(void* menu);
void SetFade__9CRingMenuFi(void* ringMenu, int fade);
int __cntlzw(unsigned int);
void SetExternalTlut__8CTextureFPvi(void* texture, void* tlut, int enable);

static const char s_CMesMenu_801D9E90[] = "CMesMenu";
const char DAT_801d9e9c[] =
    "mesMenu\x95\x8e\xa6on/off\x82\xaa\x95\xcf\x8d\x58\x82\xb3\x82\xea\x82\xdc\x82\xb5\x82\xbd\x81\x42%d-%d\n\0\0\0";
int DAT_8020f998[4] = {1, 0, -1, 0};
int DAT_8020F9A8[4] = {1, 6, 7, 6};
extern float FLOAT_803308d8;
extern float FLOAT_803308dc;
extern float FLOAT_803308e0;
extern float FLOAT_803308e4;
extern float FLOAT_803308e8;
extern float FLOAT_803308ec;
extern float FLOAT_803308f0;
extern float FLOAT_803308f4;
extern float FLOAT_803308f8;
extern double DOUBLE_80330900;
extern float FLOAT_80330908;
extern float FLOAT_8033090c;
extern float FLOAT_80330910;
extern float FLOAT_80330914;
extern float FLOAT_80330918;
extern float FLOAT_8033091c;
extern float FLOAT_80330920;
extern float FLOAT_80330924;
extern float FLOAT_80330928;
extern float FLOAT_8033092c;
extern float FLOAT_80330930;
extern float FLOAT_80330934;
extern float FLOAT_80330938;
extern float FLOAT_8033093C;
extern float FLOAT_80330940;
extern float FLOAT_80330944;
extern float FLOAT_80330948;
extern float FLOAT_8033094C;
extern float FLOAT_80330950;
extern float FLOAT_80330954;
extern float FLOAT_80330958;
extern float FLOAT_8033095C;
extern float FLOAT_80330960;
extern float FLOAT_80330964;
extern float FLOAT_80330968;
extern float FLOAT_8033096C;
extern float FLOAT_80330970;
extern float FLOAT_80330974;
extern double DOUBLE_80330978;
extern float FLOAT_80330984;
extern float FLOAT_80330988;
extern float FLOAT_8033098C;
extern float FLOAT_80330990;
extern float FLOAT_80330980;
extern float FLOAT_80330994;
}

struct CFlatDataTableEntryView
{
    int count;
    char** index;
    char* buffer;
};

struct CFlatDataView
{
    int dataCount;
    char pad[0x68 - 4];
    int tableCount;
    CFlatDataTableEntryView m_table[8];
};

/*
 * --INFO--
 * PAL Address: 0x8009b4e4
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::SetPos(float x, float y)
{
	*(float*)((char*)this + 0x3d74) = x;
	*(float*)((char*)this + 0x3d78) = y;
}

/*
 * --INFO--
 * PAL Address: 0x8009b4f0
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::CloseRequest(int closeReason)
{
    CFlatRuntime::CStack stack[2];

    *(int*)((char*)this + 0x3DA4) = closeReason;
    if (*(int*)((char*)this + 0x0C) <= 1) {
        if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x40) != 0) {
            m_mes.Set(0, 0);
            stack[0].m_word = *(int*)((char*)this + 0x18);
            stack[1].m_word = *(int*)((char*)this + 0x3DA4);
            reinterpret_cast<CFlatRuntime*>(CFlat)->SystemCall(0, 1, 3, 2, stack, 0);
            *(int*)((char*)this + 0x0C) = 4;
            *(int*)((char*)this + 0x08) = 0;
            if (*(int*)((char*)this + 0x18) < 4) {
                int menuIndex = *(int*)((char*)this + 0x18);
                void** ringMenuSlots = (void**)((char*)&MenuPcs + 0x13C);
                SetFade__9CRingMenuFi(ringMenuSlots[menuIndex], 1);
            }
        } else {
            *(int*)((char*)this + 0x0C) = 2;
            *(int*)((char*)this + 0x10) = 0;
            *(int*)((char*)this + 0x14) = 4;
            if (((*(unsigned int*)((char*)this + 0x3D8C) & 1) == 0) &&
                ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                Sound.PlaySe(6, 0x40, 0x7F, 0);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b5fc
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::Open(char* script, int x, int y, int flags, int unk1, int unk2, int unk3)
{
    float fVar1;
    unsigned int uVar2;
    bool bVar3;
    double dVar4;

    fVar1 = FLOAT_803308d8;
    *(float*)((char*)this + 0x3D78) = FLOAT_803308d8;
    *(float*)((char*)this + 0x3D74) = fVar1;
    *(int*)((char*)this + 0x08) = 1;
    *(int*)((char*)this + 0x3DA4) = 0;
    *(unsigned int*)((char*)this + 0x3D8C) = (unsigned int)flags;

    if (*(int*)((char*)this + 0x18) >= 4) {
        *(float*)((char*)this + 0x3D6C) = (float)x;
        *(float*)((char*)this + 0x3D70) = (float)y;
        *(int*)((char*)this + 0x3D88) = 1;
        uVar2 = ((unsigned int)__cntlzw((unsigned int)(flags & 2))) >> 5;
        fVar1 = FLOAT_803308dc;
        *(float*)((char*)this + 0x3D9C) = fVar1;
        *(float*)((char*)this + 0x3DA0) = fVar1;
        int flagMask = -(flags >> 1 & 1);
        int displayOffset = 0x1C;
        displayOffset &= flagMask;
        *(unsigned int*)((char*)this + 0x3D50) = (unsigned int)displayOffset;
        *(unsigned int*)((char*)this + 0x3D54) = uVar2;
    } else {
        SetFade__9CRingMenuFi(*(void**)((char*)&MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 0);
        *(float*)((char*)this + 0x3D9C) = FLOAT_803308e0;
        fVar1 = FLOAT_803308e4;
        *(float*)((char*)this + 0x3DA0) = fVar1;
    }

    *(int*)((char*)this + 0x3D90) = unk1;
    *(int*)((char*)this + 0x3D94) = unk2;
    *(int*)((char*)this + 0x3D98) = unk3;
    m_mes.Set(script, flags & 0x20);

    fVar1 = FLOAT_803308e8;
    *(float*)((char*)this + 0x3D7C) = FLOAT_803308e8 * *(float*)((char*)this + 0x3D9C) + *(float*)((char*)this + 0x3CC0);
    *(float*)((char*)this + 0x3D80) = fVar1 * *(float*)((char*)this + 0x3DA0) + *(float*)((char*)this + 0x3CC4);

    if (*(int*)((char*)this + 0x18) >= 4) {
        if ((flags & 8) != 0) {
            fVar1 = FLOAT_803308ec;
            *(float*)((char*)this + 0x3D6C) = -(FLOAT_803308ec * *(float*)((char*)this + 0x3D7C) - *(float*)((char*)this + 0x3D6C));
            *(float*)((char*)this + 0x3D70) = -(fVar1 * *(float*)((char*)this + 0x3D80) - *(float*)((char*)this + 0x3D70));
        } else if ((flags & 0x8000) != 0) {
            *(float*)((char*)this + 0x3D6C) -= *(float*)((char*)this + 0x3D7C);
        }
    } else if ((flags & 0x100) == 0) {
        fVar1 = *(float*)((char*)this + 0x3D7C);
        if (fVar1 < FLOAT_803308f0) {
            fVar1 = FLOAT_803308f0;
        }
        *(float*)((char*)this + 0x3D7C) = fVar1;
    }

    uVar2 = (unsigned int)*(int*)((char*)this + 0x18);
    if ((int)uVar2 < 4) {
        if ((uVar2 & 2) != 0) {
            dVar4 = (double)((*(float*)((char*)this + 0x3DA0) + (*(float*)((char*)this + 0x3D70) - FLOAT_803308f4) +
                              *(float*)((char*)this + 0x3D78)) -
                             *(float*)((char*)this + 0x3D80));
        } else {
            dVar4 = (double)(FLOAT_803308f8 + *(float*)((char*)this + 0x3DA0) + *(float*)((char*)this + 0x3D70) +
                             *(float*)((char*)this + 0x3D78));
        }
    } else {
        dVar4 = (double)(*(float*)((char*)this + 0x3DA0) + *(float*)((char*)this + 0x3D70) + *(float*)((char*)this + 0x3D78));
    }

    bVar3 = false;
    if (((int)uVar2 < 4) && ((uVar2 & 1) != 0)) {
        bVar3 = true;
    }
    if (bVar3) {
        fVar1 = (*(float*)((char*)this + 0x3D9C) + *(float*)((char*)this + 0x3D6C) + *(float*)((char*)this + 0x3D74)) -
                *(float*)((char*)this + 0x3D7C);
    } else {
        fVar1 = *(float*)((char*)this + 0x3D9C) + *(float*)((char*)this + 0x3D6C) + *(float*)((char*)this + 0x3D74);
    }
    m_mes.SetPosition(fVar1, (float)dVar4);

    unsigned int state;
    if (*(int*)((char*)this + 0x18) < 4) {
        state = ((unsigned int)flags >> 4) & 1;
    } else {
        state = (flags & 0x10) != 0;
    }
    *(unsigned int*)((char*)this + 0x0C) = state;
    *(int*)((char*)this + 0x10) = 0;
    *(int*)((char*)this + 0x14) = 8;
    if ((flags & 0x11) == 0 && ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
        Sound.PlaySe(5, 0x40, 0x7F, 0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b8e4
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::onScriptChanged(char*, int)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x8009b8e8
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::onScriptChanging(char*)
{
    int menuIndex;
    void** ringMenuSlots;

    m_mes.Set(0, 0);
    *(int*)((char*)this + 0x0C) = 4;
    *(int*)((char*)this + 0x08) = 0;
    menuIndex = *(int*)((char*)this + 0x18);
    if (menuIndex < 4) {
        ringMenuSlots = (void**)((char*)&MenuPcs + 0x13C);
        SetFade__9CRingMenuFi(ringMenuSlots[menuIndex], 1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009b958
 * PAL Size: 916b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::DrawHeart(float x, float y, float z, float alpha)
{
    (void)z;

    unsigned int scriptFood = Game.m_scriptFoodBase[*(int*)((char*)this + 0x18)];
    if (scriptFood == 0) {
        return;
    }

    if (FLOAT_803308d8 >= alpha) {
        return;
    }

    CColor colorStorage(0xFF, 0xFF, 0xFF, (int)(FLOAT_80330908 * alpha));
    MenuPcs.SetColor(colorStorage);
    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x17));

    int offset = 0x4C;
    if ((*(int*)((char*)this + 0x18) & 1) != 0) {
        offset = 0x30;
    }

    float baseY = FLOAT_8033090c + y;
    float stepScale = FLOAT_80330910;
    int valueOffset = 0;
    float baseX = x + (float)offset;
    float timerScale = FLOAT_80330918;
    float one = FLOAT_80330914;
    float pulseScale = FLOAT_8033091c;
    float pulseMul = FLOAT_80330920;
    int timerOffset = (int)this;

    for (unsigned int i = 0; i < (*(unsigned short*)(scriptFood + 0x1A) >> 1); i++) {
        int heartValue = *(int*)((char*)this + 0x3DA8) - valueOffset;
        float timer = (float)*(unsigned int*)(timerOffset + 0x3DB0);
        float pulse = (pulseScale * (float)sin(stepScale * -(timer * timerScale - one)) + one) * pulseMul;

        unsigned int subTimer = *(unsigned int*)(timerOffset + 0x3DD0);
        int shakeX;
        if (subTimer == 0) {
            shakeX = 0;
        } else {
            shakeX = ((int)subTimer >> 2) * DAT_8020f998[((subTimer + 1) * 4 & 0xC) / 4];
        }

        float drawX = baseX + (float)shakeX;
        int shakeY;
        if (subTimer == 0) {
            shakeY = 0;
        } else {
            shakeY = ((int)subTimer >> 2) * DAT_8020f998[subTimer & 3];
        }

        float drawY = baseY + (float)shakeY;

        MenuPcs.DrawRect(
            3, drawX, drawY, FLOAT_803308dc, FLOAT_803308dc, FLOAT_803308d8, FLOAT_803308d8, pulse, pulse,
            FLOAT_803308d8);

        if (heartValue > 0) {
            int fillAmount = 0x0B;
            if (heartValue < 0x0B) {
                fillAmount = heartValue;
            }

            float u = (float)((*(unsigned short*)(scriptFood + 0x42) != 0) * 0x18);
            float v = (float)((0x0C - fillAmount) * 0x18);
            MenuPcs.DrawRect(
                3, drawX, drawY, FLOAT_803308dc, FLOAT_803308dc, u, v, pulse, pulse,
                FLOAT_803308d8);
        }

        baseX += ((*(int*)((char*)this + 0x18) & 1) != 0) ? FLOAT_80330924 : FLOAT_80330928;
        valueOffset += 0x0C;
        timerOffset += 4;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009bcec
 * PAL Size: 496b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::CalcHeart()
{
    unsigned int scriptFood = Game.m_scriptFoodBase[*(int*)((char*)this + 0x18)];
    if (scriptFood == 0) {
        return;
    }

    unsigned int foodCount = (unsigned int)*(unsigned short*)(scriptFood + 0x1C);
    int targetValue = (int)(foodCount * 6);
    if (*(int*)((char*)this + 0x3DAC) < targetValue) {
        *(int*)((char*)this + 0x3DAC) += targetValue - *(int*)((char*)this + 0x3DAC);
    } else if (targetValue < *(int*)((char*)this + 0x3DAC)) {
        *(int*)((char*)this + 0x3DAC) -= *(int*)((char*)this + 0x3DAC) - targetValue;
    }

    int currentValue = *(int*)((char*)this + 0x3DA8);
    if (currentValue < *(int*)((char*)this + 0x3DAC)) {
        int index = currentValue / 0xC;
        int base = (int)this + index * 4;
        if (*(int*)(base + 0x3DB0) == 0) {
            *(int*)(base + 0x3DB0) = 0x10;
        }

        int nextValue = *(int*)((char*)this + 0x3DA8) + 2;
        int maxValue = *(int*)((char*)this + 0x3DAC);
        if (nextValue < maxValue) {
            maxValue = nextValue;
        }
        *(int*)((char*)this + 0x3DA8) = maxValue;
    } else if (*(int*)((char*)this + 0x3DAC) < currentValue) {
        *(unsigned int*)((char*)this + 0x3DA8) = (currentValue - 2U) & ~((int)(currentValue - 2U) >> 0x1F);

        int decValue = *(int*)((char*)this + 0x3DA8);
        int index = decValue / 0xC;
        int base = (int)this + index * 4;
        if (*(int*)(base + 0x3DD0) == 0) {
            *(int*)(base + 0x3DD0) = 0x10;
        }
        if (*(int*)((char*)this + 0x3DF0) == 0) {
            *(int*)((char*)this + 0x3DF0) = 0x10;
        }
    }

    int base = (int)this;
    for (int i = 0; i < 2; i++) {
        unsigned int value = *(int*)(base + 0x3DB0) - 1;
        *(unsigned int*)(base + 0x3DB0) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DD0) - 1;
        *(unsigned int*)(base + 0x3DD0) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DB4) - 1;
        *(unsigned int*)(base + 0x3DB4) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DD4) - 1;
        *(unsigned int*)(base + 0x3DD4) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DB8) - 1;
        *(unsigned int*)(base + 0x3DB8) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DD8) - 1;
        *(unsigned int*)(base + 0x3DD8) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DBC) - 1;
        *(unsigned int*)(base + 0x3DBC) = value & ~((int)value >> 0x1F);

        value = *(int*)(base + 0x3DDC) - 1;
        *(unsigned int*)(base + 0x3DDC) = value & ~((int)value >> 0x1F);

        base += 0x10;
    }

    unsigned int value = *(int*)((char*)this + 0x3DF0) - 1;
    *(unsigned int*)((char*)this + 0x3DF0) = value & ~((int)value >> 0x1F);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onDraw()
{
    if ((*(int*)((char*)this + 0x18) == 0) && ((int)((unsigned int)*(unsigned char*)(CFlat + 0x12E4) << 30) < 0)) {
        int iconFrame = 0;
        int charaMode = *(int*)((char*)&Chara + 0x2004);
        if (charaMode == 2) {
            iconFrame = 5;
        } else if (charaMode < 2) {
            if (charaMode == 0) {
                iconFrame = 3;
            } else if (charaMode >= 0) {
                iconFrame = 4;
            }
        } else if (charaMode == 4) {
            unsigned short buttons;
            if ((Pad._452_4_ != 0) || (Pad._448_4_ != -1)) {
                buttons = 0;
            } else {
                buttons = Pad.GetPadInputs()[__cntlzw((unsigned int)Pad._448_4_) >> 5].button[0];
            }

            iconFrame = DAT_8020F9A8[0];
            if ((buttons & 0x100) != 0) {
                iconFrame = DAT_8020F9A8[(System.m_frameCounter & 6) >> 1];
            }
        } else if (charaMode < 4) {
            iconFrame = 2;
        }

        CColor colorStorage(0xFF, 0xFF, 0xFF, 0xFF);
        MenuPcs.SetColor(colorStorage);
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0));
        MenuPcs.DrawRect(
            0, (float)(*(int*)((char*)&Chara + 0x200C) - 0x20), (float)*(int*)((char*)&Chara + 0x2010),
            FLOAT_8033092c, FLOAT_8033092c, FLOAT_803308d8, (float)(iconFrame << 5), FLOAT_80330914, FLOAT_80330914,
            FLOAT_803308d8);
    }

    CFont* font = MenuPcs.m_fonts[0];
    int menuIndex = *(int*)((char*)this + 0x18);
    if (!((menuIndex < 4) || (*(int*)((char*)this + 8) != 0))) {
        return;
    }
    if ((Game.m_gameWork.m_menuStageMode != 0) && (menuIndex > 0) && (menuIndex < 4)) {
        return;
    }

    font->SetMargin(FLOAT_803308d8);
    font->SetShadow(1);
    MenuPcs.SetAttrFmt(static_cast<CMenuPcs::FMT>(0));

    float stageBlend = (float)*(int*)((char*)this + 0x3DF4) * FLOAT_80330918;
    if (*(int*)((char*)this + 0x3DF8) != 0) {
        stageBlend = FLOAT_80330914 - stageBlend;
    }
    if (stageBlend == FLOAT_803308d8) {
        return;
    }

    float stateBlend = FLOAT_803308d8;
    int state = *(int*)((char*)this + 0x0C);
    if ((state == 0) || (state == 1) || (state == 3)) {
        if (state == 0) {
            stateBlend = (float)*(int*)((char*)this + 0x10) / (float)*(int*)((char*)this + 0x14);
        } else if (state == 3) {
            stateBlend = FLOAT_80330914 - (float)*(int*)((char*)this + 0x10) / (float)*(int*)((char*)this + 0x14);
        } else {
            stateBlend = FLOAT_80330914;
        }
    }
    if (stateBlend <= FLOAT_803308d8) {
        return;
    }

    if (menuIndex < 4) {
        unsigned int scriptFood = Game.m_scriptFoodBase[menuIndex];
        if (scriptFood == 0) {
            return;
        }

        float pulse = FLOAT_8033092c * (FLOAT_80330914 - sinf(FLOAT_80330930 * stageBlend));
        (void)MenuPcs.m_battleRingMenus[menuIndex]->GetDispCounter();
        float baseX = *(float*)((char*)this + 0x3D6C) + *(float*)((char*)this + 0x3D74);
        float baseY = *(float*)((char*)this + 0x3D70) + *(float*)((char*)this + 0x3D78);
        float dirX = ((menuIndex & 1) != 0) ? FLOAT_80330914 : -FLOAT_80330914;
        float dirY = ((menuIndex & 2) != 0) ? FLOAT_80330914 : -FLOAT_80330914;
        baseX += dirX * pulse;
        baseY += dirY * pulse;

        if (stateBlend > FLOAT_803308d8) {
            float width = *(float*)((char*)this + 0x3D7C) * stateBlend;
            float height = *(float*)((char*)this + 0x3D80) * stateBlend;
            float drawX = baseX;
            if ((menuIndex & 1) == 0) {
                drawX -= *(float*)((char*)this + 0x3D7C) - width;
            }

            float edgeY = FLOAT_803308f8;
            if ((menuIndex & 2) != 0) {
                edgeY = (FLOAT_80330934 - *(float*)((char*)this + 0x3D80)) + (*(float*)((char*)this + 0x3D80) - height);
            }
            float drawY = baseY + edgeY;

            float alphaF = FLOAT_80330908 * stateBlend * stageBlend;
            CColor colorStorage(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
            MenuPcs.SetColor(colorStorage);
            MenuPcs.DrawWindow(drawX, drawY, width, height, static_cast<CMenuPcs::TEX>(2), FLOAT_8033092c);

            if ((*(int*)((char*)this + 0x0C) == 1) && (stageBlend == FLOAT_80330914)) {
                m_mes.Draw();
                MenuPcs.DrawInit();
            }

            if ((*(int*)((char*)this + 0x3D94) >= 0) || (*(int*)((char*)this + 0x3D98) >= 0)) {
                MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x14));
                colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
                MenuPcs.SetColor(colorStorage);

                float cursorWave = sinf(FLOAT_80330930 * (FLOAT_80330914 - stateBlend) + FLOAT_80330930);
                int signX = ((menuIndex & 1) != 0) ? 32 : -32;
                float iconX = drawX + (float)signX * (FLOAT_80330914 - cursorWave);
                iconX += ((menuIndex & 1) != 0) ? FLOAT_80330938 : (width - FLOAT_8033093C) - FLOAT_80330938;
                float iconY = drawY + (((menuIndex & 2) != 0) ? FLOAT_80330940 + height : FLOAT_80330944);
                MenuPcs.DrawRect(
                    ((menuIndex & 1) != 0) ? 8 : 0, iconX, iconY, FLOAT_8033093C, FLOAT_80330948,
                    (float)(((menuIndex & 2) != 0) ? 144 : 0), FLOAT_803308d8, FLOAT_80330914, FLOAT_80330914,
                    FLOAT_803308d8);

                CFlatDataView* flatData = reinterpret_cast<CFlatDataView*>(&Game.m_cFlatDataArr[1]);
                if (*(int*)((char*)this + 0x3D98) >= 0) {
                    font->SetScale(FLOAT_8033094C);
                    font->SetShadow(1);
                    font->SetMargin(FLOAT_803308d8);
                    float textWidth = font->GetWidth(flatData->m_table[2].index[*(int*)((char*)this + 0x3D98)]);
                    font->DrawInit();
                    font->SetTlut(0xF);
                    colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
                    font->SetColor(colorStorage.color);
                    font->SetPosX(iconX + (((menuIndex & 1) != 0) ? FLOAT_80330950 : FLOAT_80330954 - textWidth));
                    font->SetPosY(iconY + (float)(((menuIndex & 2) != 0) ? 8 : 31));
                    font->Draw(flatData->m_table[2].index[*(int*)((char*)this + 0x3D98)]);
                    MenuPcs.DrawInit();
                }

                if (*(int*)((char*)this + 0x3D94) >= 0) {
                    int itemIndex = *(int*)((char*)this + 0x3D94);
                    colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
                    MenuPcs.SetColor(colorStorage);
                    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x18));
                    SetExternalTlut__8CTextureFPvi(MenuPcs.m_textures[0x18], 0, 1);
                    float itemX = iconX + (float)(((menuIndex & 1) != 0) ? 13 : 83);
                    int iconColumn = itemIndex % 8;
                    int iconRow = itemIndex / 8;
                    MenuPcs.DrawRect(
                        (((menuIndex & 1) != 0) && ((*(unsigned int*)((char*)this + 0x3D8C) & 4) == 0)) ? 8 : 0,
                        itemX, iconY + FLOAT_80330958, FLOAT_8033095C, FLOAT_80330960, (float)(iconColumn * 0x30),
                        (float)(iconRow * 0x30), FLOAT_80330914, FLOAT_80330914, FLOAT_803308d8);
                }
            }

            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x16));
            colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)(FLOAT_80330908 * stageBlend));
            MenuPcs.SetColor(colorStorage);
            float frameX = baseX - (float)(((menuIndex & 1) != 0) ? 128 : 0);
            float frameY = baseY - (float)(((menuIndex & 2) != 0) ? 56 : 0);
            MenuPcs.DrawRect(
                0, frameX, frameY, FLOAT_80330964, FLOAT_80330948,
                (float)(((menuIndex & 2) != 0) ? 128 : 0),
                (float)(((menuIndex & 1) != 0) ? 56 : 0), FLOAT_80330914, FLOAT_80330914, FLOAT_803308d8);

            font->SetScale(FLOAT_8033094C);
            float titleWidth = font->GetWidth(reinterpret_cast<char*>(scriptFood + 0x3CA));
            font->DrawInit();
            font->SetTlut(0xF);
            colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)(FLOAT_80330908 * stageBlend));
            font->SetColor(colorStorage.color);
            font->SetPosX(frameX + (((menuIndex & 1) != 0) ? FLOAT_80330968 - titleWidth : FLOAT_80330950));
            font->SetPosY(frameY + FLOAT_8033096C);
            font->Draw(reinterpret_cast<char*>(scriptFood + 0x3CA));
            MenuPcs.DrawInit();

            {
                unsigned int heartFood = Game.m_scriptFoodBase[*(int*)((char*)this + 0x18)];
                if ((heartFood != 0) && (stageBlend > FLOAT_803308d8)) {
                    colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)(FLOAT_80330908 * stageBlend));
                    MenuPcs.SetColor(colorStorage);
                    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x17));

                    int heartOffset = 0x4C;
                    if ((menuIndex & 1) != 0) {
                        heartOffset = 0x30;
                    }

                    float heartBaseY = FLOAT_8033090c + frameY;
                    float heartBaseX = frameX + (float)heartOffset;
                    int heartValueOffset = 0;
                    int heartTimerOffset = (int)this;

                    for (int heartIndex = 0; heartIndex < (int)((unsigned int)*(unsigned short*)(heartFood + 0x1A) >> 1);
                         heartIndex++) {
                        int heartValue = *(int*)((char*)this + 0x3DA8) - heartValueOffset;
                        float heartTimer = (float)*(unsigned int*)(heartTimerOffset + 0x3DB0);
                        float heartPulse =
                            (FLOAT_8033091c * (float)sin(FLOAT_80330910 * -(heartTimer * FLOAT_80330918 - FLOAT_80330914)) +
                             FLOAT_80330914) *
                            FLOAT_80330920;

                        unsigned int heartSubTimer = *(unsigned int*)(heartTimerOffset + 0x3DD0);
                        int heartShakeX = 0;
                        if (heartSubTimer != 0) {
                            heartShakeX = ((int)heartSubTimer >> 2) * DAT_8020f998[((heartSubTimer + 1) * 4 & 0xC) / 4];
                        }

                        int heartShakeY = 0;
                        if (heartSubTimer != 0) {
                            heartShakeY = ((int)heartSubTimer >> 2) * DAT_8020f998[heartSubTimer & 3];
                        }

                        float heartX = heartBaseX + (float)heartShakeX;
                        float heartY = heartBaseY + (float)heartShakeY;

                        MenuPcs.DrawRect(
                            3, heartX, heartY, FLOAT_803308dc, FLOAT_803308dc, FLOAT_803308d8, FLOAT_803308d8,
                            heartPulse, heartPulse, FLOAT_803308d8);

                        if (heartValue > 0) {
                            int fillAmount = 0x0B;
                            if (heartValue < 0x0B) {
                                fillAmount = heartValue;
                            }

                            float u = (float)((*(unsigned short*)(heartFood + 0x42) != 0) * 0x18);
                            float v = (float)((0x0C - fillAmount) * 0x18);
                            MenuPcs.DrawRect(
                                3, heartX, heartY, FLOAT_803308dc, FLOAT_803308dc, u, v, heartPulse, heartPulse,
                                FLOAT_803308d8);
                        }

                        heartBaseX += ((menuIndex & 1) != 0) ? FLOAT_80330924 : FLOAT_80330928;
                        heartValueOffset += 0x0C;
                        heartTimerOffset += 4;
                    }
                }
            }

            unsigned int foodTimer = *(unsigned int*)((char*)this + 0x3DF0);
            unsigned int foodAmount = (unsigned int)*(unsigned short*)(scriptFood + 0x14);
            int foodTier = (int)foodAmount - 100;
            foodTier = foodTier / 100 + (foodTier >> 31);
            unsigned int foodIcon = (foodAmount % 100) + (foodTier - (foodTier >> 31)) * 4;
            float shakeX = (foodTimer != 0) ? (float)(((int)foodTimer >> 2) * DAT_8020f998[(3 - ((foodTimer + 1) & 3)) & 3]) : FLOAT_803308d8;
            float shakeY = (foodTimer != 0) ? (float)(((int)foodTimer >> 2) * DAT_8020f998[(3 - (foodTimer & 3)) & 3]) : FLOAT_803308d8;
            colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)(FLOAT_80330908 * stageBlend));
            MenuPcs.SetColor(colorStorage);
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x18));
            SetExternalTlut__8CTextureFPvi(
                MenuPcs.m_textures[0x18], (*(short*)(scriptFood + 0x1C) == 0) ? MenuPcs.m_externalFontTlut : 0, 1);
            MenuPcs.DrawRect(
                ((menuIndex & 1) == 0) ? 8 : 0, frameX + shakeX + (float)(((menuIndex & 1) != 0) ? 75 : 5),
                frameY + shakeY + FLOAT_80330958, FLOAT_8033095C, FLOAT_80330960,
                (float)((foodIcon % 8) * 0x30), (float)((foodIcon / 8) * 0x30), FLOAT_80330914, FLOAT_80330914,
                FLOAT_803308d8);
        }
    } else {
        float sizeX = *(float*)((char*)this + 0x3D7C) * stateBlend;
        float sizeY = *(float*)((char*)this + 0x3D80) * stateBlend;
        float baseX = *(float*)((char*)this + 0x3D6C) + *(float*)((char*)this + 0x3D74);
        float baseY = *(float*)((char*)this + 0x3D70) + *(float*)((char*)this + 0x3D78);
        float drawX = -(FLOAT_803308ec * sizeX - (FLOAT_803308ec * *(float*)((char*)this + 0x3D7C) + baseX));
        float drawY = -(FLOAT_803308ec * sizeY - (FLOAT_803308ec * *(float*)((char*)this + 0x3D80) + baseY));
        CColor colorStorage(0xFF, 0xFF, 0xFF, 0xFF);

        if ((*(unsigned int*)((char*)this + 0x3D8C) & 1) == 0) {
            float alphaF = FLOAT_80330908 * stateBlend * stageBlend;
            colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
            MenuPcs.SetColor(colorStorage);

            int tex = ((*(unsigned int*)((char*)this + 0x3D8C) & 0x200) != 0) ? 2 : 0xB;
            MenuPcs.DrawWindow(drawX, drawY, sizeX, sizeY, static_cast<CMenuPcs::TEX>(tex), FLOAT_8033092c);

            if (((*(int*)((char*)this + 0x3D94) >= 0) || (*(int*)((char*)this + 0x3D98) >= 0)) &&
                (((*(unsigned int*)((char*)this + 0x3D8C) >> 10) & 7) != 0)) {
                unsigned int iconAnchor = ((*(unsigned int*)((char*)this + 0x3D8C) >> 10) & 7) - 1;
                unsigned int anchorX = iconAnchor & 1;
                unsigned int anchorY = iconAnchor & 2;
                MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x14));
                colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
                MenuPcs.SetColor(colorStorage);
                float iconX = drawX + FLOAT_80330938 + ((anchorX == 0) ? sizeX - FLOAT_8033093C : FLOAT_803308d8);
                float iconY = drawY + ((anchorY != 0) ? FLOAT_80330940 + sizeY : FLOAT_80330944);
                MenuPcs.DrawRect(
                    anchorX != 0 ? 8 : 0, iconX, iconY, FLOAT_8033093C, FLOAT_80330948,
                    (float)(anchorY != 0 ? 144 : 0), FLOAT_803308d8, FLOAT_80330914, FLOAT_80330914,
                    FLOAT_803308d8);

                CFlatDataView* flatData = reinterpret_cast<CFlatDataView*>(&Game.m_cFlatDataArr[1]);
                if (*(int*)((char*)this + 0x3D98) >= 0) {
                    font->SetScale(FLOAT_8033094C);
                    font->SetShadow(1);
                    font->SetMargin(FLOAT_803308d8);
                    float textWidth = font->GetWidth(flatData->m_table[2].index[*(int*)((char*)this + 0x3D98)]);
                    font->DrawInit();
                    font->SetTlut(0xF);
                    colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
                    font->SetColor(colorStorage.color);
                    font->SetPosX(iconX + ((anchorX == 0) ? FLOAT_80330954 - textWidth : FLOAT_80330950));
                    font->SetPosY(iconY + (float)(anchorY != 0 ? 8 : 31));
                    font->Draw(flatData->m_table[2].index[*(int*)((char*)this + 0x3D98)]);
                    MenuPcs.DrawInit();
                }

                if (*(int*)((char*)this + 0x3D94) >= 0) {
                    int itemIndex = *(int*)((char*)this + 0x3D94);
                    colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
                    MenuPcs.SetColor(colorStorage);
                    MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x18));
                    SetExternalTlut__8CTextureFPvi(MenuPcs.m_textures[0x18], 0, 1);
                    MenuPcs.DrawRect(
                        (anchorX != 0 && ((*(unsigned int*)((char*)this + 0x3D8C) & 4) == 0)) ? 8 : 0,
                        iconX + (float)(anchorX != 0 ? 13 : 83), iconY + FLOAT_80330958, FLOAT_8033095C, FLOAT_80330960,
                        (float)((itemIndex % 8) * 0x30), (float)((itemIndex / 8) * 0x30), FLOAT_80330914, FLOAT_80330914,
                        FLOAT_803308d8);
                }
            }
        }

        if ((*(int*)((char*)this + 0x0C) == 1) && ((*(unsigned int*)((char*)this + 0x3D8C) & 0x2000) != 0)) {
            float windowScale = stateBlend * stageBlend;
            float pulseScale = FLOAT_80330970 * (FLOAT_80330914 - windowScale) + FLOAT_80330914;
            float time = fmod(FLOAT_80330974 * (float)*(int*)((char*)this + 0x10), (float)DOUBLE_80330978);
            if (time > FLOAT_80330914) {
                time = FLOAT_803308e8 - time;
            }

            float angle = FLOAT_80330910 * time;
            float sinX = sinf(FLOAT_80330980 + angle);
            float sinY = sinf(angle);
            MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0x1E));
            int shadowAlpha = (int)((FLOAT_803308ec * (FLOAT_80330908 * windowScale)) * stageBlend);
            colorStorage = CColor(0, 0, 0, shadowAlpha);
            MenuPcs.SetColor(colorStorage);
            float promptX = FLOAT_803308f8 + drawX;
            float promptY = FLOAT_8033092c + drawY;
            float waveX = promptX + FLOAT_80330984 * (pulseScale * sinX);
            float waveY = promptY - FLOAT_80330988 * (pulseScale * sinY);
            float fadeScale = FLOAT_80330914 - pulseScale;
            MenuPcs.DrawRect(
                3, FLOAT_803308e4 + waveX, FLOAT_803308e4 + waveY, FLOAT_8033098C, FLOAT_8033095C, FLOAT_803308d8,
                FLOAT_803308d8, FLOAT_80330990 * (FLOAT_80330914 + fadeScale), FLOAT_80330990 * (pulseScale + fadeScale),
                FLOAT_803308d8);
            colorStorage = CColor(0xFF, 0xFF, 0xFF, (unsigned char)(int)((FLOAT_80330908 * windowScale) * stageBlend));
            MenuPcs.SetColor(colorStorage);
            MenuPcs.DrawRect(
                3, waveX, waveY, FLOAT_8033098C, FLOAT_8033095C, FLOAT_803308d8, FLOAT_803308d8,
                FLOAT_80330990 * pulseScale, FLOAT_80330990 * pulseScale, FLOAT_803308d8);
        }

        if (*(int*)((char*)this + 0x0C) == 1) {
            m_mes.Draw();
            MenuPcs.DrawInit();
        }
    }

    if ((*(int*)((char*)this + 0x0C) == 1) && (m_mes.GetWait() == 3)) {
        MenuPcs.SetTexture(static_cast<CMenuPcs::TEX>(0));
        float alphaF = FLOAT_80330908 * stageBlend;
        CColor colorStorage(0xFF, 0xFF, 0xFF, (unsigned char)(int)alphaF);
        MenuPcs.SetColor(colorStorage);

        MenuPcs.DrawRect(
            0, FLOAT_80330994 + *(float*)((char*)this + 0x3CB8),
            (float)*(int*)((char*)this + 0x3D34) * *(float*)((char*)this + 0x3D40) + FLOAT_803308e8 +
                *(float*)((char*)this + 0x3CBC) + *(float*)((char*)this + 0x3D3C),
            FLOAT_8033092c, FLOAT_8033092c, FLOAT_803308d8, FLOAT_803308d8, FLOAT_80330914, FLOAT_80330914, FLOAT_803308d8);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009d69c
 * PAL Size: 2292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::onCalc()
{
    if (Game.m_gameWork.m_menuStageMode != 0) {
        if ((m_menuIndex >= 1) && (m_menuIndex < 4)) {
            return;
        }
    }

    unsigned int stageBit = 0;
    if (m_menuIndex < 4) {
        stageBit = *(unsigned int*)(CFlat + 0x12A0) & *(unsigned int*)(CFlat + 0x12A4) & 1;
    } else {
        stageBit = *(unsigned int*)(CFlat + 0x12A0) & *(unsigned int*)(CFlat + 0x12A4) & 2;
    }

    unsigned int desiredStageFlag = stageBit != 0;
    if (*(unsigned int*)((char*)this + 0x3DF8) != desiredStageFlag) {
        System.Printf(const_cast<char*>(DAT_801d9e9c));
        *(unsigned int*)((char*)this + 0x3DF8) =
            ((unsigned int)__cntlzw(*(unsigned int*)((char*)this + 0x3DF8)) >> 5) & 0xFF;
        *(int*)((char*)this + 0x3DF4) = 0x10 - *(int*)((char*)this + 0x3DF4);
    }

    unsigned int timer = *(int*)((char*)this + 0x3DF4) - 1;
    *(unsigned int*)((char*)this + 0x3DF4) = timer & ~((int)timer >> 0x1F);

    if ((m_menuIndex >= 4) && (*(int*)((char*)this + 8) == 0)) {
        return;
    }

    if (m_menuIndex < 4) {
        unsigned int scriptFood = Game.m_scriptFoodBase[m_menuIndex];
        if (scriptFood != 0) {
            unsigned int foodCount = (unsigned int)*(unsigned short*)(scriptFood + 0x1C);
            int targetValue = (int)(foodCount * 6);
            if (*(int*)((char*)this + 0x3DAC) < targetValue) {
                *(int*)((char*)this + 0x3DAC) += targetValue - *(int*)((char*)this + 0x3DAC);
            } else if (targetValue < *(int*)((char*)this + 0x3DAC)) {
                *(int*)((char*)this + 0x3DAC) -= *(int*)((char*)this + 0x3DAC) - targetValue;
            }

            int currentValue = *(int*)((char*)this + 0x3DA8);
            if (currentValue < *(int*)((char*)this + 0x3DAC)) {
                int idx = currentValue / 0xC;
                int slotBase = (int)this + idx * 4;
                if (*(int*)(slotBase + 0x3DB0) == 0) {
                    *(int*)(slotBase + 0x3DB0) = 0x10;
                }

                int nextValue = *(int*)((char*)this + 0x3DA8) + 2;
                int maxValue = *(int*)((char*)this + 0x3DAC);
                if (nextValue < maxValue) {
                    maxValue = nextValue;
                }
                *(int*)((char*)this + 0x3DA8) = maxValue;
            } else if (*(int*)((char*)this + 0x3DAC) < currentValue) {
                *(unsigned int*)((char*)this + 0x3DA8) = (currentValue - 2U) & ~((int)(currentValue - 2U) >> 0x1F);

                int decValue = *(int*)((char*)this + 0x3DA8);
                int idx = decValue / 0xC;
                int slotBase = (int)this + idx * 4;
                if (*(int*)(slotBase + 0x3DD0) == 0) {
                    *(int*)(slotBase + 0x3DD0) = 0x10;
                }
                if (*(int*)((char*)this + 0x3DF0) == 0) {
                    *(int*)((char*)this + 0x3DF0) = 0x10;
                }
            }

            int base = (int)this;
            unsigned int value;
            for (int i = 0; i < 2; i++) {
                value = *(int*)(base + 0x3DB0) - 1;
                *(unsigned int*)(base + 0x3DB0) = value & ~((int)value >> 0x1F);

                value = *(int*)(base + 0x3DD0) - 1;
                *(unsigned int*)(base + 0x3DD0) = value & ~((int)value >> 0x1F);

                value = *(int*)(base + 0x3DB4) - 1;
                *(unsigned int*)(base + 0x3DB4) = value & ~((int)value >> 0x1F);

                value = *(int*)(base + 0x3DD4) - 1;
                *(unsigned int*)(base + 0x3DD4) = value & ~((int)value >> 0x1F);

                value = *(int*)(base + 0x3DB8) - 1;
                *(unsigned int*)(base + 0x3DB8) = value & ~((int)value >> 0x1F);

                value = *(int*)(base + 0x3DD8) - 1;
                *(unsigned int*)(base + 0x3DD8) = value & ~((int)value >> 0x1F);

                value = *(int*)(base + 0x3DBC) - 1;
                *(unsigned int*)(base + 0x3DBC) = value & ~((int)value >> 0x1F);

                value = *(int*)(base + 0x3DDC) - 1;
                *(unsigned int*)(base + 0x3DDC) = value & ~((int)value >> 0x1F);

                base += 0x10;
            }

            value = *(int*)((char*)this + 0x3DF0) - 1;
            *(unsigned int*)((char*)this + 0x3DF0) = value & ~((int)value >> 0x1F);
        }
    }

    if (*(int*)((char*)this + 8) == 0) {
        return;
    }

    int state = *(int*)((char*)this + 0xC);
    if (state < 2) {
        if (state == 0) {
            (void)sin(FLOAT_80330980 +
                      (FLOAT_80330910 * (float)*(int*)((char*)this + 0x10)) / (float)*(int*)((char*)this + 0x14));
        } else {
            *(float*)((char*)this + 0x3D84) = FLOAT_80330914;
            m_mes.Calc();

            unsigned int downMask = 0;
            unsigned int repeatMask = 0;
            int maxButtons = *(int*)((char*)this + 0x10);
            if (maxButtons > 0) {
                for (int button = 0; button < 4; button++) {
                    if ((*(unsigned int*)((char*)this + 0x3D90) & (1U << button)) != 0) {
                        downMask |= MenuPcs.GetButtonDown(button) & 0xFFFF;
                        repeatMask |= MenuPcs.GetButtonRepeat(button) & 0xFFFF;
                    }
                }
            }

            int wait = m_mes.GetWait();
            if (wait == 3) {
                int cursor = *(int*)((char*)this + 0x3D34);
                int altCursor = *(int*)((char*)this + 0x3D38);
                if ((repeatMask & 8) != 0) {
                    cursor--;
                    if (cursor < 0) {
                        cursor = *(int*)((char*)this + 0x3D30) - 1;
                    }
                    if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0) {
                        Sound.PlaySe(1, 0x40, 0x7F, 0);
                    }
                } else if ((repeatMask & 4) != 0) {
                    cursor++;
                    if (*(int*)((char*)this + 0x3D30) <= cursor) {
                        cursor = 0;
                    }
                    if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0) {
                        Sound.PlaySe(1, 0x40, 0x7F, 0);
                    }
                } else if ((downMask & 0x200) != 0) {
                    if (altCursor < 0) {
                        if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0) {
                            Sound.PlaySe(1, 0x40, 0x7F, 0);
                        }
                    } else {
                        cursor = altCursor;
                        if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0) {
                            Sound.PlaySe(3, 0x40, 0x7F, 0);
                        }
                    }
                }

                *(int*)((char*)this + 0x3D34) = cursor;
                if ((altCursor >= 0) && (cursor == altCursor)) {
                    cursor = -1;
                }
                *(int*)((char*)this + 0x3CDC) = cursor;
            } else {
                int wait1 = m_mes.GetWait();
                if (((wait1 == 1) || (m_mes.GetWait() == 5)) &&
                    (*(int*)((char*)this + 0x3CC8) == 0)) {
                    *(int*)((char*)this + 0x3CC8) = 1;
                    *(int*)((char*)this + 0x3CD8) = 0;
                }
            }

            bool advance = false;
            if ((downMask & 0x100) == 0) {
                advance = (*(int*)((char*)this + 0x3CC8) != 0) &&
                          (*(int*)((char*)this + 0x3CD8) == *(int*)((char*)this + 0x3CD4));
            } else {
                int wait2 = m_mes.GetWait();
                if (wait2 == 0) {
                    *(int*)((char*)this + 0x3C9C) = *(int*)((char*)this + 0x3C98) + 1000;
                    m_mes.useFlag(*(int*)((char*)this + 0x3C28), 1);
                } else {
                    int wait3 = m_mes.GetWait();
                    if ((wait3 == 3) && ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                        Sound.PlaySe(2, 0x40, 0x7F, 0);
                    }
                    int wait4 = m_mes.GetWait();
                    if ((wait4 != 1) && (m_mes.GetWait() != 5) &&
                        (*(int*)((char*)this + 0x3C90) == 0) && ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                        Sound.PlaySe(0xC, 0x40, 0x7F, 0);
                    }
                }

                if (*(int*)((char*)this + 0x3CC8) == 0) {
                    *(int*)((char*)this + 0x3CC8) = 1;
                    *(int*)((char*)this + 0x3CD8) = 0;
                }
                advance = (*(int*)((char*)this + 0x3CC8) != 0) &&
                          (*(int*)((char*)this + 0x3CD8) == *(int*)((char*)this + 0x3CD4));
            }

            if (advance) {
                if (*(int*)((char*)this + 0x3C90) == 0) {
                    m_mes.Next();
                } else {
                    int wait5 = m_mes.GetWait();
                    if (wait5 != 4) {
                        *(int*)((char*)this + 0x3DA4) = 0;
                        if (*(int*)((char*)this + 0x0C) < 2) {
                            if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x40) == 0) {
                                *(int*)((char*)this + 0x0C) = 2;
                                *(int*)((char*)this + 0x10) = 0;
                                *(int*)((char*)this + 0x14) = 4;
                                if (((*(unsigned int*)((char*)this + 0x3D8C) & 1) == 0) &&
                                    ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                                    Sound.PlaySe(6, 0x40, 0x7F, 0);
                                }
                            } else {
                                CFlatRuntime::CStack stack[2];
                                m_mes.Set(0, 0);
                                stack[0].m_word = *(int*)((char*)this + 0x18);
                                stack[1].m_word = *(int*)((char*)this + 0x3DA4);
                                reinterpret_cast<CFlatRuntime*>(CFlat)->SystemCall(0, 1, 3, 2, stack, 0);
                                *(int*)((char*)this + 0x0C) = 4;
                                *(int*)((char*)this + 0x08) = 0;
                                if (*(int*)((char*)this + 0x18) < 4) {
                                    SetFade__9CRingMenuFi(*(void**)((char*)&MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 1);
                                }
                            }
                        }
                    }
                }
            }
        }
    } else if (state < 4) {
        if (state == 3) {
            float step = FLOAT_80330914 - (float)*(int*)((char*)this + 0x10) / (float)*(int*)((char*)this + 0x14);
            *(float*)((char*)this + 0x3D84) = FLOAT_803308ec * (FLOAT_80330914 + (float)sin(FLOAT_80330910 * step + FLOAT_80330980));
        }
    }

    *(int*)((char*)this + 0x10) = *(int*)((char*)this + 0x10) + 1;
    if (*(int*)((char*)this + 0x14) < *(int*)((char*)this + 0x10)) {
        int nextState = *(int*)((char*)this + 0x0C);
        if (nextState == 2) {
            *(int*)((char*)this + 0x0C) = 3;
            *(int*)((char*)this + 0x10) = 0;
            *(int*)((char*)this + 0x14) = 8;
        } else if (nextState < 2) {
            if (nextState == 0) {
                *(int*)((char*)this + 0x0C) = 1;
                *(int*)((char*)this + 0x10) = 0;
                *(int*)((char*)this + 0x14) = 0;
            }
        } else if (nextState < 4) {
            CFlatRuntime::CStack stack[2];
            *(int*)((char*)this + 0x0C) = 4;
            *(int*)((char*)this + 0x10) = 0;
            *(int*)((char*)this + 0x14) = 0;
            m_mes.Set(0, 0);
            stack[0].m_word = *(int*)((char*)this + 0x18);
            stack[1].m_word = *(int*)((char*)this + 0x3DA4);
            reinterpret_cast<CFlatRuntime*>(CFlat)->SystemCall(0, 1, 3, 2, stack, 0);
            *(int*)((char*)this + 0x0C) = 4;
            *(int*)((char*)this + 0x08) = 0;
            if (*(int*)((char*)this + 0x18) < 4) {
                SetFade__9CRingMenuFi(*(void**)((char*)&MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 1);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8009df90
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::Destroy()
{
    m_mes.Set(0, 0);
    Destroy__5CMenuFv(this);
}

/*
 * --INFO--
 * PAL Address: 0x8009dfd0
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::Create()
{
    Destroy();
    Create__5CMenuFv(this);

    float defaultValue = FLOAT_803308d8;
    m_offsetY = defaultValue;
    m_offsetX = defaultValue;
    m_active = 0;
    m_state = 4;
    m_stageFadeTimer = 0;
    m_stageFadeOut = 0;

    if (m_menuIndex < 4) {
        int x = 0x10;
        if ((m_menuIndex & 1) != 0) {
            x = 0x270;
        }
        m_baseX = (float)x;

        int y = 0x18;
        if ((m_menuIndex & 2) != 0) {
            y = 0x1B0;
        }
        defaultValue = FLOAT_803308d8;
        m_baseY = (float)y;
        m_windowWidth = defaultValue;
        m_windowHeight = defaultValue;
        m_windowScale = defaultValue;
        m_fromScriptPosition = 0;
        m_flags = 0;
        m_heartValue = 0;
        m_heartTarget = 0;
        memset(m_heartGrowTimers, 0, sizeof(m_heartGrowTimers));
        memset(m_heartDropTimers, 0, sizeof(m_heartDropTimers));
        m_foodShakeTimer = 0;
    }

    m_nameIndex = 0;
    m_itemIndex = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8009e0fc
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMesMenu::~CMesMenu()
{
    Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x8009e17c
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMesMenu::CMesMenu()
{
}
