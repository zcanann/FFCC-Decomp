#ifndef _FFCC_PPPCORONA_H_
#define _FFCC_PPPCORONA_H_

#include <dolphin/types.h>

struct pppCorona {
    union {
        void* ptr;
        struct {
            u32 m_graphId;
        };
    } field0_0x0;
};

struct UnkC {
    u8 _pad0[0xC];
    s32* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructCorona(pppCorona* param1, UnkC* param2);
void pppDestructCorona(void);
void pppFrameCorona(pppCorona* param1, UnkC* param2);
void pppRenderCorona(pppCorona* param1, UnkC* param2);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCORONA_H_
