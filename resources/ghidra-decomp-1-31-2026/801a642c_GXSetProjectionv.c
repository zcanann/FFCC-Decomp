// Function: GXSetProjectionv
// Entry: 801a642c
// Size: 192 bytes

void GXSetProjectionv(float *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = __cvt_fp2unsigned((double)*param_1);
  iVar1 = DAT_80333828;
  *(undefined4 *)(DAT_80333828 + 0x420) = uVar2;
  *(float *)(iVar1 + 0x424) = param_1[1];
  *(float *)(iVar1 + 0x428) = param_1[2];
  *(float *)(iVar1 + 0x42c) = param_1[3];
  *(float *)(iVar1 + 0x430) = param_1[4];
  *(float *)(iVar1 + 0x434) = param_1[5];
  *(float *)(iVar1 + 0x438) = param_1[6];
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x61020;
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x424);
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x428);
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x42c);
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x430);
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x434);
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x438);
  DAT_cc008000 = *(undefined4 *)(iVar1 + 0x420);
  *(undefined2 *)(iVar1 + 2) = 1;
  return;
}

