#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "obj.h"
#include "session.h"
#include "radar.h"
#include "window.h"
#include "screen.h"

extern u32 gScreenUnused;
extern const struct ScreenFuncs gFieldScreens[];
extern const struct ScreenFuncs gCMakeScreens[];
extern const struct ScreenFuncs gShopScreens[];
extern const struct ScreenFuncs gSmithScreens[];

void Mode_Init(void)
{
    vu16 ie;

    gMode = MODE_FIELD;
    CMake_Reset();
    Smith_ResetList();
    gScreen = 0;
    Screen_Reset();
    gShopMenuPos[0] = 0;
    gShopMenuPos[1] = -1;
    gLetterAttachKind = 0;
    gInfoWinReady = 0;
    Scouter_SetDirty(0);
    ie = REG_IE;
    REG_IE = 0;
    gLinkEstablished = 0;
    REG_IE = ie;
    gMask = 0;
    DmaClear32(0, 0, gWindows, sizeof(gWindows));
    Bg_ClearMaps();
    gSavedScreen = gScreen;
    gOpenMenuReq = 0;
    MenuScreen_SetReturn(0);
}

s32 Mode_Update(void)
{
    s32 ret;

    switch (gMode) {
    case MODE_FIELD:
        ret = FieldMode_Update();
        break;
    case MODE_CMAKE:
        ret = CMakeMode_Update();
        break;
    case MODE_SHOP:
        ret = ShopMode_Update();
        break;
    case MODE_SMITH:
        ret = SmithMode_Update();
        break;
    case MODE_CONTROLLER:
    default:
        ret = CtrlMode_Update();
        break;
    }
    return ret;
}

s32 FieldMode_Update(void)
{
    s32 ret;
    s32 i;

    if (gLinkEstablished) {
        Screen_Reset();
        Bg_ClearMaps();
    }
    if (gReconnectPending && gWasConnected && gLinkStarted) {
        gScreen = gSavedScreen;
        Bg_SetBlend(0);
        REG_DISPCNT = 0x9F40;
        Bg_ClearMaps();
        Screen_Reset();
        gReconnectPending = 0;
    }

    ret = 0;
    if (gScreenPhase == PHASE_INIT) {
        if (gLinkStarted || gScreen == 13) {
            if (gScreen == 0 && gRadarType == 2)
                ret = ScouterScreen_Init();
            else
                ret = gFieldScreens[gScreen].init();
        }
    } else if (gScreenPhase == PHASE_MAIN) {
        if (gScreen == 0 && gRadarType == 2)
            ret = ScouterScreen_Main();
        else
            ret = gFieldScreens[gScreen].main();
    } else {
        if (gScreen == 0 && gRadarType == 2)
            ret = ScouterScreen_Exit();
        else
            ret = gFieldScreens[gScreen].exit();
    }

    if (ret) {
        if (gScreenPhase <= 1) {
            gScreenPhase++;
        } else {
            if (gOpenMenuReq) {
                MenuScreen_SetReturn(gScreen);
                gScreen = 10;
            } else if (gScreen == 10) {
                gScreen = gWindows[0].cursor;
            } else if (gScreen == 9 && gLetterAttachKind == 2) {
                gScreen = 6;
            } else if (gScreen != 9 && gLetterAttachKind) {
                gScreen = 9;
            } else {
                Xfer_ClearLetterData();
                if (gScreenStep > 0) {
                    gScreen++;
                    if (gFieldScreens[gScreen].init == 0)
                        gScreen++;
                    if (gScreen > 9)
                        gScreen = 0;
                } else {
                    gScreen--;
                    if (gFieldScreens[gScreen].init == 0)
                        gScreen--;
                    if (gScreen < 0)
                        gScreen = 9;
                }
            }
            gScreenStep = 0;
            Bg_ClearMaps();
            Screen_Reset();
        }
        for (i = 0; i < 5; i++)
            gWindows[i].anim = 0;
    }
    return ret;
}

s32 CMakeMode_Update(void)
{
    s32 ret;
    s32 i;

    if (gLinkEstablished) {
        Screen_Reset();
        Bg_ClearMaps();
    }

    ret = 0;
    if (gScreenPhase == PHASE_INIT) {
        if (gLinkStarted)
            ret = gCMakeScreens[gScreen].init();
    } else if (gScreenPhase == PHASE_MAIN) {
        ret = gCMakeScreens[gScreen].main();
    } else {
        ret = gCMakeScreens[gScreen].exit();
    }

    if (ret) {
        if (gScreenPhase <= 1) {
            gScreenPhase++;
        } else {
            if (gScreen == 0 && ret < 0) {
                gLinkStarted = 0;
                gMenuHasInput = 0;
                gScreen = 5;
            } else if (gScreen != 4) {
                if (ret > 0)
                    gScreen++;
                else
                    gScreen--;
            } else if (ret > 0) {
                gLinkStarted = 0;
                gMenuHasInput = 0;
                gScreen = 5;
            } else {
                gScreen = gSubState;
            }
            Screen_Restart();
            Bg_ClearMaps();
        }
        for (i = 0; i < 5; i++)
            gWindows[i].anim = 0;
    }
    return ret;
}

s32 ShopMode_Update(void)
{
    s32 ret;
    s32 i;

    if (gLinkEstablished) {
        Screen_Reset();
        Bg_ClearMaps();
        gInfoWinReady = 0;
        gShopMenuPos[0] = 0;
    }

    ret = 0;
    if (gScreenPhase == PHASE_INIT) {
        if (gLinkStarted)
            ret = gShopScreens[gScreen].init();
    } else if (gScreenPhase == PHASE_MAIN) {
        ret = gShopScreens[gScreen].main();
    } else {
        ret = gShopScreens[gScreen].exit();
    }

    if (ret) {
        if (gScreenPhase <= 1) {
            gScreenPhase++;
        } else {
            if (gScreen == 0 && ret < 0) {
                gLinkStarted = 0;
                gMenuHasInput = 0;
                gScreen = 3;
            } else if (gScreen == 0 && ret != 0) {
                gShopMenuPos[0] = gWindows[0].cursor;
                switch (gShopMenuPos[0]) {
                case 0:
                    gScreen = 1;
                    break;
                case 1:
                    gScreen = 2;
                    break;
                }
            } else {
                gScreen = 0;
            }
            Screen_Restart();
            Bg_ClearMaps();
        }
        gInfoWinReady = 0;
        for (i = 0; i < 5; i++)
            gWindows[i].anim = 0;
    }
    return ret;
}

s32 SmithMode_Update(void)
{
    s32 ret;
    s32 i;

    if (gLinkEstablished) {
        Screen_Reset();
        Bg_ClearMaps();
        gInfoWinReady = 0;
        gShopMenuPos[0] = 0;
    }

    ret = 0;
    if (gScreenPhase == PHASE_INIT) {
        if (gLinkStarted)
            ret = gSmithScreens[gScreen].init();
    } else if (gScreenPhase == PHASE_MAIN) {
        ret = gSmithScreens[gScreen].main();
    } else {
        ret = gSmithScreens[gScreen].exit();
    }

    if (ret) {
        if (gScreenPhase <= 1) {
            gScreenPhase++;
        } else {
            if (gScreen == 0) {
                if (ret > 0) {
                    gScreen = 1;
                } else {
                    gMenuHasInput = 0;
                    gScreen = 3;
                }
            } else if (gScreen == 1) {
                if (ret > 0)
                    gScreen = 2;
                else
                    gScreen = 0;
            } else {
                gScreen = 0;
            }
            Screen_Restart();
            Bg_ClearMaps();
        }
        gInfoWinReady = 0;
        for (i = 0; i < 5; i++)
            gWindows[i].anim = 0;
    }
    return ret;
}

s32 CtrlMode_Update(void)
{
    s32 ret;
    s32 i;

    if (gLinkEstablished) {
        Screen_Reset();
        Bg_ClearMaps();
    }

    ret = 0;
    if (gScreenPhase == PHASE_INIT) {
        if (gLinkStarted) {
            gMsgScreenId = 3;
            ret = MsgScreen_Init();
        }
    } else {
        ret = MsgScreen_Main();
    }

    if (ret) {
        if (gScreenPhase <= 1) {
            gScreenPhase++;
        } else {
            gScreenPhase = PHASE_INIT;
            Screen_Restart();
            Bg_ClearMaps();
        }
        for (i = 0; i < 5; i++)
            gWindows[i].anim = 0;
    }
    return ret;
}

void Screen_Reset(void)
{
    if (gWasConnected || gScreen != 13) {
        Screen_Restart();
        Obj_FreeAllPalettes();
    }
}

void Screen_Restart(void)
{
    vu16 ie;
    s32 i;
    u16 *map;

    if (gWasConnected || gScreen != 13) {
        gScreenUnused = 0;
        gScreenPhase = PHASE_INIT;
        gScreenInitDone = 0;
        gSubMode = 0;
        gSubState = 0;
        gOpenMenuReq = 0;
        Bg_SetScroll(15, 0, 0);
        ie = REG_IE;
        REG_IE = 0;
        gLinkEstablished = 0;
        REG_IE = ie;
        Bg_SetBlend(0);
        for (i = 0; i < 32; i++)
            Obj_SetAffine(i, 0, 256, 256);
        REG_DISPCNT = 0x9F40;
        gDataFlags &= 0xFC0F;
        map = (u16 *)0x06007FE0;
        DmaClear16(0, 0, map, 32);
        map = (u16 *)0x0600DFE0;
        DmaClear16(0, 0, map, 32);
        Link_SendScreenId((s8)gScreen);
    }
}

s32 Screen_Idle(void)
{
    return 0;
}
