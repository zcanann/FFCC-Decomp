#ifndef _FFCC_GRAPHIC_SYMBOLS_H_
#define _FFCC_GRAPHIC_SYMBOLS_H_

#include <dolphin/gx.h>
#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern u32 gGraphicDrawDoneRequest;
extern u8 gGraphicDrawDoneRequestInit;
extern u32 gGraphicDrawDonePartControlRequest;
extern u8 gGraphicDrawDonePartControlInit;
extern _GXColor gGraphicDefaultClearColor;
extern char sGraphicUnknownOrderName[];
extern u8 gGraphicNoiseTextureI8_64x96[];
extern const float kGraphicZeroF;
extern const float kGraphicOneF;
extern const double kGraphicHalfF64;
extern const float kGraphicBlurAlphaScale;
extern const float kGraphicNoiseTexScaleU;
extern const float kGraphicNoiseTexScaleV;

#ifdef __cplusplus
}
#endif

#endif // _FFCC_GRAPHIC_SYMBOLS_H_

