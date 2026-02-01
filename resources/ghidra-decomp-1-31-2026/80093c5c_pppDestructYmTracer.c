// Function: pppDestructYmTracer
// Entry: 80093c5c
// Size: 56 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmTracer(pppYmTracer *pppYmTracer,UnkC *param_2)

{
  if (*(CStage **)(&pppYmTracer->field_0xa8 + *param_2->m_serializedDataOffsets) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage
              (*(CStage **)(&pppYmTracer->field_0xa8 + *param_2->m_serializedDataOffsets));
  }
  return;
}

