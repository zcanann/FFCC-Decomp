#include "ffcc/pppRandCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"


typedef struct RandCVParams {
    s32 index;
    s32 colorOffset;
    s8 delta[4];
    u8 flag;
    u8 pad[3];
} RandCVParams;

/*
 * --INFO--
 * PAL Address: 0x8006103C
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandCV(_pppPObject* basePtr, RandCVParams* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    f32* valuePtr;

    if (gPppCalcDisabled != 0) {
        return;
    }

    if (in->index == *(s32*)(base + 0xC)) {
        f32 value = Math.RandF();
        if (in->flag != 0) {
            value += Math.RandF();
        } else {
            value *= 2.0f;
        }

        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
        *valuePtr = value;
    } else if (in->index != *(s32*)(base + 0xC)) {
        return;
    } else {
        valuePtr = (f32*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    u8* targetColor;
    s32 colorOffset = in->colorOffset;
    if (colorOffset == -1) {
        targetColor = gPppDefaultValueBuffer;
    } else {
        targetColor = base + colorOffset + 0x80;
    }

    {
        f32 scale = *valuePtr;

        {
            u8 color = targetColor[0];
            targetColor[0] = color + (s8)((f32)in->delta[0] * scale - (f32)in->delta[0]);
        }
        {
            u8 color = targetColor[1];
            targetColor[1] = color + (s8)((f32)in->delta[1] * scale - (f32)in->delta[1]);
        }
        {
            u8 color = targetColor[2];
            targetColor[2] = color + (s8)((f32)in->delta[2] * scale - (f32)in->delta[2]);
        }
        {
            u8 color = targetColor[3];
            targetColor[3] = color + (s8)((f32)in->delta[3] * scale - (f32)in->delta[3]);
        }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
char randchar(char value, float scale)
{
    return (char)(((f32)value * scale) - (f32)value);
}
