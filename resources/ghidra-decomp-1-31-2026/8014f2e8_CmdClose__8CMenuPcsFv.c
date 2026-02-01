// Function: CmdClose__8CMenuPcsFv
// Entry: 8014f2e8
// Size: 512 bytes

undefined4 CmdClose__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  double dVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  
  iVar4 = *(int *)&menuPcs->field_0x82c;
  if (*(char *)(iVar4 + 8) == '\0') {
    iVar4 = UniteCloseAnim__8CMenuPcsFi(menuPcs,0xffffffff);
    if (iVar4 != 0) {
      *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
      *(undefined *)(*(int *)&menuPcs->field_0x82c + 8) = 1;
    }
    return 0;
  }
  iVar6 = 0;
  *(short *)(iVar4 + 0x22) = *(short *)(iVar4 + 0x22) + 1;
  uVar7 = (uint)**(short **)&menuPcs->field_0x850;
  psVar5 = *(short **)&menuPcs->field_0x850 + 4;
  iVar4 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  uVar8 = uVar7;
  if (0 < (int)uVar7) {
    do {
      dVar1 = DOUBLE_80332a80;
      if (*(int *)(psVar5 + 0x12) <= iVar4) {
        if (iVar4 < *(int *)(psVar5 + 0x12) + *(int *)(psVar5 + 0x14)) {
          *(int *)(psVar5 + 0x10) = *(int *)(psVar5 + 0x10) + 1;
          dVar3 = DOUBLE_80332b30;
          *(float *)(psVar5 + 8) =
               (float)-((DOUBLE_80332a58 /
                        ((double)CONCAT44(0x43300000,*(uint *)(psVar5 + 0x14) ^ 0x80000000) - dVar1)
                        ) * ((double)CONCAT44(0x43300000,*(uint *)(psVar5 + 0x10) ^ 0x80000000) -
                            dVar1) - DOUBLE_80332a58);
          if ((double)*(float *)(psVar5 + 8) < dVar3) {
            *(float *)(psVar5 + 8) = FLOAT_80332ab0;
          }
        }
        else {
          iVar6 = iVar6 + 1;
          *(float *)(psVar5 + 8) = FLOAT_80332ab0;
        }
      }
      psVar5 = psVar5 + 0x20;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  fVar2 = FLOAT_80332ab0;
  if (**(short **)&menuPcs->field_0x850 == iVar6) {
    psVar5 = *(short **)&menuPcs->field_0x850 + 4;
    if (0 < (int)uVar7) {
      uVar8 = uVar7 >> 3;
      if (uVar8 != 0) {
        do {
          psVar5[0x12] = 0;
          psVar5[0x13] = 0;
          psVar5[0x14] = 0;
          psVar5[0x15] = 1;
          *(float *)(psVar5 + 8) = fVar2;
          psVar5[0x32] = 0;
          psVar5[0x33] = 0;
          psVar5[0x34] = 0;
          psVar5[0x35] = 1;
          *(float *)(psVar5 + 0x28) = fVar2;
          psVar5[0x52] = 0;
          psVar5[0x53] = 0;
          psVar5[0x54] = 0;
          psVar5[0x55] = 1;
          *(float *)(psVar5 + 0x48) = fVar2;
          psVar5[0x72] = 0;
          psVar5[0x73] = 0;
          psVar5[0x74] = 0;
          psVar5[0x75] = 1;
          *(float *)(psVar5 + 0x68) = fVar2;
          psVar5[0x92] = 0;
          psVar5[0x93] = 0;
          psVar5[0x94] = 0;
          psVar5[0x95] = 1;
          *(float *)(psVar5 + 0x88) = fVar2;
          psVar5[0xb2] = 0;
          psVar5[0xb3] = 0;
          psVar5[0xb4] = 0;
          psVar5[0xb5] = 1;
          *(float *)(psVar5 + 0xa8) = fVar2;
          psVar5[0xd2] = 0;
          psVar5[0xd3] = 0;
          psVar5[0xd4] = 0;
          psVar5[0xd5] = 1;
          *(float *)(psVar5 + 200) = fVar2;
          psVar5[0xf2] = 0;
          psVar5[0xf3] = 0;
          psVar5[0xf4] = 0;
          psVar5[0xf5] = 1;
          *(float *)(psVar5 + 0xe8) = fVar2;
          psVar5 = psVar5 + 0x100;
          uVar8 = uVar8 - 1;
        } while (uVar8 != 0);
        uVar7 = uVar7 & 7;
        if (uVar7 == 0) {
          return 1;
        }
      }
      do {
        psVar5[0x12] = 0;
        psVar5[0x13] = 0;
        psVar5[0x14] = 0;
        psVar5[0x15] = 1;
        *(float *)(psVar5 + 8) = fVar2;
        psVar5 = psVar5 + 0x20;
        uVar7 = uVar7 - 1;
      } while (uVar7 != 0);
    }
    return 1;
  }
  return 0;
}

