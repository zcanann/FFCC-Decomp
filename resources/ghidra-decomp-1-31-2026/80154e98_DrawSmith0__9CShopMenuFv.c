// Function: DrawSmith0__9CShopMenuFv
// Entry: 80154e98
// Size: 448 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawSmith0__9CShopMenuFv(CShopMenu *shopMenu)

{
  uint uVar1;
  undefined4 font;
  undefined4 *puVar2;
  undefined *puVar3;
  double dVar4;
  undefined auStack_38 [4];
  undefined4 local_34;
  undefined4 local_30;
  undefined *puStack_2c;
  longlong local_28;
  undefined4 local_20;
  uint uStack_1c;
  
  DrawShopBase__9CShopMenuFv(shopMenu);
  drawShapeSeqScale__FiiiiffUc((double)FLOAT_80332e48,(double)FLOAT_80332d28,0x11,0,0,0x154,0xff);
  DrawItemList__9CShopMenuFv(shopMenu);
  DrawItemHelp__9CShopMenuFiii(shopMenu,*(int *)&shopMenu->field_0x28,0x140,0x172);
  font = MenuPcs._248_4_;
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._248_4_);
  SetShadow__5CFontFi((CFont *)font,1);
  SetScale__5CFontFf(FLOAT_80332d8c,(CFont *)font);
  puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_38,0xff,0xff,0xff,0xff);
  local_34 = *puVar2;
  SetColor__5CFontF8_GXColor((CFont *)font,&local_34);
  DrawInit__5CFontFv((CFont *)font);
  if (*(char *)(*(int *)&shopMenu->field_0x20 + 0xbe1) == '\0') {
    puVar3 = (&PTR_s_Blacksmith_80214da0)[(Game.game.m_gameWork.m_languageId - 1) * 0x15];
  }
  else {
    puVar3 = (undefined *)GetJobStr__8CMenuPcsFi(&MenuPcs,1);
  }
  dVar4 = (double)GetWidth__5CFontFPc((CFont *)font,puVar3);
  puStack_2c = &DAT_80000108;
  local_30 = 0x43300000;
  uVar1 = (uint)((double)(float)(4503601774854408.0 - DOUBLE_80332d20) - dVar4);
  local_28 = (longlong)(int)uVar1;
  DrawInit__5CFontFv((CFont *)font);
  uStack_1c = uVar1 ^ 0x80000000;
  local_20 = 0x43300000;
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80332d20),
             (double)FLOAT_80332e4c,&MenuPcs,font,puVar3,9,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  return;
}

