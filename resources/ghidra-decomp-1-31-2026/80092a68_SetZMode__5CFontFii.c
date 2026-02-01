// Function: SetZMode__5CFontFii
// Entry: 80092a68
// Size: 36 bytes

void SetZMode__5CFontFii(CFont *font,int param_2,int param_3)

{
  font->renderFlags = (byte)((int)(char)param_2 << 6) & 0x40 | font->renderFlags & 0xbf;
  font->renderFlags = (byte)((int)(char)param_3 << 5) & 0x20 | font->renderFlags & 0xdf;
  return;
}

