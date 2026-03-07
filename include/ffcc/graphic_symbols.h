#ifndef _FFCC_GRAPHIC_SYMBOLS_H_
#define _FFCC_GRAPHIC_SYMBOLS_H_

#include <dolphin/gx.h>
#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern u8 gGraphicDrawDoneRequest;
extern u8 gGraphicDrawDoneRequestInit;
extern u8 gGraphicDrawDonePartControlRequest;
extern u8 gGraphicDrawDonePartControlInit;
extern _GXColor gGraphicDefaultClearColor;
extern char sGraphicUnknownOrderName[];
extern u8 gGraphicNoiseTextureI8_64x96[];
extern float kGraphicZeroF;
extern float kGraphicOneF;
extern double kGraphicHalfF64;
extern float kGraphicBlurAlphaScale;
extern float kGraphicNoiseTexScaleU;
extern float kGraphicNoiseTexScaleV;

#ifdef __cplusplus
}
#endif

#endif // _FFCC_GRAPHIC_SYMBOLS_H_

