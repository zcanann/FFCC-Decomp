// Function: EquipOpen__8CMenuPcsFv
// Entry: 8015d108
// Size: 948 bytes

undefined4 EquipOpen__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  int iVar6;
  short *psVar7;
  uint uVar8;
  undefined2 *puVar9;
  short sVar10;
  int iVar11;
  uint uVar12;
  double local_20;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
    fVar5 = FLOAT_80332ee0;
    iVar6 = *(int *)&menuPcs->field_0x850 + 8;
    iVar11 = 8;
    do {
      *(float *)(iVar6 + 0x14) = fVar5;
      *(float *)(iVar6 + 0x54) = fVar5;
      *(float *)(iVar6 + 0x94) = fVar5;
      *(float *)(iVar6 + 0xd4) = fVar5;
      *(float *)(iVar6 + 0x114) = fVar5;
      *(float *)(iVar6 + 0x154) = fVar5;
      *(float *)(iVar6 + 0x194) = fVar5;
      *(float *)(iVar6 + 0x1d4) = fVar5;
      dVar4 = DOUBLE_80332ed8;
      dVar3 = DOUBLE_80332ed0;
      dVar2 = DOUBLE_80332ec8;
      fVar1 = FLOAT_80332eb8;
      iVar6 = iVar6 + 0x200;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    iVar6 = 0;
    puVar9 = (undefined2 *)(*(int *)&menuPcs->field_0x850 + 8);
    iVar11 = 2;
    do {
      *(undefined4 *)(puVar9 + 0xe) = 0x34;
      puVar9[2] = 200;
      puVar9[3] = 0x28;
      *puVar9 = (short)(int)-(((double)CONCAT44(0x43300000,(int)(short)puVar9[2] ^ 0x80000000) -
                              dVar4) * dVar3 - dVar2);
      puVar9[1] = (short)iVar6 * (puVar9[3] + -8) + 0x60;
      *(float *)(puVar9 + 4) = fVar1;
      *(float *)(puVar9 + 6) = fVar1;
      *(int *)(puVar9 + 0x12) = iVar6;
      *(undefined4 *)(puVar9 + 0x14) = 3;
      *(undefined4 *)(puVar9 + 0x2e) = 0x34;
      puVar9[0x22] = 200;
      puVar9[0x23] = 0x28;
      puVar9[0x20] = (short)(int)-(((double)CONCAT44(0x43300000,
                                                     (int)(short)puVar9[0x22] ^ 0x80000000) - dVar4)
                                   * dVar3 - dVar2);
      puVar9[0x21] = (short)(iVar6 + 1) * (puVar9[0x23] + -8) + 0x60;
      *(float *)(puVar9 + 0x24) = fVar1;
      *(float *)(puVar9 + 0x26) = fVar1;
      *(int *)(puVar9 + 0x32) = iVar6 + 1;
      iVar6 = iVar6 + 2;
      *(undefined4 *)(puVar9 + 0x34) = 3;
      puVar9 = puVar9 + 0x40;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
    **(undefined2 **)&menuPcs->field_0x850 = 4;
    EquipInit1__8CMenuPcsFv(menuPcs);
    puVar9 = (undefined2 *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    sVar10 = 0;
    for (iVar6 = 0; iVar6 < 0x40; iVar6 = iVar6 + 1) {
      iVar11 = GetItemType__8CMenuPcsFii(menuPcs,iVar6,0);
      if (iVar11 == 1) {
        puVar9 = puVar9 + 1;
        *puVar9 = (short)iVar6;
        sVar10 = sVar10 + 1;
      }
    }
    psVar7 = (short *)GetLetterBuffer__6JoyBusFi(&Joybus,0);
    *psVar7 = sVar10 + 1;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  }
  iVar6 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  uVar8 = (uint)**(short **)&menuPcs->field_0x850;
  psVar7 = *(short **)&menuPcs->field_0x850 + 4;
  iVar11 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  uVar12 = uVar8;
  if (0 < (int)uVar8) {
    do {
      dVar2 = DOUBLE_80332ed8;
      if (*(int *)(psVar7 + 0x12) <= iVar11) {
        if (iVar11 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
          *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
          local_20 = (double)(CONCAT44(0x43300000,*(undefined4 *)(psVar7 + 0x14)) ^ 0x80000000);
          *(float *)(psVar7 + 8) =
               (float)((DOUBLE_80332ec0 / (local_20 - dVar2)) *
                      ((double)CONCAT44(0x43300000,*(uint *)(psVar7 + 0x10) ^ 0x80000000) - dVar2));
        }
        else {
          iVar6 = iVar6 + 1;
          *(float *)(psVar7 + 8) = FLOAT_80332ee0;
        }
      }
      psVar7 = psVar7 + 0x20;
      uVar12 = uVar12 - 1;
    } while (uVar12 != 0);
  }
  fVar5 = FLOAT_80332ee0;
  if (**(short **)&menuPcs->field_0x850 == iVar6) {
    psVar7 = *(short **)&menuPcs->field_0x850 + 4;
    if (0 < (int)uVar8) {
      uVar12 = uVar8 >> 3;
      if (uVar12 != 0) {
        do {
          psVar7[0x12] = 0;
          psVar7[0x13] = 0;
          psVar7[0x14] = 0;
          psVar7[0x15] = 1;
          *(float *)(psVar7 + 8) = fVar5;
          psVar7[0x32] = 0;
          psVar7[0x33] = 0;
          psVar7[0x34] = 0;
          psVar7[0x35] = 1;
          *(float *)(psVar7 + 0x28) = fVar5;
          psVar7[0x52] = 0;
          psVar7[0x53] = 0;
          psVar7[0x54] = 0;
          psVar7[0x55] = 1;
          *(float *)(psVar7 + 0x48) = fVar5;
          psVar7[0x72] = 0;
          psVar7[0x73] = 0;
          psVar7[0x74] = 0;
          psVar7[0x75] = 1;
          *(float *)(psVar7 + 0x68) = fVar5;
          psVar7[0x92] = 0;
          psVar7[0x93] = 0;
          psVar7[0x94] = 0;
          psVar7[0x95] = 1;
          *(float *)(psVar7 + 0x88) = fVar5;
          psVar7[0xb2] = 0;
          psVar7[0xb3] = 0;
          psVar7[0xb4] = 0;
          psVar7[0xb5] = 1;
          *(float *)(psVar7 + 0xa8) = fVar5;
          psVar7[0xd2] = 0;
          psVar7[0xd3] = 0;
          psVar7[0xd4] = 0;
          psVar7[0xd5] = 1;
          *(float *)(psVar7 + 200) = fVar5;
          psVar7[0xf2] = 0;
          psVar7[0xf3] = 0;
          psVar7[0xf4] = 0;
          psVar7[0xf5] = 1;
          *(float *)(psVar7 + 0xe8) = fVar5;
          psVar7 = psVar7 + 0x100;
          uVar12 = uVar12 - 1;
        } while (uVar12 != 0);
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
        *(float *)(psVar7 + 8) = fVar5;
        psVar7 = psVar7 + 0x20;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
    }
    return 1;
  }
  return 0;
}

