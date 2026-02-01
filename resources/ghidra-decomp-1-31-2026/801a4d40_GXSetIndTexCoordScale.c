// Function: GXSetIndTexCoordScale
// Entry: 801a4d40
// Size: 380 bytes

void GXSetIndTexCoordScale(int param_1,uint param_2,int param_3)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  if (param_1 == 2) {
    *(uint *)(DAT_80333828 + 300) = *(uint *)(DAT_80333828 + 300) & 0xfffffff0 | param_2;
    *(uint *)(iVar1 + 300) = *(uint *)(iVar1 + 300) & 0xffffff0f | param_3 << 4;
    *(uint *)(iVar1 + 300) = *(uint *)(iVar1 + 300) & 0xffffff | 0x26000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar1 + 300);
  }
  else if (param_1 < 2) {
    if (param_1 == 0) {
      *(uint *)(DAT_80333828 + 0x128) = *(uint *)(DAT_80333828 + 0x128) & 0xfffffff0 | param_2;
      *(uint *)(iVar1 + 0x128) = *(uint *)(iVar1 + 0x128) & 0xffffff0f | param_3 << 4;
      *(uint *)(iVar1 + 0x128) = *(uint *)(iVar1 + 0x128) & 0xffffff | 0x25000000;
      DAT_cc008000._0_1_ = 0x61;
      DAT_cc008000 = *(undefined4 *)(iVar1 + 0x128);
    }
    else if (-1 < param_1) {
      *(uint *)(DAT_80333828 + 0x128) = *(uint *)(DAT_80333828 + 0x128) & 0xfffff0ff | param_2 << 8;
      *(uint *)(iVar1 + 0x128) = *(uint *)(iVar1 + 0x128) & 0xffff0fff | param_3 << 0xc;
      *(uint *)(iVar1 + 0x128) = *(uint *)(iVar1 + 0x128) & 0xffffff | 0x25000000;
      DAT_cc008000._0_1_ = 0x61;
      DAT_cc008000 = *(undefined4 *)(iVar1 + 0x128);
    }
  }
  else if (param_1 < 4) {
    *(uint *)(DAT_80333828 + 300) = *(uint *)(DAT_80333828 + 300) & 0xfffff0ff | param_2 << 8;
    *(uint *)(iVar1 + 300) = *(uint *)(iVar1 + 300) & 0xffff0fff | param_3 << 0xc;
    *(uint *)(iVar1 + 300) = *(uint *)(iVar1 + 300) & 0xffffff | 0x26000000;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar1 + 300);
  }
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

