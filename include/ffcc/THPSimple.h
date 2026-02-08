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
void THPSimpleInit(void);
void THPSimpleQuit(void);
void THPSimpleOpen(void);
void THPSimpleClose(void);
void THPSimpleCalcNeedMemory(void);
void THPSimpleSetBuffer(void);
void ReadFrameAsync();
void __THPSimpleDVDCallback(long, DVDFileInfo*);
void THPSimplePreLoad(void);
void THPSimpleAudioStart(void);
void THPSimpleAudioStop(void);
void THPSimpleLoadStop(void);
void THPSimpleDecode(void);
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
