// Function: ClearArena
// Entry: 8017b7e4
// Size: 296 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void ClearArena(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  
  iVar1 = OSGetResetCode();
  if (iVar1 == -0x80000000) {
    DAT_8032ef4c = _DAT_812fdff0;
    DAT_8032ef48 = _DAT_812fdfec;
    if (_DAT_812fdff0 == 0) {
      iVar1 = OSGetArenaHi();
      iVar2 = OSGetArenaLo();
      uVar3 = OSGetArenaLo();
      memset(uVar3,0,iVar1 - iVar2);
    }
    else {
      uVar4 = OSGetArenaLo();
      if (uVar4 < DAT_8032ef4c) {
        uVar4 = OSGetArenaHi();
        if (DAT_8032ef4c < uVar4) {
          iVar1 = OSGetArenaLo();
          iVar1 = DAT_8032ef4c - iVar1;
          uVar3 = OSGetArenaLo();
          memset(uVar3,0,iVar1);
          uVar5 = OSGetArenaHi();
          uVar4 = DAT_8032ef48;
          if (DAT_8032ef48 < uVar5) {
            iVar1 = OSGetArenaHi();
            memset(uVar4,0,iVar1 - uVar4);
          }
        }
        else {
          iVar1 = OSGetArenaHi();
          iVar2 = OSGetArenaLo();
          uVar3 = OSGetArenaLo();
          memset(uVar3,0,iVar1 - iVar2);
        }
      }
    }
  }
  else {
    DAT_8032ef4c = 0;
    DAT_8032ef48 = 0;
    iVar1 = OSGetArenaHi();
    iVar2 = OSGetArenaLo();
    uVar3 = OSGetArenaLo();
    memset(uVar3,0,iVar1 - iVar2);
  }
  return;
}

