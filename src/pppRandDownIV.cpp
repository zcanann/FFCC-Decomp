#include "ffcc/pppRandDownIV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandDownIVParams {
    s32 targetId;
    s32 sourceOffset;
    s32 blend[3];
    u8 _pad[4];
    u8 randomTwice;
};

static inline int randint(int value, float scale)
{
    return (int)((float)value * scale);
}

/*
 * --INFO--
 * PAL Address: 0x80061a88
 * PAL Size: 404b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppRandDownIV(_pppPObject* basePtr, RandDownIVParams* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    u8* base = (u8*)basePtr;
    f32 value;
    f32* valuePtr;

    if (in->targetId == *(s32*)(base + 0xC)) {
        value = -Math.RandF();
        if (in->randomTwice != 0) {
            f32 randValue = value - Math.RandF();
            f32 scale = 0.5f;
            value = randValue * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else {
        if (in->targetId != *(s32*)(base + 0xC)) {
            return;
        }
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    s32* target = (in->sourceOffset == -1) ? (s32*)gPppDefaultValueBuffer : (s32*)(base + in->sourceOffset + 0x80);
    f32 scale = *valuePtr;

    target[0] += randint(in->blend[0], scale);
    target[1] += randint(in->blend[1], scale);
    target[2] += randint(in->blend[2], scale);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
