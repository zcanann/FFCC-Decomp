// Function: ARQSetChunkSize
// Entry: 80191584
// Size: 32 bytes

void ARQSetChunkSize(uint param_1)

{
  if ((param_1 & 0x1f) != 0) {
    DAT_8032f1e0 = param_1 + (0x20 - (param_1 & 0x1f));
    return;
  }
  DAT_8032f1e0 = param_1;
  return;
}

