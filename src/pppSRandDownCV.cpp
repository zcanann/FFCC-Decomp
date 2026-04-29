#include "ffcc/pppSRandDownCV.h"
#include "ffcc/partMng.h"
#include "ffcc/math.h"
#include "dolphin/types.h"
#include "ffcc/pppColor.h"
#include "ffcc/ppp_default_buffer.h"
#include "ffcc/ppp_linkage.h"

const float kPppSRandDownCVDualSampleScale = 0.5f;

inline char randchar(char value, float scale)
{
    return (char)((f32)value * scale);
}

/*
 * --INFO--
 * PAL Address: 0x800635b0
 * PAL Size: 656b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSRandDownCV(void* basePtr, void* in, _pppCtrlTable* ctrl)
{
    if (gPppCalcDisabled != 0) {
        return;
    }

    float* target;

    if (*(int*)in == *((int*)basePtr + 3)) {
        int** base_ptr = (int**)((char*)ctrl + 0xC);
        int offset = **base_ptr;
        target = (float*)((char*)basePtr + offset + 0x80);

        {
            u8 flag = *((u8*)in + 0xC);
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
            u8 flag = *((u8*)in + 0xC);
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
            u8 flag = *((u8*)in + 0xC);
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
            u8 flag = *((u8*)in + 0xC);
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
        if (*(int*)in != *((int*)basePtr + 3)) {
            return;
        }
        int** base_ptr = (int**)((char*)ctrl + 0xC);
        int offset = **base_ptr;
        target = (float*)((char*)basePtr + offset + 0x80);
    }

    int color_offset = *((int*)in + 1);
    u8* target_colors =
        (color_offset == -1) ? gPppDefaultValueBuffer : (u8*)((char*)basePtr + color_offset + 0x80);

    target_colors[0] = target_colors[0] + randchar(*(s8*)((char*)in + 0x8), target[0]);
    target_colors[1] = target_colors[1] + randchar(*(s8*)((char*)in + 0x9), target[1]);
    target_colors[2] = target_colors[2] + randchar(*(s8*)((char*)in + 0xA), target[2]);
    target_colors[3] = target_colors[3] + randchar(*(s8*)((char*)in + 0xB), target[3]);
}
