// Function: pppDestructYmMelt
// Entry: 800a5ce8
// Size: 56 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmMelt(pppYmMelt *pppYmMelt,UnkC *param_2)

{
  if (*(CStage **)((int)(&pppYmMelt->field0_0x0 + 2) + *param_2->m_serializedDataOffsets) !=
      (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage
              (*(CStage **)((int)(&pppYmMelt->field0_0x0 + 2) + *param_2->m_serializedDataOffsets));
  }
  return;
}

