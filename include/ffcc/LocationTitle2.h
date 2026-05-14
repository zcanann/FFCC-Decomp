#ifndef _FFCC_LOCATIONTITLE2_H_
#define _FFCC_LOCATIONTITLE2_H_

#include "ffcc/partMng.h"
#include <dolphin/types.h>

typedef _pppPObject pppLocationTitle2;

struct pppLocationTitle2UnkB {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u16 m_maxCount;
    u8 m_stepCount;
    u8 m_blendMode;
    u8 _pad0x0E;
    u8 _pad0x0F;
    float m_arg3;
    float m_payload0;
    float m_payload1;
    u16 _pad0x1C;
    u16 _pad0x1E;
    u16 _pad0x20;
    u8 m_enableColorUpdate;
    u8 _pad0x23;
};

typedef _pppCtrlTable pppLocationTitle2UnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle2(struct pppLocationTitle2*, struct pppLocationTitle2UnkC*);
void pppDestructLocationTitle2(struct pppLocationTitle2*, struct pppLocationTitle2UnkC*);
void pppFrameLocationTitle2(struct pppLocationTitle2*, struct pppLocationTitle2UnkB*, struct pppLocationTitle2UnkC*);
void pppRenderLocationTitle2(struct pppLocationTitle2*, struct pppLocationTitle2UnkB*, struct pppLocationTitle2UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_LOCATIONTITLE2_H_
