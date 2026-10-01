#ifndef GUARD_SOUND_H
#define GUARD_SOUND_H

#include "global.h"

enum {
    SE_CURSOR = 0,
    SE_SELECT = 1,
    SE_ENGINE = 3,
    SE_COUNTDOWN = 4,
    SE_GO = 5,
    SE_BRAKE = 6,
    SE_SKID = 7,
    SE_ENGINE_ROUGH = 8,
    SE_ITEM_GET = 9,
    SE_SPIN = 10,
    SE_SLIP = 11,
    SE_FREEZE = 12,
    SE_ITEM_USE = 13,
    SE_BUMP = 14,
    SE_BOOST = 15,
    SE_SLOW = 16,
    SE_FINAL_LAP = 17,
    SE_PANEL = 18,
    BGM_RACE = 50,
    BGM_WIN = 51,
    BGM_LOSE = 52,
    BGM_READY = 53,
    SONG_NONE = 0xFF,
};

struct MusicPlayerInfo;

extern struct MusicPlayerInfo gMPlayBgm;
extern struct MusicPlayerInfo gMPlayEngine;

void m4aSoundInit(void);
void m4aSoundMain(void);
void m4aSoundVSync(void);
void m4aSoundVSyncOff(void);
void m4aSoundVSyncOn(void);
void m4aSongNumStart(u16 n);
void m4aSongNumStop(u16 n);
void m4aMPlayFadeOut(struct MusicPlayerInfo *mplayInfo, u16 speed);
void m4aMPlayFadeOutTemporarily(struct MusicPlayerInfo *mplayInfo, u16 speed);
void m4aMPlayFadeIn(struct MusicPlayerInfo *mplayInfo, u16 speed);
void m4aMPlayPitchControl(struct MusicPlayerInfo *mplayInfo, u16 trackBits, s16 pitch);

/* Positional sound listener (follows the local player) */
struct Sound {
    struct Vec3 listener;
};

extern struct Sound gSound;

void Sound_Init(struct Sound *sound);
void Sound_UpdateListener(struct Sound *sound);
void PlaySong(struct Sound *sound, u16 song, void *source);
void Sound_StaticInit(void);

#endif
