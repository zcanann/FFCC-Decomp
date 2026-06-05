#ifndef _PPP_SCREENBREAK_H_
#define _PPP_SCREENBREAK_H_

#include "ffcc/chara.h"
#include "ffcc/pppPart.h"

struct pppScreenBreak {
    _pppPObject m_object;
};

struct PScreenBreak;
struct VScreenBreak;

struct _pppCtrlTable;

int SB_BeforeCalcMatrixCallback(CChara::CModel*, void*, void*);
void SB_BeforeDrawCallback(CChara::CModel*, void*, void*, float (*)[4], int);
void SB_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void InitPieceData(CChara::CModel*, PScreenBreak*, VScreenBreak*);
void SB_BeforeMeshLockEnvCallback(CChara::CModel*, void*, void*, int);

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenBreak(pppScreenBreak*, _pppCtrlTable*);
void pppCon2ScreenBreak(pppScreenBreak*, _pppCtrlTable*);
void pppDesScreenBreak(pppScreenBreak*, _pppCtrlTable*);
void pppFrameScreenBreak(pppScreenBreak*, PScreenBreak*, _pppCtrlTable*);
void pppRenderScreenBreak(pppScreenBreak*, PScreenBreak*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENBREAK_H_
