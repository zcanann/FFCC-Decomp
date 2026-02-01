// Function: SeStopID__Fi
// Entry: 801ca4b8
// Size: 384 bytes

undefined4 SeStopID__Fi(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  
  iVar1 = DAT_8032f3f0;
  *(undefined4 *)(DAT_8032f3f0 + 0x1244) = 0;
  piVar5 = *(int **)(iVar1 + 0xdbc);
  do {
    if ((*piVar5 != 0) && ((param_1 == -1 || (piVar5[0x3e] == param_1)))) {
      KeyOnReserveClear__FP12RedKeyOnDATAP12RedTrackDATA(DAT_8032f3fc,piVar5);
      piVar5[0x3e] = 0;
      piVar5[0x41] = 0;
      *piVar5 = 0;
      piVar5[0x16] = 0;
      iVar4 = (int)*(char *)((int)piVar5 + 0x14e);
      iVar2 = iVar4 * 0xc0 + 0x1a;
      *(byte *)(DAT_8032f444 + iVar2) = *(byte *)(DAT_8032f444 + iVar2) & 0xfa;
      iVar2 = iVar4 * 0xc0 + 0x94;
      iVar3 = iVar4 * 0xc0 + 0x90;
      *(uint *)(DAT_8032f444 + iVar2) = *(uint *)(DAT_8032f444 + iVar2) & 0xfffffff7;
      iVar2 = iVar4 * 0xc0 + 0x90;
      *(uint *)(DAT_8032f444 + iVar3) = *(uint *)(DAT_8032f444 + iVar3) & 0xfffffffe;
      *(uint *)(DAT_8032f444 + iVar2) = *(uint *)(DAT_8032f444 + iVar2) | 2;
      *(undefined4 *)(DAT_8032f444 + iVar4 * 0xc0) = 0;
      *(undefined4 *)(DAT_8032f444 + iVar4 * 0xc0 + 0x8c) = 0;
      if (piVar5[6] != 0) {
        WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,0,(int)*(short *)(piVar5[6] + 2));
      }
      SeSepHistoryManager__9CRedEntryFii(&DAT_8032e154,0,piVar5[0x3d]);
    }
    piVar5 = piVar5 + 0x55;
  } while (piVar5 < (int *)(*(int *)(iVar1 + 0xdbc) + 0x2a80));
  return 0;
}

