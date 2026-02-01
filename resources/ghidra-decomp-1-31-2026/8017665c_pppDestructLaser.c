// Function: pppDestructLaser
// Entry: 8017665c
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructLaser(pppLaser *pppLaser,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  if (*(CStage **)(&pppLaser->field_0x9c + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppLaser->field_0x9c + iVar1));
    *(undefined4 *)(&pppLaser->field_0x9c + iVar1) = 0;
  }
  return;
}

