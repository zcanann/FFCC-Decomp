// Function: pppDestructLocationTitle
// Entry: 800d9278
// Size: 84 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructLocationTitle(pppLocationTitle *pppLocationTitle,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = *param_2->m_serializedDataOffsets;
  if (*(CStage **)((int)(&pppLocationTitle->field0_0x0 + 2) + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage
              (*(CStage **)((int)(&pppLocationTitle->field0_0x0 + 2) + iVar1));
    *(undefined4 *)((int)(&pppLocationTitle->field0_0x0 + 2) + iVar1) = 0;
  }
  return;
}

