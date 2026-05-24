#include "ffcc/pppYmLookOn.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/ppp_constants.h"
#include <dolphin/mtx.h>

static inline u8** GetYmLookOnWork(pppYmLookOn* lookOn, pppYmLookOnCtrl* ctrl)
{
    return reinterpret_cast<u8**>(lookOn->m_object.m_workArea + *ctrl->m_serializedDataOffsets);
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
void pppFrameYmLookOn(struct pppYmLookOn* pppYmLookOn, struct pppYmLookOnStep* param_2, struct pppYmLookOnCtrl* param_3)
{
    struct _pppMngSt* pppMngSt;
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
    owner = reinterpret_cast<u8*>(pppMngSt->m_lookTarget);
    work = GetYmLookOnWork(pppYmLookOn, param_3);
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
    local_58.x = pppMngStPtr->m_matrix.value[0][3];
    local_58.y = pppMngStPtr->m_matrix.value[1][3];
    local_58.z = pppMngStPtr->m_matrix.value[2][3];
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
        pppMngStPtr->m_matrix.value[0][0] = local_28.x;
        pppMngStPtr->m_matrix.value[1][0] = local_28.y;
        pppMngStPtr->m_matrix.value[2][0] = local_28.z;
        pppMngStPtr->m_matrix.value[0][1] = local_34.x;
        pppMngStPtr->m_matrix.value[1][1] = local_34.y;
        pppMngStPtr->m_matrix.value[2][1] = local_34.z;
        pppMngStPtr->m_matrix.value[0][2] = local_40.x;
        pppMngStPtr->m_matrix.value[1][2] = local_40.y;
        pppMngStPtr->m_matrix.value[2][2] = local_40.z;
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
void pppConstructYmLookOn(struct pppYmLookOn* pppYmLookOn, struct pppYmLookOnCtrl* param_2)
{
    *GetYmLookOnWork(pppYmLookOn, param_2) = 0;
}
