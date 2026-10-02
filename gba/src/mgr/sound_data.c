#include "gba/m4a_internal.h"

struct SoundInfo gSoundInfo = {0};
MPlayFunc gMPlayJumpTable[36] = {0};
struct CgbChannel gCgbChans[4] = {0};
struct MusicPlayerInfo gMPlayBgm = {0};
struct MusicPlayerInfo gMPlaySe = {0};
struct MusicPlayerInfo gMPlayEngine = {0};
u8 gMPlayMemAccArea[0x10] = {0};

struct MusicPlayerTrack gMPlayTrackBgm[4];
struct MusicPlayerTrack gMPlayTrackSe[2];
struct MusicPlayerTrack gMPlayTrackEngine[2];

extern struct WaveData gWaveSample0;
extern struct WaveData gWaveSample1;
extern struct WaveData gWaveSample2;
extern struct WaveData gWaveSample3;
extern struct WaveData gWaveSample4;
extern struct WaveData gWaveSample5;
extern struct WaveData gWaveSample6;
extern struct WaveData gWaveSample7;

extern struct SongHeader gSong00;
extern struct SongHeader gSong01;
extern struct SongHeader gSong02;
extern struct SongHeader gSong03;
extern struct SongHeader gSong04;
extern struct SongHeader gSong05;
extern struct SongHeader gSong06;
extern struct SongHeader gSong07;
extern struct SongHeader gSong08;
extern struct SongHeader gSong09;
extern struct SongHeader gSong10;
extern struct SongHeader gSong11;
extern struct SongHeader gSong12;
extern struct SongHeader gSong13;
extern struct SongHeader gSong14;
extern struct SongHeader gSong15;
extern struct SongHeader gSong16;
extern struct SongHeader gSong17;
extern struct SongHeader gSong18;
extern struct SongHeader gSong50;
extern struct SongHeader gSong51;
extern struct SongHeader gSong52;
extern struct SongHeader gSong53;

extern const u8 gProgWave0[];
extern const u8 gProgWave1[];
extern const u8 gProgWave2[];
extern const u8 gProgWave3[];
extern const u8 gProgWave4[];
extern const u8 gProgWave5[];
extern const u8 gProgWave6[];
extern const u8 gProgWave7[];
extern const u8 gProgWave8[];

const struct ToneData gVoiceGroup0[] = {
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 0, 60, 0, 0, &gWaveSample0, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample3, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample1, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample4, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample5, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample6, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample7, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample2, 255, 0, 255, 0 },
};

const struct ToneData gVoiceGroup1[] = {
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 0, 60, 0, 0, &gWaveSample3, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample4, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample5, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample6, 255, 0, 255, 0 },
    { 0, 60, 0, 0, &gWaveSample7, 255, 0, 255, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 2, 7, 1 },
    { 2, 60, 0, 0, (struct WaveData *)2, 0, 1, 7, 1 },
    { 3, 60, 0, 0, (struct WaveData *)gProgWave6, 0, 1, 7, 2 },
    { 4, 60, 0, 0, (struct WaveData *)0, 0, 0, 12, 0 },
    { 3, 60, 0, 0, (struct WaveData *)gProgWave1, 0, 1, 12, 1 },
    { 1, 60, 0, 0, (struct WaveData *)2, 1, 1, 7, 0 },
    { 2, 60, 0, 0, (struct WaveData *)2, 0, 1, 7, 2 },
    { 3, 60, 0, 0, (struct WaveData *)gProgWave2, 0, 1, 9, 1 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 3, 12, 2 },
    { 2, 60, 0, 0, (struct WaveData *)2, 0, 1, 7, 1 },
    { 3, 60, 0, 0, (struct WaveData *)gProgWave1, 0, 1, 12, 1 },
    { 4, 60, 0, 0, (struct WaveData *)0, 0, 0, 12, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 0, 0, 15, 0 },
    { 1, 60, 0, 0, (struct WaveData *)2, 1, 3, 12, 1 },
    { 3, 60, 0, 0, (struct WaveData *)gProgWave6, 1, 1, 7, 1 },
    { 2, 60, 0, 0, (struct WaveData *)2, 1, 2, 12, 1 },
};

const u8 gProgWave0[] = { 0x00, 0x11, 0x23, 0x56, 0x89, 0xAC, 0xDE, 0xEF, 0xFF, 0xEE, 0xDC, 0xA9, 0x86, 0x53, 0x21, 0x10 };
const u8 gProgWave1[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0xFE, 0xDC, 0xBA, 0x98, 0x76, 0x54, 0x32, 0x10 };
const u8 gProgWave2[] = { 0xFF, 0xEE, 0xDD, 0xCC, 0xBB, 0xAA, 0x99, 0x88, 0x77, 0x66, 0x55, 0x44, 0x33, 0x22, 0x11, 0x00 };
const u8 gProgWave3[] = { 0xFE, 0xDC, 0xBA, 0x99, 0x88, 0x88, 0x88, 0x88, 0x77, 0x77, 0x77, 0x77, 0x66, 0x54, 0x32, 0x10 };
const u8 gProgWave4[] = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const u8 gProgWave5[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const u8 gProgWave6[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const u8 gProgWave7[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
const u8 gProgWave8[] = { 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

const struct MusicPlayer gMPlayTable[] = {
    { &gMPlayBgm, gMPlayTrackBgm, 4, 0 },
    { &gMPlaySe, gMPlayTrackSe, 2, 0 },
    { &gMPlayEngine, gMPlayTrackEngine, 2, 0 },
};

extern const u8 gDummySongHeader[];

const struct Song gSongTable[] = {
    { &gSong00, 1, 1 },
    { &gSong01, 1, 1 },
    { &gSong02, 1, 1 },
    { &gSong03, 2, 2 },
    { &gSong04, 1, 1 },
    { &gSong05, 1, 1 },
    { &gSong06, 2, 2 },
    { &gSong07, 2, 2 },
    { &gSong08, 2, 2 },
    { &gSong09, 1, 1 },
    { &gSong10, 1, 1 },
    { &gSong11, 1, 1 },
    { &gSong12, 1, 1 },
    { &gSong13, 1, 1 },
    { &gSong14, 1, 1 },
    { &gSong15, 1, 1 },
    { &gSong16, 1, 1 },
    { &gSong17, 1, 1 },
    { &gSong18, 1, 1 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { (struct SongHeader *)gDummySongHeader, 0, 0 },
    { &gSong50, 0, 0 },
    { &gSong51, 0, 0 },
    { &gSong52, 0, 0 },
    { &gSong53, 0, 0 },
};

const u8 gDummySongHeader[] = { 0, 0, 0, 0 };
