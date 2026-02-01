// Function: SetDiffuse__9CCharaPcsFiUlP8_GXColorP3Vec
// Entry: 800b96f8
// Size: 92 bytes

void SetDiffuse__9CCharaPcsFiUlP8_GXColorP3Vec
               (int param_1,int param_2,int param_3,undefined *param_4,undefined4 *param_5)

{
  int iVar1;
  
  iVar1 = param_1 + param_2 * 0xc + param_3 * 4;
  *(undefined *)(iVar1 + 0xf0) = *param_4;
  *(undefined *)(iVar1 + 0xf1) = param_4[1];
  *(undefined *)(iVar1 + 0xf2) = param_4[2];
  *(undefined *)(iVar1 + 0xf3) = param_4[3];
  if (param_2 != 0) {
    return;
  }
  param_1 = param_1 + param_3 * 0xc;
  *(undefined4 *)(param_1 + 0x108) = *param_5;
  *(undefined4 *)(param_1 + 0x10c) = param_5[1];
  *(undefined4 *)(param_1 + 0x110) = param_5[2];
  return;
}

