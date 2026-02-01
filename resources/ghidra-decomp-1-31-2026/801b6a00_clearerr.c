// Function: clearerr
// Entry: 801b6a00
// Size: 16 bytes

void clearerr(int param_1)

{
  *(undefined *)(param_1 + 9) = 0;
  *(undefined *)(param_1 + 10) = 0;
  return;
}

