// Function: IsUse__8CMesMenuFv
// Entry: 800b9484
// Size: 88 bytes

undefined4 IsUse__8CMesMenuFv(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if (((*(int *)(param_1 + 8) != 0) && (*(int *)(param_1 + 0xc) < 2)) &&
     (iVar1 = GetWait__4CMesFv(param_1 + 0x1c), iVar1 != 4)) {
    uVar2 = 1;
  }
  return uVar2;
}

