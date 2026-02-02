#ifndef _PPP_LOCATIONTITLE_H_
#define _PPP_LOCATIONTITLE_H_

#include <dolphin/types.h>
#include "ffcc/partMng.h"

struct pppLocationTitle {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
            pppFMATRIX m_localMatrix;
        };
    } field0_0x0;
    
    // Add padding up to offset 0x88 (rough estimate)
    char pad[0x50];
    void* field_0x88;
};

struct UnkB {
    u32 m_dataValIndex;
    u16 m_initWOrk;
    
    // Extended fields from decompilation
    u32 m_graphId;
    float m_arg3;
    void* m_payload;
    u8 m_stepValue;
};

struct UnkC {
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle(pppLocationTitle* param_1, UnkC* param_2);
void pppDestructLocationTitle(pppLocationTitle* param_1, UnkC* param_2);
void pppFrameLocationTitle(pppLocationTitle* param_1, UnkB* param_2, UnkC* param_3);
void pppRenderLocationTitle(pppLocationTitle* param_1, UnkB* param_2, UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LOCATIONTITLE_H_
