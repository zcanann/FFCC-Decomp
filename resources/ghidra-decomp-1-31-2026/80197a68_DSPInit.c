// Function: DSPInit
// Entry: 80197a68
// Size: 196 bytes

void DSPInit(void)

{
  ushort uVar1;
  undefined4 uVar2;
  
  __DSP_debug_printf(s_DSPInit____Build_Date___s__s_8021c000,s_Sep_5_2002_8021c020,
                     s_05_35_13_8021c02c);
  if (DAT_8032f2c0 != 1) {
    OSRegisterVersion(PTR_s_<<_Dolphin_SDK___DSP_release_bui_8032eb68);
    uVar2 = OSDisableInterrupts();
    __OSSetInterruptHandler(7,__DSPHandler);
    __OSUnmaskInterrupts(0x1000000);
    uVar1 = DAT_cc00500a;
    DAT_cc00500a = uVar1 & 0xff57 | 0x800;
    uVar1 = DAT_cc00500a;
    DAT_cc00500a = uVar1 & 0xff53;
    DAT_8032f2d0 = 0;
    DAT_8032f2dc = 0;
    DAT_8032f2d4 = 0;
    DAT_8032f2d8 = 0;
    DAT_8032f2c0 = 1;
    OSRestoreInterrupts(uVar2);
  }
  return;
}

