#include "ffcc/pppParHitSph.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include <dolphin/mtx.h>

extern unsigned char* lbl_8032ED50;
extern float FLOAT_80330700;
extern unsigned char CFlat[];

/*
 * --INFO--
 * PAL Address: 80093d04
 * PAL Size: 372b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppParHitSph(struct _pppPObject* param_1, int param_2)
{
    _pppMngSt* pppMngSt;
    float radius;
    u32 local_a8;
    u32 local_a4;
    Vec local_a0;
    Vec local_94;
    Vec local_88;
    Mtx MStack_78;
    Mtx local_48;
    
    pppMngSt = (_pppMngSt*)lbl_8032ED50;
    PSVECSubtract((Vec*)(lbl_8032ED50 + 0x8), (Vec*)(lbl_8032ED50 + 0x48), &local_88);
    local_94.x = *(float*)(lbl_8032ED50 + 0x84);
    local_94.y = *(float*)(lbl_8032ED50 + 0x94);
    local_94.z = *(float*)(lbl_8032ED50 + 0xA4);
    radius = *(float*)(lbl_8032ED50 + 0x64) * *(float*)(param_2 + 8);
    
    if (((FLOAT_80330700 == local_88.x) && (FLOAT_80330700 == local_88.y)) &&
        (FLOAT_80330700 == local_88.z)) {
        pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, 0.0f);
    } else {
        pppHitCylinderSendSystem(pppMngSt, &local_94, &local_88, radius, *(float*)(param_2 + 4));
    }
    
    if ((*(unsigned int*)(CFlat + 0x129c) & 0x200000) != 0) {
        local_a4 = 0xFFFFFFFF;
        PSMTXIdentity(MStack_78);
        PSMTXIdentity(local_48);
        local_48[0][0] = radius;
        local_48[1][1] = radius;
        local_48[2][2] = radius;
        PSMTXConcat(ppvCameraMatrix0, MStack_78, MStack_78);
        PSMTXMultVec(MStack_78, &local_94, &local_a0);
        local_48[0][3] = local_a0.x;
        local_48[1][3] = local_a0.y;
        local_48[2][3] = local_a0.z;
        local_a8 = local_a4;
        Graphic.DrawSphere(local_48, *(_GXColor*)&local_a8);
    }
}
