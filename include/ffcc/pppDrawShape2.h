#ifndef _FFCC_PPPDRAWSHAPE2_H_
#define _FFCC_PPPDRAWSHAPE2_H_

#include "ffcc/pppDrawShapeCommon.h"

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

void pppDrawShape2Construct(void* param1, void* param2);
void pppCalcShape2(void* param1, struct Shape2ControlData* param2, void* param3);
void pppDrawShape2(void* param1, struct Shape2ControlData* param2, void* param3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPDRAWSHAPE2_H_
