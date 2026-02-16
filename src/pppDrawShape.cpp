#include "ffcc/pppDrawShape.h"
#include "dolphin/types.h"

extern int lbl_8032ED70;
extern void* lbl_8032ED54;

extern "C" {
void pppSetDrawEnv__FP10pppCVECTORP10pppFMATRIXfUcUcUcUcUcUcUc(void*, void*, float, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void pppSetBlendMode__FUc(unsigned char);
void pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(void*, void*, unsigned char);
}

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
    float scale;
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
    s16 type = *(volatile s16*)((u8*)controlData + 0x4);

    if (type == -1) {
        return;
    }

    u32* shapeTables = *(u32**)((u8*)lbl_8032ED54 + 0xC);
    u8* shapeSpec = (u8*)shapeTables[(u16)type];
    ShapeSpecEntry* shape = (ShapeSpecEntry*)(shapeSpec + ((u32)shapeData->counter << 3) + 0x10);

	shapeData->currentId = shapeData->counter;
	shapeData->value = (u16)(shapeData->value + controlData->step);
    u16 value = shapeData->value;
    s16 maxValue = shape->maxValue;
	if (value < maxValue) {
		return;
	}
	shapeData->value = (u16)(value - maxValue);

	shapeData->counter++;
    if (shapeData->counter < *(s16*)(shapeSpec + 0x6)) {
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
	u32 shapeDataOffset = runtimeData->shapeDataOffset + 0x80;
	u32 posDataOffset = runtimeData->posDataOffset + 0x80;
	ShapeState* shapeData = (ShapeState*)((u8*)pppShape + shapeDataOffset);
	void* posData = (u8*)pppShape + posDataOffset;
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
		(u8*)pppShape + 0x40,
		controlData->scale,
        controlData->param15,
        controlData->paramE,
        controlData->blendMode,
        0,
        1,
        controlData->param14,
        0
    );

	pppSetBlendMode__FUc(controlData->blendMode);
	pppDrawShp__FP13tagOAN3_SHAPEP12CMaterialSetUc(drawShape, *(void**)((u8*)lbl_8032ED54 + 4), controlData->blendMode);
}
