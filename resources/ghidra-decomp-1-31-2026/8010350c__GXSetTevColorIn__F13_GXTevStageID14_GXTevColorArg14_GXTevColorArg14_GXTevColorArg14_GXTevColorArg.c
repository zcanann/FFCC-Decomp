// Function: _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
// Entry: 8010350c
// Size: 112 bytes

void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg
               (int param_1,int param_2,int param_3,int param_4,int param_5)

{
  param_1 = param_1 * 0x10;
  if ((((*(int *)(s_GXSetTevColorIn_Reg + param_1) != param_2) ||
       (*(int *)(s_GXSetTevColorIn_Reg + param_1 + 4) != param_3)) ||
      (*(int *)(s_GXSetTevColorIn_Reg + param_1 + 8) != param_4)) ||
     (*(int *)(s_GXSetTevColorIn_Reg + param_1 + 0xc) != param_5)) {
    *(int *)(s_GXSetTevColorIn_Reg + param_1) = param_2;
    *(int *)(s_GXSetTevColorIn_Reg + param_1 + 4) = param_3;
    *(int *)(s_GXSetTevColorIn_Reg + param_1 + 8) = param_4;
    *(int *)(s_GXSetTevColorIn_Reg + param_1 + 0xc) = param_5;
    GXSetTevColorIn();
  }
  return;
}

