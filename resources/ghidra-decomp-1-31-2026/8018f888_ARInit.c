// Function: ARInit
// Entry: 8018f888
// Size: 196 bytes

undefined4 ARInit(undefined4 param_1,undefined4 param_2)

{
  ushort uVar1;
  ushort uVar2;
  undefined4 uVar3;
  
  if (DAT_8032f1bc == 1) {
    uVar3 = 0x4000;
  }
  else {
    OSRegisterVersion(DAT_8032eb40);
    uVar3 = OSDisableInterrupts();
    DAT_8032f1a0 = 0;
    __OSSetInterruptHandler(6,__ARHandler);
    __OSUnmaskInterrupts(0x2000000);
    DAT_8032f1b0 = 0x4000;
    uVar1 = DAT_cc00501a;
    uVar2 = DAT_cc00501a;
    DAT_cc00501a = uVar2 & 0xff | uVar1 & 0xff00;
    DAT_8032f1b4 = param_2;
    DAT_8032f1b8 = param_1;
    __ARChecksize();
    DAT_8032f1bc = 1;
    OSRestoreInterrupts(uVar3);
    uVar3 = DAT_8032f1b0;
  }
  return uVar3;
}

