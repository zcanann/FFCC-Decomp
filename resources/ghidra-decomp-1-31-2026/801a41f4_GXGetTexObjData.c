// Function: GXGetTexObjData
// Entry: 801a41f4
// Size: 12 bytes

int GXGetTexObjData(int param_1)

{
  return (*(uint *)(param_1 + 0xc) & 0x1fffff) << 5;
}

