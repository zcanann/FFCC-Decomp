// Function: SeStopMG__Fiiii
// Entry: 801ca638
// Size: 464 bytes

undefined4 SeStopMG__Fiiii(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  
  iVar1 = DAT_8032f3f0;
  piVar4 = (int *)(DAT_8032f3f0 + 0xdbc);
  *(undefined4 *)(DAT_8032f3f0 + 0x1244) = 0;
  piVar5 = *(int **)(iVar1 + 0xdbc);
  do {
    if ((*piVar5 != 0) && ((piVar5[0x3d] & 0x80000000U) == 0)) {
      iVar1 = piVar5[0x3d] / 1000 + (piVar5[0x3d] >> 0x1f);
      iVar1 = iVar1 - (iVar1 >> 0x1f);
      if ((param_1 != iVar1) && (((param_2 != iVar1 && (param_3 != iVar1)) && (param_4 != iVar1))))
      {
        KeyOnReserveClear__FP12RedKeyOnDATAP12RedTrackDATA(DAT_8032f3fc,piVar5);
        piVar5[0x3e] = 0;
        piVar5[0x41] = 0;
        *piVar5 = 0;
        piVar5[0x16] = 0;
        iVar3 = (int)*(char *)((int)piVar5 + 0x14e);
        iVar1 = iVar3 * 0xc0 + 0x1a;
        *(byte *)(DAT_8032f444 + iVar1) = *(byte *)(DAT_8032f444 + iVar1) & 0xfa;
        iVar1 = iVar3 * 0xc0 + 0x94;
        iVar2 = iVar3 * 0xc0 + 0x90;
        *(uint *)(DAT_8032f444 + iVar1) = *(uint *)(DAT_8032f444 + iVar1) & 0xfffffff7;
        iVar1 = iVar3 * 0xc0 + 0x90;
        *(uint *)(DAT_8032f444 + iVar2) = *(uint *)(DAT_8032f444 + iVar2) & 0xfffffffe;
        *(uint *)(DAT_8032f444 + iVar1) = *(uint *)(DAT_8032f444 + iVar1) | 2;
        *(undefined4 *)(DAT_8032f444 + iVar3 * 0xc0) = 0;
        *(undefined4 *)(DAT_8032f444 + iVar3 * 0xc0 + 0x8c) = 0;
        if (piVar5[6] != 0) {
          WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,0,(int)*(short *)(piVar5[6] + 2));
        }
        SeSepHistoryManager__9CRedEntryFii(&DAT_8032e154,0,piVar5[0x3d]);
      }
    }
    piVar5 = piVar5 + 0x55;
  } while (piVar5 < (int *)(*piVar4 + 0x2a80));
  return 0;
}

