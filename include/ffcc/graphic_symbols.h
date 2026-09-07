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
extern GXRenderModeObj _GXPal528IntDf;
extern const char sGraphicInitData[];
extern const char sGraphicSourceStrings[];
extern u8 gGraphicNoiseTextureI8_64x96[];

#ifdef __cplusplus
}
#endif

#endif // _FFCC_GRAPHIC_SYMBOLS_H_
