// Function: SetGroup__7CMemoryFPvi
// Entry: 8001ec80
// Size: 20 bytes

void SetGroup__7CMemoryFPvi(undefined4 param_1,int param_2,int param_3)

{
  *(byte *)(param_2 + -0x3e) = *(byte *)(param_2 + -0x3e) & 0xf | (byte)(param_3 << 4);
  return;
}

