#ifndef _FFCC_PPPANGACCELE_H_
#define _FFCC_PPPANGACCELE_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef struct {
    int m_graphId; // 0x00
    int m_field_04;
    int m_x;
    int m_y;
    int m_z;
} pppAngAcceleUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppAngAccele(_pppPObject* obj, pppAngAcceleUnkB* param_2, _pppCtrlTable* param_3);
void pppAngAcceleCon(_pppPObject* obj, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif
