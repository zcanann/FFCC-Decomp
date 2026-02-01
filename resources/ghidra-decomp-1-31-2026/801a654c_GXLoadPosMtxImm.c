// Function: GXLoadPosMtxImm
// Entry: 801a654c
// Size: 80 bytes

/* WARNING: Removing unreachable block (ram,0x801a6594) */
/* WARNING: Removing unreachable block (ram,0x801a6590) */
/* WARNING: Removing unreachable block (ram,0x801a658c) */
/* WARNING: Removing unreachable block (ram,0x801a6588) */
/* WARNING: Removing unreachable block (ram,0x801a6584) */
/* WARNING: Removing unreachable block (ram,0x801a6580) */
/* WARNING: Removing unreachable block (ram,0x801a657c) */
/* WARNING: Removing unreachable block (ram,0x801a6578) */
/* WARNING: Removing unreachable block (ram,0x801a6574) */
/* WARNING: Removing unreachable block (ram,0x801a6570) */
/* WARNING: Removing unreachable block (ram,0x801a656c) */
/* WARNING: Removing unreachable block (ram,0x801a6568) */

void GXLoadPosMtxImm(undefined4 *param_1,int param_2)

{
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_2 << 2 | 0xb0000;
  DAT_cc008000 = *param_1;
  DAT_cc008004 = param_1[1];
  DAT_cc008000 = param_1[2];
  DAT_cc008004 = param_1[3];
  DAT_cc008000 = param_1[4];
  DAT_cc008004 = param_1[5];
  DAT_cc008000 = param_1[6];
  DAT_cc008004 = param_1[7];
  DAT_cc008000 = param_1[8];
  DAT_cc008004 = param_1[9];
  DAT_cc008000 = param_1[10];
  DAT_cc008004 = param_1[0xb];
  return;
}

