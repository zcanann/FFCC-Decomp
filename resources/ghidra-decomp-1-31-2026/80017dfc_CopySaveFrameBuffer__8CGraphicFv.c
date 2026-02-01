// Function: CopySaveFrameBuffer__8CGraphicFv
// Entry: 80017dfc
// Size: 172 bytes

void CopySaveFrameBuffer__8CGraphicFv(CGraphic *graphic)

{
  double dVar1;
  
  GXSetTexCopySrc(0,0,0x280,0x1c0);
  GXSetTexCopyDst(0x280,0x1c0,4,0);
  GXCopyTex(*(undefined4 *)&graphic->field_0x71ec,0);
  GXPixModeSync();
  GXInitTexObj(&graphic->field_0x722c,*(undefined4 *)&graphic->field_0x71ec,0x280,0x1c0,4,0,0,0);
  dVar1 = (double)FLOAT_8032f6c0;
  GXInitTexObjLOD(dVar1,dVar1,dVar1,&graphic->field_0x722c,0,0,0,0,0);
  return;
}

