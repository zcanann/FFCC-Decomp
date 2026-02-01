// Function: commandFinished__10CGPartyObjFv
// Entry: 8011e0d8
// Size: 20 bytes

void commandFinished__10CGPartyObjFv(int param_1)

{
  *(byte *)(param_1 + 0x6b8) = *(byte *)(param_1 + 0x6b8) & 0x7f;
  return;
}

