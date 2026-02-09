#ifndef _PPP_YMCHANGETEX_H_
#define _PPP_YMCHANGETEX_H_

#include "ffcc/chara.h"
#include <dolphin/types.h>

struct pppYmChangeTex {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
};

struct pppYmChangeTexStep {
    s32 m_graphId;
    s32 m_dataValIndex;
    u16 m_initWOrk;
    u8 _pad0[2];
    float m_stepValue;
    u8 m_arg3;
    u8 m_payload[6];
    u8 _pad1[1];
};

struct pppYmChangeTexData {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

void ChangeTex_DrawMeshDLCallback(CChara::CModel*, void*, void*, int, int, float (*)[4]);
void ChangeTex_AfterDrawMeshCallback(CChara::CModel*, void*, void*, int, float (*)[4]);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmChangeTex(pppYmChangeTex*, pppYmChangeTexData*);
void pppDestructYmChangeTex(pppYmChangeTex*, pppYmChangeTexData*);
void pppFrameYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, pppYmChangeTexData*);
void pppRenderYmChangeTex(pppYmChangeTex*, pppYmChangeTexStep*, pppYmChangeTexData*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMCHANGETEX_H_
