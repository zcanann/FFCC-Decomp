// Function: GXSetTevColorIn
// Entry: 801a5264
// Size: 68 bytes

void GXSetTevColorIn(int param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = DAT_80333828;
  iVar3 = DAT_80333828 + param_1 * 4;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = param_5 & 0xf |
          (param_4 & 0xf) << 4 |
          (param_3 & 0xf) << 8 | (param_2 & 0xf) << 0xc | *(uint *)(iVar3 + 0x130) & 0xffff0000;
  DAT_cc008000 = uVar2;
  *(uint *)(iVar3 + 0x130) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

