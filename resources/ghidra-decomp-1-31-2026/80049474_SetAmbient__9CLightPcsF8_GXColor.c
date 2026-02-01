// Function: SetAmbient__9CLightPcsF8_GXColor
// Entry: 80049474
// Size: 48 bytes

void SetAmbient__9CLightPcsF8_GXColor(undefined4 param_1,undefined4 *param_2)

{
  undefined4 local_8 [2];
  
  local_8[0] = *param_2;
  GXSetChanAmbColor(4,local_8);
  return;
}

