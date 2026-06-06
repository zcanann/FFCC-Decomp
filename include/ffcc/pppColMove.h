#ifndef _FFCC_PPPCOLMOVE_H_
#define _FFCC_PPPCOLMOVE_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct pppColMoveDataOffsets {
    s32 m_sourceMoveOffset;
    s32 m_accumulatedMoveOffset;
};

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

void pppColMove(_pppPObject* object, pppColMoveInput* step, _pppCtrlTable* ctrlTable);
void pppColMoveCon(_pppPObject* object, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLMOVE_H_
