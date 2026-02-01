// Function: GXGetTexObjWidth
// Entry: 801a4200
// Size: 16 bytes

int GXGetTexObjWidth(int param_1)

{
  return (*(uint *)(param_1 + 8) & 0x3ff) + 1;
}

