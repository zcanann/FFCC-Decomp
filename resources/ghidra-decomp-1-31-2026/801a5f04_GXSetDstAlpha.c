// Function: GXSetDstAlpha
// Entry: 801a5f04
// Size: 60 bytes

void GXSetDstAlpha(uint param_1,uint param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_80333828;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = (param_1 & 1) << 8 | param_2 & 0xff | *(uint *)(DAT_80333828 + 0x1d4) & 0xfffffe00;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_80333828 + 0x1d4) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

