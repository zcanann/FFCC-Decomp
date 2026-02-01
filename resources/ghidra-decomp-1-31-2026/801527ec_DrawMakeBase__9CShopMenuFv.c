// Function: DrawMakeBase__9CShopMenuFv
// Entry: 801527ec
// Size: 832 bytes

void DrawMakeBase__9CShopMenuFv(void)

{
  int iVar1;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c [2];
  
  DrawSingleBase__8CMenuPcsFf((double)FLOAT_80332d28,&MenuPcs);
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
  local_40 = 0xffffff00;
  local_3c = 0xffffffff;
  local_44 = 0xffffffff;
  local_48 = 0xffffff00;
  drawShapeSeqGrouad__Fiiiiff8_GXColor8_GXColor8_GXColor8_GXColor
            ((double)FLOAT_80332d78,(double)FLOAT_80332dc8,9,0,0x1c,0xb8,&local_48,&local_44,
             &local_40,&local_3c);
  for (iVar1 = 0x3c; iVar1 < 0x25c; iVar1 = iVar1 + 0x20) {
    local_2c = 0xffffffff;
    local_30 = 0xffffffff;
    local_34 = 0xffffffff;
    local_38 = 0xffffffff;
    drawShapeSeqGrouad__Fiiiiff8_GXColor8_GXColor8_GXColor8_GXColor
              ((double)FLOAT_80332d78,(double)FLOAT_80332dc8,9,0,iVar1,0xb8,&local_38,&local_34,
               &local_30,&local_2c);
  }
  local_20 = 0xffffffff;
  local_1c[0] = 0xffffff00;
  local_24 = 0xffffff00;
  local_28 = 0xffffffff;
  drawShapeSeqGrouad__Fiiiiff8_GXColor8_GXColor8_GXColor8_GXColor
            ((double)FLOAT_80332d78,(double)FLOAT_80332dc8,9,0,iVar1,0xb8,&local_28,&local_24,
             &local_20,local_1c);
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,3,0,0xb4,0x8c,0xff,0,0,0);
  iVar1 = 0xb4;
  do {
    drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,4,0,iVar1,0x8c,0xff,0,0,0);
    iVar1 = iVar1 + 0x20;
  } while (iVar1 < 0x1cc);
  drawShapeSeq__FiiiiUcUcUcfUc((double)FLOAT_80332d9c,3,0,iVar1,0x8c,0xff,1,0,0);
  return;
}

