// Function: HandleReverb
// Entry: 801946f8
// Size: 1292 bytes

void HandleReverb(uint *param_1,int param_2,int param_3)

{
  uint *puVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  double dVar19;
  float fVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  int iVar27;
  int iVar28;
  int iVar29;
  int iVar30;
  int iVar31;
  int iVar32;
  int iVar33;
  int iVar34;
  int iVar35;
  int iVar36;
  int iVar37;
  int iVar38;
  int iVar39;
  int iVar40;
  int *piVar41;
  int iVar42;
  int *piVar43;
  float *pfVar44;
  uint uVar45;
  float *pfVar46;
  float *pfVar47;
  int iVar48;
  int iVar49;
  int iVar50;
  
  fVar20 = DAT_8033378c;
  dVar19 = DAT_80333780;
  fVar3 = *(float *)(param_2 + 0x168);
  fVar4 = *(float *)(param_2 + 0x1a0);
  fVar16 = *(float *)(param_2 + 0x19c) * DAT_80333790;
  fVar17 = DAT_80333790 - fVar16;
  piVar43 = (int *)(param_2 + 0xb4 + param_3 * 0x3c);
  piVar41 = (int *)(param_2 + param_3 * 0x3c);
  iVar48 = param_3 * 0xc + param_2;
  fVar5 = *(float *)(iVar48 + 0x16c);
  fVar6 = *(float *)(iVar48 + 0x170);
  fVar7 = *(float *)(iVar48 + 0x174);
  fVar8 = *(float *)(param_3 * 4 + param_2 + 400);
  iVar49 = *(int *)(param_2 + 0x1a4);
  iVar42 = param_3 * 4 + param_2;
  iVar36 = *piVar43;
  iVar35 = piVar43[1];
  iVar34 = piVar43[5];
  iVar33 = piVar43[6];
  iVar32 = piVar43[10];
  iVar31 = piVar43[0xb];
  fVar9 = (float)piVar43[4];
  fVar10 = (float)piVar43[9];
  fVar11 = (float)piVar43[0xe];
  iVar39 = piVar43[2];
  iVar38 = piVar43[7];
  iVar37 = piVar43[0xc];
  iVar48 = piVar43[3];
  iVar21 = piVar43[8];
  iVar22 = piVar43[0xd];
  iVar28 = *piVar41;
  iVar27 = piVar41[1];
  iVar26 = piVar41[5];
  iVar25 = piVar41[6];
  iVar24 = piVar41[10];
  iVar23 = piVar41[0xb];
  fVar12 = (float)piVar41[4];
  fVar13 = (float)piVar41[9];
  fVar14 = (float)piVar41[0xe];
  iVar30 = piVar41[2];
  iVar29 = piVar41[7];
  fVar2 = (float)((double)CONCAT44(0x43300000,*param_1 ^ 0x80000000) - DAT_80333780);
  iVar50 = 0x9f;
  do {
    fVar15 = fVar2;
    if (iVar49 != 0) {
      pfVar47 = *(float **)(iVar42 + 0x1ac);
      pfVar44 = *(float **)(iVar42 + 0x1b8);
      fVar15 = *pfVar44;
      *pfVar44 = fVar2;
      pfVar46 = pfVar44 + 1;
      if (pfVar44 + 1 == pfVar47 + iVar49 + -1) {
        pfVar46 = pfVar47;
      }
      pfVar47[0x6e] = (float)pfVar46;
    }
    puVar1 = param_1 + 1;
    uVar45 = *puVar1;
    *(float *)(iVar48 + iVar36) = fVar5 * fVar9 + fVar15;
    iVar36 = iVar36 + 4;
    *(float *)(iVar21 + iVar34) = fVar6 * fVar10 + fVar15;
    fVar9 = *(float *)(iVar48 + iVar35);
    iVar35 = iVar35 + 4;
    fVar10 = *(float *)(iVar21 + iVar33);
    iVar34 = iVar34 + 4;
    iVar33 = iVar33 + 4;
    if (iVar36 == iVar39) {
      iVar36 = 0;
    }
    if (iVar35 == iVar39) {
      iVar35 = 0;
    }
    *(float *)(iVar22 + iVar32) = fVar7 * fVar11 + fVar15;
    iVar32 = iVar32 + 4;
    if (iVar34 == iVar38) {
      iVar34 = 0;
    }
    fVar11 = *(float *)(iVar22 + iVar31);
    iVar31 = iVar31 + 4;
    if (iVar33 == iVar38) {
      iVar33 = 0;
    }
    iVar40 = piVar41[3];
    fVar15 = fVar3 * fVar12 + fVar9 + fVar10 + fVar11;
    if (iVar32 == iVar37) {
      iVar32 = 0;
    }
    if (iVar31 == iVar37) {
      iVar31 = 0;
    }
    *(float *)(iVar40 + iVar28) = fVar15;
    fVar15 = fVar3 * fVar15 - fVar12;
    iVar28 = iVar28 + 4;
    fVar12 = *(float *)(iVar40 + iVar27);
    iVar27 = iVar27 + 4;
    iVar40 = piVar41[8];
    fVar15 = fVar3 * fVar13 + -fVar15;
    if (iVar28 == iVar30) {
      iVar28 = 0;
    }
    *(float *)(iVar40 + iVar26) = fVar15;
    fVar15 = fVar3 * fVar15 - fVar13;
    iVar26 = iVar26 + 4;
    if (iVar27 == iVar30) {
      iVar27 = 0;
    }
    fVar13 = *(float *)(iVar40 + iVar25);
    iVar25 = iVar25 + 4;
    fVar8 = fVar4 * fVar8 + -fVar15 * fVar20;
    if (iVar26 == iVar29) {
      iVar26 = 0;
    }
    iVar40 = piVar41[0xd];
    fVar15 = fVar3 * fVar14 + fVar8;
    if (iVar25 == iVar29) {
      iVar25 = 0;
    }
    *(float *)(iVar40 + iVar24) = fVar15;
    fVar15 = fVar3 * fVar15 - fVar14;
    fVar18 = fVar17 * fVar2;
    fVar14 = *(float *)(iVar40 + iVar23);
    iVar24 = iVar24 + 4;
    iVar23 = iVar23 + 4;
    if (iVar24 == piVar41[0xc]) {
      iVar24 = 0;
    }
    if (iVar23 == piVar41[0xc]) {
      iVar23 = 0;
    }
    fVar2 = (float)((double)CONCAT44(0x43300000,uVar45 ^ 0x80000000) - dVar19);
    *param_1 = (int)(fVar16 * -fVar15 + fVar18);
    iVar50 = iVar50 + -1;
    param_1 = puVar1;
  } while (iVar50 != 0);
  fVar15 = fVar2;
  if (iVar49 != 0) {
    pfVar47 = *(float **)(iVar42 + 0x1ac);
    pfVar44 = *(float **)(iVar42 + 0x1b8);
    fVar15 = *pfVar44;
    *pfVar44 = fVar2;
    pfVar46 = pfVar44 + 1;
    if (pfVar44 + 1 == pfVar47 + iVar49 + -1) {
      pfVar46 = pfVar47;
    }
    pfVar47[0x6e] = (float)pfVar46;
  }
  *(float *)(iVar48 + iVar36) = fVar5 * fVar9 + fVar15;
  iVar36 = iVar36 + 4;
  *(float *)(iVar21 + iVar34) = fVar6 * fVar10 + fVar15;
  fVar5 = *(float *)(iVar48 + iVar35);
  iVar35 = iVar35 + 4;
  fVar6 = *(float *)(iVar21 + iVar33);
  iVar34 = iVar34 + 4;
  iVar33 = iVar33 + 4;
  if (iVar36 == iVar39) {
    iVar36 = 0;
  }
  if (iVar35 == iVar39) {
    iVar35 = 0;
  }
  *(float *)(iVar22 + iVar32) = fVar7 * fVar11 + fVar15;
  iVar32 = iVar32 + 4;
  if (iVar34 == iVar38) {
    iVar34 = 0;
  }
  fVar7 = *(float *)(iVar22 + iVar31);
  iVar31 = iVar31 + 4;
  if (iVar33 == iVar38) {
    iVar33 = 0;
  }
  iVar48 = piVar41[3];
  fVar9 = fVar3 * fVar12 + fVar5 + fVar6 + fVar7;
  if (iVar32 == iVar37) {
    iVar32 = 0;
  }
  if (iVar31 == iVar37) {
    iVar31 = 0;
  }
  *(float *)(iVar48 + iVar28) = fVar9;
  iVar28 = iVar28 + 4;
  iVar48 = *(int *)(iVar48 + iVar27);
  iVar27 = iVar27 + 4;
  iVar21 = piVar41[8];
  fVar9 = fVar3 * fVar13 + -(fVar3 * fVar9 - fVar12);
  if (iVar28 == iVar30) {
    iVar28 = 0;
  }
  *(float *)(iVar21 + iVar26) = fVar9;
  iVar26 = iVar26 + 4;
  if (iVar27 == iVar30) {
    iVar27 = 0;
  }
  iVar21 = *(int *)(iVar21 + iVar25);
  iVar25 = iVar25 + 4;
  fVar4 = fVar4 * fVar8 + -(fVar3 * fVar9 - fVar13) * fVar20;
  if (iVar26 == iVar29) {
    iVar26 = 0;
  }
  iVar22 = piVar41[0xd];
  fVar8 = fVar3 * fVar14 + fVar4;
  if (iVar25 == iVar29) {
    iVar25 = 0;
  }
  *(float *)(iVar22 + iVar24) = fVar8;
  iVar22 = *(int *)(iVar22 + iVar23);
  iVar24 = iVar24 + 4;
  iVar23 = iVar23 + 4;
  if (iVar24 == piVar41[0xc]) {
    iVar24 = 0;
  }
  if (iVar23 == piVar41[0xc]) {
    iVar23 = 0;
  }
  *puVar1 = (int)(fVar16 * -(fVar3 * fVar8 - fVar14) + fVar17 * fVar2);
  piVar43 = (int *)(param_2 + 0xb4 + param_3 * 0x3c);
  *piVar43 = iVar36;
  piVar43[1] = iVar35;
  piVar43[5] = iVar34;
  piVar43[6] = iVar33;
  piVar43[10] = iVar32;
  piVar43[0xb] = iVar31;
  piVar43[4] = (int)fVar5;
  piVar43[9] = (int)fVar6;
  piVar43[0xe] = (int)fVar7;
  *piVar41 = iVar28;
  piVar41[1] = iVar27;
  piVar41[5] = iVar26;
  piVar41[6] = iVar25;
  piVar41[10] = iVar24;
  piVar41[0xb] = iVar23;
  piVar41[4] = iVar48;
  piVar41[9] = iVar21;
  piVar41[0xe] = iVar22;
  *(float *)(param_3 * 4 + param_2 + 400) = fVar4;
  return;
}

