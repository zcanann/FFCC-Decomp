#include "ffcc/pppSclMove.h"
#include <dolphin/mtx.h>

extern int DAT_8032ed70;

/*
 * --INFO--
 * PAL Address: 0x80063210
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclMoveCon(void* param1, void* param2)
{
    void* ptr = (void*)((int*)((char*)param2 + 0xC))[0];
    ptr = (void*)((int*)((char*)ptr + 0x4))[0];
    Vec* data1 = (Vec*)((char*)param1 + (int)ptr + 0x80);
    data1->x = 0.0f;
    data1->y = 0.0f;
    data1->z = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80063234
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclMove(void* param1, void* param2, void* param3)
{
    int* data2 = *(int**)((char*)param3 + 0xC);
    float* dataA = (float*)((char*)param1 + data2[1] + 0x80);
    float* dataB = (float*)((char*)param1 + data2[0] + 0x80);

    if (*(volatile int*)&DAT_8032ed70 != 0) {
        return;
    }

    if (*(int*)param2 == *(int*)((char*)param1 + 0xC)) {
        dataB[0] += *(float*)((char*)param2 + 0x8);
        dataB[1] += *(float*)((char*)param2 + 0xC);
        dataB[2] += *(float*)((char*)param2 + 0x10);
    }

    dataA[0] += dataB[0];
    dataA[1] += dataB[1];
    dataA[2] += dataB[2];
}
