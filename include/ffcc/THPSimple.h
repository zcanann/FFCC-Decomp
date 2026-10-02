#ifndef _FFCC_PPP_THPSIMPLE_H_
#define _FFCC_PPP_THPSIMPLE_H_

#include "types.h"
#include "dolphin/gx/GXStruct.h"

#ifdef __cplusplus
extern "C" {
#endif

s32 THPSimpleInit(s32);
void THPSimpleQuit(void);
s32 THPSimpleOpen(const char*);
s32 THPSimpleClose(void);
s32 THPSimpleCalcNeedMemory(void);
s32 THPSimpleSetBuffer(u8*);
s32 THPSimplePreLoad(s32);
void THPSimpleAudioStart(void);
void THPSimpleAudioStop(void);
s32 THPSimpleLoadStop(void);
s32 THPSimpleDecode(s32);
s32 THPSimpleDrawCurrentFrame(GXRenderModeObj*, int, int, int, int);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_THPSIMPLE_H_
