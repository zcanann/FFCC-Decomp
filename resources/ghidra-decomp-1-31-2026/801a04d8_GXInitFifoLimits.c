// Function: GXInitFifoLimits
// Entry: 801a04d8
// Size: 12 bytes

void GXInitFifoLimits(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0xc) = param_2;
  *(undefined4 *)(param_1 + 0x10) = param_3;
  return;
}

