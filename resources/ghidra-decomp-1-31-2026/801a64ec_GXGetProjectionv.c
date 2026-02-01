// Function: GXGetProjectionv
// Entry: 801a64ec
// Size: 96 bytes

void GXGetProjectionv(float *param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *param_1 = (float)((double)CONCAT44(0x43300000,*(undefined4 *)(DAT_80333828 + 0x420)) -
                    DOUBLE_80333920);
  param_1[1] = *(float *)(iVar1 + 0x424);
  param_1[2] = *(float *)(iVar1 + 0x428);
  param_1[3] = *(float *)(iVar1 + 0x42c);
  param_1[4] = *(float *)(iVar1 + 0x430);
  param_1[5] = *(float *)(iVar1 + 0x434);
  param_1[6] = *(float *)(iVar1 + 0x438);
  return;
}

