// Function: CARDMountAsync
// Entry: 8019cafc
// Size: 416 bytes

undefined4 CARDMountAsync(int chan,undefined4 param_2,undefined4 param_3,code *callback)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  if ((chan < 0) || (1 < chan)) {
    uVar1 = 0xffffff80;
  }
  else if ((DAT_800030e3 & 0x80) == 0) {
    iVar4 = chan * 0x110;
    piVar5 = &DAT_80327540 + chan * 0x44;
    uVar1 = OSDisableInterrupts();
    if ((&DAT_80327544)[chan * 0x44] == -1) {
      OSRestoreInterrupts(uVar1);
      uVar1 = 0xffffffff;
    }
    else if ((*piVar5 == 0) && (uVar2 = EXIGetState(chan), (uVar2 & 8) != 0)) {
      OSRestoreInterrupts(uVar1);
      uVar1 = 0xfffffffe;
    }
    else {
      (&DAT_80327544)[chan * 0x44] = 0xffffffff;
      (&DAT_803275c0)[chan * 0x44] = param_2;
      *(undefined4 *)(&DAT_80327604 + iVar4) = param_3;
      if (callback == (code *)0x0) {
        callback = __CARDDefaultApiCallback;
      }
      *(code **)(&DAT_80327610 + iVar4) = callback;
      *(undefined4 *)(&DAT_8032760c + iVar4) = 0;
      if ((*piVar5 == 0) && (iVar3 = EXIAttach(chan,__CARDExtHandler), iVar3 == 0)) {
        (&DAT_80327544)[chan * 0x44] = 0xfffffffd;
        OSRestoreInterrupts(uVar1);
        uVar1 = 0xfffffffd;
      }
      else {
        *(undefined4 *)(&DAT_80327564 + iVar4) = 0;
        *piVar5 = 1;
        EXISetExiCallback(chan,0);
        OSCancelAlarm(&DAT_80327620 + iVar4);
        *(undefined4 *)(&DAT_803275c4 + iVar4) = 0;
        *(undefined4 *)(&DAT_803275c8 + iVar4) = 0;
        OSRestoreInterrupts(uVar1);
        *(code **)(&DAT_8032761c + iVar4) = __CARDMountCallback;
        iVar3 = EXILock(chan,0,__CARDUnlockedHandler);
        if (iVar3 == 0) {
          uVar1 = 0;
        }
        else {
          *(undefined4 *)(&DAT_8032761c + iVar4) = 0;
          uVar1 = DoMount(chan);
        }
      }
    }
  }
  else {
    uVar1 = 0xfffffffd;
  }
  return uVar1;
}

