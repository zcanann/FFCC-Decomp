// Function: CARDInit
// Entry: 801993f4
// Size: 172 bytes

void CARDInit(void)

{
  int iVar1;
  undefined4 *puVar2;
  
  puVar2 = &DAT_80327540;
  if ((DAT_8032764c == 0) || (DAT_8032775c == 0)) {
    DAT_8032f2e0 = FUN_8017e2e8();
    OSRegisterVersion(DAT_8032eb70);
    DSPInit();
    OSInitAlarm();
    iVar1 = 0;
    do {
      puVar2[1] = 0xfffffffd;
      OSInitThreadQueue(puVar2 + 0x23);
      OSCreateAlarm(puVar2 + 0x38);
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 0x44;
    } while (iVar1 < 2);
    __CARDSetDiskID(&DVDDiskId_80000000);
    OSRegisterResetFunction(&PTR_OnReset_8021c1c0);
  }
  return;
}

