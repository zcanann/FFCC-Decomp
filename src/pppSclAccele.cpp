#include "ffcc/pppSclAccele.h"

extern int lbl_8032ED70;
extern float lbl_80330050;

typedef struct {
    int m_graphId;
    int m_pad;
    float m_x;
    float m_y;
    float m_z;
} PppSclAcceleStep;

typedef struct {
    int m_pad0;
    int m_pad1;
    int m_pad2;
    int* m_offsets;
} PppSclAcceleConfig;

/*
 * --INFO--
 * PAL Address: 0x80063150
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclAcceleCon(void* arg1, void* arg2)
{
    PppSclAcceleConfig* config = (PppSclAcceleConfig*)arg2;
    float* accel = (float*)((char*)arg1 + config->m_offsets[1] + 0x80);
    float zero = lbl_80330050;

    accel[2] = zero;
    accel[1] = zero;
    accel[0] = zero;
}

/*
 * --INFO--
 * PAL Address: 0x80063174
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSclAccele(void* arg1, void* arg2, void* arg3)
{
    PppSclAcceleConfig* config = (PppSclAcceleConfig*)arg3;
    PppSclAcceleStep* step = (PppSclAcceleStep*)arg2;
    float* scale = (float*)((char*)arg1 + config->m_offsets[0] + 0x80);
    float* accel = (float*)((char*)arg1 + config->m_offsets[1] + 0x80);

    if (lbl_8032ED70 != 0) {
        return;
    }

    if (step->m_graphId == ((int*)arg1)[3]) {
        accel[0] += step->m_x;
        accel[1] += step->m_y;
        accel[2] += step->m_z;
    }

    scale[0] += accel[0];
    scale[1] += accel[1];
    scale[2] += accel[2];
}
