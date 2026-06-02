#ifndef _PPP_SCREENBREAK_H_
#define _PPP_SCREENBREAK_H_

#include "ffcc/chara.h"

class PScreenBreak;
class VScreenBreak;
struct pppScreenBreakUnkB;
struct _pppCtrlTable;

int SB_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);
void SB_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void SB_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void InitPieceData(CChara::CModel*, PScreenBreak*, VScreenBreak*);
void SB_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenBreak(PScreenBreak*, _pppCtrlTable*);
void pppCon2ScreenBreak(PScreenBreak*, _pppCtrlTable*);
void pppDesScreenBreak(PScreenBreak*, _pppCtrlTable*);
void pppFrameScreenBreak(PScreenBreak*, pppScreenBreakUnkB*, _pppCtrlTable*);
void pppRenderScreenBreak(PScreenBreak*, pppScreenBreakUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENBREAK_H_
