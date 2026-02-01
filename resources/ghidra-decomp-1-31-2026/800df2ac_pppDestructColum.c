// Function: pppDestructColum
// Entry: 800df2ac
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructColum(pppColum *pppColum,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[3];
  if (*(CStage **)(&pppColum->field_0x88 + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppColum->field_0x88 + iVar1));
    *(undefined4 *)(&pppColum->field_0x88 + iVar1) = 0;
  }
  return;
}

