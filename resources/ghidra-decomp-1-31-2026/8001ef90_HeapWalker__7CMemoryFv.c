// Function: HeapWalker__7CMemoryFv
// Entry: 8001ef90
// Size: 392 bytes

void HeapWalker__7CMemoryFv(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  CStage *pCVar4;
  int iVar5;
  CStage *pCVar6;
  
  Printf__7CSystemFPce(&System,&DAT_8032f7e8);
  Printf__7CSystemFPce(&System,&DAT_8032f808);
  Printf__7CSystemFPce(&System,s____Heap_Walker_801d6bfc);
  Printf__7CSystemFPce(&System,&DAT_8032f808);
  pCVar6 = (CStage *)(param_1 + 4);
  iVar5 = 0;
  do {
    if ((iVar5 != 1) || (iVar2 = OSGetConsoleSimulatedMemSize(), iVar2 == 0x3000000)) {
      for (pCVar4 = *(CStage **)&pCVar6->field_0x4; pCVar4 != pCVar6;
          pCVar4 = *(CStage **)&pCVar4->field_0x4) {
        heapWalker__Q27CMemory6CStageFiPvUl(pCVar4,0xffffffff,0,0xffffffff);
      }
      Printf__7CSystemFPce(&System,&DAT_8032f7e8);
      pCVar4 = *(CStage **)&pCVar6->field_0x4;
      iVar3 = 0;
      iVar2 = 0;
      do {
        uVar1 = (uint)(*(int *)&pCVar4->field_0xc - *(int *)&pCVar4->field_0x8) >> 10;
        Printf__7CSystemFPce(&System,s_Use____5dKB__s_801d6c0c,uVar1,&pCVar4->m_allocationSourceStr)
        ;
        iVar3 = iVar3 + uVar1;
        uVar1 = (uint)(*(int *)(*(int *)&pCVar4->field_0x4 + 8) - *(int *)&pCVar4->field_0xc) >> 10;
        Printf__7CSystemFPce(&System,s_Unuse___5dKB_801d6c20,uVar1);
        pCVar4 = *(CStage **)&pCVar4->field_0x4;
        iVar2 = iVar2 + uVar1;
      } while (pCVar4 != pCVar6);
      Printf__7CSystemFPce
                (&System,s_Total___5dKB_Use___5dKB_Unuse____801d6c30,iVar3 + iVar2,iVar3,iVar2);
    }
    iVar5 = iVar5 + 1;
    pCVar6 = pCVar6 + 0x22;
  } while (iVar5 < 3);
  return;
}

