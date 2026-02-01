// Function: SetShadow__5CFontFi
// Entry: 80092a30
// Size: 20 bytes

void SetShadow__5CFontFi(CFont *font,char param_2)

{
  font->renderFlags = (byte)((int)param_2 << 7) | font->renderFlags & 0x7f;
  return;
}

