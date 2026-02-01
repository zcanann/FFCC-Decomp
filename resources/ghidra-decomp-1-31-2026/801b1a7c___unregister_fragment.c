// Function: __unregister_fragment
// Entry: 801b1a7c
// Size: 52 bytes

void __unregister_fragment(int param_1)

{
  if (param_1 < 0) {
    return;
  }
  if (0 < param_1) {
    return;
  }
  (&DAT_8032b400)[param_1 * 3] = 0;
  (&DAT_8032b404)[param_1 * 3] = 0;
  (&DAT_8032b408)[param_1 * 3] = 0;
  return;
}

