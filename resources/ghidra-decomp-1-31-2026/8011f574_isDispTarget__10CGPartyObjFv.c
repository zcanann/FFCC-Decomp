// Function: isDispTarget__10CGPartyObjFv
// Entry: 8011f574
// Size: 48 bytes

undefined4 isDispTarget__10CGPartyObjFv(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (((*(int *)(param_1 + 0x520) == 2) || (*(int *)(param_1 + 0x520) == 6)) &&
     (*(int *)(param_1 + 0x668) != 0)) {
    uVar1 = 1;
  }
  return uVar1;
}

