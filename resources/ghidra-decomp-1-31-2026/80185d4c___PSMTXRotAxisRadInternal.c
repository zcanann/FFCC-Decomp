// Function: __PSMTXRotAxisRadInternal
// Entry: 80185d4c
// Size: 176 bytes

/* WARNING: Removing unreachable block (ram,0x80185df4) */
/* WARNING: Removing unreachable block (ram,0x80185df0) */
/* WARNING: Removing unreachable block (ram,0x80185de8) */
/* WARNING: Removing unreachable block (ram,0x80185de0) */
/* WARNING: Removing unreachable block (ram,0x80185dd8) */
/* WARNING: Removing unreachable block (ram,0x80185dd0) */
/* WARNING: Removing unreachable block (ram,0x80185d58) */

void __PSMTXRotAxisRadInternal(float rX,float rY,Mtx *destination,Vec *origin)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  
  fVar2 = origin->x;
  fVar3 = origin->y;
  fVar1 = origin->z;
  fVar5 = FLOAT_803336e8 - FLOAT_803336e8;
  fVar6 = fVar1 * fVar1 + fVar2 * fVar2 + fVar3 * fVar3;
  fVar7 = (FLOAT_803336e8 + FLOAT_803336e8) - rY;
  fVar4 = 1.0 / SQRT(fVar6);
  fVar4 = -(fVar4 * fVar4 * fVar6 - FLOAT_803336ec) * fVar4 * FLOAT_803336e8;
  fVar2 = fVar2 * fVar4;
  fVar3 = fVar3 * fVar4;
  fVar1 = fVar1 * fVar4;
  fVar6 = fVar2 * fVar7;
  fVar4 = fVar3 * fVar7 * fVar1;
  destination->value[0][2] = fVar6 * fVar1 + fVar3 * rX;
  destination->value[0][3] = fVar5;
  destination->value[0][0] = fVar6 * fVar2 + rY;
  destination->value[0][1] = -(fVar1 * rX - fVar6 * fVar3);
  destination->value[1][0] = fVar1 * rX + fVar6 * fVar3;
  destination->value[1][1] = rY + fVar3 * fVar7 * fVar3;
  destination->value[1][2] = -(fVar2 * rX) + fVar4;
  destination->value[1][3] = fVar5;
  destination->value[2][0] = fVar6 * fVar1 + -(fVar3 * rX);
  destination->value[2][1] = fVar2 * rX + fVar4;
  destination->value[2][2] = fVar1 * fVar7 * fVar1 + rY;
  destination->value[2][3] = fVar5;
  return;
}

