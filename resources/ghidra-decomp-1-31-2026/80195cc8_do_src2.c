// Function: do_src2
// Entry: 80195cc8
// Size: 492 bytes

void do_src2(undefined4 *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  double dVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  uint *puVar14;
  int *piVar15;
  uint uVar16;
  int iVar17;
  bool bVar18;
  int iVar19;
  
  dVar7 = DAT_803337d8;
  uVar8 = param_1[3];
  iVar9 = param_1[4];
  uVar11 = param_1[5];
  iVar13 = param_1[7];
  iVar12 = param_1[8];
  iVar17 = param_1[1];
  puVar14 = (uint *)param_1[2];
  iVar19 = 0xa0;
  piVar15 = (int *)*param_1;
  fVar2 = (float)((double)CONCAT44(0x43300000,*puVar14 ^ 0x80000000) - DAT_803337d8);
  fVar1 = (float)((double)CONCAT44(0x43300000,puVar14[2] ^ 0x80000000) - DAT_803337d8);
  fVar3 = (float)((double)CONCAT44(0x43300000,puVar14[1] ^ 0x80000000) - DAT_803337d8);
  fVar5 = (float)((double)CONCAT44(0x43300000,*(uint *)(iVar17 + iVar9 * 4) ^ 0x80000000) -
                 DAT_803337d8);
  while( true ) {
    while( true ) {
      fVar4 = fVar1;
      uVar16 = (uVar8 << 7 | uVar8 >> 0x19) & 0x7f0;
      bVar18 = CARRY4(uVar8,uVar11);
      uVar8 = uVar8 + uVar11;
      iVar10 = iVar9 + 1;
      if (!bVar18) break;
      if (iVar10 == iVar13) {
        iVar10 = iVar12;
      }
      fVar1 = (float)((double)CONCAT44(0x43300000,*(uint *)(iVar10 * 4 + iVar17) ^ 0x80000000) -
                     dVar7);
      iVar9 = iVar10 + 1;
      if (iVar10 + 1 == iVar13) {
        iVar9 = iVar12;
      }
      fVar6 = fVar5 * *(float *)(&DAT_8021b79c + uVar16) +
              fVar4 * *(float *)(&DAT_8021b798 + uVar16) +
              fVar3 * *(float *)(&DAT_8021b794 + uVar16) +
              fVar2 * *(float *)(&DAT_8021b790 + uVar16);
      iVar19 = iVar19 + -1;
      fVar3 = fVar4;
      fVar2 = fVar5;
      if (iVar19 == 0) goto LAB_80195e74;
      uVar16 = *(uint *)(iVar9 * 4 + iVar17);
      *piVar15 = (int)fVar6;
      piVar15 = piVar15 + 1;
      fVar2 = fVar4;
      fVar3 = fVar5;
      fVar5 = (float)((double)CONCAT44(0x43300000,uVar16 ^ 0x80000000) - dVar7);
    }
    iVar9 = iVar10;
    if (iVar10 == iVar13) {
      iVar9 = iVar12;
    }
    fVar6 = fVar5 * *(float *)(&DAT_8021b79c + uVar16) +
            fVar4 * *(float *)(&DAT_8021b798 + uVar16) +
            fVar3 * *(float *)(&DAT_8021b794 + uVar16) + fVar2 * *(float *)(&DAT_8021b790 + uVar16);
    iVar19 = iVar19 + -1;
    fVar2 = fVar4;
    fVar1 = fVar5;
    if (iVar19 == 0) break;
    uVar16 = *(uint *)(iVar9 * 4 + iVar17);
    *piVar15 = (int)fVar6;
    piVar15 = piVar15 + 1;
    fVar2 = fVar3;
    fVar3 = fVar4;
    fVar5 = (float)((double)CONCAT44(0x43300000,uVar16 ^ 0x80000000) - dVar7);
  }
LAB_80195e74:
  *piVar15 = (int)fVar6;
  piVar15 = (int *)param_1[2];
  *piVar15 = (int)fVar3;
  piVar15[1] = (int)fVar2;
  piVar15[2] = (int)fVar1;
  param_1[3] = uVar8;
  param_1[4] = iVar9;
  return;
}

