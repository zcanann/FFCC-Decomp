#include "ffcc/pppYmLookOn.h"
#include <dolphin/mtx.h>

extern int DAT_8032ed70;
extern float FLOAT_80330ec8;
extern float FLOAT_80330ecc;

struct _pppMngSt;
extern struct _pppMngSt* pppMngStPtr;

void pppSetFpMatrix__FP9_pppMngSt(struct _pppMngSt*);

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
    int dataOffset;
    u8* owner;
    Vec local_58;
    Vec local_4c;
    Vec local_40;
    Vec local_34;
    Vec local_28;
    Vec local_1c;

    if (DAT_8032ed70 != 0) {
        return;
    }

    pppMngSt = pppMngStPtr;
    owner = *(u8**)((u8*)pppMngSt + 0xdc);
    dataOffset = *param_3->m_serializedDataOffsets;
    if ((owner != nullptr) || (*(int*)((u8*)pppYmLookOn + dataOffset + 0x80) != 0)) {
        *(u8**)((u8*)pppYmLookOn + dataOffset + 0x80) = owner;
        if (owner == nullptr) {
            owner = *(u8**)((u8*)pppYmLookOn + dataOffset + 0x80);
        }

        local_4c.x = *(f32*)(owner + 0x15c);
        local_4c.y = *(f32*)(owner + 0x160) + (f32)param_2->m_dataValIndex;
        local_4c.z = *(f32*)(owner + 0x164);
        local_58.x = *(f32*)((u8*)pppMngSt + 0x84);
        local_58.y = *(f32*)((u8*)pppMngSt + 0x94);
        local_58.z = *(f32*)((u8*)pppMngSt + 0xa4);
        PSVECSubtract(&local_58, &local_4c, &local_1c);

        if (((FLOAT_80330ec8 != local_1c.x) || (FLOAT_80330ec8 != local_1c.y)) ||
            (FLOAT_80330ec8 != local_1c.z)) {
            PSVECNormalize(&local_1c, &local_40);
            local_28.z = -local_40.x;
            local_28.x = local_40.z;
            local_28.y = FLOAT_80330ec8;
            if ((FLOAT_80330ec8 == local_40.z) && (FLOAT_80330ec8 == local_28.z)) {
                local_28.x = FLOAT_80330ecc;
                local_28.z = FLOAT_80330ec8;
                local_34.x = FLOAT_80330ec8;
                local_34.y = FLOAT_80330ec8;
                local_34.z = FLOAT_80330ecc;
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
            pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        }
    }
}
