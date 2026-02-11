#include "ffcc/pppDrawShape.h"
#include "dolphin/types.h"

extern int lbl_8032ED70;
extern void* lbl_8032ED54;

extern void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
extern void pppSetBlendMode__FUc(unsigned char);
extern void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(void*, void*, unsigned char);

typedef struct ShapeRuntimeData {
    u32 shapeDataOffset;
    u32 posDataOffset;
} ShapeRuntimeData;

typedef struct ShapeState {
    s16 value;
    s16 counter;
    s16 currentId;
} ShapeState;

typedef struct ShapeControlData {
    u8 _pad0[4];
    u16 type;
    u8 _pad1[2];
    s32 step;
    u8 _pad2[1];
    u8 blendMode;
    u8 paramE;
    u8 param14;
    float scale;
} ShapeControlData;

typedef struct ShapeSpecEntry {
    s16 offset;
    u16 maxValue;
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

	if ((u16)type == 0xFFFF) {
		return;
	}

	void** shapeTables = *(void***)((u8*)lbl_8032ED54 + 0xC);
	void* shapeSpec = *(void**)((u8*)shapeTables + ((u32)type << 2));
	ShapeSpecEntry* shape = (ShapeSpecEntry*)((u8*)shapeSpec + ((u32)shapeData->counter << 3) + 0x10);

	shapeData->currentId = shapeData->counter;
	shapeData->value = shapeData->value + controlData->step;
	if (shapeData->value >= shape->maxValue) {
		shapeData->value = shapeData->value - shape->maxValue;
	}

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
	u16 type = controlData->type;

	if (type == 0xFFFF) {
		return;
	}

	void** shapeTables = *(void***)((u8*)lbl_8032ED54 + 0xC);
	void* shapeSpec = *(void**)((u8*)shapeTables + ((u32)type << 2));
	ShapeSpecEntry* shape = (ShapeSpecEntry*)((u8*)shapeSpec + ((u32)shapeData->currentId << 3) + 0x10);
	void* drawShape = (u8*)shapeSpec + shape->offset;

	pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(
		(u8*)posData + 8,
		(u8*)pppShape + 0x40,
		controlData->scale,
		controlData->param14,
		controlData->paramE,
		controlData->blendMode,
		(u8)0,
		(u8)1,
		(u8)1,
		(u8)0
	);

	pppSetBlendMode__FUc(controlData->blendMode);
	pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(drawShape, *(void**)((u8*)lbl_8032ED54 + 4), controlData->blendMode);
}
