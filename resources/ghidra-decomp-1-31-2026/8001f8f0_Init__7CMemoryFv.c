// Function: Init__7CMemoryFv
// Entry: 8001f8f0
// Size: 524 bytes

void Init__7CMemoryFv(CMemory *param_1)

{
  undefined *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  CStage *pCVar6;
  undefined *puVar7;
  undefined *puVar8;
  int iVar9;
  
  iVar2 = OSGetArenaLo();
  uVar3 = OSGetArenaLo();
  OSInitAlloc(uVar3,iVar2 + 0x14000,1);
  puVar8 = &param_1->field_0x4;
  *(undefined4 *)&param_1->field_0x7794 = 0;
  iVar2 = 0;
  *(undefined4 *)&param_1->field_0x7798 = 0;
  *(undefined4 *)&param_1->field_0x779c = 0;
  do {
    if ((iVar2 != 1) || (iVar4 = OSGetConsoleSimulatedMemSize(), iVar4 == 0x3000000)) {
      if ((iVar2 == 0) || (iVar2 == 1)) {
        uVar5 = OSGetArenaHi();
        if (iVar2 == 0) {
          *(undefined4 *)(puVar8 + 8) = 0x81780000;
          iVar4 = OSGetArenaLo();
          *(uint *)(puVar8 + 0xc) = iVar4 + 0x1403fU & 0xffffffc0;
        }
        else {
          *(uint *)(puVar8 + 8) = uVar5 & 0xffffffc0;
          *(undefined4 *)(puVar8 + 0xc) = 0x81800000;
        }
        if (0 < *(int *)(puVar8 + 8) - *(int *)(puVar8 + 0xc)) {
          memset(*(int *)(puVar8 + 0xc),0xab);
        }
      }
      else {
        *(undefined4 *)(puVar8 + 8) = 0x7fc000;
        *(undefined4 *)(puVar8 + 0xc) = 0x4000;
      }
      *(undefined **)puVar8 = puVar8;
      *(undefined **)(puVar8 + 4) = puVar8;
      iVar4 = 0;
      *(undefined **)(puVar8 + 0x130) = puVar8 + 600;
      iVar9 = 8;
      puVar7 = puVar8;
      do {
        if (iVar4 == 0x1f) {
          puVar1 = puVar8 + 300;
        }
        else {
          puVar1 = puVar8 + (iVar4 + 1) * 300 + 600;
        }
        *(undefined **)(puVar7 + 0x25c) = puVar1;
        if (iVar4 == 0x1e) {
          puVar1 = puVar8 + 300;
        }
        else {
          puVar1 = puVar8 + (iVar4 + 2) * 300 + 600;
        }
        *(undefined **)(puVar7 + 0x388) = puVar1;
        if (iVar4 == 0x1d) {
          puVar1 = puVar8 + 300;
        }
        else {
          puVar1 = puVar8 + (iVar4 + 3) * 300 + 600;
        }
        *(undefined **)(puVar7 + 0x4b4) = puVar1;
        if (iVar4 == 0x1c) {
          puVar1 = puVar8 + 300;
        }
        else {
          puVar1 = puVar8 + (iVar4 + 4) * 300 + 600;
        }
        *(undefined **)(puVar7 + 0x5e0) = puVar1;
        puVar7 = puVar7 + 0x4b0;
        iVar4 = iVar4 + 4;
        iVar9 = iVar9 + -1;
      } while (iVar9 != 0);
    }
    iVar2 = iVar2 + 1;
    puVar8 = puVar8 + 0x27d8;
  } while (iVar2 < 3);
  pCVar6 = CreateStage__7CMemoryFUlPci(param_1,0x2000,s_CMemory_current_801d6c88,0);
  *(CStage **)&param_1->field_0x778c = pCVar6;
  pCVar6 = CreateStage__7CMemoryFUlPci(param_1,0x4000,s_CMemory_memory_801d6c98,0);
  param_1->m_stage = pCVar6;
  return;
}

