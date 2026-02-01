// Function: pppDestructYmMiasma
// Entry: 80090d90
// Size: 56 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmMiasma(pppYmMiasma *pppYmMiasma,UnkC *param_2)

{
  if (*(CStage **)((int)(&pppYmMiasma->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]) !=
      (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage
              (*(CStage **)
                ((int)(&pppYmMiasma->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]));
  }
  return;
}

