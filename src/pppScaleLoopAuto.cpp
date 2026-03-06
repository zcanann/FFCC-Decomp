#include "ffcc/pppScaleLoopAuto.h"
#include <dolphin/types.h>

extern int lbl_8032ED70;
extern float lbl_801EC9F0[];
extern float lbl_80331C08;

struct pppScaleLoopAutoWork {
    float m_scale[3];
    u8 _pad0x0c[4];
    float m_baseScale[3];
    u8 m_initialized;
    u8 m_step;
    s16 m_angle;
    s8 m_countA;
    s8 m_countB;
    u8 _pad0x22[2];
    float m_delta;
};

struct pppScaleLoopAutoStep {
    s32 m_index;
    u8 _pad0x04[4];
    float m_addScale[3];
    u8 _pad0x14[4];
    float m_amplitude;
    u8 m_stepCount;
    s8 m_countA;
    s8 m_countB;
    u8 _pad0x1f;
    float m_scale;
};

struct pppScaleLoopAutoContext {
    s32 _pad0x00[3];
    s32* m_serializedDataOffsets;
};

/*
 * --INFO--
 * PAL Address: 0x8012b4f4
 * PAL Size: 540b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScaleLoopAuto(void* arg1, void* arg2, void* arg3)
{
    pppScaleLoopAutoStep* step = (pppScaleLoopAutoStep*)arg2;
    pppScaleLoopAutoContext* context = (pppScaleLoopAutoContext*)arg3;

    if (lbl_8032ED70 != 0) {
        return;
    }

    pppScaleLoopAutoWork* work = (pppScaleLoopAutoWork*)((u8*)arg1 + context->m_serializedDataOffsets[0] + 0x80);

    if (step->m_index == *(s32*)((u8*)arg1 + 0xC)) {
        work->m_scale[0] += step->m_addScale[0];
        work->m_scale[1] += step->m_addScale[1];
        work->m_scale[2] += step->m_addScale[2];
    }

    if (work->m_initialized == 0) {
        work->m_initialized = 1;
        work->m_baseScale[0] = work->m_scale[0];
        work->m_baseScale[1] = work->m_scale[1];
        work->m_baseScale[2] = work->m_scale[2];
        work->m_countA = step->m_countA;
        work->m_countB = step->m_countB;
        return;
    }

    if ((work->m_angle < 90) && (work->m_countA > 0)) {
        work->m_countA--;
        work->m_scale[0] = work->m_baseScale[0] + work->m_delta;
        work->m_scale[1] = work->m_baseScale[1] + work->m_delta;
        work->m_scale[2] = work->m_baseScale[2] + work->m_delta;
    } else if ((work->m_angle < 270) && (work->m_countB > 0)) {
        work->m_countB--;
        work->m_scale[0] = work->m_baseScale[0] + work->m_delta;
        work->m_scale[1] = work->m_baseScale[1] + work->m_delta;
        work->m_scale[2] = work->m_baseScale[2] + work->m_delta;
    } else {
        work->m_step++;
        if (work->m_step > step->m_stepCount) {
            work->m_step = 0;
            work->m_angle = 0;
            work->m_countA = step->m_countA;
            work->m_countB = step->m_countB;
            return;
        }

        work->m_angle += 360 / (s32)step->m_stepCount;

        {
            s32 tableAngle = (s32)(((f32)((s32)work->m_angle << 15)) / 360.0f);
            f32 sinVal = *(f32*)((u8*)lbl_801EC9F0 + (tableAngle & 0xFFFC));
            f32 delta = (step->m_amplitude * sinVal) * step->m_scale;

            work->m_delta = delta;
            work->m_scale[0] = work->m_baseScale[0] + delta;
            work->m_scale[1] = work->m_baseScale[1] + delta;
            work->m_scale[2] = work->m_baseScale[2] + delta;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8012b4a8
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppScaleLoopAutoCon(void* arg1, void* arg2)
{
	int** arg2Data = (int**)arg2;
	int* data = arg2Data[3];
	int* ptr = (int*)data[0];
	float zero = lbl_80331C08;
	
	void* targetPtr = (void*)((char*)arg1 + (int)ptr + 0x80);
	float* targetData = (float*)targetPtr;
	char* targetBytes = (char*)targetPtr;
	
	targetData[2] = zero;
	targetData[1] = zero;
	targetData[0] = zero;
	targetData[6] = zero;
	targetData[5] = zero;
	targetData[4] = zero;
	targetBytes[28] = 0;
	targetBytes[29] = 0;
	*(short*)(targetBytes + 30) = 0;
	targetBytes[33] = 0;
	targetBytes[32] = 0;
	targetData[9] = zero;
}
