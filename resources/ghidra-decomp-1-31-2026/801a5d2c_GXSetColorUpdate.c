// Function: GXSetColorUpdate
// Entry: 801a5d2c
// Size: 44 bytes

void GXSetColorUpdate(uint param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_80333828;
  uVar2 = (param_1 & 1) << 3 | *(uint *)(DAT_80333828 + 0x1d0) & 0xfffffff7;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = uVar2;
  *(uint *)(DAT_80333828 + 0x1d0) = uVar2;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

