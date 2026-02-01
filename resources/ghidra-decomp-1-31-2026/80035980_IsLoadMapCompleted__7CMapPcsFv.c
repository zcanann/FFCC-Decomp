// Function: IsLoadMapCompleted__7CMapPcsFv
// Entry: 80035980
// Size: 260 bytes

ulonglong IsLoadMapCompleted__7CMapPcsFv(void)

{
  uint uVar1;
  CMapMng *pCVar2;
  int iVar3;
  
  pCVar2 = &MapMng;
  uVar1 = 0;
  iVar3 = 2;
  while( true ) {
    if (*(int *)&pCVar2->field_0x22a2c != 0) {
      return (ulonglong)uVar1;
    }
    if (*(int *)&pCVar2->field_0x22a30 != 0) {
      return (ulonglong)uVar1;
    }
    if (*(int *)&pCVar2->field_0x22a34 != 0) {
      return (ulonglong)uVar1;
    }
    if (*(int *)&pCVar2->field_0x22a38 != 0) {
      return (ulonglong)uVar1;
    }
    if (*(int *)&pCVar2->field_0x22a3c != 0) {
      return (ulonglong)uVar1;
    }
    if (*(int *)&pCVar2->field_0x22a40 != 0) {
      return (ulonglong)uVar1;
    }
    if (*(int *)&pCVar2->field_0x22a44 != 0) {
      return (ulonglong)uVar1;
    }
    if (*(int *)&pCVar2->field_0x22a48 != 0) break;
    pCVar2 = (CMapMng *)&pCVar2->octTreeArr[0].field_0xc;
    uVar1 = uVar1 + 7;
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      return CONCAT44(1,uVar1);
    }
  }
  return (ulonglong)uVar1;
}

