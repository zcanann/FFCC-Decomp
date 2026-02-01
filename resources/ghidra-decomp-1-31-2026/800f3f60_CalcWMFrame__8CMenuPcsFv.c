// Function: CalcWMFrame__8CMenuPcsFv
// Entry: 800f3f60
// Size: 3012 bytes

/* WARNING: Removing unreachable block (ram,0x800f4b10) */
/* WARNING: Removing unreachable block (ram,0x800f3f68) */
/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void CalcWMFrame__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  char cVar2;
  short sVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  uint uVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  int *piVar17;
  float *pfVar18;
  int iVar19;
  float *pfVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int local_58 [4];
  undefined8 local_48;
  double local_40;
  undefined8 local_38;
  
  sVar3 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x10);
  if (sVar3 == 0) {
    return;
  }
  if (2 < sVar3) {
    return;
  }
  if ((sVar3 == 2) && (menuPcs->field_0x13 != '\0')) {
    *(int *)(*(int *)&menuPcs->field_0x81c + 4) = *(int *)(*(int *)&menuPcs->field_0x81c + 4) + -1;
    if (*(int *)(*(int *)&menuPcs->field_0x81c + 4) < 0) {
      *(undefined4 *)(*(int *)&menuPcs->field_0x81c + 4) = 0;
    }
  }
  else {
    if ((menuPcs->field_0xa & 1) != 0) {
      iVar16 = *(int *)(*(int *)&menuPcs->field_0x81c + 4);
      if (iVar16 != 0) {
        *(int *)(*(int *)&menuPcs->field_0x81c + 4) = iVar16 + -1;
        if (*(int *)(*(int *)&menuPcs->field_0x81c + 4) < 0) {
          *(undefined4 *)(*(int *)&menuPcs->field_0x81c + 4) = 0;
        }
        if (*(int *)(*(int *)&menuPcs->field_0x81c + 4) == 0) {
          menuPcs->field_0xa = menuPcs->field_0xa & 0xfe;
        }
        goto LAB_800f4038;
      }
    }
    iVar16 = *(int *)(*(int *)&menuPcs->field_0x81c + 4);
    if (iVar16 < 10) {
      *(int *)(*(int *)&menuPcs->field_0x81c + 4) = iVar16 + 1;
    }
  }
LAB_800f4038:
  *(undefined2 *)(*(int *)&menuPcs->field_0x81c + 0x98) = 0x68;
  fVar1 = FLOAT_803313dc;
  *(undefined2 *)(*(int *)&menuPcs->field_0x81c + 0x9a) = 0x14;
  *(undefined2 *)(*(int *)&menuPcs->field_0x81c + 0x9c) = 200;
  *(undefined2 *)(*(int *)&menuPcs->field_0x81c + 0x9e) = 0x28;
  *(float *)(*(int *)&menuPcs->field_0x81c + 0xa0) = fVar1;
  if ((menuPcs->field_0xa & 1) == 0) {
    local_58[2] = 0x43300000;
    local_58[3] = (int)*(short *)(*(int *)&menuPcs->field_0x81c + 0x9e) *
                  (int)(char)menuPcs->field_0x4 ^ 0x80000000;
    *(float *)(*(int *)&menuPcs->field_0x81c + 0xa4) =
         (float)((double)CONCAT44(0x43300000,local_58[3]) - DOUBLE_80331408);
  }
  else {
    local_58[2] = 0x43300000;
    local_58[3] = (int)*(short *)(*(int *)&menuPcs->field_0x81c + 0x9e) *
                  (int)(char)menuPcs->field_0x5 ^ 0x80000000;
    *(float *)(*(int *)&menuPcs->field_0x81c + 0xa4) =
         (float)((double)CONCAT44(0x43300000,local_58[3]) - DOUBLE_80331408);
  }
  *(short *)(*(int *)&menuPcs->field_0x81c + 0x98) =
       (short)(10 - *(int *)(*(int *)&menuPcs->field_0x81c + 4)) * 2 + 0x68;
  if ((((menuPcs->field_0xa & 2) != 0) ||
      ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) == 2 && (menuPcs->field_0x13 != '\0')))) &&
     (9 < *(int *)(*(int *)&menuPcs->field_0x81c + 8))) {
    *(undefined4 *)(*(int *)&menuPcs->field_0x81c + 8) = 0;
    menuPcs->field_0xa = menuPcs->field_0xa & 0xfd;
  }
  fVar1 = FLOAT_803313e8;
  if ((menuPcs->field_0xa & 2) == 0) {
    cVar2 = menuPcs->field_0xc;
  }
  else {
    cVar2 = menuPcs->field_0xb;
  }
  uVar13 = Game.game.m_gameWork._8_4_ + (int)cVar2;
  DAT_8032ee30 = (undefined)uVar13;
  if (99 < (int)uVar13) {
    DAT_8032ee30 = 100;
  }
  uVar14 = 1 - ((int)(((int)(uVar13 ^ 9) >> 1) - ((uVar13 ^ 9) & uVar13)) >> 0x1f);
  if (99 < (int)uVar13) {
    uVar14 = 3;
  }
  *(float *)(*(int *)&menuPcs->field_0x81c + 200) = FLOAT_803313e8;
  *(float *)(*(int *)&menuPcs->field_0x81c + 0xe4) = fVar1;
  dVar12 = DOUBLE_80331540;
  dVar11 = DOUBLE_80331538;
  fVar4 = FLOAT_80331528;
  fVar1 = FLOAT_80331524;
  dVar10 = DOUBLE_80331490;
  dVar9 = DOUBLE_80331408;
  iVar16 = DAT_801dc140;
  if (uVar14 == 3) {
    *(short *)(*(int *)&menuPcs->field_0x81c + 0xb4) = (short)((0x2b - DAT_801dc140) / 2) + 0x2c;
    *(undefined2 *)(*(int *)&menuPcs->field_0x81c + 0xb6) = 0x43;
    *(short *)(*(int *)&menuPcs->field_0x81c + 0xb8) = (short)iVar16;
    *(undefined2 *)(*(int *)&menuPcs->field_0x81c + 0xba) = 0x20;
    *(float *)(*(int *)&menuPcs->field_0x81c + 0xbc) = fVar1;
    *(float *)(*(int *)&menuPcs->field_0x81c + 0xc0) = fVar4;
  }
  else {
    iVar16 = (int)uVar13 / 10 + ((int)uVar13 >> 0x1f);
    local_58[0] = uVar13 + (iVar16 - (iVar16 >> 0x1f)) * -10;
    if (1 < uVar14) {
      local_58[1] = iVar16 - (iVar16 >> 0x1f);
    }
    iVar16 = *(int *)(&DAT_801dc118 + local_58[0] * 4);
    if (1 < uVar14) {
      iVar15 = (int)uVar13 / 10 + ((int)uVar13 >> 0x1f);
      iVar16 = iVar16 + *(int *)(&DAT_801dc118 + (iVar15 - (iVar15 >> 0x1f)) * 4);
    }
    iVar19 = uVar14 - 1;
    iVar15 = (0x2b - iVar16) / 2 + 0x2c;
    iVar16 = iVar19 * 0x1c;
    piVar17 = local_58 + iVar19;
    uVar13 = uVar14;
    if (-1 < iVar19) {
      do {
        iVar23 = *piVar17;
        *(short *)(*(int *)&menuPcs->field_0x81c + iVar16 + 0xb4) = (short)iVar15;
        iVar19 = *(int *)(&DAT_801dc118 + iVar23 * 4);
        piVar17 = piVar17 + -1;
        iVar21 = iVar23 / 5 + (iVar23 >> 0x1f);
        *(undefined2 *)(*(int *)&menuPcs->field_0x81c + iVar16 + 0xb6) = 0x43;
        local_58[2] = 0x43300000;
        iVar24 = iVar16 + 0xba;
        *(short *)(*(int *)&menuPcs->field_0x81c + iVar16 + 0xb8) = (short)iVar19;
        local_58[3] = iVar23 + (iVar21 - (iVar21 >> 0x1f)) * -5 ^ 0x80000000;
        iVar22 = iVar16 + 0xbc;
        iVar23 = iVar16 + 0xc0;
        iVar15 = iVar15 + iVar19;
        iVar16 = iVar16 + -0x1c;
        local_48 = (double)CONCAT44(0x43300000,iVar21 - (iVar21 >> 0x1f) ^ 0x80000000);
        *(undefined2 *)(*(int *)&menuPcs->field_0x81c + iVar24) = 0x20;
        *(float *)(*(int *)&menuPcs->field_0x81c + iVar22) =
             (float)(dVar10 * (double)(float)((double)CONCAT44(0x43300000,local_58[3]) - dVar9));
        *(float *)(*(int *)&menuPcs->field_0x81c + iVar23) =
             (float)(dVar12 * (double)(float)(local_48 - dVar9) + dVar11);
        uVar13 = uVar13 - 1;
      } while (uVar13 != 0);
    }
  }
  dVar11 = DOUBLE_803316e8;
  dVar10 = DOUBLE_80331408;
  dVar9 = DOUBLE_803313f8;
  fVar1 = FLOAT_803313dc;
  if (((menuPcs->field_0xa & 2) == 0) &&
     ((*(short *)(*(int *)&menuPcs->field_0x82c + 0x10) != 2 || (menuPcs->field_0x13 == '\0')))) {
    iVar16 = *(int *)&menuPcs->field_0x81c;
    uVar13 = *(uint *)(iVar16 + 8);
    local_38 = (double)(CONCAT44(0x43300000,uVar13 - 5) ^ 0x80000000);
    if ((float)(local_38 - DOUBLE_80331408) <
        (float)(DOUBLE_803314a8 * (double)DAT_8032e8c4[DAT_8032e8c0 * 4 + -4])) {
      local_38 = (double)CONCAT44(0x43300000,uVar13 ^ 0x80000000);
      fVar4 = (float)(local_38 - DOUBLE_80331408) / FLOAT_803314c0;
      if (fVar4 < DAT_8032e8c4[DAT_8032e8c0 * 4 + -4]) {
        iVar19 = 0;
        pfVar18 = DAT_8032e8c4;
        iVar15 = DAT_8032e8c0;
        fVar5 = FLOAT_803313dc;
        if (0 < DAT_8032e8c0) {
          do {
            if (fVar4 <= *pfVar18) {
              if (iVar19 == 0) {
                fVar5 = DAT_8032e8c4[1];
              }
              else {
                pfVar20 = DAT_8032e8c4 + iVar19 * 4;
                pfVar18 = DAT_8032e8c4 + (iVar19 + -1) * 4;
                fVar5 = *pfVar20 - *pfVar18;
                fVar8 = (fVar4 - *pfVar18) / fVar5;
                fVar7 = fVar8 * fVar8;
                fVar6 = fVar7 * fVar8;
                fVar5 = fVar5 * (pfVar18[3] * (fVar8 + -(FLOAT_803314c8 * fVar7 - fVar6)) +
                                pfVar20[2] * (fVar6 - fVar7)) +
                        pfVar18[1] *
                        (FLOAT_803313e8 + (FLOAT_803314c8 * fVar6 - FLOAT_803314c4 * fVar7)) +
                        pfVar20[1] * (FLOAT_803314cc * fVar6 + FLOAT_803314c4 * fVar7);
              }
              break;
            }
            pfVar18 = pfVar18 + 4;
            iVar19 = iVar19 + 1;
            iVar15 = iVar15 + -1;
          } while (iVar15 != 0);
        }
      }
      else {
        fVar5 = DAT_8032e8c4[DAT_8032e8c0 * 4 + -3];
      }
      local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar16 + 0xd2)) ^ 0x80000000);
      *(short *)(iVar16 + 0xd2) = (short)(int)((float)(local_38 - DOUBLE_80331408) + fVar5);
      if (fVar4 < DAT_8032e8cc[DAT_8032e8c8 * 4 + -4]) {
        iVar15 = 0;
        pfVar18 = DAT_8032e8cc;
        iVar16 = DAT_8032e8c8;
        if (0 < DAT_8032e8c8) {
          do {
            if (fVar4 <= *pfVar18) {
              if (iVar15 == 0) {
                fVar1 = DAT_8032e8cc[1];
              }
              else {
                pfVar20 = DAT_8032e8cc + iVar15 * 4;
                pfVar18 = DAT_8032e8cc + (iVar15 + -1) * 4;
                fVar1 = *pfVar20 - *pfVar18;
                fVar6 = (fVar4 - *pfVar18) / fVar1;
                fVar5 = fVar6 * fVar6;
                fVar4 = fVar5 * fVar6;
                fVar1 = fVar1 * (pfVar18[3] * (fVar6 + -(FLOAT_803314c8 * fVar5 - fVar4)) +
                                pfVar20[2] * (fVar4 - fVar5)) +
                        pfVar18[1] *
                        (FLOAT_803313e8 + (FLOAT_803314c8 * fVar4 - FLOAT_803314c4 * fVar5)) +
                        pfVar20[1] * (FLOAT_803314cc * fVar4 + FLOAT_803314c4 * fVar5);
              }
              break;
            }
            pfVar18 = pfVar18 + 4;
            iVar15 = iVar15 + 1;
            iVar16 = iVar16 + -1;
          } while (iVar16 != 0);
        }
      }
      else {
        fVar1 = DAT_8032e8cc[DAT_8032e8c8 * 4 + -3];
      }
      *(float *)(*(int *)&menuPcs->field_0x81c + 0xe0) = fVar1;
      fVar1 = FLOAT_803313dc;
      if (uVar14 == 2) {
        uVar13 = uVar13 - 5;
      }
      local_38 = (double)CONCAT44(0x43300000,uVar13 ^ 0x80000000);
      fVar4 = (float)(local_38 - DOUBLE_80331408) / FLOAT_803314c0;
      if (fVar4 < DAT_8032e8c4[DAT_8032e8c0 * 4 + -4]) {
        iVar15 = 0;
        pfVar18 = DAT_8032e8c4;
        iVar16 = DAT_8032e8c0;
        fVar5 = FLOAT_803313dc;
        if (0 < DAT_8032e8c0) {
          do {
            if (fVar4 <= *pfVar18) {
              if (iVar15 == 0) {
                fVar5 = DAT_8032e8c4[1];
              }
              else {
                pfVar20 = DAT_8032e8c4 + iVar15 * 4;
                pfVar18 = DAT_8032e8c4 + (iVar15 + -1) * 4;
                fVar5 = *pfVar20 - *pfVar18;
                fVar8 = (fVar4 - *pfVar18) / fVar5;
                fVar7 = fVar8 * fVar8;
                fVar6 = fVar7 * fVar8;
                fVar5 = fVar5 * (pfVar18[3] * (fVar8 + -(FLOAT_803314c8 * fVar7 - fVar6)) +
                                pfVar20[2] * (fVar6 - fVar7)) +
                        pfVar18[1] *
                        (FLOAT_803313e8 + (FLOAT_803314c8 * fVar6 - FLOAT_803314c4 * fVar7)) +
                        pfVar20[1] * (FLOAT_803314cc * fVar6 + FLOAT_803314c4 * fVar7);
              }
              break;
            }
            pfVar18 = pfVar18 + 4;
            iVar15 = iVar15 + 1;
            iVar16 = iVar16 + -1;
          } while (iVar16 != 0);
        }
      }
      else {
        fVar5 = DAT_8032e8c4[DAT_8032e8c0 * 4 + -3];
      }
      local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(*(int *)&menuPcs->field_0x81c + 0xb6))
                         ^ 0x80000000);
      *(short *)(*(int *)&menuPcs->field_0x81c + 0xb6) =
           (short)(int)((float)(local_38 - DOUBLE_80331408) + fVar5);
      if (fVar4 < DAT_8032e8cc[DAT_8032e8c8 * 4 + -4]) {
        iVar15 = 0;
        pfVar18 = DAT_8032e8cc;
        iVar16 = DAT_8032e8c8;
        if (0 < DAT_8032e8c8) {
          do {
            if (fVar4 <= *pfVar18) {
              if (iVar15 == 0) {
                fVar1 = DAT_8032e8cc[1];
              }
              else {
                pfVar20 = DAT_8032e8cc + iVar15 * 4;
                pfVar18 = DAT_8032e8cc + (iVar15 + -1) * 4;
                fVar1 = *pfVar20 - *pfVar18;
                fVar6 = (fVar4 - *pfVar18) / fVar1;
                fVar5 = fVar6 * fVar6;
                fVar4 = fVar5 * fVar6;
                fVar1 = fVar1 * (pfVar18[3] * (fVar6 + -(FLOAT_803314c8 * fVar5 - fVar4)) +
                                pfVar20[2] * (fVar4 - fVar5)) +
                        pfVar18[1] *
                        (FLOAT_803313e8 + (FLOAT_803314c8 * fVar4 - FLOAT_803314c4 * fVar5)) +
                        pfVar20[1] * (FLOAT_803314cc * fVar4 + FLOAT_803314c4 * fVar5);
              }
              break;
            }
            pfVar18 = pfVar18 + 4;
            iVar15 = iVar15 + 1;
            iVar16 = iVar16 + -1;
          } while (iVar16 != 0);
        }
      }
      else {
        fVar1 = DAT_8032e8cc[DAT_8032e8c8 * 4 + -3];
      }
      *(float *)(*(int *)&menuPcs->field_0x81c + 0xc4) = fVar1;
      *(int *)(*(int *)&menuPcs->field_0x81c + 8) = *(int *)(*(int *)&menuPcs->field_0x81c + 8) + 1;
    }
  }
  else {
    iVar16 = 0;
    iVar15 = 0;
    uVar13 = uVar14;
    while ((uVar13 != 0 && ((iVar16 == 0 || (uVar14 == 2))))) {
      local_48 = (double)(CONCAT44(0x43300000,10 - *(int *)(*(int *)&menuPcs->field_0x81c + 8)) ^
                         0x80000000);
      fVar1 = (float)((double)(float)(local_48 - dVar10) / dVar11);
      *(float *)(*(int *)&menuPcs->field_0x81c + iVar15 + 0xc4) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x81c + iVar15 + 200) =
           (float)(dVar9 * (double)fVar1 + dVar9);
      iVar19 = *(int *)&menuPcs->field_0x81c + iVar15;
      local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar19 + 0xba)) ^ 0x80000000);
      *(short *)(iVar19 + 0xb6) =
           *(short *)(iVar19 + 0xb6) +
           (short)(int)((float)(local_40 - dVar10) -
                       (float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(iVar19 + 0xba) ^ 0x80000000) -
                              dVar10) * *(float *)(iVar19 + 200));
      if ((iVar16 == 0) && ((uVar14 == 1 || (uVar14 == 3)))) {
        iVar19 = *(int *)&menuPcs->field_0x81c + iVar15;
        local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar19 + 0xb8)) ^ 0x80000000);
        local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar19 + 0xb8)) ^ 0x80000000);
        *(short *)(iVar19 + 0xb4) =
             *(short *)(iVar19 + 0xb4) +
             (short)(int)((DOUBLE_80331420 +
                          (double)((float)(local_40 - DOUBLE_80331408) -
                                  (float)(local_38 - DOUBLE_80331408) * *(float *)(iVar19 + 200))) *
                         DOUBLE_803313f8);
      }
      else if (iVar16 != 0) {
        iVar19 = *(int *)&menuPcs->field_0x81c + iVar15;
        local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar19 + 0xb8)) ^ 0x80000000);
        local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar19 + 0xb8)) ^ 0x80000000);
        *(short *)(iVar19 + 0xb4) =
             *(short *)(iVar19 + 0xb4) +
             (short)(int)((float)(local_40 - DOUBLE_80331408) -
                         (float)(local_38 - DOUBLE_80331408) * *(float *)(iVar19 + 200));
      }
      iVar15 = iVar15 + 0x1c;
      iVar16 = iVar16 + 1;
      uVar13 = uVar13 - 1;
    }
    *(int *)(*(int *)&menuPcs->field_0x81c + 8) = *(int *)(*(int *)&menuPcs->field_0x81c + 8) + 1;
  }
  return;
}

