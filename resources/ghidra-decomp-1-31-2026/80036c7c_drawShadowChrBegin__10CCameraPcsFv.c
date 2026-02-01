// Function: drawShadowChrBegin__10CCameraPcsFv
// Entry: 80036c7c
// Size: 88 bytes

void drawShadowChrBegin__10CCameraPcsFv(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8032fa58;
  if (*(char *)(param_1 + 0x404) != '\0') {
    *(float *)(param_1 + 0x3e0) = *(float *)(param_1 + 0x3e0) * FLOAT_8032fa58;
    *(float *)(param_1 + 0x3f0) = *(float *)(param_1 + 0x3f0) * fVar1;
    PSMTXConcat((Mtx *)(param_1 + 0x3d4),(Mtx *)(param_1 + 0x214),(Mtx *)(param_1 + 0x3a4));
  }
  return;
}

