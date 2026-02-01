// Function: GXCopyTex
// Entry: 801a333c
// Size: 380 bytes

void GXCopyTex(uint param_1,byte param_2)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = DAT_80333828;
  if (param_2 != 0) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_80333828 + 0x1d8) & 0xfffffff0 | 0xf;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_80333828 + 0x1d0) & 0xfffffffc;
  }
  bVar1 = false;
  uVar3 = *(uint *)(DAT_80333828 + 0x1dc);
  if (*(char *)(DAT_80333828 + 0x200) != '\0') {
    if ((uVar3 & 7) != 3) {
      uVar3 = uVar3 & 0xfffffff8 | 3;
      bVar1 = true;
    }
  }
  if (param_2 == 0) {
    if ((uVar3 & 7) != 3) goto LAB_801a33d4;
  }
  if ((uVar3 >> 6 & 1) == 1) {
    bVar1 = true;
    uVar3 = uVar3 & 0xffffffbf;
  }
LAB_801a33d4:
  if (bVar1) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = uVar3;
  }
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x1f0);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 500);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x1f8);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1 >> 5 & 0xffffff | 0x4b000000;
  *(uint *)(DAT_80333828 + 0x1fc) =
       *(uint *)(DAT_80333828 + 0x1fc) & 0xfffff7ff | (uint)param_2 << 0xb;
  *(uint *)(iVar2 + 0x1fc) = *(uint *)(iVar2 + 0x1fc) & 0xffffbfff;
  *(uint *)(iVar2 + 0x1fc) = *(uint *)(iVar2 + 0x1fc) & 0xffffff | 0x52000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1fc);
  if (param_2 != 0) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1d8);
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1d0);
  }
  if (bVar1) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x1dc);
  }
  *(undefined2 *)(DAT_80333828 + 2) = 0;
  return;
}

