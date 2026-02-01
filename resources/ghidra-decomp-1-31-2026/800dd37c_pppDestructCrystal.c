// Function: pppDestructCrystal
// Entry: 800dd37c
// Size: 136 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructCrystal(pppCrystal *pppCrystal,UnkC *param_2)

{
  CStage *stage;
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)((int)(&pppCrystal->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  stage = (CStage *)*puVar1;
  if ((stage != (CStage *)0x0) && (*(CStage **)stage != (CStage *)0x0)) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)stage);
    *(undefined4 *)stage = 0;
  }
  if (stage != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(stage);
  }
  if ((CStage *)puVar1[1] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar1[1]);
    puVar1[1] = 0;
  }
  return;
}

