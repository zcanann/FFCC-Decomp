// Function: GetMiniGameParam__12CMiniGamePcsFi
// Entry: 800b9068
// Size: 96 bytes

int GetMiniGameParam__12CMiniGamePcsFi(int param_1,int param_2)

{
  if (param_2 == 0x2002) {
    return (int)*(char *)(param_1 + 0x649a);
  }
  if (param_2 < 0x2002) {
    if (param_2 == 0x2000) {
      return (int)*(char *)(param_1 + 0x6498);
    }
    if (0x1fff < param_2) {
      return (int)*(char *)(param_1 + 0x6499);
    }
  }
  else if (param_2 < 0x2004) {
    return (int)*(char *)(param_1 + 0x649b);
  }
  return 0;
}

