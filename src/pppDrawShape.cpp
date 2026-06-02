#include "ffcc/pppDrawShape.h"
#include "global.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "dolphin/types.h"
#include "ffcc/ppp_linkage.h"
#include <stddef.h>


typedef struct ShapeRuntimeData {
    u32 shapeDataOffset;
    u32 posDataOffset;
} ShapeRuntimeData;

typedef struct ShapeState {
    u16 value;
    u16 counter;
    u16 currentId;
} ShapeState;

typedef struct ShapeControlData {
    u8 _pad0[4];
    u32 type;
    u32 step;
    u8 _pad2[1];
    u8 blendMode;
    u8 paramE;
    u8 _pad3[1];
    f32 scale;
    u8 param15;
    u8 param14;
} ShapeControlData;

typedef struct ShapePositionData {
    u8 _pad0[8];
    pppCVECTOR color;
} ShapePositionData;

STATIC_ASSERT(offsetof(pppShapeAnimData, m_frameCount) == 0x6);
STATIC_ASSERT(offsetof(pppShapeAnimData, m_frames) == 0x10);
STATIC_ASSERT(offsetof(ShapePositionData, color) == 0x8);

/*
 * --INFO--
 * PAL Address: 0x800654b4
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape(void* pppShape, ShapeControlData* data, void* additionalData){
	_pppPObject* object = (_pppPObject*)pppShape;
	_pppCtrlTable* ctrlTable = (_pppCtrlTable*)additionalData;
	ShapeRuntimeData* runtimeData = (ShapeRuntimeData*)ctrlTable->m_serializedDataOffsets;
	ShapeState* shapeData = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
	ShapePositionData* posData = (ShapePositionData*)(object->m_workArea + runtimeData->posDataOffset);
	s32 type = data->type;
	if (type == 0xFFFF) {
		return;
	}

	pppShapeSt* shapeSt = ppvEnv->m_resourceTables.m_shapeTablePtr[type];
	pppShapeAnimData* shapeSpec = (pppShapeAnimData*)shapeSt->m_animData;
	pppShapeAnimFrame* shape = &shapeSpec->m_frames[shapeData->currentId];
	void* drawShape = (u8*)shapeSpec + shape->m_shapeOffset;

	pppSetDrawEnv(
		&posData->color,
		&object->m_drawMatrix,
		data->scale,
		data->param15,
		data->paramE,
		data->blendMode,
		0,
		1,
		1,
		0
	);

	pppSetBlendMode(data->blendMode);
	pppDrawShp((tagOAN3_SHAPE*)drawShape, ppvEnv->m_materialSetPtr, data->blendMode);
}



/*
 * --INFO--
 * PAL Address: 0x80065588
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCalcShape(void* pppShape, ShapeControlData* data, void* additionalData){
	if (ppvUserStopPartF != 0) {
		return;
	}

	_pppPObject* object = (_pppPObject*)pppShape;
	_pppCtrlTable* ctrlTable = (_pppCtrlTable*)additionalData;
	ShapeRuntimeData* runtimeData = (ShapeRuntimeData*)ctrlTable->m_serializedDataOffsets;
	ShapeState* shapeData = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
	s32 type = data->type;
	if (type == 0xFFFF) {
		return;
	}

	pppShapeSt* shapeSt = ppvEnv->m_resourceTables.m_shapeTablePtr[type];
	pppShapeAnimData* shapeSpec = (pppShapeAnimData*)shapeSt->m_animData;
	pppShapeAnimFrame* shape = &shapeSpec->m_frames[shapeData->counter];

	shapeData->currentId = shapeData->counter;
	shapeData->value = (u16)(shapeData->value + data->step);
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
 * PAL Address: 0x80065654
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShapeConstruct(void* pppShape, void* data)
{
	_pppPObject* object = (_pppPObject*)pppShape;
	_pppCtrlTable* ctrlTable = (_pppCtrlTable*)data;
	ShapeRuntimeData* runtimeData = (ShapeRuntimeData*)ctrlTable->m_serializedDataOffsets;
	ShapeState* targetPtr = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
	
	targetPtr->currentId = 0;
	targetPtr->counter = 0;
	targetPtr->value = 0;
}
