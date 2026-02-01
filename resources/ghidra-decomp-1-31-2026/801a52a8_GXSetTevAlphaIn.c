// Function: GXSetTevAlphaIn
// Entry: 801a52a8
// Size: 68 bytes

void GXSetTevAlphaIn(int param_1,uint param_2,uint param_3,uint param_4,uint param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = DAT_80333828;
  iVar3 = DAT_80333828 + param_1 * 4;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = (param_5 & 7) << 4 |
          (param_4 & 7) << 7 |
          (param_3 & 7) << 10 | (param_2 & 7) << 0xd | *(uint *)(iVar3 + 0x170) & 0xffff000f;
  DAT_cc008000 = uVar2;
  *(uint *)(iVar3 + 0x170) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

