#include "global.h"
#include "link.h"
#include "xfer.h"
#include "main.h"
#include "text.h"
#include "obj.h"
#include "radar.h"
#include "window.h"
#include "screen.h"

static s8 sRadarMapShown;

void RadarScreen_DrawFrame(void);

void RadarScreen_Setup(void)
{
    REG_DISPCNT = 0x9940;
    gSubState = 0;
    DmaClear32(0, 0, gWindows, sizeof(struct Window) * 5);
    StatusWin_Setup(0, 0);
    Text_SetFill(1, 0);
    Text_LoadPalette(4, 0, 0);
    Font_LoadPalette(0x050000E0, 1);
    Font_LoadPalette(0x05000120, Link_GetPlayerNo() + 5);
    Text_CopyFill(0x06000000);
    Obj_AllocPalette(17, 0);
    Obj_LoadToBg(17, 0, 0, 0);
    Obj_LoadToBg(14, 1, 1, 0);
    sRadarMapShown = 0;
    Bg_CopyBackdropToRadar();
    Radar_LoadPalette();
    Radar_ClearMap();
    if (gRadarType == 0)
        Radar_InitMap();
    Bg_SetBlend(1);
    RadarScreen_DrawFrame();
    BonusWin_Setup(3);
    gScreenInitDone = 1;
}

s32 RadarScreen_Init(void)
{
    struct Window *win = gWindows;
    s32 ret;

    Text_SetFill(1, 0);
    if (gScreenInitDone == 0) {
        RadarScreen_Setup();
        if (gScreenInitDone == 0) {
            if (gMenuHasInput && (gKeysNew & (L_BUTTON | R_BUTTON))) {
                if (gKeysNew & R_BUTTON)
                    gScreenStep = 1;
                else
                    gScreenStep = -1;
                m4aSongNumStart(6);
                gScreenPhase++;
                REG_DISPCNT = 0x9F40;
                Bg_SetBlend(0);
                return 1;
            }
            if (gScreenInitDone == 0)
                return 0;
        }
    }
    ret = StatusWin_Open(0);
    if (ret) {
        win->anim = 0;
        REG_DISPCNT = 0x9F40;
        BonusWin_Show(3, 9);
    }
    return ret;
}

s32 RadarScreen_Main(void)
{
    s16 dx;
    s16 dy;

    StatusWin_DrawIcon(0);
    if ((gDataFlags & (DATA_BASE_POS | DATA_MAP)) != 0x402 && sRadarMapShown) {
        REG_DISPCNT = 0x9940;
        Radar_ClearMap();
        sRadarMapShown = 0;
    }
    Text_SetFill(1, 0);
    if (Link_IsConnected() && gRadarMode) {
        Radar_DrawParty();
        if (gRadarType == 1 || gRadarType == 3) {
            Radar_DrawEnemies();
            if (gRadarType == 3)
                Radar_DrawTreasures();
        }
        if (gRadarType == 0)
            Radar_DrawMapObjs();
    }
    if ((gDataFlags & (DATA_BASE_POS | DATA_MAP)) == 0x402 && sRadarMapShown == 0 && gRadarMode) {
        REG_DISPCNT = 0x9F40;
        if (gRadarType == 0)
            Radar_DrawMap();
        sRadarMapShown = 1;
    }
    if (gRadarMode && gRadarType == 0 && !(gStaticMap & 1) && (gDataFlags & DATA_BASE_POS)) {
        Radar_GetBaseDelta(&dx, &dy);
        if (dx < -6 || dx > 6 || dy > 6 || dy <= -7)
            Radar_DrawMap();
        else
            Radar_ScrollMap(dx, dy);
    }
    if (gMenuHasInput) {
        if (gKeysNew & (L_BUTTON | R_BUTTON)) {
            if (gKeysNew & R_BUTTON)
                gScreenStep = 1;
            else
                gScreenStep = -1;
            REG_DISPCNT = 0x9940;
            m4aSongNumStart(6);
            BonusWin_Hide(gWindows[3].bg);
            return 1;
        }
        if (gKeysNew & A_BUTTON) {
            m4aSongNumStart(0);
        } else if (gKeysNew & B_BUTTON) {
            gOpenMenuReq = 1;
            m4aSongNumStart(3);
            return 1;
        }
    }
    return 0;
}

s32 RadarScreen_Exit(void)
{
    struct Window *win = gWindows;
    s32 ret = 0;

    Text_SetFill(1, 0);
    Window_Close(win);
    if ((win->anim >> 3) >= win->height - 1) {
        ret = 1;
        Obj_FreePalette(17);
        Bg_SetBlend(0);
        REG_DISPCNT = 0x9F40;
        win->anim = 0;
    } else {
        win->anim += 8;
    }
    return ret;
}

void RadarScreen_DrawFrame(void)
{
    u16 buf[30];
    s32 row;
    s32 col;
    s32 tile;
    s32 v;
    u16 *dst;
    s32 attr = 0xB000;

    for (row = 0; row < 16; row++) {
        dst = Bg_GetMapPtr(1, 0, row);
        if (row == 1 || row + 1 >= 16) {
            for (col = 0; col < ARRAY_COUNT(buf); col++)
                buf[col] = 0x3FF;
        }
        for (col = 0; col < 20; col++) {
            tile = 36;
            if (row == 0 || row + 1 >= 16) {
                if (col == 1 || col == 18)
                    tile = 37;
                else if (col >= 2 && col <= 17)
                    tile = 38;
                v = attr | tile;
                buf[col] = v;
                if (row != 0)
                    buf[col] = v | 0x800;
                if (col > 17)
                    buf[col] |= 0x400;
            } else {
                if (row >= 3 && row <= 13)
                    break;
                tile = (row == 1 || row == 14) ? 39 : 40;
                v = attr | tile;
                buf[0] = v;
                if (row > 13)
                    buf[0] = v | 0x800;
                buf[19] = buf[0] | 0x400;
            }
        }
        DmaCopy16(0, buf, dst, 40);
    }
}

void Radar_DrawMapObjs(void)
{
    s16 x, y;
    s32 origin[2];
    s32 right, bottom;
    s32 i;

    if (gMapObjs.count == 0)
        return;
    Radar_GetBasePos(&x, &y);
    origin[0] = x - 80;
    origin[1] = y - 64;
    right = x + 80;
    bottom = y + 64;
    for (i = 0; i < gMapObjs.count; i++) {
        s32 frame = gMapObjs.entries[i].type;
        s32 dx, dy, n, stepx, stepy, j;

        if (!(gMapObjs.drawFlags & (1 << i)))
            continue;
        dx = gMapObjs.entries[i].x1 - gMapObjs.entries[i].x0;
        dy = gMapObjs.entries[i].y1 - gMapObjs.entries[i].y0;
        if (ABS(dx) >= ABS(dy)) {
            n = ABS(dx) >> 3;
            stepx = 8;
            stepy = dy / n;
            if ((ABS(dx) & 7) > 3)
                n++;
        } else {
            n = ABS(dy) >> 3;
            stepx = dx / n;
            stepy = 8;
            if ((ABS(dy) & 7) > 3)
                n++;
        }
        n++;
        for (j = 0; j < n; j++) {
            x = gMapObjs.entries[i].x0 + j * stepx;
            y = gMapObjs.entries[i].y0 + j * stepy;
            if (x >= origin[0] && right >= x && y >= origin[1] && bottom >= y) {
                x -= origin[0];
                y -= origin[1];
                Obj_Draw(x - 4, y - 4, 2, frame, Obj_GetPalette(2, frame), 2, 0);
            }
        }
    }
}

void Radar_DrawParty(void)
{
    s32 i;
    s16 frame = 8;

    for (i = 0; i <= 3; i++, frame++) {
        struct Marker *p = Radar_GetPartyMarker(i);

        if (p->visible) {
            s16 x = p->x + 76;
            s16 y = p->y + 60;

            Obj_Draw(x, y, 2, frame, Obj_GetPalette(2, frame), 2, 0);
        }
    }
}

void Radar_DrawEnemies(void)
{
    s32 i;

    for (i = 0; i < 64; i++) {
        u8 type = gEnemyMarkers[i].kind;

        if (gEnemyMarkers[i].visible && (u8)(type - 1) < 3) {
            s16 x = gEnemyMarkers[i].x + 76;
            s16 y = gEnemyMarkers[i].y + 60;
            s32 frame = gEnemyMarkers[i].kind + 15;

            Obj_Draw(x, y, 2, frame, Obj_GetPalette(2, frame), 2, 0);
        }
    }
}

void Radar_DrawTreasures(void)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (gTreasureMarkers[i].visible && (u8)(gTreasureMarkers[i].kind - 4) < 2) {
            s16 x = gTreasureMarkers[i].x + 76;
            s16 y = gTreasureMarkers[i].y + 60;
            s32 frame = gTreasureMarkers[i].kind + 2;

            Obj_Draw(x, y, 2, frame, Obj_GetPalette(2, frame), 2, 0);
        }
    }
}
