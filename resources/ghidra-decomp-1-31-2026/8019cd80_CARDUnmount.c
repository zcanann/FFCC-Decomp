// Function: CARDUnmount
// Entry: 8019cd80
// Size: 172 bytes

int CARDUnmount(int chan)

{
  int iVar1;
  undefined4 uVar2;
  CARDControl *apCStack_14 [2];
  
  iVar1 = __CARDGetControlBlock(chan,apCStack_14);
  if (-1 < iVar1) {
    uVar2 = OSDisableInterrupts();
    if ((&DAT_80327540)[chan * 0x44] != 0) {
      EXISetExiCallback(chan,0);
      EXIDetach(chan);
      OSCancelAlarm(&DAT_80327620 + chan * 0x110);
      (&DAT_80327540)[chan * 0x44] = 0;
      (&DAT_80327544)[chan * 0x44] = 0xfffffffd;
      *(undefined4 *)(&DAT_80327564 + chan * 0x110) = 0;
    }
    OSRestoreInterrupts(uVar2);
    iVar1 = 0;
  }
  return iVar1;
}

