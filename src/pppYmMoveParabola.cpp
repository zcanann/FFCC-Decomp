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
extern double DOUBLE_80330e30; // Double constant for counter conversion
extern int ppvSinTbl;         // Sin table base
extern int DAT_8032ed70;      // Global flag
extern u8* lbl_8032ED50;

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
    u8* pppMngSt = lbl_8032ED50;
    f32* pfVar = (f32*)((u8*)basePtr + *dataPtr->m_serializedDataOffsets + 0x80);

    f32 fVar2 = FLOAT_80330e1c;
    pfVar[2] = FLOAT_80330e1c;
    pfVar[1] = fVar2;
    *pfVar = fVar2;
    *(u16*)(pfVar + 3) = 1;

    if (Game.game.m_currentSceneId == 7) {
        Vec matrixPos;
        Vec basePos;
        Vec resultPos;

        pppCopyVector(*(Vec*)(pfVar + 4), *(Vec*)(pppMngSt + 0x58));

        matrixPos.x = *(f32*)(pppMngSt + 0x84);
        matrixPos.y = *(f32*)(pppMngSt + 0x94);
        matrixPos.z = *(f32*)(pppMngSt + 0xA4);

        basePos.x = pfVar[4];
        basePos.y = pfVar[5];
        basePos.z = pfVar[6];

        pppAddVector(*(Vec*)(pfVar + 4), basePos, matrixPos);

        resultPos.x = pfVar[4];
        resultPos.y = pfVar[5];
        resultPos.z = pfVar[6];
        pppCopyVector(*(Vec*)(pppMngSt + 0x68), resultPos);
        *(f32*)(pppMngSt + 0x68) += FLOAT_80330e18;
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
    if (DAT_8032ed70 == 0) {
        u8* pppMngSt = lbl_8032ED50;
        f32* pfVar = (f32*)((u8*)basePtr + *offsetData->m_serializedDataOffsets + 0x80);
        
        // Update velocity and position
        pfVar[1] = pfVar[1] + pfVar[2];
        *pfVar = *pfVar + pfVar[1];
        
        if (stepData->m_graphId == basePtr->m_graphId) {
            *pfVar = *pfVar + stepData->m_stepValue;
            pfVar[1] = pfVar[1] + stepData->m_arg3;
            pfVar[2] = pfVar[2] + stepData->m_payload;
        }
        
        // Convert counter to double for frame calculations
        u16 counter = *(u16*)(pfVar + 3);
        union {
            u64 u;
            double d;
        } frameBits;
        frameBits.u = ((u64)0x43300000 << 32) | (u64)counter;
        double frameCount = (double)(f32)(frameBits.d - DOUBLE_80330e30);
        
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
        pppNormalize(direction, tempDir);
        
        // Trigonometric parabolic motion calculations
        s32 sinIndex = (s32)((FLOAT_80330e20 * stepData->m_dataValIndex) / FLOAT_80330e24);
        
        f32 baseValue = *pfVar;
        f32 horizontalScale = (f32)(frameCount * (double)(baseValue * *(f32*)((int)ppvSinTbl + ((sinIndex + 0x4000) & 0xfffc))));
        f32 horizontalX = direction.x * horizontalScale;
        f32 horizontalZ = direction.z * horizontalScale;
        f32 verticalY = (f32)(frameCount * (double)(baseValue * *(f32*)((int)ppvSinTbl + (sinIndex & 0xfffc))) -
                             (double)(f32)(frameCount * (double)(f32)((double)(FLOAT_80330e28 * stepData->m_initWOrk) * frameCount)));
        
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
            pppAddVector(newPosition, offset, basePos);
        } else {
            Vec basePos;
            basePos.x = *(f32*)((u8*)pppMngSt + 0x58);
            basePos.y = *(f32*)((u8*)pppMngSt + 0x5c);
            basePos.z = *(f32*)((u8*)pppMngSt + 0x60);
            Vec offset;
            offset.x = horizontalX;
            offset.y = verticalY;
            offset.z = horizontalZ;
            pppAddVector(newPosition, offset, basePos);
        }

        pppCopyVector(*(Vec*)((u8*)pppMngSt + 0x48), *(Vec*)((u8*)pppMngSt + 0x8));
        pppCopyVector(*(Vec*)((u8*)pppMngSt + 0x8), newPosition);
        
        // Update matrix with new position
        *(f32*)(pppMngSt + 0x84) = newPosition.x;
        *(f32*)(pppMngSt + 0x94) = newPosition.y;
        *(f32*)(pppMngSt + 0xA4) = newPosition.z;

        pppSetFpMatrix((_pppMngSt*)pppMngSt);
        
        *(u16*)(pfVar + 3) = *(u16*)(pfVar + 3) + 1;
    }
}
