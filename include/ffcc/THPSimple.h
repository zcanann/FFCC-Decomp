#ifndef _FFCC_PPP_THPSIMPLE_H_
#define _FFCC_PPP_THPSIMPLE_H_

#include "types.h"
#include "dolphin/gx/GXStruct.h"

struct DVDFileInfo;

#ifdef __cplusplus
extern "C" {
#endif

void checkError();
void _kami_DVDREAD(DVDFileInfo*, void*, long, long);
s32 THPSimpleInit(s32);
void THPSimpleQuit(void);
s32 THPSimpleOpen(const char*);
s32 THPSimpleClose(void);
s32 THPSimpleCalcNeedMemory(void);
s32 THPSimpleSetBuffer(u8*);
void ReadFrameAsync();
void __THPSimpleDVDCallback__FlP11DVDFileInfo(long, DVDFileInfo*);
s32 THPSimplePreLoad(s32);
void THPSimpleAudioStart(void);
void THPSimpleAudioStop(void);
s32 THPSimpleLoadStop(void);
s32 THPSimpleDecode(s32);
void CheckPrefetch();
void VideoDecode(unsigned char*);
s32 THPSimpleDrawCurrentFrame(GXRenderModeObj*, int, int, int, int);
void MixAudio__FPsPsUl(short*, short*, unsigned long);
void THPAudioMixCallback__Fv();

extern s32 gTHPSimpleInitialized;
extern s32 gTHPSimpleSoundBufferIndex;
extern void (*gTHPSimpleOldAIDCallback)(void);
extern s16* gTHPSimpleCurAudioBuffer;
extern s16* gTHPSimpleLastAudioBuffer;
extern s32 gTHPSimpleAudioSystem;
extern u16 gTHPSimpleVolumeTable[];
extern s16 WorkBuffer_32_[];

#define MixAudio MixAudio__FPsPsUl
#define THPAudioMixCallback THPAudioMixCallback__Fv
#define __THPSimpleDVDCallback __THPSimpleDVDCallback__FlP11DVDFileInfo

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_THPSIMPLE_H_
