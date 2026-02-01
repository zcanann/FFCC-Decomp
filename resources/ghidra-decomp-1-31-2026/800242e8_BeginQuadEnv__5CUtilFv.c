// Function: BeginQuadEnv__5CUtilFv
// Entry: 800242e8
// Size: 348 bytes

void BeginQuadEnv__5CUtilFv(void)

{
  undefined auStack_88 [24];
  Mtx MStack_70;
  Mtx MStack_40;
  
  PSMTXIdentity(&MStack_70);
  GXLoadPosMtxImm(&MStack_70,0);
  GXSetCurrentMtx(0);
  C_MTXOrtho(FLOAT_8032f888,FLOAT_8032f8a0,FLOAT_8032f888,FLOAT_8032f8a4,FLOAT_8032f888,
             FLOAT_8032f88c,&MStack_40);
  GXSetProjection(&MStack_40,1);
  GXSetCullMode(0);
  GXSetNumTexGens(1);
  GXSetNumChans(1);
  GXSetNumTevStages(1);
  GXSetZMode(0,3,0);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,5);
  _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
            (0,0,1,2,3);
  _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
  GXSetTexCoordGen2(0,1,4,0x3c,0,0x7d);
  GXSetChanCtrl(4,1,0,1,0,0,2);
  GXSetTevDirect(0);
  GXSetNumIndStages(0);
  memset(auStack_88,0,0x18);
  GXSetIndTexMtx(1,auStack_88,1);
  GXSetIndTexMtx(2,auStack_88,1);
  GXSetIndTexMtx(3,auStack_88,1);
  return;
}

