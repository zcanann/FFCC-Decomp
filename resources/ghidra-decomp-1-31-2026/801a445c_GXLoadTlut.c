// Function: GXLoadTlut
// Entry: 801a445c
// Size: 156 bytes

void GXLoadTlut(uint *param_1,undefined4 param_2)

{
  uint uVar1;
  uint *puVar2;
  
  puVar2 = (uint *)(**(code **)(DAT_80333828 + 0x414))(param_2);
  __GXFlushTextureState();
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = param_1[1];
  DAT_cc008000._0_1_ = 0x61;
  DAT_cc008000 = *puVar2;
  __GXFlushTextureState();
  *param_1 = *param_1 & 0xfffffc00 | *puVar2 & 0x3ff;
  uVar1 = param_1[1];
  puVar2[1] = *param_1;
  puVar2[2] = uVar1;
  puVar2[3] = param_1[2];
  return;
}

