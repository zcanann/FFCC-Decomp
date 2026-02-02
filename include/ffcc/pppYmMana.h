#ifndef _PPP_YMMANA_H_
#define _PPP_YMMANA_H_

#include "ffcc/chara.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct PYmMana;
struct VYmMana;
struct CTexture;
struct CGObject;
struct Vec2d;

void SetEnvMap(PYmMana*, VYmMana*);
void Mana_BeforeDrawShadowLockEnvCallback(CChara::CModel*, void*, void*, int);
void Chara_DrawShadowMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Mana_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Mana_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void GXSetViewportv(void);
void MakeWave(Vec*, unsigned short*, float*, Vec&, float, float);
void CreateWaterMesh(Vec*, Vec*, Vec2d*, unsigned short*, float);
void UpdateWaterMesh(VYmMana*);
void RenderWaterMesh(VYmMana*);
void CalculateNormal(VYmMana*);
void CalcWaterReflectionVector(Vec*, Vec*, Vec*, long, Vec&, float (*)[4], _GXColor*, Vec2d*);
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*)[4], void*, unsigned long, _GXColor*, S16Vec2d*, S16Vec2d*, CChara::CNode*, PYmMana*, VYmMana*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMana(void);
void pppDestructYmMana(void);
void pppFrameYmMana(void);
void pppRenderYmMana(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMMANA_H_
