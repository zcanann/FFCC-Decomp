// Function: SetStdDispCopySrc__8CGraphicFv
// Entry: 8001992c
// Size: 52 bytes

void SetStdDispCopySrc__8CGraphicFv(CGraphic *graphic)

{
  GXSetDispCopySrc(0,0,*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 4),
                   *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6));
  return;
}

