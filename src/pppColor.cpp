#include "ffcc/pppColor.h"
#include "types.h"

/*
 * --INFO--
 * PAL Address: 0x8005FFB4
 * PAL Size: 416b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColor(void* param1, void* param2, void* param3)
{
    struct PppColorOffsets {
        u8 pad[0xC];
        s32* m_serializedDataOffsets;
    };

    PppColorOffsets* offsets = (PppColorOffsets*)param3;
    _pppColorWork* work = (_pppColorWork*)((u8*)param1 + offsets->m_serializedDataOffsets[0] + 0x80);

    if (lbl_8032ED70 == 0) {
        s32 id1 = *(s32*)param2;
        s32 id2 = *(s32*)((u8*)param1 + 0xC);

        if (id1 == id2) {
            s16* src_colors = (s16*)((u8*)param2 + 8);
            work->r += src_colors[0];
            work->g += src_colors[1];
            work->b += src_colors[2];
            work->a += src_colors[3];
        }

        if (((u8*)lbl_8032ED50)[0xef] != 0) {
            work->result.r = (u8)((float)(work->r >> 7) * ((float*)lbl_8032ED50)[14]);
            work->result.g = (u8)((float)(work->g >> 7) * ((float*)lbl_8032ED50)[15]);
            work->result.b = (u8)((float)(work->b >> 7) * ((float*)lbl_8032ED50)[16]);
            work->result.a = (u8)((float)(work->a >> 7) * ((float*)lbl_8032ED50)[17]);
            return;
        }
    }
    
    work->result.r = (u8)(work->r >> 7);
    work->result.g = (u8)(work->g >> 7);
    work->result.b = (u8)(work->b >> 7);
    work->result.a = (u8)(work->a >> 7);
}

/*
 * --INFO--
 * PAL Address: 0x8005FF8C  
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppColorCon(void* param1, void* param2)
{
    struct PppColorOffsets {
        u8 pad[0xC];
        s32* m_serializedDataOffsets;
    };

    PppColorOffsets* offsets = (PppColorOffsets*)param2;
    _pppColorWork* work = (_pppColorWork*)((u8*)param1 + offsets->m_serializedDataOffsets[0] + 0x80);
    
    work->a = 0;
    work->b = 0;
    work->g = 0;
    work->r = 0;
}
