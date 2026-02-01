// Function: OSDefaultExceptionHandler
// Entry: 8017c094
// Size: 88 bytes

void OSDefaultExceptionHandler
               (undefined4 param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4,
               undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined4 in_r0;
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
  
  *param_2 = in_r0;
  param_2[1] = register0x00000004;
  param_2[2] = &DAT_80337600;
  param_2[6] = param_4;
  param_2[7] = param_5;
  param_2[8] = param_6;
  param_2[9] = param_7;
  param_2[10] = param_8;
  param_2[0xb] = in_r11;
  param_2[0xc] = in_r12;
  param_2[0xd] = 0x803363c0;
  param_2[0xe] = unaff_r14;
  param_2[0xf] = unaff_r15;
  param_2[0x10] = unaff_r16;
  param_2[0x11] = unaff_r17;
  param_2[0x12] = unaff_r18;
  param_2[0x13] = unaff_r19;
  param_2[0x14] = unaff_r20;
  param_2[0x15] = unaff_r21;
  param_2[0x16] = unaff_r22;
  param_2[0x17] = unaff_r23;
  param_2[0x18] = unaff_r24;
  param_2[0x19] = unaff_r25;
  param_2[0x1a] = unaff_r26;
  param_2[0x1b] = unaff_r27;
  param_2[0x1c] = unaff_r28;
  param_2[0x1d] = unaff_r29;
  param_2[0x1e] = unaff_r30;
  param_2[0x1f] = unaff_r31;
  param_2[0x6a] = 0;
  param_2[0x6b] = 0;
  param_2[0x6c] = 0;
  param_2[0x6d] = 0;
  param_2[0x6e] = 0;
  param_2[0x6f] = 0;
  param_2[0x70] = 0;
  __OSUnhandledException();
  return;
}

