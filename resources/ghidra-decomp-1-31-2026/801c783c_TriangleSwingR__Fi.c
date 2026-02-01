// Function: TriangleSwingR__Fi
// Entry: 801c783c
// Size: 96 bytes

ulonglong TriangleSwingR__Fi(uint param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = (param_1 ^ 0x200) >> 8 & 3;
  uVar1 = (param_1 ^ 0x200) & 0xff;
  iVar3 = uVar1 * 0x100;
  if (uVar2 == 2) {
    iVar3 = uVar1 * -0x100;
  }
  else if (uVar2 < 2) {
    if (uVar2 != 0) {
      iVar3 = uVar1 * -0x100 + 0x10000;
    }
  }
  else if (uVar2 < 4) {
    iVar3 = iVar3 + -0x10000;
  }
  return CONCAT44(iVar3,param_1) & 0xffffffff000000ff;
}

