#ifndef _FFCC_PPPCOLMOVE_H_
#define _FFCC_PPPCOLMOVE_H_

#include <dolphin/types.h>

struct pppColMoveVec4S {
    s16 x;
    s16 y;
    s16 z;
    s16 w;
};

struct pppColMoveInput {
    s32 id;
    s32 pad;
    pppColMoveVec4S move;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppColMove(void* param1, void* param2, void* param3);
void pppColMoveCon(void* param1, void* param2);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLMOVE_H_
