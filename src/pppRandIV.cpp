#include "ffcc/pppRandIV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/ppp_default_buffer.h"

struct RandIVParams {
    s32 targetId;
    s32 sourceOffset;
    s32 blend[3];
    u8 _pad[4];
    u8 randomTwice;
};

static inline int randint(int value, float scale)
{
    return (int)((float)value * scale - (float)value);
}

/*
 * --INFO--
 * PAL Address: 0x800622d4
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandIV(_pppPObject* basePtr, RandIVParams* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    f32 value;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->targetId == *(s32*)(base + 0xC)) {
        value = Math.RandF();
        if (in->randomTwice != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
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

    target[0] = target[0] + randint(in->blend[0], scale);
    target[1] = target[1] + randint(in->blend[1], scale);
    target[2] = target[2] + randint(in->blend[2], scale);
}
