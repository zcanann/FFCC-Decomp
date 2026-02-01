// Function: PSMTXInverse
// Entry: 80185b34
// Size: 248 bytes

/* WARNING: Removing unreachable block (ram,0x80185c24) */
/* WARNING: Removing unreachable block (ram,0x80185c18) */
/* WARNING: Removing unreachable block (ram,0x80185c10) */
/* WARNING: Removing unreachable block (ram,0x80185c08) */
/* WARNING: Removing unreachable block (ram,0x80185bfc) */
/* WARNING: Removing unreachable block (ram,0x80185bf4) */
/* WARNING: Removing unreachable block (ram,0x80185be8) */
/* WARNING: Removing unreachable block (ram,0x80185be0) */
/* WARNING: Removing unreachable block (ram,0x80185b50) */
/* WARNING: Removing unreachable block (ram,0x80185b48) */
/* WARNING: Removing unreachable block (ram,0x80185b44) */
/* WARNING: Removing unreachable block (ram,0x80185b3c) */
/* WARNING: Removing unreachable block (ram,0x80185b38) */
/* WARNING: Removing unreachable block (ram,0x80185b34) */

undefined4 PSMTXInverse(Mtx *source,Mtx *dest)

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
  
  fVar3 = source->value[0][0];
  fVar4 = source->value[0][1];
  fVar9 = source->value[0][2];
  fVar5 = source->value[1][0];
  fVar6 = source->value[1][1];
  fVar10 = source->value[1][2];
  fVar7 = source->value[2][0];
  fVar8 = source->value[2][1];
  fVar11 = source->value[2][2];
  fVar14 = fVar4 * fVar10 - fVar6 * fVar9;
  fVar15 = fVar6 * fVar11 - fVar8 * fVar10;
  fVar13 = fVar8 * fVar9 - fVar4 * fVar11;
  fVar1 = fVar7 * fVar14 + fVar5 * fVar13 + fVar3 * fVar15;
  if (fVar1 != fVar9 - fVar9) {
    fVar2 = 1.0 / fVar1;
    fVar17 = -(fVar1 * fVar2 * fVar2 - (fVar2 + fVar2));
    fVar1 = source->value[0][3];
    fVar15 = fVar15 * fVar17;
    fVar16 = (fVar10 * fVar7 - fVar11 * fVar5) * fVar17;
    fVar2 = source->value[1][3];
    fVar13 = fVar13 * fVar17;
    fVar12 = (fVar11 * fVar3 - fVar9 * fVar7) * fVar17;
    fVar11 = source->value[2][3];
    fVar14 = fVar14 * fVar17;
    fVar10 = (fVar9 * fVar5 - fVar10 * fVar3) * fVar17;
    fVar9 = (fVar5 * fVar8 - fVar6 * fVar7) * fVar17;
    fVar7 = (fVar4 * fVar7 - fVar3 * fVar8) * fVar17;
    dest->value[0][0] = fVar15;
    dest->value[0][1] = fVar13;
    dest->value[1][0] = fVar16;
    dest->value[1][1] = fVar12;
    fVar17 = (fVar3 * fVar6 - fVar4 * fVar5) * fVar17;
    dest->value[2][0] = fVar9;
    dest->value[2][1] = fVar7;
    dest->value[2][2] = fVar17;
    dest->value[0][2] = fVar14;
    dest->value[0][3] = -(fVar14 * fVar11 + fVar13 * fVar2 + fVar15 * fVar1);
    dest->value[1][2] = fVar10;
    dest->value[1][3] = -(fVar10 * fVar11 + fVar12 * fVar2 + fVar16 * fVar1);
    dest->value[2][3] = -(fVar17 * fVar11 + fVar7 * fVar2 + fVar9 * fVar1);
    return 1;
  }
  return 0;
}

