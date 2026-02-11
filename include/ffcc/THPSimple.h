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
void __THPSimpleDVDCallback(long, DVDFileInfo*);
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

#define MixAudio MixAudio__FPsPsUl
#define THPAudioMixCallback THPAudioMixCallback__Fv

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_THPSIMPLE_H_
