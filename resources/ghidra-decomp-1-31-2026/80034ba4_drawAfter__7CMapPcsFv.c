// Function: drawAfter__7CMapPcsFv
// Entry: 80034ba4
// Size: 540 bytes

void drawAfter__7CMapPcsFv(int param_1)

{
  undefined4 *puVar1;
  undefined auStack_98 [4];
  undefined4 local_94;
  undefined4 local_90 [6];
  Mat4x4 MStack_78;
  Mtx MStack_38;
  
  if (*(int *)(param_1 + 0x178) == 0) {
    if (*(int *)(param_1 + 0x180) != 0) {
      InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei
                (&MaterialMan,0xffffffff,4,0,3,0xe,3,10);
      MapMng._141548_4_ = CameraPcs._224_4_;
      MapMng._141552_4_ = CameraPcs._228_4_;
      MapMng._141556_4_ = CameraPcs._232_4_;
      PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_38);
      PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_78);
      GXSetColorUpdate(1);
      GXSetAlphaUpdate(0);
      GXSetCullMode(1);
      GXSetZMode(1,3,1);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (0,0,1,2,3);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (1,0,1,2,3);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (2,0,1,2,3);
      _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
                (3,0,1,2,3);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0,0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1,0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2,0,0);
      _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(3,0,0);
      DrawAfter__7CMapMngFv(&MapMng);
      if ((CFlat._4764_4_ & 0x2000000) != 0) {
        local_90[0] = CameraPcs._1044_4_;
        local_90[1] = CameraPcs._1048_4_;
        local_90[2] = CameraPcs._1052_4_;
        local_90[3] = CameraPcs._1056_4_;
        local_90[4] = CameraPcs._1060_4_;
        local_90[5] = CameraPcs._1064_4_;
        puVar1 = (undefined4 *)__ct__6CColorFUcUcUcUc(auStack_98,0xff,0xff,0x80,0xff);
        local_94 = *puVar1;
        DrawBound__8CGraphicFR6CBound8_GXColor(&Graphic,local_90,&local_94);
      }
    }
  }
  return;
}

