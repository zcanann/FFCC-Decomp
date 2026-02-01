// Function: DrawShopBase__9CShopMenuFv
// Entry: 80152b2c
// Size: 1916 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void DrawShopBase__9CShopMenuFv(CShopMenu *shopMenu)

{
  undefined4 font;
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int unaff_r30;
  double dVar6;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
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
  
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,1);
  iVar5 = Game.game.m_gameWork.m_languageId - 1;
  DrawSingleBase__8CMenuPcsFf((double)FLOAT_80332d28,&MenuPcs);
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,2);
  pppInitDrawEnv__FUc(0);
  GXSetVtxAttrFmt(7,9,1,4,0);
  GXSetVtxAttrFmt(7,0xb,1,5,0);
  GXSetVtxAttrFmt(7,0xd,1,4,0);
  GXSetNumChans(1);
  GXSetChanCtrl(0,1,0,1,0,0,2);
  GXSetChanCtrl(2,1,0,1,0,0,2);
  GXSetCullMode(0);
  GXSetZMode(1,3,1);
  GXSetColorUpdate(1);
  iVar1 = (shopMenu->field0_0x0).ref.refCount;
  if (iVar1 < 3) {
    unaff_r30 = 0xe6;
  }
  else if (iVar1 < 9) {
    unaff_r30 = 0x154;
  }
  else if (iVar1 < 0xc) {
    unaff_r30 = 0x118;
  }
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,3);
  local_80 = 0xffffff00;
  local_7c = 0xffffffff;
  local_84 = 0xffffffff;
  local_88 = 0xffffff00;
  drawShapeSeqGrouad__Fiiiiff8_GXColor8_GXColor8_GXColor8_GXColor
            ((double)FLOAT_80332d78,(double)FLOAT_80332dc8,9,0,0x1c,unaff_r30 + 0x22,&local_88,
             &local_84,&local_80,&local_7c);
  for (iVar1 = 0x3c; iVar1 < 0x25c; iVar1 = iVar1 + 0x20) {
    local_6c = 0xffffffff;
    local_70 = 0xffffffff;
    local_74 = 0xffffffff;
    local_78 = 0xffffffff;
    drawShapeSeqGrouad__Fiiiiff8_GXColor8_GXColor8_GXColor8_GXColor
              ((double)FLOAT_80332d78,(double)FLOAT_80332dc8,9,0,iVar1,unaff_r30 + 0x22,&local_78,
               &local_74,&local_70,&local_6c);
  }
  local_60 = 0xffffffff;
  local_5c = 0xffffff00;
  local_64 = 0xffffff00;
  local_68 = 0xffffffff;
  drawShapeSeqGrouad__Fiiiiff8_GXColor8_GXColor8_GXColor8_GXColor
            ((double)FLOAT_80332d78,(double)FLOAT_80332dc8,9,0,iVar1,unaff_r30 + 0x22,&local_68,
             &local_64,&local_60,&local_5c);
  SetDrawDoneDebugData__8CGraphicFSc(&Graphic,4);
  iVar1 = (shopMenu->field0_0x0).ref.refCount;
  if (2 < iVar1) {
    if (iVar1 < 9) {
      iVar1 = 100;
    }
    else {
      iVar1 = 0x118;
    }
    for (iVar3 = iVar1 + 0x48; iVar3 < 0x244; iVar3 = iVar3 + 8) {
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,5);
      drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0x10,0,iVar3,0x11e,0xff,0,0,0);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,6);
    }
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,7);
    drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xd,0,iVar1 + 0x46,0xa7,0xff,0,0,0);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,8);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,9);
    drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,8,0,iVar3,0x11e,0xff,0,0,0);
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,10);
    if ((shopMenu->field0_0x0).ref.refCount < 9) {
      iVar1 = 0x4e;
      do {
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0xb);
        drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xc,0,iVar1,0x174,0xff,0,0,0);
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0xc);
        iVar1 = iVar1 + -0x10;
      } while (0x32 < iVar1);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0xd);
      drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,0xb,0,0x7e,0x150,0xff,0,0,0);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0xe);
      drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,8,0,iVar1,0x170,0xff,0,0,0);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0xf);
      font = MenuPcs._264_4_;
      SetMargin__5CFontFf(FLOAT_80332d28,(CFont *)MenuPcs._264_4_);
      SetShadow__5CFontFi((CFont *)font,0);
      SetScaleX__5CFontFf(FLOAT_80332d2c,(CFont *)font);
      SetScaleY__5CFontFf(FLOAT_80332d28,(CFont *)font);
      puVar2 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_58,0xff,0xff,0xff,0xff);
      local_54 = *puVar2;
      SetColor__5CFontF8_GXColor((CFont *)font,&local_54);
      DrawInit__5CFontFv((CFont *)font);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x10);
      if (*(int *)&shopMenu->field_0x14 == 0) {
        puVar4 = (&PTR_DAT_80214d90)[iVar5 * 0x15];
      }
      else {
        puVar4 = (&PTR_DAT_80214d94)[iVar5 * 0x15];
      }
      dVar6 = (double)GetWidth__5CFontFPc((CFont *)font,puVar4);
      puStack_4c = &DAT_80000050;
      local_50 = 0x43300000;
      local_40 = 0x43300000;
      uStack_3c = (uint)((float)((double)FLOAT_80332dd4 - dVar6) * FLOAT_80332d78 +
                        (float)(4503601774854224.0 - DOUBLE_80332d20));
      local_48 = (longlong)(int)uStack_3c;
      uStack_3c = uStack_3c ^ 0x80000000;
      SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80332d20),
                        (CFont *)font);
      SetPosY__5CFontFf(FLOAT_80332dd8,(CFont *)font);
      Draw__5CFontFPc((CFont *)font,puVar4);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x11);
      puVar4 = (&PTR_s_Cancel_80214d98)[iVar5 * 0x15];
      dVar6 = (double)GetWidth__5CFontFPc((CFont *)font,puVar4);
      puStack_34 = &DAT_80000050;
      local_38 = 0x43300000;
      local_28 = 0x43300000;
      uStack_24 = (uint)((float)((double)FLOAT_80332dd4 - dVar6) * FLOAT_80332d78 +
                        (float)(4503601774854224.0 - DOUBLE_80332d20));
      local_30 = (longlong)(int)uStack_24;
      uStack_24 = uStack_24 ^ 0x80000000;
      SetPosX__5CFontFf((float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80332d20),
                        (CFont *)font);
      SetPosY__5CFontFf(FLOAT_80332ddc,(CFont *)font);
      Draw__5CFontFPc((CFont *)font,puVar4);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x12);
      DrawInit__8CMenuPcsFv(&MenuPcs);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x13);
      if (*(int *)&shopMenu->field_0x10 == 2) {
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x14);
        DrawCursor__8CMenuPcsFiif
                  ((double)FLOAT_80332d28,&MenuPcs,0x2c,*(int *)&shopMenu->field_0x3c * 0x18 + 0x134
                  );
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x15);
      }
    }
  }
  return;
}

