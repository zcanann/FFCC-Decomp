#ifndef GUARD_MAIN_H
#define GUARD_MAIN_H

#include "global.h"

enum {
    STATE_LOADING,
    STATE_SELECT,
    STATE_COUNTDOWN,
    STATE_RACE,
    STATE_FINISH,
    STATE_RETRY,
};

struct Main {
    u16 heldKeys;
    u16 newKeys;
    u8 state;
    u8 paused;
    s8 menuCursor;
    u8 menuPlayer;
    u8 finishedMask;
    s8 lapCount;
    s8 racerCount;
    s8 finishCount;
    u8 finishOrder[8];
    s8 result;
    s8 lap;
    u8 finalLapShown;
    u8 showLap;
    u8 bannerShown;
    u8 unk19;
    u16 finalLapTimer;
    u32 lapTime;
    u32 lastLapTime;
    u32 totalTime;
    u32 bestLapTime;
    u32 timer;
    union {
        s8 cursor[4];
        u8 answer[4];
        s32 wait;
    } select;
    u8 readyMask;
    u8 answeredMask;
    u8 retryLinked;
    u8 unk37;
    vu8 mode7Enabled;
    vu8 skyEnabled;
    vu8 textEnabled;
    vu8 objEnabled;
    vu16 splitLine;
    vu16 horizon;
    vu8 mode7Dirty;
    vu8 oamDirty;
};

extern struct Main gMain;
extern vu32 gVBlankCounter;
extern s32 gFrameCounter;
extern s32 gRaceFrameCounter;
extern vu16 gSkyScrollPrev;
extern vu16 gSkyScroll;
extern u8 gIntrMainRam[];
extern vu8 gVCountPhase;
extern volatile s8 gShownLap;
extern u8 gWrongWayShown;
extern struct Actor *gChaserPlayer;
extern struct Actor *gChaserEnemy;
extern u32 lbl_03005C68;
extern u32 lbl_03005C6C;
extern const char *gAssertFile;
extern s32 gAssertLine;
extern u16 gHeldKeys;
extern u16 gNewKeys;

extern const u8 gConfigLinkMode;
extern const u8 gConfigRacerCount;
extern const u8 gConfigLapCount;

extern const char gAssertText[];
extern const char gAssertFileFmt[];
extern const char gAssertLineFmt[];
extern const char gAssertCountFmt[];
extern const char gLoadingText[];
extern const char gLapTimeFmt[];
extern const char gBlankTimeText[];
extern const char gTotalTimeFmt[];
extern const char gRank1stText[];
extern const char gRank2ndText[];
extern const char gRank3rdText[];
extern const char gRank4thText[];
extern const char gRank5thText[];
extern const char gRank6thText[];
extern const char gRank7thText[];
extern const char gRank8thText[];
extern const char gRankNoneText[];
extern const char gPauseText[];

void WaitFrames(u32 frames);
void DebugPrintf(const char *fmt, ...);
void UpdateSound(void);
void AgbMain(void);
void VBlankIntr(void);
void VCountIntr(void);
void IntrDummy(void);
void InitGame(struct Main *main);
void UpdateGameState(struct Main *main);
void DrawTime(struct Main *main, u32 frames, s32 x, s32 y, const char *fmt);
void DrawTimerAndRank(struct Main *main);
void SetGameState(struct Main *main, u8 state);
void RecordFinish(struct Main *main, u8 id);
void RemovePlayer(struct Main *main, u8 id);
void ClosePauseMenu(struct Main *main);
void PauseMenu(struct Main *main);
void SleepMode(struct Main *main);
void PauseMenuInput(struct Main *main);
void DrawPauseCursor(struct Main *main);
void DrawStatIcon(struct Point *pos, u8 value);
void DrawGameSprites(struct Main *main);

#endif
