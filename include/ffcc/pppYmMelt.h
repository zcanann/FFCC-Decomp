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
void pppConstructYmMelt(void);
void pppDestructYmMelt(void);
void pppFrameYmMelt(void);
void pppRenderYmMelt(void);

#endif // _FFCC_PPP_YMMELT_H_
