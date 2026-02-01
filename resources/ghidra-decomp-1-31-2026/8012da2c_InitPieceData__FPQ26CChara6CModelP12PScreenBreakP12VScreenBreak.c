// Function: InitPieceData__FPQ26CChara6CModelP12PScreenBreakP12VScreenBreak
// Entry: 8012da2c
// Size: 1020 bytes

/* WARNING: Removing unreachable block (ram,0x8012de0c) */
/* WARNING: Removing unreachable block (ram,0x8012de04) */
/* WARNING: Removing unreachable block (ram,0x8012ddfc) */
/* WARNING: Removing unreachable block (ram,0x8012ddf4) */
/* WARNING: Removing unreachable block (ram,0x8012ddec) */
/* WARNING: Removing unreachable block (ram,0x8012dde4) */
/* WARNING: Removing unreachable block (ram,0x8012dddc) */
/* WARNING: Removing unreachable block (ram,0x8012ddd4) */
/* WARNING: Removing unreachable block (ram,0x8012da74) */
/* WARNING: Removing unreachable block (ram,0x8012da6c) */
/* WARNING: Removing unreachable block (ram,0x8012da64) */
/* WARNING: Removing unreachable block (ram,0x8012da5c) */
/* WARNING: Removing unreachable block (ram,0x8012da54) */
/* WARNING: Removing unreachable block (ram,0x8012da4c) */
/* WARNING: Removing unreachable block (ram,0x8012da44) */
/* WARNING: Removing unreachable block (ram,0x8012da3c) */

void InitPieceData__FPQ26CChara6CModelP12PScreenBreakP12VScreenBreak
               (int param_1,int param_2,int param_3)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  short sVar7;
  short sVar9;
  short *psVar11;
  short sVar12;
  int iVar14;
  uint uVar15;
  Vec *inVec;
  int iVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double dVar25;
  S16Vec local_e8;
  S16Vec local_e0;
  S16Vec local_d8;
  short local_d0;
  short sStack_ce;
  short local_cc;
  Vec local_c8;
  undefined4 local_b8;
  uint uStack_b4;
  short sVar8;
  short sVar10;
  short sVar13;
  
  memset(*(undefined4 *)(param_3 + 0xc),0,*(int *)(*(int *)(param_1 + 0xa4) + 0xc) * 0x3c);
  dVar19 = (double)FLOAT_80331cc8;
  iVar16 = *(int *)(param_1 + 0xac);
  dVar18 = -dVar19;
  inVec = *(Vec **)(param_3 + 0xc);
  dVar20 = (double)FLOAT_80331cd0;
  local_d0 = -0x7fff;
  sStack_ce = -0x7fff;
  dVar21 = (double)FLOAT_80331cd4;
  local_cc = -0x7fff;
  dVar22 = (double)FLOAT_80331cc4;
  dVar24 = (double)FLOAT_80331cc0;
  dVar25 = (double)FLOAT_80331cd8;
  dVar23 = DOUBLE_80331ce0;
  for (uVar15 = 0; uVar15 < *(uint *)(*(int *)(param_1 + 0xa4) + 0xc); uVar15 = uVar15 + 1) {
    iVar14 = *(int *)(iVar16 + 8);
    iVar5 = *(int *)(param_1 + 0xa8) + *(int *)(iVar14 + 0x5c) * 0xc0;
    *(byte *)(iVar5 + 0xbc) = *(byte *)(iVar5 + 0xbc) & 0x7f;
    PSMTXIdentity((Mtx *)(iVar5 + 0x14));
    iVar5 = *(int *)(iVar14 + 0x14);
    iVar6 = 0;
    local_d8.x = -0x7fff;
    local_d8.y = -0x7fff;
    local_d8.z = -0x7fff;
    sVar2 = 0x7fff;
    sVar3 = 0x7fff;
    local_e0.z = 0x7fff;
    sVar12 = 0x7fff;
    sVar9 = 0x7fff;
    sVar4 = 0x7fff;
    for (; iVar5 != 0; iVar5 = iVar5 + -1) {
      sVar1 = *(short *)(*(int *)(iVar14 + 0x18) + iVar6);
      if (local_d0 < sVar1) {
        local_d0 = sVar1;
      }
      sVar1 = *(short *)(*(int *)(iVar14 + 0x18) + iVar6 + 2);
      if (sStack_ce < sVar1) {
        sStack_ce = sVar1;
      }
      sVar1 = *(short *)(*(int *)(iVar14 + 0x18) + iVar6 + 4);
      if (local_cc < sVar1) {
        local_cc = sVar1;
      }
      psVar11 = (short *)(*(int *)(iVar14 + 0x18) + iVar6);
      sVar1 = *psVar11;
      sVar7 = sVar1;
      sVar8 = sVar1;
      if (sVar12 < sVar1) {
        sVar7 = sVar2;
        sVar8 = sVar12;
      }
      sVar12 = psVar11[1];
      sVar13 = sVar12;
      if (sVar9 < sVar12) {
        sVar12 = sVar3;
        sVar13 = sVar9;
      }
      sVar9 = psVar11[2];
      sVar10 = sVar9;
      if (sVar4 < sVar9) {
        sVar9 = local_e0.z;
        sVar10 = sVar4;
      }
      if (local_d8.x < sVar1) {
        local_d8.x = sVar1;
      }
      sVar2 = *(short *)(*(int *)(iVar14 + 0x18) + iVar6 + 2);
      if (local_d8.y < sVar2) {
        local_d8.y = sVar2;
      }
      sVar2 = *(short *)(*(int *)(iVar14 + 0x18) + iVar6 + 4);
      if (local_d8.z < sVar2) {
        local_d8.z = sVar2;
      }
      iVar6 = iVar6 + 6;
      sVar2 = sVar7;
      sVar3 = sVar12;
      local_e0.z = sVar9;
      sVar12 = sVar8;
      sVar9 = sVar13;
      sVar4 = sVar10;
    }
    local_e0.z = local_d8.z + local_e0.z;
    local_d8.x = local_d8.x + sVar2;
    local_d8.y = local_d8.y + sVar3;
    local_e0.x = local_d8.x;
    local_e0.y = local_d8.y;
    local_d8.z = local_e0.z;
    ConvI2FVector__5CUtilFR3Vec6S16Vecl
              ((CUtil *)&DAT_8032ec70,inVec + 3,&local_e0,
               *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x34));
    PSVECScale(FLOAT_80331ccc,inVec + 3,inVec + 3);
    dVar17 = (double)inVec[3].x;
    if (dVar19 < dVar17) {
      dVar17 = (double)RandF__5CMathFf(dVar19,&Math);
    }
    if ((double)inVec[3].x < dVar18) {
      dVar17 = (double)RandF__5CMathFf((double)FLOAT_80331cc8,&Math);
      dVar17 = -dVar17;
    }
    inVec->x = (float)dVar17;
    inVec->y = (float)dVar20;
    inVec->z = (float)dVar21;
    PSVECNormalize(inVec,inVec);
    local_c8.x = DAT_801dd4bc;
    local_c8.y = DAT_801dd4c0;
    local_c8.z = DAT_801dd4c4;
    PSVECCrossProduct(inVec,&local_c8,inVec + 2);
    dVar17 = (double)RandF__5CMathFf((double)*(float *)(param_2 + 0x3c),&Math);
    PSVECScale((float)((double)*(float *)(param_2 + 0x38) + dVar17),inVec,inVec);
    inVec[1].z = (float)dVar22;
    inVec[1].y = (float)dVar22;
    inVec[1].x = (float)dVar22;
    inVec[4].x = (float)dVar22;
    uStack_b4 = (uint)*(byte *)(param_2 + 0x34);
    local_b8 = 0x43300000;
    dVar17 = (double)RandF__5CMathFf((double)(float)((double)CONCAT44(0x43300000,uStack_b4) - dVar23
                                                    ),&Math);
    iVar16 = iVar16 + 0x14;
    inVec[4].y = (float)(dVar25 * (double)(float)(dVar24 + dVar17));
    *(undefined *)&inVec[4].z = 0;
    inVec = inVec + 5;
  }
  local_e8.y = sStack_ce;
  local_e8.x = local_d0;
  local_e8.z = local_cc;
  ConvI2FVector__5CUtilFR3Vec6S16Vecl
            ((CUtil *)&DAT_8032ec70,param_3 + 0x18,&local_e8,
             *(undefined4 *)(*(int *)(param_1 + 0xa4) + 0x34));
  return;
}

