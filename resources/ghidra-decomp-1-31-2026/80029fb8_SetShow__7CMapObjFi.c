// Function: SetShow__7CMapObjFi
// Entry: 80029fb8
// Size: 80 bytes

void SetShow__7CMapObjFi(int param_1,int param_2)

{
  if (param_2 == 0) {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) & 0xfe;
  }
  else {
    *(byte *)(param_1 + 0x18) = *(byte *)(param_1 + 0x18) | 1;
  }
  if (*(int *)(param_1 + 4) != 0) {
    SetShow_r__7CMapObjFi();
  }
  return;
}

