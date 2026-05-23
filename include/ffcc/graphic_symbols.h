#ifndef _FFCC_GRAPHIC_SYMBOLS_H_
#define _FFCC_GRAPHIC_SYMBOLS_H_

#include <dolphin/gx.h>
#include <dolphin/types.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int gGraphicDrawDoneRequest;
extern signed char gGraphicDrawDoneRequestInit;
extern int gGraphicDrawDonePartControlRequest;
extern signed char gGraphicDrawDonePartControlInit;
extern GXRenderModeObj gDefaultGXRenderMode;
extern _GXColor gGraphicDefaultClearColor;
extern const char s_CGraphic_801d6330[];
extern const char s_graphic_cpp_801d6348[];
extern char sGraphicUnknownOrderName[];
extern u8 gGraphicNoiseTextureI8_64x96[];
extern const float kGraphicZeroF;
extern const float kGraphicOneF;
extern const float FLOAT_8032F6D0;
extern const double kGraphicHalfF64;
extern const float FLOAT_8032F6E0;
extern const double DOUBLE_8032F6E8;
extern const float FLOAT_8032F6F0;
extern const float FLOAT_8032F6F4;
extern const float FLOAT_8032F700;
extern const float FLOAT_8032F704;
extern const float kGraphicBlurAlphaScale;
extern const float kGraphicNoiseTexScaleU;
extern const float kGraphicNoiseTexScaleV;

#ifdef __cplusplus
}
#endif

#endif // _FFCC_GRAPHIC_SYMBOLS_H_
