#ifndef _FFCC_PPP_YMMELT_H_
#define _FFCC_PPP_YMMELT_H_

#include <dolphin/gx.h>
#include <dolphin/types.h>

struct PYmMelt
{

};

struct VERTEX_DATA
{

};

struct PYmMeltDataOffsets {
    u8 _pad[0xC];
    s32* m_serializedDataOffsets;
};

void InitPolygonData(PYmMelt*, VERTEX_DATA*, short);
void CalcPolygonHeight(PYmMelt*, VERTEX_DATA*, _GXColor*, float);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMelt(PYmMelt*, PYmMeltDataOffsets*);
void pppDestructYmMelt(PYmMelt*, PYmMeltDataOffsets*);
void pppFrameYmMelt(void);
void pppRenderYmMelt(void);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMELT_H_
