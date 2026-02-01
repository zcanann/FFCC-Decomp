// Function: CARDFreeBlocks
// Entry: 8019962c
// Size: 336 bytes

int CARDFreeBlocks(undefined4 chan,int *bytes,int *files)

{
  int iVar1;
  int iVar2;
  ushort uVar3;
  CARDControl *local_18 [3];
  
  iVar1 = __CARDGetControlBlock(chan,local_18);
  if (-1 < iVar1) {
    iVar1 = __CARDGetFatBlock(local_18[0]);
    iVar2 = __CARDGetDirBlock(local_18[0]);
    if ((iVar1 == 0) || (iVar2 == 0)) {
      OSDisableInterrupts();
      if (local_18[0]->attached == 0) {
        if (local_18[0]->result == -1) {
          local_18[0]->result = -6;
        }
      }
      else {
        local_18[0]->result = -6;
      }
      OSRestoreInterrupts();
      iVar1 = -6;
    }
    else {
      if (bytes != (int *)0x0) {
        *bytes = local_18[0]->sectorSize * (uint)*(ushort *)(iVar1 + 6);
      }
      if (files != (int *)0x0) {
        *files = 0;
        for (uVar3 = 0; uVar3 < 0x7f; uVar3 = uVar3 + 1) {
          if (*(char *)(iVar2 + 8) == -1) {
            *files = *files + 1;
          }
          iVar2 = iVar2 + 0x40;
        }
      }
      OSDisableInterrupts();
      if (local_18[0]->attached == 0) {
        if (local_18[0]->result == -1) {
          local_18[0]->result = 0;
        }
      }
      else {
        local_18[0]->result = 0;
      }
      OSRestoreInterrupts();
      iVar1 = 0;
    }
  }
  return iVar1;
}

