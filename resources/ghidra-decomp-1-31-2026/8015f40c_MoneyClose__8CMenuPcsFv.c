// Function: MoneyClose__8CMenuPcsFv
// Entry: 8015f40c
// Size: 380 bytes

bool MoneyClose__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  iVar4 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar6 = (int)**(short **)&menuPcs->field_0x850;
  psVar5 = *(short **)&menuPcs->field_0x850 + 4;
  iVar7 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  iVar8 = iVar6;
  if (0 < iVar6) {
    do {
      dVar2 = DOUBLE_80332f88;
      fVar1 = FLOAT_80332f64;
      if (*(int *)(psVar5 + 0x12) <= iVar7) {
        if (iVar7 < *(int *)(psVar5 + 0x12) + *(int *)(psVar5 + 0x14)) {
          *(int *)(psVar5 + 0x10) = *(int *)(psVar5 + 0x10) + 1;
          dVar3 = DOUBLE_80332f90;
          *(float *)(psVar5 + 8) =
               (float)-((DOUBLE_80332f90 /
                        ((double)CONCAT44(0x43300000,*(uint *)(psVar5 + 0x14) ^ 0x80000000) - dVar2)
                        ) * ((double)CONCAT44(0x43300000,*(uint *)(psVar5 + 0x10) ^ 0x80000000) -
                            dVar2) - DOUBLE_80332f90);
          if ((*(uint *)(psVar5 + 0x16) & 2) == 0) {
            fVar1 = (float)-((dVar3 / ((double)CONCAT44(0x43300000,
                                                        *(uint *)(psVar5 + 0x14) ^ 0x80000000) -
                                      dVar2)) *
                             ((double)CONCAT44(0x43300000,*(uint *)(psVar5 + 0x10) ^ 0x80000000) -
                             dVar2) - dVar3);
            *(float *)(psVar5 + 0x18) =
                 (*(float *)(psVar5 + 0x1c) -
                 (float)((double)CONCAT44(0x43300000,(int)*psVar5 ^ 0x80000000) - dVar2)) * fVar1;
            *(float *)(psVar5 + 0x1a) =
                 (*(float *)(psVar5 + 0x1e) -
                 (float)((double)CONCAT44(0x43300000,(int)psVar5[1] ^ 0x80000000) - dVar2)) * fVar1;
          }
        }
        else {
          iVar4 = iVar4 + 1;
          *(float *)(psVar5 + 8) = FLOAT_80332f64;
          *(float *)(psVar5 + 0x18) = fVar1;
          *(float *)(psVar5 + 0x1a) = fVar1;
        }
      }
      psVar5 = psVar5 + 0x20;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  return iVar6 == iVar4;
}

