// Function: GetWidth__5CFontFPc
// Entry: 80091f88
// Size: 404 bytes

/* WARNING: Removing unreachable block (ram,0x800920f8) */
/* WARNING: Removing unreachable block (ram,0x80091f98) */

double GetWidth__5CFontFPc(CFont *font,byte *param_2)

{
  float fVar1;
  byte bVar2;
  uint uVar3;
  ushort *puVar4;
  double dVar5;
  double dVar6;
  
  fVar1 = FLOAT_803306b8;
  do {
    dVar6 = (double)fVar1;
    bVar2 = *param_2;
    if (bVar2 == 0) {
      return dVar6;
    }
    param_2 = param_2 + 1;
    puVar4 = *(ushort **)(&font->field_0x3c + (uint)bVar2 * 4) + 1;
    for (uVar3 = (uint)**(ushort **)(&font->field_0x3c + (uint)bVar2 * 4); uVar3 != 0;
        uVar3 = uVar3 - 1) {
      if (*(char *)(puVar4 + 1) == '\0') goto LAB_80091ff8;
      puVar4 = puVar4 + 4;
    }
    puVar4 = (ushort *)0x0;
LAB_80091ff8:
    if (puVar4 == (ushort *)0x0) {
      puVar4 = *(ushort **)&font->field_0x138 + 1;
      for (uVar3 = (uint)**(ushort **)&font->field_0x138; uVar3 != 0; uVar3 = uVar3 - 1) {
        if (*(char *)(puVar4 + 1) == '\0') goto LAB_800920bc;
        puVar4 = puVar4 + 4;
      }
      puVar4 = (ushort *)0x0;
LAB_800920bc:
      if (puVar4 != (ushort *)0x0) goto LAB_80092000;
      dVar5 = (double)FLOAT_803306b8;
    }
    else {
LAB_80092000:
      bVar2 = font->renderFlags;
      if ((int)((uint)bVar2 << 0x1b | (uint)(bVar2 >> 5)) < 0) {
        uVar3 = (uint)*(ushort *)&font->field_0x8;
      }
      else {
        uVar3 = (uint)*(byte *)((int)puVar4 +
                               ((uint)(-(int)((char)bVar2 >> 7) | (int)((char)bVar2 >> 7)) >> 0x1e &
                               2) + 4);
      }
      dVar5 = (double)(font->scaleX *
                      (font->margin +
                      (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - DOUBLE_803306c0)));
      if ((int)((uint)(byte)font->renderFlags << 0x1c | (uint)((byte)font->renderFlags >> 4)) < 0) {
        dVar5 = (double)floor();
        dVar5 = (double)(float)dVar5;
      }
    }
    fVar1 = (float)(dVar6 + dVar5);
  } while( true );
}

