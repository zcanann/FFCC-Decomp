#ifndef _PPP_YMDEFORMATIONSHP_H_
#define _PPP_YMDEFORMATIONSHP_H_

struct _pppPObject;
struct VYmDeformationShp;
struct Vec;
struct Vec2d;
struct Vec4d;

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

void pppConstructYmDeformationShp(void);
void pppConstruct2YmDeformationShp(void);
void pppDestructYmDeformationShp(void);
void pppFrameYmDeformationShp(void);
void pppRenderYmDeformationShp(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSHP_H_
