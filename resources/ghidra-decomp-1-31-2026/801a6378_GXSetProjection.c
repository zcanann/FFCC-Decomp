// Function: GXSetProjection
// Entry: 801a6378
// Size: 180 bytes

void GXSetProjection(undefined4 *param_1,int param_2)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *(int *)(DAT_80333828 + 0x420) = param_2;
  *(undefined4 *)(iVar1 + 0x424) = *param_1;
  *(undefined4 *)(iVar1 + 0x42c) = param_1[5];
  *(undefined4 *)(iVar1 + 0x434) = param_1[10];
  *(undefined4 *)(iVar1 + 0x438) = param_1[0xb];
  if (param_2 == 1) {
    *(undefined4 *)(iVar1 + 0x428) = param_1[3];
    *(undefined4 *)(iVar1 + 0x430) = param_1[7];
  }
  else {
    *(undefined4 *)(iVar1 + 0x428) = param_1[2];
    *(undefined4 *)(iVar1 + 0x430) = param_1[6];
  }
  DAT_cc008000._0_1_ = 0x10;
  DAT_cc008000 = 0x61020;
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x424);
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x428);
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x42c);
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x430);
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x434);
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x438);
  DAT_cc008000 = *(undefined4 *)(DAT_80333828 + 0x420);
  *(undefined2 *)(DAT_80333828 + 2) = 1;
  return;
}

