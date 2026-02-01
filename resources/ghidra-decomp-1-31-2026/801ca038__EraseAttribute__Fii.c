// Function: _EraseAttribute__Fii
// Entry: 801ca038
// Size: 364 bytes

void _EraseAttribute__Fii(int param_1,byte param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  
  piVar5 = *(int **)(DAT_8032f3f0 + 0xdbc);
  piVar3 = (int *)(DAT_8032f3f0 + 0xdbc);
  do {
    if (*piVar5 != 0) {
      if (((int)(uint)*(byte *)((int)piVar5 + 0x14f) <= param_1) &&
         ((*(byte *)(piVar5 + 0x54) & param_2) != 0)) {
        KeyOnReserveClear__FP12RedKeyOnDATAP12RedTrackDATA(DAT_8032f3fc,piVar5);
        piVar5[0x3e] = 0;
        piVar5[0x41] = 0;
        *piVar5 = 0;
        piVar5[0x16] = 0;
        iVar4 = (int)*(char *)((int)piVar5 + 0x14e);
        iVar1 = iVar4 * 0xc0 + 0x1a;
        *(byte *)(DAT_8032f444 + iVar1) = *(byte *)(DAT_8032f444 + iVar1) & 0xfa;
        iVar1 = iVar4 * 0xc0 + 0x94;
        iVar2 = iVar4 * 0xc0 + 0x90;
        *(uint *)(DAT_8032f444 + iVar1) = *(uint *)(DAT_8032f444 + iVar1) & 0xfffffff7;
        iVar1 = iVar4 * 0xc0 + 0x90;
        *(uint *)(DAT_8032f444 + iVar2) = *(uint *)(DAT_8032f444 + iVar2) & 0xfffffffe;
        *(uint *)(DAT_8032f444 + iVar1) = *(uint *)(DAT_8032f444 + iVar1) | 2;
        *(undefined4 *)(DAT_8032f444 + iVar4 * 0xc0 + 0x8c) = 0;
        SeSepHistoryManager__9CRedEntryFii(&DAT_8032e154,0,piVar5[0x3d]);
        if (piVar5[6] != 0) {
          WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,0,(int)*(short *)(piVar5[6] + 2));
        }
      }
    }
    piVar5 = piVar5 + 0x55;
  } while (piVar5 < (int *)(*piVar3 + 0x2a80));
  return;
}

