// Function: DrawSphere__8CGraphicFv
// Entry: 80018a10
// Size: 64 bytes

void DrawSphere__8CGraphicFv(CGraphic *graphic)

{
  GXSetLineWidth(8,0);
  GXCallDisplayList(*(undefined4 *)&graphic->field_0x71fc,*(undefined4 *)&graphic->field_0x71f8);
  return;
}

