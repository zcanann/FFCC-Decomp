// Function: IncNumTevStage__12CMaterialManFv
// Entry: 80041f8c
// Size: 24 bytes

void IncNumTevStage__12CMaterialManFv(int param_1)

{
  *(uint *)(param_1 + 0x60) = (*(uint *)(param_1 + 0x60) & 0xff) + 1 & 0xff;
  return;
}

