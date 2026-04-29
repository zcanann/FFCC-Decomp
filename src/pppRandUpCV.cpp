#include "ffcc/pppRandUpCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

struct RandUpCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 useNormalDistribution;
};


/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static inline char randchar(char value, float scale)
{
    return (char)((f32)value * scale);
}

/*
 * --INFO--
 * PAL Address: 0x80062708
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandUpCV(_pppPObject* basePtr, RandUpCVParam* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    u8* target;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->targetId == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 random = Math.RandF();
            f32 blend = value + random;
            f32 scale = 0.5f;
            value = blend * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else if (in->targetId != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    target = (in->sourceOffset == -1) ? &gPppDefaultValueBuffer[0] : (u8*)(base + in->sourceOffset + 0x80);
    f32 scale = *valuePtr;

    target[0] = (u8)(target[1] + randchar(in->delta[0], scale));
    target[1] = (u8)(target[1] + randchar(in->delta[1], scale));
    target[2] = (u8)(target[2] + randchar(in->delta[2], scale));
    target[3] = (u8)(target[3] + randchar(in->delta[3], scale));
}
