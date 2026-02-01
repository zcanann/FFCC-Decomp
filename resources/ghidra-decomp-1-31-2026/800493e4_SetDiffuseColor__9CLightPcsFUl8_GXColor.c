// Function: SetDiffuseColor__9CLightPcsFUl8_GXColor
// Entry: 800493e4
// Size: 60 bytes

void SetDiffuseColor__9CLightPcsFUl8_GXColor(int param_1,int param_2,undefined4 *param_3)

{
  undefined4 local_8 [2];
  
  local_8[0] = *param_3;
  GXInitLightColor(param_1 + param_2 * 0xb0 + 0x128,local_8);
  return;
}

