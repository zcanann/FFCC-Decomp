// Function: OnReset
// Entry: 80199898
// Size: 80 bytes

undefined4 OnReset(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((param_1 == 0) &&
     ((iVar1 = CARDUnmount(0), iVar1 == -1 || (iVar1 = CARDUnmount(1), iVar1 == -1)))) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

