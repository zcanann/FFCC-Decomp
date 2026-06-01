#ifndef _FFCC_PPPACCELE_H_
#define _FFCC_PPPACCELE_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef struct {
    int m_graphId;          // 0x00
    int m_field_04;         // 0x04
    float m_initWOrk;       // 0x08
    float m_stepValue;      // 0x0C
    float m_arg3;           // 0x10
} pppAcceleUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppAccele(_pppPObject* obj, pppAcceleUnkB* param_2, _pppCtrlTable* param_3);
void pppAcceleCon(_pppPObject* obj, _pppCtrlTable* param);

#ifdef __cplusplus
}
#endif

#endif
