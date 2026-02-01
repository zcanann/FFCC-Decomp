// Function: SetStdProjectionMatrix__10CCameraPcsFv
// Entry: 80039450
// Size: 128 bytes

void SetStdProjectionMatrix__10CCameraPcsFv(int param_1)

{
  float fVar1;
  
  fVar1 = *(float *)(param_1 + 0xfc);
  if ((*(float *)(param_1 + 0xfc) < FLOAT_8032fac8) &&
     (fVar1 = FLOAT_8032fab4, System.m_execParam != 0)) {
    Printf__7CSystemFPce(&System,&DAT_801d7928);
    fVar1 = FLOAT_8032fab4;
  }
  C_MTXPerspective(fVar1,FLOAT_8032fa3c,*(float *)(param_1 + 0x100),*(float *)(param_1 + 0x104),
                   (Mtx *)(param_1 + 0x94));
  GXSetProjection(param_1 + 0x94,0);
  return;
}

