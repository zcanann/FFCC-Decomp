// Function: CmdOpen0__8CMenuPcsFv
// Entry: 8014d0c4
// Size: 432 bytes

bool CmdOpen0__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  iVar6 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x40 + 8;
  if (iVar4 < 5) {
    *(short *)(*(int *)&menuPcs->field_0x850 + iVar6) =
         *(short *)(*(int *)&menuPcs->field_0x850 + iVar6) + -0x13;
  }
  psVar5 = *(short **)&menuPcs->field_0x850;
  iVar7 = 0;
  iVar8 = (int)psVar5[1] - (int)*psVar5;
  psVar5 = psVar5 + *psVar5 * 0x20 + 4;
  iVar6 = iVar8;
  if (0 < iVar8) {
    do {
      fVar1 = FLOAT_80332ab0;
      dVar3 = DOUBLE_80332a80;
      if (*(int *)(psVar5 + 0x12) <= iVar4) {
        if (iVar4 < *(int *)(psVar5 + 0x12) + *(int *)(psVar5 + 0x14)) {
          *(int *)(psVar5 + 0x10) = *(int *)(psVar5 + 0x10) + 1;
          dVar2 = DOUBLE_80332a58;
          *(float *)(psVar5 + 8) =
               (float)((DOUBLE_80332a58 /
                       ((double)CONCAT44(0x43300000,*(uint *)(psVar5 + 0x14) ^ 0x80000000) - dVar3))
                      * ((double)CONCAT44(0x43300000,*(uint *)(psVar5 + 0x10) ^ 0x80000000) - dVar3)
                      );
          if ((*(uint *)(psVar5 + 0x16) & 2) == 0) {
            fVar1 = (float)((dVar2 / ((double)CONCAT44(0x43300000,
                                                       *(uint *)(psVar5 + 0x14) ^ 0x80000000) -
                                     dVar3)) *
                           ((double)CONCAT44(0x43300000,*(uint *)(psVar5 + 0x10) ^ 0x80000000) -
                           dVar3));
            *(float *)(psVar5 + 0x18) =
                 (*(float *)(psVar5 + 0x1c) -
                 (float)((double)CONCAT44(0x43300000,(int)*psVar5 ^ 0x80000000) - dVar3)) * fVar1;
            *(float *)(psVar5 + 0x1a) =
                 (*(float *)(psVar5 + 0x1e) -
                 (float)((double)CONCAT44(0x43300000,(int)psVar5[1] ^ 0x80000000) - dVar3)) * fVar1;
          }
        }
        else {
          iVar7 = iVar7 + 1;
          *(float *)(psVar5 + 8) = FLOAT_80332a70;
          *(float *)(psVar5 + 0x18) = fVar1;
          *(float *)(psVar5 + 0x1a) = fVar1;
        }
      }
      psVar5 = psVar5 + 0x20;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  return iVar8 == iVar7;
}

