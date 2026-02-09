#include "ffcc/p_chara_viewer.h"

extern "C" int DAT_8032edc0;
extern "C" unsigned char Chara[];
extern "C" unsigned char LightPcs[];
extern "C" unsigned char Memory[];
extern "C" void Destroy__6CCharaFv(void*);
extern "C" void DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(void*, int);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);

namespace {
static void releaseRef(void** slot)
{
    int* ref = (int*)*slot;
    if (ref != 0) {
        int count = ref[1] - 1;
        ref[1] = count;
        if (count == 0) {
            (*(void (**)(void*, int))(*(int*)ref + 8))(ref, 1);
        }
        *slot = 0;
    }
}
} // namespace

/*
 * --INFO--
 * PAL Address: 0x800BEE50
 * PAL Size: 580b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void destroyViewer__9CCharaPcsFv(void* param_1)
{
    unsigned char* p = (unsigned char*)param_1;
    unsigned int i;

    Destroy__6CCharaFv(Chara);
    DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(LightPcs, 0);
    DAT_8032edc0 = 0;

    releaseRef((void**)(p + 0x1A0));

    i = 0;
    do {
        releaseRef((void**)(p + 0x190 + i * 4));
        releaseRef((void**)(p + 0x198 + i * 4));
        releaseRef((void**)(p + 0x2B0 + i * 4));
        i++;
    } while (i < 2);

    releaseRef((void**)(p + 0x2B8));

    i = 0;
    do {
        releaseRef((void**)(p + 0x1B0 + i * 4));
        i++;
    } while (i < 0x40);

    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xCC));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xD0));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(Memory, *(void**)(p + 0xD4));
}
