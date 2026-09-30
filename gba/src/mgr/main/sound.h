#ifndef GUARD_SOUND_H
#define GUARD_SOUND_H

#include "global.h"

struct MusicPlayerInfo;

extern struct MusicPlayerInfo gMPlayBgm;
extern struct MusicPlayerInfo gMPlaySe;

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
