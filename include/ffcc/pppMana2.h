#ifndef _PPP_MANA2_H_
#define _PPP_MANA2_H_

class CChara;
struct Vec;
struct Vec2d;
struct S16Vec;
struct S16Vec2d;
struct _GXColor;
struct VMana2;

void Mana2_DrawMeshDLCallback(CChara::CModel *, void *, void *, int, int, float (*)[4]);
void pppConstructMana2(void);
void pppDestructMana2(void);
void pppFrameMana2(void);
void pppRenderMana2(void);
void Mana2_BeforeDrawCallback(CChara::CModel *, void *, void *, float (*)[4], int);
void GXSetTexCoordGen(void);
void CalcReflectionVector2(Vec *, S16Vec *, S16Vec *, long, unsigned long, unsigned long, float (*)[4], void *, unsigned long, _GXColor *, S16Vec2d *, CChara::CNode *);
void MakeWave(Vec *, unsigned short *, float *, Vec, float, float);
void CreateWaterMesh(Vec *, Vec *, Vec2d *, unsigned short *, float);
void UpdateWaterMesh(VMana2 *);
void RenderWaterMesh(VMana2 *);
void GXEnd(void);
void CalculateNormal(VMana2 *);
void CalcWaterReflectionVector(Vec *, Vec *, Vec *, long, Vec, float (*)[4], _GXColor *, Vec2d *);

#endif // _PPP_MANA2_H_
