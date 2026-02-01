// Function: pppDestructYmMana
// Entry: 800d7440
// Size: 1060 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void pppDestructYmMana(pppYmMana *pppYmMana,UnkC *param_2)

{
  char cVar1;
  CCharaPcsCHandle *handle;
  int iVar2;
  int iVar3;
  CStage *pCVar4;
  uint uVar5;
  CGObject *gObject;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  
  puVar10 = (undefined4 *)((int)(&pppYmMana->field0_0x0 + 2) + param_2->m_serializedDataOffsets[2]);
  gObject = (CGObject *)*puVar10;
  DispCharaParts__8CGObjectFi(gObject,1);
  handle = (CCharaPcsCHandle *)GetCharaHandlePtr__FP8CGObjectl(gObject,0);
  iVar2 = GetCharaModelPtr__FPQ29CCharaPcs7CHandle(handle);
  *(undefined4 *)(iVar2 + 0xe4) = 0;
  *(undefined4 *)(iVar2 + 0xe8) = 0;
  *(undefined4 *)(iVar2 + 0xf0) = 0;
  *(undefined4 *)(iVar2 + 0xfc) = 0;
  _WaitDrawDone__8CGraphicFPci(&Graphic,s_pppYmMana_cpp_801db4d8,0x2ce);
  MaterialMan._208_4_ = 0;
  MaterialMan._220_4_ = 0;
  if ((CStage *)puVar10[10] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[10]);
    puVar10[10] = 0;
  }
  if ((CStage *)puVar10[0xb] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0xb]);
    puVar10[0xb] = 0;
  }
  if ((CStage *)puVar10[0xc] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0xc]);
    puVar10[0xc] = 0;
  }
  if ((CStage *)puVar10[0xd] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0xd]);
    puVar10[0xd] = 0;
  }
  if ((CStage *)puVar10[8] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[8]);
    puVar10[8] = 0;
  }
  if ((CStage *)puVar10[0xf] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0xf]);
    puVar10[0xf] = 0;
  }
  if ((CStage *)puVar10[0x10] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x10]);
    puVar10[0x10] = 0;
  }
  if ((CStage *)puVar10[0x12] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x12]);
    puVar10[0x12] = 0;
  }
  if ((CStage *)puVar10[0x13] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x13]);
    puVar10[0x13] = 0;
  }
  if ((CStage *)puVar10[0x14] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x14]);
    puVar10[0x14] = 0;
  }
  if ((CStage *)puVar10[0x15] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x15]);
    puVar10[0x15] = 0;
  }
  if ((CStage *)puVar10[0x16] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x16]);
    puVar10[0x16] = 0;
  }
  if ((CStage *)puVar10[0x1e] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x1e]);
    puVar10[0x1e] = 0;
  }
  if ((CStage *)puVar10[9] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[9]);
    puVar10[9] = 0;
  }
  if ((CStage *)puVar10[0x17] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x17]);
    puVar10[0x17] = 0;
  }
  if ((CStage *)puVar10[0x11] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x11]);
    puVar10[0x11] = 0;
  }
  if ((CStage *)puVar10[0x19] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x19]);
    puVar10[0x19] = 0;
  }
  if ((CStage *)puVar10[0x1a] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x1a]);
    puVar10[0x1a] = 0;
  }
  if ((CStage *)puVar10[0x1b] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x1b]);
    puVar10[0x1b] = 0;
  }
  if ((CStage *)puVar10[0x1c] != (CStage *)0x0) {
    pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x1c]);
    puVar10[0x1c] = 0;
  }
  iVar9 = *(int *)(iVar2 + 0xac);
  iVar8 = puVar10[0x1d];
  for (uVar7 = 0; uVar7 < *(uint *)(*(int *)(iVar2 + 0xa4) + 0xc); uVar7 = uVar7 + 1) {
    cVar1 = *(char *)(iVar8 + 0x1c);
    iVar6 = *(int *)(iVar9 + 8);
    if (cVar1 == '\x01') {
      iVar3 = strcmp(iVar6,&DAT_80330e88);
      if (iVar3 == 0) {
        iVar3 = 0;
        for (uVar5 = 0; uVar5 < *(uint *)(iVar6 + 0x4c); uVar5 = uVar5 + 1) {
          if ((puVar10[0x18] != 0) &&
             (pCVar4 = *(CStage **)(puVar10[0x18] + iVar3), pCVar4 != (CStage *)0x0)) {
            pppHeapUseRate__FPQ27CMemory6CStage(pCVar4);
            *(undefined4 *)(puVar10[0x18] + iVar3) = 0;
          }
          iVar3 = iVar3 + 4;
        }
        if ((CStage *)puVar10[0x18] != (CStage *)0x0) {
          pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x18]);
          puVar10[0x18] = 0;
        }
      }
    }
    else if (cVar1 == '\x02') {
      iVar3 = strcmp(iVar6,&DAT_80330e90);
      if (iVar3 == 0) {
        iVar3 = 0;
        for (uVar5 = 0; uVar5 < *(uint *)(iVar6 + 0x4c); uVar5 = uVar5 + 1) {
          if ((puVar10[0x18] != 0) &&
             (pCVar4 = *(CStage **)(puVar10[0x18] + iVar3), pCVar4 != (CStage *)0x0)) {
            pppHeapUseRate__FPQ27CMemory6CStage(pCVar4);
            *(undefined4 *)(puVar10[0x18] + iVar3) = 0;
          }
          iVar3 = iVar3 + 4;
        }
        if ((CStage *)puVar10[0x18] != (CStage *)0x0) {
          pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x18]);
          puVar10[0x18] = 0;
        }
      }
    }
    else if ((cVar1 == '\x03') && (iVar3 = strcmp(iVar6,&DAT_80330e98), iVar3 == 0)) {
      iVar3 = 0;
      for (uVar5 = 0; uVar5 < *(uint *)(iVar6 + 0x4c); uVar5 = uVar5 + 1) {
        if ((puVar10[0x18] != 0) &&
           (pCVar4 = *(CStage **)(puVar10[0x18] + iVar3), pCVar4 != (CStage *)0x0)) {
          pppHeapUseRate__FPQ27CMemory6CStage(pCVar4);
          *(undefined4 *)(puVar10[0x18] + iVar3) = 0;
        }
        iVar3 = iVar3 + 4;
      }
      if ((CStage *)puVar10[0x18] != (CStage *)0x0) {
        pppHeapUseRate__FPQ27CMemory6CStage((CStage *)puVar10[0x18]);
        puVar10[0x18] = 0;
      }
    }
    iVar9 = iVar9 + 0x14;
  }
  return;
}

