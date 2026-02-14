#ifndef _PPP_YMDEFORMATIONSHP_H_
#define _PPP_YMDEFORMATIONSHP_H_

#include <dolphin/types.h>

struct _pppPObject;
struct pppYmDeformationShp;
struct VYmDeformationShp;
struct Vec;
struct Vec2d;
struct Vec4d;
struct UnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    f32 m_payload[6];
    s16 m_payload3;
    u8 m_pad_0x22[0x1a];
};
struct UnkC {
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
};

void SetUpIndWarp(VYmDeformationShp*);
void calcBoundaryBox(Vec&, Vec&, Vec4d*);
void setVertexPos(Vec&, Vec&, Vec&, Vec&, float, char);
void setVertexPos(Vec*, char, float, float, float, float);
void setVertexUV(Vec2d*, float, float, float, float);
void calcScreenPos(Vec4d&, Vec&, float (*)[4], float (*)[4]);
void oddToEven(float&);
void RenderDeformationShape(_pppPObject*, VYmDeformationShp*, Vec*, Vec2d*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationShp(pppYmDeformationShp*, UnkC*);
void pppConstruct2YmDeformationShp(pppYmDeformationShp*, UnkC*);
void pppDestructYmDeformationShp(void);
void pppFrameYmDeformationShp(pppYmDeformationShp*, UnkB*, UnkC*);
void pppRenderYmDeformationShp(pppYmDeformationShp*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSHP_H_
