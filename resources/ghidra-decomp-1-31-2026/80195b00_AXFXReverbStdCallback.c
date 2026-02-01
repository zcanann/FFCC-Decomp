// Function: AXFXReverbStdCallback
// Entry: 80195b00
// Size: 48 bytes

void AXFXReverbStdCallback(undefined4 *param_1,int param_2)

{
  if (*(char *)(param_2 + 0x13c) == '\0') {
    HandleReverb(*param_1);
  }
  return;
}

