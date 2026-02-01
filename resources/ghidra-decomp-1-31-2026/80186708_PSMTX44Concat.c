// Function: PSMTX44Concat
// Entry: 80186708
// Size: 260 bytes

/* WARNING: Removing unreachable block (ram,0x80186804) */
/* WARNING: Removing unreachable block (ram,0x801867fc) */
/* WARNING: Removing unreachable block (ram,0x801867f4) */
/* WARNING: Removing unreachable block (ram,0x801867ec) */
/* WARNING: Removing unreachable block (ram,0x801867e4) */
/* WARNING: Removing unreachable block (ram,0x801867dc) */
/* WARNING: Removing unreachable block (ram,0x801867d4) */
/* WARNING: Removing unreachable block (ram,0x801867cc) */
/* WARNING: Removing unreachable block (ram,0x801867c4) */
/* WARNING: Removing unreachable block (ram,0x801867bc) */
/* WARNING: Removing unreachable block (ram,0x801867b4) */
/* WARNING: Removing unreachable block (ram,0x801867ac) */
/* WARNING: Removing unreachable block (ram,0x801867a4) */
/* WARNING: Removing unreachable block (ram,0x8018679c) */
/* WARNING: Removing unreachable block (ram,0x80186794) */
/* WARNING: Removing unreachable block (ram,0x8018678c) */
/* WARNING: Removing unreachable block (ram,0x80186784) */
/* WARNING: Removing unreachable block (ram,0x8018677c) */
/* WARNING: Removing unreachable block (ram,0x80186774) */
/* WARNING: Removing unreachable block (ram,0x8018676c) */
/* WARNING: Removing unreachable block (ram,0x80186764) */
/* WARNING: Removing unreachable block (ram,0x80186758) */
/* WARNING: Removing unreachable block (ram,0x8018674c) */
/* WARNING: Removing unreachable block (ram,0x80186740) */
/* WARNING: Removing unreachable block (ram,0x80186734) */
/* WARNING: Removing unreachable block (ram,0x8018672c) */
/* WARNING: Removing unreachable block (ram,0x80186724) */
/* WARNING: Removing unreachable block (ram,0x80186720) */
/* WARNING: Removing unreachable block (ram,0x80186718) */
/* WARNING: Removing unreachable block (ram,0x80186714) */
/* WARNING: Removing unreachable block (ram,0x8018670c) */
/* WARNING: Removing unreachable block (ram,0x80186708) */

void PSMTX44Concat(Mat4x4 *a,Mat4x4 *b,Mat4x4 *dest)

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
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  float fVar36;
  float fVar37;
  float fVar38;
  float fVar39;
  float fVar40;
  
  fVar1 = a->value[0][0];
  fVar21 = a->value[0][1];
  fVar2 = b->value[0][0];
  fVar22 = b->value[0][1];
  fVar3 = b->value[1][0];
  fVar23 = b->value[1][1];
  fVar4 = b->value[2][0];
  fVar24 = b->value[2][1];
  fVar5 = a->value[0][2];
  fVar25 = a->value[0][3];
  fVar6 = b->value[3][0];
  fVar26 = b->value[3][1];
  fVar7 = a->value[1][0];
  fVar27 = a->value[1][1];
  fVar8 = a->value[1][2];
  fVar28 = a->value[1][3];
  fVar9 = a->value[2][0];
  fVar29 = a->value[2][1];
  fVar10 = a->value[2][2];
  fVar30 = a->value[2][3];
  fVar11 = a->value[3][0];
  fVar31 = a->value[3][1];
  fVar12 = a->value[3][2];
  fVar32 = a->value[3][3];
  fVar13 = b->value[0][2];
  fVar33 = b->value[0][3];
  fVar14 = a->value[0][0];
  fVar34 = a->value[0][1];
  fVar15 = b->value[1][2];
  fVar35 = b->value[1][3];
  fVar16 = a->value[0][2];
  fVar36 = a->value[0][3];
  fVar17 = b->value[2][2];
  fVar37 = b->value[2][3];
  fVar18 = b->value[3][2];
  fVar38 = b->value[3][3];
  fVar19 = a->value[1][0];
  fVar39 = a->value[1][1];
  fVar20 = a->value[1][2];
  fVar40 = a->value[1][3];
  dest->value[0][0] = fVar6 * fVar25 + fVar4 * fVar5 + fVar3 * fVar21 + fVar2 * fVar1;
  dest->value[0][1] = fVar26 * fVar25 + fVar24 * fVar5 + fVar23 * fVar21 + fVar22 * fVar1;
  fVar1 = a->value[2][0];
  fVar21 = a->value[2][1];
  dest->value[1][0] = fVar6 * fVar28 + fVar4 * fVar8 + fVar3 * fVar27 + fVar2 * fVar7;
  dest->value[1][1] = fVar26 * fVar28 + fVar24 * fVar8 + fVar23 * fVar27 + fVar22 * fVar7;
  fVar5 = a->value[2][2];
  fVar8 = a->value[2][3];
  dest->value[2][0] = fVar6 * fVar30 + fVar4 * fVar10 + fVar3 * fVar29 + fVar2 * fVar9;
  dest->value[2][1] = fVar26 * fVar30 + fVar24 * fVar10 + fVar23 * fVar29 + fVar22 * fVar9;
  fVar7 = a->value[3][0];
  fVar9 = a->value[3][1];
  dest->value[3][0] = fVar6 * fVar32 + fVar4 * fVar12 + fVar3 * fVar31 + fVar2 * fVar11;
  dest->value[3][1] = fVar26 * fVar32 + fVar24 * fVar12 + fVar23 * fVar31 + fVar22 * fVar11;
  fVar2 = a->value[3][2];
  fVar3 = a->value[3][3];
  dest->value[0][2] = fVar18 * fVar36 + fVar17 * fVar16 + fVar15 * fVar34 + fVar13 * fVar14;
  dest->value[0][3] = fVar38 * fVar36 + fVar37 * fVar16 + fVar35 * fVar34 + fVar33 * fVar14;
  dest->value[1][2] = fVar18 * fVar40 + fVar17 * fVar20 + fVar15 * fVar39 + fVar13 * fVar19;
  dest->value[1][3] = fVar38 * fVar40 + fVar37 * fVar20 + fVar35 * fVar39 + fVar33 * fVar19;
  dest->value[2][2] = fVar18 * fVar8 + fVar17 * fVar5 + fVar15 * fVar21 + fVar13 * fVar1;
  dest->value[2][3] = fVar38 * fVar8 + fVar37 * fVar5 + fVar35 * fVar21 + fVar33 * fVar1;
  dest->value[3][2] = fVar18 * fVar3 + fVar17 * fVar2 + fVar15 * fVar9 + fVar13 * fVar7;
  dest->value[3][3] = fVar38 * fVar3 + fVar37 * fVar2 + fVar35 * fVar9 + fVar33 * fVar7;
  return;
}

