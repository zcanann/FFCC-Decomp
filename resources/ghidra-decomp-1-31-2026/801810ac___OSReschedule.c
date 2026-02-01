// Function: __OSReschedule
// Entry: 801810ac
// Size: 48 bytes

void __OSReschedule(void)

{
  if (DAT_8032efd4 != 0) {
    SelectThread(0);
  }
  return;
}

