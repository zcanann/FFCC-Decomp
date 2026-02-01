// Function: OSIsThreadTerminated
// Entry: 80180b6c
// Size: 52 bytes

undefined4 OSIsThreadTerminated(int param_1)

{
  bool bVar1;
  
  bVar1 = true;
  if ((*(short *)(param_1 + 0x2c8) != 8) && (*(short *)(param_1 + 0x2c8) != 0)) {
    bVar1 = false;
  }
  if (bVar1) {
    return 1;
  }
  return 0;
}

