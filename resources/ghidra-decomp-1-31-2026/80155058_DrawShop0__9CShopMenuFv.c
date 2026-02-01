// Function: DrawShop0__9CShopMenuFv
// Entry: 80155058
// Size: 848 bytes

/* WARNING: Removing unreachable block (ram,0x8015538c) */
/* WARNING: Removing unreachable block (ram,0x80155384) */
/* WARNING: Removing unreachable block (ram,0x8015537c) */
/* WARNING: Removing unreachable block (ram,0x80155078) */
/* WARNING: Removing unreachable block (ram,0x80155070) */
/* WARNING: Removing unreachable block (ram,0x80155068) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawShop0__9CShopMenuFv(CShopMenu *shopMenu)

{
  undefined4 font;
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  int *piVar4;
  undefined *puVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  undefined auStack_68 [4];
  undefined4 local_64;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  
  iVar6 = Game.game.m_gameWork.m_languageId - 1;
  DrawShopBase__9CShopMenuFv(shopMenu);
  if (DAT_8032eed8 == '\0') {
    DAT_80214f3c = (&PTR_DAT_80214d90)[iVar6 * 0x15];
    DAT_80214f48 = (&PTR_DAT_80214d94)[iVar6 * 0x15];
    DAT_80214f54 = (&PTR_s_Cancel_80214d98)[iVar6 * 0x15];
    DAT_8032eed8 = '\x01';
  }
  piVar7 = &DAT_80214f34;
  iVar8 = 0;
  piVar4 = piVar7;
  do {
    uVar1 = countLeadingZeros(iVar8 - (uint)(byte)shopMenu->field_0x48);
    uVar1 = uVar1 >> 5;
    DAT_8032eed4 = piVar4;
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x1e);
    iVar3 = *DAT_8032eed4;
    if (uVar1 != 0) {
      iVar3 = iVar3 + 8;
    }
    drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0,uVar1,iVar3,DAT_8032eed4[1],0xff,0,0,0);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x1f);
    drawShapeSeq__FiiiiUcUcUcfUc
              ((double)FLOAT_80332d9c,8,uVar1,*DAT_8032eed4 + -0x30,DAT_8032eed4[1],0xff,0,0,0);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x20);
    font = MenuPcs._248_4_;
    iVar8 = iVar8 + 1;
    piVar4 = piVar4 + 3;
  } while (iVar8 < 3);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._248_4_);
  SetShadow__5CFontFi((CFont *)font,1);
  SetScale__5CFontFf(FLOAT_80332d8c,(CFont *)font);
  puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_68,0xff,0xff,0xff,0xff);
  local_64 = *puVar2;
  SetColor__5CFontF8_GXColor((CFont *)font,&local_64);
  DrawInit__5CFontFv((CFont *)font);
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x21);
  puVar5 = (&PTR_DAT_80214d9c)[iVar6 * 0x15];
  DrawInit__5CFontFv((CFont *)font);
  DrawNoShadowFont__8CMenuPcsFP5CFontPcffii
            ((double)FLOAT_80332d54,(double)FLOAT_80332e30,&MenuPcs,font,puVar5,9,0x12);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x22);
  SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)font);
  SetScale__5CFontFf(FLOAT_80332d28,(CFont *)font);
  iVar6 = 0;
  dVar11 = DOUBLE_80332d20;
  do {
    DAT_8032eed4 = piVar7;
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x23);
    local_60 = 0x43300000;
    local_58 = 0x43300000;
    iVar8 = DAT_8032eed4[2];
    uStack_5c = DAT_8032eed4[1] - 0xbU ^ 0x80000000;
    uStack_54 = *DAT_8032eed4 - 0x10U ^ 0x80000000;
    dVar9 = (double)(float)((double)CONCAT44(0x43300000,uStack_5c) - dVar11);
    dVar10 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - dVar11);
    DrawInit__5CFontFv((CFont *)font);
    DrawNoShadowFont__8CMenuPcsFP5CFontPcffii(dVar10,dVar9,&MenuPcs,font,iVar8,0x18,0x12);
    DrawInit__8CMenuPcsFv(&MenuPcs);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x24);
    iVar6 = iVar6 + 1;
    piVar7 = piVar7 + 3;
  } while (iVar6 < 3);
  DrawInit__8CMenuPcsFv(&MenuPcs);
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x28);
  return;
}

