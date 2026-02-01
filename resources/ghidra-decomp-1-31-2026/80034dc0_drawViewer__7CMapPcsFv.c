// Function: drawViewer__7CMapPcsFv
// Entry: 80034dc0
// Size: 532 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void drawViewer__7CMapPcsFv(int param_1)

{
  Mtx MStack_78;
  Mat4x4 MStack_48;
  
  if (((*(int *)(param_1 + 0x180) != 0) && (*(int *)(param_1 + 0x178) == 0)) &&
     (*(int *)(param_1 + 0x180) != 0)) {
    if (Game.game.m_currentSceneId == 3) {
      _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_map_cpp_801d7728,0x2c4);
    }
    InitVtxFmt__12CMaterialManFi11_GXCompTypei11_GXCompTypei11_GXCompTypei
              (&MaterialMan,0xffffffff,4,0,3,0xe,3,10);
    MapMng._141548_4_ = CameraPcs._224_4_;
    MapMng._141552_4_ = CameraPcs._228_4_;
    MapMng._141556_4_ = CameraPcs._232_4_;
    PSMTXCopy(&CameraPcs.m_cameraMatrix,&MStack_78);
    PSMTX44Copy(&CameraPcs.m_screenMatrix,&MStack_48);
    SetViewMtx__7CMapMngFPA4_fPA4_f(&MapMng,&MStack_78,&MStack_48);
    SetFog__8CGraphicFii(&Graphic,(uint)(byte)MapMng._141704_1_,0);
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
    Draw__7CMapMngFv(&MapMng);
    if (Game.game.m_currentSceneId == 3) {
      _WaitDrawDone__8CGraphicFPci(&Graphic,s_p_map_cpp_801d7728,0x2e0);
    }
  }
  return;
}

