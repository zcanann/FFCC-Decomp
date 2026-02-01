// Function: pppDestructYmTracer2
// Entry: 80103e0c
// Size: 56 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmTracer2(pppYmTracer2 *pppYmTracer2,UnkC *param_2)

{
  if (*(CStage **)(pppYmTracer2->m_serializedData + *param_2->m_serializedDataOffsets + 0x28) !=
      (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage
              (*(CStage **)
                (pppYmTracer2->m_serializedData + *param_2->m_serializedDataOffsets + 0x28));
  }
  return;
}

