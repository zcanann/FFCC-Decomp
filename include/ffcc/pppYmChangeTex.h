#ifndef _PPP_YMCHANGETEX_H_
#define _PPP_YMCHANGETEX_H_

#include "ffcc/pppPart.h"

#include <dolphin/types.h>

struct pppYmChangeTex {
    _pppPObject m_object;
};

struct pppYmChangeTexStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    float m_initWOrk;
    float m_stepValue;
    float m_arg3;
    union {
        u8 m_payload[6];
        struct Payload {
            u8 m_mode;
            u8 m_pad01[5];
        } m_changeTex;
    };
    u8 _pad1[1];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmChangeTex(pppYmChangeTex*, _pppCtrlTable*);
void pppDestructYmChangeTex(pppYmChangeTex*, _pppCtrlTable*);
void pppFrameYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, _pppCtrlTable*);
void pppRenderYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCHANGETEX_H_
