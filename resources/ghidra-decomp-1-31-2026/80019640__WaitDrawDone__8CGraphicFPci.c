// Function: _WaitDrawDone__8CGraphicFPci
// Entry: 80019640
// Size: 84 bytes

void _WaitDrawDone__8CGraphicFPci(CGraphic *graphic,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)&graphic->field_0x7368 = param_2;
  *(undefined4 *)&graphic->field_0x736c = param_3;
  *(undefined4 *)&graphic->field_0x7364 = 1;
  GXSetDrawDone();
  GXWaitDrawDone();
  *(undefined4 *)&graphic->field_0x7364 = 0;
  *(int *)&graphic->field_0x7370 = *(int *)&graphic->field_0x7370 + 1;
  return;
}

