#include "ffcc/pppKeShpTail3X.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>

/*
 * --INFO--
 * PAL Address: 0x80089da0
 * PAL Size: 1516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3X(struct pppKeShpTail3X* obj, struct UnkB* param_2, struct UnkC* param_3)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80089360
 * PAL Size: 2624b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XDraw(struct pppKeShpTail3X* obj, struct UnkB* param_2, struct UnkC* param_3)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80089230
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XCon(struct pppKeShpTail3X* obj, struct UnkC* param_2)
{
    unsigned char* data;
    int i;
    
    // Get data pointer based on Ghidra analysis
    data = (unsigned char*)((int)(&obj->pppPObject + 2));
    
    // Initialize flags to zero
    data[0x1c3] = 0;
    data[0x1c2] = 0;
    
    // Clear some memory areas
    memset(data, 0, 8);
    memset(data + 8, 0, 8);
    memset(data + 0x10, 0, 8);
    memset(data + 0x18, 0, 8);
    memset(data + 0x20, 0, 8);
    memset(data + 0x28, 0, 8);
    
    // Initialize array elements
    for (i = 0; i < 0x1c; i++) {
        *(float*)(data + 0x30 + i * 12) = 1.0f;
        *(float*)(data + 0x34 + i * 12) = 1.0f;  
        *(float*)(data + 0x38 + i * 12) = 1.0f;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8008922c
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppKeShpTail3XDes(void)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void S4ToF32(pppFVECTOR4*, short*)
{
	// TODO
}
