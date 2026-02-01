// Function: SetOffsetZBuff__10CCameraPcsFf
// Entry: 80036290
// Size: 84 bytes

/* WARNING: Removing unreachable block (ram,0x800362cc) */
/* WARNING: Removing unreachable block (ram,0x800362a0) */

void SetOffsetZBuff__10CCameraPcsFf(double param_1,int param_2)

{
  double in_f31;
  double in_ps31_1;
  Mat4x4 MStack_58;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  PSMTX44Copy((Mat4x4 *)(param_2 + 0x94),&MStack_58);
  MStack_58.value[2][3] = (float)((double)MStack_58.value[2][3] + param_1);
  GXSetProjection(&MStack_58,0);
  return;
}

