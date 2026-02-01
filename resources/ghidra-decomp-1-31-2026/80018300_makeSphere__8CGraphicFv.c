// Function: makeSphere__8CGraphicFv
// Entry: 80018300
// Size: 1124 bytes

/* WARNING: Removing unreachable block (ram,0x80018748) */
/* WARNING: Removing unreachable block (ram,0x80018740) */
/* WARNING: Removing unreachable block (ram,0x80018738) */
/* WARNING: Removing unreachable block (ram,0x80018730) */
/* WARNING: Removing unreachable block (ram,0x80018728) */
/* WARNING: Removing unreachable block (ram,0x80018720) */
/* WARNING: Removing unreachable block (ram,0x80018718) */
/* WARNING: Removing unreachable block (ram,0x80018710) */
/* WARNING: Removing unreachable block (ram,0x80018348) */
/* WARNING: Removing unreachable block (ram,0x80018340) */
/* WARNING: Removing unreachable block (ram,0x80018338) */
/* WARNING: Removing unreachable block (ram,0x80018330) */
/* WARNING: Removing unreachable block (ram,0x80018328) */
/* WARNING: Removing unreachable block (ram,0x80018320) */
/* WARNING: Removing unreachable block (ram,0x80018318) */
/* WARNING: Removing unreachable block (ram,0x80018310) */

void makeSphere__8CGraphicFv(CGraphic *graphic)

{
  int iVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  float *pfVar12;
  float *pfVar13;
  int iVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double dVar18;
  double dVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  float local_2b8 [126];
  undefined4 local_c0;
  uint uStack_bc;
  
  dVar19 = (double)FLOAT_8032f6d0;
  iVar11 = 1;
  local_2b8[0] = FLOAT_8032f6d0;
  dVar22 = (double)FLOAT_8032f704;
  local_2b8[1] = FLOAT_8032f6c0;
  local_2b8[2] = FLOAT_8032f6c0;
  dVar20 = (double)FLOAT_8032f6e0;
  pfVar12 = local_2b8 + 3;
  dVar21 = (double)FLOAT_8032f700;
  iVar10 = 0;
  dVar23 = DOUBLE_8032f6e8;
  do {
    local_c0 = 0x43300000;
    uStack_bc = iVar10 + 1U ^ 0x80000000;
    dVar17 = (double)(float)((double)(float)(dVar20 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                       uStack_bc) -
                                                                     dVar23)) / dVar21);
    dVar15 = (double)cos(dVar17);
    dVar16 = (double)(float)(dVar19 * (double)(float)dVar15);
    dVar15 = (double)sin(dVar17);
    uVar9 = 0;
    dVar15 = (double)(float)(dVar19 * (double)(float)dVar15);
    pfVar13 = pfVar12;
    iVar6 = iVar11 * 0xc;
    do {
      uStack_bc = uVar9 ^ 0x80000000;
      local_c0 = 0x43300000;
      dVar17 = (double)CONCAT44(0x43300000,uStack_bc);
      *pfVar13 = (float)dVar16;
      dVar18 = (double)(float)(dVar22 * (double)(float)(dVar17 - dVar23));
      dVar17 = (double)sin(dVar18);
      pfVar13[1] = (float)(dVar15 * (double)(float)dVar17);
      dVar17 = (double)cos(dVar18);
      fVar3 = FLOAT_8032f6c4;
      uVar9 = uVar9 + 1;
      pfVar12 = pfVar12 + 3;
      pfVar13 = pfVar13 + 3;
      iVar11 = iVar11 + 1;
      *(float *)((int)local_2b8 + iVar6 + 8) = (float)(dVar15 * (double)(float)dVar17);
      iVar6 = iVar6 + 0xc;
    } while ((int)uVar9 < 8);
    iVar10 = iVar10 + 1;
  } while (iVar10 < 5);
  *(undefined4 *)&graphic->field_0x71f8 = 0x880;
  local_2b8[iVar11 * 3] = fVar3;
  uVar5 = *(undefined4 *)&graphic->field_0x71f8;
  local_2b8[iVar11 * 3 + 1] = FLOAT_8032f6c0;
  uVar7 = *(undefined4 *)&graphic->field_0x4;
  local_2b8[iVar11 * 3 + 2] = FLOAT_8032f6c0;
  uVar5 = __nwa__FUlPQ27CMemory6CStagePci(uVar5,uVar7,s_graphic_cpp_801d6348,0x41a);
  *(undefined4 *)&graphic->field_0x71fc = uVar5;
  DCInvalidateRange(*(undefined4 *)&graphic->field_0x71fc,*(undefined4 *)&graphic->field_0x71f8);
  GXBeginDisplayList(*(undefined4 *)&graphic->field_0x71fc,*(undefined4 *)&graphic->field_0x71f8);
  GXBegin(0xa8,0,0xb0);
  iVar11 = 0;
  iVar10 = 1;
  do {
    iVar6 = iVar10 * 0xc;
    iVar8 = 0;
    iVar14 = 4;
    do {
      iVar1 = iVar8 + 1 >> 0x1f;
      DAT_cc008000 = *(undefined4 *)((int)local_2b8 + iVar6 + 4);
      iVar4 = ((iVar1 * 8 | (uint)((iVar8 + 1) * 0x20000000 + iVar1) >> 0x1d) - iVar1) + iVar10;
      DAT_cc008000 = *(undefined4 *)((int)local_2b8 + iVar6);
      DAT_cc008000 = *(undefined4 *)((int)local_2b8 + iVar6 + 8);
      iVar1 = iVar8 + 2 >> 0x1f;
      DAT_cc008000 = local_2b8[iVar4 * 3 + 1];
      iVar2 = iVar6 + 0xc;
      DAT_cc008000 = local_2b8[iVar4 * 3];
      DAT_cc008000 = local_2b8[iVar4 * 3 + 2];
      iVar4 = ((iVar1 * 8 | (uint)((iVar8 + 2) * 0x20000000 + iVar1) >> 0x1d) - iVar1) + iVar10;
      DAT_cc008000 = *(undefined4 *)((int)local_2b8 + iVar6 + 0x10);
      iVar1 = iVar6 + 0x14;
      iVar6 = iVar6 + 0x18;
      DAT_cc008000 = *(undefined4 *)((int)local_2b8 + iVar2);
      iVar8 = iVar8 + 2;
      DAT_cc008000 = *(undefined4 *)((int)local_2b8 + iVar1);
      DAT_cc008000 = local_2b8[iVar4 * 3 + 1];
      DAT_cc008000 = local_2b8[iVar4 * 3];
      DAT_cc008000 = local_2b8[iVar4 * 3 + 2];
      iVar14 = iVar14 + -1;
    } while (iVar14 != 0);
    iVar11 = iVar11 + 1;
    iVar10 = iVar10 + 8;
  } while (iVar11 < 5);
  iVar10 = 0;
  do {
    iVar6 = 0;
    iVar11 = 1;
    iVar8 = 3;
    do {
      uVar9 = countLeadingZeros(iVar6);
      iVar14 = 0x29;
      uVar9 = (iVar6 + -1) * 8 + iVar10 + 1U & ~-(uVar9 >> 5 & 1);
      DAT_cc008000 = local_2b8[uVar9 * 3 + 1];
      DAT_cc008000 = local_2b8[uVar9 * 3];
      DAT_cc008000 = local_2b8[uVar9 * 3 + 2];
      if (iVar6 != 5) {
        iVar14 = iVar10 + iVar11;
      }
      uVar9 = countLeadingZeros(iVar6 + 1);
      DAT_cc008000 = local_2b8[iVar14 * 3 + 1];
      uVar9 = iVar6 * 8 + iVar10 + 1U & ~-(uVar9 >> 5 & 1);
      DAT_cc008000 = local_2b8[iVar14 * 3];
      DAT_cc008000 = local_2b8[iVar14 * 3 + 2];
      iVar14 = 0x29;
      DAT_cc008000 = local_2b8[uVar9 * 3 + 1];
      DAT_cc008000 = local_2b8[uVar9 * 3];
      DAT_cc008000 = local_2b8[uVar9 * 3 + 2];
      if (iVar6 != 4) {
        iVar14 = iVar10 + iVar11 + 8;
      }
      iVar11 = iVar11 + 0x10;
      iVar6 = iVar6 + 2;
      DAT_cc008000 = local_2b8[iVar14 * 3 + 1];
      DAT_cc008000 = local_2b8[iVar14 * 3];
      DAT_cc008000 = local_2b8[iVar14 * 3 + 2];
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    iVar10 = iVar10 + 1;
  } while (iVar10 < 8);
  uVar5 = GXEndDisplayList();
  *(undefined4 *)&graphic->field_0x71f8 = uVar5;
  DCFlushRange(*(undefined4 *)&graphic->field_0x71fc,*(undefined4 *)&graphic->field_0x71f8);
  return;
}

