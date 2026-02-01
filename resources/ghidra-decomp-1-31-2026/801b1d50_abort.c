// Function: abort
// Entry: 801b1d50
// Size: 156 bytes

void abort(void)

{
  raise(1);
  DAT_8032f378 = 1;
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

