// Function: draw__11CDbgMenuPcsFv
// Entry: 8012cd10
// Size: 120 bytes

void draw__11CDbgMenuPcsFv(int param_1)

{
  *(undefined4 *)(param_1 + 0x2a68) = 0xffffffff;
  InitDebugString__8CGraphicFv(&Graphic);
  _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1,4,5,1);
  GXSetNumChans(1);
  if (*(int *)(param_1 + 0x58) != 0) {
    drawMenu__11CDbgMenuPcsFPQ211CDbgMenuPcs3CDM(param_1);
  }
  SetViewport__8CGraphicFv(&Graphic);
  return;
}

