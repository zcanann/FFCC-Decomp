// Function: heapInfo__Q27CMemory6CStageFRUlRUlRUl
// Entry: 8001c2f0
// Size: 280 bytes

void heapInfo__Q27CMemory6CStageFRUlRUlRUl(CStage *stage,int *param_2,int *param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  if (stage->m_allocationMode == 2) {
    iVar1 = stage->field269_0x110;
  }
  else {
    iVar1 = *(int *)(stage->field269_0x110 + 8);
  }
  *param_2 = 0;
  *param_3 = 0;
  *param_4 = 0;
  if (stage->m_allocationMode == 2) {
    iVar3 = *(int *)&stage->field_0x8;
    for (iVar5 = 0; iVar5 <= *(int *)&stage->field_0x120; iVar5 = iVar5 + 1) {
      if (*(int *)&stage->field_0x120 == iVar5) {
        iVar4 = *(int *)&stage->field_0xc;
      }
      else {
        iVar4 = *(int *)(iVar1 + 4);
      }
      iVar2 = iVar4 - iVar3;
      if (iVar2 != 0) {
        *param_4 = *param_4 + iVar2;
        *param_2 = *param_2 + iVar2;
      }
      if (iVar5 < *(int *)&stage->field_0x120) {
        iVar2 = *(int *)(iVar1 + 8) - *(int *)(iVar1 + 4);
        *param_3 = *param_3 + iVar2;
        iVar3 = iVar4 + iVar2;
        *param_2 = *param_2 + iVar2;
      }
      iVar1 = iVar1 + 0x40;
    }
    return;
  }
  while( true ) {
    if ((*(byte *)(iVar1 + 2) & 2) != 0) break;
    if ((*(byte *)(iVar1 + 2) & 4) == 0) {
      *param_4 = *param_4 + *(int *)(iVar1 + 0x10);
    }
    else {
      *param_3 = *param_3 + *(int *)(iVar1 + 0x10);
    }
    *param_2 = *param_2 + (*(int *)(iVar1 + 8) - iVar1);
    iVar1 = *(int *)(iVar1 + 8);
  }
  return;
}

