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

/*
 * --INFO--
 * PAL Address: 0x800d4558
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmMoveParabola(struct pppYmMoveParabola* basePtr, struct UnkC* dataPtr)
{
    _pppMngSt* pppMngSt = pppMngStPtr;
    f32 zero = FLOAT_80330e1c;
    f32* pfVar = (f32*)((u8*)&basePtr->field0_0x0 + 8 + *dataPtr->m_serializedDataOffsets);
    
    // Initialize velocity components
    pfVar[2] = FLOAT_80330e1c;
    pfVar[1] = zero;
    *pfVar = zero;
    *(u16*)(pfVar + 3) = 1;
    
    // For now, simplified implementation without unavailable struct members
    if (Game.game.m_currentSceneId == 7) {
        // Initialize position data from matrix
        f32 matrixX = pppMngStPtr->m_matrix.value[0][3];
        f32 matrixY = pppMngStPtr->m_matrix.value[1][3];
        f32 matrixZ = pppMngStPtr->m_matrix.value[2][3];
        
        pfVar[4] = matrixX;
        pfVar[5] = matrixY;
        pfVar[6] = matrixZ;
        
        pfVar[4] = pfVar[4] + FLOAT_80330e18;
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
void pppFrameYmMoveParabola(struct pppYmMoveParabola* basePtr, struct UnkB* stepData, struct UnkC* offsetData)
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
        
        // Convert counter to double for frame calculations
        u16 counter = *(u16*)(pfVar + 3);
        double frameCount = (double)(f32)((double)((u32)counter | 0x43300000) - DOUBLE_80330e30);
        
        Vec direction;
        if (Game.game.m_currentSceneId == 7) {
            direction.y = FLOAT_80330e1c;
            direction.x = FLOAT_80330e18;
            direction.z = FLOAT_80330e1c;
        } else {
            // Simplified direction calculation using current position
            direction.x = pppMngSt->m_position.x;
            direction.y = pppMngSt->m_position.y;
            direction.z = pppMngSt->m_position.z;
        }
        
        Vec normalizedDir;
        pppNormalize(normalizedDir, direction);
        
        // Trigonometric parabolic motion calculations
        u32 sinIndex = (u32)((FLOAT_80330e20 * (f32)stepData->m_dataValIndex) / FLOAT_80330e24);
        
        f32 horizontalScale = (f32)(frameCount * (double)(*pfVar * *(f32*)((int)ppvSinTbl + ((sinIndex + 0x4000) & 0xfffc))));
        f32 horizontalX = normalizedDir.x * horizontalScale;
        f32 horizontalZ = normalizedDir.z * horizontalScale;
        f32 verticalY = (f32)(frameCount * (double)(*pfVar * *(f32*)((int)ppvSinTbl + (sinIndex & 0xfffc))) - 
                             (double)(f32)(frameCount * (double)(f32)((double)(FLOAT_80330e28 * (f32)stepData->m_initWOrk) * frameCount)));
        
        Vec newPosition;
        if (Game.game.m_currentSceneId == 7) {
            f32 baseX = pfVar[4];
            f32 baseY = pfVar[5];
            f32 baseZ = pfVar[6];
            Vec offset = {horizontalX, verticalY, horizontalZ};
            Vec base = {baseX, baseY, baseZ};
            pppAddVector(newPosition, offset, base);
        } else {
            f32 posX = pppMngSt->m_position.x;
            f32 posY = pppMngSt->m_position.y;
            f32 posZ = pppMngSt->m_position.z;
            Vec offset = {horizontalX, verticalY, horizontalZ};
            Vec base = {posX, posY, posZ};
            pppAddVector(newPosition, offset, base);
        }
        
        // Update matrix with new position
        pppMngStPtr->m_matrix.value[0][3] = newPosition.x;
        pppMngStPtr->m_matrix.value[1][3] = newPosition.y;
        pppMngStPtr->m_matrix.value[2][3] = newPosition.z;
        
        pppSetFpMatrix(pppMngSt);
        
        *(u16*)(pfVar + 3) = *(u16*)(pfVar + 3) + 1;
    }
}