// Function: SetFov__10CCameraPcsFf
// Entry: 800b9918
// Size: 8 bytes

void SetFov__10CCameraPcsFf(double param_1,int param_2)

{
  *(float *)(param_2 + 0xfc) = (float)param_1;
  return;
}

