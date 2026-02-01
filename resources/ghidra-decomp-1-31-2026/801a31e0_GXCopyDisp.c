// Function: GXCopyDisp
// Entry: 801a31e0
// Size: 348 bytes

void GXCopyDisp(uint param_1,byte param_2)

{
  bool bVar1;
  int iVar2;
  
  iVar2 = DAT_80333828;
  if (param_2 != 0) {
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_80333828 + 0x1d8) & 0xfffffff0 | 0xf;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(uint *)(DAT_80333828 + 0x1d0) & 0xfffffffc;
  }
  bVar1 = false;
  if (param_2 == 0) {
    if ((*(uint *)(DAT_80333828 + 0x1dc) & 7) != 3) goto LAB_801a326c;
  }
  if ((*(uint *)(DAT_80333828 + 0x1dc) >> 6 & 1) == 1) {
    DAT_cc008000._0_1_ = 0x61;
    bVar1 = true;
    DAT_cc008000 = *(uint *)(DAT_80333828 + 0x1dc) & 0xffffffbf;
  }
LAB_801a326c:
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x1e0);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x1e4);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x1e8);
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1 >> 5 & 0xffffff | 0x4b000000;
  *(uint *)(DAT_80333828 + 0x1ec) =
       *(uint *)(DAT_80333828 + 0x1ec) & 0xfffff7ff | (uint)param_2 << 0xb;
  *(uint *)(iVar2 + 0x1ec) = *(uint *)(iVar2 + 0x1ec) & 0xffffbfff | 0x4000;
  *(uint *)(iVar2 + 0x1ec) = *(uint *)(iVar2 + 0x1ec) & 0xffffff | 0x52000000;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *(undefined4 *)(iVar2 + 0x1ec);
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

