// Function: SetStdPixelFmt__8CGraphicFv
// Entry: 800198b8
// Size: 72 bytes

void SetStdPixelFmt__8CGraphicFv(CGraphic *graphic)

{
  if (*(char *)(*(int *)&graphic->field_0x71e0 + 0x19) == '\0') {
    GXSetPixelFmt(0,0);
  }
  else {
    GXSetPixelFmt(2,0);
  }
  return;
}

