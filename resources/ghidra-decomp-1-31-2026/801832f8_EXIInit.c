// Function: EXIInit
// Entry: 801832f8
// Size: 468 bytes

void EXIInit(void)

{
  uint uVar1;
  int iVar2;
  int local_18 [2];
  
  do {
    do {
      uVar1 = DAT_cc00680c;
    } while ((uVar1 & 1) == 1);
    uVar1 = DAT_cc006820;
  } while (((uVar1 & 1) == 1) || (uVar1 = DAT_cc006834, (uVar1 & 1) == 1));
  __OSMaskInterrupts(0x7f8000);
  DAT_cc006800 = 0;
  DAT_cc006814 = 0;
  DAT_cc006828 = 0;
  DAT_cc006800 = 0x2000;
  __OSSetInterruptHandler(9,EXIIntrruptHandler);
  __OSSetInterruptHandler(10,TCIntrruptHandler);
  __OSSetInterruptHandler(0xb,EXTIntrruptHandler);
  __OSSetInterruptHandler(0xc,EXIIntrruptHandler);
  __OSSetInterruptHandler(0xd,TCIntrruptHandler);
  __OSSetInterruptHandler(0xe,EXTIntrruptHandler);
  __OSSetInterruptHandler(0xf,EXIIntrruptHandler);
  __OSSetInterruptHandler(0x10,TCIntrruptHandler);
  EXIGetID(0,2,&DAT_8032efe8);
  if (DAT_8032ef50 == 0) {
    iVar2 = EXIGetID(0,0,local_18);
    if ((iVar2 == 0) || (local_18[0] != 0x7010000)) {
      iVar2 = EXIGetID(1,0,local_18);
      if ((iVar2 != 0) && (local_18[0] == 0x7010000)) {
        __OSEnableBarnacle(0,2);
      }
    }
    else {
      __OSEnableBarnacle(1,0);
    }
  }
  else {
    DAT_800030c4 = 0;
    DAT_800030c0 = 0;
    FatalContext[0x2af] = 0;
    FatalContext[0x29f] = 0;
    __EXIProbe(0);
    __EXIProbe(1);
  }
  OSRegisterVersion(DAT_8032eab8);
  return;
}

