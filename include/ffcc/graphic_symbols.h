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
extern const char sGraphicInitData[];
extern const char sGraphicStageName[];
extern const char sGraphicSourceStrings[];
extern const char sGraphicUnknownOrderName[4];
extern u8 gGraphicNoiseTextureI8_64x96[];
extern const float kGraphicZeroF;
extern const float kGraphicOneF;
extern const float kGraphicSphereNegativeX;
extern const double kGraphicHalfF64;
extern const float kGraphicSpherePi;
extern const float kGraphicSmallBackTextureWidth;
extern const float kGraphicSmallBackTextureHeight;
extern const float kGraphicSphereRingDivisor;
extern const float kGraphicSphereSegmentAngle;
extern const float kGraphicBlurAlphaScale;
extern const float kGraphicNoiseTexScaleU;
extern const float kGraphicNoiseTexScaleV;

#ifdef __cplusplus
}
#endif

#endif // _FFCC_GRAPHIC_SYMBOLS_H_
