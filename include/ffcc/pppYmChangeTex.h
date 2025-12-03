#ifndef _PPP_YMCHANGETEX_H_
#define _PPP_YMCHANGETEX_H_

class CChara;

void ChangeTex_DrawMeshDLCallback(CChara::CModel *, void *, void *, int, int, float (*)[4]);
void ChangeTex_AfterDrawMeshCallback(CChara::CModel *, void *, void *, int, float (*)[4]);

void pppConstructYmChangeTex(void);
void pppDestructYmChangeTex(void);
void pppFrameYmChangeTex(void);
void pppRenderYmChangeTex(void);

#endif // _PPP_YMCHANGETEX_H_
