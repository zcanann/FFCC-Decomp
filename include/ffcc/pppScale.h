#ifndef _PPP_SCALE_H_
#define _PPP_SCALE_H_

#include <dolphin/types.h>

struct _pppCtrlTable;
struct _pppPObject;

struct PppScaleDataOffsets {
    s32 m_scaleOffset;
};

struct PppScaleInput {
    s32 m_graphId;
    s32 m_padding;
    f32 m_scale[3];
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
