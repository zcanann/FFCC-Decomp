// Function: GXSetTevAlphaOp
// Entry: 801a5354
// Size: 104 bytes

void GXSetTevAlphaOp(int param_1,uint param_2,uint param_3,uint param_4,uint param_5,uint param_6)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  
  iVar1 = DAT_80333828;
  uVar2 = *(uint *)(DAT_80333828 + param_1 * 4 + 0x170);
  uVar3 = (param_2 & 1) << 0x12;
  if ((int)param_2 < 2) {
    uVar3 = (param_3 & 3) << 0x10 | (param_4 & 3) << 0x14 | uVar3 | uVar2 & 0xffc8ffff;
  }
  else {
    uVar3 = (param_2 & 6) << 0x13 | uVar3 | uVar2 & 0xffc8ffff | 0x30000;
  }
  DAT_cc008000._0_1_ = 0x61;
  uVar3 = (param_6 & 3) << 0x16 | (param_5 & 1) << 0x13 | uVar3 & 0xff37ffff;
  DAT_cc008000 = uVar3;
  *(uint *)(DAT_80333828 + param_1 * 4 + 0x170) = uVar3;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

