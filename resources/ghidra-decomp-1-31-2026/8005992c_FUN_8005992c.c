// Function: FUN_8005992c
// Entry: 8005992c
// Size: 252 bytes

void FUN_8005992c(int param_1)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  iVar5 = param_1;
  do {
    if ((*(CFileCHandle **)(iVar5 + 0x2378c) != (CFileCHandle *)0x0) &&
       (iVar2 = IsCompleted__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)(iVar5 + 0x2378c)),
       pvVar1 = File.m_readBuffer, iVar2 != 0)) {
      iVar2 = GetLength__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)(iVar5 + 0x2378c));
      CopyToAMemorySync__7CMemoryFPvPvUl
                (&Memory,pvVar1,*(undefined4 *)(param_1 + 0x236f8),iVar2 + 0x1fU & 0xffffffe0);
      *(int *)(iVar5 + 0x2370c) = iVar2;
      uVar3 = CheckSum__FPvi(pvVar1,iVar2);
      *(undefined4 *)(iVar5 + 0x2374c) = uVar3;
      *(int *)(param_1 + 0x23700) = *(int *)(param_1 + 0x23700) + 1;
      *(int *)(param_1 + 0x236f8) = *(int *)(param_1 + 0x236f8) + iVar2;
      Close__5CFileFPQ25CFile7CHandle(&File,*(CFileCHandle **)(iVar5 + 0x2378c));
      *(undefined4 *)(iVar5 + 0x2378c) = 0;
    }
    iVar4 = iVar4 + 1;
    iVar5 = iVar5 + 4;
  } while (iVar4 < 0x10);
  return;
}

