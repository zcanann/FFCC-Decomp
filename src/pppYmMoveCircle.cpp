#include "ffcc/pppYmMoveCircle.h"
#include "ffcc/pppPart.h"
#include "types.h"
#include "dolphin/mtx.h"
#include <math.h>

/*
 * --INFO--
 * PAL Address: 0x800d183c
 * PAL Size: 300b
 */
void pppConstructYmMoveCircle(void)
{
    Vec temp1, temp2;
    float angle;
    
    // PSVECSubtract call observed in assembly
    PSVECSubtract(&temp1, &temp2, &temp1);
    
    // PSVECNormalize call observed
    PSVECNormalize(&temp1, &temp1);
    
    // PSVECDotProduct and acos calls for angle calculation
    angle = PSVECDotProduct(&temp1, &temp2);
    angle = acos(angle);
}

/*
 * --INFO--
 * PAL Address: 0x800d160c  
 * PAL Size: 560b
 */
void pppFrameYmMoveCircle(void)
{
    Vec position;
    float angleStep;
    
    // Vector operations observed in assembly
    pppCopyVector(position, position);
    
    // Floating point math for circular movement
    position.x += angleStep;
    position.y += angleStep; 
    position.z += angleStep;
}