#include "ffcc/pppDrawShape.h"
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
STATIC_ASSERT(offsetof(VColor, m_color) == 0x8);

static inline ShapeRuntimeData* GetDrawShapeRuntimeData(_pppCtrlTable* ctrlTable)
{
	return reinterpret_cast<ShapeRuntimeData*>(ctrlTable->m_serializedDataOffsets);
}

/*
 * --INFO--
 * PAL Address: 0x800654b4
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape(_pppPObject* object, ShapeControlData* data, _pppCtrlTable* ctrlTable){
	ShapeRuntimeData* runtimeData = GetDrawShapeRuntimeData(ctrlTable);
	ShapeState* shapeData = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
	VColor* posData = (VColor*)(object->m_workArea + runtimeData->posDataOffset);
	s32 type = data->type;
	if (type == 0xFFFF) {
		return;
	}

	pppShapeSt* shapeSt = ppvEnv->m_shapeTablePtr[type];
	pppShapeAnimData* shapeSpec = (pppShapeAnimData*)shapeSt->m_animData;
	pppShapeAnimFrame* shape = &shapeSpec->m_frames[shapeData->currentId];
	void* drawShape = (u8*)shapeSpec + shape->m_shapeOffset;

	pppSetDrawEnv(
		&posData->m_color,
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
void pppCalcShape(_pppPObject* object, ShapeControlData* data, _pppCtrlTable* ctrlTable){
	if (ppvUserStopPartF != 0) {
		return;
	}

	ShapeRuntimeData* runtimeData = GetDrawShapeRuntimeData(ctrlTable);
	ShapeState* shapeData = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);
	s32 type = data->type;
	if (type == 0xFFFF) {
		return;
	}

	pppShapeSt* shapeSt = ppvEnv->m_shapeTablePtr[type];
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
void pppDrawShapeConstruct(_pppPObject* object, _pppCtrlTable* ctrlTable)
{
	ShapeRuntimeData* runtimeData = GetDrawShapeRuntimeData(ctrlTable);
	ShapeState* targetPtr = (ShapeState*)(object->m_workArea + runtimeData->shapeDataOffset);

	targetPtr->currentId = 0;
	targetPtr->counter = 0;
	targetPtr->value = 0;
}
