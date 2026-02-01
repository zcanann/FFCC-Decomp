// Function: MIXReleaseChannel
// Entry: 80197958
// Size: 32 bytes

void MIXReleaseChannel(int param_1)

{
  *(undefined4 *)(&DAT_80325d40 + *(int *)(param_1 + 0x18) * 0x60) = 0;
  return;
}

