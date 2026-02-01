// Function: SetFullScreenShadowPos__10CCameraPcsFP3Vecf
// Entry: 800b9634
// Size: 32 bytes

void SetFullScreenShadowPos__10CCameraPcsFP3Vecf(double param_1,int param_2,undefined4 *param_3)

{
  *(undefined4 *)(param_2 + 0x408) = *param_3;
  *(undefined4 *)(param_2 + 0x40c) = param_3[1];
  *(undefined4 *)(param_2 + 0x410) = param_3[2];
  *(float *)(param_2 + 0x370) = (float)param_1;
  return;
}

