#include "ffcc/pppScaleLoopAuto.h"
#include <dolphin/types.h>

extern int lbl_8032ED70;
extern float lbl_801EC9F0[];

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

    u32* ctrlA = *(u32**)arg3;
    u32* ctrlB = *(u32**)((u8*)arg3 + 0xC);
    u8* workA = (u8*)arg1 + ctrlA[0] + 0x80;
    u8* workB = (u8*)arg1 + ctrlB[0] + 0x80;
    f32* workBF = (f32*)workB;

    if (*(u32*)((u8*)arg2 + 0x0) == *(u32*)((u8*)arg1 + 0xC)) {
        *(f32*)(workA + 0x0) += *(f32*)((u8*)arg2 + 0x8);
        *(f32*)(workA + 0x4) += *(f32*)((u8*)arg2 + 0xC);
        *(f32*)(workA + 0x8) += *(f32*)((u8*)arg2 + 0x10);
    }

    if (workB[28] == 0) {
        workB[28] = 1;
        workBF[4] = workBF[0];
        workBF[5] = workBF[1];
        workBF[6] = workBF[2];
        workB[32] = *((u8*)arg2 + 29);
        workB[33] = *((u8*)arg2 + 30);
        return;
    }

    s16 angle = *(s16*)(workB + 30);
    if (angle < 90) {
        s8 cnt = *(s8*)(workB + 32);
        if (cnt <= 0) {
            return;
        }

        *(s8*)(workB + 32) = cnt - 1;
        workBF[4] += workBF[9];
        workBF[5] += workBF[9];
        workBF[6] += workBF[9];
        return;
    }

    if (angle < 270) {
        s8 cnt = *(s8*)(workB + 33);
        if (cnt <= 0) {
            return;
        }

        *(s8*)(workB + 33) = cnt - 1;
        workBF[4] += workBF[9];
        workBF[5] += workBF[9];
        workBF[6] += workBF[9];
        return;
    }

    workB[29]++;
    if (workB[29] > *((u8*)arg2 + 28)) {
        workB[29] = 0;
        *(s16*)(workB + 30) = 0;
        workB[32] = *((u8*)arg2 + 29);
        workB[33] = *((u8*)arg2 + 30);
        return;
    }

    angle += 360 / (s32)(*((u8*)arg2 + 28));
    *(s16*)(workB + 30) = angle;

    {
        s32 tableAngle = (angle * 32768) / 360;
        f32 sinVal = *(f32*)((u8*)lbl_801EC9F0 + (tableAngle & 0x3FFC));
        f32 delta = (*(f32*)((u8*)arg2 + 24) * sinVal) * *(f32*)((u8*)arg2 + 32);

        workBF[9] = delta;
        workBF[4] += delta;
        workBF[5] += delta;
        workBF[6] += delta;
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
