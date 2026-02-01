// Function: SetDrawDoneDebugData__8CGraphicFSc
// Entry: 800196e0
// Size: 56 bytes

void SetDrawDoneDebugData__8CGraphicFSc(CGraphic *graphic,uint param_2)

{
  GXSetDrawSync(param_2 & 0xff | (System.m_currentOrderIndex & 0xffU) << 8);
  return;
}

