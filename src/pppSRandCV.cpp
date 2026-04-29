#include "ffcc/pppSRandCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"


struct SRandCVParam {
    s32 targetId;
    s32 sourceOffset;
    s8 delta[4];
    u8 randomTwice;
    u8 _pad[3];
};

static float randf(unsigned char flag)
{
    float value = Math.RandF();
    if (flag != 0) {
        value = value + Math.RandF();
    } else {
        float scale = 2.0f;
        value = value * scale;
    }
    return value;
}

static char randchar(char value, float scale)
{
    return (char)((f32)value * scale - (f32)value);
}

/*
 * --INFO--
 * PAL Address: 800632d0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandCV(_pppPObject* basePtr, SRandCVParam* in, _pppCtrlTable* ctrl)
{
    u8* base = (u8*)basePtr;
    if (gPppCalcDisabled != 0) {
        return;
    }

    float* target;

    if (in->targetId == *(s32*)(base + 0xC)) {
        target = (float*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);

        {
            u8 flag = in->randomTwice;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                float scale = 2.0f;
                value = value * scale;
            }
            target[0] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                float scale = 2.0f;
                value = value * scale;
            }
            target[1] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                float scale = 2.0f;
                value = value * scale;
            }
            target[2] = value;
        }

        {
            u8 flag = in->randomTwice;
            float value = Math.RandF();
            if (flag != 0) {
                value = value + Math.RandF();
            } else {
                float scale = 2.0f;
                value = value * scale;
            }
            target[3] = value;
        }
    } else {
        if (in->targetId != *(s32*)(base + 0xC)) {
            return;
        }
        target = (float*)(basePtr->m_workArea + *ctrl->m_serializedDataOffsets);
    }

    s32 color_offset = in->sourceOffset;
    u8* target_colors = (color_offset == -1) ? gPppDefaultValueBuffer : (base + color_offset + 0x80);

    target_colors[0] = target_colors[0] + randchar(in->delta[0], target[0]);
    target_colors[1] = target_colors[1] + randchar(in->delta[1], target[1]);
    target_colors[2] = target_colors[2] + randchar(in->delta[2], target[2]);
    target_colors[3] = target_colors[3] + randchar(in->delta[3], target[3]);
}
