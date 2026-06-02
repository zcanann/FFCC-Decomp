#include "ffcc/pppDrawShape2.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "dolphin/types.h"
#include "ffcc/ppp_linkage.h"
#include <stddef.h>

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
    u8 _pad5[3];
} ShapeSpecEntry;

typedef struct ShapeSpec {
    u8 _pad0[6];
    s16 count;
    u8 _pad8[8];
    ShapeSpecEntry entries[1];
} ShapeSpec;

typedef struct ShapePositionData {
    u8 _pad0[8];
    pppCVECTOR color;
} ShapePositionData;

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

STATIC_ASSERT(sizeof(ShapeSpecEntry) == 8);
STATIC_ASSERT(offsetof(ShapeSpec, count) == 0x6);
STATIC_ASSERT(offsetof(ShapeSpec, entries) == 0x10);
STATIC_ASSERT(offsetof(ShapePositionData, color) == 0x8);

/*
 * --INFO--
 * PAL Address: 0x800da93c  
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape2(void* param1, ShapeControlData* param2, void* param3){
    _pppPObject* object = (_pppPObject*)param1;
    _pppCtrlTable* ctrlTable = (_pppCtrlTable*)param3;
    ShapeRuntimeData* runtimeData = (ShapeRuntimeData*)ctrlTable->m_serializedDataOffsets;
    ShapeState* shapeData = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
    ShapePositionData* posData = (ShapePositionData*)(object->m_workArea + runtimeData->posDataOffset);
    s32 type = param2->type;

    if (type == 0xFFFF) {
        return;
    }

    pppShapeSt* shapeSt = ppvEnv->m_resourceTables.m_shapeTablePtr[type];
    ShapeSpec* shapeSpec = (ShapeSpec*)shapeSt->m_animData;
    ShapeSpecEntry* shape = &shapeSpec->entries[shapeData->currentId];
    void* drawShape = (u8*)shapeSpec + shape->offset;

    pppSetDrawEnv(
        &posData->color,
        &object->m_drawMatrix,
        param2->scale,
        param2->param15,
        param2->paramE,
        param2->blendMode,
        0,
        param2->param14,
        1,
        0
    );

    pppSetBlendMode(param2->blendMode);
    pppDrawShp((tagOAN3_SHAPE*)drawShape, ppvEnv->m_materialSetPtr, param2->blendMode);
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
void pppCalcShape2(void* param1, ShapeControlData* param2, void* param3){
    if (gPppCalcDisabled != 0) {
        return;
    }

    _pppPObject* object = (_pppPObject*)param1;
    _pppCtrlTable* ctrlTable = (_pppCtrlTable*)param3;
    ShapeRuntimeData* runtimeData = (ShapeRuntimeData*)ctrlTable->m_serializedDataOffsets;
    ShapeState* shapeData = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
    s32 type = param2->type;

    if (type == 0xFFFF) {
        return;
    }

    pppShapeSt* shapeSt = ppvEnv->m_resourceTables.m_shapeTablePtr[type];
    ShapeSpec* shapeSpec = (ShapeSpec*)shapeSt->m_animData;
    ShapeSpecEntry* shape = &shapeSpec->entries[shapeData->counter];

    shapeData->currentId = shapeData->counter;
    shapeData->value = (u16)(shapeData->value + param2->step);
    s32 value = shapeData->value;
    s32 maxValue = shape->maxValue;

    if (value < maxValue) {
        return;
    }
    shapeData->value = (u16)(value - maxValue);

    shapeData->counter++;
    if (shapeData->counter < shapeSpec->count) {
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
 * PAL Address: 0x800daadc
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape2Construct(void* param1, void* param2)
{
    _pppPObject* object = (_pppPObject*)param1;
    _pppCtrlTable* ctrlTable = (_pppCtrlTable*)param2;
    ShapeRuntimeData* data = (ShapeRuntimeData*)ctrlTable->m_serializedDataOffsets;
    ShapeState* shapeData = (ShapeState*)(object->m_workArea + data->shapeDataOffset);

    shapeData->currentId = 0;
    shapeData->counter = 0;
    shapeData->value = 0;
}
