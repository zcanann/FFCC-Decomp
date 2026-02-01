// Function: _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
// Entry: 801031e8
// Size: 112 bytes

void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan
               (int param_1,int param_2,int param_3,int param_4,int param_5)

{
  param_1 = param_1 * 0x10;
  if ((((*(int *)(s_GXSetTevSwapModeTable_Reg + param_1) != param_2) ||
       (*(int *)(s_GXSetTevSwapModeTable_Reg + param_1 + 4) != param_3)) ||
      (*(int *)(s_GXSetTevSwapModeTable_Reg + param_1 + 8) != param_4)) ||
     (*(int *)(s_GXSetTevSwapModeTable_Reg + param_1 + 0xc) != param_5)) {
    *(int *)(s_GXSetTevSwapModeTable_Reg + param_1) = param_2;
    *(int *)(s_GXSetTevSwapModeTable_Reg + param_1 + 4) = param_3;
    *(int *)(s_GXSetTevSwapModeTable_Reg + param_1 + 8) = param_4;
    *(int *)(s_GXSetTevSwapModeTable_Reg + param_1 + 0xc) = param_5;
    GXSetTevSwapModeTable();
  }
  return;
}

