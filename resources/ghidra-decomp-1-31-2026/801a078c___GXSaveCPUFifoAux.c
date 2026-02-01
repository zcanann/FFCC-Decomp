// Function: __GXSaveCPUFifoAux
// Entry: 801a078c
// Size: 220 bytes

void __GXSaveCPUFifoAux(int *param_1)

{
  undefined4 uVar1;
  
  uVar1 = OSDisableInterrupts();
  GXFlush();
  *param_1 = *(int *)(DAT_8032f2e8 + 0xc) + -0x80000000;
  param_1[1] = *(int *)(DAT_8032f2e8 + 0x10) + -0x80000000;
  param_1[6] = (*(uint *)(DAT_8032f2e8 + 0x14) & 0xfbffffff) + 0x80000000;
  if (DAT_8032f31c == '\0') {
    param_1[7] = param_1[6] - param_1[5];
    if (param_1[7] < 0) {
      param_1[7] = param_1[7] + param_1[2];
    }
  }
  else {
    param_1[5] = CONCAT22(*(undefined2 *)(DAT_8032f2ec + 0x3a),*(undefined2 *)(DAT_8032f2ec + 0x38))
                 + -0x80000000;
    param_1[7] = CONCAT22(*(undefined2 *)(DAT_8032f2ec + 0x32),*(undefined2 *)(DAT_8032f2ec + 0x30))
    ;
  }
  OSRestoreInterrupts(uVar1);
  return;
}

