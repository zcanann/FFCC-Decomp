// Function: PADInit
// Entry: 8018de3c
// Size: 536 bytes

undefined4 PADInit(void)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 uVar3;
  short extraout_r4;
  short extraout_r4_00;
  short extraout_r4_01;
  uint uVar4;
  undefined8 uVar5;
  
  if (DAT_8032f138 == 0) {
    OSRegisterVersion(DAT_8032eb18);
    if (DAT_8032f15c != 0) {
      PADSetSpec();
    }
    DAT_8032f138 = 1;
    if (DAT_8032f008 != 0) {
      uVar5 = OSGetTime();
      uVar1 = (undefined4)((ulonglong)uVar5 >> 0x20);
      uVar3 = (undefined4)uVar5;
      __shr2i(uVar1,uVar3,0x10);
      __shr2i(uVar1,uVar3,0x20);
      __shr2i(uVar1,uVar3,0x30);
      DAT_8032f144 = 0xf0000000;
      DAT_800030e0 = extraout_r4_01 + extraout_r4_00 + (short)uVar5 + extraout_r4 & 0x3fff;
    }
    DAT_8030ccd0 = (DAT_800030e0 & 0x3fff) << 8 | 0x4d000000;
    DAT_8030ccd4 = (DAT_800030e0 & 0x3fff) << 8 | 0x4d400000;
    DAT_8030ccd8 = (DAT_800030e0 & 0x3fff) << 8 | 0x4d800000;
    DAT_8030ccdc = (DAT_800030e0 & 0x3fff) << 8 | 0x4dc00000;
    SIRefreshSamplingRate();
    OSRegisterResetFunction(&PTR_OnReset_80217bf8);
    uVar1 = OSDisableInterrupts();
    uVar4 = (DAT_8032f150 | 0xf0000000) & ~(DAT_8032f148 | DAT_8032f14c);
    DAT_8032f140 = DAT_8032f140 | uVar4;
    DAT_8032f150 = 0;
    uVar2 = DAT_8032f140 & DAT_8032f13c;
    if (DAT_8032eb28 == 4) {
      DAT_8032f144 = DAT_8032f144 | uVar4;
    }
    DAT_8032f13c = DAT_8032f13c & ~uVar4;
    SIDisablePolling(uVar2);
    if ((DAT_8032eb1c == 0x20) &&
       (DAT_8032eb1c = countLeadingZeros(DAT_8032f140), DAT_8032eb1c != 0x20)) {
      DAT_8032f140 = DAT_8032f140 & ~(0x80000000U >> DAT_8032eb1c);
      memset(&DAT_8030cca0 + DAT_8032eb1c * 0xc,0,0xc);
      SIGetTypeAsync(DAT_8032eb1c,PADTypeAndStatusCallback);
    }
    OSRestoreInterrupts(uVar1);
  }
  return 1;
}

