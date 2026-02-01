// Function: LetterClose__8CMenuPcsFv
// Entry: 80166490
// Size: 488 bytes

bool LetterClose__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  
  iVar6 = 0;
  DAT_8032eeea = 1;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar5 = (int)**(short **)&menuPcs->field_0x850;
  psVar7 = *(short **)&menuPcs->field_0x850 + 4;
  iVar4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  iVar8 = iVar5;
  if (0 < iVar5) {
    do {
      dVar2 = DOUBLE_803330c8;
      fVar1 = FLOAT_803330bc;
      if (*(int *)(psVar7 + 0x12) <= iVar4) {
        if (iVar4 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
          *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
          dVar3 = DOUBLE_803330e8;
          *(float *)(psVar7 + 8) =
               (float)-((DOUBLE_803330e8 /
                        (double)(float)((double)CONCAT44(0x43300000,
                                                         *(uint *)(psVar7 + 0x14) ^ 0x80000000) -
                                       dVar2)) *
                        (double)(float)((double)CONCAT44(0x43300000,
                                                         *(uint *)(psVar7 + 0x10) ^ 0x80000000) -
                                       dVar2) - DOUBLE_803330e8);
          if ((*(uint *)(psVar7 + 0x16) & 2) == 0) {
            fVar1 = (float)-((dVar3 / (double)(float)((double)CONCAT44(0x43300000,
                                                                       *(uint *)(psVar7 + 0x14) ^
                                                                       0x80000000) - dVar2)) *
                             (double)(float)((double)CONCAT44(0x43300000,
                                                              *(uint *)(psVar7 + 0x10) ^ 0x80000000)
                                            - dVar2) - dVar3);
            *(float *)(psVar7 + 0x18) =
                 (*(float *)(psVar7 + 0x1c) -
                 (float)((double)CONCAT44(0x43300000,(int)*psVar7 ^ 0x80000000) - dVar2)) * fVar1;
            *(float *)(psVar7 + 0x1a) =
                 (*(float *)(psVar7 + 0x1e) -
                 (float)((double)CONCAT44(0x43300000,(int)psVar7[1] ^ 0x80000000) - dVar2)) * fVar1;
          }
        }
        else {
          iVar6 = iVar6 + 1;
          *(float *)(psVar7 + 8) = FLOAT_803330bc;
          *(float *)(psVar7 + 0x18) = fVar1;
          *(float *)(psVar7 + 0x1a) = fVar1;
        }
      }
      psVar7 = psVar7 + 0x20;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  if ((iVar5 == iVar6) && (iVar8 = SingGetLetterAttachflg__8CMenuPcsFv(menuPcs), -1 < iVar8)) {
    DAT_8032eef8 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x26);
    DAT_8032ef00 = DAT_8032eee8 - DAT_8032eef8;
    iRam8032eefc = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x28);
  }
  return iVar5 == iVar6;
}

