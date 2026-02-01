// Function: DrawQuit__5CFontFv
// Entry: 800925d0
// Size: 60 bytes

void DrawQuit__5CFontFv(void)

{
  Mat4x4 MStack_48;
  
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_48);
  GXSetProjection(&MStack_48,0);
  return;
}

