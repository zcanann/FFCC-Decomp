// Function: CalcSelectOpenAnim__8CMenuPcsFv
// Entry: 80135d60
// Size: 4668 bytes

/* WARNING: Removing unreachable block (ram,0x80136f80) */
/* WARNING: Removing unreachable block (ram,0x80135d70) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void CalcSelectOpenAnim__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  bool bVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float fVar12;
  int iVar13;
  short sVar14;
  int *piVar15;
  int iVar16;
  short sVar17;
  uint uVar18;
  int iVar19;
  short *psVar20;
  int iVar21;
  int iVar22;
  undefined2 *puVar23;
  short *psVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  uint uVar31;
  int iVar32;
  uint unaff_r21;
  int iVar33;
  int iVar34;
  int iVar35;
  float *pfVar36;
  int iVar37;
  int iVar38;
  double dVar39;
  Vec local_188;
  Vec local_17c;
  Mtx MStack_170;
  Mtx MStack_140;
  Mtx MStack_110;
  Mtx MStack_e0;
  double local_b0;
  double local_a8;
  undefined8 local_a0;
  undefined4 local_98;
  uint uStack_94;
  undefined4 local_90;
  uint uStack_8c;
  undefined8 local_88;
  undefined4 local_80;
  uint uStack_7c;
  undefined8 local_78;
  undefined8 local_70;
  undefined8 local_68;
  undefined4 local_60;
  uint uStack_5c;
  
  iVar37 = *DAT_8032eea8;
  if (*(char *)(*(int *)&menuPcs->field_0x82c + 0xb) == '\0') {
    menuPcs->field_0x8d = 0;
    PlaySe__6CSoundFiiii(&Sound,0x4c,0x40,0x7f,0);
    memset(*(undefined4 *)&menuPcs->field_0x84c,0,0x1008);
    iVar13 = *(int *)&menuPcs->field_0x84c;
    *(undefined4 *)(iVar13 + 0x24) = 0x16;
    *(undefined2 *)(iVar13 + 10) = 0;
    *(undefined2 *)(iVar13 + 8) = 0;
    fVar1 = FLOAT_80331eac;
    *(undefined2 *)(iVar13 + 0xc) = 0x280;
    fVar7 = FLOAT_80331eb0;
    *(undefined2 *)(iVar13 + 0xe) = 0x1c0;
    *(float *)(iVar13 + 0x14) = fVar1;
    *(float *)(iVar13 + 0x10) = fVar1;
    *(undefined4 *)(iVar13 + 0x2c) = 0;
    fVar5 = FLOAT_80331f5c;
    *(undefined4 *)(iVar13 + 0x30) = 0;
    *(float *)(iVar13 + 0x1c) = fVar7;
    dVar39 = DOUBLE_80331e88;
    *(undefined4 *)(iVar13 + 0x34) = 3;
    fVar6 = FLOAT_80331f60;
    sVar14 = 0x28;
    iVar13 = *(int *)&menuPcs->field_0x84c;
    *(undefined4 *)(iVar13 + 100) = 0xfffffffd;
    *(undefined2 *)(iVar13 + 0x48) = 0xf0;
    *(undefined2 *)(iVar13 + 0x4a) = 0x38;
    *(undefined2 *)(iVar13 + 0x4c) = 0x168;
    *(undefined2 *)(iVar13 + 0x4e) = 0x148;
    *(float *)(iVar13 + 0x54) = fVar1;
    *(float *)(iVar13 + 0x50) = fVar1;
    *(undefined4 *)(iVar13 + 0x6c) = 0;
    *(undefined4 *)(iVar13 + 0x70) = 8;
    *(float *)(iVar13 + 0x5c) = fVar7;
    iVar13 = *(int *)&menuPcs->field_0x84c;
    *(undefined4 *)(iVar13 + 0xa4) = 0x1f;
    *(undefined2 *)(iVar13 + 0x88) = 0;
    *(undefined2 *)(iVar13 + 0x8a) = 0;
    *(undefined2 *)(iVar13 + 0x8c) = 0x80;
    *(undefined2 *)(iVar13 + 0x8e) = 0x78;
    *(float *)(iVar13 + 0x94) = fVar1;
    *(float *)(iVar13 + 0x90) = fVar1;
    *(undefined4 *)(iVar13 + 0xac) = 9999;
    *(undefined4 *)(iVar13 + 0xb0) = 8;
    *(float *)(iVar13 + 0x9c) = fVar7;
    *(float *)(iVar13 + 0xb8) = fVar5;
    *(float *)(iVar13 + 0xbc) = fVar5;
    *(undefined4 *)(iVar13 + 0xb4) = 2;
    iVar13 = *(int *)&menuPcs->field_0x84c;
    *(undefined4 *)(iVar13 + 0xe4) = 0xfffffffc;
    *(undefined2 *)(iVar13 + 200) = 0;
    *(undefined2 *)(iVar13 + 0xca) = 0;
    *(undefined2 *)(iVar13 + 0xcc) = 0x70;
    *(undefined2 *)(iVar13 + 0xce) = 0x68;
    *(float *)(iVar13 + 0xd4) = fVar1;
    *(float *)(iVar13 + 0xd0) = fVar1;
    *(undefined4 *)(iVar13 + 0xec) = 0;
    *(undefined4 *)(iVar13 + 0xf0) = 8;
    *(float *)(iVar13 + 0xdc) = fVar7;
    for (iVar13 = 0; fVar12 = FLOAT_80331f60, fVar8 = FLOAT_80331eb0, fVar5 = FLOAT_80331eac,
        dVar3 = DOUBLE_80331e88, iVar13 < iVar37; iVar13 = iVar13 + 1) {
      iVar33 = 0;
      piVar15 = DAT_8032eea8;
      iVar22 = iVar37;
      if (0 < iVar37) {
        do {
          if (iVar13 == piVar15[0xd]) {
            unaff_r21 = DAT_8032eea8[iVar33 * 0xb + 7];
            break;
          }
          piVar15 = piVar15 + 0xb;
          iVar33 = iVar33 + 1;
          iVar22 = iVar22 + -1;
        } while (iVar22 != 0);
      }
      psVar20 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar13 + 4) * 0x40 + 8);
      bVar2 = false;
      psVar20[0xe] = 0;
      psVar20[0xf] = 0x18;
      if ((0 < iVar13) && (iVar13 < 3)) {
        bVar2 = true;
      }
      sVar17 = 0x48;
      if (bVar2) {
        sVar17 = 0x30;
      }
      *psVar20 = sVar17;
      psVar20[1] = sVar14;
      psVar20[2] = 0x60;
      psVar20[3] = 0x58;
      if ((unaff_r21 & 1) == 0) {
        iVar22 = 0;
      }
      else {
        iVar22 = (int)psVar20[2];
      }
      local_b0 = (double)(CONCAT44(0x43300000,iVar22) ^ 0x80000000);
      *(float *)(psVar20 + 4) = (float)(local_b0 - dVar39);
      if ((int)unaff_r21 >> 1 == 0) {
        iVar22 = 0;
      }
      else {
        iVar22 = (int)psVar20[3];
      }
      local_a8 = (double)(CONCAT44(0x43300000,iVar22) ^ 0x80000000);
      sVar14 = sVar14 + 0x60;
      *(float *)(psVar20 + 6) = (float)(local_a8 - dVar39);
      psVar20[0x12] = 0;
      psVar20[0x13] = 0;
      psVar20[0x14] = 0;
      psVar20[0x15] = 8;
      *(float *)(psVar20 + 10) = fVar7;
      *(float *)(psVar20 + 0x18) = fVar6;
      *(float *)(psVar20 + 0x1a) = fVar1;
      local_a0 = (double)(CONCAT44(0x43300000,(int)*psVar20) ^ 0x80000000);
      *(float *)(psVar20 + 0x1c) = (float)(local_a0 - dVar39) + *(float *)(psVar20 + 0x18);
      *(float *)(psVar20 + 0x1e) =
           (float)((double)CONCAT44(0x43300000,(int)psVar20[1] ^ 0x80000000) - dVar39) +
           *(float *)(psVar20 + 0x1a);
      psVar20[0x16] = 0;
      psVar20[0x17] = 1;
    }
    iVar33 = iVar37 + 4;
    DAT_8032eeae = (char)iVar33;
    iVar22 = 0;
    iVar13 = iVar37;
    if (0 < iVar37) {
      do {
        psVar20 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar33 + iVar22) * 0x40 + 8);
        psVar20[0xe] = -1;
        psVar20[0xf] = -2;
        iVar22 = iVar22 + 1;
        *psVar20 = 0;
        psVar20[1] = 0;
        psVar20[2] = 0;
        psVar20[3] = 0;
        *(float *)(psVar20 + 4) = fVar5;
        *(float *)(psVar20 + 6) = fVar5;
        *(undefined4 *)(psVar20 + 0x12) = *(undefined4 *)(psVar20 + iVar37 * -0x20 + 0x12);
        psVar20[0x14] = 0;
        psVar20[0x15] = 8;
        *(float *)(psVar20 + 10) = fVar8;
        *(float *)(psVar20 + 0x18) = fVar12;
        *(float *)(psVar20 + 0x1a) = fVar5;
        *(float *)(psVar20 + 0x1c) =
             (float)((double)CONCAT44(0x43300000,(int)*psVar20 ^ 0x80000000) - dVar3) +
             *(float *)(psVar20 + 0x18);
        local_a0 = (double)(CONCAT44(0x43300000,(int)psVar20[1]) ^ 0x80000000);
        *(float *)(psVar20 + 0x1e) = (float)(local_a0 - dVar3) + *(float *)(psVar20 + 0x1a);
        psVar20[0x16] = 0;
        psVar20[0x17] = 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
    }
    fVar5 = FLOAT_80331f64;
    fVar7 = FLOAT_80331eb0;
    fVar1 = FLOAT_80331eac;
    dVar39 = DOUBLE_80331e88;
    iVar33 = iVar33 + iVar37;
    DAT_8032eead = (undefined)iVar33;
    iVar22 = 0;
    iVar13 = 10;
    iVar38 = 8;
    do {
      iVar16 = 0;
      puVar23 = (undefined2 *)(*(int *)&menuPcs->field_0x84c + (iVar33 + iVar22) * 0x40 + 8);
      *(undefined4 *)(puVar23 + 0xe) = 0xfffffffe;
      iVar22 = iVar22 + 1;
      *puVar23 = 0;
      puVar23[1] = 0;
      puVar23[2] = 0;
      puVar23[3] = 0;
      *(float *)(puVar23 + 4) = fVar1;
      *(float *)(puVar23 + 6) = fVar1;
      *(int *)(puVar23 + 0x12) = iVar13;
      iVar13 = iVar13 + 5;
      uStack_94 = *(uint *)(puVar23 + 0x12) ^ 0x80000000;
      iVar35 = (int)(fVar5 * (float)((double)CONCAT44(0x43300000,uStack_94) - dVar39));
      local_a0 = (double)(longlong)iVar35;
      *(int *)(puVar23 + 0x12) = iVar35;
      *(undefined4 *)(puVar23 + 0x14) = 0x21;
      *(float *)(puVar23 + 10) = fVar7;
      *(undefined4 *)(puVar23 + 0x16) = 1;
      fVar12 = FLOAT_80331f68;
      fVar8 = FLOAT_80331f60;
      fVar6 = FLOAT_80331eac;
      dVar3 = DOUBLE_80331e88;
      iVar38 = iVar38 + -1;
    } while (iVar38 != 0);
    iVar13 = iVar37;
    if (0 < iVar37) {
      do {
        psVar20 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar33 + 8 + iVar16) * 0x40 + 8);
        psVar24 = psVar20 + (iVar33 + 4) * -0x20;
        iVar16 = iVar16 + 1;
        *psVar20 = *psVar24;
        psVar20[1] = psVar24[1];
        psVar20[2] = psVar24[2];
        psVar20[3] = psVar24[3];
        *(undefined4 *)(psVar20 + 4) = *(undefined4 *)(psVar24 + 4);
        *(undefined4 *)(psVar20 + 6) = *(undefined4 *)(psVar24 + 6);
        *(undefined4 *)(psVar20 + 8) = *(undefined4 *)(psVar24 + 8);
        *(undefined4 *)(psVar20 + 10) = *(undefined4 *)(psVar24 + 10);
        *(undefined4 *)(psVar20 + 0xc) = *(undefined4 *)(psVar24 + 0xc);
        *(undefined4 *)(psVar20 + 0xe) = *(undefined4 *)(psVar24 + 0xe);
        *(undefined4 *)(psVar20 + 0x10) = *(undefined4 *)(psVar24 + 0x10);
        *(undefined4 *)(psVar20 + 0x12) = *(undefined4 *)(psVar24 + 0x12);
        *(undefined4 *)(psVar20 + 0x14) = *(undefined4 *)(psVar24 + 0x14);
        *(undefined4 *)(psVar20 + 0x16) = *(undefined4 *)(psVar24 + 0x16);
        *(undefined4 *)(psVar20 + 0x18) = *(undefined4 *)(psVar24 + 0x18);
        *(undefined4 *)(psVar20 + 0x1a) = *(undefined4 *)(psVar24 + 0x1a);
        *(undefined4 *)(psVar20 + 0x1c) = *(undefined4 *)(psVar24 + 0x1c);
        *(undefined4 *)(psVar20 + 0x1e) = *(undefined4 *)(psVar24 + 0x1e);
        psVar20[1] = psVar20[1] + 0x20;
        psVar20[2] = 0xa8;
        psVar20[3] = 0x38;
        *(float *)(psVar20 + 4) = fVar6;
        *(float *)(psVar20 + 6) = fVar12;
        *(float *)(psVar20 + 0x18) = fVar8;
        *(float *)(psVar20 + 0x1a) = fVar6;
        uStack_94 = (int)*psVar20 ^ 0x80000000;
        *(float *)(psVar20 + 0x1c) =
             (float)((double)CONCAT44(0x43300000,uStack_94) - dVar3) + *(float *)(psVar20 + 0x18);
        local_a0 = (double)(CONCAT44(0x43300000,(int)psVar20[1]) ^ 0x80000000);
        *(float *)(psVar20 + 0x1e) = (float)(local_a0 - dVar3) + *(float *)(psVar20 + 0x1a);
        psVar20[0x16] = 0;
        psVar20[0x17] = 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
    }
    fVar5 = FLOAT_80331f60;
    fVar7 = FLOAT_80331eb0;
    fVar1 = FLOAT_80331eac;
    dVar39 = DOUBLE_80331e88;
    iVar33 = iVar33 + 8 + iVar37;
    iVar22 = 0;
    sVar14 = 0x28;
    iVar13 = iVar37;
    if (0 < iVar37) {
      do {
        psVar20 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar33 + iVar22) * 0x40 + 8);
        bVar2 = false;
        psVar20[0xe] = 0;
        psVar20[0xf] = 0x19;
        if ((0 < iVar22) && (iVar22 < 3)) {
          bVar2 = true;
        }
        sVar17 = 0x20;
        if (bVar2) {
          sVar17 = 8;
        }
        *psVar20 = sVar17;
        psVar20[1] = sVar14;
        sVar14 = sVar14 + 0x60;
        psVar20[2] = 0x38;
        psVar20[3] = 0x28;
        uStack_94 = iVar22 * psVar20[2];
        iVar22 = iVar22 + 1;
        uStack_94 = uStack_94 ^ 0x80000000;
        *(float *)(psVar20 + 4) = (float)((double)CONCAT44(0x43300000,uStack_94) - dVar39);
        *(float *)(psVar20 + 6) = fVar1;
        psVar20[0x12] = 0;
        psVar20[0x13] = 0;
        psVar20[0x14] = 0;
        psVar20[0x15] = 8;
        *(float *)(psVar20 + 10) = fVar7;
        *(float *)(psVar20 + 0x18) = fVar5;
        *(float *)(psVar20 + 0x1a) = fVar1;
        local_a0 = (double)(CONCAT44(0x43300000,(int)*psVar20) ^ 0x80000000);
        *(float *)(psVar20 + 0x1c) = (float)(local_a0 - dVar39) + *(float *)(psVar20 + 0x18);
        local_a8 = (double)(CONCAT44(0x43300000,(int)psVar20[1]) ^ 0x80000000);
        *(float *)(psVar20 + 0x1e) = (float)(local_a8 - dVar39) + *(float *)(psVar20 + 0x1a);
        psVar20[0x16] = 0;
        psVar20[0x17] = 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
    }
    fVar5 = FLOAT_80331f60;
    fVar7 = FLOAT_80331eb0;
    fVar1 = FLOAT_80331eac;
    dVar39 = DOUBLE_80331e88;
    iVar33 = iVar33 + iVar37;
    iVar22 = 0;
    iVar13 = iVar37;
    if (0 < iVar37) {
      do {
        psVar24 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar33 + iVar22) * 0x40 + 8);
        psVar24[0xe] = -1;
        psVar24[0xf] = -1;
        psVar20 = psVar24 + (iVar33 + -4) * -0x20;
        iVar22 = iVar22 + 1;
        *psVar24 = *psVar20 + 0x50;
        psVar24[1] = psVar20[1] + 0x48;
        psVar24[2] = 0;
        psVar24[3] = 0;
        *(float *)(psVar24 + 4) = fVar1;
        *(float *)(psVar24 + 6) = fVar1;
        *(undefined4 *)(psVar24 + 0x12) = *(undefined4 *)(psVar20 + 0x12);
        psVar24[0x14] = 0;
        psVar24[0x15] = 8;
        *(float *)(psVar24 + 10) = fVar7;
        *(float *)(psVar24 + 0x18) = fVar5;
        *(float *)(psVar24 + 0x1a) = fVar1;
        uStack_94 = (int)*psVar24 ^ 0x80000000;
        *(float *)(psVar24 + 0x1c) =
             (float)((double)CONCAT44(0x43300000,uStack_94) - dVar39) + *(float *)(psVar24 + 0x18);
        local_a0 = (double)(CONCAT44(0x43300000,(int)psVar24[1]) ^ 0x80000000);
        *(float *)(psVar24 + 0x1e) = (float)(local_a0 - dVar39) + *(float *)(psVar24 + 0x1a);
        psVar24[0x16] = 0;
        psVar24[0x17] = 1;
        iVar13 = iVar13 + -1;
      } while (iVar13 != 0);
    }
    local_98 = 0x43300000;
    ArtiBaseInfoInit__8CMenuPcsFPQ28CMenuPcs5Sprt2PQ28CMenuPcs5Sprt2
              (menuPcs,*(int *)&menuPcs->field_0x84c + 0x48,*(int *)&menuPcs->field_0x84c + 200);
    fVar5 = FLOAT_80331f6c;
    dVar9 = DOUBLE_80331ef0;
    dVar4 = DOUBLE_80331ee8;
    fVar7 = FLOAT_80331eb0;
    fVar1 = FLOAT_80331eac;
    dVar3 = DOUBLE_80331e88;
    dVar39 = DOUBLE_80331e78;
    iVar22 = iVar37 * 0xa0;
    iVar13 = *(int *)&menuPcs->field_0x84c;
    iVar38 = 8;
    do {
      iVar35 = iVar22 + 4;
      pfVar36 = (float *)(*(int *)&menuPcs->field_0x814 + iVar22 + 0x1c);
      local_98 = 0x43300000;
      iVar34 = iVar22 + 8;
      iVar32 = iVar22 + 10;
      pfVar36[2] = fVar1;
      iVar30 = iVar22 + 0xc;
      iVar29 = iVar22 + 0xe;
      pfVar36[1] = fVar1;
      iVar28 = iVar22 + 0x10;
      iVar27 = iVar22 + 0x14;
      *pfVar36 = fVar1;
      iVar26 = iVar22 + 0x18;
      iVar25 = iVar22 + 0x40;
      iVar21 = iVar22 + 0x44;
      pfVar36[5] = fVar1;
      iVar19 = iVar22 + 0x48;
      iVar16 = iVar22 + 0x4c;
      pfVar36[4] = fVar1;
      pfVar36[3] = fVar1;
      pfVar36[8] = fVar7;
      pfVar36[7] = fVar7;
      pfVar36[6] = fVar7;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar22) = 0;
      iVar22 = iVar22 + 0x50;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar35) = 0;
      uStack_94 = (int)*(short *)(iVar13 + 0x4c) ^ 0x80000000;
      local_a0 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar13 + 0x48)) ^ 0x80000000);
      local_90 = 0x43300000;
      iVar35 = (int)((double)(float)(((double)CONCAT44(0x43300000,uStack_94) - dVar3) * dVar39 +
                                    (local_a0 - dVar3)) - dVar4);
      local_a8 = (double)(longlong)iVar35;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar34) = (short)iVar35;
      uStack_8c = (int)*(short *)(iVar13 + 0x4a) ^ 0x80000000;
      local_b0 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar13 + 0x4e)) ^ 0x80000000);
      iVar35 = (int)((double)(float)((local_b0 - dVar3) * dVar39 +
                                    ((double)CONCAT44(0x43300000,uStack_8c) - dVar3)) - dVar9);
      local_88 = (double)(longlong)iVar35;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar32) = (short)iVar35;
      *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar30) = 0x280;
      *(undefined2 *)(*(int *)&menuPcs->field_0x814 + iVar29) = 0x1c0;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar28) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar27) = fVar1;
      *(float *)(*(int *)&menuPcs->field_0x814 + iVar26) = fVar5;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar25) = 0;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar21) = 0;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar19) = 0x280;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar16) = 0x1c0;
      iVar38 = iVar38 + -1;
    } while (iVar38 != 0);
    **(short **)&menuPcs->field_0x84c = (short)iVar33 + (short)iVar37;
    *(undefined2 *)(*(int *)&menuPcs->field_0x84c + 6) = 0;
    *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  }
  iVar13 = 0;
  iVar33 = 0;
  *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) =
       *(short *)(*(int *)&menuPcs->field_0x82c + 0x22) + 1;
  iVar38 = (int)*(short *)(*(int *)&menuPcs->field_0x82c + 0x22);
  for (iVar22 = 0; fVar7 = FLOAT_80331efc, fVar1 = FLOAT_80331ef8, dVar11 = DOUBLE_80331ef0,
      dVar10 = DOUBLE_80331ee8, dVar9 = DOUBLE_80331ee0, dVar4 = DOUBLE_80331e90,
      dVar3 = DOUBLE_80331e88, dVar39 = DOUBLE_80331e78, iVar22 < **(short **)&menuPcs->field_0x84c;
      iVar22 = iVar22 + 1) {
    psVar20 = (short *)((int)*(short **)&menuPcs->field_0x84c + iVar13 + 8);
    if ((*(uint *)(psVar20 + 0x16) & 1) == 0) {
      if (iVar38 < *(int *)(psVar20 + 0x12)) {
        *(float *)(psVar20 + 8) = FLOAT_80331eac;
      }
      if (iVar38 < (int)(*(int *)(psVar20 + 0x12) + *(uint *)(psVar20 + 0x14))) {
        local_88 = (double)CONCAT44(0x43300000,*(uint *)(psVar20 + 0x14) ^ 0x80000000);
        uStack_8c = *(uint *)(psVar20 + 0x10) ^ 0x80000000;
        local_90 = 0x43300000;
        *(float *)(psVar20 + 8) =
             (float)((DOUBLE_80331ed8 / (local_88 - DOUBLE_80331e88)) *
                    ((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88));
      }
      else {
        *(float *)(psVar20 + 8) = FLOAT_80331eb0;
      }
    }
    else {
      *(float *)(psVar20 + 8) = FLOAT_80331eb0;
    }
    if (((int)(*(int *)(psVar20 + 0x12) + *(uint *)(psVar20 + 0x14)) <= iVar38) ||
       (0x270e < *(int *)(psVar20 + 0x12))) {
      iVar33 = iVar33 + 1;
    }
    if (((*(uint *)(psVar20 + 0x16) & 2) == 0) &&
       ((*(float *)(psVar20 + 0x18) != FLOAT_80331eac ||
        (*(float *)(psVar20 + 0x1a) != FLOAT_80331eac)))) {
      local_88 = (double)CONCAT44(0x43300000,*(uint *)(psVar20 + 0x14) ^ 0x80000000);
      uStack_8c = *(uint *)(psVar20 + 0x10) ^ 0x80000000;
      local_90 = 0x43300000;
      uStack_94 = (int)psVar20[1] ^ 0x80000000;
      local_a0 = (double)CONCAT44(0x43300000,(int)*psVar20 ^ 0x80000000);
      local_98 = 0x43300000;
      fVar1 = (float)-((DOUBLE_80331ed8 / (local_88 - DOUBLE_80331e88)) *
                       ((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80331e88) - DOUBLE_80331ed8)
      ;
      dVar39 = (double)CONCAT44(0x43300000,uStack_94) - DOUBLE_80331e88;
      *(float *)(psVar20 + 0x18) =
           (*(float *)(psVar20 + 0x1c) - (float)(local_a0 - DOUBLE_80331e88)) * fVar1;
      *(float *)(psVar20 + 0x1a) = (*(float *)(psVar20 + 0x1e) - (float)dVar39) * fVar1;
    }
    if ((*(int *)(psVar20 + 0x12) < iVar38) &&
       (iVar38 <= *(int *)(psVar20 + 0x12) + *(int *)(psVar20 + 0x14))) {
      *(int *)(psVar20 + 0x10) = *(int *)(psVar20 + 0x10) + 1;
    }
    iVar13 = iVar13 + 0x40;
  }
  iVar35 = 0;
  iVar22 = 0;
  iVar13 = iVar37;
  if (0 < iVar37) {
    do {
      local_90 = 0x43300000;
      psVar20 = (short *)(*(int *)&menuPcs->field_0x84c + (iVar35 + 4) * 0x40 + 8);
      uStack_8c = (int)*psVar20 ^ 0x80000000;
      iVar21 = iVar22 + 0x40;
      local_88 = (double)(CONCAT44(0x43300000,(int)psVar20[2]) ^ 0x80000000);
      uStack_94 = (int)psVar20[3] ^ 0x80000000;
      local_a0 = (double)CONCAT44(0x43300000,(int)psVar20[1] ^ 0x80000000);
      local_98 = 0x43300000;
      local_80 = 0x43300000;
      iVar16 = (int)((double)(float)(dVar9 + (local_88 - dVar3) * dVar39 +
                                             (double)((float)((double)CONCAT44(0x43300000,uStack_8c)
                                                             - dVar3) + *(float *)(psVar20 + 0x18)))
                    - dVar10);
      local_a8 = (double)(longlong)iVar16;
      iVar19 = (int)((double)(float)(((double)CONCAT44(0x43300000,uStack_94) - dVar3) * dVar39 +
                                    (double)((float)(local_a0 - dVar3) + *(float *)(psVar20 + 0x1a))
                                    ) - dVar11);
      local_b0 = (double)(longlong)iVar19;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar22 + 8) = (short)iVar16;
      *(short *)(*(int *)&menuPcs->field_0x814 + iVar22 + 10) = (short)iVar19;
      uStack_7c = (int)*psVar20 ^ 0x80000000;
      iVar16 = (int)(fVar1 + (float)((double)CONCAT44(0x43300000,uStack_7c) - dVar3) +
                             *(float *)(psVar20 + 0x18));
      local_78 = (double)(longlong)iVar16;
      *(int *)(*(int *)&menuPcs->field_0x814 + iVar21) = iVar16;
      local_70 = (double)(CONCAT44(0x43300000,(int)psVar20[1]) ^ 0x80000000);
      iVar16 = (int)(((float)(local_70 - dVar3) + *(float *)(psVar20 + 0x1a)) - fVar7);
      local_68 = (double)(longlong)iVar16;
      *(int *)(*(int *)&menuPcs->field_0x814 + iVar22 + 0x44) = iVar16;
      if ((double)CONCAT44(0x43300000,*(uint *)(*(int *)&menuPcs->field_0x814 + iVar21) ^ 0x80000000
                          ) - dVar3 < dVar4) {
        *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar21) = 0;
      }
      local_60 = 0x43300000;
      uStack_5c = *(uint *)(*(int *)&menuPcs->field_0x814 + iVar22 + 0x44) ^ 0x80000000;
      if ((double)CONCAT44(0x43300000,uStack_5c) - dVar3 < dVar4) {
        *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar22 + 0x44) = 0;
      }
      iVar16 = iVar22 + 0x4c;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar22 + 0x48) = 0x48;
      iVar22 = iVar22 + 0x50;
      iVar35 = iVar35 + 1;
      *(undefined4 *)(*(int *)&menuPcs->field_0x814 + iVar16) = 0x58;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
  }
  iVar13 = 0;
  iVar22 = 0;
  do {
    if (iVar37 + 8 <= iVar13) {
      if (**(short **)&menuPcs->field_0x84c == iVar33) {
        (*(short **)&menuPcs->field_0x84c)[3] = 1;
      }
      return;
    }
    iVar35 = *(int *)&menuPcs->field_0x84c + (DAT_8032eeae + iVar13) * 0x40 + 8;
    if (iVar13 < iVar37) {
      iVar16 = *(int *)((int)DAT_8032eea8 + iVar22 + 0x44);
      iVar19 = *(int *)((int)DAT_8032eea8 + iVar22 + 0x20);
      fVar1 = *(float *)(&DAT_801dd56c + iVar16 * 4);
      PSMTXScale(fVar1,fVar1,fVar1,&MStack_e0);
LAB_80136c10:
      if (iVar13 < iVar37) {
        MStack_e0.value[1][3] = *(float *)(&DAT_801dd55c + iVar16 * 4);
        MStack_e0.value[0][3] = FLOAT_80331eac;
      }
      else {
        uVar18 = *(uint *)(iVar35 + 0x28);
        uStack_5c = uVar18 ^ 0x80000000;
        local_60 = 0x43300000;
        iVar16 = (int)uVar18 / 5 + ((int)uVar18 >> 0x1f);
        local_78 = (double)CONCAT44(0x43300000,uStack_5c);
        uVar31 = iVar16 - (iVar16 >> 0x1f);
        local_68 = (double)CONCAT44(0x43300000,-(iVar13 - iVar37) + 10U ^ 0x80000000);
        dVar39 = (double)(float)(DOUBLE_80331f70 / (double)(float)(local_78 - DOUBLE_80331e88));
        uVar18 = (uint)((((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331e88) /
                        DOUBLE_80331f30) * (local_68 - DOUBLE_80331e88));
        local_70 = (double)(longlong)(int)uVar18;
        if ((iVar38 == *(int *)(iVar35 + 0x24)) && (menuPcs->field_0x8d == '\0')) {
          menuPcs->field_0x8d = 1;
          PlaySe__6CSoundFiiii(&Sound,0x4d,0x40,0x7f,0);
        }
        if (iVar38 < *(int *)(iVar35 + 0x24)) {
          local_17c.x = _DAT_801dd584;
          fVar1 = FLOAT_80331f78;
        }
        else if (*(int *)(iVar35 + 0x20) < (int)uVar18) {
          uStack_5c = *(int *)(iVar35 + 0x20) - 1;
          if ((int)uVar31 < (int)uStack_5c) {
            local_68 = (double)CONCAT44(0x43300000,uVar31 ^ 0x80000000);
            local_70 = (double)CONCAT44(0x43300000,uStack_5c - uVar31 ^ 0x80000000);
            local_17c.x = ((DAT_801dd580 - DAT_801dd57c) /
                          ((float)((double)CONCAT44(0x43300000,uVar18 ^ 0x80000000) -
                                  DOUBLE_80331e88) - (float)(local_68 - DOUBLE_80331e88))) *
                          (float)(local_70 - DOUBLE_80331e88) - DAT_801dd580;
          }
          else {
            local_68 = (double)CONCAT44(0x43300000,uVar31 ^ 0x80000000);
            local_17c.x = (float)((double)CONCAT44(0x43300000,uStack_5c ^ 0x80000000) -
                                 DOUBLE_80331e88) *
                          ((_DAT_801dd584 - DAT_801dd580) / (float)(local_68 - DOUBLE_80331e88)) -
                          _DAT_801dd584;
          }
          local_17c.x = -local_17c.x;
          uStack_5c = uStack_5c ^ 0x80000000;
          local_60 = 0x43300000;
          fVar1 = (float)(DOUBLE_80331f88 +
                         (double)(float)(dVar39 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                   uStack_5c) -
                                                                 DOUBLE_80331e88)));
        }
        else {
          uStack_5c = -(iVar13 - iVar37) + 8U ^ 0x80000000;
          local_60 = 0x43300000;
          local_17c.x = DAT_801dd57c;
          fVar1 = (float)(DOUBLE_80331f80 *
                         ((double)CONCAT44(0x43300000,uStack_5c) - DOUBLE_80331e88));
        }
        local_17c.y = FLOAT_80331eac;
        local_17c.z = FLOAT_80331eac;
        PSMTXRotRad(FLOAT_80331f04 * fVar1,&MStack_110,0x7a);
        PSMTXMultVecSR(&MStack_110,&local_17c,&local_188);
        if (*(int *)(iVar19 + 4) == 0x44) {
          PSMTXRotRad(FLOAT_80331f10,&MStack_140,0x79);
          PSMTXConcat(&MStack_e0,&MStack_140,&MStack_e0);
          PSMTXRotRad(FLOAT_80331f14,&MStack_170,0x78);
          PSMTXConcat(&MStack_e0,&MStack_170,&MStack_e0);
        }
        MStack_e0.value[0][3] = local_188.x;
        iVar16 = *(int *)(iVar19 + 4);
        MStack_e0.value[1][3] = (float)((double)(FLOAT_80331f18 * local_188.y) - DOUBLE_80331f20);
        if ((iVar16 == 0x41) || (iVar16 == 0x37)) {
          MStack_e0.value[1][3] = MStack_e0.value[1][3] + FLOAT_80331f28;
        }
        else if (iVar16 == 0x44) {
          MStack_e0.value[1][3] = MStack_e0.value[1][3] + FLOAT_80331f2c;
        }
      }
      MStack_e0.value[2][3] = FLOAT_80331eac;
      *(byte *)(*(int *)(iVar19 + 0x168) + 0x10c) =
           *(byte *)(*(int *)(iVar19 + 0x168) + 0x10c) & 0x7f | 0x80;
      SetMatrix__Q26CChara6CModelFPA4_f(*(CModel **)(iVar19 + 0x168),&MStack_e0);
      CalcMatrix__Q26CChara6CModelFv(*(undefined4 *)(iVar19 + 0x168));
      CalcSkin__Q26CChara6CModelFv(*(undefined4 *)(iVar19 + 0x168));
      *(undefined4 *)(*(int *)(iVar19 + 0x168) + 0x9c) = *(undefined4 *)(iVar35 + 0x10);
    }
    else {
      iVar16 = iVar13 + iVar37;
      iVar19 = *(int *)((int)(&menuPcs->m_cameraMatrix + 1) + iVar16 * 4);
      if (iVar19 != 0) {
        PSMTXScale(FLOAT_80331f00,FLOAT_80331f00,FLOAT_80331f00,&MStack_e0);
        goto LAB_80136c10;
      }
    }
    iVar22 = iVar22 + 0x2c;
    iVar13 = iVar13 + 1;
  } while( true );
}

