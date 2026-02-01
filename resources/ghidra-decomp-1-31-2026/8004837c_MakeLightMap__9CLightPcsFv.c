// Function: MakeLightMap__9CLightPcsFv
// Entry: 8004837c
// Size: 712 bytes

void MakeLightMap__9CLightPcsFv(int param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  Mat4x4 MStack_58;
  
  GXSetCullMode(2);
  GXSetZCompLoc(1);
  GXSetZMode(1,3,1);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0,0,0,5);
  _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7,0,0,7,0xff);
  GXSetColorUpdate(1);
  GXSetPixelFmt(1,0);
  dVar4 = (double)FLOAT_8032fc14;
  GXSetViewport(dVar4,dVar4,(double)FLOAT_8032fc28,(double)FLOAT_8032fc28,dVar4,
                (double)FLOAT_8032fc1c);
  GXSetScissor(0,0,0x40,0x40);
  C_MTXOrtho(FLOAT_8032fc2c,FLOAT_8032fc1c,FLOAT_8032fc2c,FLOAT_8032fc1c,FLOAT_8032fc1c,
             FLOAT_8032fc30,(Mtx *)&MStack_58);
  GXSetProjection(&MStack_58,1);
  GXSetChanCtrl(0,1,0,0,1,2,2);
  GXSetChanCtrl(2,1,0,0,1,0,0);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (0,0,1,2,3);
  GXSetTevDirect(0);
  _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0,0xff,0xff,4);
  _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0,4);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  GXSetNumIndStages(0);
  GXSetNumTevStages(1);
  GXSetNumTexGens(0);
  GXSetNumChans(1);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(10,1);
  GXSetVtxAttrFmt(0,9,1,4,0);
  GXSetVtxAttrFmt(0,10,0,4,0);
  GXSetAlphaUpdate(1);
  uVar2 = 0;
  do {
    uVar1 = 0;
    iVar3 = param_1;
    do {
      if (*(char *)(iVar3 + 0x1cec) != '\0') {
        MakeLightMap__Q29CLightPcs10CBumpLightFv(iVar3 + 0x1c3c);
      }
      uVar1 = uVar1 + 1;
      iVar3 = iVar3 + 0x138;
    } while (uVar1 < 8);
    uVar2 = uVar2 + 1;
    param_1 = param_1 + 0x9c0;
  } while (uVar2 < 4);
  SetStdPixelFmt__8CGraphicFv(&Graphic);
  setViewport__11CGraphicPcsFv(&GraphicsPcs);
  PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_58);
  GXSetProjection(&MStack_58,0);
  GXSetCullMode(1);
  GXSetAlphaUpdate(0);
  GXSetTexCopySrc(0,0,0x40,0x40);
  GXSetTexCopyDst(0x40,0x40,3,0);
  GXCopyTex(DAT_80238030,1);
  return;
}

