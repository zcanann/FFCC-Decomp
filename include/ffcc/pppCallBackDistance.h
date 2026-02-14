#ifndef _FFCC_PPPCALLBACKDISTANCE_H_
#define _FFCC_PPPCALLBACKDISTANCE_H_

#include <dolphin/types.h>

struct pppCallBackDistance {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
};

struct UnkB {
    u32 m_unk0;
    f32 m_dataValIndex;
    s16 m_initWOrk;
};

struct UnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCallBackDistance(pppCallBackDistance* param1, UnkC* param2);
void pppDestructCallBackDistance(void);
void pppFrameCallBackDistance(pppCallBackDistance* param1, UnkB* param2, UnkC* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCALLBACKDISTANCE_H_
