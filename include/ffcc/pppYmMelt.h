#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

struct PYmMelt;
struct VERTEX_DATA;
struct _GXColor;

void InitPolygonData(PYmMelt*, VERTEX_DATA*, short);
void CalcPolygonHeight(PYmMelt*, VERTEX_DATA*, _GXColor*, float);
void pppConstructYmMelt(void);
void pppDestructYmMelt(void);
void pppFrameYmMelt(void);
void pppRenderYmMelt(void);
void GXEnd(void);
void GXSetTexCoordGen(void);

#endif // _FFCC_PPP_YMMELT_H_
