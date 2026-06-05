#ifndef _PPP_SCALE_H_
#define _PPP_SCALE_H_

struct _pppCtrlTable;
struct _pppPObject;

struct PppScaleInput {
    int m_graphId;
    int m_padding;
    float m_scale[3];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppScale(_pppPObject* obj, PppScaleInput* param2, _pppCtrlTable* ctrlTable);
void pppScaleCon(_pppPObject* obj, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCALE_H_
