// Function: OSInit
// Entry: 8017b948
// Size: 984 bytes

void OSInit(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  
  if (DAT_8032ef40 != 0) {
    return;
  }
  DAT_8032ef40 = 1;
  uVar6 = __OSGetSystemTime();
  DAT_8032ef58 = (undefined4)((ulonglong)uVar6 >> 0x20);
  DAT_8032ef5c = (undefined4)uVar6;
  OSDisableInterrupts();
  PPCMtmmcr0(0);
  PPCMtmmcr1(0);
  PPCMtpmc1(0);
  PPCMtpmc2(0);
  PPCMtpmc3(0);
  PPCMtpmc4(0);
  PPCDisableSpeculation();
  PPCSetFpNonIEEEMode();
  DAT_8032ef24 = (uint *)0x0;
  DAT_8032ef20 = -0x80000000;
  if (DAT_800000f4 == 0) {
    if (DAT_80000034 != 0) {
      DAT_8032ef28 = (uint)DAT_800030e8._0_1_;
      DAT_8032ef24 = &DAT_8032ef28;
      DAT_8032f15c = (uint)DAT_800030e8._1_1_;
    }
  }
  else {
    DAT_8032ef24 = (uint *)(DAT_800000f4 + 0xc);
    DAT_8032f15c = *(uint *)(DAT_800000f4 + 0x24);
    DAT_800030e8._0_1_ = (byte)*DAT_8032ef24;
    DAT_800030e8._1_1_ = (byte)DAT_8032f15c;
  }
  DAT_8032f074 = 1;
  iVar2 = DAT_80000030;
  if (DAT_80000030 == 0) {
    iVar2 = -0x7fc8a1e0;
  }
  OSSetArenaLo(iVar2);
  if (((*(int *)(DAT_8032ef20 + 0x30) == 0) && (DAT_8032ef24 != (uint *)0x0)) && (*DAT_8032ef24 < 2)
     ) {
    OSSetArenaLo(0x80373e20);
  }
  iVar2 = *(int *)(DAT_8032ef20 + 0x34);
  if (iVar2 == 0) {
    iVar2 = -0x7e900000;
  }
  OSSetArenaHi(iVar2);
  OSExceptionInit();
  __OSInitSystemCall();
  OSInitAlarm();
  __OSModuleInit();
  __OSInterruptInit();
  __OSSetInterruptHandler(0x16,__OSResetSWInterruptHandler);
  __OSContextInit();
  __OSCacheInit();
  EXIInit();
  SIInit();
  __OSInitSram();
  __OSThreadInit();
  __OSInitAudioSystem();
  uVar3 = PPCMfhid2();
  PPCMthid2(uVar3 & 0xbfffffff);
  if (DAT_8032ef50 == 0) {
    __OSInitMemoryProtection();
  }
  OSReport(s_Dolphin_OS_802167b4);
  OSReport(s_Kernel_built____s__s_802167c4,s_Mar_17_2003_802167dc,s_04_20_41_802167e8);
  OSReport(s_Console_Type___802167f4);
  if ((DAT_8032ef20 == 0) || (uVar3 = *(uint *)(DAT_8032ef20 + 0x2c), uVar3 == 0)) {
    uVar3 = 0x10000002;
  }
  uVar1 = uVar3 & 0xf0000000;
  if (uVar1 == 0x10000000) {
LAB_8017bbb0:
    uVar1 = uVar3 & 0xfffffff;
    if (uVar1 == 0x10000002) {
      OSReport(s_EPPC_Arthur_80216830);
    }
    else {
      if (uVar1 < 0x10000002) {
        if (uVar1 == 0x10000000) {
          OSReport(s_Mac_Emulator_80216810);
          goto LAB_8017bc50;
        }
        if (0xfffffff < uVar1) {
          OSReport(s_PC_Emulator_80216820);
          goto LAB_8017bc50;
        }
      }
      else if (uVar1 < 0x10000004) {
        OSReport(s_EPPC_Minnow_80216840);
        goto LAB_8017bc50;
      }
      OSReport(s_Development_HW_d___08x__80216850,(uVar3 & 0xfffffff) - 3,uVar3);
    }
  }
  else {
    if ((int)uVar1 < 0x10000000) {
      if (uVar1 == 0) {
        OSReport(s_Retail__d_80216804);
        goto LAB_8017bc50;
      }
    }
    else if (uVar1 == 0x20000000) goto LAB_8017bbb0;
    OSReport(&DAT_8032ea84);
  }
LAB_8017bc50:
  OSReport(s_Memory__d_MB_8021686c,*(uint *)(DAT_8032ef20 + 0x28) >> 0x14);
  uVar4 = OSGetArenaHi();
  uVar5 = OSGetArenaLo();
  OSReport(s_Arena___0x_x___0x_x_8021687c,uVar5,uVar4);
  OSRegisterVersion(DAT_8032ea80);
  if ((DAT_8032ef24 != (uint *)0x0) && (1 < *DAT_8032ef24)) {
    EnableMetroTRKInterrupts();
  }
  ClearArena();
  OSEnableInterrupts();
  if (DAT_8032ef50 == 0) {
    DVDInit();
    if (DAT_8032ef2c == 0) {
      DCInvalidateRange(&DriveInfo,0x20);
      DVDInquiryAsync(&DriveBlock,&DriveInfo,InquiryCallback);
    }
    else {
      DAT_800030e6 = 0x9000;
    }
  }
  return;
}

