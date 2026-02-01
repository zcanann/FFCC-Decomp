// Function: TRKInterruptHandler
// Entry: 801abb68
// Size: 404 bytes

undefined4
TRKInterruptHandler(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                   undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 in_r0;
  uint uVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
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
  uint uVar3;
  byte in_cr0;
  byte in_cr1;
  byte in_cr2;
  byte in_cr3;
  byte unaff_cr4;
  byte in_cr5;
  byte in_cr6;
  byte in_cr7;
  undefined4 in_XER;
  undefined4 in_LR;
  undefined4 in_CTR;
  undefined *puVar4;
  undefined4 in_SPRG1;
  undefined4 in_SPRG2;
  undefined4 in_SPRG3;
  
  puVar4 = &DAT_80337600;
  uVar1 = (uint)(in_cr0 & 0xf) << 0x1c | (uint)(in_cr1 & 0xf) << 0x18 | (uint)(in_cr2 & 0xf) << 0x14
          | (uint)(in_cr3 & 0xf) << 0x10 | (uint)(unaff_cr4 & 0xf) << 0xc |
          (uint)(in_cr5 & 0xf) << 8 | (uint)(in_cr6 & 0xf) << 4 | (uint)(in_cr7 & 0xf);
  sync(0);
  uVar3 = in_MSR & 0x9000;
  sync(0);
  DAT_8032a120 = (undefined2)param_1;
  if (param_1 == 0x500) {
    DAT_8032a5f4 = in_LR;
    TRKUARTInterruptHandler();
    if ((*DAT_8032a1c4 == '\0') || (DAT_8021cfe0 == '\x01')) {
      returnFromInterrupt(uVar3,param_2);
      return DAT_8032a604;
    }
    DAT_8032a1c0 = 1;
    in_SPRG3 = extraout_r4;
    in_LR = DAT_8032a5f4;
  }
  if (DAT_8021cfe0 != '\0') {
    DAT_8021cfdc._0_2_ = DAT_8032a120;
    DAT_8021cfd4 = puVar4;
    DAT_8021cfe1 = 1;
    returnFromInterrupt(uVar3,param_2);
    return in_SPRG2;
  }
  DAT_8032a4c0._0_2_ = DAT_8032a120;
  DAT_8032a4c0._2_2_ = DAT_8032a120;
  DAT_8032a1fc = 0x803363c0;
  DAT_8032a1c8 = in_r0;
  DAT_8032a1cc = (undefined *)register0x00000004;
  DAT_8032a1d0 = in_SPRG1;
  DAT_8032a1d4 = in_SPRG2;
  DAT_8032a1d8 = in_SPRG3;
  DAT_8032a1dc = param_3;
  DAT_8032a1e0 = param_4;
  DAT_8032a1e4 = param_5;
  DAT_8032a1e8 = param_6;
  DAT_8032a1ec = param_7;
  DAT_8032a1f0 = param_8;
  DAT_8032a1f4 = in_r11;
  DAT_8032a1f8 = in_r12;
  DAT_8032a200 = unaff_r14;
  DAT_8032a204 = unaff_r15;
  DAT_8032a208 = unaff_r16;
  DAT_8032a20c = unaff_r17;
  DAT_8032a210 = unaff_r18;
  DAT_8032a214 = unaff_r19;
  DAT_8032a218 = unaff_r20;
  DAT_8032a21c = unaff_r21;
  DAT_8032a220 = unaff_r22;
  DAT_8032a224 = unaff_r23;
  DAT_8032a228 = unaff_r24;
  DAT_8032a22c = unaff_r25;
  DAT_8032a230 = unaff_r26;
  DAT_8032a234 = unaff_r27;
  DAT_8032a238 = unaff_r28;
  DAT_8032a23c = unaff_r29;
  DAT_8032a240 = unaff_r30;
  DAT_8032a244 = unaff_r31;
  DAT_8032a248 = puVar4;
  DAT_8032a24c = in_LR;
  DAT_8032a250 = uVar1;
  DAT_8032a254 = in_CTR;
  DAT_8032a258 = in_XER;
  TRKSaveExtended1Block();
  DAT_8021cfe0 = 1;
  sync(0);
  sync(0);
  uVar2 = TRKPostInterruptEvent
                    (DAT_8032a130,DAT_8032a134,DAT_8032a138,DAT_8032a13c,DAT_8032a140,DAT_8032a144,
                     DAT_8032a148,DAT_8032a14c);
  return uVar2;
}

