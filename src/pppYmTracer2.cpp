#include "ffcc/pppYmTracer2.h"
#include "ffcc/pppPart.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void initTracePolygon(PYmTracer2*, TRACE_POLYGON&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80103e68
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
{
	float fVar1 = 1.0f; // FLOAT_80331840 placeholder
	unsigned char* puVar2 = (unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets;
	
	*(u32*)(puVar2 + 0x28) = 0;
	*(u32*)(puVar2 + 0x24) = 0;
	*(u32*)(puVar2 + 0x20) = 0;
	*(u16*)(puVar2 + 0x2c) = 0;
	
	*(float*)(puVar2 + 0xc) = fVar1;
	*(float*)(puVar2 + 8) = fVar1;
	*(float*)(puVar2 + 4) = fVar1;
	*(float*)puVar2 = fVar1;
	*(float*)(puVar2 + 0x1c) = fVar1;
	*(float*)(puVar2 + 0x18) = fVar1;
	*(float*)(puVar2 + 0x14) = fVar1;
	*(float*)(puVar2 + 0x10) = fVar1;
	
	*(u16*)(puVar2 + 0x2e) = 0;
	*(u16*)(puVar2 + 0x30) = 0;
	*(u16*)(puVar2 + 0x32) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80103e44
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
{
	unsigned char* iVar1 = (unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets;
	
	*(short*)(iVar1 + 0x2c) = 0;
	*(short*)(iVar1 + 0x2e) = 0;
	*(short*)(iVar1 + 0x32) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80103e0c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmTracer2(pppYmTracer2* pppYmTracer2, UnkC* param_2)
{
	void** memPtr = (void**)((unsigned char*)pppYmTracer2 + 0x80 + *param_2->m_serializedDataOffsets + 0x28);
	if (*memPtr != 0) {
		pppHeapUseRate((CMemory::CStage*)*memPtr);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppFrameYmTracer2(pppYmTracer2*, UnkB*, UnkC*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppRenderYmTracer2(pppYmTracer2*, UnkB*, UnkC*)
{
	// TODO
}
