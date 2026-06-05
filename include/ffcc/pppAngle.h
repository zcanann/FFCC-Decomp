#ifndef _FFCC_PPPANGLE_H_
#define _FFCC_PPPANGLE_H_

struct _pppCtrlTable;
struct _pppPObject;

struct PppAngleInput {
    int m_graphId;
    int m_padding;
    int m_angle[3];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppAngle(_pppPObject* dest, PppAngleInput* src, _pppCtrlTable* ctrlTable);
void pppAngleCon(_pppPObject* dest, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif
