// Function: DisplayMMemoryInfo__9CRedEntryFv
// Entry: 801c2b70
// Size: 1108 bytes

void DisplayMMemoryInfo__9CRedEntryFv(uint *param_1)

{
  bool bVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int *piVar11;
  
  if (DAT_8032f408 != 0) {
    OSReport(&DAT_80333d4d);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_____MMemory_Information______801e7cce,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_Name___Start___Size___Free_801e7cef,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    iVar8 = 0;
    iVar7 = 0;
    iVar6 = 0;
    iVar2 = GetMainBufferAddress__10CRedMemoryFv(&DAT_8032f480);
    piVar3 = (int *)GetMainBankAddress__10CRedMemoryFv(&DAT_8032f480);
    iVar4 = GetMainBufferSize__10CRedMemoryFv(&DAT_8032f480);
    iVar4 = iVar2 + iVar4;
    piVar11 = piVar3;
    do {
      if (piVar11[1] != 0) {
        bVar1 = false;
        if (piVar11[3] < 1) {
          iVar5 = iVar4 - (*piVar11 + piVar11[1]);
        }
        else {
          iVar5 = piVar11[2] - (*piVar11 + piVar11[1]);
        }
        uVar10 = param_1[2];
        do {
          if ((*(int *)(uVar10 + 0xc) != 0) && (*(int *)(uVar10 + 8) == *piVar11)) {
            OSReport(s__s_MUSIC_3_3d___0x_8_8X___0x_8_8_801e7d24,&DAT_801e7905,
                     (int)*(short *)(*piVar11 + 4),*piVar11,piVar11[1],iVar5);
            fflush(&DAT_8021d1a8);
            bVar1 = true;
            break;
          }
          uVar10 = uVar10 + 0x10;
        } while (uVar10 < param_1[2] + 0x40);
        if (!bVar1) {
          iVar9 = 0;
          do {
            if (((&DAT_8032e12c)[iVar9] != 0) && (*piVar11 == (&DAT_8032e12c)[iVar9])) {
              OSReport(s__s_SE_BLOCK___0x_8_8X___0x_8_8X___801e7d51,&DAT_801e7905,*piVar11,
                       piVar11[1],iVar5);
              fflush(&DAT_8021d1a8);
              bVar1 = true;
              break;
            }
            iVar9 = iVar9 + 1;
          } while (iVar9 < 4);
        }
        if (!bVar1) {
          uVar10 = *param_1;
          do {
            if ((*(int *)(uVar10 + 0xc) != 0) && (*(int *)(uVar10 + 8) == *piVar11)) {
              OSReport(s__s_WAVE_4_4d___0x_8_8X___0x_8_8X_801e7d7c,&DAT_801e7905,
                       (int)*(short *)(*piVar11 + 2),*piVar11,piVar11[1],iVar5);
              fflush(&DAT_8021d1a8);
              bVar1 = true;
              break;
            }
            uVar10 = uVar10 + 0x10;
          } while (uVar10 < *param_1 + 0x400);
        }
        if (!bVar1) {
          uVar10 = param_1[1];
          do {
            if ((*(int *)(uVar10 + 0xc) != 0) && (*(int *)(uVar10 + 8) == *piVar11)) {
              OSReport(s__s_SE_6_6d___0x_8_8X___0x_8_8X___801e7da8,&DAT_801e7905,
                       *(undefined4 *)(*piVar11 + 8),*piVar11,piVar11[1],iVar5);
              fflush(&DAT_8021d1a8);
              bVar1 = true;
              break;
            }
            uVar10 = uVar10 + 0x10;
          } while (uVar10 < param_1[1] + 0x1000);
        }
        if (!bVar1) {
          OSReport(s__s____________0x_8_8X___0x_8_8X___801e7dd2,&DAT_801e7905,*piVar11,piVar11[1],
                   iVar5);
          fflush(&DAT_8021d1a8);
        }
        if (iVar8 < *piVar11 - iVar2) {
          iVar8 = *piVar11 - iVar2;
        }
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + piVar11[1];
        iVar2 = *piVar11 + piVar11[1];
      }
      piVar11 = piVar11 + 2;
    } while (piVar11 < piVar3 + 0x800);
    iVar4 = GetMainBufferSize__10CRedMemoryFv(&DAT_8032f480);
    iVar5 = GetMainBufferAddress__10CRedMemoryFv(&DAT_8032f480);
    iVar2 = (iVar5 + iVar4) - iVar2;
    if (iVar8 < iVar2) {
      iVar8 = iVar2;
    }
    OSReport(&DAT_80333d4f,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_Entry_Items____d_801e7dfd,&DAT_801e7905,iVar6);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_Total_Size___0x_8_8X_801e7b18,&DAT_801e7905,iVar7);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_Max_Free_Size___0x_8_8X_801e7b34,&DAT_801e7905,iVar8);
    fflush(&DAT_8021d1a8);
    OSReport(&DAT_80333d4f,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    OSReport(&DAT_80333d4d);
    fflush(&DAT_8021d1a8);
  }
  return;
}

