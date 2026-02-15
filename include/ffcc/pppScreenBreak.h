#ifndef _PPP_SCREENBREAK_H_
#define _PPP_SCREENBREAK_H_

#include "ffcc/chara.h"

class PScreenBreak;
class VScreenBreak;
struct UnkB;
struct UnkC;

void SB_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);
void SB_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void SB_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void InitPieceData(CChara::CModel*, PScreenBreak*, VScreenBreak*);
void SB_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenBreak(PScreenBreak*, UnkC*);
void pppCon2ScreenBreak(void);
void pppDesScreenBreak(void);
void pppFrameScreenBreak(PScreenBreak*, UnkB*, UnkC*);
void pppRenderScreenBreak(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENBREAK_H_
