// Function: Draw__5CFontFUs
// Entry: 8009211c
// Size: 1088 bytes

/* WARNING: Removing unreachable block (ram,0x80092538) */
/* WARNING: Removing unreachable block (ram,0x80092530) */
/* WARNING: Removing unreachable block (ram,0x80092528) */
/* WARNING: Removing unreachable block (ram,0x80092520) */
/* WARNING: Removing unreachable block (ram,0x80092518) */
/* WARNING: Removing unreachable block (ram,0x80092510) */
/* WARNING: Removing unreachable block (ram,0x80092508) */
/* WARNING: Removing unreachable block (ram,0x80092500) */
/* WARNING: Removing unreachable block (ram,0x80092164) */
/* WARNING: Removing unreachable block (ram,0x8009215c) */
/* WARNING: Removing unreachable block (ram,0x80092154) */
/* WARNING: Removing unreachable block (ram,0x8009214c) */
/* WARNING: Removing unreachable block (ram,0x80092144) */
/* WARNING: Removing unreachable block (ram,0x8009213c) */
/* WARNING: Removing unreachable block (ram,0x80092134) */
/* WARNING: Removing unreachable block (ram,0x8009212c) */

void Draw__5CFontFUs(CFont *font,uint param_2)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  ushort *puVar4;
  int iVar5;
  byte *pbVar6;
  uint uVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  undefined8 local_d8;
  undefined8 local_d0;
  undefined8 local_c8;
  undefined8 local_c0;
  undefined8 local_b8;
  
  puVar4 = *(ushort **)(&font->field_0x3c + (param_2 & 0xff) * 4) + 1;
  for (uVar2 = (uint)**(ushort **)(&font->field_0x3c + (param_2 & 0xff) * 4); uVar2 != 0;
      uVar2 = uVar2 - 1) {
    if ((uint)*(byte *)(puVar4 + 1) == (param_2 >> 8 & 0xff)) goto LAB_800921b8;
    puVar4 = puVar4 + 4;
  }
  puVar4 = (ushort *)0x0;
LAB_800921b8:
  if (puVar4 == (ushort *)0x0) {
    puVar4 = *(ushort **)&font->field_0x138 + 1;
    for (uVar2 = (uint)**(ushort **)&font->field_0x138; uVar2 != 0; uVar2 = uVar2 - 1) {
      if (*(char *)(puVar4 + 1) == '\0') goto LAB_800921f8;
      puVar4 = puVar4 + 4;
    }
    puVar4 = (ushort *)0x0;
LAB_800921f8:
    if (puVar4 == (ushort *)0x0) {
      return;
    }
  }
  bVar1 = font->renderFlags;
  pbVar6 = (byte *)((int)puVar4 +
                   ((uint)(-(int)((char)bVar1 >> 7) | (int)((char)bVar1 >> 7)) >> 0x1e & 2) + 3);
  if ((int)((uint)bVar1 << 0x1b | (uint)(bVar1 >> 5)) < 0) {
    uVar7 = (uint)*(ushort *)&font->field_0x8;
    uVar2 = (uint)*puVar4 / (uint)*(ushort *)&font->field_0xc;
    iVar5 = uVar7 * ((uint)*puVar4 - uVar2 * *(ushort *)&font->field_0xc);
    iVar3 = *(ushort *)&font->field_0xa * uVar2;
  }
  else {
    uVar2 = (uint)*puVar4 / (uint)*(ushort *)&font->field_0xc;
    uVar7 = (uint)pbVar6[1];
    iVar3 = *(ushort *)&font->field_0xa * uVar2;
    iVar5 = (uint)*pbVar6 +
            (uint)*(ushort *)&font->field_0x8 *
            ((uint)*puVar4 - uVar2 * *(ushort *)&font->field_0xc);
  }
  dVar16 = (double)(float)((double)(CONCAT44(0x43300000,iVar5 * 2) ^ 0x80000000) - DOUBLE_803306c0);
  dVar15 = (double)(float)((double)(CONCAT44(0x43300000,iVar3 * 2) ^ 0x80000000) - DOUBLE_803306c0);
  dVar14 = (double)font->posX;
  dVar13 = (double)font->posY;
  if ((int)((uint)(byte)font->renderFlags << 0x1c | (uint)((byte)font->renderFlags >> 4)) < 0) {
    dVar14 = (double)floor(dVar14);
    dVar14 = (double)(float)dVar14;
    dVar13 = (double)floor(dVar13);
    dVar13 = (double)(float)dVar13;
  }
  local_b8 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
  local_d0 = (double)CONCAT44(0x43300000,uVar7 << 1 ^ 0x80000000);
  dVar8 = (double)font->scaleX * (double)((float)(local_b8 - DOUBLE_803306c0) + font->margin);
  local_d8 = (double)CONCAT44(0x43300000,(uint)*(ushort *)&font->field_0xa << 1 ^ 0x80000000);
  dVar12 = (double)(float)(dVar16 + (double)(float)(local_d0 - DOUBLE_803306c0));
  local_c8 = (double)CONCAT44(0x43300000,uVar7 ^ 0x80000000);
  dVar11 = (double)(float)(dVar15 + (double)(float)(local_d8 - DOUBLE_803306c0));
  local_c0 = (double)CONCAT44(0x43300000,(uint)*(ushort *)&font->field_0xa);
  dVar10 = (double)(float)((double)(float)(local_c8 - DOUBLE_803306c0) * (double)font->scaleX +
                          dVar14);
  dVar9 = (double)(float)((double)(float)(local_c0 - DOUBLE_803306d0) * (double)font->scaleY +
                         dVar13);
  if ((int)((uint)(byte)font->renderFlags << 0x1c | (uint)((byte)font->renderFlags >> 4)) < 0) {
    dVar8 = (double)floor();
  }
  font->posX = font->posX + (float)dVar8;
  if (*pbVar6 == 0) {
    dVar16 = (double)(float)(dVar16 + (double)FLOAT_803306c8);
  }
  if (*(short *)&font->field_0x8 == (ushort)((ushort)*pbVar6 + (ushort)pbVar6[1])) {
    dVar12 = (double)(float)(dVar12 - (double)FLOAT_803306c8);
  }
  dVar8 = (double)(float)(dVar15 + (double)FLOAT_803306c8);
  dVar15 = (double)(float)(dVar11 - (double)FLOAT_803306c8);
  GXBegin(0x80,0,4);
  DAT_cc008000 = (float)dVar14;
  DAT_cc008000 = (float)dVar13;
  DAT_cc008000 = font->posZ;
  DAT_cc008000._0_2_ = (short)(int)dVar16;
  DAT_cc008000._0_2_ = (short)(int)dVar8;
  DAT_cc008000 = (float)dVar10;
  DAT_cc008000 = (float)dVar13;
  DAT_cc008000 = font->posZ;
  DAT_cc008000._0_2_ = (short)(int)dVar12;
  DAT_cc008000._0_2_ = (short)(int)dVar8;
  DAT_cc008000 = (float)dVar10;
  DAT_cc008000 = (float)dVar9;
  DAT_cc008000 = font->posZ;
  DAT_cc008000._0_2_ = (short)(int)dVar12;
  DAT_cc008000._0_2_ = (short)(int)dVar15;
  DAT_cc008000 = (float)dVar14;
  DAT_cc008000 = (float)dVar9;
  DAT_cc008000 = font->posZ;
  DAT_cc008000._0_2_ = (short)(int)dVar16;
  DAT_cc008000._0_2_ = (short)(int)dVar15;
  return;
}

