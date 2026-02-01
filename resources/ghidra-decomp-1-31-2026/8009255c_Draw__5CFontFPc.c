// Function: Draw__5CFontFPc
// Entry: 8009255c
// Size: 116 bytes

void Draw__5CFontFPc(CFont *font,byte *param_2)

{
  for (; *param_2 != 0; param_2 = param_2 + 1) {
    Draw__5CFontFUs(font,(uint)*param_2);
  }
  return;
}

