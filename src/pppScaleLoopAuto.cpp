#include "ffcc/pppScaleLoopAuto.h"
#include <dolphin/types.h>

extern int lbl_8032ED70;
extern float lbl_801EC9F0[];

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
    if (lbl_8032ED70 != 0) {
        return;
    }

    int* offsets = (int*)((u8*)arg3 + 0xC);
    pppScaleLoopAutoWork* work = (pppScaleLoopAutoWork*)((u8*)arg1 + offsets[0] + 0x80);

    if (*(u32*)((u8*)arg2 + 0x0) == *(u32*)((u8*)arg1 + 0xC)) {
        work->m_scale[0] += *(f32*)((u8*)arg2 + 0x8);
        work->m_scale[1] += *(f32*)((u8*)arg2 + 0xC);
        work->m_scale[2] += *(f32*)((u8*)arg2 + 0x10);
    }

    if (work->m_initialized == 0) {
        work->m_initialized = 1;
        work->m_baseScale[0] = work->m_scale[0];
        work->m_baseScale[1] = work->m_scale[1];
        work->m_baseScale[2] = work->m_scale[2];
        work->m_countA = *((u8*)arg2 + 29);
        work->m_countB = *((u8*)arg2 + 30);
        return;
    }

    s16 angle = work->m_angle;
    if (angle < 90) {
        s8 cnt = work->m_countA;
        if (cnt <= 0) {
            return;
        }

        work->m_countA = cnt - 1;
        work->m_scale[0] = work->m_baseScale[0] + work->m_delta;
        work->m_scale[1] = work->m_baseScale[1] + work->m_delta;
        work->m_scale[2] = work->m_baseScale[2] + work->m_delta;
        return;
    }

    if (angle < 270) {
        s8 cnt = work->m_countB;
        if (cnt <= 0) {
            return;
        }

        work->m_countB = cnt - 1;
        work->m_scale[0] = work->m_baseScale[0] + work->m_delta;
        work->m_scale[1] = work->m_baseScale[1] + work->m_delta;
        work->m_scale[2] = work->m_baseScale[2] + work->m_delta;
        return;
    }

    work->m_step++;
    if (work->m_step > *((u8*)arg2 + 28)) {
        work->m_step = 0;
        work->m_angle = 0;
        work->m_countA = *((u8*)arg2 + 29);
        work->m_countB = *((u8*)arg2 + 30);
        return;
    }

    angle += 360 / (s32)(*((u8*)arg2 + 28));
    work->m_angle = angle;

    {
        s32 tableAngle = (s32)(((f64)((s32)work->m_angle << 15)) / 360.0);
        f32 sinVal = *(f32*)((u8*)lbl_801EC9F0 + (tableAngle & 0x3FFC));
        f32 delta = (*(f32*)((u8*)arg2 + 24) * sinVal) * *(f32*)((u8*)arg2 + 32);

        work->m_delta = delta;
        work->m_scale[0] = work->m_baseScale[0] + delta;
        work->m_scale[1] = work->m_baseScale[1] + delta;
        work->m_scale[2] = work->m_baseScale[2] + delta;
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
	
	void* targetPtr = (void*)((char*)arg1 + (int)ptr + 0x80);
	float* targetData = (float*)targetPtr;
	char* targetBytes = (char*)targetPtr;
	
	targetData[2] = 0.0f;
	targetData[1] = 0.0f;
	targetData[0] = 0.0f;
	targetData[6] = 0.0f;
	targetData[5] = 0.0f;
	targetData[4] = 0.0f;
	targetBytes[28] = 0;
	targetBytes[29] = 0;
	*(short*)(targetBytes + 30) = 0;
	targetBytes[33] = 0;
	targetBytes[32] = 0;
	targetData[9] = 0.0f;
}
