// Function: SetStdDispCopyDst__8CGraphicFv
// Entry: 80019900
// Size: 44 bytes

void SetStdDispCopyDst__8CGraphicFv(CGraphic *graphic)

{
  GXSetDispCopyDst(*(undefined2 *)(*(int *)&graphic->field_0x71e0 + 4),
                   *(undefined2 *)(*(int *)&graphic->field_0x71e0 + 6));
  return;
}

