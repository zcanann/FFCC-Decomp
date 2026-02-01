// Function: PADClamp
// Entry: 8018d3c8
// Size: 276 bytes

void PADClamp(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if (*(char *)(param_1 + 10) == '\0') {
      ClampStick(param_1 + 2,param_1 + 3,DAT_801e6613,DAT_801e6614,DAT_801e6612);
      ClampStick(param_1 + 4,param_1 + 5,DAT_801e6616,DAT_801e6617,DAT_801e6615);
      if (DAT_801e6610 < *(byte *)(param_1 + 6)) {
        if (DAT_801e6611 < *(byte *)(param_1 + 6)) {
          *(byte *)(param_1 + 6) = DAT_801e6611;
        }
        *(byte *)(param_1 + 6) = *(char *)(param_1 + 6) - DAT_801e6610;
      }
      else {
        *(undefined *)(param_1 + 6) = 0;
      }
      if (DAT_801e6610 < *(byte *)(param_1 + 7)) {
        if (DAT_801e6611 < *(byte *)(param_1 + 7)) {
          *(byte *)(param_1 + 7) = DAT_801e6611;
        }
        *(byte *)(param_1 + 7) = *(char *)(param_1 + 7) - DAT_801e6610;
      }
      else {
        *(undefined *)(param_1 + 7) = 0;
      }
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 0xc;
  } while (iVar1 < 4);
  return;
}

