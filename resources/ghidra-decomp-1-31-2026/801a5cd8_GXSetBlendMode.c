// Function: GXSetBlendMode
// Entry: 801a5cd8
// Size: 84 bytes

void GXSetBlendMode(uint param_1,uint param_2,uint param_3,uint param_4)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = DAT_80333828;
  uVar3 = countLeadingZeros(3 - param_1);
  uVar2 = countLeadingZeros(2 - param_1);
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = (param_3 & 7) << 5 |
          (param_2 & 7) << 8 |
          (param_4 & 0xf) << 0xc |
          uVar2 >> 4 & 2 |
          param_1 & 1 | (uVar3 & 0x20) << 6 | *(uint *)(DAT_80333828 + 0x1d0) & 0xffff001c;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_80333828 + 0x1d0) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

