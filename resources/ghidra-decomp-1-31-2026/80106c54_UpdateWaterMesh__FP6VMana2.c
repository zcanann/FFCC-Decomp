// Function: UpdateWaterMesh__FP6VMana2
// Entry: 80106c54
// Size: 968 bytes

undefined4 UpdateWaterMesh__FP6VMana2(int param_1)

{
  undefined4 *puVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  float *pfVar13;
  int iVar14;
  int iVar15;
  undefined4 *puVar16;
  undefined4 *puVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  float *pfVar23;
  float *pfVar24;
  float *pfVar25;
  int iVar26;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  puVar16 = *(undefined4 **)(param_1 + 0x48);
  iVar4 = *(int *)(param_1 + 0x3c);
  puVar17 = *(undefined4 **)(param_1 + 0x4c);
  if (puVar16 == (undefined4 *)0x0) {
    uVar5 = 0;
  }
  else {
    iVar19 = 1;
    iVar8 = 0x11;
    do {
      fVar3 = FLOAT_803318a4;
      fVar2 = FLOAT_80331898;
      iVar18 = 1;
      iVar6 = iVar8 + 1;
      iVar20 = iVar6 * 4;
      iVar26 = 3;
      do {
        iVar21 = iVar18 + iVar8;
        pfVar13 = (float *)((int)puVar16 + iVar20);
        iVar22 = iVar21 + 1;
        iVar10 = iVar21 + 2;
        iVar14 = iVar18 + iVar8;
        iVar11 = iVar18 + iVar8;
        iVar12 = iVar11 + 3;
        pfVar25 = (float *)(puVar16 + iVar22);
        pfVar24 = (float *)(puVar16 + iVar10);
        pfVar23 = (float *)(puVar16 + iVar12);
        iVar15 = iVar14 + 4;
        *(float *)((int)puVar17 + iVar20) =
             (fVar2 * *pfVar13 +
             fVar3 * (pfVar13[1] +
                     pfVar13[-1] + (float)puVar16[iVar6 + -0x11] + (float)puVar16[iVar6 + 0x11])) -
             *(float *)((int)puVar17 + iVar20);
        puVar17[iVar22] =
             (fVar2 * *pfVar25 +
             fVar3 * (pfVar25[1] +
                     pfVar25[-1] + (float)puVar16[iVar21 + -0x10] + (float)puVar16[iVar21 + 0x12]))
             - (float)puVar17[iVar22];
        puVar17[iVar10] =
             (fVar2 * *pfVar24 +
             fVar3 * (pfVar24[1] +
                     pfVar24[-1] + (float)puVar16[iVar21 + -0xf] + (float)puVar16[iVar21 + 0x13])) -
             (float)puVar17[iVar10];
        puVar17[iVar12] =
             (fVar2 * *pfVar23 +
             fVar3 * (pfVar23[1] +
                     pfVar23[-1] + (float)puVar16[iVar11 + -0xe] + (float)puVar16[iVar11 + 0x14])) -
             (float)puVar17[iVar12];
        pfVar13 = (float *)(puVar16 + iVar15);
        iVar6 = iVar6 + 5;
        iVar20 = iVar20 + 0x14;
        iVar18 = iVar18 + 5;
        puVar17[iVar15] =
             (fVar2 * *pfVar13 +
             fVar3 * (pfVar13[1] +
                     pfVar13[-1] + (float)puVar16[iVar14 + -0xd] + (float)puVar16[iVar14 + 0x15])) -
             (float)puVar17[iVar15];
        iVar26 = iVar26 + -1;
      } while (iVar26 != 0);
      iVar19 = iVar19 + 1;
      iVar8 = iVar8 + 0x11;
    } while (iVar19 < 0x10);
    iVar19 = 0;
    iVar20 = 0x24;
    puVar7 = puVar16;
    puVar9 = puVar17;
    iVar8 = iVar4;
    do {
      uVar5 = *puVar7;
      iVar19 = iVar19 + 8;
      *puVar7 = *puVar9;
      *puVar9 = uVar5;
      *(undefined4 *)(iVar8 + 4) = *puVar7;
      uVar5 = puVar7[1];
      puVar7[1] = puVar9[1];
      puVar9[1] = uVar5;
      *(undefined4 *)(iVar8 + 0x10) = puVar7[1];
      uVar5 = puVar7[2];
      puVar7[2] = puVar9[2];
      puVar9[2] = uVar5;
      *(undefined4 *)(iVar8 + 0x1c) = puVar7[2];
      uVar5 = puVar7[3];
      puVar7[3] = puVar9[3];
      puVar9[3] = uVar5;
      *(undefined4 *)(iVar8 + 0x28) = puVar7[3];
      uVar5 = puVar7[4];
      puVar7[4] = puVar9[4];
      puVar9[4] = uVar5;
      *(undefined4 *)(iVar8 + 0x34) = puVar7[4];
      uVar5 = puVar7[5];
      puVar7[5] = puVar9[5];
      puVar9[5] = uVar5;
      *(undefined4 *)(iVar8 + 0x40) = puVar7[5];
      uVar5 = puVar7[6];
      puVar7[6] = puVar9[6];
      puVar9[6] = uVar5;
      *(undefined4 *)(iVar8 + 0x4c) = puVar7[6];
      uVar5 = puVar7[7];
      puVar7[7] = puVar9[7];
      puVar9[7] = uVar5;
      puVar9 = puVar9 + 8;
      puVar1 = puVar7 + 7;
      puVar7 = puVar7 + 8;
      *(undefined4 *)(iVar8 + 0x58) = *puVar1;
      iVar8 = iVar8 + 0x60;
      iVar20 = iVar20 + -1;
    } while (iVar20 != 0);
    iVar8 = 0x121 - iVar19;
    puVar16 = puVar16 + iVar19;
    puVar17 = puVar17 + iVar19;
    iVar20 = iVar4 + iVar19 * 0xc;
    if (iVar19 < 0x121) {
      do {
        uVar5 = *puVar16;
        *puVar16 = *puVar17;
        *puVar17 = uVar5;
        puVar17 = puVar17 + 1;
        uVar5 = *puVar16;
        puVar16 = puVar16 + 1;
        *(undefined4 *)(iVar20 + 4) = uVar5;
        iVar20 = iVar20 + 0xc;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    DCFlushRange(iVar4,0xd8c);
    CalculateNormal__FP6VMana2(param_1);
    local_48 = *(undefined4 *)(param_1 + 0x8c);
    local_44 = *(undefined4 *)(param_1 + 0x9c);
    local_40 = *(undefined4 *)(param_1 + 0xac);
    local_3c = local_48;
    local_38 = local_44;
    local_34 = local_40;
    CalcWaterReflectionVector__FP3VecP3VecP3Vecl3VecPA4_fP8_GXColorP5Vec2d
              (*(undefined4 *)(param_1 + 0x44),*(undefined4 *)(param_1 + 0x3c),
               *(undefined4 *)(param_1 + 0x40),0x121,&local_48,param_1 + 0x80,
               *(undefined4 *)(param_1 + 0x5c),*(undefined4 *)(param_1 + 0x58));
    uVar5 = 1;
  }
  return uVar5;
}

