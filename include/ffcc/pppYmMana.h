#ifndef _PPP_YMMANA_H_
#define _PPP_YMMANA_H_

#include "ffcc/chara.h"

struct PYmMana;
struct VYmMana;
struct CTexture;
struct CGObject;
struct Vec;
struct Vec2d;
struct S16Vec;
struct S16Vec2d;
struct _GXColor;
struct _GXTexObj;

void SetEnvMap(PYmMana *, VYmMana *);
void GXSetTexCoordGen(void);
void Mana_BeforeDrawShadowLockEnvCallback(CChara::CModel *, void *, void *, int);
void Chara_DrawShadowMeshDLCallback(CChara::CModel *, void *, void *, int, int, float (*)[4]);
void Mana_DrawMeshDLCallback(CChara::CModel *, void *, void *, int, int, float (*)[4]);
void pppConstructYmMana(void);
void pppDestructYmMana(void);
void pppFrameYmMana(void);
void pppRenderYmMana(void);
void Mana_BeforeDrawCallback(CChara::CModel *, void *, void *, float (*)[4], int);
void GXSetViewportv(void);
void MakeWave(Vec *, unsigned short *, float *, Vec&, float, float);
void CreateWaterMesh(Vec *, Vec *, Vec2d *, unsigned short *, float);
void UpdateWaterMesh(VYmMana *);
void RenderWaterMesh(VYmMana *);
void GXEnd(void);
void CalculateNormal(VYmMana *);
void CalcWaterReflectionVector(Vec *, Vec *, Vec *, long, Vec&, float (*)[4], _GXColor *, Vec2d *);
void CalcReflectionVector2(Vec *, S16Vec *, S16Vec *, long, unsigned long, unsigned long, float (*)[4], void *, unsigned long, _GXColor *, S16Vec2d *, S16Vec2d *, CChara::CNode *, PYmMana *, VYmMana *);

#endif // _PPP_YMMANA_H_
