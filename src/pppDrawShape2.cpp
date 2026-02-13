#include "ffcc/pppDrawShape2.h"
#include "dolphin/types.h"

extern int lbl_8032ED70;
extern void* lbl_8032ED54;

extern void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
extern void pppSetBlendMode__FUc(unsigned char);
extern void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(void*, void*, unsigned char);

typedef struct ShapeState {
    u16 value;
    u16 counter;
    u16 currentId;
} ShapeState;

typedef struct ShapeRuntimeData {
    u32 shapeDataOffset;
    u32 posDataOffset;
} ShapeRuntimeData;

typedef struct ShapeSpecEntry {
    s16 offset;
    s16 maxValue;
    u8 flags;
} ShapeSpecEntry;

typedef struct ShapeControlData {
    u8 _pad0[4];
    u32 type;
    u32 step;
    u8 _pad2[1];
    u8 blendMode;
    u8 paramE;
    u8 _pad3[1];
    f32 scale;
    u8 param14;
    u8 param15;
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
    if (lbl_8032ED70 != 0) {
        return;
    }

    ShapeRuntimeData* runtimeData = *(ShapeRuntimeData**)((u8*)param3 + 0xC);
    ShapeControlData* controlData = (ShapeControlData*)param2;
    ShapeState* shapeData = (ShapeState*)((u8*)param1 + runtimeData->shapeDataOffset + 0x80);
    s16 type = *(s16*)((u8*)controlData + 0x4);

    if (type == -1) {
        return;
    }

    void** shapeTables = *(void***)((u8*)lbl_8032ED54 + 0xC);
    void* shapeSpec = *(void**)((u8*)shapeTables + ((u16)type << 2));
    ShapeSpecEntry* shape = (ShapeSpecEntry*)((u8*)shapeSpec + ((u32)shapeData->counter << 3) + 0x10);

    shapeData->currentId = shapeData->counter;
    shapeData->value = (u16)(shapeData->value + controlData->step);
    if (shapeData->value < shape->maxValue) {
        return;
    }
    shapeData->value = (u16)(shapeData->value - shape->maxValue);

    shapeData->counter++;
    if (shapeData->counter < *(s16*)((u8*)shapeSpec + 0x6)) {
        return;
    }

    if ((shape->flags & 0x80) != 0) {
        shapeData->counter = 0;
        shapeData->value = 0;
        return;
    }

    shapeData->value = 0;
    shapeData->counter--;
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
    u32 type = controlData->type;

    if (type == 0xFFFF) {
        return;
    }

    void** shapeTables = *(void***)((u8*)lbl_8032ED54 + 0xC);
    void* shapeSpec = *(void**)((u8*)shapeTables + (type << 2));
    ShapeSpecEntry* shape = (ShapeSpecEntry*)((u8*)shapeSpec + ((u32)shapeData->currentId << 3) + 0x10);
    void* drawShape = (u8*)shapeSpec + shape->offset;

    pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
        (u8*)posData + 8,
        (u8*)param1 + 0x40,
        controlData->scale,
        controlData->param15,
        controlData->paramE,
        controlData->blendMode,
        0,
        controlData->param14,
        1,
        0
    );

    pppSetBlendMode__FUc(controlData->blendMode);
    pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(drawShape, *(void**)((u8*)lbl_8032ED54 + 0x4), controlData->blendMode);
}
