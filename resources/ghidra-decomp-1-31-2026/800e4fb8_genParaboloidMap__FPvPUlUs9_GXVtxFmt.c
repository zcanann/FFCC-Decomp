// Function: genParaboloidMap__FPvPUlUs9_GXVtxFmt
// Entry: 800e4fb8
// Size: 1316 bytes

/* WARNING: Removing unreachable block (ram,0x800e54c0) */
/* WARNING: Removing unreachable block (ram,0x800e54b8) */
/* WARNING: Removing unreachable block (ram,0x800e54b0) */
/* WARNING: Removing unreachable block (ram,0x800e54a8) */
/* WARNING: Removing unreachable block (ram,0x800e54a0) */
/* WARNING: Removing unreachable block (ram,0x800e5498) */
/* WARNING: Removing unreachable block (ram,0x800e5490) */
/* WARNING: Removing unreachable block (ram,0x800e5488) */
/* WARNING: Removing unreachable block (ram,0x800e5480) */
/* WARNING: Removing unreachable block (ram,0x800e5478) */
/* WARNING: Removing unreachable block (ram,0x800e5470) */
/* WARNING: Removing unreachable block (ram,0x800e5468) */
/* WARNING: Removing unreachable block (ram,0x800e5460) */
/* WARNING: Removing unreachable block (ram,0x800e5458) */
/* WARNING: Removing unreachable block (ram,0x800e5450) */
/* WARNING: Removing unreachable block (ram,0x800e5448) */
/* WARNING: Removing unreachable block (ram,0x800e5040) */
/* WARNING: Removing unreachable block (ram,0x800e5038) */
/* WARNING: Removing unreachable block (ram,0x800e5030) */
/* WARNING: Removing unreachable block (ram,0x800e5028) */
/* WARNING: Removing unreachable block (ram,0x800e5020) */
/* WARNING: Removing unreachable block (ram,0x800e5018) */
/* WARNING: Removing unreachable block (ram,0x800e5010) */
/* WARNING: Removing unreachable block (ram,0x800e5008) */
/* WARNING: Removing unreachable block (ram,0x800e5000) */
/* WARNING: Removing unreachable block (ram,0x800e4ff8) */
/* WARNING: Removing unreachable block (ram,0x800e4ff0) */
/* WARNING: Removing unreachable block (ram,0x800e4fe8) */
/* WARNING: Removing unreachable block (ram,0x800e4fe0) */
/* WARNING: Removing unreachable block (ram,0x800e4fd8) */
/* WARNING: Removing unreachable block (ram,0x800e4fd0) */
/* WARNING: Removing unreachable block (ram,0x800e4fc8) */

void genParaboloidMap__FPvPUlUs9_GXVtxFmt
               (undefined4 param_1,uint *param_2,uint param_3,undefined4 param_4)

{
  float fVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  
  uVar3 = param_3 & 0xffff;
  iVar6 = uVar3 + 1;
  uVar2 = (iVar6 + (uVar3 - 2) * iVar6 * 2) * 0x18 + 0x1f & 0xffffffe0;
  DCInvalidateRange(param_1,uVar2);
  GXBeginDisplayList(param_1,uVar2);
  GXClearVtxDesc();
  GXSetVtxDesc(9,1);
  GXSetVtxDesc(10,1);
  GXSetVtxAttrFmt(param_4,9,1,4,0);
  GXSetVtxAttrFmt(param_4,10,0,4,0);
  GXBegin(0xa0,7,uVar3 + 2 & 0xffff);
  dVar10 = (double)(FLOAT_803311b0 / (float)((double)CONCAT44(0x43300000,uVar3) - DOUBLE_803311a8));
  dVar7 = (double)sin(dVar10);
  dVar16 = (double)(FLOAT_80331184 * (float)dVar7);
  dVar7 = (double)cos(dVar10);
  DAT_cc008000 = FLOAT_80331180;
  DAT_cc008000 = FLOAT_80331180;
  dVar15 = (double)(FLOAT_80331184 * (float)dVar7);
  dVar21 = (double)FLOAT_803311b4;
  uVar4 = 0;
  DAT_cc008000 = FLOAT_80331184;
  DAT_cc008000 = FLOAT_80331180;
  dVar20 = (double)FLOAT_803311b8;
  DAT_cc008000 = FLOAT_80331180;
  dVar13 = (double)(float)((double)(float)((double)FLOAT_80331190 * dVar15) * dVar15);
  DAT_cc008000 = FLOAT_80331190;
  dVar7 = DOUBLE_803311a8;
  dVar10 = DOUBLE_803311d8;
  fVar1 = FLOAT_80331180;
  while (dVar11 = (double)fVar1, (int)uVar4 <= (int)uVar3) {
    dVar9 = (double)cos(dVar11);
    dVar9 = (double)(float)(dVar16 * (double)(float)dVar9);
    dVar11 = (double)sin(dVar11);
    uVar4 = uVar4 + 1;
    DAT_cc008000 = (float)dVar9;
    DAT_cc008000 = (float)(dVar16 * (double)(float)dVar11);
    fVar1 = (float)(dVar20 * (double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) -
                                            dVar10)) /
            (float)((double)CONCAT44(0x43300000,uVar3) - dVar7);
    DAT_cc008000 = (float)dVar15;
    DAT_cc008000 = (float)((double)(float)(dVar21 * dVar9) * dVar15);
    DAT_cc008000 = (float)((double)(float)(dVar21 * (double)(float)(dVar16 * (double)(float)dVar11))
                          * dVar15);
    DAT_cc008000 = (float)dVar13;
  }
  dVar21 = (double)FLOAT_803311b4;
  dVar11 = (double)FLOAT_803311c8;
  param_3 = param_3 & 0xffff;
  dVar15 = (double)FLOAT_803311b0;
  dVar16 = (double)FLOAT_80331184;
  dVar20 = (double)FLOAT_80331190;
  dVar7 = DOUBLE_803311a8;
  dVar10 = DOUBLE_803311c0;
  dVar13 = DOUBLE_803311d8;
  for (uVar4 = 2; (int)uVar4 < (int)uVar3; uVar4 = uVar4 + 1) {
    dVar9 = (double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000)
                                                    - dVar13));
    dVar14 = (double)((float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,
                                                                        uVar4 - 1 ^ 0x80000000) -
                                                      dVar13)) /
                     (float)((double)CONCAT44(0x43300000,param_3) - dVar7));
    dVar18 = (double)(float)(dVar9 / (double)(float)((double)CONCAT44(0x43300000,param_3) - dVar7));
    dVar9 = (double)sin(dVar14,CONCAT44(0x43300000,param_3),dVar9);
    dVar17 = (double)(float)(dVar16 * (double)(float)dVar9);
    dVar9 = (double)cos(dVar14);
    dVar14 = (double)(float)(dVar16 * (double)(float)dVar9);
    dVar9 = (double)sin(dVar18);
    dVar23 = (double)(float)(dVar16 * (double)(float)dVar9);
    dVar9 = (double)cos(dVar18);
    dVar22 = (double)(float)(dVar16 * (double)(float)dVar9);
    dVar9 = (double)(float)((double)(float)(dVar20 * dVar14) * dVar14);
    dVar18 = (double)(float)((double)(float)(dVar20 * dVar22) * dVar22);
    if ((ABS(dVar14) < dVar10) || (ABS(dVar22) < dVar10)) break;
    GXBegin(0x98,7,iVar6 * 2 & 0xfffe);
    uVar5 = 0;
    fVar1 = FLOAT_80331180;
    while (dVar19 = (double)fVar1, (int)uVar5 <= (int)uVar3) {
      dVar8 = (double)cos(dVar19);
      dVar12 = (double)(float)(dVar23 * (double)(float)dVar8);
      dVar8 = (double)sin(dVar19);
      DAT_cc008000 = (float)dVar12;
      DAT_cc008000 = (float)(dVar23 * (double)(float)dVar8);
      DAT_cc008000 = (float)dVar22;
      DAT_cc008000 = (float)((double)(float)(dVar21 * dVar12) * dVar22);
      DAT_cc008000 = (float)((double)(float)(dVar21 * (double)(float)(dVar23 * (double)(float)dVar8)
                                            ) * dVar22);
      DAT_cc008000 = (float)dVar18;
      dVar8 = (double)cos(dVar19);
      dVar8 = (double)(float)(dVar17 * (double)(float)dVar8);
      dVar19 = (double)sin(dVar19);
      uVar5 = uVar5 + 1;
      DAT_cc008000 = (float)dVar8;
      DAT_cc008000 = (float)(dVar17 * (double)(float)dVar19);
      fVar1 = (float)(dVar11 * (double)(float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) -
                                              dVar13)) /
              (float)((double)CONCAT44(0x43300000,param_3) - dVar7);
      DAT_cc008000 = (float)dVar14;
      DAT_cc008000 = (float)((double)(float)(dVar21 * dVar8) * dVar14);
      DAT_cc008000 = (float)((double)(float)(dVar21 * (double)(float)(dVar17 * (double)(float)dVar19
                                                                     )) * dVar14);
      DAT_cc008000 = (float)dVar9;
    }
  }
  uVar3 = GXEndDisplayList();
  *param_2 = uVar3;
  if (uVar2 < *param_2) {
    OSReport(s_Error_allocating_display_list____801db7ac,uVar2);
    OSPanic(s_pppYmEnv_cpp_801db7d4,0x19f,s_Exiting_803311cc);
  }
  DCFlushRange(param_1,*param_2);
  return;
}

