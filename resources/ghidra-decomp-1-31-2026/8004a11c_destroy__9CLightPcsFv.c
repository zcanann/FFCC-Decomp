// Function: destroy__9CLightPcsFv
// Entry: 8004a11c
// Size: 200 bytes

void destroy__9CLightPcsFv(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  iVar2 = param_1;
  do {
    bVar1 = *(int *)(iVar2 + 0x26b0) != 0;
    if (bVar1) {
      if (bVar1) {
        Free__7CMemoryFPv(&Memory);
        *(undefined4 *)(iVar2 + 0x26b0) = 0;
      }
      *(undefined *)(iVar2 + 0x26ac) = 0;
      *(undefined *)(iVar2 + 0x26ad) = 0;
    }
    uVar3 = uVar3 + 1;
    iVar2 = iVar2 + 0x138;
  } while (uVar3 < 8);
  uVar3 = 0;
  do {
    bVar1 = *(int *)(param_1 + 0x1cf0) != 0;
    if (bVar1) {
      if (bVar1) {
        Free__7CMemoryFPv(&Memory);
        *(undefined4 *)(param_1 + 0x1cf0) = 0;
      }
      *(undefined *)(param_1 + 0x1cec) = 0;
      *(undefined *)(param_1 + 0x1ced) = 0;
    }
    uVar3 = uVar3 + 1;
    param_1 = param_1 + 0x138;
  } while (uVar3 < 8);
  return;
}

