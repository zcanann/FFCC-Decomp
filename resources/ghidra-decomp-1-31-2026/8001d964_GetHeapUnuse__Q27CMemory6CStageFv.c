// Function: GetHeapUnuse__Q27CMemory6CStageFv
// Entry: 8001d964
// Size: 88 bytes

int GetHeapUnuse__Q27CMemory6CStageFv(CStage *stage)

{
  int iVar1;
  int iVar2;
  
  if (stage->m_allocationMode == 2) {
    iVar2 = stage->field269_0x110;
  }
  else {
    iVar2 = *(int *)(stage->field269_0x110 + 8);
  }
  iVar1 = 0;
  while( true ) {
    if ((*(byte *)(iVar2 + 2) & 2) != 0) break;
    if ((*(byte *)(iVar2 + 2) & 4) == 0) {
      iVar1 = iVar1 + *(int *)(iVar2 + 0x10);
    }
    iVar2 = *(int *)(iVar2 + 8);
  }
  return iVar1;
}

