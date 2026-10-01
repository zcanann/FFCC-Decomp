#include "global.h"
#include "main.h"
#include "joybus.h"
#include "obj.h"
#include "effect.h"
#include "camera.h"
#include "field.h"
#include "route.h"
#include "text.h"
#include "sound.h"
#include "random.h"

#define IWRAM 0x03000000

typedef void (*IntrFunc)(void);

const u32 lbl_0200EC98[2] = { 0, 0 };

/* Interrupt handlers dispatched by intr_main, highest priority first */
const IntrFunc IntrTable[] = {
    Link_JoyIntr,
    VBlankIntr,
    VCountIntr,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
    IntrDummy,
};

const char gAssertText[] = "ASSERT";
const char gAssertFileFmt[] = "FILE=%s";
const char gAssertLineFmt[] = "LINE=%d";
const char gAssertCountFmt[] = "CNT=%d";
const char gLoadingText[] = "LOADING...";
const char gLapTimeFmt[] = "LAP   %d:%02d:%02d   ";
const char gBlankTimeText[] = "                   ";
const char gTotalTimeFmt[] = "TOTAL %d:%02d:%02d   ";
const char gRank1stText[] = "1ST";
const char gRank2ndText[] = "2ND";
const char gRank3rdText[] = "3RD";
const char gRank4thText[] = "4TH";
const char gRank5thText[] = "5TH";
const char gRank6thText[] = "6TH";
const char gRank7thText[] = "7TH";
const char gRank8thText[] = "8TH";
const char gRankNoneText[] = "---";
const char gPauseText[] = "PAUSE";

struct Main gMain;
u16 gHeldKeys;
u16 gNewKeys;
u8 gIntrMainRam[0x200];
u8 gFieldTiles[128][128];
struct BgAffine gBgAffine[160];
struct OamData gOamBuffer[128];
struct OamMatrix gOamMatrices[32];
char gPrintBuffer[256];
vu32 gVBlankCounter;
s32 gFrameCounter;
s32 gRaceFrameCounter;
vu16 gSkyScrollPrev;
vu16 gSkyScroll;
u8 gBgAffineHdma[0xA00];
u32 gJoySendData;
vu8 gVCountPhase;
volatile s8 gShownLap;
u8 gWrongWayShown;
struct Actor *gChaserPlayer;
struct Actor *gChaserEnemy;
u32 gMainUnused;
u32 gMainUnused2;
const char *gAssertFile;
s32 gAssertLine;

/* Glyphs; the digits 1-3 are large, 4-8 small */
#define GLYPH_DIGIT(n)    (8 - (n))
#define GLYPH_GO          8
#define GLYPH_FINISH      9
#define GLYPH_ST          10
#define GLYPH_ND          11
#define GLYPH_RD          12
#define GLYPH_TH          13
#define GLYPH_LAP         14
#define GLYPH_WRONG_WAY_1 15
#define GLYPH_WRONG_WAY_2 16
#define GLYPH_WRONG_WAY_3 17
#define GLYPH_FINAL_LAP   20

void AssertFailed(const char *file, s32 line)
{
    s32 i;

    gAssertFile = file;
    gAssertLine = line;
    Text_Printf(&gTextLayer, 0, 5, gAssertText);
    Text_Printf(&gTextLayer, 0, 6, gAssertFileFmt, file + 16);
    Text_Printf(&gTextLayer, 0, 7, gAssertLineFmt, line);
    gMain.textEnabled = 1;
    for (i = 0;; i++) {
        Text_Printf(&gTextLayer, 0, 8, gAssertCountFmt, i % 10);
        Text_Flush(&gTextLayer);
        VBlankIntrWait();
    }
}

void WaitFrames(u32 frames)
{
    u32 end = gVBlankCounter + frames;

    while (gVBlankCounter < end) {
        VBlankIntrWait();
        UpdateSound();
    }
}

static inline void SetCameraPlayer(struct Camera *cam, u8 no)
{
    cam->player = no;
}

void DebugPrintf(const char *fmt, ...)
{
    char buf[512];
    va_list ap;

    va_start(ap, fmt);
    vsprintf(buf, fmt, ap);
    va_end(ap);
}

void UpdateSound(void)
{
    m4aSoundMain();
}

void AgbMain(void)
{
    u16 keys;

    gVBlankCounter = 0;
    REG_IME = 0;
    InitGame(&gMain);
    for (;;) {
        ReadKeys();
        keys = REG_KEYINPUT ^ KEY_MASK;
        gMain.newKeys = keys & ~gMain.heldKeys;
        gMain.heldKeys = keys;
        if (gLinkSynced != 0 && (u8)(gMain.state - STATE_COUNTDOWN) <= STATE_RETRY - STATE_COUNTDOWN) {
            Field_UpdateMap(&gField);
            Mode7_UpdateAffine(&gField);
        }
        DrawGameSprites(&gMain);
        UpdateSound();
        UpdateGameState(&gMain);
        while (gVBlankCounter == 0) {
            VBlankIntrWait();
        }
        UpdateSound();
        Link_ApplyRemotePads();
        Link_BuildPadPacket();
        VBlankIntrWait();
        gVBlankCounter = 0;
        if (gMain.mode7Dirty) {
            DmaSet(gBgAffine, gBgAffineHdma, 0x84000280);
            DmaSet(gFieldTiles, VRAM + 0x8000, 0x84001000);
            gMain.mode7Dirty = 0;
        }
        if (gMain.oamDirty) {
            gMain.oamDirty = 0;
            DmaSet(gOamBuffer, OAM, 0x84000100);
        }
        Text_Flush(&gTextLayer);
        if (gMain.mode7Enabled) {
            gMain.splitLine = gMain.horizon;
        } else {
            gMain.splitLine = 0x1000;
        }
        if (gMain.textEnabled) {
            REG_DISPCNT |= DISPCNT_BG0_ON;
        } else {
            REG_DISPCNT &= ~DISPCNT_BG0_ON;
        }
        if (gMain.objEnabled) {
            REG_DISPCNT |= DISPCNT_OBJ_ON;
        } else {
            REG_DISPCNT &= ~DISPCNT_OBJ_ON;
        }
    }
}

void VBlankIntr(void)
{
    REG_IE &= ~INTR_FLAG_VCOUNT;
    REG_DISPCNT &= ~DISPCNT_BG2_ON;
    m4aSoundVSync();
    if (gMain.skyEnabled) {
        REG_DISPCNT |= DISPCNT_BG1_ON;
        if (gVBlankCounter == 0) {
            REG_BG1HOFS = (gSkyScroll + gSkyScrollPrev) >> 1;
        } else {
            REG_BG1HOFS = gSkyScroll;
            gSkyScrollPrev = gSkyScroll;
        }
    } else {
        REG_DISPCNT &= ~DISPCNT_BG1_ON;
    }
    gVBlankCounter++;
    if (gMain.mode7Enabled) {
        REG_IE |= INTR_FLAG_VCOUNT;
    }
    INTR_CHECK = 1;
}

/* Splits the screen between the sky (BG1) and the mode 7 floor (BG2) */
void VCountIntr(void)
{
    u8 line;
    u32 vcount;

    switch (gVCountPhase) {
    case 0:
        REG_DMA0CNT_H = 0;
        line = REG_VCOUNT;
        {
            vu32 *dmaRegs = (vu32 *)REG_ADDR_DMA0;
            dmaRegs[0] = (u32)&gBgAffineHdma[line * 16];
            dmaRegs[1] = (u32)&REG_BG2PA;
            dmaRegs[2] = 0xA6600004;
        }
        if (line < gMain.splitLine) {
            gVCountPhase = 1;
            REG_VCOUNT_MATCH = gMain.splitLine;
            break;
        }
    case 1:
        if (gMain.mode7Enabled) {
            REG_DISPCNT |= DISPCNT_BG2_ON;
        }
        gVCountPhase = 2;
        vcount = REG_VCOUNT;
        REG_VCOUNT_MATCH = vcount + 6;
        break;
    case 2:
        REG_DISPCNT &= ~DISPCNT_BG1_ON;
        gVCountPhase = 0;
        REG_VCOUNT_MATCH = 0;
        gVCountPhase = 3;
        REG_VCOUNT_MATCH = 158;
        break;
    case 3:
        REG_DMA0CNT_H = 0;
        gVCountPhase = 0;
        REG_VCOUNT_MATCH = 0;
        break;
    }
}

void IntrDummy(void)
{
}

void InitGame(struct Main *main)
{
    RegisterRamReset(0xC2);
    DmaFill32(0, IWRAM, 0x85001F80);
    REG_WAITCNT = 0x4014;
    DmaFill32(0, VRAM, 0x85006000);
    DmaFill32(0xA0, OAM, 0x85000100);
    DmaFill32(0, PLTT, 0x85000100);
    DmaSet(intr_main, gIntrMainRam, 0x84000080);
    INTR_VECTOR = gIntrMainRam;
    DmaFill32(0xA0, gOamBuffer, 0x85000100);
    REG_BG0HOFS = 0;
    REG_BG0VOFS = 0;
    REG_BG1HOFS = 0;
    REG_BG1VOFS = 0;
    REG_BG2PA = 0x100;
    REG_BG2PB = 0;
    REG_BG2PC = 0;
    REG_BG2PD = 0x100;
    REG_BG2X_L = 0;
    REG_BG2X_H = 0;
    REG_BG2Y_L = 0;
    REG_BG2Y_H = 0;
    REG_MOSAIC = 0;
    REG_BLDCNT = 0x1044;
    REG_BLDALPHA = 0xF08;
    m4aSoundInit();
    m4aSoundVSyncOff();
    REG_DISPCNT = 0x1001;
    SetGameState(main, STATE_LOADING);
    gVCountPhase = 0xFF;
    main->paused = 0;
    main->mode7Enabled = main->skyEnabled = main->textEnabled = main->objEnabled = 0;
    gMainUnused = 0;
    gMainUnused2 = 0;
    DmaWait();
    sgenrand(10000);
    Text_Init(&gTextLayer);
    Link_InitState();
    Camera_Init(&gCamera);
    Route_Init(gRoutes);
    PointList_Init(gPointLists);
    Field_Init(&gField);
    Game_Init(&gGame);
    Text_Init(&gTextLayer);
    Sound_Init(&gSound);
    LZ77UnCompWram(gFieldMapLz, gFieldMap);
    REG_IE = INTR_FLAG_GAMEPAK | INTR_FLAG_SERIAL | INTR_FLAG_VCOUNT | INTR_FLAG_VBLANK;
    REG_DISPSTAT = 0x28;
    REG_IME = 1;
    m4aSoundVSyncOn();
}

void UpdateGameState(struct Main *main)
{
    s32 i;
    s8 lap;
    u8 ready;
    u8 buf[16];

    gFrameCounter++;
    gRaceFrameCounter++;
    PauseMenuInput(main);
    switch (main->state) {
    case STATE_LOADING:
        if (main->timer == 0) {
            Text_Clear(&gTextLayer, 15);
            Text_Printf(&gTextLayer, 10, 9, gLoadingText);
            main->textEnabled = 1;
        }
        main->timer++;
        if (gLinkMode) {
            ready = gLinkStarted;
        } else {
            ready = main->timer > 29;
        }
        if (!ready) {
            return;
        }
        sgenrand(10000);
        SetCameraPlayer(&gCamera, gPlayerNo);
        SetGameState(main, STATE_SELECT);
        break;
    case STATE_SELECT:
        if (main->paused) {
            break;
        }
        main->readyMask &= gPlayerMask;
        if (main->readyMask == gPlayerMask) {
            SetGameState(main, STATE_COUNTDOWN);
            break;
        }
        if (main->timer == 0) {
            main->mode7Enabled = 0;
            main->skyEnabled = 1;
            main->objEnabled = 1;
            Field_SetupMenuBg(&gField);
        }
        if (main->timer > 15) {
            s32 j;

            for (j = 0; j <= 3; j++) {
                if ((main->readyMask >> j) & 1) {
                    continue;
                }
                if (gPadNew[j] & DPAD_DOWN) {
                    if (++main->select.cursor[j] > 3) {
                        main->select.cursor[j] = 0;
                    }
                    if (j == gPlayerNo) {
                        m4aSongNumStart(SE_CURSOR);
                    }
                }
                if (gPadNew[j] & DPAD_UP) {
                    if (--main->select.cursor[j] < 0) {
                        main->select.cursor[j] = 3;
                    }
                    if (j == gPlayerNo) {
                        m4aSongNumStart(SE_CURSOR);
                    }
                }
                if (gPadNew[j] & A_BUTTON) {
                    main->readyMask |= 1 << j;
                    if (j == gPlayerNo) {
                        m4aSongNumStart(SE_SELECT);
                    }
                }
            }
        }
        main->timer++;
        break;
    case STATE_COUNTDOWN:
        if (main->paused) {
            break;
        }
        if (main->timer == 0) {
            Field_SetupRaceBg(&gField);
            main->mode7Enabled = 1;
            gRaceFrameCounter = 0;
            gVCountPhase = 0;
            Text_Clear(&gTextLayer, 15);
        }
        if (main->timer == 11) {
            m4aSongNumStart(BGM_READY);
        }
        if (main->timer == 80) {
            Text_DrawGlyph(&gTextLayer, 13, 4, GLYPH_DIGIT(3), 14);
            m4aSongNumStart(SE_COUNTDOWN);
        } else if (main->timer == 110) {
            Text_DrawGlyph(&gTextLayer, 13, 4, GLYPH_DIGIT(2), 14);
            m4aSongNumStart(SE_COUNTDOWN);
        } else if (main->timer == 140) {
            Text_DrawGlyph(&gTextLayer, 13, 4, GLYPH_DIGIT(1), 14);
            m4aSongNumStart(SE_COUNTDOWN);
        } else if (main->timer == 170) {
            Text_DrawGlyph(&gTextLayer, 11, 4, GLYPH_GO, 14);
            SetGameState(main, STATE_RACE);
            m4aSongNumStart(SE_GO);
            gEngineSong = SONG_NONE;
            goto race;
        }
        main->timer++;
        break;
    case STATE_RACE:
    race:
        if (main->paused) {
            break;
        }
        if (main->timer == 30) {
            m4aSongNumStart(BGM_RACE);
            if (main->timer == 30) {
                Text_Clear(&gTextLayer, 15);
                gGame.actors[gPlayerNo].showMarker = 0;
            }
        }
        if (main->timer > 29) {
            lap = gGame.actors[gPlayerNo].lap;
            if (main->lap != lap) {
                if ((s8)(lap - gShownLap) > 0 && lap >= 0) {
                    if (main->bestLapTime > main->lapTime) {
                        main->bestLapTime = main->lastLapTime = main->lapTime;
                        main->lapTime = 0;
                    }
                    if (lap != main->lapCount) {
                        main->lapTime = 0;
                    }
                    if (main->totalTime == -1) {
                        main->totalTime = 0;
                    }
                }
                main->lap = lap;
                Text_DrawGlyph(&gTextLayer, 21, 0, GLYPH_LAP, 14);
                if (main->lapCount == 3) {
                    Text_DrawGlyph(&gTextLayer, 26, 0, 19, 14);
                } else {
                    Text_DrawGlyph(&gTextLayer, 26, 0, 18, 14);
                }
                main->showLap = 1;
                gShownLap = lap;
                if (gShownLap >= main->lapCount) {
                    gShownLap = main->lapCount - 1;
                }
                if (lap == main->lapCount) {
                    SetGameState(main, STATE_FINISH);
                    break;
                }
                if (lap == main->lapCount - 1 && !main->finalLapShown) {
                    main->finalLapShown = 1;
                    main->finalLapTimer = 96;
                }
            }
            DrawTimerAndRank(main);
            if (Game_IsWrongWay(&gGame, gCamera.player)) {
                if (main->bannerShown == 0 && main->finalLapTimer == 0 && !gWrongWayShown) {
                    Text_DrawGlyph(&gTextLayer, 9, 5, GLYPH_WRONG_WAY_1, 14);
                    Text_DrawGlyph(&gTextLayer, 15, 5, GLYPH_WRONG_WAY_2, 14);
                    Text_DrawGlyph(&gTextLayer, 21, 5, GLYPH_WRONG_WAY_3, 14);
                    gWrongWayShown = 1;
                }
            } else if (gWrongWayShown) {
                Text_EraseGlyph(&gTextLayer, 9, 5, GLYPH_WRONG_WAY_1);
                Text_EraseGlyph(&gTextLayer, 15, 5, GLYPH_WRONG_WAY_2);
                Text_EraseGlyph(&gTextLayer, 21, 5, GLYPH_WRONG_WAY_3);
                gWrongWayShown = 0;
            }
            gChaserPlayer = Game_FindChaser(&gGame, gPlayerNo, 0);
            gChaserEnemy = Game_FindChaser(&gGame, gPlayerNo, 4);
        }
        if (main->finalLapTimer) {
            if ((main->finalLapTimer & 31) == 16) {
                m4aSongNumStart(SE_FINAL_LAP);
                Text_DrawGlyph(&gTextLayer, 11, 4, GLYPH_FINAL_LAP, 14);
            } else if ((main->finalLapTimer & 31) == 1) {
                Text_EraseGlyph(&gTextLayer, 11, 4, GLYPH_FINAL_LAP);
            }
            main->finalLapTimer--;
        }
        if (++main->timer > 0xFFFFFFF0) {
            main->timer = 0xFFFFFFF0;
        }
        break;
    case STATE_FINISH:
        if (main->paused) {
            break;
        }
        if (main->timer == 0) {
            gLinkSendCmd = main->result | PAD_CODE_RESULT;
            Text_DrawGlyph(&gTextLayer, 9, 4, GLYPH_FINISH, 14);
            main->bannerShown = 1;
        }
        DrawTimerAndRank(main);
        if (main->timer == 60) {
            Text_EraseGlyph(&gTextLayer, 9, 4, GLYPH_FINISH);
            main->bannerShown = 0;
            switch (main->result) {
            case 0:
            case 1:
                Text_DrawGlyph(&gTextLayer, 13, 4, GLYPH_DIGIT(1), 14);
                Text_DrawGlyph(&gTextLayer, 17, 6, GLYPH_ST, 14);
                break;
            case 2:
                Text_DrawGlyph(&gTextLayer, 13, 4, GLYPH_DIGIT(2), 14);
                Text_DrawGlyph(&gTextLayer, 17, 6, GLYPH_ND, 14);
                break;
            case 3:
                Text_DrawGlyph(&gTextLayer, 13, 4, GLYPH_DIGIT(3), 14);
                Text_DrawGlyph(&gTextLayer, 17, 6, GLYPH_RD, 14);
                break;
            case 4:
                Text_DrawGlyph(&gTextLayer, 14, 6, GLYPH_DIGIT(4), 14);
                Text_DrawGlyph(&gTextLayer, 16, 6, GLYPH_TH, 14);
                break;
            case 5:
                Text_DrawGlyph(&gTextLayer, 14, 6, GLYPH_DIGIT(5), 14);
                Text_DrawGlyph(&gTextLayer, 16, 6, GLYPH_TH, 14);
                break;
            case 6:
                Text_DrawGlyph(&gTextLayer, 14, 6, GLYPH_DIGIT(6), 14);
                Text_DrawGlyph(&gTextLayer, 16, 6, GLYPH_TH, 14);
                break;
            case 7:
                Text_DrawGlyph(&gTextLayer, 14, 6, GLYPH_DIGIT(7), 14);
                Text_DrawGlyph(&gTextLayer, 16, 6, GLYPH_TH, 14);
                break;
            case 8:
                Text_DrawGlyph(&gTextLayer, 14, 6, GLYPH_DIGIT(8), 14);
                Text_DrawGlyph(&gTextLayer, 16, 6, GLYPH_TH, 14);
                break;
            }
        }
        main->timer++;
        if (main->select.wait != -1) {
            if (main->select.wait == 122) {
                gLinkSendCmd = PAD_CODE_RACE_END;
                SetGameState(main, STATE_RETRY);
            } else {
                main->select.wait++;
            }
        } else if ((main->finishedMask & gPlayerMask) == gPlayerMask) {
            main->select.wait = 0;
        }
        break;
    case STATE_RETRY:
        if (main->timer == 0) {
        setup:
            main->retryLinked = gLinkMode;
            if (main->retryLinked) {
                Text_LoadScreen(&gTextLayer, gRetryLinkScreenLz);
            } else {
                Text_LoadScreen(&gTextLayer, gRetrySoloScreenLz);
            }
        }
        DrawTimerAndRank(main);
        if (gLinkMode) {
            for (i = 0; i <= 3; i++) {
                if ((main->answeredMask >> i) & 1) {
                    continue;
                }
                if (gPadNew[i] & (DPAD_UP | DPAD_DOWN)) {
                    main->select.answer[i] ^= 1;
                    m4aSongNumStart(SE_CURSOR);
                }
                if (gPadNew[i] & A_BUTTON) {
                    m4aSongNumStart(SE_CURSOR);
                    if (main->select.answer[i] == 0) {
                        main->select.answer[i] = 0xFF;
                        main->readyMask |= 1 << i;
                        main->answeredMask |= 1 << i;
                        if (main->readyMask == gPlayerMask) {
                            if (i == gPlayerNo) {
                                gLinkSendCmd = PAD_CODE_CONTINUE;
                            }
                            SetGameState(main, STATE_SELECT);
                            goto end;
                        }
                    } else {
                        main->select.answer[i] |= 0xFF;
                        if (i == gPlayerNo) {
                            gLinkSendCmd = PAD_CODE_QUIT;
                        }
                        main->answeredMask |= 1 << i;
                    }
                }
            }
        } else if (main->retryLinked) {
            goto setup;
        } else if (gPadNew[gPlayerNo] & 0xFF) {
            m4aSongNumStart(SE_CURSOR);
            SetGameState(main, STATE_SELECT);
            break;
        }
        main->timer++;
        break;
    }
end:
    Sound_UpdateListener(&gSound);
    if (gLinkFrameReady && !main->paused) {
        Game_Update(&gGame);
        Camera_Update(&gCamera);
    }
}

void DrawTime(struct Main *main, u32 frames, s32 x, s32 y, const char *fmt)
{
    u16 min, sec, frac;
    u16 total;

    total = frames / 30;
    frac = (frames % 30) * 100 / 30;
    min = total / 60;
    sec = total % 60;
    Text_Printf(&gTextLayer, x, y, fmt, min, sec, frac);
}

void DrawTimerAndRank(struct Main *main)
{
    const char *str;
    u8 rank;

    if (main->lastLapTime != -1) {
        if (main->state == STATE_RACE) {
            main->totalTime++;
            main->lapTime++;
            if ((gRaceFrameCounter & 15) > 4) {
                DrawTime(main, main->lastLapTime, 0, 1, gLapTimeFmt);
            } else {
                Text_Printf(&gTextLayer, 0, 1, gBlankTimeText);
            }
            if (main->lapTime > 150) {
                main->lastLapTime = -1;
            }
        } else {
            main->lapTime++;
            if ((gRaceFrameCounter & 15) > 4 || main->lapTime > 150) {
                DrawTime(main, main->lastLapTime, 0, 1, gLapTimeFmt);
            } else {
                Text_Printf(&gTextLayer, 0, 1, gBlankTimeText);
            }
        }
    } else if (main->lapTime != main->lastLapTime) {
        if (main->state == STATE_RACE) {
            main->totalTime++;
            main->lapTime++;
        }
        DrawTime(main, main->lapTime, 0, 1, gLapTimeFmt);
    }
    if (main->totalTime != -1) {
        DrawTime(main, main->totalTime, 0, 2, gTotalTimeFmt);
    }
    if (main->state == STATE_RACE) {
        rank = Game_GetRank(&gGame, gPlayerNo);
    } else {
        rank = main->result;
    }
    switch (rank) {
    case 0:
    case 1:
        str = gRank1stText;
        break;
    case 2:
        str = gRank2ndText;
        break;
    case 3:
        str = gRank3rdText;
        break;
    case 4:
        str = gRank4thText;
        break;
    case 5:
        str = gRank5thText;
        break;
    case 6:
        str = gRank6thText;
        break;
    case 7:
        str = gRank7thText;
        break;
    case 8:
        str = gRank8thText;
        break;
    default:
        str = gRankNoneText;
        break;
    }
    Text_Print(&gTextLayer, 25, 4, 14, str);
}

void SetGameState(struct Main *main, enum GameState state)
{
    struct PointList *points;
    s32 i;
    s32 j;
    s32 k;

    main->state = state;
    switch (main->state) {
    case STATE_LOADING:
        main->timer = 0;
        break;
    case STATE_SELECT:
        m4aSongNumStop(SE_ENGINE);
        m4aSongNumStop(SE_ENGINE_ROUGH);
        m4aSongNumStop(SE_SKID);
        m4aSongNumStop(SE_ITEM_GET);
        m4aMPlayFadeOut(&gMPlayBgm, 4);
        main->timer = 0;
        main->readyMask = 0;
        for (i = 0; i <= 3; i++) {
            main->select.cursor[i] = 0;
        }
        break;
    case STATE_COUNTDOWN:
        SetCameraPlayer(&gCamera, gPlayerNo);
        main->showLap = 0;
        gShownLap = -1;
        main->lastLapTime = main->lapTime = main->totalTime = main->bestLapTime = -1;
        gWrongWayShown = 0;
        gChaserPlayer = gChaserEnemy = NULL;
        main->racerCount = gConfigRacerCount;
        main->lapCount = gConfigLapCount;
        Game_Reset(&gGame);
        for (i = 0; i <= 3; i++) {
            if ((u8)(1 << i) & gPlayerMask) {
                Game_AddPlayer(&gGame, i, main->select.answer[i]);
            }
        }
        Game_AddEnemies(&gGame, main->racerCount - gPlayerCount);
        points = PointList_Get(gPointLists, POINTS_ITEM_BOX);
        for (j = 0; j < points->count; j++) {
            Effect_SpawnLast(&gGame, EFFECT_ITEM_BOX, j);
        }
        points = PointList_Get(gPointLists, POINTS_PANEL);
        for (k = 0; k < points->count; k++) {
            Effect_SpawnLast(&gGame, EFFECT_PANEL, k);
        }
        main->timer = 0;
        main->finishCount = 0;
        main->lap = 0x80;
        break;
    case STATE_RACE:
        main->timer = 0;
        main->finalLapTimer = 0;
        main->finalLapShown = 0;
        main->finishedMask = 0;
        main->showLap = 0;
        main->bannerShown = 0;
        break;
    case STATE_FINISH:
        main->timer = 0;
        main->select.wait = -1;
        main->result = main->finishCount;
        m4aSongNumStart(SE_ENGINE);
        if (main->result <= 1) {
            m4aSongNumStart(BGM_WIN);
        } else {
            m4aSongNumStart(BGM_LOSE);
        }
        break;
    case STATE_RETRY:
        main->timer = 0;
        main->readyMask = 0;
        main->answeredMask = 0;
        main->retryLinked = 0;
        for (i = 0; i <= 3; i++) {
            main->select.cursor[i] = 0;
        }
        break;
    }
}

void RecordFinish(struct Main *main, u8 id)
{
    main->finishOrder[main->finishCount] = id;
    main->finishCount++;
    if (id <= 3) {
        main->finishedMask |= 1 << id;
    }
}

/* Drops a player that left the link session */
void RemovePlayer(struct Main *main, u8 id)
{
    s32 bit = 1 << id;

    if (bit & gPlayerMask) {
        gGame.actors[id].active = 0;
        gPlayerMask &= ~bit;
        CountPlayers();
    }
}

void ClosePauseMenu(struct Main *main)
{
    gEngineSong = SONG_NONE;
    gSkidSong = SONG_NONE;
    main->paused = 0;
    Text_Restore(&gTextLayer);
}

void PauseMenu(struct Main *main)
{
    m4aSongNumStart(SE_SELECT);
    m4aMPlayFadeOut(&gMPlayEngine, 2);
    main->menuCursor = 0;
    main->paused = 1;
    Text_Save(&gTextLayer);
    switch (main->state) {
    case STATE_RACE:
        if (main->menuPlayer == gPlayerNo) {
            Text_LoadPauseMenu(&gTextLayer, gLinkMode);
        } else {
            Text_Print(&gTextLayer, 12, 5, 14, gPauseText);
        }
        break;
    case STATE_SELECT:
        main->mode7Enabled = 0;
        main->skyEnabled = 0;
        main->textEnabled = 1;
        main->objEnabled = 1;
        main->splitLine = 0x1000;
        REG_DMA0CNT_H = 0;
        REG_IE &= ~INTR_FLAG_VCOUNT;
        Text_LoadSelectPauseMenu(&gTextLayer);
        break;
    }
}

void SleepMode(struct Main *main)
{
    Text_LoadSleepScreen(&gTextLayer);
    Text_Flush(&gTextLayer);
    {
        u8 mode7Enabled = main->mode7Enabled;
        u8 skyEnabled = main->skyEnabled;
        u8 textEnabled = main->textEnabled;
        u8 objEnabled = main->objEnabled;
        u16 ie = REG_IE;
        u16 keycnt;

        REG_IE &= ~INTR_FLAG_VCOUNT;
        main->mode7Enabled = 0;
        main->skyEnabled = 0;
        main->textEnabled = 1;
        main->objEnabled = 0;
        main->splitLine = 0x1000;
        REG_DISPCNT &= 0x81FF;
        REG_DMA0CNT_H = 0;
        m4aSongNumStop(SE_ENGINE);
        m4aSongNumStop(SE_SKID);
        m4aSongNumStop(SE_ITEM_GET);
        if (main->state == STATE_RACE) {
            m4aMPlayFadeOutTemporarily(&gMPlayBgm, 4);
        }
        WaitFrames(360);
        m4aSongNumStop(SE_SELECT);
        REG_DISPCNT &= 0xE0FF;
        WaitFrames(60);
        keycnt = REG_KEYCNT;
        REG_KEYCNT = 0xC304;
        REG_IE = INTR_FLAG_KEYPAD;
        SoundBiasReset();
        asm("swi 3");
        SoundBiasSet();
        REG_KEYCNT = keycnt;
        REG_IE = ie;
        WaitFrames(60);
        REG_KEYCNT = 0;
        REG_IE &= ~INTR_FLAG_KEYPAD;
        main->mode7Enabled = mode7Enabled;
        main->skyEnabled = skyEnabled;
        main->textEnabled = textEnabled;
        main->objEnabled = objEnabled;
        Text_LoadFont(&gTextLayer);
        Text_Restore(&gTextLayer);
        if (main->state == STATE_RACE) {
            m4aMPlayFadeIn(&gMPlayBgm, 4);
        }
        PauseMenu(main);
    }
}

void PauseMenuInput(struct Main *main)
{
    u16 keys;
    u8 max;
    s32 i;

    if (main->paused) {
        keys = gPadNew[main->menuPlayer];
        switch (main->state) {
        case STATE_RACE:
        case STATE_FINISH:
            max = gLinkMode ? 1 : 2;
            break;
        case STATE_SELECT:
            max = 1;
            break;
        }
        if (keys & START_BUTTON) {
            m4aSongNumStart(SE_SELECT);
            if (main->state == STATE_SELECT) {
                goto resume;
            }
            goto close;
        } else if (keys & DPAD_UP) {
            m4aSongNumStart(SE_CURSOR);
            if (--main->menuCursor < 0) {
                main->menuCursor = max;
            }
        } else if (keys & DPAD_DOWN) {
            m4aSongNumStart(SE_CURSOR);
            main->menuCursor++;
            if (main->menuCursor > max) {
                main->menuCursor = 0;
            }
        } else if (keys & A_BUTTON) {
            m4aSongNumStart(SE_SELECT);
            switch (main->state) {
            case STATE_RACE:
            case STATE_FINISH:
                switch (main->menuCursor) {
                case 0:
                    ClosePauseMenu(main);
                    break;
                case 1:
                    main->paused = 0;
                    if (main->menuPlayer == gPlayerNo) {
                        gLinkSendCmd = PAD_CODE_CONTINUE;
                    }
                    SetGameState(main, STATE_SELECT);
                    break;
                case 2:
                    SleepMode(main);
                    break;
                }
                break;
            case STATE_SELECT:
                gPadNew[main->menuPlayer] &= ~A_BUTTON;
                switch (main->menuCursor) {
                case 0:
                resume:
                    main->mode7Enabled = 0;
                    main->skyEnabled = 1;
                    main->textEnabled = 1;
                    main->objEnabled = 1;
                close:
                    ClosePauseMenu(main);
                    break;
                case 1:
                    SleepMode(main);
                    break;
                }
                break;
            }
        }
    } else if (main->timer != 0) {
        for (i = 0; i <= 3; i++) {
            if (gPadNew[i] & START_BUTTON) {
                switch (main->state) {
                case STATE_RACE:
                case STATE_FINISH:
                    if (!((main->finishedMask >> i) & 1)) {
                        main->menuPlayer = i;
                        PauseMenu(main);
                    }
                    return;
                case STATE_SELECT:
                    if (!gLinkMode) {
                        main->menuPlayer = i;
                        PauseMenu(main);
                    }
                    return;
                }
            }
        }
    }
}

void DrawPauseCursor(struct Main *main)
{
    struct Point pos[1];

    if (main->paused && gPlayerNo == main->menuPlayer) {
        switch (main->state) {
        case STATE_SELECT:
            pos->x = 86;
            pos->y = main->menuCursor * 16 + 86;
            break;
        case STATE_COUNTDOWN:
        case STATE_RACE:
        case STATE_FINISH:
            pos->x = 86;
            pos->y = main->menuCursor * 16 + 78;
            break;
        }
        Sprite_Draw(&gGame, 57, pos, 0);
    }
}

void DrawStatIcon(struct Point *pos, u8 value)
{
    u8 idx = value - 1;

    Sprite_Draw(&gGame, idx + 62, pos, 0);
}

static inline void SetPoint(struct Point *p, s16 x, s16 y)
{
    p->x = x;
    p->y = y;
}

void DrawGameSprites(struct Main *main)
{
    struct Point pos;
    struct Point cursor;
    struct Point num;
    const struct ActorData *data;
    s32 i;
    s16 x;

    switch (main->state) {
    case STATE_LOADING:
        break;
    case STATE_SELECT:
        Oam_Clear(&gGame);
        if (main->paused == 0) {
            SetPoint(&pos, 64, 64);
            Sprite_Draw(&gGame, 58, &pos, 0);
            for (i = 0; i <= 3; i++) {
                x = 87;
                pos.y = 55 + i * 32;
                data = &gPlayerData[i];
                pos.x = x;
                DrawStatIcon(&pos, data->stats[0]);
                pos.x += 56;
                DrawStatIcon(&pos, data->stats[1]);
                pos.x += 56;
                DrawStatIcon(&pos, data->stats[2]);
                if (main->select.cursor[gPlayerNo] == i) {
                    pos.x = 8;
                    Sprite_Draw(&gGame, 57, &pos, 0);
                }
            }
        } else {
            DrawPauseCursor(main);
        }
        Oam_Flush(&gGame);
        break;
    case STATE_COUNTDOWN:
    case STATE_RACE:
    case STATE_FINISH:
    case STATE_RETRY:
        if (gLinkSynced == 0) {
            break;
        }
        Oam_Clear(&gGame);
        Game_Draw(&gGame);
        if (main->state == STATE_RETRY) {
            if (gLinkMode && main->select.answer[gPlayerNo] != 0xFF) {
                SetPoint(&cursor, 78, main->select.answer[gPlayerNo] * 24 + 94);
                Sprite_Draw(&gGame, 57, &cursor, 0);
            }
        } else {
            SetPoint(&num, 208, 14);
            if (main->showLap && gShownLap < main->lapCount) {
                if (gShownLap <= 0) {
                    Sprite_Draw(&gGame, 41, &num, 0);
                } else {
                    Sprite_Draw(&gGame, gShownLap + 41, &num, 0);
                }
            }
            Game_DrawChaserMarker(&gGame, 0, gPlayerNo, gChaserPlayer);
            Game_DrawChaserMarker(&gGame, 1, gPlayerNo, gChaserEnemy);
        }
        DrawPauseCursor(main);
        Oam_Flush(&gGame);
        break;
    }
}
