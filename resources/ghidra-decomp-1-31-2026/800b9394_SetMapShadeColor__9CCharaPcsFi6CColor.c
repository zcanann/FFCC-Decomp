// Function: SetMapShadeColor__9CCharaPcsFi6CColor
// Entry: 800b9394
// Size: 44 bytes

void SetMapShadeColor__9CCharaPcsFi6CColor(int param_1,int param_2,undefined *param_3)

{
  undefined uVar1;
  undefined uVar2;
  
  param_1 = param_1 + param_2 * 4;
  uVar1 = param_3[1];
  *(undefined *)(param_1 + 300) = *param_3;
  uVar2 = param_3[2];
  *(undefined *)(param_1 + 0x12d) = uVar1;
  uVar1 = param_3[3];
  *(undefined *)(param_1 + 0x12e) = uVar2;
  *(undefined *)(param_1 + 0x12f) = uVar1;
  return;
}

