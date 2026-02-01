// Function: Ptr2Off__8CMapMeshFv
// Entry: 800285dc
// Size: 108 bytes

void Ptr2Off__8CMapMeshFv(int param_1)

{
  if (*(int *)(param_1 + 0x24) == 0) {
    return;
  }
  *(int *)(param_1 + 0x2c) = *(int *)(param_1 + 0x2c) - *(int *)(param_1 + 0x24);
  *(int *)(param_1 + 0x30) = *(int *)(param_1 + 0x30) - *(int *)(param_1 + 0x24);
  *(int *)(param_1 + 0x34) = *(int *)(param_1 + 0x34) - *(int *)(param_1 + 0x24);
  *(int *)(param_1 + 0x38) = *(int *)(param_1 + 0x38) - *(int *)(param_1 + 0x24);
  *(int *)(param_1 + 0x3c) = *(int *)(param_1 + 0x3c) - *(int *)(param_1 + 0x24);
  *(int *)(param_1 + 0x40) = *(int *)(param_1 + 0x40) - *(int *)(param_1 + 0x24);
  return;
}

