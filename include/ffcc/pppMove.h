#ifndef _PPP_MOVE_H_
#define _PPP_MOVE_H_

#include "dolphin/types.h"

struct PppMoveData {
    void* field_0;   // 0x0
    void* matrix;    // 0x4 
    u32 field_8;     // 0x8
    void* ptrData;   // 0xc
};

struct PppMoveInput {
    f32 field_0;     // 0x0
    f32 field_4;     // 0x4
    f32 x;           // 0x8
    f32 y;           // 0xc
    f32 z;           // 0x10
};

#ifdef __cplusplus
extern "C" {
#endif

void pppMoveCon(void* basePtr, PppMoveData* data);
void pppMove(void* basePtr, PppMoveInput* input, PppMoveData* data1, PppMoveData* data2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MOVE_H_
