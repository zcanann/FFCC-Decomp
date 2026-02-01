// Function: SetDrawDoneDebugDataPartControl__8CGraphicFi
// Entry: 800196b8
// Size: 40 bytes

void SetDrawDoneDebugDataPartControl__8CGraphicFi(CGraphic *graphic,ushort param_2)

{
  GXSetDrawSync(param_2 | 0x8000);
  return;
}

