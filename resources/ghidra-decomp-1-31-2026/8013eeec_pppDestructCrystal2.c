// Function: pppDestructCrystal2
// Entry: 8013eeec
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructCrystal2(pppCrystal2 *pppCrystal2,UnkC *param_2)

{
  CStage *stage;
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)((int)(&pppCrystal2->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2])
  ;
  stage = (CStage *)*puVar1;
  if ((CStage *)puVar1[1] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar1[1]);
    puVar1[1] = 0;
  }
  if ((stage != (CStage *)0x0) && (*(CStage **)stage != (CStage *)0x0)) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)stage);
    *(undefined4 *)stage = 0;
  }
  if (stage != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(stage);
  }
  return;
}

