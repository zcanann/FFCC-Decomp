// Function: do_src1
// Entry: 80195b30
// Size: 408 bytes

void do_src1(undefined4 *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint *puVar12;
  int *piVar13;
  uint uVar14;
  int iVar15;
  bool bVar16;
  int iVar17;
  
  dVar6 = DAT_803337d8;
  uVar7 = param_1[3];
  iVar8 = param_1[4];
  uVar9 = param_1[5];
  iVar11 = param_1[7];
  iVar10 = param_1[8];
  iVar15 = param_1[1];
  puVar12 = (uint *)param_1[2];
  iVar17 = 0xa0;
  piVar13 = (int *)*param_1;
  fVar1 = (float)((double)CONCAT44(0x43300000,*puVar12 ^ 0x80000000) - DAT_803337d8);
  fVar2 = (float)((double)CONCAT44(0x43300000,puVar12[1] ^ 0x80000000) - DAT_803337d8);
  fVar3 = (float)((double)CONCAT44(0x43300000,puVar12[2] ^ 0x80000000) - DAT_803337d8);
  fVar4 = (float)((double)CONCAT44(0x43300000,*(uint *)(iVar15 + iVar8 * 4) ^ 0x80000000) -
                 DAT_803337d8);
  do {
    while( true ) {
      uVar14 = (uVar7 << 7 | uVar7 >> 0x19) & 0x7f0;
      bVar16 = CARRY4(uVar7,uVar9);
      uVar7 = uVar7 + uVar9;
      if (bVar16) break;
      *piVar13 = (int)(fVar4 * *(float *)(&DAT_8021b79c + uVar14) +
                      fVar3 * *(float *)(&DAT_8021b798 + uVar14) +
                      fVar2 * *(float *)(&DAT_8021b794 + uVar14) +
                      fVar1 * *(float *)(&DAT_8021b790 + uVar14));
      iVar17 = iVar17 + -1;
      piVar13 = piVar13 + 1;
      if (iVar17 == 0) {
LAB_80195c90:
        piVar13 = (int *)param_1[2];
        *piVar13 = (int)fVar1;
        piVar13[1] = (int)fVar2;
        piVar13[2] = (int)fVar3;
        param_1[3] = uVar7;
        param_1[4] = iVar8;
        return;
      }
    }
    iVar8 = iVar8 + 1;
    if (iVar8 == iVar11) {
      iVar8 = iVar10;
    }
    fVar5 = fVar4 * *(float *)(&DAT_8021b79c + uVar14) +
            fVar3 * *(float *)(&DAT_8021b798 + uVar14) +
            fVar2 * *(float *)(&DAT_8021b794 + uVar14) + fVar1 * *(float *)(&DAT_8021b790 + uVar14);
    iVar17 = iVar17 + -1;
    fVar1 = fVar2;
    fVar2 = fVar3;
    fVar3 = fVar4;
    if (iVar17 == 0) {
      *piVar13 = (int)fVar5;
      goto LAB_80195c90;
    }
    uVar14 = *(uint *)(iVar8 * 4 + iVar15);
    *piVar13 = (int)fVar5;
    piVar13 = piVar13 + 1;
    fVar4 = (float)((double)CONCAT44(0x43300000,uVar14 ^ 0x80000000) - dVar6);
  } while( true );
}

