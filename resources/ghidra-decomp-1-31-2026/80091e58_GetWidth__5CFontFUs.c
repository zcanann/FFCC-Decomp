// Function: GetWidth__5CFontFUs
// Entry: 80091e58
// Size: 304 bytes

double GetWidth__5CFontFUs(CFont *font,uint param_2)

{
  byte bVar1;
  uint uVar2;
  ushort *puVar3;
  double dVar4;
  
  puVar3 = *(ushort **)(&font->field_0x3c + (param_2 & 0xff) * 4) + 1;
  for (uVar2 = (uint)**(ushort **)(&font->field_0x3c + (param_2 & 0xff) * 4); uVar2 != 0;
      uVar2 = uVar2 - 1) {
    if ((uint)*(byte *)(puVar3 + 1) == (param_2 >> 8 & 0xff)) goto LAB_80091ea4;
    puVar3 = puVar3 + 4;
  }
  puVar3 = (ushort *)0x0;
LAB_80091ea4:
  if (puVar3 == (ushort *)0x0) {
    puVar3 = *(ushort **)&font->field_0x138 + 1;
    for (uVar2 = (uint)**(ushort **)&font->field_0x138; uVar2 != 0; uVar2 = uVar2 - 1) {
      if (*(char *)(puVar3 + 1) == '\0') goto LAB_80091f68;
      puVar3 = puVar3 + 4;
    }
    puVar3 = (ushort *)0x0;
LAB_80091f68:
    if (puVar3 == (ushort *)0x0) {
      return (double)FLOAT_803306b8;
    }
  }
  bVar1 = font->renderFlags;
  if ((int)((uint)bVar1 << 0x1b | (uint)(bVar1 >> 5)) < 0) {
    uVar2 = (uint)*(ushort *)&font->field_0x8;
  }
  else {
    uVar2 = (uint)*(byte *)((int)puVar3 +
                           ((uint)(-(int)((char)bVar1 >> 7) | (int)((char)bVar1 >> 7)) >> 0x1e & 2)
                           + 4);
  }
  dVar4 = (double)(font->scaleX *
                  (font->margin +
                  (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DOUBLE_803306c0)));
  if ((int)((uint)(byte)font->renderFlags << 0x1c | (uint)((byte)font->renderFlags >> 4)) < 0) {
    dVar4 = (double)floor(dVar4);
    dVar4 = (double)(float)dVar4;
  }
  return dVar4;
}

