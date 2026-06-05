#ifndef _FFCC_PPPDRAWSHAPECOMMON_H_
#define _FFCC_PPPDRAWSHAPECOMMON_H_

#include "ffcc/pppPart.h"

#include <dolphin/types.h>

struct ShapeRuntimeData {
    u32 shapeDataOffset;
    u32 posDataOffset;
};

struct ShapeState {
    u16 value;
    u16 counter;
    u16 currentId;
};

struct ShapePositionData {
    u8 _pad0[8];
    pppCVECTOR color;
};

#endif // _FFCC_PPPDRAWSHAPECOMMON_H_
