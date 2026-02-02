#include "ffcc/pppPointRAp.h"
#include "ffcc/pppPart.h"
#include "ffcc/math.h"
#include <dolphin/mtx.h>

extern CMath math;

/*
 * --INFO--
 * PAL Address: 0x80060ee4
 * PAL Size: 24b
 */
void pppPointRApCon(_pppMngSt* mngSt, _pppPDataVal* dataVal)
{
    // Based on assembly: lwz r4, 0xc(r4); lwz r4, 0x4(r4); addi r0, r4, 0x81; stbx r5, r3, r0
    u32* dataPtr = (u32*)((char*)dataVal + 0xC);
    u32 innerValue = *(u32*)((char*)*dataPtr + 0x4);
    *((u8*)mngSt + innerValue + 0x81) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80060d20
 * PAL Size: 452b
 */
void pppPointRAp(_pppMngSt* mngSt, _pppPDataVal* dataVal)
{
    // TODO: Complex particle effect function
    // Stub implementation - needs reverse engineering from assembly
}