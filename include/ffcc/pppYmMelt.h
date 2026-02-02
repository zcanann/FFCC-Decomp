#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

#include <dolphin/gx.h>

struct PYmMelt
{

};

struct VERTEX_DATA
{

};

void InitPolygonData(PYmMelt*, VERTEX_DATA*, short);
void CalcPolygonHeight(PYmMelt*, VERTEX_DATA*, _GXColor*, float);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMelt(void);
void pppDestructYmMelt(void);
void pppFrameYmMelt(void);
void pppRenderYmMelt(void);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMELT_H_
