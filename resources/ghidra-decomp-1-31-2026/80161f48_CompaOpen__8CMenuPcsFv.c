// Function: CompaOpen__8CMenuPcsFv
// Entry: 80161f48
// Size: 432 bytes

bool CompaOpen__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  short *psVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    CompaInit__8CMenuPcsFv(menuPcs);
  }
  iVar5 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar6 = (int)**(short **)&menuPcs->field_0x850;
  psVar4 = *(short **)&menuPcs->field_0x850 + 4;
  iVar7 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  iVar8 = iVar6;
  if (0 < iVar6) {
    do {
      dVar3 = DOUBLE_80333030;
      fVar1 = FLOAT_80332ff8;
      if (*(int *)(psVar4 + 0x12) <= iVar7) {
        if (iVar7 < *(int *)(psVar4 + 0x12) + *(int *)(psVar4 + 0x14)) {
          *(int *)(psVar4 + 0x10) = *(int *)(psVar4 + 0x10) + 1;
          dVar2 = DOUBLE_80333008;
          *(float *)(psVar4 + 8) =
               (float)((DOUBLE_80333008 /
                       ((double)CONCAT44(0x43300000,*(uint *)(psVar4 + 0x14) ^ 0x80000000) - dVar3))
                      * ((double)CONCAT44(0x43300000,*(uint *)(psVar4 + 0x10) ^ 0x80000000) - dVar3)
                      );
          if ((*(uint *)(psVar4 + 0x16) & 2) == 0) {
            fVar1 = (float)((dVar2 / ((double)CONCAT44(0x43300000,
                                                       *(uint *)(psVar4 + 0x14) ^ 0x80000000) -
                                     dVar3)) *
                           ((double)CONCAT44(0x43300000,*(uint *)(psVar4 + 0x10) ^ 0x80000000) -
                           dVar3));
            *(float *)(psVar4 + 0x18) =
                 (*(float *)(psVar4 + 0x1c) -
                 (float)((double)CONCAT44(0x43300000,(int)*psVar4 ^ 0x80000000) - dVar3)) * fVar1;
            *(float *)(psVar4 + 0x1a) =
                 (*(float *)(psVar4 + 0x1e) -
                 (float)((double)CONCAT44(0x43300000,(int)psVar4[1] ^ 0x80000000) - dVar3)) * fVar1;
          }
        }
        else {
          iVar5 = iVar5 + 1;
          *(float *)(psVar4 + 8) = FLOAT_80333000;
          *(float *)(psVar4 + 0x18) = fVar1;
          *(float *)(psVar4 + 0x1a) = fVar1;
        }
      }
      psVar4 = psVar4 + 0x20;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  return iVar6 == iVar5;
}

