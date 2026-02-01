// Function: PSMTXMultVecArray
// Entry: 80186448
// Size: 140 bytes

/* WARNING: Removing unreachable block (ram,0x801864cc) */
/* WARNING: Removing unreachable block (ram,0x801864c8) */
/* WARNING: Removing unreachable block (ram,0x80186494) */
/* WARNING: Removing unreachable block (ram,0x801864b4) */
/* WARNING: Removing unreachable block (ram,0x8018649c) */
/* WARNING: Removing unreachable block (ram,0x801864ac) */
/* WARNING: Removing unreachable block (ram,0x80186480) */
/* WARNING: Removing unreachable block (ram,0x8018647c) */
/* WARNING: Removing unreachable block (ram,0x80186474) */
/* WARNING: Removing unreachable block (ram,0x8018646c) */
/* WARNING: Removing unreachable block (ram,0x80186460) */
/* WARNING: Removing unreachable block (ram,0x80186454) */
/* WARNING: Removing unreachable block (ram,0x8018644c) */
/* WARNING: Removing unreachable block (ram,0x80186448) */

void PSMTXMultVecArray(Mtx *mtx,Vec *vec,int param_3,int param_4)

{
  float fVar1;
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
  float fVar19;
  float fVar20;
  float fVar21;
  float *pfVar22;
  float *pfVar23;
  float *pfVar24;
  int iVar25;
  
  fVar1 = mtx->value[0][0];
  fVar10 = mtx->value[0][1];
  fVar2 = mtx->value[1][0];
  fVar11 = mtx->value[1][1];
  iVar25 = param_4 + -1;
  fVar3 = mtx->value[0][2];
  fVar12 = mtx->value[0][3];
  fVar4 = mtx->value[1][2];
  fVar13 = mtx->value[1][3];
  fVar5 = mtx->value[2][0];
  fVar14 = mtx->value[2][1];
  fVar6 = mtx->value[2][2];
  fVar15 = mtx->value[2][3];
  fVar7 = vec->x;
  fVar16 = vec->y;
  pfVar23 = &vec->z;
  fVar8 = *pfVar23;
  fVar18 = fVar10 * fVar16 + fVar1 * fVar7 + fVar12;
  fVar19 = fVar11 * fVar16 + fVar2 * fVar7 + fVar13;
  fVar7 = fVar6 * fVar8 + fVar5 * fVar7;
  fVar16 = fVar15 * 1.0 + fVar14 * fVar16;
  pfVar22 = (float *)(param_3 + -4);
  do {
    pfVar24 = pfVar22;
    fVar9 = pfVar23[1];
    fVar17 = pfVar23[2];
    fVar21 = fVar3 * fVar8;
    fVar20 = fVar4 * fVar8;
    pfVar23 = pfVar23 + 3;
    fVar8 = *pfVar23;
    pfVar24[1] = fVar21 + fVar18;
    pfVar24[2] = fVar20 + fVar19;
    fVar18 = fVar10 * fVar17 + fVar1 * fVar9 + fVar12;
    fVar19 = fVar11 * fVar17 + fVar2 * fVar9 + fVar13;
    pfVar24[3] = fVar7 + fVar16;
    fVar7 = fVar6 * fVar8 + fVar5 * fVar9;
    fVar16 = fVar15 * 1.0 + fVar14 * fVar17;
    iVar25 = iVar25 + -1;
    pfVar22 = pfVar24 + 3;
  } while (iVar25 != 0);
  pfVar24[4] = fVar3 * fVar8 + fVar18;
  pfVar24[5] = fVar4 * fVar8 + fVar19;
  pfVar24[6] = fVar7 + fVar16;
  return;
}

