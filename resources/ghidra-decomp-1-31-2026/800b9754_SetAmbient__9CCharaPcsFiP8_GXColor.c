// Function: SetAmbient__9CCharaPcsFiP8_GXColor
// Entry: 800b9754
// Size: 44 bytes

void SetAmbient__9CCharaPcsFiP8_GXColor(int param_1,int param_2,undefined *param_3)

{
  param_1 = param_1 + param_2 * 4;
  *(undefined *)(param_1 + 0xe8) = *param_3;
  *(undefined *)(param_1 + 0xe9) = param_3[1];
  *(undefined *)(param_1 + 0xea) = param_3[2];
  *(undefined *)(param_1 + 0xeb) = param_3[3];
  return;
}

