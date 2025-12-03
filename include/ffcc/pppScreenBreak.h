#ifndef _PPP_SCREENBREAK_H_
#define _PPP_SCREENBREAK_H_

#include "ffcc/chara.h"

class PScreenBreak;
class VScreenBreak;

void SB_BeforeCalcMatrixCallback(CChara::CModel *, void *, void *);
void SB_BeforeDrawCallback(CChara::CModel *, void *, void *, float (*)[4], int);
void SB_DrawMeshDLCallback(CChara::CModel *, void *, void *, int, int, float (*)[4]);
void GXSetTexCoordGen(void);
void InitPieceData(CChara::CModel *, PScreenBreak *, VScreenBreak *);
void SB_BeforeMeshLockEnvCallback(CChara::CModel *, void *, void *, int);

void pppConScreenBreak(void);
void pppCon2ScreenBreak(void);
void pppDesScreenBreak(void);
void pppFrameScreenBreak(void);
void pppRenderScreenBreak(void);

#endif // _PPP_SCREENBREAK_H_
