// Function: GXSetChanCtrl
// Entry: 801a3aac
// Size: 204 bytes

void GXSetChanCtrl(uint param_1,uint param_2,int param_3,uint param_4,uint param_5,int param_6,
                  int param_7)

{
  int iVar1;
  uint uVar2;
  
  if (param_7 == 0) {
    param_6 = 0;
  }
  iVar1 = -param_7 + 2;
  DAT_cc008000._0_1_ = 0x10;
  uVar2 = (param_5 & 0xf0) << 7 |
          (param_5 & 0xf) << 2 |
          (((((param_2 & 0xff) << 1 | param_4) & 0xffffffbf | param_3 << 6) & 0xfffffe7f |
           param_6 << 7) & 0xfffffdff | (iVar1 - ((uint)(iVar1 == 0) + -param_7 + 1)) * 0x200) &
          0xffff83c3 | (uint)(param_7 != 0) * 0x400;
  DAT_cc008000 = (param_1 & 3) + 0x100e;
  DAT_cc008000 = uVar2;
  if (param_1 == 4) {
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1010;
    DAT_cc008000 = uVar2;
  }
  else if (param_1 == 5) {
    DAT_cc008000._0_1_ = 0x10;
    DAT_cc008000 = 0x1011;
    DAT_cc008000 = uVar2;
  }
  *(undefined2 *)(DAT_80333828 + 2) = 1;
  return;
}

