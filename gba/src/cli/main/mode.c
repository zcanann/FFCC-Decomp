#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "obj.h"
#include "session.h"
#include "radar.h"
#include "window.h"
#include "screen.h"

struct Window gWindows[5];
s8 gOpenMenuReq;
u16 gMask;

extern u32 gScreenUnused;
s32 CmdListScreen_Init(void);
s32 CmdListScreen_Main(void);
s32 CmdListScreen_Exit(void);
s32 ItemScreen_Init(void);
s32 ItemScreen_Main(void);
s32 ItemScreen_Exit(void);
s32 EquipScreen_Init(void);
s32 EquipScreen_Main(void);
s32 EquipScreen_Exit(void);
s32 ArtifactScreen_Init(void);
s32 ArtifactScreen_Main(void);
s32 ArtifactScreen_Exit(void);
s32 TmpArtifactScreen_Init(void);
s32 TmpArtifactScreen_Main(void);
s32 TmpArtifactScreen_Exit(void);
s32 GilScreen_Init(void);
s32 GilScreen_Main(void);
s32 GilScreen_Exit(void);
s32 FavoriteScreen_Init(void);
s32 FavoriteScreen_Main(void);
s32 FavoriteScreen_Exit(void);
s32 FamilyScreen_Init(void);
s32 FamilyScreen_Main(void);
s32 FamilyScreen_Exit(void);
s32 LetterScreen_Update(void);
s32 MenuScreen_Init(void);
s32 MenuScreen_Main(void);
s32 MenuScreen_Exit(void);
s32 CMakeNameScreen_Init(void);
s32 CMakeNameScreen_Main(void);
s32 CMakeNameScreen_Exit(void);
s32 CMakeGenderScreen_Init(void);
s32 CMakeGenderScreen_Main(void);
s32 CMakeGenderScreen_Exit(void);
s32 CMakeLookScreen_Init(void);
s32 CMakeLookScreen_Main(void);
s32 CMakeLookScreen_Exit(void);
s32 CMakeJobScreen_Init(void);
s32 CMakeJobScreen_Main(void);
s32 CMakeJobScreen_Exit(void);
s32 CMakeConfirmScreen_Init(void);
s32 CMakeConfirmScreen_Main(void);
s32 CMakeConfirmScreen_Exit(void);
s32 ShopTopScreen_Init(void);
s32 ShopTopScreen_Main(void);
s32 ShopTopScreen_Exit(void);
s32 ShopBuyScreen_Init(void);
s32 ShopBuyScreen_Main(void);
s32 ShopBuyScreen_Exit(void);
s32 ShopSellScreen_Init(void);
s32 ShopSellScreen_Main(void);
s32 ShopSellScreen_Exit(void);
s32 SmithTopScreen_Init(void);
s32 SmithTopScreen_Main(void);
s32 SmithTopScreen_Exit(void);
s32 SmithForgeScreen_Init(void);
s32 SmithForgeScreen_Main(void);
s32 SmithForgeScreen_Exit(void);
s32 SmithEquipScreen_Init(void);
s32 SmithEquipScreen_Main(void);
s32 SmithEquipScreen_Exit(void);

struct ScreenFuncs gFieldScreens[] = {
    { RadarScreen_Init, RadarScreen_Main, RadarScreen_Exit },
    { CmdListScreen_Init, CmdListScreen_Main, CmdListScreen_Exit },
    { ItemScreen_Init, ItemScreen_Main, ItemScreen_Exit },
    { EquipScreen_Init, EquipScreen_Main, EquipScreen_Exit },
    { ArtifactScreen_Init, ArtifactScreen_Main, ArtifactScreen_Exit },
    { TmpArtifactScreen_Init, TmpArtifactScreen_Main, TmpArtifactScreen_Exit },
    { GilScreen_Init, GilScreen_Main, GilScreen_Exit },
    { FavoriteScreen_Init, FavoriteScreen_Main, FavoriteScreen_Exit },
    { FamilyScreen_Init, FamilyScreen_Main, FamilyScreen_Exit },
    { LetterScreen_Update, LetterScreen_Update, LetterScreen_Update },
    { MenuScreen_Init, MenuScreen_Main, MenuScreen_Exit },
    { MsgScreen_Init, MsgScreen_Main, MsgScreen_Main },
    { NULL, NULL, NULL },
    { MsgScreen_Init, MsgScreen_Main, MsgScreen_Main },
    { NULL, NULL, NULL },
};

struct ScreenFuncs gCMakeScreens[] = {
    { CMakeNameScreen_Init, CMakeNameScreen_Main, CMakeNameScreen_Exit },
    { CMakeGenderScreen_Init, CMakeGenderScreen_Main, CMakeGenderScreen_Exit },
    { CMakeLookScreen_Init, CMakeLookScreen_Main, CMakeLookScreen_Exit },
    { CMakeJobScreen_Init, CMakeJobScreen_Main, CMakeJobScreen_Exit },
    { CMakeConfirmScreen_Init, CMakeConfirmScreen_Main, CMakeConfirmScreen_Exit },
    { Screen_Idle, Screen_Idle, Screen_Idle },
};

struct ScreenFuncs gShopScreens[] = {
    { ShopTopScreen_Init, ShopTopScreen_Main, ShopTopScreen_Exit },
    { ShopBuyScreen_Init, ShopBuyScreen_Main, ShopBuyScreen_Exit },
    { ShopSellScreen_Init, ShopSellScreen_Main, ShopSellScreen_Exit },
    { Screen_Idle, Screen_Idle, Screen_Idle },
};

struct ScreenFuncs gSmithScreens[] = {
    { SmithTopScreen_Init, SmithTopScreen_Main, SmithTopScreen_Exit },
    { SmithForgeScreen_Init, SmithForgeScreen_Main, SmithForgeScreen_Exit },
    { SmithEquipScreen_Init, SmithEquipScreen_Main, SmithEquipScreen_Exit },
    { Screen_Idle, Screen_Idle, Screen_Idle },
};

void Mode_Init(void)
{
    vu16 ie;

    gMode = MODE_FIELD;
    CMake_Reset();
    Smith_ResetList();
    gScreen = SCREEN_RADAR;
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
    MenuScreen_SetReturn(SCREEN_RADAR);
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
        if (gLinkStarted || gScreen == SCREEN_WAITING) {
            if (gScreen == SCREEN_RADAR && gRadarType == RADAR_SCOUTER)
                ret = ScouterScreen_Init();
            else
                ret = gFieldScreens[gScreen].init();
        }
    } else if (gScreenPhase == PHASE_MAIN) {
        if (gScreen == SCREEN_RADAR && gRadarType == RADAR_SCOUTER)
            ret = ScouterScreen_Main();
        else
            ret = gFieldScreens[gScreen].main();
    } else {
        if (gScreen == SCREEN_RADAR && gRadarType == RADAR_SCOUTER)
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
                gScreen = SCREEN_MENU;
            } else if (gScreen == SCREEN_MENU) {
                gScreen = gWindows[0].cursor;
            } else if (gScreen == SCREEN_LETTERS && gLetterAttachKind == 2) {
                gScreen = SCREEN_GIL;
            } else if (gScreen != SCREEN_LETTERS && gLetterAttachKind) {
                gScreen = SCREEN_LETTERS;
            } else {
                Xfer_ClearLetterData();
                if (gScreenStep > 0) {
                    gScreen++;
                    if (gFieldScreens[gScreen].init == 0)
                        gScreen++;
                    if (gScreen > SCREEN_LETTERS)
                        gScreen = SCREEN_RADAR;
                } else {
                    gScreen--;
                    if (gFieldScreens[gScreen].init == 0)
                        gScreen--;
                    if (gScreen < SCREEN_RADAR)
                        gScreen = SCREEN_LETTERS;
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
            if (gScreen == SCREEN_CMAKE_NAME && ret < 0) {
                gLinkStarted = 0;
                gMenuHasInput = 0;
                gScreen = SCREEN_CMAKE_DONE;
            } else if (gScreen != SCREEN_CMAKE_CONFIRM) {
                if (ret > 0)
                    gScreen++;
                else
                    gScreen--;
            } else if (ret > 0) {
                gLinkStarted = 0;
                gMenuHasInput = 0;
                gScreen = SCREEN_CMAKE_DONE;
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
            if (gScreen == SCREEN_SHOP_TOP && ret < 0) {
                gLinkStarted = 0;
                gMenuHasInput = 0;
                gScreen = SCREEN_SHOP_DONE;
            } else if (gScreen == SCREEN_SHOP_TOP && ret != 0) {
                gShopMenuPos[0] = gWindows[0].cursor;
                switch (gShopMenuPos[0]) {
                case 0:
                    gScreen = SCREEN_SHOP_BUY;
                    break;
                case 1:
                    gScreen = SCREEN_SHOP_SELL;
                    break;
                }
            } else {
                gScreen = SCREEN_SHOP_TOP;
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
            if (gScreen == SCREEN_SMITH_TOP) {
                if (ret > 0) {
                    gScreen = SCREEN_SMITH_FORGE;
                } else {
                    gMenuHasInput = 0;
                    gScreen = SCREEN_SMITH_DONE;
                }
            } else if (gScreen == SCREEN_SMITH_FORGE) {
                if (ret > 0)
                    gScreen = SCREEN_SMITH_EQUIP;
                else
                    gScreen = SCREEN_SMITH_TOP;
            } else {
                gScreen = SCREEN_SMITH_TOP;
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
            gMsgScreenId = NOTICE_SEE_TV;
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
    if (gWasConnected || gScreen != SCREEN_WAITING) {
        Screen_Restart();
        Obj_FreeAllPalettes();
    }
}

/*
 * --INFO--
 * PAL Address: 0x0200586C
 * PAL Size: 248b
 * EN Address: 0x0200586C
 * EN Size: 200b
 * JP Address: 0x02005A20
 * JP Size: 200b
 */
void Screen_Restart(void)
{
    vu16 ie;
    s32 i;
#if defined(VERSION_GCCP01)
    u16 *map;
#endif

    if (gWasConnected || gScreen != SCREEN_WAITING) {
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
#if defined(VERSION_GCCP01)
        map = (u16 *)0x06007FE0;
        DmaClear16(0, 0, map, 32);
        map = (u16 *)0x0600DFE0;
        DmaClear16(0, 0, map, 32);
#endif
        Link_SendScreenId((s8)gScreen);
    }
}

s32 Screen_Idle(void)
{
    return 0;
}
