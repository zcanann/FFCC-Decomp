// Function: GXGetTexObjHeight
// Entry: 801a4210
// Size: 16 bytes

int GXGetTexObjHeight(int param_1)

{
  return (*(uint *)(param_1 + 8) >> 10 & 0x3ff) + 1;
}

