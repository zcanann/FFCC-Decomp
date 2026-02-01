// Function: ReverbSTDFree
// Entry: 801958dc
// Size: 252 bytes

void ReverbSTDFree(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 6; bVar1 = bVar1 + 1) {
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar2 + 0xc));
    iVar2 = iVar2 + 0x14;
  }
  iVar2 = param_1;
  for (bVar1 = 0; bVar1 < 6; bVar1 = bVar1 + 1) {
    (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(iVar2 + 0x84));
    iVar2 = iVar2 + 0x14;
  }
  if (*(int *)(param_1 + 0x120) != 0) {
    for (bVar1 = 0; bVar1 < 3; bVar1 = bVar1 + 1) {
      (*(code *)PTR___AXFXFreeFunction_8032eb64)(*(undefined4 *)(param_1 + 0x124));
      param_1 = param_1 + 4;
    }
  }
  return;
}

