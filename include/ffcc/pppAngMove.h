#ifndef _FFCC_PPPANGMOVE_H_
#define _FFCC_PPPANGMOVE_H_

struct _pppCtrlTable;
struct _pppPObject;

struct PppAngMoveInput {
    int m_graphId;
    int m_padding;
    int x;
    int y;
    int z;
};

struct PppAngMoveOffsets {
    int m_angleOffset;
    int m_velocityOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppAngMove(_pppPObject* dest, PppAngMoveInput* src, _pppCtrlTable* ctrlTable);
void pppAngMoveCon(_pppPObject* dest, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif
