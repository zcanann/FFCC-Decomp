// Function: pppDestructRain
// Entry: 800dda78
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructRain(pppRain *pppRain,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  if (*(CStage **)((int)(&pppRain->field0_0x0 + 2) + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)((int)(&pppRain->field0_0x0 + 2) + iVar1));
    *(undefined4 *)((int)(&pppRain->field0_0x0 + 2) + iVar1) = 0;
  }
  return;
}

