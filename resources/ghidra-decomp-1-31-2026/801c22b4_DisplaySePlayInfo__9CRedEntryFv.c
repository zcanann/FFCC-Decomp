// Function: DisplaySePlayInfo__9CRedEntryFv
// Entry: 801c22b4
// Size: 612 bytes

void DisplaySePlayInfo__9CRedEntryFv(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  int iVar5;
  int *piVar6;
  
  if (DAT_8032f408 != 0) {
    OSReport(&DAT_80333d4d);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_____SE_Play_Information______801e7b71,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_Track___Name___Wave_801e7b92,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    piVar6 = *(int **)(DAT_8032f3f0 + 0xdbc);
    piVar4 = (int *)(DAT_8032f3f0 + 0xdbc);
    do {
      if (*piVar6 == 0) {
        iVar1 = ((int)piVar6 - *piVar4) / 0x154 + ((int)piVar6 - *piVar4 >> 0x1f);
        OSReport(s__s__2d_____801e7c01,&DAT_801e7905,(iVar1 - (iVar1 >> 0x1f)) + 0x20);
        fflush(&DAT_8021d1a8);
      }
      else if ((piVar6[0x3d] & 0x80000000U) == 0) {
        iVar2 = SearchSeSepBank__9CRedEntryFi(param_1,piVar6[0x3d]);
        iVar1 = ((int)piVar6 - *piVar4) / 0x154 + ((int)piVar6 - *piVar4 >> 0x1f);
        OSReport(s__s__2d___se_6_6u_sep___WAVE_4_4u_801e7bdc,&DAT_801e7905,
                 (iVar1 - (iVar1 >> 0x1f)) + 0x20,piVar6[0x3d],
                 CONCAT11(*(undefined *)(*(int *)(iVar2 + 8) + 0x12),
                          *(undefined *)(*(int *)(iVar2 + 8) + 0x11)));
        fflush(&DAT_8021d1a8);
      }
      else {
        uVar3 = piVar6[0x3d];
        iVar2 = (int)(uVar3 & 0x7fffffff) >> 9;
        iVar5 = (&DAT_8032e12c)[iVar2] + 0x10;
        iVar1 = ((int)piVar6 - *piVar4) / 0x154 + ((int)piVar6 - *piVar4 >> 0x1f);
        iVar5 = iVar5 + *(short *)((&DAT_8032e12c)[iVar2] + 10) * 4 +
                (*(uint *)(iVar5 + (uVar3 & 0x1ff) * 4) & 0x7fffffff);
        OSReport(s__s__2d____3_3u__3_3u___WAVE_4_4u_801e7bb2,&DAT_801e7905,
                 (iVar1 - (iVar1 >> 0x1f)) + 0x20,iVar2,uVar3 & 0x1ff,
                 CONCAT11(*(undefined *)(iVar5 + 2),*(undefined *)(iVar5 + 1)));
        fflush(&DAT_8021d1a8);
      }
      piVar6 = piVar6 + 0x55;
    } while (piVar6 < (int *)(*piVar4 + 0x2a80));
    OSReport(&DAT_80333d4f,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    OSReport(&DAT_80333d4d);
    fflush(&DAT_8021d1a8);
  }
  return;
}

