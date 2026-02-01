// Function: MoneyOpen__8CMenuPcsFv
// Entry: 8015f688
// Size: 928 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

bool MoneyOpen__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  bool bVar2;
  uint32_t uVar3;
  float fVar4;
  double dVar5;
  double dVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  short *psVar11;
  int iVar12;
  int iVar13;
  undefined4 *puVar14;
  int iVar15;
  undefined8 local_20;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
    fVar1 = FLOAT_80332f70;
    iVar8 = *(int *)&menuPcs->field_0x850 + 8;
    iVar15 = 8;
    do {
      *(float *)(iVar8 + 0x14) = fVar1;
      *(float *)(iVar8 + 0x54) = fVar1;
      *(float *)(iVar8 + 0x94) = fVar1;
      *(float *)(iVar8 + 0xd4) = fVar1;
      *(float *)(iVar8 + 0x114) = fVar1;
      *(float *)(iVar8 + 0x154) = fVar1;
      *(float *)(iVar8 + 0x194) = fVar1;
      *(float *)(iVar8 + 0x1d4) = fVar1;
      iVar8 = iVar8 + 0x200;
      iVar15 = iVar15 + -1;
    } while (iVar15 != 0);
    iVar8 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar8 + 0x24) = 0x3b;
    dVar5 = DOUBLE_80332f88;
    *(undefined2 *)(iVar8 + 10) = 0x68;
    *(undefined2 *)(iVar8 + 0xc) = 0xf8;
    puVar9 = s_place;
    *(undefined2 *)(iVar8 + 0xe) = 0x88;
    fVar4 = FLOAT_80332f70;
    fVar1 = FLOAT_80332f64;
    iVar15 = 0;
    *(short *)(iVar8 + 8) =
         (short)(int)-(((double)CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0xc) ^ 0x80000000) -
                       dVar5) * DOUBLE_80332fa0 - DOUBLE_80332f98);
    *(float *)(iVar8 + 0x10) = fVar1;
    *(float *)(iVar8 + 0x14) = fVar1;
    *(float *)(iVar8 + 0x1c) = fVar4;
    *(undefined4 *)(iVar8 + 0x2c) = 0;
    *(undefined4 *)(iVar8 + 0x30) = 10;
    **(undefined2 **)&menuPcs->field_0x850 = 1;
    uVar3 = Game.game.m_scriptFoodBase[0];
    DAT_8032eee0 = 0;
    do {
      iVar8 = 10000000;
      if (iVar15 == 0) {
        iVar12 = *(int *)(uVar3 + 0x200);
      }
      else {
        iVar12 = 0;
      }
      iVar13 = 0;
      iVar7 = 8;
      bVar2 = false;
      puVar14 = puVar9;
      do {
        if ((!bVar2) && (iVar8 <= iVar12)) {
          bVar2 = true;
        }
        if (((bVar2) || (iVar8 <= iVar12)) || (6 < iVar13)) {
          iVar10 = iVar12 / iVar8;
          if (9 < iVar10) {
            iVar10 = 9;
          }
          *(char *)puVar14 = (char)iVar10;
          iVar12 = iVar12 - (iVar12 / iVar8) * iVar8;
        }
        else {
          *(undefined *)puVar14 = 0xff;
        }
        puVar14 = (undefined4 *)((int)puVar14 + 1);
        iVar13 = iVar13 + 1;
        iVar8 = iVar8 / 10 + (iVar8 >> 0x1f);
        iVar8 = iVar8 - (iVar8 >> 0x1f);
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      iVar15 = iVar15 + 1;
      puVar9 = puVar9 + 2;
    } while (iVar15 < 2);
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  }
  iVar15 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar12 = (int)**(short **)&menuPcs->field_0x850;
  psVar11 = *(short **)&menuPcs->field_0x850 + 4;
  iVar7 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  iVar8 = iVar12;
  if (0 < iVar12) {
    do {
      dVar5 = DOUBLE_80332f88;
      fVar1 = FLOAT_80332f64;
      if (*(int *)(psVar11 + 0x12) <= iVar7) {
        if (iVar7 < *(int *)(psVar11 + 0x12) + *(int *)(psVar11 + 0x14)) {
          *(int *)(psVar11 + 0x10) = *(int *)(psVar11 + 0x10) + 1;
          dVar6 = DOUBLE_80332f90;
          local_20 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar11 + 0x14)) ^ 0x80000000);
          *(float *)(psVar11 + 8) =
               (float)((DOUBLE_80332f90 / (local_20 - dVar5)) *
                      ((double)CONCAT44(0x43300000,*(uint *)(psVar11 + 0x10) ^ 0x80000000) - dVar5))
          ;
          if ((*(uint *)(psVar11 + 0x16) & 2) == 0) {
            local_20 = (double)CONCAT44(0x43300000,*(uint *)(psVar11 + 0x14) ^ 0x80000000);
            fVar1 = (float)((dVar6 / (local_20 - dVar5)) *
                           ((double)CONCAT44(0x43300000,*(uint *)(psVar11 + 0x10) ^ 0x80000000) -
                           dVar5));
            *(float *)(psVar11 + 0x18) =
                 (*(float *)(psVar11 + 0x1c) -
                 (float)((double)CONCAT44(0x43300000,(int)*psVar11 ^ 0x80000000) - dVar5)) * fVar1;
            *(float *)(psVar11 + 0x1a) =
                 (*(float *)(psVar11 + 0x1e) -
                 (float)((double)CONCAT44(0x43300000,(int)psVar11[1] ^ 0x80000000) - dVar5)) * fVar1
            ;
          }
        }
        else {
          iVar15 = iVar15 + 1;
          *(float *)(psVar11 + 8) = FLOAT_80332f70;
          *(float *)(psVar11 + 0x18) = fVar1;
          *(float *)(psVar11 + 0x1a) = fVar1;
        }
      }
      psVar11 = psVar11 + 0x20;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  return iVar12 == iVar15;
}

