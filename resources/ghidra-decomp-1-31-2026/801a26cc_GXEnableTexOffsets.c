// Function: GXEnableTexOffsets
// Entry: 801a26cc
// Size: 92 bytes

void GXEnableTexOffsets(int param_1,uint param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_80333828;
  param_1 = param_1 * 4;
  iVar2 = DAT_80333828 + param_1;
  *(uint *)(DAT_80333828 + param_1 + 0xb8) =
       *(uint *)(DAT_80333828 + param_1 + 0xb8) & 0xfffbffff | (param_2 & 0xff) << 0x12;
  *(uint *)(iVar2 + 0xb8) = *(uint *)(iVar2 + 0xb8) & 0xfff7ffff | (param_3 & 0xff) << 0x13;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar1 + param_1 + 0xb8);
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

