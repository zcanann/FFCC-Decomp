// Function: PSMTXReflect
// Entry: 80186010
// Size: 112 bytes

/* WARNING: Removing unreachable block (ram,0x80186078) */
/* WARNING: Removing unreachable block (ram,0x80186074) */
/* WARNING: Removing unreachable block (ram,0x8018606c) */
/* WARNING: Removing unreachable block (ram,0x8018605c) */
/* WARNING: Removing unreachable block (ram,0x80186050) */
/* WARNING: Removing unreachable block (ram,0x80186040) */
/* WARNING: Removing unreachable block (ram,0x80186024) */
/* WARNING: Removing unreachable block (ram,0x8018601c) */
/* WARNING: Removing unreachable block (ram,0x80186018) */
/* WARNING: Removing unreachable block (ram,0x80186014) */

void PSMTXReflect(Mtx *destination,Vec *p,Vec *n)

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
  
  fVar10 = FLOAT_803336e0;
  fVar1 = n->z;
  fVar2 = n->x;
  fVar5 = n->y;
  fVar3 = p->x;
  fVar6 = p->y;
  fVar9 = -(fVar1 * FLOAT_803336e0 + fVar1);
  fVar4 = p->z;
  fVar8 = -(fVar2 * FLOAT_803336e0 + fVar2);
  fVar7 = -(fVar5 * FLOAT_803336e0 + fVar5);
  destination->value[2][0] = fVar2 * fVar9;
  destination->value[2][1] = fVar5 * fVar9;
  fVar3 = -(fVar9 * fVar4 + fVar8 * fVar3 + fVar7 * fVar6);
  destination->value[0][0] = fVar2 * fVar8 + fVar10;
  destination->value[0][1] = fVar5 * fVar8;
  destination->value[1][0] = fVar2 * fVar7;
  destination->value[1][1] = fVar10 + fVar5 * fVar7;
  destination->value[0][2] = fVar2 * fVar9;
  destination->value[0][3] = fVar2 * fVar3;
  destination->value[1][2] = fVar5 * fVar9;
  destination->value[1][3] = fVar5 * fVar3;
  destination->value[2][2] = fVar9 * fVar1 + fVar10;
  destination->value[2][3] = fVar3 * fVar1;
  return;
}

