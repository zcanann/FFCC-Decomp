// Function: WaveHistoryManager__9CRedEntryFii
// Entry: 801c1594
// Size: 408 bytes

void WaveHistoryManager__9CRedEntryFii(int *param_1,int param_2,int param_3)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  
  if (param_2 == 0) {
    bVar1 = false;
    if ((*(short *)(DAT_8032f3f0 + 0x48e) != 0) && (*(int *)(DAT_8032f3f0 + 0x47c) == param_3)) {
      bVar1 = true;
    }
    if ((*(short *)(DAT_8032f3f0 + 0x922) != 0) && (*(int *)(DAT_8032f3f0 + 0x910) == param_3)) {
      bVar1 = true;
    }
    if (!bVar1) {
      piVar3 = *(int **)(DAT_8032f3f0 + 0xdbc);
      do {
        if (((*piVar3 != 0) && (piVar3[6] != 0)) && (*(short *)(piVar3[6] + 2) == param_3)) {
          bVar1 = true;
          break;
        }
        piVar3 = piVar3 + 0x55;
      } while (piVar3 < (int *)(*(int *)(DAT_8032f3f0 + 0xdbc) + 0x2a80));
    }
    if (((!bVar1) && (iVar2 = SearchWaveSequence__9CRedEntryFi(param_1,param_3), 0xf < iVar2)) &&
       (*(int *)(*param_1 + iVar2 * 0x10 + 4) == 0)) {
      WaveHistoryAdd__9CRedEntryFi(param_1,0x14);
      *(undefined4 *)(*param_1 + iVar2 * 0x10 + 4) = 0x14;
    }
  }
  else {
    iVar2 = SearchWaveSequence__9CRedEntryFi(param_1,param_3);
    if ((0xf < iVar2) && (*(int *)(*param_1 + iVar2 * 0x10 + 4) != 0)) {
      WaveHistoryDelete__9CRedEntryFi(param_1,*(undefined4 *)(*param_1 + iVar2 * 0x10 + 4));
      *(undefined4 *)(*param_1 + iVar2 * 0x10 + 4) = 0;
    }
  }
  return;
}

