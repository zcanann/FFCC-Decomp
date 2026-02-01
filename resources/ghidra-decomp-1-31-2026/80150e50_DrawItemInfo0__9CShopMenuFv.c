// Function: DrawItemInfo0__9CShopMenuFv
// Entry: 80150e50
// Size: 2284 bytes

/* WARNING: Removing unreachable block (ram,0x80151720) */
/* WARNING: Removing unreachable block (ram,0x80150e60) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawItemInfo0__9CShopMenuFv(CShopMenu *shopMenu)

{
  uint uVar1;
  bool bVar2;
  undefined4 font;
  undefined4 uVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  int32_t iVar11;
  int iVar12;
  undefined *puVar13;
  undefined4 uVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  undefined4 local_100;
  undefined auStack_fc [4];
  undefined4 local_f8;
  undefined auStack_f4 [4];
  undefined auStack_f0 [4];
  undefined4 local_ec;
  undefined auStack_e8 [64];
  undefined auStack_a8 [64];
  double local_68;
  undefined8 local_60;
  undefined4 local_58;
  uint uStack_54;
  double local_50;
  double local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  iVar5 = *(int *)&shopMenu->field_0x28;
  if (iVar5 != -1) {
    iVar6 = *(int *)&shopMenu->field_0x14;
    if (iVar6 == 0) {
      iVar5 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar5 * 2 + 0xbe6);
    }
    else if (iVar6 == 1) {
      iVar5 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar5 * 2 + 0xb6);
    }
    else if (iVar6 == 2) {
      if (*(int *)(&shopMenu->field_0x50 + iVar5 * 4) == -1) {
        iVar5 = -1;
      }
      else {
        iVar5 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                *(int *)(&shopMenu->field_0x50 + iVar5 * 4) * 2 + 0xb6);
      }
    }
    else {
      iVar5 = -1;
    }
    iVar6 = Game.game.m_gameWork.m_languageId - 1;
    DrawInit__8CMenuPcsFv(&MenuPcs);
    if (0 < iVar5) {
      DrawSingleIcon__8CMenuPcsFiiifif
                ((double)FLOAT_80332d28,(double)FLOAT_80332d28,&MenuPcs,iVar5,0x40,100,0);
    }
    font = MenuPcs._248_4_;
    SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._248_4_);
    SetShadow__5CFontFi((CFont *)font,1);
    SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)font);
    SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)font);
    puVar7 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_f0,0xff,0xff,0xff,0xff);
    local_ec = *puVar7;
    SetColor__5CFontF8_GXColor((CFont *)font,&local_ec);
    DrawInit__5CFontFv((CFont *)font);
    if (0 < iVar5) {
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
      if (iVar5 < 1) {
        iVar11 = 0;
      }
      else {
        iVar11 = Game.game.m_cFlatDataArr[1].m_table[0].index[iVar5 * 5 + 4];
      }
      DrawInit__5CFontFv((CFont *)font);
      DrawShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)FLOAT_80332d54,(double)FLOAT_80332d58,&MenuPcs,font,iVar11,0x18,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
    }
    iVar9 = *(int *)&shopMenu->field_0x28;
    if (iVar9 == -1) {
      bVar2 = false;
    }
    else {
      iVar10 = *(int *)&shopMenu->field_0x14;
      if (iVar10 == 0) {
        iVar12 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar9 * 2 + 0xbe6);
      }
      else if (iVar10 == 1) {
        iVar12 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + iVar9 * 2 + 0xb6);
      }
      else if (iVar10 == 2) {
        if (*(int *)(&shopMenu->field_0x50 + iVar9 * 4) == -1) {
          iVar12 = -1;
        }
        else {
          iVar12 = (int)*(short *)(*(int *)&shopMenu->field_0x20 +
                                   *(int *)(&shopMenu->field_0x50 + iVar9 * 4) * 2 + 0xb6);
        }
      }
      else {
        iVar12 = -1;
      }
      if (iVar12 < 1) {
        bVar2 = false;
      }
      else if (iVar10 == 0) {
        bVar2 = true;
      }
      else if (iVar10 == 2) {
        bVar2 = true;
        if ((*(uint *)(*(int *)&shopMenu->field_0x20 + ((int)(iVar12 - 0x191U) >> 5) * 4 + 0xc08) &
            1 << (iVar12 - 0x191U & 0x1f)) == 0) {
          bVar2 = false;
        }
      }
      else {
        cVar8 = EquipChk__8CMenuPcsFi(&MenuPcs,iVar9);
        if (cVar8 == '\0') {
          if (iVar12 < 0x9f) {
            bVar2 = false;
          }
          else {
            bVar2 = true;
          }
        }
        else {
          bVar2 = false;
        }
      }
    }
    if (bVar2) {
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
      puVar13 = (&PTR_DAT_80214da8)[iVar6 * 0x15];
      dVar15 = (double)GetWidth__5CFontFPc((CFont *)font,puVar13);
      uVar3 = MenuPcs._248_4_;
      dVar17 = (double)(float)((double)FLOAT_80332d3c - dVar15);
      dVar15 = dVar17 - (double)FLOAT_80332d5c;
      local_68 = (double)(longlong)(int)dVar15;
      if (*(int *)&shopMenu->field_0x14 == 0) {
        if (iVar5 < 1) {
          iVar9 = 0;
        }
        else {
          iVar9 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                  (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar5 * 0x48 + 0x20);
          iVar9 = iVar9 / 100 + (iVar9 >> 0x1f);
          iVar9 = iVar9 - (iVar9 >> 0x1f);
        }
      }
      else if (*(int *)&shopMenu->field_0x14 == 1) {
        if (iVar5 < 1) {
          iVar9 = 0;
        }
        else {
          iVar9 = (int)*(short *)(*(int *)&shopMenu->field_0x20 + 0xbe2) *
                  (uint)*(ushort *)(Game.game.unkCFlatData0[2] + iVar5 * 0x48 + 0x20);
          iVar9 = iVar9 / 100 + (iVar9 >> 0x1f);
          local_68 = (double)(CONCAT44(0x43300000,iVar9 - (iVar9 >> 0x1f)) ^ 0x80000000);
          iVar9 = (int)(FLOAT_80332d60 * (float)(local_68 - DOUBLE_80332d20));
          local_60 = (double)(longlong)iVar9;
        }
      }
      else {
        iVar9 = -1;
      }
      SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
      SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar3);
      puVar7 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_f4,0xff,0xff,0xff,0xff);
      local_f8 = *puVar7;
      SetColor__5CFontF8_GXColor((CFont *)uVar3,&local_f8);
      DrawInit__5CFontFv((CFont *)uVar3);
      fVar4 = FLOAT_80332d64;
      *(byte *)(uVar3 + 0x24) = *(byte *)(uVar3 + 0x24) & 0xef | 0x10;
      SetMargin__5CFontFf(fVar4,(CFont *)uVar3);
      sprintf(auStack_a8,&DAT_80332d14,iVar9);
      dVar16 = (double)GetWidth__5CFontFPc((CFont *)uVar3,auStack_a8);
      local_60 = (double)CONCAT44(0x43300000,(int)dVar15 ^ 0x80000000);
      local_58 = 0x43300000;
      uStack_54 = (uint)((double)(float)(local_60 - DOUBLE_80332d20) - dVar16);
      local_68 = (double)(longlong)(int)uStack_54;
      uStack_54 = uStack_54 ^ 0x80000000;
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332d20),
                 (double)FLOAT_80332d68,&MenuPcs,uVar3,auStack_a8,0x1b,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
      DrawInit__5CFontFv((CFont *)font);
      local_50 = (double)(longlong)(int)dVar17;
      local_48 = (double)(CONCAT44(0x43300000,(int)dVar17) ^ 0x80000000);
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)(float)(local_48 - DOUBLE_80332d20),(double)FLOAT_80332d68,&MenuPcs,font,
                 puVar13,0x19,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
    }
    else {
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
      if (*(int *)&shopMenu->field_0x14 == 0) {
        puVar13 = (&PTR_s_Cannot_buy__80214dc8)[iVar6 * 0x15];
      }
      else {
        puVar13 = (&PTR_s_Cannot_sell__80214dcc)[iVar6 * 0x15];
      }
      dVar15 = (double)GetWidth__5CFontFPc((CFont *)font,puVar13);
      DrawInit__5CFontFv((CFont *)font);
      local_48 = (double)(longlong)(int)((double)FLOAT_80332d3c - dVar15);
      local_50 = (double)(CONCAT44(0x43300000,(int)((double)FLOAT_80332d3c - dVar15)) ^ 0x80000000);
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)(float)(local_50 - DOUBLE_80332d20),(double)FLOAT_80332d68,&MenuPcs,font,
                 puVar13,0x19,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
    }
    if (*(int *)&shopMenu->field_0x10 == 0) {
      DrawItemInfo__9CShopMenuFiiiiiiii(shopMenu,iVar5,0,0xa8,0,0xc6);
    }
    uVar3 = MenuPcs._248_4_;
    if ((*(int *)&shopMenu->field_0x10 == 1) && (*(int *)&shopMenu->field_0x14 == 0)) {
      uVar14 = *(undefined4 *)&shopMenu->field_0x44;
      SetShadow__5CFontFi((CFont *)MenuPcs._248_4_,1);
      SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar3);
      puVar7 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_fc,0xff,0xff,0xff,0xff);
      local_100 = *puVar7;
      SetColor__5CFontF8_GXColor((CFont *)uVar3,&local_100);
      DrawInit__5CFontFv((CFont *)uVar3);
      fVar4 = FLOAT_80332d34;
      *(byte *)(uVar3 + 0x24) = *(byte *)(uVar3 + 0x24) & 0xef | 0x10;
      SetMargin__5CFontFf(fVar4,(CFont *)uVar3);
      sprintf(auStack_e8,&DAT_80332d18,uVar14);
      dVar15 = (double)GetWidth__5CFontFPc((CFont *)uVar3,auStack_e8);
      local_48 = 4503601774854408.0;
      local_58 = 0x43300000;
      uVar1 = (uint)((double)(float)(4503601774854408.0 - DOUBLE_80332d20) - dVar15);
      local_50 = (double)(longlong)(int)uVar1;
      uStack_54 = uVar1 ^ 0x80000000;
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_80332d20),
                 (double)FLOAT_80332d6c,&MenuPcs,uVar3,auStack_e8,4,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      DrawInit__5CFontFv((CFont *)font);
      SetScale__5CFontFf(FLOAT_80332d28,(CFont *)font);
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
      puVar13 = (&PTR_s_Quantity__80214dd0)[iVar6 * 0x15];
      dVar15 = (double)GetWidth__5CFontFPc((CFont *)font,puVar13);
      DrawInit__5CFontFv((CFont *)font);
      local_60 = (double)CONCAT44(0x43300000,uVar1 ^ 0x80000000);
      local_40 = 0x43300000;
      uStack_3c = (uint)((float)((double)(float)(local_60 - DOUBLE_80332d20) - dVar15) -
                        FLOAT_80332d5c);
      local_68 = (double)(longlong)(int)uStack_3c;
      uStack_3c = uStack_3c ^ 0x80000000;
      DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
                ((double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20),
                 (double)FLOAT_80332d6c,&MenuPcs,font,puVar13,0x18,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      if (*(int *)&shopMenu->field_0x10 == 1) {
        uStack_3c = *(uint *)&shopMenu->field_0x38 ^ 0x80000000;
        local_40 = 0x43300000;
        iVar5 = (int)-((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20) *
                       FLOAT_80332d74 - FLOAT_80332d70);
        local_48 = (double)(longlong)iVar5;
        drawShapeSeqScale__FiiiiffUc
                  ((double)FLOAT_80332d78,(double)FLOAT_80332d78,0x12,0,iVar5,0xd4,0xff);
      }
    }
  }
  return;
}

