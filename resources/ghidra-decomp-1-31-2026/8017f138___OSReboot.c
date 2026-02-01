// Function: __OSReboot
// Entry: 8017f138
// Size: 832 bytes

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void __OSReboot(void)

{
  uint uVar1;
  uint uVar2;
  DVDDiskId *pDVar3;
  int iVar4;
  undefined8 uVar5;
  undefined8 uVar6;
  undefined auStack_370 [48];
  undefined auStack_340 [48];
  undefined auStack_310 [48];
  undefined auStack_2e0 [712];
  
  OSDisableInterrupts();
  _DAT_817ffffc = 0;
  _DAT_817ffff8 = 0;
  DAT_800030e2 = 1;
  _DAT_812fdff0 = DAT_8032ef98;
  _DAT_812fdfec = DAT_8032ef9c;
  OSClearContext(auStack_2e0);
  OSSetCurrentContext(auStack_2e0);
  DVDInit();
  DVDSetAutoInvalidation(1);
  DVDResume();
  DAT_8032efa0 = 0;
  __DVDPrepareResetAsync(Callback);
  __OSMaskInterrupts(0xffffffe0);
  __OSUnmaskInterrupts(0x400);
  OSEnableInterrupts();
  uVar5 = OSGetTime();
  uVar1 = DAT_800000f8 >> 2;
  while (DAT_8032efa0 != 1) {
    iVar4 = DVDCheckDisk();
    if ((iVar4 == 0) ||
       (uVar6 = OSGetTime(),
       0x80000000 <
       (uint)(uVar1 < (uint)uVar6 - (uint)uVar5) +
       ((int)((ulonglong)uVar6 >> 0x20) -
        ((uint)((uint)uVar6 < (uint)uVar5) + (int)((ulonglong)uVar5 >> 0x20)) ^ 0x80000000))) {
      __OSDoHotReset(_DAT_817ffffc);
    }
  }
  if ((DAT_8032ef2c == 0) && (pDVar3 = DVDGetCurrentDiskID(), pDVar3->streaming != '\0')) {
    AISetStreamVolLeft(0);
    AISetStreamVolRight(0);
    DVDCancelStreamAsync(auStack_310,0);
    uVar5 = OSGetTime();
    uVar1 = DAT_800000f8 >> 2;
    while (iVar4 = DVDGetCommandBlockStatus(auStack_310), iVar4 != 0) {
      iVar4 = DVDCheckDisk();
      if ((iVar4 == 0) ||
         (uVar6 = OSGetTime(),
         0x80000000 <
         (uint)(uVar1 < (uint)uVar6 - (uint)uVar5) +
         ((int)((ulonglong)uVar6 >> 0x20) -
          ((uint)((uint)uVar6 < (uint)uVar5) + (int)((ulonglong)uVar5 >> 0x20)) ^ 0x80000000))) {
        __OSDoHotReset(_DAT_817ffffc);
      }
    }
    AISetStreamPlayState(0);
  }
  DVDReadAbsAsyncPrio(auStack_340,FatalParam,0x20,0x2440,0,0);
  uVar5 = OSGetTime();
  uVar1 = DAT_800000f8 >> 2;
  while (iVar4 = DVDGetCommandBlockStatus(auStack_340), iVar4 != 0) {
    iVar4 = DVDCheckDisk();
    if ((iVar4 == 0) ||
       (uVar6 = OSGetTime(),
       0x80000000 <
       (uint)(uVar1 < (uint)uVar6 - (uint)uVar5) +
       ((int)((ulonglong)uVar6 >> 0x20) -
        ((uint)((uint)uVar6 < (uint)uVar5) + (int)((ulonglong)uVar5 >> 0x20)) ^ 0x80000000))) {
      __OSDoHotReset(_DAT_817ffffc);
    }
  }
  uVar2 = FatalContext[1] + 0x1fU & 0xffffffe0;
  DVDReadAbsAsyncPrio(auStack_370,0x81300000,uVar2,FatalContext[0] + 0x2460,0,0);
  uVar5 = OSGetTime();
  uVar1 = DAT_800000f8 >> 2;
  while (iVar4 = DVDGetCommandBlockStatus(auStack_370), iVar4 != 0) {
    iVar4 = DVDCheckDisk();
    if ((iVar4 == 0) ||
       (uVar6 = OSGetTime(),
       0x80000000 <
       (uint)(uVar1 < (uint)uVar6 - (uint)uVar5) +
       ((int)((ulonglong)uVar6 >> 0x20) -
        ((uint)((uint)uVar6 < (uint)uVar5) + (int)((ulonglong)uVar5 >> 0x20)) ^ 0x80000000))) {
      __OSDoHotReset(_DAT_817ffffc);
    }
  }
  ICInvalidateRange(0x81300000,uVar2);
  OSDisableInterrupts();
  ICFlashInvalidate();
  Run(0x81300000);
  return;
}

