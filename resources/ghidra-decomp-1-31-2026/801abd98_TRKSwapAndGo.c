// Function: TRKSwapAndGo
// Entry: 801abd98
// Size: 196 bytes

/* WARNING: This function may have set the stack pointer */

undefined4
TRKSwapAndGo(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 in_r0;
  undefined4 uVar1;
  undefined4 in_r11;
  undefined4 in_r12;
  undefined4 unaff_r14;
  undefined4 unaff_r15;
  undefined4 unaff_r16;
  undefined4 unaff_r17;
  undefined4 unaff_r18;
  undefined4 unaff_r19;
  undefined4 unaff_r20;
  undefined4 unaff_r21;
  undefined4 unaff_r22;
  undefined4 unaff_r23;
  undefined4 unaff_r24;
  undefined4 unaff_r25;
  undefined4 unaff_r26;
  undefined4 unaff_r27;
  undefined4 unaff_r28;
  undefined4 unaff_r29;
  undefined4 unaff_r30;
  undefined4 unaff_r31;
  uint in_MSR;
  uint uVar2;
  undefined4 in_XER;
  undefined4 in_LR;
  undefined4 in_CTR;
  undefined4 in_DSISR;
  undefined4 in_DAR;
  undefined4 in_SRR1;
  
  DAT_8032a12c = &DAT_80337600;
  DAT_8032a130 = &DAT_8032a124;
  DAT_8032a158 = 0x803363c0;
  uVar2 = in_MSR & 0x9000;
  DAT_8032a124 = in_r0;
  DAT_8032a128 = (undefined *)register0x00000004;
  DAT_8032a134 = param_2;
  DAT_8032a138 = param_3;
  DAT_8032a13c = param_4;
  DAT_8032a140 = param_5;
  DAT_8032a144 = param_6;
  DAT_8032a148 = param_7;
  DAT_8032a14c = param_8;
  DAT_8032a150 = in_r11;
  DAT_8032a154 = in_r12;
  DAT_8032a15c = unaff_r14;
  DAT_8032a160 = unaff_r15;
  DAT_8032a164 = unaff_r16;
  DAT_8032a168 = unaff_r17;
  DAT_8032a16c = unaff_r18;
  DAT_8032a170 = unaff_r19;
  DAT_8032a174 = unaff_r20;
  DAT_8032a178 = unaff_r21;
  DAT_8032a17c = unaff_r22;
  DAT_8032a180 = unaff_r23;
  DAT_8032a184 = unaff_r24;
  DAT_8032a188 = unaff_r25;
  DAT_8032a18c = unaff_r26;
  DAT_8032a190 = unaff_r27;
  DAT_8032a194 = unaff_r28;
  DAT_8032a198 = unaff_r29;
  DAT_8032a19c = unaff_r30;
  DAT_8032a1a0 = unaff_r31;
  DAT_8032a1a4 = in_LR;
  DAT_8032a1a8 = in_CTR;
  DAT_8032a1ac = in_XER;
  DAT_8032a1b0 = in_MSR;
  DAT_8032a1b4 = in_DAR;
  DAT_8032a1b8 = in_DSISR;
  if (*DAT_8032a1c4 != '\0') {
    DAT_8032a1c0 = 1;
    uVar1 = TRKInterruptHandlerEnableInterrupts();
    return uVar1;
  }
  DAT_8021cfe0 = 0;
  TRKRestoreExtended1Block();
  returnFromInterrupt(uVar2,in_SRR1);
  return DAT_8032a1d4;
}

