// Function: GXLoadLightObjImm
// Entry: 801a3804
// Size: 124 bytes

/* WARNING: Removing unreachable block (ram,0x801a386c) */
/* WARNING: Removing unreachable block (ram,0x801a3868) */
/* WARNING: Removing unreachable block (ram,0x801a3864) */
/* WARNING: Removing unreachable block (ram,0x801a3860) */
/* WARNING: Removing unreachable block (ram,0x801a385c) */
/* WARNING: Removing unreachable block (ram,0x801a3858) */
/* WARNING: Removing unreachable block (ram,0x801a3844) */
/* WARNING: Removing unreachable block (ram,0x801a3840) */
/* WARNING: Removing unreachable block (ram,0x801a383c) */
/* WARNING: Removing unreachable block (ram,0x801a3838) */
/* WARNING: Removing unreachable block (ram,0x801a3834) */
/* WARNING: Removing unreachable block (ram,0x801a3830) */

void GXLoadLightObjImm(int param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = countLeadingZeros(param_2);
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = ((0x1f - iVar1) * 0x10 & 0x70U) + 0x600 | 0xf0000;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = 0;
  DAT_cc008000 = *(undefined4 *)(param_1 + 0xc);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x10);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x14);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x18);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x1c);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x20);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x24);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x28);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x2c);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x30);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x34);
  DAT_cc008000 = *(undefined4 *)(param_1 + 0x38);
  DAT_cc008004 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined2 *)(DAT_80333828 + 2) = 1;
  return;
}

