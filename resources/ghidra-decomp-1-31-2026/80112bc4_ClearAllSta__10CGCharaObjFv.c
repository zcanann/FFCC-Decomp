// Function: ClearAllSta__10CGCharaObjFv
// Entry: 80112bc4
// Size: 92 bytes

void ClearAllSta__10CGCharaObjFv(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    setSta__10CGCharaObjFii(param_1,iVar1,0);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 0x27);
  *(uint *)(param_1 + 0x60) = *(uint *)(param_1 + 0x60) | 2;
  return;
}

