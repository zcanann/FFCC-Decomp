// Function: __ct__Q26CChara9CAnimNodeFv
// Entry: 800bf8f0
// Size: 32 bytes

void __ct__Q26CChara9CAnimNodeFv(int param_1)

{
  *(byte *)(param_1 + 0x14) = *(byte *)(param_1 + 0x14) & 0x7f;
  *(uint *)(param_1 + 0x14) = *(uint *)(param_1 + 0x14) & 0x80001fff;
  return;
}

