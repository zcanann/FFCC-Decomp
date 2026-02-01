// Function: RestoreProjection__8CMenuPcsFv
// Entry: 800f673c
// Size: 164 bytes

void RestoreProjection__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  undefined4 local_58;
  Mat4x4 MStack_54;
  
  PSMTXCopy(&menuPcs->m_cameraMatrix,&CameraPcs.m_cameraMatrix);
  local_58 = DAT_802381a7;
  GXSetCopyClear(&local_58,0xffffff);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_54);
  GXSetProjection(&MStack_54,0);
  SetViewport__8CGraphicFv(&Graphic);
  GXSetScissor(0,0,0x280,0x1c0);
  DrawInit__8CMenuPcsFv(menuPcs);
  return;
}

