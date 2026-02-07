#include "ffcc/pppRandFloat.h"
#include "ffcc/math.h"

extern CMath math;
extern int lbl_8032ED70;
extern float lbl_8032FF88;
extern float lbl_801EADC8;
extern "C" float RandF__5CMathFv(CMath* instance);

/*
 * --INFO--
 * PAL Address: 0x80061d48
 * PAL Size: 268b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRandFloat(void* param1, void* param2, void* param3)
{
    char* base = (char*)param1;
    int* param = (int*)param2;
    void* ctx = param3;
    int index = *(int*)(base + 0xC);

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (index == 0) {
        float out = RandF__5CMathFv(&math);

        if (*(unsigned char*)((char*)param + 0xC) != 0) {
            out += RandF__5CMathFv(&math);
        } else {
            out *= lbl_8032FF88;
        }

        int outputOffset = *(int*)*(int**)((char*)ctx + 0xC);
        *(float*)(base + outputOffset + 0x80) = out;
        return;
    }

    if (param[0] == index) {
        int outputOffset = *(int*)*(int**)((char*)ctx + 0xC);
        float* source;

        if (param[1] == -1) {
            source = &lbl_801EADC8;
        } else {
            source = (float*)(base + param[1] + 0x80);
        }

        float blend = *(float*)((char*)param + 0x8);
        float output = *(float*)(base + outputOffset + 0x80);
        *source = *source + (blend * output - blend);
    }
}
