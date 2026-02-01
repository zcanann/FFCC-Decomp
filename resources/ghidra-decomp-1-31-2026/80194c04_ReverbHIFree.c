// Function: ReverbHIFree
// Entry: 80194c04
// Size: 252 bytes

void ReverbHIFree(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 9; bVar1 = bVar1 + 1) {
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar2 + 0xc));
    iVar2 = iVar2 + 0x14;
  }
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 9; bVar1 = bVar1 + 1) {
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar2 + 0xc0));
    iVar2 = iVar2 + 0x14;
  }
  if (*(int *)(param_1 + 0x1a4) != 0) {
    for (bVar1 = 0; bVar1 < 3; bVar1 = bVar1 + 1) {
      (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x1ac));
      param_1 = param_1 + 4;
    }
  }
  return;
}

