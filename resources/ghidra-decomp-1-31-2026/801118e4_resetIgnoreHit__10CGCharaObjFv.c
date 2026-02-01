// Function: resetIgnoreHit__10CGCharaObjFv
// Entry: 801118e4
// Size: 56 bytes

void resetIgnoreHit__10CGCharaObjFv(int param_1)

{
  *(byte *)(param_1 + 0x640) = *(byte *)(param_1 + 0x640) & 0x7f;
  *(byte *)(param_1 + 0x648) = *(byte *)(param_1 + 0x648) & 0x7f;
  *(byte *)(param_1 + 0x650) = *(byte *)(param_1 + 0x650) & 0x7f;
  *(byte *)(param_1 + 0x658) = *(byte *)(param_1 + 0x658) & 0x7f;
  return;
}

