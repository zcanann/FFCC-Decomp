// Function: GXLoadNrmMtxImm
// Entry: 801a659c
// Size: 80 bytes

/* WARNING: Removing unreachable block (ram,0x801a65e0) */
/* WARNING: Removing unreachable block (ram,0x801a65d8) */
/* WARNING: Removing unreachable block (ram,0x801a65d0) */
/* WARNING: Removing unreachable block (ram,0x801a65c8) */
/* WARNING: Removing unreachable block (ram,0x801a65c0) */
/* WARNING: Removing unreachable block (ram,0x801a65b8) */

void GXLoadNrmMtxImm(undefined4 *param_1,int param_2)

{
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_2 * 3 + 0x400U | 0x80000;
  DAT_cc008000 = *param_1;
  DAT_cc008004 = param_1[1];
  DAT_cc008000 = param_1[2];
  DAT_cc008000 = param_1[4];
  DAT_cc008004 = param_1[5];
  DAT_cc008000 = param_1[6];
  DAT_cc008000 = param_1[8];
  DAT_cc008004 = param_1[9];
  DAT_cc008000 = param_1[10];
  return;
}

