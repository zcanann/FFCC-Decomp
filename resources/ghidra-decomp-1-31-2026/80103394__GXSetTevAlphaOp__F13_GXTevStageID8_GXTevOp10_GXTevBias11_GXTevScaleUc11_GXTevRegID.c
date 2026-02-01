// Function: _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
// Entry: 80103394
// Size: 132 bytes

void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID
               (int param_1,int param_2,int param_3,int param_4,char param_5,int param_6)

{
  param_1 = param_1 * 0x14;
  if ((((*(int *)(s_GXSetTevAlphaOp_Reg + param_1) != param_2) ||
       (*(int *)(s_GXSetTevAlphaOp_Reg + param_1 + 4) != param_3)) ||
      (*(int *)(s_GXSetTevAlphaOp_Reg + param_1 + 8) != param_4)) ||
     ((s_GXSetTevAlphaOp_Reg[param_1 + 0xc] != param_5 ||
      (*(int *)(s_GXSetTevAlphaOp_Reg + param_1 + 0x10) != param_6)))) {
    *(int *)(s_GXSetTevAlphaOp_Reg + param_1) = param_2;
    *(int *)(s_GXSetTevAlphaOp_Reg + param_1 + 4) = param_3;
    *(int *)(s_GXSetTevAlphaOp_Reg + param_1 + 8) = param_4;
    s_GXSetTevAlphaOp_Reg[param_1 + 0xc] = param_5;
    *(int *)(s_GXSetTevAlphaOp_Reg + param_1 + 0x10) = param_6;
    GXSetTevAlphaOp();
  }
  return;
}

