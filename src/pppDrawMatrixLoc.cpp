#include "ffcc/pppDrawMatrixLoc.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>

extern float FLOAT_803331d8;

/*
 * --INFO--
 * PAL Address: 0x8016c9e8
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawMatrixLoc(_pppPObject* param_1)
{
    Vec local_38;
    Vec local_2c;
    Vec local_20[2];
    
    local_2c.z = FLOAT_803331d8;
    local_2c.y = FLOAT_803331d8;
    local_2c.x = FLOAT_803331d8;
    PSMTXCopy(*(Mtx*)((char*)param_1 + 0x10), *(Mtx*)((char*)param_1 + 0x40));
    PSMTXMultVec(ppvWorldMatrix, &local_2c, &local_2c);
    local_38.x = (float)(*(int*)((char*)param_1 + 0x40));
    local_38.y = *(float*)((char*)param_1 + 0x4C);
    local_38.z = *(float*)((char*)param_1 + 0x5C);
    PSVECAdd(&local_38, &local_2c, local_20);
    *(int*)((char*)param_1 + 0x40) = (int)local_20[0].x;
    *(float*)((char*)param_1 + 0x4C) = local_20[0].y;
    *(float*)((char*)param_1 + 0x5C) = local_20[0].z;
}