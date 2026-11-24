#include "ffcc/pppRandDownCV.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

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
 * PAL Address: 80061384
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownCV(_pppPObject* basePtr, RandDownCVParams* in, _pppCtrlTable* ctrl)
{
    u8* target;
    f32* valuePtr;

    if (ppvUserStopPartF != 0) {
        return;
    }

    if (in->targetId == basePtr->m_graphId) {
        f32 value = -Math.RandF();
        if (in->useNormalDistribution != 0) {
            f32 random = Math.RandF();
            f32 blend = value - random;
            f32 scale = 0.5f;
            value = blend * scale;
        }

        valuePtr = (f32*)(basePtr->m_workArea + ctrl->m_serializedDataOffsets[0]);
        *valuePtr = value;
    } else if (in->targetId != basePtr->m_graphId) {
        return;
    } else {
        valuePtr = (f32*)(basePtr->m_workArea + ctrl->m_serializedDataOffsets[0]);
    }

    target = (in->sourceOffset == -1) ? &gPppDefaultValueBuffer[0] : (u8*)(basePtr->m_workArea + in->sourceOffset);
    target[0] = (u8)(target[0] + randchar(in->delta[0], *valuePtr));
    target[1] = (u8)(target[1] + randchar(in->delta[1], *valuePtr));
    target[2] = (u8)(target[2] + randchar(in->delta[2], *valuePtr));
    target[3] = (u8)(target[3] + randchar(in->delta[3], *valuePtr));
}
