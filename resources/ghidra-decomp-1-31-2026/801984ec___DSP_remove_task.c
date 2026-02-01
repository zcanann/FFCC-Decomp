// Function: __DSP_remove_task
// Entry: 801984ec
// Size: 148 bytes

void __DSP_remove_task(undefined4 *param_1)

{
  param_1[2] = 0;
  *param_1 = 3;
  if (DAT_8032f2d8 != param_1) {
    if (DAT_8032f2d4 == param_1) {
      DAT_8032f2d4 = (undefined4 *)param_1[0xf];
      *(undefined4 *)(param_1[0xf] + 0x38) = 0;
      DAT_8032f2dc = DAT_8032f2d8;
      return;
    }
    DAT_8032f2dc = (undefined4 *)param_1[0xe];
    *(undefined4 *)(param_1[0xf] + 0x38) = param_1[0xe];
    *(undefined4 *)(param_1[0xe] + 0x3c) = param_1[0xf];
    return;
  }
  DAT_8032f2d8 = (undefined4 *)param_1[0xe];
  if (DAT_8032f2d8 != (undefined4 *)0x0) {
    *(undefined4 *)(param_1[0xe] + 0x3c) = 0;
    return;
  }
  DAT_8032f2dc = (undefined4 *)0x0;
  DAT_8032f2d4 = (undefined4 *)0x0;
  DAT_8032f2d8 = (undefined4 *)0x0;
  return;
}

