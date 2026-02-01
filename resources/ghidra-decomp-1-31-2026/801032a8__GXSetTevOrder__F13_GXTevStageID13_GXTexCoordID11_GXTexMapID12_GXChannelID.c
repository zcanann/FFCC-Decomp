// Function: _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
// Entry: 801032a8
// Size: 96 bytes

void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID
               (int param_1,int param_2,int param_3,int param_4)

{
  param_1 = param_1 * 0xc;
  if (((*(int *)(s_GXSetTevOrder_Reg + param_1) != param_2) ||
      (*(int *)(s_GXSetTevOrder_Reg + param_1 + 4) != param_3)) ||
     (*(int *)(s_GXSetTevOrder_Reg + param_1 + 8) != param_4)) {
    *(int *)(s_GXSetTevOrder_Reg + param_1) = param_2;
    *(int *)(s_GXSetTevOrder_Reg + param_1 + 4) = param_3;
    *(int *)(s_GXSetTevOrder_Reg + param_1 + 8) = param_4;
    GXSetTevOrder();
  }
  return;
}

