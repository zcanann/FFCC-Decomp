// Function: _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
// Entry: 80103258
// Size: 80 bytes

void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel
               (int param_1,int param_2,int param_3)

{
  param_1 = param_1 * 8;
  if ((*(int *)(s_GXSetTevSwapMode_Reg + param_1) != param_2) ||
     (*(int *)(s_GXSetTevSwapMode_Reg + param_1 + 4) != param_3)) {
    *(int *)(s_GXSetTevSwapMode_Reg + param_1) = param_2;
    *(int *)(s_GXSetTevSwapMode_Reg + param_1 + 4) = param_3;
    GXSetTevSwapMode();
  }
  return;
}

