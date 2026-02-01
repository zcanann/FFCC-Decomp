// Function: GXLoadTexObjPreLoaded
// Entry: 801a4228
// Size: 408 bytes

void GXLoadTexObjPreLoaded(uint *param_1,uint *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  *param_1 = *param_1 & 0xffffff | (uint)(byte)(&DAT_8032eba0)[param_3] << 0x18;
  param_1[1] = param_1[1] & 0xffffff | (uint)(byte)(&DAT_8032eba8)[param_3] << 0x18;
  param_1[2] = param_1[2] & 0xffffff | (uint)(byte)(&DAT_8032ebb0)[param_3] << 0x18;
  *param_2 = *param_2 & 0xffffff | (uint)(byte)(&DAT_8032ebb8)[param_3] << 0x18;
  param_2[1] = param_2[1] & 0xffffff | (uint)(byte)(&DAT_8032ebc0)[param_3] << 0x18;
  param_1[3] = param_1[3] & 0xffffff | (uint)(byte)(&DAT_8032ebc8)[param_3] << 0x18;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *param_1;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1[1];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1[2];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *param_2;
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_2[1];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1[3];
  if ((*(byte *)((int)param_1 + 0x1f) & 2) == 0) {
    iVar1 = (**(code **)(DAT_80333828 + 0x414))(param_1[6]);
    *(uint *)(iVar1 + 4) =
         *(uint *)(iVar1 + 4) & 0xffffff | (uint)(byte)(&DAT_8032ebd0)[param_3] << 0x18;
    DAT_cc008000._0_1_ = 0x61;
    DAT_cc008000 = *(undefined4 *)(iVar1 + 4);
  }
  iVar1 = DAT_80333828;
  iVar2 = DAT_80333828 + param_3 * 4;
  *(uint *)(iVar2 + 0x45c) = param_1[2];
  *(uint *)(iVar2 + 0x47c) = *param_1;
  *(uint *)(iVar1 + 0x4f4) = *(uint *)(iVar1 + 0x4f4) | 1;
  *(undefined2 *)(iVar1 + 2) = 0;
  return;
}

