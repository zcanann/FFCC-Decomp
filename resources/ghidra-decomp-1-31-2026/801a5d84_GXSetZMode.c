// Function: GXSetZMode
// Entry: 801a5d84
// Size: 52 bytes

void GXSetZMode(uint param_1,uint param_2,uint param_3)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_80333828;
  DAT_cc008000._0_1_ = 0x61;
  uVar2 = (param_3 & 1) << 4 |
          (param_2 & 7) << 1 | param_1 & 1 | *(uint *)(DAT_80333828 + 0x1d8) & 0xffffffe0;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_80333828 + 0x1d8) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

