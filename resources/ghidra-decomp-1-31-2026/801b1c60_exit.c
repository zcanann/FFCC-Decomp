// Function: exit
// Entry: 801b1c60
// Size: 240 bytes

void exit(void)

{
  undefined **ppuVar1;
  
  if (DAT_8032f378 == 0) {
    __begin_critical_region(0);
    __end_critical_region(0);
    __destroy_global_chain();
    for (ppuVar1 = &PTR___destroy_global_chain_801d5460; (code *)*ppuVar1 != (code *)0x0;
        ppuVar1 = ppuVar1 + 1) {
      (*(code *)*ppuVar1)();
    }
    if (DAT_8032f380 != (code *)0x0) {
      (*DAT_8032f380)();
      DAT_8032f380 = (code *)0x0;
    }
  }
  __begin_critical_region(0);
  while (0 < DAT_8032f37c) {
    DAT_8032f37c = DAT_8032f37c + -1;
    (**(code **)(&DAT_8032b410 + DAT_8032f37c * 4))();
  }
  __end_critical_region(0);
  __kill_critical_regions();
  if (DAT_8032f384 != (code *)0x0) {
    (*DAT_8032f384)();
    DAT_8032f384 = (code *)0x0;
  }
  _ExitProcess();
  return;
}

