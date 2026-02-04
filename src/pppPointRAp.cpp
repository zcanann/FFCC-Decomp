#include "ffcc/pppPointRAp.h"
#include "ffcc/pppPart.h"
#include "ffcc/math.h"
#include "ffcc/pppsintbl.h"
#include <dolphin/mtx.h>

extern CMath math;

/*
 * --INFO--
 * PAL Address: 0x80060ee4
 * PAL Size: 24b
 */
void pppPointRApCon(_pppMngSt* mngSt, _pppPDataVal* dataVal)
{
    u32* dataPtr = (u32*)((char*)dataVal + 0xC);
    u32 offset = *(u32*)((char*)*dataPtr + 0x4) + 0x81;
    *((u8*)mngSt + offset) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80060d20
 * PAL Size: 452b
 */
void pppPointRAp(_pppMngSt* mngSt, _pppPDataVal* dataVal)
{
    extern int lbl_8032ED70;
    
    if (lbl_8032ED70 != 0) {
        return;
    }
    
    u32 particleId = *(u32*)((char*)*(u32**)((char*)dataVal + 0xC) + 0x4);
    u8* particleBase = (u8*)mngSt + particleId + 0x80;
    
    if (particleBase[1] == 0) {
        u32 checkValue = *(u32*)((char*)dataVal + 0xC);
        if ((checkValue + 0x10000) != 0xFFFF) {
            pppCreatePObject(mngSt, dataVal);
            
            math.RandF();
            f32 angleRandom = 0.5f; // Placeholder - RandF result accessed elsewhere
            angleRandom = angleRandom * 65536.0f;
            s32 angleIndex = (s32)angleRandom & 0xFFFF;
            
            f32 posScale = *(f32*)((char*)dataVal + 0x4);
            f32 sinValue = pppTrigTable[angleIndex & 0x3FFF];
            f32 cosValue = pppTrigTable[(angleIndex + 0x1000) & 0x3FFF];
            
            sinValue *= posScale;
            cosValue *= posScale;
            
            math.RandF();
            f32 velRandom = 0.3f; // Placeholder - RandF result accessed elsewhere  
            velRandom = velRandom * 65536.0f;
            s32 velAngleIndex = (s32)velRandom & 0xFFFF;
            
            f32 velScale = *(f32*)((char*)dataVal + 0x8);
            f32 velSin = pppTrigTable[velAngleIndex & 0x3FFF];
            f32 velCos = pppTrigTable[(velAngleIndex + 0x1000) & 0x3FFF];
            
            velSin *= velScale;
            velCos *= velScale;
            
            u8 lifetime = *(u8*)((char*)dataVal + 0x1C);
            particleBase[1] = lifetime;
        }
    }
    
    if (particleBase[1] > 0) {
        particleBase[1]--;
    }
}