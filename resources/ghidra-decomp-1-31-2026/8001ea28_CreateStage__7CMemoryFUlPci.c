// Function: CreateStage__7CMemoryFUlPci
// Entry: 8001ea28
// Size: 600 bytes

CStage * CreateStage__7CMemoryFUlPci
                   (CMemory *memory,int param_2,char *allocationSourceStr,int allocationMode)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined *puVar6;
  CStage *pCVar7;
  
  if ((allocationMode != 1) || (iVar2 = OSGetConsoleSimulatedMemSize(), iVar2 == 0x3000000)) {
    uVar1 = param_2 + 0x3fU & 0xffffffc0;
    puVar6 = &memory->field_0x4 + allocationMode * 0x27d8;
    pCVar7 = *(CStage **)(puVar6 + 0x130);
    puVar5 = puVar6;
    if (pCVar7 == (CStage *)(puVar6 + 300)) {
      Printf__7CSystemFPce(&System,&DAT_801d6b7c);
    }
    else {
      do {
        puVar4 = *(undefined **)(puVar5 + 4);
        if (*(int *)(puVar5 + 0xc) + uVar1 <= *(uint *)(puVar4 + 8)) {
          *(undefined4 *)(puVar6 + 0x130) = *(undefined4 *)&pCVar7->field_0x4;
          *(undefined **)pCVar7 = puVar5;
          *(undefined4 *)&pCVar7->field_0x4 = *(undefined4 *)(puVar5 + 4);
          **(undefined4 **)(puVar5 + 4) = pCVar7;
          *(CStage **)(puVar5 + 4) = pCVar7;
          *(undefined4 *)&pCVar7->field_0x8 = *(undefined4 *)(puVar5 + 0xc);
          *(uint *)&pCVar7->field_0xc = *(int *)&pCVar7->field_0x8 + uVar1;
          if (allocationSourceStr == (char *)0x0) {
            allocationSourceStr = &DAT_8032f7d4;
          }
          strcpy(&pCVar7->m_allocationSourceStr,allocationSourceStr);
          pCVar7->m_allocationMode = allocationMode;
          if (allocationMode != 2) {
            for (puVar5 = *(undefined **)&pCVar7->field_0x8;
                puVar5 < *(undefined **)&pCVar7->field_0xc; puVar5 = puVar5 + 1) {
              *puVar5 = 0xcd;
            }
            pCVar7->field269_0x110 = *(int *)&pCVar7->field_0x8;
            *(int *)&pCVar7->field_0x114 = *(int *)&pCVar7->field_0xc + -0x40;
            *(undefined *)(pCVar7->field269_0x110 + 2) = 5;
            *(undefined4 *)(pCVar7->field269_0x110 + 4) = 0;
            *(int *)(pCVar7->field269_0x110 + 8) = pCVar7->field269_0x110 + 0x40;
            *(undefined2 *)(pCVar7->field269_0x110 + 0x40) = 0x4b41;
            *(undefined2 *)(pCVar7->field269_0x110 + 0x7e) = 0x4d49;
            *(undefined *)(pCVar7->field269_0x110 + 0x42) = 0;
            *(int *)(pCVar7->field269_0x110 + 0x50) =
                 *(int *)&pCVar7->field_0x114 - (pCVar7->field269_0x110 + 0x80);
            *(int *)(pCVar7->field269_0x110 + 0x44) = pCVar7->field269_0x110;
            *(undefined4 *)(pCVar7->field269_0x110 + 0x48) = *(undefined4 *)&pCVar7->field_0x114;
            *(undefined *)(*(int *)&pCVar7->field_0x114 + 2) = 6;
            *(int *)(*(int *)&pCVar7->field_0x114 + 4) = pCVar7->field269_0x110 + 0x40;
            *(undefined4 *)(*(int *)&pCVar7->field_0x114 + 8) = 0;
            *(undefined4 *)&pCVar7->field_0x124 = 0;
          }
          if (allocationMode == 2) {
            uVar3 = alloc__Q27CMemory6CStageFUlPcUli
                              (memory->m_stage,0x810,s_memory_cpp_801d6690,0x228,0);
            iVar2 = __construct_new_array(uVar3,0,0,0x40,0x20);
            pCVar7->field269_0x110 = iVar2;
            *(undefined4 *)&pCVar7->field_0x120 = 0;
          }
          pCVar7->defaultParam = 0xffffffff;
          return pCVar7;
        }
        puVar5 = puVar4;
      } while (puVar4 != puVar6);
      Printf__7CSystemFPce(&System,&DAT_801d6bb0);
      HeapWalker__7CMemoryFv(memory);
    }
  }
  return (CStage *)0x0;
}

