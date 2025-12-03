#ifndef _FFCC_PPPCHANGETEX_H_
#define _FFCC_PPPCHANGETEX_H_

class CChara;

void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

void pppConstructChangeTex(void);
void pppConstruct2ChangeTex(void);
void pppDestructChangeTex(void);
void pppFrameChangeTex(void);
void pppRenderChangeTex(void);

#endif // _FFCC_PPPCHANGETEX_H_
