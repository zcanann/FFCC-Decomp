// Function: PSMTXQuat
// Entry: 80185f6c
// Size: 164 bytes

/* WARNING: Removing unreachable block (ram,0x80186008) */
/* WARNING: Removing unreachable block (ram,0x80186004) */
/* WARNING: Removing unreachable block (ram,0x80185ff8) */
/* WARNING: Removing unreachable block (ram,0x80185ff4) */
/* WARNING: Removing unreachable block (ram,0x80185fe8) */
/* WARNING: Removing unreachable block (ram,0x80185fd4) */
/* WARNING: Removing unreachable block (ram,0x80185fc8) */
/* WARNING: Removing unreachable block (ram,0x80185fbc) */
/* WARNING: Removing unreachable block (ram,0x80185f74) */
/* WARNING: Removing unreachable block (ram,0x80185f70) */

void PSMTXQuat(Mtx *destination,Quat *quat)

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
  
  fVar12 = FLOAT_803336e0;
  fVar1 = quat->x;
  fVar3 = quat->y;
  fVar2 = quat->z;
  fVar4 = quat->w;
  fVar5 = FLOAT_803336e0 - FLOAT_803336e0;
  fVar6 = FLOAT_803336e0 + FLOAT_803336e0;
  fVar8 = fVar3 * fVar3;
  fVar9 = fVar2 * fVar2 + fVar1 * fVar1;
  fVar7 = fVar9 + fVar4 * fVar4 + fVar8;
  fVar10 = 1.0 / fVar7;
  fVar10 = fVar10 * -(fVar7 * fVar10 - fVar6) * fVar6;
  destination->value[0][3] = fVar5;
  destination->value[2][3] = fVar5;
  destination->value[2][2] = -((fVar1 * fVar1 + fVar8) * fVar10 - fVar12);
  fVar11 = fVar1 * fVar2 + fVar3 * fVar4;
  fVar7 = fVar3 * fVar2 + fVar1 * fVar4;
  destination->value[1][0] = (fVar1 * fVar3 + fVar2 * fVar4) * fVar10;
  destination->value[1][1] = -(fVar9 * fVar10 - fVar12);
  destination->value[0][0] = -((fVar2 * fVar2 + fVar8) * fVar10 - fVar12);
  destination->value[0][1] = (fVar1 * fVar3 - fVar2 * fVar4) * fVar10;
  destination->value[0][2] = fVar11 * fVar10;
  destination->value[1][2] = -(fVar1 * fVar4 * fVar6 - fVar7) * fVar10;
  destination->value[1][3] = fVar5;
  destination->value[2][0] = -(fVar3 * fVar4 * fVar6 - fVar11) * fVar10;
  destination->value[2][1] = fVar7 * fVar10;
  return;
}

