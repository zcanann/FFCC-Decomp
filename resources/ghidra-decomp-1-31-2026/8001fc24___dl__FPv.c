// Function: __dl__FPv
// Entry: 8001fc24
// Size: 284 bytes

void __dl__FPv(int param_1)

{
  int iVar1;
  
  if (param_1 != 0) {
    if ((*(short *)(param_1 + -0x40) != 0x4b41) || (*(short *)(param_1 + -2) != 0x4d49)) {
      Printf__7CSystemFPce
                (&System,&DAT_801d6648,param_1,param_1 + -0x26,*(undefined2 *)(param_1 + -0x28));
    }
    *(byte *)(param_1 + -0x3e) = *(byte *)(param_1 + -0x3e) & 0xfb;
    if ((*(byte *)(*(int *)(param_1 + -0x38) + 2) & 4) == 0) {
      *(int *)(param_1 + -0x30) =
           *(int *)(*(int *)(param_1 + -0x38) + 0x10) + *(int *)(param_1 + -0x30) + 0x40;
      *(int *)(*(int *)(*(int *)(param_1 + -0x38) + 8) + 4) = param_1 + -0x40;
      *(undefined4 *)(param_1 + -0x38) = *(undefined4 *)(*(int *)(param_1 + -0x38) + 8);
    }
    iVar1 = *(int *)(param_1 + -0x3c);
    if ((*(byte *)(iVar1 + 2) & 4) == 0) {
      *(int *)(iVar1 + 0x10) = *(int *)(param_1 + -0x30) + *(int *)(iVar1 + 0x10) + 0x40;
      *(undefined4 *)(*(int *)(param_1 + -0x3c) + 8) = *(undefined4 *)(param_1 + -0x38);
      *(undefined4 *)(*(int *)(param_1 + -0x38) + 4) = *(undefined4 *)(param_1 + -0x3c);
    }
    *(int *)(*(int *)(param_1 + -0x34) + 0x124) = *(int *)(*(int *)(param_1 + -0x34) + 0x124) + -1;
    return;
  }
  return;
}

