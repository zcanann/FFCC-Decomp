#ifndef _PPPEMISSION_H_
#define _PPPEMISSION_H_

class CChara;
class CMaterialMan;
class PEmission;

void SetTexGenMode(PEmission *);
void Emission_DrawMeshDLCallback(CChara::CModel *, void *, void *, int, int, float (*)[4]);
void Emission_AfterDrawMeshCallback(CChara::CModel *, void *, void *, int, float (*)[4]);
void pppConstructEmission(void);
void pppConstruct2Emission(void);
void pppDestructEmission(void);
void pppFrameEmission(void);
void pppRenderEmission(void);
void CMaterialMan_GetModelViewITMtx(float (*)[4]);
void GXSetTexCoordGen(void);

#endif // _PPPEMISSION_H_
