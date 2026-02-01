// Function: GXLoadTexMtxImm
// Entry: 801a6624
// Size: 180 bytes

/* WARNING: Removing unreachable block (ram,0x801a66d0) */
/* WARNING: Removing unreachable block (ram,0x801a66cc) */
/* WARNING: Removing unreachable block (ram,0x801a66c8) */
/* WARNING: Removing unreachable block (ram,0x801a66c4) */
/* WARNING: Removing unreachable block (ram,0x801a66c0) */
/* WARNING: Removing unreachable block (ram,0x801a66bc) */
/* WARNING: Removing unreachable block (ram,0x801a66b8) */
/* WARNING: Removing unreachable block (ram,0x801a66b4) */
/* WARNING: Removing unreachable block (ram,0x801a66a8) */
/* WARNING: Removing unreachable block (ram,0x801a66a4) */
/* WARNING: Removing unreachable block (ram,0x801a66a0) */
/* WARNING: Removing unreachable block (ram,0x801a669c) */
/* WARNING: Removing unreachable block (ram,0x801a6698) */
/* WARNING: Removing unreachable block (ram,0x801a6694) */
/* WARNING: Removing unreachable block (ram,0x801a6690) */
/* WARNING: Removing unreachable block (ram,0x801a668c) */
/* WARNING: Removing unreachable block (ram,0x801a6688) */
/* WARNING: Removing unreachable block (ram,0x801a6684) */
/* WARNING: Removing unreachable block (ram,0x801a6680) */
/* WARNING: Removing unreachable block (ram,0x801a667c) */

void GXLoadTexMtxImm(undefined4 *param_1,uint param_2,int param_3)

{
  int iVar1;
  
  if (param_2 < 0x40) {
    param_2 = param_2 << 2;
  }
  else {
    param_2 = (param_2 - 0x40) * 4 + 0x500;
  }
  if (param_3 == 1) {
    iVar1 = 8;
  }
  else {
    iVar1 = 0xc;
  }
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = param_2 | (iVar1 + -1) * 0x10000;
  if (param_3 != 0) {
    DAT_cc008000 = *param_1;
    DAT_cc008004 = param_1[1];
    DAT_cc008000 = param_1[2];
    DAT_cc008004 = param_1[3];
    DAT_cc008000 = param_1[4];
    DAT_cc008004 = param_1[5];
    DAT_cc008000 = param_1[6];
    DAT_cc008004 = param_1[7];
    return;
  }
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

