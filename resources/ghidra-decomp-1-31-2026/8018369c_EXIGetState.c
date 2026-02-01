// Function: EXIGetState
// Entry: 8018369c
// Size: 24 bytes

undefined4 EXIGetState(int param_1)

{
  return FatalContext[param_1 * 0x10 + 0x29a];
}

