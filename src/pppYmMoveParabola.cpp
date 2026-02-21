#include "ffcc/pppYmMoveParabola.h"
#include "ffcc/pppPart.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "types.h"
#include "dolphin/mtx.h"

extern float FLOAT_80330e1c;  // 0.0f
extern float FLOAT_80330e18;  // Small offset constant
extern float FLOAT_80330e20;  // Scale factor
extern float FLOAT_80330e24;  // Divisor
extern float FLOAT_80330e28;  // Gravity factor
extern int ppvSinTbl;         // Sin table base
extern int DAT_8032ed70;      // Global flag

extern "C" {
void pppCopyVector__FR3Vec3Vec(Vec*, const Vec*);
void pppAddVector__FR3Vec3Vec3Vec(Vec*, const Vec*, const Vec*);
void pppNormalize__FR3Vec3Vec(float*, Vec*);
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
extern "C" void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, struct UnkC* dataPtr)
{
    _pppMngSt* pppMngSt = pppMngStPtr;
    f32 fVar2 = FLOAT_80330e1c;
    f32* pfVar = (f32*)((u8*)&basePtr->field0_0x0 + 8 + *dataPtr->m_serializedDataOffsets);
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

    pfVar[2] = FLOAT_80330e1c;
    pfVar[1] = fVar2;
    *pfVar = fVar2;
    *(u16*)(pfVar + 3) = 1;
    if (Game.game.m_currentSceneId == 7) {
        local_24.x = *(f32*)((u8*)pppMngSt + 0x58);
        local_24.y = *(f32*)((u8*)pppMngSt + 0x5c);
        local_24.z = *(f32*)((u8*)pppMngSt + 0x60);
        pppCopyVector__FR3Vec3Vec((Vec*)(pfVar + 4), &local_24);
        local_3c = pppMngStPtr->m_matrix.value[0][3];
        local_38 = pppMngStPtr->m_matrix.value[1][3];
        local_34 = pppMngStPtr->m_matrix.value[2][3];
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
        *(f32*)((u8*)pppMngSt + 0x68) = *(f32*)((u8*)pppMngSt + 0x68) + FLOAT_80330e18;
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
extern "C" void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct UnkB* stepData, struct UnkC* offsetData)
{
    _pppMngSt* pppMngSt = pppMngStPtr;
    
    if (DAT_8032ed70 == 0) {
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
            direction.y = FLOAT_80330e1c;
            direction.x = FLOAT_80330e18;
            direction.z = FLOAT_80330e1c;
        } else {
            PSVECSubtract((Vec*)((u8*)pppMngSt + 0x68), (Vec*)((u8*)pppMngSt + 0x58), &direction);
        }
        
        // Normalize the direction vector
        Vec tempDir = direction;
        pppNormalize__FR3Vec3Vec((float*)&direction, &tempDir);
        
        // Trigonometric parabolic motion calculations
        u32 sinIndex = (u32)((FLOAT_80330e20 * (f32)stepData->m_dataValIndex) / FLOAT_80330e24);
        
        f32 baseValue = *pfVar;
        f32 horizontalScale = (f32)(frameCount * (double)(baseValue * *(f32*)((int)ppvSinTbl + ((sinIndex + 0x4000) & 0xfffc))));
        f32 horizontalX = direction.x * horizontalScale;
        f32 horizontalZ = direction.z * horizontalScale;
        f32 verticalY = (f32)(frameCount * (double)(baseValue * *(f32*)((int)ppvSinTbl + (sinIndex & 0xfffc))) - 
                             (double)(f32)(frameCount * (double)(f32)((double)(FLOAT_80330e28 * (f32)stepData->m_initWOrk) * frameCount)));
        
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
        pppMngStPtr->m_matrix.value[0][3] = newPosition.x;
        pppMngStPtr->m_matrix.value[1][3] = newPosition.y;
        pppMngStPtr->m_matrix.value[2][3] = newPosition.z;
        
        pppSetFpMatrix__FP9_pppMngSt(pppMngSt);
        
        *(u16*)(pfVar + 3) = *(u16*)(pfVar + 3) + 1;
    }
}
