// Function: DisplayWaveInfo__9CRedEntryFv
// Entry: 801c172c
// Size: 864 bytes

void DisplayWaveInfo__9CRedEntryFv(uint *param_1)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int *piVar10;
  
  if (DAT_8032f408 != 0) {
    OSReport(&DAT_80333d4d);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_____AMemory_Information______801e79ed,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_Bank___Name___Start___Size___F_801e7a0e,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    iVar8 = 0;
    iVar7 = 0;
    iVar6 = 0;
    iVar2 = GetABufferAddress__10CRedMemoryFv(&DAT_8032f480);
    piVar3 = (int *)GetABankAddress__10CRedMemoryFv(&DAT_8032f480);
    iVar4 = GetABufferSize__10CRedMemoryFv(&DAT_8032f480);
    iVar4 = iVar2 + iVar4;
    piVar10 = piVar3;
    do {
      if (piVar10[1] != 0) {
        if (piVar10[3] < 1) {
          iVar5 = iVar4 - (*piVar10 + piVar10[1]);
        }
        else {
          iVar5 = piVar10[2] - (*piVar10 + piVar10[1]);
        }
        uVar9 = *param_1;
        do {
          if ((*(int *)(uVar9 + 0xc) != 0) && (*(int *)(*(int *)(uVar9 + 8) + 0x10) == *piVar10))
          break;
          uVar9 = uVar9 + 0x10;
        } while (uVar9 < *param_1 + 0x400);
        if (uVar9 < *param_1 + 0x400) {
          if (uVar9 < *param_1 + 0x100) {
            uVar1 = uVar9 - *param_1;
            OSReport(s__s__2d___WAVE_4_4d___0x_8_8X___0_801e7a53,&DAT_801e7905,
                     ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0),
                     (int)*(short *)(*(int *)(uVar9 + 8) + 2),
                     *(undefined4 *)(*(int *)(uVar9 + 8) + 0x10),piVar10[1],iVar5,
                     *(undefined4 *)(uVar9 + 4));
            fflush(&DAT_8021d1a8);
          }
          else {
            OSReport(s__s______WAVE_4_4d___0x_8_8X___0x_801e7a8f,&DAT_801e7905,
                     (int)*(short *)(*(int *)(uVar9 + 8) + 2),
                     *(undefined4 *)(*(int *)(uVar9 + 8) + 0x10),piVar10[1],iVar5,
                     *(undefined4 *)(uVar9 + 4));
            fflush(&DAT_8021d1a8);
          }
          iVar6 = iVar6 + 1;
        }
        else {
          uVar9 = (int)piVar10 - (int)piVar3;
          OSReport(s__s______________0x_8_8X___0x_8_8_801e7aca,&DAT_801e7905,*piVar10,piVar10[1],
                   iVar5,((int)uVar9 >> 3) + (uint)((int)uVar9 < 0 && (uVar9 & 7) != 0));
          fflush(&DAT_8021d1a8);
        }
        if (iVar8 < *piVar10 - iVar2) {
          iVar8 = *piVar10 - iVar2;
        }
        iVar7 = iVar7 + piVar10[1];
        iVar2 = *piVar10 + piVar10[1];
      }
      piVar10 = piVar10 + 2;
    } while (piVar10 < piVar3 + 0x800);
    iVar4 = GetABufferAddress__10CRedMemoryFv(&DAT_8032f480);
    iVar5 = GetABufferSize__10CRedMemoryFv(&DAT_8032f480);
    if (iVar8 < (iVar4 + iVar5) - iVar2) {
      iVar8 = GetABufferSize__10CRedMemoryFv(&DAT_8032f480);
      iVar8 = (iVar4 + iVar8) - iVar2;
    }
    OSReport(&DAT_80333d4f,&DAT_801e7905);
    fflush(&DAT_8021d1a8);
    OSReport(s__s_Entry_Wave____d_801e7b01,&DAT_801e7905,iVar6);
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

