// Function: _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc
// Entry: 80103308
// Size: 140 bytes

void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc
               (int param_1,ushort param_2,int param_3,int param_4,ushort param_5)

{
  if ((((ARRAY_802ffa50._0_4_ != param_1) || (ARRAY_802ffa50._4_4_ != param_3)) ||
      (ARRAY_802ffa50._8_4_ != param_4)) ||
     ((ARRAY_802ffa50._12_2_ != (param_2 & 0xff) || (ARRAY_802ffa50._14_2_ != (param_5 & 0xff))))) {
    ARRAY_802ffa50._12_2_ = param_2 & 0xff;
    ARRAY_802ffa50._14_2_ = param_5 & 0xff;
    ARRAY_802ffa50._0_4_ = param_1;
    ARRAY_802ffa50._4_4_ = param_3;
    ARRAY_802ffa50._8_4_ = param_4;
    GXSetAlphaCompare();
  }
  return;
}

