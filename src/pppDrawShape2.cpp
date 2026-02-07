#include "ffcc/pppDrawShape2.h"
#include "dolphin/types.h"

extern int lbl_8032ED70;
extern void* lbl_8032ED54;

extern void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
extern void pppSetBlendMode__FUc(unsigned char);
extern void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(void*, void*, unsigned char);

typedef struct ShapeState {
    s16 value;
    s16 counter;
    s16 currentId;
} ShapeState;

typedef struct ShapeRuntimeData {
    u32 shapeDataOffset;
    u32 posDataOffset;
} ShapeRuntimeData;

typedef struct ShapeSpecEntry {
    s16 _unk0;
    s16 maxValue;
    u8 flags;
} ShapeSpecEntry;

typedef struct ShapeControlData {
    u8 _pad0[4];
    s16 type;
    u8 _pad1[2];
    s32 step;
    u8 _pad2[1];
    u8 blendMode;
    u8 alpha;
    u8 _pad3[1];
    f32 scale;
    u8 _pad4[4];
    u8 red;
    u8 green;
} ShapeControlData;

/*
 * --INFO--
 * PAL Address: 0x800daadc
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape2Construct(void* param1, void* param2)
{
    ShapeRuntimeData* data = *(ShapeRuntimeData**)((u8*)param2 + 0xC);
    ShapeState* shapeData = (ShapeState*)((u8*)param1 + data->shapeDataOffset + 0x80);

    shapeData->currentId = 0;
    shapeData->counter = 0;
    shapeData->value = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800daa10
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCalcShape2(void* param1, void* param2, void* param3)
{
    ShapeState* shapeData;
    ShapeRuntimeData* runtimeData;
    ShapeControlData* controlData;
    s16 currentId;
    s16 value;
    s16 maxValue;
    s16 counter;
    void* shapeSpec;
    ShapeSpecEntry* currentShape;

    if (lbl_8032ED70 != 0) {
        return;
    }

    runtimeData = *(ShapeRuntimeData**)((u8*)param3 + 0xC);
    controlData = (ShapeControlData*)param2;
    shapeData = (ShapeState*)((u8*)param1 + runtimeData->shapeDataOffset + 0x80);

    if ((u16)controlData->type == 0xFFFF) {
        return;
    }

    shapeSpec = ((void**)*(void**)((u8*)lbl_8032ED54 + 0xC))[controlData->type];

    currentId = shapeData->counter;
    shapeData->currentId = currentId;
    currentShape = (ShapeSpecEntry*)((u8*)shapeSpec + ((u32)currentId << 3) + 0x10);

    value = shapeData->value + controlData->step;
    shapeData->value = value;

    maxValue = currentShape->maxValue;
    if (value >= maxValue) {
        value -= maxValue;
        shapeData->value = value;
    }

    counter = shapeData->counter + 1;
    shapeData->counter = counter;

    if (counter >= *(s16*)((u8*)shapeSpec + 0x6)) {
        if ((currentShape->flags & 0x80) != 0) {
            shapeData->value = 0;
            shapeData->counter = 0;
        } else {
            shapeData->value = 0;
            shapeData->counter = currentId;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800da93c  
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape2(void* param1, void* param2, void* param3)
{
    ShapeRuntimeData* runtimeData = *(ShapeRuntimeData**)((u8*)param3 + 0xC);
    ShapeControlData* controlData = (ShapeControlData*)param2;
    ShapeState* shapeData = (ShapeState*)((u8*)param1 + runtimeData->shapeDataOffset + 0x80);
    void* posData = (u8*)param1 + runtimeData->posDataOffset + 0x80;
    s16 type = controlData->type;

    if ((u16)type == 0xFFFF) {
        return;
    }

    void* shapeSpec = ((void**)*(void**)((u8*)lbl_8032ED54 + 0xC))[type];
    void* currentShape = (u8*)shapeSpec + ((u32)shapeData->currentId << 3) + 0x10;
    void* materialData = *(void**)((u8*)lbl_8032ED54 + 0x4);

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        posData,
        (u8*)param1 + 0x40,
        controlData->scale,
        controlData->blendMode,
        controlData->alpha,
        controlData->blendMode,
        controlData->red,
        controlData->green,
        0,
        0
    );

    pppSetBlendMode__FUc(controlData->blendMode);

    pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(currentShape, materialData, controlData->blendMode);
}
