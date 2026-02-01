// Function: EquipClose0__8CMenuPcsFv
// Entry: 8015b264
// Size: 516 bytes

bool EquipClose0__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  undefined2 *puVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  int iVar9;
  undefined8 local_18;
  
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  iVar7 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x40 + 8;
  if (7 < iVar4) {
    *(short *)(*(int *)&menuPcs->field_0x850 + iVar7) =
         *(short *)(*(int *)&menuPcs->field_0x850 + iVar7) + 0x13;
  }
  psVar8 = *(short **)&menuPcs->field_0x850;
  iVar6 = 0;
  iVar9 = (int)psVar8[1] - (int)*psVar8;
  psVar8 = psVar8 + *psVar8 * 0x20 + 4;
  iVar7 = iVar9;
  if (0 < iVar9) {
    do {
      dVar3 = DOUBLE_80332ed8;
      fVar1 = FLOAT_80332eb8;
      if (*(int *)(psVar8 + 0x12) <= iVar4) {
        if (iVar4 < *(int *)(psVar8 + 0x12) + *(int *)(psVar8 + 0x14)) {
          *(int *)(psVar8 + 0x10) = *(int *)(psVar8 + 0x10) + 1;
          dVar2 = DOUBLE_80332ec0;
          *(float *)(psVar8 + 8) =
               (float)-((DOUBLE_80332ec0 /
                        ((double)CONCAT44(0x43300000,*(uint *)(psVar8 + 0x14) ^ 0x80000000) - dVar3)
                        ) * ((double)CONCAT44(0x43300000,*(uint *)(psVar8 + 0x10) ^ 0x80000000) -
                            dVar3) - DOUBLE_80332ec0);
          if ((*(uint *)(psVar8 + 0x16) & 2) == 0) {
            local_18 = (double)CONCAT44(0x43300000,(int)psVar8[1] ^ 0x80000000);
            fVar1 = (float)-((dVar2 / ((double)CONCAT44(0x43300000,
                                                        *(uint *)(psVar8 + 0x14) ^ 0x80000000) -
                                      dVar3)) *
                             ((double)CONCAT44(0x43300000,*(uint *)(psVar8 + 0x10) ^ 0x80000000) -
                             dVar3) - dVar2);
            *(float *)(psVar8 + 0x18) =
                 (*(float *)(psVar8 + 0x1c) -
                 (float)((double)CONCAT44(0x43300000,(int)*psVar8 ^ 0x80000000) - dVar3)) * fVar1;
            *(float *)(psVar8 + 0x1a) =
                 (*(float *)(psVar8 + 0x1e) - (float)(local_18 - dVar3)) * fVar1;
          }
        }
        else {
          iVar6 = iVar6 + 1;
          *(float *)(psVar8 + 8) = FLOAT_80332eb8;
          *(float *)(psVar8 + 0x18) = fVar1;
          *(float *)(psVar8 + 0x1a) = fVar1;
        }
      }
      psVar8 = psVar8 + 0x20;
      iVar7 = iVar7 + -1;
    } while (iVar7 != 0);
  }
  if (iVar9 == iVar6) {
    puVar5 = (undefined2 *)
             (*(int *)&menuPcs->field_0x850 +
             *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x40 + 8);
    *puVar5 = (short)(int)-(((double)CONCAT44(0x43300000,(int)(short)puVar5[2] ^ 0x80000000) -
                            DOUBLE_80332ed8) * DOUBLE_80332ed0 - DOUBLE_80332ec8);
  }
  return iVar9 == iVar6;
}

