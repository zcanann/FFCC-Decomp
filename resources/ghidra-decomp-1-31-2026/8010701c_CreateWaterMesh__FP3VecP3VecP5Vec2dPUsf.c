// Function: CreateWaterMesh__FP3VecP3VecP5Vec2dPUsf
// Entry: 8010701c
// Size: 404 bytes

undefined4
CreateWaterMesh__FP3VecP3VecP5Vec2dPUsf
          (double param_1,float *param_2,float *param_3,float *param_4,int param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  int iVar7;
  short sVar8;
  uint uVar9;
  short sVar10;
  float *pfVar11;
  int iVar12;
  float *pfVar13;
  float *pfVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  double dVar18;
  
  dVar6 = DOUBLE_803318b0;
  fVar5 = FLOAT_803318a0;
  fVar4 = FLOAT_80331898;
  uVar16 = 0;
  dVar18 = (double)FLOAT_803318a8;
  fVar1 = (float)(param_1 * (double)FLOAT_803318a4);
  for (fVar3 = fVar1; -fVar1 <= fVar3; fVar3 = fVar3 - (float)(param_1 * dVar18)) {
    uVar15 = 0;
    pfVar11 = param_2;
    pfVar13 = param_3;
    pfVar14 = param_4;
    for (fVar2 = -fVar1; fVar2 <= fVar1; fVar2 = fVar2 + (float)(param_1 * dVar18)) {
      *pfVar11 = fVar2;
      uVar9 = uVar15 ^ 0x80000000;
      param_2 = param_2 + 3;
      pfVar11[1] = fVar4;
      uVar15 = uVar15 + 1;
      param_3 = param_3 + 3;
      param_4 = param_4 + 2;
      pfVar11[2] = fVar3;
      pfVar11 = pfVar11 + 3;
      *pfVar13 = fVar4;
      pfVar13[1] = fVar5;
      pfVar13[2] = fVar4;
      pfVar13 = pfVar13 + 3;
      *pfVar14 = (float)((double)(float)((double)CONCAT44(0x43300000,uVar9) - dVar6) * dVar18);
      pfVar14[1] = (float)((double)(float)((double)CONCAT44(0x43300000,uVar16 ^ 0x80000000) - dVar6)
                          * dVar18);
      pfVar14 = pfVar14 + 2;
    }
    uVar16 = uVar16 + 1;
  }
  iVar7 = 0;
  iVar12 = 0;
  sVar10 = 0;
  do {
    iVar17 = 8;
    sVar8 = sVar10;
    do {
      *(short *)(param_5 + iVar7) = sVar8;
      *(short *)(param_5 + iVar7 + 2) = sVar8 + 1;
      *(short *)(param_5 + iVar7 + 4) = sVar8 + 0x12;
      *(short *)(param_5 + iVar7 + 6) = sVar8 + 0x12;
      *(short *)(param_5 + iVar7 + 8) = sVar8 + 0x11;
      *(short *)(param_5 + iVar7 + 10) = sVar8;
      *(short *)(param_5 + iVar7 + 0xc) = sVar8 + 1;
      *(short *)(param_5 + iVar7 + 0xe) = sVar8 + 2;
      *(short *)(param_5 + iVar7 + 0x10) = sVar8 + 0x13;
      *(short *)(param_5 + iVar7 + 0x12) = sVar8 + 0x13;
      *(short *)(param_5 + iVar7 + 0x14) = sVar8 + 0x12;
      *(short *)(param_5 + iVar7 + 0x16) = sVar8 + 1;
      sVar8 = sVar8 + 2;
      iVar7 = iVar7 + 0x18;
      iVar17 = iVar17 + -1;
    } while (iVar17 != 0);
    iVar12 = iVar12 + 1;
    sVar10 = sVar10 + 0x11;
  } while (iVar12 < 0x10);
  return 1;
}

