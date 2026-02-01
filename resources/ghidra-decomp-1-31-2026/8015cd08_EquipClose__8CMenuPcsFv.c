// Function: EquipClose__8CMenuPcsFv
// Entry: 8015cd08
// Size: 428 bytes

undefined4 EquipClose__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  short *psVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  iVar5 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  uVar6 = (uint)**(short **)&menuPcs->field_0x850;
  psVar4 = *(short **)&menuPcs->field_0x850 + 4;
  iVar7 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  uVar8 = uVar6;
  if (0 < (int)uVar6) {
    do {
      dVar2 = DOUBLE_80332ed8;
      if (*(int *)(psVar4 + 0x12) <= iVar7) {
        if (iVar7 < *(int *)(psVar4 + 0x12) + *(int *)(psVar4 + 0x14)) {
          *(int *)(psVar4 + 0x10) = *(int *)(psVar4 + 0x10) + 1;
          dVar3 = DOUBLE_80332f08;
          *(float *)(psVar4 + 8) =
               (float)-((DOUBLE_80332ec0 /
                        ((double)CONCAT44(0x43300000,*(uint *)(psVar4 + 0x14) ^ 0x80000000) - dVar2)
                        ) * ((double)CONCAT44(0x43300000,*(uint *)(psVar4 + 0x10) ^ 0x80000000) -
                            dVar2) - DOUBLE_80332ec0);
          if ((double)*(float *)(psVar4 + 8) < dVar3) {
            *(float *)(psVar4 + 8) = FLOAT_80332eb8;
          }
        }
        else {
          iVar5 = iVar5 + 1;
          *(float *)(psVar4 + 8) = FLOAT_80332eb8;
        }
      }
      psVar4 = psVar4 + 0x20;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  fVar1 = FLOAT_80332eb8;
  if (**(short **)&menuPcs->field_0x850 == iVar5) {
    psVar4 = *(short **)&menuPcs->field_0x850 + 4;
    if (0 < (int)uVar6) {
      uVar8 = uVar6 >> 3;
      if (uVar8 != 0) {
        do {
          psVar4[0x12] = 0;
          psVar4[0x13] = 0;
          psVar4[0x14] = 0;
          psVar4[0x15] = 1;
          *(float *)(psVar4 + 8) = fVar1;
          psVar4[0x32] = 0;
          psVar4[0x33] = 0;
          psVar4[0x34] = 0;
          psVar4[0x35] = 1;
          *(float *)(psVar4 + 0x28) = fVar1;
          psVar4[0x52] = 0;
          psVar4[0x53] = 0;
          psVar4[0x54] = 0;
          psVar4[0x55] = 1;
          *(float *)(psVar4 + 0x48) = fVar1;
          psVar4[0x72] = 0;
          psVar4[0x73] = 0;
          psVar4[0x74] = 0;
          psVar4[0x75] = 1;
          *(float *)(psVar4 + 0x68) = fVar1;
          psVar4[0x92] = 0;
          psVar4[0x93] = 0;
          psVar4[0x94] = 0;
          psVar4[0x95] = 1;
          *(float *)(psVar4 + 0x88) = fVar1;
          psVar4[0xb2] = 0;
          psVar4[0xb3] = 0;
          psVar4[0xb4] = 0;
          psVar4[0xb5] = 1;
          *(float *)(psVar4 + 0xa8) = fVar1;
          psVar4[0xd2] = 0;
          psVar4[0xd3] = 0;
          psVar4[0xd4] = 0;
          psVar4[0xd5] = 1;
          *(float *)(psVar4 + 200) = fVar1;
          psVar4[0xf2] = 0;
          psVar4[0xf3] = 0;
          psVar4[0xf4] = 0;
          psVar4[0xf5] = 1;
          *(float *)(psVar4 + 0xe8) = fVar1;
          psVar4 = psVar4 + 0x100;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar6 = uVar6 & 7;
        if (uVar6 == 0) {
          return 1;
        }
      }
      do {
        psVar4[0x12] = 0;
        psVar4[0x13] = 0;
        psVar4[0x14] = 0;
        psVar4[0x15] = 1;
        *(float *)(psVar4 + 8) = fVar1;
        psVar4 = psVar4 + 0x20;
        uVar6 = uVar6 - 1;
      } while (uVar6 != 0);
    }
    return 1;
  }
  return 0;
}

