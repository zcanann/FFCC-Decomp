#ifndef _FFCC_PPPDRAWSHAPE2_H_
#define _FFCC_PPPDRAWSHAPE2_H_

#include "ffcc/pppDrawShapeCommon.h"

struct _pppCtrlTable;
struct _pppPObject;

struct Shape2ControlData {
    u8 _pad0[4];
    u32 type;
    u32 step;
    u8 _pad2[1];
    u8 blendMode;
    u8 paramE;
    u8 _pad3[1];
    f32 scale;
    u8 param14;
    u8 param15;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppDrawShape2Construct(_pppPObject* object, _pppCtrlTable* ctrlTable);
void pppCalcShape2(_pppPObject* object, struct Shape2ControlData* controlData, _pppCtrlTable* ctrlTable);
void pppDrawShape2(_pppPObject* object, struct Shape2ControlData* controlData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWSHAPE2_H_
