// Function: pppDestructLocationTitle2
// Entry: 800da8b8
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructLocationTitle2(pppLocationTitle2 *pppLocationTitle2,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = *param_2->m_serializedDataOffsets;
  if (*(CStage **)((int)(&pppLocationTitle2->field0_0x0 + 2) + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage
              (*(CStage **)((int)(&pppLocationTitle2->field0_0x0 + 2) + iVar1));
    *(undefined4 *)((int)(&pppLocationTitle2->field0_0x0 + 2) + iVar1) = 0;
  }
  return;
}

