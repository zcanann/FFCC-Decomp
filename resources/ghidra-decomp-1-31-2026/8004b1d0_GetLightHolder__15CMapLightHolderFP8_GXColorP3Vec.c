// Function: GetLightHolder__15CMapLightHolderFP8_GXColorP3Vec
// Entry: 8004b1d0
// Size: 76 bytes

void GetLightHolder__15CMapLightHolderFP8_GXColorP3Vec
               (undefined *param_1,undefined *param_2,undefined4 *param_3)

{
  if (param_2 != (undefined *)0x0) {
    *param_2 = *param_1;
    param_2[1] = param_1[1];
    param_2[2] = param_1[2];
    param_2[3] = param_1[3];
  }
  if (param_3 == (undefined4 *)0x0) {
    return;
  }
  *param_3 = *(undefined4 *)(param_1 + 4);
  param_3[1] = *(undefined4 *)(param_1 + 8);
  param_3[2] = *(undefined4 *)(param_1 + 0xc);
  return;
}

