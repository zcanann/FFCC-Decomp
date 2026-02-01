// Function: pppDestructYmLaser
// Entry: 800d36f0
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmLaser(pppYmLaser *pppYmLaser,UnkC *param_2)

{
  int iVar1;
  
  iVar1 = param_2->m_serializedDataOffsets[2];
  if (*(CStage **)(&pppYmLaser->field_0x9c + iVar1) != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage(*(CStage **)(&pppYmLaser->field_0x9c + iVar1));
    *(undefined4 *)(&pppYmLaser->field_0x9c + iVar1) = 0;
  }
  return;
}

