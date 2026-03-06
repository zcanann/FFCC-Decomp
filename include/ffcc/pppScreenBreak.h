#ifndef _PPP_SCREENBREAK_H_
#define _PPP_SCREENBREAK_H_

#include "ffcc/chara.h"

class PScreenBreak;
class VScreenBreak;
struct pppScreenBreakUnkB;
struct pppScreenBreakUnkC;

int SB_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);
void SB_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void SB_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void InitPieceData(CChara::CModel*, PScreenBreak*, VScreenBreak*);
void SB_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenBreak(PScreenBreak*, pppScreenBreakUnkC*);
void pppCon2ScreenBreak(PScreenBreak*, pppScreenBreakUnkC*);
void pppDesScreenBreak(PScreenBreak*, pppScreenBreakUnkC*);
void pppFrameScreenBreak(PScreenBreak*, pppScreenBreakUnkB*, pppScreenBreakUnkC*);
void pppRenderScreenBreak(PScreenBreak*, pppScreenBreakUnkB*, pppScreenBreakUnkC*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENBREAK_H_

