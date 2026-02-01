// Function: LetterOpen__8CMenuPcsFv
// Entry: 80167844
// Size: 1016 bytes

bool LetterOpen__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  
  DAT_8032eeea = 1;
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
    fVar1 = FLOAT_803330f8;
    iVar4 = *(int *)&menuPcs->field_0x850 + 8;
    iVar8 = 8;
    do {
      *(float *)(iVar4 + 0x14) = fVar1;
      *(float *)(iVar4 + 0x54) = fVar1;
      *(float *)(iVar4 + 0x94) = fVar1;
      *(float *)(iVar4 + 0xd4) = fVar1;
      *(float *)(iVar4 + 0x114) = fVar1;
      *(float *)(iVar4 + 0x154) = fVar1;
      *(float *)(iVar4 + 0x194) = fVar1;
      *(float *)(iVar4 + 0x1d4) = fVar1;
      iVar4 = iVar4 + 0x200;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    iVar4 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar4 + 0x24) = 0;
    *(undefined4 *)(iVar4 + 0x2c) = 0;
    *(undefined4 *)(iVar4 + 0x30) = 10;
    iVar4 = *(int *)&menuPcs->field_0x850;
    *(undefined4 *)(iVar4 + 100) = 0;
    *(uint *)(iVar4 + 0x6c) =
         ~((-(int)(char)menuPcs->field_0x872 | (int)(char)menuPcs->field_0x872) >> 0x1f) & 10;
    *(undefined4 *)(iVar4 + 0x70) = 10;
    **(undefined2 **)&menuPcs->field_0x850 = 2;
    *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
    iVar4 = SingGetLetterAttachflg__8CMenuPcsFv(menuPcs);
    if (iVar4 < 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x34) = 0;
      DAT_8032eef0 = 0;
      DAT_8032eef4 = 0;
      DAT_8032eeed = 2;
      DAT_8032eee8 = 0;
    }
    else {
      memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
      fVar1 = FLOAT_803330f8;
      iVar4 = *(int *)&menuPcs->field_0x850 + 8;
      iVar8 = 8;
      do {
        *(float *)(iVar4 + 0x14) = fVar1;
        *(float *)(iVar4 + 0x54) = fVar1;
        *(float *)(iVar4 + 0x94) = fVar1;
        *(float *)(iVar4 + 0xd4) = fVar1;
        *(float *)(iVar4 + 0x114) = fVar1;
        *(float *)(iVar4 + 0x154) = fVar1;
        *(float *)(iVar4 + 0x194) = fVar1;
        *(float *)(iVar4 + 0x1d4) = fVar1;
        iVar4 = iVar4 + 0x200;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      iVar4 = *(int *)&menuPcs->field_0x850;
      *(undefined4 *)(iVar4 + 0x24) = 0;
      *(undefined4 *)(iVar4 + 0x2c) = 0;
      *(undefined4 *)(iVar4 + 0x30) = 10;
      **(undefined2 **)&menuPcs->field_0x850 = 1;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x26) = DAT_8032eef8._2_2_;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x28) = uRam8032eefc._2_2_;
      *(short *)(*(int *)&menuPcs->field_0x82c + 0x34) = DAT_8032ef00._2_2_;
      DAT_8032eee8 = DAT_8032eef8._2_2_ + DAT_8032ef00._2_2_;
    }
    DAT_8032eef8 = 0;
    uRam8032eefc = 0;
    DAT_8032ef00 = 0;
    SetSingWinScl__8CMenuPcsFf((double)FLOAT_803330f8,menuPcs);
  }
  iVar6 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar5 = (int)**(short **)&menuPcs->field_0x850;
  psVar7 = *(short **)&menuPcs->field_0x850 + 4;
  iVar8 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  iVar4 = iVar5;
  if (0 < iVar5) {
    do {
      dVar2 = DOUBLE_803330c8;
      fVar1 = FLOAT_803330bc;
      if (*(int *)(psVar7 + 0x12) <= iVar8) {
        if (iVar8 < *(int *)(psVar7 + 0x12) + *(int *)(psVar7 + 0x14)) {
          *(int *)(psVar7 + 0x10) = *(int *)(psVar7 + 0x10) + 1;
          dVar3 = DOUBLE_803330e8;
          *(float *)(psVar7 + 8) =
               (float)((DOUBLE_803330e8 /
                       (double)(float)((double)CONCAT44(0x43300000,
                                                        *(uint *)(psVar7 + 0x14) ^ 0x80000000) -
                                      dVar2)) *
                      (double)(float)((double)CONCAT44(0x43300000,
                                                       *(uint *)(psVar7 + 0x10) ^ 0x80000000) -
                                     dVar2));
          if ((*(uint *)(psVar7 + 0x16) & 2) == 0) {
            fVar1 = (float)((dVar3 / (double)(float)((double)CONCAT44(0x43300000,
                                                                      *(uint *)(psVar7 + 0x14) ^
                                                                      0x80000000) - dVar2)) *
                           (double)(float)((double)CONCAT44(0x43300000,
                                                            *(uint *)(psVar7 + 0x10) ^ 0x80000000) -
                                          dVar2));
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
          *(float *)(psVar7 + 8) = FLOAT_803330f8;
          *(float *)(psVar7 + 0x18) = fVar1;
          *(float *)(psVar7 + 0x1a) = fVar1;
        }
      }
      psVar7 = psVar7 + 0x20;
      iVar4 = iVar4 + -1;
    } while (iVar4 != 0);
  }
  if (iVar5 == iVar6) {
    iVar4 = SingGetLetterAttachflg__8CMenuPcsFv(menuPcs);
    if (iVar4 < 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 1;
    }
    else {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x12) = 0;
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x30) = 1;
      LetterInit1__8CMenuPcsFv(menuPcs);
    }
  }
  return iVar5 == iVar6;
}

