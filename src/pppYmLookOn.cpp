#include "ffcc/pppYmLookOn.h"
#include "ffcc/partMng.h"
#include "ffcc/ppp_constants.h"
#include <dolphin/mtx.h>

void pppSetFpMatrix(_pppMngSt*);

extern "C" void pppSetFpMatrix(struct _pppMngSt*);

/*
 * --INFO--
 * PAL Address: 0x800d88c8
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmLookOn(struct pppYmLookOn* pppYmLookOn, struct pppYmLookOnUnkB* param_2, struct pppYmLookOnUnkC* param_3)
{
    struct _pppMngSt* pppMngSt;
    int workOffset;
    u8* owner;
    u8** work;
    Vec local_44;
    Vec local_28;
    Vec local_34;
    Vec local_40;
    Vec local_4c;
    Vec local_58;

    if (gPppCalcDisabled != 0) {
        return;
    }

    pppMngSt = pppMngStPtr;
    owner = *(u8**)((u8*)pppMngSt + 0xdc);
    workOffset = *param_3->m_serializedDataOffsets;
    work = (u8**)((u8*)pppYmLookOn + workOffset + 0x80);
    if (owner == nullptr) {
        if (*work == nullptr) {
            return;
        }
    }
    *work = owner;
    if (owner == nullptr) {
        owner = *work;
    }

    local_4c.x = *(f32*)(owner + 0x15c);
    local_4c.y = *(f32*)(owner + 0x160);
    local_4c.z = *(f32*)(owner + 0x164);
    local_4c.y += param_2->m_dataValIndex;
    local_58.x = *(f32*)((u8*)pppMngStPtr + 0x84);
    local_58.y = *(f32*)((u8*)pppMngStPtr + 0x94);
    local_58.z = *(f32*)((u8*)pppMngStPtr + 0xa4);
    PSVECSubtract(&local_58, &local_4c, &local_44);

    if (((gPppYmLookOnZero != local_44.x) || (gPppYmLookOnZero != local_44.y)) || (gPppYmLookOnZero != local_44.z)) {
        PSVECNormalize(&local_44, &local_40);
        local_28.x = local_40.z;
        local_28.y = gPppYmLookOnZero;
        local_28.z = -local_40.x;
        f32 zero = gPppYmLookOnZero;
        if ((zero == local_40.z) && (zero == local_28.z)) {
            local_28.x = gPppYmLookOnOne;
            local_28.y = gPppYmLookOnZero;
            local_28.z = gPppYmLookOnZero;
            local_34.x = gPppYmLookOnZero;
            local_34.y = gPppYmLookOnZero;
            local_34.z = gPppYmLookOnOne;
        } else {
            PSVECNormalize(&local_28, &local_28);
            PSVECCrossProduct(&local_40, &local_28, &local_34);
            PSVECNormalize(&local_34, &local_34);
        }
        *(f32*)((u8*)pppMngStPtr + 0x78) = local_28.x;
        *(f32*)((u8*)pppMngStPtr + 0x88) = local_28.y;
        *(f32*)((u8*)pppMngStPtr + 0x98) = local_28.z;
        *(f32*)((u8*)pppMngStPtr + 0x7c) = local_34.x;
        *(f32*)((u8*)pppMngStPtr + 0x8c) = local_34.y;
        *(f32*)((u8*)pppMngStPtr + 0x9c) = local_34.z;
        *(f32*)((u8*)pppMngStPtr + 0x80) = local_40.x;
        *(f32*)((u8*)pppMngStPtr + 0x90) = local_40.y;
        *(f32*)((u8*)pppMngStPtr + 0xa0) = local_40.z;
        pppSetFpMatrix(pppMngSt);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d8aa4
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmLookOn(struct pppYmLookOn* pppYmLookOn, struct pppYmLookOnUnkC* param_2)
{
    int dataOffset = *param_2->m_serializedDataOffsets;
    *(int*)((char*)pppYmLookOn + dataOffset + 0x80) = 0;
}
