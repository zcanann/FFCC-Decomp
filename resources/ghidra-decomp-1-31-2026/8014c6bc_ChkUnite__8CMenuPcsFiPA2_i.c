// Function: ChkUnite__8CMenuPcsFiPA2_i
// Entry: 8014c6bc
// Size: 1572 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

int ChkUnite__8CMenuPcsFiPA2_i(CMenuPcs *menuPcs,int param_2,int *param_3)

{
  short sVar1;
  bool bVar2;
  uint32_t uVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  undefined2 *puVar11;
  short *psVar12;
  int iVar13;
  short *psVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int aiStack_a8 [10];
  int local_80 [10];
  int aiStack_58 [11];
  
  uVar3 = Game.game.m_scriptFoodBase[0];
  if (param_3 != (int *)0x0) {
    *param_3 = -1;
    param_3[1] = -1;
    param_3[2] = -1;
    param_3[3] = -1;
    param_3[4] = -1;
    param_3[5] = -1;
    param_3[6] = -1;
    param_3[7] = -1;
    param_3[8] = -1;
    param_3[9] = -1;
  }
  sVar1 = *(short *)(uVar3 + param_2 * 2 + 0x214);
  uVar4 = -(int)sVar1 & ~(int)sVar1;
  if ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x30) == 1) &&
     (*(short *)(*(int *)&menuPcs->field_0x82c + 0x12) == 2)) {
    if (sVar1 < 0) {
      param_2 = param_2 + -1;
    }
    if (*(short *)(uVar3 + param_2 * 2 + 0x214) < 0) {
      param_2 = param_2 + -1;
    }
  }
  memset(aiStack_a8,0xff,0x28);
  iVar5 = 8;
  iVar7 = 4;
  iVar10 = 2;
  while (iVar10 < 8) {
    iVar17 = iVar5;
    iVar15 = iVar7;
    iVar19 = iVar10;
    if (iVar10 == param_2) {
      if (*(short *)(uVar3 + iVar7 + 0x214) == 0) {
        *(undefined4 *)((int)aiStack_a8 + iVar5) = 0;
      }
      else {
        *(undefined4 *)((int)aiStack_a8 + iVar5) = 0;
        *(undefined4 *)((int)aiStack_a8 + iVar5 + 4) = 0;
        iVar17 = iVar5 + 4;
        iVar15 = iVar7 + 2;
        iVar19 = iVar10 + 1;
        if (*(short *)(uVar3 + iVar7 + 0x218) < 0) {
          *(undefined4 *)((int)aiStack_a8 + iVar5 + 8) = 0;
          iVar17 = iVar5 + 8;
          iVar15 = iVar7 + 4;
          iVar19 = iVar10 + 2;
        }
      }
    }
    else {
      uVar8 = (uint)*(short *)(uVar3 + iVar7 + 0x214);
      *(int *)((int)aiStack_a8 + iVar5) = (int)(-uVar8 | uVar8) >> 0x1f;
    }
    iVar5 = iVar17 + 4;
    iVar7 = iVar15 + 2;
    iVar10 = iVar19 + 1;
  }
  memset(aiStack_58,0xff,0x28);
  iVar7 = uVar3 + 4;
  piVar6 = aiStack_58 + 2;
  iVar5 = 2;
  do {
    if (*(short *)(uVar3 + 0xbaa) <= iVar5) break;
    if (-1 < *(short *)(iVar7 + 0x204)) {
      iVar17 = (int)*(short *)(uVar3 + *(short *)(iVar7 + 0x204) * 2 + 0xb6);
      iVar10 = GetItemIcon__8CMenuPcsFi(menuPcs,iVar17);
      bVar2 = false;
      if ((0xde < iVar17) && (iVar17 < 0xe4)) {
        bVar2 = true;
      }
      if (bVar2) {
        if (iVar17 == 0xdf) {
          *piVar6 = 0x100;
        }
        else if (iVar17 == 0xe0) {
          *piVar6 = 0x101;
        }
        else if (iVar17 == 0xe1) {
          *piVar6 = 0x102;
        }
        else if (iVar17 == 0xe2) {
          *piVar6 = 0x105;
        }
        else {
          *piVar6 = 0x107;
        }
      }
      else if ((((iVar10 == 0) || (iVar10 == 1)) || (iVar10 == 2)) || (iVar10 == 3)) {
        *piVar6 = 999;
      }
      else if ((iVar10 == 0x10) || (iVar10 == 0x11)) {
        *piVar6 = iVar17;
      }
      else {
        *piVar6 = -1;
      }
    }
    iVar5 = iVar5 + 1;
    piVar6 = piVar6 + 1;
    iVar7 = iVar7 + 2;
  } while (iVar5 < 8);
  if (aiStack_58[param_2] < 1) {
    iVar5 = 0;
  }
  else {
    iVar5 = 0;
    iVar7 = 0;
    memset(local_80,0xff,0x28);
    if ((aiStack_58[param_2] == 999) && (2 < param_2)) {
      piVar6 = local_80;
      iVar10 = 0;
      for (psVar14 = &DAT_801de910; -1 < psVar14[1]; psVar14 = psVar14 + 6) {
        if ((*psVar14 != 0) && ((iVar17 = (int)psVar14[2], iVar17 != 2 || (-1 < (int)uVar4)))) {
          iVar13 = 0;
          iVar19 = iVar17 + -1;
          iVar16 = 0;
          psVar12 = psVar14;
          iVar15 = iVar19;
          if (0 < iVar19) {
            do {
              iVar18 = param_2 - (iVar19 - iVar16);
              if (aiStack_a8[iVar18] != 0) break;
              if ((int)psVar12[3] == aiStack_58[iVar18]) {
                iVar13 = iVar13 + 1;
              }
              psVar12 = psVar12 + 1;
              iVar16 = iVar16 + 1;
              iVar15 = iVar15 + -1;
            } while (iVar15 != 0);
          }
          if (iVar13 == iVar17 + -1) {
            *piVar6 = iVar10;
            *(int *)((int)local_80 + iVar7 + 4) = param_2 - (iVar17 + -1);
            piVar6 = piVar6 + 2;
            iVar5 = iVar5 + 1;
            iVar7 = iVar7 + 8;
          }
        }
        iVar10 = iVar10 + 1;
      }
    }
    else if (-1 < (int)uVar4) {
      piVar6 = local_80;
      iVar15 = (int)DAT_801de914;
      iVar10 = param_2 - (iVar15 + -1);
      iVar7 = 0;
      for (iVar17 = 0; iVar17 < iVar15; iVar17 = iVar17 + 1) {
        iVar13 = 0;
        iVar16 = 0;
        puVar11 = &DAT_801de910;
        iVar19 = iVar15;
        if (0 < iVar15) {
          do {
            iVar18 = iVar17 + (param_2 - ((iVar15 + -1) - iVar16));
            if (aiStack_a8[iVar18] != 0) break;
            if ((int)(short)puVar11[3] == aiStack_58[iVar18]) {
              iVar13 = iVar13 + 1;
            }
            puVar11 = puVar11 + 1;
            iVar16 = iVar16 + 1;
            iVar19 = iVar19 + -1;
          } while (iVar19 != 0);
        }
        iVar19 = iVar7;
        if (iVar13 == iVar15) {
          *piVar6 = 0;
          iVar19 = iVar7 + 8;
          piVar6 = piVar6 + 2;
          *(int *)((int)local_80 + iVar7 + 4) = iVar10;
          iVar5 = iVar5 + 1;
        }
        iVar10 = iVar10 + 1;
        iVar7 = iVar19;
      }
    }
    iVar7 = 1;
    piVar6 = local_80 + iVar5 * 2;
    for (psVar14 = &DAT_801de91c; -1 < psVar14[1]; psVar14 = psVar14 + 6) {
      piVar9 = piVar6;
      if ((((*psVar14 == 0) || (aiStack_58[param_2] != 999)) || (param_2 < 3)) &&
         ((iVar10 = (int)psVar14[2], iVar10 != 2 || (-1 < (int)uVar4)))) {
        iVar17 = iVar5 << 3;
        for (iVar15 = 0; iVar15 < iVar10; iVar15 = iVar15 + 1) {
          if ((iVar15 == 0) && ((int)uVar4 < 0)) {
            iVar15 = 1;
          }
          iVar13 = 0;
          iVar16 = 0;
          psVar12 = psVar14;
          iVar19 = iVar10;
          if (0 < iVar10) {
            do {
              iVar18 = iVar15 + (param_2 - ((iVar10 + -1) - iVar16));
              if (aiStack_a8[iVar18] != 0) break;
              if ((int)psVar12[3] == aiStack_58[iVar18]) {
                iVar13 = iVar13 + 1;
              }
              psVar12 = psVar12 + 1;
              iVar16 = iVar16 + 1;
              iVar19 = iVar19 + -1;
            } while (iVar19 != 0);
          }
          if (iVar13 == iVar10) {
            *piVar6 = iVar7;
            *(int *)((int)local_80 + iVar17 + 4) = iVar15 + (param_2 - (iVar10 + -1));
            piVar9 = piVar9 + 2;
            piVar6 = piVar6 + 2;
            iVar5 = iVar5 + 1;
            iVar17 = iVar17 + 8;
          }
        }
      }
      iVar7 = iVar7 + 1;
      piVar6 = piVar9;
    }
    iVar7 = 0;
    do {
      piVar9 = local_80;
      piVar6 = param_3;
      iVar10 = iVar5;
      if (0 < iVar5) {
        do {
          if (iVar7 + 2 == (int)(&DAT_801de914)[*piVar9 * 6]) {
            *param_3 = *piVar9;
            piVar6 = piVar6 + 2;
            param_3[1] = piVar9[1];
            param_3 = param_3 + 2;
          }
          piVar9 = piVar9 + 2;
          iVar10 = iVar10 + -1;
        } while (iVar10 != 0);
      }
      iVar7 = iVar7 + 1;
      param_3 = piVar6;
    } while (iVar7 < 2);
  }
  return iVar5;
}

