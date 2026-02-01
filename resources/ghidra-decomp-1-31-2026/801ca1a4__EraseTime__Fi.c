// Function: _EraseTime__Fi
// Entry: 801ca1a4
// Size: 536 bytes

int _EraseTime__Fi(uint param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  int *piVar8;
  int *piVar9;
  
  uVar6 = 0x100;
  piVar9 = *(int **)(DAT_8032f3f0 + 0xdbc);
  piVar8 = (int *)(DAT_8032f3f0 + 0xdbc);
  do {
    if (((*piVar9 != 0) && (*(char *)(piVar9 + 0x54) == '\0')) &&
       (*(byte *)((int)piVar9 + 0x14f) < uVar6)) {
      uVar6 = (uint)*(byte *)((int)piVar9 + 0x14f);
    }
    piVar9 = piVar9 + 0x55;
  } while (piVar9 < (int *)(*piVar8 + 0x2a80));
  if ((int)uVar6 < (int)param_1) {
    param_1 = uVar6;
  }
  piVar9 = (int *)*piVar8;
  iVar7 = 0;
  iVar3 = 0;
  do {
    if (((*piVar9 != 0) && (*(char *)(piVar9 + 0x54) == '\0')) &&
       (((int)(uint)*(byte *)((int)piVar9 + 0x14f) <= (int)param_1 && (iVar7 < piVar9[0x43])))) {
      iVar7 = piVar9[0x43];
      iVar3 = piVar9[0x3d];
    }
    piVar9 = piVar9 + 0x55;
  } while (piVar9 < (int *)(*piVar8 + 0x2a80));
  piVar9 = (int *)*piVar8;
  iVar4 = 0;
  do {
    if (((*piVar9 != 0) && (*(char *)(piVar9 + 0x54) == '\0')) &&
       (((int)(uint)*(byte *)((int)piVar9 + 0x14f) <= (int)param_1 && (piVar9[0x43] == iVar7)))) {
      KeyOnReserveClear__FP12RedKeyOnDATAP12RedTrackDATA(DAT_8032f3fc,piVar9);
      piVar9[0x3e] = 0;
      piVar9[0x41] = 0;
      *piVar9 = 0;
      piVar9[0x16] = 0;
      iVar5 = (int)*(char *)((int)piVar9 + 0x14e);
      iVar1 = iVar5 * 0xc0 + 0x1a;
      *(byte *)(DAT_8032f444 + iVar1) = *(byte *)(DAT_8032f444 + iVar1) & 0xfa;
      iVar1 = iVar5 * 0xc0 + 0x94;
      iVar2 = iVar5 * 0xc0 + 0x90;
      *(uint *)(DAT_8032f444 + iVar1) = *(uint *)(DAT_8032f444 + iVar1) & 0xfffffff7;
      iVar1 = iVar5 * 0xc0 + 0x90;
      *(uint *)(DAT_8032f444 + iVar2) = *(uint *)(DAT_8032f444 + iVar2) & 0xfffffffe;
      *(uint *)(DAT_8032f444 + iVar1) = *(uint *)(DAT_8032f444 + iVar1) | 2;
      *(undefined4 *)(DAT_8032f444 + iVar5 * 0xc0 + 0x8c) = 0;
      if (piVar9[6] != 0) {
        WaveHistoryManager__9CRedEntryFii(&DAT_8032e154,0,(int)*(short *)(piVar9[6] + 2));
      }
      iVar4 = iVar4 + 1;
    }
    piVar9 = piVar9 + 0x55;
  } while (piVar9 < (int *)(*piVar8 + 0x2a80));
  if (iVar4 != 0) {
    SeSepHistoryManager__9CRedEntryFii(&DAT_8032e154,0,iVar3);
  }
  return iVar4;
}

