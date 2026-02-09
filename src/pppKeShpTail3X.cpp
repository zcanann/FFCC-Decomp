#include "ffcc/pppKeShpTail3X.h"
#include "ffcc/partMng.h"
#include <dolphin/mtx.h>
#include <dolphin/os.h>
#include <string.h>

extern "C" int rand(void);

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
    struct KeShpTail3XConArg {
        char pad[0xc];
        int* m_serializedDataOffsets;
    };
    unsigned char* work;
    unsigned char* anglePtr;
    int i;

    work = (unsigned char*)((char*)&obj->pppPObject + 8 + *(reinterpret_cast<KeShpTail3XConArg*>(param_2)->m_serializedDataOffsets));
    work[0x1c3] = 0;
    work[0x1c2] = 0;
    *(u16*)(work + 0x1bc) = 0;
    *(u32*)(work + 0x1b8) = 0;
    *(u16*)(work + 0x1c0) = (u16)rand();
    memset(work, 0, 8);
    memset(work + 8, 0, 8);
    memset(work + 0x10, 0, 8);
    memset(work + 0x18, 0, 8);
    memset(work + 0x20, 0, 8);
    memset(work + 0x28, 0, 8);

    anglePtr = work;
    i = 0;
    do {
        *(s16*)(anglePtr + 0x180) = (s16)(rand() % 0x168);
        anglePtr += 2;
        *(float*)(work + 0x38) = 1.0f;
        *(float*)(work + 0x34) = 1.0f;
        *(float*)(work + 0x30) = 1.0f;
        work += 0xc;
        i++;
    } while (i < 0x1c);
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
