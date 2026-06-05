#ifndef _FFCC_PPPDRAWSHAPE_H_
#define _FFCC_PPPDRAWSHAPE_H_

#include "ffcc/pppDrawShapeCommon.h"

struct _pppCtrlTable;
struct _pppPObject;

struct ShapeControlData {
    u8 _pad0[4];
    u32 type;
    u32 step;
    u8 _pad2[1];
    u8 blendMode;
    u8 paramE;
    u8 _pad3[1];
    f32 scale;
    u8 param15;
    u8 param14;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawShapeConstruct(_pppPObject* pppShape, _pppCtrlTable* data);
void pppCalcShape(_pppPObject* pppShape, struct ShapeControlData* data, _pppCtrlTable* additionalData);
void pppDrawShape(_pppPObject* pppShape, struct ShapeControlData* data, _pppCtrlTable* additionalData);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWSHAPE_H_
