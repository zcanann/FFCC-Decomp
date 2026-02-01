// Function: GetSameCharaData__8CMenuPcsFPQ22Mc7SaveDatPQ22Mc7SaveDatii
// Entry: 800e9904
// Size: 424 bytes

uint GetSameCharaData__8CMenuPcsFPQ22Mc7SaveDatPQ22Mc7SaveDatii
               (CMenuPcs *menuPcs,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  
  if ((param_5 == 0) &&
     ((iVar1 = param_3 + param_4 * 0x9c0,
      *(int *)(param_2 + 0x13d4) != *(int *)(iVar1 + 0x1d9c) ||
      *(int *)(param_2 + 0x13d0) != *(int *)(iVar1 + 0x1d98) ||
      (*(int *)(param_2 + 0x13d8) != *(int *)(iVar1 + 0x1da0))))) {
    return 0xfffffffe;
  }
  uVar2 = 0;
  iVar1 = param_4 * 0x9c0 + 0x1d94;
  iVar4 = 4;
  do {
    if (*(int *)(param_2 + 0x1a84) != 0) {
      uVar3 = uVar2;
      if (param_5 == 0) {
        if ((*(char *)(param_2 + 0x1d90) != '\0') &&
           (*(int *)(param_2 + 0x1d94) == *(int *)(param_3 + iVar1))) break;
      }
      else if ((((*(char *)(param_2 + 0x1d91) != '\0') &&
                (*(int *)(param_2 + 0x1d94) == *(int *)(param_3 + iVar1))) &&
               (*(int *)(param_2 + 0x1d9c) == *(int *)(param_3 + 0x13d4) &&
                *(int *)(param_2 + 0x1d98) == *(int *)(param_3 + 0x13d0))) &&
              (*(int *)(param_2 + 0x1da0) == *(int *)(param_3 + 0x13d8))) break;
    }
    if (*(int *)(param_2 + 0x2444) != 0) {
      uVar3 = uVar2 + 1;
      if (param_5 == 0) {
        if ((*(char *)(param_2 + 0x2750) != '\0') &&
           (*(int *)(param_2 + 0x2754) == *(int *)(param_3 + iVar1))) break;
      }
      else if (((*(char *)(param_2 + 0x2751) != '\0') &&
               (*(int *)(param_2 + 0x2754) == *(int *)(param_3 + iVar1))) &&
              ((*(int *)(param_2 + 0x275c) == *(int *)(param_3 + 0x13d4) &&
                *(int *)(param_2 + 0x2758) == *(int *)(param_3 + 0x13d0) &&
               (*(int *)(param_2 + 0x2760) == *(int *)(param_3 + 0x13d8))))) break;
    }
    param_2 = param_2 + 0x1380;
    uVar2 = uVar2 + 2;
    iVar4 = iVar4 + -1;
    uVar3 = uVar2;
  } while (iVar4 != 0);
  if (param_5 != 0) {
    return 0xfffffffc - ((int)(((int)(uVar3 ^ 8) >> 1) - ((uVar3 ^ 8) & 8)) >> 0x1f);
  }
  if ((int)uVar3 < 8) {
    return uVar3;
  }
  return 0xffffffff;
}

