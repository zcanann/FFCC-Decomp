// Function: DrawSoubi__9CShopMenuFv
// Entry: 80153680
// Size: 996 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawSoubi__9CShopMenuFv(CShopMenu *shopMenu)

{
  undefined4 *puVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  int32_t iVar5;
  double dVar6;
  undefined4 uVar7;
  undefined auStack_60 [4];
  undefined4 local_5c;
  undefined auStack_58 [4];
  undefined4 local_54;
  undefined4 local_50;
  undefined *puStack_4c;
  longlong local_48;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  undefined *puStack_34;
  longlong local_30;
  undefined4 local_28;
  uint uStack_24;
  
  DrawSoubiBase__9CShopMenuFv();
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xf,0,0xa8,0x5a,0xff,0,0,0);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawSingleIcon__8CMenuPcsFiiifif
            ((double)FLOAT_80332d28,(double)FLOAT_80332d28,&MenuPcs,
             *(undefined4 *)&shopMenu->field_0x150,0x40,0x42,0);
  uVar7 = MenuPcs._248_4_;
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._248_4_);
  SetShadow__5CFontFi((CFont *)uVar7,1);
  SetScale__5CFontFf(FLOAT_80332d28,(CFont *)uVar7);
  puVar1 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_58,0xff,0xff,0xff,0xff);
  local_54 = *puVar1;
  SetColor__5CFontF8_GXColor((CFont *)uVar7,&local_54);
  DrawInit__5CFontFv((CFont *)uVar7);
  if (*(int *)&shopMenu->field_0x150 < 1) {
    iVar5 = 0;
  }
  else {
    iVar5 = Game.game.m_cFlatDataArr[1].m_table[0].index[*(int *)&shopMenu->field_0x150 * 5 + 4];
  }
  DrawInit__5CFontFv((CFont *)uVar7);
  DrawShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)FLOAT_80332d54,(double)FLOAT_80332e04,&MenuPcs,uVar7,iVar5,0x18,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  uVar7 = 0x138;
  DrawItemInfo__9CShopMenuFiiiiiiii
            (shopMenu,*(undefined4 *)&shopMenu->field_0x150,0x98,0x7e,0x98,0x9c);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  iVar3 = 0x1f6;
  do {
    drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xc,0,iVar3,0x17c,0xff,0,0,0,uVar7);
    iVar3 = iVar3 + -0x10;
  } while (0x42 < iVar3);
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xb,0,0x226,0x158,0xff,0,0,0,uVar7);
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,1,1,iVar3,0x17c,0xff,0,0,0);
  uVar7 = MenuPcs._264_4_;
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._264_4_);
  SetShadow__5CFontFi((CFont *)uVar7,0);
  puVar1 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_60,0xff,0xff,0xff,0xff);
  local_5c = *puVar1;
  SetColor__5CFontF8_GXColor((CFont *)uVar7,&local_5c);
  SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)uVar7);
  SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)uVar7);
  DrawInit__5CFontFv((CFont *)uVar7);
  uVar2 = (uint)Game.game.m_gameWork.m_languageId;
  SetPosY__5CFontFf(FLOAT_80332e08,(CFont *)uVar7);
  puVar4 = (&PTR_s_Equip_80214dc0)[(uVar2 - 1) * 0x15];
  dVar6 = (double)GetWidth__5CFontFPc((CFont *)uVar7,puVar4);
  puStack_4c = &DAT_800001f8;
  local_50 = 0x43300000;
  local_40 = 0x43300000;
  uStack_3c = (uint)((float)((double)FLOAT_80332dd4 - dVar6) * FLOAT_80332d78 +
                    (float)(4503601774854648.0 - DOUBLE_80332d20));
  local_48 = (longlong)(int)uStack_3c;
  uStack_3c = uStack_3c ^ 0x80000000;
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20),(CFont *)uVar7
                   );
  SetPosY__5CFontFf(FLOAT_80332e08,(CFont *)uVar7);
  Draw__5CFontFPc((CFont *)uVar7,puVar4);
  puVar4 = (&PTR_s_Cancel_80214d98)[(uVar2 - 1) * 0x15];
  dVar6 = (double)GetWidth__5CFontFPc((CFont *)uVar7,puVar4);
  puStack_34 = &DAT_800001f8;
  local_38 = 0x43300000;
  local_28 = 0x43300000;
  uVar2 = (uint)((float)((double)FLOAT_80332dd4 - dVar6) * FLOAT_80332d78 +
                (float)(4503601774854648.0 - DOUBLE_80332d20));
  local_30 = (longlong)(int)uVar2;
  uStack_24 = uVar2 ^ 0x80000000;
  SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80332d20),(CFont *)uVar7
                   );
  SetPosY__5CFontFf(FLOAT_80332d88,(CFont *)uVar7);
  Draw__5CFontFPc((CFont *)uVar7,puVar4);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawCursor__8CMenuPcsFiif
            ((double)FLOAT_80332d28,&MenuPcs,uVar2 - 0x24,
             *(int *)&shopMenu->field_0x3c * 0x18 + 0x13c);
  return;
}

