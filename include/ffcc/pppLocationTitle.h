#ifndef _PPP_LOCATIONTITLE_H_
#define _PPP_LOCATIONTITLE_H_

#include <dolphin/types.h>
#include "ffcc/partMng.h"

typedef _pppPObject pppLocationTitle;

struct pppLocationTitleUnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_maxCount;
    u8 m_stepCount;
    u8 m_blendMode;
    u8 m_pad0E;
    u8 m_pad0F;
    float m_arg3;
    float m_payload0;
    float m_payload1;
    u16 m_spawnFrame;
    u16 m_fadeStartFrame;
    u16 m_fadeLength;
    u16 m_pad;
};

typedef _pppCtrlTable pppLocationTitleUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkC* param_2);
void pppDestructLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkC* param_2);
void pppFrameLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkB* param_2, pppLocationTitleUnkC* param_3);
void pppRenderLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkB* param_2, pppLocationTitleUnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LOCATIONTITLE_H_
