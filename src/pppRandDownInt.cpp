#include "ffcc/pppRandDownInt.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;

extern "C" float RandF__5CMathFv();

/*
 * --INFO--
 * PAL Address: 0x80066ab4
 * PAL Size: 300b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandDownInt(void* param1, void* param2, void* param3)
{
    int* p1 = (int*)param1;
    int* p2 = (int*)param2;
    int* p3 = (int*)param3;

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (p1[3] == 0) {
        float randValue = RandF__5CMathFv();
        randValue = -randValue;

        unsigned char* p2_bytes = (unsigned char*)param2;
        if (p2_bytes[0xC] != 0) {
            float rand2 = RandF__5CMathFv();
            randValue = randValue - rand2;
            randValue = randValue * 100.0f;
        }

        int* p3_data = (int*)p3[3];
        *(float*)((char*)p1 + p3_data[0] + 0x80) = randValue;
        return;
    }

    if (p2[0] != p1[3]) {
        return;
    }

    if (p2[1] != -1) {
        int multiplier = p2[2];
        int* p3_data = (int*)p3[3];
        float source = *(float*)((char*)p1 + p3_data[0] + 0x80);
        int* target = (int*)((char*)p1 + p2[1] + 0x80);

        *target = *target + (int)(source * (float)multiplier);
    }
}
