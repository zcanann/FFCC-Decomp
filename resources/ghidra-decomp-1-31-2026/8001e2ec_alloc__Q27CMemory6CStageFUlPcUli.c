// Function: alloc__Q27CMemory6CStageFUlPcUli
// Entry: 8001e2ec
// Size: 524 bytes

int alloc__Q27CMemory6CStageFUlPcUli
              (CStage *stage,int param_2,char *param_3,undefined4 param_4,int param_5)

{
  uint uVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  DAT_8032ec58 = DAT_8032ec58 + 1;
  if (param_2 == 0) {
    param_2 = 0x40;
  }
  uVar1 = param_2 + 0x3fU & 0xffffffc0;
  iVar5 = 0;
  iVar4 = 0;
  do {
    if (iVar4 != 0) {
      for (iVar3 = *(int *)(stage->field269_0x110 + 8); (*(byte *)(iVar3 + 2) & 3) == 0;
          iVar3 = *(int *)(iVar3 + 8)) {
        if (((*(byte *)(iVar3 + 2) & 4) == 0) && (uVar1 <= *(uint *)(iVar3 + 0x10))) {
          if (uVar1 < *(uint *)(iVar3 + 0x10) - 0x40) {
            iVar5 = iVar3 + uVar1;
            *(undefined *)(iVar5 + 0x42) = 0;
            *(uint *)(iVar5 + 0x50) = (*(int *)(iVar3 + 0x10) - uVar1) + -0x40;
            *(uint *)(iVar3 + 0x10) = uVar1;
            *(undefined2 *)(iVar5 + 0x40) = 0x4b41;
            *(undefined2 *)(iVar5 + 0x7e) = 0x4d49;
            *(int *)(iVar5 + 0x44) = iVar3;
            *(undefined4 *)(iVar5 + 0x48) = *(undefined4 *)(iVar3 + 8);
            *(int *)(iVar3 + 8) = iVar5 + 0x40;
            *(int *)(*(int *)(iVar5 + 0x48) + 4) = iVar5 + 0x40;
          }
          *(short *)(iVar3 + 0x18) = (short)param_4;
          *(char *)(iVar3 + 3) = (char)Memory._30612_4_;
          memset(iVar3 + 0x1a,0,0x24);
          pcVar2 = param_3;
          if (param_3 == (char *)0x0) {
            pcVar2 = &DAT_8032f7d4;
          }
          strncpy(iVar3 + 0x1a,pcVar2,0x23);
          iVar5 = iVar3 + 0x40;
          *(undefined *)(iVar3 + 2) = 4;
          *(byte *)(iVar3 + 2) = *(byte *)(iVar3 + 2) & 0xf | (byte)(Memory._30620_4_ << 4);
          *(ulong *)(iVar3 + 0x14) = stage->defaultParam;
          *(int *)&stage->field_0x124 = *(int *)&stage->field_0x124 + 1;
          *(CStage **)(iVar3 + 0xc) = stage;
          break;
        }
        if ((*(int *)(iVar3 + 8) == 0) || (*(int *)(iVar3 + 4) == 0)) {
          heapWalker__Q27CMemory6CStageFiPvUl(stage,0xffffffff,0,0xffffffff);
        }
      }
      if (iVar5 != 0) break;
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 < 2);
  if ((param_5 == 0) && (iVar5 == 0)) {
    if (param_3 == (char *)0x0) {
      param_3 = &DAT_8032f7d4;
    }
    Printf__7CSystemFPce(&System,&DAT_801d6a24,&stage->m_allocationSourceStr,uVar1,param_3,param_4);
    heapWalker__Q27CMemory6CStageFiPvUl(stage,0xffffffff,0,0xffffffff);
  }
  return iVar5;
}

