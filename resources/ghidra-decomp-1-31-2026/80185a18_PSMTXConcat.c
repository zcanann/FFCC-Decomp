// Function: PSMTXConcat
// Entry: 80185a18
// Size: 204 bytes

/* WARNING: Removing unreachable block (ram,0x80185ad4) */
/* WARNING: Removing unreachable block (ram,0x80185ac8) */
/* WARNING: Removing unreachable block (ram,0x80185ac0) */
/* WARNING: Removing unreachable block (ram,0x80185aac) */
/* WARNING: Removing unreachable block (ram,0x80185aa4) */
/* WARNING: Removing unreachable block (ram,0x80185a94) */
/* WARNING: Removing unreachable block (ram,0x80185a80) */
/* WARNING: Removing unreachable block (ram,0x80185a7c) */
/* WARNING: Removing unreachable block (ram,0x80185a74) */
/* WARNING: Removing unreachable block (ram,0x80185a6c) */
/* WARNING: Removing unreachable block (ram,0x80185a64) */
/* WARNING: Removing unreachable block (ram,0x80185a5c) */
/* WARNING: Removing unreachable block (ram,0x80185a54) */
/* WARNING: Removing unreachable block (ram,0x80185a4c) */
/* WARNING: Removing unreachable block (ram,0x80185a44) */
/* WARNING: Removing unreachable block (ram,0x80185a3c) */
/* WARNING: Removing unreachable block (ram,0x80185a2c) */
/* WARNING: Removing unreachable block (ram,0x80185a24) */
/* WARNING: Removing unreachable block (ram,0x80185a1c) */

void PSMTXConcat(Mtx *a,Mtx *b,Mtx *ab)

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
  
  fVar26 = DAT_8032eacc;
  fVar25 = DAT_8032eac8;
  fVar1 = a->value[0][0];
  fVar13 = a->value[0][1];
  fVar2 = b->value[0][0];
  fVar14 = b->value[0][1];
  fVar3 = b->value[0][2];
  fVar15 = b->value[0][3];
  fVar4 = b->value[1][0];
  fVar16 = b->value[1][1];
  fVar5 = a->value[1][0];
  fVar17 = a->value[1][1];
  fVar6 = b->value[1][2];
  fVar18 = b->value[1][3];
  fVar7 = a->value[0][2];
  fVar19 = a->value[0][3];
  fVar8 = a->value[1][2];
  fVar20 = a->value[1][3];
  fVar9 = b->value[2][0];
  fVar21 = b->value[2][1];
  fVar10 = b->value[2][2];
  fVar22 = b->value[2][3];
  fVar11 = a->value[2][0];
  fVar23 = a->value[2][1];
  fVar12 = a->value[2][2];
  fVar24 = a->value[2][3];
  ab->value[0][0] = fVar9 * fVar7 + fVar4 * fVar13 + fVar2 * fVar1;
  ab->value[0][1] = fVar21 * fVar7 + fVar16 * fVar13 + fVar14 * fVar1;
  ab->value[1][0] = fVar9 * fVar8 + fVar4 * fVar17 + fVar2 * fVar5;
  ab->value[1][1] = fVar21 * fVar8 + fVar16 * fVar17 + fVar14 * fVar5;
  ab->value[0][2] = fVar25 * fVar19 + fVar10 * fVar7 + fVar6 * fVar13 + fVar3 * fVar1;
  ab->value[0][3] = fVar26 * fVar19 + fVar22 * fVar7 + fVar18 * fVar13 + fVar15 * fVar1;
  ab->value[1][2] = fVar25 * fVar20 + fVar10 * fVar8 + fVar6 * fVar17 + fVar3 * fVar5;
  ab->value[1][3] = fVar26 * fVar20 + fVar22 * fVar8 + fVar18 * fVar17 + fVar15 * fVar5;
  ab->value[2][0] = fVar9 * fVar12 + fVar4 * fVar23 + fVar2 * fVar11;
  ab->value[2][1] = fVar21 * fVar12 + fVar16 * fVar23 + fVar14 * fVar11;
  ab->value[2][2] = fVar25 * fVar24 + fVar10 * fVar12 + fVar6 * fVar23 + fVar3 * fVar11;
  ab->value[2][3] = fVar26 * fVar24 + fVar22 * fVar12 + fVar18 * fVar23 + fVar15 * fVar11;
  return;
}

