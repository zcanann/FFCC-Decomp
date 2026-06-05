#ifndef _PPP_SCREENBREAK_H_
#define _PPP_SCREENBREAK_H_

#include "dolphin/mtx.h"
#include "dolphin/types.h"

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppScreenBreak;

struct PScreenBreak {
    s32 m_graphId;
    s32 m_dataValIndex;
    u8 m_initWOrk;
    u8 _pad9[3];
    float m_stepValue;
    float m_arg3;
    float m_graphPayload;
    float m_gravityScale;
    u8 m_pad1C[4];
    Vec m_gravityDir;
    u8 m_pad2C[4];
    float m_gravityAmount;
    u8 m_angleRand;
    u8 m_pad35[3];
    float m_speedBase;
    float m_speedRand;
};

struct VScreenBreak;

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
