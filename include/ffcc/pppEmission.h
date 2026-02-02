#ifndef _PPPEMISSION_H_
#define _PPPEMISSION_H_

#include "ffcc/chara.h"

class CMaterialMan;
class PEmission;

void SetTexGenMode(PEmission*);
void Emission_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void Emission_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);
void CMaterialMan_GetModelViewITMtx(float (*)[4]);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEmission(void);
void pppConstruct2Emission(void);
void pppDestructEmission(void);
void pppFrameEmission(void);
void pppRenderEmission(void);

#ifdef __cplusplus
}
#endif

#endif // _PPPEMISSION_H_
