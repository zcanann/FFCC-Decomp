#include "ffcc/pppDrawShape2.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "dolphin/types.h"
#include "ffcc/ppp_linkage.h"
#include <stddef.h>

STATIC_ASSERT(offsetof(pppShapeAnimData, m_frameCount) == 0x6);
STATIC_ASSERT(offsetof(pppShapeAnimData, m_frames) == 0x10);
STATIC_ASSERT(offsetof(ShapeRuntimeData, shapeDataOffset) == 0x0);
STATIC_ASSERT(offsetof(ShapeRuntimeData, posDataOffset) == 0x4);
STATIC_ASSERT(offsetof(ShapePositionData, color) == 0x8);

static inline ShapeRuntimeData* GetDrawShape2RuntimeData(_pppCtrlTable* ctrlTable)
{
    return reinterpret_cast<ShapeRuntimeData*>(ctrlTable->m_serializedDataOffsets);
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
void pppDrawShape2(_pppPObject* object, Shape2ControlData* controlData, _pppCtrlTable* ctrlTable){
    ShapeRuntimeData* runtimeData = GetDrawShape2RuntimeData(ctrlTable);
    ShapeState* shapeData = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
    ShapePositionData* posData = (ShapePositionData*)(object->m_workArea + runtimeData->posDataOffset);
    s32 type = controlData->type;

    if (type == 0xFFFF) {
        return;
    }

    pppShapeSt* shapeSt = ppvEnv->m_shapeTablePtr[type];
    pppShapeAnimData* shapeSpec = (pppShapeAnimData*)shapeSt->m_animData;
    pppShapeAnimFrame* shape = &shapeSpec->m_frames[shapeData->currentId];
    void* drawShape = (u8*)shapeSpec + shape->m_shapeOffset;

    pppSetDrawEnv(
        &posData->color,
        &object->m_drawMatrix,
        controlData->scale,
        controlData->param15,
        controlData->paramE,
        controlData->blendMode,
        0,
        controlData->param14,
        1,
        0
    );

    pppSetBlendMode(controlData->blendMode);
    pppDrawShp((tagOAN3_SHAPE*)drawShape, ppvEnv->m_materialSetPtr, controlData->blendMode);
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
void pppCalcShape2(_pppPObject* object, Shape2ControlData* controlData, _pppCtrlTable* ctrlTable){
    if (ppvUserStopPartF != 0) {
        return;
    }

    ShapeRuntimeData* runtimeData = GetDrawShape2RuntimeData(ctrlTable);
    ShapeState* shapeData = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
    s32 type = controlData->type;

    if (type == 0xFFFF) {
        return;
    }

    pppShapeSt* shapeSt = ppvEnv->m_shapeTablePtr[type];
    pppShapeAnimData* shapeSpec = (pppShapeAnimData*)shapeSt->m_animData;
    pppShapeAnimFrame* shape = &shapeSpec->m_frames[shapeData->counter];

    shapeData->currentId = shapeData->counter;
    shapeData->value = (u16)(shapeData->value + controlData->step);
    s32 value = shapeData->value;
    s32 maxValue = shape->m_duration;

    if (value < maxValue) {
        return;
    }
    shapeData->value = (u16)(value - maxValue);

    shapeData->counter++;
    if (shapeData->counter < shapeSpec->m_frameCount) {
        return;
    }

    if ((shape->m_flags & 0x80) != 0) {
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
void pppDrawShape2Construct(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
    ShapeRuntimeData* data = GetDrawShape2RuntimeData(ctrlTable);
    ShapeState* shapeData = (ShapeState*)(object->m_workArea + data->shapeDataOffset);

    shapeData->currentId = 0;
    shapeData->counter = 0;
    shapeData->value = 0;
}
