// Function: drawHeapTitle__Q27CMemory6CStageFi
// Entry: 8001d9bc
// Size: 396 bytes

void drawHeapTitle__Q27CMemory6CStageFi(CStage *stage,int param_2)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  undefined auStack_118 [264];
  
  if (stage->m_allocationMode == 2) {
    iVar3 = stage->field269_0x110;
  }
  else {
    iVar3 = *(int *)(stage->field269_0x110 + 8);
  }
  uVar6 = 0;
  uVar5 = 0;
  iVar4 = *(int *)(iVar3 + 4);
  do {
    if ((*(byte *)(iVar3 + 2) & 2) != 0) {
      iVar3 = strlen(&stage->m_allocationSourceStr);
      strcpy(auStack_118,
             (int)&stage->m_allocationSourceStr + (iVar3 - 0xcU & ~((int)(iVar3 - 0xcU) >> 0x1f)));
      DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,0x10,(short)param_2,auStack_118,8);
      sprintf(auStack_118,s__4d__4d__4d_801d6800,*(undefined4 *)&stage->field_0x124,
              ((int)uVar6 >> 10) + (uint)((int)uVar6 < 0 && (uVar6 & 0x3ff) != 0),
              ((int)uVar5 >> 10) + (uint)((int)uVar5 < 0 && (uVar5 & 0x3ff) != 0));
      DrawDebugStringDirect__8CGraphicFUlUlPcUl(&Graphic,0x208,(short)param_2,auStack_118,8);
      return;
    }
    if ((*(byte *)(iVar3 + 2) & 4) == 0) {
      uVar2 = *(int *)(iVar3 + 8) - (iVar3 + 0x40);
      uVar6 = uVar6 + uVar2;
      if ((int)uVar5 < (int)uVar2) {
        uVar5 = uVar2;
      }
    }
  } while ((*(int *)(iVar3 + 0x10) == *(int *)(iVar3 + 8) - (iVar3 + 0x40)) &&
          (bVar1 = *(int *)(iVar3 + 4) == iVar4, iVar4 = iVar3, iVar3 = *(int *)(iVar3 + 8), bVar1))
  ;
  if (System.m_execParam != 0) {
    Printf__7CSystemFPce(&System,&DAT_801d67d8);
  }
  return;
}

