// Function: SeSepHistoryManager__9CRedEntryFii
// Entry: 801c2174
// Size: 320 bytes

void SeSepHistoryManager__9CRedEntryFii(int param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  
  if (param_2 == 0) {
    bVar1 = false;
    piVar3 = *(int **)(DAT_8032f3f0 + 0xdbc);
    do {
      if ((*piVar3 != 0) && (piVar3[0x3d] == param_3)) {
        bVar1 = true;
        break;
      }
      piVar3 = piVar3 + 0x55;
    } while (piVar3 < (int *)(*(int *)(DAT_8032f3f0 + 0xdbc) + 0x2a80));
    if (((!bVar1) && (iVar2 = SearchSeSepSequence__9CRedEntryFi(param_1,param_3), -1 < iVar2)) &&
       (*(int *)(*(int *)(param_1 + 4) + iVar2 * 0x10 + 4) == 0)) {
      SeSepHistoryAdd__9CRedEntryFv(param_1);
      *(undefined4 *)(*(int *)(param_1 + 4) + iVar2 * 0x10 + 4) = 1;
    }
  }
  else {
    iVar2 = SearchSeSepSequence__9CRedEntryFi(param_1,param_3);
    if (*(int *)(*(int *)(param_1 + 4) + iVar2 * 0x10 + 4) != 0) {
      SeSepHistoryDelete__9CRedEntryFi
                (param_1,*(undefined4 *)(*(int *)(param_1 + 4) + iVar2 * 0x10 + 4));
      *(undefined4 *)(*(int *)(param_1 + 4) + iVar2 * 0x10 + 4) = 0;
    }
  }
  return;
}

