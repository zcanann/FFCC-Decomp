// Function: CmdOpen__8CMenuPcsFv
// Entry: 8014fa78
// Size: 472 bytes

void CmdOpen__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  bool bVar1;
  float fVar2;
  double dVar3;
  short *psVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    CmdInit__8CMenuPcsFv();
  }
  iVar5 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  uVar6 = (uint)**(short **)&menuPcs->field_0x850;
  psVar4 = *(short **)&menuPcs->field_0x850 + 4;
  iVar7 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  uVar8 = uVar6;
  if (0 < (int)uVar6) {
    do {
      dVar3 = DOUBLE_80332a80;
      if (*(int *)(psVar4 + 0x12) <= iVar7) {
        if (iVar7 < *(int *)(psVar4 + 0x12) + *(int *)(psVar4 + 0x14)) {
          *(int *)(psVar4 + 0x10) = *(int *)(psVar4 + 0x10) + 1;
          *(float *)(psVar4 + 8) =
               (float)((DOUBLE_80332a58 /
                       ((double)CONCAT44(0x43300000,*(uint *)(psVar4 + 0x14) ^ 0x80000000) - dVar3))
                      * ((double)CONCAT44(0x43300000,*(uint *)(psVar4 + 0x10) ^ 0x80000000) - dVar3)
                      );
        }
        else {
          iVar5 = iVar5 + 1;
          *(float *)(psVar4 + 8) = FLOAT_80332a70;
        }
      }
      psVar4 = psVar4 + 0x20;
      uVar8 = uVar8 - 1;
    } while (uVar8 != 0);
  }
  fVar2 = FLOAT_80332a70;
  bVar1 = false;
  if (**(short **)&menuPcs->field_0x850 != iVar5) goto LAB_8014fc28;
  psVar4 = *(short **)&menuPcs->field_0x850 + 4;
  if (0 < (int)uVar6) {
    uVar8 = uVar6 >> 3;
    if (uVar8 != 0) {
      do {
        psVar4[0x12] = 0;
        psVar4[0x13] = 0;
        psVar4[0x14] = 0;
        psVar4[0x15] = 1;
        *(float *)(psVar4 + 8) = fVar2;
        psVar4[0x32] = 0;
        psVar4[0x33] = 0;
        psVar4[0x34] = 0;
        psVar4[0x35] = 1;
        *(float *)(psVar4 + 0x28) = fVar2;
        psVar4[0x52] = 0;
        psVar4[0x53] = 0;
        psVar4[0x54] = 0;
        psVar4[0x55] = 1;
        *(float *)(psVar4 + 0x48) = fVar2;
        psVar4[0x72] = 0;
        psVar4[0x73] = 0;
        psVar4[0x74] = 0;
        psVar4[0x75] = 1;
        *(float *)(psVar4 + 0x68) = fVar2;
        psVar4[0x92] = 0;
        psVar4[0x93] = 0;
        psVar4[0x94] = 0;
        psVar4[0x95] = 1;
        *(float *)(psVar4 + 0x88) = fVar2;
        psVar4[0xb2] = 0;
        psVar4[0xb3] = 0;
        psVar4[0xb4] = 0;
        psVar4[0xb5] = 1;
        *(float *)(psVar4 + 0xa8) = fVar2;
        psVar4[0xd2] = 0;
        psVar4[0xd3] = 0;
        psVar4[0xd4] = 0;
        psVar4[0xd5] = 1;
        *(float *)(psVar4 + 200) = fVar2;
        psVar4[0xf2] = 0;
        psVar4[0xf3] = 0;
        psVar4[0xf4] = 0;
        psVar4[0xf5] = 1;
        *(float *)(psVar4 + 0xe8) = fVar2;
        psVar4 = psVar4 + 0x100;
        uVar8 = uVar8 - 1;
      } while (uVar8 != 0);
      uVar6 = uVar6 & 7;
      if (uVar6 == 0) goto LAB_8014fc24;
    }
    do {
      psVar4[0x12] = 0;
      psVar4[0x13] = 0;
      psVar4[0x14] = 0;
      psVar4[0x15] = 1;
      *(float *)(psVar4 + 8) = fVar2;
      psVar4 = psVar4 + 0x20;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
LAB_8014fc24:
  bVar1 = true;
LAB_8014fc28:
  if (bVar1) {
    UniteOpenAnim__8CMenuPcsFi(menuPcs,0xffffffff);
  }
  return;
}

