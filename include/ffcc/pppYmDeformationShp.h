#ifndef _PPP_YMDEFORMATIONSHP_H_
#define _PPP_YMDEFORMATIONSHP_H_

#include <dolphin/types.h>

struct _pppPObject;
struct pppYmDeformationShp;
struct VYmDeformationShp;
struct Vec;
struct Vec2d;
struct Vec4d;
struct pppYmDeformationShpUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_size;
    u8 m_pad_0x9[3];
    f32 m_payload[6];
    s16 m_payload3;
    s8 m_splitMode;
    u8 m_splitSize;
    s8 m_orientation;
    u8 m_pad_0x29[3];
    f32 m_drawZ;
    u8 m_pad_0x30;
    u8 m_alpha;
    u8 m_pad_0x32[0xA];
};
struct pppYmDeformationShpUnkC {
    u8 m_pad_0x0[0xc];
    s32* m_serializedDataOffsets;
};

void SetUpIndWarp(VYmDeformationShp*);
void calcBoundaryBox(Vec&, Vec&, Vec4d*);
void setVertexPos(Vec&, Vec&, Vec&, Vec&, float, signed char);
void setVertexPos(Vec&, Vec&, Vec&, Vec&, float, float, signed char);
void setVertexPos(Vec*, signed char, float, float, float, float);
void setVertexUV(Vec2d*, float, float, float, float);
void calcScreenPos(Vec4d&, Vec, float (*)[4], float (*)[4]);
void oddToEven(float&);
void oddToEven(int&);
int RenderDeformationShape(_pppPObject*, VYmDeformationShp*, Vec*, Vec2d*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpUnkC*);
void pppConstruct2YmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpUnkC*);
void pppDestructYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpUnkC*);
void pppFrameYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpUnkB*, pppYmDeformationShpUnkC*);
void pppRenderYmDeformationShp(pppYmDeformationShp*, pppYmDeformationShpUnkB*, pppYmDeformationShpUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSHP_H_
