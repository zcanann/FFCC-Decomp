#include "ffcc/pppEraseCharaParts.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"

#include <dolphin/gx.h>

extern CMaterialMan MaterialMan;
extern int lbl_8032ED70;
extern unsigned char* lbl_8032ED50;

extern "C" {
void* GetCharaHandlePtr__FP8CGObjectl(void* obj, long index);
int GetCharaModelPtr__FPQ29CCharaPcs7CHandle(void* handle);
void DCFlushRange(void* ptr, unsigned long size);
}

/*
 * --INFO--
 * PAL Address: 0x8010400C
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void EraseCharaParts_DrawMeshDLCallback(CChara::CModel* model, void* param_2, void* param_3,
                                        int meshIndex, int param_5, float (*) [4])
{
    struct MeshData {
        u8 pad[0x50];
        void* displayLists;
    };
    struct Mesh {
        u8 pad[8];
        MeshData* data;
        u8 tail[8];
    };
    struct ModelData {
        u8 pad[0x24];
        CMaterialSet* materialSet;
    };
    struct DisplayList {
        void* data;
        u32 size;
        u16 material;
    };

    DisplayList* displayList = ((DisplayList*)(((Mesh*)((char*)model + 0xAC))[meshIndex].data->displayLists)) + param_5;
    ModelData* modelData = *(ModelData**)((char*)model + 0xA4);

    MaterialMan.SetMaterial(modelData->materialSet, displayList->material, 0, (_GXTevScale)0);

    if ((((UnkB*)param_3)->m_meshIndex != -1) && (meshIndex == ((UnkB*)param_3)->m_meshIndex)) {
        GXSetArray((GXAttr)0xB, param_2, 4);
    }

    GXCallDisplayList(displayList->data, displayList->size);
}

/*
 * --INFO--
 * PAL Address: 0x80103FA8
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, UnkC* param_2)
{
    s32* serializedDataOffsets;
    void* handle;
    int model;
    u8* colorPtr;
    void* gObject;

    serializedDataOffsets = *(s32**)((u8*)param_2 + 0xC);
    colorPtr = (u8*)pppEraseCharaParts + 0x80 + serializedDataOffsets[1];
    gObject = *(void**)(lbl_8032ED50 + 0xD8);
    colorPtr[0] = 0x80;
    colorPtr[1] = 0x80;
    colorPtr[2] = 0x80;
    colorPtr[3] = 0x80;

    handle = GetCharaHandlePtr__FP8CGObjectl(gObject, 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(void (**)(CChara::CModel*, void*, void*, int, int, float (*)[4]))(model + 0xFC) =
        EraseCharaParts_DrawMeshDLCallback;
}

/*
 * --INFO--
 * PAL Address: 0x80103F68
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructEraseCharaParts(void)
{
    void* handle;
    int model;

    handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)(lbl_8032ED50 + 0xD8), 0);
    model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
    *(void**)(model + 0xE4) = 0;
    *(void**)(model + 0xE8) = 0;
    *(void**)(model + 0xFC) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80103EC0
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameEraseCharaParts(pppEraseCharaParts* pppEraseCharaParts, UnkB* param_2, UnkC* param_3)
{
    void* handle;
    int model;
    s32* offsets;
    int colorIndex;
    u8* dstColor;
    u8* srcColor;

    if (lbl_8032ED70 == 0) {
        offsets = param_3->m_serializedDataOffsets;
        colorIndex = offsets[0];
        dstColor = (u8*)((char*)pppEraseCharaParts + 2 + offsets[1]);
        srcColor = (u8*)((char*)pppEraseCharaParts + 0x88 + colorIndex);
        handle = GetCharaHandlePtr__FP8CGObjectl(*(void**)((char*)pppMngStPtr + 0x8), 0);
        model = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);

        *(u8**)(model + 0xE4) = dstColor;
        *(UnkB**)(model + 0xE8) = param_2;

        dstColor[0] = srcColor[0];
        dstColor[1] = srcColor[1];
        dstColor[2] = srcColor[2];
        dstColor[3] = srcColor[3];

        DCFlushRange(dstColor, 4);
    }
}
