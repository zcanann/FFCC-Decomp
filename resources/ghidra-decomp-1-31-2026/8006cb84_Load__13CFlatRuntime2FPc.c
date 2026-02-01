// Function: Load__13CFlatRuntime2FPc
// Entry: 8006cb84
// Size: 444 bytes

undefined4 Load__13CFlatRuntime2FPc(CFlatRuntime2 *flatRuntime2,undefined4 param_2)

{
  CFileCHandle *pCVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined auStack_128 [256];
  
  sprintf(auStack_128,s_dvd_cft__s_cft_801d9024,param_2);
  pCVar1 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_128,0,0);
  if (pCVar1 == (CFileCHandle *)0x0) {
    uVar3 = 0;
  }
  else {
    Read__5CFileFPQ25CFile7CHandle(&File,pCVar1);
    SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar1);
    Create__12CFlatRuntimeFPv(&flatRuntime2->flatRuntimeBase,File.m_readBuffer);
    Close__5CFileFPQ25CFile7CHandle(&File,pCVar1);
    iVar2 = (**(code **)((int)(flatRuntime2->flatRuntimeBase).vtable + 0x48))(flatRuntime2);
    if (iVar2 != 0) {
      iVar4 = 0;
      iVar2 = 0;
      do {
        sprintf(auStack_128,s_dvd_cft__s_cft_dbg_801d9034,param_2);
        if (iVar4 != 0) {
          sprintf(auStack_128,&DAT_80330194,auStack_128,iVar4);
        }
        pCVar1 = (CFileCHandle *)Open__5CFileFPcUlQ25CFile3PRI(&File,auStack_128,0,0);
        if (pCVar1 == (CFileCHandle *)0x0) {
          return 0;
        }
        Read__5CFileFPQ25CFile7CHandle(&File,pCVar1);
        SyncCompleted__5CFileFPQ25CFile7CHandle(&File,pCVar1);
        iVar2 = CreateDebug__12CFlatRuntimeFPvi
                          (&flatRuntime2->flatRuntimeBase,File.m_readBuffer,iVar2);
        Close__5CFileFPQ25CFile7CHandle(&File,pCVar1);
        iVar4 = iVar4 + 1;
      } while (iVar2 != -1);
    }
    resetChangeScript__13CFlatRuntime2Fv(flatRuntime2);
    if (2 < (uint)System.m_execParam) {
      Printf__7CSystemFPce(&System,&DAT_801d9048);
    }
    uVar3 = 1;
  }
  return uVar3;
}

