#include "ffcc/pppSRandDownCV.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

const float kPppSRandDownCVDualSampleScale = 0.5f;

/*
 * --INFO--
 * PAL Address: 0x800635b0
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownCV(void* param1, void* param2, void* param3)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    float* target;

    if (*(int*)param2 == *((int*)param1 + 3)) {
        int** base_ptr = (int**)((char*)param3 + 0xC);
        int offset = **base_ptr;
        target = (float*)((char*)param1 + offset + 0x80);

        {
            u8 flag = *((u8*)param2 + 0xC);
            float value = -Math.RandF();
            if (flag != 0) {
                float random = Math.RandF();
                float blend = value - random;
                float scale = kPppSRandDownCVDualSampleScale;
                value = blend * scale;
            }
            target[0] = value;
        }

        {
            u8 flag = *((u8*)param2 + 0xC);
            float value = -Math.RandF();
            if (flag != 0) {
                float random = Math.RandF();
                float blend = value - random;
                float scale = kPppSRandDownCVDualSampleScale;
                value = blend * scale;
            }
            target[1] = value;
        }

        {
            u8 flag = *((u8*)param2 + 0xC);
            float value = -Math.RandF();
            if (flag != 0) {
                float random = Math.RandF();
                float blend = value - random;
                float scale = kPppSRandDownCVDualSampleScale;
                value = blend * scale;
            }
            target[2] = value;
        }

        {
            u8 flag = *((u8*)param2 + 0xC);
            float value = -Math.RandF();
            if (flag != 0) {
                float random = Math.RandF();
                float blend = value - random;
                float scale = kPppSRandDownCVDualSampleScale;
                value = blend * scale;
            }
            target[3] = value;
        }
    } else {
        if (*(int*)param2 != *((int*)param1 + 3)) {
            return;
        }
        int** base_ptr = (int**)((char*)param3 + 0xC);
        int offset = **base_ptr;
        target = (float*)((char*)param1 + offset + 0x80);
    }

    int color_offset = *((int*)param2 + 1);
    u8* target_colors =
        (color_offset == -1) ? gPppDefaultValueBuffer : (u8*)((char*)param1 + color_offset + 0x80);

    {
        s8 base = *(s8*)((char*)param2 + 0x8);
        s8 delta = (s8)((f32)base * target[0]);
        target_colors[0] = (u8)(target_colors[0] + delta);
    }

    {
        s8 base = *(s8*)((char*)param2 + 0x9);
        s8 delta = (s8)((f32)base * target[1]);
        target_colors[1] = (u8)(target_colors[1] + delta);
    }

    {
        s8 base = *(s8*)((char*)param2 + 0xA);
        s8 delta = (s8)((f32)base * target[2]);
        target_colors[2] = (u8)(target_colors[2] + delta);
    }

    {
        s8 base = *(s8*)((char*)param2 + 0xB);
        s8 delta = (s8)((f32)base * target[3]);
        target_colors[3] = (u8)(target_colors[3] + delta);
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static float randf(unsigned char flag)
{
    float value = -Math.RandF();
    if (flag != 0) {
        float random = Math.RandF();
        float blend = value - random;
        float scale = kPppSRandDownCVDualSampleScale;
        value = blend * scale;
    }
    return value;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
static char randchar(char value, float scale)
{
    return (char)((f32)value * scale);
}
