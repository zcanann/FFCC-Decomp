#include "ffcc/pppYmTracer.h"

extern f32 FLOAT_803306e8;

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO  
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void initTracePolygon(pppYmTracer*, TRACE_POLYGON*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void copyPolygonData(TRACE_POLYGON*, TRACE_POLYGON*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80093cb4
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstructYmTracer(pppYmTracer* pppYmTracer, UnkC* param_2)
{
    f32 fVar1;
    f32* pfVar2;
    
    fVar1 = FLOAT_803306e8;
    pfVar2 = (f32*)((int)(&pppYmTracer->field0_0x0 + 2) + *(int*)param_2);
    
    pfVar2[10] = 0.0f;
    pfVar2[9] = 0.0f;
    pfVar2[8] = 0.0f;
    *(u16*)(pfVar2 + 0xb) = 0;
    
    pfVar2[3] = fVar1;
    pfVar2[2] = fVar1;
    pfVar2[1] = fVar1;
    pfVar2[0] = fVar1;
    pfVar2[7] = fVar1;
    pfVar2[6] = fVar1;
    pfVar2[5] = fVar1;
    pfVar2[4] = fVar1;
    
    *(u16*)((int)pfVar2 + 0x2e) = 0;
}

/*
 * --INFO--
 * PAL Address: 80093c94
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppConstruct2YmTracer(pppYmTracer* pppYmTracer, UnkC* param_2)
{
    int iVar1;
    
    iVar1 = *(int*)param_2;
    *(u16*)((char*)pppYmTracer + 0xae + iVar1) = 0;
    *(u16*)((char*)pppYmTracer + 0xac + iVar1) = 0;
}

/*
 * --INFO--
 * PAL Address: 80093c5c
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDestructYmTracer(pppYmTracer* pppYmTracer, UnkC* param_2)
{
    void** ptr = (void**)((char*)pppYmTracer + 0xa8 + *(int*)param_2);
    if (*ptr != nullptr) {
        // Call some heap usage function - simplified for now
        // pppHeapUseRate__FPQ27CMemory6CStage(*ptr);
    }
}

/*
 * --INFO--
 * PAL Address: 800934c4
 * PAL Size: 1944b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppFrameYmTracer(pppYmTracer* pppYmTracer, UnkB* param_2, UnkC* param_3)
{
	// TODO - Complex function, implement later
}

/*
 * --INFO--
 * PAL Address: 8009312c
 * PAL Size: 920b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppRenderYmTracer(pppYmTracer* pppYmTracer, UnkB* param_2, UnkC* param_3)
{
	// TODO - Complex function, implement later
}
