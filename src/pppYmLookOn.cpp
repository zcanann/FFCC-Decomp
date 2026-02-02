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
    *((int*)((char*)(&pppYmLookOn->field0_0x0[2]) + *param_2->m_serializedDataOffsets)) = 0;
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
    int iVar1;
    float fVar2;
    Vec local_58;
    Vec local_4c;
    Vec local_40;
    Vec local_34;
    Vec local_28;
    Vec local_1c[2];
    
    pppMngSt = pppMngStPtr;
    if (DAT_8032ed70 == 0) {
        // Access velocity from pppMngSt - this will need proper struct definition
        fVar2 = 0.0f; // Placeholder for (pppMngStPtr->m_velocity).y;
        iVar1 = *param_3->m_serializedDataOffsets;
        
        if ((fVar2 != 0.0f) || (*((int*)((char*)(&pppYmLookOn->field0_0x0[2]) + iVar1)) != 0)) {
            *((float*)((char*)(&pppYmLookOn->field0_0x0[2]) + iVar1)) = fVar2;
            if (fVar2 == 0.0f) {
                fVar2 = *((float*)((char*)(&pppYmLookOn->field0_0x0[2]) + iVar1));
            }
            
            // Access matrix data - placeholder implementation
            local_4c.x = 0.0f; // *(float*)((int)fVar2 + 0x15c);
            local_4c.z = 0.0f; // *(float*)((int)fVar2 + 0x164);
            local_4c.y = 0.0f + (float)param_2->m_dataValIndex; // *(float*)((int)fVar2 + 0x160) + (float)param_2->m_dataValIndex;
            
            // Access pppMngSt matrix - placeholder
            local_58.x = 0.0f; // (pppMngStPtr->m_matrix).value[0][3];
            local_58.y = 0.0f; // (pppMngStPtr->m_matrix).value[1][3];
            local_58.z = 0.0f; // (pppMngStPtr->m_matrix).value[2][3];
            
            PSVECSubtract(&local_58, &local_4c, local_1c);
            
            if (((FLOAT_80330ec8 != local_1c[0].x) || (FLOAT_80330ec8 != local_1c[0].y)) ||
               (FLOAT_80330ec8 != local_1c[0].z)) {
                PSVECNormalize(local_1c, &local_40);
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
                
                // Set matrix values - placeholder
                //(pppMngStPtr->m_matrix).value[0][0] = local_28.x;
                //(pppMngStPtr->m_matrix).value[1][0] = local_28.y;
                //(pppMngStPtr->m_matrix).value[2][0] = local_28.z;
                //(pppMngStPtr->m_matrix).value[0][1] = local_34.x;
                //(pppMngStPtr->m_matrix).value[1][1] = local_34.y;
                //(pppMngStPtr->m_matrix).value[2][1] = local_34.z;
                //(pppMngStPtr->m_matrix).value[0][2] = local_40.x;
                //(pppMngStPtr->m_matrix).value[1][2] = local_40.y;
                //(pppMngStPtr->m_matrix).value[2][2] = local_40.z;
                
                pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
            }
        }
    }
}