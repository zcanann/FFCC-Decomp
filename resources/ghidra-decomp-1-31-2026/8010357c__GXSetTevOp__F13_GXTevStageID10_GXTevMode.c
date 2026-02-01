// Function: _GXSetTevOp__F13_GXTevStageID10_GXTevMode
// Entry: 8010357c
// Size: 96 bytes

void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int param_1)

{
  *(undefined4 *)(s_GXSetTevColorIn_Reg + param_1 * 0x10) = 0xffffffff;
  *(undefined4 *)(s_GXSetTevAlphaIn_Reg + param_1 * 0x10) = 0xffffffff;
  *(undefined4 *)(s_GXSetTevColorOp_Reg + param_1 * 0x14) = 0xffffffff;
  *(undefined4 *)(s_GXSetTevAlphaOp_Reg + param_1 * 0x14) = 0xffffffff;
  *(undefined4 *)(s_GXSetTevSwapMode_Reg + param_1 * 8) = 0xffffffff;
  GXSetTevOp();
  return;
}

