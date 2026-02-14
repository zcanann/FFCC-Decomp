#ifndef _PPP_MANA2_H_
#define _PPP_MANA2_H_

#include "ffcc/chara.h"

#include <dolphin/mtx.h>

struct Vec;
struct Vec2d;
struct _GXColor;
struct VMana2;
struct pppMana2;
struct UnkB;
struct UnkC {
    s32* m_serializedDataOffsets;
};

void Mana2_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Mana2_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void CalcReflectionVector2(Vec*, S16Vec*, S16Vec*, long, unsigned long, unsigned long, float (*)[4], void*, unsigned long, _GXColor*, S16Vec2d*, CChara::CNode*);
void MakeWave(Vec*, unsigned short*, float*, Vec*, float, float);
void CreateWaterMesh(Vec*, Vec*, Vec2d*, unsigned short*, float);
void UpdateWaterMesh(VMana2*);
void RenderWaterMesh(VMana2*);
void CalculateNormal(VMana2*);
void CalcWaterReflectionVector(Vec*, Vec*, Vec*, long, Vec*, float (*)[4], _GXColor*, Vec2d*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructMana2(pppMana2*, UnkC*);
void pppDestructMana2(pppMana2*, UnkC*);
void pppFrameMana2(pppMana2*, UnkB*, UnkC*);
void pppRenderMana2(pppMana2*, UnkB*, UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MANA2_H_
