// Function: CmdClose0__8CMenuPcsFv
// Entry: 8014cef8
// Size: 460 bytes

bool CmdClose0__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  iVar6 = *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x40 + 8;
  if (7 < iVar4) {
    *(short *)(*(int *)&menuPcs->field_0x850 + iVar6) =
         *(short *)(*(int *)&menuPcs->field_0x850 + iVar6) + 0x13;
  }
  psVar7 = *(short **)&menuPcs->field_0x850;
  iVar5 = 0;
  iVar8 = (int)psVar7[1] - (int)*psVar7;
  psVar7 = psVar7 + *psVar7 * 0x20 + 4;
  iVar6 = iVar8;
  if (0 < iVar8) {
    do {
      fVar1 = FLOAT_80332ab0;
      dVar3 = DOUBLE_80332a80;
      if (*(int *)(psVar7 + 0x12) <= iVar4) {
        if (iVar4 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
          *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
          dVar2 = DOUBLE_80332a58;
          *(float *)(psVar7 + 8) =
               (float)-((DOUBLE_80332a58 /
                        ((double)CONCAT44(0x43300000,*(uint *)(psVar7 + 0x14) ^ 0x80000000) - dVar3)
                        ) * ((double)CONCAT44(0x43300000,*(uint *)(psVar7 + 0x10) ^ 0x80000000) -
                            dVar3) - DOUBLE_80332a58);
          if ((*(uint *)(psVar7 + 0x16) & 2) == 0) {
            fVar1 = (float)-((dVar2 / ((double)CONCAT44(0x43300000,
                                                        *(uint *)(psVar7 + 0x14) ^ 0x80000000) -
                                      dVar3)) *
                             ((double)CONCAT44(0x43300000,*(uint *)(psVar7 + 0x10) ^ 0x80000000) -
                             dVar3) - dVar2);
            *(float *)(psVar7 + 0x18) =
                 (*(float *)(psVar7 + 0x1c) -
                 (float)((double)CONCAT44(0x43300000,(int)*psVar7 ^ 0x80000000) - dVar3)) * fVar1;
            *(float *)(psVar7 + 0x1a) =
                 (*(float *)(psVar7 + 0x1e) -
                 (float)((double)CONCAT44(0x43300000,(int)psVar7[1] ^ 0x80000000) - dVar3)) * fVar1;
          }
        }
        else {
          iVar5 = iVar5 + 1;
          *(float *)(psVar7 + 8) = FLOAT_80332ab0;
          *(float *)(psVar7 + 0x18) = fVar1;
          *(float *)(psVar7 + 0x1a) = fVar1;
        }
      }
      psVar7 = psVar7 + 0x20;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
  }
  if (iVar8 == iVar5) {
    *(undefined2 *)
     (*(int *)&menuPcs->field_0x850 + *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) * 0x40 + 8) =
         *(undefined2 *)(*(int *)&menuPcs->field_0x850 + 8);
  }
  return iVar8 == iVar5;
}

