// Function: __GXInitGX
// Entry: 8019fa04
// Size: 2244 bytes

void __GXInitGX(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  local_58 = DAT_8033382c;
  local_5c = DAT_80333830;
  local_60 = DAT_80333834;
  iVar2 = VIGetTvFormat();
  if (iVar2 == 2) {
    iVar2 = -0x7fde39a4;
    goto LAB_8019faac;
  }
  if (iVar2 < 2) {
    if (iVar2 == 0) {
      iVar2 = -0x7fde39e0;
      goto LAB_8019faac;
    }
    if (-1 < iVar2) {
      iVar2 = -0x7fde3968;
      goto LAB_8019faac;
    }
  }
  else if (iVar2 == 5) {
    iVar2 = -0x7fde392c;
    goto LAB_8019faac;
  }
  iVar2 = -0x7fde39e0;
LAB_8019faac:
  local_64 = local_58;
  GXSetCopyClear(&local_64,0xffffff);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  GXSetTexCoordGen2(1,1,5,0x3c,0,0x7d);
  GXSetTexCoordGen2(2,1,6,0x3c,0,0x7d);
  GXSetTexCoordGen2(3,1,7,0x3c,0,0x7d);
  GXSetTexCoordGen2(4,1,8,0x3c,0,0x7d);
  GXSetTexCoordGen2(5,1,9,0x3c,0,0x7d);
  GXSetTexCoordGen2(6,1,10,0x3c,0,0x7d);
  GXSetTexCoordGen2(7,1,0xb,0x3c,0,0x7d);
  GXSetNumTexGens(1);
  GXClearVtxDesc();
  GXInvalidateVtxCache();
  uVar3 = 9;
  do {
    GXSetArray(uVar3,DAT_80333828,0);
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x19);
  uVar3 = 0;
  do {
    GXSetVtxAttrFmtv(uVar3,&DAT_8021c3c4);
    uVar3 = uVar3 + 1;
  } while (uVar3 < 8);
  GXSetLineWidth(6,0);
  GXSetPointSize(6,0);
  GXEnableTexOffsets(0,0,0);
  GXEnableTexOffsets(1,0,0);
  GXEnableTexOffsets(2,0,0);
  GXEnableTexOffsets(3,0,0);
  GXEnableTexOffsets(4,0,0);
  GXEnableTexOffsets(5,0,0);
  GXEnableTexOffsets(6,0,0);
  GXEnableTexOffsets(7,0,0);
  local_54 = FLOAT_80333838;
  local_50 = FLOAT_8033383c;
  local_4c = FLOAT_8033383c;
  local_48 = FLOAT_8033383c;
  local_44 = FLOAT_8033383c;
  local_40 = FLOAT_80333838;
  local_3c = FLOAT_8033383c;
  local_38 = FLOAT_8033383c;
  local_34 = FLOAT_8033383c;
  local_30 = FLOAT_8033383c;
  local_2c = FLOAT_80333838;
  local_28 = FLOAT_8033383c;
  GXLoadPosMtxImm(&local_54,0);
  GXLoadNrmMtxImm(&local_54,0);
  GXSetCurrentMtx(0);
  GXLoadTexMtxImm(&local_54,0x3c,0);
  GXLoadTexMtxImm(&local_54,0x7d,0);
  uStack_14 = (uint)*(ushort *)(iVar2 + 4);
  uStack_1c = (uint)*(ushort *)(iVar2 + 8);
  dVar4 = (double)FLOAT_8033383c;
  local_18 = 0x43300000;
  local_20 = 0x43300000;
  GXSetViewport(dVar4,dVar4,
                (double)(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80333848),
                (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80333848),dVar4,
                (double)FLOAT_80333838);
  GXSetProjectionv(&DAT_8021c494);
  GXSetCoPlanar(0);
  GXSetCullMode(2);
  GXSetClipMode(0);
  GXSetScissor(0,0,*(undefined2 *)(iVar2 + 4),*(undefined2 *)(iVar2 + 6));
  GXSetScissorBoxOffset(0,0);
  GXSetNumChans(0);
  GXSetChanCtrl(4,0,0,1,0,0,2);
  local_68 = local_5c;
  GXSetChanAmbColor(4,&local_68);
  local_6c = local_60;
  GXSetChanMatColor(4,&local_6c);
  GXSetChanCtrl(5,0,0,1,0,0,2);
  local_70 = local_5c;
  GXSetChanAmbColor(5,&local_70);
  local_74 = local_60;
  GXSetChanMatColor(5,&local_74);
  GXInvalidateTexAll();
  iVar1 = DAT_80333828;
  uVar3 = 0;
  *(undefined4 *)(DAT_80333828 + 0x2c8) = 0;
  *(undefined4 *)(iVar1 + 0x2cc) = 0;
  GXSetTexRegionCallback(__GXDefaultTexRegionCallback);
  GXSetTlutRegionCallback(__GXDefaultTlutRegionCallback);
  GXSetTevOrder(0,0,0,4);
  GXSetTevOrder(1,1,1,4);
  GXSetTevOrder(2,2,2,4);
  GXSetTevOrder(3,3,3,4);
  GXSetTevOrder(4,4,4,4);
  GXSetTevOrder(5,5,5,4);
  GXSetTevOrder(6,6,6,4);
  GXSetTevOrder(7,7,7,4);
  GXSetTevOrder(8,0xff,0xff,0xff);
  GXSetTevOrder(9,0xff,0xff,0xff);
  GXSetTevOrder(10,0xff,0xff,0xff);
  GXSetTevOrder(0xb,0xff,0xff,0xff);
  GXSetTevOrder(0xc,0xff,0xff,0xff);
  GXSetTevOrder(0xd,0xff,0xff,0xff);
  GXSetTevOrder(0xe,0xff,0xff,0xff);
  GXSetTevOrder(0xf,0xff,0xff,0xff);
  GXSetNumTevStages(1);
  GXSetTevOp(0,3);
  GXSetAlphaCompare(7,0,0,7,0);
  GXSetZTexture(0,0x11,0);
  do {
    GXSetTevKColorSel(uVar3,6);
    GXSetTevKAlphaSel(uVar3,0);
    GXSetTevSwapMode(uVar3,0,0);
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x10);
  GXSetTevSwapModeTable(0,0,1,2,3);
  GXSetTevSwapModeTable(1,0,0,0,3);
  GXSetTevSwapModeTable(2,1,1,1,3);
  GXSetTevSwapModeTable(3,2,2,2,3);
  uVar3 = 0;
  do {
    GXSetTevDirect(uVar3);
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x10);
  GXSetNumIndStages(0);
  GXSetIndTexCoordScale(0,0,0);
  GXSetIndTexCoordScale(1,0,0);
  GXSetIndTexCoordScale(2,0,0);
  GXSetIndTexCoordScale(3,0,0);
  local_78 = local_5c;
  GXSetFog((double)FLOAT_8033383c,(double)FLOAT_80333838,(double)FLOAT_80333840,
           (double)FLOAT_80333838,0,&local_78);
  GXSetFogRangeAdj(0,0,0);
  GXSetBlendMode(0,4,5,0);
  GXSetColorUpdate(1);
  GXSetAlphaUpdate(1);
  GXSetZMode(1,3,1);
  GXSetZCompLoc(1);
  GXSetDither(1);
  GXSetDstAlpha(0,0);
  GXSetPixelFmt(0,0);
  GXSetFieldMask(1,1);
  GXSetFieldMode(*(undefined *)(iVar2 + 0x18),
                 (uint)*(ushort *)(iVar2 + 0x10) == (uint)*(ushort *)(iVar2 + 8) << 1);
  GXSetDispCopySrc(0,0,*(undefined2 *)(iVar2 + 4),*(undefined2 *)(iVar2 + 6));
  GXSetDispCopyDst(*(undefined2 *)(iVar2 + 4),*(undefined2 *)(iVar2 + 6));
  uStack_1c = (uint)*(ushort *)(iVar2 + 8);
  uStack_14 = (uint)*(ushort *)(iVar2 + 6);
  local_20 = 0x43300000;
  local_18 = 0x43300000;
  GXSetDispCopyYScale((double)((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_80333848) /
                              (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80333848)));
  GXSetCopyClamp(3);
  GXSetCopyFilter(*(undefined *)(iVar2 + 0x19),iVar2 + 0x1a,1,iVar2 + 0x32);
  GXSetDispCopyGamma(0);
  GXSetDispCopyFrame2Field(0);
  GXClearBoundingBox();
  GXPokeColorUpdate(1);
  GXPokeAlphaUpdate(1);
  GXPokeDither(0);
  GXPokeBlendMode(0,0,1,0xf);
  GXPokeAlphaMode(7,0);
  GXPokeAlphaRead(1);
  GXPokeDstAlpha(0,0);
  GXPokeZMode(1,7,1);
  GXSetGPMetric(0x23,0x16);
  GXClearGPMetric();
  return;
}

