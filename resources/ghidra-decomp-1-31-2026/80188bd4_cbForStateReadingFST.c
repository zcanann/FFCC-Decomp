// Function: cbForStateReadingFST
// Entry: 80188bd4
// Size: 140 bytes

void cbForStateReadingFST(uint param_1)

{
  undefined *puVar1;
  code *pcVar2;
  
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_8032f080 + 0xc) = 0xffffffff;
    stateTimeout();
  }
  else if ((param_1 & 1) == 0) {
    stateGettingError();
  }
  else {
    DAT_8032f0b4 = 0;
    __DVDFSInit();
    puVar1 = DAT_8032f080;
    DAT_8032f080 = &DAT_8030ca60;
    *(undefined4 *)(puVar1 + 0xc) = 0;
    pcVar2 = *(code **)(puVar1 + 0x28);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(0);
    }
    stateReady();
  }
  return;
}

