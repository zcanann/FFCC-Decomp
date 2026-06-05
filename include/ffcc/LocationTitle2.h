#ifndef _FFCC_LOCATIONTITLE2_H_
#define _FFCC_LOCATIONTITLE2_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppLocationTitle2;
typedef _pppCtrlTable pppLocationTitle2UnkC;

struct pppLocationTitle2Step {
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

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle2(pppLocationTitle2*, pppLocationTitle2UnkC*);
void pppDestructLocationTitle2(pppLocationTitle2*, pppLocationTitle2UnkC*);
void pppFrameLocationTitle2(pppLocationTitle2*, pppLocationTitle2Step*, pppLocationTitle2UnkC*);
void pppRenderLocationTitle2(pppLocationTitle2*, pppLocationTitle2Step*, pppLocationTitle2UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_LOCATIONTITLE2_H_
