// Function: pppDestructLerpPos
// Entry: 8012b43c
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructLerpPos(pppLerpPos *pppLerpPos,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = *param_2->m_serializedDataOffsets;
  if (*(CStage **)((int)(&pppLerpPos->field0_0x0 + 2) + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)((int)(&pppLerpPos->field0_0x0 + 2) + iVar1));
    *(undefined4 *)((int)(&pppLerpPos->field0_0x0 + 2) + iVar1) = 0;
  }
  return;
}

