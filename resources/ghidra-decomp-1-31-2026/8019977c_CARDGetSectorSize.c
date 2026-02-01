// Function: CARDGetSectorSize
// Entry: 8019977c
// Size: 132 bytes

int CARDGetSectorSize(undefined4 param_1,int32_t *param_2)

{
  int iVar1;
  CARDControl *local_10 [3];
  
  iVar1 = __CARDGetControlBlock(param_1,local_10);
  if (-1 < iVar1) {
    *param_2 = local_10[0]->sectorSize;
    OSDisableInterrupts();
    if (local_10[0]->attached == 0) {
      if (local_10[0]->result == -1) {
        local_10[0]->result = 0;
      }
    }
    else {
      local_10[0]->result = 0;
    }
    OSRestoreInterrupts();
    iVar1 = 0;
  }
  return iVar1;
}

