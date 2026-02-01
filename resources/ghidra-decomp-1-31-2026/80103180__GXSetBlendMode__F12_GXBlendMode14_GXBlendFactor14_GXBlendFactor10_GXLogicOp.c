// Function: _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp
// Entry: 80103180
// Size: 104 bytes

void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp
               (int param_1,int param_2,int param_3,int param_4)

{
  if ((((ARRAY_802ffa60._0_4_ != param_1) || (ARRAY_802ffa60._4_4_ != param_2)) ||
      (ARRAY_802ffa60._8_4_ != param_3)) || (ARRAY_802ffa60._12_4_ != param_4)) {
    ARRAY_802ffa60._0_4_ = param_1;
    ARRAY_802ffa60._4_4_ = param_2;
    ARRAY_802ffa60._8_4_ = param_3;
    ARRAY_802ffa60._12_4_ = param_4;
    GXSetBlendMode();
  }
  return;
}

