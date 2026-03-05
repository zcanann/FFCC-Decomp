#include "ffcc/pppYmLookOn.h"
#include <dolphin/mtx.h>

extern int lbl_8032ED70;
extern float lbl_80330EC8;
extern float lbl_80330ECC;

struct _pppMngSt;
extern struct _pppMngSt* lbl_8032ED50;

extern "C" void pppSetFpMatrix__FP9_pppMngSt(struct _pppMngSt*);

/*
 * --INFO--
 * PAL Address: 0x800d8aa4
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmLookOn(struct pppYmLookOn* pppYmLookOn, struct UnkC* param_2)
{
    int dataOffset = *param_2->m_serializedDataOffsets;
    *(int*)((char*)pppYmLookOn + dataOffset + 0x80) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800d88c8
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmLookOn(struct pppYmLookOn* pppYmLookOn, struct UnkB* param_2, struct UnkC* param_3)
{
    struct _pppMngSt* pppMngSt;
    int workOffset;
    u8* owner;
    u8** ownerRef;
    Vec local_44;
    Vec local_28;
    Vec local_34;
    Vec local_40;
    Vec local_4c;
    Vec local_58;

    if (lbl_8032ED70 != 0) {
        return;
    }

    pppMngSt = lbl_8032ED50;
    owner = *(u8**)((u8*)pppMngSt + 0xdc);
    workOffset = *param_3->m_serializedDataOffsets;
    ownerRef = (u8**)((u8*)pppYmLookOn + workOffset + 0x80);
    if (owner == nullptr) {
        if (*ownerRef == nullptr) {
            return;
        }
    }
    *ownerRef = owner;
    if (owner == nullptr) {
        owner = *ownerRef;
    }

    local_4c.x = *(f32*)(owner + 0x15c);
    local_4c.z = *(f32*)(owner + 0x164);
    local_4c.y = *(f32*)(owner + 0x160) + param_2->m_dataValIndex;
    local_58.x = *(f32*)((u8*)pppMngSt + 0x84);
    local_58.y = *(f32*)((u8*)pppMngSt + 0x94);
    local_58.z = *(f32*)((u8*)pppMngSt + 0xa4);
    PSVECSubtract(&local_58, &local_4c, &local_44);

    if (((lbl_80330EC8 != local_44.x) || (lbl_80330EC8 != local_44.y)) || (lbl_80330EC8 != local_44.z)) {
        PSVECNormalize(&local_44, &local_40);
        local_28.x = local_40.z;
        local_28.y = lbl_80330EC8;
        local_28.z = -local_40.x;
        if ((lbl_80330EC8 == local_40.z) && (lbl_80330EC8 == local_28.z)) {
            local_28.x = lbl_80330ECC;
            local_28.z = lbl_80330EC8;
            local_34.x = lbl_80330EC8;
            local_34.y = lbl_80330EC8;
            local_34.z = lbl_80330ECC;
        } else {
            PSVECNormalize(&local_28, &local_28);
            PSVECCrossProduct(&local_40, &local_28, &local_34);
            PSVECNormalize(&local_34, &local_34);
        }
        *(f32*)((u8*)lbl_8032ED50 + 0x78) = local_28.x;
        *(f32*)((u8*)lbl_8032ED50 + 0x88) = local_28.y;
        *(f32*)((u8*)lbl_8032ED50 + 0x98) = local_28.z;
        *(f32*)((u8*)lbl_8032ED50 + 0x7c) = local_34.x;
        *(f32*)((u8*)lbl_8032ED50 + 0x8c) = local_34.y;
        *(f32*)((u8*)lbl_8032ED50 + 0x9c) = local_34.z;
        *(f32*)((u8*)lbl_8032ED50 + 0x80) = local_40.x;
        *(f32*)((u8*)lbl_8032ED50 + 0x90) = local_40.y;
        *(f32*)((u8*)lbl_8032ED50 + 0xa0) = local_40.z;
        pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
    }
}
