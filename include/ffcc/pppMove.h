#ifndef _PPP_MOVE_H_
#define _PPP_MOVE_H_

#include "dolphin/types.h"

struct _pppPObject;
struct _pppCtrlTable;

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

void pppMoveCon(_pppPObject* basePtr, _pppCtrlTable* ctrlTable);
void pppMove(_pppPObject* basePtr, PppMoveInput* input, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MOVE_H_
