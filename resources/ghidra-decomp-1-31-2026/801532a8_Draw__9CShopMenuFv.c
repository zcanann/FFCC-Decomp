// Function: Draw__9CShopMenuFv
// Entry: 801532a8
// Size: 984 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void Draw__9CShopMenuFv(CShopMenu *shopMenu)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_d4;
  undefined4 local_d0;
  uint local_cc;
  uint local_c8;
  uint local_c4;
  uint local_c0;
  uint local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  Mtx local_88;
  Mtx MStack_58;
  longlong local_18;
  
  if ((shopMenu->field0_0x0).ref.vtable == (void *)0x0) {
    (shopMenu->field0_0x0).ref.vtable = (void *)0x1;
  }
  else {
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x46);
    pppEnvStPtr = (_pppEnvSt *)PartMng.m_pdtSlots[*(int *)&shopMenu->field_0x18].field1_0x4;
    DrawInit__8CMenuPcsFv(&MenuPcs);
    iVar2 = (shopMenu->field0_0x0).ref.refCount;
    if (iVar2 < 9) {
      if (iVar2 < 3) {
        if (-1 < iVar2) {
          DrawShop0__9CShopMenuFv(shopMenu);
        }
      }
      else if (iVar2 < 6) {
        DrawShopBase__9CShopMenuFv(shopMenu);
        DrawItemList__9CShopMenuFv(shopMenu);
        DrawItemInfo0__9CShopMenuFv(shopMenu);
        DrawBuySellInfo__9CShopMenuFv(shopMenu);
      }
      else {
        DrawShopBase__9CShopMenuFv(shopMenu);
        DrawItemList__9CShopMenuFv(shopMenu);
        DrawItemInfo0__9CShopMenuFv(shopMenu);
        DrawBuySellInfo__9CShopMenuFv(shopMenu);
      }
    }
    else if (iVar2 < 0xf) {
      if (iVar2 < 0xc) {
        DrawSmith0__9CShopMenuFv(shopMenu);
      }
      else {
        DrawMake__9CShopMenuFv(shopMenu);
      }
    }
    else if (iVar2 < 0x12) {
      DrawSoubi__9CShopMenuFv(shopMenu);
    }
    if (FLOAT_80332d28 != *(float *)&shopMenu->field_0x1c) {
      iVar2 = (int)(FLOAT_80332de0 * *(float *)&shopMenu->field_0x1c);
      local_18 = (longlong)iVar2;
      local_bc = (uint)(byte)(-(char)iVar2 - 1);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x32);
      PSMTXIdentity(&local_88);
      local_88.value[0][0] = FLOAT_80332d78;
      local_88.value[1][1] = FLOAT_80332dd0;
      local_88.value[2][2] = FLOAT_80332d78;
      local_88.value[0][3] = FLOAT_80332de4;
      local_88.value[1][3] = FLOAT_80332de8;
      GXLoadPosMtxImm(&local_88,0);
      GXSetCurrentMtx(0);
      C_MTXOrtho(FLOAT_80332d9c,FLOAT_80332dec,FLOAT_80332d9c,FLOAT_80332df0,FLOAT_80332d9c,
                 FLOAT_80332d28,&MStack_58);
      MStack_58.value[2][3] = MStack_58.value[2][3] + FLOAT_80332d9c;
      GXSetProjection(&MStack_58,1);
      uVar1 = DAT_80332d0c;
      local_d4 = DAT_80332d08;
      GXSetChanAmbColor(4,&local_d4);
      local_d0 = uVar1;
      GXSetChanMatColor(4,&local_d0);
      _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
      _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
      GXSetZCompLoc(1);
      GXSetZMode(0,3,0);
      GXSetCullMode(0);
      GXSetNumTexGens(0);
      GXSetNumTevStages(1);
      _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
      _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
      GXSetNumChans(1);
      GXSetChanCtrl(0,1,0,1,0,2,2);
      GXSetChanCtrl(2,1,0,1,0,2,2);
      GXClearVtxDesc();
      GXSetVtxDesc(9,1);
      GXSetVtxDesc(0xb,1);
      local_b8 = FLOAT_80332df4;
      local_b4 = FLOAT_80332df8;
      local_b0 = FLOAT_80332d9c;
      local_ac = FLOAT_80332dfc;
      local_a8 = FLOAT_80332e00;
      local_a4 = FLOAT_80332d9c;
      local_c0 = local_bc;
      local_c4 = local_bc;
      local_c8 = local_bc;
      local_cc = local_bc;
      local_94 = FLOAT_80332dfc;
      local_90 = FLOAT_80332e00;
      local_8c = FLOAT_80332d9c;
      local_a0 = FLOAT_80332df4;
      local_9c = FLOAT_80332df8;
      local_98 = FLOAT_80332d9c;
      RenderNoTexQuadGrouad__8CGraphicF3Vec3Vec8_GXColor8_GXColor8_GXColor8_GXColor
                (&Graphic,&local_a0,&local_94,&local_cc,&local_c8,&local_c4,&local_c0);
      SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x33);
    }
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic,0x3c);
  }
  return;
}

