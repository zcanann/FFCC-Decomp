// Function: __OSUnhandledException
// Entry: 8017e000
// Size: 744 bytes

void __OSUnhandledException(byte param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  undefined4 extraout_r4;
  undefined8 uVar6;
  
  uVar6 = OSGetTime();
  if ((*(uint *)(param_2 + 0x19c) & 2) == 0) {
    OSReport(s_Non_recoverable_Exception__d_80216e4c,param_1);
  }
  else {
    if (((param_1 == 6) && ((*(uint *)(param_2 + 0x19c) & 0x100000) != 0)) &&
       (__OSErrorTable._64_4_ != 0)) {
      param_1 = 0x10;
      uVar4 = PPCMfmsr();
      PPCMtmsr(uVar4 | 0x2000);
      if (DAT_800000d8 != 0) {
        OSSaveFPUContext();
      }
      uVar5 = PPCMffpscr();
      PPCMtfpscr(uVar5 & 0x6005f8ff);
      PPCMtmsr(uVar4);
      if (DAT_800000d8 == param_2) {
        OSDisableScheduler();
        (*(code *)__OSErrorTable._64_4_)(0x10,param_2,param_3,param_4);
        *(uint *)(param_2 + 0x19c) = *(uint *)(param_2 + 0x19c) & 0xffffdfff;
        DAT_800000d8 = 0;
        *(uint *)(param_2 + 0x194) = *(uint *)(param_2 + 0x194) & 0x6005f8ff;
        OSEnableScheduler();
        __OSReschedule();
      }
      else {
        *(uint *)(param_2 + 0x19c) = *(uint *)(param_2 + 0x19c) & 0xffffdfff;
        DAT_800000d8 = 0;
      }
      OSLoadContext(param_2);
    }
    if (*(int *)(__OSErrorTable + (uint)param_1 * 4) != 0) {
      OSDisableScheduler();
      (**(code **)(__OSErrorTable + (uint)param_1 * 4))(param_1,param_2,param_3,param_4);
      OSEnableScheduler();
      __OSReschedule();
      OSLoadContext(param_2);
    }
    if (param_1 == 8) {
      OSLoadContext(param_2);
    }
    OSReport(s_Unhandled_Exception__d_80216e6c,param_1);
  }
  OSReport(&DAT_8032eaa4);
  OSDumpContext(param_2);
  OSReport(s_DSISR___0x_08x_DAR___0x_08x_80216e84,param_3,param_4);
  OSReport(s_TB___0x_016llx_80216eb8,extraout_r4,(int)((ulonglong)uVar6 >> 0x20),(int)uVar6);
  switch(param_1) {
  case 2:
    OSReport(s_Instruction_at_0x_x__read_from_S_80216ec8,*(undefined4 *)(param_2 + 0x198),param_4);
    break;
  case 3:
    OSReport(s_Attempted_to_fetch_instruction_f_80216f28,*(undefined4 *)(param_2 + 0x198));
    break;
  case 5:
    OSReport(s_Instruction_at_0x_x__read_from_S_80216f74,*(undefined4 *)(param_2 + 0x198),param_4);
    break;
  case 6:
    OSReport(s_Program_exception___Possible_ill_80216fd8,*(undefined4 *)(param_2 + 0x198),param_4);
    break;
  case 0xf:
    OSReport(&DAT_8032eaa4);
    uVar1 = DAT_cc005030;
    uVar2 = DAT_cc005032;
    OSReport(s_AI_DMA_Address___0x_04x_04x_80217038,uVar1,uVar2);
    uVar1 = DAT_cc005020;
    uVar2 = DAT_cc005022;
    OSReport(s_ARAM_DMA_Address___0x_04x_04x_80217058,uVar1,uVar2);
    uVar3 = DAT_cc006014;
    OSReport(s_DI_DMA_Address___0x_08x_80217078,uVar3);
  }
  OSReport(s_Last_interrupt___d___SRR0___0x_0_80217094,(int)DAT_8032ef88,
           OSAlarm_8032ef60.start._4_4_);
  PPCHalt();
  return;
}

