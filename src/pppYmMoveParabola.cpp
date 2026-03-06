#include "ffcc/pppYmMoveParabola.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "types.h"
#include "dolphin/mtx.h"

extern float lbl_80330E1C;
extern float lbl_80330E18;
extern float lbl_80330E20;
extern float lbl_80330E24;
extern float lbl_80330E28;
extern float lbl_801EC9F0[];
extern int lbl_8032ED70;
extern unsigned char* lbl_8032ED50;

extern "C" {
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppAddVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
void pppNormalize__FR3Vec3Vec(Vec*, Vec*);
void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);
}

/*
 * --INFO--
 * PAL Address: 0x800d4558
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkC* dataPtr)
{
    _pppMngSt* pppMngSt = (_pppMngSt*)lbl_8032ED50;
    f32 fVar2 = lbl_80330E1C;
    f32* pfVar = (f32*)((u8*)(&basePtr->field0_0x0 + 2) + *dataPtr->m_serializedDataOffsets);
    Vec local_48;
    Vec local_24;
    f32 local_3c;
    f32 local_38;
    f32 local_34;
    f32 local_30;
    f32 local_2c;
    f32 local_28;
    f32 local_18;
    f32 local_14;
    f32 local_10;

    pfVar[2] = lbl_80330E1C;
    pfVar[1] = fVar2;
    *pfVar = fVar2;
    *(u16*)(pfVar + 3) = 1;
    if (Game.game.m_currentSceneId == 7) {
        local_24.x = *(f32*)((u8*)pppMngSt + 0x58);
        local_24.y = *(f32*)((u8*)pppMngSt + 0x5c);
        local_24.z = *(f32*)((u8*)pppMngSt + 0x60);
        pppCopyVector__FR3Vec3Vec((Vec*)(pfVar + 4), &local_24);
        local_3c = ((_pppMngSt*)lbl_8032ED50)->m_matrix.value[0][3];
        local_38 = ((_pppMngSt*)lbl_8032ED50)->m_matrix.value[1][3];
        local_34 = ((_pppMngSt*)lbl_8032ED50)->m_matrix.value[2][3];
        local_30 = pfVar[4];
        local_2c = pfVar[5];
        local_28 = pfVar[6];
        local_18 = local_3c;
        local_14 = local_38;
        local_10 = local_34;
        pppAddVector__FR3Vec3Vec3Vec((Vec*)(pfVar + 4), (Vec*)&local_30, (Vec*)&local_3c);
        local_48.x = pfVar[4];
        local_48.y = pfVar[5];
        local_48.z = pfVar[6];
        pppCopyVector__FR3Vec3Vec((Vec*)((u8*)pppMngSt + 0x68), &local_48);
        *(f32*)((u8*)pppMngSt + 0x68) = *(f32*)((u8*)pppMngSt + 0x68) + lbl_80330E18;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800d4278
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct pppYmMoveParabolaUnkB* stepData, struct pppYmMoveParabolaUnkC* offsetData)
{
    if (lbl_8032ED70 == 0) {
        _pppMngSt* pppMngSt = (_pppMngSt*)lbl_8032ED50;
        f32* pfVar = (f32*)((u8*)&basePtr->field0_0x0 + 8 + *offsetData->m_serializedDataOffsets);
        
        // Update velocity and position
        pfVar[1] = pfVar[1] + pfVar[2];
        *pfVar = *pfVar + pfVar[1];
        
        if (stepData->m_graphId == basePtr->field0_0x0.m_graphId) {
            *pfVar = *pfVar + stepData->m_stepValue;
            pfVar[1] = pfVar[1] + (f32)stepData->m_arg3;
            pfVar[2] = pfVar[2] + *(f32*)stepData->m_payload;
        }
        
        u16 counter = *(u16*)(pfVar + 3);
        double frameCount = (double)(f32)counter;
        
        Vec direction;
        if (Game.game.m_currentSceneId == 7) {
            direction.y = lbl_80330E1C;
            direction.x = lbl_80330E18;
            direction.z = lbl_80330E1C;
        } else {
            PSVECSubtract((Vec*)((u8*)pppMngSt + 0x68), (Vec*)((u8*)pppMngSt + 0x58), &direction);
        }
        
        // Normalize the direction vector
        Vec tempDir = direction;
        pppNormalize__FR3Vec3Vec(&direction, &tempDir);
        
        // Trigonometric parabolic motion calculations
        u32 sinIndex = (u32)((lbl_80330E20 * (f32)stepData->m_dataValIndex) / lbl_80330E24);
        
        f32 baseValue = *pfVar;
        f32 horizontalScale = (f32)(frameCount * (double)(baseValue * lbl_801EC9F0[((sinIndex + 0x4000) & 0xfffc) / 4]));
        f32 horizontalX = direction.x * horizontalScale;
        f32 horizontalZ = direction.z * horizontalScale;
        f32 verticalY = (f32)(frameCount * (double)(baseValue * lbl_801EC9F0[(sinIndex & 0xfffc) / 4]) - 
                             (double)(f32)(frameCount * (double)(f32)((double)(lbl_80330E28 * (f32)stepData->m_initWOrk) * frameCount)));
        
        Vec newPosition;
        if (Game.game.m_currentSceneId == 7) {
            Vec basePos;
            basePos.x = pfVar[4];
            basePos.y = pfVar[5];
            basePos.z = pfVar[6];
            Vec offset;
            offset.x = horizontalX;
            offset.y = verticalY;
            offset.z = horizontalZ;
            pppAddVector__FR3Vec3Vec3Vec(&newPosition, &offset, &basePos);
        } else {
            Vec basePos;
            basePos.x = *(f32*)((u8*)pppMngSt + 0x58);
            basePos.y = *(f32*)((u8*)pppMngSt + 0x5c);
            basePos.z = *(f32*)((u8*)pppMngSt + 0x60);
            Vec offset;
            offset.x = horizontalX;
            offset.y = verticalY;
            offset.z = horizontalZ;
            pppAddVector__FR3Vec3Vec3Vec(&newPosition, &offset, &basePos);
        }

        pppCopyVector__FR3Vec3Vec((Vec*)((u8*)pppMngSt + 0x48), (Vec*)((u8*)pppMngSt + 0x8));
        pppCopyVector__FR3Vec3Vec((Vec*)((u8*)pppMngSt + 0x8), &newPosition);
        
        // Update matrix with new position
        ((_pppMngSt*)lbl_8032ED50)->m_matrix.value[0][3] = newPosition.x;
        ((_pppMngSt*)lbl_8032ED50)->m_matrix.value[1][3] = newPosition.y;
        ((_pppMngSt*)lbl_8032ED50)->m_matrix.value[2][3] = newPosition.z;
        
        pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        
        *(u16*)(pfVar + 3) = *(u16*)(pfVar + 3) + 1;
    }
}

