// Function: GXInitTexObjCI
// Entry: 801a4010
// Size: 72 bytes

void GXInitTexObjCI(int param_1)

{
  undefined4 param_9;
  
  GXInitTexObj();
  *(byte *)(param_1 + 0x1f) = *(byte *)(param_1 + 0x1f) & 0xfd;
  *(undefined4 *)(param_1 + 0x18) = param_9;
  return;
}

