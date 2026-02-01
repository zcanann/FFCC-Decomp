// Function: EndQuadEnv__5CUtilFv
// Entry: 8002428c
// Size: 92 bytes

void EndQuadEnv__5CUtilFv(void)

{
  Mat4x4 MStack_78;
  Mtx MStack_38;
  
  PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_38);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_78);
  GXLoadPosMtxImm(&MStack_38,0);
  GXSetProjection(&MStack_78,0);
  return;
}

