// Function: MLstOpen__8CMenuPcsFv
// Entry: 80175210
// Size: 720 bytes

undefined4 MLstOpen__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  int iVar6;
  short *psVar7;
  uint uVar8;
  short sVar9;
  short sVar10;
  undefined2 *puVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  double local_10;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
    fVar3 = FLOAT_803333f0;
    iVar6 = *(int *)&menuPcs->field_0x850 + 8;
    iVar12 = 8;
    do {
      *(float *)(iVar6 + 0x14) = fVar3;
      *(float *)(iVar6 + 0x54) = fVar3;
      *(float *)(iVar6 + 0x94) = fVar3;
      *(float *)(iVar6 + 0xd4) = fVar3;
      *(float *)(iVar6 + 0x114) = fVar3;
      *(float *)(iVar6 + 0x154) = fVar3;
      *(float *)(iVar6 + 0x194) = fVar3;
      *(float *)(iVar6 + 0x1d4) = fVar3;
      dVar5 = DOUBLE_80333420;
      dVar4 = DOUBLE_80333408;
      dVar2 = DOUBLE_803333e8;
      fVar1 = FLOAT_803333d0;
      iVar6 = iVar6 + 0x200;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    sVar9 = 0;
    iVar6 = 0;
    iVar12 = 0;
    sVar10 = 0x18;
    iVar13 = 9;
    do {
      puVar11 = (undefined2 *)(*(int *)&menuPcs->field_0x850 + iVar6 + 8);
      *(undefined4 *)(puVar11 + 0x16) = 2;
      sVar9 = sVar9 + 1;
      *(undefined4 *)(puVar11 + 0xe) = 0x5b;
      iVar6 = iVar6 + 0x40;
      puVar11[2] = 0xe0;
      puVar11[3] = 0x28;
      *puVar11 = (short)(int)-(((double)CONCAT44(0x43300000,(int)(short)puVar11[2] ^ 0x80000000) -
                               dVar4) * dVar2 - dVar5);
      puVar11[1] = sVar10;
      sVar10 = sVar10 + 0x20;
      *(float *)(puVar11 + 4) = fVar1;
      *(float *)(puVar11 + 6) = fVar1;
      *(int *)(puVar11 + 0x12) = iVar12;
      iVar12 = iVar12 + 1;
      *(undefined4 *)(puVar11 + 0x14) = 4;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    **(short **)&menuPcs->field_0x850 = sVar9;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  }
  iVar6 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  uVar8 = (uint)**(short **)&menuPcs->field_0x850;
  psVar7 = *(short **)&menuPcs->field_0x850 + 4;
  iVar12 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  uVar14 = uVar8;
  if (0 < (int)uVar8) {
    do {
      dVar2 = DOUBLE_80333408;
      if (*(int *)(psVar7 + 0x12) <= iVar12) {
        if (iVar12 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
          *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
          local_10 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar7 + 0x14)) ^ 0x80000000);
          *(float *)(psVar7 + 8) =
               (float)((DOUBLE_80333410 / (local_10 - dVar2)) *
                      ((double)CONCAT44(0x43300000,*(uint *)(psVar7 + 0x10) ^ 0x80000000) - dVar2));
        }
        else {
          iVar6 = iVar6 + 1;
          *(float *)(psVar7 + 8) = FLOAT_803333f0;
        }
      }
      psVar7 = psVar7 + 0x20;
      uVar14 = uVar14 - 1;
    } while (uVar14 != 0);
  }
  fVar3 = FLOAT_803333f0;
  if (**(short **)&menuPcs->field_0x850 == iVar6) {
    psVar7 = *(short **)&menuPcs->field_0x850 + 4;
    if (0 < (int)uVar8) {
      uVar14 = uVar8 >> 3;
      if (uVar14 != 0) {
        do {
          psVar7[0x12] = 0;
          psVar7[0x13] = 0;
          psVar7[0x14] = 0;
          psVar7[0x15] = 1;
          *(float *)(psVar7 + 8) = fVar3;
          psVar7[0x32] = 0;
          psVar7[0x33] = 0;
          psVar7[0x34] = 0;
          psVar7[0x35] = 1;
          *(float *)(psVar7 + 0x28) = fVar3;
          psVar7[0x52] = 0;
          psVar7[0x53] = 0;
          psVar7[0x54] = 0;
          psVar7[0x55] = 1;
          *(float *)(psVar7 + 0x48) = fVar3;
          psVar7[0x72] = 0;
          psVar7[0x73] = 0;
          psVar7[0x74] = 0;
          psVar7[0x75] = 1;
          *(float *)(psVar7 + 0x68) = fVar3;
          psVar7[0x92] = 0;
          psVar7[0x93] = 0;
          psVar7[0x94] = 0;
          psVar7[0x95] = 1;
          *(float *)(psVar7 + 0x88) = fVar3;
          psVar7[0xb2] = 0;
          psVar7[0xb3] = 0;
          psVar7[0xb4] = 0;
          psVar7[0xb5] = 1;
          *(float *)(psVar7 + 0xa8) = fVar3;
          psVar7[0xd2] = 0;
          psVar7[0xd3] = 0;
          psVar7[0xd4] = 0;
          psVar7[0xd5] = 1;
          *(float *)(psVar7 + 200) = fVar3;
          psVar7[0xf2] = 0;
          psVar7[0xf3] = 0;
          psVar7[0xf4] = 0;
          psVar7[0xf5] = 1;
          *(float *)(psVar7 + 0xe8) = fVar3;
          psVar7 = psVar7 + 0x100;
          uVar14 = uVar14 - 1;
        } while (uVar14 != 0);
        uVar8 = uVar8 & 7;
        if (uVar8 == 0) {
          return 1;
        }
      }
      do {
        psVar7[0x12] = 0;
        psVar7[0x13] = 0;
        psVar7[0x14] = 0;
        psVar7[0x15] = 1;
        *(float *)(psVar7 + 8) = fVar3;
        psVar7 = psVar7 + 0x20;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
    }
    return 1;
  }
  return 0;
}

