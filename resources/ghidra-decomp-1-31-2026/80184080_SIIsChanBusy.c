// Function: SIIsChanBusy
// Entry: 80184080
// Size: 60 bytes

undefined4 SIIsChanBusy(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 1;
  if ((FatalContext[param_1 * 8 + 0x2c7] == -1) && (DAT_80217304 != param_1)) {
    uVar1 = 0;
  }
  return uVar1;
}

