// Function: ARStartDMA
// Entry: 8018f790
// Size: 240 bytes

void ARStartDMA(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  ushort uVar1;
  
  OSDisableInterrupts();
  uVar1 = DAT_cc005020;
  DAT_cc005020 = uVar1 & 0xfc00 | (ushort)((uint)param_2 >> 0x10);
  uVar1 = DAT_cc005022;
  DAT_cc005022 = uVar1 & 0x1f | (ushort)param_2;
  uVar1 = DAT_cc005024._0_2_;
  DAT_cc005024._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)param_3 >> 0x10);
  uVar1 = DAT_cc005024._2_2_;
  DAT_cc005024._2_2_ = uVar1 & 0x1f | (ushort)param_3;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = (ushort)(param_1 << 0xf) | uVar1 & 0x7fff;
  uVar1 = DAT_cc005028._0_2_;
  DAT_cc005028._0_2_ = uVar1 & 0xfc00 | (ushort)((uint)param_4 >> 0x10);
  uVar1 = DAT_cc005028._2_2_;
  DAT_cc005028._2_2_ = uVar1 & 0x1f | (ushort)param_4;
  OSRestoreInterrupts();
  return;
}

