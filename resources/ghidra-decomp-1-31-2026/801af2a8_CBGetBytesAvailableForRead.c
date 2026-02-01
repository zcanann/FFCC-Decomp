// Function: CBGetBytesAvailableForRead
// Entry: 801af2a8
// Size: 8 bytes

undefined4 CBGetBytesAvailableForRead(int param_1)

{
  return *(undefined4 *)(param_1 + 0x10);
}

