#include "ffcc/pppDrawShape.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppShape.h"
#include "dolphin/types.h"

extern int lbl_8032ED70;
extern void* lbl_8032ED54;

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
    s16 type;
    u16 _padType;
    u32 step;
    u8 _pad2[1];
    u8 blendMode;
    u8 paramE;
    u8 _pad3[1];
    f32 scale;
    u8 param14;
    u8 param15;
} ShapeControlData;

typedef struct ShapeSpecEntry {
    s16 offset;
    s16 maxValue;
    u8 flags;
} ShapeSpecEntry;

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
	void** dataPtr = (void**)data;
	void* basePtr = dataPtr[3];
	void* shapePtr = ((void**)basePtr)[0];
	u16* targetPtr = (u16*)((u8*)pppShape + (u32)shapePtr + 0x80);
	
	targetPtr[2] = 0;
	targetPtr[1] = 0;
	targetPtr[0] = 0;
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
void pppCalcShape(void* pppShape, void* data, void* additionalData)
{
	if (lbl_8032ED70 != 0) {
		return;
	}

	ShapeRuntimeData* runtimeData = *(ShapeRuntimeData**)((u8*)additionalData + 0xC);
	ShapeControlData* controlData = (ShapeControlData*)data;
	ShapeState* shapeData = (ShapeState*)((u8*)pppShape + runtimeData->shapeDataOffset + 0x80);
	s16 type = controlData->type;

	if (type == -1) {
		return;
	}

	void** shapeTables = *(void***)((u8*)lbl_8032ED54 + 0xC);
	void* shapeSpec = *(void**)shapeTables[(u16)type];
	ShapeSpecEntry* shape = (ShapeSpecEntry*)((u8*)shapeSpec + ((u32)shapeData->counter << 3) + 0x10);

	shapeData->currentId = shapeData->counter;
	shapeData->value = (u16)(shapeData->value + controlData->step);
	u16 value = shapeData->value;
	s16 maxValue = shape->maxValue;
	if (maxValue > value) {
		return;
	}
	shapeData->value = (u16)(value - maxValue);

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
 * PAL Address: 0x800654b4
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShape(void* pppShape, void* data, void* additionalData)
{
	ShapeRuntimeData* runtimeData = *(ShapeRuntimeData**)((u8*)additionalData + 0xC);
	ShapeControlData* controlData = (ShapeControlData*)data;
	ShapeState* shapeData = (ShapeState*)((u8*)pppShape + runtimeData->shapeDataOffset + 0x80);
	void* posData = (u8*)pppShape + runtimeData->posDataOffset + 0x80;
	s16 type = controlData->type;

	if (type == -1) {
		return;
	}

	void** shapeTables = *(void***)((u8*)lbl_8032ED54 + 0xC);
	void* shapeSpec = *(void**)shapeTables[(u16)type];
	ShapeSpecEntry* shape = (ShapeSpecEntry*)((u8*)shapeSpec + ((u32)shapeData->currentId << 3) + 0x10);
	void* drawShape = (u8*)shapeSpec + shape->offset;

	pppSetDrawEnv(
		(pppCVECTOR*)((u8*)posData + 8),
		(pppFMATRIX*)((u8*)pppShape + 0x40),
		controlData->scale,
		controlData->param14,
		controlData->paramE,
		controlData->blendMode,
		0,
		1,
		1,
		0
	);

	pppSetBlendMode(controlData->blendMode);
	pppDrawShp((tagOAN3_SHAPE*)drawShape, *(CMaterialSet**)((u8*)lbl_8032ED54 + 0x4), controlData->blendMode);
}
