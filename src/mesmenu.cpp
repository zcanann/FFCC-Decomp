#include "ffcc/mesmenu.h"
#include "ffcc/p_game.h"

#include <math.h>
#include <string.h>

extern "C" {
void Create__5CMenuFv(void* menu);
void Set__4CMesFPci(void* mes, char* script, int flags);
void SetPosition__4CMesFff(void* mes, float x, float y);
void PlaySe__6CSoundFiiii(void* sound, int id, int volume, int pan, int unk);
void SetFade__9CRingMenuFi(void* ringMenu, int fade);
int __cntlzw(unsigned int);
void SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
    void* flatRuntime, int object, int type, int id, int stackCount, void* stack, void* stack2);
void* __ct__6CColorFUcUcUcUc(void* color, unsigned char r, unsigned char g, unsigned char b, unsigned char a);
void SetColor__8CMenuPcsFR6CColor(void* menuPcs, void* color);
void SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(void* menuPcs, int tex);
void DrawRect__8CMenuPcsFUlfffffffff(
    void* menuPcs, unsigned long flags, float x, float y, float w, float h, float u, float v, float uvScaleX, float uvScaleY,
    float rot);
unsigned int GetButtonDown__8CMenuPcsFi(void* menuPcs, int button);
unsigned int GetButtonRepeat__8CMenuPcsFi(void* menuPcs, int button);
void Calc__4CMesFv(void* mes);
void Next__4CMesFv(void* mes);
int GetWait__4CMesFv(void* mes);
int useFlag__4CMesFii(void* mes, int flag, int value);
void Printf__7CSystemFPce(CSystem* system, const char* format, ...);

extern unsigned char CFlat[];
extern unsigned char MenuPcs[];
extern unsigned char Sound[];
extern const char DAT_801d9e9c[];
extern int DAT_8020f998[4];
extern float FLOAT_803308d8;
extern float FLOAT_803308dc;
extern float FLOAT_803308e0;
extern float FLOAT_803308e4;
extern float FLOAT_803308e8;
extern float FLOAT_803308ec;
extern float FLOAT_803308f0;
extern float FLOAT_803308f4;
extern float FLOAT_803308f8;
extern float FLOAT_80330908;
extern float FLOAT_8033090c;
extern float FLOAT_80330910;
extern float FLOAT_80330914;
extern float FLOAT_80330918;
extern float FLOAT_8033091c;
extern float FLOAT_80330920;
extern float FLOAT_80330924;
extern float FLOAT_80330928;
extern float FLOAT_80330980;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMesMenu::CMesMenu()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMesMenu::~CMesMenu()
{
	// TODO
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
    typedef void (*VFunc)(void*);

    ((VFunc)(*(unsigned int*)this + 0x10))(this);
    Create__5CMenuFv(this);

    *(float*)((char*)this + 0x3D78) = FLOAT_803308d8;
    *(float*)((char*)this + 0x3D74) = FLOAT_803308d8;
    *(int*)((char*)this + 8) = 0;
    *(int*)((char*)this + 0xC) = 4;
    *(int*)((char*)this + 0x3DF4) = 0;
    *(int*)((char*)this + 0x3DF8) = 0;

    if (*(int*)((char*)this + 0x18) < 4) {
        unsigned int x = 0x10;
        if ((*(int*)((char*)this + 0x18) & 1) != 0) {
            x = 0x270;
        }
        *(float*)((char*)this + 0x3D6C) = (float)x;

        unsigned int y = 0x18;
        if ((*(int*)((char*)this + 0x18) & 2) != 0) {
            y = 0x1B0;
        }
        *(float*)((char*)this + 0x3D70) = (float)y;

        *(float*)((char*)this + 0x3D7C) = FLOAT_803308d8;
        *(float*)((char*)this + 0x3D80) = FLOAT_803308d8;
        *(float*)((char*)this + 0x3D84) = FLOAT_803308d8;
        *(int*)((char*)this + 0x3D88) = 0;
        *(int*)((char*)this + 0x3D8C) = 0;
        *(int*)((char*)this + 0x3DA8) = 0;
        *(int*)((char*)this + 0x3DAC) = 0;
        memset((char*)this + 0x3DB0, 0, 0x20);
        memset((char*)this + 0x3DD0, 0, 0x20);
        *(int*)((char*)this + 0x3DF0) = 0;
    }

    *(int*)((char*)this + 0x3D98) = 0;
    *(int*)((char*)this + 0x3D94) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::Destroy()
{
	// TODO
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
    int menuIndex = *(int*)((char*)this + 0x18);
    if ((Game.game.m_gameWork.m_menuStageMode != 0) && (menuIndex > 0) && (menuIndex < 4)) {
        return;
    }

    unsigned int stageBit = 0;
    if (menuIndex < 4) {
        stageBit = *(unsigned int*)(CFlat + 0x12A0) & *(unsigned int*)(CFlat + 0x12A4) & 1;
    } else {
        stageBit = *(unsigned int*)(CFlat + 0x12A0) & *(unsigned int*)(CFlat + 0x12A4) & 2;
    }

    unsigned int currentStageFlag = *(unsigned int*)((char*)this + 0x3DF8);
    unsigned int desiredStageFlag = (unsigned int)(-(int)stageBit) >> 0x1F;
    if (currentStageFlag != desiredStageFlag) {
        Printf__7CSystemFPce(&System, DAT_801d9e9c);
        *(unsigned int*)((char*)this + 0x3DF8) = ((unsigned int)__cntlzw(currentStageFlag) >> 5) & 0xFF;
        *(int*)((char*)this + 0x3DF4) = 0x10 - *(int*)((char*)this + 0x3DF4);
    }

    unsigned int timer = *(int*)((char*)this + 0x3DF4) - 1;
    *(unsigned int*)((char*)this + 0x3DF4) = timer & ~((int)timer >> 0x1F);

    if ((menuIndex > 3) && (*(int*)((char*)this + 8) == 0)) {
        return;
    }

    if (menuIndex < 4) {
        unsigned int scriptFood = Game.game.m_scriptFoodBase[menuIndex];
        if (scriptFood != 0) {
            unsigned int foodCount = (unsigned int)*(unsigned short*)(scriptFood + 0x1C);
            int targetValue = (int)(foodCount * 6);
            if (*(int*)((char*)this + 0x3DAC) < targetValue) {
                *(int*)((char*)this + 0x3DAC) = targetValue;
            } else if (targetValue < *(int*)((char*)this + 0x3DAC)) {
                *(unsigned int*)((char*)this + 0x3DAC) = foodCount * 6;
            }

            int currentValue = *(int*)((char*)this + 0x3DA8);
            if (currentValue < *(int*)((char*)this + 0x3DAC)) {
                int idx = currentValue / 0xC + (currentValue >> 0x1F);
                int slotBase = (int)this + (idx - (idx >> 0x1F)) * 4;
                if (*(int*)(slotBase + 0x3DB0) == 0) {
                    *(int*)(slotBase + 0x3DB0) = 0x10;
                }

                int nextValue = currentValue + 2;
                int maxValue = *(int*)((char*)this + 0x3DAC);
                if (nextValue < maxValue) {
                    maxValue = nextValue;
                }
                *(int*)((char*)this + 0x3DA8) = maxValue;
            } else if (*(int*)((char*)this + 0x3DAC) < currentValue) {
                *(unsigned int*)((char*)this + 0x3DA8) = (currentValue - 2U) & ~((int)(currentValue - 2U) >> 0x1F);

                int decValue = *(int*)((char*)this + 0x3DA8);
                int idx = decValue / 0xC + (decValue >> 0x1F);
                int slotBase = (int)this + (idx - (idx >> 0x1F)) * 4;
                if (*(int*)(slotBase + 0x3DD0) == 0) {
                    *(int*)(slotBase + 0x3DD0) = 0x10;
                }
                if (*(int*)((char*)this + 0x3DF0) == 0) {
                    *(int*)((char*)this + 0x3DF0) = 0x10;
                }
            }

            int i = 2;
            int base = (int)this;
            unsigned int value;
            do {
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
                i--;
            } while (i != 0);

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
            Calc__4CMesFv((char*)this + 0x1C);

            unsigned int downMask = 0;
            unsigned int repeatMask = 0;
            int maxButtons = *(int*)((char*)this + 0x10);
            if (maxButtons > 0) {
                for (int button = 0; button < 4; button++) {
                    if ((*(unsigned int*)((char*)this + 0x3D90) & (1U << button)) != 0) {
                        downMask |= GetButtonDown__8CMenuPcsFi(MenuPcs, button) & 0xFFFF;
                        repeatMask |= GetButtonRepeat__8CMenuPcsFi(MenuPcs, button) & 0xFFFF;
                    }
                }
            }

            int wait = GetWait__4CMesFv((char*)this + 0x1C);
            if (wait == 3) {
                int cursor = *(int*)((char*)this + 0x3D34);
                int altCursor = *(int*)((char*)this + 0x3D38);
                if ((repeatMask & 8) != 0) {
                    cursor--;
                    if (cursor < 0) {
                        cursor = *(int*)((char*)this + 0x3D30) - 1;
                    }
                    if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0) {
                        PlaySe__6CSoundFiiii(Sound, 1, 0x40, 0x7F, 0);
                    }
                } else if ((repeatMask & 4) != 0) {
                    cursor++;
                    if (*(int*)((char*)this + 0x3D30) <= cursor) {
                        cursor = 0;
                    }
                    if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0) {
                        PlaySe__6CSoundFiiii(Sound, 1, 0x40, 0x7F, 0);
                    }
                } else if ((downMask & 0x200) != 0) {
                    if (altCursor < 0) {
                        if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0) {
                            PlaySe__6CSoundFiiii(Sound, 1, 0x40, 0x7F, 0);
                        }
                    } else {
                        cursor = altCursor;
                        if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0) {
                            PlaySe__6CSoundFiiii(Sound, 3, 0x40, 0x7F, 0);
                        }
                    }
                }

                *(int*)((char*)this + 0x3D34) = cursor;
                if ((altCursor >= 0) && (cursor == altCursor)) {
                    cursor = -1;
                }
                *(int*)((char*)this + 0x3CDC) = cursor;
            } else {
                int wait1 = GetWait__4CMesFv((char*)this + 0x1C);
                if (((wait1 == 1) || (GetWait__4CMesFv((char*)this + 0x1C) == 5)) &&
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
                int wait2 = GetWait__4CMesFv((char*)this + 0x1C);
                if (wait2 == 0) {
                    *(int*)((char*)this + 0x3C9C) = *(int*)((char*)this + 0x3C98) + 1000;
                    useFlag__4CMesFii((char*)this + 0x1C, *(int*)((char*)this + 0x3C28), 1);
                } else {
                    int wait3 = GetWait__4CMesFv((char*)this + 0x1C);
                    if ((wait3 == 3) && ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                        PlaySe__6CSoundFiiii(Sound, 2, 0x40, 0x7F, 0);
                    }
                    int wait4 = GetWait__4CMesFv((char*)this + 0x1C);
                    if ((wait4 != 1) && (GetWait__4CMesFv((char*)this + 0x1C) != 5) &&
                        (*(int*)((char*)this + 0x3C90) == 0) && ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                        PlaySe__6CSoundFiiii(Sound, 0xC, 0x40, 0x7F, 0);
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
                    Next__4CMesFv((char*)this + 0x1C);
                } else {
                    int wait5 = GetWait__4CMesFv((char*)this + 0x1C);
                    *(int*)((char*)this + 0x3DA4) = 0;
                    if ((wait5 != 4) && (*(int*)((char*)this + 0x0C) < 2)) {
                        if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x40) == 0) {
                            *(int*)((char*)this + 0x0C) = 2;
                            *(int*)((char*)this + 0x10) = 0;
                            *(int*)((char*)this + 0x14) = 4;
                            if (((*(unsigned int*)((char*)this + 0x3D8C) & 1) == 0) &&
                                ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                                PlaySe__6CSoundFiiii(Sound, 6, 0x40, 0x7F, 0);
                            }
                        } else {
                            int stack[2];
                            Set__4CMesFPci((char*)this + 0x1C, 0, 0);
                            stack[0] = *(int*)((char*)this + 0x18);
                            stack[1] = *(int*)((char*)this + 0x3DA4);
                            SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
                                CFlat, 0, 1, 3, 2, stack, 0);
                            *(int*)((char*)this + 0x0C) = 4;
                            *(int*)((char*)this + 0x08) = 0;
                            if (*(int*)((char*)this + 0x18) < 4) {
                                SetFade__9CRingMenuFi(*(void**)((char*)MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 1);
                            }
                        }
                    }
                }
            }
        }
    } else if (state < 4) {
        if (state == 2) {
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
            int stack[2];
            *(int*)((char*)this + 0x0C) = 4;
            *(int*)((char*)this + 0x10) = 0;
            *(int*)((char*)this + 0x14) = 0;
            Set__4CMesFPci((char*)this + 0x1C, 0, 0);
            stack[0] = *(int*)((char*)this + 0x18);
            stack[1] = *(int*)((char*)this + 0x3DA4);
            SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
                CFlat, 0, 1, 3, 2, stack, 0);
            *(int*)((char*)this + 0x0C) = 4;
            *(int*)((char*)this + 0x08) = 0;
            if (*(int*)((char*)this + 0x18) < 4) {
                SetFade__9CRingMenuFi(*(void**)((char*)MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 1);
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::onDraw()
{
	// TODO
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
    unsigned int scriptFood = Game.game.m_scriptFoodBase[*(int*)((char*)this + 0x18)];
    if (scriptFood == 0) {
        return;
    }

    unsigned int foodCount = (unsigned int)*(unsigned short*)(scriptFood + 0x1C);
    int targetValue = (int)(foodCount * 6);
    if (*(int*)((char*)this + 0x3DAC) < targetValue) {
        *(int*)((char*)this + 0x3DAC) = targetValue;
    } else if (targetValue < *(int*)((char*)this + 0x3DAC)) {
        *(unsigned int*)((char*)this + 0x3DAC) = foodCount * 6;
    }

    int currentValue = *(int*)((char*)this + 0x3DA8);
    if (currentValue < *(int*)((char*)this + 0x3DAC)) {
        int index = currentValue / 0xC + (currentValue >> 0x1F);
        int base = (int)this + (index - (index >> 0x1F)) * 4;
        if (*(int*)(base + 0x3DB0) == 0) {
            *(int*)(base + 0x3DB0) = 0x10;
        }

        int nextValue = currentValue + 2;
        int maxValue = *(int*)((char*)this + 0x3DAC);
        if (nextValue < maxValue) {
            maxValue = nextValue;
        }
        *(int*)((char*)this + 0x3DA8) = maxValue;
    } else if (*(int*)((char*)this + 0x3DAC) < currentValue) {
        *(unsigned int*)((char*)this + 0x3DA8) = (currentValue - 2U) & ~((int)(currentValue - 2U) >> 0x1F);

        int decValue = *(int*)((char*)this + 0x3DA8);
        int index = decValue / 0xC + (decValue >> 0x1F);
        int base = (int)this + (index - (index >> 0x1F)) * 4;
        if (*(int*)(base + 0x3DD0) == 0) {
            *(int*)(base + 0x3DD0) = 0x10;
        }
        if (*(int*)((char*)this + 0x3DF0) == 0) {
            *(int*)((char*)this + 0x3DF0) = 0x10;
        }
    }

    int i = 2;
    int base = (int)this;
    do {
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
        i--;
    } while (i != 0);

    unsigned int value = *(int*)((char*)this + 0x3DF0) - 1;
    *(unsigned int*)((char*)this + 0x3DF0) = value & ~((int)value >> 0x1F);
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

    unsigned int scriptFood = Game.game.m_scriptFoodBase[*(int*)((char*)this + 0x18)];
    if (scriptFood == 0 || alpha <= FLOAT_803308d8) {
        return;
    }

    unsigned char colorStorage[8];
    int colorAlpha = (int)(FLOAT_80330908 * alpha);
    __ct__6CColorFUcUcUcUc(colorStorage, 0xFF, 0xFF, 0xFF, (unsigned char)colorAlpha);
    SetColor__8CMenuPcsFR6CColor(MenuPcs, colorStorage);
    SetTexture__8CMenuPcsFQ28CMenuPcs3TEX(MenuPcs, 0x17);

    float baseX = x + (float)((*(unsigned int*)((char*)this + 0x18) & 1) != 0 ? 0x30 : 0x4C);
    float baseY = y + FLOAT_8033090c;
    int valueOffset = 0;
    int timerOffset = 0;

    int heartCount = (int)((unsigned short)*(unsigned short*)(scriptFood + 0x1A) >> 1);
    for (int i = 0; i < heartCount; i++) {
        unsigned int addTimer = *(unsigned int*)((char*)this + 0x3DB0 + timerOffset);
        int heartValue = *(int*)((char*)this + 0x3DA8) - valueOffset;

        float pulse = (FLOAT_8033091c *
                       (float)sin(FLOAT_80330910 * -(((float)addTimer * FLOAT_80330918) - FLOAT_80330914)) +
                       FLOAT_80330914) *
                      FLOAT_80330920;

        unsigned int subTimer = *(unsigned int*)((char*)this + 0x3DD0 + timerOffset);
        int shakeX = 0;
        int shakeY = 0;
        if (subTimer != 0) {
            shakeX = ((int)subTimer >> 2) * DAT_8020f998[(subTimer + 1) & 3];
            shakeY = ((int)subTimer >> 2) * DAT_8020f998[subTimer & 3];
        }

        float drawX = baseX + (float)shakeX;
        float drawY = baseY + (float)shakeY;

        DrawRect__8CMenuPcsFUlfffffffff(
            MenuPcs, 3, drawX, drawY, FLOAT_803308dc, FLOAT_803308dc, FLOAT_803308d8, FLOAT_803308d8, pulse, pulse,
            FLOAT_803308d8);

        if (heartValue > 0) {
            int fillAmount = heartValue;
            if (fillAmount > 0x0B) {
                fillAmount = 0x0B;
            }

            float u = *(unsigned short*)(scriptFood + 0x42) != 0 ? 24.0f : 0.0f;
            float v = (float)((0x0C - fillAmount) * 0x18);
            DrawRect__8CMenuPcsFUlfffffffff(
                MenuPcs, 3, drawX, drawY, FLOAT_803308dc, FLOAT_803308dc, u, v, pulse, pulse, FLOAT_803308d8);
        }

        baseX += ((*(unsigned int*)((char*)this + 0x18) & 1) != 0) ? FLOAT_80330924 : FLOAT_80330928;
        valueOffset += 0x0C;
        timerOffset += 4;
    }
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
    Set__4CMesFPci((char*)this + 0x1C, 0, 0);
    *(int*)((char*)this + 0x0C) = 4;
    *(int*)((char*)this + 0x08) = 0;
    if (*(int*)((char*)this + 0x18) < 4) {
        SetFade__9CRingMenuFi(*(void**)((char*)MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 1);
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
 * PAL Address: 0x8009b5fc
 * PAL Size: 744b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMesMenu::Open(char* script, int x, int y, int flags, int unk1, int unk2, int unk3)
{
    *(float*)((char*)this + 0x3D78) = FLOAT_803308d8;
    *(float*)((char*)this + 0x3D74) = FLOAT_803308d8;
    *(int*)((char*)this + 0x08) = 1;
    *(int*)((char*)this + 0x3DA4) = 0;
    *(unsigned int*)((char*)this + 0x3D8C) = (unsigned int)flags;

    if (*(int*)((char*)this + 0x18) < 4) {
        SetFade__9CRingMenuFi(*(void**)((char*)MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 0);
        *(float*)((char*)this + 0x3D9C) = FLOAT_803308e0;
        *(float*)((char*)this + 0x3DA0) = FLOAT_803308e4;
    } else {
        *(float*)((char*)this + 0x3D6C) = (float)x;
        *(float*)((char*)this + 0x3D70) = (float)y;
        *(int*)((char*)this + 0x3D88) = 1;
        *(float*)((char*)this + 0x3D9C) = FLOAT_803308dc;
        *(float*)((char*)this + 0x3DA0) = FLOAT_803308dc;
        *(unsigned int*)((char*)this + 0x3D50) = (unsigned int)(-(flags >> 1 & 1) & 0x1C);
        *(unsigned int*)((char*)this + 0x3D54) = ((unsigned int)__cntlzw((unsigned int)(flags & 2))) >> 5;
    }

    *(int*)((char*)this + 0x3D90) = unk1;
    *(int*)((char*)this + 0x3D94) = unk2;
    *(int*)((char*)this + 0x3D98) = unk3;
    Set__4CMesFPci((char*)this + 0x1C, script, flags & 0x20);

    *(float*)((char*)this + 0x3D7C) = FLOAT_803308e8 * *(float*)((char*)this + 0x3D9C) + *(float*)((char*)this + 0x3CC0);
    *(float*)((char*)this + 0x3D80) = FLOAT_803308e8 * *(float*)((char*)this + 0x3DA0) + *(float*)((char*)this + 0x3CC4);

    if (*(int*)((char*)this + 0x18) < 4) {
        if ((flags & 0x100) == 0 && *(float*)((char*)this + 0x3D7C) < FLOAT_803308f0) {
            *(float*)((char*)this + 0x3D7C) = FLOAT_803308f0;
        }
    } else if ((flags & 8) == 0) {
        if ((flags & 0x8000) != 0) {
            *(float*)((char*)this + 0x3D6C) -= *(float*)((char*)this + 0x3D7C);
        }
    } else {
        *(float*)((char*)this + 0x3D6C) = -(FLOAT_803308ec * *(float*)((char*)this + 0x3D7C) - *(float*)((char*)this + 0x3D6C));
        *(float*)((char*)this + 0x3D70) = -(FLOAT_803308ec * *(float*)((char*)this + 0x3D80) - *(float*)((char*)this + 0x3D70));
    }

    float posY;
    unsigned int index = (unsigned int)*(int*)((char*)this + 0x18);
    if ((int)index < 4) {
        if ((index & 2) == 0) {
            posY = FLOAT_803308f8 + *(float*)((char*)this + 0x3DA0) + *(float*)((char*)this + 0x3D70) +
                   *(float*)((char*)this + 0x3D78);
        } else {
            posY = (*(float*)((char*)this + 0x3DA0) + (*(float*)((char*)this + 0x3D70) - FLOAT_803308f4) +
                    *(float*)((char*)this + 0x3D78)) -
                   *(float*)((char*)this + 0x3D80);
        }
    } else {
        posY = *(float*)((char*)this + 0x3DA0) + *(float*)((char*)this + 0x3D70) + *(float*)((char*)this + 0x3D78);
    }

    float posX;
    if ((int)index < 4 && (index & 1) != 0) {
        posX = (*(float*)((char*)this + 0x3D9C) + *(float*)((char*)this + 0x3D6C) + *(float*)((char*)this + 0x3D74)) -
               *(float*)((char*)this + 0x3D7C);
    } else {
        posX = *(float*)((char*)this + 0x3D9C) + *(float*)((char*)this + 0x3D6C) + *(float*)((char*)this + 0x3D74);
    }
    SetPosition__4CMesFff((char*)this + 0x1C, posX, posY);

    *(unsigned int*)((char*)this + 0x0C) = ((unsigned int)flags >> 4) & 1;
    *(int*)((char*)this + 0x10) = 0;
    *(int*)((char*)this + 0x14) = 8;
    if ((flags & 0x11) == 0 && ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
        PlaySe__6CSoundFiiii(Sound, 5, 0x40, 0x7F, 0);
    }
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
    int stack[2];

    *(int*)((char*)this + 0x3DA4) = closeReason;
    if (*(int*)((char*)this + 0x0C) <= 1) {
        if ((*(unsigned int*)((char*)this + 0x3D8C) & 0x40) != 0) {
            Set__4CMesFPci((char*)this + 0x1C, 0, 0);
            stack[0] = *(int*)((char*)this + 0x18);
            stack[1] = *(int*)((char*)this + 0x3DA4);
            SystemCall__12CFlatRuntimeFPQ212CFlatRuntime7CObjectiiiPQ212CFlatRuntime6CStackPQ212CFlatRuntime6CStack(
                CFlat, 0, 1, 3, 2, stack, 0);
            *(int*)((char*)this + 0x0C) = 4;
            *(int*)((char*)this + 0x08) = 0;
            if (*(int*)((char*)this + 0x18) < 4) {
                SetFade__9CRingMenuFi(*(void**)((char*)MenuPcs + 0x13C + *(int*)((char*)this + 0x18) * 4), 1);
            }
        } else {
            *(int*)((char*)this + 0x0C) = 2;
            *(int*)((char*)this + 0x10) = 0;
            *(int*)((char*)this + 0x14) = 4;
            if (((*(unsigned int*)((char*)this + 0x3D8C) & 1) == 0) &&
                ((*(unsigned int*)((char*)this + 0x3D8C) & 0x4000) == 0)) {
                PlaySe__6CSoundFiiii(Sound, 6, 0x40, 0x7F, 0);
            }
        }
    }
}

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
 * Address:	TODO
 * Size:	TODO
 */
void CMesMenu::close(int)
{
	// TODO
}
