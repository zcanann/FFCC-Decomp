#ifndef _PPP_SCREENBREAK_H_
#define _PPP_SCREENBREAK_H_

#include "ffcc/chara.h"
#include "ffcc/pppPart.h"

#include <dolphin/gx.h>

struct pppScreenBreak {
    _pppPObject m_object;
};

struct ScreenBreakPiece {
    Vec m_velocity;
    Vec m_offset;
    Vec m_axis;
    Vec m_translation;
    float m_timer;
    float m_angle;
    u8 m_active;
    u8 m_pad39[3];
};

struct VScreenBreak {
    float m_graphValue0;
    float m_graphValue1;
    float m_graphValue2;
    ScreenBreakPiece* m_pieces;
    GXTexObj* m_backBufferTexObj;
    u8 m_pad14[4];
    Vec m_extent;
    u8 m_backBufferReady;
    u8 m_pad25[3];
    GXColor m_color;
};

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

struct ScreenBreakColorData {
    u8 m_pad0[8];
    GXColor m_color;
};

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
