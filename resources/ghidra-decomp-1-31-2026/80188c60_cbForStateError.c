// Function: cbForStateError
// Entry: 80188c60
// Size: 172 bytes

void cbForStateError(int param_1)

{
  undefined *puVar1;
  
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    stateTimeout();
  }
  else {
    __DVDPrintFatalMessage();
    puVar1 = DAT_8032f080;
    DAT_8032f080 = &DAT_8030ca60;
    DAT_8032f098 = 1;
    if (*(code **)(puVar1 + 0x28) != (code *)0x0) {
      (**(code **)(puVar1 + 0x28))(0xffffffff,puVar1);
    }
    if (DAT_8032f0a0 != 0) {
      DAT_8032f0a0 = 0;
      if (DAT_8032f0a4 != (code *)0x0) {
        (*DAT_8032f0a4)(0,puVar1);
      }
    }
    stateReady();
  }
  return;
}

