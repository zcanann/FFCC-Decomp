#ifndef _PPP_MOVE_H_
#define _PPP_MOVE_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct PppMoveInput {
    int m_graphId;
    int m_padding;
    f32 x;
    f32 y;
    f32 z;
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
